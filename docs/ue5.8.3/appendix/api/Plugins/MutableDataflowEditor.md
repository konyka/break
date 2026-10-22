# Plugins / MutableDataflowEditor

- module root: `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor`
- headers: 25; symbols: 226
- symbol kinds: class=1, function=12, member=62, prototype=115, struct=36
- PrivateDependencyModuleNames: DataflowCore, DataflowEditor, DataflowEngine
- PublicDependencyModuleNames: Core, CoreUObject, CustomizableObject, Engine

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/MutableDataflowEditorModule.h` (Public)


#### class `FMutableDataflowEditorModule`  
`class FMutableDataflowEditorModule : public IModuleInterface`  
_L6-9_
- inherits: `IModuleInterface`
- L8 _private prototype_ `virtual void StartupModule() override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/MutableDataflowParameters.h` (Public)


#### struct `FMutableParameterBase`  
`struct FMutableParameterBase`  
_L14-27_
- reflection: `USTRUCT()`
- L18 _public prototype_ `virtual ~FMutableParameterBase() = default;`
- L21 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`
- L23 _public function_ `bool operator== (const FMutableParameterBase& Other) const`

#### struct `FMutableSkeletalMeshParameter`  
`struct FMutableSkeletalMeshParameter : public FMutableParameterBase`  
_L31-37_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L36 _public member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableTextureParameter`  
`struct FMutableTextureParameter : public FMutableParameterBase`  
_L41-47_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L46 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableMaterialParameter`  
`struct FMutableMaterialParameter : public FMutableParameterBase`  
_L51-57_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L56 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableBoolParameter`  
`struct FMutableBoolParameter : public FMutableParameterBase`  
_L61-67_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L66 _public member_ `bool Bool;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableEnumParameter`  
`struct FMutableEnumParameter : public FMutableParameterBase`  
_L71-77_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L76 _public member_ `FString OptionName;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableFloatParameter`  
`struct FMutableFloatParameter : public FMutableParameterBase`  
_L81-87_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L86 _public member_ `float Float;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableVectorParameter`  
`struct FMutableVectorParameter : public FMutableParameterBase`  
_L91-97_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L96 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableProjectorParameter`  
`struct FMutableProjectorParameter : public FMutableParameterBase`  
_L101-107_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L106 _public member_ `FCustomizableObjectProjector Projector;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableTransformParameter`  
`struct FMutableTransformParameter : public FMutableParameterBase`  
_L111-117_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L116 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FMutableInstancedStructParameter`  
`struct FMutableInstancedStructParameter : public FMutableParameterBase`  
_L121-127_
- reflection: `USTRUCT(BlueprintType, meta = (Experimental))`
- inherits: `FMutableParameterBase`
- L126 _public member_ `FInstancedStruct InstancedStruct;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/COInstanceGeneratorNode.h` (Public)


#### struct `FMutableGeneratedResource`  
`struct FMutableGeneratedResource`  
_L17-26_
- reflection: `USTRUCT(meta = (Experimental))`
- L22 _public member_ `FString ComponentName;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`
- L25 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Mutable")`

