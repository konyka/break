# Plugins / AnimGenEditor

- module root: `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor`
- headers: 10; symbols: 283
- symbol kinds: class=16, enum=2, enumerator=19, function=14, macro=3, member=100, namespace=34, prototype=92, struct=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, BlueprintGraph, Blutility, ClassViewer, CoreUObject, DetailCustomizations, DrawDebugLibrary, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, Json, JsonUtilities, KismetWidgets, Learning, LearningTraining, LevelEditor, NNE, NNERuntimeBasicCpu, Projects, PropertyEditor, PythonScriptPlugin, RenderCore, SequencerWidgets, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: AnimDatabase, AnimDatabaseEditor, AnimGen, AnimGraph, Core, Learning, LearningTraining

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditor.h` (Public)


#### class `FAnimGenEditorModule`  
`class FAnimGenEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorAutoEncoderMode.h` (Public)


#### class `UE::AnimGen::Editor::FAutoEncoderMode`  
`class FAutoEncoderMode : public FEdMode`  
_L30-99_
- inherits: `FEdMode`
- L34 _public prototype_ `FAutoEncoderMode();`
- L35 _public prototype_ `~FAutoEncoderMode();`
- L37 _public member_ `const static FEditorModeID EditorModeId;`
- L39 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L40 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);`
- L45 _private member_ `const int32 MaxCharacterNum = 128;` — Maximum number of characters to draw in the scene
- L48 _private member_ `TWeakPtr<FAutoEncoderToolkit> WeakToolkit;` — Weak pointer to the auto encoder toolkit used for rendering
- L51 _private member_ `TArray<int32> ActiveRanges;` — Used to track when the selected ranges have changed and so when the timeline needs updating
- L54 _private member_ `TArray<int32> BoneParents;` — Temporary bone parents array
- L57 _private member_ `TArray<int32> CharacterSequenceIndices;` — Character Data
- L58 _private member_ `TArray<float> CharacterRangeTimes;`
- L59 _private member_ `TArray<int32> CharacterRangeStarts;`
- L60 _private member_ `TArray<int32> CharacterRangeLengths;`
- L63 _private member_ `int32 CurrentContentHash = 0;` — Trained Database content hash
- L65 _private member_ `bool bAutoEncoderValid = false;`
- L66 _private member_ `bool bFrameAttributesGenerated = false;`
- L67 _private member_ `TArray<FAnimDatabaseFrameAttribute> FrameAttributeObjects;`
- L68 _private member_ `TArray<EAnimDatabaseAttributeType> FrameAttributeTypes;`
- L69 _private member_ `TArray<FName> FrameAttributeNames;`
- L71 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> EncoderInference;`
- L72 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> DecoderInference;`
- L74 _private member_ `ULearningNeuralNetworkData* EncoderInferenceNetwork = nullptr;`
- L75 _private member_ `ULearningNeuralNetworkData* DecoderInferenceNetwork = nullptr;`
- L77 _private member_ `UE::AnimGen::Editor::FPerfCounter EncoderPerfCounter;`
- L78 _private member_ `UE::AnimGen::Editor::FPerfCounter DecoderPerfCounter;`
- L80 _private member_ `FAnimDatabasePoseState OriginalPoseState;`
- L81 _private member_ `FAnimDatabasePoseState ReconstructedPoseState;`
- L82 _private member_ `TLearningArray<1, FVector> ReconstructedRootLocations;`
- L83 _private member_ `TLearningArray<1, FQuat4f> ReconstructedRootRotations;`
- L85 _private member_ `TLearningArray<2, float> OriginalPoseVector;`
- L86 _private member_ `TLearningArray<2, float> EncodedVector;`
- L87 _private member_ `TLearningArray<2, float> ReconstructedPoseVector;`
- L90 _private member_ `TArray<TLearningArray<1, FVector>> RangeTrajectoryLocations;` — Trajectories for all currently queried ranges
- L91 _private member_ `TArray<TLearningArray<1, FQuat4f>> RangeTrajectoryRotations;`
- L94 _private member_ `TSharedPtr<Learning::FPCAEncoder> PCAEncoder;` — Encoded Space Visualization Data
- L95 _private member_ `TLearningArray<2, float> PCAEncodedPoses;`
- L96 _private member_ `TLearningArray<1, float> PCAEncoderMean;`
- L97 _private member_ `float PCAEncoderStd = 1.0f;`
- L98 _private member_ `TLearningArray<2, float> NormalizedEncodedVector;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace AnimGen` (scope `UE`)
- L26 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorAutoEncoderToolkit.h` (Public)


#### class `UAnimGenEditorAutoEncoderAssetDefinition`  
`class UAnimGenEditorAutoEncoderAssetDefinition : public UAssetDefinitionDefault`  
_L20-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L26 _public prototype_ `virtual FText GetAssetDisplayName() const override final;`
- L27 _public prototype_ `virtual FLinearColor GetAssetColor() const override final;`
- L28 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override final;`
- L29 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override final;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override final;`

#### class `UAnimGenAutoEncoderEditorFactory`  
`class UAnimGenAutoEncoderEditorFactory : public UFactory`  
_L35-52_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- desc: Asset factory for the AnimGen AutoEncoder class
- L40 _public prototype_ `UAnimGenAutoEncoderEditorFactory();`
- L43 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory overrides.
- L44 _public prototype_ `virtual FText GetDisplayName() const override;`
- L45 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L46 _public prototype_ `virtual FText GetToolTip() const override;`
- L47 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L48 _public prototype_ `virtual bool ConfigureProperties() override;`
- L49 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L50 _public prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`

