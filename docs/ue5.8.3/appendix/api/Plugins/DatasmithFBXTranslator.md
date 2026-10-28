# Plugins / DatasmithFBXTranslator

- module root: `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator`
- headers: 8; symbols: 278
- symbol kinds: class=6, delegate=1, enum=8, enumerator=32, function=22, macro=2, member=131, prototype=58, struct=14, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, DatasmithCore, EditorFramework, Engine, LevelSequence, MeshDescription, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: DatasmithContent, DatasmithTranslator

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Private/DatasmithFBXImporterLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFBXImport, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFBXImport, Log, All);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXFileImporter.h` (Public)


#### class `FDatasmithFBXFileImporter`  
`class FDatasmithFBXFileImporter`  
_L21-84_
- desc: Imports an FBX file into the intermediate FBX scene representation
- L24 _public prototype_ `FDatasmithFBXFileImporter(FbxScene* InFbxScene, FDatasmithFBXScene* InScene, const UDatasmithFBXImportOptions* InOptions, const FDatasmithImportBaseOptions* InBaseOptions);`
- L26 _public prototype_ `void ImportScene();`
- L30 _protected prototype_ `void ConvertCoordinateSystem();` — Convert scene coordinate system
- L33 _protected prototype_ `void CreateAnimationTimelines();` — Create one timeline per animation layer contained in the animation
- L36 _protected prototype_ `void TraverseHierarchyNodeRecursively(FbxNode* ParentNode, TSharedPtr<FDatasmithFBXSceneNode>& ParentInfo);` — Recursively import Fbx scene
- L40 _protected prototype_ `void ExtractAnimations(FbxNode* Node);` — Extract all animation curves from the FBX and pack them into OutScene->AnimNodes. Note that only VRED uses this data, as for DeltaGen all animation data comes from .tml aux files
- L43 _protected prototype_ `TSharedPtr<FDatasmithFBXSceneMesh> ImportMesh(FbxMesh* InMesh, FbxNode* InNode);` — Allocate FDatasmithFBXSceneMesh
- L46 _protected prototype_ `static void DoImportMesh(FbxMesh* InMesh, FDatasmithFBXSceneMesh* Mesh);` — Convert Fbx mesh into FRawMesh
- L49 _protected prototype_ `TSharedPtr<FDatasmithFBXSceneMaterial> ImportMaterial(FbxSurfaceMaterial* InMaterial);` — Import an Fbx material
- L51 _protected prototype_ `static void FindFbxUVChannels(FbxMesh* Mesh, TArray<FFbxUVInfo>& FbxUVs);`
- L53 _protected prototype_ `bool IsOddNegativeScale(FbxAMatrix& TotalMatrix);`
- L55 _protected prototype_ `void AddCurvesForProperty(FbxProperty InProperty, FbxAnimLayer* InLayer, EDatasmithFBXSceneAnimationCurveType Type, TArray<FDatasmithFBXSceneAnimCurve>& OutCurves);`
- L57 _protected prototype_ `void FillCurveFromClipsFile(FbxAnimCurve* InCurve, EDatasmithFBXSceneAnimationCurveType InType, EDatasmithFBXSceneAnimationCurveComponent InComponent);`
- L58 _protected prototype_ `FDatasmithFBXSceneAnimCurve CreateNewCurve(FbxAnimCurve* InCurve, EDatasmithFBXSceneAnimationCurveType InType, EDatasmithFBXSceneAnimationCurveComponent InComponent);`
- L61 _protected member_ `FbxScene* InScene;` — Fbx scene which we're importing
- L64 _protected member_ `FDatasmithFBXScene* OutScene;` — Local scene which we're importing onto
- L67 _protected member_ `const UDatasmithFBXImportOptions* Options;` — All options to configure importer
- L70 _protected member_ `const FDatasmithImportBaseOptions* BaseOptions;` — Basic options like whether to import geometry or materials at all
- L73 _protected member_ `TMap<FbxMesh*, TSharedPtr<FDatasmithFBXSceneMesh> > ImportedMeshes;` — Map of FbxMesh objects to already imported FDatasmithFBXSceneMesh
- L76 _protected member_ `TMap<FbxSurfaceMaterial*, TSharedPtr<FDatasmithFBXSceneMaterial> > ImportedMaterials;` — Map of Fbx material objects to imported material structure
- L81 _protected member_ `TMap<int32, TArray<FDatasmithFBXSceneAnimCurve*>> ImportedAnimationCurves;` — Stored imported AnimCurves by DSID, which is a specific value inserted into animation curves emitted from VRED at time OutScene->TagTime. When we parse a curve from the FBX file, we'll check if we can find the corresponding DSID in here, and add the actual animation curve data to it.
- L83 _protected member_ `bool bDisplayedTwoKeysWarning = false;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXHashUtils.h` (Public)


#### class `FDatasmithFBXHashUtils`  
`class FDatasmithFBXHashUtils`  
_L12-82_
- L15 _public function_ `static void UpdateHash(FMD5& Hash, int32 Value)`
- L20 _public function_ `static void UpdateHash(FMD5& Hash, const FString& String)`
- L30 _public function_ `static void UpdateHash(FMD5& Hash, const FMD5Hash& Value)`
- L36 _public function_ `static void UpdateHash(FMD5& Hash, const FTransform& Value)`
- L60 _public function_ `template<typename T> static void UpdateHash(FMD5& Hash, const TArray<T>& Data)`
- L72 _public function_ `template<typename T> static void UpdateHashForPODArray(FMD5& Hash, const TArray<T>& Data)` — Quick hash function for POD-typed array

#### Free symbols / members of external scopes

- L85 _function_ `inline uint32 GetTypeHash(const FMD5Hash& Hash)` — Make FMD5Hash usable in TMap as a key
- L92 _function_ `inline bool operator<(const FMD5Hash& A, const FMD5Hash& B)` — Allow sorting / comparing hash values

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXImportOptions.h` (Public)


