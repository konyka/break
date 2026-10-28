# Plugins / AnimationLayeringUncookedOnly

- module root: `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayeringUncookedOnly`
- headers: 4; symbols: 39
- symbol kinds: class=4, function=2, macro=1, member=3, namespace=1, prototype=28
- PrivateDependencyModuleNames: BlueprintGraph, CoreUObject, EditorFramework, Engine, Kismet, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationCore, AnimationLayering, AnimationModifierLibrary, Core, ToolMenus

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayeringUncookedOnly/Public/AnimGraph/AnimGraphNode_BoneMask.h` (Public)


#### class `UAnimGraphNode_BoneMask`  
`class UAnimGraphNode_BoneMask : public UAnimGraphNode_BlendListBase`  
_L12-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase`
- L17 _private member_ `FAnimNode_BoneMask Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L21 _private prototype_ `virtual void PostLoad() override;`
- L25 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L26 _private prototype_ `virtual FText GetTooltipText() const override;`
- L27 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L28 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L36 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L37 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L38 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L43 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — Gives each visual node a chance to validate that they are still valid in the context of the compiled class, giving a last shot at error or warning generation after primary compilation is finished

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayeringUncookedOnly/Public/AnimGraph/AnimGraphNode_CopyBoneAdvanced.h` (Public)


#### class `UAnimGraphNode_CopyBoneAdvanced`  
`class UAnimGraphNode_CopyBoneAdvanced : public UAnimGraphNode_SkeletalControlBase`  
_L10-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L15 _private member_ `FAnimNode_CopyBoneAdvanced Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L19 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L20 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L26 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L27 _protected prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L28 _protected prototype_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;`

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayeringUncookedOnly/Public/AnimGraph/AnimGraphNode_CopyBoneMotion.h` (Public)


#### class `UAnimGraphNode_CopyBoneMotion`  
`class UAnimGraphNode_CopyBoneMotion : public UAnimGraphNode_SkeletalControlBase`  
_L15-45_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L20 _private member_ `FAnimNode_CopyBoneMotion Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L35 _protected prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* AnimNode) override;`
- L36 _protected prototype_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;`
- L39 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L43 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONLAYERINGUNCOOKEDONLY_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayeringUncookedOnly/Public/BoneMaskDetailCustomization.h` (Public)


#### class `FBoneMaskEntryDetails`  
`class FBoneMaskEntryDetails : public IPropertyTypeCustomization`  
_L13-23_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _protected prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L22 _protected prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
