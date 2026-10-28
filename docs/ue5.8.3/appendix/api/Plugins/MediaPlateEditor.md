# Plugins / MediaPlateEditor

- module root: `Plugins/Media/MediaPlate/Source/MediaPlateEditor`
- headers: 14; symbols: 216
- symbol kinds: class=14, delegate=2, function=21, member=43, prototype=134, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, CinematicCamera, CoreUObject, DesktopWidgets, EditorStyle, Engine, GeometryCore, InputCore, MediaAssets, MediaCompositing, MediaCompositingEditor, MediaPlate, MediaPlayerEditor, ModelingComponents, ModelingComponentsEditorOnly, MovieScene, PlacementMode, Projects, PropertyEditor, SceneOutliner, Sequencer, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/ActorFactoryMediaPlate.h` (Private)


#### class `UActorFactoryMediaPlate`  
`class UActorFactoryMediaPlate : public UActorFactory`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L16 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L27 _private prototype_ `void SetUpActor(UObject* Asset, AActor* Actor);` — Set up a media plate actor. @param Asset		Media source asset. @param Actor		Media plate actor to set up.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/AssetTools/AssetDefinition_MediaPlate.h` (Private)


#### class `UAssetDefinition_MediaPlate`  
`class UAssetDefinition_MediaPlate : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/MediaPlateCustomization.h` (Private)