#### class `UDatasmithFBXImportOptions`  
`class UDatasmithFBXImportOptions : public UDatasmithOptionsBase`  
_L15-22_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, HideCategories=(DebugProperty))`
- inherits: `UDatasmithOptionsBase`
- L21 _public member_ `TArray<FDirectoryPath> TextureDirs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Texture folders", ToolTip="Where to look for textures"))`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXImporter.h` (Public)


#### class `FDatasmithFBXImporter`  
`class FDatasmithFBXImporter`  
_L25-41_
- desc: Base class for the VRED and DeltaGen importers, this class is responsible for parsing the intermediate FBX scene representation into Datasmith elements
- L28 _public prototype_ `FDatasmithFBXImporter();`
- L29 _public prototype_ `virtual ~FDatasmithFBXImporter();`
- L31 _public prototype_ `void GetGeometriesForMeshElementAndRelease(const TSharedRef<IDatasmithMeshElement> MeshElement, TArray<FMeshDescription>& OutMeshDescriptions);`
- L33 _public prototype_ `void BuildAssetMaps(TSharedRef<IDatasmithScene> Scene, FActorMap& ActorsByOriginalName, FMaterialMap& MaterialsByName);`
- L36 _protected member_ `TUniquePtr<FDatasmithFBXScene> IntermediateScene;`
- L38 _protected member_ `TMap<TSharedPtr<FDatasmithFBXSceneMaterial>, TSharedPtr<IDatasmithBaseMaterialElement>> ImportedMaterials;`
- L40 _protected member_ `TMap<FName, TSharedPtr<FDatasmithFBXSceneMesh>> MeshNameToFBXMesh;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define DATASMITH_FBXIMPORTER_INTERMEDIATE_FORMAT_EXT "intermediate"`
- L18 _typedef_ `using FActorMap = TMap<FName, TArray<TSharedPtr<IDatasmithActorElement>>>;`
- L19 _typedef_ `using FMaterialMap = TMap<FName, TSharedPtr<IDatasmithBaseMaterialElement>>;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXScene.h` (Public)


