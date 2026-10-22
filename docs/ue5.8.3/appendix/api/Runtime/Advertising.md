# Runtime / Advertising

- module root: `Source/Runtime/Advertising/Advertising`
- headers: 2; symbols: 19
- symbol kinds: class=2, function=4, prototype=13
- PublicDependencyModuleNames: Core

### `Source/Runtime/Advertising/Advertising/Public/Advertising.h` (Public)


#### class `FAdvertising`  
`class FAdvertising : public IModuleInterface`  
_L19-66_
- inherits: `IModuleInterface`
- desc: Advertising module interface implementation
- L25 _public prototype_ `FAdvertising();`
- L26 _public prototype_ `virtual ~FAdvertising();`
- L34 _public function_ `static inline FAdvertising& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L44 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public function_ `static FName GetDefaultProviderName()`
- L56 _public prototype_ `virtual IAdvertisingProvider* GetAdvertisingProvider( const FName& ProviderName );`
- L58 _public function_ `virtual IAdvertisingProvider* GetDefaultProvider()`
- L64 _private prototype_ `virtual void StartupModule() override;`
- L65 _private prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/Advertising/Advertising/Public/Interfaces/IAdvertisingProvider.h` (Public)


#### class `IAdvertisingProvider`  
`class IAdvertisingProvider : public IModuleInterface`  
_L9-20_
- inherits: `IModuleInterface`
- desc: Generic interface for an advertising provider. Other modules can define more and register them with this module.
- L12 _public prototype_ `virtual void ShowAdBanner( bool bShowOnBottomOfScreen, int32 adID ) = 0;`
- L13 _public prototype_ `virtual void HideAdBanner() = 0;`
- L14 _public prototype_ `virtual void CloseAdBanner() = 0;`
- L15 _public prototype_ `virtual void LoadInterstitialAd(int32 adID) = 0;`
- L16 _public prototype_ `virtual bool IsInterstitialAdAvailable() = 0;`
- L17 _public prototype_ `virtual bool IsInterstitialAdRequested() = 0;`
- L18 _public prototype_ `virtual void ShowInterstitialAd() = 0;`
- L19 _public prototype_ `virtual int32 GetAdIDCount() = 0;`
