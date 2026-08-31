/* Native Redis state provider adapter (Task 17).
 *
 * This translation unit is wired into rule_engine_core by CMake only when
 * RULE_ENGINE_ENABLE_REDIS is ON and hiredis is discovered (which also defines
 * RE_HAS_HIREDIS). The whole body is guarded by RE_HAS_HIREDIS: without the
 * macro the file contributes no symbols, so accidental inclusion in a build is
 * harmless (the re_internal.h include keeps the translation unit non-empty).
 *
 * Bounded configuration seam: the v1 provider API (re_state_provider_options_t)
 * has no connection-string field, so the adapter takes its connection from the
 * RE_REDIS_URL environment variable in the form
 * "redis://host[:port][/db][?prefix=name]" (default "redis://127.0.0.1:6379")
 * and uses the fixed default key prefix "re" when the URL carries no
 * ?prefix=. Keys are stored as "<prefix>:<name>". Values are raw bytes:
 * a 4-byte re_value_type tag followed by the payload (STRING bytes as-is),
 * relying on Redis binary-safe length-prefixed semantics - no JSON. A put with
 * a TTL uses PSETEX, a plain put SET; get uses GET, delete DEL, ttl PTTL.
 *
 * Error reporting: command and connection failures record
 * RE_PROVIDER_ERROR_UNAVAILABLE (corrupt stored data records
 * RE_PROVIDER_ERROR_SERIALIZATION) with a message in provider->last_error and
 * return RE_STATUS_ERROR; the in-memory provider reports only status codes, so
 * last_error is the adapter's added diagnostics channel. A connect failure
 * during create returns RE_STATUS_ERROR with *out_provider left NULL, because
 * no provider instance exists yet to carry last_error.
 *
 * Borrow rule: a STRING value returned by get is backed by the provider and
 * stays valid until the next provider call or destroy - the same borrow the
 * in-memory provider and re_facts_get document.
 */
#include "re_internal.h"

#if defined(RE_HAS_HIREDIS)

#if defined(_WIN32)
/* winsock2.h defines struct timeval, which hiredis.h only forward-declares
 * when _MSC_VER is set (clang targeting the MSVC ABI, and MSVC itself), but
 * this file uses it as a complete type for redisConnectWithTimeout. Include
 * it before hiredis.h so the tracked source needs no hiredis header patch. */
#include <winsock2.h>
#endif

#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct redis_state_t {
    re_allocator_impl_t allocator;
    redisContext *connection;
    char *prefix;
    size_t prefix_size;
    /* Backing store for the last STRING result handed out by redis_get. */
    char *last_string;
    /* Backing store for provider->last_error.message. */
    char error_message[256];
} redis_state_t;

static re_status_t redis_fail(re_state_provider_t *provider, redis_state_t *state,
                              re_provider_error_t kind, const char *message) {
    size_t size;
    if (provider == NULL) return RE_STATUS_ERROR;
    size = strlen(message);
    if (size >= sizeof(state->error_message)) size = sizeof(state->error_message) - 1u;
    memcpy(state->error_message, message, size);
    state->error_message[size] = '\0';
    provider->last_error.struct_size = (uint32_t)sizeof(provider->last_error);
    provider->last_error.kind = kind;
    provider->last_error.message.data = state->error_message;
    provider->last_error.message.size = size;
    return RE_STATUS_ERROR;
}

/* Frees an error reply and records the failure; returns the reply on success. */
static redisReply *redis_checked(re_state_provider_t *provider, redis_state_t *state,
                                 redisReply *reply) {
    if (reply == NULL) {
        redis_fail(provider, state, RE_PROVIDER_ERROR_UNAVAILABLE,
                   state->connection->errstr[0] != '\0' ? state->connection->errstr
                                                        : "redis connection error");
        return NULL;
    }
    if (reply->type == REDIS_REPLY_ERROR) {
        redis_fail(provider, state, RE_PROVIDER_ERROR_UNAVAILABLE,
                   reply->str != NULL ? reply->str : "redis command error");
        freeReplyObject(reply);
        return NULL;
    }
    return reply;
}

