# Plugins / CineAssemblyTools

- module root: `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools`
- headers: 6; symbols: 226
- symbol kinds: class=8, delegate=1, enum=3, enumerator=10, macro=2, member=77, prototype=123, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Json, JsonUtilities, MovieScene, MovieSceneTools, MovieSceneTracks, SlateCore, UniversalObjectLocator
- PublicDependencyModuleNames: Engine, LevelSequence, NamingTokens

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/CineAssembly.h` (Public)


#### struct `FAssemblyAssociatedAssetDesc`  
`struct FAssemblyAssociatedAssetDesc`  
_L23-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines an additional asset that should be created alongside an assembly. These definitions are configured by the Schema.
- L29 _public member_ `TSoftClassPtr<UObject> AssetClass;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — The class of asset to create
- L33 _public member_ `FTemplateString AssetName;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — The template name for the associated asset
- L37 _public member_ `FTemplateString RelativePath;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — The path relative to the assembly root where this asset should be created
- L41 _public member_ `TSoftObjectPtr<UObject> TemplateAsset;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — Template asset that will be duplicated when creating an asset for this descriptor. If null, a new asset of type AssetClass will be created.
- L45 _public member_ `TSoftObjectPtr<UObject> CreatedAsset;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — Reference to the asset created from this definition (populated after the asset is created)
- L49 _public member_ `FGuid AssetID;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — Stable identifier for this definition
- L53 _public member_ `FName Label;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — Semantic label for identifying this associated asset
- L57 _public member_ `bool bShouldCreate = true;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Cine Assembly Tools")` — If true, the CineAssembly factory will create an asset for this descriptor. If false, it is skipped.

