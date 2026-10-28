# Developer / MetalShaderFormat

- module root: `Source/Developer/Apple/MetalShaderFormat`
- headers: 5; symbols: 145
- symbol kinds: class=3, delegate=2, enum=3, enumerator=11, function=12, member=70, prototype=25, struct=6, typedef=2, union=1, variable=10
- PrivateDependencyModuleNames: Core, FileUtilities, HlslParser, RHI, RenderCore, ShaderCompilerCommon, ShaderPreprocessor, Shaders
- PrivateIncludePathModuleNames: TargetPlatform
- PublicIncludePathModuleNames: MetalRHI

### `Source/Developer/Apple/MetalShaderFormat/Private/MetalBackend.h` (Private)


#### enum `EMetalGPUSemantics`  
`enum EMetalGPUSemantics`  
_L9-14_
- L11 _public enumerator_ `EMetalGPUSemanticsMobile` — Mobile shaders for TBDR GPUs
- L12 _public enumerator_ `EMetalGPUSemanticsTBDRDesktop` — Desktop shaders for TBDR GPUs
- L13 _public enumerator_ `EMetalGPUSemanticsImmediateDesktop` — Desktop shaders for Immediate GPUs

#### struct `SDMARange`  
`struct SDMARange`  
_L21-39_
- L23 _public member_ `unsigned SourceCB;`
- L24 _public member_ `unsigned SourceOffset;`
- L25 _public member_ `unsigned Size;`
- L26 _public member_ `unsigned DestCBIndex;`
- L27 _public member_ `unsigned DestCBPrecision;`
- L28 _public member_ `unsigned DestOffset;`
- L30 _public function_ `bool operator <(SDMARange const & Other) const`

#### Free symbols / members of external scopes

- L17 _variable_ `static const int32 MaxMetalSamplers = 16;` — Metal supports 16 across all HW
- L40 _typedef_ `typedef std::list<SDMARange> TDMARangeList;`
- L41 _typedef_ `typedef std::map<unsigned, TDMARangeList> TCBDMARangeMap;`
- L44 _function_ `static void InsertRange( TCBDMARangeMap& CBAllRanges, unsigned SourceCB, unsigned SourceOffset, unsigned Size, unsigned DestCBIndex, unsigned DestCBPrecision, unsigned DestOffset )`

### `Source/Developer/Apple/MetalShaderFormat/Private/MetalCompileShaderMSC.h` (Private)


#### class `FMetalCompileShaderMSC`  
`class FMetalCompileShaderMSC`  
_L11-28_
- L14 _public prototype_ `static void DoCompileMetalShader( const FShaderCompilerInput& Input, const FShaderParameterParser& ShaderParameterParser, FShaderCompilerOutput& Output, const FString& InPreprocessedShader, uint32 VersionEnum, EMetalGPUSemantics Semantics, uint32 MaxUnrollLoops, EShaderFrequency Frequency, bool bDumpDebugInfo, const FString& Standard, const FString& MinOSVersion, FMetalBindlessShaderInfo& ShaderInfo );`

### `Source/Developer/Apple/MetalShaderFormat/Private/MetalCompileShaderSPIRV.h` (Private)


#### class `FMetalCompileShaderSPIRV`  
`class FMetalCompileShaderSPIRV`  
_L9-25_
- L12 _public prototype_ `static void DoCompileMetalShader( const FShaderCompilerInput& Input, const FShaderParameterParser& ShaderParameterParser, FShaderCompilerOutput& Output, const FString& InPreprocessedShader, uint32 VersionEnum, EMetalGPUSemantics Semantics, uint32 MaxUnrollLoops, EShaderFrequency Frequency, bool bDumpDebugInfo, const FString& Standard, const FString& MinOSVersion );`

### `Source/Developer/Apple/MetalShaderFormat/Private/MetalShaderCompiler.h` (Private)


