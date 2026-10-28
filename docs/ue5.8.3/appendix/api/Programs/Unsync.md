# Programs / Unsync

- module root: `Source/Programs/Unsync`
- headers: 49; symbols: 1916
- symbol kinds: class=12, enum=24, enumerator=133, externvar=19, function=329, macro=34, member=641, namespace=52, prototype=442, struct=164, typedef=44, union=2, variable=20
- PrivateDependencyModuleNames: BLAKE3, CLI11, LibreSSL, fmt, http_parser, zstd

### `Source/Programs/Unsync/Private/UnsyncAuth.h` (Private)


#### struct `unsync::FAuthToken`  
`struct FAuthToken`  
_L21-30_
- L24 _public member_ `std::string Raw;` — Raw data acquired from authentication endpoint
- L27 _public member_ `std::string Access;` — Parsed data for convenience
- L28 _public member_ `std::string Refresh;`
- L29 _public member_ `int64 ExirationTime = 0;` — UNIX timestamp in seconds (0 if unknown)

#### struct `unsync::FOpenIdConfig`  
`struct FOpenIdConfig`  
_L33-39_
- desc: Data from /.well-known/openid-configuration
- L35 _public member_ `std::string AuthorizationEndpoint;`
- L36 _public member_ `std::string TokenEndpoint;`
- L37 _public member_ `std::string UserInfoEndpoint;`
- L38 _public member_ `std::string JwksUri;`

#### struct `unsync::FAuthDesc`  
`struct FAuthDesc`  
_L42-61_
- desc: Data from server configuration
- L45 _public member_ `std::string AuthServer;` — Mandatory configuration
- L46 _public member_ `std::string ClientId;`
- L49 _public member_ `std::string Audience;` — Optional configuration
- L50 _public member_ `std::string Callback;` — OAuth flow redirection URL
- L52 _public member_ `FPath TokenPath;` — Optional explicit storage location for the auth token
- L55 _public function_ `bool IsValid() const` — Check that mandatory fields have values
- L60 _public prototype_ `static FAuthDesc FromHelloResponse(const ProxyQuery::FHelloResponse& HelloResponse);`

#### struct `unsync::FAuthUserInfo`  
`struct FAuthUserInfo`  
_L79-87_
- L81 _public member_ `std::string Sub;`
- L82 _public member_ `std::string Name;`
- L83 _public member_ `std::string Nickname;`
- L84 _public member_ `std::string GivenName;`
- L85 _public member_ `std::string FamilyName;`
- L86 _public member_ `std::string Email;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace unsync`
- L17 _namespace_ `namespace ProxyQuery` (scope `unsync`)
- L64 _prototype_ `TResult<FOpenIdConfig> GetOpenIdConfig(const FAuthDesc& AuthDesc, uint32 RecvTimeoutSeconds);` (scope `unsync`) — Query OIDC/OAuth2 configuration via HTTP
- L71 _prototype_ `TResult<FAuthToken> Authenticate(const FAuthDesc& AuthDesc, uint32 RecvTimeoutSeconds, int32 RefreshThreshold = 300);` (scope `unsync`) — Perform the complete authentication flow: - Attempt use stored refresh token first - If refresh is not possible, use PKCE Authentication flow to get new tokens - Save refresh token in user directory for future use - Skips acquiring new token if remaining valid time is above RefreshThreshold (in seconds, 5 minutes by default)
- L75 _prototype_ `TResult<FAuthToken> AcquireAuthToken(const FAuthDesc& AuthDesc, uint32 RecvTimeoutSeconds, const FOpenIdConfig& OpenIdConfig);` (scope `unsync`)
- L76 _prototype_ `TResult<FAuthToken> RefreshAuthToken(const FAuthDesc& AuthDesc, uint32 RecvTimeoutSeconds, const FOpenIdConfig& OpenIdConfig, const FAuthToken& PreviousToken);` (scope `unsync`)
- L77 _prototype_ `TResult<FAuthToken> RefreshOrAcquireToken(const FAuthDesc& AuthDesc, uint32 RecvTimeoutSeconds, const FOpenIdConfig& OpenIdConfig, const FAuthToken& PreviousToken);` (scope `unsync`)
- L88 _prototype_ `TResult<FAuthUserInfo> GetUserInfo(FHttpConnection& HttpConnection, const FAuthDesc& AuthDesc, const FOpenIdConfig& OpenIdConfig, const FAuthToken& AuthToken);` (scope `unsync`)
- L90 _prototype_ `std::string GenerateTokenId(const FAuthDesc& RemoteDesc);` (scope `unsync`)
- L92 _prototype_ `bool SaveAuthToken(const FPath& Path, const FAuthToken& AuthToken);` (scope `unsync`)
- L93 _prototype_ `TResult<FAuthToken> LoadAuthToken(const FPath& Path);` (scope `unsync`)
- L95 _prototype_ `std::string SecureRandomBytesAsHexString(uint32 NumBytes);` (scope `unsync`)
- L96 _prototype_ `FHash256 HashSha256Bytes(const uint8* Data, uint64 Size);` (scope `unsync`)
- L97 _prototype_ `std::string EncodeBase64(const uint8* Data, uint64 Size);` (scope `unsync`)
- L98 _prototype_ `bool DecodeBase64(std::string_view Base64Data, FBuffer& Output);` (scope `unsync`)
- L100 _prototype_ `void TransformBase64VanillaToUrlSafe(std::string& Base64Vanilla);` (scope `unsync`)
- L101 _prototype_ `void TransformBase64UrlSafeToVanilla(std::string& Base64UrlSafe);` (scope `unsync`)
- L103 _prototype_ `std::string GetPKCECodeChallenge(std::string_view CodeVerifier);` (scope `unsync`)
- L105 _prototype_ `TResult<FAuthDesc> GetRemoteAuthDesc(const FRemoteDesc& RemoteDesc);` (scope `unsync`)
- L107 _prototype_ `int64 GetSecondsFromUnixEpoch();` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncBuffer.h` (Private)


#### struct `unsync::FBufferView`  
`struct FBufferView`  
_L11-15_
- L13 _public member_ `const uint8* Data = nullptr;`
- L14 _public member_ `uint64 Size = 0;`

#### struct `unsync::FMutBufferView`  
`struct FMutBufferView`  
_L17-29_
- L19 _public member_ `uint8* Data = nullptr;`
- L20 _public member_ `uint64 Size = 0;`
- L22 _public function_ `operator FBufferView() const`

#### class `unsync::FBuffer`  
`class FBuffer`  
_L31-102_
- L34 _public prototype_ `FBuffer() = default;`
- L35 _public prototype_ `explicit FBuffer(uint64 InitialSize);`
- L36 _public prototype_ `FBuffer(uint64 InitialSize, uint8 Value);`
- L37 _public prototype_ `FBuffer(std::initializer_list<uint8> Values);`
- L38 _public prototype_ `FBuffer(const FBuffer&) = delete;`
- L39 _public prototype_ `FBuffer& operator=(const FBuffer&) = delete;`
- L40 _public prototype_ `FBuffer(FBuffer&& Rhs);`
- L41 _public prototype_ `FBuffer& operator=(FBuffer&& Rhs);`
- L42 _public prototype_ `~FBuffer();`
- L44 _public prototype_ `void Reserve(uint64 RequiredCapacity);`
- L46 _public function_ `uint64 Capacity() const`
- L47 _public function_ `uint64 Size() const`
- L48 _public function_ `bool Empty() const`
- L50 _public function_ `uint8* Data()`
- L51 _public function_ `const uint8* Data() const`
- L53 _public function_ `uint8* begin()` — NOLINT
- L54 _public function_ `uint8* end()` — NOLINT
- L55 _public function_ `const uint8* begin() const` — NOLINT
- L56 _public function_ `const uint8* end() const` — NOLINT
- L58 _public prototype_ `void Append(const uint8* AppendData, uint64 AppendSize);`
- L59 _public prototype_ `void Append(const FBuffer& Other);`
- L60 _public prototype_ `void Append(const FBufferView& Other);`
- L61 _public function_ `void PushBack(uint8 Value)`
- L62 _public prototype_ `void Resize(uint64 NewSize);`
- L63 _public function_ `void Clear()`
- L64 _public prototype_ `void Shrink();`
- L66 _public function_ `uint8& operator[](size_t I)`
- L72 _public function_ `const uint8& operator[](size_t I) const`
- L78 _public function_ `FBufferView View() const`
- L79 _public function_ `FMutBufferView MutView()`
- L81 _public function_ `FBufferView View(uint64 ViewOffset, uint64 ViewSize) const`
- L87 _public function_ `FMutBufferView MutView(uint64 ViewOffset, uint64 ViewSize)`
- L93 _public function_ `operator FBufferView() const`
- L94 _public function_ `operator FMutBufferView()`
- L97 _private prototype_ `void EnsureCapacity(uint64 RequiredCapacity);`
- L99 _private member_ `uint8* Buffer = nullptr;`
- L100 _private member_ `uint64 BufferSize = 0;`
- L101 _private member_ `uint64 BufferCapacity = 0;`

#### struct `unsync::FBufferPool`  
`struct FBufferPool`  
_L112-126_
- L114 _public prototype_ `UNSYNC_DISALLOW_COPY_ASSIGN(FBufferPool);`
- L116 _public prototype_ `FBufferPool(uint64 InMaxBufferSize);`
- L117 _public prototype_ `~FBufferPool();`
- L119 _public prototype_ `FBuffer* Acquire();`
- L120 _public prototype_ `void Release(FBuffer* Buffer);`
- L122 _public member_ `uint64 MaxBufferSize;`
- L123 _public member_ `uint64 AllocatedBuffers = 0;`
- L124 _public member_ `std::mutex Mutex;`
- L125 _public member_ `std::vector<FBuffer*> Pool;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L106 _function_ `ReinterpretView(FBufferView BufferView)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncChunking.h` (Private)


