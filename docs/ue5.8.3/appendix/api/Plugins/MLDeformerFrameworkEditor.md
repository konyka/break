# Plugins / MLDeformerFrameworkEditor

- module root: `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor`
- headers: 50; symbols: 1498
- symbol kinds: class=72, delegate=11, enum=4, enumerator=16, externvar=1, function=159, macro=43, member=344, namespace=107, prototype=732, struct=9
- PrivateDependencyModuleNames: AnimGraph, AnimationEditMode, ApplicationCore, AssetDefinition, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorWidgets, Engine, GeometryCache, InputCore, InteractiveToolsFramework, Json, MLDeformerFramework, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, ModelingToolsEditorMode, Persona, Projects, PropertyEditor, PythonScriptPlugin, RHI, RenderCore, SkeletalMeshDescription, SkeletalMeshEditor, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StatusBar, TimeManagement, ToolWidgets, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: Core, SequencerWidgets
- PublicIncludePathModuleNames: GeometryCache, Persona

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/MLDeformerAssetDefinitions.h` (Private)


#### class `UAssetDefinition_MLDeformer`  
`class UAssetDefinition_MLDeformer : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `FText GetAssetDisplayName() const override final;` — UAssetDefinition overrides
- L17 _public prototype_ `FLinearColor GetAssetColor() const override final;`
- L18 _public prototype_ `TSoftClassPtr<UObject> GetAssetClass() const override final;`
- L19 _public prototype_ `TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override final;`
- L20 _public prototype_ `EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override final;`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/MLDeformerOctree.h` (Private)


#### class `UE::MLDeformer::FMLDeformerOctree`  
`class FMLDeformerOctree`  
_L20-49_
- desc: An octree around a mesh consisting of FSoftSkinVertex vertices. This class is used to accelerate finding a close matching vertex in a lower LOD, inside another LOD. For example, for a given vertex position in LOD 1, we want to find the best matching vertex in LOD 0. We do that by finding a close match. But instead of always iterating over all vertices in LOD 0, we would first only check a small subset of nearby vertices.
- L25 _public prototype_ `void Build(const TArray<FSoftSkinVertex>& InVertices, int32 MaxNumVertsPerNode = 200, int32 MaxDepth = 5);`
- L26 _public prototype_ `void Render(FPrimitiveDrawInterface* PDI);`
- L27 _public prototype_ `int32 FindClosestMeshVertexIndex(FVector VertexPos, double FallBackDistanceThreshold = 0.1) const;`
- L30 _private prototype_ `void Split(FNode* Parent, int32 MaxNumVertsPerNode, int32 MaxDepth, int32 CurDepth);`
- L31 _private prototype_ `void RecursiveRender(FNode* Node, FPrimitiveDrawInterface* PDI);`
- L32 _private prototype_ `FNode* FindNodeForPosition(FNode* Node, const FVector Pos) const;`
- L45 _private member_ `TUniquePtr<FNode> RootNode;` — The root node of the octree.
- L48 _private member_ `TArray<FSoftSkinVertex> MeshVertices;` — The actual array of vertices.

#### struct `UE::MLDeformer::FMLDeformerOctree::FNode`  
`struct FNode`  
_L36-42_
- desc: The octree node.
- L38 _public member_ `TArray<int32> VertexIndices;` — Points inside the MeshVertices member array.
- L39 _public member_ `TArray<TUniquePtr<FNode>> ChildNodes;` — Doesn't need to be 8, can be less, or empty.
- L40 _public member_ `FNode* Parent = nullptr;` — Pointer to parent node, or nullptr in case of the root node.
- L41 _public member_ `FBox AABB;` — The bounding box of this node.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/MLDeformerTimelineTabSummoner.h` (Private)


#### struct `UE::MLDeformer::FMLDeformerTimelineTabSummoner`  
`struct FMLDeformerTimelineTabSummoner : public FWorkflowTabFactory`  
_L14-26_
- inherits: `FWorkflowTabFactory`
- L17 _public member_ `static const FName TabID;`
- L19 _public prototype_ `FMLDeformerTimelineTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& InEditor);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `FMLDeformerEditorToolkit* Editor = nullptr;`
- L25 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/MLDeformerVizSettingsTabSummoner.h` (Private)


#### struct `UE::MLDeformer::FMLDeformerVizSettingsTabSummoner`  
`struct FMLDeformerVizSettingsTabSummoner : public FWorkflowTabFactory`  
_L14-26_
- inherits: `FWorkflowTabFactory`
- L17 _public member_ `static const FName TabID;`
- L19 _public prototype_ `FMLDeformerVizSettingsTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& InEditor);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `TWeakPtr<FMLDeformerEditorToolkit> Editor = nullptr;`
- L25 _protected member_ `TSharedPtr<IDetailsView> DetailsView = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/SMLDeformerDebugSelectionWidget.h` (Private)


#### struct `UE::MLDeformer::FMLDeformerDebugActor`  
`struct FMLDeformerDebugActor`  
_L23-33_
- L26 _public member_ `TObjectPtr<AActor> Actor;` — The actor inside the PIE viewport, or nullptr when debugging is disabled.
- L32 _public member_ `bool bSelectedInEngine = false;` — Is this actor selected in the editor / engine? This is different from the Debug Actor we picked, we call that Active debug actor.

#### class `UE::MLDeformer::SMLDeformerDebugSelectionWidget`  
`class SMLDeformerDebugSelectionWidget : public SCompoundWidget`  
_L38-80_
- inherits: `SCompoundWidget`
- L42 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerDebugSelectionWidget)`
- L43 _public prototype_ `SLATE_ARGUMENT(FMLDeformerEditorToolkit*, MLDeformerEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L49 _public prototype_ `void Refresh();` — Refresh the list of debuggable actors in the combobox.
- L52 _public prototype_ `AActor* GetDebugActor() const;` — Get the current actor we're debugging, or a nullptr when debugging is disabled.
- L54 _public function_ `const TArray<TSharedPtr<FMLDeformerDebugActor>>& GetActors() const`
- L57 _private prototype_ `TSharedRef<SWidget> OnGenerateActorComboBoxItemWidget(TSharedPtr<FMLDeformerDebugActor> Item);`
- L58 _private prototype_ `TArray<TSharedPtr<FMLDeformerDebugActor>> GetDebugActorsForWorld(TObjectPtr<UWorld> World) const;`
- L59 _private prototype_ `FText GetComboBoxText() const;`
- L60 _private prototype_ `void OnActorSelectionChanged(TSharedPtr<FMLDeformerDebugActor> Item, ESelectInfo::Type SelectInfo);`
- L61 _private prototype_ `void RefreshActorList();`
- L62 _private prototype_ `void UpdateDebugActorSelectedFlags();`
- L63 _private prototype_ `bool IsDebuggingDisabled() const;`
- L67 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FMLDeformerDebugActor>>> ActorComboBox;` — The combobox that contains the actor names.
- L70 _private member_ `TArray<TSharedPtr<FMLDeformerDebugActor>> Actors;` — The actors we can debug.
- L73 _private member_ `TSharedPtr<FMLDeformerDebugActor> ActiveDebugActor;` — The selected actor.
- L76 _private member_ `FText DebugActorName;` — The name of the actor we are debugging.
- L79 _private member_ `FMLDeformerEditorToolkit* MLDeformerEditor = nullptr;` — A pointer to our asset editor.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Private/SMLDeformerTimeline.h` (Private)


#### class `UE::MLDeformer::SMLDeformerTimeline`  
`class SMLDeformerTimeline : public SCompoundWidget`  
_L35-138_
- inherits: `SCompoundWidget`
- desc: Implements a timeline widget for the ML Deformer editor.
- L38 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerTimeline)`
- L51 _public prototype_ `void Construct(const FArguments& InArgs, FMLDeformerEditorToolkit* InEditor);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The model for the anim timeline.
- L54 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface.
- L58 _public prototype_ `bool GetGridMetrics(float PhysicalWidth, double& OutMajorInterval, int32& OutMinorDivisions) const;` — Compute a major grid interval and number of minor divisions to display.
- L61 _public prototype_ `TSharedPtr<ITimeSliderController> GetTimeSliderController() const;` — Get the time slider controller.
- L63 _public prototype_ `void SetModel(TWeakPtr<FMLDeformerEditorModel> InModel);`
- L66 _public prototype_ `void SetTrainingAnimNames(const TArray<TSharedPtr<FMLDeformerTrainingInputAnimName>>& Names);` — Set the list of names to show in the timeline animation list combobox.
- L68 _public prototype_ `void OnDeletedTrainingInputAnim(int32 Index);`
- L70 _public prototype_ `void UpdateTimeSliderArgs(FTimeSliderArgs& TimeSliderArgs);`
- L76 _private function_ `float GetColumnFillCoefficient(int32 ColumnIndex) const` — @return The fill percentage of the animation outliner.
- L78 _private prototype_ `TSharedRef<SWidget> OnGenerateAnimListComboWidget(TSharedPtr<FMLDeformerTrainingInputAnimName> Item) const;`
- L79 _private prototype_ `void OnSelectTrainingAnim(TSharedPtr<FMLDeformerTrainingInputAnimName> Item, ESelectInfo::Type SelectInfo);`
- L82 _private prototype_ `TSharedRef<INumericTypeInterface<double>> GetNumericTypeInterface() const;` — Get numeric Type interface for converting between frame numbers and display formats.
- L85 _private prototype_ `void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);` — Called when a column fill percentage is changed by a splitter slot.
- L88 _private prototype_ `void HandleScrubPositionChanged(FFrameTime NewScrubPosition, bool bIsScrubbing, bool bEvaluate);` — Handles an additive layer key being set.
- L89 _private prototype_ `void HandleViewRangeChanged(TRange<double> InRange, EViewRangeInterpolation InInterpolation);`
- L91 _private prototype_ `double GetSpinboxDelta() const;`
- L92 _private prototype_ `void SetPlayTime(double InFrameTime);`
- L93 _private prototype_ `void SetDisplayFormat(EFrameNumberDisplayFormats InFormat);`
- L94 _private prototype_ `bool IsDisplayFormatChecked(EFrameNumberDisplayFormats InFormat) const;`
- L98 _private member_ `TWeakPtr<FMLDeformerEditorModel> Model;` — Anim timeline model.
- L101 _private member_ `UE::MLDeformer::FMLDeformerEditorToolkit* Editor = nullptr;` — The currently active editor model.
- L104 _private member_ `TSharedPtr<FMLTimeSliderController> TimeSliderController;` — The time slider controller.
- L107 _private member_ `TSharedPtr<SAnimTimelineTransportControls> TransportControls;` — The anim timeline transport controls, which contains the forward, backward and step actions.
- L110 _private member_ `TSharedPtr<ITimeSlider> TopTimeSlider;` — The top time slider widget.
- L113 _private member_ `float ColumnFillCoefficients[2] = { 0.2f, 0.8f };` — The fill coefficients of each column in the grid.
- L116 _private member_ `FSimpleDelegate OnSelectionRangeBeginDrag;` — Called when the user has begun dragging the selection selection range.
- L119 _private member_ `FSimpleDelegate OnSelectionRangeEndDrag;` — Called when the user has finished dragging the selection selection range.
- L122 _private member_ `FSimpleDelegate OnReceivedFocus;` — Called when any widget contained within the anim timeline has received focus.
- L125 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — Numeric Type interface for converting between frame numbers and display formats.
- L128 _private member_ `TAttribute<FAnimatedRange> ViewRange;` — The view range.
- L131 _private member_ `FText FilterText;` — Filter text used to search the tree.
- L134 _private member_ `TArray<TSharedPtr<FMLDeformerTrainingInputAnimName>> TrainingAnimNames;` — The training animation names as they will appear inside the timeline combobox on the left (in training mode only).
- L137 _private member_ `int32 SelectedTrainingAnimNameIndex = INDEX_NONE;` — The currently selected animation index. Index into the TrainingAnimNames array.

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerApplicationMode.h` (Public)


