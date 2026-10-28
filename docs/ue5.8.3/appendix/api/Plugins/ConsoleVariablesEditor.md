# Plugins / ConsoleVariablesEditor

- module root: `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor`
- headers: 29; symbols: 679
- symbol kinds: class=32, delegate=8, enum=8, enumerator=22, function=87, macro=13, member=167, namespace=4, prototype=322, struct=12, typedef=4
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, Concert, ConcertSharedSlate, ConcertSyncClient, ConcertSyncCore, ConcertTransport, ConsoleVariablesEditorRuntime, ContentBrowser, CoreUObject, EditorStyle, EditorWidgets, Engine, InputCore, Kismet, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, OutputLog

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/AssetDefinition/AssetDefinition_ConsoleVariables.h` (Private)


#### class `UAssetDefinition_ConsoleVariables`  
`class UAssetDefinition_ConsoleVariables : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/ConsoleVariablesEditorStyle.h` (Private)


#### class `FConsoleVariablesEditorStyle`  
`class FConsoleVariablesEditorStyle : FSlateStyleSet`  
_L7-36_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static void ReloadTextures();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L19 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L21 _public prototype_ `virtual const FSlateBrush* GetBrush(const FName PropertyName, const ANSICHAR* Specifier = nullptr, const ISlateStyle* RequestingStyle = nullptr) const override;`
- L24 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L31 _private prototype_ `static FString GetExternalPluginContent(const FString& PluginName, const FString& RelativePath, const ANSICHAR* Extension);`
- L33 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L35 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Factories/ConsoleVariablesEditorFactory.h` (Private)


#### class `UConsoleVariablesEditorFactory`  
`class UConsoleVariablesEditorFactory : public UFactory`  
_L11-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L17 _public prototype_ `UConsoleVariablesEditorFactory();`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConcertConsoleVariableSessionCustomization.h` (Private)


#### class `FConcertConsoleVariableSessionCustomization`  
`class FConcertConsoleVariableSessionCustomization : public IDetailCustomization`  
_L20-40_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L25 _public prototype_ `void UpdateClientSettings(EConcertClientStatus Status, const FConcertCVarDetails& RecordSetting);`
- L26 _public prototype_ `void PopulateClientList();`
- L28 _public function_ `FOnConcertCVarDetailChanged& OnSettingChanged()`
- L34 _private prototype_ `void SettingChange(const FConcertCVarDetails &Setting);`
- L36 _private member_ `FOnConcertCVarDetailChanged DetailDelegate;`
- L38 _private member_ `TArray<TSharedPtr<FConcertCVarDetails>> Clients;`
- L39 _private member_ `TWeakPtr<SListViewCVarDetail> ClientsListViewWeak;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertCVarDetailChanged, const FConcertCVarDetails&);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertCVarDetailChanged, const FConcertCVarDetails&);`
- L18 _typedef_ `using SListViewCVarDetail = SListView<TSharedPtr<FConcertCVarDetails>>;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConcertConsoleVariableSyncCustomization.h` (Private)


#### class `FConcertConsoleVariableSyncCustomization`  
`class FConcertConsoleVariableSyncCustomization : public IDetailCustomization`  
_L29-90_
- inherits: `IDetailCustomization`
- L32 _public typedef_ `using ThisType = FConcertConsoleVariableSyncCustomization;`
- L33 _public function_ `static void OpenMultiUserExcludeProperty()`
- L38 _public function_ `static FOnCVarSyncPropertyValueChanged& OnSyncPropertyValueChanged()`
- L44 _public function_ `void SyncPropertyChanged()`
- L50 _public function_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override`

#### Free symbols / members of external scopes

- L25 _macro_ `#define LOCTEXT_NAMESPACE "ConcertConsoleVariableSyncCustomization"`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCVarSyncPropertyValueChanged, bool);`
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCVarSyncPropertyValueChanged, bool);`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConsoleVariableSync.h` (Private)


#### enum `ERemoteCVarChangeType`  
`enum class ERemoteCVarChangeType : uint8`  
_L15-20_
- L17 _public enumerator_ `Update = 0`
- L18 _public enumerator_ `Add`
- L19 _public enumerator_ `Remove`

#### struct `UE::ConsoleVariables::MultiUser::Private::FManager`  
`struct FManager`  
_L31-70_
- L33 _public prototype_ `FManager();`
- L34 _public prototype_ `~FManager();`
- L37 _public prototype_ `FManager(const FManager&) = delete;` — Do not allow this to be copied or moved.
- L38 _public prototype_ `FManager(FManager&&) = delete;`
- L39 _public prototype_ `FManager &operator=(const FManager&) = delete;`
- L40 _public prototype_ `FManager &operator=(FManager&&) = delete;`
- L43 _public prototype_ `FOnRemoteCVarChange& OnRemoteCVarChange();` — Delegate that is invoked when a remote client has sent a new console variable value.
- L46 _public prototype_ `FOnRemoteListItemCheckStateChange& OnRemoteListItemCheckStateChange();` — Delegate invoked when a remote client's console variable list item in CVE is manually checked or unchecked.
- L49 _public prototype_ `FOnMultiUserConnectionChange& OnConnectionChange();` — Delegate that is invoked when the connection status changes for this client.
- L52 _public prototype_ `void SendConsoleVariableChange(ERemoteCVarChangeType InChangeType, FString InName, FString InValue, EConsoleVariableFlags InFlags);` — Sends the named console variable with value to all connected Multi-user clients
- L55 _public prototype_ `void SendListItemCheckStateChange(FString InName, ECheckBoxState InCheckedState);` — Sends the named console variable with value to all connected Multi-user clients
- L58 _public prototype_ `void SetEnableMultiUserSupport(bool bIsEnabled);` — Enables / disables multi-user message handling.
- L60 _public prototype_ `bool IsInitialized() const;`
- L62 _public prototype_ `bool IsSyncEnabled() const;`
- L64 _public prototype_ `bool IsSessionValid() const;`
- L66 _public prototype_ `bool IsLocalUserInMultiUserSession();`
- L69 _private member_ `TUniquePtr<FManagerImpl> Implementation;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnRemoteCVarChange, ERemoteCVarChangeType, FString, FString, EConsoleVariableFlags);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnRemoteCVarChange, ERemoteCVarChangeType, FString, FString, EConsoleVariableFlags);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteListItemCheckStateChange, FString, ECheckBoxState);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteListItemCheckStateChange, FString, ECheckBoxState);`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMultiUserConnectionChange, EConcertConnectionStatus);`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMultiUserConnectionChange, EConcertConnectionStatus);`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace ConsoleVariables` (scope `UE`)
- L26 _namespace_ `namespace MultiUser` (scope `UE::ConsoleVariables`)
- L26 _namespace_ `namespace Private` (scope `UE::ConsoleVariables::MultiUser`)

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConsoleVariableSyncData.h` (Private)


#### class `UConcertCVarSynchronization`  
`class UConcertCVarSynchronization : public UObject`  
_L15-22_
- reflection: `UCLASS(config=Engine, DisplayName="Multi-user Console Variable Synchronization")`
- inherits: `UObject`
- L21 _public member_ `bool bSyncCVarTransactions = true;` — `UPROPERTY(config,EditAnywhere,BlueprintReadWrite,Category="Multi-User",DisplayName="Multi-User Console Variables Synchronization")`

#### struct `FConcertCVarSettings`  
`struct FConcertCVarSettings`  
_L25-32_
- reflection: `USTRUCT()`
- L31 _public member_ `bool bReceiveCVarChanges = true;` — `UPROPERTY(config,EditAnywhere,Category="Multi-user Console Variable Settings")` — Indicates if the given node can receive console variable values from other clients.

#### struct `FConcertCVarDetails`  
`struct FConcertCVarDetails`  
_L35-47_
- reflection: `USTRUCT()`
- L40 _public member_ `FConcertSessionClientInfo Details;` — `UPROPERTY()`
- L43 _public member_ `bool bCVarSyncEnabled = true;` — `UPROPERTY()`
- L46 _public member_ `FConcertCVarSettings Settings;` — `UPROPERTY()`

#### class `UConcertCVarConfig`  
`class UConcertCVarConfig : public UObject`  
_L50-60_
- reflection: `UCLASS(config=Engine, DisplayName="Multi-user Console Variable Settings")`
- inherits: `UObject`
- L56 _public member_ `FConcertCVarSettings LocalSettings;` — `UPROPERTY(config,EditAnywhere,Category="Multi-user Console Variable Settings")`
- L59 _public member_ `TArray<FConcertCVarDetails> RemoteDetails;` — `UPROPERTY(Transient,EditAnywhere,Category="Multi-user Console Variable Settings")`

#### struct `FConcertCVarChangeEvent`  
`struct FConcertCVarChangeEvent`  
_L63-74_
- reflection: `USTRUCT()`
- L69 _public member_ `FGuid EndpointId;` — `UPROPERTY()` — The endpoint id sending this event.
- L73 _public member_ `FConcertCVarSettings Settings;` — `UPROPERTY()` — The Console Variable multi-user settings for the given EndpointId.

#### struct `FConcertCVarSyncChangeEvent`  
`struct FConcertCVarSyncChangeEvent`  
_L77-88_
- reflection: `USTRUCT()`
- L83 _public member_ `FGuid EndpointId;` — `UPROPERTY()` — The endpoint id sending this event.
- L87 _public member_ `bool bSyncCVarChanges = true;` — `UPROPERTY()` — The value of the console variable mult-user sync for the above EndpointId.

#### enum `EConsoleVariableChangeType`  
`enum class EConsoleVariableChangeType : uint8`  
_L91-101_
- reflection: `UENUM()`
- L94 _public enumerator_ `Modify = 0` — The console variable was modified
- L97 _public enumerator_ `Add` — A console variable was added to the CVE asset
- L100 _public enumerator_ `Remove` — A console variable was removed to the CVE asset

#### struct `FConcertSetConsoleVariableEvent`  
`struct FConcertSetConsoleVariableEvent`  
_L104-123_
- reflection: `USTRUCT()`
- L110 _public member_ `EConsoleVariableChangeType ChangeType = EConsoleVariableChangeType::Modify;` — `UPROPERTY()`
- L114 _public member_ `FString Variable;` — `UPROPERTY()` — Console variable name to apply value change.
- L118 _public member_ `FString Value;` — `UPROPERTY()` — The value to set the named console variable.
- L122 _public member_ `uint32 Flags = 0;` — `UPROPERTY()` — The flags for this console variable.

#### struct `FConcertSetListItemCheckStateEvent`  
`struct FConcertSetListItemCheckStateEvent`  
_L126-135_
- reflection: `USTRUCT()`
- L131 _public member_ `FString Variable;` — `UPROPERTY()` — Console variable name to apply the checked state change.
- L134 _public member_ `ECheckBoxState CheckState = ECheckBoxState::Checked;` — `UPROPERTY()` — The checked state of the list item.

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorList.h` (Private)


