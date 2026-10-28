# Plugins / GLTFCore

- module root: `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore`
- headers: 19; symbols: 1007
- symbol kinds: class=20, enum=27, enumerator=135, function=141, macro=5, member=327, namespace=40, prototype=256, struct=50, typedef=3, union=2, variable=1

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTF/ConversionUtilities.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace GLTF`
- L16 _function_ `inline FVector ConvertVec3(const FVector& Vec)` (scope `GLTF`)
- L23 _function_ `inline FVector4 ConvertTangent(const FVector4& Tangent)` (scope `GLTF`)
- L32 _function_ `template<typename T> UE::Math::TQuat<T> ConvertQuat(const UE::Math::TQuat<T>& Quat)` (scope `GLTF`)
- L48 _function_ `inline FMatrix ConvertMat(const FMatrix& Matrix)` (scope `GLTF`)
- L66 _function_ `inline FMaterial::EAlphaMode AlphaModeFromString(const FString& Str)` (scope `GLTF`)
- L85 _function_ `inline FAnimation::EPath AnimationPathFromString(const FString& Str)` (scope `GLTF`)
- L108 _function_ `inline FPrimitive::EMode PrimitiveModeFromNumber(uint32 Num)` (scope `GLTF`)
- L128 _function_ `inline FImage::EFormat ImageFormatFromFilename(const FString& Filename)` (scope `GLTF`)
- L143 _function_ `inline FImage::EFormat ImageFormatFromMimeType(const FString& Str)` (scope `GLTF`)
- L158 _function_ `inline FSampler::EFilter FilterFromNumber(uint16 Num)` (scope `GLTF`)
- L171 _function_ `inline FSampler::EWrap WrapModeFromNumber(uint16 Num)` (scope `GLTF`)
- L182 _function_ `inline FAccessor::EType AccessorTypeFromString(const FString& Str)` (scope `GLTF`)
- L216 _function_ `inline FAccessor::EComponentType ComponentTypeFromNumber(uint16 Num)` (scope `GLTF`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTF/ExtensionsHandler.h` (Private)


#### class `GLTF::FExtensionsHandler`  
`class FExtensionsHandler`  
_L27-64_
- L30 _public prototype_ `explicit FExtensionsHandler(TArray<FLogMessage>& InMessages);`
- L32 _public prototype_ `void SetAsset(GLTF::FAsset& InAsset);`
- L34 _public prototype_ `void SetupAssetExtensions(const FJsonObject& Object, const FString& InResourcesPath) const;`
- L35 _public prototype_ `void SetupBufferExtensions(const FJsonObject& Object, FBuffer& Buffer) const;`
- L36 _public prototype_ `void SetupBufferViewExtensions(const FJsonObject& Object, FBufferView& BufferView) const;`
- L37 _public prototype_ `void SetupAccessorExtensions(const FJsonObject& Object, FAccessor& Accessor) const;`
- L38 _public prototype_ `void SetupPrimitiveExtensions(const FJsonObject& Object, FPrimitive& Primitive, uint32 PrimitiveIndex, const FString& MeshUniqueId) const;`
- L39 _public prototype_ `void SetupMeshExtensions(const FJsonObject& Object, FMesh& Mesh) const;`
- L40 _public prototype_ `void SetupSceneExtensions(const FJsonObject& Object, FScene& Scene) const;`
- L41 _public prototype_ `void SetupNodeExtensions(const FJsonObject& Object, FNode& Node) const;`
- L42 _public prototype_ `void SetupCameraExtensions(const FJsonObject& Object, FCamera& Camera) const;`
- L43 _public prototype_ `void SetupSkinExtensions(const FJsonObject& Object, FSkinInfo& Skin) const;`
- L44 _public prototype_ `void SetupAnimationExtensions(const FJsonObject& Object, FAnimation& Animation) const;`
- L45 _public prototype_ `void SetupImageExtensions(const FJsonObject& Object, FImage& Image) const;`
- L46 _public prototype_ `void SetupSamplerExtensions(const FJsonObject& Object, FSampler& Sampler) const;`
- L47 _public prototype_ `void SetupTextureExtensions(const FJsonObject& Object, FTexture& Texture) const;`
- L48 _public prototype_ `void SetupMaterialExtensions(const FJsonObject& Object, FMaterial& Material) const;`
- L49 _public prototype_ `void SetupLightExtensions(const FJsonObject& Object, const FString& InResourcesPath) const;`
- L51 _public function_ `TArray<FLogMessage>& GetMessages()`
- L57 _private prototype_ `void CheckExtensions(const FJsonObject& Object, const TArray<FString>& ExtensionsSupported) const;`
- L59 _private prototype_ `void SetupLightPunctual(const FJsonObject& Object) const;`
- L62 _private member_ `TArray<FLogMessage>& Messages;`
- L63 _private member_ `GLTF::FAsset* Asset;`
- L66 _function_ `inline void FExtensionsHandler::SetAsset(GLTF::FAsset& InAsset)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTF/GLTFBinaryReader.h` (Private)


