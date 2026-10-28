# Runtime / Voice

- module root: `Source/Runtime/Online/Voice`
- headers: 9; symbols: 185
- symbol kinds: class=9, delegate=13, enum=1, enumerator=7, function=19, macro=7, member=45, namespace=1, prototype=81, struct=1, typedef=1
- PrivateDependencyModuleNames: AudioMixer, Core, SignalProcessing
- PublicDependencyModuleNames: Engine
- PublicIncludePathModuleNames: AndroidPermission, HeadMountedDisplay

### `Source/Runtime/Online/Voice/Private/VoiceCodecOpus.h` (Private)


#### class `FVoiceEncoderOpus`  
`class FVoiceEncoderOpus : public IVoiceEncoder`  
_L18-57_
- inherits: `IVoiceEncoder`
- desc: Opus voice compression
- L22 _public prototype_ `FVoiceEncoderOpus();`
- L23 _public prototype_ `~FVoiceEncoderOpus();`
- L26 _public prototype_ `virtual bool Init(int32 SampleRate, int32 NumChannels, EAudioEncodeHint EncodeHint) override;` — IVoiceEncoder
- L27 _public prototype_ `virtual int32 Encode(const uint8* RawPCMData, uint32 RawDataSize, uint8* OutCompressedData, uint32& OutCompressedDataSize) override;`
- L28 _public prototype_ `virtual bool SetBitrate(int32 InBitRate) override;`
- L29 _public prototype_ `virtual bool SetVBR(bool bEnableVBR) override;`
- L30 _public prototype_ `virtual bool SetComplexity(int32 InComplexity) override;`
- L31 _public prototype_ `virtual void Reset() override;`
- L32 _public prototype_ `virtual void Destroy() override;`
- L33 _public prototype_ `virtual void DumpState() const override;`
- L38 _private member_ `int32 SampleRate;` — Sample rate encoding (supports 8000, 12000, 16000, 24000, 480000)
- L40 _private member_ `int32 NumChannels;` — Encoded channel count (supports 1,2)
- L48 _private member_ `int32 FrameSize;` — Number of samples encoded in a time slice "frame" (must match decoder) One frame defined as (2.5, 5, 10, 20, 40 or 60 ms) of audio data Voice encoding lower bound is 10ms (audio goes to 2.5ms). Voice encoding upper bound is 60ms (audio goes to 20ms). at 48 kHz the permitted values are 120 (2.5ms), 240 (5ms), 480 (10ms), 960 (20ms), 1920 (40ms), and 2880 (60ms)
- L50 _private member_ `struct OpusEncoder* Encoder;` — Opus encoder stateful data
- L52 _private member_ `uint32 Entropy[NUM_ENTROPY_VALUES];` — Last values for error checking with the decoder
- L54 _private member_ `uint32 LastEntropyIdx;` — Last recorded entropy index
- L56 _private member_ `uint8 Generation;` — Last value set in the call to Encode()

#### class `FVoiceDecoderOpus`  
`class FVoiceDecoderOpus : public IVoiceDecoder`  
_L62-95_
- inherits: `IVoiceDecoder`
- desc: Opus voice decompression
- L66 _public prototype_ `FVoiceDecoderOpus();`
- L67 _public prototype_ `~FVoiceDecoderOpus();`
- L70 _public prototype_ `virtual bool Init(int32 SampleRate, int32 NumChannels) override;` — IVoiceDecoder
- L71 _public prototype_ `virtual void Decode(const uint8* CompressedData, uint32 CompressedDataSize, uint8* OutRawPCMData, uint32& OutRawDataSize) override;`
- L72 _public prototype_ `virtual void Reset() override;`
- L73 _public prototype_ `virtual void Destroy() override;`
- L74 _public prototype_ `virtual void DumpState() const override;`
- L79 _private member_ `int32 SampleRate;` — Sample rate to decode into, regardless of encoding (supports 8000, 12000, 16000, 24000, 480000)
- L81 _private member_ `int32 NumChannels;` — Decoded channel count (supports 1,2)
- L86 _private member_ `int32 FrameSize;` — Number of samples encoded in a time slice (must match encoder) at 48 kHz the permitted values are 120, 240, 480, 960, 1920, and 2880
- L88 _private member_ `struct OpusDecoder* Decoder;` — Opus decoder stateful data
- L90 _private member_ `uint32 Entropy[NUM_ENTROPY_VALUES];` — Last values for error checking with the encoder
- L92 _private member_ `uint32 LastEntropyIdx;` — Last recorded entropy index
- L94 _private member_ `uint8 LastGeneration;` — Generation value received from the last incoming packet

