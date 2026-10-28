# Plugins / MetaHumanFootageIngest

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest`
- headers: 10; symbols: 354
- symbol kinds: class=12, delegate=8, enum=4, enumerator=16, function=10, macro=3, member=112, namespace=2, prototype=184, struct=2, typedef=1
- PrivateDependencyModuleNames: CaptureDataCore, CaptureDataUtils, ContentBrowserData, CoreUObject, EditorStyle, Engine, GeometryCore, GeometryFramework, ImgMedia, InputCore, Json, LauncherPlatform, LiveLinkHubEditor, MeshDescription, MeshTrackerInterface, MetaHumanCaptureData, MetaHumanCaptureSource, MetaHumanCaptureUtils, MetaHumanCore, MetaHumanCoreEditor, Networking, Projects, PropertyEditor, Slate, SlateCore, Sockets, StaticMeshDescription, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Private/DevelopersContentFilter.h` (Private)


#### enum `UE::MetaHuman::EDevelopersContentVisibility`  
`enum class EDevelopersContentVisibility`  
_L10-14_
- L12 _public enumerator_ `Visible`
- L13 _public enumerator_ `NotVisible`

#### enum `UE::MetaHuman::EOtherDevelopersContentVisibility`  
`enum class EOtherDevelopersContentVisibility`  
_L16-20_
- L18 _public enumerator_ `Visible`
- L19 _public enumerator_ `NotVisible`

#### class `UE::MetaHuman::FDevelopersContentFilter`  
`class FDevelopersContentFilter`  
_L22-41_
- L25 _public prototype_ `FDevelopersContentFilter( EDevelopersContentVisibility InDevelopersContentVisibility, EOtherDevelopersContentVisibility InOtherDevelopersContentVisibility );`
- L30 _public prototype_ `bool PassesFilter(const FString& InAssetPath) const;`
- L31 _public prototype_ `EDevelopersContentVisibility GetDevelopersContentVisibility() const;`
- L32 _public prototype_ `EOtherDevelopersContentVisibility GetOtherDevelopersContentVisibility() const;`
- L35 _private member_ `FString BaseDeveloperPath;`
- L36 _private member_ `TArray<ANSICHAR> BaseDeveloperPathAnsi;`
- L37 _private member_ `FString UserDeveloperPath;`
- L38 _private member_ `TArray<ANSICHAR> UserDeveloperPathAnsi;`
- L39 _private member_ `EDevelopersContentVisibility DevelopersContentVisibility;`
- L40 _private member_ `EOtherDevelopersContentVisibility OtherDevelopersContentVisibility;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Private/MetaHumanFootageIngestModule.h` (Private)


#### class `FMetaHumanFootageIngestModule`  
`class FMetaHumanFootageIngestModule : public IModuleInterface`  
_L7-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `class FCaptureManager* CaptureManager = nullptr;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Private/Utils/AppleDeviceList.h` (Private)


#### class `FAppleDeviceList`  
`class FAppleDeviceList`  
_L8-14_
- L11 _public typedef_ `using FDeviceMap = TMap<FString, FString>;`
- L13 _public member_ `static const FDeviceMap DeviceMap;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/CaptureManager.h` (Public)


#### class `FCaptureManager`  
`FCaptureManager : public TSharedFromThis<SWidget>`  
_L13-40_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `TSharedFromThis<SWidget>`
- desc: Enables 'this->AsShared()'
- L16 _public prototype_ `static FCaptureManager* Get();`
- L17 _public prototype_ `static void Initialize();`
- L18 _public prototype_ `static void Terminate();`
- L19 _public prototype_ `void Show();`
- L21 _public prototype_ `TWeakPtr<SDockTab> ShowMonitoringTab(UMetaHumanCaptureSource* CaptureSource);` — TODO: add parameter to determine which tab should be shown
- L25 _private prototype_ `void OnCaptureManagerTabClosed(TSharedRef<class SDockTab> ClosedTab);`
- L26 _private prototype_ `bool OnCanCloseCaptureTab();`
- L27 _private prototype_ `void OnMapOpened(const FString& FileName, bool bAsTemplate);`
- L29 _private prototype_ `FCaptureManager();`
- L30 _private prototype_ `~FCaptureManager();`
- L31 _private prototype_ `void RegisterTabSpawner();`
- L32 _private prototype_ `void UnregisterTabSpawner();`
- L35 _private member_ `static FCaptureManager* Instance;`
- L36 _private member_ `TSharedPtr<SCaptureManagerWidget> CaptureManagerWidget;`
- L38 _private member_ `TSharedPtr<class FCaptureManagerCommands> Commands;`
- L39 _private member_ `FDelegateHandle OnMapOpenedDelegateHandle;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/CaptureManagerCommands.h` (Public)


