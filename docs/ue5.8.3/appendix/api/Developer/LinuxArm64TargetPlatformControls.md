# Developer / LinuxArm64TargetPlatformControls

- module root: `Source/Developer/Linux/LinuxArm64TargetPlatformControls`
- headers: 1; symbols: 2
- symbol kinds: class=1, prototype=1
- PrivateDependencyModuleNames: Core, DesktopPlatform, Engine, LinuxArm64TargetPlatformSettings, TargetPlatform
- PrivateIncludePathModuleNames: LinuxArm64TargetPlatformSettings, LinuxTargetPlatformControls, LinuxTargetPlatformSettings, TextureCompressor

### `Source/Developer/Linux/LinuxArm64TargetPlatformControls/Public/ILinuxArm64TargetPlatformControlsModule.h` (Public)


#### class `ILinuxArm64TargetPlatformControlsModule`  
`class ILinuxArm64TargetPlatformControlsModule : public ITargetPlatformControlsModule`  
_L8-13_
- inherits: `ITargetPlatformControlsModule`
- L12 _public prototype_ `virtual void NotifyMultiSelectedFormatsChanged() = 0;` — Called when the user changes the selected texture formats for the Multi cook target
