# Plugins / PropertyAnimator

- module root: `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator`
- headers: 38; symbols: 455
- symbol kinds: class=31, enum=9, enumerator=46, function=64, member=76, namespace=4, prototype=211, struct=10, typedef=4
- PrivateDependencyModuleNames: ApplicationCore, AudioSynesthesia, CoreUObject, DeveloperSettings, Engine, Json, MovieSceneTracks, Text3D
- PublicDependencyModuleNames: Core, MovieScene, PropertyAnimatorCore

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/MovieScene/Easing/PropertyAnimatorEasingDoubleChannelEvaluatorSystem.h` (Private)


#### class `UPropertyAnimatorEasingDoubleChannelEvaluatorSystem`  
`class UPropertyAnimatorEasingDoubleChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating Easing channels.
- L15 _public prototype_ `UPropertyAnimatorEasingDoubleChannelEvaluatorSystem(const FObjectInitializer& InObjectInitializer);`
- L18 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* InTaskScheduler) override;`
- L19 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& InSubsequents) override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/MovieScene/Easing/PropertyAnimatorEasingDoubleChannelOverrideContainer.h` (Private)


#### class `UPropertyAnimatorEasingDoubleChannelOverrideContainer`  
`class UPropertyAnimatorEasingDoubleChannelOverrideContainer : public UMovieSceneChannelOverrideContainer`  
_L10-30_
- reflection: `UCLASS(meta=(DisplayName="Easing (Double)", ToolTip="Override a double channel to use double easing"))`
- inherits: `UMovieSceneChannelOverrideContainer`
- L16 _public prototype_ `virtual bool SupportsOverride(FName InDefaultChannelTypeName) const override;`
- L17 _public prototype_ `virtual void ImportEntityImpl(const UE::MovieScene::FChannelOverrideEntityImportParams& InOverrideParams, const UE::MovieScene::FEntityImportParams& InImportParams, UE::MovieScene::FImportedEntity* OutImportedEntity) override;`
- L18 _public prototype_ `virtual const FMovieSceneChannel* GetChannel() const override;`
- L19 _public prototype_ `virtual FMovieSceneChannel* GetChannel() override;`
- L21 _public prototype_ `virtual FMovieSceneChannelHandle AddChannelProxy(FName InChannelName, FMovieSceneChannelProxyData& InProxyData, const FMovieSceneChannelMetaData& InMetaData) override;`
- L23 _public prototype_ `virtual void AddChannelProxy(FName InChannelName, FMovieSceneChannelProxyData& InProxyData) override;`
- L29 _private member_ `FPropertyAnimatorEasingDoubleChannel EasingChannel;` — `UPROPERTY(EditAnywhere, Category = "Easing")`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/MovieScene/PropertyAnimatorComponentTypes.h` (Private)


#### struct `FPropertyAnimatorComponentTypes`  
`struct FPropertyAnimatorComponentTypes`  
_L11-23_
- L13 _public prototype_ `static FPropertyAnimatorComponentTypes* Get();`
- L15 _public prototype_ `static void Destroy();`
- L17 _public member_ `UE::MovieScene::TComponentTypeID<FPropertyAnimatorWaveParameters> WaveParameters;`
- L19 _public member_ `UE::MovieScene::TComponentTypeID<FPropertyAnimatorEasingParameters> EasingParameters;`
- L22 _private prototype_ `FPropertyAnimatorComponentTypes();`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/MovieScene/Wave/PropertyAnimatorWaveDoubleChannelEvaluatorSystem.h` (Private)


#### class `UPropertyAnimatorWaveDoubleChannelEvaluatorSystem`  
`class UPropertyAnimatorWaveDoubleChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating wave channels.
- L15 _public prototype_ `UPropertyAnimatorWaveDoubleChannelEvaluatorSystem(const FObjectInitializer& InObjectInitializer);`
- L18 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* InTaskScheduler) override;`
- L19 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& InSubsequents) override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/MovieScene/Wave/PropertyAnimatorWaveDoubleChannelOverrideContainer.h` (Private)


#### class `UPropertyAnimatorWaveDoubleChannelOverrideContainer`  
`class UPropertyAnimatorWaveDoubleChannelOverrideContainer : public UMovieSceneChannelOverrideContainer`  
_L10-30_
- reflection: `UCLASS(meta=(DisplayName="Wave (Double)", ToolTip="Override a double channel to use double waves"))`
- inherits: `UMovieSceneChannelOverrideContainer`
- L16 _public prototype_ `virtual bool SupportsOverride(FName InDefaultChannelTypeName) const override;`
- L17 _public prototype_ `virtual void ImportEntityImpl(const UE::MovieScene::FChannelOverrideEntityImportParams& InOverrideParams, const UE::MovieScene::FEntityImportParams& InImportParams, UE::MovieScene::FImportedEntity* OutImportedEntity) override;`
- L18 _public prototype_ `virtual const FMovieSceneChannel* GetChannel() const override;`
- L19 _public prototype_ `virtual FMovieSceneChannel* GetChannel() override;`
- L21 _public prototype_ `virtual FMovieSceneChannelHandle AddChannelProxy(FName InChannelName, FMovieSceneChannelProxyData& InProxyData, const FMovieSceneChannelMetaData& InMetaData) override;`
- L23 _public prototype_ `virtual void AddChannelProxy(FName InChannelName, FMovieSceneChannelProxyData& InProxyData) override;`
- L29 _private member_ `FPropertyAnimatorWaveDoubleChannel WaveChannel;` — `UPROPERTY(EditAnywhere, Category = "Wave")`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetLocation.h` (Private)


#### class `UPropertyAnimatorPresetLocation`  
`class UPropertyAnimatorPresetLocation : public UPropertyAnimatorCorePropertyPreset`  
_L15-32_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCorePropertyPreset`
- desc: Preset for position properties (X, Y, Z) on scene component
- L20 _public function_ `UPropertyAnimatorPresetLocation()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`
- L29 _protected prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties) override;`
- L30 _protected function_ `virtual bool LoadPreset() override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetRotation.h` (Private)


