# Developer / ChaosTestHarness

- module root: `Source/Developer/ChaosTestHarness`
- headers: 6; symbols: 93
- symbol kinds: class=6, function=22, member=15, namespace=7, prototype=33, struct=7, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LowLevelTestsRunner
- PublicDependencyModuleNames: Catch2

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestCatch2.h` (Public)
_(no declarations extracted)_

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestErrorLogSuppressor.h` (Public)


#### class `Chaos::LowLevelTest::FErrorLogSuppressor`  
`class UE_INTERNAL FErrorLogSuppressor : public FFeedbackContext`  
_L23-45_
- inherits: `FFeedbackContext`
- desc: RAII guard that suppresses Error and Warning verbosity log messages matching registered substrings. Replaces GWarn and adds itself to GLog so that matching lines are swallowed rather than forwarded to output devices that Horde scans. Non-matching messages are forwarded normally so unexpected errors/warnings still surface. Usage: FErrorLogSuppressor Suppressor; Suppressor.ExpectError(TEXT("expected error substring")); Suppressor.ExpectWarning(TEXT("expected warning substring")); // ... code that logs the expected messages ...
- L26 _public prototype_ `UE_INTERNAL FErrorLogSuppressor();`
- L27 _public prototype_ `UE_INTERNAL ~FErrorLogSuppressor();`
- L28 _public prototype_ `FErrorLogSuppressor(const FErrorLogSuppressor&) = delete;`
- L29 _public prototype_ `FErrorLogSuppressor(FErrorLogSuppressor&&) = delete;`
- L30 _public prototype_ `FErrorLogSuppressor& operator=(const FErrorLogSuppressor&) = delete;`
- L31 _public prototype_ `FErrorLogSuppressor& operator=(FErrorLogSuppressor&&) = delete;`
- L34 _public prototype_ `UE_INTERNAL FErrorLogSuppressor& ExpectError(FStringView InPattern);` — Register a substring pattern. Errors containing this text will be swallowed.
- L37 _public prototype_ `UE_INTERNAL FErrorLogSuppressor& ExpectWarning(FStringView InPattern);` — Register a substring pattern. Warnings containing this text will be swallowed.
- L39 _public prototype_ `virtual void Serialize(const TCHAR* InData, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L42 _private member_ `TArray<FString> ErrorPatterns;`
- L43 _private member_ `TArray<FString> WarningPatterns;`
- L44 _private member_ `FFeedbackContext* OldWarn;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace LowLevelTest` (scope `Chaos`)

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestHarness.h` (Public)
_(no declarations extracted)_

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestMatchers.h` (Public)


#### class `Catch::FVectorEqualityMatcher`  
`template <typename T, int D> class FVectorEqualityMatcher : public Catch::Matchers::MatcherBase<Chaos::TVector<T, D>>`  
_L11-40_
- inherits: `Catch::Matchers::MatcherBase<Chaos::TVector<T,D>>`
- L14 _public typedef_ `using FVector = Chaos::TVector<T, D>;`
- L15 _public member_ `FVector Target;`
- L16 _public member_ `T Epsilon;`
- L18 _public function_ `FVectorEqualityMatcher(const FVector& InTarget, const T InEpsilon = UE_KINDA_SMALL_NUMBER) : Target(InTarget) , Epsilon(InEpsilon)`
- L25 _public function_ `bool match(const FVector& ToCompare) const override` — Performs the test for this matcher
- L34 _public function_ `virtual std::string describe() const override` — Produces a string describing what this matcher does. It should include any provided data (the begin/ end in this case) and be written as if it were stating a fact (in the output it will be preceded by the value under test).

#### class `Catch::FQuatEqualityMatcher`  
`template <typename T> class FQuatEqualityMatcher : public Catch::Matchers::MatcherBase<UE::Math::TQuat<T>>`  
_L55-84_
- inherits: `Catch::Matchers::MatcherBase<UE::Math::TQuat<T>>`
- L58 _public typedef_ `using FQuat = UE::Math::TQuat<T>;`
- L59 _public member_ `FQuat Target;`
- L60 _public member_ `T Epsilon;`
- L62 _public function_ `FQuatEqualityMatcher(const FQuat& InTarget, const T InEpsilon = UE_KINDA_SMALL_NUMBER) : Target(InTarget) , Epsilon(InEpsilon)`
- L69 _public function_ `bool match(const FQuat& ToCompare) const override` — Performs the test for this matcher
- L78 _public function_ `virtual std::string describe() const override` — Produces a string describing what this matcher does. It should include any provided data (the begin/ end in this case) and be written as if it were stating a fact (in the output it will be preceded by the value under test).

#### class `Catch::TAABBEqualityMatcher`  
`template <typename T, int D> class TAABBEqualityMatcher : public Catch::Matchers::MatcherBase<Chaos::TAABB<T, D>>`  
_L93-126_
- inherits: `Catch::Matchers::MatcherBase<Chaos::TAABB<T,D>>`
- L96 _public typedef_ `using FAABB = Chaos::TAABB<T, D>;`
- L97 _public member_ `FAABB Target;`
- L98 _public member_ `T Epsilon;`
- L100 _public function_ `TAABBEqualityMatcher(const FAABB& InTarget, const T InEpsilon = static_cast<T>(UE_KINDA_SMALL_NUMBER)) : Target(InTarget) , Epsilon(InEpsilon)`
- L107 _public function_ `bool match(const FAABB& ToCompare) const override` — Performs the test for this matcher
- L120 _public function_ `virtual std::string describe() const override` — Produces a string describing what this matcher does. It should include any provided data (the begin/ end in this case) and be written as if it were stating a fact (in the output it will be preceded by the value under test).

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Catch`
- L43 _function_ `template <typename T, int D> FVectorEqualityMatcher<T, D> ApproxEq(const Chaos::TVector<T, D>& Target, const T Epsilon = UE_KINDA_SMALL_NUMBER)` (scope `Catch`)
- L49 _function_ `template <typename T> FVectorEqualityMatcher<T, 3> ApproxEq(const UE::Math::TVector<T>& Target, const T Epsilon = UE_KINDA_SMALL_NUMBER)` (scope `Catch`)
- L87 _function_ `template <typename T> FQuatEqualityMatcher<T> ApproxEq(const UE::Math::TQuat<T>& Target, const T Epsilon = UE_KINDA_SMALL_NUMBER)` (scope `Catch`)
- L129 _function_ `template <typename T, int D> TAABBEqualityMatcher<T, D> Equal(const Chaos::TAABB<T, D>& Target)` (scope `Catch`)
- L135 _function_ `template <typename T, int D> TAABBEqualityMatcher<T, D> ApproxEq(const Chaos::TAABB<T, D>& Target, const T Epsilon = static_cast<T>(UE_KINDA_SMALL_NUMBER))` (scope `Catch`)

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestScene.h` (Public)


#### class `Chaos::LowLevelTest::FChaosTestScene`  
`class UE_INTERNAL FChaosTestScene`  
_L23-79_
- desc: A wrapper around a chaos solver providing minimal functionality for testing.
- L26 _public prototype_ `UE_INTERNAL FChaosTestScene();`
- L27 _public prototype_ `UE_INTERNAL ~FChaosTestScene();`
- L29 _public prototype_ `UE_INTERNAL Chaos::FPBDRigidsSolver* GetSolver();`
- L32 _public prototype_ `UE_INTERNAL void TickSolver(float Dt);` — Tick the solver.
- L36 _public prototype_ `UE_INTERNAL bool TickSolverToSleep(float Dt, int32 MaxTicks);` — Tick the solver until it sleeps (or until we reach MaxTicks ticks). Return true if the scene is sleeping.
- L39 _public prototype_ `UE_INTERNAL bool IsSceneSleeping() const;` — Return true if all dynamic bodies are asleep.
- L42 _public prototype_ `UE_INTERNAL int GetNumTicks() const;` — How many ticks have been run (useful if using TickSolverToSleep)
- L45 _public prototype_ `UE_INTERNAL Chaos::FSingleParticlePhysicsProxy* AddDynamicSphere(const TCHAR* InName, const FTransform3d& InTransform, const double& InRadius);` — Add a dynamic awake body to the scene.
- L46 _public prototype_ `UE_INTERNAL Chaos::FSingleParticlePhysicsProxy* AddDynamicBox(const TCHAR* InName, const FTransform3d& InTransform, const FVector3d& InHalfExtents);`
- L47 _public prototype_ `UE_INTERNAL Chaos::FSingleParticlePhysicsProxy* AddDynamicProxy(const TCHAR* InName, const FTransform3d& InTransform, const Chaos::FImplicitObjectPtr& InGeometry);`
- L50 _public prototype_ `UE_INTERNAL Chaos::FSingleParticlePhysicsProxy* AddKinematicBox(const TCHAR* InName, const FTransform3d& InTransform, const FVector3d& InHalfExtents);` — Add a kinematic (which can be promoted to dynamic) body to the scene
- L51 _public prototype_ `UE_INTERNAL Chaos::FSingleParticlePhysicsProxy* AddKinematicProxy(const TCHAR* InName, const FTransform3d& InTransform, const Chaos::FImplicitObjectPtr& InGeometry);`
- L54 _public prototype_ `UE_INTERNAL void SetGravity(const FVector3d& InG);` — Set the gravity (for gravity group 0)
- L57 _public prototype_ `UE_INTERNAL void SetCollisionCallback(const TFunction<void(const Chaos::FCollisionEventData&)>& InCollisionCallback);` — Set the collision event callback (can only be one)
- L60 _private prototype_ `void CreateScene();`
- L61 _private prototype_ `void DestroyScene();`
- L62 _private prototype_ `void CreateSolver();`
- L63 _private prototype_ `void DestroySolver();`
- L65 _private prototype_ `Chaos::FSingleParticlePhysicsProxy* CreateDynamicSphere(const TCHAR* InName, const FTransform3d& InTransform, const double& InRadius);`
- L66 _private prototype_ `Chaos::FSingleParticlePhysicsProxy* CreateDynamicBox(const TCHAR* InName, const FTransform3d& InTransform, const FVector3d& InHalfExtents);`
- L67 _private prototype_ `Chaos::FSingleParticlePhysicsProxy* CreateDynamicProxy(const TCHAR* InName, const FTransform3d& InTransform, const Chaos::FImplicitObjectPtr& InGeometry);`
- L68 _private prototype_ `void InitCollisionFilter(Chaos::FSingleParticlePhysicsProxy* Proxy);`
- L69 _private prototype_ `void InitMassProperties(Chaos::FSingleParticlePhysicsProxy* Proxy);`
- L71 _private prototype_ `void OnCollision(const Chaos::FCollisionEventData& CollisionEventData);`
- L74 _private member_ `FChaosScene* Scene = nullptr;`
- L75 _private member_ `Chaos::FPBDRigidsSolver* Solver;`
- L76 _private member_ `TArray<Chaos::FSingleParticlePhysicsProxy*> Proxies;`
- L77 _private member_ `TFunction<void(const Chaos::FCollisionEventData&)> CollisionCallback;`
- L78 _private member_ `int32 NumTicks;`

#### class `Chaos::LowLevelTest::FChaosTestSimCallback`  
`class FChaosTestSimCallback : public Chaos::TSimCallbackObject<Chaos::FSimCallbackNoInput, Chaos::FSimCallbackNoOutput, Chaos::ESimCallbackOptions::ContactModification>`  
_L83-95_
- inherits: `Chaos::TSimCallbackObject<Chaos::FSimCallbackNoInput,Chaos::FSimCallbackNoOutput,Chaos::ESimCallbackOptions::ContactModification>`
- desc: A sim callback that allows unit tests to hook a lambda up to the various callbacks TODO: Add all the other callbacks!
- L86 _public function_ `virtual void OnContactModification_Internal(Chaos::FCollisionContactModifier& Modifier) override final`
- L94 _public member_ `TFunction<void(Chaos::FCollisionContactModifier&)> ContactModifier;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace LowLevelTest` (scope `Chaos`)

### `Source/Developer/ChaosTestHarness/Public/Chaos/LowLevelTest/ChaosTestStringMakers.h` (Public)


#### struct `Catch::StringMaker`  
`template<typename T> struct StringMaker<UE::Math::TQuat<T>>`  
_L14-17_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<> struct StringMaker<Chaos::FRotation3>`  
_L20-23_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<> struct StringMaker<Chaos::FRotation3f>`  
_L26-29_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<> struct StringMaker<Chaos::FVec3>`  
_L32-35_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<> struct StringMaker<Chaos::FVec3f>`  
_L38-41_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<typename T> struct StringMaker<UE::Math::TVector<T>>`  
_L44-47_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### struct `Catch::StringMaker`  
`template<typename T, int d> struct StringMaker<Chaos::TAABB<T, d>>`  
_L50-53_
- L16 _public function_ `static std::string convert(UE::Math::TQuat<T> const& Value)`
- L22 _public function_ `static std::string convert(Chaos::FRotation3 const& Value)`
- L28 _public function_ `static std::string convert(Chaos::FRotation3f const& Value)`
- L34 _public function_ `static std::string convert(Chaos::FVec3 const& Value)`
- L40 _public function_ `static std::string convert(Chaos::FVec3f const& Value)`
- L46 _public function_ `static std::string convert(UE::Math::TVector<T> const& Value)`
- L52 _public function_ `static std::string convert(Chaos::TAABB<T, d> const& Value)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Catch`
