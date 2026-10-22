# Editor / MainFrame

- module root: `Source/Editor/MainFrame`
- headers: 20; symbols: 541
- symbol kinds: class=23, delegate=15, enum=5, enumerator=22, function=67, macro=3, member=156, prototype=240, struct=8, typedef=2
- DynamicallyLoadedModuleNames: AssetTools, GameProjectGeneration, HotReload, LevelEditor, LocalizationDashboard, ProjectTargetPlatformEditor, SourceCodeAccess
- PrivateDependencyModuleNames: Analytics, ApplicationCore, Core, CoreUObject, DesktopPlatform, DeviceProfileEditor, EditorFramework, Engine, EngineSettings, HTTP, InputCore, InterchangeCore, InterchangeEngine, LauncherServices, MessageLog, Projects, RHI, RenderCore, Slate, SlateCore, SourceControl, SourceControlWindows, TargetPlatform, ToolMenus, ToolWidgets, TranslationEditor, UATHelper, UndoHistoryEditor, UnrealEd, WebBrowser, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: GameProjectGeneration, HotReload, LauncherPlatform, LevelEditor, ProjectTargetPlatformEditor, Settings, SourceCodeAccess
- PublicDependencyModuleNames: Documentation

### `Source/Editor/MainFrame/Private/Frame/MainFrameActions.h` (Private)


#### class `FMainFrameCommands`  
`class FMainFrameCommands : public TCommands<FMainFrameCommands>`  
_L18-93_
- inherits: `TCommands<FMainFrameCommands>`
- desc: Unreal editor main frame actions
- L22 _public prototype_ `FMainFrameCommands();` — FMainFrameCommands constructor
- L25 _public member_ `static TSharedRef< FUICommandList > ActionList;` — List of all of the main frame commands
- L27 _public member_ `TSharedPtr< FUICommandInfo > SaveAll;`
- L28 _public member_ `TSharedPtr< FUICommandInfo > Exit;`
- L29 _public member_ `TSharedPtr< FUICommandInfo > ChooseFilesToSave;`
- L30 _public member_ `TSharedPtr< FUICommandInfo > ViewChangelists;`
- L31 _public member_ `TSharedPtr< FUICommandInfo > ViewSnapshotHistory;`
- L32 _public member_ `TSharedPtr< FUICommandInfo > ViewBranchExplorer;`
- L33 _public member_ `TSharedPtr< FUICommandInfo > SubmitContent;`
- L34 _public member_ `TSharedPtr< FUICommandInfo > SyncContent;`
- L35 _public member_ `TSharedPtr< FUICommandInfo > CheckOutModifiedFiles;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > ConnectToSourceControl;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > ChangeSourceControlSettings;`
- L38 _public member_ `TSharedPtr< FUICommandInfo > NewProject;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > OpenProject;`
- L40 _public member_ `TSharedPtr< FUICommandInfo > AddCodeToProject;`
- L41 _public member_ `TSharedPtr< FUICommandInfo > OpenIDE;`
- L42 _public member_ `TSharedPtr< FUICommandInfo > RefreshCodeProject;`
- L43 _public member_ `TSharedPtr< FUICommandInfo > ZipUpProject;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > OpenCurrentProjectDirectory;`
- L45 _public member_ `TSharedPtr< FUICommandInfo > LocalizeProject;`
- L46 _public member_ `TArray< TSharedPtr< FUICommandInfo > > SwitchProjectCommands;`
- L48 _public member_ `TSharedPtr< FUICommandInfo > OpenContentBrowser;`
- L49 _public member_ `TSharedPtr< FUICommandInfo > OpenLevelEditor;`
- L50 _public member_ `TSharedPtr< FUICommandInfo > OpenOutputLog;`
- L51 _public member_ `TSharedPtr< FUICommandInfo > OpenMessageLog;`
- L52 _public member_ `TSharedPtr< FUICommandInfo > OpenKeybindings;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > OpenSessionManagerApp;`
- L54 _public member_ `TSharedPtr< FUICommandInfo > OpenDeviceManagerApp;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > OpenToolbox;`
- L56 _public member_ `TSharedPtr< FUICommandInfo > OpenDebugView;`
- L57 _public member_ `TSharedPtr< FUICommandInfo > OpenClassViewer;`
- L58 _public member_ `TSharedPtr< FUICommandInfo > OpenWidgetReflector;`
- L60 _public member_ `TSharedPtr< FUICommandInfo > DocumentationHome;`
- L61 _public member_ `TSharedPtr< FUICommandInfo > BrowseAPIReference;`
- L62 _public member_ `TSharedPtr< FUICommandInfo > BrowseCVars;`
- L63 _public member_ `TSharedPtr< FUICommandInfo > VisitCommunityHome;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > VisitOnlineLearning;`
- L65 _public member_ `TSharedPtr< FUICommandInfo > VisitForums;`
- L66 _public member_ `TSharedPtr< FUICommandInfo > VisitSearchForAnswersPage;`
- L67 _public member_ `TSharedPtr< FUICommandInfo > VisitCommunitySnippets;`
- L68 _public member_ `TSharedPtr< FUICommandInfo > ReportABug;`
- L69 _public member_ `TSharedPtr< FUICommandInfo > OpenIssueTracker;`
- L70 _public member_ `TSharedPtr< FUICommandInfo > VisitSupportWebSite;`
- L71 _public member_ `TSharedPtr< FUICommandInfo > VisitEpicGamesDotCom;`
- L72 _public member_ `TSharedPtr< FUICommandInfo > AboutUnrealEd;`
- L73 _public member_ `TSharedPtr< FUICommandInfo > CreditsUnrealEd;`
- L76 _public member_ `TSharedPtr< FUICommandInfo > ImportLayout;` — Layout
- L77 _public member_ `TSharedPtr< FUICommandInfo > SaveLayoutAs;`
- L78 _public member_ `TSharedPtr< FUICommandInfo > ExportLayout;`
- L79 _public member_ `TSharedPtr< FUICommandInfo > RemoveUserLayouts;`
- L81 _public member_ `TSharedPtr< FUICommandInfo > ToggleFullscreen;`
- L83 _public prototype_ `virtual void RegisterCommands() override;`
- L90 _private member_ `FAutoConsoleCommand ToggleFullscreenConsoleCommand;` — Console command for toggling full screen.  We need this to expose the full screen toggle action to the game UI system for play-in-editor view ports
- L92 _private prototype_ `void RegisterLayoutCommands();`

