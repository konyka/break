# Plugins / AVCodecsCore

- module root: `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore`
- headers: 57; symbols: 2223
- symbol kinds: class=83, delegate=1, enum=44, enumerator=482, externvar=3, function=313, macro=24, member=842, namespace=19, prototype=278, struct=92, typedef=19, union=1, variable=22
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, MetalRHI
- PublicIncludePathModuleNames: Vulkan

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVCoder.h` (Public)


#### class `IAVCoder`  
`class IAVCoder`  
_L48-99_
- desc: Simple base coder interface
- L59 _protected member_ `static TMap<FTypeID, TMap<FTypeID, TMap<FTypeID, TSharedPtr<void>>>> Factories;` — Type-erased factory list. First level is domain ids, second is resource ids, third is configuration ids. Stored void pointers point to a TArray of TAVCoder::TFactory's with types matching the domain, resource, and configuration ids. This is declared here to avoid exporting the template types (which can be real dodgy). @see FTypeID @see TAVCoder::GetFactories
- L62 _public prototype_ `virtual ~IAVCoder() = default;`
- L67 _public prototype_ `virtual TSharedPtr<FAVDevice> const& GetDevice() const = 0;` — @return Get the physical device this coder runs on.
- L72 _public prototype_ `virtual TSharedPtr<FAVInstance> const& GetInstance() const = 0;` — @return Get the shared data cache of this coder.
- L79 _public prototype_ `virtual FAVResult ApplyConfig() = 0;` — Force any pending configuration to apply. @return Result of the operation, @see FAVResult.
- L84 _public prototype_ `virtual bool IsOpen() const = 0;` — @return True if the underlying coder architecture is ready for use.
- L93 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) = 0;` — Construct the underlying coder architecture on a physical device with a configuration. @param NewDevice The physical device on which to construct this coder. @param NewInstance The cache with which to construct this coder. @return Result of the operation, @see FAVResult.
- L98 _public prototype_ `virtual void Close() = 0;` — Gracefully tear down the underlying coder architecture.

#### class `TAVCoder`  
`template <template <typename TResource = void, typename TConfig = void> typename TDomain, typename TResource, typename TConfig> class TAVCoder : public TDomain<TResource>`  
_L107-242_
- inherits: `TDomain<TResource>`
- desc: Common coder base with a factory, that supports typesafe resource handling and configuration. Usage: To be inherited by a domain implementation, see top of file.
- L110 _public typedef_ `using ConfigType = TConfig;`
- L194 _protected member_ `TConfig AppliedConfig;` — The currently active configuration, for comparison with PendingConfig. Never modify this directly.
- L200 _public function_ `TConfig const& GetAppliedConfig() const` — @return Get the currently active configuration, for comparison with PendingConfig.
- L208 _public function_ `TConfig const& GetPendingConfig() const` — @return The pending configuration, to be applied on the next call to ApplyConfig.
- L216 _public function_ `TConfig& EditPendingConfig() const` — @return A mutable reference to the pending configuration, to be applied on the next call to ApplyConfig.
- L226 _public function_ `void SetPendingConfig(TConfig const& NewPendingConfig) const` — Set the pending configuration, to be applied on the next call to ApplyConfig. @param NewPendingConfig The pending configuration to be set.
- L236 _public function_ `virtual FAVResult ApplyConfig() override` — Force any pending configuration to apply. @return Result of the operation, @see FAVResult.
- L253 _public typedef_ `using ResourceType = TResource;`
- L268 _public typedef_ `typedef TFunction<bool(TSharedRef<FAVDevice> const&, TSharedRef<FAVInstance> const&)> FIsCompatible;` — Delegate used to test factory compatibility.
- L292 _private function_ `template <typename TResource, typename TConfig> static TArray<TFactory<TResource, TConfig>>& GetFactories()` — Internal getter for type-specific coder factories.
- L324 _public function_ `template <typename TResource, typename TConfig, typename TCoder> static TSharedPtr<TDomain<TResource, TConfig>> Wrap(TSharedPtr<TCoder> const& Child)` — Wrap a fully typed child coder with a differently-typed outer encoder, to transform one resource/config type into another. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder. @tparam TResource Resource type of returned wrapper coder. @tparam TConfig Config type of returned wrapper coder. @return The new wrapper coder containing the child.
- L352 _public function_ `template <typename TCoder, typename TResource, typename TConfig> static TFactory<TResource, TConfig>& Register(FIsCompatible const& IsCompatible = nullptr)` — Register a fully type-complete coder with the domain factory. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder to be created by the factory. Must have a valid default constructor. Must be assignable to the base domain with the filter types below. @tparam TResource Type of AVResource to filter by when requested. @tparam TConfig Type of AVConfig to to filter by when requested. @param IsCompatible Optional delegate to further filter this coder. @return The constructed factory, to be further customised if desired.
- L429 _public function_ `template <typename TResource, typename TConfig> static int32 CountSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Count the number of different coders that can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The number of different coders that can be created.
- L452 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported()` — Checks if any coder can be created to match this combination of resource and configuration. This does NOT check the device or desired configuration, so all potential coders may still reject being created. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @return True if a coder could be created.
- L467 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Checks if any coder can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return True if a coder could be created.
- L490 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L523 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L541 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L561 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder, open and ready for use. NOTE: This is for advanced use cases only (ie. sharing an instance between multiple coders). Prefer the above version of this function if possible. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L574 _private member_ `TSharedPtr<FAVDevice> Device;` — The physical device this coder runs on.
- L579 _private member_ `TSharedPtr<FAVInstance> Instance;` — The shared data cache of this coder.
- L585 _public function_ `virtual TSharedPtr<FAVDevice> const& GetDevice() const override` — @return Get the physical device this coder runs on.
- L593 _public function_ `virtual TSharedPtr<FAVInstance> const& GetInstance() const override` — @return Get the shared data cache of this coder.
- L605 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override` — Construct the underlying coder architecture on a physical device with a configuration. @param NewDevice The physical device on which to construct this coder. @param NewInstance The cache with which to construct this coder. @return Result of the operation, @see FAVResult.

#### class `TAVCoder::TWrapper`  
`template <typename TChildResource, typename TChildConfig> class TWrapper : public TDomain<TResource, TConfig>`  
_L119-188_
- inherits: `TDomain<TResource,TConfig>`
- desc: Wrapper coder that transforms resource/config types for use with a differently typed child coder. @tparam TChildResource Type of child resource. @tparam TChildConfig Type of child config.
- L125 _public member_ `TSharedRef<TDomain<TChildResource, TChildConfig>> Child;` — The child coder to wrap.
- L127 _public function_ `TWrapper(TSharedRef<TDomain<TChildResource, TChildConfig>> const& Child) : Child(Child)`
- L138 _public function_ `virtual bool IsOpen() const override`
- L143 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override`
- L165 _public function_ `virtual void Close() override`
- L173 _public function_ `virtual FAVResult ApplyConfig() override`

