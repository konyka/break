# Plugins / InterchangeFbxParser

- module root: `Plugins/Interchange/Runtime/Source/Parsers/Fbx`
- headers: 20; symbols: 581
- symbol kinds: class=21, delegate=1, enum=3, enumerator=21, function=94, macro=10, member=161, namespace=59, prototype=185, struct=20, typedef=6
- PrivateDependencyModuleNames: DeveloperSettings, Engine, ImageCore, ImageWrapper, InterchangeCommonParser, InterchangeEngine, InterchangeMessages, InterchangeNodes, MeshConversion, MeshDescription, SkeletalMeshDescription, StaticMeshDescription
- PrivateIncludePathModuleNames: InterchangeImport
- PublicDependencyModuleNames: Core, CoreUObject, InterchangeCore

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxAPI.h` (Private)


#### class `UE::Interchange::Private::IFbxParser`  
`class IFbxParser`  
_L39-72_
- L42 _public prototype_ `virtual ~IFbxParser() = default;`
- L44 _public prototype_ `virtual const TCHAR* GetName() = 0;`
- L46 _public function_ `virtual bool IsThreadSafe()`
- L48 _public prototype_ `virtual void SetResultContainer(UInterchangeResultsContainer* Result) = 0;`
- L49 _public prototype_ `virtual void SetConvertSettings(const bool InbConvertScene, const bool InbForceFrontXAxis, const bool InbConvertSceneUnit, const bool InbKeepFbxNamespace, const bool InbConsiderClusterBeforePoseForMeshBindPose) = 0;`
- L52 _public prototype_ `virtual bool LoadFbxFile(const FString& Filename, UInterchangeBaseNodeContainer& NodeContainer) = 0;` — Load an fbx file into the fbx sdk, return false if the file could not be load.
- L55 _public prototype_ `virtual void FillContainerWithFbxScene(UInterchangeBaseNodeContainer& NodeContainer) = 0;` — Extract the fbx data from the sdk into our node container
- L58 _public prototype_ `virtual bool FetchPayloadData(const FString& PayloadKey, const FString& PayloadFilepath) = 0;` — Extract the fbx data from the sdk into our node container
- L61 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath) = 0;` — Extract the fbx mesh data from the sdk into our node container
- L63 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData) = 0;`
- L64 _public function_ `virtual bool FetchTexturePayload(const FString& PayloadKey, TOptional<TArray64<uint8>>& OutTexturePayloadData)`
- L70 _public prototype_ `virtual bool FetchAnimationBakeTransformPayload(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, const FString& ResultFolder, FCriticalSection* ResultPayloadsCriticalSection, TAtomic<int64>& UniqueIdCounter, TMap<FString, FString>& ResultPayloads ) = 0;` — Extract the fbx data from the sdk into our node container @Param PayloadQueries - Will be grouped based on their TimeDescription Hashes (so that we acquire the same timings in one iteration, avoiding cache rebuilds)
- L71 _public prototype_ `virtual void Reset() = 0;`

#### class `UE::Interchange::Private::FFbxParser`  
`class FFbxParser: public IFbxParser`  
_L74-204_
- inherits: `IFbxParser`
- L77 _public function_ `explicit FFbxParser(TWeakObjectPtr<UInterchangeResultsContainer> InResultsContainer) : ResultsContainer(InResultsContainer)`
- L81 _public function_ `virtual const TCHAR* GetName() override`
- L86 _public prototype_ `~FFbxParser();`
- L88 _public prototype_ `virtual void Reset() override;`
- L90 _public function_ `virtual void SetResultContainer(UInterchangeResultsContainer* Result) override`
- L95 _public function_ `virtual void SetConvertSettings(const bool InbConvertScene, const bool InbForceFrontXAxis, const bool InbConvertSceneUnit, const bool InbKeepFbxNamespace, const bool InbConsiderClusterBeforePoseForMeshBindPose) override`
- L105 _public prototype_ `const TSharedPtr<FFbxHelper> GetFbxHelper();` — return the fbx helper for this parser
- L108 _public prototype_ `virtual bool LoadFbxFile(const FString& Filename, UInterchangeBaseNodeContainer& NodeContainer) override;` — Load an fbx file into the fbx sdk, return false if the file could not be load.
- L111 _public prototype_ `virtual void FillContainerWithFbxScene(UInterchangeBaseNodeContainer& NodeContainer) override;` — Extract the fbx data from the sdk into our node container
- L114 _public prototype_ `virtual bool FetchPayloadData(const FString& PayloadKey, const FString& PayloadFilepath) override;` — Extract the fbx data from the sdk into our node container
- L117 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath) override;` — Extract the fbx mesh data from the sdk into our node container
- L119 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData) override;`
- L125 _public prototype_ `virtual bool FetchAnimationBakeTransformPayload(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, const FString& ResultFolder, FCriticalSection* ResultPayloadsCriticalSection, TAtomic<int64>& UniqueIdCounter, TMap<FString, FString>& ResultPayloads ) override;` — Extract the fbx data from the sdk into our node container @Param PayloadQueries - Will be grouped based on their TimeDescription Hashes (so that we acquire the same timings in one iteration, avoiding cache rebuilds)
- L131 _public function_ `template <typename T> T* AddMessage() const` — This function is used to add the given message object directly into the results for this operation.
- L140 _public function_ `void AddMessage(UInterchangeResult* Item) const`
- L147 _public function_ `FbxScene* GetSDKScene()`
- L149 _public function_ `double GetFrameRate()`
- L151 _public function_ `bool IsCreatorBlender()`
- L153 _public function_ `const FString& GetSourceFilename() const`
- L155 _public function_ `bool GetUseFbxClustersForBindPoseMatrices() const`
- L157 _public member_ `FbxAMatrix JointOrientationMatrix;`
- L164 _public member_ `FCriticalSection PayloadCriticalSection;` — Critical section to avoid getting multiple payload in same time. The FBX evaluator use a cache mechanism for evaluating global transform that is not thread safe. There si other stuff in the sdk which are not thread safe, so all fbx payload should be fetch one by one
- L167 _private prototype_ `void EnsureNodeNameAreValid(const FString& BaseFilename);`
- L168 _private prototype_ `void CleanupFbxData();`
- L169 _private prototype_ `void ProcessExtraInformation(UInterchangeBaseNodeContainer& NodeContainer);`
- L171 _private member_ `TWeakObjectPtr<UInterchangeResultsContainer> ResultsContainer;`
- L172 _private member_ `FbxManager* SDKManager = nullptr;`
- L173 _private member_ `FbxScene* SDKScene = nullptr;`
- L174 _private member_ `FbxImporter* SDKImporter = nullptr;`
- L175 _private member_ `FbxGeometryConverter* SDKGeometryConverter = nullptr;`
- L176 _private member_ `FbxIOSettings* SDKIoSettings = nullptr;`
- L177 _private member_ `FString SourceFilename;`
- L178 _private member_ `TMap<FString, TSharedPtr<FPayloadContextBase>> PayloadContexts;`
- L179 _private member_ `TSharedPtr<FFbxHelper> FbxHelper;`
- L182 _private member_ `double FrameRate = 30.0;` — For PivotReset and Animation Conversion:
- L185 _private member_ `bool bConvertScene = true;` — Convert settings
- L186 _private member_ `bool bForceFrontXAxis = false;`
- L187 _private member_ `bool bConvertSceneUnit = true;`
- L188 _private member_ `bool bKeepFbxNamespace = false;`
- L189 _private member_ `bool bCreatorIsBlender = false;`
- L190 _private member_ `bool bConsiderClusterBeforePoseForMeshBindPose = false;`
- L202 _private member_ `} FileDetails;`

#### struct `UE::Interchange::Private::FFbxParser::FileDetails`  
`struct FileDetails`  
_L192-202_
- L194 _public member_ `FString FbxFileVersion;`
- L195 _public member_ `FString FbxFileCreator;`
- L196 _public member_ `FString ApplicationName;`
- L197 _public member_ `FString ApplicationVersion;`
- L198 _public member_ `FString ApplicationVendor;`
- L199 _public member_ `FString UnitSystem;`
- L200 _public member_ `FString AxisDirection;`
- L201 _public member_ `FString FrameRate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define FBX_METADATA_PREFIX TEXT("FBX.")`
- L12 _macro_ `#define INVALID_UNIQUE_ID 0xFFFFFFFFFFFFFFFF`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L33 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Interchange` (scope `UE`)
- L37 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxAnimation.h` (Private)


#### struct `UE::Interchange::Private::FNodeTransformFetchPayloadData`  
`struct FNodeTransformFetchPayloadData`  
_L28-33_
- desc: Skeletal/Rigged Animation
- L30 _public member_ `FbxNode* Node = nullptr;`
- L31 _public member_ `FbxAnimStack* CurrentAnimStack = nullptr;`
- L32 _public member_ `bool bIsRootJoint = false;`

#### struct `UE::Interchange::Private::FAttributeFetchPayloadData`  
`struct FAttributeFetchPayloadData`  
_L36-45_
- desc: User defined animations:
- L38 _public member_ `FbxNode* Node = nullptr;`
- L39 _public member_ `FbxAnimCurveNode* AnimCurves = nullptr;`
- L42 _public member_ `bool bAttributeTypeIsStepCurveAnimation = false;` — If true the payload is TArray<FInterchangeStepCurve>, if false the payload is TArray<FInterchangeCurve>
- L43 _public member_ `fbxsdk::EFbxType PropertyType = fbxsdk::EFbxType::eFbxUndefined;`
- L44 _public member_ `FbxProperty Property;`

#### struct `UE::Interchange::Private::FAttributeNodeTransformFetchPayloadData`  
`struct FAttributeNodeTransformFetchPayloadData`  
_L48-55_
- desc: Rigid Animation
- L50 _public member_ `double FrameRate = 30.0;`
- L51 _public member_ `FbxNode* Node = nullptr;`
- L52 _public member_ `FbxAnimCurveNode* TranlsationCurveNode = nullptr;`
- L53 _public member_ `FbxAnimCurveNode* RotationCurveNode = nullptr;`
- L54 _public member_ `FbxAnimCurveNode* ScaleCurveNode = nullptr;`

#### struct `UE::Interchange::Private::FMorphTargetFetchPayloadData`  
`struct FMorphTargetFetchPayloadData`  
_L57-76_
- L65 _public member_ `FbxScene* SDKScene;`
- L67 _public member_ `int32 GeometryIndex;`
- L68 _public member_ `int32 MorphTargetIndex;`
- L69 _public member_ `int32 ChannelIndex;`
- L70 _public member_ `FbxAnimLayer* AnimLayer;`
- L74 _public member_ `TArray<FString> InbetweenCurveNames;` — In between blend shape animation support The count of the curve names should match the in between full weights
- L75 _public member_ `TArray<float> InbetweenFullWeights;`

#### class `UE::Interchange::Private::FAnimationPayloadContext`  
`class FAnimationPayloadContext : public FPayloadContextBase`  
_L80-97_
- inherits: `FPayloadContextBase`
- L83 _public prototype_ `virtual ~FAnimationPayloadContext() = default;`
- L84 _public function_ `virtual FString GetPayloadType() const override`
- L85 _public prototype_ `virtual bool FetchPayloadToFile(FFbxParser& Parser, const FString& PayloadFilepath) override;`
- L86 _public prototype_ `virtual bool FetchAnimationBakeTransformPayloadForTime(FFbxParser& Parser, const FbxTime Currenttime, FTransform& Out) override;`
- L87 _public prototype_ `virtual FbxAnimStack* GetAnimStack() override;`
- L89 _public member_ `TOptional<FNodeTransformFetchPayloadData> NodeTransformFetchPayloadData;`
- L90 _public member_ `TOptional<FAttributeFetchPayloadData> AttributeFetchPayloadData;`
- L91 _public member_ `TOptional<FAttributeNodeTransformFetchPayloadData> AttributeNodeTransformFetchPayloadData;`
- L92 _public member_ `TOptional<FMorphTargetFetchPayloadData> MorphTargetFetchPayloadData;`
- L94 _private prototype_ `bool InternalFetchCurveNodePayloadToFile(FFbxParser& Parser, const FString& PayloadFilepath);`
- L95 _private prototype_ `bool InternalFetchMorphTargetCurvePayloadToFile(FFbxParser& Parser, const FString& PayloadFilepath);`
- L96 _private prototype_ `bool InternalFetchMorphTargetCurvePayload(FFbxParser& Parser, TArray<FInterchangeCurve>& InterchangeCurves);`

#### class `UE::Interchange::Private::FFbxAnimation`  
`class FFbxAnimation`  
_L99-149_
- L103 _public prototype_ `static bool AddSkeletalTransformAnimation(UInterchangeBaseNodeContainer& NodeContainer , FbxScene* SDKScene , FFbxParser& Parser , FbxNode* Node , UInterchangeSceneNode* UnrealNode , TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts , UInterchangeSkeletalAnimationTrackNode* SkeletalAnimationTrackNode , const int32& AnimationIndex , bool bIsRootJoint);` — This function add the payload key if the scene node transform is animated.
- L114 _public prototype_ `static void AddNodeAttributeCurvesAnimation(FFbxParser& Parser , FbxNode* Node , FbxProperty& Property , FbxAnimCurveNode* AnimCurveNode , TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts , EFbxType PropertyType , TOptional<FString>& OutPayloadKey , TOptional<bool>& OutIsStepCurve);` — This function add the payload key for an animated node user attribute.
- L123 _public prototype_ `static void AddRigidTransformAnimation(FFbxParser& Parser , FbxNode* Node , const int32& AnimationIndex , FbxAnimCurveNode* TranslationCurveNode , FbxAnimCurveNode* RotationCurveNode , FbxAnimCurveNode* ScaleCurveNode , TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts , TOptional<FString>& OutPayloadKey);`
- L133 _public prototype_ `static void AddMorphTargetCurvesAnimation(FbxScene* SDKScene , FFbxParser& Parser , UInterchangeSkeletalAnimationTrackNode* SkeletalAnimationTrackNode , TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts , const FMorphTargetAnimationBuildingData& MorphTargetAnimationBuildingData);` — This function add the payload key for an animated curve for morph target.
- L139 _public prototype_ `static bool IsFbxPropertyTypeSupported(EFbxType PropertyType);`
- L140 _public prototype_ `static bool IsFbxPropertyTypeDecimal(EFbxType PropertyType);`
- L143 _public prototype_ `static bool FetchAnimationBakeTransformPayload(FFbxParser& Parser, FbxScene* SDKScene, TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts, const TArray<const UE::Interchange::FAnimationPayloadQuery*>& PayloadQueries, const FString& ResultFolder, FCriticalSection* ResultPayloadsCriticalSection, TAtomic<int64>& UniqueIdCounter, TMap<FString, FString>& ResultPayloads, TArray<FText>& OutErrorMessages);` — PayloadQueries arriving here should be of the same start/stop and frequency:

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Interchange` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxCamera.h` (Private)


#### class `UE::Interchange::Private::FFbxCamera`  
`class FFbxCamera`  
_L18-38_
- L21 _public function_ `explicit FFbxCamera(FFbxParser& InParser) : Parser(InParser)`
- L30 _public prototype_ `void AddAllCameras(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer);` — Create a UInterchangePhysicalCameraNode and add it to the NodeContainer for all FbxNodeAttributes of type eCamera that the fbx file contains. @note - Any node that already exist in the NodeContainer will not be created or modified.
- L33 _protected prototype_ `UInterchangePhysicalCameraNode* CreateCameraNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeUID, const FString& NodeName);`
- L34 _protected prototype_ `void AddCamerasRecursively(FbxNode* Node, UInterchangeBaseNodeContainer& NodeContainer);`
- L37 _private member_ `FFbxParser& Parser;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxConvert.h` (Private)


#### struct `UE::Interchange::Private::FFbxConvert`  
`struct FFbxConvert`  
_L14-222_
- L23 _public function_ `template<typename TransformType, typename VectorType, typename QuatType> static TransformType ConvertTransform(const FbxAMatrix& Matrix)` — Return a FTransform float or double
- L36 _public function_ `template<typename MatrixType> static MatrixType ConvertMatrix(const FbxAMatrix& Matrix)` — Return a FMatrix float or double
- L65 _public function_ `template<typename MatrixType> static FbxAMatrix ConvertMatrix(const MatrixType& UEMatrix)` — Take a FMatrix float or double and return a fbx affine matrix
- L94 _public function_ `template<typename QuatType> static QuatType ConvertRotToQuat(FbxQuaternion Quaternion)` — Return a FQuat float or double
- L107 _public function_ `template<typename RotatorType, typename VectorType> static RotatorType ConvertEuler(FbxDouble3 Euler)` — Return a FRotator float or double
- L114 _public function_ `template<typename VectorType> static VectorType ConvertScale(FbxVector4 Vector)` — Return a FVector float or double
- L126 _public function_ `template<typename RotatorType, typename QuatType> static RotatorType ConvertRotation(FbxQuaternion Quaternion)` — Return a FRotator float or double
- L134 _public function_ `template<typename VectorType> static VectorType ConvertPos(const FbxVector4& Vector)` — Return a FVector float or double
- L143 _public function_ `template<typename VectorType> static VectorType ConvertDir(const FbxVector4& Vector)` — Return a FVector float or double
- L150 _public prototype_ `static FLinearColor ConvertColor(const FbxDouble3& Color);`
- L152 _public prototype_ `static FTransform AdjustCameraTransform(const FTransform& Transform);`
- L153 _public prototype_ `static FTransform AdjustLightTransform(const FTransform& Transform);`
- L165 _public prototype_ `static void ConvertScene(FbxScene* SDKScene, const bool bConvertScene, const bool bForceFrontXAxis, const bool bConvertSceneUnit, FString& FileSystemDirection, FString& FileUnitSystem, FbxAMatrix& AxisConversionInverseMatrix, FbxAMatrix& JointOrientationMatrix);` — Convert a fbx scene
- L180 _public prototype_ `static FString MakeString(const ANSICHAR* Name);` — Convert UTF8 char to a FString using ANSI_TO_TCHAR macro
- L188 _private function_ `template<typename ScalarType> static void VerifyFiniteScalar(ScalarType& Value)`
- L197 _private function_ `template<typename VectorType> static void VerifyFiniteVector(VectorType& Value)`
- L206 _private function_ `template<typename QuatType> static void VerifyFiniteQuat(QuatType& Value)`
- L215 _private function_ `template<typename MatrixType> static void VerifyFiniteMatrix(MatrixType& Value)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Interchange` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxHelper.h` (Private)


