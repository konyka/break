# Plugins / MediaProfile

- module root: `Plugins/Media/MediaProfile/Source/MediaProfile`
- headers: 9; symbols: 250
- symbol kinds: class=10, delegate=2, function=8, member=67, namespace=1, prototype=159, struct=2, typedef=1
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, LevelEditor, MediaAssets, MediaIOCore, MediaPlayerEditor, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Media/MediaProfile/Source/MediaProfile/Private/MediaProfileModule.h` (Private)


#### class `FMediaProfileModule`  
`class FMediaProfileModule : public IMediaProfileModule`  
_L11-39_
- inherits: `IMediaProfileModule`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public function_ `virtual IMediaProfileManager& GetProfileManager() override`
- L20 _public function_ `virtual bool CanCaptureWithLevelEditorViewportClients() override`
- L23 _private prototype_ `void RegisterSettings();`
- L24 _private prototype_ `void UnregisterSettings();`
- L26 _private prototype_ `void ApplyStartupMediaProfile();`
- L27 _private prototype_ `void RemoveStartupMediaProfile();`
- L30 _private prototype_ `void FixupRedirectedConfigs();` — Fixes up all saved config properties for UMediaProfileSettings and UMediaProfileUserSettings which may still be saved under the old MFU package name
- L34 _private member_ `bool bIsLevelEditorInitialized = false;` — Keeps track of whether the level editor module has been initialized and can be used for media capture
- L36 _private member_ `FMediaProfileManager MediaProfileManager;`
- L37 _private member_ `FDelegateHandle InitHandle;`
- L38 _private member_ `FDelegateHandle OnLevelEditorCreatedHandle;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaProfile, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaProfile, Log, All);`

### `Plugins/Media/MediaProfile/Source/MediaProfile/Private/Profile/MediaProfileManager.h` (Private)


#### class `FMediaProfileManager`  
`class FMediaProfileManager : public IMediaProfileManager, public FGCObject`  
_L12-43_
- inherits: `IMediaProfileManager,FGCObject`
- L15 _public prototype_ `FMediaProfileManager();`
- L16 _public prototype_ `virtual ~FMediaProfileManager();`
- L19 _public prototype_ `virtual UMediaProfile* GetCurrentMediaProfile() const override;`
- L20 _public prototype_ `virtual void SetCurrentMediaProfile(UMediaProfile* InMediaProfile) override;`
- L21 _public prototype_ `TArray<UProxyMediaSource*> GetAllMediaSourceProxy() const override;`
- L22 _public prototype_ `TArray<UProxyMediaOutput*> GetAllMediaOutputProxy() const override;`
- L23 _public prototype_ `virtual FOnMediaProfileChanged& OnMediaProfileChanged() override;`
- L27 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L28 _public function_ `virtual FString GetReferencerName() const override`
- L36 _private prototype_ `void OnMediaProxiesChanged();`
- L39 _private member_ `TArray<TObjectPtr<UProxyMediaSource>> MediaSourceProxies;`
- L40 _private member_ `TArray<TObjectPtr<UProxyMediaOutput>> MediaOutputProxies;`
- L41 _private member_ `TObjectPtr<UMediaProfile> CurrentMediaProfile;`
- L42 _private member_ `FOnMediaProfileChanged MediaProfileChangedDelegate;`

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/IMediaProfileModule.h` (Public)


#### class `IMediaProfileModule`  
`class IMediaProfileModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- desc: Public interface for MediaProfileModule
- L15 _public member_ `static const FName LegacyPackageName;` — Legacy package name (/Script/MediaFrameworkUtilities) for unmigrated media profile assets; add a class path built from this alongside the current class path in asset picker filters so unmigrated entries remain discoverable.
- L18 _public prototype_ `virtual IMediaProfileManager& GetProfileManager() = 0;` — Gets the global media profile manager
- L21 _public prototype_ `virtual bool CanCaptureWithLevelEditorViewportClients() = 0;` — Gets whether the engine has been loaded with the necessary components to allow media captures using a level editor viewport client

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/MediaAssets/ProxyMediaOutput.h` (Public)