#### class `UE::MLDeformer::FMLDeformerApplicationMode`  
`class FMLDeformerApplicationMode : public FApplicationMode`  
_L21-40_
- inherits: `FApplicationMode`
- desc: The application mode for the ML Deformer editor. This defines the layout of the UI. It basically spawns all the tabs, such as the viewport, details panels, etc.
- L26 _public member_ `static FName ModeName;` — The name of this mode.
- L28 _public prototype_ `FMLDeformerApplicationMode(TSharedRef<FWorkflowCentricApplication> InHostingApp, TSharedRef<IPersonaPreviewScene> InPreviewScene);`
- L31 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode overrides.
- L36 _protected member_ `TWeakPtr<FMLDeformerEditorToolkit> EditorToolkit = nullptr;` — The hosting app.
- L39 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — The tab factories we support.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerAssetFactory.h` (Public)


#### class `UMLDeformerFactory`  
`class UMLDeformerFactory : public UFactory`  
_L16-34_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- desc: The factory for the ML Deformer asset type. This basically integrates the new asset type into the editor, so you can right click and create a new ML Deformer asset.
- L22 _public prototype_ `UMLDeformerFactory();`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;` — UFactory overrides.
- L26 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L27 _public prototype_ `virtual FText GetToolTip() const override;`
- L28 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L29 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L30 _public prototype_ `virtual bool ConfigureProperties() override;`
- L31 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L32 _public prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerCurveReferenceCustomization.h` (Public)


#### class `UE::MLDeformer::FMLDeformerCurveReferenceCustomization`  
`class FMLDeformerCurveReferenceCustomization : public IPropertyTypeCustomization`  
_L19-45_
- inherits: `IPropertyTypeCustomization`
- desc: The curve reference property detail customization.
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization overrides.
- L27 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L31 _protected prototype_ `void SetSkeleton(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L32 _protected prototype_ `virtual void SetPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L33 _protected prototype_ `TSharedPtr<IPropertyHandle> FindStructMemberProperty(TSharedRef<IPropertyHandle> PropertyHandle, const FName& PropertyName);`
- L36 _protected member_ `TSharedPtr<IPropertyHandle> CurveNameProperty = nullptr;` — Property to change after curve has been picked.
- L39 _protected member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — The skeletal mesh we get the curves from.
- L42 _private prototype_ `virtual void OnCurveSelectionChanged(const FString& Name);`
- L43 _private prototype_ `virtual FString OnGetSelectedCurve() const;`
- L44 _private prototype_ `virtual USkeletalMesh* OnGetSkeletalMesh() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorActor.h` (Public)


#### enum `UE::MLDeformer::(anonymous)`  
``  
_L23-41_

#### class `UE::MLDeformer::FMLDeformerEditorActor`  
`class FMLDeformerEditorActor`  
_L49-144_
- desc: An actor in the ML Deformer asset editor viewport. The UE Actor object itself is created by the FMLDeformerEditorModel class, after which this editor actor class can create components on it. It also contains some methods to control visibility and playback, among some other helper methods.
- L79 _public prototype_ `FMLDeformerEditorActor(const FConstructSettings& Settings);`
- L80 _public prototype_ `virtual ~FMLDeformerEditorActor();`
- L83 _public prototype_ `virtual void SetVisibility(bool bIsVisible);` — Main methods you can override.
- L84 _public prototype_ `virtual bool IsVisible() const;`
- L85 _public prototype_ `virtual void SetPlayPosition(float TimeInSeconds, bool bAutoPause = true);`
- L86 _public prototype_ `virtual float GetPlayPosition() const;`
- L87 _public prototype_ `virtual void SetPlaySpeed(float PlaySpeed);`
- L88 _public prototype_ `virtual float GetPlaySpeed();`
- L90 _public prototype_ `virtual FBox GetBoundingBox() const;`
- L91 _public prototype_ `virtual void Pause(bool bPaused);`
- L92 _public prototype_ `virtual bool IsPlaying() const;`
- L93 _public prototype_ `virtual bool IsGroundTruthActor() const;`
- L94 _public prototype_ `virtual bool HasVisualMesh() const;`
- L96 _public function_ `AActor* GetActor() const`
- L97 _public function_ `int32 GetTypeID() const`
- L98 _public function_ `int32 GetActorTypeInstanceIndex() const`
- L99 _public function_ `UDebugSkelMeshComponent* GetSkeletalMeshComponent() const`
- L100 _public function_ `UTextRenderComponent* GetLabelComponent() const`
- L101 _public function_ `UMLDeformerComponent* GetMLDeformerComponent() const`
- L102 _public function_ `bool IsTrainingActor() const`
- L103 _public function_ `bool IsTestActor() const`
- L104 _public function_ `float GetMeshOffsetFactor() const`
- L106 _public function_ `void SetSkeletalMeshComponent(UDebugSkelMeshComponent* SkelMeshComponent)`
- L107 _public function_ `void SetMLDeformerComponent(UMLDeformerComponent* Component)`
- L108 _public function_ `void SetMeshOffsetFactor(float OffsetFactor)`
- L109 _public function_ `void SetActorTypeInstanceIndex(int32 Index)`
- L112 _protected prototype_ `UTextRenderComponent* CreateLabelComponent(AActor* InActor, FLinearColor Color, const FText& Text) const;`
- L119 _protected member_ `int32 TypeID = -1;` — The ID of the editor actor type. This can be used to identify what actor we are dealing with, for example the base actor or ML Deformed one etc.
- L125 _protected member_ `int32 ActorTypeInstanceIndex = 0;` — The instance index. There can for example be multiple editor actors with a TypeID of ActorID_Test_Compare. This index separates those. If you have three test compare editor actors, on will have index 0, another 1, and the third one will have a value of 2 for this member.
- L128 _protected member_ `TObjectPtr<UTextRenderComponent> LabelComponent = nullptr;` — The label component, which shows above the actor.
- L131 _protected member_ `TObjectPtr<AActor> Actor = nullptr;` — The actual actor pointer.
- L134 _protected member_ `TObjectPtr<UDebugSkelMeshComponent> SkeletalMeshComponent = nullptr;` — The skeletal mesh component (can be nullptr).
- L137 _protected member_ `TObjectPtr<UMLDeformerComponent> MLDeformerComponent = nullptr;` — The ML Deformer component (can be nullptr).
- L140 _protected member_ `float MeshOffsetFactor = 0.0f;` — The position offset factor of the actor. A value of 1.0 would offset the actor with the Mesh Spacing amount, a value of 2.0 would be two times the mesh spacing offset, etc.
- L143 _protected member_ `bool bIsTrainingActor = true;` — Is this actor used for training?

#### struct `UE::MLDeformer::FMLDeformerEditorActor::FConstructSettings`  
`struct FConstructSettings`  
_L55-77_
- desc: The construction settings, which can be used as info when creating new components.
- L58 _public member_ `AActor* Actor = nullptr;` — The UE actor object that we should add components to.
- L61 _public member_ `int32 TypeID = -1;` — The ID of the actor. Look at the UE::MLDeformer::ActorID_Train_Base etc for example.
- L67 _public member_ `int32 ActorTypeInstanceIndex = 0;` — The instance index. There can for example be multiple editor actors with a TypeID of ActorID_Test_Compare. This index separates those. If you have three test compare editor actors, on will have index 0, another 1, and the third one will have a value of 2 for this member.
- L70 _public member_ `FLinearColor LabelColor = FLinearColor(1.0f, 0.0f, 0.0f);` — The color of the label text.
- L73 _public member_ `FText LabelText;` — The label text, which should be something like "Linear Skinned" or "Ground Truth", basically describing the actor. This will appear inside the render viewport.
- L76 _public member_ `bool bIsTrainingActor = false;` — Is this an actor used during training? Set to false if it is a testing mode actor.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)
- L25 _enumerator_ `ActorID_Train_Base` (scope `UE::MLDeformer::__anon7e11391e0103`) — The linear skinned (base) actor in training mode.
- L28 _enumerator_ `ActorID_Train_GroundTruth` (scope `UE::MLDeformer::__anon7e11391e0103`) — The ground truth (target) actor in training mode. This is our training target that we try to approximate.
- L31 _enumerator_ `ActorID_Test_Base` (scope `UE::MLDeformer::__anon7e11391e0103`) — The linear skinned (base) actor, in test mode.
- L34 _enumerator_ `ActorID_Test_MLDeformed` (scope `UE::MLDeformer::__anon7e11391e0103`) — The ML Deformed actor, in test mode. This one should have an UMLDeformerComponent on it.
- L37 _enumerator_ `ActorID_Test_GroundTruth` (scope `UE::MLDeformer::__anon7e11391e0103`) — The ground truth test actor, in test mode. This will represent your test anim sequence ground truth.
- L40 _enumerator_ `ActorID_Test_Compare` (scope `UE::MLDeformer::__anon7e11391e0103`) — The comparison actor, in test mode. This can be used to compare the results to another pretrained ML Deformer model.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorMode.h` (Public)


#### class `UE::MLDeformer::FMLDeformerEditorMode`  
`class FMLDeformerEditorMode : public IPersonaEditMode`  
_L21-50_
- inherits: `IPersonaEditMode`
- desc: The ML Deformer Persona editor mode. This handles ticking and rendering of the render viewport and camera focus.
- L26 _public member_ `static FName ModeName;` — The name of the mode.
- L28 _public function_ `void SetEditorToolkit(FMLDeformerEditorToolkit* InToolkit)`
- L31 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode overrides.
- L32 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L33 _public function_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override`
- L37 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — FEdMode overrides.
- L38 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L39 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L40 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L41 _public function_ `virtual bool AllowWidgetMove() override`
- L42 _public function_ `virtual bool ShouldDrawWidget() const override`
- L43 _public function_ `virtual bool UsesTransformWidget() const override`
- L44 _public function_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override`
- L45 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L49 _protected member_ `FMLDeformerEditorToolkit* DeformerEditorToolkit = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorModel.h` (Public)


#### enum `ETrainingResult`  
`enum class ETrainingResult : uint8`  
_L41-60_
- reflection: `UENUM()`
- desc: Training process return codes.
- L44 _public enumerator_ `Success = 0` — The training successfully finished.
- L47 _public enumerator_ `Aborted` — The user has aborted the training process.
- L50 _public enumerator_ `AbortedCantUse` — The user has aborted the training process, and we can't use the resulting network.
- L53 _public enumerator_ `FailOnData` — The input or output data to the network has issues, which means we cannot train.
- L56 _public enumerator_ `FailPythonError` — The python script has some error (see output log). Or it's missing some required model training class. Or an actual python code syntax error or failed imports.
- L59 _public enumerator_ `Other` — Any other error, for example when some exception got thrown during training.

#### class `UE::MLDeformer::FMLDeformerEditorModel`  
`class FMLDeformerEditorModel : public TSharedFromThis<FMLDeformerEditorModel> , public FGCObject`  
_L76-1241_
- inherits: `TSharedFromThis<FMLDeformerEditorModel>,FGCObject`
- desc: The base class for the editor side of an UMLDeformerModel. The editor model class handles most of the editor interactions, such as property changes, triggering the training process, creation of the viewport actors, and many more things. In most cases you will want to inherit your own editor model from either FMLDeformerGeomCacheEditorModel or FMLDeformerMorphModelEditorModel though. These classes will already implement a lot of base functionality in case you work with geometry caches as ground truth data etc.
- L98 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject overrides.
- L99 _public function_ `virtual FString GetReferencerName() const override`
- L107 _public prototype_ `virtual void CopyBaseSettingsFromModel(const FMLDeformerEditorModel* SourceEditorModel);` — Copy the common property values from a source model into this model. This includes the skeletal mesh, input animations, and shared visualization settings. @param SourceEditorModel The source model to copy the shared settings from.
- L120 _public prototype_ `static void ChangeSkeletalMeshOnComponent(USkeletalMeshComponent* SkelMeshComponent, USkeletalMesh* Mesh);` — Change the skeletal mesh on a specific skeletal mesh component. This internally will not only call SkelMeshComponent->SetSkeletalMesh(Mesh), but also will reassign the materials. The reason for this is that if there are material instances set already, the skeletal mesh component will not override them to preserve changes done by the user. This helper function will force these to be updated as well. This was needed in case of Metahumans. Metahumans use a PostProcessAnimBP with a ControlRig node in it, which drives material curves. In order to drive this, material instances are needed instead of regular materials. But as mentioned before, when switching the mesh the code internally will not override the material instances. So we simply have to force this manually, hence this function. @param SkelMeshComponent The skeletal mesh component to change the mesh for. @param Mesh The new mesh to use.
- L128 _public prototype_ `virtual int32 GetNumTrainingFrames() const;` — Get the number of training frames. This must not be clamped yet to the maximum training frame limit. It must return the full amount of frames available in your training data. For example this could return the number of frames inside your geometry cache. @return The number of frames in the training data.
- L136 _public prototype_ `virtual void UpdateNumTrainingFrames();` — Updates the number of available training frames as returned by GetNumTrainingFrames(). This should update the NumTrainingFrames class member with the total number of frames that can be included during training. So this must be the sum of all frames of all enabled training input animations. This should not take into account the maximum number of frames we want to train with.
- L169 _public prototype_ `virtual ETrainingResult Train();` — Launch the training. This gets executed when the Train button is pressed. Training can succeed, or be aborted, and there can be training errors. The result is returned by this method. You generally want to implement a class inherited from MLDeformerTrainingModel, and put a Train function inside of that, which you then execute through the TrainModel function. A code example: @code{.cpp} ETrainingResult FYourEditorModel::Train() { return TrainModel<UYourTrainingModel>(this); } @endcode That will internally call the Train function of your python class. Now inside your Python class you do something like: @code{.py} @unreal.uclass() class YourModelPythonTrainingModel(unreal.YourTrainingModel): @unreal.ufunction(override=True) def train(self): # ...do training here... return 0   # A value of 0 is success, 1 means aborted, see ETrainingResult. @endcode Calling the TrainModel function inside will then trigger the Python train method to be called. @return The training result.
- L177 _public prototype_ `virtual void Init(const InitSettings& Settings);` — Initialize the model. This will mainly create the delta sampler, editor input info and some other things. @param Settings The initialization settings.
- L187 _public prototype_ `virtual void CreateActors(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Create the editor actors. These are the actors that will appear in the viewport of the asset editor. Every actor has some specific ID. The base implementation of certain methods will assume there are specific actors, such as a linear skinned actor, ML Deformed actor, and a ground truth one. You can find the ID values of those inside the FMLDeformerEditorActor.h file. The ID values are things like: ActorID_Train_Base, ActorID_Train_GroundTruth, ActorID_Test_Base, ActorID_Test_MLDeformed and ActorID_Test_GroundTruth. Nothing prevents you from adding more or less actors though. @param InPersonaPreviewScene The persona scene.
- L192 _public prototype_ `virtual void ClearWorld();` — Clears the world, which basically means it removes all the editor actors and engine actors from the editor world.
- L197 _public prototype_ `virtual void ClearPersonaPreviewScene();` — Clears the Persona preview scene. Resetting the preview mesh, preview mesh component etc.
- L203 _public prototype_ `virtual void ClearWorldAndPersonaPreviewScene();` — Clear both the world and preview scene. This calls ClearWorld and ClearPersonaPreviewScene.
- L213 _public prototype_ `virtual FMLDeformerEditorActor* CreateEditorActor(const FMLDeformerEditorActor::FConstructSettings& Settings) const;` — Create an actor in the editor viewport. Each actor will have a specific ID and a label that is displayed above it, with a specific color. The ID values are things like: ActorID_Train_Base, ActorID_Train_GroundTruth, ActorID_Test_Base, ActorID_Test_MLDeformed and ActorID_Test_GroundTruth. You can find the ID values of those inside the FMLDeformerEditorActor.h file. @param Settings The creation settings for the editor actor you are creating. @return A pointer to the editor actor object that was created.
- L221 _public prototype_ `virtual TSharedPtr<FMLDeformerSampler> CreateSamplerObject() const;` — Create the vertex delta sampler object. You can create your own sampler in case you use anything else than say a Geometry Cache as ground truth target data. A geometry cache based editor model would create a new FMLDeformerGeomCacheSampler for example. @return A pointer to the newly created sampler.
- L229 _public prototype_ `virtual int32 GetNumTrainingInputAnims() const;` — Get the number of training input animations. Each training input anim is a pair of a source animation and a target mesh deformation with the same poses. This data is fed into the training process. @return The number of training input anims.
- L238 _public prototype_ `virtual FMLDeformerTrainingInputAnim* GetTrainingInputAnim(int32 Index) const;` — Get a given training input animation. Each training input anim is a pair of a source animation and a target mesh deformation with the same poses. This data is fed into the training process. @param Index The training input animation to get. @see GetNumTrainingInputAnims
- L245 _public prototype_ `virtual void UpdateTimelineTrainingAnimList();` — Update the timeline's training input animation list. This is the list of animations that show inside the timeline when in training mode. Each training input animation pair needs some name that is shown inside the timeline.
- L252 _public prototype_ `virtual double GetTrainingTimeAtFrame(int32 FrameNumber) const;` — Get the time in seconds, for a given frame in the training data. @param FrameNumber The frame number to get the time in seconds for. @return The time offset of this frame, in seconds.
- L259 _public prototype_ `virtual int32 GetTrainingFrameAtTime(double TimeInSeconds) const;` — Get the training data frame number for a specific time offset in seconds. @param TimeInSeconds The time offset, in seconds, to get the frame number for. @return The frame number for this time offset.
- L266 _public prototype_ `virtual double GetTestTimeAtFrame(int32 FrameNumber) const;` — Get the time in seconds, for a given frame in the test data. @param FrameNumber The frame number to get the time in seconds for. @return The time offset of this frame, in seconds.
- L273 _public prototype_ `virtual int32 GetTestFrameAtTime(double TimeInSeconds) const;` — Get the test data frame number for a specific time offset in seconds. @param TimeInSeconds The time offset, in seconds, to get the frame number for. @return The frame number for this time offset.
- L279 _public prototype_ `virtual int32 GetNumTestFrames() const;` — Get the total number of frames in the test anim sequence. @return The number of frames.
- L286 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime);` — Tick the editor viewport. @param ViewportClient The editor viewport client object. @param DeltaTime The delta time of this tick, in seconds.
- L295 _public prototype_ `virtual void CreateTrainingLinearSkinnedActor(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Create the linear skinned actor that is used as training base. This is the actor you see marked as "Training Base" in the training mode. An editor actor needs to be created by this method. The default implementation will directly set the persona actor and preview mesh and component to this actor. @param InPersonaPreviewScene The personal preview scene.
- L303 _public prototype_ `virtual void CreateTestLinearSkinnedActor(UWorld* World);` — Create the linear skinned test actor. This is the "Linear Skinned" actor you see in testing mode. An editor actor needs to be created by this method. @param World The world to create the actor in.
- L312 _public prototype_ `virtual void CreateTestMLDeformedActor(UWorld* World);` — Create the test ML Deformed actor. This is the actor you see in test mode marked as "ML Deformed". So this actor will have the ML Deformer component added to it as well. An editor actor needs to be created by this method. @param World The world to create the actor in.
- L318 _public prototype_ `virtual void CreateTestCompareActors(UWorld* World);` — Create the compare actors for the testing mode. @param World The world to create the actors in.
- L327 _public prototype_ `virtual bool IsCompatibleDeformer(UMLDeformerAsset* Deformer) const;` — Check if this model is compatible with a specific deformer asset. For example, it will check whether the other deformer asset's skeletal mesh is the same as the one used by this model. @param Deformer The deformer asset to check against. @return Returns true if the specified asset is compatible with this one, otherwise false is returned.
- L333 _public prototype_ `virtual void UpdateMeshOffsetFactors();` — Update the mesh offset factors, which is basically controlling where to place the actors in the scene. The spacing between the characters is the mesh offset factor multiplied by the mesh spacing.
- L341 _public function_ `virtual void CreateTrainingGroundTruthActor(UWorld* World)` — Create the training ground truth actor. This is the training target, so the actor that has the complex deformations, for example using a geometry cache. An editor actor needs to be created by this method. @param World The world to create the actor in.
- L351 _public function_ `virtual void CreateTestGroundTruthActor(UWorld* World)` — Create the test ground truth actor. This is the actor typically marked as "Ground Truth" in the editor. It represents the test animation sequence ground truth deformation. So this could contain a geometry cache equivalent to the animation sequence. An editor actor needs to be created by this method. @param World The world to create the actor in.
- L358 _public prototype_ `virtual void OnTrainingDataFrameChanged();` — This is triggered when the training frame is changed by the user. For example when they click the timeline in the editor, or enter a specific frame number. This happens only in training mode.
- L364 _public prototype_ `virtual void UpdateActorTransforms();` — Update the transforms of all the editor actors. This should apply the mesh offsets to space the actors in the world/viewport.
- L370 _public prototype_ `virtual void UpdateActorVisibility();` — Update the visibility status of the editor actors. This should hide test actors when the editor is in training mode for example, and the other way around.
- L376 _public prototype_ `virtual void UpdateLabels();` — Update the visibility of the labels, as well as their positions. For example labels of invisible actors should be made invisible as well.
- L383 _public prototype_ `virtual void OnInputAssetsChanged();` — This is called when training data inputs change. This includes changing things such as the Skeletal Mesh, training anim sequence and target mesh. It will re-initialize the components. For example a skeletal mesh change will update the skeletal mesh component to the new mesh.
- L389 _public prototype_ `virtual void OnPostInputAssetChanged();` — This is executed after the input assets have changed. On default this will refresh the deformer graphs, update the timeline ranges, select the right frames, modify the training button ready state, etc.
- L397 _public prototype_ `virtual void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent);` — This is called whenever a property value changes in the UI. The default implementation handles all the shared property changes already. You can overload this and call the base class method inside it, and then handle your own model specific property changes. @param PropertyChangedEvent The event information object that contains info about the property change.
- L402 _public function_ `virtual void OnPreEditUndo()` — This is called before undo is called on the model.
- L407 _public function_ `virtual void OnPostEditUndo()` — This is called after undo is performed on the model.
- L413 _public prototype_ `virtual void OnPostTransacted(const FTransactionObjectEvent& Event);` — This is called whenever a transaction happened on the model. @param Event Information about the event.
- L419 _public prototype_ `virtual void OnPlayPressed();` — Executed when the user presses the play button in the timeline. On default this will start playing the anim sequence related to whether we are in training or testing mode.
- L426 _public function_ `virtual void OnPreTraining()` — This is called just before we start the training process. You can use it to back up any specific values that might be modified by the training process. Sometimes you want to restore specific values when the user aborts the training, while the training already modified those values.
- L434 _public prototype_ `virtual void OnPostTraining(ETrainingResult TrainingResult, bool bUsePartiallyTrainedWhenAborted);` — This method is executed after training. @param TrainingResult The result of the training process, such as whether it was a success or the user aborted, etc. @param bUsePartiallyTrainedWhenAborted When the user aborts training, they can get offered to use the partially trained neural network. This boolean specifies whether they picked "Yes" (true) or "No" (false) to that question.
- L442 _public function_ `virtual void OnTrainingAborted(bool bUsePartiallyTrainedData)` — This is executed when the training process got aborted by the user. You can use this method to restore any values you had to back up during OnPreTraining for example. @param bUsePartiallyTrainedData When the user aborts training, they can get offered to use the partially trained neural network. This boolean specifies whether they picked "Yes" (true) or "No" (false) to that question.
- L452 _public prototype_ `virtual bool IsPlayingAnim() const;` — Check whether we are playing an animation or not. This looks at whether we are in training or testing mode. It will look at the correct anim sequence based on this mode. So if you are in training mode and the testing animation is playing, while the training sequence isn't playing, then it returns false. It would in that case only return true when the training anim sequence is playing. The same goes in testing mode, if we are in testing mode it will only return true when the test anim sequence is playing. @return Returns true whether the mode specific animation sequence is playing.
- L459 _public prototype_ `virtual bool IsPlayingForward() const;` — Check whether our anim sequence is playing forward or backward. Just like the IsPlayingAnim method, it is specific to the mode we are in. @return Returns true when we are playing the animation forwards, and not backward.
- L467 _public prototype_ `virtual double CalcTrainingTimelinePosition() const;` — Get the current playback position of our training mode. This will use the target mesh if there is any, and uses the anim sequence play offset in case no target mesh has been set yet. So if you have a geometry cache or so specified as target mesh, it would extract the current time value from that. @return The time offset, in seconds, of our training data.
- L475 _public prototype_ `virtual double CalcTestTimelinePosition() const;` — Calculate the test mode timeline position. This will use the ground truth test data if there is any, and uses the test anim sequence play offset in case no test ground truth has been set yet. So if you have a geometry cache or so specified as test ground truth, it would extract the current time value from that. @return The time offset, in seconds, of our test data.
- L483 _public prototype_ `virtual void OnTimeSliderScrubPositionChanged(double NewScrubTime, bool bIsScrubbing);` — This is executed when the timeline has been scrubbed. Sometimes this is also executed without user interaction, but to update the same data when there was scrubbed. @param NewScrubTime This is the new time value, in seconds. @param bIsScrubbing Specifies whether the user is scrubbing or just clicked.
- L491 _public prototype_ `virtual void UpdateTestAnimPlaySpeed();` — Update the playback speed of the test data. This will iterate over all the editor actors, check whether they are test mode actors, and if so it will update the play speed. For example a linear skinned mesh will update its skeletal mesh component's play speed, while a geometry cache ground truth actor would update the play speed set on the geometry cache component.
- L499 _public prototype_ `virtual void ClampCurrentTrainingFrameIndex();` — Clamp the current training frame index to be in a valid range. A valid range would be between 0 and the number of frames in the training data. So if the training data contains 100 frames, so index 0..99, and we set the TrainingFrameNumber member to 500, this method will turn that into 99.
- L507 _public prototype_ `virtual void ClampCurrentTestFrameIndex();` — Clamp the current test frame index to be in a valid range. A valid range would be between 0 and the number of frames in the test data (anim sequence / ground truth). So if the test data contains 100 frames, so index 0..99, and we set the TestingFrameNumber member to 500, this method will turn that into 99.
- L515 _public prototype_ `virtual int32 GetNumFramesForTraining() const;` — Get the total number of frames used for training, but limited by the maximum number of training frames we have setup. So if the training data contains 10000 frames, but we set to train on a maximum of 2000 frames, then this will return 2000. If the number of training frames is 10000 but we set the max number of training frames to 1 million, then it will still return only 10000. @return The number of frames we should be training on.
- L523 _public prototype_ `virtual void SetTrainingFrame(int32 FrameNumber, bool bIsScrubbing);` — Go to a given frame in the training data. Internally this will also call OnTimeSliderScrubPositionChanged, to go to the specific frame. @param FrameNumber The training frame to go to. This will automatically be clamped to a valid range in case it goes out of bounds. @param bIsScrubbing This is set to true when we are scrubbing the timeline. It is set to false when the mouse button is released.
- L531 _public prototype_ `virtual void SetTestFrame(int32 FrameNumber, bool bIsScrubbing);` — Go to a given frame in the test data. Internally this will also call OnTimeSliderScrubPositionChanged, to go to the specific frame. @param FrameNumber The test frame to go to. This will automatically be clamped to a valid range in case it goes out of bounds. @param bIsScrubbing This is set to true when we are scrubbing the timeline. It is set to false when the mouse button is released.
- L540 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);` — Render additional (debug) things in the viewport. This will draw the vertex deltas when we are in training mode and aren't playing the training data. @param View The scene view object. @param Viewport The viewport object. @param PDI The draw primitive interface used for drawing things.
- L547 _public function_ `virtual void UpdateIsReadyForTrainingState()` — Update the state that is used to decide whether the Train button in the UI is enabled or not. A criteria could be to check whether we have all required inputs, such as a skeletal mesh, target mesh and anim sequence. This should set the bIsReadyForTraining bool to true when it is ready, or false if not.
- L553 _public prototype_ `virtual FText GetOverlayText() const;` — Get the text that we should display as overlay on top of the asset editor viewport. @return The text, or an empty text object if there is nothing to show.
- L563 _public prototype_ `virtual void InitInputInfo(UMLDeformerInputInfo* InputInfo);` — Initialize the input information, which basically describes what the inputs to the neural network are going to be. This contains things such as bone and curve names. The input info is used during both training and inference time. It is used to see what bone transforms and curve values to feed into the network inputs. Next to bones and curve reference it also stores the vertex counts of the base and target meshes, so we can later do some compatibility checks when applying this ML Deformer onto some character. @param InputInfo The input info object to initialize.
- L569 _public prototype_ `virtual void RefreshMLDeformerComponents();` — Call the SetupComponent on every ML Deformer component on our editor actors and update the compatibility status of the deformer components. This gets triggered when some input assets change.
- L575 _public prototype_ `virtual void CreateHeatMapMaterial();` — Create the heat map material for this model. This updates the HeatMapMaterial member.
- L581 _public prototype_ `virtual void CreateHeatMapDeformerGraph();` — Create the heat map deformer graph for this model. This updates the HeatMapDeformerGraph member.
- L587 _public prototype_ `virtual void CreateHeatMapAssets();` — Create the heat map assets for this model. This calls CreateHeatMapMaterial and CreateHeatMapDeformerGraph on default.
- L596 _public prototype_ `virtual UMeshDeformer* GetActiveHeatMapDeformer() const;` — Get the heat map deformer that should currently be used (when heatmaps are enabled). On default this will return the HeatMapDeformerGraph. However, if your deformer supports let's say linear blend skinning and dual quaternion skinning, you could make it return the appropriate deformer graph for skinning method that is currently used. @return Returns a pointer to the mesh deformer to use when heatmaps are enabled.
- L603 _public prototype_ `virtual void SetHeatMapMaterialEnabled(bool bEnabled);` — Specify whether the heat map material should be enabled or not. This will activate the heat map visualization, or deactivate it. @param bEnabled Set to true to enable heat map mode.
- L609 _public prototype_ `virtual UMeshDeformer* LoadDefaultDeformerGraph() const;` — Load the default Optimus deformer graph to use on the skeletal mesh when using this model. @return The mesh deformer graph.
- L615 _public prototype_ `virtual void SetDefaultDeformerGraphIfNeeded();` — This makes sure that the deformer graph selected in the visualization settings is not a nullptr. If the current graph hasn't been set, it will assign the default deformer graph to it.
- L622 _public prototype_ `virtual void UpdateDeformerGraph();` — This applies the right mesh deformer to the editor actors that have an ML Deformer component on them. Basically this just ensures that the heat map deformer graph is active when this is enabled. Otherwise the default mesh deformer is used.
- L628 _public function_ `virtual void OnMaxNumLODsChanged()` — Executed when the maximum number of LOD levels changed. Other models could use this to reinitialize the morph targets for all LOD levels for example.
- L636 _public prototype_ `virtual void SampleDeltas();` — Sample the vertex deltas between the training base model and target model. This will initialize the sampler if needed and set the sampler space to post-skinning deltas, and then samples them using the sampler. So this will update the internal state of the Sampler member. It will use the current training frame number to sample from. If this number is somehow out of range it will automatically clamp it to be inside a valid range.
- L642 _public function_ `virtual bool LoadTrainedNetwork() const` — Load the trained network from an onnx file. The filename of the onnx file is determined by the GetTrainedNetworkOnnxFile method.
- L651 _public prototype_ `virtual FString GetTrainedNetworkOnnxFile() const;` — Get the onnx file name of the trained network. This is the filename that your python script will save the onnx file to. On default this will return the following filename: "<intermediatedir>/YourModel/YourModel.onnx". Where "intermediatedir" is your project's Intermediate folder. And "YourModel" is the name of your runtime model class. So if you have a model class named UFancyModel, on default this method will return "<intermediatedir>/FancyModel/FancyModel.onnx"
- L658 _public function_ `virtual bool IsTrained() const` — Check whether our model is trained or not. This is determined by looking whether the neural network pointer is nullptr or not. @return Returns true when the model is trained already, or false if it hasn't been trained yet.
- L665 _public prototype_ `virtual FMLDeformerEditorActor* GetTimelineEditorActor() const;` — Get the editor actor that defines the timeline play position. In training mode this is the training target actor, while in test mode it is the test ground truth actor. @return A pointer to the ground truth actor depending on whether we're in test or training mode.
- L671 _public prototype_ `virtual FString GetHeatMapMaterialPath() const;` — Get the path to the heat map material asset. @return The path to the heat map asset.
- L677 _public prototype_ `virtual FString GetHeatMapDeformerGraphPath() const;` — Get the path to the heat map deformer graph asset, when using linear skinning. @return The path to the heat map deformer graph asset.
- L683 _public prototype_ `virtual FString GetHeatMapDeformerGraphDualQuatPath() const;` — Get the path to the heat map deformer graph asset, when using dual quaternion skinning. @return The path to the heat map deformer graph asset.
- L689 _public prototype_ `virtual void RefreshInputWidget();` — Refresh the contents of the input widget. This includes the bone and curve list contents.
- L698 _public prototype_ `virtual TSharedPtr<SMLDeformerInputWidget> CreateInputWidget();` — Create the input widget. The default widget that is created contains the bone and curve list. You can inherit from the SMLDeformerInputWidget base class and override this method to return your custom widget. This can be useful when you want to add new types of inputs to your model. @return A shared pointer to the input widget that will appear in the UI.
- L701 _public prototype_ `virtual void UpdatePreviewScene();` — Update the persona preview scene's actor, skeletal mesh component, mesh and anim asset. These are based on the current visualization mode.
- L709 _public prototype_ `virtual void OnDebugActorChanged(TObjectPtr<AActor> DebugActor);` — Called whenever the actor to debug has been changed. This can be changed throughout the UI, in testing mode. When debugging gets disabled, this will contain a nullptr. @param DebugActor The new actor we want to debug.
- L715 _public prototype_ `virtual void ApplyDebugActorTransforms(const TArray<FTransform>& DebugActorComponentSpaceTransforms);` — Apply the transforms of the actor we debug to the editor actors in our world. @param DebugActorComponentSpaceTransforms The component space transforms from the actor we are debugging.
- L726 _public prototype_ `virtual void UpdatePaintModePose(bool bFullUpdate=true);` — Update the character's pose in paint mode. This will check whether we are in training or testing mode and choose the editor actor based on that. The paint mode will then use this specific editor actor's skeletal mesh component to calculate skinned vertex positions at its current pose. After that it will update the dynamic mesh in the paint mode in order to paint in this same pose. This method is called when you start painting, or scrub the timeline. @param bFullUpdate When set to true, this can internally update the acceleration structures, which is slow. When set to false it can quickly update the visual mesh It is still important to once call it with bFullUpdate set to true though, before you start painting.
- L734 _public prototype_ `virtual void DrawPIEDebugActors();` — Debug draw helpers inside the PIE viewport that highlight debuggable actors. On default this will draw a bounding box around the actors that can be debugged by this model. Also it will render the actor names. NOTE: This renders inside the PIE viewport, not our own MLD asset editor viewport.
- L741 _public function_ `virtual bool GetSupportsPerTrainingInputAnimVertexMask() const` — Check whether this model supports a per training input animation vertex mask. If this is enabled, each training intput animation should show something where the user can select an optional mask. @return Returns true when vertex masking per training input is supported, false otherwise.
- L747 _public prototype_ `virtual void UpdateActorLODs();` — Update LOD levels of the actors in editor world. This can be used to for example sync the LOD levels of the compare actors with the main actor.
- L781 _public function_ `virtual void UpdateTrainingDeviceList()` — This should update the list of available training devices. If not implemented, the user won't be able to pick a training device. With training device we mean the device used to store the tensors at. Typically you want to make it build a list of GPU's and have the CPU in there as well. <code> UYourTrainingModel* TrainingModel = NewDerivedObject<UYourTrainingModel>(); if (TrainingModel) { TrainingModel->Init(this); TrainingModel->UpdateAvailableDevices(); TrainingModel->ConditionalBeginDestroy(); } </code> You can implement the following in Python as an example: <code> @unreal.ufunction(override=True) def update_available_devices(self): reload(mldeformer.training_helpers) mldeformer.training_helpers.update_training_device_list(self) </code> Then inside the python code you can do something like: <code> training_device = model.get_training_device() device_index = mldeformer.training_helpers.find_cuda_device_index(device_name=training_device) if torch.cuda.is_available() and device_index != -1: torch.cuda.set_device(device_index) </code>
- L784 _public prototype_ `void ApplyDebugActorTransforms();` — Apply the transforms of the debug actor to the actors in the asset editor world. This will internally call ApplyDebugActorTransforms(DebugActorComponentSpaceTransforms).
- L787 _public prototype_ `void UpdateMemoryUsage();` — Invalidate the memory usage, so it gets updated in the UI again.
- L790 _public prototype_ `UAnimSequence* GetActiveTrainingInputAnimSequence() const;` — Get the currently active training input animation sequence, which is the one that the viewport is showing the timeline for in training mode.
- L793 _public prototype_ `TRange<double> GetViewRange() const;` — Get the current view range.
- L796 _public prototype_ `void SetViewRange(TRange<double> InRange);` — Set the current view range.
- L799 _public prototype_ `TRange<double> GetWorkingRange() const;` — Get the working range of the model's data.
- L802 _public prototype_ `TRange<FFrameNumber> GetPlaybackRange() const;` — Get the playback range of the model's data.
- L805 _public prototype_ `FFrameNumber GetTickResScrubPosition() const;` — Get the current scrub position.
- L808 _public prototype_ `int32 GetTicksPerFrame() const;` — Get how many ticks there are per frame.
- L811 _public prototype_ `float GetScrubTime() const;` — Get the current scrub time.
- L814 _public prototype_ `void SetScrubPosition(FFrameTime NewScrubPosition, bool bIsScrubbing);` — Set the current scrub position.
- L817 _public prototype_ `void SetScrubPosition(FFrameNumber NewScrubPosition, bool bIsScrubbing);` — Set the current scrub position.
- L820 _public prototype_ `void SetDisplayFrames(bool bDisplayFrames);` — Set if frames are displayed.
- L823 _public prototype_ `bool IsDisplayingFrames() const;` — Is the timeline displaying frames rather than seconds?
- L826 _public prototype_ `void HandleModelChanged();` — Handle the timeline changes when our model changes.
- L829 _public prototype_ `void HandleVizModeChanged(EMLDeformerVizMode Mode);` — Handle the timeline changes required when changing the visualization mode, so when we switch between training and testing mode.
- L832 _public prototype_ `void HandleViewRangeChanged(TRange<double> InRange);` — Handle the view range being changed.
- L835 _public prototype_ `void HandleWorkingRangeChanged(TRange<double> InRange);` — Handle the working range being changed.
- L838 _public prototype_ `double GetFrameRate() const;` — Get the framerate specified by the anim sequence.
- L841 _public prototype_ `int32 GetTickResolution() const;` — Get the tick resolution we are displaying at.
- L844 _public function_ `FMLDeformerEditorToolkit* GetEditor() const` — Get a pointer to the ML Deformer editor tookit. Cannot be a nullptr.
- L847 _public function_ `UMLDeformerModel* GetModel() const` — Get a pointer to the runtime ML Deformer model. Cannot really be a nullptr.
- L850 _public prototype_ `UWorld* GetWorld() const;` — Get a pointer to the world that our editor is displaying. Cannot be nullptr.
- L853 _public function_ `const TArray<FMLDeformerEditorActor*>& GetEditorActors() const` — Get all the created editor actors.
- L856 _public prototype_ `FMLDeformerEditorActor* FindEditorActor(int32 ActorTypeID) const;` — Find an editor actor with a specific ID, or return nullptr when not found.
- L859 _public function_ `bool IsReadyForTraining() const` — Check whether we are ready to train. The Train button in the UI will be enabled or disabled based on this return value.
- L866 _public function_ `FMLDeformerSampler* GetSamplerForTrainingAnim(int32 AnimIndex) const` — Get the vertex delta sampler for a given training input animation. @param AnimIndex The training input animation index. @return A pointer to the sampler for this specific input anim, or nullptr in case the index is out of range.
- L873 _public function_ `void SetResamplingInputOutputsNeeded(bool bNeeded)` — Set whether we need to resample inputs or not. This can be used by the training code to determine if we need to resample inputs and outputs, or if some cache can be used. Resampling is generally needed when input assets change, or other specific settings. @param bNeeded Set to true to mark that inputs or other cached data need resampling.
- L880 _public function_ `bool GetResamplingInputOutputsNeeded() const` — Check whether we need to resample inputs and outputs. @return Returns true if resampling of the inputs and outputs is needed, for example because input assets have changed. @see SetResamplingInputOutputsNeeded
- L886 _public prototype_ `FText GetBaseAssetChangedErrorText() const;` — Check whether the vertex counts of the skeletal mesh have changed compared to the one we have trained on. @return An error string if there is an error, otherwise an empty text object is returned.
- L893 _public prototype_ `FText GetVertexMapChangedErrorText() const;` — Check whether the vertex map has changed or not. This basically checks whether the vertex order has changed. @return An error string if there is an error, otherwise an empty text object is returned.
- L900 _public prototype_ `FText GetInputsErrorText() const;` — Check for errors in the inputs. This basically checks if there are bones or curves to train on. If there aren't any it will give some error. @return An error string if there is an error, otherwise an empty text object is returned.
- L906 _public prototype_ `FText GetIncompatibleSkeletonErrorText(const USkeletalMesh* InSkelMesh, const UAnimSequence* InAnimSeq) const;` — Check for incompatible skeletons between the skeletal mesh and anim sequence skeleton. @return An error string if there is an error, otherwise an empty text object is returned.
- L914 _public prototype_ `FText GetSkeletalMeshNeedsReimportErrorText() const;` — Check to see if the skeletal mesh has to be reimported because it misses some newly added data. We have added imported mesh information to the Fbx importer. Older assets won't have this info, while this is required to make the ML Deformer work properly. @return An error string if there is an error, otherwise an empty text object is returned.
- L921 _public prototype_ `FText GetTargetAssetChangedErrorText() const;` — Check whether the vertex count in the target mesh has changed or not. If this is the case you would need to re-train the model. @return An error string if there is an error, otherwise an empty text object is returned.
- L929 _public function_ `UMLDeformerInputInfo* GetEditorInputInfo() const` — Get the editor's input info object. This is the information the user currently has setup in the UI, so not the input info of the runtime model. The runtime model's input info contains the data inputs the model has been trained on, which can be different from what the user currently has set up in the UI. @return A pointer to the editor's input info object.
- L934 _public prototype_ `void UpdateEditorInputInfo();` — Update the editor's input info based on the current UI settings.
- L941 _public prototype_ `void TriggerInputAssetChanged(bool bRefreshVizSettings=false);` — This will call OnInputAssetsChanged first, followed by OnPostInputAssetChanged. It then will update the editor only flags for the assets, and then forces a refresh of the model details panel and optionally also the visualization settings panel. @param bRefreshVizSettings Set to true if you want the visualization settings details panel to also refresh.
- L948 _public prototype_ `void InitBoneIncludeListToAnimatedBonesOnly();` — Initialize the bone include list of the runtime model to the set of bones that are animated. A bone is seen as animated if its animation data has keyframes that have a different value than the first keyframe. So if the bone's animation data has 1000 keyframes, and they are all the same value, it won't see it as animated.
- L955 _public prototype_ `void InitCurveIncludeListToAnimatedCurvesOnly();` — Initialize the curve include list of the runtime model to the set of curves that are animated. A curve is seen as animated if its animation data has keyframes that have a different value than the first keyframe. So if the curve's animation data has 1000 keyframes, and they are all the same value, it won't see it as animated.
- L960 _public prototype_ `void AddAnimatedBonesToBonesIncludeList();` — Add all animated bones to the bone include list.
- L965 _public prototype_ `void AddAnimatedCurvesToCurvesIncludeList();` — Add all animated curves to the curve include list.
- L972 _public prototype_ `int32 GetNumCurvesOnSkeletalMesh(USkeletalMesh* SkelMesh) const;` — Get the number of curves on a specific skeletal mesh. @param SkelMesh The skeletal mesh to get the curves count from. @return The number of curves found on the skeletal mesh.
- L979 _public function_ `int32 GetCurrentTrainingFrame() const` — Get the currently desired training frame number. You can call CheckTrainingFrameChanged in order to make the desired frame the actual frame. @return The currently desired training frame number, which might not be the same as the real training frame number.
- L985 _public prototype_ `void CheckTrainingDataFrameChanged();` — Check whether our training data frame number changed. We have a TrainingFrameNumber and a CurrentTrainingFrame. If they don't match it will call OnTrainingDataFrameChanged.
- L992 _public prototype_ `UMLDeformerComponent* FindMLDeformerComponent(int32 ActorID = ActorID_Test_MLDeformed) const;` — Find the ML Deformer component of a given editor actor. @param ActorID The actor ID to get the component for. @return A pointer to the ML Deformer component, if it exists on the actor, otherwise nullptr is returned.
- L1001 _public prototype_ `static float CorrectedFrameTime(int32 FrameNumber, float FrameTimeForFrameNumber, FFrameRate FrameRate);` — Correct floating point errors that can cause issues when sampling animation using step timing. @param FrameNumber The desired frame number. @param FrameTimeForFrameNumber The frame time computed for the frame number, which may have conversion errors. @param FrameRate The frame rate for conversion. @return A corrected frame time, which is equal to FrameTimeForFrameNumber unless a floating point error means the floor is not equal to the FrameNumber.
- L1003 _public function_ `TSharedPtr<SMLDeformerInputWidget> GetInputWidget() const`
- L1004 _public function_ `void SetInputWidget(const TSharedPtr<SMLDeformerInputWidget>& Widget)`
- L1006 _public prototype_ `FMLDeformerSampler* GetSamplerForActiveAnim() const;`
- L1008 _public prototype_ `void SetActiveTrainingInputAnimIndex(int32 Index);`
- L1009 _public prototype_ `int32 GetActiveTrainingInputAnimIndex() const;`
- L1012 _public prototype_ `void InvalidateDeltas();` — Mark the deltas to be updated on next Tick.
- L1018 _public prototype_ `TVertexAttributesConstRef<float> FindVertexAttributes(FName AttributeName) const;` — Find the float based vertex attributes on the skeletal map that have a given name. You can check whether the attribute data has been found using ReturnedValue.IsValid().
- L1021 _public function_ `bool IsScrubbingTimeline() const` — Are we scrubbing on the timeline?
- L1024 _public function_ `const TArray<TSharedPtr<FName>>& GetVertexAttributeNames() const` — Get the array of vertex attribute names that can be used for UI widget elements. Refresh this list with UpdateVertexAttributeNames().
- L1027 _public prototype_ `void UpdateVertexAttributeNames();` — Update the vertex attribute names array as returned by GetVertexAttributeNames(). This is some array that can be used for UI elements like combo boxes.
- L1033 _public function_ `void RequestTriggerInputAssetsChangedNextTick()` — Request a call to TriggerInputAssetsChanged on the next tick, so not directly. This can be useful to prevent multiple nested calls to TriggerInputAssetsChanged.
- L1036 _protected prototype_ `virtual void CreateSamplers();`
- L1038 _protected prototype_ `void AddAnimatedBonesToBonesIncludeList(const UAnimSequence* AnimSequence);`
- L1039 _protected prototype_ `void AddAnimatedCurvesToCurvesIncludeList(const UAnimSequence* AnimSequence);`
- L1045 _protected prototype_ `void OnPostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);` — Executed when a property changes by a change in the UI. This internally calls OnPropertyChanged.
- L1051 _protected prototype_ `void BroadcastPropertyChanged(const FName PropertyName);` — Trigger a PostEditChangeProperty using a ValueSet event type, on the model, which will also trigger the OnPostEditChangeProperty. @param PropertyName The name of the property to trigger it for.
- L1060 _protected prototype_ `virtual void OnObjectModified(UObject* Object);` — Called whenever an engine object is being modified. Use this to set the reinitialize assets flag. For example when a skeletal mesh or anim sequence change (being modified or reimported), we should set the bNeedsAssetReinit member to true, to trigger the actor components and UI etc to be reinitialized. The default implementation of this method will check for changes in the skeletal mesh and training and test anim sequence. If you want to check more things (your target mesh), you need to check for that.
- L1067 _protected prototype_ `void DeleteEditorActors();` — Delete all editor actors. This does not actually delete the actors in the world. You can call ClearWorld to include that.
- L1072 _protected prototype_ `void SetTimelineAnimNames(const TArray<TSharedPtr<FMLDeformerTrainingInputAnimName>>& AnimNames);` — Set the names of the anim sequences in the timeline.
- L1080 _protected prototype_ `bool IsEditorReadyForTrainingBasicChecks();` — Perform some basic checks to see if the editor can be ready to train the model. This checks whether there is an anim sequence, target mesh, and skeletal mesh. It can be called inside the UpdateIsReadyForTrainingState method, which can then do additional checks afterwards. @return Returns true when at least the basic required inputs have been selected, false if not.
- L1087 _protected prototype_ `FMLDeformerEditorActor* GetVisualizationModeBaseActor() const;` — Get the base actor depending on the currently active mode (train or test mode). The base actor is the linear-skinned one. @return A pointer to the linear skinned actor in either test or training mode.
- L1094 _protected prototype_ `const UAnimSequence* GetAnimSequence() const;` — Get the animation sequence, either the test or training one, depending on in which mode we are in. This can return a nullptr if no anim sequence has been set up yet. @return A pointer to the test sequence when we are in test mode, or the training anim sequence if we are in training mode.
- L1101 _protected prototype_ `double CalcTimelinePosition() const;` — Calculate the current timeline position offset, of the currently selected frame. This depends on whether we are in test or training mode. @return The timeline offset, in seconds.
- L1106 _protected prototype_ `void UpdateRanges();` — Update the timeline related ranges, based on the length of the training or testing data.
- L1108 _protected prototype_ `void AddCompareActor(int32 ArrayIndex);`
- L1109 _protected prototype_ `void RemoveCompareActor(int32 ArrayIndex);`
- L1110 _protected prototype_ `void RemoveAllCompareActors();`
- L1111 _protected prototype_ `void UpdateCompareActorLabels();`
- L1113 _protected prototype_ `int32 CalcNumValidCompareActorsPriorTo(int32 CompareActorIndex) const;`
- L1114 _protected prototype_ `virtual bool IsAnimIndexValid(int32 AnimIndex) const;`
- L1116 _protected prototype_ `void UpdateLODMappings();`
- L1123 _protected prototype_ `void UpdateStepInterpolationMode();` — Update whether we force to use step interpolation on the ML Deformed model or not. Step interpolation is needed when we are enabled heatmaps and have a ground truth mesh and are in ground truth heatmap mode. This will modify the AnimInstance's ForceStepInterpolation state on just the ML Deformed model. It can also disable it when needed.
- L1131 _protected prototype_ `void UpdateHeatMapMaterialBasedOnMode();` — Because of some technical reasons we cannot display a correct ground truth heat map at the moment while playing an animation. Scrubbing works fine though, because we can align on the right keyframes then. This method will look whether we are having heatmaps enabled or not, and if we are playing or not and if we're in ground truth mode. It then disables or enables the heatmap material based on the current state.
- L1144 _protected member_ `TArray<FLODInfo> LODMappings;` — The LOD information. The size of this array is the number of LODs on the skeletal mesh, unless less LOD levels are desired using MLD.
- L1147 _protected member_ `TArray<FVector3f> SkinnedPositions;` — A reusable array to store current LOD skinned vertex positions.
- L1150 _protected member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — The runtime model associated with this editor model.
- L1153 _protected member_ `TArray<FMLDeformerEditorActor*> EditorActors;` — The set of actors that can appear inside the editor viewport.
- L1156 _protected member_ `FMLDeformerEditorToolkit* Editor = nullptr;` — A pointer to the editor toolkit.
- L1159 _protected member_ `TArray<TSharedPtr<FMLDeformerSampler>> Samplers;` — A sampler for every input animation. These samplers are used to calculate the vertex deltas.
- L1162 _protected member_ `TSharedPtr<SMLDeformerInputWidget> InputWidget;` — The inputs widget.
- L1168 _protected member_ `TObjectPtr<UMLDeformerInputInfo> EditorInputInfo = nullptr;` — The input info as currently setup in the editor. This is different from the runtime model's input info, as that is the one that was used to train with.
- L1171 _protected member_ `TObjectPtr<UMaterial> HeatMapMaterial = nullptr;` — The heatmap material.
- L1174 _protected member_ `TObjectPtr<UMeshDeformer> HeatMapDeformerGraph = nullptr;` — The heatmap deformer graph.
- L1177 _protected member_ `TObjectPtr<UMeshDeformer> HeatMapDeformerGraphDualQuat = nullptr;` — The dual quaternion based heat map.
- L1180 _protected member_ `TArray<TSharedPtr<FName>> VertexAttributeNames;` — A list of vertex attribute names that can be used inside combobox UI elements.
- L1183 _protected member_ `FDelegateHandle PostEditPropertyDelegateHandle;` — The delegate handle to the post edit property event.
- L1186 _protected member_ `FDelegateHandle PostTransactedDelegateHandle;` — The delegate handle linked to PostTransacted of the model.
- L1189 _protected member_ `FDelegateHandle PreEditUndoDelegateHandle;` — The delegate handle linked to PreEditUndo of the model.
- L1192 _protected member_ `FDelegateHandle PostEditUndoDelegateHandle;` — The delegate handle linked to PostEditUndo of the model.
- L1195 _protected member_ `int32 CurrentTrainingFrame = -1;` — The current training frame.
- L1198 _protected member_ `TRange<double> ViewRange;` — The range we are currently viewing
- L1201 _protected member_ `TRange<double> WorkingRange;` — The working range of this model, encompassing the view range
- L1204 _protected member_ `TRange<double> PlaybackRange;` — The playback range of this model for each timeframe
- L1207 _protected member_ `FFrameTime ScrubPosition;` — The current scrub position.
- L1213 _protected member_ `bool bIsReadyForTraining = false;` — Are we ready for training? The training button in the editor will be enabled or disabled based on this on default.
- L1216 _protected member_ `bool bNeedToResampleInputOutputs = true;` — Do we need to resample all input/output data?
- L1219 _protected member_ `bool bDisplayFrames = true;` — Display frame numbers?
- L1222 _protected member_ `FDelegateHandle InputObjectModifiedHandle;` — The delegate that handles when an object got modified (any object).
- L1225 _protected member_ `FDelegateHandle InputObjectPropertyChangedHandle;` — The delegate that handles when an object property got changed (any object).
- L1228 _protected member_ `bool bNeedsAssetReinit = false;` — Set to true when on next tick we need to trigger an input assets changed event.
- L1234 _protected member_ `int32 NumTrainingFrames = 0;` — The total number of frames that can be used for training, based on the training input animations list. Call UpdateNumTrainingFrames() to refresh this value.
- L1237 _protected member_ `int32 ActiveTrainingInputAnimIndex = INDEX_NONE;` — The training input animation that is selected in the timeline.
- L1240 _protected member_ `bool bIsScrubbingTimeline = false;` — Are we currently scrubbing the timeline?