#### class `FMediaPlateCustomization`  
`class FMediaPlateCustomization : public IDetailCustomization`  
_L24-220_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UMediaPlateComponent class.
- L29 _public prototype_ `FMediaPlateCustomization();`
- L30 _public prototype_ `~FMediaPlateCustomization();`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L40 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L49 _public prototype_ `static bool IsMediaPlateEventAllowedForPlayer(EMediaPlateEventState InState, UMediaPlayer* InMediaPlayer);` — Determines if the event state switch is allowed for the given media player. Those are the UI only conditions to mirror the backend's conditions.
- L54 _public prototype_ `static void HandleMediaPlateEvent(TConstArrayView<TWeakObjectPtr<UMediaPlateComponent>> InMediaPlates, EMediaPlateEventState InState);` — Changes the state of selected media plates and broadcasts the event to the remote endpoints.
- L57 _private prototype_ `static void CustomizeCategories(IDetailLayoutBuilder& InDetailBuilder);`
- L60 _private member_ `FDelegateHandle PropertyChangeDelegate;` — Property change delegate used for static mesh material changes.
- L62 _private member_ `TArray<TWeakObjectPtr<UMediaPlateComponent>> MediaPlatesList;` — List of the media plates we are editing.
- L65 _private member_ `EMediaTextureVisibleMipsTiles MeshMode = EMediaTextureVisibleMipsTiles::None;` — Whether we have a plane, sphere, etc.
- L68 _private member_ `FMediaPlateCustomizationMesh MeshCustomization;` — Handles mesh stuff.
- L71 _private member_ `TSharedPtr<IPropertyHandle> MediaPlateResourcePropertyHandle;` — Property handle of the currently customized Media Plate Resource
- L76 _private prototype_ `void AddMeshCustomization(IDetailCategoryBuilder& InParentCategory);` — Adds widgets for editing the mesh.
- L81 _private prototype_ `EVisibility ShouldShowMeshCustomWidgets() const;` — Controls visibility for widgets for custom meshes.
- L86 _private prototype_ `EVisibility ShouldShowMeshPlaneWidgets() const;` — Controls visibility for widgets for plane meshes.
- L91 _private prototype_ `EVisibility ShouldShowMeshSphereWidgets() const;` — Controls visibility for widgets for sphere meshes.
- L96 _private prototype_ `void SetMeshMode(EMediaTextureVisibleMipsTiles InMode);` — Call this to switch between planes, spheres, etc.
- L101 _private prototype_ `void SetSphereMesh(UMediaPlateComponent* MediaPlate);` — Call this to apply a sphere mesh to an object.
- L106 _private prototype_ `TSharedRef<SWidget> OnGetAspectRatios();` — Returns menu options for all aspect ratio presets.
- L111 _private prototype_ `TSharedRef<SWidget> OnGetLetterboxAspectRatios();` — Returns menu options for all aspect ratio presets.
- L116 _private prototype_ `FText OnGetAspectRatioText() const;` — Returns the text to display for a given aspect ratio.
- L121 _private prototype_ `FText OnGetLetterboxAspectRatioText() const;` — Returns the text to display for a given letter box aspect ratio.
- L126 _private prototype_ `void AddAspectRatiosToMenuBuilder(FMenuBuilder& MenuBuilder, void (FMediaPlateCustomization::*Func)(float));` — Adds menu options for all aspect ratio presets.
- L132 _private prototype_ `ECheckBoxState IsAspectRatioAuto() const;` — Call this to see if auto aspect ratio is enabled.
- L137 _private prototype_ `void SetIsAspectRatioAuto(ECheckBoxState State);` — Call this to enable/disable automatic aspect ratio.
- L142 _private prototype_ `void SetAspectRatio(float AspectRatio);` — Call this to set the aspect ratio.
- L147 _private prototype_ `float GetAspectRatio() const;` — Call this to get the aspect ratio.
- L152 _private prototype_ `void SetLetterboxAspectRatio(float AspectRatio);` — Call this to set the aspect ratio.
- L157 _private prototype_ `float GetLetterboxAspectRatio() const;` — Call this to get the aspect ratio.
- L162 _private prototype_ `void SetMeshHorizontalRange(float HorizontalRange);` — Call this to set the horizontal range of the mesh.
- L167 _private prototype_ `TOptional<float> GetMeshHorizontalRange() const;` — Call this to get the horizontal range of the mesh.
- L172 _private prototype_ `void SetMeshVerticalRange(float VerticalRange);` — Call this to set the vertical range of the mesh.
- L177 _private prototype_ `TOptional<float> GetMeshVerticalRange() const;` — Call this to get the vertical range of the mesh.
- L182 _private prototype_ `void SetMeshRange(FVector2D Range);` — Call this to set the range of the mesh.
- L187 _private prototype_ `FString GetStaticMeshPath() const;` — Gets the object path for the static mesh.
- L192 _private prototype_ `void OnStaticMeshChanged(const FAssetData& AssetData);` — Called when the static mesh changes.
- L197 _private prototype_ `bool IsButtonEventAllowedForAnyPlate(EMediaPlateEventState InState) const;` — Determines if the event state switch is allowed in at least one selected components.
- L202 _private prototype_ `void OnButtonEvent(EMediaPlateEventState InState);` — Changes the state of selected media plates and broadcasts the event to the remote endpoints.
- L207 _private prototype_ `FReply OnOpenMediaPlate();` — Called when the open media plate button is pressed.
- L212 _private prototype_ `void StopMediaPlates();` — Call this to stop all playback.
- L214 _private prototype_ `TArray<TWeakObjectPtr<UMediaPlayer>> GetMediaPlayers() const;`
- L219 _private prototype_ `bool IsTrueForAllPlayers(TFunctionRef<bool(const UMediaPlayer*)> InPredicate) const;` — Evaluates if the given predicate is true for all players.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/MediaPlateCustomizationMesh.h` (Private)


#### class `FMediaPlateCustomizationMesh`  
`class FMediaPlateCustomizationMesh`  
_L16-58_
- desc: Implements mesh handling for FMediaPlateCustomization.
- L22 _public prototype_ `void SetCustomMesh(UMediaPlateComponent* MediaPlate, UStaticMesh* StaticMesh);` — Call this to use a custom mesh on a media plate.
- L27 _public prototype_ `void SetPlaneMesh(UMediaPlateComponent* MediaPlate);` — Call this to use a plane mesh on a media plate.
- L32 _public prototype_ `void SetSphereMesh(UMediaPlateComponent* MediaPlate);` — Call this to use a sphere mesh on a media plate.
- L39 _private prototype_ `void SetMesh(UStaticMeshComponent* StaticMeshComponent, UStaticMesh* Mesh);` — Generic function to set a mesh on a StaticMeshComponent.
- L44 _private prototype_ `void GenerateSphereMesh(FDynamicMesh3* OutMesh, UMediaPlateComponent* MediaPlate);` — Creates a sphere mesh.
- L49 _private prototype_ `UStaticMesh* CreateStaticMeshAsset(FDynamicMesh3* Mesh, const FString& AssetPath);` — Call this to create a static mesh asset for a mesh.
- L54 _private prototype_ `FString GetAssetPath(UMediaPlateComponent* MediaPlate);` — Gets the path for the mesh asset.
- L57 _private member_ `static TMap<UStaticMesh*, int32> MeshRefCount;` — Reference count for our generated meshes.

#### Free symbols / members of external scopes

- L7 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/MediaPlateEditorStyle.h` (Private)


