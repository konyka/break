# Runtime / AudioLinkCore

- module root: `Source/Runtime/AudioLink/AudioLinkCore`
- headers: 1; symbols: 11
- symbol kinds: class=2, function=3, member=1, prototype=4, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/AudioLink/AudioLinkCore/Public/AudioLinkSettingsAbstract.h` (Public)


#### class `IAudioLinkSettingsProxy`  
`class IAudioLinkSettingsProxy`  
_L15-24_
- desc: This interface should be used to provide a non-uclass version of the data described in your implementation of UAudioLinkSettingsAbstract
- L18 _public prototype_ `virtual ~IAudioLinkSettingsProxy() = default;`
- L22 _protected prototype_ `virtual void RefreshFromSettings(UAudioLinkSettingsAbstract* InSettings, FPropertyChangedEvent& InPropertyChangedEvent) = 0;`

#### class `UAudioLinkSettingsAbstract`  
`class UAudioLinkSettingsAbstract : public UObject`  
_L31-65_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This opaque class should be used for specifying settings for how audio should be send to an external audio link.
- L36 _public typedef_ `using FSharedSettingsProxyPtr = TSharedPtr<IAudioLinkSettingsProxy, ESPMode::ThreadSafe>;`
- L38 _public prototype_ `virtual FName GetFactoryName() const PURE_VIRTUAL(UAudioLinkSettingsAbstract::GetFactoryName, return {};);`
- L40 _public function_ `virtual const FSharedSettingsProxyPtr& GetProxy() const`
- L50 _public function_ `template<typename T> auto GetCastProxy() const`
- L57 _protected function_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)`
- L63 _protected prototype_ `virtual FSharedSettingsProxyPtr MakeProxy() const PURE_VIRTUAL(UAudioLinkSettingsAbstract::MakeProxy, return {};);`
- L64 _protected member_ `mutable FSharedSettingsProxyPtr ProxyInstance;`
