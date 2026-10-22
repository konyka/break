# Plugins / WireInterface2026_0

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface`
- headers: 5; symbols: 240
- symbol kinds: class=9, delegate=1, enum=5, enumerator=19, externvar=3, function=58, macro=15, member=44, namespace=9, prototype=67, struct=3, typedef=7

### `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface/Private/AliasModelToCADKernelConverter.h` (Private)


#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FAliasModelToCADKernelConverter`  
`class FAliasModelToCADKernelConverter : public FCADModelToCADKernelConverterBase`  
_L34-68_
- inherits: `FCADModelToCADKernelConverterBase`
- L38 _public prototype_ `FAliasModelToCADKernelConverter(const FDatasmithTessellationOptions& Options, CADLibrary::FImportParameters InImportParameters);`
- L41 _public prototype_ `virtual bool Tessellate(const CADLibrary::FMeshParameters& InMeshParameters, FMeshDescription& OutMeshDescription) override;`
- L42 _public prototype_ `virtual bool RepairTopology() override;`
- L44 _public prototype_ `virtual bool AddGeometry(const CADLibrary::FCADModelGeometry& Geometry) override;`
- L47 _public prototype_ `bool AddBRep(const FAlDagNodePtr& DagNode, const FColor& Color, EAliasObjectReference ObjectReference);`
- L48 _public prototype_ `bool AddBRep(const FAlDagNodePtr& DagNode, uint32 SlotID, EAliasObjectReference ObjectReference);`
- L51 _protected prototype_ `TSharedPtr<UE::CADKernel::FTopologicalEdge> AddEdge(const AlTrimCurve& TrimCurve, TSharedPtr<UE::CADKernel::FSurface>& CarrierSurface);`
- L53 _protected prototype_ `TSharedPtr<UE::CADKernel::FTopologicalLoop> AddLoop(const AlTrimBoundary& TrimBoundary, TSharedPtr<UE::CADKernel::FSurface>& CarrierSurface, const bool bIsExternal);`
- L59 _protected prototype_ `void LinkEdgesLoop(const AlTrimBoundary& TrimBoundary, UE::CADKernel::FTopologicalLoop& Loop);` — Build face's links with its neighbor have to be done after the loop is finalize. This is to avoid to link an edge with another and then to delete it...
- L61 _protected prototype_ `TSharedPtr<UE::CADKernel::FTopologicalFace> AddTrimRegion(const AlTrimRegion& InTrimRegion, EAliasObjectReference InObjectReference, const AlMatrix4x4& InAlMatrix, bool bInOrientation);`
- L62 _protected prototype_ `void AddFace(const AlSurface& InSurface, EAliasObjectReference InObjectReference, const AlMatrix4x4& InAlMatrix, bool bInOrientation, TSharedRef<UE::CADKernel::FShell>& Shell);`
- L63 _protected prototype_ `void AddShell(const AlShell& InShell, EAliasObjectReference InObjectReference, const AlMatrix4x4& InAlMatrix, bool bInOrientation, TSharedRef<UE::CADKernel::FShell>& Shell);`
- L66 _protected member_ `int32 LastFaceId = 1;`
- L67 _protected member_ `TMap<void*, TSharedPtr<UE::CADKernel::FTopologicalEdge>> AlEdge2CADKernelEdge;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CADKernel` (scope `UE`)
- L31 _namespace_ `namespace UE_DATASMITHWIRETRANSLATOR_NAMESPACE`

### `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface/Private/AliasModelToTechSoftConverter.h` (Private)


