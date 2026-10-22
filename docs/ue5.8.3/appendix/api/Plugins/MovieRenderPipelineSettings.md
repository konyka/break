# Plugins / MovieRenderPipelineSettings

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineSettings`
- headers: 4; symbols: 64
- symbol kinds: class=4, function=14, macro=3, member=17, namespace=2, prototype=24
- PrivateDependencyModuleNames: ApplicationCore, AudioMixer, Core, CoreUObject, NonRealtimeAudioRenderer, RHI, RenderCore, Slate, UMG
- PublicDependencyModuleNames: ConsoleVariablesEditor, Engine, LevelSequence, MovieRenderPipelineCore, MovieScene, MovieSceneTracks, OpenColorIO, SlateCore

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineSettings/Public/MoviePipelineBurnInSetting.h` (Public)


#### class `UMoviePipelineBurnInSetting`  
`class UMoviePipelineBurnInSetting : public UMoviePipelineRenderPass`  
_L19-65_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineRenderPass`
- L23 _private function_ `UMoviePipelineBurnInSetting() : BurnInClass(DefaultBurnInWidgetAsset) , bCompositeOntoFinalImage(true)`
- L31 _protected prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;` — UMoviePipelineRenderPass Interface
- L32 _protected prototype_ `virtual void TeardownImpl() override;`
- L33 _protected prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L34 _protected prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L40 _public function_ `virtual FText GetDisplayText() const override`
- L41 _public function_ `virtual FText GetCategoryText() const`
- L43 _public function_ `virtual bool IsValidOnShots() const override`
- L44 _public function_ `virtual bool IsValidOnPrimary() const override`
- L47 _public member_ `FSoftClassPath BurnInClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MetaClass="/Script/MovieRenderPipelineSettings.MoviePipelineBurnInWidget"), Category = "Widget Settings")`
- L51 _public member_ `bool bCompositeOntoFinalImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MetaClass = "/Script/MovieRenderPipelineSettings.MoviePipelineBurnInWidget"), Category = "Widget Settings")` — If true, the Burn In image will be composited into the Final Image pass. Doesn't apply to multi-layer EXR files.
- L54 _private member_ `FIntPoint OutputResolution;`
- L55 _private member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L56 _private member_ `TSharedPtr<SVirtualWindow> VirtualWindow;`
- L59 _private member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient)`
- L62 _private member_ `TArray<TObjectPtr<UMoviePipelineBurnInWidget>> BurnInWidgetInstances;` — `UPROPERTY(Transient)`
- L64 _public member_ `static FString DefaultBurnInWidgetAsset;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINESETTINGS_API`
- L16 _namespace_ `namespace MoviePipeline`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineSettings/Public/MoviePipelineBurnInWidget.h` (Public)


#### class `UMoviePipelineBurnInWidget`  
`class UMoviePipelineBurnInWidget : public UUserWidget`  
_L14-25_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UUserWidget`
- desc: Base class for level sequence burn ins
- L24 _public prototype_ `void OnOutputFrameStarted(UMoviePipeline* ForPipeline);` — `UFUNCTION(BlueprintImplementableEvent)` — Called on the first temporal and first spatial sample of each output frame with the information about the frame being produced. @param	ForPipeline		The pipeline the burn in is for. This will be consistent throughout a burn in widget's life.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINESETTINGS_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineSettings/Public/MoviePipelineConsoleVariableSetting.h` (Public)


