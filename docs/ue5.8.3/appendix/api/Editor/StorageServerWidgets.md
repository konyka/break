# Editor / StorageServerWidgets

- module root: `Source/Editor/StorageServerWidgets`
- headers: 17; symbols: 465
- symbol kinds: class=19, delegate=6, enum=3, enumerator=12, function=25, macro=12, member=175, namespace=16, prototype=184, struct=11, typedef=2
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, InputCore, Json, Projects, Slate, SlateCore, ToolWidgets, Zen

### `Source/Editor/StorageServerWidgets/Internal/BuildSelectionInternal.h` (Internal)


#### struct `UE::BuildSelection::Internal::FArtifact`  
`struct FArtifact`  
_L12-16_
- L14 _public member_ `TSet<FName> Configurations;`
- L15 _public member_ `UE::Zen::Build::FBuildServiceInstance::FBuildRecord BuildRecord;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace BuildSelection` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::BuildSelection`)
- L18 _prototype_ `void ConformSelection(TSharedPtr<FString>& SelectedItem, const TArray<TSharedPtr<FString>>& SelectionList);` (scope `UE::BuildSelection::Internal`)
- L20 _prototype_ `bool WriteSetting(FStringView InSectionName, FStringView InKeyName, FStringView InValue);` (scope `UE::BuildSelection::Internal`)
- L21 _prototype_ `bool WriteSetting(FStringView InKeyName, FStringView InValue);` (scope `UE::BuildSelection::Internal`)
- L22 _prototype_ `bool ReadSetting(FStringView InSectionName, FStringView InKeyName, FString& OutValue);` (scope `UE::BuildSelection::Internal`)
- L23 _prototype_ `bool ReadSetting(FStringView InKeyName, FString& OutValue);` (scope `UE::BuildSelection::Internal`)

### `Source/Editor/StorageServerWidgets/Internal/BuildServiceInstanceManager.h` (Internal)


#### class `UE::Zen::Build::FServiceInstanceManager`  
`class FServiceInstanceManager`  
_L14-20_
- L17 _public prototype_ `TSharedPtr<FBuildServiceInstance> GetBuildServiceInstance() const;`
- L19 _private member_ `mutable TSharedPtr<FBuildServiceInstance> CurrentInstance;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Zen` (scope `UE`)
- L9 _namespace_ `namespace Build` (scope `UE::Zen`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Zen` (scope `UE`)
- L11 _namespace_ `namespace Build` (scope `UE::Zen`)

### `Source/Editor/StorageServerWidgets/Internal/SBuildActivity.h` (Internal)


#### class `SBuildActivity`  
`class SBuildActivity : public SCompoundWidget`  
_L21-77_
- inherits: `SCompoundWidget`
- L23 _private function_ `SLATE_BEGIN_ARGS(SBuildActivity) : _ZenServiceInstance(nullptr) , _BuildServiceInstance(nullptr)`
- L28 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L29 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::Build::FBuildServiceInstance>, BuildServiceInstance);`
- L40 _private prototype_ `void Construct(const FArguments& InArgs);`
- L42 _private function_ `void AddBuildTransfer(UE::Zen::Build::FBuildServiceInstance::FBuildTransfer Transfer, FStringView Name, FStringView Platform)`
- L54 _private prototype_ `TSharedRef<ITableRow> GenerateBuildActivityRow(TSharedPtr<FBuildActivity> InItem, const TSharedRef<STableViewBase>& InOwningTable);`
- L55 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L56 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FBuildActivity, ESPMode::ThreadSafe> Item);`
- L57 _private prototype_ `TSharedPtr<SWidget> OnGetBuildActivityContextMenuContent();`
- L59 _private prototype_ `bool CanCancelBuildActivity() const;`
- L60 _private prototype_ `void CancelBuildActivity() const;`
- L61 _private prototype_ `bool CanRetryBuildActivity() const;`
- L62 _private prototype_ `void RetryBuildActivity();`
- L63 _private prototype_ `void OpenDestinationForBuildActivity();`
- L64 _private prototype_ `static void OpenDestinationForBuildActivity(TSharedPtr<UE::Zen::Build::FBuildServiceInstance> ServiceInstance, TSharedPtr<FBuildActivity> Item);`
- L65 _private prototype_ `bool CanClearBuildActivity() const;`
- L66 _private prototype_ `void ClearBuildActivity();`
- L67 _private prototype_ `bool CanViewLogForBuildActivity() const;`
- L68 _private prototype_ `void ViewLogForBuildActivity() const;`
- L69 _private prototype_ `void ClearAllCompleted();`
- L71 _private member_ `TSharedPtr<SListView<TSharedPtr<SBuildActivity::FBuildActivity, ESPMode::ThreadSafe>>> BuildActivityListView;`
- L72 _private member_ `TArray<TSharedPtr<SBuildActivity::FBuildActivity, ESPMode::ThreadSafe>> BuildActivities;`
- L74 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L75 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`
- L76 _private member_ `TAttribute<TSharedPtr<UE::Zen::Build::FBuildServiceInstance>> BuildServiceInstance;`

#### struct `SBuildActivity::FBuildActivity`  
`struct FBuildActivity : public TSharedFromThis<FBuildActivity, ESPMode::ThreadSafe>`  
_L33-38_
- inherits: `TSharedFromThis<FBuildActivity,ESPMode::ThreadSafe>`
- L35 _public member_ `FString Name;`
- L36 _public member_ `FString Platform;`
- L37 _public member_ `UE::Zen::Build::FBuildServiceInstance::FBuildTransfer Transfer;`

#### class `SBuildActivityTableRow`  
`class SBuildActivityTableRow : public SMultiColumnTableRow<FBuildActivityPtr>`  
_L81-98_
- inherits: `SMultiColumnTableRow<FBuildActivityPtr>`
- L84 _public function_ `SLATE_BEGIN_ARGS(SBuildActivityTableRow)`
- L85 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const FBuildActivityPtr InBuildActivity, TSharedPtr<UE::Zen::Build::FBuildServiceInstance> InBuildServiceInstance);`
- L91 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L92 _public prototype_ `const FSlateBrush* GetBorder() const;`
- L93 _public prototype_ `FReply OnBrowseClicked();`
- L96 _private member_ `FBuildActivityPtr BuildActivity;`
- L97 _private member_ `TSharedPtr<UE::Zen::Build::FBuildServiceInstance> BuildServiceInstance;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`
- L79 _typedef_ `typedef TSharedPtr<SBuildActivity::FBuildActivity, ESPMode::ThreadSafe> FBuildActivityPtr;`

