# Plugins / IntroTutorials

- module root: `Plugins/Editor/GuidedTutorials/Source/IntroTutorials`
- headers: 25; symbols: 577
- symbol kinds: class=25, delegate=10, enum=5, enumerator=18, function=25, member=203, namespace=3, prototype=275, struct=12, typedef=1
- DynamicallyLoadedModuleNames: LauncherServices, MainFrame
- PrivateDependencyModuleNames: Analytics, AppFramework, AssetRegistry, AssetTools, ContentBrowser, DesktopPlatform, EditorFramework, GameProjectGeneration, Kismet, LevelEditor, PlacementMode, PropertyEditor, Settings, SlateCore, SourceCodeAccess, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: LauncherServices, MainFrame, TargetDeviceServices, TargetPlatform
- PublicDependencyModuleNames: ApplicationCore, BlueprintGraph, Core, CoreUObject, Documentation, Engine, GraphEditor, InputCore, MessageLog, Slate, SlateCore

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/ClassTypeActions_EditorTutorial.h` (Private)


#### class `FClassTypeActions_EditorTutorial`  
`class FClassTypeActions_EditorTutorial : public FClassTypeActions_Base`  
_L11-17_
- inherits: `FClassTypeActions_Base`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;` — IClassTypeActions Implementation
- L16 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialDetailsCustomization.h` (Private)


#### class `FEditorTutorialDetailsCustomization`  
`class FEditorTutorialDetailsCustomization : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialFactory.h` (Private)


#### class `UEditorTutorialFactory`  
`class UEditorTutorialFactory : public UFactory`  
_L11-20_
- reflection: `UCLASS(hidecategories=Object, collapsecategories)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L17 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L18 _private prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialImportFactory.h` (Private)


#### class `UEditorTutorialImportFactory`  
`class UEditorTutorialImportFactory : public UFactory, public FReimportHandler`  
_L14-33_
- reflection: `UCLASS(hidecategories=Object, collapsecategories)`
- inherits: `UFactory,FReimportHandler`
- L19 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L20 _private prototype_ `virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;`
- L24 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L25 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L26 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L27 _private prototype_ `virtual int32 GetPriority() const override;`
- L32 _private prototype_ `bool Import(UEditorTutorial* InTutorialToImportTo, const FString& InImportPath);` — Import the tutorial from file

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialSettings.h` (Private)


#### struct `FTutorialContext`  
`struct FTutorialContext`  
_L14-33_
- reflection: `USTRUCT()`
- desc: Named context that corresponds to a particular tutorial
- L20 _public member_ `FName Context;` — `UPROPERTY(EditAnywhere, Category = "Tutorials")` — The context that this tutorial is used in
- L24 _public member_ `FString BrowserFilter;` — `UPROPERTY(EditAnywhere, Category = "Tutorials")` — The filter string to apply to the tutorials browser when launched from this context
- L28 _public member_ `FSoftClassPath AttractTutorial;` — `UPROPERTY(EditAnywhere, Category = "Tutorials", meta = (MetaClass = "/Script/IntroTutorials.EditorTutorial"))` — The tutorial to use in this context to let the user know there is a tutorial available
- L32 _public member_ `FSoftClassPath LaunchTutorial;` — `UPROPERTY(EditAnywhere, Category = "Tutorials", meta = (MetaClass = "/Script/IntroTutorials.EditorTutorial"))` — The tutorial to use in this context when the user chooses to launch

#### class `UEditorTutorialSettings`  
`class UEditorTutorialSettings : public UObject`  
_L37-59_
- reflection: `UCLASS(config=GuidedTutorials)`
- inherits: `UObject`
- desc: Editor-wide tutorial settings
- L43 _private member_ `bool bDisableAllTutorialAlerts;` — `UPROPERTY(Config, EditAnywhere, Category = "Tutorials")` — Disable the pulsing alert that indicates a new tutorial is available.
- L47 _private member_ `TArray<FTutorialCategory> Categories;` — `UPROPERTY(Config, EditAnywhere, Category="Tutorials")` — Categories for tutorials
- L51 _private member_ `FSoftClassPath StartupTutorial;` — `UPROPERTY(Config, EditAnywhere, Category="Tutorials", meta=(MetaClass="/Script/IntroTutorials.EditorTutorial"))` — Tutorial to start on Editor startup
- L55 _private member_ `TArray<FTutorialContext> TutorialContexts;` — `UPROPERTY(Config, EditAnywhere, Category = "Tutorials")` — Tutorials used in various contexts - e.g. the various asset editors
- L58 _private prototype_ `void FindTutorialInfoForContext(FName InContext, UEditorTutorial*& OutAttractTutorial, UEditorTutorial*& OutLaunchTutorial, FString& OutBrowserFilter) const;` — Get the tutorial info for the specified context

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialStyle.h` (Private)


#### class `FEditorTutorialStyle`  
`class FEditorTutorialStyle : public FSlateStyleSet`  
_L8-24_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FEditorTutorialStyle& Get();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `~FEditorTutorialStyle();`
- L20 _private prototype_ `FEditorTutorialStyle();`
- L22 _private member_ `static FName StyleName;`
- L23 _private member_ `static TUniquePtr<FEditorTutorialStyle> Instance;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/IntroTutorials.h` (Private)


#### class `FIntroTutorials`  
`class FIntroTutorials : public IIntroTutorials`  
_L32-167_
- inherits: `IIntroTutorials`
- L36 _public prototype_ `FIntroTutorials();` — ctor
- L39 _public prototype_ `FOnIsPicking& OnIsPicking();` — Get the delegate used to check for whether we are picking widgets
- L42 _public prototype_ `FOnValidatePickingCandidate& OnValidatePickingCandidate();` — Get the delegate used to validate the given widget for pickings
- L44 _public prototype_ `void GoToPreviousStage();`
- L46 _public prototype_ `void GoToNextStage(TWeakPtr<SWindow> InNavigationWindow);`
- L48 _public prototype_ `float GetIntroCurveValue(float InTime);`
- L50 _public prototype_ `void SummonTutorialBrowser();`
- L52 _public prototype_ `void DismissTutorialBrowser();`
- L54 _public prototype_ `void AttachWidget(TSharedPtr<SWidget> Widget);`
- L56 _public prototype_ `void DetachWidget();`
- L58 _public prototype_ `static FString AnalyticsEventNameFromTutorial(UEditorTutorial* Tutorial);`
- L63 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L64 _private prototype_ `virtual void ShutdownModule() override;`
- L67 _private prototype_ `void RegisterSummonTutorialsMenuEntries();` — Register the menu for summoning the tutorial
- L70 _private prototype_ `TSharedRef<FExtender> AddSummonBlueprintTutorialsMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> EditingObjects) const;` — Add a menu extender to summon context-sensitive Blueprints page
- L73 _private prototype_ `void AddSummonBlueprintTutorialsMenuExtension(FMenuBuilder& MenuBuilder, UObject* PrimaryObject);` — Add a menu entry to summon context-sensitive Blueprints page
- L76 _private prototype_ `void MainFrameLoad(TSharedPtr<SWindow> InRootWindow, bool bIsRunningStartupDialog);` — Event to be called when the main frame is loaded
- L79 _private prototype_ `void SummonTutorialHome();` — Summon tutorial home page to front
- L82 _private prototype_ `void SummonBlueprintTutorialHome(UObject* Asset, bool bForceWelcome);` — Summon blueprint tutorial home page to front
- L85 _private prototype_ `void OnTutorialWindowClosed(const TSharedRef<SWindow>& Window);` — Event to be called when Tutorial window is closed.
- L88 _private prototype_ `void OnTutorialDismissed() const;` — Called when tutorial is dismissed, either when finished or aborted.
- L91 _private prototype_ `void OnAssetEditorOpened(UObject* Asset);` — Event to be called when any asset editor is opened
- L94 _private prototype_ `void OnAddCodeToProjectDialogOpened();` — Events to call when editor changes state in various ways
- L95 _private prototype_ `void OnNewProjectDialogOpened();`
- L98 _private prototype_ `void HandleCompilerNotFound();` — Events to call when opening the compiler fails
- L101 _private prototype_ `void HandleSDKNotInstalled(const FString& PlatformName, const FString& InTutorialAsset);` — Events to call when SDK isn't installed
- L104 _private prototype_ `void HandleRequestResource(const FString& Category, const FString& InTutorialName);` — Handles calls to MainFrameRequestResource that specify a tutorial asset and "Tutorial" category.
- L106 _private prototype_ `bool MaybeOpenWelcomeTutorial();`
- L107 _private prototype_ `void ResetWelcomeTutorials() const;`
- L110 _private prototype_ `EVisibility GetHomeButtonVisibility() const;` — Delegate for home button visibility
- L113 _private prototype_ `void LaunchTutorialByName(const FString& InAssetPath, bool bRestart = true, TWeakPtr<SWindow> InNavigationWindow = nullptr, FSimpleDelegate OnTutorialClosed = FSimpleDelegate(), FSimpleDelegate OnTutorialExited = FSimpleDelegate());` — Internal helper to launch a tutorial from a path
- L116 _private prototype_ `TSharedRef<SDockTab> SpawnTutorialsBrowserTab(const FSpawnTabArgs& SpawnTabArgs);` — Spawn a tab for browsing tutorials
- L119 _private member_ `TWeakPtr<SDockTab> TutorialBrowserDockTab;` — When we create a tutorial browser tab, we only keep a weak pointer to it. This way, it can be closed/destroyed without our involvement, but we can also close/destroy it ourselves.
- L124 _public prototype_ `virtual void LaunchTutorial(const FString& TutorialAssetName, TSharedPtr<SWindow> InNavigationWindow = nullptr) override;` — IIntroTutorials interface
- L125 _public prototype_ `virtual void LaunchTutorial(UEditorTutorial* Tutorial, IIntroTutorials::ETutorialStartType InStartType = IIntroTutorials::ETutorialStartType::TST_RESTART, TWeakPtr<SWindow> InNavigationWindow = nullptr, FSimpleDelegate OnTutorialClosed = FSimpleDelegate(), FSimpleDelegate OnTutorialExited = FSimpleDelegate()) override;`
- L126 _public prototype_ `virtual void CloseAllTutorialContent() override;`
- L127 _public prototype_ `virtual TSharedRef<SWidget> CreateTutorialsWidget(FName InContext, TWeakPtr<SWindow> InContextWindow = nullptr) const override;`
- L128 _public prototype_ `virtual TSharedPtr<SWidget> CreateTutorialsLoadingWidget(TWeakPtr<SWindow> InContextWindow = nullptr) const override;`
- L129 _public prototype_ `virtual void RegisterCategory(FTutorialCategory NewCategory) override;`
- L133 _private member_ `static const FName IntroTutorialTabName;` — The tab id of the tutorial tab
- L136 _private member_ `TSharedPtr<FExtender> MainMenuExtender;` — The extender to pass to the level editor to extend it's window menu
- L139 _private member_ `TSharedPtr<FExtender> BlueprintEditorExtender;` — The extender to pass to the blueprint editor to extend it's window menu
- L142 _private member_ `bool bDisableTutorials;` — Whether tutorials are disabled altogether
- L145 _private member_ `UClass* CurrentObjectClass;` — The current object we are using as a basis for displaying a tutorial
- L148 _private member_ `bool bDesireResettingTutorialSeenFlagOnLoad;` — should we be clearing the 'have seen this tutorial' flag? (controlled by -tutorials on the command line)
- L151 _private member_ `FOnIsPicking OnIsPickingDelegate;` — Delegate used to determine whether we are in picking mode
- L154 _private member_ `FOnValidatePickingCandidate OnValidatePickingCandidateDelegate;` — Delegate used to determine if we are in picking mode, get the name of any picked widget and check if it matches the 'pickable' name of the given widget
- L157 _private member_ `TSharedPtr<STutorialRoot> TutorialRoot;` — Root widget for tutorial overlay system
- L160 _private member_ `TWeakObjectPtr<UCurveFloat> ContentIntroCurve;` — Curve asset for intros
- L163 _private member_ `TArray<TSharedRef<IClassTypeActions>> RegisteredClassTypeActions;` — The collection of registered class type actions.
- L166 _private member_ `TArray<FTutorialCategory> ExternalCategories;` — Extra tutorial categories that have been defined externally

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsPicking, FName& );` — Query delegate to see if we are in picking mode
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsPicking, FName& );` — Query delegate to see if we are in picking mode
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnValidatePickingCandidate, TSharedRef<SWidget> , FName& , bool& );` — Query delegate for name of any picked widget and check if it matches the 'pickable' name of the given widget
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnValidatePickingCandidate, TSharedRef<SWidget> , FName& , bool& );` — Query delegate for name of any picked widget and check if it matches the 'pickable' name of the given widget

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/SEditorTutorials.h` (Private)