#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FAliasModelToTechSoftConverter`  
`class FAliasModelToTechSoftConverter : public FCADModelToTechSoftConverterBase`  
_L31-54_
- inherits: `FCADModelToTechSoftConverterBase`
- L35 _public function_ `FAliasModelToTechSoftConverter(CADLibrary::FImportParameters InImportParameters) : FCADModelToTechSoftConverterBase(InImportParameters)`
- L40 _public prototype_ `virtual bool AddGeometry(const CADLibrary::FCADModelGeometry& Geometry) override;`
- L42 _public prototype_ `bool AddBRep(const FAlDagNodePtr& DagNode, const FColor& Color, EAliasObjectReference ObjectReference);`
- L43 _public prototype_ `bool AddBRep(const FAlDagNodePtr& DagNode, uint32 SlotID, EAliasObjectReference ObjectReference);`
- L46 _protected member_ `TMap<void*, A3DTopoCoEdge*> AlEdgeToTSCoEdge;`
- L48 _protected prototype_ `A3DTopoFace* AddTrimRegion(const AlTrimRegion& InTrimRegion, const FColor& Color, EAliasObjectReference InObjectReference, const AlMatrix4x4& InAlMatrix);`
- L49 _protected prototype_ `A3DTopoLoop* CreateTopoLoop(const AlTrimBoundary& TrimBoundary);`
- L50 _protected prototype_ `A3DTopoCoEdge* CreateEdge(const AlTrimCurve& TrimCurve);`
- L51 _protected prototype_ `A3DCrvBase* CreateCurve(const AlTrimCurve& TrimCurve);`
- L53 _protected prototype_ `void LinkEdgesLoop(const AlTrimBoundary& TrimBoundary);`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef void A3DTopoCoEdge;`
- L23 _typedef_ `typedef void A3DTopoFace;`
- L24 _typedef_ `typedef void A3DTopoLoop;`
- L26 _typedef_ `typedef void A3DCrvBase;`
- L28 _namespace_ `namespace UE_DATASMITHWIRETRANSLATOR_NAMESPACE`

### `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface/Private/OpenModelUtils.h` (Private)


#### enum `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::ETesselatorType`  
`enum class ETesselatorType : uint8`  
_L80-84_
- L82 _public enumerator_ `Fast`
- L83 _public enumerator_ `Accurate`

#### enum `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::EAlShaderModelType`  
`enum class EAlShaderModelType : uint8`  
_L86-92_
- L88 _public enumerator_ `BLINN`
- L89 _public enumerator_ `LAMBERT`
- L90 _public enumerator_ `LIGHTSOURCE`
- L91 _public enumerator_ `PHONG`

#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::TAlObjectPtr`  
`template<typename T> class TAlObjectPtr : public TSharedPtr<T>`  
_L95-160_
- inherits: `TSharedPtr<T>`
- L97 _private typedef_ `using Super = TSharedPtr<T>;`
- L100 _public function_ `TAlObjectPtr(T* Object = nullptr) : Super(Object)`
- L114 _public function_ `~TAlObjectPtr()`
- L127 _public function_ `bool IsValid() const`
- L129 _public function_ `FString GetName() const`
- L134 _public function_ `uint32 GetHash() const`
- L146 _public function_ `FString GetUniqueID(const TCHAR* TypeName = TEXT("Object")) const`
- L151 _public function_ `operator bool() const`
- L175 _prototype_ `template<> uint32 TAlObjectPtr<AlLayer>::GetHash() const;`

#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FLayerContainer`  
`class FLayerContainer`  
_L177-185_
- L180 _public prototype_ `static void Reset();`
- L181 _public prototype_ `static TAlObjectPtr<AlLayer> FindOrAdd(AlLayer* Layer);`
- L184 _private member_ `static TMap<AlLayer*, TAlObjectPtr<AlLayer>> LayerMap;`

#### enum `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::EDagNodeType`  
`enum class EDagNodeType : uint8`  
_L187-195_
- L189 _public enumerator_ `Unknown = 0x00`
- L190 _public enumerator_ `MeshType = 0x01`
- L191 _public enumerator_ `SurfaceType = 0x02`
- L192 _public enumerator_ `ShellType = 0x04`
- L193 _public enumerator_ `GroupType = 0x08`
- L194 _public enumerator_ `GeometryType = MeshType | SurfaceType | ShellType`