#### class `UE::Interchange::Private::FPayloadContextBase`  
`class FPayloadContextBase`  
_L21-34_
- L24 _public prototype_ `virtual ~FPayloadContextBase() = default;`
- L25 _public function_ `virtual FString GetPayloadType() const`
- L26 _public function_ `virtual bool FetchPayloadToFile(FFbxParser& Parser, const FString& PayloadFilepath)`
- L27 _public function_ `virtual bool FetchMeshPayloadToFile(FFbxParser& Parser, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath)`
- L29 _public function_ `virtual bool FetchMeshPayload(FFbxParser& Parser, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData)`
- L31 _public function_ `virtual bool FetchAnimationBakeTransformPayloadForTime(FFbxParser& Parser, const FbxTime Currenttime, FTransform& Out)`
- L33 _public function_ `virtual FbxAnimStack* GetAnimStack()`

#### struct `UE::Interchange::Private::FFbxHelper`  
`struct FFbxHelper`  
_L36-76_
- L39 _public function_ `explicit FFbxHelper(bool bInKeepFbxNamespace) : bKeepFbxNamespace(bInKeepFbxNamespace)`
- L44 _public function_ `void Reset()`
- L45 _public prototype_ `FString GetMeshName(FbxGeometryBase* Mesh) const;`
- L46 _public prototype_ `FString GetMeshUniqueID(FbxGeometryBase* Mesh) const;`
- L48 _public prototype_ `FString GetNodeAttributeName(FbxNodeAttribute* NodeAttribute, const FStringView DefaultNamePrefix) const;`
- L49 _public prototype_ `FString GetNodeAttributeUniqueID(FbxNodeAttribute* NodeAttribute, const FStringView Prefix) const;`
- L54 _public prototype_ `FString GetFbxPropertyName(const FbxProperty& Property) const;` — Return the name of an FbxProperty, return empty string if the property is null.
- L59 _public prototype_ `FString GetFbxObjectName(const FbxObject* Object, bool bIsJoint = false) const;` — Return the name of an FbxObject, return empty string if the object is null.
- L66 _public prototype_ `FString GetFbxNodeHierarchyName(const FbxNode* Node) const;` — Return a string with the name of all the parent in the hierarchy separate by a dot( . ) from the fbx root node to the specified node. This is a way to have a valid unique ID for a fbx node that will be the same if the fbx change when we re-import. Using the fbx sdk int32 uniqueID is not valid anymore if the fbx is re-exported.
- L68 _public prototype_ `void ManageNamespace(FString& ObjectName) const;`
- L69 _public prototype_ `void ManageNamespaceAndRenameObject(FString& ObjectName, FbxObject* Object) const;`
- L71 _protected prototype_ `FString GetUniqueIDString(const uint64 UniqueID) const;`
- L74 _private member_ `mutable TMap<FString, const FbxObject*> MaterialNameClashMap;`
- L75 _private member_ `bool bKeepFbxNamespace;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L78 _prototype_ `void ProcessCustomAttribute(FFbxParser& Parser, UInterchangeBaseNode* UnrealNode, FbxProperty Property, const TOptional<FString>& PayloadKey = TOptional<FString>());` (scope `UE::Interchange::Private`)
- L81 _prototype_ `void ProcessCustomAttributes(FFbxParser& Parser, FbxObject* Object, UInterchangeBaseNode* UnrealNode);` (scope `UE::Interchange::Private`) — Without AnimationProcessing

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxInclude.h` (Private)