#### class `FMediaPlateEditorStyle`  
`class FMediaPlateEditorStyle : public FSlateStyleSet`  
_L10-30_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the media plate editor UI.
- L14 _public prototype_ `FMediaPlateEditorStyle();` — Default constructor.
- L17 _public prototype_ `~FMediaPlateEditorStyle();` — Destructor.
- L19 _public function_ `static TSharedRef<FMediaPlateEditorStyle> Get()`
- L29 _private member_ `static TSharedPtr<FMediaPlateEditorStyle> Singleton;`

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/MediaPlateResourceCustomization.h` (Private)


#### class `FMediaPlateResourceCustomization`  
`class FMediaPlateResourceCustomization : public IPropertyTypeCustomization`  
_L12-47_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle , FDetailWidgetRow& InHeaderRow , IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle , IDetailChildrenBuilder& InChildBuilder , IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L28 _private prototype_ `TOptional<EMediaPlateResourceType> GetAssetType() const;`
- L30 _private prototype_ `FString GetMediaPath() const;`
- L31 _private prototype_ `FString GetMediaBrowseDirectory() const;`
- L33 _private prototype_ `void OnAssetTypeChanged(TOptional<EMediaPlateResourceType> InResourceType);`
- L34 _private prototype_ `void OnMediaPathPicked(const FString& InPickedPath);`
- L36 _private prototype_ `EVisibility GetAssetSelectorVisibility() const;`
- L37 _private prototype_ `EVisibility GetFileSelectorVisibility() const;`
- L38 _private prototype_ `EVisibility GetPlaylistSelectorVisibility() const;`
- L39 _private prototype_ `EVisibility GetMultipleValuesVisibility() const;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> ResourceTypePropertyHandle;`
- L43 _private member_ `TSharedPtr<IPropertyHandle> MediaPlateResourcePropertyHandle;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> ExternalMediaPathPropertyHandle;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> MediaAssetPropertyHandle;`
- L46 _private member_ `TSharedPtr<IPropertyHandle> SourcePlaylistPropertyHandle;`

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/MediaPlateSphereGenerator.h` (Private)


