# Plugins / MusicEnvironment

- module root: `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment`
- headers: 10; symbols: 314
- symbol kinds: class=15, enum=9, enumerator=42, externvar=1, function=49, macro=8, member=33, namespace=1, prototype=145, struct=9, typedef=2
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags, MovieScene, TimeManagement

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/FrameBasedMusicMap.h` (Public)


#### enum `FrameBasedMusicMap::ETripletQuantizationTicks`  
`enum ETripletQuantizationTicks : int32`  
_L19-27_
- L21 _public enumerator_ `ThirtysecondNoteTriplet = (MusicalTime::TicksPerQuarterNote / 4) / 3` — 80
- L22 _public enumerator_ `SixteenthNoteTriplet = (MusicalTime::TicksPerQuarterNote / 2) / 3` — 160
- L23 _public enumerator_ `EighthNoteTriplet = (MusicalTime::TicksPerQuarterNote) / 3` — 320
- L24 _public enumerator_ `QuarterNoteTriplet = (MusicalTime::TicksPerQuarterNote * 2) / 3` — 640
- L25 _public enumerator_ `HalfNoteTriplet = (MusicalTime::TicksPerQuarterNote * 4) / 3` — 1280
- L26 _public enumerator_ `WholeNoteTriplet = (MusicalTime::TicksPerQuarterNote * 8) / 3` — 2560

#### enum `FrameBasedMusicMap::EWholeQuantizationTicks`  
`enum EWholeQuantizationTicks : int32`  
_L29-39_
- L31 _public enumerator_ `ThirtysecondNote = MusicalTime::TicksPerQuarterNote / 8` — 120
- L32 _public enumerator_ `SixteenthNote = MusicalTime::TicksPerQuarterNote / 4` — 240
- L33 _public enumerator_ `EighthNote = MusicalTime::TicksPerQuarterNote / 2` — 480
- L34 _public enumerator_ `QuarterNote = MusicalTime::TicksPerQuarterNote` — 960
- L35 _public enumerator_ `HalfNote = MusicalTime::TicksPerQuarterNote * 2` — 1920
- L36 _public enumerator_ `WholeNote = MusicalTime::TicksPerQuarterNote * 4` — 3840
- L37 _public enumerator_ `Bar = std::numeric_limits<int32>::min()+1` — Ticks depends on Time Signature
- L38 _public enumerator_ `Beat = std::numeric_limits<int32>::min()+2` — Ticks depends on Time Signature

#### enum `FrameBasedMusicMap::EDottedQuantizationTicks`  
`enum EDottedQuantizationTicks : int32`  
_L41-49_
- L43 _public enumerator_ `DottedThirtysecondNote = (MusicalTime::TicksPerQuarterNote / 16) * 3` — 180
- L44 _public enumerator_ `DottedSixteenthNote = (MusicalTime::TicksPerQuarterNote / 8) * 3` — 360
- L45 _public enumerator_ `DottedEighthNote = (MusicalTime::TicksPerQuarterNote / 4) * 3` — 720
- L46 _public enumerator_ `DottedQuarterNote = (MusicalTime::TicksPerQuarterNote / 2) * 3` — 1440
- L47 _public enumerator_ `DottedHalfNote = (MusicalTime::TicksPerQuarterNote) * 3` — 2880
- L48 _public enumerator_ `DottedWholeNote = (MusicalTime::TicksPerQuarterNote) * 6` — 5760

#### enum `FrameBasedMusicMap::EBarBeatFormat`  
`enum class EBarBeatFormat`  
_L56-61_
- L58 _public enumerator_ `Position`
- L59 _public enumerator_ `Duration`
- L60 _public enumerator_ `NotAllowed` — Don't display bars.beats! Fall back to seconds.

#### struct `FGridInterval`  
`struct FGridInterval`  
_L64-78_
- L66 _public member_ `double IntervalStartTime;`
- L68 _public member_ `int32 IntervalTick;`
- L70 _public member_ `FMusicalTime MusicalTime;`
- L72 _public function_ `FGridInterval(double InIntervalStartTime, int32 InIntervalTick, FMusicalTime InMusicalTime)`

#### struct `FFrameBasedTempoPoint`  
`struct FFrameBasedTempoPoint`  
_L81-177_
- reflection: `USTRUCT()`
- L92 _public function_ `FFrameBasedTempoPoint()`
- L95 _public function_ `FFrameBasedTempoPoint(float InBpm, int32 InTick, float InAtMillisecond) : OnTick(InTick) , OnMs(InAtMillisecond)`
- L102 _public function_ `void SetBpm(float InBpm)`
- L107 _public function_ `bool IsNearlyEqual(const FFrameBasedTempoPoint& Other, float MsTolerance = UE_SMALL_NUMBER) const`
- L115 _public member_ `int32 MicrosecondsPerQuarterNote = 500000;` — `UPROPERTY()` — 120 bpm default.
- L117 _public member_ `int32 OnTick = 0;` — `UPROPERTY()`
- L119 _public member_ `float OnMs = 0.0;` — `UPROPERTY()`
- L121 _public function_ `float Bpm() const`
- L126 _public function_ `int32 MsToTick(float Ms) const`
- L139 _public function_ `int32 SecondsToTick(double Second) const`
- L144 _public function_ `double TickToSeconds(int32 Tick) const`
- L149 _public function_ `float TickToMs(int32 Tick) const`
- L160 _public function_ `static bool Equals(const TArray<FFrameBasedTempoPoint>& A, const TArray<FFrameBasedTempoPoint>& B)`

#### struct `FFrameBasedTimeSignature`  
`struct FFrameBasedTimeSignature`  
_L180-205_
- reflection: `USTRUCT()`
- L184 _public function_ `FFrameBasedTimeSignature()`
- L186 _public function_ `FFrameBasedTimeSignature(int32 InNumerator, int32 InDenominator) : Numerator(static_cast<int16>(InNumerator)) , Denominator(static_cast<int16>(InDenominator))`
- L192 _public member_ `int16 Numerator = 4;` — `UPROPERTY(EditAnywhere, Category="Time Signature")`
- L194 _public member_ `int16 Denominator = 4;` — `UPROPERTY(EditAnywhere, Category="Time Signature")`
- L196 _public function_ `bool operator==(const FFrameBasedTimeSignature& Other) const`
- L201 _public function_ `bool operator!=(const FFrameBasedTimeSignature& Other) const`

#### struct `FFrameBasedTimeSignaturePoint`  
`struct FFrameBasedTimeSignaturePoint`  
_L208-309_
- reflection: `USTRUCT()`
- L212 _public function_ `FFrameBasedTimeSignaturePoint()`
- L215 _public function_ `FFrameBasedTimeSignaturePoint(const FFrameBasedTimeSignature& InTimeSignature, int32 InOnBar, int32 InOnTick, double InOnFrame) : TimeSignature(InTimeSignature) , OnBar(InOnBar) , OnTick(InOnTick) , OnFrame(InOnFrame)`
- L223 _public function_ `bool IsNearlyEqual(const FFrameBasedTimeSignaturePoint& Other, double FrameTolerance = UE_DOUBLE_SMALL_NUMBER) const`
- L232 _public member_ `FFrameBasedTimeSignature TimeSignature;` — `UPROPERTY()`
- L234 _public member_ `int32 OnBar = 0;` — `UPROPERTY()`
- L236 _public member_ `int32 OnTick = 0;` — `UPROPERTY()`
- L238 _public member_ `double OnFrame = 0.0;` — `UPROPERTY()`
- L240 _public function_ `int32 TicksPerBeat() const`
- L245 _public function_ `int32 TicksPerBar() const`
- L250 _public function_ `FMusicalTime TickToMusicalTime(int32 InTick) const`
- L273 _public function_ `int32 MusicalTimeToTick(const FMusicalTime& MusicalTime) const`
- L279 _public function_ `int32 BarToTick(int32 Bar) const`
- L285 _public function_ `int32 BarBeatToTick(int32 Bar, float Beat) const`
- L292 _public function_ `static bool Equals(const TArray<FFrameBasedTimeSignaturePoint>& A, const TArray<FFrameBasedTimeSignaturePoint>& B)`

#### struct `FTempoTimeSignatureMarker`  
`struct FTempoTimeSignatureMarker`  
_L312-324_
- reflection: `USTRUCT()`
- L317 _public member_ `TOptional<FFrameBasedTimeSignaturePoint> TimeSigPoint;` — `UPROPERTY()`
- L320 _public member_ `TOptional<FFrameBasedTempoPoint> TempoPoint;` — `UPROPERTY()`
- L323 _public member_ `float Seconds = 0.f;` — `UPROPERTY()`

#### class `UFrameBasedMusicMap`  
`class UFrameBasedMusicMap : public UObject`  
_L327-600_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L332 _public function_ `UFrameBasedMusicMap() : FrameResolution(0,0)`
- L336 _public function_ `UFrameBasedMusicMap(const FFrameRate& InFrameResolution) : FrameResolution(InFrameResolution)`
- L342 _public function_ `UFrameBasedMusicMap(const FFrameRate& InFrameResolution, float InBpm, const FFrameBasedTimeSignature& TimeSignature) : FrameResolution(InFrameResolution)`
- L349 _public prototype_ `void SetFrameResolution(const FFrameRate& NewFrameResolution);`
- L351 _public prototype_ `void Init(float InBpm, const FFrameBasedTimeSignature& InTimeSignature);`
- L353 _public prototype_ `void SetInitialTempo(float Bpm);`
- L354 _public prototype_ `float GetInitialTempo() const;`
- L355 _public prototype_ `void SetInitialTimeSignature(const FFrameBasedTimeSignature& TimeSignature);`
- L356 _public prototype_ `FFrameBasedTimeSignature GetInitialTimeSignature() const;`
- L358 _public function_ `void Clear()`
- L364 _public function_ `bool IsEmpty() const`
- L365 _public function_ `bool IsSimple() const`
- L367 _public prototype_ `double GetFrame(const FMusicalTime& MusicalTime) const;`
- L368 _public prototype_ `double GetFrame(int32 AtBar) const;`
- L369 _public prototype_ `FFrameTime GetFrameTime(const FMusicalTime& MusicalTime) const;`
- L370 _public prototype_ `FFrameTime GetFrameTime(int32 AtBar, float AtBeat) const;`
- L371 _public prototype_ `FFrameTime GetFrameTime(double FractionalBar) const;`
- L372 _public prototype_ `FFrameTime GetFrameTime(int32 AtTick) const;`
- L374 _public prototype_ `double GetSeconds(const FMusicalTime& MusicalTime) const;`
- L375 _public prototype_ `double GetSeconds(int32 AtBar, float AtBeat = 0.0f) const;`
- L377 _public prototype_ `FString MakeBarBeatStringForFrame(double DecimalFrame, FrameBasedMusicMap::EBarBeatFormat BarBeatFormat) const;`
- L378 _public prototype_ `FString MakeBarBeatStringForFrameTime(const FFrameTime& Frame, FrameBasedMusicMap::EBarBeatFormat BarBeatFormat) const;`
- L379 _public prototype_ `FString MakeBarBeatStringForMusicalTime(const FMusicalTime& MusicalTime, FrameBasedMusicMap::EBarBeatFormat BarBeatFormat) const;`
- L380 _public prototype_ `FString MakeBarBeatStringForSeconds(double Seconds, FrameBasedMusicMap::EBarBeatFormat BarBeatFormat) const;`
- L382 _public prototype_ `FMusicalTime GetMusicalTime(int32 Tick) const;`
- L383 _public prototype_ `FMusicalTime GetMusicalTime(const FFrameTime& FrameTime) const;`
- L385 _public prototype_ `float GetTempoForFrame(double DecimalFrame) const;`
- L386 _public prototype_ `float GetTempoForFrameTime(const FFrameTime& FrameTime) const;`
- L387 _public prototype_ `float GetTempoForSeconds(double Seconds) const;`
- L389 _public prototype_ `FFrameBasedTimeSignature GetTimeSignatureForFrame(double DecimalFrame) const;`
- L390 _public prototype_ `FFrameBasedTimeSignature GetTimeSignatureForFrameTime(const FFrameTime& FrameTime) const;`
- L391 _public prototype_ `FFrameBasedTimeSignature GetTimeSignatureForSeconds(double Seconds) const;`
- L392 _public prototype_ `int32 GetBeatsInBar(int32 Bar) const;`
- L393 _public prototype_ `int32 GetTicksInBar(int32 Bar) const;`
- L395 _public prototype_ `FFrameTime RemapFrameTime(FFrameTime SourceTime, const UFrameBasedMusicMap* OldMap) const;`
- L397 _public prototype_ `FMusicalTime BarsToMusicalTime(double BarsFromStart) const;`
- L405 _public prototype_ `FMusicalTime Quantize(const FMusicalTime& MusicalTime, int32 QuantizationInterval, EQuantizeDirection Direction = EQuantizeDirection::Nearest) const;`
- L406 _public prototype_ `int32 QuantizeToTick(const FMusicalTime& MusicalTime, int32 QuantizationInterval, EQuantizeDirection Direction = EQuantizeDirection::Nearest) const;`
- L426 _public prototype_ `FMusicalTime Add(const FMusicalTime& MusicalTime, int32 QuantizationInterval) const;` — FMusicalTime Add(const FMusicalTime& MusicalTime, int32 QuantizationInterval) const; Increment the supplied MusicalTime by the specified QuantizationInterval. NOTE: This does NOT quantize anything. QuantizationInterval is just used as a convenient way to specify a musical subdivision. You can use any of the TripletQuantizationTicks, WholeQuantizationTicks, or DottedQuantizationTicks enum values. AND... you can negate them to go back in time. @param MusicalTime			Time to be added to @param QuantizationInterval	One of the values from... TripletQuantizationTicks WholeQuantizationTicks DottedQuantizationTicks
- L429 _public member_ `TArray<FFrameBasedTempoPoint> TempoMap;` — `UPROPERTY()`
- L431 _public member_ `TArray<FFrameBasedTimeSignaturePoint> BarMap;` — `UPROPERTY()`
- L433 _public member_ `FFrameRate FrameResolution;` — `UPROPERTY()`
- L444 _public prototype_ `void AddTimeSignature(int32 AtTick, int32 AtBar, int16 Numerator, int16 Denominator);` — Appends a time signature change to the end of the Bar Map. Ensures that this time signature change's tick is after the last one in the map @param AtTick @param AtBar @param Numerator @param Denominator
- L454 _public prototype_ `void AddTempo(int32 AtTick, float AtMs, float Bpm);` — Appends a tempo change to the end of the Ensures that this tempo change's tick is after the last one in the map @param AtTick @param AtMs @param Bpm
- L468 _public prototype_ `void InsertTimeSignature(int32 AtBar, int16 Numerator, int16 Denominator);` — Inserts a Time Signature change at the specified Bar, avoiding duplicates as needed. Time Signature changes after this point will recalculate their ticks and frame times to happen on the new bar lines based on the inserted time signature change This will not insert a time signature change if the same change already exists immediately before this one being inserted If there is the same time signature change immediately after this one being inserted, it will be removed. @param AtBar @param Numerator @param Denominator
- L481 _public prototype_ `void InsertTempo(int32 AtTick, float Bpm);` — Inserts a Tempo Change at the specified tick, avoiding duplicates as needed. Time signature and tempo changes after this point will recalculate their frame times and ms respectively based on the new tempo change This will not insert a tempo change if the same change already exits immediately before If the same tempo change exists immediately after this one being inserted, it will be removed @param AtTick @param Bpm
- L494 _public prototype_ `void InsertTimeSignature(FMusicalTime AtMusicalTime, const FFrameBasedTimeSignature& TimeSignature);` — Inserts a Time Signature change at the specified Bar of the Musical Time (ignoring beats), avoiding duplicates as needed. Time Signature changes after this point will recalculate their ticks and frame times to happen on the new bar lines based on the inserted time signature change This will not insert a time signature change if the same change already exists immediately before this one being inserted If there is the same time signature change immediately after this one being inserted, it will be removed. @param AtMusicalTime @param TimeSignature
- L507 _public prototype_ `void InsertTempo(FMusicalTime AtMusicalTime, float Bpm);` — Inserts a Tempo Change at the specified MusicalTime, avoiding duplicates as needed. Time signature and tempo changes after this point will recalculate their frame times and ms respectively based on the new tempo change This will not insert a tempo change if the same change already exits immediately before If the same tempo change exists immediately after this one being inserted, it will be removed @param AtMusicalTime @param Bpm
- L517 _public prototype_ `bool RemoveTimeSignature(int32 AtBar);` — Removes the time signature change at the specified bar, if it exists Time Signature changes after this point will recalculate their ticks and frame times to happen on the new bar lines based on the inserted time signature change @param AtBar @return true if a time signature change was removed
- L527 _public prototype_ `bool RemoveTempo(int32 AtTick);` — Removes the tempo change at the specified tick, if it exists Time signature and tempo changes after this point will recalculate their frame times and ms respectively based on the new tempo change @param AtTick @return true if the tempo change was removed
- L538 _public prototype_ `bool RemoveTimeSignature(FMusicalTime AtMusicalTime);` — Removes the time signature change at the specified Musical Time, if it exists Note: Time Signature changes only happen on bar bounderies. A Musical Time that is not on whole bare is guaranteed to fail @param AtMusicalTime @return true if a time signature change was removed
- L546 _public prototype_ `bool RemoveTempo(FMusicalTime AtMusicalTime);` — Removes the tempo change at the specified Musical Time, if it exists @param AtMusicalTime @return true if the tempo change was removed
- L552 _public prototype_ `bool HasTimeSignatureChange(int32 AtBar);` — @param AtBar @return true if there is a time signature change at the given bar
- L558 _public prototype_ `bool HasTempoChange(int32 AtTick);` — @param AtTick @return true if there is a tempo change at the given tick
- L564 _public prototype_ `bool HasTimeSignatureChange(FMusicalTime AtMusicalTime);` — @param AtMusicalTime @return true if there is a time signature change at the exact musical time
- L570 _public prototype_ `bool HasTempoChange(FMusicalTime AtMusicalTime);` — @param AtMusicalTime @return true if there is a tempo change at the exact musical time
- L573 _public prototype_ `void GatherSubdivisonsForTimespan(int32 StartTick, int32 EndTick, int32 QuantizationInterval, TArray<FGridInterval>& OutSubdivisions) const;`
- L575 _public prototype_ `void GatherBarsForTimespan(int32 StartBar, int32 EndBar, int32 QuantizationInterval, TArray<FGridInterval>& OutBars) const;`
- L577 _public prototype_ `void GetGridMetricsMusic(float InViewStartSeconds, float InViewEndSeconds, float PixelsPerSecond, float MinTickPx, float DesiredMajorTickPx, TArray<FGridInterval>& OutMajorIntervals, TArray<FGridInterval>& OutMinorIntervals) const;`
- L579 _public prototype_ `void ComputeGridSpacingAtTick(int32 TickToCompute, float DesiredMajorTickSeconds, int32& OutMajorIntervalTicks) const;`
- L581 _public prototype_ `void ComputeMinorGridSpacing(int32 StartTick, int32 EndTick, TArray<FGridInterval>& OutMinorIntervals) const;`
- L583 _public prototype_ `TArray<FFrameBasedTempoPoint> GetTempoMetrics(float InViewStartSeconds, float InViewEndSeconds) const;`
- L585 _public prototype_ `void GetTempoTimeSignatureMarkers(float InStartSeconds, float InEndSeconds, TArray<FTempoTimeSignatureMarker>& OutMarkers) const;`
- L588 _private prototype_ `const FFrameBasedTimeSignaturePoint* GetTimeSignaturePointForTick(int32 Tick) const;`
- L589 _private prototype_ `const FFrameBasedTimeSignaturePoint* GetTimeSignaturePointForBar(int32 Bar) const;`
- L590 _private prototype_ `const FFrameBasedTimeSignaturePoint* GetTimeSignaturePointForFrame(double DecimalFrame) const;`
- L591 _private prototype_ `const FFrameBasedTimeSignaturePoint* GetTimeSignaturePointForFrameTime(const FFrameTime& Frame) const;`
- L592 _private prototype_ `const FFrameBasedTimeSignaturePoint* GetTimeSignaturePointForSeconds(double Seconds) const;`
- L594 _private prototype_ `const FFrameBasedTempoPoint* GetTempoPointForTick(int32 Tick) const;`
- L595 _private prototype_ `const FFrameBasedTempoPoint* GetTempoPointForFrame(double DecimalFrame) const;`
- L596 _private prototype_ `const FFrameBasedTempoPoint* GetTempoPointForFrameTime(const FFrameTime& Frame) const;`
- L597 _private prototype_ `const FFrameBasedTempoPoint* GetTempoPointForSeconds(double Seconds) const;`
- L599 _private prototype_ `FString MakeBarBeatString(double DecimalFrame, const FFrameBasedTimeSignaturePoint* TimeSignature, const FFrameBasedTempoPoint* Tempo, FrameBasedMusicMap::EBarBeatFormat BarBeatFormat) const;`

#### enum `UFrameBasedMusicMap::EQuantizeDirection`  
`enum class EQuantizeDirection`  
_L399-404_
- L401 _public enumerator_ `Nearest = 0`
- L402 _public enumerator_ `Ceiling = 1`
- L403 _public enumerator_ `Floor = 2`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUSICENVIRONMENT_API`
- L17 _namespace_ `namespace FrameBasedMusicMap`
- L51 _prototype_ `FText GetQuantizationName(int32 Quantization);` (scope `FrameBasedMusicMap`)
- L52 _prototype_ `EQuartzCommandQuantization QuantiazationIntervalToQuartz(int32 Quantization);` (scope `FrameBasedMusicMap`)
- L54 _externvar_ `extern TArray<TSharedPtr<int32>> QuantizationOptionsSource;` (scope `FrameBasedMusicMap`)

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicClockSourceManager.h` (Public)


#### class `UMusicClockSourceManager`  
`class UMusicClockSourceManager : public UObject`  
_L14-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L20 _public prototype_ `TScriptInterface<IMusicEnvironmentClockSource> FindClock(const FGameplayTag& Tag, bool bExactMatch = true);` — `UFUNCTION(BlueprintCallable, Category="Music|Clock")`
- L23 _public prototype_ `void AddTaggedClock(const FGameplayTag& Tag, TScriptInterface<IMusicEnvironmentClockSource> InClock);` — `UFUNCTION(BlueprintCallable, Category="Music|Clock")`
- L24 _public prototype_ `void AddTaggedClock(const FGameplayTag& Tag, UObject* InClock);`
- L27 _public prototype_ `void RemoveTaggedClock(TScriptInterface<IMusicEnvironmentClockSource> InClock);` — `UFUNCTION(BlueprintCallable, Category="Music|Clock")`
- L28 _public prototype_ `void RemoveTaggedClock(UObject* InClock);`
- L31 _public prototype_ `void RemoveClockWithTag(const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category="Music|Clock")`
- L34 _public prototype_ `TScriptInterface<IMusicEnvironmentClockSource> GetGlobalMusicClockAuthority();` — `UFUNCTION(BlueprintCallable, Category="Music|Clock")`
- L37 _public prototype_ `bool PushGlobalMusicClockAuthority(TScriptInterface<IMusicEnvironmentClockSource> InClock);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L38 _public prototype_ `bool PushGlobalMusicClockAuthority(UObject* InClock);`
- L41 _public prototype_ `void RemoveGlobalClockAuthority(TScriptInterface<IMusicEnvironmentClockSource> InClock);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L42 _public prototype_ `void RemoveGlobalClockAuthority(UObject* InClock);`
- L45 _public prototype_ `void PopMusicClockAuthority();` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L48 _private member_ `TMap<FGameplayTag, TWeakInterfacePtr<IMusicEnvironmentClockSource>> TaggedClocks;`
- L49 _private member_ `TArray<TWeakInterfacePtr<IMusicEnvironmentClockSource>> GlobalClockSourceStack;`
- L51 _private prototype_ `void CleanMap();`
- L52 _private prototype_ `void CleanStack();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUSICENVIRONMENT_API`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicEnvironmentClockSource.h` (Public)


