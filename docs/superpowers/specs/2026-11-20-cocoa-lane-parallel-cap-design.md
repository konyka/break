# macOS Cocoa Lane Build Parallelism Cap Design

## Context

`lane-native-surface-cocoa` (macOS 15, "macOS Cocoa + MoltenVK (Clang)") failed
in 4 of the last 39 CI runs. Three of those failures (`7ae28b5b`, `e1944152`,
`753765ff`) end the same way:

```text
clang: error: unable to execute command: posix_spawn failed: Resource temporarily unavailable
make[2]: *** wait: No child processes.  Stop.
```

The lane configures with the default generator, Unix Makefiles. Its two build
steps run `cmake --build build ... --parallel` with no job count. For the
Makefile generator CMake turns a bare `--parallel` into `make -j` with no
limit, so make starts a compiler for every ready object (909 objects in the
full build) and the runner hits its per-user process limit. Ninja lanes are
not affected: Ninja's default is the CPU count. The fourth failure
(`60aeae9d`) was a separate compile error, already fixed.

## Approaches

1. Pass an explicit job count from the runner's CPU count:
   `--parallel "$(sysctl -n hw.ncpu)"` in both steps. Recommended: same
   throughput as Ninja's default, bounded, no new dependency.
2. Switch the lane to Ninja. Rejected for this slice: changes the build
   graph the lane has been validating and needs `brew install ninja`.
3. Set `CMAKE_BUILD_PARALLEL_LEVEL` in the job env. Equivalent, but a bare
   `--parallel` on the command line overrides it, so the steps would still
   need editing.

## Change

In `lane-native-surface-cocoa`, replace the two bare `--parallel` flags with
`--parallel "$(sysctl -n hw.ncpu)"`. No other lane changes. The other
Makefile-generator lanes are Linux (`lane-headless-linux-clang`,
`lane-native-surface-wayland`, `wayland-gl`, `lane-gpu-runtime-linux-gl`) and
have not shown this failure; they are recorded as candidates, not changed.

## TDD and Verification

1. Contract: in that lane, no `cmake --build` step uses a bare `--parallel`,
   both build steps use `--parallel "$(sysctl -n hw.ncpu)"`, and the job still
   uses the default generator. RED on the current workflow.
2. Apply the edit; GREEN.
3. Push and confirm the lane succeeds on the exact HEAD.
