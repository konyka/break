# Plugins / WorldMetricsTest

- module root: `Plugins/WorldMetrics/Source/WorldMetricsTest`
- headers: 2; symbols: 49
- symbol kinds: class=24, function=5, macro=1, member=9, namespace=2, prototype=7, typedef=1
- PrivateDependencyModuleNames: Core, Engine
- PublicDependencyModuleNames: CoreUObject, WorldMetricsCore

### `Plugins/WorldMetrics/Source/WorldMetricsTest/Public/WorldMetricsTestTypes.h` (Public)


#### class `UMockWorldMetricBase`  
`class UMockWorldMetricBase : public UWorldMetricInterface`  
_L11-29_
- reflection: `UCLASS(abstract)`
- inherits: `UWorldMetricInterface`
- L15 _private prototype_ `virtual void Initialize() override;`
- L16 _private prototype_ `virtual void Deinitialize() override;`
- L17 _private prototype_ `virtual void Update(float DeltaTimeInSeconds) override;`
- L20 _public member_ `TArray<UWorldMetricsExtension*> Extensions;`
- L21 _public member_ `int32 InitializeCount = 0;`
- L22 _public member_ `int32 DeinitializeCount = 0;`
- L23 _public member_ `int32 UpdateCount = 0;`
- L25 _public function_ `virtual SIZE_T GetAllocatedSize() const override`

#### class `UMockWorldMetricsExtensionBase`  
`class UMockWorldMetricsExtensionBase : public UWorldMetricsExtension`  
_L32-55_
- reflection: `UCLASS(abstract)`
- inherits: `UWorldMetricsExtension`
- L36 _private prototype_ `virtual void Initialize() override;`
- L37 _private prototype_ `virtual void Deinitialize() override;`
- L38 _private prototype_ `virtual void OnAcquire(UObject* InOwner) override;`
- L39 _private prototype_ `virtual void OnRelease(UObject* InOwner) override;`
- L42 _public member_ `int32 InitializeCount = 0;`
- L43 _public member_ `int32 DeinitializeCount = 0;`
- L44 _public member_ `int32 OnAcquireCount = 0;`
- L45 _public member_ `int32 OnReleaseCount = 0;`
- L48 _public typedef_ `using FInitializeDeinitializeDelegate = TDelegate<void(UWorldMetricsExtension* Extension, bool bInitialize)>;` — Static delegate to allow injecting logic into Initialize/Deinitialize without needing to create new classes.
- L49 _public member_ `static FInitializeDeinitializeDelegate OnInitializeDeinitialize;`
- L51 _public function_ `virtual SIZE_T GetAllocatedSize() const override`

#### class `UMockWorldMetricFooBase`  
`class UMockWorldMetricFooBase: public UMockWorldMetricBase`  
_L58-61_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBase`

#### class `UMockWorldMetricBarBase`  
`class UMockWorldMetricBarBase : public UMockWorldMetricBase`  
_L64-67_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBase`

#### class `UMockWorldMetricA`  
`class UMockWorldMetricA : public UMockWorldMetricFooBase`  
_L70-73_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricFooBase`

#### class `UMockWorldMetricB`  
`class UMockWorldMetricB : public UMockWorldMetricFooBase`  
_L76-79_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricFooBase`

#### class `UMockWorldMetricC`  
`class UMockWorldMetricC : public UMockWorldMetricFooBase`  
_L82-85_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricFooBase`

#### class `UMockWorldMetricD`  
`class UMockWorldMetricD : public UMockWorldMetricFooBase`  
_L88-91_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricFooBase`

#### class `UMockWorldMetricE`  
`class UMockWorldMetricE : public UMockWorldMetricFooBase`  
_L94-97_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricFooBase`

#### class `UMockWorldMetricF`  
`class UMockWorldMetricF : public UMockWorldMetricBarBase`  
_L100-103_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBarBase`

#### class `UMockWorldMetricG`  
`class UMockWorldMetricG : public UMockWorldMetricBarBase`  
_L106-109_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBarBase`

#### class `UMockWorldMetricH`  
`class UMockWorldMetricH : public UMockWorldMetricBarBase`  
_L112-115_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBarBase`

#### class `UMockWorldMetricI`  
`class UMockWorldMetricI : public UMockWorldMetricBarBase`  
_L118-121_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBarBase`

#### class `UMockWorldMetricJ`  
`class UMockWorldMetricJ : public UMockWorldMetricBarBase`  
_L124-127_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricBarBase`

#### class `UMockWorldMetricsExtensionA`  
`class UMockWorldMetricsExtensionA : public UMockWorldMetricsExtensionBase`  
_L130-133_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionB`  
`class UMockWorldMetricsExtensionB : public UMockWorldMetricsExtensionBase`  
_L136-139_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionC`  
`class UMockWorldMetricsExtensionC : public UMockWorldMetricsExtensionBase`  
_L142-145_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionD`  
`class UMockWorldMetricsExtensionD : public UMockWorldMetricsExtensionBase`  
_L148-151_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionE`  
`class UMockWorldMetricsExtensionE : public UMockWorldMetricsExtensionBase`  
_L154-157_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionF`  
`class UMockWorldMetricsExtensionF : public UMockWorldMetricsExtensionBase`  
_L160-163_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionG`  
`class UMockWorldMetricsExtensionG : public UMockWorldMetricsExtensionBase`  
_L166-169_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionH`  
`class UMockWorldMetricsExtensionH : public UMockWorldMetricsExtensionBase`  
_L172-175_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionI`  
`class UMockWorldMetricsExtensionI : public UMockWorldMetricsExtensionBase`  
_L178-181_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

#### class `UMockWorldMetricsExtensionJ`  
`class UMockWorldMetricsExtensionJ : public UMockWorldMetricsExtensionBase`  
_L184-187_
- reflection: `UCLASS()`
- inherits: `UMockWorldMetricsExtensionBase`

### `Plugins/WorldMetrics/Source/WorldMetricsTest/Public/WorldMetricsTestUtil.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define REQUIRE_MESSAGE(Message, Expr) \`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace WorldMetrics` (scope `UE`)
- L26 _function_ `inline TArray<int32> MakeIndexArray(int32 Size)` (scope `UE::WorldMetrics`) — Returns an array with the parameter number of sequentially increased index values starting from zero. This method is equivalent to using std::iota with a zero starting value in a sequential container.
- L43 _function_ `template <typename T> TArray<T> MakeRandomSubset(TArrayView<T> Items, int32 Size = 0)` (scope `UE::WorldMetrics`) — Returns an array with a subset of the elements in the parameter input array. The subset size is expressed by the parameter size which must be smaller than the number of elements in the input array.
- L73 _function_ `template <typename T> void Shuffle(TArray<T>& OutArray)` (scope `UE::WorldMetrics`) — Performs a number of randomized swaps in the parameter array equivalent to its number of elements.