#### class `UMusicEnvironmentClockSource`  
`class UMusicEnvironmentClockSource : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: This class does not need to be modified.

#### class `IMusicEnvironmentClockSource`  
`class IMusicEnvironmentClockSource`  
_L24-40_
- L31 _public prototype_ `virtual void GetCurrentBarBeat(float& Bar, float& BeatInBar);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L33 _public prototype_ `virtual float GetPositionSeconds() const = 0;`
- L34 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime() const = 0;`
- L35 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime(const FMusicalTime& SourceSpaceOffset) const = 0;`
- L36 _public prototype_ `virtual int32 GetPositionAbsoluteTick() const = 0;`
- L37 _public prototype_ `virtual int32 GetPositionAbsoluteTick(const FMusicalTime& SourceSpaceOffset) const = 0;`
- L38 _public prototype_ `virtual FMusicalTime Quantize(const FMusicalTime& MusicalTime, int32 QuantizationInterval, UFrameBasedMusicMap::EQuantizeDirection Direction = UFrameBasedMusicMap::EQuantizeDirection::Nearest) const = 0;`
- L39 _public prototype_ `virtual bool CanAuditionInEditor() const = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUSICENVIRONMENT_API`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicEnvironmentMetronome.h` (Public)


#### class `UMusicEnvironmentMetronome`  
`class UMusicEnvironmentMetronome : public UMusicEnvironmentClockSource`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UMusicEnvironmentClockSource`
- desc: This class does not need to be modified.

