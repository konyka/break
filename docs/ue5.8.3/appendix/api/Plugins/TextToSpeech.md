# Plugins / TextToSpeech

- module root: `Plugins/Experimental/TextToSpeech/Source/TextToSpeech`
- headers: 17; symbols: 193
- symbol kinds: class=13, delegate=3, function=19, member=35, prototype=116, struct=2, typedef=5
- PrivateDependencyModuleNames: AudioMixer, AudioPlatformConfiguration, Engine, SignalProcessing
- PublicDependencyModuleNames: Core, CoreUObject
- PublicIncludePathModuleNames: ApplicationCore

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Android/AndroidTextToSpeechFactory.h` (Private)


#### class `FAndroidTextToSpeechFactory`  
`class FAndroidTextToSpeechFactory : public ITextToSpeechFactory`  
_L10-17_
- inherits: `ITextToSpeechFactory`
- desc: The platform default text to speech factory for Android platforms.
- L13 _public prototype_ `FAndroidTextToSpeechFactory() = default;`
- L14 _public prototype_ `virtual ~FAndroidTextToSpeechFactory() = default;`
- L16 _public prototype_ `virtual TSharedRef<FTextToSpeechBase> Create() override;`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef FAndroidTextToSpeechFactory FPlatformTextToSpeechFactory;`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Apple/AppleTextToSpeech.h` (Private)


#### class `FAppleTextToSpeech`  
`class FAppleTextToSpeech : public FTextToSpeechBase`  
_L12-51_
- inherits: `FTextToSpeechBase`
- desc: The text to speech implementation for Mac
- L15 _public prototype_ `FAppleTextToSpeech();`
- L16 _public prototype_ `virtual ~FAppleTextToSpeech();`
- L19 _public prototype_ `virtual void Speak(const FString& InStringToSpeak) override final;` — FGenericTextToSpeech
- L20 _public prototype_ `virtual bool IsSpeaking() const override final;`
- L21 _public prototype_ `virtual void StopSpeaking() override final;`
- L22 _public prototype_ `virtual float GetVolume() const override final;`
- L23 _public prototype_ `virtual void SetVolume(float InVolume) override final;`
- L24 _public prototype_ `virtual float GetRate() const override final;`
- L25 _public prototype_ `virtual void SetRate(float InRate) override final;`
- L26 _public prototype_ `virtual void Mute() override final;`
- L27 _public prototype_ `virtual void Unmute() override final;`
- L29 _protected prototype_ `virtual void OnActivated() override final;`
- L30 _protected prototype_ `virtual void OnDeactivated() override final;`
- L39 _private member_ `bool bIsSpeaking;` — True if the speech synthesizer is currently synthesizing any text, else false. Speech synthesis for Mac is asynchronous, but we make the checking of whether something is speaking synchrnous so as to simplify algorithms that depend on the check. A precise check is not currently necessary.
- L41 _private member_ `float Volume;` — The current volume of the speech synthesizer.
- L43 _private member_ `float Rate;` — The current speech rate of the speech synthesizer
- L45 _private member_ `AVSpeechSynthesizer* SpeechSynthesizer;` — The platform speech synthesizer that converts text to speech
- L50 _private member_ `FSpeechSynthesizerDelegate* SpeechSynthesizerDelegate;` — The delegate for the speech synthesizer. Callbacks indicating speech synthesis playback progress, intruuption and completion are handled by this delegate.

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Apple/AppleTextToSpeechFactory.h` (Private)


#### class `FAppleTextToSpeechFactory`  
`class FAppleTextToSpeechFactory : public ITextToSpeechFactory`  
_L8-17_
- inherits: `ITextToSpeechFactory`
- desc: The platform default text to speech factory for Apple.
- L11 _public prototype_ `FAppleTextToSpeechFactory() = default;`
- L12 _public prototype_ `virtual ~FAppleTextToSpeechFactory() = default;`
- L15 _public prototype_ `virtual TSharedRef<FTextToSpeechBase> Create() override;` — ITextToSpeechFactory

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FAppleTextToSpeechFactory FPlatformTextToSpeechFactory;`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Flite/FliteAdapter.h` (Private)


