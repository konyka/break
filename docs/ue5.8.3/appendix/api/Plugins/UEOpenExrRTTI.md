# Plugins / UEOpenExrRTTI

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/openexrRTTI`
- headers: 1; symbols: 2
- symbol kinds: class=1, prototype=1
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: Imath, UEOpenExr

### `Plugins/MovieScene/MovieRenderPipeline/Source/openexrRTTI/Public/IOpenExrRTTIModule.h` (Public)


#### class `IOpenExrRTTIModule`  
`class IOpenExrRTTIModule : public IModuleInterface`  
_L14-18_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void AddFileMetadata(const TMap<FString, FStringFormatArg>& InMetadata, Imf::Header& InHeader) = 0;`