#### enum `ELightType`  
`enum class ELightType : uint8`  
_L20-26_
- L22 _public enumerator_ `Point`
- L23 _public enumerator_ `Directional`
- L24 _public enumerator_ `Spot`
- L25 _public enumerator_ `Area`

#### enum `EAttenuationType`  
`enum class EAttenuationType : uint8`  
_L28-33_
- L30 _public enumerator_ `None`
- L31 _public enumerator_ `Linear`
- L32 _public enumerator_ `Realistic`

#### enum `ENodeType`  
`enum class ENodeType : uint32`  
_L35-44_
- L37 _public enumerator_ `Node = 0`
- L38 _public enumerator_ `Switch = 1`
- L39 _public enumerator_ `SharedNode = 2`
- L40 _public enumerator_ `Animated = 4`
- L41 _public enumerator_ `Movable = 8`
- L42 _public enumerator_ `Toggle = 16`
- L43 _public enumerator_ `Material = 32`

#### enum `EProjectionType`  
`enum class EProjectionType : uint8`  
_L47-51_
- L49 _public enumerator_ `Perspective`
- L50 _public enumerator_ `Orghographic`

#### enum `ETextureMapType`  
`enum class ETextureMapType : uint8`  
_L53-58_
- L55 _public enumerator_ `UV = 0`
- L56 _public enumerator_ `Planar = 1`
- L57 _public enumerator_ `Triplanar = 2`

#### enum `ETextureRepeatMode`  
`enum class ETextureRepeatMode : uint8`  
_L60-67_
- L63 _public enumerator_ `Repeat = 0` — These match VRED codes
- L64 _public enumerator_ `Mirror = 9`
- L65 _public enumerator_ `Decal = 18`
- L66 _public enumerator_ `Clamp = 27`

#### struct `FDatasmithFBXSceneMaterial`  
`struct FDatasmithFBXSceneMaterial`  
_L69-140_
- L128 _public prototype_ `FDatasmithFBXSceneMaterial();`
- L130 _public member_ `FString Name;`
- L131 _public member_ `FString Type;`
- L134 _public member_ `TMap<FString, FVector4> VectorParams;` — Indexed by param name
- L135 _public member_ `TMap<FString, float> ScalarParams;`
- L136 _public member_ `TMap<FString, bool> BoolParams;`
- L137 _public member_ `TMap<FString, FTextureParams> TextureParams;`
- L139 _public member_ `TArray<TWeakPtr<FDatasmithFBXSceneMaterial>> ClonedMaterials;`

#### struct `FDatasmithFBXSceneMaterial::FTextureParams`  
`struct FTextureParams`  
_L71-126_
- L74 _public member_ `FString Path;` — Full path of the exported texture
- L77 _public member_ `FVector4 Translation;` — Used for planar projection
- L78 _public member_ `FVector4 Rotation;`
- L79 _public member_ `FVector4 Scale;`
- L82 _public member_ `FVector4 Color;` — Multiplied color
- L87 _public member_ `FVector4 Offset;` — Image space Can't combine these two in a single FVector4 because Vector4 parameters are actually float3
- L88 _public member_ `FVector4 Repeat;`
- L89 _public member_ `float Rotate;` — Degrees
- L91 _public member_ `ETextureMapType ProjectionType;`
- L92 _public member_ `ETextureRepeatMode RepeatMode;`
- L95 _public member_ `FVector4 TriplanarRotation;` — Exclusively for triplanar projection
- L96 _public member_ `FVector4 TriplanarOffsetU;`
- L97 _public member_ `FVector4 TriplanarOffsetV;`
- L98 _public member_ `FVector4 TriplanarRepeatU;`
- L99 _public member_ `FVector4 TriplanarRepeatV;`
- L100 _public member_ `FVector4 TriplanarTextureSize;`
- L101 _public member_ `float TriplanarBlendBias;`
- L103 _public member_ `bool bEnabled;`
- L105 _public function_ `FTextureParams() : Path(FString()) , Translation(0, 0, 0, 0) , Rotation(0, 0, 0, 0) , Scale(1, 1, 1, 1) , Color(1, 1, 1, 1) , Offset(0, 0, 0, 1) , Repeat(1, 1, 0, 1) , Rotate(0.0) , ProjectionType(ETextureMapType::UV) , RepeatMode(ETextureRepeatMode::Repeat) , TriplanarRotation(0, 0, 0, 1) , TriplanarOffsetU(0, 0, 0, 1) , TriplanarOffsetV(0, 0, 0, 1) , TriplanarRepeatU(1, 1, 1, 1) , TriplanarRepeatV(1, 1, 1, 1) , TriplanarTextureSize(50.0f, 50.0f, 0.0f, 1.0f) , TriplanarBlendBias(0.1f) , bEnabled(true)`