#### class `UE::AnimGen::Editor::FAutoEncoderTrainingSettingsDetails`  
`class FAutoEncoderTrainingSettingsDetails : public IDetailCustomization`  
_L68-89_
- inherits: `IDetailCustomization`
- desc: Details customization used to render the appropriate UI for the UAnimGenAutoEncoderTrainingSettings object
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L74 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L77 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<AnimDatabase::Editor::FQueryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback to generate a single row of the list of ranges
- L80 _public prototype_ `void OnSelectionChanged(TSharedPtr<AnimDatabase::Editor::FQueryEntry> SelectedItem, ESelectInfo::Type SelectInfo);` — Callback for when the selection changes
- L85 _private member_ `TArray<TSharedPtr<AnimDatabase::Editor::FQueryEntry>> SelectedItems;` — Keep track of the selected items so we can see when they change
- L88 _private member_ `TSharedPtr<SListView<TSharedPtr<AnimDatabase::Editor::FQueryEntry>>> ListView;` — ListView for all the FQueryEntry items in the query

#### class `UE::AnimGen::Editor::FAutoEncoderDetails`  
`class FAutoEncoderDetails : public IDetailCustomization`  
_L92-99_
- inherits: `IDetailCustomization`
- desc: Details customization for the auto encoder
- L96 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L98 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `UE::AnimGen::Editor::FAutoEncoderToolkit`  
`class FAutoEncoderToolkit : public FAssetEditorToolkit, public FTickableEditorObject`  
_L101-158_
- inherits: `FAssetEditorToolkit,FTickableEditorObject`
- L105 _public prototype_ `void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UAnimGenAutoEncoder* InAutoEncoder);`
- L107 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L108 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L109 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L110 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L111 _public prototype_ `virtual FText GetToolkitName() const override;`
- L112 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L113 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L116 _public prototype_ `void ReconstructTimelineWidget();` — Reconstruct the timeline widget. This can be used for when new ranges are selected.
- L119 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Begin FTickableEditorObject interface
- L120 _public prototype_ `virtual TStatId GetStatId() const override;`
- L124 _public member_ `UAnimGenAutoEncoder* AutoEncoder = nullptr;` — We keep a pointer to the autoencoder asset. We assume this will out-live the editor toolkit.
- L127 _public member_ `TSharedPtr<AnimDatabase::Editor::FTimelineModel> TimelineModel;` — Model for the timeline Widget
- L130 _public member_ `TSharedPtr<AnimDatabase::Editor::FTimelineTracksModel> TracksModel;` — Model for the tracks Widget
- L133 _public member_ `TSharedPtr<FAutoEncoderTrainingModel> TrainingModel;` — AutoEncoder Training model
- L136 _public member_ `TSharedPtr<AnimDatabase::Editor::FPreviewScene> PreviewScene;` — Preview Scene for the viewport Widget
- L139 _public member_ `TSharedPtr<SWidget> ViewportWidget;` — Viewport Tab Widget
- L142 _public member_ `TSharedPtr<IDetailsView> EditingAssetWidget;` — Asset details Tab Widget
- L145 _public member_ `TSharedPtr<SWidget> PreviewSettingsWidget;` — Preview Settings Tab Widget
- L148 _public member_ `TSharedPtr<IDetailsView> ViewportSettingsWidget;` — Viewport Settings Tab Widget
- L151 _public member_ `TSharedPtr<SWidget> TimelineWidget;` — Timeline Tab Widget
- L154 _public member_ `TSharedPtr<IDetailsView> TrainingSettingsWidget;` — Training Settings Tab Widget
- L157 _public member_ `TSharedPtr<SWidget> TrainingWidget;` — Training Widget

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L54 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace AnimGen` (scope `UE`)
- L63 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorControllerMode.h` (Public)


