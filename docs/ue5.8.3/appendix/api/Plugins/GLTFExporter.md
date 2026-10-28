# Plugins / GLTFExporter

- module root: `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter`
- headers: 120; symbols: 1998
- symbol kinds: class=107, delegate=1, enum=20, enumerator=109, function=229, macro=70, member=583, namespace=3, prototype=691, struct=102, typedef=77, union=6
- PrivateDependencyModuleNames: Analytics, ContentBrowser, EditorStyle, EngineSettings, ImageWrapper, InputCore, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, Json, Landscape, LevelSequence, MainFrame, MaterialUtilities, MeshDescription, MeshMergeUtilities, MessageLog, MovieScene, MovieSceneTracks, Projects, PropertyEditor, RHI, RenderCore, SkeletalMeshDescription, Slate, SlateCore, StaticMeshDescription, ToolMenus, ToolWidgets, UnrealEd, VariantManagerContent
- PrivateIncludePathModuleNames: InterchangeImport
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MaterialBaking

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Actions/GLTFEditorStyle.h` (Private)


#### class `FGLTFEditorStyle`  
`class FGLTFEditorStyle : public FSlateStyleSet`  
_L14-39_
- inherits: `FSlateStyleSet`
- L18 _public function_ `FGLTFEditorStyle() : FSlateStyleSet("GLTFEditorStyle")`
- L29 _public function_ `virtual ~FGLTFEditorStyle() override`
- L34 _public function_ `static FGLTFEditorStyle& Get()`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Actions/GLTFProxyAssetActions.h` (Private)


#### class `FGLTFProxyAssetActions`  
`class FGLTFProxyAssetActions`  
_L12-27_
- L16 _public member_ `static FName MenuName;`
- L17 _public member_ `static FName SectionName;`
- L18 _public member_ `static FName EntryName;`
- L20 _public prototype_ `static void AddMenuEntry();`
- L21 _public prototype_ `static void RemoveMenuEntry();`
- L25 _private prototype_ `static void OnConstructMenu(FToolMenuSection& MenuSection);`
- L26 _private prototype_ `static void OnExecuteAction(const FToolMenuContext& MenuContext);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFBoneUtilities.h` (Private)


#### struct `FGLTFBoneUtilities`  
`struct FGLTFBoneUtilities`  
_L11-20_
- L13 _public prototype_ `static FTransform GetBindTransform(const FReferenceSkeleton& ReferenceSkeleton, int32 BoneIndex);`
- L15 _public prototype_ `static void GetBoneIndices(const FReferenceSkeleton& ReferenceSkeleton, TArray<FBoneIndexType>& OutBoneIndices);`
- L17 _public prototype_ `static void GetFrameTimestamps(const UAnimSequence* AnimSequence, TArray<float>& OutFrameTimestamps);`
- L19 _public prototype_ `static void GetBoneTransformsByFrame(const UObject* SkeletalMeshOrSkeleton, const UAnimSequence* AnimSequence, const TArray<FBoneIndexType>& BoneIndices, const TArray<float>& FrameTimestamps, TArray<TArray<FTransform>>& OutBoneTransformsByFrame);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFBufferAdapter.h` (Private)


#### class `IGLTFBufferAdapter`  
`class IGLTFBufferAdapter`  
_L14-30_
- L18 _public prototype_ `virtual ~IGLTFBufferAdapter() = default;`
- L20 _public prototype_ `virtual const uint8* GetData() = 0;`
- L22 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetIndices(const FRawStaticIndexBuffer* IndexBuffer);`
- L23 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetIndices(const FRawStaticIndexBuffer16or32Interface* IndexBuffer);`
- L24 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetPositions(const FPositionVertexBuffer* VertexBuffer);`
- L25 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetColors(const FColorVertexBuffer* VertexBuffer);`
- L26 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetTangents(const FStaticMeshVertexBuffer* VertexBuffer);`
- L27 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetUVs(const FStaticMeshVertexBuffer* VertexBuffer);`
- L28 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetInfluences(const FSkinWeightVertexBuffer* VertexBuffer);`
- L29 _public prototype_ `static TUniquePtr<IGLTFBufferAdapter> GetLookups(const FSkinWeightVertexBuffer* VertexBuffer);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFBufferUtilities.h` (Private)


#### struct `FGLTFBufferUtilities`  
`struct FGLTFBufferUtilities`  
_L17-30_
- L19 _public prototype_ `static bool HasCPUAccess(const FRawStaticIndexBuffer* IndexBuffer);`
- L20 _public prototype_ `static bool HasCPUAccess(const FRawStaticIndexBuffer16or32Interface* IndexBuffer);`
- L21 _public prototype_ `static bool HasCPUAccess(const FPositionVertexBuffer* VertexBuffer);`
- L22 _public prototype_ `static bool HasCPUAccess(const FColorVertexBuffer* VertexBuffer);`
- L23 _public prototype_ `static bool HasCPUAccess(const FStaticMeshVertexBuffer* VertexBuffer);`
- L24 _public prototype_ `static bool HasCPUAccess(const FSkinWeightVertexBuffer* VertexBuffer);`
- L26 _public prototype_ `static const void* GetCPUBuffer(const FRawStaticIndexBuffer* IndexBuffer);`
- L27 _public prototype_ `static const void* GetCPUBuffer(const FRawStaticIndexBuffer16or32Interface* IndexBuffer);`
- L29 _public prototype_ `static void ReadRHIBuffer(FRHIBuffer* SourceBuffer, TArray<uint8>& OutData);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFImageUtilities.h` (Private)


#### struct `FGLTFImageUtilities`  
`struct FGLTFImageUtilities`  
_L11-24_
- L13 _public prototype_ `static const TCHAR* GetFileExtension(EGLTFJsonMimeType MimeType);`
- L15 _public prototype_ `static FString GetUniqueFilename(const FString& BaseFilename, const FString& FileExtension, const TSet<FString>& UniqueFilenames);`
- L17 _public prototype_ `static bool NoAlphaNeeded(const FColor* Pixels, FIntPoint Size);`
- L19 _public prototype_ `static bool CompressToPNG(const FColor* InPixels, FIntPoint InSize, TArray64<uint8>& OutCompressedData);`
- L20 _public prototype_ `static bool CompressToJPEG(const FColor* InPixels, FIntPoint InSize, int32 InCompressionQuality, TArray64<uint8>& OutCompressedData);`
- L22 _public prototype_ `static bool CompressToFormat(const FColor* InPixels, FIntPoint InSize, EImageFormat InCompressionFormat, int32 InCompressionQuality, TArray64<uint8>& OutCompressedData);`
- L23 _public prototype_ `static bool CompressToFormat(const void* InRawData, int64 InRawSize, int32 InWidth, int32 InHeight, ERGBFormat InRGBFormat, int32 InBitDepth, EImageFormat InCompressionFormat, int32 InCompressionQuality, TArray64<uint8>& OutCompressedData);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFMaterialProxyFactory.h` (Private)


#### class `FGLTFMaterialProxyFactory`  
`class FGLTFMaterialProxyFactory`  
_L14-64_
- L18 _public prototype_ `FGLTFMaterialProxyFactory(const UGLTFProxyOptions* Options = nullptr);`
- L20 _public prototype_ `UMaterialInterface* Create(UMaterialInterface* OriginalMaterial);`
- L21 _public prototype_ `void OpenLog();`
- L23 _public member_ `FString RootPath;`
- L35 _private prototype_ `void SetBaseProperties(UMaterialInstanceConstant* ProxyMaterial, UMaterialInterface* OriginalMaterial);`
- L36 _private prototype_ `void SetProxyParameters(UMaterialInstanceConstant* ProxyMaterial, const FGLTFJsonMaterial& JsonMaterial);`
- L38 _private prototype_ `void SetProxyParameter(UMaterialInstanceConstant* ProxyMaterial, const TGLTFProxyMaterialParameterInfo<float>& ParameterInfo, float Scalar);`
- L39 _private prototype_ `void SetProxyParameter(UMaterialInstanceConstant* ProxyMaterial, const TGLTFProxyMaterialParameterInfo<FLinearColor>& ParameterInfo, const FGLTFJsonColor3& Color);`
- L40 _private prototype_ `void SetProxyParameter(UMaterialInstanceConstant* ProxyMaterial, const TGLTFProxyMaterialParameterInfo<FLinearColor>& ParameterInfo, const FGLTFJsonColor4& Color);`
- L41 _private prototype_ `void SetProxyParameter(UMaterialInstanceConstant* ProxyMaterial, const FGLTFProxyMaterialTextureParameterInfo& ParameterInfo, const FGLTFJsonTextureInfo& TextureInfo);`
- L43 _private prototype_ `UTexture2D* FindOrCreateTexture(FGLTFJsonTexture* JsonTexture, const FGLTFProxyMaterialTextureParameterInfo& ParameterInfo);`
- L44 _private prototype_ `UTexture2D* CreateTexture(const FGLTFImageData* ImageData, const FGLTFJsonSampler& JsonSampler, const FGLTFProxyMaterialTextureParameterInfo& ParameterInfo);`
- L46 _private prototype_ `UMaterialInstanceConstant* CreateInstancedMaterial(UMaterialInterface* OriginalMaterial, EGLTFJsonShadingModel ShadingModel);`
- L48 _private prototype_ `UPackage* FindOrCreatePackage(const FString& BaseName);`
- L50 _private prototype_ `TUniquePtr<IGLTFTexture2DConverter> CreateTextureConverter();`
- L51 _private prototype_ `TUniquePtr<IGLTFImageConverter> CreateImageConverter();`
- L53 _private prototype_ `static bool MakeDirectory(const FString& String);`
- L55 _private prototype_ `static UGLTFExportOptions* CreateExportOptions(const UGLTFProxyOptions* ProxyOptions);`
- L57 _private prototype_ `static TextureAddress ConvertWrap(EGLTFJsonTextureWrap Wrap);`
- L58 _private prototype_ `static TextureFilter ConvertFilter(EGLTFJsonTextureFilter Filter);`
- L60 _private member_ `FGLTFConvertBuilder Builder;`
- L62 _private member_ `TMap<FGLTFJsonTexture*, UTexture2D*> Textures;`
- L63 _private member_ `TMap<FGLTFJsonImage*, FGLTFImageData> Images;`

#### struct `FGLTFMaterialProxyFactory::FGLTFImageData`  
`struct FGLTFImageData`  
_L27-33_
- L29 _public member_ `FString Filename;`
- L30 _public member_ `bool bIgnoreAlpha;`
- L31 _public member_ `FIntPoint Size;`
- L32 _public member_ `TGLTFSharedArray<FColor> Pixels;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFMaterialUtilities.h` (Private)


#### struct `FGLTFPropertyBakeOutput`  
`struct FGLTFPropertyBakeOutput`  
_L16-36_
- L18 _public function_ `FGLTFPropertyBakeOutput(const TGLTFSharedArray<FColor>& Pixels, FIntPoint Size, float EmissiveScale, bool bSRGB) : Pixels(Pixels) , Size(Size) , EmissiveScale(EmissiveScale) , bIsConstant(Pixels->Num() == 1)`
- L31 _public member_ `TGLTFSharedArray<FColor> Pixels;`
- L32 _public member_ `FIntPoint Size;`
- L33 _public member_ `float EmissiveScale;`
- L34 _public member_ `bool bIsConstant;`
- L35 _public member_ `FLinearColor ConstantValue;`

#### struct `FGLTFMaterialUtilities`  
`struct FGLTFMaterialUtilities`  
_L38-99_
- L40 _public prototype_ `static UMaterialInterface* GetDefaultMaterial();`
- L42 _public prototype_ `static bool IsClearCoatBottomNormalEnabled();`
- L44 _public prototype_ `static EMaterialShadingModel GetRichestShadingModel(const FMaterialShadingModelField& ShadingModels);`
- L45 _public prototype_ `static FString ShadingModelsToString(const FMaterialShadingModelField& ShadingModels);`
- L47 _public prototype_ `static bool NeedsMeshData(const UMaterialInterface* Material);`
- L48 _public prototype_ `static bool NeedsMeshData(const TArray<const UMaterialInterface*>& Materials);`
- L50 _public prototype_ `static EMaterialShadingModel GetShadingModel(const UMaterialInterface* Material, FString& OutMessage);`
- L52 _public prototype_ `static TextureAddress ToTextureAddress(float Value);`
- L53 _public prototype_ `static float FromTextureWrap(EGLTFJsonTextureWrap Value);`
- L56 _public prototype_ `static bool IsNormalMap(const FMaterialPropertyEx& Property);`
- L57 _public prototype_ `static bool IsSRGB(const FMaterialPropertyEx& Property);`
- L59 _public prototype_ `static FGuid GetAttributeID(const FMaterialPropertyEx& Property);`
- L60 _public prototype_ `static FGuid GetAttributeIDChecked(const FMaterialPropertyEx& Property);`
- L62 _public prototype_ `static FVector4f GetPropertyDefaultValue(const FMaterialPropertyEx& Property);`
- L63 _public prototype_ `static FVector4f GetPropertyMask(const FMaterialPropertyEx& Property);`
- L65 _public prototype_ `static const FExpressionInput* GetInputForProperty(const UMaterialInterface* Material, const FMaterialPropertyEx& Property);`
- L68 _public function_ `template <class InputType> static const FMaterialInput<InputType>* GetInputForProperty(const UMaterialInterface* Material, const FMaterialPropertyEx& Property)`
- L74 _public prototype_ `static UMaterialExpressionCustomOutput* GetCustomOutputByName(const UMaterialInterface* Material, const FString& FunctionName);`
- L76 _public prototype_ `static FGLTFPropertyBakeOutput BakeMaterialProperty(const FIntPoint& OutputSize, const FMaterialPropertyEx& Property, const UMaterialInterface* Material, const FBox2f& TexCoordBounds, int32 TexCoordIndex, const FGLTFMeshData* MeshData, const FGLTFIndexArray& MeshSectionIndices, bool bFillAlpha, bool bAdjustNormalmaps);`
- L78 _public prototype_ `static FGLTFJsonTexture* AddTexture(FGLTFConvertBuilder& Builder, TGLTFSharedArray<FColor>& Pixels, const FIntPoint& TextureSize, bool bIgnoreAlpha, bool bIsNormalMap, const FString& TextureName, TextureAddress TextureAddress, TextureFilter TextureFilter);`
- L80 _public prototype_ `static FLinearColor GetMask(const FExpressionInput& ExpressionInput);`
- L81 _public prototype_ `static uint32 GetMaskComponentCount(const FExpressionInput& ExpressionInput);`
- L83 _public prototype_ `static bool TryGetMaxTextureSize(const UMaterialInterface* Material, const FMaterialPropertyEx& Property, FIntPoint& OutMaxSize);`
- L84 _public prototype_ `static bool TryGetMaxTextureSize(const UMaterialInterface* Material, const FMaterialPropertyEx& PropertyA, const FMaterialPropertyEx& PropertyB, FIntPoint& OutMaxSize);`
- L86 _public prototype_ `static UTexture* GetTextureFromSample(const UMaterialInterface* Material, const UMaterialExpressionTextureSample* SampleExpression);`
- L88 _public prototype_ `static bool TryGetTextureCoordinateIndex(const UMaterialExpressionTextureSample* TextureSample, int32& OutTexCoord, FGLTFJsonTextureTransform& OutTransform);`
- L89 _public prototype_ `static void GetAllTextureCoordinateIndices(const UMaterialInterface* Material, const FMaterialPropertyEx& Property, FGLTFIndexArray& OutTexCoords);`
- L91 _public prototype_ `static void AnalyzeMaterialProperty(const UMaterialInterface* Material, const FMaterialPropertyEx& InProperty, FMaterialAnalysisResult& OutAnalysis);`
- L93 _public prototype_ `static FMaterialShadingModelField EvaluateShadingModelExpression(const UMaterialInterface* Material);`
- L97 _private prototype_ `template<typename ExpressionType> static void GetAllInputExpressionsOfType(const UMaterialInterface* Material, const FMaterialPropertyEx& Property, TArray<ExpressionType*>& OutExpressions);`

#### struct `FGLTFImportMaterialMatchMakingHelper`  
`struct FGLTFImportMaterialMatchMakingHelper`  
_L103-122_
- desc: Helper used to identify Interchange - glTF Importer created materials. And then helps to acquire the Values set by the glTF Importer
- L105 _public member_ `TMap<FString, UMaterialExpression*> Inputs;`
- L106 _public member_ `FGLTFConvertBuilder& Builder;`
- L107 _public member_ `FGLTFJsonMaterial& JsonMaterial;`
- L108 _public member_ `const UMaterialInterface* Material;`
- L109 _public member_ `bool bMaterialInstance;` — uses Parameter acquisition approach if true, otherwise uses Inputs
- L110 _public member_ `bool bIsGLTFImportedMaterial;`
- L112 _public prototype_ `FGLTFImportMaterialMatchMakingHelper(FGLTFConvertBuilder& InBuilder, const UMaterialInterface* InMaterial, FGLTFJsonMaterial& InJsonMaterial);`
- L116 _public prototype_ `bool GetValue(const FString& InputKey, float& OutValue);`
- L117 _public prototype_ `bool GetValue(const FString& InputKey, FGLTFJsonColor3& OutValue);`
- L118 _public prototype_ `bool GetValue(const FString& InputKey, FGLTFJsonColor4& OutValue, bool HandleAsColor);`
- L119 _public prototype_ `bool GetValue(const FString& InputKey, FGLTFJsonTextureInfo& OutValue);`
- L121 _public prototype_ `void Process();`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFMeshUtilities.h` (Private)


#### struct `FGLTFMeshUtilities`  
`struct FGLTFMeshUtilities`  
_L19-59_
- L21 _public prototype_ `static void FullyLoad(const UStaticMesh* InStaticMesh);`
- L22 _public prototype_ `static void FullyLoad(const USkeletalMesh* InSkeletalMesh);`
- L24 _public prototype_ `static const UMaterialInterface* GetDefaultMaterial();`
- L26 _public prototype_ `static const TArray<FStaticMaterial>& GetMaterials(const UStaticMesh* StaticMesh);`
- L27 _public prototype_ `static const TArray<FSkeletalMaterial>& GetMaterials(const USkeletalMesh* SkeletalMesh);`
- L29 _public prototype_ `static const UMaterialInterface* GetMaterial(const UMaterialInterface* Material);`
- L30 _public prototype_ `static const UMaterialInterface* GetMaterial(const FStaticMaterial& Material);`
- L31 _public prototype_ `static const UMaterialInterface* GetMaterial(const FSkeletalMaterial& Material);`
- L33 _public prototype_ `static void ResolveMaterials(TArray<const UMaterialInterface*>& Materials, const UStaticMeshComponent* StaticMeshComponent, const UStaticMesh* StaticMesh);`
- L34 _public prototype_ `static void ResolveMaterials(TArray<const UMaterialInterface*>& Materials, const USkeletalMeshComponent* SkeletalMeshComponent, const USkeletalMesh* SkeletalMesh);`
- L35 _public prototype_ `static void ResolveMaterials(const UMaterialInterface*& LandscapeMaterial, const ULandscapeComponent* LandscapeComponent);`
- L38 _public prototype_ `template <typename MaterialType> static void ResolveMaterials(TArray<const UMaterialInterface*>& Materials, const TArray<MaterialType>& Defaults);`
- L39 _public prototype_ `static void ResolveMaterials(TArray<const UMaterialInterface*>& Materials, const UMaterialInterface* Default);`
- L41 _public prototype_ `static const FStaticMeshLODResources& GetRenderData(const UStaticMesh* StaticMesh, int32 LODIndex);`
- L42 _public prototype_ `static const FSkeletalMeshLODRenderData& GetRenderData(const USkeletalMesh* SkeletalMesh, int32 LODIndex);`
- L44 _public prototype_ `static FGLTFIndexArray GetSectionIndices(const UStaticMesh* StaticMesh, int32 LODIndex, int32 MaterialIndex);`
- L45 _public prototype_ `static FGLTFIndexArray GetSectionIndices(const USkeletalMesh* SkeletalMesh, int32 LODIndex, int32 MaterialIndex);`
- L47 _public prototype_ `static FGLTFIndexArray GetSectionIndices(const FStaticMeshLODResources& RenderData, int32 MaterialIndex);`
- L48 _public prototype_ `static FGLTFIndexArray GetSectionIndices(const FSkeletalMeshLODRenderData& RenderData, int32 MaterialIndex);`
- L50 _public prototype_ `static int32 GetLOD(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, int32 DefaultLOD);`
- L51 _public prototype_ `static int32 GetLOD(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, int32 DefaultLOD);`
- L52 _public prototype_ `static int32 GetLOD(const UStaticMesh* StaticMesh, const USplineMeshComponent* SplineMeshComponent, int32 DefaultLOD);`
- L54 _public prototype_ `static int32 GetMaximumLOD(const UStaticMesh* StaticMesh);`
- L55 _public prototype_ `static int32 GetMaximumLOD(const USkeletalMesh* SkeletalMesh);`
- L57 _public prototype_ `static int32 GetMinimumLOD(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent);`
- L58 _public prototype_ `static int32 GetMinimumLOD(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFNameUtilities.h` (Private)


#### struct `FGLTFNameUtilities`  
`struct FGLTFNameUtilities`  
_L10-21_
- L13 _public function_ `template <typename EnumType, typename = typename TEnableIf<TIsEnum<EnumType>::Value>::Type> static FString GetName(EnumType Value)`
- L18 _public prototype_ `static FString GetName(const UEnum* Enum, int32 Value);`
- L20 _public prototype_ `static FString GetName(const USceneComponent* Component);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFNormalMapPreview.h` (Private)


#### class `FGLTFNormalMapPreview`  
`class FGLTFNormalMapPreview : public FBatchedElementParameters`  
_L15-26_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for previewing normal maps.
- L18 _private prototype_ `virtual void BindShaders( FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFProxyMaterialCompiler.h` (Private)


