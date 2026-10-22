# Plugins / MediaFrameworkUtilitiesEditor

- module root: `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor`
- headers: 35; symbols: 919
- symbol kinds: class=52, delegate=6, enum=5, enumerator=20, function=136, macro=2, member=241, namespace=11, prototype=424, struct=14, typedef=8
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ClassViewer, CommonMenuExtensions, ContentBrowser, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, Json, JsonUtilities, LevelEditor, MainFrame, MaterialEditor, MediaAssets, MediaFrameworkUtilities, MediaIOCore, MediaIOEditor, MediaPlayerEditor, MediaProfile, MediaProfileEditor, MediaUtils, PlacementMode, PropertyEditor, RenderCore, SharedSettingsWidgets, Slate, SlateCore, TimeManagement, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: PropertyEditor

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetDefinition/AssetDefinition_MediaBundle.h` (Private)


#### class `UAssetDefinition_MediaBundle`  
`class UAssetDefinition_MediaBundle : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetDefinition/AssetDefinition_MediaProfile.h` (Private)


#### class `UAssetDefinition_MediaProfile`  
`class UAssetDefinition_MediaProfile : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/DummyMediaObject.h` (Private)


#### class `UDummyMediaSource`  
`class UDummyMediaSource : public UMediaSource`  
_L13-24_
- reflection: `UCLASS(HideCategories=("Media|MediaSource"))`
- inherits: `UMediaSource`
- desc: Placeholder to use in the details panel when the media profile has a null media source in its list of media sources
- L18 _public function_ `virtual FString GetUrl() const override`
- L19 _public function_ `virtual bool Validate() const override`
- L23 _public member_ `int32 MediaProfileIndex = INDEX_NONE;` — Index of the media source in the media profile's media sources list that this dummy represents

#### class `UDummyMediaOutput`  
`class UDummyMediaOutput : public UMediaOutput`  
_L28-39_
- reflection: `UCLASS(HideCategories=("Output", "Media|Output"))`
- inherits: `UMediaOutput`
- desc: Placeholder to use in the details panel when the media profile has a null media output in its list of media outputs
- L33 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L34 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L38 _public member_ `int32 MediaProfileIndex = INDEX_NONE;` — Index of the media output in the media profile's media outputs list that this dummy represents

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaBundleEditorToolkit.h` (Private)


#### class `FMediaBundleEditorToolkit`  
`class FMediaBundleEditorToolkit : public FAssetEditorToolkit`  
_L15-56_
- inherits: `FAssetEditorToolkit`
- desc: Viewer/editor for a MediaBundle
- L18 _private typedef_ `using Super = FAssetEditorToolkit;`
- L21 _public prototype_ `static TSharedRef<FMediaBundleEditorToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UMediaBundle* InMediaBundle);`
- L30 _public prototype_ `void InitMediaBundleEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UMediaBundle* InMediaBundle);` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InMediaBundle			The MediaBundle asset to edit
- L31 _public prototype_ `~FMediaBundleEditorToolkit();`
- L34 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L35 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L36 _public prototype_ `virtual FText GetToolkitName() const override;`
- L37 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L38 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L39 _public prototype_ `virtual void RemoveEditingObject(UObject* Object) override;`
- L41 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L42 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L45 _public prototype_ `class UMediaBundle* GetMediaBundle() const;` — Get the MediaBundle Asset being edited
- L48 _private prototype_ `void HandleAssetPostImport(UFactory* InFactory, UObject* InObject);`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `void ExtendToolBar();`
- L55 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details view

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileCommands.h` (Private)


#### class `FMediaProfileCommands`  
`class FMediaProfileCommands : public TCommands<FMediaProfileCommands>`  
_L12-48_
- inherits: `TCommands<FMediaProfileCommands>`
- L16 _public function_ `FMediaProfileCommands() : TCommands<FMediaProfileCommands>(TEXT("ToolbarIcon"), NSLOCTEXT("Contexts", "ToolbarIcon", "Media Profile"), NAME_None, FMediaFrameworkUtilitiesEditorStyle::GetStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L26 _public member_ `TSharedPtr<FUICommandInfo> Apply;` — Applies changes to the original Media Profile.
- L29 _public member_ `TSharedPtr<FUICommandInfo> Edit;` — Edit the current Media Profile.
- L32 _public member_ `TSharedPtr<FUICommandInfo> ClearCurrentMediaProfile;` — Clears out the current media profile
- L35 _public member_ `TSharedPtr<FUICommandInfo> SaveLayout;` — Saves the current media profile editor layout
- L38 _public member_ `TSharedPtr<FUICommandInfo> SaveLayoutAs;` — Saves the current media profile editor layout
- L41 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllLayouts;` — Removes all media profile editor layouts
- L44 _public member_ `TSharedPtr<FUICommandInfo> ToggleFullscreen;` — Toggles fullscreen mode on the media profile editor window
- L47 _public member_ `TSharedPtr<FUICommandInfo> Immersive;` — Makes the media profile editor's viewport immersive

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileEditor.h` (Private)


#### class `FMediaProfileEditor`  
`class FMediaProfileEditor : public FAssetEditorToolkit`  
_L23-204_
- inherits: `FAssetEditorToolkit`
- desc: Media profile editor 2.0, which replaces the old, simple editor with a more robust one
- L26 _private member_ `static const FName AppName;`
- L27 _private member_ `static const FName MediaOutputTabId;`
- L28 _private member_ `static const FName MediaTreeTabId;`
- L29 _private member_ `static const FName DetailsTabId;`
- L30 _private member_ `static const FName TimecodeTabId;`
- L32 _private member_ `static const FString DefaultLayoutName;`
- L38 _public prototype_ `static TSharedRef<FMediaProfileEditor> CreateMediaProfileEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMediaProfile* InMediaProfile);`
- L40 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMediaProfile* InMediaProfile);`
- L45 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — IToolkit interface
- L46 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L50 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L51 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L52 _public prototype_ `virtual FText GetToolkitName() const override;`
- L53 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L54 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L55 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L56 _public prototype_ `virtual bool CanSaveAsset() const override;`
- L57 _public prototype_ `virtual bool IsSaveAssetVisible() const override;`
- L58 _public prototype_ `virtual bool IsFindInContentBrowserButtonVisible() const override;`
- L59 _public prototype_ `virtual UE::Editor::Toolbars::ECreateStatusBarOptions GetStatusBarCreationOptions() const override;`
- L63 _public function_ `UMediaProfile* GetMediaProfile() const` — Gets the media profile being edited
- L66 _public prototype_ `bool IsEditingTransientProfile() const;` — Returns true if the profile being edited is a transient (in-memory) profile, e.g. in Live Link Hub.
- L69 _public prototype_ `void CloseAllMediaSources();` — Closes all open media sources in the media profile
- L72 _public prototype_ `void CloseAllMediaOutputs();` — Closes all open media outputs in the media profile
- L75 _public prototype_ `bool CanMediaOutputCapture(UMediaOutput* InMediaOutput) const;` — Determines if the specified media output is properly configured for capturing
- L78 _public prototype_ `void RestartActiveMediaCaptures(UMediaOutput* InMediaOutput);` — Restart any active media captures for the specified media output
- L81 _public prototype_ `static UMediaProfileEditorCaptureSettings* GetMediaFrameworkCaptureSettings();` — Gets the media capture settings config object
- L84 _public function_ `FOnCaptureMethodChanged& GetOnCaptureMethodChanged()` — Gets the delegate that is raised when the capture method is changed through the details panel for a media output
- L88 _private prototype_ `TSharedRef<FTabManager::FLayout> GetDefaultLayout() const;` — Creates the default layout to use for the media profile editor
- L90 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MediaOutput(const FSpawnTabArgs& InArgs);`
- L91 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MediaTree(const FSpawnTabArgs& InArgs);`
- L92 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& InArgs);`
- L93 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Timecode(const FSpawnTabArgs& InArgs);`
- L96 _private prototype_ `void OpenTab(FName InTabId);` — Raised when something has requested that a tab be manually opened/focused
- L99 _private prototype_ `void BindCommands();` — Binds commands to the asset editor's command list
- L101 _private prototype_ `void ExtendToolbar();`
- L104 _private prototype_ `void ExtendWindowMenu();` — Registers the editor's tab spawners in the host application's Window menu (e.g. LiveLinkHub)
- L107 _private prototype_ `void PopulateWindowMenu(class FMenuBuilder& MenuBuilder, class UToolMenu*);` — Populates the host Window menu with this editor's tab spawners
- L110 _private prototype_ `void RefreshSelectedMediaItems(const TArray<int32>& InMediaSources,const TArray<int32>& InMediaOutputs);` — Refreshes the selected media items, reopening media sources and outputs
- L113 _private prototype_ `void CleanUpAndSaveUserSettings();` — Cleans up and saves the media profile editor user settings config
- L116 _private prototype_ `FText GetIsCurrentMediaProfileLabel() const;` — Gets the label used to indicate if the media profile being edited is set as the current editor media profile
- L119 _private prototype_ `TSharedRef<SWidget> CreateCurrentProfileMenu();` — Creates the dropdown menu for the "Current" profile toolbar button
- L122 _private prototype_ `void MakeCurrentMediaProfile();` — Makes the media profile being edited the currently active media profile
- L125 _private prototype_ `void ClearCurrentMediaProfile();` — Clears the media profile being edited from being the currently active media profile
- L128 _private prototype_ `bool CanClearCurrentMediaProfile() const;` — Gets whether the media profile being edited can be cleared from being the currently active media profile
- L130 _private prototype_ `TSharedRef<SWidget> CreateLayoutMenu();`
- L133 _private prototype_ `FText GetActiveLayoutText(FText Prefix, bool bDirtyFlag) const;` — Gets the text to display in the layouts menu for the currently active layout
- L136 _private prototype_ `void SaveLayout();` — Raised when the 'Save Layout' menu entry is clicked in the Layouts dropdown
- L139 _private prototype_ `bool CanSaveLayout() const;` — Gets whether the 'Save Layout' menu entry can be used on the current layout
- L142 _private prototype_ `void SaveLayoutAs();` — Raised when the 'Save Layout As' menu entry is clicked in the Layouts dropdown
- L145 _private prototype_ `bool CanSaveLayoutAs() const;` — Gets whether the 'Save Layout As' menu entry can be used on the current layout
- L148 _private prototype_ `void LoadLayout(FString LayoutName);` — Raised when a specific layout is selected to load in the Layouts dropdown
- L151 _private prototype_ `bool IsLayoutLoaded(FString LayoutName) const;` — Gets whether the layout of the specified name is the currently active layout
- L154 _private prototype_ `void RemoveLayout(FString LayoutName);` — Removes the layout of the specified name from the list of saved layouts
- L157 _private prototype_ `void RemoveAllLayouts();` — Removes all saved layouts
- L160 _private prototype_ `void ToggleFullscreen();` — Toggles fullscreen mode on the window that contains the media profile editor
- L163 _private prototype_ `bool IsFullscreen() const;` — Gets whether the window containing the media profile editor is in fullscreen mode or not
- L166 _private prototype_ `void SetViewportImmersive();` — Sets the media profile editor viewport to immersive mode
- L169 _private prototype_ `void OnPersistLayout(const TSharedRef<FTabManager::FLayout>& LayoutToSave);` — Raised when the tab manager for this editor tries to save the current tab layout to config
- L171 _private prototype_ `void OnMediaItemDeleted(UClass* InMediaType, int32 InMediaItemIndex);`
- L172 _private prototype_ `void OnSelectedMediaItemsChanged(const TArray<int32>& SelectedMediaSources, const TArray<int32>& SelectedMediaOutputs);`
- L174 _private prototype_ `void OnMapChange(uint32 InMapFlags);`
- L175 _private prototype_ `void OnLevelActorsRemoved(AActor* InActor);`
- L176 _private prototype_ `void OnAssetsDeleted(const TArray<UClass*>& DeletedAssetClasses);`
- L177 _private prototype_ `void OnObjectPreEditChange(UObject* Object, const FEditPropertyChain& PropertyChain);`
- L178 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L182 _private member_ `TObjectPtr<UMediaProfile> MediaProfileBeingEdited;` — The media profile being edited by this editor
- L184 _private member_ `TSharedPtr<SMediaProfileDetailsPanel> DetailsPanel;`
- L185 _private member_ `TSharedPtr<SMediaProfileViewport> ViewportPanel;`
- L188 _private member_ `TSharedPtr<SMediaFrameworkTimecodeGenlockHeader> TimecodeToolbarEntry;` — Timecode/Genlock header widget that is displayed in the editor's primary toolbar
- L191 _private member_ `TSet<TWeakObjectPtr<UMediaOutput>> OutputsToRestartCapture;` — List of media outputs whose capture needs to be restarted on the next engine tick
- L194 _private member_ `bool bActiveLayoutDirty = false;` — Indicates if the currently active layout has been dirtied and can be saved
- L197 _private member_ `FOnCaptureMethodChanged OnCaptureMethodChanged;` — Raised when the capture method is changed on a media output through the details panel
- L200 _private member_ `FTimerHandle RestartCapturesTimerHandle;` — Handle for callback to restart any modified captures on the next engine tick
- L203 _private member_ `bool bRegisteredWindowMenuEntries = false;` — Whether this editor registered entries in the host application's Window menu

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCaptureMethodChanged, UMediaOutput*) public: static TSharedRef<FMediaProfileEditor> CreateMediaProfileEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMediaProfile* InMediaProfile);`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileEditorUserSettings.h` (Private)


#### enum `EMediaImageRotation`  
`enum class EMediaImageRotation`  
_L12-18_
- reflection: `UENUM()`
- desc: Rotation of the displayed media image in the media profile editor
- L14 _public enumerator_ `None UMETA(DisplayName = "0°")`
- L15 _public enumerator_ `CW90 UMETA(DisplayName = "90°")`
- L16 _public enumerator_ `CCW90 UMETA(DisplayName = "-90°")`
- L17 _public enumerator_ `CW180 UMETA(DisplayName = "180°")`

#### struct `FMediaProfileEditorPerMediaItemSettings`  
`struct FMediaProfileEditorPerMediaItemSettings`  
_L22-50_
- reflection: `USTRUCT()`
- desc: Settings for a media source/output in the media profile editor
- L29 _public member_ `int32 ColorChannelMask = INDEX_NONE;` — `UPROPERTY(Config)` — The saved color channel mask applied to the media source/output
- L33 _public member_ `bool bInvertAlphaChannelMask = false;` — `UPROPERTY(Config)` — The saved invert alpha flag applied to the media source/output
- L37 _public member_ `bool bDrawAlphaBlendedCheckerboard = false;` — `UPROPERTY(Config)` — The saved draw checkerboard flag applied to the media source/output
- L41 _public member_ `EMediaImageRotation Rotation = EMediaImageRotation::None;` — `UPROPERTY(Config)` — The rotation of the media image in the viewport
- L45 _public member_ `bool bFlipHorizontal = false;` — `UPROPERTY(Config)` — Whether the media image is flipped horizontally
- L49 _public member_ `bool bFlipVertical = false;` — `UPROPERTY(Config)` — Whether the media image is flipped vertically

#### struct `FMediaProfileEditorLayoutPanelSettings`  
`struct FMediaProfileEditorLayoutPanelSettings`  
_L53-64_
- reflection: `USTRUCT()`
- L59 _public member_ `FString MediaItemName;` — `UPROPERTY(Config)` — The name of the media item being displayed in the panel
- L63 _public member_ `bool bMediaSource = false;` — `UPROPERTY(Config)` — Whether the media item being displayed is a media source or media output

#### struct `FMediaProfileEditorLayoutSettings`  
`struct FMediaProfileEditorLayoutSettings`  
_L67-90_
- reflection: `USTRUCT()`
- L73 _public member_ `FString Name;` — `UPROPERTY(Config)` — The name of the saved layout
- L77 _public member_ `FString Layout;` — `UPROPERTY(Config)` — The stringified FTabManager::FLayout of the saved layout
- L81 _public member_ `uint8 ViewportLayout = 0;` — `UPROPERTY(Config)` — A flag that indicates which panel arrangement the viewport has for the layout
- L85 _public member_ `uint8 ViewportOrientation = 0;` — `UPROPERTY(Config)` — A flag that indicates which panel orientation the viewport has for the layout
- L89 _public member_ `TArray<FMediaProfileEditorLayoutPanelSettings> Panels;` — `UPROPERTY(Config)` — A list of panel contents the viewport has for the layout

#### class `UMediaProfileEditorUserSettings`  
`class UMediaProfileEditorUserSettings : public UObject`  
_L94-130_
- reflection: `UCLASS(MinimalAPI, Config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Config class to store editor user settings for the media profile editor
- L101 _public member_ `bool bShowTimecodeInViewportToolbar = true;` — `UPROPERTY(Config)` — Whether to show the timecode entry in the viewport toolbar
- L105 _public member_ `bool bShowTimecodeInEditorToolbar = true;` — `UPROPERTY(Config)` — Whether to show the timecode entry in the main editor toolbar
- L109 _public member_ `bool bShowGenlockInViewportToolbar = true;` — `UPROPERTY(Config)` — Whether to show the genlock entry in the viewport toolbar
- L113 _public member_ `bool bShowGenlockInEditorToolbar = true;` — `UPROPERTY(Config)` — Whether to show the genlock entry in the main editor toolbar
- L117 _public member_ `bool bShowChannelsInViewportToolbar = true;` — `UPROPERTY(Config)` — Whether to show the Channels menu in the viewports
- L121 _public member_ `TMap<FName, FMediaProfileEditorPerMediaItemSettings> PerMediaItemSettings;` — `UPROPERTY(Config)` — Config settings specific to individual media sources/outputs, indexed by the media item's name
- L125 _public member_ `TArray<FMediaProfileEditorLayoutSettings> SavedLayouts;` — `UPROPERTY(Config)` — A list of user-created layouts for the media profile editor
- L129 _public member_ `FString ActiveLayout;` — `UPROPERTY(Config)` — The currently active layout for the media profile editor

#### class `UMediaProfileEditorCaptureSettings`  
`class UMediaProfileEditorCaptureSettings : public UMediaFrameworkWorldSettingsAssetUserData`  
_L136-144_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UMediaFrameworkWorldSettingsAssetUserData`
- desc: Variant of the media capture settings config for media outputs in the media profile
- L143 _public member_ `bool bAutoRestartCaptureOnChange = true;` — `UPROPERTY(config)` — Should the capture be restarted if the media output is modified.

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileMediaItemDetailCustomization.h` (Private)


#### class `FMediaProfileMediaItemDetailCustomization`  
`template<typename TMediaType> class FMediaProfileMediaItemDetailCustomization : public IDetailCustomization`  
_L33-328_
- inherits: `IDetailCustomization`
- desc: Base class for a details panel customization for a media source or output within a media profile. Displays an additional category that contains a editable label field and a type dropdown that allows the user to change the media item's type
- L57 _public function_ `FMediaProfileMediaItemDetailCustomization(TWeakPtr<FMediaProfileEditor>& InMediaProfileEditor, UMediaProfile* InMediaProfile, FSimpleDelegate InOnObjectsChanged)`
- L64 _public function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L70 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`
- L146 _protected function_ `void AddSectionsForEachCategory(IDetailLayoutBuilder& DetailBuilder, FPropertyEditorModule& PropertyModule)` — Registers sections to the root media item type for each category being displayed in the details panel if one does not yet exist
- L166 _protected prototype_ `virtual FText GetMediaItemTypeText() const = 0;`
- L169 _protected prototype_ `virtual void RegisterMediaTypeSection(FPropertyEditorModule& PropertyModule, const FName& MediaTypeCategory) = 0;` — Registers a section for the custom media type category under the type specific name
- L171 _protected function_ `EVisibility GetValidObjectVisibility() const`
- L184 _protected function_ `FText GetLabelText() const`
- L203 _protected function_ `bool IsLabelTextBoxEnabled() const`
- L211 _protected function_ `void OnLabelTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo)`
- L229 _protected function_ `TSharedRef<SWidget> GetClassPickerMenuContent()`
- L242 _protected function_ `void OnClassPicked(UClass* InClass)`
- L268 _protected function_ `const FSlateBrush* GetClassIcon() const`
- L286 _protected function_ `FText GetClassName() const`
- L309 _protected prototype_ `virtual FText GetMediaObjectLabel(TMediaType* InMediaObject) const = 0;`
- L310 _protected prototype_ `virtual void SetMediaObjectLabel(TMediaType* InMediaObject, const FText& InLabel) = 0;`
- L311 _protected prototype_ `virtual void SetMediaObject(TMediaType* InOriginalMediaObject, TMediaType* InNewMediaObject) = 0;`
- L315 _protected member_ `TWeakPtr<FMediaProfileEditor> MediaProfileEditor;` — Media profile editor that owns the details panel being customized by this customization
- L318 _protected member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;` — Media profile that owns the media sources or outputs whose details panel is being customized
- L321 _protected member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — Cached detail layout builder pointer, used to manually refresh the details panel
- L324 _protected member_ `TSharedPtr<SComboButton> ClassPickerComboButton;` — Combo button that displays the types that the media item can be changed to
- L327 _protected member_ `FSimpleDelegate OnObjectsChanged;` — Delegate that is raised when the media items' type is changed

