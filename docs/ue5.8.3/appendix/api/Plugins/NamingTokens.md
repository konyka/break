# Plugins / NamingTokens

- module root: `Plugins/Developer/NamingTokens/Source/NamingTokens`
- headers: 11; symbols: 167
- symbol kinds: class=5, delegate=5, function=14, macro=4, member=38, namespace=10, prototype=85, struct=5, variable=1
- PrivateDependencyModuleNames: CoreUObject, UnrealEd
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Private/NamingTokensLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNamingTokens, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNamingTokens, Log, All);`

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Private/NamingTokensModule.h` (Private)


#### class `FNamingTokensModule`  
`class FNamingTokensModule : public INamingTokensModule`  
_L7-16_
- inherits: `INamingTokensModule`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private prototype_ `void OnPostEngineInit();`

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Private/Utils/NamingTokenUtilsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NamingTokens` (scope `UE`)
- L10 _namespace_ `namespace Utils` (scope `UE::NamingTokens`)
- L10 _namespace_ `namespace Private` (scope `UE::NamingTokens::Utils`)
- L13 _prototype_ `void ForEachNamingTokensBlueprint(const TFunction<void(const FAssetData& AssetData, const FTopLevelAssetPath& ClassObjectPath)>& Function);` (scope `UE::NamingTokens::Utils::Private`) — Iterate each Naming Tokens blueprint asset, executing a function for each qualifying asset.
- L16 _prototype_ `FString NormalizeTokenString(const FString& InTokenString);` (scope `UE::NamingTokens::Utils::Private`) — Preprocess a string removing any spaces within braces.
- L19 _prototype_ `FString SanitizeTokenOrNamespace(const FString& InString);` (scope `UE::NamingTokens::Utils::Private`) — Remove spaces from within tokens or namespaces.
- L22 _prototype_ `FString GetTokenPatternString();` (scope `UE::NamingTokens::Utils::Private`) — Retrieve the token regex.

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/GlobalNamingTokens.h` (Public)


#### class `UGlobalNamingTokens`  
`class UGlobalNamingTokens : public UNamingTokens`  
_L15-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- desc: Default global tokens accessed project wide.
- L20 _public prototype_ `UGlobalNamingTokens();`
- L22 _public function_ `static const FString& GetGlobalNamespace()`
- L26 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;` — Define any default tokens.
- L30 _private member_ `static FString GlobalNamespace;` — The global namespace to register this naming token as.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NAMINGTOKENS_API`

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/INamingTokensModule.h` (Public)


#### class `INamingTokensModule`  
`class INamingTokensModule : public IModuleInterface`  
_L7-26_
- inherits: `IModuleInterface`
- L15 _private function_ `static INamingTokensModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L25 _private function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/NamingTokenData.h` (Public)


#### struct `FNamingTokenValueData`  
`struct FNamingTokenValueData`  
_L15-31_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `FString TokenKey;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — The token key.
- L24 _public member_ `FString TokenNamespace;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — The namespace of the token key.
- L27 _public member_ `FText TokenValue;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — The evaluated token text.
- L30 _public member_ `bool bWasEvaluated = false;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — If the token was able to be evaluated.

#### struct `FNamingTokenResultData`  
`struct FNamingTokenResultData`  
_L35-48_
- reflection: `USTRUCT(BlueprintType)`
- desc: Evaluated results from a template file string.
- L41 _public member_ `FText OriginalText;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — Original text without any modifications.
- L44 _public member_ `FText EvaluatedText;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — The full text with evaluated tokens.
- L47 _public member_ `TArray<FNamingTokenValueData> TokenValues;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — The result of individual tokens, in the order they appear in OriginalText.