#### class `FGLTFProxyMaterialCompiler`  
`class FGLTFProxyMaterialCompiler : public FProxyMaterialCompiler`  
_L10-186_
- inherits: `FProxyMaterialCompiler`
- L14 _public member_ `bool bUsesActorPosition = false;`
- L15 _public member_ `bool bUsesObjectPosition = false;`
- L16 _public member_ `bool bUsesObjectOrientation = false;`
- L17 _public member_ `bool bUsesObjectRadius = false;`
- L18 _public member_ `bool bUsesObjectBounds = false;`
- L19 _public member_ `bool bUsesObjectLocalBounds = false;`
- L20 _public member_ `bool bUsesPreSkinnedLocalBounds = false;`
- L21 _public member_ `bool bUsesCustomPrimitiveData = false;`
- L22 _public member_ `bool bUsesTransformVector = false;`
- L23 _public member_ `bool bUsesTransformPosition = false;`
- L25 _public function_ `bool UsesPrimitiveData() const`
- L41 _public function_ `virtual int32 ActorWorldPosition(EPositionOrigin OriginType) override`
- L47 _public function_ `virtual int32 ObjectWorldPosition(EPositionOrigin OriginType) override`
- L53 _public function_ `virtual int32 ObjectOrientation() override`
- L59 _public function_ `virtual int32 ObjectRadius() override`
- L65 _public function_ `virtual int32 ObjectBounds() override`
- L71 _public function_ `virtual int32 ObjectLocalBounds(int32 OutputIndex) override`
- L78 _public function_ `virtual int32 CustomExpression(class UMaterialExpressionCustom* Custom, int32 OutputIndex, TArray<int32>& CompiledInputs) override` — NOTE: also need to check old in-engine material function ObjectLocalBounds that bypasses the above override since it uses custom expressions
- L88 _public function_ `virtual int32 PreSkinnedLocalBounds(int32 OutputIndex) override`
- L94 _public function_ `virtual int32 CustomPrimitiveData(int32 OutputIndex, EMaterialValueType Type) override`
- L100 _public function_ `virtual int32 TransformVector(EMaterialCommonBasis SourceCoordBasis, EMaterialCommonBasis DestCoordBasis, FTransformParameters& Parameters, int32 A) override`
- L106 _public function_ `virtual int32 TransformPosition(EMaterialCommonBasis SourceCoordBasis, EMaterialCommonBasis DestCoordBasis, FTransformParameters& Parameters, int32 A) override`
- L112 _public function_ `virtual int32 GIReplace(int32 Direct, int32 StaticIndirect, int32 DynamicIndirect) override`
- L117 _public function_ `virtual int32 ShadowReplace(int32 Default, int32 Shadow) override`
- L122 _public function_ `virtual int32 RayTracingQualitySwitchReplace(int32 Normal, int32 RayTraced) override`
- L127 _public function_ `virtual int32 ReflectionCapturePassSwitch(int32 Default, int32 Reflection) override`
- L132 _public function_ `virtual int32 ReflectionAboutCustomWorldNormal(int32 CustomWorldNormal, int32 bNormalizeCustomWorldNormal) override`
- L137 _public function_ `virtual int32 ParticleRelativeTime() override`
- L142 _public function_ `virtual int32 ParticleMotionBlurFade() override`
- L147 _public function_ `virtual int32 ParticleRandom() override`
- L152 _public function_ `virtual int32 ParticleDirection() override`
- L157 _public function_ `virtual int32 ParticleSpeed() override`
- L162 _public function_ `virtual int32 ParticleSize() override`
- L167 _public function_ `virtual int32 ParticleSpriteRotation() override`
- L172 _public function_ `virtual int32 VertexInterpolator(uint32 InterpolatorIndex) override`
- L177 _public function_ `virtual int32 MaterialBakingWorldPosition() override`
- L182 _public function_ `virtual EMaterialCompilerType GetCompilerType() const override`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFSimpleTexture2DPreview.h` (Private)


#### class `FGLTFSimpleTexture2DPreview`  
`class FGLTFSimpleTexture2DPreview : public FBatchedElementParameters`  
_L8-19_
- inherits: `FBatchedElementParameters`
- L11 _private prototype_ `virtual void BindShaders( FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFTextureUtilities.h` (Private)


#### struct `FGLTFTextureUtilities`  
`struct FGLTFTextureUtilities`  
_L12-36_
- L14 _public prototype_ `static bool IsAlphaless(EPixelFormat PixelFormat);`
- L16 _public prototype_ `static void FullyLoad(const UTexture* InTexture);`
- L18 _public prototype_ `static bool Is2D(const UTexture* Texture);`
- L19 _public prototype_ `static bool IsCubemap(const UTexture* Texture);`
- L20 _public prototype_ `static bool IsHDR(const UTexture* Texture);`
- L22 _public prototype_ `static TextureFilter GetDefaultFilter(TextureGroup Group);`
- L24 _public prototype_ `static int32 GetMipBias(const UTexture* Texture);`
- L26 _public prototype_ `static FIntPoint GetInGameSize(const UTexture* Texture);`
- L28 _public prototype_ `static UTextureRenderTarget2D* CreateRenderTarget(const FIntPoint& Size, bool bIsHDR);`
- L30 _public prototype_ `static bool DrawTexture(UTextureRenderTarget2D* OutTarget, const UTexture2D* InSource);`
- L32 _public prototype_ `static bool ReadPixels(const UTextureRenderTarget2D* InRenderTarget, TArray<FColor>& OutPixels);`
- L34 _public prototype_ `static void FlipGreenChannel(TArray<FColor>& Pixels);`
- L35 _public prototype_ `static void TransformColorSpace(TArray<FColor>& Pixels, bool bFromSRGB, bool bToSRGB);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFVariantUtilities.h` (Private)


#### struct `FGLTFVariantUtilities`  
`struct FGLTFVariantUtilities`  
_L17-34_
- L20 _public function_ `template <typename T> static bool TryGetPropertyValue(UPropertyValue* Property, T& OutValue)`
- L25 _public prototype_ `static bool TryGetPropertyValue(UPropertyValue* Property, void* OutData, uint32 OutSize);`
- L27 _public prototype_ `static FString GetLogContext(const UPropertyValue* Property);`
- L28 _public prototype_ `static FString GetLogContext(const UVariantObjectBinding* Binding);`
- L29 _public prototype_ `static FString GetLogContext(const UVariant* Variant);`
- L30 _public prototype_ `static FString GetLogContext(const UVariantSet* VariantSet);`
- L31 _public prototype_ `static FString GetLogContext(const ULevelVariantSets* LevelVariantSets);`
- L33 _public prototype_ `static FGLTFJsonMaterial* AddUniqueMaterial(FGLTFConvertBuilder& Builder, const UMaterialInterface* Material, const UMeshComponent* MeshComponent, int32 MaterialIndex);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Exporters/GLTFExporterAnalytics.h` (Private)


#### struct `FGLTFExporterAnalytics`  
`struct FGLTFExporterAnalytics`  
_L11-32_
- L13 _public member_ `const UClass* AssetType;`
- L14 _public member_ `const UGLTFExportOptions* ExportOptions;`
- L15 _public member_ `bool bExportAsGLB;`
- L16 _public member_ `bool bSelectedOnly;`
- L17 _public member_ `bool bInitiatedByTask;`
- L18 _public member_ `bool bExportAutomated;`
- L19 _public member_ `bool bExportSuccessful;`
- L20 _public member_ `double ExportDuration;`
- L22 _public prototype_ `FGLTFExporterAnalytics(const UObject* Object, const FGLTFConvertBuilder& InBuilder, bool bInitiatedByTask, bool bExportAutomated, bool bExportSuccessful, uint64 StartTime);`
- L23 _public prototype_ `FGLTFExporterAnalytics(const UObject* Object, const FGLTFConvertBuilder& InBuilder, bool bInitiatedByTask, bool bExportAutomated, bool bExportSuccessful, uint64 StartTime, uint64 EndTime);`
- L25 _public prototype_ `void Send() const;`
- L28 _private member_ `const FGLTFConvertBuilder& Builder;`
- L30 _private prototype_ `static void GetAttributesFromStruct(const UStruct* Struct, const void* ContainerPtr, const FString& AttributeName, TArray<FAnalyticsEventAttribute>& OutAttributes);`
- L31 _private prototype_ `static void GetAttributesFromProperty(const FProperty* Property, const void* ValuePtr, const FString& AttributeName, TArray<FAnalyticsEventAttribute>& OutAttributes);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Exporters/GLTFExporterUtilities.h` (Private)


#### struct `FGLTFExporterUtilities`  
`struct FGLTFExporterUtilities`  
_L14-25_
- L16 _public prototype_ `static void GetSelectedActors(TSet<AActor*>& OutSelectedActors);`
- L18 _public prototype_ `static const UStaticMesh* GetPreviewMesh(const UMaterialInterface* Material);`
- L19 _public prototype_ `static const UStaticMesh* GetSphereMesh();`
- L21 _public prototype_ `static const USkeletalMesh* GetPreviewMesh(const UAnimSequence* AnimSequence);`
- L22 _public prototype_ `static const USkeletalMesh* FindCompatibleMesh(const USkeleton* Skeleton);`
- L24 _public prototype_ `static TArray<UWorld*> GetAssociatedWorlds(const UObject* Object);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Materials/GLTFProxyMaterialInfo.h` (Private)


#### class `FGLTFProxyMaterialInfo`  
`class FGLTFProxyMaterialInfo`  
_L9-62_
- L13 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo BaseColor;`
- L14 _public member_ `static const TGLTFProxyMaterialParameterInfo<FLinearColor> BaseColorFactor;`
- L16 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo Emissive;`
- L17 _public member_ `static const TGLTFProxyMaterialParameterInfo<FLinearColor> EmissiveFactor;`
- L18 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> EmissiveStrength;`
- L20 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo MetallicRoughness;`
- L21 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> MetallicFactor;`
- L22 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> RoughnessFactor;`
- L24 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo Normal;`
- L25 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> NormalScale;`
- L27 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo Occlusion;`
- L28 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> OcclusionStrength;`
- L30 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo ClearCoat;`
- L31 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> ClearCoatFactor;`
- L33 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo ClearCoatRoughness;`
- L34 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> ClearCoatRoughnessFactor;`
- L36 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo ClearCoatNormal;`
- L37 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> ClearCoatNormalScale;`
- L39 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> SpecularFactor;`
- L40 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo SpecularTexture;` — Only using Alpha Channel
- L42 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> IOR;`
- L44 _public member_ `static const TGLTFProxyMaterialParameterInfo<FLinearColor> SheenColorFactor;`
- L45 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo SheenColorTexture;` — RGB
- L46 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> SheenRoughnessFactor;`
- L47 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo SheenRoughnessTexture;` — A
- L49 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> TransmissionFactor;`
- L50 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo TransmissionTexture;` — Only using Red Channel
- L52 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> IridescenceFactor;`
- L53 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> IridescenceIOR;`
- L54 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo IridescenceTexture;`
- L55 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> IridescenceThicknessMinimum;`
- L56 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> IridescenceThicknessMaximum;`
- L57 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo IridescenceThicknessTexture;`
- L59 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> AnisotropyStrength;`
- L60 _public member_ `static const TGLTFProxyMaterialParameterInfo<float> AnisotropyRotation;`
- L61 _public member_ `static const FGLTFProxyMaterialTextureParameterInfo AnisotropyTexture;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Materials/GLTFProxyMaterialParameterInfo.h` (Private)


#### class `TGLTFProxyMaterialParameterInfo`  
`template <typename ParameterType> class TGLTFProxyMaterialParameterInfo`  
_L12-53_
- L16 _public function_ `TGLTFProxyMaterialParameterInfo(const FString& ParameterName) : ParameterInfo(*ParameterName)`
- L21 _public function_ `bool Get(const UMaterialInterface* Material, ParameterType& OutValue, bool NonDefaultOnly = false) const`
- L27 _public function_ `void Set(UMaterialInstanceConstant* Material, const ParameterType& Value, bool NonDefaultOnly = false) const`
- L33 _public function_ `FString ToString() const`
- L38 _public function_ `bool operator==(const TGLTFProxyMaterialParameterInfo<ParameterType>& Other) const`
- L45 _public function_ `bool operator!=(const TGLTFProxyMaterialParameterInfo<ParameterType>& Other) const`
- L52 _private member_ `FHashedMaterialParameterInfo ParameterInfo;`

#### class `FGLTFProxyMaterialTextureParameterInfo`  
`class FGLTFProxyMaterialTextureParameterInfo`  
_L55-85_
- L59 _public function_ `FGLTFProxyMaterialTextureParameterInfo(const FString& ParameterName) : Texture(ParameterName + TEXT(" Texture")) , UVIndex(ParameterName + TEXT(" UV Index")) , UVOffset(ParameterName + TEXT(" UV Offset")) , UVScale(ParameterName + TEXT(" UV Scale")) , UVRotation(ParameterName + TEXT(" UV Rotation")) , TilingMethod(ParameterName + TEXT(" Tiling Method"))`
- L69 _public function_ `bool operator==(const FGLTFProxyMaterialTextureParameterInfo& Other) const`
- L74 _public function_ `bool operator!=(const FGLTFProxyMaterialTextureParameterInfo& Other) const`
- L79 _public member_ `TGLTFProxyMaterialParameterInfo<UTexture*> Texture;`
- L80 _public member_ `TGLTFProxyMaterialParameterInfo<float> UVIndex;`
- L81 _public member_ `TGLTFProxyMaterialParameterInfo<FLinearColor> UVOffset;`
- L82 _public member_ `TGLTFProxyMaterialParameterInfo<FLinearColor> UVScale;`
- L83 _public member_ `TGLTFProxyMaterialParameterInfo<float> UVRotation;`
- L84 _public member_ `TGLTFProxyMaterialParameterInfo<FLinearColor> TilingMethod;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Tasks/GLTFDelayedAnimationTasks.h` (Private)


#### class `FGLTFDelayedAnimSequenceTask`  
`class FGLTFDelayedAnimSequenceTask : public FGLTFDelayedTask`  
_L10-38_
- inherits: `FGLTFDelayedTask`
- L14 _public function_ `FGLTFDelayedAnimSequenceTask(FGLTFConvertBuilder& Builder, FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, const UAnimSequence* AnimSequence, FGLTFJsonAnimation* JsonAnimation) : FGLTFDelayedTask(EGLTFTaskPriority::Animation) , Builder(Builder) , RootNode(RootNode) , SkeletalMesh(SkeletalMesh) , AnimSequence(AnimSequence) , JsonAnimation(JsonAnimation)`
- L24 _public function_ `virtual FString GetName() override`
- L29 _public prototype_ `virtual void Process() override;`
- L33 _private member_ `FGLTFConvertBuilder& Builder;`
- L34 _private member_ `FGLTFJsonNode* RootNode;`
- L35 _private member_ `const USkeletalMesh* SkeletalMesh;`
- L36 _private member_ `const UAnimSequence* AnimSequence;`
- L37 _private member_ `FGLTFJsonAnimation* JsonAnimation;`

#### class `FGLTFDelayedLevelSequenceTask`  
`class FGLTFDelayedLevelSequenceTask : public FGLTFDelayedTask`  
_L40-66_
- inherits: `FGLTFDelayedTask`
- L44 _public function_ `FGLTFDelayedLevelSequenceTask(FGLTFConvertBuilder& Builder, const ULevel* Level, const ULevelSequence* LevelSequence, FGLTFJsonAnimation* JsonAnimation) : FGLTFDelayedTask(EGLTFTaskPriority::Animation) , Builder(Builder) , Level(Level) , LevelSequence(LevelSequence) , JsonAnimation(JsonAnimation)`
- L53 _public function_ `virtual FString GetName() override`
- L58 _public prototype_ `virtual void Process() override;`
- L62 _private member_ `FGLTFConvertBuilder& Builder;`
- L63 _private member_ `const ULevel* Level;`
- L64 _private member_ `const ULevelSequence* LevelSequence;`
- L65 _private member_ `FGLTFJsonAnimation* JsonAnimation;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Tasks/GLTFDelayedMaterialTasks.h` (Private)


#### class `FGLTFDelayedMaterialTask`  
`class FGLTFDelayedMaterialTask : public FGLTFDelayedTask`  
_L18-116_
- inherits: `FGLTFDelayedTask`
- L22 _public function_ `FGLTFDelayedMaterialTask(FGLTFConvertBuilder& Builder, FGLTFUVOverlapChecker& UVOverlapChecker, FGLTFUVBoundsCalculator& UVBoundsCalculator, const UMaterialInterface* Material, const FGLTFMeshData* MeshData, FGLTFIndexArray& SectionIndices, FGLTFJsonMaterial* JsonMaterial) : FGLTFDelayedTask(EGLTFTaskPriority::Material) , Builder(Builder) , UVOverlapChecker(UVOverlapChecker) , UVBoundsCalculator(UVBoundsCalculator) , Material(Material) , MeshData(MeshData) , SectionIndices(SectionIndices) , JsonMaterial(JsonMaterial)`
- L34 _public function_ `virtual FString GetName() override`
- L39 _public prototype_ `virtual void Process() override;`
- L43 _private member_ `FGLTFConvertBuilder& Builder;`
- L44 _private member_ `FGLTFUVOverlapChecker& UVOverlapChecker;`
- L45 _private member_ `FGLTFUVBoundsCalculator& UVBoundsCalculator;`
- L46 _private member_ `const UMaterialInterface* Material;`
- L47 _private member_ `const FGLTFMeshData* MeshData;`
- L48 _private member_ `const FGLTFIndexArray SectionIndices;` — We copy because the received value can be temporary value.
- L49 _private member_ `FGLTFJsonMaterial* JsonMaterial;`
- L51 _private prototype_ `FString GetMaterialName() const;`
- L52 _private prototype_ `FString GetBakedTextureName(const FString& PropertyName) const;`
- L54 _private prototype_ `void GetProxyParameters(FGLTFJsonMaterial& OutMaterial) const;`
- L55 _private prototype_ `void GetProxyParameter(const TGLTFProxyMaterialParameterInfo<float>& ParameterInfo, float& OutValue) const;`
- L56 _private prototype_ `void GetProxyParameter(const TGLTFProxyMaterialParameterInfo<FLinearColor>& ParameterInfo, FGLTFJsonColor3& OutValue) const;`
- L57 _private prototype_ `void GetProxyParameter(const TGLTFProxyMaterialParameterInfo<FLinearColor>& ParameterInfo, FGLTFJsonColor4& OutValue) const;`
- L58 _private prototype_ `void GetProxyParameter(const FGLTFProxyMaterialTextureParameterInfo& ParameterInfo, FGLTFJsonTextureInfo& OutValue) const;`
- L61 _private function_ `template <typename ParameterType> bool HasProxyParameter(const TGLTFProxyMaterialParameterInfo<ParameterType>& ParameterInfo) const`
- L67 _private prototype_ `void ConvertShadingModel(EMaterialShadingModel& UEShadingModel, EGLTFJsonShadingModel& OutGLTFShadingModel) const;`
- L68 _private prototype_ `void ApplyExportOptionsToShadingModel(EGLTFJsonShadingModel& ShadingModel, const EMaterialShadingModel& UEMaterialShadingModel) const;`
- L70 _private prototype_ `void ConvertAlphaMode(EGLTFJsonAlphaMode& OutAlphaMode) const;`
- L73 _private member_ `TSet<FMaterialPropertyEx> MeshDataBakedProperties;`
- L75 _private prototype_ `bool TryGetBaseColorAndOpacity(FGLTFJsonPBRMetallicRoughness& OutPBRParams, const FMaterialPropertyEx& BaseColorProperty, const FMaterialPropertyEx& OpacityProperty);`
- L76 _private prototype_ `bool TryGetMetallicAndRoughness(FGLTFJsonPBRMetallicRoughness& OutPBRParams, const FMaterialPropertyEx& MetallicProperty, const FMaterialPropertyEx& RoughnessProperty);`
- L77 _private prototype_ `bool TryGetClearCoatRoughness(FGLTFJsonClearCoatExtension& OutExtParams, const FMaterialPropertyEx& IntensityProperty, const FMaterialPropertyEx& RoughnessProperty);`
- L78 _private prototype_ `bool TryGetEmissive(FGLTFJsonMaterial& OutMaterial, const FMaterialPropertyEx& EmissiveProperty);`
- L79 _private prototype_ `bool TryGetSpecular(FGLTFJsonMaterial& OutMaterial, const FMaterialPropertyEx& SpecularProperty);`
- L80 _private prototype_ `bool TryGetRefraction(FGLTFJsonMaterial& OutMaterial, const FMaterialPropertyEx& RefractionProperty);`
- L81 _private prototype_ `bool TryGetFuzzColorAndCloth(FGLTFJsonMaterial& OutMaterial, const FMaterialPropertyEx& FuzzColorProperty, const FMaterialPropertyEx& ClothProperty);`
- L82 _private prototype_ `bool TryGetTransmissionBaseColorAndOpacity(FGLTFJsonMaterial& OutMaterial, const FMaterialPropertyEx& BaseColorProperty, const FMaterialPropertyEx& OpacityProperty);`
- L84 _private prototype_ `bool IsPropertyNonDefault(const FMaterialPropertyEx& Property) const;`
- L85 _private prototype_ `bool TryGetConstantColor(FGLTFJsonColor3& OutValue, const FMaterialPropertyEx& Property) const;`
- L86 _private prototype_ `bool TryGetConstantColor(FGLTFJsonColor4& OutValue, const FMaterialPropertyEx& Property) const;`
- L87 _private prototype_ `bool TryGetConstantColor(FLinearColor& OutValue, const FMaterialPropertyEx& Property) const;`
- L88 _private prototype_ `bool TryGetConstantScalar(float& OutValue, const FMaterialPropertyEx& Property) const;`
- L90 _private prototype_ `bool TryGetSourceTexture(FGLTFJsonTextureInfo& OutTexInfo, const FMaterialPropertyEx& Property, const TArray<FLinearColor>& AllowedMasks = {}) const;`
- L91 _private prototype_ `bool TryGetSourceTexture(const UTexture2D*& OutTexture, int32& OutTexCoord, FGLTFJsonTextureTransform& OutTransform, const FMaterialPropertyEx& Property, const TArray<FLinearColor>& AllowedMasks = {}) const;`
- L93 _private prototype_ `bool TryGetBakedMaterialProperty(FGLTFJsonTextureInfo& OutTexInfo, FGLTFJsonColor3& OutConstant, const FMaterialPropertyEx& Property, const FString& PropertyName);`
- L94 _private prototype_ `bool TryGetBakedMaterialProperty(FGLTFJsonTextureInfo& OutTexInfo, FGLTFJsonColor4& OutConstant, const FMaterialPropertyEx& Property, const FString& PropertyName);`
- L95 _private prototype_ `bool TryGetBakedMaterialProperty(FGLTFJsonTextureInfo& OutTexInfo, float& OutConstant, const FMaterialPropertyEx& Property, const FString& PropertyName);`
- L96 _private prototype_ `bool TryGetBakedMaterialProperty(FGLTFJsonTextureInfo& OutTexInfo, const FMaterialPropertyEx& Property, const FString& PropertyName);`
- L99 _private prototype_ `template <typename CallbackType> bool TryGetBakedMaterialProperty(FGLTFJsonTextureInfo& Texture, float& Factor, const float& DefaultFactorValue, const FMaterialPropertyEx& Property, CallbackType Callback , const FString& TextureName = TEXT(""));`
- L101 _private prototype_ `FGLTFPropertyBakeOutput BakeMaterialProperty(const FMaterialPropertyEx& Property, int32& OutTexCoord, FGLTFJsonTextureTransform& OutTransform);`
- L102 _private prototype_ `FGLTFPropertyBakeOutput BakeMaterialProperty(const FMaterialPropertyEx& Property, int32& OutTexCoord, FGLTFJsonTextureTransform& OutTransform, const FIntPoint& TextureSize, bool bFillAlpha);`
- L104 _private prototype_ `bool StoreBakedPropertyTexture(const FMaterialPropertyEx& Property, FGLTFJsonTextureInfo& OutTexInfo, FGLTFPropertyBakeOutput& PropertyBakeOutput, const FString& PropertyName) const;`
- L106 _private prototype_ `FIntPoint GetBakeSize(const FMaterialPropertyEx& Property) const;`
- L107 _private prototype_ `FIntPoint GetBakeSize(const FMaterialPropertyEx& PropertyA,const FMaterialPropertyEx& PropertyB) const;`
- L109 _private prototype_ `static EGLTFMaterialPropertyGroup GetPropertyGroup(const FMaterialPropertyEx& Property);`
- L112 _private prototype_ `template <typename CallbackType> static void CombinePixels(const TArray<FColor>& FirstPixels, const TArray<FColor>& SecondPixels, TArray<FColor>& OutPixels, CallbackType Callback);`
- L115 _private prototype_ `bool HandleGLTFImported(const EMaterialShadingModel& UEMaterialShadingModel);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Tasks/GLTFDelayedMeshTasks.h` (Private)


#### class `FGLTFDelayedStaticAndSplineMeshTask`  
`class FGLTFDelayedStaticAndSplineMeshTask : public FGLTFDelayedTask`  
_L16-52_
- inherits: `FGLTFDelayedTask`
- L19 _public function_ `FGLTFDelayedStaticAndSplineMeshTask(FGLTFConvertBuilder& Builder, FGLTFStaticMeshSectionConverter& MeshSectionConverter, const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, const USplineMeshComponent* SplineMeshComponent, FGLTFMaterialArray& Materials, int32 LODIndex, FGLTFJsonMesh* JsonMesh) : FGLTFDelayedTask(EGLTFTaskPriority::Mesh) , Builder(Builder) , MeshSectionConverter(MeshSectionConverter) , StaticMesh(StaticMesh) , StaticMeshComponent(StaticMeshComponent) , SplineMeshComponent(SplineMeshComponent) , Materials(Materials) , LODIndex(LODIndex) , JsonMesh(JsonMesh)`
- L34 _public prototype_ `virtual FString GetName() override;`
- L36 _public prototype_ `virtual void Process() override;`
- L40 _private prototype_ `void ProcessMeshDescription(const TArray<FStaticMaterial>& MaterialSlots, const FGLTFMeshData* MeshData);`
- L42 _private prototype_ `void ProcessRenderData(const TArray<FStaticMaterial>& MaterialSlots, const FGLTFMeshData* MeshData);`
- L44 _private member_ `FGLTFConvertBuilder& Builder;`
- L45 _private member_ `FGLTFStaticMeshSectionConverter& MeshSectionConverter;`
- L46 _private member_ `const UStaticMesh* StaticMesh;`
- L47 _private member_ `const UStaticMeshComponent* StaticMeshComponent;`
- L48 _private member_ `const USplineMeshComponent* SplineMeshComponent;`
- L49 _private member_ `const FGLTFMaterialArray Materials;` — We copy because the received value can be temporary value.
- L50 _private member_ `const int32 LODIndex;`
- L51 _private member_ `FGLTFJsonMesh* JsonMesh;`

#### class `FGLTFDelayedStaticMeshTask`  
`class FGLTFDelayedStaticMeshTask : public FGLTFDelayedStaticAndSplineMeshTask`  
_L54-62_
- inherits: `FGLTFDelayedStaticAndSplineMeshTask`
- L58 _public function_ `FGLTFDelayedStaticMeshTask(FGLTFConvertBuilder& Builder, FGLTFStaticMeshSectionConverter& MeshSectionConverter, const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, FGLTFMaterialArray& Materials, int32 LODIndex, FGLTFJsonMesh* JsonMesh) : FGLTFDelayedStaticAndSplineMeshTask(Builder, MeshSectionConverter, StaticMesh, StaticMeshComponent, nullptr, Materials, LODIndex, JsonMesh)`

#### class `FGLTFDelayedSplineMeshTask`  
`class FGLTFDelayedSplineMeshTask : public FGLTFDelayedStaticAndSplineMeshTask`  
_L64-72_
- inherits: `FGLTFDelayedStaticAndSplineMeshTask`
- L68 _public function_ `FGLTFDelayedSplineMeshTask(FGLTFConvertBuilder& Builder, FGLTFStaticMeshSectionConverter& MeshSectionConverter, const UStaticMesh* StaticMesh, const USplineMeshComponent* SplineMeshComponent, FGLTFMaterialArray& Materials, int32 LODIndex, FGLTFJsonMesh* JsonMesh) : FGLTFDelayedStaticAndSplineMeshTask(Builder, MeshSectionConverter, StaticMesh, nullptr, SplineMeshComponent, Materials, LODIndex, JsonMesh)`

#### class `FGLTFDelayedSkeletalMeshTask`  
`class FGLTFDelayedSkeletalMeshTask : public FGLTFDelayedTask`  
_L74-107_
- inherits: `FGLTFDelayedTask`
- L78 _public function_ `FGLTFDelayedSkeletalMeshTask(FGLTFConvertBuilder& Builder, FGLTFSkeletalMeshSectionConverter& MeshSectionConverter, const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, FGLTFMaterialArray& Materials, int32 LODIndex, FGLTFJsonMesh* JsonMesh) : FGLTFDelayedTask(EGLTFTaskPriority::Mesh) , Builder(Builder) , MeshSectionConverter(MeshSectionConverter) , SkeletalMesh(SkeletalMesh) , SkeletalMeshComponent(SkeletalMeshComponent) , Materials(Materials) , LODIndex(LODIndex) , JsonMesh(JsonMesh)`
- L90 _public prototype_ `virtual FString GetName() override;`
- L92 _public prototype_ `virtual void Process() override;`
- L96 _private prototype_ `void ProcessSourceModel(const TArray<FSkeletalMaterial>& MaterialSlots, const FGLTFMeshData* MeshData);`
- L98 _private prototype_ `void ProcessRenderData(const TArray<FSkeletalMaterial>& MaterialSlots, const FGLTFMeshData* MeshData);`
- L100 _private member_ `FGLTFConvertBuilder& Builder;`
- L101 _private member_ `FGLTFSkeletalMeshSectionConverter& MeshSectionConverter;`
- L102 _private member_ `const USkeletalMesh* SkeletalMesh;`
- L103 _private member_ `const USkeletalMeshComponent* SkeletalMeshComponent;`
- L104 _private member_ `const FGLTFMaterialArray Materials;` — We copy because the received value can be temporary value.
- L105 _private member_ `const int32 LODIndex;`
- L106 _private member_ `FGLTFJsonMesh* JsonMesh;`

#### class `FGLTFDelayedLandscapeTask`  
`class FGLTFDelayedLandscapeTask : public FGLTFDelayedTask`  
_L109-125_
- inherits: `FGLTFDelayedTask`
- L113 _public prototype_ `FGLTFDelayedLandscapeTask(FGLTFConvertBuilder& Builder, const ULandscapeComponent& LandscapeComponent, FGLTFJsonMesh* JsonMesh, const UMaterialInterface& LandscapeMaterial);`
- L115 _public prototype_ `virtual FString GetName() override;`
- L117 _public prototype_ `virtual void Process() override;`
- L121 _private member_ `FGLTFConvertBuilder& Builder;`
- L122 _private member_ `const ULandscapeComponent& LandscapeComponent;`
- L123 _private member_ `FGLTFJsonMesh* JsonMesh;`
- L124 _private member_ `const UMaterialInterface& LandscapeMaterial;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Tasks/GLTFDelayedTextureTasks.h` (Private)


#### class `FGLTFDelayedTexture2DTask`  
`class FGLTFDelayedTexture2DTask : public FGLTFDelayedTask`  
_L8-35_
- inherits: `FGLTFDelayedTask`
- L12 _public function_ `FGLTFDelayedTexture2DTask(FGLTFConvertBuilder& Builder, const UTexture2D* Texture2D, bool bToSRGB, FGLTFJsonTexture* JsonTexture, TextureAddress InTextureAddressX, TextureAddress InTextureAddressY) : FGLTFDelayedTask(EGLTFTaskPriority::Texture) , Builder(Builder) , Texture2D(Texture2D) , bToSRGB(bToSRGB) , TextureAddressX(InTextureAddressX) , TextureAddressY(InTextureAddressY) , JsonTexture(JsonTexture)`
- L23 _public prototype_ `virtual FString GetName() override;`
- L25 _public prototype_ `virtual void Process() override;`
- L29 _private member_ `FGLTFConvertBuilder& Builder;`
- L30 _private member_ `const UTexture2D* Texture2D = nullptr;`
- L31 _private member_ `bool bToSRGB;`
- L32 _private member_ `TextureAddress TextureAddressX;`
- L33 _private member_ `TextureAddress TextureAddressY;`
- L34 _private member_ `FGLTFJsonTexture* JsonTexture = nullptr;`

#### class `FGLTFDelayedTextureRenderTarget2DTask`  
`class FGLTFDelayedTextureRenderTarget2DTask : public FGLTFDelayedTask`  
_L37-60_
- inherits: `FGLTFDelayedTask`
- L41 _public function_ `FGLTFDelayedTextureRenderTarget2DTask(FGLTFConvertBuilder& Builder, const UTextureRenderTarget2D* RenderTarget2D, bool bToSRGB, FGLTFJsonTexture* JsonTexture) : FGLTFDelayedTask(EGLTFTaskPriority::Texture) , Builder(Builder) , RenderTarget2D(RenderTarget2D) , bToSRGB(bToSRGB) , JsonTexture(JsonTexture)`
- L50 _public prototype_ `virtual FString GetName() override;`
- L52 _public prototype_ `virtual void Process() override;`
- L56 _private member_ `FGLTFConvertBuilder& Builder;`
- L57 _private member_ `const UTextureRenderTarget2D* RenderTarget2D = nullptr;`
- L58 _private member_ `bool bToSRGB;`
- L59 _private member_ `FGLTFJsonTexture* JsonTexture = nullptr;`

#### class `FGLTFDelayedTextureLightMapTask`  
`class FGLTFDelayedTextureLightMapTask : public FGLTFDelayedTask`  
_L64-85_
- inherits: `FGLTFDelayedTask`
- L68 _public function_ `FGLTFDelayedTextureLightMapTask(FGLTFConvertBuilder& Builder, const ULightMapTexture2D* LightMap, FGLTFJsonTexture* JsonTexture) : FGLTFDelayedTask(EGLTFTaskPriority::Texture) , Builder(Builder) , LightMap(LightMap) , JsonTexture(JsonTexture)`
- L76 _public prototype_ `virtual FString GetName() override;`
- L78 _public prototype_ `virtual void Process() override;`
- L82 _private member_ `FGLTFConvertBuilder& Builder;`
- L83 _private member_ `const ULightMapTexture2D* LightMap = nullptr;`
- L84 _private member_ `FGLTFJsonTexture* JsonTexture = nullptr;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/UI/GLTFExportOptionsWindow.h` (Private)


#### class `SGLTFExportOptionsWindow`  
`class SGLTFExportOptionsWindow : public SCompoundWidget`  
_L15-57_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SGLTFExportOptionsWindow) : _ExportOptions(nullptr) , _BatchMode()`
- L24 _public prototype_ `SLATE_ARGUMENT( UGLTFExportOptions*, ExportOptions ) SLATE_ARGUMENT( TSharedPtr<SWindow>, WidgetWindow ) SLATE_ARGUMENT( FText, FullPath ) SLATE_ARGUMENT( bool, BatchMode ) SLATE_END_ARGS() SGLTFExportOptionsWindow();`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `FReply OnReset() const;`
- L35 _public prototype_ `FReply OnExport();`
- L36 _public prototype_ `FReply OnExportAll();`
- L37 _public prototype_ `FReply OnCancel();`
- L40 _public function_ `virtual bool SupportsKeyboardFocus() const override` — Begin SCompoundWidget overrides
- L41 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L44 _public prototype_ `bool ShouldExport() const;`
- L45 _public prototype_ `bool ShouldExportAll() const;`
- L47 _public prototype_ `static void ShowDialog(UGLTFExportOptions* ExportOptions, const FString& FullPath, bool bBatchMode, bool& bOutOperationCanceled, bool& bOutExportAll);`
- L51 _private member_ `UGLTFExportOptions* ExportOptions;`
- L52 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L53 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L54 _private member_ `TSharedPtr<SButton> ExportButton;`
- L55 _private member_ `bool bShouldExport;`
- L56 _private member_ `bool bShouldExportAll;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/UI/GLTFMaterialBakeSizeCustomization.h` (Private)


#### class `FGLTFMaterialBakeSizeCustomization`  
`class FGLTFMaterialBakeSizeCustomization : public IPropertyTypeCustomization`  
_L18-44_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static void Register();`
- L23 _public prototype_ `static void Unregister();`
- L25 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _private prototype_ `FString GetSizeString() const;`
- L33 _private prototype_ `void SetSizeString(const FString& String) const;`
- L34 _private prototype_ `TSharedPtr<FString> GetSelectedOption() const;`
- L37 _private prototype_ `template <typename SetterType> void SetPropertyValue(SetterType Setter) const;`
- L40 _private prototype_ `template <typename ValueType, typename GetterType> bool TryGetPropertyValue(ValueType& OutValue, GetterType Getter) const;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L43 _private member_ `TArray<TSharedPtr<FString>> OptionsSource;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/UI/GLTFProxyOptionsWindow.h` (Private)


#### class `SGLTFProxyOptionsWindow`  
`class SGLTFProxyOptionsWindow : public SCompoundWidget`  
_L15-46_
- inherits: `SCompoundWidget`
- desc: Options window used to populate provided settings objects
- L19 _public function_ `SLATE_BEGIN_ARGS(SGLTFProxyOptionsWindow)`
- L21 _public prototype_ `SLATE_ARGUMENT( UGLTFProxyOptions*, ProxyOptions ) SLATE_ARGUMENT( TSharedPtr<SWindow>, WidgetWindow ) SLATE_END_ARGS() SGLTFProxyOptionsWindow();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `FReply OnConfirm();`
- L30 _public prototype_ `FReply OnCancel();`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override` — Begin SCompoundWidget overrides
- L34 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L37 _public prototype_ `static bool ShowDialog(UGLTFProxyOptions* ProxyOptions);`
- L41 _private member_ `UGLTFProxyOptions* ProxyOptions;`
- L42 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L43 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L44 _private member_ `TSharedPtr<SButton> ConfirmButton;`
- L45 _private member_ `bool bUserCancelled;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFAnalyticsBuilder.h` (Public)


#### class `FGLTFAnalyticsBuilder`  
`class FGLTFAnalyticsBuilder : public FGLTFBufferBuilder`  
_L23-60_
- inherits: `FGLTFBufferBuilder`
- L27 _public prototype_ `FGLTFAnalyticsBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions);`
- L29 _public prototype_ `TArray<FAnalyticsEventAttribute> GenerateAnalytics() const;`
- L33 _protected prototype_ `void RecordActor(const AActor* Object);`
- L34 _protected prototype_ `void RecordStaticMesh(const UStaticMesh* Object);`
- L35 _protected prototype_ `void RecordSkeletalMesh(const USkeletalMesh* Object);`
- L36 _protected prototype_ `void RecordSplineStaticMesh(const UStaticMesh* Object);`
- L37 _protected prototype_ `void RecordLandscapeComponent(const ULandscapeComponent* Object);`
- L38 _protected prototype_ `void RecordLevelSequence(const ULevelSequence* Object);`
- L39 _protected prototype_ `void RecordAnimSequence(const UAnimSequence* Object);`
- L40 _protected prototype_ `void RecordMaterial(const UMaterialInterface* Object);`
- L41 _protected prototype_ `void RecordTexture(const UTexture* Object);`
- L42 _protected prototype_ `void RecordCamera(const UCameraComponent* Object);`
- L43 _protected prototype_ `void RecordLight(const ULightComponent* Object);`
- L47 _private member_ `TSet<const AActor*> ActorsRecorded;`
- L48 _private member_ `TSet<const USceneComponent*> ComponentsRecorded;`
- L49 _private member_ `TSet<const UStaticMesh*> StaticMeshesRecorded;`
- L50 _private member_ `TSet<const USkeletalMesh*> SkeletalMeshesRecorded;`
- L51 _private member_ `TSet<const UStaticMesh*> SplineStaticMeshesRecorded;`
- L52 _private member_ `TSet<const ULandscapeComponent*> LandscapeComponentsRecorded;`
- L53 _private member_ `TSet<const ULevelSequence*> LevelSequencesRecorded;`
- L54 _private member_ `TSet<const UAnimSequence*> AnimSequencesRecorded;`
- L55 _private member_ `TSet<const UMaterialInterface*> MaterialsRecorded;`
- L56 _private member_ `TSet<const UTexture*> TexturesRecorded;`
- L58 _private member_ `TSet<const UCameraComponent*> CamerasRecorded;`
- L59 _private member_ `TSet<const ULightComponent*> LightsRecorded;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFBufferBuilder.h` (Public)


#### class `FGLTFBufferBuilder`  
`class FGLTFBufferBuilder : public FGLTFJsonBuilder`  
_L9-34_
- inherits: `FGLTFJsonBuilder`
- L13 _protected prototype_ `FGLTFBufferBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L14 _protected prototype_ `~FGLTFBufferBuilder();`
- L16 _protected prototype_ `const FGLTFMemoryArchive* GetBufferData() const;`
- L20 _public prototype_ `FGLTFJsonBufferView* AddBufferView(const void* RawData, uint64 ByteLength, EGLTFJsonBufferTarget BufferTarget = EGLTFJsonBufferTarget::None, uint8 DataAlignment = 4);`
- L23 _public function_ `template <class ElementType> FGLTFJsonBufferView* AddBufferView(const TArray<ElementType>& Array, EGLTFJsonBufferTarget BufferTarget = EGLTFJsonBufferTarget::None, uint8 DataAlignment = 4)`
- L30 _private prototype_ `void InitializeBuffer();`
- L32 _private member_ `FGLTFJsonBuffer* JsonBuffer;`
- L33 _private member_ `TSharedPtr<FGLTFMemoryArchive> BufferArchive;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFBuilder.h` (Public)


