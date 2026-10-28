# Plugins / ElectraCodecFactory

- module root: `Plugins/Media/ElectraCodecs/Source/ElectraCodecFactory`
- headers: 4; symbols: 24
- symbol kinds: class=5, delegate=1, function=1, prototype=17
- PrivateDependencyModuleNames: ElectraBase, ElectraDecoders
- PublicDependencyModuleNames: Core

### `Plugins/Media/ElectraCodecs/Source/ElectraCodecFactory/Private/ElectraCodecFactoryModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraCodecFactory, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraCodecFactory, Log, All);`

### `Plugins/Media/ElectraCodecs/Source/ElectraCodecFactory/Public/IElectraCodecFactory.h` (Public)


#### class `IElectraCodecFactory`  
`class IElectraCodecFactory`  
_L14-93_
- L17 _public prototype_ `virtual ~IElectraCodecFactory() = default;`
- L23 _public prototype_ `virtual void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions) const = 0;` — Populates the provided map with decoder configuration options (see IElectraDecoderFeature). Some required options must be available through the factory prior to creating a decoder instance.
- L53 _public prototype_ `virtual int32 SupportsDecoding(TMap<FString, FVariant>& OutFormatInfo, const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions) const = 0;` — Queries whether or not this codec factory can create a decoder capable of decoding the specified format. The following FCodecTypeFormat members need to be set up .Type .FourCC .RFC6381 .Properties to the appropriate type like FVideo, FAudio, etc. For video decoders: Required: .Properties.FVideo.Profile Optional, but recommended: .Properties.FVideo.Width .Properties.FVideo.Height .Properties.FVideo.FrameRate For convenience you can just set .RFC6381 and .DCR and have ElectraDecodersUtil::PrepareCodecTypeFormat() from the ElectraCodecs plugin fill in all other parameters. Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. See below. Returns 0 if not supported. If supported the return value indicates a priority value. If multiple factories are registered that claim support for the format the one with the highest priority is chosen.
- L58 _public prototype_ `virtual TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> CreateDecoder(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions) = 0;` — Called to create a decoder for the given format.
- L92 _public prototype_ `virtual const IProviderInformation& GetProviderInformation() const = 0;` — Returns an interface to query decoder provider information.

#### class `IElectraCodecFactory::IProviderInformation`  
`class IProviderInformation`  
_L61-88_
- L64 _public prototype_ `virtual ~IProviderInformation() = default;`
- L69 _public prototype_ `virtual FString GetName() const = 0;` — Returns the name of the implementation, like `VideoToolbox` or similar. Could be an empty string if information is not provided.
- L75 _public prototype_ `virtual FString GetVersion() const = 0;` — Returns a version number of the implementation. Could be an empty string if information is not provided.
- L81 _public prototype_ `virtual FString GetImplementation() const = 0;` — Returns implementation, which could be platform specific, or a version specific value. Could be an empty string if information is not provided.
- L87 _public prototype_ `virtual FString GetVendor() const = 0;` — Returns the name of the vendor, if the codec is provided by the OS manufacturer. Could be an empty string if information is not provided.

### `Plugins/Media/ElectraCodecs/Source/ElectraCodecFactory/Public/IElectraCodecFactoryModule.h` (Public)


#### class `IElectraCodecFactoryModule`  
`class IElectraCodecFactoryModule : public IModuleInterface`  
_L19-31_
- inherits: `IModuleInterface`
- desc: Interface for the `ElectraCodecFactory` module.
- L22 _public prototype_ `virtual ~IElectraCodecFactoryModule() = default;`
- L24 _public function_ `static FName GetModularFeatureName()`
- L30 _public prototype_ `virtual TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> GetBestDecoderFactoryForFormat(TMap<FString, FVariant>& OutFormatInfo, const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions) = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraCodecFactory/Public/IElectraCodecRegistry.h` (Public)


#### class `IElectraCodecRegistry`  
`class IElectraCodecRegistry`  
_L11-17_
- L14 _public prototype_ `virtual ~IElectraCodecRegistry() = default;`
- L16 _public prototype_ `virtual void AddCodecFactory(TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> InCodecFactory) = 0;`

#### class `IElectraCodecModularFeature`  
`class IElectraCodecModularFeature : public IModularFeature`  
_L20-25_
- inherits: `IModularFeature`
- L23 _public prototype_ `virtual ~IElectraCodecModularFeature() = default;`
- L24 _public prototype_ `virtual void GetListOfFactories(TArray<TWeakPtr<IElectraCodecFactory, ESPMode::ThreadSafe>>& OutCodecFactories) = 0;`
