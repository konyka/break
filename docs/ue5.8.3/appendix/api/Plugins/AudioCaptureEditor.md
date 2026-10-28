# Plugins / AudioCaptureEditor

- module root: `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor`
- headers: 5; symbols: 101
- symbol kinds: class=4, delegate=1, enum=1, enumerator=4, function=3, member=42, namespace=2, prototype=38, struct=6
- PrivateDependencyModuleNames: AudioCapture, AudioCaptureCore, AudioCaptureRtAudio, AudioCaptureWasapi, AudioEditor, Core, CoreUObject, EditorFramework, Engine, UnrealEd

### `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor/Private/AudioCaptureEditor.h` (Private)


#### class `Audio::FAudioCaptureEditor`  
`class FAudioCaptureEditor : public IAudioCaptureEditor`  
_L12-34_
- inherits: `IAudioCaptureEditor`
- L16 _public prototype_ `virtual ~FAudioCaptureEditor() = default;`
- L19 _public prototype_ `virtual bool IsReadyToRecord() override;`
- L20 _public prototype_ `virtual bool IsRecording() override;`
- L21 _public prototype_ `virtual bool IsStopped() override;`
- L22 _public prototype_ `virtual void Start(const FTakeRecorderAudioSettings& InSettings) override;`
- L23 _public prototype_ `virtual void Stop() override;`
- L24 _public prototype_ `virtual TObjectPtr<USoundWave> GetRecordedSoundWave(const FTakeRecorderAudioSourceSettings& InSourceSettings) override;`
- L25 _public prototype_ `virtual bool GetCaptureDeviceInfo(FTakeRecorderAudioDeviceInfo& OutInfo, int32 InDeviceIndex) override;`
- L26 _public prototype_ `virtual bool GetCaptureDevicesAvailable(TArray<FTakeRecorderAudioDeviceInfo>& OutDevices) override;`
- L31 _private prototype_ `void CopyDeviceInfo(const Audio::FCaptureDeviceInfo& InDeviceInfo, FTakeRecorderAudioDeviceInfo& OutDeviceInfo);`
- L33 _private member_ `Audio::FAudioRecordingManager AudioRecordingManager;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor/Private/AudioRecordingManager.h` (Private)


#### struct `Audio::FRecordingSettings`  
`struct FRecordingSettings`  
_L19-32_
- desc: Settings used for starting a recording with the recording manager
- L22 _public member_ `FString AudioCaptureDeviceId;` — The audio device to use for capturing
- L25 _public member_ `int32 AudioInputBufferSize = 1024;` — The desired buffer size in samples.
- L28 _public member_ `float RecordingDuration = -1.0f;` — The length of the recording. Set to 0.0 or less for unbounded recording duration.
- L31 _public member_ `int32 NumRecordChannels = 0;` — Number of channels to record

#### struct `Audio::FRecordingManagerSourceSettings`  
`struct FRecordingManagerSourceSettings`  
_L35-54_
- desc: Settings used for individual audio input sources
- L38 _public member_ `FDirectoryPath Directory;` — The place to put the audio file recording
- L41 _public member_ `FString AssetName;` — The name of the asset you want to record
- L44 _public member_ `float GainDb = 0.0f;` — The output gain of the recording. Allows you to boost the amplitude of your recording.
- L47 _public member_ `int32 InputChannelNumber = -1;` — The channel number of the selected audio device to use for recording.
- L50 _public member_ `FTimecode StartTimecode;` — The timecode locations for this recording
- L53 _public member_ `FFrameRate VideoFrameRate;` — The video framerate used during this recording

