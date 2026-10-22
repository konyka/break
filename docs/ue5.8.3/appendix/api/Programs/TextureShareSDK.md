# Programs / TextureShareSDK

- module root: `Source/Programs/VirtualProduction/TextureShare`
- headers: 12; symbols: 391
- symbol kinds: class=5, enum=4, enumerator=91, function=104, macro=2, member=39, namespace=5, prototype=97, struct=21, typedef=22, variable=1
- PrivateDependencyModuleNames: Core, ImageCore, TextureShareCore

### `Source/Programs/VirtualProduction/TextureShare/Private/TextureShareSDKObject.h` (Private)


#### class `FTextureShareSDKObject`  
`class FTextureShareSDKObject : public ITextureShareSDKObject`  
_L11-87_
- inherits: `ITextureShareSDKObject`
- desc: TextureShareSDK object impl
- L15 _public prototype_ `FTextureShareSDKObject(const TSharedPtr<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject);`
- L16 _public prototype_ `virtual ~FTextureShareSDKObject();`
- L20 _public prototype_ `virtual const wchar_t* GetName() const override;` — State /////////////////////////
- L22 _public prototype_ `virtual void GetObjectDesc(TDataOutput<FTextureShareCoreObjectDesc>& OutObjectDesc) const override;`
- L23 _public prototype_ `virtual void GetObjectDesc_RenderThread(TDataOutput<FTextureShareCoreObjectDesc>& OutObjectDesc) const override;`
- L25 _public prototype_ `virtual bool IsActive() const override;`
- L26 _public prototype_ `virtual bool IsActive_RenderThread() const override;`
- L28 _public prototype_ `virtual bool IsFrameSyncActive() const override;`
- L29 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const override;`
- L31 _public prototype_ `virtual bool IsBeginFrameSyncActive() const override;`
- L32 _public prototype_ `virtual bool IsBeginFrameSyncActive_RenderThread() const override;`
- L36 _public prototype_ `virtual bool SetProcessId(const wchar_t* InProcessId) override;` — Settings /////////////////////////
- L37 _public prototype_ `virtual bool SetDeviceType(const ETextureShareDeviceType InDeviceType) override;`
- L38 _public prototype_ `virtual bool SetSyncSetting(const TDataInput<FTextureShareCoreSyncSettings>& InSyncSetting) override;`
- L39 _public prototype_ `virtual void GetSyncSetting(TDataOutput<FTextureShareCoreSyncSettings>& OutSyncSettings) const override;`
- L40 _public prototype_ `virtual void GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType, TDataOutput<FTextureShareCoreFrameSyncSettings>& OutFrameSyncSettings) const override;`
- L42 _public prototype_ `virtual bool FindSkippedSyncStep(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) const override;`
- L43 _public prototype_ `virtual bool FindSkippedSyncStep_RenderThread(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) const override;`
- L47 _public prototype_ `virtual bool BeginSession() override;` — Session /////////////////////////
- L48 _public prototype_ `virtual bool EndSession() override;`
- L49 _public prototype_ `virtual bool IsSessionActive() const override;`
- L53 _public prototype_ `virtual bool LockThreadMutex(const ETextureShareThreadMutex InThreadMutex, bool bForceLockNoWait = false) override;` — Thread sync support /////////////////////////
- L54 _public prototype_ `virtual bool UnlockThreadMutex(const ETextureShareThreadMutex InThreadMutex) override;`
- L58 _public prototype_ `virtual bool BeginFrameSync() override;` — Interprocess Synchronization /////////////////////////
- L59 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) override;`
- L60 _public prototype_ `virtual bool EndFrameSync() override;`
- L61 _public prototype_ `virtual bool BeginFrameSync_RenderThread() override;`
- L62 _public prototype_ `virtual bool FrameSync_RenderThread(const ETextureShareSyncStep InSyncStep) override;`
- L63 _public prototype_ `virtual bool EndFrameSync_RenderThread() override;`
- L64 _public prototype_ `virtual void GetConnectedInterprocessObjects(TDataOutput<TArraySerializable<FTextureShareCoreObjectDesc>>& OutObjectList) const override;`
- L68 _public prototype_ `virtual void GetData(TDataOutput<FTextureShareCoreData>& OutObjectData) override;` — Data Containers /////////////////////////
- L69 _public prototype_ `virtual void SetData(const TDataInput<FTextureShareCoreData>& InObjectData) override;`
- L70 _public prototype_ `virtual void GetProxyData_RenderThread(TDataOutput<FTextureShareCoreProxyData>& OutObjectProxyData) override;`
- L71 _public prototype_ `virtual void SetProxyData_RenderThread(const TDataInput<FTextureShareCoreProxyData>& InObjectProxyData) override;`
- L72 _public prototype_ `virtual void GetReceivedData(TDataOutput<TArraySerializable<FTextureShareCoreObjectData>>& OutReceivedObjectsData) const override;`
- L73 _public prototype_ `virtual void GetReceivedProxyData_RenderThread(TDataOutput<TArraySerializable<FTextureShareCoreObjectProxyData>>& OutObjectsProxyData) const override;`
- L77 _public prototype_ `virtual ID3D11Texture2D* OpenSharedResourceD3D11(ID3D11Device* pD3D11Device, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc) override;` — Access to shared resources /////////////////////////
- L78 _public prototype_ `virtual ID3D12Resource* OpenSharedResourceD3D12(ID3D12Device* pD3D12Device, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc) override;`
- L80 _public prototype_ `virtual bool OpenSharedResourceVulkan(const TDataInput<FTextureShareDeviceVulkanContext>& InDeviceVulkanContext, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc, TDataOutput<FTextureShareDeviceVulkanResource>& OutVulkanResource) override;`
- L83 _private prototype_ `bool ImplFindResource(const struct FTextureShareCoreResourceDesc& InResourceDesc, struct FTextureShareCoreResourceHandle& OutResourceHandle) const;`
- L86 _private member_ `TSharedPtr<ITextureShareCoreObject, ESPMode::ThreadSafe> const CoreObject;`

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/TextureShareSDKContainers.h` (Public)


#### Free symbols / members of external scopes

- L20 _macro_ `#define TEXTURESHARESDK_API __declspec(dllimport)` — Support SDK user side DLL functions import

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineArray.h` (Public)


#### enum `(anonymous)`  
`enum`  
_L10-10_

#### struct `TArray`  
`template<typename InElementType> struct TArray : public std::vector<InElementType>`  
_L18-210_
- inherits: `std::vector<InElementType>`
- desc: Implementation of TArray on the SDK ext app side (reflect this data type)
- L21 _public typedef_ `typedef InElementType ElementType;`
- L22 _public typedef_ `typedef int32 SizeType;`
- L31 _public function_ `inline SizeType Find(const ElementType& Item) const` — Finds element within the array. @param Item Item to look for. @returns Index of the found element. INDEX_NONE otherwise. @see FindLast, FindLastByPredicate
- L50 _public function_ `inline ElementType* GetData()` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L60 _public function_ `inline const ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L68 _public function_ `inline void Empty()` — Empties the array. It calls the destructors on held items if needed.
- L77 _public function_ `void Reset()` — Same as empty, but doesn't change memory allocations, unless the new size is larger than the current array. It calls the destructors on held items if needed and then zeros the ArrayNum.
- L88 _public function_ `inline bool IsEmpty() const` — Returns true if the array is empty and contains no elements. @returns True if the array is empty. @see Num
- L98 _public function_ `inline SizeType Num() const` — Returns number of elements in array. @returns Number of elements in array.
- L112 _public function_ `inline SizeType Add(const ElementType& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L121 _public function_ `inline SizeType AddUnique(const ElementType& Item)`
- L134 _public function_ `inline void Insert(const ElementType& Item, const int32 Index)`
- L151 _public function_ `inline SizeType AddZeroed(SizeType Count = 1)` — Adds new items to the end of the array, possibly reallocating the whole array to fit. The new items will be zeroed. Caution, AddZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param  Count  The number of new items to add. @return Index to the first of the new items. @see Add, AddDefaulted, AddUnique, Append, Insert
- L176 _public function_ `inline SizeType AddDefaulted(SizeType Count = 1)` — Adds new items to the end of the array, possibly reallocating the whole array to fit. The new items will be default-constructed. @param  Count  The number of new items to add. @return Index to the first of the new items. @see Add, AddZeroed, AddUnique, Append, Insert
- L196 _public function_ `inline void RemoveAt(SizeType Index, SizeType Count = 1)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove.