#### struct `FDatasmithFBXSceneMesh`  
`struct FDatasmithFBXSceneMesh`  
_L142-176_
- L144 _public prototype_ `FDatasmithFBXSceneMesh();`
- L145 _public prototype_ `~FDatasmithFBXSceneMesh();`
- L147 _public member_ `FString Name;`
- L150 _public member_ `FMeshDescription MeshDescription;` — Actual mesh geometry
- L153 _public member_ `int32 ImportMaterialCount;` — Number of materials which could be assigned to this mesh
- L156 _public member_ `TWeakPtr<FDatasmithFBXSceneNode> ImportMaterialsNode;` — Node whose materials will be used if mesh instance will be attached to a node without materials. Used only during Fbx import.
- L158 _public prototype_ `const FMD5Hash& GetHash();`
- L160 _public prototype_ `bool HasNormals() const;`
- L162 _public prototype_ `bool HasTangents() const;`
- L171 _public member_ `bool bFlippedFaces;` — Whether the MeshDescription polygon faces have been reversed with respect to how they were immediately after import. We use this during the merge process, as nodes may share the same mesh and have oddnegative and non-oddnegative scales. To compensate for how the vertices are baked with the node transforms during merge, we need to flip polygon facing. But since the nodes are merged in random order, this helps us coordinate whether we need to reverse or not the polygon facing once more.
- L175 _protected member_ `FMD5Hash Hash;` — MD5 of RawMesh contents

#### struct `FDatasmithFBXSceneLight`  
`struct FDatasmithFBXSceneLight`  
_L178-197_
- L180 _public member_ `FString Name;`
- L181 _public member_ `ELightType LightType;`
- L182 _public member_ `bool Enabled;`
- L183 _public member_ `bool UseTemperature;`
- L184 _public member_ `float Temperature;`
- L185 _public member_ `float Intensity;`
- L186 _public member_ `FLinearColor DiffuseColor;`
- L187 _public member_ `FLinearColor UnusedGlossyColor;`
- L188 _public member_ `float ConeInnerAngle;`
- L189 _public member_ `float ConeOuterAngle;`
- L190 _public member_ `bool AreaLightUseConeAngle;`
- L191 _public member_ `bool VisualizationVisible;`
- L192 _public member_ `EAttenuationType AttenuationType;`
- L193 _public member_ `int32 Unit;`
- L194 _public member_ `bool UseIESProfile;`
- L195 _public member_ `FString IESPath;`
- L196 _public member_ `EDatasmithLightShape AreaLightShape;`

