# Plugins / AudioMotorSimDebug

- module root: `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug`
- headers: 8; symbols: 142
- symbol kinds: class=13, function=13, member=49, namespace=4, prototype=51, struct=2, variable=10
- PrivateDependencyModuleNames: AudioMotorSim, Core, CoreUObject, Engine, SlateCore, SlateIM, UnrealEd

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelDebugWidget.h` (Private)


#### struct `AudioMotorModelDebug::FDebugContext`  
`struct FDebugContext`  
_L18-51_
- desc: Structs that hold information about an object to be interpreted/plotted by the debugger
- L20 _public prototype_ `FDebugContext() = default;`
- L22 _public function_ `explicit FDebugContext(const TObjectPtr<UObject>& InDebuggedObject) : DebuggedObject(InDebuggedObject)`
- L26 _public function_ `FDebugContext(const TObjectPtr<UObject>& InDebuggedObject, const TArray<FInstancedStruct>& InDebugData, const TMap<FName, TSharedPtr<IParamGraph>>& InParamGraphs, bool bInDrawGraphs) : DebuggedObject(InDebuggedObject) , DebugData(InDebugData) , ParamGraphs(InParamGraphs) , bDrawGraphs(bInDrawGraphs)`
- L33 _public function_ `~FDebugContext()`
- L41 _public function_ `bool operator==(const FDebugContext& A) const`
- L46 _public member_ `TObjectPtr<UObject> DebuggedObject;`
- L47 _public member_ `TArray<FInstancedStruct> DebugData;`
- L48 _public member_ `TMap<FName, TSharedPtr<IParamGraph>> ParamGraphs;`
- L49 _public member_ `TSharedPtr<FAudioMotorModelDebugDetailWindow> DetailWindow;`
- L50 _public member_ `bool bDrawGraphs = false;`

#### class `FAudioMotorModelDebugWidget`  
`class FAudioMotorModelDebugWidget`  
_L54-104_
- L57 _public prototype_ `FAudioMotorModelDebugWidget();`
- L58 _public prototype_ `void Draw();`
- L59 _public prototype_ `void RegisterMotorModelComponent(UAudioMotorModelComponent* Component);`
- L60 _public prototype_ `void SendAdditionalDebugData(UObject* Object, const FInstancedStruct& AdditionalData);`
- L63 _private prototype_ `void UpdateDebugContexts();`
- L65 _private prototype_ `void PollRegisteredModels();`
- L66 _private prototype_ `void DrawMotorModelSelection();`
- L67 _private prototype_ `void DrawParameterSelection(AudioMotorModelDebug::FDebugContext& DebugContext);`
- L69 _private prototype_ `void InstantiateMotorModelDetails(UAudioMotorModelComponent* Model);`
- L70 _private prototype_ `void DrawMotorSimComponentList();`
- L71 _private prototype_ `AudioMotorModelDebug::FDebugContext* CreateMotorModelObjectDebugContext(UObject* ObjectToTrack);`
- L72 _private prototype_ `void CreateModelSimComponentsDebugContexts(const UAudioMotorModelComponent* Model);`
- L74 _private prototype_ `void GenerateParamSelector(const FProperty& ParamProperty, void* PropertyContainer);`
- L75 _private prototype_ `void DrawParameterGraphs();`
- L76 _private prototype_ `void PollParameterGraphs();`
- L78 _private prototype_ `void DrawObjectPropertiesTree(const TObjectPtr<UObject>& InObject);`
- L79 _private prototype_ `void DrawMotorSimComponentDetailButton(AudioMotorModelDebug::FDebugContext& DebugContext);`
- L81 _private prototype_ `TSharedPtr<AudioMotorModelDebug::IParamGraph> CreateParamGraph(const FProperty& ParamProperty, void* PropertyContainer);`
- L82 _private prototype_ `TSharedPtr<AudioMotorModelDebug::IParamGraph> CreateParamGraph(const FName& GraphedPropertyName, const FProperty& ParamProperty, void* PropertyContainer);`
- L84 _private prototype_ `void RegisterTrackedObject(const AudioMotorModelDebug::FDebugContext& InTrackedObject);`
- L85 _private prototype_ `void UnregisterTrackedObject(TObjectPtr<UObject> DebuggedObject);`
- L87 _private member_ `TArray<TObjectPtr<UAudioMotorModelComponent>> RegisteredMotorModels;`
- L89 _private member_ `int32 SelectedMotorModelIndex = 0;`
- L91 _private member_ `int32 GraphRowSize = 2;`
- L92 _private member_ `int32 MaxGraphRowSize = 50;`
- L93 _private member_ `int32 LiveGraphRowSize = GraphRowSize;`
- L94 _private member_ `FString GraphRowSizeText = FString::FromInt(GraphRowSize);`
- L96 _private member_ `float ParamGraphScale = 1.0f;`
- L97 _private member_ `float ParamGraphScaleMax = 5.0f;`
- L99 _private member_ `float ParamGraphNumFrames = 300.0f;`
- L100 _private member_ `float ParamGraphNumFramesMax = 1000.0f;`
- L102 _private member_ `TArray<AudioMotorModelDebug::FDebugContext> MotorSimDebugContexts;`
- L103 _private member_ `TArray<const FProperty*> PropertiesToGraph;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace AudioMotorModelDebug`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelDebugWidgetChildWindow.h` (Private)