#### class `FGLTFBuilder`  
`class FGLTFBuilder`  
_L18-45_
- L22 _public member_ `const FString FileName;`
- L23 _public member_ `const bool bIsGLB;`
- L25 _public member_ `const UGLTFExportOptions* ExportOptions;` — TODO: make ExportOptions private and expose each option via getters to ease overriding settings in future
- L27 _public prototype_ `FGLTFBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L29 _public prototype_ `const UMaterialInterface* ResolveProxy(const UMaterialInterface* Material) const;`
- L30 _public prototype_ `void ResolveProxies(TArray<const UMaterialInterface*>& Materials) const;`
- L32 _public prototype_ `FGLTFMaterialBakeSize GetBakeSizeForMaterialProperty(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup) const;`
- L33 _public prototype_ `TextureFilter GetBakeFilterForMaterialProperty(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup) const;`
- L34 _public prototype_ `TextureAddress GetBakeTilingForMaterialProperty(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup) const;`
- L36 _public prototype_ `int32 SanitizeLOD(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex) const;`
- L37 _public prototype_ `int32 SanitizeLOD(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, int32 LODIndex) const;`
- L38 _public prototype_ `int32 SanitizeLOD(const UStaticMesh* StaticMesh, const USplineMeshComponent* SplineMeshComponent, int32 LODIndex) const;`
- L42 _private member_ `FGCObjectScopeGuard ExportOptionsGuard;`
- L44 _private prototype_ `static const UGLTFExportOptions* SanitizeExportOptions(const UGLTFExportOptions* Options);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFContainerBuilder.h` (Public)


#### class `FGLTFContainerBuilder`  
`class FGLTFContainerBuilder : public FGLTFConvertBuilder`  
_L9-38_
- inherits: `FGLTFConvertBuilder`
- L13 _public prototype_ `FGLTFContainerBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr, const TSet<AActor*>& SelectedActors = {});`
- L15 _public prototype_ `bool WriteInternalArchive(FArchive& Archive);`
- L17 _public prototype_ `bool WriteAllFiles(const FString& DirPath, uint32 WriteFlags = 0);`
- L18 _public prototype_ `bool WriteAllFiles(const FString& DirPath, TArray<FString>& OutFilePaths, uint32 WriteFlags = 0);`
- L20 _public prototype_ `void GetAllFiles(TArray<FString>& OutFilePaths, const FString& DirPath = TEXT("")) const;`
- L24 _protected prototype_ `bool WriteGlbArchive(FArchive& Archive);`
- L28 _private prototype_ `bool WriteGlb(FArchive& Archive, const TArray64<uint8>& JsonData, const TArray64<uint8>* BinaryData);`
- L30 _private prototype_ `static void WriteHeader(FArchive& Archive, uint32 FileSize);`
- L31 _private prototype_ `static void WriteChunk(FArchive& Archive, uint32 ChunkType, const TArray64<uint8>& ChunkData, uint8 PaddingValue);`
- L33 _private prototype_ `static void WriteInt(FArchive& Archive, uint32 Value);`
- L34 _private prototype_ `static void WriteData(FArchive& Archive, const TArray64<uint8>& Data);`
- L35 _private prototype_ `static void WriteFill(FArchive& Archive, uint32 Size, uint8 Value);`
- L37 _private prototype_ `static uint32 GetChunkPaddingLength(uint64 Size);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFConvertBuilder.h` (Public)


#### class `FGLTFConvertBuilder`  
`class FGLTFConvertBuilder : public FGLTFAnalyticsBuilder`  
_L28-181_
- inherits: `FGLTFAnalyticsBuilder`
- L32 _public member_ `const TSet<AActor*> SelectedActors;`
- L34 _public prototype_ `FGLTFConvertBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr, const TSet<AActor*>& SelectedActors = {});`
- L36 _public prototype_ `bool IsSelectedActor(const AActor* Object) const;`
- L37 _public prototype_ `bool IsRootActor(const AActor* Actor) const;`
- L39 _public prototype_ `FGLTFJsonAccessor* AddUniquePositionAccessor(const FGLTFMeshSection* MeshSection, const FPositionVertexBuffer* VertexBuffer);`
- L40 _public prototype_ `FGLTFJsonAccessor* AddUniquePositionDeltaAccessor(const FGLTFMeshSection* MeshSection, const TMap<uint32, FVector3f>* TargetPositionDeltas);`
- L41 _public prototype_ `FGLTFJsonAccessor* AddUniquePositionAccessor(const FGLTFPositionArray& VertexBuffer);`
- L42 _public prototype_ `FGLTFJsonAccessor* AddUniqueColorAccessor(const FGLTFMeshSection* MeshSection, const FColorVertexBuffer* VertexBuffer);`
- L43 _public prototype_ `FGLTFJsonAccessor* AddUniqueColorAccessor(const FGLTFColorArray& VertexColorBuffer);`
- L44 _public prototype_ `FGLTFJsonAccessor* AddUniqueNormalAccessor(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer);`
- L45 _public prototype_ `FGLTFJsonAccessor* AddUniqueNormalDeltaAccessor(const FGLTFMeshSection* MeshSection, const TMap<uint32, FVector3f>* TargetNormalDeltas, const bool& bHighPrecision);`
- L46 _public prototype_ `FGLTFJsonAccessor* AddUniqueNormalAccessor(const FGLTFNormalArray& Normals, const bool& bNormalize = true);`
- L47 _public prototype_ `FGLTFJsonAccessor* AddUniqueTangentAccessor(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer);`
- L48 _public prototype_ `FGLTFJsonAccessor* AddUniqueTangentAccessor(const FGLTFTangentArray& Tangents);`
- L49 _public prototype_ `FGLTFJsonAccessor* AddUniqueUVAccessor(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer, int32 UVIndex);`
- L50 _public prototype_ `FGLTFJsonAccessor* AddUniqueUVAccessor(const FGLTFUVArray& UVs);`
- L51 _public prototype_ `FGLTFJsonAccessor* AddUniqueJointAccessor(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, int32 InfluenceOffset);` — UE_API FGLTFJsonAccessor* AddUniqueUVAccessor(const FGLTFUVArray& UVs);   Supports single UV channel
- L52 _public prototype_ `FGLTFJsonAccessor* AddUniqueWeightAccessor(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, int32 InfluenceOffset);`
- L53 _public prototype_ `FGLTFJsonAccessor* AddUniqueJointAccessor(const FGLTFJointInfluenceArray& BoneIndices);`
- L54 _public prototype_ `FGLTFJsonAccessor* AddUniqueWeightAccessor(const FGLTFJointWeightArray& Weights);`
- L55 _public prototype_ `FGLTFJsonAccessor* AddUniqueIndexAccessor(const FGLTFMeshSection* MeshSection);`
- L56 _public prototype_ `FGLTFJsonAccessor* AddUniqueIndexAccessor(const FGLTFIndexArray& IndexBuffer, const FString& MeshName);`
- L58 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const UStaticMesh* StaticMesh, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L59 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const USkeletalMesh* SkeletalMesh, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L60 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const UMeshComponent* MeshComponent, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L61 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const UStaticMeshComponent* StaticMeshComponent, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L62 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const USkeletalMeshComponent* SkeletalMeshComponent, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L63 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const USplineMeshComponent* SplineMeshComponent, const FGLTFMaterialArray& Materials = {}, int32 LODIndex = INDEX_NONE);`
- L64 _public prototype_ `FGLTFJsonMesh* AddUniqueMesh(const ULandscapeComponent* LandscapeComponent, const UMaterialInterface* LandscapeMaterial = nullptr);`
- L66 _public prototype_ `const FGLTFMeshData* AddUniqueMeshData(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent = nullptr, int32 LODIndex = INDEX_NONE);`
- L67 _public prototype_ `const FGLTFMeshData* AddUniqueMeshData(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent = nullptr, int32 LODIndex = INDEX_NONE);`
- L69 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const UStaticMesh* StaticMesh, int32 LODIndex = INDEX_NONE, int32 MaterialIndex = INDEX_NONE);`
- L70 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const USkeletalMesh* SkeletalMesh, int32 LODIndex = INDEX_NONE, int32 MaterialIndex = INDEX_NONE);`
- L71 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const UMeshComponent* MeshComponent, int32 LODIndex = INDEX_NONE, int32 MaterialIndex = INDEX_NONE);`
- L72 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex = INDEX_NONE, int32 MaterialIndex = INDEX_NONE);`
- L73 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const USkeletalMeshComponent* SkeletalMeshComponent, int32 LODIndex = INDEX_NONE, int32 MaterialIndex = INDEX_NONE);`
- L74 _public prototype_ `FGLTFJsonMaterial* AddUniqueMaterial(const UMaterialInterface* Material, const FGLTFMeshData* MeshData = nullptr, const FGLTFIndexArray& SectionIndices = {});`
- L76 _public prototype_ `FGLTFJsonSampler* AddUniqueSampler(const UTexture* Texture);`
- L77 _public prototype_ `FGLTFJsonSampler* AddUniqueSampler(TextureAddress Address, TextureFilter Filter, TextureGroup LODGroup = TEXTUREGROUP_MAX);`
- L78 _public prototype_ `FGLTFJsonSampler* AddUniqueSampler(TextureAddress AddressX, TextureAddress AddressY, TextureFilter Filter, TextureGroup LODGroup = TEXTUREGROUP_MAX);`
- L80 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTexture* Texture);`
- L81 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTexture2D* Texture);`
- L82 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTextureRenderTarget2D* Texture);`
- L83 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTexture* Texture, bool bToSRGB, TextureAddress TextureAddressX = TextureAddress::TA_MAX, TextureAddress TextureAddressY = TextureAddress::TA_MAX);`
- L84 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTexture2D* Texture, bool bToSRGB, TextureAddress TextureAddressX, TextureAddress TextureAddressY);`
- L85 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const UTextureRenderTarget2D* Texture, bool bToSRGB);`
- L86 _public prototype_ `FGLTFJsonTexture* AddUniqueTexture(const ULightMapTexture2D* Texture);`
- L88 _public prototype_ `FGLTFJsonImage* AddUniqueImage(TGLTFSharedArray<FColor>& Pixels, FIntPoint Size, bool bIgnoreAlpha, const FString& Name);`
- L90 _public prototype_ `FGLTFJsonSkin* AddUniqueSkin(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh);`
- L91 _public prototype_ `FGLTFJsonSkin* AddUniqueSkin(FGLTFJsonNode* RootNode, const USkeletalMeshComponent* SkeletalMeshComponent);`
- L92 _public prototype_ `FGLTFJsonAnimation* AddUniqueAnimation(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, const UAnimSequence* AnimSequence);`
- L93 _public prototype_ `FGLTFJsonAnimation* AddUniqueAnimation(FGLTFJsonNode* RootNode, const USkeletalMeshComponent* SkeletalMeshComponent);`
- L94 _public prototype_ `FGLTFJsonAnimation* AddUniqueAnimation(const ULevel* Level, const ULevelSequence* LevelSequence);`
- L95 _public prototype_ `FGLTFJsonAnimation* AddUniqueAnimation(const ALevelSequenceActor* LevelSequenceActor);`
- L97 _public prototype_ `FGLTFJsonNode* AddUniqueNode(const AActor* Actor);`
- L98 _public prototype_ `FGLTFJsonNode* AddUniqueNode(const USceneComponent* SceneComponent);`
- L99 _public prototype_ `FGLTFJsonNode* AddUniqueNode(const USceneComponent* SceneComponent, FName SocketName);`
- L100 _public prototype_ `FGLTFJsonNode* AddUniqueNode(FGLTFJsonNode* RootNode, const UStaticMesh* StaticMesh, FName SocketName);`
- L101 _public prototype_ `FGLTFJsonNode* AddUniqueNode(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, FName SocketName);`
- L102 _public prototype_ `FGLTFJsonNode* AddUniqueNode(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, int32 BoneIndex);`
- L103 _public prototype_ `FGLTFJsonScene* AddUniqueScene(const UWorld* World);`
- L105 _public prototype_ `FGLTFJsonCamera* AddUniqueCamera(const UCameraComponent* CameraComponent);`
- L106 _public prototype_ `FGLTFJsonLight* AddUniqueLight(const ULightComponent* LightComponent);`
- L107 _public prototype_ `FGLTFJsonLightIES* AddUniqueLightIES(const ULightComponent* LightComponent);`
- L108 _public prototype_ `FGLTFJsonLightIESInstance* AddUniqueLightIESInstance(const ULightComponent* LightComponent);`
- L109 _public prototype_ `FGLTFJsonMaterialVariant* AddUniqueMaterialVariant(const UVariant* Variant);`
- L110 _public prototype_ `FGLTFJsonLightMap* AddUniqueLightMap(const UStaticMeshComponent* StaticMeshComponent);`
- L112 _public prototype_ `void RegisterObjectVariant(const UObject* Object, const UPropertyValue* Property);`
- L113 _public prototype_ `const TArray<const UPropertyValue*>* GetObjectVariants(const UObject* Object) const;`
- L116 _public member_ `TUniquePtr<IGLTFPositionBufferConverter> PositionBufferConverter = MakeUnique<FGLTFPositionBufferConverter>(*this);` — 'Original' converters:
- L117 _public member_ `TUniquePtr<IGLTFPositionDeltaBufferConverter> PositionDeltaBufferConverter = MakeUnique<FGLTFPositionDeltaBufferConverter>(*this);`
- L118 _public member_ `TUniquePtr<IGLTFColorBufferConverter> ColorBufferConverter = MakeUnique<FGLTFColorBufferConverter>(*this);`
- L119 _public member_ `TUniquePtr<IGLTFNormalBufferConverter> NormalBufferConverter = MakeUnique<FGLTFNormalBufferConverter>(*this);`
- L120 _public member_ `TUniquePtr<IGLTFNormalDeltaBufferConverter> NormalDeltaBufferConverter = MakeUnique<FGLTFNormalDeltaBufferConverter>(*this);`
- L121 _public member_ `TUniquePtr<IGLTFTangentBufferConverter> TangentBufferConverter = MakeUnique<FGLTFTangentBufferConverter>(*this);`
- L122 _public member_ `TUniquePtr<IGLTFUVBufferConverter> UVBufferConverter = MakeUnique<FGLTFUVBufferConverter>(*this);`
- L123 _public member_ `TUniquePtr<IGLTFBoneIndexBufferConverter> BoneIndexBufferConverter = MakeUnique<FGLTFBoneIndexBufferConverter>(*this);`
- L124 _public member_ `TUniquePtr<IGLTFBoneWeightBufferConverter> BoneWeightBufferConverter = MakeUnique<FGLTFBoneWeightBufferConverter>(*this);`
- L125 _public member_ `TUniquePtr<IGLTFIndexBufferConverter> IndexBufferConverter = MakeUnique<FGLTFIndexBufferConverter>(*this);`
- L128 _public member_ `TUniquePtr<IGLTFPositionBufferConverterRaw> PositionBufferConverterRaw = MakeUnique<FGLTFPositionBufferConverterRaw>(*this);` — Raw converters:
- L129 _public member_ `TUniquePtr<IGLTFColorBufferConverterRaw> ColorBufferConverterRaw = MakeUnique<FGLTFColorBufferConverterRaw>(*this);`
- L130 _public member_ `TUniquePtr<IGLTFNormalBufferConverterRaw> NormalBufferConverterRaw = MakeUnique<FGLTFNormalBufferConverterRaw>(*this);`
- L131 _public member_ `TUniquePtr<IGLTFTangentBufferConverterRaw> TangentBufferConverterRaw = MakeUnique<FGLTFTangentBufferConverterRaw>(*this);`
- L132 _public member_ `TUniquePtr<IGLTFUVBufferConverterRaw> UVBufferConverterRaw = MakeUnique<FGLTFUVBufferConverterRaw>(*this);`
- L133 _public member_ `TUniquePtr<IGLTFIndexBufferConverterRaw> IndexBufferConverterRaw = MakeUnique<FGLTFIndexBufferConverterRaw>(*this);`
- L134 _public member_ `TUniquePtr<IGLTFBoneIndexBufferConverterRaw> BoneIndexBufferConverterRaw = MakeUnique<FGLTFBoneIndexBufferConverterRaw>(*this);`
- L135 _public member_ `TUniquePtr<IGLTFBoneWeightBufferConverterRaw> BoneWeightBufferConverterRaw = MakeUnique<FGLTFBoneWeightBufferConverterRaw>(*this);`
- L138 _public member_ `TUniquePtr<IGLTFSplineMeshConverter> SplineMeshConverter = MakeUnique<FGLTFSplineMeshConverter>(*this);`
- L139 _public member_ `TUniquePtr<IGLTFLandscapeMeshConverter> LandscapeConverter = MakeUnique<FGLTFLandscapeMeshConverter>(*this);`
- L141 _public member_ `TUniquePtr<IGLTFStaticMeshConverter> StaticMeshConverter = MakeUnique<FGLTFStaticMeshConverter>(*this);`
- L142 _public member_ `TUniquePtr<IGLTFSkeletalMeshConverter> SkeletalMeshConverter = MakeUnique<FGLTFSkeletalMeshConverter>(*this);`
- L144 _public member_ `TUniquePtr<IGLTFMaterialConverter> MaterialConverter = MakeUnique<FGLTFMaterialConverter>(*this);`
- L145 _public member_ `TUniquePtr<IGLTFStaticMeshDataConverter> StaticMeshDataConverter = MakeUnique<FGLTFStaticMeshDataConverter>(*this);`
- L146 _public member_ `TUniquePtr<IGLTFSkeletalMeshDataConverter> SkeletalMeshDataConverter = MakeUnique<FGLTFSkeletalMeshDataConverter>(*this);`
- L148 _public member_ `TUniquePtr<IGLTFSamplerConverter> SamplerConverter = MakeUnique<FGLTFSamplerConverter>(*this);`
- L150 _public member_ `TUniquePtr<IGLTFTexture2DConverter> Texture2DConverter = MakeUnique<FGLTFTexture2DConverter>(*this);`
- L151 _public member_ `TUniquePtr<IGLTFTextureRenderTarget2DConverter> TextureRenderTarget2DConverter = MakeUnique<FGLTFTextureRenderTarget2DConverter>(*this);`
- L152 _public member_ `TUniquePtr<IGLTFImageConverter> ImageConverter = MakeUnique<FGLTFImageConverter>(*this);`
- L154 _public member_ `TUniquePtr<IGLTFSkinConverter> SkinConverter = MakeUnique<FGLTFSkinConverter>(*this);`
- L155 _public member_ `TUniquePtr<IGLTFAnimationConverter> AnimationConverter = MakeUnique<FGLTFAnimationConverter>(*this);`
- L156 _public member_ `TUniquePtr<IGLTFAnimationDataConverter> AnimationDataConverter = MakeUnique<FGLTFAnimationDataConverter>(*this);`
- L157 _public member_ `TUniquePtr<IGLTFLevelSequenceConverter> LevelSequenceConverter = MakeUnique<FGLTFLevelSequenceConverter>(*this);`
- L158 _public member_ `TUniquePtr<IGLTFLevelSequenceDataConverter> LevelSequenceDataConverter = MakeUnique<FGLTFLevelSequenceDataConverter>(*this);`
- L160 _public member_ `TUniquePtr<IGLTFActorConverter> ActorConverter = MakeUnique<FGLTFActorConverter>(*this);`
- L161 _public member_ `TUniquePtr<IGLTFComponentConverter> ComponentConverter = MakeUnique<FGLTFComponentConverter>(*this);`
- L162 _public member_ `TUniquePtr<IGLTFComponentSocketConverter> ComponentSocketConverter = MakeUnique<FGLTFComponentSocketConverter>(*this);`
- L163 _public member_ `TUniquePtr<IGLTFStaticSocketConverter> StaticSocketConverter = MakeUnique<FGLTFStaticSocketConverter>(*this);`
- L164 _public member_ `TUniquePtr<IGLTFSkeletalSocketConverter> SkeletalSocketConverter = MakeUnique<FGLTFSkeletalSocketConverter>(*this);`
- L165 _public member_ `TUniquePtr<IGLTFSkeletalBoneConverter> SkeletalBoneConverter = MakeUnique<FGLTFSkeletalBoneConverter>(*this);`
- L166 _public member_ `TUniquePtr<IGLTFSceneConverter> SceneConverter = MakeUnique<FGLTFSceneConverter>(*this);`
- L168 _public member_ `TUniquePtr<IGLTFCameraConverter> CameraConverter = MakeUnique<FGLTFCameraConverter>(*this);`
- L169 _public member_ `TUniquePtr<IGLTFLightConverter> LightConverter = MakeUnique<FGLTFLightConverter>(*this);`
- L170 _public member_ `TUniquePtr<IGLTFLightIESConverter> LightIESConverter = MakeUnique<FGLTFLightIESConverter>(*this);`
- L171 _public member_ `TUniquePtr<FGLTFLightIESInstanceConverter> LightIESInstanceConverter = MakeUnique<FGLTFLightIESInstanceConverter>(*this);`
- L172 _public member_ `TUniquePtr<IGLTFMaterialVariantConverter> MaterialVariantConverter = MakeUnique<FGLTFMaterialVariantConverter>(*this);`
- L175 _public member_ `TUniquePtr<IGLTFTextureLightMapConverter> TextureLightMapConverter = MakeUnique<FGLTFTextureLightMapConverter>(*this);` — LightMap related:
- L176 _public member_ `TUniquePtr<IGLTFLightMapConverter> LightMapConverter = MakeUnique<FGLTFLightMapConverter>(*this);`
- L180 _private member_ `TMap<const UObject*, TArray<const UPropertyValue*>> ObjectVariants;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFFileBuilder.h` (Public)


#### class `FGLTFFileBuilder`  
`class FGLTFFileBuilder : public FGLTFTaskBuilder`  
_L10-37_
- inherits: `FGLTFTaskBuilder`
- L14 _public prototype_ `FGLTFFileBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L16 _public prototype_ `FString AddExternalFile(const FString& DesiredURI, const TSharedPtr<FGLTFMemoryArchive>& Archive);`
- L18 _public prototype_ `void GetExternalFiles(TArray<FString>& OutFilePaths, const FString& DirPath = TEXT("")) const;`
- L20 _public prototype_ `const TMap<FString, TSharedPtr<FGLTFMemoryArchive>>& GetExternalArchives() const;`
- L22 _public prototype_ `bool WriteExternalFiles(const FString& DirPath, uint32 WriteFlags = 0);`
- L26 _private member_ `TMap<FString, TSharedPtr<FGLTFMemoryArchive>> ExternalArchives;`
- L28 _private prototype_ `FString GetUniqueFileName(const FString& InFileName) const;`
- L30 _private prototype_ `static FString SanitizeFileName(const FString& InFileName);`
- L32 _private prototype_ `static FString EncodeURI(const FString& InFileName);`
- L36 _protected prototype_ `bool SaveToFile(const FString& FilePath, const TArray64<uint8>& FileData, uint32 WriteFlags);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFJsonBuilder.h` (Public)


