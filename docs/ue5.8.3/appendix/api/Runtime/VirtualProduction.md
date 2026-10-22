# Runtime / VirtualProduction

- module root: `Source/Runtime/VirtualProduction/VirtualProduction`
- headers: 1; symbols: 17
- symbol kinds: class=1, function=1, member=3, namespace=2, prototype=9, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/VirtualProduction/VirtualProduction/Public/IUpscalerModularFeature.h` (Public)


#### struct `UE::VirtualProduction::FUpscalerModularFeatureParameters`  
`struct FUpscalerModularFeatureParameters`  
_L20-27_
- desc: The upscaler modular feature parameters.
- L23 _public member_ `float UpscalerScreenPercentage = 1.0f;` — Upscaler screen percentage vaue.
- L26 _public member_ `float SecondaryScreenPercentage = 1.0f;` — Secondary screen percentage value.

#### class `UE::VirtualProduction::IUpscalerModularFeature`  
`class IUpscalerModularFeature : public IModularFeature`  
_L39-128_
- inherits: `IModularFeature`
- desc: Interface for a modular feature of a Upscaler. This interface provides a way to interact with the upscaler without requiring the presence of their specific plugins. It allows modular features to be integrated and accessed within the rendering pipeline in a flexible and decoupled manner. Classes implementing this interface can define custom behavior and settings for Scene View Extensions while maintaining compatibility with other parts of the Unreal Engine system.
- L43 _public prototype_ `virtual ~IUpscalerModularFeature() = default;`
- L46 _public member_ `static constexpr const TCHAR* ModularFeatureName = TEXT("Ups` — The unique modular feature name.
- L52 _public prototype_ `virtual const FName& GetName() const = 0;` — Returns the unique identifier name for this feature.
- L57 _public prototype_ `virtual const FText& GetDisplayName() const = 0;` — Gets the display name shown in the UI.
- L62 _public prototype_ `virtual const FText& GetTooltipText() const = 0;` — Returns a hint text for the feature.
- L69 _public prototype_ `virtual bool IsFeatureEnabled() const = 0;` — Determines whether the feature is currently enabled and available for use. This can depend on config, platform, or runtime logic.
- L78 _public prototype_ `virtual bool AddSceneViewExtensionIsActiveFunctor(const FSceneViewExtensionIsActiveFunctor& IsActiveFunction) = 0;` — Adds a functor and returns a GUID to identify it. @param IsActiveFunction - the functor with custom logic for the upscaler ViewExtension @return true on success
- L87 _public prototype_ `virtual bool RemoveSceneViewExtensionIsActiveFunctor(const FGuid& FunctorGuid) = 0;` — Removes a functor by GUID. @param FunctorGuid - use value from the FSceneViewExtensionIsActiveFunctor::GetGuid() @return true if the functor exists and has been deleted
- L96 _public function_ `virtual bool GetSettings(FInstancedPropertyBag& OuUpscalerSettings) const` — Get default settings for this upscaler @param OuUpscalerSettings - (out) default settings @return true if successed.
- L108 _public prototype_ `virtual void SetupSceneView( const FInstancedPropertyBag& InUpscalerSettings, FSceneView& InOutView) = 0;` — Setup SceneView for this upscaler. Upscalers should configure the view properties (e.g. AntiAliasingMethod) for their rendering pipeline (temporal/spatial/etc.). @param InUpscalerSettings - (in) upscaler settings which we want to use. This settings should be associated with the InOutViews. @param InOutView          - (in) scene view to that will be configured.
- L124 _public prototype_ `virtual bool PostConfigureViewFamily( const FInstancedPropertyBag& InUpscalerSettings, const FUpscalerModularFeatureParameters& InUpscalerParam, FSceneViewFamilyContext& InOutViewFamily) = 0;` — Configure ViewFamily and it Views for specific settings and use these settings for the views. Note: Expected that these parameters should be configured: InOutViewFamily.SetScreenPercentageInterface(); InOutViewFamily.SecondaryViewFraction; 241300 Some features from the settings may require additional customization in the view family or view structures. @param InUpscalerSettings - (in) upscaler settings which we want to use. This settings should be associated with the InOutViews. @param InUpscalerParam    - (in) upscaler parameters that is used to configure view family. @param InOutViewFamily    - (in, out) The view family that will be configured.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace VirtualProduction` (scope `UE`)
