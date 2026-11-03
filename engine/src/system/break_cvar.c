#include <system/break_cvar.h>
#include <system/break_system_internal.h>

#include <platform/platform_fs.h>

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BREAK_CVAR_CONFIG_LINE_CAPACITY 256u

typedef struct BreakCVarEntry {
    bool used;
    bool seen_in_config;
    char name[BREAK_CVAR_NAME_CAPACITY];
    BreakCVarType type;
    u32 flags;
    BreakCVarValue value;
    char string[BREAK_CVAR_STRING_CAPACITY];
    i64 min_integer;
    i64 max_integer;
    f64 min_number;
    f64 max_number;
    BreakCVarChangedFn changed;
    void *changed_user;
} BreakCVarEntry;

struct BreakCVarRegistry {
    u32 capacity;
    u32 count;
    BreakCVarEntry *entries;
    BreakCVarEntry *scratch;
    char *config;
    bool notifying;
};

static bool cvar_name_valid(const char *name) {
    usize length;
    if (!name) return false;
    length = strlen(name);
    if (length == 0u || length >= BREAK_CVAR_NAME_CAPACITY) return false;
    if (!((name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z') || name[0] == '_')) return false;
    for (usize i = 1u; i < length; i++) {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '-'))
            return false;
    }
    return true;
}

static bool cvar_string_valid(const char *string, usize *out_length) {
    usize length;
    if (!string) return false;
    length = strlen(string);
    if (length >= BREAK_CVAR_STRING_CAPACITY ||
        !break_system_utf8_valid(string, length)) return false;
    for (usize i = 0u; i < length; i++) {
        u8 c = (u8)string[i];
        if (c < 0x20u || c == 0x7Fu) return false;
    }
    if (out_length) *out_length = length;
    return true;
}

static i32 cvar_find(const BreakCVarRegistry *registry, const char *name) {
    if (!registry || !cvar_name_valid(name)) return -1;
    for (u32 i = 0u; i < registry->capacity; i++) {
        if (registry->entries[i].used &&
            strcmp(registry->entries[i].name, name) == 0) return (i32)i;
    }
    return -1;
}

static bool cvar_values_equal(const BreakCVarEntry *a, const BreakCVarEntry *b) {
    switch (a->type) {
    case BREAK_CVAR_BOOL: return a->value.boolean == b->value.boolean;
    case BREAK_CVAR_INT: return a->value.integer == b->value.integer;
    case BREAK_CVAR_FLOAT: return a->value.number == b->value.number;
    case BREAK_CVAR_STRING: return strcmp(a->string, b->string) == 0;
    default: return false;
    }
}

static BreakCVarStatus cvar_validate_value(const BreakCVarEntry *entry,
                                           BreakCVarValue value) {
    switch (entry->type) {
    case BREAK_CVAR_BOOL:
        return BREAK_CVAR_OK;
    case BREAK_CVAR_INT:
        if (value.integer < entry->min_integer || value.integer > entry->max_integer)
            return BREAK_CVAR_OVERLOAD;
        return BREAK_CVAR_OK;
    case BREAK_CVAR_FLOAT:
        if (!isfinite(value.number)) return BREAK_CVAR_INVALID;
        if (value.number < entry->min_number || value.number > entry->max_number)
            return BREAK_CVAR_OVERLOAD;
        return BREAK_CVAR_OK;
    case BREAK_CVAR_STRING:
        return cvar_string_valid(value.string, NULL) ? BREAK_CVAR_OK : BREAK_CVAR_INVALID;
    default:
        return BREAK_CVAR_INVALID;
    }
}

static BreakCVarStatus cvar_apply(BreakCVarEntry *entry, BreakCVarValue value,
                                  bool allow_cheat, bool from_config) {
    BreakCVarStatus status;
    BreakCVarEntry candidate = *entry;
    if ((entry->flags & BREAK_CVAR_CHEAT) && !allow_cheat)
        return BREAK_CVAR_REJECTED;
    if (entry->flags & BREAK_CVAR_READONLY) {
        if (!from_config) return BREAK_CVAR_REJECTED;
        if (entry->type == BREAK_CVAR_STRING) {
            if (!value.string || strcmp(entry->string, value.string) != 0)
                return BREAK_CVAR_REJECTED;
        } else {
            candidate.value = value;
            if (!cvar_values_equal(entry, &candidate)) return BREAK_CVAR_REJECTED;
        }
        return BREAK_CVAR_OK;
    }
    status = cvar_validate_value(entry, value);
    if (status != BREAK_CVAR_OK) return status;
    if (entry->type == BREAK_CVAR_STRING) {
        size_t length = strlen(value.string);
        memcpy(entry->string, value.string, length + 1u);
        entry->value.string = entry->string;
    } else {
        entry->value = value;
    }
    return BREAK_CVAR_OK;
}

BreakCVarRegistry *break_cvar_create(u32 capacity) {
    BreakCVarRegistry *registry;
    if (capacity == 0u || capacity > BREAK_CVAR_HARD_MAX) return NULL;
    registry = (BreakCVarRegistry *)calloc(1u, sizeof(*registry));
    if (!registry) return NULL;
    registry->entries = (BreakCVarEntry *)calloc(capacity, sizeof(BreakCVarEntry));
    registry->scratch = (BreakCVarEntry *)calloc(capacity, sizeof(BreakCVarEntry));
    registry->config = (char *)malloc(BREAK_CVAR_CONFIG_MAX_BYTES + 1u);
    if (!registry->entries || !registry->scratch || !registry->config) {
        break_cvar_destroy(registry);
        return NULL;
    }
    registry->capacity = capacity;
    return registry;
}

void break_cvar_destroy(BreakCVarRegistry *registry) {
    if (!registry) return;
    free(registry->config);
    free(registry->scratch);
    free(registry->entries);
    free(registry);
}

BreakCVarStatus break_cvar_register(BreakCVarRegistry *registry,
                                    const BreakCVarDesc *desc) {
    BreakCVarEntry *entry;
    BreakCVarStatus status;
    if (!registry || !desc || registry->notifying || !cvar_name_valid(desc->name) ||
        desc->type < BREAK_CVAR_BOOL || desc->type > BREAK_CVAR_STRING ||
        (desc->flags & ~(BREAK_CVAR_READONLY | BREAK_CVAR_CHEAT)) != 0u)
        return BREAK_CVAR_INVALID;
    if (cvar_find(registry, desc->name) >= 0) return BREAK_CVAR_REJECTED;
    if (registry->count == registry->capacity) return BREAK_CVAR_OVERLOAD;
    entry = &registry->entries[registry->count];
    memset(entry, 0, sizeof(*entry));
    entry->type = desc->type;
    entry->flags = desc->flags;
    entry->min_integer = desc->min_integer;
    entry->max_integer = desc->max_integer;
    entry->min_number = desc->min_number;
    entry->max_number = desc->max_number;
    entry->changed = desc->changed;
    entry->changed_user = desc->changed_user;
    if (desc->type == BREAK_CVAR_INT && desc->min_integer > desc->max_integer)
        return BREAK_CVAR_INVALID;
    if (desc->type == BREAK_CVAR_FLOAT &&
        (!isfinite(desc->min_number) || !isfinite(desc->max_number) ||
         desc->min_number > desc->max_number)) return BREAK_CVAR_INVALID;
    status = cvar_validate_value(entry, desc->default_value);
    if (status != BREAK_CVAR_OK)
        return status == BREAK_CVAR_OVERLOAD ? BREAK_CVAR_INVALID : status;
    memcpy(entry->name, desc->name, strlen(desc->name) + 1u);
    entry->used = true;
    if (desc->type == BREAK_CVAR_STRING) {
        size_t length = strlen(desc->default_value.string);
        memcpy(entry->string, desc->default_value.string, length + 1u);
        entry->value.string = entry->string;
    } else {
        entry->value = desc->default_value;
    }
    registry->count++;
    return BREAK_CVAR_OK;
}

BreakCVarStatus break_cvar_get(const BreakCVarRegistry *registry,
                               const char *name, BreakCVarType type,
                               BreakCVarValue *out_value) {
    i32 index;
    const BreakCVarEntry *entry;
    if (!registry || !out_value || !cvar_name_valid(name)) return BREAK_CVAR_INVALID;
    index = cvar_find(registry, name);
    if (index < 0) return BREAK_CVAR_FAILED;
    entry = &registry->entries[index];
    if (entry->type != type) return BREAK_CVAR_INVALID;
    *out_value = entry->value;
    return BREAK_CVAR_OK;
}

BreakCVarStatus break_cvar_set(BreakCVarRegistry *registry, const char *name,
                               BreakCVarValue value, bool allow_cheat) {
    i32 index;
    BreakCVarEntry *entry;
    BreakCVarEntry old;
    BreakCVarStatus status;
    if (!registry || registry->notifying || !cvar_name_valid(name))
        return registry && registry->notifying ? BREAK_CVAR_REJECTED : BREAK_CVAR_INVALID;
    index = cvar_find(registry, name);
    if (index < 0) return BREAK_CVAR_FAILED;
    entry = &registry->entries[index];
    old = *entry;
    status = cvar_apply(entry, value, allow_cheat, false);
    if (status != BREAK_CVAR_OK) return status;
    if (!cvar_values_equal(&old, entry) && entry->changed) {
        registry->notifying = true;
        entry->changed(entry->name, entry->changed_user);
        registry->notifying = false;
    }
    return BREAK_CVAR_OK;
}

static char *cvar_trim(char *text) {
    char *end;
    while (*text == ' ' || *text == '\t' || *text == '\r' || *text == '\n') text++;
    end = text + strlen(text);
    while (end > text && (end[-1] == ' ' || end[-1] == '\t' ||
                          end[-1] == '\r' || end[-1] == '\n')) end--;
    *end = '\0';
    return text;
}

static BreakCVarStatus cvar_parse_line(BreakCVarRegistry *registry, char *line,
                                       bool allow_cheat) {
    char *equals = strchr(line, '=');
    char *name;
    char *text;
    BreakCVarValue value;
    BreakCVarEntry *entry;
    i32 index;
    BreakCVarStatus status;
    if (!equals) return BREAK_CVAR_INVALID;
    *equals = '\0';
    name = cvar_trim(line);
    text = cvar_trim(equals + 1);
    if (!cvar_name_valid(name)) return BREAK_CVAR_INVALID;
    index = cvar_find(registry, name);
    if (index < 0) return BREAK_CVAR_FAILED;
    entry = &registry->scratch[index];
    if (entry->seen_in_config) return BREAK_CVAR_INVALID;
    entry->seen_in_config = true;
    switch (entry->type) {
    case BREAK_CVAR_BOOL:
        if (strcmp(text, "true") == 0) value.boolean = true;
        else if (strcmp(text, "false") == 0) value.boolean = false;
        else return BREAK_CVAR_INVALID;
        break;
    case BREAK_CVAR_INT: {
        char *end = NULL;
        long long parsed;
        if (!text[0]) return BREAK_CVAR_INVALID;
        errno = 0;
        parsed = strtoll(text, &end, 10);
        if (errno == ERANGE || !end || *end != '\0') return BREAK_CVAR_INVALID;
        value.integer = (i64)parsed;
        break;
    }
    case BREAK_CVAR_FLOAT: {
        char *end = NULL;
        double parsed;
        if (!text[0]) return BREAK_CVAR_INVALID;
        errno = 0;
        parsed = strtod(text, &end);
        if (errno == ERANGE || !end || *end != '\0' || !isfinite(parsed))
            return BREAK_CVAR_INVALID;
        value.number = (f64)parsed;
        break;
    }
    case BREAK_CVAR_STRING:
        value.string = text;
        break;
    default:
        return BREAK_CVAR_INVALID;
    }
    status = cvar_apply(entry, value, allow_cheat, true);
    if (status != BREAK_CVAR_OK) entry->seen_in_config = false;
    return status;
}

BreakCVarStatus break_cvar_load(BreakCVarRegistry *registry, const char *path,
                                bool allow_cheat) {
    FILE *file;
    long length;
    usize size;
    usize offset = 0u;
    BreakCVarEntry *old;
    BreakCVarStatus status = BREAK_CVAR_OK;
    if (!registry || registry->notifying || !path || !path[0])
        return registry && registry->notifying ? BREAK_CVAR_REJECTED : BREAK_CVAR_INVALID;
    file = fopen(path, "rb");
    if (!file) return BREAK_CVAR_FAILED;
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return BREAK_CVAR_FAILED;
    }
    if ((u64)length > BREAK_CVAR_CONFIG_MAX_BYTES) {
        fclose(file);
        return BREAK_CVAR_OVERLOAD;
    }
    size = (usize)length;
    {
        bool read_ok = size == 0u || fread(registry->config, 1u, size, file) == size;
        if (ferror(file)) read_ok = false;
        if (fclose(file) != 0) read_ok = false;
        if (!read_ok) return BREAK_CVAR_FAILED;
    }
    if (memchr(registry->config, '\0', size)) return BREAK_CVAR_INVALID;
    registry->config[size] = '\0';
    memcpy(registry->scratch, registry->entries,
           registry->capacity * sizeof(BreakCVarEntry));
    for (u32 i = 0u; i < registry->capacity; i++) {
        registry->scratch[i].seen_in_config = false;
        if (registry->scratch[i].used && registry->scratch[i].type == BREAK_CVAR_STRING)
            registry->scratch[i].value.string = registry->scratch[i].string;
    }
    while (offset < size) {
        usize end = offset;
        char line[BREAK_CVAR_CONFIG_LINE_CAPACITY];
        usize line_length;
        char *content;
        while (end < size && registry->config[end] != '\n') end++;
        line_length = end - offset;
        if (line_length >= sizeof(line)) return BREAK_CVAR_INVALID;
        memcpy(line, registry->config + offset, line_length);
        line[line_length] = '\0';
        offset = end < size ? end + 1u : end;
        content = cvar_trim(line);
        if (!content[0] || content[0] == '#') continue;
        status = cvar_parse_line(registry, content, allow_cheat);
        if (status != BREAK_CVAR_OK) return status;
    }
    old = registry->scratch;
    registry->scratch = registry->entries;
    registry->entries = old;
    registry->notifying = true;
    for (u32 i = 0u; i < registry->capacity; i++) {
        BreakCVarEntry *entry = &registry->entries[i];
        if (entry->used && !cvar_values_equal(&registry->scratch[i], entry) && entry->changed)
            entry->changed(entry->name, entry->changed_user);
    }
    registry->notifying = false;
    return BREAK_CVAR_OK;
}