#### class `UProxyMediaOutput`  
`class UProxyMediaOutput : public UMediaOutput`  
_L14-98_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- desc: A media output that redirect to another media output.
- L19 _private prototype_ `UProxyMediaOutput();`
- L25 _private member_ `TObjectPtr<UMediaOutput> DynamicProxy;` — `UPROPERTY(Transient, DuplicateTransient)` — Dynamic media output proxy.
- L29 _private member_ `TObjectPtr<UMediaOutput> Proxy;` — `UPROPERTY(EditAnywhere, Category = "Media Proxy")` — Media output proxy.
- L38 _public prototype_ `UMediaOutput* GetMediaOutput() const;` — Get the media output proxy. @return The media output, or nullptr if not set.
- L45 _public prototype_ `UMediaOutput* GetLeafMediaOutput() const;` — Get the last element of the media output chain that is not a proxy media output. @return The media output, or nullptr if not set.
- L53 _public prototype_ `bool IsProxyValid() const;` — `UFUNCTION(BlueprintCallable, Category = "Media Proxy")` — Is the media proxy has a valid proxy. @return true if the proxy is valid.
- L60 _public prototype_ `void SetDynamicMediaOutput(UMediaOutput* InProxy);` — Set the dynamic media output proxy. @param InProxy The proxy to use.
- L69 _public prototype_ `void SetMediaOutput(UMediaOutput* InProxy);` — Set the media output proxy. @param InProxy The proxy to use.
- L75 _public prototype_ `virtual bool Validate(FString& OutFailureReason) const override;`
- L76 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L77 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L78 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L81 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L82 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L87 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L91 _private member_ `mutable bool bLeafMediaOutput;`
- L92 _private member_ `mutable bool bValidateGuard;`
- L93 _private member_ `mutable bool bRequestedSizeGuard;`
- L94 _private member_ `mutable bool bRequestedPixelFormatGuard;`
- L95 _private member_ `mutable bool bConfigurationTextGuard;`
- L96 _private member_ `mutable bool bGetInfoElementsGuard;`
- L97 _private member_ `mutable bool bCreateMediaCaptureImplGuard;`

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/MediaAssets/ProxyMediaSource.h` (Public)


#### class `UProxyMediaSource`  
`class UProxyMediaSource : public UMediaSource`  
_L14-104_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaSource`
- desc: A media source that redirects to another media source.
- L19 _private prototype_ `UProxyMediaSource();`
- L25 _private member_ `TObjectPtr<UMediaSource> DynamicProxy;` — `UPROPERTY(Transient, DuplicateTransient)` — Cached media source proxy.
- L29 _private member_ `TObjectPtr<UMediaSource> Proxy;` — `UPROPERTY(EditAnywhere, Category="Media Proxy")` — Media source proxy.
- L38 _public prototype_ `UMediaSource* GetMediaSource() const;` — Get the media source proxy. @return The media source, or nullptr if not set.
- L45 _public prototype_ `UMediaSource* GetLeafMediaSource() const;` — Get the last element of the media source chain that is not a proxy media source. @return The media source, or nullptr if not set.
- L53 _public prototype_ `bool IsProxyValid() const;` — `UFUNCTION(BlueprintCallable, Category = "Media Proxy")` — Is the media proxy has a valid proxy. @return true if the proxy is valid.
- L60 _public prototype_ `void SetDynamicMediaSource(UMediaSource* InProxy);` — Set the dynamic media source proxy. @param InProxy The proxy to use.
- L68 _public prototype_ `void SetMediaSource(UMediaSource* InProxy);` — Set the media source proxy. @param InProxy The proxy to set.
- L75 _public prototype_ `virtual FString GetUrl() const override;`
- L76 _public prototype_ `virtual bool Validate() const override;`
- L79 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L80 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L87 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L88 _public prototype_ `virtual double GetMediaOption(const FName& Key, double DefaultValue) const override;`
- L89 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L90 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L91 _public prototype_ `virtual FText GetMediaOption(const FName& Key, const FText& DefaultValue) const override;`
- L92 _public prototype_ `virtual TSharedPtr<IMediaOptions::FDataContainer, ESPMode::ThreadSafe> GetMediaOption(const FName& Key, const TSharedPtr<FDataContainer, ESPMode::ThreadSafe>& DefaultValue) const override;`
- L93 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L97 _private member_ `mutable bool bUrlGuard;`
- L98 _private member_ `mutable bool bValidateGuard;`
- L99 _private member_ `mutable bool bConfigurationTextGuard;`
- L100 _private member_ `mutable bool bGetInfoElementsGuard;`
- L101 _private member_ `mutable bool bLeafMediaSource;`
- L102 _private member_ `mutable bool bMediaOptionGuard;`

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/IMediaProfileManager.h` (Public)


#### class `IMediaProfileManager`  
`class IMediaProfileManager`  
_L11-36_
- L14 _public prototype_ `static IMediaProfileManager& Get();`
- L17 _public function_ `virtual ~IMediaProfileManager()` — IMediaProfileManager structors
- L20 _public prototype_ `virtual UMediaProfile* GetCurrentMediaProfile() const = 0;` — Get the current profile used by the manager. Can be null.
- L23 _public prototype_ `virtual void SetCurrentMediaProfile(UMediaProfile* InMediaProfile) = 0;` — Set the current profile used by the manager.
- L26 _public prototype_ `virtual TArray<UProxyMediaSource*> GetAllMediaSourceProxy() const = 0;` — Get all the media source proxy.
- L29 _public prototype_ `virtual TArray<UProxyMediaOutput*> GetAllMediaOutputProxy() const = 0;` — Get all the media output proxy.
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaProfileChanged, UMediaProfile* , UMediaProfile* );` — Delegate type for media profile changed event
- L35 _public prototype_ `virtual FOnMediaProfileChanged& OnMediaProfileChanged() = 0;` — Delegate for media profile changed event

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaProfileChanged, UMediaProfile* , UMediaProfile* );` — Delegate type for media profile changed event

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/MediaProfile.h` (Public)