### `Source/Editor/StorageServerWidgets/Internal/SBuildArtifactSelection.h` (Internal)


#### class `SBuildArtifactSelection`  
`class SBuildArtifactSelection : public SCompoundWidget`  
_L23-72_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SBuildArtifactSelection) : _ZenServiceInstance(nullptr) , _BuildServiceInstance(nullptr)`
- L32 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L33 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::Build::FBuildServiceInstance>, BuildServiceInstance);`
- L35 _public prototype_ `SLATE_EVENT(FOnDownloadWithSpec, OnDownloadWithSpec) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `bool HasArtifactConfigurations() const;`
- L42 _public prototype_ `TSharedPtr<FString> GetSelectedConfiguration() const;`
- L43 _public prototype_ `const TArray<FString>& GetSelectedArtifacts() const;`
- L44 _public prototype_ `void SetAvailableConfigurations( TSet<FString>&& InArtifactConfigurationSet, TMultiMap<FString, FString>&& InArtifactNameMap );`
- L48 _public prototype_ `void Refresh(FStringView InNamespace, FStringView InGroupDisplayName, const TMap<FString, UE::BuildSelection::Internal::FArtifact>* InNamedArtifacts, FCbObjectId InHighlightBuildId = {}, bool bInCanViewContents = false);`
- L50 _private prototype_ `void RebuildSelectedGroupArtifactHeader();`
- L51 _private prototype_ `void RebuildSelectedGroupArtifactContents();`
- L52 _private prototype_ `void SetSelectedConfiguration(const TSharedPtr<FString> InSelectedConfiguration);`
- L53 _private prototype_ `TSharedRef<SWidget> CreateArtifactMenuWidget(UE::BuildSelection::Internal::FArtifact* Artifact, const FString& ArtifactName);`
- L55 _private member_ `TAttribute<TSharedPtr<UE::Zen::Build::FBuildServiceInstance>> BuildServiceInstance;`
- L56 _private member_ `FOnDownloadWithSpec OnDownloadWithSpec;`
- L57 _private member_ `FString Namespace;`
- L58 _private member_ `bool bCanViewContents = false;`
- L60 _private member_ `TMultiMap<FString, FString> ArtifactNameMap;`
- L61 _private member_ `TSet<FString> ArtifactConfigurationSet;`
- L62 _private member_ `TArray<TSharedPtr<FString>> ArtifactConfigurationList;`
- L63 _private member_ `TSharedPtr<FString> SelectedConfiguration;`
- L64 _private member_ `TArray<FString> SelectedArtifacts;`
- L65 _private member_ `FCbObjectId HighlightedBuildId;`
- L66 _private member_ `FString GroupDisplayName;`
- L68 _private member_ `TMap<FString, UE::BuildSelection::Internal::FArtifact> NamedArtifacts;`
- L70 _private member_ `TSharedPtr<SGridPanel> SelectedGroupArtifactHeaderGrid;`
- L71 _private member_ `TSharedPtr<SGridPanel> SelectedGroupArtifactGrid;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`
- L21 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDownloadWithSpec, const FString& , const UE::BuildSelection::Internal::FArtifact& , const FString& , const TArray<FString>& );`
- L21 _prototype_ `DECLARE_DELEGATE_FourParams(FOnDownloadWithSpec, const FString& , const UE::BuildSelection::Internal::FArtifact& , const FString& , const TArray<FString>& );`

### `Source/Editor/StorageServerWidgets/Internal/SBuildLogin.h` (Internal)