#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FAlDagNodePtr`  
`class FAlDagNodePtr : public TAlObjectPtr<AlDagNode>`  
_L198-371_
- inherits: `TAlObjectPtr<AlDagNode>`
- L200 _private typedef_ `using Super = TSharedPtr<AlDagNode>;`
- L203 _public function_ `FAlDagNodePtr(AlDagNode* DagNode = nullptr) : TAlObjectPtr<AlDagNode>(DagNode) , Type(EDagNodeType::Unknown)`
- L243 _public function_ `~FAlDagNodePtr()`
- L265 _public function_ `FString GetLayerName() const`
- L270 _public function_ `const TAlObjectPtr<AlLayer>& GetLayer() const`
- L275 _public function_ `bool HasSymmetry() const`
- L280 _public function_ `bool IsVisible() const`
- L285 _public function_ `AlDagNode* AsADagNode() const`
- L290 _public function_ `bool HasGeometry() const`
- L295 _public function_ `bool IsAGroup() const`
- L300 _public function_ `bool IsAMesh() const`
- L305 _public function_ `bool IsASurface() const`
- L310 _public function_ `bool IsAShell() const`
- L315 _public function_ `bool GetMesh(TAlObjectPtr<AlMesh>& OutMesh) const`
- L322 _public function_ `bool GetSurface(TAlObjectPtr<AlSurface>& OutSurface) const`
- L329 _public function_ `bool GetShell(TAlObjectPtr<AlShell>& OutShell) const`
- L336 _public prototype_ `CADLibrary::FMeshParameters GetMeshParameters() const;`
- L338 _public function_ `void SetActorTransform(IDatasmithActorElement& ActorElement) const`
- L367 _private member_ `mutable TOptional<FString> LayerName;`
- L368 _private member_ `mutable TAlObjectPtr<AlLayer> CachedLayer;`
- L369 _private member_ `bool bCanDeleteObject = false;`
- L370 _private member_ `EDagNodeType Type;`

#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FPatchMesh`  
`class FPatchMesh`  
_L373-437_
- L376 _public function_ `FPatchMesh(const FString& InName, TAlObjectPtr<AlLayer>& InLayer, int32 Count) : Name(InName) , Layer(InLayer)`
- L383 _public function_ `bool HasContent()`
- L388 _public function_ `bool HasSingleContent() const`
- L393 _public function_ `bool GetSingleContent(FAlDagNodePtr& OutMeshNode)`
- L406 _public function_ `const FString& GetName() const`
- L408 _public function_ `uint32 GetHash() const`
- L410 _public function_ `const FString& GetUniqueID() const`
- L412 _public function_ `const TAlObjectPtr<AlLayer>& GetLayer() const`
- L414 _public function_ `void AddMeshNode(FAlDagNodePtr& MeshNode)`
- L420 _public function_ `void IterateOnMeshNodes(const TFunction<void(const FAlDagNodePtr& MeshNode)>& Callback) const`
- L428 _public prototype_ `bool Initialize();`
- L431 _private member_ `FString Name;`
- L432 _private member_ `TArray<FAlDagNodePtr> MeshNodes;`
- L433 _private member_ `TAlObjectPtr<AlLayer> Layer;`
- L434 _private member_ `uint32 Hash;`
- L435 _private member_ `FString UniqueID;`
- L436 _private member_ `bool bInitialized = false;`

