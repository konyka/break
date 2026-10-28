# Plugins / HierarchyTableAnimationUncookedOnly

- module root: `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/UncookedOnly`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=1, prototype=9
- PrivateDependencyModuleNames: BlueprintGraph, EditorFramework, Kismet, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, ToolMenus

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/UncookedOnly/Public/AnimGraphNode_BlendProfileLayeredBlend.h` (Public)


#### class `UAnimGraphNode_BlendProfileLayeredBlend`  
`class UAnimGraphNode_BlendProfileLayeredBlend : public UAnimGraphNode_BlendListBase`  
_L12-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase`
- L17 _private member_ `FAnimNode_BlendProfileLayeredBlend Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L31 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L32 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/UncookedOnly/Public/HierarchyTableAnimationUncookedOnlyModule.h` (Public)


#### class `FHierarchyTableAnimationUncookedOnlyModule`  
`class FHierarchyTableAnimationUncookedOnlyModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
