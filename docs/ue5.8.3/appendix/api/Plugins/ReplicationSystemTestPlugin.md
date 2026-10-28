# Plugins / ReplicationSystemTestPlugin

- module root: `Plugins/Runtime/ReplicationSystemTestPlugin/Source`
- headers: 7; symbols: 255
- symbol kinds: class=10, delegate=1, enum=1, enumerator=3, function=60, macro=95, member=16, namespace=18, prototype=49, struct=2
- PrivateDependencyModuleNames: Catch2, CoreUObject, Engine, LowLevelTestsRunner, NetCore
- PrivateIncludePathModuleNames: Catch2
- PublicDependencyModuleNames: Core, Projects

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Private/IrisTestMessageStreamOperators.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Net` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Net` (scope `UE`)
- L16 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, ENetFilterStatus);` (scope `UE::Net`)

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Private/NetworkAutomationTest.h` (Private)


#### struct `UE::Net::FNetworkAutomationTestStats`  
`struct FNetworkAutomationTestStats`  
_L16-20_
- L18 _public member_ `SIZE_T FailureCount;`
- L19 _public member_ `SIZE_T WarningCount;`

#### struct `UE::Net::FNetworkAutomationTestConfig`  
`struct FNetworkAutomationTestConfig`  
_L22-29_
- L24 _public function_ `static void SetVerboseLogging(bool bVerbose)`
- L25 _public function_ `static bool GetVerboseLogging()`
- L28 _private member_ `static bool bVerboseLogging;`

#### class `UE::Net::FNetworkAutomationTestSuiteFixture`  
`class FNetworkAutomationTestSuiteFixture`  
_L31-66_
- L34 _public prototype_ `virtual ~FNetworkAutomationTestSuiteFixture();`
- L36 _public prototype_ `virtual const TCHAR* GetName() const = 0;`
- L38 _public prototype_ `void RunTest();`
- L41 _protected prototype_ `FNetworkAutomationTestSuiteFixture();`
- L44 _protected prototype_ `virtual void SetUp();` — Run just before test case
- L47 _protected prototype_ `virtual void TearDown();` — Run just after test case
- L49 _protected prototype_ `virtual void RunTestImpl() = 0;`
- L52 _protected prototype_ `void SetSuppressWarningsFromSummary(bool bSuppress);` — Stats
- L54 _protected prototype_ `void AddTestFailure();`
- L55 _protected prototype_ `void AddTestWarning();`
- L58 _private prototype_ `void PreSetUp();`
- L59 _private prototype_ `void PostTearDown();`
- L64 _private member_ `FNetworkAutomationTestStats Stats = {};`
- L65 _private member_ `bool bSuppressWarningsFromSummary;`

#### class `UE::Net::FNetworkAutomationTestWrapper`  
`class FNetworkAutomationTestWrapper : private FAutomationTestBase`  
_L70-86_
- inherits: `FAutomationTestBase`
- L73 _public prototype_ `FNetworkAutomationTestWrapper(FNetworkAutomationTestSuiteFixture& TestSuite, const TCHAR* Name);`
- L76 _private prototype_ `virtual EAutomationTestFlags GetTestFlags() const override;`
- L77 _private prototype_ `virtual uint32 GetRequiredDeviceNum() const override;`
- L79 _private prototype_ `virtual FString GetBeautifiedTestName() const override;`
- L81 _private prototype_ `virtual void GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const override;`
- L82 _private prototype_ `virtual bool RunTest(const FString&) override;`
- L85 _private member_ `FNetworkAutomationTestSuiteFixture& TestSuite;`

