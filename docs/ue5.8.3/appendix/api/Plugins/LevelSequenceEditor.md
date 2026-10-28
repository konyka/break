# Plugins / LevelSequenceEditor

- module root: `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor`
- headers: 30; symbols: 606
- symbol kinds: class=31, delegate=15, function=56, macro=9, member=153, namespace=3, prototype=327, struct=11, typedef=1
- DynamicallyLoadedModuleNames: AssetTools, PlacementMode
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, BlueprintGraph, CinematicCamera, ClassViewer, Constraints, ContentBrowser, Core, CoreUObject, CurveEditor, EditorFramework, EditorSubsystem, Engine, InputCore, Kismet, KismetCompiler, LevelEditor, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, Projects, PropertyEditor, SceneOutliner, Sequencer, SequencerCore, Slate, SlateCore, TimeManagement, ToolMenus, ToolWidgets, UniversalObjectLocator, UnrealEd, VREditor
- PrivateIncludePathModuleNames: AssetTools, DesktopPlatform, MovieSceneCaptureDialog, PlacementMode, Settings
- PublicDependencyModuleNames: SequencerScripting, SequencerScriptingEditor

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/CinematicLevelViewportToolbarContext.h` (Private)


#### class `UCinematicLevelViewportToolbarContext`  
`class UCinematicLevelViewportToolbarContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<SCinematicLevelViewport> CinematicLevelViewport;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/CinematicViewportCommands.h` (Private)


#### class `FCinematicViewportCommands`  
`class FCinematicViewportCommands : public TCommands<FCinematicViewportCommands>`  
_L15-59_
- inherits: `TCommands<FCinematicViewportCommands>`
- L19 _public function_ `FCinematicViewportCommands() : TCommands<FCinematicViewportCommands> ( "Cinematic Viewport", NSLOCTEXT("Contexts", "CinematicViewport", "Cinematic Viewport"), NAME_None, FAppStyle::GetAppStyleSetName()`
- L29 _public member_ `TSharedPtr<FUICommandInfo> Disabled;` — Disabled
- L32 _public member_ `TSharedPtr<FUICommandInfo> Grid2x2;` — Grid 2x2
- L35 _public member_ `TSharedPtr<FUICommandInfo> Grid3x3;` — Grid 3x3
- L38 _public member_ `TSharedPtr<FUICommandInfo> Crosshair;` — Crosshair
- L41 _public member_ `TSharedPtr<FUICommandInfo> Rabatment;` — Rabatment
- L44 _public member_ `TSharedPtr<FUICommandInfo> ActionSafe;` — ActionSafe
- L47 _public member_ `TSharedPtr<FUICommandInfo> TitleSafe;` — TitleSafe
- L50 _public member_ `TSharedPtr<FUICommandInfo> CustomSafe;` — CustomSafe
- L53 _public member_ `TSharedPtr<FUICommandInfo> Letterbox;` — Letterbox
- L58 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/CinematicViewportLayoutEntity.h` (Private)


#### class `FCinematicViewportLayoutEntity`  
`class FCinematicViewportLayoutEntity : public ILevelViewportLayoutEntity`  
_L13-52_
- inherits: `ILevelViewportLayoutEntity`
- L16 _public function_ `FCinematicViewportLayoutEntity(const FAssetEditorViewportConstructionArgs& Args, TSharedPtr<ILevelEditor> InLevelEditor) : Widget( SNew(SCinematicLevelViewport) .ParentLayout(Args.ParentLayout) .ParentLevelEditor(InLevelEditor) .LayoutName(Args.ConfigKey) )`
- L25 _public function_ `virtual TSharedRef<SWidget> AsWidget() const override`
- L26 _public function_ `virtual TSharedPtr<SLevelViewport> AsLevelViewport() const`
- L28 _public function_ `FName GetType() const`
- L34 _public function_ `FLevelEditorViewportClient& GetLevelViewportClient() const`
- L35 _public function_ `bool IsPlayInEditorViewportActive() const`
- L36 _public function_ `void RegisterGameViewportIfPIE()`
- L37 _public function_ `void SetKeyboardFocus()`
- L38 _public function_ `void OnLayoutDestroyed()`
- L45 _public function_ `void SaveConfig(const FString& ConfigString)`
- L46 _public function_ `void TakeHighResScreenShot() const`
- L51 _protected member_ `TSharedRef<SCinematicLevelViewport> Widget;` — This entity's widget

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/FilmOverlays.h` (Private)


#### class `SFilmOverlay`  
`class SFilmOverlay : public SCompoundWidget`  
_L15-55_
- inherits: `SCompoundWidget`
- desc: A widget that sits on top of a viewport, and draws custom content
- L18 _public function_ `SLATE_BEGIN_ARGS(SFilmOverlay)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(TArray<IFilmOverlay*>, FilmOverlays) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — User provided array of overlays to draw
- L29 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — Paint this widget
- L32 _public function_ `void SetFilmOverlays(const TAttribute<TArray<IFilmOverlay*>>& InFilmOverlays)` — Assigns film overlays to this film overlay widget
- L38 _public function_ `void SetPrimaryFilmOverlay(const FName InFilmOverlay)` — Sets the current primary film overlay
- L44 _public function_ `FName GetPrimaryFilmOverlay() const` — Get the current primary film overlay
- L51 _private member_ `TAttribute<TArray<IFilmOverlay*>> FilmOverlays;` — Attribute used once per frame to retrieve the film overlays to paint
- L54 _private member_ `FName PrimaryFilmOverlay;` — Currently selected primary film overlay

#### class `SFilmOverlayOptions`  
`class SFilmOverlayOptions : public SCompoundWidget`  
_L58-118_
- inherits: `SCompoundWidget`
- desc: A custom widget that comprises a combo box displaying all available overlay options
- L61 _public function_ `SLATE_BEGIN_ARGS(SFilmOverlayOptions) : _IsComboButton(true)`
- L65 _public prototype_ `SLATE_ATTRIBUTE(bool, IsComboButton) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SFilmOverlay> InFilmOverlay);` — Set this to false in order to directly show the menu content, instead of showing a button to summon it
- L72 _public prototype_ `TSharedPtr<SFilmOverlay> GetFilmOverlayWidget() const;` — Retrieve the actual overlay widget that this widget controls. Can be positioned in any other widget hierarchy.
- L75 _public prototype_ `void BindCommands(TSharedRef<FUICommandList>);` — Bind commands for the overlays
- L78 _public prototype_ `static void RegisterDefaultOverlays();` — Register the default primary and toggleable overlays into UFilmOverlayToolkit (idempotent).
- L83 _private prototype_ `TSharedRef<SWidget> GetMenuContent();` — Generate menu content for the combo button
- L86 _private prototype_ `TSharedRef<SWidget> ConstructPrimaryOverlaysMenu();` — Construct the part of the menu that defines the set of film overlays
- L89 _private prototype_ `TSharedRef<SWidget> ConstructToggleableOverlaysMenu();` — Construct the part of the menu that defines the set of toggleable overlays (currently just safe-frames)
- L94 _private prototype_ `const FSlateBrush* GetCurrentThumbnail() const;` — Get the thumbnail to be displayed on the combo box button
- L97 _private prototype_ `IFilmOverlay* GetPrimaryFilmOverlay() const;` — Get the primary film overlay ptr (may be nullptr)
- L100 _private prototype_ `TArray<IFilmOverlay*> GetActiveFilmOverlays() const;` — Get an array of all enabled film overlays
- L103 _private prototype_ `FReply SetPrimaryFilmOverlay(FName InName);` — Set the current primary overlay to the specified name
- L106 _private prototype_ `FLinearColor GetPrimaryColorTint() const;` — Get/Set the color tint override for the current primary overlay
- L107 _private prototype_ `void OnPrimaryColorTintChanged(const FLinearColor& Tint);`
- L110 _private prototype_ `FReply ToggleFilmOverlay(FName InName);` — Toggle the film overlay enabled or disabled
- L114 _private member_ `FLinearColor PrimaryColorTint;` — Color tint to apply to primary overlays
- L117 _private member_ `TWeakPtr<SFilmOverlay> OverlayWidget;` — The overlay widget we control - externally owned

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/SCinematicLevelViewport.h` (Private)


#### struct `FCinematicViewportClient`  
`struct FCinematicViewportClient : FLevelEditorViewportClient`  
_L29-34_
- inherits: `FLevelEditorViewportClient`
- desc: Overridden level viewport client for this viewport
- L31 _public prototype_ `FCinematicViewportClient();`
- L33 _public function_ `void SetViewportWidget(const TSharedPtr<SEditorViewport>& InViewportWidget)`

#### struct `FUIData`  
`struct FUIData`  
_L38-59_
- desc: struct containing UI data - populated once per frame
- L41 _public member_ `FText ShotName;` — The name of the current shot
- L43 _public member_ `FText CameraName;` — The name of the current camera
- L45 _public member_ `FText Lens;` — The name of the current shot's lens
- L47 _public member_ `FText Filmback;` — The name of the current shot's filmback
- L49 _public member_ `FText LocalPlaybackTime;` — The text that represents the current playback time relative to the currently evaluated sequence.
- L51 _public member_ `FText RootStartText;` — The text that represents the root start frame
- L53 _public member_ `FText RootEndText;` — The text that represents the root end frame
- L56 _public member_ `FFrameRate OuterResolution;` — The tick resolution of the root
- L58 _public member_ `FFrameRate OuterPlayRate;` — The play rate of the root

#### class `SCinematicLevelViewport`  
`class SCinematicLevelViewport : public SCompoundWidget`  
_L62-188_
- inherits: `SCompoundWidget`
- L66 _public function_ `SLATE_BEGIN_ARGS(SCinematicLevelViewport)`
- L69 _public function_ `SLATE_ARGUMENT(FName, LayoutName) SLATE_ARGUMENT(FName, RevertToLayoutName) SLATE_ARGUMENT(TSharedPtr<FAssetEditorViewportLayout>, ParentLayout) SLATE_ARGUMENT(TWeakPtr<ILevelEditor>, ParentLevelEditor) SLATE_ARGUMENT(TWeakPtr<SCinematicPreviewViewport>, PreviewViewport) SLATE_END_ARGS() TSharedPtr<FCinematicViewportClient> GetViewportClient() const` — The unique name of this viewport inside its parent layout
- L83 _public prototype_ `TSharedPtr<SLevelViewport> GetLevelViewport() const;`
- L86 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget
- L88 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L89 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L90 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L92 _public function_ `const TSharedPtr<SFilmOverlay>& GetOverlayWidget()`
- L97 _public function_ `TSharedPtr<FUICommandList> GetCommandList()`
- L101 _private prototype_ `void Setup(FLevelSequenceEditorToolkit& NewToolkit);` — Set up this viewport to operate on the specified toolkit
- L104 _private prototype_ `void CleanUp();` — Clean up this viewport after its toolkit has been closed
- L107 _private prototype_ `void OnEditorOpened(FLevelSequenceEditorToolkit& Toolkit);` — Called when a level sequence editor toolkit has been opened
- L110 _private prototype_ `void OnEditorClosed();` — Called when the level sequence editor toolkit we were observing has been closed
- L115 _private prototype_ `ISequencer* GetSequencer() const;` — Get the sequencer ptr from our current toolkit, if set
- L120 _private prototype_ `void CacheDesiredViewportSize(const FGeometry& AllottedGeometry);` — Cache the desired viewport size based on the filled, allotted geometry
- L123 _private prototype_ `FOptionalSize GetDesiredViewportWidth() const;` — Get the desired width and height of the viewport
- L124 _private prototype_ `FOptionalSize GetDesiredViewportHeight() const;`
- L126 _private prototype_ `int32 GetVisibleWidgetIndex() const;`
- L127 _private prototype_ `EVisibility GetControlsVisibility() const;`
- L131 _private prototype_ `TOptional<double> GetMinTime() const;`
- L133 _private prototype_ `TOptional<double> GetMaxTime() const;`
- L135 _private prototype_ `void OnTimeCommitted(double Value, ETextCommit::Type);`
- L137 _private prototype_ `void SetTime(double Value);`
- L139 _private prototype_ `double GetTime() const;`
- L141 _private prototype_ `float GetPlayTimeMinDesiredWidth() const;`
- L146 _private member_ `TSharedPtr<SCinematicPreviewViewport> ViewportWidget;` — Widget where the scene viewport is drawn in
- L149 _private member_ `TWeakPtr<FLevelSequenceEditorToolkit> CurrentToolkit;` — The toolkit we're currently editing
- L152 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commandlist used in the viewport (Maps commands to viewport specific actions)
- L155 _private member_ `TSharedPtr<SBox> TransportControlsContainer, TimeRangeContainer;` — Slot for transport controls
- L155 _private member_ `TSharedPtr<SBox> TransportControlsContainer, TimeRangeContainer;` — Slot for transport controls
- L158 _private member_ `TSharedPtr<SWidget> DecoratedTransportControls;` — Decorated transport controls
- L161 _private member_ `TSharedPtr<SCinematicTransportRange> TransportRange;` — Transport range widget
- L164 _private member_ `FUIData UIData;` — Cached UI data
- L167 _private member_ `FVector2D DesiredViewportSize;` — Cached desired size of the viewport
- L170 _private member_ `TSharedPtr<SWidget> ViewportControls;` — Viewport controls widget that sits just below, and matches the width, of the viewport
- L173 _private member_ `TWeakPtr<FAssetEditorViewportLayout> ParentLayout;` — Weak ptr to our parent layout
- L176 _private member_ `FName LayoutName;` — Name of the viewport in the parent layout
- L178 _private member_ `FName RevertToLayoutName;` — Name of the viewport layout we should revert to at the user's request
- L181 _private member_ `TSharedPtr<FTypeInterfaceProxy> TypeInterfaceProxy;` — The time spin box
- L184 _private member_ `TSharedPtr<FCinematicViewportClient> ViewportClient;` — The level editor viewport client for this viewport
- L187 _private member_ `TSharedPtr<SFilmOverlay> OverlayWidget;` — The overlay widget

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ETextCommit`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/CinematicViewport/SCinematicTransportRange.h` (Private)


#### class `SCinematicTransportRange`  
`class SCinematicTransportRange : public SCompoundWidget`  
_L14-50_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SCinematicTransportRange)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void SetSequencer(TWeakPtr<ISequencer> InSequencer);` — Assign a new sequencer to this transport
- L27 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L28 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L29 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L37 _private prototype_ `void SetTime(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L39 _private prototype_ `ISequencer* GetSequencer() const;`
- L41 _private prototype_ `void DrawKeys(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bParentEnabled, const TArrayView<const FFrameNumber>& Keys, const TArrayView<const FLinearColor>& KeyColors, bool& bOutPlayMarkerOnKey) const;`
- L44 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer that we're controlling
- L47 _private member_ `TUniquePtr<FSequencerKeyCollection> ActiveKeyCollection;` — The collection of keys for the currently active sequencer selection
- L49 _private member_ `bool bDraggingTime;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Factories/LevelSequenceFactoryNew.h` (Private)


#### class `ULevelSequenceFactoryNew`  
`class ULevelSequenceFactoryNew : public UFactory`  
_L12-23_
- reflection: `UCLASS(BlueprintType, hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for ULevelSequence objects.
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L22 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/LevelSequenceEditorCommands.h` (Private)


#### class `FLevelSequenceEditorCommands`  
`class FLevelSequenceEditorCommands : public TCommands<FLevelSequenceEditorCommands>`  
_L7-40_
- inherits: `TCommands<FLevelSequenceEditorCommands>`
- L13 _public prototype_ `FLevelSequenceEditorCommands();` — Default constructor.
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L18 _public member_ `TSharedPtr<FUICommandInfo> CreateNewLevelSequenceInLevel;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> CreateNewLevelSequenceWithShotsInLevel;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ToggleCinematicViewportCommand;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> SnapSectionsToTimelineUsingSourceTimecode;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> SyncSectionsUsingSourceTimecode;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> FixActorReferences;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddActorsToBinding;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> RemoveActorsFromBinding;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ReplaceBindingWithActors;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllBindings;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RemoveInvalidBindings;`
- L34 _public member_ `TSharedPtr< FUICommandInfo > ImportFBX;` — Imports animation from fbx.
- L37 _public member_ `TSharedPtr< FUICommandInfo > ExportFBX;` — Exports animation to fbx.
- L39 _public member_ `TSharedPtr<FUICommandInfo> BakeTransform;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/LevelSequenceEditorToolkit.h` (Private)


#### class `FLevelSequenceEditorToolkit`  
`class FLevelSequenceEditorToolkit : public ILevelSequenceEditorToolkit , public FGCObject`  
_L27-159_
- inherits: `ILevelSequenceEditorToolkit,FGCObject`
- desc: Implements an Editor toolkit for level sequences.
- L38 _public prototype_ `FLevelSequenceEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L41 _public prototype_ `virtual ~FLevelSequenceEditorToolkit();` — Virtual destructor
- L46 _public prototype_ `static void IterateOpenToolkits(TFunctionRef<bool(FLevelSequenceEditorToolkit&)> Iter);` — Iterate all open level sequence editor toolkits
- L49 _public prototype_ `DECLARE_EVENT_OneParam(FLevelSequenceEditorToolkit, FLevelSequenceEditorToolkitOpened, FLevelSequenceEditorToolkit&);` — Called when the tab manager is changed
- L50 _public prototype_ `static FLevelSequenceEditorToolkitOpened& OnOpened();`
- L53 _public prototype_ `DECLARE_EVENT(FLevelSequenceEditorToolkit, FLevelSequenceEditorToolkitClosed);` — Called when the tab manager is changed
- L54 _public function_ `FLevelSequenceEditorToolkitClosed& OnClosed()`
- L66 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULevelSequence* LevelSequence);` — Initialize this asset editor. @param Mode Asset editing mode for this editor (standalone or world-centric). @param InitToolkitHost When Mode is WorldCentric, this is the level editor instance to spawn this editor within. @param LevelSequence The animation to edit. @param TrackEditorDelegates Delegates to call to create auto-key handlers for this sequencer.
- L73 _public function_ `virtual TSharedPtr<ISequencer> GetSequencer() const override` — Get the sequencer object being edited in this tool kit. @return Sequencer object.
- L82 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L86 _public function_ `virtual FString GetReferencerName() const override`
- L91 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L92 _public prototype_ `virtual void OnClose() override;`
- L93 _public prototype_ `virtual bool CanFindInContentBrowser() const override;`
- L99 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L100 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L101 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L102 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L103 _public prototype_ `virtual FText GetTabSuffix() const override;`
- L104 _public prototype_ `virtual void BringToolkitToFront() override;`
- L109 _protected prototype_ `void AddDefaultTracksForActor(AActor& Actor, const FGuid Binding);` — Add default movie scene tracks for the given actor.
- L112 _protected prototype_ `void AddShot(UMovieSceneCinematicShotTrack* ShotTrack, const FString& ShotAssetName, const FString& ShotPackagePath, FFrameNumber ShotStartTime, FFrameNumber ShotEndTime, UObject* AssetToDuplicate, const FString& FirstShotAssetName);` — Add a shot to a sequence
- L115 _protected prototype_ `void OnSequencerReceivedFocus();` — Called whenever sequencer has received focus
- L118 _protected prototype_ `void OnInitToolMenuContext(FToolMenuContext& MenuContext);` — Called whenever sequencer in initializing tool menu context
- L122 _private prototype_ `void ExtendSequencerToolbar(FName InToolMenuName);`
- L125 _private prototype_ `void HandleMapChanged(UWorld* NewWorld, EMapChangeType MapChangeType);` — Callback for map changes.
- L128 _private prototype_ `void HandleLevelSequenceWithShotsCreated(UObject* LevelSequenceWithShotsAsset);` — Callback for when a sequence with shots is created.
- L131 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args);` — Callback for spawning tabs.
- L134 _private prototype_ `void HandleActorAddedToSequencer(AActor* Actor, const FGuid Binding);` — Callback for actor added to sequencer.
- L137 _private prototype_ `void HandleVREditorModeExit();` — Callback for VR Editor mode exiting
- L142 _private member_ `TObjectPtr<ULevelSequence> LevelSequence;` — Level sequence for our edit operation.
- L145 _private member_ `FLevelSequenceEditorToolkitClosed OnClosedEvent;` — Event that is cast when this toolkit is closed
- L148 _private member_ `TSharedPtr<ISequencer> Sequencer;` — The sequencer used by this editor.
- L151 _private member_ `TSharedRef<ISlateStyle> Style;` — Pointer to the style set to use for toolkits.
- L154 _private member_ `TSharedPtr<FLevelSequencePlaybackContext> PlaybackContext;` — Instance of a class used for managing the playback context for a level sequence.
- L158 _private member_ `static const FName SequencerMainTabId;` — The tab ids for all the tabs used

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_EVENT_OneParam(FLevelSequenceEditorToolkit, FLevelSequenceEditorToolkitOpened, FLevelSequenceEditorToolkit&);` — Called when the tab manager is changed
- L53 _delegate_ `DECLARE_EVENT(FLevelSequenceEditorToolkit, FLevelSequenceEditorToolkitClosed);` — Called when the tab manager is changed

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/LevelSequenceCustomization.h` (Private)


#### class `UE::Sequencer::FLevelSequenceCustomization`  
`class FLevelSequenceCustomization : public ISequencerCustomization`  
_L18-77_
- inherits: `ISequencerCustomization`
- desc: The sequencer customization for level sequences.
- L21 _public prototype_ `void AddCustomization(TUniquePtr<ISequencerCustomization> NewCustomization);`
- L26 _protected prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L27 _protected prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L32 _private prototype_ `void BindCommands();` — Map the UI commands used by the extensions in this customization
- L35 _private prototype_ `TSharedPtr<FExtender> CreateActionsMenuExtender();` — Create the menu extenders that will be added to the registered customization builder
- L36 _private prototype_ `TSharedPtr<FExtender> CreateObjectBindingContextMenuExtender(FViewModelPtr InViewModel);`
- L37 _private prototype_ `TSharedPtr<FExtender> CreateObjectBindingSidebarMenuExtender(FViewModelPtr InViewModel);`
- L40 _private prototype_ `void ImportFBX();` — Action Menu Extensions
- L41 _private prototype_ `void ExportFBX();`
- L42 _private prototype_ `void SnapSectionsToTimelineUsingSourceTimecode();`
- L43 _private prototype_ `void SyncSectionsUsingSourceTimecode();`
- L44 _private prototype_ `void FixActorReferences();`
- L45 _private prototype_ `void BakeTransform();`
- L47 _private prototype_ `bool DoesMovieSceneHaveEnoughSectionsSelected(int32 MinSectionCount);`
- L50 _private prototype_ `void ExtendObjectBindingContextMenu(FMenuBuilder& MenuBuilder, TSharedPtr<FObjectBindingModel> ObjectBindingModel);` — Object Binding Context Menu Extensions
- L51 _private prototype_ `void AddAssignActorSubMenu(FMenuBuilder& MenuBuilder);`
- L52 _private prototype_ `void AddBindingPropertiesSubMenu(FMenuBuilder& MenuBuilder);`
- L53 _private prototype_ `TSharedRef<SWidget> BuildActorPicker();`
- L55 _private prototype_ `void AddActorsToBinding();`
- L56 _private prototype_ `void ReplaceBindingWithActors();`
- L57 _private prototype_ `void RemoveActorsFromBinding();`
- L58 _private prototype_ `void RemoveAllBindings();`
- L59 _private prototype_ `void RemoveInvalidBindings();`
- L61 _private prototype_ `FMovieSceneBindingProxy GetSelectedBindingProxy();`
- L62 _private prototype_ `TArray<AActor*> GetSelectedActors();`
- L64 _private prototype_ `bool AreAnyActorsSelected();`
- L65 _private prototype_ `bool IsSelectedBindingRootPossessable();`
- L68 _private prototype_ `void ExtendObjectBindingSidebarMenu(FMenuBuilder& MenuBuilder, TSharedPtr<FObjectBindingModel> ObjectBindingModel);` — Object Binding Sidebar Menu Extensions
- L72 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L74 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L76 _private member_ `TArray<TUniquePtr<ISequencerCustomization>> AdditionalCustomizations;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/LevelSequenceEditorActorBinding.h` (Private)


#### class `FLevelSequenceEditorActorBinding`  
`class FLevelSequenceEditorActorBinding : public ISequencerEditorObjectBinding`  
_L11-32_
- inherits: `ISequencerEditorObjectBinding`
- L15 _public prototype_ `FLevelSequenceEditorActorBinding(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerEditorObjectBinding interface
- L19 _public prototype_ `virtual void BuildSequencerAddMenu(FMenuBuilder& MenuBuilder) override;`
- L20 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L25 _private prototype_ `void AddPossessActorMenuExtensions(FMenuBuilder& MenuBuilder);` — Menu extension callback for the add menu
- L28 _private prototype_ `void AddActorsToSequencer(AActor*const* InActors, int32 NumActors);` — Add the specified actors to the sequencer
- L31 _private member_ `TWeakPtr<ISequencer> Sequencer;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/LevelSequenceEditorActorSpawner.h` (Private)


#### class `FLevelSequenceEditorActorSpawner`  
`class FLevelSequenceEditorActorSpawner : public FLevelSequenceActorSpawner`  
_L9-22_
- inherits: `FLevelSequenceActorSpawner`
- L13 _public prototype_ `static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();`
- L16 _public function_ `virtual bool IsEditor() const override` — IMovieSceneObjectSpawner interface
- L18 _public prototype_ `virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;`
- L19 _public prototype_ `virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;`
- L20 _public prototype_ `virtual bool CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const override;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/LevelSequenceEditorHelpers.h` (Private)


#### class `LevelSequenceEditorHelpers`  
`class LevelSequenceEditorHelpers`  
_L9-18_
- L14 _public prototype_ `static void OpenLevelSequenceWithShotsDialog(const TSharedRef<FTabManager>& TabManager);` — Open dialog for creating a level sequence with shots
- L17 _public prototype_ `static UObject* CreateLevelSequenceAsset(const FString& AssetName, const FString& PackagePath, UObject* AssetToDuplicate = nullptr);` — Create a level sequence asset given an asset name and package path

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/LevelSequenceEditorMenuContext.h` (Private)


#### class `ULevelSequenceEditorMenuContext`  
`class ULevelSequenceEditorMenuContext : public UObject`  
_L11-16_
- reflection: `UCLASS()`
- inherits: `UObject`
- L15 _public member_ `TWeakPtr<FLevelSequenceEditorToolkit> Toolkit;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Misc/MovieSceneSequenceEditor_LevelSequence.h` (Private)


#### struct `FMovieSceneSequenceEditor_LevelSequence`  
`struct FMovieSceneSequenceEditor_LevelSequence : FMovieSceneSequenceEditor`  
_L15-60_
- inherits: `FMovieSceneSequenceEditor`
- L17 _public function_ `virtual bool CanCreateEvents(UMovieSceneSequence* InSequence) const`
- L22 _public function_ `virtual bool CanCreateDirectorBlueprint(UMovieSceneSequence* Sequence) const override`
- L38 _public function_ `virtual UBlueprint* GetBlueprintForSequence(UMovieSceneSequence* InSequence) const override`
- L44 _public function_ `virtual UBlueprint* CreateBlueprintForSequence(UMovieSceneSequence* InSequence) const override`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Styles/LevelSequenceEditorStyle.h` (Private)


#### class `FLevelSequenceEditorStyle`  
`class FLevelSequenceEditorStyle final : public FSlateStyleSet`  
_L18-142_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the messaging debugger UI.
- L24 _public function_ `FLevelSequenceEditorStyle() : FSlateStyleSet("LevelSequenceEditorStyle")` — Default constructor.
- L126 _public function_ `virtual ~FLevelSequenceEditorStyle()` — Virtual destructor.
- L131 _public function_ `static TSharedRef<FLevelSequenceEditorStyle> Get()`
- L141 _private member_ `static TSharedPtr<FLevelSequenceEditorStyle> Singleton;`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Widgets/SScoreRating.h` (Private)


#### class `SScoreRating`  
`class SScoreRating : public SCompoundWidget`  
_L14-67_
- inherits: `SCompoundWidget`
- desc: Widget for viewing and setting a score rating.
- L19 _public function_ `SLATE_BEGIN_ARGS(SScoreRating) : _MaxScore(3) , _ElementIcon(FAppStyle::GetBrush("Icons.Star")) , _OnScoreChanged() , _Score(0)`
- L27 _public prototype_ `SLATE_ARGUMENT( int32, MaxScore ) SLATE_ATTRIBUTE( const FSlateBrush*, ElementIcon ) SLATE_EVENT( FOnScoreChanged, OnScoreChanged) SLATE_ATTRIBUTE( int32, Score ) SLATE_END_ARGS() SScoreRating();` — The max score shown by the widget
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _private function_ `inline void SetHoverIndex(int32 Index)` — Set the current hover index
- L48 _private prototype_ `void NotifyScoreChanged(int32 NewScore);` — Notify the score has changed with the new score
- L51 _private member_ `TSharedPtr<SHorizontalBox> LayoutBox;` — The overall layout widget
- L54 _private member_ `int32 MaxScore = 3;` — Max possible score to display
- L57 _private member_ `FOnScoreChanged OnScoreChanged;` — Event triggered when the score is changed.
- L60 _private member_ `int32 HoverIndex = 0;` — Current score rating index that the mouse is hovering over
- L63 _private member_ `TSlateAttribute<const FSlateBrush*> ElementIconAttribute;` — The slate brush to use to draw the element icons.
- L66 _private member_ `TSlateAttribute<int32> ScoreAttribute;` — The current score

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnScoreChanged, int32 ) class SScoreRating : public SCompoundWidget { SLATE_DECLARE_WIDGET(SScoreRating, SCompoundWidget) public: SLATE_BEGIN_ARGS(SScoreRating) : _MaxScore(3) , _ElementIcon(FAppStyle::GetBrush("Icons.Star")) , _OnScoreChanged() , _Score(0) {} SLATE_ARGUMENT( int32, MaxScore ) SLATE_ATTRIBUTE( const FSlateBrush*, ElementIcon ) SLATE_EVENT( FOnScoreChanged, OnScoreChanged) SLATE_ATTRIBUTE( int32, Score ) SLATE_END_ARGS() SScoreRating(); void Construct(const FArguments& InArgs); private: inline void SetHoverIndex(int32 Index) { HoverIndex = Index; } void NotifyScoreChanged(int32 NewScore);` — Delegate that is executed when the score is changed

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Private/Widgets/SScoreRatingElement.h` (Private)


#### class `SScoreRatingElement`  
`class SScoreRatingElement : public SCompoundWidget`  
_L20-74_
- inherits: `SCompoundWidget`
- desc: Specialized widget for a score value to expose when mouse hover events occur. Ideally this would be contained entirely in SScoreRating however the need to get the hover events mean we require an extra wrapper class.
- L25 _public function_ `SLATE_BEGIN_ARGS(SScoreRatingElement) : _OnHoverStarted() , _OnHoverFinished() , _OnCheckStateChanged() , _Icon(FAppStyle::GetBrush("Icons.Star")) , _IsChecked(false)`
- L35 _public prototype_ `SLATE_EVENT( FOnScoreRatingElementHoverEvent, OnHoverStarted ) SLATE_EVENT( FOnScoreRatingElementHoverEvent, OnHoverFinished ) SLATE_EVENT( FOnBinaryCheckStateChanged, OnCheckStateChanged ) SLATE_ATTRIBUTE( const FSlateBrush*, Icon ) SLATE_ATTRIBUTE( bool, IsChecked ) SLATE_END_ARGS() SScoreRatingElement();` — Called when a hover event starts
- L53 _public prototype_ `void Construct(const FArguments& InArgs);`
- L56 _public prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget Interface
- L57 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L61 _private member_ `FOnScoreRatingElementHoverEvent OnHoverStarted;` — Delegate fired when a hover event starts
- L64 _private member_ `FOnScoreRatingElementHoverEvent OnHoverFinished;` — Delegate fired when a hover event finishes
- L67 _private member_ `FOnBinaryCheckStateChanged OnCheckStateChanged;` — Delegate fired when a state change event occurs
- L70 _private member_ `TSlateAttribute<const FSlateBrush*> IconAttribute;` — The slate brush to use to draw the icon.
- L73 _private member_ `TSlateAttribute<bool> IsCheckedAttribute;` — Are we checked

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE(FOnScoreRatingElementHoverEvent);` — Delegate that is executed when a Score Rating Element hover event happens
- L10 _prototype_ `DECLARE_DELEGATE(FOnScoreRatingElementHoverEvent);` — Delegate that is executed when a Score Rating Element hover event happens
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBinaryCheckStateChanged, bool);` — Delegate that is executed when a binary check state change occurs, either to/from true/false
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBinaryCheckStateChanged, bool);` — Delegate that is executed when a binary check state change occurs, either to/from true/false

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/AssetTools/AssetDefinition_LevelSequence.h` (Public)