#### struct `FliteSpeechStreaming`  
`struct FliteSpeechStreaming`  
_L10-15_
- L13 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSynthesizedSpeechChunk, FFliteSynthesizedSpeechData);` — Delegate that fires when flite streams in a chunk of audio
- L14 _public member_ `static FOnSynthesizedSpeechChunk OnSynthesizedSpeechChunk;`

#### class `FFliteAdapter`  
`class FFliteAdapter`  
_L23-73_
- desc: Adapter that handles Flite initialization and deinitialization as well as converting audio data from flite format to unreal format
- L26 _public prototype_ `FFliteAdapter();`
- L27 _public prototype_ `~FFliteAdapter();`
- L29 _public prototype_ `void StartSynthesizeSpeechData_GameThread(const FString& InText);` — Starts synthesizing the given text into speech. Must be called from the game thread.
- L31 _public prototype_ `void StopSynthesizeSpeechData_GameThread();` — Stops the synthesis of the current text
- L33 _public prototype_ `void SynthesizeSpeechData_AnyThread(const FString& InText);` — Called in background threads to
- L41 _public prototype_ `float GetRate_GameThread() const;` — Gets the speech rate Flite is synthesizing text in Unreal units. * Value guaranteed to be between 0.0f and 1.0f
- L46 _public prototype_ `void SetRate_GameThread(float InRate);` — Sets the speech rate for Flite to synthesize text at. User expected to pass in a value between 0.0f and 1.0f
- L50 _private prototype_ `float GetFliteMaximumRate() const;` — Returns the maximum speech rate allowed in Flite units
- L52 _private prototype_ `float GetFliteMinimumRate() const;` — Returns the minimum speech rate allowed in Flite units
- L54 _private prototype_ `void RegisterVoices();` — Register all desired voices for Flite
- L56 _private prototype_ `void UnregisterVoices();` — Unregister all voices used from Flite
- L58 _private member_ `cst_voice_struct* FliteCurrentVoice;` — The currently active voice. Note only US_EN supported right now
- L60 _private member_ `cst_audio_streaming_info_struct* FliteAudioStreamingInfo;` — The streaming info for the current voice being used
- L62 _private member_ `float FliteRate;` — The speech rate the voice should be synthesized at in Flite units
- L71 _private member_ `static const float FliteMaximumDurationStretch;` — Flite uses the feasture "duration_stretch" t scale the duration of an utterance.o E.g Duration stretch of 2.0 means the utterance will take twice as long to finish speaking. Thus a duration_stretch of X can be interpreted as speaking at a rate of 1/X
- L72 _private member_ `static const float FliteMinimumDurationStretch;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSynthesizedSpeechChunk, FFliteSynthesizedSpeechData);` — Delegate that fires when flite streams in a chunk of audio

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Flite/FliteSynthesizedSpeechData.h` (Private)