#### class `SEditorTutorials`  
`class SEditorTutorials : public SCompoundWidget`  
_L27-136_
- inherits: `SCompoundWidget`
- desc: Container widget for all tutorial-related widgets
- L29 _private function_ `SLATE_BEGIN_ARGS( SEditorTutorials )`
- L34 _private prototype_ `SLATE_EVENT(FSimpleDelegate, OnCloseClicked) SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_EVENT(FOnNextClicked, OnNextClicked) SLATE_EVENT(FSimpleDelegate, OnBackClicked) SLATE_EVENT(FSimpleDelegate, OnHomeClicked) SLATE_EVENT(FOnGetCurrentTutorial, OnGetCurrentTutorial) SLATE_EVENT(FOnGetCurrentTutorialStage, OnGetCurrentTutorialStage) SLATE_EVENT(FOnLaunchTutorial, OnLaunchTutorial) SLATE_EVENT(FOnWidgetWasDrawn, OnWidgetWasDrawn) SLATE_EVENT(FOnWasWidgetDrawn, OnWasWidgetDrawn) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L50 _private prototype_ `void LaunchTutorial(bool bInIsNavigationWindow, FSimpleDelegate InOnTutorialClosed, FSimpleDelegate InOnTutorialExited);` — Launch a tutorial - will interrogate parent to get the tutorial data to display
- L53 _private prototype_ `void HideContent();` — hide the tutorials browser in this window
- L56 _private prototype_ `TSharedPtr<SWindow> GetParentWindow() const;` — Get parent window for this widget
- L59 _private prototype_ `void RebuildCurrentContent();` — Rebuild content according to the current tutorial state
- L62 _private prototype_ `bool IsNavigationVisible() const;` — @return whether the navigation controls are currently visible
- L66 _private prototype_ `EVisibility GetBrowserVisibility() const;` — Handle whether we should display the browser
- L69 _private prototype_ `EVisibility GetNavigationVisibility() const;` — Handle whether we should display the navigation buttons
- L72 _private prototype_ `void HandleCloseClicked();` — Handle hitting the close button on the browser or a standalone widget
- L75 _private prototype_ `void HandleHomeClicked();` — Handle hitting the home button in the navigation window
- L78 _private prototype_ `void HandleBackClicked();` — Handle hitting the back button in the navigation window
- L81 _private prototype_ `void HandleNextClicked();` — Handle hitting the next button in the navigation window
- L84 _private prototype_ `bool IsBackButtonEnabled() const;` — Get enabled state of the back button
- L87 _private prototype_ `bool IsHomeButtonEnabled() const;` — Get enabled state of the home button
- L90 _private prototype_ `bool IsNextButtonEnabled() const;` — Get enabled state of the next button
- L93 _private prototype_ `float GetProgress() const;` — Get the current progress to display in the progress bar
- L97 _private member_ `TSharedPtr<SHorizontalBox> ContentBox;` — Box that contains varied content for current tutorial
- L100 _private member_ `TSharedPtr<STutorialOverlay> OverlayContent;` — Content widget for current tutorial
- L103 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Window that contains this widget
- L106 _private member_ `bool bBrowserVisible;` — Whether the browser is visible
- L109 _private member_ `bool bIsNavigationWindow;` — Whether we should display navigation
- L112 _private member_ `FOnNextClicked OnNextClicked;` — Delegate fired when next button is clicked
- L115 _private member_ `FSimpleDelegate OnBackClicked;` — Delegate fired when back button is clicked
- L118 _private member_ `FSimpleDelegate OnHomeClicked;` — Delegate fired when home button is clicked
- L121 _private member_ `FSimpleDelegate OnCloseClicked;` — Delegate fired when close button is clicked
- L124 _private member_ `FOnGetCurrentTutorial OnGetCurrentTutorial;` — Delegate fired to retrive the current tutorial
- L127 _private member_ `FOnGetCurrentTutorialStage OnGetCurrentTutorialStage;` — Delegate fired to retrive the current tutorial stage
- L130 _private member_ `FSimpleDelegate OnTutorialClosed;` — External delegates used to report user interaction
- L131 _private member_ `FSimpleDelegate OnTutorialExited;`
- L134 _private member_ `FOnWidgetWasDrawn OnWidgetWasDrawn;` — Delegates for registering & querying whether a widget was drawn
- L135 _private member_ `FOnWasWidgetDrawn OnWasWidgetDrawn;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNextClicked, TWeakPtr<SWindow> );` — Delegate fired when next button is clicked
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNextClicked, TWeakPtr<SWindow> );` — Delegate fired when next button is clicked
- L19 _delegate_ `DECLARE_DELEGATE_RetVal(UEditorTutorial*, FOnGetCurrentTutorial);` — Delegate fired to retrieve current tutorial
- L19 _prototype_ `DECLARE_DELEGATE_RetVal(UEditorTutorial*, FOnGetCurrentTutorial);` — Delegate fired to retrieve current tutorial
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FOnGetCurrentTutorialStage);` — Delegate fired to retrieve current tutorial stage
- L22 _prototype_ `DECLARE_DELEGATE_RetVal(int32, FOnGetCurrentTutorialStage);` — Delegate fired to retrieve current tutorial stage

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialButton.h` (Private)