#### class `Audio::FAudioRecordingManager`  
`class FAudioRecordingManager`  
_L60-175_
- desc: FAudioRecordingManager Singleton Mic Recording Manager -- generates recordings, stores the recorded data and plays them back
- L64 _public prototype_ `FAudioRecordingManager();`
- L66 _public prototype_ `~FAudioRecordingManager();`
- L69 _public function_ `bool IsReadyToRecord()` — Returns true if this object is in the PreRecord state indicating it is ready to record
- L72 _public function_ `bool IsRecording()` — Returns true if this object is in the Recording state indicating it is currently recording
- L75 _public function_ `bool IsStopped()` — Returns true if this object is in the Stopped state indicating it has finished recording
- L79 _public prototype_ `void StartRecording(const FRecordingSettings& Settings);` — Starts a new recording with the given name and optional duration. If set to -1.0f, a duration won't be used and the recording length will be determined by StopRecording().
- L82 _public prototype_ `void StopRecording();` — Stops recording if the recording manager is recording. If not recording but has recorded data (due to set duration), it will just return the generated USoundWave.
- L85 _public prototype_ `int32 OnAudioCapture(const void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow);` — Called by RtAudio when a new audio buffer is ready to be supplied.
- L87 _public prototype_ `TObjectPtr<USoundWave> GetRecordedSoundWave(const FRecordingManagerSourceSettings& InSourceSettings);`
- L90 _public prototype_ `bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 InDeviceIndex = INDEX_NONE);` — Returns the audio capture device information at the given index.
- L93 _public prototype_ `bool GetCaptureDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices);` — Returns the total amount of audio devices.
- L107 _private prototype_ `void ProcessRecordedData(const FRecordingManagerSourceSettings& InSourceSettings);` — Called after recording to handle processing of recorded data (SRC, de-interleaving, apply gain, etc.)
- L110 _private prototype_ `void DeinterleaveRecordedData();` — Deinterleave recorded data into discreet channels
- L113 _private prototype_ `void ApplyGain(const FRecordingManagerSourceSettings& InSourceSettings, const int32 InNumFrames);` — Applies the user supplied gain parameter if neccessary to a single channel of audio
- L116 _private prototype_ `TObjectPtr<USoundWave> CreateSoundWaveAsset(const FRecordingManagerSourceSettings& InSourceSettings);` — Creates a wave asset for a single channel of audio data
- L119 _private prototype_ `bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32& OutDeviceIndex, FString InDeviceId);` — Returns the device info and index for a given device id
- L122 _private prototype_ `FSoundWaveTimecodeInfo GetTimecodeInfo(const FRecordingManagerSourceSettings& InSourceSettings);` — Returns the timecode info for this recording
- L125 _private member_ `const int32 WAVE_FILE_SAMPLERATE = 44100;` — The default mic sample rate
- L128 _private member_ `std::atomic<EAudioRecorderState> RecorderState;` — Current state for the state machine
- L131 _private member_ `FRecordingSettings Settings;` — Copy of the input recording settings
- L134 _private member_ `FAudioCapture AudioCapture;` — FAudioCapture object -- used to interact with low-level audio device.
- L137 _private member_ `TArray<int16> CurrentRecordedPCMData;` — The data which is currently being recorded to, if the manager is actively recording. This is not safe to access while recording.
- L140 _private member_ `TArray<int16> ConvertedPCMData;` — Buffer to store sample rate converted PCM data
- L147 _private member_ `TArray<FDeinterleavedAudio> DeinterleavedAudio;`
- L150 _private member_ `TArray<uint8> RawWaveData;` — Reusable raw wave data buffer to generate .wav file formats
- L153 _private member_ `int32 NumRecordedSamples;` — The number of frames that have been recorded
- L156 _private member_ `int32 NumFramesToRecord;` — The number of frames to record if recording a set duration
- L159 _private member_ `int32 RecordingBlockSize;` — Recording block size (number of frames per callback block)
- L162 _private member_ `float RecordingSampleRate;` — The sample rate used in the recording
- L165 _private member_ `int32 NumInputChannels;` — Num input channels
- L168 _private member_ `int32 NumOverflowsDetected;` — Number of overflows detected while recording
- L171 _private member_ `TArray<int16>* PCMDataToSerialize = nullptr;` — Pointer to the recorded PCM data after any sample rate conversion has been applied
- L174 _private member_ `TArray<TObjectPtr<USoundWave>> RecordedSoundWaves;` — Array of USoundWaves created during this record pass

#### enum `Audio::FAudioRecordingManager::EAudioRecorderState`  
`enum class EAudioRecorderState : uint8`  
_L98-104_
- desc: States used by AudioRecordingManager state machine
- L100 _public enumerator_ `PreRecord`
- L101 _public enumerator_ `Recording`
- L102 _public enumerator_ `Stopped`
- L103 _public enumerator_ `ErrorDetected`

