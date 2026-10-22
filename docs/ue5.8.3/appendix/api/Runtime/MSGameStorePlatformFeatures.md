# Runtime / MSGameStorePlatformFeatures

- module root: `Source/Runtime/Windows/MSGaming/MSGameStorePlatformFeatures`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: Core, Engine, GRDK
- PublicDependencyModuleNames: WindowsPlatformFeatures

### `Source/Runtime/Windows/MSGaming/MSGameStorePlatformFeatures/Public/MSGameStorePlatformFeatures.h` (Public)


#### class `FMSGameStorePlatformFeaturesModule`  
`class FMSGameStorePlatformFeaturesModule : public FWindowsPlatformFeaturesModule`  
_L5-12_
- inherits: `FWindowsPlatformFeaturesModule`
- L9 _public prototype_ `virtual FString GetUniqueAppId() override;`
- L10 _public prototype_ `virtual void SetScreenshotEnableState(bool bEnabled) override;`
