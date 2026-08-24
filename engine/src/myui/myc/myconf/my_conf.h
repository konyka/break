/**
 * @file my_conf.h
 * @brief Configuration document tree (M17a): a typed tree of
 * NULL/BOOL/INT64/DOUBLE/STR/OBJECT/ARRAY nodes with dot-path queries
 * and JSON/BSON codecs.
 *
 * Conventions: every constructor takes a leading allocator (NULL =
 * default); nodes are owned by their parent (my_conf_destroy frees the
 * whole tree); OBJECT children keep insertion order; numeric scalars
 * are normalized to INT64/DOUBLE (BSON int32 reads become INT64).
 *
 * Dot paths: "a.b.0.c" — a segment selects an object key, or an array
 * index when the current node is an ARRAY (the segment must be all
 * digits then). Object keys containing dots are not reachable via
 * paths (documented limitation).
 */
#ifndef MY_CONF_H
#define MY_CONF_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#define MY_CONF_YAML_MAX_BYTES (4u * 1024u * 1024u)
#define MY_CONF_YAML_MAX_LINES 65536u
#define MY_CONF_YAML_MAX_DEPTH 256u
#define MY_CONF_YAML_MAX_CHILDREN 4096u
#define MY_CONF_YAML_MAX_SCALAR_BYTES (1024u * 1024u)

/** @brief Node type. */
typedef enum my_conf_type_t {
  MY_CONF_NULL = 0,
  MY_CONF_BOOL,
  MY_CONF_INT64,
  MY_CONF_DOUBLE,
  MY_CONF_STR,
  MY_CONF_OBJECT,
  MY_CONF_ARRAY
} my_conf_type_t;

/** @brief Parse/codec error with position (line/col 1-based in JSON;
 * offset is the byte offset, used by BSON). */
typedef struct my_conf_error_t {
  int32_t line;
  int32_t col;
  int64_t offset;
  char msg[96];
} my_conf_error_t;

/** @brief Document tree node (opaque). */
typedef struct my_conf_node_t my_conf_node_t;

/* ---------------- constructors ---------------- */

my_conf_node_t* my_conf_new_null(const my_allocator_t* allocator);
my_conf_node_t* my_conf_new_object(const my_allocator_t* allocator);
my_conf_node_t* my_conf_new_array(const my_allocator_t* allocator);
my_conf_node_t* my_conf_new_int64(const my_allocator_t* allocator, int64_t v);
my_conf_node_t* my_conf_new_double(const my_allocator_t* allocator, double v);
my_conf_node_t* my_conf_new_bool(const my_allocator_t* allocator, bool v);
my_conf_node_t* my_conf_new_str(const my_allocator_t* allocator,
                                const char* v);

/** @brief Destroy a node and its subtree (NULL safe). */
void my_conf_destroy(my_conf_node_t* node);

/* ---------------- structure ---------------- */

/**
 * @brief Set key -> child on an OBJECT node (on success takes over the
 * child; the child's key is set to a copy of key). An existing key is
 * replaced. Fails on non-object nodes (child NOT taken then).
 */
my_ret_t my_conf_object_set(my_conf_node_t* node, const char* key,
                            my_conf_node_t* child);

/** @brief Append child to an ARRAY node (takes over the child). */
my_ret_t my_conf_array_push(my_conf_node_t* node, my_conf_node_t* child);

/** @brief Child count (OBJECT/ARRAY; 0 for scalars). */
size_t my_conf_child_count(const my_conf_node_t* node);

/** @brief i-th child (borrowed; NULL out of range). */
my_conf_node_t* my_conf_child(const my_conf_node_t* node, size_t index);

/** @brief The node's key inside its parent object (NULL at the root /
 * in arrays). */
const char* my_conf_key(const my_conf_node_t* node);

/* ---------------- scalar access ---------------- */

my_conf_type_t my_conf_type(const my_conf_node_t* node);

