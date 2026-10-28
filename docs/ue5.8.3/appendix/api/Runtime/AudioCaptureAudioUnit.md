# Runtime / AudioCaptureAudioUnit

- module root: `Source/Runtime/AudioCaptureImplementations/IOS/AudioCaptureAudioUnit`
- headers: 1; symbols: 27
- symbol kinds: class=1, function=1, member=9, namespace=1, prototype=15
- PrivateDependencyModuleNames: AudioCaptureCore, Core

### `Source/Runtime/AudioCaptureImplementations/IOS/AudioCaptureAudioUnit/Private/AudioCaptureAudioUnit.h` (Private)


#### class `Audio::FAudioCaptureAudioUnitStream`  
`class FAudioCaptureAudioUnitStream : public IAudioCaptureStream`  
_L10-44_
- inherits: `IAudioCaptureStream`
- L13 _public prototype_ `FAudioCaptureAudioUnitStream();`
- L15 _public prototype_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) override;`
- L16 _public prototype_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction InOnCapture, uint32 NumFramesDesired) override;`
- L17 _public prototype_ `virtual bool CloseStream() override;`
- L18 _public prototype_ `virtual bool StartStream() override;`
- L19 _public prototype_ `virtual bool StopStream() override;`
- L20 _public prototype_ `virtual bool AbortStream() override;`
- L21 _public prototype_ `virtual bool GetStreamTime(double& OutStreamTime) override;`
- L22 _public function_ `virtual int32 GetSampleRate() const override`
- L23 _public prototype_ `virtual bool IsStreamOpen() const override;`
- L24 _public prototype_ `virtual bool IsCapturing() const override;`
- L25 _public prototype_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) override;`
- L26 _public prototype_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) override;`
- L27 _public prototype_ `virtual void SetHardwareFeatureEnabled(EHardwareInputFeature FeatureType, bool bEnabled);`
- L29 _public prototype_ `OSStatus OnCaptureCallback( AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList* ioData );`
- L32 _private prototype_ `void AllocateBuffer(int SizeInBytes);`
- L34 _private member_ `AudioComponentInstance IOUnit;`
- L36 _private member_ `FOnAudioCaptureFunction OnCapture;`
- L37 _private member_ `int32 NumChannels;`
- L38 _private member_ `int32 SampleRate;`
- L39 _private member_ `TArray<uint8> CaptureBuffer;`
- L40 _private member_ `int BufferSize = 0;`
- L41 _private member_ `bool bIsStreamOpen;`
- L42 _private member_ `bool bHasCaptureStarted;`
- L43 _private member_ `bool bIsHardwareVoiceProcessingSupported;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
