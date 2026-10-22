# Plugins / PluginToolset

- module root: `Plugins/Experimental/Toolsets/PluginToolset/Source/PluginToolset`
- headers: 1; symbols: 54
- symbol kinds: class=1, member=29, prototype=20, struct=4
- PrivateDependencyModuleNames: CoreUObject, Engine, Kismet, PluginUtils, Projects, SourceControl, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/PluginToolset/Source/PluginToolset/Private/PluginToolset.h` (Private)


#### struct `FPluginDescriptorToolsetInfo`  
`struct FPluginDescriptorToolsetInfo`  
_L14-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: Editable metadata fields from a plugin's descriptor.
- L20 _public member_ `FString FriendlyName;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Friendly name of the plugin.
- L24 _public member_ `FString Description;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Description of the plugin.
- L28 _public member_ `FString Category;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — The name of the category this plugin belongs to.
- L35 _public member_ `FString VersionName;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Name of the version for this plugin. This is the front-facing part of the version number. It doesn't need to match the version number numerically, but should be updated when the version number is increased accordingly.
- L43 _public member_ `int32 Version = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Version number for the plugin. The version number must increase with every version of the plugin, so that the system can determine whether one version of a plugin is newer than another, or to enforce other requirements. This version number is not displayed in front-facing UI. Use the VersionName for that.
- L47 _public member_ `FString CreatedBy;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — The company or individual who created this plugin. This is an optional field that may be displayed in the user interface.
- L51 _public member_ `FString CreatedByURL;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Hyperlink URL string for the company or individual who created this plugin. This is optional.
- L55 _public member_ `FString DocsURL;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Documentation URL string.
- L59 _public member_ `FString MarketplaceURL;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Marketplace URL for this plugin. This URL will be embedded into projects that enable this plugin, so we can redirect to the marketplace if a user doesn't have it installed.
- L63 _public member_ `FString SupportURL;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Support URL/email for this plugin.
- L67 _public member_ `bool bCanContainContent = false;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Can this plugin contain content?
- L71 _public member_ `bool bIsBetaVersion = false;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Marks the plugin as beta in the UI.
- L75 _public member_ `bool bIsExperimentalVersion = false;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Marks the plugin as experimental in the UI.
- L79 _public member_ `bool bIsSealed = false;` — `UPROPERTY(BlueprintReadWrite, Category = "PluginToolset")` — Prevents other plugins from depending on this plugin.

#### struct `FPluginToolsetInfo`  
`struct FPluginToolsetInfo`  
_L84-108_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata about a plugin.
- L89 _public member_ `FString Description;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L92 _public member_ `int32 Version = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L95 _public member_ `FString VersionName;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L98 _public member_ `FString BaseDir;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L101 _public member_ `FString ContentDir;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L104 _public member_ `FString DescriptorPath;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`
- L107 _public member_ `FString MountedAssetPath;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")`

#### struct `FPluginDependencyToolsetInfo`  
`struct FPluginDependencyToolsetInfo`  
_L112-127_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single dependency entry from a plugin's Plugins array.
- L118 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Name of the dependency plugin.
- L122 _public member_ `bool bOptional = false;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Whether the dependency is optional.
- L126 _public member_ `bool bEnabled = true;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Whether the dependency should be enabled.

#### struct `FPluginTemplateDescriptionToolsetInfo`  
`struct FPluginTemplateDescriptionToolsetInfo`  
_L131-154_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata about a plugin template description.
- L137 _public member_ `FText Name;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Name of this template in the GUI
- L141 _public member_ `FText Description;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Description of this template in the GUI
- L145 _public member_ `FString OnDiskPath;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Path to the directory containing template files.
- L149 _public member_ `FText DefaultTemplateName;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Default plugin name. Typically a prefix.
- L153 _public member_ `bool bCanBePlacedInEngine = false;` — `UPROPERTY(BlueprintReadOnly, Category = "PluginToolset")` — Whether or not this template can be used for Engine plugins