#### class `FMediaProfileMediaItemDetailCustomization::FMediaTypeClassFilter`  
`class FMediaTypeClassFilter : public IClassViewerFilter`  
_L36-54_
- inherits: `IClassViewerFilter`
- L39 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override`
- L50 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override`

#### class `FMediaProfileMediaSourceDetailCustomization`  
`class FMediaProfileMediaSourceDetailCustomization : public FMediaProfileMediaItemDetailCustomization<UMediaSource>`  
_L333-358_
- inherits: `FMediaProfileMediaItemDetailCustomization<UMediaSource>`
- desc: Details panel customization for media sources
- L336 _public function_ `FMediaProfileMediaSourceDetailCustomization(TWeakPtr<FMediaProfileEditor>& InMediaProfileEditor, UMediaProfile* InMediaProfile, FSimpleDelegate InOnObjectsChanged) : FMediaProfileMediaItemDetailCustomization(InMediaProfileEditor, InMediaProfile, InOnObjectsChanged)`
- L340 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L343 _private prototype_ `virtual FText GetMediaItemTypeText() const override;`
- L344 _private prototype_ `virtual void RegisterMediaTypeSection(FPropertyEditorModule& PropertyModule, const FName& MediaTypeCategory) override;`
- L345 _private prototype_ `virtual FText GetMediaObjectLabel(UMediaSource* InMediaObject) const override;`
- L346 _private prototype_ `virtual void SetMediaObjectLabel(UMediaSource* InMediaObject, const FText& InLabel) override;`
- L347 _private prototype_ `virtual void SetMediaObject(UMediaSource* InOriginalMediaObject, UMediaSource* InNewMediaObject) override;`
- L350 _private prototype_ `bool ShowMediaPlayerOptions(UMediaSource* InSource) const;` — Gets whether the properties of the media player that is playing the media source should be displayed in the details panel
- L353 _private prototype_ `void AddMediaPlayerProperties(UMediaSource* InMediaSource, IDetailLayoutBuilder& DetailBuilder);` — Adds appropraite media player properties to the details panel of the media source being displayed
- L357 _private member_ `TWeakObjectPtr<UMediaPlayer> SourceMediaPlayer;` — Weak pointer to the media player of the media source being customized

#### class `FMediaProfileMediaOutputDetailCustomization`  
`class FMediaProfileMediaOutputDetailCustomization : public FMediaProfileMediaItemDetailCustomization<UMediaOutput>`  
_L363-393_
- inherits: `FMediaProfileMediaItemDetailCustomization<UMediaOutput>`
- desc: Details customization for media outputs. Adds a media capture category that displays the outputs' media capture settings
- L366 _public function_ `FMediaProfileMediaOutputDetailCustomization(TWeakPtr<FMediaProfileEditor>& InMediaProfileEditor, UMediaProfile* InMediaProfile, FSimpleDelegate InOnObjectsChanged) : FMediaProfileMediaItemDetailCustomization(InMediaProfileEditor, InMediaProfile, InOnObjectsChanged)`
- L372 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L375 _private prototype_ `virtual FText GetMediaItemTypeText() const override;`
- L376 _private prototype_ `virtual void RegisterMediaTypeSection(FPropertyEditorModule& PropertyModule, const FName& MediaTypeCategory) override;`
- L377 _private prototype_ `virtual FText GetMediaObjectLabel(UMediaOutput* InMediaObject) const override;`
- L378 _private prototype_ `virtual void SetMediaObjectLabel(UMediaOutput* InMediaObject, const FText& InLabel) override;`
- L379 _private prototype_ `virtual void SetMediaObject(UMediaOutput* InOriginalMediaObject, UMediaOutput* InNewMediaObject) override;`
- L382 _private prototype_ `void RegisterCaptureSection(FPropertyEditorModule& PropertyModule, const FName& CaptureCategory);` — Registers a section for the Capture category
- L384 _private prototype_ `void OnCaptureMethodChanged();`
- L385 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L392 _private member_ `TSharedPtr<FStructOnScopeStructureDataProvider> MediaCaptureStruct;` — Stored FStructOnScopes for the media capture structs of all objects being displayed by this customization, which are pulled from the currently active UMediaFrameworkWorldSettingsAssetUserData's ViewportCaptures and RenderTargetCaptures list

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "FMediaProfileMediaItemDetailCustomization"`
- L177 _function_ `` (scope `FMediaProfileMediaItemDetailCustomization::GetValidObjectVisibility`)

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMaskedMediaImage.h` (Private)


#### class `SMaskedMediaImage`  
`class SMaskedMediaImage : public SCompoundWidget`  
_L16-66_
- inherits: `SCompoundWidget`
- desc: Displays a media image texture with optional channel masking and alpha blending support
- L21 _public function_ `SLATE_BEGIN_ARGS(SMaskedMediaImage) : _IsAlphaPremultiplied(true) , _Rotation(0.0f) , _Scale(FVector2D(1.0f, 1.0f))`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, ImageSize) SLATE_ATTRIBUTE(EColorChannelMask, ChannelMask) SLATE_ATTRIBUTE(bool, InvertAlphaChannel) SLATE_ATTRIBUTE(bool, DrawCheckerboard) SLATE_ARGUMENT(bool, IsAlphaPremultiplied) SLATE_ATTRIBUTE(float, Rotation) SLATE_ATTRIBUTE(FVector2f, Scale) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UTexture* InMediaImageTexture);`
- L37 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L41 _private member_ `TStrongObjectPtr<UMaterialInstanceDynamic> Material;` — Material used to render the media image texture
- L44 _private member_ `TWeakObjectPtr<UTexture> MediaImageTexture;` — The texture the media image is being written to
- L47 _private member_ `TSharedPtr<FSlateBrush> MaterialBrush;` — Slate brush that wraps the material
- L50 _private member_ `TAttribute<FVector2D> ImageSizeAttr;` — Attribute used to size the media image appropriately
- L53 _private member_ `TAttribute<EColorChannelMask> ChannelMaskAttr;` — Attribute for the color channel to mask to
- L56 _private member_ `TAttribute<bool> InvertAlphaChannelAttr;` — Attribute for the invert alpha flag
- L59 _private member_ `TAttribute<bool> DrawCheckerboardAttr;` — Attribute for drawing the alpha-blended checkerboard background
- L62 _private member_ `TAttribute<float> RotationAttr;` — The 2D rotation of the image
- L65 _private member_ `TAttribute<FVector2f> ScaleAttr;` — The 2D scale of the image

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMediaProfileDetailsInfoPanel.h` (Private)


