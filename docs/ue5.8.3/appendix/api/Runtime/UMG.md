# Runtime / UMG

- module root: `Source/Runtime/UMG`
- headers: 168; symbols: 5156
- symbol kinds: class=168, delegate=125, enum=30, enumerator=121, function=433, macro=17, member=1265, namespace=13, prototype=2919, struct=52, typedef=13
- DynamicallyLoadedModuleNames: ImageWrapper
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, InputCore, RHI, RenderCore, Renderer, Slate, SlateCore, SlateRHIRenderer, TraceLog
- PrivateIncludePathModuleNames: ImageWrapper, SlateRHIRenderer, TargetPlatform
- PublicDependencyModuleNames: FieldNotification, HTTP, MovieScene, MovieSceneTracks, PropertyPath, TimeManagement

### `Source/Runtime/UMG/Private/Animation/MovieSceneMarginPropertySystem.h` (Private)


#### class `UMovieSceneMarginPropertySystem`  
`class UMovieSceneMarginPropertySystem : public UMovieScenePropertySystem`  
_L12-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L18 _public prototype_ `UMovieSceneMarginPropertySystem(const FObjectInitializer& ObjInit);`
- L20 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

#### Free symbols / members of external scopes

- L9 _prototype_ `Expose_TNameOf(FMargin);`

### `Source/Runtime/UMG/Private/Binding/WidgetFieldNotificationExtension.h` (Private)


#### class `UWidgetFieldNotificationExtension`  
`class UWidgetFieldNotificationExtension : public UUserWidgetExtension`  
_L15-63_
- reflection: `UCLASS(MinimalAPI, Transient, NotBlueprintType)`
- inherits: `UUserWidgetExtension`
- L20 _public typedef_ `using FDelegate = UE::FieldNotification::FFieldMulticastDelegate::FDelegate;`
- L21 _public typedef_ `using FFieldId = UE::FieldNotification::FFieldId;`
- L22 _public typedef_ `using FRemoveFromResult = UE::FieldNotification::FFieldMulticastDelegate::FRemoveFromResult;`
- L23 _public typedef_ `using FRemoveAllResult = UE::FieldNotification::FFieldMulticastDelegate::FRemoveAllResult;`
- L26 _public function_ `FDelegateHandle AddFieldValueChangedDelegate(const UVisual* InObject, FFieldId InFieldId, FDelegate InNewDelegate)`
- L31 _public function_ `FDelegateHandle AddFieldValueChangedDelegate(const UVisual* InObject, FFieldId InFieldId, const FFieldValueChangedDynamicDelegate& InDelegate)`
- L36 _public function_ `FRemoveFromResult RemoveFieldValueChangedDelegate(const UVisual* InObject, FFieldId InFieldId, FDelegateHandle InDelegateHandle)`
- L41 _public function_ `FRemoveFromResult RemoveFieldValueChangedDelegate(const UVisual* InObject, FFieldId InFieldId, const FFieldValueChangedDynamicDelegate& InDelegate)`
- L46 _public function_ `FRemoveAllResult RemoveAllFieldValueChangedDelegates(const UVisual* InObject, FDelegateUserObjectConst InUserObject)`
- L51 _public function_ `FRemoveAllResult RemoveAllFieldValueChangedDelegates(const UVisual* InObject, FFieldId InFieldId, FDelegateUserObjectConst InUserObject)`
- L56 _public function_ `void BroadcastFieldValueChanged(UVisual* InObject, UE::FieldNotification::FFieldId InFieldId)`
- L62 _private member_ `UE::FieldNotification::FFieldMulticastDelegate Delegates;`

### `Source/Runtime/UMG/Private/Blueprint/ListViewDesignerPreviewItem.h` (Private)


#### class `UListViewDesignerPreviewItem`  
`class UListViewDesignerPreviewItem : public UObject`  
_L11-14_
- reflection: `UCLASS(Transient, Within = ListView)`
- inherits: `UObject`
- desc: Empty dummy UObject used as the table view item during design time Allows rough design-time previewing of how list contents will lay out

### `Source/Runtime/UMG/Private/UMGPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUMG, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUMG, Log, All);`

### `Source/Runtime/UMG/Public/Animation/MovieScene2DTransformPropertySystem.h` (Public)


#### class `UMovieScene2DTransformPropertySystem`  
`class UMovieScene2DTransformPropertySystem : public UMovieScenePropertySystem`  
_L9-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _public prototype_ `UMovieScene2DTransformPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/UMG/Public/Animation/MovieScene2DTransformSection.h` (Public)


#### enum `EMovieScene2DTransformChannel`  
`enum class EMovieScene2DTransformChannel : uint32`  
_L15-34_
- L17 _public enumerator_ `None = 0x000`
- L19 _public enumerator_ `TranslationX = 0x001`
- L20 _public enumerator_ `TranslationY = 0x002`
- L21 _public enumerator_ `Translation = TranslationX | TranslationY`
- L23 _public enumerator_ `Rotation = 0x004`
- L25 _public enumerator_ `ScaleX = 0x008`
- L26 _public enumerator_ `ScaleY = 0x010`
- L27 _public enumerator_ `Scale = ScaleX | ScaleY`
- L29 _public enumerator_ `ShearX = 0x020`
- L30 _public enumerator_ `ShearY = 0x040`
- L31 _public enumerator_ `Shear = ShearX | ShearY`
- L33 _public enumerator_ `AllTransform = Translation | Rotation | Scale | Shear`

#### struct `FMovieScene2DTransformMask`  
`struct FMovieScene2DTransformMask`  
_L38-93_
- reflection: `USTRUCT()`
- L42 _public function_ `FMovieScene2DTransformMask() : Mask(0)`
- L46 _public function_ `FMovieScene2DTransformMask(EMovieScene2DTransformChannel Channel) : Mask((__underlying_type(EMovieScene2DTransformChannel))Channel)`
- L50 _public function_ `EMovieScene2DTransformChannel GetChannels() const`
- L55 _public function_ `FVector2D GetTranslationFactor() const`
- L63 _public function_ `float GetRotationFactor() const`
- L73 _public function_ `FVector2D GetScaleFactor() const`
- L81 _public function_ `FVector2D GetShearFactor() const`
- L92 _private member_ `uint32 Mask;` — `UPROPERTY()`

#### class `UMovieScene2DTransformSection`  
`class UMovieScene2DTransformSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L99-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A transform section
- L110 _public prototype_ `FMovieScene2DTransformMask GetMask() const;` — Access the mask that defines which channels this track should animate
- L115 _public prototype_ `void SetMask(FMovieScene2DTransformMask NewMask);` — Set the mask that defines which channels this track should animate
- L120 _public prototype_ `FMovieScene2DTransformMask GetMaskByName(const FName& InName) const;` — Get the mask by name
- L122 _public prototype_ `FWidgetTransform GetCurrentValue(const UObject* Object) const;`
- L126 _protected prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L130 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L135 _public member_ `FMovieScene2DTransformMask TransformMask;` — `UPROPERTY()`
- L139 _public member_ `FMovieSceneFloatChannel Translation[2];` — `UPROPERTY()` — Translation curves
- L143 _public member_ `FMovieSceneFloatChannel Rotation;` — `UPROPERTY()` — Rotation curve
- L147 _public member_ `FMovieSceneFloatChannel Scale[2];` — `UPROPERTY()` — Scale curves
- L151 _public member_ `FMovieSceneFloatChannel Shear[2];` — `UPROPERTY()` — Shear curve

### `Source/Runtime/UMG/Public/Animation/MovieScene2DTransformTrack.h` (Public)


#### class `UMovieScene2DTransformTrack`  
`class UMovieScene2DTransformTrack : public UMovieScenePropertyTrack`  
_L17-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of 2D transforms in a movie scene
- L24 _public prototype_ `UMovieScene2DTransformTrack(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L28 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/UMG/Public/Animation/MovieSceneMarginSection.h` (Public)


#### class `UMovieSceneMarginSection`  
`class UMovieSceneMarginSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L19-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A section in a Margin track
- L29 _public member_ `FMovieSceneFloatChannel TopCurve;` — `UPROPERTY()` — Red curve data
- L33 _public member_ `FMovieSceneFloatChannel LeftCurve;` — `UPROPERTY()` — Green curve data
- L37 _public member_ `FMovieSceneFloatChannel RightCurve;` — `UPROPERTY()` — Blue curve data
- L41 _public member_ `FMovieSceneFloatChannel BottomCurve;` — `UPROPERTY()` — Alpha curve data
- L45 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L46 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`

### `Source/Runtime/UMG/Public/Animation/MovieSceneMarginTrack.h` (Public)


#### class `UMovieSceneMarginTrack`  
`class UMovieSceneMarginTrack : public UMovieScenePropertyTrack`  
_L14-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of FMargins in a movie scene
- L20 _public prototype_ `UMovieSceneMarginTrack(const FObjectInitializer& Init);`
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/UMG/Public/Animation/MovieSceneUMGComponentTypes.h` (Public)


#### struct `UE::MovieScene::FWidgetMaterialPath`  
`struct FWidgetMaterialPath`  
_L21-29_
- L23 _public prototype_ `FWidgetMaterialPath() = default;`
- L24 _public function_ `FWidgetMaterialPath(TArrayView<const FName> Names) : Path(Names.GetData(), Names.Num())`
- L28 _public member_ `TArray<FName, TInlineAllocator<2>> Path;`

#### struct `UE::MovieScene::FIntermediateWidgetTransform`  
`struct FIntermediateWidgetTransform`  
_L31-40_
- L33 _public member_ `double TranslationX;`
- L34 _public member_ `double TranslationY;`
- L35 _public member_ `double Rotation;`
- L36 _public member_ `double ScaleX;`
- L37 _public member_ `double ScaleY;`
- L38 _public member_ `double ShearX;`
- L39 _public member_ `double ShearY;`

#### struct `UE::MovieScene::FIntermediateMargin`  
`struct FIntermediateMargin`  
_L44-50_
- L46 _public member_ `double Left;`
- L47 _public member_ `double Top;`
- L48 _public member_ `double Right;`
- L49 _public member_ `double Bottom;`

#### struct `UE::MovieScene::FMovieSceneUMGComponentTypes`  
`struct FMovieSceneUMGComponentTypes`  
_L60-79_
- L62 _public prototype_ `~FMovieSceneUMGComponentTypes();`
- L64 _public member_ `TPropertyComponents<FMarginTraits> Margin;`
- L65 _public member_ `TPropertyComponents<FWidgetTransformPropertyTraits> WidgetTransform;`
- L67 _public member_ `TComponentTypeID<FWidgetMaterialPath> WidgetMaterialPath;`
- L68 _public member_ `TComponentTypeID<FWidgetMaterialHandle> WidgetMaterialHandle;`
- L70 _public member_ `TCustomPropertyRegistration<FMarginTraits, 1> CustomMarginAccessors;`
- L71 _public member_ `TCustomPropertyRegistration<FWidgetTransformPropertyTraits, 1> CustomWidgetTransformAccessors;`
- L73 _public prototype_ `static void Destroy();`
- L75 _public prototype_ `static FMovieSceneUMGComponentTypes* Get();`
- L78 _private prototype_ `FMovieSceneUMGComponentTypes();`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieScene` (scope `UE`)
- L41 _prototype_ `void ConvertOperationalProperty(const FIntermediateWidgetTransform& In, FWidgetTransform& Out);` (scope `UE::MovieScene`)
- L42 _prototype_ `void ConvertOperationalProperty(const FWidgetTransform& In, FIntermediateWidgetTransform& Out);` (scope `UE::MovieScene`)
- L51 _prototype_ `void ConvertOperationalProperty(const FIntermediateMargin& In, FMargin& Out);` (scope `UE::MovieScene`)
- L52 _prototype_ `void ConvertOperationalProperty(const FMargin& In, FIntermediateMargin& Out);` (scope `UE::MovieScene`)
- L54 _prototype_ `void UnpackChannelsFromOperational(const FIntermediateMargin& In, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L55 _prototype_ `void UnpackChannelsFromOperational(const FIntermediateWidgetTransform& In, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L57 _typedef_ `using FMarginTraits = TPropertyTraits<FMargin, FIntermediateMargin>;` (scope `UE::MovieScene`)
- L58 _typedef_ `using FWidgetTransformPropertyTraits = TPropertyTraits<FWidgetTransform, FIntermediateWidgetTransform>;` (scope `UE::MovieScene`)

### `Source/Runtime/UMG/Public/Animation/MovieSceneWidgetMaterialSystem.h` (Public)


#### struct `UE::MovieScene::FWidgetMaterialKey`  
`struct FWidgetMaterialKey`  
_L19-32_
- L21 _public member_ `FObjectKey Object;`
- L22 _public member_ `FWidgetMaterialHandle WidgetMaterialHandle;`

#### struct `UE::MovieScene::FWidgetMaterialAccessor`  
`struct FWidgetMaterialAccessor`  
_L34-50_
- L36 _public typedef_ `using KeyType = FWidgetMaterialKey;`
- L38 _public member_ `UWidget* Widget;`
- L39 _public member_ `FWidgetMaterialHandle WidgetMaterialHandle;`
- L41 _public prototype_ `FWidgetMaterialAccessor(const FWidgetMaterialKey& InKey);`
- L42 _public prototype_ `FWidgetMaterialAccessor(UObject* InObject, FWidgetMaterialHandle InWidgetMaterialHandle);`
- L44 _public prototype_ `explicit operator bool() const;`
- L46 _public prototype_ `UMaterialInterface* GetMaterial() const;`
- L47 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);`
- L48 _public prototype_ `UMaterialInstanceDynamic* CreateDynamicMaterial(UMaterialInterface* InMaterial);`
- L49 _public prototype_ `FString ToString() const;`

#### struct `UE::MovieScene::FPreAnimatedWidgetMaterialSwitcherStorage`  
`struct FPreAnimatedWidgetMaterialSwitcherStorage : public TPreAnimatedStateStorage<TPreAnimatedMaterialTraits<FWidgetMaterialAccessor, UObject*, FWidgetMaterialHandle>>`  
_L55-59_
- inherits: `TPreAnimatedStateStorage<TPreAnimatedMaterialTraits<FWidgetMaterialAccessor,UObject*,FWidgetMaterialHandle>>`
- L58 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedWidgetMaterialSwitcherStorage> StorageID;`

#### struct `UE::MovieScene::FPreAnimatedWidgetMaterialParameterStorage`  
`struct FPreAnimatedWidgetMaterialParameterStorage : public TPreAnimatedStateStorage<TPreAnimatedMaterialParameterTraits<FWidgetMaterialAccessor, UObject*, FWidgetMaterialHandle>>`  
_L61-65_
- inherits: `TPreAnimatedStateStorage<TPreAnimatedMaterialParameterTraits<FWidgetMaterialAccessor,UObject*,FWidgetMaterialHandle>>`
- L64 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedWidgetMaterialParameterStorage> StorageID;`

#### class `UMovieSceneWidgetMaterialSystem`  
`class UMovieSceneWidgetMaterialSystem : public UMovieSceneEntitySystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L71-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem,IMovieScenePreAnimatedStateSystemInterface`
- L79 _public prototype_ `UMovieSceneWidgetMaterialSystem(const FObjectInitializer& ObjInit);`
- L83 _private prototype_ `virtual void OnLink() override;`
- L84 _private prototype_ `virtual void OnUnlink() override;`
- L85 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L87 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L91 _private member_ `UE::MovieScene::TMovieSceneMaterialSystem<UE::MovieScene::FWidgetMaterialAccessor, UObject*, FWidgetMaterialHandle> SystemImpl;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L24 _function_ `friend uint32 GetTypeHash(const FWidgetMaterialKey& In)` (scope `UE::MovieScene`)
- L28 _function_ `friend bool operator==(const FWidgetMaterialKey& A, const FWidgetMaterialKey& B)` (scope `UE::MovieScene`)
- L52 _typedef_ `using FPreAnimatedWidgetMaterialTraits = TPreAnimatedMaterialTraits<FWidgetMaterialAccessor, UObject*, FWidgetMaterialHandle>;` (scope `UE::MovieScene`)
- L53 _typedef_ `using FPreAnimatedWidgetMaterialParameterTraits = TPreAnimatedMaterialParameterTraits<FWidgetMaterialAccessor, UObject*, FWidgetMaterialHandle>;` (scope `UE::MovieScene`)

### `Source/Runtime/UMG/Public/Animation/MovieSceneWidgetMaterialTrack.h` (Public)


#### class `UMovieSceneWidgetMaterialTrack`  
`class UMovieSceneWidgetMaterialTrack : public UMovieSceneMaterialTrack , public IMovieSceneEntityProvider , public IMovieSceneParameterSectionExtender`  
_L30-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneMaterialTrack,IMovieSceneEntityProvider,IMovieSceneParameterSectionExtender`
- desc: A material track which is specialized for materials which are owned by widget brushes.
- L40 _public prototype_ `virtual FName GetTrackName() const override;` — UMovieSceneTrack interface
- L42 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L43 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L46 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneEntityProvider
- L47 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L50 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneParameterSectionExtender
- L53 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L59 _public function_ `const TArray<FName>& GetBrushPropertyNamePath() const` — Gets name of the brush property which has the material to animate.
- L62 _public prototype_ `void SetBrushPropertyNamePath( TArray<FName> InBrushPropertyNamePath );` — Sets the name of the brush property which has the material to animate.
- L68 _private member_ `TArray<FName> BrushPropertyNamePath;` — `UPROPERTY()` — The name of the brush property which will be animated by this track.
- L72 _private member_ `FName TrackName;` — `UPROPERTY()` — The name of this track, generated from the property name path.

### `Source/Runtime/UMG/Public/Animation/UMGSequencePlayer.h` (Public)


#### class `UUMGSequencePlayer`  
`class UUMGSequencePlayer : public UObject, public IMovieScenePlayer`  
_L19-146_
- reflection: `UCLASS(Transient, BlueprintType, MinimalAPI)`
- inherits: `UObject,IMovieScenePlayer`
- L25 _public prototype_ `UUMGSequencePlayer(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `void InitSequencePlayer(FWidgetAnimationState& InState);`
- L30 _public prototype_ `void InitSequencePlayer(UWidgetAnimation& InAnimation, UUserWidget& InUserWidget);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L34 _public prototype_ `void Tick(float DeltaTime);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Updates the running movie
- L38 _public prototype_ `void Play(float StartAtTime, int32 InNumLoopsToPlay, EUMGSequencePlayMode::Type InPlayMode, float InPlaybackSpeed, bool bRestoreState);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Begins playing or restarts an animation
- L42 _public prototype_ `void PlayTo(float StartAtTime, float EndAtTime, int32 InNumLoopsToPlay, EUMGSequencePlayMode::Type InPlayMode, float InPlaybackSpeed, bool bRestoreState);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Begins playing or restarts an animation  and plays to the specified end time
- L46 _public prototype_ `void Stop();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Stops a running animation and resets time
- L50 _public prototype_ `void Pause();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Pauses a running animation
- L54 _public prototype_ `void Reverse();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Reverses a running animation
- L57 _public prototype_ `void SetCurrentTime(float InTime);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L60 _public prototype_ `FQualifiedFrameTime GetCurrentTime() const;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L64 _public prototype_ `const UWidgetAnimation* GetAnimation() const;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — @return The current animation being played
- L68 _public prototype_ `FName GetUserTag() const;` — `UFUNCTION(BlueprintCallable, Category="Animation", meta=(DeprecatedFunction))` — @return
- L71 _public prototype_ `void SetUserTag(FName InUserTag);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(DeprecatedFunction))`
- L75 _public prototype_ `void SetNumLoopsToPlay(int32 InNumLoopsToPlay);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Sets the number of loops to play
- L79 _public prototype_ `void SetPlaybackSpeed(float PlaybackSpeed);` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Sets the animation playback rate
- L83 _public prototype_ `bool IsPlayingForward() const;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Gets the current time position in the player (in seconds).
- L87 _public prototype_ `bool IsStopping() const;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Check whether this player is currently being stopped
- L92 _public prototype_ `virtual FMovieSceneRootEvaluationTemplateInstance& GetEvaluationTemplate() override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L95 _public prototype_ `virtual UMovieSceneEntitySystemLinker* ConstructEntitySystemLinker() override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L98 _public prototype_ `virtual UObject* AsUObject() override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L101 _public prototype_ `virtual EMovieScenePlayerStatus::Type GetPlaybackStatus() const override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L104 _public prototype_ `virtual void SetPlaybackStatus(EMovieScenePlayerStatus::Type InPlaybackStatus) override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L107 _public prototype_ `virtual IMovieScenePlaybackClient* GetPlaybackClient() override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L110 _public prototype_ `virtual FMovieSceneSpawnRegister& GetSpawnRegister() override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L113 _public prototype_ `virtual UObject* GetPlaybackContext() const override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L116 _public prototype_ `virtual void InitializeRootInstance(TSharedRef<UE::MovieScene::FSharedPlaybackState> NewSharedPlaybackState) override;` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L120 _public prototype_ `virtual void BeginDestroy() override;`
- L124 _public prototype_ `void RemoveEvaluationData();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")` — Disable this sequence player by removing any of its animation data from the entity manager
- L127 _public prototype_ `void TearDown();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L129 _public prototype_ `DECLARE_EVENT_OneParam(UUMGSequencePlayer, FOnSequenceFinishedPlaying, UUMGSequencePlayer&);`
- L132 _public prototype_ `FOnSequenceFinishedPlaying& OnSequenceFinishedPlaying();` — `UE_DEPRECATED(5.6, "Please use FWidgetAnimationHandle and FWidgetAnimationState")`
- L137 _public prototype_ `void BroadcastSequenceFinishedPlaying();` — Internal API.
- L141 _private member_ `FWidgetAnimationHandle WidgetAnimationHandle;`
- L143 _private member_ `FMovieSceneRootEvaluationTemplateInstance RootTemplateInstance;`
- L145 _private member_ `FOnSequenceFinishedPlaying OnSequenceFinishedPlayingEvent;`

#### Free symbols / members of external scopes

- L129 _delegate_ `DECLARE_EVENT_OneParam(UUMGSequencePlayer, FOnSequenceFinishedPlaying, UUMGSequencePlayer&);`

### `Source/Runtime/UMG/Public/Animation/UMGSequenceTickManager.h` (Public)


#### struct `FSequenceTickManagerWidgetData`  
`struct FSequenceTickManagerWidgetData`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `bool bIsTicking = true;` — The widget was ticked.
- L25 _public member_ `bool bActionsAndAnimationTicked = false;` — The widget's animation was ticked this frame.

#### class `UUMGSequenceTickManager`  
`class UUMGSequenceTickManager : public UObject`  
_L33-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An automatically created global object that will manage all widget animations.
- L38 _public prototype_ `UUMGSequenceTickManager(const FObjectInitializer& Init);`
- L40 _public prototype_ `void Initialize(UObject* Owner);`
- L42 _public function_ `UMovieSceneEntitySystemLinker* GetLinker()`
- L43 _public function_ `TSharedPtr<FMovieSceneEntitySystemRunner> GetRunner()`
- L45 _public prototype_ `void AddLatentAction(FMovieSceneSequenceLatentActionDelegate Delegate);`
- L46 _public prototype_ `void ClearLatentActions(UObject* Object);`
- L47 _public prototype_ `void RunLatentActions();`
- L49 _public prototype_ `static UUMGSequenceTickManager* Get(UObject* PlaybackContext);`
- L51 _public prototype_ `void ForceFlush();`
- L53 _public prototype_ `void AddWidget(UUserWidget* InWidget);`
- L54 _public prototype_ `void RemoveWidget(UUserWidget* InWidget);`
- L56 _public prototype_ `void OnWidgetTicked(UUserWidget* InWidget);`
- L59 _private prototype_ `virtual void BeginDestroy() override;`
- L61 _private prototype_ `void HandleSlatePostTick(float DeltaSeconds);`
- L62 _private prototype_ `void TickWidgetAnimations(float DeltaSeconds);`
- L63 _private prototype_ `bool TickWidgetAnimations( float DeltaSeconds, UUserWidget* UserWidget, FSequenceTickManagerWidgetData& UserWidgetData, bool bIsCurrentlyEvaluating);`
- L72 _private member_ `TMap<TWeakObjectPtr<UUserWidget>, FSequenceTickManagerWidgetData> WeakUserWidgetData;` — `UPROPERTY(transient)`
- L75 _private member_ `TArray<TObjectPtr<UUserWidget>> PendingUserWidgets;` — `UPROPERTY(transient)`
- L78 _private member_ `TObjectPtr<UMovieSceneEntitySystemLinker> Linker;` — `UPROPERTY(transient)`
- L80 _private member_ `TSharedPtr<FMovieSceneEntitySystemRunner> Runner;`
- L82 _private member_ `FDelegateHandle SlateApplicationPreTickHandle, SlateApplicationPostTickHandle;`
- L82 _private member_ `FDelegateHandle SlateApplicationPreTickHandle, SlateApplicationPostTickHandle;`
- L84 _private member_ `FMovieSceneLatentActionManager LatentActionManager;`
- L86 _private member_ `bool bIsTicking;`

### `Source/Runtime/UMG/Public/Animation/WidgetAnimation.h` (Public)


#### class `UWidgetAnimation`  
`class UWidgetAnimation : public UMovieSceneSequence`  
_L25-158_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneSequence`
- L37 _public prototype_ `static UWidgetAnimation* GetNullAnimation();` — Get a placeholder animation. @return Placeholder animation.
- L40 _public function_ `const FString& GetDisplayLabel() const` — @return The friendly name of the animation
- L46 _public prototype_ `void SetDisplayLabel(const FString& InDisplayLabel);` — Sets the friendly name of the animation to display in the editor
- L49 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the DisplayLabel if set, otherwise the object name
- L59 _public prototype_ `float GetStartTime() const;` — `UFUNCTION(BlueprintCallable, Category="Animation")` — Get the start time of this animation. @return Start time in seconds. @see GetEndTime
- L68 _public prototype_ `float GetEndTime() const;` — `UFUNCTION(BlueprintCallable, Category="Animation")` — Get the end time of this animation. @return End time in seconds. @see GetStartTime
- L77 _public prototype_ `void BindToAnimationStarted(UUserWidget* Widget, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta=(BlueprintInternalUseOnly = "TRUE"))`
- L80 _public prototype_ `void UnbindFromAnimationStarted(UUserWidget* Widget, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta = (BlueprintInternalUseOnly = "TRUE"))`
- L83 _public prototype_ `void UnbindAllFromAnimationStarted(UUserWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta = (BlueprintInternalUseOnly = "TRUE"))`
- L86 _public prototype_ `void BindToAnimationFinished(UUserWidget* Widget, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta = (BlueprintInternalUseOnly = "TRUE"))`
- L89 _public prototype_ `void UnbindFromAnimationFinished(UUserWidget* Widget, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta = (BlueprintInternalUseOnly = "TRUE"))`
- L92 _public prototype_ `void UnbindAllFromAnimationFinished(UUserWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category = Animation, meta = (BlueprintInternalUseOnly = "TRUE"))`
- L97 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;` — UMovieSceneAnimation overrides
- L98 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L99 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L100 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L101 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L102 _public function_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* InContext) override`
- L103 _public function_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* InContext) override`
- L104 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, const UE::UniversalObjectLocator::FResolveParams& ResolveParams, TSharedPtr<const FSharedPlaybackState> SharedPlaybackState, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L105 _public prototype_ `virtual UObject* CreateDirectorInstance(TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID SequenceID) override;`
- L109 _public prototype_ `virtual void IterateDynamicBindings(TFunction<void(const FGuid&, FMovieSceneDynamicBinding&)> InCallback) override;`
- L110 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L111 _public prototype_ `virtual bool IsFilterSupportedImpl(const FString& InFilterName) const override;`
- L112 _public prototype_ `virtual const FSlateBrush* GetCustomBrushForBinding(FGuid BindingID) const override;`
- L114 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFixupWidgetDynamicBindingsEvent, UWidgetAnimation*);`
- L115 _public member_ `static FFixupWidgetDynamicBindingsEvent FixupWidgetDynamicBindingsEvent;`
- L120 _public prototype_ `virtual bool IsPostLoadThreadSafe() const override;`
- L124 _public function_ `const TArray<FWidgetAnimationBinding>& GetBindings() const` — Get Animation bindings of the animation
- L127 _public prototype_ `void RemoveBinding(const UObject& PossessedObject);` — Remove Animation Binding
- L128 _public prototype_ `void RemoveBinding(const FWidgetAnimationBinding& Binding);`
- L132 _public function_ `bool GetLegacyFinishOnStop() const` — Whether to finish evaluation on stop
- L137 _protected prototype_ `virtual void PostLoad() override;` — Called after this object has been deserialized
- L143 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()` — Pointer to the movie scene that controls this animation.
- L147 _public member_ `TArray<FWidgetAnimationBinding> AnimationBindings;` — `UPROPERTY()`
- L153 _private member_ `bool bLegacyFinishOnStop;` — `UPROPERTY()` — Whether to finish evaluation on stop. This legacy value is to preserve existing asset behavior to NOT finish on stop since content was created with this bug. If this is removed, evaluation should always finish on stop.
- L157 _private member_ `FString DisplayLabel;` — `UPROPERTY()` — The friendly name for this animation displayed in the designer.

#### Free symbols / members of external scopes

- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFixupWidgetDynamicBindingsEvent, UWidgetAnimation*);`

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationBinding.h` (Public)


#### struct `FWidgetAnimationBinding`  
`struct FWidgetAnimationBinding`  
_L26-67_
- reflection: `USTRUCT()`
- desc: A single object bound to a UMG sequence.
- L31 _public member_ `FName WidgetName;` — `UPROPERTY()`
- L34 _public member_ `FName SlotWidgetName;` — `UPROPERTY()`
- L37 _public member_ `FGuid AnimationGuid;` — `UPROPERTY()`
- L40 _public member_ `bool bIsRootWidget = false;` — `UPROPERTY()`
- L43 _public member_ `FMovieSceneDynamicBinding DynamicBinding;` — `UPROPERTY()`
- L52 _public prototype_ `UObject* FindRuntimeObject(const UWidgetTree& WidgetTree, UUserWidget& UserWidget) const;` — `UE_DEPRECATED(5.5, "Please use the version that takes a SharedPlaybackState and Sequence")` — Locates a runtime object to animate from the provided tree of widgets. @return the runtime object to animate or null if not found
- L54 _public prototype_ `UObject* FindRuntimeObject(const UWidgetTree& WidgetTree, UUserWidget& UserWidget, const UMovieSceneSequence* Sequence, TSharedPtr<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L63 _function_ `friend bool operator==(const FWidgetAnimationBinding& X, const FWidgetAnimationBinding& Y)` — Compares two widget animation bindings for equality. @param X The first binding to compare. @param Y The second binding to compare. @return true if the bindings are equal, false otherwise.

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationDelegateBinding.h` (Public)


#### struct `FBlueprintWidgetAnimationDelegateBinding`  
`struct FBlueprintWidgetAnimationDelegateBinding`  
_L14-37_
- reflection: `USTRUCT()`
- L19 _public member_ `EWidgetAnimationEvent Action;` — `UPROPERTY()`
- L22 _public member_ `FName AnimationToBind;` — `UPROPERTY()`
- L25 _public member_ `FName FunctionNameToBind;` — `UPROPERTY()`
- L28 _public member_ `FName UserTag;` — `UPROPERTY()`
- L30 _public function_ `FBlueprintWidgetAnimationDelegateBinding() : Action(EWidgetAnimationEvent::Started) , AnimationToBind(NAME_None) , FunctionNameToBind(NAME_None) , UserTag(NAME_None)`

#### class `UWidgetAnimationDelegateBinding`  
`class UWidgetAnimationDelegateBinding : public UDynamicBlueprintBinding`  
_L40-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicBlueprintBinding`
- L45 _private member_ `TArray<FBlueprintWidgetAnimationDelegateBinding> WidgetAnimationDelegateBindings;` — `UPROPERTY()`
- L47 _private prototype_ `virtual void BindDynamicDelegates(UObject* InInstance) const override;`

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationEvents.h` (Public)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetAnimationPlaybackStatusChanged);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetAnimationPlaybackStatusChanged);` — `UDELEGATE()`
- L13 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FWidgetAnimationDynamicEvent);`
- L13 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FWidgetAnimationDynamicEvent);` — `UDELEGATE()`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWidgetAnimationDynamicEvents);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWidgetAnimationDynamicEvents);` — `UDELEGATE()`

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationHandle.h` (Public)


#### struct `FWidgetAnimationHandle`  
`struct FWidgetAnimationHandle`  
_L21-77_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to an ongoing or finished widget animation.
- L28 _public prototype_ `FWidgetAnimationHandle();` — Creates an invalid handle.
- L31 _public prototype_ `FWidgetAnimationState* GetAnimationState() const;` — Gets the animation state.
- L34 _public prototype_ `TSharedPtr<FWidgetAnimationState> PinAnimationState() const;` — Gets the animation state.
- L39 _public prototype_ `UUMGSequencePlayer* GetSequencePlayer() const;` — For backwards compatibility in C++ code.
- L40 _public function_ `inline operator UUMGSequencePlayer*() const`
- L48 _public prototype_ `bool IsValid() const;` — Returns whether this handle is valid. A valid handle may still return a null animation state if the animation has finished playing.
- L51 _public prototype_ `FName GetUserTag() const;` — Gets the user tag associated with the running animation.
- L54 _public prototype_ `void SetUserTag(FName InUserTag);` — Sets the user tag associated with the running animation.
- L67 _private prototype_ `FWidgetAnimationHandle(TSharedPtr<FWidgetAnimationState> InState);` — Creates a handle for the given running animation on the given widget.
- L72 _private member_ `TWeakPtr<FWidgetAnimationState> WeakState;` — Weak pointer to the animation state.

#### class `UWidgetAnimationHandleFunctionLibrary`  
`class UWidgetAnimationHandleFunctionLibrary : public UBlueprintFunctionLibrary`  
_L80-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L87 _public prototype_ `static FName GetUserTag(const FWidgetAnimationHandle& Target);` — `UFUNCTION(BlueprintPure, Category = "UMG")`
- L90 _public prototype_ `static void SetUserTag(UPARAM(ref) FWidgetAnimationHandle& Target, FName InUserTag);` — `UFUNCTION(BlueprintCallable, Category = "UMG")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UMG_API`
- L59 _function_ `friend uint32 GetTypeHash(const FWidgetAnimationHandle& Handle)` — Type hash for using handles in maps and other containers.

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationPlayCallbackProxy.h` (Public)


#### class `UWidgetAnimationPlayCallbackProxy`  
`class UWidgetAnimationPlayCallbackProxy : public UObject`  
_L18-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L24 _private member_ `FWidgetAnimationResult Finished;` — `UPROPERTY(BlueprintAssignable)` — Called when animation has been completed
- L31 _private prototype_ `static UWidgetAnimationPlayCallbackProxy* CreatePlayAnimationProxyObject( UUMGSequencePlayer*& Result, UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f);` — `UFUNCTION(BlueprintCallable , Category = "User Interface|Animation", meta = ( BlueprintInternalUseOnly = "true", DisplayName = "Play Animation with Finished event (legacy)", ShortToolTip = "Play Animation and trigger event on Finished (legacy version using deprecated UMG Sequencer Player)", ToolTip="Play Animation on widget and trigger Finish event when the animation is done (legacy version using deprecated UMG Sequencer Player)."))`
- L45 _private prototype_ `static UWidgetAnimationPlayCallbackProxy* NewPlayAnimationProxyObject( FWidgetAnimationHandle& Result, UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f);` — `UFUNCTION(BlueprintCallable , Category = "User Interface|Animation", meta = ( BlueprintInternalUseOnly = "true", DisplayName = "Play Animation with Finished event", ShortToolTip = "Play Animation and trigger event on Finished", ToolTip="Play Animation on widget and trigger Finish event when the animation is done."))`
- L59 _private prototype_ `static UWidgetAnimationPlayCallbackProxy* CreatePlayAnimationTimeRangeProxyObject( UUMGSequencePlayer*& Result, UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, float EndAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Animation", meta = ( BlueprintInternalUseOnly = "true", DisplayName = "Play Animation Time Range with Finished event (legacy)", ShortToolTip = "Play Animation Time Range and trigger event on Finished (legacy version using deprecated UMG Sequencer Player)", ToolTip = "Play Animation Time Range on widget and trigger Finish event when the animation is done (legacy version using deprecated UMG Sequencer Player)."))`
- L74 _private prototype_ `static UWidgetAnimationPlayCallbackProxy* NewPlayAnimationTimeRangeProxyObject( FWidgetAnimationHandle& Result, UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, float EndAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Animation", meta = ( BlueprintInternalUseOnly = "true", DisplayName = "Play Animation Time Range with Finished event", ShortToolTip = "Play Animation Time Range and trigger event on Finished", ToolTip = "Play Animation Time Range on widget and trigger Finish event when the animation is done."))`
- L86 _private prototype_ `void ExecutePlayAnimation(UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, EUMGSequencePlayMode::Type PlayMode, float PlaybackSpeed);`
- L87 _private prototype_ `void ExecutePlayAnimationTimeRange(UUserWidget* Widget, UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, EUMGSequencePlayMode::Type PlayMode, float PlaybackSpeed);`
- L88 _private prototype_ `void OnSequenceFinished(FWidgetAnimationState& State);`
- L89 _private prototype_ `bool OnAnimationFinished(float DeltaTime);`
- L91 _private member_ `FWidgetAnimationHandle WidgetAnimationHandle;`
- L92 _private member_ `FDelegateHandle OnFinishedHandle;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWidgetAnimationResult);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWidgetAnimationResult);`

### `Source/Runtime/UMG/Public/Animation/WidgetAnimationState.h` (Public)


#### struct `FWidgetAnimationStatePlayParams`  
`struct FWidgetAnimationStatePlayParams`  
_L24-42_
- L27 _public member_ `double StartAtTime = 0;` — The start time for the animation.
- L29 _public member_ `TOptional<double> EndAtTime;` — The end time for the animation.
- L31 _public member_ `TOptional<double> StartOffset;` — An optional start offset to apply to the animation.
- L33 _public member_ `TOptional<double> EndOffset;` — An optional end offset to apply to the animation.
- L35 _public member_ `int32 NumLoopsToPlay = 1;` — The number of loops to play before finishing the animation.
- L37 _public member_ `float PlaybackSpeed = 1.f;` — The play-rate of the animation.
- L39 _public member_ `EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward;` — The play mode of the animation.
- L41 _public member_ `bool bRestoreState = false;` — Whether to restore pre-animated state after the animation has finished.

#### struct `FWidgetAnimationState`  
`struct FWidgetAnimationState : public TSharedFromThis<FWidgetAnimationState>`  
_L47-200_
- inherits: `TSharedFromThis<FWidgetAnimationState>`
- desc: A class that runs an animation on a widget.
- L52 _public prototype_ `FWidgetAnimationState();` — Builds a new widget animation state.
- L55 _public prototype_ `void Initialize(UWidgetAnimation* InAnimation, UUserWidget* InUserWidget);` — Initializes the widget animation state.
- L58 _public function_ `UUserWidget* GetUserWidget() const` — Gets the user widget this state is animating.
- L61 _public function_ `const UWidgetAnimation* GetAnimation() const` — Gets the current animation being played
- L64 _public function_ `TSharedPtr<UE::MovieScene::FSharedPlaybackState> GetSharedPlaybackState() const` — Gets the playback state of the animation being played.
- L67 _public function_ `FName GetUserTag() const` — Gets the user tag for the animation.
- L70 _public function_ `void SetUserTag(FName InUserTag)` — Sets the user tag for the animation.
- L73 _public function_ `bool IsStopping() const` — Returns whether this state is currently stopping.
- L76 _public function_ `bool IsPendingDelete() const` — Returns whether this state is currently pending destruction.
- L79 _public function_ `FOnWidgetAnimationEvent& GetOnWidgetAnimationFinished()` — Allows registering a callback for when the animation has finished playing.
- L84 _public prototype_ `UUMGSequencePlayer* GetOrCreateLegacyPlayer();` — Gets a legacy player object for backwards compatibility, lazily created it if needed.
- L87 _public prototype_ `UUMGSequencePlayer* GetLegacyPlayer() const;` — Gets a legacy player object for backwards compatibility, returning null if none exists yet.
- L90 _public prototype_ `FWidgetAnimationHandle GetAnimationHandle() const;` — Gets the widget animation handle for the animation being played.
- L93 _public prototype_ `bool IsPlayingForward() const;` — Gets whether the animation is playing forwards or backwards.
- L96 _public prototype_ `EMovieScenePlayerStatus::Type GetPlaybackStatus() const;` — Gets the playback status of the animation.
- L99 _public prototype_ `void SetPlaybackStatus(EMovieScenePlayerStatus::Type InPlaybackStatus);` — Sets the playback status of the animation.
- L102 _public prototype_ `FQualifiedFrameTime GetCurrentTime() const;` — Gets the current time of the animation.
- L105 _public prototype_ `void SetCurrentTime(float InTime);` — Sets the current time of the animation.
- L108 _public prototype_ `void SetNumLoopsToPlay(int32 InNumLoopsToPlay);` — Sets the number of loops to play.
- L111 _public prototype_ `void SetPlaybackSpeed(float PlaybackSpeed);` — Sets the animation playback rate.
- L114 _public prototype_ `void Tick(float InDeltaSeconds);` — Update the animation.
- L117 _public prototype_ `void Play(const FWidgetAnimationStatePlayParams& PlayParams);` — Begins playing or restarts an animation.
- L120 _public prototype_ `void Stop();` — Stops a running animation and resets time.
- L123 _public prototype_ `void Pause();` — Pauses a running animation.
- L126 _public prototype_ `void Reverse();` — Reverses a running animation.
- L129 _public prototype_ `void RemoveEvaluationData();` — Disable this sequence player by removing any of its animation data from the entity manager.
- L132 _public prototype_ `void TearDown();` — Tears down the animation.
- L135 _public prototype_ `bool IsValid() const;` — Returns whether this animation is valid. An uninitialized or torn-down state is not valid.
- L138 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect objects for the GC.
- L142 _private prototype_ `bool NeedsLegacyPlayer() const;`
- L144 _private prototype_ `void FlushIfPrivateLinker();`
- L146 _private prototype_ `void OnBegunPlay();`
- L147 _private prototype_ `void OnStopped();`
- L152 _private member_ `TObjectPtr<UWidgetAnimation> Animation;` — Animation being played
- L155 _private member_ `TObjectPtr<UUMGSequencePlayer> LegacyPlayer;` — Legacy sequence player for backwards compatibility
- L158 _private member_ `TWeakObjectPtr<UUserWidget> WeakUserWidget;` — The user widget this sequence is animating
- L163 _private member_ `TWeakPtr<UE::MovieScene::FSharedPlaybackState> WeakPlaybackState;` — Shared playback state for the animation.
- L166 _private member_ `TObjectPtr<UMovieSceneEntitySystemLinker> PrivateLinker;` — Private linker for blocking/synchronous running.
- L169 _private member_ `FMovieScenePlaybackManager PlaybackManager;` — Playback manager for the animation.
- L172 _private member_ `EUMGSequencePlayMode::Type PlayMode;` — The current playback mode.
- L181 _private member_ `FName UserTag;` — The 'state' tag the user may want to use to track what the animation is for. It's very common in UI to use the same animation for intro / outro, so this allows you to tag what the animation is currently doing so that you can have some events just get called back when the animation finishes the outtro, to say, remove the UI then.
- L184 _private member_ `float BlockedDeltaTimeCompensation;` — Accumulated delta-time we were not able to evaluate with due to ongoing budgeted evaluation.
- L187 _private member_ `bool bRestoreState : 1;` — Whether to restore pre-animated state.
- L190 _private member_ `bool bIsBeginningPlay : 1;` — Whether we are in the process of starting play.
- L193 _private member_ `bool bIsStopping : 1;` — Whether we are in the process of stopping.
- L196 _private member_ `bool bIsPendingDelete : 1;` — Whether we have played, stopped, and now waiting to be deleted.
- L199 _private member_ `FOnWidgetAnimationEvent OnWidgetAnimationFinishedEvent;` — Callback for when the animation has finished playing.

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetAnimationEvent, FWidgetAnimationState&);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetAnimationEvent, FWidgetAnimationState&);`

### `Source/Runtime/UMG/Public/Animation/WidgetMaterialTrackUtilities.h` (Public)


#### class `FWidgetMaterialHandle`  
`class FWidgetMaterialHandle`  
_L13-53_
- desc: Handle to a widget material for easy getting and setting of the material.  Not designed to be stored
- L16 _public function_ `FWidgetMaterialHandle() : TypeName(NAME_None) , Data(nullptr)`
- L21 _public function_ `FWidgetMaterialHandle(FName InTypeName, void* InData) : TypeName(InTypeName) , Data(InData)`
- L40 _public function_ `bool IsValid() const` — @return true if this handle points to valid data
- L43 _public prototype_ `UMaterialInterface* GetMaterial() const;` — Gets the currently bound material
- L46 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial, UWidget* OwnerWidget);` — Sets the new bound material
- L50 _private member_ `FName TypeName;` — Struct typename for that the data is pointing to
- L52 _private member_ `void* Data;` — Pointer to the struct data holding the material

#### struct `FWidgetMaterialPropertyPath`  
`struct FWidgetMaterialPropertyPath`  
_L55-64_
- L57 _public function_ `FWidgetMaterialPropertyPath(const TArray<FProperty*>& InPropertyPath, const FString& InDisplayName) : PropertyPath(InPropertyPath) , DisplayName(InDisplayName)`
- L62 _public member_ `TArray<FProperty*> PropertyPath;`
- L63 _public member_ `FString DisplayName;`

#### Free symbols / members of external scopes

- L26 _function_ `friend uint32 GetTypeHash(const FWidgetMaterialHandle& In)`
- L30 _function_ `friend bool operator==(const FWidgetMaterialHandle& A, const FWidgetMaterialHandle& B)`
- L34 _function_ `friend bool operator!=(const FWidgetMaterialHandle& A, const FWidgetMaterialHandle& B)`
- L65 _namespace_ `namespace WidgetMaterialTrackUtilities`
- L68 _prototype_ `FWidgetMaterialHandle GetMaterialHandle(UWidget* Widget, TArrayView<const FName> BrushPropertyNamePath);` (scope `WidgetMaterialTrackUtilities`) — Gets a material handle from a property on a widget by the properties FName path.
- L71 _prototype_ `void GetMaterialBrushPropertyPaths( UWidget* Widget, TArray<FWidgetMaterialPropertyPath>& MaterialBrushPropertyPaths );` (scope `WidgetMaterialTrackUtilities`) — Gets the property paths on a widget which are slate brush properties, and who's slate brush has a valid material.
- L74 _prototype_ `FName GetTrackNameFromPropertyNamePath( TArrayView<const FName> PropertyNamePath );` (scope `WidgetMaterialTrackUtilities`) — Converts a property name path into a single name which is appropriate for a track name.

### `Source/Runtime/UMG/Public/Binding/BoolBinding.h` (Public)


#### class `UBoolBinding`  
`class UBoolBinding : public UPropertyBinding`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L18 _public prototype_ `UBoolBinding();`
- L20 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L21 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L24 _public prototype_ `bool GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Binding/BrushBinding.h` (Public)


#### class `UBrushBinding`  
`class UBrushBinding : public UPropertyBinding`  
_L13-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L19 _public prototype_ `UBrushBinding();`
- L21 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L22 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L25 _public prototype_ `FSlateBrush GetValue() const;` — `UFUNCTION()`
- L35 _private member_ `mutable TOptional<EConversion> bConversion;`

#### enum `UBrushBinding::EConversion`  
`enum class EConversion : uint8`  
_L28-33_
- L30 _public enumerator_ `None`
- L31 _public enumerator_ `Texture`

### `Source/Runtime/UMG/Public/Binding/CheckedStateBinding.h` (Public)


#### class `UCheckedStateBinding`  
`class UCheckedStateBinding : public UPropertyBinding`  
_L14-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L20 _public prototype_ `UCheckedStateBinding();`
- L22 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L23 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L26 _public prototype_ `ECheckBoxState GetValue() const;` — `UFUNCTION()`
- L35 _private member_ `mutable TOptional<EConversion> bConversion;`

#### enum `UCheckedStateBinding::EConversion`  
`enum class EConversion : uint8`  
_L29-33_
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `Bool`

### `Source/Runtime/UMG/Public/Binding/ColorBinding.h` (Public)


#### class `UColorBinding`  
`class UColorBinding : public UPropertyBinding`  
_L13-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L19 _public prototype_ `UColorBinding();`
- L21 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L22 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L24 _public prototype_ `virtual void Bind(FProperty* Property, FScriptDelegate* Delegate) override;`
- L27 _public prototype_ `FSlateColor GetSlateValue() const;` — `UFUNCTION()`
- L30 _public prototype_ `FLinearColor GetLinearValue() const;` — `UFUNCTION()`
- L33 _private member_ `mutable TOptional<bool> bNeedsConversion;`

### `Source/Runtime/UMG/Public/Binding/DynamicPropertyPath.h` (Public)


#### struct `FDynamicPropertyPath`  
`struct FDynamicPropertyPath : public FCachedPropertyPath`  
_L18-47_
- reflection: `USTRUCT()`
- inherits: `FCachedPropertyPath`
- L25 _public prototype_ `FDynamicPropertyPath();`
- L28 _public prototype_ `FDynamicPropertyPath(const FString& Path);`
- L31 _public prototype_ `FDynamicPropertyPath(const TArray<FString>& PropertyChain);`
- L35 _public function_ `template<typename T> bool GetValue(UObject* InContainer, T& OutValue) const` — Get the value represented by this property path
- L43 _public function_ `template<typename T> bool GetValue(UObject* InContainer, T& OutValue, FProperty*& OutProperty) const` — Get the value and the leaf property represented by this property path

### `Source/Runtime/UMG/Public/Binding/FloatBinding.h` (Public)


#### class `UFloatBinding`  
`class UFloatBinding : public UPropertyBinding`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L18 _public prototype_ `UFloatBinding();`
- L20 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L21 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L24 _public prototype_ `float GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Binding/Int32Binding.h` (Public)


#### class `UInt32Binding`  
`class UInt32Binding : public UPropertyBinding`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L18 _public prototype_ `UInt32Binding();`
- L20 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L21 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L24 _public prototype_ `int32 GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Binding/MouseCursorBinding.h` (Public)


#### class `UMouseCursorBinding`  
`class UMouseCursorBinding : public UPropertyBinding`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L19 _public prototype_ `UMouseCursorBinding();`
- L21 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L22 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L25 _public prototype_ `EMouseCursor::Type GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Binding/PropertyBinding.h` (Public)


#### class `UPropertyBinding`  
`class UPropertyBinding : public UObject`  
_L17-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L22 _public prototype_ `UPropertyBinding();`
- L24 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const;`
- L25 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const;`
- L27 _public prototype_ `virtual void Bind(FProperty* Property, FScriptDelegate* Delegate);`
- L32 _public member_ `TWeakObjectPtr<UObject> SourceObject;` — `UPROPERTY(Transient)` — The source object to use as the initial container to resolve the Source Property Path on.
- L36 _public member_ `FDynamicPropertyPath SourcePath;` — `UPROPERTY()` — The property path to trace to resolve this binding on the Source Object
- L40 _public member_ `FName DestinationProperty;` — `UPROPERTY()` — Used to determine if a binding already exists on the object and if this binding can be safely removed.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UMG Binding"), STAT_UMGBinding, STATGRO`

### `Source/Runtime/UMG/Public/Binding/States/WidgetStateBitfield.h` (Public)


#### struct `FWidgetStateBitfield`  
`struct FWidgetStateBitfield`  
_L22-181_
- reflection: `USTRUCT()`
- desc: Expensive to create wrapper for binary and enumerated widget states that supports FName-based interaction and dynamic states populated in an IWidgetStateNameMapper May be used to represent either a target widget state combination, or an actual widgets state All this does is cache the integer results of dynamic FName state lookup from an IWidgetStateNameMapper So it's prefertable to create these once and reuse. In particular, if broadcasting current state determine the correct bitfield to modify the existing state ahead of time. Save that bitfield and use it when performing state-modifications. Likewise when performing state tests, try to construct the relevant bitfield ahead of time & store that to later be compared against
- L29 _public prototype_ `FWidgetStateBitfield();` — Default, will convert to false as a bool
- L32 _public prototype_ `FWidgetStateBitfield(const FName InStateName);` — Interprets name as binary state on
- L36 _public prototype_ `FWidgetStateBitfield(const FName InStateName, const uint8 InValue);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Interprets name value pair as enum state
- L43 _public prototype_ `FWidgetStateBitfield operator~() const;` — Negation of binary and enum states, maintains enum state usage, but marks states as not allowed.
- L51 _public prototype_ `FWidgetStateBitfield Intersect(const FWidgetStateBitfield& Rhs) const;` — Intersection of binary and enum states, with union on enum state usage so enum state mismatches can fail Intersections will remove not allowed enum states, allowing for failure on bool conversion due to empty used states. Approximation of bitwise '&'. Non-commutative, will use LHS enum state set if RHS does not use enum. Additionally, if the RHS has binary states & the LHS does not meet those, all enum states will be marked unused to ensure failure
- L58 _public prototype_ `FWidgetStateBitfield Union(const FWidgetStateBitfield& Rhs) const;` — Union of binary and enum states, allows for a single enum state to have multiple values in a bitfield. Unions will grow enum state set if allowance is same, otherwise the allowed set is maintained. Approximation of bitwise '|'. Commutative.
- L63 _public prototype_ `operator bool() const;` — True if any binary or enum state is set, and no empty used enum states exist
- L66 _public prototype_ `bool HasBinaryStates() const;` — True if any binary state is set
- L70 _public prototype_ `bool HasEnumStates() const;` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — True if any enum state is used, does not indicate if state is actually set. Use 'HasEmptyUsedEnumStates' for that.
- L74 _public prototype_ `bool HasEmptyUsedEnumStates() const;` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — True if any enum used enum states are empty, usually indicating a failed '&' test
- L83 _public prototype_ `bool HasAnyFlags(const FWidgetStateBitfield& InBitfield) const;` — True if any state flag is met
- L86 _public prototype_ `bool HasAllFlags(const FWidgetStateBitfield& InBitfield) const;` — True if all state flags are met
- L89 _public prototype_ `bool HasAnyBinaryFlags(const FWidgetStateBitfield& InBitfield) const;` — True if any binary state flag is met
- L92 _public prototype_ `bool HasAllBinaryFlags(const FWidgetStateBitfield& InBitfield) const;` — True if all binary state flags are met
- L96 _public prototype_ `bool HasAnyEnumFlags(const FWidgetStateBitfield& InBitfield) const;` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — True if any enum state flag is met
- L100 _public prototype_ `bool HasAllEnumFlags(const FWidgetStateBitfield& InBitfield) const;` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — True if all enum state flags are met
- L105 _public prototype_ `void SetState(const FWidgetStateBitfield& InBitfield);` — Set state to given value, just calls assignment operator for you
- L108 _public prototype_ `void NegateStates();` — Negate both binary and enum states
- L116 _public prototype_ `void SetBinaryState(uint8 BinaryStateIndex, bool BinaryStateValue);` — Set binary state to given value @param BinaryStateIndex Index for Binary state to assign value to @param BinaryStateValue Value to assign for given Binary state
- L124 _public prototype_ `void SetBinaryState(const FWidgetStateBitfield& BinaryStateBitfield, bool BinaryStateValue);` — Set Binary state to given value, using a bitfield to indicate states that should be changed @param BinaryStateBitfield state bitfield, all marked states will be set with given value @param BinaryStateValue Value to assign for given Binary state
- L127 _public prototype_ `void SetBinaryStateSlow(FName BinaryStateName, bool BinaryStateValue);` — Set Binary state to given value, slow version w/ FName map lookup
- L130 _public prototype_ `void NegateBinaryStates();` — Negate only binary states
- L139 _public prototype_ `void SetEnumState(uint8 EnumStateIndex, uint8 EnumStateValue);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Set enum state to given value, clearing all existing values for that state @param EnumStateIndex Index for enum state to assign value to @param EnumStateValue Value to assign for given enum state
- L147 _public prototype_ `void SetEnumState(const FWidgetStateBitfield& EnumStateBitfield);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Set enum state to given value, clearing all existing values for states in use @param EnumStateBitfield state bitfield, all used states will copy-overwrite current enum state
- L151 _public prototype_ `void SetEnumStateSlow(FName EnumStateName, uint8 EnumStateValue);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Set enum state to given value, clearing all existing values for that state, slow version w/ FName map lookup
- L159 _public prototype_ `void ClearEnumState(const FWidgetStateBitfield& EnumStateBitfield);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Clear all existing values for given states & mark the states unused @param EnumStateBitfield state bitfield, all used states will be cleared
- L167 _public prototype_ `void ClearEnumState(uint8 EnumStateIndex);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Clear all existing values for given state & mark the state unused @param EnumStateIndex Index for enum state to mark as unused
- L171 _public prototype_ `void ClearEnumState(FName EnumStateName);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Clear all existing values for given state & mark the state unused, slow version w/ map lookup
- L175 _public prototype_ `void NegateEnumStates();` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Negate only enum states, does not change usage, but marks existing values as not allowed
- L180 _private member_ `uint64 BinaryStates = 0;` — Binary states captured by this state field

### `Source/Runtime/UMG/Public/Binding/States/WidgetStateRegistration.h` (Public)


#### class `UWidgetBinaryStateRegistration`  
`class UWidgetBinaryStateRegistration : public UObject`  
_L22-41_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: Derive from to add a new widget binary state Technically these can be created in BP, but for now we don't want to encourage that workflow as it involves requring overrides for the virtuals which is technical.
- L27 _public prototype_ `UWidgetBinaryStateRegistration() = default;`
- L28 _public prototype_ `virtual ~UWidgetBinaryStateRegistration() = default;`
- L31 _public prototype_ `virtual FName GetStateName() const;` — Called once during WidgetStateSettings initialization to get this widget state's name
- L34 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const;` — Called on widget registration to correctly initialize widget state based on the current widget
- L40 _protected prototype_ `virtual void InitializeStaticBitfields() const;` — Called to give CDO chance to initialize any static state bitfields that might be declared for convenience

#### class `UWidgetHoveredStateRegistration`  
`class UWidgetHoveredStateRegistration : public UWidgetBinaryStateRegistration`  
_L44-66_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UWidgetBinaryStateRegistration`
- L51 _public member_ `static FWidgetStateBitfield Bit;` — Post-load initialized bit corresponding to this binary state
- L53 _public member_ `static const inline FName StateName = FName("Hov`
- L56 _public prototype_ `virtual FName GetStateName() const override;`
- L57 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L64 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### class `UWidgetPressedStateRegistration`  
`class UWidgetPressedStateRegistration : public UWidgetBinaryStateRegistration`  
_L69-91_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UWidgetBinaryStateRegistration`
- L76 _public member_ `static FWidgetStateBitfield Bit;` — Post-load initialized bit corresponding to this binary state
- L78 _public member_ `static const inline FName StateName = FName("Pre`
- L81 _public prototype_ `virtual FName GetStateName() const override;`
- L82 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L89 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### class `UWidgetDisabledStateRegistration`  
`class UWidgetDisabledStateRegistration : public UWidgetBinaryStateRegistration`  
_L94-116_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UWidgetBinaryStateRegistration`
- L101 _public member_ `static FWidgetStateBitfield Bit;` — Post-load initialized bit corresponding to this binary state
- L103 _public member_ `static const inline FName StateName = FName("Dis`
- L106 _public prototype_ `virtual FName GetStateName() const override;`
- L107 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L114 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### class `UWidgetSelectedStateRegistration`  
`class UWidgetSelectedStateRegistration : public UWidgetBinaryStateRegistration`  
_L119-141_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UWidgetBinaryStateRegistration`
- L126 _public member_ `static FWidgetStateBitfield Bit;` — Post-load initialized bit corresponding to this binary state
- L128 _public member_ `static const inline FName StateName = FName("Sel`
- L131 _public prototype_ `virtual FName GetStateName() const override;`
- L132 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L139 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### class `UWidgetEnumStateRegistration`  
`class UWidgetEnumStateRegistration : public UObject`  
_L147-169_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: Derive from to add a new Enum binary state
- L152 _public prototype_ `UWidgetEnumStateRegistration() = default;`
- L153 _public prototype_ `virtual ~UWidgetEnumStateRegistration() = default;`
- L156 _public prototype_ `virtual FName GetStateName() const;` — Called once during WidgetStateSettings initialization to get this widget state's name
- L159 _public prototype_ `virtual bool GetRegisteredWidgetUsesState(const UWidget* InWidget) const;` — Called on widget registration to determine if this widget uses the given state
- L162 _public prototype_ `virtual uint8 GetRegisteredWidgetState(const UWidget* InWidget) const;` — Called on widget registration to correctly initialize widget state based on the current widget
- L168 _protected prototype_ `virtual void InitializeStaticBitfields() const;` — Called to give CDO chance to initialize any static state bitfields that might be declared for convenience

### `Source/Runtime/UMG/Public/Binding/States/WidgetStateSettings.h` (Public)


#### class `UWidgetStateSettings`  
`class UWidgetStateSettings : public UDeveloperSettings`  
_L26-85_
- reflection: `UCLASS(config = Game, defaultconfig, MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Settings used to map widget states to indexes. Does not perform any input validation, will crash if given invalid searches Note: Currently doesn't really have any meaningful settings, used more as global singleton. May change.
- L32 _public function_ `static const UWidgetStateSettings* Get()`
- L38 _public prototype_ `virtual void PostInitProperties() override;`
- L44 _public prototype_ `void GetAllStateNames(TArray<FName>& OutStateNames) const;` — Obtain a list of all known States.
- L47 _public prototype_ `void GetBinaryStateNames(TArray<FName>& OutBinaryStateNames) const;` — Obtain a list of all known Binary States.
- L50 _public prototype_ `void GetEnumStateNames(TArray<FName>& OutEnumStateNames) const;` — Obtain a list of all known Enum States.
- L53 _public prototype_ `uint8 GetBinaryStateIndex(const FName InBinaryStateName) const;` — Get Index corresponding to this binary state, which may dynamically change - but not within a game session.
- L56 _public prototype_ `uint8 GetEnumStateIndex(const FName InEnumStateName) const;` — Get Index corresponding to this enum state, which may dynamically change - but not within a game session.
- L59 _public prototype_ `FName GetBinaryStateName(const uint8 InBinaryStateIndex) const;` — Get Name corresponding to this binary state index, which may dynamically change - but not within a game session.
- L62 _public prototype_ `FName GetEnumStateName(const uint8 InEnumStateIndex) const;` — Get Name corresponding to this enum state index, which may dynamically change - but not within a game session.
- L65 _public prototype_ `FWidgetStateBitfield GetInitialRegistrationBitfield(const UWidget* InWidget) const;` — Gets bitfield of widget based on current state and given on registration state initializers
- L69 _private member_ `TMap<FName, uint8, TInlineSetAllocator<32>> BinaryStateMap;` — Map of Binary State Names to index (In order of addition)
- L72 _private member_ `TMap<FName, uint8, TInlineSetAllocator<8>> EnumStateMap;` — Map of Enum State Names to index (In order of addition)
- L75 _private member_ `TArray<FName, TInlineAllocator<32>> BinaryStates;` — Ordered list of Binary Widget States
- L78 _private member_ `TArray<FName, TInlineAllocator<8>> EnumStates;` — Ordered list of Enum Widget States
- L81 _private member_ `TArray<TObjectPtr<UWidgetBinaryStateRegistration>, TInlineAllocator<32>> BinaryStateRegistrationCDOs;` — Ordered list of Binary Widget States
- L84 _private member_ `TArray<TObjectPtr<UWidgetEnumStateRegistration>, TInlineAllocator<8>> EnumStateRegistrationCDOs;` — Ordered list of Enum Widget States

### `Source/Runtime/UMG/Public/Binding/TextBinding.h` (Public)


#### class `UTextBinding`  
`class UTextBinding : public UPropertyBinding`  
_L12-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L18 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L19 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L21 _public prototype_ `virtual void Bind(FProperty* Property, FScriptDelegate* Delegate) override;`
- L24 _public prototype_ `FText GetTextValue() const;` — `UFUNCTION()`
- L27 _public prototype_ `FString GetStringValue() const;` — `UFUNCTION()`
- L40 _private member_ `mutable TOptional<EConversion> NeedsConversion;`

#### enum `UTextBinding::EConversion`  
`enum class EConversion : uint8`  
_L31-38_
- L33 _public enumerator_ `None`
- L34 _public enumerator_ `String`
- L35 _public enumerator_ `Words`
- L36 _public enumerator_ `Integer`
- L37 _public enumerator_ `Float`

### `Source/Runtime/UMG/Public/Binding/VisibilityBinding.h` (Public)


#### class `UVisibilityBinding`  
`class UVisibilityBinding : public UPropertyBinding`  
_L15-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L21 _public prototype_ `UVisibilityBinding();`
- L23 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L24 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L27 _public prototype_ `ESlateVisibility GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Binding/WidgetBinding.h` (Public)


#### class `UWidgetBinding`  
`class UWidgetBinding : public UPropertyBinding`  
_L14-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBinding`
- L20 _public prototype_ `UWidgetBinding();`
- L22 _public prototype_ `virtual bool IsSupportedSource(FProperty* Property) const override;`
- L23 _public prototype_ `virtual bool IsSupportedDestination(FProperty* Property) const override;`
- L26 _public prototype_ `UWidget* GetValue() const;` — `UFUNCTION()`

### `Source/Runtime/UMG/Public/Blueprint/AsyncTaskDownloadImage.h` (Public)


#### class `UAsyncTaskDownloadImage`  
`class UAsyncTaskDownloadImage : public UBlueprintAsyncActionBase`  
_L17-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L23 _public prototype_ `static UAsyncTaskDownloadImage* DownloadImage(FString URL);` — `UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))`
- L28 _public member_ `FDownloadImageDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L31 _public member_ `FDownloadImageDelegate OnFail;` — `UPROPERTY(BlueprintAssignable)`
- L35 _public prototype_ `void Start(FString URL);`
- L40 _private prototype_ `void HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — Handles image requests coming from the web

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadImageDelegate, UTexture2DDynamic*, Texture);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadImageDelegate, UTexture2DDynamic*, Texture);`

### `Source/Runtime/UMG/Public/Blueprint/DragDropOperation.h` (Public)


#### enum `EUMGItemDropZone`  
`enum class EUMGItemDropZone : uint8`  
_L20-26_
- reflection: `UENUM(BlueprintType)`
- desc: A drop zone enum that can be passed through blueprint implementable events and sent through multicast delegates.
- L22 _public enumerator_ `AboveItem`
- L23 _public enumerator_ `OntoItem`
- L24 _public enumerator_ `BelowItem`
- L25 _public enumerator_ `None`

#### enum `EDragPivot`  
`enum class EDragPivot : uint8`  
_L35-48_
- reflection: `UENUM(BlueprintType)`
- desc: Controls where the drag widget visual will appear when dragged relative to the pointer performing the drag operation.
- L38 _public enumerator_ `MouseDown`
- L39 _public enumerator_ `TopLeft`
- L40 _public enumerator_ `TopCenter`
- L41 _public enumerator_ `TopRight`
- L42 _public enumerator_ `CenterLeft`
- L43 _public enumerator_ `CenterCenter`
- L44 _public enumerator_ `CenterRight`
- L45 _public enumerator_ `BottomLeft`
- L46 _public enumerator_ `BottomCenter`
- L47 _public enumerator_ `BottomRight`

#### class `UDragDropOperation`  
`class UDragDropOperation : public UObject`  
_L54-114_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta=( DontUseGenericSpawnObject="True" ), MinimalAPI)`
- inherits: `UObject`
- desc: This class is the base drag drop operation for UMG, extend it to add additional data and add new functionality.
- L60 _public prototype_ `static EUMGItemDropZone ConvertSlateDropZoneToUMG(TOptional<EItemDropZone> DropZone);`
- L64 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop", meta=( ExposeOnSpawn="true" ))` — A simple string tag you can optionally use to provide extra metadata about the operation.
- L71 _public member_ `TObjectPtr<UObject> Payload;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop", meta=( ExposeOnSpawn="true" ))` — The payload of the drag operation.  This can be any UObject that you want to pass along as dragged data.  If you were building an inventory screen this would be the UObject representing the item being moved to another slot.
- L78 _public member_ `TObjectPtr<class UWidget> DefaultDragVisual;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Drag and Drop", meta=( ExposeOnSpawn="true", DisplayName="Drag Visual" ))` — The Drag Visual is the widget to display when dragging the item.  Normally people create a new widget to represent the temporary drag.
- L85 _public member_ `EDragPivot Pivot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop", meta=( ExposeOnSpawn="true" ))` — Controls where the drag widget visual will appear when dragged relative to the pointer performing the drag operation.
- L89 _public member_ `FVector2D Offset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop", AdvancedDisplay, meta=( ExposeOnSpawn="true" ))` — A percentage offset (-1..+1) from the Pivot location, the percentage is of the desired size of the dragged visual.
- L93 _public member_ `FOnDragDropMulticast OnDrop;` — `UPROPERTY(BlueprintAssignable)`
- L97 _public member_ `FOnDragDropMulticast OnDragCancelled;` — `UPROPERTY(BlueprintAssignable)`
- L101 _public member_ `FOnDragDropMulticast OnDragged;` — `UPROPERTY(BlueprintAssignable)`
- L105 _public prototype_ `void Drop(const FPointerEvent& PointerEvent);` — `UFUNCTION(BlueprintNativeEvent, Category="Drag and Drop")`
- L109 _public prototype_ `void DragCancelled(const FPointerEvent& PointerEvent);` — `UFUNCTION(BlueprintNativeEvent, Category="Drag and Drop")`
- L113 _public prototype_ `void Dragged(const FPointerEvent& PointerEvent);` — `UFUNCTION(BlueprintNativeEvent, Category="Drag and Drop")`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragDropMulticast, UDragDropOperation*, Operation);`
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragDropMulticast, UDragDropOperation*, Operation);`

### `Source/Runtime/UMG/Public/Blueprint/GameViewportSubsystem.h` (Public)


#### struct `FGameViewportWidgetSlot`  
`struct FGameViewportWidgetSlot`  
_L22-45_
- reflection: `USTRUCT(BlueprintType)`
- desc: The default value fills the entire screen / player region.
- L27 _public member_ `FAnchors Anchors = FAnchors(0.f, 0.f, 1.f, 1.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")`
- L30 _public member_ `FMargin Offsets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")`
- L33 _public member_ `FVector2D Alignment = FVector2D(0.f, 0.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")`
- L37 _public member_ `int32 ZOrder = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")` — The higher the number, the more on top this widget will be.
- L44 _public member_ `bool bAutoRemoveOnWorldRemoved = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")` — Remove the widget when the Widget's World is removed. @note The Widget is added to the GameViewportClient of the Widget's World. The GameViewportClient can migrate from World to World. The widget can stay visible if the owner of the widget also migrate.

#### class `UGameViewportSubsystem`  
`class UGameViewportSubsystem : public UEngineSubsystem`  
_L52-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L58 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L59 _public prototype_ `virtual void Deinitialize() override;`
- L62 _public prototype_ `static UGameViewportSubsystem* Get();`
- L65 _public prototype_ `static UGameViewportSubsystem* Get(UWorld* World);` — `UE_DEPRECATED(5.8, "Use the Get function which takes no arguments instead.")`
- L70 _public prototype_ `bool IsWidgetAdded(const UWidget* Widget) const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "User Interface")` — @return true if the widget was added to the viewport using AddWidget or AddWidgetForPlayer.
- L74 _public prototype_ `bool AddWidget(UWidget* Widget, FGameViewportWidgetSlot Slot);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")` — Adds it to the game's viewport.
- L81 _public prototype_ `bool AddWidgetForPlayer(UWidget* Widget, ULocalPlayer* Player, FGameViewportWidgetSlot Slot);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")` — Adds the widget to the game's viewport in the section dedicated to the player. This is valuable in a split screen game where you need to only show a widget over a player's portion of the viewport.
- L85 _public prototype_ `void RemoveWidget(UWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")` — Removes the widget from the viewport.
- L89 _public prototype_ `FGameViewportWidgetSlot GetWidgetSlot(const UWidget* Widget) const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")` — The slot info from previously added widget or info that is store for later.
- L93 _public prototype_ `void SetWidgetSlot(UWidget* Widget, FGameViewportWidgetSlot Slot);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")` — Update the slot info of a previously added widget or Store the slot info for later use.
- L96 _public prototype_ `DECLARE_EVENT_TwoParams(UGameViewportSubsystem, FWidgetAddedEvent, UWidget*, ULocalPlayer*);`
- L97 _public member_ `FWidgetAddedEvent OnWidgetAdded;`
- L100 _public prototype_ `DECLARE_EVENT_OneParam(UGameViewportSubsystem, FWidgetRemovedEvent, UWidget*);`
- L101 _public member_ `FWidgetRemovedEvent OnWidgetRemoved;`
- L112 _public prototype_ `static FGameViewportWidgetSlot SetWidgetSlotPosition(FGameViewportWidgetSlot Slot, const UWidget* Widget, FVector2D Position, bool bRemoveDPIScale);` — `UFUNCTION(BlueprintCallable, Category = "GameViewportWidgetSlot")` — Helper function to set the position in the viewport for the Slot. @param Position The 2D position to set the widget to in the viewport. @param bRemoveDPIScale If you've already calculated inverse DPI, set this to false. Otherwise inverse DPI is applied to the position so that when the location is scaled by DPI, it ends up in the expected position.
- L118 _public prototype_ `static FGameViewportWidgetSlot SetWidgetSlotDesiredSize(FGameViewportWidgetSlot Slot, FVector2D Size);` — `UFUNCTION(BlueprintCallable, Category = "GameViewportWidgetSlot")` — Helper function to set the desired size in the viewport for the Slot.
- L130 _private prototype_ `bool AddToScreen(UWidget* Widget, ULocalPlayer* Player, FGameViewportWidgetSlot& Slot);`
- L131 _private prototype_ `void RemoveWidgetInternal(UWidget* Widget, const TWeakPtr<SConstraintCanvas>& FullScreenWidget, const TWeakObjectPtr<ULocalPlayer>& LocalPlayer);`
- L132 _private prototype_ `void HandleWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResoures);`
- L133 _private prototype_ `void HandleRemoveWorld(UWorld* InWorld);`
- L134 _private prototype_ `void HandleLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);`
- L136 _private prototype_ `FMargin GetFullScreenOffsetForWidget(UWidget* Widget) const;`
- L137 _private prototype_ `TPair<FMargin, bool> GetOffsetAttribute(UWidget* Widget, const FGameViewportWidgetSlot& Slot) const;`
- L140 _private typedef_ `using FViewportWidgetList = TMap<TObjectKey<UWidget>, FSlotInfo>;`
- L141 _private member_ `FViewportWidgetList ViewportWidgets;`

#### struct `UGameViewportSubsystem::FSlotInfo`  
`struct FSlotInfo`  
_L121-127_
- L123 _public member_ `FGameViewportWidgetSlot Slot;`
- L124 _public member_ `TWeakObjectPtr<ULocalPlayer> LocalPlayer;`
- L125 _public member_ `TWeakPtr<SConstraintCanvas> FullScreenWidget;`
- L126 _public member_ `SConstraintCanvas::FSlot* FullScreenWidgetSlot = nullptr;`

#### Free symbols / members of external scopes

- L96 _delegate_ `DECLARE_EVENT_TwoParams(UGameViewportSubsystem, FWidgetAddedEvent, UWidget*, ULocalPlayer*);`
- L100 _delegate_ `DECLARE_EVENT_OneParam(UGameViewportSubsystem, FWidgetRemovedEvent, UWidget*);`

### `Source/Runtime/UMG/Public/Blueprint/IUserListEntry.h` (Public)


#### class `UUserListEntry`  
`class UUserListEntry : public UInterface`  
_L22-25_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`
- desc: Required interface for any UUserWidget class to be usable as entry widget in a UListViewBase Provides access to getters and events for changes to the status of the widget as an entry that represents an item in a list. @see UListViewBase @see ITypedUMGListView Note: To be usable as an entry for UListView, UTileView, or UTreeView, implement IUserObjectListEntry instead

#### class `IUserListEntry`  
`class IUserListEntry : public IInterface`  
_L27-99_
- inherits: `IInterface`
- L32 _public prototype_ `bool IsListItemSelected() const;` — Returns true if the item represented by this entry is currently selected in the owning list view.
- L35 _public prototype_ `bool IsListItemExpanded() const;` — Returns true if the item represented by this entry is currently expanded and showing its children. Tree view entries only.
- L38 _public prototype_ `UListViewBase* GetOwningListView() const;` — Returns the list view that contains this entry.
- L45 _public function_ `virtual bool IsListItemSelectable() const` — Advanced native-only option for specific rows to preclude themselves from any kind of selection. Intended primarily for category separators and the like. Note that this is only relevant when the row is in a list that allows selection in the first place.
- L49 _public prototype_ `static void ReleaseEntry(UUserWidget& ListEntryWidget);` — Functionality largely for "internal" use/plumbing - see SObjectTableRow's usage. You shouldn't have any cause to call these directly.
- L50 _public prototype_ `static void UpdateItemSelection(UUserWidget& ListEntryWidget, bool bIsSelected);`
- L51 _public prototype_ `static void UpdateItemExpansion(UUserWidget& ListEntryWidget, bool bIsExpanded);`
- L52 _public prototype_ `static void UpdateEntryDropIndicator(UUserWidget& ListEntryWidget, TOptional<EItemDropZone> DropZone);`
- L53 _public prototype_ `static void UpdateEntryDragOverState(UUserWidget& ListEntryWidget, bool bIsDraggingOver);`
- L54 _public prototype_ `static void EndEntryDropOperation(UUserWidget& ListEntryWidget, bool bSuccess);`
- L55 _public prototype_ `static void HandleEntryDropped(UUserWidget& ListEntryWidget, UDragDropOperation* Operation);`
- L56 _public prototype_ `static void HandleEntryDragged(UUserWidget& ListEntryWidget, UDragDropOperation* Operation);`
- L63 _protected prototype_ `virtual void NativeOnItemSelectionChanged(bool bIsSelected);` — These follow the same pattern as the NativeOn[X] methods in UUserWidget - super calls are expected in order to route the event to BP. See the BP events below for descriptions.
- L64 _protected prototype_ `virtual void NativeOnItemExpansionChanged(bool bIsExpanded);`
- L65 _protected prototype_ `virtual void NativeOnEntryReleased();`
- L69 _protected prototype_ `void BP_OnItemSelectionChanged(bool bIsSelected);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Item Selection Changed"))` — Called when the selection state of the item represented by this entry changes.
- L73 _protected prototype_ `void BP_OnItemExpansionChanged(bool bIsExpanded);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Item Expansion Changed"))` — Called when the expansion state of the item represented by this entry changes. Tree view entries only.
- L77 _protected prototype_ `void BP_OnEntryReleased();` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Entry Released"))` — Called when this entry is released from the owning table and no longer represents any list item
- L81 _protected prototype_ `void BP_OnUpdateEntryDropIndicator(EUMGItemDropZone DropZone);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Update Entry Drop Indicator"))` — Called when the drop zone indicator is changed for this entry
- L85 _protected prototype_ `void BP_OnEntryDragOverChanged(bool bIsDraggingOver);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Entry Drag Over Changed"))` — Called when the the entry is dragged over
- L89 _protected prototype_ `void BP_OnEndEntryDropOperation(bool bSuccess);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Entry Accept Drop"))` — Called when this entry accepts a drag and drop operation
- L93 _protected prototype_ `void BP_OnEntryDropped(UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Entry Dropped"))` — Called when this entry is dropped
- L97 _protected prototype_ `void BP_OnEntryDragged(UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, Category = UserListEntry, meta = (DisplayName = "On Entry Dragged"))` — Called when this entry is dragged

#### class `UUserListEntryLibrary`  
`class UUserListEntryLibrary : public UBlueprintFunctionLibrary`  
_L103-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Static library to supply "for free" functionality to widgets that implement IUserListEntry
- L113 _public prototype_ `static bool IsListItemSelected(TScriptInterface<IUserListEntry> UserListEntry);` — `UFUNCTION(BlueprintPure, Category = UserListEntry, meta = (DefaultToSelf = UserListEntry))` — Returns true if the item represented by this entry is currently selected in the owning list view. @param UserListEntry Note: Visually not transmitted, but this defaults to "self". No need to hook up if calling internally.
- L120 _public prototype_ `static bool IsListItemExpanded(TScriptInterface<IUserListEntry> UserListEntry);` — `UFUNCTION(BlueprintPure, Category = UserListEntry, meta = (DefaultToSelf = UserListEntry))` — Returns true if the item represented by this entry is currently expanded and showing its children. Tree view entries only. @param UserListEntry Note: Visually not transmitted, but this defaults to "self". No need to hook up if calling internally.
- L127 _public prototype_ `static UListViewBase* GetOwningListView(TScriptInterface<IUserListEntry> UserListEntry);` — `UFUNCTION(BlueprintPure, Category = UserListEntry, meta = (DefaultToSelf = UserListEntry))` — Returns the list view that contains this entry. @param UserListEntry Note: Visually not transmitted, but this defaults to "self". No need to hook up if calling internally.

### `Source/Runtime/UMG/Public/Blueprint/IUserObjectListEntry.h` (Public)


#### class `UUserObjectListEntry`  
`class UUserObjectListEntry : public UUserListEntry`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UUserListEntry`
- desc: Required interface for any UUserWidget class to be usable as entry widget in a stock UMG list view - ListView, TileView, and TreeView Provides a change event and getter for the object item the entry is assigned to represent by the owning list view (in addition to functionality from IUserListEntry)

#### class `IUserObjectListEntry`  
`class IUserObjectListEntry : public IUserListEntry`  
_L18-44_
- inherits: `IUserListEntry`
- L25 _public function_ `template <typename ItemObjectT = UObject> ItemObjectT* GetListItem() const` — Returns the UObject item in the owning UListView that this entry currently represents
- L33 _protected prototype_ `virtual void NativeOnListItemObjectSet(UObject* ListItemObject);` — Follows the same pattern as the NativeOn[X] methods in UUserWidget - super calls are expected in order to route the event to BP.
- L37 _protected prototype_ `void OnListItemObjectSet(UObject* ListItemObject);` — `UFUNCTION(BlueprintImplementableEvent, Category = ObjectListEntry)` — Called when this entry is assigned a new item object to represent by the owning list view
- L40 _private prototype_ `UObject* GetListItemObjectInternal() const;`
- L43 _private prototype_ `template <typename> friend class SObjectTableRow;`

#### class `UUserObjectListEntryLibrary`  
`class UUserObjectListEntryLibrary : public UBlueprintFunctionLibrary`  
_L48-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Static library to supply "for free" functionality to widgets that implement IUserListEntry
- L58 _public prototype_ `static UObject* GetListItemObject(TScriptInterface<IUserObjectListEntry> UserObjectListEntry);` — `UFUNCTION(BlueprintPure, Category = UserObjectListEntry, meta = (DefaultToSelf = UserObjectListEntry))` — Returns the item in the owning list view that this entry is currently assigned to represent. @param UserObjectListEntry Note: Visually not transmitted, but this defaults to "self". No need to hook up if calling internally.
- L62 _public prototype_ `static int32 GetListItemIndex(TScriptInterface<IUserObjectListEntry> UserObjectListEntry);` — `UFUNCTION(BlueprintPure, Category = UserObjectListEntry, meta = (DefaultToSelf = UserObjectListEntry))` — Returns the index of the list item in the owning UListView
- L66 _public prototype_ `static bool IsFirstWidget(TScriptInterface<IUserObjectListEntry> UserObjectListEntry);` — `UFUNCTION(BlueprintPure, Category = UserObjectListEntry, meta = (DefaultToSelf = UserObjectListEntry))` — Returns true if the widget list entry is the first item in the list view
- L70 _public prototype_ `static bool IsLastWidget(TScriptInterface<IUserObjectListEntry> UserObjectListEntry);` — `UFUNCTION(BlueprintPure, Category = UserObjectListEntry, meta = (DefaultToSelf = UserObjectListEntry))` — Returns true if the widget list entry is the last item in the list view

### `Source/Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h` (Public)


#### class `USlateBlueprintLibrary`  
`class USlateBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-143_
- reflection: `UCLASS(meta=(ScriptName="SlateLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static bool IsUnderLocation(const FGeometry& Geometry, const FVector2D& AbsoluteCoordinate);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry")` — Absolute coordinates could be either desktop or window space depending on what space the root of the widget hierarchy is in. @return true if the provided location in absolute coordinates is within the bounds of this geometry.
- L36 _public prototype_ `static FVector2D AbsoluteToLocal(const FGeometry& Geometry, FVector2D AbsoluteCoordinate);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta = (DisplayName = "Absolute to Local (Coordinates)", Keywords = "transform"))` — Transforms absolute coordinates into local coordinates Absolute coordinates could be either desktop or window space depending on what space the root of the widget hierarchy is in. @return Transforms AbsoluteCoordinate into the local space of this Geometry.
- L46 _public prototype_ `static FVector2D LocalToAbsolute(const FGeometry& Geometry, FVector2D LocalCoordinate);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta = (DisplayName = "Local to Absolute (Coordinates)", Keywords = "transform"))` — Transforms local coordinates into absolute coordinates Absolute coordinates could be either desktop or window space depending on what space the root of the widget hierarchy is in. @return  Absolute coordinates
- L50 _public prototype_ `static FVector2D GetLocalTopLeft(const FGeometry& Geometry);` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry")` — Returns the local top/left of the geometry in local space.
- L54 _public prototype_ `static FVector2D GetLocalSize(const FGeometry& Geometry);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry")` — Returns the size of the geometry in local space.
- L58 _public prototype_ `static FVector2D GetAbsoluteSize(const FGeometry& Geometry);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry")` — Returns the size of the geometry in absolute space.
- L62 _public prototype_ `static float Scalar_AbsoluteToLocal(const FGeometry& Geometry, float AbsoluteScalar);` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DisplayName = "Absolute to Local (Scalar)", Keywords = "transform"))` — Transforms a scalar from absolute space to local space
- L66 _public prototype_ `static float Scalar_LocalToAbsolute(const FGeometry& Geometry, float LocalScalar);` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DisplayName = "Local to Absolute (Scalar)", Keywords = "transform"))` — Transforms a scalar from local space to absolute space
- L70 _public prototype_ `static FVector2D Vector_AbsoluteToLocal(const FGeometry& Geometry, FVector2D AbsoluteVector);` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DisplayName = "Absolute to Local (Vector)", Keywords = "transform"))` — Transforms a vector from absolute space to local space
- L74 _public prototype_ `static FVector2D Vector_LocalToAbsolute(const FGeometry& Geometry, FVector2D LocalVector);` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DisplayName = "Local to Absolute (Vector)", Keywords = "transform"))` — Transforms a vector from local space to absolute space
- L79 _public prototype_ `static float TransformScalarAbsoluteToLocal(const FGeometry& Geometry, float AbsoluteScalar);` — `UE_DEPRECATED(5.6, "TransformScalarAbsoluteToLocal returns inverted results and has been replaced by Scalar_LocalToAbsolute")` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DeprecatedFunction, DeprecationMessage = "Returns inverted results. Replace with 'Local to Absolute (Scalar)'"))`
- L84 _public prototype_ `static float TransformScalarLocalToAbsolute(const FGeometry& Geometry, float LocalScalar);` — `UE_DEPRECATED(5.6, "TransformScalarLocalToAbsolute returns inverted results and has been replaced by Scalar_AbsoluteToLocal")` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DeprecatedFunction, DeprecationMessage = "Returns inverted results. Replace with 'Absolute To Local (Scalar)'"))`
- L89 _public prototype_ `static FVector2D TransformVectorAbsoluteToLocal(const FGeometry& Geometry, FVector2D AbsoluteVector);` — `UE_DEPRECATED(5.6, "TransformVectorAbsoluteToLocal returns inverted results and has been replaced by Vector_LocalToAbsolute")` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DeprecatedFunction, DeprecationMessage = "Returns inverted results. Replace with 'Local to Absolute (Vector)'"))`
- L94 _public prototype_ `static FVector2D TransformVectorLocalToAbsolute(const FGeometry& Geometry, FVector2D LocalVector);` — `UE_DEPRECATED(5.6, "TransformVectorLocalToAbsolute returns inverted results and has been replaced by Vector_AbsoluteToLocal")` — `UFUNCTION(BlueprintPure, Category = "User Interface|Geometry", meta = (DeprecatedFunction, DeprecationMessage = "Returns inverted results. Replace with 'Absolute To Local (Vector)'"))`
- L98 _public prototype_ `static bool EqualEqual_SlateBrush(const FSlateBrush& A, const FSlateBrush& B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SlateBrush)", CompactNodeTitle = "=="), Category = "SlateBrush")` — Returns whether brushes A and B are identical.
- L110 _public prototype_ `static void LocalToViewport(const UObject* WorldContextObject, const FGeometry& Geometry, FVector2D LocalCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta=( WorldContext="WorldContextObject" ))` — Translates local coordinate of the geometry provided into local viewport coordinates. @param PixelPosition The position in the game's viewport, usable for line traces and other uses where you need a coordinate in the space of viewport resolution units. @param ViewportPosition The position in the space of other widgets in the viewport.  Like if you wanted to add another widget to the viewport at the same position in viewport space as this location, this is what you would use.
- L122 _public prototype_ `static void AbsoluteToViewport(const UObject* WorldContextObject, FVector2D AbsoluteDesktopCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta=( WorldContext="WorldContextObject" ))` — Translates absolute coordinate in desktop space of the geometry provided into local viewport coordinates. @param PixelPosition The position in the game's viewport, usable for line traces and other uses where you need a coordinate in the space of viewport resolution units. @param ViewportPosition The position in the space of other widgets in the viewport.  Like if you wanted to add another widget to the viewport at the same position in viewport space as this location, this is what you would use.
- L129 _public prototype_ `static void ScreenToWidgetLocal(const UObject* WorldContextObject, const FGeometry& Geometry, FVector2D ScreenPosition, FVector2D& LocalCoordinate, bool bIncludeWindowPosition = false);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta=( WorldContext="WorldContextObject", DisplayName="ScreenToLocal" ))` — Translates a screen position in pixels into the local space of a widget with the given geometry. If bIncludeWindowPosition is true, then this method will also remove the game window's position (useful when in windowed mode).
- L136 _public prototype_ `static void ScreenToWidgetAbsolute(const UObject* WorldContextObject, FVector2D ScreenPosition, FVector2D& AbsoluteCoordinate, bool bIncludeWindowPosition = false);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta=( WorldContext="WorldContextObject", DisplayName="ScreenToAbsolute" ))` — Translates a screen position in pixels into absolute application coordinates. If bIncludeWindowPosition is true, then this method will also remove the game window's position (useful when in windowed mode).
- L142 _public prototype_ `static void ScreenToViewport(const UObject* WorldContextObject, FVector2D ScreenPosition, FVector2D& ViewportPosition);` — `UFUNCTION(BlueprintPure, Category="User Interface|Geometry", meta=( WorldContext="WorldContextObject" ))` — Translates a screen position in pixels into the local space of the viewport widget.

### `Source/Runtime/UMG/Public/Blueprint/UMGSequencePlayMode.h` (Public)


#### enum `EUMGSequencePlayMode::Type`  
`enum Type : int`  
_L15-23_
- L18 _public enumerator_ `Forward` — Animation plays and loops from the beginning to the end.
- L20 _public enumerator_ `Reverse` — Animation plays and loops from the end to the beginning.
- L22 _public enumerator_ `PingPong` — Animation plays from the beginning to the end and then from the end to the beginning.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EUMGSequencePlayMode`

### `Source/Runtime/UMG/Public/Blueprint/UserWidget.h` (Public)


#### enum `EQueuedWidgetAnimationMode`  
`enum class EQueuedWidgetAnimationMode : uint8`  
_L47-63_
- desc: Describes overall action driving this animation transition.
- L50 _public enumerator_ `Play` — Animation plays with given params.
- L52 _public enumerator_ `PlayTo` — Animation plays with given params to given point.
- L54 _public enumerator_ `Forward` — Animation plays from current position forward.
- L56 _public enumerator_ `Reverse` — Animation plays from current position reverse.
- L58 _public enumerator_ `Stop` — Animation stops playing.
- L60 _public enumerator_ `Pause` — Animation stops playing.
- L62 _public enumerator_ `None` — Default state, should not be used.

#### enum `ERequiresLegacyPlayer`  
`enum class ERequiresLegacyPlayer : uint8`  
_L66-74_
- desc: Describes whether the widget needs a legacy UMG sequence player to be created.
- L69 _public enumerator_ `AutoDetect` — Will create a legacy player if the widget class has native C++ children.
- L71 _public enumerator_ `Yes` — Force creating a legacy player.
- L73 _public enumerator_ `No` — Declares that no legacy player is required.

#### struct `FQueuedWidgetAnimationTransition`  
`struct FQueuedWidgetAnimationTransition`  
_L80-113_
- reflection: `USTRUCT()`
- desc: Struct that maintains state of currently queued animation transtions to be evaluated next frame.
- L86 _public member_ `TObjectPtr<UWidgetAnimation> WidgetAnimation;` — `UPROPERTY(Transient)` — Animation with a queued transition
- L89 _public member_ `EQueuedWidgetAnimationMode TransitionMode;` — Overall action driving this animation transition
- L92 _public member_ `TOptional<float> StartAtTime;` — The time in the animation from which to start playing, relative to the start position. For looped animations, this will only affect the first playback of the animation
- L95 _public member_ `TOptional<float> EndAtTime;` — The absolute time in the animation where to stop, this is only considered in the last loop.
- L98 _public member_ `TOptional<int32> NumLoopsToPlay;` — The number of times to loop this animation (0 to loop indefinitely)
- L101 _public member_ `TOptional<EUMGSequencePlayMode::Type> PlayMode;` — Specifies the playback mode (Forward, Reverse)
- L104 _public member_ `TOptional<float> PlaybackSpeed;` — The speed at which the animation should play
- L107 _public member_ `TOptional<bool> bRestoreState;` — Restores widgets to their pre-animated state when the animation stops
- L109 _public function_ `FQueuedWidgetAnimationTransition() : WidgetAnimation(nullptr) , TransitionMode(EQueuedWidgetAnimationMode::None)`

#### enum `EWidgetTickFrequency`  
`enum class EWidgetTickFrequency : uint8`  
_L117-128_
- reflection: `UENUM()`
- desc: Determines what strategy we use to determine when and if the widget ticks.
- L120 _public enumerator_ `Never = 0` — This widget never ticks
- L127 _public enumerator_ `Auto` — This widget will tick if a blueprint tick function is implemented, any latent actions are found or animations need to play If the widget inherits from something other than UserWidget it will also tick so that native C++ or inherited ticks function To disable native ticking use add the class metadata flag "DisableNativeTick".  I.E: meta=(DisableNativeTick)

#### enum `EWidgetAnimationEvent`  
`enum class EWidgetAnimationEvent : uint8`  
_L132-136_
- reflection: `UENUM(BlueprintType)`
- desc: Different animation events.
- L134 _public enumerator_ `Started`
- L135 _public enumerator_ `Finished`

#### struct `FAnimationEventBinding`  
`struct FAnimationEventBinding`  
_L140-169_
- reflection: `USTRUCT()`
- desc: Used to manage different animation event bindings that users want callbacks on.
- L146 _public function_ `FAnimationEventBinding() : Animation(nullptr) , Delegate() , AnimationEvent(EWidgetAnimationEvent::Started) , UserTag(NAME_None)`
- L156 _public member_ `TObjectPtr<UWidgetAnimation> Animation;` — `UPROPERTY()` — The animation to look for.
- L160 _public member_ `FWidgetAnimationDynamicEvent Delegate;` — `UPROPERTY()` — The callback.
- L164 _public member_ `EWidgetAnimationEvent AnimationEvent;` — `UPROPERTY()` — The type of animation event.
- L168 _public member_ `FName UserTag;` — `UPROPERTY()` — A user tag used to only get callbacks for specific runs of the animation.

#### struct `FPaintContext`  
`struct FPaintContext`  
_L177-216_
- reflection: `USTRUCT(BlueprintType)`
- desc: The state passed into OnPaint that we can expose as a single painting structure to blueprints to allow script code to override OnPaint behavior.
- L184 _public prototype_ `FPaintContext();` — Don't ever use this constructor.  Needed for code generation.
- L186 _public function_ `FPaintContext(const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& InOutDrawElements, const int32 InLayerId, const FWidgetStyle& InWidgetStyle, const bool bInParentEnabled) : AllottedGeometry(InAllottedGeometry) , MyCullingRect(InMyCullingRect) , OutDrawElements(InOutDrawElements) , LayerId(InLayerId) , WidgetStyle(InWidgetStyle) , bParentEnabled(bInParentEnabled) , MaxLayer(InLayerId)`
- L198 _public function_ `void operator=( const FPaintContext& Other )` — We override the assignment operator to allow generated code to compile with the const ref member.
- L208 _public member_ `const FGeometry& AllottedGeometry;`
- L209 _public member_ `const FSlateRect& MyCullingRect;`
- L210 _public member_ `FSlateWindowElementList& OutDrawElements;`
- L211 _public member_ `int32 LayerId;`
- L212 _public member_ `const FWidgetStyle& WidgetStyle;`
- L213 _public member_ `bool bParentEnabled;`
- L215 _public member_ `int32 MaxLayer;`

#### struct `FNamedSlotBinding`  
`struct FNamedSlotBinding`  
_L219-241_
- reflection: `USTRUCT()`
- L225 _public function_ `FNamedSlotBinding() : Name(NAME_None) , Content(nullptr)`
- L231 _public member_ `FName Name;` — `UPROPERTY()`
- L236 _public member_ `FGuid Guid;` — `UPROPERTY()` — GUID of the NamedSlot is used as a secondary identifier to find a binding in case the name of NamedSlot has changed.
- L240 _public member_ `TObjectPtr<UWidget> Content;` — `UPROPERTY(Instanced)`

#### enum `EDesignPreviewSizeMode`  
`enum class EDesignPreviewSizeMode : uint8`  
_L246-253_
- reflection: `UENUM()`
- L248 _public enumerator_ `FillScreen`
- L249 _public enumerator_ `Custom`
- L250 _public enumerator_ `CustomOnScreen`
- L251 _public enumerator_ `Desired`
- L252 _public enumerator_ `DesiredOnScreen`

#### class `UUserWidgetFunctionLibrary`  
`class UUserWidgetFunctionLibrary : public UBlueprintFunctionLibrary`  
_L258-268_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L264 _public prototype_ `static UUMGSequencePlayer* Conv_UMGSequencePlayer(const FWidgetAnimationHandle& WidgetAnimationHandle);` — `UFUNCTION(BlueprintPure, Category = "UMG", meta = (BlueprintAutocast, DeprecatedFunction, DeprecatedMessage="UMGSequencePlayer is deprecated, please use FWidgetAnimationState"))`
- L267 _public prototype_ `static UUserWidget* GetOuterUserWidget(const UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "UMG")`

#### class `UUserWidget`  
`class UUserWidget : public UWidget, public INamedSlotInterface`  
_L280-1807_
- reflection: `UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta=( DontUseGenericSpawnObject="True", DisableNativeTick) , MinimalAPI)`
- inherits: `UWidget,INamedSlotInterface`
- desc: A widget that enables UI extensibility through WidgetBlueprint.
- L286 _public prototype_ `UUserWidget(const FObjectInitializer& ObjectInitializer);`
- L289 _public prototype_ `virtual class UWorld* GetWorld() const override;`
- L290 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L291 _public prototype_ `virtual void BeginDestroy() override;`
- L292 _public prototype_ `virtual void PostLoad() override;`
- L295 _public prototype_ `void DuplicateAndInitializeFromWidgetTree(UWidgetTree* InWidgetTree, const TMap<FName, UWidget*>& NamedSlotContentToMerge);`
- L297 _public prototype_ `virtual bool Initialize();`
- L299 _public function_ `EWidgetTickFrequency GetDesiredTickFrequency() const`
- L307 _public prototype_ `UWidgetBlueprintGeneratedClass* GetWidgetTreeOwningClass() const;` — Returns the BlueprintGeneratedClass that generated the WidgetTree. A child UserWidget that extends a parent UserWidget will not have a new WidgetTree. The child UserWidget will have the same WidgetTree as the parent UserWidget. This function returns the parent UserWidget's BlueprintClass.
- L309 _public prototype_ `void UpdateCanTick();`
- L313 _protected function_ `virtual void InitializeNativeClassData()` — The function is implemented only in nativized widgets (automatically converted from BP to c++)
- L316 _protected function_ `virtual ERequiresLegacyPlayer GetLegacyPlayerRequirement() const` — Returns whether this widget needs a legacy player.
- L318 _protected prototype_ `void InitializeNamedSlots();`
- L322 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L326 _public prototype_ `virtual void SynchronizeProperties() override;`
- L330 _public prototype_ `virtual void GetSlotNames(TArray<FName>& SlotNames) const override;`
- L331 _public prototype_ `virtual UWidget* GetContentForSlot(FName SlotName) const override;`
- L332 _public prototype_ `virtual void SetContentForSlot(FName SlotName, UWidget* Content) override;`
- L342 _public prototype_ `void AddToViewport(int32 ZOrder = 0);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport", meta=( AdvancedDisplay = "ZOrder" ))` — Adds it to the game's viewport and fills the entire screen, unless SetDesiredSizeInViewport is called to explicitly set the size. @param ZOrder The higher the number, the more on top this widget will be.
- L351 _public prototype_ `bool AddToPlayerScreen(int32 ZOrder = 0);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport", meta=( AdvancedDisplay = "ZOrder" ))` — Adds the widget to the game's viewport in a section dedicated to the player.  This is valuable in a split screen game where you need to only show a widget over a player's portion of the viewport. @param ZOrder The higher the number, the more on top this widget will be.
- L358 _public prototype_ `void RemoveFromViewport();` — `UE_DEPRECATED(5.1, "RemoveFromViewport is deprecated. Use RemoveFromParent instead.")` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport", meta=( DeprecatedFunction, DeprecationMessage="Use RemoveFromParent instead" ))` — Removes the widget from the viewport.
- L368 _public prototype_ `void SetPositionInViewport(FVector2D Position, bool bRemoveDPIScale = true);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport")` — Sets the widgets position in the viewport. @param Position The 2D position to set the widget to in the viewport. @param bRemoveDPIScale If you've already calculated inverse DPI, set this to false. Otherwise inverse DPI is applied to the position so that when the location is scaled by DPI, it ends up in the expected position.
- L372 _public prototype_ `void SetDesiredSizeInViewport(FVector2D Size);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport")`
- L376 _public prototype_ `void SetAnchorsInViewport(FAnchors Anchors);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport")`
- L380 _public prototype_ `void SetAlignmentInViewport(FVector2D Alignment);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport")`
- L384 _public prototype_ `FAnchors GetAnchorsInViewport() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Viewport")`
- L388 _public prototype_ `FVector2D GetAlignmentInViewport() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Viewport")`
- L393 _public prototype_ `bool GetIsVisible() const;` — `UE_DEPRECATED(5.1, "GetIsVisible is deprecated. Please use IsInViewport instead.")` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Appearance", meta=( DeprecatedFunction, DeprecationMessage="Use IsInViewport instead" ))`
- L396 _public prototype_ `virtual void SetVisibility(ESlateVisibility InVisibility) override;` — Sets the visibility of the widget.
- L399 _public prototype_ `void SetPlayerContext(const FLocalPlayerContext& InPlayerContext);` — Sets the player context associated with this UI.
- L402 _public prototype_ `const FLocalPlayerContext& GetPlayerContext() const;` — Gets the player context associated with this UI.
- L408 _public prototype_ `virtual ULocalPlayer* GetOwningLocalPlayer() const override;` — Gets the local player associated with this UI. @return The owning local player.
- L415 _public function_ `template < class T > T* GetOwningLocalPlayer() const` — Gets the local player associated with this UI cast to the template type. @return The owning local player. May be NULL if the cast fails.
- L424 _public prototype_ `void SetOwningLocalPlayer(ULocalPlayer* LocalPlayer);` — Sets the player associated with this UI via LocalPlayer reference. @param LocalPlayer The local player you want to be the conceptual owner of this UI.
- L430 _public prototype_ `virtual APlayerController* GetOwningPlayer() const override;` — Gets the player controller associated with this UI. @return The player controller that owns the UI.
- L437 _public function_ `template < class T > T* GetOwningPlayer() const` — Gets the player controller associated with this UI cast to the template type. @return The player controller that owns the UI. May be NULL if the cast fails.
- L447 _public prototype_ `void SetOwningPlayer(APlayerController* LocalPlayerController);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Player")` — Sets the local player associated with this UI via PlayerController reference. @param LocalPlayerController The PlayerController of the local player you want to be the conceptual owner of this UI.
- L454 _public prototype_ `class APawn* GetOwningPlayerPawn() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Player")` — Gets the player pawn associated with this UI. @return Gets the owning player pawn that's owned by the player controller assigned to this widget.
- L462 _public function_ `template < class T > T* GetOwningPlayerPawn() const` — Gets the player pawn associated with this UI cast to the template type. @return Gets the owning player pawn that's owned by the player controller assigned to this widget. May be NULL if the cast fails.
- L473 _public function_ `template <class TPlayerState = APlayerState> TPlayerState* GetOwningPlayerState(bool bChecked = false) const` — Get the owning player's PlayerState. @return const APlayerState*
- L489 _public prototype_ `class APlayerCameraManager* GetOwningPlayerCameraManager() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Player")` — Gets the player camera manager associated with this UI. @return Gets the owning player camera manager that's owned by the player controller assigned to this widget.
- L497 _public function_ `template <class T> T* GetOwningPlayerCameraManager() const` — Gets the player camera manager associated with this UI cast to the template type. @return Gets the owning player camera manager that's owned by the player controller assigned to this widget. May be NULL if the cast fails.
- L508 _public prototype_ `void OnInitialized();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface")` — Called once only at game time on non-template instances. While Construct/Destruct pertain to the underlying Slate, this is called only once for the UUserWidget. If you have one-time things to establish up-front (like binding callbacks to events on BindWidget properties), do so here.
- L523 _public prototype_ `void PreConstruct(bool IsDesignTime);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface")` — Called by both the game and the editor.  Allows users to run initial setup for their widgets to better preview the setup in the designer and since generally that same setup code is required at runtime, it's called there as well. **WARNING** This is intended purely for cosmetic updates using locally owned data, you can not safely access any game related state, if you call something that doesn't expect to be run at editor time, you may crash the editor. In the event you save the asset with blueprint code that causes a crash on evaluation.  You can turn off PreConstruct evaluation in the Widget Designer settings in the Editor Preferences.
- L531 _public prototype_ `void Construct();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface", meta=( Keywords="Begin Play" ))` — Called after the underlying slate widget is constructed.  Depending on how the slate object is used this event may be called multiple times due to adding and removing from the hierarchy. If you need a true called-once-when-created event, use OnInitialized.
- L538 _public prototype_ `void Destruct();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface", meta=( Keywords="End Play, Destroy" ))` — Called when a widget is no longer referenced causing the slate resource to destroyed.  Just like Construct this event can be called multiple times.
- L547 _public prototype_ `void Tick(FGeometry MyGeometry, float InDeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface")` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  MyGeometry The space allotted for this widget @param  InDeltaTime  Real time passed since last tick
- L553 _public prototype_ `void OnPaint(UPARAM(ref) FPaintContext& Context) const;` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface | Painting")`
- L559 _public prototype_ `bool IsInteractable() const;` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface | Interaction")` — Gets a value indicating if the widget is interactive.
- L569 _public prototype_ `FEventReply OnFocusReceived(FGeometry MyGeometry, FFocusEvent InFocusEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — Called when keyboard focus is given to this widget.  This event does not bubble. @param MyGeometry The Geometry of the widget receiving the event @param InFocusEvent  FocusEvent @return  Returns whether the event was handled, along with other possible actions
- L577 _public prototype_ `void OnFocusLost(FFocusEvent InFocusEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — Called when this widget loses focus.  This event does not bubble. @param  InFocusEvent  FocusEvent
- L586 _public prototype_ `void OnAddedToFocusPath(FFocusEvent InFocusEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — If focus is gained on on this widget or on a child widget and this widget is added to the focus path, and wasn't previously part of it, this event is called. @param  InFocusEvent  FocusEvent
- L595 _public prototype_ `void OnRemovedFromFocusPath(FFocusEvent InFocusEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — If focus is lost on on this widget or on a child widget and this widget is no longer part of the focus path. @param  InFocusEvent  FocusEvent
- L605 _public prototype_ `FEventReply OnKeyChar(FGeometry MyGeometry, FCharacterEvent InCharacterEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — Called after a character is entered while this widget has focus @param MyGeometry The Geometry of the widget receiving the event @param  InCharacterEvent  Character event @return  Returns whether the event was handled, along with other possible actions
- L619 _public prototype_ `FEventReply OnPreviewKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);` — `UFUNCTION(BlueprintImplementableEvent, Category="Input")` — Called after a key (keyboard, controller, ...) is pressed when this widget or a child of this widget has focus If a widget handles this event, OnKeyDown will *not* be passed to the focused widget. This event is primarily to allow parent widgets to consume an event before a child widget processes it and it should be used only when there is no better design alternative. @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L629 _public prototype_ `FEventReply OnKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — Called after a key (keyboard, controller, ...) is pressed when this widget has focus (this event bubbles if not handled) @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L639 _public prototype_ `FEventReply OnKeyUp(FGeometry MyGeometry, FKeyEvent InKeyEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Input")` — Called after a key (keyboard, controller, ...) is released when this widget has focus @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L649 _public prototype_ `FEventReply OnAnalogValueChanged(FGeometry MyGeometry, FAnalogInputEvent InAnalogInputEvent);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Input")` — Called when an analog value changes on a button that supports analog @param MyGeometry The Geometry of the widget receiving the event @param  InAnalogInputEvent  Analog Event @return  Returns whether the event was handled, along with other possible actions
- L659 _public prototype_ `FEventReply OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L673 _public prototype_ `FEventReply OnPreviewMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — Just like OnMouseButtonDown, but tunnels instead of bubbling. If this event is handled, OnMouseButtonDown will not be sent. Use this event sparingly as preview events generally make UIs more difficult to reason about. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L683 _public prototype_ `FEventReply OnMouseButtonUp(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — The system calls this method to notify the widget that a mouse button was release within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L693 _public prototype_ `FEventReply OnMouseMove(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — The system calls this method to notify the widget that a mouse moved within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L702 _public prototype_ `void OnMouseEnter(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — The system will use this event to notify a widget that the cursor has entered it. This event is NOT bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event
- L710 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — The system will use this event to notify a widget that the cursor has left it. This event is NOT bubbled. @param MouseEvent Information about the input event
- L719 _public prototype_ `FEventReply OnMouseWheel(FGeometry MyGeometry, const FPointerEvent& MouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — Called when the mouse wheel is spun. This event is bubbled. @param  MouseEvent  Mouse event @return  Returns whether the event was handled, along with other possible actions
- L729 _public prototype_ `FEventReply OnMouseButtonDoubleClick(FGeometry InMyGeometry, const FPointerEvent& InMouseEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Mouse")` — Called when a mouse button is double clicked.  Override this in derived classes. @param  InMyGeometry  Widget geometry @param  InMouseEvent  Mouse button event @return  Returns whether the event was handled, along with other possible actions
- L746 _public prototype_ `void OnDragDetected(FGeometry MyGeometry, const FPointerEvent& PointerEvent, UDragDropOperation*& Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called when Slate detects that a widget started to be dragged. @param  InMyGeometry  Widget geometry @param  PointerEvent  MouseMove that triggered the drag @param  Operation     The drag operation that was detected.
- L756 _public prototype_ `void OnDragCancelled(const FPointerEvent& PointerEvent, UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called when the user cancels the drag operation, typically when they simply release the mouse button after beginning a drag operation, but failing to complete the drag. @param  PointerEvent  Last mouse event from when the drag was canceled. @param  Operation     The drag operation that was canceled.
- L766 _public prototype_ `void OnDragEnter(FGeometry MyGeometry, FPointerEvent PointerEvent, UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called during drag and drop when the drag enters the widget. @param MyGeometry     The geometry of the widget receiving the event. @param PointerEvent   The mouse event from when the drag entered the widget. @param Operation      The drag operation that entered the widget.
- L775 _public prototype_ `void OnDragLeave(FPointerEvent PointerEvent, UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called during drag and drop when the drag leaves the widget. @param PointerEvent   The mouse event from when the drag left the widget. @param Operation      The drag operation that entered the widget.
- L787 _public prototype_ `bool OnDragOver(FGeometry MyGeometry, FPointerEvent PointerEvent, UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called during drag and drop when the the mouse is being dragged over a widget. @param MyGeometry     The geometry of the widget receiving the event. @param PointerEvent   The mouse event from when the drag occurred over the widget. @param Operation      The drag operation over the widget. @return 'true' to indicate that you handled the drag over operation.  Returning 'false' will cause the operation to continue to bubble up.
- L799 _public prototype_ `bool OnDrop(FGeometry MyGeometry, FPointerEvent PointerEvent, UDragDropOperation* Operation);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Drag and Drop")` — Called when the user is dropping something onto a widget.  Ends the drag and drop operation, even if no widget handles this. @param MyGeometry     The geometry of the widget receiving the event. @param PointerEvent   The mouse event from when the drag occurred over the widget. @param Operation      The drag operation over the widget. @return 'true' to indicate you handled the drop operation.
- L809 _public prototype_ `FEventReply OnTouchGesture(FGeometry MyGeometry, const FPointerEvent& GestureEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when the user performs a gesture on trackpad. This event is bubbled. @param MyGeometry     The geometry of the widget receiving the event. @param  GestureEvent  gesture event @return  Returns whether the event was handled, along with other possible actions
- L818 _public prototype_ `FEventReply OnTouchStarted(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when a touchpad touch is started (finger down) @param MyGeometry    The geometry of the widget receiving the event. @param InTouchEvent	The touch event generated
- L827 _public prototype_ `FEventReply OnTouchMoved(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when a touchpad touch is moved  (finger moved) @param MyGeometry    The geometry of the widget receiving the event. @param InTouchEvent	The touch event generated
- L836 _public prototype_ `FEventReply OnTouchEnded(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when a touchpad touch is ended (finger lifted) @param MyGeometry    The geometry of the widget receiving the event. @param InTouchEvent	The touch event generated
- L846 _public prototype_ `FEventReply OnMotionDetected(FGeometry MyGeometry, FMotionEvent InMotionEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when motion is detected (controller or device) e.g. Someone tilts or shakes their controller. @param MyGeometry    The geometry of the widget receiving the event. @param MotionEvent	The motion event generated
- L852 _public prototype_ `void OnMouseCaptureLost();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="Touch Input")` — Called when mouse capture is lost if it was owned by this widget.
- L858 _public prototype_ `void CancelLatentActions();` — `UFUNCTION(BlueprintCallable, Category = "Delay")` — Cancels any pending Delays or timer callbacks for this widget.
- L864 _public prototype_ `void StopAnimationsAndLatentActions();` — `UFUNCTION(BlueprintCallable, Category = "Delay")` — Cancels any pending Delays or timer callbacks for this widget, and stops all active animations on the widget.
- L873 _public prototype_ `FEventReply OnTouchForceChanged(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Touch Input")` — Called when a touchpad force has changed (user pressed down harder or let up) @param MyGeometry    The geometry of the widget receiving the event. @param InTouchEvent	The touch event generated
- L882 _public prototype_ `FEventReply OnTouchFirstMove(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Touch Input")` — Called when a touchpad touch is first moved (initial finger movement) @param MyGeometry    The geometry of the widget receiving the event. @param InTouchEvent	The touch event generated
- L892 _public prototype_ `void BindToAnimationStarted(UWidgetAnimation* Animation, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category=Animation)` — Bind an animation started delegate. @param Animation the animation to listen for starting or finishing. @param Delegate the delegate to call when the animation's state changes
- L900 _public prototype_ `void UnbindFromAnimationStarted(UWidgetAnimation* Animation, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Unbind an animation started delegate. @param Animation the animation to listen for starting or finishing. @param Delegate the delegate to call when the animation's state changes
- L903 _public prototype_ `void UnbindAllFromAnimationStarted(UWidgetAnimation* Animation);` — `UFUNCTION(BlueprintCallable, Category = Animation)`
- L911 _public prototype_ `void BindToAnimationFinished(UWidgetAnimation* Animation, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Bind an animation finished delegate. @param Animation the animation to listen for starting or finishing. @param Delegate the delegate to call when the animation's state changes
- L919 _public prototype_ `void UnbindFromAnimationFinished(UWidgetAnimation* Animation, FWidgetAnimationDynamicEvent Delegate);` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Unbind an animation finished delegate. @param Animation the animation to listen for starting or finishing. @param Delegate the delegate to call when the animation's state changes
- L922 _public prototype_ `void UnbindAllFromAnimationFinished(UWidgetAnimation* Animation);` — `UFUNCTION(BlueprintCallable, Category = Animation)`
- L932 _public prototype_ `void BindToAnimationEvent(UWidgetAnimation* Animation, FWidgetAnimationDynamicEvent Delegate, EWidgetAnimationEvent AnimationEvent, FName UserTag = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Allows binding to a specific animation's event. @param Animation the animation to listen for starting or finishing. @param Delegate the delegate to call when the animation's state changes @param AnimationEvent the event to watch for. @param UserTag Scopes the delegate to only be called when the animation completes with a specific tag set on it when it was played.
- L935 _public function_ `virtual bool IsEditorUtility() const` — Is this widget an editor utility widget.
- L945 _protected prototype_ `void OnAnimationStarted( const UWidgetAnimation* Animation );` — `UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "Animation")` — Called when an animation is started. @param Animation the animation that started
- L947 _protected prototype_ `virtual void OnAnimationStarted_Implementation(const UWidgetAnimation* Animation);`
- L955 _protected prototype_ `void OnAnimationFinished( const UWidgetAnimation* Animation );` — `UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "Animation")` — Called when an animation has either played all the way through or is stopped @param Animation The animation that has finished playing
- L957 _protected prototype_ `virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation);`
- L961 _protected prototype_ `void BroadcastAnimationStateChange(const UUMGSequencePlayer& Player, EWidgetAnimationEvent AnimationEvent);` — `UE_DEPRECATED(5.6, "UUMGSequencePlayer is deprecated")` — Broadcast any events based on a state transition for the sequence player, started, finished...etc.
- L965 _private prototype_ `void BroadcastAnimationStateChange(const FWidgetAnimationState& State, EWidgetAnimationEvent AnimationEvent);`
- L967 _private prototype_ `void BroadcastAnimationStateChange(const UWidgetAnimation* Animation, FName UserTag, EWidgetAnimationEvent AnimationEvent);`
- L969 _private prototype_ `void BroadcastAnimationStartedPlaying(FWidgetAnimationState& State);`
- L970 _private prototype_ `void BroadcastAnimationFinishedPlaying(FWidgetAnimationState& State);`
- L975 _protected function_ `FOnWidgetAnimationEvent& OnAnimationStartedPlaying()` — Called when a sequence player is finished playing an animation
- L978 _protected function_ `FOnWidgetAnimationEvent& OnAnimationFinishedPlaying()` — Called when a sequence player is finished playing an animation
- L981 _protected function_ `virtual void OnAnimationStartedPlaying(UUMGSequencePlayer& Player)` — `UE_DEPRECATED(5.6, "UUMGSequencePlayer is deprecated")`
- L984 _protected function_ `virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)` — `UE_DEPRECATED(5.6, "UUMGSequencePlayer is deprecated")`
- L988 _private member_ `FOnWidgetAnimationEvent OnAnimationStartedPlayingEvent;`
- L989 _private member_ `FOnWidgetAnimationEvent OnAnimationFinishedPlayingEvent;`
- L996 _public member_ `FLinearColor ColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetColorAndOpacity", Category = "Appearance")` — The color and opacity of this widget.  Tints all child widgets.
- L999 _public member_ `FGetLinearColor ColorAndOpacityDelegate;` — `UPROPERTY()`
- L1007 _public member_ `FSlateColor ForegroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetForegroundColor", Category = "Appearance")` — The foreground color of the widget, this is inherited by sub widgets.  Any color property that is marked as inherit will use this color.
- L1010 _public member_ `FGetSlateColor ForegroundColorDelegate;` — `UPROPERTY()`
- L1014 _public member_ `FOnVisibilityChangedEvent OnVisibilityChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Appearance|Event")` — Called when the visibility has changed
- L1015 _public prototype_ `DECLARE_EVENT_OneParam(UUserWidget, FNativeOnVisibilityChangedEvent, ESlateVisibility);`
- L1016 _public member_ `FNativeOnVisibilityChangedEvent OnNativeVisibilityChanged;`
- L1018 _public prototype_ `DECLARE_EVENT_OneParam(UUserWidget, FNativeOnDestruct, UUserWidget*);`
- L1019 _public member_ `FNativeOnDestruct OnNativeDestruct;`
- L1024 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetPadding", Category = "Appearance")` — The padding area around the content.
- L1028 _public member_ `int32 Priority;` — `UE_DEPRECATED(5.2, "Direct access to Priority is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetInputActionPriority", Setter = "SetInputActionPriority", BlueprintSetter = "SetInputActionPriority", Category = "Input")`
- L1033 _public member_ `uint8 bIsFocusable : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsFocusable", Setter = "SetIsFocusable", Category = "Interaction")` — Setting this flag to true, allows this widget to accept focus when clicked, or when navigated to.
- L1037 _public member_ `uint8 bStopAction : 1;` — `UE_DEPRECATED(5.2, "Direct access to bStopAction is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsInputActionBlocking", Setter = "SetInputActionBlocking", BlueprintSetter = "SetInputActionBlocking", Category = "Input")`
- L1046 _public member_ `uint8 bAutomaticallyRegisterInputOnConstruction : 1;` — `UPROPERTY()` — If true, this widget will automatically register its own input component upon construction. This will allow the use of binding input delegates in the event graph. This is set during the compilation of the widget blueprint.
- L1056 _public prototype_ `void SetColorAndOpacity(FLinearColor InColorAndOpacity);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Appearance")` — Sets the tint of the widget, this affects all child widgets. @param InColorAndOpacity	The tint to apply to all child widgets.
- L1061 _public prototype_ `const FLinearColor& GetColorAndOpacity() const;` — Gets the tint of the widget.
- L1070 _public prototype_ `void SetForegroundColor(FSlateColor InForegroundColor);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Appearance")` — Sets the foreground color of the widget, this is inherited by sub widgets.  Any color property that is marked as inherit will use this color. @param InForegroundColor	The foreground color.
- L1076 _public prototype_ `const FSlateColor& GetForegroundColor() const;` — Gets the foreground color of the widget, this is inherited by sub widgets.  Any color property that is marked as inherit uses this color.
- L1082 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Appearance")` — Sets the padding for the user widget, putting a larger gap between the widget border and it's root widget.
- L1087 _public prototype_ `FMargin GetPadding() const;` — Gets the padding for the user widget.
- L1092 _public prototype_ `int32 GetInputActionPriority() const;` — Gets the priority of the input action.
- L1097 _public prototype_ `bool IsInputActionBlocking() const;` — Returns whether the input action is blocking.
- L1102 _public prototype_ `bool IsFocusable() const;` — Sets whether this widget to accept focus when clicked, or when navigated to.
- L1104 _public prototype_ `void SetIsFocusable(bool InIsFocusable);`
- L1117 _public prototype_ `void QueuePlayAnimation(UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation in this widget a specified number of times @param InAnimation The animation to play @param StartAtTime The time in the animation from which to start playing, relative to the start position. For looped animations, this will only affect the first playback of the animation. @param NumLoopsToPlay The number of times to loop this animation (0 to loop indefinitely) @param PlaybackSpeed The speed at which the animation should play @param PlayMode Specifies the playback mode @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1131 _public prototype_ `void QueuePlayAnimationTimeRange(UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, float EndAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation in this widget a specified number of times stopping at a specified time @param InAnimation The animation to play @param StartAtTime The time in the animation from which to start playing, relative to the start position. For looped animations, this will only affect the first playback of the animation. @param EndAtTime The absolute time in the animation where to stop, this is only considered in the last loop. @param NumLoopsToPlay The number of times to loop this animation (0 to loop indefinitely) @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1144 _public prototype_ `void QueuePlayAnimationForward(UWidgetAnimation* InAnimation, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation on this widget relative to it's current state forward.  You should use this version in situations where say a user can click a button and that causes a panel to slide out, and you want to reverse that same animation to begin sliding in the opposite direction. @param InAnimation The animation to play @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1157 _public prototype_ `void QueuePlayAnimationReverse(UWidgetAnimation* InAnimation, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation on this widget relative to it's current state in reverse.  You should use this version in situations where say a user can click a button and that causes a panel to slide out, and you want to reverse that same animation to begin sliding in the opposite direction. @param InAnimation The animation to play @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1165 _public prototype_ `void QueueStopAnimation(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, Category="User Interface|Animation")` — Stops an already running animation in this widget @param The name of the animation to stop
- L1171 _public prototype_ `void QueueStopAllAnimations();` — `UFUNCTION(BlueprintCallable, Category="User Interface|Animation")` — Stop All actively running animations.
- L1180 _public prototype_ `float QueuePauseAnimation(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Animation")` — Pauses an already running animation in this widget @param The name of the animation to pause @return the time point the animation was at when it was paused, relative to its start position.  Use this as the StartAtTime when you trigger PlayAnimation.
- L1193 _public prototype_ `FWidgetAnimationHandle PlayAnimation(UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation in this widget a specified number of times @param InAnimation The animation to play @param StartAtTime The time in the animation from which to start playing, relative to the start position. For looped animations, this will only affect the first playback of the animation. @param NumLoopsToPlay The number of times to loop this animation (0 to loop indefinitely) @param PlaybackSpeed The speed at which the animation should play @param PlayMode Specifies the playback mode @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1207 _public prototype_ `FWidgetAnimationHandle PlayAnimationTimeRange(UWidgetAnimation* InAnimation, float StartAtTime = 0.0f, float EndAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation in this widget a specified number of times stopping at a specified time @param InAnimation The animation to play @param StartAtTime The time in the animation from which to start playing, relative to the start position. For looped animations, this will only affect the first playback of the animation. @param EndAtTime The absolute time in the animation where to stop, this is only considered in the last loop. @param NumLoopsToPlay The number of times to loop this animation (0 to loop indefinitely) @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1220 _public prototype_ `FWidgetAnimationHandle PlayAnimationForward(UWidgetAnimation* InAnimation, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation on this widget relative to it's current state forward.  You should use this version in situations where say a user can click a button and that causes a panel to slide out, and you want to reverse that same animation to begin sliding in the opposite direction. @param InAnimation The animation to play @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1233 _public prototype_ `FWidgetAnimationHandle PlayAnimationReverse(UWidgetAnimation* InAnimation, float PlaybackSpeed = 1.0f, bool bRestoreState = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Plays an animation on this widget relative to it's current state in reverse.  You should use this version in situations where say a user can click a button and that causes a panel to slide out, and you want to reverse that same animation to begin sliding in the opposite direction. @param InAnimation The animation to play @param PlayMode Specifies the playback mode @param PlaybackSpeed The speed at which the animation should play @param bRestoreState Restores widgets to their pre-animated state when the animation stops
- L1241 _public prototype_ `void StopAnimation(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, Category="User Interface|Animation")` — Stops an already running animation in this widget @param The name of the animation to stop
- L1249 _public prototype_ `void StopAllAnimations();` — `UFUNCTION(BlueprintCallable, Category="User Interface|Animation")` — Stop All actively running animations. @param The name of the animation to stop
- L1258 _public prototype_ `float PauseAnimation(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Animation")` — Pauses an already running animation in this widget @param The name of the animation to pause @return the time point the animation was at when it was paused, relative to its start position.  Use this as the StartAtTime when you trigger PlayAnimation.
- L1267 _public prototype_ `float GetAnimationCurrentTime(const UWidgetAnimation* InAnimation) const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Gets the current time of the animation in this widget @param The name of the animation to get the current time for @return the current time of the animation.
- L1276 _public prototype_ `void SetAnimationCurrentTime(const UWidgetAnimation* InAnimation, float InTime);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Sets the current time of the animation in this widget. Does not change state. @param The name of the animation to get the current time for @param The current time of the animation.
- L1285 _public prototype_ `bool IsAnimationPlaying(const UWidgetAnimation* InAnimation) const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Animation")` — Gets whether an animation is currently playing on this widget. @param InAnimation The animation to check the playback status of @return True if the animation is currently playing
- L1291 _public prototype_ `bool IsAnyAnimationPlaying() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Animation")` — @return True if any animation is currently playing
- L1300 _public prototype_ `void SetNumLoopsToPlay(const UWidgetAnimation* InAnimation, int32 NumLoopsToPlay);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Changes the number of loops to play given a playing animation @param InAnimation The animation that is already playing @param NumLoopsToPlay The number of loops to play. (0 to loop indefinitely)
- L1309 _public prototype_ `void SetPlaybackSpeed(const UWidgetAnimation* InAnimation, float PlaybackSpeed = 1.0f);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Changes the playback rate of a playing animation @param InAnimation The animation that is already playing @param PlaybackRate Playback rate multiplier (1 is default)
- L1317 _public prototype_ `void ReverseAnimation(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — If an animation is playing, this function will reverse the playback. @param InAnimation The playing animation that we want to reverse
- L1325 _public prototype_ `bool IsAnimationPlayingForward(const UWidgetAnimation* InAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — returns true if the animation is currently playing forward, false otherwise. @param InAnimation The playing animation that we want to know about
- L1331 _public prototype_ `void FlushAnimations();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")` — Flushes all animations on all widgets to guarantee that any queued updates are processed before this call returns
- L1335 _public function_ `template<typename ExtensionType> ExtensionType* GetExtension() const` — Find the first extension of the requested type.
- L1342 _public prototype_ `UUserWidgetExtension* GetExtension(TSubclassOf<UUserWidgetExtension> ExtensionType) const;` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension", Meta = (DeterminesOutputType = "ExtensionType"))` — Find the first extension of the requested type.
- L1346 _public prototype_ `TArray<UUserWidgetExtension*> GetExtensions(TSubclassOf<UUserWidgetExtension> ExtensionType) const;` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension", Meta = (DeterminesOutputType = "ExtensionType"))` — Find the extensions of the requested type.
- L1350 _public function_ `template<typename ExtensionType> ExtensionType* AddExtension()` — Add the extension of the requested type.
- L1357 _public prototype_ `UUserWidgetExtension* AddExtension(TSubclassOf<UUserWidgetExtension> InExtensionType);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension", Meta = (DeterminesOutputType = "InExtensionType"))` — Add the extension of the requested type.
- L1361 _public function_ `template<typename ExtensionType> ExtensionType& GetOrAddExtension()` — Find an existing extension of the request type, or create it if not found
- L1368 _public prototype_ `UUserWidgetExtension* GetOrAddExtension(TSubclassOf<UUserWidgetExtension> InExtensionType);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension", Meta = (DeterminesOutputType = "InExtensionType"))` — Find an existing extension of the request type, or create it if not found
- L1372 _public prototype_ `void RemoveExtension(UUserWidgetExtension* InExtension);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension")` — Remove the extension.
- L1376 _public function_ `template<typename ExtensionType> void RemoveExtensions()` — Remove all extensions of the requested type.
- L1383 _public prototype_ `void RemoveExtensions(TSubclassOf<UUserWidgetExtension> InExtensionType);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Extension")` — Remove all extensions of the requested type.
- L1391 _public prototype_ `void PlaySound(class USoundBase* SoundToPlay);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Sound", meta=( DeprecatedFunction, DeprecationMessage="Use the UGameplayStatics::PlaySound2D instead." ))` — Plays a sound through the UI @param The sound to play
- L1399 _public prototype_ `bool SetDesiredFocusWidget(FName WidgetName);` — Sets the child Widget that should receive focus when this UserWidget gets focus using it's name. @param WidgetName Name of the Widget to forward the focus to when this widget receives focus. @return True if the Widget is set properly. Will return false if we can't find a child widget with the specified name.
- L1408 _public prototype_ `bool SetDesiredFocusWidget(UWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category = "User Interface|Focus")` — Sets the child Widget that should receive focus when this UserWidget gets focus. @param Widget Widget to forward the focus to when this widget receives focus @return True if the Widget is set properly. Will return false if it's not a child of this UserWidget.
- L1411 _public prototype_ `FName GetDesiredFocusWidgetName() const;` — @returns The Name of the Widget that should receive focus when this UserWidget gets focus.
- L1414 _public prototype_ `UWidget* GetDesiredFocusWidget() const;` — @returns The Widget that should receive focus when this UserWidget gets focus.
- L1417 _public prototype_ `UWidget* GetWidgetHandle(TSharedRef<SWidget> InWidget);` — @returns The UObject wrapper for a given SWidget
- L1420 _public prototype_ `UWidget* GetRootWidget() const;` — @returns The root UObject widget wrapper
- L1423 _public prototype_ `TSharedPtr<SWidget> GetSlateWidgetFromName(const FName& Name) const;` — @returns The slate widget corresponding to a given name
- L1426 _public prototype_ `UWidget* GetWidgetFromName(const FName& Name) const;` — @returns The uobject widget corresponding to a given name
- L1429 _public prototype_ `virtual bool IsAsset() const;`
- L1430 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L1435 _public prototype_ `bool IsPlayingAnimation() const;` — `UFUNCTION(BlueprintCallable, Category="User Interface|Animation")` — Are we currently playing any animations?
- L1439 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L1442 _public prototype_ `virtual void SetDesignerFlags(EWidgetDesignFlags NewFlags) override;`
- L1443 _public prototype_ `virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;`
- L1444 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1447 _public prototype_ `void UpdateBindingForSlot(FName SlotName);` — Update the binding for this namedslot if the name is not found but GUID is matched.
- L1450 _public prototype_ `void AssignGUIDToBindings();` — Add the GUID of each Namedslot widget to its corresponding binding, if any.
- L1457 _public prototype_ `void ValidateBlueprint(const UWidgetTree& BlueprintWidgetTree, class IWidgetCompilerLog& CompileLog) const;` — Final step of Widget Blueprint compilation. Allows widgets to perform custom validation and trigger compiler outputs as needed. @see ValidateCompiledDefaults @see ValidateCompiledWidgetTree
- L1467 _public function_ `virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, class IWidgetCompilerLog& CompileLog) const` — Override to perform any custom inspections of the default widget tree at the end of compilation. Note: The WidgetTree and BindWidget properties of this user widget will not be established at this point, so be sure to inspect only the given BlueprintWidgetTree. Tip: If you need to validate properties of BindWidget members, you can search for them by property name within the widget tree.
- L1470 _public prototype_ `static UUserWidget* CreateWidgetInstance(UWidget& OwningWidget, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);`
- L1471 _public prototype_ `static UUserWidget* CreateWidgetInstance(UWidgetTree& OwningWidgetTree, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);`
- L1472 _public prototype_ `static UUserWidget* CreateWidgetInstance(APlayerController& OwnerPC, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);`
- L1473 _public prototype_ `static UUserWidget* CreateWidgetInstance(UGameInstance& GameInstance, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);`
- L1474 _public prototype_ `static UUserWidget* CreateWidgetInstance(UWorld& World, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);`
- L1478 _private prototype_ `static UUserWidget* CreateInstanceInternal(UObject* Outer, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName, UWorld* World, ULocalPlayer* LocalPlayer);`
- L1480 _private prototype_ `void ClearStoppedAnimationStates();`
- L1483 _private prototype_ `void UpdatePlayerContextIfInvalid(const FLocalPlayerContext& ParentPlayerContext);` — If this widget's player context is invalid, this function will set it to the provided player context, otherwise it will keep its current player context and call CheckUpdatePlayerContext on its children
- L1489 _public member_ `TArray<FQueuedWidgetAnimationTransition> QueuedWidgetAnimationTransitions;` — `UPROPERTY(Transient)` — Animation transitions to trigger on next tick
- L1493 _public member_ `TArray<TObjectPtr<UUMGSequencePlayer>> ActiveSequencePlayers;` — `UE_DEPRECATED(5.6, "Please use ActiveAnimations")` — `UPROPERTY(Transient)`
- L1497 _public member_ `TObjectPtr<UUMGSequenceTickManager> AnimationTickManager;` — `UPROPERTY(Transient)` — Global tick manager for running widget animations
- L1501 _public member_ `TArray<TObjectPtr<UUMGSequencePlayer>> StoppedSequencePlayers;` — `UE_DEPRECATED(5.6, "Please use ActiveAnimations")` — `UPROPERTY(Transient)`
- L1506 _private member_ `TArray<TSharedRef<FWidgetAnimationState>> ActiveAnimations;` — All the sequences currently playing
- L1509 _private member_ `bool bIsTickingAnimations = false;` — True when we are ticking our active animations
- L1515 _private member_ `TArray<FNamedSlotBinding> NamedSlotBindings;` — `UPROPERTY()` — Stores the widgets being assigned to named slots
- L1519 _private member_ `TArray<TObjectPtr<UUserWidgetExtension>> Extensions;` — `UPROPERTY()` — The UserWidget extensions
- L1524 _public member_ `TObjectPtr<UWidgetTree> WidgetTree;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — The widget tree contained inside this user widget initialized by the blueprint
- L1532 _public member_ `FVector2D DesignTimeSize;` — `UPROPERTY()` — Stores the design time desired size of the user widget
- L1535 _public member_ `EDesignPreviewSizeMode DesignSizeMode;` — `UPROPERTY()`
- L1539 _public member_ `FText PaletteCategory;` — `UPROPERTY()` — The category this widget appears in the palette.
- L1546 _public member_ `TObjectPtr<UTexture2D> PreviewBackground;` — `UPROPERTY(EditDefaultsOnly, Category="Designer")` — A preview background that you can use when designing the UI to get a sense of scale on the screen.  Use a texture with a screenshot of your game in it, for example if you were designing a HUD.
- L1552 _public member_ `uint8 bHasScriptImplementedTick : 1;` — `UPROPERTY()` — If a widget has an implemented tick blueprint function
- L1556 _public member_ `uint8 bHasScriptImplementedPaint : 1;` — `UPROPERTY()` — If a widget has an implemented paint blueprint function
- L1561 _private member_ `uint8 bInitialized : 1;` — Has this widget been initialized by its class yet?
- L1564 _private member_ `uint8 bAreExtensionsPreConstructed : 1;` — Has this widget been preconstructed and we need to call PreConstruct on new extension.
- L1567 _private member_ `uint8 bAreExtensionsConstructed : 1;` — Has this widget been constructed and we need to call Construct on new extension.
- L1570 _private member_ `uint8 bStoppingAllAnimations : 1;` — If we're stopping all animations, don't allow new animations to be created as side-effects.
- L1574 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L1576 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L1577 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L1580 _protected prototype_ `FMargin GetFullScreenOffset() const;` — `UE_DEPRECATED(5.1, "GetFullScreenOffset is deprecated. Use the GameViewportSubsystem.")`
- L1582 _protected prototype_ `virtual void NativeOnInitialized();`
- L1583 _protected prototype_ `virtual void NativePreConstruct();`
- L1584 _protected prototype_ `virtual void NativeConstruct();`
- L1585 _protected prototype_ `virtual void NativeDestruct();`
- L1586 _protected prototype_ `virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);`
- L1592 _protected prototype_ `virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;` — Native implemented paint function for the Widget Returns the maximum LayerID painted on
- L1594 _protected function_ `inline FVector2D GetMinimumDesiredSize() const`
- L1595 _protected prototype_ `void SetMinimumDesiredSize(FVector2D InMinimumDesiredSize);`
- L1597 _protected prototype_ `virtual bool NativeIsInteractable() const;`
- L1598 _protected prototype_ `virtual bool NativeSupportsKeyboardFocus() const;`
- L1599 _protected function_ `virtual bool NativeSupportsCustomNavigation() const`
- L1601 _protected prototype_ `virtual FReply NativeOnFocusReceived( const FGeometry& InGeometry, const FFocusEvent& InFocusEvent );`
- L1602 _protected prototype_ `virtual void NativeOnFocusLost( const FFocusEvent& InFocusEvent );`
- L1603 _protected prototype_ `virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent);`
- L1604 _protected prototype_ `virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent);`
- L1605 _protected prototype_ `virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent);`
- L1606 _protected prototype_ `virtual FNavigationReply NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply);`
- L1607 _protected prototype_ `virtual FReply NativeOnKeyChar( const FGeometry& InGeometry, const FCharacterEvent& InCharEvent );`
- L1608 _protected prototype_ `virtual FReply NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent );`
- L1609 _protected prototype_ `virtual FReply NativeOnKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent );`
- L1610 _protected prototype_ `virtual FReply NativeOnKeyUp( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent );`
- L1611 _protected prototype_ `virtual FReply NativeOnAnalogValueChanged( const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent );`
- L1612 _protected prototype_ `virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1613 _protected prototype_ `virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1614 _protected prototype_ `virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1615 _protected prototype_ `virtual FReply NativeOnMouseMove( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1616 _protected prototype_ `virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1617 _protected prototype_ `virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent );`
- L1618 _protected prototype_ `virtual FReply NativeOnMouseWheel( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1619 _protected prototype_ `virtual FReply NativeOnMouseButtonDoubleClick( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent );`
- L1620 _protected prototype_ `virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation );`
- L1621 _protected prototype_ `virtual void NativeOnDragEnter( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );`
- L1622 _protected prototype_ `virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );`
- L1623 _protected prototype_ `virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );`
- L1624 _protected prototype_ `virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );`
- L1625 _protected prototype_ `virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );`
- L1626 _protected prototype_ `virtual FReply NativeOnTouchGesture( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent );`
- L1627 _protected prototype_ `virtual FReply NativeOnTouchStarted( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent );`
- L1628 _protected prototype_ `virtual FReply NativeOnTouchMoved( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent );`
- L1629 _protected prototype_ `virtual FReply NativeOnTouchEnded( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent );`
- L1630 _protected prototype_ `virtual FReply NativeOnMotionDetected( const FGeometry& InGeometry, const FMotionEvent& InMotionEvent );`
- L1631 _protected prototype_ `virtual FReply NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent);`
- L1632 _protected prototype_ `virtual FReply NativeOnTouchFirstMove(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent);`
- L1633 _protected prototype_ `virtual FCursorReply NativeOnCursorQuery( const FGeometry& InGeometry, const FPointerEvent& InCursorEvent );`
- L1634 _protected prototype_ `virtual FNavigationReply NativeOnNavigation(const FGeometry& InGeometry, const FNavigationEvent& InNavigationEvent);`
- L1635 _protected prototype_ `virtual void NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent);`
- L1636 _protected function_ `virtual void NativeOnFinishedPointerInput()`
- L1643 _protected prototype_ `void TickActionsAndAnimation(float InDeltaTime);` — Ticks the active sequences and latent actions that have been scheduled for this Widget.
- L1646 _protected function_ `void PostTickActionsAndAnimation(float InDeltaTime)` — `UE_DEPRECATED(5.6, "This method isn't needed anymore")`
- L1648 _protected prototype_ `void RemoveObsoleteBindings(const TArray<FName>& NamedSlots);`
- L1650 _protected prototype_ `TSharedPtr<const FWidgetAnimationState> GetAnimationState(const UWidgetAnimation* InAnimation) const;`
- L1651 _protected prototype_ `TSharedPtr<FWidgetAnimationState> GetAnimationState(const UWidgetAnimation* InAnimation);`
- L1652 _protected prototype_ `TSharedPtr<FWidgetAnimationState> GetOrAddAnimationState(UWidgetAnimation* InAnimation);`
- L1654 _protected prototype_ `void ExecuteQueuedAnimationTransitions();`
- L1656 _protected prototype_ `void ConditionalTearDownAnimations();`
- L1658 _protected prototype_ `void TearDownAnimations();`
- L1660 _protected prototype_ `void DisableAnimations();`
- L1662 _protected prototype_ `void Invalidate(EInvalidateWidgetReason InvalidateReason);`
- L1669 _protected prototype_ `void ListenForInputAction( FName ActionName, TEnumAsByte< EInputEvent > EventType, bool bConsume, FOnInputAction Callback );` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — Listens for a particular Player Input Action by name.  This requires that those actions are being executed, and that we're not currently in UI-Only Input Mode.
- L1675 _protected prototype_ `void StopListeningForInputAction( FName ActionName, TEnumAsByte< EInputEvent > EventType );` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — Removes the binding for a particular action's callback.
- L1681 _protected prototype_ `void StopListeningForAllInputActions();` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — Stops listening to all input actions, and unregisters the input component with the player controller.
- L1689 _protected prototype_ `void RegisterInputComponent();` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — ListenForInputAction will automatically Register an Input Component with the player input system. If you however, want to Pause and Resume, listening for a set of actions, the best way is to use UnregisterInputComponent to pause, and RegisterInputComponent to resume listening.
- L1697 _protected prototype_ `void UnregisterInputComponent();` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — StopListeningForAllInputActions will automatically Register an Input Component with the player input system. If you however, want to Pause and Resume, listening for a set of actions, the best way is to use UnregisterInputComponent to pause, and RegisterInputComponent to resume listening.
- L1703 _protected prototype_ `bool IsListeningForInputAction( FName ActionName ) const;` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))` — Checks if the action has a registered callback with the input component.
- L1706 _protected prototype_ `void SetInputActionPriority( int32 NewPriority );` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))`
- L1709 _protected prototype_ `void SetInputActionBlocking( bool bShouldBlock );` — `UFUNCTION(BlueprintCallable, Category = "Input", meta = ( BlueprintProtected = "true" ))`
- L1711 _protected prototype_ `void OnInputAction( FOnInputAction Callback );`
- L1714 _protected prototype_ `virtual void InitializeInputComponent() final;` — `UE_DEPRECATED(5.7, "InitializeInputComponent is deprecated. bAutomaticallyRegisterInputOnConstruction will be set on compilation of this widget and automatically create the input component instead.")`
- L1717 _private member_ `FVector2D MinimumDesiredSize;`
- L1725 _private member_ `EWidgetTickFrequency TickFrequency;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance", meta=(AllowPrivateAccess="true"))` — This widget is allowed to tick. If this is unchecked tick will never be called, animations will not play correctly, and latent actions will not execute. Uncheck this for performance reasons only
- L1728 _private member_ `FWidgetChild DesiredFocusWidget;` — `UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))`
- L1740 _protected prototype_ `virtual void CreateInputComponent();` — Spawns the InputComponent and binds any script delegates if bAutomaticallyRegisterInputOnConstruction is true. bAutomaticallyRegisterInputOnConstruction is true when there are input event nodes in the graph of this widget, which would in turn need to be bound in order to receive their callbacks. This should only happen once per widget when it is spawned and initialized.
- L1746 _protected prototype_ `virtual void StartProcessingInputScriptDelegates();` — Pushes the input component to the input stack and allows for any script delegates on this widget to get called.
- L1755 _protected prototype_ `virtual void StopProcessingInputScriptDelegates();` — Removes this widget's input component from the input stack, stopping any script delegates from being called. This does not actually destroy or unbind any of the delegates yet, because the widget may be added to the viewport again the future, and the binding process can be expensive.
- L1761 _protected prototype_ `virtual void DestroyInputComponent();` — Unbinds all script delegates that this widget has bound to on its input component, removes it from the input stack, and deletes the actual input component object.
- L1764 _protected member_ `TObjectPtr<class UInputComponent> InputComponent;` — `UPROPERTY(Transient, DuplicateTransient)`
- L1769 _protected prototype_ `void HandleOwningLocalPlayerControllerChanged(APlayerController* NewPlayerController);` — A callback bound to this widget's owning local player which will fire when the player controller has changed.
- L1770 _protected prototype_ `void StartListeningForPlayerControllerChanges();`
- L1771 _protected prototype_ `void StopListeningForPlayerControllerChanges();`
- L1775 _protected member_ `TArray<FAnimationEventBinding> AnimationCallbacks;` — `UPROPERTY(Transient, DuplicateTransient)`
- L1778 _private prototype_ `static void OnLatentActionsChanged(UObject* ObjectWhichChanged, ELatentActionChangeType ChangeType);`
- L1781 _private member_ `FLocalPlayerContext PlayerContext;` — The player context that is associated with this UI.  Think of this as the owner of the UI.
- L1784 _private member_ `mutable TWeakObjectPtr<UWorld> CachedWorld;` — Get World calls can be expensive for Widgets, we speed them up by caching the last found world until it goes away.
- L1786 _private prototype_ `static uint32& GetInitializingFromWidgetTree();`
- L1790 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, ColorAndOpacity);`
- L1791 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, ForegroundColor);`

#### Free symbols / members of external scopes

- L270 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConstructEvent);`
- L270 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConstructEvent);`
- L272 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnInputAction );`
- L272 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnInputAction );`
- L274 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisibilityChangedEvent, ESlateVisibility, InVisibility);`
- L274 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisibilityChangedEvent, ESlateVisibility, InVisibility);`
- L1015 _delegate_ `DECLARE_EVENT_OneParam(UUserWidget, FNativeOnVisibilityChangedEvent, ESlateVisibility);`
- L1018 _delegate_ `DECLARE_EVENT_OneParam(UUserWidget, FNativeOnDestruct, UUserWidget*);`
- L1809 _macro_ `#define LOCTEXT_NAMESPACE "UMG"`
- L1811 _namespace_ `namespace CreateWidgetHelpers`
- L1813 _prototype_ `bool ValidateUserWidgetClass(const UClass* UserWidgetClass);` (scope `CreateWidgetHelpers`)
- L1819 _function_ `template <typename WidgetT = UUserWidget, typename OwnerType = UObject> WidgetT* CreateWidget(OwnerType OwningObject, TSubclassOf<UUserWidget> UserWidgetClass = WidgetT::StaticClass(), FName WidgetName = NAME_None)`

### `Source/Runtime/UMG/Public/Blueprint/UserWidgetBlueprint.h` (Public)


#### class `UUserWidgetBlueprint`  
`class UUserWidgetBlueprint : public UBlueprint`  
_L9-18_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBlueprint`
- L15 _public function_ `virtual bool AllowEditorWidget() const` — Does the editor support widget from an editor package.
- L17 _public function_ `virtual bool ShouldAutomaticallyRegisterInputOnConstruction() const override`

### `Source/Runtime/UMG/Public/Blueprint/UserWidgetPool.h` (Public)


#### struct `FUserWidgetPool`  
`struct FUserWidgetPool`  
_L26-164_
- reflection: `USTRUCT()`
- desc: Pools UUserWidget instances to minimize UObject and SWidget allocations for UMG elements with dynamic entries. Note that if underlying Slate instances are released when a UserWidget instance becomes inactive, NativeConstruct & NativeDestruct will be called when UUserWidget instances are made active or inactive, respectively, provided the widget isn't actively referenced in the Slate hierarchy (i.e. if the shared reference count on the widget goes from/to 0). WARNING: Be sure to release the pool's Slate widgets within the owning widget's ReleaseSlateResources call to prevent leaking due to circular references Otherwise the cached references to SObjectWidgets will keep the UUserWidgets - and all that they reference - alive @see UListView @see UDynamicEntryBox
- L31 _public prototype_ `FUserWidgetPool() = default;`
- L32 _public prototype_ `FUserWidgetPool(UWidget& InOwningWidget);`
- L33 _public prototype_ `~FUserWidgetPool();`
- L36 _public prototype_ `void SetWorld(UWorld* OwningWorld);` — In the case that you don't have an owner widget, you should set a world to your pool, or it won't be able to construct widgets.
- L43 _public prototype_ `void SetDefaultPlayerController(APlayerController* InDefaultPlayerController);` — In the case a pool has no owner widget, a default player controller can optionally be specified allowing greater control in split screen scenarios. The following priority rules are applied when determining the controller which should own created widgets: Controller of owning widget (if set) > Default player controller (if set) > First local player controller from world.
- L46 _public prototype_ `void RebuildWidgets();` — Triggers RebuildWidget on all currently active UserWidget instances
- L49 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Report any references to UObjects to the reference collector (only necessary if this is not already a UPROPERTY)
- L51 _public function_ `bool IsInitialized() const`
- L52 _public function_ `const TArray<UUserWidget*>& GetActiveWidgets() const`
- L59 _public function_ `template <typename UserWidgetT = UUserWidget> UserWidgetT* GetOrCreateInstance(TSubclassOf<UserWidgetT> WidgetClass)` — Gets an instance of a widget of the given class. The underlying slate is stored automatically as well, so the returned widget is fully constructed and GetCachedWidget will return a valid SWidget.
- L69 _public typedef_ `using WidgetConstructFunc = TFunctionRef<TSharedPtr<SObjectWidget>(UUserWidget*, TSharedRef<SWidget>)>;`
- L73 _public function_ `template <typename UserWidgetT = UUserWidget> UserWidgetT* GetOrCreateInstance(TSubclassOf<UserWidgetT> WidgetClass, WidgetConstructFunc ConstructWidgetFunc)` — Gets an instance of the widget this factory is for with a custom underlying SObjectWidget type
- L79 _public prototype_ `void Release(UUserWidget* Widget, bool bReleaseSlate = false);` — Return a widget object to the pool, allowing it to be reused in the future
- L82 _public prototype_ `void Release(TArray<UUserWidget*> Widgets, bool bReleaseSlate = false);` — Return a widget object to the pool, allowing it to be reused in the future
- L85 _public prototype_ `void ReleaseAll(bool bReleaseSlate = false);` — Returns all active widget objects to the inactive pool and optionally destroys all cached underlying slate widgets.
- L88 _public prototype_ `void ResetPool();` — Full reset of all created widget objects (and any cached underlying slate)
- L91 _public prototype_ `void ReleaseInactiveSlateResources();` — Reset of all cached underlying Slate widgets, only for inactive widgets in the pool.
- L94 _public function_ `void ReleaseSlateResources()` — `UE_DEPRECATED(4.24, "Use ReleaseAllSlateResources instead.")`
- L97 _public prototype_ `void ReleaseAllSlateResources();` — Reset of all cached underlying Slate widgets, but not the active UUserWidget objects
- L101 _private function_ `template <typename UserWidgetT = UUserWidget> UserWidgetT* AddActiveWidgetInternal(TSubclassOf<UserWidgetT> WidgetClass, WidgetConstructFunc ConstructWidgetFunc)`
- L155 _private member_ `TArray<TObjectPtr<UUserWidget>> ActiveWidgets;` — `UPROPERTY(Transient)`
- L158 _private member_ `TArray<TObjectPtr<UUserWidget>> InactiveWidgets;` — `UPROPERTY(Transient)`
- L160 _private member_ `TWeakObjectPtr<UWidget> OwningWidget;`
- L161 _private member_ `TWeakObjectPtr<UWorld> OwningWorld;`
- L162 _private member_ `TWeakObjectPtr<APlayerController> DefaultPlayerController;`
- L163 _private member_ `TMap<UUserWidget*, TSharedPtr<SWidget>> CachedSlateByWidgetObject;`

#### Free symbols / members of external scopes

- L64 _function_ `` (scope `FUserWidgetPool::GetOrCreateInstance`)

### `Source/Runtime/UMG/Public/Blueprint/WidgetBlueprintGeneratedClass.h` (Public)


#### enum `EBindingKind`  
`enum class EBindingKind : uint8`  
_L22-26_
- reflection: `UENUM()`
- L24 _public enumerator_ `Function`
- L25 _public enumerator_ `Property`

#### struct `FDelegateRuntimeBinding`  
`struct FDelegateRuntimeBinding`  
_L29-52_
- reflection: `USTRUCT()`
- L35 _public member_ `FString ObjectName;` — `UPROPERTY()` — The widget that will be bound to the live data.
- L39 _public member_ `FName PropertyName;` — `UPROPERTY()` — The property on the widget that will have a binding placed on it.
- L43 _public member_ `FName FunctionName;` — `UPROPERTY()` — The function or property we're binding to on the source object.
- L47 _public member_ `FDynamicPropertyPath SourcePath;` — `UPROPERTY()`
- L51 _public member_ `EBindingKind Kind = EBindingKind::Property;` — `UPROPERTY()` — The kind of binding we're performing, are we binding to a property or a function.

#### class `FWidgetBlueprintGeneratedClassDelegates`  
`class FWidgetBlueprintGeneratedClassDelegates`  
_L56-70_
- L60 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTagsWithContext, const UWidgetBlueprintGeneratedClass*, FAssetRegistryTagsContext);` — delegate for generating widget asset registry tags.
- L61 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTags, const UWidgetBlueprintGeneratedClass*, TArray<UObject::FAssetRegistryTag>&);`
- L62 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FCollectSaveOverrides, const UWidgetBlueprintGeneratedClass*, FObjectCollectSaveOverridesContext);`
- L65 _public member_ `static FGetAssetTagsWithContext GetAssetTagsWithContext;` — called by UWidgetBlueprintGeneratedClass::GetAssetRegistryTags()
- L67 _public member_ `static FCollectSaveOverrides CollectSaveOverrides;` — called by UWidgetBlueprintGeneratedClass::CollectSaveOverrides()
- L69 _public member_ `static FGetAssetTags GetAssetTags;` — `UE_DEPRECATED(5.4, "Subscribe to GetAssetTagsWithContext instead.")`

#### class `UWidgetBlueprintGeneratedClass`  
`class UWidgetBlueprintGeneratedClass : public UBlueprintGeneratedClass`  
_L80-234_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- desc: The widget blueprint generated class allows us to create blueprint-able widgets for UMG at runtime. All WBPGC's are of UUserWidget classes, and they perform special post initialization using this class to give themselves many of the same capabilities as AActor blueprints, like dynamic delegate binding for widgets.
- L86 _public prototype_ `UWidgetBlueprintGeneratedClass();`
- L92 _private member_ `TObjectPtr<UWidgetTree> WidgetTree;` — `UPROPERTY(DuplicateTransient)` — A tree of the widget templates to be created
- L96 _private member_ `TArray<TObjectPtr<UWidgetBlueprintGeneratedClassExtension>> Extensions;` — `UPROPERTY()` — The extension that are considered static to the class
- L100 _private member_ `uint32 bClassRequiresNativeTick :1;` — `UPROPERTY()` — The classes native parent requires a native tick
- L105 _public member_ `uint32 bCanCallPreConstruct : 1;` — `UPROPERTY(Transient)`
- L115 _public member_ `uint32 bCanCallInitializedWithoutPlayerContext : 1;` — `UPROPERTY()` — Determines whether this widget blueprint can be initialized without a valid player context (PlayerController, etc.). Required to be true for use with UMG Widget Preview.
- L118 _public member_ `TArray< FDelegateRuntimeBinding > Bindings;` — `UPROPERTY()`
- L121 _public member_ `TArray< TObjectPtr<UWidgetAnimation> > Animations;` — `UPROPERTY()`
- L128 _public member_ `TArray<FName> NamedSlots;` — `UPROPERTY()` — All named slots, even the ones that have content already filled into them by a parent class and are not available for extension.
- L133 _public member_ `TMap<FName, FGuid> NamedSlotsWithID;` — `UPROPERTY()` — All named slots mapped the assigned GUID of their UNamedSlot widget.
- L136 _public member_ `TSet<FName> NamedSlotsWithContentInSameTree;` — `UPROPERTY(Transient)`
- L139 _public member_ `TSet<FName> NameClashingInHierarchy;` — `UPROPERTY(Transient)`
- L147 _public member_ `TArray<FName> AvailableNamedSlots;` — `UPROPERTY(AssetRegistrySearchable)` — Available Named Slots for content in a subclass.  These are slots that are accumulated from all super classes on compile.  They will exclude any named slots that are filled by a parent class.
- L156 _public member_ `TArray<FName> InstanceNamedSlots;` — `UPROPERTY()` — These are the set of named slots that can be used on an instance of the widget.  This set is slightly different from available named slots, because ones designated UNamedSlot::bExposeOnInstanceOnly == true will also be in this list, even though they wont be in AvailableNamedSlots, if are inherited, as inherited named slots do not have the capability to remove existing content in a named slot.
- L159 _public function_ `UWidgetTree* GetWidgetTreeArchetype() const`
- L160 _public prototype_ `void SetWidgetTreeArchetype(UWidgetTree* InWidgetTree);`
- L162 _public prototype_ `void GetNamedSlotArchetypeContent(TFunctionRef<void(FName , UWidget* )> Predicate) const;`
- L165 _public prototype_ `UWidgetBlueprintGeneratedClass* FindWidgetTreeOwningClass() const;` — Walks up the hierarchy looking for a valid widget tree.
- L168 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L169 _public prototype_ `virtual void PostLoad() override;`
- L170 _public prototype_ `virtual bool NeedsLoadForServer() const override;`
- L172 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L173 _public prototype_ `virtual void CollectSaveOverrides(FObjectCollectSaveOverridesContext SaveContext) override;`
- L177 _public prototype_ `virtual void PurgeClass(bool bRecompilingOnLoad) override;`
- L184 _public prototype_ `void InitializeWidget(UUserWidget* UserWidget) const;` — This is the function that makes UMG work.  Once a user widget is constructed, it will post load call into its generated class and ask to be initialized.  The class will perform all the delegate binding and wiring necessary to have the user's widget perform as desired.
- L186 _public prototype_ `static void InitializeWidgetStatic(UUserWidget* UserWidget , const UClass* InClass , UWidgetTree* InWidgetTree , const UClass* InWidgetTreeWidgetClass , const TArrayView<UWidgetAnimation*> InAnimations , const TArrayView<const FDelegateRuntimeBinding> InBindings);`
- L193 _public function_ `bool ClassRequiresNativeTick() const`
- L196 _public prototype_ `void SetClassRequiresNativeTick(bool InClassRequiresNativeTick);`
- L201 _public function_ `template<typename ExtensionType> ExtensionType* GetExtension(bool bIncludeSuper = true)` — Find the first extension of the requested type.
- L207 _public prototype_ `UWidgetBlueprintGeneratedClassExtension* GetExtension(TSubclassOf<UWidgetBlueprintGeneratedClassExtension> InExtensionType, bool bIncludeSuper = true);` — Find the first extension of the requested type.
- L210 _public prototype_ `TArray<UWidgetBlueprintGeneratedClassExtension*> GetExtensions(TSubclassOf<UWidgetBlueprintGeneratedClassExtension> InExtensionType, bool bIncludeSuper = true);` — Find the extensions of the requested type.
- L213 _public function_ `template<typename Predicate> void ForEachExtension(Predicate Pred, bool bIncludeSuper = true) const`
- L230 _private prototype_ `static void InitializeBindingsStatic(UUserWidget* UserWidget, const TArrayView<const FDelegateRuntimeBinding> InBindings, const TMap<FName, FObjectPropertyBase*>& InPropertyMap);`
- L231 _private prototype_ `static void BindAnimationsStatic(UUserWidget* Instance, const TArrayView<UWidgetAnimation*> InAnimations, const TMap<FName, FObjectPropertyBase*>& InPropertyMap);`
- L233 _private prototype_ `void GetExtensions(TArray<UWidgetBlueprintGeneratedClassExtension*>& OutExtensions, TSubclassOf<UWidgetBlueprintGeneratedClassExtension> InExtensionType, bool bIncludeSuper);`

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTagsWithContext, const UWidgetBlueprintGeneratedClass*, FAssetRegistryTagsContext);` — delegate for generating widget asset registry tags.
- L61 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTags, const UWidgetBlueprintGeneratedClass*, TArray<UObject::FAssetRegistryTag>&);`
- L62 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FCollectSaveOverrides, const UWidgetBlueprintGeneratedClass*, FObjectCollectSaveOverridesContext);`

### `Source/Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h` (Public)


#### class `UWidgetBlueprintLibrary`  
`class UWidgetBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L26-365_
- reflection: `UCLASS(meta=(ScriptName="WidgetLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L34 _public prototype_ `static class UUserWidget* Create(UObject* WorldContextObject, TSubclassOf<class UUserWidget> WidgetType, APlayerController* OwningPlayer);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=( WorldContext="WorldContextObject", DisplayName="Create Widget", BlueprintInternalUseOnly="true" ), Category="Widget")` — Creates a widget
- L41 _public prototype_ `static UDragDropOperation* CreateDragDropOperation(TSubclassOf<UDragDropOperation> OperationClass);` — `UFUNCTION(BlueprintCallable, Category="Widget|Drag and Drop", meta=( BlueprintInternalUseOnly="true" ))` — Creates a new drag and drop operation that can be returned from a drag begin to inform the UI what i being dragged and dropped and what it looks like.
- L49 _public prototype_ `static void SetInputMode_UIOnlyEx(APlayerController* PlayerController, UWidget* InWidgetToFocus = nullptr, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, const bool bFlushInput = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Input", meta=(DisplayName="Set Input Mode UI Only"))` — Setup an input mode that allows only the UI to respond to user input. Note: This means that any bound Input Events in the widget will not be called!
- L56 _public prototype_ `static void SetInputMode_GameAndUIEx(APlayerController* PlayerController, UWidget* InWidgetToFocus = nullptr, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, bool bHideCursorDuringCapture = true, const bool bFlushInput = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Input", meta = (DisplayName = "Set Input Mode Game And UI"))` — Setup an input mode that allows only the UI to respond to user input, and if the UI doesn't handle it player input / player controller gets a chance. Note: This means that any bound Input events in the widget will be called.
- L64 _public prototype_ `static void SetInputMode_GameOnly(APlayerController* PlayerController, const bool bFlushInput = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Input")` — Setup an input mode that allows only player input / player controller to respond to user input. Note: Any bound Input Events in this widget will be called.
- L68 _public prototype_ `static void SetFocusToGameViewport();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Focus")`
- L72 _public prototype_ `static void DrawBox(UPARAM(ref) FPaintContext& Context, FVector2D Position, FVector2D Size, USlateBrushAsset* Brush, FLinearColor Tint = FLinearColor::White);` — `UFUNCTION(BlueprintCallable, Category="Painting")` — Draws a box
- L85 _public prototype_ `static void DrawSpline(UPARAM(ref) FPaintContext& Context, FVector2D Start, FVector2D StartDir, FVector2D End, FVector2D EndDir, FLinearColor Tint = FLinearColor::White, float Thickness = 1.0f);` — `UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "6"), Category = "Painting")` — Draws a hermite spline. @param Start			Starting position of the spline in local space. @param StartDir		The direction of the spline from the start point. @param End			Ending position of the spline in local space. @param EndDir		The direction of the spline to the end point. @param Tint			Color to render the spline. @param Thickness		How many pixels thick this spline should be.
- L97 _public prototype_ `static void DrawLine(UPARAM(ref) FPaintContext& Context, FVector2D PositionA, FVector2D PositionB, FLinearColor Tint = FLinearColor::White, bool bAntiAlias = true, float Thickness = 1.0f);` — `UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "4"), Category = "Painting")` — Draws a line. @param PositionA		Starting position of the line in local space. @param PositionB		Ending position of the line in local space. @param Tint			Color to render the line. @param bAntialias	Whether the line should be antialiased. @param Thickness		How many pixels thick this line should be.
- L108 _public prototype_ `static void DrawLines(UPARAM(ref) FPaintContext& Context, const TArray<FVector2D>& Points, FLinearColor Tint = FLinearColor::White, bool bAntiAlias = true, float Thickness = 1.0f);` — `UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "3"), Category = "Painting")` — Draws several line segments. @param Points		Line pairs, each line needs to be 2 separate points in the array. @param Tint			Color to render the line. @param bAntialias	Whether the line should be antialiased. @param Thickness		How many pixels thick this line should be.
- L118 _public prototype_ `static void DrawText(UPARAM(ref) FPaintContext& Context, const FString& InString, FVector2D Position, FLinearColor Tint = FLinearColor::White);` — `UFUNCTION(BlueprintCallable, Category="Painting", meta=( DeprecatedFunction, DeprecationMessage = "Use Draw Text instead", DisplayName="Draw String"))` — Draws text. @param InString		The string to draw. @param Position		The starting position where the text is drawn in local space. @param Tint			Color to render the line.
- L128 _public prototype_ `static void DrawTextFormatted(UPARAM(ref) FPaintContext& Context, const FText& Text, FVector2D Position, UFont* Font, float FontSize = 16.0f, FName FontTypeFace = FName("Regular"), FLinearColor Tint = FLinearColor::` — `UFUNCTION(BlueprintCallable, Category="Painting", meta=(DisplayName="Draw Text"))` — Draws text. @param Text			The string to draw. @param Position		The starting position where the text is drawn in local space. @param Tint			Color to render the line.
- L135 _public prototype_ `static FEventReply Handled();` — `UFUNCTION(BlueprintPure, Category="Widget|Event Reply")` — The event reply to use when you choose to handle an event.  This will prevent the event from continuing to bubble up / down the widget hierarchy.
- L139 _public prototype_ `static FEventReply Unhandled();` — `UFUNCTION(BlueprintPure, Category="Widget|Event Reply")` — The event reply to use when you choose not to handle an event.
- L143 _public prototype_ `static FEventReply CaptureMouse(UPARAM(ref) FEventReply& Reply, UWidget* CapturingWidget);` — `UFUNCTION(BlueprintPure, meta=( DefaultToSelf="CapturingWidget" ), Category="Widget|Event Reply")`
- L147 _public prototype_ `static FEventReply ReleaseMouseCapture(UPARAM(ref) FEventReply& Reply);` — `UFUNCTION(BlueprintPure, Category="Widget|Event Reply")`
- L150 _public prototype_ `static FEventReply LockMouse( UPARAM( ref ) FEventReply& Reply, UWidget* CapturingWidget );` — `UFUNCTION(BlueprintPure, Category = "Widget|Event Reply", meta = ( HidePin = "CapturingWidget", DefaultToSelf = "CapturingWidget" ))`
- L153 _public prototype_ `static FEventReply UnlockMouse( UPARAM( ref ) FEventReply& Reply );` — `UFUNCTION(BlueprintPure, Category = "Widget|Event Reply")`
- L157 _public prototype_ `static FEventReply SetUserFocus(UPARAM(ref) FEventReply& Reply, UWidget* FocusWidget, bool bInAllUsers = false);` — `UFUNCTION(BlueprintPure, meta= (HidePin="CapturingWidget", DefaultToSelf="CapturingWidget"), Category="Widget|Event Reply")`
- L160 _public prototype_ `static FEventReply CaptureJoystick(UPARAM(ref) FEventReply& Reply, UWidget* CapturingWidget, bool bInAllJoysticks = false);` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "Use SetUserFocus() instead"), Category = "Widget|Event Reply")`
- L164 _public prototype_ `static FEventReply ClearUserFocus(UPARAM(ref) FEventReply& Reply, bool bInAllUsers = false);` — `UFUNCTION(BlueprintPure, meta = (HidePin = "CapturingWidget", DefaultToSelf = "CapturingWidget"), Category = "Widget|Event Reply")`
- L167 _public prototype_ `static FEventReply ReleaseJoystickCapture(UPARAM(ref) FEventReply& Reply, bool bInAllJoysticks = false);` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "Use ClearUserFocus() instead"), Category = "Widget|Event Reply")`
- L171 _public prototype_ `static FEventReply SetMousePosition(UPARAM(ref) FEventReply& Reply, FVector2D NewMousePosition);` — `UFUNCTION(BlueprintPure, Category="Widget|Event Reply")`
- L181 _public prototype_ `static FEventReply DetectDrag(UPARAM(ref) FEventReply& Reply, UWidget* WidgetDetectingDrag, FKey DragKey);` — `UFUNCTION(BlueprintPure, meta=( HidePin="WidgetDetectingDrag", DefaultToSelf="WidgetDetectingDrag" ), Category="Widget|Drag and Drop|Event Reply")` — Ask Slate to detect if a user starts dragging in this widget later.  Slate internally tracks the movement and if it surpasses the drag threshold, Slate will send an OnDragDetected event to the widget. @param WidgetDetectingDrag  Detect dragging in this widget @param DragKey		       This button should be pressed to detect the drag
- L191 _public prototype_ `static FEventReply DetectDragIfPressed(const FPointerEvent& PointerEvent, UWidget* WidgetDetectingDrag, FKey DragKey);` — `UFUNCTION(BlueprintCallable, meta=( HidePin="WidgetDetectingDrag", DefaultToSelf="WidgetDetectingDrag" ), Category="Widget|Drag and Drop|Event Reply")` — Given the pointer event, emit the DetectDrag reply if the provided key was pressed. If the DragKey is a touch key, that will also automatically work. @param PointerEvent	The pointer device event coming in. @param WidgetDetectingDrag  Detect dragging in this widget. @param DragKey		       This button should be pressed to detect the drag, won't emit the DetectDrag FEventReply unless this is pressed.
- L197 _public prototype_ `static FEventReply EndDragDrop(UPARAM(ref) FEventReply& Reply);` — `UFUNCTION(BlueprintPure, Category="Widget|Drag and Drop|Event Reply")` — An event should return FReply::Handled().EndDragDrop() to request that the current drag/drop operation be terminated.
- L203 _public prototype_ `static bool IsDragDropping();` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Widget|Drag and Drop")` — Returns true if a drag/drop event is occurring that a widget can handle.
- L209 _public prototype_ `static UDragDropOperation* GetDragDroppingContent();` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Widget|Drag and Drop")` — Returns the drag and drop operation that is currently occurring if any, otherwise nothing.
- L215 _public prototype_ `static void CancelDragDrop();` — `UFUNCTION(BlueprintCallable, Category="Widget|Drag and Drop")` — Cancels any current drag drop operation.
- L223 _public prototype_ `static FSlateBrush MakeBrushFromAsset(USlateBrushAsset* BrushAsset);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Creates a Slate Brush from a Slate Brush Asset @return A new slate brush using the asset's brush.
- L234 _public prototype_ `static FSlateBrush MakeBrushFromTexture(UTexture2D* Texture, int32 Width = 0, int32 Height = 0);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Creates a Slate Brush from a Texture2D @param Width  When less than or equal to zero, the Width of the brush will default to the Width of the Texture @param Height  When less than or equal to zero, the Height of the brush will default to the Height of the Texture @return A new slate brush using the texture.
- L243 _public prototype_ `static FSlateBrush MakeBrushFromMaterial(UMaterialInterface* Material, int32 Width = 32, int32 Height = 32);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Creates a Slate Brush from a Material.  Materials don't have an implicit size, so providing a widget and height is required to hint slate with how large the image wants to be by default. @return A new slate brush using the material.
- L249 _public prototype_ `static UObject* GetBrushResource(const FSlateBrush& Brush);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Gets the resource object on a brush.  This could be a UTexture2D or a UMaterialInterface.
- L255 _public prototype_ `static UTexture2D* GetBrushResourceAsTexture2D(const FSlateBrush& Brush);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Gets the brush resource as a texture 2D.
- L261 _public prototype_ `static UMaterialInterface* GetBrushResourceAsMaterial(const FSlateBrush& Brush);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Gets the brush resource as a material.
- L267 _public prototype_ `static void SetBrushResourceToTexture(UPARAM(ref) FSlateBrush& Brush, UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category="Widget|Brush")` — Sets the resource on a brush to be a UTexture2D.
- L273 _public prototype_ `static void SetBrushResourceToMaterial(UPARAM(ref) FSlateBrush& Brush, UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category="Widget|Brush")` — Sets the resource on a brush to be a Material.
- L281 _public prototype_ `static FSlateBrush NoResourceBrush();` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Creates a Slate Brush that wont draw anything, the "Null Brush". @return A new slate brush that wont draw anything.
- L290 _public prototype_ `static UMaterialInstanceDynamic* GetDynamicMaterial(UPARAM(ref) FSlateBrush& Brush);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")` — Gets the material that allows changes to parameters at runtime.  The brush must already have a material assigned to it, if it does it will automatically be converted to a MID. @return A material that supports dynamic input from the game.
- L294 _public prototype_ `static void DismissAllMenus();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Widget|Menu")` — Closes any popup menu
- L303 _public prototype_ `static void GetAllWidgetsOfClass(const UObject* WorldContextObject, TArray<UUserWidget*>& FoundWidgets, TSubclassOf<UUserWidget> WidgetClass, bool TopLevelOnly = true);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Widget", meta=( WorldContext="WorldContextObject", DeterminesOutputType = "WidgetClass", DynamicOutputParam = "FoundWidgets" ))` — Find all widgets of a certain class. @param FoundWidgets The widgets that were found matching the filter. @param WidgetClass The widget class to filter by. @param TopLevelOnly Only the widgets that are direct children of the viewport will be returned.
- L313 _public prototype_ `static void GetAllWidgetsWithInterface(const UObject* WorldContextObject, TArray<UUserWidget*>& FoundWidgets, TSubclassOf<UInterface> Interface, bool TopLevelOnly);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Widget", meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "WidgetClass", DynamicOutputParam = "FoundWidgets"))` — Find all widgets in the world with the specified interface. This is a slow operation, use with caution e.g. do not use every frame. @param Interface The interface to find. Must be specified or result array will be empty. @param FoundWidgets Output array of widgets that implement the specified interface. @param TopLevelOnly Only the widgets that are direct children of the viewport will be returned.
- L316 _public prototype_ `static FInputEvent GetInputEventFromKeyEvent(const FKeyEvent& Event);` — `UFUNCTION(BlueprintPure, Category="Widget", meta = (CompactNodeTitle = "->", BlueprintAutocast))`
- L319 _public prototype_ `static FKeyEvent GetKeyEventFromAnalogInputEvent(const FAnalogInputEvent& Event);` — `UFUNCTION(BlueprintPure, Category="Widget", meta = (CompactNodeTitle = "->", BlueprintAutocast))`
- L322 _public prototype_ `static FInputEvent GetInputEventFromCharacterEvent(const FCharacterEvent& Event);` — `UFUNCTION(BlueprintPure, Category="Widget", meta = ( CompactNodeTitle = "->", BlueprintAutocast ))`
- L325 _public prototype_ `static FInputEvent GetInputEventFromPointerEvent(const FPointerEvent& Event);` — `UFUNCTION(BlueprintPure, Category="Widget", meta = ( CompactNodeTitle = "->", BlueprintAutocast ))`
- L328 _public prototype_ `static FInputEvent GetInputEventFromNavigationEvent(const FNavigationEvent& Event);` — `UFUNCTION(BlueprintPure, Category="Widget", meta = ( CompactNodeTitle = "->", BlueprintAutocast ))`
- L334 _public prototype_ `static void GetSafeZonePadding(const UObject* WorldContextObject, FVector4& SafePadding, FVector2D& SafePaddingScale, FVector4& SpillOverPadding);` — `UFUNCTION(BlueprintCallable, Category="Widget|Safe Zone", meta=( WorldContext="WorldContextObject" ))` — Gets the amount of padding that needs to be added when accounting for the safe zone on TVs.
- L344 _public prototype_ `static void SetColorVisionDeficiencyType(EColorVisionDeficiency Type, float Severity, bool CorrectDeficiency, bool ShowCorrectionWithDeficiency);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget|Accessibility", meta = (AdvancedDisplay = "3"))` — Apply color deficiency correction settings to the game window @param Type The type of color deficiency correction to apply. @param Severity Intensity of the color deficiency correction effect, from 0 to 1. @param CorrectDeficiency Shifts the color spectrum to the visible range based on the current deficiency type. @param ShowCorrectionWithDeficiency If you're correcting the color deficiency, you can use this to visualize what the correction looks like with the deficiency.
- L350 _public prototype_ `static bool SetHardwareCursor(const UObject* WorldContextObject, EMouseCursor::Type CursorShape, FName CursorName, FVector2D HotSpot);` — `UFUNCTION(BlueprintCallable, Category="Widget|Hardware Cursor", meta=( WorldContext="WorldContextObject" ))` — Loads or sets a hardware cursor from the content directory in the game.
- L353 _public prototype_ `static void SetWindowTitleBarState(UWidget* TitleBarContent, EWindowTitleBarMode Mode, bool bTitleBarDragEnabled, bool bWindowButtonsVisible, bool bTitleBarVisible);` — `UFUNCTION(BlueprintCallable, Category = "Widget|Window Title Bar")`
- L356 _public prototype_ `static void RestorePreviousWindowTitleBarState();` — `UFUNCTION(BlueprintCallable, Category = "Widget|Window Title Bar")`
- L358 _public prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnGameWindowCloseButtonClickedDelegate);`
- L361 _public prototype_ `static void SetWindowTitleBarOnCloseClickedDelegate(FOnGameWindowCloseButtonClickedDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "Widget|Window Title Bar")`
- L364 _public prototype_ `static void SetWindowTitleBarCloseButtonActive(bool bActive);` — `UFUNCTION(BlueprintCallable, Category = "Widget|Window Title Bar")`

#### Free symbols / members of external scopes

- L358 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnGameWindowCloseButtonClickedDelegate);`

### `Source/Runtime/UMG/Public/Blueprint/WidgetChild.h` (Public)


#### struct `FWidgetChild`  
`struct FWidgetChild`  
_L18-45_
- reflection: `USTRUCT()`
- desc: Represent a Widget present in the Tree Widget of the UserWidget
- L22 _public prototype_ `FWidgetChild();`
- L23 _public prototype_ `FWidgetChild(const class UUserWidget* Outer, FName InChildName);`
- L25 _public function_ `FName GetFName() const`
- L30 _public function_ `UWidget* GetWidget() const`
- L36 _public prototype_ `UWidget* Resolve(const class UWidgetTree* WidgetTree);` — Resolves the Widget ptr using it's name.
- L41 _private member_ `FName WidgetName;` — `UPROPERTY(EditAnywhere, Category = "Interaction")` — This either the widget to focus, OR the name of the function to call.
- L44 _private member_ `TWeakObjectPtr<UWidget> WidgetPtr;` — `UPROPERTY(Transient)`

### `Source/Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h` (Public)


#### struct `FWidgetDesignTimeInfo`  
`struct FWidgetDesignTimeInfo`  
_L17-28_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- desc: Design-time preview information from the UMG Designer. Contains the current designer preview dimensions and derived orientation. Only populated at design time — all values are zeroed/false at runtime.
- L23 _public member_ `FVector2D PreviewSize = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Design Time")` — The current preview dimensions in the UMG Designer (width x height).
- L27 _public member_ `bool bIsPortrait = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Design Time")` — True when the designer preview is in portrait orientation (height > width).

#### class `UWidgetLayoutLibrary`  
`class UWidgetLayoutLibrary : public UBlueprintFunctionLibrary`  
_L48-248_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L64 _public prototype_ `static bool ProjectWorldLocationToWidgetPosition(const APlayerController* PlayerController, FVector WorldLocation, FVector2D& ScreenPosition, bool bPlayerViewportRelative);` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Viewport")` — Gets the projected world to screen position for a player, then converts it into a widget position, which takes into account any quality scaling. @param PlayerController The player controller to project the position in the world to their screen. @param WorldLocation The world location to project from. @param ScreenPosition The position in the viewport with quality scale removed and DPI scale remove. @param bPlayerViewportRelative Should this be relative to the player viewport subregion (useful when using player attached widgets in split screen or when aspect-ratio constrained) @return true if the position projects onto the screen.
- L72 _public prototype_ `static bool ProjectWorldLocationToWidgetPositionWithDistance(const APlayerController* PlayerController, FVector WorldLocation, FVector& ScreenPosition, bool bPlayerViewportRelative);` — Convert a World Space 3D position into a 2D Widget Screen Space position, with distance from the camera the Z component.  This takes into account any quality scaling as well. @return true if the world coordinate was successfully projected to the screen.
- L78 _public prototype_ `static float GetViewportScale(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Viewport", meta=( WorldContext="WorldContextObject" ))` — Gets the current DPI Scale being applied to the viewport and all the Widgets.
- L83 _public prototype_ `static float GetViewportScale(const UGameViewportClient* ViewportClient);` — Gets the current DPI Scale being applied to the viewport and all the Widgets.
- L89 _public prototype_ `static FVector2D GetViewportSize(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Viewport", meta=( WorldContext="WorldContextObject", Keywords = "screen size"))` — Gets the size of the game viewport.
- L97 _public prototype_ `static FGeometry GetViewportWidgetGeometry(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category="Viewport", meta=( WorldContext="WorldContextObject" ))` — Gets the geometry of the widget holding all widgets added to the "Viewport".  You can use this geometry to convert between absolute and local space of widgets held on this widget.
- L105 _public prototype_ `static FGeometry GetPlayerScreenWidgetGeometry(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category="Viewport")` — Gets the geometry of the widget holding all widgets added to the "Player Screen". You can use this geometry to convert between absolute and local space of widgets held on this widget.
- L111 _public prototype_ `static FVector2D GetMousePositionOnPlatform();` — `UFUNCTION(BlueprintCallable, Category="Viewport")` — Gets the platform's mouse cursor position.  This is the 'absolute' desktop location of the mouse.
- L117 _public prototype_ `static FVector2D GetMousePositionOnViewport(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category="Viewport", meta=( WorldContext="WorldContextObject" ))` — Gets the platform's mouse cursor position in the local space of the viewport widget.
- L127 _public prototype_ `static bool GetMousePositionScaledByDPI(const APlayerController* Player, float& LocationX, float& LocationY);` — `UE_DEPRECATED(4.17, "Use GetMousePositionOnViewport() instead. Optionally and for more options, you can use GetViewportWidgetGeometry and GetPlayerScreenWidgetGeometry are newly introduced to give you the geometry of the viewport and the player screen for widgets to help convert between spaces.")` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Viewport")` — Gets the mouse position of the player controller, scaled by the DPI.  If you're trying to go from raw mouse screenspace coordinates to fullscreen widget space, you'll need to transform the mouse into DPI Scaled space.  This function performs that scaling. MousePositionScaledByDPI = MousePosition * (1 / ViewportScale).
- L128 _public prototype_ `static bool GetMousePositionScaledByDPI(const APlayerController* Player, double& LocationX, double& LocationY);` — LWC_TODO: Temp stand in for native calls with FVector2D components.
- L135 _public prototype_ `static class UBorderSlot* SlotAsBorderSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Border Slot, allowing you to manipulate layout information. @param Widget The child widget of a border panel.
- L142 _public prototype_ `static UCanvasPanelSlot* SlotAsCanvasSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category="Slot")` — Gets the slot object on the child widget as a Canvas Slot, allowing you to manipulate layout information. @param Widget The child widget of a canvas panel.
- L149 _public prototype_ `static UGridSlot* SlotAsGridSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category="Slot")` — Gets the slot object on the child widget as a Grid Slot, allowing you to manipulate layout information. @param Widget The child widget of a grid panel.
- L156 _public prototype_ `static UHorizontalBoxSlot* SlotAsHorizontalBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category="Slot")` — Gets the slot object on the child widget as a Horizontal Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Horizontal Box.
- L163 _public prototype_ `static UOverlaySlot* SlotAsOverlaySlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category="Slot")` — Gets the slot object on the child widget as a Overlay Slot, allowing you to manipulate layout information. @param Widget The child widget of a overlay panel.
- L170 _public prototype_ `static UUniformGridSlot* SlotAsUniformGridSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category="Slot")` — Gets the slot object on the child widget as a Uniform Grid Slot, allowing you to manipulate layout information. @param Widget The child widget of a uniform grid panel.
- L177 _public prototype_ `static UVerticalBoxSlot* SlotAsVerticalBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Vertical Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Vertical Box.
- L185 _public prototype_ `static UScrollBoxSlot* SlotAsScrollBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Scroll Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Scroll Box.
- L192 _public prototype_ `static USafeZoneSlot* SlotAsSafeBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Safe Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Safe Box.
- L199 _public prototype_ `static UScaleBoxSlot* SlotAsScaleBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Scale Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Scale Box.
- L206 _public prototype_ `static USizeBoxSlot* SlotAsSizeBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Size Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Size Box.
- L213 _public prototype_ `static UStackBoxSlot* SlotAsStackBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Stack Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Stack Box.
- L220 _public prototype_ `static UWrapBoxSlot* SlotAsWrapBoxSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Wrap Box Slot, allowing you to manipulate its information. @param Widget The child widget of a Wrap Box.
- L227 _public prototype_ `static UWidgetSwitcherSlot* SlotAsWidgetSwitcherSlot(UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Slot")` — Gets the slot object on the child widget as a Widget Switcher Slot, allowing you to manipulate its information. @param Widget The child widget of a Widget Switcher Slot.
- L233 _public prototype_ `static void RemoveAllWidgets(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Viewport", meta=( WorldContext="WorldContextObject" ))` — Removes all widgets from the viewport.
- L247 _public prototype_ `static FWidgetDesignTimeInfo GetDesignTimeInfo(const UWidget* Widget);` — `UFUNCTION(BlueprintPure, Category = "Design Time", meta = (DefaultToSelf = "Widget"))` — Returns design-time preview information from the UMG Designer. Use this in PreConstruct to adapt widget layout to the designer's current preview dimensions (e.g., switching between portrait and landscape layouts). Logs an error and returns zeroed values if called outside of a design-time preview (e.g., at runtime or from a non-preview context). Use viewport/display system queries instead for runtime orientation. @param Widget	The calling widget (auto-filled via DefaultToSelf).

### `Source/Runtime/UMG/Public/Blueprint/WidgetNavigation.h` (Public)


#### struct `FWidgetNavigationData`  
`struct FWidgetNavigationData`  
_L23-46_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `EUINavigationRule Rule = EUINavigationRule::Escape;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")`
- L33 _public member_ `FName WidgetToFocus;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — This either the widget to focus, OR the name of the function to call.
- L36 _public member_ `TWeakObjectPtr<UWidget> Widget;` — `UPROPERTY()`
- L39 _public member_ `FCustomWidgetNavigationDelegate CustomDelegate;` — `UPROPERTY()`
- L41 _public prototype_ `void Resolve(class UUserWidget* Outer, class UWidgetTree* WidgetTree);`
- L44 _public prototype_ `void TryToRenameBinding(FName OldName, FName NewName);`

#### class `UWidgetNavigation`  
`class UWidgetNavigation : public UObject`  
_L52-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L59 _public member_ `FWidgetNavigationData Up;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses up arrow, joystick, d-pad.
- L63 _public member_ `FWidgetNavigationData Down;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses down arrow, joystick, d-pad.
- L67 _public member_ `FWidgetNavigationData Left;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses left arrow, joystick, d-pad.
- L71 _public member_ `FWidgetNavigationData Right;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses right arrow, joystick, d-pad.
- L75 _public member_ `FWidgetNavigationData Next;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses Tab.
- L79 _public member_ `FWidgetNavigationData Previous;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")` — Happens when the user presses Shift+Tab.
- L82 _public member_ `EWidgetNavigationRoutingPolicy RoutingPolicy = EWidgetNavigationRoutingPolicy::AcceptFocus;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation")`
- L85 _public member_ `TInstancedStruct<FNavigationMethod> NavigationMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Navigation", meta=(ExcludeBaseStruct))`
- L92 _public prototype_ `FWidgetNavigationData& GetNavigationData(EUINavigation Nav);`
- L95 _public prototype_ `EUINavigationRule GetNavigationRule(EUINavigation Nav);`
- L98 _public prototype_ `virtual void TryToRenameBinding(FName OldName, FName NewName);` — Try to rename any explicit or custom bindings from an old to a new name. This method can be overridden to customize resolving rules.
- L103 _public prototype_ `virtual void ResolveRules(class UUserWidget* Outer, class UWidgetTree* WidgetTree);` — Resolve widget names. This method can be overridden to customize resolving rules.
- L106 _public prototype_ `void UpdateMetaData(TSharedRef<FNavigationMetaData> MetaData);` — Updates a slate metadata object to match this configured navigation ruleset.
- L109 _public prototype_ `bool IsDefaultNavigation() const;` — @return true if the configured navigation object is the same as an un-customized navigation rule set.
- L113 _private prototype_ `void UpdateMetaDataEntry(TSharedRef<FNavigationMetaData> MetaData, const FWidgetNavigationData & NavData, EUINavigation Nav);`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FCustomWidgetNavigationDelegate, EUINavigation, Navigation);`
- L17 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FCustomWidgetNavigationDelegate, EUINavigation, Navigation);`

### `Source/Runtime/UMG/Public/Blueprint/WidgetTree.h` (Public)


#### class `UWidgetTree`  
`class UWidgetTree : public UObject, public INamedSlotInterface`  
_L19-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,INamedSlotInterface`
- desc: The widget tree manages the collection of widgets in a blueprint widget.
- L26 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L29 _public prototype_ `virtual bool IsCapturingAsRootObjectForTransaction() const override;`
- L34 _public prototype_ `UWidget* FindWidget(const FName& Name) const;` — Finds the widget in the tree by name.
- L37 _public prototype_ `UWidget* FindWidget(TSharedRef<SWidget> InWidget) const;` — Finds a widget in the tree using the native widget as the key.
- L41 _public function_ `template <typename WidgetT> inline WidgetT* FindWidget(const FName& Name) const` — Finds the widget in the tree by name and casts the return to the desired type.
- L47 _public prototype_ `bool RemoveWidget(UWidget* Widget);` — Removes the widget from the hierarchy and all sub widgets.
- L50 _public prototype_ `static class UPanelWidget* FindWidgetParent(UWidget* Widget, int32& OutChildIndex);` — Gets the parent widget of a given widget, and potentially the child index.
- L56 _public prototype_ `static UWidget* FindWidgetChild(UPanelWidget* ParentWidget, FName ChildWidgetName, int32& OutChildIndex);` — Searches recursively through the children of the given ParentWidget to find a child widget of the given name. If successful, also gets the index the child ultimately occupies within the starting ParentWidget (INDEX_NONE otherwise)
- L62 _public prototype_ `static int32 FindChildIndex(const UPanelWidget* ParentWidget, const UWidget* ChildWidget);` — Determines the child index of the given ParentWidget that the given ChildWidget ultimately occupies, accounting for nesting @return The child slot index within ParentWidget that ChildWidget ultimately occupies (INDEX_NONE if ChildWidget is not within ParentWidget at any level)
- L65 _public prototype_ `void GetAllWidgets(TArray<UWidget*>& Widgets) const;` — Gathers all the widgets in the tree recursively
- L68 _public prototype_ `static void GetChildWidgets(UWidget* Parent, TArray<UWidget*>& Widgets);` — Gathers descendant child widgets of a parent widget.
- L71 _public prototype_ `static bool TryMoveWidgetToNewTree(UWidget* Widget, UWidgetTree* DestinationTree);` — Attempts to move a constructed Widget to another tree. Returns true on a successful move.
- L78 _public prototype_ `void ForEachWidget(TFunctionRef<void(UWidget*)> Predicate) const;` — Iterates through all widgets including widgets contained in named slots, other than investigating named slots, this code does not dive into foreign WidgetTrees, as would exist inside another user widget.
- L84 _public prototype_ `void ForEachWidgetAndDescendants(TFunctionRef<void(UWidget*)> Predicate) const;` — Iterates through all widgets including widgets contained in named slots, other than investigating named slots.  This includes foreign widget trees inside of other UserWidgets.
- L91 _public prototype_ `static void ForWidgetAndChildren(UWidget* Widget, TFunctionRef<void(UWidget*)> Predicate);` — Iterates through all child widgets including widgets contained in named slots, other than investigating named slots, this code does not dive into foreign WidgetTrees, as would exist inside another user widget.
- L96 _public prototype_ `void ForEachWidgetUntil(TFunctionRef<bool(UWidget*)> Predicate) const;` — Iterates widgets according to ForEachWidget until Predicate returns false.
- L101 _public prototype_ `static bool ForEachWidgetAndChildrenUntil(UWidget* Widget, TFunctionRef<bool(UWidget*)> Predicate);` — Iterates widgets according to ForWidgetAndChildren until Predicate returns false.
- L106 _public function_ `template <typename WidgetT> [[nodiscard]] inline WidgetT* ConstructWidget(TSubclassOf<WidgetT> WidgetClass = WidgetT::StaticClass(), FName WidgetName = NAME_None)` — Constructs the widget, and adds it to the tree.
- L128 _public prototype_ `virtual void GetSlotNames(TArray<FName>& SlotNames) const override;` — Gets the names for slots that we can store widgets into.
- L131 _public prototype_ `virtual UWidget* GetContentForSlot(FName SlotName) const override;` — Gets the widget for a given slot by name, will return nullptr if no widget is in the slot.
- L134 _public prototype_ `virtual void SetContentForSlot(FName SlotName, UWidget* Content) override;` — Sets the widget for a given slot by name.
- L139 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;` — UObject interface
- L140 _public prototype_ `virtual void PostLoad() override;`
- L144 _public prototype_ `void FixupOrphanedWidgetNames();`
- L150 _public member_ `TObjectPtr<UWidget> RootWidget;` — `UPROPERTY(Instanced)` — The root widget of the tree
- L158 _public member_ `TMap<FName, TObjectPtr<UWidget>> NamedSlotBindings;` — `UPROPERTY()` — Stores the widgets being assigned to named slots, these widgets will be slotted into the named slots of the user widget that owns this widget tree after the user widget is constructed.  This is how we store the template content in order to have named slot inheritance, and merging widget trees.
- L164 _protected member_ `TArray< TObjectPtr<UWidget> > AllWidgets;` — `UPROPERTY(Instanced)`

### `Source/Runtime/UMG/Public/Components/BackgroundBlur.h` (Public)


#### class `UBackgroundBlur`  
`class UBackgroundBlur : public UContentWidget`  
_L16-143_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: A background blur is a container widget that can contain one child widget, providing an opportunity to surround it with adjustable padding and apply a post-process Gaussian blur to all content beneath the widget. * Single Child * Blur Effect
- L24 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetPadding, Category = Content)` — The padding area between the slot and the content it contains.
- L29 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetHorizontalAlignment, Category = Content)` — The alignment of the content horizontally.
- L34 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetVerticalAlignment, Category = Content)` — The alignment of the content vertically.
- L39 _public member_ `bool bApplyAlphaToBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter=GetApplyAlphaToBlur, Setter=SetApplyAlphaToBlur, BlueprintSetter=SetApplyAlphaToBlur, Category = Content)` — True to modulate the strength of the blur based on the widget alpha.
- L46 _public member_ `float BlurStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetBlurStrength, Category = Appearance, meta = (ClampMin = 0, ClampMax = 100))` — How blurry the background is.  Larger numbers mean more blurry but will result in larger runtime cost on the GPU.
- L51 _public member_ `bool bOverrideAutoRadiusCalculation;` — `UPROPERTY(Getter = GetOverrideAutoRadiusCalculation, Setter = SetOverrideAutoRadiusCalculation)` — When OverrideAutoRadiusCalculation is set to true, BlurRadius is used for the radius of the blur. When false, it's automatically calculated using the BlurStength value.
- L59 _public member_ `int32 BlurRadius;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetBlurRadius, Category = Appearance, meta = (ClampMin = 0, ClampMax = 255, EditCondition = "bOverrideAutoRadiusCalculation"))` — This is the number of pixels which will be weighted in each direction from any given pixel when computing the blur A larger value is more costly but allows for stronger blurs.
- L64 _public member_ `FVector4 CornerRadius;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetCornerRadius, Category = Appearance)` — Radius in Slate Units applied to the blur widget at each corner. X = Top Left, Y = Top Right, Z = Bottom Right, W = Bottom Left
- L73 _public member_ `FSlateBrush LowQualityFallbackBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter=SetLowQualityFallbackBrush, Category = Appearance)` — An image to draw instead of applying a blur when low quality override mode is enabled. You can enable low quality mode for background blurs by setting the cvar Slate.ForceBackgroundBlurLowQualityOverride to 1. This is usually done in the project's scalability settings
- L76 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L79 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L80 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L84 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L86 _public prototype_ `FMargin GetPadding() const;`
- L89 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L91 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L94 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L96 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L99 _public prototype_ `void SetApplyAlphaToBlur(bool bInApplyAlphaToBlur);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L101 _public prototype_ `bool GetApplyAlphaToBlur() const;`
- L103 _public prototype_ `void SetOverrideAutoRadiusCalculation(bool InOverrideAutoRadiusCalculation);`
- L105 _public prototype_ `bool GetOverrideAutoRadiusCalculation() const;`
- L108 _public prototype_ `void SetBlurRadius(int32 InBlurRadius);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L110 _public prototype_ `int32 GetBlurRadius() const;`
- L113 _public prototype_ `virtual void SetBlurStrength(float InStrength);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L115 _public prototype_ `float GetBlurStrength() const;`
- L118 _public prototype_ `virtual void SetCornerRadius(FVector4 InCornerRadius);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L120 _public prototype_ `FVector4 GetCornerRadius() const;`
- L123 _public prototype_ `void SetLowQualityFallbackBrush(const FSlateBrush& InBrush);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L125 _public prototype_ `FSlateBrush GetLowQualityFallbackBrush() const;`
- L128 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L129 _public prototype_ `virtual void PostLoad() override;`
- L133 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UWidget interface
- L134 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L135 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L138 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;` — UPanelWidget interface
- L139 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L142 _protected member_ `TSharedPtr<class SBackgroundBlur> MyBackgroundBlur;`

### `Source/Runtime/UMG/Public/Components/BackgroundBlurSlot.h` (Public)


#### class `UBackgroundBlurSlot`  
`class UBackgroundBlurSlot : public UPanelSlot`  
_L19-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UBackgroundBlurSlot, contains the widget displayed in a BackgroundBlur's single slot
- L25 _public prototype_ `FMargin GetPadding() const;`
- L28 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Background Blur Slot")`
- L30 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L33 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Background Blur Slot")`
- L35 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L38 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Background Blur Slot")`
- L44 _protected member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|Background Blur Slot")` — The padding area between the slot and the content it contains.
- L49 _protected member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Background Blur Slot")` — The alignment of the object horizontally.
- L54 _protected member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Background Blur Slot")` — The alignment of the object vertically.
- L59 _public prototype_ `virtual void SynchronizeProperties() override;`
- L63 _public prototype_ `void BuildSlot(TSharedRef<SBackgroundBlur> InBackgroundBlur);` — Builds the underlying slot for the slate BackgroundBlur.
- L65 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L72 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L80 _private member_ `TSharedPtr<SBackgroundBlur> BackgroundBlur;` — A pointer to the BackgroundBlur to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/Border.h` (Public)


#### class `UBorder`  
`class UBorder : public UContentWidget`  
_L29-224_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: A border is a container widget that can contain one child widget, providing an opportunity to surround it with a background image and adjustable padding. * Single Child * Image
- L37 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Content")` — The alignment of the content horizontally.
- L42 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetVerticalAlignment", Category="Content")` — The alignment of the content vertically.
- L47 _public member_ `uint8 bShowEffectWhenDisabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="GetShowEffectWhenDisabled", Setter="SetShowEffectWhenDisabled", BlueprintSetter="SetShowEffectWhenDisabled", Category="Appearance", AdvancedDisplay)` — Whether or not to show the disabled effect when this border is disabled
- L52 _public member_ `FLinearColor ContentColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetContentColorAndOpacity", Category="Content", meta=( sRGB="true" ))` — Color and opacity multiplier of content in the border
- L56 _public member_ `FGetLinearColor ContentColorAndOpacityDelegate;` — `UPROPERTY()` — A bindable delegate for the ContentColorAndOpacity.
- L61 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPadding", Category="Content")` — The padding area between the slot and the content it contains.
- L65 _public member_ `FSlateBrush Background;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=( DisplayName="Brush" ))` — Brush to drag as the background
- L69 _public member_ `FGetSlateBrush BackgroundDelegate;` — `UPROPERTY()` — A bindable delegate for the Brush.
- L74 _public member_ `FLinearColor BrushColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetBrushColor", Category="Appearance", meta = (sRGB="true"))` — Color and opacity of the actual border image
- L78 _public member_ `FGetLinearColor BrushColorDelegate;` — `UPROPERTY()` — A bindable delegate for the BrushColor.
- L88 _public member_ `FVector2D DesiredSizeScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetDesiredSizeScale", Category="Appearance")` — Scales the computed desired size of this border and its contents. Useful for making things that slide open without having to hard-code their size. Note: if the parent widget is set up to ignore this widget's desired size, then changing this value will have no effect.
- L92 _public member_ `bool bFlipForRightToLeftFlowDirection;` — `UPROPERTY(EditAnywhere, Category="Localization")` — Flips the background image if the localization's flow direction is RightToLeft
- L97 _public member_ `FOnPointerEvent OnMouseButtonDownEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))`
- L100 _public member_ `FOnPointerEvent OnMouseButtonUpEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))`
- L103 _public member_ `FOnPointerEvent OnMouseMoveEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))`
- L106 _public member_ `FOnPointerEvent OnMouseDoubleClickEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))`
- L110 _public prototype_ `FLinearColor GetContentColorAndOpacity() const;`
- L114 _public prototype_ `void SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L116 _public prototype_ `FMargin GetPadding() const;`
- L119 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L121 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L124 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L126 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L129 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L132 _public prototype_ `FLinearColor GetBrushColor() const;`
- L136 _public prototype_ `void SetBrushColor(FLinearColor InBrushColor);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L140 _public prototype_ `void SetBrush(const FSlateBrush& InBrush);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L144 _public prototype_ `void SetBrushFromAsset(USlateBrushAsset* Asset);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L148 _public prototype_ `void SetBrushFromTexture(UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L152 _public prototype_ `void SetBrushFromMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L155 _public prototype_ `bool GetShowEffectWhenDisabled() const;`
- L159 _public prototype_ `void SetShowEffectWhenDisabled(bool bInShowEffectWhenDisabled);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L163 _public prototype_ `UMaterialInstanceDynamic* GetDynamicMaterial();` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L167 _public prototype_ `FVector2D GetDesiredSizeScale() const;` — Gets the DesiredSizeScale of this border.
- L175 _public prototype_ `void SetDesiredSizeScale(FVector2D InScale);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the DesiredSizeScale of this border. @param InScale    The X and Y multipliers for the desired size
- L180 _public prototype_ `virtual void SynchronizeProperties() override;`
- L184 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L188 _public prototype_ `virtual void PostLoad() override;`
- L193 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L196 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L202 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L203 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L204 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L208 _protected member_ `TSharedPtr<SBorder> MyBorder;`
- L212 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L215 _protected prototype_ `FReply HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L216 _protected prototype_ `FReply HandleMouseButtonUp(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L217 _protected prototype_ `FReply HandleMouseMove(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L218 _protected prototype_ `FReply HandleMouseDoubleClick(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L221 _protected prototype_ `const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;` — Translates the bound brush data and assigns it to the cached brush used by this widget.

### `Source/Runtime/UMG/Public/Components/BorderSlot.h` (Public)


#### class `UBorderSlot`  
`class UBorderSlot : public UPanelSlot`  
_L20-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UBorderSlot, contains the widget displayed in a border's single slot
- L26 _public prototype_ `FMargin GetPadding() const;`
- L29 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Border Slot")`
- L31 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L34 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Border Slot")`
- L36 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L39 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Border Slot")`
- L45 _protected member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|Border Slot")` — The padding area between the slot and the content it contains.
- L50 _protected member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Border Slot")` — The alignment of the object horizontally.
- L55 _protected member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Border Slot")` — The alignment of the object vertically.
- L60 _public prototype_ `virtual void SynchronizeProperties() override;`
- L64 _public prototype_ `void BuildSlot(TSharedRef<SBorder> InBorder);` — Builds the underlying slot for the slate border.
- L66 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L73 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L81 _private member_ `TWeakPtr<SBorder> Border;` — A pointer to the border to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/Button.h` (Public)


#### class `UButton`  
`class UButton : public UContentWidget`  
_L32-226_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: The button is a click-able primitive widget to enable basic interaction, you can place any other widget inside a button to make a more complex and interesting click-able element in your UI. * Single Child * Clickable
- L40 _public member_ `FButtonStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetStyle", Setter = "SetStyle", BlueprintSetter = "SetStyle", Category = "Appearance", meta = (DisplayName = "Style"))` — The button style used at runtime
- L45 _public member_ `FLinearColor ColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetColorAndOpacity" , Category="Appearance", meta=( sRGB="true" ))` — The color multiplier for the button content
- L50 _public member_ `FLinearColor BackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetBackgroundColor", Category="Appearance", meta=( sRGB="true" ))` — The color multiplier for the button background
- L55 _public member_ `TEnumAsByte<EButtonClickMethod::Type> ClickMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetClickMethod", Category="Interaction", AdvancedDisplay)` — The type of mouse action required by the user to trigger the buttons 'Click'
- L60 _public member_ `TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetTouchMethod", Category="Interaction", AdvancedDisplay)` — The type of touch action required by the user to trigger the buttons 'Click'
- L65 _public member_ `TEnumAsByte<EButtonPressMethod::Type> PressMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetPressMethod", Category="Interaction", AdvancedDisplay)` — The type of keyboard/gamepad button press action required by the user to trigger the buttons 'Click'
- L70 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Interaction")` — Sometimes a button should only be mouse-clickable and never keyboard focusable.
- L76 _public member_ `FOnButtonClickedEvent OnClicked;` — `UPROPERTY(BlueprintAssignable, Category="Button|Event")` — Called when the button is clicked
- L80 _public member_ `FOnButtonPressedEvent OnPressed;` — `UPROPERTY(BlueprintAssignable, Category="Button|Event")` — Called when the button is pressed
- L84 _public member_ `FOnButtonReleasedEvent OnReleased;` — `UPROPERTY(BlueprintAssignable, Category="Button|Event")` — Called when the button is released
- L87 _public member_ `FOnButtonHoverEvent OnHovered;` — `UPROPERTY(BlueprintAssignable, Category = "Button|Event")`
- L90 _public member_ `FOnButtonHoverEvent OnUnhovered;` — `UPROPERTY(BlueprintAssignable, Category = "Button|Event")`
- L93 _public member_ `FOnDragDetected OnButtonDragDetected;` — Delegate triggered when a user starts to drag a button
- L96 _public member_ `FOnDragEnter OnButtonDragEnter;` — Delegate triggered when a user's drag enters the bounds of this button
- L99 _public member_ `FOnDragLeave OnButtonDragLeave;` — Delegate triggered when a user's drag leaves the bounds of this button
- L102 _public member_ `FOnDragOver OnButtonDragOver;` — Delegate triggered when a user's drag leaves the bounds of this button
- L105 _public member_ `FOnDrop OnButtonDrop;` — Delegate triggered when a user's drag is dropped in the bounds of this button
- L108 _public member_ `FSimpleDelegate OnReceivedFocus;` — Called when the button receives focus
- L111 _public member_ `FSimpleDelegate OnLostFocus;` — Called when the button loses focus
- L117 _public prototype_ `void SetStyle(const FButtonStyle& InStyle);` — `UFUNCTION(BlueprintCallable, Category="Button|Appearance")` — Sets the color multiplier for the button background
- L119 _public prototype_ `const FButtonStyle& GetStyle() const;`
- L123 _public prototype_ `void SetColorAndOpacity(FLinearColor InColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Button|Appearance")` — Sets the color multiplier for the button content
- L125 _public prototype_ `FLinearColor GetColorAndOpacity() const;`
- L129 _public prototype_ `void SetBackgroundColor(FLinearColor InBackgroundColor);` — `UFUNCTION(BlueprintCallable, Category="Button|Appearance")` — Sets the color multiplier for the button background
- L131 _public prototype_ `FLinearColor GetBackgroundColor() const;`
- L139 _public prototype_ `bool IsPressed() const;` — `UFUNCTION(BlueprintCallable, Category="Button")` — Returns true if the user is actively pressing the button.  Do not use this for detecting 'Clicks', use the OnClicked event instead. @return true if the user is actively pressing the button otherwise false.
- L142 _public prototype_ `void SetClickMethod(EButtonClickMethod::Type InClickMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")`
- L144 _public prototype_ `EButtonClickMethod::Type GetClickMethod() const;`
- L147 _public prototype_ `void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")`
- L149 _public prototype_ `EButtonTouchMethod::Type GetTouchMethod() const;`
- L152 _public prototype_ `void SetPressMethod(EButtonPressMethod::Type InPressMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")`
- L154 _public prototype_ `EButtonPressMethod::Type GetPressMethod() const;`
- L156 _public prototype_ `bool GetIsFocusable() const;`
- L159 _public prototype_ `void SetAllowDragDrop(bool bInAllowDragDrop);` — `UFUNCTION(BlueprintCallable, Category="Button")`
- L164 _public prototype_ `virtual void SynchronizeProperties() override;`
- L168 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L172 _public prototype_ `virtual void PostLoad() override;`
- L176 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L182 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L183 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L184 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L189 _protected prototype_ `FReply SlateHandleClicked();` — Handle the actual click event from slate and forward it on
- L190 _protected prototype_ `void SlateHandlePressed();`
- L191 _protected prototype_ `void SlateHandleReleased();`
- L192 _protected prototype_ `void SlateHandleHovered();`
- L193 _protected prototype_ `void SlateHandleUnhovered();`
- L194 _protected prototype_ `void SlateHandleOnReceivedFocus();`
- L195 _protected prototype_ `void SlateHandleOnLostFocus();`
- L198 _protected prototype_ `FReply SlateHandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Drag and Drop
- L199 _protected prototype_ `void SlateHandleDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L200 _protected prototype_ `void SlateHandleDragLeave(const FDragDropEvent& DragDropEvent);`
- L201 _protected prototype_ `FReply SlateHandleDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L202 _protected prototype_ `FReply SlateHandleDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L206 _protected prototype_ `void InitIsFocusable(bool InIsFocusable);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L209 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L211 _protected function_ `virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override`
- L216 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L221 _protected member_ `TSharedPtr<SButton> MyButton;` — Cached pointer to the underlying slate button owned by this UWidget
- L225 _protected member_ `bool bAllowDragDrop;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — True if this button can be dragged

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressedEvent);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressedEvent);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleasedEvent);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleasedEvent);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHoverEvent);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHoverEvent);`

### `Source/Runtime/UMG/Public/Components/ButtonSlot.h` (Public)


#### class `UButtonSlot`  
`class UButtonSlot : public UPanelSlot`  
_L17-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UButtonSlot, contains the widget displayed in a button's single slot
- L26 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPadding", Category="Layout|Button Slot")` — The padding area between the slot and the content it contains.
- L31 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Button Slot")` — The alignment of the object horizontally.
- L36 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Button Slot")` — The alignment of the object vertically.
- L40 _public prototype_ `FMargin GetPadding() const;`
- L43 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")`
- L45 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L48 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")`
- L50 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L53 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")`
- L56 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L60 _public prototype_ `void BuildSlot(TSharedRef<SButton> InButton);` — Builds the underlying slot for the slate button.
- L62 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L67 _private member_ `TWeakPtr<SButton> Button;` — A pointer to the button to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/CanvasPanel.h` (Public)


#### class `UCanvasPanel`  
`class UCanvasPanel : public UPanelWidget`  
_L25-75_
- reflection: `UCLASS(meta = (ShortTooltip = "A designer-friendly panel useful for laying out top-level widgets. Use sparingly."), MinimalAPI)`
- inherits: `UPanelWidget`
- desc: The canvas panel is a designer friendly panel that allows widgets to be laid out at arbitrary locations, anchored and z-ordered with other children of the canvas.  The canvas is a great widget for manual layout, but bad when you want to procedurally just generate widgets and place them in a container (unless you want absolute layout). * Many Children * Absolute Layout * Anchors
- L33 _public prototype_ `UCanvasPanelSlot* AddChildToCanvas(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Canvas Panel")`
- L36 _public prototype_ `TSharedPtr<class SConstraintCanvas> GetCanvasWidget() const;` — Gets the underlying native canvas widget if it has been constructed
- L39 _public prototype_ `bool GetGeometryForSlot(int32 SlotIndex, FGeometry& ArrangedGeometry) const;` — Computes the geometry for a particular slot based on the current geometry of the canvas.
- L42 _public prototype_ `bool GetGeometryForSlot(UCanvasPanelSlot* Slot, FGeometry& ArrangedGeometry) const;` — Computes the geometry for a particular slot based on the current geometry of the canvas.
- L44 _public prototype_ `void ReleaseSlateResources(bool bReleaseChildren) override;`
- L48 _public prototype_ `virtual const FText GetPaletteCategory() override;` — UWidget interface
- L52 _public function_ `virtual bool LockToPanelOnDrag() const override` — UWidget interface
- L62 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L63 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L64 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L69 _protected member_ `TSharedPtr<class SConstraintCanvas> MyCanvas;`
- L73 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/CanvasPanelSlot.h` (Public)


#### struct `FAnchorData`  
`struct FAnchorData`  
_L17-63_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FMargin Offsets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnchorData)` — Offset.
- L30 _public member_ `FAnchors Anchors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnchorData)` — Anchors.
- L38 _public member_ `FVector2D Alignment = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnchorData)` — Alignment is the pivot point of the widget.  Starting in the upper left at (0,0), ending in the lower right at (1,1).  Moving the alignment point allows you to move the origin of the widget.
- L46 _public function_ `bool operator==(const FAnchorData& Other) const` — Compares this set of FAnchorData with another for equality. @param Other The other FAnchorData. @return true if the two FAnchors are equal, false otherwise.
- L59 _public function_ `bool operator!=(const FAnchorData& Other) const` — Compares this set of FAnchorData with another for inequality. @param Other The other FAnchorData. @return true if the two FAnchors are not equal, false otherwise.

#### class `UCanvasPanelSlot`  
`class UCanvasPanelSlot : public UPanelSlot`  
_L66-203_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- L75 _public member_ `FAnchorData LayoutData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="GetLayout", Setter="SetLayout", BlueprintGetter ="GetLayout", BlueprintSetter="SetLayout", Category = "Layout|Canvas Slot")` — The anchoring information for the slot
- L80 _public member_ `bool bAutoSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="GetAutoSize", Setter="SetAutoSize", BlueprintGetter="GetAutoSize", BlueprintSetter="SetAutoSize", Category = "Layout|Canvas Slot", AdvancedDisplay, meta = (DisplayName = "Size To Content"))` — When AutoSize is true we use the widget's desired size
- L85 _public member_ `int32 ZOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter="GetZOrder", BlueprintSetter="SetZOrder", Category="Layout|Canvas Slot")` — The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top).
- L89 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L90 _public prototype_ `virtual bool DragDropPreviewByDesigner(const FVector2D& LocalCursorPosition, const TOptional<int32>& XGridSnapSize, const TOptional<int32>& YGridSnapSize) override;`
- L91 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`
- L96 _public prototype_ `void SetLayout(const FAnchorData& InLayoutData);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the layout data of the slot
- L100 _public prototype_ `FAnchorData GetLayout() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the layout data of the slot
- L104 _public prototype_ `void SetPosition(FVector2D InPosition);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the position of the slot
- L108 _public prototype_ `FVector2D GetPosition() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the position of the slot
- L112 _public prototype_ `void SetSize(FVector2D InSize);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the size of the slot
- L116 _public prototype_ `FVector2D GetSize() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the size of the slot
- L120 _public prototype_ `void SetOffsets(FMargin InOffset);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the offset data of the slot, which could be position and size, or margins depending on the anchor points
- L124 _public prototype_ `FMargin GetOffsets() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the offset data of the slot, which could be position and size, or margins depending on the anchor points
- L128 _public prototype_ `void SetAnchors(FAnchors InAnchors);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the anchors on the slot
- L132 _public prototype_ `FAnchors GetAnchors() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the anchors on the slot
- L136 _public prototype_ `void SetAlignment(FVector2D InAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the alignment on the slot
- L140 _public prototype_ `FVector2D GetAlignment() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the alignment on the slot
- L144 _public prototype_ `void SetAutoSize(bool InbAutoSize);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets if the slot to be auto-sized
- L148 _public prototype_ `bool GetAutoSize() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets if the slot to be auto-sized
- L152 _public prototype_ `void SetZOrder(int32 InZOrder);` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Sets the z-order on the slot
- L156 _public prototype_ `int32 GetZOrder() const;` — `UFUNCTION(BlueprintCallable, Category="Layout|Canvas Slot")` — Gets the z-order on the slot
- L162 _public prototype_ `void SetMinimum(FVector2D InMinimumAnchors);` — `UFUNCTION()` — Sets the anchors on the slot
- L166 _public prototype_ `void SetMaximum(FVector2D InMaximumAnchors);` — `UFUNCTION()` — Sets the anchors on the slot
- L170 _public prototype_ `void BuildSlot(TSharedRef<SConstraintCanvas> Canvas);`
- L173 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L176 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L181 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L182 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L186 _public prototype_ `void SaveBaseLayout();` — Stores the current layout information about the slot and parent canvas.
- L188 _public prototype_ `void SetDesiredPosition(FVector2D InPosition);`
- L191 _public prototype_ `void RebaseLayout(bool PreserveSize = true);` — Compares the saved base layout against the current state.  Updates the necessary properties to maintain a stable position.
- L195 _private member_ `SConstraintCanvas::FSlot* Slot;`
- L198 _private member_ `FGeometry PreEditGeometry;`
- L199 _private member_ `FAnchorData PreEditLayoutData;`
- L201 _private member_ `TOptional<FVector2D> DesiredPosition;`

### `Source/Runtime/UMG/Public/Components/CheckBox.h` (Public)


#### class `UCheckBox`  
`class UCheckBox : public UContentWidget`  
_L31-181_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: The checkbox widget allows you to display a toggled state of 'unchecked', 'checked' and 'indeterminable.  You can use the checkbox for a classic checkbox, or as a toggle button, or as radio buttons. * Single Child * Toggle
- L39 _public member_ `ECheckBoxState CheckedState;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter="GetCheckedState", BlueprintSetter="SetCheckedState", FieldNotify, Category="Appearance")` — Whether the check box is currently in a checked state
- L44 _public member_ `FGetCheckBoxState CheckedStateDelegate;` — `UPROPERTY()` — A bindable delegate for the IsChecked.
- L49 _public member_ `FCheckBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta = (DisplayName="Style"))` — The checkbox bar style
- L53 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearance")` — How the content of the toggle button should align within the given space
- L58 _public member_ `TEnumAsByte<EButtonClickMethod::Type> ClickMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetClickMethod", Category="Interaction", AdvancedDisplay)` — The type of mouse action required by the user to trigger the buttons 'Click'
- L63 _public member_ `TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetTouchMethod", Category="Interaction", AdvancedDisplay)` — The type of touch action required by the user to trigger the buttons 'Click'
- L68 _public member_ `TEnumAsByte<EButtonPressMethod::Type> PressMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPressMethod", Category="Interaction", AdvancedDisplay)` — The type of keyboard/gamepad button press action required by the user to trigger the buttons 'Click'
- L73 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Interaction")` — Sometimes a button should only be mouse-clickable and never keyboard focusable.
- L79 _public member_ `FOnCheckBoxComponentStateChanged OnCheckStateChanged;` — `UPROPERTY(BlueprintAssignable, Category="CheckBox|Event")` — Called when the checked state has changed
- L85 _public prototype_ `bool IsPressed() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if this button is currently pressed
- L89 _public prototype_ `bool IsChecked() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if the checkbox is currently checked
- L93 _public prototype_ `ECheckBoxState GetCheckedState() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns the full current checked state.
- L97 _public prototype_ `void SetIsChecked(bool InIsChecked);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the checked state.
- L101 _public prototype_ `void SetCheckedState(ECheckBoxState InCheckedState);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the checked state.
- L104 _public prototype_ `const FCheckBoxStyle& GetWidgetStyle() const;` — Returns the local style.
- L107 _public prototype_ `void SetWidgetStyle(const FCheckBoxStyle& InStyle);` — Sets the style.
- L110 _public prototype_ `EButtonClickMethod::Type GetClickMethod() const;` — Returns the click method.
- L114 _public prototype_ `void SetClickMethod(EButtonClickMethod::Type InClickMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")` — Sets the click method.
- L117 _public prototype_ `EButtonTouchMethod::Type GetTouchMethod() const;` — Returns the touch method.
- L121 _public prototype_ `void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")` — Sets the touch method.
- L124 _public prototype_ `EButtonPressMethod::Type GetPressMethod() const;` — Returns the press method.
- L128 _public prototype_ `void SetPressMethod(EButtonPressMethod::Type InPressMethod);` — `UFUNCTION(BlueprintCallable, Category="Button")` — Sets the press method.
- L131 _public prototype_ `bool GetIsFocusable() const;` — Is the checkbox focusable.
- L136 _public prototype_ `virtual void SynchronizeProperties() override;`
- L140 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L144 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L150 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;` — UPanelWidget
- L151 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L155 _protected prototype_ `void InitIsFocusable(bool InIsFocusable);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L157 _protected prototype_ `void InitCheckedStateDelegate(FGetCheckBoxState InCheckedStateDelegate);`
- L160 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L162 _protected function_ `virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override`
- L169 _protected prototype_ `void SlateOnCheckStateChangedCallback(ECheckBoxState NewState);`
- L172 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L176 _protected member_ `TSharedPtr<SCheckBox> MyCheckbox;`

#### class `UWidgetCheckedStateRegistration`  
`class UWidgetCheckedStateRegistration : public UWidgetEnumStateRegistration`  
_L184-211_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UWidgetEnumStateRegistration`
- L191 _public member_ `static FWidgetStateBitfield Unchecked;` — Post-load initialized values corresponding to this enum state
- L192 _public member_ `static FWidgetStateBitfield Checked;`
- L193 _public member_ `static FWidgetStateBitfield Undetermined;`
- L195 _public member_ `static const inline FName StateName = FName("Che`
- L198 _public prototype_ `virtual FName GetStateName() const override;`
- L199 _public prototype_ `virtual uint8 GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L203 _public prototype_ `static const FWidgetStateBitfield& GetBitfieldFromValue(uint8 InValue);` — Convenience method to get widget state bitfield from enum value
- L209 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCheckBoxComponentStateChanged, bool, bIsChecked );`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCheckBoxComponentStateChanged, bool, bIsChecked );`

### `Source/Runtime/UMG/Public/Components/CircularThrobber.h` (Public)


#### class `UCircularThrobber`  
`class UCircularThrobber : public UWidget`  
_L22-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A throbber widget that orients images in a spinning circle. * No Children * Spinner Progress
- L31 _public member_ `int32 NumberOfPieces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetNumberOfPieces", Category = Appearance, meta = (ClampMin = "1", ClampMax = "25", UIMin = "1", UIMax = "25"))` — How many pieces there are
- L36 _public member_ `float Period;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPeriod", Category=Appearance, meta=( ClampMin="0", UIMin="0" ))` — The amount of time for a full circle (in seconds)
- L41 _public member_ `float Radius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetRadius", Category=Appearance, meta=(EditCondition="bEnableRadius"))` — The radius of the circle. If the throbber is a child of Canvas Panel, the 'Size to Content' option must be enabled in order to set Radius.
- L46 _public member_ `FSlateBrush Image;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Appearance)` — The throbber image.
- L52 _public prototype_ `void SetNumberOfPieces(int32 InNumberOfPieces);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets how many pieces there are.
- L53 _public prototype_ `int32 GetNumberOfPieces() const;`
- L57 _public prototype_ `void SetPeriod(float InPeriod);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the amount of time for a full circle (in seconds).
- L58 _public prototype_ `float GetPeriod() const;`
- L62 _public prototype_ `void SetRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the radius of the circle.
- L63 _public prototype_ `float GetRadius() const;`
- L66 _public prototype_ `void SetImage(const FSlateBrush& InRadius);` — Sets the throbber image.
- L67 _public prototype_ `const FSlateBrush& GetImage() const;`
- L71 _public prototype_ `virtual void SynchronizeProperties() override;`
- L72 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L75 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L79 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L84 _private member_ `bool bEnableRadius;` — `UPROPERTY(Transient, EditAnywhere, Category="Appearance", meta=(InlineEditConditionToggle))`
- L87 _private member_ `TSharedPtr<SCircularThrobber> MyCircularThrobber;` — The CircularThrobber widget managed by this object.

### `Source/Runtime/UMG/Public/Components/ComboBox.h` (Public)


#### class `UComboBox`  
`class UComboBox : public UWidget`  
_L16-52_
- reflection: `UCLASS(Experimental, meta=( DisplayName="ComboBox (Object)" ), MinimalAPI)`
- inherits: `UWidget`
- desc: The combobox allows you to display a list of options to the user in a dropdown menu for them to select one.
- L23 _public member_ `FScrollBarStyle ScrollBarStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")`
- L27 _public member_ `TArray<TObjectPtr<UObject>> Items;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Content)` — The list of items to be displayed on the combobox.
- L31 _public member_ `FGenerateWidgetForObject OnGenerateWidgetEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))` — Called when the widget is needed for the item.
- L33 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L36 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L40 _public member_ `bool bIsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interaction)`
- L43 _protected prototype_ `TSharedRef<SWidget> HandleGenerateWidget(UObject* Item) const;`
- L46 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L51 _protected member_ `TSharedPtr< SComboBox<UObject*> > MyComboBox;`

### `Source/Runtime/UMG/Public/Components/ComboBoxKey.h` (Public)


#### class `UComboBoxKey`  
`class UComboBoxKey : public UWidget`  
_L18-226_
- reflection: `UCLASS(meta = (DisplayName = "ComboBox (Key)"), MinimalAPI)`
- inherits: `UWidget`
- desc: The combobox allows you to display a list of options to the user in a dropdown menu for them to select one. Use OnGenerateConentWidgetEvent to return a custom built widget.
- L23 _public prototype_ `UComboBoxKey();`
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, FName, SelectedItem, ESelectInfo::Type, SelectionType);`
- L26 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpeningEvent);`
- L27 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetEvent, FName, Item);`
- L32 _private member_ `TArray<FName> Options;` — `UPROPERTY(EditAnywhere, Category = Content)` — .
- L36 _private member_ `FName SelectedOption;` — `UPROPERTY(EditAnywhere, FieldNotify, Category = Content)`
- L42 _public member_ `FComboBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style, meta = (DisplayName = "Style"))` — The combobox style.
- L47 _public member_ `FTableRowStyle ItemStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style)` — The item row style.
- L52 _public member_ `FScrollBarStyle ScrollBarStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Style")` — The scroll bar style.
- L57 _public member_ `FSlateColor ForegroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = Style, meta = (DesignerRebuild))` — The foreground color to pass through the hierarchy.
- L61 _public member_ `FMargin ContentPadding;` — `UE_DEPRECATED(5.2, "Direct access to ContentPadding is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style)`
- L66 _public member_ `float MaxListHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style, AdvancedDisplay)` — The max height of the combobox list that opens
- L74 _public member_ `bool bHasDownArrow;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsHasDownArrow", Setter = "SetHasDownArrow", Category = Style, AdvancedDisplay)` — When false, the down arrow is not generated and it is up to the API consumer to make their own visual hint that this is a drop down.
- L82 _public member_ `bool bEnableGamepadNavigationMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsEnableGamepadNavigationMode", Setter = "SetEnableGamepadNavigationMode", Category = Style, AdvancedDisplay)` — When false, directional keys will change the selection. When true, ComboBox must be activated and will only capture arrow input while activated.
- L87 _public member_ `bool bIsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsFocusable", Category = Style)` — When true, allows the combo box to receive keyboard focus
- L93 _public member_ `FGenerateWidgetEvent OnGenerateContentWidget;` — `UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))` — Called when the widget is needed for the content.
- L97 _public member_ `FGenerateWidgetEvent OnGenerateItemWidget;` — `UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))` — Called when the widget is needed for the item.
- L101 _public member_ `FOnSelectionChangedEvent OnSelectionChanged;` — `UPROPERTY(BlueprintAssignable, Category = Events)` — Called when a new item is selected in the combobox.
- L105 _public member_ `FOnOpeningEvent OnOpening;` — `UPROPERTY(BlueprintAssignable, Category = Events)` — Called when the combobox is opening
- L113 _public prototype_ `void AddOption(FName Option);` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Add an element to the option list.
- L117 _public prototype_ `bool RemoveOption(FName Option);` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Remove an element to the option list.
- L121 _public prototype_ `void ClearOptions();` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Remove all the elements of the option list.
- L125 _public prototype_ `void ClearSelection();` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Clear the current selection.
- L129 _public prototype_ `void SetSelectedOption(FName Option);` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Set the current selected option.
- L133 _public prototype_ `FName GetSelectedOption() const;` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")` — Get the current selected option
- L137 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category = "ComboBox", Meta = (ReturnDisplayName = "bOpen"))` — Is the combobox menu opened.
- L140 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L144 _public prototype_ `void SetContentPadding(FMargin InPadding);` — Set the padding for content.
- L147 _public prototype_ `FMargin GetContentPadding() const;` — Get the padding for content.
- L150 _public prototype_ `bool IsEnableGamepadNavigationMode() const;` — Is the combobox navigated by gamepad.
- L153 _public prototype_ `void SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode);` — Set whether the combobox is navigated by gamepad.
- L156 _public prototype_ `bool IsHasDownArrow() const;` — Is the combobox arrow showing.
- L159 _public prototype_ `void SetHasDownArrow(bool InHasDownArrow);` — Set whether the combobox arrow is showing.
- L162 _public prototype_ `float GetMaxListHeight() const;` — Get the maximum height of the combobox list.
- L165 _public prototype_ `void SetMaxListHeight(float InMaxHeight);` — Set the maximum height of the combobox list.
- L168 _public prototype_ `const FComboBoxStyle& GetWidgetStyle() const;` — Get the style of the combobox.
- L171 _public prototype_ `void SetWidgetStyle(const FComboBoxStyle& InWidgetStyle);` — Set the style of the combobox.
- L174 _public prototype_ `const FTableRowStyle& GetItemStyle() const;` — Get the style of the items.
- L177 _public prototype_ `void SetItemStyle(const FTableRowStyle& InItemStyle);` — Set the style of the items.
- L180 _public prototype_ `const FScrollBarStyle& GetScrollBarStyle() const;` — Get the style of the scrollbar.
- L183 _public prototype_ `bool IsFocusable() const;` — Is the combobox focusable.
- L186 _public prototype_ `FSlateColor GetForegroundColor() const;` — Get the foreground color of the button.
- L189 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L195 _protected prototype_ `void InitScrollBarStyle(const FScrollBarStyle& InScrollBarStyle);` — Initialize the scrollbar style in the constructor before the SWidget is constructed.
- L198 _protected prototype_ `void InitIsFocusable(bool InIsFocusable);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L201 _protected prototype_ `void InitForegroundColor(FSlateColor InForegroundColor);` — Initialize ForegroundColor in the constructor before the SWidget is constructed.
- L205 _private prototype_ `void GenerateContent();` — Called by slate when it needs to generate the widget in the content box
- L208 _private prototype_ `TSharedRef<SWidget> HandleGenerateItemWidget(FName Item);` — Called by slate when it needs to generate a new item for the combobox
- L211 _private prototype_ `void HandleSelectionChanged(FName Item, ESelectInfo::Type SelectionType);` — Called by slate when the underlying combobox selection changes
- L214 _private prototype_ `void HandleOpening();` — Called by slate when the underlying combobox is opening
- L217 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L222 _private member_ `TSharedPtr<SComboBox<FName>> MyComboBox;` — A shared pointer to the underlying slate combobox
- L225 _private member_ `TSharedPtr< SBox > ComboBoxContent;` — A shared pointer to a container that holds the combobox content that is selected

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, FName, SelectedItem, ESelectInfo::Type, SelectionType);`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpeningEvent);`
- L27 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetEvent, FName, Item);`

### `Source/Runtime/UMG/Public/Components/ComboBoxString.h` (Public)


#### class `UComboBoxString`  
`class UComboBoxString : public UWidget`  
_L21-263_
- reflection: `UCLASS(meta=( DisplayName="ComboBox (String)"), MinimalAPI)`
- inherits: `UWidget`
- desc: The combobox allows you to display a list of options to the user in a dropdown menu for them to select one.
- L25 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, FString, SelectedItem, ESelectInfo::Type, SelectionType);`
- L26 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpeningEvent);`
- L32 _private member_ `TArray<FString> DefaultOptions;` — `UPROPERTY(EditAnywhere, Category=Content)` — The default list of items to be displayed on the combobox.
- L36 _private member_ `FString SelectedOption;` — `UPROPERTY(EditAnywhere, FieldNotify, Category=Content)` — The item in the combobox to select by default
- L43 _public member_ `FComboBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Style, meta=( DisplayName="Style" ))` — The style.
- L48 _public member_ `FTableRowStyle ItemStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Style)` — The item row style.
- L53 _public member_ `FScrollBarStyle ScrollBarStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Style")` — The scroll bar style.
- L57 _public member_ `FMargin ContentPadding;` — `UE_DEPRECATED(5.2, "Direct access to ContentPadding is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Content)`
- L62 _public member_ `float MaxListHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Content, AdvancedDisplay)` — The max height of the combobox list that opens
- L70 _public member_ `bool HasDownArrow;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsHasDownArrow", Setter = "SetHasDownArrow", Category = Content, AdvancedDisplay)` — When false, the down arrow is not generated and it is up to the API consumer to make their own visual hint that this is a drop down.
- L78 _public member_ `bool EnableGamepadNavigationMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsEnableGamepadNavigationMode", Setter = "SetEnableGamepadNavigationMode", Category = Content, AdvancedDisplay)` — When false, directional keys will change the selection. When true, ComboBox must be activated and will only capture arrow input while activated.
- L86 _public member_ `FSlateFontInfo Font;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category=Style)` — The default font to use in the combobox, only applies if you're not implementing OnGenerateWidgetEvent to factory each new entry.
- L91 _public member_ `FSlateColor ForegroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category=Style, meta=(DesignerRebuild))` — The foreground color to pass through the hierarchy.
- L95 _public member_ `bool bIsFocusable;` — `UE_DEPRECATED(5.2, "Direct access to bIsFocusable is deprecated. Please use the getter. Note that this property is only set at construction and is not modifiable at runtime.")` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter= "IsFocusable", Category=Interaction)`
- L101 _public member_ `FGenerateWidgetForString OnGenerateWidgetEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))` — Called when the widget is needed for the item.
- L105 _public member_ `FOnSelectionChangedEvent OnSelectionChanged;` — `UPROPERTY(BlueprintAssignable, Category=Events)` — Called when a new item is selected in the combobox.
- L109 _public member_ `FOnOpeningEvent OnOpening;` — `UPROPERTY(BlueprintAssignable, Category=Events)` — Called when the combobox is opening
- L114 _public prototype_ `void AddOption(const FString& Option);` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L117 _public prototype_ `bool RemoveOption(const FString& Option);` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L120 _public prototype_ `int32 FindOptionIndex(const FString& Option) const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L123 _public prototype_ `FString GetOptionAtIndex(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L126 _public prototype_ `void ClearOptions();` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L129 _public prototype_ `void ClearSelection();` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L136 _public prototype_ `void RefreshOptions();` — `UFUNCTION(BlueprintCallable, Category="ComboBox")` — Refreshes the list of options.  If you added new ones, and want to update the list even if it's currently being displayed use this.
- L139 _public prototype_ `void SetSelectedOption(FString Option);` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L142 _public prototype_ `void SetSelectedIndex(const int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "ComboBox")`
- L145 _public prototype_ `FString GetSelectedOption() const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L148 _public prototype_ `int32 GetSelectedIndex() const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox")`
- L152 _public prototype_ `int32 GetOptionCount() const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox")` — Returns the number of options
- L155 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category="ComboBox", Meta = (ReturnDisplayName = "bOpen"))`
- L158 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L162 _public prototype_ `void SetContentPadding(FMargin InPadding);` — Set the padding for content.
- L165 _public prototype_ `FMargin GetContentPadding() const;` — Get the padding for content.
- L168 _public prototype_ `bool IsEnableGamepadNavigationMode() const;` — Is the combobox navigated by gamepad.
- L171 _public prototype_ `void SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode);` — Set whether the combobox is navigated by gamepad.
- L174 _public prototype_ `bool IsHasDownArrow() const;` — Is the combobox arrow showing.
- L177 _public prototype_ `void SetHasDownArrow(bool InHasDownArrow);` — Set whether the combobox arrow is showing.
- L180 _public prototype_ `float GetMaxListHeight() const;` — Get the maximum height of the combobox list.
- L183 _public prototype_ `void SetMaxListHeight(float InMaxHeight);` — Set the maximum height of the combobox list.
- L186 _public prototype_ `const FSlateFontInfo& GetFont() const;` — Get the default font for Combobox if no OnGenerateWidgetEvent is specified.
- L189 _public prototype_ `const FComboBoxStyle& GetWidgetStyle() const;` — Get the style of the combobox.
- L192 _public prototype_ `void SetWidgetStyle(const FComboBoxStyle& InWidgetStyle);` — Set the style of the combobox.
- L195 _public prototype_ `const FTableRowStyle& GetItemStyle() const;` — Get the style of the items.
- L198 _public prototype_ `void SetItemStyle(const FTableRowStyle& InItemStyle);` — Set the style of the items.
- L201 _public prototype_ `const FScrollBarStyle& GetScrollBarStyle() const;` — Get the style of the scrollbar.
- L204 _public prototype_ `bool IsFocusable() const;` — Is the combobox focusable.
- L207 _public prototype_ `FSlateColor GetForegroundColor() const;` — Get the foreground color of the button.
- L210 _public prototype_ `virtual void PostInitProperties() override;`
- L211 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L212 _public prototype_ `virtual void PostLoad() override;`
- L216 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L221 _protected prototype_ `void UpdateOrGenerateWidget(TSharedPtr<FString> Item);` — Refresh ComboBoxContent with the correct widget/data when the selected option changes
- L224 _protected prototype_ `virtual TSharedRef<SWidget> HandleGenerateWidget(TSharedPtr<FString> Item) const;` — Called by slate when it needs to generate a new item for the combobox
- L227 _protected prototype_ `virtual void HandleSelectionChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectionType);` — Called by slate when the underlying combobox selection changes
- L230 _protected prototype_ `virtual void HandleOpening();` — Called by slate when the underlying combobox is opening
- L233 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L237 _protected prototype_ `void InitScrollBarStyle(const FScrollBarStyle& InScrollBarStyle);` — Initialize the scrollbar style in the constructor before the SWidget is constructed.
- L240 _protected prototype_ `void InitFont(FSlateFontInfo InFont);` — Initialize the default font in the constructor before the SWidget is constructed.
- L243 _protected prototype_ `void InitIsFocusable(bool InIsFocusable);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L246 _protected prototype_ `void InitForegroundColor(FSlateColor InForegroundColor);` — Initialize ForegroundColor in the constructor before the SWidget is constructed.
- L250 _protected member_ `TArray< TSharedPtr<FString> > Options;` — The true objects bound to the Slate combobox.
- L253 _protected member_ `TSharedPtr< SComboBox< TSharedPtr<FString> > > MyComboBox;` — A shared pointer to the underlying slate combobox
- L256 _protected member_ `TSharedPtr< SBox > ComboBoxContent;` — A shared pointer to a container that holds the combobox content that is selected
- L259 _protected member_ `TWeakPtr<STextBlock> DefaultComboBoxContent;` — If OnGenerateWidgetEvent is not bound, this will store the default STextBlock generated
- L262 _protected member_ `TSharedPtr<FString> CurrentOptionPtr;` — A shared pointer to the current selected string

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, FString, SelectedItem, ESelectInfo::Type, SelectionType);`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpeningEvent);`

### `Source/Runtime/UMG/Public/Components/ContentWidget.h` (Public)


#### class `UContentWidget`  
`class UContentWidget : public UPanelWidget`  
_L12-34_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UPanelWidget`
- L19 _public prototype_ `UPanelSlot* GetContentSlot() const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")`
- L23 _public prototype_ `UPanelSlot* SetContent(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")`
- L27 _public prototype_ `UWidget* GetContent() const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")`
- L32 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget

### `Source/Runtime/UMG/Public/Components/DynamicEntryBox.h` (Public)


#### class `UDynamicEntryBox`  
`class UDynamicEntryBox : public UDynamicEntryBoxBase`  
_L17-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicEntryBoxBase`
- desc: A special box panel that auto-generates its entries at both design-time and runtime. Useful for cases where you can have a varying number of entries, but it isn't worth the effort or conceptual overhead to set up a list/tile view. Note that entries here are *not* virtualized as they are in the list views, so generally this should be avoided if you intend to scroll through lots of items. No children can be manually added in the designer - all are auto-generated based on the given entry class.
- L22 _public function_ `TSubclassOf<UUserWidget> GetEntryWidgetClass() const`
- L25 _public function_ `template <typename WidgetT = UUserWidget> WidgetT* CreateEntry(const TSubclassOf<WidgetT>& ExplicitEntryClass = {})`
- L36 _public function_ `template <typename WidgetT = UUserWidget> void Reset(TFunctionRef<void(WidgetT&)> ResetEntryFunc, bool bDeleteWidgets = false)`
- L51 _public prototype_ `void Reset(bool bDeleteWidgets = false);` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)` — Clear out the box entries, optionally deleting the underlying Slate widgets entirely as well.
- L54 _public prototype_ `void RemoveEntry(UUserWidget* EntryWidget);` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)`
- L58 _public prototype_ `virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;`
- L64 _public member_ `int32 NumDesignerPreviewEntries = 3;` — `UPROPERTY(EditAnywhere, Category = DynamicEntryBox, meta = (ClampMin = 0, ClampMax = 20))`
- L70 _public member_ `TFunction<void(UUserWidget*)> OnPreviewEntryCreatedFunc;` — Called whenever a preview entry is made for this widget in the designer. Intended to allow a containing widget to do any additional modifications needed in the interest of maintaining an accurate designer preview.
- L73 _public prototype_ `virtual void SynchronizeProperties() override;`
- L78 _private prototype_ `UUserWidget* BP_CreateEntry();` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox, meta = (DisplayName = "Create Entry", AllowPrivateAccess = true))` — Creates and establishes a new dynamic entry in the box
- L82 _private prototype_ `UUserWidget* BP_CreateEntryOfClass(TSubclassOf<UUserWidget> EntryClass);` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox, meta = (DisplayName = "Create Entry of Class", AllowPrivateAccess = true, DeterminesOutputType = "EntryClass"))` — Creates and establishes a new dynamic entry in the box using the specified class instead of the default.
- L89 _private member_ `TSubclassOf<UUserWidget> EntryWidgetClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EntryLayout, meta = (AllowPrivateAccess = true))` — The class of widget to create entries of. If natively binding this widget, use the EntryClass UPROPERTY metadata to specify the desired entry widget base class.

### `Source/Runtime/UMG/Public/Components/DynamicEntryBoxBase.h` (Public)


#### enum `EDynamicBoxType`  
`enum class EDynamicBoxType : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Horizontal`
- L17 _public enumerator_ `Vertical`
- L18 _public enumerator_ `Wrap`
- L19 _public enumerator_ `VerticalWrap`
- L20 _public enumerator_ `Radial`
- L21 _public enumerator_ `Overlay`

#### class `UDynamicEntryBoxBase`  
`class UDynamicEntryBoxBase : public UWidget`  
_L32-183_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UWidget`
- desc: Base for widgets that support a dynamic number of auto-generated entries at both design- and run-time. Contains all functionality needed to create, construct, and cache an arbitrary number of entry widgets, but exposes no means of entry creation or removal It's up to child classes to decide how they want to perform the population (some may do so entirely on their own without exposing a thing) @see UDynamicEntryBox for a ready-to-use version
- L45 _protected member_ `FVector2D EntrySpacing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetEntrySpacing", Category = EntryLayout)` — The padding to apply between entries in the box. Note horizontal boxes only use the X and vertical boxes only use Y. Value is also ignored for the first entry in the box. Wrap and Overlay types use both X and Y for spacing.
- L50 _protected member_ `TArray<FVector2D> SpacingPattern;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EntryLayout)` — The looping sequence of entry paddings to apply as entries are created. Overlay boxes only. Ignores EntrySpacing if not empty.
- L55 _protected member_ `EDynamicBoxType EntryBoxType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "GetBoxType", Category = DynamicEntryBox, meta = (DesignerRebuild))` — The type of box panel into which created entries are added. Some differences in functionality exist between each type.
- L60 _protected member_ `FSlateChildSize EntrySizeRule;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = EntryLayout)` — Sizing rule to apply to generated entries. Horizontal/Vertical boxes only.
- L65 _protected member_ `TEnumAsByte<EHorizontalAlignment> EntryHorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = EntryLayout)` — Horizontal alignment of generated entries. Horizontal/Vertical/Wrap boxes only.
- L70 _protected member_ `TEnumAsByte<EVerticalAlignment> EntryVerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = EntryLayout)` — Vertical alignment of generated entries. Horizontal/Vertical/Wrap boxes only.
- L75 _protected member_ `int32 MaxElementSize = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = EntryLayout)` — The maximum size of each entry in the dominant axis of the box. Vertical/Horizontal boxes only.
- L80 _protected member_ `FRadialBoxSettings RadialBoxSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter = "SetRadialSettings", BlueprintSetter = "SetRadialSettings", Category = EntryLayout)` — Settings only relevant to RadialBox
- L83 _public prototype_ `UDynamicEntryBoxBase(const FObjectInitializer& Initializer);`
- L84 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L86 _public prototype_ `EDynamicBoxType GetBoxType() const;`
- L87 _public prototype_ `const FVector2D& GetEntrySpacing() const;`
- L90 _public prototype_ `const TArray<UUserWidget*>& GetAllEntries() const;` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)`
- L92 _public prototype_ `const FSlateChildSize& GetEntrySizeRule() const;`
- L94 _public prototype_ `const FRadialBoxSettings& GetRadialBoxSettings() const;`
- L97 _public function_ `template <typename EntryWidgetT = UUserWidget> TArray<EntryWidgetT*> GetTypedEntries() const`
- L111 _public prototype_ `int32 GetNumEntries() const;` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)`
- L114 _public prototype_ `void SetEntrySpacing(const FVector2D& InEntrySpacing);` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)`
- L117 _public prototype_ `void SetRadialSettings(const FRadialBoxSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = DynamicEntryBox)`
- L119 _public prototype_ `EVerticalAlignment GetEntryVerticalAlignment() const;`
- L121 _public prototype_ `EHorizontalAlignment GetEntryHorizontalAlignment() const;`
- L123 _public prototype_ `int32 GetMaxElementSize() const;`
- L126 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L127 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L128 _protected prototype_ `virtual void AddEntryChild(UUserWidget& ChildWidget);`
- L130 _protected prototype_ `bool IsEntryClassValid(TSubclassOf<UUserWidget> InEntryClass) const;`
- L131 _protected prototype_ `UUserWidget* CreateEntryInternal(TSubclassOf<UUserWidget> InEntryClass);`
- L132 _protected prototype_ `void RemoveEntryInternal(UUserWidget* EntryWidget, bool bReleaseSlate = false);`
- L133 _protected prototype_ `FMargin BuildEntryPadding(const FVector2D& DesiredSpacing);`
- L136 _protected prototype_ `void ResetInternal(bool bDeleteWidgets = false);` — Clear out the box entries, optionally deleting the underlying Slate widgets entirely as well.
- L140 _protected function_ `template <typename WidgetT = UUserWidget> void ResetInternal(TFunctionRef<void(WidgetT&)> ResetEntryFunc, bool bDeleteWidgets = false)` — Clear out the box entries, executing the provided reset function for each and optionally deleting the underlying Slate widgets entirely as well.
- L154 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L155 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L159 _protected prototype_ `void InitEntryBoxType(EDynamicBoxType InEntryBoxType);` — Initialize EntryBoxType in the constructor before the SWidget is constructed.
- L162 _protected prototype_ `void InitEntrySizeRule(FSlateChildSize InEntrySizeRule);` — Initialize EntrySizeRule in the constructor before the SWidget is constructed.
- L165 _protected prototype_ `void InitEntryHorizontalAlignment(EHorizontalAlignment InEntryHorizontalAlignment);` — Initialize EntryHorizontalAlignment in the constructor before the SWidget is constructed.
- L168 _protected prototype_ `void InitEntryVerticalAlignment(EVerticalAlignment InEntryVerticalAlignment);` — Initialize EntryVerticalAlignment in the constructor before the SWidget is constructed.
- L171 _protected prototype_ `void InitMaxElementSize(int32 InMaxElementSize);` — Initialize MaxElementSize in the constructor before the SWidget is constructed.
- L175 _protected member_ `TSharedPtr<SPanel> MyPanelWidget;` — Can be a horizontal, vertical, wrap box, or overlay
- L179 _private member_ `FUserWidgetPool EntryWidgetPool;` — `UPROPERTY(Transient)`

### `Source/Runtime/UMG/Public/Components/EditableText.h` (Public)


#### class `UEditableText`  
`class UEditableText : public UWidget`  
_L26-306_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: Editable text box widget
- L32 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextChangedEvent, const FText&, Text);`
- L33 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEditableTextCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`
- L34 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnAllFontFacesFinishLoading_EditableText, UEditableText, OnAllFontFacesFinishLoading);`
- L39 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetText", BlueprintSetter = "SetText", FieldNotify, Category = "Content")` — The text content for this editable text box widget
- L43 _public member_ `FGetText TextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the text of the widget
- L50 _public member_ `FText HintText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetHintText", BlueprintSetter = "SetHintText", Category = Content, meta = (MultiLine = "true"))` — Hint text that appears when there is no text in the text box
- L54 _public member_ `FGetText HintTextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the hint text of the widget
- L58 _public member_ `FEditableTextStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Appearance, meta=(DisplayName="Style", ShowOnlyInnerProperties))` — The style
- L63 _public member_ `bool IsReadOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance)` — Sets whether this text box can actually be modified interactively by the user
- L68 _public member_ `bool IsPassword;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetIsPassword", Category = Appearance)` — Sets whether this text box is for storing a password
- L73 _public member_ `float MinimumDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetMinimumDesiredWidth", Category = "Appearance")` — The minimum desired Width for the text
- L78 _public member_ `bool IsCaretMovedWhenGainFocus;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — When set to true the caret is moved when gaining focus
- L83 _public member_ `bool SelectAllTextWhenFocused;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to select all text when the user clicks to give focus on the widget
- L88 _public member_ `bool RevertTextOnEscape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to allow the user to back out of changes when they press the escape key
- L93 _public member_ `bool ClearKeyboardFocusOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to clear keyboard focus when pressing enter to commit changes
- L98 _public member_ `bool SelectAllTextOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to select all text when pressing enter to commit changes
- L102 _public member_ `bool AllowContextMenu;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Whether the context menu can be opened
- L106 _public member_ `TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — If we're on a platform that requires a virtual keyboard, what kind of keyboard should this widget use?
- L110 _public member_ `FVirtualKeyboardOptions VirtualKeyboardOptions;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Additional options for the virtual keyboard
- L113 _public member_ `EVirtualKeyboardTrigger VirtualKeyboardTrigger;` — `UPROPERTY(EditAnywhere, Category = Behavior, AdvancedDisplay)`
- L117 _public member_ `EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — What action should be taken when the virtual keyboard is dismissed?
- L122 _public member_ `TEnumAsByte<ETextJustify::Type> Justification;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Blueprintgetter = GetJustification, BlueprintSetter = SetJustification, Category = Appearance)` — How the text should be aligned with the margin.
- L127 _public member_ `ETextOverflowPolicy OverflowPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetTextOverflowPolicy", Setter = "SetTextOverflowPolicy", BlueprintSetter = "SetTextOverflowPolicy", Category = "Clipping", AdvancedDisplay, meta = (DisplayName = "Overflow Policy"))` — Sets what happens to text that is clipped and doesn't fit within the clip rect for this widget
- L131 _public member_ `FShapedTextOptions ShapedTextOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Localization, AdvancedDisplay, meta=(ShowOnlyInnerProperties))` — Controls how the text within this widget should be shaped.
- L137 _public member_ `FOnEditableTextChangedEvent OnTextChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextChanged (Editable Text)"))` — Called whenever the text is changed programmatically or interactively by the user
- L141 _public member_ `FOnEditableTextCommittedEvent OnTextCommitted;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextCommitted (Editable Text)"))` — Called whenever the text is committed.  This happens when the user presses enter or the text box loses focus.
- L148 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta=(DisplayName="GetText (Editable Text)"))` — Gets the widget text @return The widget text
- L156 _public prototype_ `void SetText(FText InText);` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta=(DisplayName="SetText (Editable Text)"))` — Directly sets the widget text. Warning: This will wipe any binding created for the Text property! @param InText The text to assign to the widget
- L158 _public prototype_ `bool GetIsPassword() const;`
- L161 _public prototype_ `void SetIsPassword(UPARAM(DisplayName="IsPassword") bool InbIs` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L165 _public prototype_ `FText GetHintText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "GetHintText (Editable Text)"))` — Gets the Hint text that appears when there is no text in the text box
- L168 _public prototype_ `void SetHintText(FText InHintText);` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L171 _public prototype_ `float GetMinimumDesiredWidth() const;` — @return the minimum desired width for this text box
- L179 _public prototype_ `void SetMinimumDesiredWidth(float InMinDesiredWidth);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Set the minimum desired width for this text box @param InMinDesiredWidth new minimum desired width
- L182 _public prototype_ `void SetIsCaretMovedWhenGainFocus(bool bIsCaretMovedWhenGainFocus);` — When set to true the caret is moved when gaining focus
- L185 _public prototype_ `bool GetIsCaretMovedWhenGainFocus() const;` — Return true when the caret is moved when gaining focus
- L188 _public prototype_ `void SetSelectAllTextWhenFocused(bool bSelectAllTextWhenFocused);` — Set to true to select all text when the user clicks to give focus on the widget
- L191 _public prototype_ `bool GetSelectAllTextWhenFocused() const;` — Whether to select all text when the user clicks to give focus on the widget
- L194 _public prototype_ `void SetRevertTextOnEscape(bool bRevertTextOnEscape);` — Set to true to allow the user to back out of changes when they press the escape key
- L197 _public prototype_ `bool GetRevertTextOnEscape() const;` — Whether to allow the user to back out of changes when they press the escape key
- L200 _public prototype_ `bool GetClearKeyboardFocusOnCommit() const;` — Whether to clear keyboard focus when pressing enter to commit changes
- L203 _public prototype_ `void SetSelectAllTextOnCommit(bool bSelectAllTextOnCommit);` — Set to true to select all text when pressing enter to commit changes
- L206 _public prototype_ `bool GetSelectAllTextOnCommit() const;` — Whether to select all text when pressing enter to commit changes
- L209 _public prototype_ `void SetWidgetStyle(const FEditableTextStyle& InEditableTextStyle);` — Set the style and ensure the visual will be updated accordingly
- L211 _public prototype_ `bool GetIsReadOnly() const;`
- L214 _public prototype_ `void SetIsReadOnly(UPARAM(DisplayName="ReadyOnly") bool InbIsRe` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta=(DisplayName="SetIsReadOnly (Editable Text)"))`
- L217 _public prototype_ `ETextJustify::Type GetJustification() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L220 _public prototype_ `void SetJustification(ETextJustify::Type InJustification);` — `UFUNCTION(BlueprintSetter)`
- L223 _public prototype_ `ETextOverflowPolicy GetTextOverflowPolicy() const;` — @return the text overflow policy for this text block.
- L226 _public prototype_ `void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);` — `UFUNCTION(BlueprintSetter)`
- L229 _public prototype_ `void SetClearKeyboardFocusOnCommit(bool bInClearKeyboardFocusOnCommit);` — Set to true to clear keyboard focus when pressing enter to commit changes
- L231 _public prototype_ `void SetKeyboardType(EVirtualKeyboardType::Type Type);`
- L234 _public prototype_ `const FSlateFontInfo& GetFont() const;` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L237 _public prototype_ `void SetFont(FSlateFontInfo InFontInfo);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L240 _public prototype_ `void SetFontMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L243 _public prototype_ `void SetFontOutlineMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L245 _public prototype_ `bool GetEnableIntegratedKeyboard() const;`
- L246 _public prototype_ `void SetEnableIntegratedKeyboard(bool InEnableIntegratedKeyboard);`
- L250 _public prototype_ `void ToggleVirtualKeyboard(bool bShow);` — `UFUNCTION(BlueprintCallable, Category = "VirtualKeyboard")` — Function to spawn virtual keyboard on demand
- L252 _public prototype_ `void SetFontFacesLoadingPaintPolicy(EFontFacesLoadingPaintPolicy InFontFacesLoadingPaintPolicy);`
- L256 _public prototype_ `virtual void SynchronizeProperties() override;`
- L260 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L264 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L270 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L273 _protected prototype_ `void HandleOnTextChanged(const FText& Text);`
- L274 _protected prototype_ `void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);`
- L277 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L280 _protected function_ `void SlateHandleAllFontFacesFinishLoading()`
- L285 _protected member_ `TSharedPtr<SEditableText> MyEditableText;`
- L287 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, Text);`
- L288 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, HintText);`
- L292 _private prototype_ `bool SetTextInternal(const FText& InText);` — @return true if the text was changed, or false if identical.
- L296 _private member_ `bool EnableIntegratedKeyboard;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Mobile, AdvancedDisplay, meta = (AllowPrivateAccess = "true"))` — Whether the integrated keyboard is enabled for this editable text.
- L301 _protected member_ `EFontFacesLoadingPaintPolicy FontFacesLoadingPaintPolicy;` — `UPROPERTY(EditAnywhere, Setter, Category = Font)` — Controls how painting the text in the widget should behave when font faces for the text is still loading.
- L305 _protected member_ `FOnAllFontFacesFinishLoading_EditableText OnAllFontFacesFinishLoading;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event", meta = (DisplayName = "OnAllFontFacesFinishLoading(Editable Text)"))` — Called when all font faces for the text has finished async loading. Is not called if font faces are synchronously loaded.

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextChangedEvent, const FText&, Text);`
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEditableTextCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`

### `Source/Runtime/UMG/Public/Components/EditableTextBox.h` (Public)


#### class `UEditableTextBox`  
`class UEditableTextBox : public UWidget`  
_L27-322_
- reflection: `UCLASS(meta=(DisplayName="Text Box"), MinimalAPI)`
- inherits: `UWidget`
- desc: Allows the user to type in custom text.  Only permits a single line of text to be entered. * No Children * Text Entry
- L33 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextBoxChangedEvent, const FText&, Text);`
- L34 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEditableTextBoxCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditableTextBoxCursorMovedWithSelectionEvent, const FTextLocation&, const FTextSelection&);`
- L37 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnAllFontFacesFinishLoading_EditableTextBox, UEditableTextBox, OnAllFontFacesFinishLoading);`
- L42 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetText", BlueprintSetter = "SetText", FieldNotify, Category = "Content")` — The text content for this editable text box widget
- L46 _public member_ `FGetText TextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the text of the widget
- L52 _public member_ `FEditableTextBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Appearance, meta=(DisplayName="Style", ShowOnlyInnerProperties))` — The style
- L57 _public member_ `FText HintText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetHintText", Category = Content, meta = (MultiLine = "true"))` — Hint text that appears when there is no text in the text box
- L61 _public member_ `FGetText HintTextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the hint text of the widget
- L66 _public member_ `bool IsReadOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance)` — Sets the Text Box as Readonly to prevent it from being modified interactively by the user
- L71 _public member_ `bool IsPassword;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetIsPassword", Category = Appearance)` — Sets whether this text box is for storing a password
- L76 _public member_ `float MinimumDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter=SetMinDesiredWidth, Category = "Appearance")` — The minimum desired size for the text
- L81 _public member_ `bool IsCaretMovedWhenGainFocus;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Behavior, AdvancedDisplay)` — Workaround as we lose focus when the auto completion closes.
- L86 _public member_ `bool SelectAllTextWhenFocused;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Behavior, AdvancedDisplay)` — Whether to select all text when the user clicks to give focus on the widget
- L91 _public member_ `bool RevertTextOnEscape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Behavior, AdvancedDisplay)` — Whether to allow the user to back out of changes when they press the escape key
- L96 _public member_ `bool ClearKeyboardFocusOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Behavior, AdvancedDisplay)` — Whether to clear keyboard focus when pressing enter to commit changes
- L101 _public member_ `bool SelectAllTextOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Behavior, AdvancedDisplay)` — Whether to select all text when pressing enter to commit changes
- L105 _public member_ `bool AllowContextMenu;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Whether the context menu can be opened
- L109 _public member_ `TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — If we're on a platform that requires a virtual keyboard, what kind of keyboard should this widget use?
- L113 _public member_ `FVirtualKeyboardOptions VirtualKeyboardOptions;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Additional options to use for the virtual keyboard summoned by this widget
- L117 _public member_ `EVirtualKeyboardTrigger VirtualKeyboardTrigger;` — `UPROPERTY(EditAnywhere, Category = Behavior, AdvancedDisplay)` — The type of event that will trigger the display of the virtual keyboard
- L121 _public member_ `EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — What action should be taken when the virtual keyboard is dismissed?
- L126 _public member_ `TEnumAsByte<ETextJustify::Type> Justification;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetJustification, Category = Appearance)` — How the text should be aligned with the margin.
- L131 _public member_ `ETextOverflowPolicy OverflowPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="GetTextOverflowPolicy", Setter= "SetTextOverflowPolicy", BlueprintSetter = "SetTextOverflowPolicy", Category = "Clipping", AdvancedDisplay, meta = (DisplayName = "Overflow Policy"))` — Sets what happens to text that is clipped and doesn't fit within the clip rect for this widget
- L136 _public member_ `FShapedTextOptions ShapedTextOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Localization, AdvancedDisplay, meta=(ShowOnlyInnerProperties))` — Controls how the text within this widget should be shaped.
- L142 _public member_ `FOnEditableTextBoxChangedEvent OnTextChanged;` — `UPROPERTY(BlueprintAssignable, Category="TextBox|Event")` — Called whenever the text is changed programmatically or interactively by the user
- L146 _public member_ `FOnEditableTextBoxCommittedEvent OnTextCommitted;` — `UPROPERTY(BlueprintAssignable, Category="TextBox|Event")` — Called whenever the text is committed.  This happens when the user presses enter or the text box loses focus.
- L149 _public member_ `FOnEditableTextBoxCursorMovedWithSelectionEvent OnCursorMovedWithSelectionEvent;` — Called whenever the user's selection and/or cursor position of the text has changed.
- L161 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="GetText (Text Box)"))` — Gets the widget text @return The widget text
- L169 _public prototype_ `void SetText(FText InText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetText (Text Box)"))` — Directly sets the widget text. Warning: This will wipe any binding created for the Text property! @param InText The text to assign to the widget
- L172 _public prototype_ `FText GetHintText() const;` — Gets the Hint text that appears when there is no text in the text box
- L179 _public prototype_ `void SetHintText(FText InText);` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "Set Hint Text (Text Box)"))` — Sets the Hint text that appears when there is no text in the text box @param InHintText The text that appears when there is no text in the text box
- L182 _public prototype_ `float GetMinimumDesiredWidth() const;` — @return the minimum desired width for this text box
- L189 _public prototype_ `void SetMinDesiredWidth(float InMinDesiredWidth);` — Set the minimum desired width for this text box @param InMinDesiredWidth new minimum desired width
- L192 _public prototype_ `void SetIsCaretMovedWhenGainFocus(bool bIsCaretMovedWhenGainFocus);` — When set to true the caret is moved when gaining focus
- L195 _public prototype_ `bool GetIsCaretMovedWhenGainFocus() const;` — Return true when the caret is moved when gaining focus
- L198 _public prototype_ `void SetSelectAllTextWhenFocused(bool bSelectAllTextWhenFocused);` — Set to true to select all text when the user clicks to give focus on the widget
- L201 _public prototype_ `bool GetSelectAllTextWhenFocused() const;` — Whether to select all text when the user clicks to give focus on the widget
- L204 _public prototype_ `void SetRevertTextOnEscape(bool bRevertTextOnEscape);` — Set to true to allow the user to back out of changes when they press the escape key
- L207 _public prototype_ `bool GetRevertTextOnEscape() const;` — Whether to allow the user to back out of changes when they press the escape key
- L210 _public prototype_ `void SetClearKeyboardFocusOnCommit(bool bClearKeyboardFocusOnCommit);` — Set to true to clear keyboard focus when pressing enter to commit changes
- L213 _public prototype_ `bool GetClearKeyboardFocusOnCommit() const;` — Whether to clear keyboard focus when pressing enter to commit changes
- L216 _public prototype_ `void SetSelectAllTextOnCommit(bool bSelectAllTextOnCommit);` — Set to true to select all text when pressing enter to commit changes
- L219 _public prototype_ `bool GetSelectAllTextOnCommit() const;` — Whether to select all text when pressing enter to commit changes
- L222 _public prototype_ `bool IsAnyTextSelected() const;` — Whether any text is selected in the text block
- L225 _public prototype_ `void SetError(FText InError);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetError (Text Box)"))`
- L228 _public prototype_ `bool GetIsReadOnly() const;` — Return true when this text cannot be modified interactively by the user
- L232 _public prototype_ `void SetIsReadOnly(UPARAM(DisplayName = "ReadyOnly") bool bR` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "SetIsReadOnly (Editable Text)"))` — Sets the Text as Readonly to prevent it from being modified interactively by the user
- L234 _public prototype_ `bool GetIsPassword() const;`
- L237 _public prototype_ `void SetIsPassword(bool bIsPassword);` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "IsPassword"))`
- L240 _public prototype_ `void ClearError();` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L243 _public prototype_ `bool HasError() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L245 _public prototype_ `ETextJustify::Type GetJustification() const;`
- L248 _public prototype_ `void SetJustification(ETextJustify::Type InJustification);` — `UFUNCTION(BlueprintSetter)`
- L251 _public prototype_ `ETextOverflowPolicy GetTextOverflowPolicy() const;` — @return the text overflow policy for this text block.
- L259 _public prototype_ `void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);` — `UFUNCTION(BlueprintSetter)` — Set the text overflow policy for this text box. @param InOverflowPolicy the new text overflow policy.
- L261 _public prototype_ `void SetWidgetStyle(const FEditableTextBoxStyle& InStyle);`
- L263 _public prototype_ `const FEditableTextBoxStyle& GetWidgetStyle() const;`
- L266 _public prototype_ `void SetForegroundColor(FLinearColor color);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetForegroundColor (Text Box)"))`
- L268 _public prototype_ `void SetFontFacesLoadingPaintPolicy(EFontFacesLoadingPaintPolicy InFontFacesLoadingPaintPolicy);`
- L270 _public prototype_ `virtual void SynchronizeProperties() override;`
- L274 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L278 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L280 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L284 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L287 _protected prototype_ `virtual void HandleOnTextChanged(const FText& Text);`
- L288 _protected prototype_ `virtual void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);`
- L289 _protected prototype_ `virtual void HandleOnCursorMovedWithSelection(const FTextLocation& InLocation, const FTextSelection& Selection);`
- L292 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L295 _protected function_ `void SlateHandleAllFontFacesFinishLoading()`
- L300 _protected member_ `TSharedPtr<SEditableTextBox> MyEditableTextBlock;`
- L302 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, Text);`
- L303 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, HintText);`
- L307 _private prototype_ `bool SetTextInternal(const FText& InText);` — @return true if the text was changed, or false if identical.
- L311 _private member_ `bool bIsFontDeprecationDone;` — `UPROPERTY()`
- L317 _protected member_ `EFontFacesLoadingPaintPolicy FontFacesLoadingPaintPolicy;` — `UPROPERTY(EditAnywhere, Setter, Category = Font)` — Controls how painting the text in the widget should behave when font faces for the text is still loading.
- L321 _protected member_ `FOnAllFontFacesFinishLoading_EditableTextBox OnAllFontFacesFinishLoading;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event", meta = (DisplayName = "OnAllFontFacesFinishLoading(Editable Text)"))` — Called when all font faces for the text has finished async loading. Is not called if font faces are synchronously loaded.

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextBoxChangedEvent, const FText&, Text);`
- L34 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEditableTextBoxCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditableTextBoxCursorMovedWithSelectionEvent, const FTextLocation&, const FTextSelection&);`

### `Source/Runtime/UMG/Public/Components/ExpandableArea.h` (Public)


#### class `UExpandableArea`  
`class UExpandableArea : public UWidget, public INamedSlotInterface`  
_L25-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget,INamedSlotInterface`
- L33 _public member_ `FExpandableAreaStyle Style;` — `UE_DEPRECATED(5.2, "Direct access to Style is deprecated. Please use SetStyle or GetStyle.")` — `UPROPERTY(EditAnywhere, Category = "Style")`
- L37 _public member_ `FSlateBrush BorderBrush;` — `UE_DEPRECATED(5.2, "Direct access to BorderBrush is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Style")`
- L41 _public member_ `FSlateColor BorderColor;` — `UE_DEPRECATED(5.2, "Direct access to BorderColor is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Style")`
- L46 _public member_ `bool bIsExpanded;` — `UE_DEPRECATED(5.2, "Direct access to bIsExpanded is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetIsExpanded", Setter = "SetIsExpanded", BlueprintGetter = "GetIsExpanded", BlueprintSetter = "SetIsExpanded", FieldNotify, Category = "Expansion")`
- L51 _public member_ `float MaxHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Expansion")` — The maximum height of the area
- L55 _public member_ `FMargin HeaderPadding;` — `UE_DEPRECATED(5.2, "Direct access to HeaderPadding is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Expansion")`
- L60 _public member_ `FMargin AreaPadding;` — `UE_DEPRECATED(5.2, "Direct access to AreaPadding is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Expansion")`
- L64 _public member_ `FOnExpandableAreaExpansionChanged OnExpansionChanged;` — `UPROPERTY(BlueprintAssignable, Category="ExpandableArea|Event")` — A bindable delegate for the IsChecked.
- L69 _public prototype_ `bool GetIsExpanded() const;` — `UFUNCTION(BlueprintCallable, Category="Expansion")`
- L72 _public prototype_ `void SetIsExpanded(bool IsExpanded);` — `UFUNCTION(BlueprintCallable, Category="Expansion")`
- L75 _public prototype_ `void SetIsExpanded_Animated(bool IsExpanded);` — `UFUNCTION(BlueprintCallable, Category = "Expansion")`
- L77 _public prototype_ `const FExpandableAreaStyle& GetStyle() const;`
- L79 _public prototype_ `void SetStyle(const FExpandableAreaStyle& InStyle);`
- L81 _public prototype_ `const FSlateBrush& GetBorderBrush() const;`
- L83 _public prototype_ `void SetBorderBrush(const FSlateBrush& InBorderBrush);`
- L85 _public prototype_ `const FSlateColor& GetBorderColor() const;`
- L87 _public prototype_ `void SetBorderColor(const FSlateColor& InBorderColor);`
- L89 _public prototype_ `float GetMaxHeight() const;`
- L91 _public prototype_ `void SetMaxHeight(float InMaxHeight);`
- L93 _public prototype_ `FMargin GetHeaderPadding() const;`
- L95 _public prototype_ `void SetHeaderPadding(FMargin InHeaderPadding);`
- L97 _public prototype_ `FMargin GetAreaPadding() const;`
- L98 _public prototype_ `void SetAreaPadding(FMargin InAreaPadding);`
- L101 _public prototype_ `virtual void GetSlotNames(TArray<FName>& SlotNames) const override;`
- L102 _public prototype_ `virtual UWidget* GetContentForSlot(FName SlotName) const override;`
- L103 _public prototype_ `virtual void SetContentForSlot(FName SlotName, UWidget* Content) override;`
- L109 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L113 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L117 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L118 _public prototype_ `virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget) override;`
- L119 _public prototype_ `virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget) override;`
- L124 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L127 _protected prototype_ `void SlateExpansionChanged(bool NewState);`
- L131 _protected member_ `TObjectPtr<UWidget> HeaderContent;` — `UPROPERTY()`
- L134 _protected member_ `TObjectPtr<UWidget> BodyContent;` — `UPROPERTY()`
- L136 _protected member_ `TSharedPtr<SExpandableArea> MyExpandableArea;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpandableAreaExpansionChanged, UExpandableArea*, Area, bool, bIsExpanded);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpandableAreaExpansionChanged, UExpandableArea*, Area, bool, bIsExpanded);`

### `Source/Runtime/UMG/Public/Components/GridPanel.h` (Public)


#### class `UGridPanel`  
`class UGridPanel : public UPanelWidget`  
_L19-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: A table-like panel that retains the width of every column throughout the table.
- L27 _public member_ `TArray<float> ColumnFill;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fill Rules")` — The column fill rules
- L31 _public member_ `TArray<float> RowFill;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fill Rules")` — The row fill rules
- L36 _public prototype_ `UGridSlot* AddChildToGrid(UWidget* Content, int32 InRow = 0, int32 InColumn = 0);` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L39 _public prototype_ `void SetColumnFill(int32 ColumnIndex, float Coefficient);` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L42 _public prototype_ `void SetRowFill(int32 RowIndex, float Coefficient);` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L45 _public prototype_ `void ClearFill();` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L50 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L53 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L56 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L62 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L63 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L64 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L69 _protected member_ `TSharedPtr<SGridPanel> MyGridPanel;`
- L73 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/GridSlot.h` (Public)


#### class `UGridSlot`  
`class UGridSlot : public UPanelSlot`  
_L19-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: A slot for UGridPanel, these slots all share the same size as the largest slot in the grid.
- L28 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPadding", Category="Layout|Grid Slot")` — The padding area between the slot and the content it contains.
- L33 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Grid Slot")` — The alignment of the object horizontally.
- L38 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Grid Slot")` — The alignment of the object vertically.
- L43 _public member_ `int32 Row;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetRow", meta=( UIMin = "0" ), Category="Layout|Grid Slot")` — The row index of the cell this slot is in
- L48 _public member_ `int32 RowSpan;` — `UE_DEPRECATED(5.1, "Direct access to RowSpan is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetRowSpan", Category="Layout|Grid Slot")`
- L53 _public member_ `int32 Column;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetColumn", meta=( UIMin = "0" ), Category="Layout|Grid Slot")` — The column index of the cell this slot is in
- L58 _public member_ `int32 ColumnSpan;` — `UE_DEPRECATED(5.1, "Direct access to ColumnSpan is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetColumnSpan", Category="Layout|Grid Slot")`
- L63 _public member_ `int32 Layer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetLayer", Category="Layout|Grid Slot")` — Positive values offset this cell to be hit-tested and drawn on top of others. Default is 0; i.e. no offset.
- L68 _public member_ `FVector2D Nudge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetNudge", Category="Layout|Grid Slot")` — Offset this slot's content by some amount; positive values offset to lower right
- L72 _public prototype_ `FMargin GetPadding() const;`
- L75 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Border Slot")`
- L78 _public prototype_ `int32 GetRow() const;` — Gets the row index of the slot
- L82 _public prototype_ `void SetRow(int32 InRow);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")` — Sets the row index of the slot, this determines what cell the slot is in the panel
- L85 _public prototype_ `int32 GetRowSpan() const;` — Gets how many rows this this slot spans over
- L89 _public prototype_ `void SetRowSpan(int32 InRowSpan);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")` — How many rows this this slot spans over
- L92 _public prototype_ `int32 GetColumn() const;` — Gets the column index of the slot
- L96 _public prototype_ `void SetColumn(int32 InColumn);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")` — Sets the column index of the slot, this determines what cell the slot is in the panel
- L99 _public prototype_ `int32 GetColumnSpan() const;` — Gets how many columns this slot spans over
- L103 _public prototype_ `void SetColumnSpan(int32 InColumnSpan);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")` — How many columns this slot spans over
- L106 _public prototype_ `int32 GetLayer() const;` — Gets the offset this cell drawn on top of others.
- L110 _public prototype_ `void SetLayer(int32 InLayer);` — `UFUNCTION(BlueprintCallable, Category = "Layout|Grid Slot")` — Sets positive values offset this cell to be hit-tested and drawn on top of others.
- L113 _public prototype_ `FVector2D GetNudge() const;` — Gets the offset for this slot's content
- L117 _public prototype_ `void SetNudge(FVector2D InNudge);` — `UFUNCTION(BlueprintCallable, Category = "Layout|Grid Slot")` — Sets the offset for this slot's content by some amount; positive values offset to lower right
- L120 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L124 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")`
- L127 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L131 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Grid Slot")`
- L134 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L138 _public prototype_ `void BuildSlot(TSharedRef<SGridPanel> GridPanel);` — Builds the underlying FSlot for the Slate layout panel.
- L140 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L143 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L144 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`
- L149 _private member_ `SGridPanel::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/HorizontalBox.h` (Public)


#### class `UHorizontalBox`  
`class UHorizontalBox : public UPanelWidget`  
_L21-53_
- reflection: `UCLASS(meta = (ShortTooltip = "A layout panel for automatically laying child widgets out horizontally"), MinimalAPI)`
- inherits: `UPanelWidget`
- desc: Allows widgets to be laid out in a flow horizontally. * Many Children * Flow Horizontal
- L27 _private prototype_ `UHorizontalBoxSlot* AddChildToHorizontalBox(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L31 _private prototype_ `virtual const FText GetPaletteCategory() override;` — UWidget interface
- L35 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L40 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L41 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L42 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L47 _protected member_ `TSharedPtr<class SHorizontalBox> MyHorizontalBox;`
- L51 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/HorizontalBoxSlot.h` (Public)


#### class `UHorizontalBoxSlot`  
`class UHorizontalBoxSlot : public UPanelSlot`  
_L16-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- L21 _private member_ `SHorizontalBox::FSlot* Slot;`
- L28 _public member_ `FSlateChildSize Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetSize", Category = "Layout|Horizontal Box Slot")` — How much space this slot should occupy in the direction of the panel.
- L33 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetPadding", Category = "Layout|Horizontal Box Slot")` — The amount of padding between the slots parent and the content.
- L37 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UE_DEPRECATED(5.1, "Direct access to HorizontalAlignment is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetHorizontalAlignment", Category = "Layout|Horizontal Box Slot")`
- L41 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UE_DEPRECATED(5.1, "Direct access to VerticalAlignment is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetVerticalAlignment", Category = "Layout|Horizontal Box Slot")`
- L45 _public prototype_ `FMargin GetPadding() const;`
- L48 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Horizontal Box Slot")`
- L50 _public prototype_ `FSlateChildSize GetSize() const;`
- L53 _public prototype_ `void SetSize(FSlateChildSize InSize);` — `UFUNCTION(BlueprintCallable, Category="Layout|Horizontal Box Slot")`
- L55 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L58 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Horizontal Box Slot")`
- L60 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L63 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Horizontal Box Slot")`
- L67 _public prototype_ `void BuildSlot(TSharedRef<SHorizontalBox> HorizontalBox);`
- L70 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L73 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L76 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L77 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`

### `Source/Runtime/UMG/Public/Components/Image.h` (Public)


#### class `UImage`  
`class UImage : public UWidget`  
_L30-206_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: The image widget allows you to display a Slate Brush, or texture or material in the UI. * No Children
- L39 _public member_ `FSlateBrush Brush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetBrush", FieldNotify, Category=Appearance)` — Image to draw
- L43 _public member_ `FGetSlateBrush BrushDelegate;` — `UPROPERTY()` — A bindable delegate for the Image.
- L48 _public member_ `FLinearColor ColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetColorAndOpacity", Category=Appearance, meta=( sRGB="true"))` — Color and opacity
- L52 _public member_ `FGetLinearColor ColorAndOpacityDelegate;` — `UPROPERTY()` — A bindable delegate for the ColorAndOpacity.
- L57 _public member_ `bool bFlipForRightToLeftFlowDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "ShouldFlipForRightToLeftFlowDirection", Setter = "SetFlipForRightToLeftFlowDirection", Category = "Localization")` — Flips the image if the localization's flow direction is RightToLeft
- L62 _public member_ `FOnPointerEvent OnMouseButtonDownEvent;` — `UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))`
- L68 _public prototype_ `void SetColorAndOpacity(FLinearColor InColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L70 _public prototype_ `const FLinearColor& GetColorAndOpacity() const;`
- L74 _public prototype_ `void SetOpacity(float InOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L78 _public prototype_ `void SetBrushSize(FVector2D DesiredSize);` — `UE_DEPRECATED(5.0, "Deprecated. Use SetDesiredSizeOverride instead.")`
- L81 _public prototype_ `void SetDesiredSizeOverride(FVector2D DesiredSize);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L85 _public prototype_ `void SetBrushTintColor(FSlateColor TintColor);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L89 _public prototype_ `void SetBrushResourceObject(UObject* ResourceObject);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L93 _public prototype_ `virtual void SetBrush(const FSlateBrush& InBrush);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L95 _public prototype_ `const FSlateBrush& GetBrush() const;`
- L99 _public prototype_ `virtual void SetBrushFromAsset(USlateBrushAsset* Asset);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L108 _public prototype_ `virtual void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize = false);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the Brush to the specified Texture. @param Texture Texture to use to set on Brush. @param bMatchSize If true, image will change its size to texture size. If false, texture will be stretched to image size.
- L117 _public prototype_ `virtual void SetBrushFromAtlasInterface(TScriptInterface<ISlateTextureAtlasInterface> AtlasRegion, bool bMatchSize = false);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the Brush to the specified Atlas Region. @param AtlasRegion Region of the Atlas to use to set on Brush. @param bMatchSize If true, image will change its size to atlas region size. If false, atlas region will be stretched to image size.
- L126 _public prototype_ `virtual void SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize = false);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the Brush to the specified Dynamic Texture. @param Texture Dynamic Texture to use to set on Brush. @param bMatchSize If true, image will change its size to texture size. If false, texture will be stretched to image size.
- L130 _public prototype_ `virtual void SetBrushFromMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L139 _public prototype_ `virtual void SetBrushFromSoftTexture(TSoftObjectPtr<UTexture2D> SoftTexture, bool bMatchSize = false);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the Brush to the specified Soft Texture. @param SoftTexture Soft Texture to use to set on Brush. @param bMatchSize If true, image will change its size to texture size. If false, texture will be stretched to image size.
- L143 _public prototype_ `virtual void SetBrushFromSoftMaterial(TSoftObjectPtr<UMaterialInterface> SoftMaterial);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L147 _public prototype_ `UMaterialInstanceDynamic* GetDynamicMaterial();` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L149 _public prototype_ `void SetFlipForRightToLeftFlowDirection(bool InbFlipForRightToLeftFlowDirection);`
- L151 _public prototype_ `bool ShouldFlipForRightToLeftFlowDirection() const;`
- L154 _public prototype_ `virtual void SynchronizeProperties() override;`
- L158 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L163 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L169 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L173 _protected prototype_ `const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;` — Translates the bound brush data and assigns it to the cached brush used by this widget.
- L176 _protected prototype_ `void RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, TFunction<void()>&& Callback);` — Called when we need to stream in content.
- L177 _protected prototype_ `virtual void RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, FStreamableDelegate DelegateToCall);`
- L180 _protected prototype_ `virtual void CancelImageStreaming();` — Called when we need to abort the texture being streamed in.
- L183 _protected prototype_ `virtual void OnImageStreamingStarted(TSoftObjectPtr<UObject> SoftObject);` — Called when the image streaming starts, after the other one was cancelled.
- L186 _protected prototype_ `virtual void OnImageStreamingComplete(TSoftObjectPtr<UObject> LoadedSoftObject);` — Called when the image streaming completes.
- L189 _protected prototype_ `FReply HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L192 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L196 _protected member_ `TSharedPtr<SImage> MyImage;`
- L198 _protected member_ `TSharedPtr<FStreamableHandle> StreamingHandle;`
- L199 _protected member_ `FSoftObjectPath StreamingObjectPath;`
- L204 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, ColorAndOpacity);`

### `Source/Runtime/UMG/Public/Components/InputKeySelector.h` (Public)


#### class `UInputKeySelector`  
`class UInputKeySelector : public UWidget`  
_L21-182_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A widget for selecting a single key or a single key with a modifier.
- L26 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnKeySelected, FInputChord, SelectedKey );`
- L27 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnIsSelectingKeyChanged );`
- L33 _public member_ `FButtonStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetButtonStyle", Setter = "SetButtonStyle", Category = Appearance, meta = (DisplayName = "Style"))` — The button style used at runtime
- L38 _public member_ `FTextBlockStyle TextStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance, meta = (DisplayName = "Text Style"))` — The button style used at runtime
- L43 _public member_ `FInputChord SelectedKey;` — `UPROPERTY(BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetSelectedKey", FieldNotify, Category = "Key Selection")` — The currently selected key chord.
- L48 _public member_ `FMargin Margin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance)` — The amount of blank space around the text used to display the currently selected key.
- L53 _public member_ `FText KeySelectionText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetKeySelectionText", Category = Appearance)` — Sets the text which is displayed while selecting keys.
- L58 _public member_ `FText NoKeySpecifiedText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetNoKeySpecifiedText", Category = Appearance)` — Sets the text to display when no key text is available or not selecting a key.
- L66 _public member_ `bool bAllowModifierKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "AllowModifierKeys", Setter = "SetAllowModifierKeys", BlueprintSetter = "SetAllowModifierKeys", Category = "Key Selection")` — When true modifier keys such as control and alt are allowed in the input chord representing the selected key, if false modifier keys are ignored.
- L71 _public member_ `bool bAllowGamepadKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "AllowGamepadKeys", Setter = "SetAllowGamepadKeys", BlueprintSetter = "SetAllowGamepadKeys", Category = "Key Selection")` — When true gamepad keys are allowed in the input chord representing the selected key, otherwise they are ignored.
- L75 _public member_ `TArray<FKey> EscapeKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key Selection")` — When true gamepad keys are allowed in the input chord representing the selected key, otherwise they are ignored.
- L80 _public member_ `FOnKeySelected OnKeySelected;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called whenever a new key is selected by the user.
- L84 _public member_ `FOnIsSelectingKeyChanged OnIsSelectingKeyChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called whenever the key selection mode starts or stops.
- L88 _public prototype_ `void SetSelectedKey(const FInputChord& InSelectedKey);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the currently selected key.
- L91 _public prototype_ `FInputChord GetSelectedKey() const;` — Returns the currently selected key.
- L95 _public prototype_ `void SetKeySelectionText( FText InKeySelectionText );` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the text which is displayed while selecting keys.
- L98 _public prototype_ `const FText& GetKeySelectionText() const;` — Returns the text which is displayed while selecting keys.
- L102 _public prototype_ `void SetNoKeySpecifiedText(FText InNoKeySpecifiedText);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the text to display when no key text is available or not selecting a key.
- L105 _public prototype_ `const FText& GetNoKeySpecifiedText() const;` — Returns the text to display when no key text is available or not selecting a key.
- L109 _public prototype_ `void SetAllowModifierKeys(bool bInAllowModifierKeys );` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets whether or not modifier keys are allowed in the selected key.
- L112 _public prototype_ `bool AllowModifierKeys() const;` — Returns true if modifier keys keys are allowed, otherwise returns false.
- L116 _public prototype_ `void SetAllowGamepadKeys(bool bInAllowGamepadKeys);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets whether or not gamepad keys are allowed in the selected key.
- L119 _public prototype_ `bool AllowGamepadKeys() const;` — Returns true if gamepad keys are allowed, otherwise returns false.
- L123 _public prototype_ `bool GetIsSelectingKey() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Returns true if the widget is currently selecting a key, otherwise returns false.
- L127 _public prototype_ `void SetTextBlockVisibility(const ESlateVisibility InVisibility);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the visibility of the text block.
- L130 _public prototype_ `void SetButtonStyle(const FButtonStyle& ButtonStyle);` — Sets the style of the button used to start key selection mode.
- L134 _public prototype_ `void SetButtonStyle(const FButtonStyle* ButtonStyle);` — `UE_DEPRECATED(5.2, "SetButtonStyle with pointer type parameter is deprecated. Please pass a reference instead.")` — Sets the style of the button used to start key selection mode.
- L137 _public prototype_ `const FButtonStyle& GetButtonStyle() const;` — Returns the style of the button used to start key selection mode.
- L140 _public prototype_ `void SetTextStyle(const FTextBlockStyle& InTextStyle);` — Sets the style of the text used inside the button.
- L143 _public prototype_ `const FTextBlockStyle& GetTextStyle() const;` — Returns the style of the text used inside the button.
- L146 _public prototype_ `void SetMargin(const FMargin& InMargin);` — Sets the amount of blank space around the text used to display the currently selected key.
- L149 _public prototype_ `const FMargin& GetMargin() const;` — Returns the amount of blank space around the text used to display the currently selected key.
- L153 _public prototype_ `void SetEscapeKeys(const TArray<FKey>& InKeys);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets escape keys.
- L157 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L159 _public prototype_ `virtual void SynchronizeProperties() override;`
- L164 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L168 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L172 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L176 _private prototype_ `virtual void HandleKeySelected(const FInputChord& InSelectedKey);`
- L177 _private prototype_ `void HandleIsSelectingKeyChanged();`
- L181 _private member_ `TSharedPtr<SInputKeySelector> MyInputKeySelector;` — The input key selector widget managed by this object.

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnKeySelected, FInputChord, SelectedKey );`
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnIsSelectingKeyChanged );`

### `Source/Runtime/UMG/Public/Components/InvalidationBox.h` (Public)


#### class `UInvalidationBox`  
`class UInvalidationBox : public UContentWidget`  
_L19-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: Invalidate * Single Child * Caching / Performance
- L30 _public prototype_ `void InvalidateCache();` — `UE_DEPRECATED(4.27, "InvalidationCache is not used.")` — `UFUNCTION(BlueprintCallable, Category="Invalidation Box", meta=(DeprecatedFunction))`
- L37 _public prototype_ `bool GetCanCache() const;` — `UFUNCTION(BlueprintCallable, Category="Invalidation Box")` — @returns true when the invalidation box cache the widgets. The widgets will be updated only if they get invalidated.
- L44 _public prototype_ `void SetCanCache(bool CanCache);` — `UFUNCTION(BlueprintCallable, Category="Invalidation Box")` — Tell the InvalidationBox to use the invalidation process. @note the other internal flags can disable the option.
- L46 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L49 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L55 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L56 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L60 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L70 _protected member_ `bool bCanCache;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetCanCache", Setter = "SetCanCache", BlueprintGetter = "GetCanCache", BlueprintSetter = "SetCanCache", Category = "Caching")` — Should the invalidation panel cache the widgets?  Making this false makes it so the invalidation panel stops acting like an invalidation panel, just becomes a simple container widget.
- L73 _protected member_ `TSharedPtr<class SInvalidationPanel> MyInvalidationPanel;`

### `Source/Runtime/UMG/Public/Components/ListView.h` (Public)


#### class `UListView`  
`class UListView : public UListViewBase, public ITypedUMGListView<UObject*>`  
_L41-451_
- reflection: `UCLASS(meta = (EntryInterface = "/Script/UMG.UserObjectListEntry"), MinimalAPI)`
- inherits: `UListViewBase,ITypedUMGListView<UObject*>`
- desc: A virtualized list that allows up to thousands of items to be displayed. An important distinction to keep in mind here is "Item" vs. "Entry" The list itself is based on a list of n items, but only creates as many entry widgets as can fit on screen. For example, a scrolling ListView of 200 items with 5 currently visible will only have created 5 entry widgets. To make a widget usable as an entry in a ListView, it must inherit from the IUserObjectListEntry interface.
- L48 _public prototype_ `UListView(const FObjectInitializer& Initializer);`
- L50 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L51 _public prototype_ `virtual void PostLoad() override;`
- L55 _public function_ `template <typename ItemObjectT, typename AllocatorType = FDefaultAllocator> void SetListItems(const TArray<ItemObjectT, AllocatorType>& InListItems)` — Set the list of items to display within this listview
- L72 _public function_ `ESelectionMode::Type GetSelectionMode() const`
- L73 _public function_ `EOrientation GetOrientation() const`
- L76 _public function_ `template <typename RowWidgetT = UUserWidget> RowWidgetT* GetEntryWidgetFromItem(const UObject* Item) const`
- L80 _public prototype_ `void SetSelectedItem(const UObject* Item);`
- L84 _public function_ `template <typename ObjectT = UObject> ObjectT* GetSelectedItem() const` — Gets the first selected item, if any; recommended that you only use this for single selection lists.
- L94 _public function_ `const TArray<UObject*>& GetListItems() const` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Gets the list of all items in the list. Note that each of these items only has a corresponding entry widget when visible. Use GetDisplayedEntryWidgets to get the currently displayed widgets.
- L98 _public prototype_ `void AddItem(UObject* Item);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Adds an the item to the end of the list
- L102 _public prototype_ `void AddItemAt(UObject* Item, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Adds an the item to the list at the given index
- L106 _public prototype_ `void AddItems(const TArray<UObject*>& Items);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Adds multiple items to the end of the list
- L110 _public prototype_ `void AddItemsAt(const TArray<UObject*>& Items, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Adds multiple items to the list starting at the given index
- L114 _public prototype_ `void RemoveItem(UObject* Item);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Removes an the item from the list
- L118 _public prototype_ `void RemoveItems(const TArray<UObject*>& Items);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Removes multiple items from the list
- L122 _public prototype_ `UObject* GetItemAt(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Returns the item at the given index
- L126 _public prototype_ `int32 GetNumItems() const;` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Returns the total number of items
- L130 _public prototype_ `int32 GetIndexForItem(const UObject* Item) const;` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Returns the index that the specified item is at. Will return the first found, or -1 for not found
- L134 _public prototype_ `void ClearListItems();` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Removes all items from the list
- L138 _public prototype_ `void SetSelectionMode(TEnumAsByte<ESelectionMode::Type> SelectionMode);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Sets the new selection mode, preserving the current selection where possible.
- L142 _public prototype_ `void SetScrollIntoViewAlignment (EScrollIntoViewAlignment NewScrollIntoViewAlignment);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Sets ScrollIntoViewAlignment which allows to stick the selected item to either side or center
- L146 _public prototype_ `void SetEnableProximateEntryNavigation(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Sets whether spatially proximate focus routing is enabled for this list view at runtime.
- L150 _public prototype_ `void SetScrollBarPadding(const FMargin& InScrollBarPadding);` — `UFUNCTION(Category = ListView)` — Sets padding around the scrollbar.
- L154 _public prototype_ `bool IsRefreshPending() const;` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Returns true if a refresh is pending and the list will be rebuilt on the next tick
- L158 _public prototype_ `void ScrollIndexIntoView(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Requests that the item at the given index is scrolled into view
- L162 _public prototype_ `void SetSelectedIndex(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Sets the item at the given index as the sole selected item.
- L166 _public prototype_ `void NavigateToIndex(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Requests that the item at the given index navigated to, scrolling it into view if needed.
- L168 _public prototype_ `virtual UObject* GetListObjectFromEntry(UUserWidget& EntryWidget) override;`
- L171 _protected prototype_ `virtual void OnItemsChanged(const TArray<UObject*>& AddedItems, const TArray<UObject*>& RemovedItems);`
- L174 _protected prototype_ `void OnListItemEndPlayed(AActor* Item, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L177 _protected prototype_ `void OnListItemOuterEndPlayed(AActor* ItemOuter, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L179 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L180 _protected prototype_ `virtual void HandleListEntryHovered(UUserWidget& EntryWidget) override;`
- L181 _protected prototype_ `virtual void HandleListEntryUnhovered(UUserWidget& EntryWidget) override;`
- L183 _protected prototype_ `virtual UDragDropOperation* HandleListEntryDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent, UUserWidget& EntryWidget) override;` — Drag Drop handlers
- L184 _protected prototype_ `virtual TOptional<EItemDropZone> HandleListEntryCanAcceptDrop(const FDragDropEvent& DropEvent, EItemDropZone DropZone, UUserWidget& EntryWidget) override;`
- L185 _protected prototype_ `virtual FReply HandleListEntryAcceptDrop(const FDragDropEvent& DropEvent, EItemDropZone DropZone, UUserWidget& EntryWidget) override;`
- L186 _protected prototype_ `virtual void HandleListEntryDragEnter(const FDragDropEvent& DropEvent, UUserWidget& EntryWidget) override;`
- L187 _protected prototype_ `virtual void HandleListEntryDragLeave(const FDragDropEvent& DropEvent, UUserWidget& EntryWidget) override;`
- L188 _protected prototype_ `virtual void HandleListEntryDragCancelled(const FDragDropEvent& DropEvent) override;`
- L192 _protected prototype_ `virtual void OnRefreshDesignerItems() override;`
- L195 _protected prototype_ `virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L196 _protected prototype_ `virtual FMargin GetDesiredEntryPadding(UObject* Item) const override;`
- L198 _protected prototype_ `virtual void OnItemClickedInternal(UObject* Item) override;`
- L199 _protected prototype_ `virtual void OnItemDoubleClickedInternal(UObject* Item) override;`
- L200 _protected prototype_ `virtual void OnSelectionChangedInternal(UObject* FirstSelectedItem) override;`
- L201 _protected prototype_ `virtual void OnItemScrolledIntoViewInternal(UObject* Item, UUserWidget& EntryWidget) override;`
- L202 _protected prototype_ `virtual void OnListViewScrolledInternal(float ItemOffset, float DistanceRemaining) override;`
- L203 _protected prototype_ `virtual void OnListViewFinishedScrollingInternal() override;`
- L204 _protected prototype_ `virtual void OnListViewTouchStartInternal() override;`
- L205 _protected prototype_ `virtual void OnListViewTouchMoveInternal() override;`
- L206 _protected prototype_ `virtual void OnListViewTouchEndInternal() override;`
- L207 _protected prototype_ `virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;`
- L209 _protected prototype_ `void HandleOnEntryInitializedInternal(UObject* Item, const TSharedRef<ITableRow>& TableRow);`
- L213 _protected function_ `template <template<typename> class ListViewT = SListView> TSharedRef<ListViewT<UObject*>> ConstructListView()` — SListView construction helper - useful if using a custom STreeView subclass
- L239 _protected member_ `FTableViewStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView, meta = (DisplayName = "Style"))`
- L242 _protected member_ `FScrollBarStyle ScrollBarStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L245 _protected member_ `bool bEnableShadowBrush = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Enable Shadow Brush Style" ))`
- L248 _protected member_ `FScrollBoxStyle ShadowBrushStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Shadow Brush Style", EditCondition = bEnableShadowBrush, EditConditionHides ))`
- L256 _protected member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)` — The scroll & layout orientation of the list. ListView and TileView only. Vertical will scroll vertically and arrange tiles into rows. Horizontal will scroll horizontally and arrange tiles into columns.
- L259 _protected member_ `TEnumAsByte<ESelectionMode::Type> SelectionMode = ESelectionMode::Single;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L262 _protected member_ `EConsumeMouseWheel ConsumeMouseWheel = EConsumeMouseWheel::WhenScrollingPossible;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L265 _protected member_ `bool bClearSelectionOnClick = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L268 _protected member_ `bool bIsFocusable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L271 _protected member_ `bool bClearScrollVelocityOnSelection = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L274 _protected member_ `bool bReturnFocusToSelection = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)`
- L281 _protected member_ `bool bEnableProximateEntryNavigation = false;` — `UPROPERTY(Experimental, EditAnywhere, BlueprintReadOnly, Category = ListView)` — EXPERIMENTAL - Enables the ability to naturally navigate items within this listview, always preferring the closest focusable target. This also works with nested focus targets.
- L285 _protected member_ `EScrollIntoViewAlignment ScrollIntoViewAlignment = EScrollIntoViewAlignment::CenterAligned;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scrolling)` — Sets where to scroll a widget to when using explicit navigation
- L288 _protected member_ `TArray<TObjectPtr<UObject>> ListItems;` — `UPROPERTY(Transient)`
- L290 _protected member_ `TSharedPtr<SListView<UObject*>> MyListView;`
- L298 _protected member_ `float EntrySpacing = 0.f;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "EntrySpacing has been deprecated. Please use HorizontalEntrySpacing and VerticalEntrySpacing."), BlueprintReadOnly, BlueprintGetter = "GetHorizontalEntrySpacing", Category = ListView, meta = (ClampMin = 0))` — This deprecated property was originally BlueprintReadOnly. To satisfy the compiler requirment to have a BlueprintGetter for this property, it relies on the newly added UFunction GetHorizontalEntrySpacing() to act as its BlueprintGetter.
- L303 _private member_ `float HorizontalEntrySpacing = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = ListView, meta = (ClampMin = 0, AllowPrivateAccess = "true"))`
- L306 _private member_ `float VerticalEntrySpacing = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = ListView, meta = (ClampMin = 0, AllowPrivateAccess = "true"))`
- L309 _private member_ `FMargin ScrollBarPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = ListView, meta = (AllowPrivateAccess = "true", DisplayAfter="ScrollBarStyle"))`
- L315 _public function_ `float GetHorizontalEntrySpacing() const` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Get the horizontal spacing between entries.
- L319 _public function_ `float GetVerticalEntrySpacing() const` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Get the vertical spacing between entries.
- L323 _public function_ `FMargin GetScrollBarPadding() const` — `UFUNCTION(Category = ListView)` — Gets padding around the scrollbar.
- L327 _public prototype_ `void SetReturnFocusToSelection(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Set the return Focus to selection flag.
- L330 _public prototype_ `void SetVerticalEntrySpacing(float InVerticalEntrySpacing);` — Set the vertical spacing between entries.
- L333 _public prototype_ `void SetHorizontalEntrySpacing(float InHorizontalEntrySpacing);` — Set the horizontal spacing between entries.
- L336 _public prototype_ `void SetShadowBrushStyle(const FScrollBoxStyle& NewWidgetStyle);` — Sets the Shadow Brush Style when scrolling
- L339 _public prototype_ `const FScrollBoxStyle& GetShadowBrushStyle() const;` — Gets the Shadow Brush Style when scrolling
- L344 _protected prototype_ `void InitHorizontalEntrySpacing(float InHorizontalEntrySpacing);` — `UE_DEPRECATED(5.6, "InitHorizontalEntrySpacing is deprecated, please use SetHorizontalEntrySpacing instead.")`
- L347 _protected prototype_ `void InitVerticalEntrySpacing(float InVerticalEntrySpacing);` — `UE_DEPRECATED(5.6, "InitVerticalEntrySpacing is deprecated, please use SetVerticalEntrySpacing instead.")`
- L354 _private prototype_ `void BP_SetSelectedItem(UObject* Item);` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Set Selected Item"))` — Sets the given item as the sole selected item.
- L358 _private prototype_ `void BP_SetItemSelection(UObject* Item, bool bSelected);` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Set Item Selection"))` — Sets whether the given item is selected.
- L362 _private prototype_ `void BP_ClearSelection();` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Clear Selection"))` — Clear selection
- L366 _private prototype_ `int32 BP_GetNumItemsSelected() const;` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Get Num Items Selected"))` — Gets the number of items currently selected in the list
- L370 _private prototype_ `bool BP_GetSelectedItems(TArray<UObject*>& Items) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "GetSelectedItems"))` — Gets a list of all the currently selected items
- L374 _private prototype_ `bool BP_IsItemVisible(UObject* Item) const;` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Is Item Visible"))` — Gets whether the entry for the given object is currently visible in the list
- L378 _private prototype_ `void BP_NavigateToItem(UObject* Item);` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Navigate To Item"))` — Requests that the given item is navigated to, scrolling it into view if needed.
- L382 _private prototype_ `void BP_ScrollItemIntoView(UObject* Item);` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Scroll Item Into View"))` — Requests that the given item is scrolled into view
- L386 _private prototype_ `void BP_CancelScrollIntoView();` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Cancel Scroll Into View"))` — Cancels a previous request to scroll and item into view.
- L390 _private prototype_ `void BP_SetListItems(const TArray<UObject*>& InListItems);` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Set List Items", ViewmodelBlueprintWidgetExtension = "EntryViewModel"))` — Sets the array of objects to display rows for in the list
- L394 _private prototype_ `UObject* BP_GetSelectedItem() const;` — `UFUNCTION(BlueprintCallable, Category = ListView, meta = (DisplayName = "Get Selected Item", AllowPrivateAccess = true))` — Gets the first selected item, if any; recommended that you only use this for single selection lists.
- L399 _private member_ `FOnListEntryInitializedDynamic BP_OnEntryInitialized;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Entry Initialized"))` — Called when a row widget is generated for a list item
- L402 _private member_ `FSimpleListItemEventDynamic BP_OnItemClicked;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Clicked"))`
- L405 _private member_ `FSimpleListItemEventDynamic BP_OnItemDoubleClicked;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Double Clicked"))`
- L408 _private member_ `FOnItemGeometryMulticastDynamic BP_OnItemDragDetected;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Drag Detected"))`
- L411 _private member_ `FOnItemDragDropMulticastDynamic BP_OnItemDragEnter;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Drag Enter"))`
- L414 _private member_ `FOnItemDragDropMulticastDynamic BP_OnItemDragLeave;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Drag Leave"))`
- L417 _private member_ `FOnItemZoneMulticastDynamic BP_OnItemAcceptDrop;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Accept Drop"))`
- L420 _private member_ `FOnItemDragCancelledDynamic BP_OnItemDragCancelled;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Drag Cancelled"))`
- L423 _private member_ `FOnListViewDraggingStateChangedDynamic BP_OnListViewDraggingStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Dragging State Changed"))`
- L426 _private member_ `FOnItemIsHoveredChangedDynamic BP_OnItemIsHoveredChanged;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Is Hovered Changed"))`
- L429 _private member_ `FOnListItemSelectionChangedDynamic BP_OnItemSelectionChanged;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Selection Changed"))`
- L432 _private member_ `FOnListItemScrolledIntoViewDynamic BP_OnItemScrolledIntoView;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Scrolled Into View"))`
- L435 _private member_ `FOnListViewScrolledDynamic BP_OnListViewScrolled;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Scrolled"))`
- L438 _private member_ `FOnListViewFinishedScrollingDynamic BP_OnListViewFinishedScrolling;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Finished Scrolling"))`
- L441 _private member_ `FOnListViewTouchStartDynamic BP_OnListViewTouchStart;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Touch Start"))`
- L444 _private member_ `FOnListViewTouchMoveDynamic BP_OnListViewTouchMove;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Touch Move"))`
- L447 _private member_ `FOnListViewTouchEndDynamic BP_OnListViewTouchEnd;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On List View Touch End"))`
- L450 _private member_ `FOnIsItemSelectableOrNavigableDynamic BP_OnIsItemSelectableOrNavigable;` — `UPROPERTY(BlueprintReadWrite, Category = Events, meta = (AllowPrivateAccess, DisplayName = "On Is Item Selectable Or Navigable"))`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleListItemEventDynamic, UObject*, Item);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleListItemEventDynamic, UObject*, Item);`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListEntryInitializedDynamic, UObject*, Item, UUserWidget*, Widget);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListEntryInitializedDynamic, UObject*, Item, UUserWidget*, Widget);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListItemSelectionChangedDynamic, UObject*, Item, bool, bIsSelected);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListItemSelectionChangedDynamic, UObject*, Item, bool, bIsSelected);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemIsHoveredChangedDynamic, UObject*, Item, bool, bIsHovered);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemIsHoveredChangedDynamic, UObject*, Item, bool, bIsHovered);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListItemScrolledIntoViewDynamic, UObject*, Item, UUserWidget*, Widget);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListItemScrolledIntoViewDynamic, UObject*, Item, UUserWidget*, Widget);`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListViewScrolledDynamic, float, ItemOffset, float, DistanceRemaining);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListViewScrolledDynamic, float, ItemOffset, float, DistanceRemaining);`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewFinishedScrollingDynamic);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewFinishedScrollingDynamic);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchStartDynamic);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchStartDynamic);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchMoveDynamic);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchMoveDynamic);`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchEndDynamic);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnListViewTouchEndDynamic);`
- L23 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FOnIsItemSelectableOrNavigableDynamic, UObject*, Item);`
- L23 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FOnIsItemSelectableOrNavigableDynamic, UObject*, Item);`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDragDropMulticastDynamic, UObject*, Item, UDragDropOperation*, Operation);`
- L25 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDragDropMulticastDynamic, UObject*, Item, UDragDropOperation*, Operation);`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemGeometryMulticastDynamic, UObject*, Item, const FGeometry&, MyGeometry);`
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemGeometryMulticastDynamic, UObject*, Item, const FGeometry&, MyGeometry);`
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemZoneMulticastDynamic, UObject*, Item, EUMGItemDropZone, DropZone, UDragDropOperation*, Operation);`
- L27 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemZoneMulticastDynamic, UObject*, Item, EUMGItemDropZone, DropZone, UDragDropOperation*, Operation);`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDragCancelledDynamic, UDragDropOperation*, Operation);`
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDragCancelledDynamic, UDragDropOperation*, Operation);`
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListViewDraggingStateChangedDynamic, bool, bIsDragging);`
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListViewDraggingStateChangedDynamic, bool, bIsDragging);`

### `Source/Runtime/UMG/Public/Components/ListViewBase.h` (Public)


#### class `ITypedUMGListView`  
`template <typename ItemType> class ITypedUMGListView`  
_L39-562_
- desc: Mirrored SListView<T> API for easier interaction with a bound UListViewBase widget See declarations on SListView for more info on each function and event Note that, being a template class, this is not a UClass and therefore cannot be exposed to Blueprint. If you are using UObject* items, just use (or inherit from) UListView directly Otherwise, it is up to the child class to propagate events and/or expose functions to BP as needed Use the IMPLEMENT_TYPED_UMG_LIST() macro for the implementation boilerplate in your implementing class. @see UListView for an implementation example.
- L42 _public typedef_ `using NullableItemType = typename SListView<ItemType>::NullableItemType;`
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSimpleListItemEvent, ItemType);`
- L48 _public prototype_ `virtual FSimpleListItemEvent& OnItemClicked() const = 0;`
- L49 _public prototype_ `virtual FSimpleListItemEvent& OnItemDoubleClicked() const = 0;`
- L52 _public prototype_ `virtual FSimpleListItemEvent& OnItemDragDetected() const = 0;` — Drag and Drop
- L53 _public prototype_ `virtual FSimpleListItemEvent& OnItemAcceptDrop() const = 0;`
- L54 _public prototype_ `virtual FSimpleListItemEvent& OnItemDragEnter() const = 0;`
- L55 _public prototype_ `virtual FSimpleListItemEvent& OnItemDragLeave() const = 0;`
- L57 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragCancelled, const FDragDropEvent&);`
- L58 _public prototype_ `virtual FOnItemDragCancelled& OnItemDragCancelled() const = 0;`
- L60 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemCanAcceptDrop, ItemType, bool);`
- L61 _public prototype_ `virtual FOnItemCanAcceptDrop& OnItemCanAcceptDrop() const = 0;`
- L64 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemIsHoveredChanged, ItemType, bool);`
- L65 _public prototype_ `virtual FOnItemIsHoveredChanged& OnItemIsHoveredChanged() const = 0;`
- L67 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemSelectionChanged, NullableItemType);`
- L68 _public prototype_ `virtual FOnItemSelectionChanged& OnItemSelectionChanged() const = 0;`
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListViewScrolled, float, float);`
- L71 _public prototype_ `virtual FOnListViewScrolled& OnListViewScrolled() const = 0;`
- L73 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFinishedScrolling);`
- L74 _public prototype_ `virtual FOnFinishedScrolling& OnFinishedScrolling() const = 0;`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTouchStart);`
- L77 _public prototype_ `virtual FOnTouchStart& OnTouchStart() const = 0;`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTouchMove);`
- L80 _public prototype_ `virtual FOnTouchMove& OnTouchMove() const = 0;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTouchEnd);`
- L83 _public prototype_ `virtual FOnTouchEnd& OnTouchEnd() const = 0;`
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemScrolledIntoView, ItemType, UUserWidget&);`
- L86 _public prototype_ `virtual FOnItemScrolledIntoView& OnItemScrolledIntoView() const = 0;`
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemExpansionChanged, ItemType, bool);`
- L89 _public prototype_ `virtual FOnItemExpansionChanged& OnItemExpansionChanged() const = 0;`
- L91 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSubclassOf<UUserWidget>, FOnGetEntryClassForItem, ItemType);`
- L92 _public prototype_ `virtual FOnGetEntryClassForItem& OnGetEntryClassForItem() const = 0;`
- L94 _public prototype_ `virtual TSubclassOf<UUserWidget> GetDefaultEntryClass() const = 0;`
- L96 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsItemSelectableOrNavigable, ItemType);`
- L97 _public prototype_ `virtual FOnIsItemSelectableOrNavigable& OnIsItemSelectableOrNavigable() const = 0;`
- L100 _protected prototype_ `virtual SListView<ItemType>* GetMyListView() const = 0;`
- L101 _protected prototype_ `virtual uint32 GetOwningUserIndex() const = 0;`
- L102 _protected prototype_ `virtual bool IsDesignerPreview() const = 0;`
- L110 _public function_ `virtual TSubclassOf<UUserWidget> GetDesiredEntryClassForItem(ItemType Item) const` — Default behavior is to check the delegate, then fall back to the default if that fails. Feel free to override directly in child classes to determine the class yourself.
- L129 _public function_ `NullableItemType GetSelectedItem() const`
- L142 _public function_ `const TObjectPtrWrapTypeOf<ItemType>* ItemFromEntryWidget(const UUserWidget& EntryWidget) const`
- L157 _public function_ `template <typename RowWidgetT = UUserWidget> RowWidgetT* GetEntryWidgetFromItem(const ItemType& Item) const`
- L167 _public function_ `int32 GetIndexInList(const ItemType& Item) const`
- L179 _public function_ `int32 GetSelectedItems(TArray<ItemType>& OutSelectedItems) const`
- L185 _public function_ `int32 GetNumItemsSelected() const`
- L191 _public function_ `void SetSelectedItem(const ItemType& SoleSelectedItem, ESelectInfo::Type SelectInfo = ESelectInfo::Direct)`
- L199 _public function_ `void SetItemSelection(const ItemType& Item, bool bIsSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct)`
- L207 _public function_ `void ClearSelection()`
- L215 _public function_ `bool IsItemVisible(const ItemType& Item) const`
- L221 _public function_ `bool IsItemSelected(const ItemType& Item) const`
- L227 _public function_ `void RequestNavigateToItem(const ItemType& Item)`
- L235 _public function_ `void RequestScrollItemIntoView(const ItemType& Item)`
- L243 _public function_ `void CancelScrollIntoView()`
- L278 _protected function_ `template <template<typename> class ListViewT = SListView, typename UListViewBaseT> static TSharedRef<ListViewT<ItemType>> ConstructListView(UListViewBaseT* Implementer, const TArray<ItemType>& ListItems, const FListViewConstructArgs& Args = FListViewConstructArgs())`
- L329 _protected function_ `template <template<typename> class TileViewT = STileView, typename UListViewBaseT> static TSharedRef<TileViewT<ItemType>> ConstructTileView(UListViewBaseT* Implementer, const TArray<ItemType>& ListItems, const FTileViewConstructArgs& Args = FTileViewConstructArgs())`
- L377 _protected function_ `template <template<typename> class TreeViewT = STreeView, typename UListViewBaseT> static TSharedRef<TreeViewT<ItemType>> ConstructTreeView(UListViewBaseT* Implementer, const TArray<ItemType>& ListItems, const FTreeViewConstructArgs& Args = FTreeViewConstructArgs())`
- L413 _protected function_ `template <template<typename> class ObjectRowT = SObjectTableRow> TSharedPtr<ObjectRowT<ItemType>> GetObjectRowFromItem(const ItemType& Item) const` — Gets the SObjectTableRow underlying the UMG EntryWidget that represents the given item (if one exists)
- L429 _protected prototype_ `virtual UUserWidget& OnGenerateEntryWidgetInternal(ItemType Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) = 0;` — Generates the actual entry widget that represents the given item. Expected to be used in concert with UListViewBase::GenerateTypedEntry().
- L432 _protected function_ `virtual FMargin GetDesiredEntryPadding(ItemType Item) const` — Gets the desired padding for the entry representing the given item
- L435 _protected function_ `virtual void OnGetChildrenInternal(ItemType Item, TArray<ItemType>& OutChildren) const` — TreeViews only. Gets the items to consider children of the given item when generating child entries.
- L438 _protected function_ `virtual void OnItemClickedInternal(ItemType Item)` — ListView events - implement these instead of binding handlers directly to a list
- L439 _protected function_ `virtual void OnItemDoubleClickedInternal(ItemType Item)`
- L440 _protected function_ `virtual void OnSelectionChangedInternal(NullableItemType FirstSelectedItem)`
- L441 _protected function_ `virtual bool OnIsSelectableOrNavigableInternal(ItemType FirstSelectedItem)`
- L442 _protected function_ `virtual void OnItemScrolledIntoViewInternal(ItemType Item, UUserWidget& EntryWidget)`
- L443 _protected function_ `virtual void OnListViewScrolledInternal(float ItemOffset, float DistanceRemaining)`
- L444 _protected function_ `virtual void OnListViewFinishedScrollingInternal()`
- L445 _protected function_ `virtual void OnListViewTouchStartInternal()`
- L446 _protected function_ `virtual void OnListViewTouchMoveInternal()`
- L447 _protected function_ `virtual void OnListViewTouchEndInternal()`
- L448 _protected function_ `virtual void OnItemExpansionChangedInternal(ItemType Item, bool bIsExpanded)`
- L451 _private function_ `TSharedRef<ITableRow> HandleGenerateRow(ItemType Item, const TSharedRef<STableViewBase>& OwnerTable)`
- L466 _private function_ `void HandleRefreshRow(ItemType Item)`
- L476 _private function_ `void HandleItemClicked(ItemType Item)`
- L482 _private function_ `void HandleItemDoubleClicked(ItemType Item)`
- L488 _private function_ `void HandleSelectionChanged(NullableItemType Item, ESelectInfo::Type SelectInfo)`
- L496 _private function_ `bool HandleIsSelectableOrNavigable(ItemType Item)`
- L501 _private function_ `void HandleListViewScrolled(double OffsetInItems)`
- L511 _private function_ `void HandleFinishedScrolling()`
- L517 _private function_ `void HandleTouchStart()`
- L523 _private function_ `void HandleTouchMove()`
- L529 _private function_ `void HandleTouchEnd()`
- L535 _private function_ `void HandleItemScrolledIntoView(ItemType Item, const TSharedPtr<ITableRow>& InWidget)`
- L545 _private function_ `void HandleExpansionChanged(ItemType Item, bool bIsExpanded)`
- L558 _private function_ `void HandleGetChildren(ItemType Item, TArray<ItemType>& OutChildren) const`

#### struct `ITypedUMGListView::FListViewConstructArgs`  
`struct FListViewConstructArgs`  
_L258-275_
- L260 _public member_ `bool bAllowFocus = true;`
- L261 _public member_ `ESelectionMode::Type SelectionMode = ESelectionMode::Single;`
- L262 _public member_ `bool bClearSelectionOnClick = false;`
- L263 _public member_ `EConsumeMouseWheel ConsumeMouseWheel = EConsumeMouseWheel::WhenScrollingPossible;`
- L264 _public member_ `bool bReturnFocusToSelection = false;`
- L265 _public member_ `bool bEnableProximateEntryNavigation = false;`
- L266 _public member_ `bool bClearScrollVelocityOnSelection = true;`
- L267 _public member_ `EOrientation Orientation = Orient_Vertical;`
- L268 _public member_ `EScrollIntoViewAlignment ScrollIntoViewAlignment = EScrollIntoViewAlignment::CenterAligned;`
- L269 _public member_ `const FTableViewStyle* ListViewStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FTableViewStyle>("Lis`
- L270 _public member_ `const FScrollBarStyle* ScrollBarStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("Scr`
- L271 _public member_ `const FScrollBoxStyle* ShadowBoxStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("Scr`
- L272 _public member_ `bool bEnableShadowBoxStyle = false;`
- L273 _public member_ `FMargin ScrollBarPadding = FMargin(0.0f);`
- L274 _public member_ `bool bPreventThrottling = false;`

#### struct `ITypedUMGListView::FTileViewConstructArgs`  
`struct FTileViewConstructArgs : public FListViewConstructArgs`  
_L318-326_
- inherits: `FListViewConstructArgs`
- L320 _public member_ `EListItemAlignment TileAlignment = EListItemAlignment::EvenlyDistributed;`
- L321 _public member_ `TAttribute<float> EntryHeight;`
- L322 _public member_ `TAttribute<float> EntryWidth;`
- L323 _public member_ `bool bWrapDirectionalNavigation = false;`
- L324 _public member_ `const FScrollBarStyle* ScrollBarStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("Scr`
- L325 _public member_ `EVisibility ScrollbarDisabledVisibility = EVisibility::Collapsed;`

#### struct `ITypedUMGListView::FTreeViewConstructArgs`  
`struct FTreeViewConstructArgs`  
_L366-374_
- L368 _public member_ `ESelectionMode::Type SelectionMode = ESelectionMode::Single;`
- L369 _public member_ `bool bClearSelectionOnClick = false;`
- L370 _public member_ `EConsumeMouseWheel ConsumeMouseWheel = EConsumeMouseWheel::WhenScrollingPossible;`
- L371 _public member_ `bool bReturnFocusToSelection = false;`
- L372 _public member_ `const FTableViewStyle* TreeViewStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FTableViewStyle>("Tre`
- L373 _public member_ `const FScrollBarStyle* ScrollBarStyle = &FUMGCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("Scr`

#### class `UListViewBase`  
`class UListViewBase : public UWidget`  
_L587-936_
- reflection: `UCLASS(Abstract, NotBlueprintable, hidedropdown, meta = (EntryInterface = UserListEntry), MinimalAPI)`
- inherits: `UWidget`
- desc: Bare-bones base class to make creating custom UListView widgets easier. Child classes should also inherit from ITypedUMGListView<T> to get a basic public ListView API for free. Child classes will own the actual SListView<T> widgets, but this provides some boilerplate functionality for generating entries. To generate a row for the child list, use GenerateTypedRow with the appropriate SObjectTableRow<T> type for your list Additionally, the entry widget class can be filtered for a particular class and interface with the EntryClass and EntryInterface metadata arguments This can be specified either on the class directly (see below) or on any BindWidget FProperty Example: class UMyUserWidget : public UUserWidget { UPROPERTY(BindWidget, meta = (EntryClass = MyListEntryWidget)) UListView* ListView_InventoryItems; }
- L592 _public prototype_ `UListViewBase(const FObjectInitializer& ObjectInitializer);`
- L595 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L596 _public prototype_ `virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;`
- L599 _public function_ `TSubclassOf<UUserWidget> GetEntryWidgetClass() const`
- L603 _public prototype_ `const TArray<UUserWidget*>& GetDisplayedEntryWidgets() const;` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Gets all of the list entry widgets currently being displayed by the list
- L607 _public prototype_ `float GetScrollOffset() const;` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Get the scroll offset of this view (in items)
- L610 _public function_ `virtual UObject* GetListObjectFromEntry(UUserWidget& EntryWidget)` — Get the corresponding list object for this userwidget entry. Override this to call ITypedUMGListView::ItemFromEntryWidget in concrete widgets.
- L614 _public function_ `bool GetIsDraggingListItem() const` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Gets whether or not a drag operation is in progress.
- L621 _public prototype_ `void RegenerateAllEntries();` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Full regeneration of all entries in the list. Note that the entry UWidget instances will not be destroyed, but they will be released and re-generated. In other words, entry widgets will not receive Destruct/Construct events. They will receive OnEntryReleased and IUserObjectListEntry implementations will receive OnListItemObjectSet.
- L625 _public prototype_ `void ScrollToTop();` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Scroll the entire list up to the first item
- L629 _public prototype_ `void ScrollToBottom();` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Scroll the entire list down to the bottom-most item
- L633 _public prototype_ `void SetScrollOffset(const float InScrollOffset);` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Set the scroll offset of this view (in items)
- L637 _public prototype_ `void EndInertialScrolling();` — `UFUNCTION(BlueprintCallable, Category = ListView)` — Stops the scroll inertia
- L640 _public prototype_ `void SetWheelScrollMultiplier(float NewWheelScrollMultiplier);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)`
- L643 _public prototype_ `void SetScrollbarVisibility(ESlateVisibility InVisibility);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)`
- L646 _public prototype_ `ESlateVisibility GetScrollbarVisibility() const;` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)`
- L649 _public prototype_ `void SetAllowOverScroll(bool NewAllowOverscroll);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)`
- L652 _public function_ `float GetOverscroll() const` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)`
- L656 _public prototype_ `void SetIsPointerScrollingEnabled(bool bInIsPointerScrollingEnabled);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Enable/Disable the ability of the list to scroll. This should be use as a temporary disable.
- L660 _public prototype_ `void SetIsTouchScrollingEnabled(bool bInIsTouchScrollingEnabled);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Enables/Disable touch scrolling
- L664 _public prototype_ `void SetIsGamepadScrollingEnabled(bool bInIsGamepadScrollingEnabled);` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Enable/Disable the ability of the list to scroll via gamepad.
- L668 _public prototype_ `void CancelListViewDragDrop();` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Cancels the drag drop operation if one is in progress
- L672 _public prototype_ `UDragDropOperation* CreateDragDropOperation(UObject* Item);` — `UFUNCTION(Category = ListViewBase)` — Creates the drag drop operation for the list view.
- L684 _public prototype_ `void RequestRefresh();` — `UFUNCTION(BlueprintCallable, Category = ListViewBase)` — Sets the list to refresh on the next tick. Note that refreshing, from a list perspective, is limited to accounting for discrepancies between items and entries. In other words, it will only release entries that no longer have items and generate entries for new items (or newly visible items). It does NOT account for changes within existing items - that is up to the item to announce and an entry to listen to as needed. This can be onerous to set up for simple cases, so it's also reasonable (though not ideal) to call RegenerateAllEntries when changes within N list items need to be reflected.
- L686 _public prototype_ `DECLARE_EVENT_OneParam(UListView, FOnListEntryGenerated, UUserWidget&);`
- L687 _public function_ `FOnListEntryGenerated& OnEntryWidgetGenerated()`
- L689 _public prototype_ `DECLARE_EVENT_OneParam(UListView, FOnEntryWidgetReleased, UUserWidget&);`
- L690 _public function_ `FOnEntryWidgetReleased& OnEntryWidgetReleased()`
- L693 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override final;`
- L694 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L695 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L698 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget();` — Implement in child classes to construct the actual ListView Slate widget
- L701 _protected function_ `virtual void HandleListEntryHovered(UUserWidget& EntryWidget)` — @todo DanH: Should probably have the events for native & BP built in up here - need to update existing binds to UListView's version
- L702 _protected function_ `virtual void HandleListEntryUnhovered(UUserWidget& EntryWidget)`
- L703 _protected function_ `virtual UDragDropOperation* HandleListEntryDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent, UUserWidget& EntryWidget)`
- L704 _protected function_ `virtual TOptional<EItemDropZone> HandleListEntryCanAcceptDrop(const FDragDropEvent& DropEvent, EItemDropZone DropZone, UUserWidget& EntryWidget)`
- L705 _protected function_ `virtual FReply HandleListEntryAcceptDrop(const FDragDropEvent& DropEvent, EItemDropZone DropZone, UUserWidget& EntryWidget)`
- L706 _protected function_ `virtual void HandleListEntryDragEnter(const FDragDropEvent& DropEvent, UUserWidget& EntryWidget)`
- L707 _protected function_ `virtual void HandleListEntryDragLeave(const FDragDropEvent& DropEvent, UUserWidget& EntryWidget)`
- L708 _protected function_ `virtual void HandleListEntryDragCancelled(const FDragDropEvent& DropEvent)`
- L710 _protected prototype_ `virtual void FinishGeneratingEntry(UUserWidget& GeneratedEntry);`
- L714 _protected member_ `FOnListEntryGeneratedDynamic BP_OnEntryGenerated;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Entry Generated"))` — Called when a row widget is generated for a list item
- L715 _protected function_ `virtual void NativeOnEntryGenerated(UUserWidget* EntryWidget)`
- L719 _protected member_ `FOnListEntriesGeneratedDynamic BP_OnEntriesGenerated;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Entries Generated"))` — Called when all row widgets are generated for all list items
- L720 _protected function_ `virtual void NativeOnEntriesGenerated()`
- L727 _protected member_ `TArray<TWeakObjectPtr<UUserWidget>> GeneratedEntriesToAnnounce;` — Normally these are processed by UListViewBase::FinishGeneratingEntry which uses World->GetTimerManager() to generate entries next frame However when for example using a listview in editor utility widgets a world there is not reliable and an alternative is to use FTSTicker::GetCoreTicker()
- L737 _protected function_ ``
- L769 _protected function_ `virtual void OnRefreshDesignerItems()` — Called during design time to allow lists to generate preview entries via dummy data. Since that data could be of any type, the child has to be the one to generate them. Expected to call RefreshDesignerItems<T> with the appropriate T for your underlying list @see UListView::OnRefreshDesignerItems for a usage example
- L776 _protected function_ `template <typename PlaceholderItemT> void RefreshDesignerItems(TArray<PlaceholderItemT>& ListItems, TFunctionRef<PlaceholderItemT()> CreateItemFunc)` — Helper intended to be called by overrides of OnRefreshDesignerItems. @see UListView::OnRefreshDesignerItems for a usage example
- L811 _protected prototype_ `void HandleRowReleased(const TSharedRef<ITableRow>& Row);` — Expected to be bound to the actual ListView widget created by a child class (automatically taken care of via the construction helpers within ITypedUMGListView)
- L816 _protected member_ `TSubclassOf<UUserWidget> EntryWidgetClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListEntries, meta = (DesignerRebuild, AllowPrivateAccess = true, MustImplement = "/Script/UMG.UserListEntry"))` — The type of widget to create for each entry displayed in the list.
- L820 _protected member_ `float WheelScrollMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scrolling)` — The multiplier to apply when wheel scrolling
- L824 _protected member_ `bool bEnableScrollAnimation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scrolling)` — True to enable lerped animation when scrolling through the list
- L828 _protected member_ `float ScrollingAnimationInterpolationSpeed = 12.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scrolling)` — The speed to apply when lerping in the scroll animation.
- L832 _protected member_ `bool bInEnableTouchAnimatedScrolling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scrolling, DisplayName = "Enable Touch Animated Scrolling")` — True to enable lerped animation when scrolling through the list with touch
- L836 _protected member_ `bool AllowOverscroll = true;` — `UPROPERTY(EditAnywhere, Category = Scrolling)` — Disable to stop scrollbars from activating inertial overscrolling
- L840 _protected member_ `bool bEnableRightClickScrolling = true;` — `UPROPERTY(EditAnywhere, Category = Scrolling)` — True to allow right click drag scrolling.
- L844 _protected member_ `bool bEnableTouchScrolling = true;` — `UPROPERTY(EditAnywhere, Category = Scrolling)` — True to allow scrolling using touch input.
- L848 _protected member_ `bool bIsPointerScrollingEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = Scrolling)` — Enable/Disable scrolling using Touch or Mouse.
- L852 _protected member_ `bool bIsGamepadScrollingEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = Scrolling)` — Enable/Disable scrolling using Gamepad.
- L855 _protected member_ `bool bEnableFixedLineOffset = false;` — `UPROPERTY(EditAnywhere, Category = Scrolling)`
- L863 _protected member_ `float FixedLineScrollOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = Scrolling, meta = (EditCondition = bEnableFixedLineOffset, ClampMin = 0.0f, ClampMax = 0.5f))` — Optional fixed offset (in lines) to always apply to the top/left (depending on orientation) of the list. If provided, all non-inertial means of scrolling will settle with exactly this offset of the topmost entry. Ex: A value of 0.25 would cause the topmost full entry to be offset down by a quarter length of the preceeding entry.
- L867 _protected member_ `bool bAllowDragging = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scrolling")` — True to allow dragging of row widgets in the list
- L871 _protected member_ `bool bAllowDragDrop = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag and Drop")` — Allow drag and drop operations to be performed on the list.
- L878 _protected member_ `EDragPivot DragDropVisualPivot = EDragPivot::CenterCenter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop")` — Controls where the drag widget visual will appear when dragged relative to the pointer performing the drag operation.
- L882 _protected member_ `FVector2D DragDropVisualOffset = FVector2D(0,0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop")` — A percentage offset (-1..+1) from the Pivot location, the percentage is of the desired size of the dragged visual.
- L886 _protected member_ `TSubclassOf<UUserWidget> DragDropVisualEntryClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag and Drop", meta = (AllowPrivateAccess = true, MustImplement = "/Script/UMG.UserListEntry"))` — The class which will be used to generate the drag drop visual.  If none is specified, the EntryWidgetClass will be used.
- L890 _protected member_ `TSubclassOf<UDragDropOperation> DragDropOperationClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag and Drop", meta = (AllowPrivateAccess = true))` — The drag drop operation class for this listview - if this is not specified, drag drop operations will not be created.
- L894 _protected member_ `TObjectPtr<class UWidget> DragVisualWidget = nullptr;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = "Drag and Drop")` — This is the actual drag visual widget that will be used by the drag drop operation.This can be set in blueprint via override of CreateDragDropOperation(should call parent)
- L898 _protected member_ `bool bIsDragging = false;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Drag and Drop")` — This indicates whether the ListViewBase is currently in a dragging state
- L902 _protected member_ `bool bSelectItemOnNavigation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)` — If true, items will be "selected" (in addition to focused) when navigating to them. If false, they will only be focused.
- L906 _protected member_ `bool bAllowKeepPreselectedItems = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListView)` — If true, when selecting an item via mouse button, we allow pre-selected items to remain selected (applicable to "Multi" Selection Mode only).
- L910 _protected member_ `FOnListEntryReleasedDynamic BP_OnEntryReleased;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Entry Released"))` — Called when a row widget is released by the list (i.e. when it no longer represents a list item)
- L911 _protected function_ `virtual void NativeOnEntryReleased(UUserWidget* EntryWidget)`
- L915 _private prototype_ `virtual void HandleAnnounceGeneratedEntries();`
- L918 _private member_ `bool bNeedsToCallRefreshDesignerItems = false;`
- L922 _private member_ `int32 NumDesignerPreviewEntries = 5;` — `UPROPERTY(EditAnywhere, Category = ListEntries, meta = (ClampMin = 0, ClampMax = 20))` — The number of dummy item entry widgets to preview in the widget designer
- L926 _private member_ `FUserWidgetPool EntryWidgetPool;` — `UPROPERTY(Transient)`
- L928 _private member_ `FTSTicker::FDelegateHandle EntryGenAnnouncementDelegateHandle;`
- L930 _private member_ `FOnListEntryGenerated OnListEntryGeneratedEvent;`
- L931 _private member_ `FOnEntryWidgetReleased OnEntryWidgetReleasedEvent;`
- L933 _private member_ `TSharedPtr<STableViewBase> MyTableViewBase;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntryGeneratedDynamic, UUserWidget*, Widget);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntryGeneratedDynamic, UUserWidget*, Widget);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntryReleasedDynamic, UUserWidget*, Widget);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntryReleasedDynamic, UUserWidget*, Widget);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntriesGeneratedDynamic, int32, NumEntries);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListEntriesGeneratedDynamic, int32, NumEntries);`
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSimpleListItemEvent, ItemType);`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragCancelled, const FDragDropEvent&);`
- L60 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemCanAcceptDrop, ItemType, bool);`
- L64 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemIsHoveredChanged, ItemType, bool);`
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemSelectionChanged, NullableItemType);`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListViewScrolled, float, float);`
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFinishedScrolling);`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTouchStart);`
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTouchMove);`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTouchEnd);`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemScrolledIntoView, ItemType, UUserWidget&);`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemExpansionChanged, ItemType, bool);`
- L91 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSubclassOf<UUserWidget>, FOnGetEntryClassForItem, ItemType);`
- L96 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsItemSelectableOrNavigable, ItemType);`
- L686 _delegate_ `DECLARE_EVENT_OneParam(UListView, FOnListEntryGenerated, UUserWidget&);`
- L689 _delegate_ `DECLARE_EVENT_OneParam(UListView, FOnEntryWidgetReleased, UUserWidget&);`
- L939 _macro_ `#define IMPLEMENT_TYPED_UMG_LIST(ItemType, ListPropertyName) \`

### `Source/Runtime/UMG/Public/Components/MenuAnchor.h` (Public)


#### class `UMenuAnchor`  
`class UMenuAnchor : public UContentWidget`  
_L23-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: The Menu Anchor allows you to specify an location that a popup menu should be anchored to, and should be summoned from. * Single Child * Popup
- L29 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(UUserWidget*, FGetUserWidget);`
- L37 _public member_ `TSubclassOf<class UUserWidget> MenuClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Menu Anchor")` — The widget class to spawn when the menu is required.  Creates the widget freshly each time. If you want to customize the creation of the popup, you should bind a function to OnGetMenuContentEvent instead.
- L42 _public member_ `FGetWidget OnGetMenuContentEvent;` — `UE_DEPRECATED(4.26, "Use OnGetUserMenuContentEvent instead, you may need to make the previous binding return an User Widget.")` — `UPROPERTY(EditAnywhere, Category = "Events", meta = (DeprecationMessage = "4.26. Use OnGetUserMenuContentEvent instead, you may need to make the previous binding return an User Widget."))` — Deprecated. Called when the menu content is requested to allow a more customized handling over what to display
- L46 _public member_ `FGetUserWidget OnGetUserMenuContentEvent;` — `UPROPERTY(EditAnywhere, Category="Events")` — Called when the menu content is requested to allow a more customized handling over what to display
- L51 _public member_ `TEnumAsByte<EMenuPlacement> Placement;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, BlueprintSetter = "SetPlacement", Category = "Menu Anchor")` — The placement location of the summoned widget.
- L56 _public member_ `bool bFitInWindow;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = "FitInWindow", Getter = "IsFitInWindow", BlueprintSetter = "FitInWindow", Category = "Menu Anchor", meta = (ScriptName = "ShouldFitInWindow"))` — Should the menu anchor attempt to fit the menu inside the window.
- L60 _public member_ `bool ShouldDeferPaintingAfterWindowContent;` — `UE_DEPRECATED(5.2, "Direct access to ShouldDeferPaintingAfterWindowContent is deprecated. Please use the getter.")` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsDeferPaintingAfterWindowContent", AdvancedDisplay, Category = "Menu Anchor")`
- L65 _public member_ `bool UseApplicationMenuStack;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsUseApplicationMenuStack", AdvancedDisplay, Category = "Menu Anchor")` — Does this menu behave like a normal stacked menu? Set it to false to control the menu's lifetime yourself.
- L69 _public member_ `bool ShowMenuBackground;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsShowMenuBackground", AdvancedDisplay, Category = "Menu Anchor", meta = (EditCondition = "UseApplicationMenuStack", EditConditionHides, AllowPrivateAccess = "true", DisplayAfter = "UseApplicationMenuStack"))` — For menus using the application menu stack, should the window background be visible?
- L74 _public member_ `FOnMenuOpenChangedEvent OnMenuOpenChanged;` — `UPROPERTY(BlueprintAssignable, Category="Menu Anchor|Event")` — Called when the opened state of the menu changes
- L80 _public prototype_ `void SetPlacement(EMenuPlacement InPlacement);` — `UFUNCTION(BlueprintCallable, Category = "Menu Anchor")`
- L82 _public prototype_ `EMenuPlacement GetPlacement() const;`
- L85 _public prototype_ `void FitInWindow(bool bFit);` — `UFUNCTION(BlueprintCallable, Category = "Menu Anchor")`
- L87 _public prototype_ `bool IsFitInWindow() const;`
- L89 _public prototype_ `bool IsDeferPaintingAfterWindowContent() const;`
- L91 _public prototype_ `bool IsUseApplicationMenuStack() const;`
- L93 _public prototype_ `bool IsShowMenuBackground() const;`
- L103 _public prototype_ `void ToggleOpen(bool bFocusOnOpen);` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Toggles the menus open state. @param bFocusOnOpen  Should we focus the popup as soon as it opens?
- L107 _public prototype_ `void Open(bool bFocusMenu);` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Opens the menu if it is not already open
- L111 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Closes the menu if it is currently open.
- L115 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Returns true if the popup is open; false otherwise.
- L123 _public prototype_ `bool ShouldOpenDueToClick() const;` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Returns true if we should open the menu due to a click. Sometimes we should not, if the same MouseDownEvent that just closed the menu is about to re-open it because it happens to land on the button.
- L127 _public prototype_ `FVector2D GetMenuPosition() const;` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Returns the current menu position
- L131 _public prototype_ `bool HasOpenSubMenus() const;` — `UFUNCTION(BlueprintCallable, Category="Menu Anchor")` — Returns whether this menu has open submenus
- L133 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L136 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L142 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;` — UPanelWidget
- L143 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L147 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L151 _protected prototype_ `void InitShouldDeferPaintingAfterWindowContent(bool InShouldDeferPaintingAfterWindowContent);` — Initialize ShouldDeferPaintingAfterWindowContent in the constructor before the SWidget is constructed.
- L154 _protected prototype_ `void InitUseApplicationMenuStack(bool InUseApplicationMenuStack);` — Initialize UseApplicationMenuStack in the constructor before the SWidget is constructed.
- L157 _protected prototype_ `void InitShowMenuBackground(bool InShowMenuBackground);` — Initialize ShowMenuBackground in the constructor before the SWidget is constructed.
- L160 _protected prototype_ `TSharedRef<SWidget> HandleGetMenuContent();`
- L161 _protected prototype_ `void HandleMenuOpenChanged(bool bIsOpen);`
- L164 _protected member_ `TSharedPtr<SMenuAnchor> MyMenuAnchor;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuOpenChangedEvent, bool, bIsOpen);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuOpenChangedEvent, bool, bIsOpen);`
- L29 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(UUserWidget*, FGetUserWidget);`

### `Source/Runtime/UMG/Public/Components/MouseHoverComponent.h` (Public)


#### class `UMouseHoverComponent`  
`class UMouseHoverComponent : public UUIComponent`  
_L13-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUIComponent`
- desc: This is a class for a Component that exposes the mouse hover state of its Owner widget.
- L19 _public function_ `bool GetIsHovered() const`
- L21 _public prototype_ `void OnMouseHoverChanged(bool InbIsHovered);`
- L26 _private member_ `bool bIsHovered = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter = "GetIsHovered", FieldNotify, Category = "Mouse Hover State", meta = (AllowPrivateAccess))`
- L28 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidgetWithContent(const TSharedRef<SWidget> OwnerContent) override;`

### `Source/Runtime/UMG/Public/Components/MultiLineEditableText.h` (Public)


#### class `UMultiLineEditableText`  
`class UMultiLineEditableText : public UTextLayoutWidget`  
_L21-207_
- reflection: `UCLASS(meta=( DisplayName="Editable Text (Multi-Line)" ), MinimalAPI)`
- inherits: `UTextLayoutWidget`
- desc: Editable text box widget
- L27 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultiLineEditableTextChangedEvent, const FText&, Text);`
- L28 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMultiLineEditableTextCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`
- L34 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetText", BlueprintSetter = "SetText", FieldNotify, Category = Content, meta = (MultiLine = "true"))` — The text content for this editable text box widget
- L39 _public member_ `FText HintText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetHintText", BlueprintSetter = "SetHintText", Category = Content, meta = (MultiLine = "true"))` — Hint text that appears when there is no text in the text box
- L43 _public member_ `FGetText HintTextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the hint text of the widget
- L48 _public member_ `FTextBlockStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetWidgetStyle, Category="Style", meta=(ShowOnlyInnerProperties))` — The style
- L53 _public member_ `bool bIsReadOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = GetIsReadOnly, Setter = SetIsReadOnly, BlueprintSetter = "SetIsReadOnly", Category = Appearance)` — Sets the Text as Readonly to prevent it from being modified interactively by the user
- L58 _public member_ `bool SelectAllTextWhenFocused;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to select all text when the user clicks to give focus on the widget
- L63 _public member_ `bool ClearTextSelectionOnFocusLoss;` — `UPROPERTY(EditAnywhere, Category = Behavior, AdvancedDisplay)` — Whether to clear text selection when focus is lost
- L68 _public member_ `bool RevertTextOnEscape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to allow the user to back out of changes when they press the escape key
- L73 _public member_ `bool ClearKeyboardFocusOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Behavior, AdvancedDisplay)` — Whether to clear keyboard focus when pressing enter to commit changes
- L77 _public member_ `bool AllowContextMenu;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Whether the context menu can be opened
- L81 _public member_ `FVirtualKeyboardOptions VirtualKeyboardOptions;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Additional options for the virtual keyboard
- L85 _public member_ `EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — What action should be taken when the virtual keyboard is dismissed?
- L89 _public member_ `FOnMultiLineEditableTextChangedEvent OnTextChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextChanged (Multi-Line Editable Text)"))` — Called whenever the text is changed programmatically or interactively by the user
- L93 _public member_ `FOnMultiLineEditableTextCommittedEvent OnTextCommitted;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextCommitted (Multi-Line Editable Text)"))` — Called whenever the text is committed.  This happens when the user presses enter or the text box loses focus.
- L102 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="GetText (Multi-Line Editable Text)"))` — Gets the widget text @return The widget text
- L109 _public prototype_ `void SetText(FText InText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetText (Multi-Line Editable Text)"))` — Directly sets the widget text. @param InText The text to assign to the widget
- L113 _public prototype_ `FText GetHintText() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="GetHintText (Multi-Line Editable Text)"))` — Returns the Hint text that appears when there is no text in the text box
- L120 _public prototype_ `void SetHintText(FText InHintText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetHintText (Multi-Line Editable Text)"))` — Sets the Hint text that appears when there is no text in the text box @param InHintText The text that appears when there is no text in the text box
- L123 _public prototype_ `void SetSelectAllTextWhenFocused(bool bSelectAllTextWhenFocused);` — Set to true to select all text when the user clicks to give focus on the widget
- L126 _public prototype_ `bool GetSelectAllTextWhenFocused() const;` — Whether to select all text when the user clicks to give focus on the widget
- L129 _public prototype_ `void SetClearTextSelectionOnFocusLoss(bool bClearTextSelectionOnFocusLoss);` — Set to true to clear text selection when focus is lost
- L132 _public prototype_ `bool GetClearTextSelectionOnFocusLoss() const;` — Whether to clear text selection when focus is lost
- L135 _public prototype_ `void SetRevertTextOnEscape(bool bRevertTextOnEscape);` — Set to true to allow the user to back out of changes when they press the escape key
- L138 _public prototype_ `bool GetRevertTextOnEscape() const;` — Whether to allow the user to back out of changes when they press the escape key
- L141 _public prototype_ `void SetClearKeyboardFocusOnCommit(bool bClearKeyboardFocusOnCommit);` — Set to true to clear keyboard focus when pressing enter to commit changes
- L144 _public prototype_ `bool GetClearKeyboardFocusOnCommit() const;` — Whether to clear keyboard focus when pressing enter to commit changes
- L147 _public prototype_ `bool GetIsReadOnly() const;` — Return true when this text cannot be modified interactively by the user
- L151 _public prototype_ `void SetIsReadOnly(bool bReadOnly);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetIsReadOnly (Multi-Line Editable Text"))` — Sets the Text as Readonly to prevent it from being modified interactively by the user
- L154 _public prototype_ `void SetWidgetStyle(const FTextBlockStyle& InWidgetStyle);` — `UFUNCTION(BlueprintSetter)`
- L157 _public prototype_ `const FSlateFontInfo& GetFont() const;` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L160 _public prototype_ `void SetFont(FSlateFontInfo InFontInfo);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L163 _public prototype_ `void SetFontMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L166 _public prototype_ `void SetFontOutlineMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L169 _public prototype_ `virtual void SynchronizeProperties() override;`
- L173 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L177 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L182 _protected prototype_ `virtual void OnShapedTextOptionsChanged(FShapedTextOptions InShapedTextOptions) override;`
- L183 _protected prototype_ `virtual void OnJustificationChanged(ETextJustify::Type InJustification) override;`
- L184 _protected prototype_ `virtual void OnWrappingPolicyChanged(ETextWrappingPolicy InWrappingPolicy) override;`
- L185 _protected prototype_ `virtual void OnAutoWrapTextChanged(bool InAutoWrapText) override;`
- L186 _protected prototype_ `virtual void OnWrapTextAtChanged(float InWrapTextAt) override;`
- L187 _protected prototype_ `virtual void OnLineHeightPercentageChanged(float InLineHeightPercentage) override;`
- L188 _protected prototype_ `virtual void OnApplyLineHeightToBottomLineChanged(bool InApplyLineHeightToBottomLine) override;`
- L189 _protected prototype_ `virtual void OnMarginChanged(const FMargin& InMargin) override;`
- L193 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L196 _protected prototype_ `void HandleOnTextChanged(const FText& Text);`
- L197 _protected prototype_ `void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);`
- L200 _protected member_ `TSharedPtr<SMultiLineEditableText> MyMultiLineEditableText;`
- L202 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, HintText);`
- L206 _private prototype_ `bool SetTextInternal(const FText& InText);` — @return true if the text was changed, or false if identical.

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultiLineEditableTextChangedEvent, const FText&, Text);`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMultiLineEditableTextCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`

### `Source/Runtime/UMG/Public/Components/MultiLineEditableTextBox.h` (Public)


#### class `UMultiLineEditableTextBox`  
`class UMultiLineEditableTextBox : public UTextLayoutWidget`  
_L21-180_
- reflection: `UCLASS(meta=(DisplayName="Text Box (Multi-Line)"), MinimalAPI)`
- inherits: `UTextLayoutWidget`
- desc: Allows a user to enter multiple lines of text
- L27 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultiLineEditableTextBoxChangedEvent, const FText&, Text);`
- L28 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMultiLineEditableTextBoxCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`
- L35 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetText", BlueprintSetter = "SetText", FieldNotify, Category = Content, meta=(MultiLine="true"))` — The text content for this editable text box widget
- L40 _public member_ `FText HintText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter = "GetHintText", BlueprintSetter = "SetHintText", Category = Content, meta = (MultiLine = "true"))` — Hint text that appears when there is no text in the text box
- L44 _public member_ `FGetText HintTextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the hint text of the widget
- L49 _public member_ `FEditableTextBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=(DisplayName="Style"))` — The style
- L55 _public member_ `FTextBlockStyle TextStyle_DEPRECATED;` — `UPROPERTY(meta=(DisplayName="Text Style"))` — The text style
- L61 _public member_ `bool bIsReadOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = GetIsReadOnly, Setter = SetIsReadOnly, Category = Appearance)` — Sets the Text as Readonly to prevent it from being modified interactively by the user
- L65 _public member_ `bool AllowContextMenu;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Whether the context menu can be opened
- L69 _public member_ `FVirtualKeyboardOptions VirtualKeyboardOptions;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — Additional options to be used by the virtual keyboard summoned from this widget
- L73 _public member_ `EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;` — `UPROPERTY(EditAnywhere, Category=Behavior, AdvancedDisplay)` — What action should be taken when the virtual keyboard is dismissed?
- L77 _public member_ `FOnMultiLineEditableTextBoxChangedEvent OnTextChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextChanged (Multi-Line Text Box)"))` — Called whenever the text is changed programmatically or interactively by the user
- L81 _public member_ `FOnMultiLineEditableTextBoxCommittedEvent OnTextCommitted;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnTextCommitted (Multi-Line Text Box)"))` — Called whenever the text is committed.  This happens when the user presses enter or the text box loses focus.
- L93 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="GetText (Multi-Line Text Box)"))` — Gets the widget text @return The widget text
- L101 _public prototype_ `void SetText(FText InText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetText (Multi-Line Text Box)"))` — Directly sets the widget text. Warning: This will wipe any binding created for the Text property! @param InText The text to assign to the widget
- L105 _public prototype_ `FText GetHintText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "GetHintText (Multi-Line Text Box)"))` — Returns the Hint text that appears when there is no text in the text box
- L112 _public prototype_ `void SetHintText(FText InHintText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetHintText (Multi-Line Text Box)"))` — Sets the Hint text that appears when there is no text in the text box @param InHintText The text that appears when there is no text in the text box
- L115 _public prototype_ `void SetError(FText InError);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetError (Multi-Line Text Box)"))`
- L118 _public prototype_ `bool GetIsReadOnly() const;` — Return true when this text cannot be modified interactively by the user
- L122 _public prototype_ `void SetIsReadOnly(UPARAM(DisplayName = "ReadyOnly") bool bR` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "SetIsReadOnly (Multi-Line Text Box)"))` — Sets the Text as Readonly to prevent it from being modified interactively by the user
- L125 _public prototype_ `void SetTextStyle(const FTextBlockStyle& InTextStyle);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetTextStyle (Multi-Line Text Box)"))`
- L128 _public prototype_ `void SetForegroundColor(FLinearColor color);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetForegroundColor (Multi-Line Text Box)"))`
- L136 _public prototype_ `virtual void SynchronizeProperties() override;`
- L140 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L144 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L146 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L150 _protected prototype_ `virtual void OnShapedTextOptionsChanged(FShapedTextOptions InShapedTextOptions) override;`
- L151 _protected prototype_ `virtual void OnJustificationChanged(ETextJustify::Type InJustification) override;`
- L152 _protected prototype_ `virtual void OnWrappingPolicyChanged(ETextWrappingPolicy InWrappingPolicy) override;`
- L153 _protected prototype_ `virtual void OnAutoWrapTextChanged(bool InAutoWrapText) override;`
- L154 _protected prototype_ `virtual void OnWrapTextAtChanged(float InWrapTextAt) override;`
- L155 _protected prototype_ `virtual void OnLineHeightPercentageChanged(float InLineHeightPercentage) override;`
- L156 _protected prototype_ `virtual void OnApplyLineHeightToBottomLineChanged(bool InApplyLineHeightToBottomLine) override;`
- L157 _protected prototype_ `virtual void OnMarginChanged(const FMargin& InMargin) override;`
- L161 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L164 _protected prototype_ `void HandleOnTextChanged(const FText& Text);`
- L165 _protected prototype_ `void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);`
- L168 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> MyEditableTextBlock;`
- L170 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, HintText);`
- L174 _private prototype_ `bool SetTextInternal(const FText& InText);` — @return true if the text was changed, or false if identical.
- L178 _private member_ `bool bIsFontDeprecationDone;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultiLineEditableTextBoxChangedEvent, const FText&, Text);`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMultiLineEditableTextBoxCommittedEvent, const FText&, Text, ETextCommit::Type, CommitMethod);`

### `Source/Runtime/UMG/Public/Components/NamedSlot.h` (Public)


#### class `UNamedSlot`  
`class UNamedSlot : public UContentWidget`  
_L18-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: Allows you to expose an external slot for your user widget.  When others reuse your user control, they can put whatever they want in this named slot.
- L25 _public prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;` — UPanelWidget interface
- L26 _public prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L30 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L34 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L35 _public prototype_ `FGuid GetSlotGUID() const;`
- L47 _public member_ `bool bExposeOnInstanceOnly = false;` — `UPROPERTY(EditAnywhere, Category="Exposing")` — Named slots exposed on the instance only follow a slightly different set of rules.  For example, they can contain some content that the user can replace after dropping it into their tree.  However, these slots can not be inherited to be filled in by a subclass.  So if you want this named slot to be extensible in a subclass of this widget, you should set or leave this value as false.
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _public prototype_ `virtual void PostLoad() override;`
- L55 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L59 _protected member_ `TSharedPtr<SBox> MyBox;`
- L65 _private member_ `FGuid SlotGuid = FGuid::NewGuid();` — `UPROPERTY()`

### `Source/Runtime/UMG/Public/Components/NamedSlotInterface.h` (Public)


#### class `UNamedSlotInterface`  
`class UNamedSlotInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(meta=( CannotImplementInterfaceInBlueprint ), MinimalAPI)`
- inherits: `UInterface`

#### class `INamedSlotInterface`  
`class INamedSlotInterface`  
_L22-50_
- L29 _public prototype_ `virtual void GetSlotNames(TArray<FName>& SlotNames) const = 0;` — Gets the names for slots that we can store widgets into.
- L32 _public prototype_ `virtual UWidget* GetContentForSlot(FName SlotName) const = 0;` — Gets the widget for a given slot by name, will return nullptr if no widget is in the slot.
- L35 _public prototype_ `virtual void SetContentForSlot(FName SlotName, UWidget* Content) = 0;` — Sets the widget for a given slot by name.
- L38 _public prototype_ `bool ContainsContent(UWidget* Content) const;` — Determines if any slot holds the given widget.
- L41 _public prototype_ `FName FindSlotForContent(UWidget* Content) const;` — Determines if any slot holds the given widget and the name of that slot.
- L44 _public prototype_ `void ReleaseNamedSlotSlateResources(bool bReleaseChildren);` — Releases named slot related resources.
- L48 _public prototype_ `void SetNamedSlotDesignerFlags(EWidgetDesignFlags NewFlags);` — Applies the designer flags to the all of the content in all the slots.

### `Source/Runtime/UMG/Public/Components/NativeWidgetHost.h` (Public)


#### class `UNativeWidgetHost`  
`class UNativeWidgetHost : public UWidget`  
_L16-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A NativeWidgetHost is a container widget that can contain one child slate widget.  This should be used when all you need is to nest a native widget inside a UMG widget.
- L20 _private prototype_ `void SetContent(TSharedRef<SWidget> InContent);`
- L21 _private function_ `TSharedPtr< SWidget > GetContent() const`
- L23 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L26 _private prototype_ `virtual const FText GetPaletteCategory() override;`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L34 _protected prototype_ `TSharedRef<SWidget> GetDefaultContent();`
- L37 _protected member_ `TSharedPtr<SWidget> NativeWidget;`

### `Source/Runtime/UMG/Public/Components/Overlay.h` (Public)


#### class `UOverlay`  
`class UOverlay : public UPanelWidget`  
_L18-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: Allows widgets to be stacked on top of each other, uses simple flow layout for content on each layer.
- L22 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L26 _private prototype_ `UOverlaySlot* AddChildToOverlay(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L30 _private prototype_ `bool ReplaceOverlayChildAt(int32 Index, UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category = "Panel")` — Replace the widget at the given index it with a different widget.
- L33 _private prototype_ `virtual const FText GetPaletteCategory() override;`
- L39 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L40 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L41 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L46 _protected member_ `TSharedPtr<class SOverlay> MyOverlay;`
- L50 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/OverlaySlot.h` (Public)


#### class `UOverlaySlot`  
`class UOverlaySlot : public UPanelSlot`  
_L17-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: Slot for the UOverlay panel.  Allows content to be hover above other content.
- L25 _protected member_ `SOverlay::FOverlaySlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.
- L32 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPadding, Category="Layout|Overlay Slot")` — The padding area between the slot and the content it contains.
- L37 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetHorizontalAlignment, Category="Layout|Overlay Slot")` — The alignment of the object horizontally.
- L42 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetVerticalAlignment, Category="Layout|Overlay Slot")` — The alignment of the object vertically.
- L48 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Overlay Slot")` — Set padding area between the slot and the content it contains.
- L51 _public prototype_ `FMargin GetPadding() const;` — Get padding area between the slot and the content it contains.
- L55 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Overlay Slot")` — Set the alignment of the object horizontally.
- L58 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;` — Get the alignment of the object horizontally.
- L62 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Overlay Slot")` — Set the alignment of the object vertically.
- L65 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;` — Get the alignment of the object vertically.
- L70 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L74 _public prototype_ `virtual void BuildSlot(TSharedRef<SOverlay> InOverlay);` — Builds the underlying FSlot for the Slate layout panel.
- L77 _public prototype_ `void ReplaceContent(UWidget* Content);` — Replace the slot content.
- L79 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`

### `Source/Runtime/UMG/Public/Components/PanelSlot.h` (Public)


#### class `UPanelSlot`  
`class UPanelSlot : public UVisual`  
_L12-63_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UVisual`
- desc: The base class for all Slots in UMG.
- L19 _public member_ `TObjectPtr<class UPanelWidget> Parent;` — `UPROPERTY(Instanced)`
- L22 _public member_ `TObjectPtr<class UWidget> Content;` — `UPROPERTY(Instanced)`
- L25 _public prototype_ `UWidget* GetContent() const;` — `UFUNCTION(BlueprintCallable, Category = "Layout|Panel Slot")`
- L28 _public prototype_ `bool IsDesignTime() const;`
- L30 _public function_ `inline bool IsDesignTime() const`
- L33 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L36 _public function_ `virtual void SynchronizeProperties()` — Applies all properties to the live slot if possible.
- L41 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override`
- L51 _public function_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize)` — Called by the designer to "nudge" a widget in a direction. Returns true if the nudge had any effect, false otherwise.
- L56 _public function_ `virtual bool DragDropPreviewByDesigner(const FVector2D& LocalCursorPosition, const TOptional<int32>& XGridSnapSize, const TOptional<int32>& YGridSnapSize)` — Called by the designer when a design-time widget is dragged. Returns true if the drag had any effect, false otherwise.
- L61 _public function_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot)` — Called by the designer when a design-time widget needs to have changes to its associated template synchronized.

### `Source/Runtime/UMG/Public/Components/PanelWidget.h` (Public)


#### class `UPanelWidget`  
`class UPanelWidget : public UWidget`  
_L14-191_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UWidget`
- desc: The base class for all UMG panel widgets.  Panel widgets layout a collection of child widgets.
- L22 _protected member_ `TArray<TObjectPtr<UPanelSlot>> Slots;` — `UPROPERTY(Instanced)` — The slots in the widget holding the child widgets of this panel.
- L28 _public prototype_ `int32 GetChildrenCount() const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Gets number of child widgets in the container.
- L36 _public prototype_ `UWidget* GetChildAt(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Gets the widget at an index. @param Index The index of the widget. @return The widget at the given index, or nothing if there is no widget there.
- L40 _public prototype_ `TArray<UWidget*> GetAllChildren() const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Gets all widgets in the container
- L44 _public prototype_ `int32 GetChildIndex(const UWidget* Content) const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Gets the index of a specific child widget
- L48 _public prototype_ `bool HasChild(UWidget* Content) const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Returns true if panel contains this widget
- L52 _public prototype_ `bool RemoveChildAt(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Removes a child by it's index.
- L59 _public prototype_ `UPanelSlot* AddChild(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Adds a new child widget to the container.  Returns the base slot type, requires casting to turn it into the type specific to the container.
- L66 _public prototype_ `UPanelSlot* AddChild(UWidget* Content, UPanelSlot* SlotTemplate);` — Adds a new child widget to the container. Creates the slot using the template passed to it. Note that a new UPanelSlot object is created and the SlotTemplate is only used as a template.
- L72 _public prototype_ `UPanelSlot* InsertChildAt(int32 Index, UWidget* Content);` — Inserts a widget at a specific index.  This does not update the live slate version, it requires a rebuild of the whole UI to see a change.
- L79 _public prototype_ `UPanelSlot* InsertChildAt(int32 Index, UWidget* Content, UPanelSlot* SlotTemplate);` — Inserts a widget at a specific index. Creates the slot using the template passed to it. Note that a new UPanelSlot object is created and the SlotTemplate is only used as a template.
- L84 _public prototype_ `void ShiftChild(int32 Index, UWidget* Child);` — Moves the child widget from its current index to the new index provided.
- L95 _public prototype_ `bool ReplaceChildAt(int32 Index, UWidget* Content);` — Swaps the widget out of the slot at the given index, replacing it with a different widget. @param Index the index at which to replace the child content with this new Content. @param Content The content to replace the child with. @return true if the index existed and the child could be replaced.
- L103 _public prototype_ `virtual bool ReplaceChild(UWidget* CurrentChild, UWidget* NewChild);` — Swaps the child widget out of the slot, and replaces it with the new child widget. @param CurrentChild The existing child widget being removed. @param NewChild The new child widget being inserted. @return true if the CurrentChild was found and the swap occurred, otherwise false.
- L105 _public prototype_ `virtual void SetDesignerFlags(EWidgetDesignFlags NewFlags) override;`
- L114 _public prototype_ `bool RemoveChild(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Removes a specific widget from the container. @return true if the widget was found and removed.
- L118 _public prototype_ `bool HasAnyChildren() const;` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Returns true if there are any child widgets in the panel
- L122 _public prototype_ `virtual void ClearChildren();` — `UFUNCTION(BlueprintCallable, Category="Widget|Panel")` — Remove all child widgets from the panel widget.
- L125 _public prototype_ `const TArray<UPanelSlot*>& GetSlots() const;` — The slots in the widget holding the child widgets of this panel.
- L128 _public function_ `bool CanHaveMultipleChildren() const` — Returns true if the panel supports more than one child.
- L134 _public function_ `bool CanAddMoreChildren() const` — Returns true if the panel can accept another child widget.
- L139 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L142 _public function_ `virtual bool LockToPanelOnDrag() const`
- L147 _public function_ `virtual void ConnectEditorData() override`
- L164 _public prototype_ `virtual void PostLoad() override;`
- L167 _public function_ `virtual UClass* GetSlotClass() const`
- L175 _protected prototype_ `virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override;`
- L178 _protected function_ `virtual void OnSlotAdded(UPanelSlot* InSlot)`
- L183 _protected function_ `virtual void OnSlotRemoved(UPanelSlot* InSlot)`
- L190 _protected member_ `bool bCanHaveMultipleChildren;` — Can this panel allow for multiple children?

### `Source/Runtime/UMG/Public/Components/PostBufferBlurUpdater.h` (Public)


#### class `UPostBufferBlurUpdater`  
`class UPostBufferBlurUpdater : public USlatePostBufferProcessorUpdater`  
_L19-30_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI)`
- inherits: `USlatePostBufferProcessorUpdater`
- desc: Processor updater that sets the blur strength for a blur processor intra-frame on the renderthread
- L26 _public member_ `float GaussianBlurStrength = 10;` — `UPROPERTY(EditAnywhere, Category = "GaussianBlur")`
- L29 _public prototype_ `virtual TSharedPtr<FSlatePostProcessorUpdaterProxy > GetRenderThreadProxy() const override;`

#### class `FPostBufferBlurUpdaterProxy`  
`class FPostBufferBlurUpdaterProxy : public FSlatePostProcessorUpdaterProxy`  
_L35-43_
- inherits: `FSlatePostProcessorUpdaterProxy`
- desc: Renderthread proxy for the blur processor updater
- L40 _public member_ `float GaussianBlurStrength_RenderThread = 10;` — Blur strength that will be copied over to the processor mid-frame
- L42 _public prototype_ `virtual void UpdateProcessor_RenderThread(TSharedPtr<FSlateRHIPostBufferProcessorProxy>) const override;`

### `Source/Runtime/UMG/Public/Components/PostBufferUpdate.h` (Public)


#### struct `FSlatePostBufferUpdateInfo`  
`struct FSlatePostBufferUpdateInfo`  
_L23-34_
- reflection: `USTRUCT()`
- desc: Struct containing info needed to update a particular buffer
- L29 _public member_ `ESlatePostRT BufferToUpdate = ESlatePostRT::None;` — `UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — Buffers that we should update, all of these buffers will be affected by 'bPerformDefaultPostBufferUpdate' if disabled
- L33 _public member_ `TObjectPtr<USlatePostBufferProcessorUpdater> PostParamUpdater = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — Optional processor updater for buffer, used to update a processor within a frame

#### class `UPostBufferUpdate`  
`class UPostBufferUpdate : public UWidget`  
_L44-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: Widget that when drawn, will trigger the slate post buffer to update. Does not draw anything itself. This allows for you to perform layered UI / sampling effects with the GetSlatePost material functions, by placing this widget after UI you would like to be processed / sampled is drawn. * No Children
- L49 _public prototype_ `UPostBufferUpdate();`
- L58 _private member_ `bool bUpdateOnlyPaintArea;` — `UPROPERTY(BlueprintReadOnly, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — True if we should only update the buffer within the bounds of this widget
- L66 _private member_ `bool bPerformDefaultPostBufferUpdate;` — `UPROPERTY(BlueprintReadOnly, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — True if we should do the default post buffer update of the scene before any UI. If any PostBufferUpdate widget has this set as false, be default scene copy / processing will not occur.
- L71 _private member_ `TArray<ESlatePostRT> BuffersToUpdate;` — `UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — Buffers that we should update, all of these buffers will be affected by 'bPerformDefaultPostBufferUpdate' if disabled
- L75 _private member_ `TArray<FSlatePostBufferUpdateInfo> UpdateBufferInfos;` — `UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — Buffer to update when this widget is drawn, along with info needed to update that buffer if desired intra-frame
- L80 _public function_ `bool GetUpdateOnlyPaintArea() const`
- L83 _public prototype_ `bool DoesUpdateSlatePostRT(ESlatePostRT SlateBufferBits) const ;` — True if this widget updates any buffer indicated in SlateBufferBits
- L88 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L89 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L90 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L94 _protected member_ `TSharedPtr<SPostBufferUpdate> MyPostBufferUpdate;`

#### class `USlatePostBufferProcessorUpdater`  
`class USlatePostBufferProcessorUpdater : public UObject`  
_L103-125_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: Class that can create a FPostParamUpdaterProxy whose lifetime will be managed by the renderthread. This proxy will be given a Post buffer processor to update mid-frame.
- L118 _public member_ `bool bSkipBufferUpdate = false;` — `UPROPERTY()` — True implies we will skip the buffer update & only update the processor. Previously useful to reset params for processor runs next frame. Since there are no default buffer updates anymore, setting parameters for subsequent updates is meaningless as non-default updates will set all their parameters anyway.
- L121 _public function_ `virtual TSharedPtr<FSlatePostProcessorUpdaterProxy> GetRenderThreadProxy() const`

### `Source/Runtime/UMG/Public/Components/ProgressBar.h` (Public)


#### class `UProgressBar`  
`class UProgressBar : public UWidget`  
_L21-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: The progress bar widget is a simple bar that fills up that can be restyled to fit any number of uses. * No Children
- L29 _public member_ `FProgressBarStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Style" ))` — The progress bar style
- L34 _public member_ `float Percent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter, Setter, BlueprintSetter="SetPercent", Category="Progress", meta = (UIMin = "0", UIMax = "1"))` — Used to determine the fill position of the progress bar ranging 0..1
- L39 _public member_ `TEnumAsByte<EProgressBarFillType::Type> BarFillType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Progress")` — Defines the direction in which the progress bar fills
- L44 _public member_ `TEnumAsByte<EProgressBarFillStyle::Type> BarFillStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Progress")` — Defines the visual style of the progress bar fill - scale or mask
- L49 _public member_ `bool bIsMarquee;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter="UseMarquee", Setter="SetIsMarquee", BlueprintSetter="SetIsMarquee", Category="Progress")`
- L54 _public member_ `FVector2D BorderPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Progress")`
- L58 _public member_ `FGetFloat PercentDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the text of the widget
- L63 _public member_ `FLinearColor FillColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter, Setter, BlueprintSetter="SetFillColorAndOpacity", Category="Appearance")` — Fill Color and Opacity
- L67 _public member_ `FGetLinearColor FillColorAndOpacityDelegate;` — `UPROPERTY()`
- L72 _public prototype_ `const FProgressBarStyle& GetWidgetStyle() const;`
- L75 _public prototype_ `void SetWidgetStyle(const FProgressBarStyle& InStyle);` — /
- L78 _public prototype_ `float GetPercent() const;`
- L82 _public prototype_ `void SetPercent(float InPercent);` — `UFUNCTION(BlueprintCallable, Category="Progress")` — Sets the current value of the ProgressBar.
- L85 _public prototype_ `EProgressBarFillType::Type GetBarFillType() const;`
- L88 _public prototype_ `void SetBarFillType(EProgressBarFillType::Type InBarFillType);`
- L91 _public prototype_ `EProgressBarFillStyle::Type GetBarFillStyle() const;`
- L94 _public prototype_ `void SetBarFillStyle(EProgressBarFillStyle::Type InBarFillStyle);`
- L97 _public prototype_ `bool UseMarquee() const;`
- L101 _public prototype_ `void SetIsMarquee(bool InbIsMarquee);` — `UFUNCTION(BlueprintCallable, Category="Progress")` — Sets the progress bar to show as a marquee.
- L104 _public prototype_ `FVector2D GetBorderPadding() const;`
- L107 _public prototype_ `void SetBorderPadding(FVector2D InBorderPadding);`
- L110 _public prototype_ `FLinearColor GetFillColorAndOpacity() const;`
- L114 _public prototype_ `void SetFillColorAndOpacity(FLinearColor InColor);` — `UFUNCTION(BlueprintCallable, Category="Progress")` — Sets the fill color of the progress bar.
- L119 _public prototype_ `virtual void SynchronizeProperties() override;`
- L123 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L128 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L129 _public prototype_ `virtual void OnCreationFromPalette() override;`
- L135 _protected member_ `TSharedPtr<SProgressBar> MyProgressBar;` — Native Slate Widget
- L138 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L141 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, FillColorAndOpacity);`

### `Source/Runtime/UMG/Public/Components/RadialBoxSettings.h` (Public)


#### struct `FRadialBoxSettings`  
`struct FRadialBoxSettings`  
_L10-47_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `float StartingAngle;` — `UPROPERTY(EditAnywhere, Category = "Items", meta = (ClampMin = 0, ClampMax = 360))` — At what angle will we place the first element of the wheel?
- L20 _public member_ `bool bDistributeItemsEvenly;` — `UPROPERTY(EditAnywhere, Category = "Items")` — Distribute Items evenly in the whole circle. Checking this option ignores AngleBetweenItems
- L24 _public member_ `bool bClockwiseOrder;` — `UPROPERTY(EditAnywhere, Category = "Items")` — If enabled, Places the entries in clockwise order instead of counter-clockwise order
- L28 _public member_ `float AngleBetweenItems;` — `UPROPERTY(EditAnywhere, Category = "Items", meta = (EditCondition = "!bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))` — Amount of Euler degrees that separate each item. Only used when bDistributeItemsEvenly is false
- L32 _public member_ `float SectorCentralAngle;` — `UPROPERTY(EditAnywhere, Category = "Items", meta = (EditCondition = "bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))` — If we need a section of a radial (for example half-a-radial) we can define a central angle < 360 (180 in case of half-a-radial). Used when bDistributeItemsEvenly is enabled.
- L36 _public member_ `float MarginSize;` — `UPROPERTY(EditAnywhere, Category = "Items", meta = (ClampMin = 0))` — How much space to leave between the widgets and the edge of the panel
- L38 _public function_ `FRadialBoxSettings() : StartingAngle(0.f) , bDistributeItemsEvenly(true) , bClockwiseOrder(false) , AngleBetweenItems(0.f) , SectorCentralAngle(360.f) , MarginSize(0.f)`

### `Source/Runtime/UMG/Public/Components/RetainerBox.h` (Public)


#### class `URetainerBox`  
`class URetainerBox : public UContentWidget`  
_L26-214_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: The Retainer Box renders children widgets to a render target first before later rendering that render target to the screen.  This allows both frequency and phase to be controlled so that the UI can actually render less often than the frequency of the main game render.  It also has the side benefit of allow materials to be applied to the render target after drawing the widgets to apply a simple post process. * Single Child * Caching / Performance
- L33 _protected member_ `bool bRetainRender = true;` — `UE_DEPRECATED(5.2, "Direct access to bRetainRender is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = "SetRetainRendering", Getter = "IsRetainRendering", BlueprintSetter = "SetRetainRendering", Category = "Render Rules")`
- L42 _public member_ `bool RenderOnInvalidation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsRenderOnInvalidation", Category = "Render Rules", meta = (EditCondition = bRetainRender))` — Should this widget redraw the contents it has every time it receives an invalidation request from it's children, similar to the invalidation panel.
- L49 _public member_ `bool RenderOnPhase;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsRenderOnPhase", Category = "Render Rules", meta = (EditCondition = bRetainRender))` — Should this widget redraw the contents it has every time the phase occurs.
- L60 _public member_ `int32 Phase;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Render Rules", meta=(UIMin=0, ClampMin=0))` — The Phase this widget will draw on. If the Phase is 0, and the PhaseCount is 1, the widget will be drawn fresh every frame. If the Phase were 0, and the PhaseCount were 2, this retainer would draw a fresh frame every other frame.  So in a 60Hz game, the UI would render at 30Hz.
- L72 _public member_ `int32 PhaseCount;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Render Rules", meta=(UIMin=1, ClampMin=1))` — The PhaseCount controls how many phases are possible know what to modulus the current frame count by to determine if this is the current frame to draw the widget on. If the Phase is 0, and the PhaseCount is 1, the widget will be drawn fresh every frame. If the Phase were 0, and the PhaseCount were 2, this retainer would draw a fresh frame every other frame.  So in a 60Hz game, the UI would render at 30Hz.
- L80 _public prototype_ `void SetRenderingPhase(int32 RenderPhase, int32 TotalPhases);` — `UFUNCTION(BlueprintCallable, Category="Retainer")` — Requests the retainer redrawn the contents it has.
- L86 _public prototype_ `void RequestRender();` — `UFUNCTION(BlueprintCallable, Category="Retainer")` — Requests the retainer redrawn the contents it has.
- L92 _public prototype_ `UMaterialInstanceDynamic* GetEffectMaterial() const;` — `UFUNCTION(BlueprintCallable, Category="Retainer|Effect")` — Get the current dynamic effect material applied to the retainer box.
- L98 _public prototype_ `void SetEffectMaterial(UMaterialInterface* EffectMaterial);` — `UFUNCTION(BlueprintCallable, Category="Retainer|Effect")` — Set a new effect material to the retainer widget.
- L104 _public prototype_ `void SetTextureParameter(FName TextureParameter);` — `UFUNCTION(BlueprintCallable, Category="Retainer|Effect")` — Sets the name of the texture parameter to set the render target to on the material.
- L110 _public prototype_ `void SetRetainRendering(bool bInRetainRendering);` — `UFUNCTION(BlueprintCallable, Category = "Retainer")` — Set the flag for if we retain the render or pass-through
- L115 _public prototype_ `bool IsRetainRendering() const;` — Get the flag for if we retain the render or pass-through.
- L120 _public prototype_ `int32 GetPhase() const;` — Get the phase to render on.
- L125 _public prototype_ `int32 GetPhaseCount() const;` — Get the total number of phases.
- L130 _public prototype_ `bool IsRenderOnInvalidation() const;` — Get whether this widget should redraw the contents it has every time it receives an invalidation request.
- L135 _public prototype_ `bool IsRenderOnPhase() const;` — Get whether this widget should redraw the contents it has every time the phase occurs.
- L137 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L140 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L143 _public prototype_ `FGeometry GetCachedAllottedGeometry() const;`
- L157 _protected member_ `TObjectPtr<UMaterialInterface> EffectMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetEffectMaterialInterface", Setter, BlueprintSetter = "SetEffectMaterial", Category = "Effect")` — The effect to optionally apply to the render target.  We will set the texture sampler based on the name set in the @TextureParameter property. If you want to adjust transparency of the final image, make sure you set Blend Mode to AlphaComposite (Pre-Multiplied Alpha) and make sure to multiply the alpha you're apply across the surface to the color and the alpha of the render target, otherwise you won't see the expected color.
- L164 _protected member_ `FName TextureParameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetTextureParameter", Category="Effect")` — The texture sampler parameter of the @EffectMaterial, that we'll set to the render target.
- L171 _protected member_ `bool bShowEffectsInDesigner;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = bRetainRender))` — If true, retained rendering occurs in designer
- L175 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L176 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L180 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L181 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L186 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L191 _protected prototype_ `void InitRenderOnInvalidation(bool InRenderOnInvalidation);` — Initialize RenderOnInvalidation in the constructor before the SWidget is constructed.
- L194 _protected prototype_ `void InitRenderOnPhase(bool InRenderOnPhase);` — Initialize RenderOnPhase in the constructor before the SWidget is constructed.
- L197 _protected prototype_ `void InitPhase(int32 InPhase);` — Initialize Phase in the constructor before the SWidget is constructed.
- L200 _protected prototype_ `void InitPhaseCount(int32 InPhaseCount);` — Initialize PhaseCount in the constructor before the SWidget is constructed.
- L205 _public prototype_ `const FName& GetTextureParameter() const;` — Gets the name of the texture parameter to set the render target to on the material.
- L210 _public prototype_ `const UMaterialInterface* GetEffectMaterialInterface() const;` — Gets the current dynamic effect material applied to the retainer box.
- L213 _protected member_ `TSharedPtr<class SRetainerWidget> MyRetainerWidget;`

### `Source/Runtime/UMG/Public/Components/RichTextBlock.h` (Public)


#### struct `FRichTextStyleRow`  
`struct FRichTextStyleRow : public FTableRowBase`  
_L22-30_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- desc: Simple struct for rich text styles
- L29 _public member_ `FTextBlockStyle TextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`

#### class `URichTextBlock`  
`class URichTextBlock : public UTextLayoutWidget`  
_L39-261_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTextLayoutWidget`
- desc: The rich text block * Fancy Text * No Children
- L46 _protected member_ `FText Text;` — `UPROPERTY(EditAnywhere, Category = Content, BlueprintSetter = "SetText", BlueprintGetter = "GetText", Getter, Setter, meta = (MultiLine = "true"))` — The text to display
- L51 _protected member_ `TObjectPtr<UDataTable> TextStyleSet;` — `UPROPERTY(EditAnywhere, Category = Appearance, BlueprintSetter = "SetTextStyleSet", BlueprintGetter = "GetTextStyleSet", Getter, Setter, meta = (RequiredAssetDataTags = "RowStructure=/Script/UMG.RichTextStyleRow"))`
- L55 _protected member_ `TArray<TSubclassOf<URichTextBlockDecorator>> DecoratorClasses;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L60 _protected member_ `FTextBlockStyle DefaultTextStyleOverride;` — `UPROPERTY(EditAnywhere, Category = Appearance, BlueprintSetter = "SetDefaultTextStyle", Setter = "SetDefaultTextStyle", Getter, meta = (EditCondition = bOverrideDefaultStyle))` — Text style to apply by default to text in this block
- L65 _protected member_ `float MinDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = "SetMinDesiredWidth", Getter, Setter, Category = Appearance)` — The minimum desired size for the text
- L69 _protected member_ `bool bOverrideDefaultStyle = false;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — True to specify the default text style for this rich text inline, overriding any default provided in the style set table
- L74 _protected member_ `ETextTransformPolicy TextTransformPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = "SetTextTransformPolicy", Getter = "GetTransformPolicy", Setter, Category = Appearance, meta = (DisplayName = "Transform Policy"))` — The text transformation policy to apply to this text block
- L79 _protected member_ `ETextOverflowPolicy TextOverflowPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = "SetTextOverflowPolicy", Getter = "GetOverflowPolicy", Setter, Category = Clipping, AdvancedDisplay, meta = (DisplayName = "Overflow Policy"))` — Sets what happens to text that is clipped and doesn't fit within the clip rect for this widget
- L87 _public prototype_ `void SetDefaultColorAndOpacity(FSlateColor InColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color and opacity of the default text in this rich text block @param InColorAndOpacity		The new text color and opacity
- L95 _public prototype_ `void SetDefaultShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color and opacity of the default text drop shadow Note: if opacity is zero no shadow will be drawn @param InShadowColorAndOpacity		The new drop shadow color and opacity
- L102 _public prototype_ `void SetDefaultShadowOffset(FVector2D InShadowOffset);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the offset that the default text drop shadow should be drawn at @param InShadowOffset		The new offset
- L109 _public prototype_ `void SetDefaultFont(FSlateFontInfo InFontInfo);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Dynamically set the default font info for this rich text block @param InFontInfo The new font info
- L116 _public prototype_ `void SetDefaultStrikeBrush(const FSlateBrush& InStrikeBrush);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Dynamically set the default strike brush for this rich text block @param InStrikeBrush The new brush to use to strike through text
- L123 _public prototype_ `void SetMinDesiredWidth(float InMinDesiredWidth);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Set the minimum desired width for this rich text block @param InMinDesiredWidth new minimum desired width
- L130 _public prototype_ `void SetAutoWrapText(bool InAutoTextWrap);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Set the auto wrap for this rich text block @param InAutoTextWrap to turn wrap on or off
- L137 _public prototype_ `void SetTextTransformPolicy(ETextTransformPolicy InTransformPolicy);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Set the text transformation policy for this text block. @param InTransformPolicy the new text transformation policy.
- L144 _public prototype_ `void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Set the text overflow policy for this text block. @param InOverflowPolicy the new text overflow policy.
- L151 _public prototype_ `void SetDefaultTextStyle(const FTextBlockStyle& InDefaultTextStyle);` — `UFUNCTION(BlueprintCallable, Category = Appearance)` — Wholesale override of the currently established default text style @param InDefaultTextStyle The new text style to apply to all default (i.e. undecorated) text in the block
- L154 _public prototype_ `void SetDefaultMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = Appearance)`
- L158 _public prototype_ `void ClearAllDefaultStyleOverrides();` — `UFUNCTION(BlueprintCallable, Category = Appearance)` — Remove all overrides made to the default text style and return to the style specified in the style set data table
- L165 _public prototype_ `UMaterialInstanceDynamic* GetDefaultDynamicMaterial();` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Creates a dynamic material for the default font or returns it if it already exists
- L171 _public prototype_ `void SetDecorators(const TArray<TSubclassOf<URichTextBlockDecorator>>& InDecoratorClasses);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Replaces the existing decorators with the list provided
- L174 _public prototype_ `URichTextBlock(const FObjectInitializer& ObjectInitializer);`
- L177 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L181 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L186 _public prototype_ `virtual const FText GetPaletteCategory() override;` — UWidget interface
- L187 _public prototype_ `virtual void OnCreationFromPalette() override;`
- L188 _public prototype_ `virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;`
- L196 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Returns widgets text.
- L204 _public prototype_ `virtual void SetText(const FText& InText);` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (AutoCreateRefTerm = "InText"))` — Directly sets the widget text. Warning: This will wipe any binding created for the Text property! @param InText The text to assign to the widget
- L207 _public prototype_ `UDataTable* GetTextStyleSet() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L210 _public prototype_ `void SetTextStyleSet(UDataTable* NewTextStyleSet);` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L212 _public prototype_ `const FTextBlockStyle& GetDefaultTextStyle() const;`
- L213 _public prototype_ `const FTextBlockStyle& GetCurrentDefaultTextStyle() const;`
- L217 _public prototype_ `URichTextBlockDecorator* GetDecoratorByClass(TSubclassOf<URichTextBlockDecorator> DecoratorClass);` — `UFUNCTION(BlueprintCallable, Category = "Widget")`
- L223 _public prototype_ `void RefreshTextLayout();` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Causes the text to reflow it's layout and re-evaluate any decorators
- L227 _protected prototype_ `virtual void OnShapedTextOptionsChanged(FShapedTextOptions InShapedTextOptions) override;`
- L228 _protected prototype_ `virtual void OnJustificationChanged(ETextJustify::Type InJustification) override;`
- L229 _protected prototype_ `virtual void OnWrappingPolicyChanged(ETextWrappingPolicy InWrappingPolicy) override;`
- L230 _protected prototype_ `virtual void OnAutoWrapTextChanged(bool InAutoWrapText) override;`
- L231 _protected prototype_ `virtual void OnWrapTextAtChanged(float InWrapTextAt) override;`
- L232 _protected prototype_ `virtual void OnLineHeightPercentageChanged(float InLineHeightPercentage) override;`
- L233 _protected prototype_ `virtual void OnApplyLineHeightToBottomLineChanged(bool InApplyLineHeightToBottomLine) override;`
- L234 _protected prototype_ `virtual void OnMarginChanged(const FMargin& InMargin) override;`
- L237 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L239 _protected prototype_ `virtual void UpdateStyleData();`
- L240 _protected prototype_ `void RebuildStyleInstance();`
- L241 _protected prototype_ `virtual void CreateDecorators(TArray< TSharedRef< class ITextDecorator > >& OutDecorators);`
- L242 _protected prototype_ `virtual TSharedPtr< class IRichTextMarkupParser > CreateMarkupParser();`
- L243 _protected prototype_ `virtual TSharedPtr< class IRichTextMarkupWriter > CreateMarkupWriter();`
- L245 _protected prototype_ `void BeginDefaultStyleOverride();`
- L246 _protected prototype_ `virtual void ApplyUpdatedDefaultTextStyle();`
- L248 _protected prototype_ `const FTextBlockStyle& GetDefaultTextStyleOverride() const;`
- L249 _protected prototype_ `float GetMinDesiredWidth() const;`
- L250 _protected prototype_ `ETextTransformPolicy GetTransformPolicy() const;`
- L251 _protected prototype_ `ETextOverflowPolicy GetOverflowPolicy() const;`
- L255 _protected member_ `FTextBlockStyle DefaultTextStyle;` — `UPROPERTY(Transient)`
- L258 _protected member_ `TArray<TObjectPtr<URichTextBlockDecorator>> InstanceDecorators;` — `UPROPERTY(Transient)`
- L259 _protected member_ `TSharedPtr<class FSlateStyleSet> StyleInstance;`
- L260 _protected member_ `TSharedPtr<SRichTextBlock> MyRichTextBlock;`

### `Source/Runtime/UMG/Public/Components/RichTextBlockDecorator.h` (Public)


#### class `FRichTextDecorator`  
`class FRichTextDecorator : public ITextDecorator`  
_L19-42_
- inherits: `ITextDecorator`
- L22 _public prototype_ `FRichTextDecorator(URichTextBlock* InOwner);`
- L24 _public prototype_ `virtual ~FRichTextDecorator() = default;`
- L27 _public function_ `virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override` — Override this function to specify which types of tags are handled by this decorator
- L32 _public prototype_ `virtual TSharedRef<ISlateRun> Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style) override final;`
- L36 _protected prototype_ `virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& DefaultTextStyle) const;` — Override this function if you want to create a unique widget like an image
- L39 _protected prototype_ `virtual void CreateDecoratorText(const FTextRunInfo& RunInfo, FTextBlockStyle& InOutTextStyle, FString& InOutString) const;` — Override this function if you want to dynamically generate text, optionally changing the style. InOutString will start as the content between tags
- L41 _protected member_ `URichTextBlock* Owner;`

#### class `URichTextBlockDecorator`  
`class URichTextBlockDecorator : public UObject`  
_L45-53_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L50 _public prototype_ `URichTextBlockDecorator(const FObjectInitializer& ObjectInitializer);`
- L52 _public prototype_ `virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner);`

### `Source/Runtime/UMG/Public/Components/RichTextBlockImageDecorator.h` (Public)


#### struct `FRichImageRow`  
`struct FRichImageRow : public FTableRowBase`  
_L21-29_
- reflection: `USTRUCT(Blueprintable, BlueprintType)`
- inherits: `FTableRowBase`
- desc: Simple struct for rich text styles
- L28 _public member_ `FSlateBrush Brush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`

#### class `URichTextBlockImageDecorator`  
`class URichTextBlockImageDecorator : public URichTextBlockDecorator`  
_L39-56_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `URichTextBlockDecorator`
- desc: Allows you to setup an image decorator that can be configured to map certain keys to certain images.  We recommend you subclass this as a blueprint to configure the instance. Understands the format <img id="NameOfBrushInTable"></>
- L44 _public prototype_ `URichTextBlockImageDecorator(const FObjectInitializer& ObjectInitializer);`
- L46 _public prototype_ `virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;`
- L48 _public prototype_ `virtual const FSlateBrush* FindImageBrush(FName TagOrId, bool bWarnIfMissing);`
- L52 _protected prototype_ `FRichImageRow* FindImageRow(FName TagOrId, bool bWarnIfMissing);`
- L55 _protected member_ `TObjectPtr<class UDataTable> ImageSet;` — `UPROPERTY(EditAnywhere, Category=Appearance, meta = (RequiredAssetDataTags = "RowStructure=/Script/UMG.RichImageRow"))`

### `Source/Runtime/UMG/Public/Components/SafeZone.h` (Public)


#### class `USafeZone`  
`class USafeZone : public UContentWidget`  
_L28-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: The Safe-Zone widget is an essential part of developing a game UI that can run on lots of different non-PC platforms. While a modern flat panel computer monitor may not have over scan issues, this is a common occurrence for Consoles. It's common for TVs to have extra pixels under the bezel, in addition to projectors and projection TVs having potentially several vertical and horizontal columns of pixels hidden behind or against a black border of the projection screen. Useful testing console commands to help, simulate the safe zone on PC, r.DebugSafeZone.TitleRatio 0.96 r.DebugActionZone.ActionRatio 0.96 To enable a border to visualize the safe zone, use this console command, r.DebugSafeZone.Mode controls the debug visualization overlay (0..1, default 0). 0: Do not display the safe zone overlay. 1: Display the overlay for the title safe zone.
- L32 _public prototype_ `USafeZone();`
- L35 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L37 _public prototype_ `virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;`
- L40 _public prototype_ `virtual void OnSlotAdded( UPanelSlot* Slot ) override;`
- L41 _public prototype_ `virtual void OnSlotRemoved( UPanelSlot* Slot ) override;`
- L42 _public prototype_ `virtual UClass* GetSlotClass() const override;`
- L44 _public prototype_ `void UpdateWidgetProperties();`
- L47 _public prototype_ `void SetSidesToPad(bool InPadLeft, bool InPadRight, bool InPadTop, bool InPadBottom);` — `UFUNCTION(BlueprintCallable, Category = "SafeZone")`
- L54 _public member_ `bool PadLeft;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "SafeZone")` — If this safe zone should pad for the left side of the screen's safe zone
- L59 _public member_ `bool PadRight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "SafeZone")` — If this safe zone should pad for the right side of the screen's safe zone
- L64 _public member_ `bool PadTop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "SafeZone")` — If this safe zone should pad for the top side of the screen's safe zone
- L69 _public member_ `bool PadBottom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "SafeZone")` — If this safe zone should pad for the bottom side of the screen's safe zone
- L73 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L76 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L78 _protected prototype_ `void SetPadLeft(bool InPadLeft);`
- L79 _protected prototype_ `bool GetPadLeft() const;`
- L81 _protected prototype_ `void SetPadRight(bool InPadRight);`
- L82 _protected prototype_ `bool GetPadRight() const;`
- L84 _protected prototype_ `void SetPadTop(bool InPadTop);`
- L85 _protected prototype_ `bool GetPadTop() const;`
- L87 _protected prototype_ `void SetPadBottom(bool InPadBottom);`
- L88 _protected prototype_ `bool GetPadBottom() const;`
- L90 _protected member_ `TSharedPtr< class SSafeZone > MySafeZone;`
- L93 _protected member_ `TOptional<FVector2D> DesignerSize;`
- L94 _protected member_ `TOptional<float> DesignerDpi;`

### `Source/Runtime/UMG/Public/Components/SafeZoneSlot.h` (Public)


#### class `USafeZoneSlot`  
`class USafeZoneSlot : public UPanelSlot`  
_L15-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- L22 _public member_ `bool bIsTitleSafe;` — `UE_DEPRECATED(5.2, "Direct access to bIsTitleSafe is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsTitleSafe", Setter = "SetIsTitleSafe", Category = SafeZone)`
- L26 _public member_ `FMargin SafeAreaScale;` — `UE_DEPRECATED(5.2, "Direct access to SafeAreaScale is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = SafeZone)`
- L30 _public member_ `TEnumAsByte< EHorizontalAlignment > HAlign;` — `UE_DEPRECATED(5.2, "Direct access to HAlign is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetHorizontalAlignment", Setter = "SetHorizontalAlignment", Category = SafeZone)`
- L34 _public member_ `TEnumAsByte< EVerticalAlignment > VAlign;` — `UE_DEPRECATED(5.2, "Direct access to VAlign is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetVerticalAlignment", Setter = "SetVerticalAlignment", Category = SafeZone)`
- L38 _public member_ `FMargin Padding;` — `UE_DEPRECATED(5.2, "Direct access to Padding is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = SafeZone)`
- L40 _public prototype_ `USafeZoneSlot();`
- L42 _public prototype_ `void SetIsTitleSafe(bool InIsTitleSafe);`
- L43 _public prototype_ `bool IsTitleSafe() const;`
- L45 _public prototype_ `void SetSafeAreaScale(const FMargin& InSafeAreaScale);`
- L46 _public prototype_ `const FMargin& GetSafeAreaScale() const;`
- L48 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHAlign);`
- L49 _public prototype_ `const EHorizontalAlignment GetHorizontalAlignment() const;`
- L51 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVAlign);`
- L52 _public prototype_ `const EVerticalAlignment GetVerticalAlignment() const;`
- L54 _public prototype_ `void SetPadding(const FMargin& InPadding);`
- L55 _public prototype_ `const FMargin& GetPadding() const;`
- L58 _public prototype_ `virtual void SynchronizeProperties() override;`
- L62 _public prototype_ `void BuildSlot(TSharedRef<SSafeZone> InSafeZone);` — Builds the underlying slot for the slate button.
- L64 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L69 _private member_ `TWeakPtr<SSafeZone> SafeZone;` — A pointer to the button to allow us to adjust the alignment, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/ScaleBox.h` (Public)


#### class `UScaleBox`  
`class UScaleBox : public UContentWidget`  
_L21-103_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UContentWidget`
- desc: Allows you to place content with a desired size and have it scale to meet the constraints placed on this box's alloted area.  If you needed to have a background image scale to fill an area but not become distorted with different aspect ratios, or if you need to auto fit some text to an area, this is the control for you. * Single Child * Aspect Ratio
- L30 _public member_ `TEnumAsByte<EStretch::Type> Stretch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, BlueprintSetter = "SetStretch", Category = "Stretching")` — The stretching rule to apply when content is stretched
- L35 _public member_ `TEnumAsByte<EStretchDirection::Type> StretchDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, BlueprintSetter = "SetStretchDirection", Category = "Stretching")` — Controls in what direction content can be scaled
- L40 _public member_ `float UserSpecifiedScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, BlueprintSetter = "SetUserSpecifiedScale", Category = "Stretching")` — Optional scale that can be specified by the User. Used only for UserSpecified stretching.
- L45 _public member_ `bool IgnoreInheritedScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter = "IsIgnoreInheritedScale", BlueprintSetter = "SetIgnoreInheritedScale", Category = "Stretching")` — Optional bool to ignore the inherited scale. Applies inverse scaling to counteract parents before applying the local scale operation.
- L49 _public prototype_ `void SetStretch(EStretch::Type InStretch);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L51 _public prototype_ `EStretch::Type GetStretch() const;`
- L54 _public prototype_ `void SetStretchDirection(EStretchDirection::Type InStretchDirection);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L56 _public prototype_ `EStretchDirection::Type GetStretchDirection() const;`
- L59 _public prototype_ `void SetUserSpecifiedScale(float InUserSpecifiedScale);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L61 _public prototype_ `float GetUserSpecifiedScale() const;`
- L64 _public prototype_ `void SetIgnoreInheritedScale(bool bInIgnoreInheritedScale);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L66 _public prototype_ `bool IsIgnoreInheritedScale() const;`
- L71 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L74 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L77 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L78 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L79 _public prototype_ `virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;`
- L82 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L87 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L88 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L89 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L93 _protected member_ `TSharedPtr<SScaleBox> MyScaleBox;`
- L96 _protected member_ `TOptional<FVector2D> DesignerSize;`
- L101 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/ScaleBoxComponent.h` (Public)


#### class `UScaleBoxComponent`  
`class UScaleBoxComponent : public UUIComponent`  
_L18-99_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UUIComponent`
- desc: This is a class for a Component that wraps the Owner widget with a Scale Box
- L23 _public prototype_ `void SetStretch(EStretch::Type InStretch);`
- L25 _public prototype_ `EStretch::Type GetStretch() const;`
- L27 _public prototype_ `void SetStretchDirection(EStretchDirection::Type InStretchDirection);`
- L29 _public prototype_ `EStretchDirection::Type GetStretchDirection() const;`
- L31 _public prototype_ `void SetUserSpecifiedScale(float InUserSpecifiedScale);`
- L33 _public prototype_ `float GetUserSpecifiedScale() const;`
- L35 _public prototype_ `void SetIgnoreInheritedScale(bool bInIgnoreInheritedScale);`
- L37 _public prototype_ `bool IsIgnoreInheritedScale() const;`
- L41 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L43 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);`
- L45 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L47 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);`
- L50 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L55 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L59 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidgetWithContent(const TSharedRef<SWidget> OwnerContent) override;`
- L68 _private prototype_ `void SynchronizeProperties(TSharedRef<SScaleBox> ScaleBox);`
- L74 _private member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Scale Box Slot", meta = (AllowPrivateAccess = true))` — This property is for the Widget that owns this Component. The alignment of the object horizontally.
- L78 _private member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Scale Box Slot", meta = (AllowPrivateAccess = true))` — This property is for the Widget that owns this Component. The alignment of the object vertically.
- L84 _private member_ `TEnumAsByte<EStretch::Type> Stretch = EStretch::ScaleToFit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Stretching", meta = (AllowPrivateAccess = true))` — The stretching rule to apply when content is stretched
- L88 _private member_ `TEnumAsByte<EStretchDirection::Type> StretchDirection = EStretchDirection::Both;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Stretching", meta = (AllowPrivateAccess = true))` — Controls in what direction content can be scaled
- L92 _private member_ `float UserSpecifiedScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Stretching", meta = (AllowPrivateAccess = true))` — Optional scale that can be specified by the User. Used only for UserSpecified stretching.
- L96 _private member_ `bool IgnoreInheritedScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="IsIgnoreInheritedScale", Setter, Category = "Stretching", meta = (AllowPrivateAccess = true))` — Optional bool to ignore the inherited scale. Applies inverse scaling to counteract parents before applying the local scale operation.
- L98 _private member_ `TWeakPtr<SScaleBox> MyScaleBox;`

### `Source/Runtime/UMG/Public/Components/ScaleBoxSlot.h` (Public)


#### class `UScaleBoxSlot`  
`class UScaleBoxSlot : public UPanelSlot`  
_L17-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UScaleBoxSlot, contains the widget displayed in a button's single slot
- L26 _public member_ `FMargin Padding_DEPRECATED;` — `UPROPERTY()` — The padding area between the slot and the content it contains.
- L32 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category="Layout|ScaleBox Slot")` — The alignment of the object horizontally.
- L37 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category="Layout|ScaleBox Slot")` — The alignment of the object vertically.
- L42 _public prototype_ `void SetPadding(FMargin InPadding);` — `UE_DEPRECATED(5.1, "SetPadding is deprecated")` — `UFUNCTION(BlueprintCallable, Category="Layout|ScaleBox Slot", meta = (DeprecatedFunction, DeprecatedMessage = "The function is deprecated - There is no padding on ScaleBox."))`
- L44 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L47 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|ScaleBox Slot")`
- L50 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L53 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|ScaleBox Slot")`
- L56 _public prototype_ `virtual void SynchronizeProperties() override;`
- L60 _public prototype_ `void BuildSlot(TSharedRef<SScaleBox> InScaleBox);` — Builds the underlying slot for the slate ScaleBox.
- L62 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L66 _private member_ `TWeakPtr<SScaleBox> ScaleBox;` — A pointer to the button to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/ScrollBar.h` (Public)


#### class `UScrollBar`  
`class UScrollBar : public UWidget`  
_L15-123_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UWidget`
- L24 _public member_ `FScrollBarStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Style" ))` — Style of the scrollbar
- L29 _public member_ `bool bAlwaysShowScrollbar;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAlwaysShowScrollbar", Setter = "SetAlwaysShowScrollbar", Category = "Behavior")`
- L34 _public member_ `bool bAlwaysShowScrollbarTrack;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAlwaysShowScrollbarTrack", Setter = "SetAlwaysShowScrollbarTrack", Category = "Behavior")`
- L39 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Behavior")`
- L44 _public member_ `FVector2D Thickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Behavior")` — The thickness of the scrollbar thumb
- L49 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Behavior")` — The margin around the scrollbar
- L62 _public prototype_ `void SetState(float InOffsetFraction, float InThumbSizeFraction);` — `UFUNCTION(BlueprintCallable, Category="Scrolling")` — Set the offset and size of the track's thumb. Note that the maximum offset is 1.0-ThumbSizeFraction. If the user can view 1/3 of the items in a single page, the maximum offset will be ~0.667f @param InOffsetFraction     Offset of the thumbnail from the top as a fraction of the total available scroll space. @param InThumbSizeFraction  Size of thumbnail as a fraction of the total available scroll space.
- L65 _public prototype_ `virtual void SynchronizeProperties() override;`
- L69 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L74 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L85 _public prototype_ `const FScrollBarStyle& GetWidgetStyle() const;` — @return the style of scrollbar.
- L87 _public prototype_ `void SetWidgetStyle(const FScrollBarStyle& InWidgetStyle);` — Sets the style of scrollbar.
- L90 _public prototype_ `bool IsAlwaysShowScrollbar() const;` — @return True if the scrollbar should always show.
- L92 _public prototype_ `void SetAlwaysShowScrollbar(bool bNewValue);` — Sets whether the scrollbar should always show.
- L95 _public prototype_ `bool IsAlwaysShowScrollbarTrack() const;` — @return True if the scrollbar track should always show.
- L97 _public prototype_ `void SetAlwaysShowScrollbarTrack(bool bNewValue);` — Sets whether the scrollbar track should always show
- L100 _public prototype_ `EOrientation GetOrientation() const;` — @return the orientation of the scrollbar.
- L103 _public prototype_ `FVector2D GetThickness() const;` — @return the thickness of the scrollbar.
- L105 _public prototype_ `void SetThickness(const FVector2D& InThickness);` — Sets the thickness of the scrollbar.
- L108 _public prototype_ `FMargin GetPadding() const;` — Sets the padding of the scrollbar.
- L110 _public prototype_ `void SetPadding(const FMargin& InPadding);` — @return the padding of the scrollbar.
- L114 _protected member_ `TSharedPtr<class SScrollBar> MyScrollBar;`
- L118 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L122 _protected prototype_ `void InitOrientation(EOrientation InOrientation);` — Initialize the orientation of the scrollbar in the constructor before the SWidget is constructed.

### `Source/Runtime/UMG/Public/Components/ScrollBox.h` (Public)


#### class `UScrollBox`  
`class UScrollBox : public UPanelWidget`  
_L25-388_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: An arbitrary scrollable collection of widgets.  Great for presenting 10-100 widgets in a list.  Doesn't support virtualization.
- L32 _private member_ `float ScrollAnimationInterpolationSpeed = 15.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Scroll", meta = (AllowPrivateAccess = "true", DisplayAfter = "bAnimateWheelScrolling"))`
- L36 _private member_ `bool bEnableTouchScrolling = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="GetIsTouchScrollingEnabled", Setter="SetIsTouchScrollingEnabled", Category = "Scroll", meta = (AllowPrivateAccess = "true", DisplayAfter = "WheelScrollMultiplier"))` — True to allow scrolling using touch input.
- L40 _private member_ `bool bConsumePointerInput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetConsumePointerInput", Setter = "SetConsumePointerInput", Category = "Scroll", meta = (AllowPrivateAccess = "true", DisplayAfter = "bEnableTouchScrolling"))` — Option to pass touch input events to widgets behind the ScrollBox.
- L44 _private member_ `FKey AnalogMouseWheelKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetAnalogMouseWheelKey", Setter = "SetAnalogMouseWheelKey", Category = "Scroll", meta = (AllowPrivateAccess = "true", DisplayAfter = "bConsumePointerInput"))` — The virtual mouse wheel key for gamepad input
- L48 _private member_ `bool bIsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetIsFocusable", Setter = "SetIsFocusable", Category = "Scroll", meta = (AllowPrivateAccess = "true", DisplayAfter = "AnalogMouseWheelKey"))` — If true, scrollbox can receive focus. On gamepad, ensure AnalogMouseWheelKey is set to allow user interaction
- L55 _public member_ `FScrollBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Style" ))` — The style
- L60 _public member_ `FScrollBarStyle WidgetBarStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Bar Style" ))` — The bar style
- L65 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetOrientation", Category="Scroll")` — The orientation of the scrolling and stacking in the box.
- L70 _public member_ `ESlateVisibility ScrollBarVisibility;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetScrollBarVisibility", Category="Scroll")` — Visibility
- L75 _public member_ `EConsumeMouseWheel ConsumeMouseWheel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetConsumeMouseWheel", Category = "Scroll")` — When mouse wheel events should be consumed.
- L80 _public member_ `FVector2D ScrollbarThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetScrollbarThickness", Category="Scroll")` — The thickness of the scrollbar thumb
- L85 _public member_ `FMargin ScrollbarPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetScrollbarPadding", Category = "Scroll")` — The margin around the scrollbar
- L90 _public member_ `bool AlwaysShowScrollbar;` — `UE_DEPRECATED(5.2, "Direct access to AlwaysShowScrollbar is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAlwaysShowScrollbar", Setter, BlueprintSetter = "SetAlwaysShowScrollbar", Category = "Scroll")`
- L95 _public member_ `bool AlwaysShowScrollbarTrack;` — `UE_DEPRECATED(5.2, "Direct access to AlwaysShowScrollbarTrack is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAlwaysShowScrollbarTrack", Setter, Category = "Scroll")`
- L100 _public member_ `bool AllowOverscroll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAllowOverscroll", Setter, BlueprintSetter = "SetAllowOverscroll", Category = "Scroll")` — Disable to stop scrollbars from activating inertial overscrolling
- L105 _public member_ `bool BackPadScrolling;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsBackPadScrolling", Category = "Scroll")` — Whether to back pad this scroll box, allowing user to scroll backward until child contents are no longer visible
- L110 _public member_ `bool FrontPadScrolling;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsFrontPadScrolling", Category = "Scroll")` — Whether to front pad this scroll box, allowing user to scroll forward until child contents are no longer visible
- L115 _public member_ `bool bAnimateWheelScrolling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAnimateWheelScrolling", Setter = "SetAnimateWheelScrolling", BlueprintSetter = "SetAnimateWheelScrolling", Category = "Scroll")` — True to lerp smoothly when wheel scrolling along the scroll box
- L120 _public member_ `EDescendantScrollDestination NavigationDestination;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetNavigationDestination", Getter, Setter, Category = "Scroll")` — Sets where to scroll a widget to when using explicit navigation or if ScrollWhenFocusChanges is enabled
- L128 _public member_ `float NavigationScrollPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Scroll")` — The amount of padding to ensure exists between the item being navigated to, at the edge of the scrollbox.  Use this if you want to ensure there's a preview of the next item the user could scroll to.
- L133 _public member_ `EScrollWhenFocusChanges ScrollWhenFocusChanges;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetScrollWhenFocusChanges", Category="Scroll", meta=(DisplayName="Scroll When Focus Changes"))` — Scroll behavior when user focus is given to a child widget
- L138 _public member_ `bool bAllowRightClickDragScrolling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsAllowRightClickDragScrolling", Setter = "SetAllowRightClickDragScrolling", Category = "Scroll")` — Option to disable right-click-drag scrolling
- L143 _public member_ `float WheelScrollMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetWheelScrollMultiplier", Category = "Scroll")` — The multiplier to apply when wheel scrolling
- L145 _public prototype_ `void SetWidgetStyle(const FScrollBoxStyle& NewWidgetStyle);`
- L147 _public prototype_ `const FScrollBoxStyle& GetWidgetStyle() const;`
- L149 _public prototype_ `void SetWidgetBarStyle(const FScrollBarStyle& NewWidgetBarStyle);`
- L151 _public prototype_ `const FScrollBarStyle& GetWidgetBarStyle() const;`
- L154 _public prototype_ `void SetConsumeMouseWheel(EConsumeMouseWheel NewConsumeMouseWheel);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L156 _public prototype_ `EConsumeMouseWheel GetConsumeMouseWheel() const;`
- L159 _public prototype_ `void SetOrientation(EOrientation NewOrientation);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L161 _public prototype_ `EOrientation GetOrientation() const;`
- L164 _public prototype_ `void SetScrollBarVisibility(ESlateVisibility NewScrollBarVisibility);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L166 _public prototype_ `ESlateVisibility GetScrollBarVisibility() const;`
- L169 _public prototype_ `void SetScrollbarThickness(const FVector2D& NewScrollbarThickness);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L171 _public prototype_ `FVector2D GetScrollbarThickness() const;`
- L174 _public prototype_ `void SetScrollbarPadding(const FMargin& NewScrollbarPadding);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L176 _public prototype_ `FMargin GetScrollbarPadding() const;`
- L179 _public prototype_ `void SetAlwaysShowScrollbar(bool NewAlwaysShowScrollbar);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L181 _public prototype_ `bool IsAlwaysShowScrollbar() const;`
- L184 _public prototype_ `void SetAllowOverscroll(bool NewAllowOverscroll);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L186 _public prototype_ `bool IsAllowOverscroll() const;`
- L189 _public prototype_ `void SetAnimateWheelScrolling(bool bShouldAnimateWheelScrolling);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L191 _public prototype_ `bool IsAnimateWheelScrolling() const;`
- L194 _public prototype_ `void SetScrollAnimationInterpolationSpeed(float NewScrollAnimationInterpolationSpeed);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L196 _public prototype_ `float GetScrollAnimationInterpolationSpeed() const;`
- L199 _public prototype_ `void SetWheelScrollMultiplier(float NewWheelScrollMultiplier);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L201 _public prototype_ `float GetWheelScrollMultiplier() const;`
- L204 _public prototype_ `void SetIsTouchScrollingEnabled(bool bInEnableTouchScrolling);` — `UFUNCTION(Category = "Scroll")`
- L206 _public prototype_ `bool GetIsTouchScrollingEnabled() const;`
- L209 _public prototype_ `bool GetConsumePointerInput() const;` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L212 _public prototype_ `void SetConsumePointerInput(bool bInConsumePointerInput);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L215 _public prototype_ `void SetScrollWhenFocusChanges(EScrollWhenFocusChanges NewScrollWhenFocusChanges);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L217 _public prototype_ `EScrollWhenFocusChanges GetScrollWhenFocusChanges() const;`
- L220 _public prototype_ `void SetNavigationDestination(const EDescendantScrollDestination NewNavigationDestination);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L222 _public prototype_ `EDescendantScrollDestination GetNavigationDestination() const;`
- L224 _public prototype_ `void SetAlwaysShowScrollbarTrack(bool NewAlwaysShowScrollbarTrack);`
- L226 _public prototype_ `bool IsAlwaysShowScrollbarTrack() const;`
- L228 _public prototype_ `float GetNavigationScrollPadding() const;`
- L230 _public prototype_ `void SetAllowRightClickDragScrolling(bool bShouldAllowRightClickDragScrolling);`
- L232 _public prototype_ `bool IsAllowRightClickDragScrolling() const;`
- L234 _public prototype_ `bool IsFrontPadScrolling() const;`
- L236 _public prototype_ `bool IsBackPadScrolling() const;`
- L240 _public prototype_ `void EndInertialScrolling();` — `UFUNCTION(BlueprintCallable, Category = "Scroll")` — Instantly stops any inertial scrolling that is currently in progress
- L243 _public prototype_ `FKey GetAnalogMouseWheelKey() const;` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L246 _public prototype_ `void SetAnalogMouseWheelKey(FKey InMouseWheelKey);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L249 _public prototype_ `bool GetIsFocusable() const;` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L252 _public prototype_ `void SetIsFocusable(bool bInIsFocusable);` — `UFUNCTION(BlueprintCallable, Category = "Scroll")`
- L258 _public member_ `FOnUserScrolledEvent OnUserScrolled;` — `UPROPERTY(BlueprintAssignable, Category = "Button|Event")` — Called when the scroll has changed
- L262 _public member_ `FOnScrollBarVisibilityChangedEvent OnScrollBarVisibilityChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Button|Event")` — Called when the scrollbar visibility has changed
- L266 _public member_ `FOnScrollBoxFocusReceivedEvent OnFocusReceived;` — `UPROPERTY(BlueprintAssignable, Category = "Scroll|Event")` — Called when the scroll has changed
- L270 _public member_ `FOnScrollBoxFocusLostEvent OnFocusLost;` — `UPROPERTY(BlueprintAssignable, Category = "Scroll|Event")` — Called when the scroll has changed
- L274 _public member_ `FOnScrollBoxFocusUpdatedEvent OnFocusUpdated;` — `UPROPERTY(BlueprintAssignable, Category = "Scroll|Event")` — Called when the focus of the scrollbox has changed
- L281 _public prototype_ `void SetScrollOffset(float NewScrollOffset);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Updates the scroll offset of the scrollbox. @param NewScrollOffset is in Slate Units.
- L287 _public prototype_ `float GetScrollOffset() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the scroll offset of the scrollbox in Slate Units.
- L293 _public prototype_ `float GetOverscrollOffset() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the overscroll offset of the scrollbox in Slate Units.
- L298 _public prototype_ `float GetOverscrollPercentage() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the overscroll offset of the scrollbox in percentage from its view size.
- L302 _public prototype_ `float GetScrollOffsetOfEnd() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the scroll offset of the bottom of the ScrollBox in Slate Units.
- L306 _public prototype_ `float GetViewFraction() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the fraction currently visible in the scrollbox
- L309 _public prototype_ `float GetViewOffsetFraction() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L313 _public prototype_ `void ScrollToStart();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Scrolls the ScrollBox to the top instantly
- L317 _public prototype_ `void ScrollToEnd();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Scrolls the ScrollBox to the bottom instantly during the next layout pass.
- L321 _public prototype_ `void ScrollWidgetIntoView(UWidget* WidgetToFind, bool AnimateScroll = true, EDescendantScrollDestination ScrollDestination = EDescendantScrollDestination::IntoView, float Padding = 0);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Scrolls the ScrollBox to the widget during the next layout pass.
- L325 _public prototype_ `bool GetIsScrolling() const;` — `UFUNCTION(BlueprintPure, Category="Widget")` — Returns true when the widget is currently inertial scrolling
- L328 _public prototype_ `virtual void SynchronizeProperties() override;`
- L332 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L337 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L343 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L344 _public prototype_ `virtual void OnDescendantSelectedByDesigner( UWidget* DescendantWidget ) override;`
- L345 _public prototype_ `virtual void OnDescendantDeselectedByDesigner( UWidget* DescendantWidget ) override;`
- L352 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L353 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L354 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L357 _protected prototype_ `void SlateHandleUserScrolled(float CurrentOffset);`
- L359 _protected prototype_ `void SlateHandleScrollBarVisibilityChanged(EVisibility NewVisibility);`
- L361 _protected prototype_ `void SlateHandleFocusReceived();`
- L363 _protected prototype_ `void SlateHandleFocusLost();`
- L365 _protected prototype_ `void SlateHandleFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath);`
- L368 _protected prototype_ `void InitBackPadScrolling(bool InBackPadScrolling);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L370 _protected prototype_ `void InitFrontPadScrolling(bool InFrontPadScrolling);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L372 _protected prototype_ `void InitNavigationScrollPadding(float InNavigationScrollPadding);` — Initialize IsFocusable in the constructor before the SWidget is constructed.
- L376 _protected member_ `float DesiredScrollOffset;` — The desired scroll offset for the underlying scrollbox.  This is a cache so that it can be set before the widget is constructed.
- L378 _protected member_ `TSharedPtr<class SScrollBox> MyScrollBox;`
- L382 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L386 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScrollBoxFocusReceivedEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScrollBoxFocusReceivedEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScrollBoxFocusLostEvent);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScrollBoxFocusLostEvent);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScrollBoxFocusUpdatedEvent, const UWidget*, ScrollBox, const bool, bFocused);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScrollBoxFocusUpdatedEvent, const UWidget*, ScrollBox, const bool, bFocused);`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserScrolledEvent, float, CurrentOffset);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserScrolledEvent, float, CurrentOffset);`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScrollBarVisibilityChangedEvent, ESlateVisibility , NewVisibility);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScrollBarVisibilityChangedEvent, ESlateVisibility , NewVisibility);`

### `Source/Runtime/UMG/Public/Components/ScrollBoxSlot.h` (Public)


#### class `UScrollBoxSlot`  
`class UScrollBoxSlot : public UPanelSlot`  
_L17-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UScrollBox, contains the widget that are scrollable
- L25 _private member_ `FSlateChildSize Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Layout|ScrollBox Slot", meta = (AllowPrivateAccess = "true", DisplayAfter = "Padding"))` — How much space this slot should occupy in the direction of the panel.
- L32 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Layout|ScrollBox Slot")` — The padding area between the slot and the content it contains.
- L37 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Layout|ScrollBox Slot")` — The alignment of the object horizontally.
- L42 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|ScrollBox Slot")` — The alignment of the object vertically.
- L46 _public prototype_ `FMargin GetPadding() const;`
- L49 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|ScrollBox Slot")`
- L51 _public prototype_ `FSlateChildSize GetSize() const;`
- L53 _public prototype_ `void SetSize(FSlateChildSize InSize);`
- L55 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L58 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|ScrollBox Slot")`
- L60 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L63 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Layout|ScrollBox Slot")`
- L68 _public prototype_ `virtual void SynchronizeProperties() override;`
- L72 _public prototype_ `void BuildSlot(TSharedRef<SScrollBox> ScrollBox);` — Builds the underlying FSlot for the Slate layout panel.
- L74 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L79 _private member_ `SScrollBox::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/SizeBox.h` (Public)


#### class `USizeBox`  
`class USizeBox : public UContentWidget`  
_L21-239_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- desc: A widget that allows you to specify the size it reports to have and desire.  Not all widgets report a desired size that you actually desire.  Wrapping them in a SizeBox lets you have the Size Box force them to be a particular size. * Single Child * Fixed Size
- L26 _protected member_ `TSharedPtr<SBox> MySizeBox;`
- L33 _public member_ `float WidthOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetWidthOverride", Category="Child Layout", meta=( editcondition="bOverride_WidthOverride" ))` — When specified, ignore the content's desired size and report the WidthOverride as the Box's desired width.
- L38 _public member_ `float HeightOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetHeightOverride", Category="Child Layout", meta=( editcondition="bOverride_HeightOverride" ))` — When specified, ignore the content's desired size and report the HeightOverride as the Box's desired height.
- L43 _public member_ `float MinDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinDesiredWidth", Category="Child Layout", meta=( editcondition="bOverride_MinDesiredWidth" ))` — When specified, will report the MinDesiredWidth if larger than the content's desired width.
- L48 _public member_ `float MinDesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinDesiredHeight", Category="Child Layout", meta=( editcondition="bOverride_MinDesiredHeight" ))` — When specified, will report the MinDesiredHeight if larger than the content's desired height.
- L53 _public member_ `float MaxDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMaxDesiredWidth", Category="Child Layout", meta=( editcondition="bOverride_MaxDesiredWidth" ))` — When specified, will report the MaxDesiredWidth if smaller than the content's desired width.
- L58 _public member_ `float MaxDesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMaxDesiredHeight", Category="Child Layout", meta=( editcondition="bOverride_MaxDesiredHeight" ))` — When specified, will report the MaxDesiredHeight if smaller than the content's desired height.
- L63 _public member_ `float MinAspectRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinAspectRatio", Category = "Child Layout", meta = (editcondition = "bOverride_MinAspectRatio"))`
- L68 _public member_ `float MaxAspectRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMaxAspectRatio", Category="Child Layout", meta=( editcondition="bOverride_MaxAspectRatio" ))`
- L73 _public member_ `uint8 bOverride_WidthOverride : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L78 _public member_ `uint8 bOverride_HeightOverride : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L83 _public member_ `uint8 bOverride_MinDesiredWidth : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L88 _public member_ `uint8 bOverride_MinDesiredHeight : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L93 _public member_ `uint8 bOverride_MaxDesiredWidth : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L98 _public member_ `uint8 bOverride_MaxDesiredHeight : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L103 _public member_ `uint8 bOverride_MinAspectRatio : 1;` — `UPROPERTY(EditAnywhere, Category="Child Layout", meta=(InlineEditConditionToggle))`
- L108 _public member_ `uint8 bOverride_MaxAspectRatio : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta=(InlineEditConditionToggle))`
- L114 _public prototype_ `float GetWidthOverride() const;`
- L117 _public prototype_ `bool IsWidthOverride() const;`
- L121 _public prototype_ `void SetWidthOverride(float InWidthOverride);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, ignore the content's desired size and report the WidthOverride as the Box's desired width.
- L124 _public prototype_ `void ClearWidthOverride();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L127 _public prototype_ `float GetHeightOverride() const;`
- L130 _public prototype_ `bool IsHeightOverride() const;`
- L134 _public prototype_ `void SetHeightOverride(float InHeightOverride);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, ignore the content's desired size and report the HeightOverride as the Box's desired height.
- L137 _public prototype_ `void ClearHeightOverride();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L140 _public prototype_ `float GetMinDesiredWidth() const;`
- L143 _public prototype_ `bool IsMinDesiredWidthOverride() const;`
- L147 _public prototype_ `void SetMinDesiredWidth(float InMinDesiredWidth);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, will report the MinDesiredWidth if larger than the content's desired width.
- L150 _public prototype_ `void ClearMinDesiredWidth();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L153 _public prototype_ `float GetMinDesiredHeight() const;`
- L156 _public prototype_ `bool IsMinDesiredHeightOverride() const;`
- L160 _public prototype_ `void SetMinDesiredHeight(float InMinDesiredHeight);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, will report the MinDesiredHeight if larger than the content's desired height.
- L163 _public prototype_ `void ClearMinDesiredHeight();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L166 _public prototype_ `float GetMaxDesiredWidth() const;`
- L169 _public prototype_ `bool IsMaxDesiredWidthOverride() const;`
- L173 _public prototype_ `void SetMaxDesiredWidth(float InMaxDesiredWidth);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, will report the MaxDesiredWidth if smaller than the content's desired width.
- L176 _public prototype_ `void ClearMaxDesiredWidth();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L179 _public prototype_ `float GetMaxDesiredHeight() const;`
- L182 _public prototype_ `bool IsMaxDesiredHeightOverride() const;`
- L186 _public prototype_ `void SetMaxDesiredHeight(float InMaxDesiredHeight);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")` — When specified, will report the MaxDesiredHeight if smaller than the content's desired height.
- L189 _public prototype_ `void ClearMaxDesiredHeight();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L192 _public prototype_ `float GetMinAspectRatio() const;`
- L195 _public prototype_ `bool IsMinAspectRatioOverride() const;`
- L198 _public prototype_ `void SetMinAspectRatio(float InMinAspectRatio);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L201 _public prototype_ `void ClearMinAspectRatio();` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L204 _public prototype_ `float GetMaxAspectRatio() const;`
- L207 _public prototype_ `bool IsMaxAspectRatioOverride() const;`
- L210 _public prototype_ `void SetMaxAspectRatio(float InMaxAspectRatio);` — `UFUNCTION(BlueprintCallable, Category="Layout|Size Box")`
- L213 _public prototype_ `void ClearMaxAspectRatio();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L217 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L221 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L225 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L231 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L232 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L233 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L237 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/SizeBoxComponent.h` (Public)


#### class `USizeBoxComponent`  
`class USizeBoxComponent : public UUIComponent`  
_L16-223_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UUIComponent`
- desc: This is a class for a Component that wraps the Owner widget with a Size Box.
- L23 _public prototype_ `float GetWidthOverride() const;`
- L26 _public prototype_ `bool IsWidthOverride() const;`
- L29 _public prototype_ `void SetWidthOverride(float InWidthOverride);` — When specified, ignore the content's desired size and report the WidthOverride as the Box's desired width.
- L32 _public prototype_ `void ClearWidthOverride();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L35 _public prototype_ `float GetHeightOverride() const;`
- L38 _public prototype_ `bool IsHeightOverride() const;`
- L41 _public prototype_ `void SetHeightOverride(float InHeightOverride);` — When specified, ignore the content's desired size and report the HeightOverride as the Box's desired height.
- L44 _public prototype_ `void ClearHeightOverride();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L47 _public prototype_ `float GetMinDesiredWidth() const;`
- L50 _public prototype_ `bool IsMinDesiredWidthOverride() const;`
- L53 _public prototype_ `void SetMinDesiredWidth(float InMinDesiredWidth);` — When specified, will report the MinDesiredWidth if larger than the content's desired width.
- L56 _public prototype_ `void ClearMinDesiredWidth();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L59 _public prototype_ `float GetMinDesiredHeight() const;`
- L62 _public prototype_ `bool IsMinDesiredHeightOverride() const;`
- L65 _public prototype_ `void SetMinDesiredHeight(float InMinDesiredHeight);` — When specified, will report the MinDesiredHeight if larger than the content's desired height.
- L68 _public prototype_ `void ClearMinDesiredHeight();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L71 _public prototype_ `float GetMaxDesiredWidth() const;`
- L74 _public prototype_ `bool IsMaxDesiredWidthOverride() const;`
- L77 _public prototype_ `void SetMaxDesiredWidth(float InMaxDesiredWidth);` — When specified, will report the MaxDesiredWidth if smaller than the content's desired width.
- L80 _public prototype_ `void ClearMaxDesiredWidth();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L83 _public prototype_ `float GetMaxDesiredHeight() const;`
- L86 _public prototype_ `bool IsMaxDesiredHeightOverride() const;`
- L89 _public prototype_ `void SetMaxDesiredHeight(float InMaxDesiredHeight);` — When specified, will report the MaxDesiredHeight if smaller than the content's desired height.
- L92 _public prototype_ `void ClearMaxDesiredHeight();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L95 _public prototype_ `float GetMinAspectRatio() const;`
- L98 _public prototype_ `bool IsMinAspectRatioOverride() const;`
- L100 _public prototype_ `void SetMinAspectRatio(float InMinAspectRatio);`
- L103 _public prototype_ `void ClearMinAspectRatio();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L106 _public prototype_ `float GetMaxAspectRatio() const;`
- L109 _public prototype_ `bool IsMaxAspectRatioOverride() const;`
- L111 _public prototype_ `void SetMaxAspectRatio(float InMaxAspectRatio);`
- L114 _public prototype_ `void ClearMaxAspectRatio();` — `UFUNCTION(BlueprintCallable, Category = "Layout|Size Box")`
- L118 _public prototype_ `FMargin GetPadding() const;`
- L120 _public prototype_ `void SetPadding(FMargin InPadding);`
- L122 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L124 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);`
- L126 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L128 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);`
- L132 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L136 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidgetWithContent(const TSharedRef<SWidget> OwnerContent) override;`
- L140 _private prototype_ `void SynchronizeProperties(TSharedRef<SBox> SizeBox);`
- L146 _private member_ `FMargin Padding = FMargin(0.f, 0.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Size Box Slot", meta = (AllowPrivateAccess = true))` — This property is for the Widget that owns this Component. The padding area between the slot and the content it contains.
- L150 _private member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Size Box Slot", meta = (AllowPrivateAccess = true))` — This property is for the Widget that owns this Component. The alignment of the object horizontally.
- L154 _private member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Size Box Slot", meta = (AllowPrivateAccess = true))` — This property is for the Widget that owns this Component. The alignment of the object vertically.
- L160 _private member_ `float WidthOverride = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_WidthOverride", AllowPrivateAccess = true))` — When specified, ignore the content's desired size and report the WidthOverride as the Box's desired width.
- L164 _private member_ `float HeightOverride = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_HeightOverride", AllowPrivateAccess = true))` — When specified, ignore the content's desired size and report the HeightOverride as the Box's desired height.
- L168 _private member_ `float MinDesiredWidth = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MinDesiredWidth", AllowPrivateAccess = true))` — When specified, will report the MinDesiredWidth if larger than the content's desired width.
- L172 _private member_ `float MinDesiredHeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MinDesiredHeight", AllowPrivateAccess = true))` — When specified, will report the MinDesiredHeight if larger than the content's desired height.
- L176 _private member_ `float MaxDesiredWidth = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MaxDesiredWidth", AllowPrivateAccess = true))` — When specified, will report the MaxDesiredWidth if smaller than the content's desired width.
- L180 _private member_ `float MaxDesiredHeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MaxDesiredHeight", AllowPrivateAccess = true))` — When specified, will report the MaxDesiredHeight if smaller than the content's desired height.
- L184 _private member_ `float MinAspectRatio = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MinAspectRatio", AllowPrivateAccess = true))`
- L188 _private member_ `float MaxAspectRatio = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Child Layout", meta = (editcondition = "bOverride_MaxAspectRatio", AllowPrivateAccess = true))`
- L192 _private member_ `uint8 bOverride_WidthOverride : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L196 _private member_ `uint8 bOverride_HeightOverride : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L200 _private member_ `uint8 bOverride_MinDesiredWidth : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L204 _private member_ `uint8 bOverride_MinDesiredHeight : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L208 _private member_ `uint8 bOverride_MaxDesiredWidth : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L212 _private member_ `uint8 bOverride_MaxDesiredHeight : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L216 _private member_ `uint8 bOverride_MinAspectRatio : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L220 _private member_ `uint8 bOverride_MaxAspectRatio : 1;` — `UPROPERTY(EditAnywhere, Category = "Child Layout", meta = (InlineEditConditionToggle, AllowPrivateAccess = true))`
- L222 _private member_ `TWeakPtr<SBox> MySizeBox;`

### `Source/Runtime/UMG/Public/Components/SizeBoxSlot.h` (Public)


#### class `USizeBoxSlot`  
`class USizeBoxSlot : public UPanelSlot`  
_L17-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the USizeBoxSlot, contains the widget displayed in a button's single slot
- L25 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|SizeBox Slot")` — The padding area between the slot and the content it contains.
- L29 _private member_ `TWeakPtr<SBox> SizeBox;` — A pointer to the button to allow us to adjust the size, padding...etc at runtime.
- L35 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|SizeBox Slot")` — The alignment of the object horizontally.
- L40 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|SizeBox Slot")` — The alignment of the object vertically.
- L44 _public prototype_ `FMargin GetPadding() const;`
- L47 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|SizeBox Slot")`
- L49 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L52 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|SizeBox Slot")`
- L54 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L57 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|SizeBox Slot")`
- L62 _public prototype_ `virtual void SynchronizeProperties() override;`
- L66 _public prototype_ `void BuildSlot(TSharedRef<SBox> InSizeBox);` — Builds the underlying slot for the slate SizeBox.
- L68 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`

### `Source/Runtime/UMG/Public/Components/SlateWrapperTypes.h` (Public)


#### enum `ESlateVisibility`  
`enum class ESlateVisibility : uint8`  
_L21-33_
- reflection: `UENUM(BlueprintType)`
- desc: Is an entity visible?
- L24 _public enumerator_ `Visible` — Visible and hit-testable (can interact with cursor). Default value.
- L26 _public enumerator_ `Collapsed` — Not visible and takes up no space in the layout (obviously not hit-testable).
- L28 _public enumerator_ `Hidden` — Not visible but occupies layout space (obviously not hit-testable).
- L30 _public enumerator_ `HitTestInvisible UMETA(DisplayName = "Not Hit-Testable (Self & All Children)")` — Visible but not hit-testable (cannot interact with cursor) and children in the hierarchy (if any) are also not hit-testable.
- L32 _public enumerator_ `SelfHitTestInvisible UMETA(DisplayName = "Not Hit-Testable (Self Only)")` — Visible but not hit-testable (cannot interact with cursor) and doesn't affect hit-testing on children (if any).

#### enum `ESlateAccessibleBehavior`  
`enum class ESlateAccessibleBehavior : uint8`  
_L37-54_
- reflection: `UENUM(BlueprintType)`
- desc: Whether a widget should be included in accessibility, and if so, how its text should be retrieved.
- L40 _public enumerator_ `NotAccessible` — Not accessible.
- L47 _public enumerator_ `Auto` — Accessible, first checking to see if there's any custom default text assigned for widgets of this type. If not, then it will attempt to use the alternate behavior (ie AccessibleSummaryBehavior instead of AccessibleBehavior) and return that value instead. This acts as a reference so that you only need to set one value for both of them to return the same thing.
- L49 _public enumerator_ `Summary` — Accessible, and traverse all child widgets and concat their AccessibleSummaryText together.
- L51 _public enumerator_ `Custom` — Accessible, and retrieve manually-assigned text from a TAttribute.
- L53 _public enumerator_ `ToolTip` — Accessible, and use the tooltip's accessible text.

#### class `USlateAccessibleWidgetData`  
`class USlateAccessibleWidgetData : public UObject`  
_L61-109_
- reflection: `UCLASS(DefaultToInstanced)`
- inherits: `UObject`
- desc: A container for all accessible properties for a UWidget that will be passed to the underlying SWidget. Any property here must also be added to UWidget.h and synchronized. See UWidget for more information.
- L66 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetText);`
- L68 _public function_ `USlateAccessibleWidgetData()`
- L75 _public function_ `TAttribute<FText> CreateAccessibleTextAttribute()`
- L82 _public function_ `TAttribute<FText> CreateAccessibleSummaryTextAttribute()`
- L90 _public member_ `bool bCanChildrenBeAccessible;` — `UPROPERTY()`
- L93 _public member_ `ESlateAccessibleBehavior AccessibleBehavior;` — `UPROPERTY()`
- L96 _public member_ `ESlateAccessibleBehavior AccessibleSummaryBehavior;` — `UPROPERTY()`
- L99 _public member_ `FText AccessibleText;` — `UPROPERTY()`
- L102 _public member_ `FGetText AccessibleTextDelegate;` — `UPROPERTY()`
- L105 _public member_ `FText AccessibleSummaryText;` — `UPROPERTY()`
- L108 _public member_ `FGetText AccessibleSummaryTextDelegate;` — `UPROPERTY()`

#### enum `ESlateSizeRule::Type`  
`enum Type : int`  
_L115-121_
- L118 _public enumerator_ `Automatic` — Only requests as much room as it needs based on the widgets desired size.
- L120 _public enumerator_ `Fill` — Greedily attempts to fill all available room based on the percentage value 0..1

#### struct `FEventReply`  
`struct FEventReply`  
_L128-142_
- reflection: `USTRUCT(BlueprintType)`
- desc: Allows users to handle events and return information to the underlying UI layer.
- L134 _public function_ `FEventReply(bool IsHandled = false) : NativeReply(IsHandled ? FReply::Handled() : FReply::Unhandled())`
- L139 _public function_ `bool operator==(const FEventReply& Other) const`
- L141 _public member_ `FReply NativeReply;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FEventReply> : public TStructOpsTypeTraitsBase2<FEventReply>`  
_L145-151_
- inherits: `TStructOpsTypeTraitsBase2<FEventReply>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L148-150_

#### struct `FSlateChildSize`  
`struct FSlateChildSize`  
_L155-178_
- reflection: `USTRUCT(BlueprintType)`
- desc: A struct exposing size param related properties to UMG.
- L161 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta=( UIMin="0", UIMax="1" ))` — The parameter of the size rule.
- L165 _public member_ `TEnumAsByte<ESlateSizeRule::Type> SizeRule;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — The sizing rule of the content.
- L167 _public function_ `FSlateChildSize() : Value(1.0f) , SizeRule(ESlateSizeRule::Fill)`
- L173 _public function_ `FSlateChildSize(ESlateSizeRule::Type InSizeRule) : Value(1.0f) , SizeRule(InSizeRule)`

#### enum `EVirtualKeyboardType::Type`  
`enum Type : int`  
_L184-192_
- L186 _public enumerator_ `Default`
- L187 _public enumerator_ `Number`
- L188 _public enumerator_ `Web`
- L189 _public enumerator_ `Email`
- L190 _public enumerator_ `Password`
- L191 _public enumerator_ `AlphaNumeric`

#### Free symbols / members of external scopes

- L13 _macro_ `#define BIND_UOBJECT_ATTRIBUTE(Type, Function) \`
- L16 _macro_ `#define BIND_UOBJECT_DELEGATE(Type, Function) \`
- L66 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetText);`
- L113 _namespace_ `namespace ESlateSizeRule`
- L149 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon6389e9690103`)
- L182 _namespace_ `namespace EVirtualKeyboardType`
- L195 _namespace_ `namespace EVirtualKeyboardType`
- L197 _function_ `inline EKeyboardType AsKeyboardType( Type InType )` (scope `EVirtualKeyboardType`)

### `Source/Runtime/UMG/Public/Components/Slider.h` (Public)


#### class `USlider`  
`class USlider : public UWidget`  
_L26-228_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a sliding bar with a handle that allows you to control the value in a user define range (between 0..1 by default). * No Children
- L34 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, FieldNotify, BlueprintGetter="GetValue", BlueprintSetter="SetValue", Category="Appearance", meta=(UIMin="0", UIMax="1"))` — The volume value to display.
- L38 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L43 _public member_ `float MinValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinValue", Category="Appearance")` — The minimum value the slider can be set to.
- L48 _public member_ `float MaxValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMaxValue", Category="Appearance")` — The maximum value the slider can be set to.
- L54 _public member_ `FSliderStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Style" ))` — The progress bar style
- L59 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Appearance)` — The slider's orientation.
- L64 _public member_ `FLinearColor SliderBarColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetSliderBarColor", Category="Appearance")` — The color to draw the slider bar in.
- L69 _public member_ `FLinearColor SliderHandleColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetSliderHandleColor", Category="Appearance")` — The color to draw the slider handle in.
- L74 _public member_ `bool IndentHandle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="HasIndentHandle", Setter, BlueprintSetter="SetIndentHandle", Category="Appearance", AdvancedDisplay)` — Whether the slidable area should be indented to fit the handle.
- L79 _public member_ `bool Locked;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="IsLocked", Setter, BlueprintSetter="SetLocked", Category="Appearance", AdvancedDisplay)` — Whether the handle is interactive or fixed.
- L83 _public member_ `bool MouseUsesStep;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)` — Sets new value if mouse position is greater/less than half the step size.
- L87 _public member_ `bool RequiresControllerLock;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)` — Sets whether we have to lock input to change the slider value.
- L92 _public member_ `float StepSize;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetStepSize", Category="Appearance", meta=(UIMin="0", UIMax="1"))` — The amount to adjust the value by, when using a controller or keyboard
- L96 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — Should the slider be focusable?
- L100 _public member_ `bool bPreventThrottling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — If refresh requests for the viewport should happen for all value changes
- L106 _public member_ `FOnMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is pressed and a capture begins.
- L110 _public member_ `FOnMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is released and a capture ends.
- L114 _public member_ `FOnControllerCaptureBeginEvent OnControllerCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture begins.
- L118 _public member_ `FOnControllerCaptureEndEvent OnControllerCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture ends.
- L122 _public member_ `FOnFloatValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Called when the value is changed by slider or typing.
- L126 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Gets the current value of the slider.
- L130 _public prototype_ `float GetNormalizedValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Get the current value scaled from 0 to 1
- L134 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the current value of the slider.
- L137 _public prototype_ `float GetMinValue() const;` — Gets the minimum value of the slider.
- L141 _public prototype_ `void SetMinValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the minimum value of the slider.
- L144 _public prototype_ `float GetMaxValue() const;` — Gets the maximum value of the slider.
- L148 _public prototype_ `void SetMaxValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the maximum value of the slider.
- L151 _public prototype_ `const FSliderStyle& GetWidgetStyle() const;` — Get the style used by the widget.
- L154 _public prototype_ `void SetWidgetStyle(const FSliderStyle& InStyle);` — Set the style used by the widget.
- L157 _public prototype_ `EOrientation GetOrientation() const;` — Getg the slider's orientation.
- L160 _public prototype_ `void SetOrientation(EOrientation InOrientation);` — Sets the slider's orientation.
- L163 _public prototype_ `bool HasIndentHandle() const;` — Gets if the slidable area should be indented to fit the handle.
- L167 _public prototype_ `void SetIndentHandle(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets if the slidable area should be indented to fit the handle.
- L170 _public prototype_ `bool IsLocked() const;` — Returns true when the handle is fixed.
- L174 _public prototype_ `void SetLocked(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the handle to be interactive or fixed.
- L177 _public prototype_ `float GetStepSize() const;` — Gets the amount to adjust the value by.
- L181 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the amount to adjust the value by, when using a controller or keyboard.
- L184 _public prototype_ `FLinearColor GetSliderBarColor() const;` — Gets the color of the slider bar.
- L188 _public prototype_ `void SetSliderBarColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the slider bar.
- L191 _public prototype_ `FLinearColor GetSliderHandleColor() const;` — Gets the color of the handle bar
- L195 _public prototype_ `void SetSliderHandleColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the handle bar
- L198 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L202 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L206 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L211 _protected member_ `TSharedPtr<SSlider> MySlider;` — Native Slate Widget
- L214 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L217 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L218 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L219 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L220 _protected prototype_ `void HandleOnControllerCaptureBegin();`
- L221 _protected prototype_ `void HandleOnControllerCaptureEnd();`
- L224 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L227 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureBeginEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureBeginEvent);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureEndEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureEndEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureBeginEvent);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureBeginEvent);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureEndEvent);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureEndEvent);`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedEvent, float, Value);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedEvent, float, Value);`

### `Source/Runtime/UMG/Public/Components/Spacer.h` (Public)


#### class `USpacer`  
`class USpacer : public UWidget`  
_L19-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A spacer widget; it does not have a visual representation, and just provides padding between other widgets. * No Children
- L28 _public member_ `FVector2D Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetSize", Category="Appearance")` — The size of the spacer
- L33 _public prototype_ `FVector2D GetSize() const;`
- L37 _public prototype_ `void SetSize(FVector2D InSize);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the size of the spacer
- L40 _public prototype_ `virtual void SynchronizeProperties() override;`
- L41 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L45 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L50 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L54 _protected member_ `TSharedPtr<SSpacer> MySpacer;`

### `Source/Runtime/UMG/Public/Components/SpinBox.h` (Public)


#### class `USpinBox`  
`class USpinBox : public UWidget`  
_L19-342_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A numerical entry box that allows for direct entry of the number or allows the user to click and slide the number.
- L24 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpinBoxValueChangedEvent, float, InValue);`
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpinBoxValueCommittedEvent, float, InValue, ETextCommit::Type, CommitMethod);`
- L26 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpinBoxBeginSliderMovement);`
- L33 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetValue", BlueprintGetter = "GetValue", FieldNotify, Category = Content)` — Value stored in this spin box
- L37 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L43 _public member_ `FSpinBoxStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Style", meta=( DisplayName="Style" ))` — The Style
- L48 _public member_ `int32 MinFractionalDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetMinFractionalDigits, BlueprintGetter = GetMinFractionalDigits, Category = "Slider", meta = (ClampMin = 0, UIMin = 0))` — The minimum required fractional digits - default 1
- L53 _public member_ `int32 MaxFractionalDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetMaxFractionalDigits, BlueprintGetter = GetMaxFractionalDigits, Category = "Slider", meta = (ClampMin = 0, UIMin = 0))` — The maximum required fractional digits - default 6
- L58 _public member_ `bool bAlwaysUsesDeltaSnap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = GetAlwaysUsesDeltaSnap, Setter = SetAlwaysUsesDeltaSnap, BlueprintSetter = SetAlwaysUsesDeltaSnap, BlueprintGetter = GetAlwaysUsesDeltaSnap, Category = "Slider")` — Whether this spin box should use the delta snapping logic for typed values - default false
- L63 _public member_ `bool bEnableSlider = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetEnableSlider", Setter = "SetEnableSlider", Category = "Slider")` — Whether this spin box should have slider feature enabled
- L68 _public member_ `float Delta;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetDelta, BlueprintGetter = GetDelta, Category = "Slider")` — The amount by which to change the spin box value as the slider moves.
- L73 _public member_ `float SliderExponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Slider")` — The exponent by which to increase the delta as the mouse moves. 1 is constant (never increases the delta).
- L78 _public member_ `FSlateFontInfo Font;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Display")` — Font color and opacity (overrides style)
- L83 _public member_ `TEnumAsByte<ETextJustify::Type> Justification;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Display")` — The justification the value text should appear as.
- L88 _public member_ `float MinDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Display", AdvancedDisplay, DisplayName = "Minimum Desired Width")` — The minimum width of the spin box
- L92 _public member_ `TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;` — `UPROPERTY(EditAnywhere, Category = "Input", AdvancedDisplay)` — If we're on a platform that requires a virtual keyboard, what kind of keyboard should this widget use?
- L96 _public member_ `EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;` — `UPROPERTY(EditAnywhere, Category = Behavior, AdvancedDisplay)` — What action should be taken when the virtual keyboard is dismissed?
- L101 _public member_ `bool ClearKeyboardFocusOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Input", AdvancedDisplay)` — Whether to remove the keyboard focus from the spin box when the value is committed
- L106 _public member_ `bool SelectAllTextOnCommit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Input", AdvancedDisplay)` — Whether to select the text in the spin box when the value is committed
- L110 _public member_ `FSlateColor ForegroundColor;` — `UE_DEPRECATED(5.2, "Direct access to ForegroundColor is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetForegroundColor", Category = "Style")`
- L115 _public member_ `FOnSpinBoxValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category="SpinBox|Events")` — Called when the value is changed interactively by the user
- L119 _public member_ `FOnSpinBoxValueCommittedEvent OnValueCommitted;` — `UPROPERTY(BlueprintAssignable, Category="SpinBox|Events")` — Called when the value is committed. Occurs when the user presses Enter or the text box loses focus.
- L123 _public member_ `FOnSpinBoxBeginSliderMovement OnBeginSliderMovement;` — `UPROPERTY(BlueprintAssignable, Category="SpinBox|Events")` — Called right before the slider begins to move
- L127 _public member_ `FOnSpinBoxValueChangedEvent OnEndSliderMovement;` — `UPROPERTY(BlueprintAssignable, Category="SpinBox|Events")` — Called right after the slider handle is released by the user
- L133 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Get the current value of the spin box.
- L137 _public prototype_ `void SetValue(float NewValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Set the value of the spin box.
- L142 _public prototype_ `const FSpinBoxStyle& GetWidgetStyle() const;` — Set the style for the spin box.
- L145 _public prototype_ `void SetWidgetStyle(const FSpinBoxStyle& InWidgetStyle);` — Get the style for the spin box.
- L149 _public prototype_ `int32 GetMinFractionalDigits() const;` — `UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "Behavior")` — Get the current Min Fractional Digits for the spin box.
- L153 _public prototype_ `void SetMinFractionalDigits(int32 NewValue);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Behavior")` — Set the Min Fractional Digits for the spin box.
- L157 _public prototype_ `int32 GetMaxFractionalDigits() const;` — `UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "Behavior")` — Get the current Max Fractional Digits for the spin box.
- L161 _public prototype_ `void SetMaxFractionalDigits(int32 NewValue);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Behavior")` — Set the Max Fractional Digits for the spin box.
- L165 _public prototype_ `bool GetAlwaysUsesDeltaSnap() const;` — `UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "Behavior")` — Get whether the spin box uses delta snap on type.
- L169 _public prototype_ `void SetAlwaysUsesDeltaSnap(bool bNewValue);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Behavior")` — Set whether the spin box uses delta snap on type.
- L172 _public prototype_ `bool GetEnableSlider() const;` — Get whether the spin box uses the slider feature.
- L175 _public prototype_ `void SetEnableSlider(bool bNewValue);` — Set whether the spin box uses the slider feature.
- L179 _public prototype_ `float GetDelta() const;` — `UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "Behavior")` — Get the current delta for the spin box.
- L183 _public prototype_ `void SetDelta(float NewValue);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Behavior")` — Set the delta for the spin box.
- L186 _public prototype_ `float GetSliderExponent() const;` — Get the current slider exponent for the spin box.
- L189 _public prototype_ `void SetSliderExponent(float NewValue);` — Set the slider exponent for the spin box.
- L192 _public prototype_ `const FSlateFontInfo& GetFont() const;` — Get the font color and opacity that overrides the style font.
- L195 _public prototype_ `void SetFont(const FSlateFontInfo& InFont);` — Set the font color and opacity that overrides the style font.
- L198 _public prototype_ `const ETextJustify::Type GetJustification() const;` — Get the justification for value text.
- L201 _public prototype_ `void SetJustification(ETextJustify::Type InJustification);` — Set the justification for value text.
- L204 _public prototype_ `float GetMinDesiredWidth() const;` — Get the minimum width of the spin box.
- L207 _public prototype_ `void SetMinDesiredWidth(float NewValue);` — Set the minimum width of the spin box.
- L210 _public prototype_ `bool GetClearKeyboardFocusOnCommit() const;` — Get whether the keyboard focus is removed from the spin box when the value is committed.
- L213 _public prototype_ `void SetClearKeyboardFocusOnCommit(bool bNewValue);` — Set whether the keyboard focus is removed from the spin box when the value is committed.
- L216 _public prototype_ `bool GetSelectAllTextOnCommit() const;` — Get whether to select the text in the spin box when the value is committed.
- L219 _public prototype_ `void SetSelectAllTextOnCommit(bool bNewValue);` — Set whether to select the text in the spin box when the value is committed.
- L223 _public prototype_ `float GetMinValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Get the current minimum value that can be manually set in the spin box.
- L227 _public prototype_ `void SetMinValue(float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set the minimum value that can be manually set in the spin box.
- L231 _public prototype_ `void ClearMinValue();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Clear the minimum value that can be manually set in the spin box.
- L235 _public prototype_ `float GetMaxValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Get the current maximum value that can be manually set in the spin box.
- L239 _public prototype_ `void SetMaxValue(float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set the maximum value that can be manually set in the spin box.
- L243 _public prototype_ `void ClearMaxValue();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Clear the maximum value that can be manually set in the spin box.
- L247 _public prototype_ `float GetMinSliderValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Get the current minimum value that can be specified using the slider.
- L251 _public prototype_ `void SetMinSliderValue(float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set the minimum value that can be specified using the slider.
- L255 _public prototype_ `void ClearMinSliderValue();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Clear the minimum value that can be specified using the slider.
- L259 _public prototype_ `float GetMaxSliderValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Get the current maximum value that can be specified using the slider.
- L263 _public prototype_ `void SetMaxSliderValue(float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set the maximum value that can be specified using the slider.
- L267 _public prototype_ `void ClearMaxSliderValue();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Clear the maximum value that can be specified using the slider.
- L271 _public prototype_ `void SetForegroundColor(FSlateColor InForegroundColor);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L274 _public prototype_ `FSlateColor GetForegroundColor() const;` — Get the foreground color of the spin box.
- L279 _public prototype_ `virtual void SynchronizeProperties() override;`
- L283 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L287 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L293 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L296 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L297 _protected prototype_ `void HandleOnValueCommitted(float InValue, ETextCommit::Type CommitMethod);`
- L298 _protected prototype_ `void HandleOnBeginSliderMovement();`
- L299 _protected prototype_ `void HandleOnEndSliderMovement(float InValue);`
- L304 _protected member_ `uint32 bOverride_MinValue : 1;` — `UPROPERTY(EditAnywhere, Category = Content, meta = (InlineEditConditionToggle))` — Whether the optional MinValue attribute of the widget is set
- L308 _protected member_ `uint32 bOverride_MaxValue : 1;` — `UPROPERTY(EditAnywhere, Category = Content, meta=(InlineEditConditionToggle))` — Whether the optional MaxValue attribute of the widget is set
- L312 _protected member_ `uint32 bOverride_MinSliderValue : 1;` — `UPROPERTY(EditAnywhere, Category = Content, meta = (InlineEditConditionToggle))` — Whether the optional MinSliderValue attribute of the widget is set
- L316 _protected member_ `uint32 bOverride_MaxSliderValue : 1;` — `UPROPERTY(EditAnywhere, Category = Content, meta=(InlineEditConditionToggle))` — Whether the optional MaxSliderValue attribute of the widget is set
- L321 _protected member_ `float MinValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetMinValue", BlueprintGetter = "GetMinValue", Category = Content, DisplayName = "Minimum Value", meta = (editcondition = "bOverride_MinValue"))` — The minimum allowable value that can be manually entered into the spin box
- L326 _protected member_ `float MaxValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetMaxValue", BlueprintGetter = "GetMaxValue", Category = Content, DisplayName = "Maximum Value", meta = (editcondition = "bOverride_MaxValue"))` — The maximum allowable value that can be manually entered into the spin box
- L331 _protected member_ `float MinSliderValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetMinSliderValue", BlueprintGetter = "GetMinSliderValue", Category = Content, DisplayName = "Minimum Slider Value", meta = (editcondition = "bOverride_MinSliderValue"))` — The minimum allowable value that can be specified using the slider
- L336 _protected member_ `float MaxSliderValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetMaxSliderValue", BlueprintGetter = "GetMaxSliderValue", Category = Content, DisplayName = "Maximum Slider Value", meta = (editcondition = "bOverride_MaxSliderValue"))` — The maximum allowable value that can be specified using the slider
- L339 _protected member_ `TSharedPtr<SSpinBox<float>> MySpinBox;`
- L341 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpinBoxValueChangedEvent, float, InValue);`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpinBoxValueCommittedEvent, float, InValue, ETextCommit::Type, CommitMethod);`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpinBoxBeginSliderMovement);`

### `Source/Runtime/UMG/Public/Components/StackBox.h` (Public)


#### class `UStackBox`  
`class UStackBox : public UPanelWidget`  
_L21-66_
- reflection: `UCLASS(meta = (ShortTooltip = "A layout panel for automatically laying child widgets out vertically or horizontally"), MinimalAPI)`
- inherits: `UPanelWidget`
- desc: A stack box widget is a layout panel allowing child widgets to be automatically laid out vertically or horizontally. * Many Children * Flows Vertical or Horizontal
- L26 _public prototype_ `UStackBox();`
- L31 _private member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category = "Behavior", meta = (AllowPrivateAccess = "true"))` — The orientation of the stack box.
- L35 _public prototype_ `EOrientation GetOrientation() const;` — Get the orientation of the stack box.
- L37 _public prototype_ `void SetOrientation(EOrientation InType);` — Set the orientation of the stack box. The existing elements will be rearranged.
- L41 _public prototype_ `UStackBoxSlot* AddChildToStackBox(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Panel")` — Adds a new child widget to the container.
- L45 _public prototype_ `bool ReplaceStackBoxChildAt(int32 Index, UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category = "Panel")` — Replace the widget at the given index it with a different widget.
- L49 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L55 _protected prototype_ `virtual UClass* GetSlotClass() const override;`
- L56 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L57 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L58 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L59 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L62 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L65 _private member_ `TSharedPtr<SStackBox> MyBox;`

### `Source/Runtime/UMG/Public/Components/StackBoxSlot.h` (Public)


#### class `UStackBoxSlot`  
`class UStackBoxSlot : public UPanelSlot`  
_L17-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UStackBox, contains the widget that is flowed vertically or horizontally.
- L24 _private member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Layout|Stack Box Slot", meta = (AllowPrivateAccess = "true"))` — The padding area between the slot and the content it contains.
- L28 _private member_ `FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Automatic);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category = "Layout|Stack Box Slot", meta = (AllowPrivateAccess = "true"))` — How much space this slot should occupy in the direction of the panel.
- L32 _private member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Layout|Stack Box Slot", meta = (AllowPrivateAccess = "true"))` — The alignment of the object horizontally.
- L36 _private member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Layout|Stack Box Slot", meta = (AllowPrivateAccess = "true"))` — The alignment of the object vertically.
- L40 _private member_ `SStackBox::FSlot* Slot = nullptr;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.
- L43 _public prototype_ `FMargin GetPadding() const;`
- L44 _public prototype_ `void SetPadding(FMargin InPadding);`
- L46 _public prototype_ `FSlateChildSize GetSize() const;`
- L47 _public prototype_ `void SetSize(FSlateChildSize InSize);`
- L49 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L50 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);`
- L52 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L53 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);`
- L57 _public prototype_ `virtual void SynchronizeProperties() override;`
- L60 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L63 _public prototype_ `void BuildSlot(TSharedRef<SStackBox> InBox);` — Builds the underlying FSlot for the Slate layout panel.
- L66 _public prototype_ `void ReplaceContent(UWidget* Content);` — Replace the slot content.
- L69 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L70 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`

### `Source/Runtime/UMG/Public/Components/TextBlock.h` (Public)


#### class `UTextBlock`  
`class UTextBlock : public UTextLayoutWidget`  
_L23-311_
- reflection: `UCLASS(meta=(DisplayName="Text"), MinimalAPI)`
- inherits: `UTextLayoutWidget`
- desc: A simple static text widget. * No Children * Text
- L31 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter="GetText", BlueprintSetter="SetText", Category="Content", meta = (MultiLine = "true"))` — The text to display
- L35 _public member_ `FGetText TextDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the text of the widget
- L40 _public member_ `FSlateColor ColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetColorAndOpacity", Category="Appearance")` — The color of the text
- L44 _public member_ `FGetSlateColor ColorAndOpacityDelegate;` — `UPROPERTY()` — A bindable delegate for the ColorAndOpacity.
- L49 _public member_ `float MinDesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinDesiredWidth", Category="Appearance")` — The minimum desired size for the text
- L54 _public member_ `FSlateFontInfo Font;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetFont", Category="Appearance")` — The font to render the text with
- L59 _public member_ `FSlateBrush StrikeBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetStrikeBrush", Category="Appearance")` — The brush to strike through text with
- L64 _public member_ `FVector2D ShadowOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetShadowOffset", Category="Appearance")` — The direction the shadow is cast
- L69 _public member_ `FLinearColor ShadowColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetShadowColorAndOpacity", Category="Appearance", meta=( DisplayName="Shadow Color" ))` — The color of the shadow
- L73 _public member_ `FGetLinearColor ShadowColorAndOpacityDelegate;` — `UPROPERTY()` — A bindable delegate for the ShadowColorAndOpacity.
- L77 _public member_ `bool bWrapWithInvalidationPanel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Performance", AdvancedDisplay)` — If true, it will automatically wrap this text widget with an invalidation panel
- L82 _public member_ `ETextTransformPolicy TextTransformPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetTextTransformPolicy", Category="Appearance", meta=(DisplayName="Transform Policy"))` — The text transformation policy to apply to this text block.
- L87 _public member_ `ETextOverflowPolicy TextOverflowPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetTextOverflowPolicy", Category="Clipping", AdvancedDisplay, meta = (DisplayName="Overflow Policy"))` — Sets what happens to text that is clipped and doesn't fit within the clip rect for this widget
- L95 _public prototype_ `FText GetText() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="GetText (Text)"))` — Gets the widget text @return The widget text
- L103 _public prototype_ `virtual void SetText(FText InText);` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="SetText (Text)"))` — Directly sets the widget text. Warning: This will wipe any binding created for the Text property! @param InText The text to assign to the widget
- L106 _public prototype_ `FSlateColor GetColorAndOpacity() const;` — @return the color and opacity of the text in this text block.
- L114 _public prototype_ `void SetColorAndOpacity(FSlateColor InColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color and opacity of the text in this text block @param InColorAndOpacity		The new text color and opacity
- L122 _public prototype_ `void SetOpacity(float InOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the opacity of the text in this text block @param InOpacity		The new text opacity
- L125 _public prototype_ `FLinearColor GetShadowColorAndOpacity() const;` — @return the color and opacity of the text drop shadow.
- L134 _public prototype_ `void SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color and opacity of the text drop shadow Note: if opacity is zero no shadow will be drawn @param InShadowColorAndOpacity		The new drop shadow color and opacity
- L137 _public prototype_ `FVector2D GetShadowOffset() const;` — @return the offset that the text drop shadow should be drawn at.
- L145 _public prototype_ `void SetShadowOffset(FVector2D InShadowOffset);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the offset that the text drop shadow should be drawn at @param InShadowOffset		The new offset
- L148 _public prototype_ `const FSlateFontInfo& GetFont() const;` — @return the font info for this text block.
- L156 _public prototype_ `void SetFont(FSlateFontInfo InFontInfo);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Dynamically set the font info for this text block @param InFontInfo The new font info
- L159 _public prototype_ `const FSlateBrush& GetStrikeBrush() const;` — @return the brush to use to strike through text.
- L167 _public prototype_ `void SetStrikeBrush(FSlateBrush InStrikeBrush);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Dynamically set the strike brush for this text block @param InStrikeBrush The new brush to use to strike through text
- L170 _public prototype_ `float GetMinDesiredWidth() const;` — @return the minimum desired width for this text block
- L178 _public prototype_ `void SetMinDesiredWidth(float InMinDesiredWidth);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Set the minimum desired width for this text block @param InMinDesiredWidth new minimum desired width
- L186 _public prototype_ `void SetAutoWrapText(bool InAutoTextWrap);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Set the auto wrap for this text block. @param InAutoTextWrap to turn wrap on or off.
- L189 _public prototype_ `ETextTransformPolicy GetTextTransformPolicy() const;` — @return the text transformation policy for this text block.
- L197 _public prototype_ `void SetTextTransformPolicy(ETextTransformPolicy InTransformPolicy);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Set the text transformation policy for this text block. @param InTransformPolicy the new text transformation policy.
- L200 _public prototype_ `ETextOverflowPolicy GetTextOverflowPolicy() const;` — @return the text overflow policy for this text block.
- L208 _public prototype_ `void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Set the text overflow policy for this text block. @param InOverflowPolicy the new text overflow policy.
- L211 _public prototype_ `void SetFontMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L214 _public prototype_ `void SetFontOutlineMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L222 _public prototype_ `void SetFontSize(float DisplayFontSize);` — `UFUNCTION(BlueprintCallable, Category="Appearance", meta=(ToolTip="DisplayFontSize should be set with respect to your Project settings for Font Resolution DPI. Updates to this value in your project will impact display of text blocks set with this value accordingly."))` — Set the font size of this text block directly, respecting project-specified font resolution DPI @param The display font size, at the intended DPI (generally 72)
- L230 _public prototype_ `float GetFontSize() const;` — `UFUNCTION(BlueprintCallable, Category="Appearance", meta=(ToolTip="Gets the font size of this text block, with respect to the current project settings for Font Resolution DPI."))` — Get the font size of this text block directly, respecting project-specified font resolution DPI @return The display font size, at the intended DPI (generally 72)
- L234 _public prototype_ `UMaterialInstanceDynamic* GetDynamicFontMaterial();` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L238 _public prototype_ `UMaterialInstanceDynamic* GetDynamicOutlineMaterial();` — `UFUNCTION(BlueprintCallable, Category="Appearance")`
- L241 _protected function_ `virtual void OnTextChanged()`
- L245 _protected function_ `virtual void OnFontChanged()`
- L251 _public prototype_ `virtual void SynchronizeProperties() override;`
- L255 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L260 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L261 _public prototype_ `virtual void OnCreationFromPalette() override;`
- L262 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L265 _public prototype_ `virtual FString GetLabelMetadata() const override;`
- L267 _public prototype_ `void HandleTextCommitted(const FText& InText, ETextCommit::Type CommitteType);`
- L272 _protected prototype_ `virtual void OnShapedTextOptionsChanged(FShapedTextOptions InShapedTextOptions) override;`
- L273 _protected prototype_ `virtual void OnJustificationChanged(ETextJustify::Type InJustification) override;`
- L274 _protected prototype_ `virtual void OnWrappingPolicyChanged(ETextWrappingPolicy InWrappingPolicy) override;`
- L275 _protected prototype_ `virtual void OnAutoWrapTextChanged(bool InAutoWrapText) override;`
- L276 _protected prototype_ `virtual void OnWrapTextAtChanged(float InWrapTextAt) override;`
- L277 _protected prototype_ `virtual void OnLineHeightPercentageChanged(float InLineHeightPercentage) override;`
- L278 _protected prototype_ `virtual void OnApplyLineHeightToBottomLineChanged(bool InApplyLineHeightToBottomLine) override;`
- L279 _protected prototype_ `virtual void OnMarginChanged(const FMargin& InMargin) override;`
- L288 _protected member_ `bool bSimpleTextMode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Performance, AdvancedDisplay, meta=(AllowPrivateAccess = "true", DesignerRebuild))` — If this is enabled, text shaping, wrapping, justification are disabled in favor of much faster text layout and measurement. This feature is only suitable for "simple" text (ie, text containing only numbers or basic ASCII) as it disables the complex text rendering support required for certain languages (such as Arabic and Thai). It is significantly faster for text that can take advantage of it (particularly if that text changes frequently), but shouldn't be used for localized user-facing text.
- L291 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L292 _protected prototype_ `virtual void OnBindingChanged(const FName& Property) override;`
- L296 _protected prototype_ `virtual TAttribute<FText> GetDisplayText();` — Get the text that should be displayed in the internal Slate widget (allows flags to mutate the display text without modifying the persistent designer property data)
- L298 _protected prototype_ `EVisibility GetTextWarningImageVisibility() const;`
- L301 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L306 _protected member_ `TSharedPtr<STextBlock> MyTextBlock;`
- L308 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, Text);`
- L309 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, ColorAndOpacity);`
- L310 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, ShadowColorAndOpacity);`

### `Source/Runtime/UMG/Public/Components/TextWidgetTypes.h` (Public)


#### struct `FShapedTextOptions`  
`struct FShapedTextOptions`  
_L20-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: Common data for all widgets that use shaped text. Contains the common options that should be exposed for the underlying Slate widget.
- L24 _public prototype_ `FShapedTextOptions();`
- L28 _public function_ `template <typename TWidgetType> void SynchronizeShapedTextProperties(TWidgetType& InWidget) const` — Synchronize the properties with the given widget. A template as the Slate widgets conform to the same API, but don't derive from a common base.
- L34 _public function_ `inline bool operator==(const FShapedTextOptions& Other) const`
- L42 _public function_ `inline bool operator!=(const FShapedTextOptions& Other) const`
- L49 _public member_ `uint8 bOverride_TextShapingMethod : 1;` — `UPROPERTY(EditAnywhere, Category=Localization, meta=(InlineEditConditionToggle))`
- L53 _public member_ `uint8 bOverride_TextFlowDirection : 1;` — `UPROPERTY(EditAnywhere, Category=Localization, meta=(InlineEditConditionToggle))`
- L57 _public member_ `ETextShapingMethod TextShapingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Localization, AdvancedDisplay, meta=(EditCondition="bOverride_TextShapingMethod"))` — Which text shaping method should the text within this widget use? (unset to use the default returned by GetDefaultTextShapingMethod)
- L61 _public member_ `ETextFlowDirection TextFlowDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Localization, AdvancedDisplay, meta=(EditCondition="bOverride_TextFlowDirection"))` — Which text flow direction should the text within this widget use? (unset to use the default returned by GetDefaultTextFlowDirection)

#### class `UTextLayoutWidget`  
`class UTextLayoutWidget : public UWidget`  
_L72-165_
- reflection: `UCLASS(Abstract, BlueprintType, MinimalAPI)`
- inherits: `UWidget`
- desc: Base class for all widgets that use a text layout. Contains the common options that should be exposed for the underlying Slate widget.
- L77 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnAllFontFacesFinishLoading_TextLayoutWidget, UTextLayoutWidget, OnAllFontFacesFinishLoading);`
- L79 _public function_ `bool GetAutoWrapText() const`
- L80 _public function_ `float GetWrapTextAt() const`
- L83 _public prototype_ `virtual void SetJustification(ETextJustify::Type InJustification);` — `UFUNCTION(BlueprintSetter)`
- L85 _public prototype_ `void SetShapedTextOptions(FShapedTextOptions InShapedTextOptions);`
- L86 _public prototype_ `void SetWrappingPolicy(ETextWrappingPolicy InWrappingPolicy);`
- L87 _public prototype_ `void SetAutoWrapText(bool InAutoWrapText);`
- L88 _public prototype_ `void SetWrapTextAt(float InWrapTextAt);`
- L89 _public prototype_ `void SetLineHeightPercentage(float InLineHeightPercentage);`
- L90 _public prototype_ `void SetApplyLineHeightToBottomLine(bool InApplyLineHeightToBottomLine);`
- L91 _public prototype_ `void SetFontFacesLoadingPaintPolicy(EFontFacesLoadingPaintPolicy InFontFacesLoadingPaintPolicy);`
- L92 _public prototype_ `void SetMargin(const FMargin& InMargin);`
- L95 _protected function_ `virtual void OnShapedTextOptionsChanged(FShapedTextOptions InShapedTextOptions)`
- L96 _protected function_ `virtual void OnJustificationChanged(ETextJustify::Type InJustification)`
- L97 _protected function_ `virtual void OnWrappingPolicyChanged(ETextWrappingPolicy InWrappingPolicy)`
- L98 _protected function_ `virtual void OnAutoWrapTextChanged(bool InAutoWrapText)`
- L99 _protected function_ `virtual void OnWrapTextAtChanged(float InWrapTextAt)`
- L100 _protected function_ `virtual void OnLineHeightPercentageChanged(float InLineHeightPercentage)`
- L101 _protected function_ `virtual void OnApplyLineHeightToBottomLineChanged(bool InApplyLineHeightToBottomLine)`
- L102 _protected function_ `virtual void OnFontFacesLoadingPaintPolicyChange(EFontFacesLoadingPaintPolicy InFontFacesLoadingPaintPolicy)`
- L103 _protected function_ `virtual void OnMarginChanged(const FMargin& InMargin)`
- L107 _protected function_ `template <typename TWidgetType> void SynchronizeTextLayoutProperties(TWidgetType& InWidget)` — Synchronize the properties with the given widget. A template as the Slate widgets conform to the same API, but don't derive from a common base.
- L121 _protected function_ `void SlateHandleAllFontFacesFinishLoading()`
- L128 _protected member_ `FShapedTextOptions ShapedTextOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Localization, AdvancedDisplay, meta=(ShowOnlyInnerProperties))` — Controls how the text within this widget should be shaped.
- L132 _protected member_ `FOnAllFontFacesFinishLoading_TextLayoutWidget OnAllFontFacesFinishLoading;` — `UPROPERTY(BlueprintAssignable, Category = "Font|Event")` — Called when all font faces for the text has finished async loading. Is not called if font faces are synchronously loaded.
- L136 _protected member_ `TEnumAsByte<ETextJustify::Type> Justification;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetJustification, Setter, Category=Appearance)` — How the text should be aligned with the margin.
- L140 _protected member_ `ETextWrappingPolicy WrappingPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Wrapping, AdvancedDisplay)` — The wrapping policy to use.
- L144 _protected member_ `uint8 AutoWrapText:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Wrapping)` — True if we're wrapping text automatically based on the computed horizontal space for this widget.
- L148 _protected member_ `bool ApplyLineHeightToBottomLine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Appearance, AdvancedDisplay)` — Whether to leave extra space below the last line due to line height.
- L152 _protected member_ `EFontFacesLoadingPaintPolicy FontFacesLoadingPaintPolicy;` — `UPROPERTY(EditAnywhere, Setter, Category = Font)` — Controls how painting the text in the widget should behave when font faces for the text is still loading.
- L156 _protected member_ `float WrapTextAt;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Wrapping)` — Whether text wraps onto a new line when it's length exceeds this width; if this value is zero or negative, no wrapping occurs.
- L160 _protected member_ `FMargin Margin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Appearance, AdvancedDisplay)` — The amount of blank space left around the edges of text area.
- L164 _protected member_ `float LineHeightPercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category=Appearance, AdvancedDisplay)` — The amount to scale each lines height by.

### `Source/Runtime/UMG/Public/Components/Throbber.h` (Public)


#### class `UThrobber`  
`class UThrobber : public UWidget`  
_L19-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A Throbber widget that shows several zooming circles in a row.
- L28 _public member_ `int32 NumberOfPieces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetNumberOfPieces", Category=Appearance, meta=( ClampMin="1", ClampMax="25", UIMin="1", UIMax="25" ))` — How many pieces there are
- L33 _public member_ `bool bAnimateHorizontally;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="IsAnimateHorizontally", Setter="SetAnimateHorizontally", BlueprintSetter = "SetAnimateHorizontally", Category = Appearance)` — Should the pieces animate horizontally?
- L38 _public member_ `bool bAnimateVertically;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="IsAnimateVertically", Setter="SetAnimateVertically", BlueprintSetter="SetAnimateVertically", Category = Appearance)` — Should the pieces animate vertically?
- L43 _public member_ `bool bAnimateOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="IsAnimateOpacity", Setter="SetAnimateOpacity", BlueprintSetter="SetAnimateOpacity", Category = Appearance)` — Should the pieces animate their opacity?
- L48 _public member_ `FSlateBrush Image;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category=Appearance)` — The animated pieces.
- L54 _public prototype_ `void SetNumberOfPieces(int32 InNumberOfPieces);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets how many pieces there are
- L55 _public prototype_ `int32 GetNumberOfPieces() const;`
- L59 _public prototype_ `void SetAnimateHorizontally(bool bInAnimateHorizontally);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets whether the pieces animate horizontally.
- L60 _public prototype_ `bool IsAnimateHorizontally() const;`
- L64 _public prototype_ `void SetAnimateVertically(bool bInAnimateVertically);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets whether the pieces animate vertically.
- L65 _public prototype_ `bool IsAnimateVertically() const;`
- L69 _public prototype_ `void SetAnimateOpacity(bool bInAnimateOpacity);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets whether the pieces animate their opacity.
- L70 _public prototype_ `bool IsAnimateOpacity() const;`
- L72 _public prototype_ `void SetImage(const FSlateBrush& Brush);`
- L73 _public prototype_ `const FSlateBrush& GetImage() const;`
- L76 _public prototype_ `virtual void SynchronizeProperties() override;`
- L80 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L84 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L89 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L94 _private prototype_ `SThrobber::EAnimation GetAnimation() const;` — Gets the combined value of the animation properties as a single SThrobber::EAnimation value.
- L98 _private member_ `TSharedPtr<SThrobber> MyThrobber;` — The Throbber widget managed by this object.

### `Source/Runtime/UMG/Public/Components/TileView.h` (Public)


#### class `UTileView`  
`class UTileView : public UListView`  
_L15-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UListView`
- desc: A ListView that presents the contents as a set of tiles all uniformly sized. To make a widget usable as an entry in a TileView, it must inherit from the IUserObjectListEntry interface.
- L20 _public prototype_ `UTileView(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L26 _public prototype_ `void SetEntryHeight(float NewHeight);` — `UFUNCTION(BlueprintCallable, Category = TileView)` — Sets the height of every tile entry
- L30 _public prototype_ `void SetEntryWidth(float NewWidth);` — `UFUNCTION(BlueprintCallable, Category = TileView)` — Sets the width of every tile entry
- L34 _public function_ `float GetEntryHeight() const` — `UFUNCTION(BlueprintPure, Category = TileView)` — Gets the height of tile entries
- L38 _public function_ `float GetEntryWidth() const` — `UFUNCTION(BlueprintPure, Category = TileView)` — Gets the width of tile entries
- L41 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L42 _protected prototype_ `virtual FMargin GetDesiredEntryPadding(UObject* Item) const override;`
- L44 _protected prototype_ `float GetTotalEntryHeight() const;`
- L45 _protected prototype_ `float GetTotalEntryWidth() const;`
- L49 _protected function_ `template <template<typename> class TileViewT = STileView> TSharedRef<TileViewT<UObject*>> ConstructTileView()` — STileView construction helper - useful if using a custom STileView subclass
- L87 _private prototype_ `bool IsAligned() const;` — `UFUNCTION()` — Returns whether the TileView is left, right or center aligned.
- L92 _protected member_ `float EntryHeight = 128.f;` — `UPROPERTY(EditAnywhere, Category = ListEntries)` — The height of each tile
- L96 _protected member_ `float EntryWidth = 128.f;` — `UPROPERTY(EditAnywhere, Category = ListEntries)` — The width of each tile
- L100 _protected member_ `EListItemAlignment TileAlignment;` — `UPROPERTY(EditAnywhere, Category = ListEntries)` — The method by which to align the tile entries in the available space for the tile view
- L104 _protected member_ `bool bWrapHorizontalNavigation = false;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — True to allow left/right navigation to wrap back to the tile on the opposite edge
- L108 _protected member_ `ESlateVisibility ScrollbarDisabledVisibility = ESlateVisibility::Collapsed;` — `UPROPERTY(EditAnywhere, Category = ListView, meta=(ValidEnumValues="Collapsed, Hidden, Visible"))` — Set the visibility of the Scrollbar when it's not needed
- L110 _protected member_ `TSharedPtr<STileView<UObject*>> MyTileView;`
- L118 _private member_ `bool bEntrySizeIncludesEntrySpacing = true;` — `UPROPERTY(EditAnywhere, Category = ListEntries, meta = (EditCondition = "IsAligned"))` — True if entry dimensions should be the sum of the entry widget dimensions and the spacing. This means the size of the entry widget will be adjusted so that the summation of the widget size and entry spacing always equals entry size.

### `Source/Runtime/UMG/Public/Components/TreeView.h` (Public)


#### class `UTreeView`  
`class UTreeView : public UListView`  
_L20-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UListView`
- desc: Similar to ListView, but can display a hierarchical tree of elements. The base items source for the tree identifies the root items, each of which can have n associated child items. There is no hard limit to the nesting - child items can have children and so on To make a widget usable as an entry in a TreeView, it must inherit from the IUserObjectListEntry interface.
- L25 _public prototype_ `UTreeView(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L30 _public prototype_ `void SetItemExpansion(UObject* Item, bool bExpandItem);` — `UFUNCTION(BlueprintCallable, Category = TreeView)` — Attempts to expand/collapse the given item (only relevant if the item has children)
- L34 _public prototype_ `void ExpandAll();` — `UFUNCTION(BlueprintCallable, Category = TreeView)` — Expands all items with children
- L38 _public prototype_ `void CollapseAll();` — `UFUNCTION(BlueprintCallable, Category = TreeView)` — Collapses all currently expanded items
- L41 _public function_ `template <typename ObjectT> void SetOnGetItemChildren(ObjectT* InUserObject, typename TSlateDelegates<UObject*>::FOnGetChildren::TMethodPtr<ObjectT> InMethodPtr)`
- L47 _public function_ `template <typename ObjectT> void SetOnGetItemChildren(TSharedRef<ObjectT> InUserObject, typename TSlateDelegates<UObject*>::FOnGetChildren::TMethodPtr<ObjectT> InMethodPtr)`
- L53 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L54 _protected prototype_ `virtual void OnItemClickedInternal(UObject* ListItem) override;`
- L56 _protected prototype_ `virtual void OnItemExpansionChangedInternal(UObject* Item, bool bIsExpanded) override;`
- L57 _protected prototype_ `virtual void OnGetChildrenInternal(UObject* Item, TArray<UObject*>& OutChildren) const override;`
- L61 _protected function_ `template <template<typename> class TreeViewT = STreeView> TSharedRef<TreeViewT<UObject*>> ConstructTreeView()` — STreeView construction helper - useful if using a custom STreeView subclass
- L77 _protected member_ `TSharedPtr<STreeView<UObject*>> MyTreeView;`
- L82 _private member_ `FOnGetItemChildrenDynamic BP_OnGetItemChildren;` — `UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent, AllowPrivateAccess = true, DisplayName = "On Get Item Children"))` — Called to get the list of children (if any) that correspond to the given item. Only called if the native C++ version of the event is not bound.
- L85 _private member_ `FOnItemExpansionChangedDynamic BP_OnItemExpansionChanged;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (AllowPrivateAccess = true, DisplayName = "On Item Expansion Changed"))`
- L87 _private member_ `TSlateDelegates<UObject*>::FOnGetChildren OnGetItemChildren;`
- L88 _private member_ `FOnItemExpansionChanged OnItemExpansionChangedEvent;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetItemChildrenDynamic, UObject*, Item, TArray<UObject*>&, Children);`
- L9 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetItemChildrenDynamic, UObject*, Item, TArray<UObject*>&, Children);`
- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemExpansionChangedDynamic, UObject*, Item, bool, bIsExpanded);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemExpansionChangedDynamic, UObject*, Item, bool, bIsExpanded);`

### `Source/Runtime/UMG/Public/Components/UniformGridPanel.h` (Public)


#### class `UUniformGridPanel`  
`class UUniformGridPanel : public UPanelWidget`  
_L19-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: A panel that evenly divides up available space between all of its children.
- L28 _public member_ `FMargin SlotPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetSlotPadding", Category="Child Layout")` — Padding given to each slot
- L33 _public member_ `float MinDesiredSlotWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinDesiredSlotWidth", Category="Child Layout")` — The minimum desired width of the slots
- L38 _public member_ `float MinDesiredSlotHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetMinDesiredSlotHeight", Category="Child Layout")` — The minimum desired height of the slots
- L43 _public prototype_ `FMargin GetSlotPadding() const;`
- L47 _public prototype_ `void SetSlotPadding(FMargin InSlotPadding);` — `UFUNCTION(BlueprintCallable, Category="Child Layout")`
- L50 _public prototype_ `float GetMinDesiredSlotWidth() const;`
- L54 _public prototype_ `void SetMinDesiredSlotWidth(float InMinDesiredSlotWidth);` — `UFUNCTION(BlueprintCallable, Category="Child Layout")`
- L57 _public prototype_ `float GetMinDesiredSlotHeight() const;`
- L61 _public prototype_ `void SetMinDesiredSlotHeight(float InMinDesiredSlotHeight);` — `UFUNCTION(BlueprintCallable, Category="Child Layout")`
- L67 _public prototype_ `UUniformGridSlot* AddChildToUniformGrid(UWidget* Content, int32 InRow = 0, int32 InColumn = 0);` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L72 _public prototype_ `virtual void SynchronizeProperties() override;`
- L73 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L76 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L83 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L84 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L85 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L90 _protected member_ `TSharedPtr<SUniformGridPanel> MyUniformGridPanel;`
- L94 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

### `Source/Runtime/UMG/Public/Components/UniformGridSlot.h` (Public)


#### class `UUniformGridSlot`  
`class UUniformGridSlot : public UPanelSlot`  
_L18-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: A slot for UUniformGridPanel, these slots all share the same size as the largest slot in the grid.
- L27 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Uniform Grid Slot")` — The alignment of the object horizontally.
- L32 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Uniform Grid Slot")` — The alignment of the object vertically.
- L37 _public member_ `int32 Row;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetRow", meta=( UIMin = "0" ), Category="Layout|Uniform Grid Slot")` — The row index of the cell this slot is in
- L42 _public member_ `int32 Column;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetColumn", meta=( UIMin = "0" ), Category="Layout|Uniform Grid Slot")` — The column index of the cell this slot is in
- L47 _public prototype_ `int32 GetRow() const;` — Gets the row index of the slot
- L51 _public prototype_ `void SetRow(int32 InRow);` — `UFUNCTION(BlueprintCallable, Category="Layout|Uniform Grid Slot")` — Sets the row index of the slot, this determines what cell the slot is in the panel
- L54 _public prototype_ `int32 GetColumn() const;` — Gets the column index of the slot.
- L58 _public prototype_ `void SetColumn(int32 InColumn);` — `UFUNCTION(BlueprintCallable, Category="Layout|Uniform Grid Slot")` — Sets the column index of the slot, this determines what cell the slot is in the panel
- L61 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L65 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Uniform Grid Slot")`
- L68 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L72 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Uniform Grid Slot")`
- L77 _public prototype_ `virtual void SynchronizeProperties() override;`
- L81 _public prototype_ `void BuildSlot(TSharedRef<SUniformGridPanel> GridPanel);` — Builds the underlying FSlot for the Slate layout panel.
- L83 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L86 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L87 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`
- L92 _private member_ `SUniformGridPanel::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/VerticalBox.h` (Public)


#### class `UVerticalBox`  
`class UVerticalBox : public UPanelWidget`  
_L22-56_
- reflection: `UCLASS(meta = (ShortTooltip = "A layout panel for automatically laying child widgets out vertically"), MinimalAPI)`
- inherits: `UPanelWidget`
- desc: A vertical box widget is a layout panel allowing child widgets to be automatically laid out vertically. * Many Children * Flows Vertical
- L30 _public prototype_ `UVerticalBoxSlot* AddChildToVerticalBox(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Panel")`
- L34 _public prototype_ `virtual const FText GetPaletteCategory() override;` — UWidget interface
- L41 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L42 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L43 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L46 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L50 _protected member_ `TSharedPtr<class SVerticalBox> MyVerticalBox;`
- L54 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/VerticalBoxSlot.h` (Public)


#### class `UVerticalBoxSlot`  
`class UVerticalBoxSlot : public UPanelSlot`  
_L17-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UVerticalBox, contains the widget that is flowed vertically
- L26 _public member_ `FSlateChildSize Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetSize", Category="Layout|Vertical Box Slot", meta = (DisplayAfter = "Padding"))` — How much space this slot should occupy in the direction of the panel.
- L31 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|Vertical Box Slot")` — The padding area between the slot and the content it contains.
- L36 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Vertical Box Slot")` — The alignment of the object horizontally.
- L41 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Vertical Box Slot")` — The alignment of the object vertically.
- L46 _private member_ `SVerticalBox::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.
- L50 _public prototype_ `FMargin GetPadding() const;`
- L53 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Vertical Box Slot")`
- L55 _public prototype_ `FSlateChildSize GetSize() const;`
- L58 _public prototype_ `void SetSize(FSlateChildSize InSize);` — `UFUNCTION(BlueprintCallable, Category="Layout|Vertical Box Slot")`
- L60 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L63 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Vertical Box Slot")`
- L65 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L68 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Vertical Box Slot")`
- L73 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L76 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L79 _public prototype_ `void BuildSlot(TSharedRef<SVerticalBox> InVerticalBox);` — Builds the underlying FSlot for the Slate layout panel.
- L82 _public prototype_ `virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;`
- L83 _public prototype_ `virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;`

### `Source/Runtime/UMG/Public/Components/Viewport.h` (Public)


#### struct `FUMGViewportCameraTransform`  
`struct FUMGViewportCameraTransform`  
_L27-100_
- desc: Stores the transformation data for the viewport camera
- L30 _public prototype_ `FUMGViewportCameraTransform();`
- L33 _public prototype_ `void SetLocation(const FVector& Position);` — Sets the transform's location
- L36 _public function_ `void SetRotation(const FRotator& Rotation)` — Sets the transform's rotation
- L42 _public function_ `void SetLookAt(const FVector& InLookAt)` — Sets the location to look at during orbit
- L48 _public function_ `void SetOrthoZoom(float InOrthoZoom)` — Set the ortho zoom amount
- L55 _public function_ `inline const FVector& GetLocation() const` — @return The transform's location
- L58 _public function_ `inline const FRotator& GetRotation() const` — @return The transform's rotation
- L61 _public function_ `inline const FVector& GetLookAt() const` — @return The look at point for orbiting
- L64 _public function_ `inline float GetOrthoZoom() const` — @return The ortho zoom amount
- L72 _public prototype_ `void TransitionToLocation(const FVector& InDesiredLocation, bool bInstant);` — Animates from the current location to the desired location @param InDesiredLocation	The location to transition to @param bInstant			If the desired location should be set instantly rather than transitioned to over time
- L79 _public prototype_ `bool UpdateTransition();` — Updates any current location transitions @return true if there is currently a transition
- L84 _public prototype_ `FMatrix ComputeOrbitMatrix() const;` — Computes a matrix to use for viewport location and rotation when orbiting
- L87 _private member_ `double TransitionStartTime;` — The time when a transition to the desired location began
- L89 _private member_ `FVector ViewLocation;` — Current viewport Position.
- L91 _private member_ `FRotator ViewRotation;` — Current Viewport orientation; valid only for perspective projections.
- L93 _private member_ `FVector DesiredLocation;` — Desired viewport location when animating between two locations
- L95 _private member_ `FVector LookAt;` — When orbiting, the point we are looking at
- L97 _private member_ `FVector StartLocation;` — Viewport start location when animating to another location
- L99 _private member_ `float OrthoZoom;` — Ortho zoom amount

#### class `FUMGViewportClient`  
`class FUMGViewportClient : public FCommonViewportClient, public FViewElementDrawer`  
_L103-228_
- inherits: `FCommonViewportClient,FViewElementDrawer`
- L106 _public prototype_ `FUMGViewportClient(FPreviewScene* InPreviewScene = nullptr);`
- L107 _public prototype_ `virtual ~FUMGViewportClient();`
- L112 _public prototype_ `virtual UWorld* GetWorld() const override;` — FViewportClient interface
- L113 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L117 _public prototype_ `virtual void Tick(float InDeltaTime);`
- L119 _public prototype_ `virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily);`
- L125 _public prototype_ `virtual FSceneInterface* GetScene() const;` — @return The scene being rendered in this viewport
- L128 _public prototype_ `bool IsAspectRatioConstrained() const;`
- L130 _public prototype_ `void SetBackgroundColor(FLinearColor InBackgroundColor);`
- L131 _public prototype_ `FLinearColor GetBackgroundColor() const;`
- L134 _public function_ `void SetViewLocation(const FVector& NewLocation)` — Sets the location of the viewport's camera
- L140 _public function_ `void SetViewRotation(const FRotator& NewRotation)` — Sets the location of the viewport's camera
- L151 _public function_ `void SetLookAtLocation(const FVector& LookAt, bool bRecalculateView = false)` — Sets the look at location of the viewports camera for orbit * @param LookAt The new look at location @param bRecalulateView	If true, will recalculate view location and rotation to look at the new point immediatley
- L166 _public function_ `void SetOrthoZoom(float InOrthoZoom)` — Sets ortho zoom amount
- L174 _public function_ `const FVector& GetViewLocation() const` — @return the current viewport camera location
- L180 _public function_ `const FRotator& GetViewRotation() const` — @return the current viewport camera rotation
- L186 _public function_ `const FVector& GetLookAtLocation() const` — @return the current look at location
- L192 _public function_ `float GetOrthoZoom() const` — @return the current ortho zoom amount
- L198 _public prototype_ `float GetOrthoUnitsPerPixel(const FViewport* Viewport) const;` — @return The number of units per pixel displayed in this viewport
- L200 _public function_ `void SetEngineShowFlags(FEngineShowFlags InEngineShowFlags)`
- L205 _public prototype_ `FMatrix GetViewProjectionMatrix() const;`
- L210 _protected member_ `FPreviewScene* PreviewScene;` — The scene used for the viewport. Owned externally
- L212 _protected member_ `FMinimalViewInfo ViewInfo;`
- L214 _protected member_ `FLinearColor BackgroundColor;`
- L217 _protected member_ `FUMGViewportCameraTransform ViewTransform;` — Viewport camera transform data
- L219 _protected member_ `FViewport* Viewport;`
- L222 _protected member_ `FSceneViewStateReference ViewState;` — The viewport's scene view state.
- L225 _protected member_ `FEngineShowFlags EngineShowFlags;` — A set of flags that determines visibility for various scene elements.
- L227 _protected member_ `FMatrix CachedViewProjectionMatrix;`

#### class `UViewport`  
`class UViewport : public UContentWidget`  
_L234-314_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UContentWidget`
- L240 _private member_ `FLinearColor BackgroundColor;` — `UE_DEPRECATED(5.2, "Direct access to BackgroundColor is deprecated. Please use the getter or setter.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance)`
- L247 _private member_ `bool bIsEditorPreview = false;` — `UPROPERTY(EditAnywhere, Category = "World")` — True = WorldType in the new viewport will be set to "EditorPreview". This is advised when spawning a UMG viewport for Editor Tooling as the default World is WorldType=GamePreview and can cause unneeded subsystems to respond to the creation of the new UWorld.
- L250 _private prototype_ `UWorld* GetViewportWorld() const;` — `UFUNCTION(BlueprintCallable, Category="Viewport")`
- L253 _private prototype_ `FVector GetViewLocation() const;` — `UFUNCTION(BlueprintCallable, Category="Camera")`
- L256 _private prototype_ `void SetViewLocation(FVector Location);` — `UFUNCTION(BlueprintCallable, Category="Camera")`
- L259 _private prototype_ `FRotator GetViewRotation() const;` — `UFUNCTION(BlueprintCallable, Category="Camera")`
- L262 _private prototype_ `void SetViewRotation(FRotator Rotation);` — `UFUNCTION(BlueprintCallable, Category="Camera")`
- L265 _private prototype_ `AActor* Spawn(TSubclassOf<AActor> ActorClass);` — `UFUNCTION(BlueprintCallable, Category="Viewport")`
- L267 _private prototype_ `void SetBackgroundColor(const FLinearColor& InColor);`
- L269 _private prototype_ `const FLinearColor& GetBackgroundColor() const;`
- L272 _private prototype_ `void SetEnableAdvancedFeatures(bool InEnableAdvancedFeatures);` — `UFUNCTION(BlueprintCallable, Category = "Viewport")`
- L275 _private prototype_ `void SetLightIntensity(float LightIntensity);` — `UFUNCTION(BlueprintCallable, Category = "Viewport")`
- L278 _private prototype_ `void SetSkyIntensity(float LightIntensity);` — `UFUNCTION(BlueprintCallable, Category = "Viewport")`
- L281 _private prototype_ `void SetShowFlag(FString InShowFlagName, bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Viewport")`
- L284 _private prototype_ `FMatrix GetViewProjectionMatrix() const;` — `UFUNCTION(BlueprintCallable, Category = "Viewport")`
- L288 _private prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L291 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L294 _private prototype_ `virtual const FText GetPaletteCategory() override;`
- L300 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;` — UPanelWidget
- L301 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L305 _protected member_ `TSharedPtr<class SAutoRefreshViewport> ViewportWidget;`
- L309 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L313 _protected member_ `FEngineShowFlags ShowFlags;` — Show flags for the engine for this viewport

### `Source/Runtime/UMG/Public/Components/Visual.h` (Public)


#### class `UVisual`  
`class UVisual : public UObject`  
_L12-27_
- reflection: `UCLASS(DefaultToInstanced, MinimalAPI)`
- inherits: `UObject`
- desc: The base class for elements in UMG: slots and widgets.
- L17 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren);`
- L20 _public prototype_ `virtual void BeginDestroy() override;`
- L21 _public prototype_ `virtual bool NeedsLoadForServer() const override;`

### `Source/Runtime/UMG/Public/Components/Widget.h` (Public)


#### enum `UMWidget::(anonymous)`  
``  
_L52-58_

#### enum `UMWidget::(anonymous)`  
``  
_L62-97_

#### enum `EWidgetDesignFlags`  
`enum class EWidgetDesignFlags : uint8`  
_L175-182_
- reflection: `UENUM()`
- desc: Flags used by the widget designer.
- L177 _public enumerator_ `None = 0`
- L178 _public enumerator_ `Designing = 1 << 0`
- L179 _public enumerator_ `ShowOutline = 1 << 1`
- L180 _public enumerator_ `ExecutePreConstruct = 1 << 2`
- L181 _public enumerator_ `Previewing = 1 << 3`

#### struct `FDesignerChangedEventArgs`  
`struct FDesignerChangedEventArgs`  
_L193-207_
- desc: Event args that are sent whenever the designer is changed in some big way, allows for more accurate previews for widgets that need to anticipate things about the size of the screen, or other similar device factors.
- L196 _public function_ `FDesignerChangedEventArgs() : bScreenPreview(false) , Size(0, 0) , DpiScale(1.0f)`
- L204 _public member_ `bool bScreenPreview;`
- L205 _public member_ `FVector2D Size;`
- L206 _public member_ `float DpiScale;`

#### class `UWidget`  
`class UWidget : public UVisual, public INotifyFieldValueChanged`  
_L216-1253_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable, CustomFieldNotify, MinimalAPI)`
- inherits: `UVisual,INotifyFieldValueChanged`
- desc: This is the base class for all wrapped Slate controls that are exposed to UObjects.
- L227 _public prototype_ `UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_BEGIN(ToolTipText) UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(Visibility) UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(bIsEnabled) UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_END() UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_END();`
- L236 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FGetBool);` — Common Bindings - If you add any new common binding, you must provide a UPropertyBinding for it. all primitive binding in UMG goes through native binding evaluators to prevent thunking through the VM.
- L237 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(float, FGetFloat);`
- L238 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(int32, FGetInt32);`
- L239 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetText);`
- L240 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FSlateColor, FGetSlateColor);`
- L241 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FLinearColor, FGetLinearColor);`
- L242 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FSlateBrush, FGetSlateBrush);`
- L243 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(ESlateVisibility, FGetSlateVisibility);`
- L244 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(EMouseCursor::Type, FGetMouseCursor);`
- L245 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(ECheckBoxState, FGetCheckBoxState);`
- L246 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(UWidget*, FGetWidget);`
- L249 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetForString, FString, Item);` — Events
- L250 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetForObject, UObject*, Item);`
- L253 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FEventReply, FOnReply);` — Events
- L254 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FEventReply, FOnPointerEvent, FGeometry, MyGeometry, const FPointerEvent&, MouseEvent);`
- L256 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWidgetStateBroadcast, UWidget* , const FWidgetStateBitfield& );`
- L258 _public typedef_ `typedef TFunctionRef<TSharedPtr<SObjectWidget>( UUserWidget*, TSharedRef<SWidget> )> ConstructMethodType;`
- L264 _public member_ `TObjectPtr<UPanelSlot> Slot;` — `UPROPERTY(Instanced, TextExportTransient, EditAnywhere, BlueprintReadOnly, Category=Layout, meta=(ShowOnlyInnerProperties))` — The parent slot of the UWidget.  Allows us to easily inline edit the layout controlling this widget.
- L268 _public member_ `FGetBool bIsEnabledDelegate;` — `UPROPERTY()` — A bindable delegate for bIsEnabled
- L272 _public member_ `FGetText ToolTipTextDelegate;` — `UPROPERTY()` — A bindable delegate for ToolTipText
- L277 _public member_ `FText ToolTipText;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetToolTipText", Category="Behavior", meta=(MultiLine=true))` — Tooltip text to show when the user hovers over the widget with the mouse
- L282 _public member_ `TObjectPtr<UWidget> ToolTipWidget;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Getter="GetToolTip", Setter="SetToolTip", BlueprintSetter="SetToolTip", Category="Behavior", AdvancedDisplay)` — Tooltip widget to show when the user hovers over the widget with the mouse
- L286 _public member_ `FGetWidget ToolTipWidgetDelegate;` — `UPROPERTY()` — A bindable delegate for ToolTipWidget
- L291 _public member_ `FGetSlateVisibility VisibilityDelegate;` — `UPROPERTY()` — A bindable delegate for Visibility
- L298 _public member_ `FWidgetTransform RenderTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetRenderTransform", Category="Render Transform", meta = (DisplayName = "Transform"))` — The render transform of the widget allows for arbitrary 2D transforms to be applied to the widget.
- L306 _public member_ `FVector2D RenderTransformPivot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetRenderTransformPivot", Category="Render Transform", meta=( DisplayName="Pivot" ))` — The render transform pivot controls the location about which transforms are applied. This value is a normalized coordinate about which things like rotations will occur.
- L311 _public member_ `EFlowDirectionPreference FlowDirectionPreference;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Localization")` — Allows you to set a new flow direction
- L318 _public member_ `uint8 bIsVariable:1;` — `UPROPERTY()` — Allows controls to be exposed as variables in a blueprint.  Not all controls need to be exposed as variables, so this allows only the most useful ones to end up being exposed.
- L322 _public member_ `uint8 bCreatedByConstructionScript:1;` — `UPROPERTY(Transient)` — Flag if the Widget was created from a blueprint
- L327 _public member_ `uint8 bIsEnabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter="GetIsEnabled", Setter="SetIsEnabled", BlueprintGetter="GetIsEnabled", BlueprintSetter="SetIsEnabled", Category="Behavior")` — Sets whether this widget can be modified interactively by the user
- L331 _public member_ `uint8 bOverride_Cursor : 1;` — `UPROPERTY(EditAnywhere, Category="Behavior", meta=(InlineEditConditionToggle))`
- L348 _public member_ `uint8 bOverrideAccessibleDefaults : 1;` — `UPROPERTY(EditAnywhere, Category="Accessibility")` — Override all of the default accessibility behavior and text for this widget.
- L352 _public member_ `uint8 bCanChildrenBeAccessible : 1;` — `UPROPERTY(EditAnywhere, Category="Accessibility", meta=(EditCondition="bOverrideAccessibleDefaults"))` — Whether or not children of this widget can appear as distinct accessible widgets.
- L356 _public member_ `ESlateAccessibleBehavior AccessibleBehavior;` — `UPROPERTY(EditAnywhere, Category="Accessibility", meta=(EditCondition="bOverrideAccessibleDefaults"))` — Whether or not the widget is accessible, and how to describe it. If set to custom, additional customization options will appear.
- L360 _public member_ `ESlateAccessibleBehavior AccessibleSummaryBehavior;` — `UPROPERTY(EditAnywhere, Category="Accessibility", AdvancedDisplay, meta=(EditCondition="bOverrideAccessibleDefaults"))` — How to describe this widget when it's being presented through a summary of a parent widget. If set to custom, additional customization options will appear.
- L364 _public member_ `FText AccessibleText;` — `UPROPERTY(EditAnywhere, Category="Accessibility", meta=(MultiLine=true))` — When AccessibleBehavior is set to Custom, this is the text that will be used to describe the widget.
- L368 _public member_ `USlateAccessibleWidgetData::FGetText AccessibleTextDelegate;` — `UPROPERTY()` — An optional delegate that may be assigned in place of AccessibleText for creating a TAttribute
- L372 _public member_ `FText AccessibleSummaryText;` — `UPROPERTY(EditAnywhere, Category="Accessibility", meta=(MultiLine=true), AdvancedDisplay)` — When AccessibleSummaryBehavior is set to Custom, this is the text that will be used to describe the widget.
- L376 _public member_ `USlateAccessibleWidgetData::FGetText AccessibleSummaryTextDelegate;` — `UPROPERTY()` — An optional delegate that may be assigned in place of AccessibleSummaryText for creating a TAttribute
- L388 _protected member_ `uint8 bIsVolatile:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Performance")` — If true prevents the widget or its child's geometry or layout information from being cached.  If this widget changes every frame, but you want it to still be in an invalidation panel you should make it as volatile instead of invalidating it every frame, which would prevent the invalidation panel from actually ever caching anything.
- L391 _protected member_ `uint8 bIsManagedByGameViewportSubsystem:1;` — Cached value that indicate if the widget was added to the GameViewportSubsystem.
- L394 _protected member_ `bool bShouldBroadcastState : 1;` — False will skip state broadcasts. Useful for child classes to call Super methods without broadcasting early / late.
- L397 _protected member_ `bool bWidgetStateInitialized : 1;` — True implies widget state has been initialized.
- L402 _public member_ `uint8 bWrappedByComponent : 1;` — `UPROPERTY(Transient)` — True if the SWidget should be Wrapped in a Component
- L408 _public member_ `uint8 bHiddenInDesigner:1;` — `UPROPERTY()` — Stores the design time flag setting if the widget is hidden inside the designer
- L412 _public member_ `uint8 bExpandedInDesigner:1;` — `UPROPERTY()` — Stores the design time flag setting if the widget is expanded inside the designer
- L416 _public member_ `uint8 bLockedInDesigner:1;` — `UPROPERTY()` — Stores the design time flag setting if the widget is locked inside the designer
- L422 _public member_ `TEnumAsByte<EMouseCursor::Type> Cursor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetCursor", Category="Behavior", AdvancedDisplay, meta = (editcondition = "bOverride_Cursor"))` — The cursor to show when the mouse is over the widget
- L435 _public member_ `EWidgetClipping Clipping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Rendering")` — Controls how the clipping behavior of this widget.  Normally content that overflows the bounds of the widget continues rendering.  Enabling clipping prevents that overflowing content from being seen. NOTE: Elements in different clipping spaces can not be batched together, and so there is a performance cost to clipping.  Do not enable clipping unless a panel actually needs to prevent content from showing up outside its bounds.
- L440 _public member_ `ESlateVisibility Visibility;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter, Setter, BlueprintGetter="GetVisibility", BlueprintSetter="SetVisibility", Category="Behavior")` — The visibility of the widget
- L445 _private member_ `EWidgetPixelSnapping PixelSnapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Rendering", meta=(AllowPrivateAccess = true))` — If the widget will draw snapped to the nearest pixel.  Improves clarity but might cause visibile stepping in animation
- L452 _protected member_ `float RenderOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter="GetRenderOpacity", BlueprintSetter="SetRenderOpacity", Category="Rendering", meta = (UIMin = "0", UIMax = "1"))` — The opacity of the widget
- L457 _private member_ `TObjectPtr<USlateAccessibleWidgetData> AccessibleWidgetData;` — `UPROPERTY(Instanced)` — A custom set of accessibility rules for this widget. If null, default rules for the widget are used.
- L466 _public member_ `TObjectPtr<class UWidgetNavigation> Navigation;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category="Navigation")` — The navigation object for this widget is optionally created if the user has configured custom navigation rules for this widget in the widget designer.  Those rules determine how navigation transitions can occur between widgets.
- L471 _public member_ `TWeakObjectPtr<UObject> WidgetGeneratedBy;` — Stores a reference to the asset responsible for this widgets construction.
- L480 _public function_ `bool IsLockedInDesigner() const` — Is this widget locked in the designer UI
- L486 _public function_ `virtual void SetLockedInDesigner(bool NewLockedInDesigner)` — @param bLockedInDesigner should this widget be locked
- L495 _public member_ `TWeakObjectPtr<UClass> WidgetGeneratedByClass;` — Stores a reference to the class responsible for this widgets construction.
- L500 _public prototype_ `const FWidgetTransform& GetRenderTransform() const;`
- L504 _public prototype_ `void SetRenderTransform(FWidgetTransform InTransform);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L508 _public prototype_ `void SetRenderScale(FVector2D Scale);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L512 _public prototype_ `void SetRenderShear(FVector2D Shear);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L516 _public prototype_ `void SetRenderTransformAngle(float Angle);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L520 _public prototype_ `float GetRenderTransformAngle() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget|Transform")`
- L524 _public prototype_ `void SetRenderTranslation(FVector2D Translation);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L527 _public prototype_ `FVector2D GetRenderTransformPivot() const;`
- L531 _public prototype_ `void SetRenderTransformPivot(FVector2D Pivot);` — `UFUNCTION(BlueprintCallable, Category="Widget|Transform")`
- L534 _public prototype_ `EFlowDirectionPreference GetFlowDirectionPreference() const;` — Gets the flow direction preference of the widget
- L537 _public prototype_ `void SetFlowDirectionPreference(EFlowDirectionPreference FlowDirection);` — Sets the flow direction preference of the widget
- L541 _public prototype_ `bool GetIsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the current enabled status of the widget
- L545 _public prototype_ `virtual void SetIsEnabled(bool bInIsEnabled);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the current enabled status of the widget
- L549 _public prototype_ `bool IsInViewport() const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Appearance")` — @return true if the widget was added to the viewport using AddToViewport or AddToPlayerScreen.
- L552 _public prototype_ `FText GetToolTipText() const;` — @return the tooltip text for the widget.
- L556 _public prototype_ `void SetToolTipText(const FText& InToolTipText);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the tooltip text for the widget.
- L559 _public prototype_ `UWidget* GetToolTip() const;` — @return the custom widget as the tooltip of the widget.
- L563 _public prototype_ `void SetToolTip(UWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets a custom widget as the tooltip of the widget.
- L566 _public prototype_ `EMouseCursor::Type GetCursor() const;` — Sets the cursor to show over the widget.
- L570 _public prototype_ `void SetCursor(EMouseCursor::Type InCursor);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the cursor to show over the widget.
- L574 _public prototype_ `void ResetCursor();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Resets the cursor to use on the widget, removing any customization for it.
- L578 _public prototype_ `bool IsRendered() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if the widget is Visible, HitTestInvisible or SelfHitTestInvisible and the Render Opacity is greater than 0.
- L582 _public prototype_ `bool IsVisible() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if the widget is Visible, HitTestInvisible or SelfHitTestInvisible.
- L586 _public prototype_ `ESlateVisibility GetVisibility() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the current visibility of the widget.
- L590 _public prototype_ `virtual void SetVisibility(ESlateVisibility InVisibility);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the visibility of the widget.
- L593 _protected prototype_ `void SetVisibilityInternal(ESlateVisibility InVisibility);`
- L598 _public prototype_ `float GetRenderOpacity() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the current visibility of the widget.
- L602 _public prototype_ `void SetRenderOpacity(float InOpacity);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the visibility of the widget.
- L606 _public prototype_ `EWidgetClipping GetClipping() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the clipping state of this widget.
- L610 _public prototype_ `void SetClipping(EWidgetClipping InClipping);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the clipping state of this widget.
- L613 _public prototype_ `EWidgetPixelSnapping GetPixelSnapping() const;` — Gets the pixel snapping method of this widget.
- L616 _public prototype_ `void SetPixelSnapping(EWidgetPixelSnapping InPixelSnapping);` — Sets the pixel snapping method of this widget.
- L620 _public prototype_ `void ForceVolatile(bool bForce);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the forced volatility of the widget.
- L624 _public prototype_ `virtual bool IsHovered() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if the widget is currently being hovered by a pointer device
- L632 _public prototype_ `bool HasKeyboardFocus() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Checks to see if this widget currently has the keyboard focus @return  True if this widget has keyboard focus
- L640 _public prototype_ `bool SupportsKeyboardFocus() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Checks to see if this widget supports keyboard focus @return  True if this widget supports keyboard focus
- L647 _public prototype_ `bool HasMouseCapture() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Checks to see if this widget is the current mouse captor @return  True if this widget has captured the mouse
- L656 _public prototype_ `bool HasMouseCaptureByUser(int32 UserIndex, int32 PointerIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Checks to see if this widget is the current mouse captor @param User index to check for capture @param Optional pointer index to check for capture @return  True if this widget has captured the mouse with given user and pointer
- L660 _public prototype_ `void SetKeyboardFocus();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the focus to this widget.
- L664 _public prototype_ `bool HasUserFocus(APlayerController* PlayerController) const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if this widget is focused by a specific user.
- L668 _public prototype_ `bool HasAnyUserFocus() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if this widget is focused by any user.
- L672 _public prototype_ `bool HasFocusedDescendants() const;` — `UFUNCTION(BlueprintCallable, Category="Widget", meta=(DisplayName="HasAnyUserFocusedDescendants"))` — Returns true if any descendant widget is focused by any user.
- L676 _public prototype_ `bool HasUserFocusedDescendants(APlayerController* PlayerController) const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Returns true if any descendant widget is focused by a specific user.
- L680 _public prototype_ `void SetFocus();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the focus to this widget for the owning user
- L684 _public prototype_ `void SetUserFocus(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the focus to this widget for a specific user (if setting focus for the owning user, prefer SetFocus())
- L692 _public prototype_ `void ForceLayoutPrepass();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Forces a pre-pass.  A pre-pass caches the desired size of the widget hierarchy owned by this widget. One pre-pass already happens for every widget before Tick occurs.  You only need to perform another pre-pass if you are adding child widgets this frame and want them to immediately be visible this frame.
- L699 _public prototype_ `void InvalidateLayoutAndVolatility();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Invalidates the widget from the view of a layout caching widget that may own this widget. will force the owning widget to redraw and cache children on the next paint pass.
- L709 _public prototype_ `FVector2D GetDesiredSize() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the widgets desired size. NOTE: The underlying Slate widget must exist and be valid, also at least one pre-pass must have occurred before this value will be of any use. @return The widget's desired size
- L717 _public prototype_ `void SetAllNavigationRules(EUINavigationRule Rule, FName WidgetToFocus);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the widget navigation rules for all directions. This can only be called on widgets that are in a widget tree. @param Rule The rule to use when navigation is taking place @param WidgetToFocus When using the Explicit rule, focus on this widget
- L727 _public prototype_ `void SetNavigationRule(EUINavigation Direction, EUINavigationRule Rule, FName WidgetToFocus);` — `UE_DEPRECATED(4.23, "SetNavigationRule is deprecated. Please use either SetNavigationRuleBase or SetNavigationRuleExplicit or SetNavigationRuleCustom or SetNavigationRuleCustomBoundary.")` — `UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DeprecatedFunction, DeprecatedMessage = "Please use either SetNavigationRuleBase or SetNavigationRuleExplicit or SetNavigationRuleCustom or SetNavigationRuleCustomBoundary."))` — Sets the widget navigation rules for a specific direction. This can only be called on widgets that are in a widget tree. @param Direction @param Rule The rule to use when navigation is taking place @param WidgetToFocus When using the Explicit rule, focus on this widget
- L735 _public prototype_ `void SetNavigationRuleBase(EUINavigation Direction, EUINavigationRule Rule);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the widget navigation rules for a specific direction. This can only be called on widgets that are in a widget tree. This works only for non Explicit, non Custom and non CustomBoundary Rules. @param Direction @param Rule The rule to use when navigation is taking place
- L743 _public prototype_ `void SetNavigationRuleExplicit(EUINavigation Direction, UWidget* InWidget);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the widget navigation rules for a specific direction. This can only be called on widgets that are in a widget tree. This works only for Explicit Rule. @param Direction @param InWidget Focus on this widget instance
- L751 _public prototype_ `void SetNavigationRuleCustom(EUINavigation Direction, FCustomWidgetNavigationDelegate InCustomDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the widget navigation rules for a specific direction. This can only be called on widgets that are in a widget tree. This works only for Custom Rule. @param Direction @param InCustomDelegate Custom Delegate that will be called
- L759 _public prototype_ `void SetNavigationRuleCustomBoundary(EUINavigation Direction, FCustomWidgetNavigationDelegate InCustomDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Sets the widget navigation rules for a specific direction. This can only be called on widgets that are in a widget tree. This works only for CustomBoundary Rule. @param Direction @param InCustomDelegate Custom Delegate that will be called
- L765 _public prototype_ `void SetNavigationMethod(const TInstancedStruct<FNavigationMethod>& NavigationMethod);` — Sets the widget navigation method for this widget hierarchy. This can only be called on widgets that are in a widget tree. @param NavigationMethodStruct. Must be the StaticStruct of type FNavigationMethod
- L769 _public prototype_ `class UPanelWidget* GetParent() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the parent widget
- L776 _public prototype_ `virtual void RemoveFromParent();` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Removes the widget from its parent widget.  If this widget was added to the player's screen or the viewport it will also be removed from those containers.
- L788 _public prototype_ `const FGeometry& GetCachedGeometry() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Gets the last geometry used to Tick the widget.  This data may not exist yet if this call happens prior to the widget having been ticked/painted, or it may be out of date, or a frame behind. We recommend not to use this data unless there's no other way to solve your problem.  Normally in Slate we try and handle these issues by making a dependent widget part of the hierarchy, as to avoid frame behind or what are referred to as hysteresis problems, both caused by depending on geometry from the previous frame being used to advise how to layout a dependent object the current frame.
- L791 _public prototype_ `const FGeometry& GetTickSpaceGeometry() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L794 _public prototype_ `const FGeometry& GetPaintSpaceGeometry() const;` — `UFUNCTION(BlueprintCallable, Category="Widget")`
- L798 _public prototype_ `virtual FDelegateHandle AddFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FFieldValueChangedDelegate InNewDelegate) override final;`
- L799 _public prototype_ `virtual bool RemoveFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FDelegateHandle InHandle) override final;`
- L800 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(FDelegateUserObjectConst InUserObject) override final;`
- L801 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(UE::FieldNotification::FFieldId InFieldId, FDelegateUserObjectConst InUserObject) override final;`
- L802 _public prototype_ `virtual void BroadcastFieldValueChanged(UE::FieldNotification::FFieldId InFieldId) override final;`
- L806 _public prototype_ `void K2_AddFieldValueChangedDelegate(FFieldNotificationId FieldId, FFieldValueChangedDynamicDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "FieldNotify", meta = (DisplayName = "Add Field Value Changed Delegate", ScriptName = "AddFieldValueChangedDelegate"))`
- L809 _public prototype_ `void K2_RemoveFieldValueChangedDelegate(FFieldNotificationId FieldId, FFieldValueChangedDynamicDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "FieldNotify", meta = (DisplayName = "Remove Field Value Changed Delegate", ScriptName="RemoveFieldValueChangedDelegate"))`
- L813 _protected prototype_ `void K2_BroadcastFieldValueChanged(FFieldNotificationId FieldId);` — `UFUNCTION(BlueprintCallable, Category="FieldNotify", meta = (DisplayName="Broadcast Field Value Changed", ScriptName="BroadcastFieldValueChanged"))`
- L823 _public prototype_ `TSharedRef<SWidget> TakeWidget();` — Gets the underlying slate widget or constructs it if it doesn't exist.  If you're looking to replace what slate widget gets constructed look for RebuildWidget.  For extremely special cases where you actually need to change the GC Root widget of the constructed User Widget - you need to use TakeDerivedWidget you must also take care to not call TakeWidget before calling TakeDerivedWidget, as that would put the wrong expected wrapper around the resulting widget being constructed.
- L845 _public function_ `template <class WidgetType = SObjectWidget> TSharedRef<WidgetType> TakeDerivedWidget(ConstructMethodType ConstructMethod)` — Gets the underlying slate widget or constructs it if it doesn't exist. @param ConstructMethod allows the caller to specify a custom constructor that will be provided the default parameters we use to construct the slate widget, this allows the caller to construct derived types of SObjectWidget in cases where additional functionality at the slate level is desirable. @example class SObjectWidgetCustom : public SObjectWidget, public IMixinBehavior { } Widget->TakeDerivedWidget<SObjectWidgetCustom>( []( UUserWidget* Widget, TSharedRef<SWidget> Content ) { return SNew( SObjectWidgetCustom, Widget ) [ Content ]; });
- L852 _private prototype_ `TSharedRef<SWidget> TakeWidget_Private( ConstructMethodType ConstructMethod );`
- L857 _public prototype_ `TSharedPtr<SWidget> GetCachedWidget() const;` — Gets the last created widget from RebuildWidget does not recreate the gc container for the widget if one is needed.
- L860 _public prototype_ `TSharedPtr<SWidget> GetCachedWrappedWidget() const;` — Gets the last created widget from RebuildDesignWidget does not recreate the gc container for the widget if one is needed.
- L864 _public prototype_ `bool IsConstructed() const;` — Gets the last created widget does not recreate the gc container for the widget if one is needed.
- L871 _public prototype_ `UGameInstance* GetGameInstance() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget")` — Gets the game instance associated with this UI. @return a pointer to the owning game instance
- L878 _public function_ `template <class TGameInstance = UGameInstance> TGameInstance* GetGameInstance() const` — Gets the game instance associated with this UI. @return a pointer to the owning game instance
- L888 _public prototype_ `virtual APlayerController* GetOwningPlayer() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget")` — Gets the player controller associated with this UI. @return The player controller that owns the UI.
- L895 _public function_ `template <class TPlayerController = APlayerController > TPlayerController* GetOwningPlayer() const` — Gets the player controller associated with this UI cast to the template type. @return The player controller that owns the UI. May be NULL if the cast fails.
- L905 _public prototype_ `virtual ULocalPlayer* GetOwningLocalPlayer() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget")` — Gets the local player associated with this UI. @return The owning local player.
- L912 _public function_ `template < class T > T* GetOwningLocalPlayer() const` — Gets the local player associated with this UI cast to the template type. @return The owning local player. May be NULL if the cast fails.
- L923 _public prototype_ `FText GetAccessibleText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the accessible text from the underlying Slate accessible widget @return The accessible text of the underlying Slate accessible widget. Returns an empty text if accessibility is dsabled or the underlying accessible widget is invalid.
- L931 _public prototype_ `FText GetAccessibleSummaryText() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the accessible summary text from the underlying Slate accessible widget. @return The accessible summary text of the underlying Slate accessible widget. Returns an empty text if accessibility is dsabled or the underlying accessible widget is invalid.
- L938 _public prototype_ `virtual void SynchronizeProperties();` — Applies all properties to the native widget if possible.  This is called after a widget is constructed. It can also be called by the editor to update modified state, so ensure all initialization to a widgets properties are performed here, or the property and visual state may become unsynced.
- L945 _public prototype_ `void BuildNavigation();` — Called by the owning user widget after the slate widget has been created.  After the entire widget tree has been initialized, any widget reference that was needed to support navigating to another widget will now be initialized and ready for usage.
- L949 _public function_ `inline bool IsDesignTime() const` — Returns if the widget is currently being displayed in the designer, it may want to display different data.
- L955 _public prototype_ `virtual void SetDesignerFlags(EWidgetDesignFlags NewFlags);` — Sets the designer flags on the widget.
- L958 _public function_ `inline EWidgetDesignFlags GetDesignerFlags() const` — Gets the designer flags currently set on the widget.
- L964 _public function_ `inline bool HasAnyDesignerFlags(EWidgetDesignFlags FlagsToCheck) const` — Tests if any of the flags exist on this widget.
- L969 _public function_ `inline bool IsPreviewTime() const`
- L975 _public function_ `const FString& GetDisplayLabel() const` — Returns the friendly name of the widget to display in the editor
- L981 _public prototype_ `void SetDisplayLabel(const FString& DisplayLabel);` — Sets the friendly name of the widget to display in the editor
- L984 _public prototype_ `const FString& GetCategoryName() const;` — Returns the category name of the widget
- L987 _public prototype_ `void SetCategoryName(const FString& InValue);` — Sets the category name of the widget
- L994 _public function_ `virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const` — Called at the end of Widget Blueprint compilation. Allows UMG elements to evaluate their default states and determine whether they are acceptable. To trigger compilation failure, add an error to the log. Warnings and notes will be visible, but will not cause compiles to fail.
- L997 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;` — Mark this object as modified, also mark the slot as modified.
- L1007 _public prototype_ `bool IsChildOf(UWidget* PossibleParent);` — Recurses up the list of parents and returns true if this widget is a descendant of the PossibleParent @return true if this widget is a child of the PossibleParent
- L1010 _public prototype_ `bool AddBinding(FDelegateProperty* DelegateProperty, UObject* SourceObject, const FDynamicPropertyPath& BindingPath);`
- L1020 _public prototype_ `FDelegateHandle RegisterPostStateListener(const FOnWidgetStateBroadcast::FDelegate& ListenerDelegate, bool bBroadcastCurrentState = true);` — Add a post-state-changed listener to this widget, will fire after a state changed and all related side effects are resolved. Note: Currently we only support post-state-changed broadcasts. @param ListenerDelegate Delegate to fire when state changes @param bBroadcastCurrentState true if we should trigger this delegate once on registration with the current widget state (Does not globally broadcast).
- L1027 _public prototype_ `void UnregisterPostStateListener(const FDelegateHandle& ListenerDelegate);` — Remove a post-state-changed  listener from this widget, resets state bitfield if no other state listeners exist @param ListenerDelegate Delegate to remove
- L1029 _public prototype_ `static TSubclassOf<UPropertyBinding> FindBinderClassForDestination(FProperty* Property);`
- L1032 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L1033 _public prototype_ `virtual void BeginDestroy() override;`
- L1034 _public prototype_ `virtual void FinishDestroy() override;`
- L1035 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L1038 _public function_ `inline bool CanSafelyRouteEvent()`
- L1043 _public function_ `inline bool CanSafelyRoutePaint()`
- L1049 _protected function_ `inline bool CanSafelyRouteCall()`
- L1056 _public prototype_ `bool IsGeneratedName() const;` — Is the label generated or provided by the user?
- L1059 _public prototype_ `virtual FString GetLabelMetadata() const;` — Get Label Metadata, which may be as simple as a bit of string data to help identify an anonymous text block.
- L1062 _public prototype_ `FText GetLabelText() const;` — Gets the label to display to the user for this widget.
- L1065 _public prototype_ `FText GetLabelTextWithMetadata() const;` — Gets the label to display to the user for this widget, including any extra metadata like the text string for text.
- L1068 _public prototype_ `virtual const FText GetPaletteCategory();` — Gets the palette category of the widget
- L1071 _public prototype_ `void CreatedFromPalette();` — Called by the palette after constructing a new widget.
- L1077 _public function_ `virtual void OnCreationFromPalette()` — Called after constructing a new widget from the palette. Allows the widget to perform interesting default setup that we don't want to be UObject Defaults.
- L1080 _public function_ `virtual void ConnectEditorData()` — Allows general fixups and connections only used at editor time.
- L1083 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L1087 _public prototype_ `bool IsVisibleInDesigner() const;` — Is the widget visible in the designer?  If this widget is 'hidden in the designer' or a parent is, this widget will also return false here.
- L1090 _public prototype_ `void SelectByDesigner();`
- L1091 _public prototype_ `void DeselectByDesigner();`
- L1093 _public function_ `virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)`
- L1095 _public function_ `virtual void OnSelectedByDesigner()`
- L1096 _public function_ `virtual void OnDeselectedByDesigner()`
- L1098 _public function_ `virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget)`
- L1099 _public function_ `virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget)`
- L1101 _public function_ `virtual void OnBeginEditByDesigner()`
- L1102 _public function_ `virtual void OnEndEditByDesigner()`
- L1108 _public prototype_ `static EVisibility ConvertSerializedVisibilityToRuntime(ESlateVisibility Input);` — Utility methods @TODO UMG: Should move elsewhere
- L1109 _public prototype_ `static ESlateVisibility ConvertRuntimeToSerializedVisibility(const EVisibility& Input);`
- L1111 _public prototype_ `static FSizeParam ConvertSerializedSizeParamToRuntime(const FSlateChildSize& Input);`
- L1113 _public prototype_ `static UWidget* FindChildContainingDescendant(UWidget* Root, UWidget* Descendant);`
- L1115 _public prototype_ `static FString GetDefaultFontName();`
- L1121 _protected prototype_ `EVisibility GetVisibilityInDesigner() const;` — This is an implementation detail that allows us to show and hide the widget in the designer regardless of the actual visibility state set by the user.
- L1123 _protected prototype_ `bool IsEditorWidget() const;`
- L1126 _protected prototype_ `virtual void OnBindingChanged(const FName& Property);`
- L1134 _protected prototype_ `void BroadcastBinaryPostStateChange(const FWidgetStateBitfield& StateChange, bool bInValue);` — Broadcast a binary state post change @param StateChange bitfield marking states that should be changed @param bInValue true if marked states should be enabled, false otherwise
- L1142 _protected prototype_ `void BroadcastEnumPostStateChange(const FWidgetStateBitfield& StateChange);` — `UE_DEPRECATED(5.5, "FWidgetStateBitfield currently no longer supports enum states")` — Broadcast an enum state post change @param StateChange bitfield marking states that should be changed
- L1145 _protected prototype_ `UObject* GetSourceAssetOrClass() const;`
- L1148 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget();` — Function implemented by all subclasses of UWidget is called when the underlying SWidget needs to be constructed.
- L1151 _protected prototype_ `virtual void OnWidgetRebuilt();` — Function called after the underlying SWidget is constructed.
- L1154 _protected prototype_ `virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content);`
- L1156 _protected prototype_ `TSharedRef<SWidget> CreateDesignerOutline(TSharedRef<SWidget> Content) const;`
- L1159 _protected prototype_ `FText GetDisplayNameBase() const;` — Gets the base name used to generate the display label/name of this widget.
- L1162 _protected prototype_ `void UpdateRenderTransform();`
- L1165 _protected prototype_ `void SynchronizeAccessibleData();` — Copy all accessible properties to the AccessibleWidgetData object
- L1170 _protected function_ `EVisibility ConvertVisibility(TAttribute<ESlateVisibility> SerializedType) const` — TODO UMG Consider moving conversion functions into another class. Conversion functions
- L1176 _protected function_ `TOptional<float> ConvertFloatToOptionalFloat(TAttribute<float> InFloat) const`
- L1181 _protected function_ `FSlateColor ConvertLinearColorToSlateColor(TAttribute<FLinearColor> InLinearColor) const`
- L1186 _protected prototype_ `void SetNavigationRuleInternal(EUINavigation Direction, EUINavigationRule Rule, FName WidgetToFocus = NAME_None, UWidget* InWidget = nullptr, FCustomWidgetNavigationDelegate InCustomDelegate = FCustomWidgetNavigationDelegate());`
- L1190 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const;` — Gets the widget that accessibility properties should synchronize to.
- L1195 _protected member_ `TWeakPtr<SWidget> MyWidget;` — The underlying SWidget.
- L1198 _protected member_ `TWeakPtr<SWidget> ComponentWrapperWidget;` — The underlying SWidget for the Component wrapper widget.
- L1201 _protected member_ `TWeakPtr<SObjectWidget> MyGCWidget;` — The underlying SWidget contained in a SObjectWidget
- L1204 _protected member_ `FWidgetStateBitfield MyWidgetStateBitfield;` — The bitfield for this widget's state
- L1207 _protected member_ `FOnWidgetStateBroadcast PostWidgetStateChanged;` — Delegate that broadcasts after current widget state has fully changed, including all state-related side effects
- L1211 _protected member_ `TArray<TObjectPtr<UPropertyBinding>> NativeBindings;` — `UPROPERTY(Transient)` — Native property bindings.
- L1213 _protected member_ `static TArray<TSubclassOf<UPropertyBinding>> BinderClasses;`
- L1216 _private member_ `TBitArray<> EnabledFieldNotifications;`
- L1221 _private member_ `uint8 DesignerFlags;` — `UPROPERTY(Transient)` — Any flags used by the designer at edit time.
- L1225 _private member_ `FString DisplayLabel;` — `UPROPERTY()` — The friendly name for this widget displayed in the designer and BP graph.
- L1228 _private member_ `TWeakPtr<SWidget> DesignWrapperWidget;` — The underlying SWidget for the design time wrapper widget.
- L1232 _private member_ `FString CategoryName;` — `UPROPERTY()` — Category name used in the widget designer for sorting purpose
- L1237 _private prototype_ `void VerifySynchronizeProperties();`
- L1240 _private member_ `bool bRoutedSynchronizeProperties;` — Did we route the synchronize properties call?
- L1243 _private function_ `inline void VerifySynchronizeProperties()`
- L1247 _private prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, ToolTipText);`
- L1248 _private prototype_ `PROPERTY_BINDING_IMPLEMENTATION(bool, bIsEnabled);`
- L1250 _private prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, AccessibleText);`
- L1251 _private prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FText, AccessibleSummaryText);`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_HAS_WIDGET_GENERATED_BY_CLASS (!UE_BUILD_SHIPPING || WITH_EDITOR)`
- L35 _macro_ `#define WIDGET_INCLUDE_RELFECTION_METADATA (!UE_BUILD_SHIPPING || WITH_EDITOR)`
- L48 _namespace_ `namespace UMWidget`
- L54 _enumerator_ `EntryClass` (scope `UMWidget::__anon6e8210de0103`) — [ClassMetadata] [PropertyMetadata] Specifies the base class by which to filter available entry classes within DynamicEntryBox and any ListViewBase.
- L57 _enumerator_ `EntryInterface` (scope `UMWidget::__anon6e8210de0103`) — [ClassMetadata] [PropertyMetadata] Specifies the base class by which to filter available entry classes within DynamicEntryBox and any ListViewBase.
- L66 _enumerator_ `DesignerRebuild` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property if changed will rebuild the widget designer preview.  Use sparingly, try to update most properties by setting them in the SynchronizeProperties function. UPROPERTY(meta=(DesignerRebuild))
- L70 _enumerator_ `BindWidget` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property requires a widget be bound to it in the designer.  Allows easy native access to designer defined controls. UPROPERTY(meta=(BindWidget))
- L74 _enumerator_ `BindWidgetOptional` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property optionally allows a widget be bound to it in the designer.  Allows easy native access to designer defined controls. UPROPERTY(meta=(BindWidgetOptional))
- L78 _enumerator_ `OptionalWidget` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property optionally allows a widget be bound to it in the designer.  Allows easy native access to designer defined controls. UPROPERTY(meta=(BindWidget, OptionalWidget=true))
- L82 _enumerator_ `BindWidgetAnim` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property requires a widget animation be bound to it in the designer.  Allows easy native access to designer defined animations. UPROPERTY(meta=(BindWidgetAnim))
- L86 _enumerator_ `BindWidgetAnimOptional` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] This property optionally allows a animation widget be bound to it in the designer.  Allows easy native access to designer defined animation. UPROPERTY(meta=(BindWidgetAnimOptional))
- L90 _enumerator_ `IsBindableEvent` (scope `UMWidget::__anon6e8210de0203`) — [PropertyMetadata] Exposes a dynamic delegate property in the details panel for the widget. UPROPERTY(meta=(IsBindableEvent))
- L109 _macro_ `#define PROPERTY_BINDING(ReturnType, MemberName) \` — Helper macro for binding to a delegate or using the constant value when constructing the underlying SWidget. These macros create a binding that has a layer of indirection that allows blueprint debugging to work more effectively.
- L116 _macro_ `#define BITFIELD_PROPERTY_BINDING(MemberName) \`
- L123 _macro_ `#define PROPERTY_BINDING_IMPLEMENTATION(ReturnType, MemberName) \`
- L151 _macro_ `#define PROPERTY_BINDING_IMPLEMENTATION(Type, MemberName)`
- L155 _macro_ `#define GAME_SAFE_OPTIONAL_BINDING(ReturnType, MemberName) PROPERTY_BINDING(ReturnType, MemberName)`
- L156 _macro_ `#define GAME_SAFE_BINDING_IMPLEMENTATION(ReturnType, MemberName) PROPERTY_BINDING_IMPLEMENTATION(ReturnType, MemberName)`
- L162 _macro_ `#define OPTIONAL_BINDING_CONVERT(ReturnType, MemberName, ConvertedType, ConversionFunction) \` — Helper macro for binding to a delegate or using the constant value when constructing the underlying SWidget, also allows a conversion function to be provided to convert between the SWidget value and the value exposed to UMG.
- L184 _prototype_ `ENUM_CLASS_FLAGS(EWidgetDesignFlags);`
- L236 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FGetBool);` — Common Bindings - If you add any new common binding, you must provide a UPropertyBinding for it. all primitive binding in UMG goes through native binding evaluators to prevent thunking through the VM.
- L237 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(float, FGetFloat);`
- L238 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(int32, FGetInt32);`
- L239 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetText);`
- L240 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FSlateColor, FGetSlateColor);`
- L241 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FLinearColor, FGetLinearColor);`
- L242 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FSlateBrush, FGetSlateBrush);`
- L243 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(ESlateVisibility, FGetSlateVisibility);`
- L244 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(EMouseCursor::Type, FGetMouseCursor);`
- L245 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(ECheckBoxState, FGetCheckBoxState);`
- L246 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(UWidget*, FGetWidget);`
- L249 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetForString, FString, Item);` — Events
- L250 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetForObject, UObject*, Item);`
- L253 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FEventReply, FOnReply);` — Events
- L254 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FEventReply, FOnPointerEvent, FGeometry, MyGeometry, const FPointerEvent&, MouseEvent);`
- L256 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWidgetStateBroadcast, UWidget* , const FWidgetStateBitfield& );`

### `Source/Runtime/UMG/Public/Components/WidgetComponent.h` (Public)


#### enum `EWidgetSpace`  
`enum class EWidgetSpace : uint8`  
_L25-31_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `World` — The widget is rendered in the world as mesh, it can be occluded like any other mesh in the world.
- L30 _public enumerator_ `Screen` — The widget is rendered in the screen, completely outside of the world, never occluded.

#### enum `EWidgetTimingPolicy`  
`enum class EWidgetTimingPolicy : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `RealTime` — The widget will tick using real time. When not ticking, real time will accumulate and be simulated on the next tick.
- L39 _public enumerator_ `GameTime` — The widget will tick using game time, respecting pausing and time dilation.

#### enum `EWidgetBlendMode`  
`enum class EWidgetBlendMode : uint8`  
_L43-48_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `Opaque`
- L46 _public enumerator_ `Masked`
- L47 _public enumerator_ `Transparent`

#### enum `EWidgetGeometryMode`  
`enum class EWidgetGeometryMode : uint8`  
_L51-58_
- reflection: `UENUM(BlueprintType)`
- L54 _public enumerator_ `Plane` — The widget is mapped onto a plane
- L57 _public enumerator_ `Cylinder` — The widget is mapped onto a cylinder

#### enum `EWindowVisibility`  
`enum class EWindowVisibility : uint8`  
_L61-68_
- reflection: `UENUM(BlueprintType)`
- L64 _public enumerator_ `Visible` — The window visibility is Visible
- L67 _public enumerator_ `SelfHitTestInvisible` — The window visibility is SelfHitTestInvisible

#### enum `ETickMode`  
`enum class ETickMode : uint8`  
_L71-81_
- reflection: `UENUM(BlueprintType)`
- L74 _public enumerator_ `Disabled` — The component tick is disabled until re-enabled.
- L77 _public enumerator_ `Enabled` — The component is always ticked
- L80 _public enumerator_ `Automatic` — The component is ticked only when needed. i.e. when visible.

#### class `UWidgetComponent`  
`class UWidgetComponent : public UMeshComponent`  
_L95-689_
- reflection: `UCLASS(Blueprintable, ClassGroup="UserInterface", hidecategories=(Object,Activation,"Components|Activation",Sockets,Base,Lighting,LOD,Mesh), editinlinenew, meta=(BlueprintSpawnableComponent) , MinimalAPI)`
- inherits: `UMeshComponent`
- desc: The widget component provides a surface in the 3D environment on which to render widgets normally rendered to the screen. Widgets are first rendered to a render target, then that render target is displayed in the world. Material Properties set by this component on whatever material overrides the default. SlateUI [Texture] BackColor [Vector] TintColorAndOpacity [Vector] OpacityFromTexture [Scalar]
- L101 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L102 _public prototype_ `virtual bool CanBeInCluster() const override;`
- L103 _public prototype_ `virtual void PostLoad() override;`
- L107 _public prototype_ `virtual void BeginPlay() override;` — UActorComponent Interface
- L108 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L111 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent Interface
- L112 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;`
- L113 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`
- L114 _public prototype_ `virtual FCollisionShape GetCollisionShape(float Inflation) const override;`
- L115 _public prototype_ `virtual void OnRegister() override;`
- L116 _public prototype_ `virtual void OnUnregister() override;`
- L117 _public prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L118 _public prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L119 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L120 _public prototype_ `int32 GetNumMaterials() const override;`
- L121 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L122 _public prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;` — UMG_API virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;  Collect all the PSO precache data used by the static mesh component
- L125 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L126 _public prototype_ `void ApplyComponentInstanceData(struct FWidgetComponentInstanceData* ComponentInstanceData);`
- L127 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L130 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L131 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L135 _public prototype_ `virtual void InitWidget();` — Ensures the user widget is initialized
- L138 _public prototype_ `virtual void ReleaseResources();` — Release resources associated with the widget.
- L141 _public prototype_ `virtual void UpdateWidget();` — Ensures the 3d window is created its size and content.
- L144 _public prototype_ `virtual void UpdateRenderTarget(FIntPoint DesiredRenderTargetSize);` — Ensure the render target is initialized and updates it if needed.
- L150 _public prototype_ `void UpdateBodySetup( bool bDrawSizeChanged = false );` — Ensures the body setup is initialized and updates it if needed. @param bDrawSizeChanged Whether the draw size of this component has changed since the last update call.
- L153 _public prototype_ `void OnWorldUserEntered(int32 SlateUserIndex);` — To be called when a SlateUser enters this world space widget.
- L160 _public prototype_ `virtual void GetLocalHitLocation(FVector WorldHitLocation, FVector2D& OutLocalHitLocation) const;` — Converts a world-space hit result to a hit location on the widget @param HitResult The hit on this widget in the world @param (Out) The transformed 2D hit location on the widget
- L168 _public prototype_ `TTuple<FVector, FVector2D> GetCylinderHitLocation(FVector WorldHitLocation, FVector WorldHitDirection) const;` — When using EWidgetGeometryMode::Cylinder, continues the trace from the front face of the widget component into the cylindrical geometry and returns adjusted hit results information. @returns two hit locations FVector is in world space and a FVector2D is in widget-space.
- L171 _public function_ `FVector2D GetLastLocalHitLocation() const` — Gets the last local location that was hit
- L177 _public function_ `TSubclassOf<UUserWidget> GetWidgetClass() const` — Returns the class of the user widget displayed by this component
- L181 _public prototype_ `UUserWidget* GetUserWidgetObject() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface, meta=(UnsafeDuringActorConstruction=true))` — Returns the user widget object displayed by this component
- L184 _public prototype_ `const TSharedPtr<SWidget>& GetSlateWidget() const;` — Returns the Slate widget that was assigned to this component, if any
- L187 _public prototype_ `TArray<FWidgetAndPointer> GetHitWidgetPath(FVector WorldHitLocation, bool bIgnoreEnabledStatus, float CursorRadius = 0.0f);` — Returns the list of widgets with their geometry and the cursor position transformed into this Widget component's space.
- L190 _public prototype_ `TArray<FWidgetAndPointer> GetHitWidgetPath(FVector2D WidgetSpaceHitCoordinate, bool bIgnoreEnabledStatus, float CursorRadius = 0.0f);` — Returns the list of widgets with their geometry and the cursor position transformed into this Widget space. The widget space is expressed as a Vector2D.
- L194 _public prototype_ `UTextureRenderTarget2D* GetRenderTarget() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Returns the render target to which the user widget is rendered
- L198 _public prototype_ `UMaterialInstanceDynamic* GetMaterialInstance() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Returns the dynamic material instance used to render the user widget
- L201 _public prototype_ `TSharedPtr<SWindow> GetSlateWindow() const;` — Returns the window containing the user widget content
- L207 _public prototype_ `virtual UUserWidget* GetWidget() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Gets the widget that is used by this Widget Component. It will be null if a Slate Widget was set using SetSlateWidget function.
- L214 _public prototype_ `virtual void SetWidget(UUserWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Sets the widget to use directly. This function will keep track of the widget till the next time it's called with either a newer widget or a nullptr
- L220 _public prototype_ `virtual void SetSlateWidget( const TSharedPtr<SWidget>& InSlateWidget);` — Sets a Slate widget to be rendered.  You can use this to draw native Slate widgets using a WidgetComponent, instead of drawing user widgets.
- L228 _public prototype_ `void SetOwnerPlayer(ULocalPlayer* LocalPlayer);` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Sets the local player that owns this widget component.  Setting the owning player controls which player's viewport the widget appears on in a split screen scenario.  Additionally it forwards the owning player to the actual UserWidget that is spawned.
- L232 _public function_ `bool GetManuallyRedraw() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — @see bManuallyRedraw
- L239 _public prototype_ `void SetManuallyRedraw(bool bUseManualRedraw);` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — @see bManuallyRedraw
- L243 _public prototype_ `ULocalPlayer* GetOwnerPlayer() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Gets the local player that owns this widget component.
- L247 _public prototype_ `FVector2D GetDrawSize() const;` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Returns the "specified" draw size of the quad in the world
- L251 _public prototype_ `FVector2D GetCurrentDrawSize() const;` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Returns the "actual" draw size of the quad in the world
- L255 _public prototype_ `void SetDrawSize(FVector2D Size);` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Sets the draw size of the quad in the world
- L259 _public prototype_ `virtual void RequestRedraw();` — `UFUNCTION(BlueprintCallable, Category=UserInterface, meta = (DeprecatedFunction, DeprecationMessage = "Use RequestRenderUpdate instead"))` — Requests that the widget be redrawn.
- L263 _public prototype_ `virtual void RequestRenderUpdate();` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Requests that the widget have it's render target updated, if TickMode is disabled, this will force a tick to happen to update the render target.
- L266 _public function_ `EWidgetBlendMode GetBlendMode() const` — Gets the blend mode for the widget.
- L269 _public prototype_ `void SetBlendMode( const EWidgetBlendMode NewBlendMode );` — Sets the blend mode to use for this widget
- L273 _public function_ `bool GetTwoSided() const` — `UFUNCTION(BlueprintCallable, Category = Rendering)` — Gets whether the widget is two-sided or not
- L280 _public prototype_ `void SetTwoSided( const bool bWantTwoSided );` — `UFUNCTION(BlueprintCallable, Category = Rendering)` — Sets whether the widget is two-sided or not
- L284 _public function_ `bool GetTickWhenOffscreen() const` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Gets whether the widget ticks when offscreen or not
- L291 _public function_ `void SetTickWhenOffscreen(const bool bWantTickWhenOffscreen)` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Sets whether the widget ticks when offscreen or not
- L298 _public prototype_ `void SetBackgroundColor( const FLinearColor NewBackgroundColor );` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Sets the background color and opacityscale for this widget
- L302 _public prototype_ `void SetTintColorAndOpacity( const FLinearColor NewTintColorAndOpacity );` — `UFUNCTION(BlueprintCallable, Category=UserInterface)` — Sets the tint color and opacity scale for this widget
- L305 _public prototype_ `void SetOpacityFromTexture( const float NewOpacityFromTexture );` — Sets how much opacity from the UI widget's texture alpha is used when rendering to the viewport (0.0-1.0)
- L309 _public function_ `FVector2D GetPivot() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Returns the pivot point where the UI is rendered about the origin.
- L313 _public function_ `void SetPivot( const FVector2D& InPivot )` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L317 _public function_ `bool GetDrawAtDesiredSize() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L321 _public function_ `void SetDrawAtDesiredSize(bool bInDrawAtDesiredSize)` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L325 _public function_ `float GetRedrawTime() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L329 _public function_ `void SetRedrawTime(float InRedrawTime)` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L332 _public prototype_ `TSharedPtr< SWindow > GetVirtualWindow() const;` — Get the fake window we create for widgets displayed in the world.
- L335 _public prototype_ `void UpdateMaterialInstanceParameters();` — Updates the dynamic parameters on the material instance, without re-creating it
- L338 _public prototype_ `void SetWidgetClass(TSubclassOf<UUserWidget> InWidgetClass);` — Sets the widget class used to generate the widget for this component
- L341 _public function_ `EWidgetSpace GetWidgetSpace() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L344 _public function_ `void SetWidgetSpace( EWidgetSpace NewSpace )` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L346 _public function_ `bool GetEditTimeUsable() const`
- L348 _public function_ `void SetEditTimeUsable(bool Value)`
- L352 _public function_ `EWidgetGeometryMode GetGeometryMode() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — @see EWidgetGeometryMode, @see GetCylinderArcAngle()
- L358 _public function_ `void SetGeometryMode(EWidgetGeometryMode InGeometryMode)` — `UFUNCTION(BlueprintCallable, Category = UserInterface)`
- L363 _public function_ `bool GetReceiveHardwareInput() const`
- L367 _public function_ `double GetCylinderArcAngle() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Defines the curvature of the widget component when using EWidgetGeometryMode::Cylinder; ignored otherwise.
- L371 _public function_ `void SetCylinderArcAngle(const double InCylinderArcAngle)` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Defines the curvature of the widget component when using EWidgetGeometryMode::Cylinder; ignored otherwise.
- L378 _public function_ `void SetInitialSharedLayerName(FName NewSharedLayerName)` — Sets shared layer name used when this widget is initialized
- L381 _public function_ `void SetInitialLayerZOrder(int32 NewLayerZOrder)` — Sets layer z order used when this widget is initialized
- L385 _public function_ `bool GetWindowFocusable() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — @see bWindowFocusable
- L392 _public prototype_ `void SetWindowFocusable(bool bInWindowFocusable);` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — @see bWindowFocusable
- L396 _public function_ `EWindowVisibility GetWindowVisiblility() const` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Gets the visibility of the virtual window created to host the widget focusable.
- L403 _public prototype_ `void SetWindowVisibility(EWindowVisibility InVisibility);` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Sets the visibility of the virtual window created to host the widget focusable.
- L407 _public prototype_ `void SetTickMode(ETickMode InTickMode);` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Sets the Tick mode of the Widget Component.
- L411 _public prototype_ `bool IsWidgetVisible() const;` — `UFUNCTION(BlueprintCallable, Category = UserInterface)` — Returns true if the the Slate window is visible and that the widget is also visible, false otherwise.
- L414 _public function_ `virtual FVector2D ModifyProjectedLocalPosition(const FGeometry& ViewportGeometry, const FVector2D& LocalPosition)` — Hook to allow this component modify the local position of the widget after it has been projected from world space to screen space.
- L416 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMaterialInstanceUpdated);`
- L417 _public member_ `FOnMaterialInstanceUpdated OnMaterialInstanceUpdated;`
- L420 _protected prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);`
- L423 _protected prototype_ `bool CanReceiveHardwareInput() const;` — Just because the user attempts to receive hardware input does not mean it's possible.
- L425 _protected prototype_ `void RegisterHitTesterWithViewport(TSharedPtr<SViewport> ViewportWidget);`
- L426 _protected prototype_ `void UnregisterHitTesterWithViewport(TSharedPtr<SViewport> ViewportWidget);`
- L428 _protected prototype_ `void RegisterWindow();`
- L429 _protected prototype_ `void UnregisterWindow();`
- L430 _protected prototype_ `void RemoveWidgetFromScreen();`
- L433 _protected prototype_ `virtual bool ShouldDrawWidget() const;` — Allows subclasses to control if the widget should be drawn.  Called right before we draw the widget.
- L436 _protected prototype_ `virtual void DrawWidgetToRenderTarget(float DeltaTime);` — Draws the current widget to the render target if possible.
- L439 _protected prototype_ `double ComputeComponentWidth() const;` — Returns the width of the widget component taking GeometryMode into account.
- L441 _protected prototype_ `void UpdateMaterialInstance();`
- L443 _protected prototype_ `virtual void OnHiddenInGameChanged() override;`
- L448 _protected member_ `EWidgetSpace Space;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — The coordinate space in which to render the widget
- L452 _protected member_ `EWidgetTimingPolicy TimingPolicy;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — How this widget should deal with timing, pausing, etc.
- L456 _protected member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — The class of User Widget to create and display an instance of
- L460 _protected member_ `FIntPoint DrawSize;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — The size of the displayed quad.
- L464 _protected member_ `bool bManuallyRedraw;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — Should we wait to be told to redraw to actually draw?
- L468 _protected member_ `bool bRedrawRequested;` — `UPROPERTY(Transient, DuplicateTransient)` — Has anyone requested we redraw?
- L476 _protected member_ `float RedrawTime;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — The time in between draws, if 0 - we would redraw every frame.  If 1, we would redraw every second. This will work with bManuallyRedraw as well.  So you can say, manually redraw, but only redraw at this maximum rate.
- L479 _protected member_ `double LastWidgetRenderTime;` — What was the last time we rendered the widget?
- L482 _protected prototype_ `double GetCurrentTime() const;` — Returns current absolute time, respecting TimingPolicy.
- L489 _protected member_ `FIntPoint CurrentDrawSize;` — `UPROPERTY(Transient, DuplicateTransient)` — The actual draw size, this changes based on DrawSize - or the desired size of the widget if bDrawAtDesiredSize is true.
- L496 _protected member_ `bool bUseInvalidationInWorldSpace;` — `UPROPERTY(EditAnywhere, Category = UserInterface, meta=(EditCondition="Space==EWidgetSpace::World", DisplayName="Use Invalidation"))` — Use the invalidation system to update this widget. Only valid in World space. In Screen space, the widget is updated by the viewport owners.
- L506 _protected member_ `bool bDrawAtDesiredSize;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — Causes the render target to automatically match the desired size. WARNING: If you change this every frame, it will be very expensive. If you need that effect, you should keep the outer widget's sized locked and dynamically scale or resize some inner widget.
- L510 _protected member_ `FVector2D Pivot;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — The Alignment/Pivot point that the widget is placed at relative to the position.
- L523 _protected member_ `bool bReceiveHardwareInput;` — `UPROPERTY(EditAnywhere, Category=Interaction)` — Register with the viewport for hardware input from the true mouse and keyboard.  These widgets will more or less react like regular 2D widgets in the viewport, e.g. they can and will steal focus from the viewport. WARNING: If you are making a VR game, definitely do not change this to true.  This option should ONLY be used if you're making what would otherwise be a normal menu for a game, just in 3D.  If you also need the game to remain responsive and for the player to be able to interact with UI and move around the world (such as a keypad on a door), use the WidgetInteractionComponent instead.
- L527 _protected member_ `bool bWindowFocusable;` — `UPROPERTY(EditAnywhere, Category=Interaction)` — Is the virtual window created to host the widget focusable?
- L531 _protected member_ `EWindowVisibility WindowVisibility;` — `UPROPERTY(EditAnywhere, Category = Interaction)` — The visibility of the virtual window created to host the widget
- L538 _protected member_ `bool bApplyGammaCorrection;` — `UPROPERTY(EditAnywhere, Category = UserInterface, AdvancedDisplay)` — Widget components that appear in the world will be gamma corrected by the 3D renderer. In some cases, widget components are blitted directly into the backbuffer, in which case gamma correction should be enabled.
- L545 _protected member_ `TObjectPtr<ULocalPlayer> OwnerPlayer;` — `UPROPERTY()` — The owner player for a widget component, if this widget is drawn on the screen, this controls what player's screen it appears on for split screen, if not set, users player 0.
- L549 _protected member_ `FLinearColor BackgroundColor;` — `UPROPERTY(EditAnywhere, Category=Rendering)` — The background color of the component
- L553 _protected member_ `FLinearColor TintColorAndOpacity;` — `UPROPERTY(EditAnywhere, Category=Rendering)` — Tint color and opacity for this component
- L557 _protected member_ `float OpacityFromTexture;` — `UPROPERTY(EditAnywhere, Category=Rendering, meta=(ClampMin=0.0f, ClampMax=1.0f))` — Sets the amount of opacity from the widget's UI texture to use when rendering the translucent or masked UI to the viewport (0.0-1.0)
- L561 _protected member_ `EWidgetBlendMode BlendMode;` — `UPROPERTY(EditAnywhere, Category=Rendering)` — The blend mode for the widget.
- L565 _protected member_ `bool bOverrideRenderTargetFormat;` — `UPROPERTY(EditAnywhere, Category=Rendering, AdvancedDisplay)` — When enabled, overrides the render target pixel format instead of using the default Slate format (RGBA8).
- L569 _protected member_ `TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormatOverride;` — `UPROPERTY(EditAnywhere, Category=Rendering, AdvancedDisplay, meta=(EditCondition="bOverrideRenderTargetFormat"))` — The render target format to use when bOverrideRenderTargetFormat is true.
- L573 _protected member_ `bool bIsTwoSided;` — `UPROPERTY(EditAnywhere, Category=Rendering)` — Is the component visible from behind?
- L577 _protected member_ `bool TickWhenOffscreen;` — `UPROPERTY(EditAnywhere, Category=Animation)` — Should the component tick the widget when it's off screen?
- L581 _protected member_ `TObjectPtr<class UBodySetup> BodySetup;` — `UPROPERTY(Transient, DuplicateTransient)` — The body setup of the displayed quad
- L585 _protected member_ `TObjectPtr<UMaterialInterface> TranslucentMaterial;` — `UPROPERTY()` — The material instance for translucent widget components
- L589 _protected member_ `TObjectPtr<UMaterialInterface> TranslucentMaterial_OneSided;` — `UPROPERTY()` — The material instance for translucent, one-sided widget components
- L593 _protected member_ `TObjectPtr<UMaterialInterface> OpaqueMaterial;` — `UPROPERTY()` — The material instance for opaque widget components
- L597 _protected member_ `TObjectPtr<UMaterialInterface> OpaqueMaterial_OneSided;` — `UPROPERTY()` — The material instance for opaque, one-sided widget components
- L601 _protected member_ `TObjectPtr<UMaterialInterface> MaskedMaterial;` — `UPROPERTY()` — The material instance for masked widget components.
- L605 _protected member_ `TObjectPtr<UMaterialInterface> MaskedMaterial_OneSided;` — `UPROPERTY()` — The material instance for masked, one-sided widget components.
- L609 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient, DuplicateTransient)` — The target to which the user widget is rendered
- L613 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;` — `UPROPERTY(Transient, DuplicateTransient)` — The dynamic instance of the material that the render target is attached to
- L616 _protected member_ `bool bAddedToScreen;` — `UPROPERTY(Transient, DuplicateTransient)`
- L622 _protected member_ `bool bEditTimeUsable;` — `UPROPERTY()` — Allows the widget component to be used at editor time.  For use in the VR-Editor.
- L628 _protected member_ `FName SharedLayerName;` — `UPROPERTY(EditDefaultsOnly, Category = Layers)` — Layer Name the widget will live on
- L632 _protected member_ `int32 LayerZOrder;` — `UPROPERTY(EditDefaultsOnly, Category = Layers)` — ZOrder the layer will be created on, note this only matters on the first time a new layer is created, subsequent additions to the same layer will use the initially defined ZOrder
- L636 _protected member_ `EWidgetGeometryMode GeometryMode;` — `UPROPERTY(EditAnywhere, Category=UserInterface)` — Controls the geometry of the widget component. See EWidgetGeometryMode.
- L640 _protected member_ `double CylinderArcAngle;` — `UPROPERTY(EditAnywhere, Category=UserInterface, meta=(ClampMin=1.0f, ClampMax=180.0f))` — Curvature of a cylindrical widget in degrees.
- L643 _protected member_ `ETickMode TickMode;` — `UPROPERTY(EditAnywhere, Category = UserInterface)`
- L646 _protected member_ `TSharedPtr<class SVirtualWindow> SlateWindow;` — The slate window that contains the user widget content
- L649 _protected member_ `FVector2D LastLocalHitLocation;` — The relative location of the last hit on this component
- L652 _protected member_ `static TSharedPtr<class FWidget3DHitTester> WidgetHitTester;` — The hit tester to use for this component
- L655 _protected member_ `class FWidgetRenderer* WidgetRenderer;` — Helper class for drawing widgets to a render target.
- L658 _private prototype_ `bool ShouldReenableComponentTickWhenWidgetBecomesVisible() const;`
- L662 _private member_ `TObjectPtr<UUserWidget> Widget;` — `UPROPERTY(Transient, DuplicateTransient)` — The User Widget object displayed and managed by this component
- L665 _private member_ `TSharedPtr<SWidget> SlateWidget;` — The Slate widget to be displayed by this component.  Only one of either Widget or SlateWidget can be used
- L668 _private member_ `TSet<int32> UsersEnteredWorldWidget;` — The Slate user ids of the users which have entered our world-space widget (and thus could've gotten focus).
- L671 _private member_ `TWeakPtr<SWidget> CurrentSlateWidget;` — The slate widget currently being drawn.
- L673 _private prototype_ `static EVisibility ConvertWindowVisibilityToVisibility(EWindowVisibility visibility);`
- L675 _private prototype_ `void OnWidgetVisibilityChanged(ESlateVisibility InVisibility);`
- L678 _private prototype_ `void UpdateWidgetOnScreen();` — When using Screen space, this will update the Widget on Screen.
- L681 _private prototype_ `void AddWidgetToScreen(ULocalPlayer* TargetPlayer);` — When using Screen space, this code will add the widget to the screen.
- L684 _private prototype_ `void ResetWorldUserFocusOnWidget();` — When using World space, this will reset all the users focused on the active widget.
- L687 _private member_ `bool bRenderCleared;` — Set to true after a draw of an empty component.
- L688 _private member_ `bool bOnWidgetVisibilityChangedRegistered;`

#### struct `FWidgetComponentInstanceData`  
`struct FWidgetComponentInstanceData : public FSceneComponentInstanceData`  
_L692-729_
- reflection: `USTRUCT()`
- inherits: `FSceneComponentInstanceData`
- L696 _public function_ `FWidgetComponentInstanceData() : RenderTarget(nullptr)`
- L700 _public function_ `FWidgetComponentInstanceData(const UWidgetComponent* SourceComponent) : FSceneComponentInstanceData(SourceComponent) , WidgetClass(SourceComponent->GetWidgetClass()) , RenderTarget(SourceComponent->GetRenderTarget())`
- L705 _public prototype_ `virtual ~FWidgetComponentInstanceData() = default;`
- L707 _public function_ `virtual bool ContainsData() const override`
- L712 _public function_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override`
- L718 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L727 _public member_ `TSubclassOf<UUserWidget> WidgetClass;`
- L728 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;`

#### Free symbols / members of external scopes

- L416 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMaterialInstanceUpdated);`

### `Source/Runtime/UMG/Public/Components/WidgetInteractionComponent.h` (Public)


#### enum `EWidgetInteractionSource`  
`enum class EWidgetInteractionSource : uint8`  
_L24-37_
- reflection: `UENUM(BlueprintType)`
- desc: The interaction source for the widget interaction component, e.g. where do we try and trace from to try to find a widget under a virtual pointer device.
- L27 _public enumerator_ `World` — Sends traces from the world location and orientation of the interaction component.
- L29 _public enumerator_ `Mouse` — Sends traces from the mouse location of the first local player controller.
- L31 _public enumerator_ `CenterScreen` — Sends trace from the center of the first local player's screen.
- L36 _public enumerator_ `Custom` — Sends traces from a custom location determined by the user.  Will use whatever FHitResult is set by the call to SetCustomHitResult.

#### class `UWidgetInteractionComponent`  
`class UWidgetInteractionComponent : public USceneComponent`  
_L56-381_
- reflection: `UCLASS(ClassGroup="UserInterface", meta=(BlueprintSpawnableComponent) , MinimalAPI)`
- inherits: `USceneComponent`
- desc: This is a component to allow interaction with the Widget Component.  This class allows you to simulate a sort of laser pointer device, when it hovers over widgets it will send the basic signals to show as if the mouse were moving on top of it.  You'll then tell the component to simulate key presses, like Left Mouse, down and up, to simulate a mouse click.
- L66 _public member_ `FOnHoveredWidgetChanged OnHoveredWidgetChanged;` — `UPROPERTY(BlueprintAssignable, Category="Interaction|Event")` — Called when the hovered Widget Component changes.  The interaction component functions at the Slate level - so it's unable to report anything about what UWidget is under the hit result.
- L69 _public prototype_ `UWidgetInteractionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L72 _public prototype_ `virtual void OnComponentCreated() override;`
- L73 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L74 _public prototype_ `virtual void Deactivate() override;`
- L75 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L84 _public prototype_ `virtual void PressPointerKey(FKey Key);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Presses a key as if the mouse/pointer were the source of it.  Normally you would just use Left/Right mouse button for the Key.  However - advanced uses could also be imagined where you send other keys to signal widgets to take special actions if they're under the cursor.
- L92 _public prototype_ `virtual void ReleasePointerKey(FKey Key);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Releases a key as if the mouse/pointer were the source of it.  Normally you would just use Left/Right mouse button for the Key.  However - advanced uses could also be imagined where you send other keys to signal widgets to take special actions if they're under the cursor.
- L100 _public prototype_ `virtual bool PressKey(FKey Key, bool bRepeat = false);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Press a key as if it had come from the keyboard.  Avoid using this for 'a-z|A-Z', things like the Editable Textbox in Slate expect OnKeyChar to be called to signal a specific character being send to the widget.  So for those cases you should use SendKeyChar.
- L106 _public prototype_ `virtual bool ReleaseKey(FKey Key);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Releases a key as if it had been released by the keyboard.
- L112 _public prototype_ `virtual bool PressAndReleaseKey(FKey Key);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Does both the press and release of a simulated keyboard key.
- L119 _public prototype_ `virtual bool SendKeyChar(FString Characters, bool bRepeat = false);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Transmits a list of characters to a widget by simulating a OnKeyChar event for each key listed in the string.
- L125 _public prototype_ `virtual void ScrollWheel(float ScrollDelta);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Sends a scroll wheel event to the widget under the last hit result.
- L131 _public prototype_ `UWidgetComponent* GetHoveredWidgetComponent() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Get the currently hovered widget component.
- L138 _public prototype_ `bool IsOverInteractableWidget() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Returns true if a widget under the hit result is interactive.  e.g. Slate widgets that return true for IsInteractable().
- L145 _public prototype_ `bool IsOverFocusableWidget() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Returns true if a widget under the hit result is focusable.  e.g. Slate widgets that return true for SupportsKeyboardFocus().
- L152 _public prototype_ `bool IsOverHitTestVisibleWidget() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Returns true if a widget under the hit result is has a visibility that makes it hit test visible.  e.g. Slate widgets that return true for GetVisibility().IsHitTestVisible().
- L157 _public prototype_ `const FWeakWidgetPath& GetHoveredWidgetPath() const;` — Gets the widget path for the slate widgets under the last hit result.
- L163 _public prototype_ `const FHitResult& GetLastHitResult() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Gets the last hit result generated by the component.  Returns the custom hit result if that was set.
- L169 _public prototype_ `FVector2D Get2DHitLocation() const;` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Gets the last hit location on the widget in 2D, local pixel units of the render target.
- L175 _public prototype_ `void SetCustomHitResult(const FHitResult& HitResult);` — `UFUNCTION(BlueprintCallable, Category="Interaction")` — Set custom hit result.  This is only taken into account if InteractionSource is set to EWidgetInteractionSource::Custom.
- L181 _public prototype_ `void SetFocus(UWidget* FocusWidget);` — `UFUNCTION(BlueprintCallable, Category = "Interaction")` — Set the focus target of the virtual user managed by this component
- L192 _protected member_ `TSharedPtr<FSlateVirtualUserHandle> VirtualUser;` — Represents the virtual user in slate.  When this component is registered, it gets a handle to the virtual slate user it will be, so virtual slate user 0, is probably real slate user 8, as that's the first index by default that virtual users begin - the goal is to never have them overlap with real input hardware as that will likely conflict with focus states you don't actually want to change - like where the mouse and keyboard focus input (the viewport), so that things like the player controller receive standard hardware input.
- L202 _public member_ `int32 VirtualUserIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta=( ClampMin = "0", ExposeOnSpawn = true ))` — Represents the Virtual User Index.  Each virtual user should be represented by a different index number, this will maintain separate capture and focus states for them.  Each controller or finger-tip should get a unique PointerIndex.
- L208 _public member_ `int32 PointerIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta=( ClampMin = "0", UIMin = "0", UIMax = "9", ExposeOnSpawn = true ))` — Each user virtual controller or virtual finger tips being simulated should use a different pointer index.
- L216 _public member_ `TEnumAsByte<ECollisionChannel> TraceChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")` — The trace channel to use when tracing for widget components in the world.
- L222 _public member_ `float InteractionDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")` — The distance in game units the component should be able to interact with a widget component.
- L230 _public member_ `EWidgetInteractionSource InteractionSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")` — Should we project from the world location of the component?  If you set this to false, you'll need to call SetCustomHitResult(), and provide the result of a custom hit test form whatever location you wish.
- L239 _public member_ `bool bEnableHitTesting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")` — Should the interaction component perform hit testing (Automatic or Custom) and attempt to simulate hover - if you were going to emulate a keyboard you would want to turn this option off if the virtual keyboard was separate from the virtual pointer device and used a second interaction component.
- L247 _public member_ `bool bShowDebug;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debugging")` — Shows some debugging lines and a hit sphere to help you debug interactions.
- L253 _public member_ `float DebugSphereLineThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debugging", AdvancedDisplay, meta=( ClampMin = "0.001" ))` — Determines the line thickness of the debug sphere.
- L259 _public member_ `float DebugLineThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debugging", AdvancedDisplay, meta=( ClampMin = "0.001", ClampMax = "50"))` — Determines the thickness of the debug lines.
- L265 _public member_ `FLinearColor DebugColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debugging", AdvancedDisplay)` — Determines the color of the debug lines.
- L270 _protected prototype_ `void GetKeyAndCharCodes(const FKey& Key, bool& bHasKeyCode, uint32& KeyCode, bool& bHasCharCode, uint32& CharCode);` — Gets the key and char codes for sending keys for the platform.
- L273 _protected prototype_ `bool CanSendInput();` — Is it safe for this interaction component to run?  Might not be in a server situation with no slate application.
- L276 _protected prototype_ `void SimulatePointerMovement();` — Performs the simulation of pointer movement.  Does not run if bEnableHitTesting is set to false.
- L301 _protected prototype_ `virtual FWidgetPath FindHoveredWidgetPath(const FWidgetTraceResult& TraceResult) const;` — Gets the WidgetPath for the widget being hovered over based on the hit result.
- L304 _protected prototype_ `virtual FWidgetTraceResult PerformTrace() const;` — Performs the trace and gets the hit result under the specified InteractionSource
- L310 _protected prototype_ `void GetRelatedComponentsToIgnoreInAutomaticHitTesting(TArray<UPrimitiveComponent*>& IgnorePrimitives) const;` — Gets the list of components to ignore during hit testing.  Which is everything that is a parent/sibling of this component that's not a Widget Component.  This is so traces don't get blocked by capsules and such around the player.
- L313 _protected prototype_ `bool CanInteractWithComponent(UWidgetComponent* Component) const;` — Returns true if the inteaction component can interact with the supplied widget component
- L318 _protected member_ `FWeakWidgetPath LastWidgetPath;` — The last widget path under the hit result.
- L321 _protected member_ `FModifierKeysState ModifierKeys;` — The modifier keys to simulate during key presses.
- L324 _protected member_ `TSet<FKey> PressedKeys;` — The current set of pressed keys we maintain the state of.
- L328 _protected member_ `FHitResult CustomHitResult;` — `UPROPERTY(Transient)` — Stores the custom hit result set by the player.
- L332 _protected member_ `FVector2D LocalHitLocation;` — `UPROPERTY(Transient)` — The 2D location on the widget component that was hit.
- L336 _protected member_ `FVector2D LastLocalHitLocation;` — `UPROPERTY(Transient)` — The last 2D location on the widget component that was hit.
- L341 _protected member_ `TObjectPtr<UWidgetComponent> HoveredWidgetComponent = nullptr;` — `UE_DEPRECATED(5.6, "Property deprecated, please use WeakHoveredWidgetComponent instead.")` — `UPROPERTY(Transient)` — DEPRECATED - Use WeakHoveredWidgetComponent instead
- L345 _protected member_ `TWeakObjectPtr<UWidgetComponent> WeakHoveredWidgetComponent;` — `UPROPERTY(Transient)` — The widget component we're currently hovering over.
- L349 _protected member_ `FHitResult LastHitResult;` — `UPROPERTY(Transient)` — The last hit result we used.
- L353 _protected member_ `bool bIsHoveredWidgetInteractable;` — `UPROPERTY(Transient)` — Are we hovering over any interactive widgets.
- L357 _protected member_ `bool bIsHoveredWidgetFocusable;` — `UPROPERTY(Transient)` — Are we hovering over any focusable widget?
- L361 _protected member_ `bool bIsHoveredWidgetHitTestVisible;` — `UPROPERTY(Transient)` — Are we hovered over a widget that is hit test visible?
- L366 _private prototype_ `void OnPIEEnded(class UGameInstance*);`
- L370 _private prototype_ `FWidgetPath DetermineWidgetUnderPointer();` — Returns the path to the widget that is currently beneath the pointer
- L377 _private member_ `TObjectPtr<class UArrowComponent> ArrowComponent;` — `UPROPERTY()` — The arrow component we show at editor time.

#### struct `UWidgetInteractionComponent::FWidgetTraceResult`  
`struct FWidgetTraceResult`  
_L278-298_
- L280 _public function_ `FWidgetTraceResult() : HitResult() , LocalHitLocation(FVector2D::ZeroVector) , HitWidgetComponent(nullptr) , HitWidgetPath() , bWasHit(false) , LineStartLocation(FVector::ZeroVector) , LineEndLocation(FVector::ZeroVector)`
- L291 _public member_ `FHitResult HitResult;`
- L292 _public member_ `FVector2D LocalHitLocation;`
- L293 _public member_ `UWidgetComponent* HitWidgetComponent;`
- L294 _public member_ `FWidgetPath HitWidgetPath;`
- L295 _public member_ `bool bWasHit;`
- L296 _public member_ `FVector LineStartLocation;`
- L297 _public member_ `FVector LineEndLocation;`

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHoveredWidgetChanged, UWidgetComponent*, WidgetComponent, UWidgetComponent*, PreviousWidgetComponent);`
- L47 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHoveredWidgetChanged, UWidgetComponent*, WidgetComponent, UWidgetComponent*, PreviousWidgetComponent);`

### `Source/Runtime/UMG/Public/Components/WidgetSwitcher.h` (Public)


#### class `UWidgetSwitcher`  
`class UWidgetSwitcher : public UPanelWidget`  
_L16-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: A widget switcher is like a tab control, but without tabs. At most one widget is visible at time.
- L24 _public member_ `int32 ActiveWidgetIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetActiveWidgetIndex", BlueprintGetter = "GetActiveWidgetIndex", FieldNotify, Category = "Switcher", meta = (UIMin = 0, ClampMin = 0))` — The slot index to display
- L30 _public prototype_ `int32 GetNumWidgets() const;` — `UFUNCTION(BlueprintCallable, Category="Switcher")` — Gets the number of widgets that this switcher manages.
- L34 _public prototype_ `int32 GetActiveWidgetIndex() const;` — `UFUNCTION(BlueprintCallable, Category="Switcher")` — Gets the slot index of the currently active widget
- L38 _public prototype_ `virtual void SetActiveWidgetIndex( int32 Index );` — `UFUNCTION(BlueprintCallable, Category="Switcher")` — Activates the widget at the specified index.
- L42 _public prototype_ `virtual void SetActiveWidget(UWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category="Switcher")` — Activates the widget and makes it the active index.
- L46 _public prototype_ `UWidget* GetWidgetAtIndex( int32 Index ) const;` — `UFUNCTION(BlueprintCallable, Category = "Switcher")` — Get a widget at the provided index
- L50 _public prototype_ `UWidget* GetActiveWidget() const;` — `UFUNCTION(BlueprintCallable, Category = "Switcher")` — Get the reference of the currently active widget
- L53 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L54 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L58 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L59 _public prototype_ `virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget) override;`
- L60 _public prototype_ `virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget) override;`
- L63 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L70 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L71 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L72 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L75 _protected prototype_ `void SetActiveWidgetIndexForSlateWidget();`
- L78 _protected member_ `TSharedPtr<class SWidgetSwitcher> MyWidgetSwitcher;`
- L82 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface

### `Source/Runtime/UMG/Public/Components/WidgetSwitcherSlot.h` (Public)


#### class `UWidgetSwitcherSlot`  
`class UWidgetSwitcherSlot : public UPanelSlot`  
_L18-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UWidgetSwitcher, contains the widget that is flowed vertically
- L26 _private member_ `SWidgetSwitcher::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.
- L33 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|Widget Switcher Slot")` — The padding area between the slot and the content it contains.
- L38 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Widget Switcher Slot")` — The alignment of the object horizontally.
- L43 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Widget Switcher Slot")` — The alignment of the object vertically.
- L47 _public prototype_ `FMargin GetPadding() const;`
- L50 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Widget Switcher Slot")`
- L52 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L55 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Widget Switcher Slot")`
- L57 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L60 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Widget Switcher Slot")`
- L65 _public prototype_ `virtual void SynchronizeProperties() override;`
- L68 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L71 _public prototype_ `void BuildSlot(TSharedRef<SWidgetSwitcher> InWidgetSwitcher);` — Builds the underlying FSlot for the Slate layout panel.
- L74 _public prototype_ `void SetContent(UWidget* NewContent);` — Sets the content of this slot, removing existing content if needed.

### `Source/Runtime/UMG/Public/Components/WindowTitleBarArea.h` (Public)


#### class `UWindowTitleBarArea`  
`class UWindowTitleBarArea : public UContentWidget`  
_L21-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentWidget`
- L30 _public member_ `bool bWindowButtonsEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsWindowButtonsEnabled", Setter = "SetWindowButtonsEnabled", Category = "Interaction", meta = (DisplayName = "Window Buttons Enabled"))` — Should the title bar area diaplay window minimize/maximize/close buttons.
- L35 _public member_ `bool bDoubleClickTogglesFullscreen;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsDoubleClickTogglesFullscreen", Setter = "SetDoubleClickTogglesFullscreen", Category = "Interaction", meta = (DisplayName = "Toggle Fullscreen"))` — Should double clicking the title bar area toggle fullscreen instead of maximizing the window.
- L40 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L43 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L46 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L48 _public prototype_ `void SetWindowButtonsEnabled(bool InWindowButtonsEnabled);`
- L50 _public prototype_ `bool IsWindowButtonsEnabled() const;`
- L52 _public prototype_ `void SetDoubleClickTogglesFullscreen(bool InDoubleClickTogglesFullscreen);`
- L54 _public prototype_ `bool IsDoubleClickTogglesFullscreen() const;`
- L59 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L63 _public prototype_ `virtual void PostLoad() override;`
- L68 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L74 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L80 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L81 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L82 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L87 _protected member_ `TSharedPtr<SWindowTitleBarArea> MyWindowTitleBarArea;` — Cached pointer to the underlying slate button owned by this UWidget
- L91 _private prototype_ `bool HandleWindowAction(const TSharedRef<FGenericWindow>& PlatformWindow, EWindowAction::Type WindowAction);`
- L92 _private prototype_ `void RequestToggleFullscreen();`
- L96 _private member_ `FDelegateHandle WindowActionNotificationHandle;`

### `Source/Runtime/UMG/Public/Components/WindowTitleBarAreaSlot.h` (Public)


#### class `UWindowTitleBarAreaSlot`  
`class UWindowTitleBarAreaSlot : public UPanelSlot`  
_L17-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UWindowTitleBarArea
- L23 _public prototype_ `FMargin GetPadding() const;`
- L26 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|WindowTitleBarArea Slot")`
- L28 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L31 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|WindowTitleBarArea Slot")`
- L33 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L36 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Layout|WindowTitleBarArea Slot")`
- L43 _protected member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetPadding", Category = "Layout|WindowTitleBarArea Slot")` — The padding area between the slot and the content it contains.
- L48 _protected member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetHorizontalAlignment", Category = "Layout|WindowTitleBarArea Slot")` — The alignment of the object horizontally.
- L53 _protected member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter = "SetVerticalAlignment", Category = "Layout|WindowTitleBarArea Slot")` — The alignment of the object vertically.
- L58 _public prototype_ `virtual void SynchronizeProperties() override;`
- L62 _public prototype_ `void BuildSlot(TSharedRef<SWindowTitleBarArea> WindowTitleBarArea);` — Builds the underlying FSlot for the Slate layout panel.
- L64 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L69 _private member_ `TSharedPtr<SWindowTitleBarArea> WindowTitleBarArea;` — A pointer to the window zone to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Components/WrapBox.h` (Public)


#### class `UWrapBox`  
`class UWrapBox : public UPanelWidget`  
_L22-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelWidget`
- desc: Arranges widgets left-to-right or top-to-bottom dependently of the orientation.  When the widgets exceed the wrapSize it will place widgets on the next line. * Many Children * Flows * Wraps
- L30 _public member_ `FVector2D InnerSlotPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetInnerSlotPadding", Category = "Content Layout")` — The inner slot padding goes between slots sharing borders
- L35 _public member_ `float WrapSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Content Layout", meta=(EditCondition = "bExplicitWrapSize"))` — When this size is exceeded, elements will start appearing on the next line.
- L40 _public member_ `bool bExplicitWrapSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter="UseExplicitWrapSize", Setter = "SetExplicitWrapSize", Category = "Content Layout")` — Use explicit wrap size whenever possible. It greatly simplifies layout calculations and reduces likelihood of "wiggling UI"
- L45 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetHorizontalAlignment", Category = "Content Layout", meta = (EditCondition = "Orientation == EOrientation::Orient_Horizontal"))` — The alignment of each line of wrapped content.
- L50 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Horizontal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Content Layout")` — Determines if the Wrap Box should arranges the widgets left-to-right or top-to-bottom
- L54 _public prototype_ `FVector2D GetInnerSlotPadding() const;` — Gets the inner slot padding goes between slots sharing borders
- L58 _public prototype_ `void SetInnerSlotPadding(FVector2D InPadding);` — `UFUNCTION(BlueprintCallable, Category="Content Layout")` — Sets the inner slot padding goes between slots sharing borders
- L61 _public prototype_ `float GetWrapSize() const;`
- L64 _public prototype_ `void SetWrapSize(float InWrapSize);`
- L67 _public prototype_ `bool UseExplicitWrapSize() const;`
- L70 _public prototype_ `void SetExplicitWrapSize(bool bInExplicitWrapSize);`
- L73 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L77 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Content Layout")`
- L80 _public prototype_ `EOrientation GetOrientation() const;`
- L83 _public prototype_ `void SetOrientation(EOrientation InOrientation);`
- L87 _public prototype_ `UWrapBoxSlot* AddChildToWrapBox(UWidget* Content);` — `UFUNCTION(BlueprintCallable, Category="Panel")`
- L91 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L98 _protected prototype_ `virtual UClass* GetSlotClass() const override;`
- L99 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* Slot) override;`
- L100 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* Slot) override;`
- L104 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L108 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L113 _protected member_ `TSharedPtr<class SWrapBox> MyWrapBox;`
- L117 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

### `Source/Runtime/UMG/Public/Components/WrapBoxSlot.h` (Public)


#### class `UWrapBoxSlot`  
`class UWrapBoxSlot : public UPanelSlot`  
_L16-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: The Slot for the UWrapBox, contains the widget that is flowed vertically
- L25 _public member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPadding", Category="Layout|Wrap Box Slot")` — The padding area between the slot and the content it contains.
- L33 _public member_ `float FillSpanWhenLessThan;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetFillSpanWhenLessThan", Category="Layout|Wrap Box Slot")` — If the total available space in the wrap panel drops below this threshold, this slot will attempt to fill an entire line. NOTE: A value of 0, denotes no filling will occur.
- L38 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Wrap Box Slot")` — The alignment of the object horizontally.
- L43 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Wrap Box Slot")` — The alignment of the object vertically.
- L48 _public member_ `bool bFillEmptySpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter="SetFillEmptySpace", BlueprintSetter="SetFillEmptySpace", Category = "Layout|Wrap Box Slot")` — Should this slot fill the remaining space on the line?
- L53 _public member_ `bool bForceNewLine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter="SetNewLine", BlueprintSetter="SetNewLine", Category = "Layout|Wrap Box Slot")` — Should this slot start on a new line?
- L57 _public prototype_ `FMargin GetPadding() const;`
- L60 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L62 _public prototype_ `bool DoesFillEmptySpace() const;`
- L65 _public prototype_ `void SetFillEmptySpace(bool InbFillEmptySpace);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L67 _public prototype_ `float GetFillSpanWhenLessThan() const;`
- L70 _public prototype_ `void SetFillSpanWhenLessThan(float InFillSpanWhenLessThan);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L72 _public prototype_ `EHorizontalAlignment GetHorizontalAlignment() const;`
- L75 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L77 _public prototype_ `EVerticalAlignment GetVerticalAlignment() const;`
- L80 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L82 _public prototype_ `bool DoesForceNewLine() const;`
- L85 _public prototype_ `void SetNewLine(bool InForceNewLine);` — `UFUNCTION(BlueprintCallable, Category="Layout|Wrap Box Slot")`
- L90 _public prototype_ `virtual void SynchronizeProperties() override;` — UPanelSlot interface
- L93 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L96 _public prototype_ `void BuildSlot(TSharedRef<SWrapBox> InWrapBox);` — Builds the underlying FSlot for the Slate layout panel.
- L102 _private member_ `SWrapBox::FSlot* Slot;` — A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime.

### `Source/Runtime/UMG/Public/Editor/WidgetCompilerLog.h` (Public)


#### class `IWidgetCompilerLog`  
`class IWidgetCompilerLog`  
_L15-46_
- L18 _public function_ `TSharedRef<FTokenizedMessage> Error(const FText& Message)`
- L26 _public function_ `TSharedRef<FTokenizedMessage> Warning(const FText& Message)`
- L34 _public function_ `TSharedRef<FTokenizedMessage> Note(const FText& Message)`
- L42 _public prototype_ `virtual TSubclassOf<UUserWidget> GetContextClass() const = 0;`
- L45 _protected prototype_ `virtual void InternalLogMessage(TSharedRef<FTokenizedMessage>& Message) = 0;`

### `Source/Runtime/UMG/Public/Extensions/ContextDataWidgetExtension.h` (Public)


#### class `UContextDataWidgetExtension`  
`class UContextDataWidgetExtension : public UUserWidgetExtension`  
_L13-48_
- reflection: `UCLASS()`
- inherits: `UUserWidgetExtension`
- desc: This extention is just a data container that can be used to attach arbitrary data to a widget
- L19 _public function_ `template <typename DataType> DataType* FindData() const`
- L24 _public function_ `UObject* FindData(const UClass* Class) const`
- L36 _public function_ `void AddData(UObject* Data)`
- L47 _private member_ `TArray<TObjectPtr<UObject>> ContextData;` — `UPROPERTY(Transient)`

### `Source/Runtime/UMG/Public/Extensions/UIComponent.h` (Public)


#### class `UUIComponent`  
`class UUIComponent : public UObject, public INotifyFieldValueChanged`  
_L25-106_
- reflection: `UCLASS(Abstract, MinimalAPI, CustomFieldNotify)`
- inherits: `UObject,INotifyFieldValueChanged`
- desc: This is the base class to for UI Components that can be added to any UMG Widgets in UMG Designer.When initialized, it will pass the widget it's attached to.
- L37 _public prototype_ `void Initialize(UWidget* Target);` — Called when the owner widget is initialized.
- L43 _public prototype_ `void PreConstruct(bool bIsDesignTime);` — Called when the owner widget is pre-constructed. Called in both Editor and runtime. @param bIsDesignTime True when the Widget is constructed for design time
- L48 _public prototype_ `void Construct();` — Called when the owner widget is constructed.
- L53 _public prototype_ `void Destruct();` — Called when the owner widget is destructed.
- L58 _public prototype_ `virtual void GraphRenamed(UEdGraph* Graph, const FName& OldName, const FName& NewName);` — Called when a graph owned by the user widget is renamed.
- L64 _public prototype_ `TWeakObjectPtr<UWidget> GetOwner() const;` — Returns the Owner Widget this component is attached to. @returns The owner widget
- L71 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidgetWithContent(TSharedRef<SWidget> Content);` — Called when the OwnerWidget is Rebuilt to allow to build a more complex hierarchy between the owner parents and the Owner widget. @param Content The Owner Widget Content. @returns The SWidget that wraps the Content passed.
- L74 _public prototype_ `virtual FDelegateHandle AddFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FFieldValueChangedDelegate InNewDelegate) override final;`
- L75 _public prototype_ `virtual bool RemoveFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FDelegateHandle InHandle) override final;`
- L76 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(FDelegateUserObjectConst InUserObject) override final;`
- L77 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(UE::FieldNotification::FFieldId InFieldId, FDelegateUserObjectConst InUserObject) override final;`
- L78 _public prototype_ `virtual void BroadcastFieldValueChanged(UE::FieldNotification::FFieldId InFieldId) override final;`
- L79 _public prototype_ `virtual const UE::FieldNotification::IClassDescriptor& GetFieldNotificationDescriptor() const override;`
- L89 _public prototype_ `virtual EDataValidationResult IsDataValidForOwner(const UWidget* OwnerWidget, FDataValidationContext& Context) const;` — Called during asset validation to validate this component in the context of its owner widget. Override to perform owner-aware validation. Calls IsDataValid by default. @param OwnerWidget	The widget this component is attached to, or nullptr if it could not be resolved. @param Context		The validation context to add errors/warnings to.
- L94 _protected prototype_ `virtual void OnInitialize();`
- L95 _protected prototype_ `virtual void OnPreConstruct(bool bIsDesignTime);`
- L96 _protected prototype_ `virtual void OnConstruct();`
- L97 _protected prototype_ `virtual void OnDestruct();`
- L98 _protected prototype_ `virtual void OnGraphRenamed(UEdGraph* Graph, const FName& OldName, const FName& NewName);`
- L102 _private member_ `TWeakObjectPtr<UWidget> Owner;` — `UPROPERTY(transient, DuplicateTransient)`
- L103 _private member_ `UE::FieldNotification::FFieldMulticastDelegate Delegates;`
- L105 _private member_ `bool bInitialized = false;`

#### struct `UUIComponent::FFieldNotificationClassDescriptor`  
`struct FFieldNotificationClassDescriptor : public ::UE::FieldNotification::IClassDescriptor`  
_L30-33_
- inherits: `::UE::FieldNotification::IClassDescriptor`
- L32 _public prototype_ `virtual void ForEachField(const UClass* Class, TFunctionRef<bool(UE::FieldNotification::FFieldId FielId)> Callback) const override;`

### `Source/Runtime/UMG/Public/Extensions/UIComponentContainer.h` (Public)


#### struct `FUIComponentTarget`  
`struct FUIComponentTarget`  
_L20-44_
- reflection: `USTRUCT()`
- L25 _public prototype_ `FUIComponentTarget();`
- L26 _public prototype_ `FUIComponentTarget(UUIComponent* Component, FName InChildName);`
- L29 _public prototype_ `UWidget* Resolve(const class UWidgetTree* WidgetTree);` — Resolves the Widget ptr using it's name.
- L30 _public function_ `FName GetTargetName() const`
- L31 _public prototype_ `void SetTargetName(FName NewName);`
- L32 _public function_ `UUIComponent* GetComponent() const`
- L33 _public function_ `bool IsValid() const`
- L40 _private member_ `FName TargetName;` — `UPROPERTY()` — We use a TargetName to resolve the Widget only at compile time and on the Runtime Widget. It simplify edition in UMG Designer and make sure we do not need to keep Association in sync with the WidgetTree.
- L43 _private member_ `TObjectPtr<UUIComponent> Component;` — `UPROPERTY(Instanced)`

#### class `UUIComponentContainer`  
`class UUIComponentContainer : public UObject`  
_L51-81_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType)`
- inherits: `UObject`
- desc: Class that holds all the UIComponents for a UUserWidget.
- L56 _public prototype_ `void AddComponent(FName TargetName, UUIComponent* Component);`
- L57 _public prototype_ `void RemoveComponent(FName TargetName, UUIComponent* Component);`
- L58 _public prototype_ `void RemoveAllComponentsOfType(const UClass* ComponentClass, FName TargetName);`
- L59 _public prototype_ `void RemoveAllComponentsFor(FName TargetName);`
- L61 _public prototype_ `void MoveComponent(FName TargetName, const UClass* ComponentClass, const UClass* RelativeToComponentClass, bool bMoveAfter);`
- L63 _public prototype_ `UUIComponent* GetComponent(const UClass* ComponentClass, FName TargetName) const;`
- L65 _public prototype_ `void ForEachComponent(TFunctionRef<void(UUIComponent*)> Predicate) const;`
- L66 _public prototype_ `void ForEachComponentTarget(TFunctionRef<void(const FUIComponentTarget&)> Predicate) const;`
- L68 _public prototype_ `void InitializeComponents(const UUserWidget* UserWidget);`
- L70 _public prototype_ `bool IsEmpty() const;`
- L72 _public prototype_ `static FName GetPropertyNameForComponent(const UUIComponent* Component, const FName& TargetName);`
- L74 _public prototype_ `void RenameWidget(const FName& OldName, const FName& NewName);`
- L75 _public prototype_ `void CleanupUIComponents(const UWidgetTree* WidgetTree);`
- L80 _private member_ `TArray<FUIComponentTarget> Components;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UMG_API`

### `Source/Runtime/UMG/Public/Extensions/UIComponentUserWidgetExtension.h` (Public)


#### class `UUIComponentUserWidgetExtension`  
`class UUIComponentUserWidgetExtension : public UUserWidgetExtension`  
_L21-62_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, DefaultToInstanced, Experimental)`
- inherits: `UUserWidgetExtension`
- desc: Class that holds all the UIComponents for a UUserWidget.
- L26 _public prototype_ `virtual void Initialize() override;`
- L27 _public prototype_ `virtual void PreConstruct(bool bIsDesignTime) override;`
- L28 _public prototype_ `virtual void Construct() override;`
- L29 _public prototype_ `virtual void Destruct() override;`
- L31 _public prototype_ `TArray<UUIComponent*> GetComponentsFor(UWidget* Target) const;`
- L32 _public prototype_ `UUIComponent* GetComponent(const UClass* ComponentClass, FName OwnerName) const;`
- L34 _public prototype_ `void InitializeContainer(UUIComponentContainer* InComponentContainer);`
- L35 _public prototype_ `bool IsContainerInitialized() const;`
- L39 _public prototype_ `virtual void InitializeInEditor() override;`
- L41 _public prototype_ `void RenameWidget(const FName& OldVarName, const FName& NewVarName);`
- L44 _public prototype_ `void CreateAndAddComponent(UUIComponent* ArchetypeComponent, FName OwnerName);` — Used only to create a Component on the PreviewWidget in the editor, based on the Component Archetype object in the WidgetBlueprint.
- L46 _public prototype_ `void RemoveComponent(const UClass* ComponentClass, FName OwnerName);`
- L48 _public prototype_ `void CleanupComponents();`
- L50 _public prototype_ `void MoveComponent(FName OwnerName, const UClass* ComponentClass, const UClass* RelativeToComponentClass, bool bMoveAfter);`
- L55 _private prototype_ `void InitializeComponents();`
- L59 _private member_ `TObjectPtr<UUIComponentContainer> ComponentContainer;` — `UPROPERTY(Transient, DuplicateTransient)` — Use a single TArray for the Entire UUserWidget to reduce memory usage.
- L61 _private member_ `bool bInitialized = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UMG_API`

### `Source/Runtime/UMG/Public/Extensions/UIComponentWidgetBlueprintGeneratedClassExtension.h` (Public)


#### class `UUIComponentWidgetBlueprintGeneratedClassExtension`  
`class UUIComponentWidgetBlueprintGeneratedClassExtension : public UWidgetBlueprintGeneratedClassExtension`  
_L21-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidgetBlueprintGeneratedClassExtension`
- desc: Class that hold the archetype version of the Components to be duplicated.
- L26 _public prototype_ `virtual void Initialize(UUserWidget* UserWidget) override;`
- L28 _public prototype_ `void InitializeContainer(UUIComponentContainer* InComponentContainer);`
- L30 _public prototype_ `virtual void PreConstruct(UUserWidget* UserWidget, bool IsDesignTime) override;`
- L33 _public prototype_ `virtual void InitializeInEditor(UUserWidget* UserWidget) override;`
- L34 _public prototype_ `bool VerifyAllWidgetsExists(const UWidgetTree* WidgetTree) const;`
- L38 _private prototype_ `UUIComponentContainer* DuplicateContainer(UUserWidget* UserWidget) const;`
- L39 _private prototype_ `bool VerifyContainer(const UUserWidget* UserWidget) const;`
- L42 _private member_ `TObjectPtr<UUIComponentContainer> ComponentContainer;` — `UPROPERTY(DuplicateTransient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UMG_API`

### `Source/Runtime/UMG/Public/Extensions/UIComponents/NavigationUIComponent.h` (Public)


#### class `UNavigationUIComponent`  
`class UNavigationUIComponent : public UUIComponent`  
_L21-53_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UUIComponent`
- L26 _private prototype_ `virtual void OnConstruct() override;`
- L27 _private prototype_ `virtual void OnDestruct() override;`
- L28 _private prototype_ `virtual void OnGraphRenamed(UEdGraph* Graph, const FName& OldName, const FName& NewName) override;`
- L30 _private prototype_ `void HandleNavigationTransition(const FNavigationTransition& NavigationTransition);`
- L38 _public member_ `FName OnNavigationEntered;` — `UPROPERTY()` — FNames are references to user provided functions. No direct access to properties, modifiable in DetailsView via FNavigationUIComponentCustomization::CustomizeNavigationTransitionFunction
- L41 _public member_ `FName OnNavigationExited;` — `UPROPERTY()`
- L47 _private member_ `FOnNavigationTransition OnNavigationEnteredDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Navigation", meta = (AllowPrivateAccess = true, DisplayName = "On Navigation Entered"))` — Delegates are the concrete functions from the provided user provided function names
- L50 _private member_ `FOnNavigationTransition OnNavigationExitedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Navigation", meta = (AllowPrivateAccess = true, DisplayName = "On Navigation Exited"))`
- L52 _private member_ `TSharedPtr<FNavigationTransitionMetadata> NavigationTransitionMetadata;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNavigationTransition, EUINavigation, Type, UWidget*, OldFocusedWidget, UWidget*, NewFocusedWidget);` — If Entered, Other Widget is the Widget Navigated From If Exited , Other Widget is the Widget Navigated To
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNavigationTransition, EUINavigation, Type, UWidget*, OldFocusedWidget, UWidget*, NewFocusedWidget);` — If Entered, Other Widget is the Widget Navigated From If Exited , Other Widget is the Widget Navigated To

### `Source/Runtime/UMG/Public/Extensions/UserWidgetExtension.h` (Public)


#### class `UUserWidgetExtension`  
`class UUserWidgetExtension : public UObject`  
_L19-69_
- reflection: `UCLASS(Abstract, DefaultToInstanced, Within=UserWidget, MinimalAPI)`
- inherits: `UObject`
- desc: UserWidgetExtension is the base class for components that define reusable behavior that can be added to different types of Widgets.
- L27 _public function_ `virtual void InitializeInEditor()` — Initialize function called only in Editor
- L31 _public function_ `virtual void Initialize()` — Extend the UUserWidget::Initialize function
- L36 _public function_ `virtual void PreConstruct(bool bIsDesignTime)` — Extend the UUserWidget::PreConstruct function
- L41 _public function_ `virtual void Construct()` — Extend the UUserWidget::Construct function
- L46 _public function_ `virtual void Destruct()` — Extend the UUserWidget::Destruct function
- L51 _public function_ `virtual bool RequiresTick() const` — Does the extension requires tick.
- L60 _public function_ `virtual void Tick(const FGeometry& MyGeometry, float InDeltaTime)` — Extend the UUserWidget::Tick function. If the UserWidget ticks, then all extensions will tick regardless of RequiresTick.
- L65 _protected function_ `UUserWidget* GetUserWidget() const`

### `Source/Runtime/UMG/Public/Extensions/WidgetBlueprintGeneratedClassExtension.h` (Public)


#### class `UWidgetBlueprintGeneratedClassExtension`  
`class UWidgetBlueprintGeneratedClassExtension : public UObject`  
_L15-42_
- reflection: `UCLASS(Abstract, DefaultToInstanced, MinimalAPI)`
- inherits: `UObject`
- desc: WidgetExtension is the base class for components that define reusable behavior that can be added to different types of Widgets.
- L23 _public function_ `virtual void InitializeInEditor(UUserWidget* UserWidget)` — Initialize function called only in Editor
- L29 _public function_ `virtual void Initialize(UUserWidget* UserWidget)` — Extend the UUserWidget::Initialize function. Called once when the UUserWidget is created.
- L31 _public function_ `virtual void PreConstruct(UUserWidget* UserWidget, bool IsDesignTime)` — Extend the UUserWidget::PreConstruct function
- L36 _public function_ `virtual void Construct(UUserWidget* UserWidget)` — Extend the UUserWidget::Construct function. Called after when the SWidget is created. (TakeWidget)
- L41 _public function_ `virtual void Destruct(UUserWidget* UserWidget)` — Extend the UUserWidget::Destruct function. Called when the SWidget is going to be destroy. (ReleaseSlateWidget)

### `Source/Runtime/UMG/Public/FieldNotification/FieldId.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void FieldIdHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/FieldId.h is deprecated. The file location changed. Please include FieldNotificationId.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerFieldIdHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/FieldMulticastDelegate.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void FieldMulticastDelegateHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/FieldMulticastDelegate.h is deprecated. The file location changed. Please include FieldNotificationDelegate.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerFieldMulticastDelegateHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/FieldNotificationDeclaration.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void FieldNotificationDeclarationHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/FieldNotificationDeclaration.h is deprecated. The location of has changed. Please include FieldNotificationDeclaration.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerFieldNotificationDeclarationHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/FieldNotificationHelpers.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void FieldNotificationHelpersHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/FieldNotificationHelpers.h is deprecated. The file location changed. Please include FieldNotificationHelpers.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerFieldNotificationHelpersHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/FieldVariant.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void FieldVariantHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/FieldVariant.h is deprecated. The file location changed. Please include FieldNotificationVariant.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerFieldVariantHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/IClassDescriptor.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void IClassDescriptorHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/IClassDescriptor.h is deprecated. The file location changed. Please include IFieldNotificationClassDescriptor.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerIClassDescriptorHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/IFieldValueChanged.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void IFieldValueChangedHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.3, "Including FieldNotification/IFieldValueChanged.h is deprecated. The file location changed. Please include INotifyFieldValueChanged.h instead and add the module FieldNotification to your .build.cs")`
- L13 _function_ `inline void TriggerIFieldValueChangedHeaderDeprecatedWarning()`

### `Source/Runtime/UMG/Public/FieldNotification/WidgetEventField.h` (Public)


#### struct `FWidgetEventField`  
`struct FWidgetEventField`  
_L23-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: Generic structure to notify when an event occurs. class UMyWidget : public UWidget { UPROPERTY(FieldNotify) FWidgetEventField SomeEvent; void OnSomeEvent() { BroadcastFieldValueChanged(FFieldNotificationClassDescriptor::Text); } }; };

### `Source/Runtime/UMG/Public/IUMGModule.h` (Public)


#### class `IUMGModule`  
`class IUMGModule : public IModuleInterface`  
_L11-15_
- inherits: `IModuleInterface`
- desc: Interface for the UMG Module.

### `Source/Runtime/UMG/Public/Slate/SMeshWidget.h` (Public)


#### class `SMeshWidget`  
`class SMeshWidget : public SLeafWidget, public FGCObject`  
_L23-128_
- inherits: `SLeafWidget,FGCObject`
- desc: A widget that draws vertexes provided by a 2.5D StaticMesh. The Mesh's material is used. Hardware instancing is supported.
- L26 _public function_ `SLATE_BEGIN_ARGS(SMeshWidget) : _MeshData(nullptr)`
- L30 _public prototype_ `SLATE_ARGUMENT(USlateVectorArtData*, MeshData) SLATE_END_ARGS() void Construct(const FArguments& Args);` — The StaticMesh asset that should be drawn.
- L40 _public prototype_ `uint32 AddMesh(USlateVectorArtData& InMeshData);` — Draw the InStaticMesh when this widget paints. @return the Index of the mesh data that was added; cache this value for use with @see FRenderRun.
- L43 _public prototype_ `uint32 AddMeshWithInstancing(USlateVectorArtData& InMeshData, int32 InitialBufferSize = 1);` — Much like AddMesh, but also enables instancing support for this MeshId.
- L52 _public prototype_ `UMaterialInstanceDynamic* ConvertToMID( uint32 MeshId );` — Switch from static material to material instance dynamic. @param MeshId    The index of the mesh; returned from AddMesh. @return The MID for this Asset on which parameters can be set.
- L55 _public prototype_ `void ClearRuns(int32 NumRuns);` — Discard any previous runs and reserve space for new render runs if needed.
- L65 _public function_ `inline void AddRenderRun(uint32 InMeshIndex, uint32 InInstanceOffset, uint32 InNumInstances)` — Tell the widget to draw instances of a mesh a given number of times starting at a given offset. @param InMeshIndex        Which mesh to draw; returned by @see AddMesh @param InInstanceOffset   Start drawing with this instance @param InNumInstances     Draw this many instances
- L71 _public prototype_ `void EnableInstancing(uint32 MeshId, int32 InitialSize);` — Enable hardware instancing
- L74 _public prototype_ `void UpdatePerInstanceBuffer(uint32 MeshId, FSlateInstanceBufferData& Data);` — Updates the per instance buffer. Automatically enables hardware instancing.
- L78 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — BEGIN SLeafWidget interface
- L79 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L83 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L84 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L88 _protected prototype_ `static void PushUpdate(uint32 VectorArtId, SMeshWidget& Widget, const FVector2D& Position, float Scale, uint32 BaseAddress);`
- L89 _protected prototype_ `static void PushUpdate(uint32 VectorArtId, SMeshWidget& Widget, const FVector2D& Position, float Scale, float OptionalFloat = 0);`
- L104 _protected member_ `TArray<FRenderData, TInlineAllocator<3>> RenderData;`
- L127 _private member_ `TArray<FRenderRun> RenderRuns;`

#### struct `SMeshWidget::FRenderData`  
`struct FRenderData`  
_L91-103_
- L94 _public member_ `TArray<FSlateVertex> VertexData;` — Holds a copy of the Static Mesh's data converted to a format that Slate understands.
- L96 _public member_ `TArray<SlateIndex> IndexData;` — Connectivity data: Order in which the vertexes occur to make up a series of triangles.
- L98 _public member_ `TSharedPtr<FSlateBrush> Brush;` — Holds on to the material that is found on the StaticMesh.
- L100 _public member_ `FSlateResourceHandle RenderingResourceHandle;` — A rendering handle used to quickly access the rendering data for the slate element
- L102 _public member_ `TSharedPtr<ISlateUpdatableInstanceBuffer> PerInstanceBuffer;` — Per instance data that can be passed to

#### class `SMeshWidget::FRenderRun`  
`class FRenderRun`  
_L108-126_
- desc: Which mesh to draw, starting with which instance offset and how many instances to draw in this run/batch.
- L111 _public function_ `FRenderRun(uint32 InMeshIndex, uint32 InInstanceOffset, uint32 InNumInstances) : MeshIndex(InMeshIndex) , InstanceOffset(InInstanceOffset) , NumInstances(InNumInstances)`
- L118 _public function_ `uint32 GetMeshIndex() const`
- L119 _public function_ `uint32 GetInstanceOffset() const`
- L120 _public function_ `uint32 GetNumInstances() const`
- L123 _private member_ `uint32 MeshIndex;`
- L124 _private member_ `uint32 InstanceOffset;`
- L125 _private member_ `uint32 NumInstances;`

### `Source/Runtime/UMG/Public/Slate/SObjectTableRow.h` (Public)


#### class `IObjectTableRow`  
`class IObjectTableRow : public ITableRow`  
_L17-37_
- inherits: `ITableRow`
- L20 _public prototype_ `virtual UListViewBase* GetOwningListView() const = 0;`
- L21 _public prototype_ `virtual UUserWidget* GetUserWidget() const = 0;`
- L23 _public function_ `static TSharedPtr<const IObjectTableRow> ObjectRowFromUserWidget(const UUserWidget* RowUserWidget)`
- L36 _protected member_ `static TMap<TWeakObjectPtr<const UUserWidget>, TWeakPtr<const IObjectTableRow>> ObjectRowsByUserWidget;` — Intentionally being a bit nontraditional here - we track associations between UserWidget rows and their underlying IObjectTableRow. This allows us to mirror the ITableRow API very easily on IUserListEntry without requiring rote setting/getting of row states on every UMG subclass.

#### class `SObjectTableRow`  
`template <typename ItemType> class SObjectTableRow : public SObjectWidget, public IObjectTableRow`  
_L60-853_
- inherits: `SObjectWidget,IObjectTableRow`
- desc: It's an SObjectWidget! It's an ITableRow! It does it all! By using UUserWidget::TakeDerivedWidget<T>(), this class allows UMG to fully leverage the robust Slate list view widgets. The major gain from this is item virtualization, which is an even bigger deal when unnecessary widgets come with a boatload of additional UObject allocations. The owning UUserWidget is expected to implement the IUserListEntry UInterface, which allows the row widget to respond to various list-related events. Note: Much of the implementation here matches STableRow<T> exactly, so refer there if looking for additional information.
- L63 _public function_ `SLATE_BEGIN_ARGS(SObjectTableRow<ItemType>) :_bAllowDragging(true) ,_bAllowDragDrop(false)`
- L84 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, UUserWidget& InWidgetObject, UListViewBase* InOwnerListView = nullptr)`
- L127 _public function_ `virtual ~SObjectTableRow()`
- L133 _public function_ `virtual UUserWidget* GetUserWidget() const`
- L138 _public function_ `virtual UListViewBase* GetOwningListView() const`
- L147 _public function_ `EActiveTimerReturnType DetectItemSelectionChanged(double InCurrentTime, float InDeltaTime)`
- L153 _public function_ `virtual void NotifyItemExpansionChanged(bool bIsExpanded)`
- L162 _public function_ `virtual void InitializeRow() override final`
- L171 _public function_ `virtual void ResetRow() override final`
- L179 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L183 _public function_ `virtual void SetIndexInList(int32 InIndexInList) override`
- L187 _public function_ `virtual int32 GetIndexInList() override`
- L191 _public function_ `virtual TSharedPtr<SWidget> GetContent() override`
- L195 _public function_ `virtual int32 GetIndentLevel() const override`
- L200 _public function_ `virtual int32 DoesItemHaveChildren() const override`
- L205 _public function_ `virtual void Private_OnExpanderArrowShiftClicked() override`
- L209 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L214 _public function_ `virtual FVector2D GetRowSizeForColumn(const FName& InColumnName) const override`
- L219 _public function_ `virtual bool IsItemExpanded() const override`
- L231 _public function_ `virtual void ToggleExpansion() override`
- L243 _public function_ `virtual bool IsItemSelected() const override`
- L255 _public function_ `virtual TBitArray<> GetWiresNeededByDepth() const override`
- L261 _public function_ `virtual bool IsLastChild() const override`
- L270 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L275 _public function_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L284 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L293 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L308 _public function_ `virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L317 _public function_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L365 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L427 _public function_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L438 _public function_ `virtual void OnDragLeave(FDragDropEvent const& DragDropEvent) override`
- L453 _public function_ `EItemDropZone ZoneFromPointerPosition(UE::Slate::FDeprecateVector2DParameter LocalPointerPos, UE::Slate::FDeprecateVector2DParameter LocalSize, EOrientation Orientation)` — @return the zone (above, onto, below) based on where the user is hovering over within the row
- L473 _public function_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L501 _public function_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L571 _public function_ `void OnDragCancelled(const FDragDropEvent& DragDropEvent, UDragDropOperation* Operation) override`
- L582 _public function_ `virtual void HandleEntryDropped(UDragDropOperation* Operation)`
- L590 _public function_ `virtual void HandleEntryDragged(UDragDropOperation* Operation)`
- L598 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L664 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L740 _public function_ `bool GetAllowDragDrop() const`
- L746 _protected function_ `virtual void InitializeObjectRow()`
- L762 _protected function_ `virtual void ResetObjectRow()`
- L771 _protected function_ `virtual void DetectItemSelectionChanged()`
- L789 _protected function_ `virtual void OnItemSelectionChanged(bool bIsItemSelected)`
- L797 _protected function_ `bool IsItemSelectable() const`
- L803 _protected function_ `const TObjectPtrWrapTypeOf<ItemType>* GetItemForThis(const TSharedRef<ITypedTableView<ItemType>>& OwnerTable) const`
- L818 _protected member_ `FOnRowHovered OnHovered;`
- L819 _protected member_ `FOnRowHovered OnUnhovered;`
- L820 _protected member_ `FOnObjectRowCanAcceptDrop OnRowCanAcceptDrop;`
- L821 _protected member_ `FOnObjectRowAcceptDrop OnRowAcceptDrop;`
- L822 _protected member_ `FOnObjectRowDragDetected OnRowDragDetected;`
- L823 _protected member_ `FOnObjectRowDragEnter OnRowDragEnter;`
- L824 _protected member_ `FOnObjectRowDragLeave OnRowDragLeave;`
- L825 _protected member_ `FOnObjectRowDragCancelled OnRowDragCancelled;`
- L827 _protected member_ `TWeakObjectPtr<UListViewBase> OwnerListView;`
- L828 _protected member_ `TWeakPtr<ITypedTableView<ItemType>> OwnerTablePtr;`
- L831 _private function_ `void InitObjectRowInternal(UUserWidget& ListEntryWidget, ItemType ListItemObject)`
- L833 _private member_ `int32 IndexInList = INDEX_NONE;`
- L834 _private member_ `bool bChangedSelectionOnMouseDown = false;`
- L835 _private member_ `bool bIsAppearingSelected = false;`
- L837 _private member_ `bool bProcessingSelectionTouch = false;`
- L840 _private member_ `bool bAllowKeepPreselectedItems = true;` — If true, when selecting an item via mouse button, we allow pre-selected items to remain selected
- L843 _private member_ `bool bAllowDragging;` — Whether to allow dragging of this item
- L846 _private member_ `bool bAllowDragDrop;` — Whether to allow drag drop operations to be performed on the list
- L849 _private member_ `bool bDragWasDetected = false;` — Whether or not drag was detected
- L852 _private member_ `TOptional<EItemDropZone> ItemDropZone;` — Are we currently dragging/dropping over this item?
- L856 _function_ `template <> inline void SObjectTableRow<UObject*>::InitObjectRowInternal(UUserWidget& ListEntryWidget, UObject* ListItemObject)`

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRowHovered, UUserWidget&);`
- L39 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRowHovered, UUserWidget&);`
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<EItemDropZone>, FOnObjectRowCanAcceptDrop, const FDragDropEvent&, EItemDropZone, UUserWidget&);`
- L40 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<EItemDropZone>, FOnObjectRowCanAcceptDrop, const FDragDropEvent&, EItemDropZone, UUserWidget&);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnObjectRowAcceptDrop, const FDragDropEvent&, EItemDropZone, UUserWidget&);`
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnObjectRowAcceptDrop, const FDragDropEvent&, EItemDropZone, UUserWidget&);`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(UDragDropOperation*, FOnObjectRowDragDetected, const FGeometry&, const FPointerEvent&, UUserWidget&);`
- L42 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(UDragDropOperation*, FOnObjectRowDragDetected, const FGeometry&, const FPointerEvent&, UUserWidget&);`
- L43 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnObjectRowDragEnter, FDragDropEvent const&, UUserWidget&);`
- L43 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnObjectRowDragEnter, FDragDropEvent const&, UUserWidget&);`
- L44 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnObjectRowDragLeave, FDragDropEvent const&, UUserWidget&);`
- L44 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnObjectRowDragLeave, FDragDropEvent const&, UUserWidget&);`
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectRowDragCancelled, const FDragDropEvent&);`
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectRowDragCancelled, const FDragDropEvent&);`
- L484 _function_ `` (scope `SObjectTableRow::OnDragOver`)

### `Source/Runtime/UMG/Public/Slate/SObjectWidget.h` (Public)


#### class `SObjectWidget`  
`class SObjectWidget : public SCompoundWidget, public FGCObject`  
_L30-127_
- inherits: `SCompoundWidget,FGCObject`
- desc: The SObjectWidget allows UMG to insert an SWidget into the hierarchy that manages the lifetime of the UMG UWidget that created it.  Once the SObjectWidget is destroyed it frees the reference it holds to The UWidget allowing it to be garbage collected.  It also forwards the slate events to the UUserWidget so that it can forward them to listeners.
- L33 _private function_ `SLATE_BEGIN_ARGS(SObjectWidget)`
- L38 _private prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() SObjectWidget();`
- L42 _private prototype_ `virtual ~SObjectWidget();`
- L44 _private prototype_ `void Construct(const FArguments& InArgs, UUserWidget* InWidgetObject);`
- L46 _private prototype_ `void ResetWidget();`
- L49 _private prototype_ `virtual FString GetReferencerName() const override;` — FGCObject interface
- L50 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L53 _private function_ `UUserWidget* GetWidgetObject() const`
- L55 _private prototype_ `void SetPadding(const TAttribute<FMargin>& InMargin);`
- L58 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget Tick override.  Note this will not be called if bCanTick is set to false by the UserWidget
- L59 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L61 _private prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L63 _private prototype_ `virtual bool IsInteractable() const override;`
- L64 _private prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L66 _private prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L67 _private prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L68 _private prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;`
- L70 _private prototype_ `virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;`
- L71 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L72 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L73 _private prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L74 _private prototype_ `virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L76 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L77 _private prototype_ `virtual FReply OnPreviewMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L78 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L79 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L80 _private prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L81 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L82 _private prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L83 _private prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L84 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L86 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L87 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L88 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L89 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L90 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L92 _private prototype_ `virtual void OnDragCancelled(const FDragDropEvent& DragDropEvent, UDragDropOperation* Operation);`
- L94 _private prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent) override;`
- L95 _private prototype_ `virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L96 _private prototype_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L97 _private prototype_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L98 _private prototype_ `virtual FReply OnMotionDetected(const FGeometry& MyGeometry, const FMotionEvent& InMotionEvent) override;`
- L99 _private prototype_ `virtual FReply OnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L100 _private prototype_ `virtual FReply OnTouchFirstMove(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L101 _private prototype_ `virtual void OnFinishedPointerInput() override;`
- L103 _private prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;`
- L105 _private prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L109 _protected member_ `TObjectPtr<UUserWidget> WidgetObject;` — The UWidget that created this SObjectWidget who needs to be kept alive.
- L112 _private function_ `inline bool CanRouteEvent() const`
- L117 _private function_ `inline bool CanRoutePaint() const`
- L123 _private member_ `FString DebugName;`
- L124 _private member_ `FString DebugTickEventName;`
- L125 _private member_ `FString DebugPaintEventName;`

### `Source/Runtime/UMG/Public/Slate/SPostBufferUpdate.h` (Public)


#### class `FSlatePostProcessorUpdaterProxy`  
`class FSlatePostProcessorUpdaterProxy : public TSharedFromThis<FSlatePostProcessorUpdaterProxy>`  
_L28-37_
- inherits: `TSharedFromThis<FSlatePostProcessorUpdaterProxy>`
- desc: Class that can update a given Slate post buffer processor via its renderthread proxy. This proxy is also deleted on the renderthread
- L34 _public prototype_ `virtual ~FSlatePostProcessorUpdaterProxy () = default;`
- L36 _public prototype_ `virtual void UpdateProcessor_RenderThread(TSharedPtr<FSlateRHIPostBufferProcessorProxy>) const = 0;`

#### class `SPostBufferUpdate`  
`class SPostBufferUpdate : public SLeafWidget`  
_L42-111_
- inherits: `SLeafWidget`
- desc: Implements a widget that triggers a post buffer update on draw
- L48 _public function_ `SLATE_BEGIN_ARGS( SPostBufferUpdate ) : _bUsePaintGeometry(false)`
- L53 _public prototype_ `SLATE_ARGUMENT(bool, bUsePaintGeometry) SLATE_END_ARGS() SPostBufferUpdate();` — True if we should perform the default post buffer update
- L64 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param	InArgs	The declaration data for this widget
- L68 _public prototype_ `void SetUsePaintGeometry(bool bInUsePaintGeometry);` — Set if we should use paint geometry
- L76 _public prototype_ `void SetBuffersToUpdate(const TArrayView<ESlatePostRT> InBuffersToUpdate);` — Set buffers to, this method only affects the 'FPostBufferUpdater' custom drawer once during initialization. Afterwards it will be a no-op due to the custom drawer having update buffers initialized. This set-once behavior is done to avoid renderthread race conditions, & since you shouldn't need to modify the buffers to update at runtime since we only draw if used anyway.
- L81 _public prototype_ `void SetProcessorUpdaters(TMap<ESlatePostRT, TSharedPtr<FSlatePostProcessorUpdaterProxy>> InProcessorUpdaters);` — Set processsor updaters for the given buffers by index.
- L84 _public prototype_ `const TArrayView<const ESlatePostRT> GetBuffersToUpdate() const;` — Get buffers to update
- L87 _public prototype_ `void ReleasePostBufferUpdater();` — Release Post Buffer Updater, called out of caution in case of reuse during 'ReleaseSlateResources' in UWidget
- L92 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L98 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L104 _private member_ `bool bUsePaintGeometry;` — True if we should limit processing to our paint geometry
- L107 _private member_ `TArray<ESlatePostRT> BuffersToUpdate;` — Buffers that we should update, all of these buffers will be affected by 'bPerformDefaultPostBufferUpdate' if disabled
- L110 _private member_ `TSharedPtr<FPostBufferUpdater> PostBufferUpdater;` — Custom drawer used to trigger a post buffer update

### `Source/Runtime/UMG/Public/Slate/SRetainerWidget.h` (Public)


#### class `SRetainerWidget`  
`class SRetainerWidget : public SCompoundWidget, public FSlateInvalidationRoot`  
_L39-189_
- inherits: `SCompoundWidget,FSlateInvalidationRoot`
- desc: The SRetainerWidget renders children widgets to a render target first before later rendering that render target to the screen.  This allows both frequency and phase to be controlled so that the UI can actually render less often than the frequency of the main game render.  It also has the side benefit of allow materials to be applied to the render target after drawing the widgets to apply a simple post process.
- L42 _public member_ `static int32 Shared_MaxRetainerWorkPerFrame;`
- L45 _public function_ `SLATE_BEGIN_ARGS(SRetainerWidget)`
- L53 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(bool, RenderOnPhase) SLATE_ARGUMENT(bool, RenderOnInvalidation) SLATE_ARGUMENT_DEPRECATED(bool, RenderWithLocalTransform, 5.4, "This argument has no effect anymore, because bugs from each render path (with RenderWithLocalTransform set to true or false) have been fixed, making it no longer necessary.") SLATE_ARGUMENT(int32, Phase) SLATE_ARGUMENT(int32, PhaseCount) SLATE_ARGUMENT(FName, StatId) #if WITH_EDITOR SLATE_ARGUMENT(bool, bWarnOnInvalidSize) #endif SLATE_END_ARGS() SRetainerWidget();`
- L66 _public prototype_ `~SRetainerWidget();`
- L69 _public prototype_ `void Construct(const FArguments& Args);` — Constructor
- L71 _public prototype_ `void SetRenderingPhase(int32 Phase, int32 PhaseCount);`
- L74 _public prototype_ `void RequestRender();` — Requests that the retainer redraw the hosted content next time it's painted.
- L77 _public prototype_ `void SetIsDesignTime(bool bInIsDesignTime);`
- L78 _public prototype_ `void SetShowEffectsInDesigner(bool bInShowEffectsInDesigner);`
- L81 _public prototype_ `void SetRetainedRendering(bool bRetainRendering);`
- L83 _public prototype_ `void SetContent(const TSharedRef< SWidget >& InContent);`
- L85 _public prototype_ `UMaterialInstanceDynamic* GetEffectMaterial() const;`
- L87 _public prototype_ `void SetEffectMaterial(UMaterialInterface* EffectMaterial);`
- L89 _public prototype_ `void SetTextureParameter(FName TextureParameter);`
- L92 _public prototype_ `virtual FChildren* GetChildren() override;`
- L94 _public prototype_ `virtual FChildren* Debug_GetChildrenForReflector() override;`
- L97 _public prototype_ `void SetWorld(UWorld* World);`
- L101 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SCompoundWidget interface
- L102 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float Scale) const override;`
- L103 _protected function_ `virtual bool Advanced_IsInvalidationRoot() const`
- L104 _protected function_ `virtual const FSlateInvalidationRoot* Advanced_AsInvalidationRoot() const override`
- L105 _protected prototype_ `virtual bool CustomPrepass(float LayoutScaleMultiplier) override;`
- L108 _protected prototype_ `virtual TSharedRef<SWidget> GetRootWidget() override;`
- L109 _protected prototype_ `virtual int32 PaintSlowPath(const FSlateInvalidationContext& Context) override;`
- L119 _protected prototype_ `EPaintRetainedContentResult PaintRetainedContentImpl(const FSlateInvalidationContext& Context, const FGeometry& AllottedGeometry, int32 LayerId);`
- L122 _protected prototype_ `void RefreshRenderingMode();`
- L123 _protected prototype_ `bool ShouldBeRenderingOffscreen() const;`
- L124 _protected prototype_ `bool IsAnythingVisibleToRender() const;`
- L125 _protected prototype_ `void OnRetainerModeChanged();`
- L126 _protected prototype_ `void OnRootInvalidated();`
- L129 _private prototype_ `void OnGlobalInvalidationToggled(bool bGlobalInvalidationEnabled);`
- L131 _private prototype_ `static void OnRetainerModeCVarChanged( IConsoleVariable* CVar );`
- L132 _private member_ `static FOnRetainedModeChanged OnRetainerModeChangedDelegate;`
- L135 _private member_ `mutable FSlateBrush SurfaceBrush;`
- L137 _private member_ `FIntPoint PreviousRenderSize;`
- L138 _private member_ `FGeometry PreviousAllottedGeometry;`
- L139 _private member_ `FIntPoint PreviousClipRectSize;`
- L140 _private member_ `TOptional<FSlateClippingState> PreviousClippingState;`
- L141 _private member_ `FColor PreviousColorAndOpacity;`
- L142 _private member_ `int32 LastIncomingLayerId;`
- L144 _private prototype_ `void UpdateWidgetRenderer();`
- L146 _private member_ `TSharedPtr<SWidget> MyWidget;`
- L147 _private member_ `TSharedRef<SVirtualWindow> VirtualWindow;`
- L149 _private member_ `TSharedRef<FHittestGrid> HittestGrid;`
- L151 _private member_ `int32 Phase;`
- L152 _private member_ `int32 PhaseCount;`
- L154 _private member_ `bool bEnableRetainedRenderingDesire;`
- L155 _private member_ `bool bEnableRetainedRendering;`
- L159 _private member_ `bool bIsDesignTime;` — True if widget is used in design time
- L162 _private member_ `bool bShowEffectsInDesigner;` — True if we should retain rendering in designer
- L165 _private member_ `bool bWarnOnInvalidSize;` — True if we should warn when the requested size for the retainer is 0 or too large
- L168 _private member_ `bool RenderOnPhase;`
- L169 _private member_ `bool RenderOnInvalidation;`
- L171 _private member_ `bool bRenderRequested;`
- L172 _private member_ `bool bInvalidSizeLogged;`
- L174 _private member_ `double LastDrawTime;`
- L175 _private member_ `int64 LastTickedFrame;`
- L177 _private member_ `TWeakObjectPtr<UWorld> OuterWorld;`
- L179 _private member_ `FRetainerWidgetRenderingResources* RenderingResources;`
- L181 _private prototype_ `STAT(TStatId MyStatId;) FSlateBrush DynamicBrush;`
- L185 _private member_ `FName DynamicEffectTextureParameter;`
- L187 _private member_ `static TArray<SRetainerWidget*, TInlineAllocator<3>> Shared_WaitingToRender;`
- L188 _private member_ `static TFrameValue<int32> Shared_RetainerWorkThisFrame;`

#### enum `SRetainerWidget::EPaintRetainedContentResult`  
`enum class EPaintRetainedContentResult`  
_L111-118_
- L113 _public enumerator_ `NotPainted`
- L114 _public enumerator_ `Painted`
- L115 _public enumerator_ `Queued`
- L116 _public enumerator_ `TextureSizeTooBig`
- L117 _public enumerator_ `TextureSizeZero`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE( FOnRetainedModeChanged );`
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE( FOnRetainedModeChanged );`

### `Source/Runtime/UMG/Public/Slate/SWorldWidgetScreenLayer.h` (Public)


#### class `SWorldWidgetScreenLayer`  
`class SWorldWidgetScreenLayer : public SCompoundWidget`  
_L15-64_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SWorldWidgetScreenLayer)`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const FLocalPlayerContext& InPlayerContext);`
- L26 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L27 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L29 _public prototype_ `void SetWidgetDrawSize(FVector2D DrawSize);`
- L31 _public prototype_ `void SetWidgetPivot(FVector2D Pivot);`
- L33 _public prototype_ `void AddComponent(USceneComponent* Component, TSharedRef<SWidget> Widget);`
- L35 _public prototype_ `void RemoveComponent(USceneComponent* Component);`
- L38 _private member_ `FLocalPlayerContext PlayerContext;`
- L40 _private member_ `FVector2D DrawSize;`
- L41 _private member_ `FVector2D Pivot;`
- L60 _private prototype_ `void RemoveEntryFromCanvas(SWorldWidgetScreenLayer::FComponentEntry& Entry);`
- L62 _private member_ `TMap<FObjectKey, FComponentEntry> ComponentMap;`
- L63 _private member_ `TSharedPtr<SConstraintCanvas> Canvas;`

#### class `SWorldWidgetScreenLayer::FComponentEntry`  
`class FComponentEntry`  
_L43-58_
- L46 _public prototype_ `FComponentEntry();`
- L47 _public prototype_ `~FComponentEntry();`
- L51 _public member_ `bool bRemoving = false;`
- L52 _public member_ `TWeakObjectPtr<USceneComponent> Component;`
- L53 _public member_ `class UWidgetComponent* WidgetComponent;`
- L55 _public member_ `TSharedPtr<SWidget> ContainerWidget;`
- L56 _public member_ `TSharedPtr<SWidget> Widget;`
- L57 _public member_ `SConstraintCanvas::FSlot* Slot;`

### `Source/Runtime/UMG/Public/Slate/SlateVectorArtData.h` (Public)


#### struct `FSlateMeshVertex`  
`struct FSlateMeshVertex`  
_L15-78_
- reflection: `USTRUCT()`
- L19 _public member_ `static const int32 MaxNumUVs = 6;`
- L21 _public function_ `FSlateMeshVertex() : Position(FVector2f::ZeroVector) , Color(ForceInitToZero) , UV0(FVector2f::ZeroVector) , UV1(FVector2f::ZeroVector) , UV2(FVector2f::ZeroVector) , UV3(FVector2f::ZeroVector) , UV4(FVector2f::ZeroVector) , UV5(FVector2f::ZeroVector)`
- L34 _public function_ `FSlateMeshVertex( FVector2f InPos , FColor InColor , FVector2f InUV0 , FVector2f InUV1 , FVector2f InUV2 , FVector2f InUV3 , FVector2f InUV4 , FVector2f InUV5 ) : Position(InPos) , Color(InColor) , UV0(InUV0) , UV1(InUV1) , UV2(InUV2) , UV3(InUV3) , UV4(InUV4) , UV5(InUV5)`
- L56 _public member_ `FVector2f Position;` — `UPROPERTY()`
- L59 _public member_ `FColor Color;` — `UPROPERTY()`
- L62 _public member_ `FVector2f UV0;` — `UPROPERTY()`
- L65 _public member_ `FVector2f UV1;` — `UPROPERTY()`
- L68 _public member_ `FVector2f UV2;` — `UPROPERTY()`
- L71 _public member_ `FVector2f UV3;` — `UPROPERTY()`
- L74 _public member_ `FVector2f UV4;` — `UPROPERTY()`
- L77 _public member_ `FVector2f UV5;` — `UPROPERTY()`

#### class `USlateVectorArtData`  
`class USlateVectorArtData : public UObject`  
_L84-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Turn static mesh data into Slate's simple vector art format.
- L90 _public prototype_ `const TArray<FSlateMeshVertex>& GetVertexData() const;` — Access the slate vertexes.
- L93 _public prototype_ `const TArray<uint32>& GetIndexData() const;` — Access the indexes for the order in which to draw the vertexes.
- L96 _public prototype_ `UMaterialInterface* GetMaterial() const;` — Material to be used with the specified vector art data.
- L99 _public prototype_ `UMaterialInstanceDynamic* ConvertToMaterialInstanceDynamic();` — Convert the material into an MID and get a pointer to the MID so that parameters can be set on it.
- L102 _public prototype_ `void EnsureValidData();` — Convert the static mesh data into slate vector art on demand. Does nothing in a cooked build.
- L104 _public prototype_ `FVector2D GetDesiredSize() const;`
- L106 _public prototype_ `FVector2D GetExtentMin() const;`
- L108 _public prototype_ `FVector2D GetExtentMax() const;`
- L112 _private prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L117 _private prototype_ `void InitFromStaticMesh(const UStaticMesh& InSourceMesh);` — Does the actual work of converting mesh data into slate vector art
- L121 _private member_ `TObjectPtr<UStaticMesh> MeshAsset;` — `UPROPERTY(EditAnywhere, Category="Vector Art")` — The mesh data asset from which the vector art is sourced
- L125 _private member_ `TObjectPtr<UMaterialInterface> SourceMaterial;` — `UPROPERTY(Transient)` — The material which we are using, or the material from with the MIC was constructed.
- L130 _private member_ `TArray<FSlateMeshVertex> VertexData;` — `UPROPERTY()` — @see GetVertexData()
- L134 _private member_ `TArray<uint32> IndexData;` — `UPROPERTY()` — @see GetIndexData()
- L138 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY()` — @see GetMaterial()
- L141 _private member_ `FVector2D ExtentMin;` — `UPROPERTY()`
- L144 _private member_ `FVector2D ExtentMax;` — `UPROPERTY()`

### `Source/Runtime/UMG/Public/Slate/SlateVectorArtInstanceData.h` (Public)


#### struct `FSlateVectorArtInstanceData`  
`struct FSlateVectorArtInstanceData`  
_L11-55_
- L14 _public function_ `const FVector4& GetData() const`
- L15 _public function_ `FVector4& GetData()`
- L17 _public prototype_ `void SetPositionFixedPoint16(FVector2D Position);`
- L18 _public prototype_ `void SetScaleFixedPoint16(float Scale);`
- L20 _public prototype_ `void SetPosition(FVector2D Position);`
- L21 _public prototype_ `void SetScale(float Scale);`
- L22 _public prototype_ `void SetBaseAddress(float Address);`
- L25 _public function_ `template<int32 Component, int32 ByteIndex> void PackFloatIntoByte(float InValue)`
- L31 _public function_ `template<int32 Component, int32 ByteIndex> void PackByteIntoByte(uint8 InValue)`
- L47 _public function_ `template<int32 Component, int32 ByteIndex> void PackByteIntoByte(float InValue)`
- L54 _protected member_ `FVector4 Data;` — LWC_TODO: should this and GetData() use FVector4f?

### `Source/Runtime/UMG/Public/Slate/UMGDragDropOp.h` (Public)


#### class `FUMGDragDropOp`  
`class FUMGDragDropOp : public FGameDragDropOperation, public FGCObject`  
_L19-68_
- inherits: `FGameDragDropOperation,FGCObject`
- desc: This is the drag/drop class used for UMG, all UMG drag drop operations utilize this operation. It supports moving a UObject payload and using a UWidget decorator.
- L22 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FUMGDragDropOp, FGameDragDropOperation) static TSharedRef<FUMGDragDropOp> New(UDragDropOperation* Operation, const int32 PointerIndex, const FVector2D &CursorPosition, const FVector2D &ScreenPositionOfNode, float DPIScale, TSharedPtr<SObjectWidget> SourceUserWidget);`
- L26 _public prototype_ `FUMGDragDropOp();`
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _public prototype_ `virtual FString GetReferencerName() const override;`
- L33 _public prototype_ `virtual bool AffectedByPointerEvent(const FPointerEvent& PointerEvent) override;`
- L34 _public prototype_ `virtual void OnDrop( bool bDropWasHandled, const FPointerEvent& MouseEvent ) override;`
- L35 _public prototype_ `virtual void OnDragged( const class FDragDropEvent& DragDropEvent ) override;`
- L36 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L39 _public function_ `UDragDropOperation* GetOperation() const`
- L42 _protected prototype_ `virtual void Construct() override;`
- L47 _private member_ `TObjectPtr<UDragDropOperation> DragOperation;` — Raw pointer to the drag operation, kept alive by AddReferencedObjects.
- L50 _private member_ `TWeakPtr<SObjectWidget> SourceUserWidget;` — Source User Widget
- L53 _private member_ `TWeakObjectPtr<UGameViewportClient> GameViewport;` — The viewport this drag/drop operation is associated with.
- L56 _private member_ `TSharedPtr<SWidget> DecoratorWidget;` — The widget used during the drag/drop action to show something being dragged.
- L59 _private member_ `FVector2D MouseDownOffset;` — The offset to use when dragging the object so that it says the same distance away from the mouse.
- L62 _private member_ `FVector2D StartingScreenPos;` — The starting screen location where the drag operation started.
- L64 _private member_ `int32 PointerIndex;`
- L67 _private member_ `double StartTime;` — Allows smooth interpolation of the dragged visual over a few frames.

### `Source/Runtime/UMG/Public/Slate/WidgetRenderer.h` (Public)


#### class `FWidgetRenderer`  
`class FWidgetRenderer : public FDeferredCleanupInterface`  
_L28-166_
- inherits: `FDeferredCleanupInterface`
- L31 _public prototype_ `FWidgetRenderer(bool bUseGammaCorrection = false, bool bInClearTarget = true);`
- L32 _public prototype_ `~FWidgetRenderer();`
- L34 _public function_ `bool GetIsPrepassNeeded() const`
- L35 _public function_ `void SetIsPrepassNeeded(bool bInPrepassNeeded)`
- L37 _public function_ `bool GetClearHitTestGrid() const`
- L38 _public function_ `void SetClearHitTestGrid(bool bInClearHitTestGrid)`
- L40 _public function_ `void SetShouldClearTarget(bool bShouldClear)`
- L42 _public function_ `bool GetUseGammaCorrection() const`
- L43 _public prototype_ `void SetUseGammaCorrection(bool bInUseGammaSpace);`
- L45 _public prototype_ `void SetApplyColorDeficiencyCorrection(bool bInApplyColorCorrection);`
- L47 _public prototype_ `ISlate3DRenderer* GetSlateRenderer();`
- L49 _public prototype_ `static UTextureRenderTarget2D* CreateTargetFor(FVector2D DrawSize, TextureFilter InFilter, bool bUseGammaCorrection);`
- L51 _public prototype_ `UTextureRenderTarget2D* DrawWidget(const TSharedRef<SWidget>& Widget, FVector2D DrawSize);`
- L53 _public prototype_ `void DrawWidget( FRenderTarget* RenderTarget, const TSharedRef<SWidget>& Widget, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L60 _public prototype_ `void DrawWidget( UTextureRenderTarget2D* RenderTarget, const TSharedRef<SWidget>& Widget, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L67 _public prototype_ `void DrawWidget( FRenderTarget* RenderTarget, const TSharedRef<SWidget>& Widget, float Scale, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L75 _public prototype_ `void DrawWidget( UTextureRenderTarget2D* RenderTarget, const TSharedRef<SWidget>& Widget, float Scale, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L83 _public prototype_ `void DrawWindow( FRenderTarget* RenderTarget, FHittestGrid& HitTestGrid, TSharedRef<SWindow> Window, float Scale, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L92 _public prototype_ `void DrawWindow( UTextureRenderTarget2D* RenderTarget, FHittestGrid& HitTestGrid, TSharedRef<SWindow> Window, float Scale, FVector2D DrawSize, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L101 _public prototype_ `void DrawWindow( FRenderTarget* RenderTarget, FHittestGrid& HitTestGrid, TSharedRef<SWindow> Window, FGeometry WindowGeometry, FSlateRect WindowClipRect, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L110 _public prototype_ `void DrawWindow( UTextureRenderTarget2D* RenderTarget, FHittestGrid& HitTestGrid, TSharedRef<SWindow> Window, FGeometry WindowGeometry, FSlateRect WindowClipRect, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L119 _public prototype_ `void DrawWindow( const FPaintArgs& PaintArgs, FRenderTarget* RenderTarget, TSharedRef<SWindow> Window, FGeometry WindowGeometry, FSlateRect WindowClipRect, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L128 _public prototype_ `void DrawWindow( const FPaintArgs& PaintArgs, UTextureRenderTarget2D* RenderTarget, TSharedRef<SWindow> Window, FGeometry WindowGeometry, FSlateRect WindowClipRect, float DeltaTime, bool bDeferRenderTargetUpdate = false);`
- L137 _public prototype_ `bool DrawInvalidationRoot( TSharedRef<SVirtualWindow>& VirtualWindow, UTextureRenderTarget2D* RenderTarget, FSlateInvalidationRoot& Root, const FSlateInvalidationContext& Context, bool bDeferRenderTargetUpdate = false);`
- L144 _public prototype_ `bool DrawInvalidationRoot( TSharedRef<SVirtualWindow>& VirtualWindow, UTextureRenderTarget2D* RenderTarget, FPaintArgs PaintArgs, float DrawScale, FVector2D DrawSize, bool bDeferRenderTargetUpdate = false);`
- L152 _public member_ `TArray< TSharedPtr<FSlateWindowElementList::FDeferredPaint> > DeferredPaints;`
- L155 _private member_ `TSharedPtr<ISlate3DRenderer, ESPMode::ThreadSafe> Renderer;` — The slate 3D renderer used to render the user slate widget
- L157 _private member_ `bool bPrepassNeeded;` — Prepass Needed when drawing the widget?
- L159 _private member_ `bool bClearHitTestGrid;` — Clearing hit test grid needed?
- L161 _private member_ `bool bUseGammaSpace;` — Is gamma space needed?
- L163 _private member_ `bool bClearTarget;` — Should we clear the render target before rendering.
- L165 _public member_ `FVector2D ViewOffset;`

### `Source/Runtime/UMG/Public/Slate/WidgetTransform.h` (Public)


#### struct `FWidgetTransform`  
`struct FWidgetTransform`  
_L15-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes the standard transformation of a widget
- L23 _public member_ `FVector2D Translation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transform, meta=( Delta = "1" ))` — The amount to translate the widget in slate units
- L27 _public member_ `FVector2D Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transform, meta=( UIMin = "-5", UIMax = "5", Delta = "0.05" ))` — The scale to apply to the widget
- L31 _public member_ `FVector2D Shear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transform, meta=( UIMin = "-89", ClampMin = "-89", UIMax = "89", ClampMax = "89", Delta = "1" ))` — The amount to shear the widget in slate units
- L35 _public member_ `float Angle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transform, meta=( UIMin = "-180", UIMax = "180", Delta = "1" ))` — The angle in degrees to rotate
- L39 _public function_ `FWidgetTransform() : Translation(FVector2D::ZeroVector) , Scale(FVector2D::UnitVector) , Shear(FVector2D::ZeroVector) , Angle(0)`
- L47 _public function_ `FWidgetTransform(const FVector2D& InTranslation, const FVector2D& InScale, const FVector2D& InShear, float InAngle) : Translation(InTranslation) , Scale(InScale) , Shear(InShear) , Angle(InAngle)`
- L55 _public function_ `bool IsIdentity() const`
- L62 _public function_ `inline bool operator==( const FWidgetTransform &Other ) const`
- L67 _public function_ `inline bool operator!=( const FWidgetTransform& Other ) const`
- L72 _public function_ `inline FSlateRenderTransform ToSlateRenderTransform() const`

### `Source/Runtime/UMG/Public/UMG.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/UMG/Public/UMGStyle.h` (Public)


#### class `FUMGStyle`  
`class FUMGStyle`  
_L9-32_
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the UMG Style
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L31 _private member_ `static TSharedPtr< class FSlateStyleSet > UMGStyleInstance;`
