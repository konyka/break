# Plugins / TedsTypeInfo

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypeInfo`
- headers: 4; symbols: 108
- symbol kinds: class=2, function=1, member=11, namespace=21, prototype=30, struct=18, typedef=18, variable=7
- PrivateDependencyModuleNames: ClassViewer, Core, CoreUObject, Engine, TedsAlerts, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypeInfo/Private/TedsTypeInfoFactory.h` (Private)


#### struct `FDataStorageTypeInfoRequiresHierarchyUpdateTag`  
`struct FDataStorageTypeInfoRequiresHierarchyUpdateTag : public FEditorDataStorageTag`  
_L27-30_
- reflection: `USTRUCT(meta = (DisplayName = "Row requires a pass to assign its type hierarchy info"))`
- inherits: `FEditorDataStorageTag`

#### class `UTypeInfoFactory`  
`class UTypeInfoFactory final : public UEditorDataStorageFactory`  
_L33-81_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L39 _public prototype_ `virtual ~UTypeInfoFactory() override = default;`
- L42 _public prototype_ `void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L43 _public prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::ICompatibilityProvider& DataStorageCompatability) override;`
- L44 _public prototype_ `void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L45 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L46 _public prototype_ `void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L49 _public prototype_ `void ClearAllTypeInfo();`
- L50 _public prototype_ `void RefreshAllTypeInfo();`
- L54 _private prototype_ `void OnDatabaseUpdateCompleted();`
- L57 _private prototype_ `template <class Type> void PopulateTypeInfo();`
- L60 _private prototype_ `template <class TagToClear> void ClearTypeInfoByTag();`
- L62 _private prototype_ `bool TryAddTypeInfo(UE::Editor::DataStorage::ICoreProvider& DataStorage, const UStruct* InTypeInfo, UE::Editor::DataStorage::RowHandle& OutTypeRowHandle);`
- L63 _private prototype_ `void AddPropertyInfo(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle OwnerTypeRowHandle, const UStruct* InTypeInfo);`
- L65 _private prototype_ `bool FilterStructInfo(const UStruct* StructInfo);`
- L66 _private prototype_ `bool FilterClassInfo(const UClass* ClassInfo);`
- L68 _private prototype_ `void AddCommonColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowHandle, const UStruct* InTypeInfo);`
- L69 _private prototype_ `void AddStructColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowHandle, const UScriptStruct* InStructInfo);`
- L70 _private prototype_ `void AddClassColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowHandle, const UClass* InClassInfo);`
- L71 _private prototype_ `void AddVerseColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowHandle, const UVerseClass* InVerseTypeInfo);`
- L72 _private prototype_ `void AddIdoColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowHandle, const UVerseClass* InVerseTypeInfo);`
- L74 _private prototype_ `void AddCommonPropertyColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle TypeRowhandle, UE::Editor::DataStorage::RowHandle PropertyRowhandle, const FProperty* InPropertyInfo);`
- L77 _private member_ `bool bRefreshTypeInfoQueued = false;`
- L79 _private member_ `UE::Editor::DataStorage::TableHandle PropertyTable = UE::Editor::DataStorage::InvalidTableHandle;`
- L80 _private member_ `UE::Editor::DataStorage::FHierarchyHandle PropertyHierarchyHandle;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace Editor` (scope `UE`)
- L83 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L85 _typedef_ `using FTypeInfoRequiresHierarchyUpdateTag = FDataStorageTypeInfoRequiresHierarchyUpdateTag;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypeInfo/Public/Elements/Columns/TedsTypeInfoColumns.h` (Public)


#### struct `FDataStorageTypeInfoTag`  
`struct FDataStorageTypeInfoTag : public FEditorDataStorageTag`  
_L12-15_
- reflection: `USTRUCT(meta = (DisplayName = "Row is a type"))`
- inherits: `FEditorDataStorageTag`
- desc: Type Info Columns Start