#### Free symbols / members of external scopes

- L17 _macro_ `#define TMP_UNFBX_BACKUP_O_RDONLY _O_RDONLY`
- L18 _macro_ `#define TMP_UNFBX_BACKUP_O_WRONLY _O_WRONLY`
- L40 _macro_ `#define FBX_DLL_MSC_VER 1600`
- L54 _macro_ `#define _O_RDONLY TMP_FBX_BACKUP_O_RDONLY`
- L55 _macro_ `#define _O_WRONLY TMP_FBX_BACKUP_O_WRONLY`

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxLight.h` (Private)


#### class `UE::Interchange::Private::FFbxLight`  
`class FFbxLight`  
_L18-38_
- L21 _public function_ `explicit FFbxLight(FFbxParser& InParser) : Parser(InParser)`
- L30 _public prototype_ `void AddAllLights(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer);` — Create a UInterchangeBaseLightNode and add it to the NodeContainer for all FbxNodeAttributes of type eLight the fbx file contains. @note - Any node that already exist in the NodeContainer will not be created or modified.
- L33 _protected prototype_ `UInterchangeBaseLightNode* CreateLightNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeUID, const FString& NodeName, const FbxLight& LightAttribute);`
- L34 _protected prototype_ `void AddLightsRecursively(FbxNode* Node, UInterchangeBaseNodeContainer& NodeContainer);`
- L37 _private member_ `FFbxParser& Parser;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxMaterial.h` (Private)


#### enum `UE::Interchange::Private::EBlendMode`  
`enum EBlendMode : int`  
_L25-39_
- desc: same enum as the one in EngineTypes, required because InterchangeWorker does not compile with Engine
- L27 _public enumerator_ `BLEND_Opaque`
- L28 _public enumerator_ `BLEND_Masked`
- L29 _public enumerator_ `BLEND_Translucent`
- L30 _public enumerator_ `BLEND_Additive`
- L31 _public enumerator_ `BLEND_Modulate`
- L32 _public enumerator_ `BLEND_AlphaComposite`
- L33 _public enumerator_ `BLEND_AlphaHoldout`
- L34 _public enumerator_ `BLEND_TranslucentColoredTransmittance`
- L35 _public enumerator_ `BLEND_MAX` — BLEND_TranslucentColoredTransmittance,  Substrate only
- L37 _public enumerator_ `BLEND_TranslucentGreyTransmittance = BLEND_Translucent` — Renamed blend modes. These blend modes are remapped onto legacy ones and kept hidden for not confusing users in legacy mode, while allowing to use the new blend mode names into code.
- L38 _public enumerator_ `BLEND_ColoredTransmittanceOnly = BLEND_Modulate` — BLEND_TranslucentGreyTransmittance = BLEND_Translucent,  Substrate only

#### class `UE::Interchange::Private::FFbxMaterial`  
`class FFbxMaterial`  
_L41-87_
- L44 _public function_ `explicit FFbxMaterial(FFbxParser& InParser) : Parser(InParser)`
- L53 _public prototype_ `void AddAllTextures(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer);` — Create a UInterchangeFextureNode and add it to the NodeContainer for each texture of type FbxFileTexture that the FBX file contains. @note - Any node that already exists in the NodeContainer will not be created or modified.
- L60 _public prototype_ `void AddAllMaterials(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer);` — Create a UInterchangeMaterialNode and add it to the NodeContainer for each material of type FbxSurfaceMaterial that the FBX file contains. @note - Any node that already exists in the NodeContainer will not be created or modified.
- L68 _public prototype_ `void AddAllNodeMaterials(UInterchangeSceneNode* SceneNode, FbxNode* ParentFbxNode, UInterchangeBaseNodeContainer& NodeContainer);` — Create a UInterchangeMaterialNode and add it to the NodeContainer for each material of type FbxSurfaceMaterial that the FBX ParentFbxNode contains. Also set the dependencies of the node materials on the Interchange ParentNode. @note - Any material node that already exists in the NodeContainer will be added as a dependency.
- L71 _protected prototype_ `UInterchangeMaterialInstanceNode* CreateMaterialInstanceNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeUID, const FString& NodeName);`
- L72 _protected prototype_ `const UInterchangeTexture2DNode* CreateTexture2DNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& TextureFilePath);`
- L73 _protected prototype_ `const UInterchangeTexture2DNode* CreateTexture2DNode(FbxFileTexture* FbxTexture, UInterchangeBaseNodeContainer& NodeContainer, UInterchangeMaterialInstanceNode* MaterialInstanceNode);`
- L74 _protected prototype_ `bool ConvertPropertyToMaterialInstanceNode(UInterchangeBaseNodeContainer& NodeContainer, UInterchangeMaterialInstanceNode* MaterialInstanceNode, FbxProperty& Property, float Factor, FName InputName, const TVariant<FLinearColor, float>& DefaultValue, bool bInverse = false);`
- L76 _protected prototype_ `void ConvertValuePropertyToMaterialInstanceNode(UInterchangeMaterialInstanceNode* MaterialInstanceNode, FbxProperty& Property, float Factor, FName InputName, const TVariant<FLinearColor, float>& DefaultValue, bool bInverse);`
- L79 _protected prototype_ `const UInterchangeTexture2DNode* ConvertTexturePropertyToMaterialInstanceNode(UInterchangeBaseNodeContainer& NodeContainer, UInterchangeMaterialInstanceNode* MaterialInstanceNode, FName InputName, FbxFileTexture* FbxTexture);`
- L84 _private prototype_ `const UInterchangeMaterialInstanceNode* AddMaterialInstanceNode(FbxSurfaceMaterial* SurfaceMaterial, UInterchangeBaseNodeContainer& NodeContainer);`
- L86 _private member_ `FFbxParser& Parser;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxMesh.h` (Private)


#### struct `UE::Interchange::Private::FFbxJointMeshBindPoseGenerator`  
`struct FFbxJointMeshBindPoseGenerator`  
_L26-37_
- desc: Helper to generate and cache per joint MeshIdToGlobalBindPose transforms.
- L28 _public member_ `TMap<const FbxNode*, TMap<FString, FMatrix>> JointToMeshIdToGlobalBindPoseReferenceMap;`
- L29 _public member_ `TMap<const FbxNode*, TMap<FString, FMatrix>> JointToMeshIdToGlobalBindPoseJointMap;`
- L30 _public member_ `TMap<const FbxNode*, FbxAMatrix> JointToBindPoseMap;`
- L32 _public prototype_ `FFbxJointMeshBindPoseGenerator(FbxScene* SDKScene, FFbxParser& Parser, const bool bConsiderClusterBeforePoseForMeshBindPose);`
- L34 _public prototype_ `TMap<FString, FMatrix>& GetMeshIdToGlobalBindPoseReferenceMap(const FbxNode* Joint);`
- L35 _public prototype_ `TMap<FString, FMatrix>& GetMeshIdToGlobalBindPoseJointMap(const FbxNode* Joint);`
- L36 _public prototype_ `FbxAMatrix GetBindPoseFbxAMatrix(const FbxNode* Joint, FbxAMatrix& DefaultValue);`

#### struct `UE::Interchange::Private::FMorphTargetAnimationBuildingData`  
`struct FMorphTargetAnimationBuildingData`  
_L39-100_
- L41 _public member_ `double StartTime;`
- L42 _public member_ `double StopTime;`
- L43 _public member_ `UInterchangeMeshNode* InterchangeMeshNode;`
- L44 _public member_ `int32 GeometryIndex;`
- L45 _public member_ `int32 AnimationIndex;`
- L46 _public member_ `FbxAnimLayer* AnimLayer;`
- L47 _public member_ `int32 MorphTargetIndex;`
- L48 _public member_ `int32 ChannelIndex;`
- L49 _public member_ `FString MorphTargetNodeUid;`
- L50 _public member_ `TArray<FString> InbetweenCurveNames;`
- L51 _public member_ `TArray<float> InbetweenFullWeights;`
- L53 _public function_ `FMorphTargetAnimationBuildingData(double InStartTime , double InStopTime , UInterchangeMeshNode* InInterchangeMeshNode , int32 InGeometryIndex , int32 InAnimationIndex , FbxAnimLayer* InAnimLayer , int32 InMorphTargetIndex , int32 InChannelIndex , FString InMorphTargetNodeUid) : StartTime(InStartTime) , StopTime(InStopTime) , InterchangeMeshNode(InInterchangeMeshNode) , GeometryIndex(InGeometryIndex) , AnimationIndex(InAnimationIndex) , AnimLayer(InAnimLayer) , MorphTargetIndex(InMorphTargetIndex) , ChannelIndex(InChannelIndex) , MorphTargetNodeUid(InMorphTargetNodeUid)`

#### class `UE::Interchange::Private::FMeshDescriptionImporter`  
`class FMeshDescriptionImporter`  
_L104-165_
- L107 _public prototype_ `FMeshDescriptionImporter(FFbxParser& InParser, FMeshDescription* InMeshDescription, FbxScene* InSDKScene, FbxGeometryConverter* InSDKGeometryConverter);`
- L112 _public prototype_ `bool FillStaticMeshDescriptionFromFbxMesh(FbxMesh* Mesh, const FTransform& MeshGlobalTransform);` — Fill the mesh description using the Mesh parameter.
- L117 _public prototype_ `bool FillSkinnedMeshDescriptionFromFbxMesh(FbxMesh* Mesh, const FTransform& MeshGlobalTransform, TArray<FString>& OutJointUniqueNames);` — Fill the mesh description using the Mesh parameter, and also fill the OutJointNodeUniqueIDs so the MeshDescription bone Index can be mapped to the correct Interchange joint scene node.
- L122 _public prototype_ `bool FillMeshDescriptionFromFbxShape(FbxShape* Shape, const FTransform& MeshGlobalTransform);` — Fill the mesh description using the Shape parameter.
- L128 _public function_ `template <typename T> T* AddMessage(FbxGeometryBase* FbxNode) const` — Add messages to the message log.
- L145 _private prototype_ `bool FillMeshDescriptionFromFbxMesh(FbxMesh* Mesh, const FTransform& MeshGlobalTransform, TArray<FString>& OutJointUniqueNames, EMeshType MeshType);`
- L146 _private prototype_ `bool IsOddNegativeScale(FbxAMatrix& TotalMatrix);`
- L149 _private function_ `float FbxGetBasisDeterminantSign(const FVector3f& XAxis, const FVector3f& YAxis, const FVector3f& ZAxis)` — TODO move the real function from RenderCore to FVector, so we do not have to add render core to compute such a simple thing
- L160 _private member_ `FFbxParser& Parser;`
- L161 _private member_ `FMeshDescription* MeshDescription;`
- L162 _private member_ `FbxScene* SDKScene;`
- L163 _private member_ `FbxGeometryConverter* SDKGeometryConverter;`
- L164 _private member_ `bool bInitialized = false;`

#### enum `UE::Interchange::Private::FMeshDescriptionImporter::EMeshType`  
`enum class EMeshType : uint8`  
_L138-143_
- L140 _public enumerator_ `None = 0` — No mesh type to import
- L141 _public enumerator_ `Static = 1` — static mesh
- L142 _public enumerator_ `Skinned = 2` — skinned mesh with joints

#### class `UE::Interchange::Private::FMeshPayloadContext`  
`class FMeshPayloadContext : public FPayloadContextBase`  
_L167-185_
- inherits: `FPayloadContextBase`
- L170 _public prototype_ `virtual ~FMeshPayloadContext() = default;`
- L171 _public function_ `virtual FString GetPayloadType() const override`
- L172 _public prototype_ `virtual bool FetchMeshPayloadToFile(FFbxParser& Parser, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath) override;`
- L174 _public prototype_ `virtual bool FetchMeshPayload(FFbxParser& Parser, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData) override;`
- L176 _public member_ `bool bIsSkinnedMesh = false;`
- L177 _public member_ `FbxMesh* Mesh = nullptr;`
- L178 _public member_ `FbxScene* SDKScene = nullptr;`
- L179 _public member_ `FbxGeometryConverter* SDKGeometryConverter = nullptr;`
- L181 _private prototype_ `bool FetchMeshPayloadInternal(FFbxParser& Parser , const FTransform& MeshGlobalTransform , FMeshDescription& OutMeshDescription , TArray<FString>& OutJointNames);`

#### class `UE::Interchange::Private::FMorphTargetPayloadContext`  
`class FMorphTargetPayloadContext : public FPayloadContextBase`  
_L187-203_
- inherits: `FPayloadContextBase`
- L190 _public prototype_ `virtual ~FMorphTargetPayloadContext() = default;`
- L191 _public function_ `virtual FString GetPayloadType() const override`
- L192 _public prototype_ `virtual bool FetchMeshPayloadToFile(FFbxParser& Parser, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath) override;`
- L194 _public prototype_ `virtual bool FetchMeshPayload(FFbxParser& Parser, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData) override;`
- L196 _public member_ `FbxShape* Shape = nullptr;`
- L197 _public member_ `FbxScene* SDKScene = nullptr;`
- L198 _public member_ `FbxGeometryConverter* SDKGeometryConverter = nullptr;`
- L200 _private prototype_ `bool FetchMeshPayloadInternal(FFbxParser& Parser , const FTransform& MeshGlobalTransform , FMeshDescription& OutMeshDescription);`

#### class `UE::Interchange::Private::FFbxMesh`  
`class FFbxMesh`  
_L205-228_
- L208 _public function_ `explicit FFbxMesh(FFbxParser& InParser) : Parser(InParser)`
- L212 _public prototype_ `void AddAllMeshes(FbxScene* SDKScene, FbxGeometryConverter* SDKGeometryConverter, UInterchangeBaseNodeContainer& NodeContainer, TMap<FString, TSharedPtr<FPayloadContextBase>>& PayloadContexts);`
- L213 _public prototype_ `static bool GetGlobalJointBindPoseTransform(FFbxParser* Parser, FbxScene* SDKScene, FbxNode* Joint, FFbxJointMeshBindPoseGenerator& FbxJointMeshBindPoseGenerator, FbxAMatrix& GlobalBindPoseJointMatrix, TMap<FString, FMatrix>& MeshIdToGlobalBindPoseJointMap, TMap<FString, FMatrix>& MeshIdToGlobalBindPoseReferenceMap, bool& bBadBindPoseMessageDisplay, const bool bIsOriginalJoint, const FbxAMatrix& JointOrientationMatrix);`
- L217 _public function_ `TArray<FMorphTargetAnimationBuildingData>& GetMorphTargetAnimationsBuildingData()`
- L220 _protected prototype_ `bool ExtractSkinnedMeshNodeJoints(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer, FbxMesh* Mesh, UInterchangeMeshNode* MeshNode);` — Add joints to the Interchange mesh node joint dependencies. Return false if there is no valid joint (not a valid skinned mesh).
- L221 _protected prototype_ `UInterchangeMeshNode* CreateMeshNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeName, const FString& NodeUniqueID);`
- L224 _private member_ `FFbxParser& Parser;`
- L227 _private member_ `TArray<FMorphTargetAnimationBuildingData> MorphTargetAnimationsBuildingData;` — In order to appropriately identify the Skeleton Node Uids we have to process the MorphTarget animations once the hierarchy is processed

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/FbxScene.h` (Private)


