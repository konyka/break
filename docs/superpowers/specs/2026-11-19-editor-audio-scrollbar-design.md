# Design: a scroll bar for the audio waveform view

The audio page's view can be moved with the `<`/`>` buttons, Shift+wheel and
the arrow keys, but there is nothing showing where the view sits in the clip
or letting one jump across it. `my_scroll_bar` now supports a horizontal
orientation (`2026-11-19-myui-horizontal-scroll-bar-design.md`), so the page
can carry one.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- A horizontal `editor-audio-scrollbar` (12 px) below the waveform, inside
  the audio section.
- The bar reflects the view: `page_size` is the view length over the clip
  length, and `value` is the view's start over the scrollable range
  (`frames - view_len`), so a full view shows a full-width thumb at 0. The
  panel refreshes both whenever the view or the attachment changes.
- Its "changed" handler maps the value back to a view start
  (`value * (frames - view_len)`, rounded) and sets the view, keeping the
  length. A full view ignores the event, since there is nothing to scroll.
- The handler must not fight the panel's own updates: the panel sets the
  bar's value through `my_scroll_bar_set_value`, which does not emit
  "changed", so no feedback loop.

## Tests

`test_editor_shell`, one case:

- With no attachment the bar reads value 0 and page_size 1.
- After attaching 4000 frames and zooming in twice (a 1000-frame view at
  1500), `page_size` is 0.25 and `value` is 0.5 (1500 of the 3000
  scrollable frames).
- Scrolling with `>` moves the bar's value; zooming out to the whole clip
  puts it back to page_size 1, value 0.
- Setting the bar's value to 1 and emitting "changed" moves the view to the
  clip's end, keeping its length; setting 0 brings it back to the start.
- A "changed" with a full view leaves the view at the whole clip.
- An attachment change (a trim) resets the bar along with the view.

## Out of scope

Auto-hiding the bar when the view covers the clip, a vertical amplitude
zoom, dragging the bar's ends to resize the view.

## Result

Delivered as designed. `test_editor_shell` 220/220, the new case failing
first on the missing widget.

Mutations, each failing the test: `page_size` pinned to 1, the bar's value
computed over the clip length instead of the scrollable range, the handler
mapping the value with the clip length, and the sync call removed from the
refresh. The last one needed `if (false) audio_panel_sync_scrollbar(...)`
rather than deleting the line, because deleting it makes the static function
unused and `-Werror` rejects the build.

No feedback loop to guard against after all: the panel writes the bar with
`my_scroll_bar_set_value`, which deliberately does not emit "changed"
(`my_scroll_bar.c`, `sb_set_internal(..., notify=false)`), so the sync
cannot re-enter the handler.
