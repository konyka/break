# Runtime / CorePreciseFP

- module root: `Source/Runtime/CorePreciseFP`
- headers: 2; symbols: 28
- symbol kinds: function=14, member=1, namespace=2, prototype=10, struct=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/CorePreciseFP/Internal/Math/PreciseFP.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _prototype_ `bool PreciseFPEqual(float Lhs, float Rhs);` (scope `UE`)
- L10 _prototype_ `bool PreciseFPEqual(double Lhs, double Rhs);` (scope `UE`)
- L12 _prototype_ `uint32 PreciseFPHash(float);` (scope `UE`)
- L13 _prototype_ `uint32 PreciseFPHash(double);` (scope `UE`)

### `Source/Runtime/CorePreciseFP/Public/VerseVM/VVMFloat.h` (Public)


#### struct `Verse::VFloat`  
`struct VFloat`  
_L21-136_
- desc: Encapsulates a Verse float, which has a few deviations from IEEE-754 semantics for the sake of providing extensional equality; i.e. that iff two values compare as equal, there's no way to distinguish them. IEEE-754 floats don't have extensional equality for two reasons: - Zeroes of opposite signs compare as equal, but when used as a divisor produce different infinities. - NaNs compare as unequal to themselves. We resolve this by defining division by negative zero to produce positive infinity, and collapsing NaNs to a single canonical NaN that compares as equal to itself and unordered with all numbers.
- L26 _public function_ `constexpr VFloat() : Value(0.0)` — Default initialize to zero.
- L31 _public function_ `explicit VFloat(double InValue) : Value(InValue)`
- L36 _public function_ `static VFloat NaN()`
- L41 _public function_ `static VFloat Infinity()`
- L46 _public function_ `double AsDouble() const`
- L51 _public function_ `uint64 ReinterpretAsUInt64() const`
- L57 _public prototype_ `VFloat Purify() const;` — Purify a potentially impure float (as defined by VValue).
- L60 _public prototype_ `bool IsFinite() const;` — Predicates for different FP specials.
- L61 _public prototype_ `bool IsInfinite() const;`
- L62 _public prototype_ `bool IsNaN() const;`
- L77 _public function_ `VFloat& operator+=(VFloat Right)`
- L81 _public function_ `VFloat& operator-=(VFloat Right)`
- L85 _public function_ `VFloat& operator*=(VFloat Right)`
- L89 _public function_ `VFloat& operator/=(VFloat Right)`
- L130 _public prototype_ `int64 Ranking() const;` — Ranking function that turns a double into an int64 that defines a total order compatible with the ordering implied for floats, to be precise a <  b  =>  Ranking(a) <  Ranking(b) a == b  <=> Ranking(a) == Ranking(b) For Less(a,b), we only have implication in one direction because when a single NaN is involved, the strict "less" ordering relationship is partial. In the total order implied by Ranking, NaN compares larger than all other floats. Unlike normal IEEE semantics, NaNs compare equal to each other in our ordering, so for Equal we have full equivalence. Ranking can be used directly or as a key for sorted maps and hashes.
- L133 _private member_ `double Value;`
- L135 _private prototype_ `VFloat NormalizeSignedZero() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`
- L67 _function_ `friend constexpr VFloat operator+(VFloat Operand)` (scope `Verse`) — Arithmetic operations in a non-fast-math environment (IEEE compliant). These can (mostly) be removed when callers are guaranteed to not be compiled with fast-math or similar enabled.
- L102 _function_ `friend inline bool operator!=(VFloat Left, VFloat Right)` (scope `Verse`)
- L107 _function_ `friend inline bool operator>(VFloat Left, VFloat Right)` (scope `Verse`)
- L112 _function_ `friend inline bool operator>=(VFloat Left, VFloat Right)` (scope `Verse`)