#### class `SMediaObjectInfoPanel`  
`class SMediaObjectInfoPanel : public SCompoundWidget`  
_L21-118_
- inherits: `SCompoundWidget`
- desc: Info panel that is displayed above the details panel, and displays a summary of a media item's configuration
- L42 _public function_ `SLATE_BEGIN_ARGS(SMediaObjectInfoPanel)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FMediaProfileEditor>& InMediaProfileEditor, UMediaProfile* InMediaProfile);`
- L50 _public prototype_ `void SetMediaObject(UObject* InMediaObject);` — Sets the media source or output whose information is being displayed in the panel
- L54 _private prototype_ `void SubscribeToDetectedConfigurationChanges(UObject* InMediaObject);` — Subscribe to the leaf source's auto-detected-format change delegate so we can refresh live.
- L56 _private prototype_ `void UnsubscribeFromDetectedConfigurationChanges();` — Unsubscribe from whatever source we last subscribed to (if any).
- L58 _private prototype_ `void OnDetectedConfigurationChanged();` — Handler for the broadcast that rebuilds the info panel contents.
- L61 _private member_ `TWeakObjectPtr<class UCaptureCardMediaSource> SubscribedCaptureSource;` — Source we are currently subscribed to and the handle of that subscription.
- L62 _private member_ `FDelegateHandle DetectedConfigurationChangedHandle;`
- L64 _private prototype_ `UMediaSource* ObjectAsMediaSource() const;`
- L65 _private prototype_ `UMediaOutput* ObjectAsMediaOutput() const;`
- L67 _private prototype_ `void ClearInfo();`
- L68 _private prototype_ `void FillInfo();`
- L70 _private prototype_ `TSharedRef<SWidget> CreateInfoGroupWidget(const TAttribute<FText>& InHeader, FTwoColumnInfo& InInfo);`
- L72 _private prototype_ `FText GetCaptureMethodText() const;`
- L73 _private prototype_ `FText GetCaptureObjectLabelText() const;`
- L74 _private prototype_ `FText GetCaptureObjectValueText() const;`
- L75 _private prototype_ `FText GetCaptureStatusText() const;`
- L76 _private prototype_ `FSlateColor GetCaptureStatusColor() const;`
- L77 _private prototype_ `FText GetCaptureColorConversionText() const;`
- L80 _private prototype_ `UMediaTexture* GetActivePreviewMediaTexture() const;` — Returns the live preview UMediaTexture that the profile's playback manager has opened for the displayed media source, if any.
- L82 _private prototype_ `UMediaPlayer* GetActivePreviewMediaPlayer() const;` — Returns the live preview UMediaPlayer driving the active preview UMediaTexture, if any.
- L84 _private prototype_ `FText GetStreamResolutionText() const;`
- L85 _private prototype_ `FText GetStreamFrameRateText() const;`
- L86 _private prototype_ `FText GetStreamFormatText() const;`
- L89 _private prototype_ `EActiveTimerReturnType RefreshStreamInfo(double InCurrentTime, float InDeltaTime);` — Active timer that drives periodic re-paint of StreamInfo while a media source is displayed.
- L93 _private member_ `TWeakPtr<FMediaProfileEditor> MediaProfileEditor;` — Media profile editor that owns this widget
- L96 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;` — Media profile that is being edited
- L99 _private member_ `TWeakObjectPtr<UObject> MediaObject;` — Media source or output whose info is being displayed
- L102 _private member_ `TSharedPtr<SHorizontalBox> MediaObjectInfoBox;` — Container for any extra columns of info
- L105 _private member_ `FTwoColumnInfo BasicInfo;` — Basic info column, which displays media object label and proxy status
- L108 _private member_ `FTwoColumnInfo TypeInfo;` — Column that displays details about the type of the media object
- L111 _private member_ `FTwoColumnInfo CaptureInfo;` — Column that displays details about the media capture settings if the object is a media output
- L114 _private member_ `FTwoColumnInfo StreamInfo;` — Column that displays runtime stream details when the displayed media source has an active preview player
- L117 _private member_ `TSharedPtr<FActiveTimerHandle> StreamInfoRefreshTimerHandle;` — Handle for the active timer that re-paints StreamInfo; valid only while the Stream Info group is shown.

#### struct `SMediaObjectInfoPanel::FTwoColumnInfo`  
`struct FTwoColumnInfo`  
_L25-39_
- desc: Helper struct to maintain two columns of widgets, one for labels and one for value content
- L28 _public prototype_ `TSharedRef<SWidget> CreateWidget();`
- L30 _public prototype_ `void AddEntry(TAttribute<FText> Label, TAttribute<FText> Value, TAttribute<FSlateColor> ValueColor = TAttribute<FSlateColor>());`
- L31 _public prototype_ `void AddEntry(TAttribute<FText> Value, const FSlateBrush* Icon);`
- L32 _public prototype_ `void AddEntry(TAttribute<FText> Value);`
- L34 _public prototype_ `void ClearEntries();`
- L37 _private member_ `TSharedPtr<SVerticalBox> LabelColumn;`
- L38 _private member_ `TSharedPtr<SVerticalBox> ValueColumn;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMediaProfileDetailsPanel.h` (Private)


#### class `SMediaProfileDetailsPanel`  
`class SMediaProfileDetailsPanel : public SCompoundWidget`  
_L16-79_
- inherits: `SCompoundWidget`
- desc: Details panel for the media profile's selected media sources and outputs
- L19 _public prototype_ `DECLARE_DELEGATE(FOnDetailsChanged);`
- L23 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileDetailsPanel)`
- L24 _public prototype_ `SLATE_EVENT(FOnDetailsChanged, OnDetailsChanged) SLATE_EVENT(FOnRefreshMediaItems, OnRefresh) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FMediaProfileEditor> InOwningEditor, UMediaProfile* InMediaProfile);`
- L35 _public prototype_ `void SetSelectedMediaItems(const TArray<int32>& InSelectedMediaSourceIndices, const TArray<int32>& InSelectedMediaOutputIndices);` — Sets the media items in the media profile to display in the details panel @param InSelectedMediaSourceIndices A list of indices of the media sources in the media profile to display @param InSelectedMediaOutputIndices A list of indices of the media outputs in the media profile to display
- L38 _private prototype_ `void RefreshDetailsView();`
- L41 _private prototype_ `void OnCaptureButtonPressed();` — Raised when the Start/Stop Capture button is pressed
- L44 _private prototype_ `const FSlateBrush* GetCaptureButtonImage() const;` — Gets the icon to display in the capture button, depending on if there is a live capture or not
- L47 _private prototype_ `FText GetCaptureButtonText() const;` — Gets the text to display in the capture button, depending on if there is a live capture or not
- L50 _private prototype_ `EVisibility GetCaptureButtonVisibility() const;` — Gets the visibility of the capture button, depending on the types of the objects being displayed in the details panel
- L53 _private prototype_ `bool IsCaptureButtonEnabled() const;` — Gets whether the capture button is enabled, depending on whether the selected outputs are properly configured to capture
- L57 _private member_ `TWeakPtr<FMediaProfileEditor> OwningEditor;` — The editor that owns this details panel
- L60 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;` — The media profile being edited by this editor
- L63 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details view to display the media source or output properties
- L66 _private member_ `TSharedPtr<SMediaObjectInfoPanel> InfoPanel;` — Panel to display info on the selected media objects
- L69 _private member_ `TArray<TStrongObjectPtr<UObject>> DummyMediaObjects;` — Strong pointers for any dummy objects needed to represent null media entries in the media profile
- L72 _private member_ `TArray<int32> SelectedMediaSources;` — Indices of the selected media sources within the media profile to display in the details panel
- L75 _private member_ `TArray<int32> SelectedMediaOutputs;` — Indices of the selected media outputs within the media profile to display in the details panel
- L78 _private member_ `FOnRefreshMediaItems OnRefresh;` — Raised when the refresh button is pressed

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE(FOnDetailsChanged);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRefreshMediaItems, const TArray<int32>& , const TArray<int32>& ) public: SLATE_BEGIN_ARGS(SMediaProfileDetailsPanel) {} SLATE_EVENT(FOnDetailsChanged, OnDetailsChanged) SLATE_EVENT(FOnRefreshMediaItems, OnRefresh) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FMediaProfileEditor> InOwningEditor, UMediaProfile* InMediaProfile);`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMediaProfileMediaItemDisplay.h` (Private)


#### class `UMediaProfileMediaItemDisplayContext`  
`class UMediaProfileMediaItemDisplayContext : public UObject`  
_L43-67_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Used as the context object for the viewport toolbar displayed at the top of each display, stores a reference to the viewport widget that is displaying the toolbar instance
- L49 _public function_ `template<typename T> TSharedPtr<T> GetDisplayWidget() const`
- L60 _public function_ `template<typename T> void SetDisplayWidget(const TSharedPtr<T>& InDisplayWidget)`
- L66 _private member_ `TWeakPtr<SWidget> DisplayWidget;`

#### class `SMediaProfileMediaItemDisplayBase`  
`template<typename TMediaItem> class SMediaProfileMediaItemDisplayBase : public SCompoundWidget`  
_L73-1289_
- inherits: `SCompoundWidget`
- desc: Widget to display the input or capture from a single media source or output
- L76 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileMediaItemDisplayBase)`
- L77 _public function_ `SLATE_ARGUMENT(TWeakPtr<FMediaProfileEditor>, MediaProfileEditor) SLATE_ARGUMENT(int32, PanelIndex) SLATE_ARGUMENT(int32, MediaItemIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SMediaProfileViewport>& InOwningViewport)`
- L134 _public function_ `virtual ~SMediaProfileMediaItemDisplayBase() override`
- L139 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L149 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L153 _protected prototype_ `virtual void ConfigureMediaImage() = 0;` — Performs any needed configuration to output the media item to the UI
- L156 _protected prototype_ `virtual TMediaItem* GetMediaItem() const = 0;` — Gets the typed media item being displayed
- L159 _protected prototype_ `virtual FText GetMediaItemLabel() const = 0;` — Gets the label to display for the media item
- L162 _protected prototype_ `virtual FText GetBaseMediaTypeLabel() const = 0;` — Gets the label for the base type of the media item (e.g. media source/media output)
- L164 _protected function_ `UMediaProfile* GetMediaProfile() const`
- L176 _protected function_ `virtual void AddToolbarEntries(FToolMenuSection& Section)` — Allows implementations to add their own entries to the viewport toolbar
- L179 _protected function_ `virtual void AppendToolbarCommandList(FToolMenuContext& Context)` — Allows implementations to add their own command lists to the viewport toolbar
- L182 _protected function_ `void BindCommands()` — Binds commands to the display's command list
- L276 _protected function_ `TSharedRef<SWidget> CreateToolbar()` — Creates the viewport display's toolbar
- L363 _protected function_ `FToolMenuEntry CreateMediaItemsComboButton()` — Creates the combo button used to change which media item is being displayed in the current panel
- L375 _protected function_ `void GetMediaItemsDropdownContent(UToolMenu* ToolMenu)` — Creates the dropdown list for the media items combo box, which lists all possible media items that can be displayed in the panel
- L454 _protected function_ `FToolMenuEntry CreateRotationSubmenu()`
- L498 _protected function_ `FToolMenuEntry CreateFlipSubmenu()`
- L565 _protected function_ `FToolMenuEntry CreateChannelsSubmenu(bool bUseFullLabel)`
- L686 _protected function_ `FToolMenuEntry CreateChannelsButton()`
- L711 _protected function_ `FToolMenuEntry CreateViewportArrangementMenu()` — Creates the viewport arrangement menu, which allows users to change the arrangement of panels in the viewport
- L789 _protected function_ `FToolMenuEntry CreateMaximizeViewportButton()` — Creates the menu entry to maximize this panel
- L819 _protected function_ `FToolMenuEntry CreateSettingsMenu()`
- L888 _protected function_ `virtual FText GetActiveMediaItemLabel() const` — Gets the label to display for this panel's content in the media items combo button
- L899 _protected function_ `virtual FSlateIcon GetActiveMediaItemIcon() const` — Gets the icon to display for this panel's content in the media items combo button
- L910 _protected function_ `virtual void ChangeActiveMediaItem(UClass* InMediaItemClass, int32 InMediaItemIndex)` — Raised when the user has selected a new media item in the media items combo button
- L925 _protected function_ `virtual bool CanTransformMediaItem() const` — Gets whether 2D visual transformations are allowed on the media item
- L931 _protected function_ `virtual EMediaImageRotation GetRotation()` — Gets the media item's rotation enum value
- L942 _protected function_ `virtual float GetRotationValue(bool bInDegrees = false) const` — Gets the media item's actual rotation value
- L971 _protected function_ `virtual ECheckBoxState GetRotationCheckState(EMediaImageRotation InRotation)` — Gets the check state for the specified rotation enum value for the media item
- L982 _protected function_ `virtual void SetRotation(EMediaImageRotation InRotation)` — Sets the media item's rotation
- L991 _protected function_ `virtual void GetFlipState(bool& bOutFlipHorizontal, bool& bOutFlipVertical)` — Gets the flip state of the media item
- L1004 _protected function_ `virtual ECheckBoxState GetFlipHorizontalCheckState()` — Gets the check state for the media item's horizontal flip state
- L1015 _protected function_ `virtual ECheckBoxState GetFlipVerticalCheckState()` — Gets the check state for the media item's vertical flip state
- L1026 _protected function_ `virtual void ToggleFlipHorizontal()` — Toggle's the media item's horizontal flip state
- L1035 _protected function_ `virtual void ToggleFlipVertical()` — Toggle's the media item's vertical flip state
- L1044 _protected function_ `virtual FVector2f GetScale() const` — Gets the scale transform that should be applied to the media item's visualization
- L1064 _protected function_ `virtual void ResetTransform()` — Resets any active transform on the media item
- L1075 _protected function_ `virtual bool CanResetTransform() const` — Gets whether the media item has a transformation that can be reset
- L1088 _protected function_ `virtual EColorChannelMask GetChannelMask() const` — Gets the current color channel being displayed in the viewport
- L1099 _protected function_ `virtual void SetChannelMask(EColorChannelMask InChannelMask)` — Sets the current color channel being displayed in the viewport
- L1108 _protected function_ `virtual bool IsChannelBeingMasked(EColorChannelMask InChannelMask)` — Gets whether the specified color channel is the one being masked to
- L1119 _protected function_ `virtual bool GetInvertAlphaChannelMask() const` — Gets whether the alpha color channel is inverted when displayed as the color channel mask
- L1130 _protected function_ `virtual void SetInvertAlphaChannelMask(bool bInInvertAlphaChannelMask)` — Gets whether the alpha color channel is inverted when displayed as the color channel mask
- L1139 _protected function_ `virtual bool CanInvertAlphaChannelMask() const` — Gets whether the display's alpha channel can be displayed as inverted or not
- L1145 _protected function_ `virtual bool GetDrawAlphaBlendedCheckerboard() const` — Gets whether to draw the alpha blended checkerboard background when rendering the viewport
- L1156 _protected function_ `virtual void SetDrawAlphaBlendedCheckerboard(bool bInDrawAlphaBlendedCheckerboard)` — Sets whether to draw the alpha blended checkerboard background when rendering the viewport
- L1164 _protected function_ `virtual bool IsDrawAlphaBlendedCheckerboardEnabled() const`
- L1170 _protected function_ `virtual bool CanShowAlphaCheckerboard() const` — Indicates whether the media item display can show the 'Visualize Alpha with Checkerboard' option in the toolbar dropdown menu
- L1176 _protected function_ `bool IsMaximized() const` — Gets whether this panel is currently maximized in the viewport
- L1188 _protected function_ `bool IsImmersive() const` — Gets whether this panel is currently immersive in the viewport
- L1200 _protected function_ `void ChangePanelContents(UClass* InMediaItemClass, int32 InMediaItemIndex, bool bRefreshDisplay)` — Changes the panel's contents, recreating the display widgets
- L1212 _protected function_ `void OnPanelLockToggled()` — Raised when the lock button is toggled
- L1224 _protected function_ `bool IsPanelLocked() const` — Gets whether this panel is locked or not
- L1230 _protected function_ `FSlateIcon GetLockIcon() const` — Gets the lock button icon
- L1237 _protected function_ `FMediaProfileEditorPerMediaItemSettings* GetMediaItemSettings() const`
- L1257 _protected function_ `virtual void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent)` — Raised when an object property is changed in the editor, used to potentially refresh the display if the displayed media item is modified
- L1272 _protected member_ `TWeakPtr<FMediaProfileEditor> MediaProfileEditor;` — The media profile editor that owns this display
- L1275 _protected member_ `TWeakPtr<SMediaProfileViewport> OwningViewport;` — The viewport widget that owns this display
- L1278 _protected member_ `int32 PanelIndex = INDEX_NONE;` — The index of the panel that is displaying this display
- L1281 _protected member_ `int32 MediaItemIndex = INDEX_NONE;` — The index of the media item being displayed by this display
- L1284 _protected member_ `TSharedPtr<FMediaFrameworkTimecodeGenlockToolMenuEntry> TimecodeGenlockToolMenuEntry;` — Entry for the media profile's timecode and genlock configuration to display in the viewport toolbar
- L1286 _protected member_ `TSharedPtr<SOverlay> Overlay;`
- L1287 _protected member_ `TSharedPtr<SBorder> MediaImageContainer;`
- L1288 _protected member_ `TSharedPtr<FUICommandList> CommandList;`

