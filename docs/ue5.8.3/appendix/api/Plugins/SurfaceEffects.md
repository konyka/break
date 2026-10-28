# Plugins / SurfaceEffects

- module root: `Plugins/Experimental/SurfaceEffects/Source/SurfaceEffects`
- headers: 3; symbols: 20
- symbol kinds: class=4, function=3, member=6, prototype=4, struct=3
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, DeveloperSettings

### `Plugins/Experimental/SurfaceEffects/Source/SurfaceEffects/Public/SurfaceEffects.h` (Public)


#### class `FSurfaceEffectsModule`  
`class FSurfaceEffectsModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/SurfaceEffects/Source/SurfaceEffects/Public/SurfaceEffectsSettings.h` (Public)


#### class `USurfaceEffectsSettings`  
`class USurfaceEffectsSettings : public UDeveloperSettings`  
_L9-19_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig, meta=(DisplayName="Surface Effects"))`
- inherits: `UDeveloperSettings`
- L18 _public member_ `FSoftObjectPath SurfaceEffectsDataTable;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags, meta = (AllowedClasses = "/Script/Engine.DataTable", RowType = "/Script/SurfaceEffects.SurfaceEffectTableRow"))` — Data table for storing surface effect rules @see FSurfaceEffectTableRow

### `Plugins/Experimental/SurfaceEffects/Source/SurfaceEffects/Public/SurfaceEffectsSubsystem.h` (Public)


#### struct `FSurfaceEffectContextBase`  
`struct FSurfaceEffectContextBase`  
_L16-24_
- desc: Base context for determining which enum value to return based on a certain rule. We assume most surface interactions will want to use EPhysicalSurface as part of the context.
- L18 _public function_ `explicit FSurfaceEffectContextBase(const EPhysicalSurface PhysicalSurface) : PhysicalSurface(PhysicalSurface)`
- L23 _public member_ `EPhysicalSurface PhysicalSurface;`

#### struct `TSurfaceEffectResult`  
`template <typename TEnum> struct TSurfaceEffectResult`  
_L30-36_
- desc: TSurfaceEffectResult - results of a GetSurface call
- L32 _public member_ `TEnum OutSurface;`
- L35 _public member_ `bool bSuccess = false;` — Set to true if we successfully got a surface

#### class `USurfaceEffectRule`  
`class USurfaceEffectRule : public UDataAsset`  
_L43-58_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UDataAsset`
- desc: Base data asset used to store what conditions result in a specific surface being returned
- L54 _public function_ `virtual bool GetSurface(uint8& OutSurfaceValue, const FSurfaceEffectContextBase& Context)` — @param OutSurfaceValue The enum value to be used when casting back to the enum class @param Context Context data used by the rule to determine what value to return @return Returns true if a valid enum value is outputted. Otherwise, return false

#### struct `FSurfaceEffectTableRow`  
`struct FSurfaceEffectTableRow : public FTableRowBase`  
_L64-70_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- desc: Data Table Row that effectively wraps the Surface Effect Rule
- L69 _public member_ `TObjectPtr<USurfaceEffectRule> Rule;` — `UPROPERTY(EditAnywhere , Category="Surface Effect")`

#### class `USurfaceEffectsSubsystem`  
`class USurfaceEffectsSubsystem : public UGameInstanceSubsystem`  
_L76-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameInstanceSubsystem`
- desc: A system for handling various surface enums based on contexts
- L81 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L84 _public function_ `template <typename TEnum> TSurfaceEffectResult<TEnum> GetSurface(const FSurfaceEffectContextBase& Context)`
- L116 _private member_ `TObjectPtr<UDataTable> SurfaceEffectsData;` — `UPROPERTY()` — We store the UEnum name as the row name in a data table to get the rule associated with that surface enum
- L118 _private prototype_ `static bool IsEnabled();`