#### class `FMediaPlateSphereGenerator`  
`class FMediaPlateSphereGenerator : public UE::Geometry::FMeshShapeGenerator`  
_L12-296_
- inherits: `UE::Geometry::FMeshShapeGenerator`
- desc: Generate a sphere mesh, with UVs wrapped cylindrically
- L16 _public member_ `double Radius = 1;` — Radius
- L18 _public member_ `double PhiRange = FMathd::Pi;` — Range for the vertical arc. 180 degrees for a sphere, etc...
- L20 _public member_ `double ThetaRange = FMathd::TwoPi;` — Range for the horizontal arc. 360 degrees for a sphere, etc...
- L22 _public member_ `int NumPhi = 3;` — number of vertices along vertical extent from north pole to south pole
- L23 _public member_ `int NumTheta = 3;` — number of vertices around circles
- L26 _public member_ `bool bPolygroupPerQuad = false;` — If true, each quad of box gets a separate polygroup
- L30 _private member_ `bool bIsClosed = false;` — True if this is a closed mesh, e.g. a sphere.
- L32 _private member_ `bool bHasPoles = false;` — True if we have the north and south poles.
- L34 _private function_ `static FVector3d SphericalToCartesian(double r, double theta, double phi)`
- L44 _private function_ `void GenerateVertices()`
- L94 _private function_ `void GenerateUVVertices()`
- L145 _private typedef_ `using CornerIndices = UE::Geometry::FVector3i;`
- L146 _private function_ `void OutputTriangle(int TriIdx, int PolyIdx, CornerIndices Corners, CornerIndices UVCorners)`
- L154 _private function_ `void OutputEquatorialTriangles()`
- L208 _private function_ `void OutputPolarTriangles()`
- L255 _public function_ `FMediaPlateSphereGenerator& Generate() override` — Generate the mesh

#### Free symbols / members of external scopes

- L48 _function_ `` (scope `FMediaPlateSphereGenerator::GenerateVertices`)

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Sequencer/MediaPlateTrackEditor.h` (Private)


#### class `FMediaPlateTrackEditor`  
`class FMediaPlateTrackEditor : public FMovieSceneTrackEditor`  
_L17-117_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for media plate.
- L28 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer)` — Create a new media plate track editor instance. @param OwningSequencer The sequencer object that will own the track editor. @return The new track editor.
- L38 _public prototype_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes();` — Get the list of all property types that this track editor animates. @return List of animated properties.
- L47 _public prototype_ `FMediaPlateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Create and initialize a new instance. @param InSequencer The sequencer object that owns this track editor.
- L50 _public prototype_ `virtual ~FMediaPlateTrackEditor();` — Virtual destructor.
- L55 _public prototype_ `virtual FText GetDisplayName() const override;`
- L56 _public prototype_ `virtual void BuildObjectBindingContextMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L57 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L58 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L60 _public prototype_ `virtual void OnRelease() override;`
- L66 _private prototype_ `bool HandleAddMediaTrackToObjectBindingMenuEntryCanExecute(TArray<FGuid> InObjectBindingID);` — Callback for enabling the action to add a media track to an object binding.
- L70 _private prototype_ `void HandleAddMediaTrackToObjectBindingMenuEntryExecute(TArray<FGuid> InObjectBindingID);` — Callback for adding a media track to an object binding.
- L74 _private prototype_ `void HandleActorAdded(AActor* Actor, FGuid TargetObjectGuid);` — Callback when an actor is added.
- L78 _private prototype_ `void AddTrackForComponent(UMediaPlateComponent* Component, FGuid TargetObjectGuid);` — Adds a track for this component.
- L83 _private prototype_ `void ImportObjectBinding(const TArray<FGuid> ObjectBindings);` — Adds tracks from an object binding.
- L90 _private prototype_ `void OnBuildOutlinerEditWidget(FMenuBuilder& MenuBuilder);` — Adds media plates to the MediaTrackEditor widget. @param MenuBuilder		Menu to add to.
- L97 _private prototype_ `void AddMediaPlateToSequencer(AActor* Actor);` — Adds a media plate to a Sequencer track. @param Actor			Media plate actor to add.
- L100 _private member_ `FDelegateHandle OnActorAddedToSequencerHandle;` — Handle to our delegate.
- L115 _private member_ `FDialogResponseInfo LastAutoPlayDisableResponse;`
- L116 _private member_ `FDialogResponseInfo LastAudioDisableResponse;`

#### struct `FMediaPlateTrackEditor::FDialogResponseInfo`  
`struct FDialogResponseInfo`  
_L105-113_
- desc: Information on the last dialog response.
- L108 _public member_ `FGuid ContextId;` — Keep track of the context id for the response to all during multiple operations.
- L110 _public member_ `bool bAll = false;` — True if the response applies to all in multiple operations under the same context id.
- L112 _public member_ `bool bApply = false;` — True if the operation should be done.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Toolkits/MediaPlateEditorToolkit.h` (Private)