#### class `UE::Interchange::Private::FFbxScene`  
`class FFbxScene`  
_L28-109_
- L31 _public function_ `explicit FFbxScene(FFbxParser& InParser) : Parser(InParser)`
- L35 _public prototype_ `void AddHierarchy(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer, TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts);`
- L36 _public prototype_ `void AddAnimation(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer, TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts);`
- L37 _public prototype_ `void AddMorphTargetAnimations(FbxScene* SDKScene, UInterchangeBaseNodeContainer& NodeContainer, TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts, const TArray<FMorphTargetAnimationBuildingData>& MorphTargetAnimationsBuildingData);`
- L47 _protected prototype_ `void CreateMeshNodeReference(UInterchangeSceneNode* UnrealSceneNode, FbxNodeAttribute* NodeAttribute, UInterchangeBaseNodeContainer& NodeContainer, const FTransform& GeometricTransform, const FTransform& PivotNodeTransform);`
- L48 _protected prototype_ `void CreateCameraNodeReference(UInterchangeSceneNode* UnrealSceneNode, FbxNodeAttribute* NodeAttribute, UInterchangeBaseNodeContainer& NodeContainer);`
- L49 _protected prototype_ `void CreateLightNodeReference(UInterchangeSceneNode* UnrealSceneNode, FbxNodeAttribute* NodeAttribute, UInterchangeBaseNodeContainer& NodeContainer);`
- L51 _protected prototype_ `void AddHierarchyRecursively(UInterchangeSceneNode* UnrealParentNode , FbxNode* Node , FbxScene* SDKScene , UInterchangeBaseNodeContainer& NodeContainer , TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts , const TArray<FbxNode*>& ForceJointNodes , bool& bBadBindPoseMessageDisplay , FFbxJointMeshBindPoseGenerator& FbxJointMeshBindPoseGenerator);`
- L60 _protected prototype_ `void AddAnimationRecursively(FbxNode* Node , FbxScene* SDKScene , UInterchangeBaseNodeContainer& NodeContainer , TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts , UInterchangeSkeletalAnimationTrackNode* SkeletalAnimationTrackNode, bool SkeletalAnimationAddedToContainer , const FString& RootSceneNodeUid, const TSet<FString>& SkeletonRootNodeUids , const int32& AnimationIndex , const TArray<FbxNode*>& ForceJointNodes);`
- L70 _protected prototype_ `UInterchangeSceneNode* CreateUnrealSceneNode(UInterchangeSceneNode* UnrealParentNode , FbxNode* Node , FbxScene* SDKScene , UInterchangeBaseNodeContainer& NodeContainer , const TArray<FbxNode*>& ForceJointNodes , bool& bBadBindPoseMessageDisplay , FFbxJointMeshBindPoseGenerator& FbxJointMeshBindPoseGenerator);`
- L81 _private prototype_ `template<typename T> T* CreateUnrealSceneNodeInternal(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeName, const FString& NodeUID, const FString& ParentNodeUID);`
- L83 _private prototype_ `void AddRigidAnimation(FbxNode* Node , const FbxScene* SDKScene , const int32& AnimationIndex , const UInterchangeSceneNode* UnrealNode , UInterchangeBaseNodeContainer& NodeContainer , TMap<FString, TSharedPtr<FPayloadContextBase, ESPMode::ThreadSafe>>& PayloadContexts) const;`
- L90 _private prototype_ `void FillCommonJointRootNode(FbxScene* SDKScene, const TArray<FbxNode*>& ForceJointNodes);`
- L92 _private prototype_ `void ParseMesh(UInterchangeBaseNodeContainer& NodeContainer , UInterchangeSceneNode* UnrealNode , FbxNode* Node , FbxNodeAttribute* NodeAttribute);`
- L97 _private prototype_ `void ParseMeshLODs(UInterchangeMeshLODContainerNode& LODContainerNode , int32 LODIndex , FbxNode* Node , FbxScene* SDKScene , const FbxAMatrix& InvTransformMatrix );`
- L103 _private prototype_ `static FbxNode* Internal_GetRootSkeleton(FbxScene* SDKScene, FbxNode* Link, bool IsBlenderArmatureBone);`
- L104 _private prototype_ `static TArray<FbxNode*> FindForceJointNode(FbxScene* SDKScene);`
- L105 _private prototype_ `static bool IsValidBindPose(FbxScene* SDKScene, FbxNode* RootJoint);`
- L107 _private member_ `TMap<FbxNode*, FRootJointInfo> CommonJointRootNodes;`
- L108 _private member_ `FFbxParser& Parser;`