#### struct `Audio::FAudioRecordingManager::FDeinterleavedAudio`  
`struct FDeinterleavedAudio`  
_L143-146_
- desc: Buffers to de-interleave recorded audio
- L145 _public member_ `TArray<int16> PCMData;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMicManager, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMicManager, Log, All);`
- L16 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor/Public/AudioCaptureEditorTypes.h` (Public)


#### struct `FTakeRecorderAudioDeviceInfo`  
`struct FTakeRecorderAudioDeviceInfo`  
_L10-20_
- desc: Sequencer version of the audio device info.
- L13 _public member_ `FString DeviceName;` — The name for this audio device
- L15 _public member_ `FString DeviceId;` — The unique identifier for this device
- L17 _public member_ `int32 InputChannels = 0;` — The number of input channels this device is capable of capturing
- L19 _public member_ `int32 PreferredSampleRate = 0;` — The preferred sample rate for this device

#### struct `FTakeRecorderAudioSettings`  
`struct FTakeRecorderAudioSettings`  
_L23-36_
- desc: Take Recorder version of the audio recording settings.
- L26 _public member_ `FString AudioCaptureDeviceId;` — Audio device to use for capture.
- L29 _public member_ `int32 AudioInputBufferSize = 1024;` — The desired buffer size in samples.
- L32 _public member_ `float RecordingDuration = -1.0f;` — Optional audio recording duration in seconds.
- L35 _public member_ `int32 NumRecordChannels = 0;` — Number of channels to record

#### struct `FTakeRecorderAudioSourceSettings`  
`struct FTakeRecorderAudioSourceSettings`  
_L39-58_
- desc: Take Recorder version of the audio source settings.
- L42 _public member_ `FDirectoryPath Directory;` — Directory to create the asset within (empty for transient package)
- L45 _public member_ `FString AssetName;` — Name of the asset.
- L48 _public member_ `float GainDb = 0.0f;` — Gain in decibels of the output asset.
- L51 _public member_ `int32 InputChannelNumber = -1;` — The channel number of the selected audio device to use for recording.
- L54 _public member_ `FTimecode StartTimecode;` — The timecode position for this recording
- L57 _public member_ `FFrameRate VideoFrameRate;` — The video frame rate used during this recording

### `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor/Public/IAudioCaptureEditor.h` (Public)


#### class `IAudioCaptureEditor`  
`class IAudioCaptureEditor`  
_L11-41_
- L16 _public prototype_ `virtual ~IAudioCaptureEditor() = default;` — Virtual destructor
- L19 _public prototype_ `virtual bool IsReadyToRecord() = 0;` — Returns true if this object is in the PreRecord state indicating it is ready to record
- L22 _public prototype_ `virtual bool IsRecording() = 0;` — Returns true if this object is in the Recording state indicating it is currently recording
- L25 _public prototype_ `virtual bool IsStopped() = 0;` — Returns true if this object is in the Stopped state indicating it has finished recording
- L28 _public prototype_ `virtual void Start(const FTakeRecorderAudioSettings& InSettings) = 0;` — Start recording audio data
- L31 _public prototype_ `virtual void Stop() = 0;` — Stop recording audio data
- L34 _public prototype_ `virtual TObjectPtr<USoundWave> GetRecordedSoundWave(const FTakeRecorderAudioSourceSettings& InSourceSettings) = 0;` — Returns previously recorded audio data for single channel as a USoundWave
- L37 _public prototype_ `virtual bool GetCaptureDeviceInfo(FTakeRecorderAudioDeviceInfo& OutInfo, int32 DeviceIndex = INDEX_NONE) = 0;` — Returns the audio capture device information at the given index
- L40 _public prototype_ `virtual bool GetCaptureDevicesAvailable(TArray<FTakeRecorderAudioDeviceInfo>& OutDevices) = 0;` — Returns the total amount of audio devices

### `Plugins/Runtime/AudioCapture/Source/AudioCaptureEditor/Public/IAudioCaptureEditorModule.h` (Public)


#### class `IAudioCaptureEditorModule`  
`class IAudioCaptureEditorModule : public IModuleInterface`  
_L13-42_
- inherits: `IModuleInterface`
- L22 _public prototype_ `virtual FDelegateHandle RegisterAudioRecorder(const TFunction<TUniquePtr<IAudioCaptureEditor>()>& FactoryFunction) = 0;` — Register a function that will return a new audio capturer for the specified parameters @param	FactoryFunction		Function used to generate a new audio recorder @return A handle to be passed to UnregisterAudioRecorder to unregister the recorder
- L28 _public prototype_ `virtual void UnregisterAudioRecorder(FDelegateHandle RegisteredHandle) = 0;` — Unregister a previously registered audio recorder factory function @param	RegisteredHandle	The handle returned from RegisterAudioRecorder
- L34 _public prototype_ `virtual bool HasAudioRecorder() const = 0;` — Check whether we have an audio recorder registered or not @return true if we have an audio recorder registered, false otherwise
- L41 _public prototype_ `virtual TUniquePtr<IAudioCaptureEditor> CreateAudioRecorder() const = 0;` — Attempt to create an audio recorder @param	Settings	Settings for the audio recorder @return A valid ptr to an audio recorder or null
