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
  my_echart_mark_point_input_t* mark_points;
  my_echart_mark_line_input_t* mark_lines;
  my_echart_mark_area_input_t* mark_areas;
  my_echart_dimension_input_t* dataset;
  char** encode_flat;
  size_t encode_flat_count;
  size_t encode_flat_cap;
  size_t* encode_offsets;
  size_t* encode_counts;
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
  if (n == NULL) return false;
  if (my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n); a = (double*)alloc0(d, len, sizeof(*a));
  if (len != 0u && a == NULL) return false;
  if (d->data_count == d->data_cap) {
    size_t cap = d->data_cap == 0u ? 8u : d->data_cap * 2u;
    double** p = (double**)my_mem_realloc(d->allocator, d->data,
                                          cap * sizeof(*p));
    if (p == NULL) { my_mem_free(d->allocator, a); return false; }
    d->data = p;
    d->data_cap = cap;
  }
  d->data[d->data_count++] = a;
  for (i = 0u; i < len; ++i) {
    if (!number(child(n, i), &a[i])) return false;
  }
  *out = a; *count = len;
  return true;
}

static bool dimension_strings(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, len;
  if (n == NULL) return true;
  if (my_conf_type(n) != MY_CONF_ARRAY) return false;
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

static bool parse_annotations(my_echart_json_doc_t* d, my_conf_node_t* series) {
  size_t i, j, len; my_conf_node_t *m, *a, *v; double x;
  if (series == NULL || my_conf_type(series) != MY_CONF_ARRAY) return true;
  for (i = 0u; i < my_conf_child_count(series); ++i) {
    m = my_conf_get(child(series, i), "markPoint.data");
    if (m != NULL) {
      if (my_conf_type(m) != MY_CONF_ARRAY) return false;
      len = my_conf_child_count(m);
      if (d->option.mark_point_count + len > MY_ECHART_MAX_MARK_POINTS) { set_error(d, "mark point capacity exceeded"); return false; }
      d->mark_points = (my_echart_mark_point_input_t*)my_mem_realloc(d->allocator, d->mark_points, (d->option.mark_point_count + len) * sizeof(*d->mark_points));
      if (len != 0u && d->mark_points == NULL) return false;
      for (j = 0u; j < len; ++j) {
        a = child(m, j); v = my_conf_get(a, "coord");
        if (v == NULL || my_conf_type(v) != MY_CONF_ARRAY || my_conf_child_count(v) != 2u || !size_number(child(v, 0u), &d->mark_points[d->option.mark_point_count].category_index)) { set_error(d, "invalid mark point coord"); return false; }
        d->mark_points[d->option.mark_point_count].series_index = i;
        d->mark_points[d->option.mark_point_count].label = copy_string(d, my_conf_get_str(a, "name", NULL)); d->option.mark_point_count++;
      }
    }
    m = my_conf_get(child(series, i), "markLine.data");
    if (m != NULL) {
      if (my_conf_type(m) != MY_CONF_ARRAY) return false;
      len = my_conf_child_count(m);
      if (d->option.mark_line_count + len > MY_ECHART_MAX_MARK_LINES) { set_error(d, "mark line capacity exceeded"); return false; }
      d->mark_lines = (my_echart_mark_line_input_t*)my_mem_realloc(d->allocator, d->mark_lines, (d->option.mark_line_count + len) * sizeof(*d->mark_lines)); if (len != 0u && d->mark_lines == NULL) return false;
      for (j = 0u; j < len; ++j) { a=child(m,j); if (!number(my_conf_get(a,"yAxis"), &x)) { set_error(d,"invalid mark line value"); return false; } d->mark_lines[d->option.mark_line_count].value=x; d->mark_lines[d->option.mark_line_count].label=copy_string(d,my_conf_get_str(a,"name",NULL)); d->mark_lines[d->option.mark_line_count].color=0u; v=my_conf_get(a,"itemStyle.color"); if(v!=NULL&&!color(d,v,&d->mark_lines[d->option.mark_line_count].color)){set_error(d,"bad color string");return false;} d->option.mark_line_count++; }
    }
    m = my_conf_get(child(series, i), "markArea.data");
    if (m != NULL) {
      if (my_conf_type(m) != MY_CONF_ARRAY) return false;
      len=my_conf_child_count(m);
      if (d->option.mark_area_count + len > MY_ECHART_MAX_MARK_AREAS) { set_error(d,"mark area capacity exceeded"); return false; }
      d->mark_areas=(my_echart_mark_area_input_t*)my_mem_realloc(d->allocator,d->mark_areas,(d->option.mark_area_count+len)*sizeof(*d->mark_areas)); if(len!=0u&&d->mark_areas==NULL)return false;
      for(j=0u;j<len;++j){a=child(m,j);v=my_conf_get(a,"yAxisRange");if(v==NULL||my_conf_type(v)!=MY_CONF_ARRAY||my_conf_child_count(v)!=2u||!number(child(v,0u),&d->mark_areas[d->option.mark_area_count].y_min)||!number(child(v,1u),&d->mark_areas[d->option.mark_area_count].y_max)){set_error(d,"invalid mark area range");return false;}d->mark_areas[d->option.mark_area_count].label=copy_string(d,my_conf_get_str(a,"name",NULL));d->mark_areas[d->option.mark_area_count].color=0u;v=my_conf_get(a,"itemStyle.color");if(v!=NULL&&!color(d,v,&d->mark_areas[d->option.mark_area_count].color)){set_error(d,"bad color string");return false;}d->option.mark_area_count++;}
    }
  }
  d->option.mark_points=d->mark_points; d->option.mark_lines=d->mark_lines; d->option.mark_areas=d->mark_areas; return true;
}

static bool parse_dataset(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, len; my_conf_node_t* v; double* vals;
  if(n==NULL)return true;
  n=my_conf_get(n,"source");
  if(n==NULL||my_conf_type(n)!=MY_CONF_OBJECT)return false;
  len=my_conf_child_count(n); d->dataset=(my_echart_dimension_input_t*)alloc0(d,len,sizeof(*d->dataset)); if(len!=0u&&d->dataset==NULL)return false;
  for(i=0u;i<len;++i){v=child(n,i);if(my_conf_key(v)==NULL||my_conf_key(v)[0]=='\0'||!dimension(d,v,&vals,&d->dataset[i].count)){set_error(d,"invalid dataset dimension");return false;}d->dataset[i].name=copy_string(d,my_conf_key(v));d->dataset[i].values=vals;}
  d->option.dataset=d->dataset; d->option.dataset_count=len; return true;
}

static bool parse_transform(my_echart_json_doc_t* d, my_conf_node_t* n) {
  const char* type; const char* order; const char* op;
  if(n==NULL)return true;
  type=my_conf_get_str(n,"type",NULL);
  d->option.transform_dimension=copy_string(d,my_conf_get_str(n,"config.dimension",NULL));
  if(type==NULL||d->option.transform_dimension==NULL||d->option.transform_dimension[0]=='\0'){set_error(d,"invalid transform");return false;}
  if(strcmp(type,"sort")==0){order=my_conf_get_str(n,"config.order","asc");if(strcmp(order,"desc")==0)d->option.transform=MY_ECHART_TRANSFORM_SORT_DESC;else if(strcmp(order,"asc")==0)d->option.transform=MY_ECHART_TRANSFORM_SORT_ASC;else{set_error(d,"invalid sort order");return false;}return true;}
  if(strcmp(type,"filter")!=0){set_error(d,"unknown transform type");return false;} op=my_conf_get_str(n,"config.op",NULL); if(op==NULL){set_error(d,"unknown filter op");return false;} if(strcmp(op,"eq")==0)d->option.filter_op=MY_ECHART_FILTER_EQ;else if(strcmp(op,"ne")==0)d->option.filter_op=MY_ECHART_FILTER_NE;else if(strcmp(op,"gt")==0)d->option.filter_op=MY_ECHART_FILTER_GT;else if(strcmp(op,"ge")==0)d->option.filter_op=MY_ECHART_FILTER_GE;else if(strcmp(op,"lt")==0)d->option.filter_op=MY_ECHART_FILTER_LT;else if(strcmp(op,"le")==0)d->option.filter_op=MY_ECHART_FILTER_LE;else{set_error(d,"unknown filter op");return false;} if(!number(my_conf_get(n,"config.value"),&d->option.filter_value)){set_error(d,"invalid filter value");return false;} d->option.transform=MY_ECHART_TRANSFORM_FILTER; d->option.filter_dimension=d->option.transform_dimension; return true;
}

static bool track_data(my_echart_json_doc_t* d, double* ptr) {
  if (d->data_count == d->data_cap) {
    size_t cap = d->data_cap == 0u ? 8u : d->data_cap * 2u;
    double** p = (double**)my_mem_realloc(d->allocator, d->data,
                                          cap * sizeof(*p));
    if (p == NULL) return false;
    d->data = p;
    d->data_cap = cap;
  }
  d->data[d->data_count++] = ptr;
  return true;
}

static bool resolve_encodes(my_echart_json_doc_t* d) {
  size_t i, j;
  if (d->encode_counts == NULL) return true;
  for (i = 0u; d->series != NULL && i < d->option.series_count; ++i) {
    size_t k = d->encode_counts[i];
    size_t dims[8];
    size_t rows;
    if (k == 0u) continue;
    if (d->dataset == NULL || d->option.dataset_count == 0u) {
      set_error(d, "dataset missing for encode");
      return false;
    }
    for (j = 0u; j < k; ++j) {
      size_t m;
      bool found = false;
      for (m = 0u; m < d->option.dataset_count; ++m) {
        if (strcmp(d->encode_flat[d->encode_offsets[i] + j],
                   d->dataset[m].name) == 0) {
          dims[j] = m;
          found = true;
          break;
        }
      }
      if (!found) { set_error(d, "encode dimension not found"); return false; }
    }
    rows = d->dataset[dims[0]].count;
    for (j = 0u; j < k; ++j) {
      if (d->dataset[dims[j]].count != rows) {
        set_error(d, "encode dimension count mismatch");
        return false;
      }
    }
    if (k == 1u) {
      d->series[i].data = d->dataset[dims[0]].values;
      d->series[i].data_count = rows;
    } else {
      double* out = (double*)alloc0(d, rows * k, sizeof(*out));
      if (out == NULL) { set_error(d, "out of memory"); return false; }
      if (!track_data(d, out)) { my_mem_free(d->allocator, out);
                                 set_error(d, "out of memory"); return false; }
      for (j = 0u; j < rows; ++j) {
        size_t e;
        for (e = 0u; e < k; ++e)
          out[j * k + e] = d->dataset[dims[e]].values[j];
      }
      d->series[i].data = out;
      d->series[i].data_count = rows * k;
    }
  }
  return true;
}

static bool parse_series(my_echart_json_doc_t* d, my_conf_node_t* n) {
  size_t i, j, len, dl;
  if (n == NULL) return true;
  if (my_conf_type(n) != MY_CONF_ARRAY) return false;
  len = my_conf_child_count(n); d->series = (my_echart_series_input_t*)alloc0(d, len, sizeof(*d->series));
  d->encode_offsets = (size_t*)alloc0(d, len, sizeof(*d->encode_offsets));
  d->encode_counts = (size_t*)alloc0(d, len, sizeof(*d->encode_counts));
  if (len != 0u && (d->series == NULL || d->encode_offsets == NULL ||
                    d->encode_counts == NULL))
    return false;
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
    d->series[i].label_show = my_conf_get_bool(item, "label.show", false);
    d->series[i].y_axis_index = (unsigned)my_conf_get_int64(item, "yAxisIndex", 0);
    d->series[i].stack = copy_string(d, my_conf_get_str(item, "stack", NULL));
    { double* values = NULL;
      const char* encode_dim = my_conf_get_str(item, "encode.y", NULL);
      my_conf_node_t* encode_node = my_conf_get(item, "encode.y");
      if (encode_node != NULL && my_conf_type(encode_node) != MY_CONF_ARRAY)
        encode_node = NULL;
      my_conf_node_t* data_node = my_conf_get(item, "data");
      if (data_node != NULL && (encode_dim != NULL || encode_node != NULL)) {
        set_error(d, "series data and encode are exclusive");
        return false;
      }
      if (data_node == NULL && encode_dim == NULL && encode_node == NULL) {
        set_error(d, "invalid series data");
        return false;
      }
      if (data_node != NULL &&
          !dimension(d, data_node, &values, &dl)) {
        set_error(d, "invalid series data");
        return false;
      }
      if (encode_dim != NULL || encode_node != NULL) {
        size_t k = 1u;
        d->encode_offsets[i] = d->encode_flat_count;
        if (encode_node != NULL) {
          k = my_conf_child_count(encode_node);
          if (k < 2u || k > 8u) { set_error(d, "invalid encode"); return false; }
        }
        if (d->encode_flat_count + k > d->encode_flat_cap) {
          size_t cap = d->encode_flat_cap == 0u ? 16u
                           : d->encode_flat_cap;
          char** p;
          while (cap < d->encode_flat_count + k) cap *= 2u;
          p = (char**)my_mem_realloc(d->allocator, d->encode_flat,
                                     cap * sizeof(*p));
          if (p == NULL) { set_error(d, "out of memory"); return false; }
          d->encode_flat = p;
          d->encode_flat_cap = cap;
        }
        if (encode_node != NULL) {
          for (size_t e = 0u; e < k; ++e) {
            const char* nm = my_conf_as_str(child(encode_node, e), NULL);
            if (nm == NULL || nm[0] == '\0') {
              set_error(d, "invalid encode");
              return false;
            }
            d->encode_flat[d->encode_flat_count + e] = copy_string(d, nm);
            if (d->encode_flat[d->encode_flat_count + e] == NULL) {
              set_error(d, "out of memory");
              return false;
            }
          }
        } else {
          d->encode_flat[d->encode_flat_count] = copy_string(d, encode_dim);
          if (d->encode_flat[d->encode_flat_count] == NULL) {
            set_error(d, "out of memory");
            return false;
          }
        }
        d->encode_flat_count += k;
        d->encode_counts[i] = k;
        values = NULL;
        dl = 0u;
      }
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
    d->grids[i].axis_count = 2u;
    {
      my_conf_node_t* axis_count = my_conf_get(g, "axisCount");
      size_t parsed_axis_count;
      if (axis_count != NULL) {
        if (!size_number(axis_count, &parsed_axis_count) || parsed_axis_count < 1u ||
            parsed_axis_count > MY_ECHART_MAX_AXES_PER_GRID) {
          set_error(d, "invalid grid axis count");
          return false;
        }
        d->grids[i].axis_count = parsed_axis_count;
      }
    }
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
    y = my_conf_get(g, "yAxis");
    if (y != NULL && my_conf_type(y) == MY_CONF_ARRAY) {
      ilen = my_conf_child_count(y);
      if (ilen > d->grids[i].axis_count || ilen > MY_ECHART_MAX_AXES_PER_GRID) {
        set_error(d, "too many grid axis ranges");
        return false;
      }
      for (j = 0u; j < ilen; ++j) {
        my_conf_node_t* range = child(y, j);
        double min_value, max_value;
        if (range != NULL && my_conf_type(range) == MY_CONF_OBJECT &&
            number(my_conf_get(range, "min"), &min_value) &&
            number(my_conf_get(range, "max"), &max_value)) {
          d->grids[i].axis_min[j] = min_value;
          d->grids[i].axis_max[j] = max_value;
          d->grids[i].axis_range_set[j] = true;
        }
      }
    } else if (y != NULL && number(my_conf_get(y,"min"), &d->grids[i].axis_min[0]) && number(my_conf_get(y,"max"), &d->grids[i].axis_max[0])) {
      d->grids[i].axis_range_set[0] = true;
    }
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
   if(!parse_annotations(d,my_conf_get(n,"series")) && d->error[0]=='\0') set_error(d,"invalid annotations");
   if(!parse_dataset(d,my_conf_get(n,"dataset")) && d->error[0]=='\0') set_error(d,"invalid dataset");
   if(d->error[0]=='\0' && !resolve_encodes(d) && d->error[0]=='\0') set_error(d,"invalid encode");
   (void)parse_transform(d,my_conf_get(n,"transform"));
  d->option.legend_hidden=!my_conf_get_bool(n,"legend.show",true); d->option.tooltip_hidden=!my_conf_get_bool(n,"tooltip.show",true);
  {
    my_conf_node_t* radar = my_conf_get(n, "radar.indicator");
    if (radar != NULL && my_conf_type(radar) == MY_CONF_ARRAY &&
        d->x_axis == NULL) {
      size_t k;
      d->option.x_axis_count = 0u;
      for (k = 0u; k < my_conf_child_count(radar); ++k) {
        const char* nm = my_conf_get_str(child(radar, k), "name", NULL);
        if (nm == NULL || nm[0] == '\0') {
          set_error(d, "invalid radar indicator");
          break;
        }
      }
      if (d->error[0] == '\0') {
        d->x_axis = (char**)alloc0(d, my_conf_child_count(radar),
                                   sizeof(*d->x_axis));
        if (d->x_axis == NULL) { set_error(d, "out of memory"); }
        else {
          for (k = 0u; k < my_conf_child_count(radar); ++k) {
            d->x_axis[k] = copy_string(
                d, my_conf_get_str(child(radar, k), "name", NULL));
            if (d->x_axis[k] == NULL) { set_error(d, "out of memory"); break; }
          }
          if (d->error[0] == '\0') {
            d->option.x_axis_data = (const char* const*)d->x_axis;
            d->option.x_axis_count = my_conf_child_count(radar);
          }
        }
      }
    }
    {
      my_conf_node_t* gauge_min = my_conf_get(n, "series.0.min");
      my_conf_node_t* gauge_max = my_conf_get(n, "series.0.max");
      if (gauge_min != NULL && gauge_max != NULL &&
          number(gauge_min, &d->option.y_min) &&
          number(gauge_max, &d->option.y_max))
        d->option.range_set = true;
    }
    {
      my_conf_node_t* palette = my_conf_get(n, "color");
      size_t k;
      if (palette != NULL && my_conf_type(palette) == MY_CONF_ARRAY &&
          my_conf_child_count(palette) > 0u) {
        for (k = 0u; k < d->option.series_count; ++k) {
          my_conf_node_t* pick =
              child(palette, k % my_conf_child_count(palette));
          if (d->series[k].color == 0u && !color(d, pick, &d->series[k].color))
            { set_error(d, "bad color string"); break; }
        }
      }
    }
  }
   if(number(my_conf_get(n,"yAxis.min"),&d->option.y_min)&&number(my_conf_get(n,"yAxis.max"),&d->option.y_max)) d->option.range_set=true;
   if (my_conf_get(n, "visualMap.inRange.color") != NULL && d->error[0] == '\0') {
     my_conf_node_t* c = my_conf_get(n, "visualMap.inRange.color");
     if (my_conf_type(c) != MY_CONF_ARRAY || my_conf_child_count(c) < 2u || !color(d, child(c, 0u), &d->option.visual_map_low_color) || !color(d, child(c, my_conf_child_count(c) - 1u), &d->option.visual_map_high_color)) set_error(d, "bad color string");
   }
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
   my_mem_free((*doc)->allocator, (*doc)->mark_points);
   my_mem_free((*doc)->allocator, (*doc)->mark_lines);
   my_mem_free((*doc)->allocator, (*doc)->mark_areas);
   my_mem_free((*doc)->allocator, (*doc)->dataset);
  my_mem_free((*doc)->allocator, (*doc)->encode_flat);
  my_mem_free((*doc)->allocator, (*doc)->encode_offsets);
  my_mem_free((*doc)->allocator, (*doc)->encode_counts);
  my_mem_free((*doc)->allocator, (*doc)->grids);
  my_conf_destroy((*doc)->tree);
  my_mem_free((*doc)->allocator, *doc);
  *doc = NULL;
}
