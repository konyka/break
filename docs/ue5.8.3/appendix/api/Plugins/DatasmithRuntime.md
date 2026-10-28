# Plugins / DatasmithRuntime

- module root: `Plugins/Experimental/Enterprise/DatasmithRuntime/Source`
- headers: 10; symbols: 429
- symbol kinds: class=15, delegate=5, enum=8, enumerator=60, externvar=6, function=69, macro=4, member=107, namespace=11, prototype=128, struct=9, typedef=7
- PrivateDependencyModuleNames: CinematicCamera, Core, CoreUObject, DesktopPlatform, DeveloperToolSettings, DirectLink, Engine, FreeImage, IESFile, Landscape, LevelSequence, MeshDescription, MeshUtilitiesCommon, MessageLog, PhysicsCore, RHI, RawMesh, RenderCore, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: DatasmithContent, DatasmithCore, DatasmithNativeTranslator, DatasmithTranslator

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/DatasmithRuntimeAuxiliaryData.h` (Private)


#### class `UDatasmithRuntimeTHelper`  
`class UDatasmithRuntimeTHelper : public UObject, public IInterface_AssetUserData`  
_L21-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData`
- desc: Utility class to hold on FAssetData entities while their associated texture is being built
- L27 _public function_ `virtual void AddAssetUserData( UAssetUserData* InUserData ) override`
- L41 _public function_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override`
- L54 _public function_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override`
- L68 _public function_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override`
- L77 _private member_ `TArray< TObjectPtr<UAssetUserData> > AssetUserData;` — `UPROPERTY()` — Array of user data stored with the asset

#### class `UDatasmithRuntimeAuxiliaryData`  
`class UDatasmithRuntimeAuxiliaryData : public UAssetUserData`  
_L82-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Asset user data that can be used with DatasmithRuntime on Actors and other objects
- L87 _public function_ `UDatasmithRuntimeAuxiliaryData() : Auxiliary(nullptr) , bIsCompleted(false)`
- L94 _public member_ `TObjectPtr<UObject> Auxiliary;` — `UPROPERTY(VisibleAnywhere, Category = "DatasmithRuntime Internal")`
- L96 _public member_ `TSet<uint64> Referencers;`
- L98 _public member_ `std::atomic_bool bIsCompleted;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DatasmithRuntime`

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/DatasmithRuntimeUtils.h` (Private)


#### class `URuntimeMesh`  
`class URuntimeMesh : public UStaticMesh`  
_L42-64_
- reflection: `UCLASS()`
- inherits: `UStaticMesh`
- desc: Class deriving from UStaticMesh to allow the cooking of collision meshes at runtime To do so, bAllowCPUAccess must be true AND  the metod GetWorld() must return a valid world
- L47 _public function_ `URuntimeMesh() : World(nullptr)`
- L56 _public function_ `virtual UWorld* GetWorld() const override` — UObject overrides Overridden to allow cooking of collision meshes, simple and complex, from static mesh at runtime
- L60 _public function_ `void SetWorld(UWorld* InWorld)` — Use valid world to allow cooking of collision meshes, simple and complex, from static mesh at runtime
- L63 _private member_ `UWorld* World;`

#### enum `DatasmithRuntime::EDSResizeTextureMode`  
`enum class EDSResizeTextureMode`  
_L68-74_
- L70 _public enumerator_ `NoResize`
- L71 _public enumerator_ `NearestPowerOfTwo`
- L72 _public enumerator_ `PreviousPowerOfTwo`
- L73 _public enumerator_ `NextPowerOfTwo`

#### class `DatasmithRuntime::FAssetRegistry`  
`class FAssetRegistry`  
_L104-131_
- L107 _public prototype_ `static void RegisterMapping(uint32 SceneKey, TMap<FSceneGraphId, FAssetData>* AssetsMapping);`
- L109 _public prototype_ `static void UnregisterMapping(uint32 SceneKey);`
- L111 _public prototype_ `static void RegisterAssetData(UObject* Asset, uint32 SceneKey, FAssetData& AssetData);`
- L113 _public prototype_ `static int32 UnregisterAssetData(UObject* Asset, uint32 SceneKey, FSceneGraphId AssetId);`
- L115 _public prototype_ `static void UnregisteredAssetsData(UObject* Asset, uint32 SceneKey, TFunction<void(FAssetData& AssetData)> UpdateFunc);`
- L117 _public prototype_ `static void SetObjectCompletion(UObject* Asset, bool bIsCompleted);`
- L119 _public prototype_ `static bool IsObjectCompleted(UObject* Asset);`
- L121 _public prototype_ `static UObject* FindObjectFromHash(uint32 ElementHash);`
- L123 _public prototype_ `static int32 GetAssetReferenceCount(UObject* Asset);`
- L126 _public prototype_ `static bool CleanUp();` — @return true if some assets have been marked for deletion
- L129 _private member_ `static TMap<uint32, TStrongObjectPtr<UObject>> RegistrationMap;`
- L130 _private member_ `static TMap<uint32, TMap<FSceneGraphId,FAssetData>*> SceneMappings;`

#### Free symbols / members of external scopes