#### struct `FFliteSynthesizedSpeechData`  
`struct FFliteSynthesizedSpeechData`  
_L9-25_
- L11 _public prototype_ `FFliteSynthesizedSpeechData();`
- L13 _public prototype_ `FFliteSynthesizedSpeechData(TArray<float> InSpeechBuffer, int32 InSampleRate, int32 InNumChannels);` — TArrays to be passed by move construction
- L14 _public function_ `bool HasData() const`
- L15 _public prototype_ `bool IsValid() const;`
- L16 _public prototype_ `void Reset();`
- L17 _public function_ `int32 GetNumSpeechSamples() const`
- L18 _public function_ `float* GetSpeechData()`
- L19 _public function_ `bool IsLastChunk() const`
- L21 _public member_ `TArray<float> SpeechBuffer;`
- L22 _public member_ `int32 SampleRate;`
- L23 _public member_ `int32 NumChannels;`
- L24 _public member_ `bool bIsLastChunk;`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Flite/FliteTextToSpeech.h` (Private)


#### class `FFliteTextToSpeech`  
`class FFliteTextToSpeech : public FTextToSpeechBase`  
_L10-44_
- inherits: `FTextToSpeechBase`
- L13 _public prototype_ `FFliteTextToSpeech();`
- L14 _public prototype_ `virtual ~FFliteTextToSpeech();`
- L17 _public prototype_ `virtual void Speak(const FString& InStringToSpeak) override final;` — FTextToSpeechBase
- L18 _public prototype_ `virtual bool IsSpeaking() const override final;`
- L19 _public prototype_ `virtual void StopSpeaking() override final;`
- L20 _public prototype_ `virtual float GetVolume() const override final;`
- L21 _public prototype_ `virtual void SetVolume(float InVolume) override final;`
- L22 _public prototype_ `virtual float GetRate() const override final;`
- L23 _public prototype_ `virtual void SetRate(float InRate) override final;`
- L24 _public prototype_ `virtual void Mute() override final;`
- L25 _public prototype_ `virtual void Unmute() override final;`
- L27 _protected prototype_ `virtual void OnActivated() override final;`
- L28 _protected prototype_ `virtual void OnDeactivated() override final;`
- L35 _private prototype_ `void OnSynthesizedSpeechChunk_AnyThread(FFliteSynthesizedSpeechData InSynthesizedSpeechData);` — Callback to queue synthesized audio data into the submix listener for playback Should only be called by worker threads in background threads
- L41 _private member_ `TUniquePtr<class FFliteAdapter> FliteAdapter;` — Handles synthesizing of speech and returning speech audio data in a format our Audio Engine can use
- L43 _private member_ `TSharedPtr<FFliteTextToSpeechSubmixListener, ESPMode::ThreadSafe> TTSSubmixListener;` — Handles routing synthesized speech audio data directly to the hardware

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Flite/FliteTextToSpeechSubmixListener.h` (Private)


#### class `FFliteTextToSpeechSubmixListener`  
`class FFliteTextToSpeechSubmixListener : public ISubmixBufferListener`  
_L14-102_
- inherits: `ISubmixBufferListener`
- desc: Handles storing TTS audio data to be played. Expects audio data as floats
- L17 _public prototype_ `FFliteTextToSpeechSubmixListener(TextToSpeechId InOwningTTSId);`
- L18 _public prototype_ `virtual ~FFliteTextToSpeechSubmixListener();`
- L21 _public prototype_ `void StartPlayback_GameThread();` — Starts playback and allows any queued audio datat to be played
- L26 _public prototype_ `void QueueSynthesizedSpeechChunk_AnyThread(FFliteSynthesizedSpeechData InSynthesizedSpeechChunk);` — * Queues a chunk of synthesized audio streamed from the flite library. Called by background worker threads.
- L28 _public prototype_ `void StopPlayback_GameThread();` — Stops playback and stops all audio from playing
- L30 _public prototype_ `bool IsPlaybackActive() const;` — Returns true if the submix listener is playing the queued speech audio data. Else false
- L32 _public prototype_ `void Mute();` — Mutes the submix listener. No speech audio data will be played
- L34 _public prototype_ `void Unmute();` — Unmutes the submix listener. Speech audio data will be audible again
- L36 _public function_ `bool IsMuted() const` — Returns true if the submix listener is muted. Else false.
- L38 _public prototype_ `float GetVolume() const;` — Returns the volume the speech data is played at
- L40 _public prototype_ `void SetVolume(float InVolume);` — Sets the volume the speech data should be played at
- L43 _public prototype_ `virtual const FString& GetListenerName() const override;` — ISubmixBufferListener
- L44 _public prototype_ `virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;`
- L45 _public prototype_ `virtual bool IsRenderingAudio() const override;`
- L76 _private member_ `FSynthesizedSpeechBuffer SynthesizedSpeechBuffer;`
- L77 _private member_ `Audio::FResampler AudioResampler;`
- L78 _private member_ `FCriticalSection SynthesizedSpeechBufferCS;`
- L83 _private member_ `TArray<float> OutputSpeechBuffer;` — The buffer that stores the data with DSP applied should only be used in audio render thread
- L85 _private member_ `TextToSpeechId OwningTTSId;` — ID for the TTS object htat owns this usbmix listener
- L91 _private member_ `std::atomic<float> Volume;` — Current volume between 0.0f and 1.0f. written/read in game thread and read in audio render thread
- L96 _private member_ `std::atomic<bool> bAllowPlayback;` — If true, this allows audio playback of the queued audio data written in game thread read in audio render thread
- L101 _private member_ `std::atomic<bool> bMuted;` — If true, this mutes the submix listener and prevents any audio from playing written in game thread and read in audio render thread