#### class `FAudioMotorModelDebugWidgetChildWindow`  
`class FAudioMotorModelDebugWidgetChildWindow : public FSlateIMWidgetBase`  
_L10-45_
- inherits: `FSlateIMWidgetBase`
- L13 _public function_ `FAudioMotorModelDebugWidgetChildWindow(const FStringView& WindowTitle, FVector2f WindowSize) : FSlateIMWidgetBase(WindowTitle) , WindowTitle(WindowTitle) , WindowSize(WindowSize)`
- L20 _protected prototype_ `virtual void DrawWindow(float DeltaTime) = 0;`
- L23 _private function_ `virtual void DrawWidget(float DeltaTime) final override`
- L43 _private member_ `FString WindowTitle;`
- L44 _private member_ `FVector2f WindowSize;`

#### class `FAudioMotorModelDebugDetailWindow`  
`class FAudioMotorModelDebugDetailWindow : public FAudioMotorModelDebugWidgetChildWindow`  
_L48-57_
- inherits: `FAudioMotorModelDebugWidgetChildWindow`
- L51 _public function_ `FAudioMotorModelDebugDetailWindow(const FStringView& WindowTitle, const FVector2f& WindowSize) : FAudioMotorModelDebugWidgetChildWindow(WindowTitle, WindowSize)`
- L55 _public prototype_ `virtual void SendDebugData(TConstArrayView<FInstancedStruct> DebugDataView) = 0;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelDebuggerParamGraph.h` (Private)


#### struct `AudioMotorModelDebug::FParamGraphSettings`  
`struct FParamGraphSettings`  
_L12-17_
- L14 _public member_ `FDoubleRange GraphRange = FDoubleRange(0, 1);`
- L15 _public member_ `FLinearColor GraphLineColor = FLinearColor::MakeRandomColor();`
- L16 _public member_ `bool bAdaptive = true;`

#### class `AudioMotorModelDebug::IParamGraph`  
`class IParamGraph`  
_L19-28_
- L23 _public prototype_ `virtual ~IParamGraph() = default;`
- L25 _public prototype_ `virtual void Draw() = 0;`
- L26 _public prototype_ `virtual void SetScale(const float InScale) = 0;`
- L27 _public prototype_ `virtual void SetNumFrames(const uint32 InNumFrames) = 0;`

#### class `AudioMotorModelDebug::TParamGraphRingBuffer`  
`template <typename RingBufferType> class TParamGraphRingBuffer : public IParamGraph`  
_L31-60_
- inherits: `IParamGraph`
- L34 _public function_ `virtual void Draw() override`
- L35 _public function_ `virtual void SetScale(const float InScale) override`
- L40 _public function_ `virtual void SetNumFrames(const uint32 InNumFrames) override`
- L54 _protected member_ `float Scale = 1.f;`
- L55 _protected member_ `int32 NumFrames = 100;`
- L56 _protected member_ `uint32 NumFramesMax = 1000;`
- L58 _protected member_ `TRingBuffer<RingBufferType> GraphValues;`

