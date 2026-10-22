# Editor / SparseVolumeTexture

- module root: `Source/Editor/SparseVolumeTexture`
- headers: 7; symbols: 184
- symbol kinds: class=9, enum=2, enumerator=16, function=29, macro=5, member=54, namespace=2, prototype=46, struct=7, typedef=14
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, InputCore, MainFrame, RHI, Settings, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools, EditorWidgets
- PublicDependencyModuleNames: ApplicationCore, Core, Engine, Projects, RenderCore, Renderer, Slate, SlateCore, ToolWidgets

### `Source/Editor/SparseVolumeTexture/Private/OpenVDBGridAdapter.h` (Private)


#### class `IOpenVDBGridAdapterBase`  
`class IOpenVDBGridAdapterBase`  
_L110-118_
- desc: Interface for sampling and getting other values from an openVDB grid, abstracting away the actual type/format of the underlying grid.
- L113 _public prototype_ `virtual void IteratePhysical(TFunctionRef<void(const FIntVector3& Coord, uint32 NumComponents, float* VoxelValues)> OnVisit) const = 0;`
- L114 _public prototype_ `virtual float Sample(const FIntVector3& VoxelCoord, uint32 ComponentIndex) const = 0;`
- L115 _public prototype_ `virtual void GetMinMaxValue(uint32 ComponentIndex, float* OutMinVal, float* OutMaxVal) const = 0;`
- L116 _public prototype_ `virtual float GetBackgroundValue(uint32 ComponentIndex) const = 0;`
- L117 _public prototype_ `virtual ~IOpenVDBGridAdapterBase() = default;`

#### class `TOpenVDBGridAdapter`  
`template<typename GridType> class TOpenVDBGridAdapter : public IOpenVDBGridAdapterBase`  
_L121-213_
- inherits: `IOpenVDBGridAdapterBase`
- L123 _private typedef_ `using ValueType = typename GridType::ValueType;`
- L125 _public function_ `explicit TOpenVDBGridAdapter(openvdb::SharedPtr<GridType> Grid) : Grid(Grid), Accessor(Grid->getConstAccessor())`
- L130 _public function_ `void IteratePhysical(TFunctionRef<void(const FIntVector3& Coord, uint32 NumComponents, float* VoxelValues)> OnVisit) const override`
- L178 _public function_ `float Sample(const FIntVector3& VoxelCoord, uint32 ComponentIndex) const override`
- L184 _public function_ `void GetMinMaxValue(uint32 ComponentIndex, float* OutMinVal, float* OutMaxVal) const override`
- L205 _public function_ `float GetBackgroundValue(uint32 ComponentIndex) const override`
- L211 _private member_ `typename GridType::Ptr Grid;`
- L212 _private member_ `typename GridType::ConstAccessor Accessor;`

#### Free symbols / members of external scopes