#### class `SBuildLogin`  
`class SBuildLogin : public SCompoundWidget`  
_L15-39_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SBuildLogin) : _ZenServiceInstance(nullptr) , _BuildServiceInstance(nullptr)`
- L22 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L23 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::Build::FBuildServiceInstance>, BuildServiceInstance);`
- L25 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `UE::Zen::Build::FBuildServiceInstance::EConnectionState GetEffectiveConnectionState(TSharedPtr<UE::Zen::Build::FBuildServiceInstance> ServiceInstance) const;`
- L31 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L33 _private member_ `UE::Zen::Build::FBuildServiceInstance::EConnectionFailureReason LastConnectionFailureReason = UE::Zen::Build::FBuildServiceInstance::EConnectionFailureReason::None;`
- L34 _private member_ `bool bTriggeredInteractiveLogin = false;`
- L36 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L37 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`
- L38 _private member_ `TAttribute<TSharedPtr<UE::Zen::Build::FBuildServiceInstance>> BuildServiceInstance;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SBuildSelection.h` (Internal)


#### class `SBuildSelection`  
`class SBuildSelection : public SCompoundWidget`  
_L42-210_
- inherits: `SCompoundWidget`
- L44 _private function_ `SLATE_BEGIN_ARGS(SBuildSelection) : _ZenServiceInstance(nullptr) , _BuildServiceInstance(nullptr)`
- L49 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L50 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::Build::FBuildServiceInstance>, BuildServiceInstance);`
- L69 _private prototype_ `void Construct(const FArguments& InArgs);`
- L77 _private prototype_ `void ActOnBuildArtifact(EBuildArtifactAction Action, const UE::Zen::Build::FBuildReference& BuildReference, bool bRebuildLists = true);`
- L95 _private prototype_ `static TPair<FRegexPattern, FKnownBuildType> MakeKnownBuildTypePattern(const FStringView InPattern, EBuildType Type, FText&& InText, int InDefaultSelectionOrdering = 0);`
- L96 _private prototype_ `EBuildType GetSelectedBuildType() const;`
- L97 _private prototype_ `void RebuildLists();`
- L98 _private prototype_ `void RegenerateBuildGroups(UE::Zen::Build::FListBuildsState& ListBuildsState);`
- L99 _private prototype_ `void RefreshPresentedBuildGroups();`
- L100 _private prototype_ `void RegenerateActivePlatformFilters();`
- L101 _private prototype_ `void ValidateBuildGroupSelection();`
- L102 _private prototype_ `TSharedRef<SWidget> OnGenerateTextBlockFromString(TSharedPtr<FString> Item);`
- L103 _private prototype_ `TSharedRef<SWidget> OnGenerateBuildTypeTextBlockFromString(TSharedPtr<FString> Item);`
- L104 _private prototype_ `bool DoesPassAllViewFilters(TSharedPtr<FBuildGroup> InItem) const;`
- L105 _private prototype_ `void PostViewFilterChange();`
- L106 _private prototype_ `bool BuildGroupIsSelectableOrNavigable(TSharedPtr<FBuildGroup> InItem) const;`
- L107 _private prototype_ `TSharedRef<ITableRow> GenerateBuildGroupRow(TSharedPtr<FBuildGroup> InItem, const TSharedRef<STableViewBase>& InOwningTable);`
- L108 _private prototype_ `TSharedPtr<SWidget> OnGetBuildGroupContextMenuContent() const;`
- L109 _private prototype_ `void OnChooseDestinationDirectoryClicked();`
- L110 _private prototype_ `void OnChooseTransferFilterClicked();`
- L111 _private prototype_ `TSharedRef<SWidget> GetBuildDestinationPanel();`
- L112 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L113 _private prototype_ `void RefreshArtifactSelectionWidget(TSharedPtr<FBuildGroup> Item);`
- L114 _private prototype_ `void BuildGroupSelectionChanged(TSharedPtr<FBuildGroup> Item, ESelectInfo::Type SelectInfo);`
- L115 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L116 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L117 _private prototype_ `void EnforceTargetedBuildActionOnGroup();`
- L119 _private prototype_ `FText ConvertBuildTypeToText(const FString& InBuildType);`
- L120 _private prototype_ `int ConvertBuildTypeToDefaultSelectionOrdering(const FString& InBuildType);`
- L122 _private prototype_ `void SetUserSelectedDestination(const FStringView InDestination);`
- L123 _private prototype_ `FString GetUserSelectedDestination() const;`
- L124 _private prototype_ `FString GetDefaultDestination() const;`
- L125 _private prototype_ `FString GetEffectiveDestination() const;`
- L127 _private prototype_ `void SetUserSelectedAppendBuildNameToDestination(bool bAppendBuildNameToDestination);`
- L128 _private prototype_ `void SetUserSelectedTransferFilter(const FStringView InIncludeFilter, const FStringView InExcludeFilter);`
- L130 _private prototype_ `void SetSelectedStream(const TSharedPtr<FString> InSelectedStream);`
- L131 _private prototype_ `void SetSelectedProject(const TSharedPtr<FString> InSelectedProject);`
- L132 _private prototype_ `void SetSelectedBuildType(const TSharedPtr<FString> InBuildType);`
- L133 _private prototype_ `void SetIncludePreflights(const bool bInIncludePreflights);`
- L135 _private prototype_ `void SetUserSelectedProjectDictionaryRoot(FStringView InRoot);`
- L136 _private prototype_ `void SetFallbackProjectDictionaryRoot(FStringView InRoot);`
- L138 _private prototype_ `static FString SanitizeForPath(const FString& InString);`
- L139 _private prototype_ `static FString SanitizeForZenId(const FString& InString);`
- L140 _private prototype_ `static FString SanitizeBranch(const FString& InString);`
- L141 _private prototype_ `static FString SanitizeBucket(const FString& InString);`
- L143 _private prototype_ `static const TCHAR* LexToString(EBuildType BuildType);`
- L145 _private prototype_ `FReply ExploreDestination_OnClicked();`
- L146 _private prototype_ `void DownloadSelectedArtifactsInSelectedBuildGroup();`
- L147 _private prototype_ `bool DownloadItem(const FBuildGroup& Group, const FString& ArtifactName, const UE::BuildSelection::Internal::FArtifact& Artifact, FString&& DownloadSpecJSONContents = FString(), TArray<FString>&& PartNames = TArray<FString>());`
- L149 _private member_ `TMap<FString, FString> EngineInstallations;`
- L151 _private member_ `FString FallbackProjectDictionaryRootDir;`
- L152 _private member_ `TUniquePtr<FUProjectDictionary> FallbackProjectDictionary;`
- L154 _private member_ `FString UserSelectedProjectDictionaryRootDir;`
- L155 _private member_ `TUniquePtr<FUProjectDictionary> UserSelectedProjectDictionary;`
- L157 _private member_ `FString BranchName;`
- L158 _private member_ `int EffectiveCompatibleChangelist = 0;`
- L160 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ProjectWidget;`
- L161 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> StreamWidget;`
- L162 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> BuildTypeWidget;`
- L163 _private member_ `TSharedPtr<SMultiSelectComboBox> PlatformFiltersWidget;`
- L165 _private member_ `TSharedPtr<SBuildArtifactSelection> BuildArtifactSelection;`
- L167 _private member_ `TArray<TSharedPtr<FString>> ProjectList;`
- L168 _private member_ `TArray<TSharedPtr<FString>> StreamList;`
- L169 _private member_ `TArray<TSharedPtr<FString>> BuildTypeList;`
- L170 _private member_ `TArray<TSharedPtr<FString>> PlatformList;`
- L178 _private member_ `mutable FRWLock TargetedBuildIdLock;`
- L179 _private member_ `EBuildArtifactAction TargetedBuildIdAction = EBuildArtifactAction::None;`
- L180 _private member_ `FCbObjectId TargetedBuildId;`
- L182 _private member_ `TArray<FString> ActivePlatformFilters;`
- L183 _private member_ `FString UserSelectedDestinations[(int)EBuildType::Count];`
- L184 _private member_ `FTransferFilter UserSelectedTransferFilters[(int)EBuildType::Count];`
- L185 _private member_ `bool bAppendBuildNameToDestinations[(int)EBuildType::Count];`
- L186 _private member_ `bool bCleanDestinations[(int)EBuildType::Count];`
- L188 _private member_ `TSharedPtr<FString> SelectedStream;`
- L189 _private member_ `TSharedPtr<FString> SelectedProject;`
- L190 _private member_ `TSharedPtr<FString> SelectedBuildType;`
- L191 _private member_ `FString SelectedTextFilter;`
- L192 _private member_ `bool bIncludePreflights = true;`
- L194 _private member_ `TArray<TPair<FRegexPattern, FKnownBuildType>> KnownBuildTypePatterns;`
- L196 _private member_ `TSharedPtr<SListView<TSharedPtr<SBuildSelection::FBuildGroup, ESPMode::ThreadSafe>>> BuildGroupListView;`
- L197 _private member_ `FName BuildGroupSortByColumn;`
- L198 _private member_ `EColumnSortMode::Type BuildGroupSortMode;`
- L200 _private member_ `std::atomic<uint32> BuildListRefreshesInProgress = 0;`
- L201 _private member_ `std::atomic<uint32> BuildRefreshGeneration = 0;`
- L202 _private member_ `TArray<TSharedPtr<SBuildSelection::FBuildGroup, ESPMode::ThreadSafe>> BuildGroups;`
- L203 _private member_ `TArray<TSharedPtr<SBuildSelection::FBuildGroup, ESPMode::ThreadSafe>> PresentedBuildGroups;`
- L205 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`
- L206 _private member_ `TAttribute<TSharedPtr<UE::Zen::Build::FBuildServiceInstance>> BuildServiceInstance;`
- L207 _private member_ `FPreBuildTransfer PreBuildTransfer;`
- L208 _private member_ `FPreOplogBuildTransfer PreOplogBuildTransfer;`
- L209 _private member_ `FOnBuildTransferStarted OnBuildTransferStarted;`