#### Free symbols / members of external scopes

- L13 _macro_ `#define NUM_ENTROPY_VALUES 5` — Number of entropy values to store in the encoder/decoder (similar to a CRC)

### `Source/Runtime/Online/Voice/Private/VoiceDelayBuffer.h` (Private)


#### class `FVoiceDelayBuffer`  
`template<class SampleType> class FVoiceDelayBuffer`  
_L12-111_
- desc: /
- L15 _private member_ `TArray<SampleType> InternalBuffer;`
- L17 _private member_ `int32 WriteIndex;`
- L18 _private member_ `int32 ReadIndex;`
- L22 _public function_ `void Init(int32 MaxLength)` — Allocates resources for a maximum buffer of MaxLength samples.
- L31 _public function_ `void SetDelay(int32 NumSamples)` — Sets delay between read and write in samples.
- L45 _public function_ `int32 GetBufferCount()` — Gets the amount of samples on the buffer.
- L58 _public function_ `void PushSample(const SampleType& InSample)` — Pushes sample onto the buffer. Decrements delay between read and write by one sample.
- L64 _public function_ `void PushFrame(const SampleType* InFrame, int32 NumChannels)`
- L73 _public function_ `SampleType PopSample()` — pop sample off of the buffer. Increments delay between read and write by one sample.
- L80 _public function_ `void ProcessSample(const SampleType& InSample, SampleType& OutSample)` — Pushes InSample onto the buffer and pops OutSample.
- L87 _public function_ `int32 PopBufferedAudio(SampleType* OutBuffer, int32 MaxNumSamples)` — pop as much audio as possible onto OutBuffer. returns the number of samples copied.

### `Source/Runtime/Online/Voice/Private/VoicePrivate.h` (Private)


#### Free symbols / members of external scopes

- L22 _macro_ `#define ANDROIDVOICE_SUPPORTED_PLATFORMS (PLATFORM_ANDROID)`
- L23 _macro_ `#define PLATFORM_SUPPORTS_VOICE_CAPTURE (PLATFORM_WINDOWS || PLATFORM_MAC || ANDROIDVOICE_SUPPORTED_PLATFORMS || (PLATFORM_UNIX && VOICE_MODULE_WITH_CAPTURE))`

### `Source/Runtime/Online/Voice/Private/Windows/VoiceCaptureWindows.h` (Private)


