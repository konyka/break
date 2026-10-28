# Runtime / AudioCaptureWasapi

- module root: `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi`
- headers: 6; symbols: 139
- symbol kinds: class=6, enum=2, enumerator=8, function=1, macro=1, member=33, namespace=5, prototype=80, struct=1, typedef=2
- PrivateDependencyModuleNames: AudioCaptureCore, AudioPlatformSupportWasapi, Core

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/AudioCaptureWasapi.h` (Private)


#### class `Audio::FAudioCaptureWasapiStream`  
`class FAudioCaptureWasapiStream : public IAudioCaptureStream`  
_L16-69_
- inherits: `IAudioCaptureStream`
- desc: WASAPI implementation of IAudioCaptureStream which encapsulates capturing audio streams from device.
- L19 _public prototype_ `FAudioCaptureWasapiStream();`
- L22 _public prototype_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) override;`
- L24 _public prototype_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction InOnCapture, uint32 NumFramesDesired) override;`
- L26 _public prototype_ `virtual bool CloseStream() override;`
- L28 _public prototype_ `virtual bool StartStream() override;`
- L30 _public prototype_ `virtual bool StopStream() override;`
- L32 _public prototype_ `virtual bool AbortStream() override;`
- L34 _public prototype_ `virtual bool GetStreamTime(double& OutStreamTime) override;`
- L36 _public function_ `virtual int32 GetSampleRate() const override`
- L38 _public prototype_ `virtual bool IsStreamOpen() const override;`
- L40 _public prototype_ `virtual bool IsCapturing() const override;`
- L42 _public prototype_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) override;`
- L44 _public prototype_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) override;`
- L49 _private member_ `FOnAudioCaptureFunction OnCapture;` — Audio callback which will be called during audio capture.
- L51 _private member_ `int32 NumChannels = InvalidDeviceChannelCount;` — The number of channels to capture audio data on from the device.
- L53 _private member_ `int32 SampleRate = InvalidDeviceSampleRate;` — The sample rate used during this capture.
- L55 _private member_ `FWasapiStreamManager CaptureDevice;` — The aggregate capture device which manages one or more capture streams.
- L65 _private prototype_ `static bool GetAudioFormatFromCaptureParams( const FAudioCaptureDeviceParams& InParams, const FWasapiDeviceEnumeration::FDeviceInfo& InDeviceInfo, FWasapiAudioFormat& OutAudioFormat);` — GetAudioFormatFromCaptureParams - Converts FAudioCaptureDeviceParams into a corresponding FWasapiAudioFormat utilizing InDeviceInfo for default values if needed. @param InParams - The capture parameters supplied by the caller to be used when configuring the audio format. @param InDeviceInfo - The audio device info which will be used as a fallback for default format values if needed. @param OutAudioFormat - The resulting audio format to corresponding to the input parameters.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/WasapiCaptureLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define WASAPI_CAPTURE_LOG_RESULT(FunctionName, Result) \`

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/WasapiCaptureThread.h` (Private)


#### class `Audio::FWasapiCaptureRunnable`  
`class FWasapiCaptureRunnable : public FRunnable`  
_L17-57_
- inherits: `FRunnable`
- desc: FWasapiCaptureRunnable - The runnable which executes the main thread loop for FWasapiCaptureThread. It has a pointer to a FWasapiInputStream which it uses to coordinating waiting for new data and delivery of that data to the audio callback.
- L20 _public prototype_ `FWasapiCaptureRunnable() = delete;`
- L21 _public prototype_ `FWasapiCaptureRunnable(FWasapiCaptureRunnable&& InOther) = delete;`
- L22 _public prototype_ `FWasapiCaptureRunnable(const FWasapiCaptureRunnable& InOther) = delete;`
- L24 _public prototype_ `FWasapiCaptureRunnable& operator=(FWasapiCaptureRunnable&& InOther) = delete;`
- L25 _public prototype_ `FWasapiCaptureRunnable& operator=(const FWasapiCaptureRunnable& InOther) = delete;`
- L32 _public prototype_ `explicit FWasapiCaptureRunnable(TSharedPtr<FWasapiInputStream> InStream);` — FWasapiCaptureRunnable - Constructor with given FWasapiInputStream. @param InStream - The stream which will receive audio data as it is received.
- L35 _public prototype_ `virtual ~FWasapiCaptureRunnable() = default;` — Default destructor
- L38 _public prototype_ `virtual uint32 Run() override;`
- L39 _public prototype_ `virtual void Stop() override;`
- L44 _private member_ `std::atomic<bool> bIsRunning;` — bIsRunning - The main run loop for this runnable will continue iterating while this flag is true.
- L49 _private member_ `uint32 InputStreamTimeoutsDetected = 0;` — InputStreamTimeoutsDetected - Accumulates timeouts which occur when the thread event timeout is reached prior to the event being signaled for new data being available.
- L54 _private member_ `uint32 InputStreamDeviceErrorsDetected = 0;` — InputStreamDeviceErrorsDetected - Accumulates any device errors which occur. Device errors which can happen if the device goes off line during capture (e.g. unplugged USB device).
- L56 _private member_ `TSharedPtr<FWasapiInputStream> InputStream;` — InputStream - The input stream which will be run and periodically receive new audio data.

