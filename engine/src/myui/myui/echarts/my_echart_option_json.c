#include "myui/echarts/my_echart_option_json.h"

#include "myc/myconf/my_conf.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_echart_json_doc_t {
  const my_allocator_t* allocator;
  my_conf_node_t* tree;
  my_echart_option_input_t option;
  char* title;
  char** x_axis;
  my_echart_series_input_t* series;
  size_t* series_counts;
  char** owned_strings;
  size_t owned_string_count;
  size_t owned_string_cap;
  double** data;
  size_t data_count;
  size_t data_cap;
  my_echart_grid_input_t* grids;
  size_t* grid_indices;
  size_t* grid_offsets;
  size_t grid_index_count;
  char error[160];
};

static void set_error(my_echart_json_doc_t* d, const char* msg) {
  if (d->error[0] == '\0') {
    (void)snprintf(d->error, sizeof(d->error), "%s", msg);
  }
}

static void* alloc0(my_echart_json_doc_t* d, size_t n, size_t sz) {
  return my_mem_calloc(d->allocator, n, sz);
}

static char* copy_string(my_echart_json_doc_t* d, const char* s) {
  size_t n;
  char* out;
  if (s == NULL) return NULL;
  n = strlen(s);
  out = (char*)alloc0(d, n + 1u, 1u);
  if (out == NULL) return NULL;
  memcpy(out, s, n + 1u);
  if (d->owned_string_count == d->owned_string_cap) {
    size_t cap = d->owned_string_cap == 0u ? 16u : d->owned_string_cap * 2u;
    char** p = (char**)my_mem_realloc(d->allocator, d->owned_strings,
                                      cap * sizeof(*p));
    if (p == NULL) { my_mem_free(d->allocator, out); return NULL; }
    d->owned_strings = p;
    d->owned_string_cap = cap;
  }
  d->owned_strings[d->owned_string_count++] = out;
  return out;
}

static my_conf_node_t* child(my_conf_node_t* n, size_t i) {
  return my_conf_child(n, i);
}

static bool number(my_conf_node_t* n, double* out) {
  if (n == NULL || out == NULL) return false;
  if (my_conf_type(n) == MY_CONF_INT64) *out = (double)my_conf_as_int64(n, 0);
  else if (my_conf_type(n) == MY_CONF_DOUBLE) *out = my_conf_as_double(n, 0.0);
  else return false;
  return isfinite(*out) != 0;
}

static bool size_number(my_conf_node_t* n, size_t* out) {
  double v;
  if (!number(n, &v) || v < 0.0 || floor(v) != v) return false;
  *out = (size_t)v;
  return (double)*out == v;
}

static bool color(my_echart_json_doc_t* d, my_conf_node_t* n, uint32_t* out) {
  const char* s;
  size_t i, len;
  uint32_t v = 0u;
  if (n == NULL) return false;
  if (my_conf_type(n) == MY_CONF_INT64 || my_conf_type(n) == MY_CONF_DOUBLE) {
    int64_t x = my_conf_as_int64(n, -1);
    if (my_conf_type(n) == MY_CONF_DOUBLE) {
      double dv = my_conf_as_double(n, -1.0);
      if (!isfinite(dv) || dv < 0.0 || floor(dv) != dv || dv > 4294967295.0) return false;
      *out = (uint32_t)dv; return true;
    }
    if (x < 0 || (uint64_t)x > 0xffffffffu) return false;
    *out = (uint32_t)x; return true;
  }
  if (my_conf_type(n) != MY_CONF_STR) return false;
  s = my_conf_as_str(n, NULL); len = s == NULL ? 0u : strlen(s);
  if (len != 7u && len != 9u) return false;
  if (s[0] != '#') return false;
  for (i = 1u; i < len; ++i) {
    int c = tolower((unsigned char)s[i]);
    if (c >= '0' && c <= '9') v = (v << 4u) | (uint32_t)(c - '0');
    else if (c >= 'a' && c <= 'f') v = (v << 4u) | (uint32_t)(c - 'a' + 10);
    else return false;
  }
  if (len == 7u) v = (v << 8u) | 0xffu;
  *out = v; (void)d; return true;
}

static bool type_of(const char* s, my_echart_series_type_t* out) {
  static const char* names[] = {"line","bar","scatter","pie","radar","funnel","heatmap","boxplot","candlestick","gauge","sankey","parallel","treemap","graph","calendar","themeriver"};
  size_t i, j;
  char buf[32];
  if (s == NULL || strlen(s) >= sizeof(buf)) return false;
  for (i = 0u; s[i] != '\0'; ++i) buf[i] = (char)tolower((unsigned char)s[i]);
  buf[i] = '\0';
  for (j = 0u; j < sizeof(names) / sizeof(names[0]); ++j) {
    if (strcmp(buf, names[j]) == 0) { *out = (my_echart_series_type_t)j; return true; }
  }
  return false;
}

