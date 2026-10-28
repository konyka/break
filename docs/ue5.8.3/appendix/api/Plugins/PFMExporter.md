# Plugins / PFMExporter

- module root: `Plugins/Runtime/WarpUtils/Source/PFMExporter`
- headers: 8; symbols: 36
- symbol kinds: class=8, delegate=2, function=5, member=6, prototype=15
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Projects, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Private/Blueprints/PFMExporterBlueprintAPIImpl.h` (Private)


#### class `UPFMExporterAPIImpl`  
`class UPFMExporterAPIImpl : public UObject , public IPFMExporterBlueprintAPI`  
_L15-45_
- reflection: `UCLASS()`
- inherits: `UObject,IPFMExporterBlueprintAPI`
- desc: Blueprint API interface implementation
- L36 _public prototype_ `virtual bool ExportPFM( UStaticMeshComponent* SrcMesh, USceneComponent* Origin, int Width, int Height, const FString& FileName ) override;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Export Static Mesh to PFM file"), Category = "PFMExporter")` — Generate PFM file from static mesh. The UV channel must be defined, assigned range 0..1 used as screen surface. Origin assigned by function arg, or by default used mesh parent. @param SrcMesh - Static mesh with assigned UV channel, used as export source of PFM file @param Origin - (Optional) Custom cave origin node, if not defined, used SrcMesh parent @param Width - Output PFM mesh texture width @param Height - Output PFM mesh texture height @param FileName - Output PFM file name @return true, if success

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Private/PFMExporterLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPFMExporter, Warning, Warning);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPFMExporter, Warning, Warning);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPFMExporter, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPFMExporter, Log, All);`

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Private/PFMExporterMesh.h` (Private)


#### class `FPFMExporterMesh`  
`class FPFMExporterMesh`  
_L8-38_
- L10 _private member_ `TArray<FVector> PFMPoints;`
- L11 _private member_ `int DimWidth;`
- L12 _private member_ `int DimHeight;`
- L14 _public prototype_ `FPFMExporterMesh(int Width, int Height);`
- L15 _public prototype_ `~FPFMExporterMesh();`
- L17 _public prototype_ `bool BeginExport_RenderThread(FRHICommandListImmediate& RHICmdList);`
- L18 _public prototype_ `bool FinishExport_RenderThread(FRHICommandListImmediate& RHICmdList);`
- L19 _public prototype_ `bool SaveToFile(const FString& FileName);`
- L21 _public function_ `inline bool IsValid() const`
- L25 _public function_ `inline FIntRect GetSize() const`
- L30 _public function_ `inline FTextureRHIRef GetTargetableTexture() const`
- L36 _private member_ `FTextureRHIRef RenderTargetTexture;`
- L37 _private member_ `FTextureRHIRef ShaderResourceTexture;`

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Private/PFMExporterModule.h` (Private)


#### class `FPFMExporterModule`  
`class FPFMExporterModule : public IPFMExporter`  
_L6-27_
- inherits: `IPFMExporter`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual bool ExportPFM( const FStaticMeshLODResources* SrcMeshResource, const FMatrix& MeshToOrigin, int PFMWidth, int PFMHeight, const FString& LocalFileName ) override;`

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Private/PFMExporterShader.h` (Private)


#### class `FPFMExporterShader`  
`class FPFMExporterShader`  
_L13-22_
- L16 _public prototype_ `static bool ApplyPFMExporter_RenderThread( FRHICommandListImmediate& RHICmdList, const FStaticMeshLODResources& SrcMeshResource, const FMatrix& MeshToOrigin, FPFMExporterMesh& DstPfmMesh );`

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Public/Blueprints/IPFMExporterBlueprintAPI.h` (Public)


#### class `UPFMExporterBlueprintAPI`  
`class UPFMExporterBlueprintAPI : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IPFMExporterBlueprintAPI`  
`class IPFMExporterBlueprintAPI`  
_L20-46_
- L39 _public prototype_ `virtual bool ExportPFM( UStaticMeshComponent* SrcMesh, USceneComponent* Origin, int Width, int Height, const FString& FileName ) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Export Static Mesh to PFM file"), Category = "PFMExporter")` — Generate PFM file from static mesh. The UV channel must be defined, assigned range 0..1 used as screen surface. Origin assigned by function arg, or by default used mesh parent. @param SrcMesh - Static mesh with assigned UV channel, used as export source of PFM file @param Origin - (Optional) Custom cave origin node, if not defined, used SrcMesh parent @param Width - Output PFM mesh texture width @param Height - Output PFM mesh texture height @param FileName - Output PFM file name @return true, if success

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Public/Blueprints/PFMExporterBlueprintLib.h` (Public)


#### class `UPFMExporterBlueprintLib`  
`class UPFMExporterBlueprintLib : public UBlueprintFunctionLibrary`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint API function library
- L21 _public prototype_ `static void GetAPI(TScriptInterface<IPFMExporterBlueprintAPI>& OutAPI);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "PFMExporter Module API"), Category = "nDisplay")` — Return Display Cluster API interface.

### `Plugins/Runtime/WarpUtils/Source/PFMExporter/Public/IPFMExporter.h` (Public)


#### class `IPFMExporter`  
`class IPFMExporter : public IModuleInterface`  
_L10-57_
- inherits: `IModuleInterface`
- L13 _public member_ `static constexpr auto ModuleName = TEXT("PFM`
- L21 _public function_ `static inline IPFMExporter& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public prototype_ `virtual bool ExportPFM( const FStaticMeshLODResources* SrcMeshResource, const FMatrix& MeshToOrigin, int PFMWidth, int PFMHeight, const FString& LocalFileName ) = 0;` — Generate PFM file from static mesh. The UV channel must be defined, assigned range 0..1 used as screen surface. @param SrcMeshResource - Source mesh with defined UV, used as PFM 3d source @param MeshToOrigin - Transform matrix convert mesh vertices to cave origin space @param PFMWidth - Output PFM mesh texture width @param PFMHeight - Output PFM mesh texture height @param LocalFileName - Output PFM file name (supported relative paths) @return - true, if export success