#### class `IMusicEnvironmentMetronome`  
`class IMusicEnvironmentMetronome : public IMusicEnvironmentClockSource`  
_L25-62_
- inherits: `IMusicEnvironmentClockSource`
- desc: A music environment system that can spawn metronomes will have to return an instance of a UObject that implements this interface from its "MovieSceneMetronomeSpawner".
- L31 _public prototype_ `void SetMusicMap(UFrameBasedMusicMap* InMusicMap);`
- L33 _public prototype_ `virtual bool Initialize(UWorld* InWorld) = 0;`
- L34 _public prototype_ `virtual void Tick(float DeltaSeconds) = 0;`
- L35 _public prototype_ `virtual void Start(double FromSeconds = 0.0) = 0;`
- L36 _public prototype_ `virtual void Seek(double ToSeconds) = 0;`
- L37 _public prototype_ `virtual void Stop() = 0;`
- L38 _public prototype_ `virtual void Pause() = 0;`
- L39 _public prototype_ `virtual void Resume() = 0;`
- L41 _public prototype_ `bool SetTempo(float Bpm);`
- L42 _public prototype_ `virtual float GetCurrentTempo() const = 0;`
- L43 _public prototype_ `virtual double GetCurrentPositionSeconds() const = 0;`
- L45 _public prototype_ `void SetSpeed(float Speed);`
- L46 _public prototype_ `virtual float GetCurrentSpeed() const = 0;`
- L48 _public prototype_ `void SetVolume(float InVolumeLinear);`
- L49 _public prototype_ `virtual float GetCurrentVolume() const = 0;`
- L51 _public prototype_ `void SetMuted(bool bInMuted);`
- L52 _public prototype_ `virtual bool IsMuted() const = 0;`
- L55 _protected prototype_ `virtual void OnMusicMapSet() = 0;`
- L56 _protected prototype_ `virtual void OnSetSpeed(const float Speed) = 0;`
- L57 _protected prototype_ `virtual bool OnSetTempo(const float Bpm) = 0;`
- L58 _protected prototype_ `virtual void OnSetVolume(float NewVolumeLinear) = 0;`
- L59 _protected prototype_ `virtual void OnSetMuted(bool bNewMuted) = 0;`
- L61 _protected member_ `TStrongObjectPtr<UFrameBasedMusicMap> MusicMap;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUSICENVIRONMENT_API`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicEnvironmentModule.h` (Public)


#### class `FMusicEnvironmentModule`  
`class FMusicEnvironmentModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- desc: The public interface of the MusicEnvironment module
- L17 _public function_ `static inline FMusicEnvironmentModule& Get()`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicEnvironmentSubsystem.h` (Public)


#### class `UMusicEnvironmentSubsystem`  
`class UMusicEnvironmentSubsystem : public UEngineSubsystem`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", DisplayName = "MusicEnvironmentSubsystem")`
- inherits: `UEngineSubsystem`
- L25 _public prototype_ `static UMusicEnvironmentSubsystem& Get();`
- L28 _public prototype_ `UMusicClockSourceManager* GetClockSourceManager();` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L30 _public prototype_ `bool SetMetronomeClass(const UClass* InMetronomeType);`
- L33 _public prototype_ `bool CanSpawnMetronome() const;` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L36 _public prototype_ `virtual TScriptInterface<IMusicEnvironmentMetronome> SpawnMetronome(UObject* Outer, FName Name = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L40 _private member_ `TObjectPtr<UMusicClockSourceManager> ClockSourceManager;` — `UPROPERTY(Transient)`
- L43 _private member_ `TSoftClassPtr<UObject> MetronomeType;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUSICENVIRONMENT_API`
- L46 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicEnvironment, Log, All);`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicTypes/MusicHandle.h` (Public)


#### enum `EMusicHanldeClockValidity`  
`enum class EMusicHanldeClockValidity : uint8`  
_L41-45_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `ClockValid`
- L44 _public enumerator_ `ClockInvalid`

#### enum `EMusicHanldeTransportState`  
`enum class EMusicHanldeTransportState : uint8`  
_L48-55_
- reflection: `UENUM(BlueprintType)`
- L50 _public enumerator_ `PreparingToPlay`
- L51 _public enumerator_ `ReadyToPlay`
- L52 _public enumerator_ `Playing`
- L53 _public enumerator_ `Paused`
- L54 _public enumerator_ `Stale`

#### class `UMusicHandle`  
`class UMusicHandle : public UInterface`  
_L62-65_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: UMusicHandle: The UInterface derived class needed to support Unreal's interface system. This class definition stays empty.

#### class `IMusicHandle`  
`class IMusicHandle`  
_L75-141_
- desc: IMusicHandle: The actual pure virtual definition of the UMusicHandle interface. This is what derived classes will inherit from. AND... IMusicalAssets return TScriptInterface<IMusicHandle> when they are asked to instantiate themselves. BUT NOTE... If a non-UCLASS or a non-USTRUCT asks an IMusicalAsset to instantiate itself there may not be anything holding a strong reference to the object the script interface is pointing to. More on this below.
- L81 _public prototype_ `virtual bool IsValid() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L83 _public prototype_ `virtual void Tick(float DeltaSeconds) = 0;`
- L87 _public function_ `virtual bool IsReadyToPlay(float FromSeconds = 0.0f)` — `UFUNCTION(BlueprintCallable, Category = "Music")` — /  Transport
- L89 _public prototype_ `virtual bool Play(float FromSeconds = 0.0f) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L91 _public prototype_ `virtual void Pause() = 0;` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L93 _public prototype_ `virtual void Continue() = 0;` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L95 _public prototype_ `virtual void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L97 _public prototype_ `virtual void Kill();` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L99 _public function_ `operator bool()`
- L105 _public prototype_ `virtual void BranchOnTransportState(EMusicHanldeTransportState& Branches) const;` — `UFUNCTION(BlueprintCallable, Category = "Music", Meta = (ExpandEnumAsExecs = "Branches"))`
- L108 _public function_ `virtual EMusicHanldeTransportState GetTransportState() const` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L111 _public function_ `virtual bool IsUsingAsset(const TScriptInterface<IMusicalAsset> Asset) const` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L112 _public prototype_ `virtual bool IsUsingAsset(const UObject* Asset) const = 0;`
- L115 _public prototype_ `virtual TScriptInterface<IMusicEnvironmentClockSource> GetMusicClockSource() = 0;` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L118 _public prototype_ `virtual void GetCurrentBarBeat(float& Bar, float& BeatInBar, EMusicHanldeClockValidity& Branches);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock", Meta = (ExpandEnumAsExecs = "Branches"))`
- L121 _public prototype_ `virtual void BecomeGlobalMusicClockAuthority();` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L124 _public prototype_ `virtual void RelinquishGlobalMusicClockAuthority();` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L127 _public prototype_ `virtual void RegisterAsTaggedClock(const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L130 _public prototype_ `virtual void UnregisterAsTaggedClock(const FGameplayTag& Tag = FGameplayTag());` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock")`
- L133 _protected prototype_ `virtual void Stop_Internal() = 0;`
- L134 _protected prototype_ `virtual void Kill_Internal() = 0;`
- L136 _protected member_ `EMusicHanldeTransportState CurrentTransportState = EMusicHanldeTransportState::PreparingToPlay;`
- L139 _private member_ `bool IsOnGlobalClockAuthorityStack = false;`
- L140 _private member_ `FGameplayTagContainer RegisteredToTags;`

