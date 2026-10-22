# Plugins / BinkMediaPlayerEditor

- module root: `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor`
- headers: 9; symbols: 88
- symbol kinds: class=3, function=46, macro=1, member=17, prototype=15, struct=6
- DynamicallyLoadedModuleNames: AssetTools, MainFrame, WorkspaceMenuStructure
- PrivateDependencyModuleNames: BinkMediaPlayer, ContentBrowser, Core, CoreUObject, DesktopPlatform, Engine, InputCore, PropertyEditor, RHI, RenderCore, Slate, SlateCore, TextureEditor, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: BinkMediaPlayer, MetalRHI

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/BinkMediaPlayerCustomization.h` (Private)


#### struct `FBinkMediaPlayerCustomization`  
`struct FBinkMediaPlayerCustomization : public IDetailCustomization`  
_L13-38_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;`
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `FText HandleDurationTextBlockText() const;`
- L23 _public function_ `FString HandleUrlPickerFilePath() const`
- L29 _public function_ `FString HandleUrlPickerFileTypeFilter() const`
- L33 _public prototype_ `void HandleUrlPickerPathPicked( const FString& PickedPath );`
- L34 _public prototype_ `EVisibility HandleUrlWarningIconVisibility() const;`
- L36 _public member_ `TArray<TWeakObjectPtr<UObject>> CustomizedMediaPlayers;`
- L37 _public member_ `TSharedPtr<IPropertyHandle> UrlProperty;`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/BinkMediaPlayerEditorPrivate.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/BinkMediaPlayerEditorToolkit.h` (Private)


#### struct `FBinkMediaPlayerEditorToolkit`  
`struct FBinkMediaPlayerEditorToolkit : public FAssetEditorToolkit, public FEditorUndoClient, public FGCObject`  
_L13-71_
- inherits: `FAssetEditorToolkit,FEditorUndoClient,FGCObject`
- L15 _public function_ `FBinkMediaPlayerEditorToolkit( const TSharedRef<ISlateStyle>& InStyle ) : MediaPlayer(nullptr) , Style(InStyle)`
- L21 _public function_ `virtual ~FBinkMediaPlayerEditorToolkit()`
- L30 _public prototype_ `void Initialize( UBinkMediaPlayer* InMediaPlayer, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost );`
- L34 _public function_ `virtual FString GetDocumentationLink() const override`
- L35 _public prototype_ `virtual void RegisterTabSpawners( const TSharedRef<class FTabManager>& TabManager ) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners( const TSharedRef<class FTabManager>& TabManager ) override;`
- L40 _public function_ `virtual FText GetBaseToolkitName() const override`
- L41 _public function_ `virtual FName GetToolkitFName() const override`
- L42 _public function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L43 _public function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L47 _public function_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override`
- L48 _public function_ `virtual FString GetReferencerName() const override`
- L55 _public function_ `virtual void PostUndo( bool bSuccess ) override`
- L56 _public function_ `virtual void PostRedo( bool bSuccess ) override`
- L60 _private function_ `bool HandlePauseMediaActionCanExecute() const`
- L61 _private function_ `void HandlePauseMediaActionExecute()`
- L62 _private function_ `bool HandlePlayMediaActionCanExecute() const`
- L63 _private function_ `void HandlePlayMediaActionExecute()`
- L64 _private function_ `bool HandleRewindMediaActionCanExecute() const`
- L65 _private function_ `void HandleRewindMediaActionExecute()`
- L66 _private prototype_ `void HandleEditorEndPIE(bool bIsSimulating);`
- L68 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab( const FSpawnTabArgs& Args, FName TabIdentifier );`
- L69 _private member_ `TObjectPtr<UBinkMediaPlayer> MediaPlayer;`
- L70 _private member_ `TSharedRef<ISlateStyle> Style;`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/Factories/BinkMediaPlayerFactory.h` (Private)


#### class `UBinkMediaPlayerFactory`  
`class UBinkMediaPlayerFactory : public UFactory`  
_L10-15_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L14 _public prototype_ `virtual UObject* FactoryCreateBinary( UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn ) override;`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/Factories/BinkMediaPlayerFactoryNew.h` (Private)


#### class `UBinkMediaPlayerFactoryNew`  
`class UBinkMediaPlayerFactoryNew : public UFactory`  
_L11-23_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L15 _public function_ `virtual UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn ) override`
- L19 _public function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/Factories/BinkMediaTextureFactoryNew.h` (Private)