#### class `FCaptureManagerCommands`  
`FCaptureManagerCommands : public TCommands<FCaptureManagerCommands>`  
_L9-24_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `TCommands<FCaptureManagerCommands>`
- L13 _public prototype_ `FCaptureManagerCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L19 _public member_ `TSharedPtr<FUICommandInfo> Save;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> SaveAll;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> StartStopCapture;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/CaptureManagerLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManager, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManager, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/CaptureManagerWidget.h` (Public)


#### class `UCaptureManagerEditorContext`  
`UCaptureManagerEditorContext : public UObject`  
_L21-28_
- reflection: `UCLASS(meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `UObject`
- L27 _public member_ `TWeakPtr<class SCaptureManagerWidget> CaptureManagerWidget;`

#### class `SCaptureManagerWidget`  
`SCaptureManagerWidget : public SCompoundWidget`  
_L34-220_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `SCompoundWidget`
- desc: A widget that allows management of capture sources, footage ingestion and controlling of capture devices
- L37 _public function_ `SLATE_BEGIN_ARGS(SCaptureManagerWidget)`
- L39 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FCaptureManagerCommands>, CaptureManagerCommands) PRAGMA_ENABLE_DEPRECATION_WARNINGS SLATE_END_ARGS() SCaptureManagerWidget();`
- L44 _public prototype_ `~SCaptureManagerWidget();`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<SWindow>& OwningWindow, const TSharedRef<class SDockTab>& OwningTab);`
- L48 _public prototype_ `struct FTabSpawnerEntry& RegisterCaptureSourcesTabSpawner();`
- L49 _public prototype_ `struct FTabSpawnerEntry& RegisterFootageIngestTabSpawner();`
- L51 _public prototype_ `TWeakPtr<class SDockTab> ShowMonitoringTab( UMetaHumanCaptureSource* CaptureSource );`
- L53 _public prototype_ `bool CanClose();`
- L54 _public prototype_ `void OnClose();`
- L55 _public prototype_ `void UpdateDefaultAssetCreationLocation();`
- L59 _private prototype_ `void RegisterCommands();`
- L60 _private prototype_ `void Initialize();`
- L61 _private prototype_ `void RemoveDynamicToolbarSection() const;`
- L63 _private prototype_ `void ShowCMToolbar(IConsoleVariable* InVar);`
- L65 _private member_ `static const FName CaptureSourcesTabName;`
- L66 _private member_ `static const FName FootageIngestTabName;`
- L68 _private member_ `TSharedPtr<class FTabManager> TabManager;`
- L69 _private member_ `TMap<TWeakObjectPtr<UMetaHumanCaptureSource>, TWeakPtr<class SDockTab> > CaptureSourceToTabMap;`
- L71 _private member_ `TSharedPtr<class SExpandableArea> CaptureSourcesArea;`
- L72 _private member_ `TSharedPtr<class SExpandableArea> DeviceContentsArea;`
- L74 _private member_ `TSharedPtr<class SCaptureSourcesWidget> CaptureSourcesWidget;`
- L75 _private member_ `TSharedPtr<class SFootageIngestWidget> FootageIngestWidget;`
- L77 _private member_ `TSharedPtr<SListView<TSharedPtr<FFootageCaptureSource>>> SourceListView;`
- L80 _private prototype_ `void OnCurrentCaptureSourceChanged(TSharedPtr<FFootageCaptureSource> InCaptureSource, ESelectInfo::Type InSelectInfo);` — invoked by CaptureSourcesWidget after it has processed the event
- L83 _private prototype_ `void OnCaptureSourcesChanged(TArray<TSharedPtr<FFootageCaptureSource>> InCaptureSources);` — invoked by CaptureSourcesWidget after it has processed the event
- L86 _private prototype_ `void OnCaptureSourceUpdated(TSharedPtr<FFootageCaptureSource> InCaptureSource);` — invoked by CaptureSourcesWidget after it has processed the event
- L89 _private prototype_ `void OnCaptureSourceFinishedImportingTakes(const TArray<struct FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource);` — invoked by CaptureSourcesWidget after it has processed the event
- L92 _private prototype_ `void OnTargetFolderAssetPathChanged(FText InTargetFolderAssetPath);` — invoked by FootageIngestWidget after it has processed the event
- L94 _private prototype_ `FText GetStartStopCaptureButtonLabel() const;`
- L95 _private prototype_ `FText GetStartStopCaptureButtonTooltip() const;`
- L96 _private prototype_ `FSlateIcon GetStartStopCaptureButtonIcon() const;`
- L98 _private prototype_ `bool IsCurrentSourceRecording() const;`
- L100 _private prototype_ `void BindCommands();`
- L106 _private prototype_ `void InitToolMenuContext(struct FToolMenuContext& InMenuContext);`
- L108 _private prototype_ `FName GetToolkitFName() const;`
- L109 _private prototype_ `FName GetToolMenuAppName() const;`
- L110 _private prototype_ `FName GetToolMenuName() const;`
- L111 _private prototype_ `FName GetToolMenuToolbarName() const;`
- L112 _private prototype_ `FName GetToolMenuToolbarName(FName& OutParentName) const;`
- L114 _private function_ `const TSharedRef<FUICommandList> GetToolkitCommands() const`
- L120 _private prototype_ `void GenerateToolbar();` — generates the entire toolbar, with common actions, toolbar command buttons and misc widget on the right
- L121 _private prototype_ `void RegisterDefaultToolBar();`
- L122 _private prototype_ `void RegisterSettingsToolBar(const struct FToolMenuContext& MenuContext);`
- L126 _private function_ `FName GetToolMenuToolbarName()` — this is a method to imitate UAssetEditorToolkit API (which we are not using as Capture Manager is not an asset editor) so that the code to build toolbar doesn't change much to what it usually does
- L128 _private prototype_ `class UToolMenu* GenerateCommonActionsToolbar(struct FToolMenuContext& MenuContext);`
- L129 _private prototype_ `class UToolMenu* GenerateSettingsToolbar(struct FToolMenuContext& MenuContext);`
- L130 _private prototype_ `static TSharedRef<SWidget> GenerateQuickSettingsMenu();`
- L132 _private prototype_ `void GenerateMessageWidget();`
- L134 _private member_ `const static FName ToolMenuToolbarName;`
- L135 _private member_ `const static FName DefaultToolbarName;`
- L138 _private member_ `TSharedRef<FUICommandList> ToolkitUICommandList;` — List of UI commands for this toolkit.
- L141 _private member_ `TSharedPtr<SWidget> Toolbar;` — The main Toolbar
- L144 _private member_ `TSharedPtr<class SBorder> ToolbarWidgetContent;` — The widget that will house the default Toolbar widget
- L147 _private member_ `TArray<TSharedRef<SWidget>> ToolbarWidgets;` — Additional widgets to be added to the toolbar
- L148 _private member_ `bool bIsInitialized = false;`
- L151 _private member_ `TSharedPtr<SWidget> MessageWidget;` — The information message widget
- L156 _private member_ `TSharedPtr<FCaptureManagerCommands> Commands;`
- L159 _private member_ `TUniquePtr<FAutoConsoleCommand> StartCapture;`
- L160 _private member_ `TUniquePtr<FAutoConsoleCommand> StopCapture;`
- L162 _private prototype_ `void ExtendToolBar( bool bRegenerateDynamicSection = false);`
- L163 _private prototype_ `void ExtendMenu( bool bRegenerateMenu = false );`
- L165 _private prototype_ `TSharedRef<SWidget> GenerateTakeSlateWidget();`
- L167 _private prototype_ `static TSharedRef<SWidget> PopulateAddCaptureSourceComboBox();`
- L169 _private prototype_ `void CreateSelectedCaptureSourceType(int64 InType);`
- L170 _private prototype_ `FText GetCreationTooltip(FText InTypeName) const;`
- L172 _private prototype_ `bool CanSave();`
- L173 _private prototype_ `bool CanSaveAll();`
- L174 _private prototype_ `bool CanRefresh();`
- L175 _private prototype_ `bool CanStartStopCapture() const;`
- L176 _private prototype_ `bool IsCaptureSourceSelected() const;`
- L178 _private prototype_ `void HandleSave();`
- L179 _private prototype_ `void HandleSaveAll();`
- L180 _private prototype_ `void HandleRefresh();`
- L181 _private prototype_ `void HandleStartStopCaptureToggle();`
- L183 _private prototype_ `static void PresentTargetPicker();`
- L185 _private prototype_ `static FText GetAutoSaveOnImportTooltip();`
- L186 _private prototype_ `static void ToggleAutoSaveOnImport();`
- L187 _private prototype_ `static bool IsAutoSaveOnImportToggled();`
- L189 _private prototype_ `void StartCaptureConsoleHandler(const TArray<FString>& InArguments);`
- L190 _private prototype_ `void StopCaptureConsoleHandler();`
- L191 _private prototype_ `void StopCaptureHandler(FFootageCaptureSource* InSource, bool bInShouldFetchTake);`
- L193 _private prototype_ `bool VerifyTakeNumber(const FText& InNewNumber, FText& OutErrorText);`
- L194 _private prototype_ `void HandleTakeNumberCommited(const FText& InNewNumber, ETextCommit::Type InCommitType);`
- L195 _private prototype_ `FText GetTakeNumber() const;`
- L197 _private prototype_ `bool VerifySlateName(const FText& InNewName, FText& OutErrorText);`
- L198 _private prototype_ `void HandleSlateNameTextCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L199 _private prototype_ `FText GetSlateName() const;`
- L201 _private prototype_ `void ToggleShowDevelopersContent();`
- L202 _private prototype_ `bool IsShowingDevelopersContent();`
- L203 _private prototype_ `FText GetShowOtherDevelopersToolTip() const;`
- L204 _private prototype_ `void OnShowOtherDevelopersCheckStateChanged(ECheckBoxState InCheckboxState);`
- L205 _private prototype_ `ECheckBoxState GetShowOtherDevelopersCheckState() const;`
- L207 _private member_ `TSharedPtr<SEditableTextBox> SlateNameTextBox;`
- L208 _private member_ `TSharedPtr<SEditableTextBox> TakeNumberTextBox;`
- L210 _private member_ `bool bAutosaveAfterImport = true;`
- L211 _private member_ `FString DefaultAssetCreationPath;`
- L213 _private prototype_ `void RegenerateMenusAndToolbars();`
- L215 _private prototype_ `FReply OpenLiveLinkHub();`

#### Free symbols / members of external scopes

- L17 _macro_ `#define SHOW_MISC_WIDGETS`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/CaptureSourcesWidget.h` (Public)


