# Developer / LowLevelTestsRunner

- module root: `Source/Developer/LowLevelTestsRunner`
- headers: 17; symbols: 178
- symbol kinds: class=3, delegate=2, function=61, macro=48, member=1, namespace=5, prototype=57, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, UnrealEd

### `Source/Developer/LowLevelTestsRunner/Private/Platform/Apple/AppleTestRunnerHelper.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define PLATFORM_IOS 0`
- L10 _macro_ `#define PLATFORM_MAC 0`

### `Source/Developer/LowLevelTestsRunner/Private/TestRunnerOutputDeviceError.h` (Private)


#### class `UE::LowLevelTests::FTestRunnerOutputDeviceError`  
`class FTestRunnerOutputDeviceError : public FOutputDeviceError`  
_L10-46_
- inherits: `FOutputDeviceError`
- desc: @brief Used to replace GError so that errors are capture during execution of tests
- L13 _public function_ `explicit FTestRunnerOutputDeviceError(FOutputDeviceError* Error) : DeviceError(Error)`
- L18 _public function_ `FTestRunnerOutputDeviceError() : DeviceError(nullptr)`
- L24 _public function_ `virtual void HandleError() override`
- L32 _public prototype_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L34 _public function_ `void SetDeviceError(FOutputDeviceError* Error)`
- L39 _public function_ `FOutputDeviceError* GetDeviceError() const`
- L45 _private member_ `FOutputDeviceError* DeviceError;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace LowLevelTests` (scope `UE`)

### `Source/Developer/LowLevelTestsRunner/Private/TestRunnerPrivate.h` (Private)


#### class `UE::LowLevelTests::ITestRunner`  
`class ITestRunner`  
_L8-26_
- L12 _public prototype_ `static ITestRunner* Get();` — Returns the test runner if one is active, otherwise null.
- L15 _public prototype_ `virtual bool HasGlobalSetup() const = 0;` — Returns true if the test runner will perform global setup and teardown.
- L17 _public prototype_ `virtual bool HasLogOutput() const = 0;` — Returns true if the test runner has default logging enabled via UE_LOG.
- L19 _public prototype_ `virtual bool IsDebugMode() const = 0;` — Returns true if the test runner has extra debug functionality enabled.
- L21 _public prototype_ `virtual int GetTimeoutMinutes() const = 0;` — Returns a value indicating per test allowed timeout in minutes.
- L24 _protected prototype_ `ITestRunner();`
- L25 _protected prototype_ `virtual ~ITestRunner();`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace LowLevelTests` (scope `UE`)

### `Source/Developer/LowLevelTestsRunner/Public/CommandLineUtil.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `const char** ReadAndAppendAdditionalArgs(const char* FileDir, int* OutNumArgs, const char** Argv, int Argc);`

### `Source/Developer/LowLevelTestsRunner/Public/Platform/Android/AndroidTestRunner.h` (Public)
_(no declarations extracted)_

### `Source/Developer/LowLevelTestsRunner/Public/Platform/IOS/IOSTestRunner.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `int main(int argc, const char* argv[]);`

### `Source/Developer/LowLevelTestsRunner/Public/Platform/Linux/LinuxTestRunner.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `int main(int argc, const char* argv[]);`

### `Source/Developer/LowLevelTestsRunner/Public/Platform/Mac/MacTestRunner.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `int main(int argc, const char* argv[]);`

### `Source/Developer/LowLevelTestsRunner/Public/Platform/Windows/WindowsTestRunner.h` (Public)


#### Free symbols / members of external scopes

- L10 _prototype_ `int main(int argc, const char* argv[]);`

### `Source/Developer/LowLevelTestsRunner/Public/TestCommon/CoreUObjectUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `void InitCoreUObject();`
- L9 _prototype_ `void CleanupCoreUObject();`