#### class `SMediaProfileMediaSourceDisplay`  
`class SMediaProfileMediaSourceDisplay : public SMediaProfileMediaItemDisplayBase<UMediaSource>`  
_L1294-1344_
- inherits: `SMediaProfileMediaItemDisplayBase<UMediaSource>`
- desc: Implementation of SMediaProfileMediaItemDisplayBase for media sources, which displays the live feed from the selected media source
- L1297 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileMediaSourceDisplay)`
- L1298 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FMediaProfileEditor>, MediaProfileEditor) SLATE_ARGUMENT(int32, PanelIndex) SLATE_ARGUMENT(int32, MediaItemIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SMediaProfileViewport>& InOwningViewport);`
- L1308 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L1312 _protected prototype_ `virtual void ConfigureMediaImage() override;`
- L1314 _protected prototype_ `virtual UMediaSource* GetMediaItem() const override;`
- L1315 _protected prototype_ `virtual FText GetMediaItemLabel() const override;`
- L1316 _protected prototype_ `virtual FText GetBaseMediaTypeLabel() const override;`
- L1317 _protected prototype_ `virtual bool CanTransformMediaItem() const override;`
- L1320 _private prototype_ `UMediaTexture* GetMediaTexture() const;`
- L1321 _private prototype_ `FVector2D GetSourceImageSize() const;`
- L1322 _private prototype_ `FOptionalSize GetSourceAspectRatio() const;`
- L1324 _private prototype_ `FText GetTimeDurationText() const;`
- L1325 _private prototype_ `FText GetFramerateText() const;`
- L1328 _private prototype_ `void SetupTileVisibilityProvider(UMediaTexture* InMediaTexture);` — Register a tile-visibility provider for InMediaTexture. Must be called before opening the media source.
- L1331 _private prototype_ `void TeardownTileVisibilityProvider();` — Symmetric counterpart to SetupTileVisibilityProvider. Idempotent; safe to call when nothing is registered.
- L1334 _private member_ `TSharedPtr<SMaskedMediaImage> MediaImage;` — The actual masked-image leaf widget; Tick reads its tick-space geometry to push the rendered size to the provider.
- L1337 _private member_ `TSharedPtr<UE::MediaPlayerEditor::FViewportTileVisibilityProvider, ESPMode::ThreadSafe> TileVisibilityProvider;` — Tile-visibility provider; Tick pushes the rendered viewport size into it each frame.
- L1340 _private member_ `TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe> TextureTrackerObject;` — FMediaTextureTracker bookkeeping for the provider. Registered against the playback manager's MediaTexture.
- L1343 _private member_ `TWeakObjectPtr<UMediaTexture> RegisteredMediaTexture;` — The MediaTexture we registered with on the tracker - kept so the dtor can unregister against the same one.

#### class `SMediaProfileMediaOutputDisplay`  
`class SMediaProfileMediaOutputDisplay : public SMediaProfileMediaItemDisplayBase<UMediaOutput>`  
_L1347-1415_
- inherits: `SMediaProfileMediaItemDisplayBase<UMediaOutput>`
- desc: Implementation of SMediaProfileMediaItemDisplayBase for media outputs, which displays the result from a media capture from the selected media output
- L1360 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileMediaOutputDisplay)`
- L1361 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FMediaProfileEditor>, MediaProfileEditor) SLATE_ARGUMENT(int32, PanelIndex) SLATE_ARGUMENT(int32, MediaItemIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SMediaProfileViewport>& InOwningViewport);`
- L1371 _protected prototype_ `virtual void ConfigureMediaImage() override;`
- L1373 _protected prototype_ `virtual UMediaOutput* GetMediaItem() const override;`
- L1374 _protected prototype_ `virtual FText GetMediaItemLabel() const override;`
- L1375 _protected prototype_ `virtual FText GetBaseMediaTypeLabel() const override;`
- L1377 _protected prototype_ `virtual bool CanTransformMediaItem() const override;`
- L1378 _protected prototype_ `virtual EMediaImageRotation GetRotation() override;`
- L1379 _protected prototype_ `virtual ECheckBoxState GetRotationCheckState(EMediaImageRotation InRotation) override;`
- L1380 _protected prototype_ `virtual float GetRotationValue(bool bInDegrees = false) const override;`
- L1381 _protected prototype_ `virtual void SetRotation(EMediaImageRotation InRotation) override;`
- L1382 _protected prototype_ `virtual void GetFlipState(bool& bOutFlipHorizontal, bool& bOutFlipVertical) override;`
- L1383 _protected prototype_ `virtual ECheckBoxState GetFlipHorizontalCheckState() override;`
- L1384 _protected prototype_ `virtual ECheckBoxState GetFlipVerticalCheckState() override;`
- L1385 _protected prototype_ `virtual void ToggleFlipHorizontal() override;`
- L1386 _protected prototype_ `virtual void ToggleFlipVertical() override;`
- L1387 _protected prototype_ `virtual FVector2f GetScale() const override;`
- L1388 _protected prototype_ `virtual void ResetTransform() override;`
- L1389 _protected prototype_ `virtual bool CanResetTransform() const override;`
- L1391 _protected prototype_ `virtual void SetChannelMask(EColorChannelMask InChannelMask) override;`
- L1392 _protected prototype_ `virtual void SetInvertAlphaChannelMask(bool bInInvertAlphaChannelMask) override;`
- L1393 _protected function_ `virtual bool CanInvertAlphaChannelMask() const override`
- L1394 _protected prototype_ `virtual void SetDrawAlphaBlendedCheckerboard(bool bInDrawAlphaBlendedCheckerboard) override;`
- L1395 _protected prototype_ `virtual bool IsDrawAlphaBlendedCheckerboardEnabled() const override;`
- L1396 _protected prototype_ `virtual bool CanShowAlphaCheckerboard() const override;`
- L1398 _protected prototype_ `virtual void AddToolbarEntries(FToolMenuSection& Section) override;`
- L1399 _protected prototype_ `virtual void AppendToolbarCommandList(FToolMenuContext& Context) override;`
- L1401 _protected prototype_ `virtual void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L1404 _private prototype_ `TOptional<EMediaCaptureState> GetMediaOutputCaptureState() const;`
- L1405 _private prototype_ `FOptionalSize GetMediaOutputDesiredAspectRatio() const;`
- L1407 _private prototype_ `void OnCaptureMethodChanged(UMediaOutput* MediaOutput);`
- L1410 _private member_ `TSharedPtr<SWidget> ImageWidget;`
- L1411 _private member_ `TSharedPtr<FUICommandList> ShowFlagsCommandList;`
- L1412 _private member_ `ECaptureType CaptureType = ECaptureType::None;`
- L1413 _private member_ `int32 CaptureIndex = INDEX_NONE;`
- L1414 _private member_ `bool bDisplayShowFlags = false;`

#### enum `SMediaProfileMediaOutputDisplay::ECaptureType`  
`enum class ECaptureType : uint8`  
_L1350-1357_
- L1352 _public enumerator_ `None`
- L1353 _public enumerator_ `ActiveViewport`
- L1354 _public enumerator_ `Viewport`
- L1355 _public enumerator_ `RenderTarget`
- L1356 _public enumerator_ `MediaTexture`

#### class `SMediaProfileDummyDisplay`  
`class SMediaProfileDummyDisplay : public SMediaProfileMediaItemDisplayBase<UObject>`  
_L1418-1438_
- inherits: `SMediaProfileMediaItemDisplayBase<UObject>`
- desc: Dummy display for when a panel needs to be displayed that doesn't contain any media item
- L1421 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileDummyDisplay)`
- L1422 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FMediaProfileEditor>, MediaProfileEditor) SLATE_ARGUMENT(int32, PanelIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SMediaProfileViewport>& InOwningViewport);`
- L1429 _protected prototype_ `virtual void ConfigureMediaImage() override;`
- L1431 _protected function_ `virtual UObject* GetMediaItem() const override`
- L1432 _protected function_ `virtual FText GetMediaItemLabel() const override`
- L1433 _protected function_ `virtual FText GetBaseMediaTypeLabel() const override`
- L1435 _protected prototype_ `virtual FText GetActiveMediaItemLabel() const override;`
- L1436 _protected function_ `virtual FSlateIcon GetActiveMediaItemIcon() const override`
- L1437 _protected prototype_ `virtual void ChangeActiveMediaItem(UClass* InMediaItemClass, int32 InMediaItemIndex) override;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace MediaPlayerEditor` (scope `UE`)
- L69 _macro_ `#define LOCTEXT_NAMESPACE "SMediaProfileMediaItemDisplay"`
- L188 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::BindCommands`)
- L205 _function_ `}), FCanExecuteAction(), FIsActionChecked::CreateLambda([this]` (scope `SMediaProfileMediaItemDisplayBase::BindCommands`)
- L290 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateToolbar`)
- L300 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateToolbar::__anonb40b97ae0502`)
- L395 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::GetMediaItemsDropdownContent`)
- L459 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateRotationSubmenu`)
- L470 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateRotationSubmenu::__anonb40b97ae0c02`)
- L503 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateFlipSubmenu`)
- L588 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateChannelsSubmenu`)
- L616 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateChannelsSubmenu::__anonb40b97ae1102`)
- L692 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateChannelsButton`)
- L700 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateChannelsButton::__anonb40b97ae1a02`)
- L718 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateViewportArrangementMenu`)
- L726 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateViewportArrangementMenu::__anonb40b97ae1c02`)
- L793 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateMaximizeViewportButton`)
- L826 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateSettingsMenu`)
- L835 _function_ `` (scope `SMediaProfileMediaItemDisplayBase::CreateSettingsMenu::__anonb40b97ae2102`)

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMediaProfileSourcesTreeView.h` (Private)


