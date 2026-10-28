# Plugins / AnimDatabaseEditor

- module root: `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor`
- headers: 8; symbols: 213
- symbol kinds: class=10, function=3, macro=5, member=78, namespace=22, prototype=92, struct=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, BlueprintGraph, Blutility, ClassViewer, CoreUObject, DetailCustomizations, DrawDebugLibrary, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, Json, JsonUtilities, KismetWidgets, Learning, LevelEditor, Projects, PropertyEditor, RenderCore, SequencerWidgets, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: AnimDatabase, Core, Learning

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditor.h` (Public)


#### class `FAnimDatabaseEditorModule`  
`class FAnimDatabaseEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditorMode.h` (Public)


#### class `UE::AnimDatabase::Editor::FDatabaseMode`  
`class FDatabaseMode : public FEdMode`  
_L16-67_
- inherits: `FEdMode`
- desc: Simple Editor mode used for ticking the viewport of the Animation Database Editor
- L20 _public member_ `const static FEditorModeID EditorModeId;`
- L22 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L23 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L24 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L29 _private member_ `const int32 MaxCharacterNum = 128;` — Maximum number of characters to draw in the scene
- L32 _private member_ `TWeakPtr<FDatabaseToolkit> WeakToolkit;` — Weak pointer to the database toolkit used for rendering
- L35 _private member_ `TArray<int32> ActiveRanges;` — Used to track when the selected ranges have changed and so when the timeline needs updating
- L38 _private member_ `TArray<int32> BoneParents;` — Temporary bone parents array
- L41 _private member_ `TArray<int32> CharacterSequenceIndices;` — Character Data
- L42 _private member_ `TArray<float> CharacterRangeTimes;`
- L43 _private member_ `TArray<int32> CharacterRangeStarts;`
- L44 _private member_ `TArray<int32> CharacterRangeLengths;`
- L47 _private member_ `FAnimDatabasePoseState PoseState;` — Temporary pose state object used to store the sampled pose state for all characters
- L48 _private member_ `TLearningArray<1, FVector> AccumulatedRootLocations;`
- L49 _private member_ `TLearningArray<1, FQuat4f> AccumulatedRootRotations;`
- L52 _private member_ `TArray<TLearningArray<1, FVector>> RangeTrajectoryLocations;` — Trajectories for all currently queried ranges
- L53 _private member_ `TArray<TLearningArray<1, FQuat4f>> RangeTrajectoryRotations;`
- L56 _private member_ `TArray<FAnimDatabaseFrames> FramesObjects;` — Cached Frames Objects
- L57 _private member_ `TArray<FName> FramesNames;`
- L60 _private member_ `TArray<FAnimDatabaseFrameRanges> FrameRangesObjects;` — Cached Frame Ranges Objects
- L61 _private member_ `TArray<FName> FrameRangeNames;`
- L64 _private member_ `TArray<FAnimDatabaseFrameAttribute> FrameAttributeObjects;` — Cached Frame Attributes Objects
- L65 _private member_ `TArray<EAnimDatabaseAttributeType> FrameAttributeTypes;`
- L66 _private member_ `TArray<FName> FrameAttributeNames;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditorPreviewScene.h` (Public)


#### class `UE::AnimDatabase::Editor::FPreviewScene`  
`class FPreviewScene : public FAdvancedPreviewScene`  
_L16-57_
- inherits: `FAdvancedPreviewScene`
- desc: Simple re-usable preview scene that contains multiple characters each with a PoseableMeshComponent
- L20 _public prototype_ `FPreviewScene(ConstructionValues CVS);`
- L24 _public prototype_ `virtual void Tick(float InDeltaTime) override;` — Updates the preview scene
- L27 _public prototype_ `int32 GetCharacterNum() const;` — Gets the number of characters in the scene
- L30 _public prototype_ `int32 AddCharacter();` — Adds a new character to the scene. Returns the added character index
- L33 _public prototype_ `int32 RemoveCharacter();` — Removes a character from the scene
- L36 _public prototype_ `void SetCharacterVisibility(const int32 CharacterIdx, bool bVisibility);` — Adjusts the visibility for the given character
- L39 _public prototype_ `bool GetCharacterVisibility(const int32 CharacterIdx) const;` — Gets the current visibility of the given character
- L42 _public prototype_ `ACharacter* GetCharacterActor(const int32 CharacterIdx) const;` — Gets the actor associated with a given character
- L45 _public prototype_ `UPoseableMeshComponent* GetPoseableMeshComponent(const int32 CharacterIdx) const;` — Gets the poseable mesh component associated with a given character
- L50 _private member_ `TArray<ACharacter*> CharacterActors;` — Array of Character Actors
- L53 _private member_ `TArray<UCapsuleComponent*> CapsuleComponents;` — Array of Capsule Components which get added by default to each new character
- L56 _private member_ `TArray<UPoseableMeshComponent*> PoseableMeshComponents;` — Array of poseable mesh components

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ANIMDATABASEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditorTimeline.h` (Public)