#### class `UPropertyAnimatorPresetRotation`  
`class UPropertyAnimatorPresetRotation : public UPropertyAnimatorCorePropertyPreset`  
_L15-32_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCorePropertyPreset`
- desc: Preset for position properties (Roll, Pitch, Yaw) on scene component
- L20 _public function_ `UPropertyAnimatorPresetRotation()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`
- L29 _protected prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties) override;`
- L30 _protected function_ `virtual bool LoadPreset() override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetScale.h` (Private)


#### class `UPropertyAnimatorPresetScale`  
`class UPropertyAnimatorPresetScale : public UPropertyAnimatorCorePropertyPreset`  
_L15-32_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCorePropertyPreset`
- desc: Preset for position properties (X, Y, Z) on scene component
- L20 _public function_ `UPropertyAnimatorPresetScale()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`
- L29 _protected prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties) override;`
- L30 _protected function_ `virtual bool LoadPreset() override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetText.h` (Private)


#### class `UPropertyAnimatorPresetText`  
`class UPropertyAnimatorPresetText : public UPropertyAnimatorCorePropertyPreset`  
_L15-32_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCorePropertyPreset`
- desc: Preset for text property on root text 3d component
- L20 _public function_ `UPropertyAnimatorPresetText()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`
- L29 _protected prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties) override;`
- L30 _protected function_ `virtual bool LoadPreset() override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetTextLocation.h` (Private)


#### class `UPropertyAnimatorPresetTextLocation`  
`class UPropertyAnimatorPresetTextLocation : public UPropertyAnimatorPresetLocation`  
_L15-30_
- reflection: `UCLASS()`
- inherits: `UPropertyAnimatorPresetLocation`
- desc: Preset for text character position properties (X, Y, Z) on scene component
- L20 _public function_ `UPropertyAnimatorPresetTextLocation()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetTextRotation.h` (Private)


#### class `UPropertyAnimatorPresetTextRotation`  
`class UPropertyAnimatorPresetTextRotation : public UPropertyAnimatorPresetRotation`  
_L15-30_
- reflection: `UCLASS()`
- inherits: `UPropertyAnimatorPresetRotation`
- desc: Preset for text character position properties (Roll, Pitch, Yaw) on scene component
- L20 _public function_ `UPropertyAnimatorPresetTextRotation()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetTextScale.h` (Private)


#### class `UPropertyAnimatorPresetTextScale`  
`class UPropertyAnimatorPresetTextScale : public UPropertyAnimatorPresetScale`  
_L15-30_
- reflection: `UCLASS()`
- inherits: `UPropertyAnimatorPresetScale`
- desc: Preset for text character position properties (X, Y, Z) on scene component
- L20 _public function_ `UPropertyAnimatorPresetTextScale()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetTextVisibility.h` (Private)


#### class `UPropertyAnimatorPresetTextVisibility`  
`class UPropertyAnimatorPresetTextVisibility : public UPropertyAnimatorPresetVisibility`  
_L15-30_
- reflection: `UCLASS()`
- inherits: `UPropertyAnimatorPresetVisibility`
- desc: Preset for text character visibility on scene component
- L20 _public function_ `UPropertyAnimatorPresetTextVisibility()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Presets/PropertyAnimatorPresetVisibility.h` (Private)


#### class `UPropertyAnimatorPresetVisibility`  
`class UPropertyAnimatorPresetVisibility : public UPropertyAnimatorCorePropertyPreset`  
_L15-32_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCorePropertyPreset`
- desc: Preset for visibility properties on root scene component
- L20 _public function_ `UPropertyAnimatorPresetVisibility()`
- L27 _protected prototype_ `virtual void OnPresetRegistered() override;`
- L28 _protected prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const override;`
- L29 _protected prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties) override;`
- L30 _protected function_ `virtual bool LoadPreset() override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Properties/PropertyAnimatorTextResolver.h` (Private)


#### enum `EPropertyAnimatorTextResolverRangeUnit`  
`enum class EPropertyAnimatorTextResolverRangeUnit : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `Percentage`
- L13 _public enumerator_ `Character`
- L14 _public enumerator_ `Word`

#### enum `EPropertyAnimatorTextResolverRangeDirection`  
`enum class EPropertyAnimatorTextResolverRangeDirection : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `LeftToRight`
- L21 _public enumerator_ `RightToLeft`
- L22 _public enumerator_ `FromCenter`

#### class `UPropertyAnimatorTextResolver`  
`class UPropertyAnimatorTextResolver : public UPropertyAnimatorCoreResolver`  
_L32-127_
- reflection: `UCLASS()`
- inherits: `UPropertyAnimatorCoreResolver`
- desc: Text characters properties resolver Since each character in text are transient and regenerated on change We need to have a resolver that will resolve each character in the text when needed We manipulate a single property that underneath means we manipulate all text characters properties
- L37 _public function_ `UPropertyAnimatorTextResolver() : UPropertyAnimatorCoreResolver(TEXT("TextChars"))`
- L41 _public prototype_ `void SetUnit(EPropertyAnimatorTextResolverRangeUnit InUnit);`
- L42 _public function_ `EPropertyAnimatorTextResolverRangeUnit GetUnit() const`
- L47 _public function_ `float GetPercentageRange() const`
- L52 _public prototype_ `void SetPercentageRange(float InPercentageRange);`
- L54 _public function_ `float GetPercentageOffset() const`
- L59 _public prototype_ `void SetPercentageOffset(float InPercentageOffset);`
- L61 _public function_ `int32 GetCharacterRangeCount() const`
- L66 _public prototype_ `void SetCharacterRangeCount(int32 InCharacterRangeCount);`
- L68 _public function_ `int32 GetCharacterOffsetCount() const`
- L73 _public prototype_ `void SetCharacterOffsetCount(int32 InCharacterOffsetCount);`
- L75 _public function_ `int32 GetWordRangeCount() const`
- L80 _public prototype_ `void SetWordRangeCount(int32 InWordRangeCount);`
- L82 _public function_ `int32 GetWordOffsetCount() const`
- L87 _public prototype_ `void SetWordOffsetCount(int32 InWordOffsetCount);`
- L89 _public prototype_ `void SetDirection(EPropertyAnimatorTextResolverRangeDirection InDirection);`
- L90 _public function_ `EPropertyAnimatorTextResolverRangeDirection GetDirection() const`
- L97 _protected prototype_ `virtual bool FixUpProperty(FPropertyAnimatorCoreData& InOldProperty) override;`
- L98 _protected prototype_ `virtual void GetTemplateProperties(UObject* InContext, TSet<FPropertyAnimatorCoreData>& OutProperties, const TArray<FName>* InSearchPath) override;`
- L99 _protected prototype_ `virtual void ResolveTemplateProperties(const FPropertyAnimatorCoreData& InTemplateProperty, TArray<FPropertyAnimatorCoreData>& OutProperties, bool bInForEvaluation) override;`
- L100 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L101 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L105 _protected member_ `EPropertyAnimatorTextResolverRangeUnit Unit = EPropertyAnimatorTextResolverRangeUnit::Percentage;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")`
- L108 _protected member_ `float PercentageRange = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", ClampMin="0", ClampMax="100", Units=Percent, EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Percentage", EditConditionHides))`
- L111 _protected member_ `float PercentageOffset = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", Units=Percent, EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Percentage", EditConditionHides))`
- L114 _protected member_ `int32 CharacterRangeCount = 100;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", ClampMin="0", EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Character", EditConditionHides))`
- L117 _protected member_ `int32 CharacterOffsetCount = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Character", EditConditionHides))`
- L120 _protected member_ `int32 WordRangeCount = 100;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", ClampMin="0", EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Word", EditConditionHides))`
- L123 _protected member_ `int32 WordOffsetCount = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Delta="1", EditCondition="Unit == EPropertyAnimatorTextResolverRangeUnit::Word", EditConditionHides))`
- L126 _protected member_ `EPropertyAnimatorTextResolverRangeDirection Direction = EPropertyAnimatorTextResolverRangeDirection::LeftToRight;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Settings/PropertyAnimatorSettings.h` (Private)