#### class `STutorialButton`  
`class STutorialButton : public SCompoundWidget`  
_L16-111_
- inherits: `SCompoundWidget`
- L18 _private function_ `SLATE_BEGIN_ARGS(STutorialButton)`
- L20 _private prototype_ `SLATE_ARGUMENT(FName, Context) SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L29 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L30 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _private prototype_ `EActiveTimerReturnType OpenTutorialPostConstruct( double InCurrentTime, float InDeltaTime );` — Opens the tutorial post-construct
- L37 _private prototype_ `FReply HandleButtonClicked();` — Handle clicking the tutorial button
- L40 _private prototype_ `EActiveTimerReturnType HandleButtonClicked_AssetRegistryChecker(double InCurrentTime, float InDeltaTime);` — After the initial click is processed, go here, wait for the asset registry to load, and complete the action once we're ready
- L43 _private prototype_ `void DismissAlert();` — Dismiss the pulsing alert
- L46 _private prototype_ `void DismissAllAlerts();` — Dismiss all pulsing alerts
- L49 _private prototype_ `void LaunchBrowser();` — Launch the tutorials browser
- L52 _private prototype_ `bool ShouldLaunchBrowser() const;` — Check whether we should launch the browser in this context
- L55 _private prototype_ `bool ShouldShowAlert() const;` — Check whether we should show the alert in this context
- L58 _private prototype_ `FText GetButtonToolTip() const;` — Get the tooltip for the tutorials button
- L61 _private prototype_ `void LaunchTutorial();` — Launch tutorial from the context menu
- L64 _private prototype_ `void RefreshStatus();` — Refresh internal status of flags, tutorials, filters etc.
- L67 _private prototype_ `void HandleTutorialExited();` — Handle tutorial exiting/finishing
- L72 _private member_ `bool bTutorialAvailable;` — Whether we have a tutorial for this context
- L75 _private member_ `bool bTutorialCompleted;` — Whether we have completed the tutorial for this content
- L78 _private member_ `bool bTutorialDismissed;` — Whether we have dismissed the tutorial for this content
- L81 _private member_ `bool bTestAlerts;` — Flag to force alerts to appear in internal builds (caches command line -TestTutorialAlerts)
- L84 _private member_ `FName Context;` — Context that this widget was created for (i.e. what part of the editor)
- L87 _private member_ `TWeakPtr<SWindow> ContextWindow;` — Window that the tutorial should be launched in
- L90 _private member_ `FCurveSequence PulseAnimation;` — Animation curve for displaying pulse
- L93 _private member_ `float AlertStartTime;` — Start time we began playing the alert animation
- L96 _private member_ `FText TutorialTitle;` — The name of the tutorial we will launch
- L99 _private member_ `UEditorTutorial* CachedAttractTutorial;` — Cached attract tutorial
- L102 _private member_ `UEditorTutorial* CachedLaunchTutorial;` — Cached launch tutorial
- L105 _private member_ `FString CachedBrowserFilter;` — Cached browser filter
- L107 _private member_ `TSharedPtr<SWidget> LoadingWidget;`
- L110 _private member_ `bool bPendingClickAction;` — True if we're waiting for asset registry to load in response to a click

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialContent.h` (Private)


