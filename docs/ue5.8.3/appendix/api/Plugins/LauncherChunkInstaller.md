# Plugins / LauncherChunkInstaller

- module root: `Plugins/Portal/LauncherChunkInstaller/Source/LauncherChunkInstaller`
- headers: 1; symbols: 3
- symbol kinds: class=1, macro=1, prototype=1
- PrivateDependencyModuleNames: Core, PakFile

### `Plugins/Portal/LauncherChunkInstaller/Source/LauncherChunkInstaller/Public/LauncherChunkInstaller.h` (Public)


#### class `FLauncherChunkInstaller`  
`class FLauncherChunkInstaller : public FGenericPlatformChunkInstall`  
_L12-16_
- inherits: `FGenericPlatformChunkInstall`
- desc: Launcher Implementation of the platform chunk install module
- L15 _public prototype_ `virtual EChunkLocation::Type GetChunkLocation(uint32 ChunkID) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LAUNCHERCHUNKINSTALLER_API`
