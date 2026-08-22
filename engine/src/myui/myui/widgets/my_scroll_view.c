/**
 * @file my_scroll_view.c
 * @brief Generic vertical scroll container implementation (M14a).
 */
#include "myui/widgets/my_scroll_view.h"

#include "myui/my_layout.h"
#include "myui/widgets/my_scroll_bar.h"

#define SV_WHEEL_STEP (24 * 3) /**< px per wheel row unit */

struct my_scroll_view_t {
  my_widget_t base;
  my_widget_t* content;    /**< weak (the tree owns it) */
  my_widget_t* scroll_bar; /**< weak, external sibling */
  int32_t offset;
  int32_t content_h;       /**< explicit height, 0 = auto */
};

static int32_t sv_content_height(my_scroll_view_t* sv) {
  int32_t m;
  if (sv->content_h > 0) {
    return sv->content_h;
  }
  if (sv->content == NULL) {
    return 0;
  }
  m = my_layouter_flow_measure(sv->content); /* 0 when not flow-laid */
  return m > 0 ? m : sv->content->rect.h;
}

static int32_t sv_max_offset(my_scroll_view_t* sv) {
  int32_t max = sv_content_height(sv) - ((my_widget_t*)sv)->rect.h;
  return max > 0 ? max : 0;
}

/** @brief Push value/page_size into the linked bar (no "changed" echo:
 * the public setters never notify). */
static void sv_sync_bar(my_scroll_view_t* sv) {
  int32_t ch, max;
  if (sv->scroll_bar == NULL) {
    return;
  }
  ch = sv_content_height(sv);
  max = sv_max_offset(sv);
  my_scroll_bar_set_page_size(
      sv->scroll_bar,
      ch > 0 ? (float)((my_widget_t*)sv)->rect.h / (float)ch : 1.0f);
  my_scroll_bar_set_value(sv->scroll_bar,
                          max > 0 ? (float)sv->offset / (float)max : 0.0f);
}

/** @brief Position the content child: full width, y = -offset. */
static void sv_layout_content(my_scroll_view_t* sv) {
  my_widget_t* w = (my_widget_t*)sv;
  if (sv->content == NULL) {
    return;
  }
  (void)my_widget_set_layout_rect(
      sv->content,
      &(my_rect_t){0, -sv->offset, w->rect.w, sv_content_height(sv)});
  my_widget_invalidate(w, NULL);
}

void my_scroll_view_set_offset(my_scroll_view_t* sv, int32_t offset) {
  int32_t max;
  if (sv == NULL) {
    return;
  }
  max = sv_max_offset(sv);
  if (offset < 0) {
    offset = 0;
  }
  if (offset > max) {
    offset = max;
  }
  if (offset != sv->offset) {
    sv->offset = offset;
    sv_layout_content(sv);
    sv_sync_bar(sv);
  }
}

int32_t my_scroll_view_get_offset(my_scroll_view_t* sv) {
  return sv != NULL ? sv->offset : 0;
}

void my_scroll_view_set_content_height(my_scroll_view_t* sv, int32_t height) {
  if (sv == NULL) {
    return;
  }
  sv->content_h = height > 0 ? height : 0;
  my_scroll_view_set_offset(sv, sv->offset); /* re-clamp */
  sv_layout_content(sv);
  sv_sync_bar(sv);
}

static my_ret_t sv_on_event(my_widget_t* widget, const my_event_t* event) {
  my_scroll_view_t* sv = (my_scroll_view_t*)widget;
  if (event->type == MY_EVENT_POINTER_WHEEL) {
    int32_t before = sv->offset;
    my_scroll_view_set_offset(sv,
                              sv->offset - event->u.pointer.delta * SV_WHEEL_STEP);
    /* nested scrolling (M16): only eat the wheel when we actually scrolled;
     * at the limit (or no overflow) let it bubble to an outer scroll view */
    return sv->offset != before ? MY_RET_OK : MY_RET_FAIL;
  }
  return MY_RET_FAIL;
}

/** @brief M24c: measurement-phase duties — re-clamp the offset after a
 * resize and sync the linked bar. Runs before the layouter (relayout). */
static void sv_on_measure(my_widget_t* widget) {
  my_scroll_view_t* sv = (my_scroll_view_t*)widget;
  my_scroll_view_set_offset(sv, sv->offset); /* re-clamp after resize */
  sv_sync_bar(sv);
}

/** @brief Layout-phase duty: position the content child. */
static void sv_on_layout(my_widget_t* widget) {
  sv_layout_content((my_scroll_view_t*)widget);
}

static const my_widget_vtable_t s_sv_vtable = {NULL, sv_on_event, sv_on_layout,
                                               sv_on_measure};

my_scroll_view_t* my_scroll_view_create(const my_allocator_t* allocator) {
  my_scroll_view_t* sv =
      (my_scroll_view_t*)my_mem_calloc(allocator, 1, sizeof(my_scroll_view_t));
  if (sv == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)sv, allocator, &s_sv_vtable,
                     "scroll_view") != MY_RET_OK) {
    my_mem_free(allocator, sv);
    return NULL;
  }
  return sv;
}

my_ret_t my_scroll_view_set_content(my_scroll_view_t* sv,
                                    my_widget_t* content) {
  my_widget_t* w = (my_widget_t*)sv;
  my_ret_t ret;
  if (sv == NULL || content == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (sv->content != NULL) {
    my_widget_remove_child(w, sv->content);
    sv->content = NULL;
  }
  ret = my_widget_add_child(w, content);
  if (ret != MY_RET_OK) {
    return ret;
  }
  sv->content = content;
  sv->offset = 0;
  sv_layout_content(sv);
  sv_sync_bar(sv);
  return MY_RET_OK;
}

my_widget_t* my_scroll_view_get_content(my_scroll_view_t* sv) {
  return sv != NULL ? sv->content : NULL;
}

my_widget_t* my_scroll_view_widget(my_scroll_view_t* sv) {
  return (my_widget_t*)sv; /* IS-A widget; NULL-safe like any cast */
}

/** @brief scroll_bar "changed" -> offset. */
static void sv_on_bar_changed(void* ctx, const char* event, void* data) {
  my_scroll_view_t* sv = (my_scroll_view_t*)ctx;
  int32_t max;
  (void)event;
  (void)data;
  max = sv_max_offset(sv);
  my_scroll_view_set_offset(
      sv, (int32_t)(my_scroll_bar_get_value(sv->scroll_bar) * (float)max));
}

my_ret_t my_scroll_view_set_scroll_bar(my_scroll_view_t* sv,
                                       my_widget_t* bar) {
  if (sv == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  sv->scroll_bar = bar;
  if (bar != NULL) {
    my_widget_on(bar, "changed", sv_on_bar_changed, sv);
    sv_sync_bar(sv);
  }
  return MY_RET_OK;
}
