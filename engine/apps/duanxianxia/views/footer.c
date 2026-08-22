/**
 * @file footer.c
 * @brief duanxianxia clone: two-line centered footer (M14b).
 */
#include "../dxx_data.h"
#include "../dxx_theme.h"
#include "myui/widgets/my_label.h"
#include "views.h"

my_widget_t* dxx_build_footer(my_widget_t* parent) {
  my_widget_t* box = my_widget_create(NULL, "dxx_footer");
  my_widget_t* l1 = my_label_create(NULL, DXX_FOOTER_DISCLAIMER);
  my_widget_t* l2 = my_label_create(NULL, DXX_FOOTER_ICP);
  my_label_set_align(l1, MY_TEXT_ALIGN_CENTER);
  my_label_set_align(l2, MY_TEXT_ALIGN_CENTER);
  /* M18b: site footer is grey — class "muted" hits the CSS rule
   * label.muted in dxx_theme */
  my_widget_set_style_class(l1, "muted");
  my_widget_set_style_class(l2, "muted");
  my_widget_set_rect(l1, &(my_rect_t){0, 4, parent != NULL ? parent->rect.w : 0, 20});
  my_widget_set_rect(l2, &(my_rect_t){0, 26, parent != NULL ? parent->rect.w : 0, 20});
  my_widget_add_child(box, l1);
  my_widget_add_child(box, l2);
  my_widget_unref(l1);
  my_widget_unref(l2);
  if (parent != NULL) {
    my_widget_add_child(parent, box);
  }
  return box;
}