#### Free symbols / members of external scopes

- L10 _enumerator_ `enum { INDEX_NONE = -1 }; /** * Implementation of TArray on the SDK ext app side (reflect this data type) */ template<typename InElementType>` (scope `__anondef5dcd70103`)

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineContainers.h` (Public)


#### struct `FGuid`  
`struct FGuid`  
_L15-27_
- desc: SDK ext app type (reflect UE struct FGuid)
- L17 _public member_ `uint32 A = 0;`
- L18 _public member_ `uint32 B = 0;`
- L19 _public member_ `uint32 C = 0;`
- L20 _public member_ `uint32 D = 0;`
- L23 _public function_ `inline bool operator==(const FGuid& In) const`

#### struct `FIntPoint`  
`struct FIntPoint`  
_L32-45_
- desc: SDK ext app type (reflect UE struct FIntPoint)
- L34 _public member_ `int32 X = 0;`
- L35 _public member_ `int32 Y = 0;`
- L38 _public prototype_ `FIntPoint() = default;`
- L39 _public function_ `FIntPoint(int32 InX, int32 InY) : X(InX), Y(InY)`
- L44 _public member_ `static FIntPoint ZeroValue;`

#### struct `FIntRect`  
`struct FIntRect`  
_L50-60_
- desc: SDK ext app type (reflect UE struct FIntRect)
- L52 _public member_ `FIntPoint Min;`
- L53 _public member_ `FIntPoint Max;`
- L56 _public prototype_ `FIntRect() = default;`
- L57 _public function_ `FIntRect(const FIntPoint& InMin, const FIntPoint& InMax) : Min(InMin), Max(InMax)`

#### struct `FVector`  
`struct FVector`  
_L65-79_
- desc: SDK ext app type (reflect UE struct FVector)
- L67 _public member_ `double X = 0;`
- L68 _public member_ `double Y = 0;`
- L69 _public member_ `double Z = 0;`
- L72 _public prototype_ `FVector() = default;`
- L73 _public function_ `FVector(double InX, double InY, double InZ) : X(InX), Y(InY), Z(InZ)`
- L78 _public member_ `static FVector ZeroVector;`

#### struct `FQuat`  
`struct FQuat`  
_L84-96_
- desc: SDK ext app type (reflect UE struct FQuat)
- L86 _public member_ `double X = 0;`
- L87 _public member_ `double Y = 0;`
- L88 _public member_ `double Z = 0;`
- L89 _public member_ `double W = 1;`
- L92 _public prototype_ `FQuat() = default;`
- L93 _public function_ `FQuat(double InX, double InY, double InZ, double InW) : X(InX), Y(InY), Z(InZ), W(InW)`

#### struct `FVector2D`  
`struct FVector2D`  
_L101-111_
- desc: SDK ext app type (reflect UE struct FVector2D)
- L103 _public member_ `double X = 0;`
- L104 _public member_ `double Y = 0;`
- L107 _public prototype_ `FVector2D() = default;`
- L108 _public function_ `FVector2D(double InX, double InY) : X(InX), Y(InY)`

#### struct `FMatrix`  
`struct FMatrix`  
_L116-125_
- desc: SDK ext app type (reflect UE struct FMatrix)
- L118 _public member_ `double M[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };`
- L121 _public prototype_ `FMatrix() = default;`
- L124 _public member_ `static FMatrix Identity;`

#### struct `FRotator`  
`struct FRotator`  
_L130-149_
- desc: SDK ext app type (reflect UE struct FRotator)
- L133 _public member_ `double Pitch = 0;` — Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down)
- L136 _public member_ `double Yaw = 0;` — Rotation around the up axis (around Z axis), Running in circles 0=East, +North, -South.
- L139 _public member_ `double Roll = 0;` — Rotation around the forward axis (around X axis), Tilting your head, 0=Straight, +Clockwise, -CCW.
- L142 _public prototype_ `FRotator() = default;`
- L143 _public function_ `FRotator(double InPitch, double InYaw, double InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)`
- L148 _public member_ `static FRotator ZeroRotator;`

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineEnums_PixelFormat.h` (Public)