#### class `UE::Net::TCatchFixtureWrapper`  
`template<class Fixture, const TCHAR* Name> class TCatchFixtureWrapper : public Fixture`  
_L98-115_
- inherits: `Fixture`
- L101 _public function_ `TCatchFixtureWrapper() : Fixture()`
- L107 _public function_ `~TCatchFixtureWrapper()`
- L113 _public function_ `virtual const TCHAR* GetName() const override`
- L114 _public function_ `virtual void RunTestImpl() override` — Unused in Catch-based tests

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Net` (scope `UE`)
- L94 _namespace_ `namespace UE`
- L94 _namespace_ `namespace Net` (scope `UE`)
- L119 _macro_ `#define UE_NET_TEST_CATCH_INTERNAL(TestSuite, TestCase, BaseClass) \`
- L123 _macro_ `#define UE_NET_TEST_FIXTURE(TestFixture, TestCase) UE_NET_TEST_CATCH_INTERNAL(TestFixture, TestCase, TestFixture)`
- L124 _macro_ `#define UE_NET_TEST(TestSuite, TestCase) UE_NET_TEST_CATCH_INTERNAL(TestSuite, TestCase, UE::Net::FNetworkAutomationTestSuiteFixture)`
- L131 _macro_ `#define UE_NET_TEST_INTERNAL(TestSuite, TestCase, BaseClass) \`
- L152 _macro_ `#define UE_NET_TEST(TestSuite, TestCase) UE_NET_TEST_INTERNAL(TestSuite, TestCase, UE::Net::FNetworkAutomationTestSuiteFixture)`
- L153 _macro_ `#define UE_NET_TEST_FIXTURE(TestFixture, TestCase) UE_NET_TEST_INTERNAL(TestFixture, TestCase, TestFixture)`
- L165 _macro_ `#define UE_NET_TEST(TestSuite, TestCase) UE_NET_TEST_INTERNAL(TestSuite, TestCase, FNetworkAutomationTestSuiteFixture)`

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Private/NetworkAutomationTestMacros.h` (Private)


#### class `UE::Net::FTestEnsureScope`  
`class FTestEnsureScope : public FEnsureScope`  
_L21-29_
- inherits: `FEnsureScope`
- L24 _public prototype_ `FTestEnsureScope();`
- L25 _public prototype_ `~FTestEnsureScope();`
- L28 _private member_ `bool bIgnoreDebugger;`

#### enum `UE::Net::ETestResult`  
`enum ETestResult`  
_L31-36_
- L33 _public enumerator_ `ETestResult_Success`
- L34 _public enumerator_ `ETestResult_Error`
- L35 _public enumerator_ `ETestResult_FatalError`

#### class `UE::Net::FTestResult`  
`class FTestResult`  
_L38-53_
- L41 _public function_ `template<typename T> FTestResult& operator<<(T Value)`
- L43 _public function_ `operator bool() const`
- L44 _public function_ `bool operator!() const`
- L46 _public function_ `FTestMessage& GetMessage()`
- L49 _protected prototype_ `FTestResult();`
- L51 _protected member_ `FTestMessage Message;`
- L52 _protected member_ `ETestResult TestResult;`

#### class `UE::Net::FTestMessageLog`  
`class FTestMessageLog`  
_L55-76_
- L58 _public prototype_ `FTestMessageLog(FNetworkAutomationTestSuiteFixture& Test, ELogVerbosity::Type LogVerbosity);`
- L61 _public function_ `template<typename T> FTestMessageLog(FNetworkAutomationTestSuiteFixture& InTest, ELogVerbosity::Type InLogVerbosity, const T& InMessage) : Test(InTest) , LogVerbosity(InLogVerbosity)`
- L68 _public prototype_ `~FTestMessageLog();`
- L70 _public prototype_ `void operator=(const FTestMessage&);`
- L73 _private member_ `FNetworkAutomationTestSuiteFixture& Test;`
- L74 _private member_ `FTestMessage Message;`
- L75 _private member_ `ELogVerbosity::Type LogVerbosity;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Net` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Net` (scope `UE`)
- L78 _prototype_ `FTestResult CreateTestSuccess();` (scope `UE::Net`)
- L79 _prototype_ `FTestResult CreateTestFailure();` (scope `UE::Net`)
- L82 _function_ `BooleanTestResult(bool Value, bool ExpectedValue, const char* ValueText)` (scope `UE::Net`)
- L96 _macro_ `#define UE_NET_COMPARE_RETURN_TESTRESULT(Name, Operator) \`
- L126 _macro_ `#define UE_NET_TEST_MSG_INTERNAL(Message) \`
- L131 _macro_ `#define UE_NET_ASSERT_EQ(V1, V2) REQUIRE(V1 == V2)`
- L132 _macro_ `#define UE_NET_ASSERT_NE(V1, V2) REQUIRE(V1 != V2)`
- L133 _macro_ `#define UE_NET_ASSERT_LT(V1, V2) REQUIRE(V1 < V2)`
- L134 _macro_ `#define UE_NET_ASSERT_LE(V1, V2) REQUIRE(V1 <= V2)`
- L135 _macro_ `#define UE_NET_ASSERT_GT(V1, V2) REQUIRE(V1 > V2)`
- L136 _macro_ `#define UE_NET_ASSERT_GE(V1, V2) REQUIRE(V1 >= V2)`
- L137 _macro_ `#define UE_NET_ASSERT_TRUE(V) REQUIRE(V)`
- L138 _macro_ `#define UE_NET_ASSERT_FALSE(V) REQUIRE_FALSE(V)`
- L140 _macro_ `#define UE_NET_ASSERT_EQ_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 == V2)`
- L141 _macro_ `#define UE_NET_ASSERT_NE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 != V2)`
- L142 _macro_ `#define UE_NET_ASSERT_LT_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 < V2)`
- L143 _macro_ `#define UE_NET_ASSERT_LE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 <= V2)`
- L144 _macro_ `#define UE_NET_ASSERT_GT_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 > V2)`
- L145 _macro_ `#define UE_NET_ASSERT_GE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V1 >= V2)`
- L146 _macro_ `#define UE_NET_ASSERT_TRUE_MSG(V, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE(V)`
- L147 _macro_ `#define UE_NET_ASSERT_FALSE_MSG(V, Message) UE_NET_TEST_MSG_INTERNAL(Message); REQUIRE_FALSE(V)`
- L149 _macro_ `#define UE_NET_EXPECT_EQ(V1, V2) CHECK(V1 == V2)`
- L150 _macro_ `#define UE_NET_EXPECT_NE(V1, V2) CHECK(V1 != V2)`
- L151 _macro_ `#define UE_NET_EXPECT_LT(V1, V2) CHECK(V1 < V2)`
- L152 _macro_ `#define UE_NET_EXPECT_LE(V1, V2) CHECK(V1 <= V2)`
- L153 _macro_ `#define UE_NET_EXPECT_GT(V1, V2) CHECK(V1 > V2)`
- L154 _macro_ `#define UE_NET_EXPECT_GE(V1, V2) CHECK(V1 >= V2)`
- L155 _macro_ `#define UE_NET_EXPECT_TRUE(V) CHECK(V)`
- L156 _macro_ `#define UE_NET_EXPECT_FALSE(V) CHECK_FALSE(V)`
- L158 _macro_ `#define UE_NET_EXPECT_EQ_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 == V2)`
- L159 _macro_ `#define UE_NET_EXPECT_NE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 != V2)`
- L160 _macro_ `#define UE_NET_EXPECT_LT_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 < V2)`
- L161 _macro_ `#define UE_NET_EXPECT_LE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 <= V2)`
- L162 _macro_ `#define UE_NET_EXPECT_GT_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 > V2)`
- L163 _macro_ `#define UE_NET_EXPECT_GE_MSG(V1, V2, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V1 >= V2)`
- L164 _macro_ `#define UE_NET_EXPECT_TRUE_MSG(V, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK(V)`
- L165 _macro_ `#define UE_NET_EXPECT_FALSE_MSG(V, Message) UE_NET_TEST_MSG_INTERNAL(Message); CHECK_FALSE(V)`
- L167 _macro_ `#define UE_NET_FAIL(Message) FAIL(Message)`
- L168 _macro_ `#define UE_NET_WARN(Message) FAIL_CHECK(Message)`
- L179 _macro_ `#define UE_NET_FAIL_MSG(Message) return UE_DEBUG_BREAK(), this->AddTestFailure(), UE::Net::FTestMessageLog(*this, ELogVerbosity::Error) = UE::Net::FTestMessage() << Message`
- L180 _macro_ `#define UE_NET_WARN_MSG(Message) this->AddTestWarning(), UE::Net::FTestMessageLog(*this, ELogVerbosity::Warning) = UE::Net::FTestMessage() << Message`
- L182 _macro_ `#define UE_NET_FAIL(Message) return UE_DEBUG_BREAK(), this->AddTestFailure(), void(UE::Net::FTestMessageLog(*this, ELogVerbosity::Error, Message))`
- L183 _macro_ `#define UE_NET_WARN(Message) this->AddTestWarning(), void(UE::Net::FTestMessageLog(*this, ELogVerbosity::Warning, Message))`
- L185 _macro_ `#define UE_NET_TEST_(CompareWithTestResult, V1, V2, FailFunction) if (UE::Net::FTestResult Result_ = CompareWithTestResult(V1, V2, #V1, #V2)) {} else FailFunction(Result_.GetMessage())`
- L186 _macro_ `#define UE_NET_ASSERT_INTERNAL_MSG(CompareWithTestResult, V1, V2) UE_NET_TEST_(CompareWithTestResult, V1, V2, UE_NET_FAIL_MSG)`
- L187 _macro_ `#define UE_NET_EXPECT_INTERNAL_MSG(CompareWithTestResult, V1, V2) UE_NET_TEST_(CompareWithTestResult, V1, V2, UE_NET_WARN_MSG)`
- L189 _macro_ `#define UE_NET_ASSERT_INTERNAL(CompareWithTestResult, V1, V2) UE_NET_TEST_(CompareWithTestResult, V1, V2, UE_NET_FAIL)`
- L190 _macro_ `#define UE_NET_EXPECT_INTERNAL(CompareWithTestResult, V1, V2) UE_NET_TEST_(CompareWithTestResult, V1, V2, UE_NET_WARN)`
- L192 _macro_ `#define UE_NET_TEST_BOOL_(V1, V2, FailFunction) if (UE::Net::FTestResult Result_ = UE::Net::BooleanTestResult(V1, V2, #V1)) {} else FailFunction(Result_.GetMessage())`
- L193 _macro_ `#define UE_NET_ASSERT_BOOL_INTERNAL_MSG(V1, V2) UE_NET_TEST_BOOL_(V1, V2, UE_NET_FAIL_MSG)`
- L194 _macro_ `#define UE_NET_EXPECT_BOOL_INTERNAL_MSG(V1, V2) UE_NET_TEST_BOOL_(V1, V2, UE_NET_WARN_MSG)`
- L196 _macro_ `#define UE_NET_ASSERT_BOOL_INTERNAL(V1, V2) UE_NET_TEST_BOOL_(V1, V2, UE_NET_FAIL)`
- L197 _macro_ `#define UE_NET_EXPECT_BOOL_INTERNAL(V1, V2) UE_NET_TEST_BOOL_(V1, V2, UE_NET_WARN)`
- L200 _macro_ `#define UE_NET_VALIDATE_CATCH_EXPR(V) (false ? (void)(Catch::Decomposer() <= V) : (void)0)` — Causes a build error if the tested expression isn't compatible with Catch/low-level tests, without evaluating the expression at runtime.
- L202 _macro_ `#define UE_NET_ASSERT_EQ(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 == V2); UE_NET_ASSERT_INTERNAL(TCmpEqual, V1, V2)`
- L203 _macro_ `#define UE_NET_ASSERT_NE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 != V2); UE_NET_ASSERT_INTERNAL(TCmpNotEqual, V1, V2)`
- L204 _macro_ `#define UE_NET_ASSERT_LT(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 < V2); UE_NET_ASSERT_INTERNAL(TCmpLess, V1, V2)`
- L205 _macro_ `#define UE_NET_ASSERT_LE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 <= V2); UE_NET_ASSERT_INTERNAL(TCmpLessOrEqual, V1, V2)`
- L206 _macro_ `#define UE_NET_ASSERT_GT(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 > V2); UE_NET_ASSERT_INTERNAL(TCmpGreater, V1, V2)`
- L207 _macro_ `#define UE_NET_ASSERT_GE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 >= V2); UE_NET_ASSERT_INTERNAL(TCmpGreaterOrEqual, V1, V2)`
- L208 _macro_ `#define UE_NET_ASSERT_TRUE(V) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_ASSERT_BOOL_INTERNAL(V, true)`
- L209 _macro_ `#define UE_NET_ASSERT_FALSE(V) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_ASSERT_BOOL_INTERNAL(V, false)`
- L211 _macro_ `#define UE_NET_ASSERT_EQ_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 == V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpEqual, V1, V2) << Message`
- L212 _macro_ `#define UE_NET_ASSERT_NE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 != V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpNotEqual, V1, V2) << Message`
- L213 _macro_ `#define UE_NET_ASSERT_LT_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 < V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpLess, V1, V2) << Message`
- L214 _macro_ `#define UE_NET_ASSERT_LE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 <= V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpLessOrEqual, V1, V2) << Message`
- L215 _macro_ `#define UE_NET_ASSERT_GT_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 > V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpGreater, V1, V2) << Message`
- L216 _macro_ `#define UE_NET_ASSERT_GE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 >= V2); UE_NET_ASSERT_INTERNAL_MSG(TCmpGreaterOrEqual, V1, V2) << Message`
- L217 _macro_ `#define UE_NET_ASSERT_TRUE_MSG(V, Message) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_ASSERT_BOOL_INTERNAL_MSG(V, true) << Message`
- L218 _macro_ `#define UE_NET_ASSERT_FALSE_MSG(V, Message) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_ASSERT_BOOL_INTERNAL_MSG(V, false) << Message`
- L220 _macro_ `#define UE_NET_EXPECT_EQ(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 == V2); UE_NET_EXPECT_INTERNAL(TCmpEqual, V1, V2)`
- L221 _macro_ `#define UE_NET_EXPECT_NE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 != V2); UE_NET_EXPECT_INTERNAL(TCmpNotEqual, V1, V2)`
- L222 _macro_ `#define UE_NET_EXPECT_LT(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 < V2); UE_NET_EXPECT_INTERNAL(TCmpLess, V1, V2)`
- L223 _macro_ `#define UE_NET_EXPECT_LE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 <= V2); UE_NET_EXPECT_INTERNAL(TCmpLessOrEqual, V1, V2)`
- L224 _macro_ `#define UE_NET_EXPECT_GT(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 > V2); UE_NET_EXPECT_INTERNAL(TCmpGreater, V1, V2)`
- L225 _macro_ `#define UE_NET_EXPECT_GE(V1, V2) UE_NET_VALIDATE_CATCH_EXPR(V1 >= V2); UE_NET_EXPECT_INTERNAL(TCmpGreaterOrEqual, V1, V2)`
- L226 _macro_ `#define UE_NET_EXPECT_TRUE(V) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_EXPECT_BOOL_INTERNAL(V, true)`
- L227 _macro_ `#define UE_NET_EXPECT_FALSE(V) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_EXPECT_BOOL_INTERNAL(V, false)`
- L229 _macro_ `#define UE_NET_EXPECT_EQ_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 == V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpEqual, V1, V2) << Message`
- L230 _macro_ `#define UE_NET_EXPECT_NE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 != V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpNotEqual, V1, V2) << Message`
- L231 _macro_ `#define UE_NET_EXPECT_LT_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 < V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpLess, V1, V2) << Message`
- L232 _macro_ `#define UE_NET_EXPECT_LE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 <= V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpLessOrEqual, V1, V2) << Message`
- L233 _macro_ `#define UE_NET_EXPECT_GT_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 > V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpGreater, V1, V2) << Message`
- L234 _macro_ `#define UE_NET_EXPECT_GE_MSG(V1, V2, Message) UE_NET_VALIDATE_CATCH_EXPR(V1 >= V2); UE_NET_EXPECT_INTERNAL_MSG(TCmpGreaterOrEqual, V1, V2) << Message`
- L235 _macro_ `#define UE_NET_EXPECT_TRUE_MSG(V, Message) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_EXPECT_BOOL_INTERNAL_MSG(V, true) << Message`
- L236 _macro_ `#define UE_NET_EXPECT_FALSE_MSG(V, Message) UE_NET_VALIDATE_CATCH_EXPR(V); UE_NET_EXPECT_BOOL_INTERNAL_MSG(V, false) << Message`
- L240 _macro_ `#define UE_NET_LOG(Message) FTestMessageLog(*this, ELogVerbosity::Display) = FTestMessage() << Message`
- L242 _macro_ `#define UE_NET_STRASSERT_EQ`
- L243 _macro_ `#define UE_NET_STRASSERT_NE`
- L244 _macro_ `#define UE_NET_STRCASEASSERT_EQ`
- L245 _macro_ `#define UE_NET_STRCASEASSERT_NE`

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Private/TestMessage.h` (Private)


#### class `UE::Net::FTestMessage`  
`class FTestMessage`  
_L24-39_
- L27 _public function_ `inline const TCHAR* C_Str() const`
- L28 _public function_ `inline const TCHAR* operator*() const`
- L30 _public function_ `inline FTestMessage& operator<<(const FString& InString)`
- L31 _public function_ `inline FTestMessage& operator<<(const TCHAR* InString)`
- L32 _public function_ `inline FTestMessage& operator<<(TCHAR Char)`
- L33 _public function_ `inline FTestMessage& operator<<(FStringBuilderBase& StringBuilder)`
- L35 _public function_ `inline FTestMessage& operator<<(const FTestMessage& Message)`
- L38 _private member_ `FString String;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Net` (scope `UE`)
- L41 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, int Value)` (scope `UE::Net`)
- L46 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, unsigned Value)` (scope `UE::Net`)
- L51 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, int8 Value)` (scope `UE::Net`)
- L56 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, int16 Value)` (scope `UE::Net`)
- L61 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, int64 Value)` (scope `UE::Net`)
- L66 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, uint8 Value)` (scope `UE::Net`)
- L71 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, uint16 Value)` (scope `UE::Net`)
- L76 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, uint64 Value)` (scope `UE::Net`)
- L81 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, const void* Value)` (scope `UE::Net`)
- L88 _function_ `template<typename T, typename = typename TEnableIf<std::is_same_v<T, uintptr_t> && !std::is_same_v<uintptr_t, unsigned> && !std::is_same_v<uintptr_t, uint64>, uintptr_t>::Type> inline FTestMessage& operator<<(FTestMessage& Message, T Value)` (scope `UE::Net`) — uintptr_t streaming
- L95 _function_ `template<typename T, typename = typename TEnableIf<std::is_same_v<T, ptrdiff_t>, ptrdiff_t>::Type, typename = typename TEnableIf<std::is_same_v<T, ptrdiff_t> && !std::is_same_v<ptrdiff_t, int32> && !std::is_same_v<ptrdiff_t, int64>, ptrdiff_t>::Type> inline FTestMessage& operator<<(FTestMessage& Message, T Value)` (scope `UE::Net`) — ptrdiff_t streaming
- L100 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, float Value)` (scope `UE::Net`)
- L105 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, double Value)` (scope `UE::Net`)
- L110 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, char Char)` (scope `UE::Net`)
- L115 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, bool Value)` (scope `UE::Net`)
- L120 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, TYPE_OF_NULLPTR)` (scope `UE::Net`)
- L125 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, const char* String)` (scope `UE::Net`)
- L130 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, const FName& Name)` (scope `UE::Net`)
- L135 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, const FVector& Vector)` (scope `UE::Net`)
- L140 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, const FVector3f& Vector)` (scope `UE::Net`)
- L145 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, const FNetHandle& NetHandle);` (scope `UE::Net`)
- L147 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, const FNetRefHandle& NetRefHandle);` (scope `UE::Net`)
- L149 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, const FNetToken& NetToken);` (scope `UE::Net`)
- L151 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, const FRemoteServerId& RemoteServerId);` (scope `UE::Net`)
- L153 _prototype_ `FTestMessage& operator<<(FTestMessage& Message, const FRemoteObjectId& RemoteObjectId);` (scope `UE::Net`)
- L156 _function_ `inline FTestMessage& operator<<(FTestMessage& Message, SIZE_T Value)` (scope `UE::Net`)
- L163 _function_ `template<typename T> inline FTestMessage& operator<<(FTestMessage& Message, const TObjectPtr<T>& ObjectPtr)` (scope `UE::Net`)

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Public/ReplicationSystemTestPlugin/HAL/UserSuppliedArchivePlatformFile.h` (Public)