#### class `FMediaPlateEditorToolkit`  
`class FMediaPlateEditorToolkit : public FAssetEditorToolkit , public FEditorUndoClient , public FGCObject`  
_L20-131_
- inherits: `FAssetEditorToolkit,FEditorUndoClient,FGCObject`
- desc: Implements an Editor toolkit for media plates.
- L31 _public prototype_ `FMediaPlateEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L34 _public prototype_ `virtual ~FMediaPlateEditorToolkit();` — Virtual destructor.
- L42 _public prototype_ `void Initialize(UMediaPlateComponent* InMediaPlate, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);` — Initializes the editor tool kit. @param InMediaPlate The media plate asset to edit. @param InMode The mode to create the toolkit in. @param InToolkitHost The toolkit host.
- L47 _public prototype_ `bool IsChannelMasked(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannel) const;` — Returns true if all the given channel mask is enabled.
- L52 _public prototype_ `void ToggleChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannelToToggle);` — Toggles the given mask in the channel mask.
- L55 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L56 _public prototype_ `virtual void OnClose() override;`
- L57 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L58 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L61 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L62 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L63 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L64 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L67 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L68 _public function_ `virtual FString GetReferencerName() const override`
- L76 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L77 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L80 _protected prototype_ `void BindCommands();` — Binds the UI commands to delegates.
- L83 _protected prototype_ `void ExtendToolBar();` — Builds the toolbar widget for the media player editor.
- L90 _protected prototype_ `float GetForwardRate() const;` — Gets the playback rate for fast forward. @return Forward playback rate.
- L97 _protected prototype_ `float GetReverseRate() const;` — Gets the playback rate for reverse. @return Reverse playback rate.
- L101 _private member_ `TObjectPtr<UMediaPlateComponent> MediaPlate;` — The media plate asset being edited.
- L104 _private member_ `TSharedRef<ISlateStyle> Style;` — Pointer to the style set to use for toolkits.
- L107 _private member_ `TSharedPtr<SMediaPlayerEditorViewer> Viewer;` — The tab which displays the media.
- L110 _private prototype_ `bool CanHandleMediaPlateEvent(EMediaPlateEventState InState);` — Callback to validate playback button events.
- L113 _private prototype_ `void HandleMediaPlateEvent(EMediaPlateEventState InState);` — Callback to handle playback button events.
- L116 _private prototype_ `bool CanHandleMediaPlateTogglePlayPauseEvent();` — Callback specifically to validate the toggle between play and pause.
- L119 _private prototype_ `void HandleMediaPlateTogglePlayPauseEvent();` — Callback specifically for toggle play/pause which then triggers a play or pause event.
- L122 _private prototype_ `bool CanHandleMediaPlateTogglePlayReversePauseEvent();` — Callback specifically to validate the toggle between reverse play and pause.
- L125 _private prototype_ `void HandleMediaPlateTogglePlayReversePauseEvent();` — Callback specifically for toggle play/pause which then triggers a reverse play or pause event.
- L128 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);` — Callback for spawning tabs.
- L130 _private prototype_ `void OnActorDeleted(AActor* Actor);`

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Widgets/SMediaPlateEditorDetails.h` (Private)


#### class `SMediaPlateEditorDetails`  
`class SMediaPlateEditorDetails : public SCompoundWidget`  
_L15-38_
- inherits: `SCompoundWidget`
- desc: Implements the details panel of the MediaPlate asset editor.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMediaPlateEditorDetails)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlateComponent& InMediaPlate, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs		The declaration data for this widget. @param InMediaPlate	The MediaPlate to show the details for. @param InStyleSet	The style set to use.
- L37 _private member_ `TObjectPtr<UMediaPlateComponent> MediaPlate;` — Pointer to the MediaPlate that is being viewed.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Widgets/SMediaPlateEditorMaterial.h` (Private)


