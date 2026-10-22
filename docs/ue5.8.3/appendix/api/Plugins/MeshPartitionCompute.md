# Plugins / MeshPartitionCompute

- module root: `Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute`
- headers: 2; symbols: 17
- symbol kinds: class=6, function=3, macro=1, prototype=7
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Projects
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Public/MeshPartitionChannelRasterizationShaders.h` (Public)


#### class `FMeshPartition_DrawUVDomainVS`  
`class FMeshPartition_DrawUVDomainVS : public FGlobalShader`  
_L13-28_
- inherits: `FGlobalShader`
- L17 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMeshPartition_DrawUVDomainVS, FGlobalShader);`

#### class `FMeshPartition_DrawUVDomainPS`  
`class FMeshPartition_DrawUVDomainPS : public FGlobalShader`  
_L30-39_
- inherits: `FGlobalShader`
- L34 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMeshPartition_DrawUVDomainPS, FGlobalShader);`

#### class `FMeshPartition_BorderFillCS`  
`class FMeshPartition_BorderFillCS : public FGlobalShader`  
_L41-57_
- inherits: `FGlobalShader`
- L45 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMeshPartition_BorderFillCS, FGlobalShader);`
- L48 _public function_ `SHADER_PARAMETER(FUintVector2, Resolution) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<uint>, Mask) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWSectionTexture) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FMeshPartition_FillPullCS`  
`class FMeshPartition_FillPullCS : public FGlobalShader`  
_L65-85_
- inherits: `FGlobalShader`
- L69 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMeshPartition_FillPullCS, FGlobalShader);`
- L72 _public function_ `SHADER_PARAMETER(FVector2f, TexelSize) SHADER_PARAMETER(FIntVector4, ResolutionPass) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, SectionMipIn) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, SectionMipOut) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float>, MaskMipIn) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float>, MaskMipOut) SHADER_PARAMETER_SAMPLER(SamplerState, MipSampler) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FMeshPartition_FillPushCS`  
`class FMeshPartition_FillPushCS : public FGlobalShader`  
_L87-106_
- inherits: `FGlobalShader`
- L91 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMeshPartition_FillPushCS, FGlobalShader);`
- L94 _public function_ `SHADER_PARAMETER(FVector2f, TexelSize) SHADER_PARAMETER(FIntVector4, ResolutionPass) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, SectionMipIn) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, SectionMipOut) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float>, MaskMipIn) SHADER_PARAMETER_SAMPLER(SamplerState, MipSampler ) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONCOMPUTE_API`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Public/MeshPartitionComputeModule.h` (Public)


#### class `FMegaMeshComputeModule`  
`class FMegaMeshComputeModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