- L14 _function_ `template<typename ValueType> constexpr uint32 GetOpenVDBValueNumComponents()`
- L20 _function_ `template<> constexpr uint32 GetOpenVDBValueNumComponents<FOpenVDBHalf>()`
- L26 _function_ `template<> constexpr uint32 GetOpenVDBValueNumComponents<float>()`
- L32 _function_ `template<> constexpr uint32 GetOpenVDBValueNumComponents<double>()`
- L38 _function_ `template<typename ValueType> float GetOpenVDBValueComponent(const ValueType& Value, uint32 ComponentIndex)`
- L44 _function_ `template<> inline float GetOpenVDBValueComponent<FOpenVDBHalf>(const FOpenVDBHalf& Value, uint32 ComponentIndex)`
- L50 _function_ `template<> inline float GetOpenVDBValueComponent<float>(const float& Value, uint32 ComponentIndex)`
- L56 _function_ `template<> inline float GetOpenVDBValueComponent<double>(const double& Value, uint32 ComponentIndex)`
- L62 _function_ `template<typename ValueType> ValueType GetOpenVDBMaxComponent(const ValueType& ValueA, const ValueType& ValueB)`
- L68 _function_ `template<> inline FOpenVDBHalf GetOpenVDBMaxComponent<FOpenVDBHalf>(const FOpenVDBHalf& ValueA, const FOpenVDBHalf& ValueB)`
- L74 _function_ `template<> inline float GetOpenVDBMaxComponent<float>(const float& ValueA, const float& ValueB)`
- L80 _function_ `template<> inline double GetOpenVDBMaxComponent<double>(const double& ValueA, const double& ValueB)`
- L86 _function_ `template<typename ValueType> ValueType GetOpenVDBMinComponent(const ValueType& ValueA, const ValueType& ValueB)`
- L92 _function_ `template<> inline FOpenVDBHalf GetOpenVDBMinComponent<FOpenVDBHalf>(const FOpenVDBHalf& ValueA, const FOpenVDBHalf& ValueB)`
- L98 _function_ `template<> inline float GetOpenVDBMinComponent<float>(const float& ValueA, const float& ValueB)`
- L104 _function_ `template<> inline double GetOpenVDBMinComponent<double>(const double& ValueA, const double& ValueB)`
- L217 _function_ `template<typename GridType> TSharedPtr<IOpenVDBGridAdapterBase> CreateOpenVDBGridAdapterInternal(openvdb::GridBase::Ptr Grid)` — This is just to not have to repeat the GridType multiple times per MakeShared<>() call.
- L223 _function_ `inline TSharedPtr<IOpenVDBGridAdapterBase> CreateOpenVDBGridAdapter(openvdb::GridBase::Ptr Grid)` — Creates an adapter suitable for the type of the given grid or nullptr if the type is not supported.

### `Source/Editor/SparseVolumeTexture/Private/OpenVDBImportWindow.h` (Private)