#### struct `FDatasmithFBXSceneCamera`  
`struct FDatasmithFBXSceneCamera`  
_L199-215_
- L201 _public prototype_ `FDatasmithFBXSceneCamera();`
- L202 _public prototype_ `~FDatasmithFBXSceneCamera();`
- L204 _public member_ `double SensorWidth = 36.0f;`
- L205 _public member_ `double SensorAspectRatio = 1.7777f;`
- L206 _public member_ `double FocalLength = 35.0f;`
- L207 _public member_ `double FocusDistance = 100000.0f;`
- L209 _public member_ `double NearPlane = 0.1f;`
- L210 _public member_ `double FarPlane = 1000.0f;`
- L211 _public member_ `double OrthoZoom = 1.0f;`
- L212 _public member_ `EProjectionType ProjectionType = EProjectionType::Perspective;`
- L214 _public member_ `double Roll = 0.0f;`

#### struct `FDatasmithFBXSceneNode`  
`struct FDatasmithFBXSceneNode : public TSharedFromThis<FDatasmithFBXSceneNode>`  
_L217-335_
- inherits: `TSharedFromThis<FDatasmithFBXSceneNode>`
- L219 _public prototype_ `FDatasmithFBXSceneNode();`
- L220 _public prototype_ `~FDatasmithFBXSceneNode();`
- L223 _public member_ `FString Name;` — Name of the node. Will be unique.
- L227 _public member_ `int32 SplitNodeID;` — All nodes split from the same original node will have the same SplitNodeID. These become actor Tag[1] post-import, so we can match the right node to each variant
- L230 _public member_ `float Visibility = 1.0f;` — Node visibility, as set in fbx.
- L231 _public member_ `bool bVisibilityInheritance;`
- L234 _public member_ `FString OriginalName;` — Original name of the node, may be not unique over scene.
- L237 _public member_ `FTransform LocalTransform;` — Transformation of this node relative to its parent.
- L240 _public member_ `FVector RotationPivot;` — Transform helper objects
- L241 _public member_ `FVector ScalingPivot;`
- L242 _public member_ `FVector RotationOffset;`
- L243 _public member_ `FVector ScalingOffset;`
- L246 _public member_ `bool bShouldKeepThisNode;` — Flag indicating that scene optimizer should preserve this node and limit optimization possibilities for it.
- L249 _public member_ `TWeakPtr<FDatasmithFBXSceneNode> Parent;` — Hierarchy
- L250 _public member_ `TArray< TSharedPtr<FDatasmithFBXSceneNode> > Children;`
- L253 _public member_ `TSharedPtr<FDatasmithFBXSceneMesh> Mesh;` — Mesh data
- L254 _public member_ `TArray< TSharedPtr<FDatasmithFBXSceneMaterial> > Materials;`
- L257 _public member_ `TSharedPtr<FDatasmithFBXSceneLight> Light;` — Light data
- L260 _public member_ `TSharedPtr<FDatasmithFBXSceneCamera> Camera;` — Camera data
- L262 _public member_ `TMap<FString, FString> Metadata;`
- L264 _public prototype_ `FTransform GetTransformRelativeToParent(TSharedPtr<FDatasmithFBXSceneNode>& InParent) const;`
- L266 _public function_ `ENodeType GetNodeType() const`
- L272 _public prototype_ `FTransform GetWorldTransform() const;` — Get node transform in world coordinate system.
- L274 _public function_ `void AddChild(TSharedPtr<FDatasmithFBXSceneNode>& Child)`
- L280 _public function_ `void MoveChildren(TSharedPtr<FDatasmithFBXSceneNode>& NewParent)`
- L291 _public prototype_ `void RemoveNode();` — Remove this node from hierarchy.
- L294 _public prototype_ `int32 GetChildrenCountRecursive() const;` — Get number of children nodes including children of children
- L296 _public prototype_ `void KeepNode();`
- L299 _public prototype_ `void MarkSwitchNode();` — This function makes a switch node persistent for scene merging operation
- L302 _public prototype_ `void MarkToggleNode();` — This function makes a toggle node persistent for scene merging operation
- L305 _public prototype_ `void ResetNodeType();` — Remove special meaning of the node
- L307 _public prototype_ `const FMD5Hash& GetHash();`
- L309 _public function_ `void InvalidateHash()`
- L315 _public function_ `template<typename F> static void Traverse(TSharedPtr<FDatasmithFBXSceneNode> Node, F f)`
- L329 _protected member_ `ENodeType NodeType;`
- L331 _protected member_ `static int32 NodeCounter;`
- L334 _protected member_ `FMD5Hash Hash;` — MD5 of node and its children

