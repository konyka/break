# Plugins / MediaPlate

- module root: `Plugins/Media/MediaPlate/Source/MediaPlate`
- headers: 6; symbols: 279
- symbol kinds: class=5, delegate=3, enum=4, enumerator=23, function=15, macro=3, member=79, namespace=2, prototype=142, struct=3
- PrivateDependencyModuleNames: AudioMixer, CompositeCore, CoreUObject, Engine, MediaAssets, MediaUtils, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Media/MediaPlate/Source/MediaPlate/Private/MediaPlateOpenLatentAction.h` (Private)


#### class `FMediaPlateOpenLatentAction`  
`class FMediaPlateOpenLatentAction : public FPendingLatentAction`  
_L18-106_
- inherits: `FPendingLatentAction`
- desc: Pending Latent action to open a media plate component. The difference with UMediaPlayer::OpenSourceLatent is that is also supports waiting on the media texture to render a sample and therefore be truly ready to be displayed. This can be used to hook in other animation systems to manage dynamic loading of media plates.
- L21 _public prototype_ `FMediaPlateOpenLatentAction(const FLatentActionInfo& InLatentInfo, UMediaPlateComponent* InMediaPlateComponent, float InWaitTimeout, bool bInWaitForTexture, bool& InOutSuccess);`
- L26 _public prototype_ `virtual void UpdateOperation(FLatentResponse& InResponse) override;`
- L30 _public prototype_ `virtual FString GetDescription() const override;` — Returns a human readable description of the latent operation's current state.
- L35 _private prototype_ `FString GetStatusString() const;` — Returns a human readable description of the latent operation's current state.
- L45 _private prototype_ `OperationUpdateResult UpdateOperationPlayerReady(UMediaPlayer* InMediaPlayer, FLatentResponse& InResponse);` — Update Operation when the player is ready.
- L48 _private prototype_ `OperationUpdateResult UpdateOperationConditionalWaitForTexture(FLatentResponse& InResponse) const;` — Update Operation when the player is ready and done seeking (if waiting for texture).
- L51 _private prototype_ `void OnMediaEvent(EMediaEvent InEvent);` — Handler for UMediaPlayer::OnMediaEvent.
- L54 _private prototype_ `void FailedOperation(FLatentResponse& InResponse) const;` — Ends the operation with failure state.
- L57 _private prototype_ `void CompleteOperation(FLatentResponse& InResponse) const;` — Completes the operation with success.
- L60 _private member_ `FName ExecutionFunction;` — Latent Action Info - The function to execute.
- L63 _private member_ `int32 OutputLink;` — Latent Action Info - The resume point within the function to execute.
- L66 _private member_ `FWeakObjectPtr CallbackTarget;` — Latent Action Info - Object to execute the function on.
- L69 _private member_ `TWeakObjectPtr<UMediaPlateComponent> MediaPlateComponentWeak;` — Media Plate Component the action is done on.
- L72 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayerWeak;` — Media Player the action is done on.
- L75 _private member_ `bool bWaitForTexture = false;` — Input parameter - If true the action will not be completed until the media texture has rendered a sample.
- L78 _private member_ `bool& OutSuccess;` — Output parameter - Indicate if the operation completed successfully.
- L81 _private member_ `float TimeRemaining = 10.0f;` — Keeps track of the remaining time, in seconds, before the operation times out.
- L84 _private member_ `bool bSawError = false;` — This is set to true if one of the callbacks indicate an error.
- L87 _private member_ `bool bSawMediaOpened = false;` — Set to true if EMediaEvent::MediaOpened is received from the media player.
- L90 _private member_ `bool bSawMediaClosed = false;` — Set to true if EMediaEvent::MediaClosed is received from the media player.
- L93 _private member_ `bool bSawMediaOpenFailed = false;` — Set to true if EMediaEvent::MediaOpenFailed is received from the media player.
- L96 _private member_ `bool bSawSeekCompleted = false;` — Set to true if EMediaEvent::SeekCompleted is received from the media player.
- L99 _private member_ `bool bSawIsReady = false;` — Set to true if the media player has become ready. This is used to detect the state transition.
- L102 _private member_ `bool bSeekForTextureRequested = false;` — Set to true once the seek request has been issued.
- L105 _private member_ `FString URL;` — Cache the media source's URL for display in log messages.

#### enum `FMediaPlateOpenLatentAction::OperationUpdateResult`  
`enum class OperationUpdateResult`  
_L38-42_
- desc: Indicates if the operation is completed or needs to continue.
- L40 _public enumerator_ `Completed`
- L41 _public enumerator_ `Continue`

### `Plugins/Media/MediaPlate/Source/MediaPlate/Public/MediaPlate.h` (Public)


