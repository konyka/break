# Plugins / TedsAlerts

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts`
- headers: 5; symbols: 129
- symbol kinds: class=4, enum=1, enumerator=3, member=32, namespace=17, prototype=51, struct=12, typedef=9
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, ToolWidgets, TypedElementFramework
- PublicDependencyModuleNames: Projects

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts/Private/TedsAlertWidget.h` (Private)


#### class `UE::Editor::DataStorage::FAlertWidgetSorter`  
`class FAlertWidgetSorter final : public TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64, FAlertColumn>`  
_L16-22_
- inherits: `TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64,FAlertColumn>`
- L19 _public prototype_ `virtual FText GetShortName() const override;`
- L21 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FAlertColumn& Column, uint32 ByteIndex) const override;`

#### class `UAlertWidgetFactory`  
`class UAlertWidgetFactory final : public UEditorDataStorageFactory`  
_L26-40_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `~UAlertWidgetFactory() override = default;`
- L33 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L35 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L38 _private prototype_ `void RegisterAlertQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L39 _private prototype_ `void RegisterAlertHeaderQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`

#### struct `FAlertWidgetConstructor`  
`struct FAlertWidgetConstructor final : public FTypedElementWidgetConstructor`  
_L43-70_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L48 _public member_ `static constexpr int32 IconBackgroundSlot = 1;`
- L49 _public member_ `static constexpr int32 IconBadgeSlot = 2;`
- L50 _public member_ `static constexpr int32 CounterTextSlot = 3;`
- L51 _public member_ `static constexpr int32 ActionButtonSlot = 0;`
- L53 _public member_ `static constexpr float BadgeFontSize = 7.0f;`
- L54 _public member_ `static constexpr float BadgeHorizontalOffset = 13.0f;`
- L55 _public member_ `static constexpr float BadgeVerticalOffset = 1.0f;`
- L57 _public prototype_ `FAlertWidgetConstructor();`
- L58 _public prototype_ `~FAlertWidgetConstructor() override = default;`
- L61 _private prototype_ `TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L62 _private prototype_ `TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L63 _private prototype_ `bool FinalizeWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`
- L66 _private prototype_ `TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FAlertWidgetTag`  
`struct FAlertWidgetTag : public FEditorDataStorageTag`  
_L73-76_
- reflection: `USTRUCT(meta = (DisplayName = "General purpose alert"))`
- inherits: `FEditorDataStorageTag`

#### struct `FAlertHeaderWidgetConstructor`  
`struct FAlertHeaderWidgetConstructor final : public FTypedElementWidgetConstructor`  
_L79-93_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L84 _public prototype_ `FAlertHeaderWidgetConstructor();`
- L85 _public prototype_ `~FAlertHeaderWidgetConstructor() override = default;`
- L88 _protected prototype_ `TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L89 _protected prototype_ `TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L90 _protected prototype_ `bool FinalizeWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`

#### struct `FAlertHeaderWidgetTag`  
`struct FAlertHeaderWidgetTag : public FEditorDataStorageTag`  
_L96-99_
- reflection: `USTRUCT(meta = (DisplayName = "General purpose alert header"))`
- inherits: `FEditorDataStorageTag`

#### struct `FAlertHeaderActiveWidgetTag`  
`struct FAlertHeaderActiveWidgetTag : public FEditorDataStorageTag`  
_L102-105_
- reflection: `USTRUCT(meta = (DisplayName = "Alert header active"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts/Private/TedsAlertsFactory.h` (Private)