#### enum `EFootageTakeItemStatus`  
`enum class EFootageTakeItemStatus`  
_L26-37_
- L28 _public enumerator_ `Unqueued`
- L29 _public enumerator_ `Queued`
- L30 _public enumerator_ `Warning`
- L31 _public enumerator_ `Ingest_Active`
- L32 _public enumerator_ `Ingest_Paused`
- L33 _public enumerator_ `Ingest_Canceled`
- L34 _public enumerator_ `Ingest_Failed`
- L35 _public enumerator_ `Ingest_Succeeded`
- L36 _public enumerator_ `Ingest_Succeeded_with_Warnings`

#### class `FFootageTakeItem`  
`FFootageTakeItem : public FGCObject`  
_L40-74_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `FGCObject`
- L44 _public member_ `FText Name;`
- L45 _public member_ `TakeId TakeId;`
- L46 _public member_ `int32 NumFrames;`
- L47 _public member_ `FString PathToTakeFolder;`
- L48 _public member_ `TSharedPtr<FSlateBrush> PreviewImage;`
- L49 _public member_ `TObjectPtr<class UTexture2D> PreviewImageTexture = nullptr;`
- L50 _public member_ `bool PreviewSet = false;`
- L52 _public member_ `EFootageTakeItemStatus Status;`
- L53 _public member_ `FString StatusMessage;`
- L55 _public member_ `FText DestinationFolder;`
- L57 _public member_ `TSharedPtr<FFootageCaptureSource> CaptureSource;`
- L59 _public function_ `virtual ~FFootageTakeItem()`
- L65 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L70 _public function_ `virtual FString GetReferencerName() const override`

