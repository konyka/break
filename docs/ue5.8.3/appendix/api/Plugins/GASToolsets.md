# Plugins / GASToolsets

- module root: `Plugins/Experimental/Toolsets/GASToolsets/Source/GASToolsets`
- headers: 4; symbols: 55
- symbol kinds: class=4, delegate=1, member=26, prototype=17, struct=7
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, Engine, GameplayAbilities, GameplayTags, GameplayTagsEditor, Kismet, KismetCompiler, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/GASToolsets/Source/GASToolsets/Private/AbilitySystemInspectorToolset.h` (Private)


#### struct `FRuntimeAttributeValue`  
`struct FRuntimeAttributeValue`  
_L12-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: The runtime base and current value of a single gameplay attribute.
- L18 _public member_ `FString AttributeName;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The short attribute name (e.g. "Health").
- L22 _public member_ `FString FullName;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The fully-qualified name including the owning set (e.g. "UMyHealthSet.Health").
- L26 _public member_ `FString SetClassName;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The name of the AttributeSet class that owns this attribute (e.g. "UMyHealthSet").
- L30 _public member_ `float BaseValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The permanent base value, unaffected by temporary modifiers.
- L34 _public member_ `float CurrentValue = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The current value after all active modifiers are applied.

#### struct `FActiveEffectInfo`  
`struct FActiveEffectInfo`  
_L39-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: Summarizes a gameplay effect that is currently active on an AbilitySystemComponent.
- L45 _public member_ `FString EffectName;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The name of the GameplayEffect class (e.g. "GE_Burning").
- L49 _public member_ `int32 StackCount = 1;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — Current stack count. 1 for non-stacking effects.
- L53 _public member_ `float TotalDuration = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — Total duration in seconds. -1 means infinite.
- L57 _public member_ `float RemainingDuration = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — Remaining duration in seconds. -1 means infinite.
- L61 _public member_ `TArray<FString> GrantedTags;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — Tags granted to the owner by this effect.

#### struct `FGrantedAbilityInfo`  
`struct FGrantedAbilityInfo`  
_L66-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Summarizes an ability that has been granted to an AbilitySystemComponent.
- L72 _public member_ `FString AbilityName;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The name of the ability class (e.g. "GA_Sprint").
- L76 _public member_ `int32 Level = 1;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — The level at which this ability was granted.
- L80 _public member_ `bool bIsActive = false;` — `UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")` — True if the ability is currently executing (at least one active instance).

#### class `UAbilitySystemInspectorToolset`  
`class UAbilitySystemInspectorToolset : public UToolsetDefinition`  
_L89-134_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for inspecting the runtime state of an AbilitySystemComponent. Each function takes a direct actor pointer and raises a script error if the actor is null or has no AbilitySystemComponent.
- L102 _public prototype_ `static TArray<FRuntimeAttributeValue> GetAttributeValues(AActor* Actor);` — `UFUNCTION(meta = (AICallable), Category = "AbilitySystem")` — Returns the current base and modified values of all gameplay attributes on the actor's AbilitySystemComponent. @param Actor  The target actor. @return A list of attribute values sorted by full name. Raises a script error if Actor is null or has no ASC.
- L112 _public prototype_ `static TArray<FActiveEffectInfo> GetActiveEffects(AActor* Actor);` — `UFUNCTION(meta = (AICallable), Category = "AbilitySystem")` — Returns all gameplay effects currently active on the actor's AbilitySystemComponent. @param Actor  The target actor. @return A list of active effect summaries sorted by effect name. Raises a script error if Actor is null or has no ASC.
- L121 _public prototype_ `static TArray<FGrantedAbilityInfo> GetGrantedAbilities(AActor* Actor);` — `UFUNCTION(meta = (AICallable), Category = "AbilitySystem")` — Returns all abilities granted to the actor's AbilitySystemComponent. @param Actor  The target actor. @return A list of granted ability summaries sorted by ability name. Raises a script error if Actor is null or has no ASC.
- L131 _public prototype_ `static TArray<FString> GetActiveTags(AActor* Actor);` — `UFUNCTION(meta = (AICallable), Category = "AbilitySystem")` — Returns the gameplay tags currently owned by the actor's AbilitySystemComponent (includes loose tags, effect-granted tags, etc.). @param Actor  The target actor. @return A sorted list of gameplay tag name strings. Raises a script error if Actor is null or has no ASC.

