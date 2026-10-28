# Plugins / DatasmithC4DTranslator

- module root: `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator`
- headers: 8; symbols: 151
- symbol kinds: class=4, delegate=2, enum=4, enumerator=16, function=5, macro=12, member=32, namespace=1, prototype=74, struct=1
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, DatasmithCore, DatasmithExporter, EditorStyle, Engine, Imath, MelangeSDK, MeshDescription, Slate, SlateCore, StaticMeshDescription
- PublicDependencyModuleNames: DatasmithContent, DatasmithTranslator

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DExtraMelangeDefinitions.h` (Private)


#### enum `cineware::(anonymous)`  
``  
_L21-41_

#### enum `cineware::(anonymous)`  
``  
_L44-46_

#### enum `cineware::(anonymous)`  
``  
_L49-51_

#### enum `cineware::(anonymous)`  
``  
_L54-56_

#### Free symbols / members of external scopes

- L9 _macro_ `#define Ocloner 1018544`
- L10 _macro_ `#define Ofracture 1018791`
- L12 _macro_ `#define REFLECTION_LAYER_MAIN_OPACITY REFLECTION_LAYER_TRANS_BRIGHTNESS`
- L13 _macro_ `#define REFLECTION_LAYER_NAME 0x0015`
- L15 _namespace_ `namespace cineware`
- L23 _enumerator_ `CRANECAMERA_NAME = 900` (scope `cineware::__anonc6801d380103`) — CRANECAMERA_UNKNOWN_LINK = 898,
- L29 _enumerator_ `CRANECAMERA_BASE_HEIGHT = 100205` (scope `cineware::__anonc6801d380103`) — CRANECAMERA_UNKNOWN_LONG = 100101, // "Link" CRANECAMERA_UNKNOWN_VEC = 100102, CRANECAMERA_UNKNOWN_VEC = 100103, CRANECAMERA_UNKNOWN_REAL = 100203, CRANECAMERA_UNKNOWN_LONG = 100204,
- L30 _enumerator_ `CRANECAMERA_BASE_HEADING = 100206` (scope `cineware::__anonc6801d380103`) — double, radians
- L31 _enumerator_ `CRANECAMERA_ARM_LENGTH = 100211` (scope `cineware::__anonc6801d380103`) — double, cm
- L32 _enumerator_ `CRANECAMERA_ARM_PITCH = 100212` (scope `cineware::__anonc6801d380103`) — double, radians
- L33 _enumerator_ `CRANECAMERA_HEAD_HEIGHT = 100221` (scope `cineware::__anonc6801d380103`) — double, cm
- L34 _enumerator_ `CRANECAMERA_HEAD_HEADING = 100222` (scope `cineware::__anonc6801d380103`) — double, radians
- L35 _enumerator_ `CRANECAMERA_HEAD_WIDTH = 100223` (scope `cineware::__anonc6801d380103`) — double, cm
- L36 _enumerator_ `CRANECAMERA_CAM_PITCH = 100231` (scope `cineware::__anonc6801d380103`) — double, radians
- L37 _enumerator_ `CRANECAMERA_CAM_BANKING = 100232` (scope `cineware::__anonc6801d380103`) — double, radians
- L38 _enumerator_ `CRANECAMERA_CAM_OFFSET = 100233` (scope `cineware::__anonc6801d380103`) — double, cm
- L39 _enumerator_ `CRANECAMERA_COMPENSATE_PITCH = 100234` (scope `cineware::__anonc6801d380103`) — bool
- L40 _enumerator_ `CRANECAMERA_COMPENSATE_HEADING = 100235` (scope `cineware::__anonc6801d380103`) — bool
- L45 _enumerator_ `POLYGONSELECTIONTAG_NAME = 900` (scope `cineware::__anonc6801d380203`)
- L50 _enumerator_ `ID_BASEOBJECT_REL_SIZE = 1100` (scope `cineware::__anonc6801d380303`)
- L55 _enumerator_ `MGCLONER_VOLUMEINSTANCES_MODE = 1025` (scope `cineware::__anonc6801d380403`)

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DImportOptions.h` (Private)


#### class `UDatasmithC4DImportOptions`  
`class UDatasmithC4DImportOptions : public UDatasmithOptionsBase`  
_L24-63_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, HideCategories = (DebugProperty))`
- inherits: `UDatasmithOptionsBase`
- L33 _public member_ `bool bImportEmptyMesh;` — `UPROPERTY(config, EditAnywhere, Category = DebugProperty, meta = (DisplayName = "Import Mesh With No Vertex"))` — Import Mesh With No Vertex, false by default
- L39 _public member_ `bool bOptimizeEmptySingleChildActors;` — `UPROPERTY(config, EditAnywhere, Category = DebugProperty, meta = (DisplayName = "Clean the Scene of Empty Actors With Only One Child"))` — Remove empty actors that have only one child, false by default
- L46 _public member_ `bool bAlwaysGenerateNormals;` — `UPROPERTY(config, EditAnywhere, Category = DebugProperty, meta = (DisplayName = "Generate the Normals"))` — Ignore the normals provided by Melange and let Datasmith generate them The "if (RawNormal.SizeSquared() < SMALL_NUMBER)" check in see FDatasmithMeshUtils::ToMeshDescription is preventing some meshes to load
- L54 _public member_ `float ScaleVertices;` — `UPROPERTY(config, EditAnywhere, Category = DebugProperty, meta = (DisplayName = "Scale the Entire Scene"))` — Scale all position and vertices by this value. It is needed when scene has too precise meshes because the conversion from double (C4D) to float (UnrealEditor) can "degenerate" the faces
- L61 _public member_ `bool bExportToUDatasmith;` — `UPROPERTY(config, EditAnywhere, Category = DebugProperty, meta = (DisplayName = "Export to .udatasmith"))` — Export the imported scene as a .datasmith file, next to the .c4d file.

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DImporter.h` (Private)


#### struct `FDatasmithC4DImportOptions`  
`struct FDatasmithC4DImportOptions`  
_L47-54_
- L49 _public member_ `bool bImportEmptyMesh = false;`
- L50 _public member_ `bool bOptimizeEmptySingleChildActors = false;`
- L51 _public member_ `bool bAlwaysGenerateNormals = false;`
- L52 _public member_ `float ScaleVertices = 1.0;`
- L53 _public member_ `bool bExportToUDatasmith = false;`

#### class `FDatasmithC4DImporter`  
`class FDatasmithC4DImporter`  
_L56-230_
- L59 _public prototype_ `FDatasmithC4DImporter(TSharedRef<IDatasmithScene>& OutScene, FDatasmithC4DImportOptions& InOptions);`
- L60 _public prototype_ `~FDatasmithC4DImporter();`
- L63 _public prototype_ `void SetImportOptions(FDatasmithC4DImportOptions& InOptions);` — Updates the used import options to InOptions
- L66 _public prototype_ `bool OpenFile(const FString& InFilename);` — Open and load a .4cd file into C4dDocument
- L69 _public prototype_ `bool ProcessScene();` — Parse the scene contained in the previously opened file and process its content according to parameters from incoming context
- L72 _public prototype_ `void UnloadScene();` — Unload cineware resources after importing
- L74 _public prototype_ `void GetGeometriesForMeshElementAndRelease(const TSharedRef<IDatasmithMeshElement> MeshElement, TArray<FMeshDescription>& OutMeshDescriptions);`
- L75 _public prototype_ `TSharedPtr<IDatasmithLevelSequenceElement> GetLevelSequence();`
- L78 _public prototype_ `cineware::BaseObject* GetBestMelangeCache(cineware::BaseObject* Object);` — Finds the most derived cache for a cineware object. That will be e.g. a polygon cache or a deformed polygon cache, if it has one
- L81 _public prototype_ `TOptional<FString> MelangeObjectID(cineware::BaseObject* Object);` — Generates a unique identifier string for a cineware object based on the object's name and its position in the hierarchy
- L84 _public prototype_ `cineware::BaseObject* FindMelangeObject(const FString& SearchObjectID, cineware::BaseObject* Object);` — Searches the cineware object hierarchy for a cineware::BaseObject that has a MelangeObjectID equal to SearchObjectID
- L87 _public prototype_ `cineware::BaseObject* GoToMelangeHierarchyPosition(cineware::BaseObject* Object, const FString& HierarchyPosition);` — Fetch the object corresponding to the position encoded in HierarchyPosition, starting from Object
- L96 _public prototype_ `void MarkActorsAsParticles(cineware::BaseObject* EmitterObject, cineware::BaseObject* EmittersCache);` — Marks actors children of EmitterObject as ParticleActors, so that they can receive an artificial visibility animation track to emulate the look of the particle spawning and despawning
- L104 _public prototype_ `TSharedPtr<IDatasmithActorElement> ImportNullActor(cineware::BaseObject* Object, const FString& DatasmithName, const FString& DatasmithLabel);` — Import cineware objects into Datasmith elements. Assets like meshes, materials and textures are added to the Datasmith scene directly, while actors are merely returned and must be added as children to scene actors or added to the scene manually. Returns a null TSharedPtr if an error occurred during the import process.
- L105 _public prototype_ `TSharedPtr<IDatasmithLightActorElement> ImportLight(cineware::BaseObject* LightObject, const FString& DatasmithName, const FString& DatasmithLabel);`
- L106 _public prototype_ `TSharedPtr<IDatasmithCameraActorElement> ImportCamera(cineware::BaseObject* CameraObject, const FString& DatasmithName, const FString& DatasmithLabel);`
- L107 _public prototype_ `TSharedPtr<IDatasmithMeshActorElement> ImportPolygon(cineware::PolygonObject* PolyObject, const FString& DatasmithName, const FString& DatasmithLabel, const TArray<cineware::TextureTag*>& TextureTags);`
- L108 _public prototype_ `TSharedPtr<IDatasmithMaterialInstanceElement> ImportMaterial(cineware::Material* InC4DMaterialPtr);`
- L109 _public prototype_ `TSharedPtr<IDatasmithMaterialInstanceElement> ImportSimpleColorMaterial(cineware::BaseObject* Object, int32 UseColor);`
- L110 _public prototype_ `TSharedPtr<IDatasmithTextureElement> ImportTexture(const FString& TexturePath, EDatasmithTextureMode TextureMode);`
- L111 _public prototype_ `TSharedPtr<IDatasmithMeshElement> ImportMesh(cineware::PolygonObject* PolyObject, const FString& DatasmithMeshName, const FString& DatasmithLabel);`
- L114 _public prototype_ `void ImportSpline(cineware::SplineObject* ActorObject);` — Parses the spline and its cache into SplineCurves so that it can be used as paths for animation later
- L117 _public prototype_ `bool ImportMaterialHierarchy(cineware::BaseMaterial* InC4DMaterialPtr);` — Traverse the cineware material hierarchy contained in the c4d file and import each into IDatasmithMaterialInstanceElements
- L120 _public prototype_ `void ImportAnimations(TSharedPtr<IDatasmithActorElement> ActorElement);` — Uses ActorElementToC4DObject to find the corresponding cineware object for ActorElement and adds all of its animations to LevelSequence
- L123 _public prototype_ `void ImportActorHierarchyAnimations(TSharedPtr<IDatasmithActorElement> ActorElement);` — Traverse the Datasmith scene's IDatasmithActorElement hierarchy and import all animations for the corresponding cineware actors
- L126 _public prototype_ `FString GetBaseShaderTextureFilePath(cineware::BaseList2D* BaseShader);` — Searches for the first valid texture used by BaseShader
- L133 _public prototype_ `FString CustomizeMaterial(const FString& InMaterialID, const FString& InMeshID, cineware::TextureTag* InTextureTag);` — Generates a new copy of the IDatasmithMaterialInstanceElement with name InMaterialID and alter its properties to match values retrieved from InTextureTag, and adds the new material to the Datasmith scene. This is used because texture tags are closer to material instances, and may have different "overrides" for each property
- L138 _public prototype_ `TMap<int32, FString> GetCustomizedMaterialAssignment(const FString& DatasmithMeshName, const TArray<cineware::TextureTag*>& TextureTags);` — Creates customized materials if necessary, and returns a map from material slot indices to material names
- L141 _public prototype_ `TSharedPtr<IDatasmithActorElement> ImportObjectAndChildren(cineware::BaseObject* ActorObject, cineware::BaseObject* DataObject, TSharedPtr<IDatasmithActorElement> ParentActor, const cineware::Matrix& WorldTransformMatrix, const FString& InstancePath, const FString& DatasmithLabel, const TArray<cineware::TextureTag*>& TextureTags);` — Imports a cineware actor, which might involve parsing another small hierarchy of subnodes and deformers
- L144 _public prototype_ `void ImportHierarchy(cineware::BaseObject* ActorObject, cineware::BaseObject* DataObject, TSharedPtr<IDatasmithActorElement> ParentActor, const cineware::Matrix& WorldTransformMatrix, const FString& InstancePath, const TArray<cineware::TextureTag*>& TextureTags);` — Traverse the cineware actor hierarchy importing all nodes
- L150 _public prototype_ `bool AddChildActor(cineware::BaseObject* Object, TSharedPtr<IDatasmithActorElement> ParentActor, cineware::Matrix WorldTransformMatrix, const TSharedPtr<IDatasmithActorElement>& Actor);` — Adds Actor as a child of ParentActor using the corresponding WorldTransformMatrix. Object is the corresponding cineware Object to Actor. This will also do the necessary coordinate system conversions between cineware and Unreal.
- L153 _public function_ `DECLARE_EVENT_TwoParams(FDatasmithC4DTranslator, FPreTranslateEvent, cineware::BaseDocument*, const FString&) static FPreTranslateEvent& OnPreTranslate()` — Event for when a C4D document is about to be opened for translation
- L156 _public member_ `cineware::BaseDocument* C4dDocument = nullptr;`
- L157 _public member_ `FString C4dDocumentFilename;`
- L162 _private prototype_ `FVector GetDocumentDefaultColor();`
- L165 _private prototype_ `TArray<cineware::TextureTag*> GetActiveTextureTags(const cineware::BaseObject* Object, const TArray<cineware::TextureTag*>& OrderedTextureTags);` — Returns the TextureTags that should affect this object. May check parent objects, so relies on CachesOriginalObject
- L171 _private prototype_ `void RegisterInstancedHierarchy(cineware::BaseObject* InstanceRoot, cineware::BaseObject* OriginalRoot);` — Traverses the original and instanced hierarchy simultaneously and register links between instanced objects and their originals
- L178 _private prototype_ `void RedirectInstancedAnimations();` — Replaces the values of ActorElementToAnimationSources to point to the original objects, in case they are instanced objects. This is required because we need to parse the instanced hierarchy to fetch the correct polygons and materials, but Cinema 4D only places animations on the original hierarchy.
- L181 _private member_ `TMap<IDatasmithMeshElement*, FMeshDescription> MeshElementToMeshDescription;` — Storage of FMeshDescriptions until they're retrieved by GetGeometriesForMeshElement
- L184 _private member_ `TMap<cineware::SplineObject*, TArray<FRichCurve>> SplineCurves;` — Storage of imported spline data to be used exclusively for importing animations that follow spline paths
- L187 _private member_ `TMap<FString, TSharedPtr<IDatasmithMaterialInstanceElement>> MaterialNameToMaterialElement;` — Storage of created materials used by CustomizeMaterial to create new "material instances"
- L190 _private member_ `TMap<FString, TSharedRef<IDatasmithMeshElement>> PolygonHashToMeshElement;` — Cache meshes by hash to promote reusing StaticMeshes
- L193 _private member_ `TMap<FString, TSharedPtr<IDatasmithTextureElement>> ImportedTextures;` — Cache to prevent us from importing the same texture in the same mode more than once (mode is encoded in the FString as well)
- L196 _private member_ `TMap<IDatasmithActorElement*, cineware::BaseObject*> ActorElementToAnimationSources;` — Storage of all parsed actors from the cineware document, used so we can import all animations afterwards
- L199 _private member_ `TMap<cineware::BaseObject*, cineware::BaseObject*> InstancedSubObjectsToOriginals;` — Maps an instance to the corresponding original node, used so that we can redirect animations to the original nodes
- L202 _private member_ `TMap<cineware::BaseObject*, cineware::BaseObject*> CachesOriginalObject;` — Keeps track of the owners of every cineware cache object so we can climb the hierarchy upwards
- L205 _private member_ `TMap<cineware::BaseObject*, TSharedRef<FCraneCameraAttributes>> CraneCameraToAttributes;` — Stores all FCraneCameraAttributes for each camera
- L208 _private member_ `TSet<cineware::BaseObject*> ParticleActors;` — Melange actors that are actually baked 'mesh particles' and need to receive an extra visibility track in ImportAnimations
- L211 _private member_ `TSet<FString> NamesOfAllActors;` — Caches to make sure we don't have any actor name collisions
- L214 _private member_ `TSet<FString> NamesOfActorsToKeep;` — Names of IDatasmithActorElements that shouldn't be removed when optimizing the scene
- L216 _private member_ `FDatasmithC4DImportOptions Options;`
- L219 _private member_ `TSharedPtr<IDatasmithLevelSequenceElement> LevelSequence;` — Where all actor animations are imported into when parsing the scene
- L222 _private member_ `TSharedRef<IDatasmithScene> DatasmithScene;` — Output Datasmith scene
- L225 _private member_ `TSharedPtr<FDatasmithSceneExporter> SceneExporterRef;` — Can be used to also export the imported scene in a .udatasmith format during import
- L227 _private member_ `TOptional<FVector> DefaultDocumentColorLinear;`
- L229 _private member_ `static FPreTranslateEvent PreTranslateEvent;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_DEFINE_LEGACY_MATH_CONSTANT_MACRO_NAMES 0`
- L45 _delegate_ `DECLARE_STATS_GROUP(TEXT("C4DImporter"), STATGROUP_C4DImporter, STATCAT`
- L153 _delegate_ `DECLARE_EVENT_TwoParams(FDatasmithC4DTranslator, FPreTranslateEvent, cineware::BaseDocument*, const FString&) static FPreTranslateEvent& OnPreTranslate() { return PreTranslateEvent; } cineware::BaseDocument* C4dDocument = nullptr;` — Event for when a C4D document is about to be opened for translation

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DMelangeSDKEnterGuard.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define MAXON_TARGET_RELEASE 1` — Enter Datasmith platform include gard.
- L5 _macro_ `#define MAXON_TARGET_64BIT 1`
- L25 _macro_ `#define MAXON_TARGET_WINDOWS 1`
- L35 _macro_ `#define GCC34T this->`
- L37 _macro_ `#define __LP64__ 0`
- L38 _macro_ `#define __APPLE__ 0`

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DMelangeSDKLeaveGuard.h` (Private)
_(no declarations extracted)_

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DTranslator.h` (Private)


#### class `FDatasmithC4DTranslator`  
`class FDatasmithC4DTranslator : public IDatasmithTranslator`  
_L12-43_
- inherits: `IDatasmithTranslator`
- L15 _public function_ `virtual FName GetFName() const override`
- L18 _public function_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override`
- L21 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L22 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L23 _public prototype_ `virtual void UnloadScene() override;`
- L25 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L26 _public prototype_ `virtual bool LoadLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement> LevelSequenceElement, FDatasmithLevelSequencePayload& OutLevelSequencePayload) override;`
- L28 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L29 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L36 _private prototype_ `TObjectPtr<UDatasmithC4DImportOptions>& GetOrCreateC4DImportOptions();`
- L40 _private member_ `TObjectPtr<UDatasmithC4DImportOptions> ImportOptions;` — -1: try load dynamic initially; 0: dynamic cannot be loaded; 1: dynamic successful loaded
- L41 _private member_ `TSharedPtr<FDatasmithC4DImporter> Importer;`

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _prototype_ `int32 MelangeGetInt32(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_LONG parameter of a cineware object as a cineware::Int32, and static_casts it to an int32. Will return 0 if the parameter is invalid
- L23 _prototype_ `int64 MelangeGetInt64(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_LLONG parameter of a cineware object and returns it as an int64. Will return 0 if the parameter is invalid
- L29 _prototype_ `bool MelangeGetBool(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_LONG parameter of a cineware object as a cineware::Bool, and returns it as a bool. Will return false if the parameter is invalid
- L35 _prototype_ `double MelangeGetDouble(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_REAL parameter of a cineware object and returns it as a double. Will return 0.0 if the parameter is invalid
- L42 _prototype_ `FVector MelangeGetVector(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_VECTOR parameter of a cineware object and returns it as an FVector. No coordinate or color conversions are applied. Will return FVector() if the parameter is invalid
- L48 _prototype_ `FMatrix MelangeGetMatrix(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_MATRIX parameter of a cineware object and returns it as an FMatrix. Will return an identity matrix if the parameter is invalid
- L54 _prototype_ `TArray<uint8> MelangeGetByteArray(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_BYTEARRAY parameter of a cineware object and returns it as an array of bytes. Will return TArray<uint8>() if the parameter is invalid
- L60 _prototype_ `FString MelangeGetString(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_STRING or DA_FILENAME parameter of a cineware object and returns it as a string. Will return FString() if the parameter is invalid
- L66 _prototype_ `cineware::BaseList2D* MelangeGetLink(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves a the object pointed to by an DA_ALIASLINK parameter of a cineware object and returns it. Will return nullptr if the parameter is invalid
- L72 _prototype_ `float MelangeGetFloat(cineware::BaseList2D* Object, cineware::Int32 Parameter);` — Retrieves the value of a DA_REAL (double) parameter from a cineware object and static_casts it to float. Will return 0.0f if the parameter is invalid
- L77 _prototype_ `FVector ConvertMelangePosition(const cineware::Vector32& MelangePosition, float WorldUnitScale = 1.0f);` — Converts a vector representing a position from the cineware coordinate system to the UnrealEditor coordinate system
- L78 _prototype_ `FVector ConvertMelangePosition(const cineware::Vector64& MelangePosition, float WorldUnitScale = 1.0f);`
- L79 _prototype_ `FVector ConvertMelangePosition(const FVector& MelangePosition, float WorldUnitScale = 1.0f);`
- L84 _prototype_ `FVector ConvertMelangeDirection(const cineware::Vector32& MelangePosition);` — Converts a vector representing a direction from the cineware coordinate system to the UnrealEditor coordinate system
- L85 _prototype_ `FVector ConvertMelangeDirection(const cineware::Vector64& MelangePosition);`
- L86 _prototype_ `FVector ConvertMelangeDirection(const FVector& MelangePosition);`
- L91 _prototype_ `FVector MelangeVectorToFVector(const cineware::Vector32& MelangeVector);` — Converts a cineware::Vector into an FVector
- L92 _prototype_ `FVector MelangeVectorToFVector(const cineware::Vector64& MelangeVector);`
- L97 _prototype_ `FVector4 MelangeVector4ToFVector4(const cineware::Vector4d32& MelangeVector);` — Converts a cineware::Vector4d32 into an FVector4
- L102 _prototype_ `FVector4 MelangeVector4ToFVector4(const cineware::Vector4d64& MelangeVector);` — Converts a cineware::Vector4d64 into an FVector4
- L107 _prototype_ `FMatrix MelangeMatrixToFMatrix(const cineware::Matrix& Matrix);` — Converts a cineware::Matrix into an FMatrix
- L112 _prototype_ `FString MelangeStringToFString(const cineware::String& MelangeString);` — Converts a cineware::String into an FString
- L117 _prototype_ `FString MD5FromString(const FString& String);` — Uses the bytes of 'String' to generate an MD5 hash, and returns the bytes of the hash back as an FString
- L122 _prototype_ `FString MelangeFilenameToPath(const cineware::Filename& Filename);` — Converts a cineware::Filename to an FString path
- L134 _prototype_ `FString SearchForFile(FString Filename, const FString& C4dDocumentFilename);` — Searches for a file in places where cineware is likely to put them. Will try things like making the filename relative to the C4dDocumentFilename's folder, searching the 'tex' folder, and etc. Use this to search for texture and IES files as the path contained in cineware is likely to be pointing somewhere else if the user didn't export the scene just right. @param Filename				The path to the file we're trying to find. Can be relative or absolute @param C4dDocumentFilename	Path to the main .c4d file being imported e.g. "C:\MyFolder\Scene.c4d" @return						The full, absolute found filepath if it exists, or an empty string
- L139 _prototype_ `FString MelangeObjectName(cineware::BaseList2D* Object);` — Gets the name of a cineware object as an FString, or returns 'Invalid object' if the argument is nullptr
- L145 _prototype_ `FString MelangeObjectTypeName(cineware::BaseList2D* Object);` — Gets the type of a cineware object as an FString (e.g. Ocloner, Onull, Opolygon), or 'Invalid object' if the argument is nullptr
- L151 _prototype_ `FString GeDataToString(const cineware::GeData& Data);` — Gets the data stored within a cineware::GeData object according to its .GetType() and returns that as a string. Will try to convert to Unreal types first (like FVector or FMatrix) and convert those to string instead
- L157 _prototype_ `FString GeTypeToString(int32 GeType);` — Converts the type returned by .GetType() of a cineware::GeData instance from an cineware::Int32 into a human-readable string
- L163 _prototype_ `FString MelangeParameterValueToString(cineware::BaseList2D* Object, cineware::Int32 ParameterID);` — Gets the corresponding parameter from Object, and returns the value stored in the resulting GeData as a string. Will return an empty string if Object is nullptr, but it can return NIL if the parameter is not found
- L168 _prototype_ `TOptional<FString> GetMelangeBaseList2dID(cineware::BaseList2D* BaseList);` — Returns the full cineware ID for the BaseList2D argument as an FString, which will include AppId

### `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Public/DatasmithC4DTranslatorModule.h` (Public)


#### class `IDatasmithC4DTranslatorModule`  
`class IDatasmithC4DTranslatorModule : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L14 _public function_ `static inline IDatasmithC4DTranslatorModule& Get()`
- L19 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define C4DTRANSLATOR_MODULE_NAME TEXT("DatasmithC4DTranslator")`
