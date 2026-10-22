# Plugins / MassCommon

- module root: `Plugins/Runtime/MassGameplay/Source/MassCommon`
- headers: 6; symbols: 111
- symbol kinds: class=2, externvar=7, function=50, macro=1, member=20, namespace=8, prototype=12, struct=11
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCore, MassEngine, MassEntity

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/IMassCommonModule.h` (Public)


#### class `IMassCommonModule`  
`class IMassCommonModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassCommonModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/MassCommonFragments.h` (Public)


#### struct `FAgentRadiusFragment`  
`struct FAgentRadiusFragment : public FMassFragment`  
_L11-16_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L15 _public member_ `float Radius = 40.f;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FAgentHeightFragment`  
`struct FAgentHeightFragment : public FMassFragment`  
_L19-24_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L23 _public member_ `float Height = 180.f;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FObjectWrapperFragment`  
`struct FObjectWrapperFragment : public FMassFragment`  
_L30-33_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: This is a common type for all the wrappers pointing at UObjects used to copy data from them or set data based on Mass simulation..

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/MassCommonTypes.h` (Public)


#### struct `FMassNetworkID`  
`struct FMassNetworkID : public FSequentialIDBase`  
_L30-36_
- reflection: `USTRUCT()`
- inherits: `FSequentialIDBase`
- L34 _public prototype_ `FMassNetworkID() = default;`
- L35 _public function_ `explicit FMassNetworkID(uint32 InID) : FSequentialIDBase(InID)`

#### struct `FMassInt16Real`  
`struct FMassInt16Real`  
_L40-71_
- reflection: `USTRUCT()`
- desc: Float encoded in int16, 1cm accuracy.
- L44 _public prototype_ `FMassInt16Real() = default;`
- L46 _public function_ `explicit FMassInt16Real(const float InValue)`
- L51 _public function_ `void Set(const float InValue)`
- L56 _public function_ `float Get() const`
- L61 _public function_ `bool operator<(const FMassInt16Real RHS) const`
- L62 _public function_ `bool operator<=(const FMassInt16Real RHS) const`
- L63 _public function_ `bool operator>(const FMassInt16Real RHS) const`
- L64 _public function_ `bool operator>=(const FMassInt16Real RHS) const`
- L65 _public function_ `bool operator==(const FMassInt16Real RHS) const`
- L66 _public function_ `bool operator!=(const FMassInt16Real RHS) const`
- L70 _protected member_ `int16 Value = 0;` — `UPROPERTY(Transient)`

#### struct `FMassInt16Real10`  
`struct FMassInt16Real10`  
_L75-108_
- reflection: `USTRUCT()`
- desc: Float encoded in int16, 10cm accuracy.
- L79 _public member_ `static constexpr float Scale = 0.1f;`
- L81 _public prototype_ `FMassInt16Real10() = default;`
- L83 _public function_ `explicit FMassInt16Real10(const float InValue)`
- L88 _public function_ `void Set(const float InValue)`
- L93 _public function_ `float Get() const`
- L98 _public function_ `bool operator<(const FMassInt16Real10 RHS) const`
- L99 _public function_ `bool operator<=(const FMassInt16Real10 RHS) const`
- L100 _public function_ `bool operator>(const FMassInt16Real10 RHS) const`
- L101 _public function_ `bool operator>=(const FMassInt16Real10 RHS) const`
- L102 _public function_ `bool operator==(const FMassInt16Real10 RHS) const`
- L103 _public function_ `bool operator!=(const FMassInt16Real10 RHS) const`
- L107 _protected member_ `int16 Value = 0;` — `UPROPERTY(Transient)`

#### struct `FMassSnorm8Vector`  
`struct FMassSnorm8Vector`  
_L112-146_
- reflection: `USTRUCT()`
- desc: Vector which components are in range [-1..1], encoded in signed bytes.
- L116 _public member_ `static constexpr float Scale = (float)MAX_int8;`
- L118 _public prototype_ `FMassSnorm8Vector() = default;`
- L120 _public function_ `explicit FMassSnorm8Vector(const FVector& InVector)`
- L125 _public function_ `void Set(const FVector& InVector)`
- L132 _public function_ `FVector Get() const`
- L139 _protected member_ `int8 X = 0;` — `UPROPERTY(Transient)`
- L142 _protected member_ `int8 Y = 0;` — `UPROPERTY(Transient)`
- L145 _protected member_ `int8 Z = 0;` — `UPROPERTY(Transient)`