#### class `AMediaPlate`  
`class AMediaPlate : public AActor`  
_L20-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: MediaPlate is an actor that can play and show media in the world.
- L26 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void PostActorCreated();`
- L31 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L32 _public prototype_ `virtual void BeginDestroy() override;`
- L36 _public member_ `TObjectPtr<UMediaPlateComponent> MediaPlateComponent;` — `UPROPERTY(Category = MediaPlate, VisibleAnywhere, BlueprintReadOnly)`
- L40 _public member_ `TObjectPtr<UStaticMeshComponent> StaticMeshComponent;` — `UPROPERTY(Category = MediaPlate, VisibleAnywhere, BlueprintReadOnly)` — Holds the mesh.
- L44 _public prototype_ `void SetHoldoutCompositeEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintSetter)` — Set the holdout composite state.
- L48 _public prototype_ `bool IsHoldoutCompositeEnabled() const;` — `UFUNCTION(BlueprintGetter)` — Get the holdout composite state.
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L56 _public prototype_ `void OnStaticMeshChange();` — Callback upon static mesh component change (see UMediaPlateAssetUserData).
- L61 _public prototype_ `void UseDefaultMaterial();` — Call this to change the static mesh to use the default media plate material and reset the overlay material.
- L66 _public prototype_ `void ApplyCurrentMaterial();` — Call this after changing the current material to set it up for media plate.
- L71 _public prototype_ `void ApplyMaterial(UMaterialInterface* InMaterial);` — Setup the material for media plate use. Automatically called by ApplyCurrentMaterial.
- L76 _public prototype_ `void ApplyOverlayMaterial(UMaterialInterface* InOverlayMaterial);` — Setup the overlay material for media plate use. Automatically called by ApplyCurrentMaterial.
- L81 _public prototype_ `void SetMIDParameters(UMaterialInstanceDynamic* InMaterial);` — Sets up parameters (like the texture) that we use in the material.
- L84 _public function_ `UMaterialInterface* GetLastMaterial() const` — Get the last material assigned to the static mesh, at index 0.
- L88 _public prototype_ `UMaterialInterface* GetCurrentMaterial() const;` — Get the current static mesh material, at index 0.
- L91 _public prototype_ `UMaterialInterface* GetCurrentOverlayMaterial() const;` — Get the current static mesh overlay material, nullptr otherwise.
- L96 _private member_ `bool bEnableHoldoutComposite = false;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsHoldoutCompositeEnabled, BlueprintSetter = SetHoldoutCompositeEnabled, Category = "Materials", meta = (AllowPrivateAccess = true))` — If true, the mesh is rendered separately and composited after post-processing (see HoldoutComposite plugin). Using mip generation with this setting is also recommended if the cost is acceptable, given that the composite bypasses temporal anti-aliasing.
- L99 _private prototype_ `void ConditionallyEnableHoldoutComposite();` — Only enable registration with holdout composite subsytem if users have enabled holdout composite on the media plate.
- L102 _private member_ `static FLazyName MediaPlateComponentName;` — Name for our media plate component.
- L104 _private member_ `static FLazyName MediaTextureName;` — Name for the media texture parameter in the material.
- L107 _private member_ `UMaterialInterface* LastMaterial = nullptr;`
- L108 _private member_ `UMaterialInterface* LastOverlayMaterial = nullptr;`
- L113 _private prototype_ `void OnPreSaveWorld(UWorld* InWorld, FObjectPreSaveContext ObjectSaveContext);` — Called before a level saves
- L118 _private prototype_ `void OnPostSaveWorld(UWorld* InWorld, FObjectPostSaveContext ObjectSaveContext);` — Called after a level has saved.
- L123 _private prototype_ `void AddAssetUserData();` — Adds our asset user data to the static mesh component.
- L128 _private prototype_ `void RemoveAssetUserData();` — Removes our asset user data from the static mesh component.
- L133 _private prototype_ `UMaterialInterface* CreateMaterialInstanceConstant(UMaterialInterface* InMaterial);` — Convenience function to apply create a material instance constant for media plate use.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIAPLATE_API`

### `Plugins/Media/MediaPlate/Source/MediaPlate/Public/MediaPlateAssetUserData.h` (Public)


#### class `UMediaPlateAssetUserData`  
`class UMediaPlateAssetUserData : public UAssetUserData`  
_L14-25_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- desc: AssetUserData for media plate.
- L20 _public member_ `FOnPostEditChangeOwner OnPostEditChangeOwner;` — Bind to this to get a callback when something is changed on the associated component.
- L23 _public prototype_ `virtual void PostEditChangeOwner(const FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE(FOnPostEditChangeOwner);`
- L8 _prototype_ `DECLARE_DELEGATE(FOnPostEditChangeOwner);`

### `Plugins/Media/MediaPlate/Source/MediaPlate/Public/MediaPlateComponent.h` (Public)


#### enum `EMediaPlateEventState`  
`enum class EMediaPlateEventState : uint8`  
_L30-46_
- reflection: `UENUM()`
- L32 _public enumerator_ `Play`
- L33 _public enumerator_ `Open`
- L34 _public enumerator_ `Close`
- L35 _public enumerator_ `Pause`
- L36 _public enumerator_ `Reverse`
- L37 _public enumerator_ `Forward`
- L38 _public enumerator_ `Rewind`
- L39 _public enumerator_ `Next`
- L40 _public enumerator_ `Previous`
- L41 _public enumerator_ `PlayReverse`
- L42 _public enumerator_ `JumpToEnd`
- L43 _public enumerator_ `StepForward`
- L44 _public enumerator_ `StepBackward`
- L45 _public enumerator_ `MAX`

