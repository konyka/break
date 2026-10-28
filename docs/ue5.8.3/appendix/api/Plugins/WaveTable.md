# Plugins / WaveTable

- module root: `Plugins/Runtime/WaveTable/Source/WaveTable`
- headers: 8; symbols: 251
- symbol kinds: class=5, delegate=1, enum=6, enumerator=40, function=13, macro=7, member=57, namespace=6, prototype=106, struct=8, typedef=1, variable=1
- PrivateDependencyModuleNames: SignalProcessing
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine

### `Plugins/Runtime/WaveTable/Source/WaveTable/Private/WaveTableLogging.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveTable, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveTable, Log, All);`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTable.h` (Public)


#### struct `WaveTable::FWaveTableView`  
`struct FWaveTableView`  
_L18-29_
- desc: Read-only view to a wave table struct
- L20 _public member_ `TArrayView<const float> SampleView;`
- L21 _public member_ `const float FinalValue = 0.0f;`
- L23 _public prototype_ `explicit FWaveTableView(const TArray<float>& InSamples, const float InFinalValue);`
- L24 _public prototype_ `explicit FWaveTableView(const TArrayView<const float>& InSamples, const float InFinalValue);`
- L27 _public prototype_ `int32 Num() const;` — returns the length of the SampleView array, not including the additional FinalValue
- L28 _public prototype_ `bool IsEmpty() const;`

#### struct `WaveTable::FWaveTable`  
`struct FWaveTable`  
_L34-64_
- desc: WaveTable data used at runtime by oscillators, envelopes, etc.  Always as 32-bit float bit depth for processing optimization, at the expense of memory.
- L37 _private member_ `TArray<float> Samples;`
- L38 _private member_ `float FinalValue = 0.0f;`
- L41 _public prototype_ `FWaveTable() = default;`
- L42 _public prototype_ `FWaveTable(const TArray<float>& InSamples, const float InFinalValue = 0.0f);`
- L43 _public prototype_ `FWaveTable(TArray<float>&& InSamples, const float InFinalValue);`
- L44 _public prototype_ `FWaveTable(const ::FWaveTableData& InData);`
- L46 _public prototype_ `float* GetData();`
- L47 _public prototype_ `const float* GetData() const;`
- L48 _public prototype_ `FWaveTableView GetView() const;`
- L49 _public prototype_ `TArrayView<float> GetSamples();`
- L50 _public prototype_ `int32 Num() const;`
- L51 _public prototype_ `void Set(TArray<float>&& InSamples);`
- L52 _public prototype_ `void Set(TArrayView<const float> InSamples);`
- L53 _public prototype_ `void SetFinalValue(const float InValue);`
- L54 _public prototype_ `void SetNum(int32 InSize);`
- L55 _public prototype_ `void Zero();`
- L57 _public function_ `inline static void WrapIndexSmooth(int32 InMax, float& InOutIndex)`

#### enum `EWaveTableBitDepth`  
`enum class EWaveTableBitDepth : uint8`  
_L69-82_
- reflection: `UENUM(BlueprintType)`
- L74 _public enumerator_ `PCM_16` — Lower resolution and marginal performance cost with conversion overhead (engine operates on 32-bit) with the advantage of half the size in memory.
- L79 _public enumerator_ `IEEE_Float` — Higher precision and faster operative performance (engine operates at 32-bit) at the cost of twice the memory of 16-bit.
- L81 _public enumerator_ `COUNT UMETA(Hidden)`

