# Plugins / PhysicsControlUncookedOnly

- module root: `Plugins/Animation/PhysicsControl/Source/PhysicsControlUncookedOnly`
- headers: 2; symbols: 37
- symbol kinds: class=2, function=2, macro=1, member=5, prototype=27
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationCore, AnimationEditor, BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, Kismet, Persona, PhysicsControl, Slate, SlateCore, UnrealEd

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlUncookedOnly/Public/AnimGraphNode_RigidBodyWithControl.h` (Public)


#### class `UAnimGraphNode_RigidBodyWithControl`  
`class UAnimGraphNode_RigidBodyWithControl : public UAnimGraphNode_SkeletalControlBase`  
_L13-65_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Simulate Rigid Body Physics Ragdoll"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_RigidBodyWithControl Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const;`
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual FString GetNodeCategory() const override;`
- L26 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L30 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp, const bool bIsSelected, const bool bIsPoseWatchEnabled) const override;` — UAnimGraphNode_Base
- L31 _public prototype_ `virtual void OnPoseWatchChanged(const bool IsPoseWatchActive, TObjectPtr<UPoseWatch> InPoseWatch, FEditorModeTools& InModeTools, FAnimNode_Base* InRuntimeNode) override;`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L37 _public prototype_ `virtual void PostPasteNode() override;`
- L38 _public prototype_ `virtual void DestroyNode() override;`
- L40 _public prototype_ `void ToggleBodyVisibility();`
- L41 _public prototype_ `void ToggleConstraintVisibility();`
- L42 _public prototype_ `void ToggleControlSetViewerTab();`
- L44 _public prototype_ `TArray<TPair<FName, TArray<FName>>> GenerateControlsAndBodyModifierNames() const;`
- L46 _public prototype_ `USkeleton* GetSkeleton() const;`
- L50 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L51 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L54 _protected prototype_ `bool AreAnyBodiesHidden() const;`
- L55 _protected prototype_ `bool AreAnyConstraintsHidden() const;`
- L56 _protected prototype_ `bool IsControlSetViewerTabOpen() const;`
- L58 _protected prototype_ `void PostChange();`
- L61 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementBodies;`
- L62 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementConstraints;`
- L63 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementParentSpaceControls;`
- L64 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementWorldSpaceControls;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PHYSICSCONTROLUNCOOKEDONLY_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlUncookedOnly/Public/IPhysicsControlOperatorViewerInterface.h` (Public)


#### class `IPhysicsControlOperatorViewerInterface`  
`class IPhysicsControlOperatorViewerInterface : public IModularFeature`  
_L8-23_
- inherits: `IModularFeature`
- L11 _public function_ `static FName GetModularFeatureName()`
- L17 _public prototype_ `virtual void OpenOperatorNamesTab() = 0;`
- L18 _public prototype_ `virtual void CloseOperatorNamesTab() = 0;`
- L19 _public prototype_ `virtual void ToggleOperatorNamesTab() = 0;`
- L20 _public prototype_ `virtual bool IsOperatorNamesTabOpen() = 0;`
- L21 _public prototype_ `virtual void RequestRefresh() = 0;`
