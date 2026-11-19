# Plan: horizontal orientation for my_scroll_bar

Spec: `docs/superpowers/specs/2026-11-19-myui-horizontal-scroll-bar-design.md`.

1. **RED**: a `test_myui_window_manager` case driving a 200x12 horizontal
   bar through real pointer events. Fails to compile while
   `my_scroll_bar_set_horizontal`/`_is_horizontal` do not exist.
2. **GREEN**: the `horizontal` field and the two accessors; a `sb_track`
   helper returning the long axis, which the thumb length and offset use;
   the pointer paths reading x when horizontal; paint drawing along that
   axis with the short axis as the pill radius.
3. **Mutations** (each must fail the test): the track axis fixed to the
   height, the press axis not swapped, the drag axis not swapped, and the
   minimum thumb length removed.
4. **Docs**: `docs/Implementation_Status.md`, the widget header comment,
   spec Result. The audio page is a later slice, so
   `missing_capabilities.md` keeps "滚动条控件" as missing for it.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree for
   `test_myui_window_manager`, push, CI.