#### class `FMainFrameActionCallbacks`  
`class FMainFrameActionCallbacks`  
_L99-330_
- desc: Implementation of various main frame action callback functions
- L104 _public prototype_ `static FReply OnUnhandledKeyDownEvent(const FKeyEvent& InKeyEvent);` — Global handler for unhandled key-down events in the editor.
- L110 _public prototype_ `static bool DefaultCanExecuteAction();` — The default can execute action for all commands unless they override it By default commands cannot be executed if the application is in K2 debug mode.
- L113 _public prototype_ `static bool CanSaveWorld();` — Determine whether we are allowed to save the world at this moment
- L116 _public prototype_ `static void SaveAll();` — Saves all levels and asset packages
- L119 _public prototype_ `static bool CanSubmitContent();` — Determine whether we are allowed to submit content at this moment
- L122 _public prototype_ `static bool CanSyncContent();` — Determine whether we are allocated to sync content at this moment
- L125 _public prototype_ `static void ChoosePackagesToSave();` — Opens a dialog to choose packages to save
- L128 _public prototype_ `static void ViewChangelists();` — Opens a dialog to view the pending changelists
- L131 _public prototype_ `static bool CanViewChangelists();` — Determines whether we can show the changelist view
- L134 _public prototype_ `static void ViewSnapshotHistory();` — Opens a dialog to view the past snapshots
- L137 _public prototype_ `static bool CanViewSnapshotHistory();` — Determines whether we can show the past snapshots view
- L140 _public prototype_ `static void ViewBranchExplorer();` — Opens a dialog to view the branch explorer
- L143 _public prototype_ `static bool CanViewBranchExplorer();` — Determines whether we can show the branch explorer view
- L146 _public prototype_ `static bool IsVisibleBranchExplorer();` — Determines whether we can show the branch explorer menu item
- L149 _public prototype_ `static void CheckOutModifiedFiles();` — Opens a dialog to check out any assets which have been modified
- L152 _public prototype_ `static bool CanCheckOutModifiedFiles();` — Determines whether we can show the dialog to check out any assets which have been modified
- L155 _public prototype_ `static void ConnectToSourceControl();` — Enable source control features
- L158 _public prototype_ `static void Exit();` — Quits the application
- L161 _public prototype_ `static bool Undo_CanExecute();` — Edit menu commands
- L162 _public prototype_ `static bool Redo_CanExecute();`
- L169 _public prototype_ `static void ExecuteExecCommand( FString Command );` — Called when many of the menu items in the main frame context menu are clicked @param Command	The command to execute
- L172 _public prototype_ `static void OpenSlateApp_ViaModule( FName AppName, FName ModuleName );` — Opens up the specified slate window by name after loading the module
- L175 _public prototype_ `static void OpenSlateApp( FName AppName );` — Opens up the specified slate window by name
- L178 _public prototype_ `static bool OpenSlateApp_IsChecked( FName AppName );` — Checks if a slate window is already open
- L181 _public prototype_ `static void ReportABug();` — Visits the report a bug page
- L184 _public prototype_ `static void OpenIssueTracker();` — Opens the issue tracker page
- L187 _public prototype_ `static void VisitSupportWebSite();` — Visits the UDN support web site
- L190 _public prototype_ `static void VisitEpicGamesDotCom();` — Visits EpicGames.com
- L193 _public prototype_ `static void DocumentationHome();` — Opens the documentation home page
- L196 _public prototype_ `static void BrowseAPIReference();` — Opens the API documentation site
- L199 _public prototype_ `static void BrowseCVars();` — Creates an HTML file to browse the console variables and commands
- L202 _public prototype_ `static void VisitCommunityHome();` — Visits the home page of the Epic Games Dev Community web site
- L205 _public prototype_ `static void VisitOnlineLearning();` — Visits the Learning Library on the Epic Games Dev Community web site
- L208 _public prototype_ `static void VisitForums();` — Visits the Unreal Engine community forums
- L211 _public prototype_ `static void VisitSearchForAnswersPage();` — Visits the Q&A section of the Unreal Engine community forums
- L214 _public prototype_ `static void VisitCommunitySnippets();` — Visits the Snippets Repository on the Epic Games Dev Community web site
- L216 _public prototype_ `static void AboutUnrealEd_Execute();`
- L218 _public prototype_ `static void CreditsUnrealEd_Execute();`
- L220 _public prototype_ `static void OpenWidgetReflector_Execute();`
- L223 _public prototype_ `static TSharedRef<SWindow> CreateProjectBrowserWindow(bool bAllowProjectOpening, bool bAllowProjectCreate);` — Return the window used for the Open and New project Browser
- L226 _public prototype_ `static void NewProject( bool bAllowProjectOpening, bool bAllowProjectCreate );` — Opens the new project dialog
- L229 _public prototype_ `static void AddCodeToProject();` — Adds code to the current project if it does not already have any
- L232 _public prototype_ `static bool CanAddCodeToProject();` — Whether we can add code to the current project
- L235 _public prototype_ `static bool IsAddCodeToProjectVisible();` — Whether menu to add code to the current project is visible
- L238 _public prototype_ `static void RefreshCodeProject();` — Refresh the project in the current IDE
- L241 _public prototype_ `static bool CanRefreshCodeProject();` — Whether we can refresh the project in the current IDE
- L244 _public prototype_ `static bool IsRefreshCodeProjectVisible();` — Whether menu to refresh the project in the current IDE is visible
- L247 _public prototype_ `static bool IsCodeProject();` — Determines whether the project is a code project
- L250 _public prototype_ `static void OpenIDE();` — Opens an IDE to edit c++ code
- L253 _public prototype_ `static bool CanOpenIDE();` — Whether we can open the IDE to edit c++ code
- L256 _public prototype_ `static bool IsOpenIDEVisible();` — Whether menu to open the IDE to edit c++ code is visible
- L259 _public prototype_ `static bool IsCPPAllowed();` — Whether C++ edition/creation is allowed from the editor
- L262 _public prototype_ `static void ZipUpProject();` — Zips up the project
- L265 _public prototype_ `static void OpenCurrentProjectDirectory();` — Opens up the project directory
- L268 _public prototype_ `static void LocalizeProject();` — Opens the Project Localization Dashboard
- L271 _public prototype_ `static void SwitchProjectByIndex( int32 ProjectIndex );` — Restarts the editor and switches projects
- L274 _public prototype_ `static void SwitchProject(const FString& GameOrProjectFileName);` — Opens the specified project file or game. Restarts the editor
- L277 _public prototype_ `static void OpenBackupDirectory( FString BackupFile );` — Opens the directory where the backup for preferences is stored.
- L280 _public prototype_ `static void ToggleFullscreen_Execute();` — Toggle the level editor's fullscreen mode
- L283 _public prototype_ `static bool FullScreen_IsChecked();` — Is the level editor fullscreen?
- L292 _public prototype_ `static bool CanSwitchToProject( int32 InProjectIndex );` — Checks if the selected project can be switched to @param	InProjectIndex  Index from the available projects @return true if the selected project can be switched to (i.e. it's not the current project)
- L301 _public prototype_ `static bool IsSwitchProjectChecked( int32 InProjectIndex );` — Checks which Switch Project sub menu entry should be checked @param	InProjectIndex  Index from the available projects @return true if the menu entry should be checked
- L304 _public prototype_ `static void CacheProjectNames();` — Gathers all available projects the user can switch to from main menu
- L309 _public member_ `static TArray<FRecentProjectFile> RecentProjects;` — List of projects that the user can switch to.
- L321 _protected prototype_ `static void AddMessageLog( const FText& Text, const FText& Detail, const FString& TutorialLink, const FString& DocumentationLink );` — Adds a message to the message log. @param Text The main message text. @param Detail The detailed description. @param TutorialLink A link to an associated tutorial. @param DocumentationLink A link to documentation.
- L326 _private member_ `static TWeakPtr<SNotificationItem> ChoosePackagesToCheckInNotification;` — The notification in place while we choose packages to check in
- L329 _private member_ `static TWeakPtr<SWindow> NewProjectWindowWeak;` — New project window weak ptr, used to give the window focus if trying to open a new window when there is already an existing one

### `Source/Editor/MainFrame/Private/Frame/MainFrameHandler.h` (Private)


#### class `FMainFrameHandler`  
`class FMainFrameHandler : public TSharedFromThis<FMainFrameHandler>`  
_L35-279_
- inherits: `TSharedFromThis<FMainFrameHandler>`
- desc: Helper class that handles talking to the Slate App Manager.
- L42 _public function_ `void ShutDownEditor( TSharedRef<SDockTab> TabBeingClosed )` — Shuts down the Editor.
- L50 _public prototype_ `void ShutDownEditor( );` — Shuts down the Editor.
- L57 _public function_ `bool CanCloseTab()` — Checks whether the main frame tab can be closed. @return true if the tab can be closed, false otherwise.
- L72 _public function_ `bool CanCloseEditor()` — Checks whether the Editor tab can be closed. @return true if the Editor can be closed, false otherwise.
- L193 _public function_ `void CloseRootWindowOverride( const TSharedRef<SWindow>& WindowBeingClosed )`
- L213 _public function_ `void OnMainFrameGenerated( const TSharedPtr<SDockTab>& MainTab, const TSharedRef<SWindow>& InRootWindow )` — Method that handles the generation of the mainframe, given the window it resides in, and a string which determines the initial layout of its primary dock area.
- L244 _public prototype_ `void ShowMainFrameWindow(TSharedRef<SWindow> Window, const bool bStartImmersive, const bool bStartPIE) const;` — Shows the main frame window.  Call this after you've setup initial layouts to reveal the window @param bStartImmersive True to force a main frame viewport into immersive mode @param bStartPIE True to start a PIE session right away
- L247 _public function_ `TSharedPtr<SWindow> GetParentWindow() const` — Gets the parent window of the mainframe
- L253 _public function_ `void SetMainTab(const TSharedRef<SDockTab>& MainTab)` — Sets the reference to the main tab
- L259 _public prototype_ `void EnableTabClosedDelegate();` — Enables the delegate responsible for shutting down the editor when the main tab is closed
- L262 _public prototype_ `void DisableTabClosedDelegate();` — Disables the delegate responsible for shutting down the editor when the main tab is closed
- L267 _private function_ `void HandleTabManagerPersistLayout( const TSharedRef<FTabManager::FLayout>& LayoutToSave )` — Callback for persisting the Level Editor's layout.
- L275 _private member_ `TWeakPtr<SDockTab> MainTabPtr;` — Editor main frame window
- L278 _private member_ `TWeakPtr<SWindow> RootWindowPtr;` — The window that all of the editor is parented to.

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "MainFrameHandler"`
- L30 _prototype_ `const FText StaticGetApplicationTitle( const bool bIncludeGameName );`

### `Source/Editor/MainFrame/Private/Frame/RootWindowLocation.h` (Private)


#### struct `FRootWindowLocation`  
`struct FRootWindowLocation`  
_L13-119_
- desc: Describes the position and size of the main window.
- L18 _public member_ `FVector2D ScreenPosition;` — Holds the window's position on the screen.
- L23 _public member_ `FVector2D WindowSize;` — Holds the size of the window.
- L28 _public member_ `bool InitiallyMaximized;` — Whether the window is initially maximized.
- L36 _public function_ `FRootWindowLocation( ) : WindowSize( VectorFromSettings(TEXT("WindowSize"), FVector2D(1280,720)) ) , InitiallyMaximized( BoolFromSettings(TEXT("InitiallyMaximized"), true) )` — Default constructor.
- L46 _public function_ `FRootWindowLocation(FVector2D InWindowSize, bool InInitiallyMaximized) : WindowSize(InWindowSize) , InitiallyMaximized(InInitiallyMaximized)` — Creates and initializes a new instance with the specified size.
- L56 _public function_ `FRootWindowLocation( FVector2D InScreenPosition, FVector2D InWindowSize, bool InInitiallyMaximized ) : ScreenPosition( InScreenPosition ) , WindowSize( InWindowSize ) , InitiallyMaximized( InInitiallyMaximized )` — Creates and initializes a new instance with the specified position and size.
- L68 _public function_ `FVector2D GetCenteredScreenPosition() const` — Set centered screen position based on the size
- L82 _public function_ `void SaveToIni( )` — Saves this structure to the INI file.
- L92 _private function_ `static FVector2D VectorFromSettings( const TCHAR* SettingName, FVector2D DefaultValue )`
- L107 _private function_ `static bool BoolFromSettings( const TCHAR* SettingName, bool DefaultValue )`

### `Source/Editor/MainFrame/Private/HomeScreen/HomeScreenAnalyticsUtils.h` (Private)


#### enum `EHomeScreenElement`  
`enum class EHomeScreenElement : uint8`  
_L9-20_
- reflection: `UENUM()`
- desc: Enum used for Analytics event for the interacted element
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `CreateNewProjectButton`
- L13 _public enumerator_ `OpenProjectButton`
- L14 _public enumerator_ `SectionButton`
- L15 _public enumerator_ `ResourceButton`
- L16 _public enumerator_ `LoadAtStartup`
- L17 _public enumerator_ `SocialLinkButton`
- L18 _public enumerator_ `WebLinkButton`
- L19 _public enumerator_ `CreateStartupProjectButton`

#### enum `EHomeScreenInteractionType`  
`enum class EHomeScreenInteractionType : uint8`  
_L24-28_
- reflection: `UENUM()`
- desc: Enum used for Analytics event for the type of interaction
- L26 _public enumerator_ `None`
- L27 _public enumerator_ `Click`

#### struct `FHomeScreenInteractionAnalyticsParam`  
`struct FHomeScreenInteractionAnalyticsParam`  
_L31-59_
- desc: Helper struct that contains the params for the analytic events
- L33 _public function_ `FHomeScreenInteractionAnalyticsParam() : InteractionType(EHomeScreenInteractionType::None) , bHasProjectsOnMachine(true) , ActiveSection(EMainSectionMenu::None) , LoadAtStartup(EAutoLoadProject::MAX) , DestinationURL(TEXT("None")) , HomeScreenElement(EHomeScreenElement::None)`
- L43 _public member_ `EHomeScreenInteractionType InteractionType;` — Type of the interaction, currently only Click is supported
- L46 _public member_ `bool bHasProjectsOnMachine;` — Whether the user has already projects on its machine
- L49 _public member_ `EMainSectionMenu ActiveSection;` — The current active section
- L52 _public member_ `EAutoLoadProject LoadAtStartup;` — Load at startup option
- L55 _public member_ `FString DestinationURL;` — Link if applicable
- L58 _public member_ `EHomeScreenElement HomeScreenElement;` — The HomeScreen element that the user interacted with

#### class `FHomeScreenInteractionAnalyticsUtils`  
`class FHomeScreenInteractionAnalyticsUtils`  
_L62-67_
- desc: Helper function that sends the Interaction event
- L66 _public prototype_ `static void RegisterInteractionUserAnalytics(FHomeScreenInteractionAnalyticsParam InParam);` — Register a new HomeScreen analytics event based on the given parameters

### `Source/Editor/MainFrame/Private/HomeScreen/HomeScreenMenuContext.h` (Private)


#### class `UHomeScreenContext`  
`class UHomeScreenContext : public UObject`  
_L10-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<SHomeScreen> HomeScreen;`

### `Source/Editor/MainFrame/Private/HomeScreen/HomeScreenWeb.h` (Private)


#### class `UHomeScreenWeb`  
`class UHomeScreenWeb : public UObject`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public prototype_ `void NavigateTo(EMainSectionMenu InSectionToNavigate);` — `UFUNCTION()`
- L20 _public function_ `FOnNavigationChanged& OnNavigationChanged()`
- L23 _public prototype_ `void OpenGettingStartedProject();` — `UFUNCTION()`
- L24 _public function_ `FOnGettingStartedProjectRequested& OnTutorialProjectRequested()`
- L27 _public prototype_ `void OpenWebPage(const FString& InURL) const;` — `UFUNCTION()`
- L28 _public function_ `FOnOpenLink& OnOpenLink()`
- L31 _private member_ `FOnNavigationChanged OnNavigationChangedDelegate;`
- L32 _private member_ `FOnGettingStartedProjectRequested OnTutorialProjectRequestedDelegate;`
- L33 _private member_ `FOnOpenLink OnOpenLinkDelegate;`
- L34 _private member_ `EMainSectionMenu SectionToNavigate = EMainSectionMenu::None;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigationChanged, const EMainSectionMenu);`
- L8 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigationChanged, const EMainSectionMenu);`
- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGettingStartedProjectRequested);`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGettingStartedProjectRequested);`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenLink, FString);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenLink, FString);`

