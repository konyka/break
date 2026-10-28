# Plugins / CrashDiagnostics

- module root: `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics`
- headers: 7; symbols: 153
- symbol kinds: class=5, enum=1, enumerator=4, function=20, macro=2, member=24, namespace=19, prototype=50, struct=24, variable=4
- PrivateDependencyModuleNames: CoreUObject, CrashReportCore, InputCore, Slate, SlateCore, TedsQueryStack, TedsTableViewer, ToolMenus, ToolWidgets, UnrealEd, XmlParser
- PublicDependencyModuleNames: Core, TypedElementFramework

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/CrashDiagnosticsSettings.h` (Private)


#### class `UCrashDiagnosticsSettings`  
`class UCrashDiagnosticsSettings : public UObject`  
_L10-21_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L20 _public member_ `FDateTime LastSessionStartTime = FDateTime();` — `UPROPERTY(config)` — The start time of the last editor session. Used to detect crashes that occurred during the previous session.

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/SEditorCrashesPanel.h` (Private)


#### class `UE::Editor::CrashDiagnostics::SEditorCrashesPanel`  
`class SEditorCrashesPanel : public SCompoundWidget`  
_L25-53_
- inherits: `SCompoundWidget`
- L27 _private member_ `static const FName SettingsMenuName;`
- L30 _public function_ `SLATE_BEGIN_ARGS(SEditorCrashesPanel)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _private prototype_ `TSharedRef<SWidget> CreateTableWidget();`
- L37 _private prototype_ `TSharedRef<SWidget> CreateDetailsWidget();`
- L38 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenuWidget();`
- L40 _private prototype_ `void OnSelectionChanged(UE::Editor::DataStorage::RowHandle RowHandle, ESelectInfo::Type SelectionType);`
- L42 _private prototype_ `UToolMenu* RegisterSettingsMenu();`
- L45 _private member_ `TSharedPtr<UE::Editor::DataStorage::QueryStack::IRowNode> SearchNode;`
- L47 _private member_ `TSharedPtr<UE::Editor::DataStorage::STedsSearchBox> SearchBox;`
- L48 _private member_ `TSharedPtr<UE::Editor::DataStorage::SRowDetails> CrashRowDetails;`
- L50 _private member_ `UE::Editor::DataStorage::RowHandle SelectedRowHandle = UE::Editor::DataStorage::InvalidRowHandle;`
- L51 _private member_ `float MarkAsReadDelaySeconds = 1.0f;`
- L52 _private member_ `TSharedPtr<FActiveTimerHandle> NewCrashTimer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L21 _macro_ `#define UE_API CRASHDIAGNOSTICS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace CrashDiagnostics` (scope `UE::Editor`)

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/SFileHyperlink.h` (Private)


#### class `UE::Editor::CrashDiagnostics::SFileHyperlink`  
`class SFileHyperlink : public SCompoundWidget`  
_L9-38_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SFileHyperlink)`
- L22 _public function_ `SLATE_ATTRIBUTE(FText, TextOverride) SLATE_ARGUMENT_DEFAULT(EOpenAction, OpenAction)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FString& InPath);`
- L29 _private prototype_ `EOpenAction GetAction() const;`
- L31 _private prototype_ `void Open() const;`
- L33 _private prototype_ `FText GetToolTipText() const;`
- L36 _private member_ `FString FullPath;`
- L37 _private member_ `EOpenAction OpenAction = EOpenAction::Auto;`

#### enum `UE::Editor::CrashDiagnostics::SFileHyperlink::EOpenAction`  
`enum class EOpenAction : uint8`  
_L12-18_
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `OpenFileApplication`
- L16 _public enumerator_ `OpenFolder`
- L17 _public enumerator_ `Auto`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace CrashDiagnostics` (scope `UE::Editor`)

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/TedsCrashColumnWidgets.h` (Private)


