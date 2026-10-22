# Runtime / IOSAudio

- module root: `Source/Runtime/IOS/IOSAudio`
- headers: 1; symbols: 87
- symbol kinds: class=3, delegate=1, enum=1, enumerator=3, function=6, macro=3, member=29, prototype=41
- PrivateDependencyModuleNames: AudioMixer, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/IOS/IOSAudio/Public/IOSAudioDevice.h` (Public)


#### enum `ESoundFormat`  
`enum ESoundFormat`  
_L39-44_
- L41 _public enumerator_ `SoundFormat_Invalid`
- L42 _public enumerator_ `SoundFormat_LPCM`
- L43 _public enumerator_ `SoundFormat_ADPCM`

#### class `FIOSAudioSoundBuffer`  
`class FIOSAudioSoundBuffer : public FSoundBuffer`  
_L49-101_
- inherits: `FSoundBuffer`
- desc: IOSAudio implementation of FSoundBuffer, containing the wave data and format information.
- L52 _public prototype_ `FIOSAudioSoundBuffer(FIOSAudioDevice* InAudioDevice, USoundWave* InWave, bool InStreaming, bool InProcedural);`
- L53 _public prototype_ `virtual ~FIOSAudioSoundBuffer(void);`
- L62 _public prototype_ `static FIOSAudioSoundBuffer* Init(FIOSAudioDevice* IOSAudioDevice, USoundWave* InWave);` — Static function used to create a buffer. @param InWave USoundWave to use as template and wave source @param AudioDevice audio device to attach created buffer to @return FIOSAudioSoundBuffer pointer if buffer creation succeeded, NULL otherwise
- L69 _public prototype_ `virtual int32 GetSize(void) override;` — Returns the size of this buffer in bytes. @return Size in bytes
- L72 _public prototype_ `virtual int32 GetCurrentChunkIndex() const override;` — These are used by the streaming engine to manage loading/unloading of chunks
- L73 _public prototype_ `virtual int32 GetCurrentChunkOffset() const override;`
- L78 _public prototype_ `virtual bool ReadCompressedInfo(USoundWave* SoundWave) override;` — Read the compressed info (i.e. parse header and open up a file handle) from the given sound wave.
- L87 _public prototype_ `virtual bool ReadCompressedData( uint8* Destination, int32 NumFramesToDecode, bool bLooping ) override;` — Decompresses a chunk of compressed audio to the destination memory @param Destination		Memory to decompress to @param bLooping			Whether to loop the sound seamlessly, or pad with zeroes @return					Whether the sound looped or not
- L89 _public prototype_ `bool ReleaseCurrentChunk();`
- L91 _public member_ `int32 RenderCallbackBufferSize;`
- L92 _public member_ `int32 SampleRate;`
- L93 _public member_ `int32 SoundFormat;`
- L94 _public member_ `int16* SampleData;`
- L95 _public member_ `uint32 BufferSize;`
- L98 _public member_ `ICompressedAudioInfo* DecompressionState;` — Wrapper to assist in the bookkeeping of uncompressed data when streaming
- L99 _public member_ `bool bStreaming;`
- L100 _public member_ `bool bIsProcedural;`

#### class `FIOSAudioSoundSource`  
`class FIOSAudioSoundSource : public FSoundSource`  
_L106-188_
- inherits: `FSoundSource`
- desc: IOSAudio implementation of FSoundSource, the interface used to play, stop and update sources
- L114 _public prototype_ `FIOSAudioSoundSource(FIOSAudioDevice* InAudioDevice, uint32 InBusNumber);` — Constructor @param	InAudioDevice	audio device this source is attached to
- L119 _public prototype_ `~FIOSAudioSoundSource(void);` — Destructor
- L127 _public prototype_ `virtual bool Init(FWaveInstance* WaveInstance) override;` — Initializes a source with a given wave instance and prepares it for playback. @param	WaveInstance	wave instance being primed for playback @return	true			if initialization was successful, false otherwise
- L133 _public prototype_ `virtual void Update(void) override;` — Updates the source specific parameter like e.g. volume and pitch based on the associated wave instance.
- L136 _public prototype_ `virtual void Play(void) override;` — Plays the current wave instance.
- L139 _public prototype_ `virtual void Stop(void) override;` — Stops the current wave instance and detaches it from the source.
- L142 _public prototype_ `virtual void Pause(void) override;` — Pauses playback of current wave instance.
- L150 _public prototype_ `virtual bool IsFinished(void) override;` — Queries the status of the currently associated wave instance. @return	true if the wave instance/ source has finished playback and false if it is currently playing or paused.
- L153 _public prototype_ `AudioUnitElement GetAudioUnitElement(int32 Channel);` — Calculates the audio unit element of the input channel relative to the base bus number
- L155 _public member_ `TArray<Audio::FOnePoleLPF> LowpassFilterBank;`
- L156 _public member_ `TArray<Audio::FParam> LPFParamBank;`
- L158 _public member_ `int32 SampleRate;`
- L161 _public member_ `float SourceLPFFrequency;` — Cached version of Source->LPFFrequency.
- L164 _protected prototype_ `bool AttachToAUGraph();`
- L165 _protected prototype_ `bool DetachFromAUGraph();`
- L167 _protected member_ `FIOSAudioDevice* IOSAudioDevice;`
- L171 _protected member_ `FIOSAudioSoundBuffer* IOSBuffer;` — Do not shadow the declaration of Buffer in the parent class since that member gets used by the streaming engine
- L172 _protected member_ `uint32 BusNumber;`
- L174 _protected member_ `int32 CallbackLock;`
- L176 _protected member_ `bool bChannel0Finished;`
- L177 _protected member_ `bool bAllChannelsFinished;`
- L181 _private prototype_ `static OSStatus IOSAudioRenderCallback(void *InRefCon, AudioUnitRenderActionFlags *IOActionFlags, const AudioTimeStamp *InTimeStamp, UInt32 InBusNumber, UInt32 InNumberFrames, AudioBufferList *IOData);`
- L185 _private prototype_ `void CleanupAudioBuffer();`

#### class `FIOSAudioDevice`  
`class FIOSAudioDevice : public FAudioDevice`  
_L193-263_
- inherits: `FAudioDevice`
- desc: IOSAudio implementation of an Unreal audio device.
- L196 _public prototype_ `FIOSAudioDevice();`
- L197 _public function_ `virtual ~FIOSAudioDevice()`
- L199 _public function_ `AUGraph GetAudioUnitGraph() const`
- L200 _public function_ `AUNode GetMixerNode() const`
- L201 _public function_ `AudioUnit GetMixerUnit() const`
- L202 _public function_ `AudioUnit GetOutputUnit() const`
- L205 _public prototype_ `virtual void ResumeContext();` — Thread context management
- L206 _public prototype_ `virtual void SuspendContext();`
- L208 _public prototype_ `virtual bool Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog ) override;`
- L210 _public prototype_ `virtual void UpdateDeviceDeltaTime() override;`
- L212 _public prototype_ `static void IncrementSuspendCounter();`
- L213 _public prototype_ `static void DecrementSuspendCounter();`
- L217 _protected prototype_ `virtual bool InitializeHardware() override;` — Starts up any platform specific hardware/APIs
- L220 _protected prototype_ `virtual void TeardownHardware() override;` — Shuts down any platform specific hardware/APIs
- L223 _protected prototype_ `virtual void UpdateHardware() override;` — Lets the platform any tick actions
- L226 _protected prototype_ `virtual FAudioEffectsManager* CreateEffectsManager() override;` — Creates a new platform specific sound source
- L229 _protected prototype_ `virtual FSoundSource* CreateSoundSource() override;` — Creates a new platform specific sound source
- L232 _protected prototype_ `void GetHardwareSampleRate(double& OutSampleRate);` — Audio Session management
- L233 _protected prototype_ `bool SetHardwareSampleRate(const double& InSampleRate);`
- L234 _protected prototype_ `bool SetAudioSessionActive(bool bActive);`
- L237 _protected prototype_ `virtual bool IsExernalBackgroundSoundActive() override;` — Check if any background music or sound is playing through the audio device
- L240 _protected prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;` — Retrieves the platform settings
- L245 _private function_ `virtual bool HasCompressedAudioInfoClass(USoundWave* SoundWave) override` — Used to support adpcm streaming
- L247 _private prototype_ `void HandleError(const TCHAR* InLogOutput, bool bTeardown = false);`
- L249 _private member_ `AudioStreamBasicDescription MixerFormat;`
- L250 _private member_ `AUGraph AudioUnitGraph;`
- L251 _private member_ `AUNode OutputNode;`
- L252 _private member_ `AudioUnit OutputUnit;`
- L253 _private member_ `AUNode MixerNode;`
- L254 _private member_ `AudioUnit MixerUnit;`
- L255 _private member_ `FVector PlayerLocation;`
- L256 _private member_ `FVector PlayerFacing;`
- L257 _private member_ `FVector PlayerUp;`
- L258 _private member_ `FVector PlayerRight;`
- L259 _private member_ `int32 NextBusNumber;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define AudioSampleType SInt16`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSAudio, Log, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSAudio, Log, All);`
- L31 _macro_ `#define CHANNELS_PER_BUS 2`
- L32 _macro_ `#define AudioCallbackFrameSize (8 * 1024) // This needs to be known ahead of time to allocate appropriate buffers`
