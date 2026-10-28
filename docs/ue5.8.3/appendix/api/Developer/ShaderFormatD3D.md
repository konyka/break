# Developer / ShaderFormatD3D

- module root: `Source/Developer/Windows/ShaderFormatD3D`
- headers: 2; symbols: 54
- symbol kinds: delegate=1, enum=2, enumerator=7, function=16, member=19, prototype=5, struct=3, typedef=1
- PrivateDependencyModuleNames: Core, HlslParser, RenderCore, ShaderCompilerCommon, ShaderPreprocessor
- PrivateIncludePathModuleNames: D3D11RHI, D3D12RHI, Shaders, TargetPlatform

### `Source/Developer/Windows/ShaderFormatD3D/Private/D3DShaderCompiler.inl` (Private)


#### struct `FD3DShaderCompileData`  
`struct FD3DShaderCompileData`  
_L9-35_
- L11 _public function_ `FD3DShaderCompileData() : UsedUniformBufferSlots(false, 32)`
- L16 _public member_ `TArray<FShaderCodeVendorExtension> VendorExtensions;`
- L17 _public member_ `TArray<FString> ShaderInputs;`
- L18 _public member_ `TArray<FString> UniformBufferNames;`
- L19 _public member_ `TBitArray<> UsedUniformBufferSlots;`
- L21 _public member_ `bool bBindlessEnabled = false;`
- L22 _public member_ `bool bGlobalUniformBufferUsed = false;`
- L23 _public member_ `bool bDiagnosticBufferUsed = false;`
- L25 _public member_ `uint32 NumInstructions = 0;`
- L26 _public member_ `uint32 NumSamplers = 0;`
- L27 _public member_ `uint32 NumSRVs = 0;`
- L28 _public member_ `uint32 NumCBs = 0;`
- L29 _public member_ `uint32 NumUAVs = 0;`
- L31 _public member_ `uint32 MaxSamplers = 0;`
- L32 _public member_ `uint32 MaxSRVs = 0;`
- L33 _public member_ `uint32 MaxCBs = 0;`
- L34 _public member_ `uint32 MaxUAVs = 0;`

#### enum `ShaderCompilerType`  
`enum class ShaderCompilerType`  
_L598-602_
- L600 _public enumerator_ `FXC`
- L601 _public enumerator_ `DXC`

#### Free symbols / members of external scopes

- L38 _function_ `template <typename D3D1x_SHADER_INPUT_BIND_DESC> EShaderCodeResourceBindingType D3DBindDescToShaderCodeResourceBinding(const D3D1x_SHADER_INPUT_BIND_DESC& Binding)`
- L82 _function_ `inline void ExtractParameterMapFromD3DShader( const FShaderCompilerInput& Input, const FShaderParameterParser& ShaderParameterParser, uint32 BindingSpace, ID3D1xShaderReflection* Reflector, const D3D1x_SHADER_DESC& ShaderDesc, FD3DShaderCompileData& CompileData, FShaderCompilerOutput& Output )`
- L393 _function_ `inline bool ValidateResourceCounts(const FD3DShaderCompileData& CompileData, TArray<FShaderCompilerError>& OutErrors)` — Validate that we are not going over to maximum amount of resource bindings support by the default root signature on DX12 Currently limited for hard-coded root signature setup (see: FD3D12Adapter::StaticGraphicsRootSignature) In theory this limitation is only required for DX12, but we don't want a shader to compile on DX11 while not working on DX12. (DX11 has an API limit on 128 SRVs, 16 Samplers, 8 UAVs and 14 CBs but if you go over these values then the shader won't compile)
- L428 _function_ `inline FShaderCodePackedResourceCounts InitPackedResourceCounts(const FD3DShaderCompileData& CompileData)`
- L457 _function_ `template <typename TBlob> inline void GenerateFinalOutput( TRefCountPtr<TBlob>& CompressedData, const FShaderCompilerInput& Input, ED3DShaderModel ShaderModel, bool bProcessingSecondTime, FD3DShaderCompileData& CompileData, const FShaderCodePackedResourceCounts& PackedResourceCounts, FShaderCompilerOutput& Output, TFunction<void(FMemoryWriter&)> PostSRTWriterCallback, TFunction<void(FShaderCode&)> AddOptionalDataCallback)`
- L604 _typedef_ `using ShaderCompileLambdaType = std::function<bool( const FShaderCompilerInput& Input, const FString& PreprocessedShaderSource, const FString& EntryPointName, const FShaderParameterParser& ShaderParameterParser, const TCHAR* ShaderProfile, const ED3DShaderModel ShaderModel, const bool bProcessingSecondTime, FShaderCompilerOutput& Output)>;`
- L616 _function_ `bool RemoveUnusedInterpolators( const FShaderCompilerInput& Input, const FString& PreprocessedShaderSource, const FString& EntryPointName, const FShaderParameterParser& ShaderParameterParser, const TCHAR* ShaderProfile, const ED3DShaderModel ShaderModel, const bool bProcessingSecondTime, FD3DShaderCompileData& CompileData, TRefCountPtr<ID3D1xShaderReflection> Reflector, TShaderCompileLambdaType ShaderCompileLambda, FShaderCompilerOutput& Output, bool& CompileResult)`