#### class `SMediaProfileSourcesTreeView`  
`class SMediaProfileSourcesTreeView : public SCompoundWidget, public FEditorUndoClient`  
_L18-124_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A tree view that displays a media profile's source and outputs
- L21 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnMediaItemDeleted, UClass* , int32 ) DECLARE_DELEGATE_TwoParams(FOnSelectedMediaItemsChanged, const TArray<int32>& , const TArray<int32>& );`
- L41 _private typedef_ `typedef TSharedPtr<FMediaTreeItem> FMediaTreeItemPtr;`
- L44 _private member_ `static const FLazyName Column_Index;` — Names of the columns within the tree view
- L45 _private member_ `static const FLazyName Column_ItemLabel;`
- L46 _private member_ `static const FLazyName Column_ItemType;`
- L47 _private member_ `static const FLazyName Column_Configuration;`
- L50 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileSourcesTreeView)`
- L51 _public prototype_ `SLATE_EVENT(FOnMediaItemDeleted, OnMediaItemDeleted) SLATE_EVENT(FOnSelectedMediaItemsChanged, OnSelectedMediaItemsChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMediaProfile* InMediaProfile);`
- L59 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L63 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L64 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L69 _private prototype_ `void BindCommands();` — Initializes and binds the command list to event handlers
- L72 _private prototype_ `void CopySelectedMedia();` — Tree item context menu handlers
- L73 _private prototype_ `bool CanCopySelectedMedia() const;`
- L74 _private prototype_ `void CutSelectedMedia();`
- L75 _private prototype_ `bool CanCutSelectedMedia() const;`
- L76 _private prototype_ `void PasteSelectedMedia();`
- L77 _private prototype_ `bool CanPasteSelectedMedia() const;`
- L78 _private prototype_ `void DuplicateSelectedMedia();`
- L79 _private prototype_ `bool CanDuplicateSelectedMedia() const;`
- L80 _private prototype_ `void DeleteSelectedMedia();`
- L81 _private prototype_ `bool CanDeleteSelectedMedia() const;`
- L84 _private prototype_ `void AddNewMediaSource();` — Adds a new empty media source to the media profile
- L87 _private prototype_ `void AddNewMediaOutput();` — Adds a new empty media output to the media profile
- L90 _private prototype_ `void FillMediaTree(const TOptional<TArray<int32>>& InMediaSourcesToSelect = TOptional<TArray<int32>>(), const TOptional<TArray<int32>>& InMediaOutputsToSelect = TOptional<TArray<int32>>());` — Recreates the tree view's source list from the current media profile's list of sources and outputs
- L93 _private prototype_ `void GetSelectedMediaIndexes(TArray<int32>& OutSelectedMediaSources, TArray<int32>& OutSelectedMediaOutputs, bool bIncludeGroupIndex = false);` — Converts the selected tree items to a list of indexes of the selected media sources and outputs in the media profile
- L96 _private prototype_ `void GetTreeItemChildren(FMediaTreeItemPtr InTreeItem, TArray<FMediaTreeItemPtr>& OutChildren) const;` — TreeView event handlers
- L97 _private prototype_ `TSharedRef<ITableRow> GenerateTreeItemRow(FMediaTreeItemPtr InTreeItem, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L98 _private prototype_ `TSharedPtr<SWidget> CreateContextMenu();`
- L101 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Raised when an object property is changed. Used to monitor changes to the media profile and update the media tree view accordingly
- L104 _private prototype_ `void OnFilterChanged();` — Raised when the filter has changed in the toolbar, updates the tree view's source list to show only filtered items
- L107 _private prototype_ `void OnMoveMediaItem(TSharedPtr<FMediaTreeItem> InTreeItem, int32 InIndex);` — Raised when a media tree item is moved
- L109 _private prototype_ `void OnMediaTreeSelectionChanged(TSharedPtr<FMediaTreeItem> SelectedItem, ESelectInfo::Type SelectionType);`
- L112 _private member_ `TArray<FMediaTreeItemPtr> MediaTreeItems;`
- L113 _private member_ `TSharedPtr<STreeView<FMediaTreeItemPtr>> MediaTreeView;`
- L114 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L115 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;`
- L117 _private member_ `TSharedPtr<SMediaProfileSourcesToolbar> Toolbar;`
- L119 _private member_ `FOnMediaItemDeleted OnMediaItemDeleted;`
- L120 _private member_ `FOnSelectedMediaItemsChanged OnSelectedMediaItemsChanged;`

#### struct `SMediaProfileSourcesTreeView::FMediaTreeItem`  
`struct FMediaTreeItem`  
_L26-40_
- desc: Struct to store information for each element displayed in the tree view
- L28 _public member_ `int32 Index = INDEX_NONE;`
- L29 _public member_ `FText Label = FText::GetEmpty();`
- L30 _public member_ `FText Type = FText::GetEmpty();`
- L31 _public member_ `FText Configuration = FText::GetEmpty();`
- L32 _public member_ `const FSlateBrush* Icon = nullptr;`
- L33 _public member_ `bool bFilteredOut = false;`
- L35 _public member_ `TArray<TSharedPtr<FMediaTreeItem>> Children;`
- L36 _public member_ `TWeakObjectPtr<UClass> BackingClass = nullptr;`
- L37 _public member_ `TWeakObjectPtr<UObject> BackingObject = nullptr;`
- L39 _public function_ `bool IsLeaf() const`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMediaItemDeleted, UClass* , int32 ) DECLARE_DELEGATE_TwoParams(FOnSelectedMediaItemsChanged, const TArray<int32>& , const TArray<int32>& );`
- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectedMediaItemsChanged, const TArray<int32>& , const TArray<int32>& );`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/SMediaProfileViewport.h` (Private)


#### class `SMediaProfileViewport`  
`class SMediaProfileViewport : public SCompoundWidget`  
_L15-164_
- inherits: `SCompoundWidget`
- desc: Viewport that displays the input or output from selected media sources and outputs
- L47 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileViewport)`
- L48 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FMediaProfileEditor> InOwningEditor);`
- L52 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L53 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L56 _public prototype_ `void SetSelectedMediaItems(const TArray<int32>& InSelectedMediaSourceIndices, const TArray<int32>& InSelectedMediaOutputIndices);` — Displays the selected media items in a viewport panel arrangement
- L59 _public prototype_ `void ForceClearMediaItem(UClass* InMediaType, int32 InMediaItemIndex);` — Removes all panels that contain the specified media item, even if the panels are locked
- L62 _public prototype_ `void SetPanelContents(int32 InPanelIndex, UClass* InMediaItemClass, int32 InMediaItemIndex, bool bRefreshDisplay);` — Sets the contents of the specified panel to the specified media type and media index
- L65 _public prototype_ `void SetPanelLocked(int32 InPanelIndex, bool bInIsLocked);` — Sets the lock status the specified panel
- L68 _public prototype_ `bool IsPanelLocked(int32 InPanelIndex) const;` — Gets whether the specified panel is locked or not
- L71 _public prototype_ `bool CanMaximizePanel(int32 InPanelIndex) const;` — Gets whether the specified panel can be maximized right now or not
- L74 _public prototype_ `void MaximizePanel(int32 InPanelIndex);` — Maximizes the contents in the specified panel index, moving them to the first panel and changing the arrangement to single panel
- L77 _public prototype_ `bool IsPanelMaximized(int32 InPanelIndex) const;` — Gets whether the specified panel is currently maximized
- L80 _public prototype_ `bool CanRestorePreviousLayout() const;` — Gets whether there is a previous layout that can be restored
- L83 _public prototype_ `void RestorePreviousLayout();` — Restores the previous multi-panel layout from a maximized state, if one is saved
- L86 _public prototype_ `void SetImmersivePanel();` — Sets the panel layout to display as immersive fullscreen
- L89 _public prototype_ `bool IsPanelImmersive() const;` — Gets whether the panel layout is being displayed in immersive view
- L92 _public prototype_ `void ClearImmersivePanel();` — Clears any immersive panel being displayed
- L95 _public prototype_ `void SaveLayout(FMediaProfileEditorLayoutSettings& InOutLayoutSettings);` — Saves the current layout of the viewport's panels into the specified named layout
- L98 _public prototype_ `void LoadLayout(const FMediaProfileEditorLayoutSettings& InLayoutSettings);` — Loads the panel configuration from the specified named layout into the viewport's panels
- L101 _public prototype_ `void ClearLayout();` — Clears the current panel layout back to default
- L104 _public function_ `TSharedPtr<FUICommandList> GetCommandList()` — Gets the viewport's command list
- L108 _private prototype_ `void BindCommands();` — Binds commands in this widget's command list to actions
- L111 _private prototype_ `void UpdateDisplays();` — Updates the current media item displays to match the selected media items
- L114 _private prototype_ `TSharedRef<SWidget> ConstructPanelWidget(int32 InPanelIndex);` — Constructs the widget to display the contents of the specified panel
- L117 _private prototype_ `TSharedRef<SWidget> ConstructViewportLayout();` — Creates and lays out the panels for the viewport based on the currently set layout, orientation, and panel contents
- L120 _private prototype_ `void SetViewportLayout(EViewportLayout InViewportLayout, EViewportOrientation InViewportOrientation);` — Sets the viewport panel layout to the specified layout and orientation
- L123 _private prototype_ `bool IsViewportLayoutSet(EViewportLayout InViewportLayout, EViewportOrientation InViewportOrientation) const;` — Returns whether the current viewport panel layout matches the specified layout and orientation
- L127 _private member_ `TWeakPtr<FMediaProfileEditor> MediaProfileEditor;` — Media profile editor that owns this viewport
- L130 _private member_ `TSharedPtr<SOverlay> LayoutContainer;` — Container that holds the actual panel layout widgets
- L142 _private member_ `TArray<FPanelContent> PanelContents;` — The content of the currently displayed viewport panels
- L145 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for the viewport tab
- L148 _private member_ `EViewportLayout CurrentLayout = EViewportLayout::OnePanel;` — Currently active viewport layout
- L151 _private member_ `EViewportOrientation CurrentOrientation = EViewportOrientation::Left;` — Currently active viewport orientation
- L154 _private member_ `EViewportLayout SavedLayout = EViewportLayout::OnePanel;` — Stores the previously used layout to restore if toggling out of maximized panel
- L157 _private member_ `EViewportOrientation SavedOrientation = EViewportOrientation::Left;` — Stores the previously used orientation to restore if toggling out of maximized panel
- L160 _private member_ `int32 MaximizedPanelIndex = INDEX_NONE;` — When maximizing from a multi-panel layout, this is the panel being maximized
- L163 _private member_ `bool bImmersive = false;` — Whether the panel layout is being displayed in immersive fullscreen

#### enum `SMediaProfileViewport::EViewportLayout`  
`enum class EViewportLayout`  
_L19-35_
- desc: Indicates how to lay out the panels of the viewport
- L22 _public enumerator_ `OnePanel` — Single panel layout
- L25 _public enumerator_ `TwoPanel` — Two panel layout split either horizontally or vertically
- L28 _public enumerator_ `ThreePanel` — Three panel layout where one half is a full panel and the other half is split between two panels
- L31 _public enumerator_ `OneAndThreePanel` — Four panel layout where one half is a full panel and the other half is split between three panels
- L34 _public enumerator_ `QuadPanel` — A 2x2 panel split

#### enum `SMediaProfileViewport::EViewportOrientation`  
`enum class EViewportOrientation`  
_L38-44_
- desc: Indicates how to orient the primary panel in panel layouts that can have multiple orientations (e.g. three panel)
- L40 _public enumerator_ `Left`
- L41 _public enumerator_ `Top`
- L42 _public enumerator_ `Right`
- L43 _public enumerator_ `Bottom`

#### struct `SMediaProfileViewport::FPanelContent`  
`struct FPanelContent`  
_L133-139_
- desc: Stores the content of a displayed viewport panel
- L135 _public member_ `UClass* MediaType = nullptr;`
- L136 _public member_ `int32 MediaItemIndex = INDEX_NONE;`
- L137 _public member_ `bool bIsLocked = false;`
- L138 _public member_ `TSharedPtr<SWidget> Widget;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/CaptureTab/MediaFrameworkCapturePanelBlueprintLibrary.h` (Private)


#### class `UMediaFrameworkCapturePanel`  
`class UMediaFrameworkCapturePanel : public UObject`  
_L21-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L30 _public prototype_ `void StartCapture();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Capture the camera's viewport and the render target.
- L36 _public prototype_ `void StopCapture();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Stop the current capture.
- L42 _public prototype_ `void EmptyRenderTargetCapture();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Clear all the render target captures.
- L48 _public prototype_ `void AddRenderTargetCapture(UMediaOutput* MediaOutput, UTextureRenderTarget2D* RenderTarget, FMediaCaptureOptions CaptureOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Add a render target 2d to be captured.
- L54 _public prototype_ `void EmptyViewportCapture();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Clear all the viewport captures.
- L60 _public prototype_ `void AddViewportCapture(UMediaOutput* MediaOutput, AActor* Camera, FMediaCaptureOptions CaptureOptions, EViewModeIndex ViewMode = VMI_Unknown);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Add a camera to be used when capturing the current viewport.
- L66 _public prototype_ `void SetCurrentViewportCapture(UMediaOutput* MediaOutput, FMediaCaptureOptions CaptureOptions, EViewModeIndex ViewMode = VMI_Unknown);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Media Capture")` — Change the setting for capturing the current viewport.

#### class `UMediaFrameworkCapturePanelBlueprintLibrary`  
`class UMediaFrameworkCapturePanelBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L71-81_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="MediaFrameworkCapturePanelLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L80 _public prototype_ `static UMediaFrameworkCapturePanel* GetMediaCapturePanel();` — `UFUNCTION(BlueprintCallable, Category="Editor Scripting | Media Capture")` — Get Media Capture panel instance.

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/CaptureTab/SMediaFrameworkCapture.h` (Private)


