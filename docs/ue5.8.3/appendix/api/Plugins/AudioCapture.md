# Plugins / AudioCapture

- module root: `Plugins/Runtime/AudioCapture/Source/AudioCapture`
- headers: 3; symbols: 58
- symbol kinds: class=5, delegate=2, function=1, macro=3, member=21, prototype=24, struct=2
- PrivateDependencyModuleNames: AudioCaptureAndroid, AudioCaptureAudioUnit, AudioCaptureRtAudio, AudioCaptureWasapi
- PublicDependencyModuleNames: AudioCaptureCore, AudioMixer, Core, CoreUObject, Engine

### `Plugins/Runtime/AudioCapture/Source/AudioCapture/Public/AudioCapture.h` (Public)


#### class `FAudioCaptureModule`  
`class FAudioCaptureModule : public IModuleInterface`  
_L22-27_
- inherits: `IModuleInterface`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`

#### struct `FAudioCaptureDeviceInfo`  
`struct FAudioCaptureDeviceInfo`  
_L31-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct defining the time synth global quantization settings
- L37 _public member_ `FName DeviceName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")` — The name of the audio capture device
- L41 _public member_ `int32 NumInputChannels = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")` — The number of input channels
- L45 _public member_ `int32 SampleRate = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")` — The sample rate of the audio capture device

#### class `UAudioCapture`  
`class UAudioCapture : public UAudioGenerator`  
_L51-80_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioGenerator`
- desc: Class which opens up a handle to an audio capture device. Allows other objects to get audio buffers from the capture device.
- L56 _public prototype_ `UAudioCapture();`
- L57 _public prototype_ `~UAudioCapture();`
- L59 _public prototype_ `bool OpenDefaultAudioStream();`
- L63 _public prototype_ `bool GetAudioCaptureDeviceInfo(FAudioCaptureDeviceInfo& OutInfo);` — `UFUNCTION(BlueprintCallable, Category = "AudioCapture")` — Returns the audio capture device info
- L67 _public prototype_ `void StartCapturingAudio();` — `UFUNCTION(BlueprintCallable, Category = "AudioCapture")` — Starts capturing audio
- L71 _public prototype_ `void StopCapturingAudio();` — `UFUNCTION(BlueprintCallable, Category = "AudioCapture")` — Stops capturing audio
- L75 _public prototype_ `bool IsCapturingAudio();` — `UFUNCTION(BlueprintCallable, Category = "AudioCapture")` — Returns true if capturing audio
- L79 _protected member_ `Audio::FAudioCapture AudioCapture;`

#### class `UAudioCaptureFunctionLibrary`  
`class UAudioCaptureFunctionLibrary : public UBlueprintFunctionLibrary`  
_L83-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L89 _public prototype_ `static class UAudioCapture* CreateAudioCapture();` — `UFUNCTION(BlueprintCallable, Category = "Audio Capture")`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API AUDIOCAPTURE_API`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioCapture, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioCapture, Log, All);`

### `Plugins/Runtime/AudioCapture/Source/AudioCapture/Public/AudioCaptureBlueprintLibrary.h` (Public)


#### struct `FAudioInputDeviceInfo`  
`struct FAudioInputDeviceInfo`  
_L26-59_
- reflection: `USTRUCT(BlueprintType)`
- desc: Platform audio input device info, in a Blueprint-readable format
- L30 _public function_ `FAudioInputDeviceInfo() : DeviceName(""), DeviceId(""), InputChannels(0), PreferredSampleRate(0), bSupportsHardwareAEC(true)`
- L38 _public prototype_ `FAudioInputDeviceInfo(const Audio::FCaptureDeviceInfo& InDeviceInfo);`
- L42 _public member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The name of the audio device
- L46 _public member_ `FString DeviceId;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — ID of the device.
- L50 _public member_ `int32 InputChannels;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The number of channels supported by the audio device
- L54 _public member_ `int32 PreferredSampleRate;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The preferred sample rate of the audio device
- L58 _public member_ `uint8 bSupportsHardwareAEC : 1;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — Whether or not the device supports Acoustic Echo Canceling

#### class `UAudioCaptureBlueprintLibrary`  
`class UAudioCaptureBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L67-87_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "AudioCaptureLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L79 _public prototype_ `static FString Conv_AudioInputDeviceInfoToString(const FAudioInputDeviceInfo& info);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Audio Input Device Info To String", CompactNodeTitle = "To String", BlueprintAutocast), Category = "Audio")` — Returns the device info in a human readable format @param info - The audio device data to print @return The data in a string format
- L86 _public prototype_ `static void GetAvailableAudioInputDevices(const UObject* WorldContextObject, const FOnAudioInputDevicesObtained& OnObtainDevicesEvent);` — `UFUNCTION(BlueprintCallable, Category = "Audio", meta = (WorldContext = "WorldContextObject"))` — Gets information about all audio output devices available in the system @param OnObtainDevicesEvent - the event to fire when the audio endpoint devices have been retrieved

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API AUDIOCAPTURE_API`
- L64 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAudioInputDevicesObtained, const TArray<FAudioInputDeviceInfo>&, AvailableDevices);` — Called when a list of all available audio devices is retrieved
- L64 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAudioInputDevicesObtained, const TArray<FAudioInputDeviceInfo>&, AvailableDevices);` — Called when a list of all available audio devices is retrieved

### `Plugins/Runtime/AudioCapture/Source/AudioCapture/Public/AudioCaptureComponent.h` (Public)


#### class `UAudioCaptureComponent`  
`class UAudioCaptureComponent : public USynthComponent`  
_L13-57_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L19 _protected prototype_ `UAudioCaptureComponent(const FObjectInitializer& ObjectInitializer);`
- L22 _protected prototype_ `virtual bool Init(int32& SampleRate) override;`
- L23 _protected prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L24 _protected prototype_ `virtual void OnBeginGenerate() override;`
- L25 _protected prototype_ `virtual void OnEndGenerate() override;`
- L29 _protected prototype_ `virtual void BeginDestroy();`
- L30 _protected prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L31 _protected prototype_ `virtual void FinishDestroy() override;`
- L32 _protected prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L41 _public member_ `int32 JitterLatencyFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Latency", meta = (ClampMin = "0", ClampMax = "1024"))` — Induced latency in audio frames to use to account for jitter between mic capture hardware and audio render hardware. Increasing this number will increase latency but reduce potential for underruns.
- L45 _private member_ `Audio::FAudioCaptureSynth CaptureSynth;`
- L46 _private member_ `TArray<float> CaptureAudioData;`
- L47 _private member_ `int32 CapturedAudioDataSamples;`
- L49 _private member_ `bool bSuccessfullyInitialized;`
- L50 _private member_ `bool bIsCapturing;`
- L51 _private member_ `bool bIsStreamOpen;`
- L52 _private member_ `int32 CaptureChannels;`
- L53 _private member_ `int32 FramesSinceStarting;`
- L54 _private member_ `int32 ReadSampleIndex;`
- L55 _private member_ `FThreadSafeBool bIsDestroying;`
- L56 _private member_ `FThreadSafeBool bIsNotReadyForForFinishDestroy;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOCAPTURE_API`
