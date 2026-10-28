# Plugins / MediaFrameworkUtilities

- module root: `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities`
- headers: 6; symbols: 111
- symbol kinds: class=6, delegate=2, function=9, member=34, namespace=1, prototype=54, variable=5
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, LevelEditor, Media, MediaAssets, MediaIOCore, MediaPlayerEditor, MediaUtils, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: MediaProfile, OpenCVHelper, OpenCVLensDistortion, TimeManagement

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Private/MediaFrameworkUtilitiesModule.h` (Private)


#### class `IMediaFrameworkUtilitiesModule`  
`class IMediaFrameworkUtilitiesModule : public IModuleInterface`  
_L14-18_
- inherits: `IModuleInterface`
- desc: Implements the MediaFrameworkUtilitiesModule module.
- L17 _public prototype_ `virtual IMediaProfileManager& GetProfileManager() = 0;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaFrameworkUtilities, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaFrameworkUtilities, Log, All);`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Public/MediaBundle.h` (Public)


#### class `UMediaBundle`  
`class UMediaBundle : public UObject`  
_L40-225_
- reflection: `UCLASS(BlueprintType, hidecategories=(Object))`
- inherits: `UObject`
- desc: A bundle of the Media Asset necessary to play a video & audio
- L49 _public function_ `UMaterialInterface* GetMaterial()` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaBundle")` — Get the material interface.
- L55 _public function_ `UMediaPlayer* GetMediaPlayer()` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Get the media player.
- L61 _public function_ `UMediaTexture* GetMediaTexture()` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Get the media texture.
- L67 _public function_ `UTextureRenderTarget2D* GetLensDisplacementTexture()` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaBundle")` — Get the lens displacement Render Target.
- L73 _public function_ `UMediaSource* GetMediaSource()` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Get the media source.
- L79 _public function_ `FOpenCVCameraViewInfo GetUndistortedCameraViewInfo()` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle|LensDistortion")` — Get the undistorted space camera view information.
- L85 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Category="MediaBundle")` — MediaBundle internal MediaSource
- L89 _public member_ `bool bLoopMediaSource;` — `UPROPERTY(EditAnywhere, Category="MediaBundle")` — Controls MediaPlayer looping option
- L93 _public member_ `bool bReopenSourceOnError;` — `UPROPERTY(EditAnywhere, Category="MediaBundle")` — Automatically try to open the MediaSource again if an error is detected
- L98 _public member_ `TSubclassOf<AMediaBundleActorBase> MediaBundleActorClass;` — `UPROPERTY(AdvancedDisplay, EditAnywhere, NoClear, Category="MediaBundle")` — Class to spawn for that asset.
- L104 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(Instanced)` — MediaBundle default MediaPlayer
- L108 _protected member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(Instanced)` — MediaBundle default MediaTexture
- L112 _protected member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(Instanced)` — MediaBundle default Material
- L116 _protected member_ `FOpenCVLensDistortionParameters LensParameters;` — `UPROPERTY(EditAnywhere, Category = "LensParameters")` — Lens parameters of the source
- L120 _protected member_ `FOpenCVCameraViewInfo UndistortedCameraViewInfo;` — `UPROPERTY(VisibleAnywhere, Category = "LensParameters")` — CameraView information for the undistorted space
- L124 _protected member_ `FOpenCVLensDistortionParameters CurrentLensParameters;` — `UPROPERTY(Transient, NonTransactional)` — Current values of lens parameters to support undo/redo correctly
- L128 _protected member_ `TObjectPtr<UTextureRenderTarget2D> LensDisplacementMap;` — `UPROPERTY(Instanced)` — Destination of lens distortion result
- L133 _private member_ `int32 ReferenceCount;` — `UPROPERTY(AdvancedDisplay, DuplicateTransient, Transient, VisibleDefaultsOnly, Category="MediaBundle", meta=(DisplayName="Debug: Reference Count"))` — Internal reference counter of active media player
- L138 _private member_ `TObjectPtr<UMaterial> DefaultMaterial;` — `UPROPERTY(transient)` — Default Material from the plugin
- L142 _private member_ `TObjectPtr<UTexture> DefaultFailedTexture;` — `UPROPERTY(transient)` — Default Texture from the plugin
- L146 _private member_ `TSubclassOf<AMediaBundleActorBase> DefaultActorClass;` — `UPROPERTY(transient)` — Default Actor Class from the plugin
- L153 _public prototype_ `bool OpenMediaSource();` — Play the media source. Only open the source if the reference count is 0. (ie. no one else opened it)
- L158 _public prototype_ `void CloseMediaSource();` — Close the media source. Only close the source if the reference count is 1. (ie. last one to close it)
- L163 _public prototype_ `bool IsPlaying() const;` — The media is playing. Some reference may have requested the media but it is possible that it is not playing because of an internal error.
- L168 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMediaStateChanged, bool );` — Delegate type for media state changed event
- L174 _public function_ `FOnMediaStateChanged& OnMediaStateChanged()` — Media state changed event To use when the you want to be inform if the media is playing or not.
- L179 _private member_ `FOnMediaStateChanged MediaStateChangedDelegate;` — Delegate for the media state changed event
- L183 _private member_ `double PreviousWarningTime;` — Last time the warning has been displayed.
- L192 _private prototype_ `void OnMediaClosed();` — `UFUNCTION()` — Callback function to show the DefaultTexture
- L194 _private prototype_ `void OnMediaOpenOpened(FString DeviceUrl);` — `UFUNCTION()`
- L196 _private prototype_ `void OnMediaOpenFailed(FString DeviceUrl);` — `UFUNCTION()`
- L199 _private prototype_ `void OnMediaProfileChanged(UMediaProfile* OldMediaProfile, UMediaProfile* NewMediaProfile);` — Reopen the media when the media profile changed.
- L204 _private prototype_ `void RefreshLensDisplacementMap();` — Regenerate displacement map associated to lens parameters
- L212 _public prototype_ `TArray<UPackage*> CreateInternalsEditor();` — Create other assets required for a MediaBundle to work. Used for duplication and factory
- L218 _public prototype_ `virtual void PostLoad() override;`
- L219 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L222 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace MediaBundleMaterialParametersName`
- L28 _variable_ `static const FName MediaTextureName("Med` (scope `MediaBundleMaterialParametersName`)
- L29 _variable_ `static const FName FailedTextureName("Fai` (scope `MediaBundleMaterialParametersName`)
- L30 _variable_ `static const FName IsValidMediaName("IsV` (scope `MediaBundleMaterialParametersName`)
- L31 _variable_ `static const FName LensDisplacementMapTextureName("UVD` (scope `MediaBundleMaterialParametersName`)
- L32 _variable_ `static const FName GarbageMatteTextureName("Gar` (scope `MediaBundleMaterialParametersName`)
- L168 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMediaStateChanged, bool );` — Delegate type for media state changed event

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Public/MediaBundleActorBase.h` (Public)