#### struct `FWaveTableData`  
`struct FWaveTableData`  
_L87-171_
- reflection: `USTRUCT(BlueprintType)`
- desc: Serialized WaveTable data, that supports multiple bit depth formats.
- L91 _public prototype_ `FWaveTableData() = default;`
- L92 _public prototype_ `FWaveTableData(EWaveTableBitDepth InBitDepth);`
- L93 _public prototype_ `FWaveTableData(TArrayView<const float> InSamples, float InFinalValue);`
- L94 _public prototype_ `FWaveTableData(TArrayView<const int16> InSamples, float InFinalValue);`
- L97 _public prototype_ `static FName GetBitDepthPropertyName();`
- L102 _private member_ `EWaveTableBitDepth BitDepth = EWaveTableBitDepth::PCM_16;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L105 _private member_ `TArray<uint8> Data;` — `UPROPERTY()`
- L108 _private member_ `float FinalValue = ::WaveTable::InvalidWaveTableValue;` — `UPROPERTY()`
- L111 _private prototype_ `inline int32 GetSampleSize() const;` — Returns the size of the underlying data's sample in number of bytes.
- L117 _public prototype_ `void ArrayMixIn(TArrayView<float> OutputWaveSamples, float Gain = 1.0f) const;` — Adds this WaveTableData's internal contents to the given float buffer view, initially performing bit depth conversion to values to IEEE_FLOAT if required. Provided buffer's size must match this WaveTableData's samples count.
- L120 _public prototype_ `void Empty();` — Empties the underlying data container, deallocating memory and invalidating the FinalValue.
- L122 _public prototype_ `EWaveTableBitDepth GetBitDepth() const;`
- L125 _public prototype_ `const TArray<uint8>& GetRawData() const;` — Returns read-only view of byte array that stores sample data.
- L130 _public prototype_ `bool GetDataView(TArrayView<const float>& OutData) const;` — Returns true if ArrayView of underlying Data in the proper sample format, setting OutData to a view of the Table's data. Returns false if the bit depth of the provided ArrayView does not match the Table's BitDepth property.
- L131 _public prototype_ `bool GetDataView(TArrayView<float>& OutData);`
- L132 _public prototype_ `bool GetDataView(TArrayView<const int16>& OutData) const;`
- L133 _public prototype_ `bool GetDataView(TArrayView<int16>& OutData);`
- L138 _public prototype_ `int32 GetNumSamples() const;` — Returns number of samples within the underlying DataView, not including a FinalValue if set. (Should not to be confused with the number of bytes used to represent the given DataView in the internal Data container).
- L141 _public prototype_ `float GetLastValue() const;` — Returns the last data value value as a float.  If DataView is empty, returns 0.
- L146 _public prototype_ `float GetFinalValue() const;` — Returns the value to interpolate to beyond the last value of the DataView. If FinalValue property is set to invalid (default), returns the last value in the underlying DataView (see GetLastValue).
- L149 _public prototype_ `bool IsEmpty() const;` — Whether or not the underlying data is empty.
- L152 _public prototype_ `bool Resample(int32 InCurrentSampleRate, int32 InNewSampleRate, ::WaveTable::FWaveTableSampler::EInterpolationMode InInterpMode = ::WaveTable::FWaveTableSampler::EInterpolationMode::Cubic);` — Resamples the underlying data to a provided new sample rate.
- L156 _public prototype_ `void Reset(int32 NumSamples);` — Resets the underlying data to the given number of samples. Does not change memory allocation of data unless NumSamples is larger than the current size.
- L161 _public prototype_ `bool SetBitDepth(EWaveTableBitDepth InBitDepth);` — Converts bit depth and sets internal data to the requested bit depth. Returns true if conversion took place, false if not (i.e. data was already sampled at the given bit depth).
- L162 _public prototype_ `void SetData(TArrayView<const int16> InData, bool bIsLoop);`
- L163 _public prototype_ `void SetData(TArrayView<const float> InData, bool bIsLoop);`
- L164 _public prototype_ `void SetRawData(EWaveTableBitDepth InBitDepth, TArrayView<const uint8> InData);`
- L165 _public prototype_ `void SetRawData(EWaveTableBitDepth InBitDepth, TArray<uint8>&& InData);`
- L166 _public prototype_ `void SetFinalValue(float InFinalValue);`
- L170 _public prototype_ `void Zero(int32 InNumSamples = INDEX_NONE);` — Zeros the underlying data. If InNumSamples is set (optional), allocates space in underlying data array for the given number of samples.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WAVETABLE_API`
- L12 _namespace_ `namespace WaveTable`
- L15 _variable_ `constexpr float InvalidWaveTableValue = TNumericLimits<float>::Min();` (scope `WaveTable`) — An invalid WaveTable value, used to detect uninitialized final values.

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableBank.h` (Public)


#### struct `FWaveTableBankEntry`  
`struct FWaveTableBankEntry`  
_L21-27_
- reflection: `USTRUCT()`
- L26 _public member_ `FWaveTableTransform Transform;` — `UPROPERTY(EditAnywhere, Category = Table)`

#### class `UWaveTableBank`  
`class UWaveTableBank : public UObject, public IAudioProxyDataFactory`  
_L30-91_
- reflection: `UCLASS(MinimalAPI, config = Engine, editinlinenew, BlueprintType)`
- inherits: `UObject,IAudioProxyDataFactory`
- L37 _public member_ `EWaveTableSamplingMode SampleMode = EWaveTableSamplingMode::FixedResolution;` — `UPROPERTY(EditAnywhere, Category = Options)` — Sampling mode used for the bank.
- L41 _public member_ `EWaveTableResolution Resolution = EWaveTableResolution::Res_256;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SampleMode == EWaveTableSamplingMode::FixedResolution", EditConditionHides))` — Number of samples cached for each entry in the given bank.
- L45 _public member_ `int32 SampleRate = 48000;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SampleMode == EWaveTableSamplingMode::FixedSampleRate", ClampMin = "1", ClampMax = "48000", EditConditionHides))` — Number of samples cached for each entry in the given bank.
- L51 _public member_ `bool bBipolar = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Determines if output from curve/wavetable are to be clamped between [-1.0f, 1.0f] (i.e. for waveform generation, oscillation, etc.) or [0.0f, 1.0f] (i.e. for enveloping) when sampling curve/wavetable
- L56 _public member_ `float WaveTableSizeMB = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Options, meta = (DisplayName = "WaveTable Size (MB)"))` — Sum total size of all WaveTable data within the given bank
- L60 _public member_ `float WaveTableLengthSec = 0.0f;` — `UE_DEPRECATED(5.3, "Samples now each have own length, as they no longer are required being the same length if using shared 'SampleRate' mode")` — Length of all WaveTable samples in bank in seconds (at 48kHz)
- L68 _public member_ `TArray<FWaveTableBankEntry> Entries;` — `UE_DEPRECATED(5.3, "Direct access of 'Entries' will become protected member in future release and not externally modifiable in runtime builds. If in editor, use GetEntries(). " "To reduce memory consumption, entries are now readonly and cleared in runtime builds when proxy is generated.")` — `UPROPERTY(EditAnywhere, Category = Options)` — Tables within the given bank
- L72 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;` — IAudioProxyDataFactory Implementation
- L74 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L76 _public prototype_ `TArray<FWaveTableBankEntry>& GetEntries();`
- L79 _public prototype_ `void RefreshWaveTables();`
- L81 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L82 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L83 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L87 _private prototype_ `void CopyToProxyData();`
- L88 _private prototype_ `void MoveToProxyData();`
- L90 _private member_ `FWaveTableBankAssetProxyPtr ProxyData;`