#### class `STutorialContent`  
`class STutorialContent : public SCompoundWidget`  
_L26-273_
- inherits: `SCompoundWidget`
- desc: The widget which displays 'floating' content
- L28 _private function_ `SLATE_BEGIN_ARGS( STutorialContent )`
- L35 _private prototype_ `SLATE_ATTRIBUTE(EVerticalAlignment, VAlign) SLATE_ATTRIBUTE(EHorizontalAlignment, HAlign) SLATE_ATTRIBUTE(FVector2D, Offset) SLATE_ARGUMENT(bool, IsStandalone) SLATE_EVENT(FSimpleDelegate, OnClosed) SLATE_EVENT(FSimpleDelegate, OnBackClicked) SLATE_EVENT(FSimpleDelegate, OnHomeClicked) SLATE_EVENT(FSimpleDelegate, OnNextClicked) SLATE_ATTRIBUTE(bool, IsBackEnabled) SLATE_ATTRIBUTE(bool, IsHomeEnabled) SLATE_ATTRIBUTE(bool, IsNextEnabled) SLATE_ARGUMENT(float, WrapTextAt) SLATE_ARGUMENT(FTutorialContentAnchor, Anchor) SLATE_ARGUMENT(bool, AllowNonWidgetContent)` — Alignment of content relative to widget, note "Fill" is not supported
- L90 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget implementation
- L91 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L93 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L96 _private prototype_ `static TSharedRef<SWidget> GenerateContentWidget(const FTutorialContent& InContent, TSharedPtr<IDocumentationPage>& OutDocumentationPage, const TAttribute<FText>& InHighlightText = TAttribute<FText>(), bool bAutoWrapText = true, float WrapTextAt = 0.0f);` — Helper function to generate widgets from an FTutorialContent struct
- L99 _private prototype_ `FVector2D GetPosition() const;` — Handle repositioning the widget
- L102 _private prototype_ `FVector2D GetSize() const;` — Handle resizing the widget
- L105 _private prototype_ `void HandlePaintNamedWidget(TSharedRef<SWidget> InWidget, const FGeometry& InGeometry);` — Delegate handler called back from the overlay paint routines to flag whether we should paint as well (i.e. if this widget content is highlighted for the current stage)
- L108 _private prototype_ `void HandleResetNamedWidget();` — Called back from the overlay paint routines to reset the flag we check for painting with
- L111 _private prototype_ `void HandleCacheWindowSize(const FVector2D& InWindowSize);` — Handle caching window size - called back from overlay paint routine
- L116 _private prototype_ `EVisibility GetVisibility() const;` — Get the visibility of this content
- L119 _private prototype_ `FReply OnCloseButtonClicked();` — Handle close button clicked - forward to delegate
- L122 _private prototype_ `EVisibility GetCloseButtonVisibility() const;` — Get close button visibility - varies depending on whether we are standalone or not
- L125 _private prototype_ `EVisibility GetMenuButtonVisibility() const;` — Get menu button visibility - varies depending on whether we are standalone or not
- L128 _private prototype_ `FSlateColor GetBackgroundColor() const;` — Alter the background color depending on hover state
- L131 _private prototype_ `float GetAnimatedZoom() const;` — Get zoom level padding for content (animated for intro)
- L134 _private prototype_ `float GetInverseAnimatedZoom() const;` — Get inverse zoom level padding for content - needed because rich text content doesnt scale well
- L137 _private prototype_ `TSharedRef<SWidget> HandleGetMenuContent();` — Get the content for the navigation menu
- L140 _private prototype_ `void HandleExitSelected();` — Delegate handler for exiting the tutorial
- L143 _private prototype_ `void HandleBackSelected();` — Delegate handler for going to the previous stage of the tutorial (From dropdown menu)
- L146 _private prototype_ `void HandleNextSelected();` — Delegate handler for going to the next stage of the tutorial (From dropdown menu)
- L149 _private prototype_ `void HandleRestartSelected();` — Delegate handler for restarting the tutorial
- L152 _private prototype_ `void HandleBrowseSelected();` — Delegate handler for exiting the tutorial to the browser
- L155 _private prototype_ `FReply HandleNextClicked();` — Delegate handler for going to the next stage of the tutorial (From button)
- L158 _private prototype_ `FReply HandleBackButtonClicked();` — Delegate handler for going to the previous stage of the tutorial (From button)
- L161 _private prototype_ `const FSlateBrush* GetNextButtonBrush() const;` — Delegate handler allowing us to change the brush of the 'next' button depending on context
- L164 _private prototype_ `FText GetNextButtonTooltip() const;` — Delegate handler allowing us to change the tootlip of the 'next' button depending on context
- L167 _private prototype_ `FText GetNextButtonLabel() const;` — Change next button color based on hover state
- L170 _private prototype_ `const FSlateBrush* GetNextButtonBorder() const;` — We need to override the border ourselves, rather than let the button handle it, as we are using a larger apparent hitbox
- L173 _private prototype_ `void GetAnimationValues(float& OutAlphaFactor, float& OutPulseFactor, FLinearColor& OutShadowTint, FLinearColor& OutBorderTint) const;` — Helper to determine the proper animation values for the border pulse
- L176 _private prototype_ `const FSlateBrush* GetBackButtonBrush() const;` — Delegate handler allowing us to change the brush of the 'back' button depending on context
- L179 _private prototype_ `FText GetBackButtonTooltip() const;` — Delegate handler allowing us to change the tootlip of the 'back' button depending on context
- L182 _private prototype_ `FText GetBackButtonLabel() const;` — Change back button color based on hover state
- L185 _private prototype_ `const FSlateBrush* GetBackButtonBorder() const;` — We need to override the border ourselves, rather than let the button handle it, as we are using a larger apparent hitbox
- L188 _private prototype_ `EVisibility GetBackButtonVisibility() const;` — Get the visibilty of the back button
- L193 _private member_ `FVector2D CachedWindowSize;` — Copy of the window size we were last draw at
- L196 _private member_ `FGeometry CachedGeometry;` — Copy of the geometry our widget was last drawn with
- L199 _private member_ `mutable FGeometry CachedContentGeometry;` — Copy of the geometry our content was last drawn with
- L202 _private member_ `TSharedPtr<SWidget> ContentWidget;` — Container for widget content
- L205 _private member_ `TAttribute<EVerticalAlignment> VerticalAlignment;` — Alignment of content relative to widget, note "Fill" is not supported
- L208 _private member_ `TAttribute<EHorizontalAlignment> HorizontalAlignment;` — Alignment of content relative to widget, note "Fill" is not supported
- L211 _private member_ `TAttribute<FVector2D> WidgetOffset;` — Offset form the widget we annotate
- L214 _private member_ `FTutorialContentAnchor Anchor;` — Copy of the anchor for this tutorial content
- L217 _private member_ `bool bIsStandalone;` — Whether this a standalone widget (with its own close button) or part of a group of other widgets, paired with tutorial navigation
- L220 _private member_ `bool bIsVisible;` — Whether this overlay is currently visible
- L223 _private member_ `FSimpleDelegate OnClosed;` — Delegate fired when the close button is clicked
- L226 _private member_ `FSimpleDelegate OnNextClicked;` — Delegate fired when the next button is clicked
- L229 _private member_ `FSimpleDelegate OnHomeClicked;` — Delegate fired when the home button is clicked
- L232 _private member_ `FSimpleDelegate OnBackClicked;` — Delegate fired when the back button is clicked
- L235 _private member_ `TAttribute<bool> IsBackEnabled;` — Attribute controlling enabled state of back functionality
- L238 _private member_ `TAttribute<bool> IsHomeEnabled;` — Attribute controlling enabled state of home functionality
- L241 _private member_ `TAttribute<bool> IsNextEnabled;` — Attribute controlling enabled state of next functionality
- L244 _private member_ `FCurveSequence BorderPulseAnimation;` — Animation curves for displaying border
- L245 _private member_ `FCurveSequence BorderIntroAnimation;`
- L248 _private member_ `FCurveSequence ContentIntroAnimation;` — Animation curve for displaying content
- L251 _private member_ `TSharedPtr<IDocumentationPage> DocumentationPage;` — Documentation page reference to use if we are displaying a UDN doc - we need this otherwise the page will be freed
- L254 _private member_ `TWeakObjectPtr<UEditorTutorial> Tutorial;` — The tutorial we are referencing
- L257 _private member_ `TSharedPtr<SWidget> NextButton;` — Next button widget
- L260 _private member_ `TSharedPtr<SWidget> BackButton;` — Back button widget
- L263 _private member_ `bool bAllowNonWidgetContent;` — Whether we can show full window content in this overlay (i.e. in the same window as the navigation controls)
- L266 _private member_ `FOnWasWidgetDrawn OnWasWidgetDrawn;` — Delegate for querying whether a widget was drawn
- L269 _private member_ `TAttribute<FText> NextButtonText;` — Text for next/home button
- L272 _private member_ `TAttribute<FText> BackButtonText;` — Text for next/home button

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialEditableText.h` (Private)


#### class `STutorialEditableText`  
`class STutorialEditableText : public SCompoundWidget`  
_L20-118_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS( STutorialEditableText )`
- L25 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ARGUMENT(FOnTextCommitted, OnTextCommitted) SLATE_ARGUMENT(FOnTextChanged, OnTextChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L44 _protected prototype_ `TSharedPtr<const IRun> GetCurrentRun() const;`
- L46 _protected prototype_ `void HandleRichEditableTextChanged(const FText& Text);`
- L48 _protected prototype_ `void HandleRichEditableTextCommitted(const FText& Text, ETextCommit::Type Type);`
- L50 _protected prototype_ `void HandleRichEditableTextCursorMoved(const FTextLocation& NewCursorPosition );`
- L52 _protected prototype_ `FText GetActiveStyleName() const;`
- L54 _protected prototype_ `void OnActiveStyleChanged(TSharedPtr<struct FTextStyleAndName> NewValue, ESelectInfo::Type);`
- L56 _protected prototype_ `TSharedRef<SWidget> GenerateStyleComboEntry(TSharedPtr<struct FTextStyleAndName> SourceEntry);`
- L58 _protected prototype_ `void StyleSelectedText();`
- L60 _protected prototype_ `void HandleHyperlinkComboOpened();`
- L62 _protected prototype_ `bool IsHyperlinkComboEnabled() const;`
- L64 _protected prototype_ `FReply HandleInsertHyperLinkClicked();`
- L66 _protected prototype_ `EVisibility GetToolbarVisibility() const;`
- L68 _protected prototype_ `FText GetHyperlinkButtonText() const;`
- L70 _protected prototype_ `void OnActiveHyperlinkChanged(TSharedPtr<struct FHyperlinkTypeDesc> NewValue, ESelectInfo::Type SelectionType);`
- L72 _protected prototype_ `TSharedRef<SWidget> GenerateHyperlinkComboEntry(TSharedPtr<struct FHyperlinkTypeDesc> SourceEntry);`
- L74 _protected prototype_ `FText GetActiveHyperlinkName() const;`
- L76 _protected prototype_ `FText GetActiveHyperlinkTooltip() const;`
- L78 _protected prototype_ `TSharedPtr<FHyperlinkTypeDesc> GetHyperlinkTypeFromId(const FString& InId) const;`
- L80 _protected prototype_ `EVisibility GetOpenAssetVisibility() const;`
- L82 _protected prototype_ `void HandleOpenAssetCheckStateChanged(ECheckBoxState InCheckState);`
- L84 _protected prototype_ `ECheckBoxState IsOpenAssetChecked() const;`
- L86 _protected prototype_ `EVisibility GetExcerptVisibility() const;`
- L88 _protected prototype_ `FReply HandleImageButtonClicked();`
- L91 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> RichEditableTextBox;`
- L93 _protected member_ `FSlateHyperlinkRun::FOnClick OnBrowserLinkClicked;`
- L94 _protected member_ `FSlateHyperlinkRun::FOnClick OnDocLinkClicked;`
- L95 _protected member_ `FSlateHyperlinkRun::FOnClick OnTutorialLinkClicked;`
- L96 _protected member_ `FSlateHyperlinkRun::FOnClick OnCodeLinkClicked;`
- L97 _protected member_ `FSlateHyperlinkRun::FOnClick OnAssetLinkClicked;`
- L99 _protected member_ `TSharedPtr<SComboButton> HyperlinkComboButton;`
- L100 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<struct FTextStyleAndName>>> FontComboBox;`
- L101 _protected member_ `TSharedPtr<STextBlock> HyperlinkNameTextBlock;`
- L102 _protected member_ `TSharedPtr<SEditableTextBox> HyperlinkURLTextBox;`
- L103 _protected member_ `TSharedPtr<SEditableTextBox> UDNExcerptTextBox;`
- L105 _protected member_ `TSharedPtr<struct FTextStyleAndName> ActiveStyle;`
- L106 _protected member_ `TSharedPtr<struct FTextStyleAndName> HyperlinkStyle;`
- L108 _protected member_ `TArray<TSharedPtr<struct FTextStyleAndName>> StylesAndNames;`
- L110 _protected member_ `FOnTextCommitted OnTextCommitted;`
- L111 _protected member_ `FOnTextChanged OnTextChanged;`
- L113 _protected member_ `TSharedPtr<struct FHyperlinkTypeDesc> CurrentHyperlinkType;`
- L115 _protected member_ `bool bOpenAsset;`
- L117 _protected member_ `bool bNewHyperlink;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialLoading.h` (Private)


#### class `STutorialLoading`  
`class STutorialLoading : public SCompoundWidget`  
_L11-27_
- inherits: `SCompoundWidget`
- L13 _private function_ `SLATE_BEGIN_ARGS(STutorialLoading)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);` — Widget constructor
- L26 _private member_ `TWeakPtr<SWindow> ContextWindow;` — Window where loading visual will be displayed

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialNavigation.h` (Private)


#### class `STutorialNavigation`  
`class STutorialNavigation : public SCompoundWidget`  
_L17-65_
- inherits: `SCompoundWidget`
- desc: The widget which displays floating navigation controls
- L19 _private function_ `SLATE_BEGIN_ARGS(STutorialNavigation)`
- L21 _private prototype_ `SLATE_ARGUMENT(FSimpleDelegate, OnBackClicked) SLATE_ARGUMENT(FSimpleDelegate, OnHomeClicked) SLATE_ARGUMENT(FSimpleDelegate, OnNextClicked) SLATE_ATTRIBUTE(bool, IsBackEnabled) SLATE_ATTRIBUTE(bool, IsHomeEnabled) SLATE_ATTRIBUTE(bool, IsNextEnabled) SLATE_ATTRIBUTE(float, OnGetProgress) SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _protected prototype_ `FReply OnBackButtonClicked();` — Handle back button being clicked
- L39 _protected prototype_ `FSlateColor GetBackButtonColor() const;` — Handle back button color - used to dim the button when disabled
- L42 _protected prototype_ `FReply OnHomeButtonClicked();` — Handle home button being clicked
- L45 _protected prototype_ `FSlateColor GetHomeButtonColor() const;` — Handle home button color - used to dim the button when disabled
- L48 _protected prototype_ `FReply OnNextButtonClicked();` — Handle next button being clicked
- L51 _protected prototype_ `FSlateColor GetNextButtonColor() const;` — Handle next button color - used to dim the button when disabled
- L54 _protected prototype_ `TOptional<float> GetPercentComplete() const;` — Handle display of the progress bar
- L58 _private member_ `FSimpleDelegate OnBackClicked;`
- L59 _private member_ `FSimpleDelegate OnHomeClicked;`
- L60 _private member_ `FSimpleDelegate OnNextClicked;`
- L61 _private member_ `TAttribute<bool> IsBackEnabled;`
- L62 _private member_ `TAttribute<bool> IsHomeEnabled;`
- L63 _private member_ `TAttribute<bool> IsNextEnabled;`
- L64 _private member_ `TAttribute<float> OnGetProgress;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialOverlay.h` (Private)


#### class `STutorialOverlay`  
`class STutorialOverlay : public SCompoundWidget`  
_L32-110_
- inherits: `SCompoundWidget`
- desc: The widget which displays multiple 'floating' pieces of content overlaid onto the editor
- L35 _public function_ `SLATE_BEGIN_ARGS( STutorialOverlay )`
- L41 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(bool, IsStandalone) SLATE_EVENT(FSimpleDelegate, OnClosed) SLATE_EVENT(FSimpleDelegate, OnBackClicked) SLATE_EVENT(FSimpleDelegate, OnHomeClicked) SLATE_EVENT(FSimpleDelegate, OnNextClicked) SLATE_ATTRIBUTE(bool, IsBackEnabled) SLATE_ATTRIBUTE(bool, IsHomeEnabled) SLATE_ATTRIBUTE(bool, IsNextEnabled) SLATE_ARGUMENT(bool, AllowNonWidgetContent) SLATE_EVENT(FOnWidgetWasDrawn, OnWidgetWasDrawn) SLATE_EVENT(FOnWasWidgetDrawn, OnWasWidgetDrawn) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEditorTutorial* InTutorial, FTutorialStage* const InStage);` — The window this content is displayed over
- L68 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget implementation
- L72 _private prototype_ `int32 TraverseWidgets(TSharedRef<SWidget> InWidget, const FGeometry& InGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;` — Recursive function used to re-generate widget geometry and forward the geometry of named widgets onto their respective content
- L75 _private prototype_ `void OpenBrowserForWidgetAnchor(UEditorTutorial* InTutorial, const FTutorialWidgetContent &WidgetContent);` — Opens the browser that the given widget requires if it is not already.
- L78 _private prototype_ `void FocusOnAnyBlueprintNodes(const FTutorialWidgetContent &WidgetContent);` — Focus on the blueprint node if an anchor widget references one
- L81 _private prototype_ `void PerformWidgetInteractions(UEditorTutorial* InTutorial, const FTutorialWidgetContent &WidgetContent);` — Do any interaction stuff for a widget - open browser, scroll to node etc
- L85 _private member_ `TSharedPtr<SCanvas> OverlayCanvas;` — Reference to the canvas we use to position our content widgets
- L88 _private member_ `TWeakPtr<SWindow> ParentWindow;` — The window this content is displayed over
- L91 _private member_ `bool bIsStandalone;` — Whether this a standalone widget (with its own close button) or part of a group of other widgets, paired with tutorial navigation
- L94 _private member_ `FSimpleDelegate OnClosed;` — Delegate fired when a cos ebutton is clicked in tutorial content
- L97 _private member_ `FOnPaintNamedWidget OnPaintNamedWidget;` — Delegate used when drawing/arranging widgets
- L100 _private member_ `FSimpleMulticastDelegate OnResetNamedWidget;` — Delegate used to reset drawing of named widgets
- L103 _private member_ `FOnCacheWindowSize OnCacheWindowSize;` — Delegate used to inform widgets of the current window size, so they can auto-adjust layout
- L106 _private member_ `bool bHasValidContent;` — Flag to see if we have valid content (this widget is created to also supply picker overlays)
- L109 _private member_ `FOnWidgetWasDrawn OnWidgetWasDrawn;` — Delegate for querying whether a widget was drawn

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPaintNamedWidget, TSharedRef<SWidget> , const FGeometry& );` — Delegate used when drawing/arranging widgets
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPaintNamedWidget, TSharedRef<SWidget> , const FGeometry& );` — Delegate used when drawing/arranging widgets
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCacheWindowSize, const FVector2D& );` — Delegate used to inform widgets of the current window size, so they can auto-adjust layout
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCacheWindowSize, const FVector2D& );` — Delegate used to inform widgets of the current window size, so they can auto-adjust layout
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetWasDrawn, const FName& );` — Delegates for registering & querying whether a widget was drawn
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetWasDrawn, const FName& );` — Delegates for registering & querying whether a widget was drawn
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnWasWidgetDrawn, const FName& );`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnWasWidgetDrawn, const FName& );`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialRoot.h` (Private)


