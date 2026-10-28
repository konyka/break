# Plugins / RenderTrace

- module root: `Plugins/Runtime/RenderTrace/Source`
- headers: 3; symbols: 37
- symbol kinds: class=3, delegate=2, function=6, macro=2, member=5, prototype=18, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, MaterialUtilities, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 

### `Plugins/Runtime/RenderTrace/Source/Private/Materials/MaterialExpressionPhysicalMaterialOutput.h` (Private)


#### struct `FPhysicalMaterialTraceInput`  
`struct FPhysicalMaterialTraceInput`  
_L17-30_
- reflection: `USTRUCT()`
- desc: Structure linking a material expression input with a physical material. For use by UMaterialExpressionPhysicalMaterialOutput.
- L22 _public member_ `TObjectPtr<UPhysicalMaterial> PhysicalMaterial;` — `UPROPERTY(EditAnywhere, Category = PhysicalMaterial)`
- L25 _public member_ `FExpressionInput Input;` — `UPROPERTY(meta = (RequiredInput = "true"))`
- L27 _public function_ `FPhysicalMaterialTraceInput() : PhysicalMaterial(nullptr)`

#### class `UMaterialExpressionPhysicalMaterialOutput`  
`class UMaterialExpressionPhysicalMaterialOutput : public UMaterialExpressionCustomOutput`  
_L36-67_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories=Object)`
- inherits: `UMaterialExpressionCustomOutput`
- desc: Custom output node to write out physical material weights.
- L42 _private member_ `TArray<FPhysicalMaterialTraceInput> Inputs;` — `UPROPERTY(EditAnywhere, Category = PhysicalMaterial)` — Array of physical material inputs.
- L45 _private prototype_ `const UPhysicalMaterial* GetInputMaterialFromMap(int32 Index) const;`
- L46 _private prototype_ `void FillMaterialNames();`
- L49 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _private prototype_ `virtual void PostLoad() override;`
- L54 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L55 _private prototype_ `virtual TArrayView<FExpressionInput*> GetInputsView() override;`
- L56 _private prototype_ `virtual FExpressionInput* GetInput(int32 InputIndex) override;`
- L57 _private prototype_ `virtual FName GetInputName(int32 InputIndex) const override;`
- L58 _private function_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override`
- L59 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L64 _private prototype_ `virtual int32 GetNumOutputs() const override;`
- L65 _private function_ `virtual FString GetFunctionName() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RENDERTRACE_API`

### `Plugins/Runtime/RenderTrace/Source/Public/RenderTrace.h` (Public)


#### class `FRenderTraceQueue`  
`class FRenderTraceQueue : FTickableGameObject`  
_L22-49_
- inherits: `FTickableGameObject`
- desc: The work uses the GPU so this object handles reading back the data without stalling. All calls are expected to be made on the game thread only.
- L25 _public prototype_ `FRenderTraceQueue() = default;`
- L26 _public prototype_ `~FRenderTraceQueue() = default;`
- L34 _public prototype_ `uint32 AsyncRenderTraceComponents(TArrayView<const class UPrimitiveComponent*> PrimitiveComponents, FVector RayOrigin, FVector RayDirection, FRenderTraceDelegate OnComplete, int64 UserData = 0);` — Initialize the task for a list of components. Previously queued tasks will continue to process. Returns the unique ID of the task that will be sent with the OnCompletion callback, or 0 if the request was invalid or there were no valid primitives to check.
- L35 _public prototype_ `void CancelAsyncSample(uint32 RequestID);`
- L38 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject begin
- L39 _public function_ `virtual TStatId GetStatId() const override`
- L40 _public function_ `virtual bool IsTickable() const override`
- L41 _public function_ `virtual bool IsTickableInEditor() const override`
- L44 _public prototype_ `static bool IsEnabled();`
- L47 _private member_ `uint32 LastRequestID = 0;`
- L48 _private member_ `TArray<TSharedPtr<struct FRenderTraceTask>> RequestsInFlight;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RENDERTRACE_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderTrace, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderTrace, Log, All);`
- L16 _delegate_ `DECLARE_DELEGATE_ThreeParams(FRenderTraceDelegate, uint32 TaskID, class UPhysicalMaterial const*, int64 UserData);`
- L16 _prototype_ `DECLARE_DELEGATE_ThreeParams(FRenderTraceDelegate, uint32 TaskID, class UPhysicalMaterial const*, int64 UserData);`

### `Plugins/Runtime/RenderTrace/Source/Public/RenderTraceModule.h` (Public)


#### class `IRenderTraceModule`  
`class IRenderTraceModule : public IModuleInterface`  
_L10-13_
- inherits: `IModuleInterface`
- desc: RenderTrace module interface
