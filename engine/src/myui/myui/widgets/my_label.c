/**
 * @file my_label.c
 * @brief Minimal label widget.
 */
#include "myui/widgets/my_label.h"

#include "myc/my_str.h"

static void label_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_label_t* label = (my_label_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          my_color_to_rgba32(label->bg));
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                          my_color_to_rgba32(label->fg));
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  if (label->text != NULL) {
    int32_t tw = 0, th = 0;
    int32_t font_size =
        my_widget_style_get_int(widget, MY_STATE_NORMAL, MY_STYLE_FONT_SIZE, 16);
    float tx = 0.0f;
    my_vgcanvas_set_font(vg, NULL, font_size);
    if (my_vgcanvas_measure_text(vg, label->text, &tw, &th) == MY_RET_OK) {
      /* real text rendering (M7a): vertical center + align (M11d) */
      switch (label->align) {
        case MY_TEXT_ALIGN_CENTER:
          tx = ((float)widget->rect.w - (float)tw) / 2.0f;
          break;
        case MY_TEXT_ALIGN_RIGHT:
          tx = (float)widget->rect.w - (float)tw;
          break;
        default: /* LEFT; JUSTIFY = LEFT for a single-line label */
          tx = 0.0f;
          break;
      }
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
      my_vgcanvas_draw_text(vg, label->text, tx,
                            ((float)widget->rect.h - (float)th) / 2.0f);
    } else {
      /* no font on the backend: centered placeholder bar */
      float bar_w = (float)widget->rect.w * 0.6f;
      float bar_h = 4.0f;
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
      my_vgcanvas_fill_rect(vg,
                            &(my_rectf_t){((float)widget->rect.w - bar_w) / 2.0f,
                                          ((float)widget->rect.h - bar_h) / 2.0f,
                                          bar_w, bar_h});
      my_vgcanvas_draw_text(vg, label->text, 0, 0); /* NOT_SUPPORTED for now */
    }
  }
}

static const my_widget_vtable_t s_label_vtable = {label_on_paint, NULL, NULL, NULL};

static void label_destroy_chain(my_object_t* obj) {
  my_label_t* label = (my_label_t*)obj;
  my_mem_free(obj->allocator, label->text);
  my_widget_destroy((my_widget_t*)label);
  my_object_destroy(obj);
}

my_widget_t* my_label_create(const my_allocator_t* allocator, const char* text) {
  my_label_t* label =
      (my_label_t*)my_mem_calloc(allocator, 1, sizeof(my_label_t));
  if (label == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)label, allocator, &s_label_vtable, "label") !=
      MY_RET_OK) {
    my_mem_free(allocator, label);
    return NULL;
  }
  ((my_object_t*)label)->destroy = label_destroy_chain;
  if (text != NULL) {
    label->text = my_strdup(allocator, text);
    if (label->text == NULL) {
      my_object_unref((my_object_t*)label);
      return NULL;
    }
  }
  label->bg = my_color_rgb(48, 48, 48);
  label->fg = my_color_rgb(230, 230, 230);
  ((my_widget_t*)label)->enable = false; /* labels are non-interactive */
  ((my_widget_t*)label)->widget_type = "label";
  return (my_widget_t*)label;
}

my_ret_t my_label_set_align(my_widget_t* label, my_text_align_t align) {
  if (label == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_label_t*)label)->align = align;
  my_widget_invalidate(label, NULL);
  return MY_RET_OK;
}

my_ret_t my_label_set_text(my_widget_t* label, const char* text) {
  my_label_t* l = (my_label_t*)label;
  char* copy;
  if (label == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(((my_object_t*)label)->allocator, text);
  if (text != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(((my_object_t*)label)->allocator, l->text);
  l->text = copy;
  my_widget_invalidate(label, NULL);
  return MY_RET_OK;
}