#### enum `EPixelFormat`  
`enum EPixelFormat : uint8`  
_L11-100_
- desc: Reflect UE EPixelFormat enum on the SDK ext app side The code below is copied from the UE
- L13 _public enumerator_ `PF_Unknown = 0`
- L14 _public enumerator_ `PF_A32B32G32R32F = 1`
- L15 _public enumerator_ `PF_B8G8R8A8 = 2`
- L16 _public enumerator_ `PF_G8 = 3`
- L17 _public enumerator_ `PF_G16 = 4`
- L18 _public enumerator_ `PF_DXT1 = 5`
- L19 _public enumerator_ `PF_DXT3 = 6`
- L20 _public enumerator_ `PF_DXT5 = 7`
- L21 _public enumerator_ `PF_UYVY = 8`
- L22 _public enumerator_ `PF_FloatRGB = 9`
- L23 _public enumerator_ `PF_FloatRGBA = 10`
- L24 _public enumerator_ `PF_DepthStencil = 11`
- L25 _public enumerator_ `PF_ShadowDepth = 12`
- L26 _public enumerator_ `PF_R32_FLOAT = 13`
- L27 _public enumerator_ `PF_G16R16 = 14`
- L28 _public enumerator_ `PF_G16R16F = 15`
- L29 _public enumerator_ `PF_G16R16F_FILTER = 16`
- L30 _public enumerator_ `PF_G32R32F = 17`
- L31 _public enumerator_ `PF_A2B10G10R10 = 18`
- L32 _public enumerator_ `PF_A16B16G16R16 = 19`
- L33 _public enumerator_ `PF_D24 = 20`
- L34 _public enumerator_ `PF_R16F = 21`
- L35 _public enumerator_ `PF_R16F_FILTER = 22`
- L36 _public enumerator_ `PF_BC5 = 23`
- L37 _public enumerator_ `PF_V8U8 = 24`
- L38 _public enumerator_ `PF_A1 = 25`
- L39 _public enumerator_ `PF_FloatR11G11B10 = 26`
- L40 _public enumerator_ `PF_A8 = 27`
- L41 _public enumerator_ `PF_R32_UINT = 28`
- L42 _public enumerator_ `PF_R32_SINT = 29`
- L43 _public enumerator_ `PF_PVRTC2 = 30`
- L44 _public enumerator_ `PF_PVRTC4 = 31`
- L45 _public enumerator_ `PF_R16_UINT = 32`
- L46 _public enumerator_ `PF_R16_SINT = 33`
- L47 _public enumerator_ `PF_R16G16B16A16_UINT = 34`
- L48 _public enumerator_ `PF_R16G16B16A16_SINT = 35`
- L49 _public enumerator_ `PF_R5G6B5_UNORM = 36`
- L50 _public enumerator_ `PF_R8G8B8A8 = 37`
- L51 _public enumerator_ `PF_A8R8G8B8 = 38` — Only used for legacy loading; do NOT use!
- L52 _public enumerator_ `PF_BC4 = 39`
- L53 _public enumerator_ `PF_R8G8 = 40`
- L54 _public enumerator_ `PF_ATC_RGB = 41` — Unsupported Format
- L55 _public enumerator_ `PF_ATC_RGBA_E = 42` — Unsupported Format
- L56 _public enumerator_ `PF_ATC_RGBA_I = 43` — Unsupported Format
- L57 _public enumerator_ `PF_X24_G8 = 44` — Used for creating SRVs to alias a DepthStencil buffer to read Stencil. Don't use for creating textures.
- L58 _public enumerator_ `PF_ETC1 = 45` — Unsupported Format
- L59 _public enumerator_ `PF_ETC2_RGB = 46`
- L60 _public enumerator_ `PF_ETC2_RGBA = 47`
- L61 _public enumerator_ `PF_R32G32B32A32_UINT = 48`
- L62 _public enumerator_ `PF_R16G16_UINT = 49`
- L63 _public enumerator_ `PF_ASTC_4x4 = 50` — 8.00 bpp
- L64 _public enumerator_ `PF_ASTC_6x6 = 51` — 3.56 bpp
- L65 _public enumerator_ `PF_ASTC_8x8 = 52` — 2.00 bpp
- L66 _public enumerator_ `PF_ASTC_10x10 = 53` — 1.28 bpp
- L67 _public enumerator_ `PF_ASTC_12x12 = 54` — 0.89 bpp
- L68 _public enumerator_ `PF_BC6H = 55`
- L69 _public enumerator_ `PF_BC7 = 56`
- L70 _public enumerator_ `PF_R8_UINT = 57`
- L71 _public enumerator_ `PF_L8 = 58`
- L72 _public enumerator_ `PF_XGXR8 = 59`
- L73 _public enumerator_ `PF_R8G8B8A8_UINT = 60`
- L74 _public enumerator_ `PF_R8G8B8A8_SNORM = 61`
- L75 _public enumerator_ `PF_R16G16B16A16_UNORM = 62`
- L76 _public enumerator_ `PF_R16G16B16A16_SNORM = 63`
- L77 _public enumerator_ `PF_PLATFORM_HDR_0 = 64`
- L78 _public enumerator_ `PF_PLATFORM_HDR_1 = 65` — Reserved.
- L79 _public enumerator_ `PF_PLATFORM_HDR_2 = 66` — Reserved.
- L80 _public enumerator_ `PF_NV12 = 67`
- L81 _public enumerator_ `PF_R32G32_UINT = 68`
- L82 _public enumerator_ `PF_ETC2_R11_EAC = 69`
- L83 _public enumerator_ `PF_ETC2_RG11_EAC = 70`
- L84 _public enumerator_ `PF_R8 = 71`
- L85 _public enumerator_ `PF_B5G5R5A1_UNORM = 72`
- L86 _public enumerator_ `PF_ASTC_4x4_HDR = 73`
- L87 _public enumerator_ `PF_ASTC_6x6_HDR = 74`
- L88 _public enumerator_ `PF_ASTC_8x8_HDR = 75`
- L89 _public enumerator_ `PF_ASTC_10x10_HDR = 76`
- L90 _public enumerator_ `PF_ASTC_12x12_HDR = 77`
- L91 _public enumerator_ `PF_G16R16_SNORM = 78`
- L92 _public enumerator_ `PF_R8G8_UINT = 79`
- L93 _public enumerator_ `PF_R32G32B32_UINT = 80`
- L94 _public enumerator_ `PF_R32G32B32_SINT = 81`
- L95 _public enumerator_ `PF_R32G32B32F = 82`
- L96 _public enumerator_ `PF_R8_SINT = 83`
- L97 _public enumerator_ `PF_R64_UINT = 84`
- L98 _public enumerator_ `PF_R9G9B9EXP5 = 85`
- L99 _public enumerator_ `PF_P010 = 86`

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineMath.h` (Public)


#### struct `FMath`  
`struct FMath`  
_L16-52_
- desc: Reflect UE funcs to SDK ext app side The code below is copied from the UE
- L20 _public function_ `template< class T > static constexpr inline T Abs(const T A)` — Computes absolute value in a generic way
- L27 _public function_ `template< class T > static constexpr inline T Sign(const T A)` — Returns 1, 0, or -1 depending on relation of T to 0
- L34 _public function_ `template< class T > static constexpr inline T Max(const T A, const T B)` — Returns higher value in a generic way
- L41 _public function_ `template< class T > static constexpr inline T Min(const T A, const T B)` — Returns lower value in a generic way
- L47 _public function_ `static constexpr inline double Max(const double A, const float B)` — Allow mixing of float types to promote to highest precision type
- L48 _public function_ `static constexpr inline double Max(const float A, const double B)`
- L49 _public function_ `static constexpr inline double Min(const double A, const float B)`
- L50 _public function_ `static constexpr inline double Min(const float A, const double B)`

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineString.h` (Public)