#### class `SOpenVDBGridInfoTableRow`  
`class SOpenVDBGridInfoTableRow : public SMultiColumnTableRow<TSharedPtr<FOpenVDBGridInfo>>`  
_L18-31_
- inherits: `SMultiColumnTableRow<TSharedPtr<FOpenVDBGridInfo>>`
- L21 _public function_ `SLATE_BEGIN_ARGS(SOpenVDBGridInfoTableRow)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L27 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L30 _private member_ `TSharedPtr<FOpenVDBGridInfo> OpenVDBGridInfo;`

#### class `SOpenVDBComponentPicker`  
`class SOpenVDBComponentPicker : public SCompoundWidget`  
_L33-51_
- inherits: `SCompoundWidget`
- L36 _public function_ `SLATE_BEGIN_ARGS(SOpenVDBComponentPicker)`
- L43 _public prototype_ `void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `void RefreshUIFromData();`
- L47 _private member_ `FOpenVDBSparseVolumeAttributesDesc* AttributesDesc;`
- L48 _private member_ `uint32 ComponentIndex;`
- L49 _private member_ `const TArray<TSharedPtr<FOpenVDBGridComponentInfo>>* OpenVDBGridComponentInfo;`
- L50 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FOpenVDBGridComponentInfo>>> GridComboBox;`

#### class `SOpenVDBAttributesConfigurator`  
`class SOpenVDBAttributesConfigurator : public SCompoundWidget`  
_L53-72_
- inherits: `SCompoundWidget`
- L56 _public function_ `SLATE_BEGIN_ARGS(SOpenVDBAttributesConfigurator)`
- L64 _public prototype_ `void Construct(const FArguments& InArgs);`
- L65 _public prototype_ `void RefreshUIFromData();`
- L68 _private member_ `FOpenVDBSparseVolumeAttributesDesc* AttributesDesc;`
- L69 _private member_ `TSharedPtr<SOpenVDBComponentPicker> ComponentPickers[4];`
- L70 _private member_ `const TArray<TSharedPtr<ESparseVolumeAttributesFormat>>* OpenVDBSupportedTargetFormats;`
- L71 _private member_ `TSharedPtr<SComboBox<TSharedPtr<ESparseVolumeAttributesFormat>>> FormatComboBox;`

#### class `SOpenVDBImportWindow`  
`class SOpenVDBImportWindow : public SCompoundWidget`  
_L74-118_
- inherits: `SCompoundWidget`
- L77 _public function_ `SLATE_BEGIN_ARGS(SOpenVDBImportWindow)`
- L91 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L92 _public prototype_ `void Construct(const FArguments& InArgs);`
- L93 _public prototype_ `FReply OnImport();`
- L94 _public prototype_ `FReply OnCancel();`
- L95 _public prototype_ `bool ShouldImport() const;`
- L96 _public prototype_ `bool ShouldImportAsSequence() const;`
- L99 _private member_ `FOpenVDBImportOptions* ImportOptions;`
- L100 _private member_ `const FOpenVDBImportOptions* DefaultImportOptions;`
- L101 _private member_ `bool bIsSequence;`
- L102 _private member_ `const TArray<TSharedPtr<FOpenVDBGridInfo>>* OpenVDBGridInfo;`
- L103 _private member_ `const TArray<TSharedPtr<FOpenVDBGridComponentInfo>>* OpenVDBGridComponentInfo;`
- L104 _private member_ `const TArray<TSharedPtr<ESparseVolumeAttributesFormat>>* OpenVDBSupportedTargetFormats;`
- L105 _private member_ `TSharedPtr<SOpenVDBAttributesConfigurator> AttributesAConfigurator;`
- L106 _private member_ `TSharedPtr<SOpenVDBAttributesConfigurator> AttributesBConfigurator;`
- L107 _private member_ `TSharedPtr<SCheckBox> ImportAsSequenceCheckBox;`
- L108 _private member_ `TSharedPtr<SButton> ImportButton;`
- L109 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L110 _private member_ `bool bShouldImport;`
- L112 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);`
- L113 _private prototype_ `TSharedRef<ITableRow> GenerateGridInfoItemRow(TSharedPtr<FOpenVDBGridInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L114 _private prototype_ `bool CanImport() const;`
- L115 _private prototype_ `FReply OnResetToDefaultClick();`
- L116 _private prototype_ `FText GetImportTypeDisplayText() const;`
- L117 _private prototype_ `void SetDefaultGridAssignment();`

### `Source/Editor/SparseVolumeTexture/Private/SparseVolumeTextureOpenVDB.h` (Private)


#### Free symbols / members of external scopes

- L22 _macro_ `#define M_PI 3.14159265358979323846`
- L23 _macro_ `#define LOCAL_M_PI 1`
- L27 _macro_ `#define M_PI_2 1.57079632679489661923 // pi/2`
- L28 _macro_ `#define LOCAL_M_PI_2 1`
- L31 _macro_ `#define BOOST_ALLOW_DEPRECATED_HEADERS`
- L42 _typedef_ `using FOpenVDBHalf = openvdb::math::internal::half;`
- L43 _typedef_ `using FOpenVDBHalf1Grid = openvdb::Grid<openvdb::tree::Tree4<FOpenVDBHalf, 5, 4, 3>::Type>;`
- L44 _typedef_ `using FOpenVDBHalf2Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::math::Vec2<FOpenVDBHalf>, 5, 4, 3>::Type>;`
- L45 _typedef_ `using FOpenVDBHalf3Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::math::Vec3<FOpenVDBHalf>, 5, 4, 3>::Type>;`
- L46 _typedef_ `using FOpenVDBHalf4Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::math::Vec4<FOpenVDBHalf>, 5, 4, 3>::Type>;`
- L47 _typedef_ `using FOpenVDBFloat1Grid = openvdb::FloatGrid;`
- L48 _typedef_ `using FOpenVDBFloat2Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::Vec2f, 5, 4, 3>::Type>;`
- L49 _typedef_ `using FOpenVDBFloat3Grid = openvdb::Vec3SGrid;`
- L50 _typedef_ `using FOpenVDBFloat4Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::Vec4f, 5, 4, 3>::Type>;`
- L51 _typedef_ `using FOpenVDBDouble1Grid = openvdb::DoubleGrid;`
- L52 _typedef_ `using FOpenVDBDouble2Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::Vec2d, 5, 4, 3>::Type>;`
- L53 _typedef_ `using FOpenVDBDouble3Grid = openvdb::Vec3DGrid;`
- L54 _typedef_ `using FOpenVDBDouble4Grid = openvdb::Grid<openvdb::tree::Tree4<openvdb::Vec4d, 5, 4, 3>::Type>;`

