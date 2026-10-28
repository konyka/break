# Runtime / IOSAdvertising

- module root: `Source/Runtime/Advertising/IOS/IOSAdvertising`
- headers: 1; symbols: 9
- symbol kinds: class=1, function=8
- PrivateDependencyModuleNames: Advertising, ApplicationCore
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Advertising

### `Source/Runtime/Advertising/IOS/IOSAdvertising/Public/IOSAdvertising.h` (Public)


#### class `FIOSAdvertisingProvider`  
`class FIOSAdvertisingProvider : public IAdvertisingProvider`  
_L8-20_
- inherits: `IAdvertisingProvider`
- L12 _public function_ `virtual void ShowAdBanner( bool bShowOnBottomOfScreen, int32 AdID ) override` — empty functions for now, this is Android-only support until iAd is replaced by AdMob
- L13 _public function_ `virtual void HideAdBanner() override`
- L14 _public function_ `virtual void CloseAdBanner() override`
- L15 _public function_ `virtual int32 GetAdIDCount() override`
- L16 _public function_ `virtual void LoadInterstitialAd(int32 adID) override`
- L17 _public function_ `virtual bool IsInterstitialAdAvailable() override`
- L18 _public function_ `virtual bool IsInterstitialAdRequested() override`
- L19 _public function_ `virtual void ShowInterstitialAd() override`
