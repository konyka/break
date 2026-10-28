# Plugins / SemanticSearchToolset

- module root: `Plugins/Experimental/Toolsets/SemanticSearchToolset/Source/SemanticSearchToolset`
- headers: 3; symbols: 16
- symbol kinds: class=2, function=2, member=4, namespace=2, prototype=5, struct=1
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, Engine, Json, SemanticSearch, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/SemanticSearchToolset/Source/SemanticSearchToolset/Private/SemanticSearchAsyncResult.h` (Private)


#### class `USemanticSearchAsyncResult`  
`class USemanticSearchAsyncResult : public UToolCallAsyncResult`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UToolCallAsyncResult`
- desc: Async tool call result that completes with an array of FSemanticSearchResult.
- L18 _public function_ `bool SetValue(const TArray<FSemanticSearchResult>& InValue)` — `UFUNCTION()`
- L23 _public function_ `bool SetValue(TArray<FSemanticSearchResult>&& InValue)`
- L29 _public member_ `TArray<FSemanticSearchResult> Value;` — `UPROPERTY()`

### `Plugins/Experimental/Toolsets/SemanticSearchToolset/Source/SemanticSearchToolset/Private/SemanticSearchFilter.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SemanticSearchToolset` (scope `UE`)
- L18 _prototype_ `int32 ExpandClassFilter( const TArray<UClass*>& ClassFilter, const TSet<FName>& SupportedClassNames, TSet<FName>& OutAllowedShortNames);` (scope `UE::SemanticSearchToolset`) — Resolve user-provided short class names to the set of concrete class short names whose assets should be considered, including subclasses. @return number of ClassFilter entries that could not be resolved (unknown name, empty string, or resolved to a class that isn't in SupportedClassNames). Caller may log this.
- L26 _prototype_ `bool MatchesPathRegex( const FString& SoftObjectPath, const TArray<FRegexPattern>& CompiledPatterns);` (scope `UE::SemanticSearchToolset`) — Returns true if SoftObjectPath matches any of the precompiled regex patterns. An empty list accepts any path.
- L33 _prototype_ `int32 CompileRegexPatterns( const TArray<FString>& RegexStrings, TArray<FRegexPattern>& OutPatterns);` (scope `UE::SemanticSearchToolset`) — Compile the given regex strings. Invalid patterns are skipped (not added to the output). Returns the number of patterns that failed to compile.

### `Plugins/Experimental/Toolsets/SemanticSearchToolset/Source/SemanticSearchToolset/Private/SemanticSearchToolset.h` (Private)


#### struct `FSemanticSearchResult`  
`struct FSemanticSearchResult`  
_L14-29_
- reflection: `USTRUCT()`
- desc: A single hit from a semantic search over the Content Browser's indexed assets.
- L20 _public member_ `FSoftObjectPath Path;` — `UPROPERTY()` — Full asset path, e.g. "/Game/Blueprints/BP_Foo.BP_Foo".
- L24 _public member_ `TObjectPtr<UClass> Class;` — `UPROPERTY()` — Class of the asset
- L28 _public member_ `FString Caption;` — `UPROPERTY()` — Caption produced at index time by the SemanticSearch plugin.

#### class `USemanticSearchToolset`  
`class USemanticSearchToolset : public UToolsetDefinition`  
_L36-80_
- reflection: `UCLASS()`
- inherits: `UToolsetDefinition`
- desc: Toolset exposing the SemanticSearch plugin's hybrid vector + BM25 asset search to the AI Toolset Registry.
- L56 _public prototype_ `static USemanticSearchAsyncResult* Search( const FString& Query, const TArray<UClass*>& ClassFilter, const TArray<FString>& PathRegexes, int32 K = 10);` — `UFUNCTION(meta = (AICallable), Category = "SemanticSearch")` — Run a semantic search over the Content Browser assets indexed by the SemanticSearch plugin. @param Query        Natural-language query. Must be non-empty. @param ClassFilter  If non-empty, array of classes to filter by (provide full ref path of the class). Passing a base class covers all its subclasses. The SemanticSearch index currently covers these base classes: Blueprint, StaticMesh, SkeletalMesh, Texture, Material, MaterialInstance. Pass an empty array to consider all indexed classes. @param PathRegexes  If non-empty, only assets whose soft object path matches at least one of these regular expressions are considered (e.g. "^/Game/Blueprints/.*"). Pass an empty array to consider all indexed paths. @param K            Maximum number of results to return. Must be >= 1. Defaults to 10. @return             Array of FSemanticSearchResult sorted by relevance (highest Score first)
- L75 _public prototype_ `static USemanticSearchAsyncResult* FindSimilar( const FSoftObjectPath& AssetPath, const TArray<UClass*>& ClassFilter, const TArray<FString>& PathRegexes, int32 K = 10);` — `UFUNCTION(meta = (AICallable), Category = "SemanticSearch")` — Find assets whose embeddings are semantically similar to the given asset's embedding. Vector-only (no BM25). The source asset must already be indexed by the SemanticSearch plugin. @param AssetPath    SoftObjectPath of the reference asset. @param ClassFilter  Same semantics as Search::ClassFilter. See Search for the list of currently-indexed base classes. Pass an empty array for no class filter. @param PathRegexes  Same semantics as Search::PathRegexes. Pass an empty array for no path filter. @param K            Maximum number of results to return. Must be >= 1. Defaults to 10. @return             Array of FSemanticSearchResult sorted by relevance (highest Score first)