#### class `FGLTFJsonBuilder`  
`class FGLTFJsonBuilder : public FGLTFFileBuilder`  
_L10-53_
- inherits: `FGLTFFileBuilder`
- L14 _public member_ `FGLTFJsonScene*& DefaultScene;`
- L16 _public prototype_ `FGLTFJsonBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L18 _public prototype_ `void AddExtension(EGLTFJsonExtension Extension, bool bIsRequired = false);`
- L20 _public prototype_ `FGLTFJsonAccessor* AddAccessor();`
- L21 _public prototype_ `FGLTFJsonAnimation* AddAnimation();`
- L22 _public prototype_ `FGLTFJsonBuffer* AddBuffer();`
- L23 _public prototype_ `FGLTFJsonBufferView* AddBufferView();`
- L24 _public prototype_ `FGLTFJsonCamera* AddCamera();`
- L25 _public prototype_ `FGLTFJsonImage* AddImage();`
- L26 _public prototype_ `FGLTFJsonMaterial* AddMaterial();`
- L27 _public prototype_ `FGLTFJsonMesh* AddMesh();`
- L28 _public prototype_ `FGLTFJsonNode* AddNode();`
- L29 _public prototype_ `FGLTFJsonSampler* AddSampler();`
- L30 _public prototype_ `FGLTFJsonScene* AddScene();`
- L31 _public prototype_ `FGLTFJsonSkin* AddSkin();`
- L32 _public prototype_ `FGLTFJsonTexture* AddTexture();`
- L33 _public prototype_ `FGLTFJsonLight* AddLight();`
- L34 _public prototype_ `FGLTFJsonLightMap* AddLightMap();`
- L35 _public prototype_ `FGLTFJsonLightIES* AddLightIES();`
- L36 _public prototype_ `FGLTFJsonLightIESInstance* AddLightIESInstance();`
- L37 _public prototype_ `FGLTFJsonMaterialVariant* AddMaterialVariant();`
- L39 _public prototype_ `const FGLTFJsonRoot& GetRoot() const;`
- L43 _protected prototype_ `bool WriteJsonArchive(FArchive& Archive);`
- L47 _private prototype_ `static FString GetGeneratorString();`
- L48 _private prototype_ `static FString GetCopyrightString();`
- L50 _private member_ `FGLTFJsonRoot JsonRoot;`
- L52 _private prototype_ `void ValidateAndFixGLTFJson();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFLogBuilder.h` (Public)


#### class `FGLTFLogBuilder`  
`class FGLTFLogBuilder : public FGLTFBuilder`  
_L13-55_
- inherits: `FGLTFBuilder`
- L17 _public prototype_ `FGLTFLogBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L19 _public prototype_ `void LogSuggestion(const FString& Message);`
- L21 _public prototype_ `void LogWarning(const FString& Message);`
- L23 _public prototype_ `void LogError(const FString& Message);`
- L25 _public prototype_ `const TArray<FString>& GetLoggedSuggestions() const;`
- L27 _public prototype_ `const TArray<FString>& GetLoggedWarnings() const;`
- L29 _public prototype_ `const TArray<FString>& GetLoggedErrors() const;`
- L31 _public prototype_ `bool HasLoggedMessages() const;`
- L33 _public prototype_ `void OpenLog() const;`
- L35 _public prototype_ `void ClearLog();`
- L46 _private prototype_ `void PrintToLog(ELogLevel Level, const FString& Message) const;`
- L48 _private member_ `TArray<FString> Suggestions;`
- L49 _private member_ `TArray<FString> Warnings;`
- L50 _private member_ `TArray<FString> Errors;`
- L53 _private member_ `TSharedPtr<IMessageLogListing> LogListing;`

#### enum `FGLTFLogBuilder::ELogLevel`  
`enum class ELogLevel`  
_L39-44_
- L41 _public enumerator_ `Suggestion`
- L42 _public enumerator_ `Warning`
- L43 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFMemoryArchive.h` (Public)


#### class `FGLTFMemoryArchive`  
`class FGLTFMemoryArchive final : public FMemoryArchive, public TArray64<uint8>`  
_L8-32_
- inherits: `FMemoryArchive,TArray64<uint8>`
- L12 _public function_ `FGLTFMemoryArchive()`
- L17 _public function_ `virtual void Serialize(void* Data, int64 Length) override`
- L28 _public function_ `virtual int64 TotalSize() override`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Builders/GLTFTaskBuilder.h` (Public)


#### class `FGLTFTaskBuilder`  
`class FGLTFTaskBuilder : public FGLTFLogBuilder`  
_L10-39_
- inherits: `FGLTFLogBuilder`
- L14 _public prototype_ `FGLTFTaskBuilder(const FString& FileName, const UGLTFExportOptions* ExportOptions = nullptr);`
- L17 _public function_ `template <typename TaskType, typename... TaskArgTypes, typename = typename TEnableIf<TIsDerivedFrom<TaskType, FGLTFDelayedTask>::Value>::Type> bool ScheduleSlowTask(TaskArgTypes&&... Args)`
- L23 _public function_ `template <typename TaskType, typename = typename TEnableIf<TIsDerivedFrom<TaskType, FGLTFDelayedTask>::Value>::Type> bool ScheduleSlowTask(TUniquePtr<TaskType> Task)`
- L28 _public prototype_ `bool ScheduleSlowTask(TUniquePtr<FGLTFDelayedTask> Task);`
- L30 _public prototype_ `void ProcessSlowTasks(FFeedbackContext* Context = nullptr);`
- L34 _private prototype_ `static FText GetPriorityMessageFormat(EGLTFTaskPriority Priority);`
- L36 _private member_ `int32 PriorityIndexLock;`
- L37 _private member_ `TMap<EGLTFTaskPriority, TArray<TUniquePtr<FGLTFDelayedTask>>> TasksByPriority;`
- L38 _private member_ `TMap<EGLTFTaskPriority, TArray<TUniquePtr<FGLTFDelayedTask>>> TasksByPrioritySecondary;` — Adding to this if ProcessSlowTasks is in progress.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFAccessorConverters.h` (Public)


#### class `FGLTFPositionBufferConverter`  
`class FGLTFPositionBufferConverter : public FGLTFBuilderContext, public IGLTFPositionBufferConverter`  
_L39-48_
- inherits: `FGLTFBuilderContext,IGLTFPositionBufferConverter`
- L47 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FPositionVertexBuffer* VertexBuffer) override;`

#### class `FGLTFPositionDeltaBufferConverter`  
`class FGLTFPositionDeltaBufferConverter : public FGLTFBuilderContext, public IGLTFPositionDeltaBufferConverter`  
_L50-59_
- inherits: `FGLTFBuilderContext,IGLTFPositionDeltaBufferConverter`
- L58 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const TMap<uint32, FVector3f>* TargetPositionDeltas) override;`

#### class `FGLTFColorBufferConverter`  
`class FGLTFColorBufferConverter : public FGLTFBuilderContext, public IGLTFColorBufferConverter`  
_L61-70_
- inherits: `FGLTFBuilderContext,IGLTFColorBufferConverter`
- L69 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FColorVertexBuffer* VertexBuffer) override;`

#### class `FGLTFNormalBufferConverter`  
`class FGLTFNormalBufferConverter : public FGLTFBuilderContext, public IGLTFNormalBufferConverter`  
_L72-86_
- inherits: `FGLTFBuilderContext,IGLTFNormalBufferConverter`
- L80 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer) override;`
- L85 _private prototype_ `template <typename DestinationType, typename SourceType> FGLTFJsonBufferView* ConvertBufferView(const FGLTFMeshSection* MeshSection, const void* TangentData);`

#### class `FGLTFNormalDeltaBufferConverter`  
`class FGLTFNormalDeltaBufferConverter : public FGLTFBuilderContext, public IGLTFNormalDeltaBufferConverter`  
_L88-102_
- inherits: `FGLTFBuilderContext,IGLTFNormalDeltaBufferConverter`
- L96 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const TMap<uint32, FVector3f>* TargetNormalDeltas, bool bHighPrecision) override;`
- L101 _private prototype_ `template <typename DestinationType, typename SourceType> FGLTFJsonBufferView* ConvertBufferView(const FGLTFMeshSection* MeshSection, const TMap<uint32, FVector3f>* TargetNormalDeltas);`

#### class `FGLTFTangentBufferConverter`  
`class FGLTFTangentBufferConverter : public FGLTFBuilderContext, public IGLTFTangentBufferConverter`  
_L104-118_
- inherits: `FGLTFBuilderContext,IGLTFTangentBufferConverter`
- L112 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer) override;`
- L117 _private prototype_ `template <typename DestinationType, typename SourceType> FGLTFJsonBufferView* ConvertBufferView(const FGLTFMeshSection* MeshSection, const void* TangentData);`

#### class `FGLTFUVBufferConverter`  
`class FGLTFUVBufferConverter : public FGLTFBuilderContext, public IGLTFUVBufferConverter`  
_L120-134_
- inherits: `FGLTFBuilderContext,IGLTFUVBufferConverter`
- L128 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer, uint32 UVIndex) override;`
- L133 _private prototype_ `template <typename SourceType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FStaticMeshVertexBuffer* VertexBuffer, uint32 UVIndex, const uint8* SourceData) const;`

#### class `FGLTFBoneIndexBufferConverter`  
`class FGLTFBoneIndexBufferConverter : public FGLTFBuilderContext, public IGLTFBoneIndexBufferConverter`  
_L136-156_
- inherits: `FGLTFBuilderContext,IGLTFBoneIndexBufferConverter`
- L144 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset) override;`
- L149 _private prototype_ `template <typename DestinationType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset, const uint8* SourceData) const;`
- L152 _private prototype_ `template <typename DestinationType, typename SourceType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset, const uint8* SourceData) const;`
- L155 _private prototype_ `template <typename DestinationType, typename SourceType, typename CallbackType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset, const uint8* SourceData, CallbackType GetVertexInfluenceOffsetCount) const;`

#### class `FGLTFBoneWeightBufferConverter`  
`class FGLTFBoneWeightBufferConverter : public FGLTFBuilderContext, public IGLTFBoneWeightBufferConverter`  
_L158-175_
- inherits: `FGLTFBuilderContext,IGLTFBoneWeightBufferConverter`
- L166 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset) override;`
- L171 _private prototype_ `template <typename BoneIndexType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset, const uint8* SourceData) const;`
- L174 _private prototype_ `template <typename BoneIndexType, typename CallbackType> FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection, const FSkinWeightVertexBuffer* VertexBuffer, uint32 InfluenceOffset, const uint8* SourceData, CallbackType GetVertexInfluenceOffsetCount) const;`

#### class `FGLTFIndexBufferConverter`  
`class FGLTFIndexBufferConverter : public FGLTFBuilderContext, public IGLTFIndexBufferConverter`  
_L177-186_
- inherits: `FGLTFBuilderContext,IGLTFIndexBufferConverter`
- L185 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(const FGLTFMeshSection* MeshSection) override;`

#### class `FGLTFPositionBufferConverterRaw`  
`class FGLTFPositionBufferConverterRaw : public FGLTFBuilderContext, public IGLTFPositionBufferConverterRaw`  
_L189-196_
- inherits: `FGLTFBuilderContext,IGLTFPositionBufferConverterRaw`
- L195 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFPositionArray VertexBuffer) override;`

#### class `FGLTFIndexBufferConverterRaw`  
`class FGLTFIndexBufferConverterRaw : public FGLTFBuilderContext, public IGLTFIndexBufferConverterRaw`  
_L198-205_
- inherits: `FGLTFBuilderContext,IGLTFIndexBufferConverterRaw`
- L204 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFIndexArray IndexBuffer, FString MeshName) override;`

#### class `FGLTFNormalBufferConverterRaw`  
`class FGLTFNormalBufferConverterRaw : public FGLTFBuilderContext, public IGLTFNormalBufferConverterRaw`  
_L207-214_
- inherits: `FGLTFBuilderContext,IGLTFNormalBufferConverterRaw`
- L213 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFNormalArray NormalsSource, bool bNormalize) override;`

#### class `FGLTFUVBufferConverterRaw`  
`class FGLTFUVBufferConverterRaw : public FGLTFBuilderContext, public IGLTFUVBufferConverterRaw`  
_L216-224_
- inherits: `FGLTFBuilderContext,IGLTFUVBufferConverterRaw`
- L223 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFUVArray UVSource) override;`

#### class `FGLTFColorBufferConverterRaw`  
`class FGLTFColorBufferConverterRaw : public FGLTFBuilderContext, public IGLTFColorBufferConverterRaw`  
_L226-233_
- inherits: `FGLTFBuilderContext,IGLTFColorBufferConverterRaw`
- L232 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFColorArray VertexColorBuffer) override;`

#### class `FGLTFTangentBufferConverterRaw`  
`class FGLTFTangentBufferConverterRaw : public FGLTFBuilderContext, public IGLTFTangentBufferConverterRaw`  
_L235-242_
- inherits: `FGLTFBuilderContext,IGLTFTangentBufferConverterRaw`
- L241 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFTangentArray TangentSource) override;`

#### class `FGLTFBoneIndexBufferConverterRaw`  
`class FGLTFBoneIndexBufferConverterRaw : public FGLTFBuilderContext, public IGLTFBoneIndexBufferConverterRaw`  
_L244-251_
- inherits: `FGLTFBuilderContext,IGLTFBoneIndexBufferConverterRaw`
- L250 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFJointInfluenceArray Joints) override;`

#### class `FGLTFBoneWeightBufferConverterRaw`  
`class FGLTFBoneWeightBufferConverterRaw : public FGLTFBuilderContext, public IGLTFBoneWeightBufferConverterRaw`  
_L253-260_
- inherits: `FGLTFBuilderContext,IGLTFBoneWeightBufferConverterRaw`
- L259 _protected prototype_ `virtual FGLTFJsonAccessor* Convert(FGLTFJointWeightArray Weights) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GLTFEXPORTER_API`
- L18 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FPositionVertexBuffer*> IGLTFPositionBufferConverter;`
- L19 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const TMap<uint32, FVector3f>*> IGLTFPositionDeltaBufferConverter;`
- L20 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FColorVertexBuffer*> IGLTFColorBufferConverter;`
- L21 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FStaticMeshVertexBuffer*> IGLTFNormalBufferConverter;`
- L22 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const TMap<uint32, FVector3f>*, bool> IGLTFNormalDeltaBufferConverter;`
- L23 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FStaticMeshVertexBuffer*> IGLTFTangentBufferConverter;`
- L24 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FStaticMeshVertexBuffer*, uint32> IGLTFUVBufferConverter;`
- L25 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FSkinWeightVertexBuffer*, uint32> IGLTFBoneIndexBufferConverter;`
- L26 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*, const FSkinWeightVertexBuffer*, uint32> IGLTFBoneWeightBufferConverter;`
- L27 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, const FGLTFMeshSection*> IGLTFIndexBufferConverter;`
- L29 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFPositionArray> IGLTFPositionBufferConverterRaw;`
- L30 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFIndexArray, FString> IGLTFIndexBufferConverterRaw;`
- L31 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFNormalArray, bool> IGLTFNormalBufferConverterRaw;`
- L32 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFUVArray> IGLTFUVBufferConverterRaw;`
- L33 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFColorArray> IGLTFColorBufferConverterRaw;`
- L34 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFTangentArray> IGLTFTangentBufferConverterRaw;`
- L35 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFJointInfluenceArray> IGLTFBoneIndexBufferConverterRaw;`
- L36 _typedef_ `typedef TGLTFConverter<FGLTFJsonAccessor*, FGLTFJointWeightArray> IGLTFBoneWeightBufferConverterRaw;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFAnimationConverters.h` (Public)


#### class `FGLTFAnimationConverter`  
`class FGLTFAnimationConverter : public FGLTFBuilderContext, public IGLTFAnimationConverter`  
_L23-32_
- inherits: `FGLTFBuilderContext,IGLTFAnimationConverter`
- L31 _protected prototype_ `virtual FGLTFJsonAnimation* Convert(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, const UAnimSequence* AnimSequence) override;`

#### class `FGLTFAnimationDataConverter`  
`class FGLTFAnimationDataConverter : public FGLTFBuilderContext, public IGLTFAnimationDataConverter`  
_L34-43_
- inherits: `FGLTFBuilderContext,IGLTFAnimationDataConverter`
- L42 _protected prototype_ `virtual FGLTFJsonAnimation* Convert(FGLTFJsonNode* RootNode, const USkeletalMeshComponent* SkeletalMeshComponent) override;`

#### class `FGLTFLevelSequenceConverter`  
`class FGLTFLevelSequenceConverter : public FGLTFBuilderContext, public IGLTFLevelSequenceConverter`  
_L45-54_
- inherits: `FGLTFBuilderContext,IGLTFLevelSequenceConverter`
- L53 _protected prototype_ `virtual FGLTFJsonAnimation* Convert(const ULevel* Level, const ULevelSequence*) override;`

#### class `FGLTFLevelSequenceDataConverter`  
`class FGLTFLevelSequenceDataConverter : public FGLTFBuilderContext, public IGLTFLevelSequenceDataConverter`  
_L56-65_
- inherits: `FGLTFBuilderContext,IGLTFLevelSequenceDataConverter`
- L64 _protected prototype_ `virtual FGLTFJsonAnimation* Convert(const ALevelSequenceActor* LevelSequenceActor) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L18 _typedef_ `typedef TGLTFConverter<FGLTFJsonAnimation*, FGLTFJsonNode*, const USkeletalMesh*, const UAnimSequence*> IGLTFAnimationConverter;`
- L19 _typedef_ `typedef TGLTFConverter<FGLTFJsonAnimation*, FGLTFJsonNode*, const USkeletalMeshComponent*> IGLTFAnimationDataConverter;`
- L20 _typedef_ `typedef TGLTFConverter<FGLTFJsonAnimation*, const ULevel*, const ULevelSequence*> IGLTFLevelSequenceConverter;`
- L21 _typedef_ `typedef TGLTFConverter<FGLTFJsonAnimation*, const ALevelSequenceActor*> IGLTFLevelSequenceDataConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFBuilderContext.h` (Public)


#### class `FGLTFBuilderContext`  
`class FGLTFBuilderContext`  
_L9-21_
- L13 _public function_ `FGLTFBuilderContext(FGLTFConvertBuilder& Builder) : Builder(Builder)`
- L20 _protected member_ `FGLTFConvertBuilder& Builder;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFCameraConverters.h` (Public)