#### struct `FCOInstanceGetComponentMesh`  
`struct FCOInstanceGetComponentMesh : public FDataflowNode`  
_L30-49_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FDataflowNode`
- L39 _public member_ `TArray<FMutableGeneratedResource> GeneratedResources;` — `UPROPERTY(meta = (DataflowInput))`
- L42 _public member_ `TObjectPtr<USkeletalMesh> ComponentSkeletalMesh;` — `UPROPERTY(meta = (DataflowOutput))`
- L46 _public prototype_ `FCOInstanceGetComponentMesh(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L48 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCOInstanceGeneratorNode`  
`struct FCOInstanceGeneratorNode : public FDataflowNode`  
_L57-211_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FDataflowNode`
- desc: Node designed to work as an entry point for mutable in the DataFlow graph. It allows the setup of a Customizable Object Instance and the extraction of the skeletal meshes generated by its update.
- L64 _public prototype_ `FCOInstanceGeneratorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L66 _public prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L68 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L75 _private member_ `TObjectPtr<UCustomizableObject> CustomizableObject;` — `UPROPERTY(EditAnywhere, Category = "Mutable", meta = (DataflowInput))`
- L79 _private member_ `TArray<FMutableSkeletalMeshParameter> SkeletalMeshParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L80 _private member_ `TArray<FMutableSkeletalMeshParameter> CachedSkeletalMeshParameters;`
- L83 _private member_ `TArray<FMutableTextureParameter> TextureParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L84 _private member_ `TArray<FMutableTextureParameter> CachedTextureParameters;`
- L87 _private member_ `TArray<FMutableMaterialParameter> MaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L88 _private member_ `TArray<FMutableMaterialParameter> CachedMaterialParameters;`
- L91 _private member_ `TArray<FMutableBoolParameter> BoolParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L92 _private member_ `TArray<FMutableBoolParameter> CachedBoolParameters;`
- L95 _private member_ `TArray<FMutableEnumParameter> EnumParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L96 _private member_ `TArray<FMutableEnumParameter> CachedEnumParameters;`
- L99 _private member_ `TArray<FMutableFloatParameter> FloatParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L100 _private member_ `TArray<FMutableFloatParameter> CachedFloatParameters;`
- L103 _private member_ `TArray<FMutableVectorParameter> VectorParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L104 _private member_ `TArray<FMutableVectorParameter> CachedVectorParameters;`
- L107 _private member_ `TArray<FMutableProjectorParameter> ProjectorParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L108 _private member_ `TArray<FMutableProjectorParameter> CachedProjectorParameters;`
- L111 _private member_ `TArray<FMutableTransformParameter> TransformParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L112 _private member_ `TArray<FMutableTransformParameter> CachedTransformParameters;`
- L115 _private member_ `TArray<FMutableInstancedStructParameter> InstancedStructParameters;` — `UPROPERTY(EditAnywhere, Category = "Mutable Parameters", meta = (DataflowInput))`
- L116 _private member_ `TArray<FMutableInstancedStructParameter> CachedInstancedStructParameters;`
- L122 _private member_ `TArray<FMutableGeneratedResource> GeneratedResources;` — `UPROPERTY(meta = (DataflowOutput))` — First option : an array of structures that contain the pair of data Component name + Skeletal Mesh
- L125 _private member_ `TArray<TObjectPtr<USkeletalMesh>> GeneratedSkeletalMeshes;` — `UPROPERTY(meta = (DataflowOutput))`
- L130 _private member_ `TObjectPtr<UCustomizableObjectInstance> CustomizableObjectInstance;` — `UPROPERTY(EditAnywhere, Category = "Mutable", meta = (DisplayName = "Generated COI"))` — Instance generated during the runtime and used to generate the output resources
- L134 _private member_ `FDataflowFunctionProperty GenerateInstanceResources;` — `UPROPERTY(EditAnywhere, Category = "Mutable", meta = (DisplayName = "Generate Resources", ButtonImage = "Icons.Refresh"))` — Press this button to trigger first a CO compilation and then a COI update. This will generate the resources needed by the outputs of the node.
- L138 _private member_ `bool bIsGeneratingResources = false;` — Variable that works as a semaphore to prevent the scheduling of multiple Instance Compilation + Updates
- L144 _private prototype_ `void OnGenerateInstanceResourcesRequested(UE::Dataflow::FContext& Context);` — Callback method invoked when the "Generate outputs" button gets pressed. It will trigger the compilation and later update of the generated Customizable Object Instance
- L156 _private function_ `template<typename T> TArray<T> GetPropertyParameters(const TArray<T>* InParametersArrayProperty, const FString& ParameterTypeName, UE::Dataflow::FContext& Context)` — Get all the unique parameters defined for a given property. @tparam T The type of parameter. EX : FMutableProjectorParameter, FMutableMaterialParameter ... @param InParametersArrayProperty The property used as source to find the parameters. @param ParameterTypeName The descriptive name of the parameter type. Used for logging. @param Context The Dataflow context. @return An array with all the parameters found. Only the first occurrence of each parameter will be placed there.
- L182 _private prototype_ `void CacheNodeInputs(UE::Dataflow::FContext& Context);` — Evaluate the input nodes and add their data to our local caches so we can later access it without the dataflow context
- L188 _private prototype_ `void ApplyInstanceParameters(UCustomizableObjectInstance& Instance);` — Apply the values in the cached parameters into the provided Instance @param Instance The instance that will get its parameters updated
- L193 _private prototype_ `void ClearCachedParameters();` — Empty the caches holding the data provided by the evaluation of the input pins
- L198 _private prototype_ `void RequestCompilation(UE::Dataflow::FContext& Context);` — Request the compilation of the CO so we can later generate a Customizable Object Instance.
- L203 _private prototype_ `void RequestUpdate(UCustomizableObjectInstance& Instance);` — Request the Update of the given COI.
- L210 _private prototype_ `TArray<FMutableGeneratedResource> GetInstanceGeneratedMeshes(const UCustomizableObjectInstance& Instance) const;` — Extract from the given Customizable Object Instance the generated skeletal meshes for each one of the components the instance has. @param Instance The COI we want to get the data from @return An array of structures composed by the component name and the skeletal mesh generated for said component..

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableBoolParametersArrayNode.h` (Public)


#### struct `FMakeMutableBoolParametersArrayNode`  
`struct FMakeMutableBoolParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L16-40_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L26 _public member_ `TArray<FMutableBoolParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Bool Parameters"))`
- L30 _public prototype_ `FMakeMutableBoolParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L32 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L35 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L36 _public prototype_ `virtual bool CanRemovePin() const override;`
- L37 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L38 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L39 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableEnumParametersArrayNode.h` (Public)


#### struct `FMakeMutableEnumParametersArrayNode`  
`struct FMakeMutableEnumParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableEnumParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Enum Parameters"))`
- L29 _public prototype_ `FMakeMutableEnumParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableFloatParametersArrayNode.h` (Public)


#### struct `FMakeMutableFloatParametersArrayNode`  
`struct FMakeMutableFloatParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableFloatParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Float Parameters"))`
- L29 _public prototype_ `FMakeMutableFloatParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableInstancedStructParametersArrayNode.h` (Public)


#### struct `FMakeMutableInstancedStructParametersArrayNode`  
`struct FMakeMutableInstancedStructParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableInstancedStructParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Instanced Struct Parameters"))`
- L29 _public prototype_ `FMakeMutableInstancedStructParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableMaterialParametersArrayNode.h` (Public)


#### struct `FMakeMutableMaterialParametersArrayNode`  
`struct FMakeMutableMaterialParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableMaterialParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Material Parameters"))`
- L29 _public prototype_ `FMakeMutableMaterialParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableParametersArrayBaseNode.h` (Public)


#### struct `FMakeMutableParametersArrayBaseNode`  
`struct FMakeMutableParametersArrayBaseNode : public FDataflowNode`  
_L13-54_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FDataflowNode`
- L26 _protected member_ `static constexpr uint16 MinRequiredInputsCount = 1;` — The min amount of input pins the node can have.
- L29 _protected prototype_ `template<typename T> void AddDefaultInputs(TArray<T>& InParametersArray);`
- L32 _protected prototype_ `template<typename T> void EvaluateParameterNode(const TArray<T>& InputParameters, const TArray<T>& OutputParameters, UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L35 _protected prototype_ `template<typename T> UE::Dataflow::TConnectionReference<T> GetConnectionReference(const TArray<T>& ParametersArray, int32 Index) const;`
- L38 _protected prototype_ `template<typename T> TArray<UE::Dataflow::FPin> AddParameterPin(TArray<T>& InOutParametersArray);`
- L41 _protected prototype_ `template<typename T> bool CanRemoveParameterPin(const TArray<T>& ParametersArray) const;`
- L44 _protected prototype_ `template<typename T> TArray<UE::Dataflow::FPin> GetParameterPinsToRemove(const TArray<T>& ParametersArray) const;`
- L47 _protected prototype_ `template<typename T> void OnParameterPinRemoved(TArray<T>& InParametersArray, const UE::Dataflow::FPin& Pin);`
- L50 _protected prototype_ `template<typename T> void PostNodeSerialize(const TArray<T>& ParametersArray, const FArchive& Ar);`
- L53 _protected prototype_ `virtual bool CanAddPin() const override;` — FDataflowNode
- L57 _function_ `inline FMakeMutableParametersArrayBaseNode::FMakeMutableParametersArrayBaseNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid) : Super(InParam, InGuid)`
- L62 _function_ `inline bool FMakeMutableParametersArrayBaseNode::CanAddPin() const`
- L69 _function_ `template <typename T> void FMakeMutableParametersArrayBaseNode::AddDefaultInputs(TArray<T>& InParametersArray)`
- L79 _function_ `template <typename T> void FMakeMutableParametersArrayBaseNode::EvaluateParameterNode(const TArray<T>& InputParameters, const TArray<T>& OutputParameters, UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const`
- L98 _function_ `template<typename T> UE::Dataflow::TConnectionReference<T> FMakeMutableParametersArrayBaseNode::GetConnectionReference(const TArray<T>& ParametersArray, int32 Index) const`
- L105 _function_ `template <typename T> TArray<UE::Dataflow::FPin> FMakeMutableParametersArrayBaseNode::AddParameterPin(TArray<T>& InOutParametersArray)`
- L115 _function_ `template <typename T> bool FMakeMutableParametersArrayBaseNode::CanRemoveParameterPin(const TArray<T>& ParametersArray) const`
- L122 _function_ `template <typename T> TArray<UE::Dataflow::FPin> FMakeMutableParametersArrayBaseNode::GetParameterPinsToRemove(const TArray<T>& ParametersArray) const`
- L135 _function_ `template <typename T> void FMakeMutableParametersArrayBaseNode::OnParameterPinRemoved(TArray<T>& InParametersArray, const UE::Dataflow::FPin& Pin)`
- L150 _function_ `template <typename T> void FMakeMutableParametersArrayBaseNode::PostNodeSerialize(const TArray<T>& ParametersArray, const FArchive& Ar)`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableProjectorParametersArrayNode.h` (Public)


#### struct `FMakeMutableProjectorParametersArrayNode`  
`struct FMakeMutableProjectorParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableProjectorParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Projector Parameters"))`
- L29 _public prototype_ `FMakeMutableProjectorParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableSkeletalMeshParametersArrayNode.h` (Public)


#### struct `FMakeMutableSkeletalMeshParametersArrayNode`  
`struct FMakeMutableSkeletalMeshParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableSkeletalMeshParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Skeletal Mesh Parameters"))`
- L29 _public prototype_ `FMakeMutableSkeletalMeshParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableTextureParametersArrayNode.h` (Public)


#### struct `FMakeMutableTextureParametersArrayNode`  
`struct FMakeMutableTextureParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableTextureParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Texture Parameters"))`
- L29 _public prototype_ `FMakeMutableTextureParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableTransformParametersArrayNode.h` (Public)


#### struct `FMakeMutableTransformParametersArrayNode`  
`struct FMakeMutableTransformParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableTransformParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Transform Parameters"))`
- L29 _public prototype_ `FMakeMutableTransformParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MakeMutableVectorParametersArrayNode.h` (Public)


#### struct `FMakeMutableVectorParametersArrayNode`  
`struct FMakeMutableVectorParametersArrayNode : public FMakeMutableParametersArrayBaseNode`  
_L15-39_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMakeMutableParametersArrayBaseNode`
- L25 _public member_ `TArray<FMutableVectorParameter> GroupedParameters;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Vector Parameters"))`
- L29 _public prototype_ `FMakeMutableVectorParametersArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Overrides to allow the addition and removal of optional inputs
- L35 _public prototype_ `virtual bool CanRemovePin() const override;`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableBoolParameterNode.h` (Public)


#### struct `FMutableBoolParameterNode`  
`struct FMutableBoolParameterNode : public FMutableParameterNode`  
_L14-30_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L23 _public member_ `FMutableBoolParameter BoolParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `FMutableBoolParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableEnumParameterNode.h` (Public)


#### struct `FMutableEnumParameterNode`  
`struct FMutableEnumParameterNode : public FMutableParameterNode`  
_L14-30_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L23 _public member_ `FMutableEnumParameter EnumParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `FMutableEnumParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableFloatParameterNode.h` (Public)


#### struct `FMutableFloatParameterNode`  
`struct FMutableFloatParameterNode : public FMutableParameterNode`  
_L14-30_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L23 _public member_ `FMutableFloatParameter FloatParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `FMutableFloatParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableInstancedStructParameterNode.h` (Public)


#### struct `FMutableInstancedStructParameterNode`  
`struct FMutableInstancedStructParameterNode : public FMutableParameterNode`  
_L15-31_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L24 _public member_ `FMutableInstancedStructParameter InstancedStructParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L28 _public prototype_ `FMutableInstancedStructParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableMaterialParameterNode.h` (Public)


#### struct `FMutableMaterialParameterNode`  
`struct FMutableMaterialParameterNode : public FMutableParameterNode`  
_L13-29_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L22 _public member_ `FMutableMaterialParameter MaterialParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L26 _public prototype_ `FMutableMaterialParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L28 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableParameterNode.h` (Public)


#### struct `FMutableParameterNode`  
`struct FMutableParameterNode : public FDataflowNode`  
_L12-26_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FDataflowNode`
- L22 _public prototype_ `FMutableParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L25 _protected prototype_ `FString GetParameterName(UE::Dataflow::FContext& Context) const;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableProjectorParameterNode.h` (Public)


#### struct `FMutableProjectorParameterNode`  
`struct FMutableProjectorParameterNode : public FMutableParameterNode`  
_L13-29_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L22 _public member_ `FMutableProjectorParameter ProjectorParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L26 _public prototype_ `FMutableProjectorParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L28 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableSkeletalMeshParameterNode.h` (Public)


#### struct `FMutableSkeletalMeshParameterNode`  
`struct FMutableSkeletalMeshParameterNode : public FMutableParameterNode`  
_L14-30_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L23 _public member_ `FMutableSkeletalMeshParameter SkeletalMeshParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `FMutableSkeletalMeshParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableTextureParameterNode.h` (Public)


#### struct `FMutableTextureParameterNode`  
`struct FMutableTextureParameterNode : public FMutableParameterNode`  
_L13-29_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L22 _public member_ `FMutableTextureParameter TextureParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L26 _public prototype_ `FMutableTextureParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L28 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableTransformParameterNode.h` (Public)


#### struct `FMutableTransformParameterNode`  
`struct FMutableTransformParameterNode : public FMutableParameterNode`  
_L14-30_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L23 _public member_ `FMutableTransformParameter TransformParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `FMutableTransformParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MutableDataflow/Source/MutableDataflowEditor/Public/Nodes/MutableVectorParameterNode.h` (Public)


#### struct `FMutableVectorParameterNode`  
`struct FMutableVectorParameterNode : public FMutableParameterNode`  
_L13-29_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FMutableParameterNode`
- L22 _public member_ `FMutableVectorParameter VectorParameter;` — `UPROPERTY(meta = (DataflowOutput))`
- L26 _public prototype_ `FMutableVectorParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L28 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