#### enum `ESearchCase::Type`  
`enum Type`  
_L22-26_
- L24 _public enumerator_ `CaseSensitive`
- L25 _public enumerator_ `IgnoreCase`

#### struct `FPlatformString::TUnsignedIntType`  
`template <int NumBytes> struct TUnsignedIntType`  
_L39-40_
- desc: Type trait which yields an unsigned integer type of a given number of bytes. If there is no such type, the Type member type will be absent, allowing it to be used in SFINAE contexts.
- L42 _public typedef_ `template <> struct TUnsignedIntType<1> { using Type = uint8; };`

#### struct `FPlatformString::TUnsignedIntType`  
`template <> struct TUnsignedIntType<1>`  
_L42-42_
- L42 _public typedef_ `template <> struct TUnsignedIntType<1> { using Type = uint8; };`

#### struct `FPlatformString::TUnsignedIntType`  
`template <> struct TUnsignedIntType<1>`  
_L43-43_
- L42 _public typedef_ `template <> struct TUnsignedIntType<1> { using Type = uint8; };`

#### struct `FPlatformString::TUnsignedIntType`  
`template <> struct TUnsignedIntType<1>`  
_L44-44_
- L42 _public typedef_ `template <> struct TUnsignedIntType<1> { using Type = uint8; };`

#### struct `FPlatformString::TUnsignedIntType`  
`template <> struct TUnsignedIntType<1>`  
_L45-45_
- L42 _public typedef_ `template <> struct TUnsignedIntType<1> { using Type = uint8; };`

#### struct `FPlatformString::TChar`  
`template <typename CharType> struct TChar`  
_L56-62_
- desc: Avoid sign extension problems with signed characters smaller than int E.g. 'Ö' - 'A' is negative since the char 'Ö' (0xD6) is negative and gets sign-extended to the 32-bit int 0xFFFFFFD6 before subtraction happens. Mainly needed for subtraction and addition.
- L58 _public function_ `static constexpr uint32 ToUnsigned(CharType Char)`