#### class `UAssetDefinition_LevelSequence`  
`class UAssetDefinition_LevelSequence : public UAssetDefinitionDefault`  
_L13-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/FilmOverlayToolkit.h` (Public)


#### class `UFilmOverlayToolkit`  
`class UFilmOverlayToolkit : public UObject`  
_L13-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Tool kit for film overlays
- L20 _public prototype_ `static void RegisterPrimaryFilmOverlay(const FName& FilmOverlayName, TSharedPtr<IFilmOverlay> FilmOverlay);` — Register a primary film overlay
- L23 _public prototype_ `static void UnregisterPrimaryFilmOverlay(const FName& FilmOverlayName);` — Unregister a primary film overlay
- L26 _public prototype_ `static const TMap<FName, TSharedPtr<IFilmOverlay>>& GetPrimaryFilmOverlays();` — Get the primary film overlays
- L29 _public prototype_ `static void RegisterToggleableFilmOverlay(const FName& FilmOverlayName, TSharedPtr<IFilmOverlay> FilmOverlay);` — Register a toggleable film overlay
- L32 _public prototype_ `static void UnregisterToggleableFilmOverlay(const FName& FilmOverlayName);` — Unregister a toggleable film overlay
- L35 _public prototype_ `static const TMap<FName, TSharedPtr<IFilmOverlay>>& GetToggleableFilmOverlays();` — Get the toggleable film overlays
- L40 _private member_ `static TMap<FName, TSharedPtr<IFilmOverlay>> PrimaryFilmOverlays;` — The primary film overlays (only one can be active at a time)
- L43 _private member_ `static TMap<FName, TSharedPtr<IFilmOverlay>> ToggleableFilmOverlays;` — The toggleable film overlays (any number can be active at a time)

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/IFilmOverlay.h` (Public)