#### struct `unsync::FComputeBlocksResult`  
`struct FComputeBlocksResult`  
_L10-14_
- L12 _public member_ `FGenericBlockArray Blocks;`
- L13 _public member_ `FGenericBlockArray MacroBlocks;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L16 _prototype_ `FComputeBlocksResult ComputeBlocks(FIOReader& Reader, const FComputeBlocksParams& Params);` (scope `unsync`)
- L17 _prototype_ `FComputeBlocksResult ComputeBlocks(const uint8* Data, uint64 Size, const FComputeBlocksParams& Params);` (scope `unsync`)
- L18 _prototype_ `FComputeBlocksResult ComputeBlocksVariable(FIOReader& Reader, const FComputeBlocksParams& Params);` (scope `unsync`)
- L20 _prototype_ `FGenericBlockArray ComputeBlocks(FIOReader& Reader, uint32 BlockSize, FAlgorithmOptions Algorithm);` (scope `unsync`)
- L21 _prototype_ `FGenericBlockArray ComputeBlocks(const uint8* Data, uint64 Size, uint32 BlockSize, FAlgorithmOptions Algorithm);` (scope `unsync`)
- L22 _prototype_ `FGenericBlockArray ComputeBlocksVariable(FIOReader& Reader, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdDiff.h` (Private)


#### struct `unsync::FCmdDiffOptions`  
`struct FCmdDiffOptions`  
_L10-19_
- L12 _public member_ `FPath Source;`
- L13 _public member_ `FPath Base;`
- L14 _public member_ `FPath Output;`
- L15 _public member_ `int32 CompressionLevel = 3;`
- L16 _public member_ `uint32 BlockSize = 0;`
- L17 _public member_ `EWeakHashAlgorithmID WeakHasher = EWeakHashAlgorithmID::BuzHash;`
- L18 _public member_ `EStrongHashAlgorithmID StrongHasher = EStrongHashAlgorithmID::Blake3_128;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L21 _prototype_ `int32 CmdDiff(const FCmdDiffOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdHash.h` (Private)


#### struct `unsync::FCmdHashOptions`  
`struct FCmdHashOptions`  
_L10-21_
- L12 _public member_ `FPath Input;`
- L13 _public member_ `FPath Output;`
- L14 _public member_ `bool bForce = false;`
- L15 _public member_ `bool bIncremental = false;`
- L16 _public member_ `bool bCompressPacks = false;`
- L17 _public member_ `bool bPackFiles = false;`
- L18 _public member_ `uint64 MaxFileSizeToPack = ~0ull;`
- L19 _public member_ `uint32 BlockSize = uint32(64_KB);`
- L20 _public member_ `FAlgorithmOptions Algorithm;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L23 _prototype_ `int32 CmdHash(const FCmdHashOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdInfo.h` (Private)


#### struct `unsync::FCmdInfoOptions`  
`struct FCmdInfoOptions`  
_L11-18_
- L13 _public member_ `FPath InputA;`
- L14 _public member_ `FPath InputB;`
- L15 _public member_ `bool bListFiles = false;`
- L16 _public member_ `const FSyncFilter* SyncFilter = nullptr;`
- L17 _public member_ `bool bDecode = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L20 _prototype_ `int32 CmdInfo(const FCmdInfoOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdLogin.h` (Private)


#### struct `unsync::FCmdLoginOptions`  
`struct FCmdLoginOptions`  
_L10-19_
- L12 _public member_ `FRemoteDesc Remote;`
- L13 _public member_ `bool bInteractive = false;` — TODO
- L14 _public member_ `bool bPrint = false;`
- L15 _public member_ `bool bPrintHttpHeader = false;`
- L16 _public member_ `bool bDecode = false;`
- L17 _public member_ `bool bForceRefresh = false;`
- L18 _public member_ `bool bQuick = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L21 _prototype_ `int32 CmdLogin(const FCmdLoginOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdMount.h` (Private)


#### struct `unsync::FCmdMountOptions`  
`struct FCmdMountOptions`  
_L9-12_
- L11 _public member_ `FPath Path;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L14 _prototype_ `int32 CmdMount(const FCmdMountOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdPack.h` (Private)


#### struct `unsync::FCmdPackOptions`  
`struct FCmdPackOptions`  
_L10-22_
- L12 _public member_ `FPath RootPath;`
- L13 _public member_ `FPath P4HavePath;` — optional
- L14 _public member_ `bool bRunP4Have = false;` — mutually exclusive with P4HavePath
- L15 _public member_ `FPath StorePath;` — optional
- L16 _public member_ `uint32 BlockSize = uint32(64_KB);`
- L17 _public member_ `FAlgorithmOptions Algorithm;`
- L21 _public member_ `std::string SnapshotName;` — Optional tag for this snapshot which can be used to reference it later using a human-friendly name. Overwrites the tag if it already exists.

#### struct `unsync::FCmdUnpackOptions`  
`struct FCmdUnpackOptions`  
_L26-36_
- L28 _public member_ `FPath OutputPath;`
- L29 _public member_ `FPath P4HaveOutputPath;` — extract embedded p4 have data into the specified file
- L30 _public member_ `FPath StorePath;`
- L31 _public member_ `std::string SnapshotName;`
- L32 _public member_ `bool bOutputFiles = true;` — set to false to skip unpack process for files (useful for extracting metadata)
- L33 _public member_ `bool bOutputRevisions = true;` — write [output]/.unsync/revisions.txt if manifest contains revision control data

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L24 _prototype_ `int32 CmdPack(const FCmdPackOptions& Options);` (scope `unsync`)
- L38 _prototype_ `int32 CmdUnpack(const FCmdUnpackOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdPatch.h` (Private)


#### struct `unsync::FCmdPatchOptions`  
`struct FCmdPatchOptions`  
_L10-15_
- L12 _public member_ `FPath Base;`
- L13 _public member_ `FPath Patch;`
- L14 _public member_ `FPath Output;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L17 _prototype_ `int32 CmdPatch(const FCmdPatchOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdPush.h` (Private)


#### struct `unsync::FCmdPushOptions`  
`struct FCmdPushOptions`  
_L11-15_
- L13 _public member_ `FPath Input;`
- L14 _public member_ `FRemoteDesc Remote;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L17 _prototype_ `int32 CmdPush(const FCmdPushOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdQuery.h` (Private)


#### struct `unsync::FCmdQueryOptions`  
`struct FCmdQueryOptions`  
_L12-18_
- L14 _public member_ `std::string Query;`
- L15 _public member_ `std::vector<std::string> Args;`
- L16 _public member_ `FPath OutputPath;`
- L17 _public member_ `FRemoteDesc Remote;`

#### struct `unsync::FMirrorInfo`  
`struct FMirrorInfo`  
_L22-29_
- L24 _public member_ `std::string Name;`
- L25 _public member_ `std::string Address;`
- L26 _public member_ `std::string Description;`
- L27 _public member_ `uint16 Port = UNSYNC_DEFAULT_PORT;`
- L28 _public member_ `double Ping = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace unsync`
- L20 _prototype_ `int32 CmdQuery(const FCmdQueryOptions& Options);` (scope `unsync`)
- L31 _prototype_ `TResult<FMirrorInfo> FindClosestMirror(const FRemoteDesc& Remote);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdSync.h` (Private)


#### struct `unsync::FCmdSyncOptions`  
`struct FCmdSyncOptions`  
_L13-38_
- L15 _public member_ `FAlgorithmOptions Algorithm;`
- L17 _public member_ `FPath Source;`
- L18 _public member_ `FPath Target;`
- L19 _public member_ `FPath SourceManifestOverride;`
- L20 _public member_ `FPath ScavengeRoot;`
- L21 _public member_ `uint32 ScavengeDepth = 5;`
- L22 _public member_ `uint64 BackgroundTaskMemoryBudget = 2_GB;`
- L24 _public member_ `std::vector<FPath> Overlays;`
- L26 _public member_ `FRemoteDesc Remote;`
- L27 _public member_ `FAuthDesc* AuthDesc = nullptr;`
- L29 _public member_ `bool bFullDifference = false;`
- L30 _public member_ `bool bFullSourceScan = false;`
- L31 _public member_ `bool bCleanup = false;`
- L33 _public member_ `bool bCheckAvailableSpace = true;`
- L35 _public member_ `bool bValidateTargetFiles = true;` — WARNING: turning this off is intended only for testing/profiling
- L37 _public member_ `FSyncFilter* Filter = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L40 _prototype_ `int32 CmdSync(const FCmdSyncOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCmdVerify.h` (Private)


#### struct `unsync::FCmdVerifyOptions`  
`struct FCmdVerifyOptions`  
_L7-10_
- L9 _public member_ `FPath Input;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace unsync`
- L12 _prototype_ `int32 CmdVerify(const FCmdVerifyOptions& Options);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCommon.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `# define UNSYNC_COMPILER_MSVC 1`
- L8 _macro_ `# define UNSYNC_COMPILER_MSVC 0`
- L12 _macro_ `# define UNSYNC_BREAK __debugbreak`
- L14 _macro_ `# define UNSYNC_BREAK __builtin_trap`
- L19 _macro_ `# define UNSYNC_ATTRIB_FORCEINLINE [[msvc::forceinline]]`
- L20 _macro_ `# define UNSYNC_ATTRIB_NOINLINE __declspec(noinline)`
- L21 _macro_ `# define UNSYNC_THIRD_PARTY_INCLUDES_START \`
- L26 _macro_ `# define UNSYNC_THIRD_PARTY_INCLUDES_END __pragma(warning(pop))` — __pragma(warning(disable : 4996))   deprecated
- L28 _macro_ `# define UNSYNC_ATTRIB_FORCEINLINE __attribute__((always_inline))`
- L29 _macro_ `# define UNSYNC_ATTRIB_NOINLINE __attribute__((noinline))`
- L35 _macro_ `# define UNSYNC_THIRD_PARTY_INCLUDES_END _Pragma("GCC diagnostic pop")`
- L45 _namespace_ `namespace unsync`
- L47 _typedef_ `using llu = long long unsigned;` (scope `unsync`)
- L49 _typedef_ `using uint8 = uint8_t;` (scope `unsync`)
- L50 _typedef_ `using uint16 = uint16_t;` (scope `unsync`)
- L51 _typedef_ `using uint32 = uint32_t;` (scope `unsync`)
- L52 _typedef_ `using uint64 = uint64_t;` (scope `unsync`)
- L54 _typedef_ `using int8 = int8_t;` (scope `unsync`)
- L55 _typedef_ `using int16 = int16_t;` (scope `unsync`)
- L56 _typedef_ `using int32 = int32_t;` (scope `unsync`)
- L57 _typedef_ `using int64 = int64_t;` (scope `unsync`)
- L59 _typedef_ `using FPath = std::filesystem::path;` (scope `unsync`)
- L60 _typedef_ `using FPathStringView = std::basic_string_view<FPath::value_type>;` (scope `unsync`)
- L62 _variable_ `static const char PATH_SEPARATOR = char(FPath::preferred_separator);` (scope `unsync`)
- L64 _macro_ `#define UNSYNC_DISALLOW_COPY_ASSIGN(T) \`
- L68 _macro_ `#define UNSYNC_CONCAT1(X, Y) X##Y`
- L69 _macro_ `#define UNSYNC_CONCAT(X, Y) UNSYNC_CONCAT1(X, Y)`
- L71 _macro_ `#define UNSYNC_WSTR(x) L## #x`
- L73 _macro_ `#define UNSYNC_UNUSED(x) (void)(x)`
- L77 _function_ `ClobberT(T& Object)` (scope `unsync`)
- L82 _macro_ `#define UNSYNC_CLOBBER(Object) ClobberT(Object)`
- L84 _macro_ `#define UNSYNC_ENUM_CLASS_FLAGS(T, S) \`
- L112 _function_ `EnumHasAllFlags(Enum Flags, Enum Contains)` (scope `unsync`)
- L119 _function_ `EnumHasAnyFlags(Enum Flags, Enum Contains)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCompression.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L10 _prototype_ `uint64 GetMaxCompressedSize(uint64 RawSize);` (scope `unsync`)
- L12 _prototype_ `FBuffer Compress(const uint8* Data, uint64 DataSize, int ZstdCompressionLevel = 3);` (scope `unsync`)
- L16 _prototype_ `uint64 CompressInto(FBufferView Input, FMutBufferView Output, int ZstdCompressionLevel = 3);` (scope `unsync`) — Compress input into pre-allocated buffer that's at least as large as indicated by GetMaxCompressedSize() Returns compressed data actual size.
- L18 _prototype_ `FBuffer Decompress(const uint8* Data, uint64 DataSize);` (scope `unsync`)
- L19 _prototype_ `FBuffer Decompress(const FBuffer& Buffer);` (scope `unsync`)
- L20 _prototype_ `bool Decompress(const uint8* InputData, uint64 InputDataSize, uint8* OutputData, uint64 OutputDataSize);` (scope `unsync`)
- L21 _prototype_ `bool Decompress(FBufferView Input, FMutBufferView Output);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncCore.h` (Private)


#### struct `unsync::FIdentityHash32`  
`struct FIdentityHash32`  
_L41-44_
- L43 _public function_ `uint32 operator()(uint32 X) const`

#### struct `unsync::FBlockStrongHash`  
`struct FBlockStrongHash`  
_L46-59_
- L48 _public function_ `uint32 operator()(const FBlock128& Block) const`
- L54 _public function_ `uint32 operator()(const FGenericBlock& Block) const`

#### struct `unsync::FBlockStrongHashEq`  
`struct FBlockStrongHashEq`  
_L61-66_
- L63 _public function_ `bool operator()(const FBlock128& A, const FBlock128& B) const`
- L65 _public function_ `bool operator()(const FGenericBlock& A, const FGenericBlock& B) const`

#### struct `unsync::FCopyCommand`  
`struct FCopyCommand`  
_L68-78_
- L70 _public member_ `uint64 Size = 0;`
- L71 _public member_ `uint64 SourceOffset = 0;`
- L72 _public member_ `uint64 TargetOffset = 0;`

#### struct `unsync::FCopyCommand::FCompareBySourceOffset`  
`struct FCompareBySourceOffset`  
_L74-77_
- L76 _public function_ `bool operator()(const FCopyCommand& A, const FCopyCommand& B) const`

#### struct `unsync::FNeedBlock`  
`struct FNeedBlock : FCopyCommand`  
_L80-83_
- inherits: `FCopyCommand`
- L82 _public member_ `FGenericHash Hash = {};`

#### struct `unsync::FReadSchedule`  
`struct FReadSchedule`  
_L85-89_
- L87 _public member_ `std::vector<FCopyCommand> Blocks;`
- L88 _public member_ `std::deque<uint64> Requests;` — unique block request indices sorted small to large

#### class `unsync::FBlockCache`  
`class FBlockCache`  
_L93-99_
- L96 _public member_ `FBuffer BlockData;`
- L97 _public member_ `THashMap<FHash128, FBufferView> BlockMap;` — Decompressed block data by hash
- L98 _public member_ `FTimeDuration InitDuration;` — How long it took to create the cache (i.e. download / read all the blocks)

#### struct `unsync::FNeedList`  
`struct FNeedList`  
_L112-117_
- L114 _public member_ `std::vector<FNeedBlock> Source;`
- L115 _public member_ `std::vector<FNeedBlock> Base;`
- L116 _public member_ `std::vector<FHash128> Sequence;`

#### struct `unsync::FPatchCommandList`  
`struct FPatchCommandList`  
_L119-124_
- L121 _public member_ `std::vector<FCopyCommand> Source;`
- L122 _public member_ `std::vector<FCopyCommand> Base;`
- L123 _public member_ `std::vector<FHash128> Sequence;`

#### struct `unsync::FNeedListSize`  
`struct FNeedListSize`  
_L126-131_
- L128 _public member_ `uint64 SourceBytes = 0;`
- L129 _public member_ `uint64 BaseBytes = 0;`
- L130 _public member_ `uint64 TotalBytes = 0;`

#### struct `unsync::FBlockSourceInfo`  
`struct FBlockSourceInfo`  
_L135-139_
- L138 _public member_ `uint64 TotalSize = 0;` — FPath  FilePath; // TODO: pass this in to allow filtering by name, etc.

#### struct `unsync::FComputeBlocksParams`  
`struct FComputeBlocksParams`  
_L143-159_
- L145 _public member_ `bool bNeedBlocks = true;`
- L146 _public member_ `uint32 BlockSize = uint32(64_KB);`
- L147 _public member_ `FAlgorithmOptions Algorithm;`
- L149 _public member_ `bool bNeedMacroBlocks = false;`
- L150 _public member_ `uint64 MacroBlockTargetSize = 3_MB;`
- L151 _public member_ `uint64 MacroBlockMaxSize = 5_MB;` — Maximum allowed by Jupiter
- L154 _public member_ `FOnBlockGenerated OnBlockGenerated;` — Callbacks may be called from worker threads
- L156 _public member_ `bool bAllowThreading = true;`
- L158 _public member_ `bool bAllowStreaming = GExperimentalStreaming;`

#### enum `unsync::EFileSyncStatus`  
`enum class EFileSyncStatus`  
_L166-176_
- L168 _public enumerator_ `Ok`
- L169 _public enumerator_ `ErrorUnknown`
- L170 _public enumerator_ `ErrorFullCopy`
- L171 _public enumerator_ `ErrorValidation`
- L172 _public enumerator_ `ErrorFinalRename`
- L173 _public enumerator_ `ErrorTargetFileCreate`
- L174 _public enumerator_ `ErrorBuildTargetFailed`
- L175 _public enumerator_ `ErrorInvalidParameters`

#### struct `unsync::FFileSyncTask`  
`struct FFileSyncTask`  
_L180-198_
- L182 _public member_ `const FFileManifest* SourceManifest = nullptr;`
- L183 _public member_ `const FFileManifest* BaseManifest = nullptr;`
- L184 _public member_ `FPath OriginalSourceFilePath;`
- L185 _public member_ `FPath ResolvedSourceFilePath;`
- L186 _public member_ `FPath BaseFilePath;`
- L187 _public member_ `FPath TargetFilePath;`
- L188 _public member_ `FPath RelativeFilePath;`
- L189 _public member_ `FNeedList NeedList;`
- L191 _public member_ `uint64 NeedBytesFromSource = 0;`
- L192 _public member_ `uint64 NeedBytesFromBase = 0;`
- L193 _public member_ `uint64 TotalSizeBytes = 0;`
- L195 _public member_ `uint32 SourceId = 0;`
- L197 _public function_ `bool IsBaseValid() const`

#### struct `unsync::FFileSyncResult`  
`struct FFileSyncResult`  
_L200-212_
- L202 _public member_ `EFileSyncStatus Status = EFileSyncStatus::ErrorUnknown;`
- L203 _public member_ `std::error_code SystemErrorCode = {};`
- L205 _public function_ `bool Succeeded() const`
- L207 _public prototype_ `FFileSyncResult& operator+=(const FBuildTargetResult& BuildTargetResult);`
- L209 _public member_ `uint64 SourceBytes = 0;`
- L210 _public member_ `uint64 BaseBytes = 0;`
- L211 _public member_ `uint64 InSituBytes = 0;`

#### struct `unsync::FSyncFileOptions`  
`struct FSyncFileOptions`  
_L214-226_
- L216 _public member_ `FAlgorithmOptions Algorithm;`
- L217 _public member_ `uint32 BlockSize = uint32(64_KB);`
- L219 _public member_ `FProxyPool* ProxyPool = nullptr;`
- L220 _public member_ `FBlockCache* BlockCache = nullptr;`
- L221 _public member_ `FScavengeDatabase* ScavengeDatabase = nullptr;`
- L223 _public member_ `bool bValidateTargetFiles = true;` — WARNING: turning this off is intended only for testing/profiling
- L225 _public member_ `ESourceType SourceType = (ESourceType)0;`

#### struct `unsync::FSyncDirectoryOptions`  
`struct FSyncDirectoryOptions`  
_L239-258_
- L241 _public member_ `ESourceType SourceType = (ESourceType)0;`
- L242 _public member_ `FPath Source;` — remote data location
- L243 _public member_ `FPath Target;` — output target location
- L244 _public member_ `FPath Base;` — base data location, which typically is the same as sync target
- L245 _public member_ `FPath ScavengeRoot;` — base directory where we may want to find reusable blocks
- L246 _public member_ `uint32 ScavengeDepth = 5;` — how deep to look for unsync manifests
- L247 _public member_ `std::vector<FPath> Overlays;` — extra source directories to overlay over primary (add extra files, replace existing files)
- L248 _public member_ `FPath SourceManifestOverride;` — force the manifest to be read from a specified file instead of source directory
- L249 _public member_ `FSyncFilter* SyncFilter = nullptr;` — filter callback for partial sync support
- L250 _public member_ `FProxyPool* ProxyPool = nullptr;`
- L251 _public member_ `bool bCleanup = false;` — whether to cleanup any files in the target directory that are not in the source manifest file
- L252 _public member_ `bool bValidateSourceFiles = true;` — whether to check that all source files declared in the manifest are present/valid
- L253 _public member_ `bool bValidateTargetFiles = true;` — WARNING: turning this off is intended only for testing/profiling
- L254 _public member_ `bool bFullDifference = true;` — whether to run full file difference algorithm, even when there is an existing manifest
- L255 _public member_ `bool bCheckAvailableSpace = true;` — whether to abort the sync if target path does not have enough available space
- L256 _public member_ `uint64 BackgroundTaskMemoryBudget = 2_GB;`
- L257 _public member_ `uint64 MaxFilesPerTask = 1000;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace unsync`
- L23 _externvar_ `extern bool GDryRun;` (scope `unsync`)
- L24 _externvar_ `extern bool GExperimental;` (scope `unsync`)
- L25 _externvar_ `extern bool GExperimentalStreaming;` (scope `unsync`)
- L91 _prototype_ `FReadSchedule BuildReadSchedule(const std::vector<FNeedBlock>& Blocks);` (scope `unsync`)
- L102 _function_ `ComputeSize(const std::vector<FNeedBlock>& NeedBlocks)` (scope `unsync`)
- L133 _prototype_ `FNeedListSize ComputeNeedListSize(const FNeedList& NeedList);` (scope `unsync`)
- L141 _typedef_ `using FOnBlockGenerated = std::function<void(const FGenericBlock& Block, const FBlockSourceInfo& Source, FBufferView Data)>;` (scope `unsync`)
- L162 _prototype_ `std::vector<FCopyCommand> OptimizeNeedList(const std::vector<FNeedBlock>& Input, uint64 MaxMergedBlockSize = 8_MB);` (scope `unsync`)
- L164 _prototype_ `bool IsSynchronized(const FNeedList& NeedList, const FGenericBlockArray& SourceBlocks);` (scope `unsync`)
- L178 _prototype_ `const wchar_t* ToString(EFileSyncStatus Status);` (scope `unsync`)
- L228 _prototype_ `FFileSyncResult SyncFile(const FPath& SourceFilePath, const FGenericBlockArray& SourceBlocks, FIOReader& BaseDataReader, const FPath& TargetFilePath, const FSyncFileOptions& Options);` (scope `unsync`)
- L234 _prototype_ `FFileSyncResult SyncFile(const FPath& SourceFilePath, const FPath& BaseFilePath, const FPath& TargetFilePath, const FSyncFileOptions& Options);` (scope `unsync`)
- L260 _prototype_ `bool SyncDirectory(const FSyncDirectoryOptions& SyncOptions);` (scope `unsync`)
- L263 _prototype_ `FBlock128 ToBlock128(const FGenericBlock& GenericBlock);` (scope `unsync`) — #wip-widehash -- temporary helper functions
- L264 _prototype_ `std::vector<FBlock128> ToBlock128(FGenericBlockArray& GenericBlocks);` (scope `unsync`)
- L268 _function_ `ValidateBlockListT(const std::vector<BlockType>& Blocks)` (scope `unsync`)
- L285 _prototype_ `bool ValidateTarget(FIOReader& Reader, const FNeedList& NeedList, EStrongHashAlgorithmID StrongHasher);` (scope `unsync`)
- L286 _prototype_ `bool ValidateTarget(FIOReader& Reader, const FGenericBlockArray& ValidationBlocks, EStrongHashAlgorithmID StrongHasher);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncDiff.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L10 _prototype_ `FNeedList DiffBlocks(const uint8* BaseData, uint64 BaseDataSize, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, const FGenericBlockArray& SourceBlocks);` (scope `unsync`)
- L17 _prototype_ `FNeedList DiffBlocksParallel(const uint8* BaseData, uint64 BaseDataSize, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, const FGenericBlockArray& SourceBlocks, uint64 BytesPerTask);` (scope `unsync`)
- L25 _prototype_ `FNeedList DiffBlocks(FIOReader& BaseDataReader, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, const FGenericBlockArray& SourceBlocks);` (scope `unsync`)
- L31 _prototype_ `FNeedList DiffBlocksParallel(FIOReader& BaseDataReader, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, const FGenericBlockArray& SourceBlocks, uint64 BytesPerTask);` (scope `unsync`)
- L38 _prototype_ `FNeedList DiffBlocksVariable(FIOReader& BaseDataReader, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, const FGenericBlockArray& SourceBlocks);` (scope `unsync`)
- L44 _prototype_ `FNeedList DiffManifestBlocks(const FGenericBlockArray& SourceBlocks, const FGenericBlockArray& BaseBlocks);` (scope `unsync`)
- L46 _prototype_ `FBuffer GeneratePatch(const uint8* BaseData, uint64 BaseDataSize, const uint8* SourceData, uint64 SourceDataSize, uint32 BlockSize, EWeakHashAlgorithmID WeakHasher, EStrongHashAlgorithmID StrongHasher, int32 CompressionLevel = 3);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncError.h` (Private)


#### enum `unsync::EErrorKind`  
`enum class EErrorKind`  
_L16-22_
- L18 _public enumerator_ `Unknown`
- L19 _public enumerator_ `App`
- L20 _public enumerator_ `System`
- L21 _public enumerator_ `Http`

#### struct `unsync::FError`  
`struct FError`  
_L24-31_
- L26 _public member_ `int32 Code = 0;`
- L27 _public member_ `EErrorKind Kind = EErrorKind::Unknown;`
- L28 _public member_ `std::wstring Context;`

#### struct `unsync::FEmpty`  
`struct FEmpty`  
_L71-73_

#### struct `unsync::TResult`  
`template<typename T = FEmpty, typename Et = FError> struct [[nodiscard]] TResult`  
_L76-131_
- L79 _public function_ `TResult(Et&& E) : DataOrError(std::forward<Et>(E))` — Implicit construction from Error type for convenience
- L81 _public function_ `explicit TResult(T&& Ok) : DataOrError(std::forward<T>(Ok))`
- L83 _public function_ `bool IsOk() const`
- L85 _public function_ `bool IsError() const`
- L87 _public function_ `const T* TryData() const`
- L88 _public function_ `const Et* TryError() const`
- L90 _public function_ `T* TryData()`
- L91 _public function_ `Et* TryError()`
- L93 _public function_ `const T& GetData() const`
- L99 _public function_ `const Et& GetError() const`
- L105 _public function_ `T& GetData()`
- L111 _public function_ `Et& GetError()`
- L117 _public function_ `const T* operator->() const`
- L123 _public function_ `const T& operator*() const`
- L130 _private member_ `std::variant<T, Et> DataOrError;`

#### struct `unsync::FAtomicError`  
`struct FAtomicError`  
_L154-174_
- L156 _public member_ `std::atomic_flag Flag;`
- L157 _public member_ `std::optional<FError> Data;`
- L159 _public function_ `operator bool() const`
- L161 _public function_ `bool Test() const`
- L162 _public function_ `bool Set(FError&& InData)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace unsync`
- L34 _function_ `SystemError(std::wstring&& Context, int32 Code = -1)` (scope `unsync`)
- L40 _function_ `AppError(std::wstring&& Context, int32 Code = -1)` (scope `unsync`)
- L46 _function_ `AppError(std::string&& Context, int32 Code = -1)` (scope `unsync`)
- L53 _function_ `HttpError(std::wstring&& Context, int32 Code)` (scope `unsync`)
- L59 _function_ `HttpError(std::string&& Context, int32 Code)` (scope `unsync`)
- L66 _function_ `HttpError(int32 Code)` (scope `unsync`)
- L135 _function_ `MoveError(TResult<T2, Te>& X)` (scope `unsync`)
- L142 _function_ `ResultOk(Tx Ok)` (scope `unsync`)
- L149 _function_ `ResultOk()` (scope `unsync`)
- L176 _macro_ `#define UNSYNC_RETURN_ON_ERROR(x) \`

### `Source/Programs/Unsync/Private/UnsyncFile.h` (Private)


#### enum `unsync::EFileMode`  
`enum class EFileMode : uint32`  
_L21-41_
- L22 _public enumerator_ `None = 0`
- L24 _public enumerator_ `Read = 1 << 0`
- L25 _public enumerator_ `Write = 1 << 1`
- L26 _public enumerator_ `Create = 1 << 2`
- L27 _public enumerator_ `Unbuffered = 1 << 3`
- L30 _public enumerator_ `IgnoreDryRun = 1 << 4` — Extended modes
- L33 _public enumerator_ `ReadOnly = Read` — Commonly used mode combinations
- L34 _public enumerator_ `ReadOnlyUnbuffered = Read | Unbuffered`
- L35 _public enumerator_ `CreateReadWrite = Read | Write | Create`
- L36 _public enumerator_ `CreateWriteOnly = Write | Create`
- L39 _public enumerator_ `CommonModeMask = Create | Read | Write | Unbuffered` — Masks
- L40 _public enumerator_ `ExtendedModeMask = ~CommonModeMask`

#### struct `unsync::FIOBuffer`  
`struct FIOBuffer`  
_L75-129_
- L77 _public prototype_ `static FIOBuffer Alloc(uint64 Size, const wchar_t* DebugName);`
- L78 _public prototype_ `FIOBuffer() = default;`
- L79 _public prototype_ `FIOBuffer(FIOBuffer&& Rhs);`
- L80 _public prototype_ `FIOBuffer(const FIOBuffer& Rhs) = delete;`
- L81 _public prototype_ `FIOBuffer& operator=(const FIOBuffer& Rhs) = delete;`
- L82 _public prototype_ `FIOBuffer& operator =(FIOBuffer&& Rhs);`
- L83 _public prototype_ `~FIOBuffer();`
- L85 _public function_ `uint8* GetData() const`
- L90 _public function_ `uint64 GetSize() const`
- L96 _public function_ `uint64 GetMemorySize() const`
- L102 _public prototype_ `void Clear();`
- L104 _public function_ `void SetDataRange(uint64 Offset, uint64 Size)`
- L111 _public function_ `void* GetMemory() const`
- L117 _public function_ `FBufferView GetBufferView() const`
- L118 _public function_ `FMutBufferView GetMutBufferView()`
- L121 _private member_ `static constexpr uint64 CANARY = 0x67aced0423000de5ull;`
- L123 _private member_ `uint64 Canary = CANARY;`
- L124 _private member_ `uint8* MemoryPtr = nullptr;`
- L125 _private member_ `uint64 MemorySize = 0;`
- L126 _private member_ `uint8* DataPtr = nullptr;`
- L127 _private member_ `uint64 DataSize = 0;`
- L128 _private member_ `const wchar_t* DebugName = nullptr;`

#### struct `unsync::FIOBase`  
`struct FIOBase`  
_L139-146_
- L141 _public prototype_ `virtual ~FIOBase() = default;`
- L142 _public prototype_ `virtual uint64 GetSize() = 0;`
- L143 _public prototype_ `virtual bool IsValid() = 0;`
- L144 _public prototype_ `virtual void Close() = 0;`
- L145 _public prototype_ `virtual int32 GetError() = 0;`

#### struct `unsync::FAsyncReader`  
`struct FAsyncReader`  
_L148-155_
- L150 _public prototype_ `virtual ~FAsyncReader() = default;`
- L151 _public prototype_ `virtual uint64 GetSize() = 0;`
- L152 _public prototype_ `virtual bool IsValid() = 0;`
- L153 _public prototype_ `virtual bool EnqueueRead(uint64 SourceOffset, uint64 Size, uint64 UserData, IOCallback Callback) = 0;` — NOT thread-safe
- L154 _public prototype_ `virtual void Flush() = 0;` — NOT thread-safe

#### struct `unsync::FIOReader`  
`struct FIOReader : virtual FIOBase`  
_L157-165_
- inherits: `FIOBase`
- L159 _public prototype_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 Size) = 0;`
- L161 _public prototype_ `virtual std::unique_ptr<FAsyncReader> CreateAsyncReader(uint32 MaxPipelineDepth = MAX_IO_PIPELINE_DEPTH);`
- L164 _public function_ `virtual FIOReader& ActualReader()` — Get the actual reader, eg. for a deferred reader that has an inner file reader.

#### struct `unsync::FDummyAsyncReader`  
`struct FDummyAsyncReader final : FAsyncReader`  
_L167-178_
- inherits: `FAsyncReader`
- L169 _public prototype_ `FDummyAsyncReader(FIOReader& InReader);`
- L171 _public function_ `virtual uint64 GetSize() override`
- L172 _public function_ `virtual bool IsValid() override`
- L173 _public prototype_ `virtual bool EnqueueRead(uint64 SourceOffset, uint64 Size, uint64 UserData, IOCallback Callback) override;`
- L174 _public function_ `virtual void Flush() override`
- L177 _private member_ `FIOReader& Inner;`

#### struct `unsync::FIOWriter`  
`struct FIOWriter : virtual FIOBase`  
_L180-188_
- inherits: `FIOBase`
- L182 _public prototype_ `virtual uint64 Write(const void* Data, uint64 DestOffset, uint64 Size) = 0;`
- L187 _public prototype_ `virtual int64 WriteFrom(FIOReader& Reader, const FCopyCommand& CopyCommand, FBufferView FileData, uint64* NumBytesClonedPtr = nullptr);` — Write file data from Reader. File-backed writers may use block cloning to copy the data by reference. FileData.Size must equal CopyCommand.Size. NumBytesClonedPtr may be null. Otherwise the number of bytes cloned is added to the target variable.

#### struct `unsync::FIOReaderWriter`  
`struct FIOReaderWriter : FIOReader, FIOWriter`  
_L190-192_
- inherits: `FIOReader,FIOWriter`

#### class `unsync::FFileReaderWriter`  
`template <typename InFileType> class FFileReaderWriter : public FIOReaderWriter`  
_L196-223_
- inherits: `FIOReaderWriter`
- desc: File reader/writer that uses CRTP to implement block-cloned copies.
- L199 _public typedef_ `using FileType = InFileType;`
- L201 _public function_ `virtual int64 WriteFrom(FIOReader& Reader, const FCopyCommand& CopyCommand, FBufferView FileData, uint64* NumBytesClonedPtr) override`

#### struct `unsync::FWindowsFile`  
`struct FWindowsFile : FFileReaderWriter<FWindowsFile>`  
_L226-268_
- inherits: `FFileReaderWriter<FWindowsFile>`
- L230 _public prototype_ `explicit FWindowsFile(const FPath& Filename, EFileMode Mode = EFileMode::ReadOnly, uint64 InSize = 0);`
- L231 _public prototype_ `~FWindowsFile();`
- L234 _public function_ `virtual uint64 GetSize() override` — IOBase
- L235 _public prototype_ `virtual bool IsValid() override;`
- L236 _public prototype_ `virtual void Close() override;`
- L237 _public function_ `virtual int32 GetError() override`
- L240 _public prototype_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override;` — IORead
- L241 _public prototype_ `virtual std::unique_ptr<FAsyncReader> CreateAsyncReader(uint32 MaxPipelineDepth = MAX_IO_PIPELINE_DEPTH) override;`
- L244 _public prototype_ `virtual uint64 Write(const void* InData, uint64 DestOffset, uint64 WriteSize) override;` — IOWrite
- L246 _public member_ `uint64 FileSize = 0;`
- L247 _public member_ `HANDLE FileHandle = INVALID_HANDLE_VALUE;`
- L248 _public member_ `int32 LastError = 0;`
- L250 _public member_ `FPath Filename;`
- L252 _public member_ `static constexpr uint32 UNBUFFERED_READ_ALIGNMENT = 4096;`
- L257 _private prototype_ `bool OpenFileHandle(EFileMode InMode);` — All internal methods expect the Mutex to be locked
- L260 _private member_ `EFileMode Mode;`
- L262 _private member_ `std::mutex Mutex;`
- L264 _private prototype_ `void FlushAsyncReaders();`
- L265 _private prototype_ `void AddAsyncReader(FWindowsAsyncFileReader* Reader);`
- L266 _private prototype_ `void RemoveAsyncReader(FWindowsAsyncFileReader* Reader);`
- L267 _private member_ `std::vector<FWindowsAsyncFileReader*> AsyncReaders;`

#### struct `unsync::FUnixFile`  
`struct FUnixFile : FFileReaderWriter<FUnixFile>`  
_L284-313_
- inherits: `FFileReaderWriter<FUnixFile>`
- L286 _public prototype_ `explicit FUnixFile(const FPath& InFilename, EFileMode InMode = EFileMode::ReadOnly, uint64 InSize = 0);`
- L287 _public prototype_ `~FUnixFile();`
- L290 _public function_ `virtual uint64 GetSize() override` — IOBase
- L291 _public function_ `virtual bool IsValid() override`
- L292 _public prototype_ `virtual void Close() override;`
- L293 _public function_ `virtual int32 GetError() override`
- L296 _public prototype_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override;` — IORead
- L299 _public prototype_ `virtual uint64 Write(const void* Indata, uint64 DestOffset, uint64 WriteSize) override;` — IOWrite
- L301 _public member_ `uint64 FileSize = 0;`
- L302 _public member_ `int32 LastError = 0;`
- L304 _public member_ `FPath Filename;`
- L306 _public member_ `static constexpr uint32 UNBUFFERED_READ_ALIGNMENT = 4096;`
- L311 _private member_ `EFileMode Mode = EFileMode::None;`
- L312 _private member_ `int FileDescriptor = -1;`

#### struct `unsync::FVectorStreamOut`  
`struct FVectorStreamOut`  
_L317-341_
- L319 _public function_ `FVectorStreamOut(FBuffer& Output) : Output(Output)`
- L321 _public function_ `void Write(const void* Data, uint64 Size)`
- L328 _public function_ `template<typename T> void WriteT(const T& Data)`
- L333 _public function_ `void WriteString(const std::string& S)`
- L340 _public member_ `FBuffer& Output;`

#### struct `unsync::FMemReader`  
`struct FMemReader : FIOReader`  
_L343-363_
- inherits: `FIOReader`
- L345 _public function_ `FMemReader(const FBuffer& Buffer) : FMemReader(Buffer.Data(), Buffer.Size())`
- L346 _public prototype_ `FMemReader(const uint8* InData, uint64 InDataSize);`
- L349 _public function_ `virtual uint64 GetSize() override` — IOBase
- L350 _public function_ `virtual bool IsValid() override`
- L351 _public function_ `virtual void Close() override`
- L356 _public function_ `virtual int32 GetError() override`
- L359 _public prototype_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override;` — IORead
- L361 _public member_ `const uint8* Data = nullptr;`
- L362 _public member_ `uint64 Size = 0;`

#### struct `unsync::FMemReaderWriter`  
`struct FMemReaderWriter : FMemReader, FIOReaderWriter`  
_L369-391_
- inherits: `FMemReader,FIOReaderWriter`
- L371 _public prototype_ `FMemReaderWriter(uint8* InData, uint64 InDataSize);`
- L372 _public function_ `FMemReaderWriter(FMutBufferView Buffer) : FMemReaderWriter(Buffer.Data, Buffer.Size)`
- L375 _public function_ `virtual void Close() override` — IOBase
- L382 _public prototype_ `virtual uint64 Write(const void* InData, uint64 DestOffset, uint64 WriteSize) override;` — IOWrite
- L385 _public function_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override` — IORead
- L390 _public member_ `uint8* DataRw = nullptr;`

#### struct `unsync::FNullReaderWriter`  
`struct FNullReaderWriter : FIOReaderWriter`  
_L396-423_
- inherits: `FIOReaderWriter`
- L402 _public function_ `explicit FNullReaderWriter(uint64 InDataSize) : DataSize(InDataSize)`
- L403 _public function_ `explicit FNullReaderWriter(FInvalid) : DataSize(0), bValid(false)`
- L406 _public function_ `virtual uint64 GetSize() override` — IOBase
- L407 _public function_ `virtual bool IsValid() override`
- L408 _public function_ `virtual void Close() override`
- L409 _public function_ `virtual int32 GetError() override`
- L412 _public function_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override` — IORead
- L419 _public function_ `virtual uint64 Write(const void* InData, uint64 DestOffset, uint64 WriteSize) override` — IOWrite
- L421 _public member_ `uint64 DataSize;`
- L422 _public member_ `bool bValid = true;`

#### struct `unsync::FNullReaderWriter::FInvalid`  
`struct FInvalid`  
_L398-400_

#### struct `unsync::FDeferredOpenReader`  
`struct FDeferredOpenReader : FIOReader`  
_L425-459_
- inherits: `FIOReader`
- L427 _public typedef_ `using FOpenCallback = std::function<std::unique_ptr<FIOReader>()>;`
- L429 _public function_ `FDeferredOpenReader(FOpenCallback InOpenCallback) : OpenCallback(InOpenCallback)`
- L432 _public function_ `virtual uint64 GetSize() override` — IOBase
- L433 _public function_ `virtual bool IsValid() override`
- L434 _public function_ `virtual void Close() override`
- L435 _public function_ `virtual int32 GetError() override`
- L438 _public function_ `virtual uint64 Read(void* Dest, uint64 SourceOffset, uint64 ReadSize) override` — IORead
- L442 _public function_ `virtual std::unique_ptr<FAsyncReader> CreateAsyncReader(uint32 MaxPipelineDepth = MAX_IO_PIPELINE_DEPTH) override`
- L446 _public function_ `virtual FIOReader& ActualReader() override`
- L448 _public function_ `FIOReader* GetOrOpenInner()`
- L457 _public member_ `FOpenCallback OpenCallback;`
- L458 _public member_ `std::unique_ptr<FIOReader> Inner;`

#### struct `unsync::FIOReaderStream`  
`struct FIOReaderStream`  
_L461-493_
- L463 _public function_ `FIOReaderStream(FIOReader& InInner) : Inner(InInner)`
- L465 _public function_ `uint64 Read(void* Dest, uint64 Size)`
- L472 _public function_ `void Seek(uint64 InOffset)`
- L478 _public function_ `uint64 Tell() const`
- L479 _public function_ `void Skip(uint64 NumBytes)`
- L481 _public function_ `bool IsValid() const`
- L484 _public function_ `template <typename T> inline uint64 ReadInto(T& Output)`
- L489 _public function_ `uint64 RemainingSize() const`
- L491 _public member_ `FIOReader& Inner;`
- L492 _public member_ `uint64 Offset = 0;`

#### struct `unsync::FFileAttributes`  
`struct FFileAttributes`  
_L500-508_
- L502 _public member_ `uint64 Mtime = 0;` — Windows file time (100ns ticks since 1601-01-01T00:00:00Z)
- L503 _public member_ `uint64 Size = 0;`
- L504 _public member_ `bool bDirectory = false;`
- L505 _public member_ `bool bValid = false;`
- L506 _public member_ `bool bReadOnly = false;`
- L507 _public member_ `bool bIsExecutable = false;`

#### struct `unsync::FFileAttributeCache`  
`struct FFileAttributeCache`  
_L510-515_
- L512 _public member_ `std::unordered_map<FPath::string_type, FFileAttributes> Map;`
- L514 _public prototype_ `const bool Exists(const FPath& Path) const;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace unsync`
- L17 _externvar_ `extern bool GForceBufferedFiles;` (scope `unsync`)
- L19 _variable_ `static constexpr uint32 MAX_IO_PIPELINE_DEPTH = 16;` (scope `unsync`)
- L42 _function_ `UNSYNC_ENUM_CLASS_FLAGS(EFileMode, uint32) inline bool IsReadOnly(EFileMode Mode)` (scope `unsync`)
- L58 _function_ `IsWriteOnly(EFileMode Mode)` (scope `unsync`)
- L64 _function_ `IsReadable(EFileMode Mode)` (scope `unsync`)
- L70 _function_ `IsWritable(EFileMode Mode)` (scope `unsync`)
- L132 _function_ `MakeShared(FIOBuffer&& Buffer)` (scope `unsync`)
- L137 _typedef_ `using IOCallback = std::function<void(FIOBuffer Buffer, uint64 SourceOffset, uint64 ReadSize, uint64 UserData)>;` (scope `unsync`)
- L272 _prototype_ `bool CloneFileRange(FWindowsFile& SourceFile, FWindowsFile& DestFile, const FCopyCommand& CopyCommand, FBufferView FileData = FBufferView(), uint64* NumBytesClonedPtr = nullptr);` (scope `unsync`) — Clone file blocks via ref counting if possible. FileData optionally supplies an in-memory view of the file contents that's used for writing unaligned bytes at the beginning and end of the cloned range.
- L274 _typedef_ `using FNativeFile = FWindowsFile;` (scope `unsync`)
- L282 _prototype_ `bool CloneFileRange(FUnixFile& SourceFile, FUnixFile& DestFile, const FCopyCommand& CopyCommand, FBufferView FileData = FBufferView(), uint64* NumReflinkedBytesPtr = nullptr);` (scope `unsync`) — Copy file data using in-kernel copy, which also provides block cloning (reflinking) on filesystems that support it. The `FileData` parameter is not used; it's only for API compatiblity with the Windows CloneFileRange() function.
- L314 _typedef_ `using FNativeFile = FUnixFile;` (scope `unsync`)
- L495 _prototype_ `FBuffer ReadFileToBuffer(const FPath& Filename);` (scope `unsync`)
- L496 _prototype_ `bool WriteBufferToFile(const FPath& Filename, const uint8* Data, uint64 Size, EFileMode FileMode = EFileMode::CreateWriteOnly);` (scope `unsync`)
- L497 _prototype_ `bool WriteBufferToFile(const FPath& Filename, const FBuffer& Buffer, EFileMode FileMode = EFileMode::CreateWriteOnly);` (scope `unsync`)
- L498 _prototype_ `bool WriteBufferToFile(const FPath& Filename, const std::string& Buffer, EFileMode FileMode = EFileMode::CreateWriteOnly);` (scope `unsync`)
- L518 _function_ `IsReadOnly(std::filesystem::perms Perms)` (scope `unsync`)
- L526 _function_ `IsExecutable(std::filesystem::perms Perms)` (scope `unsync`)
- L533 _prototype_ `uint64 BlockingReadLarge(FIOReader& Reader, uint64 Offset, uint64 Size, uint8* OutputBuffer, uint64 OutputBufferSize);` (scope `unsync`)
- L535 _prototype_ `FFileAttributes GetFileAttrib(const FPath& Path, FFileAttributeCache* AttribCache = nullptr);` (scope `unsync`)
- L536 _prototype_ `FFileAttributes GetCachedFileAttrib(const FPath& Path, FFileAttributeCache& AttribCache);` (scope `unsync`)
- L538 _prototype_ `bool SetFileMtime(const FPath& Path, uint64 Mtime, bool bAllowInDryRun = false);` (scope `unsync`)
- L539 _prototype_ `bool SetFileReadOnly(const FPath& Path, bool ReadOnly);` (scope `unsync`)
- L540 _prototype_ `bool SetFileExecutable(const FPath& Path, bool Executable);` (scope `unsync`)
- L541 _prototype_ `bool IsDirectory(const FPath& Path);` (scope `unsync`)
- L542 _prototype_ `bool PathExists(const FPath& Path);` (scope `unsync`)
- L543 _prototype_ `bool PathExists(const FPath& Path, std::error_code& OutErrorCode);` (scope `unsync`)
- L544 _prototype_ `bool CreateDirectories(const FPath& Path);` (scope `unsync`)
- L545 _prototype_ `bool EnsureDirectoryExists(const FPath& Path);` (scope `unsync`)
- L546 _prototype_ `bool FileRename(const FPath& From, const FPath& To, std::error_code& OutErrorCode);` (scope `unsync`)
- L547 _prototype_ `bool FileCopy(const FPath& From, const FPath& To, std::error_code& OutErrorCode);` (scope `unsync`)
- L548 _prototype_ `bool FileCopyOverwrite(const FPath& From, const FPath& To, std::error_code& OutErrorCode);` (scope `unsync`)
- L549 _prototype_ `bool FileRemove(const FPath& Path, std::error_code& OutErrorCode);` (scope `unsync`)
- L550 _prototype_ `FPath GetRelativePath(const FPath& Path, const FPath& Base);` (scope `unsync`)
- L551 _prototype_ `FPathStringView GetRelativePathView(const FPath& Path, const FPath& Base);` (scope `unsync`)
- L552 _prototype_ `std::error_code CopyFileIfNewer(const FPath& Source, const FPath& Target);` (scope `unsync`)
- L553 _prototype_ `bool IsNonCaseSensitiveFileSystem(const FPath& ExistingPath);` (scope `unsync`)
- L554 _prototype_ `bool IsCaseSensitiveFileSystem(const FPath& ExistingPath);` (scope `unsync`)
- L556 _prototype_ `void ConvertDirectorySeparatorsToNative(std::string& Path);` (scope `unsync`)
- L557 _prototype_ `void ConvertDirectorySeparatorsToNative(std::wstring& Path);` (scope `unsync`)
- L558 _prototype_ `void ConvertDirectorySeparatorsToUnix(std::string& Path);` (scope `unsync`)
- L559 _prototype_ `void ConvertDirectorySeparatorsToUnix(std::wstring& Path);` (scope `unsync`)
- L563 _prototype_ `uint64 GetAvailableDiskSpace(const FPath& Path);` (scope `unsync`) — Returns number of bytes that can be written to the given path. Returns ~0ull if the available space could not be determined.
- L565 _prototype_ `std::filesystem::recursive_directory_iterator RecursiveDirectoryScan(const FPath& Path);` (scope `unsync`)
- L566 _prototype_ `std::filesystem::directory_iterator DirectoryScan(const FPath& Path);` (scope `unsync`)
- L568 _prototype_ `uint64 ToWindowsFileTime(const std::filesystem::file_time_type& T);` (scope `unsync`)
- L569 _prototype_ `std::filesystem::file_time_type FromWindowsFileTime(uint64 Ticks);` (scope `unsync`)
- L570 _prototype_ `std::chrono::system_clock::time_point SystemTimeFromFileTime(std::filesystem::file_time_type FileTime);` (scope `unsync`)
- L573 _prototype_ `FFileAttributeCache CreateFileAttributeCache(const FPath& Root, const FSyncFilter* SyncFilter = nullptr);` (scope `unsync`)
- L578 _prototype_ `FPath MakeExtendedAbsolutePath(const FPath& InAbsolutePath);` (scope `unsync`) — Returns extended absolute path of a form \\?\D:\verylongpath or \\?\UNC\servername\verylongpath Expects an absolute path input. Returns original path on non-Windows. https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation
- L582 _prototype_ `FPath RemoveExtendedPathPrefix(const FPath& InPath);` (scope `unsync`) — Removes `\\?\` or `\\?\UNC\` prefix from a given path. Returns original path on non-Windows.
- L584 _typedef_ `using FPathFilterCallback = std::function<bool(const FPath& Path)>;` (scope `unsync`)
- L585 _prototype_ `void DeleteOldFilesInDirectory(const FPath& Path, uint32 MaxFilesToKeep, bool bAllowInDryRun = false, const FPathFilterCallback& Filter = {});` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncFilter.h` (Private)


#### struct `unsync::FSyncFilter`  
`struct FSyncFilter`  
_L10-32_
- L12 _public prototype_ `FSyncFilter() = default;`
- L15 _public prototype_ `void IncludeInSync(const std::wstring& CommaSeparatedWords);` — By default all files will be included, calling this will include only files containing these substrings
- L16 _public prototype_ `void ExcludeFromSync(const std::wstring& CommaSeparatedWords);`
- L17 _public prototype_ `void ExcludeFromCleanup(const std::wstring& CommaSeparatedWords);`
- L19 _public prototype_ `bool ShouldSync(const FPath& Filename) const;`
- L20 _public prototype_ `bool ShouldSync(const std::wstring& Filename) const;`
- L22 _public prototype_ `bool ShouldCleanup(const FPath& Filename) const;`
- L23 _public prototype_ `bool ShouldCleanup(const std::wstring& Filename) const;`
- L25 _public prototype_ `FPath Resolve(const FPath& Filename) const;`
- L27 _public member_ `std::vector<std::wstring> SyncIncludedWords;`
- L28 _public member_ `std::vector<std::wstring> SyncExcludedWords;` — any paths that contain these words will not be synced
- L29 _public member_ `std::vector<std::wstring> CleanupExcludedWords;` — any paths that contain these words will not be deleted after sync
- L31 _public member_ `std::vector<FDfsAlias> DfsAliases;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`

### `Source/Programs/Unsync/Private/UnsyncHash.h` (Private)


#### struct `unsync::THashValue`  
`template<size_t SizeBytes> struct THashValue`  
_L20-39_
- L22 _public member_ `alignas(uint32) uint8 Data[SizeBytes];`
- L24 _public function_ `bool operator==(const THashValue& Other) const`
- L26 _public function_ `bool operator!=(const THashValue& Other) const`
- L38 _public function_ `static constexpr size_t Size()`

#### struct `unsync::THashValue::Hasher`  
`struct Hasher`  
_L28-36_
- L30 _public function_ `uint32 operator()(const THashValue& Hash) const`

#### enum `unsync::EHashType`  
`enum class EHashType : uint8`  
_L45-54_
- L46 _public enumerator_ `Unknown`
- L47 _public enumerator_ `Unknown_128`
- L48 _public enumerator_ `Unknown_160`
- L49 _public enumerator_ `Unknown_256`
- L50 _public enumerator_ `MD5` — Standard 128 bit MD5
- L51 _public enumerator_ `Blake3_128` — Blake3 hash, truncated to 128 bits
- L52 _public enumerator_ `Blake3_160` — Blake3 hash, truncated to 160 bits, AKA Unreal Engine IoHash
- L53 _public enumerator_ `Blake3_256` — Blake3 hash, full 256 bits

#### struct `unsync::FGenericHash`  
`struct FGenericHash`  
_L85-151_
- desc: Generic hash type intended for runtime uses only. Serialized formats should always use Hash128/160/256.
- L87 _public member_ `alignas(uint32) uint8 Data[32];`
- L88 _public member_ `EHashType Type = EHashType::Unknown;`
- L90 _public function_ `size_t Size() const`
- L92 _public function_ `bool operator==(const FGenericHash& Other) const`
- L94 _public function_ `bool operator!=(const FGenericHash& Other) const`
- L96 _public function_ `static FGenericHash FromHash128(const FHash128& Other, EHashType Type)`
- L105 _public function_ `static FGenericHash FromMd5(const FHash128& Other)`
- L107 _public function_ `static FGenericHash FromBlake3_128(const FHash128& Other)` — NOLINT
- L112 _public function_ `static FGenericHash FromBlake3_160(const FHash160& Other)` — NOLINT
- L120 _public function_ `static FGenericHash FromBlake3_256(const FHash256& Other)` — NOLINT
- L128 _public function_ `FHash128 ToHash128() const`
- L135 _public function_ `FHash160 ToHash160() const`

#### struct `unsync::FGenericHash::Hasher`  
`struct Hasher`  
_L142-150_
- L144 _public function_ `uint32 operator()(const FGenericHash& Hash) const`

#### struct `unsync::FRollingChecksum`  
`struct FRollingChecksum`  
_L191-224_
- L193 _public member_ `uint16 A = 0;`
- L194 _public member_ `uint16 B = 0;`
- L195 _public member_ `uint64 Count = 0;`
- L197 _public function_ `void Update(const uint8* Data, uint64 Size)`
- L205 _public function_ `void Reset()`
- L207 _public function_ `uint32 Get() const`
- L209 _public function_ `void Add(uint8 X)`
- L217 _public function_ `void Sub(uint8 X)`

#### struct `unsync::FBuzHash`  
`struct FBuzHash`  
_L226-262_
- L228 _public member_ `static const uint32 TABLE[256];`
- L230 _public function_ `static inline uint32 Rol32(uint32 V, uint32 N)`
- L236 _public member_ `uint64 Count = 0;`
- L237 _public member_ `uint32 State = 0;`
- L239 _public function_ `void Update(const uint8* Data, uint64 Size)`
- L247 _public function_ `void Reset()`
- L249 _public function_ `uint32 Get() const`
- L251 _public function_ `void Add(uint8 X)`
- L257 _public function_ `void Sub(uint8 X)`

#### class `unsync::FBlake3Hasher`  
`class alignas(8) FBlake3Hasher`  
_L302-314_
- L305 _public prototype_ `FBlake3Hasher();`
- L307 _public prototype_ `void Update(const void* Data, size_t Size);`
- L308 _public prototype_ `FHash256 Finalize();`
- L309 _public prototype_ `void Reset();`
- L312 _private member_ `static constexpr size_t STATE_SIZE = 1912;`
- L313 _private member_ `uint8 State[STATE_SIZE];`

#### class `unsync::FMD5Hasher`  
`class alignas(8) FMD5Hasher`  
_L316-328_
- L319 _public prototype_ `FMD5Hasher();`
- L321 _public prototype_ `void Update(const void* Data, size_t Size);`
- L322 _public prototype_ `FHash128 Finalize();`
- L323 _public prototype_ `void Reset();`
- L326 _private member_ `static constexpr size_t STATE_SIZE = 88;`
- L327 _private member_ `uint8 State[STATE_SIZE];`

#### class `unsync::FStrongHasher`  
`class FStrongHasher`  
_L330-343_
- L333 _public function_ `FStrongHasher(EStrongHashAlgorithmID InAlgorithm) : Algorithm(InAlgorithm)`
- L335 _public prototype_ `void Reset();`
- L336 _public prototype_ `void Update(const void* Data, uint64 Size);`
- L337 _public prototype_ `FGenericHash Finalize();`
- L340 _private member_ `const EStrongHashAlgorithmID Algorithm;`
- L341 _private member_ `FBlake3Hasher Blake3;`
- L342 _private member_ `FMD5Hasher MD5;`

#### struct `std::hash`  
`template<size_t SizeBytes> struct hash<unsync::THashValue<SizeBytes>>`  
_L371-378_
- L373 _public function_ `size_t operator()(const unsync::THashValue<SizeBytes>& Hash) const`
- L383 _public function_ `size_t operator()(const unsync::FGenericHash& Hash) const`

#### struct `std::hash`  
`template<> struct hash<unsync::FGenericHash>`  
_L381-389_
- L373 _public function_ `size_t operator()(const unsync::THashValue<SizeBytes>& Hash) const`
- L383 _public function_ `size_t operator()(const unsync::FGenericHash& Hash) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace unsync`
- L41 _typedef_ `using FHash128 = THashValue<16>;` (scope `unsync`)
- L42 _typedef_ `using FHash160 = THashValue<20>;` (scope `unsync`)
- L43 _typedef_ `using FHash256 = THashValue<32>;` (scope `unsync`)
- L57 _function_ `GetHashSize(EHashType Type)` (scope `unsync`)
- L81 _prototype_ `EHashType ToHashType(EStrongHashAlgorithmID StrongHasher);` (scope `unsync`)
- L153 _prototype_ `bool ParseHashFromHexString(EStrongHashAlgorithmID StrongHasher, std::string_view HexString, FGenericHash& Output);` (scope `unsync`)
- L154 _prototype_ `bool ParseUint64FromHexString(std::string_view HexString, uint64& Output);` (scope `unsync`)
- L157 _function_ `ToHash160(const FHash256& Other)` (scope `unsync`)
- L165 _function_ `ToHash128(const FHash256& Other)` (scope `unsync`)
- L173 _function_ `ToHash128(const FHash160& Other)` (scope `unsync`)
- L181 _function_ `MurmurMix(uint32 X)` (scope `unsync`)
- L265 _prototype_ `template<typename HashResultType> HashResultType HashBlake3Bytes(const uint8* Data, uint64 Size);` (scope `unsync`)
- L269 _function_ `HashBlake3String(std::string_view Str)` (scope `unsync`)
- L276 _function_ `HashBlake3String(const char* Str)` (scope `unsync`)
- L283 _function_ `HashBlake3String(const wchar_t* Str)` (scope `unsync`)
- L290 _function_ `HashBlake3String(const std::string& Str)` (scope `unsync`)
- L297 _function_ `HashBlake3String(const std::wstring& Str)` (scope `unsync`)
- L345 _prototype_ `FHash128 HashMd5Bytes(const uint8* Data, uint64 Size);` (scope `unsync`)
- L347 _prototype_ `FGenericHash HashBytes(const uint8* Data, uint64 Size, EHashType HashType);` (scope `unsync`)
- L349 _prototype_ `FHash128 ComputeHash128(const uint8* Data, uint64 Size, EStrongHashAlgorithmID Algorithm);` (scope `unsync`)
- L350 _prototype_ `FGenericHash ComputeHash(const uint8* Data, uint64 Size, EStrongHashAlgorithmID Algorithm);` (scope `unsync`)
- L352 _prototype_ `FGenericHash ComputeHash(const FBuffer& Buffer, EStrongHashAlgorithmID Algorithm);` (scope `unsync`)
- L353 _prototype_ `FGenericHash ComputeHash(const FBufferView& Buffer, EStrongHashAlgorithmID Algorithm);` (scope `unsync`)
- L356 _function_ `ToHash128(const FHash128& X)` (scope `unsync`)
- L362 _function_ `ToHash128(const FGenericHash& X)` (scope `unsync`)
- L369 _namespace_ `namespace std`

### `Source/Programs/Unsync/Private/UnsyncHashTable.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L13 _typedef_ `using THashMap = ska::flat_hash_map<K, V, Hash, Eq>;` (scope `unsync`) — using THashMap = std::unordered_map<K,V,Hash,Eq>;
- L17 _typedef_ `using THashSet = ska::flat_hash_set<K, Hash, Eq>;` (scope `unsync`) — using THashSet = std::unordered_set<K, Hash, Eq>;

### `Source/Programs/Unsync/Private/UnsyncHorde.h` (Private)


#### struct `unsync::FHordeProtocolImpl`  
`struct FHordeProtocolImpl : FRemoteProtocolBase`  
_L14-33_
- inherits: `FRemoteProtocolBase`
- L16 _public prototype_ `FHordeProtocolImpl(const FRemoteDesc& InRemoteDesc, const FBlockRequestMap* InRequestMap, FProxyPool& InProxyPool);`
- L18 _public function_ `virtual bool IsValid() const`
- L19 _public function_ `virtual void Invalidate()`
- L21 _public prototype_ `virtual FDownloadResult Download(const TArrayView<FNeedBlock> NeedBlocks, const FBlockDownloadCallback& CompletionCallback);`
- L22 _public prototype_ `virtual TResult<FDirectoryManifest> DownloadManifest(std::string_view ManifestName);`
- L24 _public prototype_ `static TResult<ProxyQuery::FHelloResponse> QueryHello(FHttpConnection& HttpConnection);`
- L25 _public prototype_ `static TResult<ProxyQuery::FDirectoryListing> QueryListDirectory(FHttpConnection& Connection, const FAuthDesc* AuthDesc, const std::string& Path);`
- L29 _public member_ `FProxyPool& ProxyPool;`
- L30 _public member_ `bool bValid = true;`
- L32 _public prototype_ `FDownloadResult DownloadArtifactBlobs(std::string_view ArtifactPath, const TArrayView<FNeedBlock> NeedBlocks, const FBlockDownloadCallback& CompletionCallback);`

#### struct `unsync::FHordeArtifactQuery`  
`struct FHordeArtifactQuery`  
_L36-52_
- L38 _public member_ `std::string Type;`
- L39 _public member_ `std::string Id;`
- L40 _public member_ `std::string Change;`
- L41 _public member_ `std::vector<std::string> Keys;`
- L43 _public member_ `uint32 MaxResults = 1000000;`
- L46 _public member_ `std::string Format;` — Template to use for formatting results, e.g.: `{StreamName}.{BuildName}/{Platform}#{Id}`
- L49 _public member_ `std::vector<std::string> Parts;` — Query parts, delimited by directory separator character
- L51 _public prototype_ `static TResult<FHordeArtifactQuery> FromString(std::string_view Str);`

#### struct `unsync::FHordeArtifactEntry`  
`struct FHordeArtifactEntry`  
_L54-63_
- L56 _public member_ `std::string Change;`
- L57 _public member_ `std::string Id;`
- L58 _public member_ `std::string Name;`
- L59 _public member_ `std::string Description;`
- L60 _public member_ `std::string StreamId;`
- L61 _public member_ `std::vector<std::string> Keys;`
- L62 _public member_ `std::vector<std::string> Metadata;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L65 _prototype_ `bool RequestPathLooksLikeHordeArtifact(std::string_view RequestPath);` (scope `unsync`)
- L67 _prototype_ `TResult<FDirectoryManifest> DecodeHordeManifestJson(const char* JsonString, std::string_view ArtifactRoot);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncHttp.h` (Private)


#### enum `unsync::EHttpContentType`  
`enum class EHttpContentType`  
_L20-29_
- L22 _public enumerator_ `Unknown`
- L23 _public enumerator_ `Text_Html`
- L24 _public enumerator_ `Text_Plain`
- L25 _public enumerator_ `Application_OctetStream`
- L26 _public enumerator_ `Application_Json`
- L27 _public enumerator_ `Application_WWWFormUrlEncoded`
- L28 _public enumerator_ `Application_UECB` — Unreal Engine Compact Binary

#### enum `unsync::EHttpMethod`  
`enum class EHttpMethod`  
_L31-37_
- L33 _public enumerator_ `GET`
- L34 _public enumerator_ `HEAD`
- L35 _public enumerator_ `POST`
- L36 _public enumerator_ `PUT`

#### struct `unsync::FHttpRequest`  
`struct FHttpRequest`  
_L42-53_
- L44 _public member_ `EHttpMethod Method = EHttpMethod::GET;`
- L45 _public member_ `std::string_view Url = {};`
- L46 _public member_ `std::string_view CustomHeaders = {};`
- L47 _public member_ `std::string_view BearerToken = {};`
- L49 _public member_ `EHttpContentType PayloadContentType = EHttpContentType::Unknown;`
- L50 _public member_ `FBufferView Payload = {};`
- L52 _public member_ `EHttpContentType AcceptContentType = EHttpContentType::Unknown;`

#### struct `unsync::FHttpResponse`  
`struct FHttpResponse`  
_L55-72_
- L57 _public member_ `FBuffer Buffer;` — TODO: use pooled IOBuffer
- L58 _public member_ `uint64 ContentLength = 0;`
- L59 _public member_ `int32 Code = 0;`
- L61 _public member_ `EHttpContentType ContentType = EHttpContentType::Unknown;`
- L63 _public member_ `std::vector<std::pair<std::string, std ::string>> Headers;`
- L65 _public member_ `bool bConnectionEncrypted = false;`
- L67 _public function_ `bool Success() const`
- L69 _public function_ `std::string_view AsStringView() const`
- L71 _public prototype_ `std::string_view FindHeader(const std::string_view Name) const;`

#### struct `unsync::FHttpConnection`  
`struct FHttpConnection`  
_L74-119_
- L76 _public function_ `FHttpConnection(const std::string_view InHostAddress, uint16 InPort, uint32 InRecvTimeoutSeconds) : FHttpConnection(InHostAddress, InPort, ETlsRequirement::None, FTlsClientSettings{}, InRecvTimeoutSeconds)`
- L77 _public prototype_ `FHttpConnection(const std::string_view InHostAddress, uint16 InPort, ETlsRequirement InTlsRequirement, const FTlsClientSettings& InTlsSettings, uint32 InRecvTimeoutSeconds);`
- L78 _public prototype_ `FHttpConnection(const FHttpConnection& Other);`
- L80 _public prototype_ `[[nodiscard]] static FHttpConnection CreateDefaultHttp(const std::string_view InHostAddress, uint16 Port = 80, uint32 RecvTimeoutSeconds = 0);`
- L81 _public prototype_ `[[nodiscard]] static FHttpConnection CreateDefaultHttps(const std::string_view InHostAddress, uint16 Port = 443, uint32 RecvTimeoutSeconds = 0);`
- L82 _public prototype_ `[[nodiscard]] static FHttpConnection CreateDefaultHttps(const FRemoteDesc& RemoteDesc);`
- L84 _public prototype_ `bool Open();`
- L85 _public prototype_ `void Close();`
- L87 _public member_ `std::string HostAddress;`
- L88 _public member_ `uint16 HostPort = 80;`
- L90 _public member_ `bool bKeepAlive = true;`
- L92 _public member_ `ETlsRequirement TlsRequirement = ETlsRequirement::None;`
- L93 _public member_ `bool bTlsVerifySubject = true;`
- L94 _public member_ `std::string TlsSubject;`
- L95 _public member_ `bool bTlsVerifyCertificate = true;`
- L96 _public member_ `std::shared_ptr<FBuffer> TlsCacert;`
- L98 _public member_ `uint32 RecvTimeoutSeconds = 0;`
- L100 _public member_ `uint64 NumActiveRequests = 0;`
- L103 _public member_ `std::deque<FHttpResponse> ResponseQueue;` — TODO: use single memory allocation for multiple reponse objects (perhaps a ring buffer)
- L105 _public member_ `EHttpMethod Method = EHttpMethod::GET;`
- L107 _public member_ `FTimePoint LastUsed = {};`
- L109 _public function_ `FSocketBase& GetSocket()`
- L115 _public function_ `bool IsEncrypted() const`
- L118 _protected member_ `std::unique_ptr<FSocketBase> Socket;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace unsync`
- L39 _typedef_ `using FHttpMessageCallback = std::function<void(FHttpResponse&& Response)>;` (scope `unsync`)
- L40 _typedef_ `using FHttpChunkCallback = std::function<void(FHttpResponse& Response)>;` (scope `unsync`)
- L121 _prototype_ `const char* HttpStatusToString(int32 Code);` (scope `unsync`)
- L125 _prototype_ `FHttpResponse HttpRequest(FHttpConnection& Connection, const FHttpRequest& Request, FHttpChunkCallback ChunkCallback = {});` (scope `unsync`)
- L128 _function_ `HttpRequest(FHttpConnection& Connection, EHttpMethod Method, std::string_view Url, EHttpContentType ContentType, FBufferView Payload, std::string_view CustomHeaders = {}, std::string_view BearerToken = {})` (scope `unsync`)
- L149 _function_ `HttpRequest(FHttpConnection& Connection, EHttpMethod Method, std::string_view Url, std::string_view CustomHeaders = {}, std::string_view BearerToken = {})` (scope `unsync`)
- L163 _prototype_ `FHttpResponse HttpRequest(const FRemoteDesc& RemoteDesc, EHttpMethod Method, std::string_view RequestUrl, std::string_view BearerToken = {});` (scope `unsync`)
- L168 _prototype_ `FHttpResponse HttpRequest(const FRemoteDesc& RemoteDesc, EHttpMethod Method, std::string_view RequestUrl, EHttpContentType PayloadContentType, FBufferView Payload, std::string_view BearerToken = {});` (scope `unsync`)
- L177 _prototype_ `bool HttpRequestBegin(FHttpConnection& Connection, const FHttpRequest& Request);` (scope `unsync`)
- L179 _prototype_ `FHttpResponse HttpRequestEnd(FHttpConnection& Connection, FHttpChunkCallback ChunkCallback = {});` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncJupiter.h` (Private)


#### struct `unsync::FJupiterProtocolImpl`  
`struct FJupiterProtocolImpl : FRemoteProtocolBase`  
_L36-53_
- inherits: `FRemoteProtocolBase`
- L38 _public prototype_ `FJupiterProtocolImpl(const FRemoteDesc& InSettings, const FBlockRequestMap* InRequestMap, std::string_view HttpHeaders);`
- L39 _public prototype_ `virtual bool IsValid() const override;`
- L40 _public prototype_ `virtual TResult<FDirectoryManifest> DownloadManifest(std::string_view ManifestName) override;`
- L41 _public prototype_ `virtual FDownloadResult Download(const TArrayView<FNeedBlock> NeedBlocks, const FBlockDownloadCallback& CompletionCallback) override;`
- L42 _public prototype_ `virtual void Invalidate() override;`
- L43 _public prototype_ `virtual bool Contains(const FDirectoryManifest& Manifest) override;`
- L45 _public member_ `FHttpConnection Connection;`
- L46 _public member_ `std::string HttpHeaders;` — TODO: store this in the HttpConnection instead
- L47 _public member_ `FRemoteDesc RemoteDesc;`
- L49 _public member_ `bool bConnected = false;`
- L50 _public member_ `uint64 ErrorsSinceLastSuccess = 0;`
- L51 _public member_ `uint64 TotalErrors = 0;`
- L52 _public member_ `uint64 TotalRequests = 0;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace unsync`
- L21 _prototype_ `TResult<uint64> JupiterPush(const FDirectoryManifest& Manifest, const FRemoteDesc& RemoteDesc, const FTlsClientSettings& TlsSettings);` (scope `unsync`) — Returns number of blocks pushed
- L23 _prototype_ `TResult<> JupiterPutRawBlob(FHttpConnection& Connection, const std::string_view BaseUrl, const std::string_view HttpHeaders, FBufferView Blob, const FHash160& Hash);` (scope `unsync`)
- L29 _prototype_ `TResult<FBuffer> JupiterGetRawBlob(FHttpConnection& Connection, const std::string_view, const std::string_view HttpHeaders, const FHash160& Hash);` (scope `unsync`)
- L34 _prototype_ `TResult<> JupiterCheckAccess(FHttpConnection& Connection, std::string_view JupiterNamespace, std::string_view HttpHeaders);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncLog.h` (Private)


#### struct `unsync::FLogIndentScope`  
`struct FLogIndentScope`  
_L21-39_
- L23 _public member_ `uint32 Next = 0;`
- L24 _public member_ `uint32 Prev = 0;`
- L25 _public function_ `FLogIndentScope(uint32 InN = 2, bool bInOverride = false) : Next(InN), Prev(GLogIndent)`
- L36 _public function_ `~FLogIndentScope()`
- L37 _public prototype_ `FLogIndentScope(const FLogIndentScope&) = delete;`
- L38 _public prototype_ `FLogIndentScope& operator=(const FLogIndentScope&) = delete;`

#### struct `unsync::FLogVerbosityScope`  
`struct FLogVerbosityScope`  
_L41-49_
- L43 _public member_ `bool bNext = false;`
- L44 _public member_ `bool bPrev = false;`
- L45 _public function_ `FLogVerbosityScope(bool InNext) : bNext(InNext), bPrev(GLogVerbose)`
- L46 _public function_ `~FLogVerbosityScope()`
- L47 _public prototype_ `FLogVerbosityScope(const FLogVerbosityScope&) = delete;`
- L48 _public prototype_ `FLogVerbosityScope& operator=(const FLogVerbosityScope&) = delete;`

#### struct `unsync::FLogFileScope`  
`struct FLogFileScope`  
_L51-55_
- L53 _public prototype_ `FLogFileScope(const wchar_t* Filename);`
- L54 _public prototype_ `~FLogFileScope();`

#### struct `unsync::FLogFlushScope`  
`struct FLogFlushScope`  
_L57-60_
- L59 _public prototype_ `~FLogFlushScope();`

#### enum `unsync::ELogLevel`  
`enum class ELogLevel`  
_L62-73_
- L64 _public enumerator_ `Error = 0`
- L65 _public enumerator_ `Warning = 1`
- L66 _public enumerator_ `Info = 2`
- L67 _public enumerator_ `Debug = 3`
- L68 _public enumerator_ `Trace = 4`
- L72 _public enumerator_ `MachineReadable = 5` — Special log level to signify output that's intended to be machine-readable. This is always written to stdout, while other modes may be written to stderr in some cases.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L9 _externvar_ `extern thread_local bool GLogVerbose;` (scope `unsync`)
- L10 _externvar_ `extern bool GLogVeryVerbose;` (scope `unsync`)
- L11 _externvar_ `extern bool GLogSilent;` (scope `unsync`)
- L12 _externvar_ `extern bool GBreakOnError;` (scope `unsync`)
- L13 _externvar_ `extern bool GBreakOnWarning;` (scope `unsync`)
- L14 _externvar_ `extern thread_local uint32 GLogIndent;` (scope `unsync`)
- L15 _externvar_ `extern bool GLogProgress;` (scope `unsync`) — Whether to output @progress and @status markers to stdout
- L16 _externvar_ `extern bool GLogMachineReadable;` (scope `unsync`) — Whether output is intended for other programs rather than humans
- L17 _externvar_ `extern bool GLogStdOut;` (scope `unsync`) — Whether to send all output to stdout (disabling stderr)
- L75 _prototype_ `void LogFlush();` (scope `unsync`)
- L77 _prototype_ `void LogPrintf(ELogLevel Level, const wchar_t* Str, ...);` (scope `unsync`)
- L78 _prototype_ `void LogError(const FError& E, std::wstring ExtraContext = {});` (scope `unsync`)
- L80 _prototype_ `void LogProgress(const wchar_t* ItemName, uint64 Current, uint64 Total);` (scope `unsync`)
- L81 _prototype_ `void LogStatus(const wchar_t* ItemName, const wchar_t* Status);` (scope `unsync`)
- L84 _function_ `LogGlobalProgress(uint64 Current, uint64 Total)` (scope `unsync`)
- L89 _function_ `LogGlobalStatus(const wchar_t* Status)` (scope `unsync`)
- L94 _prototype_ `void SetCrashDumpPath(const FPath& Path);` (scope `unsync`)
- L95 _prototype_ `bool GetCrashDumpPath(FPath& OutPath);` (scope `unsync`)
- L96 _prototype_ `bool LogWriteCrashDump(void* ExceptionPointers);` (scope `unsync`)
- L98 _prototype_ `void LogSaveCommandLineUtf8(int Argc, char** Argv);` (scope `unsync`)
- L100 _macro_ `#define UNSYNC_LOG_INDENT FLogIndentScope UNSYNC_CONCAT(log_indent_, __LINE__);`
- L101 _macro_ `#define UNSYNC_LOG_INDENT_N(N) FLogIndentScope UNSYNC_CONCAT(log_indent_, __LINE__)(N);`
- L103 _macro_ `#define UNSYNC_LOG(text, ...) \`
- L107 _macro_ `#define UNSYNC_WARNING(text, ...) \`
- L113 _macro_ `#define UNSYNC_ERROR(text, ...) \`
- L119 _macro_ `#define UNSYNC_FATAL(text, ...) \`
- L124 _macro_ `#define UNSYNC_VERBOSE(text, ...) \`
- L128 _macro_ `#define UNSYNC_VERBOSE2(text, ...) \`
- L133 _macro_ `#define UNSYNC_ASSERT(cond) \`
- L141 _macro_ `#define UNSYNC_ASSERTF(cond, text, ...) \`
- L150 _macro_ `#define UNSYNC_BREAK_ON_ERROR \`
- L156 _macro_ `#define UNSYNC_BREAK_ON_WARNING \`
- L162 _macro_ `#define UNSYNC_BREAK_ON_ERROR_LEVEL(LogLevel) \`
- L168 _macro_ `#define UNSYNC_BREAK_ON_WARNING_LEVEL(LogLevel) \`

### `Source/Programs/Unsync/Private/UnsyncManifest.h` (Private)


#### struct `unsync::FFileManifest`  
`struct FFileManifest`  
_L16-31_
- L18 _public member_ `uint64 Mtime = 0;`
- L19 _public member_ `uint64 Size = 0;`
- L20 _public member_ `uint32 BlockSize = 0;`
- L23 _public member_ `FGenericBlockArray Blocks;` — runtime-only data:
- L24 _public member_ `FGenericBlockArray MacroBlocks;`
- L25 _public member_ `FPath CurrentPath;`
- L26 _public member_ `std::string RevisionControlIdentity;`
- L27 _public member_ `bool bReadOnly = false;`
- L28 _public member_ `bool bIsExecutable = false;`
- L30 _public function_ `bool IsValid() const`

#### struct `unsync::FAlgorithmOptionsV5`  
`struct FAlgorithmOptionsV5`  
_L33-41_
- L35 _public member_ `static constexpr uint64 MAGIC = 0x96FF3B56283EC7DBull;`
- L36 _public member_ `static constexpr uint64 VERSION = 1;`
- L38 _public member_ `EChunkingAlgorithmID ChunkingAlgorithmId = EChunkingAlgorithmID::VariableBlocks;`
- L39 _public member_ `EWeakHashAlgorithmID WeakHashAlgorithmId = EWeakHashAlgorithmID::BuzHash;`
- L40 _public member_ `EStrongHashAlgorithmID StrongHashAlgorithmId = EStrongHashAlgorithmID::Blake3_128;`

#### struct `unsync::FAlgorithmOptions`  
`struct FAlgorithmOptions : FAlgorithmOptionsV5`  
_L43-45_
- inherits: `FAlgorithmOptionsV5`

#### struct `unsync::FDirectoryManifest`  
`struct FDirectoryManifest`  
_L47-79_
- L62 _public member_ `static constexpr uint64 MAGIC = 0x80F4CC2A414F4E41ull;`
- L63 _public member_ `static constexpr uint64 VERSION = EVersions::Latest;`
- L67 _public typedef_ `using FFileMap = std::map<std::wstring, FFileManifest>;` — wide string at runtime, utf8 serialized TODO: keep paths in canonical form (utf-8, unix-style separators)
- L68 _public member_ `FFileMap Files;`
- L71 _public member_ `FAlgorithmOptions Algorithm = {};` — runtime data
- L72 _public member_ `uint64 Version = 0;`
- L74 _public member_ `bool bHasFileRevisionControl = false;`
- L76 _public member_ `std::vector<FPackReference> PackReferences;`
- L78 _public function_ `bool IsValid() const`

#### enum `unsync::FDirectoryManifest::EVersions`  
`enum EVersions : uint64`  
_L49-60_
- L50 _public enumerator_ `Invalid = 0`
- L51 _public enumerator_ `V1_Unsupported`
- L52 _public enumerator_ `V2_Unsupported`
- L53 _public enumerator_ `V3_Unsupported`
- L54 _public enumerator_ `V4` — unsync v1.0.7
- L55 _public enumerator_ `V5` — unsync v1.0.8: added options
- L56 _public enumerator_ `V6_VariableHash` — unsync v1.0.32-iohash: added variable size hashes, moved options section before files
- L57 _public enumerator_ `V7_OptionalSections` — unsync v1.0.32-iohash
- L59 _public enumerator_ `Latest = V7_OptionalSections`

#### struct `unsync::FDirectoryManifestInfo`  
`struct FDirectoryManifestInfo`  
_L81-91_
- L83 _public member_ `uint64 TotalSize = 0;`
- L84 _public member_ `uint64 UniqueSize = 0;`
- L85 _public member_ `uint64 NumBlocks = 0;`
- L86 _public member_ `uint64 NumMacroBlocks = 0;`
- L87 _public member_ `uint64 NumFiles = 0;`
- L88 _public member_ `FHash256 StableSignature = {};`
- L90 _public member_ `FAlgorithmOptions Algorithm = {};`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace unsync`
- L93 _prototype_ `FDirectoryManifestInfo GetManifestInfo(const FDirectoryManifest& Manifest, bool bGenerateSignature = true);` (scope `unsync`)
- L94 _prototype_ `void LogManifestInfo(ELogLevel LogLevel, const FDirectoryManifest& Manifest);` (scope `unsync`)
- L95 _prototype_ `void LogManifestInfo(ELogLevel LogLevel, const FDirectoryManifestInfo& Info);` (scope `unsync`)
- L96 _prototype_ `void LogManifestFiles(ELogLevel LogLevel, const FDirectoryManifest& Manifest);` (scope `unsync`)
- L97 _prototype_ `void LogManifestFiles(ELogLevel LogLevel, const FDirectoryManifestInfo& Info);` (scope `unsync`)
- L102 _prototype_ `FHash256 ComputeManifestStableSignature(const FDirectoryManifest& Manifest);` (scope `unsync`) — Computes a Blake3 hash of the manifest blocks and file metadata, ignoring any other metadata. Files are processed in sorted order, with file names treated as utf-8. This produces a relatively stable manifest key that does not depend on the serialization differences between versions.
- L105 _prototype_ `FHash256 ComputeSerializedManifestHash(const FDirectoryManifest& Manifest);` (scope `unsync`) — Computes a Blake3 hash of the serialized manifest data
- L107 _prototype_ `void UpdateDirectoryManifestBlocks(FDirectoryManifest& Result, const FPath& Root, const FComputeBlocksParams& Params);` (scope `unsync`)
- L108 _prototype_ `FDirectoryManifest CreateDirectoryManifest(const FPath& Root, const FComputeBlocksParams& Params);` (scope `unsync`)
- L109 _prototype_ `FDirectoryManifest CreateDirectoryManifestIncremental(const FPath& Root, const FComputeBlocksParams& Params);` (scope `unsync`)
- L110 _prototype_ `bool LoadOrCreateDirectoryManifest(FDirectoryManifest& Result, const FPath& Root, const FComputeBlocksParams& Params);` (scope `unsync`)
- L111 _prototype_ `bool MergeManifests(FDirectoryManifest& Existing, const FDirectoryManifest& Other, bool bCaseSensitive);` (scope `unsync`)
- L112 _prototype_ `void MoveCompatibleManifestBlocks(FDirectoryManifest& Manifest, FDirectoryManifest&& DonorManifest);` (scope `unsync`)
- L113 _prototype_ `bool AlgorithmOptionsCompatible(const FAlgorithmOptions& A, const FAlgorithmOptions& B);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncMemory.h` (Private)


#### enum `unsync::EMallocType`  
`enum class EMallocType`  
_L15-20_
- L17 _public enumerator_ `Invalid`
- L18 _public enumerator_ `Default`
- L19 _public enumerator_ `Debug`

#### struct `unsync::FSystemMemoryInfo`  
`struct FSystemMemoryInfo`  
_L26-29_
- L28 _public member_ `uint64 InstalledPhysicalMemory = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L10 _macro_ `# define UNSYNC_USE_DEBUG_HEAP 0`
- L13 _variable_ `static constexpr size_t UNSYNC_MALLOC_ALIGNMENT = 16;` (scope `unsync`)
- L22 _prototype_ `void UnsyncMallocInit(EMallocType MallocType);` (scope `unsync`)
- L23 _prototype_ `void* UnsyncMalloc(size_t Size);` (scope `unsync`)
- L24 _prototype_ `void UnsyncFree(void* Ptr);` (scope `unsync`)
- L32 _prototype_ `bool QueryMemoryInfo(FSystemMemoryInfo& OutMemoryInfo);` (scope `unsync`) — Queries various memory properties from the OS, returns false if information is not available

### `Source/Programs/Unsync/Private/UnsyncMiniCb.h` (Private)


#### enum `unsync::EMiniCbFieldType`  
`enum class EMiniCbFieldType : uint8`  
_L18-48_
- L20 _public enumerator_ `None = 0x00`
- L21 _public enumerator_ `Null = 0x01`
- L22 _public enumerator_ `Object = 0x02`
- L23 _public enumerator_ `UniformObject = 0x03`
- L24 _public enumerator_ `Array = 0x04`
- L25 _public enumerator_ `UniformArray = 0x05`
- L26 _public enumerator_ `Binary = 0x06`
- L27 _public enumerator_ `String = 0x07`
- L28 _public enumerator_ `IntegerPositive = 0x08`
- L29 _public enumerator_ `IntegerNegative = 0x09`
- L30 _public enumerator_ `Float32 = 0x0a`
- L31 _public enumerator_ `Float64 = 0x0b`
- L32 _public enumerator_ `BoolFalse = 0x0c`
- L33 _public enumerator_ `BoolTrue = 0x0d`
- L34 _public enumerator_ `ObjectAttachment = 0x0e`
- L35 _public enumerator_ `BinaryAttachment = 0x0f`
- L36 _public enumerator_ `Hash = 0x10`
- L37 _public enumerator_ `Uuid = 0x11`
- L38 _public enumerator_ `DateTime = 0x12`
- L39 _public enumerator_ `TimeSpan = 0x13`
- L40 _public enumerator_ `ObjectId = 0x14`
- L41 _public enumerator_ `CustomById = 0x1e`
- L42 _public enumerator_ `CustomByName = 0x1f`
- L45 _public enumerator_ `Reserved = 0x20` — Flags
- L46 _public enumerator_ `HasFieldType = 0x40`
- L47 _public enumerator_ `HasFieldName = 0x80`

#### struct `unsync::FMiniCbPayloadSize`  
`struct FMiniCbPayloadSize`  
_L56-60_
- L58 _public member_ `uint64 DataSize = 0;`
- L59 _public member_ `uint64 HeaderSize = 0;`

#### struct `unsync::FMiniCbWriter`  
`struct FMiniCbWriter`  
_L93-207_
- L95 _public member_ `static const uint64 MAX_OBJECT_HEADER_SIZE = 9 + 1;` — maximum var-uint size + object type identifier
- L97 _public function_ `FMiniCbWriter()`
- L104 _public function_ `void AddNull()`
- L106 _public function_ `void AddBinaryAttachment(FHash160 Hash, std::string_view Name = {})` — TODO: add field name
- L114 _public function_ `void AddHash(FHash160 Hash, std::string_view Name = {})` — TODO: add field name
- L120 _public function_ `void AddHashArray(std::span<FHash160> Hashes, std::string_view Name = {})`
- L126 _public function_ `void AddBinaryAttachmentArray(std::span<FHash160> Hashes, std::string_view Name = {})`
- L132 _public function_ `void Finalize()`
- L143 _public function_ `const uint8* Data() const`
- L148 _public function_ `const uint64 Size() const`
- L154 _public function_ `FBufferView GetBufferView() const`
- L156 _public function_ `uint64 GetNumAttachments() const`
- L159 _private function_ `void WriteUint(uint64 V)`
- L168 _private function_ `void WriteString(std::string_view Str)`
- L174 _private function_ `void WriteFieldHeader(EMiniCbFieldType Type, std::string_view Name = {})`
- L191 _private function_ `void WriteUniformArrayHeader(EMiniCbFieldType ElemType, uint64 SizeInBytes, uint64 ItemCount, std::string_view Name = {})`
- L204 _private member_ `FBuffer Output;`
- L205 _private member_ `uint64 HeaderOffset = ~0ull;`
- L206 _private member_ `uint64 NumAttachments = 0;`

#### struct `unsync::FMiniCbFieldView`  
`struct FMiniCbFieldView : FBufferView`  
_L211-239_
- inherits: `FBufferView`
- L213 _public member_ `EMiniCbFieldType Type = EMiniCbFieldType::None;`
- L214 _public member_ `std::string_view Name;`
- L216 _public member_ `uint64 UniformArrayByteCount = 0;`
- L217 _public member_ `uint64 UniformArrayItemCount = 0;`
- L218 _public member_ `EMiniCbFieldType UniformArrayItemType = EMiniCbFieldType::None;`
- L220 _public prototype_ `FMiniCbFieldView Child();`
- L222 _public function_ `bool IsValid() const`
- L225 _public function_ `template<typename T> const T& GetValue() const`
- L233 _public function_ `template<typename T> std::span<const T> GetUniformArray() const`
- L328 _function_ `FMiniCbFieldView::Child()`

#### struct `unsync::FMiniCbReader`  
`struct FMiniCbReader`  
_L241-325_
- L243 _public function_ `FMiniCbReader(const uint8* InData, uint64 InSize) : Data(InData), Size(InSize), Cursor(InData)`
- L244 _public function_ `FMiniCbReader(FBufferView View) : FMiniCbReader(View.Data, View.Size)`
- L245 _public function_ `FMiniCbReader(const FMiniCbFieldView& InView) : FMiniCbReader(InView.Data, InView.Size)`
- L247 _public function_ `FMiniCbFieldView Child()`
- L321 _public member_ `const uint8* Data;`
- L322 _public member_ `uint64 Size;`
- L324 _public member_ `const uint8* Cursor = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace unsync`
- L51 _function_ `HasName(EMiniCbFieldType Type)` (scope `unsync`)
- L63 _function_ `GetPayloadSize(EMiniCbFieldType Type, const uint8* Payload = nullptr)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncMount.h` (Private)


#### struct `unsync::FMountedDirectory`  
``  
_L11-55_
- L15 _public prototype_ `FMountedDirectory() = default;`
- L17 _public member_ `bool bValid = false;`
- L18 _public member_ `FDirectoryManifest Manifest;`
- L49 _public member_ `std::vector<FDirectoryEntry> DirectoryEntries;`
- L52 _public member_ `std::unordered_map<std::wstring_view, uint64> DirectoryMap;` — Offset of the first directory entry corresponding to a speficic parent name
- L54 _public prototype_ `bool Mount(const FPath& RootPath);`

#### enum `unsync::FMountedDirectory::EDirectoryEntryType`  
`enum class EDirectoryEntryType`  
_L20-24_
- L22 _public enumerator_ `Directory = 0` — Filesystem entries are sorted by this and we want to list directories first during iteration
- L23 _public enumerator_ `File = 1`

#### struct `unsync::FMountedDirectory::FDirectoryEntry`  
`struct FDirectoryEntry`  
_L26-47_
- L28 _public member_ `int32 Depth = 0;`
- L29 _public member_ `EDirectoryEntryType Type = EDirectoryEntryType::File;`
- L31 _public member_ `std::wstring_view Path;` — Full path relative to mounted directory root
- L33 _public member_ `std::wstring_view Parent;` — Full path of parent directory (guaranteed to be deduplicated, i.e. identical strings point to the same memory)
- L35 _public member_ `std::wstring_view Name;` — File/directory name (without parent path)
- L36 _public member_ `const FFileManifest* Manifest = nullptr;`
- L38 _public function_ `bool operator<(const FDirectoryEntry& Other) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`

### `Source/Programs/Unsync/Private/UnsyncPack.h` (Private)


#### struct `unsync::FPackIndexDatabase`  
`struct FPackIndexDatabase`  
_L19-26_
- L21 _public member_ `std::vector<FPackIndexEntry> Entries;`
- L24 _public member_ `FPath IndexPath;` — Runtime-only data
- L25 _public member_ `FPath DataPath;`

#### struct `unsync::FPackWriteContext`  
`struct FPackWriteContext`  
_L30-75_
- L32 _public prototype_ `FPackWriteContext(const FPath& InOutputRoot);`
- L33 _public prototype_ `~FPackWriteContext();`
- L35 _public prototype_ `void AddRawBlock(const FGenericBlock& Block, FBufferView RawData);` — thread-safe
- L36 _public prototype_ `void AddCompressedBlock(const FGenericBlock& Block, FHash128 CompressedHash, FBufferView CompressedData);` — thread-safe
- L37 _public prototype_ `void CompressAndAddBlock(const FGenericBlock& Block, FBufferView RawData);` — thread-safe
- L39 _public prototype_ `void FinishPack();` — thread-safe
- L47 _public prototype_ `static FCompressedBlock CompressBlock(FBufferView RawData);`
- L49 _public prototype_ `void GetUniqueGeneratedPackIds(std::vector<FPackReference>& Output) const;` — thread-safe
- L53 _private prototype_ `void InternalAddBlock(const FGenericBlock& Block, FHash128 CompressedHash, FBufferView Data);`
- L54 _private prototype_ `void InternalReset();`
- L55 _private prototype_ `void InternalFinishPack();`
- L57 _private member_ `mutable std::mutex Mutex;`
- L61 _private member_ `uint64 IndexFileHashSum[2] = {};` — Independent sums of low and high 32 bits of all seen block hashes. Used to generate a stable hash while allowing out-of-order block processing.
- L63 _private member_ `FBuffer PackBuffer;`
- L64 _private member_ `std::vector<FPackIndexEntry> IndexEntries;`
- L66 _private member_ `uint64 ProcessedRawBytes = 0;`
- L67 _private member_ `uint64 ProcessedCompressedBytes = 0;`
- L69 _private member_ `uint32 NumRawBlocks = 0;`
- L70 _private member_ `uint32 NumCompressedBlocks = 0;`
- L72 _private member_ `FPath OutputRoot;`
- L74 _private member_ `std::vector<FPackReference> GeneratedPackIds;`

#### struct `unsync::FPackWriteContext::FCompressedBlock`  
`struct FCompressedBlock`  
_L42-46_
- desc: Common utility function to compress a block and generate compressed hash
- L44 _public member_ `FIOBuffer Data;` — zstd-compressed block
- L45 _public member_ `FHash128 Hash;` — block hash after compression

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace unsync`
- L15 _variable_ `static constexpr uint64 GMaxPackFileSize = 1_GB;` (scope `unsync`)
- L28 _prototype_ `bool LoadPackIndexDatabase(FPackIndexDatabase& Output, FIOReaderStream& Stream);` (scope `unsync`)
- L77 _prototype_ `void MergePackReferences(std::vector<FPackReference>& Destination, const std::vector<FPackReference>& Source);` (scope `unsync`)
- L79 _prototype_ `void DeletePackAndIdexData(const FPath& PackRootDirectory);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncPool.h` (Private)


#### struct `unsync::TObjectPool`  
`template<typename T> struct TObjectPool`  
_L13-44_
- L15 _public function_ `TObjectPool(std::function<T*()>&& InCreateObject) : CreateObject(InCreateObject)`
- L17 _public function_ `std::unique_ptr<T> Acquire()`
- L35 _public function_ `void Release(std::unique_ptr<T>&& Object)`
- L41 _public member_ `std::function<T*()> CreateObject;`
- L42 _public member_ `std::vector<std::unique_ptr<T>> AvailableObjects;`
- L43 _public member_ `std::mutex Mutex;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace unsync`

### `Source/Programs/Unsync/Private/UnsyncProgress.h` (Private)


#### enum `unsync::EBlockListType`  
`enum class EBlockListType`  
_L27-30_
- L28 _public enumerator_ `Source`
- L29 _public enumerator_ `Base`

#### enum `unsync::ELogProgressUnits`  
`enum class ELogProgressUnits`  
_L34-39_
- L35 _public enumerator_ `Raw`
- L36 _public enumerator_ `Bytes`
- L37 _public enumerator_ `MB`
- L38 _public enumerator_ `GB`

#### struct `unsync::FLogProgressScope`  
`struct FLogProgressScope`  
_L41-62_
- L45 _public prototype_ `FLogProgressScope(uint64 InTotal, ELogProgressUnits InUnits = ELogProgressUnits::Raw, uint64 InPeriodMilliseconds = 500, bool bInVerboseOnly = true);`
- L47 _public prototype_ `void Complete();`
- L49 _public prototype_ `void Add(uint64 X, bool bForceComplete = false);`
- L51 _public member_ `const bool bParentThreadVerbose;`
- L52 _public member_ `const uint32 ParentThreadIndent;`
- L54 _public member_ `std::mutex Mutex;`
- L55 _public member_ `std::atomic<uint64> Current;`
- L56 _public member_ `const uint64 Total;`
- L57 _public member_ `const uint64 PeriodMilliseconds;`
- L58 _public member_ `const ELogProgressUnits Units;`
- L59 _public member_ `FTimePoint NextProgressLogTime;`
- L60 _public member_ `std::atomic<bool> bEnabled;`
- L61 _public member_ `const bool bVerboseOnly;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace unsync`
- L15 _variable_ `static constexpr uint64 GLOBAL_PROGRESS_SOURCE_SCALE = 25;` (scope `unsync`) — pretend that reading remote files is ~25x slower than local
- L16 _variable_ `static constexpr uint64 GLOBAL_PROGRESS_BASE_SCALE = 1;` (scope `unsync`)
- L18 _externvar_ `extern std::atomic<uint64> GGlobalProgressCurrent;` (scope `unsync`)
- L19 _externvar_ `extern std::atomic<uint64> GGlobalProgressTotal;` (scope `unsync`)
- L22 _function_ `LogGlobalProgress()` (scope `unsync`)
- L32 _prototype_ `void AddGlobalProgress(uint64 Size, EBlockListType ListType);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncProtocol.h` (Private)


#### enum `unsync::EChunkingAlgorithmID`  
`enum class EChunkingAlgorithmID : uint64`  
_L24-29_
- L26 _public enumerator_ `Invalid = 0`
- L27 _public enumerator_ `FixedBlocks = 0xE9457636EEF48607ull` — "FixedBlocks" as fnv1a64
- L28 _public enumerator_ `VariableBlocks = 0xE62448A75E8B1CC3ull` — "VariableBlocks" as fnv1a64

#### enum `unsync::EWeakHashAlgorithmID`  
`enum class EWeakHashAlgorithmID : uint64`  
_L33-38_
- L35 _public enumerator_ `Invalid = 0`
- L36 _public enumerator_ `Naive = 0x4BD87A66500A16D6ull` — "Naive" as fnv1a64
- L37 _public enumerator_ `BuzHash = 0x9A8AB46A97A95962ull` — "Buzhash" as fnv1a64

#### enum `unsync::EStrongHashAlgorithmID`  
`enum class EStrongHashAlgorithmID : uint64`  
_L42-50_
- L44 _public enumerator_ `Invalid = 0`
- L45 _public enumerator_ `MD5 = 0x1E8F2819B58AD6B3ull` — "MD5" as fnv1a64
- L46 _public enumerator_ `Meow = 0x6D8900AEE47E763Dull` — "Meow" as fnv1a64 (deprecated)
- L47 _public enumerator_ `Blake3_128 = 0x7FD87D89C7C1D597ull` — "Blake3" as fnv1a64 ("_128" is omitted for backwards compatibility)
- L48 _public enumerator_ `Blake3_160 = 0xB68497EF4370C4F5ull` — "Blake3_160" as fnv1a64
- L49 _public enumerator_ `Blake3_256 = 0xBF89BAEF48A68CC5ull` — "Blake3_256" as fnv1a64

#### struct `unsync::TBlock`  
`template<typename StrongHashT> struct TBlock`  
_L55-68_
- L57 _public typedef_ `using StrongHashType = StrongHashT;`
- L59 _public member_ `uint64 Offset = 0;`
- L60 _public member_ `uint32 Size = 0;`
- L61 _public member_ `uint32 HashWeak = 0;`
- L62 _public member_ `StrongHashT HashStrong = {};`

#### struct `unsync::TBlock::FCompareByOffset`  
`struct FCompareByOffset`  
_L64-67_
- L66 _public function_ `bool operator()(const TBlock<StrongHashT>& A, const TBlock<StrongHashT>& B) const`

#### struct `unsync::FSerializedSectionHeader`  
`struct FSerializedSectionHeader`  
_L92-99_
- L94 _public member_ `static constexpr uint64 MAGIC = 0xEE5037CFF5BC71B2ull;`
- L95 _public member_ `uint64 Magic = MAGIC;`
- L96 _public member_ `uint64 Id = SERIALIZED_SECTION_ID_TERMINATOR;`
- L97 _public member_ `uint64 Version = 0;`
- L98 _public member_ `uint64 Size = 0;`

#### struct `unsync::FMetadataStringSection`  
`struct FMetadataStringSection`  
_L101-107_
- L103 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_METADATA_STRING;`
- L104 _public member_ `static constexpr uint64 VERSION = 1;`
- L105 _public member_ `std::string NameUtf8;`
- L106 _public member_ `std::string ValueUtf8;`

#### struct `unsync::FMacroBlockSection`  
`struct FMacroBlockSection`  
_L109-113_
- L111 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_MACRO_BLOCK;`
- L112 _public member_ `static constexpr uint64 VERSION = 2;`

#### struct `unsync::FFileReadOnlyMaskSection`  
`struct FFileReadOnlyMaskSection`  
_L115-119_
- L117 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_FILE_READ_ONLY_MASK;`
- L118 _public member_ `static constexpr uint64 VERSION = 1;`

#### struct `unsync::FFileExecutableBitSection`  
`struct FFileExecutableBitSection`  
_L121-125_
- L123 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_FILE_EXECUTABLE_BIT;`
- L124 _public member_ `static constexpr uint64 VERSION = 1;`

#### struct `unsync::FFileRevisionControlSection`  
`struct FFileRevisionControlSection`  
_L127-131_
- L129 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_FILE_REVISION_CONTROL;`
- L130 _public member_ `static constexpr uint64 VERSION = 1;`

#### struct `unsync::FPackReferenceSection`  
`struct FPackReferenceSection`  
_L133-137_
- L135 _public member_ `static constexpr uint64 MAGIC = SERIALIZED_SECTION_ID_PACK_REFERENCE;`
- L136 _public member_ `static constexpr uint64 VERSION = 3;`

#### struct `unsync::FBlockFileHeader`  
`struct FBlockFileHeader`  
_L139-148_
- L141 _public member_ `static constexpr uint64 MAGIC = 0x1DCB86A5BDBA27CFull;`
- L142 _public member_ `static constexpr uint64 VERSION = 2;`
- L144 _public member_ `uint64 Magic = MAGIC;`
- L145 _public member_ `uint64 Version = VERSION;`
- L146 _public member_ `uint64 BlockSize = 0;`
- L147 _public member_ `uint64 NumBlocks = 0;`

#### struct `unsync::FBlockRequest`  
`struct FBlockRequest`  
_L150-156_
- L152 _public member_ `FHash128 FilenameMd5 = {};`
- L153 _public member_ `FHash128 BlockHash = {};`
- L154 _public member_ `uint64 Offset = 0;`
- L155 _public member_ `uint64 Size = 0;`

#### struct `unsync::FHandshakePacket`  
`struct FHandshakePacket`  
_L158-164_
- L160 _public member_ `static constexpr uint64 MAGIC = 0xAE2C046180D0914Eull;`
- L161 _public member_ `uint64 Magic = MAGIC;`
- L162 _public member_ `uint32 Protocol = 1;`
- L163 _public member_ `uint32 Size = 0;`

#### struct `unsync::FCommandPacket`  
`struct FCommandPacket`  
_L170-175_
- L172 _public member_ `static constexpr uint64 MAGIC = 0x251B6A201A26EC82ull;`
- L173 _public member_ `uint64 Magic = MAGIC;`
- L174 _public member_ `uint64 CommandId = 0;`

#### struct `unsync::FBufferPacket`  
`struct FBufferPacket`  
_L177-182_
- L179 _public member_ `static constexpr uint64 MAGIC = 0x6539A89058A3400Aull;`
- L180 _public member_ `uint64 Magic = MAGIC;`
- L181 _public member_ `uint32 DataSizeBytes = 0;`

#### struct `unsync::FFileListPacket`  
`struct FFileListPacket`  
_L184-190_
- L186 _public member_ `static constexpr uint64 MAGIC = 0x28B96050A327172Aull;`
- L187 _public member_ `uint64 Magic = MAGIC;`
- L188 _public member_ `uint32 DataSizeBytes = 0;`
- L189 _public member_ `uint32 NumFiles = 0;`

#### struct `unsync::FRequestBlocksPacket`  
`struct FRequestBlocksPacket`  
_L192-200_
- L194 _public member_ `static constexpr uint64 MAGIC = 0x6A885827EA6659F7ull;`
- L195 _public member_ `uint64 Magic = MAGIC;`
- L196 _public member_ `uint64 StrongHashAlgorithmId = 0;`
- L197 _public member_ `uint32 CompressedSizeBytes = 0;`
- L198 _public member_ `uint32 DecompressedSizeBytes = 0;`
- L199 _public member_ `uint32 NumRequests = 0;`

#### struct `unsync::FBlockPacket`  
`struct FBlockPacket`  
_L202-207_
- L204 _public member_ `FHash128 Hash = {};`
- L205 _public member_ `uint64 DecompressedSize = 0;` — 0 if data is not compressed
- L206 _public member_ `FBuffer Data;`

#### struct `unsync::FPatchHeader`  
`struct FPatchHeader`  
_L209-227_
- L211 _public member_ `static constexpr uint64 VALIDATION_BLOCK_SIZE = 16_MB;`
- L213 _public member_ `static constexpr uint64 MAGIC = 0x3E63942C4C9ECE16ull;`
- L214 _public member_ `static constexpr uint64 VERSION = 2;`
- L216 _public member_ `uint64 Magic = MAGIC;`
- L217 _public member_ `uint64 Version = VERSION;`
- L218 _public member_ `uint64 SourceSize = 0;`
- L219 _public member_ `uint64 BaseSize = 0;`
- L220 _public member_ `uint64 NumSourceValidationBlocks = 0;`
- L221 _public member_ `uint64 NumBaseValidationBlocks = 0;`
- L222 _public member_ `uint64 NumSourceBlocks = 0;`
- L223 _public member_ `uint64 NumBaseBlocks = 0;`
- L224 _public member_ `uint64 BlockSize = 0;`
- L225 _public member_ `EWeakHashAlgorithmID WeakHashAlgorithmId = EWeakHashAlgorithmID::Naive;`
- L226 _public member_ `EStrongHashAlgorithmID StrongHashAlgorithmId = EStrongHashAlgorithmID::Blake3_128;`

#### struct `unsync::FPackIndexEntry`  
`struct FPackIndexEntry`  
_L229-239_
- L232 _public member_ `FHash128 BlockHash = {};` — Decompressed block hash
- L234 _public member_ `FHash128 CompressedHash = {};` — Compressed block hash (may be equal to BlockHash to signal uncompressed block)
- L237 _public member_ `uint32 PackBlockOffset = 0;` — Offset and size within pack file
- L238 _public member_ `uint32 PackBlockSize = 0;`

#### struct `unsync::FPackIndexHeader`  
`struct FPackIndexHeader`  
_L242-250_
- L244 _public member_ `static constexpr uint64 MAGIC = 0xEEC735E03053CC3Full;`
- L245 _public member_ `static constexpr uint64 VERSION = 2;`
- L247 _public member_ `uint64 Magic = MAGIC;`
- L248 _public member_ `uint64 Version = VERSION;`
- L249 _public member_ `uint64 NumEntries = 0;`

#### enum `unsync::EPackReferenceFlags`  
`enum class EPackReferenceFlags : uint32`  
_L253-257_
- L254 _public enumerator_ `Default = 0`
- L255 _public enumerator_ `HasRawBlocks = 1 << 0`
- L256 _public enumerator_ `HasCompressedBlocks = 1 << 1`

#### struct `unsync::FPackReference`  
`struct FPackReference`  
_L261-282_
- desc: Basic information about a pack file referenced by a manifest
- L263 _public typedef_ `using EFlags = EPackReferenceFlags;`
- L265 _public function_ `bool operator==(const FPackReference& Other) const`
- L278 _public member_ `FHash128 Id = {};`
- L279 _public member_ `EFlags Flags = EFlags::Default;`
- L280 _public member_ `uint32 NumUsedBlocks = 0;`
- L281 _public member_ `uint32 NumTotalBlocks = 0;`

#### struct `unsync::FPackReference::Hasher`  
`struct Hasher`  
_L269-276_
- L271 _public function_ `size_t operator()(const FPackReference& X) const`

#### struct `unsync::FBlockRequest256`  
`struct FBlockRequest256`  
_L287-293_
- L289 _public member_ `FHash128 FilenameMd5 = {};`
- L290 _public member_ `FHash256 BlockHash = {};`
- L291 _public member_ `uint64 Offset = 0;`
- L292 _public member_ `uint64 Size = 0;`

#### struct `unsync::FBlockPacket256`  
`struct FBlockPacket256`  
_L295-300_
- L297 _public member_ `FHash256 Hash;`
- L298 _public member_ `uint64 DecompressedSize = 0;`
- L299 _public member_ `FBuffer CompressedData;`

#### struct `unsync::FHordeUnsyncBlobHeaderV1`  
`struct FHordeUnsyncBlobHeaderV1`  
_L302-310_
- L304 _public member_ `static constexpr uint64 MAGIC = 0x4C5C2AABA992610Cull;`
- L306 _public member_ `uint64 Magic = 0;`
- L307 _public member_ `uint64 PayloadSize = 0;`
- L308 _public member_ `uint64 DecompressedSize = 0;`
- L309 _public member_ `FHash160 DecompressedHash = {};`

#### struct `unsync::FHordeUnsyncBlobErrorHeaderV1`  
`struct FHordeUnsyncBlobErrorHeaderV1`  
_L312-318_
- L314 _public member_ `static constexpr uint64 MAGIC = 0x4C5C2AABA992DEADull;`
- L316 _public member_ `uint64 Magic = 0;`
- L317 _public member_ `uint32 PayloadSize = 0;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace unsync`
- L21 _variable_ `static constexpr uint32 MAX_BLOCK_SIZE = uint32(1_MB);` (scope `unsync`)
- L22 _variable_ `static constexpr EHashType MACRO_BLOCK_HASH_TYPE = EHashType::Blake3_160;` (scope `unsync`) — Blake3 160bit (IoHash) is required for macro blocks due to back-end storage implementation
- L31 _prototype_ `const char* ToString(EChunkingAlgorithmID Algorithm);` (scope `unsync`)
- L40 _prototype_ `const char* ToString(EWeakHashAlgorithmID Algorithm);` (scope `unsync`)
- L52 _prototype_ `const char* ToString(EStrongHashAlgorithmID Algorithm);` (scope `unsync`)
- L70 _typedef_ `using FBlock128 = TBlock<FHash128>;` (scope `unsync`)
- L71 _typedef_ `using FBlock160 = TBlock<FHash160>;` (scope `unsync`)
- L72 _typedef_ `using FBlock256 = TBlock<FHash256>;` (scope `unsync`)
- L74 _typedef_ `using FGenericBlock = TBlock<FGenericHash>;` (scope `unsync`)
- L75 _typedef_ `using FGenericBlockArray = std::vector<FGenericBlock>;` (scope `unsync`)
- L78 _prototype_ `void FormatJsonBlock(std::wstring& Output, const FGenericBlock& Block);` (scope `unsync`) — Json formatting helpers
- L79 _prototype_ `void FormatJsonBlock(std::string& Output, const FGenericBlock& Block);` (scope `unsync`)
- L80 _prototype_ `void FormatJsonBlockArray(std::wstring& Output, const FGenericBlockArray& Blocks);` (scope `unsync`)
- L81 _prototype_ `void FormatJsonBlockArray(std::string& Output, const FGenericBlockArray& Blocks);` (scope `unsync`)
- L84 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_TERMINATOR = 0;` (scope `unsync`) — These are just random 64 bit numbers, not based on anything in particular
- L85 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_METADATA_STRING = 0xC6BD6CDCEEF79533ull;` (scope `unsync`)
- L86 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_MACRO_BLOCK = 0x8390AEBB745E08BCull;` (scope `unsync`)
- L87 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_FILE_READ_ONLY_MASK = 0x851F32ED3615F0ADull;` (scope `unsync`)
- L88 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_FILE_REVISION_CONTROL = 0x2C1C72E6B78B1B50ull;` (scope `unsync`)
- L89 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_PACK_REFERENCE = 0x634EA57F1E48DFBDull;` (scope `unsync`)
- L90 _variable_ `static constexpr uint64 SERIALIZED_SECTION_ID_FILE_EXECUTABLE_BIT = 0x2F4212FDAEF5C1ADull;` (scope `unsync`)
- L166 _variable_ `static constexpr uint64 COMMAND_ID_DISCONNECT = 0;` (scope `unsync`)
- L167 _variable_ `static constexpr uint64 COMMAND_ID_AUTHENTICATE = 0xAA77CB56ABD7153Aull;` (scope `unsync`)
- L168 _variable_ `static constexpr uint64 COMMAND_ID_GET_BLOCKS = 0xBBE2A1CECC8C949Cull;` (scope `unsync`)
- L258 _prototype_ `UNSYNC_ENUM_CLASS_FLAGS(EPackReferenceFlags, uint32);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncProxy.h` (Private)


#### enum `unsync::EDownloadRetryMode`  
`enum class EDownloadRetryMode`  
_L25-30_
- L27 _public enumerator_ `Retry` — potentially recoverable error (caller can retry the same request)
- L28 _public enumerator_ `Abort` — issuing the same request will likely fail, but other requests may succeed
- L29 _public enumerator_ `Disconnect` — further server API calls are likely to fail

#### struct `unsync::FDownloadError`  
`struct FDownloadError : FError`  
_L32-40_
- inherits: `FError`
- L34 _public prototype_ `FDownloadError() = default;`
- L35 _public function_ `FDownloadError(EDownloadRetryMode InRetryMode) : RetryMode(InRetryMode)`
- L37 _public member_ `EDownloadRetryMode RetryMode = EDownloadRetryMode::Abort;`
- L39 _public function_ `bool CanRetry() const`

#### struct `unsync::FDownloadedBlock`  
`struct FDownloadedBlock`  
_L44-50_
- L46 _public member_ `uint64 DecompressedSize = 0;`
- L47 _public member_ `uint64 CompressedSize = 0;`
- L48 _public member_ `const uint8* Data = nullptr;`
- L49 _public member_ `bool bCompressed = false;`

#### struct `unsync::FMacroBlockRequest`  
`struct FMacroBlockRequest`  
_L54-64_
- L56 _public member_ `FGenericHash Hash = {};`
- L57 _public member_ `uint64 Offset = 0;`
- L58 _public member_ `uint64 Size = 0;`
- L60 _public member_ `uint64 MacroBlockBaseOffset = 0;`
- L61 _public member_ `uint64 MacroBlockTotalSize = 0;`
- L63 _public function_ `bool IsValid() const`

#### class `unsync::FBlockRequestMap`  
`class FBlockRequestMap`  
_L66-101_
- L69 _public function_ `void Init(EStrongHashAlgorithmID InStrongHasher, const std::vector<FPath>& InSourceRoots)`
- L76 _public prototype_ `void AddFileBlocks(uint32 SourceId, const FPath& OriginalFilePath, const FPath& ResolvedFilePath, const FFileManifest& Manifest);`
- L77 _public prototype_ `void AddPackBlocks(const FPath& OriginalFilePath, const FPath& ResolvedFilePath, const TArrayView<FPackIndexEntry> PackManifest);`
- L84 _public function_ `const std::vector<std::string>& GetSourceFileList() const`
- L85 _public prototype_ `const FBlockRequestEx* FindRequest(const FGenericHash& BlockHash) const;`
- L86 _public prototype_ `const std::string* FindSourceFile(const FHash128& NameHashMd5) const;`
- L87 _public function_ `EStrongHashAlgorithmID GetStrongHasher() const`
- L88 _public prototype_ `FMacroBlockRequest GetMacroBlockRequest(const FGenericHash& BlockHash) const;`
- L89 _public function_ `const std::vector<FPath>& GetSourceRoots() const`
- L93 _private prototype_ `FHash128 AddFile(const FPath& OriginalFilePath, const FPath& ResolvedFilePath);`
- L95 _private member_ `EStrongHashAlgorithmID StrongHasher = EStrongHashAlgorithmID::Invalid;`
- L96 _private member_ `std::vector<std::string> SourceFileListUtf8;`
- L97 _private member_ `std::unordered_map<FHash128, uint32> HashToFile;`
- L98 _private member_ `std::unordered_map<FHash128, FBlockRequestEx> BlockRequests;`
- L99 _private member_ `std::unordered_map<FHash128, FMacroBlockRequest> MacroBlockRequests;`
- L100 _private member_ `std::vector<FPath> SourceRoots;`

#### struct `unsync::FBlockRequestMap::FBlockRequestEx`  
`struct FBlockRequestEx : FBlockRequest`  
_L79-82_
- inherits: `FBlockRequest`
- L81 _public member_ `uint32 SourceId = ~0u;`

#### struct `unsync::FRemoteProtocolFeatures`  
`struct FRemoteProtocolFeatures`  
_L103-113_
- L105 _public member_ `bool bTelemetry = false;`
- L106 _public member_ `bool bMirrors = false;`
- L107 _public member_ `bool bAuthentication = false;`
- L108 _public member_ `bool bDirectoryListing = false;`
- L109 _public member_ `bool bFileDownload = false;`
- L110 _public member_ `bool bManifestDownload = false;`
- L111 _public member_ `bool bBlockDownload = false;`
- L112 _public member_ `bool bAnnouncements = false;`

#### struct `unsync::FTelemetryEventSyncComplete`  
`struct FTelemetryEventSyncComplete`  
_L115-129_
- L117 _public member_ `std::string ClientVersion;`
- L118 _public member_ `std::string Session;`
- L119 _public member_ `std::string Source;`
- L120 _public member_ `std::string ClientHostNameHash;`
- L121 _public member_ `uint64 TotalBytes = 0;`
- L122 _public member_ `uint64 SourceBytes = 0;`
- L123 _public member_ `uint64 BaseBytes = 0;`
- L124 _public member_ `uint32 SkippedFiles = 0;`
- L125 _public member_ `uint32 FullCopyFiles = 0;`
- L126 _public member_ `uint32 PartialCopyFiles = 0;`
- L127 _public member_ `double Elapsed = 0;`
- L128 _public member_ `bool bSuccess = false;`

#### struct `unsync::FRemoteProtocolBase`  
`struct FRemoteProtocolBase`  
_L131-150_
- L133 _public function_ `FRemoteProtocolBase(const FRemoteDesc& InRemoteDesc, const FBlockRequestMap* InRequestMap) : RequestMap(InRequestMap) , RemoteDesc(InRemoteDesc)`
- L139 _public function_ `virtual ~FRemoteProtocolBase()`
- L141 _public function_ `virtual bool Contains(const FDirectoryManifest& Manifest)`
- L142 _public prototype_ `virtual bool IsValid() const = 0;`
- L143 _public prototype_ `virtual void Invalidate() = 0;`
- L145 _public prototype_ `virtual FDownloadResult Download(const TArrayView<FNeedBlock> NeedBlocks, const FBlockDownloadCallback& CompletionCallback) = 0;`
- L146 _public prototype_ `virtual TResult<FDirectoryManifest> DownloadManifest(std::string_view ManifestName) = 0;`
- L148 _public member_ `const FBlockRequestMap* RequestMap;`
- L149 _public member_ `FRemoteDesc RemoteDesc;`

#### class `unsync::FProxy`  
`class FProxy`  
_L155-173_
- desc: TODO: - transparently go through proxy when reading blocks during patching i.e. read blocks from disk / network share or from proxy automatically
- L158 _public prototype_ `FProxy(FProxyPool& ProxyPool, const FRemoteDesc& InRemoteDesc, const FRemoteProtocolFeatures& InFeatures, const FAuthDesc* InAuthDesc, const FBlockRequestMap* InRequestMap);`
- L163 _public prototype_ `~FProxy();`
- L165 _public prototype_ `bool Contains(const FDirectoryManifest& Manifest);`
- L166 _public prototype_ `bool IsValid() const;`
- L168 _public prototype_ `FDownloadResult Download(const TArrayView<FNeedBlock> NeedBlocks, const FBlockDownloadCallback& CompletionCallback);`
- L169 _public prototype_ `TResult<FDirectoryManifest> DownloadManifest(std::string_view ManifestName);`
- L172 _private member_ `std::unique_ptr<FRemoteProtocolBase> ProtocolImpl;`

#### class `unsync::FProxyPool`  
`class FProxyPool`  
_L175-216_
- L178 _public prototype_ `FProxyPool();`
- L179 _public prototype_ `FProxyPool(const FRemoteDesc& InRemoteDesc, const FAuthDesc* InAuthDesc);`
- L181 _public prototype_ `std::unique_ptr<FProxy> Alloc();`
- L182 _public prototype_ `void Dealloc(std::unique_ptr<FProxy>&& Proxy);`
- L184 _public prototype_ `std::unique_ptr<FHttpConnection> AllocHttp();`
- L185 _public prototype_ `void DeallocHttp(std::unique_ptr<FHttpConnection>&& Connection);`
- L187 _public prototype_ `std::string GetAccessToken();`
- L189 _public function_ `bool SupportsHttp() const`
- L191 _public prototype_ `void Invalidate();`
- L192 _public prototype_ `bool IsValid() const;`
- L194 _public member_ `const FRemoteDesc RemoteDesc;`
- L195 _public member_ `const FAuthDesc* AuthDesc = nullptr;` — optional reference to externally-owned auth parameters
- L197 _public prototype_ `void SetRequestMap(FBlockRequestMap&& InRequestMap);`
- L199 _public function_ `const FRemoteProtocolFeatures& GetFeatures() const`
- L200 _public function_ `const std::string& GetSessionId() const`
- L202 _public prototype_ `void SendTelemetryEvent(const FTelemetryEventSyncComplete& Event);`
- L205 _private member_ `std::vector<std::unique_ptr<FProxy>> Pool;`
- L206 _private member_ `bool bValid = true;`
- L208 _private member_ `std::optional<TObjectPool<FHttpConnection>> HttpPool;`
- L210 _private member_ `FRemoteProtocolFeatures Features;`
- L211 _private member_ `std::string SessionId;`
- L213 _private member_ `FBlockRequestMap RequestMap;`
- L215 _private member_ `std::mutex Mutex;`

#### struct `unsync::FPooledHttpConnection`  
`struct FPooledHttpConnection`  
_L218-229_
- L220 _public function_ `FPooledHttpConnection(FProxyPool& InProxyPool) : ProxyPool(InProxyPool)`
- L221 _public function_ `~FPooledHttpConnection()`
- L222 _public function_ `FHttpConnection* Get()`
- L223 _public function_ `FHttpConnection& operator*()`
- L224 _public function_ `FHttpConnection* operator->()`
- L225 _public function_ `operator FHttpConnection&()`
- L226 _public function_ `bool IsValid() const`
- L227 _public member_ `FProxyPool& ProxyPool;`
- L228 _public member_ `std::unique_ptr<FHttpConnection> Inner;`

#### struct `unsync::ProxyQuery::FAnnouncement`  
`struct FAnnouncement`  
_L235-240_
- L237 _public member_ `uint64 Id = 0;` — 64-bit hash, parsed from hex string in JSON
- L238 _public member_ `std::string Level;` — "info", "warning", "error"
- L239 _public member_ `std::string Message;`

#### struct `unsync::ProxyQuery::FHelloResponse`  
`struct FHelloResponse`  
_L242-266_
- L244 _public member_ `std::string Name;`
- L245 _public member_ `std::string VersionNumber;`
- L246 _public member_ `std::string VersionGit;`
- L247 _public member_ `std::string SessionId;`
- L249 _public member_ `std::string AuthServerUri;`
- L250 _public member_ `std::string AuthClientId;`
- L251 _public member_ `std::string AuthAudience;`
- L252 _public member_ `std::string CallbackUri;`
- L254 _public member_ `std::vector<std::string> FeatureNames;`
- L255 _public member_ `FRemoteProtocolFeatures Features;`
- L257 _public member_ `std::optional<FHostAddressAndPort> PrimaryHost;`
- L259 _public member_ `std::vector<FAnnouncement> Announcements;`
- L263 _public member_ `bool bConnectionEncrypted = false;`
- L265 _public function_ `bool SupportsAuthentication() const`

#### struct `unsync::ProxyQuery::FDirectoryListingEntry`  
`struct FDirectoryListingEntry`  
_L272-278_
- L274 _public member_ `std::string Name;` — utf-8
- L275 _public member_ `uint64 Mtime = 0;`
- L276 _public member_ `uint64 Size = 0;`
- L277 _public member_ `bool bDirectory = false;`

#### struct `unsync::ProxyQuery::FDirectoryListing`  
`struct FDirectoryListing`  
_L280-286_
- L282 _public member_ `std::vector<FDirectoryListingEntry> Entries;`
- L284 _public prototype_ `static TResult<FDirectoryListing> FromJson(const char* JsonString);`
- L285 _public prototype_ `std::string ToJson() const;`

#### struct `unsync::FProxyFileSystem`  
`struct FProxyFileSystem`  
_L308-314_
- desc: Abstracts basic filesystem operations, such as directory listing and file download. Can be used to transparently handle basic local and remote file operations.
- L310 _public prototype_ `virtual TResult<FProxyDirectoryListing> ListDirectory(const std::string_view RelativePath) = 0;`
- L311 _public prototype_ `virtual TResult<FBuffer> ReadFile(const std::string_view RelativePath) = 0;`
- L313 _public prototype_ `virtual ~FProxyFileSystem() = default;`

#### struct `unsync::FPhysicalFileSystem`  
`struct FPhysicalFileSystem : public FProxyFileSystem`  
_L316-324_
- inherits: `FProxyFileSystem`
- L318 _public prototype_ `FPhysicalFileSystem(const FPath& InRoot);`
- L320 _public prototype_ `virtual TResult<FProxyDirectoryListing> ListDirectory(const std::string_view RelativePath) final override;`
- L321 _public prototype_ `virtual TResult<FBuffer> ReadFile(const std::string_view RelativePath) final override;`
- L323 _public member_ `FPath Root;`

#### struct `unsync::FRemoteFileSystem`  
`struct FRemoteFileSystem : public FProxyFileSystem`  
_L326-335_
- inherits: `FProxyFileSystem`
- L328 _public function_ `FRemoteFileSystem(const std::string& InRoot, FProxyPool& InProxyPool) : Root(InRoot), ProxyPool(InProxyPool)`
- L330 _public prototype_ `virtual TResult<FProxyDirectoryListing> ListDirectory(const std::string_view RelativePath) final override;`
- L331 _public prototype_ `virtual TResult<FBuffer> ReadFile(const std::string_view RelativePath) final override;`
- L333 _public member_ `std::string Root;`
- L334 _public member_ `FProxyPool& ProxyPool;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace unsync`
- L42 _typedef_ `using FDownloadResult = TResult<FEmpty, FDownloadError>;` (scope `unsync`)
- L52 _typedef_ `using FBlockDownloadCallback = std::function<void(const FDownloadedBlock& Block, FHash128 BlockHash)>;` (scope `unsync`)
- L231 _externvar_ `extern bool GNoServerAnnouncements;` (scope `unsync`)
- L233 _namespace_ `namespace ProxyQuery` (scope `unsync`)
- L267 _prototype_ `TResult<FHelloResponse> Hello(const FRemoteDesc& RemoteDesc, const FAuthDesc* OptAuthDesc = nullptr, bool bDisplayAnnouncements = true);` (scope `unsync::ProxyQuery`)
- L268 _prototype_ `TResult<FHelloResponse> Hello(EProtocolFlavor Protocol, FHttpConnection& Connection, const FAuthDesc* OptAuthDesc = nullptr, bool bDisplayAnnouncements = true);` (scope `unsync::ProxyQuery`)
- L270 _prototype_ `void DisplayAnnouncements(const std::vector<FAnnouncement>& Announcements);` (scope `unsync::ProxyQuery`)
- L288 _prototype_ `TResult<FDirectoryListing> ListDirectory(EProtocolFlavor Protocol, FHttpConnection& Connection, const FAuthDesc* AuthDesc, const std::string& Path);` (scope `unsync::ProxyQuery`)
- L293 _prototype_ `TResult<FBuffer> DownloadFile(FHttpConnection& Connection, const FAuthDesc* AuthDesc, const std::string& Path);` (scope `unsync::ProxyQuery`)
- L295 _typedef_ `using FDownloadOutputCallback = std::function<FIOWriter&(uint64 Size)>;` (scope `unsync::ProxyQuery`)
- L296 _prototype_ `TResult<> DownloadFile(FHttpConnection& Connection, const FAuthDesc* AuthDesc, const std::string& Path, FDownloadOutputCallback OutputCallback);` (scope `unsync::ProxyQuery`)
- L303 _typedef_ `using FProxyDirectoryListing = ProxyQuery::FDirectoryListing;` (scope `unsync`)
- L304 _typedef_ `using FProxyDirectoryEntry = ProxyQuery::FDirectoryListingEntry;` (scope `unsync`)
- L338 _prototype_ `std::string FormatBlockRequestJson(const FBlockRequestMap& RequestMap, const TArrayView<FNeedBlock> NeedBlocks);` (scope `unsync`) — Build request block batch using Horde/Unsync JSON request format

### `Source/Programs/Unsync/Private/UnsyncRemote.h` (Private)


#### enum `unsync::EProtocolFlavor`  
`enum class EProtocolFlavor : uint8`  
_L19-24_
- L20 _public enumerator_ `Unknown`
- L21 _public enumerator_ `Unsync`
- L22 _public enumerator_ `Jupiter`
- L23 _public enumerator_ `Horde`

#### enum `unsync::ETransportProtocol`  
`enum class ETransportProtocol : uint8`  
_L26-29_
- L27 _public enumerator_ `Http`
- L28 _public enumerator_ `Unsync`

#### struct `unsync::FHostAddressAndPort`  
`struct FHostAddressAndPort`  
_L34-40_
- L36 _public member_ `std::string Address;`
- L37 _public member_ `uint16 Port = 0;`
- L39 _public function_ `bool IsValid() const`

#### struct `unsync::FRemoteDesc`  
`struct FRemoteDesc`  
_L42-78_
- L44 _public member_ `EProtocolFlavor Protocol = EProtocolFlavor::Unknown;`
- L46 _public member_ `FHostAddressAndPort Host;`
- L48 _public member_ `std::string RequestPath;`
- L49 _public member_ `std::string StorageNamespace;`
- L50 _public member_ `std::string StorageBucket = "un` — TODO: override via command line
- L51 _public member_ `std::string HttpHeaders;`
- L53 _public member_ `bool bTlsVerifyCertificate = true;` — Disabling this allows self-signed certificates
- L54 _public member_ `bool bTlsVerifySubject = true;` — Disabling this is insecure, but may be useful during development
- L55 _public member_ `ETlsRequirement TlsRequirement = ETlsRequirement::None;`
- L56 _public member_ `std::string TlsSubjectOverride;` — Use host address if empty (default)
- L57 _public member_ `std::shared_ptr<FBuffer> TlsCacert;` — Custom CA to use for server certificate validation (system root CA is used by default)
- L59 _public function_ `const std::string& GetTlsSubject() const`
- L61 _public member_ `bool bAuthenticationRequired = false;`
- L62 _public member_ `std::optional<FHostAddressAndPort> PrimaryHost;` — Optional address of the server used for login requests and other queries. If
- L65 _public member_ `bool bPreferCompression = true;` — Whether to prefer compressed encoding during bulk data transfer
- L67 _public function_ `const FHostAddressAndPort& GetPrimaryHostAddress() const`
- L69 _public member_ `uint32 RecvTimeoutSeconds = 0;`
- L71 _public member_ `uint32 MaxConnections = 8;` — Limit on concurrent connections to this server
- L73 _public function_ `bool IsValid() const`
- L75 _public prototype_ `static TResult<FRemoteDesc> FromUrl(std::string_view Url, EProtocolFlavor ProtocolFlavorHint = EProtocolFlavor::Unknown, uint32 RecvTimeoutSeconds = 0);`
- L77 _public prototype_ `FTlsClientSettings GetTlsClientSettings() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace unsync`
- L17 _variable_ `static constexpr uint16 UNSYNC_DEFAULT_PORT = 53841;` (scope `unsync`)
- L31 _prototype_ `EProtocolFlavor ProtocolFlavorFromString(std::string_view Str);` (scope `unsync`)
- L32 _prototype_ `const char* ToString(EProtocolFlavor Protocol);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncScan.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L13 _function_ `HashScan(H& Hash, const uint8* Data, uint64 DataSize, uint64 WindowSize, F& Callback)` (scope `unsync`)
- L51 _function_ `HashScan(const uint8* Data, uint64 DataSize, uint64 WindowSize, F& Callback)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncScavenger.h` (Private)


#### struct `unsync::FScavengedManifest`  
`struct FScavengedManifest`  
_L18-25_
- L20 _public member_ `bool bValid = false;`
- L21 _public member_ `FPath Root;`
- L22 _public member_ `FPath ManifestPath;`
- L23 _public member_ `FDirectoryManifest Manifest;`
- L24 _public member_ `std::vector<FPath> FileList;`

#### struct `unsync::FScavengeBlockSource`  
`struct FScavengeBlockSource`  
_L27-45_
- L39 _public function_ `bool operator==(const FScavengeBlockSource& Other) const`

#### union `unsync::FScavengeBlockSource::(anonymous)`  
``  
_L30-37_

#### struct `unsync::FScavengeBlockSource::__anon072a8b1d010a::(anonymous)`  
``  
_L32-35_

#### struct `unsync::FScavengeBlockSource::FHash`  
`struct FHash`  
_L41-44_
- L43 _public function_ `uint64 operator()(const FScavengeBlockSource& X) const`

#### class `unsync::FScavengeDatabase`  
`class FScavengeDatabase`  
_L49-74_
- L53 _public prototype_ `static FScavengeDatabase* BuildFromFileSyncTasks(const FSyncDirectoryOptions& SyncOptions, TArrayView<FFileSyncTask> AllFileTasks);`
- L55 _public function_ `const FScavengeBlockMap& GetBlockMap() const`
- L56 _public prototype_ `const FPath& GetPartialSourceFilePath(FScavengeBlockSource SourceId) const;`
- L57 _public prototype_ `FPath GetFullSourceFilePath(FScavengeBlockSource SourceId) const;`
- L58 _public function_ `const FScavengedManifest& GetScavengedManifest(FScavengeBlockSource SourceId) const`
- L59 _public prototype_ `const FFileManifest& GetFileManifest(FScavengeBlockSource SourceId) const;`
- L60 _public prototype_ `bool IsSourceValid(FScavengeBlockSource SourceId) const;`
- L63 _private member_ `std::vector<FScavengedManifest> Manifests;`
- L65 _private member_ `THashSet<FHash128> UniqueBlockHashes;`
- L66 _private member_ `THashSet<FHash128> UniqueUsableBlockHashes;`
- L69 _private member_ `FScavengeBlockMap BlockMap;` — Which local files may contain blocks with this hash

#### struct `unsync::FScavengedBuildTargetResult`  
`struct FScavengedBuildTargetResult`  
_L76-81_
- L78 _public member_ `uint64 ScavengedBytes = 0;`
- L80 _public member_ `uint64 InSituBytes = 0;` — Bytes reused on disk via block cloning. Subset of ScavengedBytes.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace unsync`
- L33 _member_ `uint32 ManifestIndex;` (scope `unsync::FScavengeBlockSource::__anon072a8b1d010a::__anon072a8b1d0208`)
- L34 _member_ `uint32 FileIndex;` (scope `unsync::FScavengeBlockSource::__anon072a8b1d010a::__anon072a8b1d0208`)
- L35 _member_ `} Data;` (scope `unsync::FScavengeBlockSource::__anon072a8b1d010a`)
- L36 _member_ `uint64 Bits = ~0ull;` (scope `unsync::FScavengeBlockSource::__anon072a8b1d010a`)
- L47 _typedef_ `using FScavengeBlockMap = std::unordered_multimap<FHash128, FScavengeBlockSource>;` (scope `unsync`)
- L83 _prototype_ `FScavengedBuildTargetResult BuildTargetFromScavengedData(FIOWriter& Output, const std::vector<FNeedBlock>& NeedList, const FScavengeDatabase& ScavengeDatabase, EStrongHashAlgorithmID StrongHasher, THashSet<FHash128>& OutScavengedBlocks);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncScheduler.h` (Private)


#### struct `unsync::FSchedulerSemaphore`  
`struct FSchedulerSemaphore`  
_L15-29_
- L19 _public prototype_ `FSchedulerSemaphore(FScheduler& InScheduler, uint32 MaxCount);`
- L21 _public function_ `bool TryAcquire()`
- L23 _public prototype_ `void Acquire(bool bAllowTaskExecution = true);`
- L24 _public prototype_ `void Release();`
- L26 _public member_ `FScheduler& Scheduler;`
- L28 _public member_ `std::counting_semaphore<UNSYNC_MAX_TOTAL_THREADS> Native;`

#### class `unsync::FScheduler`  
`class FScheduler`  
_L31-69_
- L36 _public typedef_ `using FTaskFunction = FThreadPool::FTaskFunction;`
- L38 _public member_ `static constexpr uint32 MAX_NETWORK_TASKS = 8;`
- L40 _public prototype_ `FScheduler(uint32 InNumWorkerThreads);`
- L41 _public prototype_ `~FScheduler();`
- L43 _public member_ `const uint32 NumWorkerThreads;`
- L45 _public member_ `FSchedulerSemaphore NetworkSemaphore;`
- L47 _public prototype_ `FTaskGroup CreateTaskGroup(FSchedulerSemaphore* ConcurrencyLimiter = nullptr);`
- L49 _public function_ `void TryExecuteTask()`
- L51 _public function_ `bool ExecuteTasksUntilIdle()`
- L62 _public function_ `template<typename TaskFunction> void PushTask(TaskFunction&& Fun, bool bAllowImmediateExecution = true)`
- L68 _private member_ `FThreadPool ThreadPool;`

#### struct `unsync::FTaskGroup`  
`struct FTaskGroup`  
_L71-124_
- L73 _public function_ `UNSYNC_DISALLOW_COPY_ASSIGN(FTaskGroup) template<typename F> void run(F InFunction)`
- L106 _public function_ `void wait()`
- L114 _public member_ `FThreadPool& ThreadPool;`
- L115 _public member_ `std::atomic<uint64> NumStartedTasks;`
- L116 _public member_ `std::atomic<uint64> NumFinishedTasks;`
- L117 _public member_ `FSchedulerSemaphore* Semaphore = nullptr;`
- L119 _public function_ `~FTaskGroup()`
- L123 _private function_ `FTaskGroup(FThreadPool& InThreadPool, FSchedulerSemaphore* InSemaphore) : ThreadPool(InThreadPool), Semaphore(InSemaphore)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L13 _externvar_ `extern FScheduler* GScheduler;` (scope `unsync`)
- L90 _function_ `` (scope `unsync::FTaskGroup::UNSYNC_DISALLOW_COPY_ASSIGN`)
- L128 _function_ `ParallelForEach(IT ItBegin, IT ItEnd, FT F)` (scope `unsync`)
- L135 _function_ `TaskGroup.run([&F, It]() { F(*It); });` (scope `unsync::ParallelForEach`)
- L143 _function_ `ParallelForEach(T& Container, FT F)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncSerialization.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L12 _prototype_ `bool LoadBlocks(FGenericBlockArray& OutBlocks, uint32& OutBlockSize, const FPath& Filename);` (scope `unsync`)
- L13 _prototype_ `bool SaveBlocks(const std::vector<FBlock128>& Blocks, uint32 BlockSize, const FPath& Filename);` (scope `unsync`)
- L15 _prototype_ `bool LoadDirectoryManifest(FDirectoryManifest& OutManifest, const FPath& Root, FIOReaderStream& Stream);` (scope `unsync`)
- L16 _prototype_ `bool LoadDirectoryManifest(FDirectoryManifest& OutManifest, const FPath& Root, const FPath& Filename);` (scope `unsync`)
- L18 _prototype_ `bool SaveDirectoryManifest(const FDirectoryManifest& Manifest, FVectorStreamOut& Stream);` (scope `unsync`)
- L19 _prototype_ `bool SaveDirectoryManifest(const FDirectoryManifest& Manifest, const FPath& Filename, bool bAllowInDryRun = false);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncSocket.h` (Private)


#### struct `unsync::FSocketAddress`  
`struct FSocketAddress`  
_L20-35_
- desc: opaque buffer that holds socket address
- L22 _public function_ `FSocketAddress()`
- L34 _public function_ `bool operator==(const FSocketAddress& Other) const`

#### union `unsync::FSocketAddress::(anonymous)`  
``  
_L29-32_

#### enum `unsync::ESocketSecurity`  
`enum class ESocketSecurity`  
_L70-76_
- L72 _public enumerator_ `None`
- L73 _public enumerator_ `TLSv1_2`
- L74 _public enumerator_ `TLSv1_3`
- L75 _public enumerator_ `Unknown`

#### struct `unsync::FSocketBase`  
`struct FSocketBase`  
_L80-96_
- L84 _public function_ `explicit FSocketBase(FSocketHandle InHandle) : Handle(InHandle)`
- L86 _public prototype_ `virtual ~FSocketBase();`
- L88 _public prototype_ `virtual int Send(const void* Data, size_t DataSize) = 0;`
- L89 _public prototype_ `virtual int RecvAll(void* Data, size_t DataSize) = 0;`
- L90 _public prototype_ `virtual int RecvAny(void* Data, size_t DataSize) = 0;`
- L92 _public prototype_ `virtual bool IsEncrypted() const = 0;`
- L94 _public member_ `FSocketHandle Handle = {};`
- L95 _public member_ `ESocketSecurity Security = ESocketSecurity::None;`

#### struct `unsync::FSocketRaw`  
`struct FSocketRaw : FSocketBase`  
_L98-107_
- inherits: `FSocketBase`
- L100 _public function_ `explicit FSocketRaw(FSocketHandle InHandle) : FSocketBase(InHandle)`
- L102 _public prototype_ `virtual int Send(const void* Data, size_t DataSize) override;`
- L103 _public prototype_ `virtual int RecvAll(void* Data, size_t DataSize) override;`
- L104 _public prototype_ `virtual int RecvAny(void* Data, size_t DataSize) override;`
- L106 _public function_ `virtual bool IsEncrypted() const override`

#### enum `unsync::ETlsRequirement`  
`enum class ETlsRequirement : uint8`  
_L109-113_
- L110 _public enumerator_ `None` — Use defaults for the underlying protocol
- L111 _public enumerator_ `Preferred` — Try TLS connection, but allow falling back to plaintext if server supports it
- L112 _public enumerator_ `Required` — Only allow connections with TLS

#### struct `unsync::FTlsClientSettings`  
`struct FTlsClientSettings`  
_L115-121_
- L117 _public member_ `std::string_view Subject = {};`
- L118 _public member_ `FBufferView CACert = {};`
- L119 _public member_ `bool bVerifyCertificate = true;`
- L120 _public member_ `bool bVerifySubject = true;`

#### struct `unsync::FSocketTls`  
`struct FSocketTls : FSocketBase`  
_L123-137_
- inherits: `FSocketBase`
- L125 _public prototype_ `FSocketTls(FSocketHandle InHandle, FTlsClientSettings ClientSettings);`
- L126 _public prototype_ `~FSocketTls();`
- L128 _public function_ `bool IsTlsValid() const`
- L130 _public prototype_ `virtual int Send(const void* Data, size_t DataSize) override;`
- L131 _public prototype_ `virtual int RecvAll(void* Data, size_t DataSize) override;`
- L132 _public prototype_ `virtual int RecvAny(void* Data, size_t DataSize) override;`
- L134 _public function_ `virtual bool IsEncrypted() const override`
- L136 _public member_ `tls* TlsCtx = {};`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace unsync`
- L16 _typedef_ `using FSocketHandle = uintptr_t;` (scope `unsync`)
- L18 _externvar_ `extern const FSocketHandle InvalidSocketHandle;` (scope `unsync`)
- L30 _member_ `char Data[16];` (scope `unsync::FSocketAddress::__anon8d0dd6e8010a`)
- L31 _member_ `uint64 Data64[2];` (scope `unsync::FSocketAddress::__anon8d0dd6e8010a`)
- L38 _prototype_ `std::string GetCurrentHostName();` (scope `unsync`) — Returns current host name or empty string if it could not be determined.
- L40 _prototype_ `FSocketHandle SocketListenTcp(const char* Address, uint16 Port);` (scope `unsync`)
- L41 _prototype_ `FSocketHandle SocketAccept(FSocketHandle ListenSocket);` (scope `unsync`)
- L43 _prototype_ `FSocketHandle SocketConnectTcp(const char* DestAddress, uint16 Port);` (scope `unsync`)
- L44 _prototype_ `void SocketClose(FSocketHandle Socket);` (scope `unsync`)
- L46 _prototype_ `int SocketSend(FSocketHandle Socket, const void* Data, size_t DataSize);` (scope `unsync`)
- L47 _prototype_ `int SocketRecvAll(FSocketHandle Socket, void* Data, size_t DataSize);` (scope `unsync`)
- L48 _prototype_ `int SocketRecvAny(FSocketHandle Socket, void* Data, size_t DataSize);` (scope `unsync`)
- L49 _prototype_ `FSocketAddress SocketMakeAddress(const char* Address, uint16 Port);` (scope `unsync`)
- L51 _prototype_ `bool SocketSetRecvTimeout(FSocketHandle Socket, uint32 Seconds);` (scope `unsync`)
- L53 _prototype_ `bool SocketValid(FSocketHandle Socket);` (scope `unsync`)
- L57 _function_ `SocketSendT(FSocketHandle Socket, const T& Data)` (scope `unsync`)
- L65 _function_ `SocketRecvT(FSocketHandle Socket, T& Data)` (scope `unsync`)
- L78 _prototype_ `const char* ToString(ESocketSecurity Security);` (scope `unsync`)
- L141 _function_ `SocketSendT(FSocketBase& Socket, const T& Data)` (scope `unsync`)
- L149 _function_ `SocketRecvT(FSocketBase& Socket, T& Data)` (scope `unsync`)
- L155 _function_ `SocketSend(FSocketBase& Socket, const void* Data, size_t DataSize)` (scope `unsync`)
- L161 _function_ `SocketRecvAll(FSocketBase& Socket, void* Data, size_t DataSize)` (scope `unsync`)
- L167 _function_ `SocketRecvAny(FSocketBase& Socket, void* Data, size_t DataSize)` (scope `unsync`)
- L173 _function_ `SocketValid(FSocketBase& Socket)` (scope `unsync`)
- L180 _function_ `SendStruct(FSocketBase& Socket, const T& Data)` (scope `unsync`)
- L189 _prototype_ `bool SendBuffer(FSocketBase& Socket, const FBufferView& Data);` (scope `unsync`)
- L190 _prototype_ `bool SendBuffer(FSocketBase& Socket, const FBuffer& Data);` (scope `unsync`)
- L194 _function_ `RecvStruct(FSocketBase& Socket, const T& Data)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncSource.h` (Private)


#### enum `unsync::ESourceType`  
`enum class ESourceType : uint8`  
_L10-15_
- L11 _public enumerator_ `Unknown`
- L12 _public enumerator_ `FileSystem`
- L13 _public enumerator_ `Server`
- L14 _public enumerator_ `ServerWithManifestId`

#### struct `unsync::FSourcePath`  
`struct FSourcePath`  
_L23-29_
- L25 _public member_ `ESourceType Type = ESourceType::Unknown;`
- L26 _public member_ `std::string Location;` — utf-8
- L28 _public function_ `bool operator==(const FSourcePath& Other) const`

#### struct `unsync::FDfsStorageInfo`  
`struct FDfsStorageInfo`  
_L32-38_
- desc: Returns a list of alternative DFS paths for a given root
- L34 _public member_ `std::wstring Server;`
- L35 _public member_ `std::wstring Share;`
- L37 _public function_ `bool IsValid() const`

#### struct `unsync::FDfsMirrorInfo`  
`struct FDfsMirrorInfo`  
_L39-43_
- L41 _public member_ `std::wstring Root;`
- L42 _public member_ `std::vector<FDfsStorageInfo> Storages;`

#### struct `unsync::FDfsAlias`  
`struct FDfsAlias`  
_L46-50_
- L48 _public member_ `FPath Source;`
- L49 _public member_ `FPath Target;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L18 _function_ `IsFileSystemSource(ESourceType SourceType)` (scope `unsync`)
- L44 _prototype_ `FDfsMirrorInfo DfsEnumerate(const FPath& Root);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncTarget.h` (Private)


#### struct `unsync::FBuildTargetResult`  
`struct FBuildTargetResult`  
_L16-22_
- L18 _public member_ `bool bSuccess = false;`
- L19 _public member_ `uint64 SourceBytes = 0;`
- L20 _public member_ `uint64 BaseBytes = 0;`
- L21 _public member_ `uint64 InSituBytes = 0;`

#### struct `unsync::FBuildTargetParams`  
`struct FBuildTargetParams`  
_L24-38_
- L26 _public member_ `EStrongHashAlgorithmID StrongHasher;`
- L27 _public member_ `FProxyPool* ProxyPool = nullptr;`
- L28 _public member_ `FBlockCache* BlockCache = nullptr;`
- L29 _public member_ `FScavengeDatabase* ScavengeDatabase = nullptr;`
- L37 _public member_ `ESourceType SourceType = ESourceType::File;`

#### enum `unsync::FBuildTargetParams::ESourceType`  
`enum class ESourceType`  
_L31-35_
- L32 _public enumerator_ `File`
- L33 _public enumerator_ `Patch`
- L34 _public enumerator_ `Server`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace unsync`
- L40 _prototype_ `FBuildTargetResult BuildTarget(FIOWriter& Result, FIOReader& Source, FIOReader& Base, const FNeedList& NeedList, const FBuildTargetParams& Params);` (scope `unsync`)
- L46 _prototype_ `FBuffer BuildTargetBuffer(FIOReader& SourceProvider, FIOReader& BaseProvider, const FNeedList& NeedList, const FBuildTargetParams& Params);` (scope `unsync`)
- L48 _prototype_ `FBuffer BuildTargetBuffer(const uint8* SourceData, uint64 SourceSize, const uint8* BaseData, uint64 BaseSize, const FNeedList& NeedList, const FBuildTargetParams& Params);` (scope `unsync`)
- L55 _prototype_ `FBuffer BuildTargetWithPatch(const uint8* PatchData, uint64 PatchSize, const uint8* BaseData, uint64 BaseSize);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncTest.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L9 _prototype_ `void RunTests(const std::string& Preset);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncThread.h` (Private)


#### struct `unsync::FThreadElectScope`  
`struct FThreadElectScope`  
_L27-47_
- L29 _public member_ `const bool bValue;` — NOLINT
- L30 _public member_ `const bool bCondition;` — NOLINT
- L31 _public member_ `std::atomic<uint64>& Counter;`
- L32 _public function_ `FThreadElectScope(std::atomic<uint64>& InCounter, bool bInCondition) : bValue(bInCondition && (InCounter.fetch_add(1) == 0)) , bCondition(bInCondition) , Counter(InCounter)`
- L38 _public function_ `~FThreadElectScope()`
- L46 _public function_ `operator bool() const`

#### struct `unsync::FThreadLogConfig`  
`struct FThreadLogConfig`  
_L49-70_
- L51 _public function_ `FThreadLogConfig() : ParentThreadIndent(GLogIndent), bParentThreadVerbose(GLogVerbose)`
- L54 _public member_ `uint32 ParentThreadIndent;`
- L55 _public member_ `bool bParentThreadVerbose;`
- L56 _public member_ `std::atomic<uint64> NumActiveVerboseLogThreads = {};`

#### struct `unsync::FThreadLogConfig::FScope`  
`struct FScope`  
_L58-69_
- L60 _public function_ `FScope(FThreadLogConfig& Parent) : AllowVerbose(Parent.NumActiveVerboseLogThreads, Parent.bParentThreadVerbose) , VerboseScope(AllowVerbose.bValue) , IndentScope(Parent.ParentThreadIndent, true)`
- L66 _public member_ `FThreadElectScope AllowVerbose;`
- L67 _public member_ `FLogVerbosityScope VerboseScope;`
- L68 _public member_ `FLogIndentScope IndentScope;`

#### class `unsync::FThreadPool`  
`class FThreadPool`  
_L74-111_
- L78 _public typedef_ `using FTaskFunction = std::function< void()>;`
- L81 _public prototype_ `FThreadPool() = default;`
- L82 _public prototype_ `~FThreadPool();`
- L86 _public prototype_ `void StartWorkers(uint32 NumWorkers);` — Launches worker threads until total started worker count reaches NumWorkers. Does nothing if the number of already launched workers is lower than given value.
- L89 _public prototype_ `void PushTask(FTaskFunction&& Fun, bool bAllowImmediateExecution = true);` — Adds a task to the task list
- L93 _public function_ `bool TryExecuteTask()` — Try to pop the next task from the list and execute it on the current thread. Returns false if list is empty, which may happen if worker threads have picked up the tasks already.
- L95 _public function_ `uint32 NumWorkerThreads() const`
- L100 _private prototype_ `bool DoWorkInternal(bool bWaitForSignal);` — Try to execute a task and return whether there may be more tasks to run
- L102 _private prototype_ `FTaskFunction PopTask(bool bWaitForSignal);`
- L104 _private member_ `std::vector<std::thread> Threads;`
- L105 _private member_ `std::vector<FTaskFunction> Tasks;`
- L107 _private member_ `std::mutex Mutex;`
- L108 _private member_ `std::condition_variable WakeCondition;`
- L109 _private member_ `std::atomic<bool> bShutdown;`
- L110 _private member_ `std::atomic<uint64> NumRunningTasks;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace unsync`
- L21 _variable_ `static constexpr uint32 UNSYNC_MAX_TOTAL_THREADS = 64;` (scope `unsync`)
- L23 _externvar_ `extern uint32 GMaxThreads;` (scope `unsync`)
- L72 _prototype_ `void SchedulerSleep(uint32 Milliseconds);` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncUtil.h` (Private)


#### struct `unsync::FRange`  
`struct FRange`  
_L77-81_
- L79 _public member_ `uint64 Offset = 0;`
- L80 _public member_ `uint64 Size = 0;`

#### struct `unsync::FTimingLogger`  
`struct FTimingLogger`  
_L83-93_
- L85 _public member_ `bool bEnabled = false;`
- L87 _public member_ `std::string Name;`
- L88 _public member_ `ELogLevel LogLevel;`
- L90 _public prototype_ `FTimingLogger(const char* InName, ELogLevel InLogLevel, bool InEnabled = true);`
- L91 _public prototype_ `~FTimingLogger();`
- L92 _public prototype_ `void Finish();`

#### struct `unsync::TArrayView`  
`template<typename T> struct TArrayView`  
_L206-215_
- L208 _public member_ `const T* BeginPtr = nullptr;`
- L209 _public member_ `const T* EndPtr = nullptr;`
- L211 _public function_ `const T* begin() const` — NOLINT
- L212 _public function_ `const T* end() const` — NOLINT
- L214 _public function_ `size_t Size() const`

#### struct `unsync::TBitArrayInfo`  
`template<typename StorageT> struct TBitArrayInfo`  
_L339-345_
- L341 _public member_ `static constexpr size_t ElemSizeInBits = sizeof(StorageT) * 8;`
- L342 _public member_ `const uint64 ElemIndex;`
- L343 _public member_ `const StorageT BitMask;`
- L344 _public function_ `TBitArrayInfo(uint64 BitIndex) : ElemIndex(BitIndex / ElemSizeInBits), BitMask(StorageT(1) << (BitIndex % ElemSizeInBits))`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace unsync`
- L29 _typedef_ `using FTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;` (scope `unsync`)
- L30 _typedef_ `using FTimeDuration = std::chrono::duration<double>;` (scope `unsync`)
- L32 _function_ `constexpr auto operator""_KB(unsigned long long X) -> uint64` (scope `unsync`)
- L36 _function_ `constexpr auto operator""_MB(unsigned long long X) -> uint64` (scope `unsync`)
- L40 _function_ `constexpr auto operator""_GB(unsigned long long X) -> uint64` (scope `unsync`)
- L46 _function_ `TimePointNow()` (scope `unsync`)
- L52 _function_ `DurationSec(FTimePoint TimeBegin, FTimePoint TimeEnd)` (scope `unsync`)
- L58 _function_ `DurationMs(FTimePoint TimeBegin, FTimePoint TimeEnd)` (scope `unsync`)
- L64 _function_ `CalcChunkSize(uint64 ChunkIndex, uint64 ChunkSize, uint64 TotalDataSize)` (scope `unsync`)
- L72 _function_ `MakeU64(uint32 H, uint32 L)` (scope `unsync`)
- L96 _function_ `SizeMb(double Size)` (scope `unsync`)
- L102 _function_ `SizeMb(uint64 Size)` (scope `unsync`)
- L108 _function_ `DivUp(uint64 Num, uint64 Den)` (scope `unsync`)
- L114 _function_ `NextPow2(uint32 V)` (scope `unsync`)
- L126 _prototype_ `std::string BytesToHexString(const uint8* Data, uint64 Size);` (scope `unsync`)
- L129 _prototype_ `uint64 BytesToHexChars(char* Output, uint64 OutputSize, const uint8* Input, uint64 InputSize);` (scope `unsync`) — Converts input bytes to hexadecimal ACII. Returns how many characters were written to output.
- L130 _prototype_ `uint64 BytesToHexChars(wchar_t* Output, uint64 OutputSize, const uint8* Input, uint64 InputSize);` (scope `unsync`)
- L134 _function_ `HashToHexString(const HashType& Hash)` (scope `unsync`)
- L139 _prototype_ `std::wstring ConvertUtf8ToWide(std::string_view StringUtf8);` (scope `unsync`)
- L140 _prototype_ `std::string ConvertWideToUtf8(std::wstring_view StringWide);` (scope `unsync`)
- L141 _prototype_ `void ConvertWideToUtf8(std::wstring_view StringWide, std::string& Result);` (scope `unsync`)
- L143 _prototype_ `std::string_view AsStringView(const FBuffer& Buffer);` (scope `unsync`)
- L146 _function_ `ToString(const std::wstring_view WideStringView)` (scope `unsync`)
- L152 _function_ `ToString(const std::string_view StringView)` (scope `unsync`)
- L157 _prototype_ `std::string ToString(const FPath& Path);` (scope `unsync`)
- L159 _prototype_ `std::string StringToLower(std::string_view Input);` (scope `unsync`)
- L160 _prototype_ `std::wstring StringToLower(std::wstring_view Input);` (scope `unsync`)
- L161 _prototype_ `std::wstring StringToUpper(std::wstring_view Input);` (scope `unsync`)
- L163 _prototype_ `std::string StringEscape(const std::string_view Input);` (scope `unsync`)
- L165 _prototype_ `bool StringEquals(const std::string_view A, const std::string_view B, bool bCaseSensitive = true);` (scope `unsync`)
- L166 _prototype_ `bool StringStartsWith(const std::string_view String, const std::string_view Prefix, bool bCaseSensitive = true);` (scope `unsync`)
- L169 _function_ `UncasedStringEquals(const std::string_view A, const std::string_view B)` (scope `unsync`)
- L175 _function_ `IsAsciiAlphabetCharacter(const char C)` (scope `unsync`)
- L181 _function_ `IsAsciiNumericCharacter(const char C)` (scope `unsync`)
- L187 _function_ `IsAsciiAlphaNumericCharacter(const char C)` (scope `unsync`)
- L192 _prototype_ `std::vector<std::string_view> SplitByAny(std::string_view String, const char* SeparatorCharacters);` (scope `unsync`)
- L195 _function_ `SplitBy(std::string_view String, char SeparatorCharacter)` (scope `unsync`)
- L203 _prototype_ `FPath GetUniversalPath(const FPath& Path);` (scope `unsync`) — Takes a drive-based path (e.g. P:/Foo/Bar) and converts it to universal form (e.g. //server/Foo/Bar), if possible. Otherwise, returns original path.
- L219 _function_ `MakeView(const T* Ptr, size_t Count)` (scope `unsync`)
- L229 _function_ `MakeView(const std::vector<T>& Container)` (scope `unsync`)
- L235 _function_ `AlignDownToMultiplePow2(uint64 X, uint64 MultiplePow2)` (scope `unsync`)
- L241 _function_ `AlignUpToMultiplePow2(uint64 X, uint64 MultiplePow2)` (scope `unsync`)
- L263 _function_ `CheckedNarrow(T X)` (scope `unsync`)
- L281 _function_ `Xorshift32(uint32& State)` (scope `unsync`)
- L292 _function_ `FillRandomBytes(uint8* Output, uint64 Size, uint32 Seed)` (scope `unsync`)
- L302 _function_ `_BitScanReverse64(unsigned long* Index, uint64 Mask)` (scope `unsync`)
- L315 _function_ `FloorLog264(uint64 X)` (scope `unsync`)
- L323 _function_ `CountLeadingZeros32(uint32 X)` (scope `unsync`)
- L331 _function_ `CountLeadingZeros64(uint64 X)` (scope `unsync`)
- L349 _function_ `BitArrayGet(const StorageT* Storage, uint64 BitIndex)` (scope `unsync`)
- L357 _function_ `BitArraySet(StorageT* Storage, uint64 BitIndex, bool bValue)` (scope `unsync`)
- L370 _prototype_ `FPath NormalizeFilenameWide(std::wstring_view InFilename);` (scope `unsync`)
- L371 _prototype_ `FPath NormalizeFilenameUtf8(std::string_view InFilename);` (scope `unsync`)
- L372 _prototype_ `FPath GetAbsoluteNormalPath(const FPath& InPath);` (scope `unsync`)
- L374 _prototype_ `const FBuffer& GetSystemRootCerts();` (scope `unsync`)
- L378 _function_ `ToStringView(const T& Buf)` (scope `unsync`)
- L384 _function_ `ToString(const fmt::memory_buffer& Buf)` (scope `unsync`)
- L390 _function_ `Append(fmt::memory_buffer& Buf, std::string_view V)` (scope `unsync`)
- L396 _function_ `Append(fmt::memory_buffer& Buf, const char* S)` (scope `unsync`)
- L401 _prototype_ `void OpenUrlInDefaultBrowser(const char* Address);` (scope `unsync`)
- L403 _prototype_ `FPath GetUserHomeDirectory();` (scope `unsync`)
- L405 _prototype_ `FHash256 GetAnonymizedMachineId(std::string_view Salt = {});` (scope `unsync`)
- L406 _prototype_ `std::string GetAnonymizedMachineIdString(std::string_view Salt = {});` (scope `unsync`)
- L409 _prototype_ `std::string FormatSystemErrorMessage(int32 ErrorCode);` (scope `unsync`) — Returns string in format 'Error code 123: Some description.`
- L411 _prototype_ `bool LooksLikeUrl(std::string_view Str);` (scope `unsync`)
- L412 _prototype_ `bool LooksLikeHash160(const std::string_view Str);` (scope `unsync`)
- L413 _prototype_ `bool LooksLikeHash160(const std::wstring_view Str);` (scope `unsync`)
- L416 _prototype_ `void FormatJsonKeyValueStr(std::wstring& Output, std::wstring_view K, std::wstring_view V, std::wstring_view Suffix = {});` (scope `unsync`) — Json formatting helpers
- L417 _prototype_ `void FormatJsonKeyValueStr(std::string& Output, std::string_view K, std::string_view V, std::string_view Suffix = {});` (scope `unsync`)
- L418 _prototype_ `void FormatJsonKeyValueUInt(std::wstring& Output, std::wstring_view K, uint64 V, std::wstring_view Suffix = {});` (scope `unsync`)
- L419 _prototype_ `void FormatJsonKeyValueUInt(std::string& Output, std::string_view K, uint64 V, std::string_view Suffix = {});` (scope `unsync`)
- L420 _prototype_ `void FormatJsonKeyValueBool(std::wstring& Output, std::wstring_view K, bool V, std::wstring_view Suffix = {});` (scope `unsync`)
- L421 _prototype_ `void FormatJsonKeyValueBool(std::string& Output, std::string_view K, bool V, std::string_view Suffix = {});` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncVarInt.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace unsync`
- L11 _function_ `MeasureVarUint(uint64 X)` (scope `unsync`)
- L17 _function_ `MeasureVarUint(const void* X)` (scope `unsync`)
- L23 _function_ `WriteVarUint(uint64 X, void* Output)` (scope `unsync`)
- L61 _function_ `ReadVarUint(const void* Data, uint32& OutSize)` (scope `unsync`)

### `Source/Programs/Unsync/Private/UnsyncVersion.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace unsync`
- L10 _prototype_ `GetVersionString();` (scope `unsync`)