#### class `AMediaBundleActorBase`  
`class AMediaBundleActorBase : public AActor`  
_L21-128_
- reflection: `UCLASS(abstract, Blueprintable)`
- inherits: `AActor`
- desc: A base actor that
- L30 _public function_ `UMediaBundle* GetMediaBundle()` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaBundle")` — Get the Media Bundle.
- L36 _public prototype_ `bool RequestOpenMediaSource();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Play the Media Source.
- L42 _public prototype_ `void RequestCloseMediaSource();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Close the Media Source.
- L47 _public function_ `bool IsPlayRequested() const` — Whether this actor requested the media to play.
- L54 _protected prototype_ `void SetComponent(UPrimitiveComponent* InPrimitive, UMediaSoundComponent* InMediaSound);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaBundle")` — Assign the primitive to render on. Will change the material for the Media material.
- L60 _public member_ `TObjectPtr<UTextureRenderTarget2D> GarbageMatteMask;` — `UPROPERTY(EditAnywhere, Category="Compositing")` — Texture containging 2D garbage matte mask
- L66 _protected member_ `TObjectPtr<UMediaBundle> MediaBundle;` — `UPROPERTY(EditAnywhere, NoClear, Category="MediaBundle")` — Associated MediaBundle
- L70 _protected member_ `bool bAutoPlay;` — `UPROPERTY(EditDefaultsOnly, Category="MediaBundle")` — Wheter to auto start the MediaPlayer
- L74 _protected member_ `bool bPlayWhileEditing;` — `UPROPERTY(EditDefaultsOnly, Category="MediaBundle", meta=(EditCondition="bAutoPlay"))` — Wheter to keep MediaPlayer playing when editing
- L78 _protected member_ `TObjectPtr<UPrimitiveComponent> PrimitiveCmp;` — `UPROPERTY(EditDefaultsOnly, Category="MediaBundle")` — PrimitiveComponent on which to attach our Material
- L82 _protected member_ `TObjectPtr<UMediaSoundComponent> MediaSoundCmp;` — `UPROPERTY(EditDefaultsOnly, NoClear, Category = "MediaBundle")` — MediaSoundComponent associated to play sound of our MediaSource
- L86 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> Material;` — `UPROPERTY(EditDefaultsOnly, Category="MediaBundle")` — Dynamic instance of the associated MediaBundle base Material
- L90 _protected member_ `int32 PrimitiveMaterialIndex;` — `UPROPERTY(AdvancedDisplay, EditAnywhere, Category="MediaBundle")` — Index of the Material on the primitive
- L93 _protected member_ `bool bPlayingMedia;` — Whether we're actually playing the media
- L98 _private member_ `FDelegateHandle MediaStateChangedHandle;` — Handle to handle to show the invalid material
- L101 _private prototype_ `void SetIsValidMaterialParameter(bool bIsValid);` — Based on success or failure of MediaSource opening, will change parameter to update displayed texture
- L105 _public prototype_ `virtual void BeginPlay() override;`
- L106 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L109 _public prototype_ `virtual void CheckForErrors() override;`
- L113 _public prototype_ `virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph);`
- L114 _public prototype_ `virtual void PostActorCreated() override;`
- L115 _public prototype_ `virtual void Destroyed() override;`
- L116 _public prototype_ `virtual void BeginDestroy() override;`
- L120 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L121 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L126 _private prototype_ `void SetSoundComponentMediaPlayer(UMediaPlayer* InMediaPlayer);`
- L127 _private prototype_ `void CreateDynamicMaterial();`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Public/MediaBundleTimeSynchronizationSource.h` (Public)