#### class `FConsoleVariablesEditorList`  
`class FConsoleVariablesEditorList : public TSharedFromThis<FConsoleVariablesEditorList>`  
_L13-65_
- inherits: `TSharedFromThis<FConsoleVariablesEditorList>`
- L25 _public function_ `FConsoleVariablesEditorList()`
- L27 _public prototype_ `~FConsoleVariablesEditorList();`
- L29 _public prototype_ `TSharedRef<SWidget> GetOrCreateWidget();`
- L31 _public prototype_ `void SetSearchString(const FString& SearchString);`
- L33 _public function_ `EConsoleVariablesEditorListMode GetListMode() const`
- L38 _public function_ `void SetListMode(EConsoleVariablesEditorListMode NewListMode)`
- L47 _public prototype_ `void RebuildList(const FString& InConsoleCommandToScrollTo = "", bool bShouldCacheValues = true) const;` — Regenerate the list items and refresh the list. Call when adding or removing variables. @param bShouldCacheValues If true, the current list's current values will be cached and then restored when the list is rebuilt. Otherwise preset values will be used.
- L53 _public prototype_ `void RefreshList() const;` — Refresh filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L56 _public prototype_ `void UpdatePresetValuesForSave(TObjectPtr<UConsoleVariablesAsset> InAsset) const;` — Updates the saved values in a UConsoleVariablesAsset so that the command/value map can be saved to disk
- L59 _public prototype_ `void UpdateCachedValue(const FString& Command, const FString& Value);` — Update cached value
- L63 _private member_ `EConsoleVariablesEditorListMode CurrentListMode = EConsoleVariablesEditorListMode::Preset;`
- L64 _private member_ `TSharedPtr<SConsoleVariablesEditorList> ListWidget;`

#### enum `FConsoleVariablesEditorList::EConsoleVariablesEditorListMode`  
`enum class EConsoleVariablesEditorListMode : uint8`  
_L17-23_
- L20 _public enumerator_ `Preset = 1` — We're displaying the cvars listed in the loaded (or default) preset
- L22 _public enumerator_ `GlobalSearch = 2` — We're displaying the cvars that match the criteria of the global search

#### Free symbols / members of external scopes

- L8 _typedef_ `typedef TSharedPtr<FConsoleVariablesEditorListRow> FConsoleVariablesEditorListRowPtr;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_SetByCurrentPreset.h` (Private)


#### class `ConsoleVariablesEditorListFilter_SetByCurrentPreset`  
`class ConsoleVariablesEditorListFilter_SetByCurrentPreset : public IConsoleVariablesEditorListFilter`  
_L9-47_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `ConsoleVariablesEditorListFilter_SetByCurrentPreset()`
- L20 _public function_ `virtual FString GetFilterName() override`
- L25 _public function_ `virtual FText GetFilterButtonLabel() override`
- L30 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L35 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_SetInSession.h` (Private)


#### class `ConsoleVariablesEditorListFilter_SetInSession`  
`class ConsoleVariablesEditorListFilter_SetInSession : public IConsoleVariablesEditorListFilter`  
_L9-47_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `ConsoleVariablesEditorListFilter_SetInSession()`
- L20 _public function_ `virtual FString GetFilterName() override`
- L25 _public function_ `virtual FText GetFilterButtonLabel() override`
- L30 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L35 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_ShowOnlyCommands.h` (Private)


#### class `ConsoleVariablesEditorListFilter_ShowOnlyCommands`  
`class ConsoleVariablesEditorListFilter_ShowOnlyCommands : public IConsoleVariablesEditorListFilter`  
_L9-47_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `ConsoleVariablesEditorListFilter_ShowOnlyCommands()`
- L20 _public function_ `virtual FString GetFilterName() override`
- L25 _public function_ `virtual FText GetFilterButtonLabel() override`
- L30 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L35 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_ShowOnlyModifiedVariables.h` (Private)


#### class `ConsoleVariablesEditorListFilter_ShowOnlyModifiedVariables`  
`class ConsoleVariablesEditorListFilter_ShowOnlyModifiedVariables : public IConsoleVariablesEditorListFilter`  
_L9-44_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `ConsoleVariablesEditorListFilter_ShowOnlyModifiedVariables()`
- L20 _public function_ `virtual FString GetFilterName() override`
- L25 _public function_ `virtual FText GetFilterButtonLabel() override`
- L30 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L35 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_ShowOnlyVariables.h` (Private)


#### class `ConsoleVariablesEditorListFilter_ShowOnlyVariables`  
`class ConsoleVariablesEditorListFilter_ShowOnlyVariables : public IConsoleVariablesEditorListFilter`  
_L9-47_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `ConsoleVariablesEditorListFilter_ShowOnlyVariables()`
- L20 _public function_ `virtual FString GetFilterName() override`
- L25 _public function_ `virtual FText GetFilterButtonLabel() override`
- L30 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L35 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/ConsoleVariablesEditorListFilter_Source.h` (Private)


#### class `FConsoleVariablesEditorListFilter_Source`  
`class FConsoleVariablesEditorListFilter_Source : public IConsoleVariablesEditorListFilter`  
_L9-50_
- inherits: `IConsoleVariablesEditorListFilter`
- L13 _public function_ `FConsoleVariablesEditorListFilter_Source(const EConsoleVariableFlags InSourceFlag) : SourceFlag(InSourceFlag)`
- L16 _public function_ `virtual FString GetFilterName() override`
- L21 _public function_ `virtual FText GetFilterButtonLabel() override`
- L26 _public function_ `virtual FText GetFilterButtonToolTip() override`
- L33 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem) override`
- L49 _private member_ `EConsoleVariableFlags SourceFlag;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListFilters/IConsoleVariablesEditorListFilter.h` (Private)


#### class `IConsoleVariablesEditorListFilter`  
`class IConsoleVariablesEditorListFilter`  
_L7-63_
- L19 _public prototype_ `virtual ~IConsoleVariablesEditorListFilter() = default;`
- L21 _public prototype_ `virtual FString GetFilterName() = 0;`
- L24 _public prototype_ `virtual FText GetFilterButtonLabel() = 0;` — Returns localized text to display for when this filter' active state is defined by a toggle button.
- L26 _public prototype_ `virtual FText GetFilterButtonToolTip() = 0;` — Returns localized text to display when the user mouses over a toggle button that defines whether this filter is active.
- L28 _public function_ `void SetFilterActive(const bool bNewEnabled)`
- L33 _public function_ `void ToggleFilterActive()`
- L38 _public function_ `bool GetIsFilterActive() const`
- L43 _public function_ `void SetFilterMatchType(const EConsoleVariablesEditorListFilterMatchType InType)`
- L48 _public function_ `EConsoleVariablesEditorListFilterMatchType GetFilterMatchType() const`
- L53 _public function_ `virtual bool DoesItemPassFilter(const FConsoleVariablesEditorListRowPtr& InItem)`
- L60 _private member_ `bool bIsFilterActive = true;`
- L61 _private member_ `EConsoleVariablesEditorListFilterMatchType FilterMatchType = EConsoleVariablesEditorListFilterMatchType::MatchAny;`