#### class `UPropertyAnimatorSettings`  
`class UPropertyAnimatorSettings : public UDeveloperSettings`  
_L11-37_
- reflection: `UCLASS(Config=Engine, meta=(DisplayName="Property Animator"))`
- inherits: `UDeveloperSettings`
- desc: Settings for motion design PropertyAnimator plugin
- L16 _public prototype_ `UPropertyAnimatorSettings();`
- L18 _public prototype_ `TSet<FName> GetCounterFormatNames() const;`
- L19 _public prototype_ `const FPropertyAnimatorCounterFormat* GetCounterFormat(FName InName) const;`
- L22 _public prototype_ `bool AddCounterFormat(const FPropertyAnimatorCounterFormat& InNewFormat, bool bInOverride = true, bool bInSaveConfig = true);`
- L23 _public prototype_ `void OpenSettings() const;`
- L29 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L33 _protected prototype_ `void OnCounterFormatsChanged();`
- L36 _protected member_ `TSet<FPropertyAnimatorCounterFormat> CounterFormatPresets;` — `UPROPERTY(Config, EditAnywhere, Category="Animator", meta=(TitleProperty="FormatName"))`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorBounce.h` (Public)


#### class `UPropertyAnimatorBounce`  
`class UPropertyAnimatorBounce : public UPropertyAnimatorNumericBase`  
_L12-34_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"), Hidden, meta=(Deprecated, DeprecationMessage="Use preset bounce animator based on curve instead"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies an additive bounce movement with various options on supported float properties
- L17 _public prototype_ `void SetInvertEffect(bool bInvert);`
- L18 _public function_ `bool GetInvertEffect() const`
- L24 _protected function_ `virtual void OnInvertEffect()`
- L27 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L28 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L33 _protected member_ `bool bInvertEffect = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter="SetInvertEffect", Getter="GetInvertEffect", Category="Animator")` — Invert the effect result

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorClock.h` (Public)


#### enum `EPropertyAnimatorClockMode`  
`enum class EPropertyAnimatorClockMode : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- desc: Mode supported for properties value
- L15 _public enumerator_ `LocalTime` — Local time of the machine
- L17 _public enumerator_ `Countdown` — Specified duration elapsing until it reaches 0
- L19 _public enumerator_ `Stopwatch` — Shows the current time elapsed

#### class `UPropertyAnimatorClock`  
`class UPropertyAnimatorClock : public UPropertyAnimatorTextBase`  
_L24-96_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorTextBase`
- desc: Animate supported string properties to display time
- L29 _public prototype_ `static void RegisterFormat(TCHAR InChar, TFunction<FString(const FDateTime&)> InFormatter);`
- L30 _public prototype_ `static void UnregisterFormat(TCHAR InChar);`
- L31 _public prototype_ `static FString FormatDateTime(const FDateTime& InDateTime, const FString& InDisplayFormat, const FString& InMask);`
- L33 _public prototype_ `UPropertyAnimatorClock();`
- L35 _public prototype_ `void SetDisplayFormat(const FString& InDisplayFormat);`
- L36 _public function_ `const FString& GetDisplayFormat() const`
- L41 _public prototype_ `void SetDisplayMask(const FString& InPadding);`
- L42 _public function_ `const FString& GetDisplayMask() const`
- L49 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L50 _protected prototype_ `virtual void EvaluateProperties(FInstancedPropertyBag& InParameters) override;`
- L51 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L52 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L88 _protected member_ `FString DisplayFormat = TEXT("%H:` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — Display date time format : %a - Weekday, eg) Sun %A - Weekday, eg) Sunday %w - Weekday, 0-6 (Sunday is 0) %y - Year, YY %Y - Year, YYYY %b - Month, eg) Jan %B - Month, eg) January %m - Month, 01-12 %n - Month, 1-12 %d - Day, 01-31 %e - Day, 1-31 %j - Day of the Year, 001-366 %J - Day of the Year, 1-366 %l - 12h Hour, 1-12 %I - 12h Hour, 01-12 %H - 24h Hour, 00-23 %h - 24h Hour, 0-23 %o - Hour, 0-inf %M - Minute, 00-59 %N - Minute, 0-59 %i - Minute, 0-inf %S - Second, 00-60 %s - Second, 0-60 %c - Second, 0-inf %f - Millisecond, 000-999 %F - Millisecond, 0-999 %p - AM or PM %P - am or PM %t - Ticks since midnight, January 1, 0001
- L95 _protected member_ `FString DisplayMask = TEXT("");` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — Used as padding to complete the display format eg: DisplayMask=****** and DisplayFormat=%c would result in ***999

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorCounter.h` (Public)


#### enum `EPropertyAnimatorCounterRoundingMode`  
`enum class EPropertyAnimatorCounterRoundingMode : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates all rounding mode available
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `Round`
- L15 _public enumerator_ `Floor`
- L16 _public enumerator_ `Ceil`