#### class `FWaveTableBankAssetProxy`  
`class FWaveTableBankAssetProxy : public Audio::TProxyData<FWaveTableBankAssetProxy>, public TSharedFromThis<FWaveTableBankAssetProxy, ESPMode::ThreadSafe>`  
_L93-143_
- inherits: `Audio::TProxyData<FWaveTableBankAssetProxy>,TSharedFromThis<FWaveTableBankAssetProxy,ESPMode::ThreadSafe>`
- L96 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FWaveTableBankAssetProxy);`
- L98 _public prototype_ `FWaveTableBankAssetProxy() = default;`
- L99 _public prototype_ `FWaveTableBankAssetProxy(uint32 InObjectId, EWaveTableSamplingMode InSamplingMode, int32 InSampleRate, const TArray<FWaveTableBankEntry>& InBankEntries, bool bInBipolar = false);`
- L100 _public prototype_ `FWaveTableBankAssetProxy(uint32 InObjectId, EWaveTableSamplingMode InSamplingMode, int32 InSampleRate, TArray<FWaveTableBankEntry>&& InBankEntries, bool bInBipolar = false);`
- L103 _public prototype_ `FWaveTableBankAssetProxy(const UWaveTableBank& InWaveTableBank);` — `UE_DEPRECATED(5.3, "Proxy generation & respective data translation is now entirely handled by UWaveTableBank calling the constructor variants above.")`
- L105 _public prototype_ `virtual ~FWaveTableBankAssetProxy() = default;`
- L107 _public function_ `virtual EWaveTableSamplingMode GetSampleMode() const`
- L112 _public function_ `virtual int32 GetSampleRate() const`
- L117 _public function_ `virtual const TArray<FWaveTableData>& GetWaveTableData() const`
- L122 _public function_ `virtual bool IsBipolar() const`
- L127 _public function_ `uint32 GetObjectId() const`
- L138 _protected member_ `bool bBipolar = false;`
- L139 _protected member_ `uint32 ObjectId = INDEX_NONE;`
- L140 _protected member_ `int32 SampleRate = 48000;`
- L141 _protected member_ `EWaveTableSamplingMode SampleMode = EWaveTableSamplingMode::FixedResolution;`
- L142 _protected member_ `TArray<FWaveTableData> WaveTableData;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVETABLE_API`
- L17 _typedef_ `using FWaveTableBankAssetProxyPtr = TSharedPtr<FWaveTableBankAssetProxy, ESPMode::ThreadSafe>;`
- L132 _function_ `friend inline uint32 GetTypeHash(const FWaveTableBankAssetProxy& InProxy)`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableImporter.h` (Public)


