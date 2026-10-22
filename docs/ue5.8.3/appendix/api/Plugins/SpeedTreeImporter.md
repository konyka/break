# Plugins / SpeedTreeImporter

- module root: `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter`
- headers: 4; symbols: 52
- symbol kinds: class=5, enum=2, enumerator=5, function=3, member=19, prototype=18
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, MainFrame, MeshDescription, Slate, SlateCore, StaticMeshDescription, UnrealEd

### `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter/Classes/ReimportSpeedTreeFactory.h` (Public)


#### class `UReimportSpeedTreeFactory`  
`class UReimportSpeedTreeFactory : public USpeedTreeImportFactory, public FReimportHandler`  
_L16-32_
- reflection: `UCLASS(collapsecategories)`
- inherits: `USpeedTreeImportFactory,FReimportHandler`
- L21 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L22 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L23 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L24 _private prototype_ `virtual int32 GetPriority() const override;`
- L25 _private function_ `virtual TObjectPtr<UObject>* GetFactoryObject() const override`
- L30 _private member_ `mutable TObjectPtr<UObject> GCMark{this};`

### `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter/Classes/SpeedTreeImportData.h` (Public)


#### enum `EImportGeometryType`  
`enum EImportGeometryType : int`  
_L28-33_
- reflection: `UENUM()`
- desc: Geometry import type
- L30 _public enumerator_ `IGT_3D UMETA(DisplayName = "3D LODs")`
- L31 _public enumerator_ `IGT_Billboards UMETA(DisplayName = "Billboards")`
- L32 _public enumerator_ `IGT_Both UMETA(DisplayName = "Both")`

#### enum `EImportLODType`  
`enum EImportLODType : int`  
_L38-42_
- reflection: `UENUM()`
- desc: LOD type
- L40 _public enumerator_ `ILT_PaintedFoliage UMETA(DisplayName = "Painted Foliage")`
- L41 _public enumerator_ `ILT_IndividualActors UMETA(DisplayName = "Individual Actors")`

#### class `USpeedTreeImportData`  
`class USpeedTreeImportData : public UAssetImportData`  
_L46-111_
- reflection: `UCLASS(BlueprintType, config=EditorPerProjectUserSettings, perObjectConfig, MinimalAPI)`
- inherits: `UAssetImportData`
- L52 _private member_ `float TreeScale;` — `UPROPERTY(EditAnywhere, config, Category=Mesh, meta=(DisplayName = "Tree Scale"))` — Specify the tree scale
- L64 _private member_ `uint32 IncludeCollision : 1;` — `UPROPERTY(EditAnywhere, config, Category=Mesh, meta = (DisplayName = "Include Collision", SpeedTreeVersion = "8"))`
- L68 _private member_ `uint32 MakeMaterialsCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category=Materials, meta = (DisplayName = "Create Materials", SpeedTreeVersion = "8"))`
- L72 _private member_ `uint32 IncludeNormalMapCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Normal Maps"))`
- L76 _private member_ `uint32 IncludeDetailMapCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Detail Maps"))`
- L80 _private member_ `uint32 IncludeSpecularMapCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Specular Maps"))`
- L84 _private member_ `uint32 IncludeBranchSeamSmoothing : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Branch Seam Smoothing"))`
- L88 _private member_ `uint32 IncludeSpeedTreeAO : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include SpeedTree AO"))`
- L92 _private member_ `uint32 IncludeColorAdjustment : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Random Color Variation"))`
- L96 _private member_ `uint32 IncludeSubsurface : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Subsurface", SpeedTreeVersion = "8"))`
- L100 _private member_ `uint32 IncludeVertexProcessingCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "MakeMaterialsCheck", DisplayName = "Include Vertex Processing", SpeedTreeVersion = "8"))`
- L104 _private member_ `uint32 IncludeWindCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "IncludeVertexProcessingCheck", DisplayName = "Include Wind"))`
- L108 _private member_ `uint32 IncludeSmoothLODCheck : 1;` — `UPROPERTY(EditAnywhere, config, Category = Materials, meta = (EditCondition = "IncludeVertexProcessingCheck", DisplayName = "Include Smooth LOD"))`
- L110 _private prototype_ `void CopyFrom(USpeedTreeImportData* Other);`

#### class `FSpeedTreeImportDataDetails`  
`class FSpeedTreeImportDataDetails : public IDetailCustomization`  
_L115-131_
- inherits: `IDetailCustomization`
- L119 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L122 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L125 _private prototype_ `FSpeedTreeImportDataDetails();`
- L127 _private prototype_ `void OnForceRefresh();`
- L129 _private member_ `USpeedTreeImportData *SpeedTreeImportData;`
- L130 _private member_ `class IDetailLayoutBuilder* CachedDetailBuilder;`

### `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter/Classes/SpeedTreeImportFactory.h` (Public)


#### class `USpeedTreeImportFactory`  
`class USpeedTreeImportFactory : public UFactory`  
_L18-43_
- reflection: `UCLASS(BlueprintType, hidecategories=Object)`
- inherits: `UFactory`
- L23 _private prototype_ `virtual FText GetDisplayName() const override;`
- L24 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L26 _private prototype_ `virtual bool DoesSupportClass(UClass * Class) override;`
- L27 _private prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L28 _private prototype_ `virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L30 _private prototype_ `UObject* FactoryCreateBinary7(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled);`
- L31 _private prototype_ `UObject* FactoryCreateBinary8(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled);`
- L32 _private prototype_ `UObject* FactoryCreateBinary9(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled);`
- L35 _private prototype_ `USpeedTreeImportData* GetAutomatedImportOptions(USpeedTreeImportData* ExistingImportData) const;`
- L40 _public member_ `TSet<UPackage*> LoadedPackages;`
- L41 _public member_ `UMaterialInterface* TemplateMaterial;`
- L42 _public member_ `UMaterialInterface* TemplateBillboardMaterial;`

### `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter/Public/ISpeedTreeImporter.h` (Public)


#### class `ISpeedTreeImporter`  
`class ISpeedTreeImporter : public IModuleInterface`  
_L12-38_
- inherits: `IModuleInterface`
- desc: The public interface of the SpeedTreeImporter module
- L22 _public function_ `static inline ISpeedTreeImporter& Get()` — Singleton-like access to ISpeedTreeImporter @return Returns SpeedTreeImporter singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
