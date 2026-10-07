/**
 * @file my_echart_option_json.h
 * @brief Owning parser for the supported ECharts JSON option subset.
 */
#ifndef MY_ECHART_OPTION_JSON_H
#define MY_ECHART_OPTION_JSON_H

#include "myui/echarts/my_echart_option.h"

typedef struct my_echart_json_doc_t my_echart_json_doc_t;

/** @brief Parse the supported ECharts subset, including title/xAxis/series,
 * annotations as series-level markPoint {data:[{coord:[categoryIndex,value],name}]},
 * markLine {data:[{yAxis,name,itemStyle:{color}}]}, markArea
 * {data:[{yAxisRange:[min,max],name,itemStyle:{color}}]}, and top-level
 * dataset {source:{dimension:[numeric,...]}}. Transforms are top-level
 * sort {config:{dimension,order:asc|desc}} or filter
 * {config:{dimension,op:eq|ne|gt|ge|lt|le,value}}. Grid descriptors accept
 * axisCount (1..3, default 2) and yAxis either as {min,max}, which sets the
 * range for axis 0, or as an array of up to axisCount entries. Array entries
 * are indexed by axis; an object containing both min and max sets an explicit
 * range, while null or an object missing either field leaves that axis
 * automatic. An array longer than axisCount and axisCount outside 1..3 are
 * semantic errors. */
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