### `Source/Editor/MainFrame/Private/HomeScreen/SHomeScreen.h` (Private)


#### class `SHomeScreen`  
`class SHomeScreen : public SCompoundWidget`  
_L26-216_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SHomeScreen) : _ResourceCommunityEntries() , _SectionLinks() , _AlwaysShowRecentList(false) , _RecentProjectList(SNullWidget::NullWidget) , _UnrealLogoBrush(nullptr) , _OnGetStartupSetting()`
- L37 _public prototype_ `SLATE_ARGUMENT(TArray<FHomeScreenResourceCommunityEntry>, ResourceCommunityEntries) SLATE_ARGUMENT(FHomeScreenSectionToLinkMap, SectionLinks) SLATE_ARGUMENT(bool, AlwaysShowRecentList) SLATE_ARGUMENT(TSharedRef<SWidget>, RecentProjectList) SLATE_ARGUMENT(const FSlateBrush*, UnrealLogoBrush) SLATE_ARGUMENT(FOnGetStartupSetting, OnGetStartupSetting) SLATE_END_ARGS() virtual ~SHomeScreen() override;`
- L48 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the HomeScreen widget
- L51 _public prototype_ `void OnTabForegrounded(TSharedPtr<SDockTab> NewForegroundTab, TSharedPtr<SDockTab> BackgroundTab);` — Used when the HomeScreen tab becomes visible to start the internet connection check or to stop it when it goes in the background
- L54 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L59 _private prototype_ `FReply OnCreateProjectDialog(bool bInAllowProjectOpening, bool bInAllowProjectCreation);` — Opens the Create Project dialog
- L62 _private prototype_ `FReply OnLinkClicked(TAttribute<FString> InURL, const EHomeScreenElement InElement) const;` — Handle the clicked links event
- L65 _private prototype_ `FReply OnLinkClicked(FString InURL, const EHomeScreenElement InElement) const;` — Handle the clicked links event
- L68 _private prototype_ `void OnWebLinkClicked(FString InURL) const;` — Handle a web link being clicked
- L71 _private prototype_ `ECheckBoxState IsMainHomeSectionChecked(EMainSectionMenu InMainHomeSelection) const;` — Checks if a main home section is selected
- L74 _private prototype_ `void OnMainHomeSectionChanged(ECheckBoxState InCheckBoxState, EMainSectionMenu InMainHomeSelection, bool bSkipAnalytics = false);` — Handles changes to the main home section
- L77 _private prototype_ `void OnLoadAtStartupSettingChanged(EAutoLoadProject InAutoLoadOption);` — Callback from the HomeScreenSettings when the LoadAtStartup property change
- L80 _private prototype_ `FReply OnAutoLoadOptionChanged(EAutoLoadProject InAutoLoadOption);` — Handles changes to autoload last project selection
- L83 _private prototype_ `EVisibility IsAutoLoadOptionCheckVisible(EAutoLoadProject InAutoLoadOption) const;` — True if the current AutoLoad option match the given InAutoLoadOption
- L86 _private prototype_ `bool IsCheckBoxCheckedOrHovered(const TSharedPtr<SCheckBox> InCheckBox) const;` — Checks if a checkbox is checked or hovered
- L89 _private prototype_ `FSlateColor GetMainSectionCheckBoxColor(const TSharedPtr<SCheckBox> InCheckBox) const;` — Gets the color of the main section checkbox icon and text
- L92 _private prototype_ `FSlateColor GetResourceAndSocialMediaButtonColor(const TSharedPtr<SButton> InButton) const;` — Gets the color of resource and social media section icon and text
- L95 _private prototype_ `void CreateMainSectionCheckBox(TSharedPtr<SCheckBox>& OutCheckBox, EMainSectionMenu InMainHomeSelection, const FText& InText, const FSlateBrush* InImage);` — Creates a main section checkboxes
- L98 _private prototype_ `void CreateResourceButtons(TSharedPtr<SButton>& OutButton, TAttribute<FString> InLink, const FText& InText, const FSlateBrush* InImage);` — Creates resource buttons
- L101 _private prototype_ `void CreateSocialMediaButtons(TSharedPtr<SButton>& OutButton, FString InLink, const FSlateBrush* InImage);` — Creates social media buttons
- L104 _private prototype_ `void CreateWebBrowserWidgetIfNeeded();` — Creates the webbrowser widget if not initialized yet
- L107 _private prototype_ `TSharedRef<SWidget> CreateComboButtonMenuContentWidget();` — Creates the content widget for the combo button menu
- L110 _private prototype_ `void CheckInternetConnection();` — Checks the internet connection
- L113 _private prototype_ `bool IsConnectedToInternet() const;` — Returns whether the system is connected to the internet
- L116 _private prototype_ `bool IsMainSectionEnabled(EMainSectionMenu InHomeSection) const;` — Returns whether the main section is enabled
- L119 _private prototype_ `int32 GetNoInternetIconIndex() const;` — Gets the index of the SWidgetSwitcher for the no internet icon, either NoInternet or Loading when retrying
- L122 _private prototype_ `void OnNavigateToSection(EMainSectionMenu InSectionToNavigate);` — Handles navigation to a section from a web request
- L125 _private prototype_ `void OnOpenGettingStartedProject();` — Handles the getting started template project creation
- L128 _private prototype_ `FText GetAutoLoadProjectComboBoxLabelText() const;` — Gets the label text for the autoload project combo box
- L131 _private prototype_ `FReply OnInternetConnectionRetried();` — Executed when clicking on the Reconnect button when no internet connection is detected
- L134 _private prototype_ `bool HasAlreadyLatestEngineProject() const;` — Whether the current user already created project with this Engine version
- L137 _private prototype_ `void StartInternetConnectionTickCheck();` — Create and bind a function to check for internet connection from the TimerManager
- L140 _private prototype_ `void StopInternetConnectionTickCheck();` — Unbind the function to check for internet connection from the TimerManager
- L143 _private prototype_ `void RegisterOnDestructedAnalyticEvent();` — Register an analytic event when the HomeScreen is destroyed
- L147 _private member_ `static FDelayedAutoRegisterHelper LoadStartupComboButtonRegistration;` — Registers the LoadStartup ComboButton Menu
- L151 _private member_ `EMainSectionMenu MainHomeSelection = EMainSectionMenu::Home;` — Currently selected main home section
- L154 _private member_ `TSharedPtr<SCheckBox> HomeCheckBox;` — Main section checkboxes
- L155 _private member_ `TSharedPtr<SCheckBox> NewsCheckBox;`
- L156 _private member_ `TSharedPtr<SCheckBox> GettingStartedCheckBox;`
- L157 _private member_ `TSharedPtr<SCheckBox> SampleProjectsCheckBox;`
- L160 _private member_ `FDelegateHandle OnTabForegroundedHandle;` — Handle holding the OnTabForegrounded callback
- L163 _private member_ `TSharedPtr<FHttpRetrySystem::FManager> HttpRetryManager;` — Http retry system used to check Internet connection
- L164 _private member_ `TSharedPtr<FHttpRetrySystem::FRequest> HttpRetryRequest;`
- L167 _private member_ `TSharedPtr<SComboButton> AutoLoadProjectComboBox;` — Combo box for autoload project selection
- L170 _private member_ `TWeakPtr<SWidget> ComboButtonMenuWeak;` — Current combo button menu
- L173 _private member_ `TSharedPtr<SVerticalBox> ResourceAndCommunityVerticalBox;` — VerticalBox holding the ResourceAndCommunity buttons
- L176 _private member_ `FTimerHandle CheckInternetConnectionTimerHandle;` — Timer handle for checking internet connection
- L179 _private member_ `FString CurrentSelectedProjectPath;` — Path of the currently selected project
- L182 _private member_ `bool bIsConnected = true;` — Whether the system is connected to the internet
- L185 _private member_ `bool bIsRequestFinished = true;` — Whether the last request has finished
- L188 _private member_ `bool bHasProjectsOnMachine = false;` — Whether the current user has projects on their machine
- L191 _private member_ `int32 TimerManagerCountOnceDisconnected = 0;` — How many times we executed the function without being connected
- L194 _private member_ `int32 MaxTimerManagerCountOnceDisconnectedBeforeRetry = 5;` — Max TimerManager function execution before retrying once disconnected
- L197 _private member_ `bool bForceRetry = false;` — Whether to force a retry on the connection
- L200 _private member_ `EAutoLoadProject AutoLoadProjectComboBoxSelection;` — Selection for autoload project combo box
- L203 _private member_ `TSharedPtr<SBox> WebBrowserContainer;` — Web browser lazy-loading container
- L206 _private member_ `TSharedPtr<SWebBrowser> WebBrowser;` — Web browser widget instance
- L209 _private member_ `TStrongObjectPtr<UHomeScreenWeb> WebObject;` — Bridge object for browser navigation
- L212 _private member_ `FOnGetStartupSetting OnGetStartupSettingDelegate;` — HomeScreen start up setting getter
- L215 _private member_ `FHomeScreenSectionToLinkMap SectionLinks;` — Section x link combination

### `Source/Editor/MainFrame/Private/MainFrameLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMainFrame, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMainFrame, Log, All);`

### `Source/Editor/MainFrame/Private/MainFrameModule.h` (Private)


#### class `FEditorHomeScreenProvider`  
`class FEditorHomeScreenProvider : public IHomeScreenProvider`  
_L21-32_
- inherits: `IHomeScreenProvider`
- desc: Utility class, which hooks into the editor's home screen tab and supply it with its own settings if it is the higher priority provider
- L24 _public prototype_ `void Register();`
- L25 _public prototype_ `void UnRegister();`
- L28 _public prototype_ `virtual bool IsRequestingHomeScreenPageControl() const override;`
- L29 _public prototype_ `virtual int32 GetHomeScreenPriority() override;`
- L30 _public prototype_ `virtual FHomeScreenWidgetSettings GetHomeScreenWidgetSettings() const override;`

#### class `FProjectDialogProvider`  
`class FProjectDialogProvider : public IEditorMainFrameProvider`  
_L38-49_
- inherits: `IEditorMainFrameProvider`
- desc: Utility class, which hooks into the editor's main window startup and supplies a project dialog window if the project hasn't been set.
- L41 _public prototype_ `void Register();`
- L42 _public prototype_ `void UnRegister();`
- L45 _public prototype_ `virtual bool IsRequestingMainFrameControl() const override;`
- L46 _public prototype_ `virtual FMainFrameWindowOverrides GetDesiredWindowConfiguration() const override;`
- L47 _public prototype_ `virtual TSharedRef<SWidget> CreateMainFrameContentWidget() const override;`

#### class `FMainFrameModule`  
`class FMainFrameModule : public IMainFrameModule`  
_L54-376_
- inherits: `IMainFrameModule`
- desc: Editor main frame module
- L61 _public prototype_ `virtual void CreateDefaultMainFrame(const bool bStartImmersive, const bool bStartPIE) override;`
- L62 _public prototype_ `virtual void RecreateDefaultMainFrame(const bool bStartImmersive, const bool bStartPIE) override;`
- L63 _public prototype_ `virtual void ReconstructDefaultMainFrameContent(const bool bStartImmersive, const bool bStartPIE) override;`
- L70 _private prototype_ `virtual void CreateDefaultMainFrameAuxiliary(const bool bStartImmersive, const bool bStartPIE, const bool bIsBeingRecreated, const bool bIsJustCreatingContent = false);` — Shared code between CreateDefaultMainFrame and RecreateDefaultMainFrame @param bIsBeingRecreated False if it is being called by first time (CreateDefaultMainFrame), and true if it is being recreated (RecreateDefaultMainFrame). If recreated, it will also display @param bIsJustCreatingContent False if it is being called by first time (CreateDefaultMainFrame), and true if the content is being reconstructed (ReconstructDefaultMainFrameContent).
- L73 _public prototype_ `virtual bool IsRecreatingDefaultMainFrame() const override;`
- L74 _public prototype_ `virtual TSharedRef<SWidget> MakeMainMenu(const TSharedPtr<FTabManager>& TabManager, const FName MenuName, FToolMenuContext& ToolMenuContext) const override;`
- L77 _public prototype_ `virtual TSharedRef<SWidget> MakeDeveloperTools( const TArray<FMainFrameDeveloperTool>& AdditionalTools ) const override;`
- L79 _public function_ `virtual bool IsWindowInitialized( ) const override`
- L84 _public function_ `virtual TSharedPtr<SWindow> GetParentWindow( ) const override`
- L89 _public function_ `virtual void SetMainTab(const TSharedRef<SDockTab>& MainTab) override`
- L94 _public function_ `virtual void EnableTabClosedDelegate( ) override`
- L99 _public function_ `virtual void DisableTabClosedDelegate( ) override`
- L104 _public function_ `virtual void RequestCloseEditor( ) override`
- L118 _public prototype_ `virtual void SetLevelNameForWindowTitle( const FString& InLevelFileName ) override;`
- L120 _public function_ `virtual FString GetLoadedLevelName( ) const override`
- L125 _public function_ `virtual TSharedRef<FUICommandList>& GetMainFrameCommandBindings( ) override`
- L130 _public function_ `virtual class FMainMRUFavoritesList* GetMRUFavoritesList() const override`
- L135 _public function_ `virtual const FText GetApplicationTitle( const bool bIncludeGameName ) const override`
- L140 _public prototype_ `virtual void SetApplicationTitleOverride(const FText& NewOverriddenApplicationTitle) override;`
- L142 _public function_ `virtual void ShowAboutWindow( ) const override`
- L147 _public prototype_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameCreationFinishedEvent, FMainFrameCreationFinishedEvent);`
- L148 _public function_ `virtual FMainFrameCreationFinishedEvent& OnMainFrameCreationFinished( ) override`
- L153 _public prototype_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameSDKNotInstalled, FMainFrameSDKNotInstalled);`
- L154 _public function_ `virtual FMainFrameSDKNotInstalled& OnMainFrameSDKNotInstalled( ) override`
- L158 _public function_ `void BroadcastMainFrameSDKNotInstalled(const FString& PlatformName, const FString& DocLink) override`
- L163 _public prototype_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameRequestResource, FMainFrameRequestResource);`
- L164 _public function_ `virtual FMainFrameRequestResource& OnMainFrameRequestResource() override`
- L168 _public function_ `void BroadcastMainFrameRequestResource(const FString& Category, const FString& ResourceName) override`
- L173 _public function_ `virtual void EnableDelayedShowMainFrame() override`
- L178 _public function_ `virtual void ShowDelayedMainFrame() override`
- L189 _public function_ `virtual FDelegateHandle RegisterCanCloseEditor(const FMainFrameCanCloseEditor& InDelegate) override`
- L194 _public function_ `virtual void UnregisterCanCloseEditor(FDelegateHandle InHandle) override`
- L199 _public function_ `virtual bool ExecuteCanCloseEditorDelegates() override`
- L212 _public function_ `virtual void SetEditorSettingsDefaultSelectionOverride(FName CategoryName = FName(), FName SectionName = FName()) override`
- L218 _public function_ `virtual void GetEditorSettingsDefaultSelectionOverride(FName& OutCategoryName, FName& OutSectionName) override`
- L225 _public prototype_ `virtual void ShowProjectBrowser(bool bAllowProjectOpening, bool bAllowProjectCreate) override;` — Opens the project browser in a new window
- L228 _public function_ `virtual FDelegateHandle RegisterShowProjectBrowserOverride(const FShowProjectBrowser& InShowProjectBrowserOverride) override` — Overrides the functionality of ShowProjectBrowser with the provided delegate
- L235 _public function_ `virtual void UnregisterShowProjectBrowserOverride(FDelegateHandle InHandle) override` — Removes the override of ShowProjectBrowser if it matches the handle
- L245 _public prototype_ `virtual void StartupModule( ) override;`
- L246 _public prototype_ `virtual void ShutdownModule( ) override;`
- L248 _public function_ `virtual bool SupportsDynamicReloading( ) override`
- L253 _public prototype_ `static void HandleResizeMainFrameCommand(const TArray<FString>& Args);`
- L258 _public function_ `static FVector2D GetProjectBrowserWindowSize()` — Get the size of the project browser window
- L261 _public prototype_ `virtual TSharedRef<SWidget> CreateHomeScreenWidget(const TSharedPtr<SDockTab>& InParentTab, FHomeScreenWidgetSettings InSettings = FHomeScreenWidgetSettings()) override;` — Create the home screen widget
- L266 _private prototype_ `TSharedRef<SDockTab> SpawnHomeScreenWindow(const FSpawnTabArgs& InArgs);` — Spawns the home screen tab
- L269 _private prototype_ `void HandleLevelEditorModuleCompileStarted( bool bIsAsyncCompile );` — Handles the level editor module starting to recompile.
- L272 _private prototype_ `void OnCancelCodeCompilationClicked();` — Handles the user requesting the current compilation to be canceled
- L275 _private prototype_ `void HandleLevelEditorModuleCompileFinished( const FString& LogDump, ECompilationResult::Type CompilationResult, bool bShowLog );` — Handles the level editor module finishing to recompile.
- L278 _private prototype_ `void HandleReloadFinished( EReloadCompleteReason Reason );` — Called when Reload completes
- L281 _private prototype_ `void HandleCodeAccessorLaunched( const bool WasSuccessful );` — Handles the code accessor having finished launching its editor
- L284 _private prototype_ `void HandleCodeAccessorOpenFileFailed(const FString& Filename);` — Handle an open file operation failing
- L287 _private prototype_ `void HandleCodeAccessorLaunching( );` — Handles launching code accessor
- L290 _private function_ `void ClearDelayedShowMainFrameDelegate()` — Reset delegate
- L296 _private prototype_ `void DestroyRegularAndNonRootWindows(TArray<TSharedRef<SWindow>> InWindowsToDestroy) const;` — Destroy the given array of windows if they are regular windows and not the root one
- L299 _private prototype_ `static void RegisterHomeScreenFileMenu();` — Register HomeScreen file window menu
- L302 _private prototype_ `static void RegisterHomeScreenEditMenu();` — Register HomeScreen edit window menu
- L305 _private prototype_ `static void RegisterHomeScreenHelpMenu();` — Register HomeScreen help window menu
- L308 _private member_ `static FDelayedAutoRegisterHelper HomeScreenWindowMenuRegistration;` — Register the Window Menu for the HomeScreen tab
- L312 _private member_ `TWeakPtr<SNotificationItem> CompileNotificationPtr;` — Weak pointer to the level editor's compile notification item.
- L315 _private member_ `FString LoadedLevelName;` — Friendly name for persistently level name currently loaded.  Used for window and tab titles.
- L318 _private member_ `FText OverriddenWindowTitle;` — Override window title, or empty to not override
- L321 _private member_ `FName EditorSettingsDefaultCategoryOverride;` — Overrides the category that gets selected by default when opening editor settings
- L324 _private member_ `FName EditorSettingsDefaultSectionOverride;` — Overrides the section that gets selected by default when editor settings
- L327 _private member_ `FMainFrameCreationFinishedEvent MainFrameCreationFinishedEvent;` — Event to be called when the mainframe is fully created.
- L330 _private member_ `FMainFrameSDKNotInstalled MainFrameSDKNotInstalled;` — Event to be called when the editor tried to use a platform, but it wasn't installed
- L333 _private member_ `FMainFrameRequestResource MainFrameRequestResource;` — Event to be called to make an open-ended request for a resource from any registered listeners
- L336 _private member_ `TSharedPtr<class FMainFrameCommands> MainFrameActions;` — Commands used by main frame in menus and key bindings.
- L339 _private member_ `TSharedPtr<class FMainFrameHandler> MainFrameHandler;` — Holds the main frame handler.
- L342 _private member_ `double ModuleCompileStartTime;` — Absolute real time that we started compiling modules. Used for stats tracking.
- L345 _private member_ `class FMainMRUFavoritesList* MRUFavoritesList;` — Holds the collection of most recently used favorites.
- L348 _private member_ `TWeakPtr<class SNotificationItem> CodeAccessorNotificationPtr;` — Weak pointer to the code accessor's notification item.
- L351 _private member_ `FSimpleDelegate DelayedShowMainFrameDelegate;` — Delegate that holds a delayed call to ShowMainFrameWindow
- L354 _private member_ `TArray<FMainFrameCanCloseEditor> CanCloseEditorDelegates;` — List of delegates that are called after user requests the editor to close that can stop the close
- L357 _private member_ `bool bDelayedShowMainFrame;` — Allow delaying when to show main frame's window
- L360 _private member_ `bool bRecreatingDefaultMainFrame;` — Is recreating Default Main Frame
- L363 _private member_ `FProjectDialogProvider ProjectDialogProvider;` — Instantiation of the object responsible for spawning the editor's project dialog on startup
- L366 _private member_ `FEditorHomeScreenProvider HomeScreenProvider;` — Instantiation of the object responsible for getting the home screen settings to use if active
- L369 _private member_ `bool bIsReCreatingDefaultLayoutAsFallback = false;` — Set to true if we are in the middle of recreating the default layout because a previous load attempt failed
- L372 _private member_ `TSharedPtr<FTabManager> HomeScreenTabManager = nullptr;` — Holds the tab manager that manages the HomeScreen tab.
- L375 _private member_ `FShowProjectBrowser ShowProjectBrowserOverride;` — Stores the delegate for the override of ShowProjectBrowser, if any