#### struct `FMediaTextureResourceSettings`  
`struct FMediaTextureResourceSettings`  
_L53-74_
- reflection: `USTRUCT()`
- desc: This struct is used to expose Media Texture settings via Media Plate Component and is a mirror of some of the settings.
- L59 _public member_ `bool bEnableGenMips = false;` — `UPROPERTY(EditAnywhere, Category = "MediaTexture", meta = (DisplayName = "Enable RealTime Mips"))` — Enable mips generation
- L64 _public member_ `uint8 CurrentNumMips_DEPRECATED = 1;` — `UE_DEPRECATED(5.6, "Only 'Enable RealTime Mips' is needed now. When true, the full mip chain will be generated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Only 'Enable RealTime Mips' is needed now. When true, the full mip chain will be generated."))`
- L68 _public prototype_ `FMediaTextureResourceSettings() = default;`
- L69 _public prototype_ `FMediaTextureResourceSettings(const FMediaTextureResourceSettings& InOther) = default;`
- L70 _public prototype_ `FMediaTextureResourceSettings(FMediaTextureResourceSettings&& InOther) = default;`
- L71 _public prototype_ `FMediaTextureResourceSettings& operator=(const FMediaTextureResourceSettings&) = default;`
- L72 _public prototype_ `FMediaTextureResourceSettings& operator=(FMediaTextureResourceSettings&&) = default;`