#### class `UCineAssembly`  
`class UCineAssembly : public ULevelSequence`  
_L64-431_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=Animation)`
- inherits: `ULevelSequence`
- desc: A cinematic building block that associates a level sequence with a level
- L69 _public prototype_ `UCineAssembly();`
- L74 _public prototype_ `virtual bool IsCompatibleAsSubSequence(const UMovieSceneSequence& ParentSequence) const override;`
- L79 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L82 _public prototype_ `virtual void Initialize() override;`
- L89 _public prototype_ `void InitializeFromSchema(UCineAssemblySchema* InSchema, bool bDuplicateMovieScene = true);` — Set the Schema for this Assembly and initialize the MovieScene from the Schema's template sequence. bDuplicateMovieScene determines whether the MovieScene of this Assembly is replaced with a duplicate of the MovieScene from the Schema's TemplateSequence
- L95 _public prototype_ `void InitializeFromTemplate(ULevelSequence * Template, bool bDuplicateMovieScene = true);` — Given a ULevelSequence as a template, initialize this assembly from it. bDuplicateMovieScene determines whether the MovieScene of this Assembly is replaced with a duplicate of the MovieScene on the input Template LevelSequence
- L98 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L99 _public prototype_ `virtual void PostInitProperties() override;`
- L100 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L101 _public prototype_ `virtual void PostLoad() override;`
- L104 _public prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L105 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L112 _public prototype_ `FGuid GetAssemblyGuid() const;` — Get the unique ID of this assembly
- L116 _public prototype_ `const UCineAssemblySchema* GetSchema() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the base schema for this assembly
- L119 _public prototype_ `void SetSchema(UCineAssemblySchema* InSchema);` — Set the base schema for this assembly, only if one is not already set
- L124 _public prototype_ `void CreateSubAssemblies();` — `UE_DEPRECATED(5.8, "SubAssemblies are created automatically when initializing an assembly with a Schema")` — Creates one or more subsequence assets, parented to this assembly, based on the schema
- L128 _public prototype_ `void CreateSubFolders();` — `UE_DEPRECATED(5.8, "Subfolders are created automatically when the Assembly is created through the asset factory")` — Creates the content folders specified by the schema
- L131 _public prototype_ `void ResolveMovieSceneTokens();` — Resolve any tokens in the names of this Assembly's MovieScene folders and tracks
- L136 _public prototype_ `TSoftObjectPtr<UWorld> GetLevel();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the target level associated with this assembly
- L140 _public prototype_ `void SetLevel(TSoftObjectPtr<UWorld> InLevel);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the target level associated with this assembly
- L144 _public prototype_ `FString GetNoteText();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the note text associated with this assembly
- L148 _public prototype_ `void SetNoteText(FString InNote);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the note text associated with this assembly
- L152 _public prototype_ `void AppendToNoteText(FString InNote);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Append to the note text associated with this assembly
- L156 _public prototype_ `FGuid GetProductionID();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the production ID associated with this assembly
- L160 _public prototype_ `FString GetProductionName();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the production name associated with this assembly
- L164 _public prototype_ `TSoftObjectPtr<UCineAssembly> GetParentAssembly();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the parent assembly of this assembly
- L168 _public prototype_ `void SetParentAssembly(TSoftObjectPtr<UCineAssembly> InParent);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the parent assembly of this assembly
- L172 _public prototype_ `FName GetLabel() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the semantic label for this assembly
- L176 _public prototype_ `void SetLabel(FName InLabel);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the semantic label for this assembly
- L180 _public prototype_ `TArray<UCineAssembly*> GetSubAssemblies() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the direct child SubAssemblies of this assembly
- L184 _public prototype_ `TArray<TSoftObjectPtr<UObject>> GetAssociatedAssets() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the list of Associated Assets configured on this assembly
- L188 _public prototype_ `TArray<UCineAssembly*> FindSubAssembliesByLabel(FName InLabel) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the direct child SubAssemblies of this assembly whose Label matches the input
- L192 _public prototype_ `TArray<TSoftObjectPtr<UObject>> FindAssociatedAssetsByLabel(FName InLabel) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the list of Associated Assets configured on this assembly whose Label matches the input
- L197 _public prototype_ `FString GetAuthor() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Gets the author of this assembly
- L201 _public prototype_ `void SetAuthor(const FString& InAuthor);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the author of this assembly
- L205 _public prototype_ `FString GetCreatedString() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Gets the created date-time of this assembly as a localtime formatted string.
- L209 _public prototype_ `FString GetDateCreatedString() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Gets the date this assembly was created as a YYYY-MM-DD string.
- L213 _public prototype_ `FString GetTimeCreatedString() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Gets the 24-hour time of day this assembly was created as a HH:MM:SS string.
- L218 _public prototype_ `FString GetFullMetadataString() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get all of the metadata for this assembly as a formatted JSON string
- L221 _public prototype_ `TArray<FString> GetMetadataKeys() const;` — Get all of the metadata keys for this assembly
- L225 _public prototype_ `void SetMetadataAsString(FString InKey, FString InValue);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add a string as metadata to this assembly
- L229 _public prototype_ `void SetMetadataAsTokenString(FString InKey, FTemplateString InValue);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add a tokenized string as metadata to this assembly
- L233 _public prototype_ `void SetMetadataAsBool(FString InKey, bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add a boolean as metadata to this assembly
- L237 _public prototype_ `void SetMetadataAsInteger(FString InKey, int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add an integer as metadata to this assembly
- L241 _public prototype_ `void SetMetadataAsFloat(FString InKey, float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add a floating point number as metadata to this assembly
- L245 _public prototype_ `bool GetMetadataAsString(FString InKey, FString& OutValue) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta = (ReturnDisplayName = "FoundKey"))` — Get the metadata value for the input key as a string (if it exists)
- L249 _public prototype_ `bool GetMetadataAsTokenString(FString InKey, FTemplateString& OutValue) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta = (ReturnDisplayName = "FoundKey"))` — Get the metadata value for the input key as a token string (if it exists)
- L253 _public prototype_ `bool GetMetadataAsBool(FString InKey, bool& OutValue) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta = (ReturnDisplayName = "FoundKey"))` — Get the metadata value for the input key as a boolean (if it exists)
- L257 _public prototype_ `bool GetMetadataAsInteger(FString InKey, int32& OutValue) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta = (ReturnDisplayName = "FoundKey"))` — Get the metadata value for the input key as an integer (if it exists)
- L261 _public prototype_ `bool GetMetadataAsFloat(FString InKey, float& OutValue) const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta = (ReturnDisplayName = "FoundKey"))` — Get the metadata value for the input key as a floating-point number (if it exists)
- L269 _public prototype_ `void ApplyMetadata(const TMap<FString, FString>& InMetadata);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "InMetadata"))` — Apply a map of metadata key-value pairs to this assembly. Keys matching the schema's AssemblyMetadata are applied with type-awareness based on each field's defined type. Keys not found in the schema are stored as InstanceMetadata.
- L272 _public prototype_ `void AddMetadataNamingToken(const FString& InKey);` — Adds a new metadata key to the list of supported naming tokens for assemblies
- L275 _public prototype_ `void GetAssetPathAndRootFolder(FString& OutAssetPath, FString& OutRootFolder);` — Returns the asset path and its root folder (which might be different if the schema defines a default assembly path)
- L278 _public prototype_ `void RemoveAssociatedAsset(const FGuid& InAssetID);` — Removes an associated asset by its AssetID, and cleans up any MetadataLinks that referenced it
- L281 _public prototype_ `UCineAssembly* FindSubAssembly(const FGuid& InAssemblyID) const;` — Finds a managed SubAssembly whose AssemblyGuid matches the input ID. Returns nullptr if not found.
- L284 _public prototype_ `void ValidateMetadataLinks();` — Removes stale entries from MetadataLinks whose keys or values no longer match any metadata field, associated asset, or SubAssembly section
- L287 _public prototype_ `void DuplicateManagedSubAssemblies();` — Recursively duplicates all managed SubAssemblies, replacing each with a new transient copy
- L293 _public prototype_ `void ConvertSubAssemblyTracks();` — Convert all SubAssembly Tracks found in this Assembly's MovieScene into SubTracks and CinematicShotTracks. A new transient SubAssembly will be created for every template SubAssembly Section that is found.
- L297 _private prototype_ `void ChangeSchema(UCineAssemblySchema* InSchema);` — Sets the base schema for this assembly and re-initializes the metadata inherited from the schema
- L304 _private prototype_ `void InitializeFromSchemaInternal(UCineAssemblySchema* InSchema, TSet<const UCineAssemblySchema*>& SchemaAncestors, bool bDuplicateMovieScene = true);` — Set the Schema for this Assembly and initialize the MovieScene from the Schema's template sequence. If that template sequence had SubAssemblies with template schemas, this will be recursive. Tracks the visited schemas it has seen so far as it goes to detect cycles (A->A, A->B->A) so it can avoid infinite recursion.
- L311 _private prototype_ `void ConvertSubAssemblyTracksInternal(TSet<const UCineAssemblySchema*>& SchemaAncestors);` — Convert all SubAssembly Tracks found in this Assembly's MovieScene into SubTracks and CinematicShotTracks. A new transient SubAssembly will be created for every template SubAssembly Section that is found. Tracks the visited schemas it has seen so far as it goes to detect cycles (A->A, A->B->A) so it can avoid infinite recursion.
- L314 _private prototype_ `void RenameSubAssemblies();` — Assigns meaningful, semantic names to the managed transient SubAssemblies using each SubAssembly's label
- L317 _private prototype_ `UCineAssembly* CreateSubAssemblyFromTemplate(UObject* TemplateObject, TSet<const UCineAssemblySchema*>& SchemaAncestors);` — Creates a transient CineAssembly object using the input object as a template. Threads the visited schemas for cycle detection.
- L320 _private prototype_ `void UpdateInstanceMetadata();` — Update the underlying json object whenever keys/values in the instance metadata map are added/removed/modified
- L323 _private prototype_ `TOptional<FDateTime> TryGetCreatedAsLocalTime() const;` — Get the created FDateTime in local time. If no metadata found, returns an unset optional.
- L327 _private prototype_ `void GetAllMovieSceneFoldersRecursive(UMovieSceneFolder* RootFolder, TArray<UMovieSceneFolder*>& OutFolders);` — Recursively gather the movie scene folders within a root folder
- L333 _public member_ `FTemplateString AssemblyName;` — `UPROPERTY()` — The assembly name, which supports tokens
- L337 _public member_ `FTemplateString PathRelativeToRoot;` — `UPROPERTY()` — The path where this assembly should be created, relative to its content root
- L341 _public member_ `FTemplateString PathRelativeToParent;` — `UPROPERTY()` — The path where this assembly should be created, relative to its parent assembly
- L344 _public member_ `FString SourceAssemblyPath;` — If this assembly is a duplicate of another, this represents the absolute path of the original asset
- L348 _public member_ `TSoftObjectPtr<UCineAssembly> SourceAssembly;` — `UPROPERTY(BlueprintReadOnly, Category = "Cine Assembly Tools")` — If this assembly was duplicated from another, this holds a soft reference to the source.
- L352 _public member_ `FSoftObjectPath Level;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (AllowedClasses = "/Script/Engine.World"))` — The level to open before opening this asset in Sequencer
- L356 _public member_ `TMap<FName, FString> InstanceMetadata;` — `UPROPERTY(EditAnywhere, Category = "Instance Metadata")` — User added metadata key/value pairs, which will be added as additional asset registry tags
- L360 _public member_ `FName Label;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — Semantic label for identifying this assembly
- L364 _public member_ `FString AssemblyNote;` — `UPROPERTY()` — User-facing notes about this assembly asset
- L368 _public member_ `FSoftObjectPath ParentAssembly;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (AllowedClasses = "/Script/CineAssemblyTools.CineAssembly"))` — Reference to another assembly asset that is the parent of this assembly
- L372 _public member_ `FGuid Production;` — `UPROPERTY(EditAnywhere, Category = "Default")` — The ID of the Cinematic Production that this assembly is associated with
- L376 _public member_ `FString ProductionName;` — `UPROPERTY()` — The name of the Cinematic Production that this assembly is associated with
- L380 _public member_ `TArray<FTemplateString> SubAssemblyNames;` — `UPROPERTY()` — Array of template names (possibly containing tokens), based on the schema, used to create the SubAssemblies
- L384 _public member_ `TArray<FTemplateString> DefaultFolderNames;` — `UPROPERTY()` — Array of template names (possibly containing tokens), based on the schema, used to create folders for this assembly
- L388 _public member_ `TArray<FAssemblyAssociatedAssetDesc> AssociatedAssets;` — `UPROPERTY()` — Array of associated asset definitions, used to create additional assets alongside this assembly
- L392 _public member_ `TMap<FString, FGuid> MetadataLinks;` — `UPROPERTY()` — Links metadata keys to AssociatedAssets and SubAssemblies to auto-populate the value of the linked metadata field when the asset is created
- L396 _public member_ `TArray<TObjectPtr<UMovieSceneSubSection>> SubAssemblies;` — `UPROPERTY()` — Array of Subsequence Sections created based on the schema
- L400 _public member_ `bool bIsDataOnly = false;` — `UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, Category="Default", AdvancedDisplay, meta=(DisplayName="Data-Only"))` — Mark this CineAssembly as Data-Only. When Data-Only, opening a CineAssembly opens only it's details.
- L404 _public member_ `bool bShouldCreate = true;` — `UPROPERTY(Transient, BlueprintReadWrite, Category = "Default")` — If true, the CineAssembly factory will create this Assembly. If false, it (and its SubAssemblies and Associated Assets) is skipped.
- L407 _public member_ `static const FName AssetRegistryTag_AssemblyType;` — The asset registry tag that contains the assembly type information
- L410 _public member_ `static const FName AssetRegistryTag_SchemaGuid;` — The asset registry tag that contains the value of the associated Schema ID
- L412 _public member_ `static const FName AssemblyGuidPropertyName;`
- L415 _public prototype_ `static FOnCineAssemblyMetadataChanged& OnAssemblyMetadataChanged();` — Native multicast event fired after a metadata field is added or updated on a CineAssembly.
- L420 _private member_ `FGuid AssemblyGuid;` — `UPROPERTY(AssetRegistrySearchable, meta = (IgnoreForMemberInitializationTest))` — Unique ID for this assembly, assigned at object creation
- L424 _private member_ `TObjectPtr<UCineAssemblySchema> BaseSchema;` — `UPROPERTY()` — The schema that was used as a base when creating this assembly (can be null if no schema was used)
- L427 _private member_ `TArray<FName> InstanceMetadataKeys;` — Copy of the keys present in the InstanceMetadata map, used to keep the json representation consistent with the map contents
- L430 _private member_ `TSharedPtr<FJsonObject> MetadataJsonObject;` — Json object responsible for storing the schema and instance metadata for this assembly

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyMetadataChanged, UCineAssembly*, const FString&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyMetadataChanged, UCineAssembly*, const FString&);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/CineAssemblyMovieSceneDecorations.h` (Public)


