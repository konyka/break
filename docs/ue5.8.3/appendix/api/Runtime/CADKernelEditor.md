# Runtime / CADKernelEditor

- module root: `Source/Runtime/Datasmith/CADKernel/Editor`
- headers: 3; symbols: 70
- symbol kinds: class=3, function=16, member=23, namespace=6, prototype=17, struct=3, typedef=2
- PrivateDependencyModuleNames: CADKernel, CADKernelEngine, ContentBrowser, EditorFramework, Engine, Slate, SlateCore, StaticMeshEditor, ToolMenus
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/Datasmith/CADKernel/Editor/Private/LegacyParametricSurfaceData.h` (Private)


#### struct `FLegacyParametricSceneParameters`  
`struct FLegacyParametricSceneParameters`  
_L14-28_
- L16 _public member_ `uint8 ModelCoordSys = (uint8)ECADKernelModelCoordSystem::ZUp_LeftHanded;`
- L17 _public member_ `float MetricUnit = 0.01f;`
- L18 _public member_ `float ScaleFactor = 1.0f;`
- L20 _public function_ `FCADKernelModelParameters ToCADKernel() const`

#### struct `FLegacyParametricMeshParameters`  
`struct FLegacyParametricMeshParameters`  
_L30-46_
- L32 _public member_ `bool bNeedSwapOrientation = false;`
- L33 _public member_ `bool bIsSymmetric = false;`
- L34 _public member_ `FVector SymmetricOrigin = FVector::ZeroVector;`
- L35 _public member_ `FVector SymmetricNormal = FVector::ZeroVector;`
- L37 _public function_ `FCADKernelMeshParameters ToCADKernel() const`

#### struct `FLegacyTessellationOptions`  
`struct FLegacyTessellationOptions`  
_L48-70_
- L50 _public member_ `float ChordTolerance;`
- L51 _public member_ `float MaxEdgeLength;`
- L52 _public member_ `float NormalTolerance;`
- L53 _public member_ `uint8 StitchingTechnique = (uint8)ECADKernelStitchingTechnique::StitchingNone;`
- L54 _public member_ `uint8 Tessellator = (uint8)ECADKernelTessellator::CADKernel;`
- L55 _public member_ `double GeometricTolerance = 0.001;`
- L56 _public member_ `double StitchingTolerance = 0.001;`
- L58 _public function_ `FCADKernelTessellationSettings ToCADKernel() const`

#### class `FLegacyParametricSurfaceData`  
`class FLegacyParametricSurfaceData`  
_L72-85_
- L74 _private prototype_ `UParametricSurfaceData* ToCADKernel() const;`
- L76 _private prototype_ `void Serialize(FArchive& Ar);`
- L78 _private member_ `FLegacyParametricSceneParameters SceneParameters;`
- L79 _private member_ `FLegacyParametricMeshParameters MeshParameters;`
- L80 _private member_ `FLegacyTessellationOptions LastTessellationOptions;`
- L81 _private member_ `TArray<uint8> RawData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Editor/Public/CADKernelRetessellateAction.h` (Public)


#### class `FCADKernelRetessellateAction`  
`class FCADKernelRetessellateAction`  
_L13-37_
- L16 _public prototype_ `static bool CanRetessellate(UStaticMesh* StaticMesh);`
- L18 _public prototype_ `static bool RetessellateArray(const TArray<UStaticMesh*>& StaticMeshes);`
- L19 _public function_ `static bool Retessellate(UStaticMesh* StaticMesh)`
- L24 _public prototype_ `static bool RetessellateArray(const TArray<FAssetData>& Assets);`
- L25 _public function_ `static bool Retessellate(const FAssetData& Asset)`
- L30 _public prototype_ `static bool RetessellateArray(const TArray<AStaticMeshActor*>& StaticMeshActors);`
- L31 _public function_ `static bool Retessellate(AStaticMeshActor* StaticMeshActor)`
- L36 _public prototype_ `static bool RetessellateLegacy(UStaticMesh& StaticMesh, FArchive& Ar);`

### `Source/Runtime/Datasmith/CADKernel/Editor/Public/ParametricSurfaceData.h` (Public)


#### class `UParametricSurfaceData`  
`class UParametricSurfaceData : public UAssetUserData`  
_L29-90_
- reflection: `UCLASS(meta = (DisplayName = "CADKernel Parametric Surface Data"))`
- inherits: `UAssetUserData`
- L35 _public function_ `virtual bool IsValid()`
- L37 _public function_ `void SetModelParameters(const FCADKernelModelParameters& InModelParameters)`
- L38 _public function_ `const FCADKernelModelParameters& GetModelParameters() const`
- L39 _public function_ `FCADKernelModelParameters& GetModelParameters()`
- L41 _public function_ `void SetMeshParameters(const FCADKernelMeshParameters& InMeshParameters)`
- L42 _public function_ `const FCADKernelMeshParameters& GetMeshParameters() const`
- L43 _public function_ `FCADKernelMeshParameters& GetMeshParameters()`
- L45 _public function_ `void SetLastTessellationSettings(const FCADKernelTessellationSettings& InTessellationSettings)`
- L46 _public function_ `const FCADKernelTessellationSettings& GetLastTessellationSettings() const`
- L48 _public prototype_ `TSharedPtr<UE::CADKernel::FModel> GetModel();`
- L50 _public prototype_ `virtual bool SetFromFile(const TCHAR* FilePath, bool bForTechSoft = false);`
- L53 _public prototype_ `bool SetModel(TSharedPtr<UE::CADKernel::FModel>& Model, double UnitModelToCentimeter = 1.);`
- L55 _public prototype_ `A3DRiRepresentationItem* GetRepresentation();`
- L56 _public prototype_ `bool SetRepresentation(A3DRiRepresentationItem* Representation, int32 MaterialID, double UnitRepresentationToCentimeter = 1.);`
- L58 _public prototype_ `bool Tessellate(UE::Geometry::FDynamicMesh3& MeshOut);`
- L59 _public prototype_ `bool Tessellate(FMeshDescription& MeshOut);`
- L61 _public prototype_ `bool Retessellate(const FCADKernelRetessellationSettings& Settings, UE::Geometry::FDynamicMesh3& MeshOut);`
- L62 _public prototype_ `bool Retessellate(const FCADKernelRetessellationSettings& Settings, FMeshDescription& MeshOut);`
- L69 _public function_ `virtual void SetRawData(const TArray<uint8>& InRawData, bool bForTechSoft = false)` — The SetRawData is only for internal use to facilitate the transition out of UDatasmithParametricSurfaceData into the new UParametricSurfaceData class
- L76 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _protected member_ `FCADKernelModelParameters ModelParameters;` — `UPROPERTY()`
- L83 _protected member_ `FCADKernelMeshParameters MeshParameters;` — `UPROPERTY()`
- L86 _protected member_ `FCADKernelTessellationSettings LastTessellationSettings;` — `UPROPERTY(EditAnywhere, Category = NURBS)`
- L88 _protected member_ `TArray<uint8> CADKernelRawData;`
- L89 _protected member_ `TArray<uint8> TechSoftRawData;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L25 _typedef_ `typedef void A3DRiRepresentationItem;`
- L26 _typedef_ `typedef void A3DAsmModelFile;`