#### class `UMediaPlateComponent`  
`class UMediaPlateComponent : public UActorComponent, public IMediaPlayerProxyInterface`  
_L81-729_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent,IMediaPlayerProxyInterface`
- desc: This is a component for AMediaPlate that can play and show media in the world.
- L89 _public prototype_ `virtual void PostLoad() override;`
- L91 _public prototype_ `virtual void OnRegister() override;`
- L92 _public prototype_ `virtual void BeginPlay() override;`
- L93 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;`
- L94 _public prototype_ `virtual void BeginDestroy() override;`
- L95 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L96 _public prototype_ `virtual void OnUnregister() override;`
- L97 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L99 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L100 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L101 _public prototype_ `virtual void PostEditUndo() override;`
- L108 _public prototype_ `UMediaPlayer* GetMediaPlayer();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this get our media player.
- L114 _public prototype_ `UMediaTexture* GetMediaTexture(int32 Index = 0);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this get our media texture.
- L123 _public prototype_ `bool IsEventStateChangeAllowed(EMediaPlateEventState InRequestEventState) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Indicates if switching to the given event state (open, play, etc) is currently allowed by the backend. @param InRequestEventState Requested event state to switch to (Open, Play, etc) @return true if the state switch is allowed, false otherwise.
- L129 _public prototype_ `void Open();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to open the media.
- L139 _public prototype_ `void OpenLatent(const UObject* InWorldContextObject, struct FLatentActionInfo InLatentInfo, float InTimeout, bool bInWaitForTexture, bool& bOutSuccess);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent", meta = (Latent, LatentInfo="InLatentInfo", WorldContext="InWorldContextObject", InTimeout="10.0f", bInWaitForTexture="true"))` — Open the media using a latent action. @param InTimeout Wait timeout in seconds @param bInWaitForTexture Wait for the media texture to have rendered a sample. @param bOutSuccess The media was opened successfully.
- L147 _public prototype_ `bool Next();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Play the next item in the playlist. returns	True if it played something.
- L154 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to start playing at a rate of 1.0 (forward at normal speed) Open must be called before this.
- L161 _public prototype_ `void PlayReverse();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to start playing at a rate of -1.0 (reverse at normal speed) Open must be called before this.
- L168 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to pause playback. Play can be called to resume playback.
- L176 _public prototype_ `bool Previous();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Play the previous item in the playlist. returns	True if it played something.
- L186 _public prototype_ `bool Rewind();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Rewinds the media to the beginning. This is the same as seeking to zero time. @return				True if rewinding, false otherwise.
- L195 _public prototype_ `bool Seek(const FTimespan& Time);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to seek to the specified playback time. @param Time			Time to seek to. @return				True on success, false otherwise.
- L201 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to close the media.
- L207 _public function_ `bool IsMediaPlatePlaying() const` — `UFUNCTION(BlueprintGetter)` — Call this to see if the media plate is playing.
- L213 _public prototype_ `bool GetLoop();` — `UFUNCTION(BlueprintGetter)` — Call this to see if we want to loop.
- L219 _public prototype_ `void SetLoop(bool bInLoop);` — `UFUNCTION(BlueprintSetter)` — Call this enable/disable looping.
- L225 _public prototype_ `UMediaPlaylist* GetMediaPlaylist() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Get the currently active Media Playlist
- L231 _public prototype_ `UMediaSource* GetSelectedMediaSource() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Get the currently active Media Source.
- L238 _public prototype_ `void SelectExternalMedia(const FString& InFilePath);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — @brief Select the external media file (non-UE asset) to be opened. @param InFilePath non-UFS path (absolute or relative to executable) to the media file.
- L245 _public prototype_ `void SelectMediaSourceAsset(const UMediaSource* InMediaSource);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — @brief Select the media source asset to be opened. @param InMediaSource media source asset to open.
- L252 _public prototype_ `void SelectMediaPlaylistAsset(const UMediaPlaylist* InMediaPlaylist);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — @brief Select the media playlist asset to be opened. @param InMediaPlaylist media playlist asset to open.
- L257 _public prototype_ `void SetMediaPlateResource(const FMediaPlateResource& InMediaPlayerResource);` — Update Media Player Resource. This will also refresh Playlist accordingly.
- L261 _public member_ `bool bPlayOnOpen = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")` — If set then play when opening the media.
- L265 _public member_ `bool bAutoPlay = true;` — `UPROPERTY(EditAnywhere, Category = "Control")` — If set then start playing when this object is active.
- L269 _public member_ `bool bEnableAudio = false;` — `UPROPERTY(EditAnywhere, Category = "Control")` — If set then enable audio.
- L273 _public member_ `float StartTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0.0"))` — What time to start playing from (in seconds).
- L277 _public member_ `TObjectPtr<UMediaSoundComponent> SoundComponent;` — `UPROPERTY(EditAnywhere, Category = "Advanced", meta = (DisplayName = "Audio Component"))` — Holds the component to play sound.
- L281 _public member_ `TObjectPtr<UStaticMeshComponent> StaticMeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Advanced")` — Holds the component for the mesh.
- L285 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> Letterboxes;` — `UPROPERTY(EditAnywhere, Category = "Advanced|Other")` — Holds the component for the mesh.
- L290 _public member_ `TObjectPtr<UMediaPlaylist> MediaPlaylist_DEPRECATED;` — `UE_DEPRECATED(5.5, "Use MediaPlateResource instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use MediaPlateResource instead"))`
- L295 _public member_ `FMediaPlateResource MediaPlateResource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPlate", meta=(AllowPrivateAccess="true"), Setter=SetMediaPlateResource)` — Which media source is used to populate the media playlist
- L299 _public member_ `int32 PlaylistIndex = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "MediaPlate")` — The current index of the source in the play list being played.
- L303 _public member_ `FMediaSourceCacheSettings CacheSettings;` — `UPROPERTY(EditAnywhere, Category = "Cache", meta = (DisplayName = "Cache", ShowOnlyInnerProperties))` — Override the default cache settings.
- L306 _public prototype_ `void SetEnableAudio(bool bInEnableAudio);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")`
- L310 _public prototype_ `void SetMeshRange(FVector2D InMeshRange);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Set the arc size in degrees used for visible mips and tiles calculations, specific to the sphere.
- L314 _public function_ `FVector2D GetMeshRange() const` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Return the arc size in degrees used for visible mips and tiles calculations, specific to the sphere.
- L318 _public prototype_ `void SetPlayOnlyWhenVisible(bool bInPlayOnlyWhenVisible);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to set bPlayOnlyWhenVisible.
- L323 _public prototype_ `float GetAspectRatio();` — Call this to get the aspect ratio of the mesh.
- L328 _public prototype_ `void SetAspectRatio(float AspectRatio);` — Call this to set the aspect ratio of the mesh.
- L334 _public function_ `bool GetIsAspectRatioAuto() const` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Gets whether automatic aspect ratio is enabled.
- L340 _public prototype_ `void SetIsAspectRatioAuto(bool bInIsAspectRatioAuto);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Sets whether automatic aspect ratio is enabled.
- L346 _public function_ `float GetLetterboxAspectRatio()` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to get the aspect ratio of the screen.
- L352 _public prototype_ `void SetLetterboxAspectRatio(float AspectRatio);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlateComponent")` — Call this to set the aspect ratio of the screen.
- L357 _public function_ `bool GetWantsToPlayWhenVisible() const` — Call this to see if this plate wants to play when it becomes visible.
- L362 _public prototype_ `void SetNumberOfTextures(int32 NumTextures);` — Called from AMediaPlate to set how many media textures the material needs.
- L368 _public function_ `EMediaTextureVisibleMipsTiles GetVisibleMipsTilesCalculations() const` — Call this to get the mip tile calculations mesh mode.
- L372 _public prototype_ `void SetVisibleMipsTilesCalculations(EMediaTextureVisibleMipsTiles InVisibleMipsTilesCalculations);` — Call this to set the mip tile calculations mesh mode. (Note: restarts playback to apply changes.)
- L378 _public prototype_ `void SwitchStates(EMediaPlateEventState State);` — Called whenever a button was pressed locally or on a remote endpoint.
- L383 _public prototype_ `void TickOutput();` — Called from the media clock.
- L386 _public prototype_ `virtual float GetProxyRate() const override;`
- L387 _public prototype_ `virtual bool SetProxyRate(float Rate) override;`
- L388 _public prototype_ `virtual bool IsExternalControlAllowed() override;`
- L389 _public prototype_ `virtual const FMediaSourceCacheSettings& GetCacheSettings() const override;`
- L390 _public prototype_ `virtual UMediaSource* ProxyGetMediaSourceFromIndex(int32 Index) const override;`
- L391 _public prototype_ `virtual UMediaTexture* ProxyGetMediaTexture(int32 LayerIndex, int32 TextureIndex) override;`
- L392 _public prototype_ `virtual void ProxyReleaseMediaTexture(int32 LayerIndex, int32 TextureIndex) override;`
- L393 _public prototype_ `virtual bool ProxySetAspectRatio(UMediaPlayer* InMediaPlayer) override;`
- L394 _public prototype_ `virtual void ProxySetTextureBlend(int32 LayerIndex, int32 TextureIndex, float Blend) override;`
- L400 _public prototype_ `static float GetForwardRate(UMediaPlayer* MediaPlayer);` — Get the rate to use when we press the forward button.
- L405 _public prototype_ `static float GetReverseRate(UMediaPlayer* MediaPlayer);` — Get the rate to use when we press the reverse button.
- L411 _private prototype_ `void RegisterWithMediaTextureTracker();` — Adds our media texture to the media texture tracker.
- L415 _private prototype_ `void UnregisterWithMediaTextureTracker();` — Removes our texture from the media texture tracker.
- L420 _private prototype_ `void PlayOnlyWhenVisibleChanged();` — Should be called when bPlayOnlyWhenVisible changes.
- L422 _private prototype_ `bool RestartPlayer();`
- L430 _private member_ `bool bIsMediaPlatePlaying = false;` — `UPROPERTY(Blueprintgetter = IsMediaPlatePlaying, Category = "MediaPlate", meta = (AllowPrivateAccess = true))` — If true, then we want the media plate to play. Note that this could be true, but the player is not actually playing because bPlayOnlyWhenVisible = true and the plate is not visible.
- L433 _private member_ `float CurrentRate = 0.0f;` — Desired rate of play that we want.
- L443 _private member_ `EPlaybackState IntendedPlaybackState = EPlaybackState::Unset;` — State transitions.
- L444 _private member_ `EPlaybackState PendingPlaybackState = EPlaybackState::Unset;`
- L445 _private member_ `EPlaybackState ActualPlaybackState = EPlaybackState::Unset;`
- L450 _private member_ `bool bPlayOnlyWhenVisible = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = true))` — If true then only allow playback when the media plate is visible.
- L454 _private member_ `bool bLoop = true;` — `UPROPERTY(EditAnywhere, Blueprintgetter = GetLoop, BlueprintSetter = SetLoop, Category = "Control", meta = (AllowPrivateAccess = true))` — If set then loop when we reach the end.
- L458 _private member_ `EMediaTextureVisibleMipsTiles VisibleMipsTilesCalculations;` — `UPROPERTY(EditAnywhere, Category = "EXR Tiles & Mips", meta = (DisplayName = "Visible Tiles & Mips Logic", AllowPrivateAccess = true))` — Visible mips and tiles calculation mode for the supported mesh types in MediaPlate. (Player restart on change.)
- L462 _private member_ `float MipMapBias = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "EXR Tiles & Mips", meta = (DisplayName = "Mips Bias", AllowPrivateAccess = true, UIMin = "-16.0", UIMax = "15.99"))` — Media texture mip map bias shared between the (image sequence) loader and the media texture sampler.
- L466 _private member_ `bool bIsAspectRatioAuto = true;` — `UPROPERTY(Blueprintgetter = GetIsAspectRatioAuto, BlueprintSetter = SetIsAspectRatioAuto, Category = "MediaPlate", meta = (AllowPrivateAccess = true))` — If true then set the aspect ratio automatically based on the media.
- L470 _private member_ `bool bEnableMipMapUpscaling = false;` — `UPROPERTY(EditAnywhere, Category = "EXR Tiles & Mips", meta = (DisplayName = "Enable Mip Upscaling", AllowPrivateAccess = true))` — If true then enable the use of MipLevelToUpscale as defined below.
- L474 _private member_ `int32 MipLevelToUpscale = 16;` — `UPROPERTY(EditAnywhere, Category = "EXR Tiles & Mips", meta = (DisplayName = "Upscale Mip Level", EditCondition = "bEnableMipMapUpscaling", EditConditionHides, AllowPrivateAccess = true, UIMin = "0", UIMax = "16"))` — With exr playback, upscale into lower quality mips from this specified level. All levels including and above the specified value will be fully read.
- L478 _private member_ `bool bAdaptivePoleMipUpscaling = true;` — `UPROPERTY(EditAnywhere, Category = "EXR Tiles & Mips", meta = (DisplayName = "Adaptive Pole Mip Upscale", EditCondition = "VisibleMipsTilesCalculations == EMediaTextureVisibleMipsTiles::Sphere", EditConditionHides, AllowPrivateAccess = true))` — If true then Media Plate will attempt to load and upscale lower quality mips and display those at the poles (Sphere object only).
- L483 _private member_ `float LetterboxAspectRatio = 0.0f;` — `UPROPERTY()` — If > 0, then this is the aspect ratio of our screen and letterboxes will be added if the media is smaller than the screen.
- L486 _private member_ `const int32 MatNumTexPerLayer = 2;` — Number of textures we have per layer in the material.
- L489 _private member_ `FVector2D MeshRange = FVector2D(360.0f, 180.0f);` — `UPROPERTY()`
- L492 _private member_ `static FLazyName MediaComponentName;` — Name for our media component.
- L494 _private member_ `static FLazyName MediaPlaylistName;` — Name for our playlist.
- L499 _private member_ `TObjectPtr<UMediaTexture> MediaTexture_DEPRECATED;` — `UPROPERTY(Instanced)` — Superseded by MediaTextures.
- L504 _private member_ `TArray<TObjectPtr<UMediaTexture>> MediaTextures;` — `UPROPERTY(Instanced)` — Holds the media textures.
- L508 _private member_ `FMediaTextureResourceSettings MediaTextureSettings;` — `UPROPERTY(EditAnywhere, Category = "MediaTexture", meta = (ShowOnlyInnerProperties))` — Exposes Media Texture settings via Media Plate component.
- L512 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(Instanced)` — This component's media player
- L516 _private member_ `TObjectPtr<UMediaSource> ExternalMediaSource;` — `UPROPERTY(Instanced)` — Embedded Media Source loaded from external path specified in MediaPlateResource.
- L523 _private member_ `TObjectPtr<UMediaPlaylist> ActivePlaylist;` — `UPROPERTY(Instanced)` — Currently running Playlist. It can either be a stand alone or embedded asset depending on the media plate resource type.
- L526 _private member_ `TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe> MediaTextureTrackerObject;` — Info representing this object.
- L528 _private member_ `TSharedPtr<FMediaComponentClockSink, ESPMode::ThreadSafe> ClockSink;` — Our media clock sink.
- L530 _private member_ `double TimeWhenPlaybackPaused = -1.0;` — Game time when we paused playback.
- L532 _private member_ `bool bWantsToPlayWhenVisible = false;` — True if our media should be playing when visible.
- L534 _private member_ `bool bResumeWhenOpened = false;` — True if we should resume where we left off when we open the media.
- L538 _private member_ `bool bIsNormalMode = false;` — True if we are in normal mode (as opposed to proxy mode).
- L556 _private member_ `TArray<Layer> TextureLayers;`
- L567 _private member_ `TMap<int32, int32> MediaTextureProxyCount;` — Map of TextureIndex to proxy count. This accurately reflects the set of textures that are actively being used externally through the IMediaPlayerProxyInterface's Get/ReleaseMediaTexture functions. Given that Get/Release calls can be out of order depending on the playback or scrubbing direction, we need to keep track of this state using a ref counting method. Some texture can temporarily be referenced by 2 (or more) sections (even if not actually used internally).
- L570 _private prototype_ `void IncreaseMediaTextureProxyCount(int32 InTextureIndex);` — Called when the given media texture starts being proxied by a media section to increase the proxy count.
- L573 _private prototype_ `void DecreaseMediaTextureProxyCount(int32 InTextureIndex);` — Called when the given media texture stops being proxied by a media section to decrease the proxy count.
- L576 _private prototype_ `bool IsMediaTextureProxied(int32 InTextureIndex) const;` — Determines if the given texture index is being proxied.
- L585 _private prototype_ `bool PlayMediaSource(UMediaSource* InMediaSource, bool bInPlayOnOpen);` — Plays a media source. @param	InMediaSource		Media source to play. @param	bInPlayOnOpen		True to play, false to just open. @return	True if we played anything.
- L591 _private prototype_ `void TryActivateAspectRatioAuto();` — If the player is currently active, then this will set the aspect ratio according to the media.
- L596 _private prototype_ `bool IsAspectRatioAutoAllowed();` — Returns true if auto aspect ratio is enabled and our mesh supports this (e.g. planar).
- L601 _private prototype_ `void StopClockSink();` — Stops the clock sink so we no longer tick.
- L606 _private prototype_ `bool IsVisible();` — Call this to see if this media plate is visible.
- L611 _private prototype_ `void ResumeWhenVisible();` — Call this to resume playback when the media plate is visible.
- L616 _private prototype_ `FTimespan GetResumeTime();` — Returns the time to seek to when resuming playback.
- L621 _private prototype_ `void UpdateTicking();` — Updates if we should tick or not based on current state.
- L626 _private prototype_ `void UpdateLetterboxes();` — Updates letterboxes based on the current state.
- L631 _private prototype_ `void AddLetterboxes();` — Adds ability to have letterboxes.
- L636 _private prototype_ `void RemoveLetterboxes();` — Removes ability to have letterboxes.
- L642 _private prototype_ `void OnMediaOpened(FString DeviceUrl);` — `UFUNCTION()` — Called by the media player when the media opens.
- L648 _private prototype_ `void OnMediaEnd();` — `UFUNCTION()` — Called by the media player when the video ends.
- L654 _private prototype_ `void OnMediaResumed();` — `UFUNCTION()` — Called by the media player when the video resumes.
- L660 _private prototype_ `void OnMediaSuspended();` — `UFUNCTION()` — Called by the media player when the video pauses.
- L665 _private prototype_ `void SetUpTextures(UE::MediaPlateComponent::ESetUpTexturesFlags Flags);` — Sets up the textures we have.
- L670 _private prototype_ `void SetNormalMode(bool bInIsNormalMode);` — Sets either normal mode or proxy mode for something like Sequencer.
- L675 _private prototype_ `bool IsNormalMode() const;` — Returns true if normal mode of false if proxy mode.
- L681 _private prototype_ `bool IsAnyMediaTextureProxied() const;` — @brief Indicates if any media texture is currently being proxied by sequencer. @return true if at least one media texture is in use by sequencer.
- L686 _private prototype_ `void UpdateTextureLayers();` — Sets textures in our material according to the layer assignments.
- L696 _private prototype_ `void InitializeMediaPlateResource();` — If Media Player Resource is not initialized yet (e.g. older assets) this function will initialize it with the proper data. Logic is the following: if media playlist has more than one entry, then the type will be set to Playlist. If playlist has only one entry, then the function will check for that entry Outer. If the Outer is this media plate component, then type will be set to External, otherwise to Asset.
- L702 _private prototype_ `void RefreshMediaPlateResource();` — Can be called after updating MediaPlayerResource, to ensure the Playlist and player state are up to date
- L707 _private prototype_ `void RefreshExternalMediaSource();` — If the current resource type is external path, this will load a new media source from that path.
- L712 _private prototype_ `void RefreshActivePlaylist();` — Refresh the ActivePlaylist from the current configuration of MediaPlateResource.
- L717 _private prototype_ `void RefreshMediaSoundComponent();` — Refresh the media sound component according to the bEnableAudio variable.
- L723 _private prototype_ `UMediaSoundComponent* CreateMediaSoundComponent();` — Create the media sound component with initial setup (but not registered). @return created component on success, nullptr on failure.
- L728 _private prototype_ `void RemoveMediaSoundComponent();` — Removes the audio component.

#### enum `UMediaPlateComponent::EPlaybackState`  
`enum class EPlaybackState`  
_L435-441_
- L437 _public enumerator_ `Unset`
- L438 _public enumerator_ `Paused`
- L439 _public enumerator_ `Playing`
- L440 _public enumerator_ `Resume`

#### struct `UMediaPlateComponent::Layer`  
`struct Layer`  
_L547-555_
- desc: Contains all of our layers. Each layer contains which textures it has. int32 is an index into MediaTextures. -1 signifies no entry.
- L550 _public member_ `int32 MaterialLayerIndex;` — The layer in the material that this layer uses.
- L552 _public member_ `TArray<int32> Textures;` — List of textures in this layer.
- L554 _public function_ `Layer() : MaterialLayerIndex(0)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MEDIAPLATE_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MediaPlateComponent` (scope `UE`)

### `Plugins/Media/MediaPlate/Source/MediaPlate/Public/MediaPlateModule.h` (Public)


#### class `FMediaPlateModule`  
`class FMediaPlateModule : public IModuleInterface`  
_L27-56_
- inherits: `IModuleInterface`
- L33 _public prototype_ `UMediaPlayer* GetMediaPlayer(UObject* Object, UObject*& PlayerProxy);` — Call this to get the media player from a media plate object.
- L36 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L37 _public prototype_ `virtual void ShutdownModule() override;`
- L40 _public member_ `FOnMediaPlateApplyMaterial OnMediaPlateApplyMaterial;` — Add to this if you want a callback when a media plate applies a material to itself.
- L46 _public prototype_ `void OnMediaPlateStateChanged(const TArray<FString>& InActorsPathNames, uint8 InEnumState, bool bRemoteBroadcast);` — Called when Media playback state changed.
- L50 _private member_ `int32 GetPlayerFromObjectID = INDEX_NONE;` — ID for our delegate.
- L54 _private member_ `FDelegateHandle OnMediaPlateStateChangedHandle;` — Handle for the subscribed event

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAPLATE_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlate, Log, All);` — Log category for this module.
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlate, Log, All);` — Log category for this module.
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMediaPlateApplyMaterial, UMaterialInterface*, AMediaPlate*, bool& ) class FMediaPlateModule : public IModuleInterface { public: UMediaPlayer* GetMediaPlayer(UObject* Object, UObject*& PlayerProxy); virtual void StartupModule() override; virtual void ShutdownModule() override; FOnMediaPlateApplyMaterial OnMediaPlateApplyMaterial; #if WITH_EDITOR void OnMediaPlateStateChanged(const TArray<FString>& InActorsPathNames, uint8 InEnumState, bool bRemoteBroadcast); #endif private: int32 GetPlayerFromObjectID = INDEX_NONE; #if WITH_EDITOR FDelegateHandle OnMediaPlateStateChangedHandle; #endif };` — Callback when a media plate applies a material to itself. Set bCanModify to false if you do not want the media plate to modify the material so it can show the media plate's texture.

