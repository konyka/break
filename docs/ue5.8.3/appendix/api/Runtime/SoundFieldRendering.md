# Runtime / SoundFieldRendering

- module root: `Source/Runtime/SoundFieldRendering`
- headers: 3; symbols: 48
- symbol kinds: class=5, function=1, member=19, prototype=23
- PrivateDependencyModuleNames: AudioExtensions, AudioMixer, Core, Engine, SignalProcessing
- PrivateIncludePathModuleNames: AudioMixerCore, TargetPlatform

### `Source/Runtime/SoundFieldRendering/Public/SoundFieldRendering.h` (Public)


#### class `FAmbisonicsSoundfieldBuffer`  
`class FAmbisonicsSoundfieldBuffer : public ISoundfieldAudioPacket`  
_L15-42_
- inherits: `ISoundfieldAudioPacket`
- L19 _public member_ `Audio::FAlignedFloatBuffer AudioBuffer;` — Interleaved audio buffer for all vector parts of the ambisonics stream.
- L24 _public member_ `int32 NumChannels;` — number of channels in the Ambisonics stream. Currently we don't explicitly support mixed order ambisonics, so this will always be equal to (m + 1)^2, where m is the order  of ambisonics this was encoded with.
- L27 _public member_ `FQuat Rotation;` — This is the rotation of the ambisonics source.
- L28 _public member_ `FQuat PreviousRotation;`
- L30 _public function_ `FAmbisonicsSoundfieldBuffer() : NumChannels(0) , Rotation(FQuat::Identity) , PreviousRotation(FQuat::Identity)`
- L36 _public prototype_ `virtual ~FAmbisonicsSoundfieldBuffer() = default;`
- L38 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L39 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> Duplicate() const override;`
- L40 _public prototype_ `virtual void Reset() override;`

#### class `FAmbisonicsSoundfieldSettings`  
`class FAmbisonicsSoundfieldSettings : public ISoundfieldEncodingSettingsProxy`  
_L44-52_
- inherits: `ISoundfieldEncodingSettingsProxy`
- L47 _public member_ `int32 Order;`
- L49 _public prototype_ `virtual uint32 GetUniqueId() const override;`
- L50 _public prototype_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> Duplicate() const override;`