### `Source/Editor/SparseVolumeTexture/Public/OpenVDBImportOptions.h` (Public)


#### enum `ESparseVolumeAttributesFormat`  
`enum class ESparseVolumeAttributesFormat : uint8`  
_L10-15_
- L12 _public enumerator_ `Unorm8 = 0`
- L13 _public enumerator_ `Float16 = 1`
- L14 _public enumerator_ `Float32 = 2`

#### struct `FOpenVDBSparseVolumeComponentMapping`  
`struct FOpenVDBSparseVolumeComponentMapping`  
_L17-21_
- L19 _public member_ `int32 SourceGridIndex = INDEX_NONE;`
- L20 _public member_ `int32 SourceComponentIndex = INDEX_NONE;`

#### struct `FOpenVDBSparseVolumeAttributesDesc`  
`struct FOpenVDBSparseVolumeAttributesDesc`  
_L23-27_
- L25 _public member_ `TStaticArray<FOpenVDBSparseVolumeComponentMapping, 4> Mappings;`
- L26 _public member_ `ESparseVolumeAttributesFormat Format = ESparseVolumeAttributesFormat::Unorm8;`

#### struct `FOpenVDBImportOptions`  
`struct FOpenVDBImportOptions`  
_L29-33_
- L31 _public member_ `TStaticArray<FOpenVDBSparseVolumeAttributesDesc, 2> Attributes;`
- L32 _public member_ `bool bIsSequence = false;`

#### enum `EOpenVDBGridType`  
`enum class EOpenVDBGridType : uint8`  
_L35-50_
- L37 _public enumerator_ `Unknown = 0`
- L38 _public enumerator_ `Half`
- L39 _public enumerator_ `Half2`
- L40 _public enumerator_ `Half3`
- L41 _public enumerator_ `Half4`
- L42 _public enumerator_ `Float`
- L43 _public enumerator_ `Float2`
- L44 _public enumerator_ `Float3`
- L45 _public enumerator_ `Float4`
- L46 _public enumerator_ `Double`
- L47 _public enumerator_ `Double2`
- L48 _public enumerator_ `Double3`
- L49 _public enumerator_ `Double4`

#### struct `FOpenVDBGridInfo`  
`struct FOpenVDBGridInfo`  
_L52-64_
- L54 _public member_ `FTransform Transform;`
- L55 _public member_ `FIntVector3 VolumeActiveAABBMin;`
- L56 _public member_ `FIntVector3 VolumeActiveAABBMax;`
- L57 _public member_ `FIntVector3 VolumeActiveDim;`
- L58 _public member_ `FString Name;`
- L59 _public member_ `FString DisplayString;` — Contains Index (into source file grids), Type and Name
- L60 _public member_ `uint32 Index;`
- L61 _public member_ `uint32 NumComponents;`
- L62 _public member_ `EOpenVDBGridType Type;`
- L63 _public member_ `bool bIsInWorldSpace;`

#### struct `FOpenVDBGridComponentInfo`  
`struct FOpenVDBGridComponentInfo`  
_L66-72_
- L68 _public member_ `uint32 Index;`
- L69 _public member_ `uint32 ComponentIndex;`
- L70 _public member_ `FString Name;`
- L71 _public member_ `FString DisplayString;` — Contains source file grid index, name and component (if it is a multi component type like Float3)

