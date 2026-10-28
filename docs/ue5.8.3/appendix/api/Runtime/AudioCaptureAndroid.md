# Runtime / AudioCaptureAndroid

- module root: `Source/Runtime/AudioCaptureImplementations/Android/AudioCaptureAndroid`
- headers: 1; symbols: 20
- symbol kinds: class=1, function=1, member=4, namespace=1, prototype=13
- PrivateDependencyModuleNames: AudioCaptureCore, Core, GoogleOboe
- PublicIncludePathModuleNames: GoogleOboe

### `Source/Runtime/AudioCaptureImplementations/Android/AudioCaptureAndroid/Private/AudioCaptureAndroid.h` (Private)


#### class `Audio::FAudioCaptureAndroidStream`  
`class FAudioCaptureAndroidStream : public IAudioCaptureStream, public oboe::AudioStreamCallback`  
_L9-37_
- inherits: `IAudioCaptureStream,oboe::AudioStreamCallback`
- L12 _public prototype_ `FAudioCaptureAndroidStream();`
- L14 _public prototype_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) override;`
- L15 _public prototype_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction InOnCapture, uint32 NumFramesDesired) override;`
- L16 _public prototype_ `virtual bool CloseStream() override;`
- L17 _public prototype_ `virtual bool StartStream() override;`
- L18 _public prototype_ `virtual bool StopStream() override;`
- L19 _public prototype_ `virtual bool AbortStream() override;`
- L20 _public prototype_ `virtual bool GetStreamTime(double& OutStreamTime) override;`
- L21 _public function_ `virtual int32 GetSampleRate() const override`
- L22 _public prototype_ `virtual bool IsStreamOpen() const override;`
- L23 _public prototype_ `virtual bool IsCapturing() const override;`
- L24 _public prototype_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) override;`
- L25 _public prototype_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) override;`
- L28 _public prototype_ `virtual oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32 numFrames) override;` — begin oboe::AudioStreamCallback
- L32 _private member_ `FOnAudioCaptureFunction OnCapture;`
- L33 _private member_ `int32 NumChannels;`
- L34 _private member_ `int32 SampleRate;`
- L36 _private member_ `TUniquePtr<oboe::AudioStream> InputOboeStream;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