- L66 _namespace_ `namespace DatasmithRuntime`
- L76 _function_ `FORCEINLINE uint32 GetTypeHash(const FMD5Hash& Hash, EDataType Type = EDataType::None)` (scope `DatasmithRuntime`)
- L81 _prototype_ `extern void CalculateMeshesLightmapWeights(const TArray< FSceneGraphId >& MeshElementArray, const TMap< FSceneGraphId, TSharedPtr< IDatasmithElement > >& Elements, TMap< FSceneGraphId, float >& LightmapWeights);` (scope `DatasmithRuntime`)
- L84 _prototype_ `extern int32 GetNextOpenUVChannel(FMeshDescription& MeshDescription);` (scope `DatasmithRuntime`) — Borrowed from UVGenerationUtils::GetNextOpenUVChannel(UStaticMesh* StaticMesh, int32 LODIndex)
- L87 _prototype_ `extern int32 GenerateLightmapUVResolution(FMeshDescription& Mesh, int32 SrcLightmapIndex, int32 MinLightmapResolution);` (scope `DatasmithRuntime`) — Borrowed from  UVGenerationUtils::SetupGeneratedLightmapUVResolution(UStaticMesh* StaticMesh, int32 LODIndex)
- L90 _prototype_ `extern void ProcessCollision(UStaticMesh* StaticMesh, FDatasmithMeshElementPayload& Payload);` (scope `DatasmithRuntime`) — Borrowed from FDatasmithStaticMeshImporter::ProcessCollision(UStaticMesh* StaticMesh, const TArray< FVector >& VertexPositions)
- L92 _prototype_ `extern void BuildCollision(UBodySetup* Body, ECollisionTraceFlag CollisionFlag, const FStaticMeshLODResources& Resources);` (scope `DatasmithRuntime`)
- L95 _prototype_ `extern bool ShouldRecomputeNormals(const FMeshDescription& MeshDescription, int32 BuildRequirements);` (scope `DatasmithRuntime`)
- L97 _prototype_ `extern bool ShouldRecomputeTangents(const FMeshDescription& MeshDescription, int32 BuildRequirements);` (scope `DatasmithRuntime`)
- L99 _prototype_ `extern void ImageReaderInitialize();` (scope `DatasmithRuntime`)
- L101 _prototype_ `extern bool GetTextureDataFromFile(const TCHAR* Filename, EDSResizeTextureMode Mode, uint32 MaxSize, bool bGenerateNormalMap, FTextureData& TextureData);` (scope `DatasmithRuntime`)
- L102 _prototype_ `extern bool GetTextureDataFromBuffer(TArray<uint8>& Bytes, EDatasmithTextureFormat Format, EDSResizeTextureMode Mode, uint32 MaxSize, bool bGenerateNormalMap, FTextureData& TextureData);` (scope `DatasmithRuntime`)
- L133 _externvar_ `extern const FName RuntimeTag;` (scope `DatasmithRuntime`)
- L135 _prototype_ `extern void RenameObject(UObject* Object, const TCHAR* DesiredName, UObject* NewOwner = nullptr);` (scope `DatasmithRuntime`)
- L137 _prototype_ `extern USceneComponent* CreateComponent(FActorData& ActorData, UClass* Class, AActor* Owner);` (scope `DatasmithRuntime`)
- L140 _function_ `template<typename T> T* CreateComponent(FActorData& ActorData, AActor* Owner)` (scope `DatasmithRuntime`)
- L146 _function_ `template<typename T> T* CreateActor(UWorld* World)` (scope `DatasmithRuntime`)

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/DirectLinkUtils.h` (Private)


#### class `DatasmithRuntime::FDestinationProxy`  
`class FDestinationProxy : public DirectLink::IConnectionRequestHandler, public TSharedFromThis<FDestinationProxy>`  
_L25-122_
- inherits: `DirectLink::IConnectionRequestHandler,TSharedFromThis<FDestinationProxy>`
- desc: Helper class to manage a DirectLink destination and its connection Used by the ADatasmithRuntimeActor
- L28 _public prototype_ `FDestinationProxy(FDatasmithSceneReceiver::ISceneChangeListener* InChangeListener);`
- L29 _public prototype_ `~FDestinationProxy();`
- L32 _public function_ `virtual bool CanOpenNewConnection(const FSourceInformation& ) override`
- L37 _public function_ `virtual TSharedPtr<DirectLink::ISceneReceiver> GetSceneReceiver(const FSourceInformation& ) override`
- L44 _public prototype_ `bool RegisterDestination(const TCHAR* StreamName);` — Register as a scene provider to the associated end point
- L47 _public prototype_ `void UnregisterDestination();` — Unregister as a scene provider to the associated end point
- L49 _public function_ `bool CanConnect()`
- L51 _public function_ `bool IsConnected()`
- L57 _public prototype_ `bool OpenConnection(uint32 SourceIdentifier);` — Open a connection with the source handle associated to the incoming identifier @note the identifier is used by the Game UI
- L60 _public prototype_ `bool OpenConnection(const DirectLink::FSourceHandle& SourceHandle);` — Open a connection with the given source handle
- L63 _public prototype_ `void CloseConnection();` — Close the existing connection
- L66 _public prototype_ `FString GetSourceName();` — Returns the name of the connected source. "None" if there is no connection
- L72 _public prototype_ `static void InitializeEndpointProxy();` — Create the unique end point proxy used by all ADatasmithRuntimeActors @note: This is called when the DatasmithRuntime module is loaded
- L78 _public prototype_ `static void ShutdownEndpointProxy();` — Delete the end point proxy @note: This is called when the DatasmithRuntime module is unloaded
- L81 _public function_ `static FDirectLinkEndpointProxy& GetEndpointProxy()` — Returns the unique end point proxy. This is used by the Game's UI
- L86 _public prototype_ `static const TArray<FDatasmithRuntimeSourceInfo>& GetListOfSources();`
- L89 _public function_ `void ResetConnection()` — Helper method to reset the members associated with a connection which no longer exists
- L96 _public function_ `TSharedPtr<IDatasmithScene> GetScene()` — helper methods to access members of the proxy
- L101 _public function_ `const DirectLink::FDestinationHandle& GetDestinationHandle() const`
- L103 _public function_ `DirectLink::FDestinationHandle& GetDestinationHandle()`
- L105 _public function_ `const DirectLink::FSourceHandle& GetConnectedSourceHandle() const`
- L109 _private member_ `FDatasmithSceneReceiver::ISceneChangeListener* ChangeListener;` — Listener to changes happening on the scene associated with DirectLink destination
- L112 _private member_ `TSharedPtr<FDatasmithSceneReceiver> SceneReceiver;` — Scene receiver wrapping the change listener
- L115 _private member_ `DirectLink::FDestinationHandle Destination;` — Handle to the destination associated with the proxy
- L118 _private member_ `DirectLink::FSourceHandle ConnectedSource;` — Handle to the potential connected source
- L121 _private member_ `static TSharedPtr<FDirectLinkEndpointProxy> EndpointProxy;` — Pointer to the unique end point proxy

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DatasmithRuntime`
- L19 _prototype_ `class UDirectLinkProxy* GetDirectLinkProxy();` (scope `DatasmithRuntime`)

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/LogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithRuntime, Log, All)`

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/MaterialImportUtils.h` (Private)