#### struct `UE::AnimDatabase::Editor::FTimelineModel`  
`struct FTimelineModel`  
_L26-98_
- desc: Extremely basic data-model for the timeline widget. Stores information about various ranges, as well as playback state etc. Contains mainly just some basic getters and setters, as well as some functions that can be used within callbacks. For the UAnimDatabaseDatabase we usually want to work in frames (given we have a fixed-framerate for all animations) so this model stores everything in terms of frames where possible (rather than in terms of time).
- L28 _public prototype_ `FFrameRate GetTimelineFrameRate() const;`
- L29 _public prototype_ `FFrameTime GetTimelineFrameTime() const;`
- L30 _public prototype_ `FAnimatedRange GetTimelineViewRangeTimes() const;`
- L31 _public prototype_ `FAnimatedRange GetTimelineWorkingRangeTimes() const;`
- L32 _public prototype_ `TRange<FFrameNumber> GetTimelineViewRange() const;`
- L33 _public prototype_ `TRange<FFrameNumber> GetTimelineWorkingRange() const;`
- L34 _public prototype_ `TRange<FFrameNumber> GetTimelinePlaybackRangeFrames() const;`
- L35 _public prototype_ `float GetTimelinePlaybackRate() const;`
- L36 _public prototype_ `float GetTimelineCustomPlaybackRate() const;`
- L37 _public prototype_ `bool GetTimelineUseCustomPlaybackRate() const;`
- L38 _public prototype_ `bool GetTimelineSnapOnFrames() const;`
- L39 _public prototype_ `EPlaybackMode::Type GetTransportPlaybackMode() const;`
- L40 _public prototype_ `bool GetLooping() const;`
- L42 _public prototype_ `void SetTimelineFrameRate(const FFrameRate InFrameRate);`
- L43 _public prototype_ `void SetTimelineFrameTime(const FFrameTime InFrameTime);`
- L44 _public prototype_ `void SetTimelineViewRangeTimes(const FAnimatedRange InViewRange);`
- L45 _public prototype_ `void SetTimelineWorkingRangeTimes(const FAnimatedRange InWorkingRange);`
- L46 _public prototype_ `void SetTimelinePlaybackRate(const float InPlaybackRate);`
- L47 _public prototype_ `void SetTimelineCustomPlaybackRate(const float InCustomPlaybackRate);`
- L48 _public prototype_ `void SetTimelineViewRange(const TRange<FFrameNumber> InViewRange);`
- L49 _public prototype_ `void SetTimelineWorkingRange(const TRange<FFrameNumber> InWorkingRange);`
- L50 _public prototype_ `void SetTimelinePlaybackRange(const TRange<FFrameNumber> InPlaybackRange);`
- L51 _public prototype_ `void SetTimelineUseCustomPlaybackRate(const bool bInUseCustomPlaybackRate);`
- L52 _public prototype_ `void SetTimelineSnapOnFrames(const bool bInSnapOnFrames);`
- L53 _public prototype_ `void SetTransportPlaybackMode(const EPlaybackMode::Type InPlaybackMode);`
- L54 _public prototype_ `void SetLooping(const bool bLooping);`
- L56 _public prototype_ `void UpdateTimelineFrameTime(const float DeltaTime);`
- L58 _public prototype_ `void OnTransportStepForward();`
- L59 _public prototype_ `void OnTransportStepBackward();`
- L60 _public prototype_ `void OnTransportToStartFrame();`
- L61 _public prototype_ `void OnTransportToEndFrame();`
- L62 _public prototype_ `void OnTransportPlayPressed();`
- L67 _private member_ `TRange<FFrameNumber> ViewRange = TRange<FFrameNumber>(0, 0);` — Current Active View Range
- L70 _private member_ `TRange<FFrameNumber> WorkingRange = TRange<FFrameNumber>(0, 0);` — Current Active Working Range
- L73 _private member_ `TRange<FFrameNumber> PlaybackRange = TRange<FFrameNumber>(0, 0);` — Current Active Playback Range
- L76 _private member_ `FFrameTime FrameTime = FFrameTime();` — Current FrameTime for the scrubber
- L79 _private member_ `FFrameRate FrameRate = FFrameRate(60, 1);` — Current FrameRate - should match that of the database
- L82 _private member_ `EPlaybackMode::Type PlaybackMode = (EPlaybackMode::Type)0;` — Playback State
- L85 _private member_ `float PlaybackRate = 1.0f;` — Playback Rate
- L88 _private member_ `float CustomPlaybackRate = 1.0f;` — Custom Playback Rate when used
- L91 _private member_ `bool bUseCustomPlaybackRate = false;` — If to use CustomPlaybackRate or the standard PlaybackRate
- L94 _private member_ `bool bSnapOnFrames = false;` — If to snap the scrubbing to discrete frames
- L97 _private member_ `bool bLooping = false;` — If looping is enabled