#### struct `FNamingTokenData`  
`struct FNamingTokenData`  
_L51-99_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public prototype_ `FNamingTokenData() = default;`
- L58 _public prototype_ `DECLARE_DELEGATE_RetVal(FText, FTokenProcessorDelegateNative);`
- L60 _public prototype_ `explicit FNamingTokenData(const FString& InTokenKey);`
- L61 _public prototype_ `FNamingTokenData(const FString& InTokenKey, const FText& InTokenDisplayName, const FTokenProcessorDelegateNative& InTokenProcessor);`
- L62 _public prototype_ `FNamingTokenData(const FString& InTokenKey, const FText& InTokenDisplayName, const FText& InTokenDescription, const FTokenProcessorDelegateNative& InTokenProcessor);`
- L72 _public member_ `FString TokenKey;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NamingTokens")` — The key of the token to use. This is what the text must match in order to be evaluated. Brackets are automatically added and do not need to be included. @note Must contain alphanumeric and '_' characters only and cannot be empty.
- L76 _public member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NamingTokens")` — The friendly display name of the token.
- L80 _public member_ `FText Description;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NamingTokens")` — A description of the token.
- L84 _public member_ `FName FunctionName;` — `UPROPERTY(EditAnywhere, Category = "NamingTokens", meta = (NoResetToDefault))` — The function to use to evaluate the token. Only needed for blueprint implementations.
- L87 _public member_ `FTokenProcessorDelegateNative TokenProcessorNative;` — The native delegate to execute to evaluate the function. If FunctionName is set then this is not used.
- L89 _public prototype_ `bool operator==(const FNamingTokenData& Other) const;`
- L92 _public prototype_ `bool Equals(const FNamingTokenData& Other, bool bCaseSensitive = true) const;` — Checks for equality dependent on case sensitivity.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NAMINGTOKENS_API`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FTokenProcessorDelegateNative);`
- L94 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FNamingTokenData& Item)`

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/NamingTokens.h` (Public)


