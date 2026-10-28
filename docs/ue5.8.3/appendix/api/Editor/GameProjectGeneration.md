# Editor / GameProjectGeneration

- module root: `Source/Editor/GameProjectGeneration`
- headers: 15; symbols: 656
- symbol kinds: class=14, delegate=7, enum=9, enumerator=34, function=55, macro=3, member=182, prototype=337, struct=12, typedef=3
- DynamicallyLoadedModuleNames: AssetRegistry, ContentBrowser, Documentation, MainFrame
- PrivateDependencyModuleNames: AddContentDialog, Analytics, AppFramework, ApplicationCore, AssetTools, AudioMixer, AudioMixerCore, ClassViewer, ContentBrowserData, Core, CoreUObject, DesktopPlatform, EditorFramework, EditorSubsystem, EditorWidgets, Engine, EngineSettings, InputCore, LauncherPlatform, Projects, RenderCore, Slate, SlateCore, SourceControl, TargetPlatform, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, ContentBrowser, LiveCoding, MainFrame
- PublicDependencyModuleNames: HardwareTargeting

### `Source/Editor/GameProjectGeneration/Classes/DefaultTemplateProjectDefs.h` (Public)


#### class `UDefaultTemplateProjectDefs`  
`class UDefaultTemplateProjectDefs : public UTemplateProjectDefs`  
_L19-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTemplateProjectDefs`
- L23 _private prototype_ `virtual bool GeneratesCode(const FString& ProjectTemplatePath) const override;`
- L25 _private prototype_ `virtual bool IsClassRename(const FString& DestFilename, const FString& SrcFilename, const FString& FileExtension) const override;`
- L27 _private prototype_ `virtual void AddConfigValues(TArray<FTemplateConfigValue>& ConfigValuesToSet, const FString& TemplateName, const FString& ProjectName, bool bShouldGenerateCode) const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPROJECTGENERATION_API`

### `Source/Editor/GameProjectGeneration/Classes/TemplateProjectDefs.h` (Public)


#### struct `FTemplateConfigValue`  
`struct FTemplateConfigValue`  
_L21-30_
- desc: does not require reflection exposure
- L23 _public member_ `FString ConfigFile;`
- L24 _public member_ `FString ConfigSection;`
- L25 _public member_ `FString ConfigKey;`
- L26 _public member_ `FString ConfigValue;`
- L27 _public member_ `bool bShouldReplaceExistingValue;`
- L29 _public prototype_ `FTemplateConfigValue(const FString& InFile, const FString& InSection, const FString& InKey, const FString& InValue, bool InShouldReplaceExistingValue);`

#### struct `FTemplateReplacement`  
`struct FTemplateReplacement`  
_L33-48_
- reflection: `USTRUCT()`
- L38 _public member_ `TArray<FString> Extensions;` — `UPROPERTY()`
- L41 _public member_ `FString From;` — `UPROPERTY()`
- L44 _public member_ `FString To;` — `UPROPERTY()`
- L47 _public member_ `bool bCaseSensitive{false};` — `UPROPERTY()`

#### struct `FTemplateFolderRename`  
`struct FTemplateFolderRename`  
_L51-60_
- reflection: `USTRUCT()`
- L56 _public member_ `FString From;` — `UPROPERTY()`
- L59 _public member_ `FString To;` — `UPROPERTY()`

#### struct `FLocalizedTemplateString`  
`struct FLocalizedTemplateString`  
_L63-75_
- reflection: `USTRUCT()`
- L68 _public member_ `FString Language;` — `UPROPERTY()`
- L71 _public member_ `FString Text;` — `UPROPERTY()`
- L74 _public prototype_ `static FText GetLocalizedText(const TArray<FLocalizedTemplateString>& LocalizedStrings);` — Find a text value for the current locale (or fallback to English) from the given array of localized strings.

#### struct `FTemplateVariant`  
`struct FTemplateVariant`  
_L78-100_
- reflection: `USTRUCT()`
- L83 _public member_ `FName Name;` — `UPROPERTY(config)`
- L86 _public member_ `TArray<FLocalizedTemplateString> LocalizedDisplayNames;` — `UPROPERTY(config)`
- L89 _public member_ `TArray<FLocalizedTemplateString> LocalizedDescriptions;` — `UPROPERTY(config)`
- L93 _public member_ `TArray<FFeaturePackLevelSet> SharedContentPacks;` — `UPROPERTY(config)` — Shared feature packs. The files in these packs listed in these structures marked as 'additionalfiles' will be copied on project generation
- L96 _public prototype_ `FText GetDisplayNameText() const;` — Returns the display name for the current culture, or English if the current culture has no translation
- L99 _public prototype_ `FText GetLocalizedDescription() const;` — Returns the display name for the current culture, or English if the current culture has no translation

#### enum `ETemplateSetting`  
`enum class ETemplateSetting`  
_L103-113_
- reflection: `UENUM()`
- L105 _public enumerator_ `Languages`
- L106 _public enumerator_ `HardwareTarget`
- L107 _public enumerator_ `GraphicsPreset`
- L108 _public enumerator_ `StarterContent UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")`
- L109 _public enumerator_ `XR`
- L110 _public enumerator_ `Raytracing_DEPRECATED`
- L111 _public enumerator_ `Variants`
- L112 _public enumerator_ `All`

#### class `UTemplateProjectDefs`  
`class UTemplateProjectDefs : public UObject`  
_L116-225_
- reflection: `UCLASS(abstract,config=TemplateDefs,MinimalAPI)`
- inherits: `UObject`
- L122 _public member_ `TArray<FLocalizedTemplateString> LocalizedDisplayNames;` — `UPROPERTY(config)`
- L125 _public member_ `TArray<FLocalizedTemplateString> LocalizedDescriptions;` — `UPROPERTY(config)`
- L128 _public member_ `TArray<FString> FoldersToIgnore;` — `UPROPERTY(config)`
- L131 _public member_ `TArray<FString> FilesToIgnore;` — `UPROPERTY(config)`
- L134 _public member_ `TArray<FTemplateFolderRename> FolderRenames;` — `UPROPERTY(config)`
- L137 _public member_ `TArray<FTemplateReplacement> FilenameReplacements;` — `UPROPERTY(config)`
- L140 _public member_ `TArray<FTemplateReplacement> ReplacementsInFiles;` — `UPROPERTY(config)`
- L143 _public member_ `FString SortKey;` — `UPROPERTY(config)`
- L146 _public member_ `TArray<FName> Categories;` — `UPROPERTY(config)`
- L149 _public member_ `FString ClassTypes;` — `UPROPERTY(config)`
- L152 _public member_ `FString AssetTypes;` — `UPROPERTY(config)`
- L156 _public member_ `bool bAllowProjectCreation;` — `UPROPERTY(config)` — Should we allow creation of a project from this template. If this is false, the template is treated as a feature pack.
- L160 _public member_ `bool bIsEnterprise;` — `UPROPERTY(config)` — Is this an enterprise template?
- L164 _public member_ `bool bIsBlank;` — `UPROPERTY(config)` — Is this a blank template? Determines whether we can override the default map when creating the project.
- L168 _public member_ `bool bThumbnailAsIcon;` — `UPROPERTY(config)` — Is there a rendered thumbnail that should be treated as the project template icon. If this is true the thumbnail takes up the full tile size rather than a 64x64 icon
- L172 _public member_ `TArray<ETemplateSetting> HiddenSettings;` — `UPROPERTY(config)` — Optional list of settings to hide. If none are specified, then all settings are shown.
- L176 _public member_ `TArray<FString> PacksToInclude;` — `UPROPERTY(config)` — Optional list of feature packs to include
- L180 _public member_ `EFeaturePackDetailLevel EditDetailLevelPreference;` — `UPROPERTY(config)` — What detail level to edit when editing shared template resources
- L184 _public member_ `TArray<FFeaturePackLevelSet> SharedContentPacks;` — `UPROPERTY(config)` — Shared feature packs. The files in these packs listed in these structures marked as 'additionalfiles' will be copied on project generation
- L189 _public member_ `FString StarterContent_DEPRECATED;` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Ability to add Starter Content has been removed"))`
- L194 _public member_ `TArray<FTemplateVariant> Variants;` — `UPROPERTY(config)` — List of variants for this template. Using an Array instead of a Map purely for ease of writing the ini file (allowing one variant per line)
- L197 _public prototype_ `void FixupStrings(const FString& TemplateName, const FString& ProjectName);` — Fixes up all strings in this definitions object to replace \%TEMPLATENAME\% with the supplied template name and \%PROJECTNAME\% with the supplied project name
- L200 _public prototype_ `FText GetDisplayNameText();` — Returns the display name for the current culture, or English if the current culture has no translation
- L203 _public prototype_ `FText GetLocalizedDescription();` — Returns the display name for the current culture, or English if the current culture has no translation
- L206 _public prototype_ `const FTemplateVariant* FindVariant(FName VariantName) const;` — Finds a Variant with the given name, returns null if not found
- L209 _public function_ `virtual bool GeneratesCode(const FString& ProjectTemplatePath) const PURE_VIRTUAL(UTemplateProjectDefs::GeneratesCode, return false;) virtual bool IsClassRename(const FString& DestFilename, const FString& SrcFilename, const FString& FileExtension) const` — Does this template generate C++ source?
- L215 _public function_ `virtual void AddConfigValues(TArray<FTemplateConfigValue>& ConfigValuesToSet, const FString& TemplateName, const FString& ProjectName, bool bShouldGenerateCode) const` — Callback for adding config values
- L218 _public function_ `virtual bool PreGenerateProject(const FString& DestFolder, const FString& SrcFolder, const FString& NewProjectFile, const FString& TemplateFile, bool bShouldGenerateCode, FText& OutFailReason)` — Callback before project generation is done, allowing for custom project generation behavior
- L221 _public function_ `virtual bool PostGenerateProject(const FString& DestFolder, const FString& SrcFolder, const FString& NewProjectFile, const FString& TemplateFile, bool bShouldGenerateCode, FText& OutFailReason)` — Callback after project generation is done, allowing for custom project generation behavior
- L224 _private prototype_ `void FixString(FString& InOutStringToFix, const FString& TemplateName, const FString& ProjectName);`

#### struct `FTemplateCategoryDef`  
`struct FTemplateCategoryDef`  
_L228-251_
- reflection: `USTRUCT()`
- L234 _public member_ `FName Key;` — `UPROPERTY()` — Key to use for identifying what category a template is in.
- L238 _public member_ `TArray<FLocalizedTemplateString> LocalizedDisplayNames;` — `UPROPERTY()` — Localized name for this template category.
- L242 _public member_ `TArray<FLocalizedTemplateString> LocalizedDescriptions;` — `UPROPERTY()` — Localized description for this template category.
- L246 _public member_ `FString Icon;` — `UPROPERTY()` — Reference to an icon to display for this category. Should be around 300x100.
- L250 _public member_ `bool IsMajorCategory=false;` — `UPROPERTY()` — Is this a major top-level category? Major categories are displayed as full rows, eg. the Game category.

#### class `UTemplateCategories`  
`class UTemplateCategories : public UObject`  
_L254-262_
- reflection: `UCLASS(config=TemplateCategories)`
- inherits: `UObject`
- L261 _public member_ `TArray<FTemplateCategoryDef> Categories;` — `UPROPERTY(config)` — Array of all categories specified in this location.

### `Source/Editor/GameProjectGeneration/Private/GameProjectGenerationLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameProjectGeneration, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameProjectGeneration, Verbose, All);`

### `Source/Editor/GameProjectGeneration/Private/SGetSuggestedIDEWidget.h` (Private)