#### struct `SBuildSelection::FBuildGroup`  
`struct FBuildGroup : public TSharedFromThis<FBuildGroup, ESPMode::ThreadSafe>`  
_L57-67_
- inherits: `TSharedFromThis<FBuildGroup,ESPMode::ThreadSafe>`
- L59 _public member_ `FString Namespace;`
- L60 _public member_ `FString DisplayName;`
- L61 _public member_ `FString CommitIdentifier;`
- L62 _public member_ `FDateTime CreatedAt;`
- L63 _public member_ `FString Category;`
- L64 _public member_ `FString Job;`
- L65 _public member_ `TMap<FString, UE::BuildSelection::Internal::FArtifact> NamedArtifacts;`
- L66 _public member_ `bool bIsPreflight;`

#### enum `SBuildSelection::EBuildArtifactAction`  
`enum class EBuildArtifactAction`  
_L71-76_
- L73 _public enumerator_ `None`
- L74 _public enumerator_ `Highlight`
- L75 _public enumerator_ `HighlightAndDownload`

#### enum `SBuildSelection::EBuildType`  
`enum class EBuildType`  
_L79-88_
- L81 _public enumerator_ `Oplog`
- L82 _public enumerator_ `StagedBuild`
- L83 _public enumerator_ `PackagedBuild`
- L84 _public enumerator_ `EditorPreCompiledBinary`
- L85 _public enumerator_ `EditorInstalledBuild`
- L86 _public enumerator_ `Unknown`
- L87 _public enumerator_ `Count`