static bool dimension(my_echart_json_doc_t* d, my_conf_node_t* n, double** out,
                      size_t* count) {
  size_t i, len;
  double* a;
  if (n == NULL || my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n); a = (double*)alloc0(d, len, sizeof(*a));
  if (len != 0u && a == NULL) return false;
  for (i = 0u; i < len; ++i) if (!number(child(n, i), &a[i])) return false;
  *out = a; *count = len;
  if (d->data_count == d->data_cap) {
    size_t cap = d->data_cap == 0u ? 8u : d->data_cap * 2u;
    double** p = (double**)my_mem_realloc(d->allocator, d->data, cap * sizeof(*p));
    if (p == NULL) return false;
    d->data = p;
    d->data_cap = cap;
  }
  d->data[d->data_count++] = a;
  return true;
}

static bool dimension_strings(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, len;
  if (n == NULL || my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n); d->x_axis = (char**)alloc0(d, len, sizeof(*d->x_axis));
  if (len != 0u && d->x_axis == NULL) return false;
  for (i = 0u; i < len; ++i) {
    const char* s = my_conf_as_str(child(n, i), NULL);
    d->x_axis[i] = copy_string(d, s);
    if (s == NULL || d->x_axis[i] == NULL) return false;
  }
  d->option.x_axis_data = (const char* const*)d->x_axis; d->option.x_axis_count = len;
  return true;
}

static bool parse_series(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, j, len, dl;
  if (n == NULL || my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n); d->series = (my_echart_series_input_t*)alloc0(d, len, sizeof(*d->series));
  if (len != 0u && d->series == NULL) return false;
  for (i = 0u; i < len; ++i) {
    my_conf_node_t* item = child(n, i); const char* s;
    char generated[32];
    if (my_conf_type(item) != MY_CONF_OBJECT) { set_error(d, "series item is not an object"); return false; }
    s = my_conf_get_str(item, "type", "line");
    if (!type_of(s, &d->series[i].type)) { set_error(d, "unknown series type"); return false; }
    d->series[i].name = copy_string(d, my_conf_get_str(item, "name", NULL));
    s = my_conf_get_str(item, "id", NULL); if (s == NULL) s = d->series[i].name;
    if (s == NULL) { (void)snprintf(generated, sizeof(generated), "s%u", (unsigned)i); s = generated; }
    d->series[i].id = copy_string(d, s);
    if (d->series[i].id == NULL) { set_error(d, "out of memory"); return false; }
    if (d->series[i].name == NULL) d->series[i].name = copy_string(d, s);
    d->series[i].show = my_conf_get_bool(item, "show", true);
    d->series[i].y_axis_index = (unsigned)my_conf_get_int64(item, "yAxisIndex", 0);
    d->series[i].stack = copy_string(d, my_conf_get_str(item, "stack", NULL));
    { double* values = NULL;
      if (!dimension(d, my_conf_get(item, "data"), &values, &dl)) { set_error(d, "invalid series data"); return false; }
      d->series[i].data = values; }
    d->series[i].data_count = dl;
    if (!color(d, my_conf_get(item, "color"), &d->series[i].color)) {
      my_conf_node_t* cn = my_conf_get(item, "itemStyle.color");
      d->series[i].color = 0u;
      if (cn != NULL && !color(d, cn, &d->series[i].color)) { set_error(d, "bad color string"); return false; }
    }
    for (j = 0u; j < dl; ++j) if (!isfinite(d->series[i].data[j])) { set_error(d, "non-finite data value"); return false; }
  }
  d->option.series = d->series; d->option.series_count = len; return true;
}

static bool grid_value(my_conf_node_t* n, double* out) {
  const char* s; size_t len; char* end; double v;
  if (number(n, out)) return true;
  s = my_conf_as_str(n, NULL); if (s == NULL) return false; len = strlen(s);
  if (len < 2u || s[len - 1u] != '%') return false;
  v = strtod(s, &end); if ((size_t)(end - s) != len - 1u || !isfinite(v)) return false;
  *out = v / 100.0; return true;
}

