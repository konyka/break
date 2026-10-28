# Plugins / NiagaraToolsets

- module root: `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets`
- headers: 10; symbols: 141
- symbol kinds: class=13, function=4, member=26, prototype=93, struct=5

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset.h` (Private)


#### class `UNiagaraToolset`  
`class UNiagaraToolset : public UToolsetDefinition`  
_L19-47_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UToolsetDefinition`
- desc: Base class for all Niagara Toolsets. Provides common validation and error reporting functionality for Niagara-related operations. Derived toolsets handle specific aspects like System editing, Component interaction, and Blueprint integration.
- L26 _public prototype_ `static bool ValidateSystem(UNiagaraSystem* System);` — Validates that a NiagaraSystem pointer is valid, raising a script error if not
- L29 _public prototype_ `static bool ValidateComponent(UNiagaraComponent* Component);` — Validates that a NiagaraComponent pointer is valid, raising a script error if not
- L32 _public prototype_ `static void Error(FText Error);` — Reports a localized error message to the user via script error system
- L35 _public prototype_ `static void Error(FString Error);` — Reports an error message string to the user via script error system
- L38 _public prototype_ `static void Error(TArrayView<FText> Errors);` — Reports multiple error messages to the user via script error system
- L42 _public function_ `template<typename... ArgTypes> static inline void Error(const TCHAR* Fmt, ArgTypes&&... InArgs)` — Reports a formatted error message with printf-style formatting

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolsetJsonConverters.h` (Private)


#### struct `FToolsetNiagaraTypeDefinition`  
`struct FToolsetNiagaraTypeDefinition`  
_L16-23_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Wrapper struct for FNiagaraTypeDefinition that exposes only the UStruct pointer for JSON conversion. FNiagaraTypeDefinition is a complex struct with internal state. This wrapper simplifies JSON conversion by only exposing the Struct field, which is sufficient for reconstruction.
- L22 _public member_ `TObjectPtr<UObject> ClassStructOrEnum;` — `UPROPERTY(EditAnywhere, Category=Variant)` — Reference to the UScriptStruct, UEnum, or UClass that defines this Niagara type.

#### class `FToolsetNiagaraTypeDefinitionConverter`  
`class FToolsetNiagaraTypeDefinitionConverter : public UE::ToolsetRegistry::FToolsetJsonConverter`  
_L31-40_
- inherits: `UE::ToolsetRegistry::FToolsetJsonConverter`
- desc: Custom JSON converter for FNiagaraTypeDefinition properties. Converts between FNiagaraTypeDefinition and JSON by using the simplified FToolsetNiagaraTypeDefinition wrapper struct.
- L34 _public prototype_ `virtual FString GetName() const override;`
- L35 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L36 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema(TNotNull<const FProperty*> Property) override;`
- L37 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault(TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L38 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData(TNotNull<FProperty*> Property, const void* Value) override;`
- L39 _public prototype_ `virtual bool JsonDataToProperty(const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### struct `FNiagaraToolsetInstancedValue`  
`struct FNiagaraToolsetInstancedValue`  
_L56-71_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Wrapper struct for FInstancedStruct that simplifies JSON conversion. Represents an instanced value that can be one of multiple allowed struct types. The allowed types are determined by BaseStruct metadata (auto-discovered derived types) and optional AdditionalTypes metadata (explicitly specified types). When working with this type, check the JSON schema's oneOf array to see all valid types. Specialized types (derived from BaseStruct) are listed first, followed by additional types.
- L70 _public member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY(EditAnywhere, Category=Variant, meta=( ToolTip="The struct type for this instanced value. Must match one of the allowed types in the schema." ))` — The ScriptStruct type that defines the data structure for this instanced value. Must be one of the allowed types defined in the schema's oneOf array. Specialized types (if any) should be preferred when applicable. Refer to the schema descriptions for guidance on when to use each type.

#### class `FToolsetNiagaraInstancedValueConverter`  
`class FToolsetNiagaraInstancedValueConverter : public UE::ToolsetRegistry::FToolsetJsonConverter`  
_L82-120_
- inherits: `UE::ToolsetRegistry::FToolsetJsonConverter`
- desc: Custom JSON converter for FNiagaraExt_InstancedValue properties. Automatically discovers valid types using BaseStruct metadata (derived types) and AdditionalTypes metadata (explicitly included types), generating comprehensive JSON schemas with oneOf arrays and helpful descriptions to guide AI usage. Type discovery is cached for performance.
- L85 _public prototype_ `virtual FString GetName() const override;`
- L86 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L87 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema(TNotNull<const FProperty*> Property) override;`
- L88 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault(TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L89 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData(TNotNull<FProperty*> Property, const void* Value) override;`
- L90 _public prototype_ `virtual bool JsonDataToProperty(const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`
- L94 _private prototype_ `void GetValidStructTypes(const FStructProperty* StructProperty, TArray<const UScriptStruct*>& OutStructs);` — Discovers all valid struct types using BaseStruct metadata (auto-discovers derived types)
- L97 _private prototype_ `bool DerivedFrom(const UScriptStruct* Struct, const UScriptStruct* Base) const;` — Checks if a struct derives from a base struct
- L100 _private prototype_ `void GetAdditionalTypes(const FStructProperty* StructProperty, TArray<const UScriptStruct*>& OutStructs);` — Gets additional types to include based on AdditionalTypes metadata
- L103 _private prototype_ `FString GetStructDescription(const UScriptStruct* Struct) const;` — Extracts description from struct metadata to provide context in JSON schema
- L106 _private prototype_ `TSharedPtr<FJsonObject> BuildOneOfSchema(const TArray<const UScriptStruct*>& AllowedTypes, const FString& Description, int32 SpecializedTypeCount);` — Builds a oneOf JSON schema with descriptions for each allowed type
- L111 _private prototype_ `TSharedPtr<FJsonObject> MakeRecursiveStubSchema(const UScriptStruct* Struct) const;` — Builds a terminal inline schema used at recursion boundaries. Avoids $ref so the schema stays consumable by validators without cross-reference support. The stub carries the struct's path in `title` and a human-readable field inventory in `description`.
- L114 _private member_ `TMap<FString, TArray<const UScriptStruct*>> DerivedTypesCache;` — Cache for discovered derived types to avoid repeated reflection queries
- L119 _private member_ `TArray<const UScriptStruct*> ExpansionStack;` — Stack of struct types currently being expanded into the schema. When a struct re-enters expansion (self- or mutually-recursive FInstancedStruct wrappers), the second encounter is replaced with the recursion stub from MakeRecursiveStubSchema.

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset_Assets.h` (Private)


#### struct `FNiagaraExt_ScriptDigest`  
`struct FNiagaraExt_ScriptDigest`  
_L21-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Decoded metadata for a Niagara script asset. Flat record of the asset-registry tags emitted by UNiagaraScript, plus the asset's identity. Filled in by GetNiagaraScriptDigest from a script asset's object path. No LoadObject is performed - the digest is built entirely from registry tags. Empty FString fields indicate the corresponding tag is unset (e.g. no Category text on the script).
- L27 _public member_ `FString ObjectPath;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Full object path: /Path/To/Package.AssetName
- L31 _public member_ `FString PackageName;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Long package name: /Path/To/Package
- L35 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Asset name without package
- L39 _public member_ `ENiagaraScriptUsage Usage = ENiagaraScriptUsage::Module;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Script kind: Module, DynamicInput, Function, or one of the stage scripts
- L43 _public member_ `ENiagaraScriptLibraryVisibility LibraryVisibility = ENiagaraScriptLibraryVisibility::Unexposed;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Library visibility: Unexposed, Library (= "Exposed" in editor UI), or Hidden
- L47 _public member_ `int32 ModuleUsageBitmask = 0;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Bitmask of stack contexts a Module is compatible with. 0 for non-Module scripts.
- L51 _public member_ `FString Category;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Library category text (empty if unset)
- L55 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Library description text (empty if unset)
- L59 _public member_ `FString Keywords;` — `UPROPERTY(EditAnywhere, Category = "Script")` — Library search keywords (empty if unset)
- L63 _public member_ `bool bDeprecated = false;` — `UPROPERTY(EditAnywhere, Category = "Script")` — True if the script is marked deprecated
- L67 _public member_ `bool bSuggested = false;` — `UPROPERTY(EditAnywhere, Category = "Script")` — True if the script is marked suggested

#### struct `FNiagaraToolsetAssetDiscoveryGroup`  
`struct FNiagaraToolsetAssetDiscoveryGroup`  
_L77-88_
- reflection: `USTRUCT(BlueprintType)`
- desc: Asset discovery group defining content directory paths. Groups asset paths by purpose (templates, modules, materials, etc.) with descriptions to guide asset discovery.
- L83 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category="Asset Group")` — Description of what types of assets are in these paths and when to use them
- L87 _public member_ `TArray<FString> Paths;` — `UPROPERTY(EditAnywhere, Category="Asset Group")` — Content directory paths containing assets for this group

#### class `UNiagaraToolset_Assets`  
`class UNiagaraToolset_Assets : public UNiagaraToolset`  
_L106-162_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNiagaraToolset`
- desc: Niagara Toolset for discovery of Niagara script assets. Provides: - GetAssetDiscoveryInfo: project-configured asset discovery groups - FindNiagaraScripts: asset registry search filtered by usage, visibility, name, and module usage bitmask - GetNiagaraScriptDigest: decoded asset-registry tags for a single script All functions read from the asset registry without LoadObject. Pair with NiagaraToolset_System.AddModule to drop discovered modules into a stack. Note: FAssetData JSON serialization does not include the TagsAndValues map (it is not a UPROPERTY), so callers wanting decoded metadata for a result row from FindNiagaraScripts must round-trip through GetNiagaraScriptDigest.
- L119 _public prototype_ `static TArray<FNiagaraToolsetAssetDiscoveryGroup> GetAssetDiscoveryInfo();` — `UFUNCTION(meta = (AICallable), Category = "Assets")` — Returns the project's configured asset discovery groups. Each group describes a content directory's purpose and paths. @return Configured asset discovery groups, or an empty array if none are configured in NiagaraToolsetsSettings.
- L140 _public prototype_ `static TArray<FAssetData> FindNiagaraScripts( FString FolderPath, FString Name, TArray<ENiagaraScriptUsage> Usages, TArray<ENiagaraScriptLibraryVisibility> Visibilities, int32 ModuleUsageBitmask, bool bRecursive, bool bIncludeDeprecated);` — `UFUNCTION(meta = (AICallable), Category = "Assets")` — Searches for UNiagaraScript assets matching the given filters. Reads filterable metadata from asset registry tags only - no LoadObject required. Tags reflect the exposed (published) version of versioned scripts; this function does not need a version filter and there is no way to discover non-exposed versions through the asset registry. @param FolderPath The folder to search within. Pass an empty string to search the entire project. @param Name If non-empty, only return assets whose name contains this substring (case-insensitive). @param Usages If non-empty, only return assets whose Usage matches one of the listed values. Empty array = all usages allowed. @param Visibilities If non-empty, only return assets whose LibraryVisibility matches one of the listed values. Empty array defaults to {Library} (the editor's "Exposed") - explicit override required to surface Unexposed or Hidden scripts. @param ModuleUsageBitmask If non-zero, restricts results to Module scripts whose ModuleUsageBitmask shares at least one bit with this argument (any-match). Non-Module scripts are excluded when this is non-zero. Pass 0 to disable the bitmask gate. @param bRecursive Whether to search subfolders. Ignored when FolderPath is empty (whole-project scan is always exhaustive). @param bIncludeDeprecated If false (default usage), assets whose exposed version has bDeprecated=true are excluded. Pass true only when the caller explicitly wants to surface deprecated assets (e.g. searching for the canonical 
- L161 _public prototype_ `static FNiagaraExt_ScriptDigest GetNiagaraScriptDigest(FString ObjectPath);` — `UFUNCTION(meta = (AICallable), Category = "Assets")` — Returns the decoded asset-registry tag metadata for a Niagara script asset. Looks up the asset by object path in the asset registry and reads its tags; no LoadObject is performed. Returned fields reflect the exposed (published) version when the script uses FVersionedNiagaraScriptData versioning - the registry never carries non-exposed-version metadata. @param ObjectPath Full object path of the script (e.g. "/Niagara/Modules/Spawn/Initialize Particle.Initialize Particle"). @return Decoded digest. If the path is invalid or not a UNiagaraScript, an error is raised and a default-initialized digest is returned.

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset_Blueprint.h` (Private)


#### class `UNiagaraToolset_Blueprint`  
`class UNiagaraToolset_Blueprint : public UNiagaraToolset`  
_L28-84_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNiagaraToolset`
- desc: Niagara Toolset for Niagara and Blueprint integration. Provides utilities for creating Blueprint wrappers around Niagara Systems, making it easier to expose Niagara effects as reusable Blueprint actors. Use this toolset when you need to create Blueprint-based FX actors from Niagara systems.
- L46 _public prototype_ `static UBlueprint* ConstructNiagaraBPWrapperFromSystem(const FString& NewAssetPath, UNiagaraSystem* System, UClass* ParentClass);` — `UFUNCTION(meta = (AICallable), Category = "Util")` — Creates a Blueprint actor wrapper around a Niagara System. This generates a new Blueprint actor with a Niagara component configured to use the specified system. Naming convention: NS_MyEffect -> B_MyEffect @param NewAssetPath Full path for the new Blueprint asset (prefer same directory as System) @param System The Niagara System to wrap in the Blueprint @param ParentClass The parent Actor class for the Blueprint (e.g., AActor) @return The newly created Blueprint actor asset
- L60 _public prototype_ `static UBlueprint* ConstructNiagaraBPWrapperFromComponent(const FString& NewAssetPath, UNiagaraComponent* Component, UClass* ParentClass);` — `UFUNCTION(meta = (AICallable), Category = "Util")` — Creates a Blueprint actor wrapper from a Niagara Component. This generates a new Blueprint actor and preserves all component property values and user variable overrides. Naming convention: NS_MyEffect -> B_MyEffect @param NewAssetPath Full path for the new Blueprint asset (prefer same directory as System) @param Component The Niagara Component with configured properties and overrides to preserve @param ParentClass The parent Actor class for the Blueprint (e.g., AActor) @return The newly created Blueprint actor asset
- L66 _private prototype_ `static UBlueprint* ConstructBPWrapper_Internal(const FString& NewAssetPath, UNiagaraSystem* System, UNiagaraComponent* Component, UClass* ParentClass);` — Internal: Shared logic for Blueprint wrapper construction
- L69 _private prototype_ `static UFunction* GetSetVariablesFunctionForType(const FNiagaraTypeDefinition& TypeDef);` — Internal: Gets the appropriate SetVariable function for a Niagara type
- L72 _private prototype_ `static UBlueprint* CreateNewBPAsset_Internal(const FString& NewAssetPath, UClass* ParentClass);` — Internal: Creates a new Blueprint asset
- L75 _private prototype_ `static UEdGraph* GetConstructionScriptGraph(UBlueprint* BP);` — Internal: Gets the construction script graph from a Blueprint
- L78 _private prototype_ `static UActorComponent* AddComponent_Internal(UBlueprint* BP, TSubclassOf<UActorComponent> ComponentClass, FString ComponentName);` — Internal: Adds a component to a Blueprint
- L81 _private prototype_ `static bool AddVariable_Internal(UBlueprint* Blueprint, FName Name, FEdGraphPinType Type, FString Tooltip, FString DefaultValue);` — Internal: Adds a variable to a Blueprint

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset_Component.h` (Private)


#### class `UNiagaraToolset_Component`  
`class UNiagaraToolset_Component : public UNiagaraToolset`  
_L23-70_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNiagaraToolset`
- desc: Niagara Toolset for Niagara Component operations. Use this toolset when working with: - Niagara Components on actors - Runtime Niagara system manipulation - User variable overrides on component instances - FX-related operations in levels or blueprints This is the primary toolset for runtime Niagara operations.
- L38 _public prototype_ `static void SetSystem(UNiagaraComponent* NiagaraComponent, UNiagaraSystem* System, bool bResetExistingOverrideParameters);` — `UFUNCTION(meta = (AICallable), Category = "Component")` — Sets the Niagara System for a component. Use this instead of setting the Asset property directly to ensure proper initialization. @param NiagaraComponent The Niagara component to set the system on @param System The Niagara system asset to assign to the component @param bResetExistingOverrideParameters If true, reset all user variables to system defaults; if false, preserve matching overrides
- L48 _public prototype_ `static TArray<FNiagaraExt_VariableInst> GetUserVariables(UNiagaraComponent* Component);` — `UFUNCTION(meta = (AICallable), Category = "User Variables")` — Returns all user variable values currently set on the component. This retrieves the current values of all user-exposed parameters that can be overridden at the component level. @param Component The Niagara component to retrieve user variables from @return Array of user variable instances with their current values
- L58 _public prototype_ `static void SetVariable(UNiagaraComponent* Component, FNiagaraExt_VariableInst Variable);` — `UFUNCTION(meta = (AICallable), Category = "User Variables")` — Sets the value of a user variable on the component. This overrides the default value of a user-exposed parameter on a specific component instance. @param Component The Niagara component to set the variable on @param Variable The variable instance containing the name and new value to set
- L69 _public prototype_ `static FNiagaraExt_VariableInst GetVariable(UNiagaraComponent* Component, FNiagaraExt_Variable Var);` — `UFUNCTION(meta = (AICallable), Category = "User Variables")` — Gets the current value of a specific user variable on the component. This retrieves the current value of a user-exposed parameter, including any component-level overrides. @param Component The Niagara component to retrieve the variable from @param Var The variable definition (name and type) to look up @return The variable instance containing the current value

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset_Info.h` (Private)


#### class `UNiagaraToolset_Info`  
`class UNiagaraToolset_Info : public UNiagaraToolset`  
_L25-37_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNiagaraToolset`
- desc: Niagara Toolset for general Niagara information and guidance. Provides: - Enum value lookups - General usage information Call these functions when you need context about Niagara types.
- L36 _public prototype_ `static FString UEnum_Info(UEnum* Enum);` — `UFUNCTION(meta = (AICallable), Category = "")` — Returns information about a UEnum and all its values. ALWAYS call this when working with a UEnum type to see valid values.

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolset_System.h` (Private)


#### class `UNiagaraToolset_AsyncSystemCompileState`  
`class UNiagaraToolset_AsyncSystemCompileState : public UToolCallAsyncResult`  
_L11-24_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- L17 _public function_ `bool SetValue(const FNiagaraExt_SystemCompileState& InValue)` — `UFUNCTION(BlueprintCallable, Category = "NiagaraToolset")`
- L23 _public member_ `FNiagaraExt_SystemCompileState Value;` — `UPROPERTY(BlueprintReadOnly, Category = "NiagaraToolset")`

#### class `UNiagaraToolset_AsyncStackIssues`  
`class UNiagaraToolset_AsyncStackIssues : public UToolCallAsyncResult`  
_L27-40_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- L33 _public function_ `bool SetValue(const FNiagaraExt_StackIssues& InValue)` — `UFUNCTION(BlueprintCallable, Category = "NiagaraToolset")`
- L39 _public member_ `FNiagaraExt_StackIssues Value;` — `UPROPERTY(BlueprintReadOnly, Category = "NiagaraToolset")`

#### struct `FNiagaraToolset_ApplyStackIssueFixResult`  
`struct FNiagaraToolset_ApplyStackIssueFixResult`  
_L43-54_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `FNiagaraExt_ApplyStackIssueFixResult ApplyResult;` — `UPROPERTY(BlueprintReadOnly, Category = "NiagaraToolset")` — Direct outcome of the fix application (bApplied + AppliedFixDescription).
- L53 _public member_ `FNiagaraExt_StackIssues PostFixIssues;` — `UPROPERTY(BlueprintReadOnly, Category = "NiagaraToolset")` — Stack-issue state observed after the fix's compile completed.

#### class `UNiagaraToolset_AsyncApplyStackIssueFixResult`  
`class UNiagaraToolset_AsyncApplyStackIssueFixResult : public UToolCallAsyncResult`  
_L57-70_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- L63 _public function_ `bool SetValue(const FNiagaraToolset_ApplyStackIssueFixResult& InValue)` — `UFUNCTION(BlueprintCallable, Category = "NiagaraToolset")`
- L69 _public member_ `FNiagaraToolset_ApplyStackIssueFixResult Value;` — `UPROPERTY(BlueprintReadOnly, Category = "NiagaraToolset")`

#### class `UNiagaraToolset_System`  
`class UNiagaraToolset_System : public UNiagaraToolset`  
_L87-608_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNiagaraToolset`
- desc: Niagara Toolset for Niagara System operations. Provides comprehensive access to Niagara System editing, including: - System, emitter, and module creation and modification - Schema discovery for understanding structure - Topology and Summary inspection for viewing current configuration - Data access for reading and writing properties - Dependency rollups via GetSystemDependencies - Dynamic-input chain traversal via GetDynamicInputChain This is the primary toolset for working with Niagara Systems in the editor.
- L101 _public prototype_ `static TArray<UNiagaraScript*> GetAvailableDynamicInputs(const FNiagaraTypeDefinition& Type);` — `UFUNCTION(meta = (AICallable), Category = "Assets")` — Returns all available Dynamic Input Module assets compatible with the given type. Dynamic inputs provide procedural value generation for module parameters. @param Type The Niagara type definition to find compatible dynamic inputs for @return Array of dynamic input script assets that can be used with the specified type
- L113 _public prototype_ `static UNiagaraSystem* CreateNiagaraSystem(FString AssetName, FString AssetPath, UNiagaraSystem* TemplateSystem);` — `UFUNCTION(meta = (AICallable), Category = "System")` — Creates a new Niagara System asset. The new system will be based on the template system, inheriting its configuration and emitters. @param AssetName Name of the new asset (without path or extension) @param AssetPath Directory path where the new asset will be created @param TemplateSystem Template system to base the new system on (required) @return The newly created Niagara System asset if successful, nullptr otherwise
- L126 _public prototype_ `static FNiagaraExt_SystemSchema GetSystemSchema();` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns property schema for Niagara System. Describes all available properties and their types that can be set on a Niagara System. @return Schema describing all system-level properties
- L135 _public prototype_ `static FNiagaraExt_EmitterSchema GetEmitterSchema();` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns property schema for Niagara Emitter. Describes all available properties and their types that can be set on a Niagara Emitter. @return Schema describing all emitter-level properties
- L145 _public prototype_ `static FNiagaraExt_RendererSchema GetRendererSchema(TSubclassOf<UNiagaraRendererProperties> RendererClass);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns property schema for a specific Renderer class. Describes all available properties and their types for the given renderer type. @param RendererClass The renderer class to get the schema for (e.g., UNiagaraSpriteRendererProperties) @return Schema describing all properties for the specified renderer class
- L155 _public prototype_ `static FNiagaraExt_DataInterfaceSchema GetDataInterfaceSchema(TSubclassOf<UNiagaraDataInterface> DataInterfaceClass);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns property schema for a specific Data Interface class. Describes all available properties and their types for the given data interface type. @param DataInterfaceClass The data interface class to get the schema for @return Schema describing all properties for the specified data interface class
- L165 _public prototype_ `static FNiagaraExt_StackInputSchema GetStackInputSchema(const FNiagaraExt_StackItemReference& InputReference);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns schema for a single module input in the stack. Describes the type, metadata, and configuration options for a specific input parameter. @param InputReference Reference to the stack input to get the schema for @return Schema describing the input's type and available configuration
- L175 _public prototype_ `static FNiagaraExt_ModuleSchema GetModuleSchema(const FNiagaraExt_StackItemReference& ModuleReference);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns schema for a module and all its inputs. Call this after seeing a module in topology to understand what inputs it exposes. @param ModuleReference Reference to the module to get the schema for @return Schema describing the module's inputs and their types
- L185 _public prototype_ `static FNiagaraExt_DynamicInputSchema GetDynamicInputSchema(const FNiagaraExt_StackItemReference& DynamicInputReference);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns schema for a dynamic input module in the stack. Describes the inputs and configuration for a procedural value generator. @param DynamicInputReference Reference to the dynamic input to get the schema for @return Schema describing the dynamic input's parameters and their types
- L195 _public prototype_ `static FNiagaraExt_ModuleSchema GetModuleSchemaFromAsset(const UNiagaraScript* ModuleAsset);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns schema for a module asset. Standalone function that doesn't require a system context - useful for browsing available modules. @param ModuleAsset The module script asset to get the schema for @return Schema describing the module's inputs and their types
- L205 _public prototype_ `static FNiagaraExt_DynamicInputSchema GetDynamicInputSchemaFromAsset(const UNiagaraScript* DynamicInputAsset);` — `UFUNCTION(meta = (AICallable), Category = "Schema")` — Returns schema for a dynamic input asset. Standalone function that doesn't require a system context - useful for browsing available dynamic inputs. @param DynamicInputAsset The dynamic input script asset to get the schema for @return Schema describing the dynamic input's parameters and their types
- L218 _public prototype_ `static FNiagaraExt_SystemSummary GetSystemSummary(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns lightweight system metadata: name, user variables, and one summary entry per emitter. Use this for first contact with an unfamiliar system. For full structural detail call GetEmitterTopology per emitter. @param System The Niagara System to summarise. @return Summary containing system name, user variables, and per-emitter metadata.
- L228 _public prototype_ `static FNiagaraExt_EmitterSummary GetEmitterSummary(const FNiagaraExt_StackItemReference& EmitterRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns lightweight emitter metadata: name, enabled state, sim target, renderer classes. Use this when you only need to check metadata without walking the full emitter structure. @param EmitterRef Reference to the emitter to summarise. @return Summary containing emitter name, enabled, sim target, de-duplicated renderer classes.
- L247 _public prototype_ `static FNiagaraExt_EmitterTopology GetEmitterTopology(const FNiagaraExt_StackItemReference& EmitterRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns full emitter topology: four script stacks with all modules and inputs, renderer references. All fields always populated. The returned topology carries no input values; call GetEmitterInputValues in parallel. Note: mutation endpoints (AddEmitter, AddModule) also return topology structs — input values require a separate data call. @param EmitterRef Reference to the emitter to describe. @return Emitter topology with all four script stacks and renderer references fully walked.
- L257 _public prototype_ `static FNiagaraExt_ScriptStackTopology GetScriptStackTopology(const FNiagaraExt_StackItemReference& ScriptRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns script stack topology: all modules and their inputs in execution order. All fields always populated. @param ScriptRef Reference to the script stack to describe. @return Script stack topology with all modules and inputs fully walked.
- L267 _public prototype_ `static FNiagaraExt_ModuleTopology GetModuleTopology(const FNiagaraExt_StackItemReference& ModuleRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns module topology: metadata and all inputs (name/type/visibility only, no values). All fields always populated. @param ModuleRef Reference to the module to describe. @return Module topology with all inputs in walk order.
- L277 _public prototype_ `static FNiagaraExt_StackInputTopology GetStackInputTopology(const FNiagaraExt_StackItemReference& StackInputRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns stack input topology: name, type, visibility, editability. No value payload. For the resolved value call GetStackInputData. For a dynamic-input chain call GetDynamicInputChain. @param StackInputRef Reference to the stack input to describe. @return Input topology with structural metadata only.
- L290 _public prototype_ `static FNiagaraExt_UserVariables GetUserVariables(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns all user variables defined on the system. User variables are parameters exposed for external control and can be overridden per component instance. @param System The Niagara System to retrieve user variables from @return Collection of all user variables with their names, types, and default values
- L300 _public prototype_ `static FNiagaraExt_SystemData GetSystemData(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns system property values. Retrieves the current values of all configurable system-level properties. @param System The Niagara System to retrieve data from @return Data structure containing all system property values
- L315 _public prototype_ `static FNiagaraExt_EmitterData GetEmitterData(const FNiagaraExt_StackItemReference& EmitterRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns emitter property values as a single JSON-string blob in PropertyValues. The blob contains the full FVersionedNiagaraEmitterData (SimTarget, bLocalSpace, RandomSeed, FixedBounds, etc.) — fields use C++ PascalCase, must be parsed to read individual values. For typed access to common metadata (SimTarget, EmitterName, bEnabled, RendererClasses) prefer GetEmitterSummary — it returns those as named fields directly and avoids a JSON parse step. Use this endpoint when you need the full property set or a less-common field. @param EmitterRef Reference to the emitter to retrieve data from @return Data structure with PropertyValues set to a JSON blob of all emitter properties
- L325 _public prototype_ `static FNiagaraExt_RendererData GetRendererData(const FNiagaraExt_StackItemReference& RendererRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns renderer property values. Retrieves the current values of all configurable renderer properties. @param RendererRef Reference to the renderer to retrieve data from @return Data structure containing all renderer property values
- L335 _public prototype_ `static FNiagaraExt_StackInputValue GetStackInputData(const FNiagaraExt_StackItemReference& StackInputRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns the value of a stack module input. Retrieves the current value and configuration for a specific module input parameter. @param StackInputRef Reference to the stack input to retrieve data from @return The current value and configuration of the input
- L346 _public prototype_ `static TArray<FNiagaraExt_ModuleInputValues> GetEmitterInputValues(const FNiagaraExt_StackItemReference& EmitterRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns all resolved input values for every module across all four emitter script stacks. One FNiagaraExt_ModuleInputValues entry per module, each carrying all its resolved input values. Call this in parallel with GetEmitterTopology to get both structure and values in two passes. @param EmitterRef Reference to the emitter to retrieve input values from @return Array of per-module input value bundles across all four script stacks
- L356 _public prototype_ `static TArray<FNiagaraExt_ModuleInputValues> GetScriptStackInputValues(const FNiagaraExt_StackItemReference& ScriptRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns all resolved input values for every module in the given script stack. One FNiagaraExt_ModuleInputValues entry per module. @param ScriptRef Reference to the script stack @return Array of per-module input value bundles in execution order
- L366 _public prototype_ `static FNiagaraExt_ModuleInputValues GetModuleInputValues(const FNiagaraExt_StackItemReference& ModuleRef);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns resolved input values for a single module. Use when you need values for one specific module without walking the whole emitter. @param ModuleRef Reference to the module @return Input value bundle for the module
- L381 _public prototype_ `static FNiagaraExt_DynamicInputChainRef GetDynamicInputChain(const FNiagaraExt_StackItemReference& StackInputRef);` — `UFUNCTION(meta = (AICallable), Category = "Topology")` — Returns the full recursive chain for a dynamic input: topology metadata and resolved values at every level. The starting input must have value mode Dynamic; an error is surfaced otherwise. The schema expands one full level and emits a typed recursion stub at deeper levels; the wire format recurses to arbitrary depth matching the underlying chain. @param StackInputRef Reference to the dynamic input to traverse @return Recursive chain of entries, each carrying topology metadata and a resolved Value payload
- L395 _public prototype_ `static FNiagaraExt_SystemDependencies GetSystemDependencies(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Data")` — Returns the four Used* sets (renderers, data interfaces, modules, dynamic inputs) gathered across all emitters and system scripts. These sets are not included in topology structs; call this endpoint separately when needed. @param System The Niagara System to scan @return Dependency rollup with four distinct asset sets
- L408 _public prototype_ `static void SetSystemData(UNiagaraSystem* System, const FNiagaraExt_SystemData& SystemData);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Sets property values on a Niagara System. Applies new values to system-level properties based on the provided data structure. @param System The Niagara System to modify @param SystemData Data structure containing the property values to set
- L418 _public prototype_ `static void SetEmitterData(const FNiagaraExt_StackItemReference& Emitter, const FNiagaraExt_EmitterData& EmitterData);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Sets property values on a Niagara Emitter. Applies new values to emitter-level properties based on the provided data structure. @param Emitter Reference to the emitter to modify @param EmitterData Data structure containing the property values to set
- L430 _public prototype_ `static void SetRendererData(const FNiagaraExt_StackItemReference& Renderer, const FNiagaraExt_RendererData& RendererData);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Sets property values on a Niagara Renderer. Applies new values to renderer properties based on the provided data structure. Payload shape varies with the concrete renderer class; call GetRendererSchema for the renderer's class to inspect valid properties before writing. @param Renderer Reference to the renderer to modify @param RendererData Data structure containing the property values to set
- L440 _public prototype_ `static void AddUserVariables(UNiagaraSystem* System, const TArray<FNiagaraExt_UserVariable>& VariablesToAdd);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds or updates user variables on a system. If a variable with the same name already exists, it will be replaced with the new definition. @param System The Niagara System to add variables to @param VariablesToAdd Array of user variables to add or update
- L450 _public prototype_ `static void RemoveUserVariables(UNiagaraSystem* System, const TArray<FNiagaraExt_Variable>& VariablesToRemove);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Removes user variables from a system. Deletes the specified user variables from the system's user parameter collection. @param System The Niagara System to remove variables from @param VariablesToRemove Array of variable definitions identifying which variables to remove
- L463 _public prototype_ `static FNiagaraExt_EmitterTopology AddEmitter(UNiagaraSystem* System, UNiagaraEmitter* TemplateEmitter, FName EmitterName);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds an emitter to a Niagara System. The new emitter will be based on the template emitter, inheriting its configuration and modules. Returns the full emitter topology (no input values — call GetEmitterInputValues for values). @param System The Niagara System to add the emitter to @param TemplateEmitter The emitter asset to use as a template for the new emitter @param EmitterName Name for the new emitter instance @return Topology of the newly added emitter with all scripts and modules walked
- L472 _public prototype_ `static void RemoveEmitter(const FNiagaraExt_StackItemReference& EmitterToRemove);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Removes an emitter from a system. Deletes the specified emitter and all its associated scripts, modules, and renderers. @param EmitterToRemove Reference to the emitter to remove from the system
- L485 _public prototype_ `static FNiagaraExt_RendererRef AddRenderer(const FNiagaraExt_StackItemReference& NewRendererLocation, const TSubclassOf<UNiagaraRendererProperties> RendererClass);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds a renderer to an emitter. Creates a new renderer of the specified type and adds it to the emitter's renderer list. Returns an FNiagaraExt_RendererRef with the new renderer's Index and RendererClass, usable directly with SetRendererData / GetRendererData without a follow-up topology call. @param NewRendererLocation Reference specifying which emitter to add the renderer to @param RendererClass The class of renderer to create (e.g., UNiagaraSpriteRendererProperties) @return Renderer reference (Index + RendererClass) for the newly added renderer.
- L494 _public prototype_ `static void RemoveRenderer(const FNiagaraExt_StackItemReference& RendererToRemove);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Removes a renderer from an emitter. Deletes the specified renderer from the emitter's renderer list. @param RendererToRemove Reference to the renderer to remove
- L506 _public prototype_ `static FNiagaraExt_ModuleTopology AddModule(const FNiagaraExt_StackItemReference& ModuleLocationRef, const UNiagaraScript* ModuleAsset);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds a module to a script stack. The module will be inserted into the specified script's execution stack. Returns the module topology with all inputs walked (no input values — call GetModuleInputValues for values). @param ModuleLocationRef Reference specifying where to add the module @param ModuleAsset The module script asset to add to the stack @return Topology of the newly added module with all inputs populated
- L515 _public prototype_ `static void RemoveModule(const FNiagaraExt_StackItemReference& ModuleToRemove);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Removes a module from a script stack. Deletes the specified module and all its inputs from the script's execution stack. @param ModuleToRemove Reference to the module to remove from the stack
- L525 _public prototype_ `static void SetModuleEnabled(const FNiagaraExt_StackItemReference& ModuleRef, bool bEnabled);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Sets whether a module is enabled. Disabled modules remain in the stack but don't execute. Current state is visible in module topology. @param ModuleRef Reference to the module to enable or disable @param bEnabled True to enable the module, false to disable it
- L538 _public prototype_ `static FNiagaraExt_ModuleTopology AddSetParametersModule(const FNiagaraExt_StackItemReference& ModuleLocationRef, const TArray<FNiagaraExt_SetParameterEntry>& Parameters);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds a SetParameters module to a script stack. Unlike AddModule which requires a script asset, a SetParameters module dynamically assigns values to named parameters and generates its own internal script. Use this when you need to set one or more particle/emitter/system parameters directly in the stack. @param ModuleLocationRef Reference specifying where to add the module @param Parameters Array of parameter entries, each with a variable (name + type) and an optional default value string @return Topology of the newly added module, including all its inputs
- L550 _public prototype_ `static FNiagaraExt_ModuleTopology AddSetParameterEntry(const FNiagaraExt_StackItemReference& ModuleRef, const FNiagaraExt_SetParameterEntry& Entry);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Adds a single parameter to an existing SetParameters module. The module referenced by ModuleRef must be a SetParameters (UNiagaraNodeAssignment) module. Use bIsSetParametersModule in the module topology to confirm before calling. @param ModuleRef Reference to the existing SetParameters module @param Entry The parameter to add (variable name, type, and optional default value string) @return Updated topology of the module after the parameter is added
- L561 _public prototype_ `static void RemoveSetParameterEntry(const FNiagaraExt_StackItemReference& ModuleRef, FName ParameterName);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Removes a parameter from an existing SetParameters module by name. The module referenced by ModuleRef must be a SetParameters (UNiagaraNodeAssignment) module. Use bIsSetParametersModule in the module topology to confirm before calling. @param ModuleRef Reference to the existing SetParameters module @param ParameterName Name of the parameter to remove
- L572 _public prototype_ `static FNiagaraExt_StackInputValue SetStackInputData(const FNiagaraExt_StackItemReference& StackInputRef, const FNiagaraExt_StackInputValue& InputData);` — `UFUNCTION(meta = (AICallable), Category = "Edit")` — Sets the value of a stack module input and returns the resulting stored value. Updates the value and configuration for a specific module input parameter. @param StackInputRef Reference to the stack input to modify @param InputData The new value and configuration to apply to the input @return The value now stored on the input after the operation
- L584 _public prototype_ `static UNiagaraToolset_AsyncSystemCompileState* GetSystemCompileState(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Status")` — Returns the current compile state of a Niagara System: aggregate status, per-script compile events, and summary flags. Waits for any in-flight compile to complete before collecting. @param System The Niagara System to query. @return Async result whose Value carries aggregate and per-script compile state.
- L593 _public prototype_ `static UNiagaraToolset_AsyncStackIssues* GetStackIssues(UNiagaraSystem* System);` — `UFUNCTION(meta = (AICallable), Category = "Status")` — Returns all stack issues (errors, warnings, info) from the Niagara module stack, including dismissed ones. Waits for any in-flight compile to complete before collecting. @param System The Niagara System to query. @return Async result whose Value carries all stack issues across the system and its emitters.
- L605 _public prototype_ `static UNiagaraToolset_AsyncApplyStackIssueFixResult* ApplyStackIssueFix(UNiagaraSystem* System, FString IssueId, FString FixId);` — `UFUNCTION(meta = (AICallable), Category = "Status")` — Applies a Fix-style stack issue fix identified by IssueId and FixId. Link-style fixes are rejected. The fix is undoable via the editor undo stack. Applying a fix may trigger a recompile; the result waits for that compile to complete so post-fix state is valid. @param System  The Niagara System to apply the fix to. @param IssueId IssueId from a prior FNiagaraExt_StackIssue. @param FixId   FixId from a prior FNiagaraExt_StackIssueFix. @return Async result carrying the fix outcome and a post-fix stack-issues snapshot.

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolsetsCommon.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolsetsModule.h` (Private)


#### class `FNiagaraToolsetsModule`  
`class FNiagaraToolsetsModule : public IModuleInterface`  
_L12-36_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void OnAllModuleLoadingPhasesComplete();` — Called after modules are loaded so we can register with the AI Assistant.
- L26 _private prototype_ `void OnPreExit();` — Called before engine exit so we can unregister with the AI Assistant.
- L28 _private prototype_ `void RegisterToolsets();`
- L29 _private prototype_ `void UnregisterToolsets();`
- L31 _private member_ `bool bToolsetsRegistered = false;`
- L34 _private member_ `TSharedPtr<FToolsetNiagaraInstancedValueConverter> InstancedValueConverter;` — Json Converters
- L35 _private member_ `TSharedPtr<FToolsetNiagaraTypeDefinitionConverter> TypeDefConverter;`

### `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolsetsSettings.h` (Private)


#### class `UNiagaraToolsetsSettings`  
`class UNiagaraToolsetsSettings : public UDeveloperSettings`  
_L12-26_
- reflection: `UCLASS(config = NiagaraToolsets, defaultconfig, meta=(DisplayName="Niagara Toolsets"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L19 _public prototype_ `virtual FName GetCategoryName() const override;`
- L20 _public prototype_ `virtual FText GetSectionText() const override;`
- L25 _public member_ `TArray<FNiagaraToolsetAssetDiscoveryGroup> AssetDiscoveryGroups;` — `UPROPERTY(config, EditAnywhere, Category="Niagara Toolsets")` — Information given to the AI about where it should look for assets when working with Niagara.
