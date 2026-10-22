# Plugins / TedsSettings

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings`
- headers: 6; symbols: 82
- symbol kinds: class=3, delegate=2, function=1, macro=1, member=14, namespace=4, prototype=44, struct=11, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, Settings, SettingsEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: EditorSubsystem, TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Private/TedsSettingsFactory.h` (Private)


#### class `UTedsSettingsFactory`  
`class UTedsSettingsFactory : public UEditorDataStorageFactory`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `~UTedsSettingsFactory() override = default;`
- L19 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Private/TedsSettingsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTedsSettings, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTedsSettings, Log, All);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Private/TedsSettingsManager.h` (Private)


#### class `FTedsSettingsManager`  
`class FTedsSettingsManager final : public TSharedFromThis<FTedsSettingsManager>`  
_L12-64_
- inherits: `TSharedFromThis<FTedsSettingsManager>`
- L16 _public prototype_ `FTedsSettingsManager();`
- L18 _public function_ `const bool IsInitialized() const`
- L23 _public prototype_ `void Initialize();`
- L24 _public prototype_ `void Shutdown();`
- L26 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsContainer(const FName& ContainerName) const;`
- L28 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsCategory(const FName& ContainerName, const FName& CategoryName) const;`
- L30 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsSection(const FName& ContainerName, const FName& CategoryName, const FName& SectionName) const;`
- L32 _public prototype_ `bool GetSettingsSectionFromRow(UE::Editor::DataStorage::RowHandle Row, FName& OutContainerName, FName& OutCategoryName, FName& OutSectionName);`
- L34 _public prototype_ `bool GetSettingsCategoryFromRow(UE::Editor::DataStorage::RowHandle Row, FName& OutContainerName, FName& OutCategoryName);`
- L38 _private prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L39 _private prototype_ `void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L41 _private prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L42 _private prototype_ `void UnregisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L44 _private prototype_ `void AddSettings();`
- L45 _private prototype_ `void RemoveSettings();`
- L47 _private prototype_ `void AddSettingsContainer(const FName& ContainerName);`
- L49 _private prototype_ `void UpdateSettingsCategory(TSharedPtr<ISettingsCategory> SettingsCategory, UE::Editor::DataStorage::RowHandle ContainerRow, const bool bQueryExistingRows = true);`
- L51 _private prototype_ `void OnModulesChanged(FName ModuleName, EModuleChangeReason ChangeReason);`
- L53 _private prototype_ `void RegisterSettings(ISettingsModule& SettingsModule, UDeveloperSettings* Settings);`
- L54 _private prototype_ `void RegisterSettingsForModule(FName ModuleName);`
- L55 _private prototype_ `void UnregisterSettingsForModule(FName ModuleName);`
- L57 _private member_ `bool bIsInitialized;`
- L58 _private member_ `UE::Editor::DataStorage::QueryHandle SelectAllSettingsQuery;`
- L59 _private member_ `UE::Editor::DataStorage::TableHandle SettingsContainerTable;`
- L60 _private member_ `UE::Editor::DataStorage::TableHandle SettingsCategoryTable;`
- L61 _private member_ `UE::Editor::DataStorage::TableHandle SettingsPropertyTable;`
- L62 _private member_ `UE::Editor::DataStorage::FHierarchyHandle SettingsHierarchy;`
- L63 _private member_ `TMap<FName, UE::Editor::DataStorage::QueryHandle> SelectAllSettingsInModuleQueryMap;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Private/TedsSettingsWidgets.h` (Private)


#### struct `FSettingsContainerReferenceWidgetConstructor`  
`struct FSettingsContainerReferenceWidgetConstructor : public FSimpleWidgetConstructor`  
_L11-31_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L17 _public prototype_ `FSettingsContainerReferenceWidgetConstructor();`
- L18 _public prototype_ `~FSettingsContainerReferenceWidgetConstructor() override = default;`
- L20 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L27 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### struct `FSettingsCategoryReferenceWidgetConstructor`  
`struct FSettingsCategoryReferenceWidgetConstructor : public FSimpleWidgetConstructor`  
_L34-54_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L40 _public prototype_ `FSettingsCategoryReferenceWidgetConstructor();`
- L41 _public prototype_ `~FSettingsCategoryReferenceWidgetConstructor() override = default;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L50 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### struct `FSettingsSectionWidgetConstructor`  
`struct FSettingsSectionWidgetConstructor : public FSimpleWidgetConstructor`  
_L57-73_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L63 _public prototype_ `FSettingsSectionWidgetConstructor();`
- L64 _public prototype_ `~FSettingsSectionWidgetConstructor() override = default;`
- L66 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Public/TedsSettingsColumns.h` (Public)


#### struct `FSettingsContainerReferenceColumn`  
`struct FSettingsContainerReferenceColumn final : public FEditorDataStorageColumn`  
_L17-26_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Container Reference"))`
- inherits: `FEditorDataStorageColumn`
- L23 _public member_ `FName ContainerName;` — `UPROPERTY(meta = (Searchable, Sortable))` — Store the name as it is frequently accessed to avoid indirection to the row.
- L25 _public member_ `UE::Editor::DataStorage::RowHandle ContainerRow;`

