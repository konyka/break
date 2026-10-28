# Plugins / ActorPalette

- module root: `Plugins/Experimental/ActorPalette/Source/ActorPalette`
- headers: 7; symbols: 77
- symbol kinds: class=7, function=5, macro=1, member=23, prototype=39, struct=2
- PrivateDependencyModuleNames: ContentBrowser, CoreUObject, DeveloperSettings, Engine, InputCore, Projects, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Private/ActorPalette.h` (Private)


#### class `SActorPalette`  
`class SActorPalette : public SCompoundWidget`  
_L12-25_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SActorPalette)`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, int32 InTabIndex);`
- L22 _private member_ `TSharedPtr<SActorPaletteViewport> ActorPaletteViewport;`
- L23 _private member_ `TSharedPtr<FActorPaletteViewportClient> ActorPaletteViewportClient;`
- L24 _private member_ `int32 TabIndex;`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Private/ActorPaletteSettings.h` (Private)


#### struct `FActorPaletteMapEntry`  
`struct FActorPaletteMapEntry`  
_L11-25_
- reflection: `USTRUCT()`
- desc: Information about a single recent/favorite map
- L16 _public member_ `FString MapPath;` — `UPROPERTY(EditAnywhere, Category=ActorPalette)`
- L24 _public prototype_ `FAssetData GetAsAssetData() const;`

#### class `UActorPaletteSettings`  
`class UActorPaletteSettings : public UDeveloperSettings`  
_L29-81_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Settings/preferences for Actor Palettes
- L34 _public prototype_ `UActorPaletteSettings();`
- L46 _public member_ `TArray<FActorPaletteMapEntry> SettingsPerLevel;` — `UPROPERTY(config)` — Remembered settings for any recent/current/favorite actor palette maps
- L50 _public member_ `TArray<FString> RecentlyUsedList;` — `UPROPERTY(config)` — List of levels that were recently open in any Actor Palette tab
- L54 _public member_ `TArray<FString> MostRecentLevelByTab;` — `UPROPERTY(config)` — List of levels that were last open in each Actor Palette tab (indexed by tab index)
- L58 _public member_ `TArray<FString> FavoritesList;` — `UPROPERTY(config)` — List of levels that were marked as favorite actor palettes
- L66 _public member_ `int32 NumRecentLevelsToKeep = 10;` — `UPROPERTY(config, EditAnywhere, Category=ActorPalette, meta=(ClampMin=0, ClampMax=25))` — How many recent levels will be remembered?
- L70 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L74 _public prototype_ `int32 FindMapEntry(const FString& MapName) const;`
- L75 _public prototype_ `int32 FindLastLevelForTab(int32 TabIndex) const;`
- L78 _public prototype_ `void MarkAsRecentlyUsed(const FAssetData& MapAsset, int32 TabIndex);`
- L79 _public prototype_ `void ToggleFavorite(const FAssetData& MapAsset);`
- L80 _public prototype_ `void TrimRecentList();`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Private/ActorPaletteViewport.h` (Private)


#### class `SActorPaletteViewport`  
`class SActorPaletteViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L14-47_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L17 _public function_ `SLATE_BEGIN_ARGS(SActorPaletteViewport)`
- L20 _public prototype_ `~SActorPaletteViewport();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FActorPaletteViewportClient> InViewportClient, int32 InTabIndex);`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;` — SEditorViewport interface
- L27 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L28 _public prototype_ `virtual void BindCommands() override;`
- L29 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L33 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L34 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L35 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L39 _protected prototype_ `FText GetTitleText() const;`
- L40 _protected prototype_ `TSharedRef<SWidget> GenerateMapMenu() const;`
- L43 _private member_ `TSharedPtr<FActorPaletteViewportClient> TypedViewportClient;`
- L44 _private member_ `int32 TabIndex;`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Private/ActorPaletteViewportClient.h` (Private)


#### class `FActorPaletteViewportClient`  
`class FActorPaletteViewportClient : public FEditorViewportClient`  
_L16-51_
- inherits: `FEditorViewportClient`
- L19 _public prototype_ `FActorPaletteViewportClient(int32 InTabIndex);`
- L22 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;` — FViewportClient interface
- L26 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient interface
- L27 _public prototype_ `void Tick(float DeltaSeconds) override;`
- L30 _public prototype_ `void OpenWorldAsPalette(const FAssetData& SourceWorldAsset);`
- L31 _public function_ `FAssetData GetCurrentWorldAssetData() const`
- L33 _public function_ `void SetOwnerWidget(const TWeakPtr<SEditorViewport> OwnerPtr)`
- L38 _public prototype_ `void ResetCameraView();`
- L41 _private member_ `int32 TabIndex;`
- L44 _private member_ `FPreviewScene OwnedPreviewScene;` — The preview scene
- L46 _private member_ `FAssetData SourceWorldAsset;`
- L48 _private member_ `ULevelStreamingDynamic* CurrentLevelStreaming = nullptr;`
- L50 _private member_ `FLinearColor MyBGColor;`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Public/ActorPaletteCommands.h` (Public)


#### class `FActorPaletteCommands`  
`class FActorPaletteCommands : public TCommands<FActorPaletteCommands>`  
_L9-24_
- inherits: `TCommands<FActorPaletteCommands>`
- L13 _public function_ `FActorPaletteCommands() : TCommands<FActorPaletteCommands>(TEXT("ActorPalette"), NSLOCTEXT("Contexts", "ActorPalette", "ActorPalette Plugin"), NAME_None, FActorPaletteStyle::GetStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L22 _public member_ `TSharedPtr<FUICommandInfo> ToggleGameView;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ResetCameraView;`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Public/ActorPaletteModule.h` (Public)


#### class `FActorPaletteModule`  
`class FActorPaletteModule : public IModuleInterface`  
_L12-38_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `void PluginButtonClicked();` — This function will be bound to Command (by default it will bring up plugin window)
- L24 _private prototype_ `TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs, int32 TabIndex);`
- L26 _private prototype_ `static FText GetActorPaletteLabelWithIndex(int32 TabIndex);`
- L27 _private prototype_ `FText GetActorPaletteTabLabel(int32 TabIndex) const;`
- L36 _private member_ `FActorPaletteTabInfo ActorPaletteTabs[MAX_ACTOR_PALETTES];`
- L37 _private member_ `TSharedPtr<class FUICommandList> PluginCommands;`

#### struct `FActorPaletteModule::FActorPaletteTabInfo`  
`struct FActorPaletteTabInfo`  
_L30-34_
- L32 _public member_ `FName TabID;`
- L33 _public member_ `TWeakPtr<SActorPalette> OpenInstance;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define MAX_ACTOR_PALETTES 4`

### `Plugins/Experimental/ActorPalette/Source/ActorPalette/Public/ActorPaletteStyle.h` (Public)


#### class `FActorPaletteStyle`  
`class FActorPaletteStyle`  
_L9-32_
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L31 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`
