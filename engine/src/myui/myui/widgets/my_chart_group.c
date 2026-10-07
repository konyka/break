/**
 * @file my_chart_group.c
 * @brief Fixed-capacity weak registry for linked chart dataZoom state.
 */
#include "myui/widgets/my_chart.h"

typedef struct my_chart_group_t {
  unsigned id;
  my_widget_t* charts[MY_CHART_GROUP_MAX_CHARTS];
  size_t count;
} my_chart_group_t;

static my_chart_group_t s_groups[MY_CHART_GROUP_MAX_GROUPS];
static size_t s_notify_depth;

static my_chart_group_t* chart_group_find(unsigned id) {
  size_t i;

  for (i = 0u; i < MY_CHART_GROUP_MAX_GROUPS; i++) {
    if (s_groups[i].count > 0u && s_groups[i].id == id) return &s_groups[i];
  }
  return NULL;
}

static my_chart_group_t* chart_group_empty(void) {
  size_t i;

  for (i = 0u; i < MY_CHART_GROUP_MAX_GROUPS; i++) {
    if (s_groups[i].count == 0u) return &s_groups[i];
  }
  return NULL;
}

static my_chart_group_t* chart_group_for_chart(const my_widget_t* chart,
                                                size_t* chart_index) {
  size_t group_index;
  size_t member_index;

  for (group_index = 0u; group_index < MY_CHART_GROUP_MAX_GROUPS;
       group_index++) {
    for (member_index = 0u; member_index < s_groups[group_index].count;
         member_index++) {
      if (s_groups[group_index].charts[member_index] == chart) {
        if (chart_index != NULL) *chart_index = member_index;
        return &s_groups[group_index];
      }
    }
  }
  return NULL;
}

my_ret_t my_chart_group_join(my_widget_t* chart, unsigned group_id) {
  my_chart_group_t* old_group;
  my_chart_group_t* new_group;

  if (chart == NULL || !my_chart_is_instance(chart))
    return MY_RET_INVALID_PARAMS;
  old_group = chart_group_for_chart(chart, NULL);
  new_group = chart_group_find(group_id);
  if (old_group != NULL && old_group == new_group) return MY_RET_OK;
  if (new_group != NULL && new_group->count == MY_CHART_GROUP_MAX_CHARTS)
    return MY_RET_FAIL;
  if (new_group == NULL && chart_group_empty() == NULL) return MY_RET_FAIL;
  if (old_group != NULL) my_chart_group_leave(chart);
  if (new_group == NULL) {
    new_group = chart_group_empty();
    new_group->id = group_id;
  }
  new_group->charts[new_group->count++] = chart;
  return MY_RET_OK;
}

my_ret_t my_chart_group_leave(my_widget_t* chart) {
  my_chart_group_t* group;
  size_t chart_index;

  if (chart == NULL || !my_chart_is_instance(chart))
    return MY_RET_INVALID_PARAMS;
  group = chart_group_for_chart(chart, &chart_index);
  if (group == NULL) return MY_RET_OK;
  group->count--;
  group->charts[chart_index] = group->charts[group->count];
  group->charts[group->count] = NULL;
  if (group->count == 0u) group->id = 0u;
  return MY_RET_OK;
}

size_t my_chart_group_size(unsigned group_id) {
  my_chart_group_t* group = chart_group_find(group_id);

  return group != NULL ? group->count : 0u;
}

void my_chart_group_notify(my_widget_t* chart, size_t start, size_t end) {
  my_chart_group_t* group;
  size_t i;

  if (chart == NULL || s_notify_depth > 0u) return;
  group = chart_group_for_chart(chart, NULL);
  if (group == NULL) return;
  s_notify_depth++;
  for (i = 0u; i < group->count; i++) {
    if (group->charts[i] != chart)
      my_chart_set_data_zoom(group->charts[i], start, end);
  }
  s_notify_depth--;
}

void my_chart_group_clear_notify(my_widget_t* chart) {
  my_chart_group_t* group;
  size_t i;

  if (chart == NULL || s_notify_depth > 0u) return;
  group = chart_group_for_chart(chart, NULL);
  if (group == NULL) return;
  s_notify_depth++;
  for (i = 0u; i < group->count; i++) {
    my_chart_t* peer;
    if (group->charts[i] == chart) continue;
    peer = (my_chart_t*)group->charts[i];
    (void)my_chart_clear_data_zoom((my_widget_t*)peer);
  }
  s_notify_depth--;
}