#### struct `FEditorCrashGUIDWidgetConstructor`  
`struct FEditorCrashGUIDWidgetConstructor : public FSimpleWidgetConstructor`  
_L16-32_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L21 _public function_ `FEditorCrashGUIDWidgetConstructor() : Super(StaticStruct())`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashTimeWidgetConstructor`  
`struct FEditorCrashTimeWidgetConstructor : public FSimpleWidgetConstructor`  
_L36-57_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L41 _public function_ `FEditorCrashTimeWidgetConstructor() : Super(StaticStruct())`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L53 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashTimeTableRowWidgetConstructor`  
`struct FEditorCrashTimeTableRowWidgetConstructor : public FSimpleWidgetConstructor`  
_L60-81_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L65 _public function_ `FEditorCrashTimeTableRowWidgetConstructor() : Super(StaticStruct())`
- L70 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L77 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashErrorMessageWidgetConstructor`  
`struct FEditorCrashErrorMessageWidgetConstructor : public FSimpleWidgetConstructor`  
_L85-101_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L90 _public function_ `FEditorCrashErrorMessageWidgetConstructor() : Super(StaticStruct())`
- L95 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashErrorMessageCompactWidgetConstructor`  
`struct FEditorCrashErrorMessageCompactWidgetConstructor : public FSimpleWidgetConstructor`  
_L104-120_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L109 _public function_ `FEditorCrashErrorMessageCompactWidgetConstructor() : Super(StaticStruct())`
- L114 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashTypeWidgetConstructor`  
`struct FEditorCrashTypeWidgetConstructor : public FSimpleWidgetConstructor`  
_L124-140_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L129 _public function_ `FEditorCrashTypeWidgetConstructor() : Super(StaticStruct())`
- L134 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashFileReportsWidgetConstructor`  
`struct FEditorCrashFileReportsWidgetConstructor : public FSimpleWidgetConstructor`  
_L144-160_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L149 _public function_ `FEditorCrashFileReportsWidgetConstructor() : Super(StaticStruct())`
- L154 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashCallStackWidgetConstructor`  
`struct FEditorCrashCallStackWidgetConstructor : public FSimpleWidgetConstructor`  
_L164-180_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L169 _public function_ `FEditorCrashCallStackWidgetConstructor() : Super(StaticStruct())`
- L174 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashSourceContextWidgetConstructor`  
`struct FEditorCrashSourceContextWidgetConstructor : public FSimpleWidgetConstructor`  
_L184-200_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L189 _public function_ `FEditorCrashSourceContextWidgetConstructor() : Super(StaticStruct())`
- L194 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashUserActivityHintWidgetConstructor`  
`struct FEditorCrashUserActivityHintWidgetConstructor : public FSimpleWidgetConstructor`  
_L204-220_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L209 _public function_ `FEditorCrashUserActivityHintWidgetConstructor() : Super(StaticStruct())`
- L214 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FEditorCrashTimeHeaderWidgetConstructor`  
`struct FEditorCrashTimeHeaderWidgetConstructor final : public FTypedElementWidgetConstructor`  
_L228-245_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L233 _public function_ `FEditorCrashTimeHeaderWidgetConstructor() : Super(StaticStruct())`
- L239 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L240 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`

#### struct `FEditorCrashTypeHeaderWidgetConstructor`  
`struct FEditorCrashTypeHeaderWidgetConstructor final : public FTypedElementWidgetConstructor`  
_L249-266_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L254 _public function_ `FEditorCrashTypeHeaderWidgetConstructor() : Super(StaticStruct())`
- L260 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L261 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/TedsEditorCrashDataStorageFactory.h` (Private)