#### class `STutorialRoot`  
`class STutorialRoot : public SCompoundWidget, public FGCObject`  
_L20-107_
- inherits: `SCompoundWidget,FGCObject`
- desc: The widget which simply monitors windows in its tick function to see if we need to attach a tutorial overlay.
- L23 _public function_ `SLATE_BEGIN_ARGS( STutorialRoot )`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget implementation
- L36 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject implementation
- L37 _public function_ `virtual FString GetReferencerName() const override`
- L43 _public prototype_ `void LaunchTutorial(UEditorTutorial* InTutorial, IIntroTutorials::ETutorialStartType InStartType, TWeakPtr<SWindow> InNavigationWindow, FSimpleDelegate InOnTutorialClosed, FSimpleDelegate InOnTutorialExited);` — Launch the specified tutorial from the specified window
- L46 _public prototype_ `void CloseAllTutorialContent();` — Close all tutorial content
- L49 _public prototype_ `void ReloadTutorials();` — Reload tutorials that we know about
- L52 _public prototype_ `void GoToPreviousStage();` — Got to the previous stage in the current tutorial
- L55 _public prototype_ `void GoToNextStage(TWeakPtr<SWindow> InNavigationWindow);` — Got to the next stage in the current tutorial
- L58 _public prototype_ `bool WasWidgetDrawn(const FName& InName) const;` — Has this named widget been raw anywhere this frame?
- L61 _public prototype_ `void WidgetWasDrawn(const FName& InName);` — Register that this widget was drawn this frame
- L64 _public prototype_ `void AttachWidget(TSharedPtr<SWidget> Widget);` — This is currently used for the "loading" widget
- L67 _public prototype_ `void DetachWidget();` — This is currently used for the "loading" widget
- L71 _private prototype_ `void HandleNextClicked(TWeakPtr<SWindow> InNavigationWindow);` — Handle when the next button is clicked
- L74 _private prototype_ `void HandleBackClicked();` — Handle when the back button is clicked
- L77 _private prototype_ `void HandleHomeClicked();` — Handle when the home button is clickeds
- L80 _private prototype_ `void HandleCloseClicked();` — Handle when the close button is clicked
- L83 _private prototype_ `UEditorTutorial* HandleGetCurrentTutorial();` — Handle retrieving the current tutorial
- L86 _private prototype_ `int32 HandleGetCurrentTutorialStage();` — Handle retrieving the current tutorial stage
- L89 _private prototype_ `void MaybeAddOverlay(TSharedRef<SWindow> InWindow);` — Function called on Tick() to check active windows for whether they need an overlay adding
- L93 _private member_ `TMap<TWeakPtr<SWindow>, TWeakPtr<SEditorTutorials>> TutorialWidgets;` — Container widgets, inserted into window overlays
- L96 _private member_ `TObjectPtr<UEditorTutorial> CurrentTutorial;` — Tutorial we are currently viewing
- L99 _private member_ `int32 CurrentTutorialStage;` — Current stage of tutorial
- L102 _private member_ `float CurrentTutorialStartTime;` — Start time of the current tutorial, if any
- L105 _private member_ `TArray<FName> DrawnWidgets;` — Current drawn widgets for the last frame
- L106 _private member_ `TArray<FName> PreviouslyDrawnWidgets;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/STutorialsBrowser.h` (Private)


#### struct `ITutorialListEntry`  
`struct ITutorialListEntry`  
_L24-46_
- desc: Abstract base class for list entries in the tutorial menu
- L27 _public prototype_ `virtual TSharedRef<ITableRow> OnGenerateTutorialRow(const TSharedRef<STableViewBase>& OwnerTable) const = 0;` — Generate content for a tree entry
- L30 _public prototype_ `virtual bool PassesFilter(const FString& InCategoryFilter, const FString& InFilter) const = 0;` — Whether this entry passes the current filter criteria
- L33 _public prototype_ `virtual FText GetTitleText() const = 0;` — Get the text representation of this item's title
- L36 _public prototype_ `virtual int32 GetSortOrder() const = 0;` — Get a priority value to override alphabetical sorting
- L42 _public prototype_ `virtual bool SortAgainst(TSharedRef<ITutorialListEntry> OtherEntry) const = 0;` — Sort this entry against another entry @return true if this < OtherEntry
- L45 _public prototype_ `virtual EVisibility GetCompletedVisibility() const = 0;` — Return true if this entry should show up as completed (currently used to hide/show green check mark)