#### class `Audio::FWasapiCaptureThread`  
`class FWasapiCaptureThread`  
_L62-95_
- desc: FWasapiCaptureThread - Manages both the FWasapiCaptureRunnable object and the thread whose context it runs in.
- L65 _public prototype_ `FWasapiCaptureThread() = delete;`
- L70 _public prototype_ `explicit FWasapiCaptureThread(TSharedPtr<FWasapiInputStream> InStream);` — FWasapiCaptureThread - Constructor which accepts FWasapiInputStream and creates FWasapiCaptureRunnable with it.
- L77 _public prototype_ `bool Start();` — Start - Creates the FRunnableThread object which immediately begins running the FWasapiCaptureRunnable member. @return - Boolean indicating of the thread was succesfully created.
- L82 _public prototype_ `void Stop();` — Stop - Gracefully shuts down the capture thread.
- L88 _public prototype_ `void Abort();` — Abort - Performs non-graceful shutdown of capture thread which will close the underyling thread handle without waiting for it to finish.
- L92 _private member_ `TUniquePtr<FRunnableThread> CaptureThread;` — The thread which is the context that the capture runnable executes in.
- L94 _private member_ `TUniquePtr<FWasapiCaptureRunnable> CaptureRunnable;` — The capture runnable which manages the run loop for the capture stream.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/WasapiDeviceEnumeration.h` (Private)


#### class `Audio::FWasapiDeviceEnumeration`  
`class FWasapiDeviceEnumeration`  
_L26-142_
- desc: FWasapiDeviceEnumeration - Class which wraps Microsoft's IMM device enumeration API.
- L55 _public prototype_ `FWasapiDeviceEnumeration() = default;`
- L56 _public prototype_ `~FWasapiDeviceEnumeration() = default;`
- L59 _public prototype_ `void Initialize();` — Instantiates DeviceEnumerator and initializes the default input and output devices IDs.
- L62 _public prototype_ `FString GetDefaultInputDeviceId();` — Returns the Id of the default input device.
- L64 _public prototype_ `FString GetDefaultOutputDeviceId();` — Returns the Id of the default output device.
- L74 _public prototype_ `bool GetDeviceInfo(const FString& InDeviceId, FDeviceInfo& OutDeviceInfo);` — GetDeviceInfo - Gets the FDeviceInfo for the device with the given Id. @param InDeviceId - The Id of the device to fetch information for. @param OutDeviceInfo - Upon success, the device info struct for the device. Untouched on failure. @return - Boolean indicating success or failure when attempting to fetch the device info.
- L84 _public prototype_ `bool GetDeviceIdFromIndex(int32 InDeviceIndex, EDataFlow InDataFlow, FString& OutDeviceId);` — GetDeviceIdFromIndex - Gets the device Id from a device index. @param InDeviceIndex - The index for the device to get the Id for. @param InDataFlow - Indicates which device collection to search (render, capture or both). @param OutDeviceId - Upon success, the Id of the device at the given index. @return - Boolean indicating success or failure when looking up the device index.
- L94 _public prototype_ `bool GetDeviceIndexFromId(const FString& InDeviceId, int32& OutDeviceIndex);` — GetDeviceIndexFromId - Gets the index of a device with the given Id. Searches the collection of active devices for both capture and render data flows. @param InDeviceId - Device Id to get the index for. @param OutDeviceIndex - Upon success, will contain the index for the device. @return - Boolean indicating success or failure when looking up the device Id.
- L102 _public prototype_ `bool GetInputDevicesAvailable(TArray<FDeviceInfo>& OutDevices);` — GetInputDevicesAvailable - Gets the collection of currently active audio capture devices. @param OutDevices - TArray of FDeviceInfo objects for the currently available capture devices. @return - Boolean indicating success or failure when access the collection of devices.
- L111 _public prototype_ `bool GetIMMDevice(const FString& InDeviceId, TComPtr<IMMDevice>& OutDevice);` — GetIMMDevice - Gets a COM pointer to the IMMDevice for the give device Id. @param InDeviceId - Device Id of the device to get. @param OutDevice - COM pointer to the device for the given Id. @return - Boolean indicating success or failure when looking up the give Id.
- L115 _private member_ `FString DefaultRenderId;` — The Id of the system default render device.
- L117 _private member_ `FString DefaultCaptureId;` — The Id of the system default capture device.
- L119 _private member_ `TComPtr<IMMDeviceEnumerator> DeviceEnumerator;` — COM pointer to the device enumerator used by this class to find audio devices and their properties.
- L122 _private prototype_ `void EnumerateDefaults();` — EnumerateDefaults - Get the IDs for the system default devices.
- L125 _private prototype_ `bool GetDeviceProperties(TComPtr<IMMDevice> InDevice, FDeviceInfo& OutInfo);` — GetDeviceProperties - Convenience function for getting the device info of an IMMDevice.
- L128 _private prototype_ `bool GetDeviceId(TComPtr<IMMDevice> InDevice, FString& OutString);` — GetDeviceId - Convenience function for getting the device Id of an IMMDevice.
- L131 _private prototype_ `bool GetDeviceFriendlyName(TComPtr<IMMDevice> InDevice, FString& OutString);` — GetDeviceFriendlyName - Convenience function for getting the friendly name of an IMMDevice.
- L134 _private prototype_ `FDeviceInfo::EEndpointType GetEndpointType(TComPtr<IMMDevice> InDevice);` — GetEndpointType - Returns endpoint type (render or capture) for the given IMMDevice.
- L141 _private prototype_ `bool GetAudioClientMixFormat(TComPtr<IAudioClient3> AudioClient, WAVEFORMATEX** OutFormat);` — GetAudioClientMixFormat - Returns the current mix format for the given audio client. The mix format is the audio format used by the OS audio mixer when mixing shared mode streams.

#### struct `Audio::FWasapiDeviceEnumeration::FDeviceInfo`  
`struct FDeviceInfo`  
_L32-53_
- desc: FDeviceInfo - Properties associated with an audio device.
- L40 _public member_ `FString DeviceId;` — Unique identifier for this device.
- L42 _public member_ `FString FriendlyName;` — Human readable name for this device.
- L44 _public member_ `uint32 NumInputChannels = 0;` — Number of input channels on this device available for recording.
- L46 _public member_ `uint32 NumOutputChannels = 0;` — Number of output channels on this device available for playback.
- L48 _public member_ `uint32 BitsPerSample = 0;` — The current bit depth configured for this device. Additional bit depths may be supported.
- L50 _public member_ `uint32 PreferredSampleRate = 0;` — The preferred sample rate for this device. Additional sample rates may be supported.
- L52 _public member_ `EEndpointType EndpointType = EEndpointType::Unknown;` — The endpoint type for this device (Render or Capture).

#### enum `Audio::FWasapiDeviceEnumeration::FDeviceInfo::EEndpointType`  
`enum class EEndpointType`  
_L37-37_
- desc: EEndpointType - Designates whether a device is a capture or render device.
- L37 _public enumerator_ `enum class EEndpointType { Unknown, Render, Capture }; FString DeviceId; FString FriendlyName; uint32 NumInputChannels = 0;` — EEndpointType - Designates whether a device is a capture or render device.
- L37 _public enumerator_ `enum class EEndpointType { Unknown, Render, Capture }; FString DeviceId; FString FriendlyName; uint32 NumInputChannels = 0;` — EEndpointType - Designates whether a device is a capture or render device.
- L37 _public enumerator_ `enum class EEndpointType { Unknown, Render, Capture }; FString DeviceId; FString FriendlyName; uint32 NumInputChannels = 0;` — EEndpointType - Designates whether a device is a capture or render device.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Audio`

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/WasapiInputStream.h` (Private)


#### class `Audio::FWasapiInputStream`  
`class FWasapiInputStream`  
_L33-104_
- desc: FWasapiInputStream - This class manages the WASPI audio client, capture buffers and audio callback used during capture.
- L36 _public prototype_ `FWasapiInputStream() = delete;`
- L37 _public prototype_ `FWasapiInputStream(FWasapiInputStream&& InOther) = delete;`
- L38 _public prototype_ `FWasapiInputStream(const FWasapiInputStream& InOther) = delete;`
- L40 _public prototype_ `FWasapiInputStream( TComPtr<IMMDevice> InDevice, const FWasapiAudioFormat& InFormat, uint32 InNumFramesDesired, FWasapiOnAudioCaptureFunction InCallback);`
- L46 _public prototype_ `~FWasapiInputStream();`
- L48 _public prototype_ `FWasapiInputStream& operator=(FWasapiInputStream&& InOther) = delete;`
- L49 _public prototype_ `FWasapiInputStream& operator=(const FWasapiInputStream& InOther) = delete;`
- L52 _public prototype_ `bool IsInitialized() const;` — Returns whether or not this object has been successfully initialized.
- L55 _public prototype_ `void StartStream();` — Starts the audio capture which triggers periodic callbacks with new audio data.
- L57 _public prototype_ `void StopStream();` — Stops the audio client which will shut down the stream and any further callbacks.
- L60 _public prototype_ `bool WaitOnBuffer() const;` — Waits on the audio client event handle which will get set when new capture data is available.
- L62 _public prototype_ `bool CaptureAudioFrames();` — The capture thread calls this periodically with new audio data during a capture.
- L65 _public prototype_ `uint32 GetBufferSizeFrames() const;` — Returns the buffer size in frames for the buffer for the audio callback.
- L67 _public prototype_ `uint32 GetBufferSizeBytes() const;` — Returns the buffer size in bytes corresponding to the buffer for the audio callback.
- L69 _public prototype_ `double GetStreamPosition() const;` — Returns the current stream position in seconds.
- L74 _private member_ `TComPtr<IAudioClient3> AudioClient;` — COM pointer to the WASAPI audio client object.
- L76 _private member_ `TComPtr<IAudioCaptureClient> CaptureClient;` — COM pointer to the WASAPI capture client object.
- L79 _private member_ `FWasapiAudioFormat AudioFormat;` — Holds the audio format configuration for this stream.
- L82 _private member_ `bool bIsInitialized = false;` — Indicates if this object has been successfully initialized.
- L85 _private member_ `uint32 NumFramesPerBuffer = 0;` — Number of frames of audio data which will be used for each audio callback during capture.
- L87 _private member_ `std::atomic<double> DevicePosition = 0.0;` — Current device position as reported by WASAPI each callback.
- L92 _private member_ `HANDLE EventHandle = nullptr;` — Event handle which our capture thread waits on prior to each callback. WASAPI signals this object each quanta when a buffer of audio has been captured and is ready to be consumed downstream.
- L95 _private member_ `FWasapiOnAudioCaptureFunction OnAudioCaptureCallback;` — The callback used to periodically deliver new audio data during capture.
- L97 _private member_ `TArray<uint8> SilienceBuffer;` — Buffer used when WASAPI indicates that silence should be output for a given callback.
- L103 _private prototype_ `bool DrainInputBuffer();` — DrainInputBuffer - Prepares the capture client by draining the input buffer of any audio data which may have accumulated.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Audio`
- L28 _typedef_ `typedef TFunction<void(void* InBuffer, uint32 InNumFrames, double InStreamPosition, bool bInDiscontinuityError)> FWasapiOnAudioCaptureFunction;` (scope `Audio`) — FWasapiOnAudioCaptureFunction - Callback function type for receiving audio from a capture device.