#### class `UCineAssemblySchemaContentDecoration`  
`class UCineAssemblySchemaContentDecoration : public UObject`  
_L13-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: MovieScene decoration used to tag Tracks (and, transitively, the bindings those tracks might belong to) that came from a Schema's TemplateSequence

#### class `UCineAssemblyFullRangeDecoration`  
`class UCineAssemblyFullRangeDecoration : public UObject`  
_L22-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: MovieScene decoration used to tag UMovieSceneSubSections whose outer range matches the playback range of the Schema's TemplateSequence

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/CineAssemblyNamingTokens.h` (Public)


#### class `UCineAssemblyNamingTokensContext`  
`class UCineAssemblyNamingTokensContext : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context object that lets callers supply an assembly asset when evaluating tokens
- L18 _public member_ `TWeakObjectPtr<UCineAssembly> Assembly;` — The assembly asset to use when evaluating tokens

#### class `UCineAssemblyNamingTokens`  
`class UCineAssemblyNamingTokens : public UNamingTokens`  
_L23-53_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UNamingTokens`
- desc: Naming Tokens related to Cinematic Assemblies
- L29 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L30 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L31 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L36 _public prototype_ `UCineAssemblyNamingTokens();`
- L38 _public member_ `static FString TokenNamespace;`
- L41 _public prototype_ `static FText GetResolvedText(const FString& InStringToEvaluate, UCineAssembly* InAssembly);` — Utility function that will evaluate the input string with the naming tokens subsystem and return the result evaluated text using the input assembly
- L44 _public prototype_ `void AddMetadataToken(const FString& InTokenKey);` — Adds a metadata token with the same name as the input key which will return the result of value of that metadata if found in the Cine Assembly
- L48 _private prototype_ `FText ExecuteTokenFunc(TFunction<FText(TWeakObjectPtr<UCineAssembly>)> TokenFunc);` — Runs the input Token evaluation function, which takes a Cine Assembly as input and outputs FText
- L52 _private member_ `TObjectPtr<UCineAssemblyNamingTokensContext> Context;` — The current context to use when evaluating tokens

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/CineAssemblySchema.h` (Public)