#### class `STutorialsBrowser`  
`class STutorialsBrowser : public SCompoundWidget`  
_L53-164_
- inherits: `SCompoundWidget`
- desc: The widget which holds all available tutorials
- L55 _private function_ `SLATE_BEGIN_ARGS( STutorialsBrowser )`
- L57 _private prototype_ `SLATE_ARGUMENT(FSimpleDelegate, OnClosed) SLATE_ARGUMENT(FOnLaunchTutorial, OnLaunchTutorial) SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArray<FTutorialCategory>, ExternalCategories) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L67 _private prototype_ `void SetFilter(const FString& InFilter);` — Set the current filter string. Filters are used to only show the specified category of tutorials (e.g. only Blueprint tutorials)
- L70 _private prototype_ `void ReloadTutorials();` — Reload all tutorials that we know about
- L74 _protected prototype_ `TSharedRef<ITableRow> OnGenerateTutorialRow(TSharedPtr<ITutorialListEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Handle generating a table row in the browser
- L77 _protected prototype_ `FReply OnCloseButtonClicked();` — Handle closing the browser
- L80 _protected prototype_ `FReply OnBackButtonClicked();` — Handle traversing back up the browser hierarchy
- L83 _protected prototype_ `bool IsBackButtonEnabled() const;` — Handle whether the back button can be clicked
- L86 _protected prototype_ `void OnTutorialSelected(UEditorTutorial* InTutorial, bool bRestart);` — Delegate handler fired when a tutorial is selected form the browser
- L89 _protected prototype_ `void OnCategorySelected(const FString& InCategory);` — Delegate handler fired when a category is selected form the browser
- L92 _protected prototype_ `void FilterTutorials();` — Filter displayed tutorials - regenerates the displayed items
- L95 _protected prototype_ `TSharedPtr<FTutorialListEntry_Category> RebuildCategories();` — Rebuild the displayed categories
- L98 _protected prototype_ `void RebuildTutorials(TSharedPtr<FTutorialListEntry_Category> InRootCategory);` — Rebuild the displayed tutorials
- L101 _protected prototype_ `TSharedPtr<FTutorialListEntry_Category> FindCategory_Recursive(TSharedPtr<FTutorialListEntry_Category> InCategory) const;` — Recursive helper function used to find a category given the current NavigationFilter
- L104 _protected prototype_ `void OnSearchTextChanged(const FText& InText);` — Handle rebuilding the browser display when the filter text changes
- L107 _protected prototype_ `FText GetSearchText() const;` — Supplies the text to display in the filter box
- L110 _protected prototype_ `void OnBreadcrumbClicked(const TSharedPtr<ITutorialListEntry>& InEntry);` — Handle clicking the breadcrumb trail
- L113 _protected prototype_ `void RebuildCrumbs();` — Rebuild the breadcrumb trail according to the current category
- L116 _protected prototype_ `void HandleAssetAdded(const FAssetData& InAssetData);` — Handle an asset being added - rebuild our list if required
- L121 _private prototype_ `EActiveTimerReturnType TriggerReloadTutorials( double InCurrentTime, float InDeltaTime );` — Triggers a reload of the tutorials
- L124 _private member_ `TSharedPtr<FTutorialListEntry_Category> RootEntry;` — Root entry of the tutorials tree
- L127 _private member_ `TArray<TSharedPtr<ITutorialListEntry>> FilteredEntries;` — Current filtered entries
- L130 _private member_ `TSharedPtr<SListView<TSharedPtr<ITutorialListEntry>>> TutorialList;` — List of tutorials widget
- L133 _private member_ `FSimpleDelegate OnClosed;` — Delegate fired when the close button is clicked
- L136 _private member_ `FOnLaunchTutorial OnLaunchTutorial;` — Delegate fired when a tutorial is selected
- L139 _private member_ `FText SearchFilter;` — Current search string
- L142 _private member_ `FString NavigationFilter;` — Current category navigation string
- L145 _private member_ `FString CategoryFilter;` — Static category filter for this browser
- L148 _private member_ `TWeakPtr<FTutorialListEntry_Category> CurrentCategoryPtr;` — Cached current category
- L151 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Parent window of this browser
- L154 _private member_ `TSharedPtr<SBreadcrumbTrail<TSharedPtr<ITutorialListEntry>>> BreadcrumbTrail;` — Breadcrumb trail for path display
- L157 _private member_ `bool bNeedsRefresh;` — Whether we need to refresh the content in the browser
- L160 _private member_ `float RefreshTimer;` — Prevent us from refreshing too often
- L163 _private member_ `TArray<FTutorialCategory> ExternalCategories;` — Categories that were registered externally, i.e. by a plugin

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnLaunchTutorial, UEditorTutorial* , IIntroTutorials::ETutorialStartType , TWeakPtr<SWindow> , FSimpleDelegate , FSimpleDelegate );`
- L21 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnLaunchTutorial, UEditorTutorial* , IIntroTutorials::ETutorialStartType , TWeakPtr<SWindow> , FSimpleDelegate , FSimpleDelegate );`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialHyperlinkDecorator.h` (Private)


#### class `FTutorialHyperlinkDecorator`  
`class FTutorialHyperlinkDecorator : public FHyperlinkDecorator`  
_L11-24_
- inherits: `FHyperlinkDecorator`
- L15 _public prototype_ `static TSharedRef< FTutorialHyperlinkDecorator > Create( FString InId, const FSlateHyperlinkRun::FOnClick& InNavigateDelegate, const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate, const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate );`
- L19 _public prototype_ `virtual TSharedRef< ISlateRun > Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style) override;`
- L23 _protected prototype_ `FTutorialHyperlinkDecorator( FString InId, const FSlateHyperlinkRun::FOnClick& InNavigateDelegate, const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate, const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate );`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialHyperlinkRun.h` (Private)


#### class `FTutorialHyperlinkRun`  
`class FTutorialHyperlinkRun : public FSlateHyperlinkRun`  
_L8-42_
- inherits: `FSlateHyperlinkRun`
- L12 _public prototype_ `static TSharedRef< FTutorialHyperlinkRun > Create( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FHyperlinkStyle& InStyle, FOnClick NavigateDelegate, FOnGenerateTooltip InTooltipDelegate, FOnGetTooltipText InTooltipTextDelegate );`
- L18 _public function_ `virtual ~FTutorialHyperlinkRun()`
- L21 _public prototype_ `virtual FVector2D Measure( int32 StartIndex, int32 EndIndex, float Scale, const FRunTextContext& TextContext ) const override;` — FSlateHyperlinkRun implementation
- L22 _public prototype_ `virtual TSharedRef< ILayoutBlock > CreateBlock( int32 StartIndex, int32 EndIndex, FVector2D Size, const FLayoutBlockTextContext& TextContext, const TSharedPtr< IRunRenderer >& Renderer ) override;`
- L26 _private prototype_ `FTutorialHyperlinkRun( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FHyperlinkStyle& InStyle, FOnClick InNavigateDelegate, FOnGenerateTooltip InTooltipDelegate, FOnGetTooltipText InTooltipTextDelegate );`
- L30 _private prototype_ `FTutorialHyperlinkRun( const FTutorialHyperlinkRun& Run );`
- L34 _private prototype_ `bool CheckIsBrowserLink() const;` — check whether our metadata makes us a browser link
- L38 _private member_ `bool bIsBrowserLink;` — Whether we are an external (browser) link or not
- L41 _private member_ `const FSlateBrush* LinkBrush;` — The brush we use to display external links

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialImageDecorator.h` (Private)


#### class `FTutorialImageDecorator`  
`class FTutorialImageDecorator : public ITextDecorator`  
_L10-28_
- inherits: `ITextDecorator`
- L14 _public prototype_ `static TSharedRef< FTutorialImageDecorator > Create();`
- L15 _public function_ `virtual ~FTutorialImageDecorator()`
- L19 _public prototype_ `virtual bool Supports( const FTextRunParseResults& RunParseResult, const FString& Text ) const override;`
- L21 _public prototype_ `virtual TSharedRef< ISlateRun > Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style) override;`
- L23 _public prototype_ `static FString GetPathToImage(const FString& InSrcMetaData);`
- L27 _private prototype_ `FTutorialImageDecorator();`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialSettings.h` (Private)


#### class `UTutorialSettings`  
`class UTutorialSettings : public UObject`  
_L14-25_
- reflection: `UCLASS(config=Editor)`
- inherits: `UObject`
- desc: Per-project tutorial settings
- L20 _private member_ `TArray<FTutorialCategory> Categories;` — `UPROPERTY(Config, EditAnywhere, Category="Tutorials")` — Categories for tutorials
- L24 _private member_ `FSoftClassPath StartupTutorial;` — `UPROPERTY(Config, EditAnywhere, Category="Tutorials", meta=(MetaClass="/Script/IntroTutorials.EditorTutorial"))` — Tutorial to start on project startup

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialStateSettings.h` (Private)


#### struct `FTutorialProgress`  
`struct FTutorialProgress`  
_L15-37_
- reflection: `USTRUCT()`
- desc: Track the progress of an individual tutorial
- L19 _public function_ `FTutorialProgress() : CurrentStage(0) , bUserDismissed(false) , bUserDismissedThisSession(false)`
- L27 _public member_ `FSoftClassPath Tutorial;` — `UPROPERTY()`
- L30 _public member_ `int32 CurrentStage;` — `UPROPERTY()`
- L33 _public member_ `bool bUserDismissed;` — `UPROPERTY()`
- L36 _public member_ `bool bUserDismissedThisSession;` — Non-persistent flag indicating the user dismissed this tutorial

#### class `UTutorialStateSettings`  
`class UTutorialStateSettings : public UObject`  
_L41-88_
- reflection: `UCLASS(config=EditorSettings)`
- inherits: `UObject`
- desc: Tutorial settings used to track completion state
- L46 _private member_ `TArray<FTutorialProgress> TutorialsProgress;` — `UPROPERTY(Config)`
- L49 _private prototype_ `virtual void PostInitProperties() override;` — UObject interface
- L52 _private prototype_ `void ClearProgress();` — Reset the progress and completion sate of all tutorials
- L55 _private prototype_ `int32 GetProgress(UEditorTutorial* InTutorial, bool& bOutHaveSeenTutorial) const;` — Get the recorded progress of the pass-in tutorial
- L58 _private prototype_ `bool HaveSeenTutorial(UEditorTutorial* InTutorial) const;` — Check if we have seen the passed-in tutorial before
- L61 _private prototype_ `bool HaveCompletedTutorial(UEditorTutorial* InTutorial) const;` — Check if completed the passed in tutorial (i.e. seen all of its stages)
- L64 _private prototype_ `void DismissTutorial(UEditorTutorial* InTutorial, bool bDismissAcrossSessions);` — Flag a tutorial as dismissed
- L67 _private prototype_ `bool IsTutorialDismissed(UEditorTutorial* InTutorial) const;` — Check if a tutorial has been dismissed
- L70 _private prototype_ `void RecordProgress(UEditorTutorial* InTutorial, int32 CurrentStage);` — Record the progress of the passed-in tutorial
- L73 _private prototype_ `void SaveProgress();` — Save the progress of all our tutorials
- L76 _private prototype_ `void DismissAllTutorials();` — Dismiss all tutorials, used by right-click option on scholar cap button (STutorialButton)
- L79 _private prototype_ `bool AreAllTutorialsDismissed();` — Returns true if user has dismissed tutorials
- L83 _private member_ `TMap<UEditorTutorial*, FTutorialProgress> ProgressMap;` — Recorded progress
- L87 _private member_ `bool bDismissedAllTutorials;` — `UPROPERTY(Config)` — Record if user has chosen to cancel all tutorials

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialStructCustomization.h` (Private)


