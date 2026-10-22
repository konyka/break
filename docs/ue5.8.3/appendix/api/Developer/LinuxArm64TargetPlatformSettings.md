# Developer / LinuxArm64TargetPlatformSettings

- module root: `Source/Developer/Linux/LinuxArm64TargetPlatformSettings`
- headers: 1; symbols: 2
- symbol kinds: class=1, prototype=1
- PrivateDependencyModuleNames: Core, DesktopPlatform, Engine, TargetPlatform
- PrivateIncludePathModuleNames: LinuxTargetPlatformSettings, TextureCompressor

### `Source/Developer/Linux/LinuxArm64TargetPlatformSettings/Public/ILinuxArm64TargetPlatformSettingsModule.h` (Public)


#### class `ILinuxArm64TargetPlatformSettingsModule`  
`class ILinuxArm64TargetPlatformSettingsModule : public ITargetPlatformSettingsModule`  
_L12-16_
- inherits: `ITargetPlatformSettingsModule`
- L15 _public prototype_ `virtual void GetPlatformSettingsMaps(TMap<FString, ITargetPlatformSettings*>& OutMap) = 0;`