#### struct `FDatasmithFBXScene`  
`struct FDatasmithFBXScene`  
_L340-399_
- desc: Describes all info about the scene that can be extracted from the FBX file
- L342 _public prototype_ `FDatasmithFBXScene();`
- L343 _public prototype_ `~FDatasmithFBXScene();`
- L345 _public typedef_ `using MeshUseCountType = TMap< TSharedPtr<FDatasmithFBXSceneMesh>, int32 >;`
- L346 _public typedef_ `using MaterialUseCountType = TMap< TSharedPtr<FDatasmithFBXSceneMaterial>, int32 >;`
- L350 _public prototype_ `TArray<TSharedPtr<FDatasmithFBXSceneNode>> GetAllNodes();` — Flatten all nodes into an array, so that they can be iterated while modifying the hierarchy
- L364 _public prototype_ `FStats GetStats();`
- L366 _public member_ `TSharedPtr<FDatasmithFBXSceneNode> RootNode;`
- L368 _public member_ `TArray<TSharedPtr<FDatasmithFBXSceneMaterial>> Materials;`
- L370 _public member_ `TArray<FDatasmithFBXSceneAnimNode> AnimNodes;`
- L372 _public member_ `TArray<FName> SwitchObjects;`
- L373 _public member_ `TArray<FName> ToggleObjects;`
- L374 _public member_ `TArray<FName> ObjectSetObjects;`
- L375 _public member_ `TArray<FName> AnimatedObjects;`
- L376 _public member_ `TArray<FName> SwitchMaterialObjects;`
- L377 _public member_ `TArray<FName> TransformVariantObjects;`
- L380 _public member_ `float TagTime = FLT_MAX;` — Time instant where the VRED DSID keys are stored
- L383 _public member_ `float BaseTime = 24.0f;` — Native framerate of the animations in fps
- L390 _public member_ `float PlaybackSpeed = 24.0f;` — Playback speed of the animations in fps. In VRED, animations that are natively 1 second long are displayed with total duration 1s * (BaseTime / PlaybackSpeed) The FBX file stores keys with time in seconds, so we have to multiply the key times with (BaseTime / PlaybackSpeed) when passing it to Datasmith to match the final speed in VRED
- L395 _public member_ `double ScaleFactor = 1.0f;` — What we need to multiply translation/scale data with to match the unit scale conversion automatically done when reading the FBX file This is usually 0.1f for DeltaGen and 1.0f for VRED
- L397 _public prototype_ `bool Serialize(FArchive& Ar);`
- L398 _public prototype_ `void RecursiveCollectAllObjects(MeshUseCountType* Meshes, MaterialUseCountType* Materials, int32* NodeCount, const TSharedPtr<FDatasmithFBXSceneNode>& Node) const;`

#### struct `FDatasmithFBXScene::FStats`  
`struct FStats`  
_L352-363_
- L354 _public member_ `int32 MaterialCount;`
- L355 _public member_ `int32 MeshCount;`
- L356 _public member_ `int32 GeometryCount;`
- L357 _public member_ `int32 NodeCount;`
- L359 _public function_ `FStats()`

#### enum `EDatasmithFBXSceneAnimationCurveType`  
`enum class EDatasmithFBXSceneAnimationCurveType : uint8`  
_L401-408_
- L403 _public enumerator_ `Invalid`
- L404 _public enumerator_ `Translation`
- L405 _public enumerator_ `Rotation`
- L406 _public enumerator_ `Scale`
- L407 _public enumerator_ `Visible`