#### struct `IFilmOverlay`  
`struct IFilmOverlay`  
_L11-51_
- desc: Abstract base class that defines how an overlay should be drawn over the viewport
- L13 _public function_ `IFilmOverlay() : Tint(FLinearColor::White) , bEnabled(false)`
- L17 _public prototype_ `virtual ~IFilmOverlay() = default;`
- L20 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get a localized display name that is representative of this overlay
- L23 _public function_ `virtual FText GetToolTip() const` — Get a localized tooltip for this overlay
- L26 _public prototype_ `virtual const FSlateBrush* GetThumbnail() const = 0;` — Get a slate thumbnail brush that is representative of this overlay. 36x24 recommended
- L29 _public function_ `virtual TSharedPtr<SWidget> ConstructSettingsWidget()` — Construct a widget that controls this overlay's arbitrary settings. Only used for toggleable overlays.
- L32 _public prototype_ `virtual void Paint(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const = 0;` — Paint the overlay
- L37 _public function_ `const FLinearColor& GetTint() const` — Get/Set a custom tint for this overlay
- L38 _public function_ `void SetTint(const FLinearColor& InTint)`
- L41 _public function_ `bool IsEnabled() const` — Get/Set whether this overlay should be drawn
- L42 _public function_ `void SetEnabled(bool bInEnabled)`
- L47 _protected member_ `FLinearColor Tint;` — Tint to apply to this overlay
- L50 _protected member_ `bool bEnabled;` — Whether this overlay is enabled or not

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/ILevelSequenceEditorToolkit.h` (Public)


#### class `ILevelSequenceEditorToolkit`  
`class ILevelSequenceEditorToolkit : public FAssetEditorToolkit`  
_L12-21_
- inherits: `FAssetEditorToolkit`
- desc: Implements an Editor toolkit for level sequences.
- L20 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const = 0;` — Access the sequencer that is displayed on this asset editor UI

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/LevelSequenceEditorBlueprintLibrary.h` (Public)


#### class `ULevelSequenceEditorBlueprintLibrary`  
`class ULevelSequenceEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L26-357_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L36 _public prototype_ `static bool OpenLevelSequence(ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Open a level sequence asset
- L42 _public prototype_ `static ULevelSequence* GetCurrentLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Get the currently opened root level sequence asset
- L48 _public prototype_ `static ULevelSequence* GetFocusedLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Get the currently focused/viewed level sequence asset if there is a hierarchy of sequences.
- L54 _public prototype_ `static void FocusLevelSequence(UMovieSceneSubSection* SubSection);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Focus/view the sequence associated to the given sub sequence section.
- L60 _public prototype_ `static void FocusParentSequence();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Focus/view the parent sequence, popping out of the current sub sequence section.
- L66 _public prototype_ `static TArray<UMovieSceneSubSection*> GetSubSequenceHierarchy();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Get the current sub section hierarchy from the current sequence to the section associated with the focused sequence.
- L72 _public prototype_ `static void CloseLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Close
- L78 _public prototype_ `static void Play();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Play the current level sequence
- L84 _public prototype_ `static void Pause();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Pause the current level sequence
- L90 _public prototype_ `static void SetCurrentTime(int32 NewFrame);` — `UE_DEPRECATED(5.4, "Use SetCurrentTime that takes a FMovieSceneSequencePlaybackParams")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use SetCurrentTime that takes a FMovieSceneSequencePlaybackParams"))`
- L94 _public prototype_ `static int32 GetCurrentTime();` — `UE_DEPRECATED(5.4, "Use GetCurrentTime that returns a FMovieSceneSequencePlaybackParams")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use GetCurrentTime that returns a FMovieSceneSequencePlaybackParams"))`
- L98 _public prototype_ `static void SetCurrentLocalTime(int32 NewFrame);` — `UE_DEPRECATED(5.4, "Use SetCurrentLocalTime that takes a FMovieSceneSequencePlaybackParams")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use SetCurrentLocalTime that takes a FMovieSceneSequencePlaybackParams"))`
- L102 _public prototype_ `static int32 GetCurrentLocalTime();` — `UE_DEPRECATED(5.4, "Use GetCurrentLocalTime that takes a FMovieSceneSequencePlaybackParams")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use GetCurrentLocalTime that returns a FMovieSceneSequencePlaybackParams"))`
- L108 _public prototype_ `static void SetGlobalPosition(FMovieSceneSequencePlaybackParams PlaybackParams, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Set Current Time")` — Set global playhead position for the current level sequence. If the requested time is the same as the current time, an evaluation will be forced.
- L114 _public prototype_ `static FMovieSceneSequencePlaybackParams GetGlobalPosition(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Get Current Time")` — Get the current global playhead position
- L120 _public prototype_ `static void SetLocalPosition(FMovieSceneSequencePlaybackParams PlaybackParams, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Set Current Local Time")` — Set local playhead position for the current level sequence. If the requested time is the same as the current time, an evaluation will be forced.
- L126 _public prototype_ `static FMovieSceneSequencePlaybackParams GetLocalPosition(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Get Current Local Time")` — Get the current local playhead position
- L132 _public prototype_ `static void SetPlaybackSpeed(float NewPlaybackSpeed);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Set playback speed of the current level sequence
- L138 _public prototype_ `static float GetPlaybackSpeed();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Get playback speed of the current level sequence
- L144 _public prototype_ `static void SetLoopMode(ESequencerLoopMode NewLoopMode);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Set loop mode (note this is a per user preference)
- L150 _public prototype_ `static ESequencerLoopMode GetLoopMode();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Get loop mode (note this is a per user preference)
- L156 _public prototype_ `static void PlayTo(FMovieSceneSequencePlaybackParams PlaybackParams, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Play from the current time to the requested time in frames
- L162 _public prototype_ `static FMovieSceneSequencePlaybackParams GetPlaybackStartPosition(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Get Playback Start Time")` — Return the playback start position
- L166 _public prototype_ `static FMovieSceneSequencePlaybackParams GetPlaybackEndPosition(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", DisplayName = "Get Playback End Time")` — Return end of the playback range in the Sequencer UI, which accounts for the exclusive upper bound
- L170 _public prototype_ `static bool IsPlaying();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Check whether the sequence is actively playing.
- L176 _public prototype_ `static TArray<UMovieSceneTrack*> GetSelectedTracks();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the currently selected tracks.
- L180 _public prototype_ `static TArray<UMovieSceneSection*> GetSelectedSections();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the currently selected sections.
- L184 _public prototype_ `static TArray<FSequencerChannelProxy> GetSelectedChannels();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the currently selected channels.
- L188 _public prototype_ `static TArray<FSequencerChannelProxy> GetChannelsWithSelectedKeys();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the channel with selected keys.
- L192 _public prototype_ `static TArray<int32> GetSelectedKeys(const FSequencerChannelProxy& ChannelProxy);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the selected key indices with this channel
- L196 _public prototype_ `static TArray<UMovieSceneFolder*> GetSelectedFolders();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the currently selected folders.
- L200 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetSelectedBindings();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets the currently selected object bindings
- L204 _public prototype_ `static void SelectTracks(const TArray<UMovieSceneTrack*>& Tracks);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select tracks
- L208 _public prototype_ `static void SelectSections(const TArray<UMovieSceneSection*>& Sections);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select sections
- L212 _public prototype_ `static void SelectChannels(const TArray<FSequencerChannelProxy>& Channels);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select channels
- L216 _public prototype_ `static void SelectKeys(const FSequencerChannelProxy& Channel, const TArray<int32>& Indices);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select keys from indices
- L220 _public prototype_ `static void SelectFolders(const TArray<UMovieSceneFolder*>& Folders);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select folders
- L224 _public prototype_ `static void SelectBindings(const TArray<FMovieSceneBindingProxy>& ObjectBindings);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Select bindings
- L228 _public prototype_ `static void DeselectBindings(const TArray<FMovieSceneBindingProxy>& ObjectBindings);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Deselect bindings
- L232 _public prototype_ `static void EmptySelection();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Empties the current selection.
- L236 _public prototype_ `static void SetSelectionRangeStart(int32 NewFrame);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Set the selection range start frame.
- L240 _public prototype_ `static void SetSelectionRangeEnd(int32 NewFrame);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Set the selection range end frame.
- L244 _public prototype_ `static int32 GetSelectionRangeStart();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Get the selection range start frame.
- L248 _public prototype_ `static int32 GetSelectionRangeEnd();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Get the selection range end frame.
- L254 _public prototype_ `static void RefreshCurrentLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Refresh Sequencer UI on next tick
- L258 _public prototype_ `static void ForceUpdate();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Force sequencer evaluation and UI update immediately
- L262 _public prototype_ `static TArray<UObject*> GetBoundObjects(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintPure, Category="Level Sequence Editor")` — Get the object bound to the given binding ID with the current level sequence editor
- L266 _public prototype_ `static bool IsLevelSequenceLocked();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Check whether the current level sequence and its descendants are locked for editing.
- L270 _public prototype_ `static void SetLockLevelSequence(bool bLock);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sets the lock for the current level sequence and its descendants for editing.
- L276 _public prototype_ `static bool IsCameraCutLockedToViewport();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Check whether the lock for the viewport to the camera cuts is enabled.
- L280 _public prototype_ `static void SetLockCameraCutToViewport(bool bLock);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sets the lock for the viewport to the camera cuts.
- L287 _public prototype_ `static bool IsTrackFilterEnabled(const FText& TrackFilterName);` — `UE_DEPRECATED(5.5, "Use IsTrackFilterActive")` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets whether the specified track filter is on/off
- L291 _public prototype_ `static bool IsTrackFilterActive(const FText& TrackFilterName);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets whether the specified track filter is on/off
- L296 _public prototype_ `static void SetTrackFilterEnabled(const FText& TrackFilterName, bool bEnabled);` — `UE_DEPRECATED(5.5, "Use SetTrackFilterActive")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sets the specified track filter to be on or off
- L300 _public prototype_ `static void SetTrackFilterActive(const FText& TrackFilterName, bool bActive);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sets the specified track filter to be on or off
- L304 _public prototype_ `static TArray<FText> GetTrackFilterNames();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Gets all the available track filter names
- L312 _public prototype_ `static bool HasCustomColorForChannel(UClass* Class, const FString& Identifier);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::HasCustomColorForChannel")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::HasCustomColorForChannel"))` — Get if a custom color for specified channel idendified by it's class and identifier exists
- L318 _public prototype_ `static FLinearColor GetCustomColorForChannel(UClass* Class, const FString& Identifier);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::GetCustomColorForChannel")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::HasCustomColorForChannel"))` — Get custom color for specified channel idendified by it's class and identifier,if none exists will return white
- L324 _public prototype_ `static void SetCustomColorForChannel(UClass* Class, const FString& Identifier, const FLinearColor& NewColor);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::SetCustomColorForChannel")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::SetCustomColorForChannel"))` — Set Custom Color for specified channel idendified by it's class and identifier. This will be stored in editor user preferences.
- L330 _public prototype_ `static void SetCustomColorForChannels(UClass* Class, const TArray<FString>& Identifiers, const TArray<FLinearColor>& NewColors);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::DeleteColorForChannels")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::DeleteColorForChannels"))` — Set Custom Color for specified channels idendified by it's class and identifiers. This will be stored in editor user preferences.
- L336 _public prototype_ `static void SetRandomColorForChannels(UClass* Class, const TArray<FString>& Identifiers);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::SetRandomColorForChannels")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::SetRandomColorForChannels"))` — Set Random Colors for specified channels idendified by it's class and identifiers. This will be stored in editor user preferences.
- L342 _public prototype_ `static void DeleteColorForChannels(UClass* Class, FString& Identifier);` — `UE_DEPRECATED(5.4, "Use USequencerCurveEditorObject::DeleteColorForChannels")` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor", meta = (DeprecatedFunction, DeprecationMessage = "Use USequencerCurveEditorObject::DeleteColorForChannels"))` — Delete for specified channel idendified by it's class and identifier.
- L356 _public prototype_ `static void SetSequencer(TSharedRef<ISequencer> InSequencer);` — Internal function to assign a sequencer singleton. NOTE: Only to be called by LevelSequenceEditor::Construct.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/LevelSequenceEditorModule.h` (Public)


#### class `ILevelSequenceEditorModule`  
`class ILevelSequenceEditorModule : public IModuleInterface`  
_L16-28_
- inherits: `IModuleInterface`
- desc: Interface for the Level Sequence Editor module.
- L20 _public prototype_ `DECLARE_EVENT_OneParam(ILevelSequenceEditorModule, FOnLevelSequenceWithShotsCreated, UObject*);`
- L21 _public prototype_ `virtual FOnLevelSequenceWithShotsCreated& OnLevelSequenceWithShotsCreated() = 0;`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllowPlaybackContext, bool&);`
- L24 _public prototype_ `virtual FAllowPlaybackContext& OnComputePlaybackContext() = 0;`
- L26 _public prototype_ `virtual FGuid RegisterAdditionalLevelSequenceEditorCustomization(FOnGetSequencerCustomizationInstance OnGetInstance) = 0;`
- L27 _public prototype_ `virtual void UnregisterAdditionalLevelSequenceEditorCustomization(FGuid InHandle) = 0;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_EVENT_OneParam(ILevelSequenceEditorModule, FOnLevelSequenceWithShotsCreated, UObject*);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllowPlaybackContext, bool&);`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/LevelSequenceEditorSubsystem.h` (Public)


#### struct `FMovieSceneScriptingParams`  
`struct FMovieSceneScriptingParams`  
_L56-64_
- reflection: `USTRUCT(BlueprintType)`
- L60 _public function_ `FMovieSceneScriptingParams()`
- L63 _public member_ `EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Scene")`

