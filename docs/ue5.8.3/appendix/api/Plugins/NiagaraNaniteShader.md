# Plugins / NiagaraNaniteShader

- module root: `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteShader`
- headers: 2; symbols: 10
- symbol kinds: class=2, macro=1, member=3, prototype=4
- PrivateDependencyModuleNames: CoreUObject, Engine, Renderer
- PublicDependencyModuleNames: Core, NiagaraCore, Projects, RHI, RenderCore, VectorVM

### `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteShader/Internal/NiagaraNaniteShaders.h` (Internal)


#### class `FNiagaraNaniteGPUSceneCS`  
`class FNiagaraNaniteGPUSceneCS : public FGlobalShader`  
_L11-75_
- inherits: `FGlobalShader`
- L14 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraNaniteGPUSceneCS, FGlobalShader);`
- L16 _private member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L17 _private member_ `static constexpr int32 MaxCustomFloat4s = 16;`
- L18 _private member_ `static constexpr int32 MaxCustomFloats = MaxCustomFloat4s * 4;`
- L20 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NIAGARANANITESHADER_API`

### `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteShader/Private/NiagaraNaniteShaderModule.h` (Private)


#### class `INiagaraNaniteShaderModule`  
`class INiagaraNaniteShaderModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