#### class `FUserSuppliedArchivePlatformFile`  
`class FUserSuppliedArchivePlatformFile : public IPlatformFile`  
_L25-73_
- inherits: `IPlatformFile`
- desc: IPlatformFile implementation for use in tests. Register a non-owned FArchive under a virtual path with AddArchive. OpenRead returns a valid IFileHandle for any registered path. Each handle maintains its own read position by seeking the underlying archive before every read, so multiple handles opened on the same archive work correctly when used serially. Timestamps reported for registered paths are FDateTime::Now(). All operations on paths not present in the archive map are forwarded to the lower-level IPlatformFile.
- L28 _public function_ `FUserSuppliedArchivePlatformFile() : LowerLevel(nullptr)`
- L30 _public prototype_ `FUserSuppliedArchivePlatformFile(FUserSuppliedArchivePlatformFile&&) = delete;`
- L31 _public prototype_ `FUserSuppliedArchivePlatformFile& operator=(FUserSuppliedArchivePlatformFile&&) = delete;`
- L32 _public prototype_ `FUserSuppliedArchivePlatformFile(const FUserSuppliedArchivePlatformFile&) = delete;`
- L33 _public prototype_ `FUserSuppliedArchivePlatformFile& operator=(const FUserSuppliedArchivePlatformFile&) = delete;`
- L35 _public function_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override`
- L36 _public function_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override`
- L37 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L38 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L39 _public function_ `virtual const TCHAR* GetName() const override`
- L41 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) override;`
- L42 _public prototype_ `virtual int64 FileSize(const TCHAR* Filename) override;`
- L43 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L44 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L45 _public function_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override`
- L46 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L47 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L48 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L49 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L50 _public prototype_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;`
- L51 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L52 _public function_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override`
- L53 _public function_ `virtual bool DirectoryExists(const TCHAR* Directory) override`
- L54 _public function_ `virtual bool CreateDirectory(const TCHAR* Directory) override`
- L55 _public function_ `virtual bool DeleteDirectory(const TCHAR* Directory) override`
- L56 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L57 _public function_ `virtual bool IterateDirectory(const TCHAR* Directory, FDirectoryVisitor& Visitor) override`
- L58 _public function_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, FDirectoryStatVisitor& Visitor) override`
- L61 _public prototype_ `void AddArchive(const TCHAR* Filename, FArchive* Archive);` — Register a non-owned FArchive under a virtual file path.
- L64 _private function_ `static FString NormalizePath(const TCHAR* Filename)`
- L71 _private member_ `IPlatformFile* LowerLevel;`
- L72 _private member_ `TMap<FString, FArchive*> Archives;`

#### class `FScopedUserSuppliedArchivePlatformFile`  
`class FScopedUserSuppliedArchivePlatformFile`  
_L82-104_
- desc: RAII helper that installs an FUserSuppliedArchivePlatformFile at the top of the platform file chain and restores the original chain on destruction. FArchive objects registered via AddArchive are served by OpenRead for the duration of the scope.
- L85 _public function_ `FScopedUserSuppliedArchivePlatformFile()`
- L92 _public function_ `~FScopedUserSuppliedArchivePlatformFile()`
- L97 _public function_ `void AddArchive(const TCHAR* Filename, FArchive* Archive)`
- L103 _private member_ `FUserSuppliedArchivePlatformFile PlatformFile;`

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Public/ReplicationSystemTestPlugin/NetworkAutomationTest.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkAutomationTest, Display, All) namespace UE::Net { void PrintNetworkAutomationTestSummary(); }`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Net` (scope `UE`)
- L12 _prototype_ `void PrintNetworkAutomationTestSummary();` (scope `UE::Net`)

### `Plugins/Runtime/ReplicationSystemTestPlugin/Source/Public/ReplicationSystemTestPlugin/ReplicationSystemTestPlugin.h` (Public)


#### class `IReplicationSystemTestPlugin`  
`class IReplicationSystemTestPlugin : public IModuleInterface`  
_L14-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IReplicationSystemTestPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