#### struct `FMovieSceneBindingPropertyInfo`  
`struct FMovieSceneBindingPropertyInfo`  
_L68-82_
- reflection: `USTRUCT()`
- desc: Helper struct for Binding Properties UI for locators.
- L74 _public member_ `FUniversalObjectLocator Locator;` — `UPROPERTY(EditAnywhere, Category = "Default", meta=(AllowedLocators="Actor, UsdPrim", DisplayName="Actor"))` — Locator for the entry
- L78 _public member_ `ELocatorResolveFlags ResolveFlags = ELocatorResolveFlags::None;` — `UPROPERTY()` — Flags for how to resolve the locator
- L81 _public member_ `TObjectPtr<UMovieSceneCustomBinding> CustomBinding = nullptr;` — `UPROPERTY(Instanced, VisibleAnywhere, Category = "Default", meta=(EditInline, AllowEditInlineCustomization, DisplayName="Custom Binding Type"))`

#### class `UMovieSceneBindingPropertyInfoList`  
`class UMovieSceneBindingPropertyInfoList : public UObject`  
_L86-96_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Helper UObject for editing arrays of locators for object bindings. A UObject instead of a UStruct because we need to support instanced sub objects
- L92 _public member_ `TArray<FMovieSceneBindingPropertyInfo> Bindings;` — `UPROPERTY(EditAnywhere, Category = "Binding Properties")` — List of locator info for a particular binding
- L95 _public member_ `TWeakPtr<ISequencer> Sequencer;` — The Sequencer that the Bindings are sourced from