#### class `UTedsAlertsFactory`  
`class UTedsAlertsFactory final : public UEditorDataStorageFactory`  
_L18-100_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Factory that manages tables, queries and any other data for alerts.
- L23 _public member_ `static const FName AlertChainTableName;`
- L24 _public member_ `static const FName UnsortedAlertChainTableName;`
- L26 _public prototype_ `~UTedsAlertsFactory() override = default;`
- L28 _public prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L31 _public prototype_ `UE::Editor::DataStorage::TableHandle GetAlertChainTable() const;`
- L32 _public prototype_ `UE::Editor::DataStorage::TableHandle GetUnsortedAlertChainTable() const;`
- L34 _public prototype_ `UE::Editor::DataStorage::QueryHandle GetSortedAlertsQuery() const;`
- L35 _public prototype_ `UE::Editor::DataStorage::QueryHandle GetUnsortedAlertsQuery() const;`
- L39 _public prototype_ `void RegisterAlertHierarchy(UE::Editor::DataStorage::ICoreProvider& DataStorage, const FName& InHierarchyName);` — Register a new hierarchy as being part of alerts. This adds observers to track changes for this specific hierarchy so rows with alerts beloging to this hierarchy have can update their parent
- L53 _private member_ `TMap<FName, TUniquePtr<FAlertHierarchyConditions>> HierarchyConditions;`
- L57 _private member_ `TArray<FName> AllAlertPropagationStartConditionNames;` — All per-hierarchy AlertPropagationStartConditionNames, captured by non-hierarchy queries so they can activate every registered hierarchy when a global alert change occurs.
- L59 _private member_ `UE::Editor::DataStorage::TableHandle ChainTable = UE::Editor::DataStorage::InvalidTableHandle;`
- L60 _private member_ `UE::Editor::DataStorage::TableHandle UnsortedChainTable = UE::Editor::DataStorage::InvalidTableHandle;`
- L62 _private member_ `UE::Editor::DataStorage::QueryHandle SortedAlertsQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L63 _private member_ `UE::Editor::DataStorage::QueryHandle UnsortedAlertsQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L64 _private member_ `UE::Editor::DataStorage::QueryHandle AlertActionQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L65 _private member_ `UE::Editor::DataStorage::QueryHandle AlertHierarchyQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L66 _private member_ `UE::Editor::DataStorage::QueryHandle ChildAlertColumnReadWriteQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L68 _private prototype_ `void RegisterSubQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L69 _private prototype_ `void RegisterSortUnsortedAlertsQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L70 _private prototype_ `void RegisterOnRemoveQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L74 _private prototype_ `void RegisterOnAddHierarchyQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, const FName& InAlertPropagationStartConditionName);` — Hierarchy update queries, these currently have to be registered per hierarchy since a query can only access one hierarchy and it isn't possible to right a query that can dynamically pick which hierarchy to use.
- L75 _private prototype_ `void RegisterOnRemoveHierarchyQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, const FName& InAlertPropagationStartConditionName);`
- L76 _private prototype_ `void RegisterParentUpdatesHierarchyQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, const FName& InAlertPropagationStartConditionName);`
- L77 _private prototype_ `void RegisterChildAlertHierarchyUpdatesQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage, const FName& InHierarchyName, UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, FAlertHierarchyConditions* InConditions);`
- L79 _private prototype_ `static void AssignAlert( UE::Editor::DataStorage::ISubqueryContext& TargetContext, UE::Editor::DataStorage::RowHandle TargetRow, FTedsAlertColumn& Target, UE::Editor::DataStorage::IQueryContext& SourceContext, UE::Editor::DataStorage::RowHandle SourceRow, FTedsAlertColumn& Source, int32 AlertActionQueryIndex, int32 AlertHierarchyQueryIndex);`
- L83 _private prototype_ `static void SwapAlerts( UE::Editor::DataStorage::ISubqueryContext& OriginalContext, UE::Editor::DataStorage::RowHandle OriginalRow, FTedsAlertColumn& Original, UE::Editor::DataStorage::IQueryContext& NewContext, UE::Editor::DataStorage::RowHandle NewRow, FTedsAlertColumn& New, int32 AlertActionQueryIndex, int32 AlertHierarchyQueryIndex);`
- L87 _private prototype_ `static void AppendAlert( FTedsAlertColumn& LastAlert, UE::Editor::DataStorage::IQueryContext& AdditionalAlertContext, UE::Editor::DataStorage::RowHandle AdditionalAlertRow, FTedsAlertColumn& AdditionalAlert);`
- L92 _private prototype_ `static FTedsAlertActionColumn* GetAction(UE::Editor::DataStorage::IQueryContext& Context, UE::Editor::DataStorage::RowHandle Row, int32 ChildAlertQueryIndex);`
- L94 _private prototype_ `static FTedsAlertHierarchyColumn* GetHierarchy(UE::Editor::DataStorage::IQueryContext& Context, UE::Editor::DataStorage::RowHandle Row, int32 ChildAlertQueryIndex);`
- L97 _private prototype_ `static void AddChildAlertsToHierarchy( UE::Editor::DataStorage::IQueryContext& Context, UE::Editor::DataStorage::RowHandle Parent, UE::Editor::DataStorage::FHierarchyHandle HierarchyHandle);`
- L99 _private prototype_ `static void ResetChildAlertCounters(FTedsChildAlertColumn& ChildAlert);`