#### struct `FString`  
`struct FString`  
_L164-289_
- desc: Implement FString simple container for SDK data type mirroring
- L166 _public member_ `std::wstring Data;`
- L168 _public typedef_ `typedef wchar_t CharType;`
- L169 _public typedef_ `typedef int32 SizeType;`
- L172 _public prototype_ `FString() = default;`
- L174 _public function_ `FString(const FString& In)`
- L179 _public function_ `FString(const CharType* In)`
- L184 _public function_ `FString(const CharType* In1, const CharType* In2)`
- L190 _public function_ `FString(const CharType* In1, const CharType* In2, const CharType* In3)`
- L197 _public function_ `FString(const CharType* In1, const CharType* In2, const CharType* In3, const CharType* In4)`
- L206 _public function_ `inline void operator=(const FString& In)`
- L211 _public function_ `inline void operator=(const CharType* In)`
- L216 _public function_ `inline const CharType* operator*() const`
- L221 _public function_ `inline SizeType Len() const`
- L226 _public function_ `inline bool IsEmpty() const`
- L239 _public function_ `inline bool Equals(const FString& Other, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const` — Lexicographically tests whether this string is equivalent to the Other given string @param Other 	The string test against @param SearchCase 	Whether or not the comparison should ignore case @return true if this string is lexicographically equivalent to the other, otherwise false

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ESearchCase`
- L32 _namespace_ `namespace FPlatformString`
- L64 _typedef_ `typedef wchar_t WIDECHAR;` (scope `FPlatformString`)
- L65 _typedef_ `typedef size_t SIZE_T;` (scope `FPlatformString`)
- L68 _variable_ `static constexpr uint8 LowerAscii[128] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F };` (scope `FPlatformString`) — Copied from \\Engine\Source\Runtime\Core\Private\GenericPlatform\GenericPlatformStricmp.cpp
- L79 _function_ `inline bool BothAscii(uint32 C1, uint32 C2)` (scope `FPlatformString`)
- L84 _function_ `inline int32 Strcmp(const WIDECHAR* String1, const WIDECHAR* String2)` (scope `FPlatformString`)
- L90 _function_ `template<typename CharType1, typename CharType2> inline int32 StricmpImpl(const CharType1* String1, const CharType2* String2)` (scope `FPlatformString`)
- L126 _function_ `template<typename CharType1, typename CharType2> inline int32 StrnicmpImpl(const CharType1* String1, const CharType2* String2, SIZE_T Count)` (scope `FPlatformString`)
- L160 _function_ `inline int32 Stricmp(const WIDECHAR* Str1, const WIDECHAR* Str2)` (scope `FPlatformString`)
- L272 _function_ `friend inline bool operator==(const FString& Lhs, const FString& Rhs)` — Lexicographically test whether the left string is == the right string @param Lhs String to compare against. @param Rhs String to compare against. @return true if the left string is lexicographically == the right string, otherwise false @note case insensitive
- L285 _function_ `friend inline bool operator==(const FString& Lhs, const CharType* Rhs)` — Lexicographically test whether the left string is == the right string @param Lhs String to compare against. @param Rhs String to compare against. @return true if the left string is lexicographically == the right string, otherwise false @note case insensitive

### `Source/Programs/VirtualProduction/TextureShare/Public/Containers/UnrealEngine/TextureShareSDKUnrealEngineTypes.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Windows`
- L13 _typedef_ `typedef void* HANDLE;` (scope `Windows`)
- L17 _typedef_ `typedef signed char schar;` — Standard typedefs
- L18 _typedef_ `typedef signed char int8;`
- L19 _typedef_ `typedef short int16;`
- L20 _typedef_ `typedef int int32;`
- L22 _typedef_ `typedef __int64 int64;`
- L24 _typedef_ `typedef long long int64;`
- L27 _typedef_ `typedef unsigned char uint8;`
- L28 _typedef_ `typedef unsigned short uint16;`
- L29 _typedef_ `typedef unsigned int uint32;`
- L31 _typedef_ `typedef unsigned __int64 uint64;`
- L33 _typedef_ `typedef unsigned long long uint64;`

### `Source/Programs/VirtualProduction/TextureShare/Public/ITextureShareSDK.h` (Public)


#### class `ITextureShareSDK`  
`class ITextureShareSDK`  
_L9-74_
- desc: TextureShareSDK API
- L19 _public prototype_ `static ITextureShareSDKObject* GetOrCreateObject(const wchar_t* ShareName);` — Get exist or create new ITextureShareSDKObject object @param ShareName   - Unique share name @return - Pointer to an existing/new interface, or null (if the name is already in use in another interface type)
- L28 _public prototype_ `static bool IsObjectExist(const wchar_t* ShareName);` — Check if ITextureShareSDKObject object with that name exist @param ShareName   - Unique share name @return - true if exist
- L37 _public prototype_ `static bool RemoveObject(const wchar_t* ShareName);` — Release ITextureShareSDKObject object @param ShareName   - Unique share name @return - true if released
- L47 _public prototype_ `static bool GetInterprocessObjects(TDataOutput<TArraySerializable<FTextureShareCoreObjectDesc>>& OutInterprocessObjects, const wchar_t* ShareName = nullptr);` — Returns a description of all objects @param OutInterprocessObjects - All exist texture share objects on this computer @param ShareName              - (optional) return only objects with this name @return - true if success
- L52 _public prototype_ `static void GetProcessDesc(TDataOutput<FTextureShareCoreObjectProcessDesc>& OutProcessDesc);` — Returns detailed information about the local process
- L59 _public prototype_ `static void SetProcessName(const wchar_t* InProcessId);` — Assign a unique name to the local process. The changes only affect newly created TextureShare objects. @param InProcessId - Custom local process name
- L66 _public prototype_ `static bool SetProcessDeviceType(const ETextureShareDeviceType InDeviceType);` — Assign a device type to the local process. The changes only affect newly created TextureShare objects. @param InDeviceType - render device type
- L73 _public prototype_ `static void RemoveUnusedResources(const uint32 InMilisecondsTimeOut);` — Release all resources last used more than specified timeout value @param InMilisecondsTimeOut - Timeout to remove resource

### `Source/Programs/VirtualProduction/TextureShare/Public/ITextureShareSDKObject.h` (Public)


#### class `ITextureShareSDKObject`  
`class ITextureShareSDKObject`  
_L11-307_
- desc: TextureShareSDK object API
- L14 _public prototype_ `virtual ~ITextureShareSDKObject() = default;`
- L22 _public prototype_ `virtual const wchar_t* GetName() const = 0;` — Return the name of the TextureShare.
- L27 _public prototype_ `virtual void GetObjectDesc(TDataOutput<FTextureShareCoreObjectDesc>& OutObjectDesc) const = 0;` — Returns detailed information about the TextureShare object.
- L32 _public prototype_ `virtual void GetObjectDesc_RenderThread(TDataOutput<FTextureShareCoreObjectDesc>& OutObjectDesc) const = 0;` — Returns detailed information about the TextureShare proxy object.
- L37 _public prototype_ `virtual bool IsActive() const = 0;` — Returns true if the TextureShare object is ready to be used.
- L42 _public prototype_ `virtual bool IsActive_RenderThread() const = 0;` — Returns true if the TextureShare object proxy is ready to be used.
- L47 _public prototype_ `virtual bool IsFrameSyncActive() const = 0;` — Returns true if the TextureShareCore object has started a session and processes are connected for this frame.
- L52 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const = 0;` — Returns true if the TextureShareCore object proxy has started a session and processes are connected for this frame.
- L58 _public prototype_ `virtual bool IsBeginFrameSyncActive() const = 0;` — Support for multi-threaded implementation. Returns true if the BeginFrameSync() function can be called at this moment for object
- L64 _public prototype_ `virtual bool IsBeginFrameSyncActive_RenderThread() const = 0;` — Support for multi-threaded implementation. Returns true if the BeginFrameSync() function can be called at this moment for object proxy
- L77 _public prototype_ `virtual bool SetProcessId(const wchar_t* InProcessId) = 0;` — Change the process name for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InProcessId - New process name @return true, if success
- L84 _public prototype_ `virtual bool SetDeviceType(const ETextureShareDeviceType InDeviceType) = 0;` — Assign a device type for this TextureShare object. @param InDeviceType - render device type
- L94 _public prototype_ `virtual bool SetSyncSetting(const TDataInput<FTextureShareCoreSyncSettings>& InSyncSetting) = 0;` — Change the sync settings for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InSyncSetting - New sync settings @return true, if success
- L99 _public prototype_ `virtual void GetSyncSetting(TDataOutput<FTextureShareCoreSyncSettings>& OutSyncSettings) const = 0;` — Return the sync settings of the TextureShare.
- L109 _public prototype_ `virtual void GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType, TDataOutput<FTextureShareCoreFrameSyncSettings>& OutFrameSyncSettings) const = 0;` — Get TextureShare default sync settings by template type The settings of this template are not related to the current settings of the object @param InType - Sync settings template type @return structure with sync logic settings
- L119 _public prototype_ `virtual bool FindSkippedSyncStep(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) const = 0;` — Find skipped frame sync step @param InSyncStep           - Sync step value @param OutSkippedSyncStep   - Skipped sync step value @return true, if skipped sync step found
- L129 _public prototype_ `virtual bool FindSkippedSyncStep_RenderThread(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) const = 0;` — Find skipped frame sync step for proxy object @param InSyncStep           - Sync step value @param OutSkippedSyncStep   - Skipped sync step value @return true, if skipped sync step found
- L141 _public prototype_ `virtual bool BeginSession() = 0;` — Start a TextureShare session for the specified device @param InDeviceType     - Shared resources render device type @return True if the success
- L148 _public prototype_ `virtual bool EndSession() = 0;` — End the TextureShare session and the resources in use are also removed. @return True if the success
- L153 _public prototype_ `virtual bool IsSessionActive() const = 0;` — Returns true if the session is currently valid
- L167 _public prototype_ `virtual bool LockThreadMutex(const ETextureShareThreadMutex InThreadMutex, bool bForceLockNoWait = false) = 0;` — Support for multi-threaded implementation. The mutex of the specified type will be locked (and created for the first time) @param InThreadMutex - Mutex type @param bForceLockNoWait - lock without waiting for unlock @return True if the success
- L177 _public prototype_ `virtual bool UnlockThreadMutex(const ETextureShareThreadMutex InThreadMutex) = 0;` — Support for multi-threaded implementation. The mutex of the specified type will be unlocked @param InThreadMutex - Mutex type @return True if the success
- L187 _public prototype_ `virtual bool BeginFrameSync() = 0;` — Begin sync logic in range FrameBegin..FrameEnd The list of connected processes for the current frame will also be updated. Returns true if the frame is connected to other processes that match the synchronization settings.
- L198 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) = 0;` — Synchronize connected processes that support this sync step Data from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L204 _public prototype_ `virtual bool EndFrameSync() = 0;` — Finalize sync logic in range FrameBegin..FrameEnd Missed sync steps from the sync settings will also be called.
- L209 _public prototype_ `virtual bool BeginFrameSync_RenderThread() = 0;` — Begin sync logic in range FrameProxyBegin..FrameProxyEnd
- L220 _public prototype_ `virtual bool FrameSync_RenderThread(const ETextureShareSyncStep InSyncStep) = 0;` — Synchronize connected processes that support this sync step ProxyData from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L226 _public prototype_ `virtual bool EndFrameSync_RenderThread() = 0;` — Finalize sync logic in range FrameProxyBegin..FrameProxyEnd Missed sync steps from the sync settings will also be called.
- L235 _public prototype_ `virtual void GetConnectedInterprocessObjects(TDataOutput<TArraySerializable<FTextureShareCoreObjectDesc>>& OutObjectList) const = 0;` — Returns a list of handles to the interprocess TextureShare objects that are currently connected to this object. @param OutInterprocessObjects - Output array with handles to TextureShare objects @return true, if success
- L244 _public prototype_ `virtual void GetData(TDataOutput<FTextureShareCoreData>& OutObjectData) = 0;` — Get object data Object data for the current frame in the GameThread.
- L250 _public prototype_ `virtual void SetData(const TDataInput<FTextureShareCoreData>& InObjectData) = 0;` — Set object data Set new object data for the current frame in the GameThread.
- L256 _public prototype_ `virtual void GetProxyData_RenderThread(TDataOutput<FTextureShareCoreProxyData>& OutObjectProxyData) = 0;` — Get object ProxyData. Object proxy data for the current frame in the RenderThread.
- L262 _public prototype_ `virtual void SetProxyData_RenderThread(const TDataInput<FTextureShareCoreProxyData>& InObjectProxyData) = 0;` — Set object ProxyData. Object proxy data for the current frame in the RenderThread.
- L267 _public prototype_ `virtual void GetReceivedData(TDataOutput<TArraySerializable<FTextureShareCoreObjectData>>& OutReceivedObjectsData) const = 0;` — Received Data from connected process objects
- L272 _public prototype_ `virtual void GetReceivedProxyData_RenderThread(TDataOutput<TArraySerializable<FTextureShareCoreObjectProxyData>>& OutObjectsProxyData) const = 0;` — Received ProxyData from connected process objects
- L285 _public prototype_ `virtual ID3D11Texture2D* OpenSharedResourceD3D11(ID3D11Device* InD3D11Device, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc) = 0;` — Open shared D3D11 resource @param InD3D11Device - D3D11 device interface @param InResourceDesc- Shared resource descriptor @return pointer to shared D3D11 texture, or nullptr on failure
- L295 _public prototype_ `virtual ID3D12Resource* OpenSharedResourceD3D12(ID3D12Device* InD3D12Device, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc) = 0;` — Open shared D3D12 resource @param InD3D12Device - D3D12 device interface @param InResourceDesc- Shared resource descriptor @return pointer to shared D3D12 texture, or nullptr on failure
- L306 _public prototype_ `virtual bool OpenSharedResourceVulkan(const TDataInput<FTextureShareDeviceVulkanContext>& InDeviceVulkanContext, const TDataInput<FTextureShareCoreResourceDesc>& InResourceDesc, TDataOutput<FTextureShareDeviceVulkanResource>& OutVulkanResource) = 0;` — Open shared Vulkan resource @parama InDeviceVulkanContext - Vulkan device context @param InResourceDesc         - Shared resource descriptor @param OutVulkanResource      - Output Vulkan resource @return true, if resource opened

### `Source/Programs/VirtualProduction/TextureShare/Public/Serialize/ITextureShareSDKSerializeStream.h` (Public)


#### class `ITextureShareSDKSerializeStream`  
`class ITextureShareSDKSerializeStream : public ITextureShareSerializeStream`  
_L12-140_
- inherits: `ITextureShareSerializeStream`
- desc: Support SDK data types serialization
- L16 _public prototype_ `virtual ~ITextureShareSDKSerializeStream() = default;`
- L19 _public function_ `virtual ITextureShareSerializeStream& operator<<(ITextureShareSerialize& InOutData) override` — Serialize any serializable objects
- L26 _public function_ `virtual ITextureShareSerializeStream& operator<<(int8& In) override` — Serialize atomic types:
- L27 _public function_ `virtual ITextureShareSerializeStream& operator<<(int16& In) override`
- L28 _public function_ `virtual ITextureShareSerializeStream& operator<<(int32& In) override`
- L29 _public function_ `virtual ITextureShareSerializeStream& operator<<(int64& In) override`
- L31 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint8& In) override`
- L32 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint16& In) override`
- L33 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint32& In) override`
- L34 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint64& In) override`
- L36 _public function_ `virtual ITextureShareSerializeStream& operator<<(float& In) override`
- L37 _public function_ `virtual ITextureShareSerializeStream& operator<<(double& In) override`
- L38 _public function_ `virtual ITextureShareSerializeStream& operator<<(bool& In) override`
- L42 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareFrameSyncTemplate& In) override` — Serialize TextureShare enums:
- L44 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncPass& In) override`
- L45 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncState& In) override`
- L47 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncStep& In) override`
- L48 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareResourceType& In) override`
- L50 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareTextureOp& In) override`
- L51 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareEyeType& In) override`
- L52 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareDeviceType& In) override`
- L53 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareProcessType& In) override`
- L55 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareCoreSceneViewManualProjectionType& In) override`
- L56 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewRotationDataType& In) override`
- L57 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewLocationDataType& In) override`
- L61 _public function_ `virtual ITextureShareSerializeStream& operator<<(EPixelFormat& In) override` — Serialize other enums
- L62 _public function_ `virtual ITextureShareSerializeStream& operator<<(DXGI_FORMAT& In) override`
- L66 _public function_ `virtual ITextureShareSerializeStream& operator<<(FString& InOutData) override` — Serialize UECore types:
- L92 _public function_ `virtual ITextureShareSerializeStream& operator<<(FVector& InOutData) override`
- L97 _public function_ `virtual ITextureShareSerializeStream& operator<<(FVector2D& InOutData) override`
- L102 _public function_ `virtual ITextureShareSerializeStream& operator<<(FRotator& InOutData) override`
- L107 _public function_ `virtual ITextureShareSerializeStream& operator<<(FQuat& InOutData) override`
- L112 _public function_ `virtual ITextureShareSerializeStream& operator<<(FMatrix& InOutData) override`
- L121 _public function_ `virtual ITextureShareSerializeStream& operator<<(FIntRect& InOutData) override`
- L126 _public function_ `virtual ITextureShareSerializeStream& operator<<(FIntPoint& InOutData) override`
- L131 _public function_ `virtual ITextureShareSerializeStream& operator<<(FGuid& InOutData) override`
- L136 _public function_ `virtual ITextureShareSerializeStream& operator<<(Windows::HANDLE& InOutData) override`

### `Source/Programs/VirtualProduction/TextureShare/Public/Serialize/TextureShareSDKDataWrappers.h` (Public)


#### enum `DataSerializer::Limits`  
`enum Limits`  
_L35-39_
- L38 _public enumerator_ `MaxStreamDataSize = (32 * 1024)` — Transaction memory block size

#### struct `DataSerializer::FStreamWrite`  
`struct FStreamWrite : public IDataContainerSerializeStream`  
_L44-90_
- inherits: `IDataContainerSerializeStream`
- desc: Binary serializer (Write)
- L47 _public member_ `uint8* const DataPtr = nullptr;`
- L48 _public member_ `const uint32_t DataSize = 0;`
- L50 _public member_ `uint32_t CurrentPos = 0;`
- L53 _public function_ `FStreamWrite(uint8* const InDataPtr, const uint32_t InDataSize) : DataPtr(InDataPtr), DataSize(InDataSize)`
- L57 _public prototype_ `virtual ~FStreamWrite() = default;`
- L59 _public function_ `virtual bool IsWriteStream() const`
- L65 _protected function_ `virtual FStreamWrite& SerializeData(void* InDataPtr, const uint32_t InDataSize) override`
- L70 _protected function_ `virtual FStreamWrite& SerializeData(const void* InDataPtr, const uint32_t InDataSize) override`
- L76 _private function_ `FStreamWrite& ImplWriteData(const void* InDataPtr, const uint32_t InDataSize)`

#### class `DataSerializer::FStreamRead`  
`class FStreamRead : public IDataContainerSerializeStream`  
_L95-140_
- inherits: `IDataContainerSerializeStream`
- desc: Binary serializer (Read)
- L98 _private member_ `const uint8* DataPtr = nullptr;`
- L99 _private member_ `const uint32_t DataSize = 0;`
- L101 _private member_ `uint32_t CurrentPos = 0;`
- L104 _public function_ `FStreamRead(const uint8* InDataPtr, const uint32_t InDataSize) : DataPtr(InDataPtr), DataSize(InDataSize)`
- L108 _public prototype_ `virtual ~FStreamRead() = default;`
- L110 _public function_ `virtual bool IsWriteStream() const`
- L116 _protected function_ `virtual FStreamRead& SerializeData(void* InDataPtr, const uint32_t InDataSize) override`
- L122 _private function_ `FStreamRead& ImplReadData(void* InDataPtr, const uint32_t InDataSize)`

#### struct `TDataOutput`  
`template<typename T> struct TDataOutput`  
_L147-191_
- desc: Data wrapper SDK.DLL->ExtApp
- L151 _public member_ `uint32_t DataSize = 0;` — Store structures as binary. And exchange like this Because the DLL versus the user application have differences in compilation, library version, memory alignment, etc.
- L152 _public member_ `uint8 DataPtr[DataSerializer::MaxStreamDataSize];`
- L154 _public function_ `TDataOutput(T& InOutData) : OutDataRef(InOutData)`
- L158 _public function_ `~TDataOutput()`
- L165 _public function_ `TDataOutput<T>& operator=(const T& InData)`
- L175 _public function_ `TDataOutput<T>& operator=(T& InData)`
- L184 _public function_ `TDataOutput<T>& operator*()`
- L190 _private member_ `T& OutDataRef;`

#### struct `TDataInput`  
`template<typename T> struct TDataInput`  
_L197-228_
- desc: Data wrapper ExtApp->SDK.DLL
- L201 _public member_ `uint8 DataPtr[DataSerializer::MaxStreamDataSize];` — Store structures as binary. And exchange like this Because the DLL versus the user application have differences in compilation, library version, memory alignment, etc.
- L202 _public member_ `uint32_t DataSize = 0;`
- L205 _public function_ `TDataInput(const T& InData)`
- L213 _public function_ `TDataInput(T& InData)`
- L220 _public function_ `inline T& Deserialize(T& OutData) const`

#### struct `TDataVariable`  
`template<typename T> struct TDataVariable`  
_L234-253_
- desc: Data deserializer TDataInput<InType> to InType
- L236 _public member_ `T OutData;`
- L238 _public function_ `TDataVariable(const TDataInput<T>& InData)`
- L244 _public function_ `T& operator*()`
- L249 _public function_ `const T& operator*() const`

#### Free symbols / members of external scopes

- L10 _typedef_ `using IDataContainerSerializeStream = ITextureShareCoreSerializeStream;`
- L15 _typedef_ `using IDataContainerSerializeStream = ITextureShareSDKSerializeStream;`
- L20 _namespace_ `namespace FPlatformMemory`
- L22 _typedef_ `typedef size_t SIZE_T;` (scope `FPlatformMemory`)
- L24 _function_ `inline void* Memcpy(void* Dest, const void* Src, SIZE_T Count)` (scope `FPlatformMemory`)
- L30 _macro_ `#define check(Cond)`
- L33 _namespace_ `namespace DataSerializer`