#### struct `UE::Interchange::Private::FFbxScene::FRootJointInfo`  
`struct FRootJointInfo`  
_L39-43_
- L41 _public function_ `FRootJointInfo(bool InValue) : bValidBindPose(InValue)`
- L42 _public member_ `const bool bValidBindPose;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Interchange` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxAnimation.h` (Private)


#### class `UE::Interchange::Private::FUfbxAnimation`  
`class FUfbxAnimation`  
_L23-43_
- L26 _public prototype_ `static void FetchSkinnedAnimation(ufbx_scene* Scene, const UE::Interchange::FAnimationPayloadQuery& PayloadQuery, const FSkeletalAnimationPayloadContext& SkeletalAnimationPayload, FAnimationPayloadData& PayloadData);`
- L27 _public prototype_ `static bool FetchMorphTargetAnimation(const FUfbxParser& Parser, const FMorphAnimationPayloadContext& Animation, TArray<FInterchangeCurve>& OutCurves);`
- L28 _public prototype_ `static bool FetchRigidAnimation(const FUfbxParser& Parser, const FRigidAnimationPayloadContext& Animation, TArray<FInterchangeCurve>& OutCurves);`
- L30 _public prototype_ `static bool FetchPropertyAnimationCurves(const FUfbxParser& Parser, const FPropertyAnimationPayloadContext& Animation, TArray<FInterchangeCurve>& OutCurves);`
- L31 _public prototype_ `static bool FetchPropertyAnimationStepCurves(const FUfbxParser& Parser, const FPropertyAnimationPayloadContext& Animation, TArray<FInterchangeStepCurve>& OutCurves);`
- L33 _public prototype_ `static void AddAnimation(FUfbxParser& Parser, FUfbxScene& Scene, const FUfbxMesh& Meshes, UInterchangeBaseNodeContainer& NodeContainer);`
- L35 _public prototype_ `static bool AddNodeAttributeCurvesAnimation(FUfbxParser& Parser , const FString NodeUid , const ufbx_prop& Prop , const ufbx_anim_value& AnimValue , TOptional<FString>& OutPayloadKey , TOptional<bool>& OutIsStepCurve , FString& OutCurveName);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxConvert.h` (Private)


#### struct `UE::Interchange::Private::Convert::FMeshNameAndUid`  
`struct FMeshNameAndUid`  
_L22-31_
- L24 _public prototype_ `FMeshNameAndUid(FUfbxParser& Parser, const ufbx_element& Mesh);`
- L26 _public function_ `FMeshNameAndUid(FUfbxParser& Parser, const ufbx_mesh& Mesh) : FMeshNameAndUid(Parser, Mesh.element)`
- L27 _public function_ `FMeshNameAndUid(FUfbxParser& Parser, const ufbx_blend_shape& Shape) : FMeshNameAndUid(Parser, Shape.element)`
- L29 _public member_ `FString Label;`
- L30 _public member_ `FString UniqueID;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Interchange` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L15 _namespace_ `namespace Convert` (scope `UE::Interchange::Private`)
- L17 _function_ `inline FString ToUnrealString(const ufbx_string& Src)` (scope `UE::Interchange::Private::Convert`)
- L33 _function_ `inline FVector2d ConvertVec2(const ufbx_vec2& V)` (scope `UE::Interchange::Private::Convert`)
- L38 _function_ `inline FVector2d ConvertUV(const ufbx_vec2& V)` (scope `UE::Interchange::Private::Convert`)
- L43 _function_ `inline FVector ConvertVec3(const ufbx_vec3& V)` (scope `UE::Interchange::Private::Convert`)
- L48 _function_ `inline FVector4d ConvertVec4(const ufbx_vec4& V)` (scope `UE::Interchange::Private::Convert`)
- L53 _function_ `inline FQuat ConvertQuat(const ufbx_quat& Q)` (scope `UE::Interchange::Private::Convert`)
- L58 _function_ `inline FLinearColor ConvertColor(const ufbx_vec4& Color)` (scope `UE::Interchange::Private::Convert`)
- L68 _function_ `inline FTransform ConvertTransform(const ufbx_transform& InTransform)` (scope `UE::Interchange::Private::Convert`)
- L79 _function_ `inline FMatrix ConvertMatrix(const ufbx_matrix& Matrix)` (scope `UE::Interchange::Private::Convert`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxMaterial.h` (Private)