#### class `UMediaFrameworkMediaCaptureSettings`  
`class UMediaFrameworkMediaCaptureSettings : public UObject`  
_L31-43_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the media capture tab.
- L36 _public member_ `bool bIsVerticalSplitterOrientation = true;` — `UPROPERTY(config)`
- L42 _public member_ `FIntPoint DefaultViewportCaptureSize = FIntPoint(1920, 1080);` — `UPROPERTY(EditAnywhere, config, Category="Media Viewport Capture")` — This is the resolution to use if it is not specified by the media output.

#### class `UMediaFrameworkEditorCaptureSettings`  
`class UMediaFrameworkEditorCaptureSettings : public UMediaFrameworkWorldSettingsAssetUserData`  
_L49-60_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UMediaFrameworkWorldSettingsAssetUserData`
- desc: Settings for the capture that are persistent per users.
- L55 _public member_ `bool bSaveCaptureSetingsInWorld = true;` — `UPROPERTY(config)` — Should the Capture setting be saved with the level or should it be saved as a project settings.
- L59 _public member_ `bool bAutoRestartCaptureOnChange = true;` — `UPROPERTY(config)` — Should the capture be restarted if the media output is modified.

#### class `SMediaFrameworkCapture`  
`class SMediaFrameworkCapture : public SCompoundWidget, public FNotifyHook`  
_L65-128_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: SMediaFrameworkCapture
- L68 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L69 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L70 _public prototype_ `static TSharedPtr<SMediaFrameworkCapture> GetPanelInstance();`
- L73 _private member_ `static TWeakPtr<SMediaFrameworkCapture> WidgetInstance;`
- L76 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkCapture)`
- L79 _public prototype_ `~SMediaFrameworkCapture();`
- L81 _public prototype_ `void Construct(const FArguments& InArgs);`
- L83 _public function_ `bool IsCapturing() const`
- L84 _public prototype_ `void EnabledCapture(bool bEnabled);`
- L85 _public prototype_ `UMediaFrameworkWorldSettingsAssetUserData* FindOrAddMediaFrameworkAssetUserData();`
- L88 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L89 _private prototype_ `bool IsPropertyReadOnly(const FPropertyAndParent& PropertyAndParent) const;`
- L91 _private prototype_ `void OnMapChange(uint32 InMapFlags);`
- L92 _private prototype_ `void OnLevelActorsRemoved(AActor* InActor);`
- L93 _private prototype_ `void OnAssetsDeleted(const TArray<UClass*>& DeletedAssetClasses);`
- L94 _private prototype_ `void OnObjectPreEditChange(UObject* Object, const FEditPropertyChain& PropertyChain);`
- L95 _private prototype_ `void OnOutputModified(UMediaOutput* Output);`
- L97 _private prototype_ `TSharedRef<class SWidget> MakeToolBar();`
- L98 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu();`
- L100 _private prototype_ `TOptional<int32> GetDefaultViewportSize(int32 InValueIndex) const;`
- L101 _private prototype_ `void DefaultViewportSizeChanged(int32 InValue, int32 InValueIndex);`
- L102 _private prototype_ `void DefaultViewportSizeCommitted(int32 InValue, ETextCommit::Type InCommitInfo, int32 InValueIndex);`
- L104 _private prototype_ `bool CanEnableViewport() const;`
- L105 _private prototype_ `UMediaFrameworkWorldSettingsAssetUserData* FindMediaFrameworkAssetUserData() const;`
- L107 _private prototype_ `void OnPrePIE(bool bIsSimulating);`
- L108 _private prototype_ `void OnPostPIEStarted(bool bIsSimulating);`
- L109 _private prototype_ `void OnPrePIEEnded(bool bIsSimulating);`
- L111 _private member_ `TSharedPtr<IDetailsView> DetailView;`
- L112 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L113 _private member_ `TSharedPtr<MediaFrameworkUtilities::SCaptureVerticalBox> CaptureBoxes;`
- L114 _private member_ `bool bIsCapturing;`
- L115 _private member_ `bool bIsInPIESession;`
- L117 _private member_ `TArray<TSharedPtr<SMediaFrameworkCaptureCameraViewportWidget>> CaptureCameraViewports;`
- L118 _private member_ `TArray<TSharedPtr<SMediaFrameworkCaptureRenderTargetWidget>> CaptureRenderTargets;`
- L119 _private member_ `TSharedPtr<SMediaFrameworkCaptureCurrentViewportWidget> CaptureCurrentViewport;`
- L121 _private member_ `static FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L124 _private member_ `FTimerHandle NextTickTimerHandle;` — Handle for the timer used to restart a source after its output options have been modified.
- L127 _private member_ `TArray<TWeakObjectPtr<UMediaOutput>> MediaOutputsWithDelegates;` — List of MediaOutputs for which we have a registered delegates.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace MediaFrameworkUtilities`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/CaptureTab/SMediaFrameworkCaptureOutputWidget.h` (Private)


#### class `SMediaFrameworkCaptureOutputWidget`  
`class SMediaFrameworkCaptureOutputWidget : public SCompoundWidget`  
_L31-60_
- inherits: `SCompoundWidget`
- desc: SMediaFrameworkCaptureOutputWidget definition
- L34 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkCaptureOutputWidget)`
- L35 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SMediaFrameworkCapture>, Owner) SLATE_ARGUMENT(TWeakObjectPtr<UMediaOutput>, MediaOutput) SLATE_ARGUMENT(FMediaCaptureOptions, CaptureOptions) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `virtual void StopOutput();`
- L44 _public prototype_ `TSharedRef<SWidget> BuildBaseWidget(TSharedRef<SWidget> InnerWidget, const FString& CaptureType);`
- L46 _public prototype_ `FSlateColor HandleIconColorAndOpacity() const;`
- L47 _public prototype_ `const FSlateBrush* HandleIconImage() const;`
- L48 _public prototype_ `FText HandleIconText() const;`
- L49 _public prototype_ `virtual bool IsValid() const;`
- L51 _public function_ `virtual void OnPrePIE()`
- L52 _public function_ `virtual void OnPostPIEStarted()`
- L53 _public function_ `virtual void OnPrePIEEnded()`
- L55 _public member_ `TWeakPtr<SMediaFrameworkCapture> Owner;`
- L56 _public member_ `TWeakObjectPtr<UMediaOutput> MediaOutput;`
- L57 _public member_ `FMediaCaptureOptions CaptureOptions;`
- L59 _public member_ `TStrongObjectPtr<UMediaCapture> MediaCapture;`

#### class `SMediaFrameworkCaptureCameraViewportWidget`  
`class SMediaFrameworkCaptureCameraViewportWidget : public SMediaFrameworkCaptureOutputWidget`  
_L65-100_
- inherits: `SMediaFrameworkCaptureOutputWidget`
- desc: SMediaFrameworkCaptureCameraViewportWidget definition
- L68 _private typedef_ `using Super = SMediaFrameworkCaptureOutputWidget;`
- L71 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkCaptureCameraViewportWidget)`
- L72 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SMediaFrameworkCapture>, Owner) SLATE_ARGUMENT(TWeakObjectPtr<UMediaOutput>, MediaOutput) SLATE_ARGUMENT(FMediaCaptureOptions, CaptureOptions) SLATE_ARGUMENT(TArray<TWeakObjectPtr<AActor>>, PreviewActors) SLATE_ARGUMENT(EViewModeIndex, ViewMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L80 _public prototype_ `~SMediaFrameworkCaptureCameraViewportWidget();`
- L82 _public prototype_ `void StartOutput();`
- L83 _public prototype_ `virtual void StopOutput() override;`
- L85 _public prototype_ `virtual void OnPostPIEStarted() override;`
- L86 _public prototype_ `virtual void OnPrePIEEnded() override;`
- L89 _private prototype_ `void SetActorLock(int32 CameraIndex);`
- L90 _private prototype_ `void UpdateActivePreviewList(bool bIsPIE);`
- L92 _private member_ `TSharedPtr<MediaFrameworkUtilities::FMediaFrameworkCaptureLevelEditorViewportClient> LevelViewportClient;`
- L93 _private member_ `TSharedPtr<SViewport> ViewportWidget;`
- L94 _private member_ `TSharedPtr<FSceneViewport> SceneViewport;`
- L96 _private member_ `TArray<TWeakObjectPtr<AActor>> PreviewActors;`
- L97 _private member_ `TArray<TWeakObjectPtr<AActor>> ActivePreviewActors;`
- L98 _private member_ `EViewModeIndex ViewMode;`
- L99 _private member_ `int32 CurrentLockCameraIndex;`

#### class `SMediaFrameworkCaptureRenderTargetWidget`  
`class SMediaFrameworkCaptureRenderTargetWidget : public SMediaFrameworkCaptureOutputWidget`  
_L105-129_
- inherits: `SMediaFrameworkCaptureOutputWidget`
- desc: SMediaFrameworkCaptureRenderTargetWidget definition
- L108 _private typedef_ `using Super = SMediaFrameworkCaptureOutputWidget;`
- L111 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkCaptureRenderTargetWidget)`
- L112 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SMediaFrameworkCapture>, Owner) SLATE_ARGUMENT(TWeakObjectPtr<UMediaOutput>, MediaOutput) SLATE_ARGUMENT(FMediaCaptureOptions, CaptureOptions) SLATE_ARGUMENT(TWeakObjectPtr<UTextureRenderTarget2D>, RenderTarget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L119 _public prototype_ `~SMediaFrameworkCaptureRenderTargetWidget();`
- L121 _public prototype_ `void StartOutput();`
- L123 _public prototype_ `virtual bool IsValid() const override;`
- L126 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> RenderTarget;`
- L127 _private member_ `TStrongObjectPtr<UMaterial> ImageMaterial;`
- L128 _private member_ `TSharedPtr<FSlateBrush> ImageMaterialBrush;`

#### class `SMediaFrameworkCaptureCurrentViewportWidget`  
`class SMediaFrameworkCaptureCurrentViewportWidget : public SMediaFrameworkCaptureOutputWidget`  
_L134-180_
- inherits: `SMediaFrameworkCaptureOutputWidget`
- desc: SMediaFrameworkCaptureCurrentViewportWidget definition
- L137 _private typedef_ `using Super = SMediaFrameworkCaptureOutputWidget;`
- L140 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkCaptureCurrentViewportWidget)`
- L141 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SMediaFrameworkCapture>, Owner) SLATE_ARGUMENT(TWeakObjectPtr<UMediaOutput>, MediaOutput) SLATE_ARGUMENT(FMediaCaptureOptions, CaptureOptions) SLATE_ARGUMENT(EViewModeIndex, ViewMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L148 _public prototype_ `~SMediaFrameworkCaptureCurrentViewportWidget();`
- L149 _public prototype_ `virtual void StopOutput() override;`
- L151 _public prototype_ `void StartOutput();`
- L153 _public prototype_ `virtual void OnPrePIE() override;`
- L154 _public prototype_ `virtual void OnPrePIEEnded() override;`
- L170 _private prototype_ `void ShutdownViewport();`
- L171 _private prototype_ `void OnLevelViewportClientListChanged();`
- L172 _private prototype_ `void OnMediaCaptureStateChanged();`
- L175 _private member_ `TWeakPtr<FSceneViewport> EditorSceneViewport;`
- L176 _private member_ `TWeakPtr<IAssetViewport> LevelViewport;`
- L177 _private member_ `FPreviousViewportClientFlags ViewportClientFlags;`
- L179 _private member_ `EViewModeIndex ViewMode;`

#### struct `SMediaFrameworkCaptureCurrentViewportWidget::FPreviousViewportClientFlags`  
`struct FPreviousViewportClientFlags`  
_L156-167_
- L158 _public prototype_ `FPreviousViewportClientFlags();`
- L159 _public member_ `bool bRealTime;`
- L160 _public member_ `bool bSetListenerPosition;`
- L161 _public member_ `bool bDrawAxes;`
- L162 _public member_ `bool bDisableInput;`
- L163 _public member_ `bool bAllowCinematicControl;`
- L164 _public member_ `FEngineShowFlags EngineShowFlags;`
- L165 _public member_ `FEngineShowFlags LastEngineShowFlags;`
- L166 _public member_ `FViewportStateGetter VisibilityDelegate;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace MediaFrameworkUtilities`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaBundleActorDetails.h` (Private)


#### class `FMediaBundleActorDetails`  
`class FMediaBundleActorDetails : public IDetailCustomization`  
_L9-17_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L16 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaBundleFactoryNew.h` (Private)


#### class `UMediaBundleFactoryNew`  
`class UMediaBundleFactoryNew : public UFactory`  
_L16-26_
- reflection: `UCLASS(hideCategories =Object)`
- inherits: `UFactory`
- desc: Implements a factory for UMediaPlayer objects.
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### class `UActorFactoryMediaBundle`  
`class UActorFactoryMediaBundle : public UActorFactory`  
_L29-40_
- reflection: `UCLASS(MinimalAPI, config=Editor, collapseCategories, hideCategories=Object)`
- inherits: `UActorFactory`
- L35 _public prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L36 _public prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L37 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L38 _public prototype_ `virtual AActor* GetDefaultActor(const FAssetData& AssetData) override;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkUtilitiesEditorModule.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaFrameworkUtilitiesEditor, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaFrameworkUtilitiesEditor, Log, All);`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkUtilitiesPlacement.h` (Private)