#### class `FVoiceCaptureDeviceWindows`  
`class FVoiceCaptureDeviceWindows`  
_L23-102_
- desc: DirectSound wrapper for initialization / shutdown
- L28 _private member_ `static FVoiceCaptureDeviceWindows* Singleton;` — One instance of the direct sound API
- L30 _private member_ `TArray<IVoiceCapture*> ActiveVoiceCaptures;` — All outstanding voice capture objects
- L32 _private member_ `bool bInitialized;` — Is DirectSound setup correctly
- L35 _private prototype_ `bool Init();` — Initialize DirectSound and the voice capture device
- L37 _private prototype_ `void Shutdown();` — Shutdown DirectSound and the voice capture device
- L50 _private prototype_ `static void Destroy();` — Destroy the device singleton
- L56 _private prototype_ `void FreeVoiceCaptureObject(IVoiceCapture* VoiceCaptureObj);` — Free a voice capture object created by CreateVoiceCaptureObject() @param VoiceCaptureObj voice capture object to free
- L71 _public member_ `LPDIRECTSOUND8 DirectSound;` — DirectSound8 Interface
- L74 _public member_ `FString HMDAudioInputDevice;` — HMD audio input device to use
- L76 _public member_ `FCaptureDeviceInfo DefaultVoiceCaptureDevice;` — GUID of selected voice capture device
- L79 _public member_ `TMap<FString, FCaptureDeviceInfo> Devices;` — All available capture devices
- L82 _public prototype_ `FVoiceCaptureDeviceWindows();` — Constructors
- L83 _public prototype_ `~FVoiceCaptureDeviceWindows();`
- L94 _public prototype_ `FVoiceCaptureWindows* CreateVoiceCaptureObject(const FString& DeviceName, int32 SampleRate, int32 NumChannels);` — Create a single voice capture buffer @param DeviceName name of device to capture with, empty for default device @param SampleRate valid sample rate to capture audio data (8khz - 48khz) @param NumChannel number of audio channels (1 - mono, 2 - stereo) @return class capable of recording voice on a given device
- L101 _public prototype_ `static FVoiceCaptureDeviceWindows* Get();` — Singleton accessor @return access to the voice capture device

#### struct `FVoiceCaptureDeviceWindows::FCaptureDeviceInfo`  
`struct FCaptureDeviceInfo`  
_L60-68_
- L63 _public member_ `FString DeviceName;` — Enumerated capture device name
- L65 _public member_ `GUID DeviceId;` — Enumerated capture device guid
- L67 _public member_ `bool bIsDefault;` — If this is the default device.

