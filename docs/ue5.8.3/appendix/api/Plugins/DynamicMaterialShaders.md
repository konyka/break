# Plugins / DynamicMaterialShaders

- module root: `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialShaders`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=1, namespace=3, prototype=4, typedef=1, variable=1
- PrivateDependencyModuleNames: Engine, Projects, RHI, Renderer
- PublicDependencyModuleNames: Core, CoreUObject, RenderCore

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialShaders/Private/DynamicMaterialShadersModule.h` (Private)


#### class `FDynamicMaterialShadersModule`  
`class FDynamicMaterialShadersModule : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DynamicMaterialShaders` (scope `UE`)
- L7 _namespace_ `namespace Internal` (scope `UE::DynamicMaterialShaders`)
- L9 _variable_ `static inline const TCHAR* VirtualShaderMountPoint = TEXT("/Pl` (scope `UE::DynamicMaterialShaders::Internal`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialShaders/Public/DMAlphaOneMinusPS.h` (Public)


#### class `FDMAlphaOneMinusPS`  
`class FDMAlphaOneMinusPS : public FGlobalShader`  
_L12-29_
- inherits: `FGlobalShader`
- L15 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FDMAlphaOneMinusPS, FGlobalShader);`
- L24 _public member_ `static const FString ShaderPath;`
- L26 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters);`
- L28 _public prototype_ `FParameters* AllocateAndSetParameters(FRDGBuilder& InGraphBuilder, FRDGTextureRef InRGBATexture, FRDGTextureRef InOutputTexture);`

#### Free symbols / members of external scopes

- L10 _typedef_ `using FRDGTextureRef = class FRDGTexture*;`