#### class `WaveTable::FImporter`  
`class FImporter`  
_L16-34_
- L19 _public prototype_ `FImporter(const FWaveTableSettings& InSettings, bool bInBipolar);`
- L22 _public prototype_ `void Process(TArray<float>& OutWaveTable);` — `UE_DEPRECATED(5.3, "Importer now supports multiple bit depths and sample rate. Use version of function that takes in an FWaveTableData struct.")`
- L24 _public prototype_ `void Process(FWaveTableData& OutData);`
- L27 _private prototype_ `void ProcessInternal(const TArrayView<const float> InEditSourceView, TArray<float>& OutWaveTable);`
- L29 _private member_ `const FWaveTableSettings& Settings;`
- L31 _private member_ `bool bBipolar = false;`
- L33 _private member_ `FWaveTableSampler Sampler;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WAVETABLE_API`
- L14 _namespace_ `namespace WaveTable`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableModule.h` (Public)


#### class `WaveTable::FModule`  
`class FModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API WAVETABLE_API`
- L9 _namespace_ `namespace WaveTable`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableSampler.h` (Public)


#### class `WaveTable::FWaveTableSampler`  
`class FWaveTableSampler`  
_L15-128_
- L69 _public prototype_ `FWaveTableSampler();`
- L70 _public prototype_ `FWaveTableSampler(FSettings&& InSettings);`
- L73 _public prototype_ `static void Interpolate(const FWaveTableData& InTableData, TArrayView<float> InOutIndexToSamplesView, EInterpolationMode InterpMode = EInterpolationMode::Linear);` — Interpolates and converts values in the given table for each provided index in the index-to-samples TArrayView (an array of sub-sample, floating point indices)
- L74 _public prototype_ `static void Interpolate(TArrayView<const int16> InTableView, TArrayView<float> InOutIndexToSamplesView, EInterpolationMode InterpMode = EInterpolationMode::Linear);`
- L75 _public prototype_ `static void Interpolate(TArrayView<const float> InTableView, TArrayView<float> InOutIndexToSamplesView, EInterpolationMode InterpMode = EInterpolationMode::Linear);`
- L78 _public prototype_ `float Process(const FWaveTableView& InTableView, float& OutSample, ESingleSampleMode InMode = ESingleSampleMode::Zero);` — Retrieves the sample value at the currently set phase, returning the floating point index which the current phase corresponds to.
- L79 _public prototype_ `float Process(const FWaveTableData& InTableData, float& OutSample, ESingleSampleMode InMode = ESingleSampleMode::Zero);`
- L82 _public prototype_ `float Process(const FWaveTableView& InTableView, TArrayView<float> OutSamplesView);` — Resamples entire table length into given view
- L83 _public prototype_ `float Process(const FWaveTableData& InTableData, TArrayView<float> OutSamplesView);`
- L84 _public prototype_ `float Process(const FWaveTableView& InTableView, TArrayView<const float> InFreqModulator, TArrayView<const float> InPhaseModulator, TArrayView<const float> InSyncTriggers, TArrayView<float> OutSamplesView);`
- L85 _public prototype_ `float Process(const FWaveTableData& InTableData, TArrayView<const float> InFreqModulator, TArrayView<const float> InPhaseModulator, TArrayView<const float> InSyncTriggers, TArrayView<float> OutSamplesView);`
- L88 _public prototype_ `void Reset();` — Resets the last index operated on, restarting the interpolation process for subsequent calls.
- L90 _public prototype_ `const FSettings& GetSettings() const;`
- L95 _public prototype_ `int32 GetIndexFinished() const;` — If set to one-shot, returns the first index where a reverse or stall occurred in the provided interpolated index, ignoring samples where a "sync" request took place. If set to looping, always INDEX_NONE as looping does not support a "finished" state.
- L97 _public prototype_ `void SetInterpolationMode(EInterpolationMode InMode);`
- L98 _public prototype_ `void SetFreq(float InFreq);`
- L99 _public prototype_ `void SetOneShot(bool bInLooping);`
- L100 _public prototype_ `void SetPhase(float InPhase);`
- L103 _private prototype_ `void ComputeIndexFrequency(int32 NumInputSamples, TArrayView<const float> InFreqModulator, TArrayView<const float> InSyncTriggers, TArrayView<float> OutIndicesView);`
- L104 _private prototype_ `void ComputeIndexPhase(int32 NumInputSamples, TArrayView<const float> InPhaseModulator, TArrayView<float> OutIndicesView);`
- L108 _private prototype_ `float ComputeIndexFinished(TArrayView<const float> InSyncTriggers, TArrayView<float> OutIndicesView);` — If set to one-shot, sets IndexFinished to valid index and resets remaining indices provided past the initial stop to the first index. Returns last positively increasing index if finished. If not finished, returns the last index value stored in the view.
- L111 _private prototype_ `float FinalizeSingleSample(float Index, int32 NumSamples, TArrayView<float> OutSample, float LastTableValue, float FinalValue, FWaveTableSampler::ESingleSampleMode InMode);` — Utility that takes in necessary data for finalizing a single sample index processing from either a TableData or a TableView.  Covers edge cases for final value.
- L113 _private member_ `float LastIndex = 0.0f;`
- L123 _private member_ `} OneShotData;`
- L125 _private member_ `TArray<float> PhaseModScratch;`
- L126 _private member_ `FSettings Settings;`