#### enum `IConsoleVariablesEditorListFilter::EConsoleVariablesEditorListFilterMatchType`  
`enum class EConsoleVariablesEditorListFilterMatchType`  
_L11-17_
- L14 _public enumerator_ `MatchAny` — Filters of this type are placed into a group in which if any of the group's filters pass, the row is considered passing
- L16 _public enumerator_ `MatchAll` — Filters of this type are placed into a group in which all of the group's filters must pass for the row to be considered passing

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/ConsoleVariablesEditorListRow.h` (Private)


#### struct `FConsoleVariablesEditorListRow`  
`struct FConsoleVariablesEditorListRow final : TSharedFromThis<FConsoleVariablesEditorListRow>`  
_L15-180_
- inherits: `TSharedFromThis<FConsoleVariablesEditorListRow>`
- L25 _public prototype_ `~FConsoleVariablesEditorListRow();`
- L27 _public prototype_ `void FlushReferences();`
- L29 _public function_ `FConsoleVariablesEditorListRow( const TWeakPtr<FConsoleVariablesEditorCommandInfo> InCommandInfo, const FString& InPresetValue, const EConsoleVariablesEditorListRowType InRowType, const ECheckBoxState StartingWidgetCheckboxState, const TSharedRef<SConsoleVariablesEditorList>& InListView, const int32 IndexInList, const TWeakPtr<FConsoleVariablesEditorListRow>& InDirectParentRow) : CommandInfo(InCommandInfo) , PresetValue(InPresetValue) , RowType(InRowType) , WidgetCheckedState(StartingWidgetCheckboxState) , ListViewPtr(InListView) , SortOrder(IndexInList) , DirectParentRow(InDirectParentRow)`
- L52 _public prototype_ `[[nodiscard]] TWeakPtr<FConsoleVariablesEditorCommandInfo> GetCommandInfo() const;`
- L54 _public prototype_ `[[nodiscard]] EConsoleVariablesEditorListRowType GetRowType() const;`
- L56 _public prototype_ `[[nodiscard]] int32 GetChildDepth() const;`
- L57 _public prototype_ `void SetChildDepth(const int32 InDepth);`
- L59 _public prototype_ `[[nodiscard]] int32 GetSortOrder() const;`
- L60 _public prototype_ `void SetSortOrder(const int32 InNewOrder);`
- L62 _public prototype_ `TWeakPtr<FConsoleVariablesEditorListRow> GetDirectParentRow() const;`
- L63 _public prototype_ `void SetDirectParentRow(const TWeakPtr<FConsoleVariablesEditorListRow>& InDirectParentRow);`
- L66 _public prototype_ `[[nodiscard]] const TArray<FConsoleVariablesEditorListRowPtr>& GetChildRows() const;` — bHasGeneratedChildren must be true to get actual children.
- L68 _public prototype_ `[[nodiscard]] int32 GetChildCount() const;` — bHasGeneratedChildren must be true to get an accurate value.
- L69 _public prototype_ `void SetChildRows(const TArray<FConsoleVariablesEditorListRowPtr>& InChildRows);`
- L70 _public prototype_ `void AddToChildRows(const FConsoleVariablesEditorListRowPtr& InRow);`
- L71 _public prototype_ `void InsertChildRowAtIndex(const FConsoleVariablesEditorListRowPtr& InRow, const int32 AtIndex = 0);`
- L73 _public prototype_ `[[nodiscard]] bool GetIsTreeViewItemExpanded() const;`
- L74 _public prototype_ `void SetIsTreeViewItemExpanded(const bool bNewExpanded);`
- L76 _public prototype_ `[[nodiscard]] bool GetShouldFlashOnScrollIntoView() const;`
- L77 _public prototype_ `void SetShouldFlashOnScrollIntoView(const bool bNewShouldFlashOnScrollIntoView);`
- L80 _public member_ `FSimpleMulticastDelegate OnFlashRequested;` — Broadcast to the row widget to play its flash animation.
- L81 _public function_ `void RequestFlash()`
- L83 _public prototype_ `[[nodiscard]] bool GetShouldExpandAllChildren() const;`
- L84 _public prototype_ `void SetShouldExpandAllChildren(const bool bNewShouldExpandAllChildren);`
- L86 _public prototype_ `void ResetToStartupValueAndSource() const;`
- L88 _public prototype_ `[[nodiscard]] const FString& GetPresetValue() const;`
- L89 _public prototype_ `void SetPresetValue(const FString& InPresetValue);`
- L96 _public prototype_ `bool MatchSearchTokensToSearchTerms(const TArray<FString> InTokens, ESearchCase::Type InSearchCase = ESearchCase::IgnoreCase);` — Individual members of InTokens will be considered "AnyOf" or "OR" searches. If SearchTerms contains any individual member it will match. Members will be tested for a space character (" "). If a space is found, a subsearch will be run. This subsearch will be an "AllOf" or "AND" type search in which all strings, separated by a space, must be found in the search terms.
- L99 _public prototype_ `void ExecuteSearchOnChildNodes(const FString& SearchString) const;` — This overload creates tokens from a string first, then calls ExecuteSearchOnChildNodes(const TArray<FString>& Tokens).
- L100 _public prototype_ `void ExecuteSearchOnChildNodes(const TArray<FString>& Tokens) const;`
- L102 _public prototype_ `[[nodiscard]] bool GetDoesRowPassFilters() const;`
- L103 _public prototype_ `void SetDoesRowPassFilters(const bool bPass);`
- L105 _public prototype_ `[[nodiscard]] bool DoesCurrentValueDifferFromPresetValue() const;`
- L106 _public prototype_ `void SetDoesCurrentValueDifferFromPresetValue(const bool bNewValue);`
- L108 _public prototype_ `[[nodiscard]] bool GetIsSelected() const;`
- L109 _public prototype_ `void SetIsSelected(const bool bNewSelected);`
- L111 _public prototype_ `[[nodiscard]] ECheckBoxState GetWidgetCheckedState() const;`
- L112 _public prototype_ `void SetWidgetCheckedState(const ECheckBoxState NewState, const bool bShouldUpdateHierarchyCheckedStates = false);`
- L114 _public prototype_ `[[nodiscard]] bool IsRowChecked() const;`
- L116 _public prototype_ `[[nodiscard]] bool ShouldBeVisible() const;`
- L117 _public prototype_ `[[nodiscard]] EVisibility GetDesiredVisibility() const;`
- L119 _public function_ `[[nodiscard]] bool HasVisibleChildren() const`
- L124 _public function_ `[[nodiscard]] TWeakPtr<SConsoleVariablesEditorList> GetListViewPtr() const`
- L129 _public prototype_ `[[nodiscard]] const FString& GetCachedValue() const;`
- L130 _public prototype_ `void SetCachedValue(const FString& CachedValue);`
- L132 _public prototype_ `[[nodiscard]] TArray<FConsoleVariablesEditorListRowPtr> GetSelectedTreeViewItems() const;`
- L135 _public prototype_ `[[nodiscard]] bool IsGlobalSearch() const;` — Return true if the row is being displayed in Global Search mode.
- L138 _public prototype_ `[[nodiscard]] bool IsInPreset() const;` — Return true if the command represented by the row is included in the current preset.
- L145 _public prototype_ `[[nodiscard]] TArray<FConsoleVariablesEditorListRowPtr> GetRowsAffectedByActions();` — Get an array of all rows that should be affected if an action is performed on this row. This takes multi-selection into account and imitates the Outliner visibility widget's behavior by only returning the row itself if the row is outside of the current selection.
- L147 _public prototype_ `FReply OnActionButtonClicked();`
- L149 _public prototype_ `void ResetToPresetValue();`
- L153 _private member_ `TWeakPtr<FConsoleVariablesEditorCommandInfo> CommandInfo;`
- L154 _private member_ `FString PresetValue = "";`
- L155 _private member_ `EConsoleVariablesEditorListRowType RowType = SingleCommand;`
- L156 _private member_ `TArray<FConsoleVariablesEditorListRowPtr> ChildRows;`
- L158 _private member_ `ECheckBoxState WidgetCheckedState = ECheckBoxState::Checked;`
- L160 _private member_ `TWeakPtr<SConsoleVariablesEditorList> ListViewPtr;`
- L161 _private member_ `FString CachedValue = "";`
- L163 _private member_ `bool bIsTreeViewItemExpanded = false;`
- L164 _private member_ `bool bShouldFlashOnScrollIntoView = false;`
- L166 _private member_ `int32 ChildDepth = 0;`
- L168 _private member_ `int32 SortOrder = -1;`
- L170 _private member_ `bool bDoesRowMatchSearchTerms = true;`
- L171 _private member_ `bool bDoesRowPassFilters = true;`
- L173 _private member_ `bool bDoesCurrentValueDifferFromPresetValue = false;`
- L175 _private member_ `bool bIsSelected = false;`
- L176 _private member_ `TWeakPtr<FConsoleVariablesEditorListRow> DirectParentRow;`
- L179 _private member_ `bool bShouldExpandAllChildren = false;` — Used to expand all children on shift+click.

#### enum `FConsoleVariablesEditorListRow::EConsoleVariablesEditorListRowType`  
`enum EConsoleVariablesEditorListRowType`  
_L17-23_
- L19 _public enumerator_ `None`
- L20 _public enumerator_ `HeaderRow`
- L21 _public enumerator_ `CommandGroup` — Group of commands or subgroups
- L22 _public enumerator_ `SingleCommand`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<FConsoleVariablesEditorListRow> FConsoleVariablesEditorListRowPtr;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/SConsoleVariablesEditorList.h` (Private)