#### class `FMediaFrameworkUtilitiesPlacement`  
`class FMediaFrameworkUtilitiesPlacement`  
_L6-11_
- L9 _public prototype_ `static void RegisterPlacement();`
- L10 _public prototype_ `static void UnregisterPlacement();`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkVideoInputSettings.h` (Private)


#### struct `FMediaFrameworkVideoInputSourceSettings`  
`struct FMediaFrameworkVideoInputSourceSettings`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `TSoftObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(EditAnywhere, Category="Media")`
- L21 _public member_ `TSoftObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(EditAnywhere, Category="Media")`

#### class `UMediaFrameworkVideoInputSettings`  
`class UMediaFrameworkVideoInputSettings : public UObject`  
_L28-49_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the video input tab.
- L33 _public member_ `TArray<TSoftObjectPtr<UMediaBundle>> MediaBundles;` — `UPROPERTY(config, EditAnywhere, Category="Media Bundle")`
- L36 _public member_ `TArray<FMediaFrameworkVideoInputSourceSettings> MediaSources;` — `UPROPERTY(config, EditAnywhere, Category="Media Source")`
- L39 _public member_ `bool bReopenMediaBundles;` — `UPROPERTY(config)`
- L42 _public member_ `bool bReopenMediaSources;` — `UPROPERTY(config)`
- L45 _public member_ `float ReopenDelay = 3.f;` — `UPROPERTY(config)`
- L48 _public member_ `bool bIsVerticalSplitterOrientation = true;` — `UPROPERTY(config)`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkWorldSettingsAssetUserData.h` (Private)


#### struct `FMediaFrameworkCaptureCurrentViewportOutputInfo`  
`struct FMediaFrameworkCaptureCurrentViewportOutputInfo`  
_L20-34_
- reflection: `USTRUCT()`
- desc: FMediaFrameworkCaptureCurrentViewportOutputInfo
- L24 _public prototype_ `FMediaFrameworkCaptureCurrentViewportOutputInfo();`
- L27 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(EditAnywhere, Category="MediaViewportCapture")`
- L30 _public member_ `FMediaCaptureOptions CaptureOptions;` — `UPROPERTY(EditAnywhere, Category="MediaViewportCapture")`
- L33 _public member_ `TEnumAsByte<EViewModeIndex> ViewMode;` — `UPROPERTY()`

#### struct `FMediaFrameworkCaptureCameraViewportCameraOutputInfo`  
`struct FMediaFrameworkCaptureCameraViewportCameraOutputInfo`  
_L40-83_
- reflection: `USTRUCT()`
- desc: FMediaFrameworkCaptureCameraViewportCameraOutputInfo
- L44 _public prototype_ `FMediaFrameworkCaptureCameraViewportCameraOutputInfo();`
- L49 _public prototype_ `~FMediaFrameworkCaptureCameraViewportCameraOutputInfo() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables this is a requirement for clang to compile without warnings.
- L50 _public prototype_ `FMediaFrameworkCaptureCameraViewportCameraOutputInfo(const FMediaFrameworkCaptureCameraViewportCameraOutputInfo&) = default;`
- L51 _public prototype_ `FMediaFrameworkCaptureCameraViewportCameraOutputInfo(FMediaFrameworkCaptureCameraViewportCameraOutputInfo&&) = default;`
- L52 _public prototype_ `FMediaFrameworkCaptureCameraViewportCameraOutputInfo& operator=(const FMediaFrameworkCaptureCameraViewportCameraOutputInfo&) = default;`
- L53 _public prototype_ `FMediaFrameworkCaptureCameraViewportCameraOutputInfo& operator=(FMediaFrameworkCaptureCameraViewportCameraOutputInfo&&) = default;`
- L57 _public member_ `TArray<TLazyObjectPtr<AActor>> LockedActors_DEPRECATED;` — `UE_DEPRECATED(5.7, "Use Cameras instead")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This property is no longer supported. Use Cameras instead"))`
- L61 _public member_ `TArray<TSoftObjectPtr<AActor>> Cameras;` — `UPROPERTY(EditAnywhere, Category="MediaViewportCapture")`
- L64 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(EditAnywhere, Category="MediaViewportCapture")`
- L67 _public member_ `FMediaCaptureOptions CaptureOptions;` — `UPROPERTY(EditAnywhere, Category="MediaViewportCapture")`
- L70 _public member_ `TEnumAsByte<EViewModeIndex> ViewMode;` — `UPROPERTY()`
- L72 _public prototype_ `bool Serialize(FArchive& Ar);`
- L75 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L81 _private member_ `TArray<TObjectPtr<AActor>> LockedCameraActors_DEPRECATED;` — `UPROPERTY()` — DEPRECATED 4.21 The type of LockedCameraActors has changed and will be removed from the code base in a future release. Use LockedActors.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMediaFrameworkCaptureCameraViewportCameraOutputInfo> : public TStructOpsTypeTraitsBase2<FMediaFrameworkCaptureCameraViewportCameraOutputInfo>`  
_L85-95_
- inherits: `TStructOpsTypeTraitsBase2<FMediaFrameworkCaptureCameraViewportCameraOutputInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L88-94_

#### struct `FMediaFrameworkCaptureRenderTargetCameraOutputInfo`  
`struct FMediaFrameworkCaptureRenderTargetCameraOutputInfo`  
_L101-115_
- reflection: `USTRUCT()`
- desc: FMediaFrameworkCaptureRenderTargetCameraOutputInfo
- L105 _public prototype_ `FMediaFrameworkCaptureRenderTargetCameraOutputInfo();`
- L108 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(EditAnywhere, Category="MediaRenderTargetCapture")`
- L111 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(EditAnywhere, Category="MediaRenderTargetCapture")`
- L114 _public member_ `FMediaCaptureOptions CaptureOptions;` — `UPROPERTY(EditAnywhere, Category="MediaRenderTargetCapture")`

#### struct `FMediaFrameworkCaptureMediaTextureOutputInfo`  
`struct FMediaFrameworkCaptureMediaTextureOutputInfo`  
_L118-135_
- reflection: `USTRUCT()`
- L122 _public prototype_ `FMediaFrameworkCaptureMediaTextureOutputInfo();`
- L125 _public member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L128 _public member_ `FMediaCaptureTransform Transform;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L131 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L134 _public member_ `FMediaCaptureOptions CaptureOptions;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`

#### class `UMediaFrameworkWorldSettingsAssetUserData`  
`class UMediaFrameworkWorldSettingsAssetUserData : public UAssetUserData`  
_L141-167_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UAssetUserData`
- desc: UMediaFrameworkCaptureCameraViewportAssetUserData
- L146 _public prototype_ `UMediaFrameworkWorldSettingsAssetUserData();`
- L149 _public member_ `TArray<FMediaFrameworkCaptureRenderTargetCameraOutputInfo> RenderTargetCaptures;` — `UPROPERTY(EditAnywhere, config, Category="Media Render Target Capture", meta=(ShowOnlyInnerProperties))`
- L152 _public member_ `TArray<FMediaFrameworkCaptureCameraViewportCameraOutputInfo> ViewportCaptures;` — `UPROPERTY(EditAnywhere, config, Category="Media Viewport Capture", meta=(ShowOnlyInnerProperties))`
- L155 _public member_ `TArray<FMediaFrameworkCaptureMediaTextureOutputInfo> MediaTextureCaptures;` — `UPROPERTY(config)`
- L163 _public member_ `FMediaFrameworkCaptureCurrentViewportOutputInfo CurrentViewportMediaOutput;` — `UPROPERTY(EditAnywhere, config, Category="Media Current Viewport Capture", meta=(DisplayName="Current Viewport"))` — Capture the current viewport. It may be the level editor active viewport or a PIE instance launch with "New Editor Window PIE". @note The behavior is different from MediaCapture.CaptureActiveSceneViewport. Here we can capture the editor viewport (since we are in the editor). @note If the viewport is the level editor active viewport, then all inputs will be disabled and the viewport will always rendered.
- L166 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`

#### Free symbols / members of external scopes

- L89 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonce42e06f0103`)
- L92 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonce42e06f0103`)
- L169 _namespace_ `namespace UE`
- L169 _namespace_ `namespace MediaFrameworkWorldSettings` (scope `UE`)
- L169 _namespace_ `namespace Helpers` (scope `UE::MediaFrameworkWorldSettings`)
- L177 _prototype_ `bool HasAnyOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`) — Gets whether there is output info of any type for the specified media output in the capture settings @param InSettings The capture settings to search in @param InMediaOutput The media output to look for references for @return true if there is valid output info for the media output; otherwise, false
- L187 _function_ `template<typename TOutputInfo> TOutputInfo* FindFirstOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput)` (scope `UE::MediaFrameworkWorldSettings::Helpers`) — Finds the first capture output info of a specific type in the capture settings that reference the specified media output @tparam TOutputInfo The type of capture output info to search for @param InSettings The capture settings to search in @param InMediaOutput The media output to look for references for @return A pointer to the found output info, or null if none were found
- L191 _prototype_ `template<> FMediaFrameworkCaptureCurrentViewportOutputInfo* FindFirstOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L204 _function_ `template<typename TOutputInfo> TArray<TOutputInfo> FindAllOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput)` (scope `UE::MediaFrameworkWorldSettings::Helpers`) — Finds all the capture output infos of a specific type in the capture settings that reference the specified media output @tparam TOutputInfo The type of capture output info to search for @param InSettings The capture settings to search in @param InMediaOutput The media output to look for references for @return A list of capture output infos of type TOutputInfo that reference InMediaOutput
- L208 _prototype_ `template<> TArray<FMediaFrameworkCaptureCurrentViewportOutputInfo> FindAllOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L221 _function_ `template<typename TOutputInfo> void ForEachOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput, TFunction<void(TOutputInfo&)> ForEachFunc)` (scope `UE::MediaFrameworkWorldSettings::Helpers`) — Calls the specified function on each capture output info of the specified type in the capture settings that references the specified media output @tparam TOutputInfo The type of capture output info to search for @param InSettings The capture settings to search in @param InMediaOutput The media output to look for references for @param ForEachFunc The function to run on each matching capture output info
- L225 _prototype_ `template<> void ForEachOutputInfoForMediaOutput<FMediaFrameworkCaptureCurrentViewportOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput, TFunction<void(FMediaFrameworkCaptureCurrentViewportOutputInfo&)> ForEachFunc);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L227 _prototype_ `template<> void ForEachOutputInfoForMediaOutput<FMediaFrameworkCaptureCameraViewportCameraOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput, TFunction<void(FMediaFrameworkCaptureCameraViewportCameraOutputInfo&)> ForEachFunc);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L229 _prototype_ `template<> void ForEachOutputInfoForMediaOutput<FMediaFrameworkCaptureRenderTargetCameraOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput, TFunction<void(FMediaFrameworkCaptureRenderTargetCameraOutputInfo&)> ForEachFunc);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L231 _prototype_ `template<> void ForEachOutputInfoForMediaOutput<FMediaFrameworkCaptureMediaTextureOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput, TFunction<void(FMediaFrameworkCaptureMediaTextureOutputInfo&)> ForEachFunc);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L236 _function_ `template<typename TOutputInfo> int32 RemoveAllOutputInfoForMediaOutput(UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput)` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L240 _prototype_ `template<> int32 RemoveAllOutputInfoForMediaOutput<FMediaFrameworkCaptureCurrentViewportOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L242 _prototype_ `template<> int32 RemoveAllOutputInfoForMediaOutput<FMediaFrameworkCaptureCameraViewportCameraOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L244 _prototype_ `template<> int32 RemoveAllOutputInfoForMediaOutput<FMediaFrameworkCaptureRenderTargetCameraOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)
- L246 _prototype_ `template<> int32 RemoveAllOutputInfoForMediaOutput<FMediaFrameworkCaptureMediaTextureOutputInfo>( UMediaFrameworkWorldSettingsAssetUserData* InSettings, UMediaOutput* InMediaOutput);` (scope `UE::MediaFrameworkWorldSettings::Helpers`)

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaProfileCaptureMenuExtension.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MediaFrameworkUtilities` (scope `UE`)
- L5 _namespace_ `namespace Menus` (scope `UE::MediaFrameworkUtilities`)
- L8 _prototype_ `void ExtendMediaProfileDropdownMenu();` (scope `UE::MediaFrameworkUtilities::Menus`) — Extends the media profile toolbar/dropdown menu to add media capture options

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/Profile/MediaProfileCustomization.h` (Private)


#### class `FMediaProfileCustomization`  
`class FMediaProfileCustomization : public FMediaProfileSettingsCustomization`  
_L13-25_
- inherits: `FMediaProfileSettingsCustomization`
- L16 _private typedef_ `using Super = FMediaProfileSettingsCustomization;`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/Profile/MediaProfileSettingsCustomization.h` (Private)


#### class `FMediaProfileSettingsCustomization`  
`class FMediaProfileSettingsCustomization : public IDetailCustomization`  
_L18-39_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L30 _private prototype_ `FReply OnConfigureClicked();` — Setup the proxies for the media profile
- L32 _private prototype_ `FSlateColor GetBorderColor() const;`
- L33 _private prototype_ `int32 GetConfigurationStateAsInt() const;`
- L35 _private prototype_ `void Configure(const FMediaProfileSettingsCustomizationOptions& SettingOptions);`
- L37 _private member_ `bool bNotConfigured;`
- L38 _private member_ `bool bNeedFixup;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/Profile/MediaProfileSettingsCustomizationOptions.h` (Private)


#### struct `FMediaProfileSettingsCustomizationOptions`  
`struct FMediaProfileSettingsCustomizationOptions`  
_L11-39_
- reflection: `USTRUCT()`
- L16 _public prototype_ `FMediaProfileSettingsCustomizationOptions();`
- L20 _public member_ `FDirectoryPath ProxiesLocation;` — `UPROPERTY(EditAnywhere, Category="Options", meta=(ContentDir))` — The location where the proxies should be created.
- L24 _public member_ `int32 NumberOfSourceProxies;` — `UPROPERTY(EditAnywhere, Category="Options", meta=(UIMin="0", UIMax="8"))` — The number of input source Unreal may capture.
- L28 _public member_ `int32 NumberOfOutputProxies;` — `UPROPERTY(EditAnywhere, Category="Options", meta=(UIMin="0", UIMax="8"))` — The number of output Unreal may generate.
- L32 _public member_ `bool bShouldCreateBundle;` — `UPROPERTY(EditAnywhere, Category="Options")` — Create 1 media bundle for every source proxy created.
- L36 _public member_ `FDirectoryPath BundlesLocation;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ContentDir, EditCondition="bShouldCreateBundle"))` — The location where the bundles should be created.
- L38 _public prototype_ `bool IsValid() const;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/Profile/SMediaProfileSettingsOptionsWindow.h` (Private)