#### class `SMediaPlateEditorMaterial`  
`class SMediaPlateEditorMaterial : public SCompoundWidget`  
_L13-49_
- inherits: `SCompoundWidget`
- desc: Widget for editing materials with media plate.
- L17 _public function_ `SLATE_BEGIN_ARGS(SMediaPlateEditorMaterial)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMaterialItemView>& InMaterialItemView, UActorComponent* InCurrentComponent);` — Construct this widget. @param InArgs				The declaration data for this widget. @param InMaterialItemView	Material view. @param InCurrentComponent	component that is using the material.
- L35 _private prototype_ `FReply OnBrowseMaterial() const;` — Callback for when we browse a material.
- L40 _private prototype_ `TSharedRef<SWidget> OnGetMaterials();` — Callback to get a list of media plate materials.
- L45 _private prototype_ `void OnSelectMaterial(FAssetData AssetData) const;` — Callback for when we select a material.
- L48 _private member_ `TWeakObjectPtr<AMediaPlate> MediaPlate = nullptr;` — Weak pointer to current component using the current material

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Widgets/SMediaPlateEditorMediaDetails.h` (Private)


#### class `SMediaPlateEditorMediaDetails`  
`class SMediaPlateEditorMediaDetails : public SMediaPlayerEditorMediaDetails`  
_L16-43_
- inherits: `SMediaPlayerEditorMediaDetails`
- desc: Implements the details panel of the MediaPlate asset editor.
- L21 _public function_ `SLATE_BEGIN_ARGS(SMediaPlateEditorMediaDetails)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlateComponent& InMediaPlate);` — Construct this widget. @param InArgs		The declaration data for this widget. @param InMediaPlate	The MediaPlate to show the details for.
- L36 _protected prototype_ `virtual UMediaPlayer* GetMediaPlayer() const override;`
- L37 _protected prototype_ `virtual UMediaTexture* GetMediaTexture() const override;`
- L42 _private member_ `TWeakObjectPtr<UMediaPlateComponent> MediaPlate;` — Pointer to the MediaPlate that is being viewed.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Private/Widgets/SMediaPlateEditorPlaylist.h` (Private)