#### class `SConsoleVariablesEditorList`  
`class SConsoleVariablesEditorList final : public SCompoundWidget`  
_L26-235_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorList)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FConsoleVariablesEditorList> ListModel);`
- L40 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _public function_ `TWeakPtr<FConsoleVariablesEditorList> GetListModelPtr()`
- L47 _public prototype_ `FReply TryEnterGlobalSearch(const FString& SearchString = "");`
- L48 _public prototype_ `FReply HandleRemoveGlobalSearchToggleButton();`
- L49 _public prototype_ `void CleanUpGlobalSearchesMarkedForDelete();`
- L51 _public prototype_ `void RefreshGlobalSearchWidgets();` — Remove all widgets from the global search container then recreate them
- L57 _public prototype_ `void RebuildListWithListMode(FConsoleVariablesEditorList::EConsoleVariablesEditorListMode NewListMode, const FString& InConsoleCommandToScrollTo = "", bool bShouldCacheValues = true);` — Regenerate the list items and refresh the list. Call when adding or removing variables. @param bShouldCacheValues If true, the current list's current values will be cached and then restored when the list is rebuilt. Otherwise preset values will be used.
- L63 _public prototype_ `void RefreshList();` — Refresh filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L65 _public prototype_ `[[nodiscard]] TArray<FConsoleVariablesEditorListRowPtr> GetSelectedTreeViewItems() const;`
- L67 _public prototype_ `[[nodiscard]] TArray<FConsoleVariablesEditorListRowPtr> GetTreeViewItems() const;`
- L68 _public prototype_ `void SetTreeViewItems(const TArray<FConsoleVariablesEditorListRowPtr>& InItems);`
- L71 _public prototype_ `void UpdatePresetValuesForSave(const TObjectPtr<UConsoleVariablesAsset> InAsset) const;` — Updates the saved values in a UConsoleVariablesAsset so that the command/value map can be saved to disk
- L74 _public prototype_ `void UpdateCachedValue(const FString& InCommand, const FString& InValue);` — Update the cached value stored for the given command.
- L76 _public prototype_ `FString GetSearchStringFromSearchInputField() const;`
- L77 _public prototype_ `void SetSearchStringInSearchInputField(const FString InSearchString) const;`
- L78 _public prototype_ `void ExecuteListViewSearchOnAllRows(const FString& SearchString, const bool bShouldRefreshAfterward = true);`
- L80 _public prototype_ `bool DoesTreeViewHaveVisibleChildren() const;`
- L82 _public prototype_ `void SetTreeViewItemExpanded(const TSharedPtr<FConsoleVariablesEditorListRow>& RowToExpand, const bool bNewExpansion) const;`
- L84 _public prototype_ `void SetAllListViewItemsCheckState(const ECheckBoxState InNewState);`
- L86 _public prototype_ `bool DoesListHaveCheckedMembers() const;`
- L88 _public prototype_ `bool DoesListHaveUncheckedMembers() const;`
- L90 _public prototype_ `void OnListItemCheckBoxStateChange(const ECheckBoxState InNewState);`
- L92 _public prototype_ `void ToggleFilterActive(const FString& FilterName);`
- L93 _public prototype_ `void EvaluateIfRowsPassFilters(const bool bShouldRefreshAfterward = true);`
- L97 _public function_ `const FName& GetActiveSortingColumnName() const`
- L101 _public prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName InColumnName) const;`
- L102 _public prototype_ `void OnSortColumnCalled(EColumnSortPriority::Type Priority, const FName& ColumnName, EColumnSortMode::Type SortMode);`
- L103 _public prototype_ `EColumnSortMode::Type CycleSortMode(const FName& InColumnName);`
- L104 _public prototype_ `void ExecuteSort( const FName& InColumnName, const EColumnSortMode::Type InColumnSortMode, const bool bShouldRefreshAfterward = true);`
- L106 _public function_ `void ClearSorting()`
- L111 _public prototype_ `void SetSortOrder(const bool bShouldRefreshAfterward = true);`
- L115 _public prototype_ `void CopySelectedVariableNames();`
- L116 _public prototype_ `void CopySelectedNamesAndValues();`
- L117 _public prototype_ `void CopySelectedValues();`
- L118 _public prototype_ `void PasteValueToSelectedVariable();`
- L119 _public prototype_ `void PasteNameAndValue();`
- L123 _public member_ `static const FName CustomSortOrderColumnName;`
- L124 _public member_ `static const FName CheckBoxColumnName;`
- L125 _public member_ `static const FName VariableNameColumnName;`
- L126 _public member_ `static const FName ValueColumnName;`
- L127 _public member_ `static const FName SourceColumnName;`
- L128 _public member_ `static const FName ActionButtonColumnName;`
- L132 _private member_ `TWeakPtr<FConsoleVariablesEditorList> ListModelPtr;`
- L134 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L135 _private prototype_ `TSharedPtr<SHeaderRow> GenerateHeaderRow();`
- L136 _private member_ `ECheckBoxState HeaderCheckBoxState = ECheckBoxState::Checked;`
- L138 _private prototype_ `void SetupFilters();`
- L140 _private prototype_ `TSharedRef<SWidget> BuildShowOptionsMenu();`
- L142 _private prototype_ `void FlushMemory(const bool bShouldKeepMemoryAllocated);`
- L144 _private prototype_ `void SetAllGroupsCollapsed();`
- L148 _private prototype_ `void OnListViewSearchTextChanged(const FText& Text);`
- L150 _private member_ `TSharedPtr<SSearchBox> ListSearchBoxPtr;`
- L151 _private member_ `TSharedPtr<SComboButton> ViewOptionsComboButton;`
- L154 _private member_ `TSharedPtr<SHorizontalBox> GlobalSearchesHBox;` — Contains the GlobalSearchesContainer and remove button. Made a member in order to collapse it when GlobalSearchesContainer has no children.
- L156 _private member_ `TSharedPtr<SWrapBox> GlobalSearchesContainer;` — Contains the global search checkboxes only
- L157 _private member_ `TArray<TSharedRef<SConsoleVariablesEditorGlobalSearchToggle>> CurrentGlobalSearches;`
- L159 _private member_ `TSharedPtr<SCheckBox> RemoveGlobalSearchesButtonPtr;`
- L160 _private member_ `TSharedPtr<SBox> ListBoxContainerPtr;`
- L164 _private prototype_ `TSharedPtr<SWidget> OnTreeViewContextMenuOpening();`
- L165 _private prototype_ `TSharedRef<SWidget> BuildContextMenuWidget();`
- L166 _private prototype_ `FReply OnEmptyAreaMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L169 _private prototype_ `void FlashSelectedRows();` — Flash all currently selected rows, e.g. after a Ctrl+C / Ctrl+V hotkey.
- L171 _private prototype_ `void FlashRowByCommand(const FString& InCommandName);` — Flash a row whose command matches InCommandName (case-insensitive).
- L173 _private member_ `TSharedPtr<SBorder> EmptyAreaBorder;`
- L177 _private prototype_ `void CacheCurrentListItemData();`
- L178 _private prototype_ `void RestorePreviousListItemData();`
- L179 _private prototype_ `void GenerateTreeView(const bool bSkipExecutionOfCachedCommands = true);`
- L180 _private prototype_ `void FindVisibleTreeViewObjects();`
- L181 _private prototype_ `void FindVisibleObjectsAndRequestTreeRefresh();`
- L183 _private prototype_ `void OnGetRowChildren(FConsoleVariablesEditorListRowPtr Row, TArray<FConsoleVariablesEditorListRowPtr>& OutChildren) const;`
- L184 _private prototype_ `void OnRowChildExpansionChange(FConsoleVariablesEditorListRowPtr Row, const bool bIsExpanded, const bool bIsRecursive = false) const;`
- L186 _private prototype_ `void SetChildExpansionRecursively(const FConsoleVariablesEditorListRowPtr& InRow, const bool bNewIsExpanded) const;`
- L188 _private prototype_ `const FSlateBrush* GetActionColumnImage() const;`
- L190 _private member_ `TArray<TSharedRef<IConsoleVariablesEditorListFilter>> ShowFilters;`
- L192 _private member_ `TSharedPtr<STreeView<FConsoleVariablesEditorListRowPtr>> TreeViewPtr;`
- L195 _private member_ `TArray<FConsoleVariablesEditorListRowPtr> TreeViewRootObjects;` — All Tree view objects
- L197 _private member_ `TArray<FConsoleVariablesEditorListRowPtr> VisibleTreeViewObjects;` — Visible Tree view objects, after filters
- L201 _private member_ `TArray<FConsoleVariablesEditorListRowPtr> LastPresetObjects;` — When a global search is initiated we cache the tree objects shown in preset list mode This way they can be recalled without rebuilding from the saved commands
- L204 _private member_ `TArray<FConsoleVariablesEditorAssetSaveData> CachedCommandStates;` — A collection of list item data to save and restore when rebuilding the list.
- L208 _private member_ `FName ActiveSortingColumnName = NAME_None;`
- L209 _private member_ `EColumnSortMode::Type ActiveSortingType = EColumnSortMode::None;`
- L211 _private member_ `TFunction<bool(const FConsoleVariablesEditorListRowPtr&, const FConsoleVariablesEditorListRowPtr&)> SortByOrderAscending = [](const FConsoleVariablesEditorListRowPtr& A, const FConsoleVariablesEditorListRowPtr& B) { return A->GetSortOrder() < B->GetSortOrder(); };`
- L212 _private function_ ``
- L216 _private member_ `TFunction<bool(const FConsoleVariablesEditorListRowPtr&, const FConsoleVariablesEditorListRowPtr&)> SortBySourceAscending = [](const FConsoleVariablesEditorListRowPtr& A, const FConsoleVariablesEditorListRowPtr& B) { return A->GetCommandInfo().Pin()->GetSourceAsText().ToString() < B->GetCommandInfo().Pin()->GetSourceAsText().ToString(); };`
- L221 _private member_ `TFunction<bool(const FConsoleVariablesEditorListRowPtr&, const FConsoleVariablesEditorListRowPtr&)> SortBySourceDescending = [](const FConsoleVariablesEditorListRowPtr& A, const FConsoleVariablesEditorListRowPtr& B) { return B->GetCommandInfo().Pin()->GetSourceAsText().ToString() < A->GetCommandInfo().Pin()->GetSourceAsText().ToString(); };`
- L226 _private member_ `TFunction<bool(const FConsoleVariablesEditorListRowPtr&, const FConsoleVariablesEditorListRowPtr&)> SortByVariableNameAscending = [](const FConsoleVariablesEditorListRowPtr& A, const FConsoleVariablesEditorListRowPtr& B) { return A->GetCommandInfo().Pin()->Command < B->GetCommandInfo().Pin()->Command; };`
- L231 _private member_ `TFunction<bool(const FConsoleVariablesEditorListRowPtr&, const FConsoleVariablesEditorListRowPtr&)> SortByVariableNameDescending = [](const FConsoleVariablesEditorListRowPtr& A, const FConsoleVariablesEditorListRowPtr& B) { return B->GetCommandInfo().Pin()->Command < A->GetCommandInfo().Pin()->Command; };`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/SConsoleVariablesEditorListRow.h` (Private)