#### class `FGLTFCameraConverter`  
`class FGLTFCameraConverter : public FGLTFBuilderContext, public IGLTFCameraConverter`  
_L15-24_
- inherits: `FGLTFBuilderContext,IGLTFCameraConverter`
- L23 _protected prototype_ `virtual FGLTFJsonCamera* Convert(const UCameraComponent* CameraComponent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L13 _typedef_ `typedef TGLTFConverter<FGLTFJsonCamera*, const UCameraComponent*> IGLTFCameraConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFConverter.h` (Public)


#### class `TGLTFConverter`  
`template <typename OutputType, typename... InputTypes> class TGLTFConverter`  
_L8-60_
- L10 _private typedef_ `typedef TTuple<InputTypes...> InputTupleType;`
- L14 _public prototype_ `virtual ~TGLTFConverter() = default;`
- L16 _public function_ `OutputType Get(InputTypes... Inputs)`
- L30 _public function_ `OutputType GetOrAdd(InputTypes... Inputs)`
- L46 _public function_ `const TMap<InputTupleType, OutputType>& GetOutputs() const`
- L53 _protected function_ `virtual void Sanitize(InputTypes&... Inputs)`
- L55 _protected prototype_ `virtual OutputType Convert(InputTypes... Inputs) = 0;`
- L59 _private member_ `TMap<InputTupleType, OutputType> CachedOutputs;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFImageConverters.h` (Public)


#### class `FGLTFImageConverter`  
`class FGLTFImageConverter : public FGLTFBuilderContext, public IGLTFImageConverter`  
_L15-28_
- inherits: `FGLTFBuilderContext,IGLTFImageConverter`
- L23 _protected prototype_ `virtual FGLTFJsonImage* Convert(TGLTFSuperfluous<FString> Name, bool bIgnoreAlpha, FIntPoint Size, TGLTFSharedArray<FColor> Pixels) override;`
- L27 _private prototype_ `EGLTFJsonMimeType GetMimeType(const FColor* Pixels, FIntPoint Size, bool bIgnoreAlpha) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GLTFEXPORTER_API`
- L13 _typedef_ `typedef TGLTFConverter<FGLTFJsonImage*, TGLTFSuperfluous<FString>, bool, FIntPoint, TGLTFSharedArray<FColor>> IGLTFImageConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFLightConverters.h` (Public)


#### class `FGLTFLightConverter`  
`class FGLTFLightConverter : public FGLTFBuilderContext, public IGLTFLightConverter`  
_L18-27_
- inherits: `FGLTFBuilderContext,IGLTFLightConverter`
- L26 _protected prototype_ `virtual FGLTFJsonLight* Convert(const ULightComponent* LightComponent) override;`

#### class `FGLTFLightIESConverter`  
`class FGLTFLightIESConverter : public FGLTFBuilderContext, public IGLTFLightIESConverter`  
_L30-39_
- inherits: `FGLTFBuilderContext,IGLTFLightIESConverter`
- desc: IES export is not supported runtime, as we don't have access to the AssetImportData (which stores the SourceFileContent for the IES file).
- L38 _protected prototype_ `virtual FGLTFJsonLightIES* Convert(const ULightComponent* LightComponent) override;`

#### class `FGLTFLightIESInstanceConverter`  
`class FGLTFLightIESInstanceConverter : public FGLTFBuilderContext, public IGLTFLightIESInstanceConverter`  
_L42-51_
- inherits: `FGLTFBuilderContext,IGLTFLightIESInstanceConverter`
- desc: IES export is not supported runtime, as we don't have access to the AssetImportData (which stores the SourceFileContent for the IES file).
- L50 _protected prototype_ `virtual FGLTFJsonLightIESInstance* Convert(const ULightComponent* LightComponent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L13 _typedef_ `typedef TGLTFConverter<FGLTFJsonLight*, const ULightComponent*> IGLTFLightConverter;`
- L14 _typedef_ `typedef TGLTFConverter<FGLTFJsonLightIES*, const ULightComponent*> IGLTFLightIESConverter;`
- L15 _typedef_ `typedef TGLTFConverter<FGLTFJsonLightIESInstance*, const ULightComponent*> IGLTFLightIESInstanceConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFLightMapConverters.h` (Public)


#### class `FGLTFLightMapConverter`  
`class FGLTFLightMapConverter : public FGLTFBuilderContext, public IGLTFLightMapConverter`  
_L15-24_
- inherits: `FGLTFBuilderContext,IGLTFLightMapConverter`
- L23 _protected prototype_ `virtual FGLTFJsonLightMap* Convert(const UStaticMeshComponent* StaticMeshComponent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L13 _typedef_ `typedef TGLTFConverter<FGLTFJsonLightMap*, const UStaticMeshComponent*> IGLTFLightMapConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMaterialArray.h` (Public)


#### class `FGLTFMaterialArray`  
`class FGLTFMaterialArray : public TArray<const UMaterialInterface*>`  
_L10-26_
- inherits: `TArray<constUMaterialInterface*>`
- desc: TODO: should we add GLTFEXPORTER_API ?

#### Free symbols / members of external scopes

- L17 _function_ `friend uint32 GetTypeHash(const FGLTFMaterialArray& MaterialArray)`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMaterialConverters.h` (Public)


#### class `FGLTFMaterialConverter`  
`class FGLTFMaterialConverter : public FGLTFBuilderContext, public IGLTFMaterialConverter`  
_L18-35_
- inherits: `FGLTFBuilderContext,IGLTFMaterialConverter`
- L26 _protected prototype_ `virtual void Sanitize(const UMaterialInterface*& Material, const FGLTFMeshData*& MeshData, FGLTFIndexArray& SectionIndices) override;`
- L28 _protected prototype_ `virtual FGLTFJsonMaterial* Convert(const UMaterialInterface* Material, const FGLTFMeshData* MeshData, FGLTFIndexArray SectionIndices) override;`
- L32 _private member_ `FGLTFUVOverlapChecker UVOverlapChecker;`
- L33 _private member_ `FGLTFUVBoundsCalculator UVBoundsCalculator;`
- L34 _private member_ `FGLTFUVDegenerateChecker UVDegenerateChecker;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GLTFEXPORTER_API`
- L16 _typedef_ `typedef TGLTFConverter<FGLTFJsonMaterial*, const UMaterialInterface*, const FGLTFMeshData*, FGLTFIndexArray> IGLTFMaterialConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMaterialVariantConverters.h` (Public)


#### class `FGLTFMaterialVariantConverter`  
`class FGLTFMaterialVariantConverter : public FGLTFBuilderContext, public IGLTFMaterialVariantConverter`  
_L17-30_
- inherits: `FGLTFBuilderContext,IGLTFMaterialVariantConverter`
- L25 _protected prototype_ `virtual FGLTFJsonMaterialVariant* Convert(const UVariant* Variant) override;`
- L29 _private prototype_ `bool TryParseMaterialProperty(FGLTFJsonPrimitive*& OutPrimitive, FGLTFJsonMaterial*& OutMaterial, const UPropertyValueMaterial* Property) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GLTFEXPORTER_API`
- L15 _typedef_ `typedef TGLTFConverter<FGLTFJsonMaterialVariant*, const UVariant*> IGLTFMaterialVariantConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshAttributesArray.h` (Public)


#### Free symbols / members of external scopes

- L9 _typedef_ `typedef FMeshAttributesArray<int32> FGLTFIndexArray;`
- L10 _typedef_ `typedef FMeshAttributesArray<FVector3f> FGLTFPositionArray;`
- L11 _typedef_ `typedef FMeshAttributesArray<FVector3f> FGLTFNormalArray;`
- L12 _typedef_ `typedef FMeshAttributesArray<FVector4f> FGLTFTangentArray;`
- L13 _typedef_ `typedef FMeshAttributesArray<FVector2f> FGLTFUVArray;`
- L14 _typedef_ `typedef FMeshAttributesArray<FColor> FGLTFColorArray;`
- L16 _typedef_ `typedef FMeshAttributesArray<UE::Math::TIntVector4<FBoneIndexType>> FGLTFJointInfluenceArray;`
- L17 _typedef_ `typedef FMeshAttributesArray<UE::Math::TIntVector4<uint16>> FGLTFJointWeightArray;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshConverters.h` (Public)


#### class `FGLTFStaticMeshConverter`  
`class FGLTFStaticMeshConverter : public FGLTFBuilderContext, public IGLTFStaticMeshConverter`  
_L25-40_
- inherits: `FGLTFBuilderContext,IGLTFStaticMeshConverter`
- L33 _protected prototype_ `virtual void Sanitize(const UStaticMesh*& StaticMesh, const UStaticMeshComponent*& StaticMeshComponent, FGLTFMaterialArray& Materials, int32& LODIndex) override;`
- L35 _protected prototype_ `virtual FGLTFJsonMesh* Convert(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, FGLTFMaterialArray Materials, int32 LODIndex) override;`
- L39 _private member_ `FGLTFStaticMeshSectionConverter MeshSectionConverter;`

#### class `FGLTFSkeletalMeshConverter`  
`class FGLTFSkeletalMeshConverter : public FGLTFBuilderContext, public IGLTFSkeletalMeshConverter`  
_L42-57_
- inherits: `FGLTFBuilderContext,IGLTFSkeletalMeshConverter`
- L50 _protected prototype_ `virtual void Sanitize(const USkeletalMesh*& SkeletalMesh, const USkeletalMeshComponent*& SkeletalMeshComponent, FGLTFMaterialArray& Materials, int32& LODIndex) override;`
- L52 _protected prototype_ `virtual FGLTFJsonMesh* Convert(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, FGLTFMaterialArray Materials, int32 LODIndex) override;`
- L56 _private member_ `FGLTFSkeletalMeshSectionConverter MeshSectionConverter;`

#### class `FGLTFSplineMeshConverter`  
`class FGLTFSplineMeshConverter : public FGLTFBuilderContext, public IGLTFSplineMeshConverter`  
_L59-74_
- inherits: `FGLTFBuilderContext,IGLTFSplineMeshConverter`
- L67 _protected prototype_ `virtual void Sanitize(const UStaticMesh*& StaticMesh, const USplineMeshComponent*& SplineMeshComponent, FGLTFMaterialArray& Materials, int32& LODIndex) override;`
- L69 _protected prototype_ `virtual FGLTFJsonMesh* Convert(const UStaticMesh* StaticMesh, const USplineMeshComponent* SplineMeshComponent, FGLTFMaterialArray Materials, int32 LODIndex) override;`
- L73 _private member_ `FGLTFStaticMeshSectionConverter MeshSectionConverter;`

#### class `FGLTFLandscapeMeshConverter`  
`class FGLTFLandscapeMeshConverter : public FGLTFBuilderContext, public IGLTFLandscapeMeshConverter`  
_L76-89_
- inherits: `FGLTFBuilderContext,IGLTFLandscapeMeshConverter`
- L84 _protected prototype_ `virtual void Sanitize(const ULandscapeComponent*& LandscapeComponent, const UMaterialInterface*& LandscapeMaterial) override;`
- L86 _protected prototype_ `virtual FGLTFJsonMesh* Convert(const ULandscapeComponent* LandscapeComponent, const UMaterialInterface* LandscapeMaterial) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GLTFEXPORTER_API`
- L20 _typedef_ `typedef TGLTFConverter<FGLTFJsonMesh*, const UStaticMesh*, const UStaticMeshComponent*, FGLTFMaterialArray, int32> IGLTFStaticMeshConverter;`
- L21 _typedef_ `typedef TGLTFConverter<FGLTFJsonMesh*, const USkeletalMesh*, const USkeletalMeshComponent*, FGLTFMaterialArray, int32> IGLTFSkeletalMeshConverter;`
- L22 _typedef_ `typedef TGLTFConverter<FGLTFJsonMesh*, const UStaticMesh*, const USplineMeshComponent*, FGLTFMaterialArray, int32> IGLTFSplineMeshConverter;`
- L23 _typedef_ `typedef TGLTFConverter<FGLTFJsonMesh*, const ULandscapeComponent*, const UMaterialInterface*> IGLTFLandscapeMeshConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshData.h` (Public)


#### struct `FGLTFMeshData`  
`struct FGLTFMeshData`  
_L20-43_
- L22 _public prototype_ `FGLTFMeshData(const UStaticMesh* StaticMesh, const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex);`
- L23 _public prototype_ `FGLTFMeshData(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, int32 LODIndex);`
- L25 _public prototype_ `const FGLTFMeshData* GetParent() const;`
- L28 _public member_ `const FGLTFMeshData* Parent;` — TODO: find a better name for referencing the mesh-only data (no component)
- L30 _public member_ `FString Name;`
- L31 _public member_ `int32 LODIndex;`
- L34 _public member_ `FPrimitiveData PrimitiveData;`
- L35 _public member_ `FMeshDescription Description;`
- L37 _public member_ `FLightMapRef LightMap;`
- L38 _public member_ `const FLightmapResourceCluster* LightMapResourceCluster;`
- L39 _public member_ `int32 LightMapTexCoord;`
- L41 _public member_ `int32 BakeUsingTexCoord;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshDataConverters.h` (Public)


#### class `TGLTFMeshDataConverter`  
`template <typename MeshType, typename MeshComponentType> class TGLTFMeshDataConverter : public FGLTFBuilderContext, public TGLTFConverter<const FGLTFMeshData*, const MeshType*, const MeshComponentType*, int32>`  
_L13-35_
- inherits: `FGLTFBuilderContext,TGLTFConverter<constFGLTFMeshData*,constMeshType*,constMeshComponentType*,int32>`
- L19 _public prototype_ `TGLTFMeshDataConverter(TGLTFMeshDataConverter&&) = default;`
- L20 _public prototype_ `TGLTFMeshDataConverter& operator=(TGLTFMeshDataConverter&&) = default;`
- L22 _public prototype_ `TGLTFMeshDataConverter(const TGLTFMeshDataConverter&) = delete;`
- L23 _public prototype_ `TGLTFMeshDataConverter& operator=(const TGLTFMeshDataConverter&) = delete;`
- L27 _protected prototype_ `virtual void Sanitize(const MeshType*& Mesh, const MeshComponentType*& MeshComponent, int32& LODIndex) override;`
- L29 _protected prototype_ `virtual const FGLTFMeshData* Convert(const MeshType* Mesh, const MeshComponentType* MeshComponent, int32 LODIndex) override;`
- L34 _private member_ `TArray<TUniquePtr<FGLTFMeshData>> Outputs;` — TODO: standardize converters that are responsible for deleting their output

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TGLTFConverter<const FGLTFMeshData*, const UStaticMesh*, const UStaticMeshComponent*, int32> IGLTFStaticMeshDataConverter;`
- L10 _typedef_ `typedef TGLTFConverter<const FGLTFMeshData*, const USkeletalMesh*, const USkeletalMeshComponent*, int32> IGLTFSkeletalMeshDataConverter;`
- L37 _typedef_ `typedef TGLTFMeshDataConverter<UStaticMesh, UStaticMeshComponent> FGLTFStaticMeshDataConverter;`
- L38 _typedef_ `typedef TGLTFMeshDataConverter<USkeletalMesh, USkeletalMeshComponent> FGLTFSkeletalMeshDataConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshSection.h` (Public)


#### struct `FGLTFMeshSection`  
`struct FGLTFMeshSection`  
_L16-43_
- L18 _public prototype_ `FGLTFMeshSection(const UStaticMesh* Mesh, int32 LODIndex, const FGLTFIndexArray& SectionIndices);`
- L19 _public prototype_ `FGLTFMeshSection(const USkeletalMesh* Mesh, int32 LODIndex, const FGLTFIndexArray& SectionIndices);`
- L21 _public member_ `FString Name;`
- L22 _public member_ `FGLTFIndexArray SectionIndices;`
- L24 _public member_ `TArray<uint32> IndexMap;`
- L25 _public member_ `TArray<uint32> IndexBuffer;`
- L27 _public member_ `TArray<TArray<FBoneIndexType>> BoneMaps;`
- L28 _public member_ `TArray<uint32> BoneMapLookup;`
- L29 _public member_ `FBoneIndexType MaxBoneIndex;`
- L31 _public prototype_ `FString ToString() const;`
- L36 _private prototype_ `template <typename IndexType, typename SectionArrayType> void Init(const SectionArrayType& Sections, const IndexType* SourceData);`
- L38 _private prototype_ `static uint32 GetIndexOffset(const FStaticMeshSection& Section);`
- L39 _private prototype_ `static uint32 GetIndexOffset(const FSkelMeshRenderSection& Section);`
- L41 _private prototype_ `static const TArray<FBoneIndexType>& GetBoneMap(const FStaticMeshSection& Section);`
- L42 _private prototype_ `static const TArray<FBoneIndexType>& GetBoneMap(const FSkelMeshRenderSection& Section);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFMeshSectionConverters.h` (Public)


#### class `TGLTFMeshSectionConverter`  
`template <typename MeshType> class TGLTFMeshSectionConverter : public TGLTFConverter<const FGLTFMeshSection*, const MeshType*, int32, FGLTFIndexArray>`  
_L10-31_
- inherits: `TGLTFConverter<constFGLTFMeshSection*,constMeshType*,int32,FGLTFIndexArray>`
- L14 _public prototype_ `TGLTFMeshSectionConverter() = default;`
- L15 _public prototype_ `TGLTFMeshSectionConverter(TGLTFMeshSectionConverter&&) = default;`
- L16 _public prototype_ `TGLTFMeshSectionConverter& operator=(TGLTFMeshSectionConverter&&) = default;`
- L18 _public prototype_ `TGLTFMeshSectionConverter(const TGLTFMeshSectionConverter&) = delete;`
- L19 _public prototype_ `TGLTFMeshSectionConverter& operator=(const TGLTFMeshSectionConverter&) = delete;`
- L23 _protected function_ `virtual const FGLTFMeshSection* Convert(const MeshType* Mesh, int32 LODIndex, FGLTFIndexArray SectionIndices) override`
- L30 _private member_ `TArray<TUniquePtr<FGLTFMeshSection>> Outputs;`

#### Free symbols / members of external scopes

- L33 _typedef_ `typedef TGLTFMeshSectionConverter<UStaticMesh> FGLTFStaticMeshSectionConverter;`
- L34 _typedef_ `typedef TGLTFMeshSectionConverter<USkeletalMesh> FGLTFSkeletalMeshSectionConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFNodeConverters.h` (Public)


#### class `FGLTFActorConverter`  
`class FGLTFActorConverter : public FGLTFBuilderContext, public IGLTFActorConverter`  
_L24-33_
- inherits: `FGLTFBuilderContext,IGLTFActorConverter`
- L32 _protected prototype_ `virtual FGLTFJsonNode* Convert(const AActor* Actor) override;`

#### class `FGLTFComponentConverter`  
`class FGLTFComponentConverter : public FGLTFBuilderContext, public IGLTFComponentConverter`  
_L35-46_
- inherits: `FGLTFBuilderContext,IGLTFComponentConverter`
- L43 _protected prototype_ `virtual FGLTFJsonNode* Convert(const USceneComponent* SceneComponent) override;`
- L45 _protected prototype_ `void ConvertComponentSpecialization(const USceneComponent* SceneComponent, const AActor* Owner, FGLTFJsonNode* Node);`

#### class `FGLTFComponentSocketConverter`  
`class FGLTFComponentSocketConverter : public FGLTFBuilderContext, public IGLTFComponentSocketConverter`  
_L48-57_
- inherits: `FGLTFBuilderContext,IGLTFComponentSocketConverter`
- L56 _protected prototype_ `virtual FGLTFJsonNode* Convert(const USceneComponent* SceneComponent, FName SocketName) override;`

#### class `FGLTFStaticSocketConverter`  
`class FGLTFStaticSocketConverter : public FGLTFBuilderContext, public IGLTFStaticSocketConverter`  
_L59-68_
- inherits: `FGLTFBuilderContext,IGLTFStaticSocketConverter`
- L67 _protected prototype_ `virtual FGLTFJsonNode* Convert(FGLTFJsonNode* RootNode, const UStaticMesh* StaticMesh, FName SocketName) override;`

#### class `FGLTFSkeletalSocketConverter`  
`class FGLTFSkeletalSocketConverter : public FGLTFBuilderContext, public IGLTFSkeletalSocketConverter`  
_L70-79_
- inherits: `FGLTFBuilderContext,IGLTFSkeletalSocketConverter`
- L78 _protected prototype_ `virtual FGLTFJsonNode* Convert(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, FName SocketName) override;`

#### class `FGLTFSkeletalBoneConverter`  
`class FGLTFSkeletalBoneConverter : public FGLTFBuilderContext, public IGLTFSkeletalBoneConverter`  
_L81-90_
- inherits: `FGLTFBuilderContext,IGLTFSkeletalBoneConverter`
- L89 _protected prototype_ `virtual FGLTFJsonNode* Convert(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh, int32 BoneIndex) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L17 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, const AActor*> IGLTFActorConverter;`
- L18 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, const USceneComponent*> IGLTFComponentConverter;`
- L19 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, const USceneComponent*, FName> IGLTFComponentSocketConverter;`
- L20 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, FGLTFJsonNode*, const UStaticMesh*, FName> IGLTFStaticSocketConverter;`
- L21 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, FGLTFJsonNode*, const USkeletalMesh*, FName> IGLTFSkeletalSocketConverter;`
- L22 _typedef_ `typedef TGLTFConverter<FGLTFJsonNode*, FGLTFJsonNode*, const USkeletalMesh*, int32> IGLTFSkeletalBoneConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFObjectArrayScopeGuard.h` (Public)


#### class `FGLTFObjectArrayScopeGuard`  
`template <typename ObjectType = UObject, typename = typename TEnableIf<TIsDerivedFrom<ObjectType, UObject>::Value>::Type> class FGLTFObjectArrayScopeGuard : public FGCObject, public TArray<TObjectPtr<ObjectType>>`  
_L9-32_
- inherits: `FGCObject,TArray<TObjectPtr<ObjectType>>`
- L13 _public function_ `FGLTFObjectArrayScopeGuard()`
- L20 _public prototype_ `FGLTFObjectArrayScopeGuard(const FGLTFObjectArrayScopeGuard&) = delete;` — Non-copyable
- L21 _public prototype_ `FGLTFObjectArrayScopeGuard& operator=(const FGLTFObjectArrayScopeGuard&) = delete;`
- L23 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L28 _public function_ `virtual FString GetReferencerName() const override`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFSamplerConverters.h` (Public)


#### class `FGLTFSamplerConverter`  
`class FGLTFSamplerConverter : public FGLTFBuilderContext, public IGLTFSamplerConverter`  
_L14-25_
- inherits: `FGLTFBuilderContext,IGLTFSamplerConverter`
- L22 _protected prototype_ `virtual void Sanitize(TextureAddress& AddressX, TextureAddress& AddressY, TextureFilter& Filter, TextureGroup& LODGroup) override;`
- L24 _protected prototype_ `virtual FGLTFJsonSampler* Convert(TextureAddress AddressX, TextureAddress AddressY, TextureFilter Filter, TextureGroup LODGroup) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GLTFEXPORTER_API`
- L12 _typedef_ `typedef TGLTFConverter<FGLTFJsonSampler*, TextureAddress, TextureAddress, TextureFilter, TextureGroup> IGLTFSamplerConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFSceneConverters.h` (Public)


#### class `FGLTFSceneConverter`  
`class FGLTFSceneConverter : public FGLTFBuilderContext, public IGLTFSceneConverter`  
_L13-25_
- inherits: `FGLTFBuilderContext,IGLTFSceneConverter`
- L21 _protected prototype_ `virtual FGLTFJsonScene* Convert(const UWorld* Level) override;`
- L23 _protected prototype_ `void MakeSkinnedMeshesRoot(FGLTFJsonScene* Scene);`
- L24 _protected prototype_ `void MakeSkinnedMeshesRoot(FGLTFJsonNode* Node, bool bIsRootNode, FGLTFJsonScene* Scene);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L11 _typedef_ `typedef TGLTFConverter<FGLTFJsonScene*, const UWorld*> IGLTFSceneConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFSharedArray.h` (Public)


#### class `TGLTFSharedArray`  
`template <typename ElementType, typename ArrayType = TArray<ElementType>, ESPMode Mode = ESPMode::ThreadSafe> class TGLTFSharedArray : public TSharedRef<ArrayType, Mode>`  
_L11-54_
- inherits: `TSharedRef<ArrayType,Mode>`
- L15 _public function_ `TGLTFSharedArray() : TSharedRef<ArrayType, Mode>(MakeShared<ArrayType>())`
- L24 _public function_ `TGLTFSharedArray(const TSharedRef<OtherType, Mode>& SharedRef) : TSharedRef<ArrayType, Mode>(SharedRef)`
- L32 _public function_ `bool operator==(const TGLTFSharedArray& Other) const`
- L37 _public function_ `bool operator!=(const TGLTFSharedArray& Other) const`

#### Free symbols / members of external scopes

- L42 _function_ `friend uint32 GetTypeHash(const TGLTFSharedArray& SharedArray)`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFSkinConverters.h` (Public)


#### class `FGLTFSkinConverter`  
`class FGLTFSkinConverter : public FGLTFBuilderContext, public IGLTFSkinConverter`  
_L15-24_
- inherits: `FGLTFBuilderContext,IGLTFSkinConverter`
- L23 _protected prototype_ `virtual FGLTFJsonSkin* Convert(FGLTFJsonNode* RootNode, const USkeletalMesh* SkeletalMesh) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`
- L13 _typedef_ `typedef TGLTFConverter<FGLTFJsonSkin*, FGLTFJsonNode*, const USkeletalMesh*> IGLTFSkinConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFSuperfluous.h` (Public)


#### class `TGLTFSuperfluous`  
`template <typename Type> class TGLTFSuperfluous : public Type`  
_L8-34_
- inherits: `Type`
- L12 _public function_ `TGLTFSuperfluous(const Type& Other) : Type(Other)`
- L20 _public function_ `bool operator==(const TGLTFSuperfluous& Other) const`
- L25 _public function_ `bool operator!=(const TGLTFSuperfluous& Other) const`

#### Free symbols / members of external scopes

- L30 _function_ `friend uint32 GetTypeHash(const TGLTFSuperfluous& Superfluous)`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFTextureConverters.h` (Public)


#### class `FGLTFTexture2DConverter`  
`class FGLTFTexture2DConverter : public FGLTFBuilderContext, public IGLTFTexture2DConverter`  
_L23-32_
- inherits: `FGLTFBuilderContext,IGLTFTexture2DConverter`
- L31 _protected prototype_ `virtual FGLTFJsonTexture* Convert(const UTexture2D* Texture2D, bool bToSRGB, TextureAddress WrapS, TextureAddress WrapT) override;`

#### class `FGLTFTextureRenderTarget2DConverter`  
`class FGLTFTextureRenderTarget2DConverter : public FGLTFBuilderContext, public IGLTFTextureRenderTarget2DConverter`  
_L34-43_
- inherits: `FGLTFBuilderContext,IGLTFTextureRenderTarget2DConverter`
- L42 _protected prototype_ `virtual FGLTFJsonTexture* Convert(const UTextureRenderTarget2D* RenderTarget2D, bool bToSRGB) override;`

#### class `FGLTFTextureLightMapConverter`  
`class FGLTFTextureLightMapConverter : public FGLTFBuilderContext, public IGLTFTextureLightMapConverter`  
_L45-54_
- inherits: `FGLTFBuilderContext,IGLTFTextureLightMapConverter`
- L53 _protected prototype_ `virtual FGLTFJsonTexture* Convert(const ULightMapTexture2D* LightMap) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GLTFEXPORTER_API`
- L19 _typedef_ `typedef TGLTFConverter<FGLTFJsonTexture*, const UTexture2D*, bool, TextureAddress, TextureAddress> IGLTFTexture2DConverter;`
- L20 _typedef_ `typedef TGLTFConverter<FGLTFJsonTexture*, const UTextureRenderTarget2D*, bool> IGLTFTextureRenderTarget2DConverter;`
- L21 _typedef_ `typedef TGLTFConverter<FGLTFJsonTexture*, const ULightMapTexture2D*> IGLTFTextureLightMapConverter;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFUVBoundsCalculator.h` (Public)


#### class `FGLTFUVBoundsCalculator`  
`class FGLTFUVBoundsCalculator : public TGLTFConverter<FBox2f, const FMeshDescription*, FGLTFIndexArray, int32>`  
_L12-17_
- inherits: `TGLTFConverter<FBox2f,constFMeshDescription*,FGLTFIndexArray,int32>`
- L16 _protected prototype_ `virtual FBox2f Convert(const FMeshDescription* Description, FGLTFIndexArray SectionIndices, int32 TexCoord) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFUVDegenerateChecker.h` (Public)


#### class `FGLTFUVDegenerateChecker`  
`class FGLTFUVDegenerateChecker : public TGLTFConverter<float, const FMeshDescription*, FGLTFIndexArray, int32>`  
_L13-23_
- inherits: `TGLTFConverter<float,constFMeshDescription*,FGLTFIndexArray,int32>`
- L17 _protected prototype_ `virtual float Convert(const FMeshDescription* Description, FGLTFIndexArray SectionIndices, int32 TexCoord) override;`
- L21 _private prototype_ `static bool IsDegenerateTriangle(const TStaticArray<FVector2f, 3>& Points);`
- L22 _private prototype_ `static bool IsDegenerateTriangle(const TStaticArray<FVector3f, 3>& Points);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Converters/GLTFUVOverlapChecker.h` (Public)


#### class `FGLTFUVOverlapChecker`  
`class FGLTFUVOverlapChecker : public TGLTFConverter<float, const FMeshDescription*, FGLTFIndexArray, int32>`  
_L13-22_
- inherits: `TGLTFConverter<float,constFMeshDescription*,FGLTFIndexArray,int32>`
- L17 _protected prototype_ `virtual float Convert(const FMeshDescription* Description, FGLTFIndexArray SectionIndices, int32 TexCoord) override;`
- L21 _private prototype_ `static UMaterialInterface* GetMaterial();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Core/GLTFColor.h` (Public)


#### struct `TGLTFColor3`  
`template <typename ComponentType> struct TGLTFColor3`  
_L12-35_
- L26 _public function_ `TGLTFColor3( ComponentType R, ComponentType G, ComponentType B ) : R(R) , G(G) , B(B)`

#### union `TGLTFColor3::(anonymous)`  
``  
_L15-24_

#### struct `TGLTFColor3::__anon99363b89010a::(anonymous)`  
``  
_L17-21_

#### struct `TGLTFColor4`  
`template <typename ComponentType> struct TGLTFColor4`  
_L38-64_
- L53 _public function_ `TGLTFColor4( ComponentType R, ComponentType G, ComponentType B, ComponentType A ) : R(R) , G(G) , B(B) , A(A)`

#### union `TGLTFColor4::(anonymous)`  
``  
_L41-51_

#### struct `TGLTFColor4::__anon99363b89030a::(anonymous)`  
``  
_L43-48_

#### Free symbols / members of external scopes

- L23 _member_ `ComponentType Components[3] GCC_PACK(1);` (scope `TGLTFColor3::__anon99363b89010a`)
- L50 _member_ `ComponentType Components[4] GCC_PACK(1);` (scope `TGLTFColor4::__anon99363b89030a`)
- L70 _typedef_ `typedef TGLTFColor3<float> FGLTFColor3;`
- L71 _typedef_ `typedef TGLTFColor4<float> FGLTFColor4;`
- L73 _typedef_ `typedef TGLTFColor4<uint8> FGLTFUInt8Color4;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Core/GLTFMatrix.h` (Public)


#### struct `TGLTFMatrix`  
`template <typename ElementType, SIZE_T Dimensions> struct TGLTFMatrix`  
_L12-25_
- L14 _public member_ `ElementType Elements[Dimensions * Dimensions] GCC_PACK(1);`
- L16 _public function_ `ElementType& operator()(uint32 Column, uint32 Row)`
- L21 _public function_ `const ElementType& operator()(uint32 Column, uint32 Row) const`

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef TGLTFMatrix<float, 2> FGLTFMatrix2;`
- L32 _typedef_ `typedef TGLTFMatrix<float, 3> FGLTFMatrix3;`
- L33 _typedef_ `typedef TGLTFMatrix<float, 4> FGLTFMatrix4;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Core/GLTFQuaternion.h` (Public)


#### struct `TGLTFQuaternion`  
`template <typename ComponentType> struct TGLTFQuaternion`  
_L12-38_
- L27 _public function_ `TGLTFQuaternion( ComponentType X, ComponentType Y, ComponentType Z, ComponentType W ) : X(X) , Y(Y) , Z(Z) , W(W)`

#### union `TGLTFQuaternion::(anonymous)`  
``  
_L15-25_

#### struct `TGLTFQuaternion::__anon1b253970010a::(anonymous)`  
``  
_L17-22_

#### Free symbols / members of external scopes

- L24 _member_ `ComponentType Components[4] GCC_PACK(1);` (scope `TGLTFQuaternion::__anon1b253970010a`)
- L44 _typedef_ `typedef TGLTFQuaternion<float> FGLTFQuaternion;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Core/GLTFVector.h` (Public)


#### struct `TGLTFVector2`  
`template <typename ComponentType> struct TGLTFVector2`  
_L12-32_
- L25 _public function_ `TGLTFVector2( ComponentType X, ComponentType Y ) : X(X) , Y(Y)`

#### union `TGLTFVector2::(anonymous)`  
``  
_L15-23_

#### struct `TGLTFVector2::__anon32759bbd010a::(anonymous)`  
``  
_L17-20_

#### struct `TGLTFVector3`  
`template <typename ComponentType> struct TGLTFVector3`  
_L35-58_
- L49 _public function_ `TGLTFVector3( ComponentType X, ComponentType Y, ComponentType Z ) : X(X) , Y(Y) , Z(Z)`

#### union `TGLTFVector3::(anonymous)`  
``  
_L38-47_

#### struct `TGLTFVector3::__anon32759bbd030a::(anonymous)`  
``  
_L40-44_

#### struct `TGLTFVector4`  
`template <typename ComponentType> struct TGLTFVector4`  
_L61-87_
- L76 _public function_ `TGLTFVector4( ComponentType X, ComponentType Y, ComponentType Z, ComponentType W ) : X(X) , Y(Y) , Z(Z) , W(W)`

#### union `TGLTFVector4::(anonymous)`  
``  
_L64-74_

#### struct `TGLTFVector4::__anon32759bbd050a::(anonymous)`  
``  
_L66-71_

#### Free symbols / members of external scopes

- L22 _member_ `ComponentType Components[2] GCC_PACK(1);` (scope `TGLTFVector2::__anon32759bbd010a`)
- L46 _member_ `ComponentType Components[3] GCC_PACK(1);` (scope `TGLTFVector3::__anon32759bbd030a`)
- L73 _member_ `ComponentType Components[4] GCC_PACK(1);` (scope `TGLTFVector4::__anon32759bbd050a`)
- L93 _typedef_ `typedef TGLTFVector2<float> FGLTFVector2;`
- L94 _typedef_ `typedef TGLTFVector3<float> FGLTFVector3;`
- L95 _typedef_ `typedef TGLTFVector4<float> FGLTFVector4;`
- L97 _typedef_ `typedef TGLTFVector4<int8> FGLTFInt8Vector4;`
- L98 _typedef_ `typedef TGLTFVector4<int16> FGLTFInt16Vector4;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFAnimSequenceExporter.h` (Public)


#### class `UGLTFAnimSequenceExporter`  
`class UGLTFAnimSequenceExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFAnimSequenceExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFExporter.h` (Public)


#### struct `FGLTFExportMessages`  
`struct FGLTFExportMessages`  
_L15-27_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `TArray<FString> Suggestions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)`
- L23 _public member_ `TArray<FString> Warnings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)`
- L26 _public member_ `TArray<FString> Errors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)`

#### class `UGLTFExporter`  
`class UGLTFExporter : public UExporter`  
_L30-76_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UExporter`
- L36 _public prototype_ `explicit UGLTFExporter(const FObjectInitializer& ObjectInitializer);`
- L38 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Archive, FFeedbackContext* Warn, int32 FileIndex, uint32 PortFlags) override;`
- L52 _public prototype_ `static bool ExportToGLTF(UObject* Object, const FString& FilePath, const UGLTFExportOptions* Options, const TSet<AActor*>& SelectedActors, FGLTFExportMessages& OutMessages);` — `UFUNCTION(BlueprintCallable, Category = "Miscellaneous", meta=(AutoCreateRefTerm="SelectedActors"))` — Export the specified object to a glTF file (.gltf or .glb) @param Object          The object to export (supported types are UMaterialInterface, UStaticMesh, USkeletalMesh, UWorld, UAnimSequence, ULevelSequence, ULevelVariantSets). Will default to the currently active world if null. @param FilePath        The filename on disk to save as. Associated textures and binary files will be saved in the same folder, unless file extension is .glb - which results in a self-contained binary file. @param Options         The various options to use during export. Will default to the project's user-specific editor settings if null. @param SelectedActors  The set of actors to export, only applicable if the object to export is a UWorld. An empty set results in the export of all actors. @param OutMessages     The resulting log messages from the export. @return true if the object was successfully exported
- L64 _public prototype_ `static bool ExportToGLTF(UObject* Object, const FString& FilePath, const UGLTFExportOptions* Options = nullptr, const TSet<AActor*>& SelectedActors = {});` — Export the specified object to a glTF file (.gltf or .glb) @param Object          The object to export (supported types are UMaterialInterface, UStaticMesh, USkeletalMesh, UWorld, UAnimSequence, ULevelSequence, ULevelVariantSets). Will default to the currently active world if null. @param FilePath        The filename on disk to save as. Associated textures and binary files will be saved in the same folder, unless file extension is .glb - which results in a self-contained binary file. @param Options         The various options to use during export. Will default to the project's user-specific editor settings if null. @param SelectedActors  The set of actors to export, only applicable if the object to export is a UWorld. An empty set results in the export of all actors. @return true if the object was successfully exported
- L68 _protected prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object);`
- L72 _private prototype_ `const UGLTFExportOptions* GetExportOptions();`
- L74 _private prototype_ `FString GetFilePath() const;`
- L75 _private prototype_ `bool IsAutomated() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFLevelExporter.h` (Public)


#### class `UGLTFLevelExporter`  
`class UGLTFLevelExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFLevelExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFLevelSequenceExporter.h` (Public)


#### class `UGLTFLevelSequenceExporter`  
`class UGLTFLevelSequenceExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFLevelSequenceExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFLevelVariantSetsExporter.h` (Public)


#### class `UGLTFLevelVariantSetsExporter`  
`class UGLTFLevelVariantSetsExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFLevelVariantSetsExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFMaterialExporter.h` (Public)


#### class `UGLTFMaterialExporter`  
`class UGLTFMaterialExporter : public UGLTFExporter`  
_L13-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L19 _public prototype_ `explicit UGLTFMaterialExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L21 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFSkeletalMeshExporter.h` (Public)


#### class `UGLTFSkeletalMeshExporter`  
`class UGLTFSkeletalMeshExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFSkeletalMeshExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Exporters/GLTFStaticMeshExporter.h` (Public)


#### class `UGLTFStaticMeshExporter`  
`class UGLTFStaticMeshExporter : public UGLTFExporter`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGLTFExporter`
- L17 _public prototype_ `explicit UGLTFStaticMeshExporter(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L19 _public prototype_ `virtual bool AddObject(FGLTFContainerBuilder& Builder, const UObject* Object) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/GLTFExporterModule.h` (Public)


#### class `IGLTFExporterModule`  
`class IGLTFExporterModule : public IModuleInterface`  
_L18-41_
- inherits: `IModuleInterface`
- desc: The public interface of the GLTFExporter module
- L27 _public function_ `static IGLTFExporterModule& Get()` — Singleton-like access to IGLTFExporter @return Returns IGLTFExporter singleton instance, loading the module on demand if needed
- L37 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _macro_ `#define GLTFEXPORTER_MODULE_NAME TEXT("GLTFExporter")`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGLTFExporter, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGLTFExporter, Log, All);`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonAccessor.h` (Public)