#### struct `UE::AnimDatabase::Editor::FTimelineTrack`  
`struct FTimelineTrack`  
_L104-144_
- desc: This is a struct used for each row in the timeline tracks. Since this is a tree-view each row can correspond to something different so this has several members for the different types of row objects to display.
- L107 _public member_ `static constexpr float Height = 22.0f;` — Height of each row in the timeline tracks
- L110 _public member_ `TArray<TSharedRef<FTimelineTrack>> Children;` — Child objects
- L113 _public member_ `FLinearColor Color = FLinearColor::Black;` — Color identifier
- L116 _public member_ `FText DisplayName;` — Display name to use
- L119 _public member_ `float Offset = 0.0f;` — Track Vertical Offset
- L122 _public member_ `bool bIsRange : 1;` — Whether this track is a range
- L125 _public member_ `bool bIsExpanded : 1;` — Whether this track is expanded
- L128 _public member_ `int32 ViewOffset = 0;` — Timeline View Offset in frames
- L131 _public member_ `FString SequenceName;` — Sequence Name
- L134 _public member_ `FSoftObjectPath SequencePath;` — Sequence Path
- L137 _public member_ `FAnimDatabaseFrames FramesObject;` — Frames Object for this track
- L140 _public member_ `FAnimDatabaseFrameRanges FrameRangesObject;` — Frame Ranges Object for this track
- L143 _public member_ `FAnimDatabaseFrameAttribute FrameAttributeObject;` — Frame Attribute Object for this track

#### struct `UE::AnimDatabase::Editor::FTimelineTracksModel`  
`struct FTimelineTracksModel`  
_L150-174_
- desc: This is the model object for timeline tracks. In this case the only kinds of tracks allowed are FAnimDatabaseFrames and FAnimDatabaseFrameRanges so this is what this model is designed to display and handle.
- L153 _public prototype_ `void ResetTracks();` — Resets and removes all the existing tracks
- L156 _public prototype_ `void AddTrack( const UAnimSequence* Sequence, const FLinearColor& RangeColor, const TArrayView<const FName> FrameNames, const TArrayView<const FName> FrameRangeNames, const TArrayView<const FName> FrameAttributeNames, const TArrayView<const FAnimDatabaseFrames> Frames, const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 ViewOffset);` — Adds a new set of tracks for a single sequence for various frames, frame ranges, and frame attributes
- L168 _public prototype_ `TArray<TSharedRef<FTimelineTrack>>& GetRootTracks();` — Gets a reference to the root track objects
- L173 _private member_ `TArray<TSharedRef<FTimelineTrack>> RootTracks;` — Root track objects

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMDATABASEEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditorToolkit.h` (Public)


#### class `UAnimDatabaseEditorAssetDefinition`  
`class UAnimDatabaseEditorAssetDefinition : public UAssetDefinitionDefault`  
_L22-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset definition for the Animation Database class
- L28 _public prototype_ `virtual FText GetAssetDisplayName() const override final;`
- L29 _public prototype_ `virtual FLinearColor GetAssetColor() const override final;`
- L30 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override final;`
- L31 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override final;`
- L32 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override final;`