#### class `TAVCoder`  
`template <template <typename TResource = void, typename TConfig = void> typename TDomain, typename TResource> class TAVCoder<TDomain, TResource, void> : public TDomain<>`  
_L250-254_
- inherits: `TDomain<>`
- desc: Common coder base with a factory, that supports typesafe resource handling. Usage: To be inherited by a domain implementation, see top of file.
- L110 _public typedef_ `using ConfigType = TConfig;`
- L194 _protected member_ `TConfig AppliedConfig;` — The currently active configuration, for comparison with PendingConfig. Never modify this directly.
- L200 _public function_ `TConfig const& GetAppliedConfig() const` — @return Get the currently active configuration, for comparison with PendingConfig.
- L208 _public function_ `TConfig const& GetPendingConfig() const` — @return The pending configuration, to be applied on the next call to ApplyConfig.
- L216 _public function_ `TConfig& EditPendingConfig() const` — @return A mutable reference to the pending configuration, to be applied on the next call to ApplyConfig.
- L226 _public function_ `void SetPendingConfig(TConfig const& NewPendingConfig) const` — Set the pending configuration, to be applied on the next call to ApplyConfig. @param NewPendingConfig The pending configuration to be set.
- L236 _public function_ `virtual FAVResult ApplyConfig() override` — Force any pending configuration to apply. @return Result of the operation, @see FAVResult.
- L253 _public typedef_ `using ResourceType = TResource;`
- L268 _public typedef_ `typedef TFunction<bool(TSharedRef<FAVDevice> const&, TSharedRef<FAVInstance> const&)> FIsCompatible;` — Delegate used to test factory compatibility.
- L292 _private function_ `template <typename TResource, typename TConfig> static TArray<TFactory<TResource, TConfig>>& GetFactories()` — Internal getter for type-specific coder factories.
- L324 _public function_ `template <typename TResource, typename TConfig, typename TCoder> static TSharedPtr<TDomain<TResource, TConfig>> Wrap(TSharedPtr<TCoder> const& Child)` — Wrap a fully typed child coder with a differently-typed outer encoder, to transform one resource/config type into another. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder. @tparam TResource Resource type of returned wrapper coder. @tparam TConfig Config type of returned wrapper coder. @return The new wrapper coder containing the child.
- L352 _public function_ `template <typename TCoder, typename TResource, typename TConfig> static TFactory<TResource, TConfig>& Register(FIsCompatible const& IsCompatible = nullptr)` — Register a fully type-complete coder with the domain factory. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder to be created by the factory. Must have a valid default constructor. Must be assignable to the base domain with the filter types below. @tparam TResource Type of AVResource to filter by when requested. @tparam TConfig Type of AVConfig to to filter by when requested. @param IsCompatible Optional delegate to further filter this coder. @return The constructed factory, to be further customised if desired.
- L429 _public function_ `template <typename TResource, typename TConfig> static int32 CountSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Count the number of different coders that can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The number of different coders that can be created.
- L452 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported()` — Checks if any coder can be created to match this combination of resource and configuration. This does NOT check the device or desired configuration, so all potential coders may still reject being created. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @return True if a coder could be created.
- L467 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Checks if any coder can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return True if a coder could be created.
- L490 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L523 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L541 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L561 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder, open and ready for use. NOTE: This is for advanced use cases only (ie. sharing an instance between multiple coders). Prefer the above version of this function if possible. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L574 _private member_ `TSharedPtr<FAVDevice> Device;` — The physical device this coder runs on.
- L579 _private member_ `TSharedPtr<FAVInstance> Instance;` — The shared data cache of this coder.
- L585 _public function_ `virtual TSharedPtr<FAVDevice> const& GetDevice() const override` — @return Get the physical device this coder runs on.
- L593 _public function_ `virtual TSharedPtr<FAVInstance> const& GetInstance() const override` — @return Get the shared data cache of this coder.
- L605 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override` — Construct the underlying coder architecture on a physical device with a configuration. @param NewDevice The physical device on which to construct this coder. @param NewInstance The cache with which to construct this coder. @return Result of the operation, @see FAVResult.

#### class `TAVCoder`  
`template <template <typename TResource = void, typename TConfig = void> typename TDomain> class TAVCoder<TDomain, void, void> : public IAVCoder`  
_L262-612_
- inherits: `IAVCoder`
- desc: Common coder base with a factory. Usage: To be inherited by a domain implementation, see top of file.
- L110 _public typedef_ `using ConfigType = TConfig;`
- L194 _protected member_ `TConfig AppliedConfig;` — The currently active configuration, for comparison with PendingConfig. Never modify this directly.
- L200 _public function_ `TConfig const& GetAppliedConfig() const` — @return Get the currently active configuration, for comparison with PendingConfig.
- L208 _public function_ `TConfig const& GetPendingConfig() const` — @return The pending configuration, to be applied on the next call to ApplyConfig.
- L216 _public function_ `TConfig& EditPendingConfig() const` — @return A mutable reference to the pending configuration, to be applied on the next call to ApplyConfig.
- L226 _public function_ `void SetPendingConfig(TConfig const& NewPendingConfig) const` — Set the pending configuration, to be applied on the next call to ApplyConfig. @param NewPendingConfig The pending configuration to be set.
- L236 _public function_ `virtual FAVResult ApplyConfig() override` — Force any pending configuration to apply. @return Result of the operation, @see FAVResult.
- L253 _public typedef_ `using ResourceType = TResource;`
- L268 _public typedef_ `typedef TFunction<bool(TSharedRef<FAVDevice> const&, TSharedRef<FAVInstance> const&)> FIsCompatible;` — Delegate used to test factory compatibility.
- L292 _private function_ `template <typename TResource, typename TConfig> static TArray<TFactory<TResource, TConfig>>& GetFactories()` — Internal getter for type-specific coder factories.
- L324 _public function_ `template <typename TResource, typename TConfig, typename TCoder> static TSharedPtr<TDomain<TResource, TConfig>> Wrap(TSharedPtr<TCoder> const& Child)` — Wrap a fully typed child coder with a differently-typed outer encoder, to transform one resource/config type into another. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder. @tparam TResource Resource type of returned wrapper coder. @tparam TConfig Config type of returned wrapper coder. @return The new wrapper coder containing the child.
- L352 _public function_ `template <typename TCoder, typename TResource, typename TConfig> static TFactory<TResource, TConfig>& Register(FIsCompatible const& IsCompatible = nullptr)` — Register a fully type-complete coder with the domain factory. @tparam TCoder Fully type-complete (ie. FVideoEncoderNVENC : TVideoEncoder<FVideoResourceCUDA, FVideoConfigNVENC>) coder to be created by the factory. Must have a valid default constructor. Must be assignable to the base domain with the filter types below. @tparam TResource Type of AVResource to filter by when requested. @tparam TConfig Type of AVConfig to to filter by when requested. @param IsCompatible Optional delegate to further filter this coder. @return The constructed factory, to be further customised if desired.
- L429 _public function_ `template <typename TResource, typename TConfig> static int32 CountSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Count the number of different coders that can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The number of different coders that can be created.
- L452 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported()` — Checks if any coder can be created to match this combination of resource and configuration. This does NOT check the device or desired configuration, so all potential coders may still reject being created. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @return True if a coder could be created.
- L467 _public function_ `template <typename TResource, typename TConfig> static bool IsSupported(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Checks if any coder can be created to match this combination of resource and configuration. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return True if a coder could be created.
- L490 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L523 _public function_ `template <typename TResource, typename TConfig> static TSharedPtr<TDomain<TResource, TConfig>> Create(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder if possible, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder, null if one could not be created.
- L541 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TConfig const& NewConfig)` — Create a type-safe coder, open and ready for use. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewConfig Config to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L561 _public function_ `template <typename TResource, typename TConfig> static TSharedRef<TDomain<TResource, TConfig>> CreateChecked(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` — Create a type-safe coder, open and ready for use. NOTE: This is for advanced use cases only (ie. sharing an instance between multiple coders). Prefer the above version of this function if possible. @tparam TResource Type of AVResource the coder will support. @tparam TConfig Type of AVConfig the coder will support. @param NewDevice Device to filter the coder against, and to open it with. @param NewInstance Instance to filter the coder against, and to open it with. @return The constructed and opened coder. Throws an exception if one could not be created.
- L574 _private member_ `TSharedPtr<FAVDevice> Device;` — The physical device this coder runs on.
- L579 _private member_ `TSharedPtr<FAVInstance> Instance;` — The shared data cache of this coder.
- L585 _public function_ `virtual TSharedPtr<FAVDevice> const& GetDevice() const override` — @return Get the physical device this coder runs on.
- L593 _public function_ `virtual TSharedPtr<FAVInstance> const& GetInstance() const override` — @return Get the shared data cache of this coder.
- L605 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override` — Construct the underlying coder architecture on a physical device with a configuration. @param NewDevice The physical device on which to construct this coder. @param NewInstance The cache with which to construct this coder. @return Result of the operation, @see FAVResult.

#### struct `TAVCoder::TFactory`  
`template <typename TResource, typename TConfig> struct TFactory final`  
_L274-287_
- desc: The individual factory type constructed by a call to Register.
- L277 _public typedef_ `typedef TFunction<TSharedPtr<TDomain<TResource, TConfig>>()> FCreate;`
- L279 _public member_ `FIsCompatible const IsCompatible;`
- L280 _public member_ `FCreate const Create;`
- L282 _public function_ `TFactory(FIsCompatible const& IsCompatible, FCreate const& Create) : IsCompatible(IsCompatible) , Create(Create)`

#### struct `TAVCoder::RegisterPermutationsOf`  
`template <typename TCoder> struct RegisterPermutationsOf`  
_L372-417_
- desc: Register a partially type-complete coder with the domain factory, but with multiple filter configurations and permuted typing. Cannot provide additional custom filters, if this is necessary then you must directly call Register. Usage: Highly recursive template permuter, see NVENCModule source for example of use.

#### struct `TAVCoder::RegisterPermutationsOf::With`  
`template <typename TResource = void, typename... TResources> struct With`  
_L375-401_
- L390 _public prototype_ `With() = delete;`

#### struct `TAVCoder::RegisterPermutationsOf::With::And`  
`template <typename TConfig = void, typename... TConfigs> struct And`  
_L378-388_
- L380 _public function_ `And(FIsCompatible const& IsCompatible = nullptr)`

#### struct `TAVCoder::RegisterPermutationsOf::With::And`  
`template <> struct And<void>`  
_L395-400_
- L380 _public function_ `And(FIsCompatible const& IsCompatible = nullptr)`

#### struct `TAVCoder::RegisterPermutationsOf::With`  
`template <> struct With<void>`  
_L406-416_
- L390 _public prototype_ `With() = delete;`

#### struct `TAVCoder::RegisterPermutationsOf::With::And`  
`template <typename...> struct And`  
_L410-415_
- L380 _public function_ `And(FIsCompatible const& IsCompatible = nullptr)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AVCODECSCORE_API`
- L334 _typedef_ `typedef typename TDomain<TResource, TConfig>::template TWrapper<typename TCoder::ResourceType, typename TCoder::ConfigType> WrapperType;` (scope `TAVCoder::Wrap`)
- L356 _function_ `` (scope `TAVCoder::Register`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVConfig.h` (Public)


#### enum `EAVPreset`  
`enum class EAVPreset : uint8`  
_L13-20_
- reflection: `UENUM()`
- desc: Simple presets for whole AV pipeline.
- L15 _public enumerator_ `UltraLowQuality`
- L16 _public enumerator_ `LowQuality`
- L17 _public enumerator_ `Default`
- L18 _public enumerator_ `HighQuality`
- L19 _public enumerator_ `Lossless`

#### enum `EAVLatencyMode`  
`enum class EAVLatencyMode : uint8`  
_L26-31_
- reflection: `UENUM()`
- desc: Latency mode for the AV pipeline.
- L28 _public enumerator_ `UltraLowLatency`
- L29 _public enumerator_ `LowLatency`
- L30 _public enumerator_ `Default`

#### struct `FAVConfig`  
`struct FAVConfig`  
_L36-47_
- desc: Base struct for codec configuration.
- L39 _public member_ `EAVPreset Preset;`
- L40 _public member_ `EAVLatencyMode LatencyMode;`
- L42 _public function_ `FAVConfig(EAVPreset Preset = EAVPreset::Default) : Preset(Preset) , LatencyMode(EAVLatencyMode::Default)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVConstants.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Video`
- L10 _variable_ `constexpr int MaxSpatialLayers = 5;` (scope `Video`)
- L11 _variable_ `constexpr int MaxTemporalStreams = 4;` (scope `Video`)
- L12 _variable_ `constexpr int MaxSimulcastStreams = 3;` (scope `Video`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVContext.h` (Public)


#### class `FAVContext`  
`class FAVContext`  
_L8-12_
- desc: Base class for device contexts, for use by resources and platform vendor architecture
- L11 _public prototype_ `virtual ~FAVContext() = default;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVDevice.h` (Public)


#### class `FAVDevice`  
`class FAVDevice`  
_L13-75_
- desc: A representation of a physical computer device, be it a GPU or a CPU or an external device, that can hold device resource contexts (Vulkan, D3D, CUDA, etc).
- L19 _private member_ `TTypeMap<FAVContext> Contexts;` — Type-erased list of contexts on this device
- L28 _public prototype_ `static TSharedRef<FAVDevice>& GetHardwareDevice(int32 Index = 0);` — Get the global hardware device. @param Index Index of the device if there are multiple hardware devices present (multiple GPUs or external cards). @return The global hardware device at Index.
- L35 _public prototype_ `static TSharedRef<FAVDevice>& GetSoftwareDevice();` — Get the global software device. @return The global software device.
- L44 _public function_ `template <typename TContext> bool HasContext() const` — Check if this device has a specific context. @tparam TContext Type of context to check for. @return Whether this device has a context of that type.
- L56 _public function_ `template <typename TContext> TSharedPtr<TContext> const& GetContext() const` — Get a typed context from this device, if it exists. @tparam TContext Type of context to get. @return The context if it exists, an invalid pointer if it does not.
- L68 _public function_ `template <typename TContext> void SetContext(TSharedPtr<TContext> const& NewContext)` — Set a context by type on this device. @tparam TContext Type of context to set. @param NewContext Context to set.
- L73 _public prototype_ `FAVDevice() = default;`
- L74 _public prototype_ `virtual ~FAVDevice() = default;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVExtension.h` (Public)


#### struct `FAVExtension`  
`struct FAVExtension`  
_L35-111_
- desc: Static extension system for simple composition of different resource/config types, via exported specializations
- L50 _public function_ `template <typename TContext, typename TOption> static bool IsCompatible(TSharedPtr<class FAVDevice> const& Device)` — Check if a type is compatible in a certain context, with a certain device. Very general use. Returns true by default, so specialize this to specifically disallow/test certain combinations rather than enable them. Usage: TAVCoder factory for AVResource usage, ie. FAVExtension::IsCompatible<FVideoEncoderNVENC, FVideoResourceD3D12>(Device); @tparam TContext Context against which to check compatability. @tparam TOption Type to check for compatability. @param Device The device associated with the type. @return True if the type is compatible in this context.
- L64 _public function_ `template <typename TContext, typename TOption> static bool IsCompatible(TSharedPtr<class FAVInstance> const& Instance)` — Check if a type is compatible in a certain context, with a certain instance. Very general use. Returns true by default, so specialize this to specifically disallow/test certain combinations rather than enable them. Usage: TAVCoder factory for AVConfig usage, ie. FAVExtension::IsCompatible<FVideoEncoderNVENC, FVideoConfigH264>(Instance); @tparam TContext Context against which to check compatability. @tparam TOption Type to check for compatability. @param Instance The instance associated with the type. @return True if the type is compatible in this context.
- L77 _public function_ `template <typename TOutput, typename TInput> static FAVResult TransformResource(TSharedPtr<TOutput>& OutResource, TSharedPtr<TInput> const& InResource)` — Shortcut case for above for when the input and output types match. This does NOT duplicate the resource.
- L96 _public function_ `template <typename OutputType, typename InputType> static FAVResult TransformConfig(OutputType& OutConfig, InputType const& InConfig)` — Transform one configuration type into another. Naive implementation is provided that uses the assignment operator, but it can be explicitly specialized. @tparam OutputType Config type to convert to. @tparam InputType Config type to convert from. @param OutConfig The config to write to. @param InConfig The config to read from. @return Result of the operation, @see FAVResult.
- L110 _public prototype_ `FAVExtension() = delete;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVInstance.h` (Public)


#### class `FAVInstance`  
`class FAVInstance`  
_L11-137_
- desc: The shared data and logic of a single logical pipeline, usually one or more coders.
- L17 _private member_ `TTypeMap<void> Data;` — Type-erased list of data on this instance
- L27 _public function_ `template <typename TData> bool Has() const` — Check if this instance has a specific type of data. @tparam TData Type of data to check for. @return Whether this instance has data of that type.
- L38 _public function_ `template <typename TData> void Add()` — Add default data by type to this instance. @tparam TData Type of data to add.
- L51 _public function_ `template <typename TData> bool TryGet(TData& OutData)` — Check if this instance has a specific type of data, and return it if it exists. @tparam TData Type of data to get. @param OutData A copy of the data, if it exists. @return Whether the instance has data of the type.
- L71 _public function_ `template <typename TData> TData const& Get()` — Get typed data from this instance. Will create default data of this type if it does not already exist. @tparam TData Type of data to get. @return The typed data.
- L83 _public function_ `template <typename TData> void Set(TData const& NewData)` — Set data by type on this instance. @tparam TData Type of data to set. @param NewData Data to set.
- L95 _public function_ `template <typename TData> TData* TryEdit()` — Check if this instance has a specific type of data, and return a mutable reference to it if it exists. @tparam TData Type of data to get. @return A pointer to the data, if it exists. Not valid outside of the scope from which this is called.
- L113 _public function_ `template <typename TData> TData& Edit()` — Get a mutable reference to typed data held on this instance. Will create default data of this type if it does not already exist. @tparam TData Type of data to get. @return The typed data.
- L130 _public function_ `template <typename TData> void Remove()` — Remove a specific type of data from this instance. @tparam TData Type of data to remote.
- L135 _public prototype_ `FAVInstance() = default;`
- L136 _public prototype_ `virtual ~FAVInstance() = default;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVLayout.h` (Public)


#### struct `FAVLayout`  
`struct FAVLayout`  
_L10-34_
- desc: This struct defines the memory footprint of a block of data.
- L13 _public member_ `uint32 Stride = 0;`
- L14 _public member_ `uint32 Offset = 0;`
- L15 _public member_ `uint32 Size = 0;`
- L17 _public prototype_ `FAVLayout() = default;`
- L18 _public function_ `FAVLayout(uint32 Stride, uint32 Offset, uint32 Size) : Stride(Stride) , Offset(Offset) , Size(Size)`
- L25 _public function_ `bool operator==(FAVLayout const& RHS) const`
- L30 _public function_ `bool operator!=(FAVLayout const& RHS) const`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVPacket.h` (Public)


#### struct `FAVPacket`  
`struct FAVPacket`  
_L14-68_
- desc: Base container for raw encoded AV resources, created by encoders and consumed by decoders. Can be treated like a networking packet, where the encoder and decoder are separate machines and communicate only through this medium.
- L19 _public member_ `TSharedPtr<uint8> DataPtr;` — Safe pointer to packet data.
- L24 _public member_ `uint64 DataSize;` — Size of packet data.
- L29 _public member_ `uint64 Timestamp;` — Timestamp of packet.
- L34 _public member_ `uint64 Index;` — Packet index in the sequence.
- L41 _public function_ `inline TArrayView64<uint8> GetData() const` — Convenience wrapper to treat raw data as an array view. @return Raw data as an array view.
- L43 _public function_ `inline void WriteToFile(TCHAR* FileName) const`
- L55 _public function_ `bool IsEmpty() const` — Test whether raw data is empty or not set. @return True if raw data is empty or not set.
- L60 _public prototype_ `FAVPacket() = default;`
- L61 _public function_ `FAVPacket(TSharedPtr<uint8> const& DataPtr, uint64 DataSize, uint64 Timestamp, uint64 Index) : DataPtr(DataPtr) , DataSize(DataSize) , Timestamp(Timestamp) , Index(Index)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVResource.h` (Public)


#### class `FAVResource`  
`class FAVResource`  
_L15-103_
- desc: Base wrapper for an immutable device resource. Bundles necessary data that may not be easily retrieved on without an RHI, such as size on device. If the underlying device resource must change, this resource wrapper must be recreated.
- L21 _private member_ `TSharedRef<FAVDevice> Device;` — Reference to parent device. Must exist.
- L26 _private member_ `FAVLayout Layout;` — Layout of data in device memory.
- L31 _private member_ `FCriticalSection Mutex;` — Mutex used for resource synchronization.
- L37 _private member_ `TTypeMap<void> Mappings;` — All mappings of this resource into other resources (or other objects), ensuring appropriate cleanup when the root resource is destroyed. Stored as a type-erased list of shared pointers.
- L43 _public function_ `inline TSharedRef<FAVDevice> const& GetDevice() const` — @return Get a reference to our device parent. Is always valid.
- L48 _public function_ `inline FAVLayout const& GetLayout() const` — @return Get the layout of our data in device memory.
- L53 _public function_ `inline uint64 GetOffset() const` — @return Get the offset of our data in device memory.
- L58 _public function_ `inline uint64 GetMemorySize() const` — @return Get the size of our data in device memory.
- L63 _public function_ `inline uint64 GetStride() const` — @return Get the stride of our data in device memory.
- L65 _public prototype_ `FAVResource(TSharedRef<FAVDevice> const& Device, FAVLayout const& Layout);`
- L66 _public prototype_ `virtual ~FAVResource() = default;`
- L73 _public prototype_ `virtual FAVResult Validate() const;` — Test if the underlying resource is usable or misconfigured. @return Result of the operation, @see FAVResult.
- L78 _public prototype_ `virtual void Lock();` — Lock this resource for internal use. Is a blocking call until the lock can be taken.
- L85 _public prototype_ `virtual FScopeLock LockScope();` — Lock this resource for internal use, within the current scope. Is a blocking call until the lock can be taken. @return The lock object. Capture this, because when it goes out of scope it will unlock the resource.
- L90 _public prototype_ `virtual void Unlock();` — Release this resource for external use.
- L99 _public function_ `template <typename TMapping> TSharedPtr<TMapping>& PinMapping()` — Create a mapping of this resource to another resource (or other object). Returned reference must then be set by the caller. @tparam TMapping Object type to map this resource to. @return Shared pointer reference to the mapping, initially invalid until set by the caller.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVResult.h` (Public)


#### enum `EAVResult`  
`enum class EAVResult : uint16`  
_L45-71_
- desc: Low level AV result. Use specific result codes where possible for better logging. Result codes are laid out in 'ranges', ie. ErrorCreating/ErrorResolving/ErrorUnlocking are all in the Error range. MAINTAINER NOTE: When adding a new result value, add a matching case statement to ToString(EAVResult).
- L47 _public enumerator_ `Unknown = 0`
- L49 _public enumerator_ `Fatal = 1000`
- L50 _public enumerator_ `FatalUnsupported`
- L52 _public enumerator_ `Error = 2000`
- L53 _public enumerator_ `ErrorUnsupported`
- L54 _public enumerator_ `ErrorInvalidState`
- L55 _public enumerator_ `ErrorCreating`
- L56 _public enumerator_ `ErrorDestroying`
- L57 _public enumerator_ `ErrorResolving`
- L58 _public enumerator_ `ErrorMapping`
- L59 _public enumerator_ `ErrorUnmapping`
- L60 _public enumerator_ `ErrorLocking`
- L61 _public enumerator_ `ErrorUnlocking`
- L63 _public enumerator_ `Warning = 3000`
- L64 _public enumerator_ `WarningInvalidState`
- L66 _public enumerator_ `Pending = 4000`
- L67 _public enumerator_ `PendingInput`
- L68 _public enumerator_ `PendingOutput`
- L70 _public enumerator_ `Success = 5000`

#### struct `FAVResult`  
`struct FAVResult`  
_L84-288_
- desc: Primary AV result type. Contains a result code, an optional message, and optional specific data about the platform vendor where the error occured. Automatically logs on warning and lower if not handled.
- L87 _private member_ `static int32 constexpr EMPTY_VENDOR_VALUE = TNumericLimits<int32>::Min();`
- L98 _public function_ `inline static void Log(EAVResult Value, FString const& Message = "", FString const& Vendor = "", int32 VendorValue = EMPTY_VENDOR_VALUE)` — Statically log a result without constructing and returning it. @param Value Low level AV result code. @param Message Optional message to go along with the result code. @param Vendor Optional name of vendor where this error occured. @param VendorValue Optional result code passed to us by the vendor.
- L106 _public member_ `EAVResult Value = EAVResult::Unknown;` — AV result code.
- L111 _public member_ `FString Message = "";` — Optional message alongside AV result code.
- L116 _public member_ `FString Vendor = "";` — Optional vendor where this error occured.
- L121 _public member_ `int32 VendorValue = EMPTY_VENDOR_VALUE;` — Optional result code supplied by the vendor.
- L126 _public member_ `uint8 bHandled : 1;` — Bitflag for whether this result has been handled (or whether is still must be logged).
- L128 _public prototype_ `FAVResult() = default;`
- L136 _public function_ `FAVResult(EAVResult Value, FString const& Message = "", FString const& Vendor = "", int32 VendorValue = EMPTY_VENDOR_VALUE) : Value(Value) , Message(Message) , Vendor(Vendor) , VendorValue(VendorValue) , bHandled(false)` — @param Value Low level AV result code. @param Message Optional message to go along with the result code. @param Vendor Optional name of vendor where this error occured. @param VendorValue Optional result code passed to us by the vendor.
- L145 _public function_ `FAVResult(FAVResult const& From) : Value(From.Value) , Message(From.Message) , Vendor(From.Vendor) , VendorValue(From.VendorValue) , bHandled(From.bHandled)`
- L155 _public function_ `~FAVResult()`
- L164 _public function_ `inline FAVResult& operator=(FAVResult const& From)`
- L177 _public function_ `inline bool operator==(EAVResult OtherValue) const`
- L182 _public function_ `inline bool operator!=(EAVResult OtherValue) const`
- L187 _public function_ `inline operator bool() const`
- L195 _public function_ `inline bool IsFatal() const` — @return True if AV result code is in the range of Fatal.
- L203 _public function_ `inline bool IsNotFatal() const` — @return True if AV result code is NOT in the range of Fatal.
- L211 _public function_ `inline bool IsError() const` — @return True if AV result code is in the range of Error.
- L219 _public function_ `inline bool IsNotError() const` — @return True if AV result code is NOT in the range of Error.
- L227 _public function_ `inline bool IsWarning() const` — @return True if AV result code is in the range of Warning.
- L235 _public function_ `inline bool IsNotWarning() const` — @return True if AV result code is NOT in the range of Warning.
- L243 _public function_ `inline bool IsPending() const` — @return True if AV result code is in the range of Pending.
- L251 _public function_ `inline bool IsNotPending() const` — @return True if AV result code is NOT in the range of Pending.
- L259 _public function_ `inline bool IsSuccess() const` — @return True if AV result code is in the range of Success.
- L267 _public function_ `inline bool IsNotSuccess() const` — @return True if AV result code is NOT in the range of Success.
- L275 _public prototype_ `FAVResult& Handle();` — Flag this result as handled, so that it won't be logged.
- L282 _public prototype_ `FString ToString() const;` — Convert this error into a readable string. @return Pretty string.
- L287 _public prototype_ `void Log() const;` — Logs this result to the internal AVCodecCore log category.

#### struct `TAVResult`  
`template <typename TReturnValue> struct TAVResult : public FAVResult`  
_L294-343_
- inherits: `FAVResult`
- desc: Templated AV result type that allows returning a result code and an optional value. Functions identically to FAVResult.
- L300 _public member_ `TReturnValue ReturnValue;` — Optional return value, is only valid when AV result code is in the range of Success.
- L302 _public prototype_ `TAVResult() = default;`
- L304 _public function_ `TAVResult(TReturnValue const& ReturnValue) : FAVResult(EAVResult::Success) , ReturnValue(ReturnValue)`
- L310 _public function_ `TAVResult(FAVResult const& Result) : FAVResult(Result) , ReturnValue(TReturnValue())`
- L316 _public function_ `TAVResult(TReturnValue const& ReturnValue, FAVResult const& Result) : FAVResult(Result) , ReturnValue(ReturnValue)`
- L322 _public function_ `TAVResult(EAVResult Value, FString const& Message = "", FString const& Vendor = "", int32 VendorValue = -1) : FAVResult(Value, Message, Vendor, VendorValue) , ReturnValue(TReturnValue())`
- L328 _public function_ `TAVResult(TReturnValue const& ReturnValue, EAVResult Value, FString const& Message = "", FString const& Vendor = "", int32 VendorValue = -1) : FAVResult(Value, Message, Vendor, VendorValue) , ReturnValue(ReturnValue)`
- L334 _public function_ `inline operator TReturnValue&()`
- L339 _public function_ `inline operator TReturnValue const&() const`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAVCodecs, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAVCodecs, Log, All);`
- L78 _prototype_ `FString ToString(EAVResult Result);` — AVResult string parser. MAINTAINER NOTE: When adding a new EAVResult value, add a matching case statement to this.

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/AVUtility.h` (Public)


#### class `TResolvable`  
`template <typename TObject, typename... TArgs> class TResolvable`  
_L20-137_
- desc: Base type for a deferred object, to be resolved by an external application with specific and unpredictable requirements. @tparam TObject Type of deferred object. @tparam TArgs Argument list for deferred Resolve function.
- L27 _private member_ `TTuple<TArgs...> ResolvedArgs;` — Stored args used to resolve this resource, to avoid re-resolving the same object. Only valid when a deferred object has been resolved.
- L32 _private member_ `TSharedPtr<TObject> Resolved;` — The possibly-resolved deferred object.
- L35 _public prototype_ `TResolvable() = default;`
- L36 _public prototype_ `virtual ~TResolvable() = default;`
- L38 _public function_ `TObject* Get() const`
- L43 _public function_ `TObject* operator->() const`
- L48 _public function_ `operator TSharedPtr<TObject>&()`
- L53 _public function_ `operator TSharedPtr<TObject> const&() const`
- L58 _public function_ `bool operator==(TResolvable<TObject, TArgs...> const& Other) const`
- L63 _public function_ `bool operator!=(TResolvable<TObject, TArgs...> const& Other) const`
- L68 _public function_ `TSharedRef<TObject> ToSharedRef() const`
- L79 _public function_ `bool IsResolved(TArgs const&... Args) const` — Test whether the deferred object has been successfully resolved with specific arguments. @param Args Arguments that the deferred object must have been resolved with. @return True if the deferred object is valid.
- L94 _public function_ `bool IsResolved() const` — Test whether the deferred object has been successfully resolved. @return True if the deferred object is valid.
- L105 _public function_ `bool Resolve(TArgs const&... Args)` — Attempt to resolve the deferred object with specific arguments. @param Args Arguments that the deferred object must be resolved with. @return True if the deferred object is successfully resolved.
- L121 _public function_ `virtual void Reset()` — Clear the resolved deferred object.
- L136 _protected prototype_ `virtual TSharedPtr<TObject> TryResolve(TArgs const&... Args) = 0;` — Deferred resolve, to be overridden by a variety of implementations. @param Args Arguments that the deferred object must be resolved with. @return Resolved deferred object if successful, invalid if not.

#### class `TDelegated`  
`template <typename TObject, typename... TArgs> class TDelegated : public TResolvable<TObject, TArgs...>`  
_L146-168_
- inherits: `TResolvable<TObject,TArgs...>`
- desc: Delegate-based implementation of TResolvable. @tparam TObject Type of deferred object. @tparam TArgs Argument list for deferred Resolve function.
- L152 _public typedef_ `typedef TFunction<void(TSharedPtr<TObject>&, TArgs...)> FDelegate;` — Delegate definition to be used to resolve the deferred object.
- L153 _public member_ `FDelegate const Delegate;`
- L155 _public function_ `TDelegated(FDelegate const& Delegate) : Delegate(Delegate)`
- L161 _protected function_ `virtual TSharedPtr<TObject> TryResolve(TArgs const&... Args) override`

#### struct `FTypeID`  
`struct FTypeID`  
_L182-221_
- desc: A simple type-erased type identifier, without the use of RTTI or the unreal type system.
- L188 _private member_ `void* Raw;` — Pointer to raw type identifier. Identifier is static so no cleanup.
- L191 _private function_ `FTypeID(void* Raw) : Raw(Raw)` — Private, require all FTypeID's to be valid.
- L203 _public prototype_ `template <typename TType> static FTypeID Get();` — Get the static ID of a type. @tparam TType Type to identify. Must be exported by the REGISTER_TYPEID macro above or this will fail with a linker error.
- L205 _public prototype_ `FTypeID() = default;`
- L207 _public function_ `bool operator==(FTypeID const& Other) const`
- L212 _public function_ `bool operator!=(FTypeID const& Other) const`

#### class `TTypeMap`  
`template <typename TBaseType> class TTypeMap`  
_L227-304_
- desc: Typed map of objects that are uniquely indexed by their type.
- L233 _private member_ `TMap<FTypeID, TSharedPtr<TBaseType>> Objects;` — Type-erased list of objects, stored by their base type.
- L236 _public prototype_ `TTypeMap() = default;`
- L245 _public function_ `template <typename TType UE_REQUIRES(std::is_convertible_v<TType*, TBaseType*>)> bool Contains() const` — Tests whether this map contains an object of a specific type. @tparam TType Type of object to test. @return True if an object of the type exists.
- L257 _public function_ `template <typename TType UE_REQUIRES(std::is_convertible_v<TType*, TBaseType*>)> TSharedPtr<TType> const& Get() const` — Retrieves an object of a specific type, if it already exists in the map. @tparam TType Type of object to find. @return Typed object if it exists in the map, invalid if it does not.
- L276 _public function_ `template <typename TType UE_REQUIRES(std::is_convertible_v<TType*, TBaseType*>)> void Set(TSharedPtr<TType> const& NewObject)` — Add an object to the map, indexed by its type. If an object of this type already exists then replace it. @tparam TType Type of object to add. @param NewObject Object to add.
- L288 _public function_ `template <typename TType UE_REQUIRES(std::is_convertible_v<TType*, TBaseType*>)> TSharedPtr<TType>& Edit()` — Retrieves an object of a specific type, and if it does not exist in the map then create an invalid reference to it (which must then be set by the caller). @tparam TType Type of the object to edit. @return Shared pointer reference to the mapping, invalid if the object did not already exist.
- L300 _public function_ `template <typename TType UE_REQUIRES(std::is_convertible_v<TType*, TBaseType*>)> void Remove(TSharedPtr<TType> const& NewContext)` — Remove an object type from the map. @tparam TType Type of object to add.

#### class `FAPI`  
`class FAPI`  
_L309-357_
- desc: API abstraction with static singletons.
- L315 _private member_ `static TTypeMap<FAPI> Singletons;` — Type-erased map of API singletons.
- L325 _public function_ `template <typename TAPI UE_REQUIRES(std::is_base_of_v<FAPI, TAPI>)> static TAPI const& Get()` — Gets or creates an API of a specific type. @tparam TAPI Type of API to find, which must inherit from FAPI. @return Direct reference to the typed API.
- L342 _public function_ `template <typename TAPI UE_REQUIRES(std::is_base_of_v<FAPI, TAPI>)> static void Shutdown()` — Clean up an API of a specific type. @tparam TAPI Type of the API to clean up, which must inherit from FAPI.
- L352 _public prototype_ `virtual bool IsValid() const = 0;` — Test if the API loaded correctly, or has since been cleaned up. @return True if the API is valid.
- L355 _protected prototype_ `FAPI() = default;`
- L356 _protected prototype_ `virtual ~FAPI() = default;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVCODECSCORE_API`
- L96 _function_ `return ResolvedArgs.ApplyAfter([this](TArgs const&... Args) { return IsResolved(Args...); });` (scope `TResolvable::IsResolved`)
- L173 _macro_ `#define REGISTER_TYPEID(Type) \` — Macro to register a type to be usable with FTypeID.
- L176 _macro_ `#define DECLARE_TYPEID(Type, ExportMacro) \`
- L217 _function_ `friend uint32 GetTypeHash(FTypeID const& Key)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/AudioDecoder.h` (Public)


#### struct `FAudioDecoderConfig`  
`struct FAudioDecoderConfig : public FAVConfig`  
_L13-18_
- inherits: `FAVConfig`
- L16 _public function_ `FAudioDecoderConfig(EAVPreset Preset = EAVPreset::Default) : FAVConfig(Preset)`

#### class `TAudioDecoder`  
`template <typename TResource = void, typename TConfig = void> class TAudioDecoder : public TAVCoder<TAudioDecoder, TResource, TConfig>`  
_L26-110_
- inherits: `TAVCoder<TAudioDecoder,TResource,TConfig>`
- desc: Audio decoder with a factory, that supports typesafe resource handling and configuration. @see TAVCodec
- L93 _public function_ `virtual FAudioDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableAudioResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableAudioResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FAudioPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FAudioDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TAudioDecoder::TWrapper`  
`template <typename TChildResource, typename TChildConfig> class TWrapper : public TAVCoder<TAudioDecoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>`  
_L36-86_
- inherits: `TAVCoder<TAudioDecoder,TResource,TConfig>::templateTWrapper<TChildResource,TChildConfig>`
- desc: Wrapper decoder that transforms resource/config types for use with a differently typed child decoder. @tparam TChildResource Type of child resource. @tparam TChildConfig Type of child config.
- L39 _public function_ `TWrapper(TSharedRef<TAudioDecoder<TChildResource, TChildConfig>> const& Child) : TAVCoder<TAudioDecoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>(Child)`
- L44 _public function_ `virtual FAVResult SendPacket(FAudioPacket const& Packet) override`
- L60 _public function_ `virtual FAVResult ReceiveFrame(TResolvableAudioResource<TResource>& InOutResource) override`

#### class `TAudioDecoder`  
`template <typename TResource> class TAudioDecoder<TResource> : public TAVCoder<TAudioDecoder, TResource>`  
_L118-128_
- inherits: `TAVCoder<TAudioDecoder,TResource>`
- desc: Audio decoder with a factory, that supports typesafe resource handling. @see TAVCodec
- L93 _public function_ `virtual FAudioDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableAudioResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableAudioResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FAudioPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FAudioDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TAudioDecoder`  
`template <> class TAudioDecoder<> : public TAVCoder<TAudioDecoder>`  
_L136-170_
- inherits: `TAVCoder<TAudioDecoder>`
- desc: Audio decoder with a factory. @see TAVCodec
- L93 _public function_ `virtual FAudioDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableAudioResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableAudioResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FAudioPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FAudioDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FAudioDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### Free symbols / members of external scopes

- L68 _function_ `` (scope `TAudioDecoder::TWrapper::ReceiveFrame`)
- L172 _typedef_ `typedef TAudioDecoder<> FAudioDecoder;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/AudioEncoder.h` (Public)


#### struct `FAudioEncoderConfig`  
`struct FAudioEncoderConfig : public FAVConfig`  
_L13-47_
- inherits: `FAVConfig`
- L16 _public member_ `int32 Bitrate = 12000;`
- L17 _public member_ `int32 Samplerate = 44100;`
- L18 _public member_ `int32 NumChannels = 2;`
- L20 _public function_ `FAudioEncoderConfig(EAVPreset Preset = EAVPreset::Default) : FAVConfig(Preset)`

#### class `TAudioEncoder`  
`template <typename TResource = void, typename TConfig = void> class TAudioEncoder : public TAVCoder<TAudioEncoder, TResource, TConfig>`  
_L55-141_
- inherits: `TAVCoder<TAudioEncoder,TResource,TConfig>`
- desc: Audio encoder with a factory, that supports typesafe resource handling and configuration. @see TAVCodec
- L124 _public function_ `virtual FAudioEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L137 _public function_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L159 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @return Result of the operation, @see FAVResult.
- L166 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L176 _public function_ `FAVResult FlushAndReceivePackets(TArray<FAudioPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L203 _public prototype_ `virtual FAVResult ReceivePacket(FAudioPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L211 _public function_ `virtual FAVResult ReceivePackets(TArray<FAudioPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L229 _public prototype_ `virtual FAudioEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L236 _public prototype_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TAudioEncoder::TWrapper`  
`template <typename TChildResource, typename TChildConfig> class TWrapper : public TAVCoder<TAudioEncoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>`  
_L65-117_
- inherits: `TAVCoder<TAudioEncoder,TResource,TConfig>::templateTWrapper<TChildResource,TChildConfig>`
- desc: Wrapper encoder that transforms resource/config types for use with a differently typed child encoder. @tparam TChildResource Type of child resource. @tparam TChildConfig Type of child config.
- L68 _public function_ `TWrapper(TSharedRef<TAudioEncoder<TChildResource, TChildConfig>> const& Child) : TAVCoder<TAudioEncoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>(Child)`
- L73 _public function_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp) override`
- L108 _public function_ `virtual FAVResult ReceivePacket(FAudioPacket& OutPacket) override`

#### class `TAudioEncoder`  
`template <typename TResource> class TAudioEncoder<TResource> : public TAVCoder<TAudioEncoder, TResource>`  
_L149-186_
- inherits: `TAVCoder<TAudioEncoder,TResource>`
- desc: Audio encoder with a factory, that supports typesafe resource handling. @see TAVCodec
- L124 _public function_ `virtual FAudioEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L137 _public function_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L159 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @return Result of the operation, @see FAVResult.
- L166 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L176 _public function_ `FAVResult FlushAndReceivePackets(TArray<FAudioPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L203 _public prototype_ `virtual FAVResult ReceivePacket(FAudioPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L211 _public function_ `virtual FAVResult ReceivePackets(TArray<FAudioPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L229 _public prototype_ `virtual FAudioEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L236 _public prototype_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TAudioEncoder`  
`template <> class TAudioEncoder<> : public TAVCoder<TAudioEncoder>`  
_L194-237_
- inherits: `TAVCoder<TAudioEncoder>`
- desc: Audio encoder with a factory. @see TAVCodec
- L124 _public function_ `virtual FAudioEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L137 _public function_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L159 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @return Result of the operation, @see FAVResult.
- L166 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L176 _public function_ `FAVResult FlushAndReceivePackets(TArray<FAudioPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L203 _public prototype_ `virtual FAVResult ReceivePacket(FAudioPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L211 _public function_ `virtual FAVResult ReceivePackets(TArray<FAudioPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L229 _public prototype_ `virtual FAudioEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L236 _public prototype_ `virtual void SetMinimalConfig(FAudioEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### Free symbols / members of external scopes

- L239 _typedef_ `typedef TAudioEncoder<> FAudioEncoder;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/AudioPacket.h` (Public)


#### struct `FAudioPacket`  
`struct FAudioPacket : public FAVPacket`  
_L11-18_
- inherits: `FAVPacket`
- desc: Audio-specific packet container.
- L13 _public prototype_ `FAudioPacket() = default;`
- L14 _public function_ `FAudioPacket(TSharedPtr<uint8> const& DataPtr, uint64 DataSize, uint64 Timestamp, uint64 Index) : FAVPacket(DataPtr, DataSize, Timestamp, Index)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/AudioResource.h` (Public)


#### struct `FAudioDescriptor`  
`struct FAudioDescriptor`  
_L40-69_
- desc: This struct defines how the allocated resource memory is used in the context of audio.
- L46 _public member_ `uint32 NumSamples;` — Number of samples in this resource.
- L51 _public member_ `float SampleDuration;` — Duration of samples in this resource.
- L53 _public prototype_ `FAudioDescriptor() = default;`
- L54 _public function_ `FAudioDescriptor(uint32 NumSamples, float SampleDuration) : NumSamples(NumSamples) , SampleDuration(SampleDuration)`
- L60 _public function_ `bool operator==(FAudioDescriptor const& RHS) const`
- L65 _public function_ `bool operator!=(FAudioDescriptor const& RHS) const`

#### class `FAudioResource`  
`class FAudioResource : public FAVResource`  
_L74-100_
- inherits: `FAVResource`
- desc: Base wrapper for a audio device resource.
- L80 _private member_ `FAudioDescriptor Descriptor;` — Descriptor of audio data in device memory.
- L86 _public function_ `inline FAudioDescriptor const& GetDescriptor() const` — @return Get the descriptor of our audio data in device memory.
- L91 _public function_ `inline float GetNumSamples() const` — @return Get the number of samples in our data in device memory.
- L96 _public function_ `inline float GetSampleDuration() const` — @return Get the duration of our data in device memory.
- L98 _public prototype_ `FAudioResource(TSharedRef<FAVDevice> const& Device, FAVLayout const& Layout, FAudioDescriptor const& Descriptor);`
- L99 _public prototype_ `virtual ~FAudioResource() override = default;`

#### class `TAudioResource`  
`template <typename TContext> class TAudioResource : public FAudioResource`  
_L106-115_
- inherits: `FAudioResource`
- desc: Convenience wrapper for a audio device resource that requires a specific device context to function.
- L109 _public function_ `inline TSharedPtr<TContext> GetContext() const`
- L111 _public function_ `TAudioResource(TSharedRef<FAVDevice> const& Device, FAVLayout const& Layout, FAudioDescriptor const& Descriptor) : FAudioResource(Device, Layout, Descriptor)`

#### class `TPooledAudioResource`  
`template <typename TResource> class TPooledAudioResource : public TResolvableAudioResource<TResource>`  
_L133-156_
- inherits: `TResolvableAudioResource<TResource>`
- desc: A simple pool-based resolvable audio resource. The contents of the pool must be manually managed by the application.
- L136 _public member_ `TArray<TSharedPtr<TResource>> Pool;`
- L138 _public function_ `virtual bool IsResolved(TSharedPtr<FAVDevice> const& Device, FAudioDescriptor const& Descriptor) const override`
- L144 _protected function_ `virtual TSharedPtr<TResource> TryResolve(TSharedPtr<FAVDevice> const& Device, FAudioDescriptor const& Descriptor) override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVCODECSCORE_API`
- L121 _typedef_ `template <typename TResource> using TResolvableAudioResource = TResolvable<TResource, TSharedPtr<FAVDevice>, FAudioDescriptor>;` — Wrapper for resolvable audio resources.
- L127 _typedef_ `template <typename TResource> using TDelegatedAudioResource = TDelegated<TResource, TSharedPtr<FAVDevice>, FAudioDescriptor>;` — Wrapper for delegated resolvable audio resources.

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/Encoders/Configs/AudioEncoderConfigAAC.h` (Public)


#### struct `FAudioEncoderConfigAAC`  
`struct FAudioEncoderConfigAAC : public FAudioEncoderConfig`  
_L10-17_
- inherits: `FAudioEncoderConfig`
- desc: Configuration settings for AAC encoders.
- L13 _public function_ `FAudioEncoderConfigAAC(EAVPreset Preset = EAVPreset::Default) : FAudioEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Audio/Resources/AudioResourceCPU.h` (Public)


#### class `FAudioContextCPU`  
`class FAudioContextCPU : public FAVContext`  
_L14-18_
- inherits: `FAVContext`
- L17 _public prototype_ `FAudioContextCPU();`

#### class `FAudioResourceCPU`  
`class FAudioResourceCPU : public TAudioResource<FAudioContextCPU>`  
_L20-32_
- inherits: `TAudioResource<FAudioContextCPU>`
- L23 _private member_ `TSharedPtr<float> Raw;`
- L26 _public function_ `inline TSharedPtr<float> const& GetRaw() const`
- L28 _public prototype_ `FAudioResourceCPU(TSharedRef<FAVDevice> const& Device, TSharedPtr<float> const& Raw, FAVLayout const& Layout, FAudioDescriptor const& Descriptor);`
- L29 _public prototype_ `virtual ~FAudioResourceCPU() override = default;`
- L31 _public prototype_ `virtual FAVResult Validate() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Utils/BitstreamReader.h` (Public)


#### struct `TBitSizeOf`  
`template <typename Type> struct TBitSizeOf`  
_L14-17_
- L16 _public member_ `static constexpr uint16 Value = sizeof(Type) * 8;`
- L341 _public member_ `static constexpr uint16 Value = NumBits;`

#### struct `FBitstreamSegment`  
`struct FBitstreamSegment`  
_L25-110_
- desc: Base class for a compressed block of bitstream data. Provides scoped access to some parsing types for use with FBitstreamReader.
- L82 _public typedef_ `using UE = UnsignedExpGolomb<>;`
- L109 _public typedef_ `using SE = SignedExpGolomb<>;`

#### struct `FBitstreamSegment::U`  
`template <uint8 NumBits = 0, typename ValueType = TBitSizeContainer<NumBits>> struct U`  
_L31-55_
- desc: Unsigned int, compressed to a fixed number of bits.
- L34 _public member_ `ValueType Value = ValueType();`
- L36 _public prototype_ `U() = default;`
- L37 _public function_ `U(ValueType const& Value) : Value(Value)`
- L39 _public function_ `operator ValueType() const`
- L44 _public function_ `bool AsBool() const`
- L49 _public function_ `U& operator=(ValueType const& From)`
- L321 _public member_ `uint32 Value = 0;`
- L324 _public function_ `U(uint32 const& Value) : Value(Value)`
- L326 _public function_ `operator uint32() const`
- L331 _public function_ `U& operator=(uint32 From)`

#### struct `FBitstreamSegment::UnsignedExpGolomb`  
`template <typename ValueType = uint32> struct UnsignedExpGolomb`  
_L61-80_
- desc: Unsigned int, compressed to a dynamic number of bits.
- L64 _public member_ `ValueType Value = static_cast<ValueType>(0);`
- L66 _public prototype_ `UnsignedExpGolomb() = default;`
- L67 _public function_ `UnsignedExpGolomb(ValueType Value) : Value(Value)`
- L69 _public function_ `operator ValueType() const`
- L74 _public function_ `UnsignedExpGolomb& operator=(ValueType From)`

#### struct `FBitstreamSegment::SignedExpGolomb`  
`template <typename ValueType = int32> struct SignedExpGolomb`  
_L88-107_
- desc: Signed int, compressed to a dynamic number of bits.
- L91 _public member_ `ValueType Value = static_cast<ValueType>(0);`
- L93 _public prototype_ `SignedExpGolomb() = default;`
- L94 _public function_ `SignedExpGolomb(ValueType Value) : Value(Value)`
- L96 _public function_ `operator ValueType() const`
- L101 _public function_ `SignedExpGolomb& operator=(ValueType From)`

#### struct `FBitstreamReader`  
`struct FBitstreamReader`  
_L115-314_
- desc: Simple wrapper for typed reads from a bitstream.
- L118 _public function_ `FBitstreamReader(uint8* Data, uint64 DataSize, uint64 BytePosition = 0, uint8 BitPosition = 0) : Data(Data) , DataSize(DataSize) , BytePosition(BytePosition) , BitPosition(BitPosition)`
- L126 _public function_ `bool IsByteAligned() const`
- L131 _public function_ `uint8* GetDataRemaining() const`
- L136 _public function_ `uint64 NumBytesRemaining() const`
- L141 _public function_ `uint64 NumBitsRemaining() const`
- L146 _public function_ `void Seek(uint64 NewBytePosition, uint32 NewBitPosition = 0)`
- L152 _public function_ `void SkipBytes(uint64 NumBytes)`
- L157 _public function_ `void SkipBits(uint64 NumBits)`
- L163 _public function_ `uint32 PeekBits(uint64 NumBits) const`
- L231 _public function_ `uint32 ReadBits(uint64 NumBits)`
- L242 _public function_ `uint64 ReadBits64(uint64 NumBits)`
- L258 _public function_ `template <typename TOutput> void ReadBits(TOutput& Output, uint64 NumBits)`
- L268 _public function_ `template <typename TOutput> void Read(TOutput& Output)`
- L274 _public function_ `template <typename ValueType> void Read(FBitstreamSegment::UnsignedExpGolomb<ValueType>& Output)`
- L293 _public function_ `template <typename ValueType> void Read(FBitstreamSegment::SignedExpGolomb<ValueType>& Output)`
- L302 _public function_ `template <typename TOutput, typename... TOutputs> void Read(TOutput& Output, TOutputs&... Outputs)`
- L309 _private member_ `uint8* Data;`
- L310 _private member_ `uint64 DataSize;`
- L312 _private member_ `uint64 BytePosition;`
- L313 _private member_ `uint8 BitPosition;`
- L345 _prototype_ `template <> void FBitstreamReader::Read(FBitstreamSegment::U<0>& Output) = delete;`

#### struct `FBitstreamSegment::U`  
`template <typename ValueType> struct FBitstreamSegment::U<0, ValueType>`  
_L318-336_
- desc: Requires template param for ValueType, so that all instantiations of U<0> route through this (and more importantly, the deleted specialization of FBitstreamReader::Read)
- L34 _public member_ `ValueType Value = ValueType();`
- L36 _public prototype_ `U() = default;`
- L37 _public function_ `U(ValueType const& Value) : Value(Value)`
- L39 _public function_ `operator ValueType() const`
- L44 _public function_ `bool AsBool() const`
- L49 _public function_ `U& operator=(ValueType const& From)`
- L321 _public member_ `uint32 Value = 0;`
- L324 _public function_ `U(uint32 const& Value) : Value(Value)`
- L326 _public function_ `operator uint32() const`
- L331 _public function_ `U& operator=(uint32 From)`

#### struct `TBitSizeOf`  
`template <int32 NumBits, typename ValueType> struct TBitSizeOf<FBitstreamSegment::U<NumBits, ValueType>>`  
_L339-342_
- L16 _public member_ `static constexpr uint16 Value = sizeof(Type) * 8;`
- L341 _public member_ `static constexpr uint16 Value = NumBits;`

#### struct `FNalu`  
`struct FNalu : public FBitstreamSegment`  
_L347-349_
- inherits: `FBitstreamSegment`

#### Free symbols / members of external scopes

- L20 _typedef_ `template <uint8 NumBits> using TBitSizeContainer = typename TTupleElement<(NumBits > 8) + (NumBits > 16) + (NumBits > 32), TTuple<uint8, uint16, uint32, uint64>>::Type;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/CodecUtils/CodecUtilsAV1.h` (Public)


#### enum `EAV1Profile`  
`enum class EAV1Profile : uint8`  
_L11-19_
- L13 _public enumerator_ `Auto`
- L14 _public enumerator_ `Main`
- L18 _public enumerator_ `MAX` — We currently don't support these other profiles High, Professional,

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/CodecUtils/CodecUtilsH264.h` (Public)


#### enum `EH264Profile`  
`enum class EH264Profile : uint8`  
_L24-50_
- reflection: `UENUM()`
- L26 _public enumerator_ `Auto`
- L27 _public enumerator_ `CALVLC444Intra`
- L28 _public enumerator_ `Baseline`
- L29 _public enumerator_ `ConstrainedBaseline`
- L30 _public enumerator_ `Main`
- L31 _public enumerator_ `ScalableBaseline`
- L32 _public enumerator_ `ScalableConstrainedBaseline`
- L33 _public enumerator_ `ScalableHigh`
- L34 _public enumerator_ `ScalableConstrainedHigh`
- L35 _public enumerator_ `ScalableHighIntra`
- L36 _public enumerator_ `Extended`
- L37 _public enumerator_ `High`
- L38 _public enumerator_ `ProgressiveHigh`
- L39 _public enumerator_ `ConstrainedHigh`
- L40 _public enumerator_ `High10`
- L41 _public enumerator_ `High10Intra`
- L42 _public enumerator_ `MultiviewHigh`
- L43 _public enumerator_ `High422`
- L44 _public enumerator_ `High422Intra`
- L45 _public enumerator_ `StereoHigh`
- L46 _public enumerator_ `MultiviewDepthHigh`
- L47 _public enumerator_ `High444`
- L48 _public enumerator_ `High444Intra`
- L49 _public enumerator_ `MAX`

#### enum `EH264AdaptiveTransformMode`  
`enum class EH264AdaptiveTransformMode : uint8`  
_L52-57_
- L54 _public enumerator_ `Auto`
- L55 _public enumerator_ `Disable`
- L56 _public enumerator_ `Enable`

#### enum `EH264EntropyCodingMode`  
`enum class EH264EntropyCodingMode : uint8`  
_L59-64_
- L61 _public enumerator_ `Auto`
- L62 _public enumerator_ `CABAC`
- L63 _public enumerator_ `CAVLC`

#### enum `EH264PacketizationMode`  
`enum class EH264PacketizationMode : uint8`  
_L70-74_
- desc: Packetization modes are defined in RFC 6184 section 6 Due to the structure containing this being initialized with zeroes in some places, and mode 1 being default, mode 1 needs to have the value zero.
- L72 _public enumerator_ `NonInterleaved = 0` — Mode 1 - STAP-A, FU-A is allowed
- L73 _public enumerator_ `SingleNalUnit` — Mode 0 - only single NALU allowed

#### enum `UE::AVCodecCore::H264::ENaluType`  
`enum class ENaluType : uint8`  
_L80-114_
- L82 _public enumerator_ `Unspecified = 0`
- L83 _public enumerator_ `SliceOfNonIdrPicture = 1`
- L84 _public enumerator_ `SliceDataPartitionA = 2`
- L85 _public enumerator_ `SliceDataPartitionB = 3`
- L86 _public enumerator_ `SliceDataPartitionC = 4`
- L87 _public enumerator_ `SliceIdrPicture = 5`
- L88 _public enumerator_ `SupplementalEnhancementInformation = 6`
- L89 _public enumerator_ `SequenceParameterSet = 7`
- L90 _public enumerator_ `PictureParameterSet = 8`
- L91 _public enumerator_ `AccessUnitDelimiter = 9`
- L92 _public enumerator_ `EndOfSequence = 10`
- L93 _public enumerator_ `EndOfStream = 11`
- L94 _public enumerator_ `FillerData = 12`
- L95 _public enumerator_ `SequenceParameterSetExtension = 13`
- L96 _public enumerator_ `PrefixNalUnit = 14`
- L97 _public enumerator_ `SubsetSequenceParameterSet = 15`
- L98 _public enumerator_ `Reserved16 = 16`
- L99 _public enumerator_ `Reserved17 = 17`
- L100 _public enumerator_ `Reserved18 = 18`
- L101 _public enumerator_ `SliceOfAnAuxiliaryCoded = 19`
- L102 _public enumerator_ `SliceExtension = 20`
- L103 _public enumerator_ `SliceExtensionForDepthView = 21`
- L104 _public enumerator_ `Reserved22 = 22`
- L105 _public enumerator_ `Reserved23 = 23`
- L106 _public enumerator_ `Unspecified24 = 24`
- L107 _public enumerator_ `Unspecified25 = 25`
- L108 _public enumerator_ `Unspecified26 = 26`
- L109 _public enumerator_ `Unspecified27 = 27`
- L110 _public enumerator_ `Unspecified28 = 28`
- L111 _public enumerator_ `Unspecified29 = 29`
- L112 _public enumerator_ `Unspecified30 = 30`
- L113 _public enumerator_ `Unspecified31 = 31`

#### enum `UE::AVCodecCore::H264::EH264ProfileIDC`  
`enum class EH264ProfileIDC : uint8`  
_L116-143_
- L118 _public enumerator_ `Auto = 0`
- L119 _public enumerator_ `CALVLC444Intra = 44`
- L120 _public enumerator_ `Baseline = 66`
- L122 _public enumerator_ `Main = 77` — ConstrainedBaseline = 66,			with constraint flag 1 set
- L123 _public enumerator_ `ScalableBaseline = 83`
- L125 _public enumerator_ `ScalableHigh = 86` — ScalableConstrainedBaseline = 83,	with constraint flag 5 set
- L128 _public enumerator_ `Extended = 88` — ScalableConstrainedHigh = 86,		with constraint flag 5 set ScalableHighIntra = 86,				with constraint flag 3 set
- L129 _public enumerator_ `High = 100`
- L132 _public enumerator_ `High10 = 110` — ProgressiveHigh = 100,				with constraint flag 4 set ConstrainedHigh = 100,				with constraint flag 4 & 5 set
- L134 _public enumerator_ `MultiviewHigh = 118` — High10Intra = 110,					with constraint flag 3 set
- L135 _public enumerator_ `High422 = 122`
- L137 _public enumerator_ `StereoHigh = 128` — High422Intra = 122,					with constraint flag 3 set
- L138 _public enumerator_ `MultiresolutionFrameCompatibleHigh = 134`
- L139 _public enumerator_ `MultiviewDepthHigh = 138`
- L140 _public enumerator_ `EnhancedMultiviewDepthHigh = 139`
- L141 _public enumerator_ `High444 = 244`

#### enum `UE::AVCodecCore::H264::EH264ConstraintFlag`  
`enum class EH264ConstraintFlag : uint8`  
_L145-154_
- L147 _public enumerator_ `None = 0`
- L148 _public enumerator_ `Set0 = 1u << 0`
- L149 _public enumerator_ `Set1 = 1u << 1`
- L150 _public enumerator_ `Set2 = 1u << 2`
- L151 _public enumerator_ `Set3 = 1u << 3`
- L152 _public enumerator_ `Set4 = 1u << 4`
- L153 _public enumerator_ `Set5 = 1u << 5`

#### enum `UE::AVCodecCore::H264::EH264Level`  
`enum class EH264Level : uint8`  
_L181-203_
- L183 _public enumerator_ `Level_1b = 0`
- L184 _public enumerator_ `Level_1 = 10`
- L185 _public enumerator_ `Level_1_1 = 11`
- L186 _public enumerator_ `Level_1_2 = 12`
- L187 _public enumerator_ `Level_1_3 = 13`
- L188 _public enumerator_ `Level_2 = 20`
- L189 _public enumerator_ `Level_2_1 = 21`
- L190 _public enumerator_ `Level_2_2 = 22`
- L191 _public enumerator_ `Level_3 = 30`
- L192 _public enumerator_ `Level_3_1 = 31`
- L193 _public enumerator_ `Level_3_2 = 32`
- L194 _public enumerator_ `Level_4 = 40`
- L195 _public enumerator_ `Level_4_1 = 41`
- L196 _public enumerator_ `Level_4_2 = 42`
- L197 _public enumerator_ `Level_5 = 50`
- L198 _public enumerator_ `Level_5_1 = 51`
- L199 _public enumerator_ `Level_5_2 = 52`

#### enum `UE::AVCodecCore::H264::EH264AspectRatioIDC`  
`enum class EH264AspectRatioIDC : uint8`  
_L205-226_
- L207 _public enumerator_ `Unspecified = 0`
- L208 _public enumerator_ `Square = 1` — 1x1
- L209 _public enumerator_ `_12x11 = 2`
- L210 _public enumerator_ `_10x11 = 3`
- L211 _public enumerator_ `_16x11 = 4`
- L212 _public enumerator_ `_40x33 = 5`
- L213 _public enumerator_ `_24x11 = 6`
- L214 _public enumerator_ `_20x11 = 7`
- L215 _public enumerator_ `_32x11 = 8`
- L216 _public enumerator_ `_80x33 = 9`
- L217 _public enumerator_ `_18x11 = 10`
- L218 _public enumerator_ `_15x11 = 11`
- L219 _public enumerator_ `_64x33 = 12`
- L220 _public enumerator_ `_160x99 = 13`
- L221 _public enumerator_ `_4x3 = 14`
- L222 _public enumerator_ `_3x2 = 15`
- L223 _public enumerator_ `_2x1 = 16`
- L224 _public enumerator_ `Reserved = 17`
- L225 _public enumerator_ `Extended_SAR = 255`

#### enum `UE::AVCodecCore::H264::EH264VideoFormat`  
`enum class EH264VideoFormat : uint8`  
_L228-238_
- L230 _public enumerator_ `Component = 0`
- L231 _public enumerator_ `PAL = 1`
- L232 _public enumerator_ `NTSC = 2`
- L233 _public enumerator_ `SECAM = 3`
- L234 _public enumerator_ `MAC = 4`
- L235 _public enumerator_ `Unspecified = 5`
- L236 _public enumerator_ `Reserved6 = 6`
- L237 _public enumerator_ `Reserved7 = 7`

#### struct `FH264ProfileDefinition`  
`struct FH264ProfileDefinition`  
_L241-247_
- L243 _public member_ `EH264Profile Profile;`
- L244 _public member_ `UE::AVCodecCore::H264::EH264ProfileIDC PIDC;`
- L245 _public member_ `UE::AVCodecCore::H264::EH264ConstraintFlag ConstraintFlags;`
- L246 _public member_ `const TCHAR* Name;`

#### struct `UE::AVCodecCore::H264::FNaluH264`  
`struct FNaluH264`  
_L274-281_
- L276 _public member_ `uint64 Start, Size;`
- L276 _public member_ `uint64 Start, Size;`
- L277 _public member_ `uint8 StartCodeSize;`
- L278 _public member_ `uint8 RefIdc;`
- L279 _public member_ `ENaluType Type;`
- L280 _public member_ `const uint8* Data;`

#### struct `UE::AVCodecCore::H264::SPS_t`  
`struct SPS_t : public FNalu`  
_L373-467_
- inherits: `FNalu`
- L376 _public member_ `U<8, EH264ProfileIDC> profile_idc = EH264ProfileIDC::Auto;`
- L377 _public member_ `U<8, EH264ConstraintFlag> constraint_flags = EH264ConstraintFlag::None;`
- L378 _public member_ `U<8> level_idc;` — + profile_idc + constraint_flags = EH264Level
- L379 _public member_ `UE seq_parameter_set_id;` — 0...31 inclusive
- L380 _public member_ `UE chroma_format_idc = 1;` — 0...3 inclusive
- L381 _public member_ `U<1> separate_colour_plane_flag;` — bool
- L382 _public member_ `UE bit_depth_luma_minus8;` — 0...6 inclusive
- L383 _public member_ `UE bit_depth_chroma_minus8;` — 0...6 inclusive
- L384 _public member_ `U<1> qpprime_y_zero_transform_bypass_flag;` — 0...1 inclusive
- L385 _public member_ `U<1> seq_scaling_matrix_present_flag;` — bool
- L386 _public member_ `U<1> seq_scaling_list_present_flag[12];` — bool array
- L387 _public member_ `uint8 ScalingList4x4[6][16];` — -2^(1+BitDepth)...2^(1+BitDepth)-1 inclusive
- L388 _public member_ `uint8 ScalingList8x8[6][64];` — -2^(1+BitDepth)...2^(1+BitDepth)-1 inclusive
- L389 _public member_ `UE log2_max_frame_num_minus4;` — 0...12 inclusive
- L390 _public member_ `UE pic_order_cnt_type;` — 0...3 inclusive
- L391 _public member_ `UE log2_max_pic_order_cnt_lsb_minus4;` — 0...12 inclusive
- L392 _public member_ `U<1> delta_pic_order_always_zero_flag;` — bool
- L393 _public member_ `SE offset_for_non_ref_pic;` — −2^(31)+1...2^(31)−1 inclusive
- L394 _public member_ `SE offset_for_top_to_bottom_field;` — −2^(31)+1...2^(31)−1 inclusive
- L395 _public member_ `UE num_ref_frames_in_pic_order_cnt_cycle;` — 0...255 inclusive
- L396 _public member_ `SE offset_for_ref_frame[255];` — −2^(31)+1...2^(31)−1 inclusive
- L397 _public member_ `UE max_num_ref_frames;` — 0...MaxDpbFrames inclusive MaxDpbFrames = Min( MaxDecPicBufSizeMacro / ( PicWidthMacro * FrameHeightMacro ), 16) (A.3.1 or A.3.2)
- L398 _public member_ `U<1> gaps_in_frame_num_value_allowed_flag;` — bool
- L399 _public member_ `UE pic_width_in_mbs_minus1;` — + 1 = Width in macroblocks
- L400 _public member_ `UE pic_height_in_map_units_minus1;` — + 1 = Height
- L401 _public member_ `U<1> frame_mbs_only_flag;` — bool
- L402 _public member_ `U<1> mb_adaptive_frame_field_flag;` — bool
- L403 _public member_ `U<1> direct_8x8_inference_flag;` — bool
- L404 _public member_ `U<1> frame_cropping_flag;` — bool
- L405 _public member_ `UE frame_crop_left_offset;`
- L406 _public member_ `UE frame_crop_right_offset;`
- L407 _public member_ `UE frame_crop_top_offset;`
- L408 _public member_ `UE frame_crop_bottom_offset;`
- L409 _public member_ `U<1> vui_parameters_present_flag;` — bool
- L411 _public member_ `U<1> aspect_ratio_info_present_flag;` — VUI Parameters
- L412 _public member_ `U<8, EH264AspectRatioIDC> aspect_ratio_idc = EH264AspectRatioIDC::Unspecified;`
- L413 _public member_ `U<16> sar_width;` — Width in arbitrary unit
- L414 _public member_ `U<16> sar_height;` — Height in same arbitrary unit as Width
- L415 _public member_ `U<1> overscan_info_present_flag;` — bool
- L416 _public member_ `U<1> overscan_appropriate_flag;` — bool
- L417 _public member_ `U<1> video_signal_type_present_flag;` — bool
- L418 _public member_ `U<3, EH264VideoFormat> video_format = EH264VideoFormat::Unspecified;`
- L419 _public member_ `U<1> video_full_range_flag;` — bool
- L420 _public member_ `U<1> colour_description_present_flag;` — bool
- L421 _public member_ `U<8> colour_primaries = 2;` — 0...255 inclusive but see Table E-3 as many values are Reserved
- L422 _public member_ `U<8> transfer_characteristics = 2;` — 0...255 inclusive but see Table E-4 as many values are Reserved
- L423 _public member_ `U<8> matrix_coefficients = 2;` — 0...255 inclusive but see Table E-5 as many values are Reserved
- L424 _public member_ `U<1> chroma_loc_info_present_flag;` — bool
- L425 _public member_ `UE chroma_sample_loc_type_top_field;` — 0...5 inclusive
- L426 _public member_ `UE chroma_sample_loc_type_bottom_field;` — 0...5 inclusive
- L427 _public member_ `U<1> timing_info_present_flag;` — bool
- L428 _public member_ `U<32> num_units_in_tick = 1;` — > 0
- L429 _public member_ `U<32> time_scale = 1000;` — defaulted to ms
- L430 _public member_ `U<1> fixed_frame_rate_flag;` — bool
- L431 _public member_ `U<1> nal_hrd_parameters_present_flag;` — bool
- L432 _public member_ `U<1> vcl_hrd_parameters_present_flag;` — bool
- L433 _public member_ `U<1> low_delay_hrd_flag;` — bool
- L434 _public member_ `U<1> pic_struct_present_flag;` — bool
- L435 _public member_ `U<1> bitstream_restriction_flag;` — bool
- L436 _public member_ `U<1> motion_vectors_over_pic_boundaries_flag;` — bool
- L437 _public member_ `UE max_bytes_per_pic_denom;`
- L438 _public member_ `UE max_bits_per_mb_denom;`
- L439 _public member_ `UE log2_max_mv_length_horizontal;`
- L440 _public member_ `UE log2_max_mv_length_vertical;`
- L441 _public member_ `UE max_num_reorder_frames;`
- L442 _public member_ `UE max_dec_frame_buffering;`
- L444 _public member_ `UE cpb_cnt_minus1;` — HRD Parameters
- L445 _public member_ `U<4> bit_rate_scale;`
- L446 _public member_ `U<4> cpb_size_scale;`
- L447 _public member_ `UE bit_rate_value_minus1[31];` — 0...2^(32)−2 inclusive TODO (aidan) might need an infer stage to fill out based on profile
- L448 _public member_ `UE cpb_size_value_minus1[31];` — 0...2^(32)−2 inclusive TODO (aidan) might need an infer stage to fill out based on profile
- L449 _public member_ `U<1> cbr_flag[31];` — bool
- L450 _public member_ `U<5> initial_cpb_removal_delay_length_minus1 = 23;`
- L451 _public member_ `U<5> cpb_removal_delay_length_minus1 = 23;`
- L452 _public member_ `U<5> dpb_output_delay_length_minus1 = 23;`
- L453 _public member_ `U<5> time_offset_length = 24;`
- L455 _public function_ `EH264Profile GetProfile() const`

#### struct `UE::AVCodecCore::H264::PPS_t`  
`struct PPS_t : public FNalu`  
_L471-502_
- inherits: `FNalu`
- L473 _public member_ `UE pic_parameter_set_id;`
- L474 _public member_ `UE seq_parameter_set_id;`
- L475 _public member_ `U<1> entropy_coding_mode_flag;`
- L476 _public member_ `U<1> bottom_field_pic_order_in_frame_present_flag;`
- L477 _public member_ `UE num_slice_groups_minus1;`
- L478 _public member_ `UE slice_group_map_type;`
- L479 _public member_ `TArray<UE> run_length_minus1;` — hard to justify preallocating this as it could be PicWidthInMbs * PicHeightInMapUnits - 1
- L480 _public member_ `TArray<UE> top_left;` — hard to justify preallocating this as it could be PicWidthInMbs * PicHeightInMapUnits - 1
- L481 _public member_ `TArray<UE> bottom_right;` — hard to justify preallocating this as it could be PicWidthInMbs * PicHeightInMapUnits - 1
- L482 _public member_ `U<1> slice_group_change_direction_flag;`
- L483 _public member_ `UE slice_group_change_rate_minus1;`
- L484 _public member_ `UE pic_size_in_map_units_minus1;`
- L485 _public member_ `TArray<U<>> slice_group_id;` — hard to justify preallocating this as it could be pic_size_in_map_units_minus1 + 1
- L486 _public member_ `UE num_ref_idx_l0_default_active_minus1;`
- L487 _public member_ `UE num_ref_idx_l1_default_active_minus1;`
- L488 _public member_ `U<1> weighted_pred_flag;`
- L489 _public member_ `U<2> weighted_bipred_idc;`
- L490 _public member_ `SE pic_init_qp_minus26;`
- L491 _public member_ `SE pic_init_qs_minus26;`
- L492 _public member_ `SE chroma_qp_index_offset;`
- L493 _public member_ `U<1> deblocking_filter_control_present_flag;`
- L494 _public member_ `U<1> constrained_intra_pred_flag;`
- L495 _public member_ `U<1> redundant_pic_cnt_present_flag;`
- L496 _public member_ `U<1> transform_8x8_mode_flag;`
- L497 _public member_ `U<1> pic_scaling_matrix_present_flag;`
- L498 _public member_ `U<1> pic_scaling_list_present_flag[12];`
- L499 _public member_ `uint8 ScalingList4x4[6][16];` — -2^(1+BitDepth)...2^(1+BitDepth)-1 inclusive
- L500 _public member_ `uint8 ScalingList8x8[6][64];` — -2^(1+BitDepth)...2^(1+BitDepth)-1 inclusive
- L501 _public member_ `SE second_chroma_qp_index_offset;`

#### struct `UE::AVCodecCore::H264::Slice_t`  
`struct Slice_t : public FNalu`  
_L506-557_
- inherits: `FNalu`
- L508 _public member_ `UE first_mb_in_slice;`
- L509 _public member_ `UE slice_type;`
- L510 _public member_ `UE pic_parameter_set_id;`
- L511 _public member_ `U<2> colour_plane_id;`
- L512 _public member_ `U<> frame_num;`
- L513 _public member_ `U<1> field_pic_flag;`
- L514 _public member_ `U<1> bottom_field_flag;`
- L515 _public member_ `UE idr_pic_id;`
- L516 _public member_ `U<> pic_order_cnt_lsb;`
- L517 _public member_ `SE delta_pic_order_cnt_bottom;`
- L518 _public member_ `SE delta_pic_order_cnt[2];`
- L519 _public member_ `UE redundant_pic_cnt;`
- L520 _public member_ `U<1> direct_spatial_mv_pred_flag;`
- L521 _public member_ `U<1> num_ref_idx_active_override_flag;`
- L522 _public member_ `UE num_ref_idx_l0_active_minus1;`
- L523 _public member_ `UE num_ref_idx_l1_active_minus1;`
- L524 _public member_ `UE cabac_init_idc;`
- L525 _public member_ `SE slice_qp_delta;`
- L526 _public member_ `U<1> sp_for_switch_flag;`
- L527 _public member_ `SE slice_qs_delta;`
- L528 _public member_ `UE disable_deblocking_filter_idc;`
- L529 _public member_ `SE slice_alpha_c0_offset_div2;`
- L530 _public member_ `SE slice_beta_offset_div2;`
- L531 _public member_ `U<> slice_group_change_cycle;`
- L540 _public member_ `U<1> ref_pic_list_modification_flag_l0;`
- L542 _public member_ `U<1> ref_pic_list_modification_flag_l1;` — TArray<RefPic_t> RefPicList0;
- L548 _public member_ `U<1> no_output_of_prior_pic_flag;` — dec_ref_pic_marking
- L549 _public member_ `U<1> long_term_reference_flag;`
- L551 _public member_ `U<1> adaptive_ref_pic_marking_mode_flag;`
- L553 _public member_ `UE difference_of_pic_nums_minus1;`
- L554 _public member_ `UE long_term_pic_num;`
- L555 _public member_ `UE long_term_frame_idx;`
- L556 _public member_ `UE max_long_term_frame_idx_plus1;`

#### struct `UE::AVCodecCore::H264::Slice_t::RefPic_t`  
`struct RefPic_t`  
_L534-538_
- desc: ref_pic_list_modification
- L536 _public member_ `U<1> bIsLongTerm;`
- L537 _public member_ `UE pic_num;`

#### struct `UE::AVCodecCore::H264::SEI_t`  
`struct SEI_t`  
_L562-564_
- desc: SEI can transmit arbitrary data so we probably want something less rigid for this

#### Free symbols / members of external scopes

- L76 _externvar_ `extern FH264ProfileDefinition GH264ProfileDefinitions[static_cast<uint8>(EH264Profile::MAX)];`
- L78 _namespace_ `namespace UE`
- L78 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L78 _namespace_ `namespace H264` (scope `UE::AVCodecCore`)
- L156 _function_ `inline EH264ConstraintFlag operator|(EH264ConstraintFlag const& lhs, EH264ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H264`)
- L161 _function_ `inline EH264ConstraintFlag operator&(EH264ConstraintFlag const& lhs, EH264ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H264`)
- L166 _function_ `inline EH264ConstraintFlag operator|=(EH264ConstraintFlag const& lhs, EH264ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H264`)
- L171 _function_ `inline bool operator==(EH264ConstraintFlag lhs, EH264ConstraintFlag rhs)` (scope `UE::AVCodecCore::H264`)
- L176 _function_ `inline uint8 operator&(uint8 const& lhs, EH264ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H264`)
- L249 _namespace_ `namespace UE`
- L249 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L249 _namespace_ `namespace H264` (scope `UE::AVCodecCore`)
- L251 _function_ `inline int32 EBSPtoRBSP(uint8* OutBuf, const uint8* InBuf, int32 NumBytesIn)` (scope `UE::AVCodecCore::H264`)
- L283 _prototype_ `FAVResult FindNALUs(FVideoPacket const& InPacket, TArray<FNaluH264>& FoundNalus);` (scope `UE::AVCodecCore::H264`)
- L285 _variable_ `constexpr uint8 Default_4x4_Intra[16] = { 6, 13, 13, 20, 20, 20, 28, 28, 28, 28, 32, 32, 32, 37, 37, 42 };` (scope `UE::AVCodecCore::H264`)
- L292 _variable_ `constexpr uint8 Default_4x4_Inter[16] = { 10, 14, 14, 20, 20, 20, 24, 24, 24, 24, 27, 27, 27, 30, 30, 34 };` (scope `UE::AVCodecCore::H264`)
- L299 _variable_ `constexpr uint8 Default_8x8_Intra[64] = { 6, 10, 10, 13, 11, 13, 16, 16, 16, 16, 18, 18, 18, 18, 18, 23, 23, 23, 23, 23, 23, 25, 25, 25, 25, 25, 25, 25, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 36, 36, 36, 36, 38, 38, 38, 40, 40, 42 };` (scope `UE::AVCodecCore::H264`)
- L310 _variable_ `constexpr uint8 Default_8x8_Inter[64] = { 9, 13, 13, 15, 13, 15, 17, 17, 17, 17, 19, 19, 19, 19, 19, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 30, 30, 30, 30, 32, 32, 32, 33, 33, 35 };` (scope `UE::AVCodecCore::H264`)
- L321 _variable_ `constexpr uint8 ZigZag4x4[16] = { 0, 1, 5, 6, 2, 4, 7, 12, 3, 8, 11, 13, 9, 10, 15, 15 };` (scope `UE::AVCodecCore::H264`)
- L328 _variable_ `constexpr uint8 FieldScan4x4[16] = { 0, 2, 8, 12, 1, 5, 9, 13, 3, 6, 10, 14, 4, 7, 11, 15 };` (scope `UE::AVCodecCore::H264`)
- L335 _variable_ `constexpr uint8 ZigZag8x8[64] = { 0, 1, 5, 6, 14, 15, 27, 28, 2, 4, 7, 13, 16, 26, 29, 42, 3, 8, 12, 17, 25, 30, 41, 43, 9, 11, 18, 24, 31, 40, 44, 53, 10, 19, 23, 32, 39, 45, 52, 54, 20, 22, 33, 38, 46, 51, 55, 60, 21, 34, 37, 47, 50, 56, 59, 61, 35, 36, 48, 49, 57, 58, 62, 63 };` (scope `UE::AVCodecCore::H264`)
- L346 _variable_ `constexpr uint8 FieldScan8x8[64] = { 0, 3, 8, 15, 22, 30, 38, 52, 1, 4, 14, 21, 29, 37, 45, 53, 2, 7, 16, 23, 31, 39, 46, 58, 5, 9, 20, 28, 36, 44, 51, 59, 6, 13, 24, 32, 40, 47, 54, 60, 10, 17, 25, 33, 41, 48, 55, 61, 11, 18, 26, 34, 42, 49, 56, 62, 12, 19, 27, 35, 43, 50, 57, 63 };` (scope `UE::AVCodecCore::H264`)
- L357 _function_ `inline void ScaleListToWeightScale(const bool bIsFrame, const uint8* ScalingList, const uint8 ListSize, uint8* OutWeightList )` (scope `UE::AVCodecCore::H264`)
- L469 _prototype_ `FAVResult ParseSPS(FBitstreamReader& Bitstream, FNaluH264 const& InNaluInfo, TMap<uint32, SPS_t>& OutMapSPS);` (scope `UE::AVCodecCore::H264`)
- L504 _prototype_ `FAVResult ParsePPS(FBitstreamReader& Bitstream, FNaluH264 const& InNaluInfo, TMap<uint32, SPS_t> const& InMapSPS, TMap<uint32, PPS_t>& OutMapPPS);` (scope `UE::AVCodecCore::H264`)
- L559 _prototype_ `FAVResult ParseSliceHeader(FBitstreamReader& Bitstream, FNaluH264 const& InNaluInfo, TMap<uint32, SPS_t> const& InMapSPS, TMap<uint32, PPS_t> const& InMapPPS, Slice_t& OutSlice);` (scope `UE::AVCodecCore::H264`)
- L566 _prototype_ `FAVResult ParseSEI(FBitstreamReader& Bitstream, FNaluH264 const& InNaluInfo, SEI_t& OutSEI);` (scope `UE::AVCodecCore::H264`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/CodecUtils/CodecUtilsH265.h` (Public)


#### enum `EH265Profile`  
`enum class EH265Profile : uint8`  
_L20-60_
- desc: Easy to understand user facing profiles from the T-Rec-H.264-201304 spec there is another enum in CodecUtilsH265 that aligns the profiles with PIC and constraints however users are not expected to understand those ones.
- L22 _public enumerator_ `Auto`
- L23 _public enumerator_ `Main`
- L24 _public enumerator_ `Main10`
- L25 _public enumerator_ `Main10StillPicture`
- L26 _public enumerator_ `MainStillPicture`
- L27 _public enumerator_ `Monochrome`
- L28 _public enumerator_ `Monochrome10`
- L29 _public enumerator_ `Monochrome12`
- L30 _public enumerator_ `Monochrome16`
- L31 _public enumerator_ `Main12`
- L32 _public enumerator_ `Main422_10`
- L33 _public enumerator_ `Main422_12`
- L34 _public enumerator_ `Main444`
- L35 _public enumerator_ `Main444_10`
- L36 _public enumerator_ `Main444_12`
- L37 _public enumerator_ `MainIntra`
- L38 _public enumerator_ `Main10Intra`
- L39 _public enumerator_ `Main12Intra`
- L40 _public enumerator_ `Main422_10Intra`
- L41 _public enumerator_ `Main422_12Intra`
- L42 _public enumerator_ `Main444_Intra`
- L43 _public enumerator_ `Main444_10Intra`
- L44 _public enumerator_ `Main444_12Intra`
- L45 _public enumerator_ `Main444_16Intra`
- L46 _public enumerator_ `Main444StillPicture`
- L47 _public enumerator_ `Main444_16StillPicture`
- L48 _public enumerator_ `HighThroughput444`
- L49 _public enumerator_ `HighThroughput444_10`
- L50 _public enumerator_ `HighThroughput444_14`
- L51 _public enumerator_ `HighThroughput444_16Intra`
- L52 _public enumerator_ `ScreenExtendedMain`
- L53 _public enumerator_ `ScreenExtendedMain10`
- L54 _public enumerator_ `ScreenExtendedMain444`
- L55 _public enumerator_ `ScreenExtendedMain444_10`
- L56 _public enumerator_ `ScreenExtendedHighThroughput444`
- L57 _public enumerator_ `ScreenExtendedHighThroughput444_10`
- L58 _public enumerator_ `ScreenExtendedHighThroughput444_14`
- L59 _public enumerator_ `MAX`

#### enum `UE::AVCodecCore::H265::ENaluType`  
`enum class ENaluType : uint8`  
_L66-117_
- L68 _public enumerator_ `TRAIL_N = 0` — Coded slice segment of a non-TSA, non-STSA trailing picture
- L69 _public enumerator_ `TRAIL_R = 1` — Coded slice segment of a non-TSA, non-STSA trailing picture
- L70 _public enumerator_ `TSA_N = 2` — Coded slice segment of a TSA picture
- L71 _public enumerator_ `TSA_R = 3` — Coded slice segment of a TSA picture
- L72 _public enumerator_ `STSA_N = 4` — Coded slice segment of an STSA picture
- L73 _public enumerator_ `STSA_R = 5` — Coded slice segment of an STSA picture
- L74 _public enumerator_ `RADL_N = 6` — Coded slice segment of a RADL picture
- L75 _public enumerator_ `RADL_R = 7` — Coded slice segment of a RADL picture
- L76 _public enumerator_ `RASL_N = 8` — Coded slice segment of a RASL picture
- L77 _public enumerator_ `RASL_R = 9` — Coded slice segment of a RASL picture
- L78 _public enumerator_ `RSV_VCL_N10 = 10` — Reserved non-IRAP SLNR VCL NAL unit types
- L79 _public enumerator_ `RSV_VCL_R11 = 11` — Reserved non-IRAP sub-layer reference VCL NAL unit types
- L80 _public enumerator_ `RSV_VCL_N12 = 12` — Reserved non-IRAP SLNR VCL NAL unit types
- L81 _public enumerator_ `RSV_VCL_R13 = 13` — Reserved non-IRAP sub-layer reference VCL NAL unit types
- L82 _public enumerator_ `RSV_VCL_N14 = 14` — Reserved non-IRAP SLNR VCL NAL unit types
- L83 _public enumerator_ `RSV_VCL_R15 = 15` — Reserved non-IRAP sub-layer reference VCL NAL unit types
- L84 _public enumerator_ `BLA_W_LP = 16` — Coded slice segment of a BLA picture
- L85 _public enumerator_ `BLA_W_RADL = 17` — Coded slice segment of a BLA picture
- L86 _public enumerator_ `BLA_N_LP = 18` — Coded slice segment of a BLA picture
- L87 _public enumerator_ `IDR_W_RADL = 19` — Coded slice segment of a IDR picture
- L88 _public enumerator_ `IDR_N_LP = 20` — Coded slice segment of a IDR picture
- L89 _public enumerator_ `CRA_NUT = 21` — Coded slice segment of a CRA picture
- L90 _public enumerator_ `RSV_IRAP_VCL22 = 22` — Reserved IRAP VCL NAL unit types
- L91 _public enumerator_ `RSV_IRAP_VCL23 = 23` — Reserved IRAP VCL NAL unit types
- L92 _public enumerator_ `RSV_VCL24 = 24` — Reserved non-IRAP VCL NAL unit types
- L93 _public enumerator_ `RSV_VCL25 = 25` — Reserved non-IRAP VCL NAL unit types
- L94 _public enumerator_ `RSV_VCL26 = 26` — Reserved non-IRAP VCL NAL unit types
- L95 _public enumerator_ `RSV_VCL27 = 27` — Reserved non-IRAP VCL NAL unit types
- L96 _public enumerator_ `RSV_VCL28 = 28` — Reserved non-IRAP VCL NAL unit types
- L97 _public enumerator_ `RSV_VCL29 = 29` — Reserved non-IRAP VCL NAL unit types
- L98 _public enumerator_ `RSV_VCL30 = 30` — Reserved non-IRAP VCL NAL unit types
- L99 _public enumerator_ `RSV_VCL31 = 31` — Reserved non-IRAP VCL NAL unit types
- L100 _public enumerator_ `VPS_NUT = 32` — Video Parameter Set
- L101 _public enumerator_ `SPS_NUT = 33` — Sequence Parameter Set
- L102 _public enumerator_ `PPS_NUT = 34` — Picture Parameter Set
- L103 _public enumerator_ `AUD_NUT = 35` — Access Unit Delimiter
- L104 _public enumerator_ `EOS_NUT = 36` — End of Sequence
- L105 _public enumerator_ `EOB_NUT = 37` — End of Bitstream
- L106 _public enumerator_ `FD_NUT = 38` — Filler data
- L107 _public enumerator_ `PREFIX_SEI_NUT = 39` — Supplemental Enhancement information
- L108 _public enumerator_ `SUFFIX_SEI_NUT = 40` — Supplemental Enhancement information
- L109 _public enumerator_ `RSV_NVCL41 = 41` — Reserved
- L110 _public enumerator_ `RSV_NVCL42 = 42` — Reserved
- L111 _public enumerator_ `RSV_NVCL43 = 43` — Reserved
- L112 _public enumerator_ `RSV_NVCL44 = 44` — Reserved
- L113 _public enumerator_ `RSV_NVCL45 = 45` — Reserved
- L114 _public enumerator_ `RSV_NVCL46 = 46` — Reserved
- L115 _public enumerator_ `RSV_NVCL47 = 47` — Reserved
- L116 _public enumerator_ `UNSPECIFIED = 48` — Unspecified (anything > than this)

#### enum `UE::AVCodecCore::H265::EH265ProfileIDC`  
`enum class EH265ProfileIDC : uint8`  
_L119-166_
- L121 _public enumerator_ `Auto = 0`
- L122 _public enumerator_ `Main = 1`
- L123 _public enumerator_ `Main10 = 2`
- L124 _public enumerator_ `Main10StillPicture = Main10`
- L125 _public enumerator_ `MainStillPicture = 3`
- L126 _public enumerator_ `FormatRangeExtensions = 4`
- L127 _public enumerator_ `Monochrome = FormatRangeExtensions`
- L128 _public enumerator_ `Monochrome10 = FormatRangeExtensions`
- L129 _public enumerator_ `Monochrome12 = FormatRangeExtensions`
- L130 _public enumerator_ `Monochrome16 = FormatRangeExtensions`
- L131 _public enumerator_ `Main12 = FormatRangeExtensions`
- L132 _public enumerator_ `Main422_10 = FormatRangeExtensions`
- L133 _public enumerator_ `Main422_12 = FormatRangeExtensions`
- L134 _public enumerator_ `Main444 = FormatRangeExtensions`
- L135 _public enumerator_ `Main444_10 = FormatRangeExtensions`
- L136 _public enumerator_ `Main444_12 = FormatRangeExtensions`
- L137 _public enumerator_ `MainIntra = FormatRangeExtensions`
- L138 _public enumerator_ `Main10Intra = FormatRangeExtensions`
- L139 _public enumerator_ `Main12Intra = FormatRangeExtensions`
- L140 _public enumerator_ `Main422_10Intra = FormatRangeExtensions`
- L141 _public enumerator_ `Main422_12Intra = FormatRangeExtensions`
- L142 _public enumerator_ `Main444_Intra = FormatRangeExtensions`
- L143 _public enumerator_ `Main444_10Intra = FormatRangeExtensions`
- L144 _public enumerator_ `Main444_12Intra = FormatRangeExtensions`
- L145 _public enumerator_ `Main444_16Intra = FormatRangeExtensions`
- L146 _public enumerator_ `Main444StillPicture = FormatRangeExtensions`
- L147 _public enumerator_ `Main444_16StillPicture = FormatRangeExtensions`
- L148 _public enumerator_ `HighThroughput = 5`
- L149 _public enumerator_ `HighThroughput444 = HighThroughput`
- L150 _public enumerator_ `HighThroughput444_10 = HighThroughput`
- L151 _public enumerator_ `HighThroughput444_14 = HighThroughput`
- L152 _public enumerator_ `HighThroughput444_16Intra = HighThroughput`
- L153 _public enumerator_ `MultiViewMain = 6`
- L154 _public enumerator_ `ScalableMain = 7`
- L155 _public enumerator_ `ThreeDimensionalMain = 8`
- L156 _public enumerator_ `ScreenContentCoding = 9`
- L157 _public enumerator_ `ScreenExtendedMain = ScreenContentCoding`
- L158 _public enumerator_ `ScreenExtendedMain10 = ScreenContentCoding`
- L159 _public enumerator_ `ScreenExtendedMain444 = ScreenContentCoding`
- L160 _public enumerator_ `ScreenExtendedMain444_10 = ScreenContentCoding`
- L161 _public enumerator_ `ScalableRangeExtensions = 10`
- L162 _public enumerator_ `HighThroughputScreenContentCoding = 11`
- L163 _public enumerator_ `ScreenExtendedHighThroughput444 = HighThroughputScreenContentCoding`
- L164 _public enumerator_ `ScreenExtendedHighThroughput444_10 = HighThroughputScreenContentCoding`
- L165 _public enumerator_ `ScreenExtendedHighThroughput444_14 = HighThroughputScreenContentCoding`

#### enum `UE::AVCodecCore::H265::EH265ConstraintFlag`  
`enum class EH265ConstraintFlag : uint16`  
_L174-189_
- L176 _public enumerator_ `None = 0`
- L177 _public enumerator_ `non_packed_constraint_flag = 1u << 0`
- L178 _public enumerator_ `frame_only_constraint_flag = 1u << 1`
- L179 _public enumerator_ `max_12bit_constraint_flag = 1u << 2`
- L180 _public enumerator_ `max_10bit_constraint_flag = 1u << 3`
- L181 _public enumerator_ `max_8bit_constraint_flag = 1u << 4`
- L182 _public enumerator_ `max_422chroma_constraint_flag = 1u << 5`
- L183 _public enumerator_ `max_420chroma_constraint_flag = 1u << 6`
- L184 _public enumerator_ `max_monochrome_constraint_flag = 1u << 7`
- L185 _public enumerator_ `intra_constraint_flag = 1u << 8`
- L186 _public enumerator_ `one_picture_only_constraint_flag = 1u << 9`
- L187 _public enumerator_ `lower_bit_rate_constraint_flag = 1u << 10`
- L188 _public enumerator_ `max_14bit_constraint_flag = 1u << 11`

#### enum `UE::AVCodecCore::H265::EH265LevelIDC`  
`enum class EH265LevelIDC : uint8`  
_L216-231_
- L218 _public enumerator_ `Level_1 = 10`
- L219 _public enumerator_ `Level_2 = 20`
- L220 _public enumerator_ `Level_2_1 = 21`
- L221 _public enumerator_ `Level_3 = 30`
- L222 _public enumerator_ `Level_3_1 = 31`
- L223 _public enumerator_ `Level_4 = 40`
- L224 _public enumerator_ `Level_4_1 = 41`
- L225 _public enumerator_ `Level_5 = 50`
- L226 _public enumerator_ `Level_5_1 = 51`
- L227 _public enumerator_ `Level_5_2 = 52`
- L228 _public enumerator_ `Level_6 = 60`
- L229 _public enumerator_ `Level_6_1 = 61`
- L230 _public enumerator_ `Level_6_2 = 62`

#### enum `UE::AVCodecCore::H265::EH265AspectRatioIDC`  
`enum class EH265AspectRatioIDC : uint8`  
_L233-254_
- L235 _public enumerator_ `Unspecified = 0`
- L236 _public enumerator_ `Square = 1` — 1x1
- L237 _public enumerator_ `_12x11 = 2`
- L238 _public enumerator_ `_10x11 = 3`
- L239 _public enumerator_ `_16x11 = 4`
- L240 _public enumerator_ `_40x33 = 5`
- L241 _public enumerator_ `_24x11 = 6`
- L242 _public enumerator_ `_20x11 = 7`
- L243 _public enumerator_ `_32x11 = 8`
- L244 _public enumerator_ `_80x33 = 9`
- L245 _public enumerator_ `_18x11 = 10`
- L246 _public enumerator_ `_15x11 = 11`
- L247 _public enumerator_ `_64x33 = 12`
- L248 _public enumerator_ `_160x99 = 13`
- L249 _public enumerator_ `_4x3 = 14`
- L250 _public enumerator_ `_3x2 = 15`
- L251 _public enumerator_ `_2x1 = 16`
- L252 _public enumerator_ `Reserved = 17`
- L253 _public enumerator_ `Extended_SAR = 255`

#### enum `UE::AVCodecCore::H265::EH265VideoFormat`  
`enum class EH265VideoFormat : uint8`  
_L256-266_
- L258 _public enumerator_ `Component = 0`
- L259 _public enumerator_ `PAL = 1`
- L260 _public enumerator_ `NTSC = 2`
- L261 _public enumerator_ `SECAM = 3`
- L262 _public enumerator_ `MAC = 4`
- L263 _public enumerator_ `Unspecified = 5`
- L264 _public enumerator_ `Reserved6 = 6`
- L265 _public enumerator_ `Reserved7 = 7`

#### struct `FH265ProfileDefinition`  
`struct FH265ProfileDefinition`  
_L269-275_
- L271 _public member_ `EH265Profile Profile;`
- L272 _public member_ `UE::AVCodecCore::H265::EH265ProfileIDC PIDC;`
- L273 _public member_ `UE::AVCodecCore::H265::EH265ConstraintFlag ConstraintFlags;`
- L274 _public member_ `const TCHAR* Name;`

#### struct `UE::AVCodecCore::H265::FNaluH265`  
`struct FNaluH265`  
_L302-310_
- L304 _public member_ `uint64 Start, Size;`
- L304 _public member_ `uint64 Start, Size;`
- L305 _public member_ `uint8 StartCodeSize;`
- L306 _public member_ `ENaluType Type;`
- L307 _public member_ `uint8 NuhLayerId;`
- L308 _public member_ `uint8 NuhTemporalIdPlus1;`
- L309 _public member_ `const uint8* Data;`

#### struct `UE::AVCodecCore::H265::profile_tier_level_t`  
`struct profile_tier_level_t : public FBitstreamSegment`  
_L314-372_
- inherits: `FBitstreamSegment`
- L316 _public member_ `U<2> general_profile_space;`
- L317 _public member_ `U<1> general_tier_flag;`
- L318 _public member_ `U<5, EH265ProfileIDC> general_profile_idc;`
- L319 _public member_ `TArray<U<1>> general_profile_compatibility_flag;`
- L320 _public member_ `U<1> general_progressive_source_flag;`
- L321 _public member_ `U<1> general_interlaced_source_flag;`
- L322 _public member_ `U<1> general_non_packed_constraint_flag;`
- L323 _public member_ `U<1> general_frame_only_constraint_flag;`
- L326 _public member_ `U<1> general_max_12bit_constraint_flag;`
- L327 _public member_ `U<1> general_max_10bit_constraint_flag;`
- L328 _public member_ `U<1> general_max_8bit_constraint_flag;`
- L329 _public member_ `U<1> general_max_422chroma_constraint_flag;`
- L330 _public member_ `U<1> general_max_420chroma_constraint_flag;`
- L331 _public member_ `U<1> general_max_monochrome_constraint_flag;`
- L332 _public member_ `U<1> general_intra_constraint_flag;`
- L333 _public member_ `U<1> general_one_picture_only_constraint_flag;`
- L334 _public member_ `U<1> general_lower_bit_rate_constraint_flag;`
- L335 _public member_ `U<1> general_max_14bit_constraint_flag;`
- L337 _public member_ `U<1> general_inbld_flag = 0;`
- L338 _public member_ `U<8, EH265LevelIDC> general_level_idc;`
- L369 _public member_ `TArray<sub_layer_t> sub_layers;`
- L371 _public prototype_ `inline void Parse(uint8 const& profilePresentFlag, uint8 maxNumSubLayersMinus1, FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::profile_tier_level_t::sub_layer_t`  
`struct sub_layer_t`  
_L340-367_
- L342 _public member_ `U<1> sub_layer_profile_present_flag;`
- L343 _public member_ `U<1> sub_layer_level_present_flag;`
- L345 _public member_ `U<2> sub_layer_profile_space;`
- L346 _public member_ `U<1> sub_layer_tier_flag = 0;`
- L347 _public member_ `U<5, EH265ProfileIDC> sub_layer_profile_idc;`
- L348 _public member_ `U<1> sub_layer_progressive_source_flag;`
- L349 _public member_ `U<1> sub_layer_interlaced_source_flag;`
- L350 _public member_ `TArray<U<1>> sub_layer_profile_compatibility_flag;`
- L351 _public member_ `U<1> sub_layer_non_packed_constraint_flag;`
- L352 _public member_ `U<1> sub_layer_frame_only_constraint_flag;`
- L354 _public member_ `U<1> sub_layer_max_12bit_constraint_flag;`
- L355 _public member_ `U<1> sub_layer_max_10bit_constraint_flag;`
- L356 _public member_ `U<1> sub_layer_max_8bit_constraint_flag;`
- L357 _public member_ `U<1> sub_layer_max_422chroma_constraint_flag;`
- L358 _public member_ `U<1> sub_layer_max_420chroma_constraint_flag;`
- L359 _public member_ `U<1> sub_layer_max_monochrome_constraint_flag;`
- L360 _public member_ `U<1> sub_layer_intra_constraint_flag;`
- L361 _public member_ `U<1> sub_layer_one_picture_only_constraint_flag;`
- L362 _public member_ `U<1> sub_layer_lower_bit_rate_constraint_flag;`
- L363 _public member_ `U<1> sub_layer_max_14bit_constraint_flag;`
- L365 _public member_ `U<1> sub_layer_inbld_flag;`
- L366 _public member_ `U<8, EH265LevelIDC> sub_layer_level_idc;`

#### struct `UE::AVCodecCore::H265::hrd_parameters_t`  
`struct hrd_parameters_t : public FBitstreamSegment`  
_L374-415_
- inherits: `FBitstreamSegment`
- L376 _public member_ `U<1> nal_hrd_parameters_present_flag;`
- L377 _public member_ `U<1> vcl_hrd_parameters_present_flag;`
- L378 _public member_ `U<1> sub_pic_hrd_params_present_flag;`
- L379 _public member_ `U<8> tick_divisor_minus2;`
- L380 _public member_ `U<5> du_cpb_removal_delay_increment_length_minus1;`
- L381 _public member_ `U<1> sub_pic_cpb_params_in_pic_timing_sei_flag;`
- L382 _public member_ `U<5> dpb_output_delay_du_length_minus1;`
- L383 _public member_ `U<4> bit_rate_scale;`
- L384 _public member_ `U<4> cpb_size_scale;`
- L385 _public member_ `U<4> cpb_size_du_scale;`
- L386 _public member_ `U<5> initial_cpb_removal_delay_length_minus1;`
- L387 _public member_ `U<5> au_cpb_removal_delay_length_minus1;`
- L388 _public member_ `U<5> dpb_output_delay_length_minus1;`
- L412 _public member_ `TArray<sub_layer_t> sub_layers;`
- L414 _public prototype_ `inline void Parse(uint8 const& commonInfPresentFlag, uint8 const& maxNumSubLayersMinus1, FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::hrd_parameters_t::sub_layer_t`  
`struct sub_layer_t`  
_L390-410_
- L392 _public member_ `U<1> fixed_pic_rate_general_flag;`
- L393 _public member_ `U<1> fixed_pic_rate_within_cvs_flag;`
- L394 _public member_ `UE elemental_duration_in_tc_minus1;`
- L395 _public member_ `U<1> low_delay_hrd_flag;`
- L396 _public member_ `UE cpb_cnt_minus1;`
- L407 _public member_ `TArray<sub_layer_hrd_parameters_t> sub_layer_hrd_parameters;`
- L409 _public prototype_ `inline void Parse(uint8 const& in_sub_pic_hrd_params_present_flag, uint8 const& CpbCnt, FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::hrd_parameters_t::sub_layer_t::sub_layer_hrd_parameters_t`  
`struct sub_layer_hrd_parameters_t`  
_L398-405_
- L400 _public member_ `UE bit_rate_value_minus1;`
- L401 _public member_ `UE cpb_size_value_minus1;`
- L402 _public member_ `UE cpb_size_du_value_minus1;`
- L403 _public member_ `UE bit_rate_du_value_minus1;`
- L404 _public member_ `U<1> cbr_flag;`

#### struct `UE::AVCodecCore::H265::VPS_t`  
`struct VPS_t : public FNalu`  
_L417-450_
- inherits: `FNalu`
- L419 _public member_ `U<4> vps_video_parameter_set_id;`
- L420 _public member_ `U<1> vps_base_layer_internal_flag;`
- L421 _public member_ `U<1> vps_base_layer_available_flag;`
- L422 _public member_ `U<6> vps_max_layers_minus1;`
- L423 _public member_ `U<3> vps_max_sub_layers_minus1;`
- L424 _public member_ `U<1> vps_temporal_id_nesting_flag;`
- L426 _public member_ `profile_tier_level_t profile_tier_level;`
- L428 _public member_ `U<1> vps_sub_layer_ordering_info_present_flag;`
- L429 _public member_ `TArray<UE> vps_max_dec_pic_buffering_minus1;`
- L430 _public member_ `TArray<UE> vps_max_num_reorder_pics;`
- L431 _public member_ `TArray<UE> vps_max_latency_increase_plus1;`
- L432 _public member_ `U<6> vps_max_layer_id;`
- L433 _public member_ `UE vps_num_layer_sets_minus1;`
- L434 _public member_ `TArray<TArray<U<1>>> layer_id_included_flag;`
- L435 _public member_ `U<1> vps_timing_info_present_flag;`
- L436 _public member_ `U<32> vps_num_units_in_tick;`
- L437 _public member_ `U<32> vps_time_scale;`
- L438 _public member_ `U<1> vps_poc_proportional_to_timing_flag;`
- L439 _public member_ `UE vps_num_ticks_poc_diff_one_minus1;`
- L440 _public member_ `UE vps_num_hrd_parameters;`
- L441 _public member_ `TArray<UE> hrd_layer_set_idx;`
- L442 _public member_ `TArray<U<1>> cprms_present_flag;`
- L443 _public member_ `TArray<hrd_parameters_t> hrd_parameters;`
- L444 _public member_ `U<1> vps_extension_flag;`
- L448 _public member_ `mutable uint32 prevPicOrderCntLsb = 0;` — Stream State Members TODO (aidan) perhaps this should be moved elsewhere
- L449 _public member_ `mutable uint32 prevPicOrderCntMsb = 0;`

#### struct `UE::AVCodecCore::H265::TScanOrder`  
`template <uint32 Tlog2blkSize, uint32 TscanIdx> struct TScanOrder`  
_L456-556_
- L459 _private member_ `static constexpr uint32 TBlockSize = 1u << Tlog2blkSize;`
- L462 _private function_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> MakeUpperRightDiagonal()` — TODO: This algorithm doesn't make sense, fix
- L487 _private function_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> MakeHorizontal()`
- L501 _private function_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> MakeVertical()`
- L515 _private function_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> MakeTraverse()`
- L542 _public function_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> Values = []()`
- L542 _public member_ `static constexpr TStaticArray<FIntPoint, TBlockSize * TBlockSize> Values = []() { switch (TscanIdx) { default: case 0: return MakeUpperRightDiagonal(); case 1: return MakeHorizontal(); case 2: return MakeVertical(); case 3: return MakeTraverse(); } };`

#### struct `UE::AVCodecCore::H265::scaling_list_data_t`  
`struct scaling_list_data_t : FBitstreamSegment`  
_L558-567_
- inherits: `FBitstreamSegment`
- L560 _public member_ `TStaticArray<TStaticArray<U<1>, 6>, 4> scaling_list_pred_mode_flag;`
- L561 _public member_ `TStaticArray<TStaticArray<UE, 6>, 4> scaling_list_pred_matrix_id_delta;`
- L562 _public member_ `TStaticArray<TStaticArray<SE, 6>, 4> scaling_list_dc_coef_minus8;`
- L563 _public member_ `uint8 ScalingList0[6][16];`
- L564 _public member_ `uint8 ScalingList1to3[3][6][64];`
- L566 _public prototype_ `inline void Parse(FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::FH265ChromaInfo`  
`struct FH265ChromaInfo`  
_L569-572_

#### struct `UE::AVCodecCore::H265::short_term_ref_pic_set_t`  
`struct short_term_ref_pic_set_t : FBitstreamSegment`  
_L615-642_
- inherits: `FBitstreamSegment`
- L617 _public member_ `U<1> inter_ref_pic_set_prediction_flag = 0;`
- L618 _public member_ `UE delta_idx_minus1 = 0;`
- L619 _public member_ `U<1> delta_rps_sign;`
- L620 _public member_ `UE abs_delta_rps_minus1;`
- L621 _public member_ `U<1>* used_by_curr_pic_flags;`
- L622 _public member_ `U<1>* use_delta_flags;`
- L624 _public member_ `UE num_negative_pics = 0;`
- L625 _public member_ `UE num_positive_pics = 0;`
- L626 _public member_ `UE* delta_poc_s0_minus1s;`
- L627 _public member_ `U<1>* used_by_curr_pic_s0_flags;`
- L628 _public member_ `UE* delta_poc_s1_minus1s;`
- L629 _public member_ `U<1>* used_by_curr_pic_s1_flags;`
- L632 _public member_ `uint8 NumPositivePics = 0;` — Derived Values (specification usage order)
- L633 _public member_ `TStaticArray<int32, 16> DeltaPocS1;`
- L634 _public member_ `uint8 NumNegativePics = 0;`
- L635 _public member_ `TStaticArray<int32, 16> DeltaPocS0;`
- L636 _public member_ `uint8 NumDeltaPocs = 0;`
- L637 _public member_ `TStaticArray<uint8, 16> UsedByCurrPicS0;`
- L638 _public member_ `TStaticArray<uint8, 16> UsedByCurrPicS1;`
- L640 _public prototype_ `inline void Parse(uint8 const& stRpsIdx, TArray<short_term_ref_pic_set_t> const& short_term_ref_pic_sets, FBitstreamReader& Bitstream);`
- L641 _public prototype_ `inline void CalculateValues(uint8 const& stRpsIdx, TArray<short_term_ref_pic_set_t>& st_ref_pic_set);`

#### struct `UE::AVCodecCore::H265::SPS_t`  
`struct SPS_t : public FNalu`  
_L644-821_
- inherits: `FNalu`
- L646 _public member_ `U<4> sps_video_parameter_set_id;`
- L647 _public member_ `U<3> sps_max_sub_layers_minus1;`
- L648 _public member_ `U<1> sps_temporal_id_nesting_flag;`
- L649 _public member_ `profile_tier_level_t profile_tier_level;`
- L650 _public member_ `UE sps_seq_parameter_set_id;`
- L651 _public member_ `UE chroma_format_idc;`
- L652 _public member_ `U<1> separate_colour_plane_flag;`
- L653 _public member_ `UE ChromaArrayType;`
- L654 _public member_ `UE pic_width_in_luma_samples;`
- L655 _public member_ `UE pic_height_in_luma_samples;`
- L656 _public member_ `U<1> conformance_window_flag;`
- L664 _public member_ `} conf_win;`
- L666 _public member_ `UE bit_depth_luma_minus8;`
- L667 _public member_ `UE bit_depth_chroma_minus8;`
- L668 _public member_ `UE log2_max_pic_order_cnt_lsb_minus4;`
- L670 _public member_ `U<1> sps_sub_layer_ordering_info_present_flag;`
- L679 _public member_ `TArray<sub_layer_ordering_info_t> sub_layer_ordering_infos;`
- L681 _public member_ `UE log2_min_luma_coding_block_size_minus3;`
- L682 _public member_ `UE log2_diff_max_min_luma_coding_block_size;`
- L683 _public member_ `UE log2_min_luma_transform_block_size_minus2;`
- L684 _public member_ `UE log2_diff_max_min_luma_transform_block_size;`
- L685 _public member_ `UE max_transform_hierarchy_depth_inter;`
- L686 _public member_ `UE max_transform_hierarchy_depth_intra;`
- L688 _public member_ `U<1> scaling_list_enabled_flag;`
- L689 _public member_ `U<1> sps_scaling_list_data_present_flag = 0;`
- L690 _public member_ `scaling_list_data_t scaling_list_data;`
- L692 _public member_ `U<1> amp_enabled_flag;`
- L693 _public member_ `U<1> sample_adaptive_offset_enabled_flag;`
- L695 _public member_ `U<1> pcm_enabled_flag;`
- L696 _public member_ `U<4> pcm_sample_bit_depth_luma_minus1;`
- L697 _public member_ `U<4> pcm_sample_bit_depth_chroma_minus1;`
- L698 _public member_ `UE log2_min_pcm_luma_coding_block_size_minus3;`
- L699 _public member_ `UE log2_diff_max_min_pcm_luma_coding_block_size;`
- L700 _public member_ `U<1> pcm_loop_filter_disabled_flag = 0;`
- L702 _public member_ `UE num_short_term_ref_pic_sets;`
- L703 _public member_ `mutable TArray<short_term_ref_pic_set_t> short_term_ref_pic_sets;`
- L705 _public member_ `U<1> long_term_ref_pics_present_flag;`
- L706 _public member_ `UE num_long_term_ref_pics_sps;`
- L707 _public member_ `TArray<U<>> lt_ref_pic_poc_lsb_sps = {};`
- L708 _public member_ `TArray<U<1>> used_by_curr_pic_lt_sps_flag;`
- L710 _public member_ `U<1> sps_temporal_mvp_enabled_flag;`
- L711 _public member_ `U<1> strong_intra_smoothing_enabled_flag;`
- L713 _public member_ `U<1> vui_parameters_present_flag;`
- L767 _public member_ `} vui_parameters;`
- L769 _public member_ `U<1> sps_extension_present_flag;`
- L771 _public member_ `U<1> sps_range_extension_flag = 0;`
- L772 _public member_ `U<1> sps_multilayer_extension_flag = 0;`
- L773 _public member_ `U<1> sps_3d_extension_flag = 0;`
- L774 _public member_ `U<1> sps_scc_extension_flag = 0;`
- L775 _public member_ `U<4> sps_extension_4bits = 0;`
- L790 _public member_ `} sps_range_extension;`
- L796 _public member_ `} sps_multilayer_extension;`
- L802 _public member_ `} sps_3d_extension;`
- L817 _public member_ `} sps_scc_extension;`
- L820 _public member_ `uint32 MaxDpbSize;` — Members derived from bitstream

#### struct `UE::AVCodecCore::H265::SPS_t::conf_win_t`  
`struct conf_win_t : public FBitstreamSegment`  
_L658-664_
- inherits: `FBitstreamSegment`
- L660 _public member_ `UE left_offset;`
- L661 _public member_ `UE right_offset;`
- L662 _public member_ `UE top_offset;`
- L663 _public member_ `UE bottom_offset;`

#### struct `UE::AVCodecCore::H265::SPS_t::sub_layer_ordering_info_t`  
`struct sub_layer_ordering_info_t : public FBitstreamSegment`  
_L672-677_
- inherits: `FBitstreamSegment`
- L674 _public member_ `UE sps_max_dec_pic_buffering_minus1;`
- L675 _public member_ `UE sps_max_num_reorder_pics;`
- L676 _public member_ `UE sps_max_latency_increase_plus1;`

#### struct `UE::AVCodecCore::H265::SPS_t::vui_parameters_t`  
`struct vui_parameters_t : public FBitstreamSegment`  
_L714-767_
- inherits: `FBitstreamSegment`
- L716 _public member_ `U<1> aspect_ratio_info_present_flag = 0;`
- L717 _public member_ `U<8> aspect_ratio_idc;` — TODO add a enum for this
- L718 _public member_ `U<16> sar_width;`
- L719 _public member_ `U<16> sar_height;`
- L721 _public member_ `U<1> overscan_info_present_flag;`
- L722 _public member_ `U<1> overscan_appropriate_flag;`
- L724 _public member_ `U<1> video_signal_type_present_flag;`
- L725 _public member_ `U<3> video_format;`
- L726 _public member_ `U<1> video_full_range_flag;`
- L727 _public member_ `U<1> colour_description_present_flag;`
- L729 _public member_ `U<8> colour_primaries;`
- L730 _public member_ `U<8> transfer_characteristics;`
- L731 _public member_ `U<8> matrix_coeffs;`
- L733 _public member_ `U<1> chroma_loc_info_present_flag;`
- L734 _public member_ `UE chroma_sample_loc_type_top_field;`
- L735 _public member_ `UE chroma_sample_loc_type_bottom_field;`
- L737 _public member_ `U<1> neutral_chroma_indication_flag;`
- L738 _public member_ `U<1> field_seq_flag;`
- L739 _public member_ `U<1> frame_field_info_present_flag;`
- L740 _public member_ `U<1> default_display_window_flag;`
- L742 _public member_ `UE def_disp_win_left_offset;`
- L743 _public member_ `UE def_disp_win_right_offset;`
- L744 _public member_ `UE def_disp_win_top_offset;`
- L745 _public member_ `UE def_disp_win_bottom_offset;`
- L747 _public member_ `U<1> vui_timing_info_present_flag;`
- L748 _public member_ `U<32> vui_num_units_in_tick;`
- L749 _public member_ `U<32> vui_time_scale;`
- L750 _public member_ `U<1> vui_poc_proportional_to_timing_flag;`
- L751 _public member_ `UE vui_num_ticks_poc_diff_one_minus1;`
- L752 _public member_ `U<1> vui_hrd_parameters_present_flag;`
- L753 _public member_ `hrd_parameters_t hrd_parameters;`
- L755 _public member_ `U<1> bitstream_restriction_flag;`
- L757 _public member_ `U<1> tiles_fixed_structure_flag;`
- L758 _public member_ `U<1> motion_vectors_over_pic_boundaries_flag;`
- L759 _public member_ `U<1> restricted_ref_pic_lists_flag;`
- L760 _public member_ `UE min_spatial_segmentation_idc;`
- L761 _public member_ `UE max_bytes_per_pic_denom;`
- L762 _public member_ `UE max_bits_per_min_cu_denom;`
- L763 _public member_ `UE log2_max_mv_length_horizontal;`
- L764 _public member_ `UE log2_max_mv_length_vertical;`
- L766 _public prototype_ `inline void Parse(FBitstreamReader& Bitstream, uint8 const& sps_max_sub_layers_minus1);`

#### struct `UE::AVCodecCore::H265::SPS_t::sps_range_extension_t`  
`struct sps_range_extension_t : public FBitstreamSegment`  
_L777-790_
- inherits: `FBitstreamSegment`
- L779 _public member_ `U<1> transform_skip_rotation_enabled_flag;`
- L780 _public member_ `U<1> transform_skip_context_enabled_flag;`
- L781 _public member_ `U<1> implicit_rdpcm_enabled_flag;`
- L782 _public member_ `U<1> explicit_rdpcm_enabled_flag;`
- L783 _public member_ `U<1> extended_precision_processing_flag;`
- L784 _public member_ `U<1> intra_smoothing_disabled_flag;`
- L785 _public member_ `U<1> high_precision_offsets_enabled_flag;`
- L786 _public member_ `U<1> persistent_rice_adaptation_enabled_flag;`
- L787 _public member_ `U<1> cabac_bypass_alignment_enabled_flag;`
- L789 _public prototype_ `inline void Parse(FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::SPS_t::sps_multilayer_extension_t`  
`struct sps_multilayer_extension_t : public FBitstreamSegment`  
_L792-796_
- inherits: `FBitstreamSegment`
- L795 _public function_ `inline void Parse(FBitstreamReader& Bitstream)` — TODO (aidan)

#### struct `UE::AVCodecCore::H265::SPS_t::sps_3d_extension_t`  
`struct sps_3d_extension_t : public FBitstreamSegment`  
_L798-802_
- inherits: `FBitstreamSegment`
- L801 _public function_ `inline void Parse(FBitstreamReader& Bitstream)` — TODO (aidan)

#### struct `UE::AVCodecCore::H265::SPS_t::sps_scc_extension_t`  
`struct sps_scc_extension_t : public FBitstreamSegment`  
_L804-817_
- inherits: `FBitstreamSegment`
- L806 _public member_ `U<1> sps_curr_pic_ref_enabled_flag;`
- L807 _public member_ `U<1> palette_mode_enabled_flag;`
- L808 _public member_ `UE palette_max_size;`
- L809 _public member_ `UE delta_palette_max_predictor_size;`
- L810 _public member_ `U<1> sps_palette_predictor_initializers_present_flag;`
- L811 _public member_ `UE sps_num_palette_predictor_initializers_minus1;`
- L812 _public member_ `TArray<TArray<U<>>> sps_palette_predictor_initializers = {};`
- L813 _public member_ `U<2> motion_vector_resolution_control_idc;`
- L814 _public member_ `U<1> intra_boundary_filtering_disabled_flag;`
- L816 _public prototype_ `inline void Parse(uint32 const& in_chroma_format_idc, uint32 const& in_bit_depth_chroma_minus8, FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::PPS_t`  
`struct PPS_t : public FNalu`  
_L826-916_
- inherits: `FNalu`
- L828 _public member_ `UE pps_pic_parameter_set_id;`
- L829 _public member_ `UE pps_seq_parameter_set_id;`
- L830 _public member_ `U<1> dependent_slice_segments_enabled_flag;`
- L831 _public member_ `U<1> output_flag_present_flag;`
- L832 _public member_ `U<3> num_extra_slice_header_bits;`
- L833 _public member_ `U<1> sign_data_hiding_enabled_flag;`
- L834 _public member_ `U<1> cabac_init_present_flag;`
- L835 _public member_ `UE num_ref_idx_l0_default_active_minus1;`
- L836 _public member_ `UE num_ref_idx_l1_default_active_minus1;`
- L837 _public member_ `SE init_qp_minus26;`
- L838 _public member_ `U<1> constrained_intra_pred_flag;`
- L839 _public member_ `U<1> transform_skip_enabled_flag;`
- L840 _public member_ `U<1> cu_qp_delta_enabled_flag;`
- L841 _public member_ `UE diff_cu_qp_delta_depth;`
- L842 _public member_ `SE pps_cb_qp_offset;`
- L843 _public member_ `SE pps_cr_qp_offset;`
- L844 _public member_ `U<1> pps_slice_chroma_qp_offsets_present_flag;`
- L845 _public member_ `U<1> weighted_pred_flag;`
- L846 _public member_ `U<1> weighted_bipred_flag;`
- L847 _public member_ `U<1> transquant_bypass_enabled_flag;`
- L848 _public member_ `U<1> tiles_enabled_flag;`
- L849 _public member_ `U<1> entropy_coding_sync_enabled_flag;`
- L850 _public member_ `UE num_tile_columns_minus1 = 0;`
- L851 _public member_ `UE num_tile_rows_minus1 = 0;`
- L852 _public member_ `U<1> uniform_spacing_flag = 1;` — NVParser seems to default this to 1
- L853 _public member_ `TArray<UE> column_width_minus1;`
- L854 _public member_ `TArray<UE> row_height_minus1;`
- L855 _public member_ `U<1> loop_filter_across_tiles_enabled_flag = 1;`
- L856 _public member_ `U<1> pps_loop_filter_across_slices_enabled_flag;`
- L857 _public member_ `U<1> deblocking_filter_control_present_flag;`
- L858 _public member_ `U<1> deblocking_filter_override_enabled_flag = 0;`
- L859 _public member_ `U<1> pps_deblocking_filter_disabled_flag = 0;`
- L860 _public member_ `SE pps_beta_offset_div2;`
- L861 _public member_ `SE pps_tc_offset_div2;`
- L862 _public member_ `U<1> pps_scaling_list_data_present_flag;`
- L863 _public member_ `scaling_list_data_t scaling_list_data;`
- L864 _public member_ `U<1> lists_modification_present_flag;`
- L865 _public member_ `UE log2_parallel_merge_level_minus2;`
- L866 _public member_ `U<1> slice_segment_header_extension_present_flag;`
- L867 _public member_ `U<1> pps_extension_present_flag;`
- L868 _public member_ `U<1> pps_range_extension_flag = 0;`
- L869 _public member_ `U<1> pps_multilayer_extension_flag = 0;`
- L870 _public member_ `U<1> pps_3d_extension_flag = 0;`
- L871 _public member_ `U<1> pps_scc_extension_flag = 0;`
- L872 _public member_ `U<4> pps_extension_4bits = 0;`
- L887 _public member_ `} pps_range_extension;`
- L892 _public member_ `} pps_multilayer_extension;`
- L897 _public member_ `} pps_3d_extension;`
- L915 _public member_ `} pps_scc_extension;`

#### struct `UE::AVCodecCore::H265::PPS_t::pps_range_extension_t`  
`struct pps_range_extension_t`  
_L874-887_
- L876 _public member_ `UE log2_max_transform_skip_block_size_minus2;`
- L877 _public member_ `U<1> cross_component_prediction_enabled_flag;`
- L878 _public member_ `U<1> chroma_qp_offset_list_enabled_flag;`
- L879 _public member_ `UE diff_cu_chroma_qp_offset_depth;`
- L880 _public member_ `UE chroma_qp_offset_list_len_minus1;`
- L881 _public member_ `TArray<SE> cb_qp_offset_list;`
- L882 _public member_ `TArray<SE> cr_qp_offset_list;`
- L883 _public member_ `UE log2_sao_offset_scale_luma;`
- L884 _public member_ `UE log2_sao_offset_scale_chroma;`
- L886 _public prototype_ `inline void Parse(uint8 const& in_transform_skip_enabled_flag, FBitstreamReader& Bitstream);`

#### struct `UE::AVCodecCore::H265::PPS_t::pps_multilayer_extension_t`  
`struct pps_multilayer_extension_t`  
_L889-892_
- L891 _public function_ `inline void Parse(FBitstreamReader& Bitstream)`

#### struct `UE::AVCodecCore::H265::PPS_t::pps_3d_extension_t`  
`struct pps_3d_extension_t`  
_L894-897_
- L896 _public function_ `inline void Parse(FBitstreamReader& Bitstream)`

#### struct `UE::AVCodecCore::H265::PPS_t::pps_scc_extension_t`  
`struct pps_scc_extension_t`  
_L899-915_
- L901 _public member_ `U<1> pps_curr_pic_ref_enabled_flag;`
- L902 _public member_ `U<1> residual_adaptive_colour_transform_enabled_flag;`
- L903 _public member_ `U<1> pps_slice_act_qp_offsets_present_flag;`
- L904 _public member_ `SE pps_act_y_qp_offset_plus5;`
- L905 _public member_ `SE pps_act_cb_qp_offset_plus5;`
- L906 _public member_ `SE pps_act_cr_qp_offset_plus3;`
- L907 _public member_ `U<1> pps_palette_predictor_initializers_present_flag;`
- L908 _public member_ `UE pps_num_palette_predictor_initializers;`
- L909 _public member_ `U<1> monochrome_palette_flag;`
- L910 _public member_ `UE luma_bit_depth_entry_minus8;`
- L911 _public member_ `UE chroma_bit_depth_entry_minus8;`
- L912 _public member_ `TArray<TArray<U<>>> pps_palette_predictor_initializer = {};`
- L914 _public prototype_ `inline void Parse(FBitstreamReader& Bitstream);`

#### enum `UE::AVCodecCore::H265::EH265SliceType`  
`enum class EH265SliceType : uint8`  
_L920-925_
- L922 _public enumerator_ `B = 0`
- L923 _public enumerator_ `P = 1`
- L924 _public enumerator_ `I = 2`

#### struct `UE::AVCodecCore::H265::Slice_t`  
`struct Slice_t : public FNalu`  
_L927-1025_
- inherits: `FNalu`
- L930 _public member_ `U<1> first_slice_segment_in_pic_flag;` — Members read from bitstream
- L931 _public member_ `U<1> no_output_of_prior_pics_flag;`
- L932 _public member_ `UE slice_pic_parameter_set_id;`
- L934 _public member_ `U<1> dependent_slice_segment_flag = 0;`
- L935 _public member_ `U<> slice_segment_address = 0;`
- L936 _public member_ `UnsignedExpGolomb<EH265SliceType> slice_type;`
- L937 _public member_ `U<1> pic_output_flag = 1;`
- L938 _public member_ `U<2> colour_plane_id;`
- L939 _public member_ `U<> slice_pic_order_cnt_lsb = 0;`
- L940 _public member_ `U<1> short_term_ref_pic_set_sps_flag;`
- L941 _public member_ `short_term_ref_pic_set_t short_term_ref_pic_set;`
- L942 _public member_ `U<> short_term_ref_pic_set_idx = 0;`
- L943 _public member_ `UE num_long_term_sps = 0;`
- L944 _public member_ `UE num_long_term_pics = 0;`
- L945 _public member_ `U<>* lt_idx_sps = nullptr;`
- L946 _public member_ `U<>* poc_lsb_lt = nullptr;`
- L947 _public member_ `U<1>* used_by_curr_pic_lt_flag = nullptr;`
- L948 _public member_ `U<1>* delta_poc_msb_present_flag = nullptr;`
- L949 _public member_ `UE* delta_poc_msb_cycle_lt = nullptr;`
- L950 _public member_ `U<1> slice_temporal_mvp_enabled_flag = 0;`
- L952 _public member_ `U<1> slice_sao_luma_flag = 0;`
- L953 _public member_ `U<1> slice_sao_chroma_flag = 0;`
- L955 _public member_ `U<1> num_ref_idx_active_override_flag;`
- L956 _public member_ `UE num_ref_idx_l0_active_minus1 = 0;`
- L957 _public member_ `UE num_ref_idx_l1_active_minus1 = 0;`
- L966 _public member_ `} ref_pic_list_modification;`
- L967 _public member_ `U<1> mvd_l1_zero_flag = 0;`
- L968 _public member_ `U<1> cabac_init_flag = 0;`
- L969 _public member_ `U<1> collocated_from_l0_flag = 1;`
- L970 _public member_ `UE collocated_ref_idx = 0;`
- L991 _public member_ `} pred_weight_table;`
- L993 _public member_ `UE five_minus_max_num_merge_cand;`
- L994 _public member_ `U<1> use_integer_mv_flag;`
- L996 _public member_ `SE slice_qp_delta;`
- L998 _public member_ `SE slice_cb_qp_offset = 0;`
- L999 _public member_ `SE slice_cr_qp_offset = 0;`
- L1001 _public member_ `SE slice_act_y_qp_offset;`
- L1002 _public member_ `SE slice_act_cb_qp_offset;`
- L1003 _public member_ `SE slice_act_cr_qp_offset;`
- L1005 _public member_ `U<1> cu_chroma_qp_offset_enabled_flag = 0;`
- L1007 _public member_ `U<1> deblocking_filter_override_flag = 0;`
- L1009 _public member_ `U<1> slice_deblocking_filter_disabled_flag;`
- L1010 _public member_ `SE slice_beta_offset_div2;`
- L1011 _public member_ `SE slice_tc_offset_div2;`
- L1013 _public member_ `U<1> slice_loop_filter_across_slices_enabled_flag;`
- L1015 _public member_ `UE num_entry_point_offsets = 0;`
- L1016 _public member_ `UE offset_len_minus1;`
- L1017 _public member_ `U<>* entry_point_offset_minus1;`
- L1019 _public member_ `UE slice_segment_header_extension_length = 0;`
- L1020 _public member_ `U<8>* slice_segment_header_extension_data_byte;`
- L1022 _public member_ `uint32 CurrPicIdx = 0;`
- L1023 _public member_ `uint32 CurrPicOrderCntVal = 0;`
- L1024 _public member_ `uint32 CurrRpsIdx = 0;`

#### struct `UE::AVCodecCore::H265::Slice_t::ref_pic_list_modification_t`  
`struct ref_pic_list_modification_t`  
_L958-966_
- L960 _public member_ `U<1> ref_pic_list_modification_flag_l0 = 0;`
- L961 _public member_ `U<>* list_entry_l0 = nullptr;`
- L962 _public member_ `U<1> ref_pic_list_modification_flag_l1 = 0;`
- L963 _public member_ `U<>* list_entry_l1 = nullptr;`
- L965 _public prototype_ `inline void Parse(uint8 const& in_num_ref_idx_l0_active_minus1, uint8 const& in_num_ref_idx_l1_active_minus1, uint32 const& InNumPicTotalCurr, EH265SliceType const& SliceType, FBitstreamReader& BitStream);`

#### struct `UE::AVCodecCore::H265::Slice_t::pred_weight_table_t`  
`struct pred_weight_table_t`  
_L971-991_
- L973 _public member_ `UE luma_log2_weight_denom;`
- L974 _public member_ `SE delta_chroma_log2_weight_denom = 0;`
- L976 _public member_ `TStaticArray<U<1>, 15> luma_weight_l0_flag;`
- L977 _public member_ `TStaticArray<U<1>, 15> chroma_weight_l0_flag;`
- L978 _public member_ `TStaticArray<SE, 15> delta_luma_weight_l0;`
- L979 _public member_ `TStaticArray<SE, 15> luma_offset_l0;`
- L980 _public member_ `TStaticArray<TStaticArray<SE, 2>, 15> delta_chroma_weight_l0;`
- L981 _public member_ `TStaticArray<TStaticArray<SE, 2>, 15> delta_chroma_offset_l0;`
- L983 _public member_ `TStaticArray<U<1>, 15> luma_weight_l1_flag;`
- L984 _public member_ `TStaticArray<U<1>, 15> chroma_weight_l1_flag;`
- L985 _public member_ `TStaticArray<SE, 15> delta_luma_weight_l1;`
- L986 _public member_ `TStaticArray<SE, 15> luma_offset_l1;`
- L987 _public member_ `TStaticArray<TStaticArray<SE, 2>, 15> delta_chroma_weight_l1;`
- L988 _public member_ `TStaticArray<TStaticArray<SE, 2>, 15> delta_chroma_offset_l1;`
- L990 _public prototype_ `inline void Parse(const uint8& ChromaArrayType, FNaluH265 const& InNaluInfo, Slice_t const& CurrentSlice, FBitstreamReader& BitStream);`

#### struct `UE::AVCodecCore::H265::SEI_t`  
`struct SEI_t : public FNalu`  
_L1030-1032_
- inherits: `FNalu`

#### Free symbols / members of external scopes

- L62 _externvar_ `extern FH265ProfileDefinition GH265ProfileDefinitions[static_cast<uint8>(EH265Profile::MAX)];`
- L64 _namespace_ `namespace UE`
- L64 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L64 _namespace_ `namespace H265` (scope `UE::AVCodecCore`)
- L168 _function_ `inline bool CheckProfileCompatabilityFlag(uint32 const& profile_compatibility_flag, EH265ProfileIDC const& H265ProfileIdc)` (scope `UE::AVCodecCore::H265`)
- L191 _function_ `inline EH265ConstraintFlag operator|(EH265ConstraintFlag const& lhs, EH265ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H265`)
- L196 _function_ `inline EH265ConstraintFlag operator&(EH265ConstraintFlag const& lhs, EH265ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H265`)
- L201 _function_ `inline EH265ConstraintFlag operator|=(EH265ConstraintFlag const& lhs, EH265ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H265`)
- L206 _function_ `inline bool operator==(EH265ConstraintFlag lhs, EH265ConstraintFlag rhs)` (scope `UE::AVCodecCore::H265`)
- L211 _function_ `inline uint8 operator&(uint16 const& lhs, EH265ConstraintFlag const& rhs)` (scope `UE::AVCodecCore::H265`)
- L277 _namespace_ `namespace UE`
- L277 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L277 _namespace_ `namespace H265` (scope `UE::AVCodecCore`)
- L279 _function_ `inline int32 EBSPtoRBSP(uint8* OutBuf, const uint8* InBuf, int32 NumBytesIn)` (scope `UE::AVCodecCore::H265`)
- L312 _prototype_ `FAVResult FindNALUs(FVideoPacket const& InPacket, TArray<FNaluH265>& FoundNalus);` (scope `UE::AVCodecCore::H265`)
- L452 _prototype_ `FAVResult ParseVPS(FBitstreamReader& Bitstream, FNaluH265 const& InNaluInfo, TMap<uint32, VPS_t>& OutMapVPS);` (scope `UE::AVCodecCore::H265`)
- L574 _variable_ `const scaling_list_data_t DefaultScalingList = { {}, {}, {}, {}, { {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16} }, { { {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 16, 17, 16, 17, 18, 17, 18, 18, 17, 18, 21, 19, 20, 21, 20, 19, 21, 24, 22, 22, 24, 24, 22, 22, 24, 25, 25, 27, 30, 27, 25, 25, 29, 31, 35, 35, 31, 29, 36, 41, 44, 41, 36, 47, 54, 54, 47, 65, 70, 65, 88, 88, 115}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 16, 17, 16, 17, 18, 17, 18, 18, 17, 18, 21, 19, 20, 21, 20, 19, 21, 24, 22, 22, 24, 24, 22, 22, 24, 25, 25, 27, 30, 27, 25, 25, 29, 31, 35, 35, 31, 29, 36, 41, 44, 41, 36, 47, 54, 54, 47, 65, 70, 65, 88, 88, 115}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 20, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 28, 28, 28, 28, 28, 28, 33, 33, 33, 33, 33, 41, 41, 41, 41, 54, 54, 54, 71, 71, 91}, {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 20, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 28, 28, 28, 28, 28, 28, 33, 33, 33, 33, 33, 41, 41, 41, 41, 54, 54, 54, 71, 71, 91 ...` (scope `UE::AVCodecCore::H265`)
- L823 _prototype_ `FAVResult ParseSPS(FBitstreamReader& Bitstream, FNaluH265 const& InNaluInfo, TMap<uint32, VPS_t> const& InMapVPS, TMap<uint32, SPS_t>& OutMapSPS);` (scope `UE::AVCodecCore::H265`)
- L918 _prototype_ `FAVResult ParsePPS(FBitstreamReader& Bitstream, FNaluH265 const& InNaluInfo, TMap<uint32, VPS_t> const& InMapVPS, TMap<uint32, SPS_t> const& InMapSPS, TMap<uint32, PPS_t>& OutMapPPS);` (scope `UE::AVCodecCore::H265`)
- L1027 _prototype_ `FAVResult ParseSliceHeader(FBitstreamReader& Bitstream, FNaluH265 const& InNaluInfo, TMap<uint32, VPS_t> const& InMapVPS, TMap<uint32, SPS_t> const& InMapSPS, TMap<uint32, PPS_t> const& InMapPPS, Slice_t& OutSlice);` (scope `UE::AVCodecCore::H265`)
- L1034 _prototype_ `FAVResult ParseSEI(FBitstreamReader& Bitstream, FNaluH265 const& InNaluInfo, SEI_t& OutSEI);` (scope `UE::AVCodecCore::H265`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/CodecUtils/CodecUtilsVP8.h` (Public)


#### enum `UE::AVCodecCore::VP8::EDenoiserState`  
`enum class EDenoiserState : uint32`  
_L11-20_
- L13 _public enumerator_ `DenoiserOff`
- L14 _public enumerator_ `DenoiserOnYOnly`
- L15 _public enumerator_ `DenoiserOnYUV`
- L16 _public enumerator_ `DenoiserOnYUVAggressive`
- L19 _public enumerator_ `DenoiserOnAdaptive` — Adaptive mode defaults to DenoiserOnYUV on key frame, but may switch to DenoiserOnYUVAggressive based on a computed noise metric.

#### enum `UE::AVCodecCore::VP8::EBufferFlags`  
`enum class EBufferFlags : uint8`  
_L22-28_
- L24 _public enumerator_ `None = 0b00`
- L25 _public enumerator_ `Reference = 0b01`
- L26 _public enumerator_ `Update = 0b10`
- L27 _public enumerator_ `ReferenceAndUpdate = Reference | Update`

#### enum `UE::AVCodecCore::VP8::EBufferType`  
`enum class EBufferType : int`  
_L32-38_
- L34 _public enumerator_ `Last = 0b00`
- L35 _public enumerator_ `Golden = 0b01`
- L36 _public enumerator_ `Arf = 0b10`
- L37 _public enumerator_ `Count`

#### struct `UE::AVCodecCore::VP8::FVP8FrameConfig`  
`struct FVP8FrameConfig`  
_L42-105_
- L44 _public function_ `static FVP8FrameConfig GetIntraFrameConfig()`
- L50 _public function_ `FVP8FrameConfig() : LastBufferFlags(EBufferFlags::None) , GoldenBufferFlags(EBufferFlags::None) , ArfBufferFlags(EBufferFlags::None)`
- L57 _public function_ `FVP8FrameConfig(EBufferFlags Last, EBufferFlags Golden, EBufferFlags Arf) : LastBufferFlags(Last) , GoldenBufferFlags(Golden) , ArfBufferFlags(Arf)`
- L64 _public function_ `bool References(EBufferType Buffer) const`
- L80 _public function_ `bool Updates(EBufferType Buffer) const`
- L96 _public function_ `bool IntraFrame() const`
- L102 _public member_ `EBufferFlags LastBufferFlags;`
- L103 _public member_ `EBufferFlags GoldenBufferFlags;`
- L104 _public member_ `EBufferFlags ArfBufferFlags;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L9 _namespace_ `namespace VP8` (scope `UE::AVCodecCore`)
- L30 _prototype_ `ENUM_CLASS_FLAGS(EBufferFlags);` (scope `UE::AVCodecCore::VP8`)
- L40 _prototype_ `ENUM_CLASS_FLAGS(EBufferType);` (scope `UE::AVCodecCore::VP8`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/CodecUtils/CodecUtilsVP9.h` (Public)


#### enum `UE::AVCodecCore::VP9::EProfile`  
`enum class EProfile : uint8`  
_L25-31_
- L27 _public enumerator_ `Profile0`
- L28 _public enumerator_ `Profile1`
- L29 _public enumerator_ `Profile2`
- L30 _public enumerator_ `Profile3`

#### enum `UE::AVCodecCore::VP9::EInterLayerPrediction`  
`enum class EInterLayerPrediction : uint8`  
_L33-38_
- L35 _public enumerator_ `Off`
- L36 _public enumerator_ `On`
- L37 _public enumerator_ `OnKeyPicture`

#### enum `UE::AVCodecCore::VP9::ETemporalStructureMode`  
`enum class ETemporalStructureMode : uint8`  
_L40-45_
- L42 _public enumerator_ `TemporalStructureMode1` — 1 temporal layer structure - i.e., IPPP...
- L43 _public enumerator_ `TemporalStructureMode2` — 2 temporal layers 01...
- L44 _public enumerator_ `TemporalStructureMode3` — 3 temporal layers 0212...

#### struct `UE::AVCodecCore::VP9::FGroupOfFramesInfo`  
`struct FGroupOfFramesInfo`  
_L47-105_
- L49 _public function_ `void SetGofInfo(ETemporalStructureMode tm)`
- L99 _public member_ `size_t NumFramesInGof;`
- L100 _public member_ `uint8 TemporalIdx[MaxFramesInGof];`
- L101 _public member_ `bool TemporalUpSwitch[MaxFramesInGof];`
- L102 _public member_ `uint8 NumRefPics[MaxFramesInGof];`
- L103 _public member_ `uint8 PidDiff[MaxFramesInGof][MaxRefPics];`
- L104 _public member_ `uint16 PidStart;`

#### enum `UE::AVCodecCore::VP9::EBitDepth`  
`enum class EBitDepth : uint8`  
_L107-112_
- L109 _public enumerator_ `k8Bit = 8`
- L110 _public enumerator_ `k10Bit = 10`
- L111 _public enumerator_ `k12Bit = 12`

#### enum `UE::AVCodecCore::VP9::EColorSpace`  
`enum class EColorSpace : uint8`  
_L114-125_
- L116 _public enumerator_ `UNKNOWN = 0` — Unknown (in this case the color space must be signaled
- L118 _public enumerator_ `BT_601 = 1` — outside the VP9 bitstream).
- L119 _public enumerator_ `BT_709 = 2` — Rec. ITU-R BT.709-6
- L120 _public enumerator_ `SMPTE_170 = 3` — SMPTE-170
- L121 _public enumerator_ `SMPTE_240 = 4` — SMPTE-240
- L122 _public enumerator_ `BT_2020 = 5` — Rec. ITU-R BT.2020-2
- L123 _public enumerator_ `RESERVED = 6` — Reserved
- L124 _public enumerator_ `RGB = 7` — sRGB (IEC 61966-2-1)

#### enum `UE::AVCodecCore::VP9::EColorRange`  
`enum class EColorRange : uint8`  
_L127-140_
- L129 _public enumerator_ `Studio` — Studio swing:
- L139 _public enumerator_ `Full` — For BitDepth equals 8: Y is between 16 and 235 inclusive. U and V are between 16 and 240 inclusive. For BitDepth equals 10: Y is between 64 and 940 inclusive. U and V are between 64 and 960 inclusive. For BitDepth equals 12: Y is between 256 and 3760. U and V are between 256 and 3840 inclusive.

#### enum `UE::AVCodecCore::VP9::ESubSampling`  
`enum class ESubSampling : uint8`  
_L142-148_
- L144 _public enumerator_ `k444`
- L145 _public enumerator_ `k440`
- L146 _public enumerator_ `k422`
- L147 _public enumerator_ `k420`

#### enum `UE::AVCodecCore::VP9::EReferenceFrame`  
`enum class EReferenceFrame : int`  
_L150-157_
- L152 _public enumerator_ `None = -1`
- L153 _public enumerator_ `Intra = 0`
- L154 _public enumerator_ `Last = 1`
- L155 _public enumerator_ `Golden = 2`
- L156 _public enumerator_ `Altref = 3`

#### enum `UE::AVCodecCore::VP9::EInterpolationFilter`  
`enum class EInterpolationFilter : uint8`  
_L159-166_
- L161 _public enumerator_ `EightTap = 0`
- L162 _public enumerator_ `EightTapSmooth = 1`
- L163 _public enumerator_ `EightTapSharp = 2`
- L164 _public enumerator_ `Bilinear = 3`
- L165 _public enumerator_ `Switchable = 4`

#### struct `UE::AVCodecCore::VP9::Header_t`  
`struct Header_t : public FNalu`  
_L168-200_
- inherits: `FNalu`
- L170 _public member_ `U<2> frame_marker = 0;`
- L171 _public member_ `U<1> profile_low_bit = 0;`
- L172 _public member_ `U<1> profile_high_bit = 0;`
- L173 _public member_ `U<1> show_existing_frame = 0;`
- L174 _public member_ `U<3> frame_to_show_map_idx = 0;`
- L175 _public member_ `U<1> frame_type = 0;`
- L176 _public member_ `U<1> show_frame = 0;`
- L177 _public member_ `U<1> error_resilient_mode = 0;`
- L179 _public member_ `U<8> frame_sync_byte_0;`
- L180 _public member_ `U<8> frame_sync_byte_1;`
- L181 _public member_ `U<8> frame_sync_byte_2;`
- L183 _public member_ `U<1, EBitDepth> bit_depth;`
- L185 _public member_ `U<1> intra_only = 0;`
- L186 _public member_ `U<2> reset_frame_context = 0;`
- L188 _public member_ `U<1> ten_or_twelve_bit = 0;`
- L189 _public member_ `U<3, EColorSpace> color_space;`
- L190 _public member_ `U<1, EColorRange> color_range = EColorRange::Studio;`
- L191 _public member_ `U<2, ESubSampling> sub_sampling;`
- L193 _public member_ `U<16> frame_width_minus_1;`
- L194 _public member_ `U<16> frame_height_minus_1;`
- L197 _public member_ `EProfile Profile = EProfile::Profile0;` — Pre-calculated helpers
- L198 _public member_ `uint16 FrameWidth = 0;`
- L199 _public member_ `uint16 FrameHeight = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AVCodecCore` (scope `UE`)
- L11 _namespace_ `namespace VP9` (scope `UE::AVCodecCore`)
- L13 _variable_ `constexpr int16 MaxOneBytePictureId = 0x7F;` (scope `UE::AVCodecCore::VP9`) — 7 bits
- L14 _variable_ `constexpr int16 MaxTwoBytePictureId = 0x7FFF;` (scope `UE::AVCodecCore::VP9`) — 15 bits
- L15 _variable_ `constexpr uint8 NoSpatialIdx = 0xFF;` (scope `UE::AVCodecCore::VP9`)
- L16 _variable_ `constexpr uint8 NoGofIdx = 0xFF;` (scope `UE::AVCodecCore::VP9`)
- L17 _variable_ `constexpr uint8 NumBuffers = 8;` (scope `UE::AVCodecCore::VP9`)
- L18 _variable_ `constexpr size_t MaxRefPics = 3;` (scope `UE::AVCodecCore::VP9`)
- L19 _variable_ `constexpr size_t MaxFramesInGof = 0xFF;` (scope `UE::AVCodecCore::VP9`) — 8 bits
- L20 _variable_ `constexpr size_t MaxNumberOfSpatialLayers = 8;` (scope `UE::AVCodecCore::VP9`)
- L22 _variable_ `constexpr size_t MinSpatialLayerLongSideLength = 240;` (scope `UE::AVCodecCore::VP9`)
- L23 _variable_ `constexpr size_t MinSpatialLayerShortSideLength = 135;` (scope `UE::AVCodecCore::VP9`)
- L202 _prototype_ `FAVResult ParseHeader(FBitstreamReader& Bitstream, Header_t& OutHeader);` (scope `UE::AVCodecCore::VP9`)
- L204 _prototype_ `FAVResult ParseFrameSyncCode(FBitstreamReader& Bitstream, Header_t& OutHeader);` (scope `UE::AVCodecCore::VP9`)
- L205 _prototype_ `FAVResult ParseColorConfig(FBitstreamReader& Bitstream, Header_t& OutHeader);` (scope `UE::AVCodecCore::VP9`)
- L206 _prototype_ `FAVResult ParseFrameSize(FBitstreamReader& Bitstream, Header_t& OutHeader);` (scope `UE::AVCodecCore::VP9`)
- L208 _prototype_ `EInterLayerPrediction ScalabilityModeToInterLayerPredMode(EScalabilityMode ScalabilityMode);` (scope `UE::AVCodecCore::VP9`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/Configs/VideoDecoderConfigAV1.h` (Public)


#### struct `FVideoDecoderConfigAV1`  
`struct FVideoDecoderConfigAV1 : public FVideoDecoderConfig`  
_L11-17_
- inherits: `FVideoDecoderConfig`
- desc: Configuration settings for AV1 decoders.
- L13 _public function_ `FVideoDecoderConfigAV1(EAVPreset Preset = EAVPreset::Default) : FVideoDecoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/Configs/VideoDecoderConfigH264.h` (Public)


#### struct `FVideoDecoderConfigH264`  
`struct FVideoDecoderConfigH264 : public FVideoDecoderConfig`  
_L13-27_
- inherits: `FVideoDecoderConfig`
- desc: Configuration settings for H264 decoders.
- L15 _public member_ `TMap<uint32, UE::AVCodecCore::H264::SPS_t> SPS;`
- L16 _public member_ `TMap<uint32, UE::AVCodecCore::H264::PPS_t> PPS;`
- L17 _public member_ `TArray<UE::AVCodecCore::H264::SEI_t> SEI;`
- L19 _public function_ `FVideoDecoderConfigH264(EAVPreset Preset = EAVPreset::Default) : FVideoDecoderConfig(Preset)`
- L24 _public prototype_ `FAVResult Parse(FVideoPacket const& Packet, TArray<UE::AVCodecCore::H264::Slice_t>& OutSlices);`
- L26 _public prototype_ `TOptional<int> GetLastSliceQP(TArray<UE::AVCodecCore::H264::Slice_t>& Slices);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/Configs/VideoDecoderConfigH265.h` (Public)


#### struct `FVideoDecoderConfigH265`  
`struct FVideoDecoderConfigH265 : public FVideoDecoderConfig`  
_L13-28_
- inherits: `FVideoDecoderConfig`
- desc: Configuration settings for H265 decoders.
- L15 _public member_ `TMap<uint32, UE::AVCodecCore::H265::VPS_t> VPS;`
- L16 _public member_ `TMap<uint32, UE::AVCodecCore::H265::SPS_t> SPS;`
- L17 _public member_ `TMap<uint32, UE::AVCodecCore::H265::PPS_t> PPS;`
- L18 _public member_ `TArray<UE::AVCodecCore::H265::SEI_t> SEI;`
- L20 _public function_ `FVideoDecoderConfigH265(EAVPreset Preset = EAVPreset::Default) : FVideoDecoderConfig(Preset)`
- L25 _public prototype_ `FAVResult Parse(FVideoPacket const& Packet, TArray<UE::AVCodecCore::H265::Slice_t>& OutSlices);`
- L27 _public prototype_ `TOptional<int> GetLastSliceQP(TArray<UE::AVCodecCore::H265::Slice_t>& Slices);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/Configs/VideoDecoderConfigVP8.h` (Public)


#### struct `FVideoDecoderConfigVP8`  
`struct FVideoDecoderConfigVP8 : public FVideoDecoderConfig`  
_L10-18_
- inherits: `FVideoDecoderConfig`
- desc: Configuration settings for VP8 decoders.
- L12 _public member_ `int32 NumberOfCores = 0;`
- L14 _public function_ `FVideoDecoderConfigVP8(EAVPreset Preset = EAVPreset::Default) : FVideoDecoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/Configs/VideoDecoderConfigVP9.h` (Public)


#### struct `FVideoDecoderConfigVP9`  
`struct FVideoDecoderConfigVP9 : public FVideoDecoderConfig`  
_L13-27_
- inherits: `FVideoDecoderConfig`
- desc: Configuration settings for VP9 decoders.
- L16 _public member_ `uint32 MaxOutputWidth = 0;` — Values are parsed from the bitstream during decoding
- L17 _public member_ `uint32 MaxOutputHeight = 0;`
- L19 _public member_ `int32 NumberOfCores = 0;`
- L21 _public function_ `FVideoDecoderConfigVP9(EAVPreset Preset = EAVPreset::Default) : FVideoDecoderConfig(Preset)`
- L26 _public prototype_ `FAVResult Parse(FVideoPacket const& Packet, UE::AVCodecCore::VP9::Header_t& OutHeader);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Decoders/StreamVideoDecoder.h` (Public)


#### class `TStreamVideoDecoder`  
`template <typename TResource> class TStreamVideoDecoder : public TVideoDecoder<TResource>`  
_L13-142_
- inherits: `TVideoDecoder<TResource>`
- desc: Configuration-less decoder that detects the bitstream type and creates an appropriate child decoder that can handle it.
- L19 _private member_ `uint8 bIsOpen : 1;` — Whether this encoder is open and is or isn't initialized.
- L25 _public member_ `TSharedPtr<TVideoDecoder<TResource>> Child;` — The child decoder, invalid until this decoder is initialized by sending through a packet.
- L27 _public prototype_ `TStreamVideoDecoder() = default;`
- L29 _public function_ `virtual bool IsOpen() const override`
- L37 _public function_ `bool IsInitialized() const` — @return True if this decoder has been initialized by sending through a packet.
- L42 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice,TSharedRef<FAVInstance> const& NewInstance) override`
- L56 _public function_ `virtual void Close() override`
- L66 _public function_ `virtual FVideoDecoderConfig GetMinimalConfig() override`
- L76 _public function_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) override`
- L84 _public function_ `virtual FAVResult ApplyConfig() override`
- L94 _public function_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override`
- L133 _public function_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) override`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/DependencyDescriptor.h` (Public)


#### enum `EDecodeTargetIndication`  
`enum class EDecodeTargetIndication : uint8`  
_L12-18_
- desc: Relationship of a frame to a Decode target.
- L14 _public enumerator_ `NotPresent = 0` — DecodeTargetInfo symbol '-'
- L15 _public enumerator_ `Discardable = 1` — DecodeTargetInfo symbol 'D'
- L16 _public enumerator_ `Switch = 2` — DecodeTargetInfo symbol 'S'
- L17 _public enumerator_ `Required = 3` — DecodeTargetInfo symbol 'R'

#### class `FFrameDependencyTemplate`  
`class FFrameDependencyTemplate`  
_L20-44_
- L24 _public prototype_ `FFrameDependencyTemplate& SpatialLayerId(int SpatialLayer);` — Setters are named briefly to chain them when building the template.
- L25 _public prototype_ `FFrameDependencyTemplate& TemporalLayerId(int TemporalLayer);`
- L26 _public prototype_ `FFrameDependencyTemplate& Dtis(const FString& DTIS);`
- L27 _public prototype_ `FFrameDependencyTemplate& FrameDiff(std::initializer_list<int32> Diffs);`
- L28 _public prototype_ `FFrameDependencyTemplate& ChainDiff(std::initializer_list<int32> Diffs);`
- L39 _public member_ `int32 SpatialId = 0;`
- L40 _public member_ `int32 TemporalId = 0;`
- L41 _public member_ `TArray<EDecodeTargetIndication> DecodeTargetIndications;`
- L42 _public member_ `TArray<int32> FrameDiffs;`
- L43 _public member_ `TArray<int32> ChainDiffs;`

#### class `FFrameDependencyStructure`  
`class FFrameDependencyStructure`  
_L46-66_
- L58 _public member_ `int StructureId = 0;`
- L59 _public member_ `int NumDecodeTargets = 0;`
- L60 _public member_ `int NumChains = 0;`
- L63 _public member_ `TArray<int32> DecodeTargetProtectedByChain;` — If chains are used (NumChains > 0), maps decode target index into index of the chain protecting that target.
- L64 _public member_ `TArray<FIntPoint> Resolutions;`
- L65 _public member_ `TArray<FFrameDependencyTemplate> Templates;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVCODECSCORE_API`
- L30 _function_ `friend bool operator==(const FFrameDependencyTemplate& Lhs, const FFrameDependencyTemplate& Rhs)`
- L49 _function_ `friend bool operator==(const FFrameDependencyStructure& Lhs, const FFrameDependencyStructure& Rhs)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/Configs/VideoEncoderConfigAV1.h` (Public)


#### struct `FVideoEncoderConfigAV1`  
`struct FVideoEncoderConfigAV1 : public FVideoEncoderConfig`  
_L11-26_
- inherits: `FVideoEncoderConfig`
- desc: Configuration settings for AV1 encoders.
- L14 _public member_ `EAV1Profile Profile = EAV1Profile::Main;`
- L16 _public member_ `bool RepeatSeqHdr = false;`
- L18 _public member_ `uint32 IntraRefreshPeriodFrames = 0;`
- L19 _public member_ `uint32 IntraRefreshCountFrames = 0;`
- L20 _public member_ `uint32 BitDepthMinus8 = 0;`
- L22 _public function_ `FVideoEncoderConfigAV1(EAVPreset Preset = EAVPreset::Default) : FVideoEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/Configs/VideoEncoderConfigH264.h` (Public)


#### struct `FVideoEncoderConfigH264`  
`struct FVideoEncoderConfigH264 : public FVideoEncoderConfig`  
_L11-27_
- inherits: `FVideoEncoderConfig`
- desc: Configuration settings for H264 encoders.
- L14 _public member_ `EH264Profile Profile = EH264Profile::Main;`
- L15 _public member_ `EH264AdaptiveTransformMode AdaptiveTransformMode = EH264AdaptiveTransformMode::Auto;`
- L16 _public member_ `EH264EntropyCodingMode EntropyCodingMode = EH264EntropyCodingMode::Auto;`
- L18 _public member_ `bool RepeatSPSPPS = false;`
- L20 _public member_ `uint32 IntraRefreshPeriodFrames = 0;`
- L21 _public member_ `uint32 IntraRefreshCountFrames = 0;`
- L23 _public function_ `FVideoEncoderConfigH264(EAVPreset Preset = EAVPreset::Default) : FVideoEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/Configs/VideoEncoderConfigH265.h` (Public)


#### struct `FVideoEncoderConfigH265`  
`struct FVideoEncoderConfigH265 : public FVideoEncoderConfig`  
_L11-24_
- inherits: `FVideoEncoderConfig`
- desc: Configuration settings for H265 encoders.
- L13 _public member_ `EH265Profile Profile = EH265Profile::Main;`
- L15 _public member_ `bool RepeatSPSPPS = false;`
- L17 _public member_ `int32 IntraRefreshPeriodFrames = 0;`
- L18 _public member_ `int32 IntraRefreshCountFrames = 0;`
- L20 _public function_ `FVideoEncoderConfigH265(EAVPreset Preset = EAVPreset::Default) : FVideoEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/Configs/VideoEncoderConfigVP8.h` (Public)


#### struct `FVideoEncoderConfigVP8`  
`struct FVideoEncoderConfigVP8 : public FVideoEncoderConfig`  
_L11-20_
- inherits: `FVideoEncoderConfig`
- desc: Configuration settings for VP8 encoders.
- L13 _public member_ `int32 NumberOfCores = 0;`
- L14 _public member_ `bool bDenoisingOn = false;`
- L16 _public function_ `FVideoEncoderConfigVP8(EAVPreset Preset = EAVPreset::Default) : FVideoEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/Configs/VideoEncoderConfigVP9.h` (Public)


#### struct `FVideoEncoderConfigVP9`  
`struct FVideoEncoderConfigVP9 : public FVideoEncoderConfig`  
_L13-26_
- inherits: `FVideoEncoderConfig`
- desc: Configuration settings for VP9 encoders.
- L15 _public member_ `int32 NumberOfCores = 0;`
- L16 _public member_ `bool bDenoisingOn = false;`
- L17 _public member_ `bool bAdaptiveQpMode = false;`
- L18 _public member_ `bool bAutomaticResizeOn = false;`
- L19 _public member_ `bool bFlexibleMode = false;`
- L20 _public member_ `EInterLayerPrediction InterLayerPrediction = EInterLayerPrediction::Off;`
- L22 _public function_ `FVideoEncoderConfigVP9(EAVPreset Preset = EAVPreset::Default) : FVideoEncoderConfig(Preset)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalabilityStructureFactory.h` (Public)


#### Free symbols / members of external scopes

- L13 _prototype_ `TUniquePtr<FScalableVideoController> CreateScalabilityStructure(EScalabilityMode Name);`
- L17 _prototype_ `TOptional<FScalableVideoController::FStreamLayersConfig> ScalabilityStructureConfig(EScalabilityMode Name);` — Returns description of the scalability structure identified by 'name', Return nullopt for unknown name.

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalabilityStructureFull.h` (Public)


#### class `FScalabilityStructureFullSvc`  
`class FScalabilityStructureFullSvc : public FScalableVideoController`  
_L10-67_
- inherits: `FScalableVideoController`
- L13 _public prototype_ `FScalabilityStructureFullSvc(int NumSpatialLayers, int NumTemporalLayers, FIntFraction ResolutionFactor);`
- L14 _public prototype_ `~FScalabilityStructureFullSvc() override = default;`
- L16 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const override;`
- L18 _public prototype_ `virtual TArray<FScalableVideoController::FLayerFrameConfig> NextFrameConfig(bool bRestart) override;`
- L19 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FScalableVideoController::FLayerFrameConfig& Config) override;`
- L20 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) override;`
- L35 _private member_ `static FString FramePatternNames[6];`
- L36 _private member_ `static constexpr int MaxNumSpatialLayers = 3;`
- L37 _private member_ `static constexpr int MaxNumTemporalLayers = 3;`
- L40 _private function_ `int BufferIndex(int Sid, int Tid) const` — Index of the buffer to store last frame for layer (`Sid`, `Tid`)
- L45 _private function_ `bool DecodeTargetIsActive(int Sid, int Tid) const`
- L50 _private function_ `void SetDecodeTargetIsActive(int Sid, int Tid, bool Value)`
- L55 _private prototype_ `EFramePattern NextPattern() const;`
- L56 _private prototype_ `bool TemporalLayerIsActive(int Tid) const;`
- L57 _private prototype_ `static EDecodeTargetIndication Dti(int Sid, int Tid, const FScalableVideoController::FLayerFrameConfig& Frame);`
- L59 _private member_ `const int NumSpatialLayers;`
- L60 _private member_ `const int NumTemporalLayers;`
- L61 _private member_ `const FIntFraction ResolutionFactor;`
- L63 _private member_ `EFramePattern LastPattern = EFramePattern::None;`
- L64 _private member_ `TBitArray<> CanReferenceT0FrameForSpatialId;`
- L65 _private member_ `TBitArray<> CanReferenceT1FrameForSpatialId;`
- L66 _private member_ `TArray<bool> ActiveDecodeTargets;`

#### enum `FScalabilityStructureFullSvc::EFramePattern`  
`enum EFramePattern : uint8`  
_L25-33_
- desc: NOTE: This enum name is duplicated throughout the ScalabilityStructure variants While it's name is the same, the order of the values is imporant and differs between variants
- L27 _public enumerator_ `None`
- L28 _public enumerator_ `Key`
- L29 _public enumerator_ `DeltaT2A`
- L30 _public enumerator_ `DeltaT1`
- L31 _public enumerator_ `DeltaT2B`
- L32 _public enumerator_ `DeltaT0`

#### class `FScalabilityStructureL1T2`  
`class FScalabilityStructureL1T2 : public FScalabilityStructureFullSvc`  
_L73-83_
- inherits: `FScalabilityStructureFullSvc`
- desc: T1       0   0 /   /   / ... T0     0---0---0-- Time-> 0 1 2 3 4
- L76 _public function_ `explicit FScalabilityStructureL1T2(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(1, 2, ResolutionFactor)`
- L80 _public prototype_ `~FScalabilityStructureL1T2() override = default;`
- L82 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL1T3`  
`class FScalabilityStructureL1T3 : public FScalabilityStructureFullSvc`  
_L91-101_
- inherits: `FScalabilityStructureFullSvc`
- desc: T2       0   0   0   0 |  /    |  / T1       / 0     / 0  ... |_/     |_/ T0     0-------0------ Time-> 0 1 2 3 4 5 6 7
- L94 _public function_ `explicit FScalabilityStructureL1T3(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(1, 3, ResolutionFactor)`
- L98 _public prototype_ `~FScalabilityStructureL1T3() override = default;`
- L100 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL2T1`  
`class FScalabilityStructureL2T1 : public FScalabilityStructureFullSvc`  
_L106-116_
- inherits: `FScalabilityStructureFullSvc`
- desc: S1  0--0--0- |  |  | ... S0  0--0--0-
- L109 _public function_ `explicit FScalabilityStructureL2T1(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(2, 1, ResolutionFactor)`
- L113 _public prototype_ `~FScalabilityStructureL2T1() override = default;`
- L115 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL2T2`  
`class FScalabilityStructureL2T2 : public FScalabilityStructureFullSvc`  
_L126-136_
- inherits: `FScalabilityStructureFullSvc`
- desc: S1T1     0   0 /|  /|  / S1T0   0-+-0-+-0 | | | | | ... S0T1   | 0 | 0 | |/  |/  |/ S0T0   0---0---0-- Time-> 0 1 2 3 4
- L129 _public function_ `explicit FScalabilityStructureL2T2(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(2, 2, ResolutionFactor)`
- L133 _public prototype_ `~FScalabilityStructureL2T2() override = default;`
- L135 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL2T3`  
`class FScalabilityStructureL2T3 : public FScalabilityStructureFullSvc`  
_L146-156_
- inherits: `FScalabilityStructureFullSvc`
- desc: S1T2      4    ,8 S1T1    / |  6' | S1T0   2--+-'+--+-... |  |  |  | S0T2   |  3  | ,7 S0T1   | /   5' S0T0   1----'-----... Time-> 0  1  2  3
- L149 _public function_ `explicit FScalabilityStructureL2T3(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(2, 3, ResolutionFactor)`
- L153 _public prototype_ `~FScalabilityStructureL2T3() override = default;`
- L155 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T1`  
`class FScalabilityStructureL3T1 : public FScalabilityStructureFullSvc`  
_L164-174_
- inherits: `FScalabilityStructureFullSvc`
- desc: S2     0-0-0- | | | S1     0-0-0-... | | | S0     0-0-0- Time-> 0 1 2
- L167 _public function_ `explicit FScalabilityStructureL3T1(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(3, 1, ResolutionFactor)`
- L171 _public prototype_ `~FScalabilityStructureL3T1() override = default;`
- L173 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T2`  
`class FScalabilityStructureL3T2 : public FScalabilityStructureFullSvc`  
_L177-187_
- inherits: `FScalabilityStructureFullSvc`
- desc: https://www.w3.org/TR/webrtc-svc/#L3T2*
- L180 _public function_ `explicit FScalabilityStructureL3T2(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(3, 2, ResolutionFactor)`
- L184 _public prototype_ `~FScalabilityStructureL3T2() override = default;`
- L186 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T3`  
`class FScalabilityStructureL3T3 : public FScalabilityStructureFullSvc`  
_L190-200_
- inherits: `FScalabilityStructureFullSvc`
- desc: https://www.w3.org/TR/webrtc-svc/#L3T3*
- L193 _public function_ `explicit FScalabilityStructureL3T3(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureFullSvc(3, 3, ResolutionFactor)`
- L197 _public prototype_ `~FScalabilityStructureL3T3() override = default;`
- L199 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalabilityStructureKey.h` (Public)


#### class `FScalabilityStructureKeySvc`  
`class FScalabilityStructureKeySvc : public FScalableVideoController`  
_L10-71_
- inherits: `FScalableVideoController`
- L13 _public prototype_ `FScalabilityStructureKeySvc(int NumSpatialLayers, int NumTemporalLayers);`
- L14 _public prototype_ `~FScalabilityStructureKeySvc() override = default;`
- L16 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const override;`
- L18 _public prototype_ `virtual TArray<FScalableVideoController::FLayerFrameConfig> NextFrameConfig(bool bRestart) override;`
- L19 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FScalableVideoController::FLayerFrameConfig& Config) override;`
- L20 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) override;`
- L35 _private member_ `static constexpr int MaxNumSpatialLayers = 3;`
- L36 _private member_ `static constexpr int MaxNumTemporalLayers = 3;`
- L39 _private function_ `int BufferIndex(int Sid, int Tid) const` — Index of the buffer to store last frame for layer (`Sid`, `Tid`)
- L44 _private function_ `bool DecodeTargetIsActive(int Sid, int Tid) const`
- L49 _private function_ `void SetDecodeTargetIsActive(int Sid, int Tid, bool value)`
- L54 _private prototype_ `bool TemporalLayerIsActive(int Tid) const;`
- L55 _private prototype_ `static EDecodeTargetIndication Dti(int Sid, int Tid, const FScalableVideoController::FLayerFrameConfig& config);`
- L57 _private prototype_ `TArray<FScalableVideoController::FLayerFrameConfig> KeyframeConfig();`
- L58 _private prototype_ `TArray<FScalableVideoController::FLayerFrameConfig> T0Config();`
- L59 _private prototype_ `TArray<FScalableVideoController::FLayerFrameConfig> T1Config();`
- L60 _private prototype_ `TArray<FScalableVideoController::FLayerFrameConfig> T2Config(EFramePattern Pattern);`
- L62 _private prototype_ `EFramePattern NextPattern(EFramePattern InLastPattern) const;`
- L64 _private member_ `const int NumSpatialLayers;`
- L65 _private member_ `const int NumTemporalLayers;`
- L67 _private member_ `EFramePattern LastPattern = EFramePattern::None;`
- L68 _private member_ `TBitArray<> SpatialIdIsEnabled;`
- L69 _private member_ `TBitArray<> CanReferenceT1FrameForSpatialId;`
- L70 _private member_ `TArray<bool> ActiveDecodeTargets;`

#### enum `FScalabilityStructureKeySvc::EFramePattern`  
`enum EFramePattern : uint8`  
_L25-33_
- desc: NOTE: This enum name is duplicated throughout the ScalabilityStructure variants While it's name is the same, the order of the values is imporant and differs between variants
- L27 _public enumerator_ `None`
- L28 _public enumerator_ `Key`
- L29 _public enumerator_ `DeltaT0`
- L30 _public enumerator_ `DeltaT2A`
- L31 _public enumerator_ `DeltaT1`
- L32 _public enumerator_ `DeltaT2B`

#### class `FScalabilityStructureL2T1Key`  
`class FScalabilityStructureL2T1Key : public FScalabilityStructureKeySvc`  
_L76-86_
- inherits: `FScalabilityStructureKeySvc`
- desc: S1  0--0--0- |       ... S0  0--0--0-
- L79 _public function_ `FScalabilityStructureL2T1Key() : FScalabilityStructureKeySvc(2, 1)`
- L83 _public prototype_ `~FScalabilityStructureL2T1Key() override = default;`
- L85 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL2T2Key`  
`class FScalabilityStructureL2T2Key : public FScalabilityStructureKeySvc`  
_L96-106_
- inherits: `FScalabilityStructureKeySvc`
- desc: S1T1     0   0 /   /   / S1T0   0---0---0 |         ... S0T1   | 0   0 |/   /   / S0T0   0---0---0 Time-> 0 1 2 3 4
- L99 _public function_ `FScalabilityStructureL2T2Key() : FScalabilityStructureKeySvc(2, 2)`
- L103 _public prototype_ `~FScalabilityStructureL2T2Key() override = default;`
- L105 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL2T3Key`  
`class FScalabilityStructureL2T3Key : public FScalabilityStructureKeySvc`  
_L108-118_
- inherits: `FScalabilityStructureKeySvc`
- L111 _public function_ `FScalabilityStructureL2T3Key() : FScalabilityStructureKeySvc(2, 3)`
- L115 _public prototype_ `~FScalabilityStructureL2T3Key() override = default;`
- L117 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T1Key`  
`class FScalabilityStructureL3T1Key : public FScalabilityStructureKeySvc`  
_L120-130_
- inherits: `FScalabilityStructureKeySvc`
- L123 _public function_ `FScalabilityStructureL3T1Key() : FScalabilityStructureKeySvc(3, 1)`
- L127 _public prototype_ `~FScalabilityStructureL3T1Key() override = default;`
- L129 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T2Key`  
`class FScalabilityStructureL3T2Key : public FScalabilityStructureKeySvc`  
_L132-142_
- inherits: `FScalabilityStructureKeySvc`
- L135 _public function_ `FScalabilityStructureL3T2Key() : FScalabilityStructureKeySvc(3, 2)`
- L139 _public prototype_ `~FScalabilityStructureL3T2Key() override = default;`
- L141 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureL3T3Key`  
`class FScalabilityStructureL3T3Key : public FScalabilityStructureKeySvc`  
_L144-154_
- inherits: `FScalabilityStructureKeySvc`
- L147 _public function_ `FScalabilityStructureL3T3Key() : FScalabilityStructureKeySvc(3, 3)`
- L151 _public prototype_ `~FScalabilityStructureL3T3Key() override = default;`
- L153 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalabilityStructureL2T2KeyShift.h` (Public)


#### class `FScalabilityStructureL2T2KeyShift`  
`class FScalabilityStructureL2T2KeyShift : public FScalableVideoController`  
_L18-56_
- inherits: `FScalableVideoController`
- desc: S1T1     0   0 /   /   / S1T0   0---0---0 |        ... S0T1   |   0   0 |  /   / S0T0   0-0---0-- Time-> 0 1 2 3 4
- L21 _public prototype_ `FScalabilityStructureL2T2KeyShift();`
- L22 _public prototype_ `~FScalabilityStructureL2T2KeyShift() override = default;`
- L24 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const override;`
- L25 _public prototype_ `virtual FFrameDependencyStructure DependencyStructure() const override;`
- L27 _public prototype_ `virtual TArray<FScalableVideoController::FLayerFrameConfig> NextFrameConfig(bool bRestart) override;`
- L28 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FScalableVideoController::FLayerFrameConfig& Config) override;`
- L29 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) override;`
- L41 _private member_ `static constexpr int NumSpatialLayers = 2;`
- L42 _private member_ `static constexpr int NumTemporalLayers = 2;`
- L44 _private function_ `bool DecodeTargetIsActive(int Sid, int Tid) const`
- L48 _private function_ `void SetDecodeTargetIsActive(int Sid, int Tid, bool value)`
- L52 _private prototype_ `static EDecodeTargetIndication Dti(int Sid, int Tid, const FScalableVideoController::FLayerFrameConfig& Config);`
- L54 _private member_ `EFramePattern NextPattern = EFramePattern::Key;`
- L55 _private member_ `TArray<bool> ActiveDecodeTargets;`

#### enum `FScalabilityStructureL2T2KeyShift::EFramePattern`  
`enum EFramePattern : uint8`  
_L34-39_
- desc: NOTE: This enum name is duplicated throughout the ScalabilityStructure variants While it's name is the same, the order of the values is imporant and differs between variants
- L36 _public enumerator_ `Key`
- L37 _public enumerator_ `Delta0`
- L38 _public enumerator_ `Delta1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalabilityStructureSimulcast.h` (Public)


#### class `FScalabilityStructureSimulcast`  
`class FScalabilityStructureSimulcast : public FScalableVideoController`  
_L12-65_
- inherits: `FScalableVideoController`
- desc: Scalability structure with multiple independent spatial layers each with the same temporal layering.
- L15 _public prototype_ `FScalabilityStructureSimulcast(int NumSpatialLayers, int NumTemporalLayers, FIntFraction ResolutionFactor);`
- L16 _public prototype_ `virtual ~FScalabilityStructureSimulcast() override = default;`
- L18 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const override;`
- L19 _public prototype_ `virtual TArray<FScalableVideoController::FLayerFrameConfig> NextFrameConfig(bool bRestart) override;`
- L20 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FScalableVideoController::FLayerFrameConfig& Config) override;`
- L21 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) override;`
- L34 _private member_ `static constexpr int MaxNumSpatialLayers = 3;`
- L35 _private member_ `static constexpr int MaxNumTemporalLayers = 3;`
- L38 _private function_ `int BufferIndex(int Sid, int Tid) const` — Index of the buffer to store last frame for layer (`Sid`, `Tid`)
- L43 _private function_ `bool DecodeTargetIsActive(int Sid, int Tid) const`
- L48 _private function_ `void SetDecodeTargetIsActive(int Sid, int Tid, bool Value)`
- L53 _private prototype_ `EFramePattern NextPattern() const;`
- L54 _private prototype_ `bool TemporalLayerIsActive(int Tid) const;`
- L55 _private prototype_ `static EDecodeTargetIndication Dti(int Sid, int Tid, const FScalableVideoController::FLayerFrameConfig& Config);`
- L57 _private member_ `const int NumSpatialLayers;`
- L58 _private member_ `const int NumTemporalLayers;`
- L59 _private member_ `FIntFraction ResolutionFactor;`
- L61 _private member_ `EFramePattern LastPattern = EFramePattern::None;`
- L62 _private member_ `TBitArray<> CanReferenceT0FrameForSpatialId;`
- L63 _private member_ `TBitArray<> CanReferenceT1FrameForSpatialId;`
- L64 _private member_ `TArray<bool> ActiveDecodeTargets;`

#### enum `FScalabilityStructureSimulcast::EFramePattern`  
`enum EFramePattern : uint8`  
_L26-33_
- desc: NOTE: This enum name is duplicated throughout the ScalabilityStructure variants While it's name is the same, the order of the values is imporant and differs between variants
- L28 _public enumerator_ `None`
- L29 _public enumerator_ `DeltaT2A`
- L30 _public enumerator_ `DeltaT1`
- L31 _public enumerator_ `DeltaT2B`
- L32 _public enumerator_ `DeltaT0`

#### class `FScalabilityStructureS2T1`  
`class FScalabilityStructureS2T1 : public FScalabilityStructureSimulcast`  
_L70-80_
- inherits: `FScalabilityStructureSimulcast`
- desc: S1  0--0--0- ... S0  0--0--0-
- L73 _public function_ `FScalabilityStructureS2T1(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(2, 1, ResolutionFactor)`
- L77 _public prototype_ `~FScalabilityStructureS2T1() override = default;`
- L79 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureS2T2`  
`class FScalabilityStructureS2T2 : public FScalabilityStructureSimulcast`  
_L82-90_
- inherits: `FScalabilityStructureSimulcast`
- L85 _public function_ `explicit FScalabilityStructureS2T2(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(2, 2, ResolutionFactor)`
- L87 _public prototype_ `~FScalabilityStructureS2T2() override = default;`
- L89 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureS2T3`  
`class FScalabilityStructureS2T3 : public FScalabilityStructureSimulcast`  
_L104-114_
- inherits: `FScalabilityStructureSimulcast`
- desc: S1T2       3   7 |  / S1T1       / 5 |_/ S1T0     1-------9... S0T2       2   6 |  / S0T1       / 4 |_/ S0T0     0-------8... Time->   0 1 2 3 4
- L107 _public function_ `explicit FScalabilityStructureS2T3(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(2, 3, ResolutionFactor)`
- L111 _public prototype_ `~FScalabilityStructureS2T3() override = default;`
- L113 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureS3T1`  
`class FScalabilityStructureS3T1 : public FScalabilityStructureSimulcast`  
_L116-124_
- inherits: `FScalabilityStructureSimulcast`
- L119 _public function_ `explicit FScalabilityStructureS3T1(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(3, 1, ResolutionFactor)`
- L121 _public prototype_ `~FScalabilityStructureS3T1() override = default;`
- L123 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureS3T2`  
`class FScalabilityStructureS3T2 : public FScalabilityStructureSimulcast`  
_L126-136_
- inherits: `FScalabilityStructureSimulcast`
- L129 _public function_ `explicit FScalabilityStructureS3T2(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(3, 2, ResolutionFactor)`
- L133 _public prototype_ `~FScalabilityStructureS3T2() override = default;`
- L135 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### class `FScalabilityStructureS3T3`  
`class FScalabilityStructureS3T3 : public FScalabilityStructureSimulcast`  
_L138-148_
- inherits: `FScalabilityStructureSimulcast`
- L141 _public function_ `FScalabilityStructureS3T3(FIntFraction ResolutionFactor = { 1, 2 }) : FScalabilityStructureSimulcast(3, 3, ResolutionFactor)`
- L145 _public prototype_ `~FScalabilityStructureS3T3() override = default;`
- L147 _public prototype_ `FFrameDependencyStructure DependencyStructure() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalableVideoController.h` (Public)


#### class `FScalableVideoController`  
`class FScalableVideoController`  
_L13-92_
- desc: Controls how video should be encoded to be scalable. Outputs results as buffer usage configuration for encoder and enough details to communicate the scalability structure via dependency descriptor rtp header extension.
- L71 _public prototype_ `virtual ~FScalableVideoController() = default;`
- L74 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const = 0;` — Returns video structure description for encoder to configure itself.
- L78 _public prototype_ `virtual FFrameDependencyStructure DependencyStructure() const = 0;` — Returns video structure description in format compatible with dependency descriptor rtp header extension.
- L83 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) = 0;` — Notifies Controller with updated bitrates per layer. In particular notifies when certain layers should be disabled. Controller shouldn't produce FLayerFrameConfig for disabled layers.
- L88 _public prototype_ `virtual TArray<FLayerFrameConfig> NextFrameConfig(bool bRestart) = 0;` — When `bRestart` is true, first `FLayerFrameConfig` should have `bIsKeyframe` set to true. Returned vector shouldn't be empty.
- L91 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FLayerFrameConfig& Config) = 0;` — Returns configuration to pass to EncoderCallback.

#### struct `FScalableVideoController::FIntFraction`  
`struct FIntFraction`  
_L16-20_
- L18 _public member_ `int Num = 1;`
- L19 _public member_ `int Den = 2;`

#### struct `FScalableVideoController::FStreamLayersConfig`  
`struct FStreamLayersConfig`  
_L22-31_
- L24 _public member_ `int NumSpatialLayers = 1;`
- L25 _public member_ `int NumTemporalLayers = 1;`
- L27 _public member_ `bool bUsesReferenceScaling = true;` — Indicates if frames can reference frames of a different resolution.
- L30 _public member_ `FIntFraction ScalingFactors[4] = { { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 } };` — Spatial layers scaling. Frames with spatial_id = i expected to be encoded with original_resolution * ScalingFactors[i].Num / ScalingFactors[i].Den

#### class `FScalableVideoController::FLayerFrameConfig`  
`class FLayerFrameConfig`  
_L33-69_
- L37 _public prototype_ `FLayerFrameConfig& Id(int Value);` — Builders/setters.
- L38 _public prototype_ `FLayerFrameConfig& Keyframe();`
- L39 _public prototype_ `FLayerFrameConfig& SpatialLayerId(int Value);`
- L40 _public prototype_ `FLayerFrameConfig& TemporalLayerId(int Value);`
- L41 _public prototype_ `FLayerFrameConfig& Reference(int BufferId);`
- L42 _public prototype_ `FLayerFrameConfig& Update(int BufferId);`
- L43 _public prototype_ `FLayerFrameConfig& ReferenceAndUpdate(int BufferId);`
- L46 _public prototype_ `int GetId() const;` — Getters.
- L47 _public prototype_ `bool GetIsKeyframe() const;`
- L48 _public prototype_ `int GetSpatialId() const;`
- L49 _public prototype_ `int GetTemporalId() const;`
- L50 _public prototype_ `const TArray<FCodecBufferUsage>& GetBuffers() const;`
- L57 _private member_ `int LayerId = 0;` — Id to match configuration returned by NextFrameConfig with (possibly modified) configuration passed back via OnEncoderDone. The meaning of the id is an implementation detail of the FScalableVideoController.
- L62 _private member_ `bool bIsKeyFrame = false;` — Indication frame should be encoded as a key frame. In particular when `is_keyframe=true` property `FCodecBufferUsage::referenced` should be ignored and treated as false.
- L64 _private member_ `int SpatialId = 0;`
- L65 _private member_ `int TemporalId = 0;`
- L68 _private member_ `TArray<FCodecBufferUsage> Buffers;` — Describes how encoder which buffers encoder allowed to reference and which buffers encoder should update.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/ScalableVideoControllerNoLayering.h` (Public)


#### class `FScalableVideoControllerNoLayering`  
`class FScalableVideoControllerNoLayering : public FScalableVideoController`  
_L9-24_
- inherits: `FScalableVideoController`
- L12 _public prototype_ `~FScalableVideoControllerNoLayering() override = default;`
- L14 _public prototype_ `virtual FStreamLayersConfig StreamConfig() const override;`
- L15 _public prototype_ `virtual FFrameDependencyStructure DependencyStructure() const override;`
- L17 _public prototype_ `virtual TArray<FScalableVideoController::FLayerFrameConfig> NextFrameConfig(bool bRestart) override;`
- L18 _public prototype_ `virtual FGenericFrameInfo OnEncodeDone(const FScalableVideoController::FLayerFrameConfig& Config) override;`
- L19 _public prototype_ `virtual void OnRatesUpdated(const FVideoBitrateAllocation& Bitrates) override;`
- L22 _private member_ `bool bStart = true;`
- L23 _private member_ `bool bEnabled = true;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/SVC/VideoBitrateAllocatorSVC.h` (Public)


#### class `FVideoBitrateAllocatorSVC`  
`class FVideoBitrateAllocatorSVC : public FVideoBitrateAllocator`  
_L10-41_
- inherits: `FVideoBitrateAllocator`
- L14 _public prototype_ `explicit FVideoBitrateAllocatorSVC(const FVideoEncoderConfig& Config);` — NOTE: Config stores its rates as kbps whereas this class will use bps. Convert to bps everywhere
- L15 _public prototype_ `virtual ~FVideoBitrateAllocatorSVC() = default;`
- L17 _public prototype_ `FVideoBitrateAllocation Allocate(FVideoBitrateAllocationParameters Parameters) override;`
- L19 _public prototype_ `static uint32 GetMaxBitrate(const FVideoEncoderConfig& Config);`
- L20 _public prototype_ `static uint32 GetPaddingBitrate(const FVideoEncoderConfig& Config);`
- L21 _public prototype_ `static TArray<uint32> GetLayerStartBitrates(const FVideoEncoderConfig& Config);`
- L30 _private prototype_ `static FNumLayers GetNumLayers(const FVideoEncoderConfig& Config);`
- L31 _private prototype_ `FVideoBitrateAllocation GetAllocationNormalVideo(uint32 TotalBitrateBps, size_t FirstActiveLayer, size_t NumSpatialLayers) const;`
- L35 _private prototype_ `size_t FindNumEnabledLayers(uint32 TargetRate) const;` — Returns the number of layers that are active and have enough bitrate to actually be enabled.
- L37 _private member_ `FVideoEncoderConfig Config;`
- L38 _private member_ `const FNumLayers NumLayers;`
- L39 _private member_ `const TArray<uint32> CumulativeLayerStartBitrates;`
- L40 _private member_ `size_t LastActiveLayerCount;`

#### struct `FVideoBitrateAllocatorSVC::FNumLayers`  
`struct FNumLayers`  
_L24-28_
- L26 _public member_ `size_t Spatial = 1;`
- L27 _public member_ `size_t Temporal = 1;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/VideoBitrateAllocation.h` (Public)


#### class `FVideoBitrateAllocation`  
`class FVideoBitrateAllocation`  
_L12-72_
- L15 _public member_ `static constexpr uint32 MaxBitrateBps = TNumericLimits<uint32>::Max();`
- L17 _public prototype_ `FVideoBitrateAllocation();`
- L19 _public prototype_ `virtual ~FVideoBitrateAllocation() = default;`
- L21 _public prototype_ `bool HasBitrate(uint64 SpatialIndex, uint64 TemporalIndex) const;`
- L23 _public prototype_ `uint32 GetBitrate(uint64 SpatialIndex, uint64 TemporalIndex) const;`
- L25 _public prototype_ `bool IsSpatialLayerUsed(uint64 SpatialIndex) const;`
- L27 _public prototype_ `uint32 GetSpatialLayerSumBitrate(uint64 SpatialIndex) const;`
- L29 _public prototype_ `uint32 GetTemporalLayerSumBitrate(uint64 SpatialIndex, uint64 TemporalIndex) const;`
- L31 _public prototype_ `TArray<uint32> GetTemporalLayerAllocation(uint64 SpatialIndex) const;`
- L33 _public prototype_ `uint32 GetSumBps() const;`
- L35 _public prototype_ `bool IsBwLimited() const;`
- L37 _public prototype_ `bool SetBitrate(size_t SpatialIndex, size_t TemporalIndex, uint32 BitrateBps);`
- L41 _public prototype_ `void SetBwLimited(bool Limited);` — Indicates if the allocation has some layers/streams disabled due to low available bandwidth.
- L46 _public prototype_ `TArray<TOptional<FVideoBitrateAllocation>> GetSimulcastAllocations() const;` — Returns one FVideoBitrateAllocation for each spatial layer. This is used to configure simulcast streams. Note that the length of the returned vector is always 5, the optional is unset for unused layers.
- L48 _public function_ `inline bool operator==(const FVideoBitrateAllocation& Other) const`
- L63 _public function_ `inline bool operator!=(const FVideoBitrateAllocation& Other) const`
- L69 _private member_ `uint32 SumBps;`
- L70 _private member_ `TOptional<uint32> Bitrates[Video::MaxSpatialLayers][Video::MaxTemporalStreams];`
- L71 _private member_ `bool bIsBwLimited;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Encoders/VideoBitrateAllocator.h` (Public)


#### class `FVideoBitrateAllocationParameters`  
`class FVideoBitrateAllocationParameters`  
_L10-29_
- L13 _public function_ `FVideoBitrateAllocationParameters(uint32 TotalBitrateBps, FFrameRate Framerate) : TotalBitrateBps(TotalBitrateBps) , StableBitrateBps(TotalBitrateBps) , Framerate(Framerate)`
- L19 _public function_ `FVideoBitrateAllocationParameters(uint32 TotalBitrateBps, uint32 StableBitrateBps, FFrameRate Framerate) : TotalBitrateBps(TotalBitrateBps) , StableBitrateBps(StableBitrateBps) , Framerate(Framerate)`
- L26 _public member_ `uint32 TotalBitrateBps;`
- L27 _public member_ `uint32 StableBitrateBps;`
- L28 _public member_ `FFrameRate Framerate;`

#### class `FVideoBitrateAllocator`  
`class FVideoBitrateAllocator`  
_L31-40_
- L34 _public prototype_ `FVideoBitrateAllocator() = default;`
- L35 _public prototype_ `~FVideoBitrateAllocator() = default;`
- L37 _public prototype_ `virtual FVideoBitrateAllocation GetAllocation(uint32 TotalBitrateBps, FFrameRate Framerate);`
- L39 _public prototype_ `virtual FVideoBitrateAllocation Allocate(FVideoBitrateAllocationParameters Parameters);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/GenericFrameInfo.h` (Public)


#### struct `FCodecBufferUsage`  
`struct FCodecBufferUsage`  
_L10-15_
- L12 _public member_ `int32 Id = 0;`
- L13 _public member_ `bool bReferenced = false;`
- L14 _public member_ `bool bUpdated = false;`

#### class `FGenericFrameInfo`  
`class FGenericFrameInfo : public FFrameDependencyTemplate`  
_L17-34_
- inherits: `FFrameDependencyTemplate`
- L20 _public prototype_ `FGenericFrameInfo();`
- L31 _public member_ `TArray<FCodecBufferUsage> EncoderBuffers;`
- L32 _public member_ `TArray<bool> PartOfChain;`
- L33 _public member_ `TArray<bool> ActiveDecodeTargets;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`
- L22 _function_ `friend bool operator==(const FGenericFrameInfo& Lhs, const FGenericFrameInfo& Rhs)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Resources/D3D/VideoResourceD3D.h` (Public)


#### class `FVideoContextD3D11`  
`class FVideoContextD3D11 : public FAVContext`  
_L38-44_
- inherits: `FAVContext`
- L41 _public member_ `TRefCountPtr<ID3D11Device> Device;`
- L43 _public prototype_ `FVideoContextD3D11(TRefCountPtr<ID3D11Device> const& Device);`

#### class `FVideoContextD3D12`  
`class FVideoContextD3D12 : public FAVContext`  
_L46-52_
- inherits: `FAVContext`
- L49 _public member_ `TRefCountPtr<ID3D12Device> Device;`
- L51 _public prototype_ `FVideoContextD3D12(TRefCountPtr<ID3D12Device> const& Device);`

#### class `FVideoResourceD3D11`  
`class FVideoResourceD3D11 : public TVideoResource<FVideoContextD3D11>`  
_L54-69_
- inherits: `TVideoResource<FVideoContextD3D11>`
- L57 _private member_ `TRefCountPtr<ID3D11Texture2D> Raw;`
- L58 _private member_ `HANDLE SharedHandle = nullptr;`
- L61 _public prototype_ `static FVideoDescriptor GetDescriptorFrom(TSharedRef<FAVDevice> const& Device, TRefCountPtr<ID3D11Texture2D> const& Raw);`
- L63 _public function_ `inline TRefCountPtr<ID3D11Texture2D> const& GetRaw() const`
- L64 _public function_ `inline HANDLE const& GetSharedHandle() const`
- L66 _public prototype_ `FVideoResourceD3D11(TSharedRef<FAVDevice> const& Device, TRefCountPtr<ID3D11Texture2D> const& Raw, FAVLayout const& Layout);`
- L68 _public prototype_ `virtual FAVResult Validate() const override;`

#### class `FVideoResourceD3D12`  
`class FVideoResourceD3D12 : public TVideoResource<FVideoContextD3D12>`  
_L71-108_
- inherits: `TVideoResource<FVideoContextD3D12>`
- L86 _private member_ `FRawD3D12 Raw;`
- L89 _public prototype_ `static FVideoDescriptor GetDescriptorFrom(TSharedRef<FAVDevice> const& Device, FRawD3D12 const& Raw);`
- L91 _public function_ `inline TRefCountPtr<ID3D12Resource> const& GetResource() const`
- L92 _public function_ `inline HANDLE const& GetResourceSharedHandle() const`
- L94 _public function_ `inline TRefCountPtr<ID3D12Heap> const& GetHeap() const`
- L95 _public function_ `inline HANDLE const& GetHeapSharedHandle() const`
- L97 _public function_ `inline TRefCountPtr<ID3D12Fence> const& GetFence() const`
- L98 _public function_ `inline HANDLE const& GetFenceSharedHandle() const`
- L99 _public function_ `inline uint64 const& GetFenceValue() const`
- L101 _public prototype_ `uint64 GetSizeInBytes();`
- L103 _public prototype_ `FVideoResourceD3D12(TSharedRef<FAVDevice> const& Device, FRawD3D12 const& Raw, FAVLayout const& Layout);`
- L104 _public prototype_ `FVideoResourceD3D12(TSharedRef<FAVDevice> const& Device, FRawD3D12 const& Raw, FAVLayout const& Layout, FVideoDescriptor const& Descriptor);`
- L107 _public prototype_ `virtual FAVResult Validate() const override;`

#### struct `FVideoResourceD3D12::FRawD3D12`  
`struct FRawD3D12`  
_L74-83_
- L76 _public member_ `TRefCountPtr<ID3D12Resource> D3DResource;`
- L77 _public member_ `HANDLE D3DResourceShared = nullptr;`
- L78 _public member_ `TRefCountPtr<ID3D12Heap> D3DHeap;`
- L79 _public member_ `HANDLE D3DHeapShared = nullptr;`
- L80 _public member_ `TRefCountPtr<ID3D12Fence> D3DFence;`
- L81 _public member_ `HANDLE D3DFenceShared = nullptr;`
- L82 _public member_ `uint64 FenceValue;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Resources/Metal/VideoResourceMetal.h` (Public)


#### class `FVideoContextMetal`  
`class FVideoContextMetal : public FAVContext`  
_L27-33_
- inherits: `FAVContext`
- L30 _public member_ `MTL::Device* Device;`
- L32 _public prototype_ `FVideoContextMetal(MTL::Device* Device);`

#### class `FVideoResourceMetal`  
`class FVideoResourceMetal : public TVideoResource<FVideoContextMetal>`  
_L36-59_
- inherits: `TVideoResource<FVideoContextMetal>`
- L39 _private member_ `MTL::Texture* Raw;`
- L40 _private member_ `MTL::Buffer* StagingBuffer;`
- L43 _public prototype_ `static FVideoDescriptor GetDescriptorFrom(TSharedRef<FAVDevice> const& Device, MTL::Texture* Raw);`
- L45 _public function_ `inline MTL::Texture* GetRaw() const`
- L47 _public prototype_ `FVideoResourceMetal(TSharedRef<FAVDevice> const& Device, MTL::Texture* Raw, FAVLayout const& Layout);`
- L50 _public prototype_ `FAVResult CopyFrom(CVPixelBufferRef Other);`
- L52 _public prototype_ `virtual FAVResult Validate() const override;`
- L55 _public prototype_ `FVideoResourceMetal(FVideoResourceMetal const&) = delete;` — Non-copyable and non-movable to prevent double-release of Metal resources.
- L56 _public prototype_ `FVideoResourceMetal(FVideoResourceMetal&&) = delete;`
- L57 _public prototype_ `FVideoResourceMetal& operator=(FVideoResourceMetal const&) = delete;`
- L58 _public prototype_ `FVideoResourceMetal& operator=(FVideoResourceMetal&&) = delete;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Resources/VideoResourceCPU.h` (Public)


#### class `FVideoContextCPU`  
`class FVideoContextCPU : public FAVContext`  
_L14-18_
- inherits: `FAVContext`
- L17 _public prototype_ `FVideoContextCPU();`

#### class `FVideoResourceCPU`  
`class FVideoResourceCPU : public TVideoResource<FVideoContextCPU>`  
_L20-33_
- inherits: `TVideoResource<FVideoContextCPU>`
- L23 _private member_ `TSharedPtr<uint8> Raw;`
- L26 _public function_ `inline TSharedPtr<uint8> const& GetRaw() const`
- L27 _public function_ `inline void SetRaw(TSharedPtr<uint8> RawData)`
- L29 _public prototype_ `FVideoResourceCPU(TSharedRef<FAVDevice> const& Device, TSharedPtr<uint8> const& Raw, FAVLayout const& Layout, FVideoDescriptor const& Descriptor);`
- L30 _public prototype_ `virtual ~FVideoResourceCPU() override = default;`
- L32 _public prototype_ `virtual FAVResult Validate() const override;`

#### class `FResolvableVideoResourceCPU`  
`class FResolvableVideoResourceCPU : public TResolvableVideoResource<FVideoResourceCPU>`  
_L35-43_
- inherits: `TResolvableVideoResource<FVideoResourceCPU>`
- L38 _protected prototype_ `virtual TSharedPtr<FVideoResourceCPU> TryResolve(TSharedPtr<FAVDevice> const& Device, FVideoDescriptor const& Descriptor) override;`
- L41 _private prototype_ `uint32 GetStrideInterleavedOrLuma(FVideoDescriptor const& Descriptor);`
- L42 _private prototype_ `uint32 GetSize(FVideoDescriptor const& Descriptor);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVCODECSCORE_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/Resources/Vulkan/VideoResourceVulkan.h` (Public)


#### class `FVideoContextVulkan`  
`class FVideoContextVulkan : public FAVContext`  
_L26-35_
- inherits: `FAVContext`
- L29 _public member_ `VkInstance Instance;`
- L30 _public member_ `VkDevice Device;`
- L31 _public member_ `VkPhysicalDevice PhysicalDevice;`
- L32 _public member_ `TFunction<PFN_vkVoidFunction(const char*)> vkGetDeviceProcAddr;`
- L34 _public prototype_ `FVideoContextVulkan(VkInstance const& Instance, VkDevice const& Device, VkPhysicalDevice const& PhysicalDevice, TFunction<PFN_vkVoidFunction(const char*)> const& GetDeviceProcAddrFunc);`

#### class `FVideoResourceVulkan`  
`class FVideoResourceVulkan : public TVideoResource<FVideoContextVulkan>`  
_L43-60_
- inherits: `TVideoResource<FVideoContextVulkan>`
- L46 _private member_ `VkDeviceMemory DeviceMemory;`
- L47 _private member_ `FVulkanSharedHandle DeviceMemorySharedHandle = FVulkanSharedHandle();`
- L48 _private member_ `VkFence Fence;`
- L49 _private member_ `FVulkanSharedHandle FenceSharedHandle = FVulkanSharedHandle();`
- L52 _public function_ `inline VkDeviceMemory GetRaw() const`
- L53 _public function_ `inline FVulkanSharedHandle const& GetSharedHandle() const`
- L54 _public function_ `inline FVulkanSharedHandle const& GetFenceSharedHandle() const`
- L56 _public prototype_ `FVideoResourceVulkan(TSharedRef<FAVDevice> const& Device, VkDeviceMemory Raw, FAVLayout const& Layout, FVideoDescriptor const& Descriptor);`
- L57 _public prototype_ `virtual ~FVideoResourceVulkan() override = default;`
- L59 _public prototype_ `virtual FAVResult Validate() const override;`

#### Free symbols / members of external scopes

- L38 _typedef_ `typedef HANDLE FVulkanSharedHandle;`
- L40 _typedef_ `typedef int FVulkanSharedHandle;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoCodecSpecificInfo.h` (Public)


#### struct `FCodecSpecificInfoVP8`  
`struct FCodecSpecificInfoVP8`  
_L11-32_
- L13 _public member_ `bool bNonReference;`
- L14 _public member_ `uint8 TemporalIdx;`
- L15 _public member_ `bool bLayerSync;`
- L16 _public member_ `int8 KeyIdx;` — Negative value to skip keyIdx.
- L26 _public member_ `bool bUseExplicitDependencies;` — Used to generate the list of dependency frames. `referencedBuffers` and `updatedBuffers` contain buffer IDs. Note that the buffer IDs here have a one-to-one mapping with the actual codec buffers, but the exact mapping (i.e. whether 0 refers to Last, to Golden or to Arf) is not pre-determined. More references may be specified than are strictly necessary, but not less. TODO(bugs.webrtc.org/10242): Remove `useExplicitDependencies` once all encoder-wrappers are updated.
- L27 _public member_ `static constexpr size_t BuffersCount = 3;`
- L28 _public member_ `size_t ReferencedBuffers[BuffersCount];`
- L29 _public member_ `size_t ReferencedBuffersCount;`
- L30 _public member_ `size_t UpdatedBuffers[BuffersCount];`
- L31 _public member_ `size_t UpdatedBuffersCount;`

#### struct `FCodecSpecificInfoVP9`  
`struct FCodecSpecificInfoVP9`  
_L34-61_
- L37 _public member_ `bool bFirstFrameInPicture;` — First frame, increment picture_id.
- L38 _public member_ `bool bInterPicPredicted;` — This layer frame is dependent on previously
- L40 _public member_ `bool bFlexibleMode;` — coded frame(s).
- L41 _public member_ `bool bSSDataAvailable;`
- L42 _public member_ `bool bNonRefForInterLayerPred;`
- L44 _public member_ `uint8 TemporalIdx;`
- L45 _public member_ `bool bTemporalUpSwitch;`
- L46 _public member_ `bool bInterLayerPredicted;` — Frame is dependent on directly lower spatial
- L48 _public member_ `uint8 GofIdx;` — layer frame.
- L51 _public member_ `size_t NumSpatialLayers;` — SS data.
- L52 _public member_ `size_t FirstActiveLayer;`
- L53 _public member_ `bool bSpatialLayerResolutionPresent;`
- L54 _public member_ `uint16 Width[UE::AVCodecCore::VP9::MaxNumberOfSpatialLayers];`
- L55 _public member_ `uint16 Height[UE::AVCodecCore::VP9::MaxNumberOfSpatialLayers];`
- L56 _public member_ `UE::AVCodecCore::VP9::FGroupOfFramesInfo Gof;`
- L59 _public member_ `uint8 NumRefPics;` — Frame reference data.
- L60 _public member_ `uint8 PDiff[UE::AVCodecCore::VP9::MaxRefPics];`

#### struct `FCodecSpecificInfoH264`  
`struct FCodecSpecificInfoH264`  
_L63-69_
- L65 _public member_ `EH264PacketizationMode PacketizationMode;`
- L66 _public member_ `uint8 TemporalIdx;`
- L67 _public member_ `bool bBaseLayerSync;`
- L68 _public member_ `bool bIdrFrame;`

#### union `FCodecSpecificInfoUnion`  
`union FCodecSpecificInfoUnion`  
_L71-76_
- L73 _public member_ `FCodecSpecificInfoVP8 VP8;`
- L74 _public member_ `FCodecSpecificInfoVP9 VP9;`
- L75 _public member_ `FCodecSpecificInfoH264 H264;`

#### struct `FCodecSpecificInfo`  
`struct FCodecSpecificInfo`  
_L78-93_
- L80 _public function_ `FCodecSpecificInfo() : Codec(EVideoCodec::Undefined)`
- L85 _public prototype_ `FCodecSpecificInfo(const FCodecSpecificInfo&) = default;`
- L86 _public prototype_ `~FCodecSpecificInfo() = default;`
- L88 _public member_ `EVideoCodec Codec;`
- L89 _public member_ `FCodecSpecificInfoUnion CodecSpecific;`
- L90 _public member_ `bool bEndOfPicture = true;`
- L91 _public member_ `TOptional<FGenericFrameInfo> GenericFrameInfo;`
- L92 _public member_ `TOptional<FFrameDependencyStructure> TemplateStructure;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoConfig.h` (Public)


#### enum `EVideoCodec`  
`enum class EVideoCodec : uint8`  
_L10-19_
- reflection: `UENUM()`
- L12 _public enumerator_ `Undefined`
- L13 _public enumerator_ `H264`
- L14 _public enumerator_ `H265`
- L15 _public enumerator_ `VP8`
- L16 _public enumerator_ `VP9`
- L17 _public enumerator_ `AV1`
- L18 _public enumerator_ `MAX`

#### struct `FVideoConfig`  
`struct FVideoConfig : public FAVConfig`  
_L21-30_
- inherits: `FAVConfig`
- L23 _public function_ `FVideoConfig(EAVPreset Preset = EAVPreset::Default) : FAVConfig(Preset) , Codec(EVideoCodec::Undefined)`
- L29 _public member_ `EVideoCodec Codec;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoDecoder.h` (Public)


#### struct `FVideoDecoderConfig`  
`struct FVideoDecoderConfig : public FVideoConfig`  
_L14-19_
- inherits: `FVideoConfig`
- L17 _public function_ `FVideoDecoderConfig(EAVPreset Preset = EAVPreset::Default) : FVideoConfig(Preset)`

#### class `TVideoDecoder`  
`template <typename TResource = void, typename TConfig = void> class TVideoDecoder : public TAVCoder<TVideoDecoder, TResource, TConfig>`  
_L27-110_
- inherits: `TAVCoder<TVideoDecoder,TResource,TConfig>`
- desc: Video decoder with a factory, that supports typesafe resource handling and configuration. @see TAVCodec
- L93 _public function_ `virtual FVideoDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableVideoResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FVideoDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TVideoDecoder::TWrapper`  
`template <typename TChildResource, typename TChildConfig> class TWrapper : public TAVCoder<TVideoDecoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>`  
_L37-86_
- inherits: `TAVCoder<TVideoDecoder,TResource,TConfig>::templateTWrapper<TChildResource,TChildConfig>`
- desc: Wrapper decoder that transforms resource/config types for use with a differently typed child decoder. @tparam TChildResource Type of child resource. @tparam TChildConfig Type of child config.
- L40 _public function_ `TWrapper(TSharedRef<TVideoDecoder<TChildResource, TChildConfig>> const& Child) : TAVCoder<TVideoDecoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>(Child)`
- L45 _public function_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override`
- L61 _public function_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) override`

#### class `TVideoDecoder`  
`template <typename TResource> class TVideoDecoder<TResource> : public TAVCoder<TVideoDecoder, TResource>`  
_L118-128_
- inherits: `TAVCoder<TVideoDecoder,TResource>`
- desc: Video decoder with a factory, that supports typesafe resource handling. @see TAVCodec
- L93 _public function_ `virtual FVideoDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableVideoResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FVideoDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TVideoDecoder`  
`template <> class TVideoDecoder<> : public TAVCoder<TVideoDecoder>`  
_L136-170_
- inherits: `TAVCoder<TVideoDecoder>`
- desc: Video decoder with a factory. @see TAVCodec
- L93 _public function_ `virtual FVideoDecoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L106 _public function_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L127 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) = 0;` — Read a finished frame out of the codec. @param InOutResource Deferred resource that can be resolved by the decoder in a desired format/size/etc. Passed by reference inout. @see TResolvableVideoResource @return Result of the operation, @see FAVResult.
- L145 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) = 0;` — Send a packet to the underlying codec architecture. @param Packet Packet holding the frame data. An empty packet will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L152 _public function_ `FAVResult FlushFrames()` — Flush remaining frames and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L162 _public prototype_ `virtual FVideoDecoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L169 _public prototype_ `virtual void SetMinimalConfig(FVideoDecoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### Free symbols / members of external scopes

- L68 _function_ `TDelegatedVideoResource<TChildResource> WrappedResource([&InOutResource](TSharedPtr<TChildResource>& InOutResult, TSharedPtr<FAVDevice> const& InDevice, FVideoDescriptor const& Descriptor) { InOutResult = nullptr; if (InOutResource.Resolve(InDevice, Descriptor)) { InOutResult = InOutResource->template PinMapping<TChildResource>(); if (!InOutResult.IsValid() || InOutResult->Validate().IsNotSuccess()) { if (FAVExtension::TransformResource<TChildResource, TResource>(InOutResult, InOutResource).IsNotSuccess()) { InOutResult.Reset(); } } } });` (scope `TVideoDecoder::TWrapper::ReceiveFrame`)
- L172 _typedef_ `typedef TVideoDecoder<> FVideoDecoder;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoEncoder.h` (Public)


#### enum `EScalabilityMode`  
`enum class EScalabilityMode : uint8`  
_L17-54_
- reflection: `UENUM()`
- desc: Implementation of Video Encoding domain, see TAVCoder for inheritance model
- L19 _public enumerator_ `L1T1 = 0`
- L20 _public enumerator_ `L1T2`
- L21 _public enumerator_ `L1T3`
- L22 _public enumerator_ `L2T1`
- L23 _public enumerator_ `L2T1h`
- L24 _public enumerator_ `L2T1_KEY`
- L25 _public enumerator_ `L2T2`
- L26 _public enumerator_ `L2T2h`
- L27 _public enumerator_ `L2T2_KEY`
- L28 _public enumerator_ `L2T2_KEY_SHIFT`
- L29 _public enumerator_ `L2T3`
- L30 _public enumerator_ `L2T3h`
- L31 _public enumerator_ `L2T3_KEY`
- L32 _public enumerator_ `L3T1`
- L33 _public enumerator_ `L3T1h`
- L34 _public enumerator_ `L3T1_KEY`
- L35 _public enumerator_ `L3T2`
- L36 _public enumerator_ `L3T2h`
- L37 _public enumerator_ `L3T2_KEY`
- L38 _public enumerator_ `L3T3`
- L39 _public enumerator_ `L3T3h`
- L40 _public enumerator_ `L3T3_KEY`
- L41 _public enumerator_ `S2T1`
- L42 _public enumerator_ `S2T1h`
- L43 _public enumerator_ `S2T2`
- L44 _public enumerator_ `S2T2h`
- L45 _public enumerator_ `S2T3`
- L46 _public enumerator_ `S2T3h`
- L47 _public enumerator_ `S3T1`
- L48 _public enumerator_ `S3T1h`
- L49 _public enumerator_ `S3T2`
- L50 _public enumerator_ `S3T2h`
- L51 _public enumerator_ `S3T3`
- L52 _public enumerator_ `S3T3h`
- L53 _public enumerator_ `None`

#### enum `ERateControlMode`  
`enum class ERateControlMode : uint8`  
_L69-75_
- reflection: `UENUM()`
- L71 _public enumerator_ `Unknown`
- L72 _public enumerator_ `ConstQP`
- L73 _public enumerator_ `VBR`
- L74 _public enumerator_ `CBR`

#### enum `EMultipassMode`  
`enum class EMultipassMode : uint8`  
_L78-84_
- reflection: `UENUM()`
- L80 _public enumerator_ `Unknown`
- L81 _public enumerator_ `Disabled`
- L82 _public enumerator_ `Quarter`
- L83 _public enumerator_ `Full`

#### struct `FSpatialLayer`  
`struct FSpatialLayer`  
_L87-111_
- desc: TODO (william.belcher): Use reasonable defaults set elsewhere
- L89 _public member_ `uint32 Width = 1920;`
- L90 _public member_ `uint32 Height = 1080;`
- L91 _public member_ `uint32 Framerate = 60;`
- L92 _public member_ `uint8 NumberOfTemporalLayers = 1;`
- L93 _public member_ `int32 MaxBitrate = 20000000;`
- L94 _public member_ `int32 TargetBitrate = 10000000;`
- L95 _public member_ `int32 MinBitrate = 5000000;`
- L96 _public member_ `int32 MaxQP = 0;`
- L97 _public member_ `bool bActive = false;`

#### struct `FVideoEncoderConfig`  
`struct FVideoEncoderConfig : public FVideoConfig`  
_L114-206_
- inherits: `FVideoConfig`
- desc: TODO (william.belcher): Use reasonable defaults set elsewhere
- L117 _public member_ `uint32 Width = 1920;`
- L118 _public member_ `uint32 Height = 1080;`
- L120 _public member_ `uint32 TargetFramerate = 60;`
- L123 _public member_ `int32 TargetBitrate = -1;` — Individual coder implementations check for -1 bitrate and assign value
- L124 _public member_ `int32 MaxBitrate = -1;`
- L125 _public member_ `int32 MinBitrate = -1;`
- L127 _public member_ `TOptional<int32> Bitrates[Video::MaxSpatialLayers][Video::MaxTemporalStreams];` — Advanced bitrate settings. Used for situations such as simulcast / SVC
- L129 _public member_ `int32 MinQuality = -1;`
- L130 _public member_ `int32 MaxQuality = -1;`
- L132 _public member_ `ERateControlMode RateControlMode = ERateControlMode::CBR;`
- L133 _public member_ `uint8 bFillData : 1;`
- L135 _public member_ `EScalabilityMode ScalabilityMode = EScalabilityMode::None;`
- L137 _public member_ `uint8 NumberOfSpatialLayers = 1;`
- L138 _public member_ `uint8 NumberOfTemporalLayers = 1;`
- L139 _public member_ `FSpatialLayer SpatialLayers[Video::MaxSpatialLayers];`
- L141 _public member_ `uint8 NumberOfSimulcastStreams;`
- L142 _public member_ `FSpatialLayer SimulcastStreams[Video::MaxSimulcastStreams];`
- L145 _public member_ `uint32 KeyframeInterval = 0;` — TODO (Remove and derive from latency mode)
- L146 _public member_ `EMultipassMode MultipassMode = EMultipassMode::Full;`
- L148 _public function_ `FVideoEncoderConfig(EAVPreset Preset = EAVPreset::Default) : FVideoConfig(Preset) , bFillData(false)`

#### class `TVideoEncoder`  
`template <typename TResource = void, typename TConfig = void> class TVideoEncoder : public TAVCoder<TVideoEncoder, TResource, TConfig>`  
_L214-300_
- inherits: `TAVCoder<TVideoEncoder,TResource,TConfig>`
- desc: Video encoder with a factory, that supports typesafe resource handling and configuration. @see TAVCodec
- L283 _public function_ `virtual FVideoEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L296 _public function_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L319 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @param bForceKeyframe Whether the frame should be forced to be a keyframe. @return Result of the operation, @see FAVResult.
- L326 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L336 _public function_ `FAVResult FlushAndReceivePackets(TArray<FVideoPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L363 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L371 _public function_ `virtual FAVResult ReceivePackets(TArray<FVideoPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L389 _public prototype_ `virtual FVideoEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L396 _public prototype_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TVideoEncoder::TWrapper`  
`template <typename TChildResource, typename TChildConfig> class TWrapper : public TAVCoder<TVideoEncoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>`  
_L224-276_
- inherits: `TAVCoder<TVideoEncoder,TResource,TConfig>::templateTWrapper<TChildResource,TChildConfig>`
- desc: Wrapper encoder that transforms resource/config types for use with a differently typed child encoder. @tparam TChildResource Type of child resource. @tparam TChildConfig Type of child config.
- L227 _public function_ `TWrapper(TSharedRef<TVideoEncoder<TChildResource, TChildConfig>> const& Child) : TAVCoder<TVideoEncoder, TResource, TConfig>::template TWrapper<TChildResource, TChildConfig>(Child)`
- L232 _public function_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override`
- L267 _public function_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override`

#### class `TVideoEncoder`  
`template <typename TResource> class TVideoEncoder<TResource> : public TAVCoder<TVideoEncoder, TResource>`  
_L308-346_
- inherits: `TAVCoder<TVideoEncoder,TResource>`
- desc: Video encoder with a factory, that supports typesafe resource handling. @see TAVCodec
- L283 _public function_ `virtual FVideoEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L296 _public function_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L319 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @param bForceKeyframe Whether the frame should be forced to be a keyframe. @return Result of the operation, @see FAVResult.
- L326 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L336 _public function_ `FAVResult FlushAndReceivePackets(TArray<FVideoPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L363 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L371 _public function_ `virtual FAVResult ReceivePackets(TArray<FVideoPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L389 _public prototype_ `virtual FVideoEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L396 _public prototype_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### class `TVideoEncoder`  
`template <> class TVideoEncoder<> : public TAVCoder<TVideoEncoder>`  
_L354-397_
- inherits: `TAVCoder<TVideoEncoder>`
- desc: Video encoder with a factory. @see TAVCodec
- L283 _public function_ `virtual FVideoEncoderConfig GetMinimalConfig() override` — Get generic configuration values. @return The current minimal configuration.
- L296 _public function_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) override` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.
- L319 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) = 0;` — Send a frame to the underlying codec architecture. @param Resource Resource holding the frame data. An invalid resource will perform a flush (@see FlushPackets) and invalidate the underlying architecture. @param Timestamp Recorded timestamp of the frame. @param bForceKeyframe Whether the frame should be forced to be a keyframe. @return Result of the operation, @see FAVResult.
- L326 _public function_ `FAVResult FlushPackets()` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L336 _public function_ `FAVResult FlushAndReceivePackets(TArray<FVideoPacket>& OutPackets)` — Flush remaining packets and invalidate the underlying architecture. @return Result of the operation, @see FAVResult.
- L363 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) = 0;` — Read a finished packet out of the codec. @param OutPacket Output packet if one is complete. @return Result of the operation, @see FAVResult.
- L371 _public function_ `virtual FAVResult ReceivePackets(TArray<FVideoPacket>& OutPackets)` — Read all finished packets out of the codec. @param OutPackets Output array of completed packets. @return Result of the operation, @see FAVResult.
- L389 _public prototype_ `virtual FVideoEncoderConfig GetMinimalConfig() = 0;` — Get generic configuration values. @return The current minimal configuration.
- L396 _public prototype_ `virtual void SetMinimalConfig(FVideoEncoderConfig const& MinimalConfig) = 0;` — Set generic configuration values. @param MinimalConfig New minimal configuration to set.

#### Free symbols / members of external scopes

- L56 _externvar_ `extern TMap<FString, EScalabilityMode> const ScalabilityModeMap;`
- L58 _function_ `inline TOptional<EScalabilityMode> ScalabilityModeFromString(const FString& ModeString)`
- L99 _function_ `friend bool operator==(const FSpatialLayer& Lhs, const FSpatialLayer& Rhs)`
- L399 _typedef_ `typedef TVideoEncoder<> FVideoEncoder;`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoPacket.h` (Public)


#### struct `FVideoPacket`  
`struct FVideoPacket : public FAVPacket`  
_L12-47_
- inherits: `FAVPacket`
- desc: Video-specific packet container.
- L18 _public member_ `uint32 QP;` — QP that the raw data was encoded with.
- L23 _public member_ `uint8 bIsKeyframe : 1;` — Whether this frame is a keyframe.
- L28 _public member_ `FCodecSpecificInfo CodecSpecificInfo;` — Struct holding advanced information on the video packet
- L33 _public member_ `TOptional<int> SpatialIndex;` — Spatial index of this packet
- L38 _public member_ `TOptional<int> TemporalIndex;` — Temporal index of this packet
- L40 _public prototype_ `FVideoPacket() = default;`
- L41 _public function_ `FVideoPacket(TSharedPtr<uint8> const& DataPtr, uint64 DataSize, uint64 Timestamp, uint64 Index, uint32 QP, bool bIsKeyframe) : FAVPacket(DataPtr, DataSize, Timestamp, Index) , QP(QP) , bIsKeyframe(bIsKeyframe)`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCore/Public/Video/VideoResource.h` (Public)


#### enum `EVideoFormat`  
`enum class EVideoFormat : uint8`  
_L15-29_
- L17 _public enumerator_ `BGRA = EPixelFormat::PF_B8G8R8A8`
- L18 _public enumerator_ `ABGR10 = EPixelFormat::PF_A2B10G10R10`
- L20 _public enumerator_ `NV12 = EPixelFormat::PF_NV12`
- L21 _public enumerator_ `P010 = EPixelFormat::PF_P010`
- L22 _public enumerator_ `R8 = EPixelFormat::PF_R8`
- L23 _public enumerator_ `G16 = EPixelFormat::PF_G16`
- L26 _public enumerator_ `YUV420 = 253U` — TODO No match to engine formats and should be updated if that changes
- L27 _public enumerator_ `YUV444 = 254U`
- L28 _public enumerator_ `YUV444_16 = 255U`

#### struct `FVideoDescriptor`  
`struct FVideoDescriptor`  
_L54-161_
- desc: This struct defines how the allocated resource memory is used in the context of a video.
- L60 _public member_ `EVideoFormat Format;` — Format of the pixel data.
- L65 _public member_ `uint32 Width;` — Width in pixels.
- L70 _public member_ `uint32 Height;` — Height in pixels.
- L75 _public member_ `FResourceBulkDataInterface* BulkData;` — An implementation of the BulkData interface. Used for creating textures from existing data
- L81 _public member_ `mutable FVideoDescriptor* RawDescriptor;` — If this is a descriptor stored in a different format than it really is for transport then its raw descriptor should be described in this variable
- L83 _public prototype_ `FVideoDescriptor() = default;`
- L84 _public function_ `FVideoDescriptor(const FVideoDescriptor& Descriptor) : Format(Descriptor.Format) , Width(Descriptor.Width) , Height(Descriptor.Height) , BulkData(Descriptor.BulkData) , RawDescriptor(Descriptor.RawDescriptor ? new FVideoDescriptor(*Descriptor.RawDescriptor) : nullptr)`
- L93 _public function_ `FVideoDescriptor(EVideoFormat Format, uint32 Width, uint32 Height, FResourceBulkDataInterface* BulkData = nullptr) : Format(Format), Width(Width), Height(Height), BulkData(BulkData), RawDescriptor(nullptr)`
- L98 _public function_ `FVideoDescriptor(EVideoFormat Format, uint32 Width, uint32 Height, const FVideoDescriptor& RawDescriptor, FResourceBulkDataInterface* BulkData = nullptr) : Format(Format), Width(Width), Height(Height), BulkData(BulkData), RawDescriptor(new FVideoDescriptor(RawDescriptor))`
- L103 _public function_ `~FVideoDescriptor()`
- L111 _public function_ `bool operator==(FVideoDescriptor const& RHS) const`
- L116 _public function_ `bool operator!=(FVideoDescriptor const& RHS) const`
- L122 _public function_ `uint8 GetNumChannels() const` — Planar formats are treated as single channel
- L141 _public function_ `uint32 GetSizeInBytes() const` — TODO(Nick): Try and remove this in favour of external initialisation

#### class `FVideoResource`  
`class FVideoResource : public FAVResource`  
_L166-222_
- inherits: `FAVResource`
- desc: Base wrapper for a video device resource.
- L172 _private member_ `FVideoDescriptor Descriptor;` — Descriptor of video data.
- L177 _private member_ `std::atomic<bool> bIsInUse = false;`
- L183 _public function_ `inline FVideoDescriptor const& GetRawDescriptor() const` — @return Get the descriptor of our video data in device memory.
- L188 _public function_ `inline FVideoDescriptor const& GetDescriptor() const` — @return Get the descriptor of our video data.
- L193 _public function_ `inline EVideoFormat GetFormat() const` — @return Get the format of our data.
- L198 _public function_ `inline uint32 GetWidth() const` — @return Get the width of our data.
- L203 _public function_ `inline uint32 GetHeight() const` — @return Get the height of our data.
- L208 _public function_ `inline uint32 GetSize() const` — @return Get the Size in bytes of our Resource.
- L213 _public function_ `inline void SetUsing(bool bUsing)`
- L218 _public function_ `inline bool IsInUse()`
- L220 _public prototype_ `FVideoResource(TSharedRef<FAVDevice> const& Device, FAVLayout const& Layout, FVideoDescriptor const& Descriptor);`
- L221 _public prototype_ `virtual ~FVideoResource() override = default;`

#### class `TVideoResource`  
`template <typename TContext> class TVideoResource : public FVideoResource`  
_L228-237_
- inherits: `FVideoResource`
- desc: Convenience wrapper for a video device resource that requires a specific device context to function.
- L231 _public function_ `inline TSharedPtr<TContext> GetContext() const`
- L233 _public function_ `TVideoResource(TSharedRef<FAVDevice> const& Device, FAVLayout const& Layout, FVideoDescriptor const& Descriptor) : FVideoResource(Device, Layout, Descriptor)`

#### class `TPooledVideoResource`  
`template <typename TResource> class TPooledVideoResource : public TResolvableVideoResource<TResource>`  
_L255-278_
- inherits: `TResolvableVideoResource<TResource>`
- desc: A simple pool-based resolvable video resource. The contents of the pool must be manually managed by the application.
- L258 _public member_ `TArray<TSharedPtr<TResource>> Pool;`
- L260 _public function_ `virtual bool IsResolved(TSharedPtr<FAVDevice> const& Device, FVideoDescriptor const& Descriptor) const override`
- L266 _protected function_ `virtual TSharedPtr<TResource> TryResolve(TSharedPtr<FAVDevice> const& Device, FVideoDescriptor const& Descriptor) override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AVCODECSCORE_API`
- L31 _function_ `inline bool operator==(EPixelFormat LHS, EVideoFormat RHS)`
- L36 _function_ `inline bool operator!=(EPixelFormat LHS, EVideoFormat RHS)`
- L41 _function_ `inline bool operator==(EVideoFormat LHS, EPixelFormat RHS)`
- L46 _function_ `inline bool operator!=(EVideoFormat LHS, EPixelFormat RHS)`
- L243 _typedef_ `template <typename TResource> using TResolvableVideoResource = TResolvable<TResource, TSharedPtr<FAVDevice>, FVideoDescriptor>;` — Wrapper for resolvable video resources.
- L249 _typedef_ `template <typename TResource> using TDelegatedVideoResource = TDelegated<TResource, TSharedPtr<FAVDevice>, FVideoDescriptor>;` — Wrapper for delegated resolvable video resources.