#### class `UMoviePipelineConsoleVariableSetting`  
`class UMoviePipelineConsoleVariableSetting : public UMoviePipelineSetting`  
_L18-136_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineSetting`
- L25 _public function_ `virtual FText GetDisplayText() const override`
- L26 _public prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L32 _public prototype_ `FString ResolvePresetValue(const FString& InCVarName) const;` — Returns the value of the given console variable within the presets for this setting. If none of the presets contain this cvar, an empty string is returned.
- L38 _public prototype_ `FString ResolveDisabledValue(const FMoviePipelineConsoleVariableEntry& InEntry) const;` — Returns the value of the console variable if the given entry were to be disabled in this setting. Searches other override cvars first, then presets, and lastly the startup value.
- L41 _public prototype_ `FMoviePipelineConsoleVariableEntry* GetCVarAtIndex(const int32 InIndex);` — Returns the console variable entry at the specified index, else nullptr if the index is invalid.
- L43 _public function_ `virtual bool IsValidOnShots() const override`
- L44 _public function_ `virtual bool IsValidOnPrimary() const override`
- L45 _public prototype_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L46 _public prototype_ `virtual void TeardownForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L47 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L51 _public function_ `virtual int32 GetPriority() const override` — This needs to be higher priority than the Game Override setting so that the values the user specifies for cvars here are the ones actually applied during renders otherwise the Scalability Settings of the Game Override setting can change values away from what the user expects.
- L53 _protected prototype_ `void ApplyCVarSettings(const bool bOverrideValues);`
- L64 _public member_ `TArray<TScriptInterface<IMovieSceneConsoleVariableTrackInterface>> ConsoleVariablePresets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — An array of presets from the Console Variables Editor. The preset cvars will be applied (in the order they are specified) before any of the cvars in "Console Variables". In other words, cvars in "Console Variables" will take precedence over the cvars coming from these presets.
- L72 _public member_ `TArray<FString> StartConsoleCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — An array of console commands to execute when this shot is started. If you need to restore the value after the shot, add a matching entry in the EndConsoleCommands array. Because they are commands and not values we cannot save the preivous value automatically.
- L79 _public member_ `TArray<FString> EndConsoleCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — An array of console commands to execute when this shot is finished. Used to restore changes made by StartConsoleCommands.
- L86 _public prototype_ `TArray<FMoviePipelineConsoleVariableEntry> GetConsoleVariables() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets a copy of all console variable overrides. These are not meant to be changed; use the mutator methods if console variables need to be updated.
- L94 _public prototype_ `bool RemoveConsoleVariable(const FString& Name, const bool bRemoveAllInstances = false);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Removes the console variable override with the specified name. If more than one with the same name exists, the last one will be removed. Returns true if at least one console variable was removed, else false. @param bRemoveAllInstances Remove all console variables overrides with the given name (not just the last one)
- L103 _public prototype_ `bool AddOrUpdateConsoleVariable(const FString& Name, const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a console variable override with the given name and value if one does not already exist. If the console variable with the given name already exists, its value will be updated (the last one will be updated if there are duplicates with the same name). Returns true if the operation was successful, else false. @see AddConsoleVariable()
- L111 _public prototype_ `bool AddConsoleVariable(const FString& Name, const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a console variable override with the given name and value, and will add a duplicate if one with the provided name already exists. Returns true if the operation was successful, else false. @see AddOrUpdateConsoleVariable()
- L119 _public prototype_ `bool UpdateConsoleVariableEnableState(const FString& Name, const bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Updates the enable state of the console variable override with the provided name. If there are duplicate cvars with the same name, the last one with the provided name will be updated. Returns true if the operation was successful, else false.
- L123 _private prototype_ `void MergeInPresetConsoleVariables();` — Merge together preset and override cvars into MergedConsoleVariables. Discards result of a prior merge (if any).
- L130 _private member_ `TArray<FMoviePipelineConsoleVariableEntry> CVars;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName = "Console Variables", DisplayAfter = "ConsoleVariablePresets", ScriptNoExport))` — An array of console variable overrides which are applied during render and reverted after the render completes.
- L132 _private member_ `TArray<float> PreviousConsoleVariableValues;`
- L135 _private member_ `TArray<FMoviePipelineConsoleVariableEntry> MergedConsoleVariables;` — Merged result of preset cvars and override cvars.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineSettings/Public/MoviePipelineWidgetRenderSetting.h` (Public)


#### class `UMoviePipelineWidgetRenderer`  
`class UMoviePipelineWidgetRenderer : public UMoviePipelineRenderPass`  
_L17-54_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineRenderPass`
- L22 _protected function_ `UMoviePipelineWidgetRenderer() : UMoviePipelineRenderPass() , bCompositeOntoFinalImage(true)`
- L29 _protected prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;` — UMoviePipelineRenderPass Interface
- L30 _protected prototype_ `virtual void TeardownImpl() override;`
- L31 _protected prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L32 _protected prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L35 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L40 _public member_ `bool bCompositeOntoFinalImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MetaClass = "/Script/MovieRenderPipelineSettings.MoviePipelineBurnInWidget"), Category = "Widget Settings")` — If true, the widget renderer image will be composited into the Final Image pass. Doesn't apply to multi-layer EXR files.
- L44 _public function_ `virtual FText GetDisplayText() const override`
- L45 _public function_ `virtual FText GetCategoryText() const`
- L47 _public function_ `virtual bool IsValidOnShots() const override`
- L48 _public function_ `virtual bool IsValidOnPrimary() const override`
- L50 _private member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L53 _private member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINESETTINGS_API`
- L14 _namespace_ `namespace MoviePipeline`
