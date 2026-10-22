# Programs / AutoRTFMTests

- module root: `Source/Programs/AutoRTFMTests`
- headers: 8; symbols: 118
- symbol kinds: class=8, function=27, macro=17, member=17, namespace=9, prototype=29, struct=4, typedef=2, variable=5
- PrivateDependencyModuleNames: ApplicationCore, AutoRTFM, Catch2Extras, Core, CoreUObject, DesktopPlatform, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/AutoRTFMTests/Classes/MyAutoRTFMTestObject.h` (Public)


#### class `UMyAutoRTFMTestObject`  
`class UMyAutoRTFMTestObject : public UObject`  
_L7-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L12 _public typedef_ `using FConstructorCallback = void(const FObjectInitializer&, UMyAutoRTFMTestObject&);`
- L14 _public prototype_ `UMyAutoRTFMTestObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L16 _public member_ `int Value = 42;`
- L18 _public member_ `static FConstructorCallback* ConstructorCallback;`
- L20 _public function_ `void DoNothing() const`

### `Source/Programs/AutoRTFMTests/Classes/MyAutoRTFMTestObjectWithSubObjects.h` (Public)


#### class `UMyAutoRTFMTestObjectWithSubObjects`  
`class UMyAutoRTFMTestObjectWithSubObjects : public UObject`  
_L7-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L12 _public prototype_ `static FName GetSubObjectName();`
- L14 _public prototype_ `UMyAutoRTFMTestObjectWithSubObjects(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L16 _public member_ `UObject* SubObject;`
- L18 _public function_ `void DoNothing() const`

### `Source/Programs/AutoRTFMTests/Private/API.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace NoAutoRTFM`
- L7 _prototype_ `int DoSomethingC(int I);` (scope `NoAutoRTFM`)
- L8 _prototype_ `int DoSomethingInTransactionC(int I);` (scope `NoAutoRTFM`)
- L10 _prototype_ `int DoSomethingCpp(int I);` (scope `NoAutoRTFM`)
- L11 _prototype_ `int DoSomethingInTransactionCpp(int I);` (scope `NoAutoRTFM`)

### `Source/Programs/AutoRTFMTests/Private/AutoRTFMTestUtils.h` (Private)


#### struct `AutoRTFMTestUtils::FScopedRetry`  
`struct FScopedRetry`  
_L20-34_
- desc: Temporarily changes the AutoRTFM retry mode for the lifetime of the FScopedRetry object.
- L22 _public function_ `FScopedRetry(AutoRTFM::ForTheRuntime::EAutoRTFMRetryTransactionState NewRetry) : OldRetry(AutoRTFM::ForTheRuntime::GetRetryTransaction())`
- L28 _public function_ `~FScopedRetry()`
- L33 _public member_ `AutoRTFM::ForTheRuntime::EAutoRTFMRetryTransactionState OldRetry;`

#### class `AutoRTFMTestUtils::FCaptureWarningContext`  
`class FCaptureWarningContext : private FFeedbackContext`  
_L37-113_
- inherits: `FFeedbackContext`
- desc: A helper class that for the lifetime of the object, intercepts and records UE_LOG warnings.
- L40 _public function_ `FCaptureWarningContext() : OldContext(GWarn)`
- L41 _public function_ `~FCaptureWarningContext()`
- L44 _public function_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override`
- L57 _public function_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time) override`
- L70 _public function_ `void SerializeRecord(const UE::FLogRecord& Record) override`
- L84 _public function_ `const std::vector<std::string>& GetWarnings() const`
- L90 _public function_ `bool HasWarning(std::string_view Expected) const`
- L99 _public function_ `bool HasWarningSubstring(std::string_view Substr) const`
- L108 _private prototype_ `FCaptureWarningContext(const FCaptureWarningContext&) = delete;`
- L109 _private prototype_ `FCaptureWarningContext& operator = (const FCaptureWarningContext&) = delete;`
- L111 _private member_ `FFeedbackContext* OldContext = nullptr;`
- L112 _private member_ `std::vector<std::string> Warnings;`

#### class `AutoRTFMTestUtils::FScopedSanitizerMode`  
`class FScopedSanitizerMode`  
_L118-136_
- desc: A helper class that temporarily changes the AutoRTFM sanitizer mode for the lifetime of the object, restoring the original level on destruction.
- L121 _public function_ `FScopedSanitizerMode(AutoRTFM::Sanitizer::EMode NewMode) : PrevMode(AutoRTFM::Sanitizer::GetMode())`
- L127 _public function_ `~FScopedSanitizerMode()`
- L132 _private prototype_ `FScopedSanitizerMode(const FScopedSanitizerMode&) = delete;`
- L133 _private prototype_ `FScopedSanitizerMode& operator = (const FScopedSanitizerMode&) = delete;`
- L135 _private member_ `const AutoRTFM::Sanitizer::EMode PrevMode;`

#### class `AutoRTFMTestUtils::FScopedEnsureOnInternalAbort`  
`class FScopedEnsureOnInternalAbort final`  
_L157-176_
- L160 _public function_ `FScopedEnsureOnInternalAbort(const bool bState) : bOriginal(AutoRTFM::ForTheRuntime::GetEnsureOnInternalAbort())`
- L166 _public function_ `~FScopedEnsureOnInternalAbort()`
- L172 _private prototype_ `FScopedEnsureOnInternalAbort(const FScopedEnsureOnInternalAbort&) = delete;`
- L173 _private prototype_ `FScopedEnsureOnInternalAbort& operator = (const FScopedEnsureOnInternalAbort&) = delete;`
- L175 _private member_ `const bool bOriginal;`

#### class `AutoRTFMTestUtils::FScopedInternalAbortAction`  
`class FScopedInternalAbortAction final`  
_L178-197_
- L181 _public function_ `FScopedInternalAbortAction(AutoRTFM::ForTheRuntime::EAutoRTFMInternalAbortActionState State) : Original(AutoRTFM::ForTheRuntime::GetInternalAbortAction())`
- L187 _public function_ `~FScopedInternalAbortAction()`
- L193 _private prototype_ `FScopedInternalAbortAction(const FScopedInternalAbortAction&) = delete;`
- L194 _private prototype_ `FScopedInternalAbortAction& operator = (const FScopedInternalAbortAction&) = delete;`
- L196 _private member_ `const AutoRTFM::ForTheRuntime::EAutoRTFMInternalAbortActionState Original;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AutoRTFMTestUtils`
- L93 _function_ `` (scope `AutoRTFMTestUtils::FCaptureWarningContext::HasWarning`)
- L102 _function_ `` (scope `AutoRTFMTestUtils::FCaptureWarningContext::HasWarningSubstring`)
- L139 _macro_ `#define AUTORTFM_SCOPED_DISABLE_RETRY() \`
- L144 _macro_ `#define AUTORTFM_SCOPED_SANITIZER_MODE_DISABLE() \`
- L147 _macro_ `#define AUTORTFM_SCOPED_SANITIZER_MODE_WARN() \`
- L151 _macro_ `#define AUTORTFM_SCOPED_SANITIZER_MODE_DISABLE() static_assert(true) /* require semicolon */`
- L154 _variable_ `static constexpr const std::string_view kMemoryModifiedInOpenWarning = "Th` (scope `AutoRTFMTestUtils`)

