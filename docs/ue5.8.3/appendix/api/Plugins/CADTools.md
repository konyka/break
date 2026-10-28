# Plugins / CADTools

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/CADTools`
- headers: 3; symbols: 196
- symbol kinds: class=6, enum=8, enumerator=49, externvar=1, function=40, macro=1, member=67, namespace=3, prototype=15, struct=3, typedef=3
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, DatasmithCore

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADTools/Public/CADData.h` (Public)


#### enum `CADLibrary::ECADFormat`  
`enum class ECADFormat`  
_L19-42_
- L21 _public enumerator_ `ACIS`
- L22 _public enumerator_ `AUTOCAD`
- L23 _public enumerator_ `CATIA`
- L24 _public enumerator_ `CATIA_CGR`
- L25 _public enumerator_ `CATIA_3DXML`
- L26 _public enumerator_ `CATIAV4`
- L27 _public enumerator_ `CREO`
- L28 _public enumerator_ `DWG`
- L29 _public enumerator_ `DGN`
- L30 _public enumerator_ `TECHSOFT`
- L31 _public enumerator_ `IFC`
- L32 _public enumerator_ `IGES`
- L33 _public enumerator_ `INVENTOR`
- L34 _public enumerator_ `JT`
- L35 _public enumerator_ `N_X`
- L36 _public enumerator_ `MICROSTATION`
- L37 _public enumerator_ `PARASOLID`
- L38 _public enumerator_ `SOLID_EDGE`
- L39 _public enumerator_ `SOLIDWORKS`
- L40 _public enumerator_ `STEP`
- L41 _public enumerator_ `OTHER`

#### enum `CADLibrary::ECADParsingResult`  
`enum class ECADParsingResult : uint8`  
_L44-52_
- L46 _public enumerator_ `Unknown`
- L47 _public enumerator_ `Running`
- L48 _public enumerator_ `UnTreated`
- L49 _public enumerator_ `ProcessOk`
- L50 _public enumerator_ `ProcessFailed`
- L51 _public enumerator_ `FileNotFound`

#### enum `CADLibrary::EComponentType`  
`enum EComponentType : uint8`  
_L54-61_
- L56 _public enumerator_ `Reference = 0`
- L57 _public enumerator_ `Instance`
- L58 _public enumerator_ `OverriddeOccurence`
- L59 _public enumerator_ `Body`
- L60 _public enumerator_ `LastType`

#### enum `CADLibrary::ECADGraphicPropertyInheritance`  
`enum class ECADGraphicPropertyInheritance : uint8`  
_L63-68_
- L65 _public enumerator_ `Unset`
- L66 _public enumerator_ `FatherHerit`
- L67 _public enumerator_ `ChildHerit`

#### class `CADLibrary::FCADMaterial`  
`class FCADMaterial`  
_L74-88_
- L80 _public member_ `FString MaterialName;`
- L81 _public member_ `FColor Diffuse = FColor(255, 255, 255);`
- L82 _public member_ `FColor Ambient = FColor(255, 255, 255);`
- L83 _public member_ `FColor Specular = FColor(255, 255, 255);`
- L84 _public member_ `float Shininess = 0.f;`
- L85 _public member_ `float Transparency = 0.f;`
- L86 _public member_ `float Reflexion = 0.f;`
- L87 _public member_ `FString TextureName;`

#### struct `CADLibrary::FObjectDisplayDataId`  
`struct FObjectDisplayDataId`  
_L90-95_
- L92 _public member_ `FMaterialUId DefaultMaterialUId = 0;`
- L93 _public member_ `FMaterialUId MaterialUId = 0;`
- L94 _public member_ `FMaterialUId ColorUId = 0;`

#### class `CADLibrary::FArchiveGraphicProperties`  
`class FArchiveGraphicProperties`  
_L97-157_
- L100 _public prototype_ `FArchiveGraphicProperties() = default;`
- L102 _public function_ `FArchiveGraphicProperties(const FArchiveGraphicProperties& Parent) : ColorUId(Parent.ColorUId) , MaterialUId(Parent.MaterialUId)`
- L108 _public prototype_ `virtual ~FArchiveGraphicProperties() = default;`
- L113 _public member_ `FMaterialUId ColorUId = 0;`
- L114 _public member_ `FMaterialUId MaterialUId = 0;`
- L115 _public member_ `bool bIsRemoved = false;`
- L116 _public member_ `bool bShow = true;`
- L117 _public member_ `ECADGraphicPropertyInheritance Inheritance = ECADGraphicPropertyInheritance::Unset;`
- L122 _public function_ `void DefineGraphicsPropertiesFromNoOverwrite(const FArchiveGraphicProperties& Source)` — If a graphic property is undefined, define it with Source property
- L135 _public function_ `void SetGraphicProperties(const FArchiveGraphicProperties& Source)` — If a source property is defined, set the property with it
- L148 _public function_ `bool IsDeleted() const`
- L153 _public function_ `bool IsShown() const`