#### class `AudioMotorModelDebug::FDoubleRingBufferParamGraph`  
`class FDoubleRingBufferParamGraph : public TParamGraphRingBuffer<double>`  
_L62-76_
- inherits: `TParamGraphRingBuffer<double>`
- L65 _public prototype_ `FDoubleRingBufferParamGraph(const FName& ParameterName, const FParamGraphSettings& InGraphSettings = FParamGraphSettings());`
- L68 _protected prototype_ `void DrawGraph(const double& ParamValue);`
- L70 _protected member_ `const FName ParamName;`
- L72 _protected member_ `FDoubleRange GraphRange;`
- L73 _protected member_ `FLinearColor GraphLineColor;`
- L75 _protected member_ `bool bIsAdaptive = false;`

#### class `AudioMotorModelDebug::FPropertyGraph`  
`class FPropertyGraph : public FDoubleRingBufferParamGraph`  
_L80-123_
- inherits: `FDoubleRingBufferParamGraph`
- desc: Param Graph that gets its value from a FProperty in the provided container ptr, WHICH IS NOT kept alive by the graph
- L83 _public prototype_ `FPropertyGraph(const FName& InPropertyName, const FProperty& InParamProperty, const void* PropertyContainerPtr, const FParamGraphSettings& InGraphSettings = FParamGraphSettings());`
- L85 _public prototype_ `virtual void Draw() override;`
- L89 _private function_ `template <typename OutValue> OutValue GetPropertyValue()`
- L121 _private member_ `const void* PropertyValuePtr;`
- L122 _private member_ `TVariant<FEmptyVariantState, const FIntProperty*, const FFloatProperty*, const FBoolProperty*> PropertyFieldVariant;`