#### class `UE::AnimGen::Editor::FControllerMode`  
`class FControllerMode : public FEdMode`  
_L29-78_
- inherits: `FEdMode`
- L33 _public prototype_ `FControllerMode();`
- L34 _public prototype_ `~FControllerMode();`
- L36 _public member_ `const static FEditorModeID EditorModeId;`
- L38 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L39 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);`
- L44 _private member_ `const int32 MaxCharacterNum = 128;` — Maximum number of characters to draw in the scene
- L46 _private member_ `int32 CharacterNum = 0;`
- L47 _private member_ `TArray<FLinearColor> CharacterColors;`
- L50 _private member_ `TWeakPtr<FControllerToolkit> WeakToolkit;` — Weak pointer to the controller toolkit used for rendering
- L52 _private member_ `TArray<int32> ActiveRanges;`
- L55 _private member_ `TArray<int32> CharacterSequenceIndices;` — Character Data
- L56 _private member_ `TArray<float> CharacterRangeTimes;`
- L57 _private member_ `TArray<int32> CharacterRangeStarts;`
- L58 _private member_ `TArray<int32> CharacterRangeLengths;`
- L59 _private member_ `TArray<int32> CharacterControlSetIndices;`
- L60 _private member_ `TArray<int32> CharacterControlSetEntries;`
- L61 _private member_ `TArray<int32> CharacterControlSetRanges;`
- L62 _private member_ `TArray<int32> CharacterControlSetFrames;`
- L65 _private member_ `TArray<TLearningArray<1, FVector>> RangeTrajectoryLocations;` — Trajectories for all currently queried ranges
- L66 _private member_ `TArray<TLearningArray<1, FQuat4f>> RangeTrajectoryRotations;`
- L69 _private member_ `TArray<FAnimDatabaseFrameAttributeEntry> FrameAttributeEntries;` — Current Frame Attribute Entries
- L72 _private member_ `TArray<FAnimDatabaseFrameAttribute> FrameAttributes;` — Associated Frame Attributes
- L75 _private member_ `int32 FrameAttributesDatabaseContentHash = 0;` — Frame Attributes database hash
- L77 _private member_ `FAnimDatabasePoseState PoseState;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Learning` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace AnimGen` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorControllerToolkit.h` (Public)


#### class `UAnimGenEditorControllerAssetDefinition`  
`class UAnimGenEditorControllerAssetDefinition : public UAssetDefinitionDefault`  
_L20-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L26 _public prototype_ `virtual FText GetAssetDisplayName() const override final;`
- L27 _public prototype_ `virtual FLinearColor GetAssetColor() const override final;`
- L28 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override final;`
- L29 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override final;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override final;`

#### class `UAnimGenControllerEditorFactory`  
`class UAnimGenControllerEditorFactory : public UFactory`  
_L35-52_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- desc: Asset factory for the AnimGen Controller class
- L40 _public prototype_ `UAnimGenControllerEditorFactory();`
- L43 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory overrides.
- L44 _public prototype_ `virtual FText GetDisplayName() const override;`
- L45 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L46 _public prototype_ `virtual FText GetToolTip() const override;`
- L47 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L48 _public prototype_ `virtual bool ConfigureProperties() override;`
- L49 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L50 _public prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`

#### class `UE::AnimGen::Editor::FControllerTrainingSettingsDetails`  
`class FControllerTrainingSettingsDetails : public IDetailCustomization`  
_L70-91_
- inherits: `IDetailCustomization`
- desc: Details customization used to render the appropriate UI for the UAnimGenControllerTrainingSettings object
- L74 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L76 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L79 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<AnimDatabase::Editor::FQueryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback to generate a single row of the list of ranges
- L82 _public prototype_ `void OnSelectionChanged(TSharedPtr<AnimDatabase::Editor::FQueryEntry> SelectedItem, ESelectInfo::Type SelectInfo);` — Callback for when the selection changes
- L87 _private member_ `TArray<TSharedPtr<AnimDatabase::Editor::FQueryEntry>> SelectedItems;` — Keep track of the selected items so we can see when they change
- L90 _private member_ `TSharedPtr<SListView<TSharedPtr<AnimDatabase::Editor::FQueryEntry>>> ListView;` — ListView for all the FQueryEntry items in the query

