# Plugins / GameFeaturesToolset

- module root: `Plugins/Experimental/Toolsets/GameFeaturesToolset/Source/GameFeaturesToolset`
- headers: 1; symbols: 17
- symbol kinds: class=1, delegate=1, enum=1, enumerator=6, prototype=8
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, Engine, GameFeatures, Kismet, PluginUtils, Projects, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/GameFeaturesToolset/Source/GameFeaturesToolset/Private/GameFeaturesToolset.h` (Private)


#### enum `EPluginToolsetGFPState`  
`enum class EPluginToolsetGFPState : uint8`  
_L16-24_
- reflection: `UENUM(BlueprintType)`
- desc: Simplified Game Feature Plugin state for AI tools. Maps the engine's ~34 internal states to user-facing states that an LLM would act on.
- L18 _public enumerator_ `Uninitialized`
- L19 _public enumerator_ `Installed`
- L20 _public enumerator_ `Registered`
- L21 _public enumerator_ `Loaded`
- L22 _public enumerator_ `Active`
- L23 _public enumerator_ `Unknown`

#### class `UGameFeaturesToolset`  
`class UGameFeaturesToolset : public UToolsetDefinition`  
_L28-104_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for listing, activating, and deactivating Game Feature Plugins.
- L41 _public prototype_ `static TArray<FString> ListEnabledGameFeaturePlugins();` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Lists all enabled Game Feature Plugins  sorted by name. Enabled plugins are the only plugins known by the Game Features system beyond identifying if a plugin is a Game Feature Plugin. Use the Plugins toolset to do general plugin enable/disable tasks. @return Sorted names of all enabled Game Feature Plugins.
- L51 _public prototype_ `static TArray<FString> ListDiscoveredGameFeaturePlugins();` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Lists all discovered Game Feature Plugins sorted by name. This includes enabled and disabled plugins. Only enabled plugins are known by the Game Features system beyond identifying if a plugin is a Game Feature Plugin. Use the Plugins toolset to do general plugin enable/disable tasks. @return Sorted names of all discovered Game Feature Plugins.
- L60 _public prototype_ `static bool IsGameFeaturePlugin(const FString& PluginName);` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Return whether or not a plugin is a Game Feature Plugin. Will error if no plugin of this name can be found by the Plugin Manager. @param PluginName Name of the plugin @return True if the plugin is a Game Feature Plugin
- L70 _public prototype_ `static bool IsGameFeatureActive(const FString& PluginName);` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Checks whether a Game Feature Plugin is active. Raises an error if the subsystem is unavailable or the plugin is not found. Use GetGameFeatureState if you need the current state when the plugin is not active. @param PluginName Name of the Game Feature Plugin. @return True if the Game Feature Plugin is active.
- L79 _public prototype_ `static EPluginToolsetGFPState GetGameFeatureState(const FString& PluginName);` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Gets the current state of a Game Feature Plugin. @param PluginName Name of the Game Feature Plugin. @return Simplified state enum. Raises an error if the subsystem is unavailable or the plugin is not found.
- L91 _public prototype_ `static bool RequestActivateGameFeature(const FString& PluginName);` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Requests activation of a Game Feature Plugin. Returns true if the activation request was submitted successfully. The actual activation happens asynchronously -- poll GetGameFeatureState() or IsGameFeatureActive() to confirm completion. Raises an error if the subsystem is unavailable or the plugin is not found. @param PluginName Name of the GFP. @return True if the request was submitted.
- L102 _public prototype_ `static bool RequestDeactivateGameFeature(const FString& PluginName);` — `UFUNCTION(meta = (AICallable), Category = "GameFeatures")` — Requests deactivation of a Game Feature Plugin. Returns true if the deactivation request was submitted successfully. The actual deactivation happens asynchronously -- poll GetGameFeatureState() to confirm completion. Raises an error if the subsystem is unavailable or the plugin is not found. @param PluginName Name of the GFP. @return True if the request was submitted.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameFeaturesToolset, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameFeaturesToolset, Log, All);`