#### struct `UE::MLDeformer::FMLDeformerEditorModel::InitSettings`  
`struct InitSettings`  
_L85-89_
- desc: The editor model initialization settings. This is used in the Init call.
- L87 _public member_ `FMLDeformerEditorToolkit* Editor = nullptr;`
- L88 _public member_ `UMLDeformerModel* Model = nullptr;`

#### struct `UE::MLDeformer::FMLDeformerEditorModel::FLODInfo`  
`struct FLODInfo`  
_L1134-1141_
- L1140 _public member_ `TArray<int32> VtxMappingToLODZero;` — Map all vertices in this LOD into an imported vertex number in LOD 0. This basically tells us which vertex to get the vertex delta for, for each vertex in this LOD.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace MLDeformer` (scope `UE`)
- L1249 _function_ `template<class TrainingModelClass> ETrainingResult TrainModel(FMLDeformerEditorModel* EditorModel)` (scope `UE::MLDeformer`) — Train the model. This will execute the train function inside your python code. Provide the UMLDeformerTrainingModel inherited class type as template argument.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorModule.h` (Public)


#### class `UE::MLDeformer::FMLDeformerEditorModule`  
`class FMLDeformerEditorModule : public IModuleInterface`  
_L23-50_
- inherits: `IModuleInterface`
- desc: The ML Deformer editor module. This registers the editor mode and custom property customizations. It also contains the model registry, which you will use to register your custom models to the editor.
- L28 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface overrides.
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _public function_ `FMLDeformerEditorModelRegistry& GetModelRegistry()` — Get a reference to the ML Deformer model registry. You use this to see what kind of model types ther are, register new models, or create editor models for specific types of runtime models. @return A reference to the ML Deformer model registry.
- L38 _public function_ `const FMLDeformerEditorModelRegistry& GetModelRegistry() const`
- L45 _public function_ `void SetModelRegistry(const FMLDeformerEditorModelRegistry& Registry)` — Manually assign a new model registry. This can be used in some automated tests where we want to test with different registries, for example an empty one. @param Registry The model registry to use.
- L49 _private member_ `FMLDeformerEditorModelRegistry ModelRegistry;` — The model registry, which keeps track of all model types and instances created of these models, and how to create the editor models for specific runtime model types.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MLDeformer` (scope `UE`)
- L13 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorStyle.h` (Public)


#### class `UE::MLDeformer::FMLDeformerEditorStyle`  
`class FMLDeformerEditorStyle : public FSlateStyleSet`  
_L14-22_
- inherits: `FSlateStyleSet`
- desc: The editor style class that describes specific UI style related settings for the ML Deformer editor.
- L18 _public prototype_ `FMLDeformerEditorStyle();`
- L19 _public prototype_ `~FMLDeformerEditorStyle();`
- L21 _public prototype_ `static FMLDeformerEditorStyle& Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerEditorToolkit.h` (Public)


#### class `UE::MLDeformer::FToolsMenuExtender`  
`class FToolsMenuExtender`  
_L38-44_
- L41 _public prototype_ `virtual ~FToolsMenuExtender() = default;`
- L42 _public prototype_ `virtual FMenuEntryParams GetMenuEntry(FMLDeformerEditorToolkit& Toolkit) const = 0;`
- L43 _public function_ `virtual TSharedPtr<FWorkflowTabFactory> GetTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& Toolkit) const`