#### class `FTutorialContentCustomization`  
`class FTutorialContentCustomization : public IPropertyTypeCustomization`  
_L9-17_
- inherits: `IPropertyTypeCustomization`
- desc: Struct customization for FTutorialContent
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L16 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

#### class `FTutorialContentAnchorCustomization`  
`class FTutorialContentAnchorCustomization : public IPropertyTypeCustomization`  
_L20-28_
- inherits: `IPropertyTypeCustomization`
- desc: Struct customization for FTutorialContentAnchor
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialText.h` (Private)


#### enum `EHyperlinkType::Type`  
`enum Type`  
_L14-21_
- L16 _public enumerator_ `Browser`
- L17 _public enumerator_ `UDN`
- L18 _public enumerator_ `Tutorial`
- L19 _public enumerator_ `Code`
- L20 _public enumerator_ `Asset`

#### struct `FHyperlinkTypeDesc`  
`struct FHyperlinkTypeDesc`  
_L25-58_
- desc: Helper struct to hold info about hyperlink types
- L27 _public function_ `FHyperlinkTypeDesc(EHyperlinkType::Type InType, const FText& InText, const FText& InTooltipText, const FString& InId, FSlateHyperlinkRun::FOnClick InOnClickedDelegate, FSlateHyperlinkRun::FOnGetTooltipText InTooltipTextDelegate = FSlateHyperlinkRun::FOnGetTooltipText(), FSlateHyperlinkRun::FOnGenerateTooltip InTooltipDelegate = FSlateHyperlinkRun::FOnGenerateTooltip()) : Type(InType) , Id(InId) , Text(InText) , TooltipText(InTooltipText) , OnClickedDelegate(InOnClickedDelegate) , TooltipTextDelegate(InTooltipTextDelegate) , TooltipDelegate(InTooltipDelegate)`
- L39 _public member_ `EHyperlinkType::Type Type;` — The type of the link
- L42 _public member_ `FString Id;` — Tag used by this hyperlink's run
- L45 _public member_ `FText Text;` — Text to display in the UI
- L48 _public member_ `FText TooltipText;` — Tooltip text to display in the UI
- L51 _public member_ `FSlateHyperlinkRun::FOnClick OnClickedDelegate;` — Delegate to execute for this hyperlink's run
- L54 _public member_ `FSlateHyperlinkRun::FOnGetTooltipText TooltipTextDelegate;` — Delegate used to retrieve the text to display in the hyperlink's tooltip
- L57 _public member_ `FSlateHyperlinkRun::FOnGenerateTooltip TooltipDelegate;` — Delegate used to generate hyperlink's tooltip

#### struct `FTextStyleAndName`  
`struct FTextStyleAndName`  
_L62-168_
- desc: Text style and name to display in the UI
- L76 _public function_ `FTextStyleAndName(FName InStyle, FText InDisplayName) : Style(InStyle) , DisplayName(InDisplayName)`
- L81 _public function_ `FRunInfo CreateRunInfo() const`
- L88 _public function_ `static FName GetStyleFromRunInfo(const FRunInfo& InRunInfo)`
- L153 _public function_ `FTextBlockStyle CreateTextBlockStyle() const`
- L158 _public function_ `static FTextBlockStyle CreateTextBlockStyle(const FRunInfo& InRunInfo)`
- L164 _public member_ `FName Style;` — The style identifier
- L167 _public member_ `FText DisplayName;` — The text to display for this style

#### struct `FTextStyleAndName::EFontStyle`  
`struct EFontStyle`  
_L65-74_
- desc: Legacy: Flags controlling which TTF or OTF font should be picked from the given font family
- L67 _public typedef_ `typedef uint8 Flags;`

#### enum `FTextStyleAndName::EFontStyle::Flag`  
`enum Flag`  
_L68-73_
- L70 _public enumerator_ `Regular = 0`
- L71 _public enumerator_ `Bold = 1<<0`
- L72 _public enumerator_ `Italic = 1<<1`

#### struct `FTutorialText`  
`struct FTutorialText`  
_L173-185_
- desc: Helper functions for generating rich text
- L176 _public prototype_ `static void GetRichTextDecorators(bool bForEditing, TArray<TSharedRef<class ITextDecorator>>& OutDecorators);`
- L178 _public prototype_ `static const TArray<TSharedPtr<FHyperlinkTypeDesc>>& GetHyperLinkDescs();`
- L181 _private prototype_ `static void Initialize();`
- L184 _private member_ `static TArray<TSharedPtr<FHyperlinkTypeDesc>> HyperlinkDescs;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EHyperlinkType`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Public/EditorTutorial.h` (Public)


#### enum `ETutorialContent::Type`  
`enum Type : int`  
_L20-33_
- L23 _public enumerator_ `None` — Blank - displays no content
- L26 _public enumerator_ `Text` — Plain text content
- L29 _public enumerator_ `UDNExcerpt` — Content from a UDN excerpt
- L32 _public enumerator_ `RichText` — Rich text content

#### enum `ETutorialAnchorIdentifier::Type`  
`enum Type : int`  
_L40-50_
- L43 _public enumerator_ `None` — No anchor
- L46 _public enumerator_ `NamedWidget` — Uses a tutorial wrapper widget
- L49 _public enumerator_ `Asset` — An asset accessible via the content browser

#### struct `FTutorialCategory`  
`struct FTutorialCategory`  
_L55-82_
- reflection: `USTRUCT()`
- desc: Category description
- L61 _public member_ `FString Identifier;` — `UPROPERTY(EditAnywhere, Category="Content")` — Period-separated category name, e.g. "Editor Quickstart.Level Editor"
- L65 _public member_ `FText Title;` — `UPROPERTY(EditAnywhere, Category="Content")` — Title of the category
- L69 _public member_ `int32 SortOrder = INDEX_NONE;` — `UPROPERTY()` — Sort order, used by the tutorial browser - set in editor game-agnostic INI file
- L73 _public member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category="Content", meta=(MultiLine=true))` — Localized text to use to describe this category
- L77 _public member_ `FString Icon;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Icon for this tutorial, used when presented to the user in the tutorial browser. Only used if there isn't a valid texture to use.
- L81 _public member_ `FSoftObjectPath Texture;` — `UPROPERTY(EditAnywhere, Category="Tutorial", meta=(AllowedClasses="/Script/Engine.Texture2D"))` — Texture for this tutorial, used when presented to the user in the tutorial browser.

#### struct `FTutorialContent`  
`struct FTutorialContent`  
_L86-110_
- reflection: `USTRUCT()`
- desc: Content wrapper
- L90 _public function_ `FTutorialContent()`
- L97 _public member_ `TEnumAsByte<ETutorialContent::Type> Type;` — `UPROPERTY(EditAnywhere, Category="Content")` — The type of this content
- L101 _public member_ `FString Content;` — `UPROPERTY(EditAnywhere, Category="Content")` — Content reference string, path etc.
- L105 _public member_ `FString ExcerptName;` — `UPROPERTY(EditAnywhere, Category="Content")` — Excerpt name for UDN excerpt
- L109 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, Category="Content", meta=(MultiLine=true))` — Localized text to use with this content

#### struct `FTutorialContentAnchor`  
`struct FTutorialContentAnchor`  
_L114-155_
- reflection: `USTRUCT()`
- desc: A way of identifying something to be highlighted by a tutorial
- L118 _public function_ `FTutorialContentAnchor()`
- L125 _public member_ `TEnumAsByte<ETutorialAnchorIdentifier::Type> Type;` — `UPROPERTY(EditAnywhere, Category="Anchor")`
- L129 _public member_ `FName WrapperIdentifier;` — `UPROPERTY(EditAnywhere, Category="Anchor")` — If widget is in a wrapper widget, this is the wrapper widget name
- L133 _public member_ `FSoftObjectPath Asset;` — `UPROPERTY(EditAnywhere, Category="Anchor")` — If reference is an asset, we use this to resolve it
- L137 _public member_ `bool bDrawHighlight;` — `UPROPERTY(EditAnywhere, Category="Anchor")` — Whether to draw an animated highlight around the widget
- L141 _public member_ `FString TabToFocusOrOpen;` — `UPROPERTY(EditAnywhere, Category = "Anchor")` — Tab on which to focus (EG 'My Blueprint' tab).
- L146 _public member_ `FString FriendlyName;` — `UPROPERTY(EditAnywhere, Category = "AnchorMeta|FBlueprintGraphNodeMetaData")` — User friendly name to display in the dialog
- L150 _public member_ `FString GUIDString;` — `UPROPERTY(EditAnywhere, Category = "AnchorMeta|FBlueprintGraphNodeMetaData")` — The GUID string
- L154 _public member_ `FString OuterName;` — `UPROPERTY(EditAnywhere, Category = "AnchorMeta|FBlueprintGraphNodeMetaData")` — Name of the outer object - should be the blueprint that 'owns' the node

#### struct `FTutorialWidgetContent`  
`struct FTutorialWidgetContent`  
_L159-197_
- reflection: `USTRUCT()`
- desc: Content that is displayed relative to a widget
- L163 _public function_ `FTutorialWidgetContent()`
- L174 _public member_ `FTutorialContent Content;` — `UPROPERTY(EditAnywhere, Category="Widget")` — Content to associate with widget
- L178 _public member_ `FTutorialContentAnchor WidgetAnchor;` — `UPROPERTY(EditAnywhere, Category="Widget")` — Anchor for content widget to highlight
- L181 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Widget")`
- L184 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Widget")`
- L188 _public member_ `FVector2D Offset;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Widget")` — Custom offset from widget
- L192 _public member_ `float ContentWidth;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Widget", meta=(UIMin="10.0", UIMax="600.0"))` — Content width - text will be wrapped at this point
- L196 _public member_ `bool bAutoFocus;` — `UPROPERTY(EditAnywhere, Category = "Anchor")` — If this a node that can be focused (EG a blueprint node) should we auto focus on it