#### class `SMediaPlateEditorPlaylist`  
`class SMediaPlateEditorPlaylist : public SMediaPlaylistEditorTracks`  
_L12-38_
- inherits: `SMediaPlaylistEditorTracks`
- desc: Implements the playlist panel of the MediaPlate asset editor.
- L17 _public function_ `SLATE_BEGIN_ARGS(SMediaPlateEditorPlaylist)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlateComponent& InMediaPlate, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs		The declaration data for this widget. @param InMediaPlate	The MediaPlate to show the details for. @param InStyleSet	The style set to use.
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L37 _private member_ `TWeakObjectPtr<UMediaPlateComponent> MediaPlate;` — Pointer to the MediaPlate that is being viewed.

### `Plugins/Media/MediaPlate/Source/MediaPlateEditor/Public/MediaPlateEditorModule.h` (Public)


#### class `FMediaPlateEditorModule`  
`class FMediaPlateEditorModule : public IModuleInterface, public FTickableEditorObject`  
_L24-143_
- inherits: `IModuleInterface,FTickableEditorObject`
- L29 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L34 _public function_ `virtual TStatId GetStatId() const override`
- L39 _public prototype_ `void MediaPlateStartedPlayback(TObjectPtr<UMediaPlateComponent> MediaPlate);` — Call this when a media plate starts playing so we can track it.
- L49 _public prototype_ `bool RemoveMediaSourceFromDragDropCache(UMediaSource* MediaSource);` — Call this if you want to check if your media source is a drag and drop media source. If it is, then this will remove it from this module and you can then change the outer (as it will be transient.) @param MediaSource	Media source to check. @return				True if it is a drag and drop media source.
- L55 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetMediaPlateMaterialAssetPaths, TArray<FName>& );` — Delegate called when getting the media plate materials asset paths. This allows for additional plugins to provide new media plate material templates.
- L56 _public prototype_ `FOnGetMediaPlateMaterialAssetPaths& OnGetMediaPlateMaterialAssetPaths();`
- L61 _private member_ `FName MediaPlateName;` — Customization names to avoid reusing staticstruct during shutdown.
- L62 _private member_ `FName MediaPlateResourceName;`
- L65 _private member_ `TArray<TWeakObjectPtr<UMediaPlateComponent>> ActiveMediaPlates;` — Holds all the media plates that are playing.
- L68 _private member_ `FOnGetMediaPlateMaterialAssetPaths OnGetMediaPlateMaterialAssetPathsDelegate;` — Event Delegate for OnGetMediaPlateMaterialAssetPaths.
- L71 _private member_ `FDelegateHandle TrackEditorBindingHandle;` — Handle for our track editor.
- L74 _private member_ `TMap<FString, TWeakObjectPtr<UMediaSource>> MapFileToMediaSource;` — Maps a drag and drop file to a media source we created from it.
- L76 _private member_ `bool bIsRealTimeViewportsEnabled = false;` — Caches if real time viewports are enabled.
- L78 _private member_ `TArray<TOptional<FPlacementModeID>> PlaceActors;` — Stores what we have aded to the placement module.
- L81 _private member_ `FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors LevelViewportContextMenuRemoteControlExtender;` — Holds the context menu extender.
- L84 _private member_ `FDelegateHandle MenuExtenderDelegateHandle;` — Holds the menu extender delegate handle.
- L89 _private prototype_ `const FPlacementCategoryInfo* GetMediaCategoryRegisteredInfo() const;` — Gathers the Info on the Media Plate Place Actors Category.
- L94 _private prototype_ `void RegisterPlacementModeItems();` — Register items to show up in the Place Actors panel.
- L99 _private prototype_ `void RegisterSectionMappings();` — Register which categories belong to which section.
- L104 _private prototype_ `void UnregisterPlacementModeItems();` — Unregister items in Place Actors panel.
- L109 _private prototype_ `void OnPostEngineInit();` — Called after the engine has initialized.
- L117 _private prototype_ `void ExtractAssetDataFromFiles(const TArray<FString>& Files, TArray<FAssetData>& AssetDataArray);` — Extracts an asset for a file if it can. @param Files				Files to get the asset from. @param AssetDataArray	Will add the asset here if it gets one.
- L122 _private prototype_ `void ForceRealTimeViewports(const bool bEnable);` — Enables real time viewports so media plates can update in the editor.
- L127 _private prototype_ `TSharedRef<FExtender> ExtendLevelViewportContextMenuForMediaPlate(const TSharedRef<FUICommandList> CommandList, TArray<AActor*> SelectedActors);` — Handle adding the menu extender for the actors.
- L132 _private prototype_ `void RegisterContextMenuExtender();` — Create all required callbacks for context menu's widget and button creation.
- L137 _private prototype_ `void UnregisterContextMenuExtender();` — Release context menu related resources such as handles.
- L142 _private prototype_ `void OnLevelActorAdded(AActor* InActor);` — Called when an Actor has been added to a Level

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlateEditor, Log, All);` — Log category for this module.
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlateEditor, Log, All);` — Log category for this module.
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetMediaPlateMaterialAssetPaths, TArray<FName>& );` — Delegate called when getting the media plate materials asset paths. This allows for additional plugins to provide new media plate material templates.