#### class `ULevelSequenceEditorSubsystem`  
`class ULevelSequenceEditorSubsystem : public UEditorSubsystem`  
_L103-417_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: ULevelSequenceEditorSubsystem Subsystem for level sequence editor related utilities to scripts
- L109 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L110 _public prototype_ `virtual void Deinitialize() override;`
- L112 _public prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);`
- L114 _public prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);`
- L118 _public prototype_ `USequencerModuleScriptingLayer* GetScriptingLayer();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Retrieve the scripting layer
- L122 _public prototype_ `USequencerCurveEditorObject* GetCurveEditor();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence Editor")` — Retrieve the curve editor
- L126 _public member_ `FOnLevelSequenceGlobalTimeChanged OnGlobalTimeChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the global time changes in the active sequencer
- L130 _public member_ `FOnLevelSequencePlayEvent OnPlayEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the active sequencer begins playing
- L134 _public member_ `FOnLevelSequenceStopEvent OnStopEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the active sequencer stops playing
- L138 _public member_ `FOnLevelSequenceRecordEvent OnRecordEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the active sequencer toggles recording
- L142 _public member_ `FOnLevelSequenceBeginScrubbingEvent OnBeginScrubbingEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the user begins scrubbing in the active sequencer
- L146 _public member_ `FOnLevelSequenceEndScrubbingEvent OnEndScrubbingEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Level Sequence Editor")` — Called when the user ends scrubbing in the active sequencer
- L150 _public prototype_ `TArray<FMovieSceneBindingProxy> AddActors(const TArray<AActor*>& Actors);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Add existing actors to Sequencer. Tracks will be automatically added based on default track settings.
- L154 _public prototype_ `FMovieSceneBindingProxy AddSpawnableFromInstance(UMovieSceneSequence* Sequence, UObject* ObjectToSpawn);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Add a new binding to this sequence that will spawn the specified object.
- L158 _public prototype_ `FMovieSceneBindingProxy AddSpawnableFromClass(UMovieSceneSequence* Sequence, UClass* ClassToSpawn);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Add a new binding to this sequence that will spawn the specified class.
- L162 _public prototype_ `FMovieSceneBindingProxy CreateCamera(bool bSpawnable, ACineCameraActor*& OutActor);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Create a cine camera actor and add it to Sequencer
- L169 _public prototype_ `TArray<FMovieSceneBindingProxy> ConvertToSpawnable(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Convert to spawnable. If there are multiple objects assigned to the possessable, multiple spawnables will be created. For level sequences, the bindings created will be custom bindings of type UMovieSceneSpawnableActorBinding.
- L173 _public prototype_ `FMovieSceneBindingProxy ConvertToPossessable(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Convert to possessable. If there are multiple objects assigned to the spawnable.
- L177 _public prototype_ `FMovieSceneBindingProxy ConvertToCustomBinding(const FMovieSceneBindingProxy& ObjectBinding, UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UMovieSceneCustomBinding> BindingT` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Convert to a custom binding of the given binding type
- L181 _public prototype_ `TArray<UMovieSceneCustomBinding*> GetCustomBindingObjects(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — In the case that the given binding proxy holds custom bindings, returns an array of the binding objects so properties can be accessed.
- L185 _public prototype_ `TArray<FMovieSceneBindingProxy> GetCustomBindingsOfType(TSubclassOf<UMovieSceneCustomBinding> CustomBindingType);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Returns all of the bindings in the sequence of the given custom type.
- L189 _public prototype_ `TSubclassOf<UMovieSceneCustomBinding> GetCustomBindingType(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Returns the custom binding type for the given binding, or nullptr for possessables
- L193 _public prototype_ `bool ChangeActorTemplateClass(const FMovieSceneBindingProxy& ObjectBinding, TSubclassOf<AActor> ActorClass);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sets the actor class for the spawnable or replaceable template, in the case those binding types support templates.
- L197 _public prototype_ `void SaveDefaultSpawnableState(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Save the default state of the spawnable.
- L206 _public prototype_ `void CopyFolders(const TArray<UMovieSceneFolder*>& Folders, FString& FoldersExportedText, FString& ObjectsExportedText, FString& TracksExportedText);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Copy folders The copied folders will be saved to the clipboard as well as assigned to the ExportedText string. The ExportedTest string can be used in conjunction with PasteFolders if, for example, pasting copy/pasting multiple folders without relying on a single clipboard.
- L209 _public prototype_ `void CopyFolders(const TArray<UMovieSceneFolder*>& Folders, FString& FoldersExportedText);` — `UE_DEPRECATED(5.5, "CopyFolders now gathers objects and tracks within the folders. Please use CopyFolders that outputs ObjectsExportedText and TracksExportedText")`
- L217 _public prototype_ `bool PasteFolders(const FString& TextToImport, FMovieScenePasteFoldersParams PasteFoldersParams, TArray<UMovieSceneFolder*>& OutFolders);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Paste folders Paste folders from the given TextToImport string (used in conjunction with CopyFolders). If TextToImport is empty, the contents of the clipboard will be used.
- L226 _public prototype_ `void CopySections(const TArray<UMovieSceneSection*>& Sections, FString& ExportedText);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Copy sections The copied sections will be saved to the clipboard as well as assigned to the ExportedText string. The ExportedTest string can be used in conjunction with PasteSections if, for example, pasting copy/pasting multiple sections without relying on a single clipboard.
- L234 _public prototype_ `bool PasteSections(const FString& TextToImport, FMovieScenePasteSectionsParams PasteSectionsParams, TArray<UMovieSceneSection*>& OutSections);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Paste sections Paste sections from the given TextToImport string (used in conjunction with CopySections). If TextToImport is empty, the contents of the clipboard will be used.
- L243 _public prototype_ `void CopyTracks(const TArray<UMovieSceneTrack*>& Tracks, FString& ExportedText);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Copy tracks The copied tracks will be saved to the clipboard as well as assigned to the ExportedText string. The ExportedTest string can be used in conjunction with PasteTracks if, for example, pasting copy/pasting multiple tracks without relying on a single clipboard.
- L251 _public prototype_ `bool PasteTracks(const FString& TextToImport, FMovieScenePasteTracksParams PasteTracksParams, TArray<UMovieSceneTrack*>& OutTracks);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Paste tracks Paste tracks from the given TextToImport string (used in conjunction with CopyTracks). If TextToImport is empty, the contents of the clipboard will be used.
- L260 _public prototype_ `void CopyBindings(const TArray<FMovieSceneBindingProxy>& Bindings, FString& ExportedText);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Copy bindings The copied bindings will be saved to the clipboard as well as assigned to the ExportedText string. The ExportedTest string can be used in conjunction with PasteBindings if, for example, pasting copy/pasting multiple bindings without relying on a single clipboard.
- L268 _public prototype_ `bool PasteBindings(const FString& TextToImport, FMovieScenePasteBindingsParams PasteBindingsParams, TArray<FMovieSceneBindingProxy>& OutObjectBindings);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Paste bindings Paste bindings from the given TextToImport string (used in conjunction with CopyBindings). If TextToImport is empty, the contents of the clipboard will be used.
- L272 _public prototype_ `void SnapSectionsToTimelineUsingSourceTimecode(const TArray<UMovieSceneSection*>& Sections);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Snap sections to timeline using source timecode
- L276 _public prototype_ `void SyncSectionsUsingSourceTimecode(const TArray<UMovieSceneSection*>& Sections);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Sync section using source timecode
- L280 _public prototype_ `bool BakeTransformWithSettings(const TArray<FMovieSceneBindingProxy>& ObjectBindings, const FBakingAnimationKeySettings& InSettings, const FMovieSceneScriptingParams& Params = FMovieSceneScriptingParams());` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Bake transform
- L284 _public prototype_ `void FixActorReferences();` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Attempts to automatically fix up broken actor references in the current scene
- L288 _public prototype_ `void AddActorsToBinding(const TArray<AActor*>& Actors, const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Assigns the given actors to the binding
- L292 _public prototype_ `void ReplaceBindingWithActors(const TArray<AActor*>& Actors, const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Replaces the binding with the given actors
- L296 _public prototype_ `void RemoveActorsFromBinding(const TArray<AActor*>& Actors, const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Removes the given actors from the binding
- L300 _public prototype_ `void RemoveAllBindings(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Remove all bound actors from this track
- L304 _public prototype_ `void RemoveInvalidBindings(const FMovieSceneBindingProxy& ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Remove missing objects bound to this track
- L308 _public prototype_ `void RebindComponent(const TArray<FMovieSceneBindingProxy>& ComponentBindings, const FName& ComponentName);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence Editor")` — Rebind the component binding to the requested component
- L311 _public prototype_ `void RefreshBindingDetails(IDetailsView* DetailsView, FGuid ObjectBindingID);` — Refreshes the binding details when the bindings change in the menu
- L314 _public prototype_ `void RefreshTrackRowMetadataDetails(IDetailsView* DetailsView);` — Refreshes the track row metadata details when the track row metadata changes in the menu
- L331 _private member_ `TArray<TObjectPtr<UMovieSceneBindingPropertyInfoList>> BindingPropertyInfoLists;` — `UPROPERTY()`
- L334 _private member_ `TArray<TObjectPtr<UMovieSceneTrackRowMetadataHelper>> TrackRowMetadataHelperList;` — `UPROPERTY()`
- L336 _private member_ `FBindingPropertiesNotifyHook NotifyHook;`
- L340 _private prototype_ `void AddBindingDetailCustomizations(TSharedRef<IDetailsView> DetailsView, TSharedPtr<ISequencer> ActiveSequencer, FGuid BindingGuid);`
- L341 _private prototype_ `void AddTrackRowMetadataCustomizations(TSharedRef<IDetailsView> DetailsView, TSharedPtr<ISequencer> ActiveSequencer, UMovieSceneSequence* Sequence);`
- L342 _private prototype_ `void OnTrackRowMetadataMenuBeingDestroyed(const TSharedRef<IMenu>& Menu, TSharedRef<IDetailsView> DetailsView);`
- L344 _private prototype_ `TSharedPtr<ISequencer> GetActiveSequencer();`
- L346 _private prototype_ `void RebindComponentInternal(const FName& ComponentName);`
- L348 _private prototype_ `void AddBindingPropertiesMenu(FMenuBuilder& MenuBuilder);`
- L350 _private prototype_ `void FillDirectorBlueprintBindingSubMenu(FMenuBuilder& MenuBuilder, TSharedRef<ISequencer> Sequencer, const TArray<FSequencerChangeBindingInfo>& BindingsToChange, bool bConvert, TFunction<void()> OnBindingChanged, const TSubclassOf<UMovieSceneCustomBinding>& CustomBindingType);`
- L351 _private prototype_ `void PopulateQuickBindSubMenu(FMenuBuilder& MenuBuilder, TSharedRef<ISequencer> Sequencer, const TArray<FSequencerChangeBindingInfo>& BindingsToChange, bool bConvert, TFunction<void()> OnBindingChanged, const TSubclassOf<UMovieSceneCustomBinding>& CustomBindingType);`
- L352 _private prototype_ `void FillBindingClassSubMenu(FMenuBuilder& MenuBuilder, TSharedRef<ISequencer> Sequencer, const TArray<FSequencerChangeBindingInfo>& BindingsToChange, bool bConvert, TFunction<void()> OnBindingChanged, const TArray<const TSubclassOf<UMovieSceneCustomBinding>>& UserCustomBindingTypes);`
- L353 _private prototype_ `void ChangeBindingTypes(const TSharedRef<ISequencer>& InSequencer , const TArray<FSequencerChangeBindingInfo>& InBindingsToChange , TFunction<FMovieScenePossessable* (FGuid, int32)> InDoChangeType , TFunction<void()> InOnBindingChanged);`
- L358 _private prototype_ `void AddTrackRowMetadataMenu(FMenuBuilder& MenuBuilder);`
- L360 _public prototype_ `void AddBindingPropertiesSidebar(FMenuBuilder& MenuBuilder);`
- L362 _public prototype_ `TSharedRef<SWidget> BuildBindingPropertiesDetailsWidget(TSharedRef<ISequencer> Sequencer);`
- L363 _public prototype_ `void RefreshBindingDetails(TSharedRef<ISequencer> Sequencer, IDetailsView* DetailsView, FGuid ObjectBindingID);`
- L367 _public prototype_ `void AddChangeBindingTypeMenu(FMenuBuilder& MenuBuilder, TSharedRef<ISequencer> Sequencer, const TArray<FSequencerChangeBindingInfo>& BindingsToChange, bool bConvert, TFunction<void()> OnBindingChanged);` — Creates a menu for changing or converting a binding type. If bConvert is true, it will only show types that state they are able to be converted to from the passed in bindings and will attempt to convert them. If bConvert is false, it will change the binding type and reset to a default binding of that type.
- L370 _public prototype_ `void AddDefaultTracksForActor(TSharedRef<ISequencer> InSequencer, AActor& Actor, const FGuid Binding);` — Add the default movie scene tracks for the given actor to its binding in the sequencer's focused sequence.
- L373 _private prototype_ `void OnFinishedChangingLocators(const FPropertyChangedEvent& PropertyChangedEvent, TWeakPtr<ISequencer> WeakSequencer, TSharedRef<IDetailsView> DetailsView, FGuid ObjectBindingID);`
- L375 _private prototype_ `void OnFinishedChangingTrackRowMetadata(const FPropertyChangedEvent& PropertyChangedEvent, TSharedRef<IDetailsView> DetailsView);`
- L377 _private prototype_ `void GetRebindComponentNames(TArray<FName>& OutComponentNames);`
- L378 _private prototype_ `void RebindComponentMenu(FMenuBuilder& MenuBuilder);`
- L380 _private prototype_ `UMovieSceneBindingPropertyInfoList* GetBindingPropertyInfoList(TSharedRef<ISequencer> Sequencer);`
- L382 _private prototype_ `void CreatePlaybackDelegates(TSharedRef<ISequencer> InSequencer);`
- L384 _private prototype_ `void HandleGlobalTimeChanged();`
- L385 _private prototype_ `void HandlePlayEvent();`
- L386 _private prototype_ `void HandleStopEvent();`
- L387 _private prototype_ `void HandleRecordEvent();`
- L388 _private prototype_ `void HandleBeginScrubbingEvent();`
- L389 _private prototype_ `void HandleEndScrubbingEvent();`
- L400 _private member_ `TMap<TWeakPtr<ISequencer>, FSequencerPlaybackDelegateHandles> SequencerPlaybackDelegateHandles;`
- L402 _private member_ `FDelegateHandle OnSequencerCreatedHandle;`
- L405 _private member_ `TArray<TWeakPtr<ISequencer>> Sequencers;` — List of sequencers that have been created
- L408 _private member_ `TMap<TWeakPtr<ISequencer>, TObjectPtr<USequencerCurveEditorObject>> CurveEditorObjects;` — Map of curve editors with their sequencers
- L411 _private member_ `TArray<TObjectPtr<USequencerCurveEditorObject>> CurveEditorArray;` — `UPROPERTY()` — property array of the curve editors
- L413 _private member_ `TSharedPtr<FExtender> RebindComponentMenuExtender;`
- L414 _private member_ `TSharedPtr<FExtender> SidebarMenuExtender;`

#### struct `ULevelSequenceEditorSubsystem::FBindingPropertiesNotifyHook`  
`struct FBindingPropertiesNotifyHook : FNotifyHook`  
_L319-328_
- inherits: `FNotifyHook`
- desc: Used by binding properties menu
- L321 _public member_ `UMovieSceneSequence* ObjectToModify = nullptr;`
- L322 _public function_ `FBindingPropertiesNotifyHook()`
- L324 _public function_ `FBindingPropertiesNotifyHook(UMovieSceneSequence* InObjectToModify) : ObjectToModify(InObjectToModify)`
- L326 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L327 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`

#### struct `ULevelSequenceEditorSubsystem::FSequencerPlaybackDelegateHandles`  
`struct FSequencerPlaybackDelegateHandles`  
_L391-399_
- L393 _public member_ `FDelegateHandle GlobalTimeChanged;`
- L394 _public member_ `FDelegateHandle PlayEvent;`
- L395 _public member_ `FDelegateHandle StopEvent;`
- L396 _public member_ `FDelegateHandle RecordEvent;`
- L397 _public member_ `FDelegateHandle BeginScrubbing;`
- L398 _public member_ `FDelegateHandle EndScrubbing;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`
- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelSequenceEditor, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelSequenceEditor, Log, All);`
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceGlobalTimeChanged);`
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceGlobalTimeChanged);`
- L34 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequencePlayEvent);`
- L34 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequencePlayEvent);`
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceStopEvent);`
- L35 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceStopEvent);`
- L36 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceRecordEvent);`
- L36 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceRecordEvent);`
- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceBeginScrubbingEvent);`
- L37 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceBeginScrubbingEvent);`
- L38 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceEndScrubbingEvent);`
- L38 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceEndScrubbingEvent);`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Misc/LevelSequenceEditorSettings.h` (Public)


#### struct `FLevelSequencePropertyTrackSettings`  
`struct FLevelSequencePropertyTrackSettings`  
_L10-21_
- reflection: `USTRUCT()`
- L16 _public member_ `FString ComponentPath;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Optional ActorComponent tag (when keying a component property).
- L20 _public member_ `FString PropertyPath;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Path to the keyed property within the Actor or ActorComponent.

#### struct `FLevelSequenceTrackSettings`  
`struct FLevelSequenceTrackSettings`  
_L25-48_
- reflection: `USTRUCT()`
- L31 _public member_ `FSoftClassPath MatchingActorClass;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/Engine.Actor"))` — The Actor class to create movie scene tracks for.
- L35 _public member_ `TArray<FSoftClassPath> DefaultTracks;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/MovieScene.MovieSceneTrack"))` — List of movie scene track classes to be added automatically.
- L39 _public member_ `TArray<FSoftClassPath> ExcludeDefaultTracks;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/MovieScene.MovieSceneTrack"))` — List of movie scene track classes not to be added automatically.
- L43 _public member_ `TArray<FLevelSequencePropertyTrackSettings> DefaultPropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — List of property names for which movie scene tracks will be created automatically.
- L47 _public member_ `TArray<FLevelSequencePropertyTrackSettings> ExcludeDefaultPropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — List of property names for which movie scene tracks will not be created automatically.