#### class `CADLibrary::FFileDescriptor`  
`class FFileDescriptor`  
_L159-297_
- L162 _public prototype_ `FFileDescriptor() = default;`
- L164 _public function_ `explicit FFileDescriptor(const TCHAR* InFilePath, const TCHAR* InConfiguration = nullptr, const TCHAR* InRootFolder = nullptr) : SourceFilePath(InFilePath) , Configuration(InConfiguration)`
- L176 _public function_ `void SetCacheFile(const FString& InCacheFilePath)` — Used define and then load the cache of the CAD File instead of the source file
- L181 _public function_ `bool operator==(const FFileDescriptor& Other) const`
- L186 _public function_ `bool IsEmpty()`
- L191 _public function_ `void Empty()`
- L205 _public function_ `uint32 GetDescriptorHash() const`
- L214 _public function_ `const FString& GetSourcePath() const`
- L219 _public function_ `bool HasConfiguration() const`
- L224 _public function_ `const FString& GetConfiguration() const`
- L229 _public function_ `void SetConfiguration(const FString& NewConfiguration)`
- L234 _public function_ `ECADFormat GetFileFormat() const`
- L239 _public function_ `bool CanReferenceOtherFiles() const`
- L244 _public function_ `const FString& GetPathOfFileToLoad() const`
- L257 _public function_ `void SetSourceFilePath(const FString& NewFilePath)` — Set the file path if SourceFilePath was not the real path
- L262 _public function_ `const FString& GetRootFolder() const`
- L267 _public function_ `const FString& GetFileName() const`
- L272 _public function_ `void ChangePath(const FString& OldPath, const FString& NewPath)`
- L286 _private member_ `FString SourceFilePath;` — e.g. d:/folder/content.jt
- L287 _private member_ `FString CacheFilePath;` — if the file has already been loaded
- L288 _private member_ `FString Name;` — content.jt
- L289 _private member_ `ECADFormat Format;` — ECADFormat::JT
- L290 _private member_ `bool bCanReferenceOtherFiles;`
- L291 _private member_ `FString Configuration;` — dedicated to JT or SW file to read the good configuration (SW) or only a sub-file (JT)
- L292 _private member_ `FString RootFolder;` — alternative folder where the file could be if its path is not valid.
- L294 _private member_ `mutable uint32 DescriptorHash = 0;`
- L296 _private prototype_ `void SetFileFormat(const FString& Extension);`

#### struct `CADLibrary::FTessellationData`  
`struct FTessellationData : public FArchiveGraphicProperties`  
_L309-329_
- inherits: `FArchiveGraphicProperties`
- desc: Helper struct to store tessellation data from CoreTech or CADKernel FBodyMesh and FTessellationData are design to manage mesh from CoreTech and CADKernel. FTessellationData is the mesh of a face FBodyMesh is the mesh of a body composed by an array of FTessellationData (one FTessellationData by body face) CoreTech mesh are defined surface by surface. The mesh is not connected CADKernel mesh is connected.
- L314 _public member_ `TArray<FVector3f> PositionArray;` — Empty with CADKernel as set in FBodyMesh, Set by CoreTech (this is only the vertices of the face)
- L317 _public member_ `TArray<int32> PositionIndices;` — Index of each vertex in FBody::VertexArray. Empty with CoreTech and filled by FillKioVertexPosition
- L320 _public member_ `TArray<int32> VertexIndices;` — Index of Vertices of each face in the local Vertices set (i.e. VerticesBodyIndex for CADKernel)
- L323 _public member_ `TArray<FVector3f> NormalArray;` — Normal of each vertex
- L326 _public member_ `TArray<FVector2f> TexCoordArray;` — UV coordinates of each vertex
- L328 _public member_ `int32 PatchId;`