#### enum `WaveTable::FWaveTableSampler::EInterpolationMode`  
`enum class EInterpolationMode`  
_L19-34_
- desc: Interpolation mode when sampling values between indices
- L22 _public enumerator_ `None` — No interpolation (Stepped)
- L25 _public enumerator_ `Linear` — Linear interpolation
- L28 _public enumerator_ `Cubic` — Cubic interpolation
- L31 _public enumerator_ `MaxValue` — Takes the maximum value between two points (EXPENSIVE, but good for caching/drawn curves).
- L33 _public enumerator_ `COUNT`

#### enum `WaveTable::FWaveTableSampler::ESingleSampleMode`  
`enum class ESingleSampleMode`  
_L37-50_
- desc: Mode of interpolation between last value in table and subsequent input index when sampling single values.
- L40 _public enumerator_ `Zero = 0` — Interpolates last value to zero (0.0f) in table if sampled index is beyond last position
- L43 _public enumerator_ `Unit = 1` — Interpolates last value to unit (1.0f) in table if sampled index is beyond last position
- L46 _public enumerator_ `Hold` — Holds last value in table if index is beyond last position
- L49 _public enumerator_ `Loop` — Interpolates last value and first value in table if sampled index is beyond last position

#### struct `WaveTable::FWaveTableSampler::FSettings`  
`struct FSettings`  
_L52-67_
- L54 _public member_ `float Amplitude = 1.0f;`
- L55 _public member_ `float Offset = 0.0f;`
- L59 _public member_ `float Freq = 1.0f;` — How many times to read through the incoming buffer as a ratio to a single output buffer
- L62 _public member_ `float Phase = 0.0f;` — Offset from beginning to end of array [0.0, 1.0]
- L64 _public member_ `EInterpolationMode InterpolationMode = EInterpolationMode::Linear;`
- L66 _public member_ `bool bOneShot = false;`