#### enum `DatasmithRuntime::EMaterialRequirements::Type`  
`enum Type`  
_L20-26_
- L22 _public enumerator_ `RequiresNothing = 0x00`
- L23 _public enumerator_ `RequiresNormals = 0x01`
- L24 _public enumerator_ `RequiresTangents = 0x02`
- L25 _public enumerator_ `RequiresAdjacency = 0x04`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace DatasmithRuntime`
- L14 _namespace_ `namespace DatasmithRuntime`
- L16 _externvar_ `extern const TCHAR* MATERIAL_HOST;` (scope `DatasmithRuntime`)
- L18 _namespace_ `namespace EMaterialRequirements` (scope `DatasmithRuntime`)
- L29 _externvar_ `extern FName PbrTexturePropertyNames[];` (scope `DatasmithRuntime`)
- L31 _typedef_ `using FTextureCallback = TFunction<void(const FString&, int32)>;` (scope `DatasmithRuntime`)
- L33 _prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> ValidatePbrMaterial(TSharedPtr<IDatasmithUEPbrMaterialElement> PbrMaterialElement, FSceneImporter& SceneImporter);` (scope `DatasmithRuntime`)
- L35 _prototype_ `int32 ProcessMaterialElement(TSharedPtr< IDatasmithMaterialInstanceElement > BaseMaterialElement, FTextureCallback TextureCallback);` (scope `DatasmithRuntime`)
- L37 _prototype_ `int32 ProcessMaterialElement(IDatasmithUEPbrMaterialElement* PbrMaterialElement, FTextureCallback TextureCallback);` (scope `DatasmithRuntime`)
- L39 _prototype_ `bool LoadReferenceMaterial(UMaterialInstanceDynamic* MaterialInstance, TSharedPtr<IDatasmithMaterialInstanceElement>& MaterialElement);` (scope `DatasmithRuntime`)
- L41 _prototype_ `bool LoadPbrMaterial(IDatasmithUEPbrMaterialElement& UEPbrMaterial, UMaterialInstanceDynamic* MaterialInstance);` (scope `DatasmithRuntime`)

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/MaterialSelectors/DatasmithRuntimeMaterialSelector.h` (Private)


#### class `FDatasmithRuntimeMaterialSelector`  
`class FDatasmithRuntimeMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L10-24_
- inherits: `FDatasmithReferenceMaterialSelector`
- L13 _public prototype_ `FDatasmithRuntimeMaterialSelector();`
- L14 _public prototype_ `virtual ~FDatasmithRuntimeMaterialSelector() = default;`
- L16 _public prototype_ `virtual bool IsValid() const override;`
- L17 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& ) const override;`
- L18 _public prototype_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override;`
- L21 _private member_ `FDatasmithReferenceMaterial OpaqueMaterial;`
- L22 _private member_ `FDatasmithReferenceMaterial TransparentMaterial;`
- L23 _private member_ `FDatasmithReferenceMaterial CutoutMaterial;`

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Private/SceneImporter.h` (Private)


#### class `DatasmithRuntime::Timer`  
`class Timer`  
_L44-54_
- L47 _public prototype_ `Timer(double InTimeOrigin, const char* InText);`
- L48 _public prototype_ `~Timer();`
- L51 _private member_ `double TimeOrigin;`
- L52 _private member_ `double StartTime;`
- L53 _private member_ `FString Text;`

#### struct `DatasmithRuntime::CaseSensitive_KeyFuncs`  
`struct CaseSensitive_KeyFuncs : BaseKeyFuncs<TPair<FString, FSceneGraphId>, FString, false>`  
_L61-66_
- inherits: `BaseKeyFuncs<TPair<FString,FSceneGraphId>,FString,false>`
- L63 _public function_ `static FORCEINLINE const FString& GetSetKey(const TPair<FString, FSceneGraphId>& Element)`
- L64 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`
- L65 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`

#### enum `DatasmithRuntime::EWorkerTask`  
`enum class EWorkerTask : uint32`  
_L70-99_
- L72 _public enumerator_ `NoTask = 0x00000000`
- L73 _public enumerator_ `CollectSceneData = 0x00000001`
- L74 _public enumerator_ `UpdateElement = 0x00000002`
- L75 _public enumerator_ `ResetScene = 0x00000004`
- L76 _public enumerator_ `SetupTasks = 0x00000008`
- L78 _public enumerator_ `MeshCreate = 0x00000010`
- L79 _public enumerator_ `MaterialCreate = 0x00000020`
- L80 _public enumerator_ `TextureLoad = 0x00000040`
- L81 _public enumerator_ `TextureCreate = 0x00000080`
- L83 _public enumerator_ `MeshComponentCreate = 0x00000100`
- L84 _public enumerator_ `LightComponentCreate = 0x00000200`
- L85 _public enumerator_ `ComponentFinalize = 0x00000400`
- L86 _public enumerator_ `ComputeCollision = 0x00000800`
- L88 _public enumerator_ `MaterialAssign = 0x00001000`
- L89 _public enumerator_ `TextureAssign = 0x00002000`
- L91 _public enumerator_ `DeleteComponent = 0x00010000`
- L92 _public enumerator_ `DeleteAsset = 0x00020000`
- L93 _public enumerator_ `GarbageCollect = 0x00040000`
- L95 _public enumerator_ `NonAsyncTasks = LightComponentCreate | MeshComponentCreate | MaterialAssign | TextureCreate | TextureAssign | ComponentFinalize`
- L96 _public enumerator_ `DeleteTasks = DeleteComponent | DeleteAsset`
- L98 _public enumerator_ `AllTasks = 0xffffffff`

#### enum `DatasmithRuntime::EAssetState`  
`enum class EAssetState : uint8`  
_L103-112_
- L105 _public enumerator_ `Unknown = 0x00`
- L106 _public enumerator_ `Processed = 0x01`
- L107 _public enumerator_ `Completed = 0x02`
- L108 _public enumerator_ `Skipped = 0x04`
- L109 _public enumerator_ `Building = 0x08`
- L110 _public enumerator_ `PendingDelete = 0x10`
- L111 _public enumerator_ `AllStates = 0xff`

#### enum `DatasmithRuntime::EDataType`  
`enum class EDataType : uint8`  
_L117-128_
- desc: Order is important as it reflects dependency: bottom to top
- L119 _public enumerator_ `None = 0`
- L120 _public enumerator_ `Texture = 1`
- L121 _public enumerator_ `Material = 2`
- L122 _public enumerator_ `PbrMaterial = 3`
- L123 _public enumerator_ `Mesh = 4`
- L124 _public enumerator_ `Actor = 5`
- L125 _public enumerator_ `MeshActor = 6`
- L126 _public enumerator_ `LightActor = 7`
- L127 _public enumerator_ `Metadata = 8`

#### struct `DatasmithRuntime::FReferencer`  
`struct FReferencer`  
_L133-169_
- desc: Utility structure to track elements referencing an asset
- L135 _public member_ `uint32 Type:4;`
- L136 _public member_ `uint32 ElementId:28;` — Assuming 2^28 should be plenty to store index of referencers
- L137 _public member_ `uint16 Slot;` — Assuming 65536 should be plenty
- L139 _public function_ `FReferencer(EDataType InType, FSceneGraphId InIndex, uint16 InSlot) : Type( uint8(InType) ) , ElementId( uint32(InIndex) ) , Slot( InSlot )`
- L146 _public function_ `FReferencer(EDataType InType, FSceneGraphId InIndex) : Type( uint8(InType) ) , ElementId( uint32(InIndex) ) , Slot( 0 )`
- L153 _public function_ `FReferencer(FSceneGraphId InIndex) : Type( 0 ) , ElementId( uint32(InIndex) ) , Slot( 0 )`
- L160 _public function_ `FReferencer() : Type( 0 ) , ElementId( 0 ) , Slot( 0 )`
- L167 _public function_ `EDataType GetType() const`
- L168 _public function_ `FSceneGraphId GetId() const`

#### struct `DatasmithRuntime::FBaseData`  
`struct FBaseData`  
_L182-247_
- desc: Utility structure to hold onto information used during the import process
- L185 _public member_ `FSceneGraphId ElementId;` — Identifier of the associated Datasmith element
- L188 _public member_ `FSceneGraphId MetadataId;` — Identifier of the associated metadata element
- L190 _public member_ `EDataType Type;`
- L193 _public member_ `TWeakObjectPtr<UObject> Object;` — UObject associated with the element
- L196 _public member_ `FDataState DataState;` — State in which the element is within the import process
- L199 _public member_ `TArray< FReferencer > Referencers;` — Array of elements referencing this element
- L201 _public function_ `FBaseData(FSceneGraphId InElementId, EDataType InType = EDataType::None) : ElementId(InElementId) , MetadataId(DirectLink::InvalidId) , Type(InType)`
- L209 _public function_ `FBaseData(const FBaseData& Other)`
- L220 _public prototype_ `FBaseData& operator=(const FBaseData& Other) = delete;` — Non-assignable due to DataState atomic member
- L222 _public function_ `bool HasState(EAssetState Value) const`
- L227 _public function_ `void AddState(EAssetState Value)`
- L232 _public function_ `void ClearState(EAssetState Value)`
- L237 _public function_ `void SetState(EAssetState Value)`
- L243 _public function_ `template<typename T = UObject> T* GetObject() const`

#### struct `DatasmithRuntime::FAssetData`  
`struct FAssetData : public FBaseData`  
_L252-287_
- inherits: `FBaseData`
- desc: Utility structure to hold onto additional information used for assets
- L255 _public member_ `int32 Requirements = 0;` — Build settings requirements defined by materials, used by static meshes
- L258 _public member_ `uint32 Hash = 0;` — Hash of associated element used to prevent the duplication of assets
- L261 _public member_ `uint32 ResourceHash = 0;` — Hash of potential resource of associated element used to prevent recreation of assets
- L263 _public function_ `FAssetData(FSceneGraphId InElementId, EDataType InType = EDataType::None) : FBaseData(InElementId, InType) , Requirements(-1)`
- L270 _public prototype_ `FAssetData(const FAssetData&) = default;` — Copy constructor intentionally copies the MetadataId member whereas the assignment operator doesn't - is this intentional?
- L272 _public function_ `FAssetData& operator=(const FAssetData& Source)`
- L286 _public member_ `static FAssetData EmptyAsset;`

#### struct `DatasmithRuntime::FActorData`  
`struct FActorData : public FBaseData`  
_L292-338_
- inherits: `FBaseData`
- desc: Utility structure to hold onto additional information used for actors
- L295 _public member_ `FSceneGraphId ParentId;` — Index of parent actor in FSceneImporter's array of FActorData
- L298 _public member_ `FTransform RelativeTransform;` — Transform relative to parent
- L301 _public member_ `FTransform WorldTransform;` — Transform relative to world
- L304 _public member_ `int32 AssetId;` — Index of referenced mesh (mesh actor) or texture (light actor)
- L306 _public function_ `FActorData(FSceneGraphId InElementId) : FBaseData(InElementId, EDataType::Actor) , ParentId(DirectLink::InvalidId) , AssetId(INDEX_NONE)`
- L313 _public function_ `FActorData(FSceneGraphId InElementId, FSceneGraphId InParentID) : FBaseData(InElementId, EDataType::Actor) , ParentId(InParentID) , AssetId(INDEX_NONE)`
- L321 _public prototype_ `FActorData(const FActorData&) = default;` — Copy constructor intentionally copies the MetadataId member whereas the assignment operator doesn't - is this intentional?
- L323 _public function_ `FActorData& operator=(const FActorData& Source)`

#### struct `DatasmithRuntime::FTextureData`  
`struct FTextureData`  
_L346-371_
- desc: Texture assets can only be created and built on the main thread Consequently, their creation has been divided in two steps: - Asynchronously load the data of the texture - At each tick create a texture from its data until all required textures are done
- L348 _public member_ `EPixelFormat PixelFormat;`
- L349 _public member_ `int32 Width;`
- L350 _public member_ `int32 Height;`
- L351 _public member_ `uint32 Pitch;`
- L352 _public member_ `int16 BytesPerPixel;`
- L353 _public member_ `FUpdateTextureRegion2D Region;`
- L354 _public member_ `uint8* ImageData;`
- L356 _public member_ `float Brightness;` — For IES profile
- L357 _public member_ `float TextureMultiplier;`
- L359 _public function_ `FTextureData() : PixelFormat(EPixelFormat::PF_Unknown) , Width(0) , Height(0) , Pitch(0) , BytesPerPixel(0) , Region(0,0,0,0,0,0) , ImageData(nullptr) , Brightness(-FLT_MAX) , TextureMultiplier(-FLT_MAX)`

#### enum `DatasmithRuntime::EActionResult::Type`  
`enum Type : uint8`  
_L375-381_
- L377 _public enumerator_ `Unknown = 0`
- L378 _public enumerator_ `Succeeded = 1`
- L379 _public enumerator_ `Failed = 2`
- L380 _public enumerator_ `Retry = 3`

#### class `DatasmithRuntime::FActionTask`  
`class FActionTask`  
_L386-439_
- L389 _public function_ `~FActionTask()`
- L393 _public function_ `FActionTask() : ElementId(DirectLink::InvalidId)`
- L398 _public function_ `FActionTask(FActionTaskFunction&& Function, const FReferencer& InReferencer) : ElementId(DirectLink::InvalidId) , Referencer(InReferencer) , ActionFunc(MoveTemp(Function))`
- L405 _public function_ `FActionTask(const FActionTaskFunction& Function, const FReferencer& InReferencer) : ElementId(DirectLink::InvalidId) , Referencer(InReferencer) , ActionFunc(Function)`
- L412 _public function_ `FActionTask(FActionTaskFunction&& Function, FSceneGraphId InElementId, const FReferencer& InReferencer) : ElementId(InElementId) , Referencer(InReferencer) , ActionFunc(MoveTemp(Function))`
- L419 _public function_ `FActionTask(const FActionTaskFunction& Function, FSceneGraphId InElementId, const FReferencer& InReferencer) : ElementId(InElementId) , Referencer(InReferencer) , ActionFunc(Function)`
- L426 _public function_ `FSceneGraphId GetElementId() const`
- L428 _public function_ `const FReferencer& GetReferencer() const`
- L430 _public function_ `EActionResult::Type Execute(FBaseData& ElementData)`
- L436 _private member_ `FSceneGraphId ElementId;`
- L437 _private member_ `FReferencer Referencer;`
- L438 _private member_ `FActionTaskFunction ActionFunc;`

#### enum `DatasmithRuntime::EQueueTask`  
`enum EQueueTask`  
_L446-456_
- L448 _public enumerator_ `UpdateQueue = 0`
- L449 _public enumerator_ `MeshQueue = 1`
- L450 _public enumerator_ `MaterialQueue = 2`
- L451 _public enumerator_ `TextureQueue = 3`
- L452 _public enumerator_ `NonAsyncQueue = 4`
- L453 _public enumerator_ `DeleteCompQueue = 5` — Index of queue to delete components
- L454 _public enumerator_ `DeleteAssetQueue = 6` — Index of queue to delete assets
- L455 _public enumerator_ `MaxQueues = 7`

#### class `DatasmithRuntime::FSceneImporter`  
`class FSceneImporter : public FTickableGameObject`  
_L472-735_
- inherits: `FTickableGameObject`
- desc: Helper class to incrementally load a Datasmith scene at runtime The creation of the assets and components is incrementally done on the tick of the object. At each tick, a budget of 10 ms is allocated to perform as much tasks as possible The load process is completely interruptible. Datasmith actor elements are added as component to the root component of the associated ADatasmithRuntimeActor. @note: Only assets used by Datasmith actor elements are created. The creation is phased as followed: - Collection of the assets and actors to be added - Launch of asynchronous build of static meshes - Launch of asynchronous load of images used by textures - Creation of Materials, textures, components and resolution of referencing (i.e material assignment, ...) are synchronously done on the Game thread.
- L475 _public prototype_ `explicit FSceneImporter(ADatasmithRuntimeActor* InDatasmithRuntimeActor);`
- L477 _public prototype_ `virtual ~FSceneImporter();`
- L484 _public prototype_ `void StartImport(TSharedRef< IDatasmithScene > InSceneElement, const FDatasmithRuntimeImportOptions& Options);` — Start the import process of a scene @param InSceneElement: Datasmith scene to import @param Options: Options to use for the import process
- L487 _public prototype_ `void Reset(bool bIsNewScene);` — Abort the on going import process then delete all created assets and actors
- L490 _public function_ `TSharedPtr< IDatasmithElement > GetElementFromName(const FString& PrefixedName)` — Returns the Datasmith element associated to a given asset name
- L503 _public prototype_ `bool IncrementalUpdate(TSharedRef< IDatasmithScene > InSceneElement, FUpdateContext& UpdateContext);` — Start the incremental update of the elements contained in the given context
- L505 _public function_ `void SetTranslator(const TSharedPtr<IDatasmithTranslator>& InTranslator)`
- L509 _protected prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L510 _protected function_ `virtual bool IsTickable() const override`
- L511 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L517 _private prototype_ `bool DeleteData();` — Delete all the assets and components created during the previous import process
- L520 _private prototype_ `EActionResult::Type DeleteElement(FSceneGraphId ElementId);` — Delete the asset or component associated with the Datasmith element associated with the ElementId
- L523 _private prototype_ `bool DeleteComponent(FActorData& ActorData);` — Delete the component created from the given FActorData
- L526 _private prototype_ `bool DeleteAsset(FAssetData& AssetData);` — Delete the asset created from the given FAssetData
- L529 _private prototype_ `void RemoveFromReferencer(FSceneGraphId* AssetIdPtr, FSceneGraphId ReferencerId);` — Remove given referencer from the list of referencers of the asset
- L535 _private prototype_ `void CollectSceneData();` — Creates the FAssetData and FActorData required to import the associated Datasmith scene This is the first task  after StartImport has been called
- L538 _private prototype_ `void SetupTasks();` — Sets up all counters and data required to proceed with a full import or an incremental update
- L540 _private prototype_ `void PrepareIncrementalUpdate(FUpdateContext& UpdateContext);`
- L542 _private prototype_ `void IncrementalAdditions(TArray<TSharedPtr<IDatasmithElement>>& Additions, TArray<TSharedPtr<IDatasmithElement>>& Updates);`
- L544 _private prototype_ `void IncrementalModifications(TArray<TSharedPtr<IDatasmithElement>>& Modifications);`
- L546 _private prototype_ `void IncrementalDeletions(TArray<DirectLink::FSceneGraphId>& Deletions);`
- L549 _private prototype_ `void AddAsset(TSharedPtr<IDatasmithElement>&& ElementPtr, const FString& Prefix, EDataType InType = EDataType::None);` — Add an FAssetData object associated with the element's id to the map
- L557 _private prototype_ `void ParseScene(const TSharedPtr<IDatasmithActorElement>& ActorElement, FSceneGraphId ParentId, FParsingCallback Callback);` — Recursive helper method to visit the children of an Datasmith actor element @param ActorElement: Datasmith actor element to visit @param ParentId: Identifier of the incoming actor's parent @param Callback: function called on incoming actor
- L560 _private prototype_ `void ProcessActorElement(const TSharedPtr< IDatasmithActorElement >& ActorElement, FSceneGraphId ParentId);` — Add and populate the FActorData created for the incoming Datasmith actor element
- L563 _private prototype_ `bool ProcessMeshActorData(FActorData& ActorData, IDatasmithMeshActorElement* MeshActorElement);` — Populate the FActorData created for the incoming Datasmith mesh actor element
- L566 _private prototype_ `bool ProcessLightActorData(FActorData& ActorData, IDatasmithLightActorElement* LightActorElement);` — Populate the FActorData created for the incoming Datasmith light actor element
- L569 _private prototype_ `bool ProcessCameraActorData(FActorData& ActorData, IDatasmithCameraActorElement* CameraActorElement);` — Populate the FActorData created for the incoming Datasmith camera actor element
- L575 _private prototype_ `bool ProcessMeshData(FAssetData& MeshData);` — Populate the FAssetData based on the associated Datasmith mesh element @note: A static mesh is created at this stage to be used in the asynchronous build process
- L578 _private prototype_ `void ProcessMaterialData(FAssetData& MaterialData);` — Populate the FAssetData based on the associated Datasmith material element
- L581 _private prototype_ `EActionResult::Type ProcessMaterial(FSceneGraphId MaterialId);` — Create the FAssetData based on the associated Datasmith material element
- L584 _private prototype_ `void CreateActorComponent(FActorData& ActorData, const TSharedPtr< IDatasmithActorElement >& ActorElement);` — Add and populate the FActorData created for the incoming Datasmith actor element
- L587 _private prototype_ `void ProcessTextureData(FSceneGraphId TextureId);` — Add and populate a FTextureData associated with the incoming Datasmith texture element
- L590 _private prototype_ `bool CreateStaticMesh(FSceneGraphId ElementId);` — Asynchronous build of a static mesh
- L593 _private prototype_ `void FillStaticMeshMaterials(FAssetData& MeshData, TArray< FMeshDescription >& MeshDescriptions);` — Update StaticMaterials array based on mesh description and mesh element
- L596 _private prototype_ `void UpdateStaticMeshMaterials(FAssetData& MeshData);` — Update StaticMaterials array based on mesh description and mesh element
- L599 _private prototype_ `EActionResult::Type CreateMeshComponent(FSceneGraphId ActorId, UStaticMesh* StaticMesh);` — Create and add a static mesh component to the root component
- L602 _private prototype_ `EActionResult::Type AssignMaterial(const FReferencer& Referencer, UMaterialInstanceDynamic* Material);` — Assign the given material to the object associated to the referencer, static mesh or static mesh component
- L605 _private prototype_ `bool LoadTexture(FSceneGraphId ElementId);` — Asynchronous load of the image or IES file required to build a texture
- L608 _private prototype_ `EActionResult::Type CreateTexture(FSceneGraphId ElementId);` — Create the UTexture object associated with the given element identifier
- L611 _private prototype_ `EActionResult::Type AssignTexture(const FReferencer& Referencer, UTexture2D* Texture);` — Assign the given 2D texture to the object associated to the referencer, a material
- L614 _private prototype_ `EActionResult::Type AssignProfileTexture(const FReferencer& Referencer, UTextureLightProfile* TextureProfile);` — Assign the given IES texture to the object associated to the referencer, a light component
- L617 _private prototype_ `EActionResult::Type CreateLightComponent(FSceneGraphId ActorId);` — Create and add a light component to the root component based on the type of the identified Datasmith element
- L619 _private prototype_ `void FinalizeComponent(FActorData& ActorData);`
- L622 _private prototype_ `void ProcessDependency(const TSharedPtr<IDatasmithElement>& Element);` — Calls when an element on which an asset or actor depends on has changed
- L625 _private function_ `void AddToQueue(int32 WhichQueue, FActionTask&& ActionTask)` — Add a new task to the given queue
- L638 _private function_ `void ProcessQueue(int32 Which, double EndTime, EWorkerTask TaskCompleted = EWorkerTask::NoTask, EWorkerTask TaskFollowing = EWorkerTask::NoTask)` — Helper method to dequeue a given queue for a given amount of time
- L656 _private prototype_ `FActorData& FindOrAddActorData(const TSharedPtr< IDatasmithActorElement >& ActorElement);`
- L659 _private prototype_ `void ProcessMetdata(const TSharedPtr< IDatasmithMetaDataElement >& MetadataElement);` — Add metadata to the tracking system if it applies to any tracked asset or actor or the scene
- L662 _private prototype_ `void ApplyMetadata(FSceneGraphId MetadataId, UObject* Object);` — Apply metadata to input object if applicable
- L666 _private member_ `TWeakObjectPtr<USceneComponent> RootComponent;` — DatasmithRuntime actor associated with this importer
- L669 _private member_ `TSharedPtr<IDatasmithScene> SceneElement;` — IDatasmithScene associated with DatasmithRuntime actor
- L671 _private member_ `TSharedPtr<IDatasmithTranslator> Translator;`
- L674 _private member_ `TMap< FSceneGraphId, TSharedPtr< IDatasmithElement > > Elements;` — Map of all elements in the IDatasmithScene
- L677 _private member_ `FCaseSensitiveMap AssetElementMapping;` — Mapping between prefixed asset element's name and index of element in flatten element list
- L680 _private member_ `TMap< FSceneGraphId, FAssetData > AssetDataList;` — Mapping between Datasmith element's identifiers and their associated FAssetData object
- L683 _private member_ `TMap< FSceneGraphId, FActorData > ActorDataList;` — Mapping between Datasmith actor element's identifiers and their associated FActorData object
- L686 _private member_ `TMap< FSceneGraphId, FTextureData > TextureDataList;` — Mapping between Datasmith texture element's identifiers and their associated FActorData object
- L689 _private member_ `TMap< FSceneGraphId, FReferencer > DependencyList;` — Mapping between Datasmith asset elements and their dependent elements
- L692 _private member_ `TSet< FSceneGraphId > MeshElementSet;` — Set of Datasmith mesh element's identifiers to process
- L695 _private member_ `TSet< FSceneGraphId > MaterialElementSet;` — Set of Datasmith material element's identifiers to process
- L698 _private member_ `TSet< FSceneGraphId > TextureElementSet;` — Set of Datasmith texture element's identifiers to process
- L701 _private member_ `TMap< FSceneGraphId, float > LightmapWeights;` — Mapping between Datasmith mesh element's identifiers and their lightmap weights
- L704 _private member_ `TQueue< FActionTask, EQueueMode::Mpsc > ActionQueues[EQueueTask::MaxQueues];` — Array of queues dequeued during the import process
- L707 _private member_ `TArray<TFuture<bool>> OnGoingTasks;` — Array of asynchronous tasks started during the import
- L710 _private member_ `EWorkerTask TasksToComplete;` — Flag used to properly sequence the import process
- L713 _private member_ `uint8 bIncrementalUpdate:1;` — Indicated a incremental update has been requested
- L716 _private member_ `FDatasmithRuntimeImportOptions ImportOptions;` — Specifies options to use during the import
- L719 _private member_ `TFuture<void> MetadataCollect;` — Future for asynchronous task to collect metadata
- L722 _private member_ `float& OverallProgress;` — Miscellaneous counters used to report progress
- L723 _private member_ `FThreadSafeCounter ActionCounter;`
- L724 _private member_ `double ProgressStep;`
- L725 _private member_ `int32 QueuedTaskCount;`
- L728 _private member_ `FGuid LastSceneGuid;` — GUID of the last scene imported
- L729 _private member_ `uint32 LastSceneKey;`
- L730 _private member_ `uint32 SceneKey;`
- L733 _private member_ `double GlobalStartTime;`

#### Free symbols / members of external scopes

- L33 _macro_ `#define LIVEUPDATE_TIME_LOGGING`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaticMeshComplete, UStaticMesh*) DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialComplete, UMaterialInstanceDynamic*) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTextureComplete, UTexture2D*) namespace DatasmithRuntime { #ifdef LIVEUPDATE_TIME_LOGGING class Timer { public: Timer(double InTimeOrigin, const char* InText); ~Timer(); private: double TimeOrigin; double StartTime; FString Text; }; #endif typedef DirectLink::FSceneGraphId FSceneGraphId; using FParsingCallback = TFunction<void(const TSharedPtr<IDatasmithActorElement>&, FSceneGraphId)>; struct CaseSensitive_KeyFuncs : BaseKeyFuncs<TPair<FString, FSceneGraphId>, FString, false> { static FORCEINLINE const FString& GetSetKey(const TPair<FString, FSceneGraphId>& Element) { return Element.Key; } static FORCEINLINE uint32 GetKeyHash(const FString& Key) { return GetTypeHash(Key); } static FORCEINLINE bool Matches(const FString& A, const FString& B) { return A.Equals(B, ESearchCase::CaseSensitive); } }; using FCaseSensitiveMap = TMap<FString, FSceneGraphId, FDefaultSetAllocator, CaseSensitive_KeyFuncs>; enum class EWorkerTask : uint32 { NoTask = 0x00000000, CollectSceneData = 0x00000001, UpdateElement = 0x00000002, ResetScene = 0x00000004, SetupTasks = 0x00000008,`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialComplete, UMaterialInstanceDynamic*) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTextureComplete, UTexture2D*) namespace DatasmithRuntime { #ifdef LIVEUPDATE_TIME_LOGGING class Timer { public: Timer(double InTimeOrigin, const char* InText); ~Timer(); private: double TimeOrigin; double StartTime; FString Text; }; #endif typedef DirectLink::FSceneGraphId FSceneGraphId; using FParsingCallback = TFunction<void(const TSharedPtr<IDatasmithActorElement>&, FSceneGraphId)>; struct CaseSensitive_KeyFuncs : BaseKeyFuncs<TPair<FString, FSceneGraphId>, FString, false> { static FORCEINLINE const FString& GetSetKey(const TPair<FString, FSceneGraphId>& Element) { return Element.Key; } static FORCEINLINE uint32 GetKeyHash(const FString& Key) { return GetTypeHash(Key); } static FORCEINLINE bool Matches(const FString& A, const FString& B) { return A.Equals(B, ESearchCase::CaseSensitive); } }; using FCaseSensitiveMap = TMap<FString, FSceneGraphId, FDefaultSetAllocator, CaseSensitive_KeyFuncs>; enum class EWorkerTask : uint32 { NoTask = 0x00000000, CollectSceneData = 0x00000001, UpdateElement = 0x00000002, ResetScene = 0x00000004, SetupTasks = 0x00000008,`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTextureComplete, UTexture2D*) namespace DatasmithRuntime { #ifdef LIVEUPDATE_TIME_LOGGING class Timer { public: Timer(double InTimeOrigin, const char* InText); ~Timer(); private: double TimeOrigin; double StartTime; FString Text; }; #endif typedef DirectLink::FSceneGraphId FSceneGraphId; using FParsingCallback = TFunction<void(const TSharedPtr<IDatasmithActorElement>&, FSceneGraphId)>; struct CaseSensitive_KeyFuncs : BaseKeyFuncs<TPair<FString, FSceneGraphId>, FString, false> { static FORCEINLINE const FString& GetSetKey(const TPair<FString, FSceneGraphId>& Element) { return Element.Key; } static FORCEINLINE uint32 GetKeyHash(const FString& Key) { return GetTypeHash(Key); } static FORCEINLINE bool Matches(const FString& A, const FString& B) { return A.Equals(B, ESearchCase::CaseSensitive); } }; using FCaseSensitiveMap = TMap<FString, FSceneGraphId, FDefaultSetAllocator, CaseSensitive_KeyFuncs>; enum class EWorkerTask : uint32 { NoTask = 0x00000000, CollectSceneData = 0x00000001, UpdateElement = 0x00000002, ResetScene = 0x00000004, SetupTasks = 0x00000008, MeshCreate = 0x00000010,`
- L41 _namespace_ `namespace DatasmithRuntime`
- L57 _typedef_ `typedef DirectLink::FSceneGraphId FSceneGraphId;` (scope `DatasmithRuntime`)
- L59 _typedef_ `using FParsingCallback = TFunction<void(const TSharedPtr<IDatasmithActorElement>&, FSceneGraphId)>;` (scope `DatasmithRuntime`)
- L68 _typedef_ `using FCaseSensitiveMap = TMap<FString, FSceneGraphId, FDefaultSetAllocator, CaseSensitive_KeyFuncs>;` (scope `DatasmithRuntime`)
- L101 _prototype_ `ENUM_CLASS_FLAGS(EWorkerTask);` (scope `DatasmithRuntime`)
- L114 _prototype_ `ENUM_CLASS_FLAGS(EAssetState);` (scope `DatasmithRuntime`)
- L171 _function_ `FORCEINLINE bool operator==(const FReferencer& Lhs, const FReferencer& Rhs)` (scope `DatasmithRuntime`)
- L177 _typedef_ `typedef std::atomic<EAssetState> FDataState;` (scope `DatasmithRuntime`)
- L373 _namespace_ `namespace EActionResult` (scope `DatasmithRuntime`)
- L384 _typedef_ `using FActionTaskFunction = TFunction<EActionResult::Type(UObject* Object, const FReferencer& Referencer)>;` (scope `DatasmithRuntime`)
- L441 _externvar_ `extern const FString TexturePrefix;` (scope `DatasmithRuntime`)
- L442 _externvar_ `extern const FString MaterialPrefix;` (scope `DatasmithRuntime`)
- L443 _externvar_ `extern const FString MeshPrefix;` (scope `DatasmithRuntime`)
- L740 _macro_ `#define LIVEUPDATE_LOG_TIME Timer( GlobalStartTime, __func__ )`
- L742 _macro_ `#define LIVEUPDATE_LOG_TIME`

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Public/DatasmithRuntime.h` (Public)


#### struct `FUpdateContext`  
`struct FUpdateContext`  
_L35-40_
- L37 _public member_ `TArray<TSharedPtr<IDatasmithElement>> Additions;`
- L38 _public member_ `TArray<TSharedPtr<IDatasmithElement>> Updates;`
- L39 _public member_ `TArray<DirectLink::FSceneGraphId> Deletions;`

#### class `DatasmithRuntime::FTranslationJob`  
`class FTranslationJob`  
_L44-62_
- L47 _public function_ `FTranslationJob(ADatasmithRuntimeActor* InActor, const FString& InFilePath) : RuntimeActor(InActor) , FilePath(InFilePath)`
- L53 _public function_ `FTranslationJob()`
- L57 _public prototype_ `bool Execute();`
- L60 _private member_ `TWeakObjectPtr<ADatasmithRuntimeActor> RuntimeActor;`
- L61 _private member_ `FString FilePath;`

#### class `DatasmithRuntime::FTranslationThread`  
`class FTranslationThread`  
_L64-84_
- L67 _public function_ `FTranslationThread() : bKeepRunning(false)`
- L71 _public prototype_ `~FTranslationThread();`
- L73 _public prototype_ `void Run();`
- L75 _public function_ `void AddJob(FTranslationJob&& Job)`
- L80 _public member_ `std::atomic_bool bKeepRunning;`
- L81 _public member_ `TFuture<void> ThreadResult;`
- L82 _public member_ `FEvent* ThreadEvent = nullptr;`
- L83 _public member_ `TQueue< FTranslationJob, EQueueMode::Mpsc > JobQueue;`

#### enum `EBuildHierarchyMethod`  
`enum class EBuildHierarchyMethod : uint8`  
_L91-96_
- reflection: `UENUM(BlueprintType)`
- L93 _public enumerator_ `None`
- L94 _public enumerator_ `Simplified`
- L95 _public enumerator_ `Unfiltered`

#### struct `FDatasmithRuntimeImportOptions`  
`struct FDatasmithRuntimeImportOptions`  
_L99-134_
- reflection: `USTRUCT(BlueprintType)`
- L105 _public member_ `FDatasmithTessellationOptions TessellationOptions;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)` — Tessellation options for CAD import
- L113 _public member_ `EBuildHierarchyMethod BuildHierarchy = EBuildHierarchyMethod::Simplified;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)` — Indicates whether a hierarchy of actors should be built or not. In the case a hierarchy is built, it can be simplified to minimize the number of actors created By default, a simplified hierarchy is built
- L120 _public member_ `TEnumAsByte<ECollisionEnabled::Type> BuildCollisions = ECollisionEnabled::QueryOnly;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)` — Indicates the type of collision for components Set to ECollisionEnabled::QueryOnly (spatial queries, no physics) by default
- L127 _public member_ `TEnumAsByte<ECollisionTraceFlag> CollisionType = ECollisionTraceFlag::CTF_UseComplexAsSimple;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)` — Indicates the type of collision for static meshes Set to ECollisionTraceFlag::CTF_UseComplexAsSimple by default
- L133 _public member_ `bool bImportMetaData = true;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)` — Indicates whether meta-data should be imported or not Meta-data are imported by default

#### class `ADatasmithRuntimeActor`  
`class ADatasmithRuntimeActor : public AActor , public FDatasmithSceneReceiver_ISceneChangeListener`  
_L137-232_
- reflection: `UCLASS(meta = (DisplayName = "Datasmith Destination"))`
- inherits: `AActor,FDatasmithSceneReceiver_ISceneChangeListener`
- L144 _public prototype_ `ADatasmithRuntimeActor();`
- L147 _public prototype_ `virtual void BeginPlay() override;` — AActor overrides
- L148 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L149 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L153 _public prototype_ `virtual void OnOpenDelta( ) override;` — ISceneChangeListener interface
- L154 _public prototype_ `virtual void OnNewScene(const DirectLink::FSceneIdentifier& SceneId) override;`
- L155 _public prototype_ `virtual void OnAddElement(DirectLink::FSceneGraphId ElementId, TSharedPtr<IDatasmithElement> Element) override;`
- L156 _public prototype_ `virtual void OnChangedElement(DirectLink::FSceneGraphId ElementId, TSharedPtr<IDatasmithElement> Element) override;`
- L157 _public prototype_ `virtual void OnRemovedElement(DirectLink::FSceneGraphId ElementId) override;`
- L158 _public prototype_ `virtual void OnCloseDelta() override;`
- L162 _public prototype_ `bool IsConnected();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L165 _public function_ `FString GetDestinationName()` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L168 _public prototype_ `FString GetSourceName();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L171 _public prototype_ `bool OpenConnectionWithIndex(int32 SourceIndex);` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L174 _public prototype_ `void CloseConnection();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L177 _public prototype_ `int32 GetSourceIndex();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L180 _public member_ `float Progress;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadOnly)`
- L183 _public member_ `bool bBuilding;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadOnly)`
- L186 _public member_ `FString LoadedScene;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadOnly)`
- L189 _public member_ `FDatasmithRuntimeImportOptions ImportOptions;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadWrite)`
- L192 _public member_ `FString ExternalFile;` — `UPROPERTY(Category = "DatasmithRuntime", EditDefaultsOnly, BlueprintReadOnly)`
- L195 _public function_ `bool IsReceiving()` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L198 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L201 _public prototype_ `bool LoadFile(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L203 _public function_ `void SetScene(TSharedPtr<IDatasmithScene> InSceneElement)`
- L205 _public prototype_ `void ApplyNewScene();`
- L207 _public prototype_ `virtual void OnImportEnd();`
- L209 _public prototype_ `static void OnShutdownModule();`
- L210 _public prototype_ `static void OnStartupModule();`
- L213 _private member_ `TSharedPtr< DatasmithRuntime::FSceneImporter > SceneImporter;`
- L215 _private member_ `TSharedPtr<DatasmithRuntime::FDestinationProxy> DirectLinkHelper;`
- L217 _private member_ `TSharedPtr<IDatasmithScene> SceneElement;`
- L218 _private member_ `TSharedPtr<IDatasmithTranslator> Translator;`
- L220 _private member_ `std::atomic_bool bNewScene;`
- L221 _private member_ `std::atomic_bool bReceivingStarted;`
- L222 _private member_ `std::atomic_bool bReceivingEnded;`
- L224 _private member_ `float ElementDeltaStep;`
- L226 _private member_ `static std::atomic_bool bImportingScene;`
- L227 _private member_ `FUpdateContext UpdateContext;`
- L229 _private member_ `static TUniquePtr<DatasmithRuntime::FTranslationThread> TranslationThread;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace DatasmithRuntime`
- L42 _namespace_ `namespace DatasmithRuntime`
- L88 _typedef_ `using FDatasmithSceneReceiver_ISceneChangeListener = FDatasmithSceneReceiver::ISceneChangeListener;` — UHT doesn't really like operator ::

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Public/DatasmithRuntimeBlueprintLibrary.h` (Public)


#### struct `FDatasmithRuntimeSourceInfo`  
`struct FDatasmithRuntimeSourceInfo`  
_L21-39_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public function_ `FDatasmithRuntimeSourceInfo()`
- L29 _public function_ `FDatasmithRuntimeSourceInfo( const FString& InName, const FGuid& InHandle) : Name(InName) , SourceHandle(InHandle)`
- L36 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DatasmithRuntime")`
- L38 _public member_ `FGuid SourceHandle;`

#### class `UDirectLinkProxy`  
`class UDirectLinkProxy : public UObject`  
_L45-65_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Class to interface with the DirectLink end point
- L50 _public prototype_ `UDirectLinkProxy();`
- L51 _public prototype_ `~UDirectLinkProxy();`
- L54 _public prototype_ `FString GetEndPointName();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L57 _public prototype_ `TArray<FDatasmithRuntimeSourceInfo> GetListOfSources();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L62 _public member_ `FDatasmithRuntimeChangeEvent OnDirectLinkChange;` — `UPROPERTY(BlueprintAssignable)` — Dynamic delegate used to trigger an event in the Game when there is a change in the DirectLink network

#### class `UDatasmithRuntimeLibrary`  
`class UDatasmithRuntimeLibrary : public UBlueprintFunctionLibrary`  
_L68-97_
- reflection: `UCLASS(meta = (ScriptName = "DatasmithRuntimeLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L80 _public prototype_ `static bool LoadFile(ADatasmithRuntimeActor* DatasmithRuntimeActor, const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")` — Load a file using the Datasmith translator associated with it @param DatasmithRuntimeActor	The actor to load the file into @param FilePath The path to the file to load. @return	true if an associated translator has been
- L83 _public prototype_ `static void ResetActor(ADatasmithRuntimeActor* DatasmithRuntimeActor);` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")`
- L87 _public prototype_ `static UDirectLinkProxy* GetDirectLinkProxy();` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntime")` — Returns an interface to the DirectLink end point
- L96 _public prototype_ `static bool LoadFileFromExplorer(ADatasmithRuntimeActor* DatasmithRuntimeActor, const FString& DefaultPath);` — `UFUNCTION(BlueprintCallable, Category = "DatasmithRuntimeHelper")` — Open a file browser to select a file and call LoadFile with the selected file @param DatasmithRuntimeActor	The actor to load the file into @param DefaultPath Path to open the file browser in. @return	true if an associated translator has been

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DatasmithRuntime`
- L41 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDatasmithRuntimeChangeEvent);`
- L41 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDatasmithRuntimeChangeEvent);`

### `Plugins/Experimental/Enterprise/DatasmithRuntime/Source/Public/DatasmithRuntimeModule.h` (Public)


#### class `IDatasmithRuntimeModuleInterface`  
`class IDatasmithRuntimeModuleInterface : public IModuleInterface`  
_L13-25_
- inherits: `IModuleInterface`
- L16 _public function_ `static IDatasmithRuntimeModuleInterface& Get()`
- L21 _public function_ `static bool IsAvailable()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define DATASMITHLIVEUPDATE_MODULE_NAME TEXT("DatasmithRuntime")`