#### class `SMediaProfileSettingsOptionsWindow`  
`class SMediaProfileSettingsOptionsWindow : public SCompoundWidget`  
_L16-42_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileSettingsOptionsWindow)`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L27 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;`
- L30 _public prototype_ `bool ShouldConfigure(FMediaProfileSettingsCustomizationOptions& OutSettingsOptions) const;`
- L33 _private prototype_ `FReply OnConfigure();`
- L34 _private prototype_ `FReply OnCancel();`
- L35 _private prototype_ `bool CanConfigure() const;`
- L38 _private member_ `TWeakPtr<SWindow> Window;`
- L39 _private member_ `TSharedPtr<IStructureDetailsView> DetailView;`
- L40 _private member_ `FMediaProfileSettingsCustomizationOptions Options;`
- L41 _private member_ `bool bConfigure;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/UI/MediaFrameworkTimecodeGenlockToolMenuEntry.h` (Private)


#### class `FMediaFrameworkTimecodeGenlockToolMenuEntry`  
`class FMediaFrameworkTimecodeGenlockToolMenuEntry: public TSharedFromThis<FMediaFrameworkTimecodeGenlockToolMenuEntry>`  
_L13-42_
- inherits: `TSharedFromThis<FMediaFrameworkTimecodeGenlockToolMenuEntry>`
- desc: Creates and manages tool menu entries for timecode and genlock configurations on media profiles
- L16 _public function_ `FMediaFrameworkTimecodeGenlockToolMenuEntry(TWeakObjectPtr<UMediaProfile> InMediaProfile) : MediaProfile(InMediaProfile)`
- L21 _public prototype_ `FToolMenuEntry CreateTimecodeToolMenuEntry(const TAttribute<bool>& InEntryVisibleAttribute);` — Creates the timecode tool menu entry that can be added to toolbars
- L24 _public prototype_ `FToolMenuEntry CreateGenlockToolMenuEntry(const TAttribute<bool>& InEntryVisibleAttribute);` — Creates the genlock tool menu entry that can be added to toolbars
- L28 _private prototype_ `FText GetTimecodeEntryText() const;` — Gets the text for the timecode toolbar entry
- L31 _private prototype_ `FSlateIcon GetGenlockEntryIcon() const;` — Gets the icon for the genlock toolbar entry
- L34 _private prototype_ `void GetTimecodeDropdownContent(UToolMenu* ToolMenu);` — Fills the dropdown menu for the timecode toolbar entry
- L37 _private prototype_ `void GetGenlockDropdownContent(UToolMenu* ToolMenu);` — Fills the dropdown menu for the genlock toolbar entry
- L41 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;` — Weak pointer to the media profile to source the timecode and genlock configuration from

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/UI/MediaFrameworkUtilitiesEditorStyle.h` (Private)


#### class `FMediaFrameworkUtilitiesEditorStyle`  
`class FMediaFrameworkUtilitiesEditorStyle`  
_L13-22_
- L16 _public prototype_ `static void Register();`
- L17 _public prototype_ `static void Unregister();`
- L19 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const ISlateStyle& Get();`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/UI/MediaProfileMenuEntry.h` (Private)


#### class `FMediaProfileMenuEntry`  
`class FMediaProfileMenuEntry`  
_L9-14_
- L12 _public prototype_ `static void Register();`
- L13 _public prototype_ `static void Unregister();`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/UI/SMediaFrameworkTimecodeGenlockHeader.h` (Private)


#### class `SMediaFrameworkTimecodeGenlockHeader`  
`class SMediaFrameworkTimecodeGenlockHeader : public SCompoundWidget`  
_L12-57_
- inherits: `SCompoundWidget`
- desc: Widget that displays the timecode and genlock status for a media profile that can be displayed in toolbars or details panel headers
- L15 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkTimecodeGenlockHeader) : _IsButton(false) , _ShowTimecode(true) , _ShowGenlock(true)`
- L20 _public prototype_ `SLATE_ARGUMENT(bool, IsButton) SLATE_ATTRIBUTE(bool, ShowTimecode) SLATE_ATTRIBUTE(bool, ShowGenlock) SLATE_EVENT(FSimpleDelegate, OnOpenTimecodeTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `FText GetTooltipText() const;` — Gets the text to display in the tooltip for the widget
- L34 _private prototype_ `FText GetTimecodeText() const;` — Gets the text to display for the timecode
- L37 _private prototype_ `const FSlateBrush* GetGenlockIcon() const;` — Gets the icon to display for the genlock
- L40 _private prototype_ `FText GetGenlockText() const;` — Gets the text to display for the genlock
- L43 _private prototype_ `FReply OnButtonClicked();` — Raised when the toolbar button is clicked
- L46 _private prototype_ `EVisibility GetElementVisibility(bool bTimecode, bool bGenlock) const;` — Gets whether certain elements of the toolbar entry should be visible
- L50 _private member_ `TAttribute<bool> ShowTimecodeAttr;` — Gets whether the timecode should be shown
- L53 _private member_ `TAttribute<bool> ShowGenlockAttr;` — Gets whether the genlock should be shown
- L56 _private member_ `FSimpleDelegate OnOpenTimecodeTab;` — Raised when the header is requesting the TC/Genlock tab be opened/focused

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/UI/SMediaFrameworkTimecodeGenlockPanel.h` (Private)


#### class `SMediaFrameworkTimecodeGenlockPanel`  
`class SMediaFrameworkTimecodeGenlockPanel : public SCompoundWidget, public FNotifyHook`  
_L15-38_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Details panel that displays a media profile's Timecode and Genlock settings, as well as a timecode/genlock status bar and optionally a media profile selection dropdown
- L18 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkTimecodeGenlockPanel)`
- L19 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UMediaProfile>, MediaProfile) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L30 _private prototype_ `void RefreshTimecodeGenlock(bool bRefreshTimecode, bool bRefreshGenlock);` — Refreshes the timecode and genlock to match the settings in the current media profile
- L34 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile;` — Media profile whose timecode/genlock settings are being displayed
- L37 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details view displaying timecode/genlock properties

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/VideoInputTab/SMediaFrameworkVideoInput.h` (Private)


#### class `SMediaFrameworkVideoInput`  
`class SMediaFrameworkVideoInput : public SCompoundWidget`  
_L25-78_
- inherits: `SCompoundWidget`
- desc: SMediaFrameworkVideoInput is a class that manage the video input tab and it's registration in the level editor
- L28 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L29 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L32 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkVideoInput)`
- L35 _public prototype_ `virtual ~SMediaFrameworkVideoInput();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public function_ `bool IsPlaying() const` — Tell if the video input tab is currently playing
- L45 _private prototype_ `TSharedRef<class SWidget> MakeToolBar();`
- L50 _private prototype_ `bool CanPlay() const;` — Determinate if the video input player can play it's video sources
- L55 _private prototype_ `void Play();` — If it can, start playing and displaying the video sources
- L60 _private prototype_ `void Stop();` — Stop playing and displaying the video sources
- L65 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu();` — Create the settings menu
- L67 _private prototype_ `void OnAssetsPreDelete(const TArray<UObject*>& Objects);`
- L68 _private prototype_ `void OnObjectPreEditChange(UObject* Object, const FEditPropertyChain& PropertyChain);`
- L69 _private prototype_ `void OnObjectPostEditChange(UObject* Object, FPropertyChangedEvent& InPropertyChangedEvent);`
- L72 _private member_ `TSharedPtr<IDetailsView> DetailView;`
- L73 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L74 _private member_ `TSharedPtr<MediaFrameworkVideoInputUtils::SVideoInputDisplayVerticalBox> VideosViewport;`
- L76 _private member_ `bool bIsPlaying;`
- L77 _private member_ `static FDelegateHandle LevelEditorTabManagerChangedHandle;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace MediaFrameworkVideoInputUtils`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/VideoInputTab/SMediaFrameworkVideoInputDisplay.h` (Private)


#### class `UMediaFrameworkVideoInputDisplayCallback`  
`class UMediaFrameworkVideoInputDisplayCallback : public UObject`  
_L24-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Callback object for SMediaFrameworkVideoInputDisplay
- L30 _public prototype_ `void OnMediaClosed();` — `UFUNCTION()`
- L32 _public member_ `TWeakPtr<SMediaFrameworkVideoInputDisplay> Owner;`

#### class `SMediaFrameworkVideoInputDisplay`  
`class SMediaFrameworkVideoInputDisplay : public SCompoundWidget`  
_L38-99_
- inherits: `SCompoundWidget`
- desc: SMediaFrameworkVideoInputDisplay is a specialize widget for the video input tab. It displays a video feed.
- L41 _protected prototype_ `SMediaFrameworkVideoInputDisplay();`
- L42 _protected prototype_ `virtual ~SMediaFrameworkVideoInputDisplay();`
- L44 _protected prototype_ `void Construct(const FString& SourceName);`
- L46 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector);`
- L47 _protected prototype_ `virtual UMediaPlayer* GetMediaPlayer() const = 0;`
- L48 _protected prototype_ `virtual UMediaTexture* GetMediaTexture() const = 0;`
- L49 _protected prototype_ `virtual void RestartPlayer() = 0;`
- L51 _protected prototype_ `void AttachCallback();`
- L52 _protected prototype_ `void DetachCallback();`
- L53 _protected prototype_ `void OnMediaClosed();`
- L57 _private prototype_ `TSharedRef<SWidget> ConstructVideoDisplay();`
- L58 _private prototype_ `TSharedRef<SWidget> ConstructVideoStateDisplay(const FString& SourceName);`
- L60 _private prototype_ `FSlateColor HandleSourceStateColorAndOpacity() const;`
- L61 _private prototype_ `FText HandleSourceStateText() const;`
- L86 _private member_ `FInternalReferenceCollector Collector;` — Collector to keep the UObject alive.
- L89 _private member_ `TObjectPtr< UMaterial> Material;` — The material that wraps the video texture for display in an SImage.
- L92 _private member_ `TObjectPtr<UMediaFrameworkVideoInputDisplayCallback> MediaPlayerCallback;` — Callback object for the MediaPlayer.
- L95 _private member_ `FTimerHandle RestartPlayerTimerHandle;` — Timer handle when an error occurred.
- L98 _private member_ `TSharedPtr<FSlateBrush> MaterialBrush;` — The Slate brush that renders the material.

#### class `SMediaFrameworkVideoInputDisplay::FInternalReferenceCollector`  
`class FInternalReferenceCollector : public FGCObject`  
_L63-82_
- inherits: `FGCObject`
- L66 _public function_ `FInternalReferenceCollector(SMediaFrameworkVideoInputDisplay* InObject) : Object(InObject)`
- L71 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override`
- L75 _public function_ `virtual FString GetReferencerName() const override`
- L81 _private member_ `SMediaFrameworkVideoInputDisplay* Object;`

#### class `SMediaFrameworkVideoInputMediaBundleDisplay`  
`class SMediaFrameworkVideoInputMediaBundleDisplay : public SMediaFrameworkVideoInputDisplay`  
_L104-127_
- inherits: `SMediaFrameworkVideoInputDisplay`
- desc: SMediaFrameworkVideoInputMediaBundleDisplay is a specialize widget for the video input tab. It displays the video feed of a MediaBundle
- L107 _private typedef_ `using Super = SMediaFrameworkVideoInputDisplay;`
- L110 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkVideoInputMediaBundleDisplay)`
- L111 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UMediaBundle>, MediaBundle) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L116 _public prototype_ `SMediaFrameworkVideoInputMediaBundleDisplay();`
- L117 _public prototype_ `virtual ~SMediaFrameworkVideoInputMediaBundleDisplay();`
- L120 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L121 _private prototype_ `virtual UMediaPlayer* GetMediaPlayer() const override;`
- L122 _private prototype_ `virtual UMediaTexture* GetMediaTexture() const override;`
- L123 _private prototype_ `virtual void RestartPlayer() override;`
- L125 _private member_ `TObjectPtr<UMediaBundle> MediaBundle;`
- L126 _private member_ `bool bDidMediaBundleOpen;`

#### class `SMediaFrameworkVideoInputMediaSourceDisplay`  
`class SMediaFrameworkVideoInputMediaSourceDisplay : public SMediaFrameworkVideoInputDisplay`  
_L132-157_
- inherits: `SMediaFrameworkVideoInputDisplay`
- desc: SMediaFrameworkVideoInputMediaSourceDisplay is a specialize widget for the video input tab. It displays the video feed of a MediaSource
- L135 _private typedef_ `using Super = SMediaFrameworkVideoInputDisplay;`
- L138 _public function_ `SLATE_BEGIN_ARGS(SMediaFrameworkVideoInputMediaSourceDisplay)`
- L139 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UMediaSource>, MediaSource) SLATE_ARGUMENT(TWeakObjectPtr<UMediaTexture>, MediaTexture) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L145 _public prototype_ `SMediaFrameworkVideoInputMediaSourceDisplay();`
- L146 _public prototype_ `virtual ~SMediaFrameworkVideoInputMediaSourceDisplay();`
- L149 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L150 _private prototype_ `virtual UMediaPlayer* GetMediaPlayer() const override;`
- L151 _private prototype_ `virtual UMediaTexture* GetMediaTexture() const override;`
- L152 _private prototype_ `virtual void RestartPlayer() override;`
- L154 _private member_ `TObjectPtr<UMediaSource> MediaSource;`
- L155 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;`
- L156 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;`