#### class `FVoiceCaptureWindows`  
`class FVoiceCaptureWindows : public IVoiceCapture, public FTSTickerObjectBase`  
_L107-213_
- inherits: `IVoiceCapture,FTSTickerObjectBase`
- desc: Windows implementation of voice capture using DirectSound
- L111 _public prototype_ `FVoiceCaptureWindows();`
- L112 _public prototype_ `~FVoiceCaptureWindows();`
- L115 _public prototype_ `virtual bool Init(const FString& DeviceName, int32 SampleRate, int32 NumChannels) override;` — IVoiceCapture
- L116 _public prototype_ `virtual void Shutdown() override;`
- L117 _public prototype_ `virtual bool Start() override;`
- L118 _public prototype_ `virtual void Stop() override;`
- L119 _public prototype_ `virtual bool ChangeDevice(const FString& DeviceName, int32 SampleRate, int32 NumChannels) override;`
- L120 _public prototype_ `virtual bool IsCapturing() override;`
- L121 _public prototype_ `virtual EVoiceCaptureState::Type GetCaptureState(uint32& OutAvailableVoiceData) const override;`
- L122 _public prototype_ `virtual EVoiceCaptureState::Type GetVoiceData(uint8* OutVoiceBuffer, uint32 InVoiceBufferSize, uint32& OutAvailableVoiceData) override;`
- L123 _public prototype_ `virtual EVoiceCaptureState::Type GetVoiceData(uint8* OutVoiceBuffer, uint32 InVoiceBufferSize, uint32& OutAvailableVoiceData, uint64& OutSampleCounter) override;`
- L124 _public prototype_ `virtual int32 GetBufferSize() const override;`
- L125 _public prototype_ `virtual void DumpState() const override;`
- L126 _public prototype_ `virtual float GetCurrentAmplitude() const override;`
- L129 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L134 _private member_ `FVoiceCaptureWindowsVars* CV;` — All windows related variables to hide windows includes
- L136 _private member_ `double LastCaptureTime;` — Last time data was captured
- L138 _private member_ `EVoiceCaptureState::Type VoiceCaptureState;` — State of capture device
- L140 _private member_ `TArray<uint8> UncompressedAudioBuffer;` — Uncompressed audio buffer
- L142 _private member_ `uint64 SampleCounter;` — Number of samples of audio we've returned from the beginning of the capture
- L144 _private member_ `uint64 CachedSampleStart;` — This value is used when we've detected a vocal onset in the middle of a buffer we are not sending audio for.
- L146 _private member_ `uint64 CurrentSampleStart;` — This value is used to denote the index of the first sample of the current packet of audio data we are sending.
- L149 _private member_ `bool bSampleStartCached;` — Boolean flag that is used to denote whether the starting index of a packet has been cached mid-buffer do to a vocal onset.
- L152 _private member_ `int32 NumInputChannels;` — Number of channels.
- L155 _private member_ `Audio::TSampleBuffer<float> ConversionBuffer;` — This is used to convert audio from int16 to float to push to any potential connected patch outputs on IVoiceCapture::MicrophoneOutput
- L161 _private member_ `FVoiceDelayBuffer<int16> LookaheadBuffer;` — This buffer is used so that we can detect when the player is speaking without cutting off what they are saying.
- L166 _private member_ `FVoiceDelayBuffer<int16> ReleaseBuffer;` — This buffer is used in case someone starts speaking again in the middle of a buffer they were otherwise silent in.
- L172 _private member_ `Audio::FInlineEnvelopeFollower MicLevelDetector;` — Envelope following DSP object. Configured using the MicSilenceDetectionConfig namespace in VoiceConfig.h and the CVars defined in VoiceConfig.cpp.
- L176 _private member_ `bool bIsMicActive;` — Whether the microphone level is above the threshold set
- L181 _private member_ `Audio::FLinearEase NoiseGateAttenuator;` — This linear ease is used to add attack fade in and release fadeout to the noise gate.
- L186 _private member_ `bool bWasMicAboveNoiseGateThreshold;` — This bool is used to track when we engage
- L197 _private prototype_ `bool CreateCaptureBuffer(const FString& DeviceName, int32 SampleRate, int32 NumChannels);` — Create the D3D8 capture device @param DeviceName name of device to capture with, empty for default device @param SampleRate valid sample rate to capture audio data (8khz - 48khz) @param NumChannel number of audio channels (1 - mono, 2 - stereo) @return true if successful, false otherwise
- L200 _private prototype_ `void FreeCaptureBuffer();` — Clear the capture buffer and release all resources
- L206 _private prototype_ `void ProcessData();` — Lock the DirectSound audio buffer and copy out the available data based on a notification and the current audio buffer capture cursor
- L212 _private prototype_ `bool CreateNotifications(uint32 BufferSize);` — Create notifications on the voice capture buffer, evenly distributed @param BufferSize size of buffer created

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef struct IDirectSound8 *LPDIRECTSOUND8;`

### `Source/Runtime/Online/Voice/Public/Interfaces/VoiceCapture.h` (Public)


#### enum `EVoiceCaptureState::Type`  
`enum Type`  
_L16-25_
- L18 _public enumerator_ `UnInitialized`
- L19 _public enumerator_ `NotCapturing`
- L20 _public enumerator_ `Ok`
- L21 _public enumerator_ `NoData`
- L22 _public enumerator_ `Stopping`
- L23 _public enumerator_ `BufferTooSmall`
- L24 _public enumerator_ `Error`

#### class `IVoiceCapture`  
`class IVoiceCapture : public TSharedFromThis<IVoiceCapture>`  
_L68-175_
- inherits: `TSharedFromThis<IVoiceCapture>`
- desc: Interface for capturing voice data on any platform
- L73 _protected function_ `IVoiceCapture()`
- L78 _protected member_ `Audio::FPatchSplitter MicrophoneOutput;` — Optional patch point for MicrophoneOutput.
- L82 _public prototype_ `virtual ~IVoiceCapture() = default;`
- L93 _public prototype_ `virtual bool Init(const FString& DeviceName, int32 SampleRate, int32 NumChannels) = 0;` — Initialize the voice capture object @param DeviceName name of device to capture audio data with, empty for default device @param SampleRate sampling rate of voice capture @param NumChannels number of channels to capture @return true if successful, false otherwise
- L98 _public prototype_ `virtual void Shutdown() = 0;` — Shutdown the voice capture object
- L105 _public prototype_ `virtual bool Start() = 0;` — Start capturing voice @return true if successfully started, false otherwise
- L110 _public prototype_ `virtual void Stop() = 0;` — Stop capturing voice
- L121 _public prototype_ `virtual bool ChangeDevice(const FString& DeviceName, int32 SampleRate, int32 NumChannels) = 0;` — Change the associated capture device @param DeviceName name of device to capture audio data with, empty for default device @param SampleRate sampling rate of voice capture @param NumChannels number of channels to capture @return true if change was successful, false otherwise
- L128 _public prototype_ `virtual bool IsCapturing() = 0;` — Is the voice capture object actively capturing @return true if voice is being captured, false otherwise
- L137 _public prototype_ `virtual EVoiceCaptureState::Type GetCaptureState(uint32& OutAvailableVoiceData) const = 0;` — Return the state of the voice data and its availability @param OutAvailableVoiceData size, in bytes, of available voice data @return state of the voice capture buffer
- L149 _public function_ `virtual EVoiceCaptureState::Type GetVoiceData(uint8* OutVoiceBuffer, uint32 InVoiceBufferSize, uint32& OutAvailableVoiceData)` — Fill a buffer with all available voice data @param OutVoiceBuffer allocated buffer to fill with voice data @param InVoiceBufferSize size, in bytes, of allocated buffer @param OutAvailableVoiceData size, in bytes, of data placed in the OutVoiceBuffer @param OutSampleCounter optional parameter for beginning sample of this buffer. @return state of the voice capture buffer
- L150 _public function_ `virtual EVoiceCaptureState::Type GetVoiceData(uint8* OutVoiceBuffer, uint32 InVoiceBufferSize, uint32& OutAvailableVoiceData, uint64& OutSampleCounter)`
- L155 _public prototype_ `virtual int32 GetBufferSize() const = 0;` — @return number of bytes currently allocated in the capture buffer
- L158 _public prototype_ `virtual void DumpState() const = 0;` — Dump the state of the voice capture device
- L163 _public function_ `Audio::FPatchOutputStrongPtr GetMicrophoneAudio(int32 MaxExpectedLatencyInSamples, float Gain)` — @returns a new output for this mic's audio.
- L171 _public function_ `virtual float GetCurrentAmplitude() const` — @return the current loudness of the microphone. Returns -1.0 if this function is not supported by the current platform.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EVoiceCaptureState`
- L28 _function_ `inline const TCHAR* ToString(EVoiceCaptureState::Type VoiceCaptureState)` (scope `EVoiceCaptureState`) — @return the stringified version of the enum passed in

