# Plugins / IKRigDeveloper

- module root: `Plugins/Animation/IKRig/Source/IKRigDeveloper`
- headers: 3; symbols: 89
- symbol kinds: class=5, function=20, macro=3, member=9, prototype=52
- PrivateDependencyModuleNames: AnimGraph, BlueprintGraph, Core, CoreUObject, Engine, IKRig, Persona, Slate, SlateCore, StructUtilsEditor, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Animation/IKRig/Source/IKRigDeveloper/Public/AnimGraphNode_IKRig.h` (Public)


#### class `FIKRigGoalLayout`  
`class FIKRigGoalLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FIKRigGoalLayout>`  
_L20-58_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FIKRigGoalLayout>`
- L24 _public function_ `FIKRigGoalLayout(TSharedPtr<IPropertyHandle> InGoalPropHandle, const bool InExposePosition, const bool InExposeRotation) : GoalPropHandle(InGoalPropHandle) , bExposePosition(InExposePosition) , bExposeRotation(InExposeRotation)`
- L33 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InOutGoalRow) override;` — IDetailCustomNodeBuilder Interface
- L34 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InOutChildrenBuilder) override;`
- L35 _public function_ `virtual void Tick(float DeltaTime) override`
- L36 _public function_ `virtual bool RequiresTick() const override`
- L37 _public prototype_ `virtual FName GetName() const override;`
- L38 _public function_ `virtual bool InitiallyCollapsed() const override`
- L40 _public prototype_ `static FName GetGoalName(TSharedPtr<IPropertyHandle> InGoalHandle);`
- L44 _private prototype_ `EIKRigGoalTransformSource GetTransformSource() const;`
- L46 _private prototype_ `const struct FReferenceSkeleton& GetReferenceSkeleton() const;`
- L47 _private prototype_ `TSharedPtr<IPropertyHandle> GetBoneNameHandle() const;`
- L48 _private prototype_ `void OnBoneSelectionChanged(FName Name) const;`
- L49 _private prototype_ `FName GetSelectedBone(bool& bMultipleValues) const;`
- L51 _private prototype_ `TSharedRef<SWidget> CreatePropertyWidget() const;`
- L52 _private prototype_ `TSharedRef<SWidget> CreateBoneValueWidget() const;`
- L53 _private prototype_ `TSharedRef<SWidget> CreateValueWidget() const;`
- L55 _private member_ `TSharedPtr<IPropertyHandle> GoalPropHandle = nullptr;`
- L56 _private member_ `bool bExposePosition = false;`
- L57 _private member_ `bool bExposeRotation = false;`

#### class `FIKRigGoalArrayLayout`  
`class FIKRigGoalArrayLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FIKRigGoalArrayLayout>`  
_L63-85_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FIKRigGoalArrayLayout>`
- L67 _public function_ `FIKRigGoalArrayLayout(TSharedPtr<IPropertyHandle> InNodePropHandle) : NodePropHandle(InNodePropHandle)`
- L71 _public prototype_ `virtual ~FIKRigGoalArrayLayout() = default;`
- L74 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L75 _public function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override`
- L76 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L77 _public function_ `virtual void Tick(float DeltaTime) override`
- L78 _public function_ `virtual bool RequiresTick() const override`
- L79 _public function_ `virtual FName GetName() const override`
- L80 _public function_ `virtual bool InitiallyCollapsed() const override`
- L84 _private member_ `TSharedPtr<IPropertyHandle> NodePropHandle;`