/* Builds the owned "<prefix>:<name>" key buffer; NULL for an invalid key. */
static char *redis_key(redis_state_t *state, re_string_t key, size_t *out_size) {
    char *full;
    if (key.data == NULL || key.size == 0u) return NULL;
    if (key.size > SIZE_MAX - state->prefix_size - 1u) return NULL;
    *out_size = state->prefix_size + 1u + key.size;
    full = re_alloc(&state->allocator, *out_size);
    if (full == NULL) return NULL;
    memcpy(full, state->prefix, state->prefix_size);
    full[state->prefix_size] = ':';
    memcpy(full + state->prefix_size + 1u, key.data, key.size);
    return full;
}

static size_t redis_value_payload(const re_value_t *value) {
    switch (value->type) {
    case RE_VALUE_BOOL: return sizeof(value->as.boolean);
    case RE_VALUE_INT64: return sizeof(value->as.int64_value);
    case RE_VALUE_DOUBLE: return sizeof(value->as.double_value);
    case RE_VALUE_STRING: return value->as.string.size;
    case RE_VALUE_NULL: return 0u;
    case RE_VALUE_UNKNOWN: return 0u;
    default: return SIZE_MAX;
    }
}

/* Encodes value as [4-byte type tag][payload]; raw bytes, no JSON. */
static re_status_t redis_encode_value(redis_state_t *state, const re_value_t *value,
                                      char **out_data, size_t *out_size) {
    size_t payload = redis_value_payload(value);
    char *data;
    if (payload == SIZE_MAX) return RE_STATUS_INVALID_ARGUMENT;
    if (value->type == RE_VALUE_STRING && payload != 0u && value->as.string.data == NULL)
        return RE_STATUS_INVALID_ARGUMENT;
    if (payload > SIZE_MAX - sizeof(int32_t)) return RE_STATUS_INVALID_ARGUMENT;
    data = re_alloc(&state->allocator, sizeof(int32_t) + payload);
    if (data == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(data, &value->type, sizeof(int32_t));
    if (payload != 0u) {
        if (value->type == RE_VALUE_STRING) memcpy(data + sizeof(int32_t), value->as.string.data, payload);
        else memcpy(data + sizeof(int32_t), &value->as, payload);
    }
    *out_data = data;
    *out_size = sizeof(int32_t) + payload;
    return RE_STATUS_OK;
}

/* Decodes the stored bytes; a STRING result borrows state->last_string. */
static re_status_t redis_decode_value(re_state_provider_t *provider, redis_state_t *state,
                                      const char *data, size_t size, re_value_t *out) {
    int32_t type;
    const char *payload;
    size_t payload_size;
    char *copy;
    if (size < sizeof(int32_t))
        return redis_fail(provider, state, RE_PROVIDER_ERROR_SERIALIZATION,
                          "stored redis value is too short");
    memcpy(&type, data, sizeof(int32_t));
    payload = data + sizeof(int32_t);
    payload_size = size - sizeof(int32_t);
    memset(out, 0, sizeof(*out));
    switch (type) {
    case RE_VALUE_BOOL:
        if (payload_size != sizeof(out->as.boolean)) break;
        out->type = RE_VALUE_BOOL;
        memcpy(&out->as.boolean, payload, payload_size);
        return RE_STATUS_OK;
    case RE_VALUE_INT64:
        if (payload_size != sizeof(out->as.int64_value)) break;
        out->type = RE_VALUE_INT64;
        memcpy(&out->as.int64_value, payload, payload_size);
        return RE_STATUS_OK;
    case RE_VALUE_DOUBLE:
        if (payload_size != sizeof(out->as.double_value)) break;
        out->type = RE_VALUE_DOUBLE;
        memcpy(&out->as.double_value, payload, payload_size);
        return RE_STATUS_OK;
    case RE_VALUE_STRING:
        copy = re_alloc(&state->allocator, payload_size + 1u);
        if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
        if (payload_size != 0u) memcpy(copy, payload, payload_size);
        copy[payload_size] = '\0';
        re_free(&state->allocator, state->last_string);
        state->last_string = copy;
        out->type = RE_VALUE_STRING;
        out->as.string.data = copy;
        out->as.string.size = payload_size;
        return RE_STATUS_OK;
    case RE_VALUE_NULL:
    case RE_VALUE_UNKNOWN:
        if (payload_size != 0u) break;
        out->type = (re_value_type_t)type;
        return RE_STATUS_OK;
    default:
        break;
    }
    return redis_fail(provider, state, RE_PROVIDER_ERROR_SERIALIZATION,
                      "stored redis value has a bad type tag or payload size");
}

static re_status_t redis_get(re_state_provider_t *provider, re_string_t key,
                             re_value_t *out, void *context) {
    redis_state_t *state = context;
    char *full_key;
    size_t key_size = 0u;
    redisReply *reply;
    re_status_t status;
    if (out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    full_key = redis_key(state, key, &key_size);
    if (full_key == NULL) return RE_STATUS_INVALID_ARGUMENT;
    reply = redis_checked(provider, state,
                          redisCommand(state->connection, "GET %b", full_key, key_size));
    re_free(&state->allocator, full_key);
    if (reply == NULL) return RE_STATUS_ERROR;
    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return RE_STATUS_NOT_FOUND;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        freeReplyObject(reply);
        return redis_fail(provider, state, RE_PROVIDER_ERROR_SERIALIZATION,
                          "unexpected redis GET reply type");
    }
    status = redis_decode_value(provider, state, reply->str, (size_t)reply->len, out);
    freeReplyObject(reply);
    return status;
}

static re_status_t redis_put(re_state_provider_t *provider, re_string_t key,
                             const re_value_t *value, uint64_t ttl, void *context) {
    redis_state_t *state = context;
    char *full_key;
    char *encoded = NULL;
    size_t key_size = 0u, encoded_size = 0u;
    redisReply *reply;
    re_status_t status;
    if (value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    full_key = redis_key(state, key, &key_size);
    if (full_key == NULL) return RE_STATUS_INVALID_ARGUMENT;
    status = redis_encode_value(state, value, &encoded, &encoded_size);
    if (status != RE_STATUS_OK) {
        re_free(&state->allocator, full_key);
        return status;
    }
    if (ttl != 0u) {
        char ttl_text[24];
        snprintf(ttl_text, sizeof(ttl_text), "%llu", (unsigned long long)ttl);
        reply = redisCommand(state->connection, "PSETEX %b %s %b",
                             full_key, key_size, ttl_text, encoded, encoded_size);
    } else {
        reply = redisCommand(state->connection, "SET %b %b",
                             full_key, key_size, encoded, encoded_size);
    }
    reply = redis_checked(provider, state, reply);
    re_free(&state->allocator, full_key);
    re_free(&state->allocator, encoded);
    if (reply == NULL) return RE_STATUS_ERROR;
    if (reply->type != REDIS_REPLY_STATUS) {
        freeReplyObject(reply);
        return redis_fail(provider, state, RE_PROVIDER_ERROR_UNAVAILABLE,
                          "unexpected redis SET/PSETEX reply type");
    }
    freeReplyObject(reply);
    return RE_STATUS_OK;
}

static re_status_t redis_set(re_state_provider_t *provider, re_string_t key,
                             const re_value_t *value, void *context) {
    return redis_put(provider, key, value, 0u, context);
}

static re_status_t redis_delete(re_state_provider_t *provider, re_string_t key, void *context) {
    redis_state_t *state = context;
    char *full_key;
    size_t key_size = 0u;
    redisReply *reply;
    re_status_t status = RE_STATUS_OK;
    full_key = redis_key(state, key, &key_size);
    if (full_key == NULL) return RE_STATUS_INVALID_ARGUMENT;
    reply = redis_checked(provider, state,
                          redisCommand(state->connection, "DEL %b", full_key, key_size));
    re_free(&state->allocator, full_key);
    if (reply == NULL) return RE_STATUS_ERROR;
    if (reply->type != REDIS_REPLY_INTEGER)
        status = redis_fail(provider, state, RE_PROVIDER_ERROR_UNAVAILABLE,
                            "unexpected redis DEL reply type");
    else if (reply->integer == 0)
        status = RE_STATUS_NOT_FOUND;
    freeReplyObject(reply);
    return status;
}

static re_status_t redis_ttl(re_state_provider_t *provider, re_string_t key,
                             uint64_t *out, void *context) {
    redis_state_t *state = context;
    char *full_key;
    size_t key_size = 0u;
    redisReply *reply;
    re_status_t status = RE_STATUS_OK;
    if (out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    full_key = redis_key(state, key, &key_size);
    if (full_key == NULL) return RE_STATUS_INVALID_ARGUMENT;
    reply = redis_checked(provider, state,
                          redisCommand(state->connection, "PTTL %b", full_key, key_size));
    re_free(&state->allocator, full_key);
    if (reply == NULL) return RE_STATUS_ERROR;
    if (reply->type != REDIS_REPLY_INTEGER) {
        status = redis_fail(provider, state, RE_PROVIDER_ERROR_UNAVAILABLE,
                            "unexpected redis PTTL reply type");
    } else if (reply->integer == -2) {
        status = RE_STATUS_NOT_FOUND;
    } else if (reply->integer == -1) {
        *out = 0u;
    } else {
        *out = (uint64_t)reply->integer;
    }
    freeReplyObject(reply);
    return status;
}

static void redis_release(void *context) {
    redis_state_t *state = context;
    if (state->connection != NULL) redisFree(state->connection);
    re_free(&state->allocator, state->last_string);
    re_free(&state->allocator, state->prefix);
    re_free(&state->allocator, state);
}

/* Parses "redis://host[:port][/db][?prefix=name]". Returns RE_STATUS_OK on a
 * well-formed URL; empty host/port/db segments keep their defaults. */
static re_status_t redis_parse_url(const char *url, char *host, size_t host_capacity,
                                   int *port, long *database,
                                   const char **prefix, size_t *prefix_size) {
    static const char scheme[] = "redis://";
    const char *cursor;
    const char *host_end;
    size_t host_size;
    char *end;
    if (strncmp(url, scheme, sizeof(scheme) - 1u) != 0) return RE_STATUS_INVALID_ARGUMENT;
    cursor = url + sizeof(scheme) - 1u;
    host_end = cursor;
    while (*host_end != '\0' && *host_end != ':' && *host_end != '/' && *host_end != '?')
        ++host_end;
    host_size = (size_t)(host_end - cursor);
    if (host_size >= host_capacity) return RE_STATUS_INVALID_ARGUMENT;
    if (host_size != 0u) {
        memcpy(host, cursor, host_size);
        host[host_size] = '\0';
    }
    cursor = host_end;
    if (*cursor == ':') {
        long parsed = strtol(cursor + 1, &end, 10);
        if (end == cursor + 1 || parsed < 1 || parsed > 65535) return RE_STATUS_INVALID_ARGUMENT;
        *port = (int)parsed;
        cursor = end;
    }
    if (*cursor == '/') {
        long parsed = strtol(cursor + 1, &end, 10);
        if (end == cursor + 1 || parsed < 0) return RE_STATUS_INVALID_ARGUMENT;
        *database = parsed;
        cursor = end;
    }
    if (*cursor == '?') {
        static const char key[] = "prefix=";
        if (strncmp(cursor + 1, key, sizeof(key) - 1u) != 0) return RE_STATUS_INVALID_ARGUMENT;
        *prefix = cursor + 1 + sizeof(key) - 1u;
        *prefix_size = strlen(*prefix);
        if (*prefix_size == 0u) return RE_STATUS_INVALID_ARGUMENT;
        cursor += strlen(cursor);
    }
    return *cursor == '\0' ? RE_STATUS_OK : RE_STATUS_INVALID_ARGUMENT;
}

re_status_t re_redis_provider_create(re_engine_t *engine,
                                     const re_state_provider_options_t *options,
                                     re_state_provider_t **out_provider) {
    redis_state_t *state;
    re_state_provider_t *provider;
    const char *url;
    const char *prefix = "re";
    size_t prefix_size = 2u;
    char host[128] = "127.0.0.1";
    int port = 6379;
    long database = -1;
    re_status_t status;
    if (engine == NULL || options == NULL || out_provider == NULL ||
        options->struct_size < sizeof(*options) ||
        options->abi_version != RE_STATE_PROVIDER_ABI_VERSION ||
        options->kind != RE_STATE_PROVIDER_REDIS) return RE_STATUS_INVALID_ARGUMENT;
    *out_provider = NULL;
    url = getenv("RE_REDIS_URL");
    if (url == NULL || *url == '\0') url = "redis://127.0.0.1:6379";
    status = redis_parse_url(url, host, sizeof(host), &port, &database, &prefix, &prefix_size);
    if (status != RE_STATUS_OK) return status;
    state = re_alloc(&engine->allocator, sizeof(*state));
    provider = state == NULL ? NULL : re_alloc(&engine->allocator, sizeof(*provider));
    if (state == NULL || provider == NULL) {
        re_free(&engine->allocator, state);
        re_free(&engine->allocator, provider);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    memset(state, 0, sizeof(*state));
    state->allocator = engine->allocator;
    state->prefix = re_alloc(&state->allocator, prefix_size + 1u);
    if (state->prefix == NULL) {
        re_free(&engine->allocator, provider);
        re_free(&engine->allocator, state);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    memcpy(state->prefix, prefix, prefix_size);
    state->prefix[prefix_size] = '\0';
    state->prefix_size = prefix_size;
    if (options->operation_timeout_ms != 0u) {
        struct timeval timeout;
        timeout.tv_sec = (long)(options->operation_timeout_ms / 1000u);
        timeout.tv_usec = (long)(options->operation_timeout_ms % 1000u) * 1000L;
        state->connection = redisConnectWithTimeout(host, port, timeout);
    } else {
        state->connection = redisConnect(host, port);
    }
    if (state->connection == NULL || state->connection->err != 0) {
        /* No provider instance exists yet, so the failure surfaces only as a
         * status code (documented in the file header). */
        if (state->connection != NULL) redisFree(state->connection);
        re_free(&engine->allocator, state->prefix);
        re_free(&engine->allocator, provider);
        re_free(&engine->allocator, state);
        return RE_STATUS_ERROR;
    }
    if (database >= 0) {
        char db_text[24];
        redisReply *reply;
        snprintf(db_text, sizeof(db_text), "%ld", database);
        reply = redisCommand(state->connection, "SELECT %s", db_text);
        if (reply != NULL && reply->type == REDIS_REPLY_ERROR) {
            freeReplyObject(reply);
            reply = NULL;
        }
        if (reply == NULL) {
            redisFree(state->connection);
            re_free(&engine->allocator, state->prefix);
            re_free(&engine->allocator, provider);
            re_free(&engine->allocator, state);
            return RE_STATUS_ERROR;
        }
        freeReplyObject(reply);
    }
    memset(provider, 0, sizeof(*provider));
    provider->allocator = engine->allocator;
    provider->implementation = state;
    provider->descriptor = (re_state_provider_descriptor_t){
        sizeof(provider->descriptor), RE_STATE_PROVIDER_ABI_VERSION,
        redis_get, redis_set, redis_release, state, redis_put, redis_delete, redis_ttl};
    *out_provider = provider;
    return RE_STATUS_OK;
}

#else

/* Intentionally empty: without RE_HAS_HIREDIS this translation unit provides
 * no symbols and RE_STATE_PROVIDER_REDIS stays RE_STATUS_NOT_SUPPORTED. */

#endif