#### struct `FPropertyAnimatorCounterFormat`  
`struct FPropertyAnimatorCounterFormat`  
_L21-91_
- reflection: `USTRUCT(BlueprintType)`
- desc: Format options used to convert a number to string
- L25 _public prototype_ `FPropertyAnimatorCounterFormat() = default;`
- L27 _public function_ `explicit FPropertyAnimatorCounterFormat(FName InFormatName) : FormatName(InFormatName)`
- L33 _public member_ `FName FormatName;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Format friendly name
- L37 _public member_ `uint8 MinIntegerCount = 0;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Minimum number of integer before the decimal separator for padding
- L41 _public member_ `uint8 MaxDecimalCount = 3;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Maximum number of decimal precision after the decimal separator
- L45 _public member_ `uint8 GroupingSize = 3;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Used to group numbers together like thousands
- L49 _public member_ `FString DecimalCharacter = TEXT(".")` — `UPROPERTY(EditAnywhere, Category="Animator")` — Decimal separator character
- L53 _public member_ `FString GroupingCharacter = TEXT(",")` — `UPROPERTY(EditAnywhere, Category="Animator")` — Thousands separator character
- L57 _public member_ `FString PaddingCharacter = TEXT("0")` — `UPROPERTY(EditAnywhere, Category="Animator")` — Filling character for leading blanks
- L61 _public member_ `EPropertyAnimatorCounterRoundingMode RoundingMode = EPropertyAnimatorCounterRoundingMode::None;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Whether rounding the number is needed
- L65 _public member_ `bool bUseSign = false;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Add a prefix symbol to show the sign of the number (+, -)
- L69 _public member_ `bool bTruncate = false;` — `UPROPERTY(EditAnywhere, Category="Animator")` — Truncate when the value exceeds the display format
- L72 _public prototype_ `void EnsureCharactersLength();` — Clamp custom characters to one char only
- L75 _public prototype_ `FString FormatNumber(double InNumber) const;` — Format a number using these options
- L82 _public function_ `bool operator==(const FPropertyAnimatorCounterFormat& InOther) const`
- L87 _public function_ `bool operator!=(const FPropertyAnimatorCounterFormat& InOther) const`