#### class `UAnimGraphNode_IKRig`  
`class UAnimGraphNode_IKRig : public UAnimGraphNode_CustomProperty`  
_L89-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_CustomProperty`
- desc: Editor node for IKRig
- L94 _private member_ `FAnimNode_IKRig Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L98 _public prototype_ `UAnimGraphNode_IKRig() = default;`
- L99 _public prototype_ `virtual ~UAnimGraphNode_IKRig();`
- L102 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L106 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L107 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* InOldPins) override;`
- L109 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L110 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L114 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* AnimNode) override;` — UAnimGraphNode_Base interface
- L115 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const override;`
- L116 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L120 _public prototype_ `UObject* GetJumpTargetForDoubleClick() const;` — UK2Node interface
- L124 _public prototype_ `virtual void PostLoad() override;`
- L125 _public prototype_ `virtual void PostEditUndo() override;`
- L128 _public function_ `virtual bool NeedsToSpecifyValidTargetClass() const override`
- L132 _protected function_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override`
- L133 _protected function_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override`
- L138 _private prototype_ `static void SetPinDefaultValue(UEdGraphPin* InPin, const FName& InPropertyName);` — set pin's default value based on the FIKRigGoal default struct
- L141 _private prototype_ `void CreateCustomPinsFromValidAsset();` — create custom pins from exposed goals as defined in the rig definition asset
- L144 _private prototype_ `void CreateCustomPinsFromUnloadedAsset(TArray<UEdGraphPin*>* InOldPins);` — recreate custom pins from old pins if the rig definition asset is not completely loaded
- L147 _private member_ `FDelegateHandle OnAssetPropertyChangedHandle;` — Handle to the registered delegate
- L150 _private prototype_ `bool NeedsUpdate(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent) const;` — Global callback to anticipate on changes to the asset / goals
- L151 _private prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L152 _private prototype_ `void BindPropertyChanges();`
- L155 _private prototype_ `void UpdateGoalsFromAsset();` — update the goals' array within the anim node based on the asset
- L158 _private prototype_ `static void SetupGoal(const UIKRigEffectorGoal* InAssetGoal, FIKRigGoal& OutGoal);` — setup goal based on it's asset definition

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIGDEVELOPER_API`

### `Plugins/Animation/IKRig/Source/IKRigDeveloper/Public/AnimGraphNode_RetargetPoseFromMesh.h` (Public)


#### class `UAnimGraphNode_RetargetPoseFromMesh`  
`class UAnimGraphNode_RetargetPoseFromMesh : public UAnimGraphNode_CustomProperty`  
_L18-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_CustomProperty`
- L23 _private member_ `FAnimNode_RetargetPoseFromMesh Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L28 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L29 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L34 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L35 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* AnimNode) override;`
- L36 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L37 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const override;`
- L38 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L39 _public prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins) override;`
- L40 _public function_ `virtual bool UsingCopyPoseFromMesh() const override`
- L44 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;` — UK2Node interface
- L47 _public member_ `static const FName AnimModeName;`
- L51 _private function_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override` — UAnimGraphNode_CustomProperty interface
- L52 _private function_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override`
- L55 _private function_ `virtual UStruct* GetTargetStruct() const override` — return nullptr here to completely disable the base class's automatic pin manager we are manually handling the UI and Pin generation ourselves via CustomizeDetails
- L56 _private function_ `virtual UStruct* GetTargetSkeletonStruct() const override`
- L57 _private function_ `virtual bool NeedsToSpecifyValidTargetClass() const override`
- L60 _private prototype_ `void AddVariablesToDetailsPanel(IDetailLayoutBuilder& DetailBuilder);`
- L61 _private prototype_ `void CreateCustomPinsFromValidAsset();`
- L62 _private prototype_ `void CreateCustomPinsFromUnloadedAsset(TArray<UEdGraphPin*>* InOldPins);`
- L66 _private member_ `TSet<FName> ExposedVariableNames;` — `UPROPERTY()` — Set of variable names from the asset that should be exposed as input pins

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIGDEVELOPER_API`

### `Plugins/Animation/IKRig/Source/IKRigDeveloper/Public/IKRigDeveloper.h` (Public)


#### class `FIKRigDeveloperModule`  
`class FIKRigDeveloperModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `void StartupModule() override;`
- L14 _public prototype_ `void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIGDEVELOPER_API`