#### class `SConsoleVariablesEditorListRow`  
`class SConsoleVariablesEditorListRow : public SMultiColumnTableRow<FConsoleVariablesEditorListRowPtr>`  
_L19-87_
- inherits: `SMultiColumnTableRow<FConsoleVariablesEditorListRowPtr>`
- L23 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListRow)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L30 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L37 _public prototype_ `void HandleDragLeave(const FDragDropEvent& DragDropEvent);`
- L38 _public prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, FConsoleVariablesEditorListRowPtr TargetItem);`
- L39 _public prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, FConsoleVariablesEditorListRowPtr TargetItem);`
- L41 _public prototype_ `void FlashRow();`
- L43 _public prototype_ `EVisibility GetHoverableWidgetsVisibility() const;`
- L44 _public prototype_ `EVisibility GetFlashImageVisibility() const;`
- L45 _public prototype_ `FSlateColor GetFlashImageColorAndOpacity() const;`
- L47 _public prototype_ `static const FSlateBrush* GetBorderImage(const FConsoleVariablesEditorListRow::EConsoleVariablesEditorListRowType InRowType);`
- L49 _public prototype_ `TSharedRef<SWidget> GenerateCells(const FName& InColumnName, const TSharedPtr<FConsoleVariablesEditorListRow> PinnedItem);`
- L51 _public prototype_ `ECheckBoxState GetCheckboxState() const;`
- L52 _public prototype_ `void OnCheckboxStateChange(const ECheckBoxState InNewState) const;`
- L54 _public prototype_ `TSharedRef<SWidget> GenerateValueCellWidget(const TSharedPtr<FConsoleVariablesEditorListRow> PinnedItem);`
- L58 _public member_ `const FText ValueWidgetToolTipFormatText = LOCTEXT("ValueWi`
- L59 _public member_ `const FText RevertButtonFormatText = LOCTEXT("RevertB`
- L61 _public member_ `const FText InsertFormatText = LOCTEXT("InsertA`
- L62 _public member_ `const FText AboveText = LOCTEXT("AboveLi`
- L63 _public member_ `const FText BelowText = LOCTEXT("BelowLi`
- L64 _public member_ `static const inline FText MultiDragFormatText = LOCTEXT("MultiDr`
- L70 _private member_ `TWeakPtr<FConsoleVariablesEditorListRow> Item;`
- L72 _private member_ `TSharedPtr<IToolTip> HoverToolTip;`
- L74 _private member_ `TArray<TSharedPtr<SImage>> FlashImages;`
- L76 _private member_ `TSharedPtr<SConsoleVariablesEditorListValueInput> ValueChildInputWidget;`
- L78 _private member_ `TSharedPtr<SConsoleVariablesEditorListRowHoverWidgets> HoverableWidgetsPtr;`
- L80 _private member_ `FCurveSequence FlashAnimation;`
- L82 _private member_ `const float FlashAnimationDuration = 0.75f;`
- L83 _private member_ `const FLinearColor FlashColor = FLinearColor::White;`
- L86 _private member_ `float TextBlockLeftPadding = 5.0f;` — The offset applied to text widgets so that the text aligns with the column header text

#### class `SConsoleVariablesEditorListRowHoverWidgets`  
`class SConsoleVariablesEditorListRowHoverWidgets : public SCompoundWidget`  
_L89-109_
- inherits: `SCompoundWidget`
- L93 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListRowHoverWidgets)`
- L96 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L104 _private prototype_ `FSlateColor GetActionButtonColorAndOpacity() const;`
- L105 _private prototype_ `const FSlateBrush* GetButtonImage() const;`
- L106 _private prototype_ `FText GetButtonTooltip() const;`
- L108 _private member_ `TWeakPtr<FConsoleVariablesEditorListRow> Item;`

#### Free symbols / members of external scopes

- L56 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/List/SConsoleVariablesEditorListValueInput.h` (Private)


#### class `SConsoleVariablesEditorListValueInput`  
`class SConsoleVariablesEditorListValueInput : public SCompoundWidget`  
_L15-32_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `static TSharedRef<SConsoleVariablesEditorListValueInput> GetInputWidget(const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L22 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) = 0;`
- L23 _public prototype_ `virtual FString GetInputValueAsString() = 0;`
- L25 _public prototype_ `bool IsRowChecked() const;`
- L29 _protected member_ `TWeakPtr<FConsoleVariablesEditorListRow> Item = nullptr;`
- L31 _protected member_ `TObjectPtr<UConsoleVariablesEditorProjectSettings> ProjectSettingsPtr = nullptr;`

#### class `SConsoleVariablesEditorListValueInput_Float`  
`class SConsoleVariablesEditorListValueInput_Float : public SConsoleVariablesEditorListValueInput`  
_L34-56_
- inherits: `SConsoleVariablesEditorListValueInput`
- L38 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListValueInput_Float)`
- L41 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L47 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) override;`
- L48 _public prototype_ `virtual FString GetInputValueAsString() override;`
- L50 _public prototype_ `float GetInputValue() const;`
- L51 _public prototype_ `void OnSliderAffected(const float InValue, const bool bPrintCommand);`
- L55 _private member_ `TSharedPtr<SSpinBox<float>> InputWidget;`

#### class `SConsoleVariablesEditorListValueInput_Int`  
`class SConsoleVariablesEditorListValueInput_Int : public SConsoleVariablesEditorListValueInput`  
_L58-81_
- inherits: `SConsoleVariablesEditorListValueInput`
- L62 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListValueInput_Int)`
- L65 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow, const bool bIsShowFlag = false);`
- L72 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) override;`
- L73 _public prototype_ `virtual FString GetInputValueAsString() override;`
- L75 _public prototype_ `int32 GetInputValue() const;`
- L76 _public prototype_ `void OnSliderAffected(const int32 InValue, const bool bPrintCommand);`
- L80 _private member_ `TSharedPtr<SSpinBox<int32>> InputWidget;`

#### class `SConsoleVariablesEditorListValueInput_String`  
`class SConsoleVariablesEditorListValueInput_String : public SConsoleVariablesEditorListValueInput`  
_L83-104_
- inherits: `SConsoleVariablesEditorListValueInput`
- L87 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListValueInput_String)`
- L90 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L96 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) override;`
- L97 _public prototype_ `virtual FString GetInputValueAsString() override;`
- L99 _public prototype_ `FString GetInputValue() const;`
- L103 _private member_ `TSharedPtr<SEditableTextBox> InputWidget;`

#### class `SConsoleVariablesEditorListValueInput_Bool`  
`class SConsoleVariablesEditorListValueInput_Bool : public SConsoleVariablesEditorListValueInput`  
_L106-139_
- inherits: `SConsoleVariablesEditorListValueInput`
- L110 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListValueInput_Bool)`
- L113 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow);`
- L119 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) override;`
- L120 _public prototype_ `void SetInputValue(const bool bNewValue);`
- L121 _public prototype_ `virtual FString GetInputValueAsString() override;`
- L123 _public prototype_ `bool GetInputValue();`
- L125 _public function_ `static bool StringToBool(const FString& InString)`
- L130 _public function_ `static FString BoolToString(const bool bNewBool)`
- L137 _private member_ `TSharedPtr<SButton> InputWidget;`
- L138 _private member_ `TSharedPtr<STextBlock> ButtonText;`

#### class `SConsoleVariablesEditorListValueInput_Command`  
`class SConsoleVariablesEditorListValueInput_Command : public SConsoleVariablesEditorListValueInput`  
_L141-164_
- inherits: `SConsoleVariablesEditorListValueInput`
- L145 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorListValueInput_Command)`
- L148 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TWeakPtr<FConsoleVariablesEditorListRow> InRow, const FString& InSavedText);`
- L155 _public prototype_ `virtual void SetInputValue(const FString& InValueAsString) override;`
- L156 _public prototype_ `virtual FString GetInputValueAsString() override;`
- L158 _public prototype_ `FString GetInputValue() const;`
- L162 _private member_ `TSharedPtr<SButton> InputWidget;`
- L163 _private member_ `TSharedPtr<SEditableTextBox> InputText;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/MainPanel/ConsoleVariablesEditorMainPanel.h` (Private)


#### class `FConsoleVariablesEditorMainPanel`  
`class FConsoleVariablesEditorMainPanel : public TSharedFromThis<FConsoleVariablesEditorMainPanel>`  
_L17-105_
- inherits: `TSharedFromThis<FConsoleVariablesEditorMainPanel>`
- L20 _public prototype_ `FConsoleVariablesEditorMainPanel();`
- L22 _public prototype_ `~FConsoleVariablesEditorMainPanel();`
- L24 _public prototype_ `TSharedRef<SWidget> GetOrCreateWidget();`
- L26 _public prototype_ `static FConsoleVariablesEditorModule& GetConsoleVariablesModule();`
- L27 _public prototype_ `static TObjectPtr<UConsoleVariablesAsset> GetEditingAsset();`
- L29 _public prototype_ `void AddConsoleObjectToCurrentPreset( const FString InConsoleCommand, const FString InValue, const bool bScrollToNewRow = false) const;`
- L33 _public prototype_ `void UpdateCachedValue(const FString& InConsoleVar, const FString& Value);`
- L35 _public prototype_ `void OnRemoteCvarChanged();`
- L37 _public prototype_ `FReply ValidateConsoleInputAndAddToCurrentPreset(const FText& CommittedText) const;`
- L43 _public prototype_ `void RebuildList(const FString InConsoleCommandToScrollTo = "", bool bShouldCacheValues = true) const;` — Regenerate the list items and refresh the list. Call when adding or removing variables. @param bShouldCacheValues If true, the current list's current values will be cached and then restored when the list is rebuilt. Otherwise preset values will be used.
- L49 _public prototype_ `void RefreshList() const;` — Refresh filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L51 _public prototype_ `void UpdatePresetValuesForSave(TObjectPtr<UConsoleVariablesAsset> InAsset) const;`
- L53 _public prototype_ `void RefreshMultiUserDetails() const;`
- L57 _public prototype_ `void SaveCurrentPreset();`
- L58 _public prototype_ `void SaveSpecificPreset(const TObjectPtr<UConsoleVariablesAsset> InPreset) const;`
- L59 _public prototype_ `void SaveCurrentPresetAs();`
- L60 _public prototype_ `void SaveSpecificPresetAs(const TObjectPtr<UConsoleVariablesAsset> InPreset) const;`
- L61 _public prototype_ `void ImportPreset(const FAssetData& InPresetAsset, const EConsoleVariablesEditorPresetImportMode InImportMode = EConsoleVariablesEditorPresetImportMode::UseDefault);`
- L62 _public prototype_ `void ImportPreset(const TObjectPtr<UConsoleVariablesAsset> InPreset);`
- L64 _public function_ `TWeakObjectPtr<UConsoleVariablesAsset> GetReferenceAssetOnDisk() const`
- L69 _public function_ `TWeakPtr<FConsoleVariablesEditorList> GetEditorList() const`
- L74 _public function_ `FConsoleVariablesEditorList::EConsoleVariablesEditorListMode GetEditorListMode() const`
- L79 _public function_ `UE::ConsoleVariables::MultiUser::Private::FManager& GetMultiUserManager()`
- L86 _private prototype_ `bool ImportPreset_Impl(const TObjectPtr<UConsoleVariablesAsset> Preset, const TObjectPtr<UConsoleVariablesAsset> EditingAsset, const EConsoleVariablesEditorPresetImportMode InImportMode);`
- L88 _private member_ `TSharedPtr<SConsoleVariablesEditorMainPanel> MainPanelWidget;`
- L91 _private member_ `TWeakObjectPtr<UConsoleVariablesAsset> ReferenceAssetOnDisk;` — The non-transient loaded asset from which we will copy to the transient asset for editing
- L93 _private member_ `TSharedPtr<FConsoleVariablesEditorList> EditorList;`
- L95 _private prototype_ `static void OnConnectionChanged(EConcertConnectionStatus Status);`
- L96 _private prototype_ `static void OnRemoteCvarChange(ERemoteCVarChangeType InChangeType, FString InName, FString InValue, EConsoleVariableFlags InFlags);`
- L97 _private prototype_ `static void OnRemoteListItemCheckStateChange(const FString InName, ECheckBoxState InCheckedState);`
- L99 _private prototype_ `void SendListItemCheckStateChange(const FString& InName, ECheckBoxState InCheckedState);`
- L101 _private member_ `UE::ConsoleVariables::MultiUser::Private::FManager MultiUserManager;`
- L102 _private member_ `FDelegateHandle OnConnectionChangedHandle;`
- L103 _private member_ `FDelegateHandle OnRemoteCVarChangeHandle;`
- L104 _private member_ `FDelegateHandle OnRemoteListItemCheckStateChangeHandle;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/MainPanel/SConsoleVariablesEditorMainPanel.h` (Private)


