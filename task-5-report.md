# Task 5 Report: D3D12 WARP Pixel-Level MRT Verification

Worktree: `E:/work/break/.worktrees/d3d12-mrt-fbo`
Base: `734d2fee fix(d3d12): use MRT attachment clear colors`

## Passing build/test

Command:
```bash
cd E:/work/break/.worktrees/d3d12-mrt-fbo/build-d3d12-debug-task4
ninja test_d3d12_warp_runtime
```
Output:
```text
[0/2] Re-checking globbed directories...
[1/3] Building C object CMakeFiles/test_d3d12_warp_runtime.dir/tests/test_d3d12_warp_runtime.c.obj
[2/3] Linking C executable test_d3d12_warp_runtime.exe
```

Command:
```bash
cd E:/work/break/.worktrees/d3d12-mrt-fbo/build-d3d12-debug-task4
ctest -R test_d3d12_warp_runtime -V
```
Output:
```text
118: === Running Tests ===
118:   [1] warp_device_identity_is_honest ... OK
118:   [2] offscreen_fbo_clear_round_trips_pixels ... OK
118:   [3] probe_triangle_rasterises_into_offscreen_fbo ... OK
118:   [4] push_constants_transform_reaches_the_shader ... OK
118:   [5] blit_texture_binding_samples_red_into_offscreen_fbo ... OK
118:   [6] mrt_fbo_clears_and_reads_independent_attachments ... OK
118:
118: === Results: 6 passed, 0 failed, 6 total ===
1/1 Test #118: test_d3d12_warp_runtime ..........   Passed    0.66 sec

100% tests passed, 0 tests failed out of 1
Total Test time (real) = 0.67 sec
```

## Reverse validation

Temporarily changed the expected attachment-1 color from blue `{0,0,255,255}` to red `{255,0,0,255}` and ran:
```bash
cd E:/work/break/.worktrees/d3d12-mrt-fbo/build-d3d12-debug-task4
ninja test_d3d12_warp_runtime && ctest -R test_d3d12_warp_runtime -V
```
Result (expected failure):
```text
118:   [6] mrt_fbo_clears_and_reads_independent_attachments ...   FAIL: E:/work/break/.worktrees/d3d12-mrt-fbo/engine/tests/test_d3d12_warp_runtime.c:307: pixels[attachment][pixel * 4 + channel] != expected[channel]
118:
118: === Results: 5 passed, 1 failed, 6 total ===
1/1 Test #118: test_d3d12_warp_runtime ..........***Failed    0.56 sec

0% tests passed, 1 tests failed out of 1
Errors while running CTest
Command failed with exit code 8.
```

The expected blue color was restored, rebuilt, and the passing command/output above was rerun.

## Implementation

- Added `mrt_fbo_clears_and_reads_independent_attachments` to `engine/tests/test_d3d12_warp_runtime.c`.
- Creates an 8x8 two-attachment RGBA8 MRT, uses public bind/clear-attachment/unbind APIs, presents, reads both textures, and checks all 64 pixels and all 4 channels independently.
- No production code changes were required.