### `Plugins/Experimental/Toolsets/GASToolsets/Source/GASToolsets/Private/AttributeSetToolset.h` (Private)


#### struct `FGameplayAttributeInfo`  
`struct FGameplayAttributeInfo`  
_L12-27_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a gameplay attribute belonging to an AttributeSet class.
- L18 _public member_ `FString AttributeName;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The short attribute name (e.g. "Health").
- L22 _public member_ `FString FullName;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The fully-qualified attribute name including the set class (e.g. "UMyHealthSet.Health").
- L26 _public member_ `FString SetClassName;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The name of the AttributeSet class that owns this attribute (e.g. "UMyHealthSet").

#### struct `FAttributeSetClassInfo`  
`struct FAttributeSetClassInfo`  
_L31-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes an AttributeSet subclass found in the project.
- L37 _public member_ `FString ClassName;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The UClass name of the attribute set (e.g. "UMyHealthSet").
- L41 _public member_ `FString AssetPath;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The object path to the Blueprint asset, or empty for native C++ classes.
- L45 _public member_ `TArray<FGameplayAttributeInfo> Attributes;` — `UPROPERTY(BlueprintReadWrite, Category = "AttributeSet")` — The gameplay attributes defined on this set.

#### class `UAttributeSetToolset`  
`class UAttributeSetToolset : public UToolsetDefinition`  
_L50-73_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for discovering AttributeSet classes and their gameplay attributes.
- L61 _public prototype_ `static TArray<FAttributeSetClassInfo> FindAttributeSetClasses();` — `UFUNCTION(meta = (AICallable), Category = "AttributeSets")` — Returns all AttributeSet subclasses found in the project, including their attributes. Covers both native C++ subclasses and Blueprint subclasses discovered via the asset registry. @return A list of attribute set descriptors sorted by class name.
- L70 _public prototype_ `static TArray<FGameplayAttributeInfo> ListAttributes(const FString& ClassName);` — `UFUNCTION(meta = (AICallable), Category = "AttributeSets")` — Returns the gameplay attributes defined on a specific AttributeSet class. @param ClassName The UClass name to look up, e.g. "UMyHealthSet". Raises a script error if the class is not found or is not an AttributeSet subclass. @return A list of attribute descriptors defined on the class.

### `Plugins/Experimental/Toolsets/GASToolsets/Source/GASToolsets/Private/GameplayCueToolset.h` (Private)


#### struct `FGameplayCueInfo`  
`struct FGameplayCueInfo`  
_L12-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a registered gameplay cue and its associated notify asset.
- L18 _public member_ `FString Tag;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The fully-qualified gameplay cue tag (e.g. "GameplayCue.Character.Death").
- L23 _public member_ `FString NotifyAssetPath;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The object path to the associated GameplayCueNotify asset. Empty if no notify has been found for this tag in the asset registry.
- L27 _public member_ `FString NotifyType;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The notify base class: "Static", "Actor", or "None" if no notify is found.

#### struct `FGameplayCueNotifyInfo`  
`struct FGameplayCueNotifyInfo`  
_L32-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a GameplayCueNotify asset found in the project.
- L38 _public member_ `FString CueTag;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The gameplay cue tag this notify responds to.
- L42 _public member_ `FString AssetPath;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The full object path to the asset (e.g. "/Game/Effects/GCN_Death.GCN_Death").
- L46 _public member_ `FString AssetName;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — The asset name without the package path (e.g. "GCN_Death").
- L50 _public member_ `FString NotifyType;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayCue")` — "Static" for UGameplayCueNotify_Static subclasses, "Actor" for AGameplayCueNotify_Actor subclasses.