#### class `UE::MLDeformer::FMLDeformerEditorToolkit`  
`class FMLDeformerEditorToolkit : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit, public FGCObject, public FEditorUndoClient, public FTickableEditorObject`  
_L50-239_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit,FGCObject,FEditorUndoClient,FTickableEditorObject`
- desc: The ML Deformer asset editor toolkit. This is the editor that opens when you double click an ML Deformer asset.
- L61 _public prototype_ `~FMLDeformerEditorToolkit();`
- L64 _public prototype_ `void InitAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMLDeformerAsset* InDeformerAsset);` — Initialize the asset editor. This will register the application mode, init the preview scene, etc.
- L70 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;` — FAssetEditorToolkit overrides.
- L71 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L72 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L73 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L74 _public prototype_ `virtual FText GetToolkitName() const override;`
- L75 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L76 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L77 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override;`
- L78 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;`
- L82 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L83 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L87 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject overrides.
- L88 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L89 _public prototype_ `virtual TStatId GetStatId() const override;`
- L93 _public prototype_ `void PostUndo(bool bSuccess) override;` — FEditorUndoClient overrides.
- L94 _public prototype_ `void PostRedo(bool bSuccess) override;`
- L98 _public prototype_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override;` — IHasPersonaToolkit overrides.
- L99 _public function_ `IPersonaToolkit* GetPersonaToolkitPointer() const`
- L102 _public function_ `void SetVizSettingsDetailsView(TSharedPtr<IDetailsView> InDetailsView)`
- L103 _public prototype_ `IDetailsView* GetVizSettingsDetailsView() const;`
- L105 _public prototype_ `IDetailsView* GetModelDetailsView() const;`
- L107 _public prototype_ `void SetTimeSlider(TSharedPtr<SMLDeformerTimeline> InTimeSlider);`
- L108 _public prototype_ `SMLDeformerTimeline* GetTimeSlider() const;`
- L110 _public function_ `UMLDeformerAsset* GetDeformerAsset() const`
- L111 _public function_ `FMLDeformerEditorModel* GetActiveModel()`
- L112 _public function_ `TWeakPtr<FMLDeformerEditorModel> GetActiveModelPointer()`
- L113 _public function_ `const FMLDeformerEditorModel* GetActiveModel() const`
- L114 _public function_ `FMLDeformerApplicationMode* GetApplicationMode() const`
- L115 _public function_ `TSharedPtr<IPersonaViewport> GetViewport() const`
- L117 _public function_ `void SetNeedsPaintModeDisable(bool bNeedsDisable)`
- L119 _public prototype_ `double CalcTimelinePosition() const;`
- L120 _public prototype_ `void OnTimeSliderScrubPositionChanged(double NewScrubTime, bool bIsScrubbing);`
- L121 _public prototype_ `void UpdateTimeSliderRange();`
- L122 _public prototype_ `void SetTimeSliderRange(double StartTime, double EndTime);`
- L124 _public prototype_ `void EnablePaintMode();`
- L125 _public prototype_ `void DisablePaintMode();`
- L126 _public prototype_ `bool IsDefaultModeActive() const;`
- L127 _public prototype_ `bool IsPaintModeActive() const;`
- L129 _public function_ `bool IsInitialized() const`
- L137 _public prototype_ `bool SwitchModelType(UClass* ModelType, bool bForceChange);` — Switch the editor to a given model type. @param ModelType The model type you want to switch to, for example something like: UNeuralMorphModel::StaticClass(). @param bForceChange Force changing to this model? This will suppress any UI popups. @return Returns true in case we successfully switched model types, or otherwise false is returned.
- L144 _public prototype_ `void SwitchVizMode(EMLDeformerVizMode Mode);` — Switch the editor's visualization mode. This essentially allows you to switch the UI between testing and training modes. @param Mode The mode to switch to.
- L146 _public prototype_ `bool Train(bool bSuppressDialogs);`
- L147 _public prototype_ `bool IsTrainButtonEnabled() const;`
- L148 _public prototype_ `bool IsTraining() const;`
- L151 _public prototype_ `AActor* GetDebugActor() const;` — Get the actor we want to debug, if any. Returns a nullptr when we don't want to debug anything.
- L154 _public prototype_ `TArray<FTransform> GetDebugActorComponentSpaceTransforms() const;` — Get the component space transforms of the actor we want to debug. Returns an empty array if GetDebugActor returns a nullptr.
- L156 _public prototype_ `void ZoomOnActors();`
- L158 _public function_ `TSharedPtr<SMLDeformerDebugSelectionWidget> GetDebugWidget() const`
- L160 _public prototype_ `static void AddToolsMenuExtender(TUniquePtr<FToolsMenuExtender> Extender);`
- L161 _public prototype_ `static TConstArrayView<TUniquePtr<FToolsMenuExtender>> GetToolsMenuExtenders();`
- L164 _private prototype_ `void OnModelChanged(int Index, bool bForceChange);`
- L167 _private prototype_ `void ExtendToolbar();` — Toolbar related.
- L168 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L171 _private prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Preview scene setup.
- L172 _private prototype_ `void HandleViewportCreated(const TSharedRef<IPersonaViewport>& InPersonaViewport);`
- L173 _private prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L174 _private prototype_ `void OnFinishedChangingDetails(const FPropertyChangedEvent& PropertyChangedEvent);`
- L177 _private prototype_ `void ShowNotification(const FText& Message, SNotificationItem::ECompletionState State, bool PlaySound) const;` — Helpers.
- L178 _private prototype_ `FText GetOverlayText() const;`
- L179 _private prototype_ `void OnSwitchedVisualizationMode();`
- L180 _private prototype_ `bool HandleTrainingResult(ETrainingResult TrainingResult, double TrainingDuration, bool& bOutUsePartiallyTrained, bool bSuppressDialogs, bool& bOutSuccess);`
- L181 _private prototype_ `FText GetActiveModelName() const;`
- L182 _private prototype_ `FText GetCurrentVizModeName() const;`
- L183 _private prototype_ `FText GetVizModeName(EMLDeformerVizMode Mode) const;`
- L184 _private prototype_ `void ShowNoModelsWarningIfNeeded();`
- L185 _private prototype_ `EVisibility GetDebuggingVisibility() const;`
- L186 _private prototype_ `FSlateIcon GetTrainingStatusIcon() const;`
- L188 _private prototype_ `TSharedRef<SWidget> GenerateModelButtonContents(TSharedRef<FUICommandList> InCommandList);`
- L189 _private prototype_ `TSharedRef<SWidget> GenerateVizModeButtonContents(TSharedRef<FUICommandList> InCommandList);`
- L190 _private prototype_ `TSharedRef<SWidget> GenerateToolsMenuContents(TSharedRef<FUICommandList> InCommandList);`
- L195 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — The persona toolkit.
- L198 _private member_ `TSharedPtr<IDetailsView> ModelDetailsView;` — Model details view.
- L201 _private member_ `TSharedPtr<IDetailsView> VizSettingsDetailsView;` — Model viz settings details view.
- L204 _private member_ `TSharedPtr<SMLDeformerTimeline> TimeSlider;` — The timeline slider widget.
- L207 _private member_ `TSharedPtr<FMLDeformerEditorModel> ActiveModel;` — The currently active editor model.
- L210 _private member_ `TSharedPtr<IPersonaViewport> PersonaViewport;` — Persona viewport.
- L213 _private member_ `TObjectPtr<UMLDeformerAsset> DeformerAsset;` — The ML Deformer Asset.
- L216 _private member_ `TSharedPtr<SMLDeformerDebugSelectionWidget> DebugWidget;` — The widget where you select which actor to debug.
- L219 _private member_ `FMLDeformerApplicationMode* ApplicationMode = nullptr;` — The active application mode.
- L222 _private member_ `bool bIsInitialized = false;` — Has the asset editor been initialized?
- L225 _private member_ `bool bIsTraining = false;` — Are we currently in a training process?
- L232 _private member_ `bool bNeedsPaintModeDisable = false;` — When set to true, the paint mode will be disabled automatically. This is used to defer the disable of the paint mode to a later stage in the frame, as sometimes this can cause issues by deactivating or activating modes while in a loop over all modes.
- L235 _private member_ `static TArray<TUniquePtr<FToolsMenuExtender>> ToolsMenuExtenders;` — Extenders for Tools menu
- L238 _private member_ `static FCriticalSection ExtendersMutex;` — Mutex for adding extenders

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace MLDeformer` (scope `UE`)
- L32 _namespace_ `namespace MLDeformerEditorModes` (scope `UE::MLDeformer`)
- L34 _externvar_ `extern const FName Editor;` (scope `UE::MLDeformer::MLDeformerEditorModes`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheActor.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheActor`  
`class FMLDeformerGeomCacheActor : public FMLDeformerEditorActor`  
_L18-42_
- inherits: `FMLDeformerEditorActor`
- desc: An editor actor with a geometry cache component on it. This can for example be used as ground truth viewport actors.
- L22 _public prototype_ `FMLDeformerGeomCacheActor(const FConstructSettings& Settings);`
- L24 _public function_ `void SetGeometryCacheComponent(UGeometryCacheComponent* Component)`
- L25 _public function_ `UGeometryCacheComponent* GetGeometryCacheComponent() const`
- L28 _public prototype_ `virtual void SetVisibility(bool bIsVisible) override;` — FMLDeformerEditorActor overrides.
- L29 _public prototype_ `virtual bool IsVisible() const override;`
- L30 _public prototype_ `virtual bool HasVisualMesh() const override;`
- L31 _public prototype_ `virtual void SetPlayPosition(float TimeInSeconds, bool bAutoPause = true) override;`
- L32 _public prototype_ `virtual float GetPlayPosition() const override;`
- L33 _public prototype_ `virtual void SetPlaySpeed(float PlaySpeed) override;`
- L34 _public prototype_ `virtual void Pause(bool bPaused) override;`
- L35 _public prototype_ `virtual bool IsPlaying() const override;`
- L36 _public prototype_ `virtual FBox GetBoundingBox() const override;`
- L41 _protected member_ `TObjectPtr<UGeometryCacheComponent> GeomCacheComponent = nullptr;` — The geometry cache component.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheEditorModel.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheEditorModel`  
`class FMLDeformerGeomCacheEditorModel : public FMLDeformerEditorModel`  
_L23-69_
- inherits: `FMLDeformerEditorModel`
- desc: An editor model for the a model derived from the UMLDeformerGeomCacheModel runtime model. This editor model automatically handles sampling of the geometry caches to calculate deltas. It also handles the creation of ground truth models with a geometry cache on them.
- L28 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L32 _public prototype_ `virtual void Init(const InitSettings& Settings) override;` — FMLDeformerEditorModel overrides.
- L33 _public prototype_ `virtual void CopyBaseSettingsFromModel(const FMLDeformerEditorModel* SourceEditorModel) override;`
- L34 _public prototype_ `virtual FMLDeformerEditorActor* CreateEditorActor(const FMLDeformerEditorActor::FConstructSettings& Settings) const override;`
- L35 _public prototype_ `virtual TSharedPtr<FMLDeformerSampler> CreateSamplerObject() const override;`
- L36 _public prototype_ `virtual void CreateTrainingGroundTruthActor(UWorld* World) override;`
- L37 _public prototype_ `virtual void CreateTestGroundTruthActor(UWorld* World) override;`
- L38 _public prototype_ `virtual int32 GetNumTrainingInputAnims() const override;`
- L39 _public prototype_ `virtual FMLDeformerTrainingInputAnim* GetTrainingInputAnim(int32 Index) const override;`
- L40 _public prototype_ `virtual void UpdateNumTrainingFrames() override;`
- L41 _public prototype_ `virtual void UpdateIsReadyForTrainingState() override;`
- L42 _public prototype_ `virtual void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `virtual void OnInputAssetsChanged() override;`
- L44 _public prototype_ `virtual void OnObjectModified(UObject* Object) override;`
- L45 _public prototype_ `virtual ETrainingResult Train() override;`
- L49 _public prototype_ `UMLDeformerGeomCacheModel* GetGeomCacheModel() const;` — Helpers.
- L50 _public prototype_ `UMLDeformerGeomCacheVizSettings* GetGeomCacheVizSettings() const;`
- L51 _public prototype_ `FMLDeformerGeomCacheActor* FindGeomCacheEditorActor(int32 ID) const;`
- L52 _public prototype_ `UGeometryCache* GetActiveGeometryCache() const;`
- L68 _protected prototype_ `void CreateGeomCacheActor(UWorld* World, int32 ActorID, const FName& Name, UGeometryCache* GeomCache, FLinearColor LabelColor, FLinearColor WireframeColor, const FText& LabelText, bool bIsTrainingActor);` — Creates a geometry cache editor actor (FMLDeformerGeomCacheActor) of a specific ID with a specific geometry cache and label. This will add a new editor actor to the list of editor actors. @param World The world to create the actor in. @param ActorID The ID that the actor will have after creation, for example UE::MLDeformer::ActorID_Train_GroundTruth. @param Name The name of the actor in the scene. @param GeomCache The geometry cache to use on this actor. @param LabelColor The color of the label that is rendered with the editor actor inside the editor viewport. @param WireframeColor The color of this actor when wireframe rendering is enabled. @param LabelText The text of the label. @param bIsTrainingActor Set this to true when the actor is an actor to be used in training mode, or set to false when it is to be used in testing mode.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheModelDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheModelDetails`  
`class FMLDeformerGeomCacheModelDetails : public FMLDeformerModelDetails`  
_L27-42_
- inherits: `FMLDeformerModelDetails`
- desc: The detail customization of a geometry cache based model. The model it customizes needs to be derived from UMLDeformerGeomCacheModel. It will automatically insert some error when the geom cache doesn't match the animation sequence etc. If your model inherits from a UMLDeformerGeomCacheModel then you can also inherit your model detail customization from this FMLDeformerGeomCacheModelDetails class.
- L32 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects) override;` — FMLDeformerModelDetails overrides.
- L33 _public prototype_ `virtual void AddTrainingInputAnims() override;`
- L38 _protected member_ `TObjectPtr<UMLDeformerGeomCacheModel> GeomCacheModel = nullptr;` — The geometry cache based runtime model. This value gets updated once UpdateMemberPointers gets called.
- L41 _protected member_ `FMLDeformerGeomCacheEditorModel* GeomCacheEditorModel = nullptr;` — The geometry cache based editor model. This value gets updated once UpdateMemberPointers gets called.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheSampler.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheSampler`  
`class FMLDeformerGeomCacheSampler : public FMLDeformerSampler`  
_L23-62_
- inherits: `FMLDeformerSampler`
- desc: The input data sampler, which is used to sample vertex positions from geometry caches. It can then also calculate deltas between the sampled skeletal mesh data and geometry cache data.
- L28 _public prototype_ `virtual void Init(FMLDeformerEditorModel* InModel, int32 InAnimIndex) override;` — FVertexDeltaSampler overrides.
- L29 _public prototype_ `virtual void Sample(int32 AnimFrameIndex) override;`
- L30 _public prototype_ `virtual float GetTimeAtFrame(int32 InAnimFrameIndex) const override;`
- L40 _public function_ `const TArray<FString>& GetFailedImportedMeshNames() const` — Get the array of mesh names that we cannot do any sampling for. The reason for this can be that the sampler cannot find a matching mesh in the skeletal mesh for specific geometry cache tracks. For example if there is some geometry cache track that is named "Head", but there is no such mesh inside the skeletal mesh, then the returned array of names will include a string with the value "Head". @return An array of geometry cache track names for which no mesh could be found inside the SkeletalMesh / linear skinned actor.
- L42 _public function_ `UGeometryCacheComponent* GetGeometryCacheComponent()`
- L43 _public function_ `UGeometryCacheComponent* GetGeometryCacheComponent() const`
- L45 _public function_ `const TArray<FMLDeformerGeomCacheMeshMapping>& GetMeshMappings() const`
- L49 _protected member_ `TObjectPtr<UGeometryCacheComponent> GeometryCacheComponent = nullptr;` — The geometry cache component used to sample the geometry cache.
- L52 _protected member_ `TArray<FMLDeformerGeomCacheMeshMapping> MeshMappings;` — Maps skeletal meshes imported meshes to geometry tracks.
- L55 _protected member_ `TArray<FGeometryCacheMeshData> GeomCacheMeshDatas;` — The geometry cache mesh data reusable buffers. One for each MeshMapping.
- L58 _protected member_ `TArray<FString> FailedImportedMeshNames;` — Geom cache track names for which no mesh can be found inside the skeletal mesh.
- L61 _protected member_ `TArray<FString> VertexCountMisMatchNames;` — Imported mesh names in the skeletal mesh for which the geometry track had a different vertex count.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheTrainingInputAnimCustomize.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheTrainingInputAnimCustomization`  
`class FMLDeformerGeomCacheTrainingInputAnimCustomization : public IPropertyTypeCustomization`  
_L24-38_
- inherits: `IPropertyTypeCustomization`
- desc: The ML Deformer's training input animation (that uses a geometry cache) type customization. This is used to show a custom UI when displaying the FMLDeformerGeomCacheTrainingInputAnim struct. That struct is shown in the list of training input animations in the details panel. @see FMLDeformerGeomCacheTrainingInputAnim
- L28 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization overrides.
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L36 _private prototype_ `bool FilterAnimSequences(const FAssetData& AssetData, USkeleton* Skeleton);`
- L37 _private prototype_ `UMLDeformerGeomCacheModel* FindMLDeformerModel(TSharedRef<IPropertyHandle> StructPropertyHandle) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheTrainingModel.h` (Public)


#### class `UMLDeformerGeomCacheTrainingModel`  
`class UMLDeformerGeomCacheTrainingModel : public UMLDeformerTrainingModel`  
_L17-43_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMLDeformerTrainingModel`
- desc: The training model base class for geometry cache based models. This class is our link to the Python training.
- L24 _public prototype_ `virtual void Init(UE::MLDeformer::FMLDeformerEditorModel* InEditorModel) override;` — UMLDeformerTrainingModel overrides.
- L25 _public prototype_ `virtual bool SampleNextFrame() override;`
- L32 _public prototype_ `bool GenerateBasicInputsAndOutputBuffers(const FString& InputsFilePath, const FString& OutputsFilePath);` — `UFUNCTION(BlueprintCallable, Category = "ML Deformer Training")` — Sample all input frames.
- L42 _protected prototype_ `virtual bool FindNextAnimToSample(int32& OutNextAnimIndex) const override;` — Find the next input animation to sample from. This is an index inside the training input animations list. This assumes the SampleAnimIndex member as starting point. The method does not modify this member directly, unless passed in as parameter. @param OutNextAnimIndex The next animation index to sample from when we take our next sample. @return Returns true when we found our next animation to sample. Returns false when we already sampled everything.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerGeomCacheVizSettingsDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerGeomCacheVizSettingsDetails`  
`class FMLDeformerGeomCacheVizSettingsDetails : public FMLDeformerVizSettingsDetails`  
_L20-35_
- inherits: `FMLDeformerVizSettingsDetails`
- desc: The visualization settings detail customization for a geometry cache based model. A geometry cache based model is one inherited from the UMLDeformerGeomCacheModel base class. You can inherit your own model detail customization from this class if you also inherited your model from the UMLDeformerGeomCacheModel class.
- L25 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects) override;` — FMLDeformerVizSettingsDetails overrides.
- L26 _public prototype_ `virtual void AddGroundTruth() override;`
- L31 _protected member_ `TObjectPtr<UMLDeformerGeomCacheModel> GeomCacheModel = nullptr;` — The geometry cache based runtime model pointer. This is updated once UpdateMemberPointers is called.
- L34 _protected member_ `TObjectPtr<UMLDeformerGeomCacheVizSettings> GeomCacheVizSettings = nullptr;` — A pointer to the geom cache based visualization settings. This is updated once UpdateMemberPointers is called.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerModelDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerModelDetails`  
`class FMLDeformerModelDetails : public IDetailCustomization`  
_L30-97_
- inherits: `IDetailCustomization`
- desc: The ML Deformer model detail customization base class. This adds the shared properties, inserts error messages, creates some groups, etc. Model detail customizations should all inherit from this class. If you use a geometry cache based model however, you will likely inherit from other classes such as FMLDeformerGeomCacheModelDetails or FMLDeformerMorphModelDetails. Those classes are also inherited from this one though.
- L35 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.
- L42 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects);` — Update the class member pointers, which includes the pointer to the model, and its editor model. @param Objects The array of objects that the detail customization is showing.
- L46 _public prototype_ `virtual void CreateCategories();` — Create the categories that we can add properties to. This will update the category member pointers.
- L49 _public function_ `virtual void AddBaseMeshErrors()` — Add additional errors related to the base mesh.
- L52 _public function_ `virtual void AddBoneInputErrors()` — Add additional errors related to bone inputs.
- L55 _public function_ `virtual void AddCurveInputErrors()` — Add additional errors related to curve inputs.
- L58 _public prototype_ `virtual void AddTrainingInputAnims();` — Add the property that shows the input animations.
- L61 _public function_ `virtual void AddTrainingInputFlags()` — Add training input flags, which basically are things like the check boxes that specify whether bones or curves (or both) should be included.
- L64 _public function_ `virtual void AddTrainingInputErrors()` — Add additional training input errors.
- L67 _public function_ `virtual void AddTrainingSettingsErrors()` — Add training settings errors.
- L71 _protected prototype_ `bool FilterAnimSequences(const FAssetData& AssetData, USkeleton* Skeleton);` — The filter that only shows anim sequences that are compatible with the given skeleton.
- L75 _protected member_ `IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;` — Associated detail layout builder.
- L78 _protected member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — A pointer to the model we are customizing details for.
- L81 _protected member_ `FMLDeformerEditorModel* EditorModel = nullptr;` — A pointer to the editor model of the runtime model.
- L84 _protected member_ `IDetailCategoryBuilder* BaseMeshCategoryBuilder = nullptr;` — The category related to the base mesh.
- L87 _protected member_ `IDetailCategoryBuilder* TargetMeshCategoryBuilder_DEPRECATED = nullptr;` — The category related to the target mesh.
- L90 _protected member_ `IDetailCategoryBuilder* InputOutputCategoryBuilder = nullptr;` — The category related to the inputs and outputs.
- L93 _protected member_ `IDetailCategoryBuilder* TrainingSettingsCategoryBuilder = nullptr;` — The training settings category. You most likely add your model properties to this.
- L96 _protected member_ `IDetailCategoryBuilder* LODSettingsCategoryBuilder = nullptr;` — The LOD generation category. This category can be hidden, based on whether the model supports LOD or not.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerModelRegistry.h` (Public)


#### class `UE::MLDeformer::FMLDeformerEditorModelRegistry`  
`class FMLDeformerEditorModelRegistry`  
_L26-136_
- desc: The editor model registry, which keeps track of different types of runtime ML Deformer models and their related editor models. When you create a new ML Deformer model type, you register it to this registry using the RegisterEditorModel method. You typically do this in your editor module's StartupModule method. And you unregister it again in the editor module's ShutdownModule method. Models can have priorities. The one model with the highest priority level will be the model that is created by default when creating a new ML Deformer asset.
- L32 _public prototype_ `~FMLDeformerEditorModelRegistry();`
- L43 _public prototype_ `void RegisterEditorModel(UClass* ModelType, FOnGetEditorModelInstance Delegate, int32 ModelPriority = 0);` — Register a new model. This is needed to make the model appear inside the UI of the editor as selectable model. Call this method in your editor module's StartupModule call. @param ModelType The type of the runtime model, for example UNeuralMorphModel::StaticClass(). @param Delegate The function that creates the editor model that's related to this editor model, for example FOnGetEditorModelInstance::CreateStatic(&FNeuralMorphEditorModel::MakeInstance). This MakeInstance function must return the new editor model associated with this model. @param ModelPriority The priority level of this model. The model with the highest priority is created by default when creating a new ML Deformer Asset. If there is a model with the same priority level already, and it happens to be the highest priority model, then this new model will take over as priority model.
- L50 _public prototype_ `void UnregisterEditorModel(const UClass* ModelType);` — Unregister the editor model. Call this method in your editor module's ShutdownModule call. @param ModelType The model type to unregister, for example UNeuralMorphModel::StaticClass().
- L57 _public prototype_ `FMLDeformerEditorModel* GetEditorModel(UMLDeformerModel* Model);` — Get the editor model related to a given runtime model. @param Model The runtime model to get the editor model object for. @return A pointer to the editor model object for this specific runtime model instance, or nullptr when not found.
- L63 _public prototype_ `int32 GetNumRegisteredModels() const;` — Get the number of registered models. @return The number of models that have been registered through RegisterEditorModel.
- L69 _public prototype_ `int32 GetNumInstancedModels() const;` — Get the number of instanced models. @return The number of instanced models.
- L76 _public prototype_ `UClass* GetHighestPriorityModel() const;` — Get the highest priority runtime model class. The model with the highest priority is created by default when creating a new ML Deformer Asset. @return Returns the model class of the highest priority model, or nullptr when there are none.
- L83 _public prototype_ `int32 GetPriorityForModel(UClass* ModelType) const;` — Get the priority level for a given runtime model type. @param ModelType The runtime model type, for example UNeuralMorphModel::StaticClass(). @return The model priority level, or if it cannot be found it will return MIN_int32.
- L89 _public prototype_ `const TMap<UClass*, FOnGetEditorModelInstance>& GetRegisteredModels() const;` — Get the read-only map of registered models. @return The map of registered models that have been registered through RegisterEditorModel.
- L95 _public prototype_ `const TMap<UMLDeformerModel*, FMLDeformerEditorModel*>& GetModelInstances() const;` — Get the read-only map that maps instanced models with their editor models. @return The map that provides the editor model for a specific runtime model.
- L102 _public prototype_ `int32 GetHighestPriorityModelIndex() const;` — Get the highest priority model index into the map. It is the 'index'-th item in the array that you can iterate by doing something like: for (auto& Item : Map). @return The highest priority model index.
- L109 _private prototype_ `void UpdateHighestPriorityModel();` — Update the highest priority model by looking at the priority map. This updates the value returned by GetHighestPriorityModel().
- L115 _private prototype_ `void RemoveEditorModelInstance(FMLDeformerEditorModel* EditorModel);` — Remove a given editor model instance. @param EditorModel A pointer to the editor model to remove.
- L122 _private prototype_ `FMLDeformerEditorModel* CreateEditorModel(UMLDeformerModel* Model);` — Create a new editor model for a given runtime model. @param Model The runtime model object to create an editor model for. @return A pointer to the newly created editor model.
- L126 _private member_ `TMap<UClass*, FOnGetEditorModelInstance> Map;` — A map that maps runtime model types with a function that creates its editor model.
- L129 _private member_ `TMap<UMLDeformerModel*, FMLDeformerEditorModel*> InstanceMap;` — A map of runtime model instances, and the related editor models.
- L132 _private member_ `TMap<UClass*, int32> ModelPriorities;` — The map of model type priority levels.
- L135 _private member_ `UClass* HighestPriorityModelType = nullptr;` — The registered model type that has the highest priority level.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_RetVal(FMLDeformerEditorModel*, FOnGetEditorModelInstance);`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal(FMLDeformerEditorModel*, FOnGetEditorModelInstance);` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerMorphModelDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerMorphModelDetails`  
`class FMLDeformerMorphModelDetails : public FMLDeformerGeomCacheModelDetails`  
_L22-59_
- inherits: `FMLDeformerGeomCacheModelDetails`
- desc: The detail customization for models inherited from the UMLDeformerMorphModel class. You can inherit the detail customization for your own model from this class if your model inherited from the UMLDeformerMorphModel class.
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.
- L31 _public prototype_ `virtual void CreateCategories() override;` — FMLDeformerModelDetails overrides.
- L32 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects) override;`
- L48 _protected prototype_ `bool ShouldShowShadingError() const;` — Check whether we should show an error in the UI about possible shading artifacts. The ML Deformer cannot run properly if all of the following things are true: - Skin cache is disabled - Material settings have "Use with morph targets" disabled. - No deformer graph is being used. This method checks those points. If not, we can show a warning in the UI. @return Returns true if an error should be displayed in the UI about this issue.
- L52 _protected member_ `TObjectPtr<UMLDeformerMorphModel> MorphModel = nullptr;` — A pointer to the morph model. This is updated when UpdateMemberPointers is called.
- L55 _protected member_ `FMLDeformerMorphModelEditorModel* MorphModelEditorModel = nullptr;` — A pointer to the editor model for the morph model. This is updated when UpdateMemberPointers is called.
- L58 _protected member_ `IDetailCategoryBuilder* MorphTargetCategoryBuilder = nullptr;` — The morph settings category.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerMorphModelEditorModel.h` (Public)


