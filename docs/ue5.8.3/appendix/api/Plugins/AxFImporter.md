# Plugins / AxFImporter

- module root: `Plugins/Enterprise/AxFImporter/Source/AxFImporter`
- headers: 7; symbols: 64
- symbol kinds: class=6, delegate=1, enum=1, enumerator=2, function=6, member=7, namespace=1, prototype=38, typedef=2
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, EditorFramework, Engine, ImageCore, InputCore, MainFrame, MaterialEditor, MessageLog, Projects, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/AxFFileImporter.h` (Private)


#### class `IAxFFileImporter`  
`class IAxFFileImporter`  
_L16-31_
- L19 _public typedef_ `using FProgressFunc = TFunction<void(const FString& MsgName, int MaterialIndex)>;`
- L21 _public function_ `virtual ~IAxFFileImporter()`
- L23 _public prototype_ `virtual bool OpenFile(const FString& InFileName, const UAxFImporterOptions& InImporterOptions) = 0;`
- L24 _public prototype_ `virtual int GetMaterialCountInFile() = 0;`
- L25 _public prototype_ `virtual bool ImportMaterials(UObject* ParentPackage, EObjectFlags Flags, FProgressFunc ProgressFunc = nullptr) = 0;`
- L26 _public prototype_ `virtual void SetTextureFactory(UTextureFactory* TextureFactory) = 0;`
- L27 _public prototype_ `virtual TMap<FString, UMaterialInterface*> GetCreatedMaterials() = 0;`
- L28 _public prototype_ `virtual bool Reimport(const FString& InFileName, const UAxFImporterOptions& InImporterOptions, UMaterialInterface* OutMaterial) = 0;`
- L30 _public prototype_ `virtual const TArray<AxFImporterLogging::FLogMessage> GetLogMessages() = 0;`

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/AxFImporter.h` (Private)


#### class `FAxFImporter`  
`class FAxFImporter`  
_L9-20_
- L12 _public prototype_ `FAxFImporter(const FString& PluginPath);`
- L13 _public prototype_ `~FAxFImporter();`
- L15 _public prototype_ `IAxFFileImporter* Create();`
- L17 _public prototype_ `bool IsLoaded();`
- L19 _public member_ `void* AxFDecodingHandle = nullptr;`

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/AxFImporterFactory.h` (Private)


#### class `UAxFImporterFactory`  
`class UAxFImporterFactory : public UFactory, public FReimportHandler`  
_L17-46_
- reflection: `UCLASS(HideCategories = Object, CollapseCategories)`
- inherits: `UFactory,FReimportHandler`
- L22 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L24 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L27 _public prototype_ `virtual void CleanUp() override;`
- L31 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L33 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L35 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L39 _private prototype_ `bool LoadMaterials(IAxFFileImporter* Importer, UObject* InPackage, EObjectFlags InFlags, const FString& InFilename, const UAxFImporterOptions& InImporterOptions, FFeedbackContext& Warn);`
- L42 _private prototype_ `void SendAnalytics(int32 ImportDurationInSeconds, bool bImportSuccess, const FString& InFilename) const;`
- L45 _private member_ `IAxFImporterModule* AxFImporterModule;`

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/AxFImporterOptions.h` (Private)


#### class `UAxFImporterOptions`  
`class UAxFImporterOptions : public UObject`  
_L13-23_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L22 _public member_ `float MetersPerSceneUnit;` — `UPROPERTY(config, meta = (DisplayName = "Meters per scene unit", ToolTip = "The conversion ratio between meters and scene units for materials.", ClampMin = 0.01, ClampMax = 1000))` — hidden properties

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/UI/AxFOptionsWindow.h` (Private)


#### class `SAxFOptionsWindow`  
`class SAxFOptionsWindow : public SCompoundWidget`  
_L8-41_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SAxFOptionsWindow)`
- L13 _public prototype_ `SLATE_ARGUMENT(UObject*, ImportOptions);`
- L14 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow);`
- L15 _public prototype_ `SLATE_ARGUMENT(FText, FileNameText);`
- L16 _public prototype_ `SLATE_ARGUMENT(FText, FilePathText);`
- L17 _public prototype_ `SLATE_ARGUMENT(FText, PackagePathText);`
- L18 _public prototype_ `SLATE_ARGUMENT(int, MaterialCount);`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L24 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L28 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L30 _public prototype_ `bool ShouldImport() const;`
- L33 _private prototype_ `FReply OnImport();`
- L34 _private prototype_ `FReply OnCancel();`
- L35 _private prototype_ `FReply OnHelp(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);`
- L38 _private member_ `UObject* ImportOptions;`
- L39 _private member_ `TWeakPtr<SWindow> Window;`
- L40 _private member_ `bool bShouldImport;`
- L43 _function_ `inline bool SAxFOptionsWindow::ShouldImport() const`

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/common/Logging.h` (Private)


#### enum `AxFImporterLogging::EMessageSeverity`  
`enum class EMessageSeverity`  
_L12-16_
- L14 _public enumerator_ `Warning`
- L15 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFImporter, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFImporter, Log, All);`
- L10 _namespace_ `namespace AxFImporterLogging`
- L17 _typedef_ `using FLogMessage = TTuple<EMessageSeverity, FString>;` (scope `AxFImporterLogging`)

### `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Public/AxFImporterModule.h` (Public)


#### class `IAxFImporterModule`  
`class IAxFImporterModule : public IModuleInterface`  
_L11-31_
- inherits: `IModuleInterface`
- L14 _public member_ `static const TCHAR* ModuleName;`
- L16 _public prototype_ `virtual FAxFImporter& GetAxFImporter() = 0;`
- L18 _public prototype_ `virtual IAxFFileImporter* CreateFileImporter() = 0;`
- L20 _public prototype_ `virtual bool IsLoaded() = 0;`
- L22 _public prototype_ `static IAxFImporterModule& Get();`
- L29 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L33 _function_ `inline bool IAxFImporterModule::IsAvailable()`
- L38 _function_ `inline IAxFImporterModule& IAxFImporterModule::Get()`
