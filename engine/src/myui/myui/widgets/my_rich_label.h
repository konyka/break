/**
 * @file my_rich_label.h
 * @brief Rich text label (M14a): one line of inline segments, each with
 * its own color and a bold flag.
 *
 * Segments are laid out in order on a single line, vertically centered;
 * anything past the widget width is clipped (the widget paint clip does
 * this; later segments are not even drawn). Multi-line text is out of
 * scope — compose several rich_labels in a flow/linear container.
 *
 * Bold is FAKE bold: the segment is drawn twice with a 1px x-offset
 * (works on every backend; no synthetic font emboldening).
 */
#ifndef MY_RICH_LABEL_H
#define MY_RICH_LABEL_H

#include "myui/my_widget.h"

/** @brief Create an empty rich label. */
my_widget_t* my_rich_label_create(const my_allocator_t* allocator);

/** @brief Append a segment (text copied; rgba32 color; bold = fake). */
my_ret_t my_rich_label_add_segment(my_widget_t* label, const char* text,
                                   uint32_t rgba_color, bool bold);

/** @brief Remove all segments. */
void my_rich_label_clear(my_widget_t* label);

/**
 * @brief Estimated content width in pixels using the built-in 8px cell
 * metrics (bold segments count +1). For layout hints only — the actual
 * paint measures with the vgcanvas font when one is set.
 */
int32_t my_rich_label_content_width(my_widget_t* label);

#endif /* MY_RICH_LABEL_H */