#### Free symbols / members of external scopes

- L147 _delegate_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameCreationFinishedEvent, FMainFrameCreationFinishedEvent);`
- L153 _delegate_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameSDKNotInstalled, FMainFrameSDKNotInstalled);`
- L163 _delegate_ `DECLARE_DERIVED_EVENT(FMainFrameModule, IMainFrameModule::FMainFrameRequestResource, FMainFrameRequestResource);`
- L196 _function_ `CanCloseEditorDelegates.RemoveAll([InHandle](const FMainFrameCanCloseEditor& Delegate) { return Delegate.GetHandle() == InHandle; });` (scope `FMainFrameModule::UnregisterCanCloseEditor`)

### `Source/Editor/MainFrame/Private/Menus/LayoutsMenu.h` (Private)


#### class `FLayoutsMenu`  
`class FLayoutsMenu`  
_L14-48_
- desc: Static helper functions for populating the "Layouts" menu.
- L31 _public prototype_ `static FString GetLayout(const int32 InLayoutIndex, const ELayoutsType InLayoutsType);` — Static Get the full (engine, project, or user) layout file path. Helper function for LoadLayoutI, SaveLayoutI, and RemoveLayoutI. @param InLayoutIndex Index associated with the desired layout profile ini file to be read/written. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based).
- L38 _public prototype_ `static bool IsThereUserLayouts();` — Static Checks whether there are user-created layouts. @return true if there is at least a layout in the user layouts directory.
- L47 _public prototype_ `static bool IsLayoutChecked(const int32 InLayoutIndex, const ELayoutsType InLayoutsType);` — Static Checks which (engine, project, or user) layout entry should be checked. @param InLayoutIndex Index from the selected layout. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based). @return true if the menu entry should be checked.

