# Developer / IOSTargetPlatformSettings

- module root: `Source/Developer/IOS/IOSTargetPlatformSettings`
- headers: 1; symbols: 20
- symbol kinds: class=1, function=2, member=4, prototype=13
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, TargetPlatform

### `Source/Developer/IOS/IOSTargetPlatformSettings/Private/IOSTargetPlatformSettings.h` (Private)


#### class `FIOSTargetPlatformSettings`  
`class FIOSTargetPlatformSettings : public TTargetPlatformSettingsBase<FIOSPlatformProperties>`  
_L21-82_
- inherits: `TTargetPlatformSettingsBase<FIOSPlatformProperties>`
- desc: FIOSTargetPlatformSettings
- L28 _public prototype_ `FIOSTargetPlatformSettings(bool bInISTVOS, bool bInIsVisionOS);` — Default constructor.
- L33 _public prototype_ `~FIOSTargetPlatformSettings();` — Destructor.
- L37 _public prototype_ `virtual bool SupportsFeature( ETargetPlatformFeatures Feature ) const override;`
- L39 _public prototype_ `virtual void GetAllPossibleShaderFormats( TArray<FName>& OutFormats ) const override;`
- L41 _public prototype_ `virtual void GetAllTargetedShaderFormats( TArray<FName>& OutFormats ) const override;`
- L44 _public prototype_ `virtual void GetReflectionCaptureFormats( TArray<FName>& OutFormats ) const override;`
- L46 _public function_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings( ) const override`
- L51 _public prototype_ `virtual const UTextureLODSettings& GetTextureLODSettings() const override;`
- L53 _public function_ `virtual void RegisterTextureLODSettings(const UTextureLODSettings* InTextureLODSettings) override`
- L62 _public prototype_ `virtual bool UsesDistanceFields() const override;`
- L64 _public prototype_ `virtual bool UsesRayTracing() const override;`
- L65 _public prototype_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override;`
- L70 _private member_ `bool bIsTVOS;` — true if this is targeting TVOS vs IOS
- L71 _private member_ `bool bIsVisionOS;`
- L74 _private member_ `const UTextureLODSettings* TextureLODSettings;` — Holds the cache of the target LOD settings.
- L77 _private member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds the static mesh LOD settings.
- L79 _private prototype_ `bool GetIsDistanceField() const;`
- L80 _private prototype_ `int32 GetMobileShadingPath() const ;`
- L81 _private prototype_ `bool GetIsMobileForwardEnableClusteredReflections() const;`