#### class `UBinkMediaTextureFactoryNew`  
`class UBinkMediaTextureFactoryNew : public UFactory`  
_L10-22_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _public member_ `TObjectPtr<class UBinkMediaPlayer> InitialMediaPlayer;` — `UPROPERTY()`
- L17 _public prototype_ `virtual UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn ) override;`
- L18 _public function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/Models/BinkMediaPlayerEditorCommands.h` (Private)


#### struct `FBinkMediaPlayerEditorCommands`  
`struct FBinkMediaPlayerEditorCommands : public TCommands<FBinkMediaPlayerEditorCommands>`  
_L8-28_
- inherits: `TCommands<FBinkMediaPlayerEditorCommands>`
- L10 _public function_ `FBinkMediaPlayerEditorCommands() : TCommands<FBinkMediaPlayerEditorCommands>("BinkMediaPlayerEditor", NSLOCTEXT("Contexts", "BinkMediaPlayerEditor", "Bink MediaPlayer Editor"), NAME_None, "BinkMediaPlayerEditorStyle")`
- L15 _public function_ `virtual void RegisterCommands() override`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ForwardMedia;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> PauseMedia;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> PlayMedia;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ReverseMedia;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> RewindMedia;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE ""`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/Models/BinkMediaPlayerEditorTexture.h` (Private)


#### struct `FBinkMediaPlayerEditorTexture`  
`struct FBinkMediaPlayerEditorTexture : public FTickableGameObject`  
_L10-47_
- inherits: `FTickableGameObject`
- L12 _public function_ `FBinkMediaPlayerEditorTexture( FSlateTexture2DRHIRef* InSlateTexture, UBinkMediaPlayer *InMediaPlayer ) : FTickableGameObject() , SlateTexture(InSlateTexture) , MediaPlayer(InMediaPlayer)`
- L19 _public function_ `~FBinkMediaPlayerEditorTexture()`
- L23 _public function_ `virtual void Tick( float DeltaTime ) override`
- L41 _public function_ `virtual TStatId GetStatId() const override`
- L42 _public function_ `virtual bool IsTickable() const override`
- L43 _public function_ `virtual bool IsTickableInEditor() const override`
- L45 _public member_ `FSlateTexture2DRHIRef* SlateTexture;`
- L46 _public member_ `UBinkMediaPlayer *MediaPlayer;`

#### Free symbols / members of external scopes

- L26 _function_ `` (scope `FBinkMediaPlayerEditorTexture::Tick`)

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayerEditor/Private/SBinkWidgets.h` (Private)


#### struct `SBinkMediaPlayerEditorDetails`  
`struct SBinkMediaPlayerEditorDetails : SCompoundWidget`  
_L12-22_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SBinkMediaPlayerEditorDetails)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UBinkMediaPlayer* InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle );`
- L21 _public member_ `UBinkMediaPlayer* MediaPlayer;`

#### struct `SBinkMediaPlayerEditorViewer`  
`struct SBinkMediaPlayerEditorViewer : SCompoundWidget`  
_L24-104_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SBinkMediaPlayerEditorViewer)`
- L31 _public function_ `SBinkMediaPlayerEditorViewer() : MediaPlayer()`
- L34 _public function_ `~SBinkMediaPlayerEditorViewer()`
- L42 _public prototype_ `void Construct( const FArguments& InArgs, UBinkMediaPlayer* InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle );`
- L43 _public prototype_ `void ReloadMediaPlayer();`
- L45 _public prototype_ `FText HandleOverlayStateText() const;`
- L46 _public function_ `FText HandleRemainingTimeTextBlockText() const`
- L51 _public function_ `void HandlePositionSliderMouseCaptureBegin()`
- L59 _public function_ `float HandlePositionSliderValue() const`
- L63 _public function_ `void HandlePositionSliderMouseCaptureEnd()`
- L71 _public function_ `void HandlePositionSliderValueChanged( float NewValue )`
- L79 _public function_ `EActiveTimerReturnType HandleActiveTimer(double InCurrentTime, float InDeltaTime)`
- L83 _public function_ `FText HandleElapsedTimeTextBlockText() const`
- L87 _public function_ `void HandleMediaPlayerMediaChanged()`
- L91 _public function_ `EVisibility HandleNoMediaSelectedTextVisibility() const`
- L95 _public function_ `bool HandlePositionSliderIsEnabled() const`
- L100 _public member_ `UBinkMediaPlayer* MediaPlayer;`
- L101 _public member_ `float PreScrubRate;`
- L102 _public member_ `TSharedPtr<SSlider> ScrubberSlider;`
- L103 _public member_ `TSharedPtr<FBinkMediaPlayerEditorViewport> Viewport;`