#### class `UE::MLDeformer::FMLDeformerMorphModelEditorModel`  
`class FMLDeformerMorphModelEditorModel : public FMLDeformerGeomCacheEditorModel`  
_L22-286_
- inherits: `FMLDeformerGeomCacheEditorModel`
- desc: The editor model related to the runtime UMLDeformerMorphModel class, or models inherited from that.
- L27 _public prototype_ `static FMLDeformerEditorModel* MakeInstance();` — We need to implement this static MakeInstance method.
- L30 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L34 _public prototype_ `virtual void CopyBaseSettingsFromModel(const FMLDeformerEditorModel* SourceEditorModel) override;` — FMLDeformerEditorModel overrides.
- L35 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L36 _public prototype_ `virtual void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L37 _public prototype_ `virtual FString GetHeatMapDeformerGraphPath() const override;`
- L38 _public prototype_ `virtual FString GetHeatMapDeformerGraphDualQuatPath() const override;`
- L39 _public prototype_ `virtual void OnPreTraining() override;`
- L40 _public prototype_ `virtual void OnPostTraining(ETrainingResult TrainingResult, bool bUsePartiallyTrainedWhenAborted) override;`
- L41 _public prototype_ `virtual void OnMaxNumLODsChanged() override;`
- L42 _public prototype_ `virtual void OnObjectModified(UObject* Object) override;`
- L52 _public function_ `virtual bool IsMorphWeightClampingSupported() const` — Returns whether this model supports morph output weight clamping or not. This is used to make sure the morph target weights are within valid ranges. Some models might choose not to do this, because they might already clamp input values. When this returns false, the "Clamp morph weights" option in the UI will also be hidden. @return Returns true when the model supports morph weight clamping, otherwise false is returned.
- L58 _public prototype_ `virtual const TArrayView<const float> GetMaskForMorphTarget(int32 MorphTargetIndex) const;` — Get the mask buffer for a given morph target. @param MorphTargetIndex The morph target index, excluding the first 'means' morph target that we always have, so 0 would mean the actual first real morph target.
- L66 _public prototype_ `virtual bool IsInputMaskingSupported() const;` — Check if input masking is supported in this model. This allows bones and curves to specify a given mask. These masks can be used during training. On default this is disabled. @return Returns true if supported, or false otherwise.
- L75 _public prototype_ `void FillMaskValues(TArrayView<float> ItemMaskBuffer, float Value) const;` — Fill the mask buffer for a given item with a specific value. An item can be a bone, curve, bone group or curve group. The number of values written is always Model->GetNumBaseMeshVerts(). @param MaskBuffer The mask buffer to write to. The mask buffer view has Model->GetBaseNumVerts() elements. @param Value The value to write for all vertices.
- L83 _public prototype_ `void ApplyBoneToMask(int32 SkeletonBoneIndex, TArrayView<float> MaskBuffer);` — Add bone influences to the mask. Every vertex that is linked to the specified bone will write its skinning weight to the mask buffer. @param SkeletonBoneIndex The bone index inside our reference skeleton. @param MaskBuffer The mask buffer to write to.
- L94 _public prototype_ `void RecursiveAddBoneToMaskUpwards(const FReferenceSkeleton& RefSkel, int32 SkeletonBoneIndex, int32 MaxHierarchyDepth, TArray<int32>& OutBonesAdded, int32 CurHierarchyDepth = 0);` — Recursively add bone masks for this bone and its parents. The number of parents is controlled by the MaxHierarchyDepth. @param RefSkel The reference skeleton. @param SkeletonBoneIndex The bone index of our current bone to add to the mask. @param MaxHierarchyDepth The maximum hierarchy depth. If this is 1, it means that we visit only up to the parent of the specified bone. If it is 2, we also visit the parent of the parent, etc. @param OutBoneAdded The list of bones that we already added to the mask. Bones that are in this list will not be added to the mask again. @param CurHierarchyDepth The current recursive hierarchy depth. This is used to track how deep we are when moving up the hierarchy. A value of 1 means we are currently adding the parent of the initial bone.
- L105 _public prototype_ `void RecursiveAddBoneToMaskDownwards(const FReferenceSkeleton& RefSkel, int32 SkeletonBoneIndex, int32 MaxHierarchyDepth, TArray<int32>& OutBonesAdded, int32 CurHierarchyDepth = 0);` — Recursively add bone masks for this bone and its children. The number of child steps down the hierarchy is controlled by the MaxHierarchyDepth. @param RefSkel The reference skeleton. @param SkeletonBoneIndex The bone index of our current bone to add to the mask. @param MaxHierarchyDepth The maximum hierarchy depth. If this is 1, it means that we visit only down to the children of the specified bone. If it is 2, we also visit the children of the children, etc. @param OutBoneAdded The list of bones that we already added to the mask. Bones that are in this list will not be added to the mask again. @param CurHierarchyDepth The current recursive hierarchy depth. This is used to track how deep we are when moving down the hierarchy. A value of 1 means we are currently adding a child node of the initial bone.
- L113 _public prototype_ `void ApplyMaskInfoToBuffer(const USkeletalMesh* SkeletalMesh, const FMLDeformerMaskInfo& MaskInfo, TArrayView<float> ItemMaskBuffer);` — Apply the mask info to the mask buffer of floats. @param SkeletalMesh The skeletal mesh that the mask relates to. @param MaskInfo The mask info object to apply to the float mask buffer. @param ItemMaskBuffer The mask buffer for this item. This should be an array view of size NumBaseMeshVerts.
- L124 _public prototype_ `void ApplyGeneratedMaskToVertexAttributes(USkeletalMesh* SkeletalMesh, FMLDeformerMaskInfo& MaskInfo, TVertexAttributesRef<float> AttributeRef);` — Apply a generated mask to a specific vertex attribute. This copy the generated values one to one to the vertex attribute, but it applies some scaling to the attributes to give better results. If we don't do this scaling then the values often look too small and the vertex attribute visually looks very light, rather than clearly defining the area. This will also ensure the mask gets generated, even if the MaskInfo masking mode is set to something non-generated. @param SkeletalMesh The skeletal mesh that the vertex attribute is on. @param MaskInfo The mask info object that we generate the mask from. @param AttributeRef The output vertex attributes to write to.
- L127 _public prototype_ `UMLDeformerMorphModel* GetMorphModel() const;` — Helpers.
- L128 _public prototype_ `UMLDeformerMorphModelVizSettings* GetMorphModelVizSettings() const;`
- L131 _protected prototype_ `void TransferMorphTargets(TArray<UMorphTarget*> MorphTargetsLODZero);`
- L140 _protected prototype_ `virtual void InitEngineMorphTargets(const TArray<FVector3f>& Deltas);` — Initialize a set of engine morph targets and compress them to GPU friendly buffers. These morph targets are initialized from a set of deltas. Each morph target needs to have Model->GetNumBaseVerts() number of deltas. All deltas are concatenated in one big array. So all deltas of all vertices for the second morph target are appended to the deltas for the first morph target, etc. In other words, the layout is: [morph0_deltas][morph1_deltas][morph2_deltas][...]. @param Deltas The deltas for all morph targets concatenated. So the number of items in this array is a multiple of Model->GetNumBaseVerts().
- L146 _protected prototype_ `void ClampMorphTargetNumber();` — Clamp the current morph target number inside the visualization settings to a valid range. This won't let the number of the morph target that we are visualizing go above the total number of morph targets.
- L153 _protected prototype_ `void UpdateMorphErrorValues(TArrayView<UMorphTarget*> MorphTargets);` — Update the morph target error values. This assigns an error value for each morph target. Internally this calls SetMorphTargetsErrorOrder to set the actual order and errors. @param MorphTargets The morph targets to calculate the errors and order for.
- L170 _protected prototype_ `virtual void CalcMorphTargetNormals( int32 LOD, const USkeletalMesh* SkelMesh, int32 MorphTargetIndex, const TArrayView<const FVector3f> Deltas, const TArrayView<const FVector3f> BaseVertexPositions, const TArrayView<const FVector3f> BaseNormals, const TArrayView<const int32> ImportedVertexToRenderVertexMapping, const FColorVertexBuffer& ColorBuffer, EMLDeformerMaskChannel MaskChannel, bool bInvertGlobalMaskChannel, const TArray<float>& GlobalMaskWeights, TArray<FVector3f>& OutDeltaNormals);` — Calculate the delta normals for a given morph target. @param LOD The LOD level. @param SkelMesh The skeletal mesh to get the mesh data from. @param MorphTargetIndex The morph target to calculate the normals for. @param Deltas The per vertex deltas. The number of elements in this array is NumMorphTargets * NumImportedVertices. @param BaseVertexPositions The positions of the base/neutral mesh, basically the unskinned vertices. @param BaseNormals The normals of the neutral base mesh. @param ImportedVertexToRenderVertexMapping The array of size 'NumImportedVerts' (NumBaseMeshVerts) that maps to a render vertex. @param ColorBuffer The color buffer to use when calculating the global mask. @param MaskChannel The global mask channel, for example which color channel to use from the color buffer. @param bInvertGlobalMask Set to true when you want the global mask to be inverted. @param GlobalMaskWeights The array of weights, one for each render vertex. @param OutDeltaNormals The array that we will write the generated normals to. This will automatically be resized by this method.
- L194 _protected prototype_ `void DebugDrawMorphTarget(FPrimitiveDrawInterface* PDI, const TArray<FVector3f>& MorphDeltas, float DeltaThreshold, int32 MorphTargetIndex, const FVector& DrawOffset);` — Debug draw specific morph targets using lines and points. This can show the user what deltas are included in which morph target. @param PDI A pointer to the draw interface. @param MorphDeltas A buffer of deltas for ALL morph targets. The size of the buffer must be a multiple of Model->GetBaseNumVerts(). So the layout of this buffer is [Morph0_Deltas][Morph1_Deltas][Morph2_Deltas] etc. @param DeltaThreshold Deltas with a length  larger or equal to the given threshold value will be colored differently than the ones smaller than this threshold. @param MorphTargetIndex The morph target number to visualize. @param DrawOffset An offset to perform the debug draw at.
- L197 _protected prototype_ `void ZeroDeltasByLengthThreshold(TArray<FVector3f>& Deltas, float Threshold);` — Zero all deltas with a length equal to, or smaller than the threshold value.
- L213 _protected prototype_ `void CreateMorphTargets( TArray<UMorphTarget*>& OutMorphTargets, const TArray<FVector3f>& Deltas, const FString& NamePrefix = TEXT("MorphTarget_"), int32 LOD = 0, float DeltaThreshold = 0.01f, bool bIncludeNormals=false, const EMLDeformerMaskChannel MaskChannel = EMLDeformerMaskChannel::Disabled, bool bInvertMaskChannel = false);` — Generate engine morph targets from a set of deltas. @param OutMorphTargets The output array with generated morph targets. This array will be reset, and then filled with generated morph targets. @param Deltas The per vertex deltas for all morph targets, as one big buffer. Each morph target has 'GetNumBaseMeshVerts()' number of deltas. @param NamePrefix The morph target name prefix. If set to "MorphTarget_" the names will be "MorphTarget_000", "MorphTarget_001", "MorphTarget_002", etc. @param LOD The LOD index to generate the morphs for. @param DeltaThreshold Only include deltas with a length larger than this threshold in the morph targets. @param bIncludeNormals Include normals inside the morph targets? This can be an alternative to recalculating normals at the end, although setting this to true and not recomputing normals can lead to lower quality results, in trade for faster performance. @param MaskChannel The weight mask mode, which specifies what channel to get the weight data from. Such channel allows the user to define what areas the deformer should for example not be active in. @param bInvertMaskChannel Specifies whether the weight mask should be inverted or not. @param MaskBuffer An optional mask buffer that contains 'Model->GetNumBaseMeshVerts() * (MorphModel->GetNumMorphTargets() - 1)' number of floats. Deltas will be multiplied by this value. When the mask buffer is an empty array, it will be ignored.
- L230 _protected prototype_ `void CompressMorphTargets(FMorphTargetVertexInfoBuffers& OutMorphBuffers, const TArray<UMorphTarget*>& MorphTargets, int32 LOD = 0, float MorphErrorTolerance = 0.01f);` — Compress morph targets into GPU based morph buffers. @param OutMorphBuffers The output compressed GPU based morph buffers. If this buffer is already initialized it will be released first. @param MorphTargets The morph targets to compress into GPU friendly buffers. @param LOD The LOD index to generate the morphs for. @param MorphErrorTolerance The error tolerance for the delta compression, in cm. Higher values compress better but can result in artifacts.
- L240 _protected prototype_ `void CalcVertexNormals(TArrayView<const FVector3f> VertexPositions, TArrayView<const uint32> IndexArray, TArrayView<const int32> VertexMap, TArray<FVector3f>& OutNormals) const;` — Calculate the normals for each vertex, given the triangle data and positions. It computes this by summing up the face normals for each vertex using that face, and normalizing them at the end. @param VertexPositions The buffer with vertex positions. This is the size of the number of imported vertices. @param IndexArray The index buffer, which contains NumTriangles * 3 number of integers. @param VertexMap For each render vertex, an imported vertex number. For example, for a cube these indices go from 0..7. @param OutNormals The array that will contain the normals. This will automatically be resized internally by this method.
- L254 _protected prototype_ `bool ProcessVertexDelta(FVector3f& OutScaledDelta, FVector3f& OutScaledDeltaNormal, const FVector3f RawDelta, const FVector3f RawDeltaNormal, float DeltaThreshold, float MorphMaskWeight, float GlobalMaskWeight) const;` — Process and filter a vertex delta position and normal and apply scaling to it. The scaling of these deltas is based on a given morph mask weight, a global mask weight, and a delta zero threshold, which filters out small deltas entirely. @param OutScaledDelta The scaled version of the delta position. @param OutScaledDeltaNormal The scaled version of the delta normal. @param RawDelta The unscaled raw delta position. @param RawDeltaNormal The unscaled raw delta normal. @param DeltaThreshold Any scaled vertex delta position vector with a length smaller or equal to this value, will cause this method to return false. This basically can be used to filter out small deltas. @param MorphMaskWeight The weight value of the morph target mask for this vertex. This can be values larger than 1 as well, but always larger or equal to 0. @param GlobalMaskWeight The global weight value for this vertex. This global mask / weight is used to disable the deformer in specific regions on the mesh, for example where the head or neck connects with the body. @return Returns true if this vertex should be included in the morph target, or false if it has been filtered out based on the provided delta threshold.
- L264 _protected prototype_ `TArray<float> CalcGlobalMaskWeights(const TArray<int32>& VertexMap, const FColorVertexBuffer& ColorBuffer, EMLDeformerMaskChannel MaskChannel, bool bInvertMaskChannel) const;` — Calculate the global mask weight for a specific render vertex, using a color buffer and specified mask channel settings. @param VertexMap The render vertex to import vertex map. @param ColorBuffer The color buffer which we can grab color values from, which are used to calculate the mask weight. @param MaskChannel The channel to grab the weight value from. This specifieds whether the mask is enabled and if so, from what channel (r, g, b, a) we grab the weight value. @param bInvertMaskChannel Set to true when we should invert the weight value. @return An array with a weight per render vertex. A value of 1.0 is returned when the mask channel is set to disable the mask. The return value is always between 0 and 1.
- L269 _protected function_ `void SetNeedsRebuildMaskBuffer()` — Tell the editor model that we should update the mask buffer on the next Tick call.
- L276 _protected member_ `TArray<FVector3f> MorphTargetDeltasBackup;` — The entire set of morph target deltas, 3 per vertex, for each morph target, as one flattened buffer. So the size of this buffer is: (NumVertsPerMorphTarget * NumMorphTargets).
- L279 _protected member_ `TArray<FFloatInterval> MorphTargetsMinMaxWeightsBackup;` — The backup of the minimum and maximum weights for each morph target.
- L282 _protected member_ `TArray<float> InputItemMaskBufferBackup;` — The backup of the input item mask buffer. This contains all the bone and bone group masks.
- L285 _protected member_ `bool bNeedsRebuildMaskInfo = false;` — Indicates whether we need to rebuild the mask buffer next Tick or not.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerMorphModelVizSettingsDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerMorphModelVizSettingsDetails`  
`class FMLDeformerMorphModelVizSettingsDetails : public FMLDeformerGeomCacheVizSettingsDetails`  
_L18-36_
- inherits: `FMLDeformerGeomCacheVizSettingsDetails`
- desc: The visualization settings for models inherited from the UMLDeformerMorphModel class.
- L23 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects) override;` — FMLDeformerVizSettingsDetails overrides.
- L24 _public prototype_ `virtual void AddAdditionalSettings() override;`
- L29 _protected prototype_ `bool IsMorphTargetsEnabled() const;` — Is the morph target visualization option/checkbox enabled?
- L32 _protected member_ `TObjectPtr<UMLDeformerMorphModel> MorphModel = nullptr;` — A pointer to the runtime morph model. This is updated when UpdateMemberPointers is called.
- L35 _protected member_ `TObjectPtr<UMLDeformerMorphModelVizSettings> MorphModelVizSettings = nullptr;` — A pointer to the morph model visualization settings. This is updated when UpdateMemberPointers is called.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerPaintMode.h` (Public)


#### class `UMLDeformerPaintMode`  
`class UMLDeformerPaintMode : public UBaseLegacyWidgetEdMode`  
_L19-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseLegacyWidgetEdMode`
- L25 _public member_ `const static FEditorModeID Id;`
- L27 _public prototype_ `UMLDeformerPaintMode();`
- L30 _public prototype_ `virtual void Enter() override;` — UEdMode overrides
- L31 _public prototype_ `virtual void CreateToolkit() override;`
- L32 _public function_ `virtual bool UsesTransformWidget() const override`
- L33 _public function_ `virtual bool UsesPropertyWidgets() const override`
- L34 _public function_ `virtual bool UsesToolkits() const override`
- L35 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L38 _public prototype_ `void SetMLDeformerEditor(UE::MLDeformer::FMLDeformerEditorToolkit* Editor);`
- L39 _public prototype_ `void UpdatePose(USkeletalMeshComponent* SkeletalMeshComponent, bool bFullUpdate=true);`
- L42 _private member_ `TArray<FVector3f> BindPosePositions;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerPaintModeToolkit.h` (Public)


#### class `UE::MLDeformer::FMLDeformerPaintModeToolkit`  
`class FMLDeformerPaintModeToolkit : public FModeToolkit`  
_L19-68_
- inherits: `FModeToolkit`
- L26 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — IToolkit overrides
- L27 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L28 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L29 _public function_ `virtual TSharedPtr<SWidget> GetInlineContent() const override`
- L32 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;` — FModeToolkit overrides
- L33 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L34 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L35 _public prototype_ `virtual FText GetActiveToolMessage() const override;`
- L37 _public function_ `void SetMLDeformerEditor(FMLDeformerEditorToolkit* Editor)`
- L38 _public function_ `UE::MLDeformer::FMLDeformerEditorToolkit* GetMLDeformerEditor() const`
- L41 _private prototype_ `void PostNotification(const FText& Message);`
- L42 _private prototype_ `void ClearNotification();`
- L44 _private prototype_ `void PostWarning(const FText& Message);`
- L45 _private prototype_ `void ClearWarning();`
- L47 _private prototype_ `void UpdateActiveToolProperties(UInteractiveTool* Tool);`
- L49 _private prototype_ `void RegisterPalettes();`
- L50 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L52 _private prototype_ `void MakeToolAcceptCancelWidget();`
- L54 _private member_ `FText ActiveToolName;`
- L55 _private member_ `FText ActiveToolMessage;`
- L56 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L58 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L60 _private member_ `FMLDeformerEditorToolkit* MLDeformerEditor = nullptr;`
- L62 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`
- L63 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L65 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L66 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L67 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerSampler.h` (Public)


#### enum `UE::MLDeformer::EVertexDeltaSpace`  
`enum class EVertexDeltaSpace : int8`  
_L25-32_
- desc: The space in which the sampler will calculate its vertex deltas.
- L28 _public enumerator_ `PreSkinning` — Vertex deltas will be in pre-skinning space. We train on pre-skinning deltas.
- L31 _public enumerator_ `PostSkinning` — Vertex deltas will be in post-skinning space. Mostly used to visualize deltas in the viewport.

#### class `UE::MLDeformer::FMLDeformerSampler`  
`class FMLDeformerSampler`  
_L39-209_
- desc: The input data sampler. This class can sample bone rotations, curve values and vertex deltas. It does this by creating two temp actors, one with skeletal mesh component and one with geom cache component.
- L42 _public prototype_ `virtual ~FMLDeformerSampler();`
- L45 _public prototype_ `virtual void Init(FMLDeformerEditorModel* Model, int32 AnimIndex);` — Call Init whenever assets or other relevant settings change.
- L48 _public prototype_ `virtual void Sample(int32 AnimFrameIndex);` — Call this every time the frame changes. This will update all buffer contents.
- L51 _public function_ `virtual float GetTimeAtFrame(int32 InAnimFrameIndex) const` — Get the time in seconds, at a given frame index.
- L54 _public function_ `const TArray<FVector3f>& GetSkinnedVertexPositions() const` — Get the skinned vertex positions of the skeletal mesh.
- L57 _public function_ `const TArray<FVector3f>& GetUnskinnedVertexPositions() const` — Get the unskinned vertex positions of the skeletal mesh.
- L60 _public function_ `const TArray<float>& GetVertexDeltas() const` — Get the calculated vertex deltas. The space they will be in depends on the setup vertex deltas space.
- L68 _public function_ `const TArray<float>& GetBoneRotations() const` — Get the current bone rotations that we can feed to a neural network. The number of floats in the buffer equals to NumBones * 6. The six floats represent two columns of the 3x3 rotation matrix of the bone. @return The array of floats that we can pass to the neural network as inputs.
- L71 _public function_ `const TArray<float>& GetCurveValues() const` — Get the float values for the curves. One float per curve.
- L74 _public function_ `int32 GetNumImportedVertices() const` — Get the number of imported vertices.
- L77 _public function_ `EVertexDeltaSpace GetVertexDeltaSpace() const` — Get the space in which we will calculate the vertex deltas.
- L80 _public function_ `void SetVertexDeltaSpace(EVertexDeltaSpace DeltaSpace)` — Set the space in which we should calculate the vertex deltas.
- L83 _public function_ `EMLDeformerSkinningMode GetSkinningMode() const` — Get the skinning mode.
- L86 _public function_ `void SetSkinningMode(const EMLDeformerSkinningMode Mode)` — Set the skinning mode. This defines the type of skinning we use, like Linear Blend Skinning or Dual Quaternion skinning.
- L89 _public function_ `bool IsInitialized() const` — Have we already initialized this sampler? Is it ready for sampling?
- L92 _public prototype_ `int32 GetNumBones() const;` — Get the number of bones.
- L95 _public prototype_ `SIZE_T CalcMemUsagePerFrameInBytes() const;` — Calculate the memory usage of the sampler.
- L96 _public function_ `UDebugSkelMeshComponent* GetSkeletalMeshComponent()`
- L102 _public function_ `void SetNumFloatsPerCurve(int32 NumFloats)` — Set the number of floats used per curve. Values larger than 1 will cause padding with zeros. The first float is always the value. Floats that come after that will contain zeros on default.
- L105 _public function_ `int32 GetNumFloatsPerCurve() const` — Get the number of floats per curve.
- L108 _public prototype_ `void ExtractSkinnedPositions(int32 LODIndex, TArray<FVector3f>& OutPositions);` — Get the skinned positions for a given LOD level.
- L112 _protected prototype_ `virtual void CreateActors();` — Create the actors used for sampling. This creates two actors, one for the base skeletal mesh and one for the target mesh.
- L115 _protected prototype_ `void ExtractSkinnedPositions(int32 LODIndex, TArray<FMatrix44f>& InBoneMatrices, TArray<FVector3f>& TempPositions, TArray<FVector3f>& OutPositions) const;` — Extract the skinned vertex positions, of the skeletal mesh.
- L118 _protected prototype_ `void ExtractUnskinnedPositions(int32 LODIndex, TArray<FVector3f>& OutPositions) const;` — Extract the unskinned vertex positions, of the skeletal mesh.
- L121 _protected prototype_ `FMatrix44f CalcInverseSkinningTransform(int32 VertexIndex, const FSkeletalMeshLODRenderData& SkelMeshLODData, const FSkinWeightVertexBuffer& SkinWeightBuffer) const;` — Calculate the inverse skinning transform, which is used to convert from post-skinning to pre-skinning space.
- L124 _protected prototype_ `FVector3f CalcDualQuaternionDelta(int32 VertexIndex, const FVector3f& WorldDelta, const FSkeletalMeshLODRenderData& SkelMeshLODData, const FSkinWeightVertexBuffer& SkinWeightBuffer) const;` — Calculate the delta using dual quaternions, taking a world space delta vector as input.
- L127 _protected prototype_ `AActor* CreateNewActor(UWorld* InWorld, const FName& Name) const;` — Create a new actor with a specific name, in a specified world.
- L130 _protected prototype_ `void UpdateSkeletalMeshComponent();` — Update the skeletal mesh component's play position, and refresh its bone transforms internally.
- L133 _protected prototype_ `void UpdateSkinnedPositions();` — Update the skinned vertex positions.
- L136 _protected prototype_ `void UpdateBoneRotations();` — Update the bone rotation buffers.
- L139 _protected prototype_ `void UpdateCurveValues();` — Update the curve value buffers.
- L143 _protected member_ `FMLDeformerEditorModel* EditorModel = nullptr;` — The vertex delta editor model used to sample.
- L146 _protected member_ `TObjectPtr<AActor> SkelMeshActor = nullptr;` — The skeletal mesh actor used to sample the skinned vertex positions.
- L149 _protected member_ `TObjectPtr<AActor> TargetMeshActor = nullptr;` — The actor used for the target mesh.
- L152 _protected member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — The vertex delta model associated with this sampler.
- L155 _protected member_ `TObjectPtr<UDebugSkelMeshComponent> SkeletalMeshComponent = nullptr;` — The skeletal mesh component used to sample skinned positions.
- L158 _protected member_ `TArray<FVector3f> SkinnedVertexPositions;` — The skinned vertex positions.
- L161 _protected member_ `TArray<FVector3f> UnskinnedVertexPositions;` — The unskinned vertex positions.
- L164 _protected member_ `TArray<FVector3f> TempVertexPositions;` — A temp array to store vertex positions in.
- L167 _protected member_ `TArray<FMatrix44f> BoneMatrices;` — The sampled bone matrices.
- L173 _protected member_ `TArray<float> VertexDeltas;` — The vertex deltas as float buffer. The number of floats equals: NumImportedVerts * 3. The layout is (xyz)(xyz)(xyz)(...)
- L180 _protected member_ `TArray<float> BoneRotations;` — The bone rotation floats. The number of floats in the buffer equals to NumBones * 6. The six floats represent two columns of the 3x3 rotation matrix of the bone.
- L183 _protected member_ `TArray<float> CurveValues;` — A float for each Skeleton animation curve.
- L186 _protected member_ `float SampleTime = 0.0f;` — The current sample time, in seconds.
- L189 _protected member_ `int32 NumImportedVertices = 0;` — The number of imported vertices of the skeletal mesh and geometry cache. This will be 8 for a cube.
- L192 _protected member_ `int32 AnimFrameIndex = -1;` — The animation frame we sampled the deltas for.
- L195 _protected member_ `int32 AnimIndex = -1;` — The animation index for which this is a sampler for. This is in range of 0..GetNumTrainingInputAnims().
- L202 _protected member_ `int32 NumFloatsPerCurve = 1;` — The number of floats per curve value. If this is larger than 1, the remaining floats (after the first one) will be set to 0. So basically we will pad the curve values. The CurveValues float array will contain something like : "0.75, 0.0, 0.0, 0.0" when this is set to 4.
- L205 _protected member_ `EVertexDeltaSpace VertexDeltaSpace = EVertexDeltaSpace::PreSkinning;` — The vertex delta space (pre or post skinning) used when calculating the deltas.
- L208 _protected member_ `EMLDeformerSkinningMode SkinningMode = EMLDeformerSkinningMode::Linear;` — The skinning mode, which only works in combination with pre-skinning space.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerTestHelpers.h` (Public)


#### class `UE::MLDeformer::FMLDeformerScopedEditor`  
`class FMLDeformerScopedEditor`  
_L19-39_
- desc: A scoped ML Deformer editor, which auto closes the window on destruction.
- L22 _public prototype_ `FMLDeformerScopedEditor() = delete;`
- L23 _public prototype_ `FMLDeformerScopedEditor(const FMLDeformerScopedEditor&) = delete;`
- L24 _public prototype_ `FMLDeformerScopedEditor(FMLDeformerScopedEditor&&) = delete;`
- L25 _public prototype_ `FMLDeformerScopedEditor(FMLDeformerEditorToolkit* InEditor);`
- L26 _public prototype_ `FMLDeformerScopedEditor(UMLDeformerAsset* Asset);`
- L27 _public prototype_ `FMLDeformerScopedEditor(const FString& AssetName);`
- L28 _public prototype_ `~FMLDeformerScopedEditor();` — Auto close the editor window.
- L29 _public prototype_ `bool IsValid() const;`
- L30 _public prototype_ `void SetCloseEditor(bool bCloseOnDestroy);`
- L31 _public prototype_ `FMLDeformerEditorToolkit* Get() const;`
- L32 _public prototype_ `FMLDeformerEditorToolkit* operator = (const FMLDeformerScopedEditor&) = delete;`
- L33 _public prototype_ `FMLDeformerEditorToolkit* operator = (const FMLDeformerScopedEditor&&) = delete;`
- L34 _public prototype_ `FMLDeformerEditorToolkit* operator ->() const;`
- L37 _private member_ `FMLDeformerEditorToolkit* Editor = nullptr;`
- L38 _private member_ `bool bCloseEditor = true;`

#### class `UE::MLDeformer::FMLDeformerTestHelpers`  
`class FMLDeformerTestHelpers`  
_L42-69_
- desc: Some helper functions for testing ML Deformer related things.
- L51 _public prototype_ `static FMLDeformerEditorToolkit* OpenAssetEditor(UMLDeformerAsset* Asset);` — Open the asset editor for a given ML Deformer asset. This will log an error when something doesn't succeed. @param Asset A pointer to the asset to open an editor for. @return A pointer to the editor toolkit, or nullptr when it didn't succeed.
- L60 _public prototype_ `static FMLDeformerEditorToolkit* OpenAssetEditor(const FString& AssetName);` — Open the asset editor for a given ML Deformer asset, by its package name. This will log an error when something doesn't succeed. Examples of failure cases are when the package cannot be loaded, or if it doesn't contain a valid ML Deformer asset. @param Asset The package name, for example something like: "/MLDeformerFramework/Tests/MLD_Rampage.MLD_Rampage". @return A pointer to the editor toolkit, or nullptr when it didn't succeed.
- L68 _public prototype_ `static bool PostModelPropertyChanged(UMLDeformerModel* Model, const FName PropertyName);` — Post an edit change event for a given property in the Model class. @param Model The model that the property has been changed in. @param PropertyName The name of the property (the class member name). @return Returns true if successfully emitted the PostEditChangeProperty call, or false if the property cannot be found.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerTrainingModel.h` (Public)