#### struct `FGLTFJsonAccessor`  
`struct FGLTFJsonAccessor : IGLTFJsonIndexedObject`  
_L9-43_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `FGLTFJsonBufferView* BufferView;`
- L14 _public member_ `int64 ByteOffset;`
- L15 _public member_ `int32 Count;`
- L16 _public member_ `EGLTFJsonAccessorType Type;`
- L17 _public member_ `EGLTFJsonComponentType ComponentType;`
- L18 _public member_ `bool bNormalized;`
- L20 _public member_ `int32 MinMaxLength;`
- L21 _public member_ `float Min[16];`
- L22 _public member_ `float Max[16];`
- L24 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L30 _protected function_ `FGLTFJsonAccessor(int32 Index) : IGLTFJsonIndexedObject(Index) , BufferView(nullptr) , ByteOffset(0) , Count(0) , Type(EGLTFJsonAccessorType::None) , ComponentType(EGLTFJsonComponentType::None) , bNormalized(false) , MinMaxLength(0) , Min`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonAnimation.h` (Public)


#### struct `FGLTFJsonAnimationChannelTarget`  
`struct FGLTFJsonAnimationChannelTarget : IGLTFJsonObject`  
_L9-21_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `FGLTFJsonNode* Node;`
- L12 _public member_ `EGLTFJsonTargetPath Path;`
- L14 _public function_ `FGLTFJsonAnimationChannelTarget() : Node(nullptr) , Path(EGLTFJsonTargetPath::None)`
- L20 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonAnimationChannel`  
`struct FGLTFJsonAnimationChannel : IGLTFJsonObject`  
_L23-34_
- inherits: `IGLTFJsonObject`
- L25 _public member_ `FGLTFJsonAnimationSampler* Sampler;`
- L26 _public member_ `FGLTFJsonAnimationChannelTarget Target;`
- L28 _public function_ `FGLTFJsonAnimationChannel() : Sampler(nullptr)`
- L33 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonAnimationSampler`  
`struct FGLTFJsonAnimationSampler : IGLTFJsonIndexedObject`  
_L36-56_
- inherits: `IGLTFJsonIndexedObject`
- L38 _public member_ `FGLTFJsonAccessor* Input;`
- L39 _public member_ `FGLTFJsonAccessor* Output;`
- L41 _public member_ `EGLTFJsonInterpolation Interpolation;`
- L43 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L49 _protected function_ `FGLTFJsonAnimationSampler(int32 Index) : IGLTFJsonIndexedObject(Index) , Input(nullptr) , Output(nullptr) , Interpolation(EGLTFJsonInterpolation::Linear)`

#### struct `FGLTFJsonAnimation`  
`struct FGLTFJsonAnimation : IGLTFJsonIndexedObject`  
_L58-75_
- inherits: `IGLTFJsonIndexedObject`
- L60 _public member_ `FString Name;`
- L62 _public member_ `TArray<FGLTFJsonAnimationChannel> Channels;`
- L63 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonAnimationSampler> Samplers;`
- L65 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L71 _protected function_ `FGLTFJsonAnimation(int32 Index) : IGLTFJsonIndexedObject(Index)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonArray.h` (Public)


#### struct `IGLTFJsonArray`  
`struct IGLTFJsonArray : IGLTFJsonValue`  
_L9-14_
- inherits: `IGLTFJsonValue`
- L11 _public prototype_ `virtual void WriteValue(IGLTFJsonWriter& Writer) const override final;`
- L13 _public prototype_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonAsset.h` (Public)


#### struct `FGLTFJsonAsset`  
`struct FGLTFJsonAsset : IGLTFJsonObject`  
_L9-21_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `FString Version;`
- L12 _public member_ `FString Generator;`
- L13 _public member_ `FString Copyright;`
- L15 _public function_ `FGLTFJsonAsset() : Version(TEXT("2.0"))`
- L20 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonBuffer.h` (Public)


#### struct `FGLTFJsonBuffer`  
`struct FGLTFJsonBuffer : IGLTFJsonIndexedObject`  
_L9-27_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `FString URI;`
- L14 _public member_ `int64 ByteLength;`
- L16 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L22 _protected function_ `FGLTFJsonBuffer(int32 Index) : IGLTFJsonIndexedObject(Index) , ByteLength(0)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonBufferView.h` (Public)


#### struct `FGLTFJsonBufferView`  
`struct FGLTFJsonBufferView : IGLTFJsonIndexedObject`  
_L9-36_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `FGLTFJsonBuffer* Buffer;`
- L15 _public member_ `int64 ByteLength;`
- L16 _public member_ `int64 ByteOffset;`
- L17 _public member_ `int32 ByteStride;`
- L19 _public member_ `EGLTFJsonBufferTarget Target;`
- L21 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L27 _protected function_ `FGLTFJsonBufferView(int32 Index) : IGLTFJsonIndexedObject(Index) , Buffer(nullptr) , ByteLength(0) , ByteOffset(0) , ByteStride(0) , Target(EGLTFJsonBufferTarget::None)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonCamera.h` (Public)


#### struct `FGLTFJsonOrthographic`  
`struct FGLTFJsonOrthographic : IGLTFJsonObject`  
_L9-25_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `float XMag;` — horizontal magnification of the view
- L12 _public member_ `float YMag;` — vertical magnification of the view
- L13 _public member_ `float ZFar;`
- L14 _public member_ `float ZNear;`
- L16 _public function_ `FGLTFJsonOrthographic() : XMag(0) , YMag(0) , ZFar(0) , ZNear(0)`
- L24 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonPerspective`  
`struct FGLTFJsonPerspective : IGLTFJsonObject`  
_L27-43_
- inherits: `IGLTFJsonObject`
- L29 _public member_ `float AspectRatio;` — aspect ratio of the field of view
- L30 _public member_ `float YFov;` — vertical field of view in radians
- L31 _public member_ `float ZFar;`
- L32 _public member_ `float ZNear;`
- L34 _public function_ `FGLTFJsonPerspective() : AspectRatio(0) , YFov(0) , ZFar(0) , ZNear(0)`
- L42 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonCamera`  
`struct FGLTFJsonCamera : IGLTFJsonIndexedObject`  
_L45-64_
- inherits: `IGLTFJsonIndexedObject`
- L47 _public member_ `FString Name;`
- L49 _public member_ `EGLTFJsonCameraType Type;`
- L50 _public member_ `FGLTFJsonOrthographic Orthographic;`
- L51 _public member_ `FGLTFJsonPerspective Perspective;`
- L53 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L59 _protected function_ `FGLTFJsonCamera(int32 Index) : IGLTFJsonIndexedObject(Index) , Type(EGLTFJsonCameraType::None)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonColor.h` (Public)


#### struct `TGLTFJsonColor`  
`template <typename BaseType> struct TGLTFJsonColor : BaseType, IGLTFJsonArray`  
_L12-63_
- inherits: `BaseType,IGLTFJsonArray`
- L14 _public function_ `TGLTFJsonColor(const BaseType& Other) : BaseType(Other)`
- L19 _public function_ `TGLTFJsonColor& operator=(const BaseType& Other)`
- L25 _public function_ `bool operator==(const BaseType& Other) const`
- L38 _public function_ `bool operator!=(const BaseType& Other) const`
- L43 _public function_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const override`
- L51 _public function_ `bool IsNearlyEqual(const BaseType& Other, float Tolerance = KINDA_SMALL_NUMBER) const`

#### struct `FGLTFJsonColor3`  
`struct FGLTFJsonColor3 : TGLTFJsonColor<FGLTFColor3>`  
_L65-72_
- inherits: `TGLTFJsonColor<FGLTFColor3>`
- L67 _public member_ `static const FGLTFJsonColor3 Black;`
- L68 _public member_ `static const FGLTFJsonColor3 White;`

#### struct `FGLTFJsonColor4`  
`struct FGLTFJsonColor4 : TGLTFJsonColor<FGLTFColor4>`  
_L74-81_
- inherits: `TGLTFJsonColor<FGLTFColor4>`
- L76 _public member_ `static const FGLTFJsonColor4 Black;`
- L77 _public member_ `static const FGLTFJsonColor4 White;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonCore.h` (Public)
_(no declarations extracted)_

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonEnums.h` (Public)


#### enum `EGLTFJsonExtension`  
`enum class EGLTFJsonExtension`  
_L5-23_
- L7 _public enumerator_ `KHR_LightsPunctual`
- L8 _public enumerator_ `EXT_LightsIES`
- L9 _public enumerator_ `KHR_MaterialsClearCoat`
- L10 _public enumerator_ `KHR_MaterialsEmissiveStrength`
- L11 _public enumerator_ `KHR_MaterialsUnlit`
- L12 _public enumerator_ `KHR_MaterialsVariants`
- L13 _public enumerator_ `KHR_MaterialsIOR`
- L14 _public enumerator_ `KHR_MaterialsSheen`
- L15 _public enumerator_ `KHR_MaterialsTransmission`
- L16 _public enumerator_ `KHR_MaterialsSpecularGlossiness`
- L17 _public enumerator_ `KHR_MaterialsIridescence`
- L18 _public enumerator_ `KHR_MaterialsAnisotropy`
- L19 _public enumerator_ `KHR_MeshQuantization`
- L20 _public enumerator_ `KHR_TextureTransform`
- L21 _public enumerator_ `KHR_MaterialsSpecular`
- L22 _public enumerator_ `EPIC_LightmapTextures`

#### enum `EGLTFJsonShadingModel`  
`enum class EGLTFJsonShadingModel`  
_L25-36_
- L27 _public enumerator_ `None = -1`
- L28 _public enumerator_ `Default`
- L29 _public enumerator_ `Unlit`
- L30 _public enumerator_ `ClearCoat`
- L31 _public enumerator_ `Sheen`
- L32 _public enumerator_ `Transmission` — Sheen,  UE Cloth
- L33 _public enumerator_ `SpecularGlossiness` — Transmission,  UE Thin Translucent
- L35 _public enumerator_ `NumShadingModels`

#### enum `EGLTFJsonAccessorType`  
`enum class EGLTFJsonAccessorType`  
_L38-48_
- L40 _public enumerator_ `None = -1`
- L41 _public enumerator_ `Scalar`
- L42 _public enumerator_ `Vec2`
- L43 _public enumerator_ `Vec3`
- L44 _public enumerator_ `Vec4`
- L45 _public enumerator_ `Mat2`
- L46 _public enumerator_ `Mat3`
- L47 _public enumerator_ `Mat4`

#### enum `EGLTFJsonComponentType`  
`enum class EGLTFJsonComponentType`  
_L50-60_
- L52 _public enumerator_ `None = -1`
- L53 _public enumerator_ `Int8 = 5120`
- L54 _public enumerator_ `UInt8 = 5121`
- L55 _public enumerator_ `Int16 = 5122`
- L56 _public enumerator_ `UInt16 = 5123`
- L57 _public enumerator_ `Int32 = 5124` — unused
- L58 _public enumerator_ `UInt32 = 5125`
- L59 _public enumerator_ `Float = 5126`

#### enum `EGLTFJsonBufferTarget`  
`enum class EGLTFJsonBufferTarget`  
_L62-67_
- L64 _public enumerator_ `None = -1`
- L65 _public enumerator_ `ArrayBuffer = 34962`
- L66 _public enumerator_ `ElementArrayBuffer = 34963`

#### enum `EGLTFJsonPrimitiveMode`  
`enum class EGLTFJsonPrimitiveMode`  
_L69-78_
- L71 _public enumerator_ `Points = 0`
- L72 _public enumerator_ `Lines = 1`
- L73 _public enumerator_ `LineLoop = 2`
- L74 _public enumerator_ `LineStrip = 3`
- L75 _public enumerator_ `Triangles = 4`
- L76 _public enumerator_ `TriangleStrip = 5`
- L77 _public enumerator_ `TriangleFan = 6`

#### enum `EGLTFJsonAlphaMode`  
`enum class EGLTFJsonAlphaMode`  
_L80-86_
- L82 _public enumerator_ `None = -1`
- L83 _public enumerator_ `Opaque`
- L84 _public enumerator_ `Mask`
- L85 _public enumerator_ `Blend`

#### enum `EGLTFJsonMimeType`  
`enum class EGLTFJsonMimeType`  
_L88-93_
- L90 _public enumerator_ `None = -1`
- L91 _public enumerator_ `PNG`
- L92 _public enumerator_ `JPEG`

#### enum `EGLTFJsonTextureFilter`  
`enum class EGLTFJsonTextureFilter`  
_L95-104_
- L97 _public enumerator_ `None = -1`
- L98 _public enumerator_ `Nearest = 9728`
- L99 _public enumerator_ `Linear = 9729`
- L100 _public enumerator_ `NearestMipmapNearest = 9984`
- L101 _public enumerator_ `LinearMipmapNearest = 9985`
- L102 _public enumerator_ `NearestMipmapLinear = 9986`
- L103 _public enumerator_ `LinearMipmapLinear = 9987`

#### enum `EGLTFJsonTextureWrap`  
`enum class EGLTFJsonTextureWrap`  
_L106-112_
- L108 _public enumerator_ `None = -1`
- L109 _public enumerator_ `Repeat = 10497`
- L110 _public enumerator_ `MirroredRepeat = 33648`
- L111 _public enumerator_ `ClampToEdge = 33071`

#### enum `EGLTFJsonInterpolation`  
`enum class EGLTFJsonInterpolation`  
_L114-120_
- L116 _public enumerator_ `None = -1`
- L117 _public enumerator_ `Linear`
- L118 _public enumerator_ `Step`
- L119 _public enumerator_ `CubicSpline`

#### enum `EGLTFJsonTargetPath`  
`enum class EGLTFJsonTargetPath`  
_L122-129_
- L124 _public enumerator_ `None = -1`
- L125 _public enumerator_ `Translation`
- L126 _public enumerator_ `Rotation`
- L127 _public enumerator_ `Scale`
- L128 _public enumerator_ `Weights`

#### enum `EGLTFJsonCameraType`  
`enum class EGLTFJsonCameraType`  
_L131-136_
- L133 _public enumerator_ `None = -1`
- L134 _public enumerator_ `Orthographic`
- L135 _public enumerator_ `Perspective`

#### enum `EGLTFJsonLightType`  
`enum class EGLTFJsonLightType`  
_L138-144_
- L140 _public enumerator_ `None = -1`
- L141 _public enumerator_ `Directional`
- L142 _public enumerator_ `Point`
- L143 _public enumerator_ `Spot`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonExtensions.h` (Public)


#### struct `FGLTFJsonExtensions`  
`struct FGLTFJsonExtensions`  
_L8-12_
- L10 _public member_ `TSet<EGLTFJsonExtension> Used;`
- L11 _public member_ `TSet<EGLTFJsonExtension> Required;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonImage.h` (Public)


#### struct `FGLTFJsonImage`  
`struct FGLTFJsonImage : IGLTFJsonIndexedObject`  
_L9-30_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L12 _public member_ `FString URI;`
- L14 _public member_ `EGLTFJsonMimeType MimeType;`
- L16 _public member_ `FGLTFJsonBufferView* BufferView;`
- L18 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L24 _protected function_ `FGLTFJsonImage(int32 Index) : IGLTFJsonIndexedObject(Index) , MimeType(EGLTFJsonMimeType::None) , BufferView(nullptr)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonIndexedObject.h` (Public)


#### struct `IGLTFJsonIndexedObject`  
`struct IGLTFJsonIndexedObject : IGLTFJsonObject`  
_L7-17_
- inherits: `IGLTFJsonObject`
- L9 _public member_ `int32 Index;`
- L13 _protected function_ `IGLTFJsonIndexedObject(int32 Index) : Index(Index)`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonIndexedObjectArray.h` (Public)


#### struct `TGLTFJsonIndexedObjectArray`  
`template <typename ElementType, typename = typename TEnableIf<TIsDerivedFrom<ElementType, IGLTFJsonIndexedObject>::Value>::Type> struct TGLTFJsonIndexedObjectArray : IGLTFJsonArray`  
_L10-133_
- inherits: `IGLTFJsonArray`
- L12 _public typedef_ `using ArrayType = TArray<TUniquePtr<ElementType>>;`
- L13 _public typedef_ `using SizeType = typename ArrayType::SizeType;`
- L40 _public function_ `friend bool operator!=(const TIterator& A, const TIterator& B)`
- L50 _public typedef_ `typedef TIterator<typename ArrayType::RangedForIteratorType, ElementType*> IteratorType;`
- L51 _public typedef_ `typedef TIterator<typename ArrayType::RangedForConstIteratorType, const ElementType*> ConstIteratorType;`
- L53 _public prototype_ `TGLTFJsonIndexedObjectArray() = default;`
- L54 _public prototype_ `TGLTFJsonIndexedObjectArray(TGLTFJsonIndexedObjectArray&& Other) = default;`
- L55 _public prototype_ `TGLTFJsonIndexedObjectArray& operator=(TGLTFJsonIndexedObjectArray&& Other) = default;`
- L57 _public prototype_ `TGLTFJsonIndexedObjectArray(const TGLTFJsonIndexedObjectArray&) = delete;`
- L58 _public prototype_ `TGLTFJsonIndexedObjectArray& operator=(const TGLTFJsonIndexedObjectArray&) = delete;`
- L60 _public function_ `ElementType* Add()`
- L68 _public function_ `void Remove(int32 Index)` — Do not forget to call FixElementIndices after.
- L73 _public function_ `void FixElementIndices()`
- L81 _public function_ `bool IsValidIndex(SizeType Index) const`
- L86 _public function_ `SizeType Num() const`
- L91 _public function_ `bool Contains(const ElementType* Element) const`
- L99 _public function_ `SizeType Find(const ElementType* Element) const`
- L107 _public function_ `ElementType* operator[](SizeType Index)`
- L112 _public function_ `const ElementType* operator[](SizeType Index) const`
- L117 _public function_ `IteratorType begin()`
- L118 _public function_ `IteratorType end()`
- L119 _public function_ `ConstIteratorType begin() const`
- L120 _public function_ `ConstIteratorType end() const`
- L122 _public function_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const override`
- L132 _private member_ `ArrayType Array;`

#### struct `TGLTFJsonIndexedObjectArray::TIterator`  
`template <typename IteratorType, typename ValueType> struct TIterator`  
_L16-48_
- L18 _public function_ `TIterator(const IteratorType& Iterator) : Iterator(Iterator)`
- L23 _public function_ `ValueType operator*() const`
- L28 _public function_ `TIterator& operator++()`
- L34 _public function_ `TIterator& operator--()`
- L47 _private member_ `IteratorType Iterator;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonLight.h` (Public)


#### struct `FGLTFJsonSpotLight`  
`struct FGLTFJsonSpotLight : IGLTFJsonObject`  
_L9-21_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `float InnerConeAngle;`
- L12 _public member_ `float OuterConeAngle;`
- L14 _public function_ `FGLTFJsonSpotLight() : InnerConeAngle(0) , OuterConeAngle(HALF_PI)`
- L20 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonLight`  
`struct FGLTFJsonLight : IGLTFJsonIndexedObject`  
_L23-50_
- inherits: `IGLTFJsonIndexedObject`
- L25 _public member_ `FString Name;`
- L27 _public member_ `EGLTFJsonLightType Type;`
- L29 _public member_ `FGLTFJsonColor3 Color;`
- L31 _public member_ `float Intensity;`
- L32 _public member_ `float Range;`
- L34 _public member_ `FGLTFJsonSpotLight Spot;`
- L36 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L42 _protected function_ `FGLTFJsonLight(int32 Index) : IGLTFJsonIndexedObject(Index) , Type(EGLTFJsonLightType::None) , Color(FGLTFJsonColor3::White) , Intensity(1) , Range(0)`

#### struct `FGLTFJsonLightIES`  
`struct FGLTFJsonLightIES : IGLTFJsonIndexedObject`  
_L53-74_
- inherits: `IGLTFJsonIndexedObject`
- L55 _public member_ `FString Name;`
- L57 _public member_ `FString URI;`
- L59 _public member_ `FString MimeType;`
- L60 _public member_ `FGLTFJsonBufferView* BufferView;`
- L62 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L68 _protected function_ `FGLTFJsonLightIES(int32 Index) : IGLTFJsonIndexedObject(Index) , MimeType(TEXT("application/x-ies-lm-63")) , BufferView(nullptr)`

#### struct `FGLTFJsonLightIESInstance`  
`struct FGLTFJsonLightIESInstance : IGLTFJsonIndexedObject`  
_L76-97_
- inherits: `IGLTFJsonIndexedObject`
- L79 _public member_ `float Multiplier;` — FGLTFJsonColor3 Color; //Note: While IES extension can store the Color, the Export will save out the Color within the KHR_Lights_Punctual extension.
- L81 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L83 _public member_ `FGLTFJsonLightIES* LightIES;`
- L85 _public function_ `bool HasValue()`
- L91 _protected function_ `FGLTFJsonLightIESInstance(int32 Index) : IGLTFJsonIndexedObject(Index) , Multiplier(1) , LightIES(nullptr)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonLightMap.h` (Public)


#### struct `FGLTFJsonLightMap`  
`struct FGLTFJsonLightMap : IGLTFJsonIndexedObject`  
_L10-31_
- inherits: `IGLTFJsonIndexedObject`
- L12 _public member_ `FString Name;`
- L13 _public member_ `FGLTFJsonTextureInfo Texture;`
- L14 _public member_ `FGLTFJsonVector4 LightMapScale;`
- L15 _public member_ `FGLTFJsonVector4 LightMapAdd;`
- L16 _public member_ `FGLTFJsonVector4 CoordinateScaleBias;`
- L18 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L24 _protected function_ `FGLTFJsonLightMap(int32 Index) : IGLTFJsonIndexedObject(Index) , LightMapScale(FGLTFJsonVector4::One) , LightMapAdd(FGLTFJsonVector4::Zero) , CoordinateScaleBias({ 1, 1, 0, 0 })`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonMaterial.h` (Public)


#### struct `FGLTFJsonTextureInfo`  
`struct FGLTFJsonTextureInfo : IGLTFJsonObject`  
_L10-24_
- inherits: `IGLTFJsonObject`
- L12 _public member_ `FGLTFJsonTexture* Index;`
- L13 _public member_ `int32 TexCoord;`
- L15 _public member_ `FGLTFJsonTextureTransform Transform;`
- L17 _public function_ `FGLTFJsonTextureInfo() : Index(nullptr) , TexCoord(0)`
- L23 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonNormalTextureInfo`  
`struct FGLTFJsonNormalTextureInfo : FGLTFJsonTextureInfo`  
_L26-36_
- inherits: `FGLTFJsonTextureInfo`
- L28 _public member_ `float Scale;`
- L30 _public function_ `FGLTFJsonNormalTextureInfo() : Scale(1)`
- L35 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonOcclusionTextureInfo`  
`struct FGLTFJsonOcclusionTextureInfo : FGLTFJsonTextureInfo`  
_L38-48_
- inherits: `FGLTFJsonTextureInfo`
- L40 _public member_ `float Strength;`
- L42 _public function_ `FGLTFJsonOcclusionTextureInfo() : Strength(1)`
- L47 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonPBRMetallicRoughness`  
`struct FGLTFJsonPBRMetallicRoughness : IGLTFJsonObject`  
_L50-67_
- inherits: `IGLTFJsonObject`
- L52 _public member_ `FGLTFJsonColor4 BaseColorFactor;`
- L53 _public member_ `FGLTFJsonTextureInfo BaseColorTexture;`
- L55 _public member_ `float MetallicFactor;`
- L56 _public member_ `float RoughnessFactor;`
- L57 _public member_ `FGLTFJsonTextureInfo MetallicRoughnessTexture;`
- L59 _public function_ `FGLTFJsonPBRMetallicRoughness() : BaseColorFactor(FGLTFJsonColor4::White) , MetallicFactor(1) , RoughnessFactor(1)`
- L66 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonClearCoatExtension`  
`struct FGLTFJsonClearCoatExtension : IGLTFJsonObject`  
_L69-86_
- inherits: `IGLTFJsonObject`
- L71 _public member_ `float ClearCoatFactor;`
- L72 _public member_ `FGLTFJsonTextureInfo ClearCoatTexture;`
- L74 _public member_ `float ClearCoatRoughnessFactor;`
- L75 _public member_ `FGLTFJsonTextureInfo ClearCoatRoughnessTexture;`
- L77 _public member_ `FGLTFJsonNormalTextureInfo ClearCoatNormalTexture;`
- L79 _public function_ `FGLTFJsonClearCoatExtension() : ClearCoatFactor(0) , ClearCoatRoughnessFactor(0)`
- L85 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonSpecularExtension`  
`struct FGLTFJsonSpecularExtension : IGLTFJsonObject`  
_L91-105_
- inherits: `IGLTFJsonObject`
- desc: Only taking advantage of SpecularFactor and SpecularMaps
- L93 _public member_ `float Factor;` — SpecularFactor
- L94 _public member_ `FGLTFJsonTextureInfo Texture;` — SpecularMap
- L96 _public function_ `FGLTFJsonSpecularExtension() : Factor(0.5)`
- L102 _public function_ `bool HasValue() const` — UE's default Specular value is 0.5, while glTF's is 1.
- L104 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonIORExtension`  
`struct FGLTFJsonIORExtension : IGLTFJsonObject`  
_L107-119_
- inherits: `IGLTFJsonObject`
- L109 _public member_ `float Value;`
- L111 _public function_ `FGLTFJsonIORExtension() : Value(1.5)`
- L116 _public function_ `bool HasValue() const`
- L118 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonSheenExtension`  
`struct FGLTFJsonSheenExtension : IGLTFJsonObject`  
_L121-138_
- inherits: `IGLTFJsonObject`
- L123 _public member_ `FGLTFJsonColor3 ColorFactor;`
- L124 _public member_ `FGLTFJsonTextureInfo ColorTexture;`
- L126 _public member_ `float RoughnessFactor;`
- L127 _public member_ `FGLTFJsonTextureInfo RoughnessTexture;`
- L129 _public function_ `FGLTFJsonSheenExtension() : ColorFactor(FGLTFJsonColor3::Black) , RoughnessFactor(0)`
- L135 _public function_ `bool HasValue() const`
- L137 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonTransmissionExtension`  
`struct FGLTFJsonTransmissionExtension : IGLTFJsonObject`  
_L140-153_
- inherits: `IGLTFJsonObject`
- L142 _public member_ `float Factor;` — transmissionFactor
- L143 _public member_ `FGLTFJsonTextureInfo Texture;` — transmissionTexture
- L145 _public function_ `FGLTFJsonTransmissionExtension() : Factor(0.f)`
- L150 _public function_ `bool HasValue() const`
- L152 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonSpecularGlossinessExtension`  
`struct FGLTFJsonSpecularGlossinessExtension : IGLTFJsonObject`  
_L155-174_
- inherits: `IGLTFJsonObject`
- L157 _public member_ `FGLTFJsonColor4 DiffuseFactor;`
- L158 _public member_ `FGLTFJsonTextureInfo DiffuseTexture;`
- L160 _public member_ `FGLTFJsonColor3 SpecularFactor;`
- L161 _public member_ `float GlossinessFactor;`
- L162 _public member_ `FGLTFJsonTextureInfo SpecularGlossinessTexture;`
- L164 _public function_ `FGLTFJsonSpecularGlossinessExtension() : DiffuseFactor(FGLTFJsonColor4::White) , SpecularFactor(FGLTFJsonColor3::White) , GlossinessFactor(1)`
- L171 _public function_ `bool HasValue() const`
- L173 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonIridescenceExtension`  
`struct FGLTFJsonIridescenceExtension : IGLTFJsonObject`  
_L176-199_
- inherits: `IGLTFJsonObject`
- L178 _public member_ `float IridescenceFactor;`
- L179 _public member_ `FGLTFJsonTextureInfo IridescenceTexture;`
- L180 _public member_ `float IridescenceIOR;`
- L182 _public member_ `float IridescenceThicknessMinimum;`
- L183 _public member_ `float IridescenceThicknessMaximum;`
- L184 _public member_ `FGLTFJsonTextureInfo IridescenceThicknessTexture;`
- L187 _public function_ `FGLTFJsonIridescenceExtension() : IridescenceFactor(0.f) , IridescenceIOR(1.3f) , IridescenceThicknessMinimum(100.f) , IridescenceThicknessMaximum(400.f)`
- L195 _public function_ `bool HasValue() const`
- L198 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonAnisotropyExtension`  
`struct FGLTFJsonAnisotropyExtension : IGLTFJsonObject`  
_L201-210_
- inherits: `IGLTFJsonObject`
- L203 _public member_ `float AnisotropyStrength = 0.0f;`
- L204 _public member_ `float AnisotropyRotation = 0.0f;`
- L205 _public member_ `FGLTFJsonTextureInfo AnisotropyTexture;`
- L207 _public function_ `bool HasValue() const`
- L209 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonMaterial`  
`struct FGLTFJsonMaterial : IGLTFJsonIndexedObject`  
_L212-257_
- inherits: `IGLTFJsonIndexedObject`
- L214 _public member_ `FString Name;`
- L216 _public member_ `EGLTFJsonShadingModel ShadingModel;`
- L218 _public member_ `FGLTFJsonPBRMetallicRoughness PBRMetallicRoughness;`
- L219 _public member_ `FGLTFJsonSpecularGlossinessExtension PBRSpecularGlossiness;`
- L221 _public member_ `FGLTFJsonNormalTextureInfo NormalTexture;`
- L222 _public member_ `FGLTFJsonOcclusionTextureInfo OcclusionTexture;`
- L224 _public member_ `FGLTFJsonTextureInfo EmissiveTexture;`
- L225 _public member_ `FGLTFJsonColor3 EmissiveFactor;`
- L226 _public member_ `float EmissiveStrength;`
- L228 _public member_ `EGLTFJsonAlphaMode AlphaMode;`
- L229 _public member_ `float AlphaCutoff;`
- L231 _public member_ `bool DoubleSided;`
- L233 _public member_ `FGLTFJsonClearCoatExtension ClearCoat;`
- L234 _public member_ `FGLTFJsonSpecularExtension Specular;`
- L235 _public member_ `FGLTFJsonIORExtension IOR;`
- L236 _public member_ `FGLTFJsonSheenExtension Sheen;`
- L237 _public member_ `FGLTFJsonTransmissionExtension Transmission;`
- L238 _public member_ `FGLTFJsonIridescenceExtension Iridescence;`
- L239 _public member_ `FGLTFJsonAnisotropyExtension Anisotropy;`
- L241 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L247 _protected function_ `FGLTFJsonMaterial(int32 Index) : IGLTFJsonIndexedObject(Index) , ShadingModel(EGLTFJsonShadingModel::Default) , EmissiveFactor(FGLTFJsonColor3::Black) , EmissiveStrength(1.0f) , AlphaMode(EGLTFJsonAlphaMode::Opaque) , AlphaCutoff(0.5f) , DoubleSided(false)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonMaterialVariant.h` (Public)


#### struct `FGLTFJsonMaterialVariantMapping`  
`struct FGLTFJsonMaterialVariantMapping : IGLTFJsonObject`  
_L9-20_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `FGLTFJsonMaterial* Material;`
- L12 _public member_ `TArray<FGLTFJsonMaterialVariant*> Variants;`
- L14 _public function_ `FGLTFJsonMaterialVariantMapping() : Material(nullptr)`
- L19 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`

