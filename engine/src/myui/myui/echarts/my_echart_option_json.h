/**
 * @file my_echart_option_json.h
 * @brief Owning parser for the supported ECharts JSON option subset.
 */
#ifndef MY_ECHART_OPTION_JSON_H
#define MY_ECHART_OPTION_JSON_H

#include "myui/echarts/my_echart_option.h"

typedef struct my_echart_json_doc_t my_echart_json_doc_t;

/** @brief Parse an ECharts option, returning NULL for malformed JSON. */
my_echart_json_doc_t* my_echart_json_doc_parse(const char* json, size_t len,
                                               const my_allocator_t* allocator);
/** @brief Borrow the owned option view. */
const my_echart_option_input_t* my_echart_json_doc_option(
    const my_echart_json_doc_t* doc);
/** @brief Return the semantic error, or NULL when parsing succeeded. */
const char* my_echart_json_doc_error(const my_echart_json_doc_t* doc);
/** @brief Destroy a document and all owned option storage (NULL safe). */
void my_echart_json_doc_destroy(my_echart_json_doc_t** doc);

#endif