#### struct `SBuildSelection::FKnownBuildType`  
`struct FKnownBuildType`  
_L89-94_
- L91 _public member_ `EBuildType Type;`
- L92 _public member_ `FText UserText;`
- L93 _public member_ `int DefaultSelectionOrdering;`

#### struct `SBuildSelection::FTransferFilter`  
`struct FTransferFilter`  
_L172-176_
- L174 _public member_ `FString IncludeFilter;`
- L175 _public member_ `FString ExcludeFilter;`

#### class `SBuildGroupTableRow`  
`class SBuildGroupTableRow : public SMultiColumnTableRow<FBuildSelectionBuildGroupPtr>`  
_L214-227_
- inherits: `SMultiColumnTableRow<FBuildSelectionBuildGroupPtr>`
- L217 _public function_ `SLATE_BEGIN_ARGS(SBuildGroupTableRow)`
- L218 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const FBuildSelectionBuildGroupPtr InBuildGroup);`
- L221 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L222 _public prototype_ `const FSlateBrush* GetBorder() const;`
- L223 _public prototype_ `FReply OnBrowseClicked();`
- L226 _private member_ `FBuildSelectionBuildGroupPtr BuildGroup;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Zen` (scope `UE`)
- L28 _namespace_ `namespace Build` (scope `UE::Zen`)
- L34 _delegate_ `DECLARE_DELEGATE_TwoParams(FPreBuildTransfer, FString& , UE::Zen::Build::EBuildTransferRequestFlags& );`
- L34 _prototype_ `DECLARE_DELEGATE_TwoParams(FPreBuildTransfer, FString& , UE::Zen::Build::EBuildTransferRequestFlags& );`
- L36 _delegate_ `DECLARE_DELEGATE_TwoParams(FPreOplogBuildTransfer, FString& , UE::Zen::Build::EBuildTransferRequestFlags& );`
- L36 _prototype_ `DECLARE_DELEGATE_TwoParams(FPreOplogBuildTransfer, FString& , UE::Zen::Build::EBuildTransferRequestFlags& );`
- L38 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnBuildTransferStarted, UE::Zen::Build::FBuildServiceInstance::FBuildTransfer , FStringView , FStringView );`
- L38 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnBuildTransferStarted, UE::Zen::Build::FBuildServiceInstance::FBuildTransfer , FStringView , FStringView );`
- L212 _typedef_ `typedef TSharedPtr<SBuildSelection::FBuildGroup, ESPMode::ThreadSafe> FBuildSelectionBuildGroupPtr;`

### `Source/Editor/StorageServerWidgets/Internal/SBuildTransferFilters.h` (Internal)


#### class `SBuildTransferFilters`  
`class SBuildTransferFilters : public SCompoundWidget`  
_L17-41_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_BEGIN_ARGS(SBuildTransferFilters) : _IncludeFilter(nullptr) , _ExcludeFilter(nullptr)`
- L24 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FString>, IncludeFilter);`
- L25 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FString>, ExcludeFilter);`
- L27 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private function_ `FString GetIncludeFilter() const`
- L32 _private function_ `FString GetExcludeFilter() const`
- L35 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L37 _private member_ `FString IncludeFilter;`
- L38 _private member_ `FString ExcludeFilter;`
- L40 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenCacheStatistics.h` (Internal)


#### class `SZenCacheStatistics`  
`class SZenCacheStatistics : public SCompoundWidget`  
_L15-35_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SZenCacheStatistics) : _ZenServiceInstance(nullptr)`
- L21 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L31 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L33 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L34 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenCidStoreStatistics.h` (Internal)


#### class `SZenCidStoreStatistics`  
`class SZenCidStoreStatistics : public SCompoundWidget`  
_L15-35_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SZenCidStoreStatistics) : _ZenServiceInstance(nullptr)`
- L21 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L31 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L33 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L34 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenDialogs.h` (Internal)


#### class `SZenStoreStausDialog`  
`class SZenStoreStausDialog : public SCompoundWidget`  
_L15-23_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SZenStoreStausDialog)`
- L18 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenProjectStatistics.h` (Internal)


#### class `SZenProjectStatistics`  
`class SZenProjectStatistics : public SCompoundWidget`  
_L15-35_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SZenProjectStatistics) : _ZenServiceInstance(nullptr)`
- L21 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L31 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L33 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L34 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenServiceStatus.h` (Internal)


#### class `SZenServiceStatus`  
`class SZenServiceStatus : public SCompoundWidget`  
_L15-54_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SZenServiceStatus) : _ZenServiceInstance(nullptr)`
- L21 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private member_ `static constexpr uint32 NumState = 2;`
- L41 _private member_ `FState State[NumState];`
- L42 _private member_ `std::atomic<uint32> ActiveStateIndex = 0;`
- L45 _private prototype_ `const FState& GetCurrentState() const;`
- L46 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L47 _private prototype_ `FReply ExploreDataPath_OnClicked();`
- L48 _private prototype_ `FReply ExploreExecutablePath_OnClicked();`
- L50 _private prototype_ `EActiveTimerReturnType UpdateState(double InCurrentTime, float InDeltaTime);`
- L52 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L53 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`

#### struct `SZenServiceStatus::FState`  
`struct FState`  
_L28-39_
- L30 _public member_ `UE::Zen::FZenLocalServiceRunContext RunContext;`
- L31 _public member_ `FString Version;`
- L32 _public member_ `UE::Zen::FGCStatus GCStatus;`
- L33 _public member_ `UE::Zen::FZenCacheStats ZenCacheStats;`
- L34 _public member_ `UE::Zen::FZenProjectStats ZenProjectStats;`
- L35 _public member_ `uint16 LocalPort = 0;`
- L36 _public member_ `bool bHaveStats = false;`
- L37 _public member_ `bool bGotRunContext = false;`
- L38 _public member_ `bool bIsRunning = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`

### `Source/Editor/StorageServerWidgets/Internal/SZenWorkspaces.h` (Internal)


#### class `SZenWorkspaces`  
`class SZenWorkspaces : public SCompoundWidget`  
_L17-56_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_BEGIN_ARGS(SZenWorkspaces) : _ZenServiceInstance(nullptr)`
- L24 _private prototype_ `SLATE_ATTRIBUTE(TSharedPtr<UE::Zen::FZenServiceInstance>, ZenServiceInstance);`
- L25 _private prototype_ `SLATE_ATTRIBUTE(float, UpdateFrequency);`
- L27 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private function_ `int32 GetWorkspaceCount() const`
- L32 _private prototype_ `void UpdateWorkspaces(float InDeltaTime, bool bForce = false);`
- L35 _private prototype_ `TSharedRef<SWidget> GetWorkspaceList();`
- L37 _private prototype_ `FReply ZenWorkspacesArea_Toggle() const;`
- L39 _private prototype_ `FReply OnBackToMainWidget();`
- L40 _private prototype_ `FReply OnCreateNewWorkspaceClicked();`
- L42 _private prototype_ `const FSlateBrush* ZenWorkspacesArea_Icon() const;`
- L45 _private member_ `TAttribute<TSharedPtr<UE::Zen::FZenServiceInstance>> ZenServiceInstance;`
- L46 _private member_ `float UpdateFrequency = 0.f;`
- L47 _private member_ `TSharedPtr<SVerticalBox> WorkspaceArea;`
- L48 _private member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;`
- L49 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L50 _private member_ `TSharedPtr<SExpandableArea> Expandable;`
- L52 _private member_ `TArray<TSharedPtr<UE::Zen::FZenWorkspaces>> WorkspaceModels;`
- L53 _private member_ `TSharedPtr<SListView<TSharedPtr<UE::Zen::FZenWorkspaces>>> WorkspacesListView;`
- L55 _private member_ `UE::Zen::FZenWorkspaces Workspaces;`

### `Source/Editor/StorageServerWidgets/Internal/ZenServiceInstanceManager.h` (Internal)


#### class `UE::Zen::FServiceInstanceManager`  
`class FServiceInstanceManager`  
_L14-21_
- L17 _public prototype_ `TSharedPtr<FZenServiceInstance> GetZenServiceInstance() const;`
- L19 _private member_ `mutable uint16 CurrentPort = 0;`
- L20 _private member_ `mutable TSharedPtr<FZenServiceInstance> CurrentInstance;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STORAGESERVERWIDGETS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Zen` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Editor/StorageServerWidgets/Private/SBuildArtifactContentsViewer.h` (Private)