#### class `ULevelSequenceEditorSettings`  
`class ULevelSequenceEditorSettings : public UObject`  
_L55-75_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Level Sequence Editor settings.
- L62 _public prototype_ `ULevelSequenceEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L66 _public member_ `TArray<FLevelSequenceTrackSettings> TrackSettings;` — `UPROPERTY(config, EditAnywhere, Category=Tracks)` — Specifies class properties for which movie scene tracks will be created automatically.
- L70 _public member_ `bool bAutoBindToPIE;` — `UPROPERTY(config, EditAnywhere, Category=Playback)` — Specifies whether to automatically bind an active sequencer UI to PIE worlds.
- L74 _public member_ `bool bAutoBindToSimulate;` — `UPROPERTY(config, EditAnywhere, Category=Playback)` — Specifies whether to automatically bind an active sequencer UI to simulate worlds.

#### class `ULevelSequenceWithShotsSettings`  
`class ULevelSequenceWithShotsSettings : public UObject`  
_L81-114_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Level Sequence With Shots Settings.
- L89 _public member_ `FString Name;` — `UPROPERTY(config, DisplayName="Name", EditAnywhere, Category=SequenceWithShots)` — Sequence With Shots name.
- L93 _public member_ `FString Suffix;` — `UPROPERTY(config, DisplayName="Suffix", EditAnywhere, Category=SequenceWithShots)` — Sequence With Shots suffix.
- L97 _public member_ `FDirectoryPath BasePath;` — `UPROPERTY(config, DisplayName="Base Path", EditAnywhere, Category=SequenceWithShots, meta=(ContentDir))` — Sequence With Shots path.
- L101 _public member_ `uint32 NumShots;` — `UPROPERTY(config, DisplayName="Number of Shots", EditAnywhere, Category=SequenceWithShots, meta = (UIMin = "1", UIMax = "100"))` — Sequence With Shots number of shots.
- L105 _public member_ `TSoftObjectPtr<class ULevelSequence> SequenceToDuplicate;` — `UPROPERTY(Transient, DisplayName="Sequence to Duplicate", EditAnywhere, Category=SequenceWithShots)` — Sequence With Shots level sequence to duplicate when creating shots.
- L109 _public member_ `TArray<FName> SubSequenceNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= SequenceWithShots)` — Array of sub sequence names, each will result in a level sequence asset in the shot.
- L113 _public member_ `bool bInstanceSubSequences;` — `UPROPERTY(config, DisplayName="Instance Sub Sequences", EditAnywhere, Category=SequenceWithShots)` — Whether to instance sub sequences based on the first created sub sequences.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Misc/LevelSequenceEditorSpawnRegister.h` (Public)