#### class `SConsoleVariablesEditorMainPanel`  
`class SConsoleVariablesEditorMainPanel final : public SCompoundWidget`  
_L15-70_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorMainPanel)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FConsoleVariablesEditorMainPanel>& InMainPanel);`
- L30 _public prototype_ `void ValidateConsoleInputAndAddToCurrentPreset(const FText& CommittedText) const;` — A handler for when text is committed to the Console Input Box that appears when clicking the "Add Console Variable" button
- L32 _public prototype_ `void RefreshMultiUserDetails() const;`
- L33 _public prototype_ `void ToggleMultiUserDetails(ECheckBoxState CheckState) const;`
- L38 _private member_ `TWeakPtr<FConsoleVariablesEditorMainPanel> MainPanel;` — A reference to the struct that controls this widget
- L40 _private member_ `TSharedPtr<SConsoleVariablesEditorCustomConsoleInputBox> AddConsoleObjectInputBoxPtr;`
- L42 _private member_ `TSharedPtr<SHorizontalBox> ToolbarHBox;`
- L45 _private member_ `TSharedPtr<SCheckBox> ConcertButtonPtr;` — A reference to the button which opens the plugin settings
- L48 _private prototype_ `TSharedRef<SWidget> GeneratePanelToolbar();` — Creates the toolbar at the top of the MainPanel widget
- L50 _private prototype_ `FReply HandleAddConsoleVariableButtonClicked();`
- L52 _private prototype_ `void CreateConcertButtonIfNeeded();`
- L58 _private member_ `const FText NoLoadedPresetText = LOCTEXT("NoLoade`
- L59 _private member_ `const FText LoadedPresetFormatText = LOCTEXT("LoadedP`
- L64 _private prototype_ `TSharedRef<SWidget> OnGeneratePresetsMenu();` — Creates a special asset picker widget to display when the Save/Load button is clicked
- L66 _private member_ `TSharedPtr<SVerticalBox> MultiUserDetailsBox;`
- L69 _private prototype_ `static TSharedRef<SWidget> GetConcertDetailsWidget(UObject* InObject);` — Generates a customized details widget given an object. Intended for multi-user settings display.

#### Free symbols / members of external scopes

- L56 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/Widgets/SConsoleVariablesEditorGlobalSearchToggle.h` (Private)


#### class `SConsoleVariablesEditorGlobalSearchToggle`  
`class SConsoleVariablesEditorGlobalSearchToggle : public SCompoundWidget`  
_L12-64_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorGlobalSearchToggle)`
- L18 _public prototype_ `SLATE_EVENT(FOnClicked, OnToggleCtrlClicked) SLATE_EVENT(FOnClicked, OnToggleAltClicked) SLATE_EVENT(FOnClicked, OnToggleMiddleButtonClicked) SLATE_EVENT(FOnClicked, OnToggleRightButtonClicked) SLATE_EVENT(FOnClicked, OnToggleClickedOnce) SLATE_END_ARGS();`
- L25 _public prototype_ `void Construct(const FArguments& Args, const FText& InButtonText);`
- L29 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L33 _public prototype_ `[[nodiscard]] bool GetIsToggleChecked() const;`
- L34 _public prototype_ `[[nodiscard]] ECheckBoxState GetCheckedState() const;`
- L35 _public prototype_ `void SetIsButtonChecked(const bool bNewIsButtonChecked);`
- L37 _public prototype_ `[[nodiscard]] bool GetIsMarkedForDelete() const;`
- L38 _public prototype_ `void SetIsMarkedForDelete(const bool bNewMark);`
- L40 _public function_ `const FText& GetGlobalSearchText()`
- L47 _private member_ `FOnClicked OnToggleCtrlClicked;`
- L48 _private member_ `FOnClicked OnToggleAltClicked;`
- L49 _private member_ `FOnClicked OnToggleMiddleButtonClicked;`
- L50 _private member_ `FOnClicked OnToggleRightButtonClicked;`
- L51 _private member_ `FOnClicked OnToggleClickedOnce;`
- L53 _private member_ `TSharedPtr<SCheckBox> ToggleButtonPtr;`
- L54 _private member_ `bool bIsToggleChecked = true;`
- L58 _private member_ `bool bIsMarkedForDelete = false;` — When clicked in a special manner, this search button will be marked for deletion The responsibility is on external classes to remove the button from the UI the external class controls.
- L60 _private member_ `FLinearColor CheckedColor;`
- L61 _private member_ `FLinearColor UncheckedColor;`
- L63 _private member_ `FText GlobalSearchText;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/Views/Widgets/SConsoleVariablesEditorTooltipWidget.h` (Private)


#### class `SConsoleVariablesEditorTooltipWidget`  
`class SConsoleVariablesEditorTooltipWidget : public SCompoundWidget`  
_L13-80_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorTooltipWidget)`
- L20 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FString InCommandName, const FString InHelpString)`
- L63 _public function_ `static TSharedRef<SToolTip> MakeTooltip(const FString InCommandName, const FString InHelpString)`
- L79 _private member_ `static constexpr float TooltipWindowWidth = 500.f;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorCommandInfo.h` (Public)


#### struct `FConsoleVariablesEditorCommandInfo`  
`struct FConsoleVariablesEditorCommandInfo`  
_L16-156_
- L34 _public function_ `FConsoleVariablesEditorCommandInfo(const FString& InCommand) : Command(InCommand)`
- L50 _public function_ `~FConsoleVariablesEditorCommandInfo()`
- L61 _public function_ `FORCEINLINE bool operator==(const FConsoleVariablesEditorCommandInfo& Comparator) const`
- L66 _public function_ `void SetIfChangedInCurrentPreset(const bool bNewSetting)`
- L78 _public prototype_ `void ExecuteCommand( const FString& NewValueAsString, const bool bShouldTransactInConcert = true, const bool bSetInSession = true, const bool bIsInteractiveChange = false);` — Sets a variable to the specified value whilst maintaining its SetBy flag. Non-variables will be executed through the console. @param bShouldTransactInConcert If true, send this value to multi-user. @param bSetInSession If true, this CommandInfo's associated variable row will display "Session" in the UI. @param bIsInteractiveChange If true, don't print the command or send it to multi-user/concert.
- L85 _public prototype_ `void PrintCommandOrVariable();` — Prints the current value or state of the command, similar to the text generated in teh output log when entering a command manually.
- L88 _public prototype_ `IConsoleObject* GetConsoleObjectPtr();` — Get a reference to the cached console object. May return nullptr if unregistered.
- L91 _public prototype_ `IConsoleVariable* GetConsoleVariablePtr();` — Return the console object as a console variable object if applicable. May return nullptr if unregistered.
- L97 _public prototype_ `IConsoleCommand* GetConsoleCommandPtr();` — Return the console object as a console command object if applicable. Does not consider externally parsed console commands, as they have no associated objects.
- L99 _public prototype_ `static UWorld* GetCurrentWorld();`
- L101 _public prototype_ `FString GetHelpText();`
- L103 _public prototype_ `EConsoleVariableFlags GetSource();`
- L105 _public prototype_ `void ClearSourceFlags();`
- L107 _public prototype_ `void SetSourceFlag(const EConsoleVariableFlags InSource);`
- L109 _public prototype_ `FText GetSourceAsText();`
- L111 _public prototype_ `static FText ConvertConsoleVariableSetByFlagToText(const EConsoleVariableFlags InFlag);`
- L117 _public prototype_ `bool GetCurrentValueAsString(FString& OutValueAsString);` — If this console object is a variable, get its value as string via OutValueAsString. If it's not a variable type (such as a command) then this function will return false.
- L119 _public prototype_ `bool IsCurrentValueDifferentFromInputValue(const FString& InValueToCompare);`
- L121 _public prototype_ `void OnConsoleVariableChanged(IConsoleVariable* ChangedVariable);`
- L125 _public member_ `FString Command;` — `UPROPERTY()` — The actual string key or name
- L126 _public member_ `EConsoleObjectType ObjectType = EConsoleObjectType::NullObject;`
- L128 _public member_ `IConsoleObject* ConsoleObjectPtr = nullptr;` — This object is periodically refreshed to mitigate the occurrence of stale pointers.
- L131 _public member_ `FString StartupValueAsString;` — The value of this variable (if Variable object type) when the module started in this session after it may have been set by an ini file.
- L134 _public member_ `EConsoleVariableFlags StartupSource = ECVF_Default;` — The source of this variable's (if Variable object type) last setting as recorded when the plugin was loaded.
- L136 _public member_ `bool bSetInCurrentSession = false;` — If the variable was last changed by the current preset
- L137 _public member_ `bool bHasAttemptedFind = false;`
- L139 _public member_ `FDelegateHandle OnVariableChangedCallbackHandle;` — When variables change, this callback is executed.
- L141 _public member_ `static const inline TArray<FStaticConsoleVariableFlagInfo> SupportedFlags = { { EConsoleVariableFlags::ECVF_SetByConstructor, LOCTEXT("Source_SetByConstructor", "Constructor") }, { EConsoleVariableFlags::ECVF_SetByScalability, LOCTEXT("Source_SetByScalability", "Scalability") }, { EConsoleVariableFlags::ECVF_SetByGameSetting, LOCTEXT("Source_SetByGameSetting", "Game Setting") }, { EConsoleVariableFlags::ECVF_SetByProjectSetting, LOCTEXT("Source_SetByProjectSetting", "Project Setting") }, { EConsoleVariableFlags::ECVF_SetBySystemSettingsIni, LOCTEXT("Source_SetBySystemSettingsIni", "System Settings ini") }, { EConsoleVariableFlags::ECVF_SetByDeviceProfile, LOCTEXT("Source_SetByDeviceProfile", "Device Profile") }, { EConsoleVariableFlags::ECVF_SetByGameOverride, LOCTEXT("Source_SetByGameOverride", "Game Override") }, { EConsoleVariableFlags::ECVF_SetByConsoleVariablesIni, LOCTEXT("Source_SetByConsoleVariablesIni", "Console Variables ini") }, { EConsoleVariableFlags::ECVF_SetByCommandline, LOCTEXT("Source_SetByCommandline", "Command line") }, { EConsoleVariableFlags::ECVF_SetByCode, LOCTEXT("Source_SetByCode", "Code") }, { EConsoleVariableFlags::ECVF_SetByConsole, LOCTEXT("Source_SetByConsole", "Console") }, { EConsoleVariableFlags::ECVF_SetByPreview, LOCTEXT("Source_SetByPreview", "Preview") } };` — A mapping of SetBy console variable flags to information like the associated display text.

