# Metal build: one engine.metallib copy per executable directory (2026-11-16)

## Problem
CI `81b31e64`, job "macOS native Metal (Clang)", failed while linking
`dxx_break`:

    Error copying file (if different) from ".../metal_shaders/engine.metallib"
    to ".../build/engine.metallib": No such file or directory

`engine_link_rhi_backend` gave every consumer executable (24 call sites,
most of them in the one build directory) a POST_BUILD
`cmake -E copy_if_different` of `engine.metallib` into
`$<TARGET_FILE_DIR>`. Ninja links those executables in parallel, so up to
a dozen processes copy to the same destination at once. One of them removes
or replaces the file while another is still copying, and that copy fails.
Nothing in the plugin panels change touched this; it is a race that has
been there since the Metal pipeline existed and showed up when more
executables finished linking together.

Reproduced on Linux with a 12-executable CMake project: per-target copies
into one directory failed 1 of 30 clean builds, and 6 of 360 bare parallel
`copy_if_different` runs to one destination failed with the same message.
One shared copy target failed 0 of 30.

## Fix
- `engine_metallib_beside_executables`: one custom command whose OUTPUT is
  `engine.metallib` in the executable directory (per configuration for
  multi-config generators), depending on the compiled library. Plain
  executables depend on this target instead of copying themselves.
- App bundles (the iOS build, where every executable is a bundle) keep a
  per-target copy into their own bundle directory
  (`engine_copy_metallib_into_bundle`); each bundle is a separate
  destination, so it cannot race.
- `test_metal_shader_pipeline` (text contract, runs on every platform)
  now fails when `engine_link_rhi_backend` contains `copy_if_different`
  or does not use the shared target. It failed against the old
  `engine/CMakeLists.txt` and passes with the fix.

## Not verified locally
The Metal build only runs on macOS. The macOS CI job after this commit is
the real check.

## Also seen in that run
"Verify and publish Linux CI image / Prepare ci-linux image digest" failed
with `denied: denied` when pushing to `ghcr.io`. That is a registry
permission problem outside the repository; the job has failed the same way
before (`a9c86488`) and passed on the next runs without a change.
