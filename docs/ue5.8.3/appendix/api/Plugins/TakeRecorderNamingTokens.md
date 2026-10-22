# Plugins / TakeRecorderNamingTokens

- module root: `Plugins/VirtualProduction/Takes/Source/TakeRecorderNamingTokens`
- headers: 3; symbols: 12
- symbol kinds: class=2, delegate=1, function=1, member=2, prototype=6
- PrivateDependencyModuleNames: Core, CoreUObject, MovieSceneTools, UnrealEd
- PublicDependencyModuleNames: Engine, NamingTokens, TakeRecorder, TakesCore

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderNamingTokens/Private/TakeRecorderNamingTokens.h` (Private)


#### class `UTakeRecorderNamingTokens`  
`class UTakeRecorderNamingTokens final: public UNamingTokens`  
_L16-40_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UNamingTokens`
- desc: Naming Tokens for Take Recorder.
- L21 _public prototype_ `UTakeRecorderNamingTokens();`
- L26 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L27 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L28 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L29 _protected prototype_ `virtual FDateTime GetCurrentDateTime_Implementation() const override;`
- L35 _private member_ `TWeakObjectPtr<const UTakeMetaData> TakeMetaData;` — `UPROPERTY(Transient)` — Cached metadata for this run.
- L39 _private member_ `TObjectPtr<UTakeRecorderNamingTokensContext> Context;` — `UPROPERTY(Transient)` — Cached context for this run. This isn't available globally and requires a context passed to it.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderNamingTokens/Private/TakeRecorderNamingTokensLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTakeRecorderNamingTokens, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTakeRecorderNamingTokens, Log, All);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderNamingTokens/Public/ITakeRecorderNamingTokensModule.h` (Public)


#### class `ITakeRecorderNamingTokensModule`  
`class ITakeRecorderNamingTokensModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L11 _public function_ `static FString GetTakeRecorderNamespace()` — The Take Recorder namespace used for processing naming tokens.