#### class `UGameplayCueToolset`  
`class UGameplayCueToolset : public UToolsetDefinition`  
_L55-149_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for inspecting, executing, and managing gameplay cues and their notify assets.
- L68 _public prototype_ `static TArray<FString> ListCues(const FString& ParentTag);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Returns gameplay cue tags registered in the project. @param ParentTag If non-empty, only cues descending from this tag are returned. For example, passing "GameplayCue.Character" returns all cues under that namespace. Pass an empty string to return all tags under the "GameplayCue" root. @return A sorted list of fully-qualified gameplay cue tag names.
- L77 _public prototype_ `static FGameplayCueInfo GetCueInfo(const FString& CueTag);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Returns information about a specific gameplay cue, including its notify asset. @param CueTag The fully-qualified gameplay cue tag, e.g. "GameplayCue.Character.Death". @return The cue's notify asset path and type ("Static", "Actor", or "None"). Raises a script error if the tag does not exist.
- L91 _public prototype_ `static bool ExecuteCueOnSelectedActor( const FString& CueTag, float NormalizedMagnitude, FVector Location, FVector Normal);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Executes a gameplay cue non-replicated on the currently selected actor in the editor. Useful for previewing cue effects without network replication. Requires a PIE session or a configured GameplayCueManager to produce visible results. @param CueTag The fully-qualified tag of the cue to execute, e.g. "GameplayCue.Character.Death". @param NormalizedMagnitude A normalized (0.0-1.0) magnitude value passed to the cue. @param Location World-space location parameter passed to the cue. @param Normal World-space direction parameter passed to the cue. @return True if the cue was dispatched. Raises a script error if no actor is selected or the tag does not exist.
- L101 _public prototype_ `static TArray<FGameplayCueNotifyInfo> FindCueNotifyAssets(const FString& ParentTag);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Returns all GameplayCueNotify assets found in the project via the asset registry. @param ParentTag If non-empty, only notifies whose cue tag descends from this tag are returned. Pass an empty string to return all notify assets in the project. @return A list of notify descriptors, sorted by cue tag.
- L115 _public prototype_ `static FString CreateCueNotifyAsset( const FString& CueTag, const FString& PackagePath, const FString& AssetName, bool bIsActor);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Creates a new GameplayCueNotify Blueprint asset at the specified content browser location. This should ONLY be called after getting explicit direction or permission from the user. @param CueTag The gameplay cue tag the notify should respond to. The tag must already exist; create it first with AddCueTag if needed. @param PackagePath The content browser folder for the asset, e.g. "/Game/Effects/Cues". @param AssetName The file name for the new asset, e.g. "GCN_CharacterDeath". @param bIsActor If true, creates a GameplayCueNotify_Actor (spawned actor in the world). If false, creates a GameplayCueNotify_Static (instant effect, no spawned actor). @return The object path of the created asset, or an empty string on failure.
- L128 _public prototype_ `static bool AddCueTag(const FString& CueTag, const FString& Comment);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Adds a new gameplay cue tag to the project. This should ONLY be called after getting explicit direction or permission from the user. @param CueTag The fully-qualified tag to add. Must begin with "GameplayCue." (e.g. "GameplayCue.Character.Death"). @param Comment An optional developer comment describing the cue's purpose. @return True if the tag was added successfully.
- L137 _public prototype_ `static bool RemoveCueTag(const FString& CueTag);` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Removes a gameplay cue tag from the project. This should ONLY be called after getting explicit direction or permission from the user. @param CueTag The fully-qualified cue tag to remove (e.g. "GameplayCue.Character.Death"). @return True if the tag was removed successfully.
- L145 _public prototype_ `static TArray<FString> FindCueTagsWithoutNotifies();` — `UFUNCTION(meta = (AICallable), Category = "GameplayCues")` — Returns gameplay cue tags that have no corresponding GameplayCueNotify asset in the project. Tags without notifies produce no visible effect when triggered at runtime. @return A sorted list of gameplay cue tag names with no associated notify assets.

### `Plugins/Experimental/Toolsets/GASToolsets/Source/GASToolsets/Public/GASToolsets.h` (Public)


#### class `FGASToolsetsModule`  
`class FGASToolsetsModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGASToolsets, Log, Log);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGASToolsets, Log, Log);`
