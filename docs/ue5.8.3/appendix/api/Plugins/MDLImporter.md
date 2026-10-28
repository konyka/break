# Plugins / MDLImporter

- module root: `Plugins/Enterprise/MDLImporter/Source/MDLImporter`
- headers: 43; symbols: 1326
- symbol kinds: class=37, delegate=1, enum=17, enumerator=158, function=354, macro=10, member=218, namespace=95, prototype=386, struct=29, typedef=19, union=2
- PrivateDependencyModuleNames: Analytics, AssetTools, Core, CoreUObject, EditorFramework, Engine, ImageCore, InputCore, MainFrame, MaterialEditor, MessageLog, Projects, RHI, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLImporter.h` (Private)


#### class `FMDLImporter`  
`class FMDLImporter`  
_L25-71_
- L28 _public typedef_ `using FProgressFunc = TFunction<void(const FString& MsgName, int MaterialIndex)>;`
- L30 _public prototype_ `FMDLImporter(const FString& PluginPath);`
- L31 _public prototype_ `~FMDLImporter();`
- L33 _public prototype_ `bool IsLoaded() const;`
- L35 _public prototype_ `const TArray<UMaterialInterface*>& GetCreatedMaterials() const;` — Returns newly created materials.
- L37 _public prototype_ `const TArray<MDLImporterLogging::FLogMessage>& GetLogMessages() const;` — Returns any logged messages and clears them afterwards.
- L40 _public prototype_ `bool OpenFile(const FString& InFileName, const UMDLImporterOptions& InImporterOptions, Mdl::FMaterialCollection& OutMaterials);` — Imports materials from an MDL file.
- L41 _public prototype_ `bool LoadModule(const FString& InModuleName, const UMDLImporterOptions& InImporterOptions, Mdl::FMaterialCollection& OutMaterials);`
- L44 _public prototype_ `bool ImportMaterials(UObject* ParentPackage, EObjectFlags Flags, Mdl::FMaterialCollection& Materials, FProgressFunc ProgressFunc = nullptr);` — Finalize import process and create the materials.
- L47 _public prototype_ `bool Reimport(const FString& InFileName, const UMDLImporterOptions& InImporterOptions, UMaterialInterface* OutMaterial);` — Re-imports a material from the given filename.
- L49 _public prototype_ `void CleanUp();`
- L51 _public prototype_ `void AddSearchPath(const FString& SearchPath);`
- L52 _public prototype_ `void RemoveSearchPath(const FString& SearchPath);`
- L55 _private prototype_ `void SetTextureFactory(UTextureFactory* Factory);`
- L56 _private prototype_ `bool DistillMaterials(const TMap<FString, UMaterial*>& MaterialsMap, Mdl::FMaterialCollection& Materials, FProgressFunc ProgressFunc);`
- L58 _private prototype_ `void ConvertUnsuportedVirtualTextures() const;`
- L62 _private member_ `TUniquePtr<Mdl::FApiContext> MdlContext;`
- L63 _private member_ `TUniquePtr<Generator::FMaterialTextureFactory> TextureFactory;`
- L64 _private member_ `TUniquePtr<FMDLMaterialFactory> MaterialFactory;`
- L65 _private member_ `TUniquePtr<FMDLMapHandler> DistillationMapHandler;`
- L66 _private member_ `FString ActiveFilename;`
- L67 _private member_ `FString ActiveModuleName;`
- L70 _private member_ `mutable TArray<MDLImporterLogging::FLogMessage> LogMessages;`
- L74 _function_ `inline bool FMDLImporter::IsLoaded() const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Mdl`
- L20 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLImporterFactory.h` (Private)


#### class `UMDLImporterFactory`  
`class UMDLImporterFactory : public UFactory, public FReimportHandler`  
_L17-46_
- reflection: `UCLASS(HideCategories = Object, CollapseCategories)`
- inherits: `UFactory,FReimportHandler`
- L22 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L24 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L27 _public prototype_ `virtual void CleanUp() override;`
- L31 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L33 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L35 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L39 _private prototype_ `bool LoadMaterials(IMdlFileImporter* Importer, UObject* InPackage, EObjectFlags InFlags, const FString& InFilename, const UMDLImporterOptions& InImporterOptions, FFeedbackContext& Warn);`
- L42 _private prototype_ `void SendAnalytics(int32 ImportDurationInSeconds, bool bImportSuccess, const FString& InFilename) const;`
- L45 _private member_ `IMDLImporterModule* MDLImporterModule;`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLMapHandler.h` (Private)


#### class `FMDLMapHandler`  
`class FMDLMapHandler : public Mdl::IMapDistilHandler`  
_L20-54_
- inherits: `Mdl::IMapDistilHandler`
- L23 _public prototype_ `explicit FMDLMapHandler(const Mdl::FApiContext& MdlContext);`
- L24 _public prototype_ `virtual ~FMDLMapHandler();`
- L26 _public prototype_ `virtual void PreImport(const mi::neuraylib::IMaterial_definition& MDLMaterialDefinition, const mi::neuraylib::ICompiled_material& MDLMaterial, mi::neuraylib::ITransaction& MDLTransaction) override;`
- L29 _public prototype_ `virtual bool Import(const FString& MapName, bool bIsTexture, Mdl::FBakeParam& MapBakeParam) override;`
- L31 _public prototype_ `virtual void PostImport() override;`
- L34 _public prototype_ `void SetMaterials(const TMap<FString, UMaterial*>& Materials);`
- L35 _public prototype_ `void SetTextureFactory(Generator::FMaterialTextureFactory* Factory);`
- L37 _public prototype_ `void Cleanup();`
- L39 _public prototype_ `TArray<MDLImporterLogging::FLogMessage> GetLogMessages();`
- L40 _public prototype_ `void SetFunctionAssetPath(const TCHAR* AssetPath);`
- L41 _public prototype_ `void SetObjectFlags(EObjectFlags ObjectFlags);`
- L44 _private prototype_ `void SetupNormalExpression(const FString& MapName);`
- L47 _private member_ `Generator::FMaterialExpressionFactory MaterialExpressionFactory;`
- L48 _private member_ `TMap<FString, UMaterial*> Materials;`
- L49 _private member_ `TUniquePtr<Generator::FFunctionLoader> FunctionLoader;`
- L50 _private member_ `Generator::FMaterialTextureFactory* TextureFactory;`
- L51 _private member_ `UMaterial* CurrentMaterial;`
- L52 _private member_ `UMaterialExpression* CurrentNormalExpression;`
- L53 _private member_ `UMaterialExpression* FirstNormalExpression;`
- L56 _function_ `inline void FMDLMapHandler::SetMaterials(const TMap<FString, UMaterial*>& InMaterials)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Mdl`
- L14 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLMaterialFactory.h` (Private)


#### class `FMDLMaterialFactory`  
`class FMDLMaterialFactory`  
_L21-47_
- L24 _public prototype_ `FMDLMaterialFactory(Generator::FMaterialTextureFactory& MaterialTextureFactory);`
- L25 _public prototype_ `~FMDLMaterialFactory();`
- L27 _public prototype_ `bool CreateMaterials(const FString& Filename, UObject* ParentPackage, EObjectFlags Flags, Mdl::FMaterialCollection& Materials);`
- L29 _public prototype_ `void PostImport(Mdl::FMaterialCollection& Materials);`
- L31 _public prototype_ `void Reimport(const Mdl::FMaterial& MdlMaterial, UMaterial& Material);`
- L34 _public prototype_ `const TArray<UMaterialInterface*>& GetCreatedMaterials() const;` — Returns newly created materials.
- L36 _public prototype_ `const TMap<FString, UMaterial*>& GetNameMaterialMap() const;` — Returns a map with the MDL DB material names
- L38 _public prototype_ `void CleanUp();`
- L42 _private member_ `TUniquePtr<FMDLMaterialSelector> MaterialSelector;`
- L43 _private member_ `TUniquePtr<FMDLMaterialPropertyFactory> MaterialPropertyFactory;`
- L45 _private member_ `TMap<FString, UMaterial*> NameMaterialMap;`
- L46 _private member_ `TArray<UMaterialInterface*> CreatedMaterials;`
- L49 _function_ `inline const TArray<UMaterialInterface*>& FMDLMaterialFactory::GetCreatedMaterials() const`
- L54 _function_ `inline const TMap<FString, UMaterial*>& FMDLMaterialFactory::GetNameMaterialMap() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Mdl`
- L16 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLMaterialProperty.h` (Private)


#### struct `FMDLMaterialProperty`  
`struct FMDLMaterialProperty`  
_L8-36_
- L18 _public member_ `int Id;`
- L19 _public member_ `FString Name;`
- L20 _public member_ `EPropertyType Type;`
- L23 _public member_ `Common::FTextureProperty Texture;` — @note Either a texture or a simple value.
- L29 _public member_ `bool bIsConstant;`
- L31 _public function_ `FMDLMaterialProperty() : Id(-1) , bIsConstant(false)`

#### enum `FMDLMaterialProperty::EPropertyType`  
`enum class EPropertyType`  
_L10-16_
- L12 _public enumerator_ `Texture`
- L13 _public enumerator_ `Vector`
- L14 _public enumerator_ `Scalar`
- L15 _public enumerator_ `Boolean`

#### union `FMDLMaterialProperty::(anonymous)`  
`union`  
_L24-28_

#### Free symbols / members of external scopes

- L25 _member_ `float Color[4];` (scope `FMDLMaterialProperty::__anone2461e84010a`) — FLinearColor
- L26 _member_ `float Value;` (scope `FMDLMaterialProperty::__anone2461e84010a`)
- L27 _member_ `bool bValue;` (scope `FMDLMaterialProperty::__anone2461e84010a`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLMaterialPropertyFactory.h` (Private)


#### class `FMDLMaterialPropertyFactory`  
`class FMDLMaterialPropertyFactory`  
_L20-33_
- L23 _public prototype_ `FMDLMaterialPropertyFactory();`
- L24 _public prototype_ `~FMDLMaterialPropertyFactory();`
- L26 _public prototype_ `void SetTextureFactory(Generator::FMaterialTextureFactory* Factory);`
- L28 _public prototype_ `Mat::FParameterMap CreateProperties(EObjectFlags Flags, const Mdl::FMaterial& MdlMaterial, UMaterial& Material);`
- L31 _private member_ `TArray<FMDLMaterialProperty> MaterialProperties;`
- L32 _private member_ `Generator::FMaterialTextureFactory* TextureFactory;`
- L35 _function_ `inline void FMDLMaterialPropertyFactory::SetTextureFactory(Generator::FMaterialTextureFactory* Factory)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Generator`
- L15 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MDLMaterialSelector.h` (Private)


#### class `FMDLMaterialSelector`  
`class FMDLMaterialSelector`  
_L19-48_
- L34 _public prototype_ `FMDLMaterialSelector();`
- L35 _public prototype_ `~FMDLMaterialSelector();`
- L37 _public prototype_ `EMaterialType GetMaterialType(const Mdl::FMaterial& Material) const;`
- L39 _public prototype_ `const Mat::IMaterialFactory& GetMaterialFactory(EMaterialType MaterialType) const;`
- L40 _public prototype_ `const Mat::IMaterialFactory& GetMaterialFactory(const Mdl::FMaterial& Material) const;`
- L42 _public prototype_ `static FString ToString(EMaterialType Type);`
- L45 _private member_ `TArray<TSharedPtr<Mat::IMaterialFactory>, TFixedAllocator<(int)EMaterialType::Count> > MaterialFactories;`
- L47 _private member_ `TUniquePtr<Generator::FFunctionLoader> FunctionLoader;`

#### enum `FMDLMaterialSelector::EMaterialType`  
`enum class EMaterialType`  
_L22-32_
- L24 _public enumerator_ `Opaque = 0`
- L25 _public enumerator_ `Masked`
- L26 _public enumerator_ `Translucent`
- L27 _public enumerator_ `Clearcoat`
- L28 _public enumerator_ `Emissive`
- L29 _public enumerator_ `Carpaint`
- L30 _public enumerator_ `Subsurface`
- L31 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Mat`
- L10 _namespace_ `namespace Mdl`
- L15 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/MdlFileImporter.h` (Private)


#### class `IMdlFileImporter`  
`class IMdlFileImporter`  
_L15-31_
- L18 _public typedef_ `using FProgressFunc = TFunction<void(const FString& MsgName, int MaterialIndex)>;`
- L20 _public function_ `virtual ~IMdlFileImporter()`
- L22 _public prototype_ `virtual bool OpenFile(const FString& InFileName, const UMDLImporterOptions& InImporterOptions) = 0;`
- L23 _public prototype_ `virtual int GetMaterialCountInFile() = 0;`
- L24 _public prototype_ `virtual bool ImportMaterials(UObject* ParentPackage, EObjectFlags Flags, FProgressFunc ProgressFunc = nullptr) = 0;`
- L25 _public prototype_ `virtual TMap<FString, UMaterialInterface*> GetCreatedMaterials() = 0;`
- L26 _public prototype_ `virtual bool Reimport(const FString& InFileName, const UMDLImporterOptions& InImporterOptions, UMaterialInterface* OutMaterial) = 0;`
- L28 _public prototype_ `virtual const TArray<MDLImporterLogging::FLogMessage> GetLogMessages() = 0;`
- L30 _public prototype_ `static TUniquePtr<IMdlFileImporter> Create();`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/UI/MDLOptionsWindow.h` (Private)


#### class `SMDLOptionsWindow`  
`class SMDLOptionsWindow : public SCompoundWidget`  
_L7-40_
- inherits: `SCompoundWidget`
- L10 _public function_ `SLATE_BEGIN_ARGS(SMDLOptionsWindow)`
- L12 _public prototype_ `SLATE_ARGUMENT(UObject*, ImportOptions);`
- L13 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow);`
- L14 _public prototype_ `SLATE_ARGUMENT(FText, FileNameText);`
- L15 _public prototype_ `SLATE_ARGUMENT(FText, FilePathText);`
- L16 _public prototype_ `SLATE_ARGUMENT(FText, PackagePathText);`
- L17 _public prototype_ `SLATE_ARGUMENT(int, MaterialCount);`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L23 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L27 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L29 _public prototype_ `bool ShouldImport() const;`
- L32 _private prototype_ `FReply OnImport();`
- L33 _private prototype_ `FReply OnCancel();`
- L34 _private prototype_ `FReply OnHelp(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);`
- L37 _private member_ `UObject* ImportOptions;`
- L38 _private member_ `TWeakPtr<SWindow> Window;`
- L39 _private member_ `bool bShouldImport;`
- L42 _function_ `inline bool SMDLOptionsWindow::ShouldImport() const`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/common/Logging.h` (Private)


#### enum `MDLImporterLogging::EMessageSeverity`  
`enum class EMessageSeverity`  
_L12-16_
- L14 _public enumerator_ `Warning`
- L15 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMDLImporter, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMDLImporter, Log, All);`
- L10 _namespace_ `namespace MDLImporterLogging`
- L17 _typedef_ `using FLogMessage = TTuple<EMessageSeverity, FString>;` (scope `MDLImporterLogging`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/common/TextureProperty.h` (Private)


#### enum `Common::ETextureMode`  
`enum class ETextureMode`  
_L11-21_
- L13 _public enumerator_ `Color`
- L14 _public enumerator_ `ColorLinear`
- L15 _public enumerator_ `Grayscale`
- L16 _public enumerator_ `Normal`
- L17 _public enumerator_ `NormalGreenInv`
- L18 _public enumerator_ `Displace`
- L19 _public enumerator_ `Bump`
- L20 _public enumerator_ `Other`