#### struct `UTedsAlertsFactory::FAlertHierarchyConditions`  
`struct FAlertHierarchyConditions`  
_L44-52_
- desc: Per-hierarchy condition names and propagation counter. Stored as a unique_ptr so the address of PendingPropagations is stable after the map grows.
- L46 _public member_ `FName AlertPropagationStartConditionName;`
- L47 _public member_ `FName AlertPropagationConditionName;`
- L48 _public member_ `FName AlertPropagationFinishedConditionName;`
- L51 _public member_ `std::atomic<int32> PendingPropagations{0};` — Counts how many nodes still need to propagate their alert counts to their parent. Decremented by "Propagate child alerts"; when it hits 0 propagation is complete for this wave.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts/Private/TedsAlertsModule.h` (Private)


#### class `UE::Editor::DataStorage::FTedsAlertsModule`  
`class FTedsAlertsModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L14 _public prototype_ `FTedsAlertsModule() = default;`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts/Public/TedsAlertColumns.h` (Public)


#### enum `FTedsAlertColumnType`  
`enum class FTedsAlertColumnType : uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `Warning`
- L16 _public enumerator_ `Error`
- L18 _public enumerator_ `MAX`

#### struct `FTedsAlertColumn`  
`struct FTedsAlertColumn final : public FEditorDataStorageColumn`  
_L27-54_
- reflection: `USTRUCT(meta = (DisplayName = "Alert"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing information a user needs to be alerted of.
- L32 _public member_ `FText Message;` — `UPROPERTY()`
- L38 _public member_ `UE::Editor::DataStorage::RowHandle NextAlert;` — If valid, points to the next alert in the chain.The next alert will take the place of the current alert if this alert is cleared.
- L42 _public member_ `FName Name;` — `UPROPERTY()` — Unique name to identify the message with.
- L46 _public member_ `FTedsAlertColumnType AlertType;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — The type of alert. This is used for ordering and to show appropriate icons.
- L53 _public member_ `uint8 Priority;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — A chain of priorities is sorted by errors, then warnings. If either group has multiple alerts, alerts are sorted by priority with the lowest value (0) given the later location and higher value (up to 255) the earlier locations in the chain.

#### struct `FTedsChildAlertColumn`  
`struct FTedsChildAlertColumn final : public FEditorDataStorageColumn`  
_L60-71_
- reflection: `USTRUCT(meta = (DisplayName = "Child alert"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing a count for the number of alerts any child rows have.
- L64 _public member_ `uint16 Counts[static_cast<size_t>(FTedsAlertColumnType::MAX)];`
- L67 _public member_ `uint16 ProcessedChildCount = 0;` — How many direct contributing children (leaf alerts or intermediate nodes) have propagated to this row.
- L70 _public member_ `uint16 NumAlertChildren = 0;` — Expected number of direct contributing children. Set at reset time by the "Count alert children" processor.

#### struct `FTedsAlertHierarchyColumn`  
`struct FTedsAlertHierarchyColumn final : public FEditorDataStorageColumn`  
_L77-82_
- reflection: `USTRUCT(meta = (DisplayName = "Alert Hierarchy Column"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that holds info about the hierarchy an alert is participating in
- L81 _public member_ `UE::Editor::DataStorage::FHierarchyHandle HierarchyHandle;`

#### struct `FTedsAlertActionColumn`  
`struct FTedsAlertActionColumn final : public FEditorDataStorageColumn`  
_L88-93_
- reflection: `USTRUCT(meta = (DisplayName = "Alert action"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be added to an alert column to have it trigger an action when the alert is clicked.
- L92 _public member_ `FTedsAlertActionCallback Action;`

#### struct `FTedsAlertChainTag`  
`struct FTedsAlertChainTag final : public FEditorDataStorageTag`  
_L99-102_
- reflection: `USTRUCT(meta = (DisplayName = "Alert chain"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate this row contains alert chain information.

#### struct `FTedsUnsortedAlertChainTag`  
`struct FTedsUnsortedAlertChainTag final : public FEditorDataStorageTag`  
_L109-112_
- reflection: `USTRUCT(meta = (DisplayName = "Unsorted alert chain"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate this row contains alert chain information that has not been added/sorted yet. This means that the "NextAlert" in the Alert column points to the target row, not the row for the next alert.

#### Free symbols / members of external scopes

- L21 _typedef_ `using FTedsAlertActionCallback = TFunction<void(UE::Editor::DataStorage::RowHandle)>;`
- L114 _namespace_ `namespace UE`
- L114 _namespace_ `namespace Editor` (scope `UE`)
- L114 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L114 _namespace_ `namespace Columns` (scope `UE::Editor::DataStorage`)
- L116 _typedef_ `using FAlertColumnType = FTedsAlertColumnType;` (scope `UE::Editor::DataStorage::Columns`)
- L117 _typedef_ `using FAlertActionCallback = FTedsAlertActionCallback;` (scope `UE::Editor::DataStorage::Columns`)
- L119 _typedef_ `using FAlertColumn = FTedsAlertColumn;` (scope `UE::Editor::DataStorage::Columns`)
- L120 _typedef_ `using FChildAlertColumn = FTedsChildAlertColumn;` (scope `UE::Editor::DataStorage::Columns`)
- L121 _typedef_ `using FAlertHierarchyColumn = FTedsAlertHierarchyColumn;` (scope `UE::Editor::DataStorage::Columns`)
- L122 _typedef_ `using FAlertActionColumn = FTedsAlertActionColumn;` (scope `UE::Editor::DataStorage::Columns`)
- L123 _typedef_ `using FAlertChainTag = FTedsAlertChainTag;` (scope `UE::Editor::DataStorage::Columns`)
- L124 _typedef_ `using FUnsortedAlertChainTag = FTedsUnsortedAlertChainTag;` (scope `UE::Editor::DataStorage::Columns`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAlerts/Public/TedsAlerts.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace Alerts` (scope `UE::Editor::DataStorage`)
- L34 _prototype_ `void AddAlert(ICoreProvider& DataStorage, RowHandle TargetRow, const FName& Name, FText Message, Columns::FAlertColumnType Type, uint8 Priority = 127, Columns::FAlertActionCallback Action = {}, const FName& HierarchyName = NAME_None);` (scope `UE::Editor::DataStorage::Alerts`) — Add an alert to the provided row. Various tools like the Outliner monitor for alerts and can show them for instance as a colored triangle with a exclamation count. If a row also has a parent row handle, the alerts will propagate their count to the parent. @DataStorage A reference to the data storage instance to store the alert in. @TargetRow The target row to store the alert on. If the row already has an alert, an ordered chain of alerts will be created. @Name A name to uniquely identify the alert. If there's a chain of alerts this is used to find the correct alert to remove. @Message The message shown in the alert, e.g. as a tool tip on the alert icon. @Type The type of alerts. Widgets will use separate child counts per type and use different colors such as red for errors and yellow for warnings. @Priority If there are multiple alerts for the same type, the priority is used to order the alerts so the most important one is shown when the active alert is removed. Higher values indicate higher priority. @Action An optional callback that gets triggered when the user presses the alert icon. @HierarchyName Optional hierarchy name to use when resolving parent alerts. The alert queries will walk up the parent chain in the provided hierarchy to add the child alert column
- L52 _prototype_ `void AddAlert(IQueryContext& Context, RowHandle TargetRow, const FName& Name, FText Message, Columns::FAlertColumnType Type, uint8 Priority = 127, Columns::FAlertActionCallback Action = {}, const FName& HierarchyName = NAME_None);` (scope `UE::Editor::DataStorage::Alerts`) — Add an alert to the provided row. Various tools like the Outliner monitor for alerts and can show them for instance as a colored triangle with a exclamation count. If a row also has a parent row handle, the alerts will propagate their count to the parent. @Context A reference to the query callback context. @TargetRow The target row to store the alert on. If the row already has an alert, an ordered chain of alerts will be created. @Name A name to uniquely identify the alert. If there's a chain of alerts this is used to find the correct alert to remove. @Message The message shown in the alert, e.g. as a tool tip on the alert icon. @Type The type of alerts. Widgets will use separate child counts per type and use different colors such as red for errors and yellow for warnings. @Priority If there are multiple alerts for the same type, the priority is used to order the alerts so the most important one is shown when the active alert is removed. Higher values indicate higher priority. @Action An optional callback that gets triggered when the user presses the alert icon. @HierarchyName Optional hierarchy name to use when resolving parent alerts. The alert queries will walk up the parent chain in the provided hierarchy to add the child alert column
- L62 _prototype_ `void UpdateAlertText(ICoreProvider& DataStorage, RowHandle TargetRow, const FName& Name, FText Message);` (scope `UE::Editor::DataStorage::Alerts`) — Locates the first alerts with the provided name in the alert chain found at the provided row and updates its text. @DataStorage A reference to the data storage instance to store the alert in. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert. @Message The new message for the alert.
- L70 _prototype_ `void UpdateAlertText(IQueryContext& Context, RowHandle TargetRow, const FName& Name, FText Message);` (scope `UE::Editor::DataStorage::Alerts`) — Locates the first alerts with the provided name in the alert chain found at the provided row and updates its text. @Context A reference to the query callback context. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert. @Message The new message for the alert.
- L80 _prototype_ `void UpdateAlertAction( ICoreProvider& DataStorage, RowHandle TargetRow, const FName& Name, Columns::FAlertActionCallback Action);` (scope `UE::Editor::DataStorage::Alerts`) — Locates the first alerts with the provided name in the alert chain found at the provided row and updates its action. If there's no action it will be added. If the provided action isn't bound, the alert action will be removed. @DataStorage A reference to the data storage instance to store the alert in. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert. @Action The new action to trigger.
- L90 _prototype_ `void UpdateAlertAction(IQueryContext& Context, RowHandle TargetRow, const FName& Name, Columns::FAlertActionCallback Action);` (scope `UE::Editor::DataStorage::Alerts`) — Locates the first alerts with the provided name in the alert chain found at the provided row and updates its action. If there's no action it will be added. If the provided action isn't bound, the alert action will be removed. @Context A reference to the query callback context. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert. @Action The new action to trigger.
- L100 _prototype_ `void RemoveAlert(ICoreProvider& DataStorage, RowHandle TargetRow, const FName& Name);` (scope `UE::Editor::DataStorage::Alerts`) — Searches the alert chain found at the target row for the first alert with the provided name and removes it. The chain will automatically be patched, keeping the chain in order of priority. If the root alert is removed, the UI will be automatically updated with the next alert in line or be cleared if there are no more alerts. @DataStorage A reference to the data storage instance to store the alert in. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert.
- L109 _prototype_ `void RemoveAlert(IQueryContext& Context, RowHandle TargetRow, const FName& Name);` (scope `UE::Editor::DataStorage::Alerts`) — Searches the alert chain found at the target row for the first alert with the provided name and removes it. The chain will automatically be patched, keeping the chain in order of priority. If the root alert is removed, the UI will be automatically updated with the next alert in line or be cleared if there are no more alerts. @Context A reference to the query callback context. @TargetRow The row the alert is stored on. @Name The name that uniquely identifies the alert.