#### struct `FStrongMusicHandle`  
`struct FStrongMusicHandle`  
_L152-229_
- desc: FStrongMusicHandle: This wraps a TScriptInterface<IMusicHandle> to hold a TStrongObjectPtr to the UObject that implements the interface. It is like having a TStrongInterfacePtr<>, a type that doesn't exist in the engine. This allows non-UCLASS, non-USTRUCT things to hold music handles, and for the UStuff inside of those handles to not be garbage collected until the FStrongMusicHandle is destroyed.
- L155 _public prototype_ `inline FStrongMusicHandle() = default;`
- L156 _public prototype_ `inline FStrongMusicHandle(const FStrongMusicHandle& Other) = default;`
- L157 _public prototype_ `inline FStrongMusicHandle(FStrongMusicHandle&& Other) = default;`
- L158 _public prototype_ `inline ~FStrongMusicHandle() = default;`
- L159 _public prototype_ `inline FStrongMusicHandle& operator=(const FStrongMusicHandle& Other) = default;`
- L160 _public prototype_ `inline FStrongMusicHandle& operator=(FStrongMusicHandle&& Other) = default;`
- L169 _public function_ `FStrongMusicHandle(U&& MusicHandleObject)`
- L178 _public function_ `inline FStrongMusicHandle& operator=(FMusicHandle Other)`
- L189 _public function_ `inline FStrongMusicHandle& operator=(U& Other)`
- L202 _public function_ `inline FStrongMusicHandle& operator=(std::nullptr_t)`
- L209 _public function_ `inline IMusicHandle& operator*() const`
- L215 _public function_ `inline IMusicHandle* operator->() const`
- L221 _public function_ `operator bool() const`
- L227 _private member_ `TStrongObjectPtr<UObject> ObjectInstance;`
- L228 _private member_ `IMusicHandle* InterfaceInstance = nullptr;`

