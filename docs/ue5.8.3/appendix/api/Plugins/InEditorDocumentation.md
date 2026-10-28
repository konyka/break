# Plugins / InEditorDocumentation

- module root: `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation`
- headers: 4; symbols: 56
- symbol kinds: class=4, delegate=1, function=1, member=21, prototype=28, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Blutility, CoreUObject, EditorFramework, Engine, HTTP, InputCore, Json, JsonUtilities, LevelEditor, Projects, Slate, SlateCore, ToolMenus, UMG, UnrealEd, WebBrowser
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation/Public/CommandsStyle.h` (Public)


#### class `FCommandsStyle`  
`class FCommandsStyle`  
_L10-33_
- L14 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L22 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L24 _public prototype_ `static FName GetStyleSetName();`
- L28 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L32 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

### `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation/Public/DocumentationCommands.h` (Public)


#### class `FDocumentationCommands`  
`class FDocumentationCommands : public TCommands<FDocumentationCommands>`  
_L12-26_
- inherits: `TCommands<FDocumentationCommands>`
- L15 _public function_ `FDocumentationCommands() : TCommands<FDocumentationCommands>(TEXT("InEditorDocumentation"), NSLOCTEXT("Contexts", "InEditorDocumentation", "InEditorDocumentation Plugin"), NAME_None, FCommandsStyle::GetStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<...> implementation
- L24 _public member_ `TSharedPtr<FUICommandInfo> OpenTutorial;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> OpenSearch;`

### `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation/Public/InEditorDocumentation.h` (Public)


#### class `FInEditorDocumentationModule`  
`class FInEditorDocumentationModule : public IModuleInterface`  
_L24-164_
- inherits: `IModuleInterface`
- L29 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _private member_ `ISettingsSectionPtr ModuleConfigSettings;` — Configuration Section Settings
- L37 _private member_ `const FName SettingsContainerName = "Ed`
- L38 _private member_ `const FName SettingsCategoryName = "Pl`
- L39 _private member_ `const FName SettingsSectionName = "In`
- L40 _private member_ `const FText DisplayName = FText::FromString("In-`
- L41 _private member_ `const FText Description = FText::FromString("Set`
- L44 _private member_ `TWeakPtr<SNotificationItem> TutorialToast;` — Toast notification
- L47 _private member_ `bool bUserDismissedTutorialNotification = false;` — Has the user manually dismissed the tutorial toast?
- L50 _private member_ `bool bShowSearch = true;` — Is Edc search enabled?
- L53 _private member_ `TSharedPtr<FUICommandList> PluginCommands;` — Ui commands
- L56 _private member_ `TSharedPtr<SWebBrowser> TutorialWebBrowser;` — Web browser
- L59 _private member_ `TSharedPtr<SWebBrowser> SearchWebBrowser;` — Search web browser
- L62 _private member_ `TSharedPtr<FJsonObject> SearchResults;` — Edc Search results
- L65 _private member_ `FToolMenuEntry* SearchEntry;` — Search entry in the Level Editor menu
- L70 _private prototype_ `void OnToggleTutorialClicked();` — <summary> Callback - Invoked as a response to UI_COMMAND(OpenDocumentationWindow,...) </summary>
- L75 _private prototype_ `void OnSearchClicked();` — <summary> Callback - Invoked as a response to UI_COMMAND(SearchEdc,...) </summary>
- L81 _private prototype_ `static TObjectPtr<AActor> GetFirstSelectedActor();` — <summary> Get an array of all actors currently selected in the Unreal Editor viewport </summary> <returns></returns>
- L86 _private prototype_ `void RegisterMenus();` — <summary> Register UI Menus </summary>
- L91 _private prototype_ `void ExtendLevelEditorLayout();` — <summary> Extend the level editor layout </summary>
- L97 _private prototype_ `FString GetTutorialUrl();` — <summary> Get the url to navigate to </summary> <returns></returns>
- L103 _private prototype_ `FString ConstructSearchUrl();` — <summary> Construct the url for the search edc </summary> <returns></returns>
- L110 _private prototype_ `TSharedRef<SDockTab> OnSpawnTutorialTab(const class FSpawnTabArgs& SpawnTabArgs);` — <summary> Callback - Invoked as a response to TryInvokeTab() for OpenDocumentationWindow </summary> <param name="SpawnTabArgs"></param> <returns></returns>
- L117 _private prototype_ `TSharedRef<SDockTab> OnSpawnSearchTab(const class FSpawnTabArgs& SpawnTabArgs);` — <summary> Callback - Invoked as a response to TryInvokeTab() for SearchEdc </summary> <param name="SpawnTabArgs"></param> <returns></returns>
- L123 _private prototype_ `void HandleTutorialTabClosed(TSharedRef<SDockTab> ClosedTab);` — <summary> Callback - Invoked as a response to RequestCloseTab() for OpenDocumentationWindow </summary> <param name="ClosedTab"></param>
- L128 _private prototype_ `void HandleLoadErrorContent();` — <summary> Callback - Invoked as a response to SWebBrowser::OnLoadError </summary>
- L136 _private prototype_ `bool HandleEdcNavigation(const FString& NavUrl, const struct FWebNavigationRequest& Nav);` — <summary> Callback - Invoked as a response to SWebBrowser::OnBeforeNavigation </summary> <param name="NavUrl"></param> <param name="Nav"></param> <returns></returns>
- L141 _private prototype_ `void HandleTutorialLoadCompleted();` — <summary> Callback - Invoked as a response to SWebBrowser::OnLoadCompleted for the TutorialWebBrowser </summary>
- L146 _private prototype_ `void HandleSearchLoadCompleted();` — <summary> Callback - Invoked as a response to SWebBrowser::OnLoadCompleted for the SearchWebBrowser </summary>
- L151 _private prototype_ `void DisplayTutorialToastNotification();` — <summary> Show the toast notification </summary>
- L157 _private prototype_ `void HandleTutorialToastCheckboxStateChanged(ECheckBoxState NewState);` — <summary> Callback - Invoked as a response to Taost notification checkbox state changed </summary> <param name="NewState"></param>
- L163 _private prototype_ `bool HandleSettingsModified();` — <summary> Callback - Invoked as a response to module settings modified </summary> <returns></returns>

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDocumentation, Display, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDocumentation, Display, All);`
- L22 _typedef_ `typedef TSharedPtr<ISettingsSection> ISettingsSectionPtr;`

### `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation/Public/InEditorDocumentationSettings.h` (Public)


#### class `UInEditorDocumentationSettings`  
`class UInEditorDocumentationSettings : public UObject`  
_L13-39_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, DefaultConfig)`
- inherits: `UObject`
- L25 _public member_ `FString TutorialUrl = TEXT("htt` — `UPROPERTY(EditAnywhere, Config, Category = "Tutorial", meta=(ToolTip="Tutorial url to open if the tutorial button is clicked"))` — dev.epicgames.com/documentation/unreal-engine/stack-o-bot-sample-game-in-unreal-engine");
- L28 _public member_ `bool bEnableEdcSearch = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Search (Experimental)", meta =(ToolTip="Enable Edc search for actors selected in the viewport"))`
- L31 _public member_ `FString EdcSearchApiEndpoint = TEXT("htt` — `UPROPERTY(VisibleAnywhere, Config, Category = "Search (Experimental)", meta=(ToolTip="Api endpoint to search the edc for information about selected actor"))` — dev.epicgames.com/community/api/search/index.json");
- L34 _public member_ `TMap<FString, FString> DocumentationPages;` — `UPROPERTY(EditAnywhere, Config, Category = "Search (Experimental)", meta=(ToolTip="List of predefined documentation page given an actor"))`
- L37 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