#### struct `FMassSnorm8Vector2D`  
`struct FMassSnorm8Vector2D`  
_L150-190_
- reflection: `USTRUCT()`
- desc: Vector2D which components are in range [-1..1], encoded in signed bytes.
- L154 _public member_ `static constexpr float Scale = (float)MAX_int8;`
- L156 _public prototype_ `FMassSnorm8Vector2D() = default;`
- L158 _public function_ `explicit FMassSnorm8Vector2D(const FVector2D& InVector)`
- L163 _public function_ `explicit FMassSnorm8Vector2D(const FVector& InVector)`
- L168 _public function_ `void Set(const FVector2D& InVector)`
- L174 _public function_ `FVector2D Get() const`
- L179 _public function_ `FVector GetVector(const float InZ = 0.0f) const`
- L186 _protected member_ `int8 X = 0;` — `UPROPERTY(Transient)`
- L189 _protected member_ `int8 Y = 0;` — `UPROPERTY(Transient)`

#### struct `FMassUnorm8Real`  
`struct FMassUnorm8Real`  
_L194-220_
- reflection: `USTRUCT()`
- desc: Real in range [0..1], encoded in signed bytes.
- L198 _public member_ `static constexpr float Scale = MAX_uint8;`
- L200 _public prototype_ `FMassUnorm8Real() = default;`
- L202 _public function_ `explicit FMassUnorm8Real(const float InValue)`
- L207 _public function_ `void Set(const float InValue)`
- L212 _public function_ `float Get() const`
- L219 _protected member_ `uint8 Value = 0;` — `UPROPERTY(Transient)`

#### struct `FMassInt16Vector`  
`struct FMassInt16Vector`  
_L224-255_
- reflection: `USTRUCT()`
- desc: Vector encoded in int16, 1cm accuracy.
- L228 _public prototype_ `FMassInt16Vector() = default;`
- L229 _public function_ `FMassInt16Vector(const FVector& InVector)`
- L234 _public function_ `void Set(const FVector& InVector)`
- L241 _public function_ `FVector Get() const`
- L248 _protected member_ `int16 X = 0;` — `UPROPERTY(Transient)`
- L251 _protected member_ `int16 Y = 0;` — `UPROPERTY(Transient)`
- L254 _protected member_ `int16 Z = 0;` — `UPROPERTY(Transient)`