#### class `UMLDeformerTrainingModel`  
`class UMLDeformerTrainingModel : public UObject`  
_L61-216_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: The training model base class. This class is used to interface with Python by providing some methods you can call inside your python training code. For example it allows you to get all the sampled data, such as the deltas, bones and curve values. When you create a new model you need to create a class inherited from this base class, and define a Train method inside it as follows: @code{.cpp} // Doesn't need an implementation inside cpp, just a declaration in the header file. UFUNCTION(BlueprintImplementableEvent, Category = "Training Model") int32 Train() const; @endcode Now inside your Python class you do something like: @code{.py} @unreal.uclass() class YourModelPythonTrainingModel(unreal.YourTrainingModel): @unreal.ufunction(override=True) def train(self): # ...do training here... return 0   # A value of 0 is success, 1 means aborted, see ETrainingResult. @endcode The editor will execute the Train method, which will trigger the "train" method in your Python class to be executed. Keep in mind that in Unreal Engine all python code is lower case. So a "Train" method inside c++ will need to be called "train" inside the python code. Or if you have something called "PerformMyTraining" it will need to be called "perform_my_training" inside Python.
- L72 _public prototype_ `virtual void Init(UE::MLDeformer::FMLDeformerEditorModel* InEditorModel);` — Initialize the training model. This is automatically called by the editor. @param InEditorModel The pointer to the editor model that this is a training model for.
- L76 _public prototype_ `UMLDeformerModel* GetModel() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the runtime ML Deformer model object.
- L80 _public prototype_ `int32 GetNumberSampleTransforms() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the number of input transforms. This is the number of bones.
- L84 _public prototype_ `int32 GetNumberSampleCurves() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get number of input curves.
- L88 _public prototype_ `int32 GetNumberSampleDeltas() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the number of vertex deltas.
- L92 _public prototype_ `int32 NumSamples() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the number of samples in this data set. This is the number of sample frames we want to train on.
- L96 _public prototype_ `void ResetSampling();` — `UFUNCTION(BlueprintCallable, Category = "Training Data")` — This will make the sampling start again from the beginning. This can be used if you have to iterate multiple times over the data set.
- L106 _public prototype_ `bool SetCurrentSampleIndex(int32 Index);` — `UE_DEPRECATED(5.4, "Please use NextSample instead.")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Please use NextSample instead."))` — Set the current sample frame. This will internally call the SampleFrame method, which will update the deltas, curve values and bone rotations. You call this before getting the input bone/curve and vertex delta values. @param Index The training data frame/sample number. @return Returns true when successful, or false when the specified sample index is out of range.
- L113 _public prototype_ `bool NextSample();` — `UFUNCTION(BlueprintCallable, Category = "Training Data")` — Take the next sample. This will update the deltas, curve values and bone rotation arrays with values sampled at the next frame. This will return false when there is something wrong or we sampled more times than NumSamples() returns.
- L121 _public prototype_ `bool GetNeedsResampling() const;` — `UFUNCTION(BlueprintCallable, Category = "Training Data")` — Check whether we need to resample the inputs and outputs, or if we can use a cached version. This will return true if any inputs changed, that indicate that we should regenerate any cached data. @return Returns true when we need to regenerate any cached data, otherwise false is returned.
- L125 _public prototype_ `void SetNeedsResampling(bool bNeedsResampling);` — `UFUNCTION(BlueprintCallable, Category = "Training Data")` — Specify whether we need to resample any cached data or not, because our input assets, or any other relevant settings changed that would invalidate the cached data.
- L129 _public prototype_ `void SetNumFloatsPerCurve(int32 NumFloatsPerCurve);` — `UFUNCTION(BlueprintCallable, Category = "Training Data")` — Set the number of floats per curve. On default this is one.
- L133 _public prototype_ `TArray<FName> GetTrainingInputAnimMasks() const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the names of all valid training animation masks. They are valid when they are used, the anim is enabled, and the attribute exists on the skeletal mesh.
- L137 _public prototype_ `TArray<float> GetTrainingInputAnimMaskData(FName MaskName) const;` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — Get the per vertex data for a given mask name. The mask name must be one that is present in the array returned by GetTrainingInputAnimMasks.
- L143 _public function_ `TArray<int32> GetMaskIndexPerSampleArray() const` — `UFUNCTION(BlueprintPure, Category = "Training Data")` — For each sample we took, this contains the index inside the mask as returned by the GetTrainingInputAnimMasks() array.
- L147 _public prototype_ `void SetDeviceList(const TArray<FString>& DeviceNames, int32 PreferredDeviceIndex);` — `UFUNCTION(BlueprintCallable, Category = "Training Model")` — Set the list of possible training devices.
- L150 _public prototype_ `void UpdateAvailableDevices() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Training Model")`
- L154 _protected prototype_ `virtual bool SampleNextFrame();` — Sample the next frame in the sequence of samples.
- L157 _protected prototype_ `void SetEditorModel(UE::MLDeformer::FMLDeformerEditorModel* InModel);` — Change the pointer to the editor model.
- L160 _protected prototype_ `UE::MLDeformer::FMLDeformerEditorModel* GetEditorModel() const;` — Get a pointer to the editor model.
- L169 _protected function_ `virtual bool FindNextAnimToSample(int32& OutNextAnimIndex) const` — Find the next input animation to sample from. This is an index inside the training input animations list. This assumes the SampleAnimIndex member as starting point. The method does not modify this member directly, unless passed in as parameter. @param OutNextAnimIndex The next animation index to sample from when we take our next sample. @return Returns true when we found our next animation to sample. Returns false when we already sampled everything.
- L175 _protected prototype_ `int32 GetMaskIndexForAnimIndex(int32 AnimIndex) const;` — Get the mask index for a given input training animation. @see GetTrainingInputAnimMasks.
- L180 _public member_ `TArray<float> SampleDeltas;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Data")` — The delta values per vertex for this sample. This is updated after NextSample is called. Contains an xyz (3 floats) for each vertex.
- L184 _public member_ `TArray<float> SampleCurveValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Data")` — The curve weights. This is updated after NextSample is called.
- L188 _public member_ `TArray<float> SampleBoneRotations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Data")` — The bone rotations in bone (local) space for this sample. This is updated after NextSample is called and is 6 floats per bone (2 columns of 3x3 rotation matrix).
- L193 _public member_ `TArray<int32> MaskIndexPerSample;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Data")` — The mask index for each sample. See GetTrainingInputAnimMasks() and GetTrainingInputAnimMaskData().
- L197 _protected member_ `UE::MLDeformer::FMLDeformerEditorModel* EditorModel = nullptr;` — A pointer to the editor model from which we use the sampler.
- L204 _protected member_ `TArray<int32> NumTimesSampled;` — The number of times a given input animation has been sampled. The size of the array equals the number of training input animations. Note that this also contains counts of disabled training input anims. These disabled ones should be ignored.
- L207 _protected member_ `int32 SampleAnimIndex = 0;` — The training input animation to take the next sample from.
- L210 _protected member_ `bool bFinishedSampling = false;` — Did we finish sampling? This is set to true when every possible frame has been sampled.
- L212 _protected member_ `TArray<FName> MaskNames;`
- L215 _protected member_ `static FName DefaultMaskName;` — The default mask name.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)
- L21 _function_ `template<class T> static T* NewDerivedObject()` (scope `UE::MLDeformer`) — A helper to create the last derived object of a given type. This is useful when we create a class in Python, derived from a given base class.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/MLDeformerVizSettingsDetails.h` (Public)


#### class `UE::MLDeformer::FMLDeformerVizSettingsDetails`  
`class FMLDeformerVizSettingsDetails : public IDetailCustomization`  
_L27-136_
- inherits: `IDetailCustomization`
- desc: The detail customization base class for any UMLDeformerVizSettings inherited object. This automatically adds the settings of the UMLDeformerVizSettings class to the UI and creates some groups, inserts error messages when needed, etc.
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.
- L36 _public function_ `IDetailLayoutBuilder* GetDetailLayoutBuilder() const` — Get a pointer to the detail layout builder.
- L39 _public prototype_ `FMLDeformerVizSettingsDetails() = default;` — `UE_DEPRECATED(5.4, Remove these constructors when StatsMainMemUsageGroup is removed and there is no longer warnings in the implicit functions)`
- L40 _public prototype_ `FMLDeformerVizSettingsDetails(const FMLDeformerVizSettingsDetails&);`
- L41 _public prototype_ `FMLDeformerVizSettingsDetails(FMLDeformerVizSettingsDetails&&);`
- L42 _public prototype_ `FMLDeformerVizSettingsDetails& operator=(const FMLDeformerVizSettingsDetails&);`
- L43 _public prototype_ `FMLDeformerVizSettingsDetails& operator=(FMLDeformerVizSettingsDetails&&);`
- L48 _protected prototype_ `bool FilterAnimSequences(const FAssetData& AssetData, USkeleton* Skeleton);` — The filter that only shows anim sequences that are compatible with the given skeleton.
- L51 _protected prototype_ `void OnResetToDefaultDeformerGraph(TSharedPtr<IPropertyHandle> PropertyHandle);` — When we click the reset to default button next to the deformer graph property.
- L54 _protected prototype_ `bool IsResetToDefaultDeformerGraphVisible(TSharedPtr<IPropertyHandle> PropertyHandle);` — Check if the reset to default button next to the deformer graph property should be visible or not.
- L60 _protected prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects);` — Update the class member pointers, which includes the pointer to the model, its editor model, and the viz settings. @param Objects The array of objects that the detail customization is showing.
- L63 _protected prototype_ `virtual void CreateCategories();` — Create the categories to which we can add properties. Update the member category pointers to those.
- L66 _protected function_ `virtual void AddTestSequenceErrors()` — Add some error message related to the test animation sequence.
- L69 _protected function_ `virtual void AddDeformerGraphErrors()` — Add some error related to the deformer graph.
- L72 _protected function_ `virtual void AddGroundTruth()` — Add the ground truth test sequence property.
- L75 _protected function_ `virtual void AddAdditionalSettings()` — Add any additional settings.
- L78 _protected prototype_ `virtual void AddStatistics();` — Add any statistics.
- L80 _protected prototype_ `void AddStatsPerfRow( IDetailGroup& Group, const FText& Label, const FMLDeformerEditorModel* InEditorModel, const FNumberFormattingOptions& Format, bool bHighlight, TFunctionRef<int32(const FMLDeformerEditorModel*)> GetCyclesFunction);`
- L90 _protected member_ `IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;` — Associated detail layout builder.
- L93 _protected member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — The ML deformer model that these visualization settings belong to.
- L96 _protected member_ `TObjectPtr<UMLDeformerVizSettings> VizSettings = nullptr;` — The visualization settings we are viewing.
- L99 _protected member_ `FMLDeformerEditorModel* EditorModel = nullptr;` — The editor model of the runtime model.
- L102 _protected member_ `IDetailCategoryBuilder* SharedCategoryBuilder = nullptr;` — A pointer to the shared settings category.
- L105 _protected member_ `IDetailCategoryBuilder* TestAssetsCategory = nullptr;` — A pointer to the test assets category.
- L108 _protected member_ `IDetailCategoryBuilder* LiveSettingsCategory = nullptr;` — A pointer to the live settings category.
- L111 _protected member_ `IDetailCategoryBuilder* TrainingMeshesCategoryBuilder = nullptr;` — A pointer to the training mesh category. This is only visible in training mode.
- L114 _protected member_ `IDetailCategoryBuilder* StatsCategoryBuilder = nullptr;` — A pointer to the statistics category.
- L117 _protected member_ `IDetailGroup* StatsPerformanceGroup = nullptr;` — The performance group inside the statistics category.
- L120 _protected member_ `IDetailGroup* StatsMemUsageGroup = nullptr;` — The memory usage group inside the statistics category.
- L123 _protected member_ `IDetailGroup* StatsAssetSizeGroup = nullptr;` — The memory usage group inside the statistics category.
- L126 _protected member_ `IDetailGroup* StatsMainMemUsageGroup_DEPRECATED = nullptr;` — Main memory usage subgroup.
- L129 _protected member_ `IDetailGroup* StatsGPUMemUsageGroup = nullptr;` — GPU memory usage subgroup.
- L132 _protected member_ `FNumberFormattingOptions PerformanceMetricFormat;` — Number format used for performance numbers.
- L135 _protected member_ `FNumberFormattingOptions MemUsageMetricFormat;` — Number format used for memory usage numbers.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerBonePickerDialog.h` (Public)


#### class `UE::MLDeformer::FMLDeformerBonePickerTreeElement`  
`class FMLDeformerBonePickerTreeElement : public TSharedFromThis<FMLDeformerBonePickerTreeElement>`  
_L24-34_
- inherits: `TSharedFromThis<FMLDeformerBonePickerTreeElement>`
- L28 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMLDeformerBonePickerTreeElement> InTreeElement, TSharedPtr<SMLDeformerBonePickerTreeWidget> InTreeWidget);`
- L31 _public member_ `TArray<TSharedPtr<FMLDeformerBonePickerTreeElement>> Children;`
- L32 _public member_ `FName Name;`
- L33 _public member_ `FSlateColor TextColor;`

#### class `UE::MLDeformer::SMLDeformerBonePickerTreeRowWidget`  
`class SMLDeformerBonePickerTreeRowWidget : public STableRow<TSharedPtr<FMLDeformerBonePickerTreeElement>>`  
_L37-48_
- inherits: `STableRow<TSharedPtr<FMLDeformerBonePickerTreeElement>>`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FMLDeformerBonePickerTreeElement> InTreeElement, TSharedPtr<SMLDeformerBonePickerTreeWidget> InTreeView);`
- L44 _private member_ `TWeakPtr<FMLDeformerBonePickerTreeElement> WeakTreeElement;`
- L45 _private prototype_ `FText GetName() const;`

#### class `UE::MLDeformer::SMLDeformerBonePickerTreeWidget`  
`class SMLDeformerBonePickerTreeWidget : public STreeView<TSharedPtr<FMLDeformerBonePickerTreeElement>>`  
_L51-73_
- inherits: `STreeView<TSharedPtr<FMLDeformerBonePickerTreeElement>>`
- L54 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerBonePickerTreeWidget)`
- L60 _public prototype_ `void Construct(const FArguments& InArgs);`
- L61 _public function_ `const TArray<TSharedPtr<FMLDeformerBonePickerTreeElement>>& GetRootElements() const`
- L62 _public prototype_ `void AddElement(TSharedPtr<FMLDeformerBonePickerTreeElement> Element, TSharedPtr<FMLDeformerBonePickerTreeElement> ParentElement);`
- L63 _public prototype_ `void Clear();`
- L66 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FMLDeformerBonePickerTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L67 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FMLDeformerBonePickerTreeElement> InItem, TArray<TSharedPtr<FMLDeformerBonePickerTreeElement>>& OutChildren);`
- L68 _private prototype_ `void OnMouseDoubleClicked(TSharedPtr<FMLDeformerBonePickerTreeElement> ClickedItem);`
- L71 _private member_ `TArray<TSharedPtr<FMLDeformerBonePickerTreeElement>> RootElements;`
- L72 _private member_ `TSharedPtr<SMLDeformerBonePickerDialog> PickerWidget;`

#### class `UE::MLDeformer::SMLDeformerBonePickerDialog`  
`class SMLDeformerBonePickerDialog : public SCustomDialog`  
_L80-127_
- inherits: `SCustomDialog`
- desc: A bone picker dialog window. This allows users to select one or more bones.
- L86 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerBonePickerDialog)`
- L87 _public prototype_ `SLATE_ARGUMENT(FReferenceSkeleton const*, RefSkeleton)` — The reference skeleton to grab the bone names and hierarchy from.
- L104 _public prototype_ `const TArray<FName>& GetPickedBoneNames() const;` — Get the array of picked bone names. This will be an empty list when nothing got selected, which means we basically cancelled. @return The array of selected bone names. Empty if cancelled or if no bones were there to begin with.
- L107 _private prototype_ `TSharedRef<SMLDeformerBonePickerTreeWidget> CreateBoneTree();`
- L108 _private prototype_ `FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L109 _private prototype_ `void OnOkClicked();`
- L110 _private prototype_ `void OnCancelClicked();`
- L111 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L112 _private prototype_ `void RefreshBoneTreeElements() const;`
- L113 _private prototype_ `void SelectInitialItems();`
- L114 _private prototype_ `void SelectInitialItemsRecursive(const TSharedPtr<FMLDeformerBonePickerTreeElement>& Item);`
- L117 _private member_ `TSharedPtr<SMLDeformerBonePickerTreeWidget> BoneTreeWidget;`
- L118 _private member_ `TSharedPtr<SWidget> ExtraWidget;`
- L119 _private member_ `TArray<FName> HighlightBoneNames;`
- L120 _private member_ `TArray<FName> InitialSelectedBoneNames;`
- L121 _private member_ `TArray<FName> IncludeList;`
- L122 _private member_ `FReferenceSkeleton const* RefSkeleton = nullptr;`
- L123 _private member_ `TArray<FName> PickedBoneNames;`
- L124 _private member_ `FSlateColor HighlightColor;`
- L125 _private member_ `bool bAllowMultiSelect = true;`
- L126 _private member_ `FString FilterText;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerCurvePickerDialog.h` (Public)


#### class `UE::MLDeformer::FMLDeformerCurvePickerElement`  
`class FMLDeformerCurvePickerElement : public TSharedFromThis<FMLDeformerCurvePickerElement>`  
_L26-36_
- inherits: `TSharedFromThis<FMLDeformerCurvePickerElement>`
- L30 _public prototype_ `FMLDeformerCurvePickerElement(const FName InName, const FSlateColor& InTextColor);`
- L31 _public prototype_ `TSharedRef<ITableRow> MakeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMLDeformerCurvePickerElement> InElement, TSharedPtr<SMLDeformerCurvePickerListView> InListView);`
- L34 _public member_ `FName Name;`
- L35 _public member_ `FSlateColor TextColor;`

#### class `UE::MLDeformer::SMLDeformerCurvePickerRowWidget`  
`class SMLDeformerCurvePickerRowWidget : public STableRow<TSharedPtr<FMLDeformerCurvePickerElement>>`  
_L39-50_
- inherits: `STableRow<TSharedPtr<FMLDeformerCurvePickerElement>>`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FMLDeformerCurvePickerElement> InTreeElement, TSharedPtr<SMLDeformerCurvePickerListView> InListView);`
- L46 _private member_ `TWeakPtr<FMLDeformerCurvePickerElement> WeakElement;`
- L47 _private prototype_ `FText GetName() const;`

#### class `UE::MLDeformer::SMLDeformerCurvePickerListView`  
`class SMLDeformerCurvePickerListView : public SListView<TSharedPtr<FMLDeformerCurvePickerElement>>`  
_L53-73_
- inherits: `SListView<TSharedPtr<FMLDeformerCurvePickerElement>>`
- L56 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerCurvePickerListView)`
- L62 _public prototype_ `void Construct(const FArguments& InArgs);`
- L63 _public prototype_ `void AddElement(TSharedPtr<FMLDeformerCurvePickerElement> Element);`
- L64 _public prototype_ `void Clear();`
- L67 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FMLDeformerCurvePickerElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L68 _private prototype_ `void OnMouseDoubleClicked(TSharedPtr<FMLDeformerCurvePickerElement> ClickedItem);`
- L71 _private member_ `TArray<TSharedPtr<FMLDeformerCurvePickerElement>> Elements;`
- L72 _private member_ `TSharedPtr<SMLDeformerCurvePickerDialog> PickerDialog;`

#### class `UE::MLDeformer::SMLDeformerCurvePickerDialog`  
`class SMLDeformerCurvePickerDialog : public SCustomDialog`  
_L76-117_
- inherits: `SCustomDialog`
- L82 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerCurvePickerDialog)`
- L83 _public prototype_ `SLATE_ARGUMENT(USkeletalMesh*, SkeletalMesh)` — The skeleton to pick the curves from.
- L98 _public prototype_ `const TArray<FName>& GetPickedCurveNames() const;` — Get the array of picked curves names. This will be an empty list when nothing got selected, which means we basically cancelled. @return The array of selected curves names. Empty if cancelled or if no curves were there to begin with.
- L101 _private prototype_ `TSharedRef<SMLDeformerCurvePickerListView> CreateListWidget();`
- L102 _private prototype_ `FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L103 _private prototype_ `void OnOkClicked();`
- L104 _private prototype_ `void OnCancelClicked();`
- L105 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L106 _private prototype_ `void RefreshListElements() const;`
- L109 _private member_ `TSharedPtr<SMLDeformerCurvePickerListView> CurveListView;`
- L110 _private member_ `TArray<FName> PickedCurveNames;`
- L111 _private member_ `TArray<FName> IncludeList;`
- L112 _private member_ `FString FilterText;`
- L113 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh;`
- L114 _private member_ `TArray<FName> HighlightCurveNames;`
- L115 _private member_ `FSlateColor HighlightColor = FSlateColor(FLinearColor::White);`
- L116 _private member_ `bool bAllowMultiSelect = true;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerCurvePickerWidget.h` (Public)