#### enum `FLayoutsMenu::ELayoutsType`  
`enum class ELayoutsType`  
_L17-22_
- L19 _public enumerator_ `Engine`
- L20 _public enumerator_ `Project`
- L21 _public enumerator_ `User`

#### class `FLayoutsMenuLoad`  
`class FLayoutsMenuLoad`  
_L53-100_
- desc: Static load-related helper functions for populating the "Layouts" menu.
- L60 _public prototype_ `static void MakeLoadLayoutsMenu(UToolMenu* InToolMenu);` — Static It creates the layout load selection menu.
- L69 _public prototype_ `static bool CanLoadChooseLayout(const int32 InLayoutIndex, const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Checks if the load menu can choose the selected (engine, project, or user) layout to load it. @param InLayoutIndex Index from the selected layout. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based). @return true if the selected layout can be read.
- L76 _public prototype_ `static void ReloadCurrentLayout();` — Static It re-loads the current Editor UI Layout (from GEditorLayoutIni). This function is used for many of the functions of FLayoutsMenuLoad.
- L84 _public prototype_ `static void LoadLayout(const FString& InLayoutPath, bool bInSkipLayoutReload = false);` — Static Load the visual layout state of the editor from an existing layout profile ini file, given its file path. @param InLayoutPath File path associated with the desired layout profile ini file to be read/written. @param bInSkipLayoutReload Prevents FLayoutsMenuLoad::ReloadCurrentLayout() from being called after loading the specified layout profile.
- L92 _public prototype_ `static void LoadLayout(const int32 InLayoutIndex, const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Load the visual layout state of the editor from an existing (engine, project, or user-based) layout profile ini file. @param InLayoutIndex Index associated with the desired layout profile ini file to be read/written. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based).
- L99 _public prototype_ `static void ImportLayout();` — Static Import a visual layout state of the editor from a custom directory path and with a custom file name chosen by the user. It saves it into the user layout folder, and loads it.