#### struct `FContentsEntry`  
`struct FContentsEntry`  
_L15-23_
- L17 _public member_ `bool bIsMarked = false;` — Persistent download mark
- L18 _public member_ `bool bIsDownloading = false;` — true while an "Open" download is in progress
- L19 _public member_ `FString Name;` — File name
- L20 _public member_ `FStringView PartName;` — Non-owning view into FPartTab::PartName (stable after SetContents)
- L21 _public member_ `FCbObjectId PartId;` — Parent part ID
- L22 _public member_ `uint64 RawSize = 0;`

#### struct `FPartTab`  
`struct FPartTab`  
_L25-39_
- L27 _public member_ `FString PartName;`
- L28 _public member_ `FCbObjectId PartId;`
- L29 _public member_ `TArray<TSharedPtr<FContentsEntry>> AllFiles;`
- L30 _public member_ `TArray<TSharedPtr<FContentsEntry>> FilteredFiles;`
- L31 _public member_ `TSharedPtr<SListView<TSharedPtr<FContentsEntry>>> ListView;`
- L32 _public member_ `int32 TotalFileCount = 0;`
- L33 _public member_ `uint64 TotalFileSize = 0;`
- L34 _public member_ `int32 MarkedFileCount = 0;`
- L35 _public member_ `uint64 MarkedFileSize = 0;`
- L37 _public prototype_ `ECheckBoxState GetCheckState() const;`
- L38 _public prototype_ `bool IsFullyMarked() const;`

#### struct `FDownloadSpec`  
`struct FDownloadSpec`  
_L41-45_
- L43 _public member_ `FString SpecJSON;` — JSON for partially-marked parts (individual files)
- L44 _public member_ `TArray<FString> FullyMarkedPartNames;` — Parts where every file is marked