#### enum `FConsoleVariablesEditorCommandInfo::EConsoleObjectType`  
`enum class EConsoleObjectType`  
_L18-26_
- L21 _public enumerator_ `NullObject` — A console command that has no associated console object but is parsed externally, e.g. 'stat unit'
- L23 _public enumerator_ `Command` — A console command with an associated console object, like 'r.SetNearClipPlane'
- L25 _public enumerator_ `Variable` — A console variable such as 'r.ScreenPercentage'

#### struct `FConsoleVariablesEditorCommandInfo::FStaticConsoleVariableFlagInfo`  
`struct FStaticConsoleVariableFlagInfo`  
_L28-32_
- L30 _public member_ `EConsoleVariableFlags Flag;`
- L31 _public member_ `FText DisplayText;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONSOLEVARIABLESEDITOR_API`
- L14 _macro_ `#define LOCTEXT_NAMESPACE "ConsoleVariablesEditor"`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorFunctionLibrary.h` (Public)


#### class `UConsoleVariablesEditorFunctionLibrary`  
`class UConsoleVariablesEditorFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-92_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: An asset used to track collections of console variables that can be recalled and edited using the Console Variables Editor.
- L26 _public prototype_ `static UConsoleVariablesAsset* GetCurrentlyLoadedPreset();` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Return the currently loaded list of variables in the Console Variables Editor.
- L30 _public prototype_ `static void LoadPresetIntoConsoleVariablesEditor(const UConsoleVariablesAsset* InAsset, const EConsoleVariablesEditorPresetImportMode InImportMode = EConsoleVariablesEditorPresetImportMode::AddToExisting);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Loads the given asset in the Console Variables Editor and sets all its variable values.
- L38 _public prototype_ `static bool CopyCurrentListToAsset(UConsoleVariablesAsset* InAsset);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Saves the current list in the Console Variables Editor to the given asset. The Asset will not be automatically saved. @return true if successful.
- L46 _public prototype_ `static bool AddValidatedCommandToCurrentPreset(const FString NewCommand);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Adds a validated command to the current preset with its current value. The Asset will not be automatically saved. @return true if successful.
- L54 _public prototype_ `static bool RemoveCommandFromCurrentPreset(const FString NewCommand);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Removes a command from the current preset if it exists in the saved data. The Asset will not be automatically saved. @return true if successful.
- L58 _public prototype_ `static bool GetListOfCommandsFromPreset(const UConsoleVariablesAsset* InAsset, TArray<FString>& OutCommandList);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Return an array of strings containing the command names for each command found in the given preset.
- L62 _public prototype_ `static bool SetConsoleVariableByName_Float(const FString InCommandName, const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor", meta=(DisplayName="Set Console Variable By Name (Float)"))` — Set a console variable value directly. Returns true if the console object exists.
- L66 _public prototype_ `static bool SetConsoleVariableByName_Bool(const FString InCommandName, const bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor", meta=(DisplayName="Set Console Variable By Name (Bool)"))` — Set a console variable value directly. Returns true if the console object exists.
- L70 _public prototype_ `static bool SetConsoleVariableByName_Int(const FString InCommandName, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor", meta=(DisplayName="Set Console Variable By Name (Int)"))` — Set a console variable value directly. Returns true if the console object exists.
- L74 _public prototype_ `static bool SetConsoleVariableByName_String(const FString InCommandName, const FString InValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor", meta=(DisplayName="Set Console Variable By Name (String)"))` — Set a console variable value directly. Returns true if the console object exists.
- L78 _public prototype_ `static bool GetConsoleVariableStringValue(const FString InCommandName, FString& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Get a console variable's string value directly. Returns true if the console object exists.
- L82 _public prototype_ `static bool GetConsoleVariableSourceByName(const FString InCommandName, FString& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Set a console variable value directly. Returns true if the console object exists.
- L86 _public prototype_ `static bool GetEnableMultiUserCVarSync();` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Return whether the Multi-user sync setting for the current instance of the editor is enabled.
- L90 _public prototype_ `static void SetEnableMultiUserCVarSync(bool bNewSetting);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Enable or disable the Multi-user sync setting for the current instance of the editor.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONSOLEVARIABLESEDITOR_API`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogConsoleVariablesEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogConsoleVariablesEditor, Log, All);`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorModule.h` (Public)


#### class `FConsoleVariablesEditorModule`  
`class FConsoleVariablesEditorModule : public IModuleInterface, public FGCObject`  
_L21-159_
- inherits: `IModuleInterface,FGCObject`
- L25 _public prototype_ `static FConsoleVariablesEditorModule& Get();`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void PreUnloadCallback() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `void SavePreset() const;`
- L34 _public prototype_ `void SaveSpecificPreset(const TObjectPtr<UConsoleVariablesAsset> Preset) const;`
- L35 _public prototype_ `void SavePresetAs() const;`
- L36 _public prototype_ `void SaveSpecificPresetAs(const TObjectPtr<UConsoleVariablesAsset> Preset) const;`
- L37 _public prototype_ `void OpenConsoleVariablesDialogWithPreset(const TObjectPtr<UConsoleVariablesAsset> Preset) const;`
- L38 _public prototype_ `void OpenConsoleVariablesDialogWithAssetSelected(const FAssetData& InAssetData, const EConsoleVariablesEditorPresetImportMode InImportMode = EConsoleVariablesEditorPresetImportMode::UseDefault) const;`
- L41 _public prototype_ `void QueryAndBeginTrackingConsoleVariables();` — Find all console variables and cache their startup values
- L43 _public prototype_ `void AddConsoleObjectCommandInfoToMainReference(TSharedRef<FConsoleVariablesEditorCommandInfo> InCommandInfo);`
- L46 _public prototype_ `TWeakPtr<FConsoleVariablesEditorCommandInfo> FindCommandInfoByName( const FString& NameToSearch, ESearchCase::Type InSearchCase = ESearchCase::IgnoreCase);` — Find a tracked console variable by the command string with optional case sensitivity.
- L54 _public prototype_ `TArray<TWeakPtr<FConsoleVariablesEditorCommandInfo>> FindCommandInfosMatchingTokens( const TArray<FString>& InTokens, ESearchCase::Type InSearchCase = ESearchCase::IgnoreCase);` — Find all tracked console variables matching a specific search query with optional case sensitivity. Individual members of InTokens will be considered "AnyOf" or "OR" searches. If SearchTerms contains any individual member it will match. Members will be tested for a space character (" "). If a space is found, a subsearch will be run. This subsearch will be an "AllOf" or "AND" type search in which all strings, separated by a space, must be found in the search terms.
- L57 _public prototype_ `[[nodiscard]] TObjectPtr<UConsoleVariablesAsset> GetPresetAsset() const;`
- L58 _public prototype_ `[[nodiscard]] TObjectPtr<UConsoleVariablesAsset> GetGlobalSearchAsset() const;`
- L60 _public prototype_ `FReply ValidateConsoleInputAndAddToCurrentPreset(const FText& CommittedText) const;`
- L65 _public prototype_ `void RebuildList(const FString InConsoleCommandToScrollTo = "", bool bShouldCacheValues = true) const;` — Regenerate the list items and refresh the list. Call when adding or removing variables. @param bShouldCacheValues If true, the current list's current values will be cached and then restored when the list is rebuilt. Otherwise preset values will be used.
- L71 _public prototype_ `void RefreshList() const;` — Refresh filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L73 _public prototype_ `void UpdatePresetValuesForSave(TObjectPtr<UConsoleVariablesAsset> InAsset);`
- L76 _public prototype_ `bool PopulateGlobalSearchAssetWithVariablesMatchingTokens(const TArray<FString>& InTokens);` — Fills Global Search Asset's Saved Commands with variables matching the specified query. Returns false if no matches were found.
- L78 _public prototype_ `void SendMultiUserConsoleVariableChange(ERemoteCVarChangeType InChangeType, const FString& InVariableName, const FString& InValueAsString, EConsoleVariableFlags InFlags);`
- L79 _public prototype_ `void OnRemoteCvarChanged(ERemoteCVarChangeType InChangeType, FString InName, FString InValue, EConsoleVariableFlags InFlags);`
- L81 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L82 _public prototype_ `virtual FString GetReferencerName() const override;`
- L84 _public prototype_ `void OnConsoleVariableChanged(FConsoleVariablesEditorCommandInfo& CommandInfo, IConsoleVariable* ChangedVariable);`
- L125 _private prototype_ `void OnFEngineLoopInitComplete();`
- L127 _private prototype_ `void RegisterMenuItem();`
- L128 _private prototype_ `void RegisterProjectSettings() const;`
- L129 _private prototype_ `void OnConsoleObjectUnregistered(const TCHAR* InName, IConsoleObject* InConsoleObject);`
- L131 _private prototype_ `TObjectPtr<UConsoleVariablesAsset> AllocateTransientPreset(const FName DesiredName) const;`
- L132 _private prototype_ `void CreateEditingPresets();`
- L134 _private prototype_ `TSharedRef<SDockTab> SpawnMainPanelTab(const FSpawnTabArgs& Args);`
- L136 _private prototype_ `static void OpenConsoleVariablesEditor();`
- L138 _private member_ `static const FName ConsoleVariablesToolkitPanelTabId;`
- L141 _private member_ `TSharedPtr<FConsoleVariablesEditorMainPanel> MainPanel;` — Lives for as long as the module is loaded.
- L144 _private member_ `TObjectPtr<UConsoleVariablesAsset> EditingPresetAsset = nullptr;` — Transient preset that's being edited so we don't affect the reference asset unless we save it
- L146 _private member_ `TObjectPtr<UConsoleVariablesAsset> EditingGlobalSearchAsset = nullptr;` — Transient preset that tracks variables that match the search criteria
- L149 _private member_ `TMap<FString, TSharedPtr<FConsoleVariablesEditorCommandInfo>> ConsoleObjectsMainReference;` — All tracked variables and their default, startup, and current values
- L156 _private member_ `TMap<FString, int32> CommandsReceivedFromMultiUser;` — A map of commands invoked by Multi-user.  Each command has a corresponding reference count. When this node receives a command from another node, it will be added to this list.  This is prevent a remote cvar change creating a ping/pong cvar updates effect between nodes.
- L158 _private member_ `FDelegateHandle OnConsoleObjectUnregisteredHandle;`

#### struct `FConsoleVariablesEditorModule::FScopeMultiUserReceiveCVar`  
`struct FScopeMultiUserReceiveCVar`  
_L88-123_
- desc: Scoped based struct to track inbound cvars set by Multi-user.
- L90 _public prototype_ `FScopeMultiUserReceiveCVar() = delete;`
- L91 _public prototype_ `FScopeMultiUserReceiveCVar(const FScopeMultiUserReceiveCVar&) = delete;`
- L92 _public prototype_ `FScopeMultiUserReceiveCVar& operator=(const FScopeMultiUserReceiveCVar&) = delete;`
- L94 _public function_ `FScopeMultiUserReceiveCVar(FString InCommand, TMap<FString, int32>& InTable) : TrackedCommand(MoveTemp(InCommand)), InboundCommandTable(InTable)`
- L109 _public function_ `~FScopeMultiUserReceiveCVar()`
- L121 _public member_ `FString TrackedCommand;`
- L122 _public member_ `TMap<FString, int32>& InboundCommandTable;`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorProjectSettings.h` (Public)


#### enum `EConsoleVariablesEditorRowDisplayType`  
`enum class EConsoleVariablesEditorRowDisplayType : uint8`  
_L8-12_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `ShowCurrentValue`
- L11 _public enumerator_ `ShowLastEnteredValue`

#### enum `EConsoleVariablesEditorPresetImportMode`  
`enum class EConsoleVariablesEditorPresetImportMode : uint8`  
_L15-33_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `AddToExisting` — Add the list of variables from the imported preset to the current preset, replacing the values of any overlapping variables with the values from the imported preset.
- L27 _public enumerator_ `ReplaceExisting` — Completely replace the list of variables in the current preset, resetting them to their default values and removing them from the list before importing the new preset's variable list.
- L32 _public enumerator_ `UseDefault UMETA(Hidden)` — Use the global import setting.

#### class `UConsoleVariablesEditorProjectSettings`  
`class UConsoleVariablesEditorProjectSettings : public UObject`  
_L36-78_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- L41 _public function_ `UConsoleVariablesEditorProjectSettings(const FObjectInitializer& ObjectInitializer)`
- L56 _public member_ `EConsoleVariablesEditorRowDisplayType UncheckedRowDisplayType;` — `UPROPERTY(Config, EditAnywhere, Category="Console Variables Editor")` — When a row is unchecked, its associated variable's value will be set to the value recorded when the plugin was loaded. The value displayed to the user can be configured with this setting, but will not affect the actual applied value. ShowCurrentValue displays the actual value currently applied to the variable. ShowLastEnteredValue displays the value that will be applied when the row is checked.
- L62 _public member_ `EConsoleVariablesEditorPresetImportMode PresetImportMode;` — `UPROPERTY(Config, EditAnywhere, Category = "Console Variables Editor")` — When importing a console variable preset, the variables
- L69 _public member_ `bool bAddAllChangedConsoleVariablesToCurrentPreset;` — `UPROPERTY(Config, EditAnywhere, Category="Console Variables Editor")` — When variables are changed outside the Console Variables Editor, this option will add the variables to the current preset. Does not apply to console commands like 'r.SetNearClipPlane' or 'stat fps'
- L77 _public member_ `TSet<FString> ChangedConsoleVariableSkipList;` — `UPROPERTY(Config, EditAnywhere, Category="Console Variables Editor")` — If bAddAllChangedConsoleVariablesToCurrentPreset is true, this list will filter out any matching variables changed outside of the Console Variables Editor so they won't be added to the current preset. Matching variables explicitly added inside the Console Variables Editor will not be filtered.

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/Views/Widgets/SConsoleVariablesEditorCustomConsoleInputBox.h` (Public)


#### class `SConsoleVariablesEditorCustomConsoleInputBox`  
`class SConsoleVariablesEditorCustomConsoleInputBox : public SCompoundWidget`  
_L13-156_
- inherits: `SCompoundWidget`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTextCommitted, const FText&);`
- L17 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTextChanged, const FText&);`
- L19 _public function_ `SLATE_BEGIN_ARGS(SConsoleVariablesEditorCustomConsoleInputBox) : _CommitOnFocusLost(false)`
- L103 _public prototype_ `void Construct(const FArguments& InArgs);`
- L108 _public prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;`
- L111 _public prototype_ `bool TakeKeyboardFocus() const;`
- L113 _public prototype_ `void OnInputTextChanged(const FText& InText);`
- L115 _public prototype_ `FReply OnKeyCharHandler(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) const;`
- L117 _public prototype_ `FReply OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& KeyPressed);`
- L119 _public prototype_ `void SetSuggestions(TArray<FString>& Elements, FText Highlight);`
- L121 _public prototype_ `void MarkActiveSuggestion();`
- L123 _public prototype_ `void ClearSuggestions();`
- L125 _public prototype_ `void CommitInput();`
- L128 _private prototype_ `FString GetSanitizedCommand(const FString& InCommand) const;`
- L133 _private member_ `TSharedPtr<SEditableTextBox> InputText;` — A reference to the actual text box inside ConsoleInput
- L136 _private member_ `TSharedPtr<SMenuAnchor> SuggestionBox;` — history / auto completion elements
- L139 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> SuggestionListView;` — The list view for showing all log messages. Should be replaced by a full text editor
- L142 _private member_ `FSuggestions Suggestions;` — Active list of suggestions
- L145 _private member_ `bool bIgnoreUIUpdate = false;` — to prevent recursive calls in UI callback
- L147 _private member_ `bool bHideOnFocusLost = true;`
- L148 _private member_ `bool bCommitOnFocusLost = false;`
- L149 _private member_ `bool bClearOnCommit = true;`
- L150 _private member_ `TAttribute<bool> IsEnabledAttribute;`
- L151 _private member_ `FSlateFontInfo Font;`
- L152 _private member_ `FText HintText;`
- L153 _private member_ `TAttribute<FText> TextAttribute;`
- L154 _private member_ `FOnTextCommitted OnTextCommitted;`
- L155 _private member_ `FOnTextChanged OnTextChanged;`

#### struct `SConsoleVariablesEditorCustomConsoleInputBox::FSuggestions`  
`struct FSuggestions`  
_L51-101_
- L53 _public function_ `FSuggestions() : SelectedSuggestion(INDEX_NONE)`
- L58 _public function_ `void Reset()`
- L65 _public function_ `bool HasSuggestions() const`
- L70 _public function_ `bool HasSelectedSuggestion() const`
- L75 _public function_ `void StepSelectedSuggestion(const int32 Step)`
- L88 _public function_ `TSharedPtr<FString> GetSelectedSuggestion() const`
- L94 _public member_ `int32 SelectedSuggestion;` — INDEX_NONE if not set, otherwise index into SuggestionsList
- L97 _public member_ `TArray<TSharedPtr<FString>> SuggestionsList;` — All log messages stored in this widget for the list view
- L100 _public member_ `FText SuggestionsHighlight;` — Highlight text to use for the suggestions list

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONSOLEVARIABLESEDITOR_API`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTextCommitted, const FText&);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTextChanged, const FText&);`