#### class `UMusicHandleBlueprintHelpers`  
`class UMusicHandleBlueprintHelpers : public UBlueprintFunctionLibrary`  
_L232-241_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L237 _public prototype_ `static void BranchOnTransportState(TScriptInterface<IMusicHandle> Handle, EMusicHanldeTransportState& Branches);` — `UFUNCTION(BlueprintCallable, Category = "Music", Meta = (ExpandEnumAsExecs = "Branches"))`
- L240 _public prototype_ `static EMusicHanldeTransportState GetTransportState(TScriptInterface<IMusicHandle> Handle);` — `UFUNCTION(BlueprintCallable, Category = "Music")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUSICENVIRONMENT_API`
- L143 _typedef_ `using FMusicHandle = TScriptInterface<IMusicHandle>;`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicTypes/MusicMapSource.h` (Public)


#### struct `FMarkerProviderEntry`  
`struct FMarkerProviderEntry`  
_L15-24_
- L17 _public member_ `FString Label;`
- L18 _public member_ `FFrameNumber FrameNumber;`
- L20 _public function_ `FMarkerProviderEntry(const FString& InLabel, FFrameNumber InFrameNumber) : Label(InLabel) , FrameNumber(InFrameNumber)`

#### struct `FMarkerProviderResults`  
`struct FMarkerProviderResults`  
_L27-44_
- reflection: `USTRUCT()`
- L41 _public function_ `bool IsEmpty() const`
- L43 _public member_ `TArray<FChannel> Channels;`

#### struct `FMarkerProviderResults::FChannel`  
`struct FChannel`  
_L31-39_
- L33 _public member_ `FString Name;`
- L34 _public member_ `TArray<FMarkerProviderEntry> Markers;`
- L36 _public function_ `FChannel(const FString& InName) : Name(InName)`

#### class `UMusicMapSource`  
`class UMusicMapSource : public UInterface`  
_L47-50_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMusicMapSource`  
`class IMusicMapSource`  
_L52-66_
- L59 _public function_ `virtual void CreateFrameBasedMusicMap(UFrameBasedMusicMap* Map) const` — `UFUNCTION()`
- L62 _public function_ `virtual FMarkerProviderResults GatherMarkers(const UFrameBasedMusicMap* Map) const` — `UFUNCTION()`
- L65 _public function_ `virtual float GetSongLengthSeconds() const` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUSICENVIRONMENT_API`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicTypes/MusicalAsset.h` (Public)