#### class `FSoundFieldDecoder`  
`class FSoundFieldDecoder`  
_L54-94_
- L57 _public prototype_ `FSoundFieldDecoder();` — initializes VirtualSpeakerWorldLockedSpeakerGains
- L59 _public prototype_ `void DecodeAudioDirectlyToDeviceOutputPositions(const FAmbisonicsSoundfieldBuffer& InputData, const FSoundfieldSpeakerPositionalData& OutputPositions, Audio::FAlignedFloatBuffer& OutputData);`
- L60 _public prototype_ `void DecodeAudioToSevenOneAndDownmixToDevice(const FAmbisonicsSoundfieldBuffer& InputData, const FSoundfieldSpeakerPositionalData& OutputPositions, Audio::FAlignedFloatBuffer& OutputData);`
- L61 _public prototype_ `static void RotateFirstOrderAmbisonicsBed(const FAmbisonicsSoundfieldBuffer& InputData, FAmbisonicsSoundfieldBuffer& OutputData, const FQuat& DestinationRotation, const FQuat& PreviousRotation);`
- L63 _public prototype_ `static void FoaRotationInPlace(Audio::FAlignedFloatBuffer& InOutFrames, const float XRotDegrees, const float YRotDegrees, const float ZRotDegrees);`
- L67 _private prototype_ `static void FirstOrderDecodeLoop(const int32 NumFrames, const int32 NumOutputChannels, const float* pAmbiFrame, const int32 NumAmbiChannels, float* SpeakerGainsPtr, float* OutputBufferPtrBuffer);` — Special cased, vectorized versions of first order operations.
- L70 _private prototype_ `static void OddOrderDecodeLoop(const int32 NumFrames, const int32 NumOutputChannels, const float* pAmbiFrame, const int32 NumAmbiChannels, float* SpeakerGainsPtr, float* OutputBufferPtrBuffer);` — Special cased vectorized versions of 3rd and fifth order operations.
- L73 _private prototype_ `static void EvenOrderDecodeLoop(const int32 NumFrames, const int32 NumOutputChannels, const float* pAmbiFrame, const int32 NumAmbiChannels, float* SpeakerGainsPtr, float* OutputBufferPtrBuffer);` — Partially vectorized decode operations for 2nd and 4th order operations.
- L77 _private prototype_ `static TArray<Audio::FChannelPositionInfo>* GetDefaultChannelPositions(int32 InNumChannels);` — `UE_DEPRECATED(5.8, "Channel position info can be retrieved from the FMixerDevice")` — Helper function to get the default channel positions for a channel array.
- L79 _private member_ `Audio::FAlignedFloatBuffer VirtualSpeakerScratchBuffers;`
- L80 _private member_ `Audio::FAlignedFloatBuffer FoaVirtualSpeakerWordLockedGains;`
- L81 _private member_ `Audio::FAlignedFloatBuffer TargetSpeakerGains;`
- L82 _private member_ `Audio::FAlignedFloatBuffer CurrentSpeakerGains;`
- L83 _private member_ `Audio::FAlignedFloatBuffer MixdownGainsMap;`
- L84 _private member_ `Audio::FBufferLinearEase SpeakerGainLerper;`
- L85 _private member_ `FVector2D LastListenerRotationSphericalCoord{ -999.f, -999.f };` — force interpolation on first callback
- L87 _private member_ `static FSphericalHarmonicCalculator SphereHarmCalc;`
- L88 _private member_ `static TArray<Audio::FChannelPositionInfo> VirtualSpeakerLocationsHorzOnly;`
- L89 _private member_ `static const VectorRegister Sqrt2Over2Vec;`
- L90 _private member_ `static const VectorRegister ZeroVec;`

#### class `FSoundFieldEncoder`  
`class FSoundFieldEncoder`  
_L96-108_
- L99 _public prototype_ `FSoundFieldEncoder();`
- L100 _public prototype_ `void EncodeAudioDirectlyFromOutputPositions(const Audio::FAlignedFloatBuffer& InputData, const FSoundfieldSpeakerPositionalData& InputPositions, const FAmbisonicsSoundfieldSettings& Settings, FAmbisonicsSoundfieldBuffer& OutputData);`
- L103 _private prototype_ `static void EncodeLoop(const int32 NumFrames, const int32 NumInputChannels, const float* RESTRICT InputAudioPtr, const int32 NumAmbiChannels, float* RESTRICT SpeakerGainsPtr, float* RESTRICT OutputAmbiBuffer);`
- L105 _private member_ `Audio::FAlignedFloatBuffer VirtualSpeakerScratchBuffers;`
- L106 _private member_ `Audio::FAlignedFloatBuffer SpeakerGains;`
- L107 _private member_ `Audio::FAlignedFloatBuffer MixdownGainsMap;`

#### Free symbols / members of external scopes

- L10 _prototype_ `FName GetUnrealAmbisonicsFormatName();`
- L11 _prototype_ `TUniquePtr<ISoundfieldDecoderStream> CreateDefaultSourceAmbisonicsDecoder(Audio::FMixerDevice* InDevice);`
- L12 _prototype_ `ISoundfieldEncodingSettingsProxy& GetAmbisonicsSourceDefaultSettings();`

### `Source/Runtime/SoundFieldRendering/Public/SoundFieldRenderingModule.h` (Public)


#### class `FSoundFieldRenderingModule`  
`class FSoundFieldRenderingModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/SoundFieldRendering/Public/SphericalHarmonicCalculator.h` (Public)
_(no declarations extracted)_