#### class `FFliteTextToSpeechSubmixListener::FSynthesizedSpeechBuffer`  
`class FSynthesizedSpeechBuffer`  
_L48-75_
- L51 _public prototype_ `FSynthesizedSpeechBuffer();`
- L53 _public prototype_ `void PushData(FFliteSynthesizedSpeechData InSpeechData);` — Should only be called in background thread
- L61 _public prototype_ `int32 PopData_AudioRenderThread(TArray<float>& OutBuffer, int32 NumRequestedSamples, bool& bOutPoppingLastChunk);` — Should only be called from audio render thread Expects a zeroed out buffer. Note that it is possible for the buffer to not be empty but pop 0 data from a chunk due to Flite's occassional streaming of a 0 data chunk with a flag indicating that the chunk is finished synthesizing.
- L63 _public prototype_ `void Reset_GameThread();` — Should only be called from game thread
- L64 _public prototype_ `bool IsEmpty() const;`
- L66 _public prototype_ `const FFliteSynthesizedSpeechData& GetCurrentChunk_AudioRenderThread() const;` — Should only be called from audio render thread
- L68 _private prototype_ `bool IsFull() const;`
- L69 _private member_ `TCircularBuffer<FFliteSynthesizedSpeechData> SynthesizedSpeechChunks;`
- L70 _private member_ `int32 ReadIndex;`
- L71 _private member_ `int32 WriteIndex;`
- L74 _private member_ `int32 ChunkReadIndex;` — Used to keep track of where in the current chunk we should start reading from Modified in audio render thread

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/IOS/IOSTextToSpeechFactory.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Linux/LinuxTextToSpeechFactory.h` (Private)


#### class `FLinuxTextToSpeechFactory`  
`class FLinuxTextToSpeechFactory : public ITextToSpeechFactory`  
_L9-16_
- inherits: `ITextToSpeechFactory`
- desc: The platform default text to speech factory for Linux platforms.
- L12 _public prototype_ `FLinuxTextToSpeechFactory() = default;`
- L13 _public prototype_ `virtual ~FLinuxTextToSpeechFactory() = default;`
- L15 _public prototype_ `virtual TSharedRef<FTextToSpeechBase> Create() override;`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FLinuxTextToSpeechFactory FPlatformTextToSpeechFactory;`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Mac/MacTextToSpeechFactory.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/TextToSpeechLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextToSpeech, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextToSpeech, Log, All);`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Private/Windows/WindowsTextToSpeechFactory.h` (Private)