#### class `UE::Interchange::Private::FUfbxMaterial`  
`class FUfbxMaterial`  
_L13-26_
- L16 _public function_ `explicit FUfbxMaterial(FUfbxParser& Parser) : Parser(Parser)`
- L21 _public prototype_ `void AddMaterials(UInterchangeBaseNodeContainer& NodeContainer);`
- L22 _public prototype_ `void AddAllTextures(UInterchangeBaseNodeContainer& NodeContainer);`
- L25 _private member_ `FUfbxParser& Parser;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxMesh.h` (Private)


#### class `UE::Interchange::Private::FUfbxMesh`  
`class FUfbxMesh`  
_L21-47_
- L24 _public function_ `explicit FUfbxMesh(FUfbxParser& InParser) : Parser(InParser)`
- L28 _public prototype_ `void AddAllMeshes(UInterchangeBaseNodeContainer& NodeContainer);`
- L30 _public prototype_ `static bool FetchMesh(FUfbxParser& Parser, FMeshDescription& MeshDescription, ufbx_element* Element, const FTransform& MeshGlobalTransform);`
- L31 _public prototype_ `static bool FetchSkinnedMesh(FUfbxParser& Parser, FMeshDescription& MeshDescription, ufbx_element* Element, const FTransform& MeshGlobalTransform, TArray<FString>& OutJointUniqueNames);`
- L32 _public prototype_ `static bool FetchBlendShape(FUfbxParser& Parser, FMeshDescription& MeshDescription, const ufbx_mesh& Mesh, const ufbx_blend_shape& BlendShape, const FTransform& MeshGlobalTransform);`
- L34 _public function_ `const TMap<const ufbx_blend_shape*, const ufbx_mesh*>& GetBlendShapes() const`
- L39 _public member_ `TMap<const ufbx_mesh*, UInterchangeMeshNode*> MeshToMeshNode;`
- L42 _private prototype_ `UInterchangeMeshNode* CreateMeshNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeDisplayLabel, const FString& NodeUniqueID);`
- L44 _private member_ `FUfbxParser& Parser;`
- L46 _private member_ `TMap<const ufbx_blend_shape*, const ufbx_mesh*> SkeletonRootPerBlendShape;`

#### Free symbols / members of external scopes

- L12 _typedef_ `struct ufbx_element;`
- L13 _typedef_ `struct ufbx_mesh;`
- L14 _typedef_ `struct ufbx_blend_shape;`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxParser.h` (Private)


#### struct `UE::Interchange::Private::FPayloadContext`  
`struct FPayloadContext`  
_L21-43_
- L34 _public prototype_ `FPayloadContext() = delete;`
- L35 _public function_ `FPayloadContext(const EKind InKind, const uint32 InIndex) : Kind(InKind) , Index(InIndex)`
- L41 _public member_ `EKind Kind;`
- L42 _public member_ `uint32 Index;`

#### enum `UE::Interchange::Private::FPayloadContext::EKind`  
`enum EKind`  
_L23-32_
- L25 _public enumerator_ `Element`
- L26 _public enumerator_ `SkinnedMesh`
- L27 _public enumerator_ `Morph`
- L28 _public enumerator_ `AnimationSkinned`
- L29 _public enumerator_ `AnimationMorph`
- L30 _public enumerator_ `AnimationRigid`
- L31 _public enumerator_ `AnimationProperty`

#### struct `UE::Interchange::Private::FMorph`  
`struct FMorph`  
_L45-49_
- L47 _public member_ `uint32 MeshElement;`
- L48 _public member_ `uint32 BlendShapeElement;`

#### struct `UE::Interchange::Private::FSkeletalAnimationPayloadContext`  
`struct FSkeletalAnimationPayloadContext`  
_L51-57_
- L53 _public member_ `FString NodeUid;`
- L54 _public member_ `int32 AnimStackIndex;`
- L55 _public member_ `int32 BakedNodeIndex;`
- L56 _public member_ `ufbx_shared_ptr<ufbx_baked_anim> BakedAnim;`

#### struct `UE::Interchange::Private::FMorphAnimationPayloadContext`  
`struct FMorphAnimationPayloadContext`  
_L59-68_
- L61 _public member_ `const ufbx_anim_curve* Curve;`
- L66 _public member_ `TArray<FString> InbetweenCurveNames;` — #ufbx_todo: In between blend shape animation support The count of the curve names should match the in between full weights
- L67 _public member_ `TArray<float> InbetweenFullWeights;`

#### struct `UE::Interchange::Private::FRigidAnimationPayloadContext`  
`struct FRigidAnimationPayloadContext`  
_L70-77_
- L73 _public member_ `const ufbx_node* Node = nullptr;` — Transform animation curves array in the order Interchange accepts it - Tx, Ty, Tz, Rx, Ry, Rz, Sx, Sy, Sz
- L74 _public member_ `const ufbx_anim_prop* TranslationProp = nullptr;`
- L75 _public member_ `const ufbx_anim_prop* RotationProp = nullptr;`
- L76 _public member_ `const ufbx_anim_prop* ScalingProp = nullptr;`

#### struct `UE::Interchange::Private::FPropertyAnimationPayloadContext`  
`struct FPropertyAnimationPayloadContext`  
_L79-84_
- L81 _public member_ `const ufbx_prop* Prop;`
- L82 _public member_ `const ufbx_anim_value* AnimValue;`
- L83 _public member_ `bool bIsStepAnimation;`

#### class `UE::Interchange::Private::FUfbxParser`  
`class FUfbxParser: public IFbxParser, public FNoncopyable`  
_L86-462_
- inherits: `IFbxParser,FNoncopyable`
- L89 _public prototype_ `explicit FUfbxParser(TWeakObjectPtr<UInterchangeResultsContainer> InResultsContainer);`
- L92 _public function_ `virtual const TCHAR* GetName() override`
- L94 _public function_ `virtual bool IsThreadSafe() override`
- L96 _public prototype_ `virtual void SetResultContainer(UInterchangeResultsContainer* Result) override;`
- L98 _public function_ `virtual void SetConvertSettings(const bool InbConvertScene, const bool InbForceFrontXAxis, const bool InbConvertSceneUnit, const bool InbKeepFbxNamespace, const bool InbConsiderClusterBeforePoseForMeshBindPose) override`
- L105 _public prototype_ `virtual bool LoadFbxFile(const FString& Filename, UInterchangeBaseNodeContainer& NodeContainer) override;`
- L108 _public prototype_ `virtual void FillContainerWithFbxScene(UInterchangeBaseNodeContainer& NodeContainer) override;` — Extract the fbx data from the sdk into our node container
- L111 _public prototype_ `virtual bool FetchPayloadData(const FString& PayloadKey, const FString& PayloadFilepath) override;` — Extract the fbx data from the sdk into our node container
- L114 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, const FString& PayloadFilepath) override;` — Extract the fbx mesh data from the sdk into our node container
- L116 _public prototype_ `virtual bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData) override;`
- L117 _public prototype_ `virtual bool FetchTexturePayload(const FString& PayloadKey, TOptional<TArray64<uint8>>& OutTexturePayloadData) override;`
- L123 _public prototype_ `virtual bool FetchAnimationBakeTransformPayload(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, const FString& ResultFolder, FCriticalSection* ResultPayloadsCriticalSection, TAtomic<int64>& UniqueIdCounter, TMap<FString, FString>& ResultPayloads ) override;` — Extract the fbx data from the sdk into our node container @Param PayloadQueries - Will be grouped based on their TimeDescription Hashes (so that we acquire the same timings in one iteration, avoiding cache rebuilds)
- L125 _public prototype_ `virtual void Reset() override;`
- L127 _public member_ `FString SourceFilename;`
- L128 _public member_ `TWeakObjectPtr<UInterchangeResultsContainer> ResultsContainer;`
- L135 _public function_ `template <typename T> T* AddMessage() const` — This function is used to add the given message object directly into the results for this operation.
- L144 _public function_ `void AddMessage(UInterchangeResult* Item) const`
- L157 _public prototype_ `FString GetElementNameRaw(const ufbx_element& Element) const;` — Get sanitized element name, not unique @param Element @param bIsJoint @return
- L165 _public prototype_ `FString GetElementName(const ufbx_element& Element) const;` — Returns name build for element making sure it's unique for each element - name based on sanitized name of the element so it can be used in any place when sanitized string is needed @param Element * @return
- L172 _public prototype_ `FString GetNodeName(const ufbx_node& Node) const;` — Get/Make "Name" of the node, unique(taking into account sanitized form) bu tnot sanitized(to keep namespace which contains colon), used to base Uid on, and set as a label(except bone nodes - they have different label, see @ref GetBoneNodeName) @param Node @return
- L173 _public prototype_ `FString GetNodeLabel(const ufbx_node& Node) const;`
- L174 _public prototype_ `FString GetNodeUid(const ufbx_node& Node) const;`
- L178 _public prototype_ `FString GetBoneNodeName(const ufbx_node& Node) const;` — Set name for the joint node, same name to be passed to UE::Interchange::FMeshPayloadData::JointNames when fetching the skinned mesh payload sanitized to replace underscore with dash
- L180 _public prototype_ `FString GetMeshUid(const ufbx_element& Node) const;`
- L181 _public prototype_ `FString GetMeshLabel(const ufbx_element& Mesh) const;`
- L183 _public prototype_ `FString GetMaterialName(const ufbx_material& Material) const;`
- L184 _public prototype_ `FString GetMaterialUid(const ufbx_material& Material) const;`
- L185 _public prototype_ `FString GetMaterialLabel(const ufbx_material& Material) const;`
- L187 _public function_ `FName GetMaterialSlotName(const ufbx_material* Material) const`
- L192 _public prototype_ `FString GetCameraName(const ufbx_camera& Camera) const;`
- L193 _public prototype_ `FString GetLightName(const ufbx_light& Light) const;`
- L195 _public prototype_ `static bool DoesTextureHaveAlpha(const FString& TextureFilename, const ufbx_texture& Texture);`
- L197 _public prototype_ `static void ConvertProperty(const ufbx_prop& Prop, UInterchangeBaseNode* SceneNode, const TOptional<FString>& PayloadKey = TOptional<FString>());`
- L199 _public member_ `ufbx_scene* Scene = nullptr;`
- L300 _public member_ `TMap<uint32_t, UInterchangeSceneNode*> ElementIdToSceneNode;`
- L301 _public member_ `FPayloadContexts PayloadContexts;`
- L447 _public member_ `bool bForceFrontXAxis = false;`
- L448 _public member_ `bool bKeepFbxNamespace = false;`
- L449 _public member_ `bool bConsiderClusterBeforePoseForMeshBindPose = false;`
- L452 _public member_ `FUniqueNames ElementNames;` — Unique names for elements by type, to base Label and Uid on
- L453 _public member_ `FUniqueNames NodeNames;`
- L454 _public member_ `FUniqueNames BoneNames;`
- L455 _public member_ `FUniqueNames MeshNames;`
- L456 _public member_ `FUniqueNames CameraNames;`
- L457 _public member_ `FUniqueNames LightNames;`
- L458 _public member_ `FUniqueNames MaterialNames;`
- L461 _public member_ `mutable TMap<const ufbx_node*, FString> NodeToUid;` — Cache of node Uids

