# Plugins / DMXDisplayClusterLightCard

- module root: `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayClusterLightCard`
- headers: 2; symbols: 44
- symbol kinds: class=2, member=31, prototype=10, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: DMXProtocol, DMXRuntime, DisplayCluster, DisplayClusterLightCardExtender

### `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayClusterLightCard/Private/DMXDisplayClusterLightCardComponent.h` (Private)


#### struct `FDMXDisplayClusterLightCardActorDataValueRanges`  
`struct FDMXDisplayClusterLightCardActorDataValueRanges`  
_L18-115_
- reflection: `USTRUCT()`
- L23 _public member_ `double MinDistanceFromCenter = 0.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L26 _public member_ `double MaxDistanceFromCenter = 1000.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L29 _public member_ `double MinLongitude = 0.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L32 _public member_ `double MaxLongitude = 360.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L35 _public member_ `double MinLatitude = -90.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L38 _public member_ `double MaxLatitude = 90.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L42 _public member_ `float MinLongitudeU = -2.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — Min longitude when the light card uses UV Mode
- L46 _public member_ `float MaxLongitudeU = 2.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — Max longitude when the light card uses UV Mode
- L50 _public member_ `float MinLatitudeV = -2.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — Min latitude when the light card uses UV Mode
- L54 _public member_ `float MaxLatitudeV = 2.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — Max latitude when the light card uses UV Mode
- L57 _public member_ `double MinSpin = 0.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L60 _public member_ `double MaxSpin = 360.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L63 _public member_ `double MinPitch = 0.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L66 _public member_ `double MaxPitch = 360.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L69 _public member_ `double MinYaw = 0.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L72 _public member_ `double MaxYaw = 360.0;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L75 _public member_ `FVector2D MinScale = FVector2D(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L78 _public member_ `FVector2D MaxScale = FVector2D(5.f, 5.f);` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L81 _public member_ `float MinTemperature = 0.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L84 _public member_ `float MaxTemperature = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L87 _public member_ `float MinTint = -1.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L90 _public member_ `float MaxTint = 1.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L93 _public member_ `float MinExposure = -5.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L96 _public member_ `float MaxExposure = 5.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L99 _public member_ `float MinGain = 0.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L102 _public member_ `float MaxGain = 5.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L105 _public member_ `float MinFeathering = 0.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L108 _public member_ `float MaxFeathering = 3.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L111 _public member_ `float MinGradientAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`
- L114 _public member_ `float MaxGradientAngle = 360.f;` — `UPROPERTY(EditAnywhere, Category = "DMX")`

#### class `UDMXDisplayClusterLightCardComponent`  
`class UDMXDisplayClusterLightCardComponent : public UDMXComponent`  
_L118-141_
- reflection: `UCLASS(NotBlueprintable, HideCategories = (AssetUserData, Tags, Replication))`
- inherits: `UDMXComponent`
- L125 _protected prototype_ `virtual void OnRegister() override;`
- L126 _protected prototype_ `virtual void PostLoad() override;`
- L128 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L135 _public member_ `FDMXDisplayClusterLightCardActorDataValueRanges ValueRanges;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "DMX", Meta = (ShowOnlyInnerProperties))` — Value ranges for Min and Max DMX Values
- L140 _private prototype_ `void OnLightCardReceivedDMXFromPatch(UDMXEntityFixturePatch* FixturePatch, const FDMXNormalizedAttributeValueMap& ValuePerAttribute);` — `UFUNCTION()` — Called when the fixture patch received DMX

### `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayClusterLightCard/Private/DMXDisplayClusterLightCardModule.h` (Private)


#### class `FDMXDisplayClusterLightCardModule`  
`class FDMXDisplayClusterLightCardModule : public IModuleInterface , public IDisplayClusterLightCardActorExtender`  
_L11-29_
- inherits: `IModuleInterface,IDisplayClusterLightCardActorExtender`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `virtual FName GetExtenderName() const override;`
- L23 _public prototype_ `virtual TSubclassOf<UActorComponent> GetAdditionalSubobjectClass()override;`
- L25 _public prototype_ `virtual FName GetCategory() const override;`
- L26 _public prototype_ `virtual bool ShouldShowSubcategories() const override;`