#### class `UAnimDatabaseEditorFactory`  
`class UAnimDatabaseEditorFactory : public UFactory`  
_L37-53_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- desc: Asset factory for the Animation Database class
- L42 _public prototype_ `UAnimDatabaseEditorFactory();`
- L45 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory overrides.
- L46 _public prototype_ `virtual FText GetDisplayName() const override;`
- L47 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L48 _public prototype_ `virtual FText GetToolTip() const override;`
- L49 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L50 _public prototype_ `virtual bool ConfigureProperties() override;`
- L51 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### class `UE::AnimDatabase::Editor::FQueryDetails`  
`class FQueryDetails : public IDetailCustomization`  
_L63-87_
- inherits: `IDetailCustomization`
- desc: Details customization used to render the appropriate UI for the UAnimDatabaseQuery object
- L67 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L69 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L72 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FQueryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback to generate a single row of the list of ranges
- L75 _public prototype_ `void OnSelectionChanged(TSharedPtr<FQueryEntry> SelectedItem, ESelectInfo::Type SelectInfo);` — Callback for when the selection changes
- L78 _public prototype_ `FReply OnKeyDown(UAnimDatabaseQuery* Query, const FKeyEvent& InKeyEvent);` — Callback for when keys are pressed
- L83 _private member_ `TArray<TSharedPtr<FQueryEntry>> SelectedItems;` — Keep track of the selected items so we can see when they change
- L86 _private member_ `TSharedPtr<SListView<TSharedPtr<FQueryEntry>>> ListView;` — ListView for all the FQueryEntry items in the query

#### class `UE::AnimDatabase::Editor::FDatabaseToolkit`  
`class FDatabaseToolkit : public FAssetEditorToolkit`  
_L90-139_
- inherits: `FAssetEditorToolkit`
- desc: Toolkit used for animation database assets
- L94 _public prototype_ `void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UAnimDatabase* InDatabase);`
- L96 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L97 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L98 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L99 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L100 _public prototype_ `virtual FText GetToolkitName() const override;`
- L101 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L102 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L105 _public prototype_ `void ReconstructTimelineWidget();` — Reconstruct the timeline widget. This can be used for when new ranges are selected.
- L108 _public member_ `UAnimDatabase* Database = nullptr;` — We keep a pointer to the database asset. We assume this will out-live the editor toolkit.
- L111 _public member_ `TSharedPtr<FTimelineModel> TimelineModel;` — Model for the timeline Widget
- L114 _public member_ `TSharedPtr<FTimelineTracksModel> TracksModel;` — Model for the tracks Widget
- L117 _public member_ `TSharedPtr<FPreviewScene> PreviewScene;` — Preview Scene for the viewport Widget
- L120 _public member_ `TSharedPtr<SWidget> ViewportWidget;` — Viewport Tab Widget
- L123 _public member_ `TSharedPtr<IDetailsView> EditingAssetWidget;` — Asset Details Panel Tab Widget
- L126 _public member_ `TSharedPtr<SWidget> PreviewSettingsWidget;` — Preview Settings Tab Widget
- L129 _public member_ `TSharedPtr<IDetailsView> ViewportSettingsWidget;` — Viewport Settings Tab Widget
- L132 _public member_ `TSharedPtr<SWidget> TimelineWidget;` — Timeline Tab Widget
- L135 _public member_ `TSharedPtr<IDetailsView> QueryWidget;` — Query Tab Widget
- L138 _public member_ `TSharedPtr<SWidget> AssetBrowserWidget;` — Asset Browser Tab Widget

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ESelectInfo`
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L55 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/AnimDatabaseEditorViewportClient.h` (Public)


#### class `UE::AnimDatabase::Editor::FViewportClient`  
`class FViewportClient : public FEditorViewportClient`  
_L18-61_
- inherits: `FEditorViewportClient`
- desc: Simple Viewport Client that can be used in the editor mode to get the preview scene and the editor toolkit
- L22 _public prototype_ `FViewportClient(const TWeakPtr<FPreviewScene> InPreviewScene, const TSharedRef<SEditorViewport>& InViewport, const TWeakPtr<FAssetEditorToolkit> InAssetEditorToolkit, const FEditorModeID ModeID);`
- L26 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L27 _public prototype_ `virtual void TrackingStopped() override;`
- L31 _public prototype_ `TWeakPtr<FPreviewScene> GetPreviewScene() const;` — Get the preview scene we are viewing
- L34 _public prototype_ `TWeakPtr<FAssetEditorToolkit> GetAssetEditorToolkit() const;` — Gets the Asset Editor Toolkit we are using
- L37 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — Custom Draw Function
- L40 _public prototype_ `void ClearWarningMessage();` — Clears the current warning message
- L43 _public prototype_ `void SetWarningMessage(const FText& InWarningMessage);` — Sets the current warning message
- L46 _public prototype_ `const TSharedPtr<FDebugDrawerCanvasBuffer>& GetOrMakeDebugDrawBuffer();` — Gets or makes a new DebugDrawCanvasBuffer for this viewport and returns a shared pointer to it
- L51 _private member_ `TWeakPtr<FPreviewScene> PreviewScenePtr;` — Preview scene we are viewing
- L54 _private member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkitPtr;` — Asset editor toolkit we are embedded in
- L57 _private member_ `FText WarningMessage;` — Optional warning message to display in viewport
- L60 _private member_ `TSharedPtr<FDebugDrawerCanvasBuffer> DebugDrawBuffer;` — Buffer for debug draw commands

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ANIMDATABASEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/SAnimDatabaseEditorTimeline.h` (Public)