#### struct `UE::Interchange::Private::FUfbxParser::FPayloadContexts`  
`struct FPayloadContexts`  
_L201-298_
- L203 _public function_ `void Reset()`
- L215 _public function_ `void Add(const FString& PayloadKey, const FPayloadContext& Payload)`
- L220 _public function_ `void Add(const FString& MorphTargetPayLoadKey, const FMorph& Morph)`
- L226 _public function_ `void Add(const FString& PayloadKey, const FSkeletalAnimationPayloadContext& Payload)`
- L232 _public function_ `void Add(const FString& PayloadKey, const FMorphAnimationPayloadContext& Payload)`
- L238 _public function_ `void Add(const FString& PayloadKey, const FRigidAnimationPayloadContext& Payload)`
- L244 _public function_ `void Add(const FString& PayloadKey, const FPropertyAnimationPayloadContext& Payload)`
- L250 _public function_ `bool Contains(const FString& PayloadKey)`
- L255 _public function_ `FPayloadContext* Find(const FString& PayloadKey)`
- L260 _public function_ `FMorph* GetMorph(const FPayloadContext* PayloadPtr)`
- L270 _public function_ `const FSkeletalAnimationPayloadContext& GetAnimation(const FPayloadContext& Payload)`
- L275 _public function_ `const FMorphAnimationPayloadContext& GetMorphAnimation(const FPayloadContext& Payload)`
- L280 _public function_ `const FRigidAnimationPayloadContext& GetRigidAnimation(const FPayloadContext& Payload)`
- L285 _public function_ `const FPropertyAnimationPayloadContext& GetPropertyAnimation(const FPayloadContext& Payload)`
- L290 _public member_ `TMap<FString, FPayloadContext> PayloadContexts;`
- L292 _public member_ `TArray<FMorph> MorphPayloads;`
- L294 _public member_ `TArray<FSkeletalAnimationPayloadContext> SkeletalAnimations;`
- L295 _public member_ `TArray<FMorphAnimationPayloadContext> MorphAnimations;`
- L296 _public member_ `TArray<FRigidAnimationPayloadContext> RigidAnimations;`
- L297 _public member_ `TArray<FPropertyAnimationPayloadContext> PropertyAnimations;`