#### enum `EFootageCaptureSourceStatus`  
`enum class EFootageCaptureSourceStatus`  
_L77-82_
- L79 _public enumerator_ `Closed`
- L80 _public enumerator_ `Offline`
- L81 _public enumerator_ `Online`

#### struct `FFootageCaptureSource`  
`struct FFootageCaptureSource`  
_L85-103_
- L87 _public prototype_ `explicit FFootageCaptureSource(UE::MetaHuman::FIngesterParams InIngesterParams);`
- L88 _public prototype_ `UE::MetaHuman::FIngester& GetIngester();`
- L90 _public member_ `FText Name;`
- L91 _public member_ `FString AssetPath;`
- L92 _public member_ `EFootageCaptureSourceStatus Status;`
- L93 _public member_ `bool bIsRecording = false;`
- L94 _public member_ `FString SlateName = TEXT("");`
- L95 _public member_ `int32 TakeNumber = 1;`
- L96 _public member_ `bool bImporting = false;`
- L97 _public member_ `FName PackageName;`
- L99 _public member_ `TArray<TSharedPtr<FFootageTakeItem>> TakeItems;`
- L102 _private member_ `TUniquePtr<UE::MetaHuman::FIngester> Ingester;`

#### struct `FFootageFolderTreeItem`  
`struct FFootageFolderTreeItem`  
_L106-111_
- L108 _public member_ `FText Name;`
- L109 _public member_ `TArray<TSharedPtr<FFootageFolderTreeItem>> Children;`
- L110 _public member_ `TWeakPtr<FFootageFolderTreeItem> Parent;`

#### class `UCaptureSourceSet`  
`UCaptureSourceSet : public UObject`  
_L124-129_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `UObject`
- L128 _public member_ `TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources;`