#### class `UE::AnimDatabase::Editor::STimeline`  
`class STimeline : public SCompoundWidget`  
_L32-85_
- inherits: `SCompoundWidget`
- desc: This is a timeline widget used by the Animation Database and other editors. Lots of this code is copy-pasted from the MLDeformer timeline, which itself is based off the sequencer timeline. The main changes here are that the data model(s) (i.e. FTimelineModel and FTimelineTracksModel) are changed to be a bit more generic and not include anything application specific, and that the timeline is now working by default in terms of frames rather than time. This is more appropriate for the Animation Database and related editors since we use a fixed frame-rate and all frames and frame-ranges are using this same fixed frame-rate.
- L35 _public function_ `SLATE_BEGIN_ARGS(STimeline)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FTimelineModel> InModel, TWeakPtr<FTimelineTracksModel> InTracksModel);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The model for the anim timeline. @param InTracksModel The model for the anim timeline tracks.
- L49 _public prototype_ `void SetModel(const TWeakPtr<FTimelineModel>& InModel, const TWeakPtr<FTimelineTracksModel>& InTracksModel);` — Sets the model(s) to use with this timeline widget
- L52 _public prototype_ `bool GetGridMetrics(float PhysicalWidth, double& OutMajorInterval, int32& OutMinorDivisions) const;` — Compute a major grid interval and number of minor divisions to display.
- L55 _public prototype_ `TSharedPtr<ITimeSliderController> GetTimeSliderController() const;` — Get the time slider controller.
- L58 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Callback for mouse button up
- L63 _private member_ `TWeakPtr<FTimelineModel> Model;` — Timeline model.
- L66 _private member_ `TWeakPtr<FTimelineTracksModel> TracksModel;` — Tracks model.
- L69 _private member_ `TSharedPtr<STimelineTransportControls> TransportControls;` — The anim timeline transport controls, which contains the forward, backward and step actions.
- L72 _private member_ `TSharedPtr<FTimeSliderController> TimeSliderController;` — The controller used for the time slider
- L75 _private member_ `TSharedPtr<ITimeSlider> TopTimeSlider;` — The top time slider widget.
- L78 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — Numeric Type interface for converting between frame numbers and display formats.
- L81 _private member_ `float OutlinerFillCoefficient = 0.25f;` — Width ratio of the outliner
- L84 _private member_ `float TimelineFillCoefficient = 0.75f;` — Width ratio of the timeline

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMDATABASEEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabaseEditor/Public/SAnimDatabaseEditorViewport.h` (Public)


#### class `UE::AnimDatabase::Editor::SViewport`  
`class SViewport : public SEditorViewport`  
_L17-47_
- inherits: `SEditorViewport`
- desc: Basic Viewport Widget containing the Viewport Client as well as a weak pointer to the Preview Scene
- L21 _public function_ `SLATE_BEGIN_ARGS(SViewport)`
- L22 _public prototype_ `SLATE_END_ARGS();`
- L24 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FAssetEditorToolkit>& InAssetEditorToolkit, const TSharedRef<FPreviewScene>& InPreviewScene, const FEditorModeID InModeID);`
- L33 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L37 _protected member_ `TSharedPtr<FViewportClient> ViewportClient;` — Viewport client
- L40 _protected member_ `TWeakPtr<FPreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L43 _protected member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkitPtr;` — Asset editor toolkit we are embedded in
- L46 _protected member_ `FEditorModeID ModeID;` — Editor Mode

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ANIMDATABASEEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)
