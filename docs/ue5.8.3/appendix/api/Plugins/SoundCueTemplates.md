# Plugins / SoundCueTemplates

- module root: `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates`
- headers: 5; symbols: 68
- symbol kinds: class=7, enum=1, enumerator=3, function=7, macro=1, member=15, prototype=31, struct=3
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueContainer.h` (Public)


#### enum `ESoundContainerType`  
`enum class ESoundContainerType : uint8`  
_L35-40_
- reflection: `UENUM()`
- L37 _public enumerator_ `Concatenate`
- L38 _public enumerator_ `Randomize`
- L39 _public enumerator_ `Mix`

#### class `USoundCueContainer`  
`class USoundCueContainer : public USoundCueTemplate`  
_L43-73_
- reflection: `UCLASS(MinimalAPI, hidecategories = object, BlueprintType)`
- inherits: `USoundCueTemplate`
- L50 _public member_ `ESoundContainerType ContainerType;` — `UPROPERTY(EditAnywhere, Category = "Variation")`
- L53 _public member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, Category = "Variation")`
- L56 _public member_ `TSet<TObjectPtr<USoundWave>> Variations;` — `UPROPERTY(EditAnywhere, Category = "Variation")`
- L59 _public member_ `FVector2D PitchModulation;` — `UPROPERTY(EditAnywhere, Category = "Modulation")`
- L62 _public member_ `FVector2D VolumeModulation;` — `UPROPERTY(EditAnywhere, Category = "Modulation")`
- L67 _public prototype_ `static TSet<FName>& GetCategoryAllowList();` — List of categories to allow showing on the inherited SoundCue.
- L68 _public prototype_ `virtual void OnRebuildGraph(USoundCue& SoundCue) const override;`
- L71 _private prototype_ `int32 GetMaxVariations(const FSoundCueTemplateQualitySettings& QualitySettings) const;`

#### class `FSoundCueContainerDetailCustomization`  
`class FSoundCueContainerDetailCustomization : public IDetailCustomization`  
_L76-83_
- inherits: `IDetailCustomization`
- L79 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L80 _public prototype_ `static void Register(FPropertyEditorModule& PropertyModule);`
- L81 _public prototype_ `static void Unregister(FPropertyEditorModule& PropertyModule);`
- L82 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueDistanceCrossfade.h` (Public)


#### struct `FSoundCueCrossfadeInfo`  
`struct FSoundCueCrossfadeInfo`  
_L25-34_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `FDistanceDatum DistanceInfo;` — `UPROPERTY(EditAnywhere, Category = "Crossfade Info")`
- L33 _public member_ `TObjectPtr<USoundWave> Sound = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Crossfade Info")`

#### class `USoundCueDistanceCrossfade`  
`class USoundCueDistanceCrossfade : public USoundCueTemplate`  
_L37-59_
- reflection: `UCLASS(MinimalAPI, hidecategories = object, BlueprintType)`
- inherits: `USoundCueTemplate`
- L44 _public member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, Category = "Wave Parameters")`
- L47 _public member_ `TArray<FSoundCueCrossfadeInfo> Variations;` — `UPROPERTY(EditAnywhere, Category = "Wave Parameters")`
- L52 _public prototype_ `static TSet<FName>& GetCategoryAllowList();` — List of categories to allow showing on the inherited SoundCue.
- L57 _public prototype_ `virtual void OnRebuildGraph(USoundCue& SoundCue) const override;` — Overload with logic to rebuild the node graph when user-facing properties are changed

#### class `FSoundCueDistanceCrossfadeDetailCustomization`  
`class FSoundCueDistanceCrossfadeDetailCustomization : public IDetailCustomization`  
_L62-68_
- inherits: `IDetailCustomization`
- L65 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L66 _public prototype_ `static void Register(FPropertyEditorModule& PropertyModule);`
- L67 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueTemplate.h` (Public)