#### struct `FDataStorageClassTypeInfoTag`  
`struct FDataStorageClassTypeInfoTag : public FEditorDataStorageTag`  
_L18-21_
- reflection: `USTRUCT(meta = (DisplayName = "Row type is a class"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageStructTypeInfoTag`  
`struct FDataStorageStructTypeInfoTag : public FEditorDataStorageTag`  
_L24-27_
- reflection: `USTRUCT(meta = (DisplayName = "Row type is a struct"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageTypeInfoInterfaceTag`  
`struct FDataStorageTypeInfoInterfaceTag : public FEditorDataStorageTag`  
_L30-33_
- reflection: `USTRUCT(meta = (DisplayName = "Row type is an Interface"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageVerseTypeInfoTag`  
`struct FDataStorageVerseTypeInfoTag : public FEditorDataStorageTag`  
_L36-39_
- reflection: `USTRUCT(meta = (DisplayName = "Row type is a Verse type"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageVirtualTypeInfoTag`  
`struct FDataStorageVirtualTypeInfoTag : public FEditorDataStorageTag`  
_L42-45_
- reflection: `USTRUCT(meta = (DisplayName = "Row type is virtualized"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageTypeInfoObjectPathColumn`  
`struct FDataStorageTypeInfoObjectPathColumn final : public FEditorDataStorageColumn`  
_L48-54_
- reflection: `USTRUCT(meta = (DisplayName = "Type Object Path"))`
- inherits: `FEditorDataStorageColumn`
- L53 _public member_ `FString ObjectPath;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FDataStorageTypeInfoVersePathColumn`  
`struct FDataStorageTypeInfoVersePathColumn final : public FEditorDataStorageColumn`  
_L57-63_
- reflection: `USTRUCT(meta = (DisplayName = "Type Verse Path"))`
- inherits: `FEditorDataStorageColumn`
- L62 _public member_ `FText VersePath;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FDataStorageVerseTypeInfoAccessLevel`  
`struct FDataStorageVerseTypeInfoAccessLevel : public FEditorDataStorageTag`  
_L66-69_
- reflection: `USTRUCT(meta = (DisplayName = "Verse type access level", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageHasUnknownPropertiesTag`  
`struct FDataStorageHasUnknownPropertiesTag : public FEditorDataStorageTag`  
_L72-75_
- reflection: `USTRUCT(meta = (DisplayName = "Row type has unknown properties"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStoragePropertyNameColumn`  
`struct FDataStoragePropertyNameColumn final : public FEditorDataStorageColumn`  
_L80-86_
- reflection: `USTRUCT(meta = (DisplayName = "Property Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: Property Info Columns Start
- L85 _public member_ `FText PropertyName;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FDataStoragePropertyOwnerTypeRowHandleColumn`  
`struct FDataStoragePropertyOwnerTypeRowHandleColumn final : public FEditorDataStorageColumn`  
_L89-94_
- reflection: `USTRUCT(meta = (DisplayName = "Property Owner Type Row Handle"))`
- inherits: `FEditorDataStorageColumn`
- L93 _public member_ `UE::Editor::DataStorage::RowHandle PropertyOwnerTypeRowHandle = UE::Editor::DataStorage::InvalidRowHandle;`

#### struct `FDataStoragePropertyTypeNameColumn`  
`struct FDataStoragePropertyTypeNameColumn final : public FEditorDataStorageColumn`  
_L97-103_
- reflection: `USTRUCT(meta = (DisplayName = "Property Type Name"))`
- inherits: `FEditorDataStorageColumn`
- L102 _public member_ `FText PropertyTypeName;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FDataStoragePropertyTypeNameInfoColumn`  
`struct FDataStoragePropertyTypeNameInfoColumn final : public FEditorDataStorageColumn`  
_L106-111_
- reflection: `USTRUCT(meta = (DisplayName = "Property Type Name Info"))`
- inherits: `FEditorDataStorageColumn`
- L110 _public member_ `UE::FPropertyTypeName PropertyTypeNameInfo;`

#### struct `FDataStoragePropertyMutableTag`  
`struct FDataStoragePropertyMutableTag : public FEditorDataStorageTag`  
_L114-117_
- reflection: `USTRUCT(meta = (DisplayName = "Property is mutable"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStoragePropertyInfoTag`  
`struct FDataStoragePropertyInfoTag : public FEditorDataStorageTag`  
_L120-123_
- reflection: `USTRUCT(meta = (DisplayName = "Row is a property"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDataStorageVersePropertyTag`  
`struct FDataStorageVersePropertyTag : public FEditorDataStorageTag`  
_L126-129_
- reflection: `USTRUCT(meta = (DisplayName = "Property is owned by a Verse type"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L132 _namespace_ `namespace UE`
- L132 _namespace_ `namespace Editor` (scope `UE`)
- L132 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L135 _typedef_ `using FTypeInfoTag = FDataStorageTypeInfoTag;` (scope `UE::Editor::DataStorage`) — Type Info Columns Start
- L136 _typedef_ `using FClassTypeInfoTag = FDataStorageClassTypeInfoTag;` (scope `UE::Editor::DataStorage`)
- L137 _typedef_ `using FStructTypeInfoTag = FDataStorageStructTypeInfoTag;` (scope `UE::Editor::DataStorage`)
- L138 _typedef_ `using FTypeInfoInterfaceTag = FDataStorageTypeInfoInterfaceTag;` (scope `UE::Editor::DataStorage`)
- L139 _typedef_ `using FTypeInfoObjectPathColumn = FDataStorageTypeInfoObjectPathColumn;` (scope `UE::Editor::DataStorage`)
- L140 _typedef_ `using FTypeInfoVersePathColumn = FDataStorageTypeInfoVersePathColumn;` (scope `UE::Editor::DataStorage`)
- L141 _typedef_ `using FVerseTypeInfoTag = FDataStorageVerseTypeInfoTag;` (scope `UE::Editor::DataStorage`)
- L142 _typedef_ `using FVirtualTypeInfoTag = FDataStorageVirtualTypeInfoTag;` (scope `UE::Editor::DataStorage`)
- L143 _typedef_ `using FVerseTypeInfoAccessLevel = FDataStorageVerseTypeInfoAccessLevel;` (scope `UE::Editor::DataStorage`)
- L144 _typedef_ `using FHasUnknownPropertiesTag = FDataStorageHasUnknownPropertiesTag;` (scope `UE::Editor::DataStorage`)
- L148 _typedef_ `using FPropertyNameColumn = FDataStoragePropertyNameColumn;` (scope `UE::Editor::DataStorage`) — Property Info Columns Start
- L149 _typedef_ `using FPropertyOwnerTypeRowHandleColumn = FDataStoragePropertyOwnerTypeRowHandleColumn;` (scope `UE::Editor::DataStorage`)
- L150 _typedef_ `using FPropertyTypeNameColumn = FDataStoragePropertyTypeNameColumn;` (scope `UE::Editor::DataStorage`)
- L151 _typedef_ `using FPropertyTypeNameInfoColumn = FDataStoragePropertyTypeNameInfoColumn;` (scope `UE::Editor::DataStorage`)
- L152 _typedef_ `using FPropertyMutableTag = FDataStoragePropertyMutableTag;` (scope `UE::Editor::DataStorage`)
- L153 _typedef_ `using FPropertyInfoTag = FDataStoragePropertyInfoTag;` (scope `UE::Editor::DataStorage`)
- L154 _typedef_ `using FVersePropertyTag = FDataStorageVersePropertyTag;` (scope `UE::Editor::DataStorage`)
- L158 _namespace_ `namespace UE`
- L158 _namespace_ `namespace Editor` (scope `UE`)
- L158 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L158 _namespace_ `namespace TypeInfo` (scope `UE::Editor::DataStorage`)
- L160 _variable_ `static const FName TypeMappingDomain = "Ty` (scope `UE::Editor::DataStorage::TypeInfo`)
- L161 _variable_ `static const FName TypeTableName = "Ty` (scope `UE::Editor::DataStorage::TypeInfo`)
- L162 _variable_ `static const FName PropertyTableName = "Pr` (scope `UE::Editor::DataStorage::TypeInfo`)
- L163 _variable_ `static const FName ClassHierarchyName = "Cl` (scope `UE::Editor::DataStorage::TypeInfo`)
- L164 _variable_ `static const FName PropertyHierarchyName = "Pr` (scope `UE::Editor::DataStorage::TypeInfo`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypeInfo/Public/TedsTypeInfoModule.h` (Public)


#### class `UE::Editor::DataStorage::TypeInfo::FTedsTypeInfoModule`  
`class FTedsTypeInfoModule : public IModuleInterface`  
_L9-31_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public prototype_ `static FTedsTypeInfoModule* Get();`
- L16 _public prototype_ `static FTedsTypeInfoModule& GetChecked();`
- L18 _public prototype_ `void EnableTedsTypeInfoIntegration();`
- L19 _public prototype_ `void DisableTedsTypeInfoIntegration();`
- L20 _public prototype_ `bool IsTedsTypeInfoIntegrationEnabled();`
- L22 _public prototype_ `void RefreshTypeInfo();`
- L23 _public prototype_ `void FlushTypeInfo();`
- L25 _public function_ `void SetTypeInfoFactoryEnabled()`
- L29 _private member_ `bool bTypeInfoFactoryEnabled = false;`
- L30 _private member_ `bool bDataStorageFeaturesEnabled = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L7 _namespace_ `namespace TypeInfo` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypeInfo/Public/TedsTypeInfoUtils.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L6 _namespace_ `namespace TypeInfo` (scope `UE::Editor::DataStorage`)
- L8 _variable_ `static const FName ClassSetupActionName = TEXT("Cla` (scope `UE::Editor::DataStorage::TypeInfo`)
- L9 _variable_ `static const FName PostClassSetupActionName = TEXT("Pos` (scope `UE::Editor::DataStorage::TypeInfo`)