BreakCVarStatus break_cvar_save(const BreakCVarRegistry *registry,
                                const char *path) {
    PlatformAtomicWriter *writer;
    if (!registry || !path || !path[0]) return BREAK_CVAR_INVALID;
    writer = platform_atomic_writer_open(path);
    if (!writer) return BREAK_CVAR_FAILED;
    for (u32 i = 0u; i < registry->capacity; i++) {
        const BreakCVarEntry *entry = &registry->entries[i];
        char line[BREAK_CVAR_CONFIG_LINE_CAPACITY];
        int length = 0;
        if (!entry->used || (entry->flags & BREAK_CVAR_READONLY)) continue;
        switch (entry->type) {
        case BREAK_CVAR_BOOL:
            length = snprintf(line, sizeof(line), "%s=%s\n", entry->name,
                              entry->value.boolean ? "true" : "false");
            break;
        case BREAK_CVAR_INT:
            length = snprintf(line, sizeof(line), "%s=%lld\n", entry->name,
                              (long long)entry->value.integer);
            break;
        case BREAK_CVAR_FLOAT:
            length = snprintf(line, sizeof(line), "%s=%.17g\n", entry->name,
                              entry->value.number);
            break;
        case BREAK_CVAR_STRING:
            length = snprintf(line, sizeof(line), "%s=%s\n", entry->name, entry->string);
            break;
        default:
            platform_atomic_writer_abort(writer);
            return BREAK_CVAR_INVALID;
        }
        if (length < 0 || (usize)length >= sizeof(line) ||
            !platform_atomic_writer_write(writer, line, (usize)length)) {
            platform_atomic_writer_abort(writer);
            return BREAK_CVAR_FAILED;
        }
    }
    return platform_atomic_writer_commit(writer) ? BREAK_CVAR_OK : BREAK_CVAR_FAILED;
}