### `Source/Runtime/Online/Voice/Public/Interfaces/VoiceCodec.h` (Public)


#### class `IVoiceEncoder`  
`class IVoiceEncoder : public TSharedFromThis<IVoiceEncoder>`  
_L29-104_
- inherits: `TSharedFromThis<IVoiceEncoder>`
- desc: Interface for encoding raw voice for transmission over the wire
- L34 _protected function_ `IVoiceEncoder()`
- L38 _public prototype_ `virtual ~IVoiceEncoder() = default;`
- L49 _public prototype_ `virtual bool Init(int32 SampleRate, int32 NumChannels, EAudioEncodeHint EncodeHint) = 0;` — Initialize the encoder @param SampleRate requested sample rate of the encoding @param NumChannel number of channels in the raw audio stream @param EncodeHint type of audio that will be encoded @return true if initialization was successful, false otherwise
- L61 _public prototype_ `virtual int32 Encode(const uint8* RawPCMData, uint32 RawDataSize, uint8* OutCompressedData, uint32& OutCompressedDataSize) = 0;` — Encode a raw audio stream (expects 16bit PCM audio) @param RawPCMData array of raw PCM data to encode @param RawDataSize amount of raw PCM data in the buffer @param OutCompressedData buffer to contain encoded/compressed audio stream @param OutCompressedDataSize [in/out] amount of buffer used to encode the audio stream @return number of bytes at the end of the stream that wasn't encoded (some interfaces can only encode at a certain frame slice)
- L70 _public prototype_ `virtual bool SetBitrate(int32 InBitRate) = 0;` — Adjust the encoding bitrate @param InBitRate new bitrate value (bits/sec) @return true if successfully changed, false otherwise
- L79 _public prototype_ `virtual bool SetVBR(bool bEnableVBR) = 0;` — Set the encoding to variable bitrate @param bEnableVBR true to use variable bit rate, false to turn it off @return true if successfully changed, false otherwise
- L88 _public prototype_ `virtual bool SetComplexity(int32 InComplexity) = 0;` — Adjust the encoding complexity (platform specific) @param InComplexity new complexity @return true if successfully changed, false otherwise
- L93 _public prototype_ `virtual void Reset() = 0;` — Reset the encoder back to its initial state
- L98 _public prototype_ `virtual void Destroy() = 0;` — Cleanup the encoder
- L103 _public prototype_ `virtual void DumpState() const = 0;` — Output the state of the encoder