#### class `UNamingTokens`  
`class UNamingTokens : public UObject`  
_L17-223_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UObject`
- desc: Subclass to define naming tokens to use for a specific tool or project.
- L22 _public prototype_ `UNamingTokens();`
- L24 _public prototype_ `virtual void PostInitProperties() override;`
- L25 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L28 _public prototype_ `void Validate() const;` — Validate internal values including namespace and token keys.
- L31 _public prototype_ `void CreateDefaultTokens();` — Create any default tokens.
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `void EvaluateTestToken();` — Evaluate the test token input.
- L41 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens);` — Define any default tokens.
- L45 _public prototype_ `FNamingTokenResultData EvaluateTokenText(const FText& InTokenText, const TArray<UObject*>& InContexts = {});` — Evaluate token text. Creates EvaluationData.
- L48 _public prototype_ `FNamingTokenResultData EvaluateTokenText(const FText& InTokenText, const FNamingTokensEvaluationData& InEvaluationData);` — Evaluate token text for a given EvaluationData.
- L51 _public prototype_ `FString GetFormattedTokensStringForDisplay() const;` — Creates a friendly display string of all tokens.
- L54 _public prototype_ `const TArray<FNamingTokenData>& GetDefaultTokens() const;` — Retrieve the default tokens.
- L57 _public prototype_ `const TArray<FNamingTokenData>& GetCustomTokens() const;` — Retrieve the custom tokens.
- L67 _public prototype_ `TArray<FNamingTokenData>& RegisterExternalTokens(FGuid& OutGuid);` — Register an external token array which is managed from a caller. This is transient data. To retrieve the array, call GetExternalTokensChecked and pass in the Guid. @param OutGuid The new guid these tokens are registered under. @return A reference to the token array. This reference may be invalidated if another array is registered.
- L74 _public prototype_ `void UnregisterExternalTokens(const FGuid& InGuid);` — Unregister and clear out external tokens. @param InGuid The guid to unregister.
- L82 _public prototype_ `bool AreExternalTokensRegistered(const FGuid& InGuid) const;` — Check if external tokens are registered for a guid. @param InGuid The guid which was registered for these external tokens. @return True if the tokens are registered, false if they are not registered.
- L90 _public prototype_ `TArray<FNamingTokenData>& GetExternalTokensChecked(const FGuid& InGuid);` — Retrieve the external tokens. Tokens must be registered and exist. @param InGuid The guid which was registered for these external tokens. @return A reference to the token array. This reference may be invalidated if another array is registered.
- L93 _public prototype_ `TArray<FNamingTokenData> GetAllTokens() const;` — Retrieve all tokens.
- L96 _public function_ `const FString& GetNamespace() const` — Retrieve the naming token's namespace.
- L98 _public function_ `static FName GetNamespacePropertyName()` — The name of the namespace property.
- L100 _public function_ `static FName GetIsPrivateNamespacePropertyName()` — The name of IsPrivateNamespace property.
- L103 _public function_ `const FText& GetNamespaceDisplayName() const` — Retrieve the namespace's friendly display name.
- L106 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreEvaluate, const FNamingTokensEvaluationData& InEvaluationData);` — Delegate when pre evaluate is called.
- L107 _public function_ `FOnPreEvaluate& GetOnPreEvaluateEvent()`
- L109 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEvaluate, const FNamingTokenResultData& InResultData);` — Delegate when post evaluate is called.
- L110 _public function_ `FOnPostEvaluate& GetOnPostEvaluateEvent()`
- L114 _public prototype_ `FDateTime GetCurrentDateTime() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "NamingTokens")` — Retrieve the current datetime. By default, this uses shared data so results are consistent across runs.
- L118 _public prototype_ `bool IsPrivateNamespace() const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — If this namespace is private.
- L121 _protected prototype_ `virtual FDateTime GetCurrentDateTime_Implementation() const;`
- L124 _public function_ `static FName GetProcessTokenTemplateFunctionName()`
- L126 _public function_ `static FName GetOnPreEvaluateFunctionName()`
- L127 _public function_ `static FName GetOnPostEvaluateFunctionName()`
- L132 _private function_ `FText ProcessTokenTemplateFunction()` — `UFUNCTION()` — Template function for us to dynamically create subclass graphs from matching this signature.
- L140 _protected prototype_ `void PreEvaluate(const FNamingTokensEvaluationData& InEvaluationData);` — Called prior to token evaluation. @param InEvaluationData Shared information across namespaces.
- L145 _protected prototype_ `void PostEvaluate(const FNamingTokenResultData& InResultData);` — Called after all tokens have evaluated.
- L156 _protected prototype_ `void OnPreEvaluate(const FNamingTokensEvaluationData& InEvaluationData);` — `UFUNCTION(BlueprintNativeEvent, Category = "NamingTokens")` — Called prior to evaluation. Allows consistent data to be set up for each token evaluation. This is important if the data is temporally sensitive and could change between evaluating multiple tokens in a string, such as a high resolution timer. @param InEvaluationData Contains generic shared data for this evaluation.
- L157 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData);`
- L161 _protected prototype_ `void OnPostEvaluate();` — `UFUNCTION(BlueprintNativeEvent, Category = "NamingTokens")` — Called after evaluation. Used so any cleanup can occur.
- L162 _protected prototype_ `virtual void OnPostEvaluate_Implementation();`
- L166 _private member_ `FOnPreEvaluate OnPreEvaluateEvent;` — Delegate when pre evaluate is called.
- L168 _private member_ `FOnPostEvaluate OnPostEvaluateEvent;` — Delegate when post evaluate is called.
- L171 _private prototype_ `FText ProcessToken(const FNamingTokenData& InToken, const FString& InUserProvidedNamespace, const FString& InUserTokenString, FText& InOutFormattedText);` — Process a token if is defined and return evaluated text.
- L174 _private prototype_ `UFunction* FindBlueprintFunctionForToken(const FNamingTokenData& InTokenData) const;` — Return a blueprint function for a token processor if it exists.
- L178 _private member_ `TArray<FNamingTokenData> DefaultTokens;` — The default tokens defined by this class.
- L181 _private member_ `TMap<FGuid, TArray<FNamingTokenData>> ExternalTokens;` — External and temporary instance tokens which can be filled in by tools supporting unrecognized tokens.
- L186 _protected member_ `TArray<FNamingTokenData> CustomTokens;` — `UPROPERTY(EditDefaultsOnly, Category = "NamingTokens", meta = (TitleProperty="TokenKey"))` — User defined tokens.
- L190 _protected member_ `FNamingTokensEvaluationData CurrentEvaluationData;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — Cached shared data for this evaluation.
- L198 _protected member_ `FString Namespace;` — `UPROPERTY(EditDefaultsOnly, AssetRegistrySearchable, Category = "NamingTokens")` — The namespace to identify this token. @note Must contain alphanumeric and '_' characters only and cannot be empty.
- L204 _protected member_ `FText NamespaceDisplayName;` — `UPROPERTY(EditDefaultsOnly, AssetRegistrySearchable, Category = "NamingTokens")` — The full display name of the namespace to use in UI and filtering.
- L211 _protected member_ `bool bIsPrivateNamespace = false;` — `UPROPERTY(AdvancedDisplay, EditDefaultsOnly, AssetRegistrySearchable, Category = "NamingTokens")` — If the namespace is considered private. This prevents this namespace from being gathered for display or processing unless explicitly specified.
- L217 _private member_ `FText TestTokenInput;` — `UPROPERTY(EditDefaultsOnly, Transient, Category = "NamingTokens")` — Enter a sample string using your tokens to output an evaluated result to TestTokenResult.
- L221 _private member_ `FText TestTokenResult;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category = "NamingTokens")` — An evaluated text result of your token data.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NAMINGTOKENS_API`
- L106 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreEvaluate, const FNamingTokensEvaluationData& InEvaluationData);` — Delegate when pre evaluate is called.
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEvaluate, const FNamingTokenResultData& InResultData);` — Delegate when post evaluate is called.

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/NamingTokensEngineSubsystem.h` (Public)


#### struct `FNamingTokenFilterArgs`  
`struct FNamingTokenFilterArgs`  
_L18-47_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `TArray<FString> AdditionalNamespacesToInclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — Namespaces to always be included during evaluation. Namespaces added here won't require the 'namespace' string prefixed to tokens. This does not filter out any namespaces.
- L31 _public member_ `bool bIncludeGlobal = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — Include global namespaces.
- L35 _public member_ `bool bForceCaseSensitive = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — When false, we fall back to case-insensitive if an exact match isn't found.
- L39 _public member_ `bool bNativeOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — When false, we additionally look for blueprint naming tokens.
- L46 _public member_ `bool bNormalizeInput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — If input data should be normalized first, such as removing white spaces in tokens. A better user experience typing in tokens, but may impact localization data.

#### class `UNamingTokensEngineSubsystem`  
`class UNamingTokensEngineSubsystem : public UEngineSubsystem`  
_L53-198_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: An editor subsystem for registering global tokens and evaluating strings across the entire project.
- L58 _public prototype_ `UNamingTokensEngineSubsystem();`
- L69 _public prototype_ `UNamingTokens* GetNamingTokens(const FString& InNamespace) const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Lookup naming tokens given a namespace. This will look first in cached naming tokens, then native classes, then blueprint classes. Call ClearCachedNamingTokens to reset the cache and force a full lookup. @param InNamespace The namespace of the tokens. @return The found Naming Tokens object, or nullptr.
- L80 _public prototype_ `UNamingTokens* GetNamingTokensNative(const FString& InNamespace) const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Lookup naming tokens given a namespace. This will look first in cached naming tokens, then native classes. Call ClearCachedNamingTokens to reset the cache and force a full lookup. @param InNamespace The namespace of the tokens. @return The found Naming Tokens object, or nullptr.
- L89 _public prototype_ `TArray<UNamingTokens*> GetMultipleNamingTokens(const TArray<FString>& InNamespaces) const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Lookup multiple naming tokens from multiple namespaces. @param InNamespaces An array of all token namespaces. @return An array of matching tokens objects.
- L101 _public prototype_ `FNamingTokenResultData EvaluateTokenText(const FText& InTokenText, const FNamingTokenFilterArgs& InFilter, const TArray<UObject*>& InContexts);` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens", meta = (AutoCreateRefTerm = "InFilter,InContexts"))` — Parse and evaluate token text. @param InTokenText The text containing unprocessed tokens. @param InFilter [Optional] Filter to determine which namespaces to use. @param InContexts [Optional] Context objects to pass to naming tokens. @return The result of the evaluation.
- L102 _public prototype_ `FNamingTokenResultData EvaluateTokenText(const FText& InTokenText, const FNamingTokenFilterArgs& InFilter = FNamingTokenFilterArgs());`
- L114 _public prototype_ `FNamingTokenResultData EvaluateTokenString(const FString& InTokenString, const FNamingTokenFilterArgs& InFilter, const TArray<UObject*>& InContexts);` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens", meta = (AutoCreateRefTerm = "InFilter,InContexts"))` — Parse and evaluate token string. @param InTokenString The string containing unprocessed tokens. @param InFilter [Optional] Filter to determine which namespaces to use. @param InContexts [Optional] Context objects to pass to naming tokens. @return The result of the evaluation.
- L115 _public prototype_ `FNamingTokenResultData EvaluateTokenString(const FString& InTokenString, const FNamingTokenFilterArgs& InFilter = FNamingTokenFilterArgs());`
- L127 _public prototype_ `TArray<FNamingTokenValueData> EvaluateTokenList(const TArray<FString>& InTokenList, const FNamingTokenFilterArgs& InFilter, const TArray<UObject*>& InContexts);` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens", meta = (AutoCreateRefTerm = "InFilter,InContexts"))` — Given a list of tokens, return a list of all found tokens and their values. @param InTokenList A list of raw tokens. Tokens can include their namespace, but do not include brackets. @param InFilter [Optional] Filter to determine which namespaces to use. @param InContexts [Optional] Context objects to pass to naming tokens. @return Evaluation data for each token.
- L128 _public prototype_ `TArray<FNamingTokenValueData> EvaluateTokenList(const TArray<FString>& InTokenList, const FNamingTokenFilterArgs& InFilter = FNamingTokenFilterArgs());`
- L135 _public prototype_ `void RegisterGlobalNamespace(const FString& InNamespace);` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Register tokens as a global namespace. This prevents the need to include the namespace in a token string. @param InNamespace The namespace of the tokens to register.
- L142 _public prototype_ `void UnregisterGlobalNamespace(const FString& InNamespace);` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Remove tokens from a global namespace. @param InNamespace The namespace of the tokens to unregister.
- L146 _public prototype_ `bool IsGlobalNamespaceRegistered(const FString& InNamespace) const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Checks if a namespace is registered globally.
- L150 _public prototype_ `TArray<FString> GetGlobalNamespaces() const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Retrieve the registered global namespaces.
- L154 _public prototype_ `TArray<FString> GetAllNamespaces(bool bIncludePrivateNamespaces = false) const;` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Retrieve all discovered namespaces.
- L157 _public prototype_ `void RegisterNamespaceFilter(const FName OwnerName, FFilterNamespace Delegate);` — Register a delegate to filter the list of namespaces that can be used to evaluate tokens
- L160 _public prototype_ `void UnregisterNamespaceFilter(const FName OwnerName);` — Remove a delegate from the list of namespace filters
- L163 _public prototype_ `TSet<FString> GetNamingTokenNamespacesFromString(const FString& InTokenString, const FNamingTokenFilterArgs& InFilter = FNamingTokenFilterArgs()) const;` — Locate all reference naming token namespaces from a given string.
- L166 _public prototype_ `FString GetFormattedTokensStringForDisplay(const FNamingTokenFilterArgs& InFilter) const;` — Creates a friendly display string of all tokens.
- L173 _public prototype_ `void ClearCachedNamingTokens();` — `UFUNCTION(BlueprintCallable, Category = "NamingTokens")` — Clears all currently cached naming tokens. They will be loaded on demand when required. This can avoid an editor restart if a namespace is adjusted on a BP asset, and you don't want the old namespace to access it.
- L176 _public prototype_ `bool IsCacheEnabled() const;` — If the cache is currently enabled.
- L179 _public prototype_ `void SetCacheEnabled(bool bEnabled);` — Configure whether the cache is enabled or not.
- L184 _private member_ `mutable TMap<FString, TObjectPtr<UNamingTokens>> CachedNamingTokens;` — `UPROPERTY(Transient)` — Naming tokens currently loaded from assets.
- L185 _private member_ `mutable FCriticalSection CachedNamingTokensMutex;`
- L187 _private prototype_ `UNamingTokens* LoadNamingToken(const TSoftClassPtr<UNamingTokens>& InTokensClass, const FString& InNamespace) const;`
- L188 _private prototype_ `UNamingTokens* GetNamingTokenFromCache(const FString& InNamespace, bool bNativeOnly = false) const;`
- L191 _private member_ `TSet<FString> GlobalNamespaces;` — Namespaces considered global (don't need to include namespace to access).
- L194 _private member_ `TMap<FName, FFilterNamespace> FilterNamespaceDelegates;` — Filters that will execute just before evaluating a token string
- L197 _private member_ `bool bIsCacheEnabled;` — If the cache is currently enabled.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NAMINGTOKENS_API`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FFilterNamespace, TSet<FString>& );`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FFilterNamespace, TSet<FString>& );`

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/NamingTokensEvaluationData.h` (Public)