#### struct `Common::FTextureProperty`  
`struct FTextureProperty`  
_L23-43_
- L27 _public member_ `FString Path;` — @note Can be a texture name or file path(i.e. also contains extension and it's disk path), if it's a file path then texture will imported from a file otherwise from texture source/data.
- L28 _public member_ `FImage* Source;`
- L30 _public member_ `ETextureMode Mode;`
- L31 _public member_ `TextureMipGenSettings MipGenSettings;`
- L32 _public member_ `TextureCompressionSettings CompressionSettings;`
- L33 _public member_ `TextureFilter Filter;`
- L34 _public member_ `TextureGroup LODGroup;`
- L35 _public member_ `TextureAddress Address;`
- L36 _public member_ `bool bIsSRGB;`
- L37 _public member_ `bool bFlipGreenChannel;`
- L38 _public member_ `bool bCompressionNoAlpha;`
- L40 _public prototype_ `FTextureProperty();`
- L42 _public prototype_ `void SetTextureMode(ETextureMode Mode);`
- L45 _function_ `inline FTextureProperty::FTextureProperty() : bIsSRGB(false) , bFlipGreenChannel(false) , bCompressionNoAlpha(true)`
- L58 _function_ `inline void FTextureProperty::SetTextureMode(ETextureMode InMode)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Common`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/common/TextureSource.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Common`
- L15 _function_ `FORCEINLINE bool IsValueInRange(float Value)` (scope `Common`)
- L21 _function_ `inline FImage* CreateTextureSource(const float* InData, int InWidth, int InHeight, int InChannels, bool bFlipY)` (scope `Common`) — Converts a float texture to a corresponding texture source.

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/common/Utility.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Common`
- L10 _prototype_ `template <typename T> T Saturate(T Value);` (scope `Common`)
- L12 _prototype_ `int HighestPowerofTwo(int Value);` (scope `Common`)
- L15 _prototype_ `void RemapNormal(int Size, float* Buffer);` (scope `Common`) — Convert normal values from the interval [-1.0, 1.0] to [0.0, 1.0].
- L17 _prototype_ `void RemapNormalFlipGreen(int Size, float* Buffer);` (scope `Common`) — @note Also flips green channel.
- L22 _function_ `template <typename T> FORCEINLINE T Saturate(T Value)` (scope `Common`)
- L27 _function_ `FORCEINLINE int HighestPowerofTwo(int Value)` (scope `Common`)
- L33 _function_ `inline void RemapNormal(int Size, float* Buffer)` (scope `Common`)
- L45 _function_ `inline void RemapNormalFlipGreen(int Size, float* Buffer)` (scope `Common`)
- L57 _prototype_ `void ImageResize(int32 SrcWidth, int32 SrcHeight, const TArray<FColor> &SrcData, int32 DstWidth, int32 DstHeight, TArray<FColor> &DstData, bool bLinearSpace);` (scope `Common`)
- L59 _prototype_ `void ImageResize(int32 SrcWidth, int32 SrcHeight, int32 SrcChannels, const float* SrcData, int32 DstWidth, int32 DstHeight, float* DstData);` (scope `Common`)
- L61 _prototype_ `void ImageResize(int32 SrcWidth, int32 SrcHeight, int32 SrcChannels, const uint8* SrcData, int32 DstWidth, int32 DstHeight, uint8* DstData, bool bLinearSpace);` (scope `Common`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/BaseExpressionFactory.h` (Private)


#### class `Generator::FBaseExpressionFactory`  
`class FBaseExpressionFactory`  
_L24-45_
- L27 _public prototype_ `FBaseExpressionFactory();`
- L29 _public prototype_ `void SetCurrentMaterial(const mi::neuraylib::IMaterial_definition& MDLMaterialDefinition, const mi::neuraylib::ICompiled_material& MDLMaterial, UMaterial& Material);`
- L32 _public prototype_ `TArray<MDLImporterLogging::FLogMessage> GetLogMessages();`
- L34 _public prototype_ `void Cleanup();`
- L36 _public prototype_ `void SetProcessingNormapMap(bool ProcessingNormapMap);`
- L39 _protected member_ `UMaterial* CurrentMaterial;`
- L40 _protected member_ `const mi::neuraylib::ICompiled_material* CurrentMDLMaterial;`
- L41 _protected member_ `const mi::neuraylib::IMaterial_definition* CurrentMDLMaterialDefinition;`
- L42 _protected member_ `bool bProcessingNormapMap;`
- L44 _protected member_ `mutable TArray<MDLImporterLogging::FLogMessage> LogMessages;`
- L47 _function_ `inline FBaseExpressionFactory::FBaseExpressionFactory() : CurrentMaterial(nullptr) , CurrentMDLMaterial(nullptr) , CurrentMDLMaterialDefinition(nullptr) , bProcessingNormapMap(false)`
- L55 _function_ `inline void FBaseExpressionFactory::SetCurrentMaterial(const mi::neuraylib::IMaterial_definition& MDLMaterialDefinition, const mi::neuraylib::ICompiled_material& MDLMaterial, UMaterial& Material)`
- L63 _function_ `inline TArray<MDLImporterLogging::FLogMessage> FBaseExpressionFactory::GetLogMessages()`
- L70 _function_ `inline void FBaseExpressionFactory::Cleanup()`
- L77 _function_ `inline void FBaseExpressionFactory::SetProcessingNormapMap(bool bInProcessingNormapMap)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace mi`
- L11 _namespace_ `namespace neuraylib` (scope `mi`)
- L17 _namespace_ `namespace Mdl`
- L22 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/ConstantExpressionFactory.h` (Private)


#### class `Generator::FConstantExpressionFactory`  
`class FConstantExpressionFactory : public FBaseExpressionFactory`  
_L29-52_
- inherits: `FBaseExpressionFactory`
- L32 _public prototype_ `FConstantExpressionFactory();`
- L34 _public prototype_ `void SetTextureFactory(FMaterialTextureFactory* Factory);`
- L36 _public prototype_ `FMaterialExpressionConnectionList CreateExpression(mi::neuraylib::ITransaction& Transaction, const mi::neuraylib::IValue& MDLConstant);`
- L38 _public prototype_ `void CleanupMaterialExpressions();`
- L41 _private member_ `FMaterialTextureFactory* TextureFactory;`
- L43 _private function_ `FMaterialExpressionHandle AddExpression(UMaterialExpression* Expression)`
- L49 _private prototype_ `template<typename T> FMaterialExpressionConnectionList AddNewMaterialExpressionConstantHelper(const mi::base::Handle<const mi::neuraylib::IValue_vector>& Value);`
- L51 _private member_ `TArray<FMaterialExpressionHandle> Expressions;`
- L54 _function_ `inline void FConstantExpressionFactory::SetTextureFactory(FMaterialTextureFactory* Factory)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace mi`
- L12 _namespace_ `namespace base` (scope `mi`)
- L13 _namespace_ `namespace mi`
- L13 _namespace_ `namespace neuraylib` (scope `mi`)
- L16 _namespace_ `namespace mi`
- L18 _namespace_ `namespace neuraylib` (scope `mi`)
- L25 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/FunctionGenerator.h` (Private)


#### class `Generator::FBaseFunctionGenerator`  
`class FBaseFunctionGenerator`  
_L63-6049_
- L135 _public function_ `virtual ~FBaseFunctionGenerator()`
- L137 _public prototype_ `virtual UMaterialFunction* LoadFunction(const FString& AssetName) = 0;`
- L138 _public prototype_ `virtual UMaterialFunction* LoadFunction(const FString& AssetPath, const FString& AssetName) = 0;`
- L140 _public function_ `void BaseAbbeNumberIOR(UMaterialFunction* Function, int32 ArraySize)`
- L156 _public function_ `void MathAverage(UMaterialFunction* Function, int32 ArraySize)`
- L173 _public function_ `void ImporterPerlinNoise(UMaterialFunction* Function, int32 ArraySize)`
- L184 _public function_ `void ImporterSummedPerlinNoise(UMaterialFunction* Function, int32 ArraySize)`
- L266 _public function_ `void BaseAnisotropyConversion(UMaterialFunction* Function, int32 ArraySize)`
- L324 _public function_ `void BaseArchitecturalGlossToRough(UMaterialFunction* Function, int32 ArraySize)`
- L347 _public function_ `void BaseBlendColorLayers(UMaterialFunction* Function, int32 ArraySize)`
- L405 _public function_ `void BaseCheckerBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L465 _public function_ `void BaseCheckerTexture(UMaterialFunction* Function, int32 ArraySize)`
- L503 _public function_ `void BaseCoordinateProjection(UMaterialFunction* Function, int32 ArraySize)`
- L648 _public function_ `void BaseCoordinateSource(UMaterialFunction* Function, int32 ArraySize)`
- L702 _public function_ `void BaseFileBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L971 _public function_ `void BaseFileTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1121 _public function_ `void BaseFlakeNoiseBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1194 _public function_ `void BaseFlakeNoiseTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1252 _public function_ `void BaseFlowNoiseBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1347 _public function_ `void BaseFlowNoiseTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1401 _public function_ `void BaseGlossToRough(UMaterialFunction* Function, int32 ArraySize)`
- L1412 _public function_ `void BasePerlinNoiseBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1527 _public function_ `void BasePerlinNoiseTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1591 _public function_ `void BaseRotationTranslationScale(UMaterialFunction* Function, int32 ArraySize)`
- L1662 _public function_ `void BaseSellmeierCoefficientsIOR(UMaterialFunction* Function, int32 ArraySize)`
- L1701 _public function_ `void BaseTangentSpaceNormalTexture(UMaterialFunction* Function, int32 ArraySize)`
- L1881 _public function_ `void BaseTextureCoordinateInfo(UMaterialFunction* Function, int32 ArraySize)`
- L1929 _public function_ `void BaseTileBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L2026 _public function_ `void BaseTransformCoordinate(UMaterialFunction* Function, int32 ArraySize)`
- L2065 _public function_ `void BaseVolumeCoefficient(UMaterialFunction* Function, int32 ArraySize)`
- L2086 _public function_ `void BaseWorleyNoiseBumpTexture(UMaterialFunction* Function, int32 ArraySize)`
- L2201 _public function_ `void BaseWorleyNoiseTexture(UMaterialFunction* Function, int32 ArraySize)`
- L2265 _public function_ `void DFAnisotropicVDF(UMaterialFunction* Function, int32 ArraySize)`
- L2284 _public function_ `void DFBackscatteringGlossyReflectionBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2315 _public function_ `void DFCustomCurveLayer(UMaterialFunction* Function, int32 ArraySize)`
- L2355 _public function_ `void DFDiffuseEDF(UMaterialFunction* Function, int32 ArraySize)`
- L2366 _public function_ `void DFDiffuseReflectionBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2386 _public function_ `void DFDiffuseTransmissionBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2404 _public function_ `void DFDirectionalFactor(UMaterialFunction* Function, int32 ArraySize)`
- L2431 _public function_ `void DFFresnelLayer(UMaterialFunction* Function, int32 ArraySize)`
- L2473 _public function_ `void DFLightProfileMaximum(UMaterialFunction* Function, int32 ArraySize)`
- L2487 _public function_ `void DFLightProfilePower(UMaterialFunction* Function, int32 ArraySize)`
- L2501 _public function_ `void DFMeasuredBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2530 _public function_ `void DFMeasuredEDF(UMaterialFunction* Function, int32 ArraySize)`
- L2561 _public function_ `void DFMeasuredCurveFactor(UMaterialFunction* Function, int32 ArraySize)`
- L2623 _public function_ `void DFMicrofacetBeckmannSmithBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2652 _public function_ `void DFMicrofacetBeckmannVCavitiesBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2681 _public function_ `void DFMicrofacetGGXSmithBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2710 _public function_ `void DFMicrofacetGGXVCavitiesBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2739 _public function_ `void DFNormalizedMix(UMaterialFunction* Function, int32 ArraySize)`
- L2787 _public function_ `void DFSimpleGlossyBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2822 _public function_ `void DFSpecularBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2851 _public function_ `void DFSpotEDF(UMaterialFunction* Function, int32 ArraySize)`
- L2877 _public function_ `void DFThinFilm(UMaterialFunction* Function, int32 ArraySize)`
- L2939 _public function_ `void DFTint(UMaterialFunction* Function, int32 ArraySize)`
- L2959 _public function_ `void DFWardGeislerMoroderBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L2986 _public function_ `void DFWeightedLayer(UMaterialFunction* Function, int32 ArraySize)`
- L3016 _public function_ `void MathCosFloat(UMaterialFunction* Function, int32 ArraySize)`
- L3028 _public function_ `void MathCosFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L3046 _public function_ `void MathLogFloat(UMaterialFunction* Function, int32 ArraySize)`
- L3058 _public function_ `void MathLogFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L3078 _public function_ `void MathLog10Float(UMaterialFunction* Function, int32 ArraySize)`
- L3090 _public function_ `void MathLog10Float3(UMaterialFunction* Function, int32 ArraySize)`
- L3110 _public function_ `void MathLog2Float(UMaterialFunction* Function, int32 ArraySize)`
- L3122 _public function_ `void MathLog2Float3(UMaterialFunction* Function, int32 ArraySize)`
- L3140 _public function_ `void MathLuminance(UMaterialFunction* Function, int32 ArraySize)`
- L3152 _public function_ `void MathMaxValue(UMaterialFunction* Function, int32 ArraySize)`
- L3167 _public function_ `void MathMinValue(UMaterialFunction* Function, int32 ArraySize)`
- L3182 _public function_ `void MathMultiplyFloat4x4Float4(UMaterialFunction* Function, int32 ArraySize)`
- L3224 _public function_ `void MathMultiplyFloat4x4Float4x4(UMaterialFunction* Function, int32 ArraySize)`
- L3288 _public function_ `void MathSinFloat(UMaterialFunction* Function, int32 ArraySize)`
- L3300 _public function_ `void MathSinFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L3318 _public function_ `void MathSum(UMaterialFunction* Function, int32 ArraySize)`
- L3333 _public function_ `void StateAnimationTime(UMaterialFunction* Function, int32 ArraySize)`
- L3343 _public function_ `void StateDirection(UMaterialFunction* Function, int32 ArraySize)`
- L3357 _public function_ `void StateGeometryNormal(UMaterialFunction* Function, int32 ArraySize)`
- L3365 _public function_ `void StateGeometryTangentU(UMaterialFunction* Function, int32 ArraySize)`
- L3373 _public function_ `void StateGeometryTangentV(UMaterialFunction* Function, int32 ArraySize)`
- L3382 _public function_ `void StateMetersPerSceneUnit(UMaterialFunction* Function, int32 ArraySize)`
- L3390 _public function_ `void StateNormal(UMaterialFunction* Function, int32 ArraySize)`
- L3406 _public function_ `void StateObjectId(UMaterialFunction* Function, int32 ArraySize)`
- L3414 _public function_ `void StatePosition(UMaterialFunction* Function, int32 ArraySize)`
- L3424 _public function_ `void StateSceneUnitsPerMeter(UMaterialFunction* Function, int32 ArraySize)`
- L3432 _public function_ `void StateTangentSpace(UMaterialFunction* Function, int32 ArraySize)`
- L3453 _public function_ `void StateTextureCoordinate(UMaterialFunction* Function, int32 ArraySize)`
- L3476 _public function_ `void StateTextureSpaceMax(UMaterialFunction* Function, int32 ArraySize)`
- L3484 _public function_ `void StateTextureTangentU(UMaterialFunction* Function, int32 ArraySize)`
- L3494 _public function_ `void StateTextureTangentV(UMaterialFunction* Function, int32 ArraySize)`
- L3504 _public function_ `void StateTransformPoint(UMaterialFunction* Function, int32 ArraySize)`
- L3532 _public function_ `void StateTransformVector(UMaterialFunction* Function, int32 ArraySize)`
- L3567 _public function_ `void TexLookupFloat(UMaterialFunction* Function, int32 ArraySize)`
- L3599 _public function_ `void TexLookupFloat2(UMaterialFunction* Function, int32 ArraySize)`
- L3632 _public function_ `void TexLookupFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L3664 _public function_ `void TexLookupFloat4(UMaterialFunction* Function, int32 ArraySize)`
- L3696 _public function_ `void ImporterAddDetailNormal(UMaterialFunction* Function, int32 ArraySize)`
- L3730 _public function_ `void ImporterApplyNoiseModifications(UMaterialFunction* Function, int32 ArraySize)`
- L3779 _public function_ `void ImporterBlendClearCoat(UMaterialFunction* Function, int32 ArraySize)`
- L3838 _public function_ `void ImporterBlendColors(UMaterialFunction* Function, int32 ArraySize)`
- L3980 _public function_ `void ImporterCalculateHue(UMaterialFunction* Function, int32 ArraySize)`
- L4017 _public function_ `void ImporterCalculateSaturation(UMaterialFunction* Function, int32 ArraySize)`
- L4033 _public function_ `void ImporterComputeCubicTransform(UMaterialFunction* Function, int32 ArraySize)`
- L4115 _public function_ `void ImporterComputeCylindricTransform(UMaterialFunction* Function, int32 ArraySize)`
- L4236 _public function_ `void ImporterComputeSphericProjection(UMaterialFunction* Function, int32 ArraySize)`
- L4278 _public function_ `void ImporterComputeSphericTransform(UMaterialFunction* Function, int32 ArraySize)`
- L4351 _public function_ `void ImporterComputeTangents(UMaterialFunction* Function, int32 ArraySize)`
- L4421 _public function_ `void ImporterComputeTangentsTransformed(UMaterialFunction* Function, int32 ArraySize)`
- L4517 _public function_ `void ImporterEvalChecker(UMaterialFunction* Function, int32 ArraySize)`
- L4580 _public function_ `void ImporterEvalTileFunction(UMaterialFunction* Function, int32 ArraySize)`
- L4751 _public function_ `void ImporterFlowNoise(UMaterialFunction* Function, int32 ArraySize)`
- L4820 _public function_ `void ImporterGradFlow(UMaterialFunction* Function, int32 ArraySize)`
- L4848 _public function_ `void ImporterHSVToRGB(UMaterialFunction* Function, int32 ArraySize)`
- L4881 _public function_ `void ImporterMonoMode(UMaterialFunction* Function, int32 ArraySize)`
- L4904 _public function_ `void ImporterMiNoise(UMaterialFunction* Function, int32 ArraySize)`
- L4918 _public function_ `void ImporterPermuteFlow(UMaterialFunction* Function, int32 ArraySize)`
- L4929 _public function_ `void ImporterRefract(UMaterialFunction* Function, int32 ArraySize)`
- L4957 _public function_ `void ImporterSelectBSDF(UMaterialFunction* Function, int32 ArraySize)`
- L5001 _public function_ `void ImporterSetClipMask(UMaterialFunction* Function, int32 ArraySize)`
- L5043 _public function_ `void ImporterSetRefraction(UMaterialFunction* Function, int32 ArraySize)`
- L5085 _public function_ `void ImporterSetSubsurfaceColor(UMaterialFunction* Function, int32 ArraySize)`
- L5125 _public function_ `void ImporterSummedFlowNoise(UMaterialFunction* Function, int32 ArraySize)`
- L5271 _public function_ `void ImporterTexremapu1(UMaterialFunction* Function, int32 ArraySize)`
- L5301 _public function_ `void ImporterTexremapu2(UMaterialFunction* Function, int32 ArraySize)`
- L5332 _public function_ `void ImporterTextureSample(UMaterialFunction* Function, int32 ArraySize)`
- L5377 _public function_ `void ImporterWorldAlignedTextureFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L5407 _public function_ `void ImporterWorldAlignedTextureFloat4(UMaterialFunction* Function, int32 ArraySize)`
- L5442 _public function_ `void ImporterWorleyNoise(UMaterialFunction* Function, int32 ArraySize)`
- L5465 _public function_ `void ImporterWorleyNoiseExt(UMaterialFunction* Function, int32 ArraySize)`
- L5520 _public function_ `void DistillingSupportAddDetailNormal(UMaterialFunction* Function, int32 ArraySize)`
- L5548 _public function_ `void DistillingSupportAverageFloatFloatFloatFloat(UMaterialFunction* Function, int32 ArraySize)`
- L5577 _public function_ `void DistillingSupportAverageFloatFloatFloatFloatFloatFloat(UMaterialFunction* Function, int32 ArraySize)`
- L5604 _public function_ `void DistillingSupportAverageFloatColorFloatColor(UMaterialFunction* Function, int32 ArraySize)`
- L5635 _public function_ `void DistillingSupportAverageFloatColorFloatColorFloatColor(UMaterialFunction* Function, int32 ArraySize)`
- L5666 _public function_ `void DistillingSupportCombineAnisotropicRoughness(UMaterialFunction* Function, int32 ArraySize)`
- L5680 _public function_ `void DistillingSupportAffineNormalSumFloatFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L5700 _public function_ `void DistillingSupportAffineNormalSumFloatFloat3FloatFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L5728 _public function_ `void DistillingSupportAffineNormalSumFloatFloat3FloatFloat3FloatFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L5761 _public function_ `void DistillingSupportCombineNormals(UMaterialFunction* Function, int32 ArraySize)`
- L5797 _public function_ `void DistillingSupportDirectionalColoring(UMaterialFunction* Function, int32 ArraySize)`
- L5818 _public function_ `void DistillingSupportDirectionalWeighting(UMaterialFunction* Function, int32 ArraySize)`
- L5839 _public function_ `void DistillingSupportPartNormalized(UMaterialFunction* Function, int32 ArraySize)`
- L5857 _public function_ `void DistillingSupportReflFromIORFloat3(UMaterialFunction* Function, int32 ArraySize)`
- L5872 _public function_ `void DistillingSupportReflFromIORFloat(UMaterialFunction* Function, int32 ArraySize)`
- L5887 _public function_ `void UnrealPixelNormalWS(UMaterialFunction* Function, int32 ArraySize)`
- L5893 _public function_ `void UnrealVertexNormalWS(UMaterialFunction* Function, int32 ArraySize)`
- L5899 _public function_ `void UnrealFresnel(UMaterialFunction* Function, int32 ArraySize)`
- L5910 _public function_ `void UnrealCameraVector(UMaterialFunction* Function, int32 ArraySize)`
- L5916 _public function_ `void UnrealTransformTangentToWorld(UMaterialFunction* Function, int32 ArraySize)`
- L5925 _public function_ `void UnrealTransformWorldToTangent(UMaterialFunction* Function, int32 ArraySize)`
- L5934 _public function_ `void UnrealTangentSpaceNormal(UMaterialFunction* Function, int32 ArraySize)`
- L5964 _public function_ `void UnrealEmissiveMultiplier(UMaterialFunction* Function, int32 ArraySize)`
- L5970 _public function_ `void UnrealSubsurfaceWeight(UMaterialFunction* Function, int32 ArraySize)`
- L5975 _public function_ `void UnrealSubsurfaceColor(UMaterialFunction* Function, int32 ArraySize)`
- L5981 _public function_ `void UnrealSubsurfaceOpacity(UMaterialFunction* Function, int32 ArraySize)`
- L5987 _public function_ `void UnrealOpacityWeight(UMaterialFunction* Function, int32 ArraySize)`
- L5994 _public function_ `void UnrealTextureLookup(UMaterialFunction* Function, int32 ArraySize)`
- L6002 _public function_ `void UnrealTranslucentGetTint(UMaterialFunction* Function, int32 ArraySize)`
- L6011 _private function_ `static TPair<UMaterialExpression*, UMaterialExpression*> MixAttributesRecursive(UMaterialFunction* Function, UMaterialFunction* MatLayerBlend_Standard, const TArray<UMaterialExpressionClamp*>& Weights, const TArray<UMaterialExpressionFunctionInput*>& Components, int32 Begin, int32 End)`
- L6040 _private function_ `static TPair<UMaterialExpressionClamp*, UMaterialExpression*> MixAttributes(UMaterialFunction* Function, UMaterialFunction* MatLayerBlend_Standard, const TArray<UMaterialExpressionClamp*>& Weights, const TArray<UMaterialExpressionFunctionInput*>& Components)`

#### enum `Generator::FBaseFunctionGenerator::EColorLayerMode`  
`enum class EColorLayerMode`  
_L65-95_
- L67 _public enumerator_ `Blend`
- L68 _public enumerator_ `Add`
- L69 _public enumerator_ `Multiply`
- L70 _public enumerator_ `Screen`
- L71 _public enumerator_ `Overlay`
- L72 _public enumerator_ `Brightness`
- L73 _public enumerator_ `Color`
- L74 _public enumerator_ `Exclusion`
- L75 _public enumerator_ `Average`
- L76 _public enumerator_ `Lighten`
- L77 _public enumerator_ `Darken`
- L78 _public enumerator_ `Sub`
- L79 _public enumerator_ `Negation`
- L80 _public enumerator_ `Difference`
- L81 _public enumerator_ `Softlight`
- L82 _public enumerator_ `ColorDodge`
- L83 _public enumerator_ `Reflect`
- L84 _public enumerator_ `ColorBurn`
- L85 _public enumerator_ `Phoenix`
- L86 _public enumerator_ `Hardlight`
- L87 _public enumerator_ `Pinlight`
- L88 _public enumerator_ `HardMix`
- L89 _public enumerator_ `LinearDodge`
- L90 _public enumerator_ `LinearBurn`
- L91 _public enumerator_ `Spotlight`
- L92 _public enumerator_ `SpotlightBlend`
- L93 _public enumerator_ `Hue`
- L94 _public enumerator_ `Saturation`

#### enum `Generator::FBaseFunctionGenerator::ECoordinateSpace`  
`enum class ECoordinateSpace`  
_L97-102_
- L99 _public enumerator_ `Internal`
- L100 _public enumerator_ `Object`
- L101 _public enumerator_ `World`

#### enum `Generator::FBaseFunctionGenerator::EMonoMode`  
`enum class EMonoMode`  
_L104-110_
- L106 _public enumerator_ `Alpha`
- L107 _public enumerator_ `Average`
- L108 _public enumerator_ `Luminance`
- L109 _public enumerator_ `Maximum`

#### enum `Generator::FBaseFunctionGenerator::EScatterMode`  
`enum class EScatterMode`  
_L112-117_
- L114 _public enumerator_ `Reflect`
- L115 _public enumerator_ `Transmit`
- L116 _public enumerator_ `ReflectTransmit`

#### enum `Generator::FBaseFunctionGenerator::ETextureCoordinateSystem`  
`enum class ETextureCoordinateSystem`  
_L119-124_
- L121 _public enumerator_ `UVW`
- L122 _public enumerator_ `World`
- L123 _public enumerator_ `Object`

#### enum `Generator::FBaseFunctionGenerator::EWrapMode`  
`enum EWrapMode`  
_L126-132_
- L128 _public enumerator_ `wrap_clamp`
- L129 _public enumerator_ `wrap_repeat`
- L130 _public enumerator_ `wrap_mirrored_repeat`
- L131 _public enumerator_ `wrap_clip`

#### enum `Generator::FBaseFunctionGenerator::BaseCoordinateProjection::projection_mode`  
`enum projection_mode`  
_L517-529_
- L519 _public enumerator_ `projection_invalid`
- L520 _public enumerator_ `projection_cubic`
- L521 _public enumerator_ `projection_spherical`
- L522 _public enumerator_ `projection_cylindrical`
- L523 _public enumerator_ `projection_infinite_cylindrical`
- L524 _public enumerator_ `projection_planar`
- L525 _public enumerator_ `projection_spherical_normalized`
- L526 _public enumerator_ `projection_cylindrical_normalized`
- L527 _public enumerator_ `projection_infinite_cylindrical_normalized`
- L528 _public enumerator_ `projection_tri_planar`

#### Free symbols / members of external scopes

- L61 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/FunctionLoader.h` (Private)


#### enum `Generator::ECommonFunction`  
`enum class ECommonFunction`  
_L14-31_
- L16 _public enumerator_ `MakeFloat2 = 0`
- L17 _public enumerator_ `MakeFloat3`
- L18 _public enumerator_ `MakeFloat4`
- L19 _public enumerator_ `DitherTemporalAA`
- L20 _public enumerator_ `AdjustNormal`
- L21 _public enumerator_ `AngularDirection`
- L22 _public enumerator_ `ColorMap`
- L23 _public enumerator_ `GrayscaleMap`
- L24 _public enumerator_ `NormalMap`
- L25 _public enumerator_ `CarColorTable`
- L26 _public enumerator_ `CarFlakes`
- L27 _public enumerator_ `EstimateObjectThickness`
- L28 _public enumerator_ `VolumeAbsorptionColor`
- L29 _public enumerator_ `TranslucentOpacity`
- L30 _public enumerator_ `Count`

#### class `Generator::FFunctionLoader`  
`class FFunctionLoader : FNoncopyable, FGCObject`  
_L33-71_
- inherits: `FNoncopyable,FGCObject`
- L36 _public prototype_ `FFunctionLoader();`
- L37 _public prototype_ `~FFunctionLoader();`
- L39 _public prototype_ `UMaterialFunction* Load(const FString& AssetName, int32 ArraySize = 0);`
- L40 _public prototype_ `UMaterialFunction* Load(const FString& AssetPath, const FString& AssetName, int32 ArraySize = 0);`
- L41 _public prototype_ `UMaterialFunction& Get(ECommonFunction Function);`
- L43 _public prototype_ `void SetAssetPath(const FString& FunctionsAssetPath);`
- L44 _public function_ `void SetObjectFlags(EObjectFlags InObjectFlags)`
- L47 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L48 _public function_ `virtual FString GetReferencerName() const override`
- L53 _private prototype_ `int32 GetVersion(const FString& AssetName) const;`
- L54 _private prototype_ `UMaterialFunction* Generate(const FString& AssetPath, const FString& AssetName, int32 ArraySize);`
- L63 _private member_ `UMaterialFunctionFactoryNew* FunctionFactory;`
- L64 _private member_ `TUniquePtr<FFunctionGenerator> FunctionGenerator;`
- L65 _private member_ `TMap<FString, FGenerationData> FunctionGenerateMap;`
- L66 _private member_ `TMap<FString, FGenerationData> NoInlineFunctionGenerateMap;`
- L67 _private member_ `TMap<FString, TObjectPtr<UMaterialFunction>> LoadedFunctions;`
- L68 _private member_ `TArray<TObjectPtr<UMaterialFunction>> CommonFunctions;`
- L69 _private member_ `FString FunctionsAssetPath;`
- L70 _private member_ `EObjectFlags ObjectFlags;`
- L73 _function_ `inline UMaterialFunction& FFunctionLoader::Get(ECommonFunction Function)`
- L80 _function_ `inline UMaterialFunction* FFunctionLoader::Load(const FString& AssetName, int32 ArraySize)`
- L85 _function_ `inline void FFunctionLoader::SetAssetPath(const FString& InFunctionsAssetPath)`

#### struct `Generator::FFunctionLoader::FGenerationData`  
`struct FGenerationData`  
_L57-61_
- L59 _public member_ `void (FFunctionGenerator::*Generator)(UMaterialFunction*, int32 ArraySize);`
- L60 _public member_ `int32 Version;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/MaterialExpressionConnection.h` (Private)


#### enum `Generator::EConnectionType`  
`enum EConnectionType`  
_L11-21_
- L13 _public enumerator_ `Expression`
- L14 _public enumerator_ `Boolean`
- L15 _public enumerator_ `Float`
- L16 _public enumerator_ `Float2`
- L17 _public enumerator_ `Float3`
- L18 _public enumerator_ `Float4`
- L19 _public enumerator_ `Texture`
- L20 _public enumerator_ `TextureSelection`

#### struct `Generator::FSharedMaterialExpression`  
`struct FSharedMaterialExpression: FNoncopyable`  
_L24-38_
- inherits: `FNoncopyable`
- desc: Controls usage count of an expression
- L26 _public member_ `UMaterialExpression* Expression;`
- L27 _public member_ `mutable int32 UserCount;`
- L28 _public function_ `FSharedMaterialExpression(UMaterialExpression* InExpression): Expression(InExpression), UserCount(0)`
- L30 _public function_ `void DestroyExpression()`

#### struct `Generator::FMaterialExpressionHandle`  
`struct FMaterialExpressionHandle`  
_L41-74_
- L43 _public member_ `TSharedPtr<FSharedMaterialExpression> Expression;`
- L45 _public function_ `FMaterialExpressionHandle()`
- L49 _public function_ `FMaterialExpressionHandle(UMaterialExpression* InExpression)`
- L54 _public function_ `UMaterialExpression* GetMaterialExpression() const`
- L59 _public function_ `void AddUser() const`
- L67 _public function_ `void DestroyExpression()`

#### struct `Generator::FMaterialExpressionConnection`  
`struct FMaterialExpressionConnection`  
_L76-227_
- L95 _public prototype_ `FMaterialExpressionConnection();`
- L96 _public prototype_ `FMaterialExpressionConnection(UMaterialExpression* Expression);`
- L97 _public prototype_ `FMaterialExpressionConnection(FMaterialExpressionHandle ExpressionHandle, int32 OutputIndex = 0, bool bIsDefault = false);`
- L98 _public prototype_ `FMaterialExpressionConnection(bool bValue);`
- L99 _public prototype_ `FMaterialExpressionConnection(int Value);`
- L100 _public prototype_ `FMaterialExpressionConnection(float Value);`
- L101 _public prototype_ `FMaterialExpressionConnection(float Value0, float Value1);`
- L102 _public prototype_ `FMaterialExpressionConnection(float Value0, float Value1, float Value2);`
- L103 _public prototype_ `FMaterialExpressionConnection(float Value0, float Value1, float Value2, float Value3);`
- L104 _public prototype_ `FMaterialExpressionConnection(double Value);`
- L105 _public prototype_ `FMaterialExpressionConnection(UTexture* Texture);`
- L106 _public prototype_ `FMaterialExpressionConnection(const FData& Value, const FData& True, const FData& False);`
- L108 _public prototype_ `bool operator!=(const FMaterialExpressionConnection& rhs);`
- L110 _public function_ `EConnectionType GetConnectionType() const`
- L116 _public function_ `UMaterialExpression* GetMaterialExpression() const` — Get expression without incrementing usage count
- L121 _public function_ `bool HasExpression() const`
- L126 _public function_ `bool IsExpressionWithoutExpression() const`
- L132 _public function_ `template<typename ExpressionType> bool IsExpressionA() const`
- L137 _public function_ `int32 GetExpressionOutputIndex() const`
- L142 _public function_ `FString GetExpressionName() const`
- L147 _public function_ `bool IsExpressionDefault() const`
- L152 _public function_ `void SetExpressionDefault()`
- L157 _public function_ `void DestroyExpression()`
- L163 _public function_ `UMaterialExpression* GetExpressionUnused() const` — Get expression but don't increment usage count
- L169 _public function_ `UMaterialExpression* GetExpressionAndUse() const` — Get expression AND increment usage count
- L177 _public function_ `UMaterialExpression* GetExpressionAndMaybeUse() const` — Get expression AND increment usage count(used in placed where it's unclear whether it's used)
- L184 _public function_ `FData GetExpressionData() const`
- L189 _public function_ `bool GetBoolValue() const`
- L194 _public function_ `const float* GetVectorValue() const`
- L199 _public function_ `FData* GetTextureSelectionData()`
- L204 _public function_ `UTexture* GetTextureAndUse() const`
- L210 _public function_ `UTexture* GetTextureUnused() const`
- L216 _private member_ `EConnectionType ConnectionType;`
- L218 _private member_ `FData ExpressionData;`
- L219 _private member_ `FData TextureSelectionData[3];`
- L226 _private member_ `mutable bool bIsUsed = false;`
- L340 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection() : ConnectionType(EConnectionType::Expression) , ExpressionData(nullptr, 0, true)`
- L346 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(UMaterialExpression* Expression) : ConnectionType(EConnectionType::Expression) , ExpressionData(Expression, 0, false)`
- L352 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(FMaterialExpressionHandle ExpressionHandle, int32 OutputIndex , bool bIsDefault ) : ConnectionType(EConnectionType::Expression) , ExpressionData(ExpressionHandle, OutputIndex, bIsDefault)`
- L360 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(bool bValue) : ConnectionType(EConnectionType::Boolean) , bValue(bValue)`
- L366 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(int Value) : ConnectionType(EConnectionType::Float) , Values`
- L372 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(float Value) : ConnectionType(EConnectionType::Float) , Values`
- L378 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(float Value0, float Value1) : ConnectionType(EConnectionType::Float2) , Values`
- L384 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(float Value0, float Value1, float Value2) : ConnectionType(EConnectionType::Float3) , Values`
- L390 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(float Value0, float Value1, float Value2, float Value3) : ConnectionType(EConnectionType::Float4) , Values`
- L396 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(double Value) : ConnectionType(EConnectionType::Float) , Values`
- L402 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(UTexture* Texture) : ConnectionType(EConnectionType::Texture) , Texture(Texture)`
- L408 _function_ `inline FMaterialExpressionConnection::FMaterialExpressionConnection(const FData& Value, const FData& True, const FData& False) : ConnectionType(EConnectionType::TextureSelection)`
- L416 _function_ `inline bool FMaterialExpressionConnection::operator!=(const FMaterialExpressionConnection& rhs)`

#### struct `Generator::FMaterialExpressionConnection::FData`  
`struct FData`  
_L78-93_
- L80 _public prototype_ `FData();`
- L81 _public prototype_ `FData(FMaterialExpressionHandle ExpressionHandle, int32 Index, bool bIsDefault);`
- L83 _public prototype_ `bool operator!=(const FData& rhs);`
- L85 _public function_ `UMaterialExpression* GetMaterialExpression() const`
- L90 _public member_ `FMaterialExpressionHandle ExpressionHandle;`
- L91 _public member_ `int32 Index;`
- L92 _public member_ `bool bIsDefault;`
- L433 _function_ `inline FMaterialExpressionConnection::FData::FData() : Index(0) , bIsDefault(false)`
- L439 _function_ `inline FMaterialExpressionConnection::FData::FData(FMaterialExpressionHandle InExpressionHandle, int32 Index, bool bIsDefault) : ExpressionHandle(InExpressionHandle) , Index(Index) , bIsDefault(bIsDefault)`
- L446 _function_ `inline bool FMaterialExpressionConnection::FData::operator!=(const FData& rhs)`

#### union `Generator::FMaterialExpressionConnection::(anonymous)`  
``  
_L221-225_

#### struct `Generator::FMaterialExpressionConnectionList`  
`struct FMaterialExpressionConnectionList`  
_L229-335_
- L231 _public member_ `TArray<FMaterialExpressionConnection> Connections;`
- L233 _public member_ `bool bIsUsed;`
- L235 _public function_ `FMaterialExpressionConnectionList() : bIsUsed(false)`
- L239 _public function_ `FMaterialExpressionConnectionList(std::initializer_list<FMaterialExpressionConnection> Expressions) : bIsUsed(false)`
- L245 _public function_ `FMaterialExpressionConnectionList(std::initializer_list<UMaterialExpression*> Expressions) : bIsUsed(false)`
- L254 _public function_ `bool IsUsed()`
- L259 _public function_ `void SetIsUsed()`
- L264 _public function_ `void Reserve(int32 Size)`
- L269 _public function_ `void SetNum(int32 Size)`
- L274 _public function_ `void Empty()`
- L279 _public function_ `int32 Num() const`
- L284 _public function_ `void Add(const FMaterialExpressionConnection& Connection)`
- L289 _public function_ `void Push(const FMaterialExpressionConnection&& Connection)`
- L295 _public function_ `template <typename... ArgsType> FORCEINLINE int32 Emplace(ArgsType&&... Args)`
- L301 _public function_ `FMaterialExpressionConnection& operator[](int32 ConnectionIndex)`
- L306 _public function_ `const FMaterialExpressionConnection& operator[](int32 ConnectionIndex) const`
- L311 _public function_ `void Append(const FMaterialExpressionConnectionList& Other)`
- L317 _public function_ `template <typename Predicate> int32 FindLastByPredicate(Predicate Pred)`
- L322 _public function_ `operator TArray<FMaterialExpressionConnection>()`
- L328 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Generator`
- L222 _member_ `bool bValue;` (scope `Generator::FMaterialExpressionConnection::__anon531d88d8010a`)
- L223 _member_ `float Values[4];` (scope `Generator::FMaterialExpressionConnection::__anon531d88d8010a`)
- L224 _member_ `UTexture* Texture;` (scope `Generator::FMaterialExpressionConnection::__anon531d88d8010a`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/MaterialExpressionFactory.h` (Private)


#### class `Generator::FMaterialExpressionFactory`  
`class FMaterialExpressionFactory : public FBaseExpressionFactory`  
_L39-123_
- inherits: `FBaseExpressionFactory`
- L42 _public prototype_ `explicit FMaterialExpressionFactory(const Mdl::FApiContext& MdlContext);`
- L44 _public prototype_ `void SetCurrentMaterial(const mi::neuraylib::IMaterial_definition& MDLMaterialDefinition, const mi::neuraylib::ICompiled_material& MDLMaterial, mi::neuraylib::ITransaction& MDLTransaction, UMaterial& Material);`
- L49 _public prototype_ `void CreateParameterExpressions();`
- L51 _public prototype_ `void SetCurrentNormal(UMaterialExpression* NormalExpression, bool bIsGeometryExpression);`
- L53 _public prototype_ `void SetFunctionLoader(FFunctionLoader* FunctionLoader);`
- L54 _public prototype_ `void SetTextureFactory(FMaterialTextureFactory* Factory);`
- L56 _public prototype_ `FMaterialExpressionConnectionList CreateExpression(const mi::base::Handle<const mi::neuraylib::IExpression>& MDLExpression, const FString& CallPath);`
- L59 _public prototype_ `void Cleanup(bool bOnlyTemporaries = false);`
- L62 _public prototype_ `void CleanupMaterialExpressions();` — remove redundant material expressions
- L64 _public prototype_ `TArray<MDLImporterLogging::FLogMessage> GetLogMessages();`
- L67 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionTemporary(const mi::neuraylib::IExpression_temporary& MDLExpression, const FString& CallPath);`
- L70 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionFunctionCall(const mi::neuraylib::IExpression_direct_call& MDLCall, const FString& CallPath);`
- L73 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionConstructorCall(const mi::neuraylib::IType& MDLType, const FMaterialExpressionConnectionList& Inputs);`
- L76 _private prototype_ `bool CreateFunctionCallInputs(const mi::neuraylib::IFunction_definition& InFunctionDefinition, const mi::neuraylib::IExpression_direct_call& InMDLFunctionCall, const FString& InCallPath, int32& OutArraySize, FMaterialExpressionConnectionList& OutInputs);`
- L82 _private prototype_ `FMaterialExpressionConnectionList MakeFunctionCall(const FString& InCallPath,`
- L88 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionUnary(int Semantic, const FMaterialExpressionConnectionList& Inputs, const mi::neuraylib::IType& MDLType);`
- L92 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionBinary(int Semantic,`
- L95 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionTernary(const FMaterialExpressionConnectionList& Inputs);`
- L97 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionMath(int Semantic,`
- L100 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionDAG(int Semantic, const FMaterialExpressionConnectionList& Inputs, const FString& FunctionName);`
- L104 _private prototype_ `FMaterialExpressionConnectionList CreateExpressionOther(int Semantic, const FMaterialExpressionConnectionList& Inputs);`
- L106 _private prototype_ `void HandleNormal(int Semantic, FMaterialExpressionConnectionList& Inputs);`
- L107 _private prototype_ `void SetClearCoatNormal(const FMaterialExpressionConnection& Base, const UMaterialExpression* Normal);`
- L110 _private member_ `FConstantExpressionFactory ConstantExpressionFactory;`
- L111 _private member_ `FParameterExpressionFactory ParameterExpressionFactory;`
- L113 _private member_ `FMaterialTextureFactory* TextureFactory;`
- L115 _private member_ `mi::neuraylib::IMdl_factory* MdlFactory;`
- L116 _private member_ `mi::neuraylib::ITransaction* CurrentTransaction;`
- L117 _private member_ `UMaterialExpression* CurrentNormalExpression;`
- L118 _private member_ `bool bIsGeometryExpression;`
- L120 _private member_ `FFunctionLoader* FunctionLoader;`
- L122 _private member_ `TArray<FMaterialExpressionConnectionList> Temporaries;`
- L125 _function_ `inline void FMaterialExpressionFactory::SetCurrentNormal(UMaterialExpression* InNormalExpression, bool InIsGeometryExpression)`
- L132 _function_ `inline void FMaterialExpressionFactory::SetFunctionLoader(FFunctionLoader* InFunctionLoader)`
- L137 _function_ `inline void FMaterialExpressionFactory::Cleanup(bool bOnlyTemporaries )`
- L157 _function_ `inline void FMaterialExpressionFactory::CleanupMaterialExpressions()`
- L164 _function_ `inline TArray<MDLImporterLogging::FLogMessage> FMaterialExpressionFactory::GetLogMessages()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace mi`
- L13 _namespace_ `namespace neuraylib` (scope `mi`)
- L23 _namespace_ `namespace base` (scope `mi`)
- L29 _namespace_ `namespace Mdl`
- L34 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/MaterialExpressions.h` (Private)


#### Free symbols / members of external scopes

- L77 _namespace_ `namespace Generator`
- L80 _prototype_ `template <typename T> T* NewMaterialExpression(UObject* Parent);` (scope `Generator`)
- L83 _prototype_ `template <typename T> void Connect(T& Target, const FMaterialExpressionConnection& Connection);` (scope `Generator`)
- L85 _prototype_ `void SetMaterialExpressionGroup(const FString& GroupName, UMaterialExpression* ParameterExpression);` (scope `Generator`)
- L87 _prototype_ `bool IsBool(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L88 _prototype_ `bool IsMaterialAttribute(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L89 _prototype_ `bool IsScalar(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L90 _prototype_ `bool IsStatic(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L91 _prototype_ `bool IsTexture(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L92 _prototype_ `bool IsVector3(const FMaterialExpressionConnection& Input);` (scope `Generator`)
- L95 _prototype_ `UMaterialExpressionAbs* NewMaterialExpressionAbs(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Abs
- L98 _prototype_ `UMaterialExpressionAdd* NewMaterialExpressionAdd(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Add
- L99 _prototype_ `UMaterialExpressionAdd* NewMaterialExpressionAdd(UObject* Parent, const TArray<FMaterialExpressionConnection>& Arguments);` (scope `Generator`)
- L102 _prototype_ `UMaterialExpressionAppendVector* NewMaterialExpressionAppendVector(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — AppendVector
- L105 _prototype_ `UMaterialExpressionAppendVector* NewMaterialExpressionAppendVector(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& C);` (scope `Generator`)
- L111 _prototype_ `UMaterialExpressionArccosine* NewMaterialExpressionArccosine(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Arccosine
- L114 _prototype_ `UMaterialExpressionArcsine* NewMaterialExpressionArcsine(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Arcsine
- L117 _prototype_ `UMaterialExpressionArctangent* NewMaterialExpressionArctangent(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Arctangent
- L120 _prototype_ `UMaterialExpressionArctangent2* NewMaterialExpressionArctangent2(UObject* Parent, const FMaterialExpressionConnection& Y, const FMaterialExpressionConnection& X);` (scope `Generator`) — Arctangent2
- L125 _prototype_ `UMaterialExpressionBlackBody* NewMaterialExpressionBlackBody(UObject* Parent, const FMaterialExpressionConnection& Temperature);` (scope `Generator`) — BlackBody
- L128 _prototype_ `UMaterialExpressionBreakMaterialAttributes* NewMaterialExpressionBreakMaterialAttributes(UObject* Parent, const FMaterialExpressionConnection& MaterialAttributes);` (scope `Generator`) — BreakMaterialAttributes
- L132 _prototype_ `UMaterialExpressionCeil* NewMaterialExpressionCeil(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Ceil
- L135 _prototype_ `UMaterialExpressionClamp* NewMaterialExpressionClamp(UObject* Parent, const FMaterialExpressionConnection& Input, const FMaterialExpressionConnection& Min, const FMaterialExpressionConnection& Max);` (scope `Generator`) — Clamp
- L141 _prototype_ `UMaterialExpressionComponentMask* NewMaterialExpressionComponentMask(UObject* Parent, const FMaterialExpressionConnection& Input, uint32 Mask);` (scope `Generator`) — ComponentMask
- L144 _prototype_ `UMaterialExpressionClearCoatNormalCustomOutput* NewMaterialExpressionClearCoatNormalCustomOutput(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — ClearCoatNormalCustomOutput
- L148 _prototype_ `UMaterialExpressionConstant* NewMaterialExpressionConstant(UObject* Parent, float X);` (scope `Generator`) — Constant
- L149 _prototype_ `UMaterialExpressionConstant2Vector* NewMaterialExpressionConstant(UObject* Parent, float X, float Y);` (scope `Generator`)
- L150 _prototype_ `UMaterialExpressionConstant3Vector* NewMaterialExpressionConstant(UObject* Parent, float X, float Y, float Z);` (scope `Generator`)
- L151 _prototype_ `UMaterialExpressionConstant4Vector* NewMaterialExpressionConstant(UObject* Parent, float X, float Y, float Z, float W);` (scope `Generator`)
- L154 _prototype_ `UMaterialExpressionCosine* NewMaterialExpressionCosine(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Cosine
- L157 _prototype_ `UMaterialExpressionCrossProduct* NewMaterialExpressionCrossProduct(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — CrossProduct
- L162 _prototype_ `UMaterialExpressionDistance* NewMaterialExpressionDistance(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Distance
- L167 _prototype_ `UMaterialExpressionDivide* NewMaterialExpressionDivide(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Divide
- L172 _prototype_ `UMaterialExpressionDotProduct* NewMaterialExpressionDotProduct(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — DotProduct
- L177 _prototype_ `UMaterialExpressionFloor* NewMaterialExpressionFloor(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Floor
- L180 _prototype_ `UMaterialExpressionFmod* NewMaterialExpressionFmod(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Fmod
- L185 _prototype_ `UMaterialExpressionFrac* NewMaterialExpressionFrac(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Frac
- L188 _prototype_ `UMaterialExpressionFresnel* NewMaterialExpressionFresnel(UObject* Parent, const FMaterialExpressionConnection& Exponent, const FMaterialExpressionConnection& BaseReflectFraction, const FMaterialExpressionConnection& Normal);` (scope `Generator`) — Fresnel
- L194 _prototype_ `UMaterialExpressionFunctionInput* NewMaterialExpressionFunctionInput(UObject* Parent, const FString& Name, EFunctionInputType Type);` (scope `Generator`) — FunctionInput
- L195 _prototype_ `UMaterialExpressionFunctionInput* NewMaterialExpressionFunctionInput(UObject* Parent, const FString& Name, EFunctionInputType Type, const FMaterialExpressionConnection& DefaultExpression);` (scope `Generator`)
- L201 _prototype_ `UMaterialExpressionFunctionOutput* NewMaterialExpressionFunctionOutput(UObject* Parent, const FString& Name, const FMaterialExpressionConnection& Output);` (scope `Generator`) — FunctionOutput
- L206 _prototype_ `UMaterialExpressionIf* NewMaterialExpressionIf(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& Less, const FMaterialExpressionConnection& Equal, const FMaterialExpressionConnection& Greater);` (scope `Generator`) — If
- L212 _prototype_ `UMaterialExpressionIf* NewMaterialExpressionIfEqual(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& Bx, const FMaterialExpressionConnection& Yes, const FMaterialExpressionConnection& No);` (scope `Generator`)
- L217 _prototype_ `UMaterialExpressionIf* NewMaterialExpressionIfGreater(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& Yes, const FMaterialExpressionConnection& No);` (scope `Generator`)
- L222 _prototype_ `UMaterialExpressionIf* NewMaterialExpressionIfLess(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& Yes, const FMaterialExpressionConnection& No);` (scope `Generator`)
- L227 _prototype_ `UMaterialExpressionIf* NewMaterialExpressionSwitch(UObject* Parent, const FMaterialExpressionConnection& Switch, const TArray<FMaterialExpressionConnection>& Cases);` (scope `Generator`)
- L232 _prototype_ `UMaterialExpressionLinearInterpolate* NewMaterialExpressionLinearInterpolate(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& Alpha);` (scope `Generator`) — LinearInterpolate
- L236 _prototype_ `UMaterialExpression* NewMaterialExpressionLinearInterpolate(UObject* Function, const TArray<FMaterialExpressionConnection>& Values, const FMaterialExpressionConnection& Alpha);` (scope `Generator`)
- L241 _prototype_ `UMaterialExpressionLogarithm2* NewMaterialExpressionLogarithm2(UObject* Parent, const FMaterialExpressionConnection& X);` (scope `Generator`) — Logarithm2
- L244 _prototype_ `UMaterialExpressionMaterialFunctionCall* NewMaterialExpressionFunctionCall(UObject* Parent, UMaterialFunction* Function, const TArray<FMaterialExpressionConnection>& Inputs);` (scope `Generator`) — MaterialFunctionCall
- L250 _prototype_ `UMaterialExpressionMakeMaterialAttributes* NewMaterialExpressionMakeMaterialAttributes( UObject* Parent, const FMaterialExpressionConnection& BaseColor = {}, const FMaterialExpressionConnection& Metallic = {}, const FMaterialExpressionConnection& Specular = {}, const FMaterialExpressionConnection& Roughness = {}, const FMaterialExpressionConnection& EmissiveColor = {}, const FMaterialExpressionConnection& Opacity = {}, const FMaterialExpressionConnection& OpacityMask = {}, const FMaterialExpressionConnection& Normal = {}, const FMaterialExpressionConnection& WorldPositionOffset = {}, const FMaterialExpressionConnection& SubsurfaceColor = {}, const FMaterialExpressionConnection& ClearCoat = 0.0f, const FMaterialExpressionConnection& ClearCoatRoughness = {}, const FMaterialExpressionConnection& AmbientOcclusion = {}, const FMaterialExpressionConnection& Refraction = {}, const FMaterialExpressionConnection& CustomizedUVs0 = {}, const FMaterialExpressionConnection& CustomizedUVs1 = {}, const FMaterialExpressionConnection& CustomizedUVs2 = {}, const FMaterialExpressionConnection& CustomizedUVs3 = {}, const FMaterialExpressionConnection& CustomizedUVs4 = {}, const FMaterialExpressionConnection& CustomizedUVs5 = {}, const FMaterialExpressionConnection& CustomizedUVs6 = {}, const FMaterialExpressionConnection& CustomizedUVs7 = {}, const FMaterialExpressionConnection& PixelDepthOffset = {});` (scope `Generator`) — MakeMaterialAttributes @note Forcing ClearCoat to 0.0f per default
- L265 _prototype_ `UMaterialExpressionMax* NewMaterialExpressionMax(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Max
- L267 _prototype_ `UMaterialExpressionMax* NewMaterialExpressionMax(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& C);` (scope `Generator`)
- L273 _prototype_ `UMaterialExpressionMin* NewMaterialExpressionMin(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Min
- L274 _prototype_ `UMaterialExpressionMin* NewMaterialExpressionMin(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& C);` (scope `Generator`)
- L280 _prototype_ `UMaterialExpressionMultiply* NewMaterialExpressionMultiply(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Multiply
- L283 _prototype_ `UMaterialExpressionMultiply* NewMaterialExpressionMultiply(UObject* Parent, const TArray<FMaterialExpressionConnection>& Arguments);` (scope `Generator`)
- L284 _prototype_ `UMaterialExpressionMultiply* NewMaterialExpressionSquare(UObject* Parent, const FMaterialExpressionConnection& A);` (scope `Generator`)
- L287 _prototype_ `UMaterialExpressionSubtract* NewMaterialExpressionNegate(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Negate
- L290 _prototype_ `UMaterialExpressionNoise* NewMaterialExpressionNoise(UObject* Parent, const FMaterialExpressionConnection& Position, int32 Quality);` (scope `Generator`) — Noise
- L293 _prototype_ `UMaterialExpressionVectorNoise* NewMaterialExpressionVectorNoise(UObject* Parent, const FMaterialExpressionConnection& Position, int32 Quality);` (scope `Generator`) — Vector Noise
- L296 _prototype_ `UMaterialExpressionNormalize* NewMaterialExpressionNormalize(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Normalize
- L299 _prototype_ `UMaterialExpressionOneMinus* NewMaterialExpressionOneMinus(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — OneMinus
- L302 _prototype_ `UMaterialExpressionPower* NewMaterialExpressionPower(UObject* Parent, const FMaterialExpressionConnection& Base, const FMaterialExpressionConnection& Exponent);` (scope `Generator`) — Power
- L307 _prototype_ `UMaterialExpressionReflectionVectorWS* NewMaterialExpressionReflectionVectorWS(UObject* Parent, const FMaterialExpressionConnection& CustomWorldNormal);` (scope `Generator`) — ReflectionVectorWS
- L311 _prototype_ `UMaterialExpressionSaturate* NewMaterialExpressionSaturate(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Saturate
- L314 _prototype_ `UMaterialExpressionScalarParameter* NewMaterialExpressionScalarParameter(UObject* Parent, const FString& Name, float DefaultValue);` (scope `Generator`) — ScalarParameter
- L317 _prototype_ `UMaterialExpressionSine* NewMaterialExpressionSine(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Sine
- L320 _prototype_ `UMaterialExpressionSquareRoot* NewMaterialExpressionSquareRoot(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — SquareRoot
- L323 _prototype_ `UMaterialExpressionStaticBool* NewMaterialExpressionStaticBool(UObject* Parent, bool bValue);` (scope `Generator`) — StaticBool
- L326 _prototype_ `UMaterialExpressionStaticBoolParameter* NewMaterialExpressionStaticBoolParameter(UObject* Parent, const FString& Name, bool bDefaultValue, const FString& Group = TEXT(""));` (scope `Generator`) — StaticBoolParameter
- L332 _prototype_ `UMaterialExpressionStaticSwitch* NewMaterialExpressionStaticSwitch(UObject* Parent, const FMaterialExpressionConnection& Value, const FMaterialExpressionConnection& True, const FMaterialExpressionConnection& False);` (scope `Generator`) — StaticSwitch
- L338 _prototype_ `UMaterialExpressionSubtract* NewMaterialExpressionSubtract(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B);` (scope `Generator`) — Subtract
- L341 _prototype_ `UMaterialExpressionSubtract* NewMaterialExpressionSubtract(UObject* Parent, const FMaterialExpressionConnection& A, const FMaterialExpressionConnection& B, const FMaterialExpressionConnection& C);` (scope `Generator`)
- L347 _prototype_ `UMaterialExpressionTangent* NewMaterialExpressionTangent(UObject* Parent, const FMaterialExpressionConnection& Input);` (scope `Generator`) — Tangent
- L350 _prototype_ `UMaterialExpressionTextureCoordinate* NewMaterialExpressionTextureCoordinate(UObject* Parent, int32 CoordinateIndex);` (scope `Generator`) — TextureCoordinate
- L353 _prototype_ `UMaterialExpressionTextureObject* NewMaterialExpressionTextureObject(UObject* Parent, UTexture* Texture);` (scope `Generator`) — TextureObject
- L356 _prototype_ `UMaterialExpressionTextureObjectParameter* NewMaterialExpressionTextureObjectParameter(UObject* Parent, const FString& Name, UTexture* Texture);` (scope `Generator`) — TextureObjectParameter
- L359 _prototype_ `UMaterialExpressionTextureProperty* NewMaterialExpressionTextureProperty(UObject* Parent, const FMaterialExpressionConnection& TextureObject, EMaterialExposedTextureProperty Property);` (scope `Generator`) — TextureProperty
- L364 _prototype_ `UMaterialExpressionTextureSample* NewMaterialExpressionTextureSample(UObject* Parent, const FMaterialExpressionConnection& TextureObject, const FMaterialExpressionConnection& Coordinates);` (scope `Generator`) — TextureSample
- L369 _prototype_ `UMaterialExpressionTransform* NewMaterialExpressionTransform(UObject* Parent, const FMaterialExpressionConnection& Input, EMaterialVectorCoordTransformSource SourceType, EMaterialVectorCoordTransform DestinationType);` (scope `Generator`) — Transform
- L375 _prototype_ `UMaterialExpressionTransformPosition* NewMaterialExpressionTransformPosition(UObject* Parent, const FMaterialExpressionConnection& Input, EMaterialPositionTransformSource SourceType, EMaterialPositionTransformSource DestinationType);` (scope `Generator`) — TransformPosition
- L381 _prototype_ `UMaterialExpressionTwoSidedSign* NewMaterialExpressionTwoSidedSign(UObject* Parent);` (scope `Generator`) — TwoSidedSign
- L384 _prototype_ `UMaterialExpressionVectorNoise* NewMaterialExpressionVectorNoise(UObject* Parent, const FMaterialExpressionConnection& Position, EVectorNoiseFunction NoiseFunction, int32 Quality);` (scope `Generator`) — VectorNoise
- L388 _prototype_ `UMaterialExpressionVectorParameter* NewMaterialExpressionVectorParameter(UObject* Parent, const FString& Name, const FLinearColor& DefaultValue);` (scope `Generator`) — VectorParameter
- L393 _function_ `template <typename T> inline void Connect(T& Target, const FMaterialExpressionConnection& Connection)` (scope `Generator`)
- L402 _function_ `template <typename T> inline T* NewMaterialExpression(UObject* Parent)` (scope `Generator`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/MaterialTextureFactory.h` (Private)


#### class `Generator::FMaterialTextureFactory`  
`class FMaterialTextureFactory`  
_L16-41_
- L19 _public typedef_ `typedef FImage* FTextureSourcePtr;`
- L21 _public prototype_ `FMaterialTextureFactory();`
- L23 _public prototype_ `void SetFactory(UTextureFactory* Factory);`
- L24 _public prototype_ `void SetDefaultProperties(const Common::FTextureProperty& Properties);`
- L25 _public prototype_ `void SetAssetPrefix(const FString& Suffix);`
- L27 _public prototype_ `UTexture2D* CreateTexture(UObject* ParentPackage, const Common::FTextureProperty& Property, FTextureSourcePtr& Source, EObjectFlags Flags, TArray<MDLImporterLogging::FLogMessage>* InLogMessages = nullptr);`
- L29 _public prototype_ `UTexture2D* CreateTexture(UObject* ParentPackage, const Common::FTextureProperty& Property, EObjectFlags Flags, TArray<MDLImporterLogging::FLogMessage>* InLogMessages = nullptr);`
- L31 _public prototype_ `UTexture2D* CreateTexture(UObject* ParentPackage, const FString& FilePath, EObjectFlags Flags, TArray<MDLImporterLogging::FLogMessage>* InLogMessages = nullptr);`
- L34 _public prototype_ `void UpdateTextureFactorySettings(UTextureFactory* TextureFactory, const Common::FTextureProperty& Property);`
- L35 _public prototype_ `void UpdateTextureSettings(UTexture2D* Texture, const Common::FTextureProperty& Property, TArray<MDLImporterLogging::FLogMessage>* LogMessages = nullptr);`
- L38 _private member_ `UTextureFactory* Factory;`
- L39 _private member_ `Common::FTextureProperty DefaultProperties;`
- L40 _private member_ `FString AssetPrefix;`
- L43 _function_ `inline void FMaterialTextureFactory::SetFactory(UTextureFactory* InFactory)`
- L48 _function_ `inline void FMaterialTextureFactory::SetDefaultProperties(const Common::FTextureProperty& Properties)`
- L53 _function_ `inline void FMaterialTextureFactory::SetAssetPrefix(const FString& Prefix)`
- L58 _function_ `inline UTexture2D* FMaterialTextureFactory::CreateTexture(UObject* ParentPackage, const Common::FTextureProperty& Property, EObjectFlags Flags, TArray<MDLImporterLogging::FLogMessage>* InLogMessages )`
- L65 _function_ `inline UTexture2D* FMaterialTextureFactory::CreateTexture(UObject* ParentPackage, const FString& FilePath, EObjectFlags Flags, TArray<MDLImporterLogging::FLogMessage>* InLogMessages )`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/generator/ParameterExpressionFactory.h` (Private)


#### class `Generator::FParameterExpressionFactory`  
`class FParameterExpressionFactory : public FBaseExpressionFactory`  
_L23-44_
- inherits: `FBaseExpressionFactory`
- L26 _public prototype_ `FParameterExpressionFactory();`
- L28 _public prototype_ `void SetTextureFactory(FMaterialTextureFactory* Factory);`
- L30 _public prototype_ `void CreateExpressions(mi::neuraylib::ITransaction& Transaction);`
- L32 _public prototype_ `const FMaterialExpressionConnectionList& GetExpression(const mi::neuraylib::IExpression_parameter& MDLExpression);`
- L34 _public prototype_ `void Cleanup();`
- L36 _public prototype_ `void CleanupMaterialExpressions();`
- L38 _private prototype_ `void ImportParameter(const FString& Name, const mi::neuraylib::IValue& Value, mi::neuraylib::ITransaction& Transaction, FMaterialExpressionConnectionList& Parameter);`
- L42 _private member_ `TArray<FMaterialExpressionConnectionList> Parameters;`
- L43 _private member_ `FMaterialTextureFactory* TextureFactory;`
- L46 _function_ `inline void FParameterExpressionFactory::SetTextureFactory(FMaterialTextureFactory* Factory)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Generator`
- L9 _namespace_ `namespace mi`
- L11 _namespace_ `namespace neuraylib` (scope `mi`)
- L19 _namespace_ `namespace Generator`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/material/BakedMaterialFactory.h` (Private)


#### class `Mat::FBakedMaterialFactory`  
`class FBakedMaterialFactory : public IMaterialFactory`  
_L14-25_
- inherits: `IMaterialFactory`
- L17 _public prototype_ `FBakedMaterialFactory(Generator::FFunctionLoader& FunctionLoader);`
- L19 _public prototype_ `virtual void Create(const Mdl::FMaterial& MdlMaterial, const Mat::FParameterMap& Parameters, UMaterial& Material) const override;`
- L21 _public prototype_ `static UMaterialExpression* GetTilingParameter(Generator::FFunctionLoader& FunctionLoader, UMaterial& Material);`
- L24 _private member_ `Generator::FFunctionLoader& FunctionLoader;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Generator`
- L12 _namespace_ `namespace Mat`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/material/CarpaintMaterialFactory.h` (Private)


#### class `Mat::FCarpaintMaterialFactory`  
`class FCarpaintMaterialFactory : public IMaterialFactory`  
_L15-32_
- inherits: `IMaterialFactory`
- L18 _public prototype_ `FCarpaintMaterialFactory(Generator::FFunctionLoader& FunctionLoader);`
- L20 _public prototype_ `virtual void Create(const Mdl::FMaterial& MdlMaterial, const Mat::FParameterMap& Parameters, UMaterial& Material) const override;`
- L23 _private prototype_ `TTuple<UMaterialExpression*, int> CreateFlakes(const Mdl::FMaterial& MdlMaterial, const Mat::FParameterMap& Parameters, UMaterialExpression* ThetaAngles, UMaterialExpression* Tiling, UMaterial& OutMaterial) const;`
- L30 _private member_ `mutable Generator::FMaterialExpressionConnectionList Inputs;`
- L31 _private member_ `Generator::FFunctionLoader& FunctionLoader;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Generator`
- L13 _namespace_ `namespace Mat`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/material/MapConnecter.h` (Private)


#### struct `Mat::FMapConnecter`  
`struct FMapConnecter`  
_L13-124_
- L15 _public function_ `FMapConnecter(const FParameterMap& Parameters, Generator::FFunctionLoader& FunctionLoader, UMaterialExpression* Tiling, UMaterial& Material) : Parameters(Parameters) , FunctionLoader(FunctionLoader) , Tiling(Tiling) , Material(Material)`
- L24 _public function_ `void DeleteExpression(EMaterialParameter Parameter)`
- L33 _public function_ `void DeleteExpressionMap(EMaterialParameter Parameter)`
- L42 _public function_ `template <typename TargetMap> void ConnectParameter(TargetMap& Target, const FString& GroupName, EMaterialParameter Parameter)`
- L52 _public function_ `UMaterialExpression* CreateMapCall(const FString& GroupName, EMaterialParameter Parameter, bool bIsColorMap, UMaterialExpression* ColorExpression)`
- L67 _public function_ `UMaterialExpression* CreateParameterMap(const FString& GroupName, EMaterialParameter Parameter, bool bIsColorMap = true, UMaterialExpression* ColorExpression = nullptr)`
- L87 _public function_ `template <typename TargetMap> UMaterialExpression* ConnectParameterMap(TargetMap& Target, const FString& GroupName, EMaterialParameter Parameter, bool bIsColorMap = true, UMaterialExpression* ColorExpression = nullptr)`
- L98 _public function_ `template <typename TargetMap> UMaterialExpression* ConnectNormalMap(TargetMap& Target, const FString& GroupName, EMaterialParameter Parameter)`
- L119 _private member_ `const FParameterMap& Parameters;`
- L120 _private member_ `Generator::FFunctionLoader& FunctionLoader;`
- L121 _private member_ `UMaterialExpression* Tiling;`
- L122 _private member_ `UMaterial& Material;`
- L123 _private member_ `Generator::FMaterialExpressionConnectionList Inputs;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Mat`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/material/MaterialFactory.h` (Private)


#### enum `Mat::EMaterialParameter`  
`enum class EMaterialParameter`  
_L16-50_
- L18 _public enumerator_ `BaseColor = 0`
- L19 _public enumerator_ `BaseColorMap`
- L20 _public enumerator_ `SubSurfaceColor`
- L21 _public enumerator_ `SubSurfaceColorMap`
- L22 _public enumerator_ `EmissionColor`
- L23 _public enumerator_ `EmissionColorMap`
- L24 _public enumerator_ `EmissionStrength`
- L25 _public enumerator_ `Roughness`
- L26 _public enumerator_ `RoughnessMap`
- L27 _public enumerator_ `Metallic`
- L28 _public enumerator_ `MetallicMap`
- L29 _public enumerator_ `Specular`
- L30 _public enumerator_ `SpecularMap`
- L31 _public enumerator_ `IOR`
- L32 _public enumerator_ `AbsorptionColor`
- L33 _public enumerator_ `Opacity`
- L34 _public enumerator_ `OpacityMap`
- L35 _public enumerator_ `NormalMap`
- L36 _public enumerator_ `NormalStrength`
- L37 _public enumerator_ `DisplacementMap`
- L38 _public enumerator_ `DisplacementStrength`
- L39 _public enumerator_ `ClearCoatWeight`
- L40 _public enumerator_ `ClearCoatWeightMap`
- L41 _public enumerator_ `ClearCoatRoughness`
- L42 _public enumerator_ `ClearCoatRoughnessMap`
- L43 _public enumerator_ `ClearCoatNormalMap`
- L44 _public enumerator_ `ClearCoatNormalStrength`
- L45 _public enumerator_ `CarFlakesMap`
- L46 _public enumerator_ `CarFlakesLut`
- L47 _public enumerator_ `Tiling`
- L48 _public enumerator_ `TilingU`
- L49 _public enumerator_ `TilingV`

#### class `Mat::IMaterialFactory`  
`class IMaterialFactory`  
_L54-60_
- L57 _public function_ `virtual ~IMaterialFactory()`
- L59 _public prototype_ `virtual void Create(const Mdl::FMaterial& MdlMaterial, const Mat::FParameterMap& Parameters, UMaterial& Material) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Mdl`
- L14 _namespace_ `namespace Mat`
- L52 _typedef_ `using FParameterMap = TMap<EMaterialParameter, UMaterialExpression*>;` (scope `Mat`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/material/TranslucentMaterialFactory.h` (Private)


#### class `Mat::FTranslucentMaterialFactory`  
`class FTranslucentMaterialFactory : public IMaterialFactory`  
_L14-23_
- inherits: `IMaterialFactory`
- L17 _public prototype_ `FTranslucentMaterialFactory(Generator::FFunctionLoader& FunctionLoader);`
- L19 _public prototype_ `virtual void Create(const Mdl::FMaterial& MdlMaterial, const Mat::FParameterMap& Parameters, UMaterial& Material) const override;`
- L22 _private member_ `Generator::FFunctionLoader& FunctionLoader;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Generator`
- L12 _namespace_ `namespace Mat`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/ApiContext.h` (Private)


#### class `Mdl::IApiContext`  
`class IApiContext : FNoncopyable`  
_L14-82_
- inherits: `FNoncopyable`
- L17 _public prototype_ `virtual ~IApiContext() = default;`
- L26 _public function_ `virtual bool Load(const FString& LibrariesPath, const FString& ModulesPath)` — Loads and initializes the MDL context. @param LibrariesPath - path to the libraries required by the MDL SDK(eg. nv_freeimage). @param ModulesPath - main search path for MDL modules. @return true if the context was loaded.
- L35 _public function_ `virtual void Unload(bool bClearDatabaseOnly)` — Unloads and de-initializes the MDL context. @param bClearDatabaseOnly - clear the MDL database(MDL modules, materials, textures, etc.)
- L40 _public function_ `virtual void AddSearchPath(const FString& ModulesPath)` — @param ModulesPath - search path for MDL modules.
- L41 _public function_ `virtual void RemoveSearchPath(const FString& ModulesPath)`
- L46 _public function_ `virtual void AddResourceSearchPath(const FString& ResourcesPath)` — @param ResourcesPath - search path for resources(i.e. textures, light profiles, bsdf measurements) used by an MDL module.
- L47 _public function_ `virtual void RemoveResourceSearchPath(const FString& ResourcesPath)`
- L58 _public function_ `virtual bool LoadModule(const FString& InModuleName, FMaterialCollection& OutMaterials)` — Loads materials from an MDL module to the given material collection. @param InModuleName - MDL module name. @param OutMaterials - collection of materials that are present in the MDL module. @return true if the MDL was loaded to the database. @note Only the material names and ids are populated, the material(s) must be distilled after.
- L62 _public function_ `virtual bool UnloadModule(const FString& InModuleName)`
- L70 _public function_ `virtual FMaterialDistiller* GetDistiller()` — Returns the material distiller used for material distillation to the Unreal target model.
- L78 _public function_ `virtual TArray<MDLImporterLogging::FLogMessage> GetLogMessages() const` — Returns any last error or warning messages.

#### class `Mdl::FApiContext`  
`class FApiContext : public IApiContext`  
_L108-144_
- inherits: `IApiContext`
- L111 _public prototype_ `FApiContext();`
- L112 _public prototype_ `virtual ~FApiContext();`
- L114 _public prototype_ `virtual bool Load(const FString& LibrariesPath, const FString& ModulesPath) override;`
- L115 _public prototype_ `virtual void Unload(bool bClearDatabaseOnly) override;`
- L117 _public prototype_ `virtual void AddSearchPath(const FString& ModulesPath) override;`
- L118 _public prototype_ `virtual void RemoveSearchPath(const FString& ModulesPath) override;`
- L120 _public prototype_ `virtual void AddResourceSearchPath(const FString& ResourcesPath) override;`
- L121 _public prototype_ `virtual void RemoveResourceSearchPath(const FString& ResourcesPath) override;`
- L123 _public prototype_ `virtual bool LoadModule(const FString& InFilePath, FMaterialCollection& OutMaterials) override;`
- L124 _public prototype_ `virtual bool UnloadModule(const FString& FilePath) override;`
- L126 _public prototype_ `virtual FMaterialDistiller* GetDistiller() override;`
- L128 _public prototype_ `virtual TArray<MDLImporterLogging::FLogMessage> GetLogMessages() const override;`
- L131 _private prototype_ `void LogInfo();`
- L134 _private member_ `void* DsoHandle;`
- L135 _private member_ `mi::base::Handle<mi::neuraylib::INeuray> NeurayHandle;`
- L136 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_configuration> ConfigHandle;`
- L137 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_compiler> CompilerHandle;`
- L138 _private member_ `mi::base::Handle<mi::neuraylib::IDatabase> DatabaseHandle;`
- L139 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_factory> FactoryHandle;`
- L140 _private member_ `TUniquePtr<FMaterialDistiller> DistillerPtr;`
- L141 _private member_ `FLogger* LoggerPtr;`
- L154 _function_ `inline FMaterialDistiller* FApiContext::GetDistiller()`

#### class `Mdl::FApiContext`  
`class FApiContext : public IApiContext`  
_L164-166_
- inherits: `IApiContext`
- L111 _public prototype_ `FApiContext();`
- L112 _public prototype_ `virtual ~FApiContext();`
- L114 _public prototype_ `virtual bool Load(const FString& LibrariesPath, const FString& ModulesPath) override;`
- L115 _public prototype_ `virtual void Unload(bool bClearDatabaseOnly) override;`
- L117 _public prototype_ `virtual void AddSearchPath(const FString& ModulesPath) override;`
- L118 _public prototype_ `virtual void RemoveSearchPath(const FString& ModulesPath) override;`
- L120 _public prototype_ `virtual void AddResourceSearchPath(const FString& ResourcesPath) override;`
- L121 _public prototype_ `virtual void RemoveResourceSearchPath(const FString& ResourcesPath) override;`
- L123 _public prototype_ `virtual bool LoadModule(const FString& InFilePath, FMaterialCollection& OutMaterials) override;`
- L124 _public prototype_ `virtual bool UnloadModule(const FString& FilePath) override;`
- L126 _public prototype_ `virtual FMaterialDistiller* GetDistiller() override;`
- L128 _public prototype_ `virtual TArray<MDLImporterLogging::FLogMessage> GetLogMessages() const override;`
- L131 _private prototype_ `void LogInfo();`
- L134 _private member_ `void* DsoHandle;`
- L135 _private member_ `mi::base::Handle<mi::neuraylib::INeuray> NeurayHandle;`
- L136 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_configuration> ConfigHandle;`
- L137 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_compiler> CompilerHandle;`
- L138 _private member_ `mi::base::Handle<mi::neuraylib::IDatabase> DatabaseHandle;`
- L139 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_factory> FactoryHandle;`
- L140 _private member_ `TUniquePtr<FMaterialDistiller> DistillerPtr;`
- L141 _private member_ `FLogger* LoggerPtr;`
- L154 _function_ `inline FMaterialDistiller* FApiContext::GetDistiller()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Mdl`
- L89 _namespace_ `namespace mi`
- L91 _namespace_ `namespace neuraylib` (scope `mi`)
- L101 _namespace_ `namespace Mdl`
- L103 _namespace_ `namespace Detail` (scope `Mdl`)
- L105 _prototype_ `mi::neuraylib::IMdl_factory* GetFactory(const IApiContext& Context);` (scope `Mdl::Detail`)
- L146 _namespace_ `namespace Detail` (scope `Mdl`)
- L148 _function_ `inline mi::neuraylib::IMdl_factory* GetFactory(const IApiContext& Context)` (scope `Mdl::Detail`)
- L162 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/ArgumentGetter.h` (Private)


#### struct `Mdl::FArgumentGetter`  
`struct FArgumentGetter`  
_L15-42_
- L17 _public member_ `const mi::neuraylib::ICompiled_material* Material;`
- L18 _public member_ `mi::base::Handle<const mi::neuraylib::IExpression_direct_call>& ParentCall;`
- L19 _public member_ `FString SubPath;`
- L21 _public function_ `FArgumentGetter(const mi::neuraylib::ICompiled_material* Material, mi::base::Handle<const mi::neuraylib::IExpression_direct_call>& ParentCall) : Material(Material) , ParentCall(ParentCall)`
- L27 _public function_ `const mi::neuraylib::IExpression* Get(const char* ArgumentName)`
- L32 _public function_ `const mi::neuraylib::IExpression* Get(const char* InSubPath, const char* InArgumentName)`
- L38 _public function_ `const mi::neuraylib::IExpression* GetFromSubPath(const char* ArgumentName)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/BakeParam.h` (Private)


#### class `Mdl::IBakeDestination`  
`class IBakeDestination`  
_L28-34_
- L31 _public prototype_ `virtual ~IBakeDestination() = default;`
- L33 _public prototype_ `virtual bool SetValue(const mi::IData& ValueData) = 0;`

#### class `Mdl::FBakeTextureData`  
`class FBakeTextureData`  
_L36-49_
- L39 _public typedef_ `typedef FImage* FTextureSourcePtr;`
- L41 _public prototype_ `FBakeTextureData(FString& Name, FTextureSourcePtr& Source);`
- L43 _public prototype_ `void SetName(const FString& Name);`
- L44 _public prototype_ `void SetData(const float* Data, int Width, int Height, int Channels);`
- L47 _private member_ `FString& Name;`
- L48 _private member_ `FTextureSourcePtr& Source;`

#### struct `Mdl::FBakeParam`  
`struct FBakeParam`  
_L51-102_
- L53 _public typedef_ `using FRemapFunc = TFunction<void(mi::base::IInterface&)>;`
- L55 _public member_ `int Id;`
- L56 _public member_ `EValueType ValueType;`
- L57 _public member_ `FRemapFunc RemapFunc;`
- L59 _public member_ `FString InputBakePath;` — MDL material bake path for a texture or simple value
- L61 _public member_ `const mi::neuraylib::IExpression* InputExpression;` — MDL expression from the bake path
- L63 _public prototype_ `FBakeParam();`
- L65 _public prototype_ `FBakeParam(int Id, FMaterial::FExpressionEntry& ExpressionEntry, Common::FTextureProperty& TextureEntry, EValueType ValueType, FRemapFunc RemapFunc = nullptr);`
- L72 _public prototype_ `template <typename T, int D> FBakeParam(int Id, FMaterial::TPropertyEntry<T, D>& Map, FRemapFunc RemapFunc = nullptr);`
- L75 _public prototype_ `template <typename T, int D> FBakeParam(int Id, FMaterial::TMapEntry<T, D>& Map, FRemapFunc RemapFunc = nullptr);`
- L78 _public prototype_ `bool SetExpression(UMaterialExpression* Expression, bool bIsTexture, int32 Index);` — @note The remap function will be ignored.
- L80 _public prototype_ `bool SetBakedValue(mi::IData& ValueData);` — @note Will remap the baked value via the remap function.
- L82 _public prototype_ `bool SetBakedTexture(const FString& Name, mi::neuraylib::ICanvas& CanvasData);` — @note Will remap the canvas via the remap function.
- L84 _public prototype_ `bool HasBakedData() const;`
- L85 _public prototype_ `bool HasBakedTextureData() const;`
- L88 _private function_ `FBakeTextureData* CreateTextureBakeData(FString& Path, FBakeTextureData::FTextureSourcePtr& Source)`
- L99 _private member_ `TSharedPtr<IBakeDestination> BakedData;`
- L100 _private member_ `TSharedPtr<FBakeTextureData> BakedTextureData;`
- L101 _private member_ `FMaterial::FExpressionEntry* ExpressionData;`
- L169 _function_ `template <typename T, int D> FBakeParam::FBakeParam(int Id, FMaterial::TPropertyEntry<T, D>& PropertyEntry, FRemapFunc RemapFunc ) : Id(Id) , RemapFunc(RemapFunc) , InputExpression(nullptr) , ExpressionData(&PropertyEntry.ExpressionData)`
- L183 _function_ `template <typename T, int D> FBakeParam::FBakeParam(int Id, FMaterial::TMapEntry<T, D>& MapEntry, FRemapFunc RemapFunc ) : Id(Id) , RemapFunc(RemapFunc) , InputExpression(nullptr) , BakedTextureData(CreateTextureBakeData(MapEntry.Texture.Path, MapEntry.Texture.Source)) , ExpressionData(&MapEntry.ExpressionData)`
- L197 _function_ `inline bool FBakeParam::HasBakedData() const`
- L202 _function_ `inline bool FBakeParam::HasBakedTextureData() const`

#### class `Mdl::Detail::FBakedFloatValue`  
`class FBakedFloatValue : public IBakeDestination`  
_L106-116_
- inherits: `IBakeDestination`
- L108 _private member_ `float& BakeDst;`
- L111 _public function_ `FBakedFloatValue(float& Dst)` — destination to bake
- L115 _public prototype_ `virtual bool SetValue(const mi::IData& ValueData) override;`

#### class `Mdl::Detail::FBakedVectorValue`  
`class FBakedVectorValue : public IBakeDestination`  
_L118-128_
- inherits: `IBakeDestination`
- L120 _private member_ `FVector3f& BakeDst;`
- L123 _public function_ `FBakedVectorValue(FVector3f& Dst)` — destination to bake
- L127 _public prototype_ `virtual bool SetValue(const mi::IData& ValueData) override;`

#### class `Mdl::Detail::FBakedLinearColorValue`  
`class FBakedLinearColorValue : public IBakeDestination`  
_L130-140_
- inherits: `IBakeDestination`
- L132 _private member_ `FLinearColor& BakeDst;`
- L135 _public function_ `FBakedLinearColorValue(FLinearColor& Dst)` — destination to bake
- L139 _public prototype_ `virtual bool SetValue(const mi::IData& ValueData) override;`

#### struct `Mdl::Detail::TGetValueTypeHelper`  
`template <> struct TGetValueTypeHelper<float>`  
_L146-151_
- L149 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::Float;` — Don't name these members 'ValueType' or the static analysis tool gets confused
- L150 _public typedef_ `using BakeType = FBakedFloatValue;`
- L156 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGBA;`
- L157 _public typedef_ `using BakeType = FBakedLinearColorValue;`
- L163 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGB;`
- L164 _public typedef_ `using BakeType = FBakedVectorValue;`

#### struct `Mdl::Detail::TGetValueTypeHelper`  
`template <> struct TGetValueTypeHelper<FLinearColor>`  
_L154-158_
- L149 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::Float;` — Don't name these members 'ValueType' or the static analysis tool gets confused
- L150 _public typedef_ `using BakeType = FBakedFloatValue;`
- L156 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGBA;`
- L157 _public typedef_ `using BakeType = FBakedLinearColorValue;`
- L163 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGB;`
- L164 _public typedef_ `using BakeType = FBakedVectorValue;`

#### struct `Mdl::Detail::TGetValueTypeHelper`  
`template <> struct TGetValueTypeHelper<FVector3f>`  
_L161-165_
- L149 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::Float;` — Don't name these members 'ValueType' or the static analysis tool gets confused
- L150 _public typedef_ `using BakeType = FBakedFloatValue;`
- L156 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGBA;`
- L157 _public typedef_ `using BakeType = FBakedLinearColorValue;`
- L163 _public member_ `static const Mdl::EValueType TypeValue = Mdl::EValueType::ColorRGB;`
- L164 _public typedef_ `using BakeType = FBakedVectorValue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Common`
- L12 _namespace_ `namespace mi`
- L15 _namespace_ `namespace base` (scope `mi`)
- L19 _namespace_ `namespace neuraylib` (scope `mi`)
- L26 _namespace_ `namespace Mdl`
- L104 _namespace_ `namespace Detail` (scope `Mdl`)
- L175 _typedef_ `typedef Detail::TGetValueTypeHelper<typename FMaterial::TMapEntry<T, D>::Type> GetValueHelper;` (scope `Mdl::FBakeParam::FBakeParam`)
- L176 _typedef_ `typedef typename GetValueHelper::BakeType BakeType;` (scope `Mdl::FBakeParam::FBakeParam`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/Common.h` (Private)


#### enum `Mdl::EValueType`  
`enum class EValueType`  
_L14-26_
- L16 _public enumerator_ `Float = 0`
- L18 _public enumerator_ `Float2` — 2 x Float32
- L20 _public enumerator_ `Float3` — 3 x Float32
- L22 _public enumerator_ `ColorRGB` — 3 x Float32 representing RGB color
- L24 _public enumerator_ `ColorRGBA` — 4 x Float32 representing RGBA color
- L25 _public enumerator_ `Count`

#### enum `Mdl::EParameterType`  
`enum class EParameterType`  
_L28-45_
- L30 _public enumerator_ `BaseColor = 0`
- L31 _public enumerator_ `Metallic`
- L32 _public enumerator_ `Specular`
- L33 _public enumerator_ `Roughness`
- L34 _public enumerator_ `Opacity`
- L35 _public enumerator_ `Emission`
- L36 _public enumerator_ `Normal`
- L37 _public enumerator_ `Displacement`
- L38 _public enumerator_ `ClearcoatWeight`
- L39 _public enumerator_ `ClearcoatRoughness`
- L40 _public enumerator_ `ClearcoatNormal`
- L41 _public enumerator_ `IOR`
- L42 _public enumerator_ `VolumeAbsorption`
- L43 _public enumerator_ `VolumeScattering`
- L44 _public enumerator_ `Count`

#### struct `Mdl::Detail::FCheckRes`  
`template <int LineNumber> struct FCheckRes`  
_L65-75_
- L67 _public function_ `FCheckRes(int Result)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define MDL_MSVC_EDITCONTINUE_WORKAROUND 0`
- L12 _namespace_ `namespace Mdl`
- L47 _prototype_ `const TCHAR* ToString(EValueType Type);` (scope `Mdl`)
- L48 _prototype_ `const TCHAR* ToString(EParameterType Type);` (scope `Mdl`)
- L49 _prototype_ `uint32 ComponentCount(EValueType Type);` (scope `Mdl`)
- L51 _macro_ `#define MDL_TOKENPASTE(x, y) x##y`
- L52 _macro_ `#define MDL_TOKENPASTE2(x, y) MDL_TOKENPASTE(x, y)`
- L55 _macro_ `#define MDL_CHECK_RESULT() const Mdl::Detail::FCheckRes<0> MDL_TOKENPASTE2(res, __LINE__)` — MSVC does not allow __LINE__ in template parameters when edit & continue is enabled (see C2975 @ MSDN)
- L56 _macro_ `#define MDL_CHECK_RESULT_MSG(msg) const Mdl::Detail::FCheckRes<0> MDL_TOKENPASTE2(res, __LINE__)`
- L58 _macro_ `#define MDL_CHECK_RESULT() const Mdl::Detail::FCheckRes<__LINE__> MDL_TOKENPASTE2(res, __LINE__)`
- L59 _macro_ `#define MDL_CHECK_RESULT_MSG(msg) const Mdl::Detail::FCheckRes<__LINE__> MDL_TOKENPASTE2(res, __LINE__)`
- L62 _namespace_ `namespace Detail` (scope `Mdl`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MapDistilHandler.h` (Private)


#### class `Mdl::IMapDistilHandler`  
`class IMapDistilHandler`  
_L21-36_
- L24 _public prototype_ `virtual ~IMapDistilHandler() = default;`
- L26 _public prototype_ `virtual void PreImport(const mi::neuraylib::IMaterial_definition& MDLMaterialDefinition, const mi::neuraylib::ICompiled_material& MDLMaterial, mi::neuraylib::ITransaction& MDLTransaction) = 0;`
- L33 _public prototype_ `virtual bool Import(const FString& MapName, bool bIsTexture, Mdl::FBakeParam& MapBakeParam) = 0;` — Import the map from the given bake path. @return True if the map was handled, otherwise will bake the map.
- L35 _public prototype_ `virtual void PostImport() = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace mi`
- L10 _namespace_ `namespace neuraylib` (scope `mi`)
- L17 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/Material.h` (Private)


#### struct `Mdl::FMaterial`  
`struct FMaterial`  
_L24-192_
- L26 _public typedef_ `using FInstantiateFunc = TFunction<FString(mi::neuraylib::INeuray* Neuray, mi::neuraylib::ITransaction*)>;`
- L27 _public typedef_ `using FPreProcessFunc = TFunction<void(mi::neuraylib::ITransaction* Transaction, TArray<FBakeParam>&)>;`
- L28 _public typedef_ `using FPostProcessFunc = TFunction<void(FMaterial&)>;`
- L93 _public typedef_ `using FDisplacementMapEntry = FNormalMapEntry;`
- L144 _public member_ `uint32 Id;`
- L145 _public member_ `FString Name;` — Name used to identify Material
- L149 _public member_ `FString BaseName;` — Base name in the Mdl db(full name is something like ::<ModuleName>::<BaseName>) note: separated from Name, because with resent Mdl SDK changes db name includes full signature(i.e. material-as-function argument list)
- L151 _public function_ `FString GetBaseName()`
- L156 _public member_ `int PreferredWidth;` — The preferred baking texture size.
- L157 _public member_ `int PreferredHeight;`
- L159 _public member_ `TMapEntry<FVector3f> BaseColor;`
- L160 _public member_ `TMapEntry<float, 0> Metallic;`
- L161 _public member_ `TMapEntry<float> Specular;`
- L162 _public member_ `TMapEntry<float> Roughness;`
- L163 _public member_ `TMapEntry<float> Opacity;`
- L164 _public member_ `TMapEntry<FVector3f, 0> Emission;`
- L165 _public member_ `TPropertyEntry<float> EmissionStrength;`
- L166 _public member_ `FNormalMapEntry Normal;`
- L167 _public member_ `FDisplacementMapEntry Displacement;`
- L169 _public member_ `FClearcoatEntry Clearcoat;`
- L170 _public member_ `FCarpaintEntry Carpaint;`
- L172 _public member_ `TPropertyEntry<FVector3f> IOR;`
- L173 _public member_ `TPropertyEntry<FVector3f, 0> Absorption;`
- L174 _public member_ `TMapEntry<FVector3f, 0> Scattering;`
- L176 _public member_ `float TilingFactor;`
- L177 _public member_ `FVector2D Tiling;`
- L179 _public member_ `FInstantiateFunc InstantiateFunction;`
- L180 _public member_ `FPreProcessFunc PreProcessFunction;`
- L181 _public member_ `FPostProcessFunc PostProcessFunction;`
- L183 _public prototype_ `FMaterial();`
- L185 _public prototype_ `void ExecutePostProcess();`
- L186 _public prototype_ `void Disable();`
- L187 _public prototype_ `bool IsDisabled() const;`
- L189 _public prototype_ `void SetPreferredSize(int Width, int Height);`
- L191 _public prototype_ `bool operator==(const FMaterial& Other) const;`
- L194 _function_ `inline FMaterial::FMaterial() : PreferredWidth(0) , PreferredHeight(0) , TilingFactor(1.f) , Tiling(1.f, 1.f)`
- L217 _function_ `inline bool FMaterial::operator==(const FMaterial& Other) const`
- L222 _function_ `inline void FMaterial::ExecutePostProcess()`
- L230 _function_ `inline void FMaterial::Disable()`
- L235 _function_ `inline bool FMaterial::IsDisabled() const`
- L240 _function_ `inline void FMaterial::SetPreferredSize(int Width, int Height)`

#### struct `Mdl::FMaterial::FExpressionEntry`  
`struct FExpressionEntry`  
_L30-42_
- L32 _public member_ `UMaterialExpression* Expression;`
- L33 _public member_ `int32 Index;`
- L34 _public member_ `bool bIsTexture;`
- L36 _public function_ `FExpressionEntry() : Expression(nullptr) , Index(0) , bIsTexture(false)`

#### struct `Mdl::FMaterial::TPropertyEntry`  
`template <typename ValueType, int DefaultValue = 255> struct TPropertyEntry`  
_L45-64_
- L47 _public typedef_ `using Type = ValueType;`
- L50 _public member_ `FExpressionEntry ExpressionData;` — Property will be defined from a material expression.
- L52 _public member_ `ValueType Value;` — Property is a simple value.
- L54 _public function_ `TPropertyEntry() : Value(DefaultValue / 255.f)`
- L60 _public prototype_ `bool WasProcessed() const;` — Returns true if a value was baked or an expression created.
- L62 _public prototype_ `bool WasValueBaked() const;` — Returns true if a map parameter was baked and the baked value is different from the default one.
- L63 _public prototype_ `bool HasExpression() const;`
- L250 _function_ `template <typename ValueType, int DefaultValue> bool FMaterial::TPropertyEntry<ValueType, DefaultValue>::WasValueBaked() const`
- L257 _function_ `template <typename ValueType, int DefaultValue> bool FMaterial::TPropertyEntry<ValueType, DefaultValue>::WasProcessed() const`
- L263 _function_ `template <typename ValueType, int DefaultValue> bool FMaterial::TPropertyEntry<ValueType, DefaultValue>::HasExpression() const`

#### struct `Mdl::FMaterial::TMapEntry`  
`template <typename ValueType, int DefaultValue = 255> struct TMapEntry : TPropertyEntry<ValueType, DefaultValue>`  
_L66-75_
- inherits: `TPropertyEntry<ValueType,DefaultValue>`
- L68 _public typedef_ `using Type = ValueType;`
- L70 _public member_ `Common::FTextureProperty Texture;`
- L73 _public prototype_ `bool WasProcessed() const;` — Returns true if a texture was baked or an expression created.
- L74 _public prototype_ `bool HasTexture() const;`
- L269 _function_ `template <typename ValueType, int DefaultValue> bool FMaterial::TMapEntry<ValueType, DefaultValue>::WasProcessed() const`
- L275 _function_ `template <typename ValueType, int DefaultValue> bool FMaterial::TMapEntry<ValueType, DefaultValue>::HasTexture() const`

#### struct `Mdl::FMaterial::FNormalMapEntry`  
`struct FNormalMapEntry`  
_L76-92_
- L79 _public member_ `FExpressionEntry ExpressionData;` — Texture will be defined from a material expression.
- L81 _public member_ `Common::FTextureProperty Texture;` — Texture will be defined from a texture source or path.
- L82 _public member_ `float Strength;`
- L84 _public function_ `FNormalMapEntry() : Strength(1.f)`
- L90 _public prototype_ `bool WasProcessed() const;` — Returns true if a texture was baked or an expression created.
- L91 _public prototype_ `bool HasExpression() const;`
- L280 _function_ `inline bool FMaterial::FNormalMapEntry::WasProcessed() const`
- L285 _function_ `inline bool FMaterial::FNormalMapEntry::HasExpression() const`

#### struct `Mdl::FMaterial::FTextureArrayEntry`  
`struct FTextureArrayEntry`  
_L95-108_
- L97 _public member_ `Common::FTextureProperty Texture;`
- L99 _public member_ `int Depth;` — Depth or number of slices of the array of textures.
- L101 _public member_ `float Size;` — Texture size of a single entry.
- L103 _public function_ `FTextureArrayEntry() : Depth(0) , Size(0)`

#### struct `Mdl::FMaterial::FClearcoatEntry`  
`struct FClearcoatEntry`  
_L109-114_
- L111 _public member_ `TMapEntry<float> Weight;`
- L112 _public member_ `TMapEntry<float> Roughness;`
- L113 _public member_ `FNormalMapEntry Normal;`

#### struct `Mdl::FMaterial::FCarpaintEntry`  
`struct FCarpaintEntry`  
_L115-142_
- L127 _public member_ `FTextureArrayEntry Flakes;`
- L128 _public member_ `FVector3f FlakesColorValue;`
- L129 _public member_ `FThetaSliceLUT ThetaFiLUT;`
- L130 _public member_ `int NumThetaI;`
- L131 _public member_ `int NumThetaF;`
- L132 _public member_ `int MaxThetaI;`
- L133 _public member_ `bool bEnabled;`
- L135 _public function_ `FCarpaintEntry() : NumThetaI(0) , NumThetaF(0) , MaxThetaI(0) , bEnabled(false)`

#### struct `Mdl::FMaterial::FCarpaintEntry::FThetaSliceLUT`  
`struct FThetaSliceLUT`  
_L117-126_
- L119 _public member_ `Common::FTextureProperty Texture;`
- L120 _public member_ `float TexelSize;`
- L122 _public function_ `FThetaSliceLUT() : TexelSize(0.f)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace mi`
- L13 _namespace_ `namespace neuraylib` (scope `mi`)
- L20 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MaterialCollection.h` (Private)


#### class `Mdl::FMaterialCollection`  
`class FMaterialCollection`  
_L10-50_
- L13 _public prototype_ `int32 Count() const;`
- L15 _public prototype_ `FMaterial& Create();`
- L16 _public prototype_ `void Reserve(int32 Count);`
- L17 _public prototype_ `void Remove(const FMaterial& Material);`
- L18 _public prototype_ `void RemoveAt(int32 Index);`
- L20 _public prototype_ `FMaterial& operator[](int32 Index);`
- L21 _public prototype_ `const FMaterial& operator[](int32 Index) const;`
- L24 _public prototype_ `template <typename Predicate> const FMaterial* FindByPredicate(Predicate Pred) const;`
- L27 _public member_ `FString Name;`
- L30 _private member_ `TArray<FMaterial> Data;`
- L34 _public function_ `FORCEINLINE TArray<FMaterial>::RangedForIteratorType begin()` — forward TArray ranges
- L38 _public function_ `FORCEINLINE TArray<FMaterial>::RangedForConstIteratorType begin() const`
- L42 _public function_ `FORCEINLINE TArray<FMaterial>::RangedForIteratorType end()`
- L46 _public function_ `FORCEINLINE TArray<FMaterial>::RangedForConstIteratorType end() const`
- L52 _function_ `inline int32 FMaterialCollection::Count() const`
- L57 _function_ `inline void FMaterialCollection::Reserve(int32 Count)`
- L62 _function_ `inline FMaterial& FMaterialCollection::Create()`
- L67 _function_ `inline void FMaterialCollection::Remove(const FMaterial& Material)`
- L72 _function_ `inline void FMaterialCollection::RemoveAt(int32 Index)`
- L77 _function_ `inline FMaterial& FMaterialCollection::operator[](int32 Index)`
- L82 _function_ `inline const FMaterial& FMaterialCollection::operator[](int32 Index) const`
- L88 _function_ `template <typename Predicate> const FMaterial* FMaterialCollection::FindByPredicate(Predicate Pred) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MaterialDistiller.h` (Private)


#### class `Mdl::IMaterialDistiller`  
`class IMaterialDistiller : FNoncopyable`  
_L23-59_
- inherits: `FNoncopyable`
- L26 _public typedef_ `using FProgressFunc = TFunction<void(const FString& MaterialName, int MaterialIndex)>;`
- L28 _public prototype_ `virtual ~IMaterialDistiller() = default;`
- L33 _public function_ `virtual void SetMapHanlder(IMapDistilHandler* MapHandler)` — Sets a custom map handler used for the distillation.
- L41 _public function_ `virtual void SetBakingSettings(uint32 Resolution, uint32 Samples)` — Sets the baking settings of the material to be baked. @param Resolution - resolution of the baked textures. @param Samples - MSAA samples for the baked textures.
- L46 _public function_ `virtual void SetMetersPerSceneUnit(float MetersPerSceneUnit)` — Sets the conversion factor for the baked textures.
- L55 _public function_ `virtual bool Distil(FMaterialCollection& Materials, FProgressFunc ProgressFunc) const` — Bakes and distills the materials by populating the material's properties. @param Materials - materials to bake, materials with an empty name will be ignored. @param ProgressFunc - callback called when a material has been distilled. @return true if the baking process was a success.

#### class `Mdl::FMaterialDistiller`  
`class FMaterialDistiller : public IMaterialDistiller`  
_L79-148_
- inherits: `IMaterialDistiller`
- L82 _public prototype_ `FMaterialDistiller() = default;`
- L84 _public prototype_ `virtual ~FMaterialDistiller();`
- L86 _public prototype_ `virtual void SetMapHanlder(IMapDistilHandler* MapHandler) override;`
- L88 _public prototype_ `virtual void SetBakingSettings(uint32 Resolution, uint32 Samples) override;`
- L90 _public prototype_ `virtual void SetMetersPerSceneUnit(float MetersPerSceneUnit) override;`
- L92 _public prototype_ `virtual bool Distil(FMaterialCollection& Materials, FProgressFunc ProgressFunc) const override;`
- L95 _private prototype_ `FMaterialDistiller(mi::base::Handle<mi::neuraylib::INeuray> Handle);`
- L97 _private prototype_ `void Distil(mi::neuraylib::ITransaction* Transaction, const FString& MaterialName, const FString& MaterialDbName, const FString& MaterialCompiledDbName, FMaterial& Material) const;`
- L103 _private prototype_ `void BakeConstantValue(mi::neuraylib::ITransaction* Transaction, const mi::neuraylib::IBaker* Baker, int MapType, FBakeParam& MapBakeParam) const;`
- L108 _private prototype_ `bool IsEmptyTexture(const mi::neuraylib::IBaker* Baker, EValueType ValueType) const;`
- L110 _private prototype_ `void BakeTexture(const FString& MaterialName,`
- L116 _private prototype_ `void DistilMaps(mi::neuraylib::ITransaction* Transaction, const FString& MaterialName, const mi::neuraylib::ICompiled_material* Material, FIntPoint BakeTextureSize, TArray<FBakeParam>& MaterialBakeParams) const;`
- L123 _private function_ `inline int ClosestPowerOfTwo(int Value)`
- L135 _private member_ `mi::base::Handle<mi::neuraylib::INeuray> Neuray;`
- L136 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_distiller_api> Handle;`
- L137 _private member_ `mi::base::Handle<mi::neuraylib::IImage_api> ImageApi;`
- L138 _private member_ `mutable mi::base::Handle<mi::neuraylib::ICanvas> BakeCanvases[(int)EValueType::Count];`
- L139 _private member_ `mutable mi::base::Handle<mi::neuraylib::ICanvas> PreBakeCanvases[(int)EValueType::Count];`
- L140 _private member_ `mutable FIntPoint BakeCanvasesSize[(int)EValueType::Count];`
- L142 _private member_ `IMapDistilHandler* MapHandler;`
- L143 _private member_ `uint32 BakeResolution;`
- L144 _private member_ `uint32 BakeSamples;`
- L145 _private member_ `float MetersPerSceneUnit;`
- L150 _function_ `inline void FMaterialDistiller::SetMapHanlder(IMapDistilHandler* Handler)`
- L155 _function_ `inline void FMaterialDistiller::SetBakingSettings(uint32 Resolution, uint32 Samples)`
- L161 _function_ `inline void FMaterialDistiller::SetMetersPerSceneUnit(float InMetersPerSceneUnit)`

#### class `Mdl::FMaterialDistiller`  
`class FMaterialDistiller : public IMaterialDistiller`  
_L170-172_
- inherits: `IMaterialDistiller`
- L82 _public prototype_ `FMaterialDistiller() = default;`
- L84 _public prototype_ `virtual ~FMaterialDistiller();`
- L86 _public prototype_ `virtual void SetMapHanlder(IMapDistilHandler* MapHandler) override;`
- L88 _public prototype_ `virtual void SetBakingSettings(uint32 Resolution, uint32 Samples) override;`
- L90 _public prototype_ `virtual void SetMetersPerSceneUnit(float MetersPerSceneUnit) override;`
- L92 _public prototype_ `virtual bool Distil(FMaterialCollection& Materials, FProgressFunc ProgressFunc) const override;`
- L95 _private prototype_ `FMaterialDistiller(mi::base::Handle<mi::neuraylib::INeuray> Handle);`
- L97 _private prototype_ `void Distil(mi::neuraylib::ITransaction* Transaction, const FString& MaterialName, const FString& MaterialDbName, const FString& MaterialCompiledDbName, FMaterial& Material) const;`
- L103 _private prototype_ `void BakeConstantValue(mi::neuraylib::ITransaction* Transaction, const mi::neuraylib::IBaker* Baker, int MapType, FBakeParam& MapBakeParam) const;`
- L108 _private prototype_ `bool IsEmptyTexture(const mi::neuraylib::IBaker* Baker, EValueType ValueType) const;`
- L110 _private prototype_ `void BakeTexture(const FString& MaterialName,`
- L116 _private prototype_ `void DistilMaps(mi::neuraylib::ITransaction* Transaction, const FString& MaterialName, const mi::neuraylib::ICompiled_material* Material, FIntPoint BakeTextureSize, TArray<FBakeParam>& MaterialBakeParams) const;`
- L123 _private function_ `inline int ClosestPowerOfTwo(int Value)`
- L135 _private member_ `mi::base::Handle<mi::neuraylib::INeuray> Neuray;`
- L136 _private member_ `mi::base::Handle<mi::neuraylib::IMdl_distiller_api> Handle;`
- L137 _private member_ `mi::base::Handle<mi::neuraylib::IImage_api> ImageApi;`
- L138 _private member_ `mutable mi::base::Handle<mi::neuraylib::ICanvas> BakeCanvases[(int)EValueType::Count];`
- L139 _private member_ `mutable mi::base::Handle<mi::neuraylib::ICanvas> PreBakeCanvases[(int)EValueType::Count];`
- L140 _private member_ `mutable FIntPoint BakeCanvasesSize[(int)EValueType::Count];`
- L142 _private member_ `IMapDistilHandler* MapHandler;`
- L143 _private member_ `uint32 BakeResolution;`
- L144 _private member_ `uint32 BakeSamples;`
- L145 _private member_ `float MetersPerSceneUnit;`
- L150 _function_ `inline void FMaterialDistiller::SetMapHanlder(IMapDistilHandler* Handler)`
- L155 _function_ `inline void FMaterialDistiller::SetBakingSettings(uint32 Resolution, uint32 Samples)`
- L161 _function_ `inline void FMaterialDistiller::SetMetersPerSceneUnit(float InMetersPerSceneUnit)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Mdl`
- L64 _namespace_ `namespace mi`
- L66 _namespace_ `namespace neuraylib` (scope `mi`)
- L77 _namespace_ `namespace Mdl`
- L168 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MaterialPrinter.h` (Private)


#### class `Mdl::FMaterialPrinter`  
`class FMaterialPrinter : protected IMaterialTraverser`  
_L33-99_
- inherits: `IMaterialTraverser`
- L36 _public prototype_ `FString Print(const mi::neuraylib::ICompiled_material& Material, mi::neuraylib::ITransaction* Transaction);`
- L38 _public prototype_ `FString Print(const mi::neuraylib::IMaterial_instance& Material, mi::neuraylib::IMdl_factory* MdlFactory, mi::neuraylib::ITransaction* Transaction);`
- L46 _protected prototype_ `void StageBegin(const mi::neuraylib::ICompiled_material& Material, ETraveralStage Stage, mi::neuraylib::ITransaction* Transaction) override;`
- L47 _protected prototype_ `void StageEnd(const mi::neuraylib::ICompiled_material& Material, ETraveralStage Stage, mi::neuraylib::ITransaction* Transaction) override;`
- L48 _protected prototype_ `void VisitBegin(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction) override;`
- L51 _protected prototype_ `void VisitChild(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, uint32 childrenCount, uint32 ChildIndex, mi::neuraylib::ITransaction* Transaction) override;`
- L53 _protected prototype_ `void VisitEnd(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction) override;`
- L59 _private prototype_ `FString EnumTypeToString(const mi::neuraylib::IType_enum* EnumType);` — Returns the type of an enum as string.
- L61 _private prototype_ `FString StructTypeToString(const mi::neuraylib::IType_struct* StructType, bool* bIsMaterialKeyword = nullptr);` — Returns the type of a struct as string.
- L63 _private prototype_ `FString AtomicTypeToString(const mi::neuraylib::IType_atomic* AtomicType);` — Returns the type of an elemental type as string.
- L65 _private prototype_ `FString VectorTypeToString(const mi::neuraylib::IType_vector* VectorType);` — Returns a vector type as string.
- L67 _private prototype_ `FString MatrixTypeToString(const mi::neuraylib::IType_matrix* MatrixType);` — Returns a matrix type as string.
- L69 _private prototype_ `FString ArrayTypeToString(const mi::neuraylib::IType_array* ArrayType);` — Returns an array type as string.
- L71 _private prototype_ `FString TypeToString(const mi::neuraylib::IType* Type);` — Returns the name of type as string.
- L73 _private prototype_ `void HandleModulesAndImports(const mi::base::Handle<const mi::neuraylib::IFunction_definition>& FuncDef, int Semantic, FString& FunctionName);`
- L74 _private prototype_ `void HandleVisitBeginExpression(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction);`
- L77 _private prototype_ `void HandleVisitBeginValue(const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction);`
- L79 _private prototype_ `void HandleVisitChildExpression(const FTraversalElement& Element, uint32 ChildIndex, mi::neuraylib::ITransaction* Transaction);`
- L81 _private prototype_ `void HandleVisitEndExpression(const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction);`
- L82 _private prototype_ `void HandleVisitEndParameter(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element);`
- L85 _private member_ `FString TraverseResult;`
- L86 _private member_ `ETraveralStage TraversalStage;`
- L87 _private member_ `uint32 Indent;`
- L89 _private member_ `TSet<FString> Imports;`
- L90 _private member_ `TSet<FString> UsedModules;`
- L91 _private member_ `TSet<FString> UsedResources;`
- L94 _private member_ `TMap<FString, FString> ParametersToInline;` — favor compiler created structure (may create invalid mdl)
- L95 _private member_ `FString TraverseInlineSwap;`
- L96 _private member_ `uint32 IndentInlineSwap;`
- L98 _private member_ `bool bKeepCompiledStructure;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace mi`
- L11 _namespace_ `namespace neuraylib` (scope `mi`)
- L25 _namespace_ `namespace base` (scope `mi`)
- L31 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MaterialTraverser.h` (Private)


#### class `Mdl::IMaterialTraverser`  
`class IMaterialTraverser`  
_L24-200_
- desc: A base class that implements traversal logic for compiled materials.
- L27 _public function_ `virtual ~IMaterialTraverser()`
- L103 _protected function_ `IMaterialTraverser()`
- L112 _protected prototype_ `void Traverse(const mi::neuraylib::ICompiled_material& Material, mi::neuraylib::ITransaction* Transaction);` — Traverses a compiled material and calls the corresponding virtual visit methods. This method is meant to be called by deriving class to start the actual traversal. @param Material - The material that is traversed. @param Transaction - The transaction from which to access material data.
- L121 _protected prototype_ `virtual void StageBegin(const mi::neuraylib::ICompiled_material& Material, ETraveralStage Stage, mi::neuraylib::ITransaction* Transaction) = 0;` — Called at the beginning of each traversal stage: Parameters, Temporaries and Body. @param Material - The material that is traversed. @param Stage - The stage that was entered. @param Transaction - The transaction from which to access material data.
- L132 _protected prototype_ `virtual void StageEnd(const mi::neuraylib::ICompiled_material& Material, ETraveralStage Stage, mi::neuraylib::ITransaction* Transaction) = 0;` — Called at the end of each traversal stage: Parameters, Temporaries and Body. @param Material - The material that is traversed. @param Stage - The stage that was finisheS. @param Transaction - The transaction from which to access material data.
- L141 _protected prototype_ `virtual void VisitBegin(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction) = 0;` — Called when the traversal reaches a new element. @param Material - The material that is traversed. @param Element - The element that was reached. @param Transaction - The transaction from which to access material data.
- L156 _protected prototype_ `virtual void VisitChild(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, uint32 ChildrenCount, uint32 ChildIndex, mi::neuraylib::ITransaction* Transaction) = 0;` — Occurs only if the current element has multiple child elements, e.g., a function call. In that case, the method is called before each of the children are traversed, e.g., before each argument of a function call. @param Material - The material that is traversed. @param Element - The currently traversed element with multiple children. @param ChildrenCount - Number of children of the current element. @param ChildIndex - The index of the child that will be traversed next. @param Transaction - The transaction from which to access material data.
- L166 _protected prototype_ `virtual void VisitEnd(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction) = 0;` — Called when the traversal reaches finishes an element. @param Material - The material that is traversed. @param Element - The element that was finished. @param Transaction - The transaction from which to access material data.
- L179 _protected prototype_ `FString GetParameterName(const mi::neuraylib::ICompiled_material& Material, uint32 Index, bool* bWasGenerated = nullptr) const;` — Gets the name of a parameter of the traversed material. @param  Material - The material that is traversed. @param  Index - Index of the parameter in the materials parameter list. @param  bWasGenerated - Optional output parameter that indicates whether the parameter was generated by the compiler rather than defined in the material definition. @return The parameter name.
- L188 _protected prototype_ `FString GetTemporaryName(uint32 Index) const;` — Gets the name of a temporary of the traversed material. Since the name is usually unknown, due to optimization, a proper name is generated. @param  Index - Index of the parameter in the materials temporary list. @return The temporary name.
- L199 _private prototype_ `void Traverse(const mi::neuraylib::ICompiled_material& Material, const FTraversalElement& Element, mi::neuraylib::ITransaction* Transaction);` — Recursive function that is used for the actual traversal. The names of templates are lost during compilation. Therefore, we generate numbered ones. @param Material - The material that is traversed.. @param Element - The element that is currently visited. @param Transaction - The transaction from which to access material data.
- L246 _function_ `inline FString IMaterialTraverser::GetTemporaryName(uint32 Index) const`

#### enum `Mdl::IMaterialTraverser::ETraveralStage`  
`enum class ETraveralStage`  
_L33-44_
- desc: Possible stages of the traversal of an compiled material
- L35 _public enumerator_ `Start = 0`
- L37 _public enumerator_ `Parameters` — Indicates that the parameters of the material are currently traversed
- L39 _public enumerator_ `Temporaries` — Indicates that the temporaries of the material are currently traversed
- L41 _public enumerator_ `Body` — Indicates that the main body of the material are currently traversed
- L43 _public enumerator_ `Finished` — Traversal is done

#### struct `Mdl::IMaterialTraverser::FParameter`  
`struct FParameter`  
_L50-58_
- desc: An internal structure that is passed to the user code while traversing. This struct is used while visiting the material parameters.
- L52 _public function_ `explicit FParameter(const mi::neuraylib::IValue* Value) : Value(Value)`
- L57 _public member_ `const mi::neuraylib::IValue* Value;`

#### struct `Mdl::IMaterialTraverser::FTemporary`  
`struct FTemporary`  
_L64-72_
- desc: An internal structure that is passed to the user code while traversing. This struct is used while visiting the materials temporaries.
- L66 _public function_ `explicit FTemporary(const mi::neuraylib::IExpression* Expression) : Expression(Expression)`
- L71 _public member_ `const mi::neuraylib::IExpression* Expression;`

#### struct `Mdl::IMaterialTraverser::FTraversalElement`  
`struct FTraversalElement`  
_L79-100_
- desc: Encapsulated to current element that is visited during the traversal It contains either an IExpression, an IValue, a Parameter or a Temporary while the others are nullptr.
- L81 _public prototype_ `explicit FTraversalElement(const mi::neuraylib::IExpression* Expression, uint32 SiblingCount = 1, uint32 SiblingIndex = 0);`
- L82 _public prototype_ `explicit FTraversalElement(const mi::neuraylib::IValue* Value, uint32 SiblingCount = 1, uint32 SiblingIndex = 0);`
- L83 _public prototype_ `explicit FTraversalElement(const FParameter* Parameter, uint32 SiblingCount = 1, uint32 SiblingIndex = 0);`
- L84 _public prototype_ `explicit FTraversalElement(const FTemporary* Temporary, uint32 SiblingCount = 1, uint32 SiblingIndex = 0);`
- L87 _public member_ `const mi::neuraylib::IExpression* Expression;` — Not nullptr if the current traversal element is an IExpression.
- L89 _public member_ `const mi::neuraylib::IValue* Value;` — Not nullptr if the current traversal element is an IValue.
- L92 _public member_ `const FParameter* Parameter;` — Not nullptr if the current traversal element is a Parameter. This can happen only in the ES_PARAMETERS stage.
- L95 _public member_ `const FTemporary* Temporary;` — Not nullptr if the current traversal element is a Parameter. This can happen only in the ES_TEMPORARAY stage.
- L97 _public member_ `uint32 SiblingCount;` — Total number of children at the parent of the currently traversed element.
- L99 _public member_ `uint32 SiblingIndex;` — Index of the currently traversed element in the list of children at the parent.
- L202 _function_ `inline IMaterialTraverser::FTraversalElement::FTraversalElement(const mi::neuraylib::IExpression* Expression, uint32 SiblingCount , uint32 SiblingIndex ) : Expression(Expression) , Value(nullptr) , Parameter(nullptr) , Temporary(nullptr) , SiblingCount(SiblingCount) , SiblingIndex(SiblingIndex)`
- L213 _function_ `inline IMaterialTraverser::FTraversalElement::FTraversalElement(const mi::neuraylib::IValue* Value, uint32 SiblingCount , uint32 SiblingIndex ) : Expression(nullptr) , Value(Value) , Parameter(nullptr) , Temporary(nullptr) , SiblingCount(SiblingCount) , SiblingIndex(SiblingIndex)`
- L224 _function_ `inline IMaterialTraverser::FTraversalElement::FTraversalElement(const FParameter* Parameter, uint32 SiblingCount , uint32 SiblingIndex ) : Expression(nullptr) , Value(nullptr) , Parameter(Parameter) , Temporary(nullptr) , SiblingCount(SiblingCount) , SiblingIndex(SiblingIndex)`
- L235 _function_ `inline IMaterialTraverser::FTraversalElement::FTraversalElement(const FTemporary* Temporary, uint32 SiblingCount , uint32 SiblingIndex ) : Expression(nullptr) , Value(nullptr) , Parameter(nullptr) , Temporary(Temporary) , SiblingCount(SiblingCount) , SiblingIndex(SiblingIndex)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace mi`
- L11 _namespace_ `namespace neuraylib` (scope `mi`)
- L19 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/MdlSdkDefines.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define MDLSDK_INCLUDES_START \`
- L17 _macro_ `#define MDLSDK_INCLUDES_END \`
- L30 _macro_ `#define MDLSDK_INCLUDES_END`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/SemanticParser.h` (Private)


#### struct `Mdl::FSemanticParser`  
`struct FSemanticParser`  
_L16-41_
- L18 _public member_ `FString PathPrefix;`
- L19 _public member_ `mi::base::Handle<const mi::neuraylib::IExpression_direct_call> ParentCall;`
- L20 _public member_ `mi::neuraylib::IFunction_definition::Semantics Semantic;`
- L21 _public member_ `mi::neuraylib::ITransaction* Transaction;`
- L22 _public member_ `const mi::neuraylib::ICompiled_material* Material;`
- L24 _public function_ `FSemanticParser(const char* BasePath, mi::neuraylib::ITransaction* Transaction, const mi::neuraylib::ICompiled_material* Material) : ParentCall(Lookup::GetCall(BasePath, Material)) , Semantic((mi::neuraylib::IFunction_definition::Semantics)Lookup::GetSemantic(Transaction, ParentCall.get())) , Transaction(Transaction) , Material(Material)`
- L34 _public function_ `void SetNextCall(const char* SubPath)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Mdl`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Private/mdl/Utility.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace mi`
- L10 _namespace_ `namespace neuraylib` (scope `mi`)
- L25 _namespace_ `namespace Mdl`
- L27 _namespace_ `namespace Util` (scope `Mdl`)
- L29 _prototype_ `FString GetMaterialDatabaseName(const FString& ModuleName, const FString& MaterialName, bool bIgnorePrefix = false);` (scope `Mdl::Util`)
- L30 _prototype_ `FString GetMaterialInstanceName(const FString& MaterialDbName);` (scope `Mdl::Util`)
- L31 _prototype_ `FString GetModuleName(const FString& MaterialDbName);` (scope `Mdl::Util`)
- L32 _prototype_ `FString GetTextureFileName(const mi::neuraylib::ITexture* Texture);` (scope `Mdl::Util`)
- L38 _prototype_ `bool CreateMaterialInstance(mi::neuraylib::ITransaction* Transaction, const FString& MaterialDbName, const FString& MaterialInstanceDbName);` (scope `Mdl::Util`) — Create a material instance from the material definition with the default arguments. @return true if a new material instance was created, false if was previously created.
- L43 _prototype_ `bool CompileMaterialInstance(mi::neuraylib::ITransaction* Transaction, mi::neuraylib::INeuray* Neuray, const FString& MaterialInstanceDbName, const FString& MaterialCompiledDbName, bool bIsClassCompilation, float MetersPerSceneUnit);` (scope `Mdl::Util`) — Compile a new material instance and stores it.
- L53 _prototype_ `mi::neuraylib::ICanvas* CreateCanvas(int Channels, int Width, int Height, mi::neuraylib::INeuray* Neuray, float Gamma = 1.f);` (scope `Mdl::Util`) — Creates a image canvas with the size.
- L58 _prototype_ `mi::neuraylib::ICanvas* CreateCanvas( int Channels, int Width, int Height, const void* Src, bool bFlipY, mi::neuraylib::INeuray* Neuray, float Gamma = 1.f);` (scope `Mdl::Util`) — Creates a image canvas with the given buffer data.
- L65 _prototype_ `FString CreateTexture(mi::neuraylib::ITransaction* Transaction, const FString& TextureDbName, mi::neuraylib::ICanvas* Canvas, bool bIsShared = false);` (scope `Mdl::Util`) — Creates a texture in the database with the given canvas. @return the texture's DB name.
- L70 _prototype_ `int GetChannelCount(const mi::neuraylib::ICanvas& Canvas);` (scope `Mdl::Util`)
- L72 _namespace_ `namespace Lookup` (scope `Mdl`)
- L78 _prototype_ `const mi::neuraylib::IExpression_direct_call* GetCall(const char* Path, const mi::neuraylib::ICompiled_material* Material, const mi::neuraylib::IExpression_direct_call* ParentCall = nullptr);` (scope `Mdl::Lookup`) — Looks up the sub expression 'path' within the compiled material starting at parent_call. If parent_call is nullptr, the  material will be traversed from the root.
- L86 _prototype_ `int GetSemantic(mi::neuraylib::ITransaction* Transaction, const mi::neuraylib::IExpression_direct_call* Call);` (scope `Mdl::Lookup`) — Returns the semantic of the function definition which corresponds to the given call or DS::UNKNOWN in case the expression is nullptr.
- L88 _prototype_ `const mi::neuraylib::IExpression* GetArgument(const mi::neuraylib::ICompiled_material* Material, const mi::neuraylib::IExpression_direct_call* ParentCall, const char* ArgumentName);` (scope `Mdl::Lookup`)
- L92 _prototype_ `FString GetValidSubExpression(const char* SubExpression, const mi::neuraylib::ICompiled_material* Material);` (scope `Mdl::Lookup`)
- L93 _prototype_ `FString GetValidSubExpression(const FString& SubExpression, const mi::neuraylib::ICompiled_material* Material);` (scope `Mdl::Lookup`)
- L95 _prototype_ `FString GetCallDefinition(const char* SubExpression, const mi::neuraylib::ICompiled_material* Material);` (scope `Mdl::Lookup`)
- L96 _prototype_ `FString GetCallDefinition(const FString& SubExpression, const mi::neuraylib::ICompiled_material* Material);` (scope `Mdl::Lookup`)
- L101 _namespace_ `namespace Util` (scope `Mdl`)
- L103 _function_ `inline FString GetMaterialDatabaseName(const FString& ModuleName, const FString& MaterialName, bool bIgnorePrefix)` (scope `Mdl::Util`)
- L110 _function_ `inline FString GetMaterialInstanceName(const FString& MaterialDbName)` (scope `Mdl::Util`)
- L115 _function_ `inline FString GetModuleName(const FString& MaterialDbName)` (scope `Mdl::Util`)
- L124 _namespace_ `namespace Lookup` (scope `Mdl`)
- L126 _function_ `inline FString GetValidSubExpression(const FString& SubExpression, const mi::neuraylib::ICompiled_material* Material)` (scope `Mdl::Lookup`)
- L131 _function_ `inline FString GetCallDefinition(const FString& SubExpression, const mi::neuraylib::ICompiled_material* Material)` (scope `Mdl::Lookup`)

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Public/MDLImporterModule.h` (Public)


#### class `IMDLImporterModule`  
`class IMDLImporterModule : public IModuleInterface`  
_L11-41_
- inherits: `IModuleInterface`
- L14 _public member_ `static const TCHAR* ModuleName;`
- L21 _public prototype_ `virtual FMDLImporter& GetMDLImporter() = 0;` — Access to the internal MDL importer. @return Returns internal importer logic.
- L23 _public prototype_ `virtual TUniquePtr<IMdlFileImporter> CreateFileImporter() = 0;`
- L25 _public prototype_ `virtual bool IsLoaded() = 0;`
- L32 _public prototype_ `static IMDLImporterModule& Get();` — Singleton-like access to MDLImporter @return Returns MDLImporter singleton instance, loading the module on demand if needed
- L39 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L43 _function_ `inline bool IMDLImporterModule::IsAvailable()`
- L48 _function_ `inline IMDLImporterModule& IMDLImporterModule::Get()`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Public/MDLImporterOptions.h` (Public)


#### class `UMDLImporterOptions`  
`class UMDLImporterOptions : public UObject`  
_L13-47_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L21 _public member_ `uint32 BakingResolution;` — `UPROPERTY(config, EditAnywhere, Category = "Bake options", meta = (DisplayName = "Baking resolution", ToolTip = "Resolution for baking procedural textures.", ClampMin = 128, ClampMax = 16384, FixedIncrement = 2))`
- L26 _public member_ `uint32 BakingSamples;` — `UPROPERTY(config, EditAnywhere, Category = "Bake options", meta = (DisplayName = "Baking samples", ToolTip = "Samples used for baking procedural textures.", ClampMin = 1, ClampMax = 16, FixedIncrement = 2))`
- L30 _public member_ `FDirectoryPath ResourcesDir;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced options", meta = (DisplayName = "Resource folder", ToolTip = "Path to look for resources: textures, light profiles and other."))`
- L34 _public member_ `FDirectoryPath ModulesDir;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced options", meta = (DisplayName = "Modules folder", ToolTip = "Path to look for extra MDL modules."))`
- L39 _public member_ `float MetersPerSceneUnit;` — `UPROPERTY(config, meta = (DisplayName = "Meters per scene unit", ToolTip = "The conversion ratio between meters and scene units for materials.", ClampMin = 0.01, ClampMax = 1000))` — hidden properties
- L43 _public member_ `bool bForceBaking;` — `UPROPERTY(config, meta = (DisplayName = "Force baking of all maps", ToolTip = "Always bakes the maps to textures instead of using material nodes."))`
- L45 _public prototype_ `static FString GetMdlSystemPath();`
- L46 _public prototype_ `static FString GetMdlUserPath();`

### `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Public/MDLMaterialImporter.h` (Public)


#### class `FMdlMaterialImporter`  
`class FMdlMaterialImporter`  
_L12-38_
- L15 _public prototype_ `static UMaterialInterface* ImportMaterialFromModule( UPackage* ParentPackage, EObjectFlags ObjectFlags, const FString& MdlModuleName, const FString& MdlDefinitionName, const UMDLImporterOptions& ImporterOptions );`
- L18 _public prototype_ `static void AddSearchPath( const FString& SearchPath );`
- L19 _public prototype_ `static void RemoveSearchPath( const FString& SearchPath );`

#### struct `FMdlMaterialImporter::FScopedSearchPath`  
`struct FScopedSearchPath`  
_L22-37_
- L24 _public function_ `explicit FScopedSearchPath( const FString& InSearchPath ) : SearchPath( InSearchPath )`
- L30 _public function_ `~FScopedSearchPath()`
- L36 _private member_ `FString SearchPath;`

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace UE`
- L42 _namespace_ `namespace Mdl` (scope `UE`)
- L44 _namespace_ `namespace Util` (scope `UE::Mdl`)
- L46 _prototype_ `FString ConvertFilePathToModuleName( const TCHAR* FilePath );` (scope `UE::Mdl::Util`)