#### class `USoundCueTemplate`  
`class USoundCueTemplate : public USoundCue`  
_L18-176_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `USoundCue`
- desc: Base Sound Cue Template class, which builds the sound node graph procedurally and hides more complex Sound Cue functionality to streamline implementation defined in child classes.
- L23 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _public prototype_ `void RebuildGraph(USoundCue& SoundCue) const;` — Rebuilds the graph when user-facing properties are changed
- L30 _public function_ `virtual void AddSoundWaves(TArray<TWeakObjectPtr<USoundWave>>& Waves)` — Override to initialize a template with array of sound waves from SoundCueFactory
- L33 _public function_ `virtual void LoadTemplateDefaultSettings()` — Override to load template default settings from SoundCueTemplateFactory
- L36 _public function_ `virtual FString GenerateDefaultNewAssetName(const TArray<TWeakObjectPtr<USoundWave>>& Waves) const` — Override to provide a default new asset name prefix from SoundCueTemplateFactory
- L39 _public prototype_ `void AddSoundWavesToTemplate(const TArray<UObject*>& SelectedObjects);` — `UFUNCTION(BlueprintCallable, Category = Config)`
- L47 _protected prototype_ `virtual void OnRebuildGraph(USoundCue& SoundCue) const PURE_VIRTUAL(, );` — Function to override that uses internal editor-data only properties to re-build node graph of provided SoundCue.  Provided SoundCue may be a reference to this SoundCue or one to be copied from this template's graph-building schema.
- L52 _protected prototype_ `static float GetNodeWidthOffset();` — Node width offset between nodes in the SoundCueEditor.
- L57 _protected prototype_ `static float GetInitialWidthOffset();` — Initial width offset of first node in the SoundCueEditor.
- L62 _protected prototype_ `static float GetNodeHeightOffset();` — Node height offset between nodes in the SoundCueEditor.
- L67 _protected prototype_ `static float GetInitialHeightOffset();` — Initial height offset of first node in the SoundCueEditor.
- L72 _protected function_ `static void SetSoundNodePosition(USoundNode& InNode, int32 Column, int32 Row)` — Sets the provided node's position to the location on the template's grid
- L90 _protected function_ `template <class T> static T& ConstructSoundNodeChild(USoundCue& SoundCue, USoundNode* InParentNode, int32 Column, int32 Row, int32 InputPinIndex = -1, const FText* InputPinDisplayName = nullptr)` — Utility function that returns newly constructed sound node that has been added to provided SoundCue's Node Graph. SoundCue				- SoundCue to insert the constructed node into. InParentNode			- If not null, Node to set as parent of constructed child. Column				- (Optional) If positive, sets visual column of node in built graph as displayed in the SoundCueEditor.  Columns are indexed as positive to the left from the root (index 0).  Can be viewed when using the 'Copy To SoundCue' action of the given template. Row					- (Optional) If positive, sets visual row of node in built graph as displayed in the SoundCueEditor.  Columns are indexed as positive descending from the root (index 0). Can be viewed when using the 'Copy To SoundCue' action of the given template. InputPinIndex		- (Optional) If InParentNode set, supplies index of input pin to connect newly constructed ChildNode to. InputPinDisplayName	- (Optional) Name to set the targeted input pin to.
- L110 _protected function_ `template <class T> static T& ConstructSoundNodeRoot(USoundCue& SoundCue)` — Constructs initial root sound node of template. Function will fail if SoundCue already contains a root/first node. SoundCue	- Parent of initial node to construct.
- L130 _protected function_ `static void AddSoundNodeChild(USoundNode& InParentNode, USoundNode& InChildNode, int32 InputPinIndex, const FText* InputPinDisplayName = nullptr)` — Utility function that adds a provided child node to a parent node's list of children. InParentNode			- Node to set as parent of provided child. InChildNode			- Node to set as child of provided parent. InputPinIndex		- Index of input pin to connect newly constructed ChildNode to. InputPinDisplayName	- (Optional) Name to set the targeted input pin to.

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueTemplateSettings.h` (Public)


#### struct `FSoundCueTemplateQualitySettingsNotifier`  
`struct FSoundCueTemplateQualitySettingsNotifier`  
_L11-15_
- L13 _public prototype_ `void PostQualitySettingsUpdated() const;`
- L14 _public prototype_ `void OnAudioSettingsChanged() const;`

#### struct `FSoundCueTemplateQualitySettings`  
`struct FSoundCueTemplateQualitySettings`  
_L18-38_
- reflection: `USTRUCT()`
- L23 _public member_ `FText DisplayName;` — `UPROPERTY(VisibleAnywhere, Category = "Quality")`
- L27 _public member_ `int32 MaxConcatenatedVariations;` — `UPROPERTY(EditAnywhere, Category = "Quality", meta = (ClampMin = "1"))` — The max number of variations to include for the given quality in a SoundCueContainer set to 'Concatenate'.
- L31 _public member_ `int32 MaxRandomizedVariations;` — `UPROPERTY(EditAnywhere, Category = "Quality", meta = (ClampMin = "1"))` — The max number of variations to include for the given quality in a SoundCueContainer set to 'Randomized'.
- L35 _public member_ `int32 MaxMixVariations;` — `UPROPERTY(EditAnywhere, Category = "Quality", meta = (ClampMin = "1"))` — The max number of variations to include for the given quality in a SoundCueContainer set to 'Mix'.
- L37 _public prototype_ `FSoundCueTemplateQualitySettings();`

#### class `USoundCueTemplateSettings`  
`class USoundCueTemplateSettings : public UDeveloperSettings`  
_L41-62_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig, meta=(DisplayName="Sound Cue Templates"))`
- inherits: `UDeveloperSettings`
- L47 _private member_ `TArray<FSoundCueTemplateQualitySettings> QualityLevels;` — `UPROPERTY(config, EditAnywhere, Category = "Quality")`
- L51 _private prototype_ `virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L52 _private prototype_ `virtual void PostInitProperties() override;`
- L54 _private member_ `FSoundCueTemplateQualitySettingsNotifier SettingsNotifier;`
- L56 _public prototype_ `bool RebuildQualityLevels();`
- L59 _public prototype_ `const FSoundCueTemplateQualitySettings& GetQualityLevelSettings(int32 Index) const;` — Get the quality level settings at the provided level index
- L60 _public prototype_ `int32 GetQualityLevelSettingsNum() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SOUNDCUETEMPLATES_API`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueTemplatesModule.h` (Public)


#### class `FSoundCueTemplatesModule`  
`class FSoundCueTemplatesModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SoundCueTemplates, Log, All);`