### `Source/Developer/Windows/ShaderFormatD3D/Private/ShaderFormatD3D.h` (Private)


#### enum `ED3DShaderModel`  
`enum class ED3DShaderModel`  
_L13-20_
- L15 _public enumerator_ `Invalid`
- L16 _public enumerator_ `SM5_0`
- L17 _public enumerator_ `SM6_0`
- L18 _public enumerator_ `SM6_6`
- L19 _public enumerator_ `SM6_8`

#### struct `FD3DShaderDebugData`  
`struct FD3DShaderDebugData`  
_L93-130_
- L100 _public function_ `inline friend FArchive& operator<<(FArchive& Ar, FFile& DebugData)`
- L118 _public member_ `TArray<FFile> Files;`
- L126 _public function_ `TConstArrayView<FFile> GetAllSymbolData() const`

#### struct `FD3DShaderDebugData::FFile`  
`struct FFile`  
_L95-116_
- L97 _public member_ `FString Name;`
- L98 _public member_ `TArray<uint8> Contents;`
- L107 _public function_ `inline FString GetFilename() const`
- L112 _public function_ `inline TConstArrayView<uint8> GetContents() const`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3DShaderCompiler, Log, All) struct FShaderTarget;`
- L22 _function_ `inline bool DoesShaderModelRequireDXC(ED3DShaderModel ShaderModel)`
- L27 _function_ `inline uint32 GetAutoBindingSpace(EShaderFrequency ShaderFrequency)`
- L46 _function_ `inline uint32 GetAutoBindingSpace(const FShaderTarget& Target)`
- L51 _prototype_ `bool PreprocessD3DShader( const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& MergedEnvironment, FShaderPreprocessOutput& PreprocessOutput);`
- L56 _prototype_ `void CompileD3DShader( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& InPreprocessOutput, FShaderCompilerOutput& Output, ED3DShaderModel ShaderModel);`
- L65 _prototype_ `bool CompileAndProcessD3DShaderFXC( const FShaderCompilerInput& Input, const FString& InPreprocessedSource, const FString& InEntryPointName, const FShaderParameterParser& ShaderParameterParser, const TCHAR* ShaderProfile, bool bSecondPassAferUnusedInputRemoval, FShaderCompilerOutput& Output);` — @param bSecondPassAferUnusedInputRemoval whether we're compiling the shader second time, after having removed the unused inputs discovered in the first pass
- L74 _prototype_ `bool CompileAndProcessD3DShaderDXC( const FShaderCompilerInput& Input, const FString& InPreprocessedSource, const FString& InEntryPointName, const FShaderParameterParser& ShaderParameterParser, const TCHAR* ShaderProfile, ED3DShaderModel ShaderModel, bool bProcessingSecondTime, FShaderCompilerOutput& Output);`
- L85 _prototype_ `bool ValidateResourceCounts(const FD3DShaderCompileData& CompiledData, TArray<FShaderCompilerError>& OutFilteredErrors);`
- L88 _function_ `template <typename TBlobType> TConstArrayView<uint8> MakeArrayViewFromBlob(const TRefCountPtr<TBlobType> Blob)`
- L120 _function_ `inline friend FArchive& operator<<(FArchive& Ar, FD3DShaderDebugData& DebugData)`