### `Source/Developer/LowLevelTestsRunner/Public/TestCommon/CoreUtilities.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `void InitGWarn();`
- L10 _prototype_ `void InitIOThreadPool(bool MultiThreaded = false, int32 StackSize = 128 * 1024);`
- L12 _prototype_ `void InitThreadPool(bool MultiThreaded = false, int32 StackSize = 128 * 1024);`
- L14 _prototype_ `void InitBackgroundPriorityThreadPool(bool MultiThreaded = false, int32 StackSize = 128 * 1024);`
- L16 _prototype_ `void InitAllThreadPools(bool MultiThreaded = false);`
- L18 _prototype_ `void CleanupThreadPool();`
- L20 _prototype_ `void CleanupIOThreadPool();`
- L22 _prototype_ `void CleanupBackgroundPriorityThreadPool();`
- L24 _prototype_ `void CleanupAllThreadPools();`
- L26 _prototype_ `void InitTaskGraph(bool MultiThreaded = false, ENamedThreads::Type ThreadToAttach = ENamedThreads::GameThread);`
- L28 _prototype_ `void CleanupTaskGraph();`
- L30 _prototype_ `void InitTaskGraphAndDependencies(bool MultiThreaded = false);`
- L32 _prototype_ `void CleanupTaskGraphAndDependencies();`
- L34 _prototype_ `void CleanupPlatform();`

### `Source/Developer/LowLevelTestsRunner/Public/TestCommon/EngineUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `void InitAsyncQueues();`
- L8 _prototype_ `void InitRendering();`
- L9 _prototype_ `void InitEngine();`
- L10 _prototype_ `void CleanupEngine();`