#### enum `ECineAssemblyMetadataType`  
`enum class ECineAssemblyMetadataType : uint8`  
_L15-23_
- reflection: `UENUM()`
- desc: The types of assembly metadata supported by Cine Assembly Schemas
- L17 _public enumerator_ `String = 0`
- L18 _public enumerator_ `Bool`
- L19 _public enumerator_ `Integer`
- L20 _public enumerator_ `Float`
- L21 _public enumerator_ `AssetPath`
- L22 _public enumerator_ `CineAssembly`

#### struct `FAssemblyMetadataDesc`  
`struct FAssemblyMetadataDesc`  
_L27-53_
- reflection: `USTRUCT()`
- desc: Structure defining a single metadata field that can be associated with an assembly built from this schema, including its type, key, and default value
- L33 _public member_ `ECineAssemblyMetadataType Type = ECineAssemblyMetadataType::String;` — `UPROPERTY(EditAnywhere, Category = "Metadata")` — Metadata type
- L37 _public member_ `FString Key;` — `UPROPERTY(EditAnywhere, Category = "Metadata")` — The key associated with this field
- L41 _public member_ `FSoftClassPath AssetClass;` — `UPROPERTY(EditAnywhere, Category = "Metadata", meta = (AllowAbstract = false, HideViewOptions, EditCondition = "Type == ECineAssemblyMetadataType::AssetPath", EditConditionHides))` — For AssetPath types, the class to restrict the value of this metadata field to
- L45 _public member_ `FSoftObjectPath SchemaType;` — `UPROPERTY(EditAnywhere, Category = "Metadata", meta = (AllowedClasses="/Script/CineAssemblyTools.CineAssemblySchema", EditCondition = "Type == ECineAssemblyMetadataType::CineAssembly", EditConditionHides))` — For CineAssembly types, the schema type to restrict the value of this metadata field to
- L48 _public member_ `TVariant<FString, bool, int32, float> DefaultValue;` — The default value for this metadata field
- L52 _public member_ `bool bEvaluateTokens = false;` — `UPROPERTY(EditAnywhere, Category = "Metadata", meta = (EditCondition = "Type == ECineAssemblyMetadataType::String", EditConditionHides))` — If string field types should be evaluated as template token strings.

