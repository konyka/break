# Developer / AndroidTargetPlatform

- module root: `Source/Developer/Android/AndroidTargetPlatform`
- headers: 1; symbols: 2
- symbol kinds: class=1, prototype=1
- PrivateDependencyModuleNames: AndroidDeviceDetection, AudioPlatformConfiguration, Core, CoreUObject, DesktopPlatform, Engine, TargetPlatform
- PrivateIncludePathModuleNames: TextureCompressor

### `Source/Developer/Android/AndroidTargetPlatform/Public/IAndroidTargetPlatformModule.h` (Public)


#### class `IAndroidTargetPlatformModule`  
`class IAndroidTargetPlatformModule : public ITargetPlatformModule`  
_L12-19_
- inherits: `ITargetPlatformModule`
- L18 _public prototype_ `virtual void NotifyMultiSelectedFormatsChanged() = 0;` — Called by AndroidRuntimeSettings to notify us when the user changes the selected texture formats for the Multi format