#### class `FLevelSequenceEditorSpawnRegister`  
`class FLevelSequenceEditorSpawnRegister : public FLevelSequenceSpawnRegister`  
_L21-123_
- inherits: `FLevelSequenceSpawnRegister`
- desc: Spawn register used in the editor to add some usability features like maintaining selection states, and projecting spawned state onto spawnable defaults
- L27 _public prototype_ `FLevelSequenceEditorSpawnRegister();` — Constructor
- L30 _public prototype_ `~FLevelSequenceEditorSpawnRegister();` — Destructor.
- L34 _public prototype_ `void SetSequencer(const TSharedPtr<ISequencer>& Sequencer);`
- L41 _public prototype_ `virtual UObject* SpawnObject(const FGuid& BindingId, UMovieScene& MovieScene, FMovieSceneSequenceIDRef Template, TSharedRef<const FSharedPlaybackState> SharedPlaybackState, int32 BindingIndex);`
- L42 _public prototype_ `virtual void PreDestroyObject(UObject& Object, const FGuid& BindingId, int32 BindingIndex, FMovieSceneSequenceIDRef TemplateID) override;`
- L44 _public prototype_ `virtual void SaveDefaultSpawnableState(const FGuid& BindingId, int32 BindingIndex, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;`
- L45 _public prototype_ `virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;`
- L46 _public prototype_ `virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;`
- L47 _public prototype_ `virtual void HandleConvertPossessableToSpawnable(UObject* OldObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState, TOptional<FTransformData>& OutTransformData) override;`
- L48 _public prototype_ `virtual bool CanConvertSpawnableToPossessable(FMovieSceneSpawnable& Spawnable) const override;`
- L54 _private prototype_ `void HandleActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the editor selection has changed.
- L57 _private prototype_ `void SaveDefaultSpawnableStateImpl(const FGuid& BindingId, int32 BindingIndex, UMovieSceneSequence* Sequence, UObject* SpawnedObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState);` — Saves the default state for the specified spawnable, if an instance for it currently exists
- L60 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Called from the editor when a blueprint object replacement has occurred
- L63 _private prototype_ `void OnObjectModified(UObject* ModifiedObject);` — Called whenever an object is modified in the editor
- L66 _private prototype_ `void OnPreObjectSaved(UObject* Object, FObjectPreSaveContext SaveContext);` — Called before an object is saved in the editor
- L69 _private prototype_ `void UpdateIsEngineCollectingGarbage(bool bIsCollectingGarbage);` — Called on pre/post GC
- L94 _private member_ `FDelegateHandle OnActorSelectionChangedHandle;` — Handles for delegates that we've bound to.
- L97 _private member_ `TSet<FMovieSceneSpawnRegisterKey> SelectedSpawnedObjects;` — Set of spawn register keys for objects that should be selected if they are spawned.
- L100 _private member_ `TMap<FObjectKey, FTrackedObjectState> TrackedObjects;` — Map from a sequenceID to an array of objects that have been tracked
- L103 _private member_ `TSet<FObjectKey> SequencesWithModifiedObjects;` — Set of UMovieSceneSequences that this register has spawned objects for that are modified
- L106 _private member_ `bool bShouldClearSelectionCache;` — True if we should clear the above selection cache when the editor selection has been changed.
- L109 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the active sequencer.
- L112 _private member_ `FDelegateHandle OnObjectModifiedHandle;` — Handle to a delegate that is bound to FCoreUObjectDelegates::OnObjectModified to harvest changes to spawned objects.
- L115 _private member_ `FDelegateHandle OnObjectSavedHandle;` — Handle to a delegate that is bound to FCoreUObjectDelegates::OnObjectPreSave to harvest changes to spawned objects.
- L118 _private member_ `bool bIsEngineCollectingGarbage;` — True when GCing
- L121 _private member_ `FDelegateHandle OnPreGarbageCollectHandle;` — Handle to a delegate that is bound to FCoreUObjectDelegates::OnPre/PostGarbageCollectHandle to disable saving changes while GCing.
- L122 _private member_ `FDelegateHandle OnPostGarbageCollectHandle;`

#### struct `FLevelSequenceEditorSpawnRegister::FTrackedObjectState`  
`struct FTrackedObjectState`  
_L74-89_
- L76 _public function_ `FTrackedObjectState(FMovieSceneSequenceIDRef InTemplateID, const FGuid& InObjectBindingID, int32 InBindingIndex=0) : TemplateID(InTemplateID), ObjectBindingID(InObjectBindingID), BindingIndex(InBindingIndex), bHasBeenModified(false)`
- L79 _public member_ `FMovieSceneSequenceID TemplateID;` — The sequence ID that spawned this object
- L82 _public member_ `FGuid ObjectBindingID;` — The object binding ID of the object in the template
- L85 _public member_ `int32 BindingIndex = 0;` — The index of the binding being tracked
- L88 _public member_ `bool bHasBeenModified;` — true if this object has been modified since it was spawned and is different from the current object template

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Misc/LevelSequencePlaybackContext.h` (Public)


