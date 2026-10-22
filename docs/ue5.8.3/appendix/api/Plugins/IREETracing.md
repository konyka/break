# Plugins / IREETracing

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/IREETracing`
- headers: 1; symbols: 34
- symbol kinds: macro=26, prototype=7, typedef=1
- PublicDependencyModuleNames: Core, Engine, TraceLog

### `Plugins/Experimental/NNERuntimeIREE/Source/IREETracing/Internal/IREETracing.h` (Internal)


#### Free symbols / members of external scopes

- L7 _macro_ `#define IREETRACING_API`
- L8 _macro_ `#define OUTSIDE_UE`
- L12 _macro_ `#define IREE_TRACING_FEATURES (IREE_TRACING_FEATURES_REQUESTED & 1)`
- L23 _prototype_ `void iree_tracing_set_thread_name(const char* name);`
- L25 _prototype_ `uint32_t iree_tracing_zone_begin(const char* name, const char* file, uint32_t line);`
- L26 _prototype_ `uint32_t iree_tracing_zone_begin_dynamic(const char* name, size_t name_length, const char* file, uint32_t line);`
- L27 _prototype_ `uint32_t iree_tracing_zone_begin_external(const char* file_name, size_t file_name_length, uint32_t line, const char* function_name, size_t function_name_length, const char* name, size_t name_length);`
- L28 _prototype_ `void iree_tracing_zone_end(uint32_t zone_id);`
- L30 _prototype_ `void iree_tracing_publish_source_file(const void* filename, size_t filename_length, const void* content, size_t content_length);`
- L31 _prototype_ `void iree_tracing_zone_append_text_string_view(uint32_t zone_id, const char* txt, size_t size);`
- L44 _typedef_ `typedef uint32_t iree_zone_id_t;`
- L46 _macro_ `#define IREE_TRACE(expr) expr`
- L48 _macro_ `#define IREE_TRACE_SET_THREAD_NAME(name) \`
- L51 _macro_ `#define IREE_TRACE_ZONE_BEGIN(zone_id) \`
- L54 _macro_ `#define IREE_TRACE_ZONE_BEGIN_NAMED(zone_id, name) \`
- L57 _macro_ `#define IREE_TRACE_ZONE_BEGIN_NAMED_DYNAMIC(zone_id, name, name_length) \`
- L60 _macro_ `#define IREE_TRACE_ZONE_BEGIN_EXTERNAL(zone_id, file_name, file_name_length, line, function_name, function_name_length, name, name_length) \`
- L63 _macro_ `#define IREE_TRACE_ZONE_END(zone_id) \`
- L66 _macro_ `#define IREE_RETURN_AND_END_ZONE_IF_ERROR(zone_id, ...) \`
- L71 _macro_ `#define IREE_TRACE_PUBLISH_SOURCE_FILE(filename, filename_length, content, content_length) \` — Unimplemented
- L73 _macro_ `#define IREE_TRACE_ZONE_APPEND_TEXT(...) \`
- L75 _macro_ `#define IREE_TRACE_ZONE_APPEND_TEXT_CSTRING(zone_id, value) \`
- L77 _macro_ `#define IREE_TRACE_ZONE_APPEND_TEXT_STRING_VIEW(zone_id, value, value_length) \`
- L79 _macro_ `#define IREE_TRACE_ZONE_APPEND_VALUE_I64(zone_id, value)`
- L80 _macro_ `#define IREE_TRACE_ZONE_SET_COLOR(zone_id, color_xbgr)`
- L81 _macro_ `#define IREE_TRACE_MESSAGE(level, value_literal)`
- L82 _macro_ `#define IREE_TRACE_FIBER_ENTER(fiber)`
- L83 _macro_ `#define IREE_TRACE_FIBER_LEAVE()`
- L84 _macro_ `#define IREE_TRACE_SET_PLOT_TYPE(name_literal, plot_type, step, fill, color)`
- L85 _macro_ `#define IREE_TRACE_PLOT_VALUE_I64(name_literal, value)`
- L86 _macro_ `#define IREE_TRACE_PLOT_VALUE_F32(name_literal, value)`
- L87 _macro_ `#define IREE_TRACE_PLOT_VALUE_F64(name_literal, value)`
- L90 _macro_ `#define IREE_TRACE_IMPL_GET_VARIADIC_HELPER_(_1, _2, _3, NAME, ...) NAME` — Utilities:
- L91 _macro_ `#define IREE_TRACE_IMPL_GET_VARIADIC_(args) \`