static bool parse_grids(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, j, len, ilen; my_conf_node_t* y;
  if (n == NULL) return true;
  if (my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n);
  d->grids = (my_echart_grid_input_t*)alloc0(d, len, sizeof(*d->grids));
  d->grid_offsets = (size_t*)alloc0(d, len, sizeof(*d->grid_offsets));
  if (len != 0u && (d->grids == NULL || d->grid_offsets == NULL)) return false;
  for (i = 0u; i < len; ++i) {
    my_conf_node_t* g = child(n, i); if (!grid_value(my_conf_get(g,"left"), &d->grids[i].left) || !grid_value(my_conf_get(g,"top"), &d->grids[i].top) || !grid_value(my_conf_get(g,"width"), &d->grids[i].width) || !grid_value(my_conf_get(g,"height"), &d->grids[i].height)) return false;
    my_conf_node_t* si = my_conf_get(g, "seriesIndices");
    if (si != NULL && my_conf_type(si) == MY_CONF_ARRAY) {
      size_t* indices;
      ilen = my_conf_child_count(si);
      d->grid_offsets[i] = d->grid_index_count;
      indices = (size_t*)my_mem_realloc(
          d->allocator, d->grid_indices,
          (d->grid_index_count + ilen) * sizeof(size_t));
      if (ilen != 0u && indices == NULL) return false;
      d->grid_indices = indices;
      for (j = 0u; j < ilen; ++j)
        if (!size_number(child(si, j), &d->grid_indices[d->grid_index_count + j]))
          return false;
      d->grid_index_count += ilen;
      d->grids[i].series_count = ilen;
    }
    y = my_conf_get(g, "yAxis"); if (y != NULL && number(my_conf_get(y,"min"), &d->grids[i].y_min) && number(my_conf_get(y,"max"), &d->grids[i].y_max)) d->grids[i].range_set=true;
  }
  for (i = 0u; i < len; ++i)
    if (d->grids[i].series_count > 0u)
      d->grids[i].series_indices = d->grid_indices + d->grid_offsets[i];
  d->option.grids=d->grids; d->option.grid_count=len; return true;
}

my_echart_json_doc_t* my_echart_json_doc_parse(const char* json, size_t len, const my_allocator_t* allocator) {
  my_echart_json_doc_t* d; my_conf_error_t err; my_conf_node_t* n; const char* s;
  d=(my_echart_json_doc_t*)my_mem_calloc(allocator,1u,sizeof(*d)); if(d==NULL) return NULL; d->allocator=allocator; d->tree=my_conf_parse_json(allocator,json,len,&err);
  if(d->tree==NULL){my_mem_free(allocator,d);return NULL;} n=d->tree;
  s=my_conf_get_str(n,"title.text",NULL); d->title=copy_string(d,s); d->option.title=d->title;
  if(!dimension_strings(d,my_conf_get(n,"xAxis.data")) && my_conf_get(n,"xAxis.data")!=NULL) set_error(d,"invalid xAxis data");
  if(!parse_series(d,my_conf_get(n,"series")) && d->error[0]=='\0') set_error(d,"invalid series");
  d->option.legend_hidden=!my_conf_get_bool(n,"legend.show",true); d->option.tooltip_hidden=!my_conf_get_bool(n,"tooltip.show",true);
  if(number(my_conf_get(n,"yAxis.min"),&d->option.y_min)&&number(my_conf_get(n,"yAxis.max"),&d->option.y_max)) d->option.range_set=true;
  if(size_number(my_conf_get(n,"dataZoom.0.startValue"),&d->option.zoom_start)&&size_number(my_conf_get(n,"dataZoom.0.endValue"),&d->option.zoom_end)) d->option.zoom_set=true;
  if(number(my_conf_get(n,"visualMap.min"),&d->option.visual_map_min)&&number(my_conf_get(n,"visualMap.max"),&d->option.visual_map_max)){my_conf_node_t* c=my_conf_get(n,"visualMap.inRange.color");if(c!=NULL&&my_conf_type(c)==MY_CONF_ARRAY&&my_conf_child_count(c)>=2u&&color(d,child(c,0),&d->option.visual_map_low_color)&&color(d,child(c,my_conf_child_count(c)-1u),&d->option.visual_map_high_color))d->option.visual_map_set=true;else if(c!=NULL)set_error(d,"bad color string");}
  if(!parse_grids(d,my_conf_get(n,"grid"))&&d->error[0]=='\0')set_error(d,"invalid grid");
  return d;
}

const my_echart_option_input_t* my_echart_json_doc_option(const my_echart_json_doc_t* doc){return doc==NULL?NULL:&doc->option;}
const char* my_echart_json_doc_error(const my_echart_json_doc_t* doc){return doc==NULL?NULL:(doc->error[0]=='\0'?NULL:doc->error);}
void my_echart_json_doc_destroy(my_echart_json_doc_t** doc) {
  size_t i;
  if (doc == NULL || *doc == NULL) return;
  for (i = 0u; i < (*doc)->data_count; ++i)
    my_mem_free((*doc)->allocator, (*doc)->data[i]);
  my_mem_free((*doc)->allocator, (*doc)->data);
  my_mem_free((*doc)->allocator, (*doc)->grid_indices);
  my_mem_free((*doc)->allocator, (*doc)->grid_offsets);
  for (i = 0u; i < (*doc)->owned_string_count; ++i)
    my_mem_free((*doc)->allocator, (*doc)->owned_strings[i]);
  my_mem_free((*doc)->allocator, (*doc)->owned_strings);
  my_mem_free((*doc)->allocator, (*doc)->x_axis);
  my_mem_free((*doc)->allocator, (*doc)->series);
  my_mem_free((*doc)->allocator, (*doc)->grids);
  my_conf_destroy((*doc)->tree);
  my_mem_free((*doc)->allocator, *doc);
  *doc = NULL;
}