#### struct `FGLTFJsonMaterialVariant`  
`struct FGLTFJsonMaterialVariant : IGLTFJsonIndexedObject`  
_L22-36_
- inherits: `IGLTFJsonIndexedObject`
- L24 _public member_ `FString Name;`
- L26 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L32 _protected function_ `FGLTFJsonMaterialVariant(int32 Index) : IGLTFJsonIndexedObject(Index)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonMatrix.h` (Public)


#### struct `TGLTFJsonMatrix`  
`template <typename BaseType> struct TGLTFJsonMatrix : BaseType, IGLTFJsonArray`  
_L12-63_
- inherits: `BaseType,IGLTFJsonArray`
- L14 _public function_ `TGLTFJsonMatrix(const BaseType& Other) : BaseType(Other)`
- L19 _public function_ `TGLTFJsonMatrix& operator=(const BaseType& Other)`
- L25 _public function_ `bool operator==(const BaseType& Other) const`
- L38 _public function_ `bool operator!=(const BaseType& Other) const`
- L43 _public function_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const override`
- L51 _public function_ `bool IsNearlyEqual(const BaseType& Other, float Tolerance = KINDA_SMALL_NUMBER) const`

#### struct `FGLTFJsonMatrix2`  
`struct FGLTFJsonMatrix2 : TGLTFJsonMatrix<FGLTFMatrix2>`  
_L65-71_
- inherits: `TGLTFJsonMatrix<FGLTFMatrix2>`
- L67 _public member_ `static const FGLTFJsonMatrix2 Identity;`

#### struct `FGLTFJsonMatrix3`  
`struct FGLTFJsonMatrix3 : TGLTFJsonMatrix<FGLTFMatrix3>`  
_L73-79_
- inherits: `TGLTFJsonMatrix<FGLTFMatrix3>`
- L75 _public member_ `static const FGLTFJsonMatrix3 Identity;`

#### struct `FGLTFJsonMatrix4`  
`struct FGLTFJsonMatrix4 : TGLTFJsonMatrix<FGLTFMatrix4>`  
_L81-87_
- inherits: `TGLTFJsonMatrix<FGLTFMatrix4>`
- L83 _public member_ `static const FGLTFJsonMatrix4 Identity;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonMesh.h` (Public)


#### struct `FGLTFJsonTarget`  
`struct FGLTFJsonTarget : IGLTFJsonObject`  
_L11-25_
- inherits: `IGLTFJsonObject`
- desc: For MorphTargets
- L13 _public member_ `FGLTFJsonAccessor* Position;`
- L14 _public member_ `FGLTFJsonAccessor* Normal;`
- L16 _public function_ `FGLTFJsonTarget() : Position(nullptr) , Normal(nullptr)`
- L22 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L24 _public prototype_ `bool HasValue() const;`

#### struct `FGLTFJsonAttributes`  
`struct FGLTFJsonAttributes : IGLTFJsonObject`  
_L27-49_
- inherits: `IGLTFJsonObject`
- L29 _public member_ `FGLTFJsonAccessor* Position;`
- L30 _public member_ `FGLTFJsonAccessor* Color0;`
- L31 _public member_ `FGLTFJsonAccessor* Normal;`
- L32 _public member_ `FGLTFJsonAccessor* Tangent;`
- L34 _public member_ `TArray<FGLTFJsonAccessor*> TexCoords;`
- L35 _public member_ `TArray<FGLTFJsonAccessor*> Joints;`
- L36 _public member_ `TArray<FGLTFJsonAccessor*> Weights;`
- L38 _public function_ `FGLTFJsonAttributes() : Position(nullptr) , Color0(nullptr) , Normal(nullptr) , Tangent(nullptr)`
- L46 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L48 _public prototype_ `bool HasValue() const;`

#### struct `FGLTFJsonPrimitive`  
`struct FGLTFJsonPrimitive : IGLTFJsonObject`  
_L51-72_
- inherits: `IGLTFJsonObject`
- L53 _public member_ `FGLTFJsonAttributes Attributes;`
- L54 _public member_ `FGLTFJsonAccessor* Indices;`
- L55 _public member_ `FGLTFJsonMaterial* Material;`
- L56 _public member_ `EGLTFJsonPrimitiveMode Mode;`
- L58 _public member_ `TArray<FGLTFJsonMaterialVariantMapping> MaterialVariantMappings;`
- L60 _public member_ `TArray<FGLTFJsonTarget> Targets;` — MorphTargets
- L62 _public function_ `FGLTFJsonPrimitive() : Indices(nullptr) , Material(nullptr) , Mode(EGLTFJsonPrimitiveMode::Triangles)`
- L69 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L71 _public prototype_ `bool HasValue() const;`

#### struct `FGLTFJsonMesh`  
`struct FGLTFJsonMesh : IGLTFJsonIndexedObject`  
_L74-94_
- inherits: `IGLTFJsonIndexedObject`
- L76 _public member_ `FString Name;`
- L78 _public member_ `TArray<FGLTFJsonPrimitive> Primitives;`
- L80 _public member_ `TArray<FString> TargetNames;`
- L82 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L84 _public prototype_ `bool HasValue() const;`
- L90 _protected function_ `FGLTFJsonMesh(int32 Index) : IGLTFJsonIndexedObject(Index)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonNode.h` (Public)


#### struct `FGLTFJsonNode`  
`struct FGLTFJsonNode : FGLTFJsonTransform, IGLTFJsonIndexedObject`  
_L10-39_
- inherits: `FGLTFJsonTransform,IGLTFJsonIndexedObject`
- L12 _public member_ `FString Name;`
- L14 _public member_ `FGLTFJsonCamera* Camera;`
- L15 _public member_ `FGLTFJsonSkin* Skin;`
- L16 _public member_ `FGLTFJsonMesh* Mesh;`
- L17 _public member_ `FGLTFJsonLight* Light;`
- L18 _public member_ `FGLTFJsonLightMap* LightMap;`
- L19 _public member_ `FGLTFJsonLightIESInstance* LightIESInstance;`
- L21 _public member_ `TArray<FGLTFJsonNode*> Children;`
- L23 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L29 _protected function_ `FGLTFJsonNode(int32 Index) : IGLTFJsonIndexedObject(Index) , Camera(nullptr) , Skin(nullptr) , Mesh(nullptr) , Light(nullptr) , LightMap(nullptr) , LightIESInstance(nullptr)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonObject.h` (Public)


#### struct `IGLTFJsonObject`  
`struct IGLTFJsonObject : IGLTFJsonValue`  
_L9-14_
- inherits: `IGLTFJsonValue`
- L11 _public prototype_ `virtual void WriteValue(IGLTFJsonWriter& Writer) const override final;`
- L13 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonQuaternion.h` (Public)


#### struct `FGLTFJsonQuaternion`  
`struct FGLTFJsonQuaternion : TGLTFQuaternion<float>, IGLTFJsonArray`  
_L11-57_
- inherits: `TGLTFQuaternion<float>,IGLTFJsonArray`
- L13 _public member_ `static const TGLTFQuaternion Identity;`
- L15 _public function_ `FGLTFJsonQuaternion(const TGLTFQuaternion& Other) : TGLTFQuaternion(Other)`
- L20 _public function_ `FGLTFJsonQuaternion& operator=(const TGLTFQuaternion& Other)`
- L26 _public function_ `bool operator==(const TGLTFQuaternion& Other) const`
- L39 _public function_ `bool operator!=(const TGLTFQuaternion& Other) const`
- L44 _public function_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const override`
- L52 _public function_ `bool IsNearlyEqual(const TGLTFQuaternion& Other, float Tolerance = KINDA_SMALL_NUMBER) const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonRoot.h` (Public)


#### struct `FGLTFJsonRoot`  
`struct FGLTFJsonRoot : IGLTFJsonObject`  
_L26-68_
- inherits: `IGLTFJsonObject`
- L28 _public member_ `FGLTFJsonAsset Asset;`
- L30 _public member_ `FGLTFJsonExtensions Extensions;`
- L32 _public member_ `FGLTFJsonScene* DefaultScene;`
- L34 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonAccessor> Accessors;`
- L35 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonAnimation> Animations;`
- L36 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonBuffer> Buffers;`
- L37 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonBufferView> BufferViews;`
- L38 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonCamera> Cameras;`
- L39 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonMaterial> Materials;`
- L40 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonMesh> Meshes;` — Important! : FGLTFJsonMeshes are validated in "FGLTFJsonBuilder::ValidateAndFixGLTFJson" and any that's found invalid (has no value) it will be removed from the list and deleted.
- L42 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonNode> Nodes;` — Any references to said deleted item need to be removed as well (for example Nodes.Mesh (1 line below))
- L43 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonImage> Images;`
- L44 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonSampler> Samplers;`
- L45 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonScene> Scenes;`
- L46 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonSkin> Skins;`
- L47 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonTexture> Textures;`
- L48 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonLight> Lights;`
- L49 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonLightMap> LightMaps;`
- L50 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonLightIES> LightIESs;`
- L51 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonLightIESInstance> LightIESInstances;`
- L52 _public member_ `TGLTFJsonIndexedObjectArray<FGLTFJsonMaterialVariant> MaterialVariants;`
- L54 _public function_ `FGLTFJsonRoot() : DefaultScene(nullptr)`
- L59 _public prototype_ `FGLTFJsonRoot(FGLTFJsonRoot&&) = default;`
- L60 _public prototype_ `FGLTFJsonRoot& operator=(FGLTFJsonRoot&&) = default;`
- L62 _public prototype_ `FGLTFJsonRoot(const FGLTFJsonRoot&) = delete;`
- L63 _public prototype_ `FGLTFJsonRoot& operator=(const FGLTFJsonRoot&) = delete;`
- L65 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L67 _public prototype_ `void WriteJson(FArchive& Archive, bool bPrettyJson, float DefaultTolerance);`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonSampler.h` (Public)


#### struct `FGLTFJsonSampler`  
`struct FGLTFJsonSampler : IGLTFJsonIndexedObject`  
_L9-33_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `EGLTFJsonTextureFilter MinFilter;`
- L14 _public member_ `EGLTFJsonTextureFilter MagFilter;`
- L16 _public member_ `EGLTFJsonTextureWrap WrapS;`
- L17 _public member_ `EGLTFJsonTextureWrap WrapT;`
- L19 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L25 _protected function_ `FGLTFJsonSampler(int32 Index) : IGLTFJsonIndexedObject(Index) , MinFilter(EGLTFJsonTextureFilter::None) , MagFilter(EGLTFJsonTextureFilter::None) , WrapS(EGLTFJsonTextureWrap::Repeat) , WrapT(EGLTFJsonTextureWrap::Repeat)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonScene.h` (Public)


#### struct `FGLTFJsonScene`  
`struct FGLTFJsonScene : IGLTFJsonIndexedObject`  
_L9-25_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `TArray<FGLTFJsonNode*> Nodes;`
- L15 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L21 _protected function_ `FGLTFJsonScene(int32 Index) : IGLTFJsonIndexedObject(Index)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonSkin.h` (Public)


#### struct `FGLTFJsonSkin`  
`struct FGLTFJsonSkin : IGLTFJsonIndexedObject`  
_L9-30_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `FGLTFJsonAccessor* InverseBindMatrices;`
- L14 _public member_ `FGLTFJsonNode* Skeleton;`
- L16 _public member_ `TArray<FGLTFJsonNode*> Joints;`
- L18 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L24 _protected function_ `FGLTFJsonSkin(int32 Index) : IGLTFJsonIndexedObject(Index) , InverseBindMatrices(nullptr) , Skeleton(nullptr)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonTexture.h` (Public)


#### struct `FGLTFJsonTexture`  
`struct FGLTFJsonTexture : IGLTFJsonIndexedObject`  
_L9-29_
- inherits: `IGLTFJsonIndexedObject`
- L11 _public member_ `FString Name;`
- L13 _public member_ `FGLTFJsonSampler* Sampler;`
- L15 _public member_ `FGLTFJsonImage* Source;`
- L17 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L23 _protected function_ `FGLTFJsonTexture(int32 Index) : IGLTFJsonIndexedObject(Index) , Sampler(nullptr) , Source(nullptr)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonTextureTransform.h` (Public)


#### struct `FGLTFJsonTextureTransform`  
`struct FGLTFJsonTextureTransform : IGLTFJsonObject`  
_L9-29_
- inherits: `IGLTFJsonObject`
- L11 _public member_ `FGLTFJsonVector2 Offset;`
- L12 _public member_ `FGLTFJsonVector2 Scale;`
- L13 _public member_ `float Rotation;`
- L15 _public function_ `FGLTFJsonTextureTransform() : Offset(FGLTFJsonVector2::Zero) , Scale(FGLTFJsonVector2::One) , Rotation(0)`
- L22 _public prototype_ `virtual void WriteObject(IGLTFJsonWriter& Writer) const override;`
- L24 _public prototype_ `bool IsNearlyEqual(const FGLTFJsonTextureTransform& Other, float Tolerance = KINDA_SMALL_NUMBER) const;`
- L25 _public prototype_ `bool IsExactlyEqual(const FGLTFJsonTextureTransform& Other) const;`
- L27 _public prototype_ `bool IsNearlyDefault(float Tolerance = KINDA_SMALL_NUMBER) const;`
- L28 _public prototype_ `bool IsExactlyDefault() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonTransform.h` (Public)


#### struct `FGLTFJsonTransform`  
`struct FGLTFJsonTransform`  
_L9-46_
- L11 _public member_ `FGLTFJsonVector3 Translation;`
- L12 _public member_ `FGLTFJsonQuaternion Rotation;`
- L13 _public member_ `FGLTFJsonVector3 Scale;`
- L15 _public member_ `static const FGLTFJsonTransform Identity;`
- L17 _public function_ `FGLTFJsonTransform() : Translation(FGLTFJsonVector3::Zero) , Rotation(FGLTFJsonQuaternion::Identity) , Scale(FGLTFJsonVector3::One)`
- L24 _public function_ `bool operator==(const FGLTFJsonTransform& Other) const`
- L31 _public function_ `bool operator!=(const FGLTFJsonTransform& Other) const`
- L38 _public prototype_ `void WriteValue(IGLTFJsonWriter& Writer) const;`
- L40 _public function_ `bool IsNearlyEqual(const FGLTFJsonTransform& Other, float Tolerance = KINDA_SMALL_NUMBER) const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonValue.h` (Public)


#### struct `IGLTFJsonValue`  
`struct IGLTFJsonValue`  
_L9-14_
- L11 _public prototype_ `virtual ~IGLTFJsonValue() = default;`
- L13 _public prototype_ `virtual void WriteValue(IGLTFJsonWriter& Writer) const = 0;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonVector.h` (Public)


#### struct `TGLTFJsonVector`  
`template <typename BaseType> struct TGLTFJsonVector : BaseType, IGLTFJsonArray`  
_L12-63_
- inherits: `BaseType,IGLTFJsonArray`
- L14 _public function_ `TGLTFJsonVector(const BaseType& Other) : BaseType(Other)`
- L19 _public function_ `TGLTFJsonVector& operator=(const BaseType& Other)`
- L25 _public function_ `bool operator==(const BaseType& Other) const`
- L38 _public function_ `bool operator!=(const BaseType& Other) const`
- L43 _public function_ `virtual void WriteArray(IGLTFJsonWriter& Writer) const override`
- L51 _public function_ `bool IsNearlyEqual(const BaseType& Other, float Tolerance = KINDA_SMALL_NUMBER) const`

#### struct `FGLTFJsonVector2`  
`struct FGLTFJsonVector2 : TGLTFJsonVector<FGLTFVector2>`  
_L65-72_
- inherits: `TGLTFJsonVector<FGLTFVector2>`
- L67 _public member_ `static const FGLTFJsonVector2 Zero;`
- L68 _public member_ `static const FGLTFJsonVector2 One;`

#### struct `FGLTFJsonVector3`  
`struct FGLTFJsonVector3 : TGLTFJsonVector<FGLTFVector3>`  
_L74-81_
- inherits: `TGLTFJsonVector<FGLTFVector3>`
- L76 _public member_ `static const FGLTFJsonVector3 Zero;`
- L77 _public member_ `static const FGLTFJsonVector3 One;`

#### struct `FGLTFJsonVector4`  
`struct FGLTFJsonVector4 : TGLTFJsonVector<FGLTFVector4>`  
_L83-90_
- inherits: `TGLTFJsonVector<FGLTFVector4>`
- L85 _public member_ `static const FGLTFJsonVector4 Zero;`
- L86 _public member_ `static const FGLTFJsonVector4 One;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Json/GLTFJsonWriter.h` (Public)


#### class `IGLTFJsonWriter`  
`class IGLTFJsonWriter`  
_L12-265_
- L16 _public member_ `float DefaultTolerance;`
- L18 _public member_ `FGLTFJsonExtensions& Extensions;`
- L20 _public function_ `IGLTFJsonWriter(FGLTFJsonExtensions& Extensions) : DefaultTolerance(0) , Extensions(Extensions)`
- L26 _public prototype_ `static TSharedRef<IGLTFJsonWriter> Create(FArchive& Archive, bool bPrettyJson, FGLTFJsonExtensions& Extensions);`
- L28 _public prototype_ `virtual ~IGLTFJsonWriter() = default;`
- L30 _public prototype_ `virtual void Close() = 0;`
- L32 _public prototype_ `virtual void Write(bool Boolean) = 0;`
- L33 _public prototype_ `virtual void Write(int32 Number) = 0;`
- L34 _public prototype_ `virtual void Write(int64 Number) = 0;`
- L35 _public prototype_ `virtual void Write(float Number) = 0;`
- L36 _public prototype_ `virtual void Write(const FString& String) = 0;`
- L37 _public prototype_ `virtual void Write(TYPE_OF_NULLPTR) = 0;`
- L38 _public prototype_ `virtual void SetIdentifier(const FString& Identifier) = 0;`
- L40 _public prototype_ `virtual void StartObject() = 0;`
- L41 _public prototype_ `virtual void EndObject() = 0;`
- L42 _public prototype_ `virtual void StartArray() = 0;`
- L43 _public prototype_ `virtual void EndArray() = 0;`
- L45 _public function_ `void Write(const TCHAR* String)`
- L50 _public function_ `void Write(const IGLTFJsonValue& Value)`
- L55 _public function_ `void Write(const IGLTFJsonIndexedObject* Object)`
- L68 _public function_ `template <typename EnumType, typename = typename TEnableIf<TIsEnum<EnumType>::Value>::Type> void Write(EnumType Enum)`
- L74 _public function_ `template <class ElementType, typename = typename TEnableIf<!std::is_same_v<ElementType, TCHAR>>::Type> void Write(const ElementType* Array, SIZE_T ArraySize)`
- L85 _public function_ `template <class ElementType, SIZE_T ArraySize, typename = typename TEnableIf<!std::is_same_v<ElementType, TCHAR>>::Type> void Write(const ElementType (&Array)[ArraySize])`
- L91 _public function_ `template <class ElementType> void Write(const TUniquePtr<ElementType>& Pointer)`
- L104 _public function_ `template <class ElementType> void Write(const TArray<ElementType>& Array)`
- L115 _public function_ `template <class ElementType> void Write(const TSet<ElementType>& Set)`
- L125 _public function_ `void Write(const FString& Identifier, bool Boolean)`
- L131 _public function_ `void Write(const FString& Identifier, int32 Number)`
- L137 _public function_ `void Write(const FString& Identifier, int64 Number)`
- L143 _public function_ `void Write(const FString& Identifier, float Number)`
- L149 _public function_ `void Write(const FString& Identifier, const FString& String)`
- L155 _public function_ `void Write(const FString& Identifier, const TCHAR* String)`
- L161 _public function_ `void Write(const FString& Identifier, const IGLTFJsonValue& Value)`
- L167 _public function_ `void Write(const FString& Identifier, const IGLTFJsonIndexedObject* Value)`
- L174 _public function_ `template <typename EnumType, typename = typename TEnableIf<TIsEnum<EnumType>::Value>::Type> void Write(const FString& Identifier, EnumType Enum)`
- L181 _public function_ `template <class ElementType, typename = typename TEnableIf<!std::is_same_v<ElementType, TCHAR>>::Type> void Write(const FString& Identifier, const ElementType* Array, SIZE_T ArraySize)`
- L188 _public function_ `template <class ElementType, SIZE_T ArraySize, typename = typename TEnableIf<!std::is_same_v<ElementType, TCHAR>>::Type> void Write(const FString& Identifier, const ElementType (&Array)[ArraySize])`
- L195 _public function_ `template <class ElementType> void Write(const FString& Identifier, const TUniquePtr<ElementType>& Pointer)`
- L202 _public function_ `template <class ElementType> void Write(const FString& Identifier, const TArray<ElementType>& Array)`
- L209 _public function_ `template <class ElementType> void Write(const FString& Identifier, const TSet<ElementType>& Set)`
- L215 _public function_ `void StartObject(const FString& Identifier)`
- L221 _public function_ `void StartArray(const FString& Identifier)`
- L227 _public function_ `void StartExtensions()`
- L232 _public function_ `void EndExtensions()`
- L237 _public function_ `void Write(const EGLTFJsonExtension& Extension, const IGLTFJsonValue& Value, bool bIsRequired = false)`
- L249 _public function_ `void StartExtension(const EGLTFJsonExtension& Extension, bool bIsRequired = false)`
- L261 _public function_ `void EndExtension()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Options/GLTFExportOptions.h` (Public)


#### enum `EGLTFTextureImageFormat`  
`enum class EGLTFTextureImageFormat : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `None` — Don't export any textures.
- L17 _public enumerator_ `PNG` — Always use PNG (lossless compression).
- L19 _public enumerator_ `JPEG UMETA(DisplayName = "JPEG (if no alpha)")` — If texture does not have an alpha channel, use JPEG (lossy compression); otherwise fallback to PNG.

#### enum `EGLTFMaterialVariantMode`  
`enum class EGLTFMaterialVariantMode : uint8`  
_L23-31_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `None` — Never export material variants.
- L28 _public enumerator_ `Simple` — Export material variants but only use a simple quad if a material input needs to be baked out.
- L30 _public enumerator_ `UseMeshData` — Export material variants and allow usage of the mesh data if a material input needs to be baked out with vertex data.

