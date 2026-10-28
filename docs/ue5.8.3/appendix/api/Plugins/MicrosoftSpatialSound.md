# Plugins / MicrosoftSpatialSound

- module root: `Plugins/Runtime/MicrosoftSpatialAudio/Source/MicrosoftSpatialSound`
- headers: 1; symbols: 43
- symbol kinds: class=3, function=6, member=22, prototype=11, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioExtensions, Core

### `Plugins/Runtime/MicrosoftSpatialAudio/Source/MicrosoftSpatialSound/Public/MicrosoftSpatialSoundPlugin.h` (Public)


#### struct `FSpatialSoundSourceObjectData`  
`struct FSpatialSoundSourceObjectData`  
_L16-49_
- desc: Struct to hold dynamic object data for Microsoft Spatial Sound API
- L18 _public function_ `FSpatialSoundSourceObjectData() : StartingPosition(FVector::ZeroVector) , CurrentPosition(FVector::ZeroVector) , TargetPosition(FVector::ZeroVector) , CurrentFrameLerpPosition(0) , NumberOfLerpFrames(0) , AudioBuffer(4096*50) , ObjectHandle(nullptr) , bActive(false) , bBuffering(false)`
- L32 _public member_ `FVector StartingPosition;` — The position of the spatial sound source
- L33 _public member_ `FVector CurrentPosition;`
- L34 _public member_ `FVector TargetPosition;`
- L35 _public member_ `int32 CurrentFrameLerpPosition;`
- L36 _public member_ `int32 NumberOfLerpFrames;`
- L39 _public member_ `Audio::TCircularAudioBuffer<float> AudioBuffer;` — A circular buffer to hold audio data from the source.
- L42 _public member_ `ISpatialAudioObject* ObjectHandle;` — The handle to the source
- L44 _public member_ `FCriticalSection ObjectCritSect;`
- L47 _public member_ `bool bActive;` — Whether or not this source data is active (playing sound)
- L48 _public member_ `bool bBuffering;`

#### class `FMicrosoftSpatialSound`  
`class FMicrosoftSpatialSound : public IAudioSpatialization, protected FRunnable`  
_L52-104_
- inherits: `IAudioSpatialization,FRunnable`
- desc: Implementation of IAudioSpatialization for Microsoft Spatial Sound API
- L57 _public prototype_ `FMicrosoftSpatialSound();`
- L58 _public prototype_ `~FMicrosoftSpatialSound();`
- L61 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;` — Begin IAudioSpatialization interface
- L62 _public prototype_ `virtual void Shutdown() override;`
- L63 _public function_ `virtual bool IsSpatializationEffectInitialized() const override`
- L64 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings) override;`
- L65 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) override;`
- L66 _public prototype_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);`
- L70 _public prototype_ `virtual uint32 Run() override;` — Begin FRunnable
- L75 _private prototype_ `void FreeResources();`
- L77 _private member_ `FAudioPluginInitializationParams InitializationParams;`
- L80 _private member_ `TQueue<TFunction<void()>> CommandQueue;` — Command queue
- L83 _private member_ `uint32 MinFramesRequiredPerObjectUpdate;` — The minimum amount of frames which need to be queued before processing audio objects
- L86 _private member_ `TArray<FSpatialSoundSourceObjectData> Objects;` — Array of spatial sound source objects
- L89 _private member_ `uint32 MaxDynamicObjects;` — The max dynamic objects
- L92 _private member_ `FRunnableThread* SpatialAudioRenderThread;` — The spatial audio render thread
- L95 _private member_ `FCriticalSection SpatialSoundCritSect;` — The rendering critical section
- L98 _private member_ `FThreadSafeBool bIsRendering;` — If the spatial audio render thread is running
- L100 _private member_ `SpatialAudioClient* SAC;`
- L102 _private member_ `bool bIsInitialized;`

#### class `FMicrosoftSpatialSoundPluginFactory`  
`class FMicrosoftSpatialSoundPluginFactory : public IAudioSpatializationFactory`  
_L106-128_
- inherits: `IAudioSpatializationFactory`
- L110 _public function_ `virtual FString GetDisplayName() override`
- L116 _public function_ `virtual bool SupportsPlatform(const FString& PlatformName) override`
- L122 _public function_ `virtual bool IsExternalSend() override` — Microsoft spatial sound dynamic objects render objects externally from the audio renderer
- L124 _public function_ `virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override`

#### class `FMicrosoftSpatialSoundModule`  
`class FMicrosoftSpatialSoundModule : public IModuleInterface`  
_L130-139_
- inherits: `IModuleInterface`
- L133 _public prototype_ `virtual void StartupModule() override;`
- L134 _public prototype_ `virtual void ShutdownModule() override;`
- L137 _private member_ `void* LibraryHandle = nullptr;`
- L138 _private member_ `FMicrosoftSpatialSoundPluginFactory PluginFactory;`