#### struct `FSettingsCategoryReferenceColumn`  
`struct FSettingsCategoryReferenceColumn final : public FEditorDataStorageColumn`  
_L29-38_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Category Reference"))`
- inherits: `FEditorDataStorageColumn`
- L35 _public member_ `FName CategoryName;` — `UPROPERTY(meta = (Searchable, Sortable))` — Store the name as it is frequently accessed to avoid indirection to the row.
- L37 _public member_ `UE::Editor::DataStorage::RowHandle CategoryRow;`

#### struct `FSettingsNameColumn`  
`struct FSettingsNameColumn final : public FEditorDataStorageColumn`  
_L43-49_
- reflection: `USTRUCT(meta = (DisplayName = "Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: A generic name column for use within the settings domain. This is added to all container, category, and section rows.
- L48 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FSettingsModuleTag`  
`struct FSettingsModuleTag final : public FEditorDataStorageTag`  
_L53-56_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Module", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: A column whose dynamic identifier specifies the module that contains the class of this row's settings section object.

#### struct `FSettingsContainerTag`  
`struct FSettingsContainerTag final : public FEditorDataStorageTag`  
_L59-62_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Container"))`
- inherits: `FEditorDataStorageTag`

#### struct `FSettingsCategoryTag`  
`struct FSettingsCategoryTag final : public FEditorDataStorageTag`  
_L65-68_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Category"))`
- inherits: `FEditorDataStorageTag`

#### struct `FSettingsSectionTag`  
`struct FSettingsSectionTag final : public FEditorDataStorageTag`  
_L71-74_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Section"))`
- inherits: `FEditorDataStorageTag`

#### struct `FSettingsPropertyTag`  
`struct FSettingsPropertyTag final : public FEditorDataStorageTag`  
_L77-80_
- reflection: `USTRUCT(meta = (DisplayName = "Settings Property"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace Settings` (scope `UE::Editor::DataStorage`)
- L12 _variable_ `inline static const FName MappingDomain = "Se` (scope `UE::Editor::DataStorage::Settings`)
- L13 _variable_ `inline static const FName HierarchyName = "Se` (scope `UE::Editor::DataStorage::Settings`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsSettings/Public/TedsSettingsEditorSubsystem.h` (Public)


#### class `UTedsSettingsEditorSubsystem`  
`class UTedsSettingsEditorSubsystem : public UEditorSubsystem`  
_L15-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L21 _public prototype_ `UTedsSettingsEditorSubsystem();`
- L23 _public prototype_ `const bool IsEnabled() const;`
- L25 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEnabledChanged) FOnEnabledChanged& OnEnabledChanged();`
- L35 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsContainer(const FName& ContainerName) const;` — Finds an existing container row. @param	ContainerName	The ContainerName to search for. @return	The found row or InvalidRowHandle if no existing row is found.
- L45 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsCategory(const FName& ContainerName, const FName& CategoryName) const;` — Finds an existing category row. @param	ContainerName	The ContainerName to search for. @param	CategoryName	The CategoryName to search for. @return	The found row or InvalidRowHandle if no existing row is found.
- L56 _public prototype_ `UE::Editor::DataStorage::RowHandle FindSettingsSection(const FName& ContainerName, const FName& CategoryName, const FName& SectionName) const;` — Finds an existing section row. @param	ContainerName	The ContainerName to search for. @param	CategoryName	The CategoryName to search for. @param	SectionName		The SectionName to search for. @return	The found row or InvalidRowHandle if no existing row is found.
- L68 _public prototype_ `bool GetSettingsSectionFromRow(UE::Editor::DataStorage::RowHandle SectionRow, FName& OutContainerName, FName& OutCategoryName, FName& OutSectionName);` — Gets the settings section details for the given section row. @param	SectionRow			The section row from which to read settings details. @param	OutContainerName	Reference to the ContainerName for the given row, only set if this method returns true. @param	OutCategoryName		Reference to the CategoryName for the given row, only set if this method returns true. @param	OutSectionName		Reference to the SectionName for the given row, only set if this method returns true. @return	True if the settings section details are successfully returned in the out parameters.
- L79 _public prototype_ `bool GetSettingsCategoryFromRow(UE::Editor::DataStorage::RowHandle CategoryRow, FName& OutContainerName, FName& OutCategoryName);` — Gets the settings category details for the given category row. @param	CategoryRow			The category row from which to read settings details. @param	OutContainerName	Reference to the ContainerName for the given row, only set if this method returns true. @param	OutCategoryName		Reference to the CategoryName for the given row, only set if this method returns true. @return	True if the settings category details are successfully returned in the out parameters.
- L83 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L84 _protected prototype_ `virtual void Deinitialize() override;`
- L88 _private member_ `TSharedPtr<FTedsSettingsManager> SettingsManager;`
- L89 _private member_ `FOnEnabledChanged EnabledChangedDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSSETTINGS_API`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEnabledChanged) FOnEnabledChanged& OnEnabledChanged();`
