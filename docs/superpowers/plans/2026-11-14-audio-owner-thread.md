# Audio owner thread (core_app Task 9 slice 5)

**Goal:** In `--audio=device` mode, every `AudioSystem` call after start-up runs on one dedicated audio owner thread. Today the application main thread drains the command queue and calls miniaudio itself (`docs/design/core_app_integration.md`, Task 9 slice 3/4: "`AudioSystem` 仍由应用主线程持有，没有独立 owner 线程").

**Scope:** device mode only. Record and null modes keep the main-thread drain, so record traces stay byte-identical and deterministic.

## Design

- `CoreAppAudio` gains an opaque `owner` pointer. When it is set, the struct is in owned mode. The thread, mutex and two condition variables live in a heap block private to `core_app_audio.c`, so the public header does not pull in `<windows.h>`.
- Producer side (main thread): `core_app_audio_enqueue_at` takes the mutex, does the same admission, overload and slot bookkeeping as now, then signals the owner.
- `core_app_audio_drain_device` in owned mode does not touch the device. It wakes the owner and returns the owner's sticky error (normally OK). The frame never waits for the device.
- Owner loop: wait until a command is queued or stop is requested. Pop one command, run the generation check and slot retirement under the lock, then make the device call and write the trace line outside the lock. Exit only when stop is set and the queue is empty. On exit the owner runs the existing close step (bounded probe wait, `audio_system_destroy`, the `result=stopped` trace line). After start, every call into the system therefore happens on the owner.
- New `core_app_audio_flush`: blocks until the queue is empty and no command is in flight. Tests use it to observe device state deterministically. In unowned mode it returns OK on an empty queue and TIMEOUT otherwise.
- `core_app_audio_join` in owned mode: set stop, wake, join the thread. Returns the sticky owner error. `destroy` returns the owner's close result and frees the block.
- New `core_app_audio_start_system_owned` mirrors `start_system` and starts the owner. `start_device_backend` starts the owner once a real device is attached. `start_system` stays synchronous (caller drains), and the existing unit tests keep using it.
- Evidence counters: `device_calls_on_owner` and `device_calls_off_owner` are compared against the owner thread id at each device call. The `result=stopped` line gains ` owner_thread=0|1`.

## Steps (TDD)

- [x] **Step 1: RED unit tests** in `engine/tests/test_core_app_runtime.c` (FAKE system):
  1. `audio_owner_thread_makes_every_device_call`: owned start; LISTENER, PLAY_3D and POSITION from the test thread; `drain_device`, then `flush`. Expect plays=1, moves=1, `device_calls_on_owner == 3`, `device_calls_off_owner == 0`, and the listener position on the system.
  2. `audio_owner_thread_drains_the_queue_before_join`: enqueue 8 PLAY_3D without draining, then shutdown. Expect `device_plays == 8` after join and the `owner_thread=1` stopped line.
  3. `audio_owner_thread_keeps_the_stale_stop_check`: same as the reclaimed-slot test, but in owned mode.
  4. `audio_owner_thread_rejects_a_frame_drain_wait`: `drain_device` with the owner returns OK without blocking, even when 256 commands are queued.
- [x] **Step 2: RED process test.** `test_core_app_audio_device.cmake` requires `owner_thread=1`.
- [x] **Step 3: Implement** in `core_app_audio.[ch]`. Wire nothing new in `core_app.c`: the coordinator order (stop admission, stop producers, close queues, drain, join, destroy) already matches.
- [x] **Step 4: Verify.** Full normal ctest, the core_app tests in TSan and ASan trees, the real device run.
- [x] **Step 5: Docs.** Add a slice 5 section to `core_app_integration.md`, update its "未做" lines, add an `Implementation_Status.md` entry, and correct the audio row in `runtime_thread_model.md`.
- [x] **Step 6: Commit and push.** Confirm CI.

## Execution record (2026-11-14)

- RED: the five new unit tests in `test_core_app_runtime.c` failed to compile before the change (missing `core_app_audio_start_system_owned`, `core_app_audio_flush`, `owner`, the call counters). A fifth test, `audio_flush_without_owner_reports_the_backlog`, pins the unowned `flush` contract.
- The existing `audio_device_drain_drives_the_audio_system` now expects `owner_thread=0`, because `start_system` stays synchronous.
- GREEN: `test_core_app_runtime` 44/44 (20 repeated runs), real PulseAudio run `owner_thread=1`, normal tree 400/400, TSan `test_core_app_runtime` 10 runs with no report. The sanitizer trees fail only the local GPU cases (Mesa/VVL).