#### class `FLayoutsMenuSave`  
`class FLayoutsMenuSave`  
_L105-150_
- desc: Static save-related helper functions for populating the "Layouts" menu.
- L112 _public prototype_ `static void MakeSaveLayoutsMenu(UToolMenu* InToolMenu);` — Static It creates the layout save selection menu.
- L121 _public prototype_ `static bool CanSaveChooseLayout(const int32 InLayoutIndex, const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Checks if the save menu can choose the selected (engine, project, or user-based) layout to modify it. @param InLayoutIndex Index from the selected layout. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based). @return true if the selected layout can be modified/removed.
- L129 _public prototype_ `static void OverrideLayout(const int32 InLayoutIndex, const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Override the visual layout state of the editor in an existing (engine, project, or user-based) layout profile ini file. @param InLayoutIndex Index associated with the desired layout profile ini file to be read/written. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based).
- L137 _public prototype_ `static void SaveLayout();` — Static Save the visual layout state of the editor (if changes to the layout have been made since the last time it was saved). If no changes has been made to the layout, the file is not updated (given that it would not be required). Any function that saves the layout (e.g., OverrideLayoutI, OverrideUserLayoutI, SaveLayoutAs, ExportLayout, etc.) should internally call this function.
- L143 _public prototype_ `static void SaveLayoutAs();` — Static Save the visual layout state of the editor with a custom file name chosen by the user.
- L149 _public prototype_ `static void ExportLayout();` — Static Export the visual layout state of the editor in a custom directory path and with a custom file name chosen by the user.

#### class `FLayoutsMenuRemove`  
`class FLayoutsMenuRemove`  
_L155-185_
- desc: Static remove-related helper functions for populating the "Layouts" menu.
- L162 _public prototype_ `static void MakeRemoveLayoutsMenu(UToolMenu* InToolMenu);` — Static It creates the layout remove selection menu.
- L170 _public prototype_ `static bool CanRemoveChooseLayout(const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Checks if the remove menu can choose the selected (engine, project, or user-based) layout to remove it. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based). @return true if the selected layout can be modified/removed.
- L178 _public prototype_ `static void RemoveLayout(const int32 InLayoutIndex, const FLayoutsMenu::ELayoutsType InLayoutsType);` — Static Remove an existing (engine, project, or user-based) layout profile ini file. @param InLayoutIndex Index associated with the desired layout profile ini file to be read/written. @param InLayoutsType ELayoutsType associated with the desired type of layout (engine, project, or user-based).
- L184 _public prototype_ `static void RemoveUserLayouts();` — Static Remove all the layout customizations created by the user.

### `Source/Editor/MainFrame/Private/Menus/MainMenu.h` (Private)


#### class `FMainMenu`  
`class FMainMenu`  
_L18-97_
- desc: Unreal editor main frame Slate widget
- L29 _public prototype_ `static TSharedRef<SWidget> MakeMainMenu( const TSharedPtr<FTabManager>& TabManager, const FName MenuName, FToolMenuContext& ToolMenuContext );` — Static: Creates a widget for the main menu bar. @param TabManager Create the workspace menu based on this tab manager. @param MenuName Identifier associated with the menu. @return ToolMenuContext Context containing state.
- L34 _public prototype_ `static void RegisterMainMenu();` — Static: Registers main menu with menu system.
- L42 _private prototype_ `static void RegisterFileMenu();` — Called to fill the file menu's content.
- L47 _private prototype_ `static void RegisterEditMenu();` — Called to fill the edit menu's content.
- L52 _private prototype_ `static void RegisterWindowMenu();` — Called to fill the app menu's content.
- L57 _private prototype_ `static void RegisterToolsMenu();` — Called to fill the app menu's content.
- L62 _private prototype_ `static void RegisterHelpMenu();` — Called to fill the help menu's content.
- L67 _private prototype_ `static void RegisterFileProjectMenu();` — Called to fill the file menu's content.
- L72 _private prototype_ `static void RegisterExitMenuItems();` — Called to fill the file menu's recent and exit content.
- L77 _private prototype_ `static void RegisterNomadMainMenu();` — Called to fill the main menu for nomad tabs (these tabs generally have a less menu options)
- L83 _private function_ `static void OpenProjectLauncher()` — `UE_DEPRECATED(5.6, "invoke the tab directly")` — Opens the legacy project launcher tab.
- L92 _private function_ `static void OpenVisualLogger()` — Opens the experimental Visual Logger tab. Remove this when it is no longer experimental.

### `Source/Editor/MainFrame/Private/Menus/RecentProjectsMenu.h` (Private)


#### class `FRecentProjectsMenu`  
`class FRecentProjectsMenu`  
_L17-46_
- desc: Static helper class for populating the "Recent Projects" menu.
- L26 _public function_ `static void MakeMenu( UToolMenu* Menu )` — Creates the menu. @param Menu	The menu being populated.

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "FRecentProjectsMenu"`

### `Source/Editor/MainFrame/Private/Menus/SaveLayoutDialog.h` (Private)


#### class `FSaveLayoutDialogParams`  
`class FSaveLayoutDialogParams`  
_L13-51_
- desc: It saves the input parameters that FSaveLayoutDialogUtils::CreateSaveLayoutAsDialogInStandaloneWindow needs and the output ones that it will generate.
- L19 _public prototype_ `FSaveLayoutDialogParams(const FString& InDefaultDirectory, const FString& InFileExtension, const TArray<FName>& LayoutNames = TArray<FName>(), const TArray<FName>& LayoutDescriptions = TArray<FName>());` — The constructor only contains the variables that FSaveLayoutDialogUtils::CreateSaveLayoutAsDialogInStandaloneWindow will need. The rest will be overriden.
- L25 _public member_ `const FString DefaultDirectory;` — The directory where the layout will be saved.
- L30 _public member_ `const FString FileExtension;` — The extension of the layout file.
- L35 _public member_ `bool bWereFilesSelected;` — Whether the user selected files (true) or cancelled/closed the window (false)
- L40 _public member_ `TArray<FString> LayoutFilePaths;` — The final full file path where the layout profile should be saved
- L45 _public member_ `TArray<FName> LayoutNames;` — The displayed layout name that will be visualized in Unreal. Its initial value will be used as default.
- L50 _public member_ `TArray<FName> LayoutDescriptions;` — The displayed layout description that will be visualized in Unreal. Its initial value will be used as default.

#### class `FSaveLayoutDialogUtils`  
`class FSaveLayoutDialogUtils`  
_L56-79_
- desc: Some convenient UI functions regarding SWidgets for saving the layout
- L62 _public prototype_ `static void SanitizeText(FString& InOutString);` — Any special character (i.e., any non-alphanumeric character) will be turned into an underscore.
- L69 _public prototype_ `static bool OverrideLayoutDialog(const FString& LayoutIniFileName);` — It will show a text asking whether you wanna override the existing UI Layout ini file. @param LayoutIniFileName The file path that might be overridden. @return True if the user agrees on overriding the file, false otherwise.
- L78 _public prototype_ `static bool CreateSaveLayoutAsDialogInStandaloneWindow(const TSharedRef<FSaveLayoutDialogParams>& InSaveLayoutDialogParams);` — Self-contained function that creates a standalone SWindow, the SSaveLayoutDialog widget, and that blocks the thread until the dialog is finished @param InSaveLayoutDialogParams The FSaveLayoutDialogParams parameters used in the construction of SSaveLayoutDialog. Looking at its values: 1) DefaultDirectory and FileExtension will only be read. 2) bWereFilesSelected and LayoutFilePaths will only be written (i.e., their initial value will be overridden). 3) LayoutNames and LayoutDescriptions will only be written, but their initial values will also be used as default.

### `Source/Editor/MainFrame/Private/Menus/SettingsMenu.h` (Private)