#### class `UMusicalAsset`  
`class UMusicalAsset : public UMusicMapSource`  
_L44-47_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UMusicMapSource`
- desc: UMusicalAsset: The UInterface derived class needed to support Unreal's interface system. This class definition stays empty.

#### class `IMusicalAsset`  
`class IMusicalAsset : public IMusicMapSource`  
_L55-86_
- inherits: `IMusicMapSource`
- desc: IMusicalAsset: The actual pure virtual definition of the interface. This is what derived classes will inherit from. It is an asset that has a FrameBasedMusicMap and can be played as music (returning a 'music handle' that becomes owned by the caller.)
- L61 _public prototype_ `virtual TScriptInterface<IMusicHandle> PrepareToPlay(UObject* PlaybackContext, UAudioComponent* OnComponent = nullptr, float FromSeconds = 0.0f, bool BecomeAuthoritativeClock = false, const FGameplayTag RegisterAsTaggedClock = FGameplayTag(), bool IsAudition = false);` — `UFUNCTION(BlueprintCallable, Category = "Music", Meta = (DefaultToSelf = "PlaybackContext"))`
- L69 _public prototype_ `virtual TScriptInterface<IMusicHandle> Play(UObject* PlaybackContext, UAudioComponent* OnComponent = nullptr, float FromSeconds = 0.0f, bool BecomeAuthoritativeClock = false, const FGameplayTag RegisterAsTaggedClock = FGameplayTag(), bool IsAudition = false);` — `UFUNCTION(BlueprintCallable, Category = "Music", Meta = (DefaultToSelf = "PlaybackContext"))`
- L77 _protected prototype_ `virtual TScriptInterface<IMusicHandle> PrepareToPlay_Internal(UObject* PlaybackContext, UAudioComponent* OnComponent = nullptr, float FromSeconds = 0.0f, bool IsAudition = false) = 0;`
- L82 _protected prototype_ `virtual TScriptInterface<IMusicHandle> Play_Internal(UObject* PlaybackContext, UAudioComponent* OnComponent = nullptr, float FromSeconds = 0.0f, bool IsAudition = false) = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUSICENVIRONMENT_API`
- L91 _typedef_ `using FMusicalAsset = TScriptInterface<IMusicalAsset>;` — FMusicalAsset: This is a convenience type definition.

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironment/Public/MusicTypes/MusicalEnums.h` (Public)


