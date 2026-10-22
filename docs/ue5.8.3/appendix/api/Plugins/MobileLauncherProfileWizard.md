# Plugins / MobileLauncherProfileWizard

- module root: `Plugins/Editor/MobileLauncherProfileWizard/Source/MobileLauncherProfileWizard`
- headers: 4; symbols: 77
- symbol kinds: class=4, delegate=1, enum=2, enumerator=6, function=3, member=15, namespace=3, prototype=42, struct=1
- PrivateDependencyModuleNames: AppFramework, CoreUObject, DesktopPlatform, InputCore, Json, LauncherServices, Projects, Slate, SlateCore, TargetPlatform
- PublicDependencyModuleNames: Core

### `Plugins/Editor/MobileLauncherProfileWizard/Source/MobileLauncherProfileWizard/Private/AndroidProfileWizard.h` (Private)


#### class `FAndroidProfileWizard`  
`class FAndroidProfileWizard : public ILauncherProfileWizard`  
_L6-12_
- inherits: `ILauncherProfileWizard`
- L9 _public prototype_ `virtual FText GetName() const override;`
- L10 _public prototype_ `virtual FText GetDescription() const override;`
- L11 _public prototype_ `virtual void HandleCreateLauncherProfile(const ILauncherProfileManagerRef& ProfileManager) override;`

### `Plugins/Editor/MobileLauncherProfileWizard/Source/MobileLauncherProfileWizard/Private/IOSProfileWizard.h` (Private)


#### class `FIOSProfileWizard`  
`class FIOSProfileWizard : public ILauncherProfileWizard`  
_L6-12_
- inherits: `ILauncherProfileWizard`
- L9 _public prototype_ `virtual FText GetName() const override;`
- L10 _public prototype_ `virtual FText GetDescription() const override;`
- L11 _public prototype_ `virtual void HandleCreateLauncherProfile(const ILauncherProfileManagerRef& ProfileManager) override;`

### `Plugins/Editor/MobileLauncherProfileWizard/Source/MobileLauncherProfileWizard/Private/SProfileWizardUI.h` (Private)


#### enum `EProfileTarget::Type`  
`enum Type`  
_L15-21_
- L17 _public enumerator_ `Application`
- L18 _public enumerator_ `DLC`
- L20 _public enumerator_ `Num`

#### enum `EProfilePlatform::Type`  
`enum Type`  
_L26-32_
- L28 _public enumerator_ `Android`
- L29 _public enumerator_ `IOS`
- L31 _public enumerator_ `Num`

#### struct `FProfileParameters`  
`struct FProfileParameters`  
_L35-42_
- L37 _public member_ `EBuildConfiguration BuildConfiguration;`
- L38 _public member_ `FString ArchiveDirectory;`
- L39 _public member_ `TArray<FString> AppMaps;`
- L40 _public member_ `TArray<FString> DLCMaps;`
- L41 _public member_ `TArray<FString> DLCCookFlavors;`