#### class `SCaptureSourcesWidget`  
`SCaptureSourcesWidget : public SCompoundWidget`  
_L132-237_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `SCompoundWidget`
- L136 _public function_ `SLATE_BEGIN_ARGS(SCaptureSourcesWidget) : _OwnerTab()`
- L139 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SDockTab>, OwnerTab) SLATE_EVENT(FOnCurrentCaptureSourceChanged, OnCurrentCaptureSourceChanged) SLATE_EVENT(FOnCaptureSourcesChanged, OnCaptureSourcesChanged) SLATE_EVENT(FOnCaptureSourceUpdated, OnCaptureSourceUpdated) SLATE_EVENT(FOnCaptureSourceFinishedImportingTakes, OnCaptureSourceFinishedImportingTakes) SLATE_END_ARGS() SCaptureSourcesWidget();`
- L148 _public prototype_ `~SCaptureSourcesWidget();`
- L150 _public prototype_ `void Construct(const FArguments& InArgs);`
- L152 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L154 _public prototype_ `void OnTargetFolderAssetPathChanged(FText InTargetFolderAssetPath);`
- L156 _public function_ `TArray<TSharedPtr<FFootageCaptureSource>> GetCaptureSources()`
- L158 _public prototype_ `void StartCaptureSources();`
- L159 _public prototype_ `void RefreshCurrentCaptureSource() const;`
- L161 _public prototype_ `const FFootageCaptureSource* GetCurrentCaptureSource() const;`
- L162 _public prototype_ `FFootageCaptureSource* GetCurrentCaptureSource();`
- L164 _public prototype_ `bool CanClose();`
- L165 _public prototype_ `void OnClose();`
- L167 _public prototype_ `bool IsShowingDevelopersContent() const;`
- L168 _public prototype_ `bool IsShowingOtherDevelopersContent() const;`
- L169 _public prototype_ `void ToggleShowDevelopersContent();`
- L170 _public prototype_ `void ToggleShowOtherDevelopersContent();`
- L174 _private prototype_ `void OnCurrentCaptureSourceChanged(TSharedPtr<FFootageCaptureSource> InCaptureSource, ESelectInfo::Type InSelectInfo);`
- L177 _private prototype_ `void OnCaptureSourceFinishedImportingTakes(const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource);`
- L180 _private prototype_ `void OnCaptureSourcePropertyEvent(UObject* InObject, FPropertyChangedEvent& InEvent);`
- L182 _private prototype_ `UFootageCaptureData* GetOrCreateCaptureData(const FString& InTargetIngestPath, const FString& InAssetName) const;`
- L184 _private member_ `static const FName CaptureSourcesTabId;`
- L186 _private prototype_ `void InitCaptureSourceList();`
- L187 _private prototype_ `void LoadCaptureSources(const TArray<FAssetData>& InAssetDataCollection);`
- L188 _private prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L189 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L190 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);`
- L191 _private prototype_ `void OnAssetUpdated(const FAssetData& InAssetData);`
- L192 _private prototype_ `void OnAssetReload(EPackageReloadPhase InPhase, FPackageReloadedEvent* InPackageEvent);`
- L193 _private prototype_ `bool IsCurrentCaptureSourceAssetValid() const;`
- L195 _private prototype_ `void UpdateCaptureSourceFilterSettings();`
- L196 _private prototype_ `void LoadCaptureSourceFilterFromSettings();`
- L197 _private prototype_ `void ToggleCaptureSourceFilterDevelopersContent();`
- L198 _private prototype_ `void ToggleCaptureSourceFilterShowOtherDevelopersContent();`
- L199 _private prototype_ `void FilterCaptureSourceList();`
- L201 _private member_ `TWeakPtr<SDockTab> OwnerTab = nullptr;`
- L204 _private member_ `TSharedPtr<SListView<TSharedPtr<FFootageCaptureSource>>> SourceListView;` — Widgets
- L206 _private member_ `TSharedPtr<SExpandableArea> CaptureSourcesArea;`
- L207 _private member_ `TSharedPtr<SExpandableArea> DeviceContentsArea;`
- L209 _private member_ `TArray<TSharedPtr<FFootageFolderTreeItem>> FolderTreeItemList;`
- L211 _private member_ `TArray<TSharedPtr<FFootageCaptureSource>> CaptureSources;`
- L212 _private member_ `TSharedPtr<FFootageCaptureSource> CurrentCaptureSource;`
- L216 _private member_ `FOnCurrentCaptureSourceChanged OnCurrentCaptureSourceChangedDelegate;` — this delegate is passed from CaptureManagerWidget and invoked in OnCaptureSourceChanged of this class so other CaptureManager's tabs (FootageIngest) can react to the change AFTER it has been handled by CaptureSources list
- L220 _private member_ `FOnCaptureSourcesChanged OnCaptureSourcesChangedDelegate;` — this delegate is passed from CaptureManagerWidget and invoked in OnCaptureSourceChanged of this class so other CaptureManager's tabs (FootageIngest) can react to the change AFTER it has been handled by CaptureSources list
- L224 _private member_ `FOnCaptureSourceUpdated OnCaptureSourceUpdatedDelegate;` — this delegate is passed from CaptureManagerWidget and invoked in OnCaptureSourceChanged of this class so other CaptureManager's tabs (FootageIngest) can react to the change AFTER it has been handled by CaptureSources list
- L228 _private member_ `FOnCaptureSourceFinishedImportingTakes OnCaptureSourceFinishedImportingTakesDelegate;` — this delegate is passed from CaptureManagerWidget and invoked in OnCaptureSourceFinishedImportingTakesDelegate of this class so other CaptureManager's tabs (FootageIngest) can react to the change AFTER it has been handled by CaptureSources list
- L231 _private member_ `FText TargetFolderAssetPath;` — the asset path for the folder picked in the Target Folder Picker of FootageIngestWidget
- L233 _private member_ `UE::MetaHuman::FDevelopersContentFilter DevelopersContentFilter;`
- L236 _private member_ `TArray<TSharedPtr<FFootageCaptureSource>> FilteredCaptureSources;` — We maintain a separate "view" into the capture sources list, to keep the management of the sources and the properties of the view separate

