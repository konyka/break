# Plugins / GameplayTagsToolset

- module root: `Plugins/Experimental/Toolsets/GameplayTagsToolset/Source/GameplayTagsToolset`
- headers: 1; symbols: 11
- symbol kinds: class=1, member=3, prototype=6, struct=1
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, EditorScriptingUtilities, Engine, GameplayTags, GameplayTagsEditor, Kismet, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/GameplayTagsToolset/Source/GameplayTagsToolset/Private/GameplayTagsToolset/GameplayTagsToolset.h` (Private)


#### struct `FGameplayTagInfo`  
`struct FGameplayTagInfo`  
_L13-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes the properties of a gameplay tag.
- L19 _public member_ `FString Comment;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayTag")` — The developer comment describing the tag's purpose.
- L23 _public member_ `FString Source;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayTag")` — The name of the INI source file that defines this tag (e.g. "DefaultGameplayTags.ini").
- L27 _public member_ `TArray<FString> Children;` — `UPROPERTY(BlueprintReadWrite, Category = "GameplayTag")` — The fully-qualified names of this tag's immediate children.

#### class `UGameplayTagsToolset`  
`class UGameplayTagsToolset : public UToolsetDefinition`  
_L32-90_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for reading and managing gameplay tags in the project's GameplayTagsManager.
- L45 _public prototype_ `static TArray<FString> ListTags(const FString& ParentTag);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Returns gameplay tags registered in the project. @param ParentTag If non-empty, only tags that are descendants of this tag are returned. For example, passing "Character.State" returns "Character.State.Dead", "Character.State.Stunned", etc. Pass an empty string to return all tags. @return A sorted list of fully-qualified tag names.
- L54 _public prototype_ `static FGameplayTagInfo GetTagInfo(const FString& TagName);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Returns detailed information about a specific gameplay tag. @param TagName The fully-qualified name of the tag, e.g. "Character.State.Dead". @return The tag's developer comment, source INI file, and immediate children. Raises a script error if the tag does not exist.
- L64 _public prototype_ `static void AddTag(const FString& TagName, const FString& Comment, const FString& TagSource);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Adds a new gameplay tag to the project. This should ONLY be called after getting explicit direction or permission from the user. @param TagName The fully-qualified name of the tag to add, e.g. "Character.State.Dead". @param Comment An optional developer comment describing the tag's purpose. @param TagSource The INI source to add the tag to. Uses the default source if empty.
- L72 _public prototype_ `static void RemoveTag(const FString& TagName);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Removes a gameplay tag from the project. This should ONLY be called after getting explicit direction or permission from the user. @param TagName The fully-qualified name of the tag to remove, e.g. "Character.State.Dead".
- L81 _public prototype_ `static void RenameTag(const FString& OldTagName, const FString& NewTagName);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Renames a gameplay tag, updating all references in the project. This should ONLY be called after getting explicit direction or permission from the user. @param OldTagName The fully-qualified name of the tag to rename. @param NewTagName The new fully-qualified name for the tag.
- L89 _public prototype_ `static TArray<FString> FindReferencersByTag(const FString& TagName);` — `UFUNCTION(meta = (AICallable), Category = "GameplayTags")` — Returns assets that reference a gameplay tag. @param TagName The fully-qualified gameplay tag to search for, e.g. "Character.State.Dead". @return A list of package paths that reference the tag.