#### struct `FTutorialStage`  
`struct FTutorialStage`  
_L201-232_
- reflection: `USTRUCT()`
- desc: A single tutorial stage, containing the optional main content & a number of widgets with content attached
- L207 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category="Stage")` — Identifier for this stage
- L211 _public member_ `FTutorialContent Content;` — `UPROPERTY(EditAnywhere, Category="Stage")` — Non-widget-bound content to display in this stage
- L215 _public member_ `TArray<FTutorialWidgetContent> WidgetContent;` — `UPROPERTY(EditAnywhere, Category="Stage")` — Widget-bound content to display for this stage
- L219 _public member_ `FText NextButtonText;` — `UPROPERTY(EditAnywhere, Category="Stage")` — Text to display on the next button
- L223 _public member_ `FText BackButtonText;` — `UPROPERTY(EditAnywhere, Category = "Stage")` — Text to display on the back button
- L227 _public member_ `TArray<FString> PlatformsToTest;` — `UPROPERTY(EditAnywhere, Category = "Stage")` — List of platforms to test against. Meaning of test is determined by InvertPlatformTest.
- L231 _public member_ `bool bInvertPlatformTest = true;` — `UPROPERTY(EditAnywhere, Category = "Stage")` — If false, stage will be skipped if running on any platform in PlatformsToTest. If true, the stage will be if not running on any platform in PlatformsToTest.

#### class `UEditorTutorial`  
`class UEditorTutorial : public UObject`  
_L236-370_
- reflection: `UCLASS(Blueprintable, hideCategories=(Object), EditInlineNew)`
- inherits: `UObject`
- desc: An asset used to build a stage-by-stage tutorial in the editor
- L242 _private member_ `FText Title;` — `UPROPERTY(EditAnywhere, Category="Tutorial", AssetRegistrySearchable)` — Title of this tutorial, used when presented to the user
- L246 _private member_ `int32 SortOrder=0;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tutorial")` — Sorting priority, used by the tutorial browser
- L250 _private member_ `FString Icon;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Icon name for this tutorial, used when presented to the user in the tutorial browser. This is a name for the icon in the Slate editor style. Only used if there isn't a valid texture to use.
- L254 _private member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Texture for this tutorial, used when presented to the user in the tutorial browser.
- L258 _private member_ `FString Category;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Category of this tutorial, used to organize tutorials when presented to the user
- L262 _private member_ `FTutorialContent SummaryContent;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Content to be displayed for this tutorial when presented to the user in summary
- L266 _private member_ `TArray<FTutorialStage> Stages;` — `UPROPERTY(EditAnywhere, Category="Stages")` — The various stages of this tutorial
- L270 _private member_ `FSoftClassPath PreviousTutorial;` — `UPROPERTY(EditAnywhere, Category = "Tutorial", meta = (MetaClass = "/Script/IntroTutorials.EditorTutorial"))` — Tutorial to optionally chain back to if the "back" button is clicked on the first stage
- L274 _private member_ `FSoftClassPath NextTutorial;` — `UPROPERTY(EditAnywhere, Category="Tutorial", meta=(MetaClass="/Script/IntroTutorials.EditorTutorial"))` — Tutorial to optionally chain onto after this tutorial completes
- L282 _private prototype_ `AActor* GetActorReference(FString PathToActor);` — `UFUNCTION(BlueprintPure, Category = "Tutorial")` — Attempts to find the actor specified by PathToActor in the current editor world @param	PathToActor	The path to the actor (e.g. PersistentLevel.PlayerStart) @return	A reference to the actor, or none if it wasn't found
- L286 _private member_ `bool bIsStandalone;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — A standalone tutorial displays no navigation buttons and each content widget has a close button
- L290 _private member_ `FSoftObjectPath AssetToUse;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Asset to open & attach the tutorial to. Non-widget-bound content will appear in the asset's window
- L294 _private member_ `FString ImportPath;` — `UPROPERTY()` — The path this tutorial was imported from, if any.
- L298 _private member_ `bool bHideInBrowser;` — `UPROPERTY(EditAnywhere, Category="Tutorial")` — Hide this tutorial in the tutorials browser
- L301 _private prototype_ `virtual UWorld* GetWorld() const override;` — UObject implementation
- L305 _private member_ `FText SearchTags;` — `UPROPERTY(EditAnywhere, Category = "Tutorial", AssetRegistrySearchable)` — Comma seperated list of tags the search will use to help find this tutorial
- L309 _public prototype_ `void HandleTutorialStageStarted(FName StageName);` — Called when a tutorial stage is started
- L312 _public prototype_ `void HandleTutorialStageEnded(FName StageName);` — Called when a tutorial stage ends
- L315 _public prototype_ `void HandleTickCurrentStage(FName StageName);` — Called each tick so the Blueprint can optionally complete or skip stages
- L318 _public prototype_ `void HandleTutorialLaunched();` — Called when a tutorial is launched
- L321 _public prototype_ `void HandleTutorialClosed();` — Called when a tutorial is closed
- L326 _protected prototype_ `void OnTutorialStageStarted(FName StageName);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Tutorial")` — Event fired when a tutorial stage begins
- L330 _protected prototype_ `void OnTutorialStageEnded(FName StageName);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Tutorial")` — Event fired when a tutorial stage ends
- L334 _protected prototype_ `void OnTutorialLaunched();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Tutorial")` — Event fired when a tutorial is launched
- L338 _protected prototype_ `void OnTutorialClosed();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Tutorial")` — Event fired when a tutorial is closed
- L342 _protected prototype_ `static void GoToNextTutorialStage();` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Advance to the next stage of a tutorial
- L346 _protected prototype_ `static void GoToPreviousTutorialStage();` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Advance to the previous stage of a tutorial
- L350 _protected prototype_ `static void BeginTutorial(UEditorTutorial* TutorialToStart, bool bRestart);` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Begin a tutorial. Note that this will end the current tutorial that is in progress, if any
- L357 _protected prototype_ `static void OpenAsset(UObject* Asset);` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Open an asset for use by a tutorial @param	Asset	The asset to open
- L363 _protected prototype_ `static void SetEngineFolderVisibilty(bool bNewVisibility);` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Sets the visibility of the engine folder in the content browser
- L369 _protected prototype_ `static bool GetEngineFolderVisibilty();` — `UFUNCTION(BlueprintCallable, Category="Tutorial")` — Returns the visibility of the engine folder in the content browser

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ETutorialContent`
- L38 _namespace_ `namespace ETutorialAnchorIdentifier`

### `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Public/IIntroTutorials.h` (Public)


#### class `IIntroTutorials`  
`class IIntroTutorials : public IModuleInterface`  
_L18-99_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L29 _public function_ `static inline IIntroTutorials& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L51 _public prototype_ `virtual void LaunchTutorial(const FString& TutorialAssetName, TSharedPtr<SWindow> InNavigationWindow = nullptr ) = 0;` — Launch a tutorial with the specified asset. @param TutorialAssetName The name of the tutorial asset.
- L71 _public prototype_ `virtual void LaunchTutorial(UEditorTutorial* Tutorial, IIntroTutorials::ETutorialStartType InStartType = TST_RESTART, TWeakPtr<SWindow> InNavigationWindow = nullptr, FSimpleDelegate OnTutorialClosed = FSimpleDelegate(), FSimpleDelegate OnTutorialExited = FSimpleDelegate()) = 0;` — Launch a tutorial immediately, bypassing the tutorial browser. @param	Tutorial	The tutorial to launch @param	bRestart	Whether to restart the tutorial or resume from where we left off last time. @param	InNavigationWindow	Optional window to launch the tutorial from - this is where navigation will be displayed.
- L76 _public prototype_ `virtual void CloseAllTutorialContent() = 0;` — Close all tutorial content, including the browser.
- L84 _public prototype_ `virtual TSharedRef<SWidget> CreateTutorialsWidget(FName InContext, TWeakPtr<SWindow> InContextWindow = nullptr) const = 0;` — Create a widget that allows access to the tutorial for the current context. @param	InContext			The name of the context this widget is attached to (e.g. "LevelEditor") @param	InContextWindow		The window that the context is attached to (e.g. the main window, or an asset editor tab) @return a widget used to access context-sensitive tutorials
- L91 _public prototype_ `virtual TSharedPtr<SWidget> CreateTutorialsLoadingWidget(TWeakPtr<SWindow> InContextWindow = nullptr) const = 0;` — Create a widget that shows a "loading" visual while waiting for tutorials to load. @param	InContextWindow		The window that the context is attached to (e.g. the main window, or an asset editor tab) @return a widget used to access context-sensitive tutorials
- L98 _public prototype_ `virtual void RegisterCategory(FTutorialCategory NewCategory) = 0;` — Register a new category with the tutorial browser. Categories are automatically created when tutorial blueprints are discovered, but this will allow you to apply some customization for tutorial categories defined by plugins @param	InTutorialCategory	The new category

#### enum `IIntroTutorials::ETutorialStartType`  
`enum ETutorialStartType`  
_L54-62_
- desc: Parameter for LaunchTutorial function
- L57 _public enumerator_ `TST_CONTINUE` — Default start type, picks up where user left off if appropriate
- L59 _public enumerator_ `TST_RESTART` — Restart and clear progress
- L61 _public enumerator_ `TST_LASTSTAGE` — Start at the last stage of the tutorial, used when backing up to a previous tutorial