#### class `AudioMotorModelDebug::FParamPtrGraph`  
`template <typename ParamType> class FParamPtrGraph : public FDoubleRingBufferParamGraph`  
_L127-148_
- inherits: `FDoubleRingBufferParamGraph`
- desc: Param Graph that gets its value from a ParamType*, WITHOUT keeping it alive
- L131 _public function_ `FParamPtrGraph(const FName& InParamName, const ParamType* InParamToDraw, const FParamGraphSettings& InGraphSettings = FParamGraphSettings()) : FDoubleRingBufferParamGraph(InParamName, InGraphSettings) , ParamToDraw(InParamToDraw)`
- L136 _public function_ `virtual void Draw() override`
- L147 _private member_ `ParamType* ParamToDraw;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AudioMotorModelDebug`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelDebuggerPropertyUI.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AudioMotorModelDebuggerPropertyUI`
- L11 _prototype_ `void DrawPropertyUI(const FProperty& InProperty, void* ContainerPtr, bool bDisplayPropertyName = true);` (scope `AudioMotorModelDebuggerPropertyUI`)
- L12 _prototype_ `void DrawArrayPropertyUI(const FArrayProperty& InArrayProperty, const void* ContainerPtr, bool bDisplayArrayName = true);` (scope `AudioMotorModelDebuggerPropertyUI`)
- L13 _prototype_ `bool CanDrawProperty(const FProperty& InProperty);` (scope `AudioMotorModelDebuggerPropertyUI`)
- L21 _variable_ `const FString& MetaClampMinString = TargetProperty.GetMetaData("Cla` (scope `AudioMotorModelDebuggerPropertyUI`)
- L22 _variable_ `const FString& MetaClampMaxString = TargetProperty.GetMetaData("Cla` (scope `AudioMotorModelDebuggerPropertyUI`)
- L23 _variable_ `const FString& MetaUIMinString = TargetProperty.GetMetaData("UIM` (scope `AudioMotorModelDebuggerPropertyUI`)
- L24 _variable_ `const FString& MetaUIMaxString = TargetProperty.GetMetaData("UIM` (scope `AudioMotorModelDebuggerPropertyUI`)
- L26 _variable_ `NumericType ClampMin = MinMaxLimits.Key;` (scope `AudioMotorModelDebuggerPropertyUI`)
- L32 _variable_ `NumericType ClampMax = MinMaxLimits.Value;` (scope `AudioMotorModelDebuggerPropertyUI`)
- L38 _variable_ `NumericType UIMin = MinMaxLimits.Key;` (scope `AudioMotorModelDebuggerPropertyUI`)
- L44 _variable_ `NumericType UIMax = MinMaxLimits.Value;` (scope `AudioMotorModelDebuggerPropertyUI`)
- L50 _variable_ `const NumericType MinAllowedValue = FMath::Max(UIMin, ClampMin);` (scope `AudioMotorModelDebuggerPropertyUI`)
- L51 _variable_ `const NumericType MaxAllowedValue = FMath::Min(UIMax, ClampMax);` (scope `AudioMotorModelDebuggerPropertyUI`)

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelSlateIMDebugger.h` (Private)


#### class `FAudioMotorModelSlateIMDebugger`  
`class FAudioMotorModelSlateIMDebugger : public IAudioMotorModelDebugger`  
_L9-23_
- inherits: `IAudioMotorModelDebugger`
- L12 _public prototype_ `FAudioMotorModelSlateIMDebugger();`
- L14 _public prototype_ `virtual void RegisterComponentWithDebugger(UAudioMotorModelComponent* MotorModelComponent) override;`
- L15 _public prototype_ `virtual void SendAdditionalDebugData(UObject* Object, const FInstancedStruct& InData) override;`
- L18 _private member_ `FAudioMotorModelSlateIMWindow SlateIMWindow;`
- L21 _private member_ `FAudioMotorModelSlateIMViewportWidget SlateIMViewportWidget;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/AudioMotorModelSlateIMWindow.h` (Private)


#### class `FAudioMotorModelSlateIMWindow`  
`class FAudioMotorModelSlateIMWindow : public FSlateIMNomadTabBase`  
_L9-17_
- inherits: `FSlateIMNomadTabBase`
- L12 _public prototype_ `FAudioMotorModelSlateIMWindow(const TCHAR* Command, const TCHAR* CommandHelp);`
- L14 _public prototype_ `virtual void DrawContent(float DeltaTime) override;`
- L16 _public member_ `FAudioMotorModelDebugWidget DebugWidget;`

#### class `FAudioMotorModelSlateIMViewportWidget`  
`class FAudioMotorModelSlateIMViewportWidget : public FSlateIMWidgetWithCommandBase`  
_L20-31_
- inherits: `FSlateIMWidgetWithCommandBase`
- L23 _public prototype_ `FAudioMotorModelSlateIMViewportWidget(const TCHAR* Command, const TCHAR* CommandHelp);`
- L25 _public prototype_ `virtual void DrawWidget(float DeltaTime) override;`
- L27 _public member_ `FAudioMotorModelDebugWidget DebugWidget;`
- L30 _private member_ `SlateIM::FViewportRootLayout Layout;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Private/MotorSimComponentDetailWindow.h` (Private)


#### class `FMotorSimComponentDetailWindow`  
`class FMotorSimComponentDetailWindow : public FAudioMotorModelDebugDetailWindow`  
_L13-40_
- inherits: `FAudioMotorModelDebugDetailWindow`
- L16 _public prototype_ `explicit FMotorSimComponentDetailWindow(const FStringView& WindowTitle);`
- L18 _public prototype_ `virtual void SendDebugData(TConstArrayView<FInstancedStruct> DebugDataView) override;`
- L21 _private prototype_ `virtual void DrawWindow(float DeltaTime) override;`
- L22 _private prototype_ `void GenerateParamSelector(const TPair<FName, double>& ParamNameValue);`
- L23 _private prototype_ `void DrawParameterSelection();`
- L24 _private prototype_ `void DrawParameterGraphs();`
- L25 _private prototype_ `void EnableMotorSimComponentDetails() const;`
- L27 _private member_ `TMap<FName, double> ParameterValues;`
- L28 _private member_ `TMap<FName, AudioMotorModelDebug::FParamPtrGraph<const double>> ParamGraphs;`
- L30 _private member_ `int32 GraphRowSize = 2;`
- L31 _private member_ `int32 MaxGraphRowSize = 50;`
- L32 _private member_ `int32 LiveGraphRowSize = GraphRowSize;`
- L33 _private member_ `FString GraphRowSizeText = FString::FromInt(GraphRowSize);`
- L35 _private member_ `float ParamGraphScale = 1.0f;`
- L36 _private member_ `float ParamGraphScaleMax = 5.0f;`
- L38 _private member_ `float ParamGraphNumFrames = 300.0f;`
- L39 _private member_ `float ParamGraphNumFramesMax = 1000.0f;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AudioMotorModelDebugger`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimDebug/Public/AudioMotorSimDebug.h` (Public)


#### class `FAudioMotorSimDebugModule`  
`class FAudioMotorSimDebugModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TUniquePtr<FAudioMotorModelSlateIMDebugger> SlateIMDebugger;`