#### class `FLevelSequencePlaybackContext`  
`class FLevelSequencePlaybackContext : public TSharedFromThis<FLevelSequencePlaybackContext>`  
_L19-105_
- inherits: `TSharedFromThis<FLevelSequencePlaybackContext>`
- desc: Class that manages the current playback context that a level-sequence editor should use for playback
- L23 _public prototype_ `FLevelSequencePlaybackContext(ULevelSequence* InLevelSequence);`
- L24 _public prototype_ `~FLevelSequencePlaybackContext();`
- L29 _public prototype_ `ULevelSequence* GetLevelSequence() const;` — Gets the level sequence for which we are trying to find the context.
- L34 _public prototype_ `TSharedRef<SWidget> BuildWorldPickerCombo();` — Build a world picker widget that allows the user to choose a world, and exit the auto-bind settings
- L39 _public prototype_ `UObject* GetPlaybackContext() const;` — Resolve the current world context pointer. Can never be nullptr.
- L44 _public prototype_ `UObject* GetPlaybackContextAsObject() const;` — Returns GetPlaybackContext as a plain object.
- L49 _public prototype_ `UObject* GetPlaybackClientAsUObject() const;` — Resolve the current playback client. May be nullptr.
- L52 _public prototype_ `ALevelSequenceActor* GetPlaybackClient() const;` — `UE_DEPRECATED(5.8, "GetPlaybackClient has been deprecated, please use GetPlaybackClientAsUObject")`
- L57 _public prototype_ `IMovieScenePlaybackClient* GetPlaybackClientAsInterface() const;` — Returns GetPlaybackClient as an interface pointer.
- L62 _public prototype_ `TArray<UObject*> GetEventContexts() const;` — Retrieve all the event contexts for the current world
- L68 _public prototype_ `void OverrideWith(UWorld* InNewContext, IMovieScenePlaybackClient* InNewClient);` — Specify a new world to use as the context. Persists until the next PIE or map change event. May be null, in which case the context will be recomputed automatically
- L72 _private typedef_ `using FContextAndClient = TTuple<UWorld*, IMovieScenePlaybackClient*>;`
- L78 _private prototype_ `static FContextAndClient ComputePlaybackContextAndClient(const ULevelSequence* InLevelSequence);` — Compute the new playback context based on the user's current auto-bind settings. Will use the first encountered PIE or Simulate world if possible, else the Editor world as a fallback
- L83 _private prototype_ `void UpdateCachedContextAndClient() const;` — Update the cached context and client pointers if needed.
- L89 _private prototype_ `FContextAndClient GetPlaybackContextAndClient() const;` — TTuple<UWorld*, IMovieScenePlaybackClient*>
- L91 _private prototype_ `void OnPieEvent(bool);`
- L92 _private prototype_ `void OnMapChange(uint32);`
- L93 _private prototype_ `void OnWorldListChanged(UWorld*);`
- L98 _private member_ `TWeakObjectPtr<ULevelSequence> LevelSequence;` — Level sequence that we should find a context for
- L101 _private member_ `mutable TWeakObjectPtr<UWorld> WeakCurrentContext;` — Mutable cached context pointer
- L104 _private member_ `mutable TWeakInterfacePtr<IMovieScenePlaybackClient> WeakCurrentClient;` — Mutable cached client pointer

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Widgets/SLevelSequenceBakeTransform.h` (Public)


#### class `SLevelSequenceBakeTransform`  
`class SLevelSequenceBakeTransform : public SCompoundWidget`  
_L19-47_
- inherits: `SCompoundWidget`
- desc: Widget that displays bake options for baking transforms
- L23 _public function_ `SLATE_BEGIN_ARGS(SLevelSequenceBakeTransform) : _Sequencer(nullptr)`
- L27 _public prototype_ `SLATE_ARGUMENT(ISequencer*, Sequencer) SLATE_ARGUMENT(FBakingAnimationKeySettings, Settings) SLATE_EVENT(SLevelSequenceBakeTransformOnBake, OnBake) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `virtual ~SLevelSequenceBakeTransform() override = default;`
- L35 _public prototype_ `FReply OpenDialog(bool bModal = true);`
- L36 _public prototype_ `void CloseDialog();`
- L41 _private member_ `TSharedPtr<TStructOnScope<FBakingAnimationKeySettings>> Settings;` — used for setting up the details
- L43 _private member_ `ISequencer* Sequencer;`
- L45 _private member_ `TWeakPtr<SWindow> DialogWindow;`
- L46 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, SLevelSequenceBakeTransformOnBake, FBakingAnimationKeySettings);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, SLevelSequenceBakeTransformOnBake, FBakingAnimationKeySettings);`

### `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Widgets/SLevelSequenceFavoriteRating.h` (Public)


#### class `SLevelSequenceFavoriteRating`  
`class SLevelSequenceFavoriteRating : public SCompoundWidget`  
_L12-30_
- inherits: `SCompoundWidget`
- desc: Widget for viewing and setting the Favorite Rating on LevelSequences.
- L15 _public function_ `SLATE_BEGIN_ARGS(SLevelSequenceFavoriteRating) : _LevelSequence(nullptr)`
- L20 _public prototype_ `SLATE_ARGUMENT( TWeakObjectPtr<ULevelSequence>, LevelSequence ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The LevelSequence object to focus the widget on
- L29 _private member_ `TWeakObjectPtr<ULevelSequence> WeakLevelSequence;` — The LevelSequence object the widget is focused on. Only a single sequence can be focused. This could be changed using the Undetermined state and special multi icons.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEVELSEQUENCEEDITOR_API`
