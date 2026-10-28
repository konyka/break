# Plugins / ConsoleVariablesEditorRuntime

- module root: `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditorRuntime`
- headers: 3; symbols: 28
- symbol kinds: class=2, delegate=1, function=4, macro=1, member=5, prototype=14, struct=1
- PrivateDependencyModuleNames: CoreUObject, SlateCore
- PublicDependencyModuleNames: Core, Engine, MovieSceneTracks

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditorRuntime/Private/ConsoleVariablesEditorRuntimeModule.h` (Private)


#### class `FConsoleVariablesEditorRuntimeModule`  
`class FConsoleVariablesEditorRuntimeModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `FConsoleVariablesEditorRuntimeModule();`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditorRuntime/Public/ConsoleVariablesAsset.h` (Public)


#### struct `FConsoleVariablesEditorAssetSaveData`  
`struct FConsoleVariablesEditorAssetSaveData`  
_L15-33_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data that will be serialized with this asset
- L19 _public function_ `FORCEINLINE bool operator==(const FConsoleVariablesEditorAssetSaveData& Comparator) const`
- L25 _public member_ `FString CommandName;` — `UPROPERTY()`
- L28 _public member_ `FString CommandValueAsString;` — `UPROPERTY()`
- L32 _public member_ `ECheckBoxState CheckedState = ECheckBoxState::Undetermined;` — If Undetermined, we can assume this data was not previously saved

#### class `UConsoleVariablesAsset`  
`class UConsoleVariablesAsset : public UObject, public IMovieSceneConsoleVariableTrackInterface`  
_L37-124_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovieSceneConsoleVariableTrackInterface`
- desc: An asset used to track collections of console variables that can be recalled and edited using the Console Variables Editor.
- L44 _public prototype_ `void SetVariableCollectionDescription(const FString& InVariableCollectionDescription);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Editor")` — Sets a description for this variable collection.
- L47 _public function_ `FString GetVariableCollectionDescription() const` — `UFUNCTION(BlueprintPure, Category = "Console Variables Editor")`
- L54 _public function_ `const TArray<FConsoleVariablesEditorAssetSaveData>& GetSavedCommands() const` — `UFUNCTION(BlueprintPure, Category="Console Variables Asset")` — Returns the saved list of console variable information such as the variable name, the type and the value of the variable at the time the asset was saved.
- L63 _public prototype_ `TArray<FString> GetSavedCommandsAsStringArray(bool bOnlyIncludeChecked = false) const;` — `UFUNCTION(BlueprintPure, Category="Console Variables Asset")` — Returns the saved list of console variables as an array of FString. @param bOnlyIncludeChecked If true, only commands and variables with a Checked checkstate in the Console Variables Editor UI will be included. Otherwise, all will be included.
- L69 _public prototype_ `FString GetSavedCommandsAsCommaSeparatedString(bool bOnlyIncludeChecked = false) const;` — `UFUNCTION(BlueprintPure, Category="Console Variables Asset")` — Returns the saved list of console variables as a concatenated comma-separated string. Useful for passing commands and variables to a command line. @param bOnlyIncludeChecked If true, only commands and variables with a Checked checkstate in the Console Variables Editor UI will be included. Otherwise, all will be included.
- L75 _public prototype_ `void ExecuteSavedCommands(UObject* WorldContextObject, bool bOnlyIncludeChecked = false) const;` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset", meta=(WorldContext="WorldContextObject"))` — Executes all saved commands in this asset, optionally only including those with a Checked checkstate in the UI. @param bOnlyIncludeChecked If true, only commands and variables with a Checked checkstate in the Console Variables Editor UI will be included. Otherwise, all will be included.
- L79 _public prototype_ `void ReplaceSavedCommands(const TArray<FConsoleVariablesEditorAssetSaveData>& Replacement);` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset")` — Completely replaces the saved data with new saved data
- L83 _public function_ `int32 GetSavedCommandsCount() const` — `UFUNCTION(BlueprintPure, Category="Console Variables Asset")` — Returns how many console variables are serialized in this asset
- L90 _public prototype_ `bool FindSavedDataByCommandString( const FString& InCommandString, FConsoleVariablesEditorAssetSaveData& OutValue, const ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const;` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset")` — Outputs the FConsoleVariablesEditorAssetSaveData matching InCommand. Returns whether a match was found. Case sensitive.
- L95 _public prototype_ `void AddOrSetConsoleObjectSavedData(const FConsoleVariablesEditorAssetSaveData& InData);` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset")` — Set the value of a saved console variable if the name matches; add a new console variable to the list if a match is not found.
- L99 _public prototype_ `bool RemoveConsoleVariable(const FString& InCommandString);` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset")` — Returns true if the element was found and successfully removed.
- L103 _public prototype_ `void CopyFrom(const UConsoleVariablesAsset* InAssetToCopy);` — `UFUNCTION(BlueprintCallable, Category="Console Variables Asset")` — Copy list of variables from input asset to this asset
- L107 _public prototype_ `void AddFrom(const UConsoleVariablesAsset* InAssetToCopy);` — `UFUNCTION(BlueprintCallable, Category = "Console Variables Asset")` — Add list of variables from input asset to this asset's list
- L112 _private prototype_ `virtual void GetConsoleVariablesForTrack(bool bOnlyIncludeChecked, TArray<TPair<FString, FString>>& OutVariables) override;`
- L113 _private prototype_ `virtual bool IsConsoleVariableEnabled(const FString& ConsoleVariableName) override;`
- L119 _private member_ `FString VariableCollectionDescription;` — `UPROPERTY(AssetRegistrySearchable, BlueprintGetter = "GetVariableCollectionDescription", EditAnywhere, Category = "Console Variables Editor")` — User defined description of the variable collection
- L123 _private member_ `TArray<FConsoleVariablesEditorAssetSaveData> SavedCommands;` — `UPROPERTY()` — A saved list of console variable information such as the variable name, the type and the value of the variable at the time the asset was saved.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONSOLEVARIABLESEDITORRUNTIME_API`

### `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditorRuntime/Public/ConsoleVariablesEditorRuntimeLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogConsoleVariablesEditorRuntime, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogConsoleVariablesEditorRuntime, Log, All);`