#### class `UPropertyAnimatorCounter`  
`class UPropertyAnimatorCounter : public UPropertyAnimatorTextBase`  
_L95-173_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorTextBase`
- desc: Animate supported string properties to display a counter
- L101 _public prototype_ `static FName GetUseCustomFormatPropertyName();`
- L104 _public prototype_ `UPropertyAnimatorCounter();`
- L106 _public prototype_ `void SetDisplayPattern(const FText& InPattern);`
- L107 _public function_ `const FText& GetDisplayPattern() const`
- L112 _public prototype_ `void SetUseCustomFormat(bool bInUseCustom);`
- L113 _public function_ `bool GetUseCustomFormat() const`
- L118 _public prototype_ `void SetPresetFormatName(FName InPresetName);`
- L119 _public function_ `FName GetPresetFormatName() const`
- L124 _public prototype_ `void SetCustomFormat(const FPropertyAnimatorCounterFormat* InFormat);`
- L125 _public prototype_ `const FPropertyAnimatorCounterFormat* GetCustomFormat() const;`
- L128 _protected prototype_ `FString FormatNumber(double InNumber) const;`
- L129 _protected prototype_ `const FPropertyAnimatorCounterFormat* GetFormat() const;`
- L133 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L138 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L139 _protected prototype_ `virtual void EvaluateProperties(FInstancedPropertyBag& InParameters) override;`
- L140 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L141 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L145 _protected prototype_ `TArray<FName> GetAvailableFormatNames() const;` — `UFUNCTION()`
- L149 _protected prototype_ `void OpenPropertyAnimatorSettings();` — `UFUNCTION(CallInEditor)`
- L152 _protected prototype_ `void SaveCustomFormatAsPreset();` — `UFUNCTION(CallInEditor)`
- L155 _protected prototype_ `void OnUseCustomFormatChanged();`
- L156 _protected prototype_ `void OnCustomFormatChanged();`
- L160 _protected member_ `FText DisplayPattern = FText::FromString(TEXT("{0}"` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — Display pattern for the output to add prefix and suffix, use {0} as replacement symbol
- L164 _protected member_ `bool bUseCustomFormat = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetUseCustomFormat", Getter="GetUseCustomFormat", Category="Animator")` — Use available presets formats or custom format
- L168 _protected member_ `FName PresetFormatName;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(GetOptions="GetAvailableFormatNames", EditCondition="!bUseCustomFormat", EditConditionHides, HideEditConditionToggle))` — Preset format defined in the project settings
- L172 _protected member_ `TInstancedStruct<FPropertyAnimatorCounterFormat> CustomFormat;` — `UPROPERTY(EditInstanceOnly, Category="Animator", meta=(EditCondition="bUseCustomFormat", EditConditionHides, HideEditConditionToggle))` — Custom format

#### Free symbols / members of external scopes

- L77 _function_ `friend uint32 GetTypeHash(const FPropertyAnimatorCounterFormat& InItem)`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorCurve.h` (Public)


#### struct `FPropertyAnimatorCurveEasing`  
`struct FPropertyAnimatorCurveEasing`  
_L12-21_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `TObjectPtr<UPropertyAnimatorEaseCurve> EaseCurve;` — `UPROPERTY(EditInstanceOnly, DisplayName="Curve", Category="Animator", meta=(ForceShowEngineContent, ForceShowPluginContent))`
- L20 _public member_ `float EaseDuration = 0.f;` — `UPROPERTY(EditInstanceOnly, Interp, DisplayName="Duration", Category="Animator", meta=(ClampMin="0", Units=Seconds))`

#### class `UPropertyAnimatorCurve`  
`class UPropertyAnimatorCurve : public UPropertyAnimatorNumericBase`  
_L27-106_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies a wave movement from a curve on supported float properties
- L32 _public prototype_ `UPropertyAnimatorCurve();`
- L34 _public prototype_ `void SetWaveCurve(UPropertyAnimatorWaveCurve* InCurve);`
- L36 _public function_ `UPropertyAnimatorWaveCurve* GetWaveCurve() const`
- L41 _public prototype_ `void SetEaseInEnabled(bool bInEnabled);`
- L43 _public function_ `bool GetEaseInEnabled() const`
- L48 _public prototype_ `void SetEaseIn(const FPropertyAnimatorCurveEasing& InEasing);`
- L50 _public function_ `const FPropertyAnimatorCurveEasing& GetEaseIn() const`
- L55 _public prototype_ `void SetEaseOutEnabled(bool bInEnabled);`
- L57 _public function_ `bool GetEaseOutEnabled() const`
- L62 _public prototype_ `void SetEaseOut(const FPropertyAnimatorCurveEasing& InEasing);`
- L64 _public function_ `const FPropertyAnimatorCurveEasing& GetEaseOut() const`
- L72 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L77 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L78 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L79 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L80 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L83 _protected prototype_ `void OnEaseInChanged();`
- L84 _protected prototype_ `void OnEaseOutChanged();`
- L85 _protected prototype_ `virtual void OnCycleDurationChanged() override;`
- L89 _protected member_ `bool bEaseInEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetEaseInEnabled", Getter="GetEaseInEnabled", DisplayName="InEnabled", Category="Animator", meta=(InlineEditConditionToggle))` — Use ease in effect
- L93 _protected member_ `FPropertyAnimatorCurveEasing EaseIn;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="In", Category="Animator", meta=(EditCondition="bEaseInEnabled"))` — Ease in for this effect
- L97 _protected member_ `TObjectPtr<UPropertyAnimatorWaveCurve> WaveCurve;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Loop Curve", Category="Animator", meta=(ForceShowEngineContent, ForceShowPluginContent))` — The base curve to sample for the animation
- L101 _protected member_ `bool bEaseOutEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetEaseOutEnabled", Getter="GetEaseOutEnabled", DisplayName="OutEnabled", Category="Animator", meta=(InlineEditConditionToggle))` — Use ease out effect
- L105 _protected member_ `FPropertyAnimatorCurveEasing EaseOut;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", DisplayName="Out", meta=(EditCondition="bEaseOutEnabled"))` — Ease out for this effect

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorNumericBase.h` (Public)


#### enum `EPropertyAnimatorCycleMode`  
`enum class EPropertyAnimatorCycleMode : uint8`  
_L9-19_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `None UMETA(Hidden)` — Disable cycle options
- L14 _public enumerator_ `DoOnce` — Cycle only once then stop
- L16 _public enumerator_ `Loop` — Cycle and repeat once we reached the end
- L18 _public enumerator_ `PingPong` — Cycle and reverse repeat

#### class `UPropertyAnimatorNumericBase`  
`class UPropertyAnimatorNumericBase : public UPropertyAnimatorCoreBase`  
_L25-124_
- reflection: `UCLASS(MinimalAPI, Abstract, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorCoreBase`
- desc: Animate supported numeric properties with various options
- L32 _public prototype_ `void SetMagnitude(float InMagnitude);`
- L33 _public function_ `float GetMagnitude() const`
- L38 _public prototype_ `void SetCycleMode(EPropertyAnimatorCycleMode InMode);`
- L39 _public function_ `EPropertyAnimatorCycleMode GetCycleMode() const`
- L44 _public prototype_ `void SetCycleDuration(float InCycleDuration);`
- L45 _public function_ `float GetCycleDuration() const`
- L50 _public prototype_ `void SetCycleGapDuration(float InCycleGap);`
- L51 _public function_ `float GetCycleGapDuration() const`
- L56 _public prototype_ `void SetRandomTimeOffset(bool bInOffset);`
- L57 _public function_ `bool GetRandomTimeOffset() const`
- L62 _public prototype_ `void SetSeed(int32 InSeed);`
- L63 _public function_ `int32 GetSeed() const`
- L71 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L75 _protected function_ `virtual void OnMagnitudeChanged()`
- L76 _protected function_ `virtual void OnCycleDurationChanged()`
- L77 _protected function_ `virtual void OnCycleModeChanged()`
- L78 _protected function_ `virtual void OnSeedChanged()`
- L81 _protected prototype_ `virtual TSubclassOf<UPropertyAnimatorCoreContext> GetPropertyContextClass(const FPropertyAnimatorCoreData& InProperty) override;`
- L82 _protected prototype_ `virtual EPropertyAnimatorPropertySupport IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L83 _protected prototype_ `virtual void EvaluateProperties(FInstancedPropertyBag& InParameters) override;`
- L84 _protected prototype_ `virtual void OnPropertyLinked(UPropertyAnimatorCoreContext* InLinkedProperty, EPropertyAnimatorPropertySupport InSupport) override;`
- L85 _protected prototype_ `virtual bool IsTimeSourceSupported(UPropertyAnimatorCoreTimeSourceBase* InTimeSource) const override;`
- L86 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L87 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L88 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L92 _protected function_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const` — Evaluate and return float value for a property
- L99 _protected member_ `float Magnitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0"))` — Magnitude for the effect on all properties
- L103 _protected member_ `EPropertyAnimatorCycleMode CycleMode = EPropertyAnimatorCycleMode::Loop;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(EditCondition="CycleMode != EPropertyAnimatorCycleMode::None", EditConditionHides))` — Cycle mode for the effect
- L107 _protected member_ `float CycleDuration = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0", Units=Seconds, EditCondition="CycleMode != EPropertyAnimatorCycleMode::None", EditConditionHides))` — Duration of one cycle for the effect = period of the effect
- L111 _protected member_ `float CycleGapDuration = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0", Units=Seconds, EditCondition="CycleMode != EPropertyAnimatorCycleMode::DoOnce && CycleMode != EPropertyAnimatorCycleMode::None", EditConditionHides))` — Time gap between each cycle
- L115 _protected member_ `bool bRandomTimeOffset = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetRandomTimeOffset", Getter="GetRandomTimeOffset", Category="Animator", meta=(InlineEditConditionToggle))` — Use random time offset to add variation in animation
- L119 _protected member_ `int32 Seed = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Seed, EditCondition="bRandomTimeOffset"))` — Seed to generate per property time offset
- L123 _private member_ `FRandomStream RandomStream = FRandomStream(Seed);` — Random stream for time offset

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorOscillate.h` (Public)


#### enum `EPropertyAnimatorOscillateFunction`  
`enum class EPropertyAnimatorOscillateFunction : uint8`  
_L9-17_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Sine`
- L12 _public enumerator_ `Cosine`
- L13 _public enumerator_ `Square`
- L14 _public enumerator_ `InvertedSquare`
- L15 _public enumerator_ `Sawtooth`
- L16 _public enumerator_ `Triangle`

#### class `UPropertyAnimatorOscillate`  
`class UPropertyAnimatorOscillate : public UPropertyAnimatorNumericBase`  
_L23-43_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"), Hidden, meta=(Deprecated, DeprecationMessage="Use preset oscillate animator based on curve instead"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies an additive regular oscillate movement with various options on supported float properties
- L28 _public prototype_ `void SetOscillateFunction(EPropertyAnimatorOscillateFunction InFunction);`
- L29 _public function_ `EPropertyAnimatorOscillateFunction GetOscillateFunction() const`
- L36 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L37 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L42 _protected member_ `EPropertyAnimatorOscillateFunction OscillateFunction = EPropertyAnimatorOscillateFunction::Sine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Animator")` — The oscillate function to feed current time elapsed

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorPulse.h` (Public)


#### class `UPropertyAnimatorPulse`  
`class UPropertyAnimatorPulse : public UPropertyAnimatorNumericBase`  
_L15-45_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"), Hidden, meta=(Deprecated, DeprecationMessage="Use preset pulse animator based on curve instead"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies an additive pulse movement with various options on supported float properties
- L20 _public prototype_ `void SetEasingFunction(EPropertyAnimatorEasingFunction InEasingFunction);`
- L21 _public function_ `EPropertyAnimatorEasingFunction GetEasingFunction() const`
- L26 _public prototype_ `void SetEasingType(EPropertyAnimatorEasingType InEasingType);`
- L27 _public function_ `EPropertyAnimatorEasingType GetEasingType() const`
- L34 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L35 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L40 _protected member_ `EPropertyAnimatorEasingFunction EasingFunction = EPropertyAnimatorEasingFunction::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Animator")` — The easing function to use to modify the base effect
- L44 _protected member_ `EPropertyAnimatorEasingType EasingType = EPropertyAnimatorEasingType::InOut;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Animator", meta=(EditCondition="EasingFunction != EPropertyAnimatorEasingFunction::Line", EditConditionHides))` — The type of effect for easing function

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorSoundWave.h` (Public)


#### class `UPropertyAnimatorSoundWave`  
`class UPropertyAnimatorSoundWave : public UPropertyAnimatorNumericBase`  
_L15-66_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies a sampled sound wave movement with various options on supported float properties
- L20 _public prototype_ `UPropertyAnimatorSoundWave();`
- L22 _public prototype_ `void SetSampledSoundWave(USoundWave* InSoundWave);`
- L23 _public function_ `USoundWave* GetSampledSoundWave() const`
- L28 _public prototype_ `void SetLoop(bool bInLoop);`
- L29 _public function_ `bool GetLoop() const`
- L37 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _protected prototype_ `void OnSampledSoundWaveChanged();`
- L44 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L45 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L46 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L47 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L56 _protected member_ `TObjectPtr<USoundWave> SampledSoundWave;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Setter, Getter, Category="Animator")` — The sound wave to analyse Cannot be switched at runtime, only in editor due to analyzer Analyzed audio will work at runtime since it is cached
- L60 _protected member_ `bool bLoop = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter="SetLoop", Getter="GetLoop", Category="Animator")` — Whether we keep looping after the duration has been reached or before 0
- L65 _private member_ `TObjectPtr<ULoudnessNRT> AudioAnalyzer;` — `UPROPERTY()` — Non-Real-Time audio analyser for loudness

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorTextBase.h` (Public)


#### class `UPropertyAnimatorTextBase`  
`class UPropertyAnimatorTextBase : public UPropertyAnimatorCoreBase`  
_L12-22_
- reflection: `UCLASS(MinimalAPI, Abstract, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorCoreBase`
- desc: Animate supported text properties with various options
- L18 _protected prototype_ `virtual EPropertyAnimatorPropertySupport IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L19 _protected prototype_ `virtual void OnPropertyLinked(UPropertyAnimatorCoreContext* InLinkedProperty, EPropertyAnimatorPropertySupport InSupport) override;`
- L20 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorTime.h` (Public)


#### class `UPropertyAnimatorTime`  
`class UPropertyAnimatorTime : public UPropertyAnimatorNumericBase`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies an additive time movement with various options on supported float properties
- L18 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L19 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Animators/PropertyAnimatorWiggle.h` (Public)


#### class `UPropertyAnimatorWiggle`  
`class UPropertyAnimatorWiggle : public UPropertyAnimatorNumericBase`  
_L12-36_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=("Animator"))`
- inherits: `UPropertyAnimatorNumericBase`
- desc: Applies a random wiggle movement with various options on supported numeric properties
- L17 _public prototype_ `UPropertyAnimatorWiggle();`
- L19 _public prototype_ `void SetFrequency(float InFrequency);`
- L20 _public function_ `float GetFrequency() const`
- L27 _protected prototype_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata) override;`
- L28 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InPropertyData, UPropertyAnimatorCoreContext* InContext, FInstancedPropertyBag& InParameters, FInstancedPropertyBag& OutEvaluationResult) const override;`
- L29 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L30 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L35 _protected member_ `float Frequency = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0", Units=Hz))` — Frequency for the effect, higher values will give you faster movements

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Curves/PropertyAnimatorEaseCurve.h` (Public)


#### class `UPropertyAnimatorEaseCurve`  
`class UPropertyAnimatorEaseCurve : public UCurveFloat`  
_L10-13_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCurveFloat`
- desc: Base class for property animator easing curves (0-1)

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Curves/PropertyAnimatorWaveCurve.h` (Public)


#### class `UPropertyAnimatorWaveCurve`  
`class UPropertyAnimatorWaveCurve : public UCurveFloat`  
_L10-13_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCurveFloat`
- desc: Base class for property animator wave curves (inf-inf)

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/MovieScene/Easing/PropertyAnimatorEasingDoubleChannel.h` (Public)


#### struct `FPropertyAnimatorEasingDoubleChannel`  
`struct FPropertyAnimatorEasingDoubleChannel : public FMovieSceneChannel`  
_L14-30_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L18 _public typedef_ `using CurveValueType = double;`
- L20 _public prototype_ `FPropertyAnimatorEasingDoubleChannel() = default;`
- L22 _public prototype_ `double Evaluate(double InBaseSeconds, double InSeconds) const;`
- L24 _public prototype_ `bool Evaluate(const UMovieSceneSection* InSection, FFrameTime InTime, double& OutValue) const;`
- L26 _public prototype_ `static double Evaluate(const FPropertyAnimatorEasingParameters& InParameters, double InBaseSeconds, double InSeconds);`
- L29 _public member_ `FPropertyAnimatorEasingParameters Parameters;` — `UPROPERTY(EditAnywhere, Category = "Easing")`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FPropertyAnimatorEasingDoubleChannel> : TMovieSceneChannelTraitsBase<FPropertyAnimatorEasingDoubleChannel>`  
_L33-39_
- inherits: `TMovieSceneChannelTraitsBase<FPropertyAnimatorEasingDoubleChannel>`
- L37 _public typedef_ `typedef TMovieSceneExternalValue<double> ExtendedEditorDataType;` — Easing Channels can have external values (they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L41 _function_ `inline bool EvaluateChannel(const UMovieSceneSection* InSection, const FPropertyAnimatorEasingDoubleChannel* InChannel, FFrameTime InTime, double& OutValue)`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/MovieScene/Easing/PropertyAnimatorEasingParameters.h` (Public)


#### struct `FPropertyAnimatorEasingParameters`  
`struct FPropertyAnimatorEasingParameters`  
_L9-31_
- reflection: `USTRUCT()`
- L14 _public member_ `double Amplitude = 1.0;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L18 _public member_ `double EasingTime = 1.0;` — `UPROPERTY(EditAnywhere, Category="Easing")` — Length of the easing in seconds
- L21 _public member_ `double OffsetX = 0.0;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L24 _public member_ `double OffsetY = 0.0;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L27 _public member_ `EPropertyAnimatorEasingType EasingType = EPropertyAnimatorEasingType::In;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L30 _public member_ `EPropertyAnimatorEasingFunction EasingFunction = EPropertyAnimatorEasingFunction::Sine;` — `UPROPERTY(EditAnywhere, Category="Easing")`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/MovieScene/PropertyAnimatorMovieSceneUtils.h` (Public)


#### struct `FPropertyAnimatorMovieSceneUtils`  
`struct FPropertyAnimatorMovieSceneUtils`  
_L10-15_
- L12 _public prototype_ `static FFrameTime GetBaseTime(const UMovieSceneSection& InSection, const UMovieScene& InMovieScene);`
- L14 _public prototype_ `static double GetBaseSeconds(const UMovieSceneSection& InSection);`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/MovieScene/Wave/PropertyAnimatorWaveDoubleChannel.h` (Public)


#### struct `FPropertyAnimatorWaveDoubleChannel`  
`struct FPropertyAnimatorWaveDoubleChannel : public FMovieSceneChannel`  
_L14-30_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L18 _public typedef_ `using CurveValueType = double;`
- L20 _public prototype_ `FPropertyAnimatorWaveDoubleChannel() = default;`
- L22 _public prototype_ `double Evaluate(double InBaseSeconds, double InSeconds) const;`
- L24 _public prototype_ `bool Evaluate(const UMovieSceneSection* InSection, FFrameTime InTime, double& OutValue) const;`
- L26 _public prototype_ `static double Evaluate(const FPropertyAnimatorWaveParameters& InParameters, double InSeconds);`
- L29 _public member_ `FPropertyAnimatorWaveParameters Parameters;` — `UPROPERTY(EditAnywhere, Category = "Wave")`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FPropertyAnimatorWaveDoubleChannel> : TMovieSceneChannelTraitsBase<FPropertyAnimatorWaveDoubleChannel>`  
_L33-39_
- inherits: `TMovieSceneChannelTraitsBase<FPropertyAnimatorWaveDoubleChannel>`
- L37 _public typedef_ `typedef TMovieSceneExternalValue<double> ExtendedEditorDataType;` — Wave Channels can have external values (they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L41 _function_ `inline bool EvaluateChannel(const UMovieSceneSection* InSection, const FPropertyAnimatorWaveDoubleChannel* InChannel, FFrameTime InTime, double& OutValue)`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/MovieScene/Wave/PropertyAnimatorWaveParameters.h` (Public)


#### struct `FPropertyAnimatorWaveParameters`  
`struct FPropertyAnimatorWaveParameters`  
_L9-27_
- reflection: `USTRUCT()`
- L14 _public member_ `double Amplitude = 1.0;` — `UPROPERTY(EditAnywhere, Category="Wave")`
- L17 _public member_ `double Frequency = 1.0;` — `UPROPERTY(EditAnywhere, Category="Wave")`
- L20 _public member_ `double OffsetX = 0.0;` — `UPROPERTY(EditAnywhere, Category="Wave")`
- L23 _public member_ `double OffsetY = 0.0;` — `UPROPERTY(EditAnywhere, Category="Wave")`
- L26 _public member_ `EPropertyAnimatorWaveFunction WaveFunction = EPropertyAnimatorWaveFunction::Sine;` — `UPROPERTY(EditAnywhere, Category="Wave")`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Properties/PropertyAnimatorFloatContext.h` (Public)


#### class `UPropertyAnimatorFloatContext`  
`class UPropertyAnimatorFloatContext : public UPropertyAnimatorCoreContext`  
_L10-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyAnimatorCoreContext`
- desc: Property context used by animator for float/double properties
- L15 _public prototype_ `void SetAmplitudeMin(double InAmplitude);`
- L16 _public function_ `double GetAmplitudeMin() const`
- L21 _public prototype_ `void SetAmplitudeMax(double InAmplitude);`
- L22 _public function_ `double GetAmplitudeMax() const`
- L30 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InProperty, const FInstancedPropertyBag& InAnimatorResult, FInstancedPropertyBag& OutEvaluatedValues) override;`
- L36 _protected prototype_ `virtual void OnAnimatedPropertyLinked() override;`
- L37 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L38 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L41 _protected prototype_ `double GetClampedAmplitude(double InAmplitude);`
- L45 _protected member_ `double AmplitudeMin = -1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — The minimum value should be remapped to that values
- L49 _protected member_ `TOptional<double> AmplitudeClampMin;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value
- L53 _protected member_ `double AmplitudeMax = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — The maximum value should be remapped to that values
- L57 _protected member_ `TOptional<double> AmplitudeClampMax;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Properties/PropertyAnimatorRotatorContext.h` (Public)


#### class `UPropertyAnimatorRotatorContext`  
`class UPropertyAnimatorRotatorContext : public UPropertyAnimatorCoreContext`  
_L10-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyAnimatorCoreContext`
- desc: Property context used by animator for rotator properties
- L15 _public prototype_ `void SetAmplitudeMin(const FRotator& InAmplitude);`
- L16 _public function_ `const FRotator& GetAmplitudeMin() const`
- L21 _public prototype_ `void SetAmplitudeMax(const FRotator& InAmplitude);`
- L22 _public function_ `const FRotator& GetAmplitudeMax() const`
- L30 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InProperty, const FInstancedPropertyBag& InAnimatorResult, FInstancedPropertyBag& OutEvaluatedValues) override;`
- L36 _protected prototype_ `virtual void OnAnimatedPropertyLinked() override;`
- L37 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L38 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L41 _protected prototype_ `FRotator GetClampedAmplitude(FRotator InAmplitude);`
- L45 _protected member_ `FRotator AmplitudeMin = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — The minimum value should be remapped to that values
- L49 _protected member_ `TOptional<FRotator> AmplitudeClampMin;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value
- L53 _protected member_ `FRotator AmplitudeMax = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — The maximum value should be remapped to that values
- L57 _protected member_ `TOptional<FRotator> AmplitudeClampMax;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/Properties/PropertyAnimatorVectorContext.h` (Public)


#### class `UPropertyAnimatorVectorContext`  
`class UPropertyAnimatorVectorContext : public UPropertyAnimatorCoreContext`  
_L10-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyAnimatorCoreContext`
- desc: Property context used by animator for vector properties
- L15 _public prototype_ `void SetAmplitudeMin(const FVector& InAmplitude);`
- L16 _public function_ `const FVector& GetAmplitudeMin() const`
- L21 _public prototype_ `void SetAmplitudeMax(const FVector& InAmplitude);`
- L22 _public function_ `const FVector& GetAmplitudeMax() const`
- L30 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _protected prototype_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InProperty, const FInstancedPropertyBag& InAnimatorResult, FInstancedPropertyBag& OutEvaluatedValues) override;`
- L36 _protected prototype_ `virtual void OnAnimatedPropertyLinked() override;`
- L37 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L38 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L41 _protected prototype_ `FVector GetClampedAmplitude(FVector InAmplitude);`
- L45 _protected member_ `FVector AmplitudeMin = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(AllowPreserveRatio))` — The minimum value should be remapped to that values
- L49 _protected member_ `TOptional<FVector> AmplitudeClampMin;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value
- L53 _protected member_ `FVector AmplitudeMax = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(AllowPreserveRatio))` — The maximum value should be remapped to that values
- L57 _protected member_ `TOptional<FVector> AmplitudeClampMax;` — `UPROPERTY()` — Some properties are clamped and cannot go past a specific min value

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Public/PropertyAnimatorShared.h` (Public)


