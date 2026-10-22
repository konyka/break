# Plugins / AnimationWarpingEditor

- module root: `Plugins/Animation/AnimationWarping/Source/Editor`
- headers: 10; symbols: 100
- symbol kinds: class=10, function=5, macro=8, member=13, namespace=8, prototype=56
- PrivateDependencyModuleNames: BlueprintGraph, EditorFramework, Kismet, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, AnimationModifierLibrary, AnimationModifiers, AnimationWarpingRuntime, Core, CoreUObject, Engine

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_FootPlacement.h` (Public)


#### class `UAnimGraphNode_FootPlacement`  
`class UAnimGraphNode_FootPlacement : public UAnimGraphNode_SkeletalControlBase`  
_L13-32_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_FootPlacement Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L30 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_OffsetRootBone.h` (Public)


#### class `UAnimGraphNode_OffsetRootBone`  
`class UAnimGraphNode_OffsetRootBone : public UAnimGraphNode_Base`  
_L15-39_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_Base`
- L21 _private member_ `FAnimNode_OffsetRootBone Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L31 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L36 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_OrientationWarping.h` (Public)


#### class `UAnimGraphNode_OrientationWarping`  
`class UAnimGraphNode_OrientationWarping : public UAnimGraphNode_SkeletalControlBase`  
_L13-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_OrientationWarping Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L28 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L29 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L34 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L38 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L39 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_OverrideRootMotion.h` (Public)


#### class `UAnimGraphNode_OverrideRootMotion`  
`class UAnimGraphNode_OverrideRootMotion : public UAnimGraphNode_Base`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_Base`
- L21 _private member_ `FAnimNode_OverrideRootMotion Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L29 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_SlopeWarping.h` (Public)


#### class `UAnimGraphNode_SlopeWarping`  
`class UAnimGraphNode_SlopeWarping : public UAnimGraphNode_SkeletalControlBase`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L20 _private member_ `FAnimNode_SlopeWarping Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L34 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L35 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_Steering.h` (Public)


#### class `UAnimGraphNode_Steering`  
`class UAnimGraphNode_Steering : public UAnimGraphNode_SkeletalControlBase`  
_L13-41_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_Steering Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L28 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L29 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L34 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L38 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L39 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_StrideWarping.h` (Public)


#### class `UAnimGraphNode_StrideWarping`  
`class UAnimGraphNode_StrideWarping : public UAnimGraphNode_SkeletalControlBase`  
_L15-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L20 _private member_ `FAnimNode_StrideWarping Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L29 _public prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L30 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L31 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L36 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L40 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L41 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimGraph/AnimGraphNode_WarpTest.h` (Public)


#### class `UAnimGraphNode_WarpTest`  
`class UAnimGraphNode_WarpTest : public UAnimGraphNode_Base`  
_L14-27_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_Base`
- L19 _private member_ `FAnimNode_WarpTest Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONWARPINGEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimationModifiers/OrientationWarpingModifier.h` (Public)


#### class `UOrientationWarpingModifier`  
`class UOrientationWarpingModifier : public UAnimationModifier`  
_L12-35_
- reflection: `UCLASS(Experimental)`
- inherits: `UAnimationModifier`
- desc: @TODO: Add comments/tooltips.
- L18 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L19 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`
- L22 _public member_ `FName EnableWarpingCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)`
- L25 _public member_ `FName EnableOffsetCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)`
- L28 _public member_ `float BlendInTime = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)`
- L31 _public member_ `float BlendOutTime = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)`
- L34 _public member_ `float StopSpeedThreshold = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)`

### `Plugins/Animation/AnimationWarping/Source/Editor/Public/AnimationWarpingEditorModule.h` (Public)


#### class `IAnimationWarpingEditorModule`  
`class IAnimationWarpingEditorModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
