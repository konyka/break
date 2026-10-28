# Developer / CQTest

- module root: `Source/Developer/CQTest`
- headers: 22; symbols: 632
- symbol kinds: class=18, enum=2, enumerator=5, externvar=2, function=215, macro=44, member=94, namespace=11, prototype=170, struct=34, typedef=28, variable=9
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings, LevelEditor, NetCore, Slate, UnrealEd
- PublicDependencyModuleNames: DeveloperSettings

### `Source/Developer/CQTest/Public/Assert/CQTestCondition.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace CQTestCondition`
- L14 _function_ `template <typename TValue, typename TOtherValue> inline bool IsEqual(const TValue& A, const TOtherValue& B)` (scope `CQTestCondition`)
- L19 _function_ `inline bool IsEqual(const TCHAR* A, const TCHAR* B)` (scope `CQTestCondition`)
- L23 _function_ `inline bool IsEqual(const TCHAR* A, const FString& B)` (scope `CQTestCondition`)
- L27 _function_ `inline bool IsEqual(const FString& A, const TCHAR* B)` (scope `CQTestCondition`)
- L31 _function_ `inline bool IsEqual(const FString& A, const FString& B)` (scope `CQTestCondition`)
- L36 _function_ `inline bool IsEqualIgnoreCase(const TCHAR* A, const TCHAR* B)` (scope `CQTestCondition`)
- L40 _function_ `inline bool IsEqualIgnoreCase(const TCHAR* A, const FString& B)` (scope `CQTestCondition`)
- L44 _function_ `inline bool IsEqualIgnoreCase(const FString& A, const TCHAR* B)` (scope `CQTestCondition`)
- L48 _function_ `inline bool IsEqualIgnoreCase(const FString& A, const FString& B)` (scope `CQTestCondition`)
- L56 _function_ `template <typename TValue, typename TOtherValue> inline bool IsNotEqual(const TValue& A, const TOtherValue& B)` (scope `CQTestCondition`)
- L61 _function_ `inline bool IsNotEqual(const TCHAR* A, const TCHAR* B)` (scope `CQTestCondition`)
- L65 _function_ `inline bool IsNotEqual(const TCHAR* A, const FString& B)` (scope `CQTestCondition`)
- L69 _function_ `inline bool IsNotEqual(const FString& A, const TCHAR* B)` (scope `CQTestCondition`)
- L73 _function_ `inline bool IsNotEqual(const FString& A, const FString& B)` (scope `CQTestCondition`)
- L78 _function_ `inline bool IsNotEqualIgnoreCase(const TCHAR* A, const TCHAR* B)` (scope `CQTestCondition`)
- L82 _function_ `inline bool IsNotEqualIgnoreCase(const TCHAR* A, const FString& B)` (scope `CQTestCondition`)
- L86 _function_ `inline bool IsNotEqualIgnoreCase(const FString& A, const TCHAR* B)` (scope `CQTestCondition`)
- L90 _function_ `inline bool IsNotEqualIgnoreCase(const FString& A, const FString& B)` (scope `CQTestCondition`)
- L97 _function_ `inline bool IsNearlyEqual(const float A, const float B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L101 _function_ `inline bool IsNearlyEqual(const double A, const double B, double Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L105 _function_ `inline bool IsNearlyEqual(const FVector A, const FVector B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L109 _function_ `inline bool IsNearlyEqual(const FTransform A, const FTransform B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L113 _function_ `inline bool IsNearlyEqual(const FRotator A, const FRotator B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L118 _function_ `inline bool IsNotNearlyEqual(const float A, const float B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L122 _function_ `inline bool IsNotNearlyEqual(const double A, const double B, double Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L126 _function_ `inline bool IsNotNearlyEqual(const FVector A, const FVector B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L130 _function_ `inline bool IsNotNearlyEqual(const FTransform A, const FTransform B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)
- L134 _function_ `inline bool IsNotNearlyEqual(const FRotator A, const FRotator B, float Tolerance = UE_KINDA_SMALL_NUMBER)` (scope `CQTestCondition`)

### `Source/Developer/CQTest/Public/Assert/CQTestConvert.h` (Public)


#### struct `__anon33af16c80111::THasToString`  
`template <typename T, typename = void> struct THasToString : std::false_type`  
_L19-21_
- inherits: `std::false_type`

#### struct `__anon33af16c80111::THasToString`  
`template<typename T> struct THasToString<T, std::void_t<decltype(std::declval<T>().ToString())>> : std::is_same<FString, decltype(std::declval<T>().ToString())>::type`  
_L24-27_
- inherits: `std::is_same<FString,decltype(std::declval<T>().ToString())>::type`

#### class `__anon33af16c80111::THasOStream`  
`template<typename T> class THasOStream`  
_L30-39_
- L33 _private prototype_ `template <typename C, typename = decltype(operator<<(std::declval<CQTestConvert::PrintStream&>(), std::declval<C>()))> static std::true_type test(int);`
- L35 _private prototype_ `template<typename C> static std::false_type test(...);`
- L38 _public member_ `static constexpr bool value = decltype(test<T>(0))::value;`

#### struct `__anon33af16c80111::StructWithToString`  
`struct StructWithToString`  
_L45-50_
- L47 _public function_ `FString ToString()`

#### struct `__anon33af16c80111::StructWithConstToString`  
`struct StructWithConstToString`  
_L52-57_
- L54 _public function_ `FString ToString() const`

#### struct `__anon33af16c80111::StructWithToStringWrongReturnType`  
`struct StructWithToStringWrongReturnType`  
_L62-65_
- L64 _public function_ `int ToString()`

#### struct `__anon33af16c80111::SomeTestStruct`  
`struct SomeTestStruct`  
_L69-71_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace CQTestConvert`
- L13 _typedef_ `using PrintStream = TStringBuilder<64>;` (scope `CQTestConvert`)
- L17 _namespace_ `namespace (anonymous)`
- L78 _namespace_ `namespace CQTestConvert`
- L81 _function_ `template <typename T> inline FString ToString(const T& Input)` (scope `CQTestConvert`)
- L116 _function_ `template <> inline FString ToString(const FString& Input)` (scope `CQTestConvert`)
- L122 _function_ `template<typename TElement, typename TAllocator> inline FString ToString(const TArray<TElement, TAllocator>& Input)` (scope `CQTestConvert`)
- L124 _function_ `FString result = FString::JoinBy(Input, TEXT(", "), [](const TElement& e) { return CQTestConvert::ToString(e); });` (scope `CQTestConvert::ToString`)
- L131 _function_ `template <typename TElement, typename TAllocator> inline FString ToString(const TSet<TElement, TAllocator>& Input)` (scope `CQTestConvert`)
- L140 _function_ `template<typename TKey, typename TValue> inline FString ToString(const TMap<TKey, TValue>& Input)` (scope `CQTestConvert`)
- L142 _function_ `return FString::JoinBy(Input, TEXT(", "), [](const auto& kvp) { return TEXT("{") + CQTestConvert::ToString(kvp.Key) + TEXT(":") + CQTestConvert::ToString(kvp.Value) + TEXT("}"); });` (scope `CQTestConvert::ToString`)
- L148 _function_ `template<typename TInnerType> inline FString ToString(const TOptional<TInnerType>& Input)` (scope `CQTestConvert`)

### `Source/Developer/CQTest/Public/Assert/NoDiscardAsserter.h` (Public)


#### struct `FNoDiscardAsserter`  
`struct FNoDiscardAsserter`  
_L7-107_
- L10 _protected member_ `FAutomationTestBase& TestRunner;`
- L13 _public function_ `explicit FNoDiscardAsserter(FAutomationTestBase& TestRunner) : TestRunner(TestRunner)`
- L16 _public prototype_ `void ExpectError(FString Error, int32 Count = 1);`
- L17 _public prototype_ `void ExpectErrorRegex(FString Error, int32 Count = 1);`
- L19 _public prototype_ `void Fail(FString error);`
- L21 _public prototype_ `[[nodiscard]] bool IsTrue(bool Condition);`
- L22 _public prototype_ `[[nodiscard]] bool IsTrue(bool Condition, const char* FailureMessage);`
- L23 _public prototype_ `[[nodiscard]] bool IsTrue(bool Condition, const TCHAR* FailureMessage);`
- L24 _public prototype_ `[[nodiscard]] bool IsTrue(bool Condition, const FString& FailureMessage);`
- L26 _public prototype_ `[[nodiscard]] bool IsFalse(bool Condition);`
- L27 _public prototype_ `[[nodiscard]] bool IsFalse(bool Condition, const char* FailureMessage);`
- L28 _public prototype_ `[[nodiscard]] bool IsFalse(bool Condition, const TCHAR* FailureMessage);`
- L29 _public prototype_ `[[nodiscard]] bool IsFalse(bool Condition, const FString& FailureMessage);`
- L32 _public prototype_ `template <typename T> [[nodiscard]] bool IsNull(const T& Ptr);`
- L35 _public prototype_ `template <typename T> [[nodiscard]] bool IsNull(const T& Ptr, const char* FailureMessage);`
- L38 _public prototype_ `template <typename T> [[nodiscard]] bool IsNull(const T& Ptr, const TCHAR* FailureMessage);`
- L41 _public prototype_ `template <typename T> [[nodiscard]] bool IsNull(const T& Ptr, const FString& FailureMessage);`
- L44 _public prototype_ `template <typename T> [[nodiscard]] bool IsNotNull(const T& Ptr);`
- L47 _public prototype_ `template <typename T> [[nodiscard]] bool IsNotNull(const T& Ptr, const char* FailureMessage);`
- L50 _public prototype_ `template <typename T> [[nodiscard]] bool IsNotNull(const T& Ptr, const TCHAR* FailureMessage);`
- L53 _public prototype_ `template <typename T> [[nodiscard]] bool IsNotNull(const T& Ptr, const FString& FailureMessage);`
- L56 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreEqual(const TExpected& Expected, const TActual& Actual);`
- L59 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreEqual(const TExpected& Expected, const TActual& Actual, const char* FailureMessage);`
- L62 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreEqual(const TExpected& Expected, const TActual& Actual, const TCHAR* FailureMessage);`
- L65 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreEqual(const TExpected& Expected, const TActual& Actual, const FString& FailureMessage);`
- L67 _public prototype_ `[[nodiscard]] bool AreEqualIgnoreCase(const FString& Expected, const FString& Actual);`
- L69 _public prototype_ `[[nodiscard]] bool AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const char* FailureMessage);`
- L71 _public prototype_ `[[nodiscard]] bool AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const TCHAR* FailureMessage);`
- L73 _public prototype_ `[[nodiscard]] bool AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const FString& FailureMessage);`
- L75 _public prototype_ `[[nodiscard]] bool AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual);`
- L77 _public prototype_ `[[nodiscard]] bool AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const char* FailureMessage);`
- L79 _public prototype_ `[[nodiscard]] bool AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const TCHAR* FailureMessage);`
- L81 _public prototype_ `[[nodiscard]] bool AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const FString& FailureMessage);`
- L84 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreNotEqual(const TExpected& Expected, const TActual& Actual);`
- L87 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreNotEqual(const TExpected& Expected, const TActual& Actual, const char* FailureMessage);`
- L90 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreNotEqual(const TExpected& Expected, const TActual& Actual, const TCHAR* FailureMessage);`
- L93 _public prototype_ `template <typename TExpected, typename TActual> [[nodiscard]] bool AreNotEqual(const TExpected& Expected, const TActual& Actual, const FString& FailureMessage);`
- L96 _public prototype_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] bool IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon);`
- L99 _public prototype_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] bool IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const char* FailureMessage);`
- L102 _public prototype_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] bool IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const TCHAR* FailureMessage);`
- L105 _public prototype_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] bool IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const FString& FailureMessage);`

### `Source/Developer/CQTest/Public/Assert/NoDiscardAsserter.inl` (Public)


#### Free symbols / members of external scopes

- L7 _function_ `inline void FNoDiscardAsserter::ExpectError(FString Error, int32 Count)` (scope `FNoDiscardAsserter`)
- L12 _function_ `inline void FNoDiscardAsserter::ExpectErrorRegex(FString Error, int32 Count)` (scope `FNoDiscardAsserter`)
- L17 _function_ `FORCEINLINE void FNoDiscardAsserter::Fail(FString Error)` (scope `FNoDiscardAsserter`)
- L22 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsTrue(bool Condition)` (scope `FNoDiscardAsserter`)
- L27 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsTrue(bool Condition, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L32 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsTrue(bool Condition, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L37 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsTrue(bool Condition, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L47 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsFalse(bool Condition)` (scope `FNoDiscardAsserter`)
- L52 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsFalse(bool Condition, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L57 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsFalse(bool Condition, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L62 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsFalse(bool Condition, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L73 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNull(const T& Ptr)` (scope `FNoDiscardAsserter`)
- L79 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNull(const T& Ptr, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L85 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNull(const T& Ptr, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L91 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNull(const T& Ptr, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L102 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNotNull(const T& Ptr)` (scope `FNoDiscardAsserter`)
- L108 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNotNull(const T& Ptr, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L114 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNotNull(const T& Ptr, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L120 _function_ `template <typename T> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNotNull(const T& Ptr, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L131 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqual(const TExpected& Expected, const TActual& Actual)` (scope `FNoDiscardAsserter`)
- L137 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqual(const TExpected& Expected, const TActual& Actual, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L143 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqual(const TExpected& Expected, const TActual& Actual, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L149 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqual(const TExpected& Expected, const TActual& Actual, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L162 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqualIgnoreCase(const FString& Expected, const FString& Actual)` (scope `FNoDiscardAsserter`)
- L167 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L172 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L177 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreEqualIgnoreCase(const FString& Expected, const FString& Actual, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L188 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqual(const TExpected& Expected, const TActual& Actual)` (scope `FNoDiscardAsserter`)
- L194 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqual(const TExpected& Expected, const TActual& Actual, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L200 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqual(const TExpected& Expected, const TActual& Actual, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L206 _function_ `template <typename TExpected, typename TActual> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqual(const TExpected& Expected, const TActual& Actual, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L219 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual)` (scope `FNoDiscardAsserter`)
- L224 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L229 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L234 _function_ `[[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::AreNotEqualIgnoreCase(const FString& Expected, const FString& Actual, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)
- L245 _function_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon)` (scope `FNoDiscardAsserter`)
- L251 _function_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const char* FailureMessage)` (scope `FNoDiscardAsserter`)
- L257 _function_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const TCHAR* FailureMessage)` (scope `FNoDiscardAsserter`)
- L263 _function_ `template <typename TExpected, typename TActual, typename TEpsilon> [[nodiscard]] FORCEINLINE bool FNoDiscardAsserter::IsNear(TExpected Expected, TActual Actual, TEpsilon Epsilon, const FString& FailureMessage)` (scope `FNoDiscardAsserter`)

### `Source/Developer/CQTest/Public/CQTest.h` (Public)


#### enum `ECQTestSuppressLogBehavior`  
`enum class ECQTestSuppressLogBehavior`  
_L60-65_
- L62 _public enumerator_ `Default`
- L63 _public enumerator_ `True`
- L64 _public enumerator_ `False`

#### struct `TBaseTest`  
`template <typename InAsserterType> struct TBaseTest`  
_L80-138_
- L82 _public typedef_ `using AsserterType = InAsserterType;`
- L84 _public prototype_ `TBaseTest(FAutomationTestBase& TestRunner, bool bInitializing);`
- L85 _public prototype_ `TBaseTest(const TBaseTest<AsserterType>& other) = delete;`
- L86 _public prototype_ `TBaseTest& operator=(const TBaseTest<AsserterType>& rhs) = delete;`
- L88 _public prototype_ `virtual ~TBaseTest() = default;`
- L90 _public function_ `virtual void Setup()`
- L92 _public function_ `virtual void TearDown()`
- L95 _public prototype_ `void AddCommand(IAutomationLatentCommand* Cmd);` — The framework expects you to pass a 'new' command, which it will own and destroy
- L96 _public prototype_ `void AddCommand(TSharedPtr<IAutomationLatentCommand> Cmd);`
- L103 _public prototype_ `void AddError(const FString& InError) const;` — Adds an error message to this test @param	InError	Error message to add to this test
- L112 _public prototype_ `bool AddErrorIfFalse(bool bCondition, const FString& InError) const;` — Adds an error message to this test if the condition is false @param   bCondition	The condition to validate. @param   InError		Error message to add to this test @return	False if there was an error
- L119 _public prototype_ `void AddWarning(const FString& InWarning) const;` — Adds a warning to this test @param	InWarning	Warning message to add to this test
- L126 _public prototype_ `void AddInfo(const FString& InLogItem) const;` — Adds a log item to this test @param	InLogItem	Log item to add to this test
- L128 _public prototype_ `virtual void RunTest(const FString& MethodName) = 0;`
- L130 _public member_ `bool bInitializing{ true };`
- L132 _public member_ `BeforeAfterAllFunc BeforeAllFunc = nullptr;`
- L133 _public member_ `BeforeAfterAllFunc AfterAllFunc = nullptr;`
- L135 _public member_ `FAutomationTestBase& TestRunner;`
- L136 _public member_ `AsserterType Assert;`
- L137 _public member_ `FTestCommandBuilder TestCommandBuilder;`

#### struct `TTestRunner`  
`template <typename InAsserterType> struct TTestRunner : public FAutomationTestBase`  
_L147-199_
- inherits: `FAutomationTestBase`
- L149 _public typedef_ `using AsserterType = InAsserterType;`
- L151 _public prototype_ `TTestRunner(FString Name, int32 LineNumber, const char* FileName, FString TestDir, EAutomationTestFlags TestFlags, TTestInstanceGenerator<AsserterType> Factory, FString TestTags);`
- L152 _public prototype_ `~TTestRunner();`
- L154 _public prototype_ `EAutomationTestFlags GetTestFlags() const override;`
- L155 _public prototype_ `FString GetTestSourceFileName() const override;`
- L156 _public prototype_ `int32 GetTestSourceFileLine() const override;`
- L157 _public prototype_ `int32 GetTestSourceFileLine(const FString& Name) const override;`
- L158 _public prototype_ `bool SuppressLogWarnings() override;`
- L159 _public prototype_ `bool SuppressLogErrors() override;`
- L160 _public prototype_ `void GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const override;`
- L162 _public prototype_ `bool RunTest(const FString& RequestedTest) override;`
- L164 _public prototype_ `virtual void SetSuppressLogWarnings(ECQTestSuppressLogBehavior Behavior = ECQTestSuppressLogBehavior::True);`
- L165 _public prototype_ `virtual void SetSuppressLogErrors(ECQTestSuppressLogBehavior Behavior = ECQTestSuppressLogBehavior::True);`
- L167 _public function_ `const FString GetTestTags() const`
- L168 _public function_ `const FString GetTestMethodTags(const FString& MethodName) const`
- L174 _public prototype_ `FString GetBeautifiedTestName() const override;`
- L176 _public member_ `int32 LineNumber = 0;`
- L177 _public member_ `FString FileName;`
- L178 _public member_ `FString TestDir;`
- L179 _public member_ `EAutomationTestFlags TestFlags{ DefaultFlags };`
- L180 _public member_ `bool bInitializing{ true };`
- L182 _public member_ `TUniquePtr<TBaseTest<AsserterType>> CurrentTestPtr;`
- L183 _public member_ `TArray<FString> TestNames;`
- L184 _public member_ `TMap<FString, int32> TestLineNumbers{};`
- L185 _public member_ `TTestInstanceGenerator<AsserterType> TestInstanceFactory;`
- L186 _public member_ `FDelegateHandle BeforeAllDelegate{};`
- L187 _public member_ `FDelegateHandle AfterAllDelegate{};`
- L189 _public prototype_ `TTestRunner() = delete;`
- L192 _protected prototype_ `uint32 GetRequiredDeviceNum() const override;`
- L194 _protected member_ `ECQTestSuppressLogBehavior SuppressLogWarningsBehavior{ ECQTestSuppressLogBehavior::Default };`
- L195 _protected member_ `ECQTestSuppressLogBehavior SuppressLogErrorsBehavior{ ECQTestSuppressLogBehavior::Default };`
- L198 _private member_ `FString TestTags;`

#### struct `TTest`  
`template <typename Derived, typename AsserterType> struct TTest : TBaseTest<AsserterType>`  
_L202-260_
- inherits: `TBaseTest<AsserterType>`
- L204 _public typedef_ `using TestMethod = void (Derived::*)();`
- L205 _public typedef_ `using DerivedType = Derived;`
- L207 _public function_ `TTest() : TBaseTest<AsserterType>(*Derived::TestRunner, Derived::TestRunner->bInitializing)`
- L220 _public prototype_ `void RunTest(const FString& TestName) override;`
- L252 _public function_ `static TUniquePtr<TBaseTest<AsserterType>> CreateTestClass(TTestRunner<AsserterType>& TestRunnerInstance)`
- L258 _public member_ `inline static TMap<FString, TestMethod> Methods{};`
- L259 _public member_ `inline static TTestRunner<AsserterType>* TestRunner{ nullptr };`

#### struct `TTest::FFunctionRegistrar`  
`struct FFunctionRegistrar`  
_L222-250_
- L224 _public function_ `FFunctionRegistrar(FString Name, TestMethod Func, int32 LineNumber, FString TestTags)`
- L247 _public function_ `const FString GetTestMethodTags() const`
- L249 _private member_ `FString MethodTags;`

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace TestDirectoryGenerator`
- L57 _prototype_ `FString Generate(const FString& Filename);` (scope `TestDirectoryGenerator`)
- L67 _externvar_ `extern const FString GenerateTestDirectory;`
- L68 _externvar_ `extern const FString DefaultTags;`
- L69 _variable_ `static constexpr EAutomationTestFlags DefaultFlags = EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter;`
- L77 _typedef_ `using BeforeAfterAllFunc = void(*)(const FString&);`
- L144 _typedef_ `template <typename InAsserterType> using TTestInstanceGenerator = TUniquePtr<TBaseTest<InAsserterType>>(*)(TTestRunner<InAsserterType>&);`
- L264 _macro_ `#define _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, _BaseClass, _AsserterType, _TestFlags, _TestTags) \`
- L284 _macro_ `#define _TEST_CLASS_IMPL(_ClassName, _TestDir, _BaseClass, _AsserterType, _TestFlags) \`
- L287 _macro_ `#define TEST_METHOD_WITH_TAGS(_MethodName, _TestTags) \`
- L291 _macro_ `#define TEST_METHOD(_MethodName) TEST_METHOD_WITH_TAGS(_MethodName, DefaultTags)`
- L297 _macro_ `#define _TEST_CLASS_IMPL(_ClassName, _TestDir, _BaseClass, _AsserterType, _TestFlags) _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, _BaseClass, _AsserterType, _TestFlags, DefaultTags)`
- L299 _macro_ `#define TEST_METHOD_WITH_TAGS(_MethodName, _TestTags) void _MethodName()`
- L303 _macro_ `#define TEST_CLASS_WITH_ASSERTS(_ClassName, _TestDir, _AsserterType) _TEST_CLASS_IMPL(_ClassName, _TestDir, TTest, _AsserterType, DefaultFlags)`
- L304 _macro_ `#define TEST_CLASS_WITH_ASSERTS_AND_TAGS(_ClassName, _TestDir, _AsserterType, _TestTags) _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, TTest, _AsserterType, DefaultFlags, _TestTags)`
- L305 _macro_ `#define TEST_CLASS(_ClassName, _TestDir) TEST_CLASS_WITH_ASSERTS(_ClassName, _TestDir, FNoDiscardAsserter)`
- L306 _macro_ `#define TEST_CLASS_WITH_TAGS(_ClassName, _TestDir, _TestTags) TEST_CLASS_WITH_ASSERTS_AND_TAGS(_ClassName, _TestDir, FNoDiscardAsserter, _TestTags)`
- L307 _macro_ `#define TEST_CLASS_WITH_BASE(_ClassName, _TestDir, _BaseClass) _TEST_CLASS_IMPL(_ClassName, _TestDir, _BaseClass, FNoDiscardAsserter, DefaultFlags)`
- L308 _macro_ `#define TEST_CLASS_WITH_BASE_AND_TAGS(_ClassName, _TestDir, _BaseClass, _TestTags) _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, _BaseClass, FNoDiscardAsserter, DefaultFlags, _TestTags)`
- L309 _macro_ `#define TEST_CLASS_WITH_BASE_AND_ASSERTS(_ClassName, _TestDir, _BaseClass, _AsserterType) _TEST_CLASS_IMPL(_ClassName, _TestDir, _BaseClass, _AsserterType, DefaultFlags)`
- L310 _macro_ `#define TEST_CLASS_WITH_FLAGS(_ClassName, _TestDir, _Flags) _TEST_CLASS_IMPL(_ClassName, _TestDir, TTest, FNoDiscardAsserter, _Flags)`
- L311 _macro_ `#define TEST_CLASS_WITH_FLAGS_AND_TAGS(_ClassName, _TestDir, _Flags, _TestTags) _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, TTest, FNoDiscardAsserter, _Flags, _TestTags)`
- L312 _macro_ `#define TEST_CLASS_WITH_BASE_AND_FLAGS(_ClassName, _TestDir, _BaseClass, _Flags) _TEST_CLASS_IMPL(_ClassName, _TestDir, _BaseClass, FNoDiscardAsserter, _Flags)`
- L313 _macro_ `#define TEST_CLASS_WITH_BASE_AND_FLAGS_AND_TAGS(_ClassName, _TestDir, _BaseClass, _Flags, _TestTags) _TEST_CLASS_IMPL_EXT(_ClassName, _TestDir, _BaseClass, FNoDiscardAsserter, _Flags, _TestTags)`
- L315 _macro_ `#define TEST(_TestName, _TestDir) \`
- L322 _macro_ `#define TEST_WITH_TAGS(_TestName, _TestDir, _TestTags) \`
- L329 _macro_ `#define ASSERT_THAT(_assertion) if (!this->Assert._assertion) {return;}`
- L330 _macro_ `#define ASSERT_FAIL(_Msg) this->Assert.Fail(_Msg); return;`
- L332 _macro_ `#define BEFORE_ALL() static void BeforeAll(const FString&)`
- L333 _macro_ `#define BEFORE_EACH() virtual void Setup() override`
- L334 _macro_ `#define AFTER_EACH() virtual void TearDown() override`
- L335 _macro_ `#define AFTER_ALL() static void AfterAll(const FString&)`

### `Source/Developer/CQTest/Public/CQTestSettings.h` (Public)


#### class `UCQTestSettings`  
`class UCQTestSettings : public UDeveloperSettingsBackedByCVars`  
_L29-67_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "CQ Test Settings"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: Implements per project Engine settings for the CQTest plugin.
- L34 _public function_ `void PostInitProperties() override`
- L47 _public member_ `float CommandTimeout = CQTestConsoleVariables::CommandTimeout;` — `UPROPERTY(config, EditAnywhere, Category = "Test Settings", meta = (ConsoleVariable = "TestFramework.CQTest.CommandTimeout"))` — Timeout for WaitUntil latent actions.
- L51 _public member_ `float NetworkTimeout = CQTestConsoleVariables::NetworkTimeout;` — `UPROPERTY(config, EditAnywhere, Category = "Test Settings", meta = (ConsoleVariable = "TestFramework.CQTest.CommandTimeout.Network"))` — Timeout for WaitUntil latent actions from the PIENetworkComponent.
- L55 _public member_ `float MapTestTimeout = CQTestConsoleVariables::MapTestTimeout;` — `UPROPERTY(config, EditAnywhere, Category = "Test Settings", meta = (ConsoleVariable = "TestFramework.CQTest.CommandTimeout.MapTest"))` — Timeout for `FMapTestSpawner::AddWaitUntilLoadedCommand` latent action used during UWorld loading.
- L66 _public prototype_ `[[nodiscard]] static TSharedPtr<FScopedTestEnvironment> SetTestClassTimeouts(FTimespan Duration);` — Sets the duration for all available timeouts @param Duration - Duration of the timeout. @return shared pointer to the FScopedTestEnvironment singleton instance @note Console Variable will reset back to the value prior to getting set once the FScopedTestEnvironment resets or gets destructed.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CQTEST_API`
- L15 _namespace_ `namespace CQTestConsoleVariables`
- L17 _variable_ `inline static constexpr float CommandTimeout = 10.0f;` (scope `CQTestConsoleVariables`)
- L18 _variable_ `constexpr auto CommandTimeoutName = TEXT("Tes` (scope `CQTestConsoleVariables`)
- L20 _variable_ `inline static constexpr float NetworkTimeout = 30.0f;` (scope `CQTestConsoleVariables`)
- L21 _variable_ `constexpr auto NetworkTimeoutName = TEXT("Tes` (scope `CQTestConsoleVariables`)
- L23 _variable_ `inline static constexpr float MapTestTimeout = 30.0f;` (scope `CQTestConsoleVariables`)
- L24 _variable_ `constexpr auto MapTestTimeoutName = TEXT("Tes` (scope `CQTestConsoleVariables`)

### `Source/Developer/CQTest/Public/Commands/TestCommandBuilder.h` (Public)


#### class `FTestCommandBuilder`  
`class FTestCommandBuilder`  
_L9-243_
- L12 _public function_ `FTestCommandBuilder(FAutomationTestBase& InTestRunner) : TestRunner(InTestRunner)`
- L15 _public function_ `~FTestCommandBuilder()`
- L20 _public function_ `FTestCommandBuilder& Do(const TCHAR* Description, TFunction<void()> Action)`
- L29 _public function_ `FTestCommandBuilder& Do(TFunction<void()> Action)`
- L34 _public function_ `FTestCommandBuilder& Then(TFunction<void()> Action)`
- L39 _public function_ `FTestCommandBuilder& Then(const TCHAR* Description, TFunction<void()> Action)`
- L44 _public function_ `FTestCommandBuilder& Until(const TCHAR* Description, TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L53 _public function_ `FTestCommandBuilder& Until(TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L59 _public function_ `template <typename ResultType> FTestCommandBuilder& DoAsync(const TCHAR* Description, TFunction<TAsyncResult<ResultType>()> AsyncAction, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L69 _public function_ `template <typename ResultType> FTestCommandBuilder& DoAsync(TFunction<TAsyncResult<ResultType>()> AsyncAction, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L75 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type DoAsync( const TCHAR* Description, TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L89 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type DoAsync( TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L98 _public function_ `template <typename ResultType> FTestCommandBuilder& ThenAsync(const TCHAR* Description, TFunction<TAsyncResult<ResultType>()> AsyncAction, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L104 _public function_ `template <typename ResultType> FTestCommandBuilder& ThenAsync(TFunction<TAsyncResult<ResultType>()> AsyncAction, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L110 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type ThenAsync( const TCHAR* Description, TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L120 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type ThenAsync( TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L129 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type UntilAsync( const TCHAR* Description, TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<bool(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> AsyncActionTimeout = CQTest::DefaultTimeout, TOptional<FTimespan> ConditionTimeout = CQTest::DefaultTimeout)`
- L144 _public function_ `template <typename ResultType> typename TEnableIf<!std::is_void_v<ResultType>, FTestCommandBuilder&>::Type UntilAsync( TFunction<TAsyncResult<ResultType>()> AsyncAction, TFunction<bool(typename TAsyncResultCallbackArg<ResultType>::Type)> ResultCallback, TOptional<FTimespan> AsyncActionTimeout = CQTest::DefaultTimeout, TOptional<FTimespan> ConditionTimeout = CQTest::DefaultTimeout)`
- L153 _public function_ `FTestCommandBuilder& StartWhen(TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L158 _public function_ `FTestCommandBuilder& StartWhen(const TCHAR* Description, TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`
- L164 _public function_ `FTestCommandBuilder& WaitDelay(FTimespan Timeout)` — Note that using a timed-wait can introduce test flakiness due to variable runtimes. Please consider using `Until` and waiting until something happens instead.
- L170 _public function_ `FTestCommandBuilder& WaitDelay(const TCHAR* Description, FTimespan Timeout)` — Note that using a timed-wait can introduce test flakiness due to variable runtimes. Please consider using `Until` and waiting until something happens instead.
- L179 _public function_ `FTestCommandBuilder& OnTearDown(const TCHAR* Description, TFunction<void()> Action)`
- L188 _public function_ `FTestCommandBuilder& OnTearDown(TFunction<void()> Action)`
- L193 _public function_ `FTestCommandBuilder& CleanUpWith(const TCHAR* Description, TFunction<void()> Action)`
- L198 _public function_ `FTestCommandBuilder& CleanUpWith(TFunction<void()> Action)`
- L203 _public function_ `TSharedPtr<IAutomationLatentCommand> Build()`
- L208 _public function_ `TSharedPtr<IAutomationLatentCommand> BuildTearDown()`
- L216 _private function_ `TSharedPtr<IAutomationLatentCommand> BuildQueue(TArray<TSharedPtr<IAutomationLatentCommand>>& Queue)`
- L237 _protected member_ `TArray<TSharedPtr<IAutomationLatentCommand>> CommandQueue{};`
- L238 _protected member_ `TArray<TSharedPtr<IAutomationLatentCommand>> TearDownQueue{};`
- L239 _protected member_ `FAutomationTestBase& TestRunner;`

### `Source/Developer/CQTest/Public/Commands/TestCommands.h` (Public)


#### class `FWaitUntil`  
`class FWaitUntil : public IAutomationLatentCommand`  
_L16-37_
- inherits: `IAutomationLatentCommand`
- desc: Latent Command that waits until the Query evaluates to `true` or the timeout has exceeded.
- L19 _public function_ `FWaitUntil(FAutomationTestBase& InTestRunner, TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout, const TCHAR* InDescription = nullptr) : TestRunner(InTestRunner) , Query(MoveTemp(Query)) , Timeout(MakeTimeout(Timeout)) , Description(InDescription)`
- L26 _public prototype_ `bool Update() override;`
- L28 _public member_ `FAutomationTestBase& TestRunner;`
- L29 _public member_ `TFunction<bool()> Query;`
- L30 _public member_ `FTimespan Timeout;`
- L31 _public member_ `FDateTime StartTime;`
- L32 _public member_ `const TCHAR* Description;`
- L33 _public member_ `bool bHasTimerStarted = false;`
- L36 _private prototype_ `FTimespan MakeTimeout(TOptional<FTimespan> InTimeout);`

#### class `FWaitDelay`  
`class FWaitDelay : public IAutomationLatentCommand`  
_L42-58_
- inherits: `IAutomationLatentCommand`
- desc: Latent Command that waits a set time frame. Note that using a timed-wait can introduce test flakiness due to variable runtimes. Please consider using `FWaitUntil` and waiting until something happens instead.
- L45 _public function_ `FWaitDelay(FAutomationTestBase& InTestRunner, FTimespan Timeout, const TCHAR* InDescription = nullptr) : TestRunner(InTestRunner) , Timeout(Timeout) , Description(InDescription)`
- L51 _public prototype_ `bool Update() override;`
- L53 _public member_ `FAutomationTestBase& TestRunner;`
- L54 _public member_ `FTimespan Timeout;`
- L55 _public member_ `FDateTime EndTime;`
- L56 _public member_ `const TCHAR* Description;`
- L57 _public member_ `bool bHasTimerStarted = false;`

#### enum `ECQTestFailureBehavior`  
`enum class ECQTestFailureBehavior`  
_L60-64_
- L62 _public enumerator_ `Skip`
- L63 _public enumerator_ `Run`

#### class `FExecute`  
`class FExecute : public IAutomationLatentCommand`  
_L67-83_
- inherits: `IAutomationLatentCommand`
- desc: Latent Command which executes the provided function.
- L70 _public function_ `FExecute(FAutomationTestBase& InTestRunner, TFunction<void()> Func, const TCHAR* InDescription = nullptr, ECQTestFailureBehavior InFailureBehavior = ECQTestFailureBehavior::Skip) : TestRunner(InTestRunner) , Func(MoveTemp(Func)) , Description(InDescription) , FailureBehavior(InFailureBehavior)`
- L77 _public prototype_ `bool Update() override;`
- L79 _public member_ `FAutomationTestBase& TestRunner;`
- L80 _public member_ `TFunction<void()> Func;`
- L81 _public member_ `const TCHAR* Description = nullptr;`
- L82 _public member_ `ECQTestFailureBehavior FailureBehavior;`

#### class `FRunSequence`  
`class FRunSequence : public IAutomationLatentCommand`  
_L86-112_
- inherits: `IAutomationLatentCommand`
- desc: Latent Command which manages and executes an array of latent commands.
- L89 _public function_ `FRunSequence(const TArray<TSharedPtr<IAutomationLatentCommand>>& ToAdd) : Commands(ToAdd)`
- L95 _public function_ `template <class... Cmds> FRunSequence(Cmds... Commands) : FRunSequence(TArray<TSharedPtr<IAutomationLatentCommand>>{ Commands... })`
- L100 _public prototype_ `void Append(TSharedPtr<IAutomationLatentCommand> ToAdd);`
- L101 _public prototype_ `void AppendAll(TArray < TSharedPtr<IAutomationLatentCommand>> ToAdd);`
- L102 _public prototype_ `void Prepend(TSharedPtr<IAutomationLatentCommand> ToAdd);`
- L104 _public function_ `bool IsEmpty() const`
- L109 _public prototype_ `bool Update() override;`
- L111 _public member_ `TArray<TSharedPtr<IAutomationLatentCommand>> Commands;`

#### struct `TAsyncResultCallbackArg`  
`template <typename ResultType> struct TAsyncResultCallbackArg`  
_L115-118_
- L117 _public typedef_ `using Type = decltype(std::declval<TAsyncResult<ResultType>>().GetFuture().Get());`

#### class `AsyncExecuteDetails::TResultCommandFactory`  
`template <typename ResultType> class TResultCommandFactory<ResultType, FExecute>`  
_L138-155_
- desc: This class provides a helper function for creating a FExecute command to handle the result of an async operation.
- L140 _private function_ `static TSharedRef<IAutomationLatentCommand> Create( FAutomationTestBase& TestRunner, TAsyncResult<ResultType>& AsyncResult, TArray<FString>& OutDescriptions, const TCHAR* BaseDescription, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)>&& InFunc)`
- L161 _private function_ `static TSharedRef<IAutomationLatentCommand> Create( FAutomationTestBase& TestRunner, TAsyncResult<ResultType>& AsyncResult, TArray<FString>& OutDescriptions, const TCHAR* BaseDescription, TFunction<bool(typename TAsyncResultCallbackArg<ResultType>::Type)>&& InFunc, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`

#### class `AsyncExecuteDetails::TResultCommandFactory`  
`template <typename ResultType> class TResultCommandFactory<ResultType, FWaitUntil>`  
_L159-178_
- desc: This class provides a helper function for creating a FWaitUntil command to handle the result of an async operation.
- L140 _private function_ `static TSharedRef<IAutomationLatentCommand> Create( FAutomationTestBase& TestRunner, TAsyncResult<ResultType>& AsyncResult, TArray<FString>& OutDescriptions, const TCHAR* BaseDescription, TFunction<void(typename TAsyncResultCallbackArg<ResultType>::Type)>&& InFunc)`
- L161 _private function_ `static TSharedRef<IAutomationLatentCommand> Create( FAutomationTestBase& TestRunner, TAsyncResult<ResultType>& AsyncResult, TArray<FString>& OutDescriptions, const TCHAR* BaseDescription, TFunction<bool(typename TAsyncResultCallbackArg<ResultType>::Type)>&& InFunc, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout)`

#### class `TAsyncExecute`  
`template <typename ResultType, typename ResultCommandType = void> class TAsyncExecute : public IAutomationLatentCommand`  
_L183-228_
- inherits: `IAutomationLatentCommand`
- desc: Latent Command that executes an async action and optionally processes the result in a Latent Command of the specified type.
- L187 _public function_ `template<typename... ResultCommandArgs> TAsyncExecute( FAutomationTestBase& TestRunner, TFunction<TAsyncResult<ResultType>()> AsyncAction, TOptional<FTimespan> AsyncActionTimeout = CQTest::DefaultTimeout, const TCHAR* Description = nullptr, ResultCommandArgs&&... Args )`
- L222 _public function_ `bool Update() override`
- L225 _private member_ `FRunSequence RunSequence;`
- L226 _private member_ `TAsyncResult<ResultType> AsyncResult;`
- L227 _private member_ `TArray<FString> Descriptions;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CQTEST_API`
- L10 _namespace_ `namespace CQTest`
- L12 _variable_ `inline static const TOptional<FTimespan> DefaultTimeout = NullOpt;` (scope `CQTest`)
- L124 _namespace_ `namespace AsyncExecuteDetails`
- L126 _function_ `static const TCHAR* CreateInternalCommandDescription(TArray<FString>& OutDescriptions, const TCHAR* External, const TCHAR* Internal)` (scope `AsyncExecuteDetails`)
- L149 _function_ `TestRunner, [&Result = AsyncResult, Func = MoveTemp(InFunc)]()` (scope `AsyncExecuteDetails::TResultCommandFactory::Create`)
- L197 _function_ `TestRunner, [&Result = AsyncResult, Action = MoveTemp(AsyncAction)]()` (scope `TAsyncExecute::TAsyncExecute`)
- L202 _function_ `TestRunner, [&Result = AsyncResult]()` (scope `TAsyncExecute::TAsyncExecute`)

### `Source/Developer/CQTest/Public/Commands/TestMacros.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define TEST_EQ(Left, Right) TestRunner->TestEqual(TEXT(#Left "==" #Right), Left, Right)`
- L6 _macro_ `#define TEST_TRUE(Condition) TestRunner->TestTrue(TEXT(#Condition), Condition)`
- L7 _macro_ `#define ADD_ERROR(Error) TestRunner->AddError(Error)`
- L8 _macro_ `#define TEST_ERROR(Error) TestRunner->AddExpectedError(Error)`
- L10 _macro_ `#define DO(Cmd) TestCommandBuilder.Do([&]() { Cmd })`
- L11 _macro_ `#define START_WHEN(Query) TestCommandBuilder.StartWhen([&]() { Query })`
- L12 _macro_ `#define WAIT_DELAY(Duration) TestCommandBuilder.WaitDelay(Duration)`
- L13 _macro_ `#define THEN(Cmd) Then([&]() { Cmd })`
- L14 _macro_ `#define UNTIL(Query) Until([&]() { Query })`

### `Source/Developer/CQTest/Public/Components/ActorTestSpawner.h` (Public)


#### struct `FActorTestSpawner`  
`struct FActorTestSpawner : public FSpawnHelper`  
_L36-54_
- inherits: `FSpawnHelper`
- desc: Class for spawning actors in an ActorTest context(no PIE loaded)
- L38 _public prototype_ `FActorTestSpawner() = default;`
- L43 _public prototype_ `void InitializeGameSubsystems();` — Initialize the GameSubsystem for the test world.
- L46 _public prototype_ `UTestGameInstance* GetGameInstance();` — Returns a pointer to the test game instance.
- L50 _protected prototype_ `virtual UWorld* CreateWorld() override;` — Returns a newly created world.
- L53 _private member_ `UTestGameInstance* GameInstance{ nullptr };`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CQTEST_API`

### `Source/Developer/CQTest/Public/Components/CQTestBlueprintHelper.h` (Public)


#### struct `FCQTestBlueprintHelper`  
`struct UE_DEPRECATED(5.5, "Use Helpers/CQTestAssetHelper.h instead") FCQTestBlueprintHelper`  
_L33-58_
- desc: Utilities for working with Blueprint in C++ Tests
- L45 _public prototype_ `UObject* FindDataBlueprint(const FString& Directory, const FString& Name);` — Finds the UObject given a directory and asset name to find. @param Directory - Directory path where the asset resides. @param Name - Name of the asset. @return pointer to the UObject that was found and loaded, returns nullptr if no object was found @note Method uses a static cache to store information regarding directories and assets.
- L57 _public prototype_ `UClass* GetBlueprintClass(const FString& Directory, const FString& Name);` — Gets the UClass of a UObject loaded from a given directory and asset name. @param Directory - Directory path where the asset resides. @param Name - Name of the asset. @return pointer of the blueprint's generated class @note Method guarantees that the UClass returned is valid, will assert otherwise.

### `Source/Developer/CQTest/Public/Components/CQTestSlateComponent.h` (Public)


#### class `FCQTestSlateComponent`  
`class FCQTestSlateComponent`  
_L38-74_
- desc: CQTest component for interacting with Slate
- L41 _public prototype_ `FCQTestSlateComponent();`
- L42 _public prototype_ `~FCQTestSlateComponent();`
- L54 _public prototype_ `bool HaveTicksElapsed(uint32 Ticks);` — Initializes the ExpectedTick variable to be checked against the amount of times Slate has ticked. Will be used to check Slate has ticked the expected amount before confirming and resetting the ExpectedTick. @param Ticks - Number of ticks we're expecting to have elapsed @return true when Slate has ticked the provided number of times. @note Method is meant to be used as the only statement within a latent command that waits until the predicate is met, such as FWaitUntil, Until, or StartWhen methods.
- L57 _public function_ `uint32 GetTotalElapsedTicks()` — Returns the total elapsed ticks since creation.
- L68 _private prototype_ `void OnPostTick([[maybe_unused]] const float InDeltaTime);` — Called on Slate's Post Tick @param InDeltaTime - Elapsed time since the last tick. While the value is not being used directly, it is needed to register for Slate's delegate.
- L70 _private member_ `std::atomic<uint32> TickCounter{0};`
- L71 _private member_ `TOptional<uint32> ExpectedTick;`
- L72 _private member_ `FDelegateHandle TickDelegateHandle;`
- L73 _private member_ `TSharedPtr<struct FScopedTestEnvironment> TestEnvironment;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CQTEST_API`

### `Source/Developer/CQTest/Public/Components/MapTestSpawner.h` (Public)


#### struct `FMapTestSpawner`  
`struct FMapTestSpawner : public FSpawnHelper`  
_L49-100_
- inherits: `FSpawnHelper`
- desc: Class for spawning Actors in a named Map / Level
- L57 _public function_ `FMapTestSpawner(const FString& MapDirectory, const FString& MapName) : MapDirectory(MapDirectory), MapName(MapName)` — Construct the MapTestSpawner. @param MapDirectory - The directory which the map resides in. @param MapName - Name of the map.
- L61 _public prototype_ `~FMapTestSpawner();` — Destructor
- L70 _public prototype_ `static TUniquePtr<FMapTestSpawner> CreateFromTempLevel(FTestCommandBuilder& InCommandBuilder);` — Creates an instance of the MapTestSpawner with a temporary level ready for use. @param InCommandBuilder - Test Command Builder used to assist with setup. @return unique instance of the FMapTestSpawner, nullptr otherwise
- L81 _public prototype_ `void AddWaitUntilLoadedCommand(FAutomationTestBase* TestRunner, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Loads the map specified from the MapDirectory and MapName to be prepared for the test. @param TestRunner - TestRunner used to send the latent command needed for map preparations. @param Timeout - Duration that the latent command can execute before reporting an error. @note Must be called outside of a latent action. Preferably within BEFORE_TEST. @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.MapTest` CVar.
- L86 _public prototype_ `APawn* FindFirstPlayerPawn();` — Finds the first pawn in the given map.
- L90 _protected prototype_ `virtual UWorld* CreateWorld() override;` — Returns a newly created world.
- L94 _private prototype_ `void OnEndPlayMap();` — Handler called when the PIE session ends.
- L96 _private member_ `FString MapDirectory;`
- L97 _private member_ `FString MapName;`
- L98 _private member_ `UWorld* PieWorld{ nullptr };`
- L99 _private member_ `FDelegateHandle EndPlayMapHandle;`

### `Source/Developer/CQTest/Public/Components/PIENetworkComponent.h` (Public)


#### struct `FBasePIENetworkComponentState`  
`struct FBasePIENetworkComponentState`  
_L71-93_
- desc: Struct which handles the PIE session's world and network information. Both the server and client will keep a reference to their own respective state which will be tested against.
- L74 _public prototype_ `virtual ~FBasePIENetworkComponentState() = default;` — Default virtual destructor.
- L77 _public member_ `UWorld* World = nullptr;` — Reference to the session's world.
- L80 _public member_ `TArray<UNetConnection*> ClientConnections;` — Used by the server to reference the connections to the client.
- L83 _public member_ `int32 ClientIndex = INDEX_NONE;` — Used by the client to reference location within the `ClientConnections` array on the server.
- L86 _public member_ `int32 ClientCount = 2;` — Used by the server for creating and validation of client instances.
- L89 _public member_ `bool bIsDedicatedServer = true;` — Used by the server to create a PIE session as a dedicated or listen server.
- L92 _public member_ `TSet<UE::Net::FNetIDVariant> LocallySpawnedActors{};` — Used to track spawned and replicated actors across client and server PIE sessions.

#### class `FBasePIENetworkComponent`  
`class FBasePIENetworkComponent`  
_L99-258_
- desc: Component which creates and initializes the server and client network connections between the PIE sessions. The component also provides methods around the CommandBuilder for adding latent commands.
- L113 _public prototype_ `FBasePIENetworkComponent(FAutomationTestBase* InTestRunner, FTestCommandBuilder& InCommandBuilder, bool IsInitializing, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Construct the BasePIENetworkComponent. @param InTestRunner - Pointer to the TestRunner used for test reporting. @param InCommandBuilder - Reference to the latent command manager. @param IsInitializing - Bool specifying if the Automation framework is still being initialized. @param Timeout - Duration that the latent command can execute before reporting an error. @note Requires that the `FBasePIENetworkComponent` is built using the `FNetworkComponentBuilder` as this will setup the server and client `FBasePIENetworkComponentState` @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L122 _public prototype_ `FBasePIENetworkComponent& Then(TFunction<void()> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame. @param Action - Function to be executed. @return a reference to this
- L132 _public prototype_ `FBasePIENetworkComponent& Then(const TCHAR* Description, TFunction<void()> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame. @param Description - Description of the provided function to be logged. @param Action - Function to be executed. @return a reference to this
- L141 _public prototype_ `FBasePIENetworkComponent& Do(TFunction<void()> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame. @param Action - Function to be executed. @return a reference to this
- L151 _public prototype_ `FBasePIENetworkComponent& Do(const TCHAR* Description, TFunction<void()> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame. @param Description - Description of the provided function to be logged. @param Action - Function to be executed. @return a reference to this
- L164 _public prototype_ `FBasePIENetworkComponent& Until(TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note Will continue to execute until the function provided evaluates to `true` or the duration exceeds the specified timeout. @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L178 _public prototype_ `FBasePIENetworkComponent& Until(const TCHAR* Description, TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout. @param Description - Description of the provided function to be logged. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note Will continue to execute until the function provided evaluates to `true` or the duration exceeds the specified timeout. @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L191 _public prototype_ `FBasePIENetworkComponent& StartWhen(TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note Will continue to execute until the function provided evaluates to `true` or the duration exceeds the specified timeout. @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L205 _public prototype_ `FBasePIENetworkComponent& StartWhen(const TCHAR* Description, TFunction<bool()> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout. @param Description - Description of the provided function to be logged. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note Will continue to execute until the function provided evaluates to `true` or the duration exceeds the specified timeout. @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L209 _protected prototype_ `void StopPie();` — Prepares the active PIE sessions to be stopped.
- L212 _protected prototype_ `void StartPie();` — Setup settings for a network session and start PIE sessions for both the server and client with the network settings applied.
- L221 _protected prototype_ `bool SetWorlds();` — Fetch all of the worlds that will be used for the networked session. @return true if an error was encountered or if the PIE sessions were created with the correct network settings, false otherwise. @note Method is expected to be used within the `Until` latent command to then wait until the worlds are ready for use.
- L224 _protected prototype_ `void SetPacketSettings() const;` — Sets the packet settings used to simulate packet behavior over a network.
- L227 _protected prototype_ `void ConnectClientsToServer();` — Connects all available clients to the server.
- L236 _protected prototype_ `bool AwaitClientsReady() const;` — Go through all of the client connections to make sure they are connected and ready. @return true if an error was encountered or if the connections all have a valid controller, false otherwise. @note Method is expected to be used within the `Until` latent command to then wait until the worlds are ready for use.
- L239 _protected prototype_ `void RestoreState();` — Restore back to the state prior to test execution.
- L248 _protected prototype_ `FTimespan MakeTimeout(TOptional<FTimespan> Timeout);` — Creates a timeout to be used. @param Timeout - Duration that the latent command can execute before reporting an error. @return either the FTimespan specified or the value from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L250 _protected member_ `TUniquePtr<FBasePIENetworkComponentState> ServerState = nullptr;`
- L251 _protected member_ `TArray<TUniquePtr<FBasePIENetworkComponentState>> ClientStates;`
- L252 _protected member_ `FAutomationTestBase* TestRunner = nullptr;`
- L253 _protected member_ `FTestCommandBuilder* CommandBuilder = nullptr;`
- L254 _protected member_ `FPacketSimulationSettings* PacketSimulationSettings = nullptr;`
- L255 _protected member_ `TSubclassOf<AGameModeBase> GameMode = TSubclassOf<AGameModeBase>(nullptr);`
- L256 _protected member_ `FPIENetworkTestStateRestorer StateRestorer;`
- L257 _protected member_ `TMap<UE::Net::FNetIDVariant, int64> SpawnedActors{};`

#### class `FPIENetworkComponent`  
`template <typename NetworkDataType = FBasePIENetworkComponentState> class FPIENetworkComponent : public FBasePIENetworkComponent`  
_L268-507_
- inherits: `FBasePIENetworkComponent`
- desc: Component which creates and initializes the server and client network connections between the PIE sessions. Expands on the `FBasePIENetworkComponent` by providing separate methods to add latent commands for the server and clients.
- L280 _public function_ `FPIENetworkComponent(FAutomationTestBase* InTestRunner, FTestCommandBuilder& InCommandBuilder, bool IsInitializing) : FBasePIENetworkComponent(InTestRunner, InCommandBuilder, IsInitializing)` — Construct the PIENetworkComponent. @param InTestRunner - Pointer to the TestRunner used for test reporting. @param InCommandBuilder - Reference to the latent command manager. @param IsInitializing - Bool specifying if the Automation framework is still being initialized. @note Requires that the `FPIENetworkComponent` is built using the `FNetworkComponentBuilder` as this will setup the server and client `NetworkDataType` states
- L290 _public prototype_ `FPIENetworkComponent& ThenServer(TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on the server. @param Action - Function to be executed. @return a reference to this
- L300 _public prototype_ `FPIENetworkComponent& ThenServer(const TCHAR* Description, TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on the server. @param Description - Description of the provided function to be logged. @param Action - Function to be executed. @return a reference to this
- L309 _public prototype_ `FPIENetworkComponent& ThenClients(TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on all clients. @param Action - Function to be executed. @return a reference to this
- L319 _public prototype_ `FPIENetworkComponent& ThenClients(const TCHAR* Description, TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on all clients. @param Description - Description of the provided function to be logged. @param Action - Function to be executed. @return a reference to this
- L329 _public prototype_ `FPIENetworkComponent& ThenClient(int32 ClientIndex, TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on a given client. @param ClientIndex - Index of the connected client. @param Action - Function to be executed. @return a reference to this
- L340 _public prototype_ `FPIENetworkComponent& ThenClient(const TCHAR* Description, int32 ClientIndex, TFunction<void(NetworkDataType&)> Action);` — Enqueues a function to the latent command manager for execution on a subsequent frame on a given client. @param Description - Description of the provided function to be logged. @param ClientIndex - Index of the connected client. @param Action - Function to be executed. @return a reference to this
- L352 _public prototype_ `FPIENetworkComponent& UntilServer(TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on the server. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L365 _public prototype_ `FPIENetworkComponent& UntilServer(const TCHAR* Description, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on the server. @param Description - Description of the latent command @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L377 _public prototype_ `FPIENetworkComponent& UntilClients(TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on all clients. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L390 _public prototype_ `FPIENetworkComponent& UntilClients(const TCHAR* Description, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on all clients. @param Description - Description of the latent command @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L403 _public prototype_ `FPIENetworkComponent& UntilClient(int32 ClientIndex, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on a given client. @param ClientIndex - Index of the connected client. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L417 _public prototype_ `FPIENetworkComponent& UntilClient(const TCHAR* Description, int32 ClientIndex, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Enqueues a function to the latent command manager for execution until completion or timeout on a given client. @param Description - Description of the latent command @param ClientIndex - Index of the connected client. @param Query - Function to be executed. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L428 _public prototype_ `FPIENetworkComponent& ThenClientJoins(TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Has a new client request a late join and syncs the server and other clients with the new client PIE session. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L440 _public prototype_ `template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::*ResultStorage> FPIENetworkComponent& SpawnAndReplicate(TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Spawns an actor on the server and replicates to the clients. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L453 _public prototype_ `template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::*ResultStorage> FPIENetworkComponent& SpawnAndReplicate(const FActorSpawnParameters& SpawnParameters, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Spawns an actor on the server and replicates to the clients. @param SpawnParameters - Parameters that can be used when spawning an Actor. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L466 _public prototype_ `template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::* ResultStorage> FPIENetworkComponent& SpawnAndReplicate(TFunction<void(ActorToSpawn&)> BeforeReplicate, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Spawns an actor on the server and replicates to the clients. @param BeforeReplicate - Function to be called after Actor has been spawned, but before being replicated to the other clients. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L480 _public prototype_ `template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::* ResultStorage> FPIENetworkComponent& SpawnAndReplicate(const FActorSpawnParameters& SpawnParameters, TFunction<void(ActorToSpawn&)> BeforeReplicate, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Spawns an actor on the server and replicates to the connected clients. @param SpawnParameters - Parameters that can be used when spawning an Actor. @param BeforeReplicate - Function to be called after Actor has been spawned, but before being replicated to the other clients. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L497 _private prototype_ `template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::* ResultStorage> FPIENetworkComponent& SpawnOnServer(const FActorSpawnParameters& SpawnParameters, TFunction<void(ActorToSpawn&)> BeforeReplicate, TOptional<FTimespan> Timeout = CQTest::DefaultTimeout);` — Spawns an actor on the server. @param SpawnParameters - Parameters that can be used when spawning an Actor. @param BeforeReplicate - Function to be called after Actor has been spawned. @param Timeout - Duration that the latent command can execute before reporting an error. @return a reference to this @note If no value is provided for the timeout, value will be pulled from the `TestFramework.CQTest.CommandTimeout.Network` CVar.
- L506 _private prototype_ `bool ReplicateToClients(NetworkDataType& ClientState);` — Replicates all Actors to the connected client. @param ClientState - Client state to receive the updated Actor. @return true if all Actors have been successfully replicated on this client

#### class `FNetworkComponentBuilder`  
`template <typename NetworkDataType = FBasePIENetworkComponentState> class FNetworkComponentBuilder`  
_L514-589_
- desc: Helper object used to setup and build the `FPIENetworkComponent`.
- L522 _public prototype_ `FNetworkComponentBuilder();` — Construct the NetworkComponentBuilder. @note Will assert if the `NetworkDataType` used is not of type or derived from `FBasePIENetworkComponentState`
- L533 _public prototype_ `FNetworkComponentBuilder& WithClients(int32 ClientCount);` — Specifies the number of clients to be used. @param ClientCount - Number of clients not including the listen server. @return a reference to this @note Number of clients should exclude the server, even if using the server as a listen server.
- L540 _public prototype_ `FNetworkComponentBuilder& AsDedicatedServer();` — Build the server as a dedicated server. @return a reference to this
- L547 _public prototype_ `FNetworkComponentBuilder& AsListenServer();` — Build the server as a listen server. @return a reference to this
- L556 _public prototype_ `FNetworkComponentBuilder& WithPacketSimulationSettings(FPacketSimulationSettings* InPacketSimulationSettings);` — Build the FPIENetworkComponent to use the provided packet simulation settings. @param InPacketSimulationSettings - Settings used to simulate packet behavior over a network. @return a reference to this
- L565 _public prototype_ `FNetworkComponentBuilder& WithGameMode(TSubclassOf<AGameModeBase> InGameMode);` — Build the FPIENetworkComponent to use the provided game mode. @param InGameMode - GameMode used for the networked session. @return a reference to this
- L574 _public prototype_ `FNetworkComponentBuilder& WithGameInstanceClass(FSoftClassPath InGameInstanceClass);` — Build the FPIENetworkComponent to restore back to the provided game instance. @param InGameInstanceClass - GameInstance to restore back to. @return a reference to this
- L581 _public prototype_ `void Build(FPIENetworkComponent<NetworkDataType>& OutNetwork);` — Build the FPIENetworkComponent with the provided data. @param OutNetwork - Reference to the FPIENetworkComponent.
- L584 _private member_ `FPacketSimulationSettings* PacketSimulationSettings = nullptr;`
- L585 _private member_ `TSubclassOf<AGameModeBase> GameMode = TSubclassOf<AGameModeBase>(nullptr);`
- L587 _private member_ `int32 ClientCount = 2;`
- L588 _private member_ `bool bIsDedicatedServer = true;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define ENABLE_PIE_NETWORK_TEST WITH_EDITOR && (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)`
- L591 _variable_ `constexpr static EAutomationTestFlags NetworkTestContext = EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter;`
- L594 _macro_ `#define NETWORK_TEST_CLASS(_ClassName, _TestDir) TEST_CLASS_WITH_FLAGS(_ClassName, _TestDir, NetworkTestContext)` — Macro to quickly create tests which will only run within the Editor.

### `Source/Developer/CQTest/Public/Components/PIENetworkTestStateRestorer.h` (Public)


#### class `FPIENetworkTestStateRestorer`  
`class FPIENetworkTestStateRestorer`  
_L16-36_
- desc: Object which saves the state of the game before starting the test, Then restores it after the test is complete.
- L19 _public prototype_ `FPIENetworkTestStateRestorer() = default;`
- L27 _public prototype_ `FPIENetworkTestStateRestorer(const FSoftClassPath InGameInstanceClass, TSubclassOf<AGameModeBase> InGameMode);` — Construct the PIENetworkTestStateRestorer. @param InGameInstanceClass - Current game instance prior to the test. @param InGameMode - Current game mode prior to the test.
- L30 _public prototype_ `void Restore();` — Restore to the previous game instance and mode.
- L33 _private member_ `bool SetWasLoadedFlag = false;`
- L34 _private member_ `FSoftClassPath OriginalGameInstance = FSoftClassPath();`
- L35 _private member_ `TSubclassOf<AGameModeBase> OriginalGameMode;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CQTEST_API`

### `Source/Developer/CQTest/Public/Components/SpawnHelper.h` (Public)


#### struct `FSpawnHelper`  
`struct FSpawnHelper`  
_L16-112_
- desc: Helper object for spawning Actors and other object types in the world. @see FActorTestSpawner, FMapTestSpawner
- L19 _public prototype_ `virtual ~FSpawnHelper();` — Destruct the Spawn Helper.
- L32 _public function_ `template <typename ActorType> ActorType& SpawnActor(const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters(), UClass* Class = nullptr)` — Spawn an Actor in the world. @param SpawnParameters - Struct of optional parameters used to assist with spawning. @param Class - Class of the object to be spawned. @return reference to the spawned object @note Method guarantees that the Actor returned is valid, will assert otherwise.
- L50 _public function_ `template <typename ActorType> ActorType& SpawnActorAt(FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters(), UClass* Class = nullptr)` — Spawn an Actor in the world. @param Location - Location to spawn the Actor in the world. @param Rotation - Rotation to spawn the Actor in the world. @param SpawnParameters - Struct of optional parameters used to assist with spawning. @param Class - Class of the object to be spawned. @return reference to the spawned object @note Method guarantees that the Actor returned is valid, will assert otherwise.
- L61 _public function_ `template <typename ObjectType> ObjectType& SpawnObject()` — Create a new Object. @return reference to the created object
- L72 _public prototype_ `UWorld& GetWorld();` — Returns a reference to the current world.
- L80 _protected prototype_ `virtual UWorld* CreateWorld() = 0;` — Creates a new world. @returns a newly created world.
- L82 _protected member_ `TArray<TWeakObjectPtr<AActor>> SpawnedActors{};`
- L83 _protected member_ `TArray<TWeakObjectPtr<UObject>> SpawnedObjects{};`
- L85 _protected member_ `UWorld* GameWorld{ nullptr };`
- L102 _private function_ `template <typename ActorType> ActorType& SpawnActorAtInWorld(UWorld& World, const FVector& Location, const FRotator& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters(), UClass* Class = nullptr)` — Spawn an Actor in the world. @param World - World to spawn the Actor. @param Location - Location to spawn the Actor in the world. @param Rotation - Rotation to spawn the Actor in the world. @param SpawnParameters - Struct of optional parameters used to assist with spawning. @param Class - Class of the object to be spawned. @return reference to the spawned object @note Method guarantees that the Actor returned is valid, will assert otherwise.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CQTEST_API`

### `Source/Developer/CQTest/Public/Helpers/CQTestAssetFilterBuilder.h` (Public)


#### class `CQTestAssetHelper::FAssetFilterBuilder`  
`class FAssetFilterBuilder`  
_L17-142_
- desc: Helper object which generates a FARFilter to be used with the CQTestAssetHelper functions. @see FARFilter
- L21 _public prototype_ `FAssetFilterBuilder() = default;` — Construct the FAssetFilterBuilder.
- L32 _public prototype_ `FAssetFilterBuilder& WithPackageName(const FName& PackageName);` — Specifies the package name to be matched against. @param PackageName - Full name of the package. @return a reference to this @note Method can be called multiple times to provide additional names.
- L45 _public prototype_ `FAssetFilterBuilder& WithPackagePath(const FName& PackagePath);` — Specifies the package path to be matched against. @param PackagePath - Path of the package. @return a reference to this @note Method can be called multiple times to provide additional paths. @note The path will be sanitized prior to being added to the filer (e.g. `Game/Assets/` converts to `/Game/Assets`). @note The specified path, but not sub paths(by default), will be included. Sub paths will be included only if IncludeRecursivePaths is called with true.
- L56 _public prototype_ `FAssetFilterBuilder& WithSoftObjectPath(const FSoftObjectPath& SoftObjectPath);` — Specifies the paths of specific assets to match. @param SoftObjectPath - Top level asset path. @return a reference to this @note Method can be called multiple times to provide additional paths.
- L68 _public prototype_ `FAssetFilterBuilder& WithClassPath(const FTopLevelAssetPath& ClassPath);` — Specifies the class paths of specific class instances to match. @param ClassPath - Name of the Class instance. @return a reference to this @note Method can be called multiple times to provide additional paths. @note Instances of the specified classes, but not subclasses (by default), will be included. Derived classes will be included only if IncludeRecursiveClasses is called with true.
- L81 _public prototype_ `FAssetFilterBuilder& WithTagAndValue(const FName& Tag, TOptional<FString> Value);` — Specifies the tag and value of an asset to match. @param Tag - Name of the asset property. @param Value - Value of the asset property. @return a reference to this @note Method can be called multiple times to provide additional tag/value pairs. @note Will only work on assets with properties marked with the AssetRegistrySearchable flag.
- L92 _public prototype_ `FAssetFilterBuilder& WithRecursiveClassPathsExclusion(const FTopLevelAssetPath& RecursiveClassPathsExclusion);` — Specifies the class paths to exclude. @param RecursiveClassPathsExclusion - Name of the Class instance. @return a reference to this @note Method can be called multiple times to provide additional paths.
- L99 _public prototype_ `FAssetFilterBuilder& IncludeRecursivePaths();` — Enables the inclusion of sub paths. @return a reference to this
- L106 _public prototype_ `FAssetFilterBuilder& IncludeRecursiveClasses();` — Enables the inclusion of subclass paths. @return a reference to this
- L113 _public prototype_ `FAssetFilterBuilder& IncludeOnlyOnDiskAssets();` — Enables matching only on assets found on disk and not in memory. @return a reference to this
- L122 _public prototype_ `FAssetFilterBuilder& WithPackageFlags(uint32 PackageFlags);` — Specifies matching only on assets with the specified flags. @param PackageFlags - Bitmask of package flags. @return a reference to this
- L131 _public prototype_ `FAssetFilterBuilder& WithoutPackageFlags(uint32 PackageFlags);` — Specifies matching only on assets without the specified flags. @param PackageFlags - Bitmask of package flags. @return a reference to this
- L138 _public prototype_ `FARFilter Build();` — Build the FARFilter with the provided data. @return the generated FARFilterparam OutFilter - Reference to the FARFilter.
- L141 _private member_ `FARFilter AssetRegistryFilter;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CQTEST_API`
- L9 _namespace_ `namespace CQTestAssetHelper`

### `Source/Developer/CQTest/Public/Helpers/CQTestAssetHelper.h` (Public)


#### Free symbols / members of external scopes

- L44 _namespace_ `namespace CQTestAssetHelper`
- L56 _prototype_ `TOptional<FString> FindAssetPackagePathByName(const FString& Name);` (scope `CQTestAssetHelper`) — Looks for the package path of an asset by its name in the AssetRegistry. @param Name - Name of the asset to find. @return package path of the asset if found @note If the asset name is found in multiple package paths, it's unspecified which one is returned.
- L68 _prototype_ `TOptional<FString> FindAssetPackagePathByName(const FARFilter& Filter, const FString& Name);` (scope `CQTestAssetHelper`) — Looks for the package path of an asset by its name in the AssetRegistry. @param Filter - AssetRegistry filter. @param Name - Name of the asset to find. @return package path of the asset if found @note If the asset name is found in multiple package paths, it's unspecified which one is returned.
- L77 _prototype_ `TArray<FAssetData> FindAssetsByFilter(const FARFilter& Filter);` (scope `CQTestAssetHelper`) — Looks for any assets matching the filter in the AssetRegistry. @param Filter - AssetRegistry filter. @return array of assets matching the filter
- L88 _prototype_ `UClass* GetBlueprintClass(const FString& Name);` (scope `CQTestAssetHelper`) — Looks for a Blueprint class by its name in the AssetRegistry. @param Name - Name of the Blueprint to find. @return UClass of the Blueprint if found @note If the name is found in multiple package paths, it's unspecified which one is returned.
- L100 _prototype_ `UClass* GetBlueprintClass(const FARFilter& Filter, const FString& Name);` (scope `CQTestAssetHelper`) — Looks for a Blueprint class by its name in the AssetRegistry. @param Filter - AssetRegistry filter. @param Name - Name of the Blueprint to find. @return UClass of the Blueprint if found @note If the name is found in multiple package paths, it's unspecified which one is returned.
- L109 _prototype_ `TArray<UClass*> GetBlueprintClasses(const FARFilter& Filter);` (scope `CQTestAssetHelper`) — Looks for all Blueprint classes matching the filter in the AssetRegistry. @param Filter - AssetRegistry filter. @return array of available UClasses matching the filter
- L120 _prototype_ `UObject* FindDataBlueprint(const FString& Name);` (scope `CQTestAssetHelper`) — Looks for a Data Blueprint by its name in the AssetRegistry. @param Name - Name of the Data Blueprint to find. @return UObject of the Data Blueprint if found @note If the name is found in multiple package paths, it's unspecified which one is returned.
- L132 _prototype_ `UObject* FindDataBlueprint(const FARFilter& Filter, const FString& Name);` (scope `CQTestAssetHelper`) — Looks for a Data Blueprint by its name in the AssetRegistry. @param Filter - AssetRegistry filter. @param Name - Name of the Data Blueprint to find @return UObject of the Data Blueprint if found @note If the name is found in multiple package paths, it's unspecified which one is returned.
- L141 _prototype_ `TArray<UObject*> FindDataBlueprints(const FARFilter& Filter);` (scope `CQTestAssetHelper`) — Looks for all UObjects matching the filter in the AssetRegistry. @param Filter - AssetRegistry filter. @return array of available UObjects matching the filter

### `Source/Developer/CQTest/Public/Impl/CQTest.inl` (Public)


#### struct `__anonbcd733020111::TBeforeTestCommand`  
`template <typename AsserterType> struct TBeforeTestCommand : public IAutomationLatentCommand`  
_L8-36_
- inherits: `IAutomationLatentCommand`
- L10 _public function_ `TBeforeTestCommand(TBaseTest<AsserterType>& InCurrentTest, TSharedRef<FRunSequence> InSequence) : CurrentTest(InCurrentTest) , Sequence(InSequence)`
- L15 _public function_ `bool Update() override`
- L34 _public member_ `TBaseTest<AsserterType>& CurrentTest;`
- L35 _public member_ `TSharedRef<FRunSequence> Sequence;`

#### struct `__anonbcd733020111::TRunTestCommand`  
`template <typename AsserterType> struct TRunTestCommand : public IAutomationLatentCommand`  
_L39-72_
- inherits: `IAutomationLatentCommand`
- L41 _public function_ `TRunTestCommand(TBaseTest<AsserterType>& InCurrentTest, const FString& InRequestedTest, const TTestRunner<AsserterType>& InTestRunner, TSharedRef<FRunSequence> InSequence) : CurrentTest(InCurrentTest) , RequestedTest(InRequestedTest) , TestRunner(InTestRunner) , Sequence(InSequence)`
- L49 _public function_ `bool Update() override`
- L68 _public member_ `TBaseTest<AsserterType>& CurrentTest;`
- L69 _public member_ `const FString& RequestedTest;`
- L70 _public member_ `const TTestRunner<AsserterType>& TestRunner;`
- L71 _public member_ `TSharedRef<FRunSequence> Sequence;`

#### struct `__anonbcd733020111::TAfterTestCommand`  
`template <typename AsserterType> struct TAfterTestCommand : public IAutomationLatentCommand`  
_L75-101_
- inherits: `IAutomationLatentCommand`
- L77 _public function_ `TAfterTestCommand(TBaseTest<AsserterType>& InCurrentTest, TSharedRef<FRunSequence> InSequence) : CurrentTest(InCurrentTest) , Sequence(InSequence)`
- L82 _public function_ `bool Update() override`
- L99 _public member_ `TBaseTest<AsserterType>& CurrentTest;`
- L100 _public member_ `TSharedRef<FRunSequence> Sequence;`

#### struct `__anonbcd733020111::TTearDownRunner`  
`template <typename AsserterType> struct TTearDownRunner : public IAutomationLatentCommand`  
_L104-127_
- inherits: `IAutomationLatentCommand`
- L106 _public function_ `explicit TTearDownRunner(TTestRunner<AsserterType>& TestRunner) : TestRunner(TestRunner)`
- L109 _public function_ `bool Update() override`
- L126 _public member_ `TTestRunner<AsserterType>& TestRunner;`

#### Free symbols / members of external scopes

- L4 _namespace_ `namespace (anonymous)`
- L5 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogCqTest, Log, All);` (scope `__anonbcd733020111`)
- L131 _function_ `template <typename AsserterType> inline TTestRunner<AsserterType>::TTestRunner(FString InName, int32 InLineNumber, const char* InFileName, FString InTestDir, EAutomationTestFlags InTestFlags, TTestInstanceGenerator<AsserterType> InFactory, FString InTestTags) : FAutomationTestBase(InName, true) , LineNumber(InLineNumber) , FileName(FString(InFileName)) , TestDir(InTestDir) , TestFlags(InTestFlags) , TestInstanceFactory(InFactory) , TestTags(InTestTags)` (scope `TTestRunner`)
- L165 _function_ `template <typename AsserterType> inline TTestRunner<AsserterType>::~TTestRunner()` (scope `TTestRunner`)
- L177 _function_ `template <typename AsserterType> inline bool TTestRunner<AsserterType>::RunTest(const FString& RequestedTest)` (scope `TTestRunner`)
- L212 _function_ `template <typename AsserterType> inline FString TTestRunner<AsserterType>::GetBeautifiedTestName() const` (scope `TTestRunner`)
- L218 _function_ `template <typename AsserterType> inline uint32 TTestRunner<AsserterType>::GetRequiredDeviceNum() const` (scope `TTestRunner`)
- L224 _function_ `template <typename AsserterType> inline EAutomationTestFlags TTestRunner<AsserterType>::GetTestFlags() const` (scope `TTestRunner`)
- L230 _function_ `template <typename AsserterType> inline FString TTestRunner<AsserterType>::GetTestSourceFileName() const` (scope `TTestRunner`)
- L236 _function_ `template <typename AsserterType> inline int32 TTestRunner<AsserterType>::GetTestSourceFileLine() const` (scope `TTestRunner`)
- L242 _function_ `template <typename AsserterType> inline int32 TTestRunner<AsserterType>::GetTestSourceFileLine(const FString& Name) const` (scope `TTestRunner`)
- L258 _function_ `template <typename AsserterType> inline bool TTestRunner<AsserterType>::SuppressLogWarnings()` (scope `TTestRunner`)
- L268 _function_ `template <typename AsserterType> inline bool TTestRunner<AsserterType>::SuppressLogErrors()` (scope `TTestRunner`)
- L278 _function_ `template <typename AsserterType> inline void TTestRunner<AsserterType>::SetSuppressLogWarnings(ECQTestSuppressLogBehavior Behavior)` (scope `TTestRunner`)
- L284 _function_ `template <typename AsserterType> inline void TTestRunner<AsserterType>::SetSuppressLogErrors(ECQTestSuppressLogBehavior Behavior)` (scope `TTestRunner`)
- L290 _function_ `template <typename AsserterType> inline void TTestRunner<AsserterType>::GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const` (scope `TTestRunner`)
- L302 _function_ `template <typename Derived, typename AsserterType> inline void TTest<Derived, AsserterType>::RunTest(const FString& TestName)` (scope `TTest`)
- L311 _function_ `template <typename AsserterType> inline TBaseTest<AsserterType>::TBaseTest(FAutomationTestBase& TestRunner, bool bInitializing) : bInitializing(bInitializing) , TestRunner(TestRunner) , Assert(AsserterType{ TestRunner }) , TestCommandBuilder(FTestCommandBuilder{ TestRunner })` (scope `TBaseTest`)
- L320 _function_ `template <typename AsserterType> inline void TBaseTest<AsserterType>::AddCommand(IAutomationLatentCommand* Cmd)` (scope `TBaseTest`)
- L326 _function_ `template <typename AsserterType> inline void TBaseTest<AsserterType>::AddCommand(TSharedPtr<IAutomationLatentCommand> Cmd)` (scope `TBaseTest`)
- L332 _function_ `template <typename AsserterType> inline void TBaseTest<AsserterType>::AddError(const FString& InError) const` (scope `TBaseTest`)
- L338 _function_ `template <typename AsserterType> inline bool TBaseTest<AsserterType>::AddErrorIfFalse(bool bCondition, const FString& InError) const` (scope `TBaseTest`)
- L344 _function_ `template <typename AsserterType> inline void TBaseTest<AsserterType>::AddWarning(const FString& InWarning) const` (scope `TBaseTest`)
- L350 _function_ `template <typename AsserterType> inline void TBaseTest<AsserterType>::AddInfo(const FString& InLogItem) const` (scope `TBaseTest`)

### `Source/Developer/CQTest/Public/Impl/PIENetworkComponent.inl` (Public)


#### Free symbols / members of external scopes

- L7 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenServer(TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L13 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenServer(const TCHAR* Description, TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L15 _function_ `CommandBuilder->Do(Description, [this, Action] { Action(static_cast<NetworkDataType&>(*ServerState)); });` (scope `FPIENetworkComponent::ThenServer`)
- L20 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenClients(TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L26 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenClients(const TCHAR* Description, TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L29 _function_ `CommandBuilder->Do(Description, [this, Action]() { for (int32 Index = 0; Index < ClientStates.Num(); Index++) { Action(static_cast<NetworkDataType&>(*ClientStates[Index])); } });` (scope `FPIENetworkComponent::ThenClients`) — The outer Do is to delay the for-loop until execution time in case a client joins during the test
- L40 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenClient(int32 ClientIndex, TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L46 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenClient(const TCHAR* Description, int32 ClientIndex, TFunction<void(NetworkDataType&)> Action)` (scope `FPIENetworkComponent`)
- L49 _function_ `CommandBuilder->Do(Description, [this, Action, ClientIndex]() { if (!ClientStates.IsValidIndex(ClientIndex)) { TestRunner->AddError(FString::Printf(TEXT("Invalid client index specified. Requested Index: %d MaxIndex: %d"), ClientIndex, ClientStates.Num() - 1)); return; } Action(static_cast<NetworkDataType&>(*ClientStates[ClientIndex])); });` (scope `FPIENetworkComponent::ThenClient`) — The outer Do is to delay the for-loop until execution time in case a client joins during the test
- L62 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilServer(TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L68 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilServer(const TCHAR* Description, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L71 _function_ `CommandBuilder->Until(Description, [this, Query]() { return Query(static_cast<NetworkDataType&>(*ServerState)); }, TimeoutValue);` (scope `FPIENetworkComponent::UntilServer`)
- L79 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilClients(TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L85 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilClients(const TCHAR* Description, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L90 _function_ `CommandBuilder->Until(Description, [this, Query, ClientsFinishedTask]() mutable {` (scope `FPIENetworkComponent::UntilClients`)
- L121 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilClient(int32 ClientIndex, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L127 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::UntilClient(const TCHAR* Description, int32 ClientIndex, TFunction<bool(NetworkDataType&)> Query, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L130 _function_ `CommandBuilder->Until(Description, [this, Query, ClientIndex]() { if (!ClientStates.IsValidIndex(ClientIndex)) { TestRunner->AddError(FString::Printf(TEXT("Invalid client index specified. Requested Index: %d MaxIndex: %d"), ClientIndex, ClientStates.Num() - 1)); return true; } return Query(static_cast<NetworkDataType&>(*ClientStates[ClientIndex])); }, TimeoutValue);` (scope `FPIENetworkComponent::UntilClient`)
- L143 _function_ `template <typename NetworkDataType> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::ThenClientJoins(TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L146 _function_ `Do(TEXT("Update Server State"), [this]() { int32 NextClientIndex = ServerState->ClientCount++; ClientStates.Add(MakeUnique<NetworkDataType>(NetworkDataType{})); ClientStates.Last()->ClientIndex = NextClientIndex; ServerState->ClientConnections.SetNum(ServerState->ClientCount); GEditor->RequestLateJoin(); }) .Until(TEXT("Setting Worlds"), [this]() { return SetWorlds(); }, TimeoutValue) .Then(TEXT("Setup Packet Settings"), [this]() { SetPacketSettings(); }) .Then(TEXT("Connect Clients to Server"), [this]() { Conn` (scope `FPIENetworkComponent::ThenClientJoins`)
- L153 _function_ `.Until(TEXT("Setting Worlds"), [this]() { return SetWorlds(); }, TimeoutValue) .Then(TEXT("Setup Packet Settings"), [this]() { SetPacketSettings(); }) .Then(TEXT("Connect Clients to Server"), [this]() { Conn` (scope `FPIENetworkComponent::ThenClientJoins`)
- L154 _function_ `.Then(TEXT("Setup Packet Settings"), [this]() { SetPacketSettings(); }) .Then(TEXT("Connect Clients to Server"), [this]() { Conn` (scope `FPIENetworkComponent::ThenClientJoins`)
- L155 _function_ `.Then(TEXT("Connect Clients to Server"), [this]() { Conn` (scope `FPIENetworkComponent::ThenClientJoins`)
- L157 _function_ `UntilClient(TEXT("Replicate to new Client"), ServerState->ClientCount, [this](NetworkDataType& State) { return ReplicateToClients(State); }, TimeoutValue);` (scope `FPIENetworkComponent::ThenClientJoins`)
- L166 _function_ `template <typename NetworkDataType> template <typename ActorToSpawn, ActorToSpawn* NetworkDataType::*ResultStorage> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::SpawnAndReplicate(TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L189 _function_ `UntilClients([this](NetworkDataType& ClientState) { return ReplicateToClients(ClientState); }, TimeoutValue);` (scope `FPIENetworkComponent::SpawnAndReplicate`)
- L196 _function_ `template <typename NetworkDataType> template<typename ActorToSpawn, ActorToSpawn* NetworkDataType::* ResultStorage> inline FPIENetworkComponent<NetworkDataType>& FPIENetworkComponent<NetworkDataType>::SpawnOnServer(const FActorSpawnParameters& SpawnParameters, TFunction<void(ActorToSpawn&)> BeforeReplicate, TOptional<FTimespan> Timeout)` (scope `FPIENetworkComponent`)
- L207 _function_ `ThenServer(TEXT("Spawning Actor On Server"), [ServerActor, SpawnParameters, BeforeReplicate](NetworkDataType& State) { *ServerActor = State.World->template SpawnActor<ActorToSpawn>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters); if(BeforeReplicate) { BeforeReplicate(**ServerActor); } if (ResultStorage != nullptr) { State.*ResultStorage = *ServerActor; } }) .UntilServer(TEXT("Waiting for Net ID"), [this, ServerActor](NetworkDataType& State) { UE::Net::FNetIDVariant NetIDVariant; if (State.World->GetNetDriver()->IsUsingIrisReplication()) { UReplicationSystem* ReplicationSystem = State.World->GetNetDriver()->GetReplicationSystem(); UObjectReplicationBridge* ReplicationBridge = Cast<UObjectReplicationBridge>(ReplicationSystem->GetReplicationBridge()); checkf(IsValid(ReplicationBridge), TEXT("Unable to create a ReplicationBridge.")); NetIDVariant = UE::Net::FNetIDVariant(ReplicationBridge->GetReplicatedRefHandle(*ServerActor)); } else { NetIDVariant = UE::Net::FNetIDVariant(State.World->GetNetDriver()->GetNetGuidCache()->GetNetGUID(*ServerActor)); } if (!NetIDVariant.IsValid()) { return false; }` (scope `FPIENetworkComponent::SpawnOnServer`)
- L218 _function_ `.UntilServer(TEXT("Waiting for Net ID"), [this, ServerActor](NetworkDataType& State) { UE::Net::FNetIDVariant NetIDVariant; if (State.World->GetNetDriver()->IsUsingIrisReplication()) { UReplicationSystem* ReplicationSystem = State.World->GetNetDriver()->GetReplicationSystem(); UObjectReplicationBridge* ReplicationBridge = Cast<UObjectReplicationBridge>(ReplicationSystem->GetReplicationBridge()); checkf(IsValid(ReplicationBridge), TEXT("Unable to create a ReplicationBridge.")); NetIDVariant = UE::Net::FNetIDVariant(ReplicationBridge->GetReplicatedRefHandle(*ServerActor)); } else { NetIDVariant = UE::Net::FNetIDVariant(State.World->GetNetDriver()->GetNetGuidCache()->GetNetGUID(*ServerActor)); } if (!NetIDVariant.IsValid()) { return false; }` (scope `FPIENetworkComponent::SpawnOnServer`)
- L254 _function_ `template <typename NetworkDataType> inline bool FPIENetworkComponent<NetworkDataType>::ReplicateToClients(NetworkDataType& ClientState)` (scope `FPIENetworkComponent`)
- L294 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>::FNetworkComponentBuilder()` (scope `FNetworkComponentBuilder`)
- L300 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::WithClients(int32 InClientCount)` (scope `FNetworkComponentBuilder`)
- L308 _function_ `template<typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::WithPacketSimulationSettings(FPacketSimulationSettings* InPacketSimulationSettings)` (scope `FNetworkComponentBuilder`)
- L315 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::AsDedicatedServer()` (scope `FNetworkComponentBuilder`)
- L322 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::AsListenServer()` (scope `FNetworkComponentBuilder`)
- L329 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::WithGameMode(TSubclassOf<AGameModeBase> InGameMode)` (scope `FNetworkComponentBuilder`)
- L336 _function_ `template <typename NetworkDataType> inline FNetworkComponentBuilder<NetworkDataType>& FNetworkComponentBuilder<NetworkDataType>::WithGameInstanceClass(FSoftClassPath InGameInstanceClass)` (scope `FNetworkComponentBuilder`)
- L343 _function_ `template<typename NetworkDataType> inline void FNetworkComponentBuilder<NetworkDataType>::Build(FPIENetworkComponent<NetworkDataType>& OutNetwork)` (scope `FNetworkComponentBuilder`)

### `Source/Developer/CQTest/Public/ObjectBuilder.h` (Public)


#### class `TObjectBuilder`  
`template <typename TUObject> class TObjectBuilder final`  
_L17-318_
- L20 _public function_ `TObjectBuilder(UObject* InOwner = static_cast<UObject*>(GetTransientPackage())) : Object(NewObject<TUObject>(InOwner))`
- L28 _public function_ `TObjectBuilder(FSpawnHelper& Spawner, UClass* Clazz = nullptr) : Object(nullptr)`
- L40 _public function_ `template <typename T> TObjectBuilder<TUObject>& SetParam(const FName& InPropertyName, T InValue)`
- L107 _public function_ `template<typename T = TUObject> T& Spawn(FTransform InTransform = FTransform::Identity)`
- L127 _public function_ `template<typename TComponent, typename T = TUObject> TObjectBuilder<TUObject>& AddComponentTo(TComponent* InComponentToAdd = nullptr)`
- L153 _public function_ `template<typename TChildActorType, typename T = TUObject> TObjectBuilder<TUObject>& AddChildActorComponentTo()`
- L170 _private member_ `TUObject* Object;`
- L173 _private function_ `template <typename T> bool IsCompatibleWith(const FProperty& Prop) const`
- L255 _private function_ `template<typename T> FString GetTypeName() const`

#### struct `TObjectBuilder::TPropType`  
`template<typename T> struct TPropType`  
_L305-305_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template<typename T> struct TPropType`  
_L306-306_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template<typename T> struct TPropType`  
_L307-307_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template<typename T> struct TPropType`  
_L308-308_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<int8>`  
_L309-309_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<uint8>`  
_L310-310_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<int16>`  
_L311-311_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<uint16>`  
_L312-312_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<int32>`  
_L313-313_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<uint32>`  
_L314-314_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<int64>`  
_L315-315_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<uint64>`  
_L316-316_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### struct `TObjectBuilder::TPropType`  
`template <> struct TPropType<bool>`  
_L317-317_
- L305 _public typedef_ `template<typename T> struct TPropType { using Value = FStructProperty; };`
- L309 _public typedef_ `template <> struct TPropType<int8> { using Value = FInt8Property; };`
- L310 _public typedef_ `template <> struct TPropType<uint8> { using Value = FByteProperty; };`
- L311 _public typedef_ `template <> struct TPropType<int16> { using Value = FInt16Property; };`
- L312 _public typedef_ `template <> struct TPropType<uint16> { using Value = FUInt16Property; };`
- L313 _public typedef_ `template <> struct TPropType<int32> { using Value = FIntProperty; };`
- L314 _public typedef_ `template <> struct TPropType<uint32> { using Value = FUInt32Property; };`
- L315 _public typedef_ `template <> struct TPropType<int64> { using Value = FInt64Property; };`
- L316 _public typedef_ `template <> struct TPropType<uint64> { using Value = FUInt64Property; };`
- L317 _public typedef_ `template <> struct TPropType<bool> { using Value = FBoolProperty; };`

#### Free symbols / members of external scopes

- L14 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogObjectBuilder, Log, Log);`
- L42 _typedef_ `using Raw = std::decay_t<T>;` (scope `TObjectBuilder::SetParam`)
- L50 _function_ `auto TrySet = [&](auto Property)` (scope `TObjectBuilder::SetParam`)
- L175 _typedef_ `using Raw = std::decay_t<T>;` (scope `TObjectBuilder::IsCompatibleWith`)
- L208 _typedef_ `using Key = typename Raw::KeyInitType;` (scope `TObjectBuilder::IsCompatibleWith`)
- L209 _typedef_ `using Value = typename Raw::ValueInitType;` (scope `TObjectBuilder::IsCompatibleWith`)
- L243 _typedef_ `using PropType = typename TPropType<Raw>::Value;` (scope `TObjectBuilder::IsCompatibleWith`)
- L257 _typedef_ `using Raw = std::decay_t<T>;` (scope `TObjectBuilder::GetTypeName`)
- L264 _typedef_ `using PtrType = typename Raw::ElementType;` (scope `TObjectBuilder::GetTypeName`)
- L269 _typedef_ `using ElementType = typename Raw::ElementType;` (scope `TObjectBuilder::GetTypeName`)
- L279 _typedef_ `using Key = typename Raw::KeyInitType;` (scope `TObjectBuilder::GetTypeName`)
- L280 _typedef_ `using Value = typename Raw::ValueInitType;` (scope `TObjectBuilder::GetTypeName`)

### `Source/Developer/CQTest/Public/TestGameInstance.h` (Public)


#### class `UTestGameInstance`  
`class UTestGameInstance : public UGameInstance`  
_L12-18_
- reflection: `UCLASS(MinimalAPI, config=Game, transient, BlueprintType, Blueprintable)`
- inherits: `UGameInstance`
- L17 _public prototype_ `void InitializeForTest(UWorld& InWorld);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CQTEST_API`
