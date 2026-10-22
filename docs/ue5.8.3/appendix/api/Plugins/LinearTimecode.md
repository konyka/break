# Plugins / LinearTimecode

- module root: `Plugins/Media/LinearTimecode/Source/LinearTimecode`
- headers: 5; symbols: 74
- symbol kinds: class=4, delegate=2, enum=1, enumerator=8, function=5, member=32, prototype=20, struct=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Media, MediaAssets, MediaUtils, TimeManagement

### `Plugins/Media/LinearTimecode/Source/LinearTimecode/Private/MediaAudioSampleReader.h` (Private)


#### class `MediaAudioSampleReader`  
`class MediaAudioSampleReader`  
_L9-87_
- L12 _public function_ `MediaAudioSampleReader(TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& InAudioFrame) : AudioFrame(InAudioFrame)`
- L25 _public function_ `bool GetSample(float& OutFloat)` — Get the next Sample from the Audio packet @param OutFloat Returned Sample, -1.0 to 1.0 range return true valid sample returned, false no more samples
- L58 _public function_ `int32 GetSampleStep() const`
- L59 _public function_ `const uint8* const GetCurrentSampleStream() const`
- L63 _protected function_ `static int GetSampleSize(EMediaAudioSampleFormat inFormat)`
- L81 _protected member_ `TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& AudioFrame;`
- L83 _protected member_ `EMediaAudioSampleFormat SampleFormat;`
- L84 _protected member_ `const uint8* SampleStream;`
- L85 _protected member_ `const uint8* SampleEnd;`
- L86 _protected member_ `int32 SampleStep;`

### `Plugins/Media/LinearTimecode/Source/LinearTimecode/Public/DropTimecode.h` (Public)