#### class `IVoiceDecoder`  
`class IVoiceDecoder : public TSharedFromThis<IVoiceDecoder>`  
_L109-154_
- inherits: `TSharedFromThis<IVoiceDecoder>`
- desc: Interface for decoding voice passed over the wire
- L114 _protected function_ `IVoiceDecoder()`
- L118 _public prototype_ `virtual ~IVoiceDecoder() = default;`
- L128 _public prototype_ `virtual bool Init(int32 SampleRate, int32 NumChannels) = 0;` — Initialize the decoder @param SampleRate requested sample rate of the decoding (may be up sampled depending on the source data) @param NumChannel number of channels in the output decoded stream (mono streams can encode to stereo) @return true if initialization was successful, false otherwise
- L138 _public prototype_ `virtual void Decode(const uint8* CompressedData, uint32 CompressedDataSize, uint8* OutRawPCMData, uint32& OutRawDataSize) = 0;` — Decode an encoded audio stream (outputs 16bit PCM audio) @param CompressedData encoded/compressed audio stream @param CompressedDataSize amount of data in the buffer @param OutRawPCMData buffer to contain the decoded raw PCM data @param OutRawDataSize [in/out] amount of buffer used for the decoded raw PCM data
- L143 _public prototype_ `virtual void Reset() = 0;` — Reset the decoder back to its initial state
- L148 _public prototype_ `virtual void Destroy() = 0;` — Cleanup the decoder
- L153 _public prototype_ `virtual void DumpState() const = 0;` — Output the state of the decoder

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("Voice"), STATGROUP_Voice, STATCAT_Advan` — Stats for voice codec
- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VoiceEncode"), STAT_Voice_Encoding, STATGROU`
- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VoiceDecode"), STAT_Voice_Decoding, STATGROU`
- L14 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Enc_SampleRate"), STAT_Encode_SampleRate, STATG`
- L15 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Enc_NumChannels"), STAT_Encode_NumChannels, STAT`
- L16 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Enc_Bitrate"), STAT_Encode_Bitrate, STATGROU`
- L17 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Enc_CompRatio"), STAT_Encode_CompressionRatio, STATGR`
- L18 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Enc_OutSize"), STAT_Encode_OutSize, STATGROU`
- L19 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Dec_SampleRate"), STAT_Decode_SampleRate, STATG`
- L20 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Dec_NumChannels"), STAT_Decode_NumChannels, STAT`
- L21 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Dec_CompRatio"), STAT_Decode_CompressionRatio, STATGR`
- L22 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Dec_OutSize"), STAT_Decode_OutSize, STATGROU`

