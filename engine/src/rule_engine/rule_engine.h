/**
 * @file rule_engine.h
 * @brief Minimal C99 public ABI for the rule engine.
 *
 * This header defines the boundary for the next TDD phase only. It does not
 * promise a parser, RETE implementation, streaming runtime, or any behavior
 * not covered by the conformance manifests and future tests.
 */
#ifndef BREAK_RULE_ENGINE_H
#define BREAK_RULE_ENGINE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct re_engine_t re_engine_t;
typedef struct re_facts_t re_facts_t;
typedef struct re_program_t re_program_t;

typedef enum re_status_t {
  RE_STATUS_OK = 0,
  RE_STATUS_ERROR = -1,
  RE_STATUS_OUT_OF_MEMORY = -2,
  RE_STATUS_INVALID_ARGUMENT = -3,
  RE_STATUS_NOT_FOUND = -4,
  RE_STATUS_NOT_SUPPORTED = -5,
  RE_STATUS_PARSE_ERROR = -6,
  RE_STATUS_LIMIT = -7,
  RE_STATUS_CANCELLED = -8,
  RE_STATUS_BUSY = -9
} re_status_t;

typedef enum re_value_type_t {
  RE_VALUE_NONE = 0,
  RE_VALUE_BOOL,
  RE_VALUE_INT64,
  RE_VALUE_DOUBLE,
  RE_VALUE_STRING
} re_value_type_t;

typedef uint32_t re_capabilities_t;

#define RE_CAP_CORE_GRL           ((re_capabilities_t)1u << 0)
#define RE_CAP_FACTS              ((re_capabilities_t)1u << 1)
#define RE_CAP_FORWARD_EXECUTION  ((re_capabilities_t)1u << 2)

typedef struct re_string_t {
  const char *data;
  size_t size;
} re_string_t;

typedef struct re_value_t {
  re_value_type_t type;
  union re_value_payload_t {
    int boolean;
    int64_t int64_value;
    double double_value;
    re_string_t string;
  } as;
} re_value_t;

typedef void *(*re_alloc_fn_t)(void *context, size_t size);
typedef void *(*re_realloc_fn_t)(void *context, void *memory, size_t size);
typedef void (*re_free_fn_t)(void *context, void *memory);

typedef struct re_allocator_t {
  void *context;
  re_alloc_fn_t alloc;
  re_realloc_fn_t realloc;
  re_free_fn_t free;
} re_allocator_t;

typedef struct re_limits_t {
  size_t max_source_bytes;
  size_t max_rules;
  size_t max_facts;
  size_t max_agenda_activations;
  size_t max_firings;
} re_limits_t;

typedef int (*re_cancel_fn_t)(void *context);

typedef struct re_run_options_t {
  const re_limits_t *limits;
  re_cancel_fn_t is_cancelled;
  void *cancel_context;
} re_run_options_t;

typedef struct re_rule_event_t {
  re_string_t rule_name;
  int32_t salience;
  uint64_t activation_sequence;
} re_rule_event_t;

typedef re_status_t (*re_action_fn_t)(re_engine_t *engine,
                                      re_facts_t *facts,
                                      const re_rule_event_t *event,
                                      void *context);

typedef struct re_callbacks_t {
  re_action_fn_t action;
  void *context;
} re_callbacks_t;

/* The returned engine owns a copy of config and remains valid until destroy. */
re_engine_t *re_engine_create(const re_allocator_t *allocator,
                              const re_limits_t *limits);
/* Destroys engine and any program owned by it. NULL is accepted. */
void re_engine_destroy(re_engine_t *engine);
/* Returns locally implemented capabilities; zero is valid for NULL. */
re_capabilities_t re_engine_capabilities(const re_engine_t *engine);

/* Creates an empty fact set owned by the caller; destroy it exactly once. */
re_facts_t *re_facts_create(const re_allocator_t *allocator,
                            const re_limits_t *limits);
/* Releases facts and all copied names/values. NULL is accepted. */
void re_facts_destroy(re_facts_t *facts);
/* Copies name and value into facts; caller retains ownership of both inputs. */
re_status_t re_facts_set(re_facts_t *facts, re_string_t name,
                         const re_value_t *value);
/* Copies the fact into out_value; string data is borrowed until next mutation. */
re_status_t re_facts_get(const re_facts_t *facts, re_string_t name,
                         re_value_t *out_value);

/*
 * Parses source into a candidate program. The candidate owns a copy of source
 * and is independent of source and engine. Destroy it with re_program_destroy.
 */
re_status_t re_program_load(const re_allocator_t *allocator,
                            re_string_t source, const re_limits_t *limits,
                            re_program_t **out_program);
/* Releases a candidate program. NULL is accepted. */
void re_program_destroy(re_program_t *program);
/* Atomically installs program; on failure engine and program remain unchanged. */
re_status_t re_engine_install(re_engine_t *engine, re_program_t *program);

/*
 * Runs the installed program against facts. Matching then assignments are
 * applied before the optional callback, which is also invoked for each firing.
 * Run-option limit fields use the engine defaults when zero; a non-zero limit
 * permits exactly that many activations or firings before the next one returns
 * RE_STATUS_LIMIT.
 */
re_status_t re_engine_run(re_engine_t *engine, re_facts_t *facts,
                          const re_run_options_t *options,
                          const re_callbacks_t *callbacks);

#ifdef __cplusplus
}
#endif

#endif /* BREAK_RULE_ENGINE_H */