#### class `SContentsEntryRow`  
`class SContentsEntryRow : public SMultiColumnTableRow<TSharedPtr<FContentsEntry>>`  
_L51-64_
- inherits: `SMultiColumnTableRow<TSharedPtr<FContentsEntry>>`
- desc: Row widget for a single contents entry, using SMultiColumnTableRow so columns track header resizing automatically.
- L54 _public function_ `SLATE_BEGIN_ARGS(SContentsEntryRow)`
- L55 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnMarkChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<FContentsEntry> InEntry);`
- L59 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L62 _private member_ `TSharedPtr<FContentsEntry> Entry;`
- L63 _private member_ `FSimpleDelegate OnMarkChanged;`

#### class `SBuildArtifactContentsViewer`  
`class SBuildArtifactContentsViewer : public SCompoundWidget`  
_L75-186_
- inherits: `SCompoundWidget`
- desc: Widget for viewing build artifact file contents in a tabbed view grouped by build part
- L78 _public function_ `SLATE_BEGIN_ARGS(SBuildArtifactContentsViewer)`
- L80 _public prototype_ `SLATE_ARGUMENT(FString, ArtifactName) SLATE_EVENT(FOnStartFileDownload, OnStartFileDownload) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L85 _public prototype_ `~SBuildArtifactContentsViewer();`
- L88 _public prototype_ `void QueueContents(TMap<FString, UE::Zen::Build::FBuildServiceInstance::FBuildPart>&& BuildContents);` — Thread-safe: queues contents from a background thread for consumption on the Slate thread.
- L91 _public prototype_ `void MarkSelectedFiles();` — Toggle bIsMarked on selected items in the active tab and update counts.
- L94 _public prototype_ `void MarkAllFiles();` — Mark all file entries for download across all tabs.
- L97 _public prototype_ `void ClearAllMarkedFiles();` — Unmark all marked files across all tabs.
- L99 _public function_ `bool HasMarkedFiles() const`
- L100 _public function_ `int32 GetMarkedFileCount() const`
- L101 _public function_ `uint64 GetMarkedFileSize() const`
- L104 _public prototype_ `void RecalculateMarkedCounts();` — Recompute MarkedFileCount/MarkedFileSize from all PartTabs and update status text.
- L107 _public prototype_ `FDownloadSpec ComposeDownloadSpec() const;` — Build download spec from marked entries, separating fully-marked parts.
- L110 _public prototype_ `FString ComposeDownloadSpecJSON() const;` — Build download spec JSON from marked entries (thin wrapper).
- L112 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L114 _public prototype_ `static FString FormatSize(uint64 SizeInBytes);`
- L117 _private prototype_ `void SetContents(TMap<FString, UE::Zen::Build::FBuildServiceInstance::FBuildPart>& BuildContents);`
- L119 _private prototype_ `EActiveTimerReturnType PollPendingContents(double InCurrentTime, float InDeltaTime);`
- L127 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L128 _private prototype_ `void OpenFileEntries(TArray<TSharedPtr<FContentsEntry>>&& FileEntries, EFileOpenAction Action = EFileOpenAction::LaunchFile);`
- L129 _private prototype_ `FString ComposeFileDownloadSpec(const TArray<TSharedPtr<FContentsEntry>>& FileEntries) const;`
- L130 _private prototype_ `EActiveTimerReturnType PollPendingFileOpens(double InCurrentTime, float InDeltaTime);`
- L132 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FContentsEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L134 _private prototype_ `void SetActiveTab(int32 Index);`
- L135 _private prototype_ `void RecalculatePartMarkedCounts(FPartTab& Tab);`
- L136 _private prototype_ `void RebuildTabBar();`
- L137 _private prototype_ `void RefreshFilteredList();`
- L138 _private prototype_ `void SortAndRefreshList();`
- L140 _private prototype_ `void OnSearchTextChanged(const FText& InText);`
- L142 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L143 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L145 _private prototype_ `static bool MatchWildcard(FStringView Wildcard, FStringView String);`
- L146 _private prototype_ `static void ParseIncludeWildcards(const FString& FilterText, TArray<FString>& OutWildcards);`
- L147 _private prototype_ `static bool MatchesIncludeWildcards(const TArray<FString>& IncludeWildcards, FStringView FileName);`
- L149 _private member_ `FCriticalSection PendingContentsMutex;`
- L150 _private member_ `TOptional<TMap<FString, UE::Zen::Build::FBuildServiceInstance::FBuildPart>> PendingContents;`
- L152 _private member_ `TArray<FPartTab> PartTabs;`
- L154 _private member_ `TSharedPtr<SWidgetSwitcher> ContentSwitcher;`
- L155 _private member_ `TSharedPtr<SScrollBox> TabBarScrollBox;`
- L156 _private member_ `int32 ActiveTabIndex = 0;`
- L158 _private member_ `TSharedPtr<STextBlock> StatusText;`
- L159 _private member_ `TSharedPtr<STextBlock> MarkedStatusText;`
- L161 _private member_ `FText SearchText;`
- L163 _private member_ `FName SortByColumn;`
- L164 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L166 _private member_ `int32 TotalFileCount = 0;`
- L167 _private member_ `uint64 TotalFileSize = 0;`
- L169 _private member_ `int32 MarkedFileCount = 0;`
- L170 _private member_ `uint64 MarkedFileSize = 0;`
- L179 _private member_ `TArray<FPendingFileOpen> PendingFileOpens;`
- L180 _private member_ `FOnStartFileDownload OnStartFileDownload;`
- L182 _private member_ `bool bIsLoading = true;`
- L184 _private member_ `FButtonStyle InactiveTabButtonStyle;`
- L185 _private member_ `FButtonStyle ActiveTabButtonStyle;`