#### enum `EDatasmithFBXSceneAnimationCurveComponent`  
`enum class EDatasmithFBXSceneAnimationCurveComponent : uint8`  
_L410-416_
- L412 _public enumerator_ `X = 0`
- L413 _public enumerator_ `Y = 1`
- L414 _public enumerator_ `Z = 2`
- L415 _public enumerator_ `Num = 3`

#### struct `FDatasmithFBXSceneAnimPoint`  
`struct FDatasmithFBXSceneAnimPoint`  
_L424-432_
- desc: Represents a single key frame of an animation curve. Has interpolation and tangent information. Ideally we would use FRichCurveKey, but it's not a BlueprintType, which we need it to be for serialization
- L426 _public member_ `ERichCurveInterpMode InterpolationMode = ERichCurveInterpMode::RCIM_Linear;`
- L427 _public member_ `ERichCurveTangentMode TangentMode = ERichCurveTangentMode::RCTM_Auto;`
- L428 _public member_ `float Time = 0.0f;`
- L429 _public member_ `float Value = 0.0f;`
- L430 _public member_ `float ArriveTangent = 0.0f;`
- L431 _public member_ `float LeaveTangent = 0.0f;`

#### struct `FDatasmithFBXSceneAnimCurve`  
`struct FDatasmithFBXSceneAnimCurve`  
_L440-459_
- desc: Represents an individual animation curve of a transform property (like translation X). Has multiple points, representing animation key frames. Also has an individual DatasmithID (DSID) that can be used to track the curve through the VRED export process.
- L445 _public member_ `int32 DSID = 0;` — ID of the curve pulled from the FBX. Since VRED doesn't emit any info about the curves in the FBX file, we use this to figure out which block the curve belongs to
- L447 _public member_ `EDatasmithFBXSceneAnimationCurveType Type = EDatasmithFBXSceneAnimationCurveType::Invalid;`
- L448 _public member_ `EDatasmithFBXSceneAnimationCurveComponent Component = EDatasmithFBXSceneAnimationCurveComponent::X;`
- L449 _public member_ `TArray<FDatasmithFBXSceneAnimPoint> Points;`
- L453 _public member_ `float StartTimeSeconds = FLT_MAX;` — Time of the first true animation key/value pair. Discard everything before this
- L455 _public function_ `bool operator<(const FDatasmithFBXSceneAnimCurve& Other) const`

#### struct `FDatasmithFBXSceneAnimBlock`  
`struct FDatasmithFBXSceneAnimBlock`  
_L465-469_
- desc: Represents a set of AnimCurves of an actor. The animation system can play an AnimBlockUsage of this block, once its part of an AnimClip.
- L467 _public member_ `FString Name;`
- L468 _public member_ `TArray<FDatasmithFBXSceneAnimCurve> Curves;`

#### struct `FDatasmithFBXSceneAnimNode`  
`struct FDatasmithFBXSceneAnimNode : public FTableRowBase`  
_L474-478_
- inherits: `FTableRowBase`
- desc: Describes the set of AnimBlocks that an AnimNode contains
- L476 _public member_ `FString Name;`
- L477 _public member_ `TArray<FDatasmithFBXSceneAnimBlock> Blocks;`

#### struct `FDatasmithFBXSceneAnimUsage`  
`struct FDatasmithFBXSceneAnimUsage`  
_L484-491_
- desc: Used by the VRED importer, this describes how an AnimBlock or AnimClip is used within an AnimClip. Analogue to an instance of an AnimBlock or AnimClip.
- L486 _public member_ `FString AnimName;`
- L487 _public member_ `float StartTime = 0.0f;`
- L488 _public member_ `float EndTime = 0.0f;`
- L489 _public member_ `float IsActive = true;`
- L490 _public member_ `bool bIsFlipped = false;`

