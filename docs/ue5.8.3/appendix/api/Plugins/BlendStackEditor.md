# Plugins / BlendStackEditor

- module root: `Plugins/Animation/BlendStack/Source/Editor`
- headers: 6; symbols: 46
- symbol kinds: class=7, delegate=1, function=2, macro=1, member=4, prototype=31
- PrivateDependencyModuleNames: BlueprintGraph, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationCore, BlendStack, Core, CoreUObject, Engine

### `Plugins/Animation/BlendStack/Source/Editor/Public/AnimGraphNode_BlendStack.h` (Public)


#### class `UAnimGraphNode_BlendStack_Base`  
`class UAnimGraphNode_BlendStack_Base : public UAnimGraphNode_AssetPlayerBase`  
_L14-55_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L19 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L20 _public prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L22 _public prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;`
- L23 _public prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L24 _public prototype_ `virtual const TCHAR* GetTimePropertyName() const override;`
- L25 _public prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L27 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L28 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L29 _public prototype_ `virtual void JumpToDefinition() const override;`
- L30 _public prototype_ `virtual void DestroyNode() override;`
- L31 _public prototype_ `virtual void PostPasteNode() override;`
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L34 _public prototype_ `virtual TArray<UEdGraph*> GetSubGraphs() const override;`
- L35 _public prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L39 _protected prototype_ `void ExpandGraphAndProcessNodes( int GraphIndex, UEdGraph* SourceGraph, UAnimGraphNode_Base* SourceRootNode, TArrayView<UAnimGraphNode_BlendStackInput*> SourceInputNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData, UAnimGraphNode_Base*& OutRootNode, TArrayView<UAnimGraphNode_BlendStackInput*> OutInputNodes);` — Helper function for compilation
- L46 _protected prototype_ `virtual FAnimNode_BlendStack_Standalone* GetBlendStackNode() const PURE_VIRTUAL(UAnimGraphNode_BlendStack_Base::GetBlendStackNode, return nullptr;);`
- L47 _protected prototype_ `int32 GetMaxActiveBlends() const;`
- L51 _private prototype_ `void CreateGraph();`
- L54 _private member_ `TObjectPtr<UEdGraph> BoundGraph = nullptr;` — `UPROPERTY()`

#### class `UAnimGraphNode_BlendStack`  
`class UAnimGraphNode_BlendStack : public UAnimGraphNode_BlendStack_Base`  
_L58-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendStack_Base`
- L63 _private member_ `FAnimNode_BlendStack Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L65 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L66 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L67 _private prototype_ `virtual FText GetTooltipText() const override;`
- L68 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L69 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L72 _protected function_ `virtual FAnimNode_BlendStack_Standalone* GetBlendStackNode() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BLENDSTACKEDITOR_API`

### `Plugins/Animation/BlendStack/Source/Editor/Public/AnimGraphNode_BlendStackInput.h` (Public)


#### class `UAnimGraphNode_BlendStackInput`  
`class UAnimGraphNode_BlendStackInput : public UAnimGraphNode_Base`  
_L11-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _public member_ `FAnimNode_BlendStackInput Node;` — `UPROPERTY(EditAnywhere, Category = "Inputs")`
- L19 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L20 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L22 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L23 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L24 _public prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L27 _public function_ `bool IsEditable() const` — @return whether this node is editable. Non-editable nodes are implemented from function interfaces

### `Plugins/Animation/BlendStack/Source/Editor/Public/AnimGraphNode_BlendStackResult.h` (Public)


#### class `UAnimGraphNode_BlendStackResult`  
`class UAnimGraphNode_BlendStackResult : public UAnimGraphNode_Root`  
_L10-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Root`
- L14 _private prototype_ `virtual bool IsNodeRootSet() const override;`

### `Plugins/Animation/BlendStack/Source/Editor/Public/AnimationBlendStackGraph.h` (Public)


#### class `UAnimationBlendStackGraph`  
`class UAnimationBlendStackGraph : public UAnimationGraph`  
_L15-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraph`
- desc: Animation graph used for blend stacks. The result node is the root of the blend graph. The input node is dynamically linked to the blend stack's sample pose.
- L22 _public member_ `TObjectPtr<class UAnimGraphNode_Root> ResultNode = nullptr;` — `UPROPERTY()` — Result node within the state's animation graph

### `Plugins/Animation/BlendStack/Source/Editor/Public/AnimationBlendStackGraphSchema.h` (Public)


#### class `UAnimationBlendStackGraphSchema`  
`class UAnimationBlendStackGraphSchema : public UAnimationGraphSchema`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraphSchema`
- L14 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`

### `Plugins/Animation/BlendStack/Source/Editor/Public/BlendStackEditor.h` (Public)


#### class `IBlendStackEditorModuleInterface`  
`class IBlendStackEditorModuleInterface : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlendStackEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlendStackEditor, Log, All);`