#### class `UE::AnimGen::Editor::FControllerDetails`  
`class FControllerDetails : public IDetailCustomization`  
_L94-101_
- inherits: `IDetailCustomization`
- desc: Details customization for the controller
- L98 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L100 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `UE::AnimGen::Editor::FControllerToolkit`  
`class FControllerToolkit : public FAssetEditorToolkit, public FTickableEditorObject`  
_L103-161_
- inherits: `FAssetEditorToolkit,FTickableEditorObject`
- L107 _public prototype_ `void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UAnimGenController* InController);`
- L109 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L110 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L111 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L112 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L113 _public prototype_ `virtual FText GetToolkitName() const override;`
- L114 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L115 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L116 _public prototype_ `void AddToolbarButton(FToolBarBuilder& Builder);`
- L119 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L120 _public prototype_ `virtual TStatId GetStatId() const override;`
- L124 _public member_ `UAnimGenController* Controller = nullptr;` — We keep a pointer to the controller asset. We assume this will out-live the editor toolkit.
- L127 _public member_ `TSharedPtr<AnimDatabase::Editor::FTimelineModel> TimelineModel;` — Model for the timeline Widget
- L130 _public member_ `TSharedPtr<AnimDatabase::Editor::FTimelineTracksModel> TracksModel;` — Model for the tracks Widget
- L133 _public member_ `TSharedPtr<FControllerTrainingModel> TrainingModel;` — Controller Training model
- L136 _public member_ `TSharedPtr<AnimDatabase::Editor::FPreviewScene> PreviewScene;` — Preview Scene for the viewport Widget
- L139 _public member_ `TSharedPtr<SControllerViewport> ViewportWidget;` — Viewport Tab Widget
- L142 _public member_ `TSharedPtr<IDetailsView> EditingAssetWidget;` — Asset details Tab Widget
- L145 _public member_ `TSharedPtr<SWidget> PreviewSettingsWidget;` — Preview Settings Tab Widget
- L148 _public member_ `TSharedPtr<IDetailsView> ViewportSettingsWidget;` — Viewport Settings Tab Widget
- L151 _public member_ `TSharedPtr<SWidget> TimelineWidget;` — Timeline Tab Widget
- L154 _public member_ `TSharedPtr<IDetailsView> TrainingSettingsWidget;` — Training Settings Tab Widget
- L157 _public member_ `TSharedPtr<SWidget> TrainingWidget;` — Training Widget
- L160 _public member_ `TSharedPtr<SControlObject> ControlObjectWidget;` — Control Object Widget

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L54 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace AnimGen` (scope `UE`)
- L63 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorPerfCounter.h` (Public)


#### struct `UE::AnimGen::Editor::FPerfCounter`  
`struct FPerfCounter`  
_L13-27_
- desc: Simple performance counter, adapted from FMLDeformerPerfCounter
- L15 _public prototype_ `FPerfCounter();`
- L17 _public prototype_ `void Reset();`
- L18 _public prototype_ `void Begin();`
- L19 _public prototype_ `void End();`
- L20 _public prototype_ `uint64 GetAverage() const;`
- L24 _private member_ `uint64 BeginCycles = 0;`
- L25 _private member_ `uint64 CycleIdx = 0;`
- L26 _private member_ `TStaticArray<uint64, 64> History;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGENEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AnimGen` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGenEditorTraining.h` (Public)


#### enum `UE::AnimGen::Editor::ETrainingStatus`  
`enum class ETrainingStatus : uint8`  
_L12-18_
- L14 _public enumerator_ `NotStarted = 0`
- L15 _public enumerator_ `Preparing = 1`
- L16 _public enumerator_ `Training = 2`
- L17 _public enumerator_ `Done = 3`

#### struct `UE::AnimGen::Editor::ITrainingModel`  
`struct ITrainingModel`  
_L20-37_
- L22 _public function_ `virtual bool IsEmpty() const`
- L24 _public function_ `virtual void StartTraining()`
- L25 _public function_ `virtual void StopTraining()`
- L26 _public function_ `virtual bool IsTraining() const`
- L28 _public function_ `virtual int32 GetProgressBarNum() const`
- L29 _public function_ `virtual FText GetProcessName(const int32 ProgressBarIdx) const`
- L30 _public function_ `virtual int32 GetIterationNum(const int32 ProgressBarIdx) const`
- L31 _public function_ `virtual int32 GetMaxIterationNum(const int32 ProgressBarIdx) const`
- L32 _public function_ `virtual ETrainingStatus GetTrainingStatus(const int32 ProgressBarIdx) const`
- L33 _public function_ `virtual float GetTrainingLoss(const int32 ProgressBarIdx) const`
- L34 _public function_ `virtual TOptional<FTimespan> GetEstimateTimeRemaining(const int32 ProgressBarIdx) const`
- L36 _public function_ `virtual FText GetErrorMessage() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AnimGen` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/AnimGraphNode_AnimGenController.h` (Public)