#### struct `FDropTimecode`  
`struct FDropTimecode`  
_L12-31_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FTimecode Timecode;` — `UPROPERTY(BlueprintReadWrite, Category = "Time")` — Decoded Timecode
- L21 _public member_ `int32 FrameRate = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "Media")` — Guess at incoming frame rate
- L24 _public member_ `bool bColorFraming = false;` — `UPROPERTY(BlueprintReadWrite, Category = "Time")` — Sync is in phase with color burst
- L27 _public member_ `bool bRunningForward = false;` — `UPROPERTY(BlueprintReadWrite, Category = "Time")` — When timecode is reading forward
- L30 _public member_ `bool bNewFrame = false;` — `UPROPERTY(BlueprintReadWrite, Category = "Time")` — Is a new timecode frame

### `Plugins/Media/LinearTimecode/Source/LinearTimecode/Public/LinearTimecodeComponent.h` (Public)


#### class `ULinearTimecodeComponent`  
`class ULinearTimecodeComponent : public USceneComponent`  
_L27-93_
- reflection: `UCLASS(ClassGroup = Media, editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- desc: Implements a Linear timecode decoder.
- L35 _public member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — The media player asset associated with this component.
- L38 _public member_ `FDropTimecode DropTimecode;` — `UPROPERTY(BlueprintReadOnly, Category = "Media")`
- L41 _protected prototype_ `static double FrameRateToFrameDelta(int32 InFrameRate, int32 InDrop);`
- L48 _public prototype_ `int32 GetDropFrameNumber() const;` — `UFUNCTION(BlueprintCallable, Category = "Media")` — Get the Frame Number @return Frame Number
- L55 _public prototype_ `static void GetDropTimeCodeFrameNumber(const FDropTimecode& Timecode, int32& FrameNumber);` — `UFUNCTION(BlueprintCallable, Category = "Media")` — Convert a drop timecode into a frame number @param Timecode - Used to access the framerate, and drop flag @param FrameNumber - returned calculated frame number
- L63 _public prototype_ `static void SetDropTimecodeFrameNumber(const FDropTimecode& Timecode, int32 FrameNumber, FDropTimecode& OutTimecode);` — `UFUNCTION(BlueprintCallable, Category = "Media")` — Convert frame number into a drop timecode @param Timecode - used to access the framerate, and drop flag @param FrameNumber - Frame number to set in the returned timecode @param OutTimecode - Returned drop timecode
- L67 _public member_ `FOnTimecodeChange OnTimecodeChange;` — `UPROPERTY(BlueprintAssignable, Category = "Media")` — Called when the timecode changes
- L70 _public prototype_ `void UpdatePlayer();`
- L74 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L78 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L79 _public prototype_ `virtual void Deactivate() override;`
- L82 _protected prototype_ `void ProcessAudio(TSharedPtr<FMediaAudioSampleQueue, ESPMode::ThreadSafe> SampleQueue);`
- L86 _protected member_ `TWeakPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> CurrentPlayerFacade;` — The player facade that's currently providing audio samples.
- L89 _protected member_ `TSharedPtr<FMediaAudioSampleQueue, ESPMode::ThreadSafe> SampleQueue;` — Audio sample queue.
- L92 _protected member_ `TSharedPtr<FLinearTimecodeDecoder, ESPMode::ThreadSafe> TimecodeDecoder;` — The Actual decoder

#### class `UDropTimecodeToStringConversion`  
`class UDropTimecodeToStringConversion : public UBlueprintFunctionLibrary`  
_L99-106_
- reflection: `UCLASS(meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Extend type conversions to handle FDropTimecode structure
- L105 _private prototype_ `static FString Conv_DropTimecodeToString(const FDropTimecode& InTimecode);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (DropTimecode)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")` — Convert a timecode structure into a string

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimecodeChange, const FDropTimecode&, Timecode);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimecodeChange, const FDropTimecode&, Timecode);`

### `Plugins/Media/LinearTimecode/Source/LinearTimecode/Public/LinearTimecodeDecoder.h` (Public)


#### class `FLinearTimecodeDecoder`  
`class FLinearTimecodeDecoder`  
_L12-97_
- L18 _public prototype_ `FLinearTimecodeDecoder();` — TimeCode structure used by reader
- L22 _public prototype_ `void Reset(void);` — Flush internal state of timecode reader
- L29 _public prototype_ `bool Sample(float InSample, FDropTimecode& OutTimeCode);` — Analyze a single sample, looking for a time code pattern @param InSample - single normalized sample, 1.0 to -1.0 @param OutTimeCode - returned timecode to this point, untouched if not end of sequence sample @return true if sample was last in a timecode frame
- L54 _protected prototype_ `void ShiftAndInsert(uint16* InBitStream, bool InBit) const;` — Add bit to decoded stream.
- L56 _protected prototype_ `void DecodeBitStream(uint16* InBitStream, EDecodePattern* InDecodePatern, int32 InForward, FDropTimecode& OutTimeCode);`
- L57 _protected prototype_ `bool HasCompleteFrame(uint16* InBitStream) const;`
- L58 _protected prototype_ `bool DecodeFrame(uint16* InBitStream, FDropTimecode& OutTimeCode);`
- L61 _protected prototype_ `int32 AdjustCycles(int32 InClock) const;` — Tries to calculate the number of clocks per bit
- L64 _protected member_ `static EDecodePattern ForwardPattern[];`
- L65 _protected member_ `static EDecodePattern BackwardPattern[];`
- L68 _protected member_ `float Center;` — Sample value to detect zero crossings/edges of the input signal
- L71 _protected member_ `bool bCurrent;` — Helper to detect zero crossings/edges of the input signal.
- L74 _protected member_ `int32 Clock;` — Counts number of samples since last edge
- L77 _protected member_ `int32 Cycles;` — Estimates number of samples for a logical 1 in the LTC stream.
- L80 _protected member_ `bool bFlip;` — Indicates that we're expecting the second half of a logical 1.
- L83 _protected member_ `int32 FrameMax;` — Keeps track of largest frame value received, helps estimate FrameRate.
- L86 _protected member_ `int32 FrameRate;` — Tries to infer FrameRate based on frame value rollovers.
- L89 _protected member_ `uint16 TimecodeBits[6];` — Holds the stream to be decoded as bits come in.
- L93 _public member_ `int32 MinSamplesPerEdge;` — Minimum allowable samples per edge in the signal. Helps filter out noise.
- L96 _public member_ `int32 MaxSamplesPerEdge;` — Maximum allowable samples per edge in the signal. Helps filter out noise.

#### struct `FLinearTimecodeDecoder::EDecodePattern`  
`struct EDecodePattern`  
_L33-50_
- desc: used to extract timecode from bit stream
- L46 _public member_ `EDecodeType Type;`
- L47 _public member_ `int32 Index;`
- L48 _public member_ `uint16 Mask;`
- L49 _public member_ `int32 Addition;`

#### enum `FLinearTimecodeDecoder::EDecodePattern::EDecodeType`  
`enum class EDecodeType`  
_L35-45_
- L37 _public enumerator_ `Hours`
- L38 _public enumerator_ `Minutes`
- L39 _public enumerator_ `Seconds`
- L40 _public enumerator_ `Frames`
- L41 _public enumerator_ `DropFrame`
- L42 _public enumerator_ `ColorFrame`
- L43 _public enumerator_ `FrameRate`
- L44 _public enumerator_ `End`

### `Plugins/Media/LinearTimecode/Source/LinearTimecode/Public/LinearTimecodePlugin.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLinearTimecode, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLinearTimecode, Log, All);`