#### class `FSettingsMenu`  
`class FSettingsMenu`  
_L22-97_
- desc: Static helper class for populating the "Settings" menu.
- L32 _public function_ `static void MakeMenu( UToolMenu* MenuBuilder, FName SettingsContainerName )` — Creates the menu. @param MenuBuilder The builder for the menu that owns this menu. @param SettingsContainerName The name of the settings container to create the menu for.
- L93 _public function_ `static void OpenSettings( FName ContainerName, FName CategoryName, FName SectionName )` — Opens the settings tab with the specified settings section. @param ContainerName The name of the settings container to open. @param CategoryName The name of the settings category that contains the section. @param SectionName The name of the settings section to select.

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "FSettingsMenu"`
- L66 _function_ `` (scope `FSettingsMenu::MakeMenu`)

### `Source/Editor/MainFrame/Public/Interfaces/IEditorMainFrameProvider.h` (Public)


#### struct `FMainFrameWindowOverrides`  
`struct FMainFrameWindowOverrides`  
_L14-36_
- desc: Set of configuration settings for the editor's main window.
- L16 _public member_ `FText WindowTitle;`
- L19 _public member_ `TOptional<FVector2D> ScreenPosition;` — If not set, will fallback to main Editor defaults
- L20 _public member_ `TOptional<FVector2D> WindowSize;`
- L21 _public member_ `TOptional<bool> bInitiallyMaximized;`
- L23 _public member_ `EAutoCenter CenterRules = EAutoCenter::None;`
- L25 _public member_ `bool bEmbedTitleAreaContent : 1;`
- L26 _public member_ `bool bIsUserSizable : 1;`
- L27 _public member_ `bool bSupportsMaximize : 1;`
- L28 _public member_ `bool bSupportsMinimize : 1;`
- L30 _public function_ `FMainFrameWindowOverrides() : bEmbedTitleAreaContent(true) , bIsUserSizable(true) , bSupportsMaximize(true) , bSupportsMinimize(true)`

#### class `IEditorMainFrameProvider`  
`class IEditorMainFrameProvider : public IModularFeature`  
_L42-73_
- inherits: `IModularFeature`
- desc: Base feature class, which serves as a hook for external sources to override the editor's main window on startup.
- L45 _public prototype_ `virtual ~IEditorMainFrameProvider() = default;`
- L47 _public function_ `static FName GetModularFeatureName()`
- L59 _public prototype_ `virtual bool IsRequestingMainFrameControl() const = 0;` — Signals if this provider wishes to override the editor's main frame on editor startup. NOTE: When true, this will block the standard editor window from appearing (instead replacing it with the provider's widget).
- L65 _public prototype_ `virtual FMainFrameWindowOverrides GetDesiredWindowConfiguration() const = 0;` — Specifies the desired window title, dimensions, etc. -- for the main frame window (to fit the provier's widget).
- L72 _public prototype_ `virtual TSharedRef<SWidget> CreateMainFrameContentWidget() const = 0;` — Spawns a widget for slotting into the main editor window (in-place of the standard editor). @return A replacement widget for the editor's main window.

### `Source/Editor/MainFrame/Public/Interfaces/IHomeScreenProvider.h` (Public)


#### class `IHomeScreenProvider`  
`class IHomeScreenProvider : public IModularFeature`  
_L12-40_
- inherits: `IModularFeature`
- desc: Base feature class, which serves as a hook for external sources to override the editor's HomeScreen window content.
- L15 _public function_ `virtual ~IHomeScreenProvider()`
- L17 _public function_ `static FName GetModularFeatureName()`
- L26 _public prototype_ `virtual bool IsRequestingHomeScreenPageControl() const = 0;` — @return True if we want our HomeScreen settings to be used for the HomeScreen widget inside the HomeScreen tab
- L34 _public prototype_ `virtual int32 GetHomeScreenPriority() = 0;` — Less priority means that it will be ignored for higher ones. The editor default HomeScreen priority is -1 @return The priority for this HomeScreen
- L39 _public prototype_ `virtual FHomeScreenWidgetSettings GetHomeScreenWidgetSettings() const = 0;` — @return Settings to use for this HomeScreen

### `Source/Editor/MainFrame/Public/Interfaces/IMainFrameModule.h` (Public)


#### struct `FMainFrameDeveloperTool`  
`struct FMainFrameDeveloperTool`  
_L21-29_
- desc: Data needed to display a Developer tools in the status bar.
- L24 _public member_ `TAttribute<EVisibility> Visibility;` — Visiblility of the developer tool.
- L26 _public member_ `TAttribute<FText> Label;` — Label of the developer tool.
- L28 _public member_ `TAttribute<FText> Value;` — Value of the developer tool.

#### class `IMainFrameModule`  
`class IMainFrameModule : public IModuleInterface`  
_L36-296_
- inherits: `IModuleInterface`
- desc: Interface for main frame modules.
- L49 _public prototype_ `virtual TSharedRef<SWidget> CreateHomeScreenWidget(const TSharedPtr<SDockTab>& InParentTab, FHomeScreenWidgetSettings InSettings = FHomeScreenWidgetSettings()) = 0;` — Create the HomeScreen widget, will use the default settings if no settings are provided and return the newly created HomeScreen Should only be used when using the IEditorMainFrameProvider if you wish to use a HomeScreen widget with different settings @param InParentTab OwnerTab of the HomeScreen, needed when the HomeScreen is created as a Tab to avoid MAC to render the WebPage when switching tabs @param InSettings HomeScreenSettings to use to create the current HomeScreen @return Return the newly created HomeScreen widget
- L57 _public prototype_ `virtual void CreateDefaultMainFrame( const bool bStartImmersive, const bool bStartPIE ) = 0;` — Creates the default editor main frame @param bStartImmersive True to force a main frame viewport into immersive mode @param bStartPIE True to start a PIE session right away
- L66 _public prototype_ `virtual void RecreateDefaultMainFrame(const bool bStartImmersive, const bool bStartPIE) = 0;` — Recreates the default editor main frame. I.e., if CreateDefaultMainFrame or RecreateDefaultMainFrame were already called, it would clean the previous default main frame and create it again. @param bStartImmersive True to force a main frame viewport into immersive mode @param bStartPIE True to start a PIE session right away
- L74 _public prototype_ `virtual void ReconstructDefaultMainFrameContent(const bool bStartImmersive, const bool bStartPIE) = 0;` — Recreates the default editor main frame content without destroying the old one. @param bStartImmersive True to force a main frame viewport into immersive mode @param bStartPIE True to start a PIE session right away
- L79 _public prototype_ `virtual bool IsRecreatingDefaultMainFrame() const = 0;` — Returns true if the Default Main Frame is being recreated.
- L91 _public prototype_ `virtual TSharedRef<SWidget> MakeMainMenu( const TSharedPtr<FTabManager>& TabManager, const FName MenuName, FToolMenuContext& ToolMenuContext ) const = 0;` — Generates a menu that includes application global commands, such as "Save All", "Exit", etc.  If you're building a menu for your tab, you should call this function to create your menu, passing in an extender object to add your tab-specific menu items! @param	TabManager	The tab manager for the tab you're creating the menu for.  This is needed so we can populate the layout menus correctly. @param	Extender	Extender object used to customize the main frame menu @return	The newly-created menu widget
- L110 _public prototype_ `virtual TSharedRef<SWidget> MakeDeveloperTools( const TArray<FMainFrameDeveloperTool>& AdditionalTools ) const = 0;` — Generates a menu for status and developer @param	AdditionalTools	Additional developer tools that would be added to the main frame menu @return	The newly-created menu widget
- L117 _public prototype_ `virtual bool IsWindowInitialized() const = 0;` — Checks to see if the main frame window is currently initialized @return	True if initialized, otherwise false
- L124 _public prototype_ `virtual TSharedPtr<SWindow> GetParentWindow( ) const = 0;` — Gets the window the mainframe lives in. @return The window widget.
- L131 _public prototype_ `virtual void SetMainTab( const TSharedRef<SDockTab>& MainTab ) = 0;` — Sets the reference to the main tab. @param MainTab - The main tab.
- L136 _public prototype_ `virtual void EnableTabClosedDelegate( ) = 0;` — Enables the delegate responsible for shutting down the editor when the main tab is closed.
- L141 _public prototype_ `virtual void DisableTabClosedDelegate( ) = 0;` — Disables the delegate responsible for shutting down the editor when the main tab is closed.
- L147 _public prototype_ `virtual void RequestCloseEditor( ) = 0;` — Requests that the editor be closed In some cases the editor may not be closed (like if a user cancels a save dialog)
- L154 _public prototype_ `virtual void SetLevelNameForWindowTitle(const FString& InLevelFileName) = 0;` — Updates the mainframe title on the Slate window and the native OS window underneath @param InLevelFileName  Full level filename from which the base name will be stripped and used to make the window title
- L161 _public prototype_ `virtual void SetApplicationTitleOverride(const FText& NewOverriddenApplicationTitle) = 0;` — Overrides the title of the application that's displayed in the title bar area and other locations @param	NewOverriddenApplicationTitle	The text to be displayed in the window title, or empty to use the application's default text
- L168 _public prototype_ `virtual FString GetLoadedLevelName() const = 0;` — Returns a friendly string name for the currently loaded persistent level. @return Name of the loaded level.
- L170 _public prototype_ `virtual TSharedRef<FUICommandList>& GetMainFrameCommandBindings( ) = 0;`
- L177 _public prototype_ `virtual class FMainMRUFavoritesList* GetMRUFavoritesList() const = 0;` — Gets the MRU/Favorites list @return	MRU/Favorites list
- L186 _public prototype_ `virtual const FText GetApplicationTitle( const bool bIncludeGameName ) const = 0;` — Gets the title string for the application, optionally including the current game name as part of the title @param	bIncludeGameName	True if the game name should be included as part of the returned title string @return	Returns the title of the application, to be displayed in tabs or window titles
- L191 _public prototype_ `virtual void ShowAboutWindow( ) const = 0;` — Shows the 'About UnrealEd' window.
- L196 _public prototype_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameCreationFinishedEvent, TSharedPtr<SWindow>, bool);` — Delegate for binding functions to be called when the mainframe finishes up getting created.
- L197 _public prototype_ `virtual FMainFrameCreationFinishedEvent& OnMainFrameCreationFinished( ) = 0;`
- L202 _public prototype_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameSDKNotInstalled, const FString&, const FString&);` — Delegate for when a platform SDK isn't installed corrected (takes the platform name and the documentation link to show)
- L203 _public prototype_ `virtual FMainFrameSDKNotInstalled& OnMainFrameSDKNotInstalled( ) = 0;`
- L204 _public prototype_ `virtual void BroadcastMainFrameSDKNotInstalled(const FString& PlatformName, const FString& DocLink) = 0;`
- L209 _public prototype_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameRequestResource, const FString&, const FString&);` — Delegate for making an open-ended request for a resource or link.
- L210 _public prototype_ `virtual FMainFrameRequestResource& OnMainFrameRequestResource() = 0;`
- L211 _public prototype_ `virtual void BroadcastMainFrameRequestResource(const FString& Category, const FString& ResourceName) = 0;`
- L216 _public prototype_ `virtual void EnableDelayedShowMainFrame() = 0;` — Enable external control of when main frame is shown
- L221 _public prototype_ `virtual void ShowDelayedMainFrame() = 0;` — Show main frame now if it was delayed and not shown yet
- L226 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FMainFrameCanCloseEditor);` — Delegate for determining if the editor can be closed
- L231 _public prototype_ `virtual FDelegateHandle RegisterCanCloseEditor(const FMainFrameCanCloseEditor& InDelegate) = 0;` — Register a new callback for determining if the editor can be closed
- L236 _public prototype_ `virtual void UnregisterCanCloseEditor(FDelegateHandle InHandle) = 0;` — Unregister a callback for determining if the editor can be closed
- L238 _public prototype_ `virtual bool ExecuteCanCloseEditorDelegates() = 0;`
- L244 _public prototype_ `virtual void SetEditorSettingsDefaultSelectionOverride(FName CategoryName = FName(), FName SectionName = FName()) = 0;` — Overrides the section that gets selected by default when opening editor settings @note Call with default parameters to clear the override
- L250 _public prototype_ `virtual void GetEditorSettingsDefaultSelectionOverride(FName& OutCategoryName, FName& OutSectionName) = 0;` — Gets the override for the section that gets selected by default when opening editor settings @note Returns None if there's no override
- L255 _public prototype_ `virtual void ShowProjectBrowser(bool bAllowProjectOpening, bool bAllowProjectCreate) = 0;` — Opens the project browser in a new window.
- L260 _public prototype_ `virtual FDelegateHandle RegisterShowProjectBrowserOverride(const FShowProjectBrowser& InShowProjectBrowserOverride) = 0;` — Overrides the functionality of ShowProjectBrowser with the provided delegate.
- L265 _public prototype_ `virtual void UnregisterShowProjectBrowserOverride(FDelegateHandle InHandle) = 0;` — Removes the override of ShowProjectBrowser if it matches the handle.
- L270 _public function_ `static FText& GetHomeScreenTabLabel()` — Return the HomeScreen tab label
- L284 _public function_ `static IMainFrameModule& Get( )` — Gets a reference to the search module instance. @todo gmp: better implementation using dependency injection. @return A reference to the MainFrame module.
- L295 _public prototype_ `virtual ~IMainFrameModule( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L31 _typedef_ `using FShowProjectBrowser = TDelegate<void(bool bAllowProjectOpening, bool bAllowProjectCreate)>;`
- L196 _delegate_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameCreationFinishedEvent, TSharedPtr<SWindow>, bool);` — Delegate for binding functions to be called when the mainframe finishes up getting created.
- L202 _delegate_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameSDKNotInstalled, const FString&, const FString&);` — Delegate for when a platform SDK isn't installed corrected (takes the platform name and the documentation link to show)
- L209 _delegate_ `DECLARE_EVENT_TwoParams(IMainFrameModule, FMainFrameRequestResource, const FString&, const FString&);` — Delegate for making an open-ended request for a resource or link.
- L226 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FMainFrameCanCloseEditor);` — Delegate for determining if the editor can be closed

### `Source/Editor/MainFrame/Public/MainFrame.h` (Public)
_(no declarations extracted)_

### `Source/Editor/MainFrame/Public/Settings/HomeScreenCommon.h` (Public)


#### enum `EMainSectionMenu`  
`enum class EMainSectionMenu : uint8`  
_L14-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `Home`
- L18 _public enumerator_ `News`
- L19 _public enumerator_ `GettingStarted`
- L20 _public enumerator_ `SampleProjects`

#### enum `EAutoLoadProject`  
`enum class EAutoLoadProject : uint8`  
_L24-29_
- reflection: `UENUM()`
- L26 _public enumerator_ `HomeScreen UMETA(DisplayName = "Home Panel")`
- L27 _public enumerator_ `LastProject UMETA(DisplayName = "Most Recent Project")`
- L28 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FHomeScreenSectionLink`  
`struct FHomeScreenSectionLink`  
_L38-43_
- desc: Struct containing information on the MainSections in the HomeScreen
- L40 _public member_ `FString BeforeLocaleURL;`
- L41 _public member_ `FString AfterLocaleURL;`
- L42 _public member_ `FString AfterLocaleNoProjectURL;`