#### Free symbols / members of external scopes

- L113 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCurrentCaptureSourceChanged, const TSharedPtr<FFootageCaptureSource>, ESelectInfo::Type InSelectInfo) DECLARE_DELEGATE_OneParam(FOnCaptureSourcesChanged, const TArray<TSharedPtr<FFootageCaptureSource>>) DECLARE_DELEGATE_OneParam(FOnCaptureSourceUpdated, const TSharedPtr<FFootageCaptureSource>) PRAGMA_DISABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_TwoParams(FOnCaptureSourceFinishedImportingTakes, const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_OneParam(FOnCaptureSourceRemoved, TSharedPtr<FFootageCaptureSource>) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") UCaptureSourceSet : public UObject { public: TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources; };`
- L114 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCaptureSourcesChanged, const TArray<TSharedPtr<FFootageCaptureSource>>) DECLARE_DELEGATE_OneParam(FOnCaptureSourceUpdated, const TSharedPtr<FFootageCaptureSource>) PRAGMA_DISABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_TwoParams(FOnCaptureSourceFinishedImportingTakes, const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_OneParam(FOnCaptureSourceRemoved, TSharedPtr<FFootageCaptureSource>) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") UCaptureSourceSet : public UObject { public: TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources; };`
- L115 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCaptureSourceUpdated, const TSharedPtr<FFootageCaptureSource>) PRAGMA_DISABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_TwoParams(FOnCaptureSourceFinishedImportingTakes, const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_OneParam(FOnCaptureSourceRemoved, TSharedPtr<FFootageCaptureSource>) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") UCaptureSourceSet : public UObject { public: TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources; };`
- L118 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCaptureSourceFinishedImportingTakes, const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_DELEGATE_OneParam(FOnCaptureSourceRemoved, TSharedPtr<FFootageCaptureSource>) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") UCaptureSourceSet : public UObject { public: TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources; };`
- L121 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCaptureSourceRemoved, TSharedPtr<FFootageCaptureSource>) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") UCaptureSourceSet : public UObject { public: TArray<TObjectPtr<FFootageCaptureSource>> CaptureSources; };`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/FootageIngestWidget.h` (Public)