#### class `UMediaBundleTimeSynchronizationSource`  
`class UMediaBundleTimeSynchronizationSource : public UTimeSynchronizationSource`  
_L16-51_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UTimeSynchronizationSource`
- desc: Synchronization Source using the Media Bundle
- L23 _public member_ `TObjectPtr<UMediaBundle> MediaBundle;` — `UPROPERTY(EditAnywhere, Category=Player)` — Media bundle asset of this input
- L29 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _public prototype_ `virtual FFrameTime GetNewestSampleTime() const override;`
- L35 _public prototype_ `virtual FFrameTime GetOldestSampleTime() const override;`
- L36 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L37 _public prototype_ `virtual bool IsReady() const override;`
- L38 _public prototype_ `virtual bool Open(const FTimeSynchronizationOpenData& InOpenData) override;`
- L39 _public prototype_ `virtual void Start(const FTimeSynchronizationStartData& InStartData) override;`
- L40 _public prototype_ `virtual void Close() override;`
- L41 _public prototype_ `virtual FString GetDisplayName() const override;`
- L43 _public prototype_ `virtual TSharedRef<SWidget> GetVisualWidget() const override;`
- L49 _private member_ `TOptional<FTimeSynchronizationOpenData> OpenData;`
- L50 _private member_ `TOptional<FTimeSynchronizationStartData> StartData;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Public/MediaPlayerTimeSynchronizationSource.h` (Public)


#### class `UMediaPlayerTimeSynchronizationSource`  
`class UMediaPlayerTimeSynchronizationSource : public UTimeSynchronizationSource`  
_L16-55_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UTimeSynchronizationSource`
- desc: Synchronization Source using the Media Player framework
- L23 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(EditAnywhere, Category=Player)` — Media source asset of this input
- L27 _public member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(EditAnywhere, Category = Player)` — Texture linked to the media player
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public prototype_ `virtual FFrameTime GetNewestSampleTime() const override;`
- L39 _public prototype_ `virtual FFrameTime GetOldestSampleTime() const override;`
- L40 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L41 _public prototype_ `virtual bool IsReady() const override;`
- L42 _public prototype_ `virtual bool Open(const FTimeSynchronizationOpenData& InOpenData) override;`
- L43 _public prototype_ `virtual void Start(const FTimeSynchronizationStartData& InStartData) override;`
- L44 _public prototype_ `virtual void Close() override;`
- L45 _public prototype_ `virtual FString GetDisplayName() const override;`
- L47 _public prototype_ `virtual TSharedRef<SWidget> GetVisualWidget() const override;`
- L53 _private member_ `TOptional<FTimeSynchronizationOpenData> OpenData;`
- L54 _private member_ `TOptional<FTimeSynchronizationStartData> StartData;`

### `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilities/Public/Profile/MediaProfileBlueprintLibrary.h` (Public)


#### class `UMediaProfileBlueprintLibrary`  
`class UMediaProfileBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-30_
- reflection: `UCLASS(meta=(ScriptName="MediaProfileLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static UMediaProfile* GetMediaProfile();` — `UFUNCTION(BlueprintPure, Category = "MediaProfile")`
- L23 _public prototype_ `static void SetMediaProfile(UMediaProfile* MediaProfile);` — `UFUNCTION(BlueprintCallable, Category = "MediaProfile")`
- L26 _public prototype_ `static TArray<UProxyMediaSource*> GetAllMediaSourceProxy();` — `UFUNCTION(BlueprintCallable, Category = "MediaProfile")`
- L29 _public prototype_ `static TArray<UProxyMediaOutput*> GetAllMediaOutputProxy();` — `UFUNCTION(BlueprintCallable, Category = "MediaProfile")`