#### class `UAnimGraphNode_AnimGenController`  
`class UAnimGraphNode_AnimGenController : public UAnimGraphNode_Base`  
_L13-28_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_Base`
- L18 _private member_ `FAnimNode_AnimGenController Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L26 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;` — UAnimGraphNode_Base interface

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/SAnimGenEditorControlObject.h` (Public)


#### enum `UE::AnimGen::Editor::EControlObjectTreeElementType`  
`enum class EControlObjectTreeElementType : uint8`  
_L12-29_
- L14 _public enumerator_ `Invalid = 0`
- L15 _public enumerator_ `Null = 1`
- L16 _public enumerator_ `Continuous = 2`
- L17 _public enumerator_ `DiscreteExclusive = 3`
- L18 _public enumerator_ `DiscreteInclusive = 4`
- L19 _public enumerator_ `NamedDiscreteExclusive = 5`
- L20 _public enumerator_ `NamedDiscreteInclusive = 6`
- L21 _public enumerator_ `And = 7`
- L22 _public enumerator_ `OrExclusive = 8`
- L23 _public enumerator_ `OrInclusive = 9`
- L24 _public enumerator_ `Array = 10`
- L25 _public enumerator_ `Set = 11`
- L26 _public enumerator_ `Encoding = 12`
- L27 _public enumerator_ `Sparse = 13`
- L28 _public enumerator_ `NamedSparse = 14`

#### struct `UE::AnimGen::Editor::FControlObjectTreeElement`  
`struct FControlObjectTreeElement`  
_L31-42_
- L33 _public member_ `EControlObjectTreeElementType Type = EControlObjectTreeElementType::Invalid;`
- L34 _public member_ `FName Tag = NAME_None;`
- L35 _public member_ `FName Name = NAME_None;`
- L36 _public member_ `TArray<TSharedPtr<FControlObjectTreeElement>> Children;`
- L37 _public member_ `TArray<int32> DiscreteValues;`
- L38 _public member_ `TArray<float> ContinuousValues;`
- L39 _public member_ `TArray<FName> NamedValues;`
- L40 _public member_ `bool bIsExpanded = true;`
- L41 _public member_ `FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);`

#### class `UE::AnimGen::Editor::SControlObject`  
`class SControlObject : public SCompoundWidget`  
_L44-67_
- inherits: `SCompoundWidget`
- L48 _public function_ `SLATE_BEGIN_ARGS(SControlObject)`
- L49 _public prototype_ `SLATE_END_ARGS();`
- L51 _public prototype_ `void Construct(const FArguments& InArgs);`
- L53 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FControlObjectTreeElement> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L54 _public prototype_ `void OnGetChildren(TSharedPtr<FControlObjectTreeElement> InItem, TArray<TSharedPtr<FControlObjectTreeElement>>& OutChildren);`
- L55 _public prototype_ `void OnExpansionChanged(TSharedPtr<FControlObjectTreeElement> Item, bool bExpanded);`
- L57 _public prototype_ `void RefreshExpansion(const TArrayView<const TSharedPtr<FControlObjectTreeElement>> Items);`
- L58 _public prototype_ `void RefreshTreeElements();`
- L60 _public prototype_ `TArray<TSharedPtr<FControlObjectTreeElement>>& GetTreeElementsRef();`
- L64 _private member_ `TArray<TSharedPtr<FControlObjectTreeElement>> TreeElements;`
- L66 _private member_ `TSharedPtr<STreeView<TSharedPtr<FControlObjectTreeElement>>> TreeView;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGENEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AnimGen` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::AnimGen`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGenEditor/Public/SAnimGenEditorTraining.h` (Public)


#### class `UE::AnimGen::Editor::STraining`  
`class STraining : public SCompoundWidget`  
_L14-26_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(STraining)`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<ITrainingModel> InTrainingModel);`
- L25 _private member_ `TWeakPtr<ITrainingModel> TrainingModel;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGENEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AnimGen` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::AnimGen`)