#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FBodyNode`  
`class FBodyNode`  
_L439-514_
- L442 _public function_ `FBodyNode(const FString& InName, TAlObjectPtr<AlLayer>& InLayer, int32 Count) : Name(InName) , Layer(InLayer)`
- L449 _public function_ `bool HasContent()`
- L454 _public function_ `bool HasSingleContent() const`
- L459 _public function_ `bool GetSingleContent(FAlDagNodePtr& OutDagNode) const`
- L472 _public function_ `const FString& GetName() const`
- L474 _public function_ `uint32 GetHash() const`
- L476 _public function_ `const FString& GetUniqueID() const`
- L478 _public function_ `const TAlObjectPtr<AlLayer>& GetLayer() const`
- L480 _public prototype_ `bool AddNode(FAlDagNodePtr& DagNode);`
- L482 _public function_ `void IterateOnDagNodes(const TFunction<void(const FAlDagNodePtr&)>& Callback) const`
- L493 _public function_ `void IterateOnSlotIndices(const TFunction<void(int SlotIndex, const TAlObjectPtr<AlShader>& Shader)>& Callback) const`
- L501 _public prototype_ `bool Initialize();`
- L503 _public prototype_ `int32 GetSlotIndex(const FAlDagNodePtr& DagNode);`
- L506 _private member_ `FString Name;`
- L507 _private member_ `mutable TArray<FAlDagNodePtr> DagNodes;`
- L508 _private member_ `TAlObjectPtr<AlLayer> Layer;`
- L509 _private member_ `TMap<FString, int> ShaderNameToSlotIndex;`
- L510 _private member_ `TMap<int, TAlObjectPtr<AlShader>> SlotIndexToShader;`
- L511 _private member_ `uint32 Hash;`
- L512 _private member_ `FString UniqueID;`
- L513 _private member_ `bool bInitialized = false;`

#### enum `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::ECADModelGeometryType`  
`enum class ECADModelGeometryType : int32`  
_L516-522_
- L518 _public enumerator_ `DagNode`
- L519 _public enumerator_ `MeshNode`
- L520 _public enumerator_ `BodyNode`
- L521 _public enumerator_ `PatchMesh`

#### enum `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::EAliasObjectReference`  
`enum class EAliasObjectReference`  
_L524-529_
- L526 _public enumerator_ `LocalReference`
- L527 _public enumerator_ `ParentReference`
- L528 _public enumerator_ `WorldReference`

#### struct `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FAliasGeometry`  
`struct FAliasGeometry : public CADLibrary::FCADModelGeometry`  
_L531-534_
- inherits: `CADLibrary::FCADModelGeometry`
- L533 _public member_ `EAliasObjectReference Reference = EAliasObjectReference::LocalReference;`

#### struct `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FDagNodeGeometry`  
`struct FDagNodeGeometry : public FAliasGeometry`  
_L536-546_
- inherits: `FAliasGeometry`
- L538 _public member_ `const FAlDagNodePtr& DagNode;`
- L540 _public function_ `FDagNodeGeometry(int32 InType, EAliasObjectReference InReference, const FAlDagNodePtr& InDagNode) : DagNode(InDagNode)`

#### struct `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FBodyNodeGeometry`  
`struct FBodyNodeGeometry : public FAliasGeometry`  
_L548-558_
- inherits: `FAliasGeometry`
- L550 _public member_ `TSharedPtr<FBodyNode> BodyNode;`
- L552 _public function_ `FBodyNodeGeometry(int32 InType, EAliasObjectReference InReference, const TSharedPtr<FBodyNode>& InBodyNode)`

#### Free symbols / members of external scopes