#### class `SGetSuggestedIDEWidget`  
`class SGetSuggestedIDEWidget : public SCompoundWidget`  
_L19-51_
- inherits: `SCompoundWidget`
- desc: Either a button to directly install or a hyperlink to a website to download the suggested IDE for the platform. Only visible when no compiler is available.
- L22 _public function_ `SLATE_BEGIN_ARGS(SGetSuggestedIDEWidget)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(EVisibility, VisibilityOverride) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `TSharedRef<SWidget> CreateGetSuggestedIDEWidget();` — Creates the appropriate widget to display for the platform
- L35 _private prototype_ `EVisibility GetVisibility() const;` — Gets the visibility of the global error label IDE Link
- L38 _private prototype_ `FReply OnDownloadIDEClicked(FString URL);` — Handler for when the error label IDE hyperlink was clicked
- L41 _private prototype_ `FReply OnInstallIDEClicked();` — Handler for when the install IDE button was clicked
- L44 _private prototype_ `static void OnIDEInstallerDownloadComplete(bool bWasSuccessful);` — Handler for when the suggested IDE installer has finished downloading
- L49 _private member_ `static TSharedPtr<class SNotificationItem> IDEDownloadNotification;` — Handle to the notification displayed when downloading an IDE installer

#### class `SGetDisableIDEWidget`  
`class SGetDisableIDEWidget : public SCompoundWidget`  
_L57-72_
- inherits: `SCompoundWidget`
- desc: A button to disable requiring an IDE to be install Only visible on platforms that dont require an IDE to compile code and when no IDE is available
- L60 _public function_ `SLATE_BEGIN_ARGS(SGetDisableIDEWidget)`
- L61 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L68 _private prototype_ `TSharedRef<SWidget> CreateGetDisableIDEWidget();` — Creates the appropriate widget to display for the platform
- L71 _private prototype_ `FReply OnDisableIDEClicked();` — Handler for when the disable button is clicked

### `Source/Editor/GameProjectGeneration/Private/SNewClassDialog.h` (Private)


#### enum `EClassDomain`  
`enum class EClassDomain : uint8`  
_L43-43_
- L43 _public enumerator_ `enum class EClassDomain : uint8 { Blueprint, Native }; /** * A dialog to choose a new class parent and name */ class SNewClassDialog : public SCompoundWidget { public:`
- L43 _public enumerator_ `enum class EClassDomain : uint8 { Blueprint, Native }; /** * A dialog to choose a new class parent and name */ class SNewClassDialog : public SCompoundWidget { public:`

#### class `SNewClassDialog`  
`class SNewClassDialog : public SCompoundWidget`  
_L48-315_
- inherits: `SCompoundWidget`
- desc: A dialog to choose a new class parent and name
- L51 _public function_ `SLATE_BEGIN_ARGS( SNewClassDialog ) : _ClassDomain(EClassDomain::Native) , _Class(NULL) , _SyncContentBrowserToNewClass(true)`
- L58 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(EClassDomain, ClassDomain) SLATE_ARGUMENT(TArray<FNewClassInfo>, FeaturedClasses) SLATE_ARGUMENT(TSharedPtr<IClassViewerFilter>, ClassViewerFilter) SLATE_ARGUMENT(const UClass*, Class) SLATE_ARGUMENT(FString, InitialPath) SLATE_ARGUMENT(FString, DefaultClassPrefix) SLATE_ARGUMENT(FString, DefaultClassName) SLATE_EVENT( FOnAddedToProject, OnAddedToProject ) SLATE_ARGUMENT(bool, SyncContentBrowserToNewClass) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — A reference to the parent window
- L94 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnActivate();` — Get the widget to focus on activation
- L96 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L99 _public prototype_ `void CancelClicked();` — Handler for when cancel is clicked
- L102 _public prototype_ `void OnConfirmHotkeyPressed();` — Handler for when the Confirm hotkey is pressed
- L107 _private prototype_ `TSharedRef<ITableRow> MakeParentClassListViewWidget(TSharedPtr<FParentClassItem> ParentClassItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates a row in the parent class list
- L110 _private prototype_ `FText GetSelectedParentClassName() const;` — Gets the currently selected parent class name
- L113 _private prototype_ `FText GetSelectedParentClassFilename() const;` — Gets the currently selected parent class's filename
- L116 _private prototype_ `EVisibility GetSourceHyperlinkVisibility() const;` — Whether the hyper link to go to source should be visible
- L119 _private prototype_ `FString GetSelectedParentDocLink() const;` — Gets the currently select parent class's doc link
- L122 _private prototype_ `EVisibility GetDocLinkVisibility() const;` — Whether the document link anchor should be visible
- L125 _private prototype_ `void OnEditCodeClicked();` — Handler for when the selected parent class's filename is clicked
- L128 _private prototype_ `void OnParentClassItemDoubleClicked( TSharedPtr<FParentClassItem> TemplateItem );` — Handler for when a parent class item is double clicked
- L131 _private prototype_ `void OnClassSelected(TSharedPtr<FParentClassItem> Item, ESelectInfo::Type SelectInfo);` — Handler for when a class is selected in the parent class list
- L134 _private prototype_ `void OnAdvancedClassSelected(UClass* Class);` — Handler for when a class was picked in the full class tree
- L137 _private prototype_ `bool IsFullClassTreeShown() const;` — Gets the boolean for the full class list
- L140 _private prototype_ `void OnFullClassTreeChanged(bool bInShowFullClassTree);` — Sets the boolean for the full class list
- L143 _private prototype_ `EVisibility GetBasicParentClassVisibility() const;` — Gets the visibility of the basic class list
- L146 _private prototype_ `EVisibility GetAdvancedParentClassVisibility() const;` — Gets the visibility of the full class list
- L149 _private prototype_ `EVisibility GetNameErrorLabelVisibility() const;` — Gets the visibility of the name error label
- L152 _private prototype_ `FText GetNameErrorLabelText() const;` — Gets the text to display in the name error label
- L155 _private prototype_ `EVisibility GetGlobalErrorLabelVisibility() const;` — Gets the visibility of the global error label
- L158 _private prototype_ `FText GetGlobalErrorLabelText() const;` — Gets the text to display in the global error label
- L161 _private prototype_ `void OnNamePageEntered();` — Handler for when the user enters the "name class" page
- L164 _private prototype_ `FText GetNameClassTitle() const;` — Returns the title text for the "name class" page
- L167 _private prototype_ `FText OnGetClassNameText() const;` — Returns the text in the class name edit box
- L170 _private prototype_ `void OnClassNameTextChanged(const FText& NewText);` — Handler for when the text in the class name edit box has changed
- L173 _private prototype_ `void OnClassNameTextCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Handler for when the text in the class name edit box is committed
- L176 _private prototype_ `FText OnGetClassPathText() const;` — Returns the text in the class path edit box
- L179 _private prototype_ `void OnClassPathTextChanged(const FText& NewText);` — Handler for when the text in the class path edit box has changed
- L182 _private prototype_ `void OnBlueprintPathSelected(const FString& NewPath);` — Called when the user chooses a path for a blueprint
- L185 _private prototype_ `FText OnGetClassHeaderFileText() const;` — Returns the text for the calculated header file name
- L188 _private prototype_ `FText OnGetClassSourceFileText() const;` — Returns the text for the calculated source file name
- L191 _private prototype_ `bool CanFinish() const;` — Returns true if Finish is allowed
- L194 _private prototype_ `void FinishClicked();` — Handler for when finish is clicked
- L197 _private prototype_ `FReply HandleChooseFolderButtonClicked( );` — Handler for when the "Choose Folder" button is clicked
- L200 _private prototype_ `FText GetSelectedModuleComboText() const;` — Get the combo box text for the currently selected module
- L203 _private prototype_ `void SelectedModuleComboBoxSelectionChanged(TSharedPtr<FModuleContextInfo> Value, ESelectInfo::Type SelectInfo);` — Called when the currently selected module is changed
- L206 _private prototype_ `TSharedRef<SWidget> MakeWidgetForSelectedModuleCombo(TSharedPtr<FModuleContextInfo> Value);` — Create the widget to use as the combo box entry for the given module info
- L211 _private prototype_ `FSlateColor GetClassLocationTextColor(GameProjectUtils::EClassLocation InLocation) const;` — Get the text color to use for the given class location checkbox
- L214 _private prototype_ `GameProjectUtils::EClassLocation IsClassLocationActive() const;` — Checks to see if the given class location is active based on the current value of NewClassPath
- L217 _private prototype_ `void OnClassLocationChanged(GameProjectUtils::EClassLocation InLocation);` — Update the value of NewClassPath so that it uses the given class location
- L220 _private prototype_ `void UpdateInputValidity();` — Checks the current class name/path for validity and updates cached values accordingly
- L223 _private prototype_ `const FNewClassInfo& GetSelectedParentClassInfo() const;` — Gets the currently selected parent class
- L226 _private prototype_ `void SetupParentClassItems(const TArray<FNewClassInfo>& UserSpecifiedFeaturedClasses);` — Adds parent classes to the ParentClassListView source
- L229 _private prototype_ `void CloseContainingWindow();` — Closes the window that contains this widget
- L234 _private member_ `TSharedPtr<SWizard> MainWizard;` — The wizard widget
- L237 _private member_ `TSharedPtr< SListView< TSharedPtr<FParentClassItem> > > ParentClassListView;` — ParentClass items
- L238 _private member_ `TArray< TSharedPtr<FParentClassItem> > ParentClassItemsSource;`
- L241 _private member_ `TSharedPtr<class SClassViewer> ClassViewer;` — A pointer to a class viewer
- L244 _private member_ `FString DefaultClassPrefix;` — The prefix to put on new classes by default, if the user doesn't type in a new name.  Defaults to 'My'.
- L248 _private member_ `FString DefaultClassName;` — If non-empty, overrides the default name of the class, when the user doesn't type a new name.  Defaults to empty, which causes the name to be the inherited class name.  Note that DefaultClassPrefix is still prepended to this name, if non-empty.
- L251 _private member_ `TSharedPtr<SEditableTextBox> ClassNameEditBox;` — The editable text box to enter the current name
- L254 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FModuleContextInfo>>> AvailableModulesCombo;` — The available modules combo box
- L257 _private member_ `static FString LastSelectedModuleName;` — The last selected module name. Meant to keep the same module selected after first selection
- L260 _private member_ `FString NewClassName;` — The name of the class being created
- L263 _private member_ `FString NewClassPath;` — The path to place the files for the class being generated
- L266 _private member_ `FString CalculatedClassHeaderName;` — The calculated name of the generated header file for this class
- L269 _private member_ `FString CalculatedClassSourceName;` — The calculated name of the generated source file for this class
- L272 _private member_ `FString LastAutoGeneratedClassName;` — The name of the last class that was auto-generated by this wizard
- L275 _private member_ `FNewClassInfo ParentClassInfo;` — The selected parent class
- L278 _private member_ `bool bShowFullClassTree;` — If true, the full class tree will be shown in the parent class selection
- L281 _private member_ `double LastPeriodicValidityCheckTime;` — The last time that the class name/path was checked for validity. This is used to throttle I/O requests to a reasonable frequency
- L284 _private member_ `double PeriodicValidityCheckFrequency;` — The frequency in seconds for validity checks while the dialog is idle. Changes to the name/path immediately update the validity.
- L287 _private member_ `bool bPreventPeriodicValidityChecksUntilNextChange;` — Periodic checks for validity will not occur while this flag is true. Used to prevent a frame of "this project already exists" while exiting after a successful creation.
- L290 _private member_ `FText LastInputValidityErrorText;` — The error text from the last validity check
- L293 _private member_ `bool bLastInputValidityCheckSuccessful;` — True if the last validity check returned that the class name/path is valid for creation
- L296 _private member_ `GameProjectUtils::EClassLocation ClassLocation;` — Whether the class should be created as a Public or Private class
- L299 _private member_ `EClassDomain ClassDomain;` — The domain of the new class we are creating (native or blueprint)
- L302 _private member_ `TArray<TSharedPtr<FModuleContextInfo>> AvailableModules;` — Information about the currently available modules for this project
- L305 _private member_ `TSharedPtr<FModuleContextInfo> SelectedModuleInfo;` — Information about the currently selected module; used for class validation
- L308 _private member_ `FOnAddedToProject OnAddedToProject;` — Event called when code is succesfully added to the project
- L311 _private member_ `bool IsBlueprintPathSelected = false;` — Flag set when PathPicker selects a path
- L314 _private member_ `bool bSyncContentBrowserToNewClass = true;` — Whether we should sync the content browser to navigate to the newly created asset

### `Source/Editor/GameProjectGeneration/Private/SProjectBrowser.h` (Private)


#### enum `EProjectSortOption`  
`enum class EProjectSortOption : uint8`  
_L37-47_
- L40 _public enumerator_ `LastAccessTime` — Sort by the last time the project was opened
- L43 _public enumerator_ `Version` — Sort by engine version
- L46 _public enumerator_ `Alphabetical` — By project name

#### class `SProjectBrowser`  
`class SProjectBrowser : public SCompoundWidget`  
_L57-204_
- inherits: `SCompoundWidget`
- desc: A list of known projects with the option to add a new one
- L64 _public function_ `SLATE_BEGIN_ARGS(SProjectBrowser) : _ShowHeaderBar(true) , _AllowScrolling(true) , _IsEmbedded(false)`
- L69 _public prototype_ `SLATE_ARGUMENT(bool, ShowHeaderBar) SLATE_ARGUMENT(bool, AllowScrolling) SLATE_ARGUMENT(bool, IsEmbedded) SLATE_ARGUMENT(FProjectSelectionChanged, OnSelectionChanged);`
- L80 _public prototype_ `SProjectBrowser();` — Constructor
- L87 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs. @param InArgs - The construction arguments.
- L89 _public prototype_ `bool HasProjects() const;`
- L91 _public function_ `bool HasSelectedProjectFile() const`
- L93 _public prototype_ `FString GetSelectedProjectFile() const;`
- L95 _public prototype_ `FText GetSelectedProjectName() const;`
- L98 _public prototype_ `void OpenSelectedProject();` — Begins the opening process for the selected project
- L100 _public prototype_ `FReply OnBrowseToProject();`
- L103 _public prototype_ `FReply OnOpenProject();` — Handler for when the Open button is clicked
- L106 _public prototype_ `void OnAutoloadLastProjectChanged(ECheckBoxState NewState);` — Whether to autoload the last project.
- L110 _protected prototype_ `TSharedRef<ITableRow> MakeProjectViewWidget(TSharedPtr<FProjectItem> ProjectItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates a row in the template list
- L113 _protected prototype_ `TSharedRef<SToolTip> MakeProjectToolTip(TSharedPtr<FProjectItem> ProjectItem) const;` — Create a tooltip for the given project item
- L116 _protected prototype_ `void AddToToolTipInfoBox(const TSharedRef<SVerticalBox>& InfoBox, const FText& Key, const FText& Value) const;` — Add information to the tooltip for this project item
- L119 _protected prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Get the context menu to use for the selected project item
- L122 _protected prototype_ `void ExecuteFindInExplorer() const;` — Handler for when find in explorer is selected
- L125 _protected prototype_ `bool CanExecuteFindInExplorer() const;` — Handler to check to see if a find in explorer command is allowed
- L128 _protected prototype_ `TSharedPtr<FProjectItem> GetSelectedProjectItem() const;` — Gets the currently selected template item
- L131 _protected prototype_ `FReply FindProjects();` — Populates ProjectItemsSource with projects found on disk
- L134 _protected prototype_ `bool OpenProject(const FString& ProjectFile);` — Opens the specified project file
- L137 _protected prototype_ `void PopulateFilteredProjects();` — Populate the list of filtered project categories
- L147 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Called after a key is pressed when this widget has focus (this event bubbles if not handled) @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L151 _private prototype_ `bool HandleOpenProjectButtonIsEnabled() const;` — Returns true if the user is allowed to open a project with the supplied name and path
- L154 _private prototype_ `void HandleProjectItemDoubleClick(TSharedPtr<FProjectItem> ProjectItem);` — Called when a user double-clicks a project item in the project view
- L157 _private prototype_ `void HandleProjectViewSelectionChanged(TSharedPtr<FProjectItem> ProjectItem, ESelectInfo::Type SelectInfo);` — Handler for when the selection changes in the project view
- L160 _private prototype_ `void OnFilterTextChanged(const FText& InText);` — Called when the text in the filter box is changed
- L163 _private prototype_ `EVisibility GetProjectCategoryVisibility(const TSharedRef<FProjectCategory> InCategory) const;` — Get the visibility of the specified category
- L165 _private prototype_ `EVisibility GetNoProjectsErrorVisibility() const;`
- L168 _private prototype_ `EVisibility GetNoProjectsAfterFilterErrorVisibility() const;` — Get the visibility of the "no projects" error
- L171 _private prototype_ `FText GetItemHighlightText() const;` — Get the filter text to highlight on items in the list
- L173 _private prototype_ `void SortProjectTiles(EProjectSortOption NewSortOption);`
- L174 _private prototype_ `ECheckBoxState GetSortOptionCheckState(EProjectSortOption TestOption) const;`
- L177 _private member_ `TSharedPtr<STileView<TSharedPtr<FProjectItem>>> ProjectTileView;`
- L178 _private member_ `TArray<TSharedPtr<FProjectItem>> ProjectItemsSource;`
- L179 _private member_ `TArray<TSharedPtr<FProjectItem>> FilteredProjectItemsSource;`
- L180 _private member_ `TSharedPtr<SVerticalBox> ProjectsBox;`
- L182 _private member_ `FProjectSelectionChanged ProjectSelectionChangedDelegate;`
- L185 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — Search box used to set the filter text
- L188 _private typedef_ `typedef TTextFilter<const TSharedPtr<FProjectItem>> ProjectItemTextFilter;` — Filter that is used to test for the visibility of projects
- L189 _private member_ `ProjectItemTextFilter ProjectItemFilter;`
- L191 _private member_ `bool bPreventSelectionChangeEvent;`
- L193 _private member_ `FString CurrentSelectedProjectPath;`
- L195 _private member_ `bool IsOnlineContentFinished;`
- L198 _private member_ `bool bIsEmbedded;` — If true it will show the embedded version of the ProjectBrowser
- L201 _private member_ `FNewProjectScreenRequested NewProjectScreenRequestedDelegate;` — Holds a delegate that is executed when the new project screen is being requested.
- L203 _private member_ `EProjectSortOption CurrentSortOption = EProjectSortOption::LastAccessTime;`

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_DELEGATE_OneParam(FProjectSelectionChanged, FString);`
- L52 _prototype_ `DECLARE_DELEGATE_OneParam(FProjectSelectionChanged, FString);`
- L62 _delegate_ `DECLARE_DELEGATE(FNewProjectScreenRequested) SLATE_BEGIN_ARGS(SProjectBrowser) : _ShowHeaderBar(true) , _AllowScrolling(true) , _IsEmbedded(false) {} SLATE_ARGUMENT(bool, ShowHeaderBar) SLATE_ARGUMENT(bool, AllowScrolling) SLATE_ARGUMENT(bool, IsEmbedded) SLATE_ARGUMENT(FProjectSelectionChanged, OnSelectionChanged);`

### `Source/Editor/GameProjectGeneration/Private/SProjectDialog.h` (Private)


#### enum `EProjectDialogModeMode`  
`enum class EProjectDialogModeMode : uint8`  
_L44-52_
- L47 _public enumerator_ `Hybrid` — Shows new project templates and existing projects
- L49 _public enumerator_ `OpenProject` — Shows existing projects
- L51 _public enumerator_ `NewProject` — Shows new project templates

#### class `SProjectDialog`  
`class SProjectDialog : public SCompoundWidget`  
_L54-295_
- inherits: `SCompoundWidget`
- L56 _private function_ `SLATE_BEGIN_ARGS(SProjectDialog)`
- L57 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, EProjectDialogModeMode Mode);`
- L62 _private prototype_ `~SProjectDialog();`
- L65 _private prototype_ `static TMap<FName, TArray<TSharedPtr<FTemplateItem>>> FindTemplateProjects();` — @returns All templates found on disk
- L69 _private prototype_ `TSharedPtr<FTemplateItem> GetSelectedTemplateItem() const;` — Accessor for the currently selected template item
- L72 _private prototype_ `UTemplateProjectDefs* GetSelectedTemplateDefs() const;` — Accessor for the TemplateDefs of the currently selected template item. Will return either the BP or CPP version based on bShouldGenerateCode
- L74 _private function_ `const FTemplateVariant* GetSelectedTemplateDefsVariant() const` — Accessor for the Variant matching the SelectedVariantName for the currently selected TemplateDefs (see GetSelectedTemplateDefs)
- L79 _private prototype_ `const FTemplateVariant* GetSelectedTemplateDefsVariant(FName VariantName) const;` — Accessor for the Variant with the given name for the currently selected TemplateDefs (see GetSelectedTemplateDefs). Returns null if not found
- L84 _private function_ `template<typename T> T GetSelectedTemplateProperty(T FTemplateItem::* Prop) const` — TRet should be defaulted but VS2012 doesn't allow default template arguments on non-class templates
- L95 _private prototype_ `void OnMajorTemplateCategorySelectionChanged(TSharedPtr<FTemplateCategory> Item, ESelectInfo::Type SelectType);`
- L96 _private prototype_ `TSharedRef<ITableRow> ConstructMajorCategoryTableRow(TSharedPtr<FTemplateCategory> Item, const TSharedRef<STableViewBase>& TableView);`
- L98 _private prototype_ `void PopulateTemplateCategories();`
- L101 _private prototype_ `void OnCurrentProjectFilePathChanged(const FText& InValue);` — Handler for when the project path string was changed
- L104 _private prototype_ `void OnCurrentProjectFileNameChanged(const FText& InValue);` — Handler for when the project name string was changed
- L106 _private prototype_ `FReply HandlePathBrowseButtonClicked();`
- L109 _private prototype_ `void UpdateProjectFileValidity();` — Checks the current project path an name for validity and updates cached values accordingly
- L112 _private prototype_ `void UpdateTemplateTrustWarning();` — Checks if the currently selected template is from a plugin that is not enabled and updates the warning message accordingly
- L115 _private prototype_ `bool IsCompilerRequired() const;` — Returns true if we have a code template selected
- L117 _private prototype_ `bool IsIDERequired() const;`
- L119 _private prototype_ `EVisibility GetProjectSettingsVisibility() const;`
- L122 _private prototype_ `EVisibility GetSelectedTemplateClassVisibility() const;` — Get a visibility of the class types display. If the string is empty this return Collapsed otherwise it will return Visible
- L125 _private prototype_ `EVisibility GetSelectedTemplateAssetVisibility() const;` — Get a visibility of the asset types display. If the string is empty this return Collapsed otherwise it will return Visible
- L127 _private function_ `EVisibility GetGlobalErrorVisibility() const`
- L129 _private function_ `EVisibility GetGlobalWarningVisibility() const`
- L131 _private prototype_ `EVisibility GetCreateButtonVisibility() const;`
- L133 _private prototype_ `EVisibility GetSuggestedIDEButtonVisibility() const;`
- L135 _private prototype_ `EVisibility GetDisableIDEButtonVisibility() const;`
- L138 _private prototype_ `FText GetCurrentProjectFileName() const;` — Accessor for the project name text
- L141 _private prototype_ `FText GetCurrentProjectFilePath() const;` — Accessor for the project path text
- L144 _private prototype_ `FText GetSelectedTemplateAssetTypes() const;` — Get a visibility of the asset types display. If the string is empty this return Collapsed otherwise it will return Visible
- L147 _private prototype_ `FText GetSelectedTemplateClassTypes() const;` — Get a string that details the class types referenced in the selected template
- L149 _private prototype_ `FText GetGlobalErrorLabelText() const;`
- L151 _private prototype_ `FText GetGlobalWarningLabelText() const;`
- L153 _private prototype_ `FText GetNameAndLocationValidityErrorText() const;`
- L156 _private prototype_ `FString GetProjectFilenameWithPath() const;` — Gets the assembled project filename with path
- L158 _private prototype_ `TSharedRef<SWidget> MakeNewProjectDialogButtons();`
- L160 _private prototype_ `TSharedRef<SWidget> MakeOpenProjectDialogButtons();`
- L162 _private prototype_ `TSharedRef<SWidget> MakeTemplateProjectView();`
- L164 _private prototype_ `TSharedRef<SWidget> MakeRecentProjectsView();`
- L166 _private prototype_ `TSharedRef<SWidget> MakeHybridView(EProjectDialogModeMode Mode);`
- L168 _private prototype_ `TSharedRef<SWidget> MakeProjectOptionsWidget();`
- L170 _private prototype_ `TSharedRef<SWidget> MakePluginInformationWidget();`
- L172 _private prototype_ `TSharedRef<SWidget> MakeRecentProjectsTile();`
- L174 _private prototype_ `TSharedRef<SWidget> MakeNewProjectPathArea();`
- L176 _private prototype_ `TSharedRef<SWidget> MakeOpenProjectPathArea();`
- L179 _private prototype_ `const FSlateBrush* GetSelectedTemplatePreviewImage() const;` — Get the images for the selected template preview and category
- L181 _private prototype_ `bool CanCreateProject() const;`
- L183 _private prototype_ `FReply OnCancel() const;`
- L185 _private function_ `int32 OnGetBlueprintOrCppIndex() const`
- L186 _private prototype_ `void OnSetBlueprintOrCppIndex(int32 Index);`
- L188 _private prototype_ `void SetHardwareClassTarget(EHardwareClass InHardwareClass);`
- L189 _private function_ `EHardwareClass GetHardwareClassTarget() const`
- L191 _private prototype_ `void SetGraphicsPreset(EGraphicsPreset InGraphicsPreset);`
- L192 _private function_ `EGraphicsPreset GetGraphicsPreset() const`
- L194 _private prototype_ `void ResetVariants();`
- L195 _private prototype_ `EVisibility GetVariantsVisibility() const;`
- L196 _private prototype_ `TSharedRef< SWidget > GetVariantsDropdownContent();`
- L197 _private prototype_ `FText GetVariantsButtonText() const;`
- L198 _private prototype_ `FText GetVariantsButtonTooltip() const;`
- L201 _private prototype_ `void HandleTemplateListViewSelectionChanged(TSharedPtr<FTemplateItem> TemplateItem, ESelectInfo::Type SelectInfo);` — Handler for when the selection changes in the template list
- L203 _private prototype_ `void SetDefaultProjectLocation();`
- L205 _private prototype_ `void SetCurrentMajorCategory(FName Category);`
- L207 _private prototype_ `FReply OnRecentProjectsClicked();`
- L210 _private prototype_ `void OnLoadMostRecentProjectEditorSettingChanged(bool bInAutoLoadOption);` — Called from the editor setting when bLoadTheMostRecentlyLoadedProjectAtStartup change to sync it
- L213 _private prototype_ `ECheckBoxState IsLoadMostRecentProjectChecked() const;` — Checked if it should load the most recent project, unchecked otherwise
- L215 _private prototype_ `FProjectInformation CreateProjectInfo() const;`
- L216 _private prototype_ `bool CreateProject(const FString& ProjectFile);`
- L217 _private prototype_ `void CreateAndOpenProject();`
- L218 _private prototype_ `bool OpenProject(const FString& ProjectFile);`
- L219 _private prototype_ `bool OpenCodeIDE(const FString& ProjectFile);`
- L220 _private prototype_ `void CloseWindowIfAppropriate(bool ForceClose = false);`
- L221 _private prototype_ `void DisplayError(const FText& ErrorText);`
- L222 _private prototype_ `void DisplayWarning(const FText& WarningText);`
- L225 _private prototype_ `static TArray<TSharedPtr<FTemplateCategory>> GetAllTemplateCategories();`
- L226 _private prototype_ `static TSharedRef<FSlateBrush> SetupThumbnailBrush(TSharedRef<FSlateBrush> ThumbnailBrush);`
- L229 _private member_ `TArray<TSharedPtr<FTemplateCategory>> TemplateCategories;`
- L230 _private member_ `TSharedPtr<FTemplateCategory> CurrentCategory;`
- L231 _private member_ `TSharedPtr<STileView<TSharedPtr<FTemplateCategory>>> MajorCategoryList;`
- L233 _private member_ `TSharedPtr<FTemplateCategory> RecentProjectsCategory;`
- L236 _private member_ `TMap<FName, TArray<TSharedPtr<FTemplateItem>> > Templates;` — A map of category name to array of templates available for that category
- L239 _private member_ `TArray<TSharedPtr<FTemplateItem> > FilteredTemplateList;` — The filtered array of templates we are currently showing
- L242 _private member_ `TSharedPtr<STileView<TSharedPtr<FTemplateItem>>> TemplateListView;` — The slate widget representing the list of templates
- L244 _private member_ `TSharedPtr<SWidgetSwitcher> TemplateAndRecentProjectsSwitcher;`
- L245 _private member_ `TSharedPtr<SWidgetSwitcher> PathAreaSwitcher;`
- L247 _private member_ `TSharedPtr<SProjectBrowser> ProjectBrowser;`
- L249 _private member_ `TSharedPtr<FSlateDynamicImageBrush> PluginIconDynamicImageBrush;`
- L251 _private member_ `FString LastBrowsePath;`
- L252 _private member_ `FString CurrentProjectFileName;`
- L253 _private member_ `FString CurrentProjectFilePath;`
- L255 _private member_ `FText PersistentGlobalErrorLabelText;`
- L256 _private member_ `FText PersistentGlobalWarningLabelText;`
- L259 _private member_ `FText LastGlobalValidityErrorText;` — The global error text from the last validity check
- L261 _private member_ `FText LastNameAndLocationValidityErrorText;`
- L264 _private member_ `FName ActiveCategory;` — Name of the currently selected template category
- L266 _private member_ `EHardwareClass SelectedHardwareClassTarget;`
- L268 _private member_ `EGraphicsPreset SelectedGraphicsPreset;`
- L270 _private member_ `FName SelectedVariantName;`
- L271 _private member_ `TArray<FName> TemplateVariantNames;`
- L273 _private member_ `TSharedPtr<FSlateBrush> RecentProjectsBrush;`
- L275 _private member_ `static TSharedPtr<FSlateBrush> CustomTemplateBrush;`
- L277 _private member_ `SVerticalBox::FSlot* ProjectOptionsSlot;`
- L279 _private member_ `SVerticalBox::FSlot* PluginInformationSlot;`
- L282 _private member_ `bool bEnableXR;` — Whether or not to enable XR in the created project.
- L285 _private member_ `bool bShouldGenerateCode;` — Whether or not we should use the blueprint or C++ version of this template.
- L288 _private member_ `bool bLastGlobalValidityCheckSuccessful;` — True if the last global validity check returned that the project path is valid for creation
- L291 _private member_ `bool bLastNameAndLocationValidityCheckSuccessful;` — True if the last NameAndLocation validity check returned that the project path is valid for creation
- L294 _private member_ `bool bLoadMostRecentlyLoadedProject = false;` — Synced setting to the EditorSetting bLoadTheMostRecentlyLoadedProjectAtStartup

### `Source/Editor/GameProjectGeneration/Private/SVerbChoiceDialog.h` (Private)


#### class `SVerbChoiceDialog`  
`class SVerbChoiceDialog : public SCompoundWidget`  
_L18-63_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS( SVerbChoiceDialog )`
- L22 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_ATTRIBUTE(FText, Message) SLATE_ATTRIBUTE(TArray<FText>, Hyperlinks) SLATE_ATTRIBUTE(TArray<FText>, Buttons) SLATE_ATTRIBUTE(float, WrapMessageAt) SLATE_END_ARGS() static int32 ShowModal(const FText& InTitle, const FText& InText, const TArray<FText>& InButtons);`
- L33 _public prototype_ `static int32 ShowModal(const FText& InTitle, const FText& InText, const TArray<FText>& InHyperlinks, const TArray<FText>& InButtons);` — Displays the modal dialog box, also allowing customization of the hyperlinks
- L36 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs the dialog
- L39 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Override behavior when a key is pressed
- L42 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;` — Override the base method to allow for keyboard focus
- L46 _protected prototype_ `void CopyMessageToClipboard( );` — Copies the message text to the clipboard.
- L50 _private prototype_ `FReply HandleCopyMessageButtonClicked( );` — Handles clicking the 'Copy Message' button.
- L53 _private prototype_ `void HandleHyperlinkClicked( int32 InResponse );` — Handles clicking on a hyperlink.
- L56 _private prototype_ `FReply HandleButtonClicked( int32 InResponse );` — Handles clicking a message box button.
- L58 _private member_ `int32 Response;`
- L59 _private member_ `TSharedPtr<SWindow> ParentWindow;`
- L60 _private member_ `TAttribute<FText> Message;`
- L61 _private member_ `TAttribute< TArray<FText> > Buttons;`
- L62 _private member_ `TAttribute< TArray<FText> > Hyperlinks;`

### `Source/Editor/GameProjectGeneration/Private/TemplateCategory.h` (Private)


#### struct `FTemplateCategory`  
`struct FTemplateCategory`  
_L10-48_
- L13 _public member_ `FText DisplayNameOverride;` — The overriden name of this category
- L16 _public member_ `FText DescriptionOverride;` — The overriden description of the templates contained within this category
- L18 _public member_ `TArray<FLocalizedTemplateString> LocalizedDisplayNames;`
- L19 _public member_ `TArray<FLocalizedTemplateString> LocalizedDescriptions;`
- L22 _public member_ `TSharedPtr<FSlateBrush> Icon;` — A thumbnail to help identify this category (on the tab)
- L25 _public member_ `FName Key;` — A unique key for this category
- L28 _public member_ `bool IsEnterprise = false;` — Is this an enterprise project? Will end up including Datasmith modules if true.
- L31 _public function_ `FText GetDisplayName() const` — Localized name of this category
- L40 _public function_ `FText GetDescription() const` — A description of the templates contained within this category

### `Source/Editor/GameProjectGeneration/Private/TemplateItem.h` (Private)


#### struct `FTemplateItem`  
`struct FTemplateItem`  
_L11-60_
- desc: Struct describing a single template project
- L13 _public member_ `FText DisplayNameOverride;`
- L14 _public member_ `FText DescriptionOverride;`
- L15 _public member_ `TArray<FLocalizedTemplateString> LocalizedDisplayNames;`
- L16 _public member_ `TArray<FLocalizedTemplateString> LocalizedDescriptions;`
- L17 _public member_ `TArray<FName> Categories;`
- L19 _public member_ `FString Key;`
- L20 _public member_ `FString SortKey;`
- L22 _public member_ `TSharedPtr<FSlateBrush> Thumbnail;`
- L23 _public member_ `TSharedPtr<FSlateBrush> PreviewImage;`
- L24 _public member_ `TWeakPtr<IPlugin> PluginWeak;`
- L27 _public member_ `FString ClassTypes;`
- L28 _public member_ `FString AssetTypes;`
- L30 _public member_ `FString CodeProjectFile;`
- L31 _public member_ `UTemplateProjectDefs* CodeTemplateDefs = nullptr;`
- L32 _public member_ `FString BlueprintProjectFile;`
- L33 _public member_ `UTemplateProjectDefs* BlueprintTemplateDefs = nullptr;`
- L35 _public member_ `TArray<ETemplateSetting> HiddenSettings;`
- L37 _public member_ `bool bIsEnterprise = false;`
- L38 _public member_ `bool bIsBlankTemplate = false;`
- L39 _public member_ `bool bThumbnailAsIcon = false;`
- L42 _public function_ `FText GetDisplayName() const` — Localized name of this template
- L52 _public function_ `FText GetDescription() const` — A description of the template

### `Source/Editor/GameProjectGeneration/Public/AddToProjectConfig.h` (Public)


#### struct `FNewClassInfo`  
`struct FNewClassInfo`  
_L25-117_
- desc: Information used when creating a new class via AddCodeToProject
- L47 _public function_ `FNewClassInfo() : ClassType(EClassType::UObject) , BaseClass(nullptr)` — Default constructor; must produce an object which fails the IsSet check
- L54 _public function_ `explicit FNewClassInfo(const EClassType InClassType) : ClassType(InClassType) , BaseClass(nullptr)` — Convenience constructor so you can construct from a EClassType
- L61 _public function_ `explicit FNewClassInfo(const UClass* InBaseClass) : ClassType(EClassType::UObject) , BaseClass(InBaseClass)` — Convenience constructor so you can construct from a UClass
- L68 _public function_ `bool IsSet() const` — Check to see if this struct is set to something that could be used to create a new class
- L74 _public prototype_ `FText GetClassName() const;` — Get the "friendly" class name to use in the UI
- L77 _public prototype_ `FText GetClassDescription(const bool bFullDescription = true) const;` — Get the class description to use in the UI
- L80 _public prototype_ `const FSlateBrush* GetClassIcon() const;` — Get the class icon to use in the UI
- L83 _public prototype_ `FString GetClassPrefixCPP() const;` — Get the C++ prefix used for this class type
- L86 _public prototype_ `FString GetClassNameCPP() const;` — Get the C++ class name; this may or may not be prefixed, but will always produce a valid C++ name via GetClassPrefix() + GetClassName()
- L89 _public prototype_ `FString GetCleanClassName(const FString& ClassName) const;` — Some classes may apply a particular suffix; this function returns the class name with those suffixes removed
- L92 _public prototype_ `FString GetFinalClassName(const FString& ClassName) const;` — Some classes may apply a particular suffix; this function returns the class name that will ultimately be used should that happen
- L95 _public prototype_ `bool GetIncludePath(FString& OutIncludePath) const;` — Get the path needed to include this class into another file
- L98 _public prototype_ `FString GetBaseClassHeaderFilename() const;` — Gets header filename of the base class.
- L101 _public prototype_ `FString GetHeaderFilename(const FString& ClassName) const;` — Given a class name, generate the header file (.h) that should be used for this class
- L104 _public prototype_ `FString GetSourceFilename(const FString& ClassName) const;` — Given a class name, generate the source file (.cpp) that should be used for this class
- L107 _public prototype_ `FString GetHeaderTemplateFilename() const;` — Get the generation template filename to used based on the current class type
- L110 _public prototype_ `FString GetSourceTemplateFilename() const;` — Get the generation template filename to used based on the current class type
- L113 _public member_ `EClassType ClassType;` — The type of class we want to create
- L116 _public member_ `const UClass* BaseClass;` — Base class information; if the ClassType is UObject

#### enum `FNewClassInfo::EClassType`  
`enum class EClassType : uint8`  
_L28-44_
- desc: The type of class we want to create
- L31 _public enumerator_ `UObject` — The new class is using a UObject as a base, consult BaseClass for the type.
- L34 _public enumerator_ `EmptyCpp` — The new class should be an empty standard C++ class.
- L37 _public enumerator_ `SlateWidget` — The new class should be a Slate widget, deriving from SCompoundWidget.
- L40 _public enumerator_ `SlateWidgetStyle` — The new class should be a Slate widget style, deriving from FSlateWidgetStyle, along with its associated UObject wrapper class.
- L43 _public enumerator_ `UInterface` — The new class is a UObject Interface, to be implemented by other UObject-based classes.

#### struct `FFeaturedClasses`  
`struct FFeaturedClasses`  
_L121-145_
- desc: @todo make this ini configurable
- L125 _public prototype_ `static TArray<FNewClassInfo> AllNativeClasses();` — Get a list of all featured native class types
- L128 _public prototype_ `static TArray<FNewClassInfo> ActorClasses();` — Get a list of all featured Actor class types
- L131 _public prototype_ `static TArray<FNewClassInfo> ComponentClasses();` — Get a list of all featured Component class types
- L135 _private prototype_ `static void AddCommonActorClasses(TArray<FNewClassInfo>& Array);` — Append the featured Actor class types that are commonly used
- L138 _private prototype_ `static void AddExtraActorClasses(TArray<FNewClassInfo>& Array);` — Append the featured Actor class types that are less commonly used
- L141 _private prototype_ `static void AddCommonComponentClasses(TArray<FNewClassInfo>& Array);` — Append the featured Component class types that are commonly used
- L144 _private prototype_ `static void AddExtraComponentClasses(TArray<FNewClassInfo>& Array);` — Append the featured Component class types that are less commonly used

#### struct `FAddToProjectConfig`  
`struct FAddToProjectConfig`  
_L148-213_
- desc: Add to project dialog configuration structure
- L150 _public function_ `FAddToProjectConfig() : _ParentClass(nullptr), _bModal(false)`
- L155 _public function_ `FAddToProjectConfig& ParentClass(const UClass* InClass)` — Force the add to project dialog to use the specified parent class. Skips the first step (choose a parent class) as a result.
- L157 _public function_ `FAddToProjectConfig& AllowableParents(const TSharedPtr<IClassViewerFilter>& In)` — Limits the allowable parent classes by the specified filter.
- L160 _public function_ `FAddToProjectConfig& InitialPath(FString InInitialPath)` — The initial path we should use as the destination for the new file, or an empty string to choose a suitable default based upon the module path.
- L162 _public function_ `FAddToProjectConfig& DefaultClassName(FString InDefaultClassName)` — Optional argument that specifies the default name for the new class being added.  The user will be able to type their own name if they don't like this name.  If empty, defaults to the name of the inherited class.
- L164 _public function_ `FAddToProjectConfig& DefaultClassPrefix(FString InDefaultClassPrefix)` — Optional argument that specifies the prefix for the new class name.  The user will be able to type their own name if they don't like this name.  Defaults to "My" if not specified or empty.
- L167 _public function_ `FAddToProjectConfig& WindowTitle(FText InText)` — The title text to display on the window
- L169 _public function_ `FAddToProjectConfig& ParentWindow(const TSharedPtr<SWindow>& InParentWindow)` — The parent window the dialog should use, or null to choose a suitable default parent window (the main frame, if available).
- L171 _public function_ `FAddToProjectConfig& Modal(bool bModal = true)` — Make the window modal to force the user to make a decision before continuing.
- L174 _public function_ `FAddToProjectConfig& OnAddedToProject(const FOnAddedToProject& InDelegate)` — Callback for when the object is successfully added to the project
- L177 _public function_ `FAddToProjectConfig& FeatureAllNativeClasses()` — Set the add to project dialog to show component types on the initial 'featured' classes list
- L179 _public function_ `FAddToProjectConfig& FeatureActorClasses()` — Set the add to project dialog to show component types on the initial 'featured' classes list
- L181 _public function_ `FAddToProjectConfig& FeatureComponentClasses()` — Set the add to project dialog to show component types on the initial 'featured' classes list
- L183 _public function_ `FAddToProjectConfig& SyncContentBrowserToNewClass(bool bInSyncContentBrowser)` — Set whether the content browser will be synced to view the newly created class
- L188 _public member_ `const UClass* _ParentClass;` — Forced parent class to use
- L190 _public member_ `TSharedPtr<IClassViewerFilter> _AllowableParents;` — Filter for allowable parent classes, when ParentClass is nullptr
- L192 _public member_ `TArray<FNewClassInfo> _FeaturedClasses;` — Array of featured classes
- L195 _public member_ `FString _InitialPath;` — Initial file path for the (blueprint) class
- L197 _public member_ `FString _DefaultClassPrefix;` — Default name prefix for the (blueprint) class
- L199 _public member_ `FString _DefaultClassName;` — Default name for the (blueprint) class, excluding class prefix
- L202 _public member_ `FText _WindowTitle;` — The title to display on the window
- L204 _public member_ `TSharedPtr<SWindow> _ParentWindow;` — Parent window to use
- L206 _public member_ `bool _bModal;` — True to force a modal dialog, false otherwise
- L209 _public member_ `FOnAddedToProject _OnAddedToProject;` — Delegate to invoke when the (blueprint) class has been added to the project
- L212 _public member_ `bool _SyncContentBrowserToNewClass = true;` — Whether the content browser will be synced to view the newly created class

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnAddedToProject, const FString& , const FString& , const FString& );` — Delegate called when code is added to the project.  Passes in the created class name and class path @param ClassName		The created class name @param ClassPath		The created class path @param ModuleName	The name of the module that the class was added to
- L20 _prototype_ `DECLARE_DELEGATE_ThreeParams( FOnAddedToProject, const FString& , const FString& , const FString& );` — Delegate called when code is added to the project.  Passes in the created class name and class path @param ClassName		The created class name @param ClassPath		The created class path @param ModuleName	The name of the module that the class was added to

### `Source/Editor/GameProjectGeneration/Public/ClassTemplateEditorSubsystem.h` (Public)


#### class `UClassTemplate`  
`class UClassTemplate : public UObject`  
_L26-65_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L31 _public prototype_ `virtual void BeginDestroy() override;`
- L35 _public prototype_ `virtual FString GetDirectory() const;` — Returns the directory containing the text file template for the given base generated class.
- L39 _public prototype_ `bool ReadHeader(FString& OutHeaderFileText, FText& OutFailReason) const;` — Reads the header template text from disk.  If failure to read from disk, returns false and provides text reason.
- L43 _public prototype_ `bool ReadSource(FString& OutSourceFileText, FText& OutFailReason) const;` — Reads the source template text from disk.  If failure to read from disk, returns false and provides text reason.
- L45 _public prototype_ `const UClass* GetGeneratedBaseClass() const;`
- L49 _protected prototype_ `void SetGeneratedBaseClass(UClass* InClass);` — Sets the generated base class associated with the given template
- L53 _protected prototype_ `virtual FString GetFilename() const;` — Returns the filename associated with the provided class template without an extension.  Defaults to class name.
- L56 _protected prototype_ `FString GetHeaderFilename() const;` — Returns full header filename including '.h.template' extension
- L59 _protected prototype_ `FString GetSourceFilename() const;` — Returns full sourcefilename including '.cpp.template' extension
- L64 _private member_ `TObjectPtr<UClass> GeneratedBaseClass;` — `UPROPERTY(Transient)` — Base UClass of which template class corresponds.

#### class `UPluginClassTemplate`  
`class UPluginClassTemplate : public UClassTemplate`  
_L68-80_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UClassTemplate`
- L75 _public prototype_ `virtual FString GetDirectory() const override;` — Returns the directory containing the text file template for the given base generated class.
- L79 _protected member_ `FString PluginName;` — `UPROPERTY(Transient)`

#### class `UClassTemplateEditorSubsystem`  
`class UClassTemplateEditorSubsystem : public UEditorSubsystem`  
_L83-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L88 _private typedef_ `using FTemplateRegistry = TMap<TWeakObjectPtr<const UClass>, TWeakObjectPtr<const UClassTemplate>>;`
- L89 _private member_ `FTemplateRegistry TemplateRegistry;`
- L92 _public prototype_ `UClassTemplateEditorSubsystem();`
- L94 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L95 _public prototype_ `virtual void Deinitialize() override;`
- L98 _public prototype_ `void RegisterTemplates();` — Registers all currently loaded template classes with the internal registry.
- L101 _public prototype_ `static FString GetEngineTemplateDirectory();` — Returns path to the directory containing all engine class templates.
- L104 _public prototype_ `bool ContainsClassTemplate(const UClass* InClass) const;` — Returns whether or not class has registered template
- L107 _public prototype_ `const UClassTemplate* FindClassTemplate(const UClass* InClass) const;` — Returns class template if one is registered.
- L113 _private prototype_ `void Register(const UClassTemplate* InClassTemplate);` — Registers a template class with the subsystem
- L116 _private prototype_ `bool Unregister(const UClassTemplate* InClassTemplate);` — Unregisters a template class with the subsystem

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GAMEPROJECTGENERATION_API`

### `Source/Editor/GameProjectGeneration/Public/FeaturedClasses.inl` (Public)


#### Free symbols / members of external scopes

- L32 _function_ `FORCEINLINE TArray<FNewClassInfo> FFeaturedClasses::AllNativeClasses()` (scope `FFeaturedClasses`) — Get a list of all featured native class types
- L52 _function_ `FORCEINLINE TArray<FNewClassInfo> FFeaturedClasses::ActorClasses()` (scope `FFeaturedClasses`) — Get a list of all featured Actor class types
- L61 _function_ `FORCEINLINE TArray<FNewClassInfo> FFeaturedClasses::ComponentClasses()` (scope `FFeaturedClasses`) — Get a list of all featured Component class types
- L70 _function_ `FORCEINLINE void FFeaturedClasses::AddCommonActorClasses(TArray<FNewClassInfo>& Array)` (scope `FFeaturedClasses`) — Append the featured Actor class types that are commonly used
- L78 _function_ `FORCEINLINE void FFeaturedClasses::AddExtraActorClasses(TArray<FNewClassInfo>& Array)` (scope `FFeaturedClasses`) — Append the featured Actor class types that are less commonly used
- L90 _function_ `FORCEINLINE void FFeaturedClasses::AddCommonComponentClasses(TArray<FNewClassInfo>& Array)` (scope `FFeaturedClasses`) — Append the featured Component class types that are commonly used
- L97 _function_ `FORCEINLINE void FFeaturedClasses::AddExtraComponentClasses(TArray<FNewClassInfo>& Array)` (scope `FFeaturedClasses`) — Append the featured Component class types that are less commonly used

### `Source/Editor/GameProjectGeneration/Public/GameProjectGenerationModule.h` (Public)


#### class `FGameProjectGenerationModule`  
`class FGameProjectGenerationModule : public IModuleInterface`  
_L29-156_
- inherits: `IModuleInterface`
- desc: Game Project Generation module
- L33 _public typedef_ `typedef TMap<FName, TSharedPtr<FTemplateCategory>> FTemplateCategoryMap;`
- L38 _public prototype_ `virtual void StartupModule();` — Called right after the plugin DLL has been loaded and the plugin object has been created
- L43 _public prototype_ `virtual void ShutdownModule();` — Called before the plugin is unloaded, right before the plugin object is destroyed.
- L51 _public function_ `static inline FGameProjectGenerationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L58 _public prototype_ `virtual TSharedRef<class SWidget> CreateGameProjectDialog(bool bAllowProjectOpening, bool bAllowProjectCreate);` — Creates the game project dialog
- L61 _public prototype_ `virtual TSharedRef<class SWidget> CreateNewClassDialog(const UClass* InClass);` — Creates a new class dialog for creating classes based on the passed-in class.
- L65 _public prototype_ `virtual TSharedRef<class SWidget> CreateProjectBrowser(bool bInShowHeaderBar = true, bool bInAllowScrolling = true);` — `UE_DEPRECATED(5.8, "Use CreateEmbeddedProjectBrowser")` — Creates the project browser widget
- L68 _public prototype_ `virtual TSharedRef<class SWidget> CreateEmbeddedProjectBrowser();` — Creates the embedded project browser widget
- L75 _public prototype_ `virtual void OpenAddCodeToProjectDialog(const FAddToProjectConfig& Config = FAddToProjectConfig());` — Opens a dialog to add code files to the current project. @param	Config		Dialog configuration options
- L82 _public prototype_ `virtual void OpenAddBlueprintToProjectDialog(const FAddToProjectConfig& Config);` — Opens a dialog to add a new blueprint to the current project. @param	Config		Dialog configuration options
- L85 _public prototype_ `DECLARE_EVENT(FGameProjectGenerationModule, FAddCodeToProjectDialogOpenedEvent);` — Delegate for when the AddCodeToProject dialog is opened
- L86 _public function_ `FAddCodeToProjectDialogOpenedEvent& OnAddCodeToProjectDialogOpened()`
- L89 _public prototype_ `virtual void TryMakeProjectFileWriteable(const FString& ProjectFile);` — Tries to make the project file writable. Prompts to check out as necessary.
- L92 _public prototype_ `virtual void CheckForOutOfDateGameProjectFile();` — Prompts the user to update their project file, if necessary.
- L95 _public prototype_ `virtual bool UpdateGameProject(const FString& ProjectFile, const FString& EngineIdentifier, FText& OutFailReason);` — Updates the currently loaded project. Returns true if the project was updated successfully or if no update was needed
- L98 _public prototype_ `virtual bool UpdateCodeProject(FText& OutFailReason, FText& OutFailLog);` — Updates the current code project
- L101 _public prototype_ `virtual bool ProjectHasCodeFiles();` — Gets the current projects source file count
- L104 _public prototype_ `virtual FString DetermineModuleIncludePath(const FModuleContextInfo& ModuleInfo, const FString& FileRelativeTo);` — Returns the path to the module's include header
- L107 _public prototype_ `virtual const TArray<FModuleContextInfo>& GetCurrentProjectModules();` — Get the information about any modules referenced in the .uproject file of the currently loaded project
- L110 _public prototype_ `virtual bool IsValidBaseClassForCreation(const UClass* InClass, const FModuleContextInfo& InModuleInfo);` — Returns true if the specified class is a valid base class for the given module
- L113 _public prototype_ `virtual bool IsValidBaseClassForCreation(const UClass* InClass, const TArray<FModuleContextInfo>& InModuleInfoArray);` — Returns true if the specified class is a valid base class for any of the given modules
- L116 _public prototype_ `virtual void GetProjectSourceDirectoryInfo(int32& OutNumFiles, int64& OutDirectorySize);` — Gets file and size info about the source directory
- L119 _public prototype_ `virtual void CheckAndWarnProjectFilenameValid();` — Warn the user if the project filename is invalid in case they renamed it outside the editor
- L122 _public prototype_ `virtual bool GenerateBasicSourceCode(TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Generate basic project source code
- L131 _public prototype_ `virtual void UpdateSupportedTargetPlatforms(const FName& InPlatformName, const bool bIsSupported);` — Update the list of supported target platforms based upon the parameters provided This will take care of checking out and saving the updated .uproject file automatically @param	InPlatformName		Name of the platform to target (eg, WindowsClient) @param	bIsSupported		true if the platform should be supported by this project, false if it should not
- L134 _public prototype_ `virtual void ClearSupportedTargetPlatforms();` — Clear the list of supported target platforms
- L139 _public prototype_ `virtual bool CreateProject(const FProjectInformation& InProjectInfo, FText& OutFailReason, FText& OutFailLog, TArray<FString>* OutCreatedFiles = nullptr);` — Creates the specified project file and all required folders. If TemplateFile is non-empty, it will be used as the template for creation. On failure, OutFailReason will be populated.
- L142 _public prototype_ `virtual bool OpenProject(const FString& InProjectFile, FText& OutFailReason);` — Opens the specified project, if it exists. Returns true if the project file is valid. On failure, OutFailReason will be populated.
- L145 _public function_ `TSharedPtr<const FTemplateCategory> GetCategory(FName Type) const` — Non DLL-exposed access to template categories
- L147 _public function_ `void GetAllTemplateCategories(TArray<TSharedPtr<FTemplateCategory>>& OutCategories) const`
- L150 _private member_ `FAddCodeToProjectDialogOpenedEvent AddCodeToProjectDialogOpenedEvent;`
- L153 _private member_ `FTemplateCategoryMap TemplateCategories;` — Map of template categories from type to ptr
- L155 _private prototype_ `void LoadTemplateCategories();`

#### Free symbols / members of external scopes

- L85 _delegate_ `DECLARE_EVENT(FGameProjectGenerationModule, FAddCodeToProjectDialogOpenedEvent);` — Delegate for when the AddCodeToProject dialog is opened

### `Source/Editor/GameProjectGeneration/Public/GameProjectUtils.h` (Public)


#### struct `FProjectInformation`  
`struct FProjectInformation`  
_L35-55_
- L37 _public prototype_ `FProjectInformation() = default;`
- L39 _public member_ `FString ProjectFilename;`
- L40 _public member_ `FString TemplateFile;`
- L41 _public member_ `FName TemplateCategory;`
- L42 _public member_ `FName Variant;`
- L44 _public member_ `bool bShouldGenerateCode = false;`
- L45 _public member_ `bool bIsBlankTemplate = false;`
- L46 _public member_ `bool bIsEnterpriseProject = false;`
- L51 _public member_ `TOptional<bool> bEnableXR;` — These are all optional, because there is an additional state introduced by hiding the setting in the template. In this case, the template author has chosen not to give the user a choice, so we must assume that the template already controls these settings explicitly.
- L53 _public member_ `TOptional<EHardwareClass> TargetedHardware;`
- L54 _public member_ `TOptional<EGraphicsPreset> DefaultGraphicsPerformance;`

#### class `GameProjectUtils`  
`class GameProjectUtils`  
_L59-567_
- L118 _public prototype_ `static bool IsValidProjectFileForCreation(const FString& ProjectFile, FText& OutFailReason);` — Returns true if the project filename is properly formed and does not conflict with another project
- L121 _public prototype_ `static bool OpenProject(const FString& ProjectFile, FText& OutFailReason);` — Opens the specified project, if it exists. Returns true if the project file is valid. On failure, OutFailReason will be populated.
- L124 _public prototype_ `static bool OpenCodeIDE(const FString& ProjectFile, FText& OutFailReason);` — Opens the code editing IDE for the specified project, if it exists. Returns true if the IDE could be opened. On failure, OutFailReason will be populated.
- L127 _public prototype_ `static bool CreateProject(const FProjectInformation& InProjectInfo, FText& OutFailReason, FText& OutFailLog, TArray<FString>* OutCreatedFiles = nullptr);` — Creates the specified project file and all required folders. If TemplateFile is non-empty, it will be used as the template for creation. On failure, OutFailReason will be populated.
- L130 _public prototype_ `static void CheckForOutOfDateGameProjectFile();` — Prompts the user to update their project file, if necessary.
- L133 _public prototype_ `static void CheckAndWarnProjectFilenameValid();` — Warn the user if the project filename is invalid in case they renamed it outside the editor
- L136 _public prototype_ `static void TryMakeProjectFileWriteable(const FString& ProjectFile);` — Checks out the current project file (or prompts to make writable)
- L139 _public prototype_ `static bool UpdateGameProject(const FString& ProjectFile, const FString& EngineIdentifier, FText& OutFailReason);` — Updates the given project file to an engine identifier. Returns true if the project was updated successfully or if no update was needed
- L147 _public prototype_ `static void OpenAddToProjectDialog(const FAddToProjectConfig& Config, EClassDomain InDomain);` — Opens a dialog to add code files or blueprints to the current project. @param	Config			Configuration options for the dialog @param	InDomain		The domain of the class we're creating (native or blueprint)
- L150 _public prototype_ `static bool IsValidClassNameForCreation(const FString& NewClassName, FText& OutFailReason);` — Returns true if the specified class name is properly formed and does not conflict with another class
- L153 _public prototype_ `static bool IsValidClassNameForCreation(const FString& NewClassName, const FModuleContextInfo& ModuleInfo, const TSet<FString>& DisallowedHeaderNames, FText& OutFailReason);` — Returns true if the specified class name is properly formed and does not conflict with another class, including source/header files
- L156 _public prototype_ `static bool IsValidBaseClassForCreation(const UClass* InClass, const FModuleContextInfo& InModuleInfo);` — Returns true if the specified class is a valid base class for the given module
- L159 _public prototype_ `static bool IsValidBaseClassForCreation(const UClass* InClass, const TArray<FModuleContextInfo>& InModuleInfoArray);` — Returns true if the specified class is a valid base class for any of the given modules
- L162 _public prototype_ `static EAddCodeToProjectResult AddCodeToProject(const FString& NewClassName, const FString& NewClassPath, const FModuleContextInfo& ModuleInfo, const FNewClassInfo ParentClassInfo, const TSet<FString>& DisallowedHeaderNames, FString& OutHeaderFilePath, FString& OutCppFilePath, FText& OutFailReason);` — Adds new source code to the project. When returning Succeeded or FailedToHotReload, OutSyncFileAndLineNumber will be the the preferred target file to sync in the users code editing IDE, formatted for use with GenericApplication::GotoLineInSource
- L168 _public prototype_ `static UTemplateCategories* LoadTemplateCategories(const FString& RootDir);` — Loads a list of template categories defined in the TemplateCategories.ini file in the specified folder
- L171 _public prototype_ `static UTemplateProjectDefs* LoadTemplateDefs(const FString& ProjectDirectory);` — Loads a template project definitions object from the TemplateDefs.ini file in the specified project
- L174 _public prototype_ `static int32 GetProjectCodeFileCount();` — @return The number of code files in the currently loaded project
- L181 _public prototype_ `static void GetProjectSourceDirectoryInfo(int32& OutNumFiles, int64& OutDirectorySize);` — Retrieves file and size info about the project's source directory @param OutNumFiles Contains the number of files within the source directory @param OutDirectorySize Contains the combined size of all files in the directory
- L184 _public prototype_ `static FString GetDefaultProjectTemplateFilename();` — Returns the uproject template filename for the default project template.
- L187 _public prototype_ `static bool BuildCodeProject(const FString& ProjectFilename);` — Compiles a project while showing a progress bar, and offers to open the IDE if it fails.
- L190 _public prototype_ `static bool GenerateCodeProjectFiles(const FString& ProjectFilename, FText& OutFailReason, FText& OutFailLog);` — Creates code project files for a new game project. On failure, OutFailReason and OutFailLog will be populated.
- L194 _public function_ `static bool IsEngineStarterContentAvailable()` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — Returns true if there are engine starter content files available for instancing into new projects.
- L198 _public function_ `static bool IsUsingEngineStarterContent(const FProjectInformation& ProjectInfo)` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — Returns true if the given project is referencing engine starter content pack.
- L202 _public function_ `static bool IsStarterContentAvailableForProject(const FProjectInformation& ProjectInfo)` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — Returns true if there are any starter content packs are available for given project.
- L207 _public prototype_ `static const TArray<FModuleContextInfo>& GetCurrentProjectModules();` — Get the information about any modules referenced in the .uproject file of the currently loaded project
- L212 _public prototype_ `static TArray<FModuleContextInfo> GetCurrentProjectPluginModules();` — Get the information about any modules in any of the plugins in the currently loaded project (Ignores Engine Plugins)
- L217 _public prototype_ `static void ResetCurrentProjectModulesCache();` — Reset the cached result of information about any modules referenced in the .uproject file of the currently loaded project
- L228 _public prototype_ `static bool IsValidSourcePath(const FString& InPath, const FModuleContextInfo& ModuleInfo, FText* const OutFailReason = nullptr);` — Check to see if the given path is a valid place to put source code for this project (exists within the source root path) @param	InPath				The path to check @param	ModuleInfo			Information about the module being validated @param	OutFailReason		Optional parameter to fill with failure information @return	true if the path is valid, false otherwise
- L241 _public prototype_ `static bool CalculateSourcePaths(const FString& InPath, const FModuleContextInfo& ModuleInfo, FString& OutHeaderPath, FString& OutSourcePath, FText* const OutFailReason = nullptr);` — Given the path provided, work out where generated .h and .cpp files would be placed @param	InPath				The path to use a base @param	ModuleInfo			Information about the module being validated @param	OutHeaderPath		The path where the .h file should be placed @param	OutSourcePath		The path where the .cpp file should be placed @param	OutFailReason		Optional parameter to fill with failure information @return	false if the paths are invalid
- L253 _public prototype_ `static bool GetClassLocation(const FString& InPath, const FModuleContextInfo& ModuleInfo, EClassLocation& OutClassLocation, FText* const OutFailReason = nullptr);` — Given the path provided, work out where it's located within the Source folder @param	InPath				The path to use a base @param	ModuleInfo			Information about the module being validated @param	OutClassLocation	The location within the Source folder @param	OutFailReason		Optional parameter to fill with failure information @return	false if the paths are invalid
- L256 _public prototype_ `static EProjectDuplicateResult DuplicateProjectForUpgrade( const FString& InProjectFile, FString& OutNewProjectFile );` — Creates a copy of a project directory in order to upgrade it.
- L265 _public prototype_ `static void UpdateSupportedTargetPlatforms(const FName& InPlatformName, const bool bIsSupported);` — Update the list of supported target platforms based upon the parameters provided This will take care of checking out and saving the updated .uproject file automatically @param	InPlatformName		Name of the platform to target (eg, WindowsClient) @param	bIsSupported		true if the platform should be supported by this project, false if it should not
- L268 _public prototype_ `static void ClearSupportedTargetPlatforms();` — Clear the list of supported target platforms
- L271 _public prototype_ `static FString DetermineModuleIncludePath(const FModuleContextInfo& ModuleInfo, const FString& FileRelativeTo);` — Returns the path to the module's include header
- L274 _public prototype_ `static bool GenerateBasicSourceCode(TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Creates the basic source code for a new project. On failure, OutFailReason will be populated.
- L277 _public prototype_ `static bool GenerateGameModuleBuildFile(const FString& NewBuildFileName, const FString& ModuleName, const TArray<FString>& PublicDependencyModuleNames, const TArray<FString>& PrivateDependencyModuleNames, FText& OutFailReason);` — Generates a Build.cs file for a game module
- L280 _public prototype_ `static bool GeneratePluginModuleBuildFile(const FString& NewBuildFileName, const FString& ModuleName, const TArray<FString>& PublicDependencyModuleNames, const TArray<FString>& PrivateDependencyModuleNames, FText& OutFailReason, bool bUseExplicitOrSharedPCHs = true);` — Generates a Build.cs file for a plugin module. Set 'bUseExplicitOrSharedPCHs' to false to disable IWYU conventions.
- L283 _public prototype_ `static bool GeneratePluginModuleCPPFile(const FString& CPPFileName, const FString& ModuleName, const FString& StartupSourceCode, FText& OutFailReason);` — Generates a module .cpp file, intended for plugin use
- L286 _public prototype_ `static bool GeneratePluginModuleHeaderFile(const FString& HeaderFileName, const TArray<FString>& PublicHeaderIncludes, FText& OutFailReason);` — Generates a module .h file, intended for plugin use
- L289 _public prototype_ `static bool ProjectHasCodeFiles();` — Returns true if the currently loaded project has code files
- L292 _public prototype_ `static bool ReadTemplateFile(const FString& TemplateFileName, FString& OutFileContents, FText& OutFailReason);` — Returns the contents of the specified template file
- L295 _public prototype_ `static bool WriteOutputFile(const FString& OutputFilename, const FString& OutputFileContents, FText& OutFailReason);` — Writes an output file. OutputFilename includes a path
- L298 _public prototype_ `static FString MakeCommaDelimitedList(const TArray<FString>& InList, bool bPlaceQuotesAroundEveryElement = true);` — Returns a comma delimited string comprised of all the elements in InList. If bPlaceQuotesAroundEveryElement, every element is within quotes.
- L301 _public prototype_ `static bool NameContainsOnlyLegalCharacters(const FString& TestName, FString& OutIllegalCharacters);` — Checks the name for illegal characters
- L304 _public prototype_ `static bool NameMatchesPlatformModuleName(const FString& TestName);` — Checks the name to see if it matches platform module names
- L307 _public prototype_ `static FString MakeIncludeList(const TArray<FString>& InList);` — Returns a list of #include lines formed from InList
- L310 _public prototype_ `static void DeleteCreatedFiles(const FString& RootFolder, const TArray<FString>& CreatedFiles);` — Deletes the specified list of files that were created during file creation
- L320 _public prototype_ `static bool UpdateAdditionalPluginDirectory(const FString& InDir, const bool bAddOrRemove);` — Update the list of plugin directories to scan This will take care of checking out and saving the updated .uproject file automatically @param	InDir directory to add/remove @param	bAddOrRemove true if the directory should be added to this project, false if it should not @return Whether the plugin directory list was changed
- L323 _public prototype_ `static const TCHAR* GetDefaultBuildSettingsVersion();` — Gets the default build settings version for UBT
- L328 _private prototype_ `static void AddHardwareConfigValues(const FProjectInformation& InProjectInfo, TArray<FTemplateConfigValue>& ConfigValues);` — Add hardware-specific config values such as the target platform and RHI.
- L332 _private function_ `static FString GetStarterContentName(const FProjectInformation& InProjectInfo)` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — Get the name of the starter content pack to use for the given project.
- L335 _private prototype_ `static TOptional<FGuid> GenerateProjectFromScratch(const FProjectInformation& InProjectInfo, FText& OutFailReason, FText& OutFailLog);` — Generates a new project without using a template project
- L338 _private prototype_ `static TOptional<FGuid> CreateProjectFromTemplate(const FProjectInformation& InProjectInfo, FText& OutFailReason, FText& OutFailLog, TArray<FString>* OutCreatedFiles = nullptr);` — Generates a new project using a template project
- L341 _private prototype_ `static bool SetEngineAssociationForForeignProject(const FString& ProjectFileName, FText& OutFailReason);` — Sets the engine association for a new project. Handles foreign and non-foreign projects.
- L345 _private prototype_ `static bool InsertFeaturePacksIntoINIFile(const FProjectInformation& InProjectInfo, FText& OutFailReason);` — `UE_DEPRECATED(5.6, "Ability to add Starter Content has been removed")` — Insert any required feature packs into the DefaultGame.ini file
- L355 _private prototype_ `static bool AddSharedContentToProject(const FProjectInformation &InProjectInfo, TArray<FString> &CreatedFiles, FText& OutFailReason);` — Insert the addition files from any feature packs specified in the temapalte defs file @param InProjectInfo		Project infor to add content for @param CreatedFiles		List of files we copied @param OutFailReason		Failure reason (if any) @returns true if no errors
- L358 _private prototype_ `static FString GetTemplateDefsFilename();` — Returns the template defs ini filename
- L361 _private prototype_ `static FString GetIncludePathForFile(const FString& InFullFilePath, const FString& ModuleRootPath);` — Returns the include header path for a given fully specified, normalized file path
- L364 _private prototype_ `static bool ProjectFileExists(const FString& ProjectFile);` — Returns true if the project file exists on disk
- L367 _private prototype_ `static bool AnyProjectFilesExistInFolder(const FString& Path);` — Returns true if any project files exist in the given folder
- L370 _private prototype_ `static bool CleanupIsEnabled();` — Returns true if file cleanup on failure is enabled, false if not
- L373 _private prototype_ `static bool GenerateConfigFiles(const FProjectInformation& InProjectInfo, TArray<FString>& OutCreatedFiles, FText& OutFailReason, FGuid& OutProjectID);` — Creates ini files for a new project. On failure, OutFailReason will be populated.
- L376 _private prototype_ `static bool GeneratePlatformConfigFiles(const FProjectInformation& InProjectInfo, FText& OutFailReason);` — Creates new ini files for a specific project's platform configurations.
- L379 _private prototype_ `static bool GenerateBasicSourceCode(const FString& NewProjectSourcePath, const FString& NewProjectName, const FString& NewProjectRoot, TArray<FString>& OutGeneratedStartupModuleNames, TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Creates the basic source code for a new project. On failure, OutFailReason will be populated.
- L382 _private prototype_ `static bool GenerateGameFrameworkSourceCode(const FString& NewProjectSourcePath, const FString& NewProjectName, TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Creates the game framework source code for a new project (Pawn, GameMode, PlayerControlleR). On failure, OutFailReason will be populated.
- L385 _private prototype_ `static bool GenerateCodeProjectGenerationBatchFile(const FString& ProjectFolder, TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Creates the batch file to regenerate code projects.
- L388 _private prototype_ `static bool GenerateLaunchBatchFile(const FString& ProjectName, const FString& ProjectFolder, bool bLaunchEditor, TArray<FString>& OutCreatedFiles, FText& OutFailReason);` — Creates the batch file for launching the editor or game
- L391 _private prototype_ `static FString MakeCopyrightLine();` — Returns the copyright line used at the top of all files
- L394 _private prototype_ `static bool GenerateClassHeaderFile(const FString& NewHeaderFileName, const FString UnPrefixedClassName, const FNewClassInfo ParentClassInfo, const TArray<FString>& ClassSpecifierList, const FString& ClassProperties, const FString& ClassFunctionDeclarations, FString& OutSyncLocation, const FModuleContextInfo& ModuleInfo, bool bDeclareConstructor, FText& OutFailReason);` — Generates a header file for a UObject class. OutSyncLocation is a string representing the preferred cursor sync location for this file after creation.
- L397 _private prototype_ `static void HarvestCursorSyncLocation( FString& FinalOutput, FString& OutSyncLocation );` — Finds the cursor sync location in the source file and reports it back as a string
- L400 _private prototype_ `static bool GenerateClassCPPFile(const FString& NewCPPFileName, const FString UnPrefixedClassName, const FNewClassInfo ParentClassInfo, const TArray<FString>& AdditionalIncludes, const TArray<FString>& PropertyOverrides, const FString& AdditionalMemberDefinitions, FString& OutSyncLocation, const FModuleContextInfo& ModuleInfo, FText& OutFailReason);` — Generates a cpp file for a UObject class
- L403 _private prototype_ `static bool GenerateGameModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason);` — Generates a Target.cs file for a game module
- L406 _private prototype_ `static bool GenerateEditorModuleBuildFile(const FString& NewBuildFileName, const FString& ModuleName, const TArray<FString>& PublicDependencyModuleNames, const TArray<FString>& PrivateDependencyModuleNames, FText& OutFailReason);` — Generates a Build.cs file for a Editor module
- L409 _private prototype_ `static bool GenerateEditorModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason);` — Generates a Target.cs file for a Editor module
- L412 _private prototype_ `static bool GenerateGameModuleCPPFile(const FString& NewGameModuleCPPFileName, const FString& ModuleName, const FString& GameName, FText& OutFailReason);` — Generates a main game module cpp file
- L415 _private prototype_ `static bool GenerateGameModuleHeaderFile(const FString& NewGameModuleHeaderFileName, const TArray<FString>& PublicHeaderIncludes, FText& OutFailReason);` — Generates a main game module header file
- L428 _private prototype_ `static FString ReplaceWildcard(const FString& Input, const FString& From, const FString& To, bool bLeadingTab = false, bool bTrailingNewLine = false);` — Replace a wildcard with another string @param Input				The input string @param From				The wildcard to be replaced @param To					The text the wildcard should be replaced with @param bLeadingTab		If the line where the wildcard is located starts with a tab @param bTrailingNewLine	If the line where the wildcard is located ends with a new line @return the input string after replacement of the wildcard
- L431 _private prototype_ `static void OnUpdateProjectConfirm();` — Handler for when the user confirms a project update
- L434 _private prototype_ `static void GetProjectCodeFilenames(TArray<FString>& OutProjectCodeFilenames);` — @param OutProjectCodeFilenames Contains the filenames of the project source code files
- L441 _private prototype_ `static void UpdateProject(const FProjectDescriptorModifier& Modifier);` — Updates the projects and modifies FProjectDescriptor accordingly to given modifier. @param Modifier	Callback delegate that will modify the project descriptor accordingly.
- L446 _private prototype_ `static void UpdateProject();` — Updates the project file.
- L453 _private prototype_ `static void UpdateProject(const TArray<FString>* StartupModuleNames);` — Updates the projects, and optionally the modules names @param StartupModuleNames	if specified, replaces the existing module names with this version
- L456 _private prototype_ `static void OnUpdateProjectCancel();` — Handler for when the user opts out of a project update
- L468 _private prototype_ `static bool UpdateGameProjectFile(const FString& ProjectFilename, const FString& EngineIdentifier, const TArray<FString>* StartupModuleNames, FText& OutFailReason);` — Updates the loaded game project file to the current version and to use the given modules @param ProjectFilename		The name of the project (used to checkout from source control) @param EngineIdentifier		The identifier for the engine to open the project with @param StartupModuleNames	if specified, replaces the existing module names with this version @param OutFailReason			Out, if unsuccessful this is the reason why @return true, if successful
- L480 _private prototype_ `static bool UpdateGameProjectFile(const FString& ProjectFilename, const FString& EngineIdentifier, const FProjectDescriptorModifier& Modifier, FText& OutFailReason);` — Updates the loaded game project file to the current version and modifies FProjectDescriptor accordingly to given modifier. @param ProjectFilename		The name of the project (used to checkout from source control) @param EngineIdentifier		The identifier for the engine to open the project with @param Modifier				Callback delegate that will modify the project descriptor accordingly. @param OutFailReason			Out, if unsuccessful this is the reason why @return true, if successful
- L491 _private prototype_ `static bool UpdateGameProjectFile(const FString& ProjectFilename, const FString& EngineIdentifier, FText& OutFailReason);` — Updates the loaded game project file to the current version. @param ProjectFilename		The name of the project (used to checkout from source control) @param EngineIdentifier		The identifier for the engine to open the project with @param OutFailReason			Out, if unsuccessful this is the reason why @return true, if successful
- L494 _private prototype_ `static bool CheckoutGameProjectFile(const FString& ProjectFilename, FText& OutFailReason);` — Checks the specified game project file out from source control
- L497 _private prototype_ `static EAddCodeToProjectResult AddCodeToProject_Internal(const FString& NewClassName, const FString& NewClassPath, const FModuleContextInfo& ModuleInfo, const FNewClassInfo ParentClassInfo, const TSet<FString>& DisallowedHeaderNames, FString& OutHeaderFilePath, FString& OutCppFilePath, FText& OutFailReason, EReloadStatus& OutReloadStatus);` — Internal handler for AddCodeToProject
- L500 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDoesClassNeedAPIExportCallback, const FString& );` — Internal handler for IsValidBaseClassForCreation
- L501 _private prototype_ `static bool IsValidBaseClassForCreation_Internal(const UClass* InClass, const FDoesClassNeedAPIExportCallback& InDoesClassNeedAPIExport);`
- L504 _private prototype_ `static void OnWarningReasonOk();` — Handler for the user confirming they've read the name legnth warning
- L507 _private prototype_ `static bool FindSourceFileInProject(const FString& InFilename, const FString& InSearchPath, FString& OutPath);` — Given a source file name, find its location within the project
- L516 _private prototype_ `static TArray<FString> GetRequiredAdditionalDependencies(const FNewClassInfo& ClassInfo);` — Gets required additional dependencies for fresh project for given class info. @param ClassInfo Given class info. @returns Array of required dependencies.
- L526 _private prototype_ `static bool UpdateStartupModuleNames(FProjectDescriptor& Descriptor, const TArray<FString>* StartupModuleNames);` — Updates startup module names in project descriptor. @param Descriptor Descriptor to update. @param StartupModuleNames Modules to fill. @returns True if descriptor has been modified. False otherwise.
- L537 _private prototype_ `static bool UpdateRequiredAdditionalDependencies(FProjectDescriptor& Descriptor, TArray<FString>& RequiredDependencies, const FString& ModuleName);` — Updates additional dependencies in project descriptor. @param Descriptor Descriptor to update. @param RequiredDependencies Required dependencies. @param ModuleName Module name for which those dependencies are required. @returns True if descriptor has been modified. False otherwise.
- L544 _private prototype_ `static void UpdateProject_Impl(const FProjectDescriptorModifier* Modifier);` — Updates the projects and modifies FProjectDescriptor accordingly to given modifier. @param Modifier	Callback delegate that will modify the project descriptor accordingly.
- L556 _private prototype_ `static bool UpdateGameProjectFile_Impl(const FString& ProjectFilename, const FString& EngineIdentifier, const FProjectDescriptorModifier* Modifier, FText& OutFailReason);` — Updates the loaded game project file to the current version and modifies FProjectDescriptor accordingly to given modifier. @param ProjectFilename		The name of the project (used to checkout from source control) @param EngineIdentifier		The identifier for the engine to open the project with @param Modifier				Callback delegate that will modify the project descriptor accordingly. @param OutFailReason			Out, if unsuccessful this is the reason why @return true, if successful
- L560 _private member_ `static TWeakPtr<SNotificationItem> UpdateGameProjectNotification;`
- L561 _private member_ `static TWeakPtr<SNotificationItem> WarningProjectNameNotification;`
- L564 _private member_ `static bool bUseAudioMixerForAllPlatforms;` — Whether we should use AudioMixer for all platforms:
- L566 _private member_ `constexpr static const TCHAR IncludePathFormatString[] = TEXT("#in`

#### enum `GameProjectUtils::EClassLocation`  
`enum class EClassLocation : uint8`  
_L63-76_
- desc: Where is this class located within the Source folder?
- L66 _public enumerator_ `UserDefined` — The class is going to a user defined location (outside of the Public, Private, or Classes) folder for this module
- L69 _public enumerator_ `Public` — The class is going to the Public folder for this module
- L72 _public enumerator_ `Private` — The class is going to the Private folder for this module
- L75 _public enumerator_ `Classes` — The class is going to the Classes folder for this module

#### enum `GameProjectUtils::EAddCodeToProjectResult`  
`enum class EAddCodeToProjectResult : uint8`  
_L79-92_
- desc: Used as a function return result when adding new code to the project
- L82 _public enumerator_ `Succeeded` — Function has successfully added the code and hot-reloaded the required module(s)
- L85 _public enumerator_ `InvalidInput` — There were errors with the input given to the function
- L88 _public enumerator_ `FailedToAddCode` — There were errors when adding the new source files
- L91 _public enumerator_ `FailedToHotReload` — There were errors when hot-reloading the new module

#### enum `GameProjectUtils::EProjectDuplicateResult`  
`enum class EProjectDuplicateResult : uint8`  
_L95-105_
- desc: Used as a function return result when a project is duplicated when upgrading project's version in Convert project dialog - Open a copy
- L98 _public enumerator_ `Succeeded` — Function has successfully duplicated all project files
- L101 _public enumerator_ `Failed` — There were errors while duplicating project files
- L104 _public enumerator_ `UserCanceled` — User has canceled project duplication process

#### enum `GameProjectUtils::EReloadStatus`  
`enum class EReloadStatus : uint8`  
_L108-115_
- desc: Reload status when adding new code to the project
- L111 _public enumerator_ `Reloaded` — Code was built and reloaded
- L114 _public enumerator_ `NotReloaded` — Code was not reloaded

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GAMEPROJECTGENERATION_API`
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FProjectDescriptorModifier, FProjectDescriptor&);`
- L57 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FProjectDescriptorModifier, FProjectDescriptor&);`
- L500 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDoesClassNeedAPIExportCallback, const FString& );` — Internal handler for IsValidBaseClassForCreation