#### struct `FDatasmithFBXSceneAnimClip`  
`struct FDatasmithFBXSceneAnimClip : public FTableRowBase`  
_L498-505_
- inherits: `FTableRowBase`
- desc: Used by the VRED importer, this describes how multiple AnimBlockUsages are composed to create complex animation sequences involving multiple actors.
- L500 _public member_ `FString Name;`
- L501 _public member_ `bool bIsFlipped;`
- L504 _public member_ `TArray<FDatasmithFBXSceneAnimUsage> AnimUsages;` — Blocks and clips that are played when we play this Playable

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXSceneProcessor.h` (Public)


#### class `FDatasmithFBXSceneProcessor`  
`class FDatasmithFBXSceneProcessor`  
_L7-80_
- L10 _public prototype_ `FDatasmithFBXSceneProcessor(FDatasmithFBXScene* InScene);`
- L13 _public prototype_ `void FindDuplicatedMaterials();` — Find duplicated materials and replace them with a single copy
- L16 _public prototype_ `void FindDuplicatedMeshes();` — Find identical meshes and replace them with a single copy
- L19 _public prototype_ `void RemoveLightMapNodes();` — Cleanup unneeded nodes for the whole scene
- L22 _public prototype_ `void RemoveInvisibleNodes();` — Cleanup nodes not meant to be visible
- L25 _public function_ `void RemoveEmptyNodes()` — Cleanup unneeded nodes for the whole scene
- L31 _public prototype_ `void RemoveEmptyNodesRecursive(TSharedPtr<FDatasmithFBXSceneNode> Node);` — Cleanup unneeded nodes for hierarchy
- L34 _public function_ `void RemoveTempNodes()` — Remove auxilliary geometry generated when exporting from VRED from the whole scene
- L40 _public prototype_ `void RemoveTempNodesRecursive(TSharedPtr<FDatasmithFBXSceneNode> Node);` — Remove auxilliary geometry generated when exporting from VRED from a hierarchy
- L43 _public prototype_ `void FindPersistentNodes();` — Find and mark scene nodes which shouldn't be merged with parent or sibling nodes
- L46 _public prototype_ `void SimplifyNodeHierarchy();` — Collapse node hierarchy .
- L49 _public prototype_ `void FixNodeNames();` — Fix node names to match output from XmlParser(it converts all whitespace sequences in Content to single space).
- L52 _public prototype_ `void FixMeshNames();` — Fix invalid mesh names - those that can't be used for asset names(like 'AUX', 'CON' etc)
- L54 _public prototype_ `void SplitControlNodes();`
- L59 _public function_ `void SplitLightNodes()` — Split our lights into a parent that is a simple actor and a child light actor. This because VRED has the convention that lights shoot toward -Z, while they shoot toward +X in Unreal. Since we also have Transform variants around, we can't just rotate the node and its children once: We need another node
- L65 _public prototype_ `void SplitLightNodesRecursive(TSharedPtr<FDatasmithFBXSceneNode> Node);` — Recursively splits light actors into a parent simple actor, and a child light actor, with the _Light suffix
- L70 _public function_ `void SplitCameraNodes()` — Split camera nodes into a parent that is a simple actor and a child camera actor. This because VRED has the convention that cameras shoot toward -Z, while they shoot toward +X in Unreal. Since we also can animate those camera nodes (needing a BP_VREDAnimNode), we need to split these camera nodes
- L76 _public prototype_ `void SplitCameraNodesRecursive(TSharedPtr<FDatasmithFBXSceneNode> Node);` — Recursively splits cameras into a parent simple actor, and a child camera actor, with the _Camera suffix
- L79 _protected member_ `FDatasmithFBXScene* Scene;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXTranslatorModule.h` (Public)


#### class `IDatasmithFBXTranslatorModule`  
`class IDatasmithFBXTranslatorModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public function_ `static inline IDatasmithFBXTranslatorModule& Get()`
- L18 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define FBXTRANSLATOR_MODULE_NAME TEXT("DatasmithFBXTranslator")`