#### class `UE::MLDeformer::SCurvePickerWidget`  
`class SCurvePickerWidget : public SCompoundWidget`  
_L30-74_
- inherits: `SCompoundWidget`
- desc: The curve picker widget for the ML Deformer editor.
- L34 _public function_ `SLATE_BEGIN_ARGS(SCurvePickerWidget)`
- L35 _public prototype_ `SLATE_EVENT(FOnCurveNamePicked, OnCurveNamePicked) SLATE_EVENT(FOnGetSkeletalMesh, OnGetSkeletalMesh) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _public function_ `TSharedPtr<SSearchBox> GetFilterTextWidget() const`
- L44 _private prototype_ `void RefreshListItems();`
- L45 _private prototype_ `void FilterAvailableCurves();`
- L46 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionType);`
- L47 _private prototype_ `void HandleFilterTextChanged(const FText& InFilterText);`
- L48 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L52 _private member_ `FOnCurveNamePicked OnCurveNamePicked;` — Delegate fired when a curve name is picked.
- L55 _private member_ `FOnGetSkeletalMesh OnGetSkeletalMesh;` — Provide us with a skeletal mesh.
- L58 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search filter box.
- L61 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh;` — The skeletal mesh to get the curves from.
- L64 _private member_ `TArray<TSharedPtr<FString>> CurveNames;` — The names of the curves we are displaying.
- L67 _private member_ `TSet<FString> UniqueCurveNames;` — All the unique curve names we can find.
- L70 _private member_ `FString FilterText;` — The string we use to filter curve names.
- L73 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> NameListView;` — The list view used to display names.

#### class `UE::MLDeformer::SCurveSelectionWidget`  
`class SCurveSelectionWidget : public SCompoundWidget`  
_L79-105_
- inherits: `SCompoundWidget`
- desc: The curve selection widget for the ML Deformer.
- L83 _public function_ `SLATE_BEGIN_ARGS(SCurveSelectionWidget)`
- L84 _public prototype_ `SLATE_EVENT(FOnCurveSelectionChanged, OnCurveSelectionChanged);`
- L85 _public prototype_ `SLATE_EVENT(FOnGetSelectedCurve, OnGetSelectedCurve);`
- L86 _public prototype_ `SLATE_EVENT(FOnGetSkeletalMesh, OnGetSkeletalMesh) SLATE_END_ARGS();`
- L89 _public prototype_ `void Construct(const FArguments& InArgs);`
- L92 _private prototype_ `TSharedRef<SWidget> CreateSkeletonWidgetMenu();`
- L93 _private prototype_ `void OnSelectionChanged(const FString& CurveName);`
- L94 _private prototype_ `USkeletalMesh* GetSkeletalMesh() const;`
- L95 _private prototype_ `FText GetCurrentCurveName() const;`
- L96 _private prototype_ `FText GetFinalToolTip() const;`
- L99 _private member_ `TSharedPtr<SComboButton> CurvePickerButton;`
- L100 _private member_ `FOnCurveSelectionChanged OnCurveSelectionChanged;`
- L101 _private member_ `FOnGetSelectedCurve OnGetSelectedCurve;`
- L102 _private member_ `FOnGetSkeletalMesh OnGetSkeletalMesh;`
- L103 _private member_ `FText SuppliedToolTip;`
- L104 _private member_ `FText SelectedCurve;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCurveSelectionChanged, const FString&);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCurveSelectionChanged, const FString&);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCurveNamePicked, const FString&) DECLARE_DELEGATE_RetVal(FString, FOnGetSelectedCurve);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCurveNamePicked, const FString&) DECLARE_DELEGATE_RetVal(FString, FOnGetSelectedCurve);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FOnGetSelectedCurve);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(USkeletalMesh*, FOnGetSkeletalMesh) namespace UE::MLDeformer { class SCurvePickerWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SCurvePickerWidget) {} SLATE_EVENT(FOnCurveNamePicked, OnCurveNamePicked) SLATE_EVENT(FOnGetSkeletalMesh, OnGetSkeletalMesh) SLATE_END_ARGS() void Construct(const FArguments& InArgs); TSharedPtr<SSearchBox> GetFilterTextWidget() const { return SearchBox; } private: void RefreshListItems(); void FilterAvailableCurves(); void HandleSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionType); void HandleFilterTextChanged(const FText& InFilterText); TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& InOwnerTable); private: FOnCurveNamePicked OnCurveNamePicked; FOnGetSkeletalMesh OnGetSkeletalMesh; TSharedPtr<SSearchBox> SearchBox; TWeakObjectPtr<USkeletalMesh> SkeletalMesh;`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerInputBonesWidget.h` (Public)


#### class `UE::MLDeformer::FMLDeformerInputBonesWidgetCommands`  
`class FMLDeformerInputBonesWidgetCommands : public TCommands<FMLDeformerInputBonesWidgetCommands>`  
_L25-39_
- inherits: `TCommands<FMLDeformerInputBonesWidgetCommands>`
- L29 _public prototype_ `FMLDeformerInputBonesWidgetCommands();`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> AddInputBones;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DeleteInputBones;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ClearInputBones;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> AddAnimatedBones;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CopyInputBones;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PasteInputBones;`

#### class `UE::MLDeformer::FMLDeformerInputBoneTreeElement`  
`class FMLDeformerInputBoneTreeElement : public TSharedFromThis<FMLDeformerInputBoneTreeElement>`  
_L42-52_
- inherits: `TSharedFromThis<FMLDeformerInputBoneTreeElement>`
- L46 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMLDeformerInputBoneTreeElement> InTreeElement, TSharedPtr<SMLDeformerInputBoneTreeWidget> InTreeWidget);`
- L49 _public member_ `FName Name;`
- L50 _public member_ `TArray<TSharedPtr<FMLDeformerInputBoneTreeElement>> Children;`
- L51 _public member_ `FSlateColor TextColor;`

#### class `UE::MLDeformer::SMLDeformerInputBoneTreeRowWidget`  
`class SMLDeformerInputBoneTreeRowWidget : public STableRow<TSharedPtr<FMLDeformerInputBoneTreeElement>>`  
_L55-66_
- inherits: `STableRow<TSharedPtr<FMLDeformerInputBoneTreeElement>>`
- L59 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FMLDeformerInputBoneTreeElement> InTreeElement, TSharedPtr<SMLDeformerInputBoneTreeWidget> InTreeView);`
- L62 _private member_ `TWeakPtr<FMLDeformerInputBoneTreeElement> WeakTreeElement;`
- L63 _private prototype_ `FText GetName() const;`

#### class `UE::MLDeformer::SMLDeformerInputBoneTreeWidget`  
`class SMLDeformerInputBoneTreeWidget : public STreeView<TSharedPtr<FMLDeformerInputBoneTreeElement>>`  
_L69-96_
- inherits: `STreeView<TSharedPtr<FMLDeformerInputBoneTreeElement>>`
- L72 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerInputBoneTreeWidget)`
- L77 _public prototype_ `void Construct(const FArguments& InArgs);`
- L78 _public function_ `const TArray<TSharedPtr<FMLDeformerInputBoneTreeElement>>& GetRootElements() const`
- L79 _public prototype_ `void AddElement(TSharedPtr<FMLDeformerInputBoneTreeElement> Element, TSharedPtr<FMLDeformerInputBoneTreeElement> ParentElement);`
- L80 _public prototype_ `void RefreshElements(const TArray<FName>& BoneNames, const FReferenceSkeleton* RefSkeleton);`
- L81 _public prototype_ `TArray<FName> ExtractAllElementNames() const;`
- L84 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FMLDeformerInputBoneTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L85 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FMLDeformerInputBoneTreeElement> InItem, TArray<TSharedPtr<FMLDeformerInputBoneTreeElement>>& OutChildren);`
- L86 _private prototype_ `FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L87 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening() const;`
- L88 _private prototype_ `void RecursiveSortElements(TSharedPtr<FMLDeformerInputBoneTreeElement> Element);`
- L89 _private prototype_ `void RecursiveAddNames(const FMLDeformerInputBoneTreeElement& Element, TArray<FName>& OutNames) const;`
- L90 _private prototype_ `void OnSelectionChanged(TSharedPtr<FMLDeformerInputBoneTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L91 _private prototype_ `TSharedPtr<FMLDeformerInputBoneTreeElement> FindParentElementForBone(FName BoneName, const FReferenceSkeleton& RefSkeleton, const TMap<FName, TSharedPtr<FMLDeformerInputBoneTreeElement>>& NameToElementMap) const;`
- L94 _private member_ `TArray<TSharedPtr<FMLDeformerInputBoneTreeElement>> RootElements;`
- L95 _private member_ `TSharedPtr<SMLDeformerInputBonesWidget> InputBonesWidget;`

#### class `UE::MLDeformer::SMLDeformerInputBonesWidget`  
`class SMLDeformerInputBonesWidget : public SCompoundWidget`  
_L99-135_
- inherits: `SCompoundWidget`
- L104 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerInputBonesWidget)`
- L110 _public prototype_ `void Construct(const FArguments& InArgs);`
- L111 _public prototype_ `void Refresh();`
- L112 _public prototype_ `void BindCommands(TSharedPtr<FUICommandList> CommandList);`
- L113 _public prototype_ `TSharedPtr<SMLDeformerInputBoneTreeWidget> GetTreeWidget() const;`
- L114 _public prototype_ `TSharedPtr<SMLDeformerInputWidget> GetInputWidget() const;`
- L115 _public prototype_ `FText GetSectionTitle() const;`
- L118 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L119 _private prototype_ `void RefreshTree(bool bBroadCastPropertyChanged=true);`
- L120 _private prototype_ `bool BroadcastModelPropertyChanged(const FName PropertyName);`
- L122 _private prototype_ `void OnAddInputBones();`
- L123 _private prototype_ `void OnDeleteInputBones();`
- L124 _private prototype_ `void OnClearInputBones();`
- L125 _private prototype_ `void OnAddAnimatedBones();`
- L126 _private prototype_ `void OnCopyInputBones() const;`
- L127 _private prototype_ `void OnPasteInputBones();`
- L130 _private member_ `TSharedPtr<SMLDeformerInputBoneTreeWidget> TreeWidget;`
- L131 _private member_ `TSharedPtr<SMLDeformerInputWidget> InputWidget;`
- L132 _private member_ `FMLDeformerEditorModel* EditorModel = nullptr;`
- L133 _private member_ `FString FilterText;`
- L134 _private member_ `FText SectionTitle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerInputCurvesWidget.h` (Public)


#### class `UE::MLDeformer::FMLDeformerInputCurvesWidgetCommands`  
`class FMLDeformerInputCurvesWidgetCommands : public TCommands<FMLDeformerInputCurvesWidgetCommands>`  
_L25-39_
- inherits: `TCommands<FMLDeformerInputCurvesWidgetCommands>`
- L29 _public prototype_ `FMLDeformerInputCurvesWidgetCommands();`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> AddInputCurves;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DeleteInputCurves;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ClearInputCurves;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> AddAnimatedCurves;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CopyInputCurves;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PasteInputCurves;`

#### class `UE::MLDeformer::FMLDeformerInputCurveListElement`  
`class FMLDeformerInputCurveListElement : public TSharedFromThis<FMLDeformerInputCurveListElement>`  
_L42-51_
- inherits: `TSharedFromThis<FMLDeformerInputCurveListElement>`
- L46 _public prototype_ `TSharedRef<ITableRow> MakeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMLDeformerInputCurveListElement> InTreeElement, TSharedPtr<SMLDeformerInputCurveListWidget> InTreeWidget);`
- L49 _public member_ `FName Name;`
- L50 _public member_ `FSlateColor TextColor;`

#### class `UE::MLDeformer::SMLDeformerInputCurveListRowWidget`  
`class SMLDeformerInputCurveListRowWidget : public STableRow<TSharedPtr<FMLDeformerInputCurveListElement>>`  
_L54-65_
- inherits: `STableRow<TSharedPtr<FMLDeformerInputCurveListElement>>`
- L58 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FMLDeformerInputCurveListElement> InElement, TSharedPtr<SMLDeformerInputCurveListWidget> InListView);`
- L61 _private member_ `TWeakPtr<FMLDeformerInputCurveListElement> WeakElement;`
- L62 _private prototype_ `FText GetName() const;`

#### class `UE::MLDeformer::SMLDeformerInputCurveListWidget`  
`class SMLDeformerInputCurveListWidget : public SListView<TSharedPtr<FMLDeformerInputCurveListElement>>`  
_L68-91_
- inherits: `SListView<TSharedPtr<FMLDeformerInputCurveListElement>>`
- L71 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerInputCurveListWidget)`
- L76 _public prototype_ `void Construct(const FArguments& InArgs);`
- L77 _public function_ `const TArray<TSharedPtr<FMLDeformerInputCurveListElement>>& GetElements() const`
- L78 _public prototype_ `void AddElement(TSharedPtr<FMLDeformerInputCurveListElement> Element);`
- L79 _public prototype_ `void RefreshElements(const TArray<FName>& CurveNames, USkeletalMesh* SkeletalMesh);`
- L82 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FMLDeformerInputCurveListElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L83 _private prototype_ `FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L84 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening() const;`
- L85 _private prototype_ `void SortElements();`
- L86 _private prototype_ `void OnSelectionChanged(TSharedPtr<FMLDeformerInputCurveListElement> Selection, ESelectInfo::Type SelectInfo);`
- L89 _private member_ `TArray<TSharedPtr<FMLDeformerInputCurveListElement>> Elements;`
- L90 _private member_ `TSharedPtr<SMLDeformerInputCurvesWidget> InputCurvesWidget;`

#### class `UE::MLDeformer::SMLDeformerInputCurvesWidget`  
`class SMLDeformerInputCurvesWidget : public SCompoundWidget`  
_L94-131_
- inherits: `SCompoundWidget`
- L99 _private function_ `SLATE_BEGIN_ARGS(SMLDeformerInputCurvesWidget)`
- L105 _public prototype_ `void Construct(const FArguments& InArgs);`
- L106 _public prototype_ `void Refresh();`
- L107 _public prototype_ `void BindCommands(TSharedPtr<FUICommandList> CommandList);`
- L108 _public prototype_ `FText GetSectionTitle() const;`
- L109 _public prototype_ `TSharedPtr<SMLDeformerInputCurveListWidget> GetListWidget() const;`
- L110 _public prototype_ `TSharedPtr<SMLDeformerInputWidget> GetInputWidget() const;`
- L113 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L114 _private prototype_ `void RefreshList(bool bBroadCastPropertyChanged=true);`
- L115 _private prototype_ `bool BroadcastModelPropertyChanged(const FName PropertyName);`
- L117 _private prototype_ `void OnCopyInputCurves() const;`
- L118 _private prototype_ `void OnPasteInputCurves();`
- L120 _private prototype_ `void OnAddInputCurves();`
- L121 _private prototype_ `void OnDeleteInputCurves();`
- L122 _private prototype_ `void OnClearInputCurves();`
- L123 _private prototype_ `void OnAddAnimatedCurves();`
- L126 _private member_ `TSharedPtr<SMLDeformerInputWidget> InputWidget;`
- L127 _private member_ `TSharedPtr<SMLDeformerInputCurveListWidget> ListWidget;`
- L128 _private member_ `FMLDeformerEditorModel* EditorModel = nullptr;`
- L129 _private member_ `FString FilterText;`
- L130 _private member_ `FText SectionTitle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerInputWidget.h` (Public)


#### class `UE::MLDeformer::SMLDeformerInputWidget`  
`class SMLDeformerInputWidget : public SCompoundWidget`  
_L24-94_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerInputWidget)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void AddSection(TSharedPtr<SWidget> Widget, const FSectionInfo& SectionInfo);`
- L42 _public prototype_ `TSharedPtr<FUICommandList> GetBonesCommandList() const;`
- L43 _public prototype_ `TSharedPtr<FUICommandList> GetCurvesCommandList() const;`
- L48 _public prototype_ `virtual void Refresh();` — Refresh all sub-widget contents.
- L50 _public function_ `virtual void AddInputBonesMenuItems(FMenuBuilder& MenuBuilder)`
- L51 _public function_ `virtual void AddInputBonesPlusIconMenuItems(FMenuBuilder& MenuBuilder)`
- L52 _public function_ `virtual void AddInputCurvesMenuItems(FMenuBuilder& MenuBuilder)`
- L53 _public function_ `virtual void AddInputCurvesPlusIconMenuItems(FMenuBuilder& MenuBuilder)`
- L55 _public function_ `virtual void OnClearInputBones()`
- L56 _public function_ `virtual void OnAddInputBones(const TArray<FName>& Names)`
- L57 _public function_ `virtual void OnDeleteInputBones(const TArray<FName>& Names)`
- L58 _public function_ `virtual void OnAddAnimatedBones()`
- L60 _public function_ `virtual void OnClearInputCurves()`
- L61 _public function_ `virtual void OnAddInputCurves(const TArray<FName>& Names)`
- L62 _public function_ `virtual void OnDeleteInputCurves(const TArray<FName>& Names)`
- L63 _public function_ `virtual void OnAddAnimatedCurves()`
- L65 _public prototype_ `virtual void ClearSelectionForAllWidgetsExceptThis(TSharedPtr<SWidget> ExceptThisWidget);`
- L66 _public function_ `virtual void OnSelectInputBone(FName BoneName)`
- L67 _public function_ `virtual void OnSelectInputCurve(FName BoneName)`
- L69 _public prototype_ `virtual TSharedPtr<SWidget> GetExtraBonePickerWidget();`
- L72 _public prototype_ `static void RegisterCommands();` — Registers the commands that are being executed by the different widgets.
- L73 _public prototype_ `static void UnregisterCommands();`
- L75 _public prototype_ `static TSharedPtr<FJsonObject> GetJsonObject(const FString& JsonString);`
- L76 _public prototype_ `static bool ExtractStringFromJson(const TSharedPtr<FJsonObject>& JsonObject, const FString& Key, FString& OutString);`
- L77 _public prototype_ `static bool HasValidClipBoardData(const FString& DataTypeId, TSharedPtr<FJsonObject>& OutJsonObject);`
- L80 _protected prototype_ `void AddSectionSeparator();`
- L81 _protected prototype_ `void CreateBonesWidget();`
- L82 _protected prototype_ `void CreateCurvesWidget();`
- L84 _protected prototype_ `FReply ShowCurvesPlusIconContextMenu();`
- L85 _protected prototype_ `FReply ShowBonesPlusIconContextMenu();`
- L88 _protected member_ `TSharedPtr<SMLDeformerInputBonesWidget> InputBonesWidget;`
- L89 _protected member_ `TSharedPtr<SMLDeformerInputCurvesWidget> InputCurvesWidget;`
- L90 _protected member_ `TSharedPtr<FUICommandList> BonesCommandList;`
- L91 _protected member_ `TSharedPtr<FUICommandList> CurvesCommandList;`
- L92 _protected member_ `TSharedPtr<SVerticalBox> SectionVerticalBox;`
- L93 _protected member_ `FMLDeformerEditorModel* EditorModel = nullptr;`

#### struct `UE::MLDeformer::SMLDeformerInputWidget::FSectionInfo`  
`struct FSectionInfo`  
_L32-37_
- L34 _public member_ `TAttribute<FText> PlusButtonTooltip;`
- L35 _public member_ `TAttribute<FText> SectionTitle;`
- L36 _public member_ `FOnClicked PlusButtonPressed;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerMaskConfigDialog.h` (Public)


#### class `UE::MLDeformer::SMLDeformerMaskConfigDialog`  
`class SMLDeformerMaskConfigDialog : public SCustomDialog`  
_L26-56_
- inherits: `SCustomDialog`
- desc: The dialog that allows the user to choose a masking mode (Generated or using Skeletal Mesh Vertex Attribute). When using a vertex attribute, you can pick which attribute to use, or create a new one. Creating a new attribute will pop up the SMLDeformerNewVertexAttributeDialog.
- L30 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerMaskConfigDialog)`
- L31 _public prototype_ `SLATE_ARGUMENT(FMLDeformerMaskInfo, InitialMaskInfo) SLATE_EVENT(FOnSetNewVertexAttributeValues, OnSetNewVertexAttributeValues) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FMLDeformerEditorModel* InEditorModel);`
- L41 _public function_ `const FMLDeformerMaskInfo& GetMaskInfo() const` — This returns the mask info object how it was setup in the dialog. You should only use this when the user didn't cancel the dialog.
- L44 _private prototype_ `void UpdateAttributeNames();`
- L45 _private prototype_ `TSharedPtr<SWidget> CreateMeshAttributeModeWidget();`
- L46 _private prototype_ `TSharedPtr<FString> MaskModeEnumToString(EMLDeformerMaskingMode MaskMode) const;`
- L47 _private prototype_ `FReply OnCreateVertexAttributeClicked();`
- L50 _private member_ `TArray<FName> AttributeNames;`
- L51 _private member_ `TArray<TSharedPtr<FString>> MaskingModeNames;`
- L52 _private member_ `TSharedPtr<SComboBox<FName>> VertexAttributeComboWidget;`
- L53 _private member_ `FMLDeformerEditorModel* EditorModel = nullptr;`
- L54 _private member_ `FMLDeformerMaskInfo MaskInfo;`
- L55 _private member_ `FOnSetNewVertexAttributeValues OnSetNewVertexAttributeValues;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MLDeformer` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetNewVertexAttributeValues, TVertexAttributesRef<float>);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetNewVertexAttributeValues, TVertexAttributesRef<float>);` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/SMLDeformerNewVertexAttributeDialog.h` (Public)


#### class `UE::MLDeformer::SMLDeformerNewVertexAttributeDialog`  
`class SMLDeformerNewVertexAttributeDialog : public SWindow`  
_L35-115_
- inherits: `SWindow`
- desc: The dialog that asks the user to enter a vertex attribute name. On default the dialog creates the actual vertex attribute on the mesh as well, when the user pressed Create. You can disable this behavior using the bAutoCreateAttribute Slate argument. A default value for all vertices can be set as well using the DefaultValue attribute. Example usage: <code> TSharedPtr<SMLDeformerNewVertexAttributeDialog> Dialog = SNew(SMLDeformerNewVertexAttributeDialog, SkeletalMesh) .bAutoCreateAttribute(true) .DefaultValue(1.0f); if (Dialog.ShowModal() == SMLDeformerNewVertexAttributeDialog::EReturnCode::CreatePressed) { // Get the name of the attribute that was created. const FString& AttributeName = Dialog.GetAttributeName(); // ... } </code>
- L49 _public function_ `SLATE_BEGIN_ARGS(SMLDeformerNewVertexAttributeDialog) : _bAutoCreateAttribute(true) , _DefaultAttributeValue(0.0f)`
- L55 _public prototype_ `SLATE_ARGUMENT(bool, bAutoCreateAttribute) SLATE_ARGUMENT(float, DefaultAttributeValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs, USkeletalMesh* InSkeletalMesh);` — Should we automatically create the vertex attribute? The default is true.
- L65 _public prototype_ `EReturnCode ShowModal();` — Shows the dialog. The return code tells you whether the user canceled or pressed create.
- L71 _public function_ `const FString& GetAttributeName() const` — When the user pressed Create, which you can check using the return code of ShowModal, then this is the attribute name they entered. It is guaranteed that this attribute is one with a unique name if no other has been created in some other thread or so after the dialog has been created.
- L76 _private prototype_ `FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;` — Override the OnKeyDown to detect when the Escape key has been pressed, to cancel and close the dialog.
- L79 _private prototype_ `FReply OnCreateClicked();` — Perform actions when the create button has been clicked.
- L85 _private prototype_ `static bool HasVertexAttribute(const USkeletalMesh* SkeletalMesh, FName InAttributeName);` — Check whether a given skeletal mesh has a given vertex attribute already. @return Returns True when the attribute already exists, or false when not.
- L94 _private prototype_ `static bool CreateVertexAttribute(USkeletalMesh& SkeletalMesh, const FString& AttributeName, float DefaultValue = 0.0f);` — Create a float based vertex attribute with a given name, using a specific default value. When there already is an attribute with the specified name, then false is returned and nothing is changed. When the attribute name is unique, the new attribute will be created and all vertices will have the default value. This will create the attribute on LOD 0. @result Returns true on success, or false when failed. A fail can occur when there is already an attribute with the given name or when no Mesh Description can be found.
- L99 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — The Skeletal Mesh that we wish to create the attribute on.
- L102 _private member_ `EReturnCode ReturnCode = EReturnCode::Canceled;` — The return code, specifying whether the user pressed create or cancel.
- L105 _private member_ `FString AttributeName;` — The name of the attribute that the user entered.
- L108 _private member_ `TSharedPtr<SButton> CreateButton;` — The create button.
- L111 _private member_ `bool bAutoCreate = true;` — Should we automatically create the new attribute when the Create button has been pressed?
- L114 _private member_ `float DefaultAttributeValue = 0.0f;` — The default value of all vertices for this vertex attribute. Only used when bAutoCreate we end up creating the attribute.

#### enum `UE::MLDeformer::SMLDeformerNewVertexAttributeDialog::EReturnCode`  
`enum class EReturnCode : uint8`  
_L40-47_
- desc: The result of the dialog, which determines whether the user pressed the Create button, or if the user would like to cancel the creation.
- L43 _public enumerator_ `CreatePressed` — The user pressed the Create button.
- L46 _public enumerator_ `Canceled` — The user canceled the creation.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/AnimCustomization.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FAnimCustomization`  
`class FAnimCustomization final : public IPropertyTypeCustomization`  
_L19-36_
- inherits: `IPropertyTypeCustomization`
- desc: The property detail customization for a single animation input that can be enabled or disabled. This is a customization for the type FMLDeformerTrainingDataProcessorAnim.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _public prototype_ `EVisibility GetAnimErrorVisibility(const TSharedRef<IPropertyHandle> StructPropertyHandle, int32 AnimIndex) const;`
- L31 _private prototype_ `void RefreshProperties() const;`
- L32 _private prototype_ `static UMLDeformerTrainingDataProcessorSettings* FindSettings(const TSharedRef<IPropertyHandle>& StructPropertyHandle);`
- L35 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)
- L13 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/BoneGroupsListCustomization.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FBoneGroupsListCustomization`  
`class FBoneGroupsListCustomization : public IPropertyTypeCustomization`  
_L20-38_
- inherits: `IPropertyTypeCustomization`
- desc: The property detail customization for a list of bone groups. This is a customization for the type FMLDeformerTrainingDataProcessorBoneGroupsList.
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L33 _private prototype_ `TArray<FMLDeformerTrainingDataProcessorBoneGroup>* GetBoneGroups() const;`
- L36 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)
- L14 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/BoneListCustomization.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FBoneListCustomization`  
`class FBoneListCustomization : public IPropertyTypeCustomization`  
_L19-37_
- inherits: `IPropertyTypeCustomization`
- desc: The property detail customization for a list of bones. This is a detail customization for the type FMLDeformerTrainingDataProcessorBoneList.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L32 _private prototype_ `TArray<FName>* GetBoneNames() const;`
- L35 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)
- L13 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/SBoneGroupsListWidget.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FBoneGroupsListWidgetCommands`  
`class FBoneGroupsListWidgetCommands final : public TCommands<FBoneGroupsListWidgetCommands>`  
_L26-37_
- inherits: `TCommands<FBoneGroupsListWidgetCommands>`
- L29 _public prototype_ `FBoneGroupsListWidgetCommands();`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> CreateGroup;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelectedItems;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ClearGroups;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> AddBoneToGroup;`