#### struct `FMetalShaderBytecodeJob`  
`struct FMetalShaderBytecodeJob`  
_L13-41_
- L15 _public member_ `FName ShaderFormat;`
- L16 _public member_ `FString Defines;`
- L17 _public member_ `FString TmpFolder;`
- L18 _public member_ `FString InputFile;`
- L19 _public member_ `FString InputPCHFile;`
- L20 _public member_ `FString OutputFile;`
- L21 _public member_ `FString OutputObjectFile;`
- L22 _public member_ `FString CompilerVersion;`
- L23 _public member_ `FString MinOSVersion;`
- L24 _public member_ `FString PreserveInvariance;`
- L25 _public member_ `FString DebugInfo;`
- L26 _public member_ `FString MathMode;`
- L27 _public member_ `FString Standard;`
- L28 _public member_ `FString IncludeDir;`
- L29 _public member_ `FString ModuleCacheDirectory;`
- L30 _public member_ `uint32 SourceCRCLen;`
- L31 _public member_ `uint32 SourceCRC;`
- L32 _public member_ `bool bUseNativeShaderLibrary;`
- L33 _public member_ `bool bCompileAsPCH;`
- L34 _public member_ `bool bOptimizeForSize;`
- L35 _public member_ `bool bStripIndividualMetalLibs;`
- L37 _public member_ `FString Message;`
- L38 _public member_ `FString Results;`
- L39 _public member_ `FString Errors;`
- L40 _public member_ `int32 ReturnCode;`

#### struct `FMetalShaderPreprocessed`  
`struct FMetalShaderPreprocessed`  
_L43-54_
- L45 _public member_ `FString NativePath;`
- L46 _public member_ `TArray<uint8> OutputFile;`
- L47 _public member_ `TArray<uint8> ObjectFile;`

#### struct `FMetalShaderOutputMetaData`  
`struct FMetalShaderOutputMetaData`  
_L56-62_
- L58 _public member_ `uint32 InvariantBuffers = 0;`
- L59 _public member_ `uint32 TypedBuffers = 0;`
- L60 _public member_ `uint32 TypedUAVs = 0;`
- L61 _public member_ `uint32 ConstantBuffers = 0;`

#### Free symbols / members of external scopes

- L49 _function_ `friend FArchive& operator<<( FArchive& Ar, FMetalShaderPreprocessed& Info )`
- L65 _prototype_ `bool PatchSpecialTextureInHlslSource(FAnsiString& SourceData, uint32* OutSubpassInputsDim, uint32 SubpassInputDimCount);` — Replace the special texture "gl_LastFragData" to a native subpass fetch operation. Returns true if the input source has been modified.

### `Source/Developer/Apple/MetalShaderFormat/Private/MetalShaderFormat.h` (Private)


#### enum `EAppleSDKType`  
`enum EAppleSDKType`  
_L15-20_
- desc: IOS and TVOS use the mobile toolchain.
- L17 _public enumerator_ `AppleSDKMac`
- L18 _public enumerator_ `AppleSDKMobile`
- L19 _public enumerator_ `AppleSDKCount`