#### enum `SBuildArtifactContentsViewer::EFileOpenAction`  
`enum class EFileOpenAction : uint8`  
_L121-125_
- L123 _public enumerator_ `LaunchFile` — Open each file in its default application
- L124 _public enumerator_ `ExploreFolder` — Open the containing folder(s) in the native file browser

#### struct `SBuildArtifactContentsViewer::FPendingFileOpen`  
`struct FPendingFileOpen`  
_L172-177_
- L174 _public member_ `UE::Zen::Build::FBuildServiceInstance::FBuildTransfer Transfer;`
- L175 _public member_ `TArray<TSharedPtr<FContentsEntry>> Entries;`
- L176 _public member_ `EFileOpenAction Action = EFileOpenAction::LaunchFile;`

#### Free symbols / members of external scopes

- L66 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( UE::Zen::Build::FBuildServiceInstance::FBuildTransfer,`
- L66 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( UE::Zen::Build::FBuildServiceInstance::FBuildTransfer,`

### `Source/Editor/StorageServerWidgets/Private/SBuildArtifactMetadataViewer.h` (Private)


#### class `SBuildArtifactMetadataViewer`  
`class SBuildArtifactMetadataViewer : public SCompoundWidget`  
_L14-77_
- inherits: `SCompoundWidget`
- desc: Widget for displaying build artifact metadata in a property grid style
- L29 _public function_ `SLATE_BEGIN_ARGS(SBuildArtifactMetadataViewer)`
- L31 _public prototype_ `SLATE_ARGUMENT(FCbObject, Metadata) SLATE_ARGUMENT(FString, ArtifactName) SLATE_ARGUMENT(FCbObjectId, BuildId) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FMetadataEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for a metadata entry
- L43 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Generate context menu for a row
- L46 _private prototype_ `void ParseMetadata(const FCbObjectId& BuildId, const FCbObject& Metadata);` — Parse FCbObject metadata into display entries
- L49 _private prototype_ `void RefreshFilteredList();` — Refresh the filtered list based on search text
- L52 _private prototype_ `void OnSearchTextChanged(const FText& InText);` — Called when search text changes
- L55 _private prototype_ `void CopyKeyToClipboard();` — Copy selected entry key to clipboard
- L58 _private prototype_ `void CopyValueToClipboard();` — Copy selected entry value to clipboard
- L61 _private prototype_ `void CopyEntryToClipboard();` — Copy selected entry as "Key: Value" to clipboard
- L64 _private member_ `TArray<TSharedPtr<FMetadataEntry>> MetadataEntries;` — List of all metadata entries
- L67 _private member_ `TArray<TSharedPtr<FMetadataEntry>> FilteredMetadataEntries;` — Filtered list of metadata entries based on search
- L70 _private member_ `TSharedPtr<SListView<TSharedPtr<FMetadataEntry>>> ListView;` — List view widget
- L73 _private member_ `FText SearchText;` — Current search filter text
- L76 _private member_ `FString ArtifactName;` — Artifact name for display

#### struct `SBuildArtifactMetadataViewer::FMetadataEntry`  
`struct FMetadataEntry`  
_L18-27_
- desc: Struct to hold a metadata key-value pair for display
- L20 _public member_ `FString Key;`
- L21 _public member_ `FString Value;`
- L22 _public member_ `FString Type;`
- L24 _public function_ `FMetadataEntry(const FString& InKey, const FString& InValue, const FString& InType) : Key(InKey), Value(InValue), Type(InType)`

### `Source/Editor/StorageServerWidgets/Private/SMultiSelectComboBox.h` (Private)


#### class `SMultiSelectComboBox`  
`class SMultiSelectComboBox : public SCompoundWidget`  
_L11-33_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SMultiSelectComboBox)`
- L15 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FString>>*, SelectValues) SLATE_EVENT(FOnMultiSelectComboBoxCheckedValuesChanged, OnCheckedValuesChanged) SLATE_END_ARGS() virtual ~SMultiSelectComboBox();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `bool IsChecked(FStringView Value) const;`
- L26 _private prototype_ `TSharedRef<class SWidget> GenerateMenuItems();`
- L28 _private prototype_ `void OnSelectedChangedFromMultiselect(TSharedPtr<FString> Value);`
- L30 _private member_ `FOnMultiSelectComboBoxCheckedValuesChanged OnCheckedValuesChanged;`
- L31 _private member_ `TArray<FString> CheckedValues;`
- L32 _private member_ `TArray<TSharedPtr<FString>>* SelectValues;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE(FOnMultiSelectComboBoxCheckedValuesChanged) class SMultiSelectComboBox : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMultiSelectComboBox) {} SLATE_ARGUMENT(TArray<TSharedPtr<FString>>*, SelectValues) SLATE_EVENT(FOnMultiSelectComboBoxCheckedValuesChanged, OnCheckedValuesChanged) SLATE_END_ARGS() virtual ~SMultiSelectComboBox(); void Construct(const FArguments& InArgs); bool IsChecked(FStringView Value) const; private: TSharedRef<class SWidget> GenerateMenuItems(); void OnSelectedChangedFromMultiselect(TSharedPtr<FString> Value); FOnMultiSelectComboBoxCheckedValuesChanged OnCheckedValuesChanged; TArray<FString> CheckedValues; TArray<TSharedPtr<FString>>* SelectValues; };`