/** @brief Node value with default on type mismatch (INT64 reads accept
 * DOUBLE by truncation is NOT done — strict types; BOOL/INT64 are
 * distinct). */
int64_t my_conf_as_int64(const my_conf_node_t* node, int64_t dflt);
double my_conf_as_double(const my_conf_node_t* node, double dflt);
bool my_conf_as_bool(const my_conf_node_t* node, bool dflt);
const char* my_conf_as_str(const my_conf_node_t* node, const char* dflt);

/* ---------------- dot-path queries ---------------- */

/** @brief Find by dot path ("a.b.0.c"); NULL when missing. */
my_conf_node_t* my_conf_get(my_conf_node_t* node, const char* path);

int64_t my_conf_get_int64(my_conf_node_t* node, const char* path,
                          int64_t dflt);
double my_conf_get_double(my_conf_node_t* node, const char* path,
                          double dflt);
bool my_conf_get_bool(my_conf_node_t* node, const char* path, bool dflt);
const char* my_conf_get_str(my_conf_node_t* node, const char* path,
                            const char* dflt);

/* ---------------- file io ---------------- */

/** @brief Load a JSON file into a tree (NULL on error; err may be
 * NULL). */
my_conf_node_t* my_conf_load_file(const my_allocator_t* allocator,
                                  const char* path, my_conf_error_t* err);

/** @brief Save as pretty JSON (2-space indent). */
my_ret_t my_conf_save_file(my_conf_node_t* node, const char* path);

/* ---------------- JSON ---------------- */

/** @brief Parse JSON (full RFC 8259 set). NULL on error (err filled
 * with line/col/msg when non-NULL). */
my_conf_node_t* my_conf_parse_json(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err);

/**
 * @brief Parse the TOML subset (M17b): key=value (basic ".." strings
 * with escapes, literal '..' strings, dec/0x/0o/0b integers with
 * underscores, floats incl. inf/nan, bools, datetimes kept as STR
 * verbatim), [table]/[a.b.c], [[table array]], inline tables, arrays
 * (mixed types allowed — BSON-style, documented), # comments.
 * Duplicate keys / table conflicts are errors. No writer (export via
 * JSON).
 */
my_conf_node_t* my_conf_parse_toml(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err);

/**
 * @brief Parse the YAML subset (M17b): indented blocks (key: value,
 * key: + nested block, - item lists incl. "- key: value" map items),
 * flow [a, b] / {k: v}, # comments, single/double-quoted strings,
 * plain scalars with type inference (null/~/true/false/int/float, else
 * STR). NOT supported (all hard errors): multi-document (---), anchors
 * (&), tags (!), folded scalars (> |), tab indentation; inconsistent
 * indentation is an error.
 */
my_conf_node_t* my_conf_parse_yaml(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err);

/** @brief Serialize to JSON (owned string). pretty: 2-space indent,
 * newlines; otherwise compact. */
char* my_conf_to_json_str(const my_allocator_t* allocator,
                          my_conf_node_t* node, bool pretty);

/* ---------------- BSON ---------------- */

/**
 * @brief Parse a BSON document (top level must be a document ->
 * OBJECT). Type mapping: 0x01 double, 0x02 utf8, 0x03 object, 0x04
 * array, 0x07 objectId (24 hex chars), 0x08 bool, 0x09 datetime
 * (INT64, milliseconds), 0x0A null, 0x10 int32 -> INT64, 0x12 int64.
 * Any other element type is an ERROR (data integrity over leniency).
 * Malformed lengths/truncation are safely rejected.
 */
my_conf_node_t* my_conf_parse_bson(const my_allocator_t* allocator,
                                   const uint8_t* data, size_t len,
                                   my_conf_error_t* err);

/** @brief Serialize to BSON (owned buffer; out_len set). INT64 values
 * in int32 range are written as 0x10, else 0x12. */
uint8_t* my_conf_to_bson(const my_allocator_t* allocator,
                         my_conf_node_t* node, size_t* out_len);

#endif /* MY_CONF_H */
