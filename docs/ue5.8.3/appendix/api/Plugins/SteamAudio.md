# Plugins / SteamAudio

- module root: `Plugins/Runtime/Steam/SteamAudio/Source/SteamAudio`
- headers: 2; symbols: 11
- symbol kinds: class=2, delegate=1, function=2, namespace=1, prototype=5
- PrivateDependencyModuleNames: AudioExtensions, AudioMixer, Core, CoreUObject, EditorFramework, Engine, InputCore, Landscape, Projects, UnrealEd
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioMixer, Core, CoreUObject, Engine, InputCore, RHI, RenderCore

### `Plugins/Runtime/Steam/SteamAudio/Source/SteamAudio/Private/SteamAudioModule.h` (Private)


#### class `SteamAudio::FSteamAudioModule`  
`class FSteamAudioModule : public ISteamAudioModule`  
_L20-29_
- inherits: `ISteamAudioModule`
- desc: /
- L23 _public prototype_ `FSteamAudioModule();`
- L24 _public prototype_ `~FSteamAudioModule();`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSteamAudio, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSteamAudio, Log, All);`
- L13 _namespace_ `namespace SteamAudio`

### `Plugins/Runtime/Steam/SteamAudio/Source/SteamAudio/Public/ISteamAudioModule.h` (Public)


#### class `ISteamAudioModule`  
`class ISteamAudioModule : public IModuleInterface`  
_L9-33_
- inherits: `IModuleInterface`
- L19 _public function_ `static inline ISteamAudioModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