#### class `GLTF::FBinaryFileReader`  
`class FBinaryFileReader : public FBaseLogger`  
_L12-27_
- inherits: `FBaseLogger`
- L15 _public prototype_ `FBinaryFileReader();`
- L17 _public prototype_ `bool ReadFile(FArchive& FileReader);`
- L19 _public prototype_ `void SetBuffer(TArray64<uint8>& InBuffer);`
- L21 _public prototype_ `const TArray<uint8>& GetJsonBuffer() const;`
- L24 _private member_ `TArray<uint8> JsonChunk;`
- L26 _private member_ `TArray64<uint8>* BinChunk;`
- L29 _function_ `inline void FBinaryFileReader::SetBuffer(TArray64<uint8>& InBuffer)`
- L34 _function_ `inline const TArray<uint8>& FBinaryFileReader::GetJsonBuffer() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTF/JsonUtilities.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`
- L11 _function_ `inline uint32 ArraySize(const FJsonObject& Object, const FString& Name)` (scope `GLTF`)
- L21 _function_ `inline FString GetString(const FJsonObject& Object, const TCHAR* Name, const FString& DefaultValue = FString())` (scope `GLTF`)
- L31 _function_ `inline bool GetBool(const FJsonObject& Object, const TCHAR* Name, bool DefaultValue = false)` (scope `GLTF`)
- L41 _function_ `inline uint64 GetUnsignedInt64(const FJsonObject& Object, const TCHAR* Name, uint64 DefaultValue)` (scope `GLTF`)
- L56 _function_ `inline uint32 GetUnsignedInt(const FJsonObject& Object, const TCHAR* Name, uint32 DefaultValue)` (scope `GLTF`)
- L71 _function_ `inline uint32 GetIndex(const FJsonObject& Object, const TCHAR* Name)` (scope `GLTF`)
- L76 _function_ `inline bool GetIndex(const FJsonObject& Object, const TCHAR* Name, uint32& Value)` (scope `GLTF`)
- L87 _function_ `inline float GetScalar(const FJsonObject& Object, const TCHAR* Name, float DefaultValue = 0.0f)` (scope `GLTF`)
- L97 _function_ `inline FVector GetVec3(const FJsonObject& Object, const TCHAR* Name, const FVector& DefaultValue = FVector::ZeroVector)` (scope `GLTF`)
- L114 _function_ `inline FVector4 GetVec4(const FJsonObject& Object, const TCHAR* Name, const FVector4& DefaultValue = FVector4())` (scope `GLTF`)
- L132 _function_ `inline FQuat GetQuat(const FJsonObject& Object, const TCHAR* Name, const FQuat& DefaultValue = FQuat(0, 0, 0, 1))` (scope `GLTF`)
- L150 _function_ `inline FMatrix GetMat4(const FJsonObject& Object, const TCHAR* Name, const FMatrix& DefaultValue = FMatrix::Identity)` (scope `GLTF`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTF/MaterialUtilities.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GLTF`
- L9 _namespace_ `namespace GLTF`
- L11 _namespace_ `namespace GLTF`
- L14 _prototype_ `float SetTextureMap(const FJsonObject& InObject, const TCHAR* InTexName, const TCHAR* InScaleName, const TArray<FTexture>& Textures, GLTF::FTextureMap& OutMap, TArray<FLogMessage>& OutMessages);` (scope `GLTF`) — Returns scale factor if JSON has it, 1.0 by default.

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Private/GLTFMapFactory.h` (Private)


#### struct `GLTF::FPBRMapFactory`  
`struct FPBRMapFactory`  
_L23-113_
- L77 _public member_ `FMaterialElement* CurrentMaterialElement;`
- L78 _public member_ `FString GroupName;`
- L81 _public prototype_ `FPBRMapFactory(ITextureFactory& TextureFactory);`
- L83 _public prototype_ `void SetParentPackage(UObject* ParentPackage, EObjectFlags Flags);`
- L85 _public prototype_ `void CreateNormalMap(const GLTF::FTexture& Map, int CoordinateIndex, float NormalScale, const GLTF::FTextureTransform* TextureTransform);`
- L87 _public prototype_ `FMaterialExpression* CreateColorMap(const GLTF::FTexture& Map, int CoordinateIndex, const FVector3f& Color, const TCHAR* MapName, const TCHAR* ValueName, ETextureMode TextureMode, FMaterialExpressionInput& MaterialInput, const GLTF::FTextureTransform* TextureTransform);`
- L91 _public prototype_ `FMaterialExpression* CreateColorMap(const GLTF::FTexture& Map, int CoordinateIndex, const FVector4f& Color, const TCHAR* MapName, const TCHAR* ValueName, ETextureMode TextureMode, FMaterialExpressionInput& MaterialInput, const GLTF::FTextureTransform* TextureTransform);`
- L95 _public prototype_ `FMaterialExpressionTexture* CreateTextureMap(const GLTF::FTexture& Map, int CoordinateIndex, const TCHAR* MapName, ETextureMode TextureMode, const GLTF::FTextureTransform* TextureTransform);`
- L98 _public prototype_ `void CreateMultiMap(const GLTF::FTexture& Map, int CoordinateIndex, const TCHAR* MapName, const FMapChannel* MapChannels, uint32 MapChannelsCount, ETextureMode TextureMode, const GLTF::FTextureTransform* TextureTransform);`
- L102 _private typedef_ `using FExpressionList = TArray<FMaterialExpression*, TFixedAllocator<4> >;`
- L105 _private prototype_ `template <class ValueExpressionClass, class ValueClass> FMaterialExpression* CreateMap(const GLTF::FTexture& Map, int CoordinateIndex, const ValueClass& Value, const TCHAR* MapName, const TCHAR* ValueName, ETextureMode TextureMode, FMaterialExpressionInput& MaterialInput, const GLTF::FTextureTransform* TextureTransform);`
- L110 _private member_ `ITextureFactory& TextureFactory;`
- L111 _private member_ `UObject* ParentPackage;`
- L112 _private member_ `EObjectFlags Flags;`
- L115 _function_ `inline void FPBRMapFactory::SetParentPackage(UObject* InParentPackage, EObjectFlags InFlags)`

#### enum `GLTF::FPBRMapFactory::EChannel`  
`enum class EChannel`  
_L25-34_
- L27 _public enumerator_ `All`
- L28 _public enumerator_ `Red`
- L29 _public enumerator_ `Green`
- L30 _public enumerator_ `Blue`
- L31 _public enumerator_ `Alpha`
- L32 _public enumerator_ `RG`
- L33 _public enumerator_ `RGB`

#### struct `GLTF::FPBRMapFactory::FMapChannel`  
`struct FMapChannel`  
_L36-75_
- L43 _public member_ `const TCHAR* ValueName;`
- L44 _public member_ `EChannel Channel;`
- L45 _public member_ `FMaterialExpressionInput* MaterialInput;`
- L46 _public member_ `FMaterialExpression* OutputExpression;`
- L48 _public function_ `FMapChannel(float InValue, const TCHAR* InValueName, EChannel InChannel, FMaterialExpressionInput* InMaterialInput, FMaterialExpression* InOutputExpression) : FMapChannel(InValueName, InChannel, InMaterialInput, InOutputExpression)`
- L54 _public function_ `FMapChannel(const FVector& InVecValue, const TCHAR* InValueName, EChannel InChannel, FMaterialExpressionInput* InMaterialInput, FMaterialExpression* InOutputExpression) : FMapChannel(InValueName, InChannel, InMaterialInput, InOutputExpression)`
- L60 _public function_ `void SetValue(const FVector& Vec)`
- L68 _private function_ `FMapChannel(const TCHAR* InValueName, EChannel InChannel, FMaterialExpressionInput* InMaterialInput, FMaterialExpression* InOutputExpression) : ValueName(InValueName) , Channel(InChannel) , MaterialInput(InMaterialInput) , OutputExpression(InOutputExpression)`

#### union `GLTF::FPBRMapFactory::FMapChannel::(anonymous)`  
`union`  
_L38-41_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`
- L10 _namespace_ `namespace GLTF`
- L11 _namespace_ `namespace GLTF`
- L12 _namespace_ `namespace GLTF`
- L13 _namespace_ `namespace GLTF`
- L14 _namespace_ `namespace GLTF`
- L17 _namespace_ `namespace GLTF`
- L39 _member_ `float Value;` (scope `GLTF::FPBRMapFactory::FMapChannel::__anon7849e1c8010a`)
- L40 _member_ `float VecValue[3];` (scope `GLTF::FPBRMapFactory::FMapChannel::__anon7849e1c8010a`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFAccessor.h` (Public)


#### struct `GLTF::FBuffer`  
`struct FBuffer`  
_L14-48_
- L16 _public member_ `uint64 ByteLength;`
- L17 _public member_ `uint8* Data;`
- L19 _public function_ `FBuffer() : ByteLength(0) , Data(nullptr)`
- L26 _public function_ `explicit FBuffer(uint64 InByteLength) : ByteLength(InByteLength) , Data(nullptr)`
- L32 _public function_ `bool IsValid() const`
- L37 _public function_ `const uint8* DataAt(uint64 Offset) const`
- L43 _public function_ `void operator=(const FBuffer& InBuffer)`

#### struct `GLTF::FBufferView`  
`struct FBufferView`  
_L50-126_
- L52 _public member_ `FBuffer Buffer;`
- L53 _public member_ `uint64 ByteOffset;`
- L54 _public member_ `uint64 ByteLength;`
- L56 _public member_ `uint32 ByteStride;` — if zero then accessor elements are tightly packed, i.e., effective stride equals the size of the element
- L58 _public function_ `FBufferView() : Buffer() , ByteOffset(0) , ByteLength(0) , ByteStride(0)`
- L66 _public function_ `explicit FBufferView(const FBuffer& InBuffer, uint64 InOffset, uint64 InLength, uint32 InStride) : Buffer(InBuffer) , ByteOffset(InOffset) , ByteLength(InLength) , ByteStride(InStride)`
- L75 _public function_ `void operator=(const FBufferView& InBufferView)`
- L83 _public function_ `bool IsValid() const`
- L88 _public function_ `bool HasCapacityFor(const uint32 InCount, const uint64 InByteOffset, const uint32 InElementSize, const uint32 InByteStride) const`
- L122 _public function_ `const uint8* DataAt(uint64 Offset) const`

#### enum `GLTF::EMeshAttributeType`  
`enum EMeshAttributeType : uint8`  
_L128-149_
- L130 _public enumerator_ `POSITION = 0`
- L131 _public enumerator_ `NORMAL`
- L132 _public enumerator_ `TANGENT`
- L134 _public enumerator_ `TEXCOORD_0`
- L135 _public enumerator_ `TEXCOORD_1`
- L136 _public enumerator_ `TEXCOORD_2`
- L137 _public enumerator_ `TEXCOORD_3`
- L138 _public enumerator_ `TEXCOORD_4`
- L139 _public enumerator_ `TEXCOORD_5`
- L140 _public enumerator_ `TEXCOORD_6`
- L141 _public enumerator_ `TEXCOORD_7`
- L143 _public enumerator_ `COLOR_0`
- L145 _public enumerator_ `JOINTS_0`
- L146 _public enumerator_ `WEIGHTS_0`
- L148 _public enumerator_ `COUNT`

#### struct `GLTF::FAccessor`  
`struct FAccessor`  
_L156-333_
- L249 _public member_ `uint32 AccessorIndex;` — Index of the Accessor in Asset->Accessors list
- L251 _public member_ `const uint32 Count;`
- L252 _public member_ `const EType Type;`
- L253 _public member_ `const EComponentType ComponentType;`
- L254 _public member_ `const bool bNormalized;`
- L255 _public member_ `bool bQuantized;`
- L256 _public member_ `const FSparse Sparse;`
- L258 _public member_ `FBufferView BufferView;`
- L259 _public member_ `uint64 ByteOffset;`
- L260 _public member_ `const uint32 NumberOfComponents;`
- L261 _public member_ `const uint32 ElementSize;`
- L262 _public member_ `const uint32 ByteStride;`
- L264 _public prototype_ `FAccessor();`
- L265 _public prototype_ `FAccessor(uint32 InAccessorIndex, FBufferView& InBufferView, uint64 InOffset, uint32 InCount, EType InType, EComponentType InCompType, bool bInNormalized, const FSparse& InSparse);`
- L270 _public prototype_ `FAccessor(uint32 InAccessorIndex, uint32 InCount, EType InType, EComponentType InCompType, bool bInNormalized, const FSparse& InSparse);` — Compressed Data sets (FAccessor does not have FBufferView at processing of Accessors, as FBufferview will be created with the processing of the KHR_draco_mesh_compression extension)
- L272 _public prototype_ `bool IsValid() const;`
- L273 _public prototype_ `FMD5Hash GetHash() const;`
- L275 _public prototype_ `uint32 GetUnsignedInt(uint32 Index) const;`
- L276 _public prototype_ `void GetUnsignedInt16x4(uint32 Index, uint16 Values[4]) const;`
- L278 _public prototype_ `float GetFloat(uint32 Index) const;`
- L279 _public prototype_ `FVector2D GetVec2(uint32 Index) const;`
- L280 _public prototype_ `FVector GetVec3(uint32 Index) const;`
- L281 _public prototype_ `FVector4 GetVec4(uint32 Index) const;`
- L282 _public prototype_ `FMatrix GetMat4(uint32 Index) const;`
- L284 _public prototype_ `void GetUnsignedIntArray(TArray<uint32>& Buffer) const;`
- L285 _public prototype_ `void GetUnsignedIntArray(uint32* Buffer) const;`
- L287 _public prototype_ `void GetFloatArray(TArray<float>& Buffer) const;`
- L288 _public prototype_ `void GetFloatArray(float* Buffer) const;`
- L290 _public prototype_ `void GetVec2Array(TArray<FVector2f>& Buffer) const;`
- L291 _public prototype_ `void GetVec2Array(FVector2f* Buffer) const;`
- L293 _public prototype_ `void GetVec3Array(TArray<FVector3f>& Buffer) const;`
- L294 _public prototype_ `void GetVec3Array(FVector3f* Buffer) const;`
- L297 _public prototype_ `void GetCoordArray(TArray<FVector3f>& Buffer) const;` — @note Performs axis conversion for vec3s(i.e. from glTF right-handed and Y-up to left-handed and Z-up).
- L298 _public prototype_ `void GetCoordArray(FVector3f* Buffer) const;`
- L300 _public prototype_ `void GetVec4Array(TArray<FVector4f>& Buffer) const;`
- L301 _public prototype_ `void GetVec4Array(FVector4f* Buffer) const;`
- L304 _public prototype_ `void GetQuatArray(TArray<FVector4f>& Buffer) const;` — @note Performs axis conversion for quaternion(i.e. from glTF right-handed and Y-up to left-handed and Z-up).
- L305 _public prototype_ `void GetQuatArray(FVector4f* Buffer) const;`
- L307 _public prototype_ `void GetMat4Array(TArray<FMatrix44f>& Buffer) const;`
- L308 _public prototype_ `void GetMat4Array(FMatrix44f* Buffer) const;`
- L310 _public prototype_ `bool IsValidDataType(EMeshAttributeType MeshAttributeType, bool bMorphTargetProperty) const;`
- L311 _public prototype_ `bool CheckAccessorTypeForDataType(EMeshAttributeType MeshAttributeType, bool bMorphTargetProperty) const;`
- L312 _public prototype_ `bool CheckNonQuantizedComponentTypeForDataType(EMeshAttributeType MeshAttributeType, bool bMorphTargetProperty) const;`
- L313 _public prototype_ `bool CheckQuantizedComponentTypeForDataType(EMeshAttributeType MeshAttributeType, bool bMorphTargetProperty) const;`
- L315 _public prototype_ `const uint8* DataAt(uint32 Index) const;`
- L318 _public prototype_ `void UpdateUnsignedIntWithSparse(uint32 Index, uint32& Data) const;` — Sparse related helpers:
- L319 _public prototype_ `void UpdateUnsignedInt16x4WithSparse(uint32 Index, uint16 Data[4]) const;`
- L321 _public prototype_ `void UpdateFloatWithSparse(uint32 Index, float& Data) const;`
- L322 _public prototype_ `void UpdateVec2WithSparse(uint32 Index, FVector2D& Data) const;`
- L323 _public prototype_ `void UpdateVec3WithSparse(uint32 Index, FVector& Data) const;`
- L324 _public prototype_ `void UpdateVec4WithSparse(uint32 Index, FVector4& Data) const;`
- L326 _public prototype_ `void UpdateMat4WithSparse(uint32 Index, FMatrix& Data) const;`
- L328 _public prototype_ `void UpdateFloatArrayWithSparse(float* Data) const;`
- L329 _public prototype_ `void UpdateUnsignedIntArrayWithSparse(uint32* Data) const;`
- L332 _public prototype_ `template<typename ItemType, uint32 ItemElementCount> void UpdateArrayWithSparse(ItemType* Data) const;`

#### enum `GLTF::FAccessor::EType`  
`enum class EType`  
_L160-171_
- L162 _public enumerator_ `Unknown`
- L163 _public enumerator_ `Scalar`
- L164 _public enumerator_ `Vec2`
- L165 _public enumerator_ `Vec3`
- L166 _public enumerator_ `Vec4`
- L167 _public enumerator_ `Mat2`
- L168 _public enumerator_ `Mat3`
- L169 _public enumerator_ `Mat4`
- L170 _public enumerator_ `Count`

#### enum `GLTF::FAccessor::EComponentType`  
`enum class EComponentType`  
_L173-183_
- L175 _public enumerator_ `None`
- L176 _public enumerator_ `S8` — signed byte
- L177 _public enumerator_ `U8` — unsigned byte
- L178 _public enumerator_ `S16` — signed short
- L179 _public enumerator_ `U16` — unsigned short
- L180 _public enumerator_ `U32` — unsigned int -- only valid for indices, not attributes
- L181 _public enumerator_ `F32` — float
- L182 _public enumerator_ `Count`

#### struct `GLTF::FAccessor::FSparse`  
`struct FSparse`  
_L185-247_
- L187 _public member_ `bool bHasSparse;`
- L189 _public member_ `const uint32 Count;`
- L209 _public member_ `} Indices;`
- L228 _public member_ `} Values;`
- L230 _public function_ `FSparse() : bHasSparse(false) , Count(0) , Indices(FIndices()) , Values(FValues())`
- L238 _public function_ `FSparse(uint32 InCount, FBufferView& InIndicesBufferView, uint64 InIndicesByteOffset, EComponentType InIndicesComponentType, FBufferView& InValuesBufferView, uint64 InValuesByteOffset) : bHasSparse(true) , Count(InCount) , Indices(InCount, InIndicesBufferView, InIndicesByteOffset, InIndicesComponentType) , Values(InValuesBufferView, InValuesByteOffset)`

#### struct `GLTF::FAccessor::FSparse::FIndices`  
`struct FIndices`  
_L192-209_
- desc: Indices:
- L194 _public member_ `const int32 Count;` — Helper for creating cache, equals to FSparse.Count
- L196 _public member_ `FBufferView BufferView;`
- L197 _public member_ `const uint64 ByteOffset;`
- L198 _public member_ `const EComponentType ComponentType;`
- L200 _public function_ `FIndices() : Count(0) , BufferView() , ByteOffset(0) , ComponentType(EComponentType::None)`
- L208 _public prototype_ `FIndices(uint32 InCount, FBufferView& InBufferView, uint64 InByteOffset, EComponentType InComponentType);`

#### struct `GLTF::FAccessor::FSparse::FValues`  
`struct FValues`  
_L212-228_
- desc: Values:
- L214 _public member_ `FBufferView BufferView;`
- L215 _public member_ `const uint64 ByteOffset;`
- L217 _public function_ `FValues() : BufferView() , ByteOffset(0)`
- L223 _public function_ `FValues(FBufferView& InBufferView, uint64 InByteOffset) : BufferView(InBufferView) , ByteOffset(InByteOffset)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFCORE_API`
- L12 _namespace_ `namespace GLTF`
- L151 _variable_ `constexpr uint8 SupportedTexCoordNum = EMeshAttributeType::TEXCOORD_7 - EMeshAttributeType::TEXCOORD_0 + 1;` (scope `GLTF`)
- L154 _prototype_ `FString ToString(const EMeshAttributeType& Type);` (scope `GLTF`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFAnimation.h` (Public)


#### struct `GLTF::FAnimation`  
`struct FAnimation`  
_L14-78_
- L71 _public member_ `FString Name;`
- L72 _public member_ `TArray<FSampler> Samplers;`
- L73 _public member_ `TArray<FChannel> Channels;`
- L75 _public member_ `TMap<FString, FString> Extras;`
- L77 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames

#### enum `GLTF::FAnimation::EInterpolation`  
`enum class EInterpolation`  
_L16-21_
- L18 _public enumerator_ `Linear`
- L19 _public enumerator_ `Step`
- L20 _public enumerator_ `CubicSpline`

#### enum `GLTF::FAnimation::EPath`  
`enum class EPath`  
_L23-29_
- L25 _public enumerator_ `Translation`
- L26 _public enumerator_ `Rotation`
- L27 _public enumerator_ `Scale`
- L28 _public enumerator_ `Weights`

#### struct `GLTF::FAnimation::FTarget`  
`struct FTarget`  
_L31-40_
- L33 _public member_ `const FNode& Node;`
- L34 _public member_ `EPath Path;`
- L36 _public function_ `FTarget(const FNode& Node) : Node(Node)`

#### struct `GLTF::FAnimation::FChannel`  
`struct FChannel`  
_L42-53_
- L45 _public member_ `int32 Sampler;` — The index of a sampler in this animation used to compute the value for the target.
- L47 _public member_ `FTarget Target;` — The index of the node and TRS property to target.
- L49 _public function_ `FChannel(const FNode& Node) : Target(Node)`

#### struct `GLTF::FAnimation::FSampler`  
`struct FSampler`  
_L55-69_
- L57 _public member_ `EInterpolation Interpolation;`
- L59 _public member_ `const FAccessor& Input;` — The accessor containing keyframe input values, e.g., time. Always float and seconds.
- L61 _public member_ `const FAccessor& Output;` — The accessor containing keyframe output values.
- L63 _public function_ `FSampler(const FAccessor& Input, const FAccessor& Output) : Interpolation(EInterpolation::Linear) , Input(Input) , Output(Output)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFAsset.h` (Public)


#### enum `GLTF::EExtension`  
`enum class EExtension`  
_L29-54_
- L31 _public enumerator_ `KHR_MaterialsPbrSpecularGlossiness`
- L32 _public enumerator_ `KHR_MaterialsUnlit`
- L33 _public enumerator_ `KHR_MaterialsClearCoat`
- L34 _public enumerator_ `KHR_MaterialsTransmission`
- L35 _public enumerator_ `KHR_MaterialsSheen`
- L36 _public enumerator_ `KHR_MaterialsVariants`
- L37 _public enumerator_ `KHR_MaterialsIOR`
- L38 _public enumerator_ `KHR_MaterialsSpecular`
- L39 _public enumerator_ `KHR_MaterialsEmissiveStrength`
- L40 _public enumerator_ `KHR_MaterialsIridescence`
- L41 _public enumerator_ `KHR_MaterialsAnisotropy`
- L42 _public enumerator_ `KHR_MaterialsVolume`
- L43 _public enumerator_ `KHR_TextureTransform`
- L44 _public enumerator_ `KHR_DracoMeshCompression`
- L45 _public enumerator_ `KHR_LightsPunctual`
- L46 _public enumerator_ `KHR_Lights`
- L47 _public enumerator_ `EXT_LightsIES`
- L48 _public enumerator_ `KHR_Blend`
- L49 _public enumerator_ `MSFT_TextureDDS`
- L50 _public enumerator_ `MSFT_PackingNormalRoughnessMetallic`
- L51 _public enumerator_ `MSFT_PackingOcclusionRoughnessMetallic`
- L52 _public enumerator_ `KHR_MeshQuantization`
- L53 _public enumerator_ `Count`

#### struct `GLTF::FScene`  
`struct FScene`  
_L56-62_
- L58 _public member_ `FString Name;`
- L59 _public member_ `TArray<int32> Nodes;`
- L60 _public member_ `TMap<FString, FString> Extras;`
- L61 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames

#### struct `GLTF::FMetadata`  
`struct FMetadata`  
_L64-76_
- L71 _public member_ `FString GeneratorName;`
- L72 _public member_ `float Version;`
- L73 _public member_ `TArray<FExtraData> Extras;`
- L75 _public prototype_ `const FExtraData* GetExtraData(const FString& Name) const;`

#### struct `GLTF::FMetadata::FExtraData`  
`struct FExtraData`  
_L66-70_
- L68 _public member_ `FString Name;`
- L69 _public member_ `FString Value;`

#### struct `GLTF::FAsset`  
`struct FAsset : FNoncopyable`  
_L78-165_
- inherits: `FNoncopyable`
- L80 _public member_ `static const TSet<EExtension> SupportedExtensions;`
- L89 _public member_ `FString Name;`
- L91 _public member_ `TArray<FBuffer> Buffers;`
- L92 _public member_ `TArray<FBufferView> BufferViews;`
- L93 _public member_ `TArray<FAccessor> Accessors;` — Note: We rely on order of the Accessors (both from glTF point of view and from internal Identification point of view).
- L94 _public member_ `TArray<FMesh> Meshes;`
- L96 _public member_ `TArray<FScene> Scenes;`
- L97 _public member_ `TArray<FNode> Nodes;`
- L98 _public member_ `TArray<FCamera> Cameras;`
- L99 _public member_ `TArray<FLight> Lights;`
- L100 _public member_ `TArray<FLightIES> LightsIES;`
- L101 _public member_ `TArray<FSkinInfo> Skins;`
- L102 _public member_ `TArray<FAnimation> Animations;`
- L104 _public member_ `TArray<FImage> Images;`
- L105 _public member_ `TArray<FSampler> Samplers;`
- L106 _public member_ `TArray<FTexture> Textures;`
- L107 _public member_ `TArray<FMaterial> Materials;`
- L109 _public member_ `TArray<FString> Variants;`
- L111 _public member_ `TArray<FString> ExtensionsUsed;` — marked in the gltf
- L112 _public member_ `TArray<FString> ExtensionsRequired;` — marked in the gltf
- L114 _public member_ `TSet<EExtension> ProcessedExtensions;`
- L115 _public member_ `FMetadata Metadata;`
- L117 _public member_ `bool HasAbnormalInverseBindMatrices = false;` — True: in cases where at least 1 Joint node has multiple InverseBindMatrices that do not equal.
- L126 _public prototype_ `void Clear(uint32 BinBufferKBytes, uint32 ExtraBinBufferKBytes);` — Will clear the asset's buffers. @param BinBufferKBytes - bytes to reserve for the bin chunk buffer. @param ExtraBinBufferKBytes -  bytes to reserve for the extra binary buffer(eg. image, mime data, etc.) @note Only reserves buffers if they had any existing data.
- L134 _public prototype_ `void GenerateNames();` — Will generate names for any entities(nodes, meshes, etc.) that have the name field missing. Is called from GLTF::FFileReader::ReadFile @param Prefix - prefix to add to the entities name.
- L141 _public prototype_ `void GetRootNodes(TArray<int32>& NodeIndices);` — Finds the indices for the nodes which are root nodes. @param NodeIndices - array with the results
- L146 _public prototype_ `EValidationCheck ValidationCheck() const;` — Returns EValidationCheck::Valid if the asset passes the post-import validation checks.
- L151 _public prototype_ `FAccessor& CreateBuffersForAccessorIndex(uint32 AccessorIndex);` — Creates and sets up FBuffer and FBufferView for a given FAccessor (at the given index 'id')
- L156 _private member_ `TArray64<uint8> BinData;` — Binary glTF files can have embedded data after JSON. This will be empty when reading from a text glTF (common) or a binary glTF with no BIN chunk (rare).
- L159 _private member_ `TArray64<uint8> ExtraBinData;` — Extra binary data used for images from disk, mime data and so on.
- L162 _private member_ `TArray<TArray64<uint8>> UncompressedDracoBinData;` — Stores (Draco) Uncompressed Binary Data

#### enum `GLTF::FAsset::EValidationCheck`  
`enum EValidationCheck`  
_L82-87_
- L84 _public enumerator_ `Valid`
- L85 _public enumerator_ `InvalidMeshPresent = 0x1`
- L86 _public enumerator_ `InvalidNodePresent = 0x2`

#### struct `GLTF::GLTFNodePrefixStaticHelper`  
`struct GLTFNodePrefixStaticHelper`  
_L169-183_
- L171 _public prototype_ `static FString GetScenePrefix(const FString& AssetName);`
- L172 _public prototype_ `static FString GetNodePrefix(const FString& AssetName);`
- L173 _public prototype_ `static FString GetJointPrefix(const FString& AssetName);`
- L174 _public prototype_ `static FString GetTexturePrefix(const FString& AssetName);`
- L175 _public prototype_ `static FString GetCameraPrefix(const FString& AssetName);`
- L176 _public prototype_ `static FString GetLightPrefix(const FString& AssetName);`
- L177 _public prototype_ `static FString GetMaterialPrefix(const FString& AssetName);`
- L178 _public prototype_ `static FString GetSkinPrefix(const FString& AssetName);`
- L179 _public prototype_ `static FString GetAnimationPrefix(const FString& AssetName);`
- L180 _public prototype_ `static FString GetImagePrefix(const FString& AssetName);`
- L181 _public prototype_ `static FString GetMeshPrefix(const FString& AssetName);`
- L182 _public prototype_ `static FString GetIESPrefix(const FString& AssetName);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace GLTF`
- L13 _namespace_ `namespace GLTF`
- L14 _namespace_ `namespace GLTF`
- L15 _namespace_ `namespace GLTF`
- L16 _namespace_ `namespace GLTF`
- L17 _namespace_ `namespace GLTF`
- L18 _namespace_ `namespace GLTF`
- L19 _namespace_ `namespace GLTF`
- L20 _namespace_ `namespace GLTF`
- L21 _namespace_ `namespace GLTF`
- L22 _namespace_ `namespace GLTF`
- L23 _namespace_ `namespace GLTF`
- L24 _namespace_ `namespace GLTF`
- L27 _namespace_ `namespace GLTF`
- L167 _prototype_ `const TCHAR* ToString(EExtension Extension);` (scope `GLTF`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFCoreModule.h` (Public)


#### class `IGLTFCoreModule`  
`class IGLTFCoreModule : public IModuleInterface`  
_L11-33_
- inherits: `IModuleInterface`
- desc: The public interface of the GLTFCore module
- L19 _public function_ `static IGLTFCoreModule& Get()` — Singleton-like access to IGLTFCore @return Returns IGLTFCore singleton instance, loading the module on demand if needed
- L29 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFLogger.h` (Public)


#### enum `GLTF::EMessageSeverity`  
`enum class EMessageSeverity`  
_L10-15_
- L12 _public enumerator_ `Display`
- L13 _public enumerator_ `Warning`
- L14 _public enumerator_ `Error`

#### class `GLTF::FBaseLogger`  
`class FBaseLogger`  
_L27-34_
- L30 _public prototype_ `const TArray<FLogMessage>& GetLogMessages() const;`
- L33 _protected member_ `mutable TArray<FLogMessage> Messages;`
- L36 _function_ `inline const TArray<FLogMessage>& FBaseLogger::GetLogMessages() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GLTF`
- L23 _prototype_ `EMessageSeverity RuntimeWarningSeverity();` (scope `GLTF`) — There are certain warnings that we acknowledge and accept when running AutomationTests. For that reason we want Display severity for these specific warnings when Automation is running. For example not supported extension warnings are acknowledged and accepted when Automation is running, but we want those shown still as warnings when running otherwise.
- L25 _typedef_ `using FLogMessage = TTuple<EMessageSeverity, FText>;` (scope `GLTF`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFMaterial.h` (Public)


#### struct `GLTF::FTextureTransform`  
`struct FTextureTransform`  
_L10-22_
- L12 _public member_ `float Offset[2];`
- L13 _public member_ `float Rotation;`
- L14 _public member_ `float Scale[2];`
- L16 _public function_ `FTextureTransform()`

#### struct `GLTF::FTextureMap`  
`struct FTextureMap`  
_L24-48_
- L26 _public member_ `int32 TextureIndex;`
- L27 _public member_ `uint8 TexCoord;`
- L29 _public member_ `bool bHasTextureTransform;`
- L30 _public member_ `FTextureTransform TextureTransform;`
- L32 _public function_ `FTextureMap() : TextureIndex(INDEX_NONE) , TexCoord(0) , bHasTextureTransform(false)`
- L39 _public function_ `FMD5Hash GetHash() const`

#### struct `GLTF::FMaterial`  
`struct FMaterial`  
_L50-241_
- L168 _public member_ `FString Name;`
- L171 _public member_ `FTextureMap BaseColor;` — PBR properties
- L172 _public member_ `FVector4f BaseColorFactor;` — Used for DiffuseFactor on Specular-Glossiness mode
- L173 _public member_ `EShadingModel ShadingModel;`
- L174 _public member_ `FMetallicRoughness MetallicRoughness;`
- L175 _public member_ `FSpecularGlossiness SpecularGlossiness;`
- L176 _public member_ `FClearCoat ClearCoat;`
- L177 _public member_ `FTransmission Transmission;`
- L178 _public member_ `FSheen Sheen;`
- L179 _public member_ `FSpecular Specular;`
- L180 _public member_ `float IOR;`
- L181 _public member_ `float EmissiveStrength;`
- L184 _public member_ `FTextureMap Normal;` — base properties
- L185 _public member_ `FTextureMap Occlusion;`
- L186 _public member_ `FTextureMap Emissive;`
- L187 _public member_ `float NormalScale;`
- L188 _public member_ `float OcclusionStrength;`
- L189 _public member_ `FVector3f EmissiveFactor;`
- L192 _public member_ `bool bIsDoubleSided;` — material properties
- L193 _public member_ `EAlphaMode AlphaMode;`
- L194 _public member_ `float AlphaCutoff;` — only used when AlphaMode == Mask
- L197 _public member_ `FPacking Packing;` — extension properties
- L198 _public member_ `bool bIsUnlitShadingModel;`
- L199 _public member_ `bool bHasClearCoat;`
- L200 _public member_ `bool bHasSheen;`
- L201 _public member_ `bool bHasTransmission;`
- L202 _public member_ `bool bHasIOR;`
- L203 _public member_ `bool bHasSpecular;`
- L204 _public member_ `bool bHasEmissiveStrength;`
- L205 _public member_ `FIridescence Iridescence;`
- L206 _public member_ `FAnisotropy Anisotropy;`
- L207 _public member_ `FVolume Volume;`
- L209 _public member_ `TMap<FString, FString> Extras;`
- L211 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L213 _public function_ `FMaterial(const FString& Name) : Name(Name) , BaseColorFactor`
- L235 _public function_ `bool IsOpaque() const`
- L240 _public prototype_ `FMD5Hash GetHash() const;`

#### enum `GLTF::FMaterial::EAlphaMode`  
`enum class EAlphaMode`  
_L52-57_
- L54 _public enumerator_ `Opaque`
- L55 _public enumerator_ `Mask`
- L56 _public enumerator_ `Blend`

#### enum `GLTF::FMaterial::EShadingModel`  
`enum class EShadingModel`  
_L59-63_
- L61 _public enumerator_ `MetallicRoughness`
- L62 _public enumerator_ `SpecularGlossiness`

#### enum `GLTF::FMaterial::EPackingFlags`  
`enum class EPackingFlags`  
_L65-77_
- L68 _public enumerator_ `None = 0x0` — no packing, i.e. default: Unused (R) Roughness (G), Metallic (B) map
- L70 _public enumerator_ `NormalRG = 0x1` — packing two channel (RG) normal map
- L72 _public enumerator_ `OcclusionRoughnessMetallic = 0x2` — packing Occlusion (R), Roughness (G), Metallic (B) map
- L74 _public enumerator_ `RoughnessMetallicOcclusion = 0x4` — packing Roughness (R), Metallic (G), Occlusion (B) map
- L76 _public enumerator_ `NormalRoughnessMetallic = NormalRG | 0x8` — packing Normal (RG), Roughness (B), Metallic (A) map

#### struct `GLTF::FMaterial::FMetallicRoughness`  
`struct FMetallicRoughness`  
_L79-84_
- L81 _public member_ `FTextureMap Map;`
- L82 _public member_ `float MetallicFactor = 1.0f;`
- L83 _public member_ `float RoughnessFactor = 1.0f;`

#### struct `GLTF::FMaterial::FSpecularGlossiness`  
`struct FSpecularGlossiness`  
_L87-92_
- desc: "pbrSpecularGlossiness" extension Implements a specular glossiness shading model and is mutually exclusive with "specular" extension, which uses metallic roughness model
- L89 _public member_ `FTextureMap Map;`
- L90 _public member_ `FVector SpecularFactor = FVector(1.0f);`
- L91 _public member_ `float GlossinessFactor = 1.0f;`

#### struct `GLTF::FMaterial::FClearCoat`  
`struct FClearCoat`  
_L93-103_
- L95 _public member_ `float ClearCoatFactor = 0.0f;`
- L96 _public member_ `FTextureMap ClearCoatMap;`
- L98 _public member_ `float Roughness = 0.0f;`
- L99 _public member_ `FTextureMap RoughnessMap;`
- L101 _public member_ `float NormalMapUVScale = 1.0f;`
- L102 _public member_ `FTextureMap NormalMap;`

#### struct `GLTF::FMaterial::FTransmission`  
`struct FTransmission`  
_L104-108_
- L106 _public member_ `float TransmissionFactor = 0.0f;`
- L107 _public member_ `FTextureMap TransmissionMap;`

#### struct `GLTF::FMaterial::FSheen`  
`struct FSheen`  
_L109-115_
- L111 _public member_ `FVector SheenColorFactor = FVector::Zero();`
- L112 _public member_ `FTextureMap SheenColorMap;`
- L113 _public member_ `float SheenRoughnessFactor = 0.f;`
- L114 _public member_ `FTextureMap SheenRoughnessMap;`

#### struct `GLTF::FMaterial::FSpecular`  
`struct FSpecular`  
_L116-122_
- desc: "specular" extension
- L118 _public member_ `float SpecularFactor = 1.0f;`
- L119 _public member_ `FTextureMap SpecularMap;`
- L120 _public member_ `FVector SpecularColorFactor = FVector(1.0f, 1.0f, 1.0f);`
- L121 _public member_ `FTextureMap SpecularColorMap;`

#### struct `GLTF::FMaterial::FPacking`  
`struct FPacking`  
_L124-129_
- L126 _public member_ `int Flags = (int)EPackingFlags::None;` — see EPackingFlags
- L127 _public member_ `FTextureMap Map;`
- L128 _public member_ `FTextureMap NormalMap;`

#### struct `GLTF::FMaterial::FIridescence`  
`struct FIridescence`  
_L131-147_
- L140 _public member_ `float Factor = 0.0f;`
- L141 _public member_ `FTextureMap Texture;`
- L142 _public member_ `float IOR = 1.3f;`
- L144 _public member_ `FThickness Thickness;`
- L146 _public member_ `bool bHasIridescence = false;`

#### struct `GLTF::FMaterial::FIridescence::FThickness`  
`struct FThickness`  
_L133-138_
- L135 _public member_ `float Minimum = 100.0f;`
- L136 _public member_ `float Maximum = 400.0f;`
- L137 _public member_ `FTextureMap Texture;`

#### struct `GLTF::FMaterial::FAnisotropy`  
`struct FAnisotropy`  
_L149-157_
- L151 _public member_ `FTextureMap Texture;`
- L153 _public member_ `float Strength = 0.0;`
- L154 _public member_ `float Rotation = 0.0;`
- L156 _public member_ `bool bHasAnisotropy = false;`

#### struct `GLTF::FMaterial::FVolume`  
`struct FVolume`  
_L159-166_
- L161 _public member_ `FTextureMap ThicknessTexture;`
- L162 _public member_ `float Thickness = 0.f;`
- L163 _public member_ `float AttenuationDistance = 10.f;` — Theoretically +∞, should definitely not be 0, 10.f if a good compromise as it renders no attenuation
- L164 _public member_ `FVector AttenuationColor{ 1, 1, 1 };`
- L165 _public member_ `bool bHasVolume = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFMaterialExpressions.h` (Public)


#### enum `GLTF::EMaterialExpressionType`  
`enum class EMaterialExpressionType`  
_L17-25_
- L19 _public enumerator_ `ConstantColor`
- L20 _public enumerator_ `ConstantScalar`
- L21 _public enumerator_ `FunctionCall`
- L22 _public enumerator_ `Generic`
- L23 _public enumerator_ `Texture`
- L24 _public enumerator_ `TextureCoordinate`

#### enum `GLTF::EGLTFMaterialShadingModel`  
`enum class EGLTFMaterialShadingModel`  
_L27-34_
- L29 _public enumerator_ `DefaultLit`
- L30 _public enumerator_ `Subsurface`
- L31 _public enumerator_ `ClearCoat`
- L32 _public enumerator_ `ThinTranslucent`
- L33 _public enumerator_ `Unlit`

#### class `GLTF::ITextureElement`  
`class ITextureElement`  
_L36-40_
- L39 _public prototype_ `virtual ~ITextureElement() = default;`

#### class `GLTF::FMaterialExpression`  
`class FMaterialExpression`  
_L42-79_
- L45 _public prototype_ `virtual ~FMaterialExpression() = default;`
- L47 _public function_ `virtual FMaterialExpressionInput* GetInput(int32 Index)`
- L52 _public function_ `virtual int32 GetInputCount() const`
- L57 _public function_ `EMaterialExpressionType GetType() const`
- L63 _public function_ `template <EMaterialExpressionType T> bool IsA() const`
- L68 _public prototype_ `void ConnectExpression(FMaterialExpressionInput& ExpressionInput, int32 OutputIndex);`
- L71 _protected prototype_ `FMaterialExpression();`
- L72 _protected prototype_ `FMaterialExpression(const FMaterialExpression& Expr);`
- L73 _protected prototype_ `explicit FMaterialExpression(int Type);`
- L76 _protected member_ `EMaterialExpressionType Type;`

#### class `GLTF::FMaterialExpressionInput`  
`class FMaterialExpressionInput`  
_L81-111_
- L84 _public function_ `FMaterialExpression* GetExpression()`
- L89 _public function_ `const FMaterialExpression* GetExpression() const`
- L94 _public function_ `int32 GetOutputIndex() const`
- L100 _private prototype_ `FMaterialExpressionInput(const FString& Name);`
- L103 _private member_ `FString Name;`
- L104 _private member_ `FMaterialExpression* Expression;`
- L105 _private member_ `int32 OutputIndex;`

#### class `GLTF::FMaterialExpressionParameter`  
`class FMaterialExpressionParameter : public FMaterialExpression`  
_L113-129_
- inherits: `FMaterialExpression`
- L116 _public prototype_ `virtual ~FMaterialExpressionParameter() = default;`
- L118 _public prototype_ `void SetName(const TCHAR* Name);`
- L119 _public prototype_ `const TCHAR* GetName() const;`
- L120 _public prototype_ `void SetGroupName(const TCHAR* GroupName);`
- L121 _public prototype_ `const TCHAR* GetGroupName() const;`
- L124 _protected prototype_ `explicit FMaterialExpressionParameter(int Type);`
- L127 _private member_ `FString Name;`
- L128 _private member_ `FString GroupName;`

#### class `GLTF::FMaterialExpressionScalar`  
`class FMaterialExpressionScalar : public FMaterialExpressionParameter`  
_L131-156_
- inherits: `FMaterialExpressionParameter`
- L139 _public function_ `FMaterialExpressionScalar() : FMaterialExpressionParameter(Type)`
- L144 _public function_ `float& GetScalar()`
- L149 _public function_ `float GetScalar() const`
- L155 _private member_ `float Scalar;`

#### enum `GLTF::FMaterialExpressionScalar::(anonymous)`  
``  
_L135-137_

#### class `GLTF::FMaterialExpressionColor`  
`class FMaterialExpressionColor : public FMaterialExpressionParameter`  
_L158-180_
- inherits: `FMaterialExpressionParameter`
- L166 _public prototype_ `FMaterialExpressionColor();`
- L168 _public function_ `FLinearColor& GetColor()`
- L173 _public function_ `const FLinearColor& GetColor() const`
- L179 _private member_ `FLinearColor Color;`

#### enum `GLTF::FMaterialExpressionColor::(anonymous)`  
``  
_L162-164_

#### class `GLTF::FMaterialExpressionTexture`  
`class FMaterialExpressionTexture : public FMaterialExpressionParameter`  
_L182-213_
- inherits: `FMaterialExpressionParameter`
- L190 _public prototype_ `FMaterialExpressionTexture();`
- L192 _public function_ `void SetTexture(ITextureElement* InTexture)`
- L197 _public function_ `ITextureElement* GetTexture() const`
- L202 _public function_ `FMaterialExpressionInput& GetInputCoordinate()`
- L207 _public prototype_ `virtual FMaterialExpressionInput* GetInput(int32 Index) override;`
- L208 _public prototype_ `virtual int32 GetInputCount() const override;`
- L211 _private member_ `FMaterialExpressionInput InputCoordinate;`
- L212 _private member_ `ITextureElement* Texture;`

#### enum `GLTF::FMaterialExpressionTexture::(anonymous)`  
``  
_L186-188_

#### class `GLTF::FMaterialExpressionTextureCoordinate`  
`class FMaterialExpressionTextureCoordinate : public FMaterialExpression`  
_L215-237_
- inherits: `FMaterialExpression`
- L223 _public prototype_ `FMaterialExpressionTextureCoordinate();`
- L225 _public function_ `void SetCoordinateIndex(int32 InCoordinateIndex)`
- L230 _public function_ `int32 GetCoordinateIndex() const`
- L236 _private member_ `int32 CoordinateIndex;`

#### enum `GLTF::FMaterialExpressionTextureCoordinate::(anonymous)`  
``  
_L219-221_

#### class `GLTF::FMaterialExpressionGeneric`  
`class FMaterialExpressionGeneric : public FMaterialExpression`  
_L239-288_
- inherits: `FMaterialExpression`
- L247 _public prototype_ `FMaterialExpressionGeneric();`
- L249 _public function_ `void SetExpressionName(const TCHAR* InExpressionName)`
- L254 _public function_ `const TCHAR* GetExpressionName() const`
- L259 _public prototype_ `virtual FMaterialExpressionInput* GetInput(int32 Index) override;`
- L260 _public prototype_ `virtual int32 GetInputCount() const override;`
- L262 _public function_ `void SetBoolProperty(const TCHAR* Name, bool Value)`
- L267 _public function_ `void SetFloatProperty(const TCHAR* Name, float Value)`
- L272 _public function_ `const TMap<FString, bool>& GetBoolProperties() const`
- L277 _public function_ `const TMap<FString, float>& GetFloatProperties() const`
- L283 _private member_ `FString ExpressionName;`
- L284 _private member_ `TArray<FMaterialExpressionInput> Inputs;`
- L286 _private member_ `TMap<FString, bool> BoolProperties;`
- L287 _private member_ `TMap<FString, float> FloatProperties;`

#### enum `GLTF::FMaterialExpressionGeneric::(anonymous)`  
``  
_L243-245_

#### class `GLTF::FMaterialExpressionFunctionCall`  
`class FMaterialExpressionFunctionCall : public FMaterialExpression`  
_L290-316_
- inherits: `FMaterialExpression`
- L298 _public prototype_ `FMaterialExpressionFunctionCall();`
- L300 _public function_ `void SetFunctionPathName(const TCHAR* InFunctionPathName)`
- L305 _public function_ `const TCHAR* GetFunctionPathName() const`
- L310 _public prototype_ `virtual FMaterialExpressionInput* GetInput(int32 Index) override;`
- L311 _public prototype_ `virtual int32 GetInputCount() const override;`
- L314 _private member_ `FString FunctionPathName;`
- L315 _private member_ `TArray<FMaterialExpressionInput> Inputs;`

#### enum `GLTF::FMaterialExpressionFunctionCall::(anonymous)`  
``  
_L294-296_

#### class `GLTF::FMaterialElement`  
`class FMaterialElement`  
_L318-383_
- L321 _public prototype_ `FMaterialElement(const FString& Name);`
- L322 _public prototype_ `virtual ~FMaterialElement();`
- L324 _public prototype_ `virtual int GetBlendMode() const = 0;`
- L325 _public prototype_ `virtual void SetBlendMode(int InBlendMode) = 0;`
- L326 _public prototype_ `virtual bool GetTwoSided() const = 0;`
- L327 _public prototype_ `virtual void SetTwoSided(bool bTwoSided) = 0;`
- L328 _public prototype_ `virtual bool GetIsThinSurface() const = 0;`
- L329 _public prototype_ `virtual void SetIsThinSurface(bool bIsThinSurface) = 0;`
- L330 _public prototype_ `virtual void SetShadingModel(EGLTFMaterialShadingModel InShadingModel) = 0;`
- L331 _public prototype_ `virtual void SetTranslucencyLightingMode(int InLightingMode) = 0;`
- L333 _public prototype_ `virtual void Finalize() = 0;`
- L335 _public prototype_ `FMD5Hash GetGLTFMaterialHash() const;`
- L336 _public prototype_ `void SetGLTFMaterialHash(FMD5Hash Hash);`
- L338 _public prototype_ `const FString& GetName() const;`
- L340 _public prototype_ `FMaterialExpressionInput& GetBaseColor();`
- L341 _public prototype_ `FMaterialExpressionInput& GetMetallic();`
- L342 _public prototype_ `FMaterialExpressionInput& GetSpecular();`
- L343 _public prototype_ `FMaterialExpressionInput& GetRoughness();`
- L344 _public prototype_ `FMaterialExpressionInput& GetEmissiveColor();`
- L345 _public prototype_ `FMaterialExpressionInput& GetOpacity();`
- L346 _public prototype_ `FMaterialExpressionInput& GetNormal();`
- L347 _public prototype_ `FMaterialExpressionInput& GetWorldDisplacement();`
- L348 _public prototype_ `FMaterialExpressionInput& GetRefraction();`
- L349 _public prototype_ `FMaterialExpressionInput& GetAmbientOcclusion();`
- L350 _public prototype_ `FMaterialExpressionInput& GetClearCoat();`
- L351 _public prototype_ `FMaterialExpressionInput& GetClearCoatRoughness();`
- L353 _public prototype_ `int32 GetExpressionsCount() const;`
- L354 _public prototype_ `FMaterialExpression* GetExpression(int32 Index);`
- L356 _public prototype_ `FMaterialExpression* AddMaterialExpression(EMaterialExpressionType ExpressionType);`
- L358 _public prototype_ `template <typename T> T* AddMaterialExpression();`
- L361 _protected member_ `FString Name;`
- L362 _protected member_ `FMaterialExpressionInput BaseColor;`
- L363 _protected member_ `FMaterialExpressionInput Metallic;`
- L364 _protected member_ `FMaterialExpressionInput Specular;`
- L365 _protected member_ `FMaterialExpressionInput Roughness;`
- L366 _protected member_ `FMaterialExpressionInput EmissiveColor;`
- L367 _protected member_ `FMaterialExpressionInput Opacity;`
- L368 _protected member_ `FMaterialExpressionInput Normal;`
- L369 _protected member_ `FMaterialExpressionInput WorldDisplacement;`
- L370 _protected member_ `FMaterialExpressionInput Refraction;`
- L371 _protected member_ `FMaterialExpressionInput AmbientOcclusion;`
- L372 _protected member_ `FMaterialExpressionInput ClearCoat;`
- L373 _protected member_ `FMaterialExpressionInput ClearCoatRoughness;`
- L375 _protected member_ `TArray<FMaterialExpression*> Expressions;`
- L377 _protected member_ `GLTF::FMaterialExpression* ThinTranslucentMaterialOutput;`
- L378 _protected member_ `GLTF::FMaterialExpression* ClearCoatBottomNormalOutput;`
- L380 _protected member_ `bool bIsFinal;`
- L382 _protected member_ `FMD5Hash GLTFMaterialHash;`
- L385 _function_ `inline const FString& FMaterialElement::GetName() const`
- L390 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetBaseColor()`
- L394 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetMetallic()`
- L398 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetSpecular()`
- L402 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetRoughness()`
- L406 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetEmissiveColor()`
- L410 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetOpacity()`
- L414 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetNormal()`
- L418 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetWorldDisplacement()`
- L422 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetRefraction()`
- L426 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetAmbientOcclusion()`
- L430 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetClearCoat()`
- L434 _function_ `inline FMaterialExpressionInput& FMaterialElement::GetClearCoatRoughness()`
- L440 _function_ `template <> inline FMaterialExpressionScalar* FMaterialElement::AddMaterialExpression<FMaterialExpressionScalar>()`
- L446 _function_ `template <> inline FMaterialExpressionColor* FMaterialElement::AddMaterialExpression<FMaterialExpressionColor>()`
- L452 _function_ `template <> inline FMaterialExpressionTexture* FMaterialElement::AddMaterialExpression<FMaterialExpressionTexture>()`
- L458 _function_ `template <> inline FMaterialExpressionTextureCoordinate* FMaterialElement::AddMaterialExpression<FMaterialExpressionTextureCoordinate>()`
- L465 _function_ `template <> inline FMaterialExpressionFunctionCall* FMaterialElement::AddMaterialExpression<FMaterialExpressionFunctionCall>()`
- L471 _function_ `template <> inline FMaterialExpressionGeneric* FMaterialElement::AddMaterialExpression<FMaterialExpressionGeneric>()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GLTFCORE_API`
- L10 _namespace_ `namespace GLTF`
- L136 _enumerator_ `Type = (int)EMaterialExpressionType::ConstantScalar` (scope `GLTF::FMaterialExpressionScalar::__anon4fe070c80103`)
- L163 _enumerator_ `Type = (int)EMaterialExpressionType::ConstantColor` (scope `GLTF::FMaterialExpressionColor::__anon4fe070c80203`)
- L187 _enumerator_ `Type = (int)EMaterialExpressionType::Texture` (scope `GLTF::FMaterialExpressionTexture::__anon4fe070c80303`)
- L220 _enumerator_ `Type = (int)EMaterialExpressionType::TextureCoordinate` (scope `GLTF::FMaterialExpressionTextureCoordinate::__anon4fe070c80403`)
- L244 _enumerator_ `Type = (int)EMaterialExpressionType::Generic` (scope `GLTF::FMaterialExpressionGeneric::__anon4fe070c80503`)
- L295 _enumerator_ `Type = (int)EMaterialExpressionType::FunctionCall` (scope `GLTF::FMaterialExpressionFunctionCall::__anon4fe070c80603`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFMaterialFactory.h` (Public)


#### enum `GLTF::ETextureMode`  
`enum class ETextureMode`  
_L20-25_
- L22 _public enumerator_ `Color`
- L23 _public enumerator_ `Grayscale`
- L24 _public enumerator_ `Normal`

#### class `GLTF::ITextureFactory`  
`class ITextureFactory`  
_L27-35_
- L30 _public prototype_ `virtual ~ITextureFactory() = default;`
- L32 _public prototype_ `virtual ITextureElement* CreateTexture(const GLTF::FTexture& Texture, UObject* ParentPackage, EObjectFlags Flags, GLTF::ETextureMode TextureMode) = 0;`
- L34 _public prototype_ `virtual void CleanUp() = 0;`

#### class `GLTF::IMaterialElementFactory`  
`class IMaterialElementFactory`  
_L37-43_
- L40 _public prototype_ `virtual ~IMaterialElementFactory() = default;`
- L42 _public prototype_ `virtual FMaterialElement* CreateMaterial(const TCHAR* Name, UObject* ParentPackage, EObjectFlags Flags) = 0;`

#### class `GLTF::FMaterialFactory`  
`class FMaterialFactory`  
_L45-63_
- L48 _public prototype_ `FMaterialFactory(IMaterialElementFactory* MaterialElementFactory, ITextureFactory* TextureFactory);`
- L49 _public prototype_ `~FMaterialFactory();`
- L51 _public prototype_ `const TArray<FMaterialElement*>& CreateMaterials(const GLTF::FAsset& Asset, UObject* ParentPackage, EObjectFlags Flags);`
- L53 _public prototype_ `const TArray<FLogMessage>& GetLogMessages() const;`
- L54 _public prototype_ `const TArray<FMaterialElement*>& GetMaterials() const;`
- L56 _public prototype_ `IMaterialElementFactory& GetMaterialElementFactory();`
- L57 _public prototype_ `ITextureFactory& GetTextureFactory();`
- L59 _public prototype_ `void CleanUp();`
- L62 _private member_ `TUniquePtr<FMaterialFactoryImpl> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GLTFCORE_API`
- L12 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFMesh.h` (Public)


#### struct `GLTF::FTriangle`  
`struct FTriangle`  
_L14-24_
- desc: for storing triangle indices as a unit
- L16 _public member_ `uint32 A, B, C;`
- L16 _public member_ `uint32 A, B, C;`
- L16 _public member_ `uint32 A, B, C;`
- L18 _public function_ `FTriangle() : A(0) , B(0) , C(0)`

#### struct `GLTF::FJointInfluence`  
`struct FJointInfluence`  
_L26-36_
- L28 _public member_ `FVector4 Weight;`
- L29 _public member_ `uint16 ID[4];`
- L31 _public function_ `FJointInfluence(const FVector4& InWeight) : Weight(InWeight) , ID`

#### struct `GLTF::FVariantMapping`  
`struct FVariantMapping`  
_L38-42_
- L40 _public member_ `int32 MaterialIndex;`
- L41 _public member_ `TArray<int32> VariantIndices;`

#### struct `GLTF::FAttributeAccessors`  
`struct FAttributeAccessors`  
_L44-60_
- L47 _public prototype_ `FAttributeAccessors(const TArray<TPair<EMeshAttributeType, FAccessor&>>& InAttributeAccessors, bool bInMorphTarget);` — Expects elements in the exact same order as the EMeshAttributeType.
- L50 _protected prototype_ `bool HasAttributeAccessor(const EMeshAttributeType& Type) const;`
- L51 _protected prototype_ `const FAccessor& GetAttributeAccessor(const EMeshAttributeType& Type) const;`
- L53 _protected prototype_ `bool AreAttributeAccessorsValid(bool& bHasData, uint32 ExpectedElementCount) const;`
- L55 _protected prototype_ `void HashAttributes(FMD5& MD5) const;`
- L58 _private member_ `TArray<TPair<EMeshAttributeType, FAccessor&>> AttributeAccessors;`
- L59 _private member_ `bool bMorphTarget;`

#### struct `GLTF::FMorphTarget`  
`struct FMorphTarget : FAttributeAccessors`  
_L62-88_
- inherits: `FAttributeAccessors`
- L64 _public prototype_ `FMorphTarget(const TArray<TPair<EMeshAttributeType, FAccessor&>>& InAttributeAccessors );`
- L66 _public prototype_ `bool IsValid(uint32 ExpectedElementCount) const;`
- L67 _public prototype_ `FMD5Hash GetHash() const;`
- L69 _public function_ `bool HasPositionDisplacements() const`
- L70 _public prototype_ `void GetPositionDisplacements(TArray<FVector3f>& Buffer) const;`
- L71 _public prototype_ `int32 GetNumberOfPositionDisplacements() const;`
- L73 _public function_ `bool HasNormalDisplacements() const`
- L74 _public prototype_ `void GetNormalDisplacements(TArray<FVector3f>& Buffer) const;`
- L75 _public prototype_ `int32 GetNumberOfNormalDisplacements() const;`
- L77 _public function_ `bool HasTangentDisplacements() const`
- L78 _public prototype_ `void GetTangentDisplacements(TArray<FVector4f>& Buffer) const;`
- L79 _public prototype_ `int32 GetNumberOfTangentDisplacements() const;`
- L81 _public prototype_ `bool HasTexCoordDisplacements(uint32 Index) const;`
- L82 _public prototype_ `void GetTexCoordDisplacements(uint32 Index, TArray<FVector2f>& Buffer) const;`
- L83 _public prototype_ `int32 GetNumberOfTexCoordDisplacements(uint32 Index) const;`
- L85 _public function_ `bool HasColorDeltas() const`
- L86 _public prototype_ `void GetColorDeltas(TArray<FVector4f>& Buffer) const;`
- L87 _public prototype_ `int32 GetNumberOfColorDeltas() const;`

#### struct `GLTF::FPrimitive`  
`struct FPrimitive : FAttributeAccessors`  
_L90-158_
- inherits: `FAttributeAccessors`
- L108 _public member_ `static const TArray<EMode> SupportedModes;`
- L109 _public prototype_ `static FString ToString(const EMode& Mode);`
- L111 _public member_ `const EMode Mode;`
- L112 _public member_ `const int32 MaterialIndex;`
- L113 _public member_ `TArray<FVariantMapping> VariantMappings;`
- L115 _public member_ `TMap<FString, FString> Extras;`
- L117 _public prototype_ `FPrimitive(EMode InMode, int32 InMaterial, const FAccessor& InIndices, const TArray<TPair<EMeshAttributeType, FAccessor&>>& InAttributeAccessors);`
- L119 _public prototype_ `void GenerateIsValidCache();`
- L120 _public prototype_ `bool IsValid() const;`
- L121 _public prototype_ `FMD5Hash GetHash() const;`
- L123 _public function_ `bool HasPositions() const`
- L124 _public function_ `bool HasNormals() const`
- L125 _public function_ `bool HasTangents() const`
- L126 _public prototype_ `bool HasTexCoords(uint32 Index) const;`
- L127 _public function_ `bool HasColors() const`
- L128 _public function_ `bool HasJointWeights() const`
- L130 _public prototype_ `void GetPositions(TArray<FVector3f>& Buffer) const;`
- L131 _public prototype_ `void GetNormals(TArray<FVector3f>& Buffer) const;`
- L132 _public prototype_ `void GetTangents(TArray<FVector4f>& Buffer) const;`
- L133 _public prototype_ `void GetTexCoords(uint32 Index, TArray<FVector2f>& Buffer) const;`
- L134 _public prototype_ `void GetColors(TArray<FVector4f>& Buffer) const;`
- L135 _public prototype_ `void GetJointInfluences(TArray<FJointInfluence>& Buffer) const;`
- L137 _public prototype_ `FTriangle TriangleVerts(uint32 T) const;`
- L138 _public prototype_ `void GetTriangleIndices(TArray<uint32>& Buffer) const;`
- L140 _public prototype_ `uint32 VertexCount() const;`
- L141 _public prototype_ `uint32 TriangleCount() const;`
- L144 _public member_ `TArray<FMorphTarget> MorphTargets;`
- L147 _public function_ `uint32 GetIndicesAccessorIndex()`
- L148 _public function_ `uint32 GetAttributeAccessorIndex(const EMeshAttributeType& Type)`
- L151 _private prototype_ `bool IsValidPrivate() const;`
- L154 _private member_ `const FAccessor& Indices;` — index buffer
- L157 _private member_ `TOptional<bool> bIsValidCache;` — Validity cache:

#### enum `GLTF::FPrimitive::EMode`  
`enum class EMode`  
_L92-106_
- L95 _public enumerator_ `Points = 0` — valid but unsupported
- L96 _public enumerator_ `Lines = 1`
- L97 _public enumerator_ `LineLoop = 2`
- L98 _public enumerator_ `LineStrip = 3`
- L100 _public enumerator_ `Triangles = 4` — initially supported
- L101 _public enumerator_ `TriangleStrip = 5`
- L102 _public enumerator_ `TriangleFan = 6`
- L105 _public enumerator_ `Unknown = 7`

#### struct `GLTF::FMesh`  
`struct FMesh`  
_L161-189_
- L163 _public member_ `FString Name;`
- L164 _public member_ `TArray<FPrimitive> Primitives;`
- L166 _public member_ `TArray<float> MorphTargetWeights;`
- L167 _public member_ `TArray<FString> MorphTargetNames;`
- L169 _public member_ `TMap<FString, FString> Extras;`
- L171 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L173 _public prototype_ `bool HasNormals() const;`
- L174 _public prototype_ `bool HasTangents() const;`
- L175 _public prototype_ `bool HasTexCoords(uint32 Index) const;`
- L176 _public prototype_ `bool HasColors() const;`
- L177 _public prototype_ `bool HasJointWeights() const;`
- L179 _public prototype_ `void GenerateIsValidCache(bool GenerateIsValidCacheForPrimitives = true);`
- L180 _public prototype_ `bool IsValid() const;`
- L181 _public prototype_ `FMD5Hash GetHash() const;`
- L183 _public prototype_ `int32 NumberOfMorphTargetsPerPrimitive() const;`
- L186 _private prototype_ `bool IsValidPrivate() const;`
- L188 _private member_ `TOptional<bool> bIsValidCache;` — Validity cache:
- L193 _function_ `inline bool FMesh::HasNormals() const`
- L198 _function_ `inline bool FMesh::HasTangents() const`
- L203 _function_ `inline bool FMesh::HasTexCoords(uint32 Index) const`
- L208 _function_ `inline bool FMesh::HasColors() const`
- L213 _function_ `inline bool FMesh::HasJointWeights() const`
- L231 _function_ `inline void FMesh::GenerateIsValidCache(bool GenerateIsValidCacheForPrimitives)`
- L243 _function_ `inline bool FMesh::IsValid() const`
- L255 _function_ `inline bool FMesh::IsValidPrivate() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace GLTF`
- L195 _function_ `return Primitives.FindByPredicate([](const FPrimitive& Prim) { return Prim.HasNormals(); }) != nullptr;` (scope `GLTF::FMesh::HasNormals`)
- L200 _function_ `return Primitives.FindByPredicate([](const FPrimitive& Prim) { return Prim.HasTangents(); }) != nullptr;` (scope `GLTF::FMesh::HasTangents`)
- L205 _function_ `return Primitives.FindByPredicate([Index](const FPrimitive& Prim) { return Prim.HasTexCoords(Index); }) != nullptr;` (scope `GLTF::FMesh::HasTexCoords`)
- L210 _function_ `return Primitives.FindByPredicate([](const FPrimitive& Prim) { return Prim.HasColors(); }) != nullptr;` (scope `GLTF::FMesh::HasColors`)
- L215 _function_ `const bool Result = Primitives.FindByPredicate([](const auto& Prim) { return Prim.HasJointWeights(); }) != nullptr;` (scope `GLTF::FMesh::HasJointWeights`)
- L258 _function_ `bool bIsValid = Primitives.FindByPredicate([](const FPrimitive& Prim) { return !Prim.IsValid(); }) == nullptr;` (scope `GLTF::FMesh::IsValidPrivate`) — Validate Primitives:

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFMeshFactory.h` (Public)


#### class `GLTF::FMeshFactory`  
`class FMeshFactory`  
_L20-43_
- L23 _public prototype_ `FMeshFactory();`
- L24 _public prototype_ `~FMeshFactory();`
- L26 _public typedef_ `using FIndexVertexIdMap = TMap<int32, FVertexID>;`
- L28 _public prototype_ `void FillMeshDescription(const GLTF::FMesh &Mesh, const FTransform& MeshGlobalTransform , FMeshDescription* MeshDescription, const TArray<float>& MorphTargetWeights = TArray<float>());`
- L30 _public prototype_ `float GetUniformScale() const;`
- L31 _public prototype_ `void SetUniformScale(float Scale);`
- L33 _public prototype_ `const TArray<FLogMessage>& GetLogMessages() const;`
- L35 _public prototype_ `void SetReserveSize(uint32 Size);`
- L37 _public prototype_ `TArray<FMeshFactory::FIndexVertexIdMap>& GetPositionIndexToVertexIdPerPrim() const;`
- L39 _public prototype_ `void CleanUp();`
- L42 _private member_ `TUniquePtr<FMeshFactoryImpl> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFCORE_API`
- L15 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFNode.h` (Public)


#### struct `GLTF::FNode`  
`struct FNode`  
_L14-108_
- L60 _public member_ `FString Name;`
- L61 _public member_ `FTransform Transform;`
- L62 _public member_ `TArray<int32> Children;` — each is an index into FAsset::Nodes
- L63 _public member_ `EType Type;`
- L65 _public member_ `int32 MeshIndex;` — index into FAsset::Meshes
- L69 _public member_ `int32 Skindex;` — Skindex is the skin used by the mesh at this node. It's not the joints belonging *to* a skin
- L70 _public member_ `int32 CameraIndex;` — index into FAsset::Cameras
- L71 _public member_ `int32 LightIndex;` — index into FAsset::Lights
- L72 _public member_ `FLightInstanceIES LightIES;`
- L74 _public member_ `int32 Index;` — index of FNode in GLTFAsset.Nodes array.
- L75 _public member_ `int32 ParentIndex;`
- L76 _public member_ `int32 ParentJointIndex;` — glTF marks the Nodes in Skins.Joints as a joint, however there are certain indirections that still make a node into a joint. (such as skin.joints having gaps/skips in the node hierarchy)
- L77 _public member_ `int32 DirectParentJointIndex;` — With this variable we are tracking the original Parent Joint Index. Joint index that was actually marked by the glTF file without any indirections, aka index is part of the Skin.Joints list.
- L78 _public member_ `int32 RootJointIndex;` — only valid if node is of Joint Type
- L80 _public member_ `TArray<float> MorphTargetWeights;` — for the instantiated mesh with morph targets.
- L82 _public member_ `TMap<int, FMatrix> SkinIndexToGlobalInverseBindMatrix;`
- L83 _public member_ `TMap<int, FTransform> SkinIndexToLocalBindTransform;`
- L85 _public member_ `bool bHasLocalBindPose;` — bind pose would be CurrentNode.GlobalInverseBindTransform.Inverse() * ParentNode.GlobalInverseBindTransform
- L86 _public member_ `FTransform LocalBindPose;` — First Skin that's using the joint will fill the LocalBindPose.
- L90 _public member_ `TMap<FString, FString> Extras;`
- L92 _public member_ `FString UniqueId;`
- L94 _public function_ `FNode() : Type(EType::None) , MeshIndex(INDEX_NONE) , Skindex(INDEX_NONE) , CameraIndex(INDEX_NONE) , LightIndex(INDEX_NONE) , Index(INDEX_NONE) , ParentIndex(INDEX_NONE) , ParentJointIndex(INDEX_NONE) , DirectParentJointIndex(INDEX_NONE) , RootJointIndex(INDEX_NONE) , bHasLocalBindPose(false)`

#### struct `GLTF::FNode::FLightInstanceIES`  
`struct FLightInstanceIES`  
_L16-47_
- L18 _public member_ `int32 Index = INDEX_NONE;` — index into FAsset::LightsIES
- L20 _public member_ `float IntensityMultipler = 1.f;`
- L21 _public member_ `bool bHasIntensityMultiplier = false;` — IES brightness scale
- L23 _public member_ `FVector Color = FVector(1.f);`
- L24 _public member_ `bool bHasColor = false;`
- L26 _public function_ `FString GetHash() const`

#### enum `GLTF::FNode::EType`  
`enum class EType`  
_L49-58_
- L51 _public enumerator_ `None`
- L52 _public enumerator_ `Transform`
- L53 _public enumerator_ `Joint`
- L54 _public enumerator_ `Mesh`
- L55 _public enumerator_ `MeshSkinned`
- L56 _public enumerator_ `Camera`
- L57 _public enumerator_ `Light`

#### struct `GLTF::FCamera`  
`struct FCamera`  
_L110-150_
- L127 _public member_ `const FNode& Node;`
- L128 _public member_ `FString Name;`
- L133 _public member_ `float ZNear;`
- L134 _public member_ `float ZFar;`
- L135 _public member_ `bool bIsPerspective;`
- L137 _public member_ `TMap<FString, FString> Extras;`
- L139 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L141 _public function_ `FCamera(const FNode& Node) : Node(Node) , ZNear(0.f) , ZFar(100.f) , bIsPerspective(true)`

#### struct `GLTF::FCamera::FPerspective`  
`struct FPerspective`  
_L112-118_
- L115 _public member_ `float Fov;` — vertical field of view in radians
- L117 _public member_ `float AspectRatio;` — aspect ratio of the field of view

#### struct `GLTF::FCamera::FOrthographic`  
`struct FOrthographic`  
_L119-125_
- L122 _public member_ `float XMagnification;` — horizontal magnification of the view
- L124 _public member_ `float YMagnification;` — vertical magnification of the view

#### union `GLTF::FCamera::(anonymous)`  
`union`  
_L129-132_

#### struct `GLTF::FLightIES`  
`struct FLightIES`  
_L152-167_
- L154 _public member_ `int32 Index;` — serves as idintifer as well.
- L156 _public member_ `FString URI;`
- L157 _public member_ `FString FilePath;`
- L159 _public member_ `int32 BufferViewIndex = INDEX_NONE;`
- L160 _public member_ `uint32 DataByteLength;`
- L161 _public member_ `const uint8* Data;`
- L163 _public member_ `FString MimeType;`
- L165 _public member_ `FString Name;`
- L166 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames

#### struct `GLTF::FLight`  
`struct FLight`  
_L169-209_
- L190 _public member_ `const FNode* Node;`
- L191 _public member_ `FString Name;`
- L192 _public member_ `EType Type;`
- L193 _public member_ `FVector Color;`
- L194 _public member_ `float Intensity;`
- L196 _public member_ `float Range;` — Must be > 0. When undefined, range is assumed to be infinite.
- L197 _public member_ `FSpot Spot;`
- L199 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L201 _public function_ `FLight(const FNode* Node) : Node(Node) , Type(EType::Point) , Color(1.f) , Intensity(1.f) , Range(1e+20f)`

#### enum `GLTF::FLight::EType`  
`enum class EType`  
_L171-176_
- L173 _public enumerator_ `Directional`
- L174 _public enumerator_ `Point`
- L175 _public enumerator_ `Spot`

#### struct `GLTF::FLight::FSpot`  
`struct FSpot`  
_L178-188_
- L180 _public member_ `float InnerConeAngle;`
- L181 _public member_ `float OuterConeAngle;`
- L183 _public function_ `FSpot() : InnerConeAngle(0.f) , OuterConeAngle(PI / 4.f)`

#### struct `GLTF::FSkinInfo`  
`struct FSkinInfo`  
_L211-228_
- L213 _public member_ `const FAccessor& InverseBindMatrices;`
- L214 _public member_ `FString Name;`
- L215 _public member_ `TArray<int32> Joints;` — each is an index into FAsset::Nodes
- L216 _public member_ `int32 Skeleton = INDEX_NONE;` — root node, index into FAsset::Nodes
- L218 _public member_ `TMap<FString, FString> Extras;`
- L220 _public member_ `bool bUsed = false;`
- L222 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L224 _public function_ `FSkinInfo(const FAccessor& InverseBindMatrices) : InverseBindMatrices(InverseBindMatrices)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GLTF`
- L12 _namespace_ `namespace GLTF`
- L130 _member_ `FOrthographic Orthographic;` (scope `GLTF::FCamera::__anon40fe291c010a`)
- L131 _member_ `FPerspective Perspective;` (scope `GLTF::FCamera::__anon40fe291c010a`)

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFReader.h` (Public)


#### class `GLTF::FFileReader`  
`class FFileReader : public FBaseLogger`  
_L23-99_
- inherits: `FBaseLogger`
- L26 _public prototype_ `FFileReader();`
- L27 _public prototype_ `~FFileReader();`
- L38 _public prototype_ `void ReadFile(const FString& InFilePath, bool bInLoadImageData, bool bInLoadMetadata, GLTF::FAsset& OutAsset);` — Loads the contents of a glTF file into the given asset. @param InFilePath - disk file path @param bInLoadImageData - if false then doesn't loads the data field of FImage @param bInLoadMetadata - load extra asset metadata images from a disk path, images from data sources will always be loaded. @param OutAsset - asset data destination
- L41 _private prototype_ `void LoadMetadata(GLTF::FAsset& Asset);`
- L42 _private prototype_ `void ImportAsset(const FString& FilePath, bool bInLoadImageData, GLTF::FAsset& Asset);`
- L43 _private prototype_ `void AllocateExtraData(const FString& InResourcesPath, bool bInLoadImageData, TArray64<uint8>& OutExtraData);`
- L45 _private prototype_ `void SetupBuffer(const FJsonObject& Object, const FString& Path);`
- L46 _private prototype_ `void SetupBufferView(const FJsonObject& Object) const;`
- L47 _private prototype_ `void SetupAccessor(const FJsonObject& Object) const;`
- L48 _private prototype_ `void SetupMorphTarget(const FJsonObject& Object, GLTF::FPrimitive& Primitive, const bool bMeshQuantized) const;`
- L49 _private prototype_ `void SetupPrimitive(const FJsonObject& Object, GLTF::FMesh& Mesh, const bool bMeshQuantized, const uint32& PrimitiveIndex) const;`
- L50 _private prototype_ `void SetupMesh(const FJsonObject& Object, const bool bMeshQuantized) const;`
- L52 _private prototype_ `void SetupScene(const FJsonObject& Object) const;`
- L53 _private prototype_ `void SetupNode(const FJsonObject& Object) const;`
- L54 _private prototype_ `void SetupCamera(const FJsonObject& Object) const;`
- L55 _private prototype_ `void SetupAnimation(const FJsonObject& Object) const;`
- L56 _private prototype_ `void SetupSkin(const FJsonObject& Object) const;`
- L58 _private prototype_ `void SetupImage(const FJsonObject& Object, const FString& Path, bool bInLoadImageData);`
- L59 _private prototype_ `void SetupSampler(const FJsonObject& Object) const;`
- L60 _private prototype_ `void SetupTexture(const FJsonObject& Object) const;`
- L61 _private prototype_ `void SetupMaterial(const FJsonObject& Object) const;`
- L64 _private prototype_ `template <typename SetupFunc> bool SetupObjects(uint32 ObjectCount, const TCHAR* FieldName, SetupFunc Func) const;`
- L65 _private prototype_ `void SetupUsedSkins() const;`
- L66 _private prototype_ `void SetupNodesType() const;`
- L68 _private prototype_ `void GenerateInverseBindPosesPerSkinIndices() const;` — Per node
- L69 _private prototype_ `void GenerateLocalBindPosesPerSkinIndices() const;` — Per node
- L70 _private prototype_ `void SetLocalBindPosesForJoints() const;` — Per node
- L72 _private prototype_ `void BuildParentJointIndices() const;`
- L73 _private prototype_ `void BuildParentIndices(int32 ParentNodeIndex, int32 DirectParentJointIndex, int32 CurrentNodeIndex) const;`
- L74 _private prototype_ `int32 FindRootJointIndex(int32 CurrentNodeIndex) const;`
- L77 _private prototype_ `void FixNodeTypesForIndirectJoints() const;` — Sets the Node Types to Joint for Nodes that were not marked Joint in Skins, however they have descendant and ancestor both in Skins.
- L78 _private prototype_ `void BuildRootJoints() const;`
- L80 _private prototype_ `void ResolveConflictingTextures();`
- L82 _private prototype_ `bool CheckForErrors(int32 StartIndex = 0) const;`
- L84 _private member_ `uint32 BufferCount;`
- L85 _private member_ `uint32 BufferViewCount;`
- L86 _private member_ `uint32 ImageCount;`
- L88 _private member_ `TSharedPtr<FJsonObject> JsonRoot;`
- L89 _private member_ `FString JsonBuffer;`
- L90 _private member_ `TUniquePtr<FBinaryFileReader> BinaryReader;`
- L91 _private member_ `TUniquePtr<FExtensionsHandler> ExtensionsHandler;`
- L95 _private member_ `GLTF::FAsset* Asset;` — Each mesh has its own primitives array. Each primitive refers to the asset's global accessors array.
- L98 _private member_ `uint8* CurrentBufferOffset;` — Current offset for extra data buffer.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GLTFCORE_API`
- L13 _namespace_ `namespace GLTF`

### `Plugins/Interchange/Runtime/Source/Parsers/GLTFCore/Public/GLTFTexture.h` (Public)


#### struct `GLTF::FImage`  
`struct FImage`  
_L11-38_
- L20 _public member_ `FString Name;`
- L21 _public member_ `FString URI;`
- L22 _public member_ `EFormat Format;`
- L23 _public member_ `FString FilePath;`
- L26 _public member_ `uint32 DataByteLength;` — Image data is kept encoded in Format, to be decoded when needed by Unreal.
- L27 _public member_ `const uint8* Data;`
- L29 _public member_ `TMap<FString, FString> Extras;`
- L31 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L33 _public function_ `FImage() : DataByteLength(0) , Data(nullptr)`

#### enum `GLTF::FImage::EFormat`  
`enum class EFormat`  
_L13-18_
- L15 _public enumerator_ `Unknown`
- L16 _public enumerator_ `PNG`
- L17 _public enumerator_ `JPEG`

#### struct `GLTF::FSampler`  
`struct FSampler`  
_L40-77_
- L61 _public member_ `static const FSampler DefaultSampler;`
- L63 _public member_ `EFilter MinFilter;`
- L64 _public member_ `EFilter MagFilter;`
- L66 _public member_ `EWrap WrapS;`
- L67 _public member_ `EWrap WrapT;`
- L69 _public function_ `FSampler()`

#### enum `GLTF::FSampler::EFilter`  
`enum class EFilter`  
_L42-52_
- L45 _public enumerator_ `Nearest = 9728` — valid for Min & Mag
- L46 _public enumerator_ `Linear = 9729`
- L48 _public enumerator_ `NearestMipmapNearest = 9984` — valid for Min only
- L49 _public enumerator_ `LinearMipmapNearest = 9985`
- L50 _public enumerator_ `NearestMipmapLinear = 9986`
- L51 _public enumerator_ `LinearMipmapLinear = 9987`

#### enum `GLTF::FSampler::EWrap`  
`enum class EWrap`  
_L54-59_
- L56 _public enumerator_ `Repeat = 10497`
- L57 _public enumerator_ `MirroredRepeat = 33648`
- L58 _public enumerator_ `ClampToEdge = 33071`

#### struct `GLTF::FTexture`  
`struct FTexture`  
_L79-95_
- L81 _public member_ `const FImage& Source;`
- L82 _public member_ `const FSampler& Sampler;`
- L83 _public member_ `FString Name;`
- L85 _public member_ `TMap<FString, FString> Extras;`
- L87 _public member_ `FString UniqueId;` — will be generated in FAsset::GenerateNames
- L89 _public function_ `FTexture(const FString& InName, const FImage& InSource, const FSampler& InSampler) : Source(InSource) , Sampler(InSampler) , Name(InName)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`