#### class `SProfileWizardUI`  
`class SProfileWizardUI : public SCompoundWidget`  
_L46-199_
- inherits: `SCompoundWidget`
- L49 _public prototype_ `SProfileWizardUI();`
- L51 _public function_ `SLATE_BEGIN_ARGS(SProfileWizardUI)`
- L55 _public prototype_ `SLATE_ARGUMENT(EProfilePlatform::Type, ProfilePlatform)` — Platform we target
- L70 _private prototype_ `TSharedRef<SWidget> MakeBuildConfigurationMenuContent();` — Generate menu content for build configuration widget
- L73 _private prototype_ `void HandleBuildConfigurationMenuEntryClicked(EBuildConfiguration Configuration);` — Handle build configuration selection
- L76 _private prototype_ `FText GetBuildConfigurationSelectorText() const;` — Get a text for a selected build configuration
- L79 _private prototype_ `TSharedRef<ITableRow> HandleMapListViewGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable, EProfileTarget::Type InProfileTarget);` — Generate a widget for specified map
- L82 _private prototype_ `ECheckBoxState HandleMapListViewCheckBoxIsChecked(TSharedPtr<FString> InMapName, EProfileTarget::Type InProfileTarget) const;` — Whether specified map is selected
- L85 _private prototype_ `void HandleMapListViewCheckBoxCheckStateChanged(ECheckBoxState NewState, TSharedPtr<FString> InMapName, EProfileTarget::Type InProfileTarget);` — Handle specified map state
- L88 _private prototype_ `TSharedRef<ITableRow> HandleCookFlavorViewGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a widget for specified cook flavor
- L91 _private prototype_ `ECheckBoxState HandleCookFlavorViewCheckBoxIsChecked(TSharedPtr<FString> InItem) const;` — Whether specified cook flavor is selected
- L94 _private prototype_ `void HandleCookFlavorViewCheckBoxCheckStateChanged(ECheckBoxState NewState, TSharedPtr<FString> InMapName);` — Handle specified cook flavor state
- L97 _private prototype_ `bool IsCookFlavorEnabled() const;` — Whether cook flavor list widget in enabled
- L100 _private prototype_ `void HandleAllMapsButton(bool bSelect, EProfileTarget::Type InProfileTarget);` — Handle select all/no maps button
- L103 _private prototype_ `bool CanShowApplicationPage() const;` — Whether wizard can proceed to Application page
- L106 _private prototype_ `bool CanShowDLCPage() const;` — Whether wizard can proceed to DLC page
- L109 _private prototype_ `FText GetApplicationPageTitleText() const;` — Gets the Title text for application page
- L112 _private prototype_ `FText GetApplicationPageDescriptionText() const;` — Gets the Desciption text for application page
- L115 _private prototype_ `FText GetApplicationPageSummaryText() const;` — Gets the Summary text for application page
- L118 _private prototype_ `FText GetDLCPageTitleText() const;` — Gets the Title text for DLC page
- L121 _private prototype_ `FText GetDLCPageDescriptionText() const;` — Gets the Desciption text for DLC page
- L124 _private prototype_ `EVisibility GetNameErrorLabelVisibility() const;` — Gets the visibility of the name error label
- L127 _private prototype_ `FText GetNameErrorLabelText() const;` — Gets the text to display in the name error label
- L130 _private prototype_ `EVisibility GetGlobalErrorLabelVisibility() const;` — Gets the visibility of the global error label
- L133 _private prototype_ `FText GetGlobalErrorLabelText() const;` — Gets the text to display in the global error label
- L136 _private prototype_ `void CancelClicked();` — Handler for when cancel is clicked
- L139 _private prototype_ `bool CanFinish() const;` — Returns true if Finish is allowed
- L142 _private prototype_ `void FinishClicked();` — Handler for when finish is clicked
- L145 _private prototype_ `FText GetDestinationDirectoryText() const;` — Get archive directory text
- L148 _private prototype_ `FReply HandleBrowseDestinationButtonClicked();` — Handle browse button for archive directory
- L151 _private prototype_ `void OnDestinationDirectoryTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Handle commit event for archive directory text
- L154 _private prototype_ `FText GetDestinationPageTitleText() const;` — Get destination page title text
- L157 _private prototype_ `FText GetDestinationPageDescriptionText() const;` — Get destination page description text
- L161 _private prototype_ `void CacheProjectMapList();` — Cache project avaiable maps
- L164 _private prototype_ `void CacheCookFlavorsList();` — Cache project avaiable cook flavors
- L167 _private prototype_ `void CloseContainingWindow();` — Closes the window that contains this widget
- L171 _private member_ `TSharedPtr<SWizard> MainWizard;` — The wizard widget
- L174 _private member_ `EProfilePlatform::Type ProfilePlatform;` — Platform we target: Android or IOS
- L177 _private member_ `FString ProjectPath;` — Full path to project we target
- L180 _private member_ `EBuildConfiguration BuildConfiguration;` — Selected project build configuration
- L183 _private member_ `TArray<TSharedPtr<FString>> ProjectMapList;` — Cached list of project maps
- L186 _private member_ `TSet<FString> SelectedMaps[EProfileTarget::Num];` — Selected maps for each profile: Application and DLC
- L189 _private member_ `TArray<TSharedPtr<FString>> DLCFlavorList;` — Available cook flavors for target platform DLC
- L192 _private member_ `TSet<FString> DLCSelectedFlavors;` — Selected cook flavors for target platform DLC
- L195 _private member_ `FString ArchiveDirectory;` — Directory where to store build products
- L198 _private member_ `FCreateProfileEvent OnCreateProfileEvent;` — Event on CreateProfile action

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace ETextCommit`
- L13 _namespace_ `namespace EProfileTarget`
- L24 _namespace_ `namespace EProfilePlatform`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FCreateProfileEvent, const FProfileParameters& );`
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FCreateProfileEvent, const FProfileParameters& );`

### `Plugins/Editor/MobileLauncherProfileWizard/Source/MobileLauncherProfileWizard/Public/IMobileLauncherProfileWizard.h` (Public)


#### class `IMobileLauncherProfileWizardModule`  
`class IMobileLauncherProfileWizardModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMobileLauncherProfileWizardModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