#### struct `FHomeScreenResourceCommunityEntry`  
`struct FHomeScreenResourceCommunityEntry`  
_L50-55_
- desc: Struct containing information of ResourceAndCommunity section entries in the HomeScreen
- L52 _public member_ `TAttribute<FString> Link;`
- L53 _public member_ `FText DisplayName;`
- L54 _public member_ `FName IconBrushName;`

#### struct `FHomeScreenLoadAtStartupSetting`  
`struct FHomeScreenLoadAtStartupSetting`  
_L57-76_
- L60 _public prototype_ `FHomeScreenLoadAtStartupSetting() = default;`
- L61 _public function_ `FHomeScreenLoadAtStartupSetting(FOnSetLoadAtStartup InOnSetLoadAtStartup, FOnGetLoadAtStartup InOnGetLoadAtStartup) : OnSetLoadAtStartupDelegate(InOnSetLoadAtStartup) , OnGetLoadAtStartupDelegate(InOnGetLoadAtStartup)`
- L68 _public function_ `FOnLoadAtStartupChanged& OnLoadAtStartupChanged()`
- L69 _public function_ `void SetOnLoadAtStartup(bool InAutoLoadOption) const`
- L70 _public function_ `bool GetOnLoadAtStartup() const`
- L73 _private member_ `FOnLoadAtStartupChanged OnLoadAtStartupChangedDelegate;`
- L74 _private member_ `FOnSetLoadAtStartup OnSetLoadAtStartupDelegate;`
- L75 _private member_ `FOnGetLoadAtStartup OnGetLoadAtStartupDelegate;`

#### struct `FHomeScreenWidgetSettings`  
`struct FHomeScreenWidgetSettings`  
_L81-121_
- desc: Setting used to create the HomeScreen, if leaved empty the defaults are used instead
- L83 _public function_ `FHomeScreenWidgetSettings() : bAlwaysShowRecentList(false) , RecentProjectListWidget(SNullWidget::NullWidget) , UnrealLogoBrush(nullptr) , OnGetStartupSetting()`
- L95 _public member_ `FHomeScreenSectionToLinkMap SectionLinks;` — Section x Link connection, if leaved empty it will use the UE default section x links. If at least 1 is populated it will use this instead, every missing section are skipped from being created in this case
- L100 _public member_ `TArray<FHomeScreenResourceCommunityEntry> ResourcesEntries;` — Additional Resource entry to add to the default ones
- L105 _public member_ `bool bAlwaysShowRecentList;` — Whether the recent project list should always be displayed without checking for their presence.
- L110 _public member_ `TSharedRef<SWidget> RecentProjectListWidget;` — Widget displaying the recent project list.
- L115 _public member_ `const FSlateBrush* UnrealLogoBrush;` — Brush representing the icon for the Unreal Logo.
- L120 _public member_ `FOnGetStartupSetting OnGetStartupSetting;` — Used to grab the StartupSetting logic to use

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadAtStartupChanged, EAutoLoadProject) DECLARE_DELEGATE_OneParam(FOnSetLoadAtStartup, bool) DECLARE_DELEGATE_RetVal(bool, FOnGetLoadAtStartup) struct FHomeScreenSectionLink { FString BeforeLocaleURL; FString AfterLocaleURL; FString AfterLocaleNoProjectURL; };`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetLoadAtStartup, bool) DECLARE_DELEGATE_RetVal(bool, FOnGetLoadAtStartup) struct FHomeScreenSectionLink { FString BeforeLocaleURL; FString AfterLocaleURL; FString AfterLocaleNoProjectURL; };`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetLoadAtStartup) struct FHomeScreenSectionLink { FString BeforeLocaleURL; FString AfterLocaleURL; FString AfterLocaleNoProjectURL; };`
- L45 _typedef_ `using FHomeScreenSectionToLinkMap = TMap<EMainSectionMenu, FHomeScreenSectionLink>;`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal(FHomeScreenLoadAtStartupSetting&, FOnGetStartupSetting) struct FHomeScreenWidgetSettings { FHomeScreenWidgetSettings() : bAlwaysShowRecentList(false) , RecentProjectListWidget(SNullWidget::NullWidget) , UnrealLogoBrush(nullptr) , OnGetStartupSetting() { } FHomeScreenSectionToLinkMap SectionLinks; TArray<FHomeScreenResourceCommunityEntry> ResourcesEntries; bool bAlwaysShowRecentList; TSharedRef<SWidget> RecentProjectListWidget; const FSlateBrush* UnrealLogoBrush; /**`

### `Source/Editor/MainFrame/Public/Settings/HomeScreenSettings.h` (Public)


#### class `UHomeScreenSettings`  
`class UHomeScreenSettings : public UObject`  
_L11-39_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings)`
- inherits: `UObject`
- L16 _public prototype_ `UHomeScreenSettings();`
- L20 _public member_ `EAutoLoadProject LoadAtStartup = EAutoLoadProject::HomeScreen;` — `UPROPERTY()`
- L23 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L24 _public prototype_ `virtual void PostInitProperties() override;`
- L27 _public function_ `FOnLoadAtStartupChanged& OnLoadAtStartupChanged()` — `UE_DEPRECATED(5.8, "Use the GetLoadAtStartupSetting instead")`
- L29 _public prototype_ `FHomeScreenLoadAtStartupSetting& GetLoadAtStartupSetting();`
- L32 _private prototype_ `void OnMostRecentProjectEditorSettingChanged(bool bInAutoLoad);`
- L33 _private prototype_ `void SetLoadAtStartupChanged(bool bInAutoLoad);`
- L34 _private prototype_ `bool GetLoadAtStartupChanged() const;`
- L37 _private member_ `FHomeScreenLoadAtStartupSetting HomeScreenLoadAtStartupSetting;`
- L38 _private member_ `FOnLoadAtStartupChanged OnLoadAtStartupChangedDelegate;`
