# Programs / HeadlessChaosPerf

- module root: `Source/Programs/HeadlessChaosPerf`
- headers: 4; symbols: 31
- symbol kinds: class=3, delegate=1, function=14, macro=4, member=6, namespace=1, prototype=2
- PrivateDependencyModuleNames: ApplicationCore, ChaosVehiclesCore, Core, CoreUObject, GeometryCore, GoogleTest, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/HeadlessChaosPerf/Private/ChaosPerf/ChaosPerf.h` (Private)
_(no declarations extracted)_

### `Source/Programs/HeadlessChaosPerf/Private/ChaosPerf/ChaosPerfLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosPerf, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosPerf, Verbose, All);`

### `Source/Programs/HeadlessChaosPerf/Private/ChaosPerf/ChaosPerfProfiling.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CSV_DEFINE_CATEGORY(ChaosPerf, true);`

### `Source/Programs/HeadlessChaosPerf/Private/ChaosPerf/ChaosPerfTest.h` (Private)


#### class `ChaosPerf::FPerfTest`  
`class FPerfTest`  
_L12-109_
- desc: Base class for a one-shot perf test (i.e., no frame subdivisions in the output data)
- L15 _public function_ `virtual ~FPerfTest()`
- L20 _protected function_ `FPerfTest(const FString& InTestName)`
- L27 _protected function_ `virtual void CreateTest()` — Override to do setup outside of the timing capture
- L29 _protected function_ `virtual void RunTest()`
- L32 _protected function_ `virtual void DestroyTest()` — Override to do teardown outside of the timing capture
- L37 _private function_ `void Run()`
- L44 _private function_ `void SetUp()`
- L62 _private function_ `void TearDown()`
- L79 _private function_ `void StartCapture()` — CSV Profiler is intended to be used for frame-based profiling with a Game Thread, Render Thread and possibly other threads. We need to do some Begin/EndFrame shenanigans to fool it into working for one-shot tests. NOTE: Most methods on CSV Profiler put evbenmts into a queue and that queue is only processed in EndFrame()
- L90 _private function_ `void StopCapture()`
- L104 _private member_ `FCsvProfiler* CSVProfiler;`
- L105 _private member_ `FString TestName;`
- L106 _private member_ `FString FilenamePrefix;`
- L107 _private member_ `FString Filename;`
- L108 _private member_ `FString RootFolder;`

#### class `ChaosPerf::FPerfTestRegistry`  
`class FPerfTestRegistry`  
_L113-137_
- desc: A registry of all the tests in the program
- L116 _public function_ `static FPerfTestRegistry& Get()`
- L122 _public function_ `void Add(const TSharedPtr<FPerfTest>& Test)`
- L127 _public function_ `void RunAll()`
- L136 _private member_ `TArray<TSharedPtr<FPerfTest>> Tests;`

#### class `ChaosPerf::FPerfTestRegistrar`  
`class FPerfTestRegistrar`  
_L141-148_
- desc: A utlity object for registering tests with the registry
- L144 _public function_ `FPerfTestRegistrar(const TSharedPtr<FPerfTest>& Test)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ChaosPerf`
- L150 _macro_ `#define CHAOSPERF_TEST_BASEIMPL(BASE_CLASS, TEST_CLASS, TEST_NAME) \`
- L162 _macro_ `#define CHAOSPERF_TEST_BASE(BASE_CLASS, TEST_NAME) CHAOSPERF_TEST_BASEIMPL(BASE_CLASS, FPerfTest_ ## TEST_NAME, TEST_NAME)`
- L181 _macro_ `#define CHAOSPERF_TEST_BASIC(CAT_ID, TEST_ID) CHAOSPERF_TEST_BASE(FPerfTest, CAT_ID ## TEST_ID)` — Simple test macro for tests which require no setup (or the setup cost is negligible) E.g., CHAOSPERF_TEST(MyPerfTests, TestSomethingsPerf) { for (int32 Index = 0; Index < 1000000; ++Index) { static int32 Count = 0; ++Count; } } This will create a custom class for the test derived from FPerfTest and the code in the braces following the macro is the implementation of RunTest(). If you also need custom setup and shutdown, see CHAOSPERF_TEST_CUSTOM
- L184 _macro_ `#define CHAOSPERF_TEST_CUSTOM(TEST_BASE, CAT_ID, TEST_ID) CHAOSPERF_TEST_BASE(TEST_BASE, CAT_ID ## TEST_ID)`