#### struct `WaveTable::FWaveTableSampler::FOneShotData`  
`struct FOneShotData`  
_L115-123_
- L118 _public member_ `float LastOutputIndex = -1.0f;` — Cached last floating index from prior process, used to compute stopping index if forward progress terminates on buffer boundary.
- L122 _public member_ `int32 IndexFinished = INDEX_NONE;` — Contains index where sampler finished as a result of a sample ending or phase reversing within the last process call. (If < 0, no finish/phase reverse was detected and sampler is considered to be continuing to make forward progress)

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API WAVETABLE_API`
- L11 _namespace_ `namespace WaveTable`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableSettings.h` (Public)


#### enum `EWaveTableResolution`  
`enum class EWaveTableResolution : uint8`  
_L30-53_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `None = 0 UMETA(Hidden)`
- L34 _public enumerator_ `Res_8 = 3 UMETA(DisplayName = "8")`
- L35 _public enumerator_ `Res_16 = 4 UMETA(DisplayName = "16")`
- L36 _public enumerator_ `Res_32 = 5 UMETA(DisplayName = "32")`
- L37 _public enumerator_ `Res_64 = 6 UMETA(DisplayName = "64")`
- L38 _public enumerator_ `Res_128 = 7 UMETA(DisplayName = "128")`
- L39 _public enumerator_ `Res_256 = 8 UMETA(DisplayName = "256")`
- L40 _public enumerator_ `Res_512 = 9 UMETA(DisplayName = "512")`
- L41 _public enumerator_ `Res_1024 = 10 UMETA(DisplayName = "1024")`
- L42 _public enumerator_ `Res_2048 = 11 UMETA(DisplayName = "2048")`
- L43 _public enumerator_ `Res_4096 = 12 UMETA(DisplayName = "4096")`
- L46 _public enumerator_ `Res_Max = Res_4096 UMETA(Hidden)` — Maximum "static" power-of-two WaveTable resolution
- L52 _public enumerator_ `Maximum` — Takes largest source file length (if WaveTable was produced by a file, PCM stream, SoundWave, etc.) of superset of waves, or Res_Max if all superset of waves were produced by curves. This can be very memory intensive if source file is large!

#### enum `EWaveTableSamplingMode`  
`enum class EWaveTableSamplingMode : uint8`  
_L58-75_
- reflection: `UENUM()`
- desc: SamplingMode of a given bank or collection of WaveTables
- L65 _public enumerator_ `FixedSampleRate` — Enforces fixed sample rate for all members in the bank/collection, enabling them to be of unique duration/number of samples. Good for use cases when entries are being treated as separate, discrete but related audio to be played back at a shared speed (ex. traditional "samplers" or granulation).
- L72 _public enumerator_ `FixedResolution` — Enforces resolution (i.e. size of all tables), uniformly resampling all tables in the collection to be the same length/number of samples (if not already).  Supports use cases where systems are mixing/ interpolating or spatializing entries in lockstep (ex. oscillating or enveloping).
- L74 _public enumerator_ `COUNT UMETA(Hidden)`