#### class `SFootageIngestWidget`  
`SFootageIngestWidget : public SCompoundWidget`  
_L48-214_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `SCompoundWidget`
- L51 _public function_ `SLATE_BEGIN_ARGS(SFootageIngestWidget) : _OwnerTab()`
- L54 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SDockTab>, OwnerTab) SLATE_EVENT(FOnTargetFolderAssetPathChanged, OnTargetFolderAssetPathChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L63 _public prototype_ `bool UnqueueTake(TSharedPtr<FFootageTakeItem> Take, bool bCancelingSingleItem);`
- L64 _public prototype_ `void UnqueueTakes(TArray<TSharedPtr<FFootageTakeItem>> Takes);`
- L68 _public prototype_ `void OnCurrentCaptureSourceChanged(TSharedPtr<FFootageCaptureSource> InCaptureSource, ESelectInfo::Type InSelectInfo);` — called by CaptureManagerWidget after CaptureSourcesWidget has processed the event
- L71 _public prototype_ `void OnCaptureSourcesChanged(TArray<TSharedPtr<FFootageCaptureSource>> InCaptureSources);` — called by CaptureManagerWidget after CaptureSourcesWidget has processed the event
- L74 _public prototype_ `void OnCaptureSourceUpdated(TSharedPtr<FFootageCaptureSource> InCaptureSource);` — called by CaptureManagerWidget after CaptureSourcesWidget has processed the event
- L78 _public prototype_ `void OnCaptureSourceFinishedImportingTakes(const TArray<FMetaHumanTake>& InTakes, TSharedPtr<FFootageCaptureSource> InCaptureSource);` — called by CaptureManagerWidget after the CaptureSourcesWidget has processed the event
- L82 _public prototype_ `bool CanClose();` — called by CaptureManagerWidget when capture manager is closed
- L83 _public prototype_ `void OnClose();`
- L86 _public function_ `void SetAutosaveAfterImport(bool bInAutosave)` — called by CaptureManager after clicking on the check box
- L89 _public prototype_ `void SaveImportedAssets();` — called right after import if bSaveAfterIngest is on, or from clicking on CaptureManager's Save All button
- L90 _public prototype_ `void SetDefaultAssetCreationPath(const FString& InDefaultAssetCreationPath);`
- L94 _private prototype_ `void OnTakeViewSelectionChanged(TSharedPtr<FFootageTakeItem> InTakeItem, ESelectInfo::Type InSelectInfo);`
- L95 _private prototype_ `void OnQueueListSelectionChanged(TSharedPtr<FFootageTakeItem> InTakeItem, ESelectInfo::Type InSelectInfo);`
- L98 _private prototype_ `void OnTakeFilterTextCommitted(const FText& InSearchText, ETextCommit::Type InCommitType);`
- L99 _private prototype_ `void OnTakeFilterTextChanged(const FText& InSearchText);`
- L101 _private prototype_ `FText GetTakeCountText() const;`
- L103 _private prototype_ `FReply OnImportTakesClicked();`
- L104 _private prototype_ `bool IsImportTakesEnabled() const;`
- L105 _private prototype_ `FReply OnCancelAllImportClicked();`
- L106 _private prototype_ `bool IsCancelAllImportEnabled() const;`
- L107 _private prototype_ `FReply OnClearAllImportClicked();`
- L108 _private prototype_ `bool IsClearAllImportEnabled() const;`
- L110 _private prototype_ `FReply OnQueueButtonClicked();`
- L111 _private prototype_ `bool IsQueueButtonEnabled() const;`
- L112 _private prototype_ `const FSlateBrush* GetQueueButtonIcon() const;`
- L113 _private prototype_ `FText GetQueueButtonText() const;`
- L114 _private prototype_ `FText GetQueueButtonTooltip() const;`
- L115 _private prototype_ `FText GetTargetFolderPickerPathTooltip() const;`
- L117 _private prototype_ `void SubscribeToCaptureSourceEvents(TSharedPtr<FFootageCaptureSource>& CaptureSource);`
- L120 _private prototype_ `void OnGetTakeImported(struct FMetaHumanCapturePerTakeVoidResult InResult);`
- L123 _private member_ `FOnTargetFolderAssetPathChanged OnTargetFolderAssetPathChangedDelegate;`
- L127 _private member_ `static const FName CaptureSourcesTabId;`
- L128 _private member_ `static const FName FootageIngestTabId;`
- L130 _private prototype_ `bool IsCurrentCaptureSourceAssetValid() const;`
- L132 _private prototype_ `TSharedPtr<FFootageTakeItem> GetTakeItemById(FFootageCaptureSource& InCaptureSource, TakeId InTakeId);`
- L133 _private prototype_ `void UpdateTakeList(TSharedPtr<FFootageCaptureSource> InCaptureSource, const TArray<int32>& NewTakes);`
- L134 _private prototype_ `void RemoveFromTakeList(TSharedPtr<FFootageCaptureSource> InCaptureSource, const TArray<TakeId>& RemovedTakes);`
- L135 _private prototype_ `void UpdateThumbnail(FFootageCaptureSource& InCaptureSource, TakeId InTakeId);`
- L136 _private prototype_ `bool LoadThumbnail(const TArray<uint8>& InThumbnailRawData, TSharedPtr<FFootageTakeItem> InTakeItem);`
- L137 _private prototype_ `TArray<TSharedPtr<FFootageTakeItem>>& GetCurrentTakeList();`
- L138 _private prototype_ `void SetTakeViewListSource(TArray<TSharedPtr<FFootageTakeItem>>* InListSource);`
- L140 _private prototype_ `UFootageCaptureData* GetOrCreateCaptureData(const FString& InTargetIngestPath, const FString& InAssetName) const;`
- L141 _private prototype_ `UFootageCaptureData* GetCaptureData(const FString& InTargetIngestPath, const FString& InAssetName) const;`
- L142 _private prototype_ `TArray<FAssetData> GetAssetsInPath(const FString& InTargetIngestPath);`
- L144 _private prototype_ `bool CheckIfTakeShouldBeIngested(const FString& InSourceName, const TakeId InTakeId) const;`
- L145 _private prototype_ `bool PresentDialogForIngestedTakes(const TArray<TSharedPtr<FFootageTakeItem>>& InAlreadyIngestedTakes) const;`
- L147 _private prototype_ `void LoadAlreadyIngestedTakes(const TSharedPtr<FFootageCaptureSource> InCaptureSource);`
- L148 _private prototype_ `void CheckIfTakeIsAlreadyIngested(const TSharedPtr<FFootageTakeItem> InTake);`
- L151 _private prototype_ `TSharedRef<SWidget> CreatePathPicker(const FPathPickerConfig& PathPickerConfig);`
- L152 _private prototype_ `void OnTargetPathChange(const FString& NewPath);`
- L153 _private prototype_ `TSharedRef<SWidget> GetPathPickerContent();`
- L156 _private member_ `TWeakPtr<SDockTab> OwnerTab = nullptr;`
- L160 _private member_ `TSharedPtr<STileView<TSharedPtr<FFootageTakeItem>>> TakeTileView;`
- L161 _private member_ `TSharedPtr<SListView<TSharedPtr<FFootageCaptureSource>>> SourceListView;`
- L162 _private member_ `TSharedPtr<SListView<TSharedPtr<FFootageTakeItem>>> QueueListView;`
- L163 _private member_ `TSharedPtr<STreeView<TSharedPtr<FFootageFolderTreeItem>>> FolderTreeView;`
- L165 _private member_ `TSharedPtr<STextBlock> TakeStatusBarText;`
- L167 _private member_ `TSharedPtr<SEditableTextBox> TargetFolderTextBox;`
- L169 _private member_ `TSharedPtr<SExpandableArea> CaptureSourcesArea;`
- L170 _private member_ `TSharedPtr<SExpandableArea> DeviceContentsArea;`
- L172 _private member_ `TSharedPtr<SSearchBox> TakeSearchBar;`
- L174 _private member_ `TSharedPtr<SPositiveActionButton> AddToQueueButton;`
- L178 _private member_ `TArray<TSharedPtr<FFootageTakeItem>>* TakeViewListSource;`
- L179 _private member_ `TArray<TSharedPtr<FFootageTakeItem>> TakeItems_Null;`
- L180 _private member_ `TArray<TSharedPtr<FFootageTakeItem>> TakeItems_Filtered;`
- L181 _private member_ `TArray<TSharedPtr<FFootageTakeItem>> QueuedTakes;`
- L183 _private member_ `TArray<TSharedPtr<FFootageFolderTreeItem>> FolderTreeItemList;`
- L185 _private member_ `TArray<TSharedPtr<FFootageCaptureSource>> CaptureSources;`
- L186 _private member_ `TSharedPtr<FFootageCaptureSource> CurrentCaptureSource;`
- L190 _private member_ `bool bImportingTakes;`
- L192 _private member_ `FText TakeFilterText;`
- L195 _private member_ `FText TargetFolderPickerAssetPath;` — The asset path for the folder shown in the Target Folder Picker, relative to Content folder, begins with /Game/ and includes [CaptureSource]_Ingested
- L197 _private member_ `FText TargetFolderPickerFullPathOnDisk;` — The full directory path (on disk) picked in the Target Folder Picker, including the suffix to the Capture Source (_Ingested)
- L199 _private member_ `bool bSaveAfterIngest;` — set by CaptureManagerWidget on initialization and each toggle of Autosave checkbox
- L200 _private member_ `TArray<FAssetData> AssetsToSave;`
- L202 _private member_ `TMap<FString, TArray<TakeId>> IngestedTakesCache;`
- L203 _private member_ `FString DefaultAssetCreationPath;`
- L205 _private prototype_ `void AddAutoReimportExemption(UEditorLoadingSavingSettings* Settings, FString DirectoryPath);`
- L206 _private prototype_ `static FString PathOnDiskFromAssetPath(const FString& InAssetPath);`
- L207 _private prototype_ `static FString GetDefaultAssetPath(const FName& InCaptureSourcePackageName);`
- L210 _private member_ `TSharedPtr<SSimpleComboButton> PathPickerButton;`

#### Free symbols / members of external scopes

- L35 _macro_ `#define CANCEL_BUTTON_FOR_INDIVIDUAL_TASKS`
- L36 _macro_ `#define TARGET_PATH_PICKER`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTargetFolderAssetPathChanged, FText TargetFolderAssetPath) DECLARE_DELEGATE_OneParam(FOnAutosaveAfterImportChanged, bool bAutosaveAfterImport) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") SFootageIngestWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SFootageIngestWidget) : _OwnerTab() {} SLATE_ARGUMENT(TWeakPtr<SDockTab>, OwnerTab) SLATE_EVENT(FOnTargetFolderAssetPathChanged, OnTargetFolderAssetPathChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; PRAGMA_DISABLE_DEPRECATION_WARNINGS bool UnqueueTake(TSharedPtr<FFootageTakeItem> Take, bool bCancelingSingleItem); void UnqueueTakes(TArray<TSharedPtr<FFootageTakeItem>> Takes); PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAutosaveAfterImportChanged, bool bAutosaveAfterImport) class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module") SFootageIngestWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SFootageIngestWidget) : _OwnerTab() {} SLATE_ARGUMENT(TWeakPtr<SDockTab>, OwnerTab) SLATE_EVENT(FOnTargetFolderAssetPathChanged, OnTargetFolderAssetPathChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; PRAGMA_DISABLE_DEPRECATION_WARNINGS bool UnqueueTake(TSharedPtr<FFootageTakeItem> Take, bool bCancelingSingleItem); void UnqueueTakes(TArray<TSharedPtr<FFootageTakeItem>> Takes); PRAGMA_ENABLE_DEPRECATION_WARNINGS`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFootageIngest/Public/MetaHumanFootageRetrievalWindowStyle.h` (Public)


#### class `FMetaHumanFootageRetrievalWindowStyle`  
`FMetaHumanFootageRetrievalWindowStyle : public FSlateStyleSet`  
_L10-27_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanFootageIngest is deprecated. This functionality is now available in the CaptureManager module")`
- inherits: `FSlateStyleSet`
- desc: A Style set for Footage Retrieval window
- L14 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L15 _public prototype_ `static const FMetaHumanFootageRetrievalWindowStyle& Get();`
- L17 _public prototype_ `static void ReloadTextures();`
- L19 _public prototype_ `static void Register();`
- L20 _public prototype_ `static void Unregister();`
- L24 _private prototype_ `FMetaHumanFootageRetrievalWindowStyle();`
- L26 _private member_ `static FName StyleName;`