#### class `UCineAssemblySchema`  
`class UCineAssemblySchema : public UObject`  
_L59-237_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A template object for building different Cine Assembly types
- L64 _public prototype_ `UCineAssemblySchema();`
- L67 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L68 _public prototype_ `virtual void PostInitProperties() override;`
- L69 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L70 _public prototype_ `virtual void PostLoad() override;`
- L71 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L75 _public prototype_ `FGuid GetSchemaGuid() const;` — Get the unique ID of this schema
- L78 _public prototype_ `FString GetDefaultAssemblyName() const;` — Get the default name for a new Assembly made from this schema
- L82 _public prototype_ `FString GetDefaultAssemblyPath() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the default path (relative to the content root) for assemblies created from this schema
- L86 _public prototype_ `void SetDefaultAssemblyPath(const FString& InPath);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the default path (relative to the content root) for assemblies created from this schema
- L90 _public prototype_ `TSoftObjectPtr<UWorld> GetDefaultLevel() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the default level for assemblies created from this schema
- L94 _public prototype_ `void SetDefaultLevel(TSoftObjectPtr<UWorld> InLevel);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Set the default level for assemblies created from this schema
- L98 _public prototype_ `void ClearDefaultLevel();` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Clear the default level for assemblies created from this schema
- L102 _public prototype_ `TArray<FString> GetDefaultFolders() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Get the list of default folder paths that will be created for assemblies made from this schema
- L109 _public prototype_ `void AddDefaultFolder(const FString& FolderPath);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add a default folder path that will be created for assemblies made from this schema. Also adds all intermediate parent paths (e.g. adding "A/B/C" will add "A", "A/B", and "A/B/C").
- L113 _public prototype_ `bool RemoveDefaultFolder(const FString& FolderPath);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Remove a default folder path and all of its descendant folder paths. Returns true if any folders were found and removed.
- L116 _public prototype_ `bool SupportsRename() const;` — Whether or not this schema can be renamed
- L120 _public prototype_ `void RenameAsset(const FString& InNewName);` — Renames the underlying schema asset
- L124 _public prototype_ `const TArray<FAssemblyMetadataDesc>& GetAssemblyPropertyMetadata() const;` — Returns the list of metadata descriptors for linkable assembly properties
- L127 _public prototype_ `const FAssemblyMetadataDesc* FindMetadataDesc(const FString& InMetadataKey) const;` — Finds the metadata desc matching the input key, searching AssemblyMetadata and AssemblyPropertyMetadata
- L130 _public prototype_ `void ForEachMetadataDesc(TFunctionRef<bool(const FAssemblyMetadataDesc&)> Visitor) const;` — Iterates over each metadata desc in AssemblyMetadata and AssemblyPropertyMetadata
- L136 _public prototype_ `FName MakeUniqueAssemblyLabel(const FString& BaseName) const;` — Returns a unique Label of the form "{BaseName}{N}" for a new SubAssembly template section in this schema's TemplateSequence. Uniqueness is enforced against existing UMovieSceneSubAssemblySection labels in this schema's TemplateSequence.
- L142 _public prototype_ `FName MakeUniqueAssetLabel(const FString& BaseName) const;` — Returns a unique Label of the form "{BaseName}{N}" for a new Associated Asset in this schema's TemplateSequence. Uniqueness is enforced against existing Associated Asset labels in this schema's TemplateSequence.
- L147 _public member_ `FString SchemaName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — The schema name, which will be used by assemblies made from this schema as their "assembly type"
- L151 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — A user-facing text description of this schema
- L155 _public member_ `FString DefaultAssemblyName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — The default name to be use when creating assemblies from this schema
- L159 _public member_ `FSoftObjectPath ParentSchema;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowedClasses = "/Script/CineAssemblyTools.CineAssemblySchema"))` — Restricts assemblies made from this schema to using this Schema when picking a Parent Assembly
- L163 _public member_ `TSoftObjectPtr<UTexture2D> ThumbnailTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (DisplayName = "Thumbnail Image"))` — The thumbnail image to use for this schema and assemblies built from this schema
- L170 _public member_ `FSoftObjectPath DefaultLevel;` — `UPROPERTY(EditAnywhere, Category = "Assembly Defaults", meta = (AllowedClasses = "/Script/Engine.World", EditCondition = "bOverrideDefaultLevel"))` — If checked, the selected override will be used to initialize the Level property for a new Assembly made from this Schema. If unchecked, the default Level for new Assemblies will be the currently open level when the Assembly is created.
- L174 _public member_ `bool bOverrideDefaultLevel = false;` — `UPROPERTY(EditAnywhere, Category = "Assembly Defaults", meta = (InlineEditConditionToggle))` — Whether assemblies created from this schema should use the DefaultLevel
- L178 _public member_ `TArray<FAssemblyMetadataDesc> AssemblyMetadata;` — `UPROPERTY(EditAnywhere, Category = "Metadata")` — List of metadata fields that should be automatically added to assemblies made from this schema
- L182 _public member_ `TObjectPtr<UCineAssembly> TemplateSequence;` — `UPROPERTY(BlueprintReadOnly, Category = "Default")` — Template sequence, owned and managed by the schema, to use when creating the assembly as a starting point.
- L186 _public member_ `bool bIsDataOnly = false;` — `UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, Category = "Default", AdvancedDisplay, meta = (DisplayName = "Data-Only"))` — Mark this Schema as Data-Only. Assemblies made from this Schema will have their Data-Only defaulted to this value.
- L190 _public member_ `bool bIsHidden = false;` — `UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, Category = "Default", AdvancedDisplay, meta = (DisplayName = "Hidden"))` — Hidden schemas will not appear in the UI when creating new Cine Assemblies.
- L193 _public member_ `static const FString DefaultLevelMetadataKey;` — Metadata key identifying the schema's DefaultLevel as a linkable target.
- L196 _public member_ `static const FName AssetRegistryTag_ThumbnailTexture;` — Asset registry tag holding the soft object path of the schema's thumbnail texture, so thumbnail display can resolve without loading the schema.
- L198 _public member_ `static const FName SchemaGuidPropertyName;`
- L204 _protected member_ `TObjectPtr<UTexture2D> ThumbnailImage_DEPRECATED;` — `UE_DEPRECATED(5.8, "ThumbnailImage is deprecated. Use ThumbnailTexture instead (now a soft reference).")` — `UPROPERTY()`
- L208 _protected member_ `TArray<FString> SubsequencesToCreate_DEPRECATED;` — `UE_DEPRECATED(5.8, "Subsequences to create are now represented by the SubAssembly sections of the TemplateSequence.")` — `UPROPERTY()`
- L212 _protected member_ `FSoftObjectPath Template_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use the TemplateSequence owned by the Schema to initialize a new Assembly.")` — `UPROPERTY()`
- L216 _protected member_ `TMap<FString, FSoftObjectPath> SubsequenceTemplates_DEPRECATED;` — `UE_DEPRECATED(5.8, "Subsequence Template objects are now stored in the SubAssembly sections of the TemplateSequence.")` — `UPROPERTY()`
- L220 _protected member_ `FString DefaultAssemblyPath_DEPRECATED;` — `UE_DEPRECATED(5.8, "This property is now managed directly by the TemplateSequence's PathRelativeToRoot property")` — `UPROPERTY()`
- L224 _protected member_ `TArray<FString> FoldersToCreate_DEPRECATED;` — `UE_DEPRECATED(5.8, "This property is now managed directly by the TemplateSequence's DefaultFolderNames property")` — `UPROPERTY()`
- L229 _private member_ `TArray<FAssemblyMetadataDesc> AssemblyPropertyMetadata;` — List of metadata fields that refer to specific Assembly properties
- L233 _private member_ `FGuid SchemaGuid;` — `UPROPERTY(AssetRegistrySearchable, meta = (IgnoreForMemberInitializationTest))` — Unique ID for this schema, assigned at object creation
- L236 _private member_ `bool bSupportsRename = false;` — Whether the schema asset supports renaming

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/MovieSceneSubAssemblySection.h` (Public)


#### enum `ESubAssemblySectionType`  
`enum class ESubAssemblySectionType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- desc: Indicates how a SubAssemblySection will be used
- L17 _public enumerator_ `Reference`
- L18 _public enumerator_ `Template` — Reference,   Section contains a reference to an existing sequence