### `Source/Programs/AutoRTFMTests/Private/Catch2Includes.h` (Private)


#### class `AutoRTFMCatch2::Section`  
`class Section`  
_L111-127_
- desc: An AutoRTFM always-open wrapper around Catch::Section
- L114 _public function_ `Section(Catch::SectionInfo&& Info) : Inner(std::move(Info))`
- L117 _public function_ `Section(Catch::SourceLineInfo const& LineInfo, Catch::StringRef Name, const char* const = nullptr) : Inner(LineInfo, Name)`
- L120 _public prototype_ `~Section() = default;`
- L123 _public function_ `explicit operator bool() const`
- L126 _private member_ `Catch::Section Inner;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define CATCH_CONFIG_PREFIX_ALL 1` — Prefixes all the 'real' Catch2 macros with 'CATCH_'. We call these with the AutoRTFM-safe, unprefixed forms below.
- L19 _namespace_ `namespace Catch`
- L19 _namespace_ `namespace Benchmark` (scope `Catch`)
- L22 _prototype_ `template <typename T> AUTORTFM_DISABLE inline void deoptimize_value(T&& x);` (scope `Catch::Benchmark`)
- L25 _prototype_ `template <typename Fn, typename... Args> AUTORTFM_DISABLE inline auto invoke_deoptimized(Fn&& fn, Args&&... args) -> std::enable_if_t<!std::is_same<void, decltype(fn(args...))>::value>;` (scope `Catch::Benchmark`)
- L28 _prototype_ `template <typename Fn, typename... Args> AUTORTFM_DISABLE inline auto invoke_deoptimized(Fn&& fn, Args&&... args) -> std::enable_if_t<std::is_same<void, decltype(fn(args...))>::value>;` (scope `Catch::Benchmark`)
- L30 _variable_ `struct AUTORTFM_DISABLE Benchmark;` (scope `Catch::Benchmark`)
- L31 _variable_ `struct AUTORTFM_DISABLE Chronometer;` (scope `Catch::Benchmark`)
- L33 _namespace_ `namespace Detail` (scope `Catch::Benchmark`)
- L33 _variable_ `namespace Detail { struct AUTORTFM_DISABLE BenchmarkFunction; } } THIRD_PARTY_INCLUDES_START #include <catch_amalgamated.hpp> THIRD_PARTY_INCLUDES_END` (scope `Catch::Benchmark::Detail`)
- L46 _macro_ `#define AUTORTFM_CATCH2_INTERNAL_CATCH_TEST(macroName, resultDisposition, ...) \` — Evaluates the expression (varargs) in the current transaction state, then switches to the open to call into the Catch2 assertion handler logic.
- L66 _macro_ `#define AUTORTFM_CATCH2_INTERNAL_CHECK_THAT( macroName, matcher, resultDisposition, arg ) \` — Evaluates the matcher + arg in the current transaction state, then switches to the open to call into the Catch2 assertion handler logic.
- L81 _macro_ `#define AUTORTFM_CATCH2_SECTION(VAR_NAME, ...) \` — Same as Catch2's INTERNAL_CATCH_SECTION, but the unique variable name is passed in, and can be used in a closed transaction.
- L89 _macro_ `#define AUTORTFM_CATCH_TEST_CASE(TEST_NAME, ...) \`
- L98 _macro_ `#define REQUIRE( ... ) AUTORTFM_CATCH2_INTERNAL_CATCH_TEST( "REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )`
- L99 _macro_ `#define REQUIRE_THAT( arg, matcher ) AUTORTFM_CATCH2_INTERNAL_CHECK_THAT( "REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )`
- L100 _macro_ `#define FAIL(...) AutoRTFM::Open([&] { CATCH_FAIL(__VA_ARGS__); })`
- L101 _macro_ `#define TEST_CASE(...) AUTORTFM_CATCH_TEST_CASE(INTERNAL_CATCH_UNIQUE_NAME(CATCH2_INTERNAL_TEST_), __VA_ARGS__)`
- L102 _macro_ `#define TEMPLATE_TEST_CASE(...) CATCH_TEMPLATE_TEST_CASE(__VA_ARGS__)`
- L103 _macro_ `#define BENCHMARK(...) CATCH_BENCHMARK(__VA_ARGS__)`
- L104 _macro_ `#define BENCHMARK_ADVANCED(...) CATCH_BENCHMARK_ADVANCED(__VA_ARGS__)`
- L105 _macro_ `#define SECTION(...) AUTORTFM_CATCH2_SECTION(INTERNAL_CATCH_UNIQUE_NAME(catch_internal_Section), __VA_ARGS__)`
- L107 _namespace_ `namespace AutoRTFMCatch2`