#### struct `FMassInt16Vector2D`  
`struct FMassInt16Vector2D`  
_L259-295_
- reflection: `USTRUCT()`
- desc: Vector2D encoded in int16, 1cm accuracy.
- L263 _public prototype_ `FMassInt16Vector2D() = default;`
- L264 _public function_ `FMassInt16Vector2D(const FVector2D& InVector)`
- L268 _public function_ `FMassInt16Vector2D(const FVector& InVector)`
- L273 _public function_ `void Set(const FVector2D& InVector)`
- L279 _public function_ `FVector2D Get() const`
- L284 _public function_ `FVector GetVector(const float InZ = 0.0f) const`
- L291 _protected member_ `int16 X = 0;` — `UPROPERTY(Transient)`
- L294 _protected member_ `int16 Y = 0;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define WITH_MASSGAMEPLAY_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR || UE_BUILD_TEST) && WITH_MASSENTITY_DEBUG && 1)`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L20 _externvar_ `extern const FName UpdateWorldFromMass;` (scope `UE::Mass::ProcessorGroupNames`)
- L21 _externvar_ `extern const FName SyncWorldToMass;` (scope `UE::Mass::ProcessorGroupNames`)
- L22 _externvar_ `extern const FName Behavior;` (scope `UE::Mass::ProcessorGroupNames`)
- L23 _externvar_ `extern const FName Tasks;` (scope `UE::Mass::ProcessorGroupNames`)
- L24 _externvar_ `extern const FName Avoidance;` (scope `UE::Mass::ProcessorGroupNames`)
- L25 _externvar_ `extern const FName ApplyForces;` (scope `UE::Mass::ProcessorGroupNames`)
- L26 _externvar_ `extern const FName Movement;` (scope `UE::Mass::ProcessorGroupNames`)

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/MassCommonUtils.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mass` (scope `UE`)
- L15 _namespace_ `namespace Utils` (scope `UE::Mass`)
- L21 _prototype_ `TArray<FMassEntityHandle> EntityQueueToArray(TQueue<FMassEntityHandle, EQueueMode::Mpsc>& EntitiesQueue, const int32 EntitiesCount);` (scope `UE::Mass::Utils`) — Creates a TArray of entities based on the given EntitiesQueue. Note that it's the caller's responsibility to ensure EntitiesCount > 0, otherwise the function will fail a check (with explosive results).
- L29 _prototype_ `bool IsDeterministic();` (scope `UE::Mass::Utils`) — If this is true, then the mass systems should strive to be as deterministic as possible, this will also enable the fixed random seed Currently maps to FApp::bUseFixedSeed
- L34 _prototype_ `int32 OverrideRandomSeedForTesting(int32 InSeed);` (scope `UE::Mass::Utils`) — If IsDeterministic() returns true, then this function will return the value of ai.massrepresentation.OverrideRandomSeed in place of InSeed
- L39 _prototype_ `int32 GenerateRandomSeed();` (scope `UE::Mass::Utils`) — If IsDeterministic() returns true, then this function will return the value of ai.massrepresentation.OverrideRandomSeed in place of FMath::Rand()
- L43 _function_ `inline constexpr bool IsDeterministic()` (scope `UE::Mass::Utils`)
- L45 _function_ `inline int32 OverrideRandomSeedForTesting(int32 InSeed)` (scope `UE::Mass::Utils`)
- L47 _function_ `inline int32 GenerateRandomSeed()` (scope `UE::Mass::Utils`)

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/MassGameplaySettings.h` (Public)


#### class `UMassGameplaySettings`  
`class UMassGameplaySettings : public UMassModuleSettings`  
_L10-18_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, DisplayName = "Mass Gameplay")`
- inherits: `UMassModuleSettings`
- L17 _public member_ `bool bLogSpawnLocations = true;` — `UPROPERTY(EditAnywhere, config, Category = Debug, meta = (ConsoleVariable = "mass.debug.VLogSpawnLocations"))`

### `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/RandomSequence.h` (Public)


#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace RandomSequence` (scope `UE`)
- L31 _function_ `inline uint32 FibonacciHash(const int32 SeqIndex)` (scope `UE::RandomSequence`) — @return 32 bit fibonacci hash at specified index.
- L42 _function_ `inline float FRand(const int32 SeqIndex)` (scope `UE::RandomSequence`) — Helper function to return random float. @return A random number in [0..1]
- L53 _function_ `inline int32 RandHelper(const int32 SeqIndex, const int32 A)` (scope `UE::RandomSequence`) — Helper function to return random int on specified range. @return A random number in [0..A)
- L62 _function_ `inline int32 RandRange(const int32 SeqIndex, const int32 InMin, const int32 InMax)` (scope `UE::RandomSequence`) — Helper function to return random int in specified range. @return A random number >= Min and <= Max
- L72 _function_ `inline float FRandRange(const int32 SeqIndex, const float InMin, const float InMax)` (scope `UE::RandomSequence`) — Helper function to return random float in specified range. @return A random number >= Min and <= Max
- L81 _function_ `inline float RandRange(const int32 SeqIndex, const float InMin, const float InMax)` (scope `UE::RandomSequence`) — Helper function to return random float in specified range. @return A random number >= Min and <= Max
- L87 _function_ `inline uint32 FibocciHash(const int32 SeqIndex)` (scope `UE::RandomSequence`) — `UE_DEPRECATED(5.4, "Please use the correctly spelled version FibonacciHash()")`
