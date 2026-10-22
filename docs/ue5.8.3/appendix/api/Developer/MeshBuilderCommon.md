# Developer / MeshBuilderCommon

- module root: `Source/Developer/MeshBuilderCommon`
- headers: 3; symbols: 12
- symbol kinds: class=1, function=2, namespace=3, prototype=6
- PublicDependencyModuleNames: Core, Engine

### `Source/Developer/MeshBuilderCommon/Public/IMeshBuilderCommonModule.h` (Public)


#### class `IMeshBuilderCommonModule`  
`class IMeshBuilderCommonModule : public IModuleInterface`  
_L9-34_
- inherits: `IModuleInterface`
- L19 _public function_ `static inline IMeshBuilderCommonModule & Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Developer/MeshBuilderCommon/Public/NaniteHelper.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Nanite`
- L11 _prototype_ `void CorrectFallbackSettings(FMeshNaniteSettings& NaniteSettings, int32 NumTris, bool bIsAssembly, bool bIsRayTracing);` (scope `Nanite`)
- L12 _prototype_ `void InheritAssemblySettings(FMeshNaniteSettings& PartMeshSettings, const FMeshNaniteSettings& AssemblyMeshSettings);` (scope `Nanite`)

### `Source/Developer/MeshBuilderCommon/Public/ThirdPartyBuildOptimizationHelper.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildOptimizationThirdParty`
- L13 _prototype_ `void CacheOptimizeIndexBuffer(TArray<uint16>& Indices);` (scope `BuildOptimizationThirdParty`)
- L14 _prototype_ `void CacheOptimizeIndexBuffer(TArray<uint32>& Indices);` (scope `BuildOptimizationThirdParty`)
- L20 _namespace_ `namespace NvTriStripHelper` (scope `BuildOptimizationThirdParty`)
- L25 _prototype_ `void BuildStaticAdjacencyIndexBuffer( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TArray<uint32>& Indices, TArray<uint32>& OutPnAenIndices );` (scope `BuildOptimizationThirdParty::NvTriStripHelper`) — Skeletal mesh helpers
- L32 _prototype_ `void BuildSkeletalAdjacencyIndexBuffer( const TArray<FSoftSkinVertex>& VertexBuffer, const uint32 TexCoordCount, const TArray<uint32>& Indices, TArray<uint32>& OutPnAenIndices );` (scope `BuildOptimizationThirdParty::NvTriStripHelper`)