#### class `UTedsEditorCrashDataStorageFactory`  
`class UTedsEditorCrashDataStorageFactory : public UEditorDataStorageFactory`  
_L13-45_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UTedsEditorCrashDataStorageFactory() override = default;`
- L20 _public prototype_ `static const UE::Editor::DataStorage::IUiProvider::FPurposeInfo& GetTableRowPurpose();`
- L21 _public prototype_ `static UE::Editor::DataStorage::IUiProvider::FPurposeID GetGeneralPurposeID();`
- L22 _public prototype_ `static UE::Editor::DataStorage::IUiProvider::FPurposeID GetTableRowPurposeID();`
- L23 _public prototype_ `static UE::Editor::DataStorage::IUiProvider::FPurposeID GetHeaderRowPurposeID();`
- L25 _public prototype_ `static FEditableTextBoxStyle* GetReadOnlyTextBoxStyle();`
- L27 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L28 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L30 _public prototype_ `virtual void RegisterWidgetConstructors( UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L34 _public function_ `UE::Editor::DataStorage::QueryHandle GetHasCrashedLastSessionQueryHandle() const`
- L38 _public function_ `UE::Editor::DataStorage::QueryHandle GetHasUnreadCrashesQueryHandle() const`
- L43 _private member_ `UE::Editor::DataStorage::QueryHandle HasCrashedLastSessionQueryHandle = UE::Editor::DataStorage::InvalidQueryHandle;`
- L44 _private member_ `UE::Editor::DataStorage::QueryHandle HasUnreadCrashesQueryHandle = UE::Editor::DataStorage::InvalidQueryHandle;`

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Public/Columns/TedsCrashColumns.h` (Public)


#### struct `FEditorCrashFileReportsColumn`  
`struct FEditorCrashFileReportsColumn : public FEditorDataStorageColumn`  
_L20-37_
- reflection: `USTRUCT(DisplayName="File Reports")`
- inherits: `FEditorDataStorageColumn`
- L25 _public member_ `FString XmlFilePath;` — `UPROPERTY(meta = (Searchable))`
- L28 _public member_ `FString LogFilePath;` — `UPROPERTY(meta = (Searchable))`
- L31 _public member_ `TArray<FString> ReportFilePaths;` — `UPROPERTY()`
- L33 _public function_ `FString GetCrashReportFolder() const`

#### struct `FEditorCrashTimeColumn`  
`struct FEditorCrashTimeColumn : public FEditorDataStorageColumn`  
_L40-49_
- reflection: `USTRUCT(DisplayName="Time of Crash")`
- inherits: `FEditorDataStorageColumn`
- L45 _public member_ `FDateTime TimeOfCrash;` — `UPROPERTY()`
- L48 _public member_ `FText TimeOfCrashString;` — `UPROPERTY(meta = (Searchable))`

#### struct `FEditorCrashGUIDColumn`  
`struct FEditorCrashGUIDColumn : public FEditorDataStorageColumn`  
_L52-58_
- reflection: `USTRUCT(DisplayName="Crash ID")`
- inherits: `FEditorDataStorageColumn`
- L57 _public member_ `FString CrashGUID;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FEditorCrashErrorMessageColumn`  
`struct FEditorCrashErrorMessageColumn : public FEditorDataStorageColumn`  
_L61-67_
- reflection: `USTRUCT(DisplayName="Error Message")`
- inherits: `FEditorDataStorageColumn`
- L66 _public member_ `FString ErrorMessage;` — `UPROPERTY(meta = (Searchable))`

#### struct `FEditorCrashCallStackColumn`  
`struct FEditorCrashCallStackColumn : public FEditorDataStorageColumn`  
_L70-76_
- reflection: `USTRUCT(DisplayName="Call Stack")`
- inherits: `FEditorDataStorageColumn`
- L75 _public member_ `FString CallStack;` — `UPROPERTY(meta = (Searchable))`

#### struct `FEditorCrashSourceContextColumn`  
`struct FEditorCrashSourceContextColumn : public FEditorDataStorageColumn`  
_L79-85_
- reflection: `USTRUCT(DisplayName="Source Context")`
- inherits: `FEditorDataStorageColumn`
- L84 _public member_ `FString SourceContext;` — `UPROPERTY(meta = (Searchable))`

#### struct `FEditorCrashTypeColumn`  
`struct FEditorCrashTypeColumn : public FEditorDataStorageColumn`  
_L88-94_
- reflection: `USTRUCT(DisplayName="Crash Type")`
- inherits: `FEditorDataStorageColumn`
- L93 _public member_ `FString CrashType;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FEditorCrashUserActivityHintColumn`  
`struct FEditorCrashUserActivityHintColumn : public FEditorDataStorageColumn`  
_L97-103_
- reflection: `USTRUCT(DisplayName="User Activity")`
- inherits: `FEditorDataStorageColumn`
- L102 _public member_ `FString UserActivityHint;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FEditorCrashIsEnsureTag`  
`struct FEditorCrashIsEnsureTag : public FEditorDataStorageTag`  
_L106-109_
- reflection: `USTRUCT(DisplayName="Is Ensure")`
- inherits: `FEditorDataStorageTag`

#### struct `FEditorCrashIsOOMTag`  
`struct FEditorCrashIsOOMTag : public FEditorDataStorageTag`  
_L112-115_
- reflection: `USTRUCT(DisplayName="Is Out Of Memory")`
- inherits: `FEditorDataStorageTag`

#### struct `FEditorCrashIsNewTag`  
`struct FEditorCrashIsNewTag : public FEditorDataStorageTag`  
_L118-121_
- reflection: `USTRUCT(DisplayName="Is New Crash")`
- inherits: `FEditorDataStorageTag`

#### struct `FEditorCrashLastSessionTag`  
`struct FEditorCrashLastSessionTag : public FEditorDataStorageTag`  
_L124-127_
- reflection: `USTRUCT(DisplayName="Crashed Last Session")`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace CrashDiagnostics` (scope `UE::Editor`)
- L13 _variable_ `inline static const FName MappingDomain = "Cr` (scope `UE::Editor::CrashDiagnostics`)
- L14 _variable_ `inline static const FName DataTableName = "Cr` (scope `UE::Editor::CrashDiagnostics`)
- L15 _variable_ `inline static const FName GlobalTableName = "Cr` (scope `UE::Editor::CrashDiagnostics`)
- L16 _variable_ `inline static const FName LastSessionCrashStateRowKey = "Cr` (scope `UE::Editor::CrashDiagnostics`)

### `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Public/CrashDiagnosticsModule.h` (Public)


#### class `UE::Editor::CrashDiagnostics::FCrashDiagnosticsModule`  
`class FCrashDiagnosticsModule : public IModuleInterface`  
_L21-71_
- inherits: `IModuleInterface`
- L24 _public function_ `static FCrashDiagnosticsModule& GetChecked()`
- L28 _public function_ `static FCrashDiagnosticsModule* Get()`
- L33 _public prototype_ `virtual void StartupModule() override;`
- L34 _public prototype_ `virtual void ShutdownModule() override;`
- L39 _public prototype_ `static TArray<TSharedRef<FPrimaryCrashProperties>> RetrieveSavedCrashes();` — Retrieve the crash data from the Saved directory
- L44 _public prototype_ `void AddCrashesToDataStorage(UE::Editor::DataStorage::ICoreProvider& DataStorage);` — Add the crashes to the given DataStorage. See TedsCrashColumns.h
- L45 _public prototype_ `void AddCrashesToDataStorage(UE::Editor::DataStorage::ICoreProvider& DataStorage, const TArray<TSharedRef<FPrimaryCrashProperties>>& Crashes);`
- L51 _public prototype_ `void AddCrashesToDataStorageAsync();` — Add the crashes asynchronously to the default DataStorage. This function will call RetrieveSavedCrashes on a background thread before calling AddCrashesToDataStorage on the GT.
- L53 _public prototype_ `void LoadCrashDiagnosticsSettings();`
- L54 _public prototype_ `void SaveCrashDiagnosticsSettings();`
- L56 _public prototype_ `bool HasCrashedLastSession() const;`
- L57 _public prototype_ `bool HasUnreadCrashes() const;`
- L59 _public prototype_ `TSharedRef<SWidget> CreateCrashLogPanel();`
- L64 _public prototype_ `static TSharedRef<SWidget> DecorateButtonWithUnreadBadge(TSharedRef<SWidget> InWidget);` — Function used for a GetDecoratedButtonDelegate that will add a badge to the first found SLayeredImage. This badge will only show if there are unread crashes.
- L65 _public prototype_ `const FSlateBrush* GetUnreadBadgeIcon() const;`
- L68 _private prototype_ `void OnEditorInitialized(double TimeToInitializeEditor);`
- L70 _private member_ `FDateTime PreviousSessionStartTime = FDateTime();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CRASHDIAGNOSTICS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace CrashDiagnostics` (scope `UE::Editor`)