#### struct `FOpenVDBPreviewData`  
`struct FOpenVDBPreviewData`  
_L74-82_
- L76 _public member_ `TArray64<uint8> LoadedFile;`
- L77 _public member_ `TArray<FOpenVDBGridInfo> GridInfo;`
- L78 _public member_ `TArray<TSharedPtr<FOpenVDBGridInfo>> GridInfoPtrs;`
- L79 _public member_ `TArray<TSharedPtr<FOpenVDBGridComponentInfo>> GridComponentInfoPtrs;`
- L80 _public member_ `TArray<FString> SequenceFilenames;`
- L81 _public member_ `FOpenVDBImportOptions DefaultImportOptions;`

#### class `UOpenVDBImportOptionsObject`  
`class UOpenVDBImportOptionsObject : public UObject`  
_L85-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L90 _public member_ `FOpenVDBPreviewData PreviewData;`

### `Source/Editor/SparseVolumeTexture/Public/SparseVolumeTextureFactory.h` (Public)


#### class `USparseVolumeTextureFactory`  
`class USparseVolumeTextureFactory : public UFactory, public FReimportHandler`  
_L17-62_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory,FReimportHandler`
- desc: Responsible for creating and importing Sparse Volume Texture objects
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual bool ConfigureProperties() override;`
- L32 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L34 _public prototype_ `virtual bool CanCreateNew() const override;`
- L39 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L42 _public prototype_ `virtual void CleanUp() override;`
- L43 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L44 _public prototype_ `virtual bool DoesSupportClass(UClass* Class) override;`
- L45 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L50 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L51 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L52 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L55 _public prototype_ `UObject* ImportWithTransform(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& bOutOperationCanceled, const FTransform& AdditionalFrameTransform);`
- L61 _private prototype_ `UObject* ImportInternal(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& bOutOperationCanceled, bool bIsReimport, const FTransform& AdditionalFrameTransform = FTransform::Identity);`

#### Free symbols / members of external scopes

- L64 _prototype_ `bool LoadOpenVDBPreviewData(const FString& Filename, FOpenVDBPreviewData* OutPreviewData);`

### `Source/Editor/SparseVolumeTexture/Public/SparseVolumeTextureModule.h` (Public)


#### class `FSparseVolumeTextureModule`  
`class FSparseVolumeTextureModule : public IModuleInterface`  
_L13-35_
- inherits: `IModuleInterface`
- desc: A sparse volume texture
- L17 _public function_ `static FSparseVolumeTextureModule& GetSparseVolumeTextureModule()`
- L29 _private prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L34 _private prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.

### `Source/Editor/SparseVolumeTexture/Public/SparseVolumeTextureOpenVDBUtility.h` (Public)


#### struct `FOpenVDBToSVTConversionResult`  
`struct FOpenVDBToSVTConversionResult`  
_L19-25_
- L21 _public member_ `struct FSparseVolumeAssetHeader* Header;`
- L22 _public member_ `TArray<uint32>* PageTable;`
- L23 _public member_ `TArray<uint8>* PhysicalTileDataA;`
- L24 _public member_ `TArray<uint8>* PhysicalTileDataB;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SVT` (scope `UE`)
- L27 _prototype_ `bool IsOpenVDBGridValid(const FOpenVDBGridInfo& GridInfo, const FString& Filename);`
- L29 _prototype_ `bool GetOpenVDBGridInfo(TArray64<uint8>& SourceFile, bool bCreateStrings, TArray<FOpenVDBGridInfo>* OutGridInfo);`
- L31 _prototype_ `bool ConvertOpenVDBToSparseVolumeTexture(TArray64<uint8>& SourceFile, const struct FOpenVDBImportOptions& ImportOptions, const FIntVector3& VolumeBoundsMin, UE::SVT::FTextureData& OutResult, FTransform& OutFrameTransform);`
- L33 _prototype_ `const TCHAR* OpenVDBGridTypeToString(EOpenVDBGridType Type);`
- L35 _prototype_ `FString GetVDBSequenceBaseFileName(const FString& FileName, bool bDiscardNumbersOnly);`
- L37 _prototype_ `TArray<FString> FindOpenVDBSequenceFileNames(const FString& Filename);`