### `Source/Runtime/Online/Voice/Public/Voice.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/Voice/Public/VoiceModule.h` (Public)


#### class `FVoiceModule`  
`class FVoiceModule : public IModuleInterface`  
_L34-129_
- inherits: `IModuleInterface`
- desc: Module for Voice capture/compression/decompression implementations
- L46 _public function_ `static inline FVoiceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L56 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L70 _public prototype_ `virtual TSharedPtr<IVoiceCapture> CreateVoiceCapture(const FString& DeviceName, int32 SampleRate = UVOIPStatics::GetVoiceSampleRate(), int32 NumChannels = UVOIPStatics::GetVoiceNumChannels());` — Instantiates a new voice capture object @param DeviceName name of device to capture audio data with, empty for default device @param SampleRate sampling rate of voice capture @param NumChannels number of channels to capture @return new voice capture object, possibly NULL
- L81 _public prototype_ `virtual TSharedPtr<IVoiceEncoder> CreateVoiceEncoder(int32 SampleRate = UVOIPStatics::GetVoiceSampleRate(), int32 NumChannels = UVOIPStatics::GetVoiceNumChannels(), EAudioEncodeHint EncodeHint = UVOIPStatics::GetAudioEncodingHint());` — Instantiates a new voice encoder object @param SampleRate sampling rate of voice capture @param NumChannels number of channels to capture @param EncodeHint hint to describe type of audio quality desired @return new voice encoder object, possibly NULL
- L91 _public prototype_ `virtual TSharedPtr<IVoiceDecoder> CreateVoiceDecoder(int32 SampleRate = UVOIPStatics::GetVoiceSampleRate(), int32 NumChannels = UVOIPStatics::GetVoiceNumChannels());` — Instantiates a new voice decoder object @param SampleRate sampling rate of voice capture @param NumChannels number of channels to capture @return new voice decoder object, possibly NULL
- L98 _public prototype_ `virtual bool DoesPlatformSupportVoiceCapture();` — Checks to see if the current platform supports voice capture. @return True if the current platform support voice capture
- L103 _public function_ `inline bool IsVoiceEnabled() const` — @return true if voice is enabled
- L110 _private prototype_ `IVoiceEncoder* CreateVoiceEncoderObject(int32 SampleRate, int32 NumChannels, EAudioEncodeHint EncodeHint);`
- L111 _private prototype_ `IVoiceDecoder* CreateVoiceDecoderObject(int32 SampleRate, int32 NumChannels);`
- L119 _private prototype_ `virtual void StartupModule() override;` — Called when voice module is loaded Initialize platform specific parts of voice handling
- L125 _private prototype_ `virtual void ShutdownModule() override;` — Called when voice module is unloaded Shutdown platform specific parts of voice handling
- L128 _private member_ `bool bEnabled;` — Is voice interface enabled

#### Free symbols / members of external scopes

- L13 _macro_ `#define DEFAULT_VOICE_SAMPLE_RATE 16000` — Default voice chat sample rate
- L15 _macro_ `#define VOICE_SAMPLE_RATE DEFAULT_VOICE_SAMPLE_RATE` — Deprecated value, use DEFAULT_VOICE_SAMPLE_RATE
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoice, Display, All);` — Logging related to general voice chat flow (muting/registration/etc)
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoiceEncode, Display, All);` — Logging related to encoding of local voice packets
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoiceDecode, Display, All);` — Logging related to decoding of remote voice packets
- L29 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoiceCapture, Warning, All);` — Internal voice capture logging
- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoiceCapture, Warning, All);` — Internal voice capture logging

### `Source/Runtime/Online/Voice/Public/VoicePackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE private`