#### class `UMovieSceneSubAssemblySection`  
`class UMovieSceneSubAssemblySection : public UMovieSceneCinematicShotSection`  
_L26-121_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneCinematicShotSection`
- desc: The UMovieSceneSubAssemblySection is only supported in the Template Assembly of a CineAssemblySchema as a placeholder section. The Track containing this section has a TrackType that indicates which section should be created when creating an Assembly from a Schema Template.
- L31 _public prototype_ `UMovieSceneSubAssemblySection(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `virtual void PostInitProperties() override;`
- L35 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L36 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `FGuid GetSectionID() const;` — Get the unique identifier for this section
- L46 _public prototype_ `const UCineAssemblySchema* GetTemplateSchema() const;` — Returns the schema associated with this section's template. Returns nullptr if no schema can be determined.
- L49 _public prototype_ `bool IsReferenceSection() const;` — Returns true if this section is used as a reference to an existing sequence
- L52 _public prototype_ `bool IsTemplateSection() const;` — Returns true if this section is used as a template to create a new sequence
- L55 _public prototype_ `bool IsSubsequenceSection() const;` — Returns true if this section is a placeholder for a UMovieSceneSubSection
- L58 _public prototype_ `bool IsCinematicShotSection() const;` — Returns true if this section is a placeholder for a UMovieSceneCinematicShotSection
- L62 _public prototype_ `UObject* GetAssemblyTemplate() const;` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Returns the Assembly Template object
- L66 _public prototype_ `void SetAssemblyTemplate(UPARAM(meta = (AllowedClasses = "/Script/LevelSequence.LevelSe` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Sets the Assembly Template and updates the SequenceName to match the new template
- L69 _public prototype_ `FText GetSequenceName() const;` — Get the name to use when creating a new SubAssembly for this section
- L72 _public prototype_ `void SetSequenceName(const FText& InName);` — Set the name to use when creating a new SubAssembly for this section
- L75 _public prototype_ `FString GetSequencePath() const;` — Get the relative path to use when creating a new SubAssembly for this section
- L78 _public prototype_ `void SetSequencePath(const FString& InPath);` — Set the relative path to use when creating a new SubAssembly for this section
- L81 _public prototype_ `void SetDefaultLabel();` — Sets a unique label based on the template assembly name to use when creating a new SubAssembly for this section
- L86 _public member_ `ESubAssemblySectionType SectionType = ESubAssemblySectionType::Reference;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence")` — Indicates whether this section will be used as a reference to an existing sequence or as a template to create a new sequence
- L90 _public member_ `FText NewSequenceName;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools")` — The name that will be used when creating a new sequence for this section. Only applicable to Template sections
- L94 _public member_ `FString NewSequencePath;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools")` — The path (relative to the root assembly's path) where the new sequence asset for this sections should be created
- L101 _public member_ `TMap<FString, FString> MetadataOverrides;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools")` — Metadata key-value pairs, used to override the default values of a SubAssembly created for this section. Keys should match metadata field keys defined by this section's template schema.
- L105 _public member_ `FName Label;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence", meta = (EditCondition = "SectionType == ESubAssemblySectionType::Template", EditConditionHides))` — Semantic label for identifying the SubAssembly created from this section.
- L108 _public member_ `static const FName AssemblyTemplatePropertyName;` — Name of the protected AssemblyTemplate property
- L110 _public member_ `static const FColor ReferenceSectionColorTint;`
- L111 _public member_ `static const FColor TemplateSectionColorTint;`
- L116 _protected member_ `TObjectPtr<UObject> AssemblyTemplate;` — `UPROPERTY(EditAnywhere, Category = "Sequence")` — The object that will be used as a template to create a new sequence in this section. Can be a Level Sequence, Cine Assembly, or Schema
- L120 _protected member_ `FGuid SectionID;` — `UPROPERTY()` — Unique identifier for this section

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CINEASSEMBLYTOOLS_API`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyTools/Public/MovieSceneSubAssemblyTrack.h` (Public)


#### enum `ESubAssemblyTrackType`  
`enum class ESubAssemblyTrackType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- desc: Indicates the underlying track type for which this track is a placeholder
- L17 _public enumerator_ `SubsequenceTrack`
- L18 _public enumerator_ `CinematicShotTrack` — SubsequenceTrack,    This track is a placeholder for a UMovieSceneSubTrack

#### class `UMovieSceneSubAssemblyTrack`  
`class UMovieSceneSubAssemblyTrack : public UMovieSceneSubTrack`  
_L26-57_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneSubTrack`
- desc: The UMovieSceneSubAssemblyTrack is only supported in the Template Assembly of a CineAssemblySchema as a placeholder track. The Track Type indicates which underlying track should be created in place of this track when creating an Assembly from a Schema Template.
- L31 _public prototype_ `UMovieSceneSubAssemblyTrack(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L39 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L44 _public prototype_ `bool IsSubsequenceTrack() const;` — Returns true if this track represents a UMovieSceneSubTrack
- L47 _public prototype_ `bool IsCinematicShotTrack() const;` — Returns true if this track represents a UMovieSceneCinematicShotTrack
- L51 _public prototype_ `FName GetTrackIconBrush() const;` — Get the icon brush for this track, determined by the track type
- L56 _public member_ `ESubAssemblyTrackType TrackType = ESubAssemblyTrackType::CinematicShotTrack;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools")` — Indicates the underlying track type for which this track is a placeholder

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CINEASSEMBLYTOOLS_API`