### `Source/Runtime/AudioCaptureImplementations/Windows/AudioCaputureWasapi/Private/WasapiStreamManager.h` (Private)


#### class `Audio::FWasapiStreamManager`  
`class FWasapiStreamManager`  
_L18-115_
- desc: FWasapiStreamManager - Top level object for managing audio captures. It is composed of a device enumerator, capture thread, input stream and state machine. In the future, additional input streams may be managed here in support of multi-track capture.
- L22 _public typedef_ `using FDeviceInfo = FWasapiDeviceEnumeration::FDeviceInfo;`
- L24 _public prototype_ `FWasapiStreamManager();`
- L25 _public prototype_ `FWasapiStreamManager(FWasapiStreamManager&& InOther) = delete;`
- L26 _public prototype_ `FWasapiStreamManager(const FWasapiStreamManager& InOther) = delete;`
- L28 _public prototype_ `virtual ~FWasapiStreamManager();`
- L30 _public prototype_ `FWasapiStreamManager& operator=(FWasapiStreamManager&& InOther) = delete;`
- L31 _public prototype_ `FWasapiStreamManager& operator=(const FWasapiStreamManager& InOther) = delete;`
- L34 _public prototype_ `FString GetDefaultInputDeviceId();` — Returns the default input device Id.
- L36 _public prototype_ `FString GetDefaultOutputDeviceId();` — Returns the default output device Id.
- L41 _public prototype_ `bool GetDeviceInfo(const FString& InDeviceId, FDeviceInfo& OutDeviceInfo);` — GetDeviceInfo - Convienence method for FWasapiDeviceEnumeration::GetDeviceInfo()
- L46 _public prototype_ `bool GetDeviceIndexFromId(const FString& InDeviceId, int32& OutDeviceIndex);` — GetDeviceIndexFromId - Convienence method for FWasapiDeviceEnumeration::GetDeviceIndexFromId()
- L51 _public prototype_ `bool GetDeviceIdFromIndex(int32 InDeviceIndex, EDataFlow InDataFlow, FString& OutDeviceId);` — GetDeviceIdFromIndex - Convienence method for FWasapiDeviceEnumeration::GetDeviceIdFromIndex()
- L56 _public prototype_ `bool GetInputDevicesAvailable(TArray<FDeviceInfo>& OutDevices);` — GetInputDevicesAvailable - Convienence method for FWasapiDeviceEnumeration::GetInputDevicesAvailable()
- L68 _public prototype_ `bool OpenStream( const FString& InDeviceId, const FWasapiAudioFormat& InFormat, uint32 InNumFramesDesired, FWasapiOnAudioCaptureFunction InCallback);` — OpenStream - Finds the device for the given Id and prepares it for capturing audio. It also spawns a capture thread. @param InDeviceId - Id of the device to use for capturing audio. @param InFormat - The audio format to use for the capture. @param InNumFramesDesired - The number of audio frames desired when audio is delivered via the capture callback. @param InCallback - The callback which is called periodically during capture with audio data.
- L75 _public prototype_ `bool IsStreamOpen() const;` — Returns whether or not this object has been successfully initialized.
- L78 _public prototype_ `void StartStream();` — Starts the audio capture which triggers periodic callbacks with new audio data.
- L80 _public prototype_ `bool IsCapturing() const;` — Indicates if the stream was successfully started and is capturing data.
- L82 _public prototype_ `void StopStream();` — Stops the capture thread which, in turn, completes the runnable and stops the input stream.
- L85 _public prototype_ `void AbortStream();` — Brute force stops the capture thread.
- L87 _public prototype_ `void CloseStream();` — Releases resources related to the capture thread and input streams.
- L90 _public prototype_ `uint32 GetStreamBufferSizeBytes() const;` — Returns the buffer size in bytes of the callback buffer.
- L92 _public prototype_ `double GetStreamPosition() const;` — Returns the current position (in seconds) of the input stream.
- L105 _private member_ `EStreamState State = EStreamState::STREAM_CLOSED;` — Current state of the state machine.
- L108 _private member_ `FWasapiDeviceEnumeration DeviceEnumerator;` — Object used to enumerate audio devices present in the system.
- L111 _private member_ `TSharedPtr<FWasapiInputStream> InputStream;` — The input stream for the selected device which will stream audio during capture.
- L114 _private member_ `TUniquePtr<FWasapiCaptureThread> CaptureThread;` — The thread which provides an execution context during audio capture.

#### enum `Audio::FWasapiStreamManager::EStreamState`  
`enum class EStreamState`  
_L96-102_
- desc: The states used by the state machine.
- L97 _public enumerator_ `INVALID_STATE`
- L98 _public enumerator_ `STREAM_CLOSED`
- L99 _public enumerator_ `STREAM_STOPPED`
- L100 _public enumerator_ `STREAM_STOPPING`
- L101 _public enumerator_ `STREAM_CAPTURING`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