- L45 _macro_ `#define LAYER_TYPE TEXT("Layer")`
- L46 _macro_ `#define GROUPNODE_TYPE TEXT("GroupNode")`
- L47 _macro_ `#define MESH_TYPE TEXT("Mesh")`
- L48 _macro_ `#define MESHNODE_TYPE TEXT("MeshNode")`
- L49 _macro_ `#define SHADER_TYPE TEXT("Shader")`
- L50 _macro_ `#define SHELLNODE_TYPE TEXT("ShellNode")`
- L51 _macro_ `#define SHELL_TYPE TEXT("Shell")`
- L52 _macro_ `#define SURFACE_TYPE TEXT("Surface")`
- L53 _macro_ `#define SURFACENODE_TYPE TEXT("SurfaceNode")`
- L56 _macro_ `#define UNIT_CONVERSION_CM_TO_MM 10.` — Convert distance from UE (in cm) to CADKernel (in mm)
- L57 _macro_ `#define UE_TO_CADKERNEL(Distance) (Distance * 10.)`
- L59 _macro_ `#define WIRE_MEMORY_CHECK 0`
- L60 _macro_ `#define WIRE_ENSURE_ENABLED 0`
- L62 _macro_ `#define ensureWire(InExpression) ensure(InExpression)`
- L64 _macro_ `#define ensureWire(InExpression)`
- L67 _namespace_ `namespace UE_DATASMITHWIRETRANSLATOR_NAMESPACE`
- L69 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWireInterface, Log, All) #if WIRE_MEMORY_CHECK extern TSet<AlDagNode*> DagNodeSet;`
- L69 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWireInterface, Log, All) #if WIRE_MEMORY_CHECK extern TSet<AlDagNode*> DagNodeSet;` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L73 _externvar_ `extern TSet<AlObject*> ObjectSet;` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L74 _externvar_ `extern int32 AllocatedObjects;` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L75 _externvar_ `extern int32 MaxAllocatedObjects;` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L78 _typedef_ `typedef double AlMatrix4x4[4][4];` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L156 _function_ `friend uint32 GetTypeHash(const TAlObjectPtr<T>& Object)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L163 _function_ `template<typename T> inline bool operator==(const TAlObjectPtr<T>& A, const TAlObjectPtr<T>& B)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L169 _function_ `template<typename T> inline bool operator!=(const TAlObjectPtr<T>& A, const TAlObjectPtr<T>& B)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L196 _prototype_ `ENUM_CLASS_FLAGS(EDagNodeType);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L560 _namespace_ `namespace OpenModelUtils` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE`)
- L563 _prototype_ `bool GetCsvLayerString(const TAlObjectPtr<AlLayer>& Layer, FString& CsvString);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`) — Following layer hierarchy, get list of layers an actor would be in as a csv string
- L565 _prototype_ `bool ActorHasContent(const TSharedPtr<IDatasmithActorElement>& ActorElement);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L567 _prototype_ `bool IsValidActor(const TSharedPtr<IDatasmithActorElement>& ActorElement);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L569 _function_ `inline FString UuidToString(const uint32& Uuid)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L574 _function_ `inline uint32 GetTypeHash(AlPersistentID& GroupNodeId)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L581 _function_ `inline uint32 GetAlDagNodeUuid(AlDagNode& DagNode)` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L593 _prototype_ `bool TransferAlMeshToMeshDescription(const AlMesh& Mesh, const TCHAR* SlotMaterialName, FMeshDescription& MeshDescription, CADLibrary::FMeshParameters& SymmetricParameters, const bool bMerge = false);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L595 _prototype_ `FAlDagNodePtr TesselateDagLeaf(const AlDagNode& DagLeaf, ETesselatorType TessType, double Tolerance);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)
- L597 _prototype_ `CADLibrary::FMeshParameters GetMeshParameters(const TAlObjectPtr<AlLayer>& Layer);` (scope `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::OpenModelUtils`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface/Private/WireInterfaceImpl.h` (Private)


#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FWireTranslatorImpl`  
`class FWireTranslatorImpl : public IWireInterface`  
_L38-144_
- inherits: `IWireInterface`
- L41 _public function_ `FWireTranslatorImpl()`
- L43 _public prototype_ `~FWireTranslatorImpl();`
- L46 _public prototype_ `virtual bool Initialize(const TCHAR* InSceneFullName) override;` — Begin IWrieInterface
- L47 _public prototype_ `virtual bool Load(TSharedPtr<IDatasmithScene> InScene) override;`
- L48 _public prototype_ `virtual void SetImportSettings(const FWireSettings& Options) override;`
- L49 _public function_ `virtual void SetOutputPath(const FString& Path)`
- L51 _public prototype_ `bool LoadStaticMesh(const TSharedPtr<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload, const FDatasmithTessellationOptions& InTessellationOptions);`
- L56 _private prototype_ `bool TraverseModel();` — Model traversal
- L57 _private prototype_ `TSharedPtr<IDatasmithActorElement> TraverseDag(const FAlDagNodePtr& DagNode);`
- L59 _private prototype_ `TSharedPtr<IDatasmithActorElement> ProcessGeometryNode(const FAlDagNodePtr& GeomNode, const TAlObjectPtr<AlLayer>& ParentLayer = TAlObjectPtr<AlLayer>());`
- L60 _private prototype_ `TSharedPtr<IDatasmithActorElement> TraverseGroupNode(const FAlDagNodePtr& GroupNode, const TAlObjectPtr<AlLayer>& ParentLayer = TAlObjectPtr<AlLayer>());`
- L61 _private prototype_ `TSharedPtr<IDatasmithActorElement> ProcessGroupNode(const FAlDagNodePtr& GroupNode, const TAlObjectPtr<AlLayer>& ParentLayer = TAlObjectPtr<AlLayer>());`
- L62 _private prototype_ `TSharedPtr<IDatasmithActorElement> ProcessBodyNode(TSharedPtr<FBodyNode>& BodyNode, const FAlDagNodePtr& GroupNode, const TAlObjectPtr<AlLayer>& ParentLayer = TAlObjectPtr<AlLayer>());`
- L63 _private prototype_ `TSharedPtr<IDatasmithActorElement> ProcessPatchMesh(TSharedPtr<FPatchMesh>& PatchMesh, const FAlDagNodePtr& GroupNode, const TAlObjectPtr<AlLayer>& ParentLayer = TAlObjectPtr<AlLayer>());`
- L65 _private prototype_ `TSharedPtr<IDatasmithActorElement> FindOrAddLayerActor(const TAlObjectPtr<AlLayer>& Layer);`
- L66 _private prototype_ `TSharedPtr<IDatasmithMeshElement> FindOrAddMeshElement(const FAlDagNodePtr& GeomNode);`
- L67 _private prototype_ `TSharedPtr<IDatasmithMeshElement> FindOrAddMeshElement(TSharedPtr<FBodyNode>& BodyNode);`
- L68 _private prototype_ `TSharedPtr<IDatasmithMeshElement> FindOrAddMeshElement(TSharedPtr<FPatchMesh>& PatchMesh);`
- L71 _private function_ `bool IsTransparent(FColor& TransparencyColor)` — Material creation
- L77 _private prototype_ `bool GetCommonParameters(int32 Field, double Value, FColor& Color, FColor& TransparencyColor, FColor& IncandescenceColor, double GlowIntensity);`
- L79 _private prototype_ `void AddAlBlinnParameters(const TAlObjectPtr<AlShader>& Shader, TSharedPtr<IDatasmithUEPbrMaterialElement> MaterialElement);`
- L80 _private prototype_ `void AddAlLambertParameters(const TAlObjectPtr<AlShader>& Shader, TSharedPtr<IDatasmithUEPbrMaterialElement> MaterialElement);`
- L81 _private prototype_ `void AddAlLightSourceParameters(const TAlObjectPtr<AlShader>& Shader, TSharedPtr<IDatasmithUEPbrMaterialElement> MaterialElement);`
- L82 _private prototype_ `void AddAlPhongParameters(const TAlObjectPtr<AlShader>& Shader, TSharedPtr<IDatasmithUEPbrMaterialElement> MaterialElement);`
- L84 _private prototype_ `TSharedPtr<IDatasmithBaseMaterialElement> FindOrAddMaterial(const TAlObjectPtr<AlShader>& Shader);`
- L87 _private prototype_ `TOptional<FMeshDescription> GetMeshDescription(TSharedPtr<IDatasmithMeshElement> MeshElement, CADLibrary::FMeshParameters& OutMeshParameters);` — Geometry retrieval
- L88 _private prototype_ `TSharedPtr<CADLibrary::ICADModelConverter> GetModelConverter() const;`
- L89 _private prototype_ `TOptional<FMeshDescription> GetMeshDescriptionFromBodyNode(TSharedPtr<FBodyNode>& BodyNode, TSharedPtr<IDatasmithMeshElement> MeshElement, CADLibrary::FMeshParameters& MeshParameters);`
- L90 _private prototype_ `TOptional<FMeshDescription> GetMeshDescriptionFromPatchMesh(TSharedPtr<FPatchMesh>& PatchMesh, TSharedPtr<IDatasmithMeshElement> MeshElement, CADLibrary::FMeshParameters& MeshParameters);`
- L91 _private prototype_ `TOptional<FMeshDescription> GetMeshDescriptionFromParametricNode(const FAlDagNodePtr& DagNode, TSharedPtr<IDatasmithMeshElement> MeshElement, CADLibrary::FMeshParameters& MeshParameters);`
- L92 _private prototype_ `TOptional<FMeshDescription> GetMeshDescriptionFromMeshNode(const FAlDagNodePtr& MeshNode, TSharedPtr<IDatasmithMeshElement> MeshElement, CADLibrary::FMeshParameters& MeshParameters);`
- L94 _private function_ `FAlDagNodePtr FindOrAddDagNode(AlDagNode* InDagNode)`
- L115 _private member_ `TSharedPtr<IDatasmithScene> DatasmithScene;`
- L116 _private member_ `FString OutputPath;`
- L117 _private member_ `FString SceneFullPath;`
- L118 _private member_ `FString SceneVersion;`
- L120 _private member_ `FWireSettings WireSettings;`
- L122 _private member_ `TSharedPtr<CADLibrary::ICADModelConverter> CADModelConverter;`
- L124 _private member_ `bool bSceneLoaded = false;`
- L126 _private member_ `TMap<FString, TSharedPtr<IDatasmithBaseMaterialElement>> ShaderNameToMaterial;`
- L128 _private member_ `TMap<uint32, TSharedPtr<IDatasmithMeshElement>> GeomNodeToMeshElement;`
- L129 _private member_ `TMap<TSharedPtr<IDatasmithMeshElement>, FAlDagNodePtr> MeshElementToParametricNode;`
- L130 _private member_ `TMap<TSharedPtr<IDatasmithMeshElement>, FAlDagNodePtr> MeshElementToMeshNode;`
- L132 _private member_ `TMap<uint32, TSharedPtr<IDatasmithMeshElement>> BodyNodeToMeshElement;`
- L133 _private member_ `TMap<TSharedPtr<IDatasmithMeshElement>, TSharedPtr<FBodyNode>> MeshElementToBodyNode;`
- L135 _private member_ `TMap<uint32, TSharedPtr<IDatasmithMeshElement>> PatchMeshToMeshElement;`
- L136 _private member_ `TMap<TSharedPtr<IDatasmithMeshElement>, TSharedPtr<FPatchMesh>> MeshElementToPatchMesh;`
- L138 _private member_ `TMap<AlDagNode*, FAlDagNodePtr> EncounteredNodes;`
- L140 _private member_ `TMap<uint32, TSharedPtr<IDatasmithActorElement>> LayerToActor;`
- L143 _private member_ `bool bTrackMesh = false;` — #cad_debug

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace CADLibrary`
- L33 _namespace_ `namespace UE_DATASMITHWIRETRANSLATOR_NAMESPACE`

### `Plugins/Enterprise/DatasmithCADImporter/Source/WireInterface/Public/WireInterfaceModule.h` (Public)


#### class `UE_DATASMITHWIRETRANSLATOR_NAMESPACE::FDatasmithWireTranslatorModule`  
`class FDatasmithWireTranslatorModule : public IModuleInterface`  
_L15-37_
- inherits: `IModuleInterface`
- desc: Datasmith Translator for .wire files.
- L19 _public function_ `static FDatasmithWireTranslatorModule& Get()`
- L24 _public function_ `static bool IsAvailable()`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `FString GetTempDir() const;`
- L36 _private member_ `FString TempDir;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE_DATASMITHWIRETRANSLATOR_NAMESPACE`