#### struct `FNamingTokensEvaluationData`  
`struct FNamingTokensEvaluationData`  
_L14-37_
- reflection: `USTRUCT(BlueprintType)`
- desc: Shared data across token evaluation.
- L19 _public prototype_ `FNamingTokensEvaluationData();`
- L22 _public prototype_ `void Initialize();` — Initialize any constant data that isn't safe to do so in the ctor, like DateTime.
- L26 _public member_ `FDateTime CurrentDateTime;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens", meta = (IgnoreForMemberInitializationTest))` — The current date time.
- L30 _public member_ `TArray<TObjectPtr<UObject>> Contexts;` — `UPROPERTY(BlueprintReadOnly, Category = "NamingTokens")` — An optional array of context objects for this evaluation.
- L33 _public member_ `bool bForceCaseSensitive = false;` — If case sensitivity should be enforced.
- L36 _public member_ `bool bNormalizeInput = true;` — If input data should be normalized first.

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/NamingTokensSpecifiers.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NamingTokens` (scope `UE`)
- L7 _namespace_ `namespace Specifiers` (scope `UE::NamingTokens`)
- L10 _variable_ `const FString UseNamingTokens = TEXT("Nam` (scope `UE::NamingTokens::Specifiers`) — Specifier indicating naming tokens should be used.

### `Plugins/Developer/NamingTokens/Source/NamingTokens/Public/Utils/NamingTokenUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NamingTokens` (scope `UE`)
- L9 _namespace_ `namespace Utils` (scope `UE::NamingTokens`)
- L12 _prototype_ `UFunction* GetProcessTokenFunctionSignature();` (scope `UE::NamingTokens::Utils`) — Return the signature function all blueprint token processing should use.
- L15 _prototype_ `bool ValidateTokenFunction(const UFunction* InFunction);` (scope `UE::NamingTokens::Utils`) — Validate that a token function can be used for token processing.
- L18 _prototype_ `FString CreateFormattedToken(const FNamingTokenData& InToken);` (scope `UE::NamingTokens::Utils`) — Formats a token key into {key}.
- L21 _prototype_ `FString GetNamespaceDelimiter();` (scope `UE::NamingTokens::Utils`) — Retrieve the delimiter for the namespace.
- L28 _prototype_ `TArray<FString> GetTokenKeysFromString(const FString& InTokenString, bool bNormalizeString=true);` (scope `UE::NamingTokens::Utils`) — Extract all token keys from a string. @param InTokenString The string to process. @param bNormalizeString If the string should be normalized first, stripping any whitespace within braces.
- L31 _prototype_ `bool IsTokenInString(const FString& InTokenKey, const FString& InTokenString);` (scope `UE::NamingTokens::Utils`) — Checks if a token is present in a string.
- L38 _prototype_ `FString GetNamespaceFromTokenKey(const FString& InTokenKey);` (scope `UE::NamingTokens::Utils`) — Return the namespace from a token key, or an empty string. @param InTokenKey The token key shouldn't have any additional formatting beyond the namespace, eg "namespace:token" @return The namespace, or an empty string.
- L45 _prototype_ `FString RemoveNamespaceFromTokenKey(const FString& InTokenKey);` (scope `UE::NamingTokens::Utils`) — Remove the namespace from the given token key. @param InTokenKey The token key shouldn't have any additional formatting beyond the namespace, eg "namespace:token" @return The token key without the namespace, or the InTokenKey if there was no namespace.
- L53 _prototype_ `FString CombineNamespaceAndTokenKey(const FString& InNamespace, const FString& InTokenKey);` (scope `UE::NamingTokens::Utils`) — Combine the namespace and token key using the delimiter. @param InNamespace The namespace. If empty no combination is performed. @param InTokenKey The token key. @return The combined key.
- L56 _prototype_ `bool ValidateName(const FString& InName, FText& OutErrorMessage);` (scope `UE::NamingTokens::Utils`) — Validates a name used for a token key or namespace.