#### class `UMediaProfile`  
`class UMediaProfile : public UObject`  
_L21-289_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: A media profile that configures the inputs, outputs, timecode provider and custom time step.
- L26 _public prototype_ `UMediaProfile(const FObjectInitializer& ObjectInitializer);`
- L32 _protected member_ `TArray<TObjectPtr<UMediaSource>> MediaSources;` — `UPROPERTY(EditAnywhere, Instanced, Category="Inputs", EditFixedSize, meta=(EditFixedOrder))` — Media sources.
- L36 _protected member_ `TArray<TObjectPtr<UMediaOutput>> MediaOutputs;` — `UPROPERTY(EditAnywhere, Instanced, Category="Outputs", EditFixedSize, meta=(EditFixedOrder))` — Media outputs.
- L40 _protected member_ `bool bOverrideTimecodeProvider;` — `UPROPERTY(EditAnywhere, Category="Timecode Provider", meta=(DisplayName="Override Project Settings"))` — Override the Engine's Timecode provider defined in the project settings.
- L44 _protected member_ `TObjectPtr<UTimecodeProvider> TimecodeProvider;` — `UPROPERTY(EditAnywhere, Instanced, Category="Timecode Provider", meta=(EditCondition="bOverrideTimecodeProvider"))` — Timecode provider.
- L48 _protected member_ `bool bOverrideCustomTimeStep;` — `UPROPERTY(EditAnywhere, Category="Genlock", meta=(DisplayName="Override Project Settings"))` — Override the Engine's Custom time step defined in the project settings.
- L52 _protected member_ `TObjectPtr<UEngineCustomTimeStep> CustomTimeStep;` — `UPROPERTY(EditAnywhere, Instanced, Category="Genlock", meta=(EditCondition="bOverrideCustomTimeStep"))` — Custom time step
- L57 _protected member_ `TArray<FString> MediaSourceLabels;` — `UPROPERTY()` — Stores user defined labels for the profile's media sources, so that users can organize and identify their media sources easier
- L61 _protected member_ `TArray<FString> MediaOutputLabels;` — `UPROPERTY()` — Stores user defined labels for the profile's media outputs, so that users can organize and identify their media outputs easier
- L70 _public member_ `bool bNeedToBeReapplied;` — When the profile is the current profile and modifications made it dirty. Without re-apply the profile does modification won't take effect.
- L80 _public prototype_ `UMediaSource* GetMediaSource(int32 Index) const;` — Get the media source for the selected proxy. @return The media source, or nullptr if not set.
- L87 _public prototype_ `void SetMediaSource(int32 Index, UMediaSource* InMediaSource);` — Sets the media source at the specified index in the profile's list of sources @param Index The index of the source to set @param InMediaSource The new media source to set
- L92 _public prototype_ `int32 NumMediaSources() const;` — Get the number of media source.
- L99 _public prototype_ `int32 FindMediaSourceIndex(UMediaSource* MediaSource) const;` — Gets the index of the specified media source if it was found in the media profile's list of sources @param MediaSource The media source to get the index of @return The index of the source in the profile's sources list, or INDEX_NONE if it was not found
- L107 _public prototype_ `int32 FindMediaSourceIndexByLabel(const FString& InLabel) const;` — Gets the index of a media source whose label matches the specified label if it was found in the media profile's list of sources @param InLabel The label of the media source to find @return The index of the source in the profile's sources list, or INDEX_NONE if it was not found
- L114 _public prototype_ `void AddMediaSource(UMediaSource* MediaSource);` — Adds the specified media source to the profile's list of media sources @param MediaSource The media source to add
- L121 _public prototype_ `bool RemoveMediaSource(int32 Index);` — Removes the specified media source from the profile's list of sources @param Index The index of the media source to remove @return true if the media source was removed
- L129 _public prototype_ `bool MoveMediaSource(int32 CurrentIndex, int32 DestIndex);` — Moves the media source at the specified index to the destination index, shifting other media sources down to accommodate @param CurrentIndex The current index of the media source to move @param DestIndex The index to put the media source at @return true if the move occurred, otherwise false
- L137 _public prototype_ `FString GetLabelForMediaSource(int32 Index);` — Gets the label for a media source @param Index The index of the media source @return The label that has been set for the media source
- L144 _public prototype_ `void SetLabelForMediaSource(int32 Index, const FString& NewLabel);` — Sets the label for a media source @param Index The index of the media source @param NewLabel The label to set for the media source
- L152 _public prototype_ `UMediaOutput* GetMediaOutput(int32 Index) const;` — Get the media output for the selected proxy. @return The media output, or nullptr if not set.
- L159 _public prototype_ `void SetMediaOutput(int32 Index, UMediaOutput* InMediaOutput);` — Sets the media output at the specified index in the profile's list of outputs @param Index The index of the output to set @param InMediaOutput The new media output to set
- L164 _public prototype_ `int32 NumMediaOutputs() const;` — Get the number of media output.
- L171 _public prototype_ `int32 FindMediaOutputIndex(UMediaOutput* MediaOutput) const;` — Gets the index of the specified media output if it was found in the media profile's list of outputs @param MediaOutput The media output to get the index of @return The index of the output in the profile's output list, or INDEX_NONE if it was not found
- L179 _public prototype_ `int32 FindMediaOutputIndexByLabel(const FString& InLabel) const;` — Gets the index of a media output with the specified label if it was found in the media profile's list of outputs @param InLabel The label of the media output to find @return The index of the output in the profile's output list, or INDEX_NONE if it was not found
- L186 _public prototype_ `void AddMediaOutput(UMediaOutput* MediaOutput);` — Adds the specified media output to the profile's list of media outputs @param MediaOutput The media output to add
- L193 _public prototype_ `bool RemoveMediaOutput(int32 Index);` — Removes the specified media output from the profile's list of outputs @param Index The index of the media output to remove @return true if the media output was removed
- L201 _public prototype_ `bool MoveMediaOutput(int32 CurrentIndex, int32 DestIndex);` — Moves the media output at the specified index to the destination index, shifting other media outputs down to accommodate @param CurrentIndex The current index of the media output to move @param DestIndex The index to put the media output at @return true if the move occurred, otherwise false
- L209 _public prototype_ `FString GetLabelForMediaOutput(int32 Index);` — Gets the label for a media output @param Index The index of the media output @return The label that has been set for the media output
- L216 _public prototype_ `void SetLabelForMediaOutput(int32 Index, const FString& NewLabel);` — Sets the label for a media output @param Index The index of the media output @param NewLabel The label to set for the media output
- L224 _public prototype_ `UTimecodeProvider* GetTimecodeProvider() const;` — Get the timecode provider. @return The timecode provider, or nullptr if not set.
- L231 _public prototype_ `UEngineCustomTimeStep* GetCustomTimeStep() const;` — Get the custom time step. @return The custom time step, or nullptr if not set.
- L234 _public prototype_ `void ApplyTimecodeProvider();` — Resets and applies the media profile's timecode to the engine if it is set to override the project settings timecode
- L237 _public prototype_ `void ApplyCustomTimeStep();` — Resets and applies the media profile's custom time step to the engine if it is set to override the project settings timecode
- L245 _public prototype_ `virtual void Apply();` — Apply the media profile. Will change the engine's timecode provider & custom time step and redirect the media profile source/output proxy for the correct media source/output.
- L251 _public prototype_ `virtual void Reset();` — Reset the media profile. Will reset the engine's timecode provider & custom time step and redirect the media profile source/output proxy for no media source/output.
- L256 _public prototype_ `void FixNumSourcesAndOutputs();` — Update the number of sources and outputs to the number to proxies.
- L259 _public prototype_ `UMediaProfilePlaybackManager* GetPlaybackManager() const;` — Gets the playback manager to use for playback of this profile's media sources and outputs
- L263 _private prototype_ `void ResetTimecodeProvider();`
- L264 _private prototype_ `void ResetCustomTimeStep();`
- L265 _private prototype_ `void SendAnalytics() const;`
- L270 _private member_ `bool bTimecodeProvideWasApplied;` — Applied Timecode provider, cached to reset the previous value.
- L272 _private member_ `TObjectPtr<UTimecodeProvider> AppliedTimecodeProvider;` — `UPROPERTY(Transient)`
- L274 _private member_ `TObjectPtr<UTimecodeProvider> PreviousTimecodeProvider;` — `UPROPERTY(Transient)`
- L277 _private member_ `bool bCustomTimeStepWasApplied;` — Applied Custom time step, cached to reset the previous value.
- L279 _private member_ `TObjectPtr<UEngineCustomTimeStep> AppliedCustomTimeStep;` — `UPROPERTY(Transient)`
- L281 _private member_ `TObjectPtr<UEngineCustomTimeStep> PreviousCustomTimeStep;` — `UPROPERTY(Transient)`
- L285 _private member_ `TObjectPtr<UMediaProfilePlaybackManager> PlaybackManager;` — `UPROPERTY(Transient, Instanced)` — Playback manager with maintains any necessary objects to support playback of the profile's media sources and outputs

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/MediaProfilePlaybackManager.h` (Public)


#### class `UMediaProfilePlaybackManager`  
`class UMediaProfilePlaybackManager : public UObject, public FTickableGameObject`  
_L47-483_
- reflection: `UCLASS()`
- inherits: `UObject,FTickableGameObject`
- desc: Manages playback of media items within a media profile
- L52 _private typedef_ `using FRecaptureFunc = TFunction<void(UMediaProfilePlaybackManager*)>;` — Alias for callback used to restart capture of media outputs
- L55 _public prototype_ `UMediaProfilePlaybackManager(const FObjectInitializer& ObjectInitializer);`
- L60 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L61 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L62 _public prototype_ `virtual bool IsTickable() const override;`
- L63 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L64 _public prototype_ `virtual TStatId GetStatId() const override;`
- L65 _public function_ `virtual bool IsTickableInEditor() const override`
- L66 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L74 _public prototype_ `UMediaTexture* GetSourceMediaTextureFromIndex(int32 InMediaSourceIndex) const;` — Gets the media texture that is outputting the specified media source @param InMediaSourceIndex The index of the media source within the media profile @return The media texture for the specified media source, or null if no media source exists at the specified index
- L81 _public prototype_ `UMediaTexture* GetSourceMediaTexture(UMediaSource* InMediaSource) const;` — Gets the media texture that is outputting the specified media source @param InMediaSource The media source within the media profile @return The media texture for the specified media source, or null if the media source is not a valid member of the media profile
- L89 _public prototype_ `bool IsValidSourceMediaTexture(UMediaTexture* InMediaTexture, int32& OutMediaSourceIndex) const;` — Checks the specified media texture to see if it is being used by the media profile to play one of its media sources @param InMediaTexture The media texture to test @param OutMediaSourceIndex The media source index in the media profile that is using the texture, or INDEX_NONE if there is none @return true if the media texture is being used by the active media profile; otherwise false
- L97 _public prototype_ `UMediaTexture* OpenSourceFromIndex(int32 InMediaSourceIndex, void* InConsumer = nullptr);` — Opens and begins playing the specified media source @param InMediaSourceIndex The index of the media source within the media profile @param InConsumer If not null, this consumer will be added to the list of consumers using the open media source @return The media texture that is outputting the media source, or null if no media source exists at the specified index
- L105 _public prototype_ `UMediaTexture* OpenSource(UMediaSource* InMediaSource, void* InConsumer = nullptr);` — Opens and begins playing the specified media source @param InMediaSource The media source within the media profile @param InConsumer If not null, this consumer will be added to the list of consumers using the open media source @return The media texture that is outputting the media source, or null if the media source is not a valid member of the media profile
- L113 _public prototype_ `bool IsSourceOpenFromIndex(int32 InMediaSourceIndex, void* InConsumer = nullptr) const;` — Gets whether a media source is currently open @param InMediaSourceIndex The index of the media source within the media profile @param InConsumer If not null, additionally checks if the specified consumer is using the media source @return true if the media source is open (and being used by InConsumer, if provided); otherwise false
- L121 _public prototype_ `bool IsSourceOpen(UMediaSource* InMediaSource, void* InConsumer = nullptr) const;` — Gets whether a media source is currently open @param InMediaSource The media source within the media profile @param InConsumer If not null, additionally checks if the specified consumer is using the media source @return true if the media source is open (and being used by InConsumer, if provided); otherwise false
- L146 _public prototype_ `void CloseSourceFromIndex(int32 InMediaSourceIndex, const FCloseSourceArgs& InArgs = FCloseSourceArgs());` — Closes the specified media source, and optionally destroys the media player that was playing the source @param InMediaSourceIndex The index of the media source within the media profile @param InArgs Arguments that control what happens when the media source is closed
- L153 _public prototype_ `void CloseSource(UMediaSource* InMediaSource, const FCloseSourceArgs& InArgs = FCloseSourceArgs());` — Closes the specified media source, and optionally destroys the media player that was playing the source @param InMediaSource The media source within the media profile @param InArgs Arguments that control what happens when the media source is closed
- L159 _public prototype_ `void CloseSourcesForConsumer(const FCloseSourceArgs& InArgs);` — Closes all media sources that are being played by a specified consumer @param InArgs Arguments that control what happens when the media source is closed
- L168 _public prototype_ `TSharedPtr<FViewportClient> GetOrCreateManagedViewportFromIndex(int32 InMediaOutputIndex, EViewModeIndex InViewMode, void* Consumer = nullptr);` — Finds an existing or creates a new viewport to use for capture for a specified media output @param InMediaOutputIndex The index of the media output in the media profile @param InViewMode The view mode to create the viewport with @param Consumer Optional pointer to a consumer of the viewport, which ensures the viewport is not destroyed when the capture is closed @return The viewport client of the viewport of one was found or created; otherwise, null
- L177 _public prototype_ `TSharedPtr<FViewportClient> GetOrCreateManagedViewport(UMediaOutput* InMediaOutput, EViewModeIndex InViewMode, void* Consumer = nullptr);` — Finds an existing or creates a new viewport to use for capture for a specified media output @param InMediaOutput The media output in the media profile @param InViewMode The view mode to create the viewport with @param Consumer Optional pointer to a consumer of the viewport, which ensures the viewport is not destroyed when the capture is closed @return The viewport client of the viewport of one was found or created; otherwise, null
- L184 _public prototype_ `void ReleaseManagedViewportFromIndex(int32 InMediaOutputIndex, void* Consumer);` — Releases a use of the managed viewport for the specified media output,which may destroy the managed viewport if it is not actively being used @param InMediaOutputIndex The index of the media output in the media profile @param Consumer The pointer of the consumer that is releasing its reference of the managed viewport
- L191 _public prototype_ `void ReleaseManagedViewport(UMediaOutput* InMediaOutput, void* Consumer);` — Releases a use of the managed viewport for the specified media output,which may destroy the managed viewport if it is not actively being used @param InMediaOutput The media output in the media profile @param Consumer The pointer of the consumer that is releasing its reference of the managed viewport
- L200 _public prototype_ `UMediaCapture* OpenManagedViewportOutputFromIndex(int32 InMediaOutputIndex, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of a managed viewport for a specified media output @param InMediaOutputIndex The index of the media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L209 _public prototype_ `UMediaCapture* OpenManagedViewportOutput(UMediaOutput* InMediaOutput, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of a managed viewport for a specified media output @param InMediaOutput The media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L216 _public prototype_ `TSharedPtr<FSceneViewport> GetActiveViewportFromIndex(int32 InMediaOutputIndex) const;` — Gets an existing viewport in the engine that is or can be captured for the specified media output @param InMediaOutputIndex The index of the media output in the media profile @return A reference to the existing viewport, if one was found; otherwise, null
- L223 _public prototype_ `TSharedPtr<FSceneViewport> GetActiveViewport(UMediaOutput* InMediaOutput) const;` — Gets an existing viewport in the engine that is or can be captured for the specified media output @param InMediaOutput The media output in the media profile @return A reference to the existing viewport, if one was found; otherwise, null
- L232 _public prototype_ `UMediaCapture* OpenActiveViewportOutputFromIndex(int32 InMediaOutputIndex, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of an existing engine viewport for a specified media output @param InMediaOutputIndex The index of the media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L241 _public prototype_ `UMediaCapture* OpenActiveViewportOutput(UMediaOutput* InMediaOutput, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of an existing engine viewport for a specified media output @param InMediaOutput The media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L251 _public prototype_ `UMediaCapture* OpenRenderTargetOutputFromIndex(int32 InMediaOutputIndex, UTextureRenderTarget2D* InRenderTarget, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of a render target for a specified media output @param InMediaOutputIndex The index of the media output in the media profile @param InRenderTarget The render target to capture @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L261 _public prototype_ `UMediaCapture* OpenRenderTargetOutput(UMediaOutput* InMediaOutput, UTextureRenderTarget2D* InRenderTarget, const FMediaCaptureOptions& InCaptureOptions, bool bAutoRestartCapture = false);` — Starts a capture of a render target for a specified media output @param InMediaOutput The media output in the media profile @param InRenderTarget The render target to capture @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L272 _public prototype_ `UMediaCapture* OpenMediaTextureOutputFromIndex(int32 InMediaOutputIndex, UMediaTexture* InMediaTexture, const FMediaCaptureOptions& InCaptureOptions, const FMediaCaptureTransform& InTransform, bool bAutoRestartCapture = false);` — Starts a capture of a media texture for a specified media output @param InMediaOutputIndex The index of the media output in the media profile @param InMediaTexture The media texture to capture @param InCaptureOptions The capture options to capture with @param InTransform The transform to apply to the media texture on output @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L283 _public prototype_ `UMediaCapture* OpenMediaTextureOutput(UMediaOutput* InMediaOutput, UMediaTexture* InMediaTexture, const FMediaCaptureOptions& InCaptureOptions, const FMediaCaptureTransform& InTransform, bool bAutoRestartCapture = false);` — Starts a capture of a media texture for a specified media output @param InMediaOutput The media output in the media profile @param InMediaTexture The media texture to capture @param InCaptureOptions The capture options to capture with @param InTransform The transform to apply to the media texture on output @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected @return The media capture object, if the capture was started successfully; otherwise, null
- L291 _public prototype_ `void RestartActiveViewportOutput(UMediaOutput* InMediaOutput, FMediaCaptureOptions InCaptureOptions, bool bAutoRestartCapture = false);` — Restarts a capture of an existing engine viewport for a specified media output @param InMediaOutput The media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected
- L299 _public prototype_ `void RestartManagedViewportOutput(UMediaOutput* InMediaOutput, FMediaCaptureOptions InCaptureOptions, bool bAutoRestartCapture = false);` — Restarts a capture of a managed viewport for a specified media output @param InMediaOutput The media output in the media profile @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected
- L308 _public prototype_ `void RestartRenderTargetOutput(UMediaOutput* InMediaOutput, UTextureRenderTarget2D* InRenderTarget, FMediaCaptureOptions InCaptureOptions, bool bAutoRestartCapture = false);` — Restarts a capture of a render target for a specified media output @param InMediaOutput The media output in the media profile @param InRenderTarget The render target to capture @param InCaptureOptions The capture options to capture with @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected
- L318 _public prototype_ `void RestartMediaTextureOutput(UMediaOutput* InMediaOutput, UMediaTexture* InMediaTexture, FMediaCaptureOptions InCaptureOptions, FMediaCaptureTransform InTransform, bool bAutoRestartCapture = false);` — Restarts a capture of a media texture for a specified media output @param InMediaOutput The media output in the media profile @param InMediaTexture The media texture to capture @param InCaptureOptions The capture options to capture with @param InTransform The transform to apply to the media texture on output @param bAutoRestartCapture Indicates that this capture will automatically restart if any modifications to the media output are detected
- L325 _public prototype_ `bool IsOutputCapturingFromIndex(int32 InMediaOutputIndex) const;` — Gets whether there is an active capture for the specified media output index @param InMediaOutputIndex The index of the media output within the media profile to check @return true if the media output is actively being captured; otherwise false
- L332 _public prototype_ `bool IsOutputCapturing(UMediaOutput* InMediaOutput) const;` — Gets whether there is an active capture for the specified media output @param InMediaOutput The media output within the media profile to check @return true if the media output is actively being captured; otherwise false
- L340 _public prototype_ `TOptional<EMediaCaptureState> GetOutputCaptureStateFromIndex(int32 InMediaOutputIndex, bool& bOutHasError) const;` — Gets the capture state of the specified media output, or null of there is no active capture of the media output @param InMediaOutputIndex The index of the media output within the media profile to check @param bOutHasError Indicates that the capture state experienced an error at some point and is stopped @return The capture state of the media output, or a null TOptional if there is no active capture of the media output
- L348 _public prototype_ `TOptional<EMediaCaptureState> GetOutputCaptureState(UMediaOutput* InMediaOutput, bool& bOutHasError) const;` — Gets the capture state of the specified media output, or null of there is no active capture of the media output @param InMediaOutput The media output within the media profile to check @param bOutHasError Indicates that the capture state experienced an error at some point and is stopped @return The capture state of the media output, or a null TOptional if there is no active capture of the media output
- L370 _public prototype_ `void CloseOutputFromIndex(int32 InMediaOutputIndex, const FCloseOutputArgs& InArgs = FCloseOutputArgs());` — Closes the capture of the specified media output @param InMediaOutputIndex The index of the media output within the media profile @param InArgs Arguments that control what happens when the output is stopped.
- L377 _public prototype_ `void CloseOutput(UMediaOutput* InMediaOutput, const FCloseOutputArgs& InArgs = FCloseOutputArgs());` — Closes the capture of the specified media output @param InMediaOutput The media output in the media profile to close @param InArgs Arguments that control what happens when the output is stopped.
- L385 _private prototype_ `UMediaPlayer* FindOrCreateMediaPlayerForIndex(int32 InMediaSourceIndex);` — Attempts to find an existing media player for the specified source, and creates one if an existing one is not found @param InMediaSourceIndex The index of the media source within the media profile @return The media player for the media source, or null if no media source exists at the specified index
- L392 _private prototype_ `void ChangeMediaSourceIndex(int32 InOriginalMediaSourceIndex, int32 InNewMediaSourceIndex);` — Processes a change to a media source's slot index, moving any existing media players around to the correct media textures @param InOriginalMediaSourceIndex The original index of the media source, or INDEX_NONE if we are processing an insert @param InNewMediaSourceIndex The new index of the media source, or INDEX_NONE if we are processing a delete
- L395 _private prototype_ `UMediaProfile* GetOwningMediaProfile() const;` — Gets the media profile that owns this playback manager
- L398 _private prototype_ `void RegisterMediaSourceConsumer(UMediaPlayer* InMediaPlayer, void* InConsumer);` — Registers a consumer with a specific media player
- L401 _private prototype_ `void UnregisterMediaSourceConsumer(UMediaPlayer* InMediaPlayer, void* InConsumer);` — Unregisters a consumer with a sepcific media player
- L404 _private prototype_ `int32 GetMediaSourceConsumerCount(UMediaPlayer* InMediaPlayer) const;` — Gets the number of consumers that have registered as using the specified media player
- L407 _private prototype_ `UMediaCapture* FindOrCreateMediaCaptureForIndex(int32 InMediaOutputIndex);` — Attempts to find an existing valid capture or creates a new capture for the specified media output index
- L414 _private prototype_ `void ChangeMediaOutputIndex(int32 InOriginalMediaOutputIndex, int32 InNewMediaOutputIndex);` — Processes a change to a media output's slot index, moving any existing media captures around @param InOriginalMediaOutputIndex The original index of the media output, or INDEX_NONE if we are processing an insert @param InNewMediaOutputIndex The new index of the media output, or INDEX_NONE if we are processing a delete
- L417 _private prototype_ `void OnCaptureStateChanged(UMediaCapture* InMediaCapture);` — Raised when the capture state of the specified media capture has changed. Used to keep track of which captures may have errored
- L420 _private prototype_ `void QueueRestartCapture(UMediaOutput* InMediaOutput, FRecaptureFunc InRestartCaptureFunc);` — Raised when a change to the specified media output has been detected and the capture shout be auto-restarted
- L423 _private prototype_ `void DeferredRestart();` — Invoked through QueueRestartCapture when the StopCapture implementation is done.
- L426 _private prototype_ `void RestartCaptures();` — Called on the next available tick, restarts any captures that have been queued to auto-restart
- L429 _private prototype_ `void Cleanup();` — Cleans up all open sources and outputs, and deletes any managed state
- L432 _private prototype_ `void CleanUpCaptureResources(UMediaOutput* InMediaOutput);` — Cleans up any managed resources used by the specified media output, such as active viewports or managed viewports
- L435 _private prototype_ `void PostStopCapture(int32 InMediaOutputIndex, FCloseOutputArgs InArgs);` — Handles cleaning up resources and invoking the post StopCapture callback.
- L439 _private prototype_ `void OnPostPIEStarted(bool bIsSimulating);` — Raised when a PIE session has started
- L442 _private prototype_ `void OnPrePIEEnded(bool bIsSimulating);` — Raised when a PIE session is ending
- L445 _private prototype_ `void OnLevelViewportClientListChanged();` — Raised when the level editor's list of viewports has changed
- L451 _private member_ `TMap<int32, TObjectPtr<UMediaPlayer>> MediaSourcePlayers;` — `UPROPERTY(Transient)` — A map of media players, where the hash key is the index of the media source the player is playing
- L455 _private member_ `TArray<TSoftObjectPtr<UMediaTexture>> MediaSourceTextures;` — `UPROPERTY(Transient)` — A list of media textures to use to output the corresponding media sources
- L459 _private member_ `TMap<int32, TObjectPtr<UMediaCapture>> MediaOutputCaptures;` — `UPROPERTY(Transient)` — A map of media captures, where the hash key is the index of the media output being captured
- L462 _private member_ `TMap<TObjectPtr<UMediaPlayer>, TSet<void*>> SourceConsumers;` — Keeps track of registered consumers that are actively using an open media source
- L465 _private member_ `TArray<TSharedPtr<MediaProfilePlaybackManager::FManagedViewport>> ManagedOutputViewports;` — A list of viewports being managed by the playback manager,
- L468 _private member_ `TArray<TSharedPtr<MediaProfilePlaybackManager::FActiveViewport>> ActiveOutputViewports;` — A list of active viewports that are being captured from
- L471 _private member_ `TArray<TSharedPtr<MediaProfilePlaybackManager::FMediaTextureCapture>> MediaTextureCaptures;` — A list of media textures that are being captured from
- L474 _private member_ `TSet<TObjectPtr<UMediaCapture>> CapturesWithError;` — Keeps track of which captures have reported an error with the capture
- L477 _private member_ `TArray<FRecaptureFunc> RestartCaptureFuncs;` — A list of callbacks to use to auto-restart any stopped captures on the next tick
- L480 _private member_ `FTimerHandle RestartCapturesTimerHandle;` — Timer handle for auto-restarting output captures

#### struct `UMediaProfilePlaybackManager::FCloseSourceArgs`  
`struct FCloseSourceArgs`  
_L124-139_
- desc: Arguments that control what happens when a media source is closed
- L127 _public member_ `void* Consumer = nullptr;` — The consumer requesting the media source be closed
- L130 _public member_ `bool bDestroyMediaPlayer = false;` — Indicates that the media player should be destroyed after closing
- L133 _public member_ `bool bForceClose = false;` — Indicates that the media source should be closed even if it still has active consumers
- L136 _public member_ `bool bSoftClose = false;` — Indicates that the media source should stay open even if there are no active consumers
- L138 _public function_ `FCloseSourceArgs()`

#### struct `UMediaProfilePlaybackManager::FCloseOutputArgs`  
`struct FCloseOutputArgs`  
_L351-363_
- desc: Arguments that control what happens when a media output is closed
- L354 _public member_ `bool bDestroyCaptureObjects;` — Indicates that the media capture and all related objects should be destroyed. Set to false if the capture is immediately going to be restarted.
- L357 _public member_ `FSimpleDelegate Callback;` — Some capture implementations can take a few frames to completely stop. When they are completely done, this callback delegate will be invoked.
- L359 _public function_ `FCloseOutputArgs() : bDestroyCaptureObjects(true)`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace MediaProfilePlaybackManager`
- L36 _prototype_ `bool IsActiveViewportCaptureAllowed();` (scope `MediaProfilePlaybackManager`) — Queries a config property (MediaProfile.bAllowActiveViewportCapture, in DefaultEngine.ini) to determine if active viewport capture is allowed. If disabled, attempting to start active viewport captures in the playback manager will fail.
- L42 _prototype_ `bool IsManagedViewportCaptureAllowed();` (scope `MediaProfilePlaybackManager`) — Queries a config property (MediaProfile.bAllowManagedViewportCapture, in DefaultEngine.ini) to determine if managed viewport capture is allowed. If disabled, attempting to start managed viewport captures in the playback manager will fail.

### `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/MediaProfileSettings.h` (Public)


#### class `UMediaProfileSettings`  
`class UMediaProfileSettings : public UObject`  
_L23-101_
- reflection: `UCLASS(config=Game, defaultconfig)`
- inherits: `UObject`
- desc: Settings for the media profile.
- L35 _public member_ `bool bApplyInCommandlet;` — `UPROPERTY(Config, EditAnywhere, Category="MediaProfile")` — Apply the startup media profile even when we are running a commandlet. @note We always try to apply the user media profile before the startup media profile in the editor or standalone.
- L42 _public member_ `bool bAutosaveAfterChange = false;` — `UPROPERTY(Config)` — Forces the media profile to save itself after a property change (if the profile was already saved once)
- L48 _private member_ `TArray<TSoftObjectPtr<UProxyMediaSource>> MediaSourceProxy;` — `UPROPERTY(AdvancedDisplay, Config, EditAnywhere, Category="MediaProfile")`
- L51 _private member_ `TArray<TSoftObjectPtr<UProxyMediaOutput>> MediaOutputProxy;` — `UPROPERTY(AdvancedDisplay, Config, EditAnywhere, Category="MediaProfile")`
- L58 _private member_ `TSoftObjectPtr<UMediaProfile> StartupMediaProfile;` — `UPROPERTY(Config, EditAnywhere, Category="MediaProfile")` — The media profile to use at startup. @note The media profile can be overridden in the editor by user.
- L67 _public prototype_ `TArray<UProxyMediaSource*> LoadMediaSourceProxies() const;` — Get all the media source proxy. @return The an array of the media source proxy.
- L74 _public prototype_ `TArray<UProxyMediaOutput*> LoadMediaOutputProxies() const;` — Get all the media output proxy. @return The an array of the media output proxy.
- L81 _public prototype_ `UMediaProfile* GetStartupMediaProfile() const;` — Get the media profile used by the engine. @return The media profile, or nullptr if not set.
- L85 _public prototype_ `void SetMediaSourceProxy(const TArray<UProxyMediaSource*>& Proxies);` — Set the media proxies used by the engine.
- L88 _public prototype_ `void FillDefaultMediaSourceProxies(int32 NumSources, bool bSilent = false);` — Fills the list of proxy sources with the default proxy assets stored in the media framework plugin
- L91 _public prototype_ `void SetMediaOutputProxy(const TArray<UProxyMediaOutput*>& Proxies);` — Set the media proxies used by the engine.
- L94 _public prototype_ `void FillDefaultMediaOutputProxies(int32 NumOutputs, bool bSilent = false);` — Fills the list of proxy outputs with the default proxy assets stored in the media framework plugin
- L96 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L99 _public member_ `FSimpleMulticastDelegate OnMediaProxiesChanged;` — Called when a proxy changed.

#### class `UMediaProfileEditorSettings`  
`class UMediaProfileEditorSettings : public UObject`  
_L109-150_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the media profile in the editor or standalone. @note Cooked games don't use this media profile setting.
- L114 _private prototype_ `UMediaProfileEditorSettings();`
- L123 _public member_ `bool bDisplayInToolbar;` — `UPROPERTY(Config, EditAnywhere, Category = "MediaProfile", meta=(ConfigRestartRequired=true))` — Display the media profile icon in the editor toolbar.
- L127 _public member_ `bool bDisplayInMainEditor;` — `UPROPERTY(config, EditAnywhere, Category = "MediaProfile")` — When enabled, the media profile name will be displayed in the main editor UI.
- L136 _private member_ `TSoftObjectPtr<UMediaProfile> UserMediaProfile;` — `UPROPERTY(Config, EditAnywhere, Category="MediaProfile")` — The media profile to use in standalone & editor. @note The startup media profile in the project setting will be used when in cooked game.
- L146 _public prototype_ `UMediaProfile* GetUserMediaProfile() const;` — Get the media profile used by the engine when in the editor & standalone. @return The media profile, or nullptr if not set.
- L149 _public prototype_ `void SetUserMediaProfile(UMediaProfile* InMediaProfile) ;` — Set the media profile used by the engine when in the editor & standalone.
