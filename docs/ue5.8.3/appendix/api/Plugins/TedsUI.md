# Plugins / TedsUI

- module root: `Plugins/Experimental/EditorDataStorage/Source/TedsUI`
- headers: 9; symbols: 86
- symbol kinds: class=9, macro=3, member=3, namespace=12, prototype=51, struct=8
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AppFramework, InputCore, ToolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, TedsCore, ToolMenus, TypedElementFramework

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Private/Processors/WidgetReferenceColumnUpdateProcessor.h` (Private)


#### class `UWidgetReferenceColumnUpdateFactory`  
`class UWidgetReferenceColumnUpdateFactory : public UEditorDataStorageFactory`  
_L16-28_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Queries that check whether or not a widget still exists. If it has been deleted then it will remove the column from the Data Storage or deletes the entire row if the FTypedElementSlateWidgetReferenceDeletesRowTag was found.
- L21 _public prototype_ `~UWidgetReferenceColumnUpdateFactory() override = default;`
- L23 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L26 _private prototype_ `void RegisterDeleteRowOnWidgetDeleteQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;`
- L27 _private prototype_ `void RegisterDeleteColumnOnWidgetDeleteQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Private/TedsUIModule.h` (Private)


#### class `FTedsUIModule`  
`class FTedsUIModule : public IModuleInterface, public FGCObject`  
_L10-29_
- inherits: `IModuleInterface,FGCObject`
- L13 _public prototype_ `~FTedsUIModule() override = default;`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L28 _public prototype_ `FString GetReferencerName() const override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Private/Widgets/SlateColorWidget.h` (Private)


#### class `USlateColorWidgetFactory`  
`class USlateColorWidgetFactory : public UEditorDataStorageFactory`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~USlateColorWidgetFactory() override = default;`
- L18 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FSlateColorWidgetConstructor`  
`struct FSlateColorWidgetConstructor : public FSimpleWidgetConstructor`  
_L24-38_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to show and edit the color column in TEDS
- L29 _public prototype_ `FSlateColorWidgetConstructor();`
- L30 _public prototype_ `~FSlateColorWidgetConstructor() override = default;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Private/Widgets/UrlWidget.h` (Private)


#### class `UUrlWidgetFactory`  
`class UUrlWidgetFactory : public UEditorDataStorageFactory`  
_L17-26_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L22 _public prototype_ `~UUrlWidgetFactory() override = default;`
- L24 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FUrlWidgetConstructor`  
`struct FUrlWidgetConstructor : public FSimpleWidgetConstructor`  
_L30-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to display a URL in TEDS
- L35 _public prototype_ `FUrlWidgetConstructor();`
- L36 _public prototype_ `~FUrlWidgetConstructor() override = default;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Private/Widgets/WorldWidget.h` (Private)


#### class `UWorldWidgetFactory`  
`class UWorldWidgetFactory : public UEditorDataStorageFactory`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UWorldWidgetFactory() override = default;`
- L20 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FWorldWidgetConstructor`  
`struct FWorldWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-40_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to display the name and type of a UWorld
- L31 _public prototype_ `FWorldWidgetConstructor();`
- L32 _public prototype_ `~FWorldWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Public/Widgets/ExportedTextWidget.h` (Public)


#### class `UExportedTextWidgetFactory`  
`class UExportedTextWidgetFactory : public UEditorDataStorageFactory`  
_L21-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L26 _public prototype_ `virtual ~UExportedTextWidgetFactory() override = default;`
- L28 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FExportedTextWidgetConstructor`  
`struct FExportedTextWidgetConstructor : public FSimpleWidgetConstructor`  
_L33-61_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L38 _public prototype_ `FExportedTextWidgetConstructor();`
- L39 _public prototype_ `virtual ~FExportedTextWidgetConstructor() override = default;`
- L44 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L45 _public prototype_ `virtual const UE::Editor::DataStorage::Queries::FConditions* GetQueryConditions(const UE::Editor::DataStorage::ICoreProvider* Storage) const override;`
- L47 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row) const override;`
- L50 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L59 _protected member_ `UE::Editor::DataStorage::Queries::FConditions MatchedColumn;` — The column this exported text widget is operating on

#### struct `FExportedTextWidgetTag`  
`struct FExportedTextWidgetTag : public FEditorDataStorageTag`  
_L64-67_
- reflection: `USTRUCT(meta = (DisplayName = "Exported text widget"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSUI_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Public/Widgets/GeneralWidgetRegistrationFactory.h` (Public)


#### class `UGeneralWidgetRegistrationFactory`  
`class UGeneralWidgetRegistrationFactory : public UEditorDataStorageFactory`  
_L13-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L18 _public member_ `static const FName LargeCellPurpose;`
- L19 _public member_ `static const FName HeaderPurpose;`
- L21 _public prototype_ `~UGeneralWidgetRegistrationFactory() override = default;`
- L23 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSUI_API`

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Public/Widgets/LabelWidget.h` (Public)


#### class `ULabelWidgetFactory`  
`class ULabelWidgetFactory : public UEditorDataStorageFactory`  
_L20-30_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L25 _public prototype_ `~ULabelWidgetFactory() override = default;`
- L27 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L29 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FLabelWidgetConstructor`  
`struct FLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L33-51_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L38 _public prototype_ `FLabelWidgetConstructor();`
- L39 _public prototype_ `~FLabelWidgetConstructor() override = default;`
- L41 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsUI/Public/Widgets/PackagePathWidget.h` (Public)


#### class `UPackagePathWidgetFactory`  
`class UPackagePathWidgetFactory : public UEditorDataStorageFactory`  
_L21-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L26 _public prototype_ `~UPackagePathWidgetFactory() override = default;`
- L28 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FPackagePathWidgetConstructor`  
`struct FPackagePathWidgetConstructor : public FTypedElementWidgetConstructor`  
_L33-48_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L38 _public prototype_ `FPackagePathWidgetConstructor();`
- L39 _public prototype_ `~FPackagePathWidgetConstructor() override = default;`
- L42 _protected prototype_ `explicit FPackagePathWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L44 _protected prototype_ `TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L45 _protected prototype_ `bool FinalizeWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`

#### struct `FLoadedPackagePathWidgetConstructor`  
`struct FLoadedPackagePathWidgetConstructor : public FPackagePathWidgetConstructor`  
_L51-63_
- reflection: `USTRUCT()`
- inherits: `FPackagePathWidgetConstructor`
- L56 _public prototype_ `FLoadedPackagePathWidgetConstructor();`
- L57 _public prototype_ `~FLoadedPackagePathWidgetConstructor() override = default;`
- L60 _protected prototype_ `bool FinalizeWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSUI_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
