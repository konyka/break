# Plugins / CADInterfaces

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces`
- headers: 15; symbols: 895
- symbol kinds: class=24, delegate=1, enum=3, enumerator=68, function=128, macro=5, member=119, namespace=22, prototype=493, struct=1, typedef=31
- PublicDependencyModuleNames: CADKernel, CADLibrary, CADTools, Core, DatasmithCore, Json, TechSoft

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/CADEnum.h` (Private)


#### enum `ECADType`  
`enum class ECADType`  
_L4-20_
- L6 _public enumerator_ `ACIS`
- L7 _public enumerator_ `CATIA`
- L8 _public enumerator_ `CATIA_CGR`
- L9 _public enumerator_ `CATIA_3DXML`
- L10 _public enumerator_ `CATIAV4`
- L11 _public enumerator_ `CREO`
- L12 _public enumerator_ `IGES`
- L13 _public enumerator_ `INVENTOR`
- L14 _public enumerator_ `JT`
- L15 _public enumerator_ `NX`
- L16 _public enumerator_ `PARASOLID`
- L17 _public enumerator_ `SOLIDWORKS`
- L18 _public enumerator_ `STEP`
- L19 _public enumerator_ `OTHER`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftBridge.h` (Private)


#### class `CADLibrary::TechSoftUtils::FUVReparameterization`  
`class FUVReparameterization`  
_L42-164_
- L45 _private member_ `double Scale[2] = { 1., 1. };`
- L46 _private member_ `double Offset[2] = { 0., 0. };`
- L47 _private member_ `bool bSwapUV = false;`
- L48 _private member_ `bool bNeedApply = false;`
- L49 _private member_ `bool bNeedSwapOrientation = false;`
- L53 _public function_ `FUVReparameterization()`
- L57 _public function_ `void SetCoef(const double InUScale, const double InUOffset, const double InVScale, const double InVOffset)`
- L66 _public function_ `bool GetNeedApply() const`
- L71 _public function_ `bool GetSwapUV() const`
- L76 _public function_ `bool GetNeedSwapOrientation() const`
- L81 _public function_ `void SetNeedSwapOrientation()`
- L86 _public function_ `void SetNeedApply()`
- L98 _public function_ `void ScaleUVTransform(double InUScale, double InVScale)`
- L111 _public function_ `void Process(TArray<FVector>& Poles) const`
- L131 _public function_ `void AddUVTransform(A3DUVParameterizationData& Transform)`
- L142 _public function_ `void Apply(FVector2d& Point) const`
- L151 _private function_ `void Apply(FVector& Point) const`
- L159 _private function_ `void GetSwapUV(FVector& Point) const`

#### class `CADLibrary::FTechSoftBridge`  
`class FTechSoftBridge`  
_L167-259_
- L170 _private member_ `FTechSoftFileParser& Parser;`
- L172 _private member_ `UE::CADKernel::FSession& Session;`
- L173 _private member_ `UE::CADKernel::FModel& Model;`
- L175 _private member_ `const double GeometricTolerance;`
- L176 _private member_ `const double EdgeLengthTolerance;`
- L177 _private member_ `const double SquareGeometricTolerance;`
- L178 _private member_ `const double SquareJoiningVertexTolerance;`
- L180 _private member_ `TMap<const A3DEntity*, TSharedPtr<UE::CADKernel::FBody>> TechSoftToCADKernel;`
- L181 _private member_ `TMap<UE::CADKernel::FBody*, const A3DEntity*> CADKernelToTechSoft;`
- L182 _private member_ `TMap<const A3DTopoCoEdge*, TSharedPtr<UE::CADKernel::FTopologicalEdge>> A3DEdgeToEdge;`
- L184 _private member_ `EFailureReason FailureReason = EFailureReason::None;`
- L185 _private member_ `bool bConvertionFailed = false;`
- L187 _private member_ `double BodyScale = 1;`
- L190 _public prototype_ `FTechSoftBridge(FTechSoftFileParser& InParser, UE::CADKernel::FSession& InSession);`
- L191 _public prototype_ `UE::CADKernel::FBody* AddBody(A3DRiBrepModel* A3DBRepModel, FArchiveCADObject& ArchiveBody);`
- L192 _public prototype_ `UE::CADKernel::FBody* GetBody(A3DRiBrepModel* A3DBRepModel);`
- L193 _public prototype_ `const A3DRiBrepModel* GetA3DBody(UE::CADKernel::FBody* BRepModel);`
- L195 _public function_ `EFailureReason GetFailureReason()`
- L202 _private prototype_ `void TraverseBrepData(const A3DTopoBrepData* A3DBrepData, TSharedRef<UE::CADKernel::FBody>& Body);`
- L204 _private prototype_ `void TraverseConnex(const A3DTopoConnex* A3DConnex, TSharedRef<UE::CADKernel::FBody>& Body);`
- L205 _private prototype_ `void TraverseShell(const A3DTopoShell* A3DShell, TSharedRef<UE::CADKernel::FBody>& Body);`
- L206 _private prototype_ `void AddFace(const A3DTopoFace* A3DFace, UE::CADKernel::EOrientation Orientation, TSharedRef<UE::CADKernel::FShell>& Body, uint32 Index);`
- L208 _private prototype_ `TSharedPtr<UE::CADKernel::FTopologicalLoop> AddLoop(const A3DTopoLoop* A3DLoop, const TSharedRef<UE::CADKernel::FSurface>& Surface, const TechSoftUtils::FUVReparameterization& UVReparameterization, const bool bIsExternalLoop);`
- L209 _private prototype_ `TSharedPtr<UE::CADKernel::FTopologicalEdge> AddEdge(const A3DTopoCoEdge* A3DCoedge, const TSharedRef<UE::CADKernel::FSurface>& Surface, const TechSoftUtils::FUVReparameterization& UVReparameterization, UE::CADKernel::EOrientation& OutOrientation);`
- L211 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSurface(const A3DSurfBase* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L212 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddConeSurface(const A3DSurfCone* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L213 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddCylinderSurface(const A3DSurfCylinder* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L214 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddLinearTransfoSurface(const A3DSurfBase* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L215 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddNurbsSurface(const A3DSurfNurbs* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L216 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddOffsetSurface(const A3DSurfOffset* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L217 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddPlaneSurface(const A3DSurfPlane* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L218 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddRevolutionSurface(const A3DSurfRevolution* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L219 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddRuledSurface(const A3DSurfRuled* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L220 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSphereSurface(const A3DSurfSphere* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L221 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddTorusSurface(const A3DSurfTorus* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L223 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddBlend01Surface(const A3DSurfBlend01* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L224 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddBlend02Surface(const A3DSurfBlend02* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L225 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddBlend03Surface(const A3DSurfBlend03* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L226 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddCylindricalSurface(const A3DSurfCylindrical* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L227 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddPipeSurface(const A3DSurfPipe* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L228 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddExtrusionSurface(const A3DSurfExtrusion* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L229 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSurfaceFromCurves(const A3DSurfFromCurves* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L230 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddTransformSurface(const A3DSurfTransform* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L232 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSurfaceAsNurbs(const A3DSurfBase* A3DSurface, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L233 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSurfaceNurbs(const A3DSurfNurbsData& A3DNurbsData, TechSoftUtils::FUVReparameterization& OutUVReparameterization);`
- L235 _private prototype_ `TSharedPtr<UE::CADKernel::FRestrictionCurve> AddRestrictionCurve(const A3DCrvBase* A3DCurve, const TSharedRef<UE::CADKernel::FSurface>& Surface);`
- L237 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurve(const A3DCrvBase* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L239 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveCircle(const A3DCrvCircle* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L240 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveComposite(const A3DCrvComposite* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L241 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveEllipse(const A3DCrvEllipse* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L242 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveHelix(const A3DCrvHelix* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L243 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveHyperbola(const A3DCrvHyperbola* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L244 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveLine(const A3DCrvLine* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L245 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveNurbs(const A3DCrvNurbs* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L246 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveParabola(const A3DCrvParabola* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L247 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurvePolyLine(const A3DCrvPolyLine* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L249 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveBlend02Boundary(const A3DCrvBlend02Boundary* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L250 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveEquation(const A3DCrvEquation* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L251 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveIntersection(const A3DCrvIntersection* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L252 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveOffset(const A3DCrvOffset* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L253 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveOnSurf(const A3DCrvOnSurf* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L254 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveTransform(const A3DCrvTransform* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L256 _private prototype_ `TSharedPtr<UE::CADKernel::FCurve> AddCurveAsNurbs(const A3DCrvBase* A3DCurve, const TechSoftUtils::FUVReparameterization& UVReparameterization);`
- L258 _private prototype_ `void AddMetaData(FArchiveCADObject& EntityData, UE::CADKernel::FTopologicalShapeEntity& Entity);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CADKernel` (scope `UE`)
- L33 _namespace_ `namespace CADLibrary`
- L39 _namespace_ `namespace TechSoftUtils` (scope `CADLibrary`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftFileParser.h` (Private)


#### class `CADLibrary::FTechSoftFileParser`  
`class FTechSoftFileParser : public ICADFileParser`  
_L30-184_
- inherits: `ICADFileParser`
- L38 _public prototype_ `FTechSoftFileParser(FCADFileData& InCADData, const FString& EnginePluginsPath = TEXT(""));` — @param InCADData TODO @param EnginePluginsPath Full Path of EnginePlugins. Mandatory to set KernelIO to import DWG, or DGN files
- L41 _public function_ `virtual ECADParsingResult Process() override`
- L46 _public prototype_ `virtual ECADParsingResult Process() override;`
- L48 _public function_ `double GetFileUnit()`
- L53 _public prototype_ `void ExtractMetaData(const A3DEntity* Entity, FArchiveCADObject& OutMetaData);`
- L57 _protected function_ `virtual A3DStatus AdaptBRepModel()`
- L66 _protected prototype_ `virtual void SewModel();` — If the tessellator is TechSoft, SewModel call TechSoftInterface::SewModel If the tessellator is UE::CADKernel, SewModel do nothing as the file is not yet parsed. In this case, the sew is done in GenerateBodyMeshes.
- L69 _protected prototype_ `virtual void GenerateBodyMeshes();` — Tessellation methods
- L70 _protected prototype_ `virtual void GenerateBodyMesh(A3DRiRepresentationItem* Representation, FArchiveBody& Body);`
- L77 _private prototype_ `void CountUnderModel();` — Methods to parse a first time the file to count the number of components Needed to reserve CADFileData Start with CountUnderModel
- L78 _private prototype_ `void CountUnderConfigurationSet(const A3DAsmProductOccurrence* Occurrence);`
- L79 _private prototype_ `void CountUnderOccurrence(const A3DAsmProductOccurrence* Occurrence);`
- L80 _private prototype_ `void CountUnderPartDefinition(const A3DAsmPartDefinition* PartDefinition);`
- L81 _private prototype_ `void CountUnderRepresentationItem(const A3DRiRepresentationItem* RepresentationItem);`
- L82 _private prototype_ `void CountUnderRepresentationSet(const A3DRiSet* RepresentationSet);`
- L83 _private prototype_ `void CountUnderOverrideOccurrence(const A3DAsmProductOccurrence* Occurrence);`
- L85 _private prototype_ `void ReserveCADFileData();`
- L88 _private prototype_ `uint32 CountColorAndMaterial();` — Materials and colors
- L89 _private prototype_ `void ReadMaterialsAndColors();`
- L92 _private prototype_ `ECADParsingResult TraverseModel();` — Traverse ASM tree by starting from the model
- L99 _private prototype_ `void TraverseReference(const A3DAsmProductOccurrence* A3DReference, FArchiveReference& Reference);`
- L100 _private prototype_ `bool IsConfigurationSet(const A3DAsmProductOccurrence* Occurrence);`
- L101 _private prototype_ `void TraverseConfigurationSet(const A3DAsmProductOccurrence* ConfigurationSet, FArchiveReference& Reference);`
- L102 _private prototype_ `void TraverseOccurrence(const A3DAsmProductOccurrence* Occurrence, FArchiveReference& ParentReference);`
- L103 _private prototype_ `void ProcessPrototype(const A3DAsmProductOccurrence* InPrototype, FArchiveUnloadedReference& OutReference, A3DMiscTransformation** OutLocation);`
- L104 _private prototype_ `void ProcessReference(const A3DAsmProductOccurrence* OccurrencePtr, FArchiveInstance& Instance, FArchiveReference& Reference);`
- L105 _private prototype_ `void ProcessUnloadedReference(const FArchiveInstance& Instance, FArchiveUnloadedReference& Reference);`
- L107 _private prototype_ `void TraversePartDefinition(const A3DAsmPartDefinition* InPartDefinition, FArchiveReference& Parent);`
- L108 _private prototype_ `void TraverseExternalData(const A3DAsmProductOccurrence* InExternalData, FArchiveReference& Parent);`
- L109 _private prototype_ `void TraverseRepresentationSet(const A3DRiSet* InSetPtr, FArchiveReference& Parent);`
- L110 _private prototype_ `void TraverseRepresentationItem(A3DRiRepresentationItem* RepresentationItem, FArchiveReference& Parent);`
- L111 _private prototype_ `void TraverseBRepModel(A3DRiBrepModel* BrepModel, FArchiveReference& Parent);`
- L112 _private prototype_ `void TraversePolyBRepModel(A3DRiPolyBrepModel* PolygonalBrepModel, FArchiveReference& Parent);`
- L115 _private prototype_ `void ExtractSpecificMetaData(const A3DAsmProductOccurrence* Occurrence, FArchiveCADObject& OutMetaData);` — MetaData
- L117 _private prototype_ `void BuildInstanceName(FArchiveCADObject& MetaData, const FArchiveReference& Parent);`
- L118 _private prototype_ `void BuildReferenceName(FArchiveCADObject& Reference);`
- L119 _private prototype_ `void BuildPartName(FArchiveCADObject& Part);`
- L120 _private prototype_ `void BuildBodyName(FArchiveBody& MetaData, const FArchiveReference& Parent);`
- L121 _private prototype_ `void BuildRepresentationSetName(FArchiveCADObject& MetaData, const FArchiveReference& Parent);`
- L123 _private prototype_ `void ExtractGraphicProperties(const A3DGraphics* Graphics, FArchiveCADObject& OutMetaData);`
- L128 _private prototype_ `void ExtractOverrideOccurrenceSubtree(const A3DAsmProductOccurrence* OccurrencePtr, FArchiveWithOverridenChildren& Parent);` — Recursive method to extract the subtree of override occurrences of the children tree of an instance
- L134 _private prototype_ `void ExtractGraphStyleProperties(uint32 StyleIndex, FArchiveGraphicProperties& OutGraphicProperties);` — ColorName and MaterialName have to be initialized before. This method update the value ColorName or MaterialName accordingly of the GraphStyleData type (material or color)
- L135 _private prototype_ `FArchiveColor& FindOrAddColor(uint32 ColorIndex, uint8 Alpha);`
- L136 _private prototype_ `FArchiveMaterial& FindOrAddMaterial(FMaterialUId MaterialId, const A3DGraphStyleData& GraphStyleData);`
- L142 _private prototype_ `FArchiveMaterial& AddMaterialAt(uint32 MaterialIndexToSave, uint32 GraphMaterialIndex, const A3DGraphStyleData& GraphStyleData);` — @param GraphMaterialIndex is the Techsoft index of the graphic data @param MaterialIndexToSave is the index of the material really saved (i.e. for texture, at the texture index, with saved the material used by the texture)
- L143 _private function_ `FArchiveMaterial& AddMaterial(uint32 MaterialIndex, const A3DGraphStyleData& GraphStyleData)`
- L149 _private prototype_ `void ExtractCoordinateSystem(const A3DRiCoordinateSystem* CoordinateSystem, FArchiveCADObject& Component);` — Transform
- L150 _private prototype_ `void ExtractTransformation(const A3DMiscTransformation* Transformation3d, FArchiveCADObject& Component);`
- L151 _private prototype_ `void ExtractGeneralTransformation(const A3DMiscTransformation* GeneralTransformation, FArchiveCADObject& Component);`
- L152 _private prototype_ `void ExtractTransformation3D(const A3DMiscTransformation* CartesianTransformation, FArchiveCADObject& Component);`
- L155 _private prototype_ `void CheckMemory();`
- L162 _protected member_ `FUniqueTechSoftModelFile ModelFile;`
- L164 _protected member_ `TSet<const A3DAsmProductOccurrence*> PrototypeCounted;`
- L165 _protected member_ `uint32 ComponentCount[EComponentType::LastType] = { 0 };`
- L167 _protected member_ `FCADFileData& CADFileData;`
- L168 _protected member_ `FArchiveSceneGraph& SceneGraph;`
- L170 _protected member_ `FTechSoftInterface& TechSoftInterface;`
- L171 _protected member_ `ECADFormat Format;`
- L172 _protected member_ `bool bForceSew = false;`
- L174 _protected member_ `EModelerType ModelerType;`
- L175 _protected member_ `double FileUnit = 1;`
- L177 _protected member_ `TMap<A3DRiRepresentationItem*, FCadId> RepresentationItemsCache;`
- L178 _protected member_ `TMap<A3DAsmProductOccurrence*, FCadId> ReferenceCache;`
- L180 _protected member_ `bool bConvertionFailed = false;`
- L182 _protected member_ `std::atomic<bool> bProcessIsRunning;`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef void A3DAsmProductOccurrence;`
- L13 _typedef_ `typedef void A3DRiRepresentationItem;`
- L15 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftFileParserCADKernelTessellator.h` (Private)


#### class `CADLibrary::FTechSoftFileParserCADKernelTessellator`  
`class FTechSoftFileParserCADKernelTessellator : public FTechSoftFileParser`  
_L18-52_
- inherits: `FTechSoftFileParser`
- L26 _public prototype_ `FTechSoftFileParserCADKernelTessellator(FCADFileData& InCADData, const FString& EnginePluginsPath = TEXT(""));` — @param InCADData TODO @param EnginePluginsPath Full Path of EnginePlugins. Mandatory to set KernelIO to import DWG, or DGN files
- L32 _private prototype_ `virtual A3DStatus AdaptBRepModel() override;`
- L34 _private function_ `virtual void SewModel() override`
- L40 _private prototype_ `virtual void GenerateBodyMeshes() override;` — Tessellation methods
- L41 _private prototype_ `virtual void GenerateBodyMesh(A3DRiRepresentationItem* Representation, FArchiveBody& Body) override;`
- L42 _private prototype_ `void MeshAndGetTessellation(UE::CADKernel::FSession& CADKernelSession, FArchiveBody& ArchiveBody, UE::CADKernel::FBody& CADKernelBody);`
- L44 _private prototype_ `void SewAndGenerateBodyMeshes();`
- L45 _private prototype_ `void SewAndMesh(TArray<A3DRiRepresentationItem*>& Representations);`
- L51 _private member_ `int32 LastHostIdUsed = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L15 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftInterfaceUtils.inl` (Private)


#### class `TechSoftInterfaceUtils::FTechSoftTessellationExtractor`  
`class FTechSoftTessellationExtractor`  
_L15-954_
- L18 _public function_ `FTechSoftTessellationExtractor(const A3DRiRepresentationItem* RepresentationItemPtr, const double InBodyUnit) : BodyUnit(InBodyUnit) , TextureUnit(InBodyUnit)`
- L48 _public function_ `bool FillBodyMesh(CADLibrary::FBodyMesh& BodyMesh)`
- L71 _private function_ `void FillVertexArray(TArray<FVector3f>& VertexArray)`
- L99 _private function_ `uint32 CountTriangles(const A3DTessFaceData& FaceTessData)` — #ueent_techsoft: TODO: Make it more in line with the actual implementation of FillFaceArray
- L142 _private function_ `void FillFaceArray(CADLibrary::FBodyMesh& BodyMesh, int32 VertexOffset = 0)`
- L348 _private typedef_ `typedef double A3DDouble;`
- L349 _private function_ `bool AddFace(int32 FaceIndex[3], CADLibrary::FTessellationData& Tessellation, int32& InOutVertexIndex)`
- L364 _private function_ `void AddNormals(const A3DDouble* Normals, const int32 Indices[3], TArray<FVector3f>& NormalsArray)`
- L373 _private function_ `void AddTextureCoordinates(const A3DDouble* TextureCoords, const int32 Indices[3], TArray<FVector2f>& TessellationTextures)`
- L382 _private function_ `void AddFaceTriangle(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutStartIndex, int32& InOutLastVertexIndex)`
- L404 _private function_ `void AddFaceTriangleWithUniqueNormal(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L429 _private function_ `void AddFaceTriangleWithUniqueNormalAndTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 TextureCount, uint32& InOutStartIndex, int32& InOutLastVertexIndex)`
- L462 _private function_ `void AddFaceTriangleWithTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 InTextureCount, uint32& InOutStartIndex, int32& inOutLastVertexIndex)`
- L492 _private function_ `void AddFaceTriangleFan(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L517 _private function_ `void AddFaceTriangleFanWithUniqueNormal(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutLastTriangleIndex, int32& )`
- L543 _private function_ `void AddFaceTriangleFanWithUniqueNormalAndTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 TextureCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L578 _private function_ `void AddFaceTriangleFanWithTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 TextureCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L613 _private function_ `void AddFaceTriangleStripe(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutLastTriangleIndex, int32& )`
- L655 _private function_ `void AddFaceTriangleStripeWithTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 TextureCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L707 _private function_ `void AddFaceTriangleStripeWithUniqueNormal(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L747 _private function_ `void AddFaceTriangleStripeWithUniqueNormalAndTexture(CADLibrary::FTessellationData& Tessellation, const uint32 InTriangleCount, const uint32 TextureCount, uint32& InOutLastTriangleIndex, int32& InOutLastVertexIndex)`
- L800 _private function_ `void ScaleUV(const A3DTopoFace* TopoFace, TArray<FVector2f>& TexCoordArray)`
- L894 _private function_ `void GetBRepFaces()`
- L943 _private member_ `const A3DTess3D* TessellationPtr = nullptr;`
- L944 _private member_ `const A3DTopoBrepData* A3DBrepData = nullptr;`
- L945 _private member_ `const double BodyUnit = 1;`
- L946 _private member_ `double TextureUnit = 1;`
- L948 _private member_ `TArray<const A3DTopoFace*> BodyFaces;`
- L950 _private member_ `int32 LastVertexIndex = 0;`
- L951 _private member_ `A3DUns32* TriangulatedIndexes = nullptr;`
- L952 _private member_ `A3DDouble* TessellationNormals;`
- L953 _private member_ `A3DDouble* TessellationTexCoords;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TechSoftInterfaceUtils`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftParserUtils.h` (Private)


#### class `TechSoftParserUtils::FTechSoftMeshConverter`  
`class FTechSoftMeshConverter`  
_L85-136_
- L88 _public function_ `FTechSoftMeshConverter(const A3DTess3D* TessellationPtr, double ScaleFactor, CADLibrary::FBodyMesh& InBodyMesh) : BodyMesh(InBodyMesh) , TessellationBaseData(TessellationPtr) , Tessellation3DData(TessellationPtr)`
- L95 _public prototype_ `bool UpdateBodyMesh();`
- L98 _private prototype_ `void ConvertFace(const A3DTessFaceData& FaceTessData, CADLibrary::FTessellationData& Tessellation);`
- L100 _private prototype_ `void AddFaceTriangle(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L102 _private prototype_ `void AddFaceTriangleFan(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L104 _private prototype_ `void AddFaceTriangleStripe(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L106 _private prototype_ `void AddFaceTriangleWithOneNormal(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L108 _private prototype_ `void AddFaceTriangleFanWithOneNormal(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L110 _private prototype_ `void AddFaceTriangleStripeWithOneNormal(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount);`
- L112 _private prototype_ `void AddFaceTriangleWithTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L114 _private prototype_ `void AddFaceTriangleFanWithTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L116 _private prototype_ `void AddFaceTriangleStripeWithTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L118 _private prototype_ `void AddFaceTriangleWithOneNormalAndTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L120 _private prototype_ `void AddFaceTriangleFanWithOneNormalAndTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L122 _private prototype_ `void AddFaceTriangleStripeWithOneNormalAndTexture(CADLibrary::FTessellationData& Tessellation, A3DUns32 InTriangleCount, A3DUns32 InTextureCount);`
- L125 _private member_ `CADLibrary::FBodyMesh& BodyMesh;`
- L127 _private member_ `CADLibrary::TUniqueTSObj<A3DTessBaseData> TessellationBaseData;`
- L129 _private member_ `CADLibrary::TUniqueTSObj<A3DTess3DData> Tessellation3DData;`
- L131 _private member_ `double ScaleFactor;`
- L133 _private member_ `uint32 LastTriangleIndex;`
- L135 _private member_ `int32 LastVertexIndex;`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef void A3DAsmModelFile;`
- L16 _typedef_ `typedef void A3DAsmPartDefinition;`
- L17 _typedef_ `typedef void A3DAsmProductOccurrence;`
- L18 _typedef_ `typedef void A3DEntity;`
- L19 _typedef_ `typedef void A3DGraphics;`
- L20 _typedef_ `typedef void A3DMiscAttribute;`
- L21 _typedef_ `typedef void A3DMiscCartesianTransformation;`
- L23 _typedef_ `typedef void A3DMiscGeneralTransformation;`
- L24 _typedef_ `typedef void A3DRiBrepModel;`
- L25 _typedef_ `typedef void A3DRiCoordinateSystem;`
- L26 _typedef_ `typedef void A3DRiPolyBrepModel;`
- L27 _typedef_ `typedef void A3DRiRepresentationItem;`
- L28 _typedef_ `typedef void A3DRiSet;`
- L29 _typedef_ `typedef void A3DTess3D;`
- L30 _typedef_ `typedef void A3DTessBase;`
- L31 _typedef_ `typedef void A3DTopoBrepData;`
- L35 _namespace_ `namespace TechSoftParserUtils`
- L37 _typedef_ `typedef double A3DDouble;` (scope `TechSoftParserUtils`)
- L39 _function_ `inline bool AddFace(int32 FaceIndex[3], CADLibrary::FTessellationData& Tessellation, int32& InOutVertexIndex)` (scope `TechSoftParserUtils`)
- L54 _function_ `inline void AddNormals(const A3DDouble* Normals, const int32 Indices[3], TArray<FVector3f>& TessellationNormals)` (scope `TechSoftParserUtils`)
- L63 _function_ `inline void AddTextureCoordinates(const A3DDouble* TextureCoords, const int32 Indices[3], TArray<FVector2f>& TessellationTextures)` (scope `TechSoftParserUtils`)
- L72 _function_ `inline void Reserve(CADLibrary::FTessellationData& Tessellation, int32 InTrinangleCount, bool bWithTexture)` (scope `TechSoftParserUtils`)
- L83 _prototype_ `uint32 CountTriangles(const A3DTessFaceData& FaceTessData);` (scope `TechSoftParserUtils`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Private/TechSoftUtilsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace CADLibrary`
- L11 _namespace_ `namespace TechSoftUtils` (scope `CADLibrary`)
- L15 _prototype_ `void ExtractAttribute(const A3DMiscAttributeData& AttributeData, TMap<FString, FString>& OutMetaData);` (scope `CADLibrary::TechSoftUtils`)
- L18 _prototype_ `FString CleanLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L19 _prototype_ `FString CleanCatiaInstanceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L20 _prototype_ `FString Clean3dxmlInstanceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L21 _prototype_ `FString CleanCatiaReferenceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L22 _prototype_ `FString Clean3dxmlReferenceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L23 _prototype_ `FString CleanSwInstanceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L24 _prototype_ `FString CleanSwReferenceLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L25 _prototype_ `FString CleanCreoLabel(const FString& Name);` (scope `CADLibrary::TechSoftUtils`)
- L26 _prototype_ `bool CheckIfNameExists(TMap<FString, FString>& MetaData);` (scope `CADLibrary::TechSoftUtils`)
- L27 _prototype_ `bool ReplaceOrAddNameValue(TMap<FString, FString>& MetaData, const TCHAR* Key);` (scope `CADLibrary::TechSoftUtils`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/CADFileData.h` (Public)


#### struct `CADLibrary::FImportRecord`  
`struct FImportRecord`  
_L15-26_
- L17 _public member_ `double ImportTime = 0;`
- L18 _public member_ `double SavePrcTime = 0;`
- L19 _public member_ `double SewTime = 0;`
- L20 _public member_ `double AdaptBRepTime = 0;`
- L21 _public member_ `double MeshTime = 0;`
- L22 _public member_ `double LoadProcessTime = 0;` — Full process
- L24 _public member_ `uint64 StartMemoryUsed = 0;`
- L25 _public member_ `uint64 MaxMemoryUsed = 0;`

#### class `CADLibrary::FCADFileData`  
`class FCADFileData`  
_L28-347_
- L31 _public function_ `FCADFileData(const FImportParameters& InImportParameters, const FFileDescriptor& InFileDescription, const FString& InCachePath) : ImportParameters(InImportParameters) , CachePath(InCachePath) , bIsCacheDefined(!InCachePath.IsEmpty()) , FileDescription(InFileDescription)`
- L41 _public function_ `uint32 GetSceneFileHash() const`
- L50 _public function_ `uint32 GetGeomFileHash() const`
- L74 _public function_ `void SetArchiveNames()`
- L81 _public function_ `const FString GetSceneGraphFilePath() const`
- L90 _public function_ `const FString GetValidationFilePath() const`
- L107 _public function_ `const FString GetMeshArchiveFilePath() const`
- L116 _public function_ `const FString GetBodyCachePath(uint32 BodyHash) const`
- L124 _public function_ `const FString GetCADCachePath() const` — @return the path of CAD cache file
- L138 _public function_ `const FString GetCachePath() const`
- L147 _public function_ `bool IsCacheDefined() const`
- L152 _public function_ `void LogError(const FString& Message)`
- L157 _public function_ `void LogWarning(const FString& Message)`
- L163 _public function_ `void LogDisplayMessage(const FString& Message)` — Logs a message to console (and log file)
- L169 _public function_ `void LogMessage(const FString& Message)` — logs a message to a log file (does not print to console)
- L174 _public function_ `void LogVerboseMessage(const FString& Message)`
- L179 _public function_ `void LoadSceneGraphArchive()`
- L185 _public function_ `void ExportSceneGraphFile()`
- L191 _public function_ `FFileDescriptor& GetExternalReferences(int32 Index)`
- L196 _public function_ `FFileDescriptor& AddExternalRef(const TCHAR* InFilePath, const TCHAR* InConfiguration, const TCHAR* InRootFilePath)`
- L201 _public function_ `FFileDescriptor& AddExternalRef(const FFileDescriptor& InFileDescription)`
- L207 _public function_ `uint32 GetStaticMeshHash(const int32 BodyId)` — return a unique value that will be used to define the static mesh name
- L212 _public function_ `FBodyMesh& AddBodyMesh(FCadId BodyId, FArchiveBody& Body)`
- L221 _public function_ `void ExportMeshArchiveFile()`
- L227 _public function_ `const TArray<FFileDescriptor>& GetExternalRefSet() const`
- L232 _public function_ `const FString& GetSceneGraphFileName() const`
- L237 _public function_ `const FString& GetMeshFileName() const`
- L242 _public function_ `const TArray<TPair<uint8, FString>>& GetMessages() const`
- L247 _public function_ `const FArchiveSceneGraph& GetSceneGraphArchive() const`
- L252 _public function_ `FArchiveSceneGraph& GetSceneGraphArchive()`
- L257 _public function_ `FArchiveMaterial* FindMaterial(FMaterialUId MaterialId)`
- L262 _public function_ `FArchiveMaterial& AddMaterial(FMaterialUId MaterialId)`
- L267 _public function_ `FArchiveColor* FindColor(FMaterialUId ColorId)`
- L272 _public function_ `FArchiveColor& AddColor(FMaterialUId ColorId)`
- L277 _public function_ `const TArray<FBodyMesh>& GetBodyMeshes() const`
- L282 _public function_ `TArray<FBodyMesh>& GetBodyMeshes()`
- L287 _public function_ `const FFileDescriptor& GetCADFileDescription() const`
- L292 _public function_ `FFileDescriptor& GetCADFileDescription()`
- L297 _public function_ `void ReserveBodyMeshes(int32 MaxBodyCount)`
- L302 _public function_ `const FImportParameters& GetImportParameters() const`
- L307 _public function_ `void UpdateExternalRefPath()`
- L320 _public prototype_ `void InitCsvFile();`
- L321 _public prototype_ `void ExportValidationData();`
- L322 _public prototype_ `void GetMeshStatsToCsv(int32& FaceCount, int32& VertexCount);`
- L324 _public function_ `FImportRecord& GetRecord()`
- L330 _private member_ `const FImportParameters ImportParameters;`
- L331 _private member_ `const FString CachePath;`
- L332 _private member_ `const bool bIsCacheDefined;`
- L334 _private member_ `FFileDescriptor FileDescription;`
- L336 _private member_ `FString MeshArchiveFile;`
- L338 _private member_ `FArchiveSceneGraph SceneGraphArchive;`
- L339 _private member_ `TArray<FBodyMesh> BodyMeshes;`
- L341 _private member_ `TArray<TPair<uint8, FString>> Messages;`
- L343 _private member_ `FImportRecord Record;`
- L345 _private member_ `mutable uint32 SceneFileHash = 0;`
- L346 _private member_ `mutable uint32 GeomFileHash = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace CADLibrary`
- L13 _macro_ `#define CSV_HEADER TEXT("Input File,FileHash,FileSize(KB),Time.LoadStep(ms),Time.SavePrcTime(ms),Time.AdaptBRepTime(ms),Time.SewStep(ms),Time.MeshStep(ms),Time.Total(ms),MemoryUsage(MB),SceneGrapheData.InstanceNum,SceneGrapheData.Bodies,Sce`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/CADFileParser.h` (Public)


#### class `CADLibrary::ICADFileParser`  
`class ICADFileParser`  
_L10-15_
- L13 _public prototype_ `virtual ~ICADFileParser() = default;`
- L14 _public prototype_ `virtual ECADParsingResult Process() = 0;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/CADFileReader.h` (Public)


#### class `CADLibrary::FCADFileReader`  
`class FCADFileReader`  
_L15-49_
- L23 _public prototype_ `FCADFileReader(const FImportParameters& ImportParams, FFileDescriptor& InCTFileDescription, const FString& EnginePluginsPath = TEXT(""), const FString& InCachePath = TEXT(""));` — @param ImportParams Parameters that setting import data like mesh SAG... @param EnginePluginsPath Full Path of EnginePlugins. Mandatory to set KernelIO to import DWG, or DGN files @param InCachePath Full path of the cache in which the data will be saved
- L24 _public prototype_ `ECADParsingResult ProcessFile();`
- L26 _public function_ `const FCADFileData& GetCADFileData() const`
- L31 _public function_ `FCADFileData& GetCADFileData()`
- L37 _private prototype_ `bool FindFile(FFileDescriptor& File);`
- L39 _private prototype_ `uint32 GetSceneFileHash(const uint32 InSGHash, const FImportParameters& ImportParam);`
- L40 _private prototype_ `uint32 GetGeomFileHash(const uint32 InSGHash, const FImportParameters& ImportParam);`
- L42 _private prototype_ `void LoadSceneGraphArchive(const FString& SceneGraphFilePath);`
- L44 _private prototype_ `void ExportSceneGraphFile();`
- L45 _private prototype_ `void ExportMeshArchiveFile();`
- L47 _private member_ `FCADFileData CADFileData;`
- L48 _private member_ `TUniquePtr<ICADFileParser> CADParser;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/CADInterfacesModule.h` (Public)


#### enum `ECADInterfaceAvailability`  
`enum class ECADInterfaceAvailability`  
_L11-16_
- L13 _public enumerator_ `Unknown`
- L14 _public enumerator_ `Available`
- L15 _public enumerator_ `Unavailable`

#### class `ICADInterfacesModule`  
`class ICADInterfacesModule : public IModuleInterface`  
_L18-24_
- inherits: `IModuleInterface`
- L21 _public prototype_ `static ICADInterfacesModule& Get();`
- L22 _public prototype_ `static ECADInterfaceAvailability GetAvailability();`
- L23 _public prototype_ `static const TCHAR* GetLibraryVersion();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define CADINTERFACES_MODULE_NAME TEXT("CADInterfaces")`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADInterfaces, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADInterfaces, Log, All);`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/CADSceneGraph.h` (Public)


#### class `CADLibrary::FArchiveCADObject`  
`class FArchiveCADObject : public FArchiveGraphicProperties`  
_L16-50_
- inherits: `FArchiveGraphicProperties`
- L19 _public function_ `FArchiveCADObject() : Id(0) , Unit(1)`
- L25 _public function_ `FArchiveCADObject(FCadId Id, const FArchiveCADObject& Parent) : FArchiveGraphicProperties(Parent) , Id(Id) , Unit(Parent.Unit)`
- L32 _public prototype_ `virtual ~FArchiveCADObject() = default;`
- L37 _public member_ `uint32 Id;`
- L38 _public member_ `FString Label;`
- L39 _public member_ `TMap<FString, FString> MetaData;`
- L40 _public member_ `FMatrix TransformMatrix = FMatrix::Identity;`
- L41 _public member_ `double Unit = 1;`
- L43 _public function_ `bool IsNameDefined() const`
- L48 _public prototype_ `bool SetNameWithAttributeValue(const TCHAR* Key);`

#### class `CADLibrary::FArchiveWithOverridenChildren`  
`class FArchiveWithOverridenChildren : public FArchiveCADObject`  
_L52-67_
- inherits: `FArchiveCADObject`
- L55 _public prototype_ `FArchiveWithOverridenChildren() = default;`
- L56 _public function_ `FArchiveWithOverridenChildren(FCadId Id, const FArchiveCADObject& Parent) : FArchiveCADObject(Id, Parent)`
- L63 _public prototype_ `void AddOverridenChild(const FCadId ChildId);`
- L66 _public member_ `TArray<FCadId> OverridenChildren;`

#### class `CADLibrary::FArchiveOverrideOccurrence`  
`class FArchiveOverrideOccurrence : public FArchiveWithOverridenChildren`  
_L82-92_
- inherits: `FArchiveWithOverridenChildren`
- desc: This class save the override data of an occurrence. Indeed, some tools/formats allows to override some occurrences of the instances of a reference (e.g. only the 4th occurrence of C is hidden in the graph below) A | - B |   | - C (show) |   | - C (show) | | - B |   | - C (show) |   | - C (hide)
- L85 _public prototype_ `FArchiveOverrideOccurrence() = default;`
- L86 _public function_ `FArchiveOverrideOccurrence(FCadId Id, const FArchiveCADObject& Parent) : FArchiveWithOverridenChildren(Id, Parent)`

#### class `CADLibrary::FArchiveInstance`  
`class FArchiveInstance : public FArchiveWithOverridenChildren`  
_L97-111_
- inherits: `FArchiveWithOverridenChildren`
- desc: An instance is link to its reference but It also save its tree of override occurrence children
- L100 _public prototype_ `FArchiveInstance() = default;`
- L101 _public function_ `FArchiveInstance(FCadId Id, const FArchiveCADObject& Parent) : FArchiveWithOverridenChildren(Id, Parent)`
- L109 _public member_ `FCadId ReferenceNodeId = 0;`
- L110 _public member_ `bool bIsExternalReference = false;`

#### class `CADLibrary::FArchiveReference`  
`class FArchiveReference : public FArchiveCADObject`  
_L113-133_
- inherits: `FArchiveCADObject`
- L116 _public prototype_ `FArchiveReference() = default;`
- L117 _public function_ `FArchiveReference(FCadId Id, const FArchiveCADObject& Reference) : FArchiveCADObject(Id, Reference)`
- L124 _public prototype_ `void AddChild(const FCadId ChildId);`
- L125 _public prototype_ `void RemoveLastChild();`
- L127 _public prototype_ `int32 ChildrenCount();`
- L128 _public prototype_ `void MoveTemp(FArchiveUnloadedReference& Reference);`
- L129 _public prototype_ `void CopyMetaData(FArchiveUnloadedReference& Reference);`
- L132 _public member_ `TArray<FCadId> Children;`

#### class `CADLibrary::FArchiveUnloadedReference`  
`class FArchiveUnloadedReference : public FArchiveCADObject`  
_L135-153_
- inherits: `FArchiveCADObject`
- L138 _public prototype_ `FArchiveUnloadedReference() = default;`
- L140 _public function_ `FArchiveUnloadedReference(FCadId Id, const FArchiveCADObject& Parent) : FArchiveCADObject(Id, Parent)`
- L149 _public member_ `FFileDescriptor ExternalFile;`
- L152 _public member_ `bool bIsUnloaded = true;` — not serialized

#### class `CADLibrary::FArchiveBody`  
`class FArchiveBody : public FArchiveCADObject`  
_L155-182_
- inherits: `FArchiveCADObject`
- L158 _public prototype_ `FArchiveBody() = default;`
- L159 _public function_ `FArchiveBody(FCadId Id, const FArchiveCADObject& Parent, EMesher InMesher) : FArchiveCADObject(Id, Parent) , ParentId(Parent.Id) , Mesher(InMesher)`
- L169 _public member_ `FCadId ParentId = 0;`
- L170 _public member_ `FCadUuid MeshActorUId = 0;`
- L172 _public member_ `TSet<FMaterialUId> MaterialFaceSet;`
- L173 _public member_ `TSet<FMaterialUId> ColorFaceSet;`
- L175 _public member_ `EMesher Mesher = EMesher::TechSoft;`
- L177 _public prototype_ `void Delete();`
- L180 _public member_ `bool bIsFromCad = true;` — non serialized fields
- L181 _public member_ `bool bIsASolid = true;`

#### class `CADLibrary::FArchiveColor`  
`class FArchiveColor`  
_L184-198_
- L187 _public function_ `FArchiveColor(FMaterialUId InId = 0) : Id(InId)`
- L195 _public member_ `FMaterialUId Id;`
- L196 _public member_ `FColor Color;`
- L197 _public member_ `FMaterialUId UEMaterialUId;`

#### class `CADLibrary::FArchiveMaterial`  
`class FArchiveMaterial`  
_L200-214_
- L203 _public function_ `FArchiveMaterial(FMaterialUId InId = 0) : Id(InId)`
- L211 _public member_ `FMaterialUId Id;`
- L212 _public member_ `FCADMaterial Material;`
- L213 _public member_ `FMaterialUId UEMaterialUId;`

#### class `CADLibrary::FArchiveSceneGraph`  
`class FArchiveSceneGraph`  
_L216-302_
- L221 _public prototype_ `void SerializeMockUp(const TCHAR* Filename);`
- L222 _public prototype_ `void DeserializeMockUpFile(const TCHAR* Filename);`
- L225 _public member_ `uint32 SceneGraphId = 0;`
- L226 _public member_ `FString CADFileName;`
- L227 _public member_ `FString ArchiveFileName;`
- L228 _public member_ `FString FullPath;`
- L230 _public member_ `TMap<FMaterialUId, FArchiveColor> ColorHIdToColor;`
- L231 _public member_ `TMap<FMaterialUId, FArchiveMaterial> MaterialHIdToMaterial;`
- L233 _public member_ `TArray<FArchiveBody> Bodies;`
- L234 _public member_ `TArray<FArchiveReference> References;`
- L235 _public member_ `TArray<FArchiveUnloadedReference> UnloadedReferences;`
- L236 _public member_ `TArray<FFileDescriptor> ExternalReferenceFiles;`
- L237 _public member_ `TArray<FArchiveInstance> Instances;`
- L238 _public member_ `TArray<FArchiveOverrideOccurrence> OverrideOccurrences;`
- L240 _public member_ `TArray<int32> CADIdToIndex;`
- L241 _public member_ `FCadId LastEntityId = 1;`
- L243 _public function_ `void Reserve(uint32* ComponentCount)`
- L260 _public prototype_ `FArchiveInstance& AddInstance(const FArchiveCADObject& Parent);`
- L261 _public prototype_ `FArchiveInstance& GetInstance(const FCadId CadId);`
- L262 _public prototype_ `void RemoveLastInstance();`
- L263 _public prototype_ `bool IsAInstance(const FCadId CadId) const;`
- L265 _public prototype_ `FArchiveReference& AddReference(FArchiveUnloadedReference&);`
- L266 _public prototype_ `FArchiveReference& AddReference(FArchiveInstance& Parent);`
- L267 _public prototype_ `FArchiveReference& GetReference(const FCadId CadId);`
- L268 _public function_ `FArchiveReference* GetRootReference()`
- L274 _public prototype_ `void RemoveLastReference();`
- L275 _public prototype_ `bool IsAReference(FCadId CadId) const;`
- L277 _public prototype_ `FArchiveReference& AddOccurrence(FArchiveReference& Parent);`
- L278 _public prototype_ `void RemoveLastOccurrence();`
- L280 _public prototype_ `FArchiveUnloadedReference& AddUnloadedReference(FArchiveInstance& Parent);`
- L281 _public prototype_ `FArchiveUnloadedReference& GetUnloadedReference(const FCadId CadId);`
- L282 _public prototype_ `void RemoveLastUnloadedReference();`
- L283 _public prototype_ `bool IsAUnloadedReference(const FCadId CadId) const;`
- L285 _public prototype_ `FArchiveOverrideOccurrence& AddOverrideOccurrence(FArchiveWithOverridenChildren& Parent);`
- L286 _public prototype_ `FArchiveOverrideOccurrence& GetOverrideOccurrence(const FCadId CadId);`
- L288 _public prototype_ `FArchiveBody& AddBody(FArchiveReference& Parent, EMesher InMesher);`
- L289 _public prototype_ `FArchiveBody& GetBody(const FCadId CadId);`
- L290 _public prototype_ `void RemoveLastBody();`
- L291 _public prototype_ `bool IsABody(const FCadId CadId) const;`
- L293 _public prototype_ `void AddExternalReferenceFile(const FArchiveUnloadedReference& Reference);`
- L295 _public function_ `int32 ReferencesCount() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/TUniqueTechSoftObj.h` (Public)


#### class `CADLibrary::TUniqueTSObjBase`  
`template<class ObjectType, class IndexerType> class TUniqueTSObjBase`  
_L33-216_
- L40 _public function_ `TUniqueTSObjBase() : bDataFromTechSoft(false) , Status(A3DStatus::A3D_SUCCESS)` — Constructor of an initialized ObjectType object
- L51 _public function_ `explicit TUniqueTSObjBase(IndexerType DataPtr) : bDataFromTechSoft(false)` — Constructor of an filled ObjectType object with the data of DataPtr @param DataPtr: the pointer of the data to copy
- L58 _public function_ `~TUniqueTSObjBase()`
- L66 _public function_ `A3DStatus FillFrom(IndexerType EntityPtr)` — Fill the structure with the data of a new DataPtr
- L86 _public function_ `template<typename... InArgTypes> A3DStatus FillWith(A3DStatus(*Getter)(const A3DEntity*, ObjectType*, InArgTypes&&...), const A3DEntity* EntityPtr, InArgTypes&&... Args)`
- L109 _public function_ `void Reset()` — Empty the structure
- L119 _public function_ `A3DStatus GetStatus()` — Return - A3DStatus::A3D_SUCCESS if the data is filled - A3DStatus::A3D_ERROR if the data is empty
- L127 _public function_ `const bool IsValid() const` — Return true if the data is filled
- L133 _public prototype_ `TUniqueTSObjBase(const TUniqueTSObjBase&) = delete;` — Non-copyable
- L134 _public prototype_ `TUniqueTSObjBase& operator=(const TUniqueTSObjBase&) = delete;`
- L138 _public function_ `const ObjectType& operator*() const`
- L143 _public function_ `ObjectType& operator*()`
- L149 _public function_ `const ObjectType* operator->() const`
- L155 _public function_ `ObjectType* operator->()`
- L164 _public function_ `ObjectType* GetPtr()` — Return the structure pointer
- L174 _private member_ `ObjectType Data;`
- L175 _private member_ `bool bDataFromTechSoft = false;`
- L176 _private member_ `A3DStatus Status = A3DStatus::A3D_ERROR;`
- L183 _private prototype_ `IndexerType GetDefaultIndexerValue() const;` — DefaultValue is used to initialize "Data" with GetData method According to IndexerType, the value is either nullptr for const A3DEntity* either something like "A3D_DEFAULT_MATERIAL_INDEX" ((A3DUns16)-1) for uint32 @see ResetData
- L185 _private prototype_ `void InitializeData() #ifdef USE_TECHSOFT_SDK ;`
- L194 _private prototype_ `A3DStatus GetData(IndexerType AsmModelFilePtr);`
- L203 _private function_ `void ResetData()`

#### class `CADLibrary::FTechSoftDefaultValue`  
`class FTechSoftDefaultValue`  
_L713-722_
- L716 _public member_ `static const uint32 Material;`
- L717 _public member_ `static const uint32 Picture;`
- L718 _public member_ `static const uint32 RgbColor;`
- L719 _public member_ `static const uint32 Style;`
- L720 _public member_ `static const uint32 TextureApplication;`
- L721 _public member_ `static const uint32 TextureDefinition;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace CADLibrary`
- L220 _typedef_ `template<class ObjectType> using TUniqueTSObj = TUniqueTSObjBase<ObjectType, const A3DEntity*>;` (scope `CADLibrary`)
- L223 _typedef_ `template<class ObjectType> using TUniqueTSObjFromIndex = TUniqueTSObjBase<ObjectType, uint32>;` (scope `CADLibrary`)
- L229 _prototype_ `template<> void TUniqueTSObj<A3DAsmModelFileData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L231 _prototype_ `template<> void TUniqueTSObj<A3DAsmPartDefinitionData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L233 _prototype_ `template<> void TUniqueTSObj<A3DAsmProductOccurrenceData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L235 _prototype_ `template<> void TUniqueTSObj<A3DAsmProductOccurrenceDataCV5>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L237 _prototype_ `template<> void TUniqueTSObj<A3DAsmProductOccurrenceDataSLW>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L239 _prototype_ `template<> void TUniqueTSObj<A3DAsmProductOccurrenceDataNX>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L241 _prototype_ `template<> void TUniqueTSObj<A3DBoundingBoxData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L243 _prototype_ `template<> void TUniqueTSObj<A3DCopyAndAdaptBrepModelData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L245 _prototype_ `template<> void TUniqueTSObj<A3DCrvCircleData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L247 _prototype_ `template<> void TUniqueTSObj<A3DCrvCompositeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L249 _prototype_ `template<> void TUniqueTSObj<A3DCrvEllipseData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L251 _prototype_ `template<> void TUniqueTSObj<A3DCrvHelixData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L253 _prototype_ `template<> void TUniqueTSObj<A3DCrvHyperbolaData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L255 _prototype_ `template<> void TUniqueTSObj<A3DCrvLineData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L257 _prototype_ `template<> void TUniqueTSObj<A3DCrvNurbsData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L259 _prototype_ `template<> void TUniqueTSObj<A3DCrvParabolaData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L261 _prototype_ `template<> void TUniqueTSObj<A3DCrvPolyLineData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L263 _prototype_ `template<> void TUniqueTSObj<A3DCrvTransformData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L265 _prototype_ `template<> void TUniqueTSObj<A3DDomainData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L267 _prototype_ `template<> void TUniqueTSObj<A3DGlobalData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L269 _prototype_ `template<> void TUniqueTSObj<A3DGraphicsData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L271 _prototype_ `template<> void TUniqueTSObj<A3DIntervalData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L273 _prototype_ `template<> void TUniqueTSObj<A3DMiscAttributeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L275 _prototype_ `template<> void TUniqueTSObj<A3DMiscCartesianTransformationData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L277 _prototype_ `template<> void TUniqueTSObj<A3DMiscEntityReferenceData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L279 _prototype_ `template<> void TUniqueTSObj<A3DMiscGeneralTransformationData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L281 _prototype_ `template<> void TUniqueTSObj<A3DMiscMaterialPropertiesData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L283 _prototype_ `template<> void TUniqueTSObj<A3DMiscReferenceOnCsysItemData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L285 _prototype_ `template<> void TUniqueTSObj<A3DMiscReferenceOnTessData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L287 _prototype_ `template<> void TUniqueTSObj<A3DMiscReferenceOnTopologyData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L289 _prototype_ `template<> void TUniqueTSObj<A3DMiscSingleAttributeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L291 _prototype_ `template<> void TUniqueTSObj<A3DRWParamsExportPrcData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L293 _prototype_ `template<> void TUniqueTSObj<A3DRiBrepModelData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L295 _prototype_ `template<> void TUniqueTSObj<A3DRiCoordinateSystemData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L297 _prototype_ `template<> void TUniqueTSObj<A3DRiDirectionData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L299 _prototype_ `template<> void TUniqueTSObj<A3DRiPolyBrepModelData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L301 _prototype_ `template<> void TUniqueTSObj<A3DRiRepresentationItemData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L303 _prototype_ `template<> void TUniqueTSObj<A3DRiSetData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L305 _prototype_ `template<> void TUniqueTSObj<A3DRootBaseData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L307 _prototype_ `template<> void TUniqueTSObj<A3DRootBaseWithGraphicsData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L309 _prototype_ `template<> void TUniqueTSObj<A3DRWParamsTessellationData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L311 _prototype_ `template<> void TUniqueTSObj<A3DSewOptionsData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L313 _prototype_ `template<> void TUniqueTSObj<A3DSurfBlend01Data>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L315 _prototype_ `template<> void TUniqueTSObj<A3DSurfBlend02Data>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L317 _prototype_ `template<> void TUniqueTSObj<A3DSurfBlend03Data>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L319 _prototype_ `template<> void TUniqueTSObj<A3DSurfConeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L321 _prototype_ `template<> void TUniqueTSObj<A3DSurfCylinderData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L323 _prototype_ `template<> void TUniqueTSObj<A3DSurfCylindricalData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L325 _prototype_ `template<> void TUniqueTSObj<A3DSurfExtrusionData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L327 _prototype_ `template<> void TUniqueTSObj<A3DSurfFromCurvesData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L329 _prototype_ `template<> void TUniqueTSObj<A3DSurfNurbsData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L331 _prototype_ `template<> void TUniqueTSObj<A3DSurfPipeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L333 _prototype_ `template<> void TUniqueTSObj<A3DSurfPlaneData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L335 _prototype_ `template<> void TUniqueTSObj<A3DSurfRevolutionData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L337 _prototype_ `template<> void TUniqueTSObj<A3DSurfRuledData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L339 _prototype_ `template<> void TUniqueTSObj<A3DSurfSphereData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L341 _prototype_ `template<> void TUniqueTSObj<A3DSurfTorusData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L343 _prototype_ `template<> void TUniqueTSObj<A3DTess3DData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L345 _prototype_ `template<> void TUniqueTSObj<A3DTessBaseData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L347 _prototype_ `template<> void TUniqueTSObj<A3DTopoBodyData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L349 _prototype_ `template<> void TUniqueTSObj<A3DTopoBrepDataData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L351 _prototype_ `template<> void TUniqueTSObj<A3DTopoCoEdgeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L353 _prototype_ `template<> void TUniqueTSObj<A3DTopoConnexData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L355 _prototype_ `template<> void TUniqueTSObj<A3DTopoContextData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L357 _prototype_ `template<> void TUniqueTSObj<A3DTopoEdgeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L359 _prototype_ `template<> void TUniqueTSObj<A3DTopoFaceData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L361 _prototype_ `template<> void TUniqueTSObj<A3DTopoLoopData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L363 _prototype_ `template<> void TUniqueTSObj<A3DTopoShellData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L365 _prototype_ `template<> void TUniqueTSObj<A3DTopoUniqueVertexData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L367 _prototype_ `template<> void TUniqueTSObj<A3DTopoWireEdgeData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L369 _prototype_ `template<> void TUniqueTSObj<A3DVector2dData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L371 _prototype_ `template<> void TUniqueTSObj<A3DVector3dData>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L374 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmModelFileData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L376 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmPartDefinitionData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L378 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmProductOccurrenceData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L380 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmProductOccurrenceDataCV5>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L382 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmProductOccurrenceDataSLW>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L384 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DAsmProductOccurrenceDataNX>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L386 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DBoundingBoxData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L388 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCopyAndAdaptBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L390 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvCircleData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L392 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvCompositeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L394 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvEllipseData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L396 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvHelixData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L398 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvHyperbolaData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L400 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvLineData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L402 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvNurbsData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L404 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvParabolaData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L406 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvPolyLineData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L408 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DCrvTransformData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L410 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DDomainData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L412 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DGlobalData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L414 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DGraphicsData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L416 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DIntervalData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L418 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscAttributeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L420 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscCartesianTransformationData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L422 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscEntityReferenceData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L424 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscGeneralTransformationData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L426 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscMaterialPropertiesData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L428 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscReferenceOnCsysItemData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L430 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscReferenceOnTessData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L432 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscReferenceOnTopologyData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L434 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DMiscSingleAttributeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L436 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRWParamsExportPrcData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L438 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L440 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiCoordinateSystemData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L442 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiDirectionData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L444 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiPolyBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L446 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiRepresentationItemData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L448 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRiSetData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L450 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRootBaseData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L452 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRootBaseWithGraphicsData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L454 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DRWParamsTessellationData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L456 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSewOptionsData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L458 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfBlend01Data>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L460 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfBlend02Data>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L462 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfBlend03Data>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L464 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfConeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L466 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfCylinderData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L468 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfCylindricalData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L470 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfExtrusionData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L472 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfFromCurvesData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L474 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfNurbsData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L476 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfPipeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L478 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfPlaneData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L480 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfRevolutionData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L482 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfRuledData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L484 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfSphereData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L486 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DSurfTorusData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L488 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTess3DData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L490 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTessBaseData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L492 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoBodyData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L494 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoBrepDataData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L496 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoCoEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L498 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoConnexData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L500 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoContextData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L502 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L504 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoFaceData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L506 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoLoopData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L508 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoShellData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L510 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoUniqueVertexData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L512 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DTopoWireEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L514 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DVector2dData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L516 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DVector3dData>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L519 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmModelFileData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L521 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmPartDefinitionData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L523 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmProductOccurrenceData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L525 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmProductOccurrenceDataCV5>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L527 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmProductOccurrenceDataSLW>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L529 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DAsmProductOccurrenceDataNX>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L531 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DBoundingBoxData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L533 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCopyAndAdaptBrepModelData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L535 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvCircleData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L537 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvCompositeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L539 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvEllipseData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L541 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvHelixData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L543 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvHyperbolaData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L545 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvLineData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L547 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvNurbsData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L549 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvParabolaData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L551 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvPolyLineData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L553 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DCrvTransformData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L555 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DDomainData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L557 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DGlobalData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L559 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DGraphicsData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L561 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DIntervalData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L563 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscAttributeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L565 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscCartesianTransformationData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L567 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscEntityReferenceData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L569 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscGeneralTransformationData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L571 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscMaterialPropertiesData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L573 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscReferenceOnCsysItemData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L575 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscReferenceOnTessData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L577 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscReferenceOnTopologyData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L579 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DMiscSingleAttributeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L581 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRWParamsExportPrcData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L583 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiBrepModelData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L585 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiCoordinateSystemData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L587 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiDirectionData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L589 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiPolyBrepModelData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L591 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiRepresentationItemData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L593 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRiSetData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L595 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRootBaseData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L597 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRootBaseWithGraphicsData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L599 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DRWParamsTessellationData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L601 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSewOptionsData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L603 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfBlend01Data>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L605 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfBlend02Data>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L607 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfBlend03Data>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L609 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfConeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L611 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfCylinderData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L613 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfCylindricalData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L615 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfExtrusionData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L617 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfFromCurvesData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L619 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfNurbsData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L621 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfPipeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L623 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfPlaneData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L625 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfRevolutionData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L627 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfRuledData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L629 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfSphereData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L631 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DSurfTorusData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L633 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTess3DData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L635 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTessBaseData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L637 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoBodyData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L639 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoBrepDataData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L641 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoCoEdgeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L643 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoConnexData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L645 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoContextData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L647 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoEdgeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L649 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoFaceData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L651 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoLoopData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L653 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoShellData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L655 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoUniqueVertexData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L657 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DTopoWireEdgeData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L659 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DVector2dData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L661 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DVector3dData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)
- L666 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphMaterialData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L668 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphPictureData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L670 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphRgbColorData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L672 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphStyleData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L674 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphTextureApplicationData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L676 _prototype_ `template<> void TUniqueTSObjFromIndex<A3DGraphTextureDefinitionData>::InitializeData();` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L679 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphMaterialData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L681 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphPictureData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L683 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphRgbColorData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L685 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphStyleData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L687 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphTextureApplicationData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L689 _prototype_ `template<> A3DStatus TUniqueTSObjFromIndex<A3DGraphTextureDefinitionData>::GetData(const uint32 InEntityIndex);` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L692 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphMaterialData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L694 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphPictureData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L696 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphRgbColorData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L698 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphStyleData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L700 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphTextureApplicationData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L702 _prototype_ `template<> uint32 TUniqueTSObjFromIndex<A3DGraphTextureDefinitionData>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObjFromIndex`)
- L707 _prototype_ `template<> void TUniqueTSObj<A3DUTF8Char*>::InitializeData();` (scope `CADLibrary::TUniqueTSObj`)
- L709 _prototype_ `template<> A3DStatus TUniqueTSObj<A3DUTF8Char*>::GetData(const A3DEntity* InEntityPtr);` (scope `CADLibrary::TUniqueTSObj`)
- L711 _prototype_ `template<> const A3DEntity* TUniqueTSObj<A3DUTF8Char*>::GetDefaultIndexerValue() const;` (scope `CADLibrary::TUniqueTSObj`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/TechSoftInterface.h` (Public)


#### class `CADLibrary::FTechSoftInterface`  
`class FTechSoftInterface`  
_L39-66_
- L43 _public prototype_ `static FTechSoftInterface& Get();`
- L49 _public function_ `bool IsExternal()` — Returns true if the object has been created outside of the memory pool of the running process This is the case when the object has been created by the DatasmithRuntime plugin
- L54 _public function_ `void SetExternal(bool Value)`
- L59 _public prototype_ `bool InitializeKernel(const TCHAR* = TEXT(""));`
- L60 _public prototype_ `const TCHAR* GetVersion();`
- L64 _private member_ `bool bIsExternal = false;`
- L65 _private member_ `bool bIsInitialize = false;`

#### class `CADLibrary::FUniqueTechSoftModelFile`  
`class FUniqueTechSoftModelFile`  
_L164-227_
- desc: Class to manage model file lifetime
- L168 _public function_ `FUniqueTechSoftModelFile() : ModelFile(nullptr)`
- L173 _public function_ `explicit FUniqueTechSoftModelFile(A3DAsmModelFile* InModelFile) : ModelFile(InModelFile)`
- L178 _public function_ `~FUniqueTechSoftModelFile()`
- L186 _public function_ `const bool IsValid() const` — Return true if the model is loaded
- L192 _public prototype_ `FUniqueTechSoftModelFile(const FUniqueTechSoftModelFile&) = delete;` — Non-copyable
- L193 _public prototype_ `FUniqueTechSoftModelFile& operator=(const FUniqueTechSoftModelFile&) = delete;`
- L195 _public function_ `FUniqueTechSoftModelFile(FUniqueTechSoftModelFile&& Old) : ModelFile(Old.ModelFile)`
- L201 _public function_ `FUniqueTechSoftModelFile& operator=(FUniqueTechSoftModelFile&& Old)`
- L209 _public function_ `A3DAsmModelFile* Get()`
- L214 _public function_ `void Reset()`
- L226 _private member_ `A3DAsmModelFile* ModelFile;`

#### enum `CADLibrary::EModelerType`  
`enum EModelerType : uint32`  
_L229-282_
- L231 _public enumerator_ `ModelerUnknown = 0`
- L232 _public enumerator_ `ModelerCatia = 2` — ModelerUnknown = 0,               < User Modeler.
- L233 _public enumerator_ `ModelerCatiaV5 = 3` — ModelerCatia = 2,                 < CATIA Modeler.
- L234 _public enumerator_ `ModelerCadds = 4` — ModelerCatiaV5 = 3,               < CATIA V5 Modeler.
- L235 _public enumerator_ `ModelerUnigraphics = 5` — ModelerCadds = 4,                 < CADDS Modeler.
- L236 _public enumerator_ `ModelerParasolid = 6` — ModelerUnigraphics = 5,           < Unigraphics Modeler.
- L237 _public enumerator_ `ModelerEuclid = 7` — ModelerParasolid = 6,             < Parasolid Modeler.
- L238 _public enumerator_ `ModelerIges = 9` — ModelerEuclid = 7,                < Euclid Modeler.
- L239 _public enumerator_ `ModelerUnisurf = 10` — ModelerIges = 9,                  < IGES Modeler.
- L240 _public enumerator_ `ModelerVda = 11` — ModelerUnisurf = 10,              < Unisurf Modeler.
- L241 _public enumerator_ `ModelerStl = 12` — ModelerVda = 11,                  < VDA Modeler.
- L242 _public enumerator_ `ModelerWrl = 13` — ModelerStl = 12,                  < STL Modeler.
- L243 _public enumerator_ `ModelerDxf = 14` — ModelerWrl = 13,                  < WRL Modeler.
- L244 _public enumerator_ `ModelerAcis = 15` — ModelerDxf = 14,                  < DXF Modeler.
- L245 _public enumerator_ `ModelerProE = 16` — ModelerAcis = 15,                 < ACIS Modeler.
- L246 _public enumerator_ `ModelerStep = 18` — ModelerProE = 16,                 < Pro/E Modeler.
- L247 _public enumerator_ `ModelerIdeas = 19` — ModelerStep = 18,                 < STEP Modeler.
- L248 _public enumerator_ `ModelerJt = 20` — ModelerIdeas = 19,                < I-DEAS Modeler.
- L249 _public enumerator_ `ModelerSlw = 22` — ModelerJt = 20,                   < JT Modeler.
- L250 _public enumerator_ `ModelerCgr = 23` — ModelerSlw = 22,                  < SolidWorks Modeler.
- L251 _public enumerator_ `ModelerPrc = 24` — ModelerCgr = 23,                  < CGR Modeler.
- L252 _public enumerator_ `ModelerXvl = 25` — ModelerPrc = 24,                  < PRC Modeler.
- L253 _public enumerator_ `ModelerHpgl = 26` — ModelerXvl = 25,                  < XVL Modeler.
- L254 _public enumerator_ `ModelerTopSolid = 27` — ModelerHpgl = 26,                 < HPGL Modeler.
- L255 _public enumerator_ `ModelerOneSpaceDesigner = 28` — ModelerTopSolid = 27,             < TopSolid Modeler.
- L256 _public enumerator_ `Modeler3dxml = 29` — ModelerOneSpaceDesigner = 28,     < OneSpace designer Modeler.
- L257 _public enumerator_ `ModelerInventor = 30` — Modeler3dxml = 29,                < 3DXML Modeler.
- L258 _public enumerator_ `ModelerPostScript = 31` — ModelerInventor = 30,             < Inventor Modeler.
- L259 _public enumerator_ `ModelerPDF = 32` — ModelerPostScript = 31,           < Postscript Modeler.
- L260 _public enumerator_ `ModelerU3D = 33` — ModelerPDF = 32,                  < PDF Modeler.
- L261 _public enumerator_ `ModelerIFC = 34` — ModelerU3D = 33,                  < U3D Modeler.
- L262 _public enumerator_ `ModelerDWG = 35` — ModelerIFC = 34,                  < IFC Modeler.
- L263 _public enumerator_ `ModelerDWF = 36` — ModelerDWG = 35,                  < DWG Modeler.
- L264 _public enumerator_ `ModelerSE = 37` — ModelerDWF = 36,                  < DWF Modeler.
- L265 _public enumerator_ `ModelerOBJ = 38` — ModelerSE = 37,                   < SolidEdge Modeler.
- L266 _public enumerator_ `ModelerKMZ = 39` — ModelerOBJ = 38,                  < OBJ Modeler.
- L267 _public enumerator_ `ModelerDAE = 40` — ModelerKMZ = 39,                  < KMZ Modeler.
- L268 _public enumerator_ `Modeler3DS = 41` — ModelerDAE = 40,                  < COLLADA Modeler.
- L269 _public enumerator_ `ModelerRhino = 43` — Modeler3DS = 41,                  < 3DS Modeler.
- L270 _public enumerator_ `ModelerXML = 44` — ModelerRhino = 43,                < Rhino Modeler.
- L271 _public enumerator_ `Modeler3mf = 45` — ModelerXML = 44,                  < XML Modeler.
- L272 _public enumerator_ `ModelerScs = 46` — Modeler3mf = 45,                  < 3MF Modeler.
- L273 _public enumerator_ `Modeler3dHtml = 47` — ModelerScs = 46,                  < SCS Modeler.
- L274 _public enumerator_ `ModelerHsf = 48` — Modeler3dHtml = 47,               < 3DHTML Modeler.
- L275 _public enumerator_ `ModelerGltf = 49` — ModelerHsf = 48,                  < Hsf Modeler.
- L276 _public enumerator_ `ModelerRevit = 50` — ModelerGltf = 49,                 < GL Modeler.
- L277 _public enumerator_ `ModelerFBX = 51` — ModelerRevit = 50,                < Revit Modeler.
- L278 _public enumerator_ `ModelerStepXML = 52` — ModelerFBX = 51,                  < FBX Modeler.
- L279 _public enumerator_ `ModelerPLMXML = 53` — ModelerStepXML = 52,              < StepXML Modeler.
- L280 _public enumerator_ `ModelerNavisworks = 54` — ModelerPLMXML = 53,               < PLMXML Modeler.
- L281 _public enumerator_ `ModelerLast` — ModelerNavisworks = 54,			 < For Future Use: Navisworks Modeler.

#### Free symbols / members of external scopes

- L26 _macro_ `#define JSON_ENTRY_BODY_UNIT TEXT("BodyUnit")`
- L27 _macro_ `#define JSON_ENTRY_COLOR_NAME TEXT("ColorName")`
- L28 _macro_ `#define JSON_ENTRY_MATERIAL_NAME TEXT("MaterialName")`
- L30 _typedef_ `typedef void A3DAsmModelFile;`
- L32 _namespace_ `namespace CADLibrary`
- L68 _namespace_ `namespace TechSoftInterface` (scope `CADLibrary`)
- L70 _prototype_ `bool TECHSOFT_InitializeKernel(const TCHAR* = TEXT(""));` (scope `CADLibrary::TechSoftInterface`)
- L72 _prototype_ `FString GetTechSoftVersion();` (scope `CADLibrary::TechSoftInterface`)
- L76 _prototype_ `FUniqueTechSoftModelFile LoadModelFileFromFile(const A3DImport& Import, A3DStatus& Status);` (scope `CADLibrary::TechSoftInterface`)
- L77 _prototype_ `FUniqueTechSoftModelFile LoadModelFileFromPrcFile(const A3DUTF8Char* CADFileName, A3DRWParamsPrcReadHelper** ReadHelper);` (scope `CADLibrary::TechSoftInterface`)
- L79 _prototype_ `A3DStatus AdaptBRepInModelFile(A3DAsmModelFile* ModelFile, const A3DCopyAndAdaptBrepModelData& Setting, int32& ErrorCount, A3DCopyAndAdaptBrepModelErrorData** Errors);` (scope `CADLibrary::TechSoftInterface`)
- L81 _prototype_ `A3DStatus DeleteModelFile(A3DAsmModelFile* ModelFile);` (scope `CADLibrary::TechSoftInterface`)
- L82 _prototype_ `A3DStatus DeleteEntity(A3DEntity* pEntity);` (scope `CADLibrary::TechSoftInterface`)
- L84 _prototype_ `A3DGlobal* GetGlobalPointer();` (scope `CADLibrary::TechSoftInterface`)
- L85 _prototype_ `A3DEntity* GetPointerFromIndex(const uint32 Index, const A3DEEntityType Type);` (scope `CADLibrary::TechSoftInterface`)
- L87 _prototype_ `A3DStatus GetSurfaceAsNurbs(const A3DSurfBase* SurfacePtr, A3DSurfNurbsData* DataPtr, A3DDouble Tolerance, A3DBool bUseSameParameterization);` (scope `CADLibrary::TechSoftInterface`)
- L88 _prototype_ `A3DStatus GetSurfaceDomain(const A3DSurfBase* SurfacePtr, A3DDomainData& OutDomain);` (scope `CADLibrary::TechSoftInterface`)
- L96 _prototype_ `A3DStatus Evaluate(const A3DSurfBase* SurfacePtr, const A3DVector2dData& UVParameter, A3DUns32 Derivatives, A3DVector3dData* OutPointAndDerivatives);` (scope `CADLibrary::TechSoftInterface`) — @param OutPointAndDerivatives size must be equal to (Derivatives+1)*(Derivatives+1) @param Derivatives The number of derivatives must be less or equal to 2 @param OutPointAndDerivatives = Point, Derivatives=1 OutPointAndDerivatives = Point + dU + dV, ... @see A3DSDKAdvancedTools.h for more details
- L98 _prototype_ `A3DStatus GetCurveAsNurbs(const A3DCrvBase* A3DCurve, A3DCrvNurbsData* DataPtr, A3DDouble Tolerance, A3DBool bUseSameParameterization);` (scope `CADLibrary::TechSoftInterface`)
- L100 _prototype_ `A3DStatus GetOriginalFilePathName(const A3DAsmProductOccurrence* A3DOccurrencePtr, A3DUTF8Char** FilePathUTF8Ptr);` (scope `CADLibrary::TechSoftInterface`)
- L101 _prototype_ `A3DStatus GetFilePathName(const A3DAsmProductOccurrence* A3DOccurrencePtr, A3DUTF8Char** FilePathUTF8Ptr);` (scope `CADLibrary::TechSoftInterface`)
- L103 _prototype_ `A3DStatus GetEntityType(const A3DEntity* pEntity, A3DEEntityType* peEntityType);` (scope `CADLibrary::TechSoftInterface`)
- L104 _prototype_ `bool IsEntityBaseWithGraphicsType(const A3DEntity* pEntity);` (scope `CADLibrary::TechSoftInterface`)
- L105 _prototype_ `bool IsEntityBaseType(const A3DEntity* EntityPtr);` (scope `CADLibrary::TechSoftInterface`)
- L106 _prototype_ `bool IsMaterialTexture(const uint32 MaterialIndex);` (scope `CADLibrary::TechSoftInterface`)
- L109 _prototype_ `FUniqueTechSoftModelFile CreateAsmModelFile(const A3DAsmModelFileData& ModelFileData);` (scope `CADLibrary::TechSoftInterface`)
- L111 _prototype_ `A3DRiBrepModel* CreateRiBRepModel(const A3DRiBrepModelData& RiBRepModelData);` (scope `CADLibrary::TechSoftInterface`)
- L112 _prototype_ `A3DAsmPartDefinition* CreateAsmPartDefinition(const A3DAsmPartDefinitionData& PartDefinitionData);` (scope `CADLibrary::TechSoftInterface`)
- L113 _prototype_ `A3DAsmProductOccurrence* CreateAsmProductOccurrence(const A3DAsmProductOccurrenceData& ProductOccurrenceData);` (scope `CADLibrary::TechSoftInterface`)
- L114 _prototype_ `A3DMiscAttribute* CreateMiscAttribute(const A3DMiscAttributeData& AttributeData);` (scope `CADLibrary::TechSoftInterface`)
- L115 _prototype_ `A3DAsmModelFile* CreateModelFile(const A3DAsmModelFileData& ModelFileData);` (scope `CADLibrary::TechSoftInterface`)
- L116 _prototype_ `A3DTopoBrepData* CreateTopoBRep(const A3DTopoBrepDataData& TopoBRepDataData);` (scope `CADLibrary::TechSoftInterface`)
- L117 _prototype_ `A3DTopoCoEdge* CreateTopoCoEdge(const A3DTopoCoEdgeData& TopoCoEdgeData);` (scope `CADLibrary::TechSoftInterface`)
- L118 _prototype_ `A3DTopoConnex* CreateTopoConnex(const A3DTopoConnexData& TopoConnexData);` (scope `CADLibrary::TechSoftInterface`)
- L119 _prototype_ `A3DTopoEdge* CreateTopoEdge(const A3DTopoEdgeData& TopoEdgeData);` (scope `CADLibrary::TechSoftInterface`)
- L120 _prototype_ `A3DTopoFace* CreateTopoFace(const A3DTopoFaceData& TopoFaceData);` (scope `CADLibrary::TechSoftInterface`)
- L121 _prototype_ `A3DTopoLoop* CreateTopoLoop(const A3DTopoLoopData& TopoLoopData);` (scope `CADLibrary::TechSoftInterface`)
- L122 _prototype_ `A3DTopoShell* CreateTopoShell(const A3DTopoShellData& TopoShellData);` (scope `CADLibrary::TechSoftInterface`)
- L124 _prototype_ `A3DCrvNurbs* CreateCurveTransform(const A3DCrvTransformData& CurveTransformData);` (scope `CADLibrary::TechSoftInterface`)
- L125 _prototype_ `A3DCrvNurbs* CreateCurveNurbs(const A3DCrvNurbsData& CurveNurbsData);` (scope `CADLibrary::TechSoftInterface`)
- L127 _prototype_ `A3DSurfNurbs* CreateSurfaceCylinder(const A3DSurfCylinderData& SurfaceCylinderData);` (scope `CADLibrary::TechSoftInterface`)
- L128 _prototype_ `A3DSurfNurbs* CreateSurfaceNurbs(const A3DSurfNurbsData& SurfaceNurbsData);` (scope `CADLibrary::TechSoftInterface`)
- L130 _prototype_ `A3DGraphics* CreateGraphics(const A3DGraphicsData& GraphicsData);` (scope `CADLibrary::TechSoftInterface`)
- L132 _prototype_ `A3DStatus LinkCoEdges(A3DTopoCoEdge* CoEdgePtr, A3DTopoCoEdge* NeighbourCoEdgePtr);` (scope `CADLibrary::TechSoftInterface`)
- L134 _prototype_ `A3DStatus SetRootBase(A3DEntity* EntityPtr, const A3DRootBaseData& RootBaseData);` (scope `CADLibrary::TechSoftInterface`)
- L135 _prototype_ `A3DStatus SetRootBaseWithGraphics(const A3DRootBaseWithGraphicsData& RootBaseWithGraphicsData, A3DRootBaseWithGraphics* RootPtr);` (scope `CADLibrary::TechSoftInterface`)
- L137 _prototype_ `A3DStatus ExportModelFileToPrcFile(const A3DAsmModelFile* ModelFile, const A3DRWParamsExportPrcData* ParamsExportData, const A3DUTF8Char* CADFileName, A3DRWParamsPrcWriteHelper** PrcWriteHelper);` (scope `CADLibrary::TechSoftInterface`)
- L139 _prototype_ `A3DUns32 InsertGraphRgbColor(const A3DGraphRgbColorData& InRgbColorData);` (scope `CADLibrary::TechSoftInterface`)
- L140 _prototype_ `A3DUns32 InsertGraphMaterial(const A3DGraphMaterialData& InMaterialData);` (scope `CADLibrary::TechSoftInterface`)
- L141 _prototype_ `A3DUns32 InsertGraphStyle(const A3DGraphStyleData& InStyleData);` (scope `CADLibrary::TechSoftInterface`)
- L143 _prototype_ `double GetModelFileUnit(const A3DAsmModelFile* pModelFile);` (scope `CADLibrary::TechSoftInterface`)
- L145 _prototype_ `A3DStatus AddAttribute(A3DEntity* EntityPtr, const TCHAR*, const TCHAR*);` (scope `CADLibrary::TechSoftInterface`)
- L150 _prototype_ `A3DStatus SewModel(A3DAsmModelFile* ModelPtr, double ToleranceInCM, A3DSewOptionsData const* SewOptions);` (scope `CADLibrary::TechSoftInterface`) — @param ToleranceInCM : The maximum tolerance for the sewing (in cm).
- L155 _prototype_ `A3DStatus SewBReps(A3DRiBrepModel** BRepsToSew, uint32 const BRepCount, double ToleranceInCM, double FileUnit, A3DSewOptionsData const* SewOptions, A3DRiBrepModel*** OutNewBReps, uint32& OutNewBRepCount);` (scope `CADLibrary::TechSoftInterface`) — @param ToleranceInCM : The maximum tolerance for the sewing (in cm).

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADInterfaces/Public/TechSoftUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef void A3DAsmPartDefinition;`
- L12 _typedef_ `typedef void A3DCrvNurbs;`
- L13 _typedef_ `typedef void A3DEntity;`
- L14 _typedef_ `typedef void A3DRiRepresentationItem;`
- L15 _typedef_ `typedef void A3DSurfBase;`
- L16 _typedef_ `typedef void A3DTopoEdge;`
- L17 _typedef_ `typedef void A3DTopoFace;`
- L18 _typedef_ `typedef void A3DTopoShell;`
- L22 _namespace_ `namespace CADLibrary`
- L28 _namespace_ `namespace TechSoftInterface` (scope `CADLibrary`)
- L33 _namespace_ `namespace TechSoftUtils` (scope `CADLibrary`)
- L36 _prototype_ `bool GetBodyFromPcrFile(const FString& Filename, const FImportParameters& ImportParameters, FBodyMesh& BodyMesh);` (scope `CADLibrary::TechSoftUtils`)
- L37 _prototype_ `bool FillBodyMesh(void* BodyPtr, const FImportParameters& ImportParameters, double FileUnit, FBodyMesh& BodyMesh);` (scope `CADLibrary::TechSoftUtils`)
- L39 _prototype_ `FUniqueTechSoftModelFile SaveBodiesToPrcFile(void** Bodies, uint32 BodyCount, const FString& Filename, const FString& JsonString);` (scope `CADLibrary::TechSoftUtils`)
- L40 _prototype_ `void SaveModelFileToPrcFile(void* ModelFile, const FString& Filename);` (scope `CADLibrary::TechSoftUtils`)
- L42 _prototype_ `int32 SetEntityGraphicsColor(A3DEntity* InEntity, FColor Color);` (scope `CADLibrary::TechSoftUtils`)
- L44 _prototype_ `A3DAsmPartDefinition* CreatePart(TArray<A3DRiRepresentationItem*>& RepresentationItems);` (scope `CADLibrary::TechSoftUtils`)
- L45 _prototype_ `A3DRiRepresentationItem* CreateRIBRep(A3DTopoShell* TopoShellPtr);` (scope `CADLibrary::TechSoftUtils`)
- L46 _prototype_ `A3DTopoEdge* CreateTopoEdge();` (scope `CADLibrary::TechSoftUtils`)
- L47 _prototype_ `A3DTopoFace* CreateTopoFaceWithNaturalLoop(A3DSurfBase* CarrierSurface);` (scope `CADLibrary::TechSoftUtils`)
- L48 _prototype_ `A3DCrvNurbs* CreateTrimNurbsCurve(A3DCrvNurbs* CurveNurbsPtr, double UMin, double UMax, bool bIs2D);` (scope `CADLibrary::TechSoftUtils`)
- L50 _prototype_ `FColor GetColorAt(uint32 ColorIndex);` (scope `CADLibrary::TechSoftUtils`)
- L51 _prototype_ `void RestoreMaterials(const TSharedPtr<FJsonObject>& DefaultValues, CADLibrary::FBodyMesh& BodyMesh);` (scope `CADLibrary::TechSoftUtils`)