### `Source/Developer/LowLevelTestsRunner/Public/TestCommon/Expectations.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace (anonymous)`
- L20 _function_ `FString GetStringValueToDisplay(FStringView Value)` (scope `__anon806426440111`)
- L32 _function_ `FString GetStringValueToDisplay(FUtf8StringView Value)` (scope `__anon806426440111`)
- L44 _function_ `bool TestTrue(const TCHAR* What, bool Value)` (scope `__anon806426440111`)
- L54 _function_ `bool TestTrue(const FString& What, bool Value)` (scope `__anon806426440111`)
- L59 _function_ `bool TestFalse(const TCHAR* What, bool Value)` (scope `__anon806426440111`)
- L69 _function_ `bool TestFalse(const FString& What, bool Value)` (scope `__anon806426440111`)
- L74 _function_ `bool TestEqual(const TCHAR* What, const int32 Actual, const int32 Expected)` (scope `__anon806426440111`)
- L84 _function_ `bool TestEqual(const TCHAR* What, const int64 Actual, const int64 Expected)` (scope `__anon806426440111`)
- L94 _function_ `bool TestEqual(const TCHAR* What, const SIZE_T Actual, const SIZE_T Expected)` (scope `__anon806426440111`)
- L104 _function_ `bool TestEqual(const TCHAR* What, const float Actual, const float Expected, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L114 _function_ `bool TestEqual(const TCHAR* What, const double Actual, const double Expected, double Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L124 _function_ `bool TestEqual(const TCHAR* What, const FVector Actual, const FVector Expected, float Tolerance)` (scope `__anon806426440111`)
- L134 _function_ `bool TestEqual(const TCHAR* What, const FTransform Actual, const FTransform Expected, float Tolerance)` (scope `__anon806426440111`)
- L144 _function_ `bool TestEqual(const TCHAR* What, const FRotator Actual, const FRotator Expected, float Tolerance)` (scope `__anon806426440111`)
- L154 _function_ `bool TestEqual(const TCHAR* What, const FColor Actual, const FColor Expected)` (scope `__anon806426440111`)
- L164 _function_ `bool TestEqual(const TCHAR* What, const FLinearColor Actual, const FLinearColor Expected)` (scope `__anon806426440111`)
- L174 _function_ `bool TestEqual(const TCHAR* What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L186 _function_ `bool TestEqual(const TCHAR* What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L197 _function_ `bool TestEqual(const TCHAR* What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L208 _function_ `bool TestEqualSensitive(const TCHAR* What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L220 _function_ `bool TestEqualSensitive(const TCHAR* What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L231 _function_ `bool TestEqualSensitive(const TCHAR* What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L243 _function_ `bool TestEqualInsensitive(const TCHAR* What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`) — `UE_DEPRECATED(5.5, "Use TestEqual instead (string tests are case insensitive by default)")`
- L248 _function_ `bool TestEqual(const FString& What, const int32 Actual, const int32 Expected)` (scope `__anon806426440111`)
- L253 _function_ `bool TestEqual(const FString& What, const float Actual, const float Expected, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L258 _function_ `bool TestEqual(const FString& What, const double Actual, const double Expected, double Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L263 _function_ `bool TestEqual(const FString& What, const FVector Actual, const FVector Expected, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L268 _function_ `bool TestEqual(const FString& What, const FTransform Actual, const FTransform Expected, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L273 _function_ `bool TestEqual(const FString& What, const FRotator Actual, const FRotator Expected, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `__anon806426440111`)
- L278 _function_ `bool TestEqual(const FString& What, const FColor Actual, const FColor Expected)` (scope `__anon806426440111`)
- L283 _function_ `bool TestEqual(const FString& What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L288 _function_ `bool TestEqual(const FString& What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L293 _function_ `bool TestEqual(const FString& What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L299 _function_ `template<typename ValueType> bool TestEqual(const TCHAR* What, const ValueType& Actual, const ValueType& Expected)` (scope `__anon806426440111`)
- L310 _function_ `template<typename ValueType> bool TestEqual(const FString& What, const ValueType& Actual, const ValueType& Expected)` (scope `__anon806426440111`)
- L315 _function_ `bool TestNotEqual(const TCHAR* What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L327 _function_ `bool TestNotEqual(const TCHAR* What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L338 _function_ `bool TestNotEqual(const TCHAR* What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L349 _function_ `bool TestNotEqualSensitive(const TCHAR* What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L361 _function_ `bool TestNotEqualSensitive(const TCHAR* What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L372 _function_ `bool TestNotEqualSensitive(const TCHAR* What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L383 _function_ `template<typename ValueType> bool TestNotEqual(const TCHAR* Description, const ValueType& Actual, const ValueType& Expected)` (scope `__anon806426440111`)
- L393 _function_ `bool TestNotEqual(const FString& What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L398 _function_ `bool TestNotEqual(const FString& What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L403 _function_ `bool TestNotEqual(const FString& What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L408 _function_ `bool TestNotEqualSensitive(const FString& What, const TCHAR* Actual, const TCHAR* Expected)` (scope `__anon806426440111`)
- L413 _function_ `bool TestNotEqualSensitive(const FString& What, FStringView Actual, FStringView Expected)` (scope `__anon806426440111`)
- L418 _function_ `bool TestNotEqualSensitive(const FString& What, FUtf8StringView Actual, FUtf8StringView Expected)` (scope `__anon806426440111`)
- L423 _function_ `template<typename ValueType> bool TestNotEqual(const FString& Description, const ValueType& Actual, const ValueType& Expected)` (scope `__anon806426440111`)
- L428 _macro_ `#define CHECK_EQUALS(What, X, Y) TestEqual(What, X, Y);`
- L429 _macro_ `#define CHECK_EQUALS_SENSITIVE(What, X, Y) TestEqualSensitive(What, X, Y);`
- L430 _macro_ `#define CHECK_NOT_EQUALS(What, X, Y) TestNotEqual(What, X, Y);`
- L431 _macro_ `#define CHECK_NOT_EQUALS_SENSITIVE(What, X, Y) TestNotEqualSensitive(What, X, Y);`

### `Source/Developer/LowLevelTestsRunner/Public/TestCommon/Initialization.h` (Public)


#### Free symbols / members of external scopes

- L5 _prototype_ `void SaveDefaultPlatformFile();`
- L6 _prototype_ `void UsePlatformFileStubIfRequired();`
- L7 _prototype_ `void UseDefaultPlatformFile();`
- L9 _prototype_ `void SetProjectNameAndDirectory();`
- L11 _prototype_ `void InitAllThreadPoolsEditorEx(bool MultiThreaded);`
- L13 _prototype_ `void InitOutputDevicesEx();`
- L15 _prototype_ `void InitStats();`
- L17 _prototype_ `void InitAll(bool bAllowLogging, bool bMultithreaded);`
- L19 _prototype_ `void CleanupLocalization();`
- L20 _prototype_ `void CleanupAll();`

### `Source/Developer/LowLevelTestsRunner/Public/TestHarness.h` (Public)


#### struct `Catch::StringMaker`  
``  
_L113-119_
- L115 _public function_ `static std::string convert(const TTuple<KeyType, ValueType>& Value)`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_ENABLE_TESTHARNESS_ENGINE_SUPPORT 1`
- L22 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const TCHAR* Value);`
- L23 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FString& Value);`
- L24 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FAnsiStringView& Value);`
- L25 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FWideStringView& Value);`
- L26 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FUtf8StringView& Value);`
- L27 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FAnsiStringBuilderBase& Value);`
- L28 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FWideStringBuilderBase& Value);`
- L29 _prototype_ `std::ostream& operator<<(std::ostream& Stream, const FUtf8StringBuilderBase& Value);`
- L36 _function_ `template <typename ObjectType, ESPMode Mode> std::ostream& operator<<(std::ostream& Stream, const TSharedRef<ObjectType, Mode>& Value)`
- L42 _function_ `template <typename ObjectType, ESPMode Mode> std::ostream& operator<<(std::ostream& Stream, const TSharedPtr<ObjectType, Mode>& Value)`
- L48 _function_ `template <typename KeyT, typename ValueT> inline bool operator==(const TMap<KeyT, ValueT>& Left, const TMap<KeyT, ValueT>& Right)`
- L89 _macro_ `#define LLT_CONCAT_(x, y) x##y`
- L90 _macro_ `#define LLT_CONCAT(x, y) LLT_CONCAT_(x,y)`
- L92 _macro_ `#define DISABLED_TEST_CASE_METHOD_INTERNAL(TestName, ClassName, ...) \`
- L105 _macro_ `#define DISABLED_TEST_CASE(...) static void LLT_CONCAT(disabled_test_,__LINE__)()`
- L106 _macro_ `#define DISABLED_TEST_CASE_METHOD(ClassName, ...) \`
- L108 _macro_ `#define DISABLED_SCENARIO(...) static void LLT_CONCAT(disabled_scenario_,__LINE__)()`
- L109 _macro_ `#define DISABLED_SECTION(...) auto LLT_CONCAT(disabled_section_,__LINE__) = []()`
- L121 _macro_ `#define TEST_CASE_NAMED(ClassName, ...) TEST_CASE(__VA_ARGS__)`
- L123 _macro_ `#define VERIFY(What, Actual)\`
- L127 _macro_ `#define ADD_WARNING(What)\`
- L130 _macro_ `#define ADD_ERROR(What)\`
- L133 _macro_ `#define FAIL_ON_MESSAGE(What)`
- L135 _macro_ `#define CHECK_EQUAL(Actual, Expected)\`
- L138 _macro_ `#define CHECK_NOT_EQUAL(Actual, Expected)\`
- L141 _macro_ `#define CHECK_MESSAGE(What, Value) do { \`
- L146 _macro_ `#define CHECK_FALSE_MESSAGE(What, Value) do { \`
- L151 _macro_ `#define REQUIRE_EQUAL(Actual, Expected)\`
- L154 _macro_ `#define REQUIRE_NOT_EQUAL(Actual, Expected)\`
- L157 _macro_ `#define REQUIRE_MESSAGE(What, Value) do { \`
- L162 _macro_ `#define TEST_TRUE(What, Value)\`
- L166 _macro_ `#define TEST_FALSE(What, Value)\`
- L170 _macro_ `#define TEST_IF_EQUAL(What, Actual, Expected)\`
- L174 _macro_ `#define TEST_EQUAL(What, Actual, Expected)\`
- L178 _macro_ `#define TEST_EQUAL_STR(What, Expected, Actual)\`
- L183 _macro_ `#define TEST_NOT_EQUAL(What, Actual, Expected)\`
- L187 _macro_ `#define TEST_NULL(What, Value)\`
- L191 _macro_ `#define TEST_NOT_NULL(What, Value)\`
- L195 _macro_ `#define TEST_VALID(What, Value)\`
- L199 _macro_ `#define TEST_INVALID(What, Value)\`

### `Source/Developer/LowLevelTestsRunner/Public/TestMacros/Assertions.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define REQUIRE_ENSURE(...) INTERNAL_UE_ENSURE( "REQUIRE_ENSURE", DO_ENSURE, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that an UE `ensure` fails in this call
- L12 _macro_ `#define REQUIRE_ENSURE_MSG(msg, ...) INTERNAL_UE_ENSURE_MSG(msg, "REQUIRE_ENSURE", DO_ENSURE, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that an UE `ensure` fails with a message that matches the supplied message
- L15 _macro_ `#define CHECK_ENSURE(...) INTERNAL_UE_ENSURE( "CHECK_ENSURE", DO_ENSURE, Catch::ResultDisposition::ContinueOnFailure, #__VA_ARGS__, __VA_ARGS__ )` — checks that an UE `ensure` fails in this call
- L18 _macro_ `#define CHECK_ENSURE_MSG(msg, ...) INTERNAL_UE_ENSURE_MSG(msg, "CHECK_ENSURE", DO_ENSURE, Catch::ResultDisposition::ContinueOnFailure, #__VA_ARGS__, __VA_ARGS__ )` — checks that an UE `ensure` fails with a message that matches the supplied message
- L21 _macro_ `#define REQUIRE_CHECK(...) INTERNAL_UE_CHECK( "REQUIRE_CHECK", DO_CHECK, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that a UE `check` fails in this call
- L24 _macro_ `#define REQUIRE_CHECK_MSG(msg, ...) INTERNAL_UE_CHECK_MSG(msg, "REQUIRE_CHECK", DO_CHECK, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that a UE `check` fails in this call contains the supplies message
- L27 _macro_ `#define REQUIRE_CHECK_SLOW(...) INTERNAL_UE_CHECK( "REQUIRE_CHECK_SLOW", DO_GUARD_SLOW, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that a UE `checkSlow` fails in this call
- L30 _macro_ `#define REQUIRE_CHECK_SLOW_MSG(msg, ...) INTERNAL_UE_CHECK_MSG(msg, "REQUIRE_CHECK_SLOW", DO_GUARD_SLOW, Catch::ResultDisposition::Normal, #__VA_ARGS__, __VA_ARGS__ )` — requires that a UE `checkSlow` fails in this call contains the supplies message
- L32 _macro_ `#define INTERNAL_UE_ENSURE( macroName, doEnsure, resultDisposition, ensureExpr, ... ) \`
- L45 _macro_ `#define INTERNAL_UE_ENSURE_MSG(msg, macroName, doEnsure, resultDisposition, ensureExpr, ... ) \`
- L58 _macro_ `#define INTERNAL_UE_CHECK(macroName, doCheck, resultDisposition, checkExpr, ... ) \`
- L71 _macro_ `#define INTERNAL_UE_CHECK_MSG(msg, macroName, doCheck, resultDisposition, checkExpr, ... ) \`

### `Source/Developer/LowLevelTestsRunner/Public/TestRunner.h` (Public)


#### class `FTestDelegates`  
`class FTestDelegates`  
_L34-54_
- L37 _public function_ `static FGlobalSetupHandler& GetGlobalSetup()`
- L43 _public function_ `static FGlobalSetupHandler& GetGlobalTeardown()`
- L49 _public function_ `static FGlobalPlatformSetupHandler& GetGlobalPlatformSetup()`

#### Free symbols / members of external scopes

- L25 _prototype_ `extern "C" const char* GetProcessExecutablePath()`
- L27 _prototype_ `const char* GetProcessExecutablePath();`
- L29 _prototype_ `const char* GetCacheDirectory();`
- L31 _delegate_ `DECLARE_DELEGATE(FGlobalSetupHandler);`
- L31 _prototype_ `DECLARE_DELEGATE(FGlobalSetupHandler);`
- L32 _delegate_ `DECLARE_DELEGATE(FGlobalPlatformSetupHandler);`
- L32 _prototype_ `DECLARE_DELEGATE(FGlobalPlatformSetupHandler);`
- L56 _prototype_ `int RunTests(int argc, const char* argv[]);`