#### enum `EMusicalSyncPointCaptureMode`  
`enum class EMusicalSyncPointCaptureMode : uint8`  
_L8-15_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `DirectMapped UMETA(ToolTip="Bar 1 | Beat 1 of the level sequence is mapped directly to Bar 1 | Beat 1 of the driving music clock. If needed the sequence is 'seeked' to match the current time of the music clock.")`
- L11 _public enumerator_ `Immediate UMETA(ToolTip="Bar 1 | Beat 1 of the level sequence will be mapped to the current position of the music clock. Now quantization is done. While the sequence will advance in a locked-step, tempo matched way, its offset will be maintained. CAREFUL! You probably want to use some sort of qunatized capture.")`
- L12 _public enumerator_ `NearestQuantizedPosition UMETA(ToolTip="Bar 1 | Beat 1 of the level sequence is mapped to the NEAREST specified quantized musical subdivision. May be before or after the current musical time. Playback will start right away if the nearest subdivision is in the past, otherwise playback will start when the next subdivision arrives.")`
- L13 _public enumerator_ `NextQuantizedPosition UMETA(ToolTip="Bar 1 | Beat 1 of the level sequence is mapped to the NEXT specified quantized musical subdivision. Will be on or after the current musical time. Playback will start when that subdivision arrives.")`
- L14 _public enumerator_ `PreviousQuantizedPosition UMETA(ToolTip="Bar 1 | Beat 1 of the level sequence is mapped to the Previous specified quantized musical subdivision. Will be on or before the current musical time. Playback will start right away.")`

#### enum `EMusicalTimeSignatureRemapMode`  
`enum class EMusicalTimeSignatureRemapMode : uint8`  
_L18-24_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `None UMETA(ToolTip="No attempt is made to maintain 'bar synchronization' if there are mismatched time signature.")`
- L21 _public enumerator_ `ScaleBars UMETA(ToolTip="Scale each bar as necessary to match bar lengths in music clock.")`
- L22 _public enumerator_ `CropOrLoopBars UMETA(ToolTip="Crop or loop bars as necessary to align downbeats between the level sequence and the music clock.")`
- L23 _public enumerator_ `ScaleBeatsAndCropOrLoop UMETA(ToolTip="Scale beats to match music clock beat lengths, and THEN crop or loop bars as necessary to align downbeats between the level sequence and the music clock.")`