#### class `FMetalCompilerToolchain`  
`class FMetalCompilerToolchain`  
_L35-278_
- L63 _public prototype_ `void Init();` — Initializes this toolchain.
- L65 _public prototype_ `void Teardown();` — Tears down the toolchain
- L68 _public prototype_ `bool CompileMetalShader(struct FMetalShaderBytecodeJob& Job, struct FMetalShaderBytecode& Output) const;` — Takes a Job and compiles a shader. Produces .air and .metallib
- L71 _public prototype_ `bool StripMetalLib(EAppleSDKType SDK, const FString& InMetalLibFilePath, const FString& OutMetalLibFilePath, const bool bStripTypes) const;` — Strips the Metal lib of debug symbols and optionally type info
- L74 _public prototype_ `bool ExecGenericCommand(const TCHAR* Command, const TCHAR* Params, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr, bool bIsConsoleApp = false) const;` — Executes 'Command' on the local machine
- L76 _public prototype_ `bool ExecMetalFrontend(EAppleSDKType SDK, const TCHAR* Parameters, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr) const;` — Executes the metal frontend compiler for 'SDK' on the local or remote machine, depending on the current configuration
- L78 _public prototype_ `bool ExecMetalLib(EAppleSDKType SDK, const TCHAR* Parameters, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr) const;` — Executes metallib for 'SDK' on the local or remote machine, depending on configuration
- L80 _public prototype_ `bool ExecMetalAr(EAppleSDKType SDK, const TCHAR* ScriptFile, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr) const;` — Executes metal-ar for 'SDK' on the local or remote machine, depending on configuration
- L82 _public prototype_ `bool ExecMetalPack(EAppleSDKType SDK, const TCHAR* Parameters, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr) const;` — Executes metal-pack for 'SDK' on the local or remote machine, depending on configuration
- L83 _public prototype_ `bool ExecMetalStrip(EAppleSDKType SDK, const TCHAR* Parameters, int32* OutReturnCode, FString* OutStdOut, FString* OutStdErr) const;`
- L86 _public function_ `bool IsCompilerAvailable() const` — This toolchain is set up correctly and ready to use.
- L92 _public prototype_ `PackedVersion GetCompilerVersion(EShaderPlatform Platform) const;` — The version of the compiler, given by metal -v
- L95 _public prototype_ `PackedVersion GetTargetVersion(EShaderPlatform Platform) const;` — The AIR target version, given by metal -v
- L98 _public prototype_ `const FString& GetCompilerVersionString(EShaderPlatform Platform) const;` — The first line of metal -v, which gives the version
- L102 _public function_ `const FString& GetLocalTempDir() const` — Fully qualified path to a process-specific temporary directory on the local machine. This directory will be destroyed when the toolchain is destroyed
- L125 _public function_ `static const FMetalCompilerToolchain* Get()` — The Singleton Toolchain object
- L131 _public prototype_ `static void CreateAndInit();` — Creates and intializes the toolchain for this process
- L134 _public prototype_ `static void Destroy();` — Cleans up and deletes the toolchain for this process
- L137 _public function_ `static bool IsMobile(const EShaderPlatform Platform)` — True if Platform indicates a mobile (ios, tvos) platform
- L148 _public function_ `static bool IsMobile(const FName& Format)` — True if Format is the FName of a mobile shader format (ios, tvos)
- L155 _public function_ `static bool IsTVOS(const EShaderPlatform Platform)` — True if Platform is a tvos platform
- L161 _public prototype_ `static EShaderPlatform MetalShaderFormatToLegacyShaderPlatform(FName ShaderFormat);` — Converts an FName ShaderFormat to the equivalent ShaderPlatform
- L163 _public function_ `static EAppleSDKType MetalShaderPlatformToSDK(EShaderPlatform Platform)` — Returns the SDK (Mac, Mobile) to use in order to compile shaders of Platform
- L173 _public function_ `static EAppleSDKType MetalFormatToSDK(FName ShaderFormat)` — Returns the SDK (Mac, Mobile) to use in order to compile shaders of ShaderFormat
- L182 _public function_ `static const FString& SDKToString(EAppleSDKType SDK)`
- L192 _public member_ `static FString MetalExtention;` — The extension of a metal shader - .metal
- L194 _public member_ `static FString MetalLibraryExtension;` — The extension of a packed metal library - .metallib
- L196 _public member_ `static FString MetalObjectExtension;` — The extension of the metal IR objects - .air
- L198 _public member_ `static FString MetalFrontendBinary;` — The name of the metal frontend compiler - metal
- L200 _public member_ `static FString MetalArBinary;` — The name of the metal-ar archiver - metal-ar
- L202 _public member_ `static FString MetalLibraryBinary;` — The name of the metal binary packager - metallib
- L204 _public member_ `static FString MetalPackBinary;` — The name of metal-pack
- L206 _public member_ `static FString MetalStripBinary;` — The name of metal-strip
- L209 _public member_ `static FString MetalMapExtension;` — The extension of the mapping from shader to metallib for shared material libraries - .metalmap
- L212 _public member_ `static FString XcrunPath;` — The path to xcrun
- L214 _public member_ `static FString MetalMacSDK;` — The string xcrun expects for the mac SDK - macos
- L216 _public member_ `static FString MetalMobileSDK;` — The string xcrun expects for the mobile SDKs - iphoneos
- L218 _public member_ `static FString WindowsToolchainVersion;` — The version of the windows native metal compiler
- L220 _public member_ `static FString WindowsToolchainSubversion;` — The subversion needed for the windows native metal compiler after version 5.0
- L224 _private member_ `bool bToolchainAvailable : 1;` — Members
- L225 _private member_ `bool bToolchainBinariesPresent : 1;`
- L228 _private member_ `bool bSkipPCH : 1;` — In this implementation we will also skip PCH generation but this is left in case we'd like to turn it on in the future. Probably needs serious testing as to whether it actually works and actually gains us anything.
- L231 _private member_ `FString MetalStandardLibraryPath[AppleSDKCount];` — The path to metal_stdlib
- L238 _private member_ `FString MetalFrontendBinaryCommand[AppleSDKCount];` — On Windows, or when using an override on Mac, we will need to figure out the full path to each The command string to invoke 'metal'
- L240 _private member_ `FString MetalLibBinaryCommand[AppleSDKCount];` — The command string to invoke 'metallib'
- L242 _private member_ `FString MetalArBinaryCommand[AppleSDKCount];` — The command string to invoke 'metal-ar'
- L245 _private member_ `FString MetalPackBinaryCommand[AppleSDKCount];` — The command string to invoke 'metal-pack'
- L247 _private member_ `FString MetalStripBinaryCommand[AppleSDKCount];` — The command string to invoke 'metal-strip'
- L250 _private member_ `FString MetalCompilerVersionString[AppleSDKCount];` — The compiler version string, parsed out of metal -v
- L252 _private member_ `PackedVersion MetalCompilerVersion[AppleSDKCount];` — The compiler version number, parsed out of metal -v. This is the first number that occurs - not the number that is (metalfe-###)
- L254 _private member_ `PackedVersion MetalTargetVersion[AppleSDKCount];` — The compiler target version, parsed out of metal -v. This is the number from 'Target: air64-apple-darwin##.##.##'
- L259 _private member_ `mutable FString LocalTempFolder;` — mutable :(
- L263 _private member_ `static FMetalCompilerToolchain* Singleton;` — Statics The one and only toolchain
- L267 _private prototype_ `EMetalToolchainStatus DoMacNativeSetup();` — fills out the paths and sets up the toolchain for compilation on the local mac
- L271 _private prototype_ `EMetalToolchainStatus DoWindowsSetup();` — Sets up toolchain for compilation on windows.
- L275 _private prototype_ `EMetalToolchainStatus FetchCompilerVersion();` — Parses and verifies the version of the compiler. Fetched via metal -v
- L277 _private prototype_ `EMetalToolchainStatus FetchMetalStandardLibraryPath();` — Parses and verifies where metal_stdlib is located.

#### enum `FMetalCompilerToolchain::EMetalToolchainStatus`  
`enum class EMetalToolchainStatus : int32`  
_L38-45_
- L40 _public enumerator_ `Success`
- L41 _public enumerator_ `ToolchainNotFound`
- L42 _public enumerator_ `CouldNotParseCompilerVersion`
- L43 _public enumerator_ `CouldNotParseTargetVersion`
- L44 _public enumerator_ `CouldNotFindMetalStdLib`

#### struct `FMetalCompilerToolchain::PackedVersion`  
`struct PackedVersion`  
_L48-60_

#### union `FMetalCompilerToolchain::PackedVersion::(anonymous)`  
``  
_L51-59_

#### struct `FMetalCompilerToolchain::PackedVersion::__anon8bccb801010a::(anonymous)`  
``  
_L53-57_

#### Free symbols / members of external scopes

- L22 _variable_ `static FName NAME_SF_METAL_ES3_1_IOS(TEXT("SF_M`
- L23 _variable_ `static FName NAME_SF_METAL_SM5_IOS(TEXT("SF_M`
- L24 _variable_ `static FName NAME_SF_METAL_SM6_IOS(TEXT("SF_M`
- L25 _variable_ `static FName NAME_SF_METAL_ES3_1_TVOS(TEXT("SF_M`
- L26 _variable_ `static FName NAME_SF_METAL_SM5_TVOS(TEXT("SF_M`
- L27 _variable_ `static FName NAME_SF_METAL_SM5(TEXT("SF_M`
- L28 _variable_ `static FName NAME_SF_METAL_SM6(TEXT("SF_M`
- L29 _variable_ `static FName NAME_SF_METAL_SIM(TEXT("SF_M`
- L30 _variable_ `static FName NAME_SF_METAL_ES3_1(TEXT("SF_M`
- L32 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalCompilerSetup, Log, All);`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalCompilerSetup, Log, All);`
- L33 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalShaderCompiler, Log, All);`
- L33 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalShaderCompiler, Log, All);`
- L54 _member_ `int32 Major : 16;` (scope `FMetalCompilerToolchain::PackedVersion::__anon8bccb801010a::__anon8bccb8010208`)
- L55 _member_ `int32 Minor : 8;` (scope `FMetalCompilerToolchain::PackedVersion::__anon8bccb801010a::__anon8bccb8010208`)
- L56 _member_ `int32 Patch : 8;` (scope `FMetalCompilerToolchain::PackedVersion::__anon8bccb801010a::__anon8bccb8010208`)
- L58 _member_ `int32 Version;` (scope `FMetalCompilerToolchain::PackedVersion::__anon8bccb801010a`)