#### class `UE::MLDeformer::TrainingDataProcessor::FBoneGroupTreeElement`  
`class FBoneGroupTreeElement final : public TSharedFromThis<FBoneGroupTreeElement>`  
_L40-56_
- inherits: `TSharedFromThis<FBoneGroupTreeElement>`
- L43 _public prototype_ `static TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FBoneGroupTreeElement>& InTreeElement, const TSharedPtr<SBoneGroupsTreeWidget>& InTreeWidget);`
- L47 _public function_ `bool IsGroup() const`
- L50 _public member_ `FString Name;`
- L51 _public member_ `TArray<TSharedPtr<FBoneGroupTreeElement>> Children;`
- L52 _public member_ `TWeakPtr<FBoneGroupTreeElement> ParentGroup;`
- L53 _public member_ `FSlateColor TextColor;`
- L54 _public member_ `int32 GroupIndex = INDEX_NONE;`
- L55 _public member_ `int32 GroupBoneIndex = INDEX_NONE;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneGroupTreeRowWidget`  
`class SBoneGroupTreeRowWidget final : public STableRow<TSharedPtr<FBoneGroupTreeElement>>`  
_L59-71_
- inherits: `STableRow<TSharedPtr<FBoneGroupTreeElement>>`
- L62 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FBoneGroupTreeElement>& InTreeElement, const TSharedPtr<SBoneGroupsTreeWidget>& InTreeView);`
- L66 _private prototype_ `FText GetName() const;`
- L69 _private member_ `TWeakPtr<FBoneGroupTreeElement> WeakTreeElement;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneGroupsTreeWidget`  
`class SBoneGroupsTreeWidget final : public STreeView<TSharedPtr<FBoneGroupTreeElement>>`  
_L74-108_
- inherits: `STreeView<TSharedPtr<FBoneGroupTreeElement>>`
- L79 _public function_ `SLATE_BEGIN_ARGS(SBoneGroupsTreeWidget)`
- L83 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SBoneGroupsListWidget>, BoneGroupsWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L87 _public prototype_ `void Refresh();`
- L88 _public prototype_ `int32 GetNumSelectedGroups() const;`
- L92 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L95 _private prototype_ `void AddElement(const TSharedPtr<FBoneGroupTreeElement>& Element, const TSharedPtr<FBoneGroupTreeElement>& ParentElement);`
- L96 _private prototype_ `const TArray<TSharedPtr<FBoneGroupTreeElement>>& GetRootElements() const;`
- L97 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FBoneGroupTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L98 _private prototype_ `TSharedPtr<SWidget> CreateContextMenuWidget() const;`
- L99 _private prototype_ `void UpdateTreeElements();`
- L100 _private prototype_ `void RefreshTree();`
- L102 _private prototype_ `static void HandleGetChildrenForTree(TSharedPtr<FBoneGroupTreeElement> InItem, TArray<TSharedPtr<FBoneGroupTreeElement>>& OutChildren);`
- L103 _private prototype_ `static TSharedPtr<SWidget> CreateContextWidget();`
- L106 _private member_ `TArray<TSharedPtr<FBoneGroupTreeElement>> RootElements;`
- L107 _private member_ `TWeakPtr<SBoneGroupsListWidget> BoneGroupsWidget;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneGroupsListWidget`  
`class SBoneGroupsListWidget final : public SCompoundWidget, public FEditorUndoClient`  
_L118-167_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A widget that shows a set of bone groups, and allows you to manage them by creating, removing and editing of groups. We see a bone group as a list of bone names. Multiple bone groups can exist. If you need only one list of bones then you can use the bone SBoneListWidget instead.
- L122 _private function_ `SLATE_BEGIN_ARGS(SBoneGroupsListWidget)`
- L134 _public prototype_ `void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook);`
- L138 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L139 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L142 _private prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InCommandList);`
- L143 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L144 _private prototype_ `void RefreshTree() const;`
- L145 _private prototype_ `FReply OnAddButtonClicked() const;`
- L146 _private prototype_ `FReply OnClearButtonClicked() const;`
- L148 _private prototype_ `TSharedPtr<SBoneGroupsTreeWidget> GetTreeWidget() const;`
- L149 _private prototype_ `TSharedPtr<FUICommandList> GetCommandList() const;`
- L150 _private prototype_ `TArray<FMLDeformerTrainingDataProcessorBoneGroup>* GetBoneGroupsValues() const;`
- L151 _private prototype_ `TWeakObjectPtr<USkeleton> GetSkeleton() const;`
- L152 _private prototype_ `const FString& GetFilterText() const;`
- L154 _private prototype_ `void OnCreateBoneGroup() const;`
- L155 _private prototype_ `void OnDeleteSelectedItems() const;`
- L156 _private prototype_ `void OnClearBoneGroups() const;`
- L157 _private prototype_ `void OnAddBoneToGroup() const;`
- L160 _private member_ `TSharedPtr<SBoneGroupsTreeWidget> TreeWidget;`
- L161 _private member_ `TWeakObjectPtr<USkeleton> Skeleton;`
- L162 _private member_ `TWeakObjectPtr<UObject> UndoObject;`
- L163 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L164 _private member_ `FBoneGroupsListWidgetGetBoneGroups GetBoneGroups;`
- L165 _private member_ `FString FilterText;`
- L166 _private member_ `FNotifyHook* NotifyHook = nullptr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MLDeformer` (scope `UE`)
- L21 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)
- L111 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FMLDeformerTrainingDataProcessorBoneGroup>*, FBoneGroupsListWidgetGetBoneGroups) class SBoneGroupsListWidget final : public SCompoundWidget, public FEditorUndoClient { friend class SBoneGroupsTreeWidget; SLATE_BEGIN_ARGS(SBoneGroupsListWidget) { } SLATE_ARGUMENT(TWeakObjectPtr<USkeleton>, Skeleton) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, UndoObject) SLATE_EVENT(FBoneGroupsListWidgetGetBoneGroups, GetBoneGroups) SLATE_END_ARGS() public: virtual ~SBoneGroupsListWidget() override; void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook); private:`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/SBoneListWidget.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FBoneListWidgetCommands`  
`class FBoneListWidgetCommands final : public TCommands<FBoneListWidgetCommands>`  
_L27-37_
- inherits: `TCommands<FBoneListWidgetCommands>`
- L30 _public prototype_ `FBoneListWidgetCommands();`
- L31 _public prototype_ `virtual void RegisterCommands() override;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> AddBones;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> RemoveBones;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ClearBones;`

#### class `UE::MLDeformer::TrainingDataProcessor::FBoneTreeWidgetElement`  
`class FBoneTreeWidgetElement final : public TSharedFromThis<FBoneTreeWidgetElement>`  
_L40-50_
- inherits: `TSharedFromThis<FBoneTreeWidgetElement>`
- L43 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FBoneTreeWidgetElement> InTreeElement, TSharedPtr<SBoneTreeWidget> InTreeWidget);`
- L47 _public member_ `FName Name;`
- L48 _public member_ `TArray<TSharedPtr<FBoneTreeWidgetElement>> Children;`
- L49 _public member_ `FSlateColor TextColor;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneTreeRowWidget`  
`class SBoneTreeRowWidget final : public STableRow<TSharedPtr<FBoneTreeWidgetElement>>`  
_L53-62_
- inherits: `STableRow<TSharedPtr<FBoneTreeWidgetElement>>`
- L56 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FBoneTreeWidgetElement>& InTreeElement, const TSharedPtr<SBoneTreeWidget>& InTreeView);`
- L60 _private member_ `TWeakPtr<FBoneTreeWidgetElement> TreeElement;`
- L61 _private prototype_ `FText GetName() const;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneTreeWidget`  
`class SBoneTreeWidget final : public STreeView<TSharedPtr<FBoneTreeWidgetElement>>`  
_L65-90_
- inherits: `STreeView<TSharedPtr<FBoneTreeWidgetElement>>`
- L67 _private function_ `SLATE_BEGIN_ARGS(SBoneTreeWidget)`
- L72 _public prototype_ `void Construct(const FArguments& InArgs);`
- L73 _public prototype_ `void RefreshElements(const TArray<FName>& BoneNames, const FReferenceSkeleton* RefSkeleton, const FString& FilterText);`
- L74 _public prototype_ `TArray<FName> ExtractAllElementNames() const;`
- L75 _public function_ `const TArray<TSharedPtr<FBoneTreeWidgetElement>>& GetRootElements() const`
- L78 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L80 _private prototype_ `static void RecursiveAddNames(const FBoneTreeWidgetElement& Element, TArray<FName>& OutNames);`
- L81 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FBoneTreeWidgetElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L82 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening() const;`
- L83 _private prototype_ `static TSharedPtr<FBoneTreeWidgetElement> FindParentElementForBone(FName BoneName, const FReferenceSkeleton& RefSkeleton, const TMap<FName, TSharedPtr<FBoneTreeWidgetElement>>& NameToElementMap);`
- L84 _private prototype_ `void RecursiveSortElements(const TSharedPtr<FBoneTreeWidgetElement>& Element);`
- L85 _private prototype_ `static void HandleGetChildrenForTree(TSharedPtr<FBoneTreeWidgetElement> InItem, TArray<TSharedPtr<FBoneTreeWidgetElement>>& OutChildren);`
- L88 _private member_ `TArray<TSharedPtr<FBoneTreeWidgetElement>> RootElements;`
- L89 _private member_ `TWeakPtr<SBoneListWidget> BoneListWidget;`

#### class `UE::MLDeformer::TrainingDataProcessor::SBoneListWidget`  
`class SBoneListWidget final : public SCompoundWidget, public FEditorUndoClient`  
_L103-150_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: The bone list widget, which displays a list of bones (in a hierarchy) and allows you to add and remove bones. It works directly on a TArray<FName> as source. You can use the GetBoneNames event to provide this array. You can use some of the delegates to listen for changes to the array.
- L105 _private function_ `SLATE_BEGIN_ARGS(SBoneListWidget)`
- L117 _public prototype_ `void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook);`
- L118 _public prototype_ `void Refresh() const;`
- L119 _public prototype_ `TSharedPtr<SBoneTreeWidget> GetTreeWidget() const;`
- L120 _public prototype_ `TSharedPtr<FUICommandList> GetCommandList() const;`
- L124 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient overrides.
- L125 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L128 _private prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InCommandList);`
- L129 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L130 _private prototype_ `void RefreshTree() const;`
- L131 _private prototype_ `FReply OnAddBonesButtonClicked() const;`
- L132 _private prototype_ `FReply OnClearBonesButtonClicked() const;`
- L133 _private prototype_ `void NotifyPropertyChanged() const;`
- L135 _private prototype_ `void OnAddBones() const;`
- L136 _private prototype_ `void OnRemoveBones() const;`
- L137 _private prototype_ `void OnClearBones() const;`
- L140 _private member_ `TSharedPtr<SBoneTreeWidget> TreeWidget;`
- L141 _private member_ `TWeakObjectPtr<USkeleton> Skeleton;`
- L142 _private member_ `TWeakObjectPtr<UObject> UndoObject;`
- L143 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L144 _private member_ `FNotifyHook* NotifyHook = nullptr;`
- L145 _private member_ `FString FilterText;`
- L146 _private member_ `FOnBoneListWidgetBonesAdded OnBonesAdded;`
- L147 _private member_ `FOnBoneListWidgetBonesRemoved OnBonesRemoved;`
- L148 _private member_ `FOnBoneListWidgetBonesCleared OnBonesCleared;`
- L149 _private member_ `FBoneListWidgetGetBoneNames GetBoneNames;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MLDeformer` (scope `UE`)
- L22 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)
- L93 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneListWidgetBonesAdded, const TArray<FName>& BoneNames) DECLARE_DELEGATE_OneParam(FOnBoneListWidgetBonesRemoved, const TArray<FName>& BoneNames) DECLARE_DELEGATE(FOnBoneListWidgetBonesCleared) DECLARE_DELEGATE_RetVal(TArray<FName>*, FBoneListWidgetGetBoneNames) class SBoneListWidget final : public SCompoundWidget, public FEditorUndoClient { SLATE_BEGIN_ARGS(SBoneListWidget) {} SLATE_ARGUMENT(TWeakObjectPtr<USkeleton>, Skeleton) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, UndoObject) SLATE_EVENT(FOnBoneListWidgetBonesAdded, OnBonesAdded) SLATE_EVENT(FOnBoneListWidgetBonesRemoved, OnBonesRemoved) SLATE_EVENT(FOnBoneListWidgetBonesCleared, OnBonesCleared) SLATE_EVENT(FBoneListWidgetGetBoneNames, GetBoneNames) SLATE_END_ARGS() public: virtual ~SBoneListWidget() override; void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook); void Refresh() const; TSharedPtr<SBoneTreeWidget> GetTreeWidget() const; TSharedPtr<FUICommandList> GetCommandList() const; private:`
- L94 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneListWidgetBonesRemoved, const TArray<FName>& BoneNames) DECLARE_DELEGATE(FOnBoneListWidgetBonesCleared) DECLARE_DELEGATE_RetVal(TArray<FName>*, FBoneListWidgetGetBoneNames) class SBoneListWidget final : public SCompoundWidget, public FEditorUndoClient { SLATE_BEGIN_ARGS(SBoneListWidget) {} SLATE_ARGUMENT(TWeakObjectPtr<USkeleton>, Skeleton) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, UndoObject) SLATE_EVENT(FOnBoneListWidgetBonesAdded, OnBonesAdded) SLATE_EVENT(FOnBoneListWidgetBonesRemoved, OnBonesRemoved) SLATE_EVENT(FOnBoneListWidgetBonesCleared, OnBonesCleared) SLATE_EVENT(FBoneListWidgetGetBoneNames, GetBoneNames) SLATE_END_ARGS() public: virtual ~SBoneListWidget() override; void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook); void Refresh() const; TSharedPtr<SBoneTreeWidget> GetTreeWidget() const; TSharedPtr<FUICommandList> GetCommandList() const; private:`
- L95 _delegate_ `DECLARE_DELEGATE(FOnBoneListWidgetBonesCleared) DECLARE_DELEGATE_RetVal(TArray<FName>*, FBoneListWidgetGetBoneNames) class SBoneListWidget final : public SCompoundWidget, public FEditorUndoClient { SLATE_BEGIN_ARGS(SBoneListWidget) {} SLATE_ARGUMENT(TWeakObjectPtr<USkeleton>, Skeleton) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, UndoObject) SLATE_EVENT(FOnBoneListWidgetBonesAdded, OnBonesAdded) SLATE_EVENT(FOnBoneListWidgetBonesRemoved, OnBonesRemoved) SLATE_EVENT(FOnBoneListWidgetBonesCleared, OnBonesCleared) SLATE_EVENT(FBoneListWidgetGetBoneNames, GetBoneNames) SLATE_END_ARGS() public: virtual ~SBoneListWidget() override; void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook); void Refresh() const; TSharedPtr<SBoneTreeWidget> GetTreeWidget() const; TSharedPtr<FUICommandList> GetCommandList() const; private:`
- L96 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FName>*, FBoneListWidgetGetBoneNames) class SBoneListWidget final : public SCompoundWidget, public FEditorUndoClient { SLATE_BEGIN_ARGS(SBoneListWidget) {} SLATE_ARGUMENT(TWeakObjectPtr<USkeleton>, Skeleton) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, UndoObject) SLATE_EVENT(FOnBoneListWidgetBonesAdded, OnBonesAdded) SLATE_EVENT(FOnBoneListWidgetBonesRemoved, OnBonesRemoved) SLATE_EVENT(FOnBoneListWidgetBonesCleared, OnBonesCleared) SLATE_EVENT(FBoneListWidgetGetBoneNames, GetBoneNames) SLATE_END_ARGS() public: virtual ~SBoneListWidget() override; void Construct(const FArguments& InArgs, FNotifyHook* InNotifyHook); void Refresh() const; TSharedPtr<SBoneTreeWidget> GetTreeWidget() const; TSharedPtr<FUICommandList> GetCommandList() const; private:`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/STrainingDataProcessorMainWidget.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::STrainingDataProcessorMainWidget`  
`class STrainingDataProcessorMainWidget final : public SCompoundWidget, public FEditorUndoClient, public FNotifyHook`  
_L23-58_
- inherits: `SCompoundWidget,FEditorUndoClient,FNotifyHook`
- desc: The main widget for the training data processor tool. This widget is basically what's inside the tab when this tool opens. It contains a detail view and generate button.
- L26 _public function_ `SLATE_BEGIN_ARGS(STrainingDataProcessorMainWidget)`
- L27 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<UMLDeformerModel>, Model) SLATE_END_ARGS() virtual ~STrainingDataProcessorMainWidget() override;`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L35 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L39 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L43 _private prototype_ `FReply OnGenerateButtonClicked() const;`
- L44 _private prototype_ `bool IsValidConfiguration() const;`
- L45 _private prototype_ `bool IsObjectOfInterest(UObject* Object) const;`
- L46 _private prototype_ `void OnAssetModified(UObject* Object) const;`
- L47 _private prototype_ `void Refresh() const;`
- L51 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view that shows the properties of our UMLDeformerTrainingDataProcessorSettings.
- L54 _private member_ `TObjectPtr<UMLDeformerModel> Model;` — A pointer to our model.
- L57 _private member_ `FDelegateHandle ObjectModifiedHandle;` — The delegate that handles when an object got modified (any object).

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)
- L16 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/TrainingDataProcessor.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FTrainingDataProcessor`  
`class FTrainingDataProcessor final`  
_L21-77_
- desc: The training data processor algorithm, which is executed when you press the Generate button. This will take a set of animation sequences as input, then find the 'best' N number of frames. After that it can remix the poses based on a set of bone groups. Basically the keyframes of the bones inside the groups get shuffled. So all the bones in the bone group will change together.
- L31 _public prototype_ `bool Execute(const UMLDeformerTrainingDataProcessorSettings& Settings, const USkeleton* Skeleton);` — Run the algorithm using specific settings. The output of this process is a UAnimSequence that is specified inside the Settings. @param Settings The settings to use during execution. This could come from the UMLDeformerModel::GetTrainingDataProcessorSettings() for example. @param Skeleton The skeleton to use when sampling animations and apply the transforms on in the output animation. @return Returns true if successful, or false if not. Errors will be logged in case false is returned.
- L34 _private prototype_ `void Clear();`
- L35 _private prototype_ `bool SampleFrames(const UMLDeformerTrainingDataProcessorSettings& Settings, const USkeleton& Skeleton);`
- L36 _private prototype_ `TArray<int32> FindBestFrameIndices(int32 MaxNumFrames, const FReferenceSkeleton& RefSkeleton) const;`
- L37 _private prototype_ `bool RemixPoses(const UMLDeformerTrainingDataProcessorSettings& Settings, const FReferenceSkeleton& RefSkeleton);`
- L38 _private prototype_ `bool SaveAnimationDataInAnimSequence(const UMLDeformerTrainingDataProcessorSettings& Settings, const FReferenceSkeleton& RefSkeleton, const TArray<int32>& FramesToInclude);`
- L39 _private prototype_ `int32 GetNumFrames() const;`
- L40 _private prototype_ `TArrayView<FTransform3f> GetFrameTransforms(int32 FrameIndex);`
- L41 _private prototype_ `TConstArrayView<FTransform3f> GetFrameTransforms(int32 FrameIndex) const;`
- L42 _private prototype_ `TConstArrayView<FTransform3f> GetFrameTransforms(const TArray<FTransform3f>& Transforms, int32 FrameIndex) const;`
- L43 _private prototype_ `TConstArrayView<FTransform3f> GetRefPoseTransforms() const;`
- L44 _private prototype_ `double CalculateMeanError(TConstArrayView<FTransform3f> PoseA, TConstArrayView<FTransform3f> PoseB) const;`
- L45 _private prototype_ `double CalculateMeanError(int32 PreviousPoseIndex, int32 CurrentPoseIndex) const;`
- L46 _private prototype_ `static FTransform3f GetRefPoseTransform(const FReferenceSkeleton& RefSkeleton, FName BoneName);`
- L76 _private member_ `FAnimFrameData AnimFrameData;` — The animation data as flat float arrays. @see FAnimFrameData for more information.

#### struct `UE::MLDeformer::TrainingDataProcessor::FTrainingDataProcessor::FAnimFrameData`  
`struct FAnimFrameData`  
_L57-73_
- desc: The animation data represented as buffers of vectors and quaternions. The size of the arrays are the number of bones in the reference skeleton, multiplied by the number of frames. So the layout for a two bone skeleton would be like this: [(Bone1, Bone2), (Bone1, Bone2), (Bone1, Bone2), ...] where each (Bone1, Bone2) represents a single frame. In case of positions and scales, the value for Bone1 and Bone2 would be a FVector. For the rotations it is an FQuat.
- L60 _public member_ `TArray<FTransform3f> Transforms;` — NumRefSkelBones * GetNumFrames().
- L63 _public member_ `TArray<FTransform3f> RefPoseTransforms;` — NumRefSkelBones FTransforms.
- L66 _public member_ `TArray<FName> BoneNames;` — Bone names in the bones list, that actually exist.
- L69 _public member_ `TArray<int32> BoneIndices;` — For each entry in the BoneNames array, this contains an index into the FReferenceSkeleton.
- L72 _public member_ `int32 NumRefSkelBones = 0;` — Number of bones in the reference skeleton.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)
- L13 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/TrainingDataProcessorSettingsDetailCustomization.h` (Public)


#### class `UE::MLDeformer::TrainingDataProcessor::FTrainingDataProcessorSettingsDetailCustomization`  
`class FTrainingDataProcessorSettingsDetailCustomization final : public IDetailCustomization`  
_L21-42_
- inherits: `IDetailCustomization`
- desc: The detail customization class for the UMLDeformerTrainingDataProcessorSettings class.
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _private prototype_ `EVisibility GetNoInputBonesWarningVisibility() const;`
- L30 _private prototype_ `EVisibility GetNoFramesWarningVisibility() const;`
- L31 _private prototype_ `EVisibility GetSkeletonMismatchErrorVisibility() const;`
- L33 _private prototype_ `FReply OnCreateNewButtonClicked() const;`
- L34 _private prototype_ `int32 GetTotalNumInputFrames() const;`
- L35 _private prototype_ `bool FilterAnimSequences(const FAssetData& AssetData) const;`
- L37 _private prototype_ `static void Refresh(IDetailLayoutBuilder* DetailBuilder);`
- L38 _private prototype_ `static FString FindDefaultAnimSequencePath(const UMLDeformerModel* Model);`
- L41 _private member_ `TWeakObjectPtr<UMLDeformerTrainingDataProcessorSettings> TrainingDataProcessorSettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORKEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)
- L16 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFrameworkEditor/Public/Tools/TrainingDataProcessor/TrainingDataProcessorTool.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MLDeformer` (scope `UE`)
- L10 _namespace_ `namespace TrainingDataProcessor` (scope `UE::MLDeformer`)
- L15 _prototype_ `void RegisterTool();` (scope `UE::MLDeformer::TrainingDataProcessor`) — Registers the Training Data Processor tool to the ML Deformer asset editor tools menu.
- L24 _prototype_ `USkeleton* FindSkeletonForProperty(const TSharedPtr<IPropertyHandle>& PropertyHandle);` (scope `UE::MLDeformer::TrainingDataProcessor`) — Find a skeleton for a given property. It does this by iterating over the outer objects of the property that's passed as parameter. It then checks the type of the object against a set of known types for which we know how to get the skeleton for. @param PropertyHandle The property handle to try to get a skeleton for. @return A pointer to the skeleton, or nullptr if not found.