#### class `CADLibrary::FBodyMesh`  
`class FBodyMesh`  
_L331-368_
- L334 _public function_ `FBodyMesh(FCadId InBodyID = 0) : BodyID(InBodyID)`
- L342 _public function_ `void AddGraphicPropertiesFrom(const FArchiveGraphicProperties& GraphicProperties)`
- L354 _public member_ `bool bIsFromCad = true;`
- L356 _public member_ `TArray<FVector3f> VertexArray;` — set by CADKernel, filled by FillKioVertexPosition that merges coincident vertices (CoreTechHelper)
- L357 _public member_ `TArray<FTessellationData> Faces;`
- L359 _public member_ `uint32 TriangleCount = 0;`
- L360 _public member_ `FCadId BodyID = 0;`
- L361 _public member_ `FCadUuid MeshActorUId = 0;`
- L363 _public member_ `TArray<int32> VertexIds;` — StaticMesh FVertexID NO Serialize, filled by FillKioVertexPosition or FillVertexPosition
- L364 _public member_ `TArray<int32> SymmetricVertexIds;` — StaticMesh FVertexID for sym part NO Serialize, filled by FillKioVertexPosition or FillVertexPosition
- L366 _public member_ `TSet<FMaterialUId> MaterialSet;`
- L367 _public member_ `TSet<FMaterialUId> ColorSet;`

#### Free symbols / members of external scopes

