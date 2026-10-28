# Plugins / SemanticSearchEditorIntegrations

- module root: `Plugins/Experimental/SemanticSearch/Source/SemanticSearchEditorIntegrations`
- headers: 4; symbols: 45
- symbol kinds: class=3, function=3, member=13, namespace=10, prototype=15, struct=1
- PrivateDependencyModuleNames: Analytics, ContentBrowser, ContentBrowserData, CoreUObject, Engine, SemanticSearch, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearchEditorIntegrations/Private/ContentBrowser/SearchResultScoreStore.h` (Private)


#### struct `UE::SemanticSearch::ContentBrowser::FAssetScores`  
`struct FAssetScores`  
_L11-18_
- L13 _public member_ `float RRFScore = 0.0f;`
- L14 _public member_ `float VectorDistance = -1.0f;`
- L15 _public member_ `float BM25Score = -1.0f;`
- L16 _public member_ `FString Caption;`
- L17 _public member_ `TArray<FString> Keywords;`

#### class `UE::SemanticSearch::ContentBrowser::FSearchResultScoreStore`  
`class FSearchResultScoreStore`  
_L29-54_
- desc: Game-thread-only score store backing tooltip / badge display for content- browser search results. No synchronization is needed — Slate and the search override callbacks both run on the game thread. Storage is a parallel-array + FHashTable layout instead of TMap so the search pipeline can build the payload on a worker thread (parallel ID writes + FHashTable Add_Concurrent) and hand it off via a single move-assign on GT.
- L32 _public prototype_ `static FSearchResultScoreStore& Get();`
- L34 _public prototype_ `void Set(TArray<int64>&& InEntryIDs, TArray<FAssetScores>&& InEntryScores, FHashTable&& InIDHashTable);`
- L35 _public prototype_ `void Clear();`
- L45 _public prototype_ `void UpdateMetadata(int64 AssetID, FString&& Caption, TArray<FString>&& Keywords);` — Update the cached caption / keywords for an indexed asset. No-op if the ID is absent (e.g. the store was cleared by a newer search mid-fetch). @param AssetID   Asset identifier to update. @param Caption   New caption text. Moved into the store. @param Keywords  New keyword list. Moved into the store.
- L47 _public prototype_ `const FAssetScores* Find(int64 AssetID) const;`
- L48 _public function_ `int32 Num() const`
- L51 _private member_ `TArray<int64> EntryIDs;`
- L52 _private member_ `TArray<FAssetScores> EntryScores;`
- L53 _private member_ `FHashTable IDHashTable;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L8 _namespace_ `namespace ContentBrowser` (scope `UE::SemanticSearch`)
- L56 _prototype_ `void RegisterScoreBadgeGenerator();` (scope `UE::SemanticSearch::ContentBrowser`)
- L57 _prototype_ `void UnregisterScoreBadgeGenerator();` (scope `UE::SemanticSearch::ContentBrowser`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearchEditorIntegrations/Private/Widgets/SSemanticSearchIndexDialog.h` (Private)


#### class `UE::SemanticSearch::SSemanticSearchIndexDialog`  
`class SSemanticSearchIndexDialog : public SCompoundWidget`  
_L14-36_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SSemanticSearchIndexDialog)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `~SSemanticSearchIndexDialog();`
- L24 _public prototype_ `static void Open();` — Open the dialog as a standalone window.
- L27 _private prototype_ `void RefreshStats();`
- L28 _private prototype_ `void ShowThrobber();`
- L29 _private prototype_ `void OnIndexChanged(bool bSuccess);`
- L31 _private member_ `FSemanticSearchIndexStats CachedStats;`
- L32 _private member_ `TSharedPtr<SVerticalBox> StatsBox;`
- L33 _private member_ `TSharedPtr<SVerticalBox> ThrobberBox;`
- L34 _private member_ `TSharedPtr<STextBlock> StatusText;`
- L35 _private member_ `FDelegateHandle IndexChangedHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearchEditorIntegrations/Public/ContentBrowser/SemanticSearchCB.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace ContentBrowser` (scope `UE::SemanticSearch`)
- L9 _prototype_ `void RegisterContentBrowserExtension();` (scope `UE::SemanticSearch::ContentBrowser`)
- L10 _prototype_ `void UnregisterContentBrowserExtension();` (scope `UE::SemanticSearch::ContentBrowser`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearchEditorIntegrations/Public/ISemanticSearchEditorIntegrationsModule.h` (Public)


#### class `UE::SemanticSearch::ISemanticSearchEditorIntegrationsModule`  
`class ISemanticSearchEditorIntegrationsModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L13 _public function_ `static ISemanticSearchEditorIntegrationsModule& Get()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SemanticSearch` (scope `UE`)