#### struct `FWaveTableSettings`  
`struct FWaveTableSettings`  
_L79-153_
- reflection: `USTRUCT()`
- L85 _public member_ `FFilePath FilePath;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (FilePathFilter = "Audio Files (*.aif, *.aiff, *.flac, *.ogg, *.wav)|*.aif;*.aiff;*.flac;*.ogg;*.wav"))` — File to import
- L89 _public member_ `int32 ChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0"))` — Index of channel in file to build WaveTable from (wraps if channel is greater than number in file)
- L93 _public member_ `FWaveTableData SourceData;` — `UPROPERTY(EditAnywhere, Category = Options)` — Source data last imported from the source file
- L97 _public member_ `int32 SourceSampleRate = 48000;` — `UPROPERTY(VisibleAnywhere, Category = Options)` — Source sample rate from last imported source file
- L101 _public member_ `float Phase = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Percent to phase shift of table
- L105 _public member_ `float Top = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Percent to remove from beginning of sampled WaveTable.
- L109 _public member_ `float Tail = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Percent to remove from end of sampled WaveTable.
- L113 _public member_ `float FadeIn = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Percent to fade in over.
- L117 _public member_ `float FadeOut = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Percent to fade out over.
- L121 _public member_ `bool bNormalize = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayAfter = "SourceData"))` — Whether or not to normalize the WaveTable.
- L126 _public member_ `bool bRemoveOffset = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayAfter = "bNormalize"))` — Whether or not to remove offset from original file (analogous to "DC offset" in circuit theory).
- L129 _public function_ `bool ContainsEdit() const` — Whether or not an edit is contained to omit or modify source file's PCM data
- L138 _public prototype_ `void VersionPCMData();`
- L143 _public prototype_ `void GetEditSourceBounds(int32& OutSourceTopOffset, int32& OutSourceNumSamples) const;` — Returns the respective offset & number of samples that characterize the source data to apply light edits to.
- L146 _public prototype_ `TArrayView<const float> GetEditSourceView() const;` — `UE_DEPRECATED(5.3, "Source now supports multiple bit depths. Use 'GetEditSourceBounds' & apply to SourceData WaveTableData TArrayView in proper format using 'GetDataView'.")`
- L151 _private member_ `TArray<float> SourcePCMData;` — `UPROPERTY(meta = (Deprecated = "5.3", DeprecationMessage = "Migrated to FWaveTableData member 'SourceData' to support multiple bitdepths"))`

#### enum `EWaveTableCurve`  
`enum class EWaveTableCurve : uint8`  
_L156-178_
- reflection: `UENUM(BlueprintType)`
- L158 _public enumerator_ `Linear UMETA(DisplayName = "Linear (Ramp In)")`
- L159 _public enumerator_ `Linear_Inv UMETA(DisplayName = "Linear (Ramp Out)")`
- L160 _public enumerator_ `Exp UMETA(DisplayName = "Exponential")`
- L161 _public enumerator_ `Exp_Inverse UMETA(DisplayName = "Exponential (Inverse)")`
- L162 _public enumerator_ `Log UMETA(DisplayName = "Log")`
- L164 _public enumerator_ `Sin UMETA(DisplayName = "Sin (90 deg)")`
- L165 _public enumerator_ `Sin_Full UMETA(DisplayName = "Sin (360 deg)")`
- L166 _public enumerator_ `SCurve UMETA(DisplayName = "Sin (+/- 90 deg)")`
- L169 _public enumerator_ `Shared UMETA(DisplayName = "Curve Asset")` — Reference a shared curve asset
- L172 _public enumerator_ `Custom UMETA(DisplayName = "Custom")` — Design a custom curve unique to the owning transform
- L175 _public enumerator_ `File UMETA(DisplayName = "File")` — Generate WaveTable from audio file
- L177 _public enumerator_ `Count UMETA(Hidden)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WAVETABLE_API`
- L16 _namespace_ `namespace WaveTable`
- L19 _function_ `[[nodiscard]] static inline int32 RatioToIndex(float InRatio, int32 InArrayNum)` (scope `WaveTable`) — Converts a ratio [0.0, 1.0] to an index within the given number of array elements.
- L180 _namespace_ `namespace WaveTable`
- L183 _prototype_ `int32 GetWaveTableSize(EWaveTableResolution InWaveTableResolution, EWaveTableCurve InCurve, int32 InMaxPCMSize = INDEX_NONE);` (scope `WaveTable`) — `UE_DEPRECATED(5.3, "Removed from public API as banks now support different bit depths and sampling mode (i.e. sample count can no longer be conflated with generic size metric)")`

### `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableTransform.h` (Public)


#### struct `FWaveTableTransform`  
`struct FWaveTableTransform`  
_L17-142_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `virtual ~FWaveTableTransform() = default;`
- L25 _public member_ `EWaveTableCurve Curve = EWaveTableCurve::Linear;` — `UPROPERTY(EditAnywhere, Category = Input, BlueprintReadWrite, meta = (DisplayName = "Curve Type"))` — The curve to apply when transforming the output.
- L33 _public member_ `float Scalar = 2.5f;` — `UPROPERTY(EditAnywhere, Category = Input, BlueprintReadWrite, meta = (DisplayName = "Exponential Scalar", ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "10.0"))` — When curve set to log, exponential or exponential inverse, value is factor 'b' in following equations with output 'y' and input 'x': Exponential: y = x * 10^-b(1-x) Exponential (Inverse): y = ((x - 1) * 10^(-bx)) + 1 Logarithmic: y = b * log(x) + 1
- L37 _public member_ `FRichCurve CurveCustom;` — `UPROPERTY()` — Custom curve to apply if output curve type is set to 'Custom.'
- L41 _public member_ `TObjectPtr<UCurveFloat> CurveShared = nullptr;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Asset"), Category = Curve, BlueprintReadWrite)` — Asset curve reference to apply if output curve type is set to 'Shared.'
- L45 _protected member_ `FWaveTableData TableData;` — `UPROPERTY()`
- L51 _protected member_ `float Duration = 1.0f;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Duration (Sec)", Category = Input, ClampMin = "0.001", UIMin = "0.001"))` — Duration of curve or file.  Only valid if parent SampleRate is set and SamplingMode is set to 'FixedSampleRate' (If set to 'FixedResolution', duration is variable depending on the resolution (number of samples in the table data) and device's sample rate.
- L53 _protected function_ `virtual bool ShouldClampToNormalizedRange() const`
- L58 _public member_ `FWaveTableSettings WaveTableSettings;` — `UPROPERTY(EditAnywhere, Category = WaveTable)`
- L62 _public prototype_ `void Apply(float& InOutValue, bool bInBipolar = false) const;` — Applies transform to provided index value, setting it to the corresponding value.
- L64 _public function_ `float GetDuration() const`
- L68 _public prototype_ `void CopyToWaveTable(TArrayView<float> InOutTable, float& OutFinalValue, bool bInBipolar) const;` — `UE_DEPRECATED(5.3, "Use FWaveTableData version instead")`
- L71 _public prototype_ `void CreateWaveTable(TArray<float>& InOutTable, float& OutFinalValue, bool bInBipolar) const;` — `UE_DEPRECATED(5.3, "Use FWaveTableData version instead")`
- L77 _public prototype_ `void CopyToWaveTable(FWaveTableData& InOutTableData, bool bInBipolar) const;` — Copies a single, period [0.0, 1.0] to provided WaveTableData using this transform's curve. The size of the resulting WaveTable is the provided ArrayView's size. If curve is itself set to 'File' and internally cached as WaveTable, will re-sample using max value interpolation. Does *not* apply destructive edits from WaveTableSetting's source table data.
- L81 _public prototype_ `void CreateWaveTable(FWaveTableData& InOutTableData, bool bInBipolar) const;` — Creates WaveTableData from transform respective Curve settings. Applies destructive edits as provided by WaveTableSettings if curve set to 'File'.
- L83 _public function_ `static FName GetDurationPropertyName()`
- L89 _public function_ `void VersionTableData()` — Versions deprecated "WaveTable" property data to PCMData, to support serialization of different bit depths
- L112 _public prototype_ `void CacheCurve();` — Caches curve data.  Should a shared curve be selected, curve points are copied locally to CurveCustom and Curve type is set accordingly.  Can be used to both avoid keeping a uobject reference should the transform be used on a non-game thread and potentially to further customize a referenced curve locally.
- L114 _public prototype_ `const FWaveTableData& GetTableData() const;`
- L117 _public prototype_ `float GetFinalValue() const;` — `UE_DEPRECATED(5.3, "FinalValue has moved to TableData. Use property's FinalValue get accessor directly.")`
- L120 _public prototype_ `void SetFinalValue(float InValue);` — `UE_DEPRECATED(5.3, "FinalValue has moved to TableData and is read-only.")`
- L124 _public member_ `TArray<float> WaveTable;` — `UPROPERTY(meta = (Deprecated = "5.3", DeprecationMessage = "WaveTable data now supports multiple bit depths and has moved to TableData"))`
- L127 _public member_ `float FinalValue = 0.0f;` — `UPROPERTY(meta = (Deprecated = "5.3", DeprecationMessage = "WaveTable data now supports multiple bit depths and FinalValue has moved to TableData"))`
- L132 _private prototype_ `void SampleCurveBipolar(FWaveTableData& InOutTableData) const;` — Clamps & applies transform to provided values as bipolar signal
- L135 _private prototype_ `void SampleCurveUnipolar(FWaveTableData& InOutTableData) const;` — Clamps & applies transform to provided values as unipolar signal
- L138 _private prototype_ `void SampleWaveTableData(FWaveTableData& InOutTableData) const;` — Converts internal TableData to float bit rate if not and re-samples to fit into provided wavetable data.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVETABLE_API`
