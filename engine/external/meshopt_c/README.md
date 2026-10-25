# meshopt_c — pure C11 port of the meshoptimizer v1.3 simplifier

Source: https://github.com/zeux/meshoptimizer, release tag **v1.3**
(`MESHOPTIMIZER_VERSION 1030`), commit `9e1f07b159d3cb777f1c67ed31fc11fd117986f4`.
License: MIT, see `LICENSE.md` (upstream text, verbatim).

Upstream file sha256 at that tag (the files the port was made from):

| upstream file | sha256 |
|---|---|
| `src/simplifier.cpp` | `719303b6970398631e30724e8eebc6cd2e7e08b67fe8ab7cbf7eecafdaa08616` |
| `src/vcacheoptimizer.cpp` | `618429ef4db8ab9b16fde4e73dcf425d89452acbf103085478bc8b1761fa6689` |
| `src/meshoptimizer.h` | `e3688ef553f603391747895a5c221ef1528574cc7f8173782417a96cb531f61b` |

## Ported public functions

- `meshopt_simplify`
- `meshopt_simplifyWithAttributes`
- `meshopt_simplifyScale`
- `meshopt_optimizeVertexCache`
- the `meshopt_Simplify*` option enum and `meshopt_SimplifyVertex_*` lock flags (same numeric values)

Everything these reach in `simplifier.cpp` (the `meshopt_simplifyEdge` call graph, including the
Sparse / Prune / Permissive / Regularize / PreserveFolds / ErrorClamped option paths) and in
`vcacheoptimizer.cpp` is ported. Not ported: `simplifyWithUpdate`, `simplifySloppy`,
`simplifyPrune`, `simplifyPoints`, `optimizeVertexCacheStrip` / `Fifo`, and the internal
`meshopt_SimplifyInternalSolve` / `InternalDebug` paths (only reachable from `simplifyWithUpdate`
or debug tooling): `solvePositions`, `solveAttributes`, `finalizeVertices`, `quadricSolve`,
`quadricReduceAttributes`, `quadricVolumeGradient`, `hasTriangleFlips(v1 position)`,
`getNeighborhoodRadius`, plus the sloppy/points helpers.

## Mechanical changes (algorithms unchanged)

The algorithms, constants, iteration order and floating-point expression order are unchanged; the
port produces bit-identical output to upstream on the same compiler and flags (see below).

1. `meshopt_Allocator` → `MeshoptArena { void* blocks[24]; size_t count; }` with
   `meshopt_arena_alloc`, `meshopt_arena_free_all` and `meshopt_arena_pop` (the LIFO
   `deallocate` upstream uses for temporary hash tables). `count * sizeof(T)` is overflow-checked.
2. Allocation failure no longer aborts: every allocation is checked, early exits become
   `goto done;` so the arena is always freed. The simplify functions then return 0 and set
   `*result_error = 0` (when non-NULL); `meshopt_optimizeVertexCache` writes the input order
   unchanged to `destination`. Upstream has no failure path (operator new throws / custom
   allocator asserts).
3. `hashLookup2<T, Hash>` → concrete `hashLookup2Position` / `hashLookup2Remap` (the only two
   instantiations reachable); hasher `hash()` / `equal()` methods → free functions.
4. C++ references → pointers; `namespace meshopt` → file-`static` functions; overloads renamed
   (`hasEdge` with wedges → `hasEdgeWedge`, attribute `quadricError` → `quadricErrorAttr`,
   `quadricAdd` on gradient arrays → `quadricGradAddN`); default arguments made explicit.
5. `reinterpret_cast` / `static_cast` / `const_cast` / `unsigned(x)` / `int(x)` → C casts.
6. The anonymous union in `Collapse` became a named member `u` (`c->u.error`, `c->u.bidi`; same
   layout and type punning). `sort_bits` / `sort_bins` in `sortEdgeCollapses` became `enum`
   constants because a C `const` is not a constant expression (the array bound would become a
   VLA). `kMaxAttributes`, `kCacheSizeMax` and `kValenceMax` became macros for the same reason.
7. `meshopt_simplifyEdge` and `meshopt_optimizeVertexCacheTable` are `static` (not exported).
   The `assert((options & meshopt_SimplifyInternalSolve) == 0)` checks in the public wrappers are
   dropped along with the internal option values; the `volume_gradients` argument (always NULL
   without `InternalSolve`) was removed from `fillFaceQuadrics` / `updateQuadrics`.
8. `TRACE` instrumentation removed.
9. `asserts` are kept as `assert()`. No warning suppressions are needed: the sources build cleanly
   under the engine's flags (`-Wall -Wextra -Werror -pedantic` for clang/gcc, `/W4 /WX` for
   MSVC-style frontends).

## Reference test

`engine/tests/test_meshopt_c.c` (ctest `test_meshopt_c`) checks invariants and compares 110
cases (5 procedural meshes × 22 option/target combinations: index count, `result_error` bit
pattern, FNV-1a of the simplified index buffer and of the vertex-cache-optimized buffer) plus
`meshopt_simplifyScale` bits against a table generated from upstream C++.

Mesh generators avoid libm transcendental functions so the inputs are identical everywhere.
Results stay bit-exact for any build that does not contract `a*b+c` into FMA. clang on x86-64
does not do this by default; with `-march=native` (or another target that has FMA), both the C++
original and this port shift identically, but they no longer match the table, so build this
library with `-ffp-contract=off` on such targets.

To regenerate or verify the table against upstream C++ (throwaway harness, outside the repo):

```sh
mkdir -p .tmp/meshopt_ref/up && cd .tmp/meshopt_ref
for f in src/simplifier.cpp src/vcacheoptimizer.cpp src/meshoptimizer.h; do
  curl -sL -o up/$(basename $f) https://raw.githubusercontent.com/zeux/meshoptimizer/v1.3/$f; done
clang++ -O2 -c up/simplifier.cpp -o up_s.o && clang++ -O2 -c up/vcacheoptimizer.cpp -o up_v.o
clang -std=c11 -O2 -DMESHOPT_C_REFERENCE_DUMP -I../../engine/external -c ../../engine/tests/test_meshopt_c.c -o dump.o
clang++ dump.o up_s.o up_v.o -o dump_ref && ./dump_ref > ref.txt
clang -O2 dump.o ../../engine/external/meshopt_c/simplifier.c ../../engine/external/meshopt_c/vcacheoptimizer.c -o dump_c && ./dump_c > c.txt
diff ref.txt c.txt   # must be empty; ref.txt is the kExpected table in the test
```