#### class `UPluginToolset`  
`class UPluginToolset : public UToolsetDefinition`  
_L158-350_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Tools for creating, editing, enabling, and querying Unreal plugins
- L170 _public prototype_ `static TArray<FString> ListEnabledPlugins();` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Lists the names of all enabled plugins, sorted alphabetically. @return Sorted array of enabled plugin names.
- L177 _public prototype_ `static TArray<FString> ListDiscoveredPlugins();` — `UFUNCTION(meta = (AICallable), Category = "PluginToolset")` — Lists the names of all discovered plugins (enabled and disabled), sorted alphabetically. @return Sorted array of discovered plugin names.
- L186 _public prototype_ `static FPluginToolsetInfo GetPluginInfo(const FString& PluginName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Gets metadata for a discovered plugin, including description, version, base directory, content directory, descriptor path, and mounted asset path. @param PluginName The name of the plugin. @return Metadata for the plugin.
- L194 _public prototype_ `static bool IsEnabled(const FString& PluginName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Checks whether a discovered plugin is currently enabled. @param PluginName The name of the plugin. @return True if the plugin is enabled, false if it is disabled.
- L202 _public prototype_ `static TArray<FPluginDependencyToolsetInfo> GetPluginDependencies(const FString& PluginName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Returns the dependency entries from a plugin's Plugins array in its .uplugin file. @param PluginName The name of the plugin. @return Array of dependency entries declared in the plugin's .uplugin file.
- L210 _public prototype_ `static TArray<FString> GetPluginDependents(const FString& PluginName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Returns the names of all discovered plugins that declare a dependency on the given plugin. @param PluginName The name of the plugin to search for as a dependency target. @return Sorted array of plugin names that list the given plugin in their Plugins array.
- L219 _public prototype_ `static FString GetPluginForAsset(const FString& AssetPath);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Returns the name of the enabled plugin whose content mount point contains the given asset path. Accepts full asset paths or mount point prefixes (e.g. /PluginName/ or /Game/Path/To/Asset). @param AssetPath The asset or mount point path to look up. @return The name of the plugin that owns the asset.
- L228 _public prototype_ `static TArray<FPluginTemplateDescriptionToolsetInfo> GetPluginTemplateDescriptions();` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Returns the list of available plugin templates. Pass one of the results to CreatePlugin to create a new plugin from that template. @return Array of available plugin template descriptors.
- L237 _public prototype_ `static bool IsPluginCreationAllowed();` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Checks whether the editor settings permit plugin creation from the plugin browser. @return True if plugin creation is allowed, false if it is disabled in Editor Settings.
- L251 _public prototype_ `static bool ValidateNewPluginNameAndLocation( const FString& PluginName, const FString& RelativePluginLocation, const bool bPlaceInEngine, const FPluginTemplateDescriptionToolsetInfo& TemplateInfo);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Validates that PluginName and RelativePluginLocation are acceptable for a new plugin. @param PluginName The proposed plugin name. @param RelativePluginLocation Parent directory for the new plugin relative to template's default location. This should be empty unless you wish to specify a subdirectory. @param bPlaceInEngine Use Engine Plugins directory rather than Game Plugins directory location. Only some Templates allow placing in Engine. See the TemplateInfo's bCanBePlacedInEngine. This should be false unless explicitly requested by the user. @param TemplateInfo The plugin template to potentially create from. @return True if the name and location are valid.
- L271 _public prototype_ `static FString CreatePlugin( const FString& PluginName, const FString& RelativePluginLocation, const bool bPlaceInEngine, const FPluginTemplateDescriptionToolsetInfo& TemplateInfo, const FString& Description);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Creates a new plugin from a template and loads it into the editor. Use GetPluginTemplateDescriptions to obtain a valid TemplateInfo. @param PluginName Name for the new plugin. @param RelativePluginLocation Parent directory for the new plugin relative to template's default location. This should be empty unless you wish to specify a subdirectory. @param bPlaceInEngine Use Engine Plugins directory rather than Game Plugins directory location. Only some Templates allow placing in Engine. See the TemplateInfo's bCanBePlacedInEngine. This should be false unless explicitly requested by the user. @param TemplateInfo The plugin template to create from. @param Description A description for the new plugin. @return Created plugin's descriptor filename. Empty on failure.
- L285 _public prototype_ `static bool IsPluginModificationAllowed();` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Checks whether the editor settings permit modifying plugins from the plugin browser. @return True if plugin modification is allowed, false if it is disabled in Editor Settings.
- L293 _public prototype_ `static void SetPluginEnabled(const FString& PluginName, bool bEnabled);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Enables or disables a plugin in the project config. The change takes effect on the next editor restart. @param PluginName The name of the plugin. @param bEnabled True to enable, false to disable.
- L303 _public prototype_ `static FPluginDescriptorToolsetInfo GetPluginDescriptor(const FString& PluginName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Gets the editable descriptor fields for a discovered plugin. @param PluginName The name of the plugin. @return The plugin's current editable descriptor fields.
- L313 _public prototype_ `static void UpdatePluginDescriptor(const FString& PluginName, const FPluginDescriptorToolsetInfo& NewDescriptor);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Updates a plugin's descriptor fields and writes them to its .uplugin file. Checks out the file via source control if source control is enabled. No-ops if the serialized descriptor is unchanged (file is not touched). @param PluginName The name of the plugin to update. @param NewDescriptor The new descriptor field values to apply.
- L325 _public prototype_ `static void AddPluginDependency(const FString& PluginName, const FString& DependencyName, bool bOptional, bool bEnabled);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Adds a dependency entry to a plugin's Plugins array in its .uplugin file. No-ops if a dependency with that name already exists with matching settings. The dependency plugin does not need to be currently discovered. @param PluginName The name of the plugin to modify. @param DependencyName The name of the plugin to add as a dependency. @param bOptional Whether the dependency is optional. @param bEnabled Whether the dependency should be enabled.
- L333 _public prototype_ `static void RemovePluginDependency(const FString& PluginName, const FString& DependencyName);` — `UFUNCTION(meta=(AICallable), Category = "PluginToolset")` — Removes a dependency entry from a plugin's Plugins array in its .uplugin file. @param PluginName The name of the plugin to modify. @param DependencyName The name of the dependency to remove.
- L343 _private prototype_ `static TSharedPtr<FPluginTemplateDescription> FindPluginTemplateDescriptionForToolsetInfo( const FPluginTemplateDescriptionToolsetInfo& PluginTemplateInfo);` — Resolves a FPluginTemplateDescriptionToolsetInfo to its underlying FPluginTemplateDescription. @param PluginTemplateInfo The toolset info to look up. @return The matching template description, or nullptr if no match was found.
- L346 _private prototype_ `static FString GeneratePluginFolderPath(FPluginTemplateDescription& PluginTemplate, bool bPlaceInEngine);`
- L348 _private prototype_ `static bool ValidateNewPluginNameAndLocationInternal(const FString& PluginName, const FString& RelativePluginLocation, const bool bPlaceInEngine, FPluginTemplateDescription& PluginTemplate, FString& OutAbsolutePluginLocation);`
