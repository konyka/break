# Plugins / AlembicImporter

- module root: `Plugins/Importers/AlembicImporter/Source/AlembicImporter`
- headers: 4; symbols: 55
- symbol kinds: class=4, function=13, macro=1, member=11, prototype=23, struct=1, typedef=2
- PublicDependencyModuleNames: AlembicLibrary, Core, CoreUObject, EditorFramework, Engine, GeometryCache, InputCore, MainFrame, PropertyEditor, RHI, RenderCore, Slate, SlateCore, UnrealEd

### `Plugins/Importers/AlembicImporter/Source/AlembicImporter/Classes/AlembicImportFactory.h` (Public)


#### class `UAlembicImportFactory`  
`class UAlembicImportFactory : public UFactory, public FReimportHandler`  
_L23-111_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory,FReimportHandler`
- L29 _private member_ `TObjectPtr<UAbcImportSettings> ImportSettings;` — `UPROPERTY()` — Object used to show import options for Alembic
- L32 _private member_ `bool bShowOption;` — `UPROPERTY()`
- L35 _private prototype_ `void PostInitProperties();`
- L39 _private prototype_ `virtual FText GetDisplayName() const override;`
- L40 _private prototype_ `virtual bool DoesSupportClass(UClass * Class) override;`
- L41 _private prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L42 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L43 _private prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L47 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L48 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L49 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L51 _private prototype_ `void ShowImportOptionsWindow(TSharedPtr<SAlembicImportOptions>& Options, FString FilePath, const FAbcImporter& Importer);`
- L53 _private prototype_ `virtual int32 GetPriority() const override;`
- L64 _private prototype_ `TArray<UObject*> ImportStaticMesh(FAbcImporter& Importer, UObject* InParent, EObjectFlags Flags);` — Imports a StaticMesh (using AbcImporter) from the Alembic File @param Importer - AbcImporter instance @param InParent - Parent for the StaticMesh @param Flags - Creation Flags for the StaticMesh @return UObject*
- L74 _private prototype_ `UObject* ImportGeometryCache(FAbcImporter& Importer, UObject* InParent, EObjectFlags Flags);` — ImportGeometryCache @param Importer - AbcImporter instance @param InParent - Parent for the GeometryCache asset @param Flags - Creation Flags for the GeometryCache asset @return UObject*
- L84 _private prototype_ `TArray<UObject*> ImportSkeletalMesh(FAbcImporter& Importer, UObject* InParent, EObjectFlags Flags);` — ImportGeometryCache @param Importer - AbcImporter instance @param InParent - Parent for the GeometryCache asset @param Flags - Creation Flags for the GeometryCache asset @return UObject*
- L92 _private prototype_ `EReimportResult::Type ReimportStaticMesh(UStaticMesh* Mesh);` — ReimportStaticMesh @param Mesh - Static mesh instance to re import @return EReimportResult::Type
- L100 _private prototype_ `EReimportResult::Type ReimportGeometryCache(UGeometryCache* Cache);` — ReimportGeometryCache @param Cache - Geometry cache instance to re import @return EReimportResult::Type
- L108 _private prototype_ `EReimportResult::Type ReimportSkeletalMesh(USkeletalMesh* SkeletalMesh);` — ReimportGeometryCache @param Cache - Geometry cache instance to re import @return EReimportResult::Type
- L110 _private prototype_ `void PopulateOptionsWithImportData(UAbcAssetImportData* ImportData);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ALEMBICIMPORTER_API`

### `Plugins/Importers/AlembicImporter/Source/AlembicImporter/Private/AlembicImportOptions.h` (Private)


#### struct `FPolyMeshData`  
`struct FPolyMeshData`  
_L18-22_
- L20 _public function_ `FPolyMeshData(class FAbcPolyMesh* InPolyMesh) : PolyMesh(InPolyMesh)`
- L21 _public member_ `class FAbcPolyMesh* PolyMesh;`

#### class `SAlembicImportOptions`  
`class SAlembicImportOptions : public SCompoundWidget`  
_L26-98_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SAlembicImportOptions) : _ImportSettings(nullptr) , _WidgetWindow()`
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L44 _public function_ `FReply OnImport()`
- L54 _public function_ `FReply OnCancel()`
- L64 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L74 _public function_ `bool ShouldImport() const`
- L80 _public function_ `SAlembicImportOptions() : ImportSettings(nullptr) , bShouldImport(false)`
- L86 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(FPolyMeshDataPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L87 _private prototype_ `bool CanImport() const;`
- L89 _private prototype_ `void OnToggleAllItems(ECheckBoxState CheckType);`
- L90 _private prototype_ `void OnItemDoubleClicked(FPolyMeshDataPtr ClickedItem);`
- L92 _private member_ `UAbcImportSettings* ImportSettings;`
- L93 _private member_ `TWeakPtr< SWindow > WidgetWindow;`
- L94 _private member_ `TSharedPtr< SButton > ImportButton;`
- L95 _private member_ `bool bShouldImport;`
- L96 _private member_ `TArray<FPolyMeshDataPtr> PolyMeshData;`
- L97 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L24 _typedef_ `typedef TSharedPtr<FPolyMeshData> FPolyMeshDataPtr;`

### `Plugins/Importers/AlembicImporter/Source/AlembicImporter/Private/STrackSelectionTableRow.h` (Private)


#### class `STrackSelectionTableRow`  
`class STrackSelectionTableRow : public SMultiColumnTableRow<FPolyMeshDataPtr>`  
_L19-122_
- inherits: `SMultiColumnTableRow<FPolyMeshDataPtr>`
- desc: Implements a row widget for the dispatch state list.
- L24 _public function_ `SLATE_BEGIN_ARGS(STrackSelectionTableRow)`
- L36 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L50 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L109 _private function_ `ECheckBoxState ShouldImportEnabled() const`
- L114 _private function_ `void OnChangeShouldImport(ECheckBoxState NewState)`
- L120 _private member_ `FPolyMeshDataPtr PolyMeshData;`
- L121 _private member_ `FText InformationText;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr<FPolyMeshData> FPolyMeshDataPtr;`

### `Plugins/Importers/AlembicImporter/Source/AlembicImporter/Public/AlembicImporterModule.h` (Public)


#### class `IAlembicImporterModuleInterface`  
`class IAlembicImporterModuleInterface : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
