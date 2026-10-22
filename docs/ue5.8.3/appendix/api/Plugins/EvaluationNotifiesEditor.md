# Plugins / EvaluationNotifiesEditor

- module root: `Plugins/Experimental/EvaluationNotifies/Source/Editor`
- headers: 2; symbols: 15
- symbol kinds: class=2, function=1, member=1, namespace=1, prototype=10
- PrivateDependencyModuleNames: BlueprintGraph, EditorFramework, Kismet, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, AnimationModifiers, Core, CoreUObject, Engine, EvaluationNotifiesRuntime

### `Plugins/Experimental/EvaluationNotifies/Source/Editor/Public/AnimGraph/AnimGraphNode_EvaluationNotifies.h` (Public)


#### class `UAnimGraphNode_EvaluationNotifies`  
`class UAnimGraphNode_EvaluationNotifies : public UAnimGraphNode_SkeletalControlBase`  
_L11-39_
- reflection: `UCLASS()`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L16 _private member_ `FAnimNode_EvaluationNotifies Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L26 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L27 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L32 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L36 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L37 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENodeTitleType`

### `Plugins/Experimental/EvaluationNotifies/Source/Editor/Public/EvaluationNotifiesEditorModule.h` (Public)


#### class `IEvaluationNotifiesEditorModule`  
`class IEvaluationNotifiesEditorModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
