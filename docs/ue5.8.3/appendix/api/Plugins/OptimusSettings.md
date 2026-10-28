# Plugins / OptimusSettings

- module root: `Plugins/Animation/DeformerGraph/Source/OptimusSettings`
- headers: 2; symbols: 27
- symbol kinds: class=2, delegate=1, enum=1, enumerator=3, macro=1, member=6, namespace=1, prototype=12
- PrivateDependencyModuleNames: ComputeFramework, Core, CoreUObject, DeveloperSettings, Engine, RHI, RenderCore

### `Plugins/Animation/DeformerGraph/Source/OptimusSettings/Private/OptimusSettingsModule.h` (Private)


#### class `FOptimusSettingsModule`  
`class FOptimusSettingsModule : public IModuleInterface, public IMeshDeformerProvider`  
_L11-27_
- inherits: `IModuleInterface,IMeshDeformerProvider`
- L14 _private prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L15 _private prototype_ `void ShutdownModule() override;`
- L18 _private prototype_ `bool IsSupported(EShaderPlatform Platform) const override;` — IMeshDeformerProvider implementation
- L19 _private prototype_ `TObjectPtr<UMeshDeformer> GetDefaultMeshDeformer(FDefaultMeshDeformerSetup const& InSetup) override;`
- L22 _private prototype_ `void CacheDefaultMeshDeformers();`
- L23 _private prototype_ `void CacheDefaultMeshDeformers(UOptimusSettings const* InSettings);`
- L25 _private member_ `TStrongObjectPtr<UMeshDeformer> DefaultDeformer;`
- L26 _private member_ `TStrongObjectPtr<UMeshDeformer> DefaultRecomputeTangentDeformer;`

### `Plugins/Animation/DeformerGraph/Source/OptimusSettings/Public/OptimusSettings.h` (Public)


#### enum `EOptimusDefaultDeformerMode`  
`enum class EOptimusDefaultDeformerMode : uint8`  
_L15-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `Never` — Never apply the default deformers.
- L20 _public enumerator_ `OptIn` — Only apply default deformers if requested.
- L22 _public enumerator_ `Always` — Always apply the default deformers.

#### class `UOptimusSettings`  
`class UOptimusSettings : public UDeveloperSettings`  
_L26-48_
- reflection: `UCLASS(MinimalAPI, config = DeformerGraph, defaultconfig, meta = (DisplayName = "DeformerGraph"))`
- inherits: `UDeveloperSettings`
- L32 _private member_ `EOptimusDefaultDeformerMode DefaultMode = EOptimusDefaultDeformerMode::OptIn;` — `UPROPERTY(config, EditAnywhere, Category = DeformerGraph)` — Set when skinned meshes should have a default deformer applied.
- L36 _private member_ `TSoftObjectPtr<UMeshDeformer> DefaultDeformer;` — `UPROPERTY(config, EditAnywhere, Category = DeformerGraph, meta = (AllowedClasses = "/Script/OptimusCore.OptimusDeformer", EditCondition = "DefaultMode != EOptimusDefaultDeformerMode::Never"))` — A default deformer that will be used on a skinned mesh if no other deformer has been set.
- L40 _private member_ `TSoftObjectPtr<UMeshDeformer> DefaultRecomputeTangentDeformer;` — `UPROPERTY(config, EditAnywhere, Category = DeformerGraph, meta = (AllowedClasses = "/Script/OptimusCore.OptimusDeformer", EditCondition = "DefaultMode != EOptimusDefaultDeformerMode::Never"))` — A default deformer that will be used on a skinned mesh if no other deformer has been set, and if the mesh has requested to recompute tangets.
- L43 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, UOptimusSettings const*);`
- L44 _private member_ `static FOnUpdateSettings OnSettingsChange;`
- L46 _private prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSSETTINGS_API`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, UOptimusSettings const*);`
- L50 _namespace_ `namespace Optimus`
- L53 _prototype_ `bool IsSupported(EShaderPlatform Platform);` (scope `Optimus`) — Returns true if DeformerGraph is supported on a platform.
- L56 _prototype_ `bool IsEnabled();` (scope `Optimus`) — Returns true if DeformerGraph is currently enabled.
- L59 _prototype_ `bool IsAssetValidationEnabled();` (scope `Optimus`) — Returns true if DeformerGraph should enable asset validation.
- L62 _prototype_ `FName GetEnableAssetValidationCVarName();` (scope `Optimus`) — Returns the name of the CVar that toggles asset validation, used by warning messages.