### `Source/Programs/AutoRTFMTests/Private/CrossCUTests.h` (Private)


#### struct `CrossCU::FLargeStruct`  
`struct FLargeStruct`  
_L8-13_
- L10 _public member_ `int Ints[32];`
- L12 _public prototype_ `static int Sum(FLargeStruct Struct);`

#### Free symbols / members of external scopes

- L3 _namespace_ `namespace CrossCU`
- L6 _prototype_ `int SomeFunction(int X);` (scope `CrossCU`)

### `Source/Programs/AutoRTFMTests/Private/IntervalTestUtils.h` (Private)


#### struct `FTreeIntervals`  
`struct FTreeIntervals`  
_L16-42_
- L19 _public member_ `std::vector<FInterval> Free;` — Intervals that are not in the tree
- L21 _public member_ `std::vector<FInterval> Used;` — Intervals that are in the tree
- L26 _public function_ `void SortAndValidate()` — Sorts the Free and Used intervals into ascending order, and checks that each interval in the vector has a non-zero size and does not overlap any other interval in the same vector.

#### Free symbols / members of external scopes

- L12 _typedef_ `using FInterval = AutoRTFM::FInterval;`
- L14 _variable_ `static constexpr FInterval MaxInterval{static_cast<uintptr_t>(0), std::numeric_limits<uintptr_t>::max()};`
- L29 _function_ `` (scope `FTreeIntervals::SortAndValidate`)
- L45 _function_ `static FTreeIntervals BuildIntervals(int Seed, size_t MaxUsed)` — Populates a tree with at most MaxUsed random intervals across the entire uintptr_t interval range.

### `Source/Programs/AutoRTFMTests/Private/ObjectLifetimeHelper.h` (Private)


#### struct `AutoRTFMTestUtils::FObjectLifetimeHelper`  
`struct FObjectLifetimeHelper`  
_L13-28_
- desc: A helper type that acts like an int, but also tracks number of ctors, dtors and whether its used after move.
- L15 _public prototype_ `FObjectLifetimeHelper();`
- L16 _public prototype_ `~FObjectLifetimeHelper();`
- L17 _public prototype_ `FObjectLifetimeHelper(int Value);`
- L18 _public prototype_ `FObjectLifetimeHelper(const FObjectLifetimeHelper& Other);`
- L19 _public prototype_ `FObjectLifetimeHelper(FObjectLifetimeHelper&& Other);`
- L20 _public prototype_ `FObjectLifetimeHelper& operator = (const FObjectLifetimeHelper& Other);`
- L21 _public prototype_ `FObjectLifetimeHelper& operator = (FObjectLifetimeHelper&& Other);`
- L22 _public prototype_ `bool operator == (FObjectLifetimeHelper Other) const;`
- L24 _public member_ `int Value = 0;`
- L25 _public member_ `bool bIsValid = true;`
- L26 _public member_ `static size_t ConstructorCalls;`
- L27 _public member_ `static size_t DestructorCalls;`

#### class `std::hash`  
`template<> class hash<AutoRTFMTestUtils::FObjectLifetimeHelper>`  
_L36-43_
- L39 _public function_ `size_t operator()(const AutoRTFMTestUtils::FObjectLifetimeHelper& Object) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AutoRTFMTestUtils`
- L33 _namespace_ `namespace std`