#### class `UGLTFExportOptions`  
`class UGLTFExportOptions : public UObject`  
_L34-182_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=EditorPerProjectUserSettings, HideCategories=(DebugProperty))`
- inherits: `UObject`
- L40 _private member_ `float ExportUniformScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = General)` — Scale factor used for exporting all assets (0.01 by default) for conversion from centimeters (Unreal default) to meters (glTF).
- L44 _private member_ `bool bExportPreviewMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = General)` — If enabled, the preview mesh for a standalone animation or material asset will also be exported.
- L48 _private member_ `bool bSkipNearDefaultValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = General, AdvancedDisplay)` — If enabled, floating-point-based JSON properties that are nearly equal to their default value will not be exported and thus regarded as exactly default, reducing JSON size.
- L52 _private member_ `bool bIncludeCopyrightNotice;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = General, AdvancedDisplay)` — If enabled, the copyright notice from project settings will be included as metadata in the glTF asset.
- L56 _private member_ `bool bExportProxyMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials that have a proxy defined in their user data, will be exported using that proxy instead. This setting won't affect proxy materials exported or referenced directly.
- L60 _private member_ `bool bUseImporterMaterialMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials imported with the Interchange-glTF importer will be directly mapped for the Exporter. bExport material options below will be ignored.
- L64 _private member_ `bool bExportUnlitMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials with shading model unlit will be properly exported. Uses extension KHR_materials_unlit.
- L68 _private member_ `bool bExportClearCoatMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials with shading model clear coat will be properly exported. Uses extension KHR_materials_clearcoat.
- L72 _private member_ `bool bExportClothMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials with shading model cloth will be properly exported. Uses extension KHR_materials_sheen.
- L76 _private member_ `bool bExportThinTranslucentMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials with shading model thin translucency will be exported. Export is only partial. Uses extension KHR_materials_transmission.
- L80 _private member_ `bool bExportSpecularGlossinessMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials using the Importer's SpecularGlossiness material function will be exported. Uses extension KHR_materials_pbrSpecularGlossiness.
- L84 _private member_ `bool bExportEmissiveStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, allows materials to have an emissive factor that exceeds the standard range [0.0, 1.0]. Uses extension KHR_materials_emissive_strength.
- L88 _private member_ `EGLTFMaterialBakeMode BakeMaterialInputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — Bake mode determining if and how a material input is baked out to a texture. Baking is only used for non-trivial material inputs (i.e. not simple texture or constant expressions).
- L92 _private member_ `FGLTFMaterialBakeSize DefaultMaterialBakeSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "BakeMaterialInputs != EGLTFMaterialBakeMode::Disabled"))` — Default size of the baked out texture (containing the material input). Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L96 _private member_ `TEnumAsByte<TextureFilter> DefaultMaterialBakeFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "BakeMaterialInputs != EGLTFMaterialBakeMode::Disabled", ValidEnumValues = "TF_Nearest, TF_Bilinear, TF_Trilinear"))` — Default filtering mode used when sampling the baked out texture. Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L100 _private member_ `TEnumAsByte<TextureAddress> DefaultMaterialBakeTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "BakeMaterialInputs != EGLTFMaterialBakeMode::Disabled"))` — Default addressing mode used when sampling the baked out texture. Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L104 _private member_ `TMap<EGLTFMaterialPropertyGroup, FGLTFOverrideMaterialBakeSettings> DefaultInputBakeSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "BakeMaterialInputs != EGLTFMaterialBakeMode::Disabled"))` — Input-specific default bake settings that override the general defaults above.
- L108 _private member_ `int32 DefaultLevelOfDetail;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh, Meta = (ClampMin = "0"))` — Default LOD level used for exporting a mesh. Can be overridden by component or asset settings (e.g. minimum or forced LOD level).
- L112 _private member_ `bool bExportSourceModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, exports the SourceModel. If false, exports the Render Data.
- L116 _private member_ `bool bExportVertexColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, export vertex color. Not recommended due to vertex colors always being used as a base color multiplier in glTF, regardless of material. Often producing undesirable results.
- L120 _private member_ `bool bExportVertexSkinWeights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, export vertex bone weights and indices in skeletal meshes. Necessary for animation sequences.
- L124 _private member_ `bool bMakeSkinnedMeshesRoot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, make skeletal meshes into root nodes to strictly comply with the glTF specification. Final bone transforms remain the same and visual results are unaffected.
- L128 _private member_ `bool bUseMeshQuantization;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, use quantization for vertex tangents and normals, reducing size. Requires extension KHR_mesh_quantization, which may result in the mesh not loading in some glTF viewers.
- L132 _private member_ `bool bExportMorphTargets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Mesh)` — If enabled, exports Morph Targets.
- L136 _private member_ `bool bExportLevelSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Animation)` — If enabled, export level sequences. Only transform tracks are currently supported. The level sequence will be played at the assigned display rate.
- L140 _private member_ `bool bExportAnimationSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Animation, Meta = (EditCondition = "bExportVertexSkinWeights"))` — If enabled, export single animation asset used by a skeletal mesh component. Export of vertex skin weights must be enabled.
- L144 _private member_ `EGLTFTextureImageFormat TextureImageFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Texture)` — Desired image format used for exported textures.
- L148 _private member_ `int32 TextureImageQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Texture, Meta = (ClampMin = "0", ClampMax = "100", EditCondition = "TextureImageFormat == EGLTFTextureImageFormat::JPEG"))` — Level of compression used for textures exported with lossy image formats, 0 (default) or value between 1 (worst quality, best compression) and 100 (best quality, worst compression).
- L152 _private member_ `bool bExportTextureTransforms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Texture, Meta = (EditCondition = "TextureImageFormat != EGLTFTextureImageFormat::None"))` — If enabled, export UV offset and scale/tiling used in materials. Uses extension KHR_texture_transform.
- L156 _private member_ `bool bExportLightmaps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Texture, Meta = (EditCondition = "TextureImageFormat != EGLTFTextureImageFormat::None"))` — If enabled, export lightmaps (created by Lightmass) when exporting a level. Uses extension EPIC_lightmap_textures, which is supported by Unreal's glTF viewer.
- L160 _private member_ `bool bAdjustNormalmaps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Texture, Meta = (EditCondition = "TextureImageFormat != EGLTFTextureImageFormat::None"))` — If enabled, exported normalmaps will be adjusted from Unreal to glTF convention (i.e. the green channel is flipped).
- L164 _private member_ `bool bExportHiddenInGame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Scene)` — If enabled, export actors and components that are flagged as hidden in-game.
- L170 _private member_ `bool bExportLights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Scene)` — If enabled, export directional, point, and spot light components. Uses extension KHR_lights_punctual. Also exports IES light profiles using the EXT_lights_ies extension.
- L174 _private member_ `bool bExportCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Scene)` — If enabled, export camera components.
- L178 _private member_ `EGLTFMaterialVariantMode ExportMaterialVariants;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = VariantSets, Meta = (EditCondition = "VariantSetsMode != EGLTFVariantSetsMode::None"))` — Mode determining if and how to export material variants that change the materials property on a static or skeletal mesh component.
- L181 _private prototype_ `void ResetToDefault();` — `UFUNCTION(BlueprintCallable, Category = General)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Options/GLTFProxyOptions.h` (Public)


#### class `UGLTFProxyOptions`  
`class UGLTFProxyOptions : public UObject`  
_L11-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=EditorPerProjectUserSettings, HideCategories=(DebugProperty))`
- inherits: `UObject`
- L17 _private member_ `bool bBakeMaterialInputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, a material input may be baked out to a texture (using a simple quad). Baking is only used for non-trivial material inputs (i.e. not simple texture or constant expressions).
- L21 _private member_ `bool bUseThinTranslucentShadingModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material)` — If enabled, materials with shading model thin translucency will be used. Conversion is only partial.
- L25 _private member_ `FGLTFMaterialBakeSize DefaultMaterialBakeSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "bBakeMaterialInputs"))` — Default size of the baked out texture (containing the material input). Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L29 _private member_ `TEnumAsByte<TextureFilter> DefaultMaterialBakeFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "bBakeMaterialInputs", ValidEnumValues = "TF_Nearest, TF_Bilinear, TF_Trilinear"))` — Default filtering mode used when sampling the baked out texture. Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L33 _private member_ `TEnumAsByte<TextureAddress> DefaultMaterialBakeTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "bBakeMaterialInputs"))` — Default addressing mode used when sampling the baked out texture. Can be overridden by material- and input-specific bake settings, see GLTFMaterialExportOptions.
- L37 _private member_ `TMap<EGLTFMaterialPropertyGroup, FGLTFOverrideMaterialBakeSettings> DefaultInputBakeSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = Material, Meta = (EditCondition = "bBakeMaterialInputs"))` — Input-specific default bake settings that override the general defaults above.
- L40 _private prototype_ `void ResetToDefault();` — `UFUNCTION(BlueprintCallable, Category = General)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Tasks/GLTFDelayedTask.h` (Public)


#### enum `EGLTFTaskPriority`  
`enum class EGLTFTaskPriority : uint8`  
_L7-14_
- L9 _public enumerator_ `Animation`
- L10 _public enumerator_ `Mesh`
- L11 _public enumerator_ `Material`
- L12 _public enumerator_ `Texture`
- L13 _public enumerator_ `MAX`

#### class `FGLTFDelayedTask`  
`class FGLTFDelayedTask`  
_L16-32_
- L20 _public member_ `const EGLTFTaskPriority Priority;`
- L22 _public function_ `FGLTFDelayedTask(EGLTFTaskPriority Priority) : Priority(Priority)`
- L27 _public prototype_ `virtual ~FGLTFDelayedTask() = default;`
- L29 _public prototype_ `virtual FString GetName() = 0;`
- L31 _public prototype_ `virtual void Process() = 0;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/UserData/GLTFMaterialUserData.h` (Public)


#### enum `EGLTFMaterialBakeMode`  
`enum class EGLTFMaterialBakeMode : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Disabled` — Never bake material inputs.
- L19 _public enumerator_ `Simple` — Only use a simple quad if a material input needs to be baked out.
- L21 _public enumerator_ `UseMeshData` — Allow usage of the mesh data if a material input needs to be baked out with vertex data.

#### enum `EGLTFMaterialPropertyGroup`  
`enum class EGLTFMaterialPropertyGroup : uint8`  
_L25-36_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `None UMETA(DisplayName = "None")`
- L29 _public enumerator_ `BaseColorOpacity UMETA(DisplayName = "Base Color + Opacity (Mask)")`
- L30 _public enumerator_ `MetallicRoughness UMETA(DisplayName = "Metallic + Roughness")`
- L31 _public enumerator_ `EmissiveColor UMETA(DisplayName = "Emissive Color")`
- L32 _public enumerator_ `Normal UMETA(DisplayName = "Normal")`
- L33 _public enumerator_ `AmbientOcclusion UMETA(DisplayName = "Ambient Occlusion")`
- L34 _public enumerator_ `ClearCoatRoughness UMETA(DisplayName = "Clear Coat + Clear Coat Roughness")`
- L35 _public enumerator_ `ClearCoatBottomNormal UMETA(DisplayName = "Clear Coat Bottom Normal")`

#### struct `FGLTFMaterialBakeSize`  
`struct FGLTFMaterialBakeSize`  
_L39-54_
- reflection: `USTRUCT(Blueprintable)`
- L44 _public member_ `int32 X = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")`
- L47 _public member_ `int32 Y = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")`
- L51 _public member_ `bool bAutoDetect = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")` — If enabled, bake size is based on the largest texture used in the material input's expression graph. If none found, bake size will fall back to the explicit dimensions.
- L53 _public member_ `static FGLTFMaterialBakeSize Default;`

#### struct `FGLTFOverrideMaterialBakeSettings`  
`struct FGLTFOverrideMaterialBakeSettings`  
_L57-86_
- reflection: `USTRUCT(Blueprintable)`
- L61 _public prototype_ `FGLTFOverrideMaterialBakeSettings();`
- L65 _public member_ `bool bOverrideSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (InlineEditConditionToggle))` — If enabled, default size will be overridden by the corresponding property.
- L69 _public member_ `FGLTFMaterialBakeSize Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (EditCondition = "bOverrideSize"))` — Overrides default size of the baked out texture.
- L73 _public member_ `bool bOverrideFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (InlineEditConditionToggle))` — If enabled, default filtering mode will be overridden by the corresponding property.
- L77 _public member_ `TEnumAsByte<TextureFilter> Filter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (EditCondition = "bOverrideFilter", ValidEnumValues = "TF_Nearest, TF_Bilinear, TF_Trilinear"))` — Overrides the default filtering mode used when sampling the baked out texture.
- L81 _public member_ `bool bOverrideTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (InlineEditConditionToggle))` — If enabled, default addressing mode will be overridden by the corresponding property.
- L85 _public member_ `TEnumAsByte<TextureAddress> Tiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (EditCondition = "bOverrideTiling"))` — Overrides the default addressing mode used when sampling the baked out texture.

#### class `UGLTFMaterialExportOptions`  
`class UGLTFMaterialExportOptions : public UAssetUserData`  
_L90-120_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "GLTF Material Export Options"))`
- inherits: `UAssetUserData`
- desc: glTF-specific user data that can be added to material assets to override export options
- L100 _public member_ `TObjectPtr<UMaterialInterface> Proxy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")` — If assigned, export will use the proxy instead of the original material.
- L104 _public member_ `FGLTFOverrideMaterialBakeSettings Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Bake Settings", meta = (ShowOnlyInnerProperties))` — Default bake settings for this material in general.
- L108 _public member_ `TMap<EGLTFMaterialPropertyGroup, FGLTFOverrideMaterialBakeSettings> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Bake Settings")` — Input-specific bake settings that override the defaults above.
- L110 _public prototype_ `static const UMaterialInterface* ResolveProxy(const UMaterialInterface* Material);`
- L112 _public prototype_ `static FGLTFMaterialBakeSize GetBakeSizeForPropertyGroup(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup, FGLTFMaterialBakeSize DefaultValue);`
- L113 _public prototype_ `static TextureFilter GetBakeFilterForPropertyGroup(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup, TextureFilter DefaultValue);`
- L114 _public prototype_ `static TextureAddress GetBakeTilingForPropertyGroup(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup, TextureAddress DefaultValue);`
- L119 _private prototype_ `template <typename Predicate> static const FGLTFOverrideMaterialBakeSettings* GetBakeSettingsByPredicate(const UMaterialInterface* Material, EGLTFMaterialPropertyGroup PropertyGroup, Predicate Pred);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/GLTFCoreUtilities.h` (Public)


#### struct `FGLTFCoreUtilities`  
`struct FGLTFCoreUtilities`  
_L20-91_
- L22 _public prototype_ `static float ConvertLength(const float Length, const float ConversionScale = 0.01);`
- L24 _public prototype_ `static FGLTFVector3 ConvertVector(const FVector3f& Vector);`
- L26 _public prototype_ `static FGLTFVector3 ConvertPosition(const FVector3f& Position, const float ConversionScale = 0.01);`
- L28 _public prototype_ `static FGLTFVector3 ConvertScale(const FVector3f& Scale);`
- L30 _public prototype_ `static FGLTFVector3 ConvertNormal(const FVector3f& Normal);`
- L31 _public prototype_ `static FGLTFInt8Vector4 ConvertNormal(const FPackedNormal& Normal);`
- L32 _public prototype_ `static FGLTFInt16Vector4 ConvertNormal(const FPackedRGBA16N& Normal);`
- L34 _public prototype_ `static FGLTFVector3 ConvertNormalDelta(const FVector3f& NormalDelta);`
- L35 _public prototype_ `static FGLTFInt8Vector4 ConvertNormalDelta(const FPackedNormal& NormalDelta);`
- L36 _public prototype_ `static FGLTFInt16Vector4 ConvertNormalDelta(const FPackedRGBA16N& NormalDelta);`
- L38 _public prototype_ `static FGLTFVector4 ConvertTangent(const FVector3f& Tangent, const FVector4f& Normal = FVector4f(ForceInitToZero));`
- L39 _public prototype_ `static FGLTFVector4 ConvertTangent(const FVector4f& Tangent);`
- L40 _public prototype_ `static FGLTFInt8Vector4 ConvertTangent(const FPackedNormal& Tangent, const FPackedNormal& Normal = FPackedNormal());`
- L41 _public prototype_ `static FGLTFInt16Vector4 ConvertTangent(const FPackedRGBA16N& Tangent, const FPackedRGBA16N& Normal = FPackedRGBA16N());`
- L43 _public prototype_ `static FGLTFVector2 ConvertUV(const FVector2f& UV);`
- L44 _public prototype_ `static FGLTFVector2 ConvertUV(const FVector2DHalf& UV);`
- L46 _public prototype_ `static FGLTFColor4 ConvertColor(const FLinearColor& Color);`
- L47 _public prototype_ `static FGLTFColor3 ConvertColor3(const FLinearColor& Color);`
- L48 _public prototype_ `static FGLTFUInt8Color4 ConvertColor(const FColor& Color);`
- L50 _public prototype_ `static FGLTFQuaternion ConvertRotation(const FRotator3f& Rotation);`
- L51 _public prototype_ `static FGLTFQuaternion ConvertRotation(const FQuat4f& Rotation);`
- L53 _public prototype_ `static FGLTFMatrix4 ConvertMatrix(const FMatrix44f& Matrix);`
- L55 _public prototype_ `static FGLTFMatrix4 ConvertTransform(const FTransform3f& Transform, const float ConversionScale = 0.01);`
- L57 _public prototype_ `static float ConvertFieldOfView(float FOVInDegrees, float AspectRatio);`
- L59 _public prototype_ `static float ConvertLightAngle(const float Angle);`
- L61 _public prototype_ `static FGLTFQuaternion GetLocalCameraRotation();`
- L62 _public prototype_ `static FGLTFQuaternion GetLocalLightRotation();`
- L64 _public prototype_ `static EGLTFJsonCameraType ConvertCameraType(ECameraProjectionMode::Type ProjectionMode);`
- L65 _public prototype_ `static EGLTFJsonLightType ConvertLightType(ELightComponentType ComponentType);`
- L67 _public prototype_ `static EGLTFJsonInterpolation ConvertInterpolation(const EAnimInterpolationType Type);`
- L69 _public prototype_ `static EGLTFJsonShadingModel ConvertShadingModel(EMaterialShadingModel ShadingModel);`
- L70 _public prototype_ `static FString GetShadingModelString(EGLTFJsonShadingModel ShadingModel);`
- L72 _public prototype_ `static EGLTFJsonAlphaMode ConvertAlphaMode(EBlendMode Mode);`
- L74 _public prototype_ `static EGLTFJsonTextureWrap ConvertWrap(TextureAddress Address);`
- L76 _public prototype_ `static EGLTFJsonTextureFilter ConvertMinFilter(TextureFilter Filter);`
- L77 _public prototype_ `static EGLTFJsonTextureFilter ConvertMagFilter(TextureFilter Filter);`
- L80 _public function_ `template <typename ComponentType> static EGLTFJsonComponentType GetComponentType()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/GLTFJsonUtilities.h` (Public)


#### struct `FGLTFJsonUtilities`  
`struct FGLTFJsonUtilities`  
_L10-27_
- L13 _public function_ `template <typename EnumType, typename = typename TEnableIf<TIsEnum<EnumType>::Value>::Type> static int32 GetValue(EnumType Enum)`
- L18 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonExtension Enum);`
- L19 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonAlphaMode Enum);`
- L20 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonMimeType Enum);`
- L21 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonAccessorType Enum);`
- L22 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonCameraType Enum);`
- L23 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonLightType Enum);`
- L24 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonInterpolation Enum);`
- L25 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonTargetPath Enum);`
- L26 _public prototype_ `static const TCHAR* GetValue(EGLTFJsonShadingModel Enum);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/GLTFLandscapeComponentDataInterface.h` (Public)


#### struct `FGLTFLandscapeComponentDataInterface`  
`struct FGLTFLandscapeComponentDataInterface`  
_L10-61_
- L13 _protected member_ `int32 ComponentSubsectionSizeQuads = 0;`
- L14 _protected member_ `int32 ComponentSizeQuads = 0;`
- L15 _protected member_ `int32 ComponentSizeVerts = 0;`
- L16 _protected member_ `int32 ComponentSubsectionSizeVerts = 0;`
- L17 _protected member_ `int32 ComponentNumSubsections = 0;`
- L19 _protected member_ `TArray64<uint8> HeightMipDataSource;`
- L20 _protected member_ `FColor* HeightMipData = nullptr;`
- L21 _protected member_ `int32 HeightmapStride = 0;`
- L22 _protected member_ `int32 HeightmapComponentOffsetX = 0;`
- L23 _protected member_ `int32 HeightmapComponentOffsetY = 0;`
- L24 _protected member_ `int32 HeightmapSubsectionOffset = 0;`
- L26 _protected member_ `TArray64<uint8> XYOffsetMipDataSource;`
- L27 _protected member_ `FColor* XYOffsetMipData = nullptr;`
- L29 _protected member_ `const ULandscapeComponent& Component;`
- L30 _protected member_ `int32 MipLevel;`
- L33 _public prototype_ `FGLTFLandscapeComponentDataInterface(const ULandscapeComponent& Component, int32 ExportLOD);`
- L35 _public prototype_ `void ComponentXYToSubsectionXY(int32 CompX, int32 CompY, int32& SubNumX, int32& SubNumY, int32& SubX, int32& SubY) const;`
- L37 _public prototype_ `int32 TexelXYToIndex(int32 TexelX, int32 TexelY) const;`
- L39 _public prototype_ `void VertexXYToTexelXY(int32 VertX, int32 VertY, int32& OutX, int32& OutY) const;`
- L41 _public prototype_ `void VertexIndexToXY(int32 VertexIndex, int32& OutX, int32& OutY) const;`
- L43 _public prototype_ `int32 VertexIndexToTexel(int32 VertexIndex) const;`
- L45 _public prototype_ `bool GetWeightmapTextureData(ULandscapeLayerInfoObject* InLayerInfo, TArray<uint8>& OutData, bool bInUseEditingWeightmap = false, bool bInRemoveSubsectionDuplicates = false);`
- L49 _public prototype_ `FColor GetHeightData(int32 LocalX, int32 LocalY) const;`
- L52 _public prototype_ `FColor GetXYOffsetData(int32 LocalX, int32 LocalY) const;` — `UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes")`
- L55 _public prototype_ `void GetXYOffset(int32 X, int32 Y, float& XOffset, float& YOffset) const;` — `UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes")`
- L57 _public prototype_ `void GetPositionNormalUV(int32 LocalX, int32 LocalY, FVector3f& Position, FVector3f& Normal, FVector2f& UV) const;`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/GLTFProxyMaterialUtilities.h` (Public)


#### class `FGLTFProxyMaterialUtilities`  
`class FGLTFProxyMaterialUtilities`  
_L18-55_
- L23 _public prototype_ `static UMaterialInstanceConstant* CreateProxyMaterial(EGLTFJsonShadingModel ShadingModel, UObject* Outer = GetTransientPackage(), FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags);`
- L26 _public prototype_ `static bool IsProxyMaterial(const UMaterial* Material);`
- L27 _public prototype_ `static bool IsProxyMaterial(const UMaterialInterface* Material);`
- L29 _public prototype_ `static UMaterial* GetBaseMaterial(EGLTFJsonShadingModel ShadingModel);`
- L31 _public prototype_ `static UMaterialInterface* GetProxyMaterial(UMaterialInterface* OriginalMaterial);`
- L32 _public prototype_ `static void SetProxyMaterial(UMaterialInterface* OriginalMaterial, UMaterialInterface* ProxyMaterial);`
- L34 _public prototype_ `static bool GetParameterValue(const UMaterialInterface* Material, const FHashedMaterialParameterInfo& ParameterInfo, float& OutValue, bool NonDefaultOnly = false);`
- L35 _public prototype_ `static bool GetParameterValue(const UMaterialInterface* Material, const FHashedMaterialParameterInfo& ParameterInfo, FLinearColor& OutValue, bool NonDefaultOnly = false);`
- L36 _public prototype_ `static bool GetParameterValue(const UMaterialInterface* Material, const FHashedMaterialParameterInfo& ParameterInfo, UTexture*& OutValue, bool NonDefaultOnly = false);`
- L39 _public prototype_ `static void SetParameterValue(UMaterialInstanceConstant* Material, const FHashedMaterialParameterInfo& ParameterInfo, float Value, bool NonDefaultOnly = false);`
- L40 _public prototype_ `static void SetParameterValue(UMaterialInstanceConstant* Material, const FHashedMaterialParameterInfo& ParameterInfo, const FLinearColor& Value, bool NonDefaultOnly = false);`
- L41 _public prototype_ `static void SetParameterValue(UMaterialInstanceConstant* Material, const FHashedMaterialParameterInfo& ParameterInfo, UTexture* Value, bool NonDefaultOnly = false);`
- L44 _public prototype_ `static bool GetTwoSided(const UMaterialInterface* Material, bool& OutValue, bool NonDefaultOnly = false);`
- L45 _public prototype_ `static bool GetIsThinSurface(const UMaterialInterface* Material, bool& OutValue, bool NonDefaultOnly = false);`
- L46 _public prototype_ `static bool GetBlendMode(const UMaterialInterface* Material, EBlendMode& OutValue, bool NonDefaultOnly = false);`
- L47 _public prototype_ `static bool GetOpacityMaskClipValue(const UMaterialInterface* Material, float& OutValue, bool NonDefaultOnly = false);`
- L50 _public prototype_ `static void SetTwoSided(UMaterialInstanceConstant* Material, bool Value, bool NonDefaultOnly = false);`
- L51 _public prototype_ `static void SetIsThinSurface(UMaterialInstanceConstant* Material, bool Value, bool NonDefaultOnly = false);`
- L52 _public prototype_ `static void SetBlendMode(UMaterialInstanceConstant* Material, EBlendMode Value, bool NonDefaultOnly = false);`
- L53 _public prototype_ `static void SetOpacityMaskClipValue(UMaterialInstanceConstant* Material, float Value, bool NonDefaultOnly = false);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GLTFEXPORTER_API`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/MeshAttributesArray.h` (Public)


#### class `FMeshAttributesArray`  
`template <typename T> class FMeshAttributesArray : public TArray<T>`  
_L8-24_
- inherits: `TArray<T>`

#### Free symbols / members of external scopes

- L15 _function_ `friend uint32 GetTypeHash(const FMeshAttributesArray& AttributesArray)`

### `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Utilities/MeshParsingUtilities.h` (Public)


#### struct `UE::MeshParser::FPrimitiveTargetDescription`  
`struct FPrimitiveTargetDescription`  
_L17-24_
- L19 _public member_ `bool bHasPositions = false;`
- L20 _public member_ `FMeshAttributesArray<FVector3f> Positions;`
- L22 _public member_ `bool bHasNormals = false;`
- L23 _public member_ `FMeshAttributesArray<FVector3f> Normals;`

#### struct `UE::MeshParser::FMeshPrimitiveDescription`  
`struct FMeshPrimitiveDescription`  
_L26-49_
- L28 _public member_ `int32 MaterialIndex = INDEX_NONE;`
- L30 _public member_ `FMeshAttributesArray<int32> Indices;`
- L31 _public member_ `FMeshAttributesArray<FVector3f> Positions;`
- L32 _public member_ `FMeshAttributesArray<FVector3f> Normals;`
- L33 _public member_ `FMeshAttributesArray<FVector4f> Tangents;`
- L34 _public member_ `TArray<FMeshAttributesArray<FVector2f>> UVs;`
- L36 _public member_ `FMeshAttributesArray<FColor> VertexColors;`
- L38 _public member_ `TArray<FMeshAttributesArray<UE::Math::TIntVector4<FBoneIndexType>>> JointInfluences;` — TODO: Per Group (make group size configurable)
- L39 _public member_ `TArray<FMeshAttributesArray<UE::Math::TIntVector4<uint16>>> JointWeights;` — TODO: Per Group (make group size configurable)
- L41 _public member_ `TArray<FPrimitiveTargetDescription> Targets;` — MorphTargets
- L43 _public prototype_ `bool IsEmpty();`
- L46 _public prototype_ `void PrepareContainers(const int32& IndexCount, const int32& AttributesCount, const int32& UVCount, bool bHasVertexColors, const int32& TargetCount);` — Except for Joint related containers
- L48 _public prototype_ `void PrepareJointContainers(const uint32& JointGroupCount, const int32& AttributesCount);`

#### struct `UE::MeshParser::FMeshDetails`  
`struct FMeshDetails`  
_L51-56_
- L53 _public member_ `int32 NumberOfPrimitives = 0;`
- L54 _public member_ `int32 UVCount = 0;`
- L55 _public member_ `bool bHasVertexColors = false;`

#### struct `UE::MeshParser::FExportConfigs`  
`struct FExportConfigs`  
_L58-71_
- L60 _public member_ `bool bExportVertexSkinWeights = false;`
- L61 _public member_ `bool bExportVertexColors = false;`
- L62 _public member_ `const USplineMeshComponent* SplineMeshComponent = nullptr;`
- L63 _public member_ `int32 SkeletonInfluenceCountPerGroup = INT32_MAX;`
- L64 _public member_ `bool bExportMorphTargets = false;`
- L66 _public prototype_ `FExportConfigs(bool bInExportVertexSkinWeights, bool bInExportVertexColors, const USplineMeshComponent* InSplineMeshComponent, int32 InSkeletonInfluenceCountPerGroup, bool bInExportMorphTargets);`

#### struct `UE::MeshParser::FMeshDescriptionParser`  
`template <class T> struct FMeshDescriptionParser`  
_L82-134_
- desc: Note0: We are compacting the Vertex Attributes and Indices per Primitives, with no overlapping. Note1: Primary approach tries compaction on a Vertex bases, if that fails (due to VertexInstance Attributes differing on a per Vertex base), it falls back onto VertexInstance based compaction. Parsing does not do compaction for identical Vertex attribute values. It's either driven by FVertexIDs or FVertexInstanceIDs within Indices. Note2: TODO: perhaps add a solution path where we keep the unfication across primitives? class T: Static/Skeletal Material Slots
- L84 _public prototype_ `FMeshDescriptionParser(const FMeshDescription* InMeshDescription, const TArray<T>& InMaterialSlots);`
- L89 _public prototype_ `void Parse(TArray<FMeshPrimitiveDescription>& OutMeshPrimitiveDescriptions, TArray<FString>& OutTargetNames, const FExportConfigs& ExportConfigs);` — Parses FMeshDescription into the FMeshPrimitiveMeshDescriptions array based on the provided ExportConfigs.
- L98 _private prototype_ `bool ParseVertexBased(const TArrayView<const FTriangleID>& TriangleIDs, FMeshPrimitiveDescription& MeshPrimitiveDescription, const FExportConfigs& ExportConfigs);` — Tries to parse the PolygonGroup to Primitive, using only the Vertices. Checks if the VertexInstances use identical values per Vertices. If any of the VertexInstances of a given Vertex do not match Values we fail out and return false. (in which case we are falling back on using ParseVertexInstanceBased function)
- L104 _private prototype_ `void ParseVertexInstanceBased(const TArrayView<const FTriangleID>& TriangleIDs, FMeshPrimitiveDescription& MeshPrimitiveDescription, const FExportConfigs& ExportConfigs);` — Parses the PolygonGroup to Primitive, using the VertexInstances. Each VertexInstance will be a new entry in the VertexAttribute containers (aka a new 'Vertex' in the parsed data set).
- L109 _private prototype_ `int32 GetMaterialIndex(const FPolygonGroupID& PolygonGroupID);` — Gets the Material Index for the PolygonGroupID, based on the MeshDescription and the MaterialSlots provided in the struct's constructor.
- L112 _private member_ `const FMeshDescription* MeshDescription;` — Inputs:
- L113 _private member_ `const TArray<T>& MaterialSlots;`
- L116 _private member_ `TVertexAttributesConstRef<FVector3f> VertexPositions;` — Helper variable acquired from Inputs:
- L117 _private member_ `TVertexInstanceAttributesConstRef<FVector3f> VertexInstanceNormals;`
- L118 _private member_ `TVertexInstanceAttributesConstRef<FVector3f> VertexInstanceTangents;`
- L119 _private member_ `TVertexInstanceAttributesConstRef<float> VertexInstanceBinormalSigns;`
- L120 _private member_ `TVertexInstanceAttributesConstRef<FVector2f> VertexInstanceUVs;`
- L121 _private member_ `TVertexInstanceAttributesConstRef<FVector4f> VertexInstanceColors;`
- L124 _private member_ `TArray<TVertexAttributesConstRef<FVector3f>> TargetVertexPositionDeltas;` — MorphTarget Deltas:
- L125 _private member_ `TArray<TVertexInstanceAttributesConstRef<FVector3f>> TargetVertexInstanceNormalDeltas;`
- L126 _private member_ `TArray<FString> TargetNames;`
- L127 _private member_ `int32 NumOfTargets;`
- L129 _private member_ `TConstArrayView<FVertexID> VertexInstanceIdToVertexId;`
- L130 _private member_ `TPolygonGroupAttributesConstRef<FName> PolygonGroupMaterialSlotNames;`
- L133 _public member_ `FMeshDetails MeshDetails;` — MeshDetails like UVCount/NumberOfPrimitives/bHasVertexColor for ease of access:

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshParser` (scope `UE`)
- L136 _namespace_ `namespace Private` (scope `UE::MeshParser`)
- L143 _prototype_ `template <class T> int32 GetNumberOfValidPolygons(const T* Mesh , const int32 LODIndex);` (scope `UE::MeshParser::Private`) — Queries number of valid polygons (polygons that have at least 1 triangle). It queries it from Source Model (MeshDescription), and not the RenderData.