- L12 _typedef_ `using FCadId = uint32;` — Identifier defined in the input CAD file
- L13 _typedef_ `using FMaterialUId = int32;` — Material of Color unique Identifier defined based on the material or color properties
- L14 _typedef_ `using FCadUuid = uint32;` — Unique identifier that be used for the unreal asset name (Actor, Material)
- L16 _namespace_ `namespace CADLibrary`
- L71 _prototype_ `void GetCleanFilenameAndExtension(const FString& InFilePath, FString& OutFilename, FString& OutExtension);` (scope `CADLibrary`) — TODO: Remove from here and replace by DatasmithUtils::GetCleanFilenameAndExtension... But need to remove DatasmithCore dependancies
- L72 _prototype_ `FString GetExtension(const FString& InFilePath);` (scope `CADLibrary`)
- L370 _prototype_ `FMaterialUId BuildColorFastUId(uint32 ColorId, uint8 Alpha);` (scope `CADLibrary`)
- L372 _prototype_ `FMaterialUId BuildColorUId(const FColor& Color);` (scope `CADLibrary`)
- L373 _prototype_ `FMaterialUId BuildMaterialUId(const FCADMaterial& Material);` (scope `CADLibrary`)
- L375 _prototype_ `void SerializeBodyMeshSet(const TCHAR* Filename, TArray<FBodyMesh>& InBodySet);` (scope `CADLibrary`)
- L376 _prototype_ `void DeserializeBodyMeshFile(const TCHAR* Filename, TArray<FBodyMesh>& OutBodySet);` (scope `CADLibrary`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADTools/Public/CADOptions.h` (Public)


#### enum `CADLibrary::EMesher`  
`enum class EMesher`  
_L15-20_
- L17 _public enumerator_ `CADKernel`
- L18 _public enumerator_ `TechSoft`
- L19 _public enumerator_ `None`

#### enum `CADLibrary::EFailureReason`  
`enum class EFailureReason : uint8`  
_L22-27_
- L24 _public enumerator_ `Curve3D`
- L25 _public enumerator_ `Unknown`
- L26 _public enumerator_ `None`

#### enum `CADLibrary::EStitchingTechnique`  
`enum EStitchingTechnique`  
_L29-34_
- L31 _public enumerator_ `StitchingNone = 0`
- L32 _public enumerator_ `StitchingHeal`
- L33 _public enumerator_ `StitchingSew`

#### enum `CADLibrary::ESewOption`  
`enum class ESewOption : uint8`  
_L36-45_
- desc: Same as UE::CADKernel::ESewOption
- L38 _public enumerator_ `None = 0x00u` — No flags.
- L40 _public enumerator_ `ForceJoining = 0x01u`
- L41 _public enumerator_ `RemoveThinFaces = 0x02u`
- L42 _public enumerator_ `RemoveDuplicatedFaces = 0x04u`
- L44 _public enumerator_ `All = 0x07u`

#### class `CADLibrary::FImportParameters`  
`class FImportParameters`  
_L49-200_
- L52 _private member_ `double ChordTolerance;`
- L53 _private member_ `double MaxEdgeLength;`
- L54 _private member_ `double MaxNormalAngle;`
- L55 _private member_ `EStitchingTechnique StitchingTechnique;`
- L56 _private member_ `EMesher Mesher;`
- L57 _private member_ `FDatasmithUtils::EModelCoordSystem ModelCoordSys;`
- L60 _public member_ `static bool bGDisableCADKernelTessellation;`
- L61 _public member_ `static bool bGEnableCADCache;`
- L62 _public member_ `static bool bGEnableTimeControl;`
- L63 _public member_ `static bool bGOverwriteCache;`
- L64 _public member_ `static bool bGPreferJtFileEmbeddedTessellation;`
- L65 _public member_ `static bool bGSewMeshIfNeeded;`
- L66 _public member_ `static bool bGRemoveDuplicatedTriangle;`
- L67 _public member_ `static float GStitchingTolerance;`
- L68 _public member_ `static bool bGStitchingForceSew;`
- L69 _public member_ `static bool bGStitchingRemoveThinFaces;`
- L70 _public member_ `static bool bGStitchingRemoveDuplicatedFaces;`
- L71 _public member_ `static bool bGActivateThinZoneMeshing;`
- L72 _public member_ `static float GStitchingForceFactor;`
- L73 _public member_ `static float GUnitScale;`
- L74 _public member_ `static float GMeshingParameterFactor;`
- L75 _public member_ `static int32 GMaxMaterialCountPerMesh;`
- L76 _public member_ `static bool bValidationProcess;`
- L79 _public function_ `FImportParameters(FDatasmithUtils::EModelCoordSystem NewCoordinateSystem = FDatasmithUtils::EModelCoordSystem::ZUp_RightHanded) : ChordTolerance(0.2) , MaxEdgeLength(0.0) , MaxNormalAngle(20.0) , StitchingTechnique(EStitchingTechnique::StitchingNone) , Mesher(EMesher::TechSoft) , ModelCoordSys(NewCoordinateSystem)`
- L89 _public function_ `FImportParameters(const FImportParameters& InParamneters, EMesher InMesher) : ChordTolerance(InParamneters.ChordTolerance) , MaxEdgeLength(InParamneters.MaxEdgeLength) , MaxNormalAngle(InParamneters.MaxNormalAngle) , StitchingTechnique(InParamneters.StitchingTechnique) , Mesher(InMesher) , ModelCoordSys(InParamneters.ModelCoordSys)`
- L99 _public function_ `void SetTesselationParameters(double InChordTolerance, double InMaxEdgeLength, double InMaxNormalAngle, EStitchingTechnique InStitchingTechnique)`
- L108 _public function_ `void SetTesselationParameters(double InChordTolerance, double InMaxEdgeLength, double InMaxNormalAngle, EStitchingTechnique InStitchingTechnique, EMesher InMesher)`
- L114 _public function_ `uint32 GetHash() const`
- L164 _public function_ `double GetChordTolerance() const`
- L169 _public function_ `double GetMaxNormalAngle() const`
- L174 _public function_ `double GetMaxEdgeLength() const`
- L179 _public function_ `EStitchingTechnique GetStitchingTechnique() const`
- L184 _public function_ `EMesher GetMesher() const`
- L189 _public function_ `FDatasmithUtils::EModelCoordSystem GetModelCoordSys() const`
- L194 _public function_ `void SetModelCoordinateSystem(FDatasmithUtils::EModelCoordSystem NewCoordinateSystem)`

#### struct `CADLibrary::FMeshParameters`  
`struct FMeshParameters`  
_L251-257_
- L253 _public member_ `bool bNeedSwapOrientation = false;`
- L254 _public member_ `bool bIsSymmetric = false;`
- L255 _public member_ `FVector3f SymmetricOrigin;`
- L256 _public member_ `FVector3f SymmetricNormal;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace CADLibrary`
- L13 _externvar_ `extern int32 GMaxImportThreads;` (scope `CADLibrary`)
- L47 _prototype_ `ENUM_CLASS_FLAGS(ESewOption);` (scope `CADLibrary`)
- L132 _function_ `friend FArchive& operator<<(FArchive& Ar, FImportParameters& ImportParameters)` (scope `CADLibrary`)
- L202 _namespace_ `namespace SewOption` (scope `CADLibrary`)
- L205 _function_ `static ESewOption GetFromImportParameters()` (scope `CADLibrary::SewOption`)
- L229 _function_ `inline FString BuildCadCachePath(const TCHAR* CachePath, uint32 FileHash)` (scope `CADLibrary`)
- L235 _function_ `inline FString BuildCacheFilePath(const TCHAR* CachePath, const TCHAR* Folder, uint32 BodyHash, const EMesher Mesher)` (scope `CADLibrary`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADTools/Public/CADToolsModule.h` (Public)


#### class `FCADToolsModule`  
`class FCADToolsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L11 _public prototype_ `static FCADToolsModule& Get();`
- L12 _public prototype_ `static bool IsAvailable();`
- L14 _public prototype_ `static uint32 GetCacheVersion();`

#### Free symbols / members of external scopes

- L6 _macro_ `#define CADTOOLS_MODULE_NAME TEXT("CADTools")`