#### enum `EPropertyAnimatorEasingType`  
`enum class EPropertyAnimatorEasingType : uint8`  
_L10-15_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `In`
- L13 _public enumerator_ `Out`
- L14 _public enumerator_ `InOut`

#### enum `EPropertyAnimatorEasingFunction`  
`enum class EPropertyAnimatorEasingFunction : uint8`  
_L18-31_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Linear`
- L21 _public enumerator_ `Sine`
- L22 _public enumerator_ `Quad`
- L23 _public enumerator_ `Cubic`
- L24 _public enumerator_ `Quart`
- L25 _public enumerator_ `Quint`
- L26 _public enumerator_ `Expo`
- L27 _public enumerator_ `Circ`
- L28 _public enumerator_ `Back`
- L29 _public enumerator_ `Elastic`
- L30 _public enumerator_ `Bounce`

#### enum `EPropertyAnimatorWaveFunction`  
`enum class EPropertyAnimatorWaveFunction : uint8`  
_L34-45_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `Sine`
- L37 _public enumerator_ `Cosine`
- L38 _public enumerator_ `Square`
- L39 _public enumerator_ `InvertedSquare`
- L40 _public enumerator_ `Sawtooth`
- L41 _public enumerator_ `Triangle`
- L42 _public enumerator_ `Bounce`
- L43 _public enumerator_ `Pulse`
- L44 _public enumerator_ `Perlin`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace PropertyAnimator` (scope `UE`)
- L50 _namespace_ `namespace Easing` (scope `UE::PropertyAnimator`)
- L52 _prototype_ `float Ease(float InProgress, EPropertyAnimatorEasingFunction InFunction, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L54 _prototype_ `float Linear(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L55 _prototype_ `float Sine(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L56 _prototype_ `float Quad(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L57 _prototype_ `float Cubic(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L58 _prototype_ `float Quart(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L59 _prototype_ `float Quint(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L60 _prototype_ `float Expo(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L61 _prototype_ `float Circ(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L62 _prototype_ `float Back(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L63 _prototype_ `float Elastic(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L64 _prototype_ `float Bounce(float InProgress, EPropertyAnimatorEasingType InType);` (scope `UE::PropertyAnimator::Easing`)
- L68 _namespace_ `namespace Wave` (scope `UE::PropertyAnimator`)
- L70 _prototype_ `double Wave(double InTime, double InAmplitude, double InFrequency, double InOffset, EPropertyAnimatorWaveFunction InFunction);` (scope `UE::PropertyAnimator::Wave`)
- L72 _prototype_ `double Sine(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L73 _prototype_ `double Cosine(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L74 _prototype_ `double Square(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L75 _prototype_ `double InvertedSquare(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L76 _prototype_ `double Sawtooth(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L77 _prototype_ `double Triangle(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L78 _prototype_ `double Bounce(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L79 _prototype_ `double Pulse(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
- L80 _prototype_ `double Perlin(double InTime, double InAmplitude, double InFrequency, double InOffset);` (scope `UE::PropertyAnimator::Wave`)