#### class `FWindowsTextToSpeechFactory`  
`class FWindowsTextToSpeechFactory : public ITextToSpeechFactory`  
_L10-17_
- inherits: `ITextToSpeechFactory`
- desc: The platform default text to speech factory for Windows.
- L13 _public prototype_ `FWindowsTextToSpeechFactory() = default;`
- L14 _public prototype_ `virtual ~FWindowsTextToSpeechFactory() = default;`
- L16 _public prototype_ `virtual TSharedRef<FTextToSpeechBase> Create() override;`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FWindowsTextToSpeechFactory FPlatformTextToSpeechFactory;`

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Public/GenericPlatform/ITextToSpeechFactory.h` (Public)


#### class `ITextToSpeechFactory`  
`class ITextToSpeechFactory`  
_L14-24_
- desc: Abstract base class for all factories that create text to speech objects. Platform default factories have already been provided for all allowed platforms for this plugin. Inherit from this class and register it with the text to speech module to create your own custom text to speech objects See ITextToSpeechModule.h for more details.
- L17 _public prototype_ `virtual ~ITextToSpeechFactory() = default;`
- L23 _public prototype_ `virtual TSharedRef<FTextToSpeechBase> Create() = 0;` — Creates an instance of a text to speech object. It is advised to only have 1 TTS as multiple TTS can speak over each other. Callers are responsible for managing the lifetime of the TTS

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Public/GenericPlatform/TextToSpeechBase.h` (Public)


#### class `FTextToSpeechBase`  
`class FTextToSpeechBase : public TSharedFromThis<FTextToSpeechBase>`  
_L13-104_
- inherits: `TSharedFromThis<FTextToSpeechBase>`
- desc: Abstract base class for all text to speech engines. Subclass for each new speech synthesis method to be used. Text to speech takes in an FString and synthesizes audio data based on the text using the underlying speech synthesizer.
- L17 _public prototype_ `DECLARE_DELEGATE(FOnTextToSpeechFinishSpeaking);` — A delegate that fires when the underlying text to speech has successfully finished speaking the requested string
- L18 _public member_ `static const TextToSpeechId InvalidTextToSpeechId = -1;`
- L20 _public prototype_ `FTextToSpeechBase();`
- L21 _public prototype_ `virtual ~FTextToSpeechBase();`
- L23 _public function_ `TextToSpeechId GetId() const` — Returns the ID associated with this text to speech object
- L29 _public prototype_ `void OnTextToSpeechFinishSpeaking_GameThread();` — This should only be called by text to speech implementations to signal that a requessted string has successfully finished speaking. Note that this should not be invoked when the spoken string is interrupted or stopped.
- L31 _public function_ `void SetTextToSpeechFinishedSpeakingDelegate(const FOnTextToSpeechFinishSpeaking& Delegate)` — Sets the TextToSpeechFinishedSpeakingDelegate
- L37 _public prototype_ `void Activate();` — Activates the TTS system and does the necessary set up. Calls OnActivated() at the end of set up. Override OnActivated() in child classes to provide additional set up.
- L44 _public prototype_ `void Deactivate();` — Deactivates the TTS and performs tear down. OnDeactivated() called at the start of tear down. Override OnDeactivated() in child classes to provide additional tear down.
- L47 _public function_ `bool IsMuted() const` — Returns true if the TTS is muted. Else false.
- L50 _public function_ `bool IsActive() const` — Returns true if the TTS is active. Else false.
- L58 _public prototype_ `virtual void Speak(const FString& InStringToSpeak) = 0;` — Immediately speaks the requested string. If another string is being spoken by the TTS, the current string will immediately be stopped before the requested string is spoken. Note: Passing in long sentences or paragraphs are not recommended. Split the paragraph into shorter sentences and register with the OnTextToSpeechFinishSpeakingDelegate to pass in the next chunk.
- L60 _public prototype_ `virtual bool IsSpeaking() const = 0;` — Returns true if any string is currently being spoken, else false.
- L62 _public prototype_ `virtual void StopSpeaking() = 0;` — Immediately stops speaking the current string being spoken
- L64 _public function_ `virtual float GetVolume() const` — Returns the current volume being spoken at.  Value is between 0 and 1.0f.
- L66 _public function_ `virtual void SetVolume(float InVolume)` — Sets the volume for strings to be spoken at. Clamps to 0 and 1.0f.
- L69 _public function_ `virtual float GetRate() const` — Returns the current speech rate strings are spoken at. Value is between 0 and 1.0f.
- L71 _public function_ `virtual void SetRate(float InRate)` — Sets the current speech rate strings should be spoken at. Clamps to 0 and 1.0f.
- L74 _public function_ `virtual void Mute()` — Mutes the TTS so no synthesized speech is audible
- L76 _public function_ `virtual void Unmute()` — Unmutes the TTS so requests to speak strings are audible again.
- L80 _protected function_ `void SetMuted(bool bInMuted)` — Sets the flag for whether the TTS is muted
- L85 _protected function_ `virtual void OnActivated()` — Called at the end of Activate() Override in child classes to provide additional set up.
- L90 _protected function_ `virtual void OnDeactivated()` — Called at the start of Deactivate() Override in child classes to provide additional tear down
- L96 _private member_ `FOnTextToSpeechFinishSpeaking TextToSpeechFinishSpeakingDelegate;` — The delegate that is called when the TTS successfully finishes speaking a string. This should not be invoked when speech is interrupted or stopped.
- L99 _private member_ `TextToSpeechId Id;` — The runtime ID for this TTS object. Used primarily for retrieving the TTS object during multithreaded calls
- L101 _private member_ `bool bMuted;` — True if the TTS is muted. Else false.
- L103 _private member_ `bool bActive;` — True if the TTS is active. Elsxe false

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef int8 TextToSpeechId;`
- L17 _delegate_ `DECLARE_DELEGATE(FOnTextToSpeechFinishSpeaking);` — A delegate that fires when the underlying text to speech has successfully finished speaking the requested string

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Public/TextToSpeech.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Public/TextToSpeechEngineSubsystem.h` (Public)


#### class `UTextToSpeechEngineSubsystem`  
`class UTextToSpeechEngineSubsystem: public UEngineSubsystem`  
_L19-198_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Subsystem for interacting with the text to speech system via blueprints. The subsystem consists of a number of text to speech channels associated with a text to speech channel Id. Each text to speech channel provides text to speech functionality such as vocalizing a string, stopping a vocalized string, controlling the audio settings of the channel and muting/unmuting a channel. Most of the functions take a text to speech channel Id which allows you to request text to speech functionality on the requested channel. All newly added text to speech channels start off deactivated and must be activated before any text to speech functionality can be used.
- L23 _public prototype_ `UTextToSpeechEngineSubsystem();`
- L24 _public prototype_ `virtual ~UTextToSpeechEngineSubsystem();`
- L38 _public prototype_ `void SpeakOnChannel(UPARAM(DisplayName = "Channel Id") FName InChannelId, UPARAM(ref, DisplayName="String To Speak") const F` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Immediately vocalizes the requested string asynchronously on the requested text to speech channel, interrupting any string that is already being vocalized on the channel. If the provided channel Id does not exist, nothing will be vocalized. Before executing this function, a text to speech channel must be added and activated. To create a platform default text to speech channel, use AddDefaultChannel. To create a custom text to speech channel with a user-implemented C++ text to speech class, use AddCustomChannel. This function is not intended for long strings that span multiple sentences or paragraphs. @param InChannelId The Id of the channel to speak on. @param InStringToSpeak The string to speak on the requested channel. @see AddDefaultChannel, AddCustomChannel, ActivateChannel, ActivateAllChannels
- L46 _public prototype_ `void StopSpeakingOnChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Immediately stops any currently vocalized string on the channel. If the provided channel Id does not exist, nothing will happen. @param InChannelId The Id of the channel speech should be stopped on.
- L50 _public prototype_ `void StopSpeakingOnAllChannels();` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Immediately stops strings from being vocalized on all text to speech channels.
- L57 _public prototype_ `bool IsSpeakingOnChannel(UPARAM(DisplayName = "Channel Id") FName InChannel` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Return true when the targeted text to speech channel is vocalising, otherwise false. @param InChannelId The id of the channel to check if a string is being vocalized.
- L65 _public prototype_ `float GetVolumeOnChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Returns the current volume strings are vocalized on a text to speech channel.  Value is between 0.0f and 1.0f. If the provided channel Id doesn't exist, 0.0f will be returned. @param InChannelId The Id for the channel to retrieve the volume from.
- L74 _public prototype_ `void SetVolumeOnChannel(UPARAM(DisplayName = "Channel Id") FName InChannelId, UPARAM(DisplayName = "Volume")` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Sets the volume for strings vocalized on a text to speech channel. If the provided channel Id does not exist, nothing will happen. @param InChannelId The Id for the channel to set for. @param InVolume The volume to be set on the channel. The value will be clamped between 0.0f and 1.0f.
- L82 _public prototype_ `float GetRateOnChannel(UPARAM(DisplayName = "Channel Id") FName InChannel` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Returns the current speech rate strings are vocalized on a text to speech channel. Value is between 0.0 and 1.0. If the provided channel Id does not exist, 0.0f will be returned. @param InChannelId The Id for the channel to get the speech rate from.
- L91 _public prototype_ `void SetRateOnChannel(UPARAM(DisplayName = "Channel Id") FName InChannelId, UPARAM(DisplayName = "Rate")` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Sets the current speech rate strings should be vocalized on a text to speech channel. If the provided channel does not exist, nothing will happen. @param InChannelId The Id for the channel to set the speech rate on. @param InRate The speech rate to set for the channel. Value will be clamped between 0.0f and 1.0f.
- L99 _public prototype_ `void MuteChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Mutes a text to speech channel so no vocalized strings are audible on that channel. If the requested channel is already muted, nothing will happen. @param InChannelId The Id for the channel to mute.
- L107 _public prototype_ `void UnmuteChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Unmutes a text to speech channel so vocalized strings are audible on the channel. If the requested channel is already unmuted, nothing will happen. @param InChannelId The Id for the channel to unmute.
- L114 _public prototype_ `bool IsChannelMuted(UPARAM(DisplayName = "Channel Id") FName InChannel` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Returns true if the text to speech channel is muted, otherwise false. @param InChannelId The Id for the channel to check if it is muted.
- L122 _public prototype_ `void ActivateChannel(UPARAM(DisplayName="Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Activates a text to speech channel to accept requests to perform text to speech functionality. If the provided channel Id does not exist, nothing will happen. @param InChannelId The Id of the channel to activate.
- L126 _public prototype_ `void ActivateAllChannels();` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Activates all text to speech channels to accept requests for text to speech functionality.
- L134 _public prototype_ `void DeactivateChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Deactivates a text to speech channel and stops any vocalized strings on that channel. Future Requests for text to speech functionality will do nothing. If the provided channel Id does not exist, nothing will happen. @param InChannelId The Id for the channel to deactivate.
- L138 _public prototype_ `void DeactivateAllChannels();` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Deactivates all text to speech channels making all requests for text to speech functionality do nothing.
- L145 _public prototype_ `bool IsChannelActive(UPARAM(DisplayName = "Channel Id") FName InChannel` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Returns true if the text to speech channel is active, otherwise false. @param InChannelId The Id for the channel to check if it is active.
- L156 _public prototype_ `void AddDefaultChannel(UPARAM(DisplayName = "New Channel Id") FName In` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Creates a new  channel for text to speech requests to be made to a platform C++ text to speech class. This will not create the channel if the provided channel id is not unique. Newly added channels must be activated to use text to speech functionalities. For out-of-the-box text to speech support, this is most likely the channel creation method you want. @param InChannelId The Id of the channel you want to add @see ActivateChannel, ActivateAllChannels
- L166 _public prototype_ `void AddCustomChannel(UPARAM(DisplayName = "New Channel Id") FName In` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Creates a new text to speech channel where text to speech requests are fulfilled by a user implemented C++ text to speech class. If you have not specified a custom text to speech class to be used, use AddDefaultChannel instead. This will not add a channel if the channel Id is not unique or if the user has not specified a custom text to speech class to be used in ITextToSpeechModule. Newly added channels must be activated to use text to speech functionalities. @see ITextToSpeechModule, AddDefaultChannel, ActivateChannel, ActivateAllChannels
- L174 _public prototype_ `void RemoveChannel(UPARAM(DisplayName = "Channel Id") FName InC` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Removes a text to speech channel, preventing all further requests for text to speech functionality from the channel. If the provided channel Id does not exist, nothing will happen. @param InChannelId The Id for the channel you want removed.
- L178 _public prototype_ `void RemoveAllChannels();` — `UFUNCTION(BlueprintCallable, Category = TextToSpeech)` — Removes all text to speech channels, preventin future requests for text to speech functionality on all channels.
- L185 _public prototype_ `bool DoesChannelExist(UPARAM(DisplayName = "Channel Id") FName InChannel` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech)` — Returns true if a text to speech channel associated with a channel Id exists. Otherwise, the function returns false. @param InChannelId The channel Id to test if it is associated with a channel.
- L189 _public prototype_ `int32 GetNumChannels() const;` — `UFUNCTION(BlueprintCallable, Category=TextToSpeech, meta=(DisplayName="Get Number Of Channels"))` — Returns the number of text to speech channels that have been added.
- L192 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UEngineSubsystem
- L193 _public prototype_ `virtual void Deinitialize() override;`
- L197 _private member_ `TMap<FName, TSharedRef<FTextToSpeechBase>> ChannelIdToTextToSpeechMap;` — The map of channel Ids to native text to speech objects.

### `Plugins/Experimental/TextToSpeech/Source/TextToSpeech/Public/TextToSpeechModule.h` (Public)


#### class `ITextToSpeechModule`  
`class ITextToSpeechModule : public IModuleInterface`  
_L24-51_
- inherits: `IModuleInterface`
- desc: The module for text to speech. Access this class via the singleton Get() convenience function. Use this class to get and set text to speech factories for creating text to speech objects. A platform default text to speech factory will be created for all allowed platforms for this plugin. Users can subclass from ITextToSpeechFactory and set their own custom factory if desired. Samples: TSharedRef<FTextToSpeechBase> MyPlatformTTS = ITextToSpeechModule::Get().GetPlatformFactory()->Create(); TSharedRef<FMyTextToSpeechFactory> MyTTSFactory = MakeShared<FMyTextToSpeechFactory>(); ITextToSpeechModule::Get().SetCustomFactory(MyTTSFactory); TSharedRef<FTextToSpeechBase> MyCustomTTS = ITextToSharedModule::Get().GetCustomFactory()->Create();
- L28 _public function_ `static ITextToSpeechModule& Get()` — Get this module and load it if required.
- L37 _public prototype_ `virtual TSharedPtr<ITextToSpeechFactory> GetPlatformFactory() const = 0;` — Returns the factory that creates the platform default text to speech object. For all allowed platforms, this is guaranteed to be valid.
- L43 _public prototype_ `virtual TSharedPtr<ITextToSpeechFactory> GetCustomFactory() const = 0;` — Returns the user set text to speech factory. This can be null if no user text to speech factory has been set. It's up to the user to check the returned factory is valid.
- L50 _public prototype_ `virtual void SetCustomFactory(const TSharedRef<ITextToSpeechFactory>& InFactory) = 0;` — Sets a user text to speech factory. Use this to register custom text to speech factories for creating custom text to speech objects. @see ITextToSpeechFactory
