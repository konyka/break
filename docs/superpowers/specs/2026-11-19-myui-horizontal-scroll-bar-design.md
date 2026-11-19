# Design: horizontal orientation for my_scroll_bar

`my_scroll_bar` (`src/myui/myui/widgets/my_scroll_bar.c`) is vertical only:
the thumb length and position come from `rect.h`, the pointer maths from the
event's local y, and the keys treat Down/Right as "forward". The audio
waveform's view needs a horizontal bar, and so would any horizontally
scrolling container.

This slice adds the orientation to the widget; wiring it into the audio page
is a separate slice.

## Change

`my_scroll_bar.h` / `.c`:

- `my_scroll_bar_set_horizontal(bar, bool)` and
  `my_scroll_bar_is_horizontal(bar)`, with a `horizontal` field in
  `my_scroll_bar_t`. Default false, so every existing user keeps its
  behaviour.
- The thumb geometry uses the long axis: `rect.w` when horizontal, `rect.h`
  otherwise. The minimum thumb length (`MY_SCROLL_BAR_MIN_THUMB`) and the
  value-to-position mapping are unchanged apart from the axis.
- The pointer paths (thumb hit, drag offset, track paging) read the local x
  when horizontal, the local y otherwise.
- Paint draws the thumb along the long axis; the rounded-rect radius uses
  the short axis (`rect.h` when horizontal), so it stays a pill.
- The keys are unchanged: Left/Up step back, Right/Down step forward,
  PageUp/PageDown page, Home/End jump. They already read sensibly in both
  orientations.

## Tests

`test_myui_window_manager.c`, extending the existing scroll-bar cases:

- A horizontal bar (200x12, page_size 0.25) reports `is_horizontal`; a press
  on the right part of the track pages forward, one on the left pages back,
  and the value clamps to [0, 1].
- Dragging the thumb from the left end to the middle of a horizontal bar
  sets roughly 0.5, and the same drag on a vertical bar of the same size
  does not (the axes are not swapped).
- A vertical bar still behaves exactly as before (the existing cases must
  stay green unchanged).
- The thumb never shrinks below `MY_SCROLL_BAR_MIN_THUMB` along the long
  axis: with page_size 0.01 on a 200 px bar, a drag to the far right still
  reaches value 1.

## Out of scope

Wiring it into the audio page, auto-hiding when the content fits, two bars
on one container.

## Result

Delivered as designed. `test_myui_window_manager` 240/240, with the new case
failing to compile first (the two accessors did not exist). Every existing
scroll-bar case stayed green unchanged, which is the evidence that the
vertical default is untouched.

Mutations, each failing the test: the track axis fixed back to `rect.h`, the
press axis not swapped to x, the drag axis not swapped, and the
`MY_SCROLL_BAR_MIN_THUMB` floor removed.

The "same press on a vertical bar does nothing" assertion works because a
200x12 vertical bar has a 12 px track and a 16 px minimum thumb, so its
movable range is zero and `sb_from_y` returns early. That is the pre-existing
clamp, not new behaviour.

Note on the ASan tree: `build-voice-relay-asan`'s `test_myui_window_manager`
reports 19527 bytes leaked in 405 allocations, an identical figure with this
change stashed. With `fast_unwind_on_malloc=0` the frames resolve into
`loader_icd_scan` in `libvulkan.so.1`: the leak is inside the system Vulkan
loader's driver scan, not project code, which is why it does not appear in
the CI ASan jobs. Not this slice's to fix; recorded so the number is not
mistaken for a regression later.