### `Plugins/Media/MediaPlate/Source/MediaPlate/Public/MediaPlateResource.h` (Public)


#### enum `EMediaPlateResourceType`  
`enum class EMediaPlateResourceType : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Playlist`
- L16 _public enumerator_ `External`
- L17 _public enumerator_ `Asset`

#### struct `FMediaPlateResource`  
`struct FMediaPlateResource`  
_L30-136_
- reflection: `USTRUCT(BlueprintType)`
- desc: Helper struct to wrap source selection functionality, and enabling the usage of media source properties for places like Remote Control. This struct allows to choose between Asset, External File, Playlist options. It's mainly conceived to be used by MediaPlateComponent. See FMediaPlayerResourceCustomization class for its customization.
- L38 _public prototype_ `UMediaPlaylist* GetSourcePlaylist() const;` — Returns the current source playlist, if any
- L43 _public function_ `FStringView GetExternalMediaPath() const` — Returns the current external media path, if any
- L48 _public prototype_ `UMediaSource* GetMediaAsset() const;` — Returns the current asset-based Media Source, if any
- L53 _public function_ `EMediaPlateResourceType GetResourceType() const` — Return current resource type
- L58 _public prototype_ `void SetResourceType(EMediaPlateResourceType InType);` — Set current resource type
- L63 _public prototype_ `void SelectAsset(const UMediaSource* InMediaSource);` — Select asset based media source. Will also update source type to Asset
- L69 _public prototype_ `void LoadExternalMedia(const FString& InFilePath);` — Loads the external source at the specified path, creating a media source with the specified outer. Will also update source type to External
- L74 _public prototype_ `void SelectPlaylist(const UMediaPlaylist* InPlaylist);` — Select the specified playlist. Will also update source type to Playlist
- L77 _public function_ `UMediaSource* GetSelectedMedia() const` — `UE_DEPRECATED(5.6, "Use UMediaPlateComponent::GetSelectedMediaSource() instead.")`
- L80 _public function_ `UMediaPlaylist* GetActivePlaylist() const` — `UE_DEPRECATED(5.6, "Use UMediaPlateComponent::GetMediaPlaylist() instead.")`
- L83 _public function_ `void SelectAsset(const UMediaSource* InMediaSource, UObject* InOuter)` — `UE_DEPRECATED(5.6, "Use UMediaPlateComponent::SelectMediaSourceAsset() instead.")`
- L89 _public function_ `void LoadExternalMedia(const FString& InFilePath, UObject* InOuter)` — `UE_DEPRECATED(5.6, "Use UMediaPlateComponent::SelectExternalMedia() instead.")`
- L96 _public function_ `void Modify() const` — `UE_DEPRECATED(5.6, "Use UMediaPlateComponent::GetMediaPlaylist()->Modify() instead")`
- L100 _public prototype_ `FMediaPlateResource() = default;`
- L101 _public prototype_ `FMediaPlateResource(const FMediaPlateResource& InOther) = default;`
- L102 _public prototype_ `FMediaPlateResource(FMediaPlateResource&& InOther) = default;`
- L103 _public prototype_ `FMediaPlateResource& operator=(const FMediaPlateResource&) = default;`
- L104 _public prototype_ `FMediaPlateResource& operator=(FMediaPlateResource&&) = default;`
- L113 _private prototype_ `void Init(const FMediaPlateResource& InOther);` — Initialize member properties from another MediaPlayerResource. Empty or null property will not be copied over.
- L117 _private member_ `EMediaPlateResourceType Type = EMediaPlateResourceType::Asset;` — `UPROPERTY(EditAnywhere, Category = "MediaPlateResource")` — Media Source Type
- L121 _private member_ `FString ExternalMediaPath;` — `UPROPERTY(EditAnywhere, Category = "MediaPlateResource")` — A path pointing to an external media resource
- L125 _private member_ `TSoftObjectPtr<UMediaSource> MediaAsset;` — `UPROPERTY(EditAnywhere, Category = "MediaPlateResource")` — Media source coming from MediaSource asset
- L129 _private member_ `TSoftObjectPtr<UMediaPlaylist> SourcePlaylist;` — `UPROPERTY(EditAnywhere, Category = "MediaPlateResource")` — User facing Playlist asset
- L134 _private member_ `TObjectPtr<UMediaSource> ExternalMedia_DEPRECATED;` — `UE_DEPRECATED(5.6, "Moved to UMediaPlateComponent::ExternalMediaSource")` — `UPROPERTY(Instanced, meta=(DeprecatedProperty, DeprecationMessage="Moved to UMediaPlateComponent::ExternalMediaSource"))`