#### struct `UE::Interchange::Private::FUfbxParser::FUniqueNames`  
`struct FUniqueNames`  
_L306-445_
- desc: Maintain map of elements unique names
- L308 _public function_ `FUniqueNames(const FUfbxParser& InParser) : Parser(InParser) , bUseNCL(true) , bUseNodeRules(false) , bIsJoint(false)`
- L324 _public function_ `FString MakeUniqueName(const ufbx_element& Element, const FString& BaseName) const` — Ensures that name is unique modulo sanitation. Although stored name may not be sanitized(Node name need to keep namespace which contains colon) still to pass Uid(based on Node name) to Interchange that Uid should dbe sanitized. @param Element @param BaseName @param bOverrideUseNCL whether to use '_ncl_' suffix when making unique name, or just add a number @return
- L378 _public function_ `void ManageNamespace(FString& ObjectName) const`
- L399 _public function_ `const FString* FindName(const ufbx_element& Element) const`
- L404 _public function_ `FString GetOrMake(const ufbx_element& Element, const TFunctionRef<FString()>& GetBaseName) const`
- L413 _public function_ `FString GetSafe(const ufbx_element& Element) const`
- L424 _public function_ `void Reset()`
- L431 _public member_ `mutable TSet<FString> NamesUsed;` — Unique sanitized name already in use
- L434 _public member_ `mutable TMap<const ufbx_element*, FString> ElementToName;` — Name (unique) registered for each element, maybe non-sanitized(e.g. for Nodes)! But having it sanitized should still produce unique
- L436 _public member_ `const FUfbxParser& Parser;`
- L438 _public member_ `bool bUseNCL;` — use "_ncl_" suffix to create uniques, followed by number, or just ""
- L440 _public member_ `bool bUseNodeRules;` — Keeping namespace name for nodes and generating unique names without removing namespace
- L442 _public member_ `FString DefaultName;` — Name to use when source base name is empty
- L444 _public member_ `bool bIsJoint;` — Joins have different rules for name sanitation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UFBX_NO_SKINNING_EVALUATION`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Interchange` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L331 _function_ `` (scope `UE::Interchange::Private::FUfbxParser::FUniqueNames::MakeUniqueName`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Private/Ufbx/UfbxScene.h` (Private)


#### class `UE::Interchange::Private::FUfbxScene`  
`class FUfbxScene`  
_L19-62_
- L22 _public prototype_ `explicit FUfbxScene(FUfbxParser& InParser);`
- L24 _public prototype_ `void InitHierarchy(UInterchangeBaseNodeContainer& NodeContainer);`
- L25 _public prototype_ `void ProcessNodes(UInterchangeBaseNodeContainer& NodeContainer);`
- L27 _public prototype_ `FString GetSkeletonRoot(ufbx_node* Node);`
- L28 _public prototype_ `bool IsInSkeleton(const ufbx_node& Node);`
- L31 _private prototype_ `void ProcessNode(UInterchangeBaseNodeContainer& NodeContainer, const ufbx_node& Node);`
- L32 _private prototype_ `FMatrix GetBindPoseMatrix(const ufbx_node& InNode);`
- L34 _private prototype_ `void ParseMeshLODs(UInterchangeMeshLODContainerNode& LODContainerNode, const ufbx_node& InNode, int32 LODIndex, const FMatrix& InvTransformMatrix );`
- L52 _private prototype_ `void InitHierarchyRecursively(TArray<UnrealNodeInfo>& OutNodeInfos, const ufbx_node& Node, const FString& ParentUid);`
- L54 _private member_ `FUfbxParser& Parser;`
- L56 _private member_ `TSet<const ufbx_node*> CommonJointRootNodes;`
- L57 _private member_ `TMap<const ufbx_node*, FString> SkeletonRootPerBone;`
- L59 _private member_ `TMap<const ufbx_node*, FMatrix> BindPose;`
- L60 _private member_ `TMap<const ufbx_node*, TMap<FString, FMatrix>> JointToMeshIdToGlobalBindPoseReferenceMap;`
- L61 _private member_ `TMap<const ufbx_node*, TMap<FString, FMatrix>> JointToMeshIdToGlobalBindPoseJointMap;`

#### struct `UE::Interchange::Private::FUfbxScene::UnrealNodeInfo`  
`struct UnrealNodeInfo`  
_L39-50_
- L41 _public member_ `const ufbx_node* Node;`
- L42 _public member_ `const FString Label;`
- L43 _public member_ `const FString UniqueId;`
- L44 _public member_ `const FString ParentUid;`
- L46 _public function_ `UnrealNodeInfo(const ufbx_node* InNode, const FString& InLabel, const FString& InUniqueId, const FString& InParentUid) : Node(InNode), Label(InLabel), UniqueId(InUniqueId), ParentUid(InParentUid)`

#### Free symbols / members of external scopes

- L11 _typedef_ `struct ufbx_node;`
- L12 _typedef_ `struct ufbx_mesh;`
- L13 _typedef_ `struct ufbx_blend_shape;`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Public/InterchangeFbxParser.h` (Public)


#### class `UE::Interchange::FInterchangeFbxParser`  
`class FInterchangeFbxParser`  
_L27-139_
- L30 _public prototype_ `FInterchangeFbxParser();`
- L31 _public prototype_ `~FInterchangeFbxParser();`
- L33 _public prototype_ `void ReleaseResources();`
- L35 _public prototype_ `const TCHAR* GetName();`
- L37 _public prototype_ `bool IsThreadSafe();`
- L39 _public prototype_ `void Reset(bool bInUseUfbxParser = false);`
- L41 _public prototype_ `void SetResultContainer(UInterchangeResultsContainer* Result);`
- L43 _public prototype_ `void SetConvertSettings(const bool InbConvertScene, const bool InbForceFrontXAxis, const bool InbConvertSceneUnit, const bool InbKeepFbxNamespace, const bool InbConsiderClusterBeforePoseForMeshBindPose);`
- L49 _public prototype_ `void LoadFbxFile(const FString& Filename, const FString& ResultFolder);` — Parse a file support by the fbx sdk. It just extract all the fbx node and create a FBaseNodeContainer and dump it in a json file inside the ResultFolder @param - Filename is the file that the fbx sdk will read (.fbx or .obj) @param - ResultFolder is the folder where we must put any result file
- L56 _public prototype_ `void LoadFbxFile(const FString& Filename, UInterchangeBaseNodeContainer& BaseNodecontainer);` — Parse a file support by the fbx sdk. It just extract all the fbx node and create a FBaseNodeContainer and dump it in a json file inside the ResultFolder @param - Filename is the file that the fbx sdk will read (.fbx or .obj) @param - BaseNodecontainer is the container of the scene graph
- L63 _public prototype_ `void FetchPayload(const FString& PayloadKey, const FString& ResultFolder);` — Extract payload data from the fbx, the key tell the translator what payload the client ask @param - PayloadKey is the key that describe the payload data to extract from the fbx file @param - ResultFolder is the folder where we must put any result file
- L72 _public prototype_ `FString FetchMeshPayload(const FString& PayloadKey, const FTransform& MeshGlobalTransform, const FString& ResultFolder);` — Extract mesh payload data from the fbx, the key tell the translator what payload the client ask @param - PayloadKey is the key that describe the payload data to extract from the fbx file @param - MeshGlobalTransform is the transform we want to apply to the mesh vertex @param - ResultFolder is the folder where we must put any result file @return - Return the 'ResultPayloads' key unique id. We cannot use only the payload key because the mesh global transform can be different.
- L81 _public prototype_ `bool FetchMeshPayload(const FString& PayloadKey, const FTransform& MeshGlobalTransform, FMeshPayloadData& OutMeshPayloadData);` — Extract mesh payload data from the fbx, the key tell the translator what payload the client ask @param - PayloadKey is the key that describe the payload data to extract from the fbx file @param - MeshGlobalTransform is the transform we want to apply to the mesh vertex @param - OutMeshPayloadData structure receiving the data
- L89 _public prototype_ `bool FetchTexturePayload(const FString& PayloadKey, TOptional<TArray64<uint8>>& OutTexturePayloadData);` — Retrieve image file contents for embedded textures @param PayloadKey @param OutTexturePayloadData @return
- L95 _public prototype_ `void FetchAnimationBakeTransformPayloads(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, const FString& ResultFolder);` — Extract bake transform animation payload data from the fbx
- L96 _public prototype_ `TMap<FString, FString> FetchAnimationBakeTransformPayloads(const FString& PayloadQueriesJsonString, const FString& ResultFolder);`
- L98 _public function_ `FString GetResultFilepath() const`
- L99 _public function_ `FString GetResultPayloadFilepath(const FString& PayloadKey) const`
- L112 _public prototype_ `TArray<FString> GetJsonLoadMessages() const;` — Transform the results container into an array of Json strings
- L115 _public function_ `template <typename T> T* AddMessage()`
- L125 _private prototype_ `UInterchangeResultsContainer* GetResultContainer() const;`
- L127 _private prototype_ `Private::IFbxParser* GetFbxParserPtr() const;`
- L128 _private prototype_ `Private::IFbxParser& GetFbxParser();`
- L130 _private member_ `TObjectPtr<UInterchangeResultsContainer> InternalResultsContainer = nullptr;`
- L131 _private member_ `TStrongObjectPtr<UInterchangeResultsContainer> ResultsContainer = nullptr;`
- L132 _private member_ `FString SourceFilename;`
- L133 _private member_ `FString ResultFilepath;`
- L134 _private member_ `mutable FCriticalSection ResultPayloadsCriticalSection;`
- L135 _private member_ `TMap<FString, FString> ResultPayloads;`
- L136 _private member_ `bool bUseUfbxParser = false;`
- L137 _private member_ `TUniquePtr<UE::Interchange::Private::IFbxParser> FbxParserPrivate;`
- L138 _private member_ `TAtomic<int64> UniqueIdCounter = 0;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Public/InterchangeFbxParserLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeFbxParser, Log, All)`

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Public/InterchangeFbxParserModule.h` (Public)


#### class `FInterchangeFbxParserModule`  
`class FInterchangeFbxParserModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: This module allows out-of-process Interchange translators in case a third-party SDK is not thread-safe.
- L14 _public prototype_ `static FInterchangeFbxParserModule& Get();`
- L15 _public prototype_ `static bool IsAvailable();`
- L18 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define INTERCHANGEFBXPARSER_MODULE_NAME TEXT("InterchangeFbxParser")`

### `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Public/InterchangeFbxSettings.h` (Public)


#### class `UInterchangeFbxSettings`  
`class UInterchangeFbxSettings : public UDeveloperSettings`  
_L18-34_
- reflection: `UCLASS(MinimalAPI, config = Interchange, meta = (DisplayName = "FBX Settings"))`
- inherits: `UDeveloperSettings`
- L24 _public prototype_ `UInterchangeFbxSettings();`
- L27 _public prototype_ `EInterchangePropertyTracks GetPropertyTrack(const FString& PropertyName) const;` — Search for a predefined property track, if the property has been found it returns it, otherwise we search for a custom property track
- L30 _public member_ `TMap<FString, EInterchangePropertyTracks > CustomPropertyTracks;` — `UPROPERTY(EditAnywhere, config, Category = "FBX | Property Tracks")`
- L33 _private member_ `TMap<FString, EInterchangePropertyTracks > PredefinedPropertyTracks;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEFBXPARSER_API`
