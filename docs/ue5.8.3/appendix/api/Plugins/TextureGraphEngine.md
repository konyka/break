# Plugins / TextureGraphEngine

- module root: `Plugins/TextureGraph/Source/TextureGraphEngine`
- headers: 145; symbols: 4445
- symbol kinds: class=260, delegate=29, enum=37, enumerator=282, externvar=1, function=844, macro=159, member=840, namespace=16, prototype=1607, struct=67, typedef=303
- PrivateDependencyModuleNames: MutableRuntime, Slate, SlateCore, UMG
- PublicDependencyModuleNames: AssetTools, Continuable, Core, CoreUObject, DeveloperSettings, Engine, Function2, HTTP, ImageCore, ImageWrapper, ImageWriteQueue, InputCore, Json, JsonUtilities, LibJpegTurbo, Networking, ProceduralMeshComponent, Projects, RHI, RenderCore, RenderDocPlugin, Renderer, Sockets, UnrealEd, XmlParser

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/BlendModes.h` (Other)


#### enum `EBlendModes::Type`  
`enum Type : int`  
_L11-24_
- L13 _public enumerator_ `Normal UMETA(DisplayName = "Copy")`
- L14 _public enumerator_ `Add UMETA(DisplayName = "Add")`
- L15 _public enumerator_ `Subtract UMETA(DisplayName = "Subtract")`
- L16 _public enumerator_ `Multiply UMETA(DisplayName = "Multiply")`
- L17 _public enumerator_ `Divide UMETA(DisplayName = "Divide")`
- L18 _public enumerator_ `Difference UMETA(DisplayName = "Difference")`
- L19 _public enumerator_ `Max UMETA(DisplayName = "Max")`
- L20 _public enumerator_ `Min UMETA(DisplayName = "Min")`
- L21 _public enumerator_ `Step UMETA(DisplayName = "Step")`
- L22 _public enumerator_ `Overlay UMETA(DisplayName = "Overlay")`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EBlendModes`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/Mask/MaskEnums.h` (Other)


#### enum `MaskType`  
`enum class MaskType : uint8`  
_L9-20_
- reflection: `UENUM()`
- L11 _public enumerator_ `PaintMask UMETA(DisplayName = "Paint")`
- L12 _public enumerator_ `SolidMask UMETA(DisplayName = "Solid")`
- L13 _public enumerator_ `ImageMask UMETA(DisplayName = "Image")`
- L14 _public enumerator_ `NoiseMask UMETA(DisplayName = "Noise")`
- L15 _public enumerator_ `PatternMask UMETA(DisplayName = "Pattern")`
- L16 _public enumerator_ `NormalMask UMETA(DisplayName = "Normal")`
- L17 _public enumerator_ `CurvatureMask UMETA(DisplayName = "Curvature")`
- L18 _public enumerator_ `PositionGradient UMETA(DisplayName = "Position Gradient")`
- L19 _public enumerator_ `MasksTypeCount UMETA(DisplayName = "Total mask types")`

#### enum `TransformType`  
`enum class TransformType : uint8`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `Circular UMETA(DisplayName = "Circular")`
- L26 _public enumerator_ `Projection UMETA(DisplayName = "Projection")`

#### enum `MaskModifierType`  
`enum MaskModifierType : int`  
_L30-40_
- reflection: `UENUM()`
- L32 _public enumerator_ `BrightnessMaskModifier UMETA(DisplayName = "Brightness/Contrast")`
- L33 _public enumerator_ `ClampMaskModifier UMETA(DisplayName = "Clamp")`
- L34 _public enumerator_ `InvertMaskModifier UMETA(DisplayName = "Invert")`
- L35 _public enumerator_ `NormalizeMaskModifier UMETA(DisplayName = "Normalize")`
- L36 _public enumerator_ `GradientRemapMaskModifier UMETA(DisplayName = "Gradient Remap")`
- L37 _public enumerator_ `PosterizeMaskModifier UMETA(DisplayName = "Posterize")`
- L38 _public enumerator_ `ScatterMaskModifier UMETA(DisplayName = "Scatter")`
- L39 _public enumerator_ `MaskModifiersTypeCount UMETA(DisplayName = "Total mask modifier types")`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TargetTextureSet.h` (Other)


#### class `TargetTextureSet`  
`class TargetTextureSet : public TextureSet`  
_L18-59_
- inherits: `TextureSet`
- L22 _protected member_ `mutable TMap<FName, TArray<TextureReadyCallback>> Callbacks;` — The callbacks to call when texture is set
- L24 _protected member_ `int32 Id = -1;` — The ID/index into the list of target texture sets
- L25 _protected member_ `FString Name;` — Display name of this target set
- L27 _protected member_ `RenderMeshPtr Mesh = nullptr;` — The render mesh that this this texture set is targetting.
- L31 _protected member_ `TMap<FName, TiledBlobRef> BoundTexturesMap;` — Textures currently bound and dont want deallocation until new textures assigned
- L32 _protected member_ `int32 RenderCount = 0;` — The number of times this layer has been rendered to
- L34 _protected prototype_ `virtual void InitTex(int32 InTypeIndex) override;`
- L35 _protected prototype_ `virtual void BindOnTextureUpdate(RenderMaterial_BPPtr InMaterial, FMaterialMappingInfo MaterialMappingInfo) const;`
- L36 _protected prototype_ `virtual void RegisterCallback(TextureReadyCallback Callback, FMaterialMappingInfo MaterialMappingInfo) const;`
- L37 _protected prototype_ `virtual void UnRegisterCallback(FName TextureName) const;`
- L39 _public prototype_ `TargetTextureSet(int32 InId, const FString& InName, RenderMeshPtr InMesh, int32 InWidth, int32 InHeight);`
- L42 _public prototype_ `void SetMesh(RenderMeshPtr InMesh);`
- L44 _public prototype_ `AsyncBufferResultPtr BindTo(RenderMaterial_BPPtr Material, TArray<struct FMaterialMappingInfo> MaterialMappingInfos);`
- L45 _public prototype_ `AsyncBufferResultPtr BindTo(RenderMaterial_BPPtr Material, struct FMaterialMappingInfo MaterialMappingInfo);`
- L46 _public prototype_ `AsyncBufferResultPtr UnbindFrom(RenderMaterial_BPPtr Material);`
- L48 _public prototype_ `virtual void SetTexture(FName TextureName, TiledBlobRef InTexture) override;`
- L49 _public prototype_ `virtual void FreeAt(FName TextureName) override;`
- L50 _public prototype_ `virtual void Free() override;`
- L54 _public function_ `FORCEINLINE int32 GetId() const`
- L55 _public function_ `FORCEINLINE FString GetName() const`
- L56 _public function_ `FORCEINLINE RenderMeshPtr GetMesh() const`
- L57 _public function_ `FORCEINLINE int32 GetRenderCount() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L12 _typedef_ `typedef TFunction<void(TiledBlobPtr)> TextureReadyCallback;`
- L15 _typedef_ `typedef std::shared_ptr<RenderMesh> RenderMeshPtr;`
- L61 _typedef_ `typedef std::unique_ptr<TargetTextureSet> TargetTextureSetPtr;`
- L62 _typedef_ `typedef std::vector<TargetTextureSetPtr> TargetTextureSetPtrVec;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/Tex.h` (Other)


#### struct `DesiredImageProperties`  
`struct DesiredImageProperties`  
_L29-41_
- L31 _public member_ `FString Name;`
- L32 _public member_ `bool bIsLinear = false;`
- L33 _public member_ `bool bForceSRGB = false;`
- L34 _public member_ `bool bIsGrayscale = false;`
- L35 _public member_ `bool bMipMaps = false;`
- L36 _public member_ `bool bPremultiplyAlpha = false;`
- L37 _public member_ `bool bCalculateDisplacementRange = false;`
- L38 _public member_ `int32 Width = -1;`
- L39 _public member_ `int32 Height = -1;`
- L40 _public member_ `EPixelFormat PixelFormat = static_cast<EPixelFormat>(-1);`

#### struct `TexDescriptor`  
`struct TexDescriptor`  
_L46-75_
- L48 _public member_ `FString Name;` — [Optional] Name of the Texture
- L49 _public member_ `uint32 Width = 0;` — Width of the Texture in pixels
- L50 _public member_ `uint32 Height = 0;` — Height of the Texture in pixels
- L51 _public member_ `EPixelFormat Format = EPixelFormat::PF_R8G8B8A8;` — The pixel format
- L52 _public member_ `uint32 NumChannels = 4;` — Channels per-pixels
- L53 _public member_ `bool bMipMaps = false;` — Whether to use mipmaps or not
- L54 _public member_ `bool bAutoGenerateMipMaps = true;` — Whether to auto-generate mipmaps or not
- L55 _public member_ `bool bIsSRGB = false;` — Whether the Texture is in SRGB space or not
- L56 _public member_ `bool bCompress = false;` — Whether to use compression on the Texture
- L57 _public member_ `bool bUAV = false;` — Whether the resource can create a UAV
- L58 _public member_ `ETextureCompressionQuality CompressionQuality = ETextureCompressionQuality::TCQ_High;` — What quality to use on the compression
- L59 _public member_ `TextureCompressionSettings CompressionSettings = TextureCompressionSettings::TC_Default;` — Compression setting
- L60 _public member_ `FLinearColor ClearColor = FLinearColor::Transparent;`
- L62 _public prototype_ `TexDescriptor();`
- L63 _public prototype_ `TexDescriptor(uint32 InWidth, uint32 InHeight, EPixelFormat InFormat);`
- L64 _public prototype_ `TexDescriptor(uint32 InWidth, uint32 InHeight, EPixelFormat InFormat, bool bInSRGB);`
- L65 _public prototype_ `TexDescriptor(uint32 InWidth, uint32 InHeight, EPixelFormat InFormat, bool bInMipMaps, bool bInAutoGenerateMipMaps, bool bInSRGB);`
- L66 _public prototype_ `explicit TexDescriptor(UTexture2D* TextureObj);`
- L67 _public prototype_ `explicit TexDescriptor(UTextureRenderTarget2D* RT);`
- L68 _public prototype_ `explicit TexDescriptor(const BufferDescriptor& BufferDesc);`
- L70 _public prototype_ `BufferDescriptor ToBufferDescriptor(uint32 NewWidth = 0, uint32 NewHeight = 0) const;`
- L71 _public prototype_ `size_t GetPitch() const;`
- L72 _public function_ `FORCEINLINE size_t Size() const`
- L73 _public prototype_ `HashType HashValue() const;`
- L74 _public prototype_ `HashType Format_HashValue() const;`

#### class `Tex`  
`class Tex : public FGCObject`  
_L87-208_
- inherits: `FGCObject`
- desc: This is a high level Texture class that wraps a 2D/1D Texture as well as a RenderTarget. Since we do a lot of texturing operations, we need to have some advanced requirements and that is why this class wraps a 2D Texture as well as a RenderTarget. It only has one state at a time though i.e. its either a UTexture or a RenderTarget. It can't be both. This works closely with the RCManager to efficiently manage the resources available to us within the system.
- L94 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L95 _private prototype_ `virtual FString GetReferencerName() const override;`
- L101 _protected member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — The optional Texture
- L102 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RT = nullptr;` — The render target
- L103 _protected member_ `TexDescriptor Desc;` — The descriptor for this Texture
- L104 _protected member_ `TextureFilter Filter = TextureFilter::TF_Bilinear;` — The filtering of the Texture/RT
- L105 _protected member_ `RenderMaterial_FXPtr CopyMat;` — Copy material
- L106 _protected member_ `CHashPtr HashObj;` — The hash for this Texture. This is totally optional
- L107 _protected member_ `bool bNoCache = false;` — Is this not supposed to be cached
- L109 _protected prototype_ `void InitTexture(const uint8* Pixels, size_t Length);`
- L110 _protected prototype_ `UTexture2D* CreateTexture(uint32 Width, uint32 Height, EPixelFormat PixelFormat, bool sRGB, UObject* Package);`
- L111 _protected prototype_ `UTexture2D* InitTextureDefault(int32 Width, int32 Height, EPixelFormat PixelFormat, const uint8* uncompressedData, size_t uncompressedDataSize, UObject* Package);`
- L113 _protected prototype_ `bool CopyImageToBuffer(EPixelFormat& PixelFormat, int32& Width, int32& Height, TArray<uint8>& inputBuffer, TArray<uint8>& OutputBuffer);`
- L115 _protected prototype_ `UTexture2D* InitTextureHDR(const TArray<uint8>& Buffer, UPackage* Package);`
- L118 _protected prototype_ `void InvalidateCached();`
- L119 _protected prototype_ `RenderMaterialPtr GetDefaultMaterial();`
- L120 _protected prototype_ `void UpdateRaw(const uint8* SrcPixels, size_t Length);`
- L121 _protected prototype_ `bool IsValidVirtualTexture();`
- L123 _public member_ `static EObjectFlags Flags;`
- L125 _public prototype_ `Tex(int32 Width, int32 Height, EPixelFormat PixelFormat);`
- L126 _public prototype_ `explicit Tex(const TexDescriptor& InDesc);`
- L127 _public prototype_ `explicit Tex(UTexture2D* Texture);`
- L128 _public prototype_ `explicit Tex(RawBufferPtr RawObj);`
- L129 _public prototype_ `explicit Tex(UTextureRenderTarget2D* RT);`
- L130 _public prototype_ `Tex();`
- L136 _public prototype_ `static void FreeGenericTexture(UTexture** Texture);`
- L137 _public prototype_ `static void FreeTexture(UTexture2D** Texture);`
- L138 _public prototype_ `static void FreeRT(UTextureRenderTarget2D** RT);`
- L140 _public prototype_ `void InitRT(bool ForceFloat = false);`
- L142 _public prototype_ `void Release();`
- L143 _public prototype_ `void ReleaseRT();`
- L144 _public prototype_ `void ReleaseTexture();`
- L145 _public prototype_ `void TransferTextureToRT(FRHICommandListImmediate& RHI, UTexture2D** PrevTexture, bool FreeAfterUse);`
- L146 _public prototype_ `void TransferVirtualTextureToRT(FRHICommandListImmediate& RHI, UTexture2D** TextureToTransfer, bool FreeAfterUse);`
- L147 _public prototype_ `bool LoadAsset(FSoftObjectPath& SoftPath, const DesiredImageProperties* Props = nullptr);`
- L148 _public prototype_ `bool LoadFile(const FString& Filename, const DesiredImageProperties* Props = nullptr);`
- L149 _public prototype_ `AsyncActionResultPtr LoadFlat();`
- L150 _public prototype_ `AsyncTiledBlobRef ToBlob(int32 XTiles, int32 YTiles, uint32 Width = 0, uint32 Height = 0, bool TransferToRT = false);` — There is a visual difference between having material transfer to RT or directly copy from Texture
- L151 _public prototype_ `AsyncTiledBlobRef ToSingleBlob(CHashPtr Hash, bool TransferToRT = false, bool ResolveOnRenderThread = false, bool NoCache = false);`
- L152 _public prototype_ `AsyncActionResultPtr LoadRaw(RawBufferPtr RawObj);`
- L153 _public prototype_ `void UpdateRaw(RawBufferPtr RawObj);`
- L155 _public prototype_ `void SetFilter(TextureFilter FilterValue);`
- L157 _public prototype_ `virtual void Bind(FName Name, std::shared_ptr<RenderMaterial> Material) const;`
- L158 _public prototype_ `void Clear();`
- L159 _public prototype_ `void Clear(FRHICommandList& RHI);`
- L160 _public prototype_ `void Clear(FRHICommandList& RHI, FLinearColor Color);`
- L162 _public prototype_ `void Free();`
- L163 _public prototype_ `size_t GetMemSize() const;`
- L164 _public prototype_ `RawBufferPtr Raw(const BufferDescriptor* SrcDesc = nullptr) const;` — Create a RawBuffer from the Texture, generate the descriptor if none is proveided
- L165 _public prototype_ `void GenerateMips();`
- L167 _public function_ `virtual bool IsArray()`
- L168 _public prototype_ `virtual FRHITexture* GetRHITexture() const;`
- L169 _public prototype_ `virtual UTexture* GetTexture() const;`
- L171 _public prototype_ `virtual bool IsNull() const;`
- L173 _public prototype_ `TArray<FColor> ReadPixels();`
- L186 _public prototype_ `static bool SaveImage(UTextureRenderTarget2D* RT, const FString& Path, const FString& Filename, bool bIsHDR = true);` — Saves render target to given path and filename (path, filename). @param	RenderTarget Input render target to save @param	Path		 receives the value of the path where the file needs to be saved @param	Filename	 filename with extension to save in particular format @param	bIsHDR		whether to save RTF_16 in HDR or EXR (discarded when trying to save PF_B8G8R8A8)
- L192 _public function_ `FORCEINLINE FLinearColor ClearColor() const`
- L193 _public function_ `FORCEINLINE FLinearColor& ClearColor()`
- L194 _public function_ `FORCEINLINE FIntPoint GetSize() const`
- L195 _public function_ `FORCEINLINE operator FRHITexture*() const`
- L197 _public function_ `FORCEINLINE operator UTexture*() const` — FORCEINLINE operator			FTextureRHIRef() const { return RHITextureRef(); }
- L198 _public function_ `FORCEINLINE FString GetName() const`
- L199 _public function_ `FORCEINLINE const TexDescriptor& GetDescriptor() const`
- L200 _public function_ `FORCEINLINE TextureFilter GetFilter() const`
- L201 _public function_ `FORCEINLINE uint32 GetWidth() const`
- L202 _public function_ `FORCEINLINE uint32 GetHeight() const`
- L203 _public function_ `FORCEINLINE bool IsRenderTarget() const`
- L204 _public function_ `FORCEINLINE UTexture2D* GetTexture2D() const`
- L205 _public function_ `FORCEINLINE UTextureRenderTarget2D* GetRenderTarget() const`
- L206 _public function_ `FORCEINLINE void SetHash(CHashPtr Hash)`
- L207 _public function_ `FORCEINLINE CHashPtr Hash() const`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L27 _typedef_ `typedef std::shared_ptr<Tex> TexPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TexArray.h` (Other)


#### class `TexArray`  
`class TexArray : public Tex`  
_L17-44_
- inherits: `Tex`
- L22 _protected member_ `TObjectPtr<UTextureRenderTarget2DArray> RTArray = nullptr;` — The render target array
- L23 _protected member_ `int32 XTiles = 0;`
- L24 _protected member_ `int32 YTiles = 0;`
- L25 _protected member_ `int32 Index = 0;`
- L26 _protected prototype_ `void InitRTArray(bool ForceFloat = false);`
- L29 _public prototype_ `TexArray();`
- L30 _public prototype_ `TexArray(Tex& TexObj, int32 XTilesTotal, int32 YTilesTotal);`
- L31 _public prototype_ `TexArray(const TexDescriptor& Desc, UTextureRenderTarget2DArray* rtArray);`
- L32 _public prototype_ `TexArray(const TexDescriptor& Desc, int32 XTilesTotal, int32 YTilesTotal);`
- L34 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L36 _public function_ `virtual bool IsArray() override`
- L37 _public prototype_ `virtual UTexture* GetTexture() const override;`
- L38 _public prototype_ `virtual bool IsNull() const override;`
- L43 _public function_ `FORCEINLINE UTextureRenderTarget2DArray* GetRenderTargetArray() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `typedef std::shared_ptr<TexArray> TexArrayPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TextureContent.h` (Other)


#### enum `TextureContent`  
`enum class TextureContent : uint8`  
_L10-65_
- reflection: `UENUM()`
- L12 _public enumerator_ `Asset`
- L13 _public enumerator_ `Diffuse`
- L14 _public enumerator_ `Specular`
- L15 _public enumerator_ `Gloss`
- L16 _public enumerator_ `AO`
- L17 _public enumerator_ `Normal`
- L18 _public enumerator_ `Displacement`
- L19 _public enumerator_ `Preview`
- L20 _public enumerator_ `Json`
- L21 _public enumerator_ `Cavity`
- L22 _public enumerator_ `Roughness`
- L23 _public enumerator_ `Metalness`
- L24 _public enumerator_ `Albedo`
- L25 _public enumerator_ `Opacity`
- L26 _public enumerator_ `Curvature`
- L27 _public enumerator_ `Mask`
- L30 _public enumerator_ `PaintMask = 100` — MASKS Components
- L31 _public enumerator_ `SolidMask`
- L32 _public enumerator_ `ImageMask`
- L33 _public enumerator_ `NoiseMask`
- L34 _public enumerator_ `PatternMask`
- L35 _public enumerator_ `NormalMask`
- L36 _public enumerator_ `CurvatureMask`
- L37 _public enumerator_ `PositionGradient`
- L40 _public enumerator_ `CircularModifier` — UV Modifiers
- L41 _public enumerator_ `TransformModifier`
- L44 _public enumerator_ `BrightnessMaskModifier = 200` — Value Modifiers
- L45 _public enumerator_ `ClampMaskModifier`
- L46 _public enumerator_ `InvertMaskModifier`
- L47 _public enumerator_ `NormalizeMaskModifier`
- L48 _public enumerator_ `GradientRemapMaskModifier`
- L49 _public enumerator_ `PosterizeMaskModifier`
- L50 _public enumerator_ `ScatterMaskModifier`
- L52 _public enumerator_ `CustomSource`
- L54 _public enumerator_ `None`
- L56 _public enumerator_ `MaterialIDMask`
- L57 _public enumerator_ `GroupMaskComponent`
- L58 _public enumerator_ `ProjectionModifier`
- L60 _public enumerator_ `SmartMaterial`
- L61 _public enumerator_ `MaterialID`
- L64 _public enumerator_ `Count` — THIS HAS TO BE THE LAST ENTRY. ADD MORE ABOVE THIS

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TextureHelper.h` (Other)


#### struct `TextureHelper`  
`struct TextureHelper`  
_L28-152_
- L30 _public member_ `static TiledBlobPtr GTransparent;` — Transparent RGBA texture
- L31 _public member_ `static TiledBlobPtr GBlack;` — Black RGBA texture
- L32 _public member_ `static TiledBlobPtr GWhite;` — White RGBA texture
- L33 _public member_ `static TiledBlobPtr GGray;` — Gray RGBA texture
- L34 _public member_ `static TiledBlobPtr GRed;` — Red RGBA texture
- L35 _public member_ `static TiledBlobPtr GGreen;` — Green RGBA texture
- L36 _public member_ `static TiledBlobPtr GBlue;` — Blue RGBA texture
- L37 _public member_ `static TiledBlobPtr GYellow;` — Yellow RGBA texture
- L38 _public member_ `static TiledBlobPtr GMagenta;` — Magenta RGBA texture
- L39 _public member_ `static TiledBlobPtr GDefaultNormal;` — Default Normal RGBA texture
- L40 _public member_ `static TiledBlobPtr GWhiteMask;` — Default white mask
- L41 _public member_ `static TiledBlobPtr GBlackMask;` — Default black mask
- L43 _public prototype_ `static cti::continuable<bool> InitSolidTexture(TiledBlobPtr* BlobObj, FLinearColor Color, FString Name, struct TexDescriptor Desc);`
- L44 _public prototype_ `static void InitStockTextures();`
- L45 _public prototype_ `static void FreeStockTextures();`
- L47 _public function_ `static FORCEINLINE TiledBlobPtr GetTransparent()`
- L48 _public function_ `static FORCEINLINE TiledBlobPtr GetBlack()`
- L49 _public function_ `static FORCEINLINE TiledBlobPtr GetWhite()`
- L50 _public function_ `static FORCEINLINE TiledBlobPtr GetGray()`
- L51 _public function_ `static FORCEINLINE TiledBlobPtr GetRed()`
- L52 _public function_ `static FORCEINLINE TiledBlobPtr GetGreen()`
- L53 _public function_ `static FORCEINLINE TiledBlobPtr GetBlue()`
- L54 _public function_ `static FORCEINLINE TiledBlobPtr GetYellow()`
- L55 _public function_ `static FORCEINLINE TiledBlobPtr GetMagenta()`
- L56 _public function_ `static FORCEINLINE TiledBlobPtr GetErrorBlob()`
- L57 _public function_ `static FORCEINLINE TiledBlobPtr GetDefaultNormal()`
- L58 _public function_ `static FORCEINLINE TiledBlobPtr GetWhiteMask()`
- L59 _public function_ `static FORCEINLINE TiledBlobPtr GetBlackMask()`
- L62 _public prototype_ `static uint32 GetChannelsFromPixelFormat(EPixelFormat InPixelFormat);`
- L63 _public prototype_ `static uint32 GetBppFromPixelFormat(EPixelFormat InPixelFormat);`
- L64 _public prototype_ `static ETextureRenderTargetFormat GetRenderTargetFormatFromPixelFormat(EPixelFormat InPixelFormat);`
- L65 _public prototype_ `static ETextureSourceFormat GetSourceFormat(ETG_TextureFormat TGTextureFormat);`
- L66 _public prototype_ `static bool GetBufferFormatAndChannelsFromTGTextureFormat(ETG_TextureFormat Format, BufferFormat& OutBufferFormat, uint32& OutBufferChannels);`
- L67 _public prototype_ `static EPixelFormat GetPixelFormatFromRenderTargetFormat(ETextureRenderTargetFormat RTFormat);`
- L68 _public prototype_ `static bool GetPixelFormatFromTextureSourceFormat(ETextureSourceFormat SourceFormat, EPixelFormat& OutPixelFormat, uint32& OutNumChannels);`
- L69 _public prototype_ `static ETextureSourceFormat GetTextureSourceFormat(BufferFormat Format, uint32 ItemsPerPoint);`
- L70 _public prototype_ `static ETG_TextureFormat GetTGTextureFormatFromChannelsAndFormat(uint32 ItemsPerPoint, BufferFormat Format);`
- L71 _public prototype_ `static uint32 GetNumChannelsFromTGTextureFormat(ETG_TextureFormat TextureFormat);`
- L72 _public prototype_ `static FString GetChannelsTextFromItemsPerPoint(const int32 InItemsPerPoint);`
- L73 _public prototype_ `static void ClearRT(UTextureRenderTarget2D* RenderTarget, FLinearColor Color = FLinearColor::Transparent);`
- L74 _public prototype_ `static void ClearRT(FRHICommandList& RHI, UTextureRenderTarget2D* RenderTarget, FLinearColor Color = FLinearColor::Transparent);`
- L76 _public prototype_ `static const char* TextureTypeToString(TextureType Type);`
- L77 _public prototype_ `static TextureType TextureStringToType(const FString& TypeString);`
- L78 _public prototype_ `static const char* TextureTypeToMegascansType(TextureType Type);`
- L80 _public prototype_ `static TextureType TextureContentToTextureType(TextureContent Content);`
- L81 _public prototype_ `static TextureContent TextureTypeToTextureContent(TextureType Type);`
- L82 _public prototype_ `static MaskType TextureContentToMaskType(TextureContent Content);`
- L83 _public prototype_ `static TextureContent MaskTypeToTextureContent(MaskType Type);`
- L84 _public prototype_ `static MaskModifierType TextureContentToMaskModifier(TextureContent Content);`
- L85 _public prototype_ `static TextureContent MaskModifierToTextureContent(MaskModifierType Type);`
- L87 _public prototype_ `static RawBufferPtr RawFromRT(UTextureRenderTarget2D* RenderTarget, const BufferDescriptor& Desc);`
- L88 _public prototype_ `static RawBufferPtr RawFromTexture(UTexture2D* Texture, const BufferDescriptor& Desc);`
- L89 _public prototype_ `static RawBufferPtr RawFromResource(const FTextureRHIRef& ResourceRHI, const BufferDescriptor& Desc);`
- L90 _public prototype_ `static BufferFormat FindOptimalSupportedFormat(BufferFormat SrcFormat);`
- L92 _public prototype_ `static void RawFromRT_Tiled(UTextureRenderTarget2D* RenderTarget, const BufferDescriptor& Desc, size_t TileSizeX, size_t TileSizeY, RawBufferPtrTiles& Tiles);`
- L93 _public prototype_ `static void RawFromTexture_Tiled(UTexture2D* Texture, const BufferDescriptor& Desc, size_t TileSizeX, size_t TileSizeY, RawBufferPtrTiles& Tiles);`
- L94 _public prototype_ `static void RawFromResource_Tiled(FTextureRHIRef ResourceRHI, const BufferDescriptor& Desc, size_t TileSizeX, size_t TileSizeY, RawBufferPtrTiles& Tiles);`
- L95 _public prototype_ `static void RawFromMem_Tiled(const uint8* SrcData, size_t SrcDataLength, const BufferDescriptor& SrcDesc, size_t TileSizeX, size_t TileSizeY, RawBufferPtrTiles& Tiles);`
- L96 _public prototype_ `static RawBufferPtr CombineRaw_Tiles(const RawBufferPtrTiles& Tiles, CHashPtr HashValue = nullptr, bool bIsTransient = false);`
- L98 _public prototype_ `static bool IsFloatRT(UTextureRenderTarget2D* RenderTarget);`
- L99 _public prototype_ `static FLinearColor GetPixelValueFromRaw(RawBufferPtr RawObj, int32 Width, int32 Height, int32 X, int32 Y);`
- L100 _public prototype_ `static AsyncBool ExportRaw(RawBufferPtr RawObj, const FString& CompletePath);`
- L101 _public prototype_ `static bool CanSupportTexture(UTexture* Tex);`
- L102 _public prototype_ `static bool CanSplitToTiles(int Width, int Height, int TilesX, int TilesY);`
- L103 _public prototype_ `static size_t RoundUpTo(size_t Size, size_t DesiredRounding);`
- L108 _public function_ `static FORCEINLINE FString CreateTileName(const FString& BaseName, int32 TileX, int32 TileY)`
- L114 _public function_ `template <class T> static FORCEINLINE bool IsPowerOf2(T Value)`
- L120 _public function_ `template <class T> static FORCEINLINE T FloorToPowerOf2(T Value)`
- L131 _public function_ `template <class T> static FORCEINLINE T CeilToPowerOf2(T Value)`
- L148 _public function_ `static FORCEINLINE uint32 CalcNumMipLevels(uint32 BaseSize)` — Calculate the total number of mip levels for a given base size. This is including the level 0 of said base size

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L23 _typedef_ `typedef std::shared_ptr<TiledBlob> TiledBlobPtr;`
- L25 _typedef_ `typedef cti::continuable<bool> AsyncBool;`
- L26 _typedef_ `typedef cti::continuable<FLinearColor> AsyncLinearColor;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TextureSet.h` (Other)


#### class `TextureSet`  
`class TextureSet`  
_L14-90_
- L17 _public member_ `static constexpr int GMaxTextures = (int)TextureType::Count;`
- L18 _public member_ `static const BufferDescriptor GDesc[GMaxTextures];` — The default descriptors for the textures
- L19 _public member_ `static constexpr int32 GDefaultTexSize = 256;` — Default texture size
- L22 _protected member_ `TMap<FName, TiledBlobRef> OwnedTexturesMap;` — The textures within this texture set that we own a reference of
- L25 _public member_ `int32 Width = 0;` — Width of this target in pixels
- L26 _public member_ `int32 Height = 0;` — Height of this target in pixels
- L28 _public member_ `TMap<FName,TiledBlobRef> TexturesMap;` — The textures within this texture set that we don't own a reference of (could be one of the owned textures)
- L29 _public member_ `BufferDescriptor Desc[GMaxTextures];` — Descriptors for all the blobs
- L31 _public prototype_ `virtual void InitTex(int32 InTypeIndex);`
- L32 _public prototype_ `virtual void InitTexFromFile(int32 InTypeIndex, const FString& FileName, int32 NumTilesX, int32 NumTilesY);`
- L33 _public prototype_ `void InitBufferDescriptor(int32 ti);`
- L34 _public prototype_ `TSet<FName> GetTextureList() const;`
- L37 _public prototype_ `TextureSet(int32 InWidth, int32 InHeight);`
- L40 _public prototype_ `virtual ~TextureSet();`
- L42 _public prototype_ `virtual void Init();`
- L43 _public prototype_ `virtual void Free();`
- L44 _public prototype_ `virtual void FreeAt(FName TextureName);`
- L45 _public prototype_ `void FreeAt(TextureType type);`
- L47 _public prototype_ `virtual void ChangeFormat(TextureType InType, EPixelFormat InPixelFormat, bool bRecreate);`
- L48 _public prototype_ `virtual void ChangeResolution(int32 InWidth, int32 InHeight, bool bRecreate);`
- L49 _public prototype_ `virtual void Invalidate(FName TextureName, bool bRecreate);`
- L50 _public prototype_ `virtual void Invalidate(TextureType InType, bool bRecreate);`
- L52 _public prototype_ `virtual void SetTexture(FName TextureName, TiledBlobRef Texture);`
- L53 _public prototype_ `virtual bool RenameTexture(FName TextureName, FName NewName);`
- L54 _public prototype_ `virtual void SetTexture(int32 TypeIndex, TiledBlobRef texture);`
- L56 _public prototype_ `virtual void Update(MixUpdateCyclePtr cycle, int32 targetId);`
- L59 _public function_ `FORCEINLINE bool ContainsTexture(FName TextureName)`
- L60 _public function_ `FORCEINLINE TiledBlobRef GetTexture(FName TextureName) const`
- L61 _public function_ `FORCEINLINE TiledBlobRef GetOwnedTexture(FName TextureName) const`
- L62 _public function_ `FORCEINLINE TiledBlobRef GetTexture(TextureType type) const`
- L63 _public function_ `FORCEINLINE TiledBlobRef GetTexture(int32 TypeIndex) const`
- L64 _public function_ `FORCEINLINE TiledBlobRef GetOwnedTexture(int32 TypeIndex) const`
- L66 _public function_ `FORCEINLINE TiledBlobRef CheckAndGetTexture(FName TextureName) const` — TextureSet&						operator = (const TextureSet& rhs);
- L75 _public function_ `FORCEINLINE TiledBlobRef GetDiffuse() const` — TODO: Need to remove these getters for PBR specific textures There are multiple references of these getters in the code. To avoid major refactoring. For now just passing the default tiled reference.
- L76 _public function_ `FORCEINLINE TiledBlobRef GetSpecular() const`
- L77 _public function_ `FORCEINLINE TiledBlobRef GetAlbedo() const`
- L78 _public function_ `FORCEINLINE TiledBlobRef GetMetalness() const`
- L79 _public function_ `FORCEINLINE TiledBlobRef GetNormal() const`
- L80 _public function_ `FORCEINLINE TiledBlobRef GetDisplacement() const`
- L81 _public function_ `FORCEINLINE TiledBlobRef GetOpacity() const`
- L82 _public function_ `FORCEINLINE TiledBlobRef GetRoughness() const`
- L83 _public function_ `FORCEINLINE TiledBlobRef GetAO() const`
- L85 _public function_ `FORCEINLINE bool IsValid(FName TextureName) const`
- L88 _public function_ `FORCEINLINE int32 GetWidth() const`
- L89 _public function_ `FORCEINLINE int32 GetHeight() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L12 _typedef_ `typedef std::shared_ptr<MixUpdateCycle> MixUpdateCyclePtr;`
- L92 _typedef_ `typedef std::unique_ptr<TextureSet> TextureSetPtr;`
- L93 _typedef_ `typedef std::vector<TextureSet> TextureSetVec;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/2D/TextureType.h` (Other)


#### enum `TextureType`  
`enum class TextureType`  
_L12-30_
- reflection: `UENUM()`
- L14 _public enumerator_ `Diffuse`
- L15 _public enumerator_ `Specular`
- L16 _public enumerator_ `Albedo` — We always use the diffuse texture for albedo (see the duplicate enum below)
- L17 _public enumerator_ `Metalness`
- L18 _public enumerator_ `Normal`
- L19 _public enumerator_ `Displacement`
- L20 _public enumerator_ `Opacity`
- L21 _public enumerator_ `Roughness`
- L22 _public enumerator_ `AO`
- L23 _public enumerator_ `Curvature`
- L24 _public enumerator_ `Preview` — We use this for thumbnails as well
- L27 _public enumerator_ `Count` — Always has to be the last
- L29 _public enumerator_ `Unknown = -1`

#### enum `LayerBlendMode`  
`enum class LayerBlendMode : uint8`  
_L34-47_
- reflection: `UENUM()`
- L36 _public enumerator_ `Normal`
- L37 _public enumerator_ `Add`
- L38 _public enumerator_ `Subtract`
- L39 _public enumerator_ `Multiply`
- L40 _public enumerator_ `Divide`
- L41 _public enumerator_ `Difference`
- L42 _public enumerator_ `Max`
- L43 _public enumerator_ `Min`
- L44 _public enumerator_ `Step`
- L45 _public enumerator_ `Overlay`
- L46 _public enumerator_ `Distort`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/CoreMesh.h` (Other)


#### struct `CoreMeshVertex`  
`struct CoreMeshVertex`  
_L16-23_
- L18 _public member_ `FVector3f position;` — The vertex position
- L19 _public member_ `FVector2f uv;` — The texture coordinates
- L20 _public member_ `FVector3f normal;` — Per-vertex normal
- L21 _public member_ `FVector4f tangent;` — Tangent with W
- L22 _public member_ `FVector4f color;` — Per vertex colour

#### struct `CoreMesh`  
`struct CoreMesh`  
_L25-39_
- L27 _public member_ `TArray<FVector> vertices;`
- L28 _public member_ `TArray<FVector> normals;`
- L29 _public member_ `TArray<FVector2D> uvs;`
- L30 _public member_ `TArray<Tangent> tangents;`
- L31 _public member_ `TArray<FLinearColor> vertexColors;`
- L35 _public member_ `TArray<int32> triangles;` — The triangles for this mesh
- L36 _public member_ `FBox bounds;` — The bounds for this mesh
- L37 _public member_ `FString name;` — The name of the mesh
- L38 _public member_ `int32 materialIndex;` — Material index that is used for UDIM/multi-material meshes

#### class `CoreMeshVertex_Decl`  
`class CoreMeshVertex_Decl : public FRenderResource`  
_L42-54_
- inherits: `FRenderResource`
- L44 _private member_ `FVertexDeclarationRHIRef _rhiDecl;` — Declaration RHI
- L47 _public prototype_ `virtual ~CoreMeshVertex_Decl() override = default;`
- L49 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L50 _public prototype_ `virtual void ReleaseRHI() override;`
- L53 _public function_ `FORCEINLINE FVertexDeclarationRHIRef RHI_Decl() const`

#### Free symbols / members of external scopes

- L56 _externvar_ `extern TGlobalResource<CoreMeshVertex_Decl> g_coreMeshVertexDecl;`
- L58 _typedef_ `typedef std::shared_ptr<CoreMesh> CoreMeshPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MaterialInfo.h` (Other)


#### struct `MaterialInfo`  
`struct MaterialInfo`  
_L9-13_
- L11 _public member_ `FString name;`
- L12 _public member_ `int32 id;`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef std::shared_ptr<MaterialInfo> MaterialInfoPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshDetails/MeshDetails.h` (Other)


#### class `MeshDetails`  
`class MeshDetails`  
_L20-38_
- L23 _protected member_ `MeshInfo* Mesh;` — The mesh that is containing this detail
- L24 _protected member_ `bool bIsFinalised = false;` — Whether this detail has been finalised or not
- L25 _protected member_ `CHashPtr HashValue;` — What is the hash of this detail
- L27 _protected prototype_ `virtual void CalculateTri(size_t ti);`
- L28 _protected prototype_ `virtual void CalculateVertex(size_t vi);`
- L31 _public prototype_ `MeshDetails(MeshInfo* mesh);`
- L32 _public prototype_ `virtual ~MeshDetails();`
- L34 _public prototype_ `virtual MeshDetailsPAsync Calculate();`
- L35 _public prototype_ `virtual MeshDetailsPAsync Finalise();`
- L36 _public prototype_ `virtual void RenderDebug();`
- L37 _public prototype_ `virtual void Release();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _typedef_ `typedef cti::continuable<MeshDetails*> MeshDetailsPAsync;`
- L17 _typedef_ `typedef std::shared_ptr<RawBuffer> RawBufferPtr;`
- L40 _typedef_ `typedef std::shared_ptr<MeshDetails> MeshDetailsPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshDetails/MeshDetails_Edges.h` (Other)


#### class `MeshDetails_Edges`  
`class MeshDetails_Edges : public MeshDetails`  
_L12-55_
- inherits: `MeshDetails`
- L15 _public member_ `static const int s_maxCongruent = 8;`
- L31 _protected typedef_ `typedef std::unordered_map<long, Edge*> EdgeLUT;`
- L32 _protected typedef_ `typedef std::vector<std::list<Edge*> > VecListsEdge;`
- L33 _protected typedef_ `typedef std::vector<std::list<int32> > VecListsTri;`
- L34 _protected typedef_ `typedef std::vector<int32> IntVec;`
- L36 _protected member_ `EdgeLUT _edges;` — All the edges within the mesh, one for each vertex
- L37 _protected member_ `VecListsEdge _vertexEdges;` — All the edges for a vertex
- L38 _protected member_ `VecListsEdge _disconnected;` — Edges that are disconnected
- L39 _protected member_ `VecListsTri _vertexTriangles;` — The triangles that share a particular vertex
- L40 _protected member_ `IntVec _numCongruent;` — How many congruent vertices
- L41 _protected member_ `int32* _congruent = nullptr;` — Adjacency/Congruency information for disconnected vertices 2D array
- L43 _protected member_ `std::list<int32> _adjTriangles;` — Indices of adjacent triangles
- L44 _protected member_ `IntVec _adjStart;` — Adjacency start index into the _adjTriangles array (for each triangle)
- L45 _protected member_ `IntVec _adjCount;` — Number of adjacent triangles in the _adjTriangles array (for each triangle)
- L47 _protected prototype_ `virtual void CalculateTri(size_t ti) override;`
- L50 _public prototype_ `MeshDetails_Edges(MeshInfo* mesh);`
- L51 _public prototype_ `virtual ~MeshDetails_Edges();`
- L53 _public prototype_ `virtual MeshDetailsPAsync Calculate() override;`
- L54 _public prototype_ `virtual void Release() override;`

#### struct `MeshDetails_Edges::Edge`  
`struct Edge`  
_L17-27_
- L19 _public member_ `int32 i_v0;` — Index of the first vertex
- L20 _public member_ `int32 i_v1;` — Index of the second vertex
- L21 _public member_ `int32 ti;` — Triangle index
- L23 _public member_ `int32 triangles[MeshDetails_Edges::s_maxCongruent];` — Triangles that share this edge
- L24 _public member_ `int32 numCongruent = 0;` — Number of valid values in congruent
- L26 _public prototype_ `Edge(int32 i_v0, int32 i_v1, int32 ti);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshDetails/MeshDetails_Spatial.h` (Other)


#### class `MeshDetails_Spatial`  
`class MeshDetails_Spatial : MeshDetails`  
_L15-134_
- inherits: `MeshDetails`
- L105 _protected member_ `MeshDetails_Spatial::Node* _root = nullptr;` — The root node of this Octree
- L108 _protected member_ `std::vector<MeshDetails_Spatial::Node*> _leafs;` — The leaf nodes of this Octree for easy access
- L110 _protected member_ `int _maxLevel = 0;` — The current max level of the tree
- L112 _protected member_ `std::array<Vector3, 8> _diagNormals;` — Normals for the diagonals of Level-0 and Level-1 of the octree. These allow us to
- L121 _protected member_ `int _nodeId = 0;` — The current node ID that we're using
- L122 _protected member_ `std::vector<ONode*> _allNodes;` — ALL the nodes in the Octree
- L123 _protected member_ `std::vector<int> _tris;` — The triangles
- L124 _protected member_ `int _triCount = 0;` — How many triangles do we have
- L126 _protected prototype_ `virtual void CalculateTri(size_t ti) override;`
- L129 _public prototype_ `MeshDetails_Spatial(MeshInfo* mesh);`
- L130 _public prototype_ `virtual ~MeshDetails_Spatial();`
- L132 _public prototype_ `virtual MeshDetailsPAsync Calculate() override;`
- L133 _public prototype_ `virtual void Release() override;`

#### struct `MeshDetails_Spatial::ONode`  
`struct ONode`  
_L18-36_
- L20 _public member_ `FBox FBox;`
- L21 _public member_ `int Level;`
- L22 _public member_ `int ChildIndex;`
- L23 _public member_ `int LevelIndex;`
- L24 _public member_ `int ParentNodeId;`
- L25 _public member_ `int NodeId;`
- L26 _public member_ `int TriStart;`
- L27 _public member_ `int TriCount;`
- L28 _public member_ `int HasChildren;`
- L32 _public member_ `static const int s_maxChildren = 8;` — We need to do stupid shit like this to avoid having int[] Children in here because it's non-blittable for the compute shader and throws an error.
- L33 _public member_ `int Children[s_maxChildren];` — The children for this node
- L35 _public prototype_ `ONode(int parentNodeId);`

#### class `MeshDetails_Spatial::Node`  
`class Node`  
_L39-99_
- L42 _private member_ `static const int s_maxTriangles = 256;`
- L43 _private member_ `static const int s_maxChildren = 8;`
- L44 _private member_ `static const int s_maxLevel = 9;`
- L46 _private member_ `FCriticalSection _mutex;` — Mutex for parallel compute
- L49 _private member_ `FBox _bounds;` — The bounds for this node
- L52 _private member_ `std::vector<int>* _triangles;` — The triangles in this node. These are indexed into MeshDetails_Tri
- L53 _private member_ `MeshDetails_Spatial* _details;`
- L56 _private member_ `Node* _parent = nullptr;` — The parent of this Octree
- L58 _private member_ `int _level = 0;` — What level is this node on
- L59 _private member_ `int _childIndex = 0;` — Which child is it (Check out Gemoetry.Util.BoundsCorners in GeometryUtil.cs)
- L60 _private member_ `int _levelIndex = 0;` — What is the index of this node at the depth level that it's at
- L61 _private member_ `int _nodeId = 0;` — Unique node id
- L64 _private member_ `std::array<Node*, 8> _children;` — The children of this octree
- L69 _public function_ `bool HasChildren() const`
- L70 _public function_ `const std::vector<int>* Triangles() const`
- L71 _public function_ `const FBox& Bounds() const`
- L72 _public function_ `const std::array<Node*, 8>& Children() const`
- L73 _public function_ `const Node* Parent() const`
- L74 _public function_ `int NodeId() const`
- L76 _public prototype_ `void RenderDebug() const;`
- L77 _public prototype_ `Node* CreateChild(int ci, int li, int ni);`
- L78 _public prototype_ `int FindTriangle(MeshInfo& mesh, const Vector3& pos, Vector2& bcCoord);`
- L79 _public prototype_ `bool Divide(MeshDetails_Tri* d_tri, Node* triNodes);`
- L81 _public prototype_ `static bool CheckIntersection(const FBox& nodeBounds, FRay ray, float& distance, float length = -1, FBox* bounds = nullptr);`
- L82 _public prototype_ `std::list<Node*> GetIntersectingLeafNodes(std::list<Node> nodes, FRay ray, float* distance, float length = -1, FBox* bounds = nullptr, std::list<Node*>* ignoreLeafs = nullptr);`
- L91 _public function_ `Node(MeshDetails_Spatial* details, Node* parent, const FBox& bounds, int nodeId, std::vector<int>* triangles = nullptr)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshDetails/MeshDetails_SpatialUV.h` (Other)


#### class `MeshDetails_SpatialUV`  
`class MeshDetails_SpatialUV : public MeshDetails`  
_L11-22_
- inherits: `MeshDetails`
- L14 _protected prototype_ `virtual void CalculateTri(size_t ti) override;`
- L17 _public prototype_ `MeshDetails_SpatialUV(MeshInfo* mesh);`
- L18 _public prototype_ `virtual ~MeshDetails_SpatialUV();`
- L20 _public prototype_ `virtual MeshDetailsPAsync Calculate() override;`
- L21 _public prototype_ `virtual void Release() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshDetails/MeshDetails_Tri.h` (Other)


#### class `MeshDetails_Tri`  
`class MeshDetails_Tri : public MeshDetails`  
_L9-54_
- inherits: `MeshDetails`
- L30 _protected member_ `static const size_t s_maxBatch;`
- L31 _protected member_ `Triangle* _triangles = nullptr;` — The triangles that we have
- L32 _protected member_ `size_t _numTriangles = 0;` — How many triangles do we have
- L33 _protected member_ `RawBufferPtr _raw;` — The triangle buffer is indexed into this RawBuffer
- L35 _protected prototype_ `virtual void CalculateTri(size_t ti) override;`
- L38 _public prototype_ `MeshDetails_Tri(MeshInfo* mesh);`
- L39 _public prototype_ `virtual ~MeshDetails_Tri();`
- L41 _public prototype_ `virtual MeshDetailsPAsync Calculate() override;`
- L43 _public prototype_ `int32* GetIndices(size_t ti) const;`
- L44 _public prototype_ `std::array<Vector3, 3> GetVertices(size_t ti) const;`
- L45 _public prototype_ `std::array<Vector2, 3> GetUVs(size_t ti) const;`
- L46 _public prototype_ `std::array<Vector3, 3> GetNormals(size_t ti) const;`
- L47 _public prototype_ `std::array<Tangent, 3> GetTangents(size_t ti) const;`
- L52 _public function_ `FORCEINLINE Triangle* Triangles() const`
- L53 _public function_ `FORCEINLINE size_t NumTriangles() const`

#### struct `MeshDetails_Tri::Triangle`  
`struct Triangle`  
_L12-27_
- L14 _public member_ `FBox bounds;`
- L15 _public member_ `FBox uvBounds;`
- L16 _public member_ `Vector3 normal;`
- L17 _public member_ `Vector3 tangent;`
- L18 _public member_ `Vector3 biTangent;`
- L19 _public member_ `float distance;`
- L20 _public member_ `Vector3 centre;`
- L22 _public member_ `int32 indices[3];`
- L24 _public prototype_ `Triangle(int32 i0, int32 i1, int32 i2);`
- L25 _public prototype_ `bool HasIndex(int32 i);`
- L26 _public prototype_ `std::array<int32, 2> GetOtherVertices(int32 vi) const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/MeshInfo.h` (Other)


#### class `MeshInfo`  
`class MeshInfo`  
_L22-72_
- L25 _protected typedef_ `typedef std::unordered_map<const char*, MeshDetailsPtr> MeshDetailsPtrLookup;`
- L27 _protected member_ `CoreMeshPtr _cmesh;` — The core mesh data structure that should've been loaded by now
- L28 _protected member_ `CHashPtr _hash;` — The hash for the mesh
- L29 _protected member_ `mutable FCriticalSection _detailsMutex;` — Mutex for details
- L30 _protected member_ `MeshDetailsPtrLookup _details;` — Details lookup
- L33 _public prototype_ `MeshInfo(CoreMeshPtr cmesh);`
- L34 _public prototype_ `~MeshInfo();`
- L36 _public prototype_ `size_t NumVertices() const;`
- L37 _public prototype_ `size_t NumTriangles() const;`
- L38 _public prototype_ `std::array<Vector3, 3> Vertices(int32 i0, int32 i1, int32 i2) const;`
- L39 _public prototype_ `int32 GetMaterialIndex();`
- L40 _public prototype_ `void InitBounds(FVector min, FVector max);`
- L41 _public prototype_ `void UpdateBounds(const FVector& vert);`
- L44 _public prototype_ `MeshDetails_Tri* d_Tri();`
- L47 _public function_ `template <typename T_Details> T_Details* GetAttribute(const char* name, bool create = true)`
- L70 _public function_ `FORCEINLINE CoreMeshPtr CMesh() const`
- L71 _public function_ `FORCEINLINE CHashPtr Hash() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `typedef std::shared_ptr<CoreMesh> CoreMeshPtr;`
- L18 _typedef_ `typedef std::shared_ptr<MeshDetails> MeshDetailsPtr;`
- L74 _typedef_ `typedef std::shared_ptr<MeshInfo> MeshInfoPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/ProceduralMeshActor.h` (Other)


#### class `AProceduralMeshActor`  
`class AProceduralMeshActor : public AActor`  
_L28-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L32 _private member_ `TArray<TArray<FVector>> _debugPoints;`
- L33 _private member_ `bool _isDebug = false;`
- L34 _private member_ `FString _meshName = FString("");`
- L36 _private prototype_ `void BlitInternal(UMaterialInterface* mat);`
- L40 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts or when spawned
- L42 _protected prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L46 _protected member_ `TObjectPtr<UProceduralMeshComponent> _meshObj;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hierarchy")`
- L49 _protected member_ `TObjectPtr<USceneCaptureComponent2D> _sceneCaptureComp;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hierarchy")`
- L52 _public prototype_ `AProceduralMeshActor();` — Sets default values for this actor's properties
- L53 _public prototype_ `~AProceduralMeshActor();`
- L55 _public prototype_ `void InitSceneCaptureComponent();`
- L57 _public prototype_ `void InitMeshObj();`
- L59 _public prototype_ `void SetMeshData(CoreMeshPtr mesh);`
- L60 _public prototype_ `void DrawDebugLines(TArray<FVector>& positionArray, FVector length);`
- L61 _public prototype_ `void SetMaterial(UMaterialInterface* mat);`
- L62 _public prototype_ `UMaterialInterface* GetMaterial();`
- L64 _public prototype_ `void BlitTo(UTextureRenderTarget2D* rt, UMaterialInterface* mat);`
- L65 _public prototype_ `virtual void BeginDestroy();`
- L68 _public prototype_ `void ToggleDebug(int32 debugType);` — `UFUNCTION(BlueprintCallable, Category = "Debug")`
- L71 _public function_ `const FString & GetMeshName()` — `UFUNCTION(BlueprintCallable,Category = "Info")`
- L74 _public function_ `void SetMeshName(const FString& name)` — `UFUNCTION(BlueprintCallable, Category = "Info")`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L26 _typedef_ `typedef std::shared_ptr<Tex> TexPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/RenderMesh.h` (Other)


#### enum `MeshType`  
`enum class MeshType : uint8`  
_L17-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `Plane UMETA(DisplayName = "Plane")`
- L20 _public enumerator_ `LibraryAsset UMETA(DisplayName = "Library Asset")`
- L21 _public enumerator_ `ShaderBall UMETA(DisplayName = "Shader Ball")`
- L22 _public enumerator_ `CustomMesh UMETA(DisplayName = "Custom 3D Mesh")`
- L23 _public enumerator_ `Editor UMETA(DisplayName = "Editor")`

#### enum `MeshSplitType`  
`enum class MeshSplitType: uint8`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `Material = 0`
- L30 _public enumerator_ `UDIM = 1`
- L31 _public enumerator_ `Single = 2`

#### enum `BoundsType`  
`enum class BoundsType : uint8`  
_L35-40_
- reflection: `UENUM()`
- L37 _public enumerator_ `Target UMETA(DisplayName = "Align to texture sets individually")`
- L38 _public enumerator_ `CombinedTarget UMETA(DisplayName = "Align to texture sets combined")`
- L39 _public enumerator_ `Full UMETA(DisplayName = "Align to model")`

#### enum `WorldTextures`  
`enum WorldTextures : int`  
_L43-50_
- reflection: `UENUM()`
- L45 _public enumerator_ `Normals UMETA(DisplayName = "WorldNormals")`
- L46 _public enumerator_ `Tangents UMETA(DisplayName = "WorldTangents")`
- L47 _public enumerator_ `Position UMETA(DisplayName = "WorldPosition")`
- L48 _public enumerator_ `UVMask UMETA(DisplayName = "WorldUVMask")`
- L49 _public enumerator_ `WorldTextureCount UMETA(DisplayName = "Total World Textures")`

#### struct `MeshLoadInfo`  
`struct MeshLoadInfo`  
_L65-74_
- L67 _public member_ `FString filename;`
- L68 _public member_ `FVector scale = FVector::OneVector;`
- L69 _public member_ `MeshSplitType meshSplitType = MeshSplitType::Single;`
- L70 _public member_ `MeshType meshType = MeshType::Plane;`
- L71 _public member_ `FVector2D dimension = FVector2D::UnitVector;`
- L72 _public member_ `int32 tesselation = 32;`
- L73 _public member_ `UMixInterface* mix = nullptr;`

#### class `RenderMesh`  
`class RenderMesh`  
_L80-189_
- L84 _protected member_ `static const int s_maxTex = 512;`
- L86 _protected member_ `bool _isPlane = false;`
- L87 _protected member_ `TArray<MeshInfoPtr> _meshes;` — All the sub-meshens within this mesh
- L88 _protected member_ `TArray<MaterialInfoPtr> _originalMaterials;` — Original Mesh materials.
- L89 _protected member_ `TArray<MaterialInfoPtr> _currentMaterials;` — Materials can be generated for mesh materials or based on UDIM data.
- L90 _protected member_ `TArray<AActor*> _meshActors;` — All the actors this mesh spawned
- L91 _protected member_ `FBox _originalBounds;` — These are in cm units.
- L95 _protected member_ `FBox _viewBounds;` — What are the original bounds (as loaded) for the mesh this can be something other than OneVector in case of Megascans Assets (e.g. OBJ loading in cms, where-as JSON size suggests otherwise)
- L98 _protected member_ `FVector _originalScale = FVector::OneVector;` — What is the default scale (transform) of the mesh (as loaded) (_defaultMeshSize in Unity version)
- L99 _protected member_ `FVector _viewScale = FVector::OneVector;` — Current mesh scale (e.g changed via size UI) (meshScaleToUse in Unity version)
- L101 _protected member_ `UMaterialInterface* _currentMat;` — What is the currently active material. Mesh can only have UMaterial applied on it
- L103 _protected member_ `RenderMesh* _parentMesh = nullptr;` — What is the parent mesh of this mesh
- L105 _protected member_ `MeshSplitType _meshSplitType = MeshSplitType::Material;` — How is the mesh being split (by submeshes, UDIMs or materials etc.)
- L106 _protected member_ `mutable CHashPtr _hash;` — What is the hash of this mesh. Mutable because
- L109 _protected member_ `TiledBlobPtr _worldMaps[WorldTextures::WorldTextureCount];`
- L110 _protected member_ `TiledBlobPtr _worldMapsSingleBlob[WorldTextures::WorldTextureCount];`
- L112 _protected prototype_ `void AddMaterialInfo(int32 id, FString& matName);`
- L113 _protected prototype_ `virtual void SpawnActors(UWorld* world);`
- L114 _protected prototype_ `void UpdateMeshTransforms();`
- L115 _protected prototype_ `void UpdateBounds();`
- L117 _protected prototype_ `virtual void LoadInternal() = 0;`
- L119 _public prototype_ `RenderMesh() = default;`
- L120 _public prototype_ `RenderMesh(const MeshLoadInfo loadInfo);`
- L121 _public prototype_ `RenderMesh(RenderMesh* parent, TArray<MeshInfoPtr> mesh, MaterialInfoPtr matInfo);`
- L123 _public prototype_ `virtual ~RenderMesh();`
- L125 _public prototype_ `virtual void PrepareForRendering(UWorld* world,FVector scale);`
- L127 _public prototype_ `void DrawBounds(UWorld* world);`
- L128 _public prototype_ `virtual void SetMaterial(UMaterialInterface* material);`
- L129 _public prototype_ `virtual AsyncActionResultPtr Load() = 0;`
- L130 _public prototype_ `FString GetMaterialName();`
- L132 _public prototype_ `virtual CHashPtr Hash() const;`
- L133 _public prototype_ `virtual FMatrix LocalToWorldMatrix() const;`
- L134 _public prototype_ `virtual void RemoveActors();`
- L135 _public prototype_ `virtual void Render_Now(FRHICommandList& rhi, int32 targetId) const;`
- L136 _public prototype_ `virtual void Init_PSO(FGraphicsPipelineStateInitializer& pso) const;`
- L138 _public prototype_ `virtual TiledBlobPtr WorldPosTexture(MixUpdateCyclePtr cycle, int32 targetId, bool singleBLob = false);`
- L139 _public prototype_ `virtual TiledBlobPtr WorldNormalsTexture(MixUpdateCyclePtr cycle, int32 targetId, bool singleBLob = false);`
- L140 _public prototype_ `virtual TiledBlobPtr WorldTangentsTexture(MixUpdateCyclePtr cycle, int32 targetId, bool singleBLob = false);`
- L141 _public prototype_ `virtual TiledBlobPtr WorldUVMaskTexture(MixUpdateCyclePtr cycle, int32 targetId, bool singleBLob = false);`
- L143 _public prototype_ `virtual FString Name() const;`
- L144 _public prototype_ `virtual void Clear();`
- L146 _public function_ `bool ContainsWorldTexture(WorldTextures texture)`
- L147 _public function_ `bool ContainsWorldNormals()`
- L148 _public function_ `bool ContainsWorldTangents()`
- L149 _public function_ `bool ContainsWorldPosition()`
- L150 _public function_ `bool ContainsWorldUVMask()`
- L152 _public function_ `TiledBlobPtr WorldTexture(WorldTextures texture)`
- L153 _public function_ `TiledBlobPtr WorldNormals()`
- L154 _public function_ `TiledBlobPtr WorldTangents()`
- L155 _public function_ `TiledBlobPtr WorldPosition()`
- L156 _public function_ `TiledBlobPtr WorldUVMask()`
- L158 _public function_ `TiledBlobPtr WorldTextureSingleBlob(WorldTextures texture)`
- L159 _public function_ `TiledBlobPtr WorldNormalsSingleBlob()`
- L160 _public function_ `TiledBlobPtr WorldTangentsSingleBlob()`
- L161 _public function_ `TiledBlobPtr WorldPositionSingleBlob()`
- L162 _public function_ `TiledBlobPtr WorldUVMaskSingleBlob()`
- L167 _public function_ `FORCEINLINE const FVector& ViewScale()`
- L168 _public function_ `FORCEINLINE const FVector& OriginalScale()`
- L169 _public function_ `FORCEINLINE const FVector InvOriginalBoundsDiameter()`
- L170 _public function_ `FORCEINLINE const FBox& OriginalBounds()`
- L171 _public function_ `FORCEINLINE void SetViewScale(FVector scale)`
- L172 _public function_ `FORCEINLINE const MeshSplitType GetMeshSplitType()`
- L174 _public function_ `FORCEINLINE TArray<MeshInfoPtr>& Meshes()`
- L175 _public function_ `FORCEINLINE const TArray<MeshInfoPtr>& Meshes() const`
- L177 _public function_ `FORCEINLINE const TArray<MaterialInfoPtr>& OriginalMaterials() const` — Original mesh materials.
- L179 _public function_ `FORCEINLINE const TArray<MaterialInfoPtr>& CurrentMaterials() const` — Materials can be generated for mesh materials or based on UDIM data.
- L181 _public function_ `FORCEINLINE TArray<AActor*>& Actors()`
- L182 _public function_ `FORCEINLINE const TArray<AActor*>& Actors() const`
- L183 _public function_ `FORCEINLINE bool IsPlane()`
- L188 _public prototype_ `static RenderMeshPtr Create(const MeshLoadInfo _loadInfo);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L54 _typedef_ `typedef std::shared_ptr<Tex> TexPtr;`
- L57 _typedef_ `typedef std::shared_ptr<MeshInfo> MeshInfoPtr;`
- L60 _typedef_ `typedef std::shared_ptr<MaterialInfo> MaterialInfoPtr;`
- L63 _typedef_ `typedef std::shared_ptr<MixUpdateCycle> MixUpdateCyclePtr;`
- L76 _typedef_ `typedef std::shared_ptr<RenderMesh> RenderMeshPtr;`
- L79 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogMesh, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/RenderMesh_Editor.h` (Other)


#### class `RenderMesh_Editor`  
`class RenderMesh_Editor: public RenderMesh`  
_L10-29_
- inherits: `RenderMesh`
- L14 _protected member_ `TArray<UStaticMeshComponent*> MeshComponents;`
- L15 _protected member_ `UWorld* World = nullptr;`
- L16 _protected prototype_ `virtual void LoadInternal() override;`
- L17 _protected prototype_ `void LoadSingleMeshComponent(const UStaticMeshComponent& mesh);`
- L20 _public prototype_ `RenderMesh_Editor();`
- L21 _public prototype_ `RenderMesh_Editor(RenderMesh* parent, TArray<MeshInfoPtr> meshes, MaterialInfoPtr matInfo);`
- L22 _public prototype_ `RenderMesh_Editor(UStaticMeshComponent* staticMeshComponent, UWorld* world);`
- L24 _public function_ `FORCEINLINE TArray<UStaticMeshComponent*> GetMeshComponents()`
- L25 _public prototype_ `virtual AsyncActionResultPtr Load() override;`
- L26 _public function_ `virtual FMatrix LocalToWorldMatrix() const override`
- L27 _public prototype_ `virtual void PrepareForRendering(UWorld* world, FVector scale) override;`
- L28 _public prototype_ `virtual void SetMaterial(UMaterialInterface* material) override;`

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef std::shared_ptr<RenderMesh_Editor> RenderMesh_EditorPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/RenderMesh_EditorScene.h` (Other)


#### class `RenderMesh_EditorScene`  
`class RenderMesh_EditorScene: public RenderMesh_Editor`  
_L9-23_
- inherits: `RenderMesh_Editor`
- L12 _private member_ `AActor* MeshActor;` — Actor that this rendermesh is associated to
- L15 _public prototype_ `RenderMesh_EditorScene();`
- L16 _public prototype_ `RenderMesh_EditorScene(AActor* actor);`
- L17 _public prototype_ `RenderMesh_EditorScene(RenderMesh* parent, TArray<MeshInfoPtr> meshes, MaterialInfoPtr matInfo);`
- L19 _public prototype_ `AsyncActionResultPtr Load();`
- L20 _public prototype_ `void PrepareForRendering(UWorld* world, FVector scale) override;`
- L21 _public prototype_ `void RemoveActors() override;`

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef std::shared_ptr<RenderMesh_EditorScene> RenderMesh_EditorScenePtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/3D/RenderMesh_Procedural.h` (Other)


#### class `RenderMesh_Procedural`  
`class RenderMesh_Procedural: public RenderMesh`  
_L15-32_
- inherits: `RenderMesh`
- L18 _private member_ `int _tesselation = 32;`
- L19 _private member_ `FVector2D _dimension= FVector2D::UnitVector;`
- L20 _private member_ `FVector _offSet;`
- L23 _public prototype_ `explicit RenderMesh_Procedural(const MeshLoadInfo loadInfo);`
- L24 _public prototype_ `virtual AsyncActionResultPtr Load() override;`
- L25 _public prototype_ `virtual void LoadInternal() override;`
- L26 _public prototype_ `void GenerateProcedural(int tesselation, FVector2D dimension, CoreMeshPtr cmesh);`
- L31 _public function_ `FORCEINLINE int& Tesselation()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L10 _typedef_ `typedef std::shared_ptr<CoreMesh> CoreMeshPtr;`
- L34 _typedef_ `typedef std::shared_ptr<RenderMesh_Procedural> RenderMesh_ProceduralPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/BinCache.h` (Other)


#### class `BinCache`  
`template <typename T_Key, typename T_Value> class BinCache`  
_L10-93_
- L12 _private typedef_ `typedef LruCache<T_Key, T_Value> LRUCache;`
- L14 _private member_ `mutable FCriticalSection CacheLock;` — Mutex for the actions (mutable because FScopeLock needs non-const object)
- L15 _private member_ `LRUCache Cache;` — The buffer cache that we have
- L18 _public function_ `BinCache(int32 MaxElements = 100000) : Cache(MaxElements)`
- L22 _public prototype_ `~BinCache() = default;`
- L27 _public function_ `FORCEINLINE const T_Value* Find(T_Key Key, bool bTouch)`
- L39 _public function_ `FORCEINLINE void UpdateValue(T_Key Key, T_Value NewValue)`
- L45 _public function_ `FORCEINLINE void TouchThreadSafe(T_Key Key)` — Thread-Safe touch
- L51 _public function_ `FORCEINLINE void Touch(T_Key Key)`
- L56 _public function_ `FORCEINLINE T_Value RemoveThreadSafe(T_Key Key)`
- L62 _public function_ `FORCEINLINE T_Value Remove(T_Key Key)`
- L74 _public function_ `FORCEINLINE void InsertThreadSafe(T_Key Key, T_Value Value)`
- L80 _public function_ `FORCEINLINE void Insert(T_Key Key, T_Value Value)`
- L85 _public function_ `FORCEINLINE void Empty()`
- L90 _public function_ `FORCEINLINE const LRUCache& GetCache() const`
- L91 _public function_ `FORCEINLINE LRUCache& GetCache()`
- L92 _public function_ `FORCEINLINE FCriticalSection* GetMutex()`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/Blob.h` (Other)


#### struct `DebugBlobLock`  
`struct DebugBlobLock`  
_L29-34_
- L32 _public prototype_ `DebugBlobLock();`
- L33 _public prototype_ `~DebugBlobLock();`

#### class `Blob`  
`class Blob : public std::enable_shared_from_this<Blob>`  
_L37-200_
- inherits: `std::enable_shared_from_this<Blob>`
- L44 _public member_ `static const char* LODTransformName;`
- L45 _public typedef_ `typedef std::vector<BlobPtrW> OwnerList;`
- L46 _public typedef_ `typedef std::vector<std::weak_ptr<Blob>> LinkedBlobsVec;`
- L49 _protected member_ `DeviceBufferRef Buffer;` — Device buffer that is attached to this blob
- L50 _protected member_ `bool bIsFinalised = false;` — Whether the promise has been finalised or not
- L51 _protected member_ `int32 ReplayCount = 0;` — For debug purpose, Incremented when replaying a job and regenerating the content of the blob.
- L52 _protected member_ `FDateTime FinaliseTS = FDateTime::Now();` — Time when the blob was finalised
- L54 _protected member_ `BlobPtrWVec LODLevels;` — The mip chain for this blob (for textures). Can also be Mesh data with fewer triangles etc. Doesn't matter to us
- L56 _protected member_ `BlobPtr MinMax;` — The blob that's used for calculating min/max
- L57 _protected member_ `std::shared_ptr<float> MinValue;` — Extracted min value (this is not always present)
- L58 _protected member_ `std::shared_ptr<float> MaxValue;` — Extracted min value (this is not always present)
- L60 _protected member_ `BlobPtr Histogram;` — The blob that's used for storing histogram data. not always have a histogram only created when required.
- L62 _protected member_ `BlobPtrW LODParent;` — The parent of this blob. Essentially the blob that was used to generate THIS lod Level
- L63 _protected member_ `BlobPtrW LODSource;` — The original source of this blob, the mip Level 0
- L65 _protected member_ `bool bIsLODLevel = false;` — Whether this blob already represents an LOD'd blob
- L66 _protected member_ `LinkedBlobsVec LinkedBlobs;` — Blobs that are linked to this tiled blob. These are objects that are
- L75 _protected member_ `OwnerList _owners;` — The TiledBlobs that contain this blob as a tile
- L76 _protected prototype_ `virtual void AddTiledOwner(BlobPtrW owner);`
- L79 _protected prototype_ `Blob();`
- L80 _protected prototype_ `virtual void OnFinaliseInternal(BlobReadyCallback callback) const;`
- L81 _protected prototype_ `virtual void ResetBuffer();`
- L82 _protected prototype_ `virtual void Touch(uint64 BatchId);`
- L83 _protected prototype_ `virtual void UpdateAccessInfo(uint64 batchId);`
- L84 _protected prototype_ `virtual void SetHash(CHashPtr Hash);`
- L86 _protected prototype_ `virtual void UpdateLinkedBlobs(bool bDoFinalise);`
- L87 _protected prototype_ `virtual void AddLinkedBlob(BlobPtr LinkedBlob);`
- L89 _protected prototype_ `virtual void FinaliseFrom(Blob* RHS);`
- L90 _protected prototype_ `virtual void SyncWith(Blob* RHS);`
- L93 _public prototype_ `Blob(DeviceBufferRef InBuffer);`
- L94 _public prototype_ `Blob(const BufferDescriptor& InDesc, CHashPtr InHash);`
- L95 _public prototype_ `Blob(const Blob& InBlob) = delete;` — non-copyable
- L97 _public prototype_ `virtual ~Blob();`
- L99 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo);`
- L100 _public prototype_ `virtual AsyncBufferResultPtr Unbind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo);`
- L101 _public prototype_ `virtual bool IsValid() const;`
- L102 _public prototype_ `virtual bool IsNull() const;`
- L103 _public prototype_ `virtual CHashPtr Hash() const;`
- L105 _public prototype_ `virtual AsyncBufferResultPtr Flush(const ResourceBindInfo& BindInfo);` — UE_API virtual void				SetHash(CHashPtr hash);
- L106 _public prototype_ `virtual AsyncPrepareResult PrepareForWrite(const ResourceBindInfo& BindInfo);`
- L112 _public prototype_ `virtual FString DisplayName() const;`
- L113 _public function_ `virtual bool IsFinalised() const`
- L114 _public function_ `virtual bool IsTiled() const`
- L115 _public function_ `virtual bool IsPromise() const`
- L116 _public function_ `virtual bool CanCalculateHash() const`
- L118 _public prototype_ `virtual void FinaliseNow(bool bNoCalcHash, CHashPtr FixedHash);`
- L119 _public prototype_ `virtual AsyncBufferResultPtr Finalise(bool bNoCalcHash, CHashPtr FixedHash);`
- L121 _public prototype_ `virtual AsyncRawBufferPtr Raw();` — SLOW: Read doc for DeviceBuffer::Raw() in DeviceBuffer.h
- L122 _public prototype_ `virtual AscynCHashPtr CalcHash();` — SLOW: Because calls Raw() underneath. Don't use directly
- L124 _public function_ `virtual FString& Name()`
- L125 _public function_ `virtual const FString& Name() const`
- L126 _public function_ `virtual const BufferDescriptor& GetDescriptor() const`
- L128 _public prototype_ `virtual AsyncBlobResultPtr OnFinalise() const;`
- L130 _public prototype_ `virtual AsyncDeviceBufferRef TransferTo(Device* TargetDevice);`
- L131 _public prototype_ `virtual DeviceBufferRef GetBufferRef() const;`
- L136 _public prototype_ `virtual BlobPtr GetMinMaxBlob();`
- L137 _public prototype_ `virtual void SetMinMax(BlobPtr InMinMax);`
- L138 _public prototype_ `virtual float GetMinValue() const;`
- L139 _public prototype_ `virtual float GetMaxValue() const;`
- L140 _public prototype_ `virtual bool HasMinMax() const;`
- L144 _public prototype_ `virtual BlobPtrW GetLODLevel(int32 Level);`
- L145 _public prototype_ `virtual bool HasLODLevels() const;`
- L146 _public prototype_ `virtual bool HasLODLevel(int32 Index) const;`
- L147 _public prototype_ `virtual int32 NumLODLevels() const;`
- L148 _public prototype_ `virtual void SetLODLevel(int32 Level, BlobPtr LODBlob, BlobPtrW LODParentBlob, BlobPtrW LODSourceBlob, bool bAddToBlobber);`
- L149 _public prototype_ `BlobPtr GetHistogram() const;`
- L155 _public prototype_ `virtual void AddOwner(BlobPtrW owner);`
- L156 _public prototype_ `virtual void RemoveOwner(BlobPtrW owner);`
- L157 _public prototype_ `void RemoveOwner(Blob* owner);`
- L158 _public prototype_ `virtual bool HasOwner(BlobPtrW owner);`
- L159 _public prototype_ `bool HasOwner(Blob* owner);`
- L160 _public prototype_ `virtual OwnerList::iterator FindOwner(BlobPtrW owner);`
- L161 _public prototype_ `OwnerList::iterator FindOwner(Blob* owner);`
- L162 _public function_ `virtual bool HasBlobAsTile(Blob* blob) const`
- L168 _public function_ `FORCEINLINE uint32 GetWidth() const`
- L169 _public function_ `FORCEINLINE uint32 GetHeight() const`
- L170 _public function_ `FORCEINLINE bool IsWellDefined()`
- L173 _public function_ `FORCEINLINE DeviceType GetDeviceType() const`
- L175 _public function_ `FORCEINLINE int32 GetReplayCount() const` — For debug purpose, report the replay number
- L176 _public function_ `FORCEINLINE const FDateTime& FinaliseTimestamp() const`
- L177 _public function_ `FORCEINLINE bool IsLateBound() const`
- L178 _public function_ `FORCEINLINE BlobPtrW GetLODParent() const`
- L179 _public function_ `FORCEINLINE BlobPtrW GetLODSource() const`
- L180 _public function_ `FORCEINLINE bool IsLODLevel() const`
- L181 _public function_ `FORCEINLINE bool IsTransient() const`
- L190 _public function_ `FORCEINLINE void SetHistogram(BlobPtr InHistogram)` — Sets the histogram of the blob
- L192 _public function_ `FORCEINLINE bool HasHistogram() const` — Check if blob already has a histogram
- L198 _public prototype_ `static CHashPtr CalculateMipHash(CHashPtr MainHash, int32 Level);`
- L199 _public prototype_ `static CHashPtrVec CalculateMipHashes(CHashPtr MainHash, CHashPtr ParentHash, int32 Level);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L19 _typedef_ `typedef TUniqueFunction<void(const Blob*)> BlobReadyCallback;`
- L20 _typedef_ `typedef cti::continuable<const Blob*> AsyncBlobResultPtr;`
- L22 _typedef_ `typedef std::shared_ptr<Blob> BlobPtr;`
- L23 _typedef_ `typedef std::unique_ptr<Blob> BlobUPtr;`
- L24 _typedef_ `typedef std::weak_ptr<Blob> BlobPtrW;`
- L25 _typedef_ `typedef std::vector<BlobPtr> BlobPtrVec;`
- L26 _typedef_ `typedef std::vector<BlobPtrW> BlobPtrWVec;`
- L203 _typedef_ `typedef T_Tiles<BlobPtr> BlobPtrTiles;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/BlobRef.h` (Other)


#### class `T_BlobRef`  
`template <class BlobType> class T_BlobRef`  
_L14-214_
- L19 _private typedef_ `typedef std::shared_ptr<BlobType> BlobTypePtr;`
- L20 _private typedef_ `typedef std::weak_ptr<BlobType> BlobTypePtrW;`
- L21 _private typedef_ `typedef T_BlobRef<BlobType> BlobTypeRef;`
- L24 _private member_ `mutable BlobTypePtrW PtrWeak;` — The weak pointer of the blob type
- L25 _private member_ `mutable CHashPtr Hash;` — The actual hash value that was saved at initialisation stage
- L26 _private member_ `mutable bool KeepStrong = false;` — Whether we should keep a strong ref or not
- L27 _private member_ `mutable bool CheckCached = false;`
- L30 _private member_ `mutable BlobTypePtr PtrStrong;` — The strong pointer of the blob type. This is only kept in certain cases when the
- L34 _private function_ `BlobTypePtr CheckReleaseStrongRef() const`
- L55 _private prototype_ `void CheckShouldKeepStrongRef();`
- L58 _public function_ `T_BlobRef()`
- L62 _public function_ `~T_BlobRef()`
- L71 _public function_ `T_BlobRef(BlobTypePtrW Ptr, bool CheckBlobber = true) : PtrWeak(Ptr), CheckCached(CheckBlobber)`
- L89 _public function_ `T_BlobRef(BlobTypePtr Ptr, bool CheckBlobber = true) : PtrWeak(Ptr), CheckCached(CheckBlobber)`
- L104 _public function_ `T_BlobRef(BlobTypePtr Ptr, bool KeepStrong_, bool CheckBlobber) : KeepStrong(KeepStrong_), CheckCached(CheckBlobber)`
- L122 _public function_ `T_BlobRef(BlobTypePtr Ptr, bool KeepStrong, bool CheckBlobber = false) : PtrStrong(Ptr)`
- L125 _public function_ `T_BlobRef(const BlobTypePtr& Ptr) : PtrStrong(Ptr)`
- L129 _public function_ `T_BlobRef(const T_BlobRef<BlobType>& RHS) : PtrStrong(RHS.PtrStrong)`
- L134 _public prototype_ `std::shared_ptr<BlobType> get() const;`
- L135 _public function_ `BlobTypePtr lock() const`
- L140 _public function_ `bool expired() const`
- L145 _public function_ `BlobType* operator -> () const`
- L150 _public function_ `bool operator == (const BlobTypeRef& RHS) const`
- L151 _public function_ `bool operator != (const DeviceBufferRef& RHS) const`
- L152 _public function_ `bool operator != (const BlobType* RHS) const`
- L154 _public function_ `bool operator == (const BlobType* RHS) const`
- L160 _public function_ `BlobTypeRef& operator = (const BlobTypeRef& RHS) const`
- L192 _public function_ `operator bool() const`
- L193 _public function_ `operator std::shared_ptr<BlobType>() const`
- L195 _public function_ `void Finalise()`
- L205 _public function_ `bool ShouldCheckCached() const`
- L206 _public function_ `bool IsKeepStrong() const`
- L207 _public function_ `FORCEINLINE CHashPtr GetHash() const`
- L213 _public function_ `bool IsNull() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define BLOB_REF_SIMPLE 1` — typename std::enable_if<std::is_base_of<Blob, BlobType>::value, void>::type
- L11 _macro_ `#define DEBUG_BLOB_REF_KEEPING 0`
- L216 _typedef_ `typedef T_BlobRef<Blob> BlobRef;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/Blobber.h` (Other)


#### class `BlobberObserverSource`  
`class BlobberObserverSource`  
_L28-58_
- L31 _public typedef_ `using HashArray = std::vector<HashType>;`
- L33 _public prototype_ `void AddHash(HashType Hash);`
- L34 _public prototype_ `void RemapHash(HashType OldHash, HashType NewHash);`
- L40 _protected member_ `FCriticalSection ObserverLock;`
- L42 _protected member_ `HashArray AddedHashStack;`
- L43 _protected member_ `HashArray RemappedHashStack;`
- L45 _protected member_ `uint32 Version = 1;`
- L48 _protected prototype_ `void Broadcast();` — Trigger the broadcast of the changes, this call is issued from the Blobber::Update function
- L51 _protected function_ `virtual void BlobberUpdated(HashArray&& InAddedHashes, HashArray&& InRemappedHashes)` — The customisable handler method triggered from Broadcast if any buffers were added or removed
- L54 _public prototype_ `BlobberObserverSource() = default;`
- L55 _public prototype_ `virtual ~BlobberObserverSource() = default;`
- L57 _public function_ `uint32 GetVersion() const` — The version of the current state of the Observer. Incremented when Broadcast trigger

#### struct `BlobCacheOptions`  
`struct BlobCacheOptions`  
_L62-66_
- L64 _public member_ `bool Discard = false;` — Whether the BlobObj is part of a "discard" cycle (user tweaking usually)
- L65 _public member_ `bool NoCacheBatch = false;` — Whether the batch is marked for no caching

#### class `Blobber`  
`class Blobber`  
_L68-260_
- L87 _public typedef_ `using BlobCacheEntryPtr = std::shared_ptr<BlobCacheEntry>;`
- L88 _public typedef_ `typedef BinCache<HashType, BlobCacheEntryPtr> BlobLRUCache;`
- L91 _private typedef_ `using BlobLUT = std::unordered_map<HashType, BlobCacheEntry>;`
- L92 _private typedef_ `using HashMappingTable = std::unordered_map<HashType, CHashPtr>;`
- L93 _private typedef_ `using BlobCacheEntryPtrVec = std::vector<BlobCacheEntryPtr>;`
- L94 _private typedef_ `using CHashPtrVec = std::vector<CHashPtr>;`
- L97 _private member_ `mutable FCriticalSection BlobLookupLock;` — typedef std::map<HashType, std::vector<HashType>> TempHashTable;
- L98 _private member_ `BlobLUT BlobLookup;` — The buffer cache that we have
- L99 _private member_ `BlobCacheEntryPtrVec TransientBlobs;` — List of transient blobs
- L100 _private member_ `BlobLRUCache BlobCache;` — Blob cache used for lookups and saving
- L101 _private member_ `CHashPtrVec TouchedHashes;` — Hashes that have been touched since the last idle update
- L103 _private member_ `double LastIdleUpdateTimestamp = 0;` — The last time the idle loop was run
- L104 _private member_ `double InvalidateTimestamp = 0;` — The last time the blobber cache was invalidated
- L106 _private member_ `size_t MemUsed = 0;` — How much memory are we using
- L107 _private member_ `size_t MemUsedNative = 0;` — Native memory used for all the blobs within the system
- L109 _private member_ `double TimeStatsPrinted = 0;` — The last time when stats were printed
- L110 _private member_ `bool ShouldPrintStats = false;` — Whether to print stats all all
- L112 _private member_ `FCriticalSection HashMutex;` — Mutex for the hashing tables
- L114 _private member_ `HashMappingTable GlobalHashes;` — All the globally unique hashes within the system. While the Hash object itself
- L126 _private member_ `HashMappingTable HashMappings;` — These are mappings from one Hash to another. The LHS is the Hash of the job
- L131 _private member_ `bool bEnableCache = true;` — Enable and disable caching within the TextureGraph system
- L134 _private member_ `bool EnableGC = true;` — This is for debugging purposes only. Never turn it off otherwise
- L136 _public function_ `FORCEINLINE void SetEnableGC(bool InEnableGC)`
- L137 _public function_ `FORCEINLINE bool IsGCEnabled() const`
- L148 _public typedef_ `typedef std::unordered_map<Blob*, DebugRefBlob> RefBlobMap;`
- L150 _public member_ `mutable FCriticalSection ReferencedBlobsLock;` — Mutex for the referenced blob LUT
- L151 _public member_ `RefBlobMap ReferencedBlobs;` — Blobs that are referenced (Debug only!)
- L154 _public prototype_ `void AddReferencedBlob(Blob* BlobObj, JobArg* Arg);`
- L155 _public prototype_ `void RemoveReferencedBlob(Blob* BlobObj, JobArg* Arg);`
- L156 _public prototype_ `bool IsBlobReferenced(Blob* BlobObj);`
- L160 _private member_ `BlobberObserverSourcePtr ObserverSource;` — Observer where the lifecycle of the blobs and hashes is recorded
- L163 _private member_ `FCriticalSection DebugBlobMutex;` — The TiledBlobs that contain this blob as a tile
- L166 _private prototype_ `void AddHashMapping(HashType LHS, CHashPtr RHS);`
- L167 _private prototype_ `void AddBlobEntry(HashType Hash, BlobPtr BlobObj, BlobCacheOptions Options);`
- L168 _private prototype_ `void AddBlobEntryThreadSafe(HashType Hash, BlobPtr BlobObj, BlobCacheOptions Options);`
- L169 _private prototype_ `void RemoveHashMapping(HashType Hash);`
- L171 _private prototype_ `void PrintStats();`
- L172 _private prototype_ `BlobRef AddInternal(BlobPtr BlobObj, BlobCacheOptions Options);`
- L173 _private prototype_ `BlobPtr Remove(HashType Hash);`
- L175 _private prototype_ `CHashPtr AddGloballyUniqueHashInternal(CHashPtr Hash);`
- L176 _private prototype_ `void UpdateGloballyUniqueHashInternal(HashType OldValue);`
- L177 _private prototype_ `void UpdateMappingInternal(HashType OldValue, CHashPtr NewValue);`
- L178 _private prototype_ `void UpdateBlobLookupInternal(HashType OldValue, BlobPtr BlobObj);`
- L179 _private prototype_ `void Touch(const Blob* BlobObj);`
- L180 _private prototype_ `BlobCacheEntryPtr FindInternal(HashType Hash);`
- L181 _private prototype_ `BlobRef AddResult(CHashPtr LHash, BlobRef Result, BlobCacheOptions Options);`
- L182 _private prototype_ `void UpdateTransient();`
- L183 _private prototype_ `void UpdateTouchedHashes();`
- L184 _private prototype_ `void UpdateBlobCache();`
- L187 _public prototype_ `Blobber();`
- L188 _public prototype_ `~Blobber();`
- L190 _public prototype_ `BlobRef FindSingle(HashType Hash);`
- L191 _public prototype_ `TiledBlobRef FindTiled(HashType Hash);`
- L193 _public prototype_ `BlobRef Create(const BufferDescriptor& Desc);`
- L194 _public prototype_ `BlobRef Create(Device* Dev, RawBufferPtr Raw);`
- L195 _public prototype_ `BlobRef Create(DeviceBufferRef DevBuffer, bool NoCache = false);`
- L197 _public prototype_ `BlobRef AddResult(CHashPtr LHash, BlobPtr InBlob, BlobCacheOptions Options = {});`
- L198 _public prototype_ `void ClearCache();`
- L205 _public prototype_ `TiledBlobRef AddTiledResult(CHashPtr LHash, TiledBlobPtr Result, BlobCacheOptions Options = {});` — In order to minimise the changes brought upon by weak reference work we've made this function. If we were to force this to take a unique_ptr<TiledBlob> it would've resulted in lots of changes around asset manager and other bits of code (Jobs etc), that we can do without. Eventually, this should either go away, or be converted to accept a unique pointer to force stop shared_ptr being passed around
- L206 _public prototype_ `TiledBlobRef AddTiledResult(TiledBlobPtr Result, BlobCacheOptions Options = {});`
- L208 _public prototype_ `void UpdateBlobHash(HashType OldHash, BlobRef InBlob);`
- L209 _public prototype_ `void UpdateHash(HashType OldHash, CHashPtr NewHash);`
- L210 _public prototype_ `void Update(float DT);`
- L211 _public prototype_ `AsyncJobResultPtr UpdateIdle();`
- L212 _public prototype_ `bool IsBlobCached(HashType Hash);`
- L214 _public prototype_ `void RegisterObserverSource(const BlobberObserverSourcePtr& observerSource);` — /
- L217 _public function_ `template <class BlobType> T_BlobRef<BlobType> Find(HashType Hash)`
- L226 _public function_ `template <> BlobRef Find<Blob>(HashType Hash)`
- L232 _public function_ `template <> TiledBlobRef Find<TiledBlob>(HashType Hash)`
- L237 _public function_ `BlobRef Find(HashType Hash)`
- L245 _public function_ `FORCEINLINE CHashPtr AddGloballyUniqueHash(CHashPtr Hash)`
- L251 _public function_ `FORCEINLINE void SetEnableCache(bool InEnableCache)`
- L252 _public function_ `FORCEINLINE bool IsCacheEnabled() const`
- L254 _public function_ `FORCEINLINE BlobberObserverSourcePtr GetObserverSource() const`
- L257 _public function_ `FCriticalSection* GetDebugBlobMutex()`

#### struct `Blobber::BlobCacheEntry`  
`struct BlobCacheEntry`  
_L76-86_
- L78 _public member_ `BlobPtr BlobObj;` — The actual BlobObj object within the cache entry
- L79 _public member_ `BlobCacheOptions Options;` — The options associated with this BlobObj entry
- L80 _public member_ `double CreateTimestamp = Util::Time();` — The timestamp when this entry was created
- L81 _public member_ `double AccessTimestamp = Util::Time();` — The timestamp when this entry was last accessed
- L83 _public prototype_ `~BlobCacheEntry();`
- L85 _public function_ `FORCEINLINE TiledBlobPtr AsTiledBlob() const`

#### struct `Blobber::DebugRefBlob`  
`struct DebugRefBlob`  
_L142-146_
- L144 _public member_ `int32 RefCount = 0;`
- L145 _public member_ `std::vector<JobArg*> JobArgs;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L18 _typedef_ `typedef std::shared_ptr<JobResult> JobResultPtr;`
- L19 _typedef_ `typedef cti::continuable<JobResultPtr> AsyncJobResultPtr;`
- L20 _typedef_ `typedef T_BlobRef<Blob> BlobRef;`
- L21 _typedef_ `typedef T_BlobRef<TiledBlob> TiledBlobRef;`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlob, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlob, Log, All);`
- L25 _typedef_ `typedef std::vector<HashType> HashTypes;`
- L60 _typedef_ `typedef std::shared_ptr<BlobberObserverSource> BlobberObserverSourcePtr;`
- L262 _typedef_ `typedef std::unique_ptr<Blobber> BlobberPtr;`
- L266 _function_ `template <class BlobType> void T_BlobRef<BlobType>::CheckShouldKeepStrongRef()` (scope `T_BlobRef`)
- L290 _function_ `template <class BlobType> std::shared_ptr<BlobType> T_BlobRef<BlobType>::get() const` (scope `T_BlobRef`)

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/G_Collectible.h` (Other)


#### struct `AccessInfo`  
`struct AccessInfo`  
_L10-37_
- L12 _public member_ `std::atomic<double> Timestamp = 0;` — The last time was accessed. We use timestamp to determine modification
- L17 _public member_ `uint64 FrameId = 0;` — If any of these need to be accessed in a thread-safe manner then these can be turned into atomics as well
- L18 _public member_ `uint64 BatchId = 0;` — The batch ID when this was last bound
- L19 _public member_ `uint64 Count = 0;` — The number of times this was bound and accessed
- L21 _public function_ `AccessInfo()`
- L25 _public function_ `AccessInfo(const AccessInfo& RHS)`
- L30 _public function_ `FORCEINLINE void operator = (const AccessInfo& RHS)`

#### class `G_Collectible`  
`class G_Collectible`  
_L41-55_
- desc: Garbage collectible data structure
- L44 _protected member_ `AccessInfo AccessDetails;` — Information about the last time this DeviceBuffer was accessed
- L47 _public prototype_ `virtual void UpdateAccessInfo(uint64 BatchId = 0);`
- L48 _public prototype_ `virtual ~G_Collectible() = default;`
- L53 _public function_ `FORCEINLINE const AccessInfo& GetAccessInfo() const`
- L54 _public function_ `FORCEINLINE bool IsSame(const std::atomic<double>& Timestamp) const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/LruCache.h` (Other)


#### class `LruCache`  
`template<typename KeyType, typename ValueType, typename KeyComp = DefaultKeyComparer<KeyType> > class LruCache`  
_L12-702_
- L93 _public function_ `LruCache() : LeastRecent(nullptr) , MostRecent(nullptr) , MaxNumElements(0)` — Default constructor (empty cache that cannot hold any values).
- L104 _public function_ `LruCache(int32 InMaxNumElements) : LeastRecent(nullptr) , MostRecent(nullptr) , MaxNumElements(InMaxNumElements)` — Create and initialize a new instance. @param InMaxNumElements The maximum number of elements this cache can hold.
- L113 _public function_ `~LruCache()` — Destructor.
- L131 _public function_ `void Add(const KeyType& Key, const ValueType& Value)` — Add an entry to the cache. If an entry with the specified key already exists in the cache, the value of the existing entry will be updated. The added or updated entry will be marked as the most recently used one. @param Key The entry's lookup key. @param Value The entry's value. @see Empty, Find, GetKeys, Remove
- L174 _public function_ `FORCEINLINE bool Contains(const KeyType& Key) const` — Check whether an entry with the specified key is in the cache. @param Key The key of the entry to check. @return true if the entry is in the cache, false otherwise. @see Add, ContainsByPredicate, Empty, FilterByPredicate, Find, GetKeys, Remove
- L187 _public function_ `template<typename Predicate> FORCEINLINE bool ContainsByPredicate(Predicate Pred) const` — Check whether an entry for which a predicate returns true is in the cache. @param Pred The predicate functor to apply to each entry. @return true if at least one matching entry is in the cache, false otherwise. @see Contains, FilterByPredicate, FindByPredicate, RemoveByPredicate
- L206 _public function_ `void Empty(int32 InMaxNumElements = 0)` — Empty the cache. @param InMaxNumElements The maximum number of elements this cache can hold (default = 0). @see Add, Find, GetKeys, Max, Num, Remove
- L230 _public function_ `template<typename Predicate> TArray<ValueType> FilterByPredicate(Predicate Pred) const` — Filter the entries in the cache using a predicate. @param Pred The predicate functor to apply to each entry. @return Collection of values for which the predicate returned true. @see ContainsByPredicate, FindByPredicate, Find, RemoveByPredicate
- L252 _public function_ `FORCEINLINE const ValueType* Find(const KeyType& Key) const` — Find the value of the entry with the specified key. @param Key The key of the entry to get. @return Pointer to the value, or nullptr if not found. @see Add, Contains, Empty, FindAndTouch, GetKeys, Remove
- L264 _public function_ `FORCEINLINE ValueType* Find(const KeyType& Key)`
- L282 _public function_ `FORCEINLINE const ValueType& FindChecked(const KeyType& Key) const` — Find the value of the entry with the specified key. @param Key The key of the entry to get. @return Reference to the value, or triggers an assertion if the key does not exist.
- L297 _public function_ `FORCEINLINE ValueType FindRef(const KeyType& Key) const` — Find the value of the entry with the specified key. @param Key The key of the entry to get. @return Copy of the value, or the default value for the ValueType if the key does not exist.
- L316 _public function_ `const ValueType* FindAndTouch(const KeyType& Key)` — Find the value of the entry with the specified key and mark it as the most recently used. @param Key The key of the entry to get. @return Pointer to the value, or nullptr if not found. @see Add, Contains, Empty, Find, GetKeys, Remove
- L336 _public function_ `const ValueType& FindAndTouchChecked(const KeyType& Key)` — Find the value of the entry with the specified key and mark it as the most recently used. @param Key The key of the entry to get. @return Pointer to the value, or triggers an assertion if the key does not exist.
- L353 _public function_ `ValueType FindAndTouchRef(const KeyType& Key)` — Find the value of the entry with the specified key and mark it as the most recently used. @param Key The key of the entry to get. @return Copy of the value, or the default value for the ValueType if the key does not exist.
- L375 _public function_ `template<typename Predicate> const ValueType* FindByPredicate(Predicate Pred) const` — Find the value of an entry using a predicate. @param Pred The predicate functor to apply to each entry. @return A value for which the predicate returned true, or nullptr if not found. @see ContainsByPredicate, FilterByPredicate, RemoveByPredicate
- L394 _public function_ `void GetKeys(TArray<KeyType>& OutKeys) const` — Find the keys of all cached entries. @param OutKeys Will contain the collection of keys. @see Add, Empty, Find
- L408 _public function_ `FORCEINLINE int32 Max() const` — Get the maximum number of entries in the cache. @return Maximum number of entries. @see Empty, Num
- L419 _public function_ `FORCEINLINE int32 Num() const` — Get the number of entries in the cache. @return Number of entries. @see Empty, Max
- L430 _public function_ `ValueType Remove(const KeyType& Key)` — Remove all entries with the specified key from the cache. @param Key The key of the entries to remove. @see Add, Empty, Find, RemoveByPredicate
- L450 _public function_ `template<typename Predicate> int32 RemoveByPredicate(Predicate Pred)` — Remove all entries using a predicate. @param Pred The predicate function to apply to each entry. @return Number of removed entries. @see ContainsByPredicate, FilterByPredicate, FindByPredicate, Remove
- L471 _public function_ `FORCEINLINE ValueType RemoveLeastRecent()` — Remove and return the least recent element from the cache. @return Copy of removed value.
- L507 _public function_ `FORCEINLINE friend bool operator==(const TBaseIterator& Lhs, const TBaseIterator& Rhs)`
- L512 _public function_ `FORCEINLINE friend bool operator!=(const TBaseIterator& Lhs, const TBaseIterator& Rhs)`
- L630 _protected function_ `FORCEINLINE void MarkAsRecent(FCacheEntry& Entry)` — Mark the given entry as recently used. @param Entry The entry to mark.
- L655 _protected function_ `FORCEINLINE ValueType Remove(FCacheEntry* Entry)` — Remove the specified entry from the cache. @param Entry The entry to remove.
- L684 _public function_ `TIterator begin()`
- L685 _public function_ `TConstIterator begin() const`
- L686 _public function_ `TIterator end()`
- L687 _public function_ `TConstIterator end() const`
- L692 _private member_ `TSet<FCacheEntry*, FKeyFuncs> LookupSet;` — Set of entries for fast lookup.
- L695 _private member_ `FCacheEntry* LeastRecent;` — Least recent item in the cache.
- L698 _private member_ `FCacheEntry* MostRecent;` — Most recent item in the cache.
- L701 _private member_ `int32 MaxNumElements;` — Maximum number of elements in the cache.

#### struct `LruCache::FCacheEntry`  
`struct FCacheEntry`  
_L15-69_
- desc: An entry in the LRU cache.
- L18 _public member_ `KeyType Key;` — The entry's lookup key.
- L21 _public member_ `FCacheEntry* LessRecent;` — The less recent entry in the linked list.
- L24 _public member_ `FCacheEntry* MoreRecent;` — The more recent entry in the linked list.
- L27 _public member_ `ValueType Value;` — The entry's value.
- L35 _public function_ `FCacheEntry(const KeyType& InKey, const ValueType& InValue) : Key(InKey) , LessRecent(nullptr) , MoreRecent(nullptr) , Value(InValue)` — Create and initialize a new instance. @param InKey The entry's key. @param InValue The entry's value.
- L43 _public function_ `FORCEINLINE void LinkBefore(FCacheEntry* Other)` — Add this entry before the given one.
- L54 _public function_ `FORCEINLINE void Unlink()` — Remove this entry from the list.

#### struct `LruCache::FKeyFuncs`  
`struct FKeyFuncs : public BaseKeyFuncs<FCacheEntry*, KeyType>`  
_L72-88_
- inherits: `BaseKeyFuncs<FCacheEntry*,KeyType>`
- desc: Lookup set key functions.
- L74 _public function_ `FORCEINLINE static const KeyType& GetSetKey(const FCacheEntry* Entry)`
- L79 _public function_ `FORCEINLINE static bool Matches(KeyType A, KeyType B)`
- L84 _public function_ `FORCEINLINE static uint32 GetKeyHash(KeyType Key)`

#### class `LruCache::TBaseIterator`  
`template<bool Const> class TBaseIterator`  
_L487-569_
- desc: Base class for cache iterators. Iteration begins at the most recent entry.
- L491 _public function_ `FORCEINLINE TBaseIterator() : CurrentEntry(nullptr)`
- L495 _public function_ `FORCEINLINE TBaseIterator(const LruCache& Cache) : CurrentEntry(Cache.LeastRecent)`
- L501 _public function_ `FORCEINLINE TBaseIterator& operator++()`
- L517 _public function_ `ValueType& operator->() const`
- L523 _public function_ `ValueType& operator*() const`
- L529 _public function_ `FORCEINLINE explicit operator bool() const`
- L534 _public function_ `FORCEINLINE bool operator!() const`
- L541 _public function_ `FORCEINLINE KeyType& Key() const`
- L547 _public function_ `FORCEINLINE ValueType& Value() const`
- L555 _protected function_ `FCacheEntry* GetCurrentEntry()`
- L560 _protected function_ `void Increment()`
- L568 _private member_ `FCacheEntry* CurrentEntry;`

#### class `LruCache::TConstIterator`  
`class TConstIterator : public TBaseIterator<true>`  
_L575-587_
- inherits: `TBaseIterator<true>`
- desc: Cache iterator (const).
- L580 _public function_ `FORCEINLINE TConstIterator() : TBaseIterator<true>()`
- L584 _public function_ `FORCEINLINE TConstIterator(const LruCache& Cache) : TBaseIterator<true>(Cache)`

#### class `LruCache::TIterator`  
`class TIterator : public TBaseIterator<false>`  
_L593-621_
- inherits: `TBaseIterator<false>`
- desc: Cache iterator.
- L598 _public function_ `FORCEINLINE TIterator() : TBaseIterator<false>() , Cache(nullptr)`
- L603 _public function_ `FORCEINLINE TIterator(LruCache& InCache) : TBaseIterator<false>(InCache) , Cache(&InCache)`
- L609 _public function_ `FORCEINLINE void RemoveCurrentAndIncrement()` — Removes the current element from the cache and increments the iterator.
- L620 _private member_ `LruCache* Cache;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/RawBuffer.h` (Other)


#### enum `BufferFormat`  
`enum class BufferFormat`  
_L16-32_
- L18 _public enumerator_ `Byte`
- L19 _public enumerator_ `Half`
- L20 _public enumerator_ `Float`
- L21 _public enumerator_ `Short`
- L22 _public enumerator_ `Int`
- L24 _public enumerator_ `Count`
- L26 _public enumerator_ `Auto = -1` — Automatically deduce
- L27 _public enumerator_ `Custom = -2`
- L29 _public enumerator_ `LateBound = -3` — The Format is unknown at the time and will

#### enum `BufferType`  
`enum class BufferType`  
_L34-40_
- L36 _public enumerator_ `Generic`
- L37 _public enumerator_ `Image`
- L38 _public enumerator_ `Mesh`
- L39 _public enumerator_ `MeshDetail`

#### struct `RawBufferMetadataDefs`  
`struct RawBufferMetadataDefs`  
_L48-63_
- L53 _public member_ `static const FString G_FX_UAV;`
- L62 _public member_ `static const FString G_LAYER_MASK;`

#### struct `BufferDescriptor`  
`struct BufferDescriptor`  
_L66-124_
- L68 _public typedef_ `typedef std::set<FString> BufferMetadata;`
- L70 _public member_ `FString Name;` — The name of the buffer
- L71 _public member_ `uint32 Width = 0;` — Width of the buffer in terms of number of points
- L72 _public member_ `uint32 Height = 0;` — Height of the buffer in terms of number of points
- L73 _public member_ `uint32 ItemsPerPoint = 0;` — How many items of Type BufferFormat per point
- L74 _public member_ `BufferFormat Format = BufferFormat::Auto;` — What is the Type of each item in the buffer
- L75 _public member_ `BufferType Type = BufferType::Image;` — Buffer Type. This is mostly used for debugging
- L76 _public member_ `FLinearColor DefaultValue = FLinearColor::Black;` — The default value of the blob values
- L78 _public member_ `bool bIsSRGB = false;`
- L79 _public member_ `bool bIsTransient = false;` — Whether this is a transient buffer
- L80 _public member_ `bool bMipMaps = false;` — Enable mip maps for this buffer
- L82 _public member_ `BufferMetadata Metadata;` — The metadata associated with this buffer descriptor
- L84 _public prototype_ `HashType HashValue() const;`
- L85 _public prototype_ `HashType FormatHashValue() const;`
- L86 _public prototype_ `static const char* FormatToString(BufferFormat InFormat);`
- L88 _public function_ `BufferDescriptor()`
- L89 _public prototype_ `BufferDescriptor(uint32 InWidth, uint32 InHeight, uint32 InItemsPerPoint, BufferFormat InFormat = BufferFormat::Float, FLinearColor InDefaultValue = FLinearColor::Black, BufferType InType = BufferType::Image, bool bInMipMaps = false, bool bInSRGB = false);`
- L92 _public prototype_ `static EPixelFormat BufferPixelFormat(BufferFormat InFormat, uint32 InItemsPerPoint);`
- L93 _public prototype_ `static BufferFormat BufferFormatFromPixelFormat(EPixelFormat PixelFormat);`
- L94 _public prototype_ `static size_t BufferFormatSize(BufferFormat InFormat);`
- L95 _public prototype_ `static ETextureSourceFormat TextureSourceFormat(BufferFormat InFormat, uint32 InItemsPerPoint);`
- L96 _public prototype_ `static BufferDescriptor Combine(const BufferDescriptor& Desc1, const BufferDescriptor& Desc2);`
- L97 _public prototype_ `static BufferDescriptor CombineWithPreference(const BufferDescriptor* BaseDesc, const BufferDescriptor* OverrideDesc, const BufferDescriptor* RefDesc);`
- L99 _public prototype_ `ETextureSourceFormat TextureSourceFormat() const;`
- L100 _public prototype_ `bool IsValid() const;`
- L101 _public prototype_ `bool IsFinal() const;`
- L103 _public function_ `FORCEINLINE size_t FormatSize() const`
- L104 _public function_ `FORCEINLINE size_t Pitch() const`
- L105 _public function_ `FORCEINLINE size_t Size() const`
- L106 _public function_ `FORCEINLINE EPixelFormat PixelFormat() const`
- L108 _public function_ `FORCEINLINE bool HasMetadata(const FString& meta) const`
- L109 _public function_ `FORCEINLINE bool HasMetadata(FString&& meta) const`
- L110 _public function_ `FORCEINLINE bool IsLateBound() const`
- L111 _public function_ `FORCEINLINE bool IsAuto() const`
- L112 _public function_ `FORCEINLINE bool IsAutoWidth() const`
- L113 _public function_ `FORCEINLINE bool IsAutoHeight() const`
- L114 _public function_ `FORCEINLINE bool IsAutoSize() const`
- L116 _public function_ `void AddMetadata(const FString& meta)`
- L117 _public function_ `void AddMetadata(FString&& meta)`
- L119 _public prototype_ `bool operator == (const BufferDescriptor& rhs) const;`
- L120 _public prototype_ `bool operator != (const BufferDescriptor& RHS) const;`
- L122 _public function_ `FORCEINLINE void AllowUAV()`
- L123 _public function_ `FORCEINLINE bool RequiresUAV() const`

#### enum `RawBufferCompressionType`  
`enum class RawBufferCompressionType`  
_L135-143_
- L137 _public enumerator_ `None` — No compression
- L138 _public enumerator_ `Auto` — Automatically choose a compression Format
- L139 _public enumerator_ `PNG` — PNG compression
- L140 _public enumerator_ `ZLib` — ZLib compression
- L141 _public enumerator_ `GZip` — GZip compression
- L142 _public enumerator_ `LZ4` — LZ4 compression

#### class `RawBuffer`  
`class RawBuffer`  
_L145-233_
- L148 _public member_ `static const uint64 GMinCompress;` — Must have at least this much data to consider compression.
- L162 _private member_ `static const RawBufferCompressionType GDefaultCompression;`
- L169 _private member_ `const uint8* Data = nullptr;` — The actual raw buffer
- L170 _private member_ `uint64 Length = 0;` — The length of the data
- L171 _private member_ `BufferDescriptor Desc;` — The buffer descriptor
- L172 _private member_ `mutable CHashPtr HashValue;` — The hash for this buffer
- L173 _private member_ `bool bIsMemoryAutoManaged = false;` — There can be instances where the owner of _data isnt RawBuffer, this check ensures those cases
- L178 _private member_ `const uint8* CompressedData = nullptr;` — The compressed data
- L179 _private member_ `uint64 CompressedLength = 0;` — Length of the compressed buffer
- L180 _private member_ `RawBufferCompressionType CompressionType = RawBufferCompressionType::None;` — What is the Type of compression used
- L185 _private member_ `FString FileName;` — The path where the file data is kept
- L187 _private prototype_ `RawBufferCompressionType ChooseBestCompressionFormat() const;`
- L189 _private prototype_ `void FreeUncompressed();`
- L190 _private prototype_ `void FreeCompressed();`
- L191 _private prototype_ `void FreeDisk();`
- L193 _private prototype_ `bool UncompressPNG();`
- L194 _private prototype_ `bool UncompressGeneric(FName InName);`
- L196 _private prototype_ `bool CompressPNG();`
- L197 _private prototype_ `bool CompressGeneric(FName InName, RawBufferCompressionType InType);`
- L199 _private prototype_ `AsyncRawBufferP ReadFromFile(bool bDoUncompress = false);`
- L202 _public prototype_ `RawBuffer(const uint8* InData, size_t InLength, const BufferDescriptor& InDesc, CHashPtr InHashValue = nullptr, bool bInIsMemoryAutoManaged = false);`
- L203 _public prototype_ `explicit RawBuffer(const BufferDescriptor& InDesc);`
- L204 _public prototype_ `explicit RawBuffer(const RawBufferPtrTiles& InTiles);`
- L205 _public prototype_ `~RawBuffer();`
- L207 _public prototype_ `AsyncRawBufferP Compress(RawBufferCompressionType InCompressionType = RawBufferCompressionType::Auto, bool bFreeMemory = true);`
- L208 _public prototype_ `AsyncRawBufferP Uncompress(bool bFreeMemory = true);`
- L210 _public prototype_ `AsyncRawBufferP WriteToFile(const FString& InFileName, bool bFreeMemory = true);`
- L212 _public prototype_ `AsyncRawBufferP LoadRawBuffer(bool bInDoUncompress, bool bFreeMemory = true);`
- L214 _public prototype_ `void GetAsLinearColor(TArray<FLinearColor>& Pixels) const;`
- L215 _public prototype_ `FLinearColor GetAsLinearColor(int PixelIndex) const;`
- L217 _public prototype_ `bool IsPadded() const;`
- L218 _public prototype_ `size_t GetUnpaddedSize();`
- L219 _public prototype_ `void CopyUnpaddedBytes(uint8* DestData);`
- L223 _public function_ `FORCEINLINE const uint8* GetData() const`
- L224 _public function_ `FORCEINLINE size_t GetLength() const`
- L225 _public function_ `FORCEINLINE CHashPtr Hash() const`
- L226 _public function_ `FORCEINLINE const FString& GetName() const`
- L227 _public function_ `FORCEINLINE const BufferDescriptor& GetDescriptor() const`
- L228 _public function_ `FORCEINLINE uint32 Width() const`
- L229 _public function_ `FORCEINLINE uint32 Height() const`
- L230 _public function_ `FORCEINLINE bool IsTransient() const`
- L231 _public function_ `FORCEINLINE bool IsCompressed() const`
- L232 _public function_ `FORCEINLINE bool HasData() const`

#### struct `RawBuffer::FileHeader`  
`struct FileHeader`  
_L153-160_
- desc: Must be fixed size (ideally every member should be 64-bit aligned)
- L155 _public member_ `uint64 Version = sizeof(FileHeader);`
- L156 _public member_ `uint64 CompressionType;`
- L157 _public member_ `uint64 CompressedLength = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L126 _typedef_ `typedef std::unique_ptr<BufferDescriptor> BufferDescriptorUPtr;`
- L127 _typedef_ `typedef std::shared_ptr<BufferDescriptor> BufferDescriptorPtr;`
- L130 _typedef_ `typedef std::shared_ptr<RawBuffer> RawBufferPtr;`
- L131 _typedef_ `typedef T_Tiles<std::shared_ptr<RawBuffer>> RawBufferPtrTiles;`
- L132 _typedef_ `typedef cti::continuable<RawBufferPtr> AsyncRawBufferPtr;`
- L133 _typedef_ `typedef cti::continuable<RawBuffer*> AsyncRawBufferP;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Data/TiledBlob.h` (Other)


#### class `TiledBlob`  
`class TiledBlob : public Blob`  
_L19-145_
- inherits: `Blob`
- L25 _protected member_ `mutable BlobPtrTiles Tiles;` — The Tiles that make up the larger BlobObj
- L26 _protected member_ `mutable CHashPtr HashValue;` — The HashValue of tiled BlobObj
- L27 _protected member_ `mutable BufferDescriptor Desc;` — We keep the combined descriptor separately
- L28 _protected member_ `bool bReady = false;` — Whether the Buffer is already ready
- L29 _protected member_ `bool bTiledTarget = true;` — Whether we're rendering to this as a tile by tile Target or not
- L30 _protected member_ `JobPtrW JobObj;` — The job that is potentially generating this tiled BlobObj
- L31 _protected member_ `BlobPtr SingleBlob;` — Single BlobObj pointer that we keep to prevent going out of Ref
- L33 _protected prototype_ `void CalcHashNow() const;`
- L34 _protected prototype_ `virtual void ResetBuffer() override;`
- L36 _protected prototype_ `virtual void TouchTiles(uint64 BatchId);`
- L37 _protected prototype_ `virtual void Touch(uint64 BatchId) override;`
- L38 _protected prototype_ `virtual void MakeSingleBlob_Internal();`
- L39 _protected prototype_ `TiledBlob& operator = (const TiledBlob& RHS);`
- L40 _protected prototype_ `virtual void SetHash(CHashPtr Hash) override;`
- L42 _protected prototype_ `virtual void AddLinkedBlob(BlobPtr LinkedBlob) override;`
- L43 _protected prototype_ `virtual void FinaliseFrom(Blob* RHS) override;`
- L46 _public prototype_ `static AsyncBufferResultPtr TileBuffer(DeviceBufferRef Buffer, BlobPtrTiles& Tiles);`
- L47 _public prototype_ `AsyncBufferResultPtr CombineTiles(bool bTouch, bool bIsArray, uint64 BatchId = 0);`
- L49 _public prototype_ `TiledBlob(const BufferDescriptor& Desc, const BlobPtrTiles& Tiles);`
- L52 _public prototype_ `TiledBlob(const BufferDescriptor& Desc, size_t NumTilesX, size_t NumTilesY, CHashPtr HashValue);`
- L53 _public prototype_ `TiledBlob(DeviceBufferRef Buffer);`
- L54 _public prototype_ `TiledBlob(BlobRef BlobObj);`
- L57 _public prototype_ `static std::shared_ptr<TiledBlob> InitFromTiles(const BufferDescriptor& Desc, BlobPtrTiles& Tiles);`
- L59 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L60 _public prototype_ `virtual AsyncBufferResultPtr Unbind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L62 _public prototype_ `virtual bool IsValid() const override;`
- L63 _public prototype_ `virtual bool IsNull() const override;`
- L64 _public prototype_ `virtual AscynCHashPtr CalcHash() override;` — SLOW: Because calls Raw() underneath. Don't use directly
- L66 _public prototype_ `virtual CHashPtr Hash() const override;`
- L67 _public prototype_ `virtual AsyncBufferResultPtr Flush(const ResourceBindInfo& BindInfo) override;`
- L68 _public prototype_ `virtual AsyncPrepareResult PrepareForWrite(const ResourceBindInfo& BindInfo) override;`
- L69 _public prototype_ `virtual FString DisplayName() const override;`
- L70 _public function_ `virtual bool IsTiled() const override`
- L71 _public prototype_ `virtual bool CanCalculateHash() const override;`
- L72 _public prototype_ `virtual void SetTile(int32 X, int32 Y, BlobRef Tile);`
- L73 _public prototype_ `virtual void SetTiles(const BlobPtrTiles& InTiles);`
- L75 _public function_ `virtual FString& Name() override`
- L76 _public function_ `virtual const FString& Name() const override`
- L77 _public function_ `virtual const BufferDescriptor& GetDescriptor() const override`
- L79 _public prototype_ `virtual AsyncBufferResultPtr MakeSingleBlob();`
- L81 _public prototype_ `virtual AsyncDeviceBufferRef TransferTo(Device* Target) override;`
- L82 _public prototype_ `virtual DeviceBufferRef GetBufferRef() const override;`
- L84 _public prototype_ `virtual void ResolveLateBound(BlobPtr Ref);`
- L85 _public prototype_ `virtual void ResolveLateBound(const BufferDescriptor& Desc, bool bOverrideExisting = false);`
- L86 _public prototype_ `virtual void CopyResolveLateBound(BlobPtr RHS);`
- L87 _public prototype_ `virtual void SetTransient();`
- L88 _public prototype_ `virtual void FinaliseNow(bool bNoCalcHash, CHashPtr FixedHash) override;`
- L93 _public prototype_ `virtual void SetMinMax(BlobPtr MinMax_) override;`
- L98 _public prototype_ `virtual void SetLODLevel(int32 Level_, BlobPtr BlobObj, BlobPtrW LODParent_, BlobPtrW LODSource_, bool AddToBlobber) override;`
- L104 _public prototype_ `virtual bool HasBlobAsTile(Blob* BlobObj) const override;`
- L115 _public prototype_ `static std::shared_ptr<TiledBlob> AsTiledBlob(BlobPtr BlobObj);` — Takes a BlobObj and returns a TiledBlob. If the passed BlobObj is already tiled, then it does nothing. Otherwise it creates a new TiledBlob with 1x1 tile that contains the passed BlobObj. Just a simple helper function, used in places that always require a TiledBlob.
- L120 _public function_ `FORCEINLINE size_t Rows() const`
- L121 _public function_ `FORCEINLINE size_t Cols() const`
- L122 _public function_ `FORCEINLINE const BlobPtrTiles& GetTiles() const`
- L123 _public function_ `FORCEINLINE uint32 GetWidth() const`
- L124 _public function_ `FORCEINLINE uint32 GetHeight() const`
- L125 _public function_ `FORCEINLINE bool TiledTarget() const`
- L126 _public function_ `FORCEINLINE bool& TiledTarget()`
- L127 _public function_ `FORCEINLINE bool IsWellDefined()`
- L128 _public function_ `FORCEINLINE bool IsValidTileIndex(int32 RowId, int32 ColId) const`
- L133 _public function_ `FORCEINLINE BlobRef GetTile(int32 RowId, int32 ColId) const`
- L141 _public function_ `FORCEINLINE BlobPtr GetSingleBlob() const`
- L143 _public function_ `JobPtrW Job() const`
- L144 _public function_ `JobPtrW& Job()`

#### class `TiledBlob_Promise`  
`class TiledBlob_Promise : public TiledBlob`  
_L159-197_
- inherits: `TiledBlob`
- L162 _protected member_ `mutable std::vector<BlobReadyCallback> Callbacks;` — The callbacks to call when the promised tiled BlobObj is ready
- L163 _protected member_ `bool bMakeSingleBlob = false;` — Make single BlobObj on finalise
- L164 _protected member_ `std::weak_ptr<TiledBlob_Promise> CachedBlob;` — The cached blob that this is derived off
- L166 _protected prototype_ `virtual void OnFinaliseInternal(BlobReadyCallback Callback) const override;`
- L167 _protected prototype_ `TiledBlob_Promise& operator = (const TiledBlob_Promise& RHS);`
- L168 _protected prototype_ `TiledBlob_Promise& operator = (const TiledBlob& RHS);`
- L169 _protected prototype_ `virtual void NotifyCallbacks();`
- L171 _protected prototype_ `virtual void AddLinkedBlob(BlobPtr LinkedBlob) override;`
- L172 _protected prototype_ `virtual void FinaliseFrom(Blob* RHS) override;`
- L175 _public prototype_ `TiledBlob_Promise(TiledBlobPtr Source);`
- L176 _public prototype_ `TiledBlob_Promise(const BufferDescriptor& Desc, size_t NumTilesX, size_t NumTilesY, CHashPtr HashValue);`
- L177 _public prototype_ `TiledBlob_Promise(DeviceBufferRef Buffer);`
- L178 _public prototype_ `virtual ~TiledBlob_Promise();`
- L180 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L181 _public prototype_ `virtual AsyncBufferResultPtr Unbind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L182 _public prototype_ `virtual AsyncBufferResultPtr Flush(const ResourceBindInfo& BindInfo) override;`
- L183 _public function_ `virtual bool IsFinalised() const override`
- L184 _public prototype_ `virtual void SetTile(int32 RowId, int32 ColId, BlobRef Tile) override;`
- L185 _public prototype_ `virtual AsyncBufferResultPtr MakeSingleBlob() override;`
- L186 _public prototype_ `virtual void CopyResolveLateBound(BlobPtr RHS) override;`
- L187 _public function_ `virtual bool IsPromise() const override`
- L189 _public prototype_ `virtual void FinaliseNow(bool bNoCalcHash, CHashPtr FixedHash) override;`
- L190 _public prototype_ `virtual AsyncBufferResultPtr Finalise(bool bNoCalcHash, CHashPtr FixedHash) override;`
- L191 _public prototype_ `void FinaliseFrom(TiledBlobPtr RHS);`
- L193 _public prototype_ `void ResetForReplay();` — For debug purpose, reset the state of the tile as a promise to NOT finalised, increment the replayCount
- L196 _public function_ `FORCEINLINE bool IsSingleBlob() const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L10 _typedef_ `typedef std::weak_ptr<Job> JobPtrW;`
- L11 _typedef_ `typedef T_BlobRef<Blob> BlobRef;`
- L12 _typedef_ `typedef T_Tiles<BlobPtr> BlobPtrTiles;`
- L149 _typedef_ `typedef std::shared_ptr<TiledBlob> TiledBlobPtr;`
- L150 _typedef_ `typedef std::unique_ptr<TiledBlob> TiledBlobUPtr;`
- L151 _typedef_ `typedef std::weak_ptr<TiledBlob> TiledBlobPtrW;`
- L199 _typedef_ `typedef std::shared_ptr<TiledBlob_Promise> TiledBlob_PromisePtr;`
- L200 _typedef_ `typedef std::weak_ptr<TiledBlob_Promise> TiledBlob_PromisePtrW;`
- L201 _typedef_ `typedef T_BlobRef<TiledBlob> TiledBlobRef;`
- L202 _typedef_ `typedef cti::continuable<TiledBlobRef> AsyncTiledBlobRef;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/CL/Device_CL.h` (Other)


#### class `Device_CL`  
`class Device_CL`  
_L11-23_
- L14 _public prototype_ `Device_CL();`
- L15 _public prototype_ `virtual ~Device_CL();`
- L17 _public function_ `virtual const char* Name() const`
- L22 _public prototype_ `static Device_CL* Get();`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Device.h` (Other)


#### struct `CombineSplitArgs`  
`struct CombineSplitArgs`  
_L37-43_
- L39 _public member_ `DeviceBufferRef Buffer;` — Main buffer that should be used for combining to or split from
- L40 _public member_ `const T_Tiles<DeviceBufferRef>& Tiles;` — Tiles that needs to be merged or split
- L41 _public member_ `bool IsArray = false;` — if operating buffer should be treated as Array
- L42 _public member_ `CHashPtr BufferHash;` — Precalculated buffer hash that might be available. Otherwise nullptr

#### class `Device`  
`class Device`  
_L49-251_
- L56 _public prototype_ `DECLARE_EVENT(Device, Event_ResourceUpdate);`
- L58 _public member_ `Event_ResourceUpdate ResourceUpdateEvent;` — Triggered when history is updated
- L60 _public prototype_ `static FString DeviceType_Names(DeviceType DevType);`
- L62 _public typedef_ `typedef BinCache<HashType, DeviceBufferPtrW> BufferCache;`
- L63 _public typedef_ `typedef std::vector<DeviceBuffer*> DeviceBufferPList;`
- L64 _public typedef_ `typedef std::vector<DeviceNativeTaskPtr> DeviceNativeTaskPtrVec;`
- L65 _public typedef_ `typedef std::vector<DeviceNativeTaskPtrW> DeviceNativeTaskPtrWVec;`
- L70 _protected member_ `static const double PrintStatsInterval;` — Print stats every <this many> milliseconds
- L71 _protected member_ `static const double DefaultBufferTransferInternal;` — Buffer transfers are updated every few milliseconds represented by this variable
- L73 _protected member_ `static const float DefaultMaxCacheConsumptionBeforeCollection;`
- L74 _protected member_ `static const float DefaultMinCacheConsumptionBeforeCollection;`
- L75 _protected member_ `static const uint64 DefaultMaxBatchDeltaDefault;`
- L76 _protected member_ `static const double DefaultMinLastUsageDuration;`
- L79 _protected member_ `float MaxCacheConsumptionBeforeCollection = DefaultMaxCacheConsumptionBeforeCollection;`
- L83 _protected member_ `float MinCacheConsumptionBeforeCollection = DefaultMinCacheConsumptionBeforeCollection;`
- L87 _protected member_ `uint64 MaxBatchDeltaDefault = DefaultMaxBatchDeltaDefault;` — Maximum batch delta allow before we start collecting the device
- L88 _protected member_ `double MinLastUsageDuration = DefaultMinLastUsageDuration;` — A DeviceBuffer must NOT have been used for a certain time before it can be collected
- L92 _protected member_ `BufferCache Cache;` — The buffer cache
- L94 _protected member_ `DeviceBufferPList GCTargets;` — Items that are prime targets for garbage collection
- L95 _protected member_ `mutable FCriticalSection GCTargetsLock;` — Lock for GCTargets
- L97 _protected member_ `size_t MaxMemory = 0;` — The max memory available to us
- L98 _protected member_ `size_t MaxThreads = 1;` — Max concurrent threads
- L99 _protected member_ `DeviceType Type = DeviceType::Count;` — What is the type of this device
- L100 _protected member_ `DeviceBuffer* BufferFactory = nullptr;` — The device buffer factory
- L101 _protected member_ `double TimeStatsPrinted = 0;` — The last time when stats were printed
- L102 _protected member_ `bool ShouldPrintStats = false;` — Whether to print stats all all
- L104 _protected member_ `size_t MemUsed = 0;` — How much main memory are we using
- L105 _protected member_ `size_t MemUsedNative = 0;` — How much native memory are we using (this EXCLUDES main memory so that its counted twice)
- L107 _protected member_ `mutable FCriticalSection NativeTaskLock;` — Lock for _nativeTasks vector
- L108 _protected member_ `DeviceNativeTask_PriorityQueueStrong NativeTasks;` — The tasks that are queued up to be executed over here
- L109 _protected member_ `DeviceNativeTaskPtrVec FinishedNativeTasks;` — The tasks that are finished. We clear this queue on the game thread
- L111 _protected member_ `DeviceNativeTaskPtr CurrentWaitTask;` — The task that we're currently waiting on (for debugging purposes only)
- L113 _protected member_ `std::atomic_bool ShouldTerminate = false;` — Whether the device is getting terminated or not
- L115 _protected member_ `DeviceNativeTask_PriorityQueue NativePreExecWait;` — Tasks queued in the pre-exec queue. This runs in a separate thread and makes sure that
- L118 _protected member_ `DeviceNativeTask_PriorityQueue NativePreExec;` — Tasks queued in the pre-exec queue. These are executed on the game thread
- L119 _protected member_ `std::unique_ptr<std::thread> PreExecThread = nullptr;` — Thread running pre-exec
- L120 _protected member_ `size_t PreExecThreadId = 0;` — The thread id of the pre-exec thread (used mostly for debugging and error checking)
- L123 _protected member_ `DeviceNativeTask_PriorityQueue NativeExec;` — Tasks queued in the exec queue
- L124 _protected member_ `std::unique_ptr<std::thread> ExecThread = nullptr;` — Thread running exec
- L125 _protected member_ `size_t ExecThreadId = 0;` — The thread id of the exec thread (used mostly for debugging and error checking)
- L126 _protected member_ `ENamedThreads::Type ExecThreadType = ENamedThreads::AnyBackgroundThreadNormalTask;`
- L129 _protected member_ `DeviceNativeTask_PriorityQueue NativePostExec;` — Tasks queued in the post-exec queue
- L130 _protected member_ `std::unique_ptr<std::thread> PostExecThread = nullptr;` — Thread running post-exec
- L131 _protected member_ `size_t PostExecThreadId = 0;` — The thread id of the post-exec thread (used mostly for debugging and error checking)
- L133 _protected member_ `DeviceNativeTask_PriorityQueue NonAsyncPostExecQueue;` — Non asynchronous post-exec tasks are queued here
- L134 _protected member_ `DeviceObserverSourcePtr ObserverSource;` — Device observer source that sends of different events happening within the device
- L136 _protected member_ `mutable std::mutex AwaitingCollectionMutex;` — Mutex for the list below
- L137 _protected member_ `DeviceBufferPList AwaitingCollection;` — Device buffers that are awaiting collection
- L139 _protected prototype_ `virtual void UpdateAwaitingCollection();`
- L140 _protected prototype_ `virtual void UpdateNonAsyncPostExec();`
- L141 _protected prototype_ `virtual void UpdateNonAsync();`
- L143 _protected prototype_ `Device(DeviceType InType, DeviceBuffer* InBufferFactory);`
- L144 _protected prototype_ `virtual ~Device();`
- L149 _protected prototype_ `virtual AsyncBool WaitForQueuedTasks(ENamedThreads::Type ReturnThread = ENamedThreads::UnusedAnchor);` — Method to wait for all the queued tasks. Can be extremely slow and should not be used outside of tests
- L150 _protected prototype_ `virtual void CallDeviceUpdate();`
- L151 _protected prototype_ `virtual void GarbageCollect();`
- L153 _protected prototype_ `virtual void UpdatePreExec();`
- L155 _protected prototype_ `virtual bool ShouldCollect(double TimeNow, DeviceBuffer* Buffer);`
- L156 _protected prototype_ `virtual AsyncJobResultPtr UpdateDeviceTransfers();`
- L160 _public prototype_ `static void CollectBuffer(DeviceBuffer* Buffer);`
- L163 _protected prototype_ `virtual void Collect(DeviceBuffer* Buffer);`
- L165 _protected prototype_ `DeviceBufferRef AddNewRef_Internal(DeviceBuffer* Buffer);`
- L166 _protected prototype_ `virtual DeviceBufferRef AddInternal(DeviceBufferRef& Buffer);`
- L167 _protected prototype_ `virtual void RemoveInternal(DeviceBuffer* Buffer);`
- L168 _protected prototype_ `virtual void Touch(HashType Hash);`
- L169 _protected prototype_ `virtual void PrintStats();`
- L171 _protected prototype_ `virtual void Terminate();`
- L173 _protected prototype_ `virtual void UpdateNative();`
- L174 _protected prototype_ `virtual void PreExecThreadFunc();`
- L175 _protected prototype_ `virtual void ExecThreadFunc();`
- L176 _protected prototype_ `virtual void PostExecThreadFunc();`
- L177 _protected prototype_ `virtual void MarkTaskFinished(DeviceNativeTaskPtr& Task, bool bRemoveFromOwnerQueue);`
- L190 _protected prototype_ `virtual void Free();`
- L193 _public prototype_ `virtual DeviceBufferRef Create(RawBufferPtr Raw);`
- L194 _public prototype_ `virtual DeviceBufferRef Create(BufferDescriptor Desc, CHashPtr Hash);`
- L196 _public prototype_ `virtual AsyncDeviceBufferRef CombineFromTiles(const CombineSplitArgs& CombineArgs);`
- L197 _public prototype_ `virtual AsyncDeviceBufferRef SplitToTiles(const CombineSplitArgs& SplitArgs);`
- L201 _public prototype_ `virtual cti::continuable<int32> Use() const;` — Acquire the device for use
- L203 _public prototype_ `virtual size_t GetMaxMemory() const;`
- L204 _public prototype_ `virtual size_t GetMaxThreads() const;`
- L206 _public prototype_ `virtual DeviceBufferRef CreateCompatible_Copy(DeviceBufferRef source);`
- L207 _public prototype_ `virtual AsyncDeviceBufferRef Transfer(DeviceBufferRef source);`
- L208 _public prototype_ `virtual DeviceBufferRef Find(HashType Hash, bool Touch);`
- L209 _public prototype_ `virtual void Update(float dt);`
- L210 _public prototype_ `virtual AsyncJobResultPtr UpdateIdle();`
- L212 _public function_ `virtual FString Name() const`
- L215 _public prototype_ `virtual void AddNativeTask(DeviceNativeTaskPtr Task);` — Adds a new task to the _nativeTasks vector. Thread-safe
- L217 _public prototype_ `virtual void TransferAborted(DeviceBufferRef Buffer);`
- L219 _public typedef_ `using Visitor = std::function<void (const std::shared_ptr<DeviceBuffer>&, uint32)>;` — Visitor callable receiving the bufferDevice visited and the index in the lru Cache
- L220 _public prototype_ `uint32 TraverseBufferCache(Visitor visitor);`
- L222 _public prototype_ `void RegisterObserverSource(const DeviceObserverSourcePtr& observerSource);`
- L223 _public prototype_ `bool CanFree() const;`
- L224 _public prototype_ `virtual void ClearCache();`
- L229 _public function_ `FORCEINLINE bool IsMultithreaded() const`
- L230 _public function_ `FORCEINLINE bool GetShouldPrintStats() const`
- L231 _public function_ `FORCEINLINE void SetShouldPrintStats(bool Value)`
- L232 _public function_ `FORCEINLINE DeviceType GetType() const`
- L233 _public function_ `FORCEINLINE uint64 GetMemUsed() const`
- L234 _public function_ `FORCEINLINE uint64 GetNumDeviceBuffersUsed() const`
- L235 _public function_ `FORCEINLINE uint64 GetNumDeviceBuffersMax() const`
- L237 _public function_ `FORCEINLINE DeviceObserverSourcePtr GetObserverSource() const`
- L238 _public function_ `FORCEINLINE size_t GetPreExecThreadId() const`
- L239 _public function_ `FORCEINLINE size_t GetExecThreadId() const`
- L240 _public function_ `FORCEINLINE size_t GetPostExecThreadId() const`
- L245 _public prototype_ `static AsyncDeviceBufferRef SplitToTiles_Generic(const CombineSplitArgs& splitArgs);`
- L250 _public function_ `FORCEINLINE Event_ResourceUpdate& E_ResourceUpdate()`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L22 _typedef_ `typedef std::shared_ptr<DeviceNativeTask> DeviceNativeTaskPtr;`
- L23 _typedef_ `typedef std::weak_ptr<DeviceNativeTask> DeviceNativeTaskPtrW;`
- L26 _typedef_ `typedef std::shared_ptr<JobResult> JobResultPtr;`
- L27 _typedef_ `typedef cti::continuable<JobResultPtr> AsyncJobResultPtr;`
- L30 _typedef_ `typedef std::shared_ptr<DeviceObserverSource> DeviceObserverSourcePtr;`
- L32 _typedef_ `using AsyncBool = cti::continuable<bool>;`
- L34 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDevice, Log, Verbose);`
- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDevice, Log, Verbose);`
- L56 _delegate_ `DECLARE_EVENT(Device, Event_ResourceUpdate);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/DeviceBuffer.h` (Other)


#### struct `BufferResult`  
`struct BufferResult`  
_L18-22_
- L20 _public member_ `std::exception_ptr ExInner;` — Original exception that was raised by the action
- L21 _public member_ `int32 ErrorCode = 0;` — What is the error code

#### class `DeviceBuffer`  
`class DeviceBuffer : public G_Collectible`  
_L40-148_
- inherits: `G_Collectible`
- L47 _public member_ `static const DeviceTransferChain DefaultTransferChain;` — Default transfer Chain
- L48 _public member_ `static const DeviceTransferChain FXOnlyTransferChain;` — Only exist on the FX device
- L49 _public member_ `static const DeviceTransferChain PersistentTransferChain;` — Persistent
- L53 _protected member_ `Device* OwnerDevice = nullptr;` — The device that this belongs to
- L54 _protected member_ `BufferDescriptor Desc;` — The descriptor for this buffer
- L56 _protected member_ `mutable CHashPtr HashValue;` — The actual RawObj buffer HashValue
- L57 _protected member_ `RawBufferPtr RawData;` — Raw buffer pointer that we keep cached (If we happen to have it)
- L58 _protected member_ `bool FetchingRaw = false;` — Whether we're already fetching raw or not
- L60 _protected member_ `bool bMarkedForCollection = false;` — Whether this instance is marked for collection or not
- L61 _protected member_ `bool bIsPersistent = false;` — Whether this is persistent or not
- L62 _protected member_ `bool Chain[static_cast<int32>(DeviceType::Count)] = {false};` — Device transfer Chain
- L64 _protected prototype_ `virtual CHashPtr CalcHash();`
- L67 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr RawObj) = 0;` — Only accessible from Device. Should not be used elsewhere
- L68 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor Desc, CHashPtr HashValue) = 0;`
- L69 _protected prototype_ `virtual DeviceBuffer* CopyFrom(DeviceBuffer* RHS);`
- L70 _protected prototype_ `virtual DeviceBuffer* Clone();`
- L74 _protected prototype_ `virtual AsyncBufferResultPtr UpdateRaw(RawBufferPtr RawObj);` — DO NOT MAKE THIS METHOD PUBLIC! Its not meant to be accessible outside
- L77 _protected prototype_ `virtual void ReleaseNative();` — To be called from the Device owner only!
- L79 _protected prototype_ `virtual void Touch(uint64 BatchId);`
- L81 _protected function_ `FORCEINLINE void MarkForCollection()`
- L84 _public prototype_ `DeviceBuffer(Device* Dev, BufferDescriptor NewDesc, CHashPtr NewHash);`
- L85 _public prototype_ `DeviceBuffer(Device* Dev, RawBufferPtr RawObj);`
- L86 _public prototype_ `DeviceBuffer(const DeviceBuffer& RHS) = delete;` — non-copyable
- L99 _public prototype_ `virtual RawBufferPtr Raw_Now() = 0;` — SLOW: Read above
- L100 _public prototype_ `virtual AsyncRawBufferPtr Raw();` — SLOW: Read above [use Blob::Raw instead. This is to be used from Blob only]
- L102 _public prototype_ `AsyncRawBufferPtr GetRawOrMaketIt();`
- L105 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& Source) = 0;`
- L110 _public prototype_ `virtual size_t MemSize() const = 0;`
- L111 _public function_ `virtual size_t DeviceNative_MemSize() const`
- L113 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) = 0;`
- L114 _public prototype_ `virtual AsyncBufferResultPtr Unbind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo);`
- L116 _public prototype_ `virtual AsyncBufferResultPtr Flush(const ResourceBindInfo& BindInfo);`
- L117 _public prototype_ `virtual bool IsValid() const;`
- L118 _public prototype_ `virtual bool IsNull() const;`
- L121 _public prototype_ `virtual CHashPtr Hash(bool Calculate = true);` — With base implementations
- L122 _public prototype_ `virtual bool IsCompatible(Device* Dev) const;`
- L124 _public function_ `virtual RawBufferPtr Min()`
- L125 _public function_ `virtual RawBufferPtr Max()`
- L127 _public prototype_ `virtual void SetHash(CHashPtr NewHash);`
- L128 _public prototype_ `virtual AsyncPrepareResult PrepareForWrite(const ResourceBindInfo& BindInfo);`
- L130 _public prototype_ `void SetDeviceTransferChain(const DeviceTransferChain& Chain, bool bPersistent = false);`
- L131 _public prototype_ `DeviceTransferChain GetDeviceTransferChain(bool* Persistent = nullptr) const;`
- L132 _public prototype_ `virtual Device* GetDowngradeDevice() const;`
- L133 _public prototype_ `virtual Device* GetUpgradeDevice() const;`
- L134 _public prototype_ `virtual bool IsTransient() const;`
- L139 _public function_ `FORCEINLINE Device* GetOwnerDevice() const`
- L141 _public function_ `BufferDescriptor& Descriptor() const`
- L142 _public function_ `FORCEINLINE FString& GetName()`
- L143 _public function_ `FORCEINLINE bool HasRaw() const`
- L145 _public function_ `FORCEINLINE const bool* TransferChain() const`
- L146 _public function_ `FORCEINLINE bool IsPersistent() const`
- L147 _public function_ `FORCEINLINE bool IsFetchingRaw() const`

#### class `DeviceBufferPtr`  
`class DeviceBufferPtr : public std::shared_ptr<DeviceBuffer>`  
_L152-160_
- inherits: `std::shared_ptr<DeviceBuffer>`
- L155 _public function_ `DeviceBufferPtr() : std::shared_ptr<DeviceBuffer>()`
- L156 _public prototype_ `DeviceBufferPtr(DeviceBuffer* buffer);`
- L157 _public prototype_ `DeviceBufferPtr(const DeviceBufferPtr& RHS);`
- L158 _public prototype_ `DeviceBufferPtr(const std::shared_ptr<DeviceBuffer>& RHS);`
- L159 _public prototype_ `~DeviceBufferPtr();`

#### class `DeviceBufferRef`  
`class DeviceBufferRef`  
_L171-212_
- L181 _private member_ `DeviceBufferPtr Buffer;` — The buffer info pointer
- L183 _private prototype_ `void Clear();`
- L185 _public function_ `DeviceBufferRef()`
- L186 _public prototype_ `explicit DeviceBufferRef(DeviceBufferPtr RHS);`
- L187 _public prototype_ `explicit DeviceBufferRef(DeviceBuffer* RHS);`
- L189 _public prototype_ `~DeviceBufferRef();`
- L191 _public prototype_ `DeviceBufferRef& operator = (const DeviceBufferRef& RHS);`
- L193 _public prototype_ `DeviceType GetDeviceType() const;` — Need complete Device Definition so cannot be inlined here
- L199 _public function_ `FORCEINLINE bool operator == (const DeviceBufferRef& RHS) const` — FORCEINLINE DeviceBufferRef		operator = (DeviceBuffer* RHS) { _buffer = DeviceBufferPtr(RHS); }
- L200 _public function_ `FORCEINLINE bool operator == (const DeviceBuffer* RHS) const`
- L201 _public function_ `FORCEINLINE bool operator != (const DeviceBufferRef& RHS) const`
- L202 _public function_ `FORCEINLINE operator bool () const`
- L203 _public function_ `FORCEINLINE operator DeviceBufferPtr() const`
- L204 _public function_ `FORCEINLINE DeviceBuffer* operator -> () const`
- L205 _public function_ `FORCEINLINE bool IsValid() const`
- L206 _public function_ `FORCEINLINE DeviceBuffer* Get() const`
- L207 _public function_ `FORCEINLINE DeviceBufferPtr GetPtr() const`
- L210 _public function_ `FORCEINLINE DeviceBuffer* get() const` — STL compatibility
- L211 _public function_ `FORCEINLINE void reset()` — Compaibility with std::shared_ptr

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L26 _typedef_ `typedef std::shared_ptr<BufferResult> BufferResultPtr;`
- L27 _typedef_ `typedef cti::continuable<BufferResultPtr> AsyncBufferResultPtr;`
- L28 _typedef_ `typedef std::function<void(BufferResultPtr)> BufferResult_Callback;`
- L29 _typedef_ `typedef cti::continuable<int32> AsyncPrepareResult;`
- L33 _typedef_ `typedef std::vector<DeviceType> DeviceTransferChain;`
- L36 _typedef_ `typedef std::shared_ptr<DeviceNativeTask> DeviceNativeTaskPtr;`
- L37 _typedef_ `typedef std::vector<DeviceNativeTaskPtr> DeviceNativeTaskPtrVec;`
- L162 _typedef_ `typedef std::weak_ptr<DeviceBuffer> DeviceBufferPtrW;`
- L214 _typedef_ `typedef cti::continuable<DeviceBufferRef> AsyncDeviceBufferRef;`
- L215 _typedef_ `typedef std::function<void(DeviceBufferRef)> DeviceBufferRef_Callback;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/DeviceManager.h` (Other)


#### class `DeviceManager`  
`class DeviceManager`  
_L17-40_
- L20 _private member_ `Device* Devices[(size_t)DeviceType::Count] = {};` — The devices available within the system
- L21 _private member_ `Device_Mem* DefaultDevice = nullptr;` — What is the default device on the system. This is always the CPU device
- L23 _private prototype_ `void InitDevices();`
- L24 _private prototype_ `void ReleaseDevices();`
- L27 _public prototype_ `DeviceManager();`
- L28 _public prototype_ `virtual ~DeviceManager();`
- L30 _public prototype_ `void Update(float dt);`
- L31 _public prototype_ `AsyncBool WaitForQueuedTasks(ENamedThreads::Type returnThread = ENamedThreads::UnusedAnchor);`
- L32 _public prototype_ `Device* GetDevice(DeviceType type) const;`
- L33 _public prototype_ `Device* GetDevice(size_t Index) const;`
- L38 _public function_ `FORCEINLINE size_t GetNumDevices() const`
- L39 _public function_ `FORCEINLINE Device_Mem* GetDefaultDevice() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `using AsyncBool = cti::continuable<bool>;`
- L42 _typedef_ `typedef std::unique_ptr<DeviceManager> DeviceManagerPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/DeviceNativeTask.h` (Other)


#### class `DeviceNativeTask`  
`class DeviceNativeTask`  
_L26-122_
- L29 _private member_ `static std::atomic<int64_t> GTaskId;` — Task ID
- L30 _private prototype_ `static int64_t GetNewTaskId();`
- L32 _private member_ `std::promise<int32> Promise;` — Our promise
- L33 _private member_ `std::shared_future<int32> Future;` — The future for our promise
- L36 _protected member_ `DeviceNativeTaskPtrVec Prev;` — The previous Tasks that this is dependent on
- L37 _protected member_ `std::atomic<bool> bTerminate = false;` — Terminate this process
- L38 _protected member_ `size_t ThreadId = 0;` — What is the actual thread ID
- L39 _protected member_ `int64_t TaskId;` — The ID of the Task
- L40 _protected member_ `int32 Priority;` — The TaskPriority of the job. Must be in range [E_Priority::kHighest, E_Priority::kLowest]
- L41 _protected member_ `std::atomic<int> ErrorCode = 0;` — The error code for this native Task. This will be set in PostExec.
- L44 _protected member_ `FString Name;` — The TaskName of this DeviceNativeTask
- L46 _protected member_ `bool bExecOnly = false;` — Whether its an exec only Task with no pre and post exec. This is to avoid waiting for system Tasks
- L47 _protected member_ `bool bIsCulled = false;` — Whether the Task is culled or not
- L48 _protected member_ `bool bIsDone = false;` — Whether the Task is done or not
- L49 _protected member_ `bool bIsAsync = true;` — Whether the native task is async or not
- L51 _protected member_ `int64_t BatchId = 0;` — What's the batch id of this native Task
- L53 _protected prototype_ `void Reset();`
- L54 _protected prototype_ `void WaitSelf();`
- L55 _protected prototype_ `bool WaitSelfFor(int32 Seconds);`
- L57 _protected prototype_ `void SetPromise(int32 Value);`
- L58 _protected prototype_ `FString DebugWaitChain();`
- L60 _protected prototype_ `virtual cti::continuable<int32> GenericExecAsync(ENamedThreads::Type CallingThread, ENamedThreads::Type ReturnThread);`
- L62 _protected prototype_ `void AdjustPrevPriority(DeviceNativeTask* Ref, DeviceNativeTask* Parent);`
- L63 _protected prototype_ `void AdjustPrevPriority(DeviceNativeTask* Ref, DeviceNativeTask* Parent, DeviceNativeTask* PrevDeps);`
- L64 _protected prototype_ `virtual void SetPriority(DeviceNativeTask* Ref);`
- L67 _public prototype_ `DeviceNativeTask(int32 TaskPriority, FString TaskName);`
- L68 _public prototype_ `DeviceNativeTask(DeviceNativeTaskPtrVec& PrevTasks, int32 TaskPriority, FString TaskName);`
- L69 _public prototype_ `virtual ~DeviceNativeTask();`
- L71 _public prototype_ `virtual bool WaitFor(int32 Seconds);`
- L72 _public prototype_ `virtual void Wait();`
- L73 _public prototype_ `virtual cti::continuable<int32> PreExecAsync(ENamedThreads::Type CallingThread, ENamedThreads::Type ReturnThread);`
- L74 _public prototype_ `virtual void PreExec();`
- L75 _public prototype_ `virtual int32 Exec() = 0;`
- L76 _public prototype_ `virtual cti::continuable<int32> ExecAsync(ENamedThreads::Type CallingThread, ENamedThreads::Type ReturnThread);`
- L77 _public prototype_ `virtual void PostExec();`
- L78 _public prototype_ `virtual cti::continuable<int32> WaitAsync(ENamedThreads::Type ReturnThread = ENamedThreads::UnusedAnchor);`
- L80 _public prototype_ `virtual Device* GetTargetDevice() const = 0;`
- L83 _public prototype_ `void CheckQueued(DeviceNativeTask* Ref);`
- L84 _public prototype_ `void DebugVerifyDepsQueued(const DeviceNativeTaskPtrVec& Queue, const DeviceNativeTaskPtrVec& AllItems);`
- L87 _public prototype_ `void FixPriorities();`
- L91 _public prototype_ `virtual ENamedThreads::Type GetExecutionThread() const;` — Waits for the _prev Task to finish before executing. Its the responsibility of the system to ensure that both the _prev
- L92 _public prototype_ `virtual FString GetName() const;`
- L93 _public prototype_ `virtual FString GetDebugName() const;`
- L94 _public prototype_ `virtual void Terminate();`
- L96 _public prototype_ `virtual void AddPrev(DeviceNativeTaskPtr PrevTasks);`
- L97 _public prototype_ `virtual void AddPrev(const DeviceNativeTaskPtrVec& Tasks);`
- L98 _public prototype_ `virtual void SetPrev(const DeviceNativeTaskPtrVec& PrevTasks);`
- L99 _public prototype_ `virtual void SetPriority(int32 TaskPriority, bool AdjustPrev);`
- L100 _public prototype_ `bool IsHigherPriorityThan(const DeviceNativeTask& RHS) const;`
- L102 _public prototype_ `void CheckCyclicalDependency(std::unordered_set<DeviceNativeTask*>& TransferChain);`
- L103 _public prototype_ `virtual bool DebugCompleteCheck();`
- L104 _public function_ `virtual bool IsAsync() const`
- L109 _public function_ `FORCEINLINE std::shared_future<int32> GetFuture()`
- L110 _public function_ `FORCEINLINE size_t GetActualThreadId() const`
- L111 _public function_ `FORCEINLINE int64_t GetTaskId() const`
- L112 _public function_ `FORCEINLINE int64_t GetBatchId() const`
- L113 _public function_ `FORCEINLINE void SetBatchId(int64_t NewBatchId)`
- L114 _public function_ `FORCEINLINE int32 GetPriority() const`
- L115 _public function_ `FORCEINLINE bool operator < (const DeviceNativeTask& RHS) const`
- L116 _public function_ `FORCEINLINE bool IsExecOnly() const`
- L117 _public function_ `FORCEINLINE bool IsCulled() const`
- L118 _public function_ `FORCEINLINE bool IsDone() const`
- L119 _public function_ `FORCEINLINE void SetIsAsync(bool bIsAsyncIn)`
- L120 _public function_ `FORCEINLINE const DeviceNativeTaskPtrVec& GetPrev() const`
- L121 _public function_ `FORCEINLINE bool IsTerminated() const`

#### class `DeviceNativeTask_Generic`  
`class DeviceNativeTask_Generic : public DeviceNativeTask`  
_L131-155_
- inherits: `DeviceNativeTask`
- L136 _protected member_ `Device* Dev = nullptr;` — The target device that this is associated with
- L137 _protected member_ `ENamedThreads::Type ThreadId = ENamedThreads::AnyThread;` — What thread is this going to run on
- L140 _public prototype_ `DeviceNativeTask_Generic(Device* TargetDevice, FString TaskName, ENamedThreads::Type TaskThreadId = ENamedThreads::AnyThread, bool IsTaskAsync = false, int32 TaskPriority = (int32)E_Priority::kNormal);`
- L142 _public prototype_ `DeviceNativeTask_Generic(DeviceNativeTaskPtrVec& PrevDeps, Device* TargetDevice, FString TaskName, ENamedThreads::Type TaskThreadId = ENamedThreads::AnyThread, bool IsTAskAsync = false, int32 TaskPriority = (int32)E_Priority::kNormal);`
- L145 _public function_ `virtual Device* GetTargetDevice() const override`
- L149 _public function_ `virtual ENamedThreads::Type GetExecutionThread() const override` — Waits for the _prev Task to finish before executing. Its the responsibility of the system to ensure that both the _prev
- L154 _public function_ `FORCEINLINE ENamedThreads::Type& GetThreadId()`

#### class `DeviceNativeTask_Lambda`  
`class DeviceNativeTask_Lambda : public DeviceNativeTask_Generic`  
_L159-178_
- inherits: `DeviceNativeTask_Generic`
- L162 _protected member_ `DeviceNativeTask_Lambda_Func Callback = nullptr;` — The lambda callback
- L164 _protected prototype_ `virtual int32 Exec() override;`
- L167 _public prototype_ `DeviceNativeTask_Lambda(DeviceNativeTask_Lambda_Func LambdaCallback, Device* Dev, FString TaskName, ENamedThreads::Type TaskThreadId = ENamedThreads::AnyThread, bool IsTaskAsync = false, int32 TaskPriority = (int32)E_Priority::kNormal);`
- L173 _public prototype_ `static std::shared_ptr<DeviceNativeTask> Create(Device* device, int32 TaskPriority, FString TaskName, DeviceNativeTask_Lambda_Func callback);`
- L174 _public prototype_ `static std::shared_ptr<DeviceNativeTask> Create(Device* device, ENamedThreads::Type threadId, bool isAsync, int32 TaskPriority, FString TaskName, DeviceNativeTask_Lambda_Func callback);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `typedef cti::continuable<DeviceNativeTask> AsyncDeviceNativeTask;`
- L16 _typedef_ `typedef cti::continuable<DeviceNativeTask*> AsyncDeviceNativeTaskP;`
- L17 _typedef_ `typedef std::shared_ptr<DeviceNativeTask> DeviceNativeTaskPtr;`
- L18 _typedef_ `typedef std::vector<DeviceNativeTaskPtr> DeviceNativeTaskPtrVec;`
- L20 _macro_ `#define DEVICE_NATIVE_TASKS_CHECK_CYCLES 0`
- L158 _typedef_ `typedef TFunction<int32()> DeviceNativeTask_Lambda_Func;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/DeviceObserverSource.h` (Other)


#### class `DeviceObserverSource`  
`class DeviceObserverSource`  
_L23-59_
- L31 _public typedef_ `using HashNDescArray = std::vector<HashNDesc>;`
- L32 _public typedef_ `using HashArray = std::vector<HashType>;`
- L34 _public prototype_ `void AddBuffer(const DeviceBuffer* Buffer, HashType Hash, const BufferDescriptor& Desc);`
- L35 _public prototype_ `void RemoveBuffer(const DeviceBuffer* buffer, HashType hash, HashType prevHash);`
- L41 _protected member_ `FCriticalSection ObserverLock;`
- L43 _protected member_ `HashNDescArray AddedBufferStack;`
- L44 _protected member_ `HashArray RemovedBufferStack;`
- L46 _protected member_ `uint32 Version = 1;`
- L49 _protected prototype_ `void Broadcast();` — Trigger the broadcast of the changes, this call is issued from the Device::Update function
- L52 _protected function_ `virtual void DeviceBuffersUpdated(HashNDescArray&& AddedBuffers, HashArray&& RemovedBuffers)` — The customisable handler method triggered from Broadcast if any buffers were added or removed
- L55 _public prototype_ `DeviceObserverSource() = default;`
- L56 _public prototype_ `virtual ~DeviceObserverSource() = default;`
- L58 _public function_ `uint32 GetVersion() const` — THe version of the current state of the Device Cache. Incremented when Broadcast trigger

#### struct `DeviceObserverSource::HashNDesc`  
`struct HashNDesc`  
_L26-30_
- L27 _public member_ `uint64 Raw = 0;`
- L28 _public member_ `HashType First = 0;`
- L29 _public member_ `BufferDescriptor Second;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `typedef std::shared_ptr<DeviceNativeTask> DeviceNativeTaskPtr;`
- L16 _typedef_ `typedef std::weak_ptr<DeviceNativeTask> DeviceNativeTaskPtrW;`
- L19 _typedef_ `typedef std::shared_ptr<JobResult> JobResultPtr;`
- L20 _typedef_ `typedef cti::continuable<JobResultPtr> AsyncJobResultPtr;`
- L60 _typedef_ `typedef std::shared_ptr<DeviceObserverSource> DeviceObserverSourcePtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/DeviceType.h` (Other)


#### enum `DeviceType`  
`enum class DeviceType`  
_L6-18_
- L8 _public enumerator_ `FX`
- L9 _public enumerator_ `OpenCL`
- L10 _public enumerator_ `Mem`
- L11 _public enumerator_ `MemCompressed`
- L12 _public enumerator_ `Disk`
- L13 _public enumerator_ `Remote`
- L15 _public enumerator_ `Null`
- L17 _public enumerator_ `Count`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Disk/DeviceBuffer_Disk.h` (Other)


#### class `DeviceBuffer_Disk`  
`class DeviceBuffer_Disk : public DeviceBuffer`  
_L17-46_
- inherits: `DeviceBuffer`
- L20 _protected member_ `RawBufferPtr RawObj;` — The underlying raw buffer
- L22 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr NewRawObj) override;`
- L23 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor NewDesc, CHashPtr NewHashValue) override;`
- L25 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& Source) override;`
- L28 _public prototype_ `DeviceBuffer_Disk(Device_Disk* Dev, BufferDescriptor Desc, CHashPtr HashValue);`
- L29 _public prototype_ `DeviceBuffer_Disk(Device_Disk* Dev, RawBufferPtr RawObj);`
- L35 _public prototype_ `virtual RawBufferPtr Raw_Now() override;`
- L36 _public prototype_ `virtual size_t MemSize() const override;`
- L37 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L41 _public prototype_ `virtual bool IsCompatible(Device* Dev) const override;` — With base implementations virtual void					Release() override;

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Disk/Device_Disk.h` (Other)


#### class `Device_Disk`  
`class Device_Disk : public Device_Mem`  
_L9-32_
- inherits: `Device_Mem`
- L12 _protected member_ `FString BaseDir;` — The base directory for
- L15 _public prototype_ `Device_Disk();`
- L18 _public function_ `virtual FString Name() const override`
- L19 _public prototype_ `virtual void Update(float Delta) override;`
- L20 _public prototype_ `virtual FString SetBaseDirectory(const FString& InBaseDir, bool MigrateExisting = true);`
- L21 _public prototype_ `FString GetCacheFilename(HashType HashValue) const;`
- L26 _public prototype_ `static Device_Disk* Get();`
- L31 _public function_ `FORCEINLINE const FString& GetBaseDirectory() const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/FX/DeviceBuffer_FX.h` (Other)


#### class `DeviceBuffer_FX`  
`class DeviceBuffer_FX : public DeviceBuffer`  
_L15-59_
- inherits: `DeviceBuffer`
- L19 _protected member_ `TexPtr Texture;` — The underlying texture object
- L21 _protected prototype_ `AsyncBufferResultPtr AllocateTexture();`
- L22 _protected prototype_ `AsyncBufferResultPtr AllocateRenderTarget();`
- L23 _protected prototype_ `void UpdateRenderTarget(TexPtr TextureObj);`
- L25 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr RawObj) override;`
- L26 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor NewDesc, CHashPtr NewHashValue) override;`
- L27 _protected prototype_ `virtual DeviceBuffer* CopyFrom(DeviceBuffer* RHS) override;`
- L28 _protected prototype_ `virtual AsyncBufferResultPtr UpdateRaw(RawBufferPtr RawObj) override;`
- L30 _protected prototype_ `virtual CHashPtr CalcHash() override;`
- L32 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& Source) override;`
- L35 _public prototype_ `DeviceBuffer_FX(Device_FX* Dev, BufferDescriptor Desc, CHashPtr NewHashValue);`
- L36 _public prototype_ `DeviceBuffer_FX(Device_FX* Dev, TexPtr TextureObj, RawBufferPtr RawObj);`
- L37 _public prototype_ `DeviceBuffer_FX(Device_FX* Dev, TexPtr TextureObj, BufferDescriptor Desc, CHashPtr NewHashValue);`
- L38 _public prototype_ `DeviceBuffer_FX(Device_FX* Dev, RawBufferPtr RawObj);`
- L44 _public prototype_ `virtual RawBufferPtr Raw_Now() override;`
- L45 _public prototype_ `virtual size_t MemSize() const override;`
- L46 _public prototype_ `virtual size_t DeviceNative_MemSize() const override;`
- L47 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L48 _public prototype_ `virtual AsyncBufferResultPtr Unbind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L49 _public prototype_ `virtual AsyncBufferResultPtr Flush(const ResourceBindInfo& BindInfo) override;`
- L50 _public prototype_ `virtual AsyncPrepareResult PrepareForWrite(const ResourceBindInfo& BindInfo) override;`
- L51 _public prototype_ `virtual bool IsNull() const override;`
- L53 _public prototype_ `virtual void ReleaseNative() override;`
- L58 _public function_ `FORCEINLINE TexPtr GetTexture()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L13 _typedef_ `typedef std::shared_ptr<Tex> TexPtr;`
- L61 _typedef_ `typedef std::shared_ptr<DeviceBuffer_FX> DeviceBuffer_FXPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/FX/Device_FX.h` (Other)


#### struct `DrawTilesSettings`  
`struct DrawTilesSettings`  
_L23-27_
- L25 _public member_ `T_Tiles<FIntPoint> Position;` — The position where to put the tiles
- L26 _public member_ `T_Tiles<FIntPoint> Size;` — The size of the tiles

#### class `Device_FX`  
`class Device_FX : public Device, public FGCObject`  
_L29-119_
- inherits: `Device,FGCObject`
- L32 _private member_ `static size_t s_maxRenderBatch;`
- L34 _private typedef_ `typedef std::list<TexPtr> TextureNodeList;`
- L36 _private member_ `mutable FCriticalSection GCLock;` — Lock to the GC lists
- L37 _private member_ `TextureNodeList GCTargetTextures;` — Textures that are GC targets right now
- L39 _private typedef_ `typedef std::list<TObjectPtr<UTextureRenderTarget2D>> RTList;`
- L40 _private typedef_ `typedef std::unordered_map<HashType, RTList*> RenderTargetCache;`
- L42 _private member_ `mutable FCriticalSection GC_RTCache;` — Lock to the GC lists
- L44 _private member_ `RenderTargetCache RTCache;` — The render target cache that we are currently maintaining
- L45 _private member_ `RenderTargetCache RTArrayCache;` — The render target array cache that we are currently maintaining
- L47 _private member_ `RTList RTUsed;` — Used render targets
- L49 _private member_ `IRendererModule* RendererModule;` — Useful rendering functionalities wrapped in this module
- L51 _private prototype_ `void GCTextures();`
- L52 _private prototype_ `virtual void Free() override;`
- L53 _private prototype_ `virtual void ClearCache() override;`
- L58 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L59 _private prototype_ `virtual FString GetReferencerName() const override;`
- L61 _private prototype_ `void FreeCacheInternal(RenderTargetCache& TargetRTCache);`
- L62 _private prototype_ `void FreeRTList(RTList& RTList);`
- L63 _private prototype_ `void FreeRenderTarget(HashType HashValue, UTextureRenderTarget2D* RT);`
- L65 _private prototype_ `static UTextureRenderTarget2D* CreateRenderTarget(const BufferDescriptor& Desc);`
- L66 _private prototype_ `AsyncDeviceBufferRef SplitToTiles_Internal(const CombineSplitArgs& SplitArgs);`
- L68 _private prototype_ `int32 AllocateRTArrayResource(TexArrayPtr TexArrayObj);`
- L69 _private prototype_ `int32 AllocateRTResource(TexPtr TextureObj);`
- L70 _private prototype_ `int32 InitRTResource(TexPtr TextureObj, UTextureRenderTarget* RT);`
- L73 _protected prototype_ `virtual void PrintStats() override;`
- L76 _public prototype_ `Device_FX();`
- L79 _public prototype_ `virtual cti::continuable<int32> Use() const override;`
- L80 _public prototype_ `void GetStatArray(TArray<FString>& ResourceArrayTiled, TArray<FString>& ResourceArrayUnTiled, TArray<FString>& TooltipListTiled, TArray<FString>& TooltipListUnTiled, FString& TotalStats);`
- L82 _public prototype_ `DeviceBufferRef CreateFromRT(UTextureRenderTarget2D* RT, const BufferDescriptor& Desc);` — Must be called from the rendering thread
- L83 _public prototype_ `DeviceBufferRef CreateFromTexture(UTexture2D* TextureObj, const BufferDescriptor& Desc);`
- L84 _public prototype_ `DeviceBufferRef CreateFromTex(TexPtr TextureObj, bool bInitRaw);`
- L85 _public prototype_ `DeviceBufferRef CreateFromTexAndRaw(TexPtr TextureObj, RawBufferPtr RawObj);`
- L87 _public prototype_ `virtual AsyncDeviceBufferRef CombineFromTiles(const CombineSplitArgs& CombineArgs) override;`
- L89 _public prototype_ `AsyncDeviceBufferRef DrawTilesToBuffer_Deferred(DeviceBufferRef buffer, const T_Tiles<DeviceBufferRef>& Tiles, const DrawTilesSettings* DrawSettings = nullptr, FLinearColor* ClearColor = nullptr);`
- L90 _public prototype_ `AsyncDeviceBufferRef FillTextureArray_Deferred(DeviceBufferRef buffer, const T_Tiles<DeviceBufferRef>& Tiles);`
- L92 _public prototype_ `virtual AsyncDeviceBufferRef SplitToTiles(const CombineSplitArgs& splitArgs) override;`
- L94 _public prototype_ `TexPtr AllocateRenderTarget(const BufferDescriptor& Desc);`
- L95 _public prototype_ `TexPtr AllocateRenderTargetArray(const BufferDescriptor& Desc, int32 NumTilesX, int32 NumTilesY);`
- L99 _public prototype_ `virtual void Update(float Delta) override;`
- L100 _public prototype_ `void MarkForCollection(TexPtr TextureObj);`
- L101 _public function_ `virtual FString Name() const override`
- L102 _public prototype_ `virtual void AddNativeTask(DeviceNativeTaskPtr task) override;`
- L107 _public function_ `FORCEINLINE FRHICommandListImmediate& RHI() const`
- L115 _public prototype_ `static void InitTiles_Texture(T_Tiles<BlobPtr>* Tiles, const BufferDescriptor& InTileDesc, bool bInitRaw);`
- L116 _public prototype_ `static void InitTiles_RenderTargets(BlobUPtr* Tiles, size_t NumRows, size_t NumCols, const BufferDescriptor& InTileDesc, bool bInitRaw);`
- L118 _public prototype_ `static Device_FX* Get();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L16 _typedef_ `typedef cti::continuable<TexPtr> AsyncTexPtr;`
- L18 _typedef_ `typedef std::shared_ptr<RenderMaterial_FX> RenderMaterial_FXPtr;`
- L19 _typedef_ `typedef std::shared_ptr<class TexArray> TexArrayPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Mem/DeviceBuffer_Mem.h` (Other)


#### class `DeviceBuffer_Mem`  
`class DeviceBuffer_Mem : public DeviceBuffer`  
_L17-45_
- inherits: `DeviceBuffer`
- L20 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr RawObj) override;`
- L21 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor NewDesc, CHashPtr NewHashValue) override;`
- L23 _protected prototype_ `void Allocate();`
- L24 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& Source) override;`
- L27 _public prototype_ `DeviceBuffer_Mem(Device_Mem* Device, BufferDescriptor Desc, CHashPtr HashValue);`
- L28 _public prototype_ `DeviceBuffer_Mem(Device_Mem* Device, RawBufferPtr RawObj);`
- L34 _public prototype_ `virtual RawBufferPtr Raw_Now() override;`
- L35 _public prototype_ `virtual size_t MemSize() const override;`
- L36 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L40 _public prototype_ `virtual bool IsCompatible(Device* Dev) const override;` — With base implementations virtual void					Release() override;

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Mem/Device_Mem.h` (Other)


#### class `Device_Mem`  
`class Device_Mem : public Device`  
_L9-26_
- inherits: `Device`
- L12 _protected prototype_ `Device_Mem(DeviceType Type, DeviceBuffer* BufferFactory);`
- L15 _public prototype_ `Device_Mem();`
- L18 _public function_ `virtual FString Name() const override`
- L19 _public prototype_ `virtual void Update(float Delta) override;`
- L20 _public prototype_ `virtual void AddNativeTask(DeviceNativeTaskPtr Task) override;`
- L25 _public prototype_ `static Device_Mem* Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/MemCM/DeviceBuffer_MemCM.h` (Other)


#### class `DeviceBuffer_MemCM`  
`class DeviceBuffer_MemCM : public DeviceBuffer_Mem`  
_L17-43_
- inherits: `DeviceBuffer_Mem`
- L20 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr InRawObj) override;`
- L21 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor InDesc, CHashPtr InHashValue) override;`
- L23 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& Source) override;`
- L25 _public prototype_ `DeviceBuffer_MemCM(Device_MemCM* Dev, BufferDescriptor InDesc, CHashPtr InHashValue);`
- L26 _public prototype_ `DeviceBuffer_MemCM(Device_MemCM* Dev, RawBufferPtr InRawObj);`
- L32 _public prototype_ `virtual RawBufferPtr Raw_Now() override;`
- L33 _public prototype_ `virtual size_t MemSize() const override;`
- L34 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* Transform, const ResourceBindInfo& BindInfo) override;`
- L38 _public prototype_ `virtual bool IsCompatible(Device* Dev) const override;` — With base implementations virtual void					Release() override;

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/MemCM/Device_MemCM.h` (Other)


#### class `Device_MemCM`  
`class Device_MemCM : public Device_Mem`  
_L9-22_
- inherits: `Device_Mem`
- L12 _public prototype_ `Device_MemCM();`
- L15 _public function_ `virtual FString Name() const override`
- L16 _public prototype_ `virtual void Update(float Delta) override;`
- L21 _public prototype_ `static Device_MemCM* Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Null/DeviceBuffer_Null.h` (Other)


#### class `DeviceBuffer_Null`  
`class DeviceBuffer_Null : public DeviceBuffer`  
_L11-29_
- inherits: `DeviceBuffer`
- L14 _protected prototype_ `virtual DeviceBuffer* CreateFromRaw(RawBufferPtr rawBuffer) override;`
- L15 _protected prototype_ `virtual DeviceBuffer* CreateFromDesc(BufferDescriptor desc, CHashPtr hash) override;`
- L17 _protected prototype_ `virtual AsyncBufferResultPtr TransferFrom(DeviceBufferRef& source);`
- L20 _public prototype_ `DeviceBuffer_Null(Device_Null* device, BufferDescriptor desc, CHashPtr hash);`
- L21 _public prototype_ `virtual ~DeviceBuffer_Null();`
- L23 _public prototype_ `virtual RawBufferPtr Raw_Now();`
- L24 _public prototype_ `virtual size_t MemSize() const;`
- L25 _public prototype_ `virtual AsyncBufferResultPtr Bind(const BlobTransform* transform, const ResourceBindInfo& bindInfo) override;`
- L26 _public prototype_ `virtual bool IsValid() const;`
- L27 _public prototype_ `virtual bool IsNull() const;`
- L28 _public prototype_ `virtual bool IsTransient() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/Null/Device_Null.h` (Other)


#### class `Device_Null`  
`class Device_Null : public Device`  
_L9-25_
- inherits: `Device`
- L13 _protected prototype_ `virtual void Collect(DeviceBuffer* Buffer) override;`
- L16 _public prototype_ `Device_Null();`
- L19 _public function_ `virtual FString Name() const override`
- L24 _public prototype_ `static Device_Null* Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Device/TaskPriorityQueue.h` (Other)


#### struct `DeviceNativeTask_CompareStrong`  
`struct DeviceNativeTask_CompareStrong`  
_L17-20_
- L19 _public prototype_ `bool operator()(const std::shared_ptr<DeviceNativeTask>& LHS, const std::shared_ptr<DeviceNativeTask>& RHS);`

#### struct `DeviceNativeTask_CompareWeak`  
`struct DeviceNativeTask_CompareWeak`  
_L23-26_
- L25 _public prototype_ `bool operator()(const std::weak_ptr<DeviceNativeTask>& InLHS, const std::weak_ptr<DeviceNativeTask>& InRHS);`

#### class `GenericTaskPriorityQueue`  
`template<typename PtrType, typename Comparer> class GenericTaskPriorityQueue : public std::priority_queue<PtrType, std::vector<PtrType>, Comparer>`  
_L30-168_
- inherits: `std::priority_queue<PtrType,std::vector<PtrType>,Comparer>`
- L32 _private typedef_ `using PriorityQueue = std::priority_queue<PtrType, std::vector<PtrType>, Comparer>;`
- L39 _protected member_ `mutable std::mutex Mutex;`
- L40 _protected member_ `std::condition_variable CondVar;`
- L43 _public function_ `bool remove(PtrType value)`
- L58 _public function_ `void add(PtrType p)`
- L65 _public function_ `void lock()`
- L70 _public function_ `void unlock()`
- L75 _public function_ `void reserve(size_t size)`
- L81 _public function_ `void resize(size_t size)`
- L87 _public function_ `size_t size() const`
- L93 _public function_ `const std::vector<PtrType>& accessInnerVector_Unsafe() const`
- L98 _public function_ `PtrType waitNext()`
- L112 _public function_ `void wait()`
- L121 _public function_ `std::vector<PtrType> to_vector() const`
- L139 _public function_ `void addBeginAndEnd(PtrType begin, PtrType end)`
- L147 _public function_ `void clear()`
- L153 _public function_ `std::vector<PtrType> to_vector_and_clear()`

#### Free symbols / members of external scopes

- L170 _typedef_ `typedef GenericTaskPriorityQueue<std::shared_ptr<DeviceNativeTask>, DeviceNativeTask_CompareStrong> DeviceNativeTask_PriorityQueueStrong;`
- L171 _typedef_ `typedef GenericTaskPriorityQueue<std::weak_ptr<DeviceNativeTask>, DeviceNativeTask_CompareWeak> DeviceNativeTask_PriorityQueue;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Export/T_ExportAsUAsset.h` (Other)


#### class `Job_ExportAsUAsset`  
`class Job_ExportAsUAsset : public Job`  
_L11-32_
- inherits: `Job`
- L14 _private member_ `FExportMapSettings Setting;`
- L15 _private member_ `FString OutFolder;`
- L18 _public prototype_ `Job_ExportAsUAsset(UMixInterface* Mix, int32 TargetId, FExportMapSettings InSetting, FString OutputFolder, UObject* InErrorOwner = nullptr, uint16 Priority = (uint16)E_Priority::kHigh, uint64 id = 0);`
- L21 _protected function_ `virtual void GetDependencies(JobPtrVec& prior, JobPtrVec& after, JobRunInfo runInfo) override`
- L22 _protected function_ `virtual AsyncPrepareResult PrepareTargets(JobBatch* batch) override`
- L23 _protected function_ `virtual AsyncPrepareResult PrepareResources(JobBatch* batch) override`
- L25 _protected function_ `virtual int32 Exec() override`
- L26 _protected function_ `virtual cti::continuable<int32> BindArgs_All(JobRunInfo runInfo) override`
- L27 _protected function_ `virtual cti::continuable<int32> UnbindArgs_All(JobRunInfo runInfo) override`
- L28 _protected function_ `virtual bool CanHandleTiles() const override`
- L30 _protected prototype_ `virtual cti::continuable<int32> PreExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type returnThread) override;`
- L31 _protected prototype_ `virtual cti::continuable<int32> ExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type returnThread) override;`

#### class `T_ExportAsUAsset`  
`class T_ExportAsUAsset`  
_L34-44_
- L37 _public prototype_ `T_ExportAsUAsset();`
- L38 _public prototype_ `virtual ~T_ExportAsUAsset();`
- L43 _public prototype_ `static void ExportAsUAsset(MixUpdateCyclePtr cycle, int32 targetId, FExportMapSettings exportMap, FString outFolder);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Export/TextureExporter.h` (Other)


#### struct `FExportMapSettings`  
`struct FExportMapSettings`  
_L21-39_
- L23 _public member_ `bool bIsEnabled = true;`
- L24 _public member_ `FName Name;`
- L25 _public member_ `FString Path;`
- L26 _public member_ `bool UseOverridePath;`
- L27 _public member_ `bool OverwriteTextures;`
- L28 _public member_ `TiledBlobPtr Map;`
- L29 _public member_ `bool IsSRGB;`
- L30 _public member_ `bool UseMipMaps;`
- L31 _public member_ `int32 Width;`
- L32 _public member_ `int32 Height;`
- L33 _public member_ `TextureCompressionSettings Compression;`
- L34 _public member_ `TextureGroup LODGroup;`
- L35 _public member_ `bool bSave;`
- L37 _public prototype_ `DECLARE_DELEGATE_OneParam(OnExportMapDone, FExportMapSettings MapSettings);`
- L38 _public member_ `OnExportMapDone OnDone;`

#### class `FExportSettings`  
`class FExportSettings`  
_L43-93_
- L46 _public member_ `FString PresetName;`
- L47 _public member_ `ExportMaps ExportPreset;`
- L49 _public prototype_ `DECLARE_DELEGATE(OnExportDone);`
- L50 _public member_ `OnExportDone OnDone;`
- L52 _public member_ `int MapsExported = 0;`
- L54 _public function_ `int GetMapCount()`
- L73 _public function_ `void Reset()`
- L79 _public function_ `void OnMapExportDone(FExportMapSettings MapSetting)`

#### struct `TextureExporter`  
`struct TextureExporter`  
_L95-106_
- L97 _public prototype_ `static FExportMapSettings GetExportSettingsForTarget(FExportSettings& ExportSettings, TiledBlobPtr BlobObj, FName Name);`
- L98 _public prototype_ `static AsyncInt ExportAllMapsAsUAsset(UMixInterface* MixObj, const FString& OutputFolder, TSharedRef<FExportSettings> SettingsRef);`
- L99 _public prototype_ `static AsyncInt ExportAsUAsset(UMixInterface* MixObj, TSharedRef<FExportSettings> SettingsRef, FString C);`
- L100 _public prototype_ `static void ExportAsUAsset(UMixInterface* MixObj, FName AssetName, FString CurrentPath, TSharedRef<FExportSettings> SettingsRef);`
- L101 _public prototype_ `static AsyncInt ExportRawAsUAsset(RawBufferPtr RawObj,const FExportMapSettings& Setting, const FString& CompletePath, const FName& TextureName);`
- L102 _public prototype_ `static bool IsPackageNameValid(FString Path, FString AssetName);`
- L103 _public prototype_ `static bool IsFileNameValid(FName FileName, FText& Reason);`
- L104 _public prototype_ `static bool IsFolderPathValid(FString FolderPath, FText& Reason);`
- L105 _public prototype_ `static bool IsFilePathValid(const FName InFileName, const FName InFolderPath, FString& OutErrors);`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(ExportLogs, Log, Verbose);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(ExportLogs, Log, Verbose);`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(OnExportMapDone, FExportMapSettings MapSettings);`
- L41 _typedef_ `typedef std::vector<std::pair<FName, FExportMapSettings>> ExportMaps;`
- L49 _delegate_ `DECLARE_DELEGATE(OnExportDone);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial.h` (Other)


#### class `VSH_Base`  
`class VSH_Base : public FGlobalShader`  
_L38-49_
- inherits: `FGlobalShader`
- L42 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`
- L47 _public function_ `VSH_Base()`
- L48 _public function_ `explicit VSH_Base(const ShaderMetaType::CompiledShaderInitializerType& initType) : FGlobalShader(initType)`

#### class `FSH_Base`  
`class FSH_Base : public FGlobalShader`  
_L52-63_
- inherits: `FGlobalShader`
- L56 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`
- L61 _public function_ `FSH_Base()`
- L62 _public function_ `explicit FSH_Base(const ShaderMetaType::CompiledShaderInitializerType& initType) : FGlobalShader(initType)`

#### class `CmpSH_Base`  
`template <const int ThreadGroupSize_X = 16, const int ThreadGroupSize_Y = 16, const int ThreadGroupSize_Z = 1> class CmpSH_Base : public FGlobalShader`  
_L67-89_
- inherits: `FGlobalShader`
- L71 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`
- L76 _public function_ `static inline void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`
- L85 _public function_ `CmpSH_Base()`
- L86 _public function_ `CmpSH_Base(const ShaderMetaType::CompiledShaderInitializerType& initType) : FGlobalShader(initType)`
- L88 _public function_ `FORCEINLINE constexpr FIntVector ThreadGroupSize() const`

#### class `VSH_Simple`  
`class VSH_Simple : public VSH_Base`  
_L92-106_
- inherits: `VSH_Base`
- L96 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(VSH_Simple, VSH_Base);`
- L102 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`

#### class `FSH_Simple`  
`class FSH_Simple : public FSH_Base`  
_L109-129_
- inherits: `FSH_Base`
- L113 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Simple, FSH_Base);`
- L121 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`
- L126 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_SimpleVT`  
`class FSH_SimpleVT : public FSH_Base`  
_L132-168_
- inherits: `FSH_Base`
- L136 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_SimpleVT, FSH_Base);`
- L150 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& params)`
- L165 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `QuadScreenBuffer`  
`class QuadScreenBuffer : public FVertexBuffer`  
_L171-174_
- inherits: `FVertexBuffer`
- L173 _private prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;`

#### class `FxMaterial`  
`class FxMaterial`  
_L177-263_
- L187 _public typedef_ `typedef TMap<FName, MemberInfo> MemberLUT;`
- L196 _public typedef_ `typedef std::vector<FxMetadata> FxMetadataSet;`
- L198 _public typedef_ `using ArrayTexture = std::vector<const UTexture*>;`
- L209 _protected member_ `std::unique_ptr<MemberLUT> ParamsLUT;` — Parameters lookup table
- L210 _protected member_ `CHashPtr HashValue;` — Hash for the FxMaterial
- L212 _protected member_ `std::vector<BoundTextures> Textures;` — Textures that are bound with this material. We bind them in the end
- L214 _protected prototype_ `std::unique_ptr<MemberLUT>& GetParamsLUT();`
- L215 _protected prototype_ `MemberInfo GetMember(FName MemberName);`
- L217 _protected prototype_ `void BindTexturesForBlitting();`
- L220 _protected prototype_ `FxMaterial() = default;` — Default constructor is only accessible to derived classes
- L224 _public prototype_ `FxMaterial(TShaderRef<VSH_Base> VSH, TShaderRef<FSH_Base> FSH);`
- L225 _public prototype_ `FxMaterial(TShaderRef<VSH_Base> VSH);`
- L226 _public prototype_ `FxMaterial(FString VSHHashStr, FString FSHHashStr);`
- L231 _public member_ `static TGlobalResource<QuadScreenBuffer> GQuadBuffer;`
- L232 _public prototype_ `static void InitPSO_Default(FGraphicsPipelineStateInitializer& PSO);`
- L233 _public prototype_ `static void InitPSO_Default(FGraphicsPipelineStateInitializer& PSO, FRHIVertexShader* VSH, FRHIPixelShader* FSH);`
- L238 _public prototype_ `virtual ~FxMaterial() = default;`
- L241 _public prototype_ `Clone() = 0;`
- L242 _public prototype_ `virtual FxMetadataSet GetMetadata() const = 0;`
- L243 _public prototype_ `virtual void Blit(FRHICommandListImmediate& RHI, FRHITexture* Target, const RenderMesh* MeshObj, int32 TargetId, FGraphicsPipelineStateInitializer* PSO = nullptr) = 0;`
- L248 _public prototype_ `virtual void SetArrayTextureParameterValue(FName Name, const ArrayTexture& Value);`
- L249 _public prototype_ `virtual void SetTextureParameterValue(FName Name, const UTexture* Value);`
- L250 _public prototype_ `virtual void SetScalarParameterValue(FName Name, float Value);`
- L251 _public prototype_ `virtual void SetScalarParameterValue(FName Name, int32 Value);`
- L252 _public prototype_ `virtual void SetVectorParameterValue(FName Name, const FLinearColor& Value);`
- L253 _public prototype_ `virtual void SetVectorParameterValue(FName Name, const FIntVector4& Value);`
- L254 _public prototype_ `virtual void SetStructParameterValue(FName Name, const char* Value, size_t StructSize);`
- L255 _public prototype_ `virtual void SetArrayParameterValue(FName Name, const char* startAddress, size_t TypeSize, size_t ArraySize);`
- L256 _public prototype_ `virtual void SetMatrixParameterValue(FName Name, const FMatrix& Value);`
- L257 _public prototype_ `virtual bool DoesMemberExist(FName MemberName);`
- L262 _public function_ `FORCEINLINE CHashPtr Hash() const`

#### struct `FxMaterial::MemberInfo`  
`struct MemberInfo`  
_L180-185_
- L183 _public member_ `Member;`
- L184 _public member_ `char* RawPtr = nullptr;`

#### struct `FxMaterial::FxMetadata`  
`struct FxMetadata`  
_L189-194_
- L192 _public member_ `Metadata = nullptr;`
- L193 _public member_ `char* StartAddress = nullptr;`

#### struct `FxMaterial::BoundTextures`  
`struct BoundTextures`  
_L201-207_
- L203 _public member_ `FName Name;` — The Name of the argument
- L204 _public member_ `char* Arg = nullptr;` — The pointer in the arg struct
- L205 _public member_ `const UTexture* Texture = nullptr;` — The underlying texture
- L206 _public member_ `ArrayTexture tiles;`

#### class `FxMaterial_Compute`  
`template <typename CmpSH_Type> class FxMaterial_Compute : public FxMaterial`  
_L269-374_
- inherits: `FxMaterial`
- L273 _public typedef_ `using CmpSHPermutationDomain = typename CmpSH_Type::FPermutationDomain;` — type Name for the permutation domain
- L276 _protected member_ `static constexpr int GDefaultNumThreadsXY = 1024;` — Default number of threads
- L277 _protected member_ `FString OutputId;` — The ID of the output of the compute shader
- L279 _protected member_ `CmpSHPermutationDomain PermutationDomain;` — Compute shader Permutation Domain Value
- L280 _protected member_ `typename CmpSH_Type::FParameters Params;` — Params for the shader
- L281 _protected member_ `int NumThreadsX = GDefaultNumThreadsXY;` — How many X threads
- L282 _protected member_ `int NumThreadsY = GDefaultNumThreadsXY;` — How many Y threads
- L283 _protected member_ `int NumThreadsZ = 1;` — How many Z threads
- L284 _protected member_ `FUnorderedAccessViewRHIRef UnorderedAccessView = nullptr;` — The access view for the compute shader. If this is null then
- L288 _public function_ `explicit FxMaterial_Compute(FString InOutputId, const CmpSHPermutationDomain* InPermDomain = nullptr, int InNumThreadsX = GDefaultNumThreadsXY, int InNumThreadsY = GDefaultNumThreadsXY, int InNumThreadsZ= 1, FUnorderedAccessViewRHIRef InUnorderedAccessView = nullptr) : FxMaterial() , OutputId(InOutputId) , NumThreadsX(InNumThreadsX) , NumThreadsY(InNumThreadsY) , NumThreadsZ(InNumThreadsZ) , UnorderedAccessView(InUnorderedAccessView)`
- L307 _public function_ `virtual std::shared_ptr<FxMaterial> Clone() override`
- L313 _public function_ `FORCEINLINE typename CmpSH_Type::FParameters& GetParams()`
- L315 _public function_ `virtual FxMetadataSet GetMetadata() const override`
- L320 _public function_ `void SetUAVParameterValue(FName Name, FUnorderedAccessViewRHIRef UAV)`
- L332 _public function_ `virtual void Blit(FRHICommandListImmediate& RHI, FRHITexture* Target, const RenderMesh* MeshObj, int32 TargetId, FGraphicsPipelineStateInitializer* PSO = nullptr) override`

#### class `FxMaterial_Normal`  
`template <typename VSH_Type, typename FSH_Type> class FxMaterial_Normal : public FxMaterial`  
_L378-490_
- inherits: `FxMaterial`
- L382 _public typedef_ `using VSHPermutationDomain = typename VSH_Type::FPermutationDomain;` — type Name for the permutation domain
- L383 _public typedef_ `using FSHPermutationDomain = typename FSH_Type::FPermutationDomain;`
- L386 _protected member_ `VSHPermutationDomain VSHPermDomain;` — Vertex shader Permutation Domain Value
- L387 _protected member_ `FSHPermutationDomain FSHPermDomain;` — Fragment shader Permutation Domain Value
- L388 _protected member_ `typename VSH_Type::FParameters VSHParams;` — Params for the vertex shader
- L389 _protected member_ `typename FSH_Type::FParameters FSHParams;` — Params for the fragment shader
- L394 _public function_ `FxMaterial_Normal() : FxMaterial( TShaderMapRef<VSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), VSHPermutationDomain()), TShaderMapRef<FSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), FSHPermutationDomain()))`
- L400 _public function_ `FxMaterial_Normal(const VSHPermutationDomain& InVSHPermutationDomain, const FSHPermutationDomain& InFSHPermutationDomain) : FxMaterial( TShaderMapRef<VSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), InVSHPermutationDomain), TShaderMapRef<FSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), InFSHPermutationDomain)), VSHPermDomain(InVSHPermutationDomain), FSHPermDomain(InFSHPermutationDomain)`
- L408 _public function_ `FxMaterial_Normal(const typename FSH_Type::FParameters InFSHParams) : FxMaterial(TShaderMapRef<VSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), VSHPermutationDomain()), TShaderMapRef<FSH_Type>(GetGlobalShaderMap(GMaxRHIFeatureLevel), FSHPermutationDomain())), FSHParams(InFSHParams)`
- L415 _public function_ `virtual std::shared_ptr<FxMaterial> Clone() override`
- L420 _public function_ `FORCEINLINE typename VSH_Type::FParameters& VSH_Params()`
- L421 _public function_ `FORCEINLINE typename FSH_Type::FParameters& FSH_Params()`
- L423 _public function_ `virtual FxMetadataSet GetMetadata() const override`
- L431 _public function_ `virtual void Blit(FRHICommandListImmediate& RHI, FRHITexture* Target, const RenderMesh* MeshObj, int32 InTargetId, FGraphicsPipelineStateInitializer* InPSO = nullptr) override`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L34 _function_ `template <class SH_TypeParams> void SetupDefaultParameters(SH_TypeParams& params)`
- L265 _typedef_ `typedef std::shared_ptr<FxMaterial> FxMaterialPtr;`
- L492 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_Simple> Fx_FullScreenCopy;`
- L493 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_SimpleVT> Fx_FullScreenCopyVT;`
- L495 _macro_ `#define DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(Name, BaseName) class TEXTUREGRAPHENGINE_API Name : public BaseName \`
- L502 _macro_ `#define DECLARE_EMPTY_GLOBAL_SHADER(Name) DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(Name, FSH_Base)`
- L504 _macro_ `#define TEXTURE_ENGINE_DEFAULT_PERMUTATION \`
- L510 _macro_ `#define TEXTUREGRAPH_ENGINE_DEFAULT_COMPILATION_ENV \`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial_DrawMaterial.h` (Other)


#### class `FTextureGraphMaterialShaderVS`  
`class FTextureGraphMaterialShaderVS : public FMaterialShader`  
_L27-58_
- inherits: `FMaterialShader`
- L30 _public prototype_ `DECLARE_SHADER_TYPE(FTextureGraphMaterialShaderVS, Material) BEGIN_SHADER_PARAMETER_STRUCT(FParameters, ) END_SHADER_PARAMETER_STRUCT() SHADER_USE_PARAMETER_STRUCT_WITH_LEGACY_BASE(FTextureGraphMaterialShaderVS, FMaterialShader);`
- L37 _public function_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters)`
- L42 _public function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L47 _public function_ `static bool ShouldCache(EShaderPlatform Platform)`
- L53 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View)`

#### class `FTextureGraphMaterialShaderPS`  
`class FTextureGraphMaterialShaderPS : public FMaterialShader`  
_L60-97_
- inherits: `FMaterialShader`
- L63 _public prototype_ `DECLARE_SHADER_TYPE(FTextureGraphMaterialShaderPS, Material) BEGIN_SHADER_PARAMETER_STRUCT(FParameters, ) SHADER_PARAMETER(FLinearColor, PSControl) SHADER_PARAMETER_STRUCT(FTileInfo, TileInfo) END_SHADER_PARAMETER_STRUCT() SHADER_USE_PARAMETER_STRUCT_WITH_LEGACY_BASE(FTextureGraphMaterialShaderPS, FMaterialShader);`
- L72 _public member_ `static FName PSCONTROL_ARG;`
- L74 _public function_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters)`
- L79 _public function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L84 _public function_ `static bool ShouldCache(EShaderPlatform Platform)`
- L90 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View, const FMaterialRenderProxy* MaterialProxy, const FMaterial& Material)`

#### class `FxMaterial_DrawMaterialBase`  
`class FxMaterial_DrawMaterialBase : public FxMaterial`  
_L99-117_
- inherits: `FxMaterial`
- L102 _public function_ `FxMaterial_DrawMaterialBase() : FxMaterial(TEXT("VSH_TypeVSH_TypeVSH_TypeVSH_Type"), TEXT("FSH_TypeFSH_TypeFSH_TypeFSH_Type"))`
- L107 _public prototype_ `FSceneView* CreateSceneView(FSceneViewFamilyContext& ViewFamily, UTextureRenderTarget2D* RenderTarget, const FIntPoint& TargetSizeXY, int32 RenderIndex);`
- L109 _public prototype_ `bool HasVirtualTextureFeedback(FMaterial const& RenderMaterial, EShaderPlatform ShaderPlatform) const;`
- L110 _public prototype_ `int32 GetDefaultVirtualTextureWarmupFrames() const;`
- L111 _public prototype_ `void VirtualTextureFeedbackBegin(FRDGBuilder& GraphBuilder, FIntPoint TargetSize, ERHIFeatureLevel::Type FeatureLevel) const;`
- L112 _public prototype_ `void VirtualTextureFeedbackEnd(FRDGBuilder& GraphBuilder) const;`
- L113 _public prototype_ `void VirtualTextureFeedbackSync(FRHICommandListImmediate& RHICmdList, ERHIFeatureLevel::Type FeatureLevel) const;`
- L114 _public prototype_ `void EndFrame(FRHICommandListImmediate& RHICmdList);`
- L116 _public prototype_ `static bool ValidateMaterialShaderMap(UMaterial* InMaterial, FShaderType* InPixelShaderType);`

#### class `FxMaterial_DrawMaterial`  
`template <typename VSH_Type, typename FSH_Type> class FxMaterial_DrawMaterial : public FxMaterial_DrawMaterialBase`  
_L120-282_
- inherits: `FxMaterial_DrawMaterialBase`
- L132 _public typedef_ `using VSHPermutationDomain = typename VSH_Type::FPermutationDomain;` — type name for the permutation domain
- L133 _public typedef_ `using FSHPermutationDomain = typename FSH_Type::FPermutationDomain;`
- L135 _public member_ `TObjectPtr<UMaterialInterface> Material;`
- L138 _protected member_ `VSHPermutationDomain VSHPermDomain;` — Vertex shader Permutation Domain value
- L139 _protected member_ `FSHPermutationDomain FSHPermDomain;` — Fragment shader Permutation Domain value
- L140 _protected member_ `typename VSH_Type::FParameters VSHParams;` — Params for the vertex shader
- L141 _protected member_ `typename FSH_Type::FParameters FSHParams;` — Params for the fragment shader
- L146 _public member_ `int32 VirtualTextureNumWarmupFrames = 0;` — If Material uses VT, we need to run several frames to make sure the VT is fully loaded. 0 indicate to use the actual default value specified from the CVar <TG.VirtualTexture.NumWarmupFrames>
- L150 _public function_ `FxMaterial_DrawMaterial() : FxMaterial_DrawMaterialBase()`
- L155 _public function_ `FxMaterial_DrawMaterial(UMaterialInterface* InMaterial, const VSHPermutationDomain& InVSHPermutationDomain, const FSHPermutationDomain& InFSHPermutationDomain, int32 InVirtualTextureNumWarmupFrames) : FxMaterial_DrawMaterialBase(), Material(InMaterial), VSHPermDomain(InVSHPermutationDomain), FSHPermDomain(InFSHPermutationDomain), VirtualTextureNumWarmupFrames(InVirtualTextureNumWarmupFrames)`
- L164 _public function_ `virtual std::shared_ptr<FxMaterial> Clone() override`
- L169 _public function_ `int32 GetVirtualTextureWarmupFrames() const`
- L182 _public function_ `virtual FxMetadataSet GetMetadata() const override`
- L190 _public function_ `virtual void Blit(FRHICommandListImmediate& RHI, FRHITexture* Target, const RenderMesh* MeshObj, int32 TargetId, FGraphicsPipelineStateInitializer* InPSO = nullptr) override`
- L195 _public function_ `void MyBlit(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* RenderTarget, FRHITexture* Target, const RenderMesh* MeshObj, int32 TargetId, FGraphicsPipelineStateInitializer* InPSO = nullptr)`
- L274 _public function_ `static bool ValidateMaterial(UMaterialInterface* InMaterial)`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L245 _function_ `` (scope `FxMaterial_DrawMaterial::MyBlit`)
- L284 _typedef_ `typedef FxMaterial_DrawMaterial< FTextureGraphMaterialShaderVS, FTextureGraphMaterialShaderPS> FxMaterial_QuadDrawMaterial;`
- L285 _typedef_ `typedef std::shared_ptr<FxMaterial_QuadDrawMaterial> FxMaterialQuadDrawMaterialPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/MaterialManager.h` (Other)


#### class `UMaterialManager`  
`class UMaterialManager : public UModelObject`  
_L17-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModelObject`
- L23 _private member_ `TMap<FString, TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(transient)` — The materials that have been loaded so far
- L25 _private prototype_ `void InitEssentialMaterials();`
- L29 _public prototype_ `UMaterialManager();`
- L32 _public prototype_ `class UMaterial* LoadMaterial(const FString& Path);`
- L34 _public prototype_ `RenderMaterial_BPPtr CreateMaterial_BP(FString Name, const FString& Path, int32 InNumWarmupFrames = 0);`
- L35 _public prototype_ `RenderMaterial_BPPtr CreateMaterial_BP(FString InName, UMaterial* InMaterial, int32 InNumWarmupFrames = 0);`
- L36 _public prototype_ `RenderMaterial_BP_NoTilePtr CreateMaterial_BP_NoTile(FString Name, const FString& Path, int32 InNumWarmupFrames = 0);`
- L37 _public prototype_ `RenderMaterial_ThumbPtr CreateMaterial_Thumbnail(FString Name, const FString& Path);`
- L38 _public prototype_ `RenderMaterial_BP_TileArgsPtr CreateMaterialOfType_BP_TileArgs(FString Name, const FString& Path, int32 InNumWarmupFrames = 0);`
- L43 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FXPtr CreateMaterial_FX(FString Name)`
- L50 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FXPtr CreateMaterial_FX(FString Name, const typename VSH_Type::FPermutationDomain& InVSHPermutationDomain, const typename FSH_Type::FPermutationDomain& InFSHPermutationDomain)`
- L57 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FXPtr CreateMaterial_FX(FString Name, const typename FSH_Type::FPermutationDomain& InFSHPermutationDomain)`
- L64 _public function_ `template <typename CmpSH_Type> RenderMaterial_FXPtr CreateMaterial_CmpFX(FString Name, FString OutputId, int NumThreadsX, int NumThreadsY, int NumThreadsZ = 1)`
- L71 _public function_ `template <typename CmpSH_Type> RenderMaterial_FXPtr CreateMaterial_CmpFX(FString Name, FString OutputId, const typename CmpSH_Type::FPermutationDomain& cmpshPermutationDomain, int NumThreadsX, int NumThreadsY, int NumThreadsZ = 1)`
- L79 _public function_ `template <typename FxMatType> RenderMaterial_FXPtr CreateMaterialOfType_FX(FString Name)`
- L86 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FX_CombinedPtr CreateMaterial_FX_Combined(FString Name)`
- L93 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FX_CombinedPtr CreateMaterial_FX_Combined(FString Name, const typename VSH_Type::FPermutationDomain& InVSHPermutationDomain, const typename FSH_Type::FPermutationDomain& InFSHPermutationDomain)`
- L100 _public function_ `template <typename VSH_Type, typename FSH_Type> RenderMaterial_FX_CombinedPtr CreateMaterial_FX_Combined(FString Name, const typename FSH_Type::FPermutationDomain& InFSHPermutationDomain)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial.h` (Other)


#### class `RenderMaterial`  
`class RenderMaterial : public BlobTransform`  
_L18-54_
- inherits: `BlobTransform`
- L21 _protected member_ `bool bCanHandleTiles = true;` — Whether this material can handle tiles or not
- L24 _public prototype_ `explicit RenderMaterial(FString Name);`
- L27 _public prototype_ `virtual void BlitTo(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* Dst, const RenderMesh* MeshObj, int32 TargetId) const = 0;`
- L28 _public prototype_ `void BlitTo(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* Dst) const;`
- L33 _public prototype_ `virtual Device* TargetDevice(size_t Index) const override;`
- L34 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) override;`
- L35 _public prototype_ `virtual ENamedThreads::Type ExecutionThread() const override;`
- L36 _public prototype_ `virtual bool CanHandleTiles() const override;`
- L38 _public prototype_ `virtual void SetTexture(FName Name, const UTexture* Texture) const = 0;`
- L39 _public prototype_ `virtual void SetArrayTexture(FName Name, const std::vector<const UTexture*>& Textures) const = 0;`
- L40 _public prototype_ `virtual void SetInt(FName Name, int32 Value) const = 0;`
- L41 _public prototype_ `virtual void SetFloat(FName Name, float Value) const = 0;`
- L42 _public prototype_ `virtual void SetColor(FName Name, const FLinearColor& Value) const = 0;`
- L43 _public prototype_ `virtual void SetIntVector4(FName Name, const FIntVector4& Value) const = 0;`
- L44 _public prototype_ `virtual void SetMatrix(FName Name, const FMatrix& Value) const = 0;`
- L45 _public prototype_ `void SetSourceTexture(const Tex* Texture) const;`
- L46 _public prototype_ `void SetTexture(FName InName, std::shared_ptr<Tex> TexObj) const;`
- L47 _public prototype_ `void SetArrayTexture(FName InName, const std::vector<std::shared_ptr<Tex>>& TexObj) const;`
- L48 _public prototype_ `void BlitTo(FRHICommandListImmediate& RHI, Tex* Dst, const RenderMesh* MeshObj = nullptr, int32 TargetId = -1) const;`
- L52 _public function_ `FORCEINLINE void SetSourceTexture(const UTexture* Texture) const`
- L53 _public function_ `FORCEINLINE bool& CanHandleTiles()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L56 _typedef_ `typedef std::shared_ptr<RenderMaterial> RenderMaterialPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_BP.h` (Other)


#### struct `FMaterialInstanceStaticSwitchPermutationMap`  
`struct FMaterialInstanceStaticSwitchPermutationMap`  
_L20-37_
- reflection: `USTRUCT()`
- desc: Helper container of MIC for the different static switch permutations of a Material Used by the caller of a RenderMaterial_BP to pick a specific permutation different from the default set. See TG_Expression_MaterialBase for a usage example
- L24 _public member_ `int32 DefaultKey = 0;`
- L27 _public member_ `FStaticParameterSet DefaultStaticParameterSet;` — `UPROPERTY()`
- L30 _public member_ `TMap<int32, TObjectPtr<UMaterialInstanceConstant>> PermutationsMap;` — `UPROPERTY()`
- L32 _public prototype_ `static FMaterialInstanceStaticSwitchPermutationMap Create(UMaterialInterface* InMaterial);`
- L33 _public prototype_ `UMaterialInterface* GetRootMaterial();`
- L34 _public prototype_ `int32 KeyFromStaticSwitchParameters(const TArray<FStaticSwitchParameter>& Parameters);`
- L35 _public prototype_ `UMaterialInstanceConstant* GetMaterialInstance(const TArray<FStaticSwitchParameter>& Parameters);`
- L36 _public prototype_ `bool IsValid() const;`

#### class `RenderMaterial_BP`  
`class RenderMaterial_BP : public RenderMaterial`  
_L39-105_
- inherits: `RenderMaterial`
- L44 _public prototype_ `static int32 GetDefaultVirtualTextureNumWarmupFrames();` — When a Material contains a VirtualTexture, the default num of warmup frames run to stream the appropriate resolution This can be fine tuned by instance of RenderMaterial_BP from the constructor
- L48 _protected member_ `UMaterialInterface* Material = nullptr;` — The base material that is used for this job
- L49 _protected member_ `TStrongObjectPtr<UMaterialInstanceConstant> MaterialInstance;` — An instance of the material
- L51 _protected member_ `CHashPtr HashValue;` — The hash for this material
- L52 _protected member_ `bool RequestMaterialValidation = true;`
- L53 _protected member_ `bool MaterialInstanceValidated = false;`
- L55 _protected member_ `FxMaterialPtr FXMaterialObj;`
- L57 _protected member_ `int32 VirtualTextureNumWarmupFrames = 0;` — Num warmup frames for this instance default to -1
- L59 _protected member_ `UCanvas* Canvas = nullptr;`
- L61 _protected prototype_ `void DrawMaterial(UMaterialInterface* RenderMaterial, FVector2D ScreenPosition, FVector2D ScreenSize, FVector2D CoordinatePosition, FVector2D CoordinateSize=FVector2D::UnitVector, float Rotation=0.f, FVector2D PivotPoint=FVector2D(0.5f,0.5f)) const;`
- L65 _public prototype_ `RenderMaterial_BP(FString Name, UMaterialInterface* InMaterial, int32 InNumWarmupFrames);`
- L69 _public prototype_ `static bool ValidateMaterialCompatible(UMaterialInterface* InMaterial);`
- L72 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args) override;`
- L77 _public prototype_ `virtual void Bind(int32 Value, const ResourceBindInfo& BindInfo) override;`
- L78 _public prototype_ `virtual void Bind(float Value, const ResourceBindInfo& BindInfo) override;`
- L79 _public prototype_ `virtual void Bind(const FLinearColor& Value, const ResourceBindInfo& BindInfo) override;`
- L80 _public prototype_ `virtual void Bind(const FIntVector4& Value, const ResourceBindInfo& BindInfo) override;`
- L81 _public prototype_ `virtual void Bind(const FMatrix& Value, const ResourceBindInfo& BindInfo) override;`
- L82 _public prototype_ `virtual void BindStruct(const char* ValueAddress, size_t StructSize, const ResourceBindInfo& BindInfo) override;`
- L83 _public prototype_ `virtual CHashPtr Hash() const override;`
- L84 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString InName) override;`
- L89 _public prototype_ `virtual void BlitTo(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* DstRT, const RenderMesh* MeshObj, int32 TargetId) const override;`
- L90 _public prototype_ `virtual void SetTexture(FName InName, const UTexture* Texture) const override;`
- L91 _public prototype_ `virtual void SetArrayTexture(FName InName, const std::vector<const UTexture*>& Textures) const override;`
- L92 _public prototype_ `virtual void SetInt(FName InName, int32 Value) const override;`
- L93 _public prototype_ `virtual void SetFloat(FName InName, float Value) const override;`
- L94 _public prototype_ `virtual void SetColor(FName InName, const FLinearColor& Value) const override;`
- L95 _public prototype_ `virtual void SetIntVector4(FName InName, const FIntVector4& Value) const override;`
- L96 _public prototype_ `virtual void SetMatrix(FName InName, const FMatrix& Value) const override;`
- L101 _public function_ `FORCEINLINE UMaterialInterface* GetMaterial()`
- L102 _public function_ `FORCEINLINE UMaterialInstanceConstant* Instance()`
- L103 _public function_ `FORCEINLINE const UMaterialInstanceConstant* Instance() const`
- L104 _public function_ `FORCEINLINE int32 GetVirtualTextureNumWarmupFrames() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _typedef_ `typedef std::shared_ptr< FxMaterial> FxMaterialPtr;`
- L107 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP> RenderMaterial_BPPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_BP_NoTile.h` (Other)


#### class `RenderMaterial_BP_NoTile`  
`class RenderMaterial_BP_NoTile : public RenderMaterial_BP`  
_L12-18_
- inherits: `RenderMaterial_BP`
- L16 _public function_ `RenderMaterial_BP_NoTile(FString InName, UMaterialInterface* InMaterial, int32 InVTNumWarmUpFrames) : RenderMaterial_BP(InName, InMaterial, InVTNumWarmUpFrames)`
- L17 _public function_ `virtual bool CanHandleTiles() const override`

#### class `RenderMaterial_BP_TileArgs`  
`class RenderMaterial_BP_TileArgs : public RenderMaterial_BP`  
_L22-33_
- inherits: `RenderMaterial_BP`
- L25 _private member_ `FName MemberName = "Ti`
- L28 _public function_ `RenderMaterial_BP_TileArgs(FString InName, UMaterialInterface* InMaterial, int32 InVTNumWarmUpFrames) : RenderMaterial_BP(InName, InMaterial, InVTNumWarmUpFrames)`
- L29 _public prototype_ `void AddTileArgs(TransformArgs& Args);`
- L30 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args) override;`
- L31 _public function_ `virtual bool CanHandleTiles() const override`
- L32 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString NewName) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L20 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP_NoTile> RenderMaterial_BP_NoTilePtr;`
- L35 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP_TileArgs> RenderMaterial_BP_TileArgsPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_FX.h` (Other)


#### class `RenderMaterial_FX`  
`class RenderMaterial_FX : public RenderMaterial`  
_L13-53_
- inherits: `RenderMaterial`
- L16 _protected member_ `mutable FxMaterialPtr FXMaterial;` — The FX material from the shader
- L17 _protected member_ `CHashPtr HashValue;` — The hash for the material
- L20 _public prototype_ `RenderMaterial_FX(FString InName, FxMaterialPtr InFXMaterial);`
- L26 _public prototype_ `virtual void Bind(int32 Value, const ResourceBindInfo& BindInfo) override;`
- L27 _public prototype_ `virtual void Bind(float Value, const ResourceBindInfo& BindInfo) override;`
- L28 _public prototype_ `virtual void Bind(const FLinearColor& Value, const ResourceBindInfo& BindInfo) override;`
- L29 _public prototype_ `virtual void Bind(const FIntVector4& Value, const ResourceBindInfo& BindInfo) override;`
- L30 _public prototype_ `virtual void Bind(const FMatrix& Value, const ResourceBindInfo& BindInfo) override;`
- L31 _public prototype_ `virtual void BindStruct(const char* ValueAddress, size_t StructSize, const ResourceBindInfo& BindInfo) override;`
- L32 _public prototype_ `virtual void BindScalarArray(const char* StartingAddress, size_t TypeSize, size_t ArraySize, const ResourceBindInfo& BindInfo) override;`
- L34 _public prototype_ `virtual CHashPtr Hash() const override;`
- L35 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString NewName) override;`
- L40 _public prototype_ `virtual void BlitTo(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* RenderTarget, const RenderMesh* MeshObj, int32 TargetId) const override;`
- L41 _public prototype_ `virtual void SetTexture(FName InName, const UTexture* Texture) const override;`
- L42 _public prototype_ `virtual void SetArrayTexture(FName InName, const std::vector<const UTexture*>& Textures) const override;`
- L43 _public prototype_ `virtual void SetInt(FName InName, int32 Value) const override;`
- L44 _public prototype_ `virtual void SetFloat(FName InName, float Value) const override;`
- L45 _public prototype_ `virtual void SetColor(FName InName, const FLinearColor& Value) const override;`
- L46 _public prototype_ `virtual void SetIntVector4(FName InName, const FIntVector4& Value) const override;`
- L47 _public prototype_ `virtual void SetMatrix(FName InName, const FMatrix& Value) const override;`
- L52 _public function_ `FORCEINLINE FxMaterialPtr FxMaterial() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L11 _typedef_ `typedef std::shared_ptr<FxMaterial> FxMaterialPtr;`
- L57 _typedef_ `typedef std::shared_ptr<RenderMaterial_FX> RenderMaterial_FXPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_FX_Combined.h` (Other)


#### class `RenderMaterial_FX_Combined`  
`class RenderMaterial_FX_Combined : public RenderMaterial_FX`  
_L15-34_
- inherits: `RenderMaterial_FX`
- L19 _private member_ `TArray<TiledBlobPtr> ToBeCombined;` — To save under process blobs. This array ensures that multiple SRVs can be passed to the shader
- L22 _public prototype_ `RenderMaterial_FX_Combined(FString InName, FxMaterialPtr InFXMaterial);`
- L25 _public prototype_ `void AddTileArgs(TransformArgs& Args);`
- L26 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args) override;`
- L27 _public function_ `virtual bool CanHandleTiles() const override`
- L28 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString NewName) override;`
- L29 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) override;`
- L30 _public prototype_ `TiledBlobPtr AddBlobToCombine(TiledBlobPtr BlobToCombine);`
- L31 _public prototype_ `void FreeCombinedBlob();`
- L33 _public member_ `static const FName MemberName;` — Default struct parameter for tile

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderMaterial_FX_NoTile, All, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderMaterial_FX_NoTile, All, All);`
- L36 _typedef_ `typedef std::shared_ptr<RenderMaterial_FX_Combined> RenderMaterial_FX_CombinedPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_FX_MinMax.h` (Other)


#### class `RenderMaterial_FX_MinMax`  
`class RenderMaterial_FX_MinMax : public RenderMaterial_FX`  
_L15-31_
- inherits: `RenderMaterial_FX`
- L19 _private member_ `FxMaterialPtr SecondPassMaterial;`
- L20 _private member_ `BufferDescriptor SourceDesc;`
- L21 _private member_ `TArray<TexPtr> DownsampledResultTargets;` — used for creating intermediate targets.
- L24 _public prototype_ `RenderMaterial_FX_MinMax(FString InName, FxMaterialPtr InMaterial, FxMaterialPtr InSecondPassMaterial);`
- L27 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args) override;`
- L28 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) override;`
- L30 _public function_ `void SetDescriptor(const BufferDescriptor& InDesc)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderMaterial_FX_MinMax, All, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderMaterial_FX_MinMax, All, All);`
- L13 _typedef_ `typedef std::shared_ptr<Tex> TexPtr;`
- L33 _typedef_ `typedef std::shared_ptr<RenderMaterial_FX_MinMax> RenderMaterial_FX_MinMaxPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/RenderMaterial_Thumbnail.h` (Other)


#### class `RenderMaterial_Thumbnail`  
`class RenderMaterial_Thumbnail : public RenderMaterial_BP`  
_L12-28_
- inherits: `RenderMaterial_BP`
- desc: Subset of RenderMaterial BP, This class will always render a thumbnail from its material instance
- L15 _public member_ `static constexpr uint32 GThumbWidth = 128;` — Width of standard thumbnail image
- L16 _public member_ `static constexpr uint32 GThumbHeight = 128;` — Height of the standard thumbnail image
- L19 _private member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L22 _public prototype_ `RenderMaterial_Thumbnail(FString InName, UMaterialInterface* InMaterial);`
- L24 _public prototype_ `virtual void BlitTo(FRHICommandListImmediate& RHI, UTextureRenderTarget2D* DstRT, const RenderMesh* MeshObj, int32 TargetId) const override;`
- L25 _public function_ `virtual bool CanHandleTiles() const override`
- L26 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString InName) override;`
- L27 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L30 _typedef_ `typedef std::shared_ptr<RenderMaterial_Thumbnail> RenderMaterial_ThumbPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/SamplerStates_FX.h` (Other)


#### Free symbols / members of external scopes

- L9 _macro_ `#define DEFAULT_POINT_CLAMP TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI()`
- L10 _macro_ `#define DEFAULT_POINT_WRAP TStaticSamplerState<SF_Point, AM_Wrap, AM_Wrap, AM_Wrap>::GetRHI()`
- L11 _macro_ `#define DEFAULT_POINT_BORDER TStaticSamplerState<SF_Point, AM_Border, AM_Border, AM_Border>::GetRHI()`
- L12 _macro_ `#define DEFAULT_LINEAR_CLAMP TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI()`
- L13 _macro_ `#define DEFAULT_LINEAR_WRAP TStaticSamplerState<SF_Bilinear, AM_Wrap, AM_Wrap, AM_Wrap>::GetRHI()`
- L14 _macro_ `#define DEFAULT_LINEAR_BORDER TStaticSamplerState<SF_Bilinear, AM_Border, AM_Border, AM_Border>::GetRHI()`
- L23 _function_ `END_SHADER_PARAMETER_STRUCT() FORCEINLINE void FStandardSamplerStates_Setup(FStandardSamplerStates& params)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/TileInfo_FX.h` (Other)
_(no declarations extracted)_

### `Plugins/TextureGraph/Source/TextureGraphEngine/GraphicsDefs.h` (Other)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FVector4 Vector4;`
- L9 _typedef_ `typedef FVector Vector3;`
- L10 _typedef_ `typedef FVector2D Vector2;`
- L11 _typedef_ `typedef FProcMeshTangent Tangent;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/ColorUtil.h` (Other)


#### class `ColorUtil`  
`class ColorUtil`  
_L9-43_
- L13 _public prototype_ `static const FLinearColor DefaultColor(TextureType Type);` — Converting from Array to Functions to avoid static fiasco problem with CPP
- L14 _public prototype_ `static const FLinearColor DefaultDiffuse();`
- L15 _public prototype_ `static const FLinearColor DefaultSpecular();`
- L16 _public prototype_ `static const FLinearColor DefaultAlbedo();`
- L17 _public prototype_ `static const FLinearColor DefaultMetalness();`
- L18 _public prototype_ `static const FLinearColor DefaultNormal();`
- L19 _public prototype_ `static const FLinearColor DefaultDisplacement();`
- L20 _public prototype_ `static const FLinearColor DefaultOpacity();`
- L21 _public prototype_ `static const FLinearColor DefaultRoughness();`
- L22 _public prototype_ `static const FLinearColor DefaultAO();`
- L23 _public prototype_ `static const FLinearColor DefaultCurvature();`
- L24 _public prototype_ `static const FLinearColor DefaultPreview();`
- L26 _public prototype_ `static float GetHue(const FColor& Color);`
- L27 _public prototype_ `static float GetSquaredDistance(FLinearColor Current, FLinearColor Match);`
- L28 _public prototype_ `static FString GetColorName(FLinearColor Color);`
- L30 _public prototype_ `static FLinearColor HSV2RGB(FLinearColor C);`
- L31 _public prototype_ `static FLinearColor RGB2HSV(FLinearColor C);`
- L32 _public prototype_ `static FLinearColor HSVTweak(FLinearColor C, float H, float S, float V);`
- L34 _public prototype_ `static bool IsColorBlack(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L35 _public prototype_ `static bool IsColorWhite(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L36 _public prototype_ `static bool IsColorGray(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L37 _public prototype_ `static bool IsColorRed(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L38 _public prototype_ `static bool IsColorGreen(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L39 _public prototype_ `static bool IsColorBlue(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L40 _public prototype_ `static bool IsColorYellow(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L41 _public prototype_ `static bool IsColorMagenta(const FLinearColor& Color, bool IgnoreAlpha = true);`
- L42 _public prototype_ `static bool IsColorNear(const FLinearColor& Color, const FLinearColor& Ref, bool IgnoreAlpha = true);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/DataUtil.h` (Other)


#### struct `DataUtil`  
`struct DataUtil`  
_L29-143_
- L31 _public member_ `static constexpr HashType GNullHash = 0;` — 0xDeadBeef;
- L35 _public member_ `static constexpr HashType GFNVPrime = 0x00000100000001B3;`
- L36 _public member_ `static const HashType GFNVInit = 0xcbf29ce484222325;`
- L39 _public member_ `static const size_t GMaxChunk = 16 * 1024;` — Don't change this ... EVER!
- L42 _public prototype_ `static HashType Hash(const uint8* data, size_t Length, HashType InitialHash = GFNVInit, HashType Prime = GFNVPrime);` — Calculate HashValue for one chunk of data
- L43 _public prototype_ `static HashType Hash_GenericString_Name(const FString& Name, HashType InitialHash = GFNVInit, HashType Prime = GFNVPrime);`
- L44 _public prototype_ `static HashType Hash(const HashTypeVec& SubHashes, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime);`
- L45 _public prototype_ `static HashType Hash(const CHashPtrVec& InSubHashes, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime);`
- L48 _public prototype_ `static HashType Hash_One(const uint8* Data, size_t Length, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime);` — Automatically decide whether to chunk the HashValue or not
- L49 _public prototype_ `static HashType Hash_Chunked(const uint8* data, size_t Length, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime);`
- L50 _public prototype_ `static size_t GetOptimalHashingSize(size_t Size);`
- L53 _public function_ `template <typename T> static HashType Hash_Simple(const T& Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L64 _public function_ `static HashType Hash_Simple(const FString& Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L69 _public function_ `static HashType Hash_Float(float Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L74 _public function_ `static HashType Hash_Int32(int32 Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L79 _public function_ `static HashType Hash_Double(double Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L84 _public function_ `static HashType Hash_Bool(bool Value, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L89 _public function_ `static HashType Hash_Simple(const FVector2D& Vec, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L99 _public function_ `static HashType Hash_Simple(const FVector& Vec, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L110 _public function_ `static HashType Hash_Simple(const FColor& Color, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L115 _public function_ `static HashType Hash_Simple(const FLinearColor& Color, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`
- L128 _public function_ `template <typename TKey, typename TValue> static HashType Hash_Simple(const TMap<TKey, TValue>& Map, HashType InitialValue = GFNVInit, HashType Prime = GFNVPrime)`

#### class `CHash`  
`class CHash : public std::enable_shared_from_this<CHash>`  
_L148-205_
- inherits: `std::enable_shared_from_this<CHash>`
- L151 _private member_ `HashType HashValue = DataUtil::GNullHash;` — The actual Value of the hash
- L152 _private member_ `CHashPtrVec HashSources;` — The sources used to construct this hash
- L153 _private member_ `bool bIsFinal = false;` — Whether this is a final (immutable hash)
- L154 _private member_ `CHashPtr TempHashValue;` — Whether there's a temporary HashValue attached with this HashValue
- L155 _private member_ `FDateTime Timestamp = FDateTime::Now();` — The timestamp of when this was last updated
- L162 _private member_ `CHashPtrWVec Linked;` — This structure represents a HashValue link. This is required for cases when a temp HashValue is used in the calculation of some other complex HashValue. When the temp HashValue finally resolves, we need to update the linked HashValues so that our look-ups to the, now old embedded HashValues is successful. otherwise we'll have no way of connecting complex-temp hashes to the correct hash and determine whether a job has already been done before or not
- L166 _private member_ `HashTypeVec IntermediateHashes;` — Intermediate hashes that might have been evaluated before this
- L169 _private function_ `FORCEINLINE bool HasTempDependency_Internal() const`
- L170 _private prototype_ `void AddLink(CHashPtrW Link);`
- L171 _private prototype_ `void CheckLinkCycles(std::unordered_set<CHashPtr>& Chain);`
- L172 _private prototype_ `void UpdateLinks();`
- L173 _private prototype_ `void HandleLinkUpdated(CHashPtr LinkUpdated);`
- L176 _private prototype_ `explicit CHash(const CHashPtrVec& Sources);` — DO NOT MAKE THIS C'TOR PUBLIC. Use ConstructFromSources instead
- L179 _public prototype_ `CHash(HashType Value, bool bInIsFinal);`
- L180 _public prototype_ `explicit CHash(CHashPtr Temp);`
- L182 _public prototype_ `bool TryFinalise(HashType FinalHash = DataUtil::GNullHash, bool UpdateBlobber = true);`
- L183 _public prototype_ `bool operator == (const CHash& RHS) const;`
- L184 _public prototype_ `HashTypeVec GetIntermediateHashes() const;`
- L186 _public prototype_ `static CHashPtr ConstructFromSources(const CHashPtrVec& Sources);`
- L187 _public prototype_ `static CHashPtr UpdateHash(CHashPtr NewHash, CHashPtr PrevHash);`
- L192 _public function_ `FORCEINLINE bool IsNull() const`
- L193 _public function_ `FORCEINLINE bool IsValid() const`
- L194 _public function_ `FORCEINLINE HashType Value() const`
- L195 _public function_ `FORCEINLINE operator HashType() const`
- L196 _public function_ `FORCEINLINE bool IsFinal() const`
- L197 _public function_ `FORCEINLINE const FDateTime& GetTimestamp() const`
- L198 _public function_ `FORCEINLINE bool HasUpdatedSince(FDateTime timestamp) const`
- L199 _public function_ `FORCEINLINE bool IsTemp() const`
- L200 _public function_ `FORCEINLINE CHashPtr Temp() const`
- L201 _public function_ `FORCEINLINE bool HasTempDependency() const`
- L202 _public function_ `FORCEINLINE const CHashPtrVec& Sources() const`
- L203 _public function_ `FORCEINLINE size_t NumSources() const`
- L204 _public function_ `FORCEINLINE bool IsTempFinal() const`

#### class `T_Tiles`  
`template <typename Type> class T_Tiles`  
_L214-272_
- L217 _public typedef_ `typedef std::vector<Type> TypeVec;`
- L220 _protected member_ `TypeVec TilesVec;` — The tiles
- L221 _protected member_ `size_t NumRows = 0;` — Number of rows
- L222 _protected member_ `size_t NumCols = 0;` — Number of columns
- L225 _public prototype_ `T_Tiles() = default;`
- L226 _public function_ `T_Tiles(size_t InNumRows, size_t InNumCols) : NumRows(InNumRows), NumCols(InNumCols)`
- L232 _public function_ `T_Tiles(const TypeVec& RHS, size_t InNumRows, size_t InNumCols) : TilesVec(RHS) , NumRows(InNumRows) , NumCols(InNumCols)`
- L239 _public function_ `void Resize(size_t InNumRows, size_t InNumCols)`
- L247 _public function_ `FORCEINLINE size_t Length() const`
- L250 _public function_ `template<typename Functor> FORCEINLINE void ForEach(Functor Func) const`
- L263 _public function_ `FORCEINLINE const Type* operator[](size_t RowId) const`
- L264 _public function_ `FORCEINLINE Type* operator[](size_t RowId)`
- L265 _public function_ `FORCEINLINE const Type& operator()(size_t RowId, size_t ColId) const`
- L266 _public function_ `FORCEINLINE Type& operator()(size_t RowId, size_t ColId)`
- L267 _public function_ `FORCEINLINE size_t Rows() const`
- L268 _public function_ `FORCEINLINE size_t Cols() const`
- L269 _public function_ `FORCEINLINE const TypeVec& Tiles() const`
- L270 _public function_ `FORCEINLINE TypeVec& Tiles()`
- L271 _public function_ `FORCEINLINE void Clear()`

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef uint64 HashType;`
- L11 _typedef_ `typedef std::vector<HashType> HashTypeVec;`
- L12 _typedef_ `typedef std::list<HashType> HashTypeList;`
- L15 _typedef_ `typedef std::shared_ptr<CHash> CHashPtr;`
- L16 _typedef_ `typedef std::weak_ptr<CHash> CHashPtrW;`
- L17 _typedef_ `typedef std::vector<CHashPtr> CHashPtrVec;`
- L18 _typedef_ `typedef std::vector<CHashPtrW> CHashPtrWVec;`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogData, Log, All);` — struct HashType { uint64							HashValue;			/// The actual HashValue Value };
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogData, Log, All);` — struct HashType { uint64							HashValue;			/// The actual HashValue Value };
- L26 _macro_ `#define MX_HASH_VAL(HashValue, Prime, val) ((HashValue * Prime) ^ (val))`
- L27 _macro_ `#define MX_HASH_VAL_DEF(val) MX_HASH_VAL(DataUtil::GFNVInit, DataUtil::GFNVPrime, (HashType)val)`
- L210 _typedef_ `typedef cti::continuable<CHashPtr> AscynCHashPtr;`
- L274 _typedef_ `using TileInvalidateMatrix = T_Tiles<int32>;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/GraphicsUtil.h` (Other)


#### enum `BoundsCorners`  
`enum class BoundsCorners`  
_L11-22_
- L13 _public enumerator_ `L0_BottomLeft`
- L14 _public enumerator_ `L0_TopLeft`
- L15 _public enumerator_ `L0_TopRight`
- L16 _public enumerator_ `L0_BottomRight`
- L18 _public enumerator_ `L1_BottomLeft`
- L19 _public enumerator_ `L1_TopLeft`
- L20 _public enumerator_ `L1_TopRight`
- L21 _public enumerator_ `L1_BottomRight`

#### class `GraphicsUtil`  
`class GraphicsUtil`  
_L24-62_
- L27 _public prototype_ `static Vector2 CalculateBarycentricCoordinates(const Vector2* UV, const Vector2& P);`
- L28 _public prototype_ `static Vector2 CalculateBarycentricCoordinates(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P);`
- L30 _public prototype_ `static bool IsPointInTriangle(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& P);`
- L31 _public prototype_ `static bool IsPointInTriangle(float u, float v, float tolerance = 0.001f);`
- L32 _public prototype_ `static bool IsPointInTriangle(const Vector2& uv, float tolerance = 0.001f);`
- L35 _public member_ `static Vector3 s_boundsAxis[6];`
- L36 _public prototype_ `static float SquaredDistance(const Vector3& p0, const Vector3& p1);`
- L37 _public prototype_ `static float SquaredLength(const Vector3& pt);`
- L39 _public prototype_ `static std::array<Vector3, 8> GetBoundsCorners(const FBox& bounds);`
- L41 _public prototype_ `static Vector3 GetBoundsPoint(const FBox& bounds, BoundsCorners pti);`
- L42 _public prototype_ `static FBox GetChildBounds_QuadTree(const FBox& bounds, BoundsCorners ci);`
- L43 _public prototype_ `static FBox GetChildBounds_Octree(const FBox& bounds, BoundsCorners ci);`
- L44 _public prototype_ `static bool CheckRayTriangleIntersection(const FRay& ray, const Vector3& p1, const Vector3& p2, const Vector3& p3, float& distance, Vector3& ip);`
- L46 _public function_ `static FORCEINLINE Vector4 ConvertTangent(const Tangent& t)`
- L47 _public function_ `static FORCEINLINE FLinearColor TangentAsLinearColor(const Tangent& t)`
- L48 _public function_ `static FORCEINLINE FLinearColor Vec2AsLinearColor(const Vector2& v)`
- L49 _public function_ `static FORCEINLINE FLinearColor Vec2AsLinearColor(const FVector2f& v)`
- L50 _public function_ `static FORCEINLINE FLinearColor Vec3AsLinearColor(const Vector3& v)`
- L51 _public function_ `static FORCEINLINE FLinearColor Vec4AsLinearColor(const Vector4& v)`
- L55 _public function_ `template <typename VecType> static VecType Interpolate(const VecType& v0, const VecType& v1, const VecType& v2, Vector2 barycentric)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/MathUtils.h` (Other)


#### class `MathUtils`  
`class MathUtils`  
_L10-29_
- L13 _public prototype_ `MathUtils() = delete;`
- L15 _public member_ `static const float GMeterToCm;`
- L17 _public prototype_ `static float MinFloat();`
- L18 _public prototype_ `static float MaxFloat();`
- L20 _public prototype_ `static FVector MinFVector();`
- L21 _public prototype_ `static FVector MaxFVector();`
- L22 _public prototype_ `static FVector2f MinFVector2();`
- L23 _public prototype_ `static FVector2f MaxFVector2();`
- L24 _public prototype_ `static void UpdateBounds(FBox& bounds, const FVector& point);`
- L25 _public prototype_ `static void EncapsulateBound(FBox& bounds, FBox& otherBounds);`
- L26 _public prototype_ `static FVector GetDirection(float yzAngle, float xAngle, int xSign = 1);`
- L27 _public prototype_ `static FBox GetCombinedBounds(TArray<FBox> inputBounds);`
- L28 _public prototype_ `static float Step(float Y, float X);`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/Promise.h` (Other)


#### struct `ActionResult`  
`struct ActionResult`  
_L17-28_
- desc: This is temporary and will eventually go away
- L19 _public member_ `std::exception_ptr ExInner;` — Original exception that was raised by the action
- L20 _public member_ `int32 ErrorCode = 0;` — What is the error code
- L22 _public member_ `TMap<FString, FString> Metadata;` — Additional metadata that may be associated with an action result.
- L25 _public function_ `explicit ActionResult(std::exception_ptr Ex = nullptr, int32 ErrCode = 0) : ExInner(Ex), ErrorCode(ErrCode)`
- L27 _public function_ `FORCEINLINE bool IsOK() const`

#### struct `PromiseUtil`  
`struct PromiseUtil`  
_L34-119_
- L39 _public prototype_ `static auto OnThread(ENamedThreads::Type ThreadType);`
- L45 _public function_ `template<typename T> static FORCEINLINE cti::continuable<T> OnThread(ENamedThreads::Type ThreadType, T&& Args)`
- L57 _public function_ `template<typename T> static cti::continuable<T> WrapResolvePromiseOnThread(ENamedThreads::Type ThreadType, TUniqueFunction<cti::continuable<T>()> callback)`
- L71 _public function_ `static AsyncInt OnBackgroundThread()`
- L82 _public function_ `static AsyncInt OnGameThread()`
- L97 _public function_ `template<typename T> static cti::continuable<T> OnGameThread(T&& Arg)`
- L106 _public function_ `static AsyncInt OnRenderingThread()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _typedef_ `typedef cti::continuable<int32> AsyncInt;`
- L30 _typedef_ `typedef std::shared_ptr<ActionResult> ActionResultPtr;`
- L31 _typedef_ `typedef cti::continuable<ActionResultPtr> AsyncActionResultPtr;`
- L48 _function_ `` (scope `PromiseUtil::OnThread`)
- L50 _function_ `` (scope `PromiseUtil::OnThread::__anon548249e50102`)
- L60 _function_ `` (scope `PromiseUtil::WrapResolvePromiseOnThread`)
- L62 _function_ `` (scope `PromiseUtil::WrapResolvePromiseOnThread::__anon548249e50302`)
- L64 _function_ `` (scope `PromiseUtil::WrapResolvePromiseOnThread::__anon548249e50302::__anon548249e50402`)
- L74 _function_ `` (scope `PromiseUtil::OnBackgroundThread`)
- L76 _function_ `` (scope `PromiseUtil::OnBackgroundThread::__anon548249e50602`)
- L88 _function_ `` (scope `PromiseUtil::OnGameThread`)
- L90 _function_ `` (scope `PromiseUtil::OnGameThread::__anon548249e50802`)
- L112 _function_ `` (scope `PromiseUtil::OnRenderingThread`)
- L114 _function_ `` (scope `PromiseUtil::OnRenderingThread::__anon548249e50a02`)
- L121 _macro_ `#define FWD_PROMISE(p) p = std::forward<decltype(p)>(p)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Helper/Util.h` (Other)


#### enum `E_Priority`  
`enum class E_Priority`  
_L13-21_
- L15 _public enumerator_ `kLowest = 0`
- L16 _public enumerator_ `kLow = 25`
- L17 _public enumerator_ `kNormal = 50`
- L18 _public enumerator_ `kHigh = 10000`
- L19 _public enumerator_ `kHighest = 100000`
- L20 _public enumerator_ `kSystem = 1000000`

#### struct `DirectoryVisitor`  
`struct DirectoryVisitor : public IPlatformFile::FDirectoryVisitor`  
_L23-48_
- inherits: `IPlatformFile::FDirectoryVisitor`
- L25 _public member_ `uint64 FileCount = 0;`
- L26 _public member_ `uint64 TotalSize = 0;`
- L27 _public member_ `uint64 FolderCount = 0;`
- L28 _public member_ `bool StoreFilenames = false;`
- L29 _public member_ `TArray<FString> FilePaths;`
- L32 _public function_ `virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override` — This function is called for every file or directory it finds.

#### struct `Util`  
`struct Util`  
_L54-127_
- L56 _public member_ `static constexpr int32 GDefaultWidth = 1024;`
- L57 _public member_ `static constexpr int32 GDefaultHeight = 1024;`
- L62 _public prototype_ `static UObject* GetModelPackage();`
- L63 _public prototype_ `static UObject* GetTexturesPackage();`
- L64 _public prototype_ `static UObject* GetRenderTargetPackage();`
- L65 _public prototype_ `static UObject* GetMegascansTexturesPackage();`
- L66 _public prototype_ `static UObject* GetMaterialsPackage();`
- L71 _public function_ `static FORCEINLINE FString GetRuntimeTexturesPackagePath()`
- L72 _public function_ `static FORCEINLINE FString GetRenderTargetPackagePath()`
- L73 _public function_ `static FORCEINLINE FString GetRuntimeTexturesPackagePath(FString suffix)`
- L74 _public function_ `static FORCEINLINE FString GetRuntimeTexturesPackagePath(const char* suffix)`
- L76 _public prototype_ `static bool IsFileValid(const FString& FileName);`
- L77 _public prototype_ `static bool IsDirectory(const FString& Path);`
- L78 _public prototype_ `static bool IsDirectoryEmpty(const FString& Path);`
- L83 _public prototype_ `static void OnGameThread(TUniqueFunction<void()> Callback);`
- L84 _public prototype_ `static void OnRenderingThread(TUniqueFunction<void(FRHICommandListImmediate&)> Callback);`
- L85 _public prototype_ `static void OnBackgroundThread(TUniqueFunction<void()> Callback);`
- L86 _public prototype_ `static void OnAnyThread(TUniqueFunction<void()> Callback);`
- L87 _public prototype_ `static void OnThread(ENamedThreads::Type thread, TUniqueFunction<void()> Callback);`
- L88 _public prototype_ `static size_t GetCurrentThreadId();`
- L91 _public prototype_ `static FRHICommandListImmediate& RHIImmediate();` — `UE_DEPRECATED(5.8, "Util::RHIImmediate() is deprecated. Use FRHICommandListImmediate::Get() instead.")`
- L96 _public prototype_ `static const FWorldContext* GetGameWorldContext();`
- L97 _public prototype_ `static UWorld* GetGameWorld();`
- L98 _public prototype_ `static void* GetOSWindowHandle();`
- L99 _public prototype_ `static FString RandomID();`
- L100 _public prototype_ `static FString ToPascalCase(const FString& strToConvert);`
- L101 _public function_ `static FORCEINLINE double Time()`
- L102 _public function_ `static FORCEINLINE double TimeDelta(double start)`
- L118 _public function_ `template<typename T> static FString EnumToString(const T EnumValue)` — Convert the value of an enum to a string. @param EnumValue The enumerated type value to convert to a string. @return The key/name that corresponds to the value in the enumerated type.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/BlobHasherService.h` (Other)


#### class `BlobHasherService`  
`class BlobHasherService : public BlobHelperService`  
_L10-18_
- inherits: `BlobHelperService`
- L13 _public prototype_ `BlobHasherService();`
- L16 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`
- L17 _public prototype_ `virtual void Add(BlobRef BlobObj) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L20 _typedef_ `typedef std::shared_ptr<BlobHasherService> BlobHasherServicePtr;`
- L21 _typedef_ `typedef std::weak_ptr<BlobHasherService> BlobHasherServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/BlobHelperService.h` (Other)


#### class `BlobHelperService`  
`class BlobHelperService : public IdleService`  
_L10-22_
- inherits: `IdleService`
- L13 _protected member_ `std::vector<BlobPtr> Blobs;` — The blobs that we want to hash
- L16 _public prototype_ `explicit BlobHelperService(const FString& InName);`
- L19 _public prototype_ `virtual void Stop() override;`
- L21 _public prototype_ `virtual void Add(BlobRef BlobObj);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/DeviceTransferService.h` (Other)


#### class `DeviceTransferService`  
`class DeviceTransferService : public IdleService`  
_L12-42_
- inherits: `IdleService`
- L15 _protected member_ `static constexpr int GMaxFlush = 32;` — Size is chosen so that TransferInfo
- L30 _protected member_ `Transfers;` — The current transfers that we're working on
- L33 _public prototype_ `DeviceTransferService();`
- L36 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`
- L37 _public prototype_ `virtual void Stop() override;`
- L38 _public function_ `virtual bool ShouldRunDuringBusyUpdate() const override`
- L40 _public prototype_ `virtual void QueueTransfer(BlobPtr BlobObj, Device* TargetDevice);`
- L41 _public prototype_ `virtual void AbortTransfer(HashType HashValue);`

#### struct `DeviceTransferService::TransferInfo`  
`struct TransferInfo`  
_L17-27_
- L19 _public member_ `Device* OwnerDevice = nullptr;` — The owner device at the time when this blob was market for collection
- L20 _public member_ `BlobPtr BlobObj;` — The blob that needs to be transferred
- L21 _public member_ `Device* TargetDevice = nullptr;` — The device that we're transferring this to
- L23 _public member_ `AccessInfo Access;` — This is a snapshot of the access info we save at the time the blob

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTransfer_Svc, Log, Verbose);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTransfer_Svc, Log, Verbose);`
- L44 _typedef_ `typedef std::shared_ptr<DeviceTransferService> DeviceTransferServicePtr;`
- L45 _typedef_ `typedef std::weak_ptr<DeviceTransferService> DeviceTransferServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/HistogramService.h` (Other)


#### class `HistogramService`  
`class HistogramService : public IdleService`  
_L17-34_
- inherits: `IdleService`
- L20 _private member_ `JobBatchPtr Batch;`
- L21 _private member_ `bool bCaptureNextBatch = false;`
- L24 _public prototype_ `HistogramService();`
- L27 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`
- L28 _public prototype_ `virtual void Stop() override;`
- L30 _public prototype_ `void AddHistogramJob(MixUpdateCyclePtr Cycle,JobUPtr JobToAdd, int32 TargetID, UMixInterface* Mix);`
- L31 _public prototype_ `JobBatchPtr GetOrCreateNewBatch(UMixInterface* mix);`
- L33 _public prototype_ `void CaptureNextBatch();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L11 _typedef_ `typedef std::shared_ptr<class Job> JobPtr;`
- L12 _typedef_ `typedef std::unique_ptr<class Job> JobUPtr;`
- L13 _typedef_ `typedef std::weak_ptr<class Job> JobPtrW;`
- L36 _typedef_ `typedef std::shared_ptr<HistogramService> HistogramServicePtr;`
- L37 _typedef_ `typedef std::weak_ptr<HistogramService> HistogramServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/IdleService.h` (Other)


#### class `IdleService`  
`class IdleService`  
_L11-44_
- L25 _protected member_ `FString Name;` — The name of this idle batch. Used primarily for debugging purposes and logging
- L27 _protected member_ `FCriticalSection StatsMutex;` — Mutex for the stats object
- L28 _protected member_ `Stats StatsData;` — The stats for this idle batch
- L31 _public function_ `explicit IdleService(const FString& InName) : Name(InName)`
- L32 _public prototype_ `virtual ~IdleService() = default;`
- L33 _public prototype_ `virtual AsyncJobResultPtr Tick() = 0;`
- L34 _public prototype_ `virtual void Stop() = 0;`
- L35 _public function_ `virtual bool ShouldRunDuringBusyUpdate() const`
- L37 _public prototype_ `void UpdateStats(double StartTime, double EndTime, bool DidOffendTimeLimit);`
- L42 _public function_ `FORCEINLINE const Stats& GetStats() const`
- L43 _public function_ `FORCEINLINE const FString& GetName() const`

#### struct `IdleService::Stats`  
`struct Stats`  
_L14-22_
- L16 _public member_ `double LastTick = 0;` — Time when this batch was last updated
- L17 _public member_ `double LastTickDuration = 0;` — Time taken during the last tick
- L18 _public member_ `double TotalTickDuration = 0;` — Total tick duration
- L19 _public member_ `double AverageTickDuration = 0;` — Average duration of the tick
- L20 _public member_ `size_t NumTicks = 0;` — The number of times this has been ticked
- L21 _public member_ `size_t NumTimeLimitOffenses = 0;` — How many times this batch offended the time limit

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIdle_Svc, Log, Verbose);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIdle_Svc, Log, Verbose);`
- L46 _typedef_ `typedef std::shared_ptr<IdleService> IdleServicePtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/Job.h` (Other)


#### class `Job`  
`class Job : public DeviceNativeTask`  
_L23-217_
- inherits: `DeviceNativeTask`
- L40 _protected typedef_ `typedef T_Tiles<JobResultPtr> JobResultPtrTiles;`
- L42 _protected member_ `UMixInterface* MixObj = nullptr;` — The mix that this job belongs to
- L43 _protected member_ `int64 Id = -1;` — Unique ID for the job [-1 means it was unassigned]
- L44 _protected member_ `int32 QueueId = -1;` — ID of the queue that this job belongs to
- L45 _protected member_ `TArray<JobArgPtr> Args;` — The arguments for the job
- L46 _protected member_ `BlobTransformPtr Transform;` — The transformation that we'll be doing for the job
- L47 _protected member_ `FWeakObjectPtr ErrorOwner;` — Error owner is an object associated with any error reported to the TextureGraphEngine::ErrorReporter during this job execution
- L48 _protected member_ `mutable CHashPtr HashValue = nullptr;` — What is the hash of this job
- L49 _protected member_ `TiledBlob_PromisePtr ResultOrg;` — The original result that was created
- L50 _protected member_ `TiledBlobRef Result;` — The rendering result of this job
- L51 _protected member_ `BufferDescriptorPtr DesiredResultDesc;` — Desired descriptor for the result
- L52 _protected member_ `JobResultPtrTiles TileResults;` — The results for all the tiles
- L53 _protected member_ `JobResultPtr FinalJobResult;` — The overall result info for this job
- L55 _protected member_ `JobPArray Parents;` — [upstream] Jobs that this job is dependent on
- L56 _protected member_ `JobPtrArray Children;` — [downstream] Jobs that are dependent on this job
- L58 _protected member_ `int32 TargetId = -1;` — What is our target
- L60 _protected member_ `TileInvalidateMatrix TileInvalidationMatrix;` — The tiles that were actually invalidated
- L62 _protected member_ `BufferDescriptor TileDesc;` — The descriptor for each tile
- L64 _protected member_ `FCriticalSection Mutex;` — For preventing shared table writes
- L65 _protected member_ `JobRunInfo RunInfo;` — The run info that was saved when it was passed as argument
- L67 _protected member_ `JobStats Stats;` — Job timing stats collected during execution
- L69 _protected member_ `const RenderMesh* Mesh = nullptr;` — The mesh that we're targeting
- L71 _protected member_ `int32 ReplayCount = 0;` — Counting the number of debug replay of this job
- L72 _protected member_ `bool bIsNoCache = false;` — Whether we should ignore the cache
- L73 _protected member_ `bool bIsTiled = true;` — Whether the job runs in tiled mode or not. You can override this and force the job to run in non-tiled mode
- L75 _protected member_ `JobPtrVec JobsGeneratedPrior;` — [Prior] The jobs that were generated from this job
- L76 _protected member_ `JobPtrVec JobsGeneratedAfter;` — [After] The jobs that were generated from this job
- L78 _protected member_ `JobPtrW Generator;` — The job that generated this job. This is useful in certain situations
- L79 _protected member_ `FString DebugJobName;` — The name of the job
- L83 _protected typedef_ `typedef std::pair<int32, int32> IndexPair;`
- L84 _protected typedef_ `typedef TMap<HashType, IndexPair> JobLUT;`
- L87 _protected prototype_ `virtual AsyncJobArgResultPtr BindArgs(JobRunInfo NewRunInfo, BlobTransformPtr TransformObj, int32 RowId, int32 ColId);` — Binds/Unbinds args for individual tiles or the entire blob if its a non-tiled job
- L88 _protected prototype_ `virtual AsyncJobArgResultPtr UnbindArgs(JobRunInfo NewRunInfo, BlobTransformPtr TransformObj, int32 RowId, int32 ColId);`
- L91 _protected prototype_ `virtual AsyncInt BindArgs_All(JobRunInfo RunInfo);` — Binds/Unbinds args for all the tiles at once and returns a promise
- L92 _protected prototype_ `virtual AsyncInt UnbindArgs_All(JobRunInfo RunInfo);`
- L94 _protected typedef_ `typedef std::function <AsyncJobArgResultPtr(JobRunInfo, BlobTransformPtr, int32, int32)> Bind_Unbind_Func;`
- L95 _protected prototype_ `virtual AsyncInt Bind_Or_Unbind_All_Generic(JobRunInfo NewRunInfo, Bind_Unbind_Func BFunc);`
- L97 _protected prototype_ `virtual AsyncJobResultPtr RunTile(JobRunInfo RunInfo, int32 RowId, int32 ColId);`
- L98 _protected prototype_ `virtual AsyncJobResultPtr RunSingle(JobRunInfo RunInfo);`
- L99 _protected prototype_ `virtual AsyncJobResultPtr FinaliseTiles(JobRunInfo RunInfo);`
- L100 _protected prototype_ `void SetTileResult(int32 RowId, int32 ColId, JobResultPtr TileResult);`
- L101 _protected prototype_ `virtual AsyncPrepareResult PrepareTargets(JobBatch* batch);`
- L103 _protected prototype_ `AsyncTransformResultPtr ExecTransform(JobRunInfo RunInfo, BlobTransformPtr TransformObj , int32 RowId, int32 ColId, CHashPtr jobHash);`
- L104 _protected prototype_ `virtual void MarkJobDone();`
- L105 _protected prototype_ `virtual bool IsDiscard() const;`
- L110 _protected prototype_ `virtual AsyncJobResultPtr Run(JobRunInfo RunInfo);`
- L111 _protected prototype_ `virtual AsyncPrepareResult PrepareResources(JobBatch* batch);`
- L113 _protected prototype_ `virtual bool CheckCached();`
- L114 _protected prototype_ `BufferDescriptor GetResultDesc() const;`
- L115 _protected prototype_ `BufferDescriptor GetCombinedDesc(BufferDescriptor& ArgsDescCombined, size_t& Count) const;`
- L118 _public prototype_ `Job(int32 TargetId, BlobTransformPtr InTransform, UObject* ErrorOwner = nullptr, uint16 InPriority = (uint16)E_Priority::kNormal, uint64 InId = -1);`
- L119 _public prototype_ `Job(UMixInterface* InMix, int32 TargetId, BlobTransformPtr Transform, UObject* ErrorOwner = nullptr, uint16 priority = (uint16)E_Priority::kNormal, uint64 id = -1);`
- L123 _public prototype_ `virtual Job* SetArgs(const TArray<JobArgPtr>& NewArgs);`
- L124 _public prototype_ `virtual Job* AddArg(JobArgPtr Arg);`
- L125 _public prototype_ `uint32_t NumArgs() const;`
- L126 _public prototype_ `JobArgPtr GetArg(uint32_t Index) const;`
- L127 _public prototype_ `virtual void AddResultToBlobber();`
- L129 _public prototype_ `virtual CHashPtr Hash() const;`
- L130 _public prototype_ `virtual CHashPtr TileHash(int32 RowId, int32 ColId) const;`
- L131 _public prototype_ `virtual CHashPtr CalcTileHash(int32 RowId, int32 ColId) const;`
- L132 _public prototype_ `virtual bool CanHandleTiles() const;`
- L133 _public prototype_ `virtual bool CheckDefaultArgs() const;`
- L135 _public prototype_ `virtual TiledBlobPtr InitResult(FString NewName, const BufferDescriptor* InDesiredDesc, int32 NumTilesX = 0, int32 NumTilesY = 0);`
- L137 _public prototype_ `void ResetForReplay(bool noCache);` — For debug purpose, reset the job so it can be replayed
- L144 _public prototype_ `virtual AsyncInt BeginNative(JobRunInfo RunInfo);`
- L145 _public prototype_ `virtual AsyncJobResultPtr EndNative();`
- L151 _protected prototype_ `virtual TiledBlobPtr InitLateBoundResult(FString NewName, BufferDescriptor DesiredDesc, size_t NumInputBlobs);`
- L153 _protected prototype_ `virtual AsyncInt PreExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type ReturnThread) override;`
- L154 _protected prototype_ `virtual int32 Exec() override;`
- L155 _protected prototype_ `virtual void PostExec() override;`
- L156 _protected prototype_ `virtual AsyncInt ExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type ReturnThread) override;`
- L157 _protected prototype_ `virtual JobPtrVec GetArgDependencies();`
- L160 _public prototype_ `virtual Device* GetTargetDevice() const override;`
- L161 _public prototype_ `virtual ENamedThreads::Type GetExecutionThread() const override;`
- L162 _public prototype_ `virtual bool IsAsync() const override;`
- L163 _public prototype_ `bool GetTileInvalidation(int32 RowId, int32 ColId) const;`
- L165 _public prototype_ `virtual void GetDependencies(JobPtrVec& Prior, JobPtrVec& After, JobRunInfo RunInfo);`
- L167 _public prototype_ `virtual FString GetName() const override;`
- L169 _public prototype_ `virtual bool DebugCompleteCheck() override;`
- L174 _public prototype_ `virtual bool CheckCulled(JobRunInfo RunInfo);`
- L175 _public prototype_ `virtual FString GetRunTimings(double BatchStartTime) const;`
- L176 _public prototype_ `virtual FString GetDebugName() const override;`
- L181 _public function_ `FORCEINLINE int64 GetJobId() const`
- L182 _public function_ `FORCEINLINE void SetJobId(int64 NewJobId)`
- L183 _public function_ `FORCEINLINE int32 GetQueueId() const`
- L184 _public function_ `FORCEINLINE void SetQueueId(int32 NewQueueId)`
- L185 _public function_ `FORCEINLINE BlobTransformPtr GetTransform() const`
- L186 _public function_ `FORCEINLINE TiledBlobRef GetResult() const`
- L188 _public function_ `FORCEINLINE bool GetTiled() const`
- L189 _public function_ `FORCEINLINE Job* SetTiled(bool bTiled)`
- L191 _public function_ `FORCEINLINE JobStats GetStats() const`
- L193 _public function_ `FORCEINLINE const JobRunInfo& GetRunInfo() const`
- L194 _public function_ `FORCEINLINE const RenderMesh* GetMesh() const`
- L195 _public function_ `FORCEINLINE void SetMesh(RenderMesh* NewMesh)`
- L196 _public function_ `FORCEINLINE JobResultPtr GetTileResult(int32 RowId, int32 ColId) const`
- L203 _public function_ `FORCEINLINE int32 GetReplayCount() const` — For debug purpose, report the replay number
- L204 _public function_ `FORCEINLINE int32 GetTargetId() const`
- L206 _public function_ `FORCEINLINE JobPtrVec& GeneratedPriorJobs()`
- L207 _public function_ `FORCEINLINE JobPtrVec& GeneratedAfterJobs()`
- L208 _public function_ `FORCEINLINE const JobPtrW& GeneratorJob() const`
- L210 _public function_ `FORCEINLINE UMixInterface* GetMix() const`
- L211 _public function_ `FORCEINLINE void SetMix(UMixInterface* mix)`
- L213 _public function_ `FORCEINLINE BlobRef GetResultRef() const`
- L214 _public function_ `FORCEINLINE TiledBlob_PromisePtr GetResultPromise() const`
- L216 _public function_ `FORCEINLINE UObject* GetErrorOwner() const`

#### struct `Job::JobStats`  
`struct JobStats`  
_L26-37_
- L28 _public member_ `double BeginNativeTime = 0.0;` — The timestamp [ms] when this job started
- L29 _public member_ `double EndNativeTime = 0.0;` — The timestamp [ms] when this job ended
- L30 _public member_ `double BeginRunTime = 0.0;` — The timestamp [ms] when this job RUN is started
- L31 _public member_ `double EndRunTime = 0.0;` — The timestamp [ms] when this job RUN has ended
- L33 _public member_ `double TargetPrepStartTime = 0;` — The timestamp [ms] when this job PrepareTargets was run
- L34 _public member_ `double TargetPrepEndTime = 0;` — The timestamp [ms] when this job PrepareTargets has ended
- L35 _public member_ `double TargetPrepWaitStartTime = 0;` — The timestamp [ms] when this job started waiting for targets to be prepared (all promises to return from Device)
- L36 _public member_ `double TargetPrepWaitEndTime = 0;` — The timestamp [ms] when this job when the waiting of promises has finished

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogJob, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJob, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/JobArgs.h` (Other)


#### struct `JobArgResult`  
`struct JobArgResult`  
_L21-25_
- L23 _public member_ `std::exception_ptr ExInner;` — Original exception that was raised by the action
- L24 _public member_ `int32 ErrorCode = 0;` — What is the error code

#### struct `JobArgBindInfo`  
`struct JobArgBindInfo`  
_L31-41_
- L33 _public member_ `Job* JobObj = nullptr;` — The job that this is associated with
- L34 _public member_ `const JobBatch* Batch = nullptr;` — What is the batch that we're going to be part of (can be nullptr)
- L35 _public member_ `size_t JobIndex = 0;` — The index of this job
- L36 _public member_ `int32 RowId = -1;` — The row index that we're binding for or -1 if it needs to be bound as one
- L37 _public member_ `int32 ColId = -1;` — The col index tile that we're binding for or -1 if it needs to be bound as one
- L38 _public member_ `Device* Dev = nullptr;` — The device to which this is going to be bound to
- L39 _public member_ `BlobTransformPtr Transform;` — The transformation function to which the argument will be bound
- L40 _public member_ `uint32 LODLevel = 0;` — What is the lod level that we'll be binding this to

#### class `JobArg`  
`class JobArg`  
_L44-83_
- L47 _protected member_ `bool bIgnoreDesc = false;` — Whether to ignore the descriptor for this argument
- L49 _protected member_ `bool bIgnoreHash = false;` — when combining descriptors during merge
- L50 _protected member_ `bool bUnbound = false;` — Sometimes you need to add an argument for hashing calculation
- L54 _public prototype_ `virtual ~JobArg() = default;`
- L55 _public prototype_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) = 0;`
- L56 _public prototype_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) = 0;`
- L57 _public prototype_ `virtual bool CanHandleTiles() const;`
- L58 _public prototype_ `virtual bool ForceNonTiledTransform() const;`
- L60 _public prototype_ `virtual CHashPtr Hash() const = 0;`
- L61 _public prototype_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const = 0;`
- L63 _public function_ `virtual CHashPtr Hash_Default() const`
- L64 _public function_ `virtual CHashPtr TileHash_Default(uint32 TileX, uint32 TileY) const`
- L65 _public function_ `virtual bool IsDefault() const`
- L67 _public function_ `virtual JobPtrW GeneratingJob() const`
- L68 _public function_ `virtual const BufferDescriptor* GetDescriptor() const`
- L69 _public function_ `virtual bool IsLateBound(uint32 TileX, uint32 TileY) const`
- L70 _public function_ `virtual bool IsBlob() const`
- L75 _public function_ `FORCEINLINE bool IgnoreHash() const`
- L76 _public function_ `FORCEINLINE void WithIgnoreHash(bool ignoreHash)`
- L78 _public function_ `FORCEINLINE bool Unbounded() const`
- L79 _public function_ `FORCEINLINE void WithUnbounded(bool unbounded)`
- L81 _public function_ `FORCEINLINE bool IgnoreDesc() const`
- L82 _public function_ `FORCEINLINE void WithIgnoreDesc(bool ignoreDesc)`

#### class `JobArg_Resource`  
`class JobArg_Resource : public JobArg`  
_L90-98_
- inherits: `JobArg`
- L93 _protected member_ `ResourceBindInfo ArgBindInfo;` — Binding information for this resource
- L96 _public function_ `JobArg_Resource(const ResourceBindInfo& BindInfo) : ArgBindInfo(BindInfo)`
- L97 _public function_ `JobArg_Resource(const char* TargetName) : ArgBindInfo({ FString(TargetName) })`

#### class `JobArg_Blob`  
`class JobArg_Blob : public JobArg_Resource`  
_L101-154_
- inherits: `JobArg_Resource`
- L104 _protected member_ `mutable TiledBlobRef BlobObjRef;` — Blob Cached between Bind and Unbind calls only
- L105 _protected member_ `bool bCanHandleTiles = true;` — Instead of providing a tile for associated blob, whole blob will be fed in the parameter
- L106 _protected member_ `bool bForceNonTiledTransform = false;` — Will force turn associated job to use Non Tiled mode (previously this was being done through canHandleTiles)
- L108 _protected member_ `bool bBindDownsampled4To1 = false;` — Bind the arg raster tile(s) in order to achieve the 4 to 1 downsampling per invocation
- L111 _protected member_ `bool bBindNeighborTiles = false;` — Bind the tile and the rign of neighbors in order to be able to go fetch border information OUT of the current tile bound
- L113 _protected member_ `bool bBindArrayOfTiles = false;` — Bind ALL the tiles contained in this arg, filling the array of UTextures before execution of the job.
- L116 _protected prototype_ `TiledBlobPtr GetRootBlob(JobArgBindInfo JobBindInfo) const;`
- L119 _public prototype_ `JobArg_Blob(TiledBlobPtr blob, const ResourceBindInfo& BindInfo);`
- L120 _public prototype_ `JobArg_Blob(TiledBlobPtr BlobObj, const char* TargetName);`
- L123 _public prototype_ `virtual void SetHandleTiles(bool bInCanHandleTiles);`
- L124 _public prototype_ `virtual bool CanHandleTiles() const override;`
- L125 _public prototype_ `JobArg_Blob& WithNotHandleTiles();` — equivalent to call  SetHandleTiles(false)
- L128 _public prototype_ `virtual void SetForceNonTiledTransform(bool bInForceNonTiledTransform);`
- L129 _public prototype_ `virtual bool ForceNonTiledTransform() const override;`
- L131 _public prototype_ `JobArg_Blob& WithDownsampled4To1();`
- L132 _public prototype_ `bool IsDownsampled4To1() const;`
- L134 _public prototype_ `JobArg_Blob& WithNeighborTiles();`
- L135 _public prototype_ `bool IsNeighborTiles() const;`
- L137 _public prototype_ `JobArg_Blob& WithArrayOfTiles();`
- L138 _public prototype_ `bool IsArrayOfTiles() const;`
- L140 _public prototype_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override;`
- L141 _public prototype_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override;`
- L143 _public prototype_ `virtual CHashPtr Hash() const override;`
- L144 _public prototype_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override;`
- L146 _public prototype_ `virtual bool IsLateBound(uint32 TileX, uint32 TileY) const override;`
- L147 _public function_ `virtual bool IsBlob() const override`
- L149 _public prototype_ `virtual JobPtrW GeneratingJob() const override;`
- L150 _public prototype_ `virtual const BufferDescriptor* GetDescriptor() const override;`
- L152 _public function_ `FORCEINLINE FString Target() const`
- L153 _public function_ `FORCEINLINE TiledBlobRef GetBlob() const`

#### class `JobArg_SimpleType`  
`template <typename SimpleType> class JobArg_SimpleType : public JobArg_Resource`  
_L160-212_
- inherits: `JobArg_Resource`
- L163 _protected member_ `SimpleType Value;` — The underlying InValue to bind
- L164 _protected member_ `mutable CHashPtr HashValue;` — The InValue of the hash
- L165 _protected member_ `mutable CHashPtr DefaultHash;` — The default hash that we have
- L168 _public function_ `JobArg_SimpleType(SimpleType InValue, const ResourceBindInfo& BindInfo) : JobArg_Resource(BindInfo), Value(InValue)`
- L169 _public function_ `JobArg_SimpleType(SimpleType InValue, const char* TargetName, CHashPtr defaultHash = nullptr) : JobArg_Resource(TargetName) , Value(InValue), DefaultHash(defaultHash)`
- L172 _public function_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override`
- L184 _public function_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override`
- L196 _public function_ `virtual CHashPtr Hash() const override`
- L204 _public function_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override`
- L209 _public function_ `virtual bool IsDefault() const override`
- L210 _public function_ `virtual CHashPtr Hash_Default() const override`
- L211 _public function_ `virtual CHashPtr TileHash_Default(uint32 TileX, uint32 TileY) const override`

#### class `JobArg_String`  
`class JobArg_String : public JobArg_SimpleType<FString>`  
_L216-229_
- inherits: `JobArg_SimpleType<FString>`
- L219 _public function_ `JobArg_String(FString InValue, const ResourceBindInfo& BindInfo) : JobArg_SimpleType<FString>(InValue, BindInfo)`
- L220 _public function_ `JobArg_String(FString InValue, const char* TargetName, CHashPtr defaultHash = nullptr) : JobArg_SimpleType<FString>(InValue, TargetName, defaultHash)`
- L223 _public function_ `virtual CHashPtr Hash() const override`

#### class `JobArg_Mesh`  
`class JobArg_Mesh : public JobArg`  
_L233-246_
- inherits: `JobArg`
- L236 _private member_ `std::shared_ptr<RenderMesh> Mesh;` — The mesh that we're binding
- L237 _private member_ `int32 _targetId = -1;` — What is the TargetName ID
- L240 _public function_ `JobArg_Mesh(std::shared_ptr<RenderMesh> mesh, int32 targetId) : Mesh(mesh), _targetId(targetId)`
- L242 _public prototype_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override;`
- L243 _public prototype_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override;`
- L244 _public prototype_ `virtual CHashPtr Hash() const override;`
- L245 _public prototype_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override;`

#### class `JobArg_Array`  
`template <typename Type> class JobArg_Array : public JobArg_Resource`  
_L250-288_
- inherits: `JobArg_Resource`
- L253 _protected member_ `TArray<Type> Value;` — The underlying InValue to bind
- L256 _public function_ `JobArg_Array()`
- L257 _public function_ `JobArg_Array(TArray<Type> InValue, const ResourceBindInfo& BindInfo) : JobArg_Resource(BindInfo), Value(InValue)`
- L258 _public function_ `JobArg_Array(TArray<Type> InValue, const char* TargetName) : JobArg_Resource(TargetName), Value(InValue)`
- L260 _public function_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override`
- L269 _public function_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override`
- L279 _public function_ `virtual CHashPtr Hash() const override`
- L284 _public function_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override`

#### class `JobArg_Struct`  
`template <typename StructType> class JobArg_Struct: public JobArg_Resource`  
_L294-335_
- inherits: `JobArg_Resource`
- L298 _protected member_ `StructType Value;` — The underlying struct to bind
- L299 _protected member_ `mutable CHashPtr HashValue;` — The InValue of the hash
- L302 _public function_ `JobArg_Struct(StructType InValue, const ResourceBindInfo& BindInfo) : JobArg_Resource(BindInfo), Value(InValue)`
- L303 _public function_ `JobArg_Struct(StructType InValue, const char* TargetName) : JobArg_Resource(TargetName), Value(InValue)`
- L305 _public function_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override`
- L315 _public function_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override`
- L324 _public function_ `virtual CHashPtr Hash() const override`
- L331 _public function_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override`

#### class `JobArg_TileInfo`  
`class JobArg_TileInfo : public JobArg_Struct<FTileInfo>`  
_L337-351_
- inherits: `JobArg_Struct<FTileInfo>`
- L341 _public function_ `JobArg_TileInfo(FTileInfo InValue, const ResourceBindInfo& BindInfo) : JobArg_Struct<FTileInfo>(InValue, BindInfo)`
- L342 _public function_ `JobArg_TileInfo(FTileInfo InValue, const char* TargetName) : JobArg_Struct<FTileInfo>(InValue, TargetName)`
- L344 _public prototype_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override;`
- L346 _public prototype_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override;`
- L348 _public prototype_ `virtual CHashPtr Hash() const override;`
- L350 _public prototype_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override;`

#### class `JobArg_ForceTiling`  
`class JobArg_ForceTiling : public JobArg`  
_L362-378_
- inherits: `JobArg`
- L366 _public prototype_ `virtual ~JobArg_ForceTiling() override = default;`
- L368 _public function_ `virtual AsyncJobArgResultPtr Bind(JobArgBindInfo JobBindInfo) override`
- L372 _public function_ `virtual AsyncJobArgResultPtr Unbind(JobArgBindInfo JobBindInfo) override`
- L376 _public prototype_ `virtual CHashPtr Hash() const override;`
- L377 _public prototype_ `virtual CHashPtr TileHash(uint32 TileX, uint32 TileY) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L27 _typedef_ `typedef std::shared_ptr<JobArgResult> JobArgResultPtr;`
- L28 _typedef_ `typedef cti::continuable<JobArgResultPtr> AsyncJobArgResultPtr;`
- L85 _typedef_ `typedef std::shared_ptr<JobArg> JobArgPtr;`
- L354 _typedef_ `typedef JobArg_SimpleType<float> JobArg_Float;`
- L355 _typedef_ `typedef JobArg_SimpleType<int32> JobArg_Int;`
- L356 _typedef_ `typedef JobArg_SimpleType<bool> JobArg_Bool;`
- L357 _typedef_ `typedef JobArg_SimpleType<FLinearColor> JobArg_LinearColor;`
- L358 _typedef_ `typedef JobArg_SimpleType<FMatrix> JobArg_Matrix;`
- L384 _macro_ `#define ARG_MATRIX(v, n) std::make_shared<JobArg_Matrix>(v, n)`
- L385 _macro_ `#define ARG_TILEINFO(v, n) std::make_shared<JobArg_TileInfo>(v, n)`
- L386 _macro_ `#define ARG_FLOAT(v, n) std::make_shared<JobArg_Float>(v, n)`
- L387 _macro_ `#define ARG_FLOAT_DEF(v, n, hv) std::make_shared<JobArg_Float>(v, n, std::make_shared<CHash>(hv, true))`
- L388 _macro_ `#define ARG_ARRAY(Type,v, n) std::make_shared<JobArg_Array<Type>>(v, n)`
- L389 _macro_ `#define ARG_VECTOR(v, n) std::make_shared<JobArg_LinearColor>(v, n)`
- L390 _macro_ `#define ARG_VECTOR_DEF(v, n, hv) std::make_shared<JobArg_LinearColor>(v, n, std::make_shared<CHash>(hv, true))`
- L391 _macro_ `#define ARG_VECTOR2(v, n) std::make_shared<JobArg_LinearColor>(GraphicsUtil::Vec2AsLinearColor(v), n)`
- L392 _macro_ `#define ARG_VECTOR3(v, n) std::make_shared<JobArg_LinearColor>(GraphicsUtil::Vec3AsLinearColor(v), n)`
- L393 _macro_ `#define ARG_TANGENT(v, n) std::make_shared<JobArg_LinearColor>(GraphicsUtil::TangentAsLinearColor(v), n)`
- L394 _macro_ `#define ARG_LINEAR_COLOR(v, n) std::make_shared<JobArg_LinearColor>(v, n)`
- L395 _macro_ `#define ARG_INT(v, n) std::make_shared<JobArg_Int>(v, n)`
- L396 _macro_ `#define ARG_BOOL(v, n) std::make_shared<JobArg_Bool>(v, n)`
- L397 _macro_ `#define ARG_STRING(v, n) std::make_shared<JobArg_String>(v, n)`
- L398 _macro_ `#define ARG_STRING_DEF(v, n, hv) std::make_shared<JobArg_String>(v, n, std::make_shared<CHash>(hv, true))`
- L399 _macro_ `#define ARG_STRUCT(s, v, n) std::make_shared<JobArg_Struct<s>>(v, n)`
- L401 _macro_ `#define ARG_BLOB(v, n) std::make_shared<JobArg_Blob>(v, n)` — Single tile blob belonging to larger Blob fed into the shader. This argument not have any information of its surrounding to be used in shader
- L402 _macro_ `#define ARG_MESH(m, t) std::make_shared<JobArg_Mesh>(m, t)`
- L405 _macro_ `#define ARG_COMBINEDBLOB(v, n) std::make_shared<JobArg_Blob_Combined>(v, n) //With Custom SRV` — All tiles of blob combined in a single blob (through SRV in shader) Blob can be fetched in HLSL using GetFullBlob(inout float 4) method. See AdjustUVGeneric.usf and TiledFetch_Combined.ush for help
- L407 _function_ `FORCEINLINE JobArgPtr WithIgnoreDesc(JobArgPtr Arg, bool bIgnoreDesc = true)`
- L413 _function_ `FORCEINLINE JobArgPtr WithIgnoreHash(JobArgPtr Arg, bool bIgnoreHash = true)`
- L419 _function_ `FORCEINLINE JobArgPtr WithUnbounded(JobArgPtr Arg, bool bUnbounded = true)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/JobBatch.h` (Other)


#### class `JobBatch`  
`class JobBatch`  
_L31-124_
- L34 _public member_ `static uint64 GBatchId;` — For easier debugging
- L37 _protected member_ `mutable FCriticalSection Mutex;` — Mutex for the JobObj queue
- L38 _protected member_ `std::atomic<bool> bIsLocked = false;` — Whether the queue is now locked from any further changes
- L40 _protected member_ `std::vector<JobPtr> AllJobs;` — All the jobs within the system
- L42 _protected member_ `JobPriorityQueue Queue;` — The JobObj queue
- L43 _protected member_ `JobPtr CurrJob;` — The current JobObj ... we keep it to prevent it from going out of scope
- L44 _protected member_ `JobPtr PrevJob;` — The previous JobObj that we ran. Mostly for debugging purposes
- L46 _protected member_ `double StartTime = 0;` — Time when the batch was started
- L47 _protected member_ `double EndTime = 0;` — Time when the batch has ended
- L49 _protected member_ `uint64 FrameId = 0;` — What is the frame id for this
- L50 _protected member_ `size_t BatchId = 0;` — What is the index of this batch
- L52 _protected member_ `std::shared_ptr<MixUpdateCycle> Cycle;` — Scene update cycle information
- L53 _protected member_ `int32 ReplayCount = 0;` — Counting the number of debug replay of this batch
- L55 _protected member_ `bool bCaptureRenderDoc = false;` — flag to record a RenderDoc capture for debugging the batch
- L56 _protected member_ `bool bNoCache = false;` — Whether we should ignore the cache
- L57 _protected member_ `bool bIsIdle = false;` — Is the batch generated by an idle service or not
- L58 _protected member_ `bool bIsFinished = false;` — Whether the batch has been finished or not
- L59 _protected member_ `bool bIsAsync = true;` — Whether the job batch is asynchronous or not
- L61 _protected prototype_ `AsyncJobResultPtr BeginQueue_Native(JobPriorityQueue& InQueue);`
- L63 _protected prototype_ `void EndBatch();`
- L66 _protected prototype_ `void OnJobDone(Job* JobObj, int64 JobId);` — Once a JobObj is TRULY done then it reports to the batch,
- L67 _protected prototype_ `void OnJobDone(Job* JobObj, int64 JobId);`
- L69 _protected member_ `std::atomic<uint32> NumJobsRunning = 0;` — A count down of the jobs still running, decremented by OnJobDone
- L70 _protected member_ `OnAllJobsDoneCallbackVec OnAllJobsDoneCallbacks;` — If the call back has been assigned, that 's what will get called when all the jobs are done.
- L72 _protected member_ `std::vector<bool> JobsFinished;` — Jobs that have been finished
- L74 _protected prototype_ `void PrintJobTimings() const;`
- L77 _public prototype_ `explicit JobBatch(const FInvalidationDetails& Details);`
- L78 _public prototype_ `virtual ~JobBatch();`
- L80 _public prototype_ `virtual AsyncJobResultPtr Exec(OnAllJobsDoneCallback Callback = nullptr);`
- L82 _public prototype_ `virtual JobPtrW AddJob(JobUPtr JobObj);`
- L83 _public prototype_ `virtual void RemoveJob(JobPtrW JobObj);`
- L85 _public prototype_ `bool IsLocked() const;`
- L87 _public prototype_ `void ResetForReplay(int32 JobId = -1);` — For debug purpose we can reset the state of a batch for a replay
- L90 _public prototype_ `void SetCaptureRenderDoc(bool CaptureRenderDoc = true);`
- L91 _public prototype_ `void DebugDumpUnfinishedJobs();`
- L93 _public prototype_ `void Terminate();`
- L94 _public prototype_ `void OnDone(OnAllJobsDoneCallback Callback);`
- L99 _public function_ `FORCEINLINE bool IsCaptureRenderDoc() const`
- L100 _public function_ `FORCEINLINE void SetNoCache(bool bInNoCache)`
- L101 _public function_ `FORCEINLINE bool IsNoCache() const`
- L102 _public function_ `FORCEINLINE std::shared_ptr<MixUpdateCycle> GetCycle() const`
- L103 _public function_ `FORCEINLINE size_t NumJobs() const`
- L104 _public function_ `FORCEINLINE uint64 GetFrameId() const`
- L105 _public function_ `FORCEINLINE uint64 GetBatchId() const`
- L107 _public function_ `FORCEINLINE JobPtrW GetJobAt(uint64_t jobNum) const`
- L108 _public function_ `FORCEINLINE double GetStartTime() const`
- L109 _public function_ `FORCEINLINE double GetEndTime() const`
- L110 _public function_ `FORCEINLINE int32 GetReplayCount() const` — For debug purpose, report the replay number
- L111 _public function_ `FORCEINLINE uint32 GetNumJobsRunning() const`
- L113 _public function_ `FORCEINLINE bool WasGeneratedFromIdleService() const`
- L114 _public function_ `FORCEINLINE bool& IsIdle()`
- L115 _public function_ `FORCEINLINE bool IsFinished() const`
- L116 _public function_ `FORCEINLINE void SetAsync(bool bIsAsyncIn)`
- L117 _public function_ `FORCEINLINE bool IsAsync() const`
- L122 _public function_ `static FORCEINLINE uint64 CurrentBatchId()`
- L123 _public prototype_ `static std::shared_ptr<JobBatch> Create(const FInvalidationDetails& details);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _typedef_ `typedef std::unique_ptr<Job> JobUPtr;`
- L15 _typedef_ `typedef std::shared_ptr<Job> JobPtr;`
- L16 _typedef_ `typedef std::weak_ptr<Job> JobPtrW;`
- L17 _typedef_ `typedef cti::continuable<bool> AsyncBool;`
- L18 _typedef_ `typedef std::shared_ptr<JobBatch> JobBatchPtr;`
- L19 _typedef_ `typedef TUniqueFunction<void(JobBatch* )> OnAllJobsDoneCallback;`
- L20 _typedef_ `typedef std::vector<OnAllJobsDoneCallback> OnAllJobsDoneCallbackVec;`
- L21 _typedef_ `typedef GenericTaskPriorityQueue<std::shared_ptr<Job>, DeviceNativeTask_CompareStrong> JobPriorityQueue;`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBatch, Log, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBatch, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/JobCommon.h` (Other)


#### struct `JobRunInfo`  
`struct JobRunInfo`  
_L28-35_
- L30 _public member_ `Scheduler* JobScheduler = nullptr;` — The scheduler instance that's scheduled this job
- L31 _public member_ `Device* Dev = nullptr;` — The device on which the job must be executed
- L32 _public member_ `JobBatch* Batch = nullptr;` — The batch that this job belongs to
- L33 _public member_ `std::shared_ptr<MixUpdateCycle> Cycle = nullptr;` — The mix update cycle
- L34 _public member_ `std::weak_ptr<Job> ThisJob;` — Shared ptr (weak) for this job. Needed in various places that need smart ptr

#### struct `JobResult`  
`struct JobResult`  
_L38-51_
- L40 _public member_ `static std::shared_ptr<JobResult> NullResult;` — Null result
- L42 _public member_ `std::exception_ptr ExInner;` — Original exception that was raised by the action
- L43 _public member_ `int32 ErrorCode = 0;` — What is the error code
- L44 _public member_ `BlobRef BlobObj;` — The resultant blob for this job
- L45 _public member_ `CHashPtr HashValue;` — The has for the job
- L46 _public member_ `BlobTransformPtr Transform;` — The transformation function (or a clone of it) that was used for this job
- L48 _public function_ `JobResult() : BlobObj(BlobRef())`
- L49 _public function_ `JobResult(BlobRef NewBlobObj, CHashPtr NewHashValue) : BlobObj(NewBlobObj), HashValue(NewHashValue)`
- L50 _public prototype_ `~JobResult();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L17 _typedef_ `typedef std::weak_ptr<Blob> BlobPtrW;`
- L18 _typedef_ `typedef std::shared_ptr<Blob> BlobPtr;`
- L21 _typedef_ `typedef std::shared_ptr<TiledBlob> TiledBlobPtr;`
- L24 _typedef_ `typedef std::shared_ptr<BlobTransform> BlobTransformPtr;`
- L53 _typedef_ `typedef std::shared_ptr<JobResult> JobResultPtr;`
- L54 _typedef_ `typedef cti::continuable<JobResultPtr> AsyncJobResultPtr;`
- L57 _typedef_ `typedef std::shared_ptr<Job> JobPtr;`
- L58 _typedef_ `typedef std::vector<JobPtr> JobPtrVec;`
- L59 _typedef_ `typedef TArray<JobPtr> JobPtrArray;`
- L60 _typedef_ `typedef TArray<Job*> JobPArray;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/MinMaxService.h` (Other)


#### class `MinMaxService`  
`class MinMaxService : public BlobHelperService`  
_L18-25_
- inherits: `BlobHelperService`
- L21 _public prototype_ `MinMaxService();`
- L24 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L13 _typedef_ `typedef std::shared_ptr<class Job> JobPtr;`
- L14 _typedef_ `typedef std::weak_ptr<class Job> JobPtrW;`
- L27 _typedef_ `typedef std::shared_ptr<MinMaxService> MinMaxServicePtr;`
- L28 _typedef_ `typedef std::weak_ptr<MinMaxService> MinMaxServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/MipMapService.h` (Other)


#### class `MipMapService`  
`class MipMapService : public BlobHelperService`  
_L18-25_
- inherits: `BlobHelperService`
- L21 _public prototype_ `MipMapService();`
- L24 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L13 _typedef_ `typedef std::shared_ptr<class Job> JobPtr;`
- L14 _typedef_ `typedef std::weak_ptr<class Job> JobPtrW;`
- L27 _typedef_ `typedef std::shared_ptr<MipMapService> MipMapServicePtr;`
- L28 _typedef_ `typedef std::weak_ptr<MipMapService> MipMapServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/Scheduler.h` (Other)


#### class `SchedulerObserverSource`  
`class SchedulerObserverSource`  
_L23-41_
- L31 _protected function_ `virtual void Start()`
- L32 _protected function_ `virtual void UpdateIdle()`
- L33 _protected function_ `virtual void Stop()`
- L34 _protected function_ `virtual void BatchAdded(JobBatchPtr Batch)`
- L35 _protected function_ `virtual void BatchDone(JobBatchPtr Batch)`
- L36 _protected function_ `virtual void BatchJobsDone(JobBatchPtr Batch)`
- L39 _public prototype_ `SchedulerObserverSource() = default;`
- L40 _public prototype_ `virtual ~SchedulerObserverSource() = default;`

#### class `Scheduler`  
`class Scheduler`  
_L44-142_
- L47 _private member_ `static const double IdleTimeInterval;` — Start an Idle Batch after <this many> milliseconds
- L48 _private member_ `static const double IdleBusyTimeInterval;` — Start an Idle Batch (during busy times) after <this many> milliseconds
- L49 _private member_ `static const double IdleBatchTimeLimit;` — Start an Idle Batch after <this many> milliseconds
- L50 _private member_ `static const double CurrentBatchWarningLimit;` — Scheduler starts spewing out warnings if the current batch doesn't finish ater <this many> milliseconds
- L52 _private member_ `bool bIsRunning = false;` — Whether the scheduler is running or not
- L54 _private typedef_ `typedef std::list<JobBatchPtr> JobBatchPtrList;`
- L55 _private typedef_ `typedef std::vector<IdleServicePtr> Svc_IdlePtrVec;`
- L57 _private member_ `SchedulerObserverSourcePtr ObserverSource;` — Scheduler observer source interface where public signals will be emitted from.
- L63 _private member_ `mutable FCriticalSection IdlServiceMutex;` — Mutex for the idle batches
- L64 _private member_ `Svc_IdlePtrVec IdleServices;` — The batches that we can run when the Scheduler is idle for s_idleTimeInterval
- L66 _private member_ `BlobHasherServicePtrW BlobHasherServiceObj;` — Blob hashing service
- L67 _private member_ `DeviceTransferServicePtrW DeviceTransferServiceObj;` — Device transfer idle service
- L68 _private member_ `ThumbnailsServicePtrW ThumbnailsServiceObj;` — Thumbnail service
- L69 _private member_ `MipMapServicePtrW MipMapServiceObj;` — Mip mapping service
- L70 _private member_ `MinMaxServicePtrW MinMaxServiceObj;` — Min/max calculation service
- L71 _private member_ `HistogramServicePtrW HistogramServiceObj;` — Histogram service
- L76 _private member_ `mutable FCriticalSection BatchMutex;` — Mutex for the job queue
- L77 _private member_ `mutable FCriticalSection CurrentBatchMutex;` — Mutex for the job queue
- L79 _private member_ `JobBatchPtr CurrentBatch;` — Current batch that we are executing
- L80 _private member_ `double CurrentBatchStartTime = 0;` — The time when the current batch started. This is used to check and give out
- L83 _private member_ `JobBatchPtr PreviousBatch;` — The previous batch that we rendered
- L84 _private member_ `JobBatchPtrList Batches;` — The batches that we have to run
- L85 _private member_ `JobBatchPtr CurrentHighPriorityBatch;` — The current high priority batch job
- L87 _private member_ `double TimeSinceIdle = 0;` — time since scheduler has been idle
- L88 _private member_ `double TimeSinceIdleBatchRan = 0;` — time since scheduler has been idle
- L90 _private member_ `bool bCaptureNextBatch = false;` — set the next incoming batch to get captured by RenderDoc
- L91 _private member_ `bool bIsDisableIdle = false;` — Disable idle services or not
- L93 _private member_ `uint64 BatchIndex = 0;` — Index of the batches
- L95 _private prototype_ `void Start();`
- L96 _private prototype_ `void Stop();`
- L97 _private prototype_ `void StopServices();`
- L99 _private prototype_ `AsyncJobResultPtr UpdateIdleBatch(size_t index, bool bIsBusyUpdate);`
- L100 _private prototype_ `void UpdateIdle(bool bForce, bool bIsBusyUpdate = false);`
- L103 _public prototype_ `Scheduler();`
- L104 _public prototype_ `~Scheduler();`
- L106 _public prototype_ `void Update(float Delta);`
- L107 _public prototype_ `void AddBatch(JobBatchPtr Batch);`
- L108 _public prototype_ `void AddIdleService(IdleServicePtr batch);`
- L110 _public prototype_ `void CaptureRenderDocLastRunBatch();`
- L112 _public prototype_ `void RegisterObserverSource(const SchedulerObserverSourcePtr& observerSource);` — /
- L113 _public prototype_ `void SetCaptureRenderDocNextBatch(bool capture = true);`
- L114 _public prototype_ `void ClearCache();`
- L119 _public function_ `FORCEINLINE BlobHasherServicePtrW GetBlobHasherService() const`
- L120 _public function_ `FORCEINLINE DeviceTransferServicePtrW GetDeviceTransferService() const`
- L121 _public function_ `FORCEINLINE ThumbnailsServicePtrW GetThumbnailsService() const`
- L122 _public function_ `FORCEINLINE MipMapServicePtrW GetMipMapService() const`
- L123 _public function_ `FORCEINLINE MinMaxServicePtrW GetMinMaxService() const`
- L124 _public function_ `FORCEINLINE HistogramServicePtrW GetHistogramService() const`
- L125 _public function_ `FORCEINLINE void SetDisableIdle(bool bIsDisableIdleIn)`
- L126 _public function_ `FORCEINLINE bool IsDisableIdle() const`
- L128 _public function_ `FORCEINLINE size_t NumBatches() const`
- L135 _public function_ `FORCEINLINE size_t GetBatchIndex() const`
- L141 _public function_ `FORCEINLINE SchedulerObserverSourcePtr GetObserverSource() const`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L20 _typedef_ `typedef std::shared_ptr<JobBatch> JobBatchPtr;`
- L21 _typedef_ `typedef std::weak_ptr<JobBatch> JobBatchPtrW;`
- L42 _typedef_ `typedef std::shared_ptr<SchedulerObserverSource> SchedulerObserverSourcePtr;`
- L144 _typedef_ `typedef std::unique_ptr<Scheduler> SchedulerPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/TempHashService.h` (Other)


#### class `TempHashService`  
`class TempHashService : public IdleService`  
_L10-24_
- inherits: `IdleService`
- L13 _protected member_ `FCriticalSection HashesMutex;` — Mutex for the hashes
- L14 _protected member_ `std::vector<CHashPtr> Hashes;` — The hashes that we're waiting to resolve
- L17 _public prototype_ `TempHashService();`
- L20 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`
- L21 _public prototype_ `virtual void Stop() override;`
- L23 _public prototype_ `void Add(CHashPtr HashValue);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L26 _typedef_ `typedef std::shared_ptr<TempHashService> TempHashServicePtr;`
- L27 _typedef_ `typedef std::weak_ptr<TempHashService> TempHashServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Job/ThumbnailsService.h` (Other)


#### class `ThumbnailsService`  
`class ThumbnailsService : public IdleService`  
_L19-51_
- inherits: `IdleService`
- L22 _protected member_ `JobBatchPtr Batch;` — The thumbnail rendering batch
- L23 _protected member_ `JobBatchPtr PrevBatch;` — Last rendered batch
- L24 _protected member_ `MixUpdateCyclePtr Cycle;` — The cycle that we'll be using for the thumbnail updates
- L32 _protected member_ `std::unordered_map<UObject*, AddedJobs> Handled;` — The components that we have already added jobs for
- L34 _protected prototype_ `JobBatchPtr CreateNewUpdateCycle(UMixInterface* Mix);`
- L35 _protected prototype_ `JobBatchPtr GetNextUpdateCycle();`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnThumbnailBatchDoneDelegate, JobBatchPtr Batch) FOnThumbnailBatchDoneDelegate OnUpdateThumbnailDelegate;`
- L40 _public prototype_ `ThumbnailsService();`
- L43 _public prototype_ `virtual AsyncJobResultPtr Tick() override;`
- L44 _public prototype_ `virtual void Stop() override;`
- L45 _public prototype_ `void AddUniqueJobToCycle(UObject* CreatorComponent, UMixInterface* Mix, JobUPtr ThumbnailJob, int32 TargetId, bool bForceExec = false);` — Use this to always generate thumbnail from last update cycle
- L50 _public function_ `JobBatchPtr GetCurrentBatch() const`

#### struct `ThumbnailsService::AddedJobs`  
`struct AddedJobs`  
_L26-30_
- L28 _public member_ `JobBatchPtr AssociatedBatch;` — Batch holding the following job
- L29 _public member_ `JobPtrW ThumbnailJob;` — Thumbnail updating job assigned

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L13 _typedef_ `typedef std::shared_ptr<class Job> JobPtr;`
- L14 _typedef_ `typedef std::unique_ptr<class Job> JobUPtr;`
- L15 _typedef_ `typedef std::weak_ptr<class Job> JobPtrW;`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnThumbnailBatchDoneDelegate, JobBatchPtr Batch) FOnThumbnailBatchDoneDelegate OnUpdateThumbnailDelegate;`
- L53 _typedef_ `typedef std::shared_ptr<ThumbnailsService> ThumbnailsServicePtr;`
- L54 _typedef_ `typedef std::weak_ptr<ThumbnailsService> ThumbnailsServicePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/Mix.h` (Other)


#### class `UMix`  
`class UMix : public UMixInterface`  
_L22-41_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UMixInterface`
- L30 _private member_ `static UMix* GNullMix;` — This is a generic mix that is used in various places and rendering actions that
- L33 _private member_ `static const FString GRootSectionName;` — often require a Mix object. This is initialised in the first call to the public static function below.
- L36 _public prototype_ `static UMix* NullMix();`
- L40 _public prototype_ `virtual void Update(MixUpdateCyclePtr Cycle) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMix, All, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMix, All, All);`
- L19 _typedef_ `typedef std::shared_ptr<RenderMesh> RenderMeshPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/MixInterface.h` (Other)


#### class `UMixInterface`  
`class UMixInterface : public UModelObject`  
_L29-109_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UModelObject`
- L34 _private member_ `static const TMap<FString, FString> s_uriAlias;` — Contains the list of URI aliases map to keep the data meaningful, short and precise.
- L35 _private member_ `static const TMap<FString, FString> s_uriAliasDecryptor;` — We need alias decryptor to convert it so we can extract the object from the data.
- L37 _private prototype_ `static TMap<FString, FString> InitURIAlias();`
- L38 _private prototype_ `static TMap<FString, FString> InitURIAliasDecryptor();`
- L40 _private prototype_ `FString GetObjectAlias(FString object);`
- L41 _private prototype_ `FString GetAliasToObject(FString Alias);`
- L45 _protected member_ `int32 Priority;` — `UPROPERTY()` — The priority of this mix in terms of update cycle
- L48 _protected member_ `TObjectPtr<UMixSettings> Settings = nullptr;` — `UPROPERTY()` — The settings for this mix interface
- L51 _protected member_ `bool bInvalidateTextures;` — `UPROPERTY()` — Invalidate the scene textures or not
- L53 _protected member_ `std::atomic_int64_t InvalidationFrameId;` — When was the mix last invalidated
- L54 _protected member_ `std::atomic_int64_t UpdatedFrameId;` — When was the mix actually last updated
- L56 _protected member_ `bool bEnableLOD = true;` — Enable LOD-ing in the system
- L58 _protected function_ `virtual UModelObject* RootURI()`
- L59 _protected prototype_ `virtual void Invalidate(FModelInvalidateInfo InvalidateInfo);`
- L66 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBatchQueued, UMixInterface*, const FInvalidationDetails*);`
- L67 _public member_ `FOnBatchQueued OnBatchQueued;`
- L69 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRenderDone, UMixInterface*, const FInvalidationDetails*);`
- L70 _public member_ `FOnRenderDone OnRenderDone;`
- L71 _public prototype_ `virtual void PostMeshLoad();`
- L73 _public function_ `virtual bool CanEdit()`
- L75 _public prototype_ `virtual void SetMesh(RenderMeshPtr MeshObj, int MeshType, FVector Scale, FVector2D Dimension);`
- L78 _public prototype_ `virtual AsyncActionResultPtr SetEditorMesh(AActor* Actor);`
- L79 _public prototype_ `virtual AsyncActionResultPtr SetEditorMesh(UStaticMeshComponent* MeshComponent, UWorld* World);`
- L82 _public prototype_ `virtual void Update(MixUpdateCyclePtr cycle);`
- L84 _public prototype_ `virtual RenderMeshPtr GetMesh() const;` — Get the mesh assigned in Settings
- L86 _public prototype_ `virtual int32 Width() const;`
- L87 _public prototype_ `virtual int32 Height() const;`
- L89 _public prototype_ `virtual int32 GetNumXTiles() const;`
- L90 _public prototype_ `virtual int32 GetNumYTiles()const;`
- L92 _public prototype_ `virtual UMixSettings* GetSettings() const;`
- L94 _public prototype_ `bool IsHigherPriorityThan(const UMixInterface* RHS) const;`
- L96 _public prototype_ `virtual void InvalidateWithDetails(const FInvalidationDetails& Details);`
- L97 _public prototype_ `virtual void InvalidateAll();`
- L99 _public prototype_ `virtual void BroadcastOnRenderingDone(const FInvalidationDetails* Details);`
- L100 _public prototype_ `virtual void BroadcastOnBatchQueued(const FInvalidationDetails* Details);`
- L105 _public function_ `FORCEINLINE int32 GetPriority() const`
- L107 _public function_ `FORCEINLINE int64 GetInvalidationFrameId() const`
- L108 _public function_ `FORCEINLINE int64 GetUpdateFrameId() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L18 _typedef_ `typedef std::shared_ptr<RenderMesh> RenderMeshPtr;`
- L21 _typedef_ `typedef std::shared_ptr<MeshAsset> MeshAssetPtr;`
- L66 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBatchQueued, UMixInterface*, const FInvalidationDetails*);`
- L69 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRenderDone, UMixInterface*, const FInvalidationDetails*);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/MixManager.h` (Other)


#### struct `MixInvalidateInfo`  
`struct MixInvalidateInfo`  
_L16-24_
- L18 _public member_ `UMixInterface *MixObj;` — The mix that needs to be updated
- L19 _public member_ `FInvalidationDetails InvalidationDetails;` — Invalidation details
- L20 _public member_ `int32 Priority = (int32)E_Priority::kNormal;` — The pririty of this invalidation

#### struct `MixInterface_ComparePriority`  
`struct MixInterface_ComparePriority`  
_L27-30_
- L29 _public prototype_ `bool operator()(const MixInvalidateInfo& LHS, const MixInvalidateInfo& RHS);`

#### class `MixManager`  
`class MixManager`  
_L41-63_
- L44 _private member_ `std::atomic_bool bIsSuspended = false;` — Whether the mix manager is suspended or not
- L45 _private member_ `MixPriorityQueue Queue;` — Mix queue
- L46 _private member_ `std::vector<UMixInterface*> MixesToFlush;` — The mixes to flush
- L49 _public prototype_ `MixManager();`
- L50 _public prototype_ `virtual ~MixManager();`
- L52 _public prototype_ `void Update(float Delta);`
- L53 _public prototype_ `void Suspend();`
- L54 _public prototype_ `void Resume();`
- L55 _public prototype_ `void Exit();`
- L57 _public prototype_ `void InvalidateMix(UMixInterface* MixObj, const FInvalidationDetails &Details, int32 Priority = (int32)E_Priority::kNormal);`
- L58 _public prototype_ `void FlushMix(UMixInterface* MixObj);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMixManager, All, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMixManager, All, All);`
- L23 _function_ `FORCEINLINE friend bool operator==(MixInvalidateInfo const& LHS, const UMixInterface* RHS)` — Global comparison between a MixInvalidateInfo internal mix and an external mix
- L32 _typedef_ `typedef GenericTaskPriorityQueue<MixInvalidateInfo, MixInterface_ComparePriority> MixPriorityQueue;`
- L65 _typedef_ `typedef std::unique_ptr<MixManager> MixManagerUPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/MixSettings.h` (Other)


#### enum `PBRWorkflowMode`  
`enum class PBRWorkflowMode`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `Specular = 0`
- L17 _public enumerator_ `Metalness = 1`
- L18 _public enumerator_ `Both = 2`

#### enum `ETileSize`  
`enum class ETileSize`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `Tile1 = 0 UMETA(DisplayName = "1")`
- L25 _public enumerator_ `Tile2 = 2 UMETA(DisplayName = "2")`
- L26 _public enumerator_ `Tile4 = 4 UMETA(DisplayName = "4")`
- L27 _public enumerator_ `Tile8 = 8 UMETA(DisplayName = "8")`
- L28 _public enumerator_ `Tile16 = 16 UMETA(DisplayName = "16")`

#### enum `EResolution`  
`enum class EResolution`  
_L32-46_
- reflection: `UENUM()`
- L34 _public enumerator_ `Auto = 0 UMETA(DisplayName = "Auto")`
- L35 _public enumerator_ `Resolution8 = 8 UMETA(DisplayName = "8")`
- L36 _public enumerator_ `Resolution16 = 16 UMETA(DisplayName = "16")`
- L37 _public enumerator_ `Resolution32 = 32 UMETA(DisplayName = "32")`
- L38 _public enumerator_ `Resolution64 = 64 UMETA(DisplayName = "64")`
- L39 _public enumerator_ `Resolution128 = 128 UMETA(DisplayName = "128")`
- L40 _public enumerator_ `Resolution256 = 256 UMETA(DisplayName = "256")`
- L41 _public enumerator_ `Resolution512 = 512 UMETA(DisplayName = "512")`
- L42 _public enumerator_ `Resolution1024 = 1024 UMETA(DisplayName = "1024")`
- L43 _public enumerator_ `Resolution2048 = 2048 UMETA(DisplayName = "2048")`
- L44 _public enumerator_ `Resolution4096 = 4096 UMETA(DisplayName = "4096")`
- L45 _public enumerator_ `Resolution8192 = 8192 UMETA(DisplayName = "8192")`

#### enum `ETSBufferFormat`  
`enum class UE_DEPRECATED(5.3, "You should use ETG_TextureFormat instead") ETSBufferFormat`  
_L49-55_
- reflection: `UENUM()`
- L51 _public enumerator_ `Auto = -1 UMETA(DisplayName = "Auto")` — Auto buffer format is deduced automatically based on other textures within the graph
- L52 _public enumerator_ `Byte = 0 UMETA(DisplayName = "Byte")` — One byte of data per channel
- L53 _public enumerator_ `Half = 1 UMETA(DisplayName = "Half")` — Two bytes (half float) of data per channel
- L54 _public enumerator_ `Float = 2 UMETA(DisplayName = "Float")` — Four bytes (full float) of data per channel

#### enum `ETSBufferChannels`  
`enum class UE_DEPRECATED(5.3, "You should use ETG_TextureFormat instead") ETSBufferChannels`  
_L58-65_
- reflection: `UENUM()`
- L60 _public enumerator_ `Auto = 0 UMETA(DisplayName = "Auto")` — Auto number of channels are deduced automatically based on other channels within the graph
- L61 _public enumerator_ `One = 1 UMETA(DisplayName = "R")` — One channel per pixel (e.g. Red only)
- L62 _public enumerator_ `Two = 2 UMETA(DisplayName = "RG")` — Two channels per pixel (e.g. RG = Red and Green only)
- L63 _public enumerator_ `Three = 3 UMETA(DisplayName = "RGB")` — Three channels per pixel (e.g. RGB)
- L64 _public enumerator_ `Four = 4 UMETA(DisplayName = "RGBA")` — Four channels per pixel (e.g. RGBA)

#### enum `ETG_TextureFormat`  
`enum class ETG_TextureFormat : uint8`  
_L68-77_
- reflection: `UENUM(BlueprintType)`
- L70 _public enumerator_ `Auto UMETA(DisplayName = "Auto")` — Auto number of channels are deduced automatically based on other channels within the graph /*UMETA(Hidden) = -1,*/
- L71 _public enumerator_ `G8 UMETA(DisplayName = "8-bit Grayscale")` — Auto		UMETA(DisplayName = "Auto"), // Auto number of channels are deduced automatically based on other channels within the graph  UMETA(Hidden) = -1,
- L72 _public enumerator_ `BGRA8 UMETA(DisplayName = "8-bit per-pixel RGBA")`
- L73 _public enumerator_ `R16F UMETA(DisplayName = "16-bit (half) Single Channel (Red)")`
- L74 _public enumerator_ `RGBA16F UMETA(DisplayName = "16-bit (half) per-pixel RGBA")`
- L75 _public enumerator_ `R32F UMETA(DisplayName = "32-bit (float) Single Channel (Red)")`
- L76 _public enumerator_ `RGBA32F UMETA(DisplayName = "32-bit (float) per-pixel RGBA")`

#### enum `ETG_TexturePresetType`  
`enum class ETG_TexturePresetType : uint8`  
_L80-90_
- reflection: `UENUM(BlueprintType)`
- L82 _public enumerator_ `None UMETA(DisplayName = "None")` — None exposes the other settings like srgb, compression and Lod Texture group */
- L83 _public enumerator_ `Diffuse UMETA(DisplayName = "Diffuse")` — Auto		UMETA(DisplayName = "Auto"), // Auto number of channels are deduced automatically based on other channels within the graph  UMETA(Hidden) = -1, G8			UMETA(DisplayName = "8-bit Grayscale"), BGRA8		UMETA(DisplayName = "8-bit per-pixel RGBA"), R16F		UMETA(DisplayName = "16-bit (half) Single Channel (Red)"), RGBA16F		UMETA(DisplayName = "16-bit (half) per-pixel RGBA"), R32F		UMETA(DisplayName = "32-bit (float) Single Channel (Red)"), RGBA32F		UMETA(DisplayName = "32-bit (float) per-pixel RGBA") }; UENUM(BlueprintType) enum class ETG_TexturePresetType : uint8 { None		UMETA(DisplayName = "None"), // None exposes the other settings like srgb, compression and Lod Texture group
- L84 _public enumerator_ `Emissive UMETA(DisplayName = "Emissive")`
- L85 _public enumerator_ `FX UMETA(DisplayName = "FX")`
- L86 _public enumerator_ `Normal UMETA(DisplayName = "Normal")`
- L87 _public enumerator_ `MaskComp UMETA(DisplayName = "Mask Comp")`
- L88 _public enumerator_ `Specular UMETA(DisplayName = "Specular")`
- L89 _public enumerator_ `Tangent UMETA(DisplayName = "Tangent")`

#### class `UMixSettings`  
`class UMixSettings : public UObject`  
_L111-248_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UObject`
- L121 _private member_ `bool bIsPlane;` — `UPROPERTY()` — Is this a plane scene
- L124 _private member_ `FVector2D PlaneDimensions;` — `UPROPERTY()` — Default dimensions for plane in the scene
- L127 _private member_ `float StandardHeight = 0.1f;` — `UPROPERTY()` — 10 cm for 0-1 range displacements
- L130 _private member_ `float MidPoint = 0.5f;` — `UPROPERTY()` — Midpoint for displacement. Default is gray.
- L133 _private member_ `PBRWorkflowMode _workflow = PBRWorkflowMode::Metalness;` — `UPROPERTY()` — The workflow for the scene right now
- L136 _private member_ `EResolution Width = EResolution::Resolution2048;` — `UPROPERTY()` — Default width of the target(s). Auto will take the width from Input texture(s)
- L139 _private member_ `EResolution Height = EResolution::Resolution2048;` — `UPROPERTY()` — Default height of the target(s). Auto will take the height from Input texture(s)
- L144 _private member_ `ETSBufferChannels Channels_DEPRECATED = ETSBufferChannels::Auto;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Texture Format instead"))` — How many channels per pixel.  Auto will take the number of channels from Input texture(s)
- L147 _private member_ `ETSBufferFormat Format_DEPRECATED = ETSBufferFormat::Auto;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Texture Format instead"))` — Per channel size/format.  Auto will take the format from Input texture(s)
- L151 _private member_ `ETG_TextureFormat TextureFormat = ETG_TextureFormat::Auto;` — `UPROPERTY()`
- L154 _private member_ `ETileSize XTiles = ETileSize::Tile8;` — `UPROPERTY()` — How many horizontal tiles to split the inputs into for the tiled processing pipeline
- L157 _private member_ `ETileSize YTiles = ETileSize::Tile8;` — `UPROPERTY()` — How many vertical tiles to split the inputs into for the tiled processing pipeline
- L160 _private member_ `bool bAllowRectangularResolution = false;` — `UPROPERTY()` — Allow rectangular outputs
- L163 _private member_ `FViewportSettings ViewportSettings;` — `UPROPERTY(EditAnywhere, Category = "Viewport Material", meta = (NoResetToDefault, ShowOnlyInnerProperties))` — Viewport settings
- L166 _private member_ `TObjectPtr<UStaticMesh> PreviewMesh;` — `UPROPERTY(EditAnywhere, Category = "Viewport Mesh", DisplayName = "Static Mesh", NoClear)`
- L170 _private member_ `RenderMeshPtr _mesh;` — Mesh related data
- L171 _private member_ `TArray<RenderMeshPtr> _sceneMeshes;` — All the different submeshes that were added to the scene
- L172 _private member_ `RenderMaterial_BPPtr _currentMat = nullptr;` — What is the active material for rendering the mesh
- L175 _private member_ `TargetTextureSetPtrVec* _targets = nullptr;` — Mesh's target texture sets
- L178 _private prototype_ `template<typename RenderMeshClass> void SetMeshInternal(RenderMeshPtr mesh, int meshType, FVector scale, FVector2D dimension);`
- L179 _private prototype_ `void SetMesh(RenderMeshPtr mesh);`
- L184 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L185 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;` — For TArray type properties in the component.
- L191 _public prototype_ `void FreeTargets();`
- L192 _public prototype_ `void InitTargets(size_t count);`
- L193 _public prototype_ `void SetTarget(size_t index, TargetTextureSetPtr& target);`
- L194 _public prototype_ `virtual void Free();`
- L197 _public prototype_ `AsyncActionResultPtr SetEditorMesh(AActor* actor);`
- L198 _public prototype_ `AsyncActionResultPtr SetEditorMesh(UStaticMeshComponent* meshComponent,UWorld* world);`
- L201 _public prototype_ `RenderMeshPtr GetMesh();`
- L202 _public prototype_ `UMixInterface* Mix() const;`
- L204 _public prototype_ `FViewportSettings& GetViewportSettings();`
- L206 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FPreviewMeshUpdateEvent) FPreviewMeshUpdateEvent OnPreviewMeshChangedEvent;`
- L212 _public function_ `[[nodiscard]] TObjectPtr<UStaticMesh> GetPreviewMesh() const`
- L213 _public function_ `FORCEINLINE void SetPreviewMesh(const TObjectPtr<UStaticMesh>& InPreviewMesh)`
- L214 _public function_ `FORCEINLINE bool IsPlane() const`
- L215 _public function_ `FORCEINLINE FVector2D GetPlaneDimensions() const`
- L216 _public function_ `FORCEINLINE const TargetTextureSetPtr& Target(size_t index) const`
- L217 _public function_ `FORCEINLINE TargetTextureSetPtr& Target(size_t index)`
- L218 _public function_ `FORCEINLINE size_t NumTargets() const`
- L220 _public function_ `FORCEINLINE PBRWorkflowMode Workflow() const`
- L221 _public function_ `FORCEINLINE PBRWorkflowMode& Workflow()`
- L222 _public function_ `FORCEINLINE void SetWidth(EResolution InWidth)`
- L223 _public function_ `FORCEINLINE void SetHeight(EResolution InHeight)`
- L224 _public function_ `FORCEINLINE void SetTextureFormat(ETG_TextureFormat InFormat)`
- L225 _public function_ `FORCEINLINE float GetMidPoint() const`
- L226 _public function_ `FORCEINLINE float GetStandardHeight() const`
- L227 _public function_ `FORCEINLINE int32 GetWidth() const` — 2^7 is 128 and Width starts with 1. So 256, 1k, 2k, 4k and 8k
- L228 _public function_ `FORCEINLINE int32 GetHeight() const`
- L229 _public function_ `FORCEINLINE int32 GetXTiles() const`
- L230 _public function_ `FORCEINLINE int32 GetYTiles() const`
- L231 _public function_ `FORCEINLINE int32 GetXTileSize() const`
- L232 _public function_ `FORCEINLINE int32 GetYTileSize() const`
- L233 _public function_ `FORCEINLINE ETG_TextureFormat GetTextureFormat() const`
- L235 _public function_ `BufferDescriptor GetDescriptor() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L95 _typedef_ `typedef std::shared_ptr<RenderMesh> RenderMeshPtr;`
- L98 _typedef_ `typedef std::shared_ptr<RenderMesh_Editor> RenderMesh_EditorPtr;`
- L101 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP> RenderMaterial_BPPtr;`
- L206 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPreviewMeshUpdateEvent) FPreviewMeshUpdateEvent OnPreviewMeshChangedEvent;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/MixUpdateCycle.h` (Other)


#### class `MixTextureSet`  
`class MixTextureSet : public TextureSet`  
_L26-30_
- inherits: `TextureSet`
- L29 _public function_ `MixTextureSet() : TextureSet(1, 1)`

#### class `MixTargetUpdate`  
`class MixTargetUpdate`  
_L35-64_
- L38 _private member_ `TWeakObjectPtr<UMixInterface> MixObj;` — What is the mix that we're dealing with
- L39 _private member_ `TileInvalidateMatrix InvalidationMatrix;` — Mix invalidation matrix
- L40 _private member_ `int32 TargetId = -1;` — What is the target oo this update cycle
- L41 _private member_ `MixTextureSet LastRender;` — The last renders in this target. This is just a dummy placeholder
- L43 _private member_ `JobPtrW LastAddedJob;` — Last job that was added
- L46 _public prototype_ `MixTargetUpdate(TWeakObjectPtr<UMixInterface> InMixObj, int32 InTargetId);`
- L47 _public prototype_ `MixTargetUpdate(TWeakObjectPtr<UMixInterface> InMixObj, const TileInvalidateMatrix& InInvalidationMatrix, int32 InTargetId);`
- L48 _public prototype_ `~MixTargetUpdate();`
- L50 _public prototype_ `void InvalidateTile(int32 Row, int32 Col);`
- L51 _public prototype_ `void InvalidateAllTiles();`
- L52 _public prototype_ `void InvalidateNoTiles();`
- L58 _public function_ `TileInvalidateMatrix& GetInvalidationMatrix() const`
- L59 _public function_ `FORCEINLINE bool CheckIsValid(int32 Row, int32 Col) const`
- L60 _public function_ `FORCEINLINE bool IsInvalidated(int32 Row, int32 Col) const`
- L61 _public function_ `FORCEINLINE MixTextureSet& GetLastRender()`
- L62 _public function_ `FORCEINLINE int32 GetTargetId() const`
- L63 _public function_ `FORCEINLINE JobPtrW GetLastAddedJob() const`

#### class `MixUpdateCycle`  
`class MixUpdateCycle : public FGCObject`  
_L75-128_
- inherits: `FGCObject`
- L78 _private member_ `const TWeakObjectPtr<UMixInterface> MixObj;` — What is the mix that we're dealing with
- L80 _private member_ `std::shared_ptr<JobBatch> Batch = nullptr;` — The batch that we have
- L82 _private member_ `TArray<UMixInterface*> ActiveMixStack;` — Maintains the stack of mixes that are currently being updated. Mix remains in the list as long as evaluation is happening.
- L86 _private member_ `FInvalidationDetails Details;` — TODO: Pointers inside _details get GC'd. This needs fixing.
- L88 _private member_ `SceneTargetUpdatePtrVec Targets;` — The targets that we're going to be working on in this update cycle
- L94 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& collector) override;`
- L95 _private prototype_ `virtual FString GetReferencerName() const override;`
- L98 _public prototype_ `explicit MixUpdateCycle(const FInvalidationDetails& InDetails);`
- L101 _public prototype_ `JobPtrW AddJob(int32 InTargetId, JobUPtr JobObj);`
- L102 _public prototype_ `void AddTarget(SceneTargetUpdatePtr Target);`
- L104 _public prototype_ `void Begin();`
- L105 _public prototype_ `void End();`
- L107 _public prototype_ `void PushMix(UMixInterface* mix);`
- L108 _public prototype_ `void PopMix();`
- L109 _public prototype_ `UMixInterface* TopMix();`
- L110 _public prototype_ `bool ContainsMix(UMixInterface* InMixObj) const;`
- L112 _public prototype_ `JobPtrW LastAddedJob(int32 InTargetId) const;`
- L113 _public prototype_ `void SetBatch(std::shared_ptr<JobBatch> InBatch);`
- L114 _public prototype_ `uint32 LODLevel() const;`
- L115 _public prototype_ `bool NoCache() const;`
- L116 _public prototype_ `void MergeDetails(const FInvalidationDetails& InDetails);`
- L117 _public function_ `SceneTargetUpdatePtr GetTarget(size_t targetId)`
- L123 _public function_ `FInvalidationDetails& GetDetails() const`
- L124 _public function_ `FORCEINLINE const JobBatch* GetBatch() const`
- L125 _public function_ `FORCEINLINE size_t GetNumTargets() const`
- L126 _public function_ `FORCEINLINE UMixInterface* GetMix()`
- L127 _public function_ `FORCEINLINE bool IsTweaking() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L16 _typedef_ `typedef std::shared_ptr<Job> JobPtr;`
- L17 _typedef_ `typedef std::unique_ptr<Job> JobUPtr;`
- L18 _typedef_ `typedef std::weak_ptr<Job> JobPtrW;`
- L32 _typedef_ `typedef std::vector<MixTextureSet> SceneTextureSetVec;`
- L66 _typedef_ `typedef std::shared_ptr<MixTargetUpdate> SceneTargetUpdatePtr;`
- L67 _typedef_ `typedef std::vector<SceneTargetUpdatePtr> SceneTargetUpdatePtrVec;`
- L130 _typedef_ `typedef std::shared_ptr<MixUpdateCycle> MixUpdateCyclePtr;`
- L131 _typedef_ `typedef std::weak_ptr<MixUpdateCycle> SceneUpdateCyclePtrW;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/Mix/ViewportSettings.h` (Other)


#### struct `FMaterialMappingInfo`  
`struct FMaterialMappingInfo`  
_L12-23_
- reflection: `USTRUCT()`
- L17 _public member_ `FName MaterialInput;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L20 _public member_ `FName Target;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L22 _public function_ `bool HasTarget() const`

#### struct `FViewportSettings`  
`struct FViewportSettings`  
_L26-56_
- reflection: `USTRUCT()`
- L31 _public member_ `TObjectPtr<UMaterial> Material;` — `UPROPERTY(EditAnywhere, Category = "Viewport Material", NoClear)`
- L34 _public member_ `TArray<FMaterialMappingInfo> MaterialMappingInfos;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Viewport Material")`
- L36 _public prototype_ `void InitDefaultSettings(FName InitialTargetName);`
- L37 _public prototype_ `void SetDefaultTarget(FName DefaultTargetName);`
- L39 _public prototype_ `UMaterial* GetDefaultMaterial();`
- L41 _public prototype_ `FName GetMaterialName() const;`
- L42 _public prototype_ `FName GetMaterialMappingInfo(const FName MaterialInput);`
- L43 _public prototype_ `bool ContainsMaterialMappingInfo(const FName InMaterialInput);`
- L45 _public prototype_ `bool RemoveMaterialMappingForTarget(FName OutputNode);`
- L46 _public prototype_ `void OnMaterialUpdate();`
- L47 _public prototype_ `void OnTargetRename(const FName OldName, const FName NewName);`
- L49 _public prototype_ `int NumAssignedTargets();`
- L51 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FViewportSettingsUpdateEvent) FViewportSettingsUpdateEvent OnViewportMaterialChangedEvent;`
- L54 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FMaterialMappingChangedEvent) FMaterialMappingChangedEvent OnMaterialMappingChangedEvent;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE(FViewportSettingsUpdateEvent) FViewportSettingsUpdateEvent OnViewportMaterialChangedEvent;`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMaterialMappingChangedEvent) FMaterialMappingChangedEvent OnMaterialMappingChangedEvent;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/ModelObject.h` (Other)


#### struct `FInvalidationDetails`  
`struct FInvalidationDetails`  
_L20-89_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TWeakObjectPtr<UMixInterface> Mix = nullptr;` — The mix that is being invalidated
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDone, const FInvalidationDetails*);`
- L27 _public member_ `FOnDone OnDone;` — Delegate allowing to provide a user callback once the invalidation is executed
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnQueued, const FInvalidationDetails*);`
- L30 _public member_ `FOnDone OnQueued;` — Delegate allowing to provide a user callback once the invalidation is executed
- L32 _public member_ `bool bReload = false;` — Whether to reload the sources or not
- L33 _public member_ `bool bSelective = true;` — Selective invalidation [tile based]
- L34 _public member_ `bool bTweaking = false;` — Whether being tweaked or not
- L35 _public member_ `bool bExporting = false;` — Should only be true in case of exporting.
- L38 _public member_ `bool bForceInvalidateParent = false;` — The list of things that have been invalidated
- L39 _public member_ `bool bRender = false;` — Re-render
- L41 _public member_ `mutable CHashPtr HashValue = nullptr;` — The hash for this invalidation
- L43 _public prototype_ `FInvalidationDetails& All();`
- L44 _public prototype_ `FInvalidationDetails& None();`
- L45 _public prototype_ `FInvalidationDetails& Merge(const FInvalidationDetails& other);` — Merge the other details with this one,
- L49 _public prototype_ `CHashPtr Hash() const;`
- L50 _public prototype_ `bool IsDiscard() const;`
- L52 _public prototype_ `void BroadcastOnDone() const;` — Trigger the broadcast of the OnDone delegate AND all
- L55 _public prototype_ `void BroadcastOnQueued() const;`
- L57 _public function_ `FInvalidationDetails() : Mix(nullptr)`
- L58 _public prototype_ `explicit FInvalidationDetails(const TWeakObjectPtr<UMixInterface> InMixObj);`
- L62 _public function_ `template <typename ListType> static TArray<ListType*> MergeList(const TArray<ListType*>& List1, const TArray<ListType*>& List2)`
- L87 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDoneMulti, const FInvalidationDetails*);`
- L88 _private member_ `FOnDoneMulti OnDoneMergedInternal;` — "Private" multicast delegate where we merge OnDone delegates for merged details

#### struct `FModelInvalidateInfo`  
`struct FModelInvalidateInfo`  
_L93-114_
- reflection: `USTRUCT(Blueprintable, BlueprintType)`
- L98 _public member_ `TObjectPtr<UModelObject> Trigger = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Trigger Info")` — This is the model object that triggered the chain of ModelInvalidate calls
- L100 _public member_ `FInvalidationDetails Details;` — details about the invalidation
- L101 _public member_ `mutable CHashPtr HashValue = nullptr;` — The hash for this invalidation
- L103 _public prototype_ `CHashPtr Hash() const;`
- L105 _public function_ `FORCEINLINE UMixInterface* GetMix() const`

#### class `UModelObject`  
`class UModelObject : public UObject`  
_L121-140_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UObject`
- L127 _public prototype_ `virtual HashType HashValue_Simple() const;`
- L128 _public prototype_ `virtual FString ToString() const;`
- L133 _public prototype_ `static UObject* LoadObjectFromPath(const FString& distilledPath);`
- L136 _public function_ `template <typename ModelClass> static ModelClass* CreateNew(EObjectFlags Flags = RF_NoFlags)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDone, const FInvalidationDetails*);`
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueued, const FInvalidationDetails*);`
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDoneMulti, const FInvalidationDetails*);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Model/StaticImageResource.h` (Other)


#### class `UStaticImageResource`  
`class UStaticImageResource : public UModelObject`  
_L16-50_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UModelObject`
- L26 _private member_ `FString AssetUUID;` — `UPROPERTY()` — Unique id for the asset within the entire system
- L29 _private member_ `TiledBlobPtr BlobObj;` — The blob that represents the data for this source
- L32 _private member_ `bool bIsFilesystem = false;` — Is loading directly from the filesystem
- L34 _private prototype_ `virtual AsyncTiledBlobRef Load(MixUpdateCyclePtr Cycle);`
- L36 _private prototype_ `FDateTime GetAssetTimeStamp();`
- L41 _public prototype_ `virtual TiledBlobPtr GetBlob(MixUpdateCyclePtr Cycle, BufferDescriptor* DesiredDesc, int32 TargetId);`
- L46 _public function_ `FORCEINLINE const FString& GetAssetUUID() const`
- L47 _public function_ `FORCEINLINE void SetAssetUUID(const FString& UUID)`
- L48 _public function_ `FORCEINLINE void SetIsFileSystem(bool bInIsFileSystem)`
- L49 _public function_ `FORCEINLINE bool IsFileSystem() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Profiling/RenderDoc/RenderDocManager.h` (Other)


#### class `TextureGraphEditor::RenderDocManager`  
`class RenderDocManager`  
_L13-27_
- L17 _public prototype_ `RenderDocManager();`
- L18 _public prototype_ `~RenderDocManager();`
- L19 _public prototype_ `void Initialize();`
- L21 _public prototype_ `void CaptureNextBatch();`
- L22 _public prototype_ `void CapturePreviousBatch();`
- L23 _public prototype_ `void BeginCapture();`
- L24 _public prototype_ `void EndCapture();`
- L25 _public prototype_ `void CaptureNextBatchHistogram();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderDocTextureGraph, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderDocTextureGraph, Log, All);`
- L11 _namespace_ `namespace TextureGraphEditor`
- L28 _typedef_ `typedef std::unique_ptr<RenderDocManager> RenderDocManagerPtr;` (scope `TextureGraphEditor`)

### `Plugins/TextureGraph/Source/TextureGraphEngine/Profiling/StatGroup.h` (Other)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("TextureGraphEngine"), STATGROUP_TextureGraphEngine, STATCAT_Advanced)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/TextureGraphEngine.h` (Other)


#### class `FTextureGraphEngineModule`  
`class FTextureGraphEngineModule : public FDefaultGameModuleImpl`  
_L46-55_
- inherits: `FDefaultGameModuleImpl`
- L49 _private member_ `FString _libPath;`
- L50 _private member_ `FString _pluginName;`
- L51 _private prototype_ `bool MapShaders();`
- L53 _public prototype_ `virtual void StartupModule() override;`
- L54 _public prototype_ `virtual FString GetParentPluginName();`

#### class `EngineObserverSource`  
`class EngineObserverSource`  
_L58-70_
- L64 _protected function_ `virtual void Created()`
- L65 _protected function_ `virtual void Destroyed()`
- L68 _public prototype_ `EngineObserverSource() = default;`
- L69 _public prototype_ `virtual ~EngineObserverSource() = default;`

#### class `TextureGraphEngine`  
`class TextureGraphEngine`  
_L80-170_
- L83 _private member_ `static TextureGraphEngine* GInstance;` — Static instance. Use Create to create a new instance. Destroy the current instance first
- L84 _private member_ `static std::atomic<bool> bGIsEngineDestroying;` — Whether the Engine is in a state of being destroyed
- L86 _private member_ `bool bIsEngineInitDone = false;` — Whether the Engine init is actually done. This is to peg it to the editor
- L88 _private prototype_ `explicit TextureGraphEngine(bool bInIsTestMode);`
- L90 _private prototype_ `void InitEngineInternal();` — This is to allow modules of Engine to access s_instance
- L92 _private prototype_ `~TextureGraphEngine();`
- L94 _private member_ `static EngineObserverSourcePtr GObserverSource;` — Engine observer source interface where public signals will be emitted from.
- L97 _private member_ `TStrongObjectPtr<UMaterialManager> MaterialMgrObj;` — The material manager
- L98 _private member_ `MixManagerUPtr MixMgrObj;` — Mix manager
- L99 _private member_ `SchedulerPtr SchedulerObj;` — The job scheduler
- L100 _private member_ `DeviceManagerPtr DeviceManagerObj;` — The device manager
- L101 _private member_ `BlobberPtr BlobberObj;` — The blobber that is responsible for managing all the blobs and their transfers across devices
- L102 _private member_ `TextureGraphEditor::RenderDocManagerPtr RenderDocMgrObj;` — The RenderDoc manager that we have
- L103 _private member_ `TMap<const UMixInterface*, ErrorReporterPtr> ErrorReporters;` — Error reporters mapped by Mix (each mix has their own reporter to allow
- L105 _private member_ `uint64 FrameId = 1;` — managing errors (report/resolve) per mix
- L108 _private member_ `bool bIsTestMode = false;` — Test related functionality
- L109 _private member_ `std::atomic_bool bRunEngine = false;` — Whether to run the engine or not. If no one is using TextureGraph,
- L112 _private member_ `std::atomic_bool bIsLocked = false;` — Whether the engine is locked. This is only available in test mode.
- L117 _private member_ `std::mutex* LockWaitMutex = nullptr;` — Mutex used to wait if the engine is locked and asked to be destroyed
- L118 _private member_ `std::condition_variable* LockWaitCVar = nullptr;` — Conditional variable to be used in conjunction with the mutex
- L120 _private prototype_ `void FirstRunInit();`
- L128 _public prototype_ `static void Create(bool bIsTestMode = false);` — Init can be called again and again to reset the engine and recreate the data structures
- L131 _public prototype_ `static void Destroy();` — Destroy the current instance
- L133 _public prototype_ `static void InitTests();`
- L134 _public prototype_ `static void DoneTests();`
- L137 _public prototype_ `static void Update(float dt);` — Update the components in the engine
- L140 _public prototype_ `static void RegisterObserverSource(const EngineObserverSourcePtr& observerSource);` — Register the observer source (only one active)
- L143 _public prototype_ `static void RegisterErrorReporter(const UMixInterface* MixKey, const ErrorReporterPtr& ErrorReporter);` — Register the Error Reporter
- L145 _public prototype_ `static void Lock();`
- L146 _public prototype_ `static void Unlock();`
- L147 _public prototype_ `static void SetRunEngine();`
- L153 _public function_ `FORCEINLINE static TextureGraphEngine* GetInstance()` — The if check is temporary over here since no one is initialising this right now
- L154 _public function_ `FORCEINLINE static MixManager* GetMixManager()`
- L155 _public function_ `FORCEINLINE static UMaterialManager* GetMaterialManager()`
- L156 _public function_ `FORCEINLINE static Scheduler* GetScheduler()`
- L157 _public function_ `FORCEINLINE static DeviceManager* GetDeviceManager()`
- L158 _public function_ `FORCEINLINE static Blobber* GetBlobber()`
- L159 _public function_ `FORCEINLINE static int64 GetFrameId()`
- L160 _public function_ `FORCEINLINE static TextureGraphEditor::RenderDocManager* GetRenderDocManager()`
- L162 _public function_ `FORCEINLINE static bool IsTestMode()`
- L164 _public function_ `FORCEINLINE static bool IsDestroying()`
- L165 _public function_ `FORCEINLINE static EngineObserverSourcePtr GetObserverSource()`
- L166 _public function_ `FORCEINLINE static FTextureGraphErrorReporter* GetErrorReporter(UMixInterface* MixKey)`
- L168 _public function_ `FORCEINLINE static bool IsRunning()`
- L169 _public prototype_ `static bool BlockCommandlets();`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphEngine, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphEngine, Log, All);`
- L23 _typedef_ `typedef std::unique_ptr<MixManager> MixManagerUPtr;`
- L26 _typedef_ `typedef std::unique_ptr<AssetsManager> AssetsManagerPtr;`
- L29 _typedef_ `typedef std::unique_ptr<DeviceManager> DeviceManagerPtr;`
- L34 _typedef_ `typedef std::unique_ptr<Blobber> BlobberPtr;`
- L37 _typedef_ `typedef std::unique_ptr<Scheduler> SchedulerPtr;`
- L39 _namespace_ `namespace TextureGraphEditor`
- L42 _typedef_ `typedef std::unique_ptr<RenderDocManager> RenderDocManagerPtr;` (scope `TextureGraphEditor`)
- L71 _typedef_ `typedef std::shared_ptr<EngineObserverSource> EngineObserverSourcePtr;`
- L72 _typedef_ `typedef std::shared_ptr<FTextureGraphErrorReporter> ErrorReporterPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/TextureGraphEngineGameInstance.h` (Other)
_(no declarations extracted)_

### `Plugins/TextureGraph/Source/TextureGraphEngine/TextureGraphErrorReporter.h` (Other)


#### struct `FTextureGraphErrorReport`  
`struct FTextureGraphErrorReport`  
_L8-18_
- L10 _public member_ `int32 ErrorId;`
- L11 _public member_ `FString ErrorMsg;`
- L12 _public member_ `UObject* ReferenceObj = nullptr;`
- L14 _public function_ `FString GetFormattedMessage()`

#### enum `ETextureGraphErrorType`  
`enum class ETextureGraphErrorType: int32`  
_L20-29_
- L22 _public enumerator_ `UNSUPPORTED_TYPE`
- L23 _public enumerator_ `MISSING_REQUIRED_INPUT`
- L24 _public enumerator_ `RECURSIVE_CALL`
- L25 _public enumerator_ `UNSUPPORTED_MATERIAL`
- L26 _public enumerator_ `SUBGRAPH_INTERNAL_ERROR`
- L27 _public enumerator_ `NODE_WARNING`
- L28 _public enumerator_ `INPUT_ARRAY_WARNING`

#### class `FTextureGraphErrorReporter`  
`class FTextureGraphErrorReporter`  
_L30-57_
- L33 _public function_ `FTextureGraphErrorReporter()`
- L37 _public prototype_ `virtual ~FTextureGraphErrorReporter() = default;`
- L39 _public prototype_ `virtual FTextureGraphErrorReport ReportLog(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr);`
- L41 _public prototype_ `virtual FTextureGraphErrorReport ReportWarning(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr);`
- L43 _public prototype_ `virtual FTextureGraphErrorReport ReportError(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr);`
- L45 _public function_ `virtual void Clear()`
- L50 _protected member_ `ErrorReportMap CompilationErrors;`
- L53 _public function_ `ErrorReportMap GetCompilationErrors() const`

#### Free symbols / members of external scopes

- L5 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphError, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphError, Log, All);`
- L19 _typedef_ `using ErrorReportMap = TMap<int32, TArray<FTextureGraphErrorReport>>;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/BlobTransform.h` (Other)


#### struct `ResourceBindInfo`  
`struct ResourceBindInfo`  
_L24-36_
- L26 _public member_ `FString Target;` — Named target (for devices that support this)
- L27 _public member_ `int32 TargetIndex = -1;` — Indexed target (for devices that support this)
- L28 _public member_ `Device* Dev = nullptr;` — The Dev to which the resource will be bound
- L29 _public member_ `bool bCalculateHash = false;` — Calculate hash immediately
- L30 _public member_ `bool bWriteTarget = false;` — Whether the resource is a write target or not
- L31 _public member_ `bool bStaticBuffer = false;` — Whether its a static buffer or not. Only used with writeTarget == true
- L32 _public member_ `bool bIsCombined = false;` — Used to transfer information to material if texture being registered to array parameter
- L33 _public member_ `int32 NumTilesX = 0;` — [Optional] Number of xtiles
- L34 _public member_ `int32 NumTilesY = 0;` — [Optional] Number of ytiles
- L35 _public member_ `uint64 BatchId = 0;` — [Optional] The batch id when this was last bound

#### struct `TransformArgs`  
`struct TransformArgs`  
_L43-57_
- L45 _public member_ `int32 TargetId = -1;` — The target id
- L46 _public member_ `const Job* JobObj = nullptr;` — The job that this is being triggered from
- L47 _public member_ `Device* Dev = nullptr;` — The Dev on which to execute the transform.
- L50 _public member_ `BlobRef Target;` — The target that the BlobObj transform is going to have to render to.
- L54 _public member_ `const RenderMesh* Mesh = nullptr;` — The mesh that we are targeting
- L56 _public member_ `std::shared_ptr<MixUpdateCycle> Cycle;` — The update cycle

#### struct `TransformResult`  
`struct TransformResult`  
_L60-65_
- L62 _public member_ `std::exception_ptr ExInner;` — Original exception that was raised by the action
- L63 _public member_ `int32 ErrorCode = 0;` — What is the error code
- L64 _public member_ `BlobRef Target;` — The target that was passed in TransformArgs returned

#### class `BlobTransform`  
`class BlobTransform`  
_L81-162_
- L87 _protected member_ `FString Name;` — User friendly Name of the transformation function
- L88 _protected member_ `mutable CHashPtr HashValue;` — The hash for this BlobObj transform
- L91 _public prototype_ `explicit BlobTransform(FString Name);`
- L92 _public prototype_ `virtual ~BlobTransform();`
- L94 _public function_ `virtual size_t NumTargetDevices() const`
- L95 _public prototype_ `virtual Device* TargetDevice(size_t Index) const = 0;`
- L96 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) = 0;`
- L97 _public prototype_ `virtual CHashPtr Hash() const;`
- L98 _public function_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString TransformName)`
- L103 _public prototype_ `virtual AsyncBufferResultPtr Bind(BlobPtr BlobObj, const ResourceBindInfo& BindInfo);`
- L104 _public prototype_ `virtual AsyncBufferResultPtr Unbind(BlobPtr BlobObj, const ResourceBindInfo& BindInfo);`
- L106 _public function_ `virtual void Bind(int32 InValue, const ResourceBindInfo& BindInfo)`
- L107 _public function_ `virtual void Bind(float InValue, const ResourceBindInfo& BindInfo)`
- L108 _public function_ `virtual void Bind(const FLinearColor& InValue, const ResourceBindInfo& BindInfo)`
- L109 _public function_ `virtual void Bind(const FIntVector4& InValue, const ResourceBindInfo& BindInfo)`
- L110 _public function_ `virtual void Bind(const FMatrix& InValue, const ResourceBindInfo& BindInfo)`
- L111 _public function_ `virtual void BindStruct(const char* ValueAddress, size_t StructSize, const ResourceBindInfo& BindInfo)`
- L112 _public function_ `virtual void BindScalarArray(const char* StartingAddress, size_t TypeSize, size_t ArraySize, const ResourceBindInfo& BindInfo)`
- L115 _public function_ `template <typename Type> void BindScalarArray(const TArray<Type>& InValue, const ResourceBindInfo& BindInfo)`
- L122 _public function_ `template<typename StructType> void BindStruct(const StructType& InValue, const ResourceBindInfo& BindInfo)`
- L127 _public prototype_ `virtual void Bind(const Vector3& InValue, const ResourceBindInfo& BindInfo);`
- L128 _public prototype_ `virtual void Bind(const Vector4& InValue, const ResourceBindInfo& BindInfo);`
- L129 _public prototype_ `virtual void Bind(const Tangent& InValue, const ResourceBindInfo& BindInfo);`
- L130 _public function_ `virtual void Bind(const FString& InValue, const ResourceBindInfo& BindInfo)`
- L132 _public prototype_ `virtual bool GeneratesData() const;`
- L133 _public prototype_ `virtual bool CanHandleTiles() const;`
- L135 _public prototype_ `virtual AsyncPrepareResult PrepareResources(const TransformArgs& Args);`
- L139 _public function_ `virtual void Unbind(int32 InValue, const ResourceBindInfo& BindInfo)` — No-Ops
- L140 _public function_ `virtual void Unbind(float InValue, const ResourceBindInfo& BindInfo)`
- L141 _public function_ `virtual void Unbind(const FLinearColor& InValue, const ResourceBindInfo& BindInfo)`
- L142 _public function_ `virtual void Unbind(const FIntVector4& InValue, const ResourceBindInfo& BindInfo)`
- L143 _public function_ `virtual void Unbind(const FMatrix& InValue, const ResourceBindInfo& BindInfo)`
- L144 _public prototype_ `virtual void Unbind(const Vector3& InValue, const ResourceBindInfo& BindInfo);`
- L145 _public prototype_ `virtual void Unbind(const Vector4& InValue, const ResourceBindInfo& BindInfo);`
- L146 _public prototype_ `virtual void Unbind(const Tangent& InValue, const ResourceBindInfo& BindInfo);`
- L147 _public function_ `virtual void Unbind(const FString& InValue, const ResourceBindInfo& BindInfo)`
- L149 _public prototype_ `virtual ENamedThreads::Type ExecutionThread() const;`
- L150 _public prototype_ `virtual bool IsAsync() const;`
- L151 _public function_ `virtual FString GetName() const`
- L157 _public function_ `virtual UObject* GetErrorOwner() const` — During the execution of the transform, errors can be raised to the TextureGraphEngine::ErrorReporter and associated to the "ErrorOwner" object provided by this method. return null by default

#### class `Null_Transform`  
`class Null_Transform : public BlobTransform`  
_L169-185_
- inherits: `BlobTransform`
- L172 _private member_ `Device* Dev = nullptr;` — The device that this transform belongs to
- L173 _private member_ `bool bIsAsync = false;` — Whether the transform is async or not
- L174 _private member_ `bool bGeneratesData = false;` — The null transform doesn't generate data by default
- L177 _public prototype_ `Null_Transform(Device* Dev, FString Name, bool bIsAsync_ = false, bool bGeneratesData_ = false);`
- L178 _public prototype_ `virtual AsyncBufferResultPtr Bind(BlobPtr InValue, const ResourceBindInfo& BindInfo) override;`
- L179 _public prototype_ `virtual AsyncBufferResultPtr Unbind(BlobPtr BlobObj, const ResourceBindInfo& BindInfo) override;`
- L180 _public prototype_ `virtual bool IsAsync() const override;`
- L181 _public prototype_ `virtual bool GeneratesData() const override;`
- L182 _public prototype_ `virtual Device* TargetDevice(size_t Index) const override;`
- L183 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) override;`
- L184 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString TransformName) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _typedef_ `typedef std::shared_ptr<DeviceNativeTask> DeviceNativeTaskPtr;`
- L16 _typedef_ `typedef std::weak_ptr<DeviceNativeTask> DeviceNativeTaskPtrW;`
- L17 _typedef_ `typedef std::vector<DeviceNativeTaskPtr> DeviceNativeTaskPtrVec;`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlobTransform, Log, Log);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlobTransform, Log, Log);`
- L67 _typedef_ `typedef std::shared_ptr<TransformResult> TransformResultPtr;`
- L68 _typedef_ `typedef cti::continuable<TransformResultPtr> AsyncTransformResultPtr;`
- L69 _typedef_ `typedef cti::continuable<int32> AsyncPrepareResult;`
- L187 _typedef_ `typedef std::shared_ptr<BlobTransform> BlobTransformPtr;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_ArrayGrid.h` (Other)


#### class `T_ArrayGrid`  
`class T_ArrayGrid`  
_L15-20_
- L18 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor& DesiredOutputDesc, TArray<TiledBlobPtr> Inputs, int32 NumRows, int32 NumCols, FLinearColor BackgroundColor, int32 TargetId = 0);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.h` (Other)


#### class `FSH_BlendBase`  
`class FSH_BlendBase : public FSH_Base`  
_L18-43_
- inherits: `FSH_Base`
- L21 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendBase, FSH_Base);`
- L32 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FIgnoreAlpha, FClamp>;`
- L35 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L40 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParams, FShaderCompilerEnvironment& InEnv)`

#### class `FSH_BlendNormal`  
`class FSH_BlendNormal : public FSH_BlendBase`  
_L48-53_
- inherits: `FSH_BlendBase`
- L52 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendNormal, FSH_BlendBase);`

#### class `FSH_BlendAdd`  
`class FSH_BlendAdd : public FSH_BlendBase`  
_L58-63_
- inherits: `FSH_BlendBase`
- L62 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendAdd, FSH_BlendBase);`

#### class `FSH_BlendSubtract`  
`class FSH_BlendSubtract : public FSH_BlendBase`  
_L68-73_
- inherits: `FSH_BlendBase`
- L72 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendSubtract, FSH_BlendBase);`

#### class `FSH_BlendMultiply`  
`class FSH_BlendMultiply : public FSH_BlendBase`  
_L78-83_
- inherits: `FSH_BlendBase`
- L82 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendMultiply, FSH_BlendBase);`

#### class `FSH_BlendDivide`  
`class FSH_BlendDivide : public FSH_BlendBase`  
_L88-93_
- inherits: `FSH_BlendBase`
- L92 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendDivide, FSH_BlendBase);`

#### class `FSH_BlendDifference`  
`class FSH_BlendDifference : public FSH_BlendBase`  
_L97-102_
- inherits: `FSH_BlendBase`
- L101 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendDifference, FSH_BlendBase);`

#### class `FSH_BlendMax`  
`class FSH_BlendMax : public FSH_BlendBase`  
_L107-112_
- inherits: `FSH_BlendBase`
- L111 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendMax, FSH_BlendBase);`

#### class `FSH_BlendMin`  
`class FSH_BlendMin : public FSH_BlendBase`  
_L117-122_
- inherits: `FSH_BlendBase`
- L121 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendMin, FSH_BlendBase);`

#### class `FSH_BlendStep`  
`class FSH_BlendStep : public FSH_BlendBase`  
_L127-132_
- inherits: `FSH_BlendBase`
- L131 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendStep, FSH_BlendBase);`

#### class `FSH_BlendOverlay`  
`class FSH_BlendOverlay : public FSH_BlendBase`  
_L137-142_
- inherits: `FSH_BlendBase`
- L141 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendOverlay, FSH_BlendBase);`

#### class `FSH_BlendDistort`  
`class FSH_BlendDistort : public FSH_BlendBase`  
_L147-152_
- inherits: `FSH_BlendBase`
- L151 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BlendDistort, FSH_BlendBase);`

#### class `T_Blend`  
`class T_Blend`  
_L156-187_
- L159 _public prototype_ `T_Blend();`
- L160 _public prototype_ `~T_Blend();`
- L175 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, EBlendModes::Type InBlendMode, const FBlendSettings* InBlendSettings);`
- L176 _public prototype_ `static TiledBlobPtr CreateNormal(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L177 _public prototype_ `static TiledBlobPtr CreateAdd(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L178 _public prototype_ `static TiledBlobPtr CreateSubtract(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L179 _public prototype_ `static TiledBlobPtr CreateMultiply(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L180 _public prototype_ `static TiledBlobPtr CreateDivide(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L181 _public prototype_ `static TiledBlobPtr CreateDifference(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L182 _public prototype_ `static TiledBlobPtr CreateMax(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L183 _public prototype_ `static TiledBlobPtr CreateMin(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L184 _public prototype_ `static TiledBlobPtr CreateStep(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L185 _public prototype_ `static TiledBlobPtr CreateOverlay(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`
- L186 _public prototype_ `static TiledBlobPtr CreateDistort(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, int InTargetId, const FBlendSettings* InBlendSettings);`

#### struct `T_Blend::FBlendSettings`  
`struct FBlendSettings`  
_L162-170_
- L164 _public member_ `TiledBlobPtr BackgroundTexture;`
- L165 _public member_ `TiledBlobPtr ForegroundTexture;`
- L166 _public member_ `TiledBlobPtr Mask;`
- L167 _public member_ `float Opacity;`
- L168 _public member_ `bool bIgnoreAlpha;`
- L169 _public member_ `bool bClamp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blur.h` (Other)


#### class `FSH_GaussianBlur`  
`class FSH_GaussianBlur : public FSH_Base`  
_L17-34_
- inherits: `FSH_Base`
- L21 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GaussianBlur, FSH_Base);`
- L30 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FSH_DirectionalBlur`  
`class FSH_DirectionalBlur : public FSH_Base`  
_L38-59_
- inherits: `FSH_Base`
- L42 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_DirectionalBlur, FSH_Base);`
- L55 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FSH_RadialBlur`  
`class FSH_RadialBlur : public FSH_Base`  
_L64-85_
- inherits: `FSH_Base`
- L68 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_RadialBlur, FSH_Base);`
- L81 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_Blur`  
`class T_Blur`  
_L90-105_
- L94 _public member_ `const static FVector2f RadialBlurCenter;`
- L96 _public prototype_ `T_Blur();`
- L97 _public prototype_ `~T_Blur();`
- L102 _public prototype_ `static TiledBlobPtr CreateGaussian(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, int32 InRadius, int InTargetId);`
- L103 _public prototype_ `static TiledBlobPtr CreateDirectional(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, float InAngle, float InStrength, int InTargetId);`
- L104 _public prototype_ `static TiledBlobPtr CreateRadial(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, float InRadius, float InStrength, int InTargetId);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Brightness.h` (Other)


#### class `FSH_Brightness`  
`class FSH_Brightness : public FSH_Base`  
_L15-34_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Brightness, FSH_Base);`
- L29 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L33 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Brightness`  
`class T_Brightness`  
_L36-43_
- L42 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, float Brightness, float Contrast, int32 TargetId);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.h` (Other)


#### enum `EColorChannel`  
`enum class EColorChannel : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Red = 0 UMETA(DisplayName = "Red")`
- L17 _public enumerator_ `Green = 1 UMETA(DisplayName = "Green")`
- L18 _public enumerator_ `Blue = 2 UMETA(DisplayName = "Blue")`
- L19 _public enumerator_ `Alpha = 3 UMETA(DisplayName = "Alpha")`

#### class `FSH_ChannelSplitter`  
`class FSH_ChannelSplitter : public FSH_Base`  
_L25-37_
- inherits: `FSH_Base`
- L28 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSplitter, FSH_Base);`
- L31 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, SourceTexture) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_ChannelSplitter_Red`  
`class FSH_ChannelSplitter_Red : public FSH_ChannelSplitter`  
_L42-47_
- inherits: `FSH_ChannelSplitter`
- L46 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSplitter_Red, FSH_ChannelSplitter);`

#### class `FSH_ChannelSplitter_Green`  
`class FSH_ChannelSplitter_Green : public FSH_ChannelSplitter`  
_L52-57_
- inherits: `FSH_ChannelSplitter`
- L56 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSplitter_Green, FSH_ChannelSplitter);`

#### class `FSH_ChannelSplitter_Blue`  
`class FSH_ChannelSplitter_Blue : public FSH_ChannelSplitter`  
_L62-67_
- inherits: `FSH_ChannelSplitter`
- L66 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSplitter_Blue, FSH_ChannelSplitter);`

#### class `FSH_ChannelSplitter_Alpha`  
`class FSH_ChannelSplitter_Alpha : public FSH_ChannelSplitter`  
_L72-77_
- inherits: `FSH_ChannelSplitter`
- L76 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSplitter_Alpha, FSH_ChannelSplitter);`

#### class `FSH_ChannelCombiner`  
`class FSH_ChannelCombiner : public FSH_Base`  
_L82-98_
- inherits: `FSH_Base`
- L86 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelCombiner, FSH_Base);`
- L89 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, SourceRed) SHADER_PARAMETER_TEXTURE(Texture2D, SourceGreen) SHADER_PARAMETER_TEXTURE(Texture2D, SourceBlue) SHADER_PARAMETER_TEXTURE(Texture2D, SourceAlpha) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_ChannelSwizzle`  
`class FSH_ChannelSwizzle : public FSH_Base`  
_L108-123_
- inherits: `FSH_Base`
- L112 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ChannelSwizzle, FSH_Base);`
- L119 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_SwizzleDstChannelRed, FVar_SwizzleDstChannelGreen, FVar_SwizzleDstChannelBlue, FVar_SwizzleDstChannelAlpha>;`

#### class `T_Channel`  
`class T_Channel`  
_L128-134_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Clamp.h` (Other)


#### class `FSH_Clamp`  
`class FSH_Clamp : public FSH_Base`  
_L15-32_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Clamp, FSH_Base);`

#### class `FSH_SmoothStep`  
`class FSH_SmoothStep : public FSH_Base`  
_L37-54_
- inherits: `FSH_Base`
- L41 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_SmoothStep, FSH_Base);`

#### class `FSH_Min`  
`class FSH_Min : public FSH_Base`  
_L59-75_
- inherits: `FSH_Base`
- L63 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Min, FSH_Base);`

#### class `FSH_Max`  
`class FSH_Max : public FSH_Base`  
_L80-96_
- inherits: `FSH_Base`
- L84 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Max, FSH_Base);`

#### class `T_Clamp`  
`class T_Clamp`  
_L98-108_
- L104 _public prototype_ `static TiledBlobPtr CreateClamp(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, TiledBlobPtr MinValue, TiledBlobPtr MaxValue, int32 TargetId);`
- L105 _public prototype_ `static TiledBlobPtr CreateSmoothStep(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, TiledBlobPtr MinValue, TiledBlobPtr MaxValue, int32 TargetId);`
- L106 _public prototype_ `static TiledBlobPtr CreateMin(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Input1, TiledBlobPtr Input2, int32 TargetId);`
- L107 _public prototype_ `static TiledBlobPtr CreateMax(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Input1, TiledBlobPtr Input2, int32 TargetId);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.h` (Other)


#### class `FSH_Grayscale`  
`class FSH_Grayscale : public FSH_Base`  
_L15-28_
- inherits: `FSH_Base`
- L18 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Grayscale, FSH_Base);`
- L22 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, SourceTexture) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_Threshold`  
`class FSH_Threshold : public FSH_Base`  
_L33-47_
- inherits: `FSH_Base`
- L36 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Threshold, FSH_Base);`
- L40 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) SHADER_PARAMETER(float, Threshold) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_HSV`  
`class FSH_HSV : public FSH_Base`  
_L52-68_
- inherits: `FSH_Base`
- L55 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_HSV, FSH_Base);`
- L59 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) SHADER_PARAMETER(float, Hue) SHADER_PARAMETER(float, Saturation) SHADER_PARAMETER(float, Value) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_RGB2HSV`  
`class FSH_RGB2HSV : public FSH_Base`  
_L73-86_
- inherits: `FSH_Base`
- L76 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_RGB2HSV, FSH_Base);`
- L80 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_HSV2RGB`  
`class FSH_HSV2RGB : public FSH_Base`  
_L91-104_
- inherits: `FSH_Base`
- L94 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_HSV2RGB, FSH_Base);`
- L98 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_Premult`  
`class FSH_Premult : public FSH_Base`  
_L109-122_
- inherits: `FSH_Base`
- L112 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Premult, FSH_Base);`
- L116 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `FSH_ColorCorrection`  
`class FSH_ColorCorrection : public FSH_Base`  
_L127-147_
- inherits: `FSH_Base`
- L130 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ColorCorrection, FSH_Base);`
- L134 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) SHADER_PARAMETER(float, Brightness) SHADER_PARAMETER(float, Contrast) SHADER_PARAMETER(float, Gamma) SHADER_PARAMETER(float, Saturation) SHADER_PARAMETER(FLinearColor, TemperatureRGB) SHADER_PARAMETER(float, TemperatureStrength) SHADER_PARAMETER(float, TemperatureBrightnessNormalization) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `T_Color`  
`class T_Color`  
_L152-158_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Conversions.h` (Other)


#### class `FSH_NormalFromHeightMap`  
`class FSH_NormalFromHeightMap : public FSH_Base`  
_L16-35_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NormalFromHeightMap, FSH_Base);`
- L23 _public function_ `SHADER_PARAMETER_STRUCT(FTileInfo, TileInfo) SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, SourceTexture) SHADER_PARAMETER(float, Strength) SHADER_PARAMETER(float, Offset) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L34 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Params, FShaderCompilerEnvironment& Env)`

#### class `T_Conversions`  
`class T_Conversions`  
_L40-51_
- L43 _public prototype_ `T_Conversions();`
- L44 _public prototype_ `~T_Conversions();`
- L50 _public prototype_ `static TiledBlobPtr CreateNormalFromHeightMap(MixUpdateCyclePtr InCycle, TiledBlobPtr HeightMapTexture, float Offset, float Strength, int InTargetId, BufferDescriptor DesiredOutputDesc);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_ExtractMaterialIds.h` (Other)


#### struct `FMaterialIDInfo`  
`struct FMaterialIDInfo`  
_L18-51_
- reflection: `USTRUCT()`
- L22 _public function_ `FMaterialIDInfo()`
- L24 _public function_ `FMaterialIDInfo(int32 InId, FColor InSrgbColor, FLinearColor InSrgbLinearColor)`
- L32 _public member_ `int32 Id = 0;` — `UPROPERTY()`
- L35 _public member_ `FColor RGBColor = FColor::Black;` — `UPROPERTY(VisibleAnywhere, Category = MaterialIDInfo)`
- L38 _public member_ `FLinearColor SrgbLinearColor = FLinearColor::Black;` — `UPROPERTY()`
- L40 _public function_ `HashType HashValue() const`

#### struct `FMaterialIDMaskInfo`  
`struct FMaterialIDMaskInfo`  
_L54-74_
- reflection: `USTRUCT()`
- L58 _public function_ `FMaterialIDMaskInfo()`
- L60 _public function_ `FMaterialIDMaskInfo(const int32 InId, FColor InDisplayColor)`
- L67 _public member_ `int32 MaterialIdReferenceId = 0;` — `UPROPERTY()`
- L70 _public member_ `FColor Color = FColor::Black;` — `UPROPERTY(VisibleAnywhere, Category = MaterialIDInfo, meta = (NoResetToDefault))`
- L73 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, Category = MaterialIDInfo)`

#### struct `FMaterialIDCollection`  
`struct FMaterialIDCollection`  
_L77-143_
- reflection: `USTRUCT()`
- L81 _public function_ `FMaterialIDCollection()`
- L84 _public member_ `TArray<FMaterialIDInfo> Infos;` — `UPROPERTY()`
- L86 _public function_ `int32 Num() const`
- L91 _public function_ `bool GetColor(const int32 Id, FLinearColor& OutColor)`
- L105 _public function_ `HashType HashValue() const`
- L122 _public function_ `FString GetColorName(const int32 Id)`
- L131 _public function_ `const FMaterialIDInfo* GetIdInfo(int32 Id)`

#### class `HSVBucket`  
`class HSVBucket`  
_L145-180_
- L148 _public member_ `static const int HBuckets = 15;`
- L149 _public member_ `static const int SBuckets = 5;`
- L150 _public member_ `static const int VBuckets = 5;`
- L151 _public member_ `static const int HCount = 360 / HBuckets;`
- L152 _public member_ `static const int SCount = 100 / SBuckets;`
- L153 _public member_ `static const int VCount = 100 / VBuckets;`
- L155 _public member_ `static const int MinPixelsCountThreshold = 10;`
- L156 _public member_ `inline static const float MinPixelsInTextureThreshold = 0.01f;`
- L157 _public member_ `inline static const float MinPixelsOccurance = 0.3f;`
- L158 _public member_ `inline static const float HRange = 359.0f;` — H Range is 0-360
- L159 _public member_ `inline static const float SRange = 99.0f;` — S Range is 0-100
- L160 _public member_ `inline static const float VRange = 99.0f;` — V Range is 0-100
- L164 _public member_ `int32 TotalCount = 0;` — Total count of all the pixels that fall into this bucket
- L165 _public member_ `int32 MaxIndividualCount = 0;` — The max number of a pixel that has fallen into this bucket
- L166 _public member_ `FIntVector3 MaxIndex;` — Index of the colour with the max count
- L167 _public member_ `Color3dArray ColorCount;` — Count of individual colours that fall into this bucket (in HSV space)
- L168 _public member_ `FIntVector3 HSVStart;` — The starting value of the HSV colours
- L169 _public member_ `TArray<FVector2f> Positions;` — Positions of each pixel
- L170 _public member_ `FVector2f MinPos;` — Min position (for calculating spread)
- L171 _public member_ `FVector2f MaxPos;` — Max position (for calculating spread)
- L173 _public prototype_ `HSVBucket(int32 InHBucket, int32 InSBucket, int32 InVBucket);`
- L175 _public prototype_ `void Add(const FLinearColor Color, int H, int S, int V, FVector2f Position);`
- L176 _public prototype_ `void Add(HSVBucket Rhs);`
- L177 _public prototype_ `static FIntVector3 GetBucket(const FLinearColor Pixel, int& OutH, int& OutS, int& OutV);`
- L178 _public prototype_ `FLinearColor GetColor(FIntVector3& OutHsv);`
- L179 _public prototype_ `bool ShouldConsider(int32 Width, int32 Height);`

#### class `Job_ExtractMaterialIds`  
`class Job_ExtractMaterialIds : public Job`  
_L183-206_
- inherits: `Job`
- L186 _private member_ `TiledBlobRef SourceTexture;`
- L187 _private member_ `TArray<FMaterialIDMaskInfo>& MaterialIDMaskInfo;`
- L188 _private member_ `FMaterialIDCollection& MaterialIDCollection;`
- L189 _private member_ `int32 ActiveColorsCount;`
- L192 _public prototype_ `Job_ExtractMaterialIds(int32 targetId, TiledBlobRef InSourceTexture, FMaterialIDCollection& MaterialIDInfoCollection, TArray<FMaterialIDMaskInfo>& InMaterialIDMaskInfo, int32& ActiveColorsCount, UObject* InErrorOwner = nullptr, uint16 priority = (uint16)E_Priority::kHigh, uint64 id = 0);`
- L195 _protected function_ `virtual void GetDependencies(JobPtrVec& prior, JobPtrVec& after, JobRunInfo runInfo) override`
- L196 _protected function_ `virtual AsyncPrepareResult PrepareTargets(JobBatch* batch)`
- L197 _protected function_ `virtual AsyncPrepareResult PrepareResources(JobBatch* batch)`
- L199 _protected function_ `virtual int32 Exec() override`
- L200 _protected function_ `virtual cti::continuable<int32> BindArgs_All(JobRunInfo runInfo)`
- L201 _protected function_ `virtual cti::continuable<int32> UnbindArgs_All(JobRunInfo runInfo)`
- L202 _protected function_ `virtual bool CanHandleTiles() const`
- L204 _protected prototype_ `virtual cti::continuable<int32> PreExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type returnThread) override;`
- L205 _protected prototype_ `virtual cti::continuable<int32> ExecAsync(ENamedThreads::Type ExecThread, ENamedThreads::Type ReturnThread) override;`

#### class `T_ExtractMaterialIds`  
`class T_ExtractMaterialIds`  
_L211-222_
- L214 _public prototype_ `T_ExtractMaterialIds();`
- L215 _public prototype_ `~T_ExtractMaterialIds();`
- L221 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr InCycle, TiledBlobPtr MaterialIDTexture, FMaterialIDCollection& MaterialIDCollection, TArray<FMaterialIDMaskInfo>& InMaterialIDMaskInfo, int32& ActiveColorsCount, int InTargetId);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _typedef_ `typedef TArray<TArray<TArray<class HSVBucket*>>> Bucket3dArray;`
- L15 _typedef_ `typedef TArray<TArray<TArray<int32>>> Color3dArray;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.h` (Other)


#### class `FSH_EdgeDetect`  
`class FSH_EdgeDetect : public FSH_Base`  
_L18-33_
- inherits: `FSH_Base`
- L22 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_EdgeDetect, FSH_Base);`

#### enum `EWarp::Type`  
`enum Type : int`  
_L38-43_
- L40 _public enumerator_ `Directional = 0 UMETA(DisplayName = "Directional")`
- L41 _public enumerator_ `Normal = 1 UMETA(DisplayName = "Normal")`
- L42 _public enumerator_ `Sine = 2 UMETA(DisplayName = "Sine")`

#### class `FSH_DirectionalWarp`  
`class FSH_DirectionalWarp : public FSH_Base`  
_L49-66_
- inherits: `FSH_Base`
- L53 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_DirectionalWarp, FSH_Base);`

#### class `FSH_NormalWarp`  
`class FSH_NormalWarp : public FSH_Base`  
_L71-87_
- inherits: `FSH_Base`
- L75 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NormalWarp, FSH_Base);`

#### class `FSH_SineWarp`  
`class FSH_SineWarp : public FSH_Base`  
_L92-110_
- inherits: `FSH_Base`
- L96 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_SineWarp, FSH_Base);`

#### class `FSH_ErodeDilate`  
`class FSH_ErodeDilate : public FSH_Base`  
_L118-134_
- inherits: `FSH_Base`
- L122 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ErodeDilate, FSH_Base);`
- L130 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_ErodeDilate_Type, FVar_ErodeDilate_Kernel, FVar_ErodeDilate_IsSingleChannel>;`

#### class `T_Filter`  
`class T_Filter`  
_L138-148_
- L144 _public prototype_ `static TiledBlobPtr CreateEdgeDetect(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, float Thickness, int32 InTargetId);`
- L145 _public prototype_ `static TiledBlobPtr CreateDirectionalWarp(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, TiledBlobPtr Mask, float Intensity, float AngleRad, int32 InTargetId);`
- L146 _public prototype_ `static TiledBlobPtr CreateNormalWarp(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, TiledBlobPtr Mask, float Intensity, int32 InTargetId);`
- L147 _public prototype_ `static TiledBlobPtr CreateSineWarp(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredDesc, TiledBlobPtr SourceTexture, TiledBlobPtr Mask, float Intensity, float PhaseU, float PhaseV, int32 InTargetId);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L36 _namespace_ `namespace EWarp`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_FlatColorTexture.h` (Other)


#### class `FSH_FlatColorTexture`  
`class FSH_FlatColorTexture : public FSH_Base`  
_L15-26_
- inherits: `FSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_FlatColorTexture, FSH_Base);`

#### class `T_FlatColorTexture`  
`class T_FlatColorTexture`  
_L33-41_
- L39 _public prototype_ `static BufferDescriptor GetFlatColorDesc(FString name, BufferFormat InBufferFormat = BufferFormat::Byte);`
- L40 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr InCycle, BufferDescriptor DesiredOutputDesc, FLinearColor Color, int InTargetId);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L28 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_FlatColorTexture> Fx_FlatColorTexture;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Invert.h` (Other)


#### class `FSH_Invert`  
`class FSH_Invert : public FSH_Base`  
_L15-37_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Invert, FSH_Base);`
- L29 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FInvertIncludeAlpha, FInvertClamp>;`
- L32 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L36 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Invert`  
`class T_Invert`  
_L39-46_
- L45 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, float MaxValue, int32 TargetId, bool bIncludeAlpha, bool bClamp);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Levels.h` (Other)


#### class `FSH_Levels`  
`class FSH_Levels : public FSH_Base`  
_L16-45_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_Levels, FSH_Base);`
- L38 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FConvertToGrayscale, FIsAutoLevels>;`
- L40 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L44 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### struct `FLevelsHistogramData`  
`struct FLevelsHistogramData`  
_L48-51_
- L50 _public member_ `TArray<FVector4f> HistogramData;`

#### struct `FLevels`  
`struct FLevels`  
_L54-96_
- L58 _public member_ `float Low = 0;` — The Low value of the Levels adjustment, any pixel under that value is set to black. Default is 0.
- L62 _public member_ `float Mid = 0.5f;` — The mid value of the Levels adjustment, must be in the range [Min, Max] and the Default is 0.5. The mid value determine where the smoothing curve applying the midpoint filter is crossing 0.5.
- L65 _public member_ `float High = 1;` — The High value of the Levels adjustment, any pixel above that value is set to white. Default is 1.
- L67 _public member_ `bool IsAutoLevels = false;`
- L68 _public member_ `float MidPercentage = 0.5f;`
- L71 _public member_ `float OutLow = 0;` — The black point of the output. Moving this will remap the dark point to this value. Default is 0
- L74 _public member_ `float OutHigh = 1;` — The white point of the output. Moving this will remap the white point to this value. Default is 1
- L76 _public prototype_ `bool SetLow(float InValue);`
- L77 _public prototype_ `bool SetMid(float InValue);`
- L78 _public prototype_ `bool SetHigh(float InValue);`
- L81 _public prototype_ `float EvalRange(float Val) const;` — Eval Low-High range mapping on value
- L83 _public prototype_ `float EvalRangeInv(float Val) const;` — Eval reverse Low-High range mapping on value
- L86 _public prototype_ `float EvalMidExponent() const;` — Evaluate the MidExponent of the power curve applying the midpoint filter
- L87 _public prototype_ `bool SetMidFromMidExponent(float InExponent);`
- L90 _public prototype_ `void InitFromLowMidHigh(float LowValue, float MidValue, float HighValue, float OutLow, float OutHigh);` — various init from different parameter set
- L91 _public prototype_ `void InitFromAutoLevels(float MidPercentage);`
- L92 _public prototype_ `void InitFromHistogramScan(float InPosition, float InContrast);`
- L93 _public prototype_ `void InitFromHistogramRange(float InPosition, float InRange);`
- L95 _public member_ `FLevelsHistogramData HistogramData;`

#### class `T_Levels`  
`class T_Levels`  
_L100-104_
- L103 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, const FLevelsPtr& Levels, int32 TargetId);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L98 _typedef_ `using FLevelsPtr = TSharedPtr< FLevels>;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_MaterialIDMask.h` (Other)


#### class `FSH_MaterialIDMask`  
`class FSH_MaterialIDMask : public FSH_Base`  
_L19-43_
- inherits: `FSH_Base`
- L24 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MaterialIDMask, FSH_Base);`
- L27 _public function_ `SHADER_PARAMETER_TEXTURE(Texture2D, MaterialIDTexture) SHADER_PARAMETER_ARRAY(FVector4f, Buckets, [HSVBucket::HBuckets * HSVBucket::SBuckets * HSVBucket::VBuckets]) SHADER_PARAMETER_ARRAY(FVector4f, ActiveColors, [128]) SHADER_PARAMETER(int, ActiveColorsCount) SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L39 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParams, FShaderCompilerEnvironment& InEnv)`

#### class `T_MaterialIDMask`  
`class T_MaterialIDMask`  
_L48-59_
- L51 _public prototype_ `T_MaterialIDMask();`
- L52 _public prototype_ `~T_MaterialIDMask();`
- L58 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr InCycle, TiledBlobPtr InMaterialIDTexture, const TArray<FLinearColor>& InActiveColors, const int32& ActiveColorsCount, BufferDescriptor DesiredDesc, int InTargetId);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.h` (Other)


#### class `FSH_MathsOp_OneInput`  
`class FSH_MathsOp_OneInput : public FSH_Base`  
_L17-29_
- inherits: `FSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MathsOp_OneInput, FSH_Base);`
- L23 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Input) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### enum `ETrigFunction`  
`enum class ETrigFunction : uint8`  
_L59-67_
- reflection: `UENUM(BlueprintType)`
- L61 _public enumerator_ `Sin UMETA(DisplayName = "Sine")`
- L62 _public enumerator_ `Cos UMETA(DisplayName = "Cosine")`
- L63 _public enumerator_ `Tan UMETA(DisplayName = "Tangent")`
- L64 _public enumerator_ `ASin UMETA(DisplayName = "ArcSine")`
- L65 _public enumerator_ `ACos UMETA(DisplayName = "ArcCosine")`
- L66 _public enumerator_ `ATan UMETA(DisplayName = "ArcTangent")`

#### class `T_Maths_OneInput`  
`class T_Maths_OneInput`  
_L72-93_
- L78 _public prototype_ `static TiledBlobPtr CreateTrigonometry(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input, ETrigFunction Function);`
- L79 _public prototype_ `static TiledBlobPtr CreateToRadians(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L80 _public prototype_ `static TiledBlobPtr CreateToDegrees(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L81 _public prototype_ `static TiledBlobPtr CreateAbs(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L82 _public prototype_ `static TiledBlobPtr CreateSqrt(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L83 _public prototype_ `static TiledBlobPtr CreateSquare(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L84 _public prototype_ `static TiledBlobPtr CreateCbrt(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L85 _public prototype_ `static TiledBlobPtr CreateCube(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L86 _public prototype_ `static TiledBlobPtr CreateExp(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L87 _public prototype_ `static TiledBlobPtr CreateLog2(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L88 _public prototype_ `static TiledBlobPtr CreateLog10(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L89 _public prototype_ `static TiledBlobPtr CreateLog(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L90 _public prototype_ `static TiledBlobPtr CreateFloor(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L91 _public prototype_ `static TiledBlobPtr CreateCeil(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`
- L92 _public prototype_ `static TiledBlobPtr CreateRound(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Input);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L31 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Sin, FSH_MathsOp_OneInput);`
- L32 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Cos, FSH_MathsOp_OneInput);`
- L33 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Tan, FSH_MathsOp_OneInput);`
- L34 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_ASin, FSH_MathsOp_OneInput);`
- L35 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_ACos, FSH_MathsOp_OneInput);`
- L36 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_ATan, FSH_MathsOp_OneInput);`
- L38 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_ToRadians, FSH_MathsOp_OneInput);`
- L39 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_ToDegrees, FSH_MathsOp_OneInput);`
- L41 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Abs, FSH_MathsOp_OneInput);`
- L42 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Sqrt, FSH_MathsOp_OneInput);`
- L43 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Square, FSH_MathsOp_OneInput);`
- L44 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Cube, FSH_MathsOp_OneInput);`
- L45 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Cbrt, FSH_MathsOp_OneInput);`
- L46 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Exp, FSH_MathsOp_OneInput);`
- L47 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Log2, FSH_MathsOp_OneInput);`
- L48 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Log10, FSH_MathsOp_OneInput);`
- L49 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Log, FSH_MathsOp_OneInput);`
- L50 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Floor, FSH_MathsOp_OneInput);`
- L51 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Ceil, FSH_MathsOp_OneInput);`
- L52 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Round, FSH_MathsOp_OneInput);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_ThreeInputs.h` (Other)


#### class `FSH_ThreeInputs`  
`class FSH_ThreeInputs : public FSH_Base`  
_L17-31_
- inherits: `FSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ThreeInputs, FSH_Base);`
- L23 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Operand1) SHADER_PARAMETER_TEXTURE(Texture2D, Operand2) SHADER_PARAMETER_TEXTURE(Texture2D, Operand3) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### class `T_Maths_ThreeInputs`  
`class T_Maths_ThreeInputs`  
_L39-47_
- L45 _public prototype_ `static TiledBlobPtr CreateMad(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2, TiledBlobPtr Operand3);`
- L46 _public prototype_ `static TiledBlobPtr CreateLerp(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2, TiledBlobPtr Operand3);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L33 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Mad, FSH_ThreeInputs);`
- L34 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Lerp, FSH_ThreeInputs);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.h` (Other)


#### class `FSH_BasicMathOp`  
`class FSH_BasicMathOp : public FSH_Base`  
_L17-30_
- inherits: `FSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BasicMathOp, FSH_Base);`
- L23 _public prototype_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, Operand1) SHADER_PARAMETER_TEXTURE(Texture2D, Operand2) END_SHADER_PARAMETER_STRUCT() TEXTURE_ENGINE_DEFAULT_PERMUTATION;`

#### enum `EIfThenElseOperator`  
`enum EIfThenElseOperator : int`  
_L46-54_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `GT UMETA(DisplayName = "Greater Than")`
- L49 _public enumerator_ `GTE UMETA(DisplayName = "Greater Than Or Equal To")`
- L50 _public enumerator_ `LT UMETA(DisplayName = "Less Than")`
- L51 _public enumerator_ `LTE UMETA(DisplayName = "Less Than Or Equal To")`
- L52 _public enumerator_ `EQ UMETA(DisplayName = "Equal To (Tolerance = 0.00001)")`
- L53 _public enumerator_ `NEQ UMETA(DisplayName = "Not Equal To (Tolerance = 0.00001)")`

#### enum `EIfThenElseType`  
`enum EIfThenElseType : int`  
_L57-62_
- reflection: `UENUM(BlueprintType)`
- L59 _public enumerator_ `IndividualComponent UMETA(DisplayName = "Individual Components")`
- L60 _public enumerator_ `AllComponents UMETA(DisplayName = "All Components")`
- L61 _public enumerator_ `Grayscale UMETA(DisplayName = "Grayscale")`

#### class `FSH_IfThenElse`  
`class FSH_IfThenElse : public FSH_Base`  
_L64-83_
- inherits: `FSH_Base`
- L67 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_IfThenElse, FSH_Base);`
- L71 _public function_ `SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, LHS) SHADER_PARAMETER_TEXTURE(Texture2D, RHS) SHADER_PARAMETER_TEXTURE(Texture2D, Then) SHADER_PARAMETER_TEXTURE(Texture2D, Else) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L82 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Maths_TwoInputs`  
`class T_Maths_TwoInputs`  
_L112-129_
- L118 _public prototype_ `static TiledBlobPtr CreateMultiply(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L119 _public prototype_ `static TiledBlobPtr CreateDivide(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L120 _public prototype_ `static TiledBlobPtr CreateAdd(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L121 _public prototype_ `static TiledBlobPtr CreateSubtract(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L122 _public prototype_ `static TiledBlobPtr CreateDot(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L123 _public prototype_ `static TiledBlobPtr CreateCross(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L124 _public prototype_ `static TiledBlobPtr CreatePow(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L125 _public prototype_ `static TiledBlobPtr CreateStep(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr Operand1, TiledBlobPtr Operand2);`
- L127 _public prototype_ `static TiledBlobPtr CreateIfThenElse(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr LHS, TiledBlobPtr RHS, TiledBlobPtr Then, TiledBlobPtr Else, EIfThenElseOperator Operator, EIfThenElseType Type);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L32 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Multiply, FSH_BasicMathOp);`
- L33 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Divide, FSH_BasicMathOp);`
- L34 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Add, FSH_BasicMathOp);`
- L35 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Subtract, FSH_BasicMathOp);`
- L37 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Dot, FSH_BasicMathOp);`
- L38 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Cross, FSH_BasicMathOp);`
- L39 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Pow, FSH_BasicMathOp);`
- L40 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_Step, FSH_BasicMathOp);`
- L85 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GT_Component, FSH_IfThenElse);`
- L86 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GT_All, FSH_IfThenElse);`
- L87 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GT_Grayscale, FSH_IfThenElse);`
- L89 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GTE_Component, FSH_IfThenElse);`
- L90 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GTE_All, FSH_IfThenElse);`
- L91 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_GTE_Grayscale, FSH_IfThenElse);`
- L93 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LT_Component, FSH_IfThenElse);`
- L94 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LT_All, FSH_IfThenElse);`
- L95 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LT_Grayscale, FSH_IfThenElse);`
- L97 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LTE_Component, FSH_IfThenElse);`
- L98 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LTE_All, FSH_IfThenElse);`
- L99 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_LTE_Grayscale, FSH_IfThenElse);`
- L101 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_EQ_Component, FSH_IfThenElse);`
- L102 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_EQ_All, FSH_IfThenElse);`
- L103 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_EQ_Grayscale, FSH_IfThenElse);`
- L105 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_NEQ_Component, FSH_IfThenElse);`
- L106 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_NEQ_All, FSH_IfThenElse);`
- L107 _prototype_ `DECLARE_EMPTY_GLOBAL_SHADER_DERIVED_FROM(FSH_IfThenElse_NEQ_Grayscale, FSH_IfThenElse);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Transform.h` (Other)


#### class `FSH_TransformBlit`  
`class FSH_TransformBlit : public FSH_Base`  
_L17-57_
- inherits: `FSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_TransformBlit, FSH_Base);`
- L24 _public function_ `SHADER_PARAMETER_STRUCT(FTileInfo, TileInfo) SHADER_PARAMETER_STRUCT(FStandardSamplerStates, SamplerStates) SHADER_PARAMETER_TEXTURE(Texture2D, SourceTexture) SHADER_PARAMETER(FLinearColor, FillColor) SHADER_PARAMETER(float, CoverageX) SHADER_PARAMETER(float, CoverageY) SHADER_PARAMETER(float, TranslationX) SHADER_PARAMETER(float, TranslationY) SHADER_PARAMETER(float, PivotX) SHADER_PARAMETER(float, PivotY) SHADER_PARAMETER(float, RotationX) SHADER_PARAMETER(float, RotationY) SHADER_PARAMETER(float, ScaleX) SHADER_PARAMETER(float, ScaleY) SHADER_PARAMETER(float, StaggerX) SHADER_PARAMETER(float, StaggerY) SHADER_PARAMETER(float, StrideX) SHADER_PARAMETER(float, StrideY) SHADER_PARAMETER(float, Zoom) SHADER_PARAMETER(float, StretchToFit) SHADER_PARAMETER(float, SpacingX) SHADER_PARAMETER(float, SpacingY) SHADER_PARAMETER(float, FilterMode) SHADER_PARAMETER(float, MirrorX) SHADER_PARAMETER(float, MirrorY) SHADER_PARAMETER(float, BlendDebugGrid) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L56 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Transform`  
`class T_Transform`  
_L60-100_
- L94 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, TiledBlobPtr Source, const TransformParameter& TransformParam, const CellParameter& CellParam, const ColorParameter& ColorParam, int32 TargetId = 0);`

#### struct `T_Transform::TransformParameter`  
`struct TransformParameter`  
_L67-74_
- L69 _public member_ `FVector2f Coverage = { 1.f, 1.f };` — Coverage of the whole domain
- L70 _public member_ `FVector2f Translation = { 0.f, 0.f };` — Translation of the whole domain
- L71 _public member_ `FVector2f Pivot = { 0.5f, 0.5f };` — Pivot coord of the rotation and scaling
- L72 _public member_ `float RotationXY = 0;` — Rotation angle in Radians centered on the pivot coord
- L73 _public member_ `FVector2f Scale = { 1.f, 1.f };` — Scaling aka the Repeatition of the motif

#### struct `T_Transform::CellParameter`  
`struct CellParameter`  
_L76-83_
- L78 _public member_ `float Zoom = 1.0f;`
- L79 _public member_ `float StretchToFit = 0.f;`
- L80 _public member_ `FVector2f Spacing = { 0.f, 0.f };`
- L81 _public member_ `FVector2f Stagger = { 0.f, 0.f };`
- L82 _public member_ `FVector2f Stride = { 0.f, 0.f };`

#### struct `T_Transform::ColorParameter`  
`struct ColorParameter`  
_L85-92_
- L87 _public member_ `FLinearColor FillColor = { 0,0,0, 1 };`
- L88 _public member_ `bool WrapFilterMode = true;`
- L89 _public member_ `bool MirrorX = false;`
- L90 _public member_ `bool MirrorY = false;`
- L91 _public member_ `float ShowDebugGrid = 0.0f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_AdjustColor.h` (Other)


#### class `FSH_AdjustColor`  
`class FSH_AdjustColor : public FSH_Base`  
_L20-50_
- inherits: `FSH_Base`
- L25 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_AdjustColor, FSH_Base);`
- L37 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_ClearColor, FVar_ShiftAlpha, FVar_Invert>;` — Permutation domain local
- L41 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L46 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_AdjustColor`  
`class T_AdjustColor`  
_L54-63_
- L57 _public prototype_ `T_AdjustColor();`
- L58 _public prototype_ `virtual ~T_AdjustColor();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L11 _typedef_ `typedef std::shared_ptr<MixUpdateCycle> MixUpdateCyclePtr;`
- L13 _namespace_ `namespace (anonymous)`
- L52 _prototype_ `template <> void SetupDefaultParameters(FSH_AdjustColor::FParameters& params);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_AdjustFrequency.h` (Other)


#### class `FSH_AdjustFrequency`  
`class FSH_AdjustFrequency : public FSH_Base`  
_L13-42_
- inherits: `FSH_Base`
- L17 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_AdjustFrequency, FSH_Base);`
- L31 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L35 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L40 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FSH_AdjustFrequencyNormals`  
`class FSH_AdjustFrequencyNormals : public FSH_Base`  
_L50-81_
- inherits: `FSH_Base`
- L54 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_AdjustFrequencyNormals, FSH_Base);`
- L66 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_Renormalize>;` — Permutation domain local
- L70 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L74 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L79 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_AdjustFrequency`  
`class T_AdjustFrequency`  
_L90-99_
- L93 _public prototype_ `T_AdjustFrequency();`
- L94 _public prototype_ `virtual ~T_AdjustFrequency();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L43 _prototype_ `template <> void SetupDefaultParameters(FSH_AdjustFrequency::FParameters& params);`
- L46 _namespace_ `namespace (anonymous)`
- L82 _prototype_ `template <> void SetupDefaultParameters(FSH_AdjustFrequencyNormals::FParameters& params);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_BlendWithHeightMask.h` (Other)


#### class `FSH_NormalBlendWithHeightMask`  
`class FSH_NormalBlendWithHeightMask : public FSH_Base`  
_L17-43_
- inherits: `FSH_Base`
- L21 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NormalBlendWithHeightMask, FSH_Base);`
- L35 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L40 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_BlendWithHeightMask`  
`class T_BlendWithHeightMask`  
_L49-55_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L15 _namespace_ `namespace (anonymous)`
- L44 _prototype_ `template <> void SetupDefaultParameters(FSH_NormalBlendWithHeightMask::FParameters& params);`
- L46 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_NormalBlendWithHeightMask> Fx_NormalBlendWithHeightMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Displacement.h` (Other)


#### class `FSH_LayerDisplacement`  
`class FSH_LayerDisplacement : public FSH_Base`  
_L14-47_
- inherits: `FSH_Base`
- L18 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_LayerDisplacement, FSH_Base);`
- L38 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L43 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Displacement`  
`class T_Displacement`  
_L53-62_
- L56 _public prototype_ `T_Displacement();`
- L57 _public prototype_ `virtual ~T_Displacement();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L48 _prototype_ `template <> void SetupDefaultParameters(FSH_LayerDisplacement::FParameters& params);`
- L50 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_LayerDisplacement> Fx_LayerDisplacement;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Dynamic.h` (Other)


#### class `T_Dynamic`  
`class T_Dynamic`  
_L11-18_

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_LayerMask.h` (Other)


#### class `FSH_LayerMask`  
`class FSH_LayerMask : public FSH_Base`  
_L32-83_
- inherits: `FSH_Base`
- desc: Then define the shader class
- L36 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_LayerMask, FSH_Base);`
- L65 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_HeightMask, FVar_FromAbove, FVar_Details, FVar_MaterialId, FVar_PaintMask, FVar_UVMask, FVar_MaskStack, FVar_Opacity>;` — Permutation domain local
- L69 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L74 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L79 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_LayerMask`  
`class T_LayerMask`  
_L91-100_
- L94 _public prototype_ `T_LayerMask();`
- L95 _public prototype_ `virtual ~T_LayerMask();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L18 _namespace_ `namespace (anonymous)`
- L84 _prototype_ `template <> void SetupDefaultParameters(FSH_LayerMask::FParameters& params);`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Normal.h` (Other)


#### class `FSH_LayerNormal`  
`class FSH_LayerNormal : public FSH_Base`  
_L14-47_
- inherits: `FSH_Base`
- L18 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_LayerNormal, FSH_Base);`
- L38 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L43 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_Normal`  
`class T_Normal`  
_L53-62_
- L56 _public prototype_ `T_Normal();`
- L57 _public prototype_ `virtual ~T_Normal();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L48 _prototype_ `template <> void SetupDefaultParameters(FSH_LayerNormal::FParameters& params);`
- L50 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_LayerNormal> Fx_LayerNormal;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Thumbnail.h` (Other)


#### class `T_Thumbnail`  
`class T_Thumbnail`  
_L15-22_
- L21 _public prototype_ `static TiledBlobRef Bind(UMixInterface* Mix, UObject* Model, TiledBlobPtr InBlobToBind, int32 TargetId);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.h` (Other)


#### enum `EGradientType`  
`enum class EGradientType : uint8`  
_L15-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `GT_Linear_1 = 0 UMETA(DisplayName = "Simple Linear")`
- L18 _public enumerator_ `GT_Linear_2 = 1 UMETA(DisplayName = "Linear Centered")`
- L19 _public enumerator_ `GT_Radial = 2 UMETA(DisplayName = "Radial")`
- L20 _public enumerator_ `GT_Axial_1 = 3 UMETA(DisplayName = "Axial Linear")`
- L21 _public enumerator_ `GT_Axial_2 = 4 UMETA(DisplayName = "Axial Centered")`

#### enum `EGradientInterpolation`  
`enum class EGradientInterpolation : uint8`  
_L25-30_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `GTI_Linear = 0 UMETA(DisplayName = "Linear")`
- L28 _public enumerator_ `GTI_Exp = 1 UMETA(DisplayName = "Exponential")`

#### enum `EGradientRotation`  
`enum class EGradientRotation : uint8`  
_L33-39_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `GTR_0 = 0 UMETA(DisplayName = "0")`
- L36 _public enumerator_ `GTR_90 = 1 UMETA(DisplayName = "90")`
- L37 _public enumerator_ `GTR_180 = 2 UMETA(DisplayName = "180")`
- L38 _public enumerator_ `GTR_270 = 3 UMETA(DisplayName = "270")`

#### enum `EGradientRotationLimited`  
`enum class EGradientRotationLimited : uint8`  
_L42-46_
- reflection: `UENUM(BlueprintType)`
- L44 _public enumerator_ `GTRL_0 = 0 UMETA(DisplayName = "0")`
- L45 _public enumerator_ `GTRL_90 = 1 UMETA(DisplayName = "90")`

#### class `FSH_GradientLinear_1`  
`class FSH_GradientLinear_1 : public FSH_Base`  
_L56-69_
- inherits: `FSH_Base`
- L60 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientLinear_1, FSH_Base);`
- L65 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_GradientInterpolation, FVar_GradientRotation>;`

#### class `FSH_GradientLinear_2`  
`class FSH_GradientLinear_2 : public FSH_Base`  
_L72-85_
- inherits: `FSH_Base`
- L76 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientLinear_2, FSH_Base);`
- L81 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_GradientInterpolation, FVar_GradientRotation>;`

#### class `FSH_GradientRadial`  
`class FSH_GradientRadial : public FSH_Base`  
_L88-102_
- inherits: `FSH_Base`
- L92 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientRadial, FSH_Base);`
- L98 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_GradientInterpolation>;`

#### class `FSH_GradientAxial1`  
`class FSH_GradientAxial1: public FSH_Base`  
_L105-120_
- inherits: `FSH_Base`
- L109 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientAxial1, FSH_Base);`
- L116 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_GradientInterpolation>;`

#### class `FSH_GradientAxial2`  
`class FSH_GradientAxial2: public FSH_Base`  
_L123-138_
- inherits: `FSH_Base`
- L127 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientAxial2, FSH_Base);`
- L134 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_GradientInterpolation>;`

#### class `T_Gradient`  
`class T_Gradient`  
_L144-161_
- L147 _public member_ `static constexpr int DefaultSize = 1024;`
- L148 _public prototype_ `static BufferDescriptor InitOutputDesc(BufferDescriptor DesiredOutputDesc);`
- L160 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, const Params& InParams, int32 TargetId = 0);`

#### struct `T_Gradient::Params`  
`struct Params`  
_L150-158_
- L151 _public member_ `EGradientType Type = EGradientType::GT_Linear_1;`
- L152 _public member_ `EGradientInterpolation Interpolation = EGradientInterpolation::GTI_Linear;`
- L153 _public member_ `int32 Rotation = 0;`
- L154 _public member_ `FVector2f Center;`
- L155 _public member_ `float Radius;`
- L156 _public member_ `FVector2f Point1;`
- L157 _public member_ `FVector2f Point2;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L49 _namespace_ `namespace (anonymous)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_ImageMask.h` (Other)


#### class `FSH_ImageMask`  
`class FSH_ImageMask : public FSH_Base`  
_L15-45_
- inherits: `FSH_Base`
- L23 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ImageMask, FSH_Base);`
- L33 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_NORMALIZE, FVar_INVERT>;`
- L36 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L41 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_ImageMask`  
`class T_ImageMask`  
_L52-64_
- L58 _public prototype_ `T_ImageMask();`
- L59 _public prototype_ `virtual ~T_ImageMask();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L46 _prototype_ `template <> void SetupDefaultParameters(FSH_ImageMask::FParameters& params);`
- L48 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_ImageMask> Fx_ImageMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskBlend_Multiply.h` (Other)


#### class `FSH_MaskBlend_Multiply`  
`class FSH_MaskBlend_Multiply : public FSH_Base`  
_L15-40_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MaskBlend_Multiply, FSH_Base);`
- L31 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L36 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_MaskBlend_Multiply`  
`class T_MaskBlend_Multiply`  
_L47-55_
- L53 _public prototype_ `T_MaskBlend_Multiply();`
- L54 _public prototype_ `virtual ~T_MaskBlend_Multiply();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L41 _prototype_ `template <> void SetupDefaultParameters(FSH_MaskBlend_Multiply::FParameters& params);`
- L43 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_MaskBlend_Multiply> Fx_BlendMode_Multiply;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.h` (Other)


#### class `FSH_BrightnessMaskModifier`  
`class FSH_BrightnessMaskModifier : public FSH_Base`  
_L21-42_
- inherits: `FSH_Base`
- L25 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_BrightnessMaskModifier, FSH_Base);`
- L34 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L38 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_ClampMaskModifier`  
`class FSH_ClampMaskModifier : public FSH_Base`  
_L44-64_
- inherits: `FSH_Base`
- L48 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ClampMaskModifier, FSH_Base);`
- L56 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L60 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_InvertMaskModifier`  
`class FSH_InvertMaskModifier : public FSH_Base`  
_L66-85_
- inherits: `FSH_Base`
- L70 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_InvertMaskModifier, FSH_Base);`
- L77 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L81 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_NormalizeMaskModifier`  
`class FSH_NormalizeMaskModifier : public FSH_Base`  
_L87-106_
- inherits: `FSH_Base`
- L91 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NormalizeMaskModifier, FSH_Base);`
- L98 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L102 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_GradientRemapMaskModifier`  
`class FSH_GradientRemapMaskModifier : public FSH_Base`  
_L108-131_
- inherits: `FSH_Base`
- L112 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_GradientRemapMaskModifier, FSH_Base);`
- L123 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L127 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_PosterizeMaskModifier`  
`class FSH_PosterizeMaskModifier : public FSH_Base`  
_L133-153_
- inherits: `FSH_Base`
- L137 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_PosterizeMaskModifier, FSH_Base);`
- L145 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L149 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_MaskModifier`  
`class T_MaskModifier`  
_L160-169_
- L163 _public prototype_ `T_MaskModifier();`
- L164 _public prototype_ `~T_MaskModifier();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L17 _namespace_ `namespace (anonymous)`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_NoiseMask.h` (Other)


#### enum `NoiseType`  
`enum class NoiseType`  
_L14-22_
- reflection: `UENUM()`
- L16 _public enumerator_ `Simplex = 0 UMETA(DisplayName = "Simplex")`
- L17 _public enumerator_ `Perlin UMETA(DisplayName = "Perlin")`
- L18 _public enumerator_ `Worley1 UMETA(DisplayName = "Worley1")`
- L19 _public enumerator_ `Worley2 UMETA(DisplayName = "Worley2")`
- L20 _public enumerator_ `Worley3 UMETA(DisplayName = "Worley3")`
- L21 _public enumerator_ `Count UMETA(DisplayName = "For fallback purpose")`

#### class `FSH_NoiseMask`  
`class FSH_NoiseMask : public FSH_Base`  
_L33-64_
- inherits: `FSH_Base`
- L37 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NoiseMask, FSH_Base);`
- L51 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_NoiseType>;` — Permutation domain local
- L55 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L60 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_NoiseMask`  
`class T_NoiseMask`  
_L73-82_
- L76 _public prototype_ `T_NoiseMask();`
- L77 _public prototype_ `~T_NoiseMask();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L28 _namespace_ `namespace (anonymous)`
- L66 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_NoiseMask> Fx_NoiseMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_NormalMask.h` (Other)


#### class `FSH_NormalMask`  
`class FSH_NormalMask : public FSH_Base`  
_L20-52_
- inherits: `FSH_Base`
- L24 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_NormalMask, FSH_Base);`
- L40 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_ThreeDimensions>;` — Permutation domain local
- L43 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L48 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_NormalMask`  
`class T_NormalMask`  
_L62-71_
- L65 _public prototype_ `T_NormalMask();`
- L66 _public prototype_ `~T_NormalMask();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L13 _namespace_ `namespace (anonymous)`
- L53 _prototype_ `template <> void SetupDefaultParameters(FSH_NormalMask::FParameters& params);`
- L55 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_NormalMask> Fx_NormalMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_PatternMask.h` (Other)


#### enum `PatternType`  
`enum class PatternType`  
_L15-22_
- reflection: `UENUM()`
- L17 _public enumerator_ `Square = 0 UMETA(DisplayName = "Square")`
- L18 _public enumerator_ `Circle UMETA(DisplayName = "Circle")`
- L19 _public enumerator_ `Checker UMETA(DisplayName = "Checker")`
- L20 _public enumerator_ `Gradient UMETA(DisplayName = "Gradient")`
- L21 _public enumerator_ `Count UMETA(DisplayName = "For fallback purpose")`

#### class `FSH_PatternMask`  
`class FSH_PatternMask : public FSH_Base`  
_L34-79_
- inherits: `FSH_Base`
- L38 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_PatternMask, FSH_Base);`
- L66 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_PatternType>;` — Permutation domain local
- L70 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L75 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_PatternMask`  
`class T_PatternMask`  
_L88-97_
- L91 _public prototype_ `T_PatternMask();`
- L92 _public prototype_ `~T_PatternMask();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L29 _namespace_ `namespace (anonymous)`
- L81 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_PatternMask> Fx_PatternMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_PositionGradientMask.h` (Other)


#### class `FSH_PositionGradientMask`  
`class FSH_PositionGradientMask : public FSH_Base`  
_L20-52_
- inherits: `FSH_Base`
- L24 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_PositionGradientMask, FSH_Base);`
- L40 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<PositionGradientMask::FVar_ThreeDimensions>;` — Permutation domain local
- L43 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L48 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FSH_CombineDisplacementAndWorldPos`  
`class FSH_CombineDisplacementAndWorldPos : public FSH_Base`  
_L60-82_
- inherits: `FSH_Base`
- L64 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_CombineDisplacementAndWorldPos, FSH_Base);`
- L78 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_PositionGradientMask`  
`class T_PositionGradientMask`  
_L92-101_
- L95 _public prototype_ `T_PositionGradientMask();`
- L96 _public prototype_ `~T_PositionGradientMask();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L12 _namespace_ `namespace PositionGradientMask`
- L53 _prototype_ `template <> void SetupDefaultParameters(FSH_PositionGradientMask::FParameters& params);`
- L55 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_PositionGradientMask> Fx_PositionGradientMask;`
- L83 _prototype_ `template <> void SetupDefaultParameters(FSH_CombineDisplacementAndWorldPos::FParameters& params);`
- L85 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_CombineDisplacementAndWorldPos> Fx_CombineDisplacementAndWorldPos;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_ShapeMask.h` (Other)


#### enum `EShapeMaskType`  
`enum class EShapeMaskType : uint8`  
_L15-52_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Circle = 0 UMETA(DisplayName = "Circle")`
- L18 _public enumerator_ `Segment UMETA(DisplayName = "Segment")`
- L19 _public enumerator_ `Rect UMETA(DisplayName = "Rect")`
- L20 _public enumerator_ `Triangle UMETA(DisplayName = "Triangle")`
- L21 _public enumerator_ `Ellipse UMETA(DisplayName = "Ellipse")`
- L22 _public enumerator_ `Pentagon UMETA(DisplayName = "Pentagon")`
- L23 _public enumerator_ `Hexagon UMETA(DisplayName = "Hexagon")`
- L24 _public enumerator_ `RegularPolygon_7 UMETA(DisplayName = " 7-gon")`
- L25 _public enumerator_ `RegularPolygon_8 UMETA(DisplayName = " 8-gon")`
- L26 _public enumerator_ `RegularPolygon_9 UMETA(DisplayName = " 9-gon")`
- L27 _public enumerator_ `RegularPolygon_10 UMETA(DisplayName = "10-gon")`
- L28 _public enumerator_ `RegularPolygon_11 UMETA(DisplayName = "11-gon")`
- L29 _public enumerator_ `RegularPolygon_12 UMETA(DisplayName = "12-gon")`
- L30 _public enumerator_ `RegularPolygon_13 UMETA(DisplayName = "13-gon")`
- L31 _public enumerator_ `RegularPolygon_14 UMETA(DisplayName = "14-gon")`
- L32 _public enumerator_ `RegularPolygon_15 UMETA(DisplayName = "15-gon")`
- L33 _public enumerator_ `RegularPolygon_16 UMETA(DisplayName = "16-gon")`
- L34 _public enumerator_ `RegularPolygon_17 UMETA(DisplayName = "17-gon")`
- L35 _public enumerator_ `RegularPolygon_18 UMETA(DisplayName = "18-gon")`
- L36 _public enumerator_ `RegularPolygon_19 UMETA(DisplayName = "19-gon")`
- L37 _public enumerator_ `RegularPolygon_20 UMETA(DisplayName = "20-gon")`
- L38 _public enumerator_ `RegularPolygon_21 UMETA(DisplayName = "21-gon")`
- L39 _public enumerator_ `RegularPolygon_22 UMETA(DisplayName = "22-gon")`
- L40 _public enumerator_ `RegularPolygon_23 UMETA(DisplayName = "23-gon")`
- L41 _public enumerator_ `RegularPolygon_24 UMETA(DisplayName = "24-gon")`
- L42 _public enumerator_ `RegularPolygon_25 UMETA(DisplayName = "25-gon")`
- L43 _public enumerator_ `RegularPolygon_26 UMETA(DisplayName = "26-gon")`
- L44 _public enumerator_ `RegularPolygon_27 UMETA(DisplayName = "27-gon")`
- L45 _public enumerator_ `RegularPolygon_28 UMETA(DisplayName = "28-gon")`
- L46 _public enumerator_ `RegularPolygon_29 UMETA(DisplayName = "29-gon")`
- L47 _public enumerator_ `RegularPolygon_30 UMETA(DisplayName = "30-gon")`
- L48 _public enumerator_ `RegularPolygon_31 UMETA(DisplayName = "31-gon")`
- L49 _public enumerator_ `RegularPolygon_32 UMETA(DisplayName = "32-gon")`
- L51 _public enumerator_ `Count UMETA(DisplayName = "For fallback purpose")`

#### class `FSH_ShapeMask`  
`class FSH_ShapeMask : public FSH_Base`  
_L64-96_
- inherits: `FSH_Base`
- L68 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_ShapeMask, FSH_Base);`
- L83 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FVar_ShapeType>;` — Permutation domain local
- L87 _public function_ `static FPermutationDomain RemapPermutation(FPermutationDomain PermutationVector)`
- L92 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `T_ShapeMask`  
`class T_ShapeMask`  
_L103-120_
- L106 _public member_ `static constexpr int DefaultSize = 1024;`
- L118 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, EShapeMaskType ShapeMaskType, const FParams& Params, int32 TargetId = 0);`

#### struct `T_ShapeMask::FParams`  
`struct FParams`  
_L108-116_
- L110 _public member_ `float Rotation = 0.f;`
- L111 _public member_ `FVector2f Size = { 1.0f, 1.0f };`
- L112 _public member_ `float Rounding = 0.0f;`
- L113 _public member_ `float BevelWidth = 0.0f;`
- L114 _public member_ `float BevelCurve = 0.0f;`
- L115 _public member_ `float BlendSDF = 0.0f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L59 _namespace_ `namespace (anonymous)`
- L98 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_ShapeMask> Fx_ShapeMask;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshDilateUVs.h` (Other)


#### class `FSH_DilateMeshTexture`  
`class FSH_DilateMeshTexture : public FSH_Base`  
_L15-38_
- inherits: `FSH_Base`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_DilateMeshTexture, FSH_Base);`
- L30 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L35 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_MeshDilateUVs`  
`class T_MeshDilateUVs`  
_L45-55_
- L48 _public prototype_ `T_MeshDilateUVs();`
- L49 _public prototype_ `virtual ~T_MeshDilateUVs();`
- L54 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr cycle, int32 targetId, TiledBlobPtr sourceTexture);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L39 _prototype_ `template <> void SetupDefaultParameters(FSH_DilateMeshTexture::FParameters& params);`
- L42 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_DilateMeshTexture> Fx_DilateMeshTexture;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.h` (Other)


#### class `VSH_MeshTexture`  
`class VSH_MeshTexture : public VSH_Base`  
_L16-30_
- inherits: `VSH_Base`
- L20 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(VSH_MeshTexture, VSH_Base);`
- L26 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `VSH_MeshTexture_WorldPos`  
`class VSH_MeshTexture_WorldPos : public VSH_Base`  
_L33-49_
- inherits: `VSH_Base`
- L37 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(VSH_MeshTexture_WorldPos, VSH_Base);`
- L45 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FSH_MeshTexture_WorldPos`  
`class FSH_MeshTexture_WorldPos : public FSH_Base`  
_L52-70_
- inherits: `FSH_Base`
- L56 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MeshTexture_WorldPos, FSH_Base);`
- L62 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L67 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_MeshTexture_WorldNormals`  
`class FSH_MeshTexture_WorldNormals : public FSH_Base`  
_L73-91_
- inherits: `FSH_Base`
- L77 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MeshTexture_WorldNormals, FSH_Base);`
- L83 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L88 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_MeshTexture_WorldTangents`  
`class FSH_MeshTexture_WorldTangents : public FSH_Base`  
_L94-112_
- inherits: `FSH_Base`
- L98 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MeshTexture_WorldTangents, FSH_Base);`
- L104 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L109 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `FSH_MeshTexture_WorldUVMask`  
`class FSH_MeshTexture_WorldUVMask : public FSH_Base`  
_L115-133_
- inherits: `FSH_Base`
- L119 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MeshTexture_WorldUVMask, FSH_Base);`
- L125 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L130 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& params, FShaderCompilerEnvironment& env)`

#### class `T_MeshEncodedAsTexture`  
`class T_MeshEncodedAsTexture`  
_L136-150_
- L139 _public member_ `static int32 s_minMeshmapRes;` — We need to create mesh maps in 4k. Otherwise we get artifacts when using in curvature and painting.
- L140 _public prototype_ `T_MeshEncodedAsTexture();`
- L141 _public prototype_ `virtual ~T_MeshEncodedAsTexture();`
- L146 _public prototype_ `static TiledBlobPtr Create_WorldPos(MixUpdateCyclePtr cycle, int32 targetId);`
- L147 _public prototype_ `static TiledBlobPtr Create_WorldNormals(MixUpdateCyclePtr cycle, int32 targetId);`
- L148 _public prototype_ `static TiledBlobPtr Create_WorldTangents(MixUpdateCyclePtr cycle, int32 targetId);`
- L149 _public prototype_ `static TiledBlobPtr Create_WorldUVMask(MixUpdateCyclePtr cycle, int32 targetId);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mix/T_InvalidateTiles.h` (Other)


#### class `T_InvalidateTiles`  
`class T_InvalidateTiles : public BlobTransform`  
_L11-27_
- inherits: `BlobTransform`
- L14 _public prototype_ `T_InvalidateTiles();`
- L17 _public prototype_ `virtual Device* TargetDevice(size_t index) const override;`
- L18 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& args) override;`
- L20 _public function_ `virtual bool GeneratesData() const override`
- L25 _public prototype_ `static JobUPtr CreateJob(MixUpdateCyclePtr cycle, int32 targetId);`
- L26 _public prototype_ `static void Create(MixUpdateCyclePtr cycle, int32 targetId);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mix/T_UpdateTargets.h` (Other)


#### class `T_UpdateTargets`  
`class T_UpdateTargets : public BlobTransform`  
_L11-30_
- inherits: `BlobTransform`
- L14 _private member_ `bool _shouldUpdate = false;` — This will ensure default texture is used when there is no child in layer set
- L15 _private member_ `static int _gpuTesselationFactor;`
- L17 _public prototype_ `T_UpdateTargets();`
- L19 _public prototype_ `virtual Device* TargetDevice(size_t index) const override;`
- L20 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& args) override;`
- L22 _public function_ `virtual bool GeneratesData() const override`
- L23 _public function_ `virtual void SetShouldUpdate(bool shouldUpdate)`
- L27 _public function_ `static void SetGPUTesselationFactor(int tesselationFactor)`
- L28 _public prototype_ `static JobUPtr CreateJob(MixUpdateCyclePtr cycle, int32 targetId, bool shouldUpdate);`
- L29 _public prototype_ `static void Create(MixUpdateCyclePtr cycle, int32 targetId, bool shouldUpdate);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_CombineTiledBlob.h` (Other)


#### struct `CombineSettings`  
`struct CombineSettings`  
_L22-27_
- L24 _public member_ `bool bFixed = false;`
- L25 _public member_ `bool bMaintainAspectRatio = false;`
- L26 _public member_ `FLinearColor BackgroundColor = FLinearColor::Transparent;`

#### class `CombineTiledBlob_Transform`  
`class CombineTiledBlob_Transform : public BlobTransform`  
_L32-53_
- inherits: `BlobTransform`
- desc: A dedicated BlobTransform creating a Combined version of a TiledBlob
- L35 _private member_ `TiledBlobPtr Source;` — The source blob that we are combining
- L36 _private member_ `CombineSettings Settings;` — Combine settings
- L37 _private member_ `DrawTilesSettings DrawSettings;` — FX device specific draw settings
- L39 _private prototype_ `void InitDrawSettings(BlobPtr Target, T_Tiles<DeviceBufferRef>& Tiles);`
- L40 _private prototype_ `void InitDrawSettingsWithoutAspectRatio(BlobPtr Target, T_Tiles<DeviceBufferRef>& Tiles);`
- L41 _private prototype_ `void InitDrawSettingsWithAspectRatio(BlobPtr Target, T_Tiles<DeviceBufferRef>& Tiles);`
- L44 _public prototype_ `CombineTiledBlob_Transform(FString InName, TiledBlobPtr InSource, const CombineSettings* InSettings = nullptr);`
- L45 _public prototype_ `virtual AsyncBufferResultPtr Bind(BlobPtr Value, const ResourceBindInfo& BindInfo) override;`
- L46 _public prototype_ `virtual AsyncBufferResultPtr Unbind(BlobPtr BlobObj, const ResourceBindInfo& BindInfo) override;`
- L47 _public prototype_ `virtual Device* TargetDevice(size_t DevIndex) const override;`
- L48 _public prototype_ `virtual std::shared_ptr<BlobTransform> DuplicateInstance(FString NewName) override;`
- L49 _public prototype_ `virtual bool GeneratesData() const override;`
- L50 _public prototype_ `virtual bool CanHandleTiles() const override;`
- L52 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& Args) override;`

#### class `T_CombineTiledBlob`  
`class T_CombineTiledBlob`  
_L58-68_
- desc: Tiles To Combined Transform
- L66 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, BufferDescriptor DesiredOutputDesc, int32 TargetId, TiledBlobPtr SourceTex, JobUPtr JobToUse = nullptr, const CombineSettings* InSettings = nullptr);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_FinaliseBlob.h` (Other)


#### class `T_FinaliseBlob`  
`class T_FinaliseBlob`  
_L11-18_
- L17 _public prototype_ `static JobPtr Create(MixUpdateCyclePtr Cycle, JobPtr JobObj);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_LoadStaticResource.h` (Other)


#### class `Job_LoadStaticImageResource`  
`class Job_LoadStaticImageResource : public Job, public FGCObject`  
_L12-39_
- inherits: `Job,FGCObject`
- L14 _private member_ `TObjectPtr<UStaticImageResource> Source;` — The source for the static image resource
- L17 _public prototype_ `Job_LoadStaticImageResource(UMixInterface* InMix, UStaticImageResource* InSource, int32 TargetId, UObject* InErrorOwner = nullptr, uint16 Priority = (uint16)E_Priority::kHigh);`
- L18 _public prototype_ `virtual ~Job_LoadStaticImageResource() override = default;`
- L23 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L24 _public prototype_ `virtual FString GetReferencerName() const override;`
- L27 _protected function_ `virtual void GetDependencies(JobPtrVec& prior, JobPtrVec& after, JobRunInfo runInfo) override`
- L28 _protected function_ `virtual AsyncPrepareResult PrepareTargets(JobBatch* batch) override`
- L29 _protected function_ `virtual AsyncPrepareResult PrepareResources(JobBatch* batch) override`
- L31 _protected function_ `virtual int32 Exec() override`
- L32 _protected function_ `virtual cti::continuable<int32> BindArgs_All(JobRunInfo runInfo) override`
- L33 _protected function_ `virtual cti::continuable<int32> UnbindArgs_All(JobRunInfo runInfo) override`
- L34 _protected function_ `virtual bool CanHandleTiles() const override`
- L36 _protected prototype_ `virtual cti::continuable<int32> PreExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type returnThread) override;`
- L37 _protected prototype_ `virtual cti::continuable<int32> ExecAsync(ENamedThreads::Type execThread, ENamedThreads::Type returnThread) override;`
- L38 _protected function_ `virtual bool IsAsync() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_MinMax.h` (Other)


#### class `FSH_MinMaxDownsample`  
`class FSH_MinMaxDownsample : public FSH_Base`  
_L24-50_
- inherits: `FSH_Base`
- L28 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSH_MinMaxDownsample, FSH_Base);`
- L38 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<MinMax::FVar_UVMask, MinMax::FVar_FirstPass>;` — Permutation domain local
- L41 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L46 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `CSH_MinMaxDownsample`  
`class CSH_MinMaxDownsample : public CmpSH_Base<1, 1, 1>`  
_L56-81_
- inherits: `CmpSH_Base<1,1,1>`
- L60 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(CSH_MinMaxDownsample, CmpSH_Base);`
- L68 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<MinMax::FVar_SourceToMinMaxPass>;` — Permutation domain local
- L71 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L77 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_MinMax`  
`class T_MinMax`  
_L86-96_
- L89 _public prototype_ `T_MinMax();`
- L90 _public prototype_ `~T_MinMax();`
- L95 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, TiledBlobPtr SourceTex, int32 TargetId, bool bUseMeshUVMask = false);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
- L14 _namespace_ `namespace MinMax`
- L51 _prototype_ `template <> void SetupDefaultParameters(FSH_MinMaxDownsample::FParameters& params);`
- L53 _typedef_ `typedef FxMaterial_Normal<VSH_Simple, FSH_MinMaxDownsample> Fx_MinMax;`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_MipMap.h` (Other)


#### class `CSH_MipMapDownsample`  
`class CSH_MipMapDownsample : public CmpSH_Base<1, 1, 1>`  
_L18-38_
- inherits: `CmpSH_Base<1,1,1>`
- L22 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(CSH_MipMapDownsample, CmpSH_Base);`
- L30 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L35 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `T_MipMap`  
`class T_MipMap`  
_L43-60_
- desc: MipMap Transform
- L46 _public prototype_ `T_MipMap();`
- L47 _public prototype_ `~T_MipMap();`
- L59 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, TiledBlobPtr SourceTex, int32 TargetId, int32 GenMipLevel = -1);` — Generate the mip map raster a the specified level Source must be power of 2 for this to work correctly THe layout in tile grid is matching the source tile grid thus if the required level is higher than the actual deepest tile can produce ( aka log2(size of the tile) ) then the transform is returning the deepest level possibly generated with the same tile grid as sourceTex. @TODO SG: Fix that behavior!

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_PrepareResources.h` (Other)


#### class `T_PrepareResources`  
`class T_PrepareResources`  
_L11-18_
- L17 _public prototype_ `static JobPtr Create(MixUpdateCyclePtr Cycle, JobPtr JobObj);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_RenderCapture.h` (Other)


#### class `T_BeginRenderCapture`  
`class T_BeginRenderCapture : public BlobTransform`  
_L11-26_
- inherits: `BlobTransform`
- L14 _public prototype_ `T_BeginRenderCapture();`
- L17 _public prototype_ `virtual Device* TargetDevice(size_t index) const override;`
- L18 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& args) override;`
- L20 _public function_ `virtual bool GeneratesData() const override`
- L25 _public prototype_ `static JobUPtr CreateJob(MixUpdateCyclePtr cycle, int32 targetId);`

#### class `T_EndRenderCapture`  
`class T_EndRenderCapture : public BlobTransform`  
_L29-44_
- inherits: `BlobTransform`
- L32 _public prototype_ `T_EndRenderCapture();`
- L35 _public prototype_ `virtual Device* TargetDevice(size_t index) const override;`
- L36 _public prototype_ `virtual AsyncTransformResultPtr Exec(const TransformArgs& args) override;`
- L38 _public function_ `virtual bool GeneratesData() const override`
- L43 _public prototype_ `static JobUPtr CreateJob(MixUpdateCyclePtr cycle, int32 targetId);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_SplitToTiles.h` (Other)


#### class `CSH_SplitToTiles`  
`class CSH_SplitToTiles : public CmpSH_Base<1, 1, 1>`  
_L17-33_
- inherits: `CmpSH_Base<1,1,1>`
- L21 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(CSH_SplitToTiles, CmpSH_Base);`
- L29 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FxMaterial_SplitToTiles`  
`class FxMaterial_SplitToTiles : public FxMaterial_Compute<CSH_SplitToTiles>`  
_L35-70_
- inherits: `FxMaterial_Compute<CSH_SplitToTiles>`
- L38 _private member_ `int32 NumTilesX;`
- L39 _private member_ `int32 NumTilesY;`
- L40 _private member_ `TiledBlobPtr RefBlob;`
- L43 _public function_ `explicit FxMaterial_SplitToTiles(FString InOutputId, int32 InNumTilesX, int32 InNumTilesY, TiledBlobPtr InRefBlob, const CmpSHPermutationDomain* InPermDomain = nullptr, FUnorderedAccessViewRHIRef InUnorderedAccessView = nullptr) : FxMaterial_Compute<CSH_SplitToTiles>(InOutputId, InPermDomain, 0, 0, 1, InUnorderedAccessView) , NumTilesX(InNumTilesX) , NumTilesY(InNumTilesY) , RefBlob(InRefBlob)`
- L52 _public function_ `virtual void Blit(FRHICommandListImmediate& RHI, FRHITexture* Target, const RenderMesh* MeshObj, int32 TargetId, FGraphicsPipelineStateInitializer* PSO = nullptr) override`
- L65 _public function_ `virtual std::shared_ptr<FxMaterial> Clone() override`

#### class `T_SplitToTiles`  
`class T_SplitToTiles`  
_L75-86_
- desc: SplitToTiles Transform
- L78 _public prototype_ `T_SplitToTiles();`
- L79 _public prototype_ `~T_SplitToTiles();`
- L85 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, int32 TargetId, TiledBlobPtr SourceTex);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`

### `Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_TextureHistogram.h` (Other)


#### class `T_TextureHistogram`  
`class T_TextureHistogram`  
_L17-29_
- desc: T_TextureHistogram Transform
- L20 _public prototype_ `T_TextureHistogram();`
- L21 _public prototype_ `~T_TextureHistogram();`
- L23 _public prototype_ `static TiledBlobPtr Create(MixUpdateCyclePtr Cycle, TiledBlobPtr SourceTex, int32 TargetId);`
- L25 _public prototype_ `static TiledBlobPtr CreateOnService(UMixInterface* InMix, TiledBlobPtr SourceTex, int32 TargetId);`
- L28 _private prototype_ `static TiledBlobPtr CreateJobAndResult(JobUPtr& OutJob, MixUpdateCyclePtr Cycle, TiledBlobPtr Histogram, int32 TargetId);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPHENGINE_API`
