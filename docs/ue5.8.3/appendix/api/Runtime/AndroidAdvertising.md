# Runtime / AndroidAdvertising

- module root: `Source/Runtime/Advertising/Android/AndroidAdvertising`
- headers: 1; symbols: 9
- symbol kinds: class=1, prototype=8
- PrivateDependencyModuleNames: Advertising
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Advertising

### `Source/Runtime/Advertising/Android/AndroidAdvertising/Public/AndroidAdvertising.h` (Public)


#### class `FAndroidAdvertisingProvider`  
`class FAndroidAdvertisingProvider : public IAdvertisingProvider`  
_L8-21_
- inherits: `IAdvertisingProvider`
- L11 _public prototype_ `virtual void ShowAdBanner(bool bShowOnBottomOfScreen, int32 adID) override;`
- L12 _public prototype_ `virtual void HideAdBanner() override;`
- L13 _public prototype_ `virtual void CloseAdBanner() override;`
- L15 _public prototype_ `virtual void LoadInterstitialAd(int32 adID) override;`
- L16 _public prototype_ `virtual bool IsInterstitialAdAvailable() override;`
- L17 _public prototype_ `virtual bool IsInterstitialAdRequested() override;`
- L18 _public prototype_ `virtual void ShowInterstitialAd() override;`
- L20 _public prototype_ `virtual int32 GetAdIDCount() override;`
