# Plugins / HarmonixMidi

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMidi`
- headers: 25; symbols: 1181
- symbol kinds: class=16, enum=18, enumerator=153, function=279, macro=18, member=145, namespace=8, prototype=443, struct=40, typedef=5, union=1, variable=55
- PrivateDependencyModuleNames: AssetRegistry, AudioExtensions, Engine, Harmonix, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, MusicEnvironment, TimeManagement

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Internal/HarmonixMidi/VarLenNumber.h` (Internal)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Midi`
- L23 _namespace_ `namespace VarLenNumber` (scope `Midi`)
- L26 _function_ `template<typename STORAGE_T> int32 Write(STORAGE_T& Storage, int32 Value)` (scope `Midi::VarLenNumber`)
- L67 _function_ `template<typename STORAGE_T> int32 Read(STORAGE_T& Storage, int32* BytesConsumed = nullptr)` (scope `Midi::VarLenNumber`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Private/HarmonixMidi/Blueprint/MidiFunctionLibrary.h` (Private)


#### class `UMidiNoteFunctionLibrary`  
`class UMidiNoteFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library for FMidiNote and various midi note constants
- L26 _public function_ `static int MidiNoteToInt(const FMidiNote& InMidiNote)` — `UFUNCTION(BlueprintPure, Meta = (DisplayName = "FMidiNote To int64", CompactNodeTitle = "->", BlueprintAutocast), Category = "Midi")`
- L29 _public function_ `static FMidiNote IntToMidiNote(int InInt)` — `UFUNCTION(BlueprintPure, Meta = (DisplayName = "int64 to FMidiNote", CompactNodeTitle = "->", BlueprintAutocast), Category = "Midi")`
- L32 _public function_ `static uint8 MidiNoteToByte(const FMidiNote& InMidiNote)` — `UFUNCTION(BlueprintPure, Meta = (DisplayName = "FMidiNote To byte", CompactNodeTitle = "->", BlueprintAutocast), Category = "Midi")`
- L35 _public function_ `static FMidiNote ByteToMidiNote(uint8 InByte)` — `UFUNCTION(BlueprintPure, Meta = (DisplayName = "byte to FMidiNote", CompactNodeTitle = "->", BlueprintAutocast), Category = "Midi")`
- L38 _public function_ `static FMidiNote MakeLiteralMidiNote(FMidiNote Value)` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L41 _public prototype_ `static FMidiNote GetMinMidiNote();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L44 _public prototype_ `static FMidiNote GetMaxMidiNote();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L47 _public prototype_ `static uint8 GetMinNoteNumber();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L50 _public prototype_ `static uint8 GetMaxNoteNumber();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L53 _public prototype_ `static int GetMaxNumNotes();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L56 _public prototype_ `static uint8 GetMinNoteVelocity();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L59 _public prototype_ `static uint8 GetMaxNoteVelocity();` — `UFUNCTION(BlueprintPure, Category = "Midi")`

#### class `UMusicalTickFunctionLibrary`  
`class UMusicalTickFunctionLibrary : public UBlueprintFunctionLibrary`  
_L66-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library for converting Ticks to Beats and Beats to Ticks and other midi constants
- L73 _public prototype_ `static float GetTicksPerQuarterNote();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L76 _public prototype_ `static int GetTicksPerQuarterNoteInt();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L79 _public prototype_ `static float GetQuarterNotesPerTick();` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L82 _public prototype_ `static float TickToQuarterNote(float InTick);` — `UFUNCTION(BlueprintPure, Category = "Midi")`
- L85 _public prototype_ `static float QuarterNoteToTick(float InQuarterNote);` — `UFUNCTION(BlueprintPure, Category = "Midi")`

#### class `UMidiSongPosFunctionLibrary`  
`class UMidiSongPosFunctionLibrary : public UBlueprintFunctionLibrary`  
_L92-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library for FMidiSongPos
- L98 _public prototype_ `static bool IsSongPosValid(const FMidiSongPos& SongPos);` — `UFUNCTION(BlueprintPure, Category = "Midi", meta = (DisplayName = "Is MIDI Song Position Valid"))`
- L101 _public prototype_ `static FMidiSongPos LerpSongPos(const FMidiSongPos& A, const FMidiSongPos& B, float Alpha);` — `UFUNCTION(BlueprintPure, Category = "Midi", meta = (DisplayName = "Lerp (MIDI Song Position)"))`
- L104 _public prototype_ `static FMidiSongPos MakeSongPosFromTime(float TimeMs, float BeatsPerMinute, int32 TimeSignatureNumerator = 4, int32 TimeSignatureDenominator = 4, int32 StartBar = 1);` — `UFUNCTION(BlueprintPure, Category="Midi", meta=(NativeMakeFunc, DisplayName = "Make MIDI Song Position from Time"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Private/HarmonixMidi/SongMapReceiver.h` (Private)


#### class `FSongMapReceiver`  
`class FSongMapReceiver : public IMidiReceiver`  
_L7-61_
- inherits: `IMidiReceiver`
- L10 _public prototype_ `FSongMapReceiver(FSongMaps* Maps);`
- L11 _public prototype_ `virtual ~FSongMapReceiver() = default;`
- L13 _public prototype_ `virtual bool Reset() override;`
- L14 _public prototype_ `virtual bool Finalize(int32 InLastFileTick) override;`
- L17 _public prototype_ `virtual bool OnNewTrack(int32 NewTrackIndex) override;` — Track begin/end:
- L18 _public prototype_ `virtual bool OnEndOfTrack(int32 InLastTick) override;`
- L19 _public function_ `virtual bool OnAllTracksRead() override`
- L22 _public prototype_ `virtual bool OnMidiMessage(int32 Tick, uint8 Status, uint8 Data1, uint8 Data2) override;` — Standard 1- or 2-byte MIDI message:
- L23 _public prototype_ `virtual bool OnText(int32 Tick, const FString& Str, uint8 Type) override;`
- L24 _public prototype_ `virtual bool OnTempo(int32 Tick, int32 Tempo) override;`
- L25 _public prototype_ `virtual bool OnTimeSignature(int32 Tick, int32 Numerator, int32 Denominator, bool FailOnError = true) override;`
- L27 _public function_ `int32 GetLastTick()`
- L30 _private prototype_ `void ReadSectionTrackText(int32 Tick, const FString& Str);`
- L31 _private prototype_ `void ReadChordTrackText(int32 Tick, const FString& Str);`
- L32 _private prototype_ `void OnTrackName(const FString& TrackName);`
- L33 _private prototype_ `void OnStartSectionTrack();`
- L34 _private prototype_ `void OnStartChordTrack();`
- L35 _private prototype_ `void OnStartBeatTrack();`
- L37 _private prototype_ `FString FmtTick(int32 Tick) const;`
- L54 _private member_ `EMidiTrack CurrentTrack = EMidiTrack::UnknownTrack;`
- L55 _private member_ `int32 TrackIndex = -1;`
- L56 _private member_ `int32 LastBeatTick = -1;`
- L57 _private member_ `bool bHaveBeatFailure = false;`
- L58 _private member_ `int32 LastTick = 0;`
- L59 _private member_ `FSongMaps* SongMaps = nullptr;`
- L60 _private member_ `EMidiNoteAssignments LastBeatType = EMidiNoteAssignments::Invalid;`

#### enum `FSongMapReceiver::EMidiNoteAssignments`  
`enum class EMidiNoteAssignments`  
_L39-44_
- L40 _public enumerator_ `Invalid = -1`
- L41 _public enumerator_ `DetailedGridPitch = 11`
- L42 _public enumerator_ `StrongBeatPitch = 12`
- L43 _public enumerator_ `NormalBeatPitch = 13`

#### enum `FSongMapReceiver::EMidiTrack`  
`enum class EMidiTrack`  
_L46-52_
- L47 _public enumerator_ `UnknownTrack`
- L48 _public enumerator_ `FirstTrack`
- L49 _public enumerator_ `BeatTrack`
- L50 _public enumerator_ `SectionTrack`
- L51 _public enumerator_ `ChordTrack`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/BarMap.h` (Public)


#### struct `FMusicTimestamp`  
`struct FMusicTimestamp`  
_L15-81_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `int32 Bar = 1;` — `UPROPERTY(Category = "Music", EditAnywhere, BlueprintReadWrite)`
- L23 _public member_ `float Beat = 1.0f;` — `UPROPERTY(Category = "Music", EditAnywhere, BlueprintReadWrite)`
- L25 _public prototype_ `FMusicTimestamp() = default;`
- L26 _public function_ `FMusicTimestamp(int32 InBar, float InBeat) : Bar(InBar) , Beat(InBeat)`
- L32 _public function_ `bool IsValid() const`
- L37 _public function_ `void Reset()`
- L43 _public function_ `bool operator>=(const FMusicTimestamp& Other) const`
- L49 _public function_ `bool operator>(const FMusicTimestamp& Other) const`
- L55 _public function_ `bool operator==(const FMusicTimestamp& Other) const`
- L60 _public function_ `bool operator!=(const FMusicTimestamp& Other) const`
- L65 _public function_ `bool operator<(const FMusicTimestamp& Other) const`
- L71 _public function_ `bool operator<=(const FMusicTimestamp& Other) const`

#### struct `FTimeSignature`  
`struct FTimeSignature`  
_L85-118_
- reflection: `USTRUCT(BlueprintType)`
- desc: A simple container for a musical time signature (numerator and denominator.)
- L90 _public function_ `FTimeSignature() : Numerator(4) , Denominator(4)`
- L94 _public function_ `FTimeSignature(int32 InNumerator, int32 InDenominator) : Numerator(InNumerator) , Denominator(InDenominator)`
- L99 _public function_ `bool operator==(const FTimeSignature& Other) const`
- L104 _public function_ `bool operator!=(const FTimeSignature& Other) const`
- L110 _public member_ `int32 Numerator = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TimeSignature", meta=(ClampMin=1, ClampMax=99))`
- L112 _public member_ `int32 Denominator = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TimeSignature", meta=(ClampMin=1, ClampMax=99))`

#### struct `FTimeSignaturePoint`  
`struct FTimeSignaturePoint : public FMusicMapTimespanBase`  
_L122-168_
- reflection: `USTRUCT()`
- inherits: `FMusicMapTimespanBase`
- desc: A time signature associated with a specific tick in a midi file.
- L127 _public member_ `static constexpr bool DefinedAsRegions = false;`
- L129 _public function_ `FTimeSignaturePoint() : BarIndex(0) , BeatIndex(0) , TimeSignature(4, 4)`
- L134 _public function_ `FTimeSignaturePoint(int32 InBarIndex, int32 InBeatIndex, const FTimeSignature& InTimeSignature, int32 InStartTick, int32 InLengthTicks = 1) : FMusicMapTimespanBase(InStartTick, InLengthTicks) , BarIndex(InBarIndex) , BeatIndex(InBeatIndex) , TimeSignature(InTimeSignature)`
- L141 _public function_ `bool operator==(const FTimeSignaturePoint& Other) const`
- L149 _public member_ `int32 BarIndex;` — `UPROPERTY()` — 0 based since it is internal!
- L151 _public member_ `int32 BeatIndex;` — `UPROPERTY()` — 0 based since it is internal!
- L153 _public member_ `FTimeSignature TimeSignature;` — `UPROPERTY()`

#### struct `FTimeSignaturePoint::BarLessThan`  
`struct BarLessThan`  
_L155-160_
- L157 _public function_ `bool operator()(int32 InBarIndex, const FTimeSignaturePoint& Point) const`
- L158 _public function_ `bool operator()(const FTimeSignaturePoint& Point, int32 InBarIndex) const`
- L159 _public function_ `bool operator()(const FTimeSignaturePoint& PointA, const FTimeSignaturePoint& PointB) const`

#### struct `FTimeSignaturePoint::BeatLessThan`  
`struct BeatLessThan`  
_L162-167_
- L164 _public function_ `bool operator()(int32 InBeatIndex, const FTimeSignaturePoint& Point) const`
- L165 _public function_ `bool operator()(const FTimeSignaturePoint& Point, int32 InBeatIndex) const`
- L166 _public function_ `bool operator()(const FTimeSignaturePoint& PointA, const FTimeSignaturePoint& PointB) const`

#### struct `FBarMap`  
`struct FBarMap`  
_L172-444_
- reflection: `USTRUCT()`
- desc: A map of time signatures changes in a song.
- L177 _public function_ `FBarMap() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L180 _public prototype_ `bool operator==(const FBarMap& Other) const;`
- L182 _public prototype_ `void Empty();`
- L183 _public prototype_ `void Copy(const FBarMap& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L184 _public prototype_ `bool IsEmpty() const;`
- L186 _public prototype_ `int32 CalculateMidiTick(const FMusicTimestamp& Timestamp, const EMidiClockSubdivisionQuantization Quantize) const;`
- L188 _public prototype_ `int32 SubdivisionToMidiTicks(const EMidiClockSubdivisionQuantization Division, const int32 AtTick) const;`
- L191 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)` — Called by the midi file importer before map points are added to this map
- L196 _public function_ `int32 GetTicksPerQuarterNote() const`
- L198 _public function_ `void SupplyDefault()`
- L207 _public prototype_ `float MusicTimestampToTick(const FMusicTimestamp& Timestamp) const;` — Takes an FMusicTimestamp and computes the absolute (raw) total tick from the beginning of the midi data. Based on the time signature(s), StartBar, and TicksPerQuarterNote set when the map was created. @param Timestamp @return The 0-based absolute tick in the midi data.
- L218 _public prototype_ `FMusicTimestamp TickToMusicTimestamp(float Tick, int32* OutBeatsPerBar = nullptr) const;` — Takes an absolute tick and calculates a music timestamp. Uses the collection of time signatures, the setting of TicksPerQuarterNote, and the setting of StartBar to do its calculations. It will also optionally return the number of beats in the found bar, which is the numerator of the current time signature. @param Tick 0-based 'raw total ticks' @param OutBeatPerBar Is not nullptr it will be filled in with the number of total beats in the described bar. @return The FMusicTimestamp where Bar 1 Beat 1 is the "beginning of the song" after count-in and pickup bars.
- L230 _public prototype_ `FMusicTimestamp TickFromBarOneToMusicTimestamp(float Tick, int32* OutBeatsPerBar = nullptr) const;` — Takes an tick relative to "bar 1 beat 1" and calculates a music timestamp. Uses the collection of time signatures, the setting of TicksPerQuarterNote, and the setting of StartBar to do its calculations. It will also optionally return the number of beats in the found bar, which is the numerator of the current time signature. @param Tick 0-based tick offset from Bar 1. So Tick 0 will always be Bar 1 Beat 1 regarless of the length of the count-in or pickup bars. @param OutBeatPerBar Is not nullptr it will be filled in with the number of total beats in the described bar. @return The FMusicTimestamp where Bar 1 Beat 1 is the "beginning of the song" after count-in and pickup bars.
- L241 _public prototype_ `int32 MusicTimestampBarToTick(int32 BarNumber, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;` — Takes a "music timestamp" bar and computes the absolute (raw) total tick from the beginning of the midi data. Optionally returns the number of beats in that bar and the number of ticks per beat. @param BarNumber As would be returned in a MusicTimestamp, where Bar 1 is the "beginning of the music" after count-in and pickups. @param optional OutBeatsPerBar Number of beats in this bar (numerator of the time signature) @param optional OutTicksPerBeat Number of ticks per beat (based on the time signature denominator and the system's TTPQ) @return The 0-based absolute tick in the midi data.
- L252 _public prototype_ `int32 BarIncludingCountInToTick(int32 BarIndex, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;` — Takes a bar index and computes the absolute (raw) total tick from the beginning of the midi data. This is a '0' based bar from the beginning of the raw midi data with no reference to count-in or pickup data. Optionally returns the number of beats in that bar and the number of ticks per beat. @param BarIndex 0 based index of the bar @param optional OutBeatsPerBar Number of beats in this bar (numerator of the time signature) @param optional OutTicksPerBeat Number of ticks per beat (based on the time signature denominator and the system's TTPQ) @return The 0-based absolute tick in the midi data.
- L268 _public prototype_ `int32 MusicTimestampBarBeatTickToTick(int32 BarNumber, int32 BeatInBar, int32 TickInBeat) const;` — Take a bar, beat (1 based) within that bar, and tick (0 based) within that beat and computes the absolute (raw) total tick from the beginning of the  midi data. Based on the time signature(s), StartBar, and TicksPerQuarterNote. NOTE: Here, bar and beat are as one would find them in a FMusicTimestamp structure... bar 1 beat 1 is the beginning of the song. Bars before '1' are count-in or pickup bars. @param BarNumber Bar in question. Remember... songs start at bar 1 beat 1! @param BeatInBar 1-based beat in the bar. Given a time signature of x/y, there are 'x' beats in a bar, and each beat is 'y' in length. @param TickInBeat 0-based tick in the Beat. NOTE: The number of ticks in a beat depends on the length of the beat (the denominator in the time signature) and the map's ticks per quarter note. @return The 0-based absolute tick in the midi data.
- L282 _public prototype_ `int32 BarBeatTickIncludingCountInToTick(int32 BarIndex, int32 BeatInBar, int32 TickInBeat) const;` — Take a bar, beat (1 based) within that bar, and tick (0 based) within that beat and computes the absolute (raw) total tick from the beginning of the  midi data. Based on the time signature(s), and TicksPerQuarterNote. Here, bar is a 'raw' bar from the beginning of the midi data. There is no consideration of count-in or pickup bars. @param BarIndex Bar in question. The beginning of the midi data is bar 0! @param BeatInBar 1-based beat in the bar. Given a time signature of x/y, there are 'x' beats in a bar, and each beat is 'y' in length. @param TickInBeat 0-based tick in the Beat. NOTE: The number of ticks in a beat depends on the length of the beat (the denominator in the time signature) and the map's ticks per quarter note. @return The 0-based absolute tick in the midi data.
- L297 _public prototype_ `void TickToBarBeatTickIncludingCountIn(int32 RawTick, int32& OutBarIndex, int32& OutBeatInBar, int32& OutTickIndexInBeat, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;` — Take "raw" tick (tick from the beginning of the midi data and in units of TicksPerQuarterNote) and return a bar (0 based), beat in bar (1 based) within that bar, and tick (0 based) within that beat. Here, the returned position is a 'raw' position from the beginning of the midi data. There is no consideration of count-in or pickup bars. @param RawTick from the beginning of the midi data. @param OutBarIndex (output) @param OutBeatInBar (1 based!) (output) @param OutTickIndexInBeat (output) @param OutBeatsPerBar (output - optional) @param OutTicksPerBeat (output - optional)
- L308 _public prototype_ `float TickToFractionalBarIncludingCountIn(float Tick) const;` — Takes an absolute tick (from the beginning of the midi data) and calculates the fractional bar, where bar 0.0 is the beginning of the raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt @param Tick 0-based 'raw total ticks' @return The 0-based fractional bar index
- L319 _public prototype_ `float TickToFractionalBeatIncludingCountIn(float Tick) const;` — Takes an absolute tick (from the beginning of the midi data) and calculates the fractional beat, where beat 0.0 is the beginning of the raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt @param Tick 0-based 'raw total ticks' @return The 0-based fractional beat index
- L330 _public prototype_ `int32 TickToBarIncludingCountIn(int32 Tick) const;` — Takes an absolute tick (from the beginning of the midi data) and calculates the bar index, where bar 0 is the beginning of the raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt @param Tick 0-based 'raw total ticks' @return The 0-based integrer bar index
- L341 _public prototype_ `int32 TickToBeatIncludingCountIn(float Tick) const;` — Takes an absolute tick (from the beginning of the midi data) and calculates the beat index, where beat 0 is the beginning of the raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt @param Tick 0-based 'raw total ticks' @return The 0-based integral beat index
- L353 _public prototype_ `float FractionalBarIncludingCountInToTick(float FractionalBarIndex) const;` — Takes a fractional bar and returns the absolute tick. Note: Bar 0.0 is the beginning of raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt to do its calculations. Note: If the returned tick is negative it is BEFORE any authored midi content. @param FractionalBarIndex 0-based fractional bar @return The 0-based raw tick
- L365 _public prototype_ `float FractionalBeatIncludingCountInToTick(float FractionalBeatIndex) const;` — Takes a fractional beat and returns the absolute tick. Note: Beat 0.0 is the beginning of raw midi data. Uses the collection of time signatures and the setting of kTicksPerQuarterNoteInt to do its calculations. Note: If the returned tick is negative it is BEFORE any authored midi content. @param FractionalBeatIndex 0-based fractional bar @return The 0-based raw tick
- L376 _public prototype_ `bool AddTimeSignatureAtMusicTimestampBar(int32 BarNumber, int32 Numerator, int32 Denominator, bool SortNow = true, bool FailOnError = true);` — Adds a time signature at the specified position, in this case a bar number as one would find in an FMusicTimestamp. In other words, a BarNumber before '1' would be in the count-in or pickup. @param BarNumber Bar 1 is the "beginning of the song". Bars before '1' are count-in or pickup bars. @param Numerator TIme Signature Numerator @param Denominator Time Signature Denominator @param SortNow Whether to sort the time signature points immediately or wait. @param FailOnError If an error is detected halt execution.
- L387 _public prototype_ `bool AddTimeSignatureAtBarIncludingCountIn(int32 BarIndex, int32 InNumerator, int32 InDenominator, bool SortNow = true, bool FailOnError = true);` — Adds a time signature at the specified position, in this case a bar index indicating the bar index from the beginning of the raw midi data. @param BarIndex '0' based index of the bar where the time signature belongs. @param Numerator TIme Signature Numerator @param Denominator Time Signature Denominator @param SortNow Whether to sort the time signature points immediately or wait. @param FailOnError If an error is detected halt execution.
- L390 _public prototype_ `void WipeTimeSignaturePoints(int32 Tick);` — Remove every point from the given tick onward
- L392 _public prototype_ `int32 GetNumTimeSignaturePoints() const;`
- L394 _public prototype_ `int32 GetPointIndexForTick(int32 Tick) const;`
- L396 _public prototype_ `const FTimeSignaturePoint& GetTimeSignaturePoint(int32 Index) const;`
- L397 _public prototype_ `FTimeSignaturePoint& GetTimeSignaturePoint(int32 Index);`
- L399 _public prototype_ `const FTimeSignature& GetTimeSignatureAtTick(int32 InTick) const;`
- L401 _public prototype_ `const FTimeSignaturePoint* GetTimeSignaturePointForTick(int32 InTick) const;`
- L403 _public prototype_ `const FTimeSignature& GetTimeSignatureAtBar(int32 InBar) const;`
- L405 _public function_ `FORCEINLINE int32 GetTicksInBeatAfterPoint(int32 Index) const`
- L414 _public function_ `FORCEINLINE int32 GetTicksInBarAfterPoint(int32 Index) const`
- L423 _public prototype_ `void Finalize(int32 InLastTick);`
- L425 _public function_ `int32 GetTickOfBarOne() const`
- L427 _public function_ `void SetStartBar(int32 InStartBar)`
- L428 _public function_ `int32 GetStartBar() const`
- L431 _public function_ `const TArray<FTimeSignaturePoint>& GetTimeSignaturePoints() const` — Returns the time signature points for inspection.
- L433 _public prototype_ `int32 GetTimeSignatureChangePointTick(int32 PointIndex) const;`
- L437 _protected member_ `int32 StartBar = 1;` — `UPROPERTY()`
- L439 _protected member_ `int32 TicksPerQuarterNote;` — `UPROPERTY()`
- L441 _protected member_ `TArray<FTimeSignaturePoint> Points;` — `UPROPERTY()`
- L443 _protected member_ `static const FTimeSignaturePoint sDefaultTimeSignature;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMIDI_API`
- L77 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMusicTimestamp& InTimestamp)`
- L114 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FTimeSignature& InTimeSignature)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/BeatMap.h` (Public)


#### enum `EMusicalBeatType`  
`enum class EMusicalBeatType : uint8`  
_L12-17_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Downbeat = 0`
- L15 _public enumerator_ `Strong = 1`
- L16 _public enumerator_ `Normal = 2`

#### struct `FBeatMapPoint`  
`struct FBeatMapPoint : public FMusicMapTimespanBase`  
_L30-57_
- reflection: `USTRUCT()`
- inherits: `FMusicMapTimespanBase`
- desc: A point in the music representing a "beat". Type may be 'Downbeat', 'Strong', or 'Normal' beat. This is very useful for odd time signatures like 5/8 where the music's beat might be on the 1st and 3rd eighth notes or the 1st and 4th eighth notes
- L35 _public member_ `static constexpr bool DefinedAsRegions = true;`
- L37 _public function_ `FBeatMapPoint() : PulseBar(-1) , Type(EMusicalBeatType::Normal)`
- L42 _public function_ `FBeatMapPoint(EMusicalBeatType InType, int32 InStartTick, int32 InLengthTicks = 1) : FMusicMapTimespanBase(InStartTick, InLengthTicks) , PulseBar(0) , Type(InType)`
- L48 _public function_ `bool operator==(const FBeatMapPoint& Other) const`
- L54 _public member_ `int32 PulseBar;` — `UPROPERTY()`
- L56 _public member_ `EMusicalBeatType Type;` — `UPROPERTY()`

#### struct `FPulseBar`  
`struct FPulseBar`  
_L64-95_
- reflection: `USTRUCT()`
- desc: Pulse Bars are groupings of beats where the first beat in the group has been marked up as a 'Downbeat' type.
- L69 _public function_ `FPulseBar() : StartTick(0) , LengthTicks(0) , FirstIncludedBeatIndex(0) , LastIncludedBeatIndex(0)`
- L75 _public function_ `FPulseBar(int32 InStartTick, int32 InLengthTicks, int32 InFirstIncludedBeatIndex, int32 InLastIncludedBeatIndex) : StartTick(InStartTick) , LengthTicks(InLengthTicks) , FirstIncludedBeatIndex(InFirstIncludedBeatIndex) , LastIncludedBeatIndex(InLastIncludedBeatIndex)`
- L82 _public function_ `bool operator==(const FPulseBar& Other) const`
- L88 _public member_ `int32 StartTick;` — `UPROPERTY()`
- L90 _public member_ `int32 LengthTicks;` — `UPROPERTY()`
- L92 _public member_ `int32 FirstIncludedBeatIndex;` — `UPROPERTY()`
- L94 _public member_ `int32 LastIncludedBeatIndex;` — `UPROPERTY()`

#### struct `FBeatMap`  
`struct FBeatMap`  
_L101-159_
- reflection: `USTRUCT()`
- desc: A map of 'beats' in a piece of music.
- L106 _public function_ `FBeatMap() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L109 _public prototype_ `bool operator==(const FBeatMap& Other) const;`
- L111 _public prototype_ `void Empty();`
- L112 _public prototype_ `void Copy(const FBeatMap& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L113 _public prototype_ `bool IsEmpty() const;`
- L114 _public prototype_ `int32 GetNumMapPoints() const;`
- L117 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)` — Called by the midi file importer before map points are added to this map
- L122 _public prototype_ `void AddBeat(EMusicalBeatType Type, int32 Tick, bool SortNow = true);`
- L124 _public prototype_ `const FBeatMapPoint* GetPointInfoForTick(int32 Tick) const;`
- L126 _public prototype_ `int32 GetPointIndexForTick(int32 Tick) const;`
- L128 _public prototype_ `float GetFractionalBeatAtTick(float Tick) const;`
- L130 _public prototype_ `float GetFractionalTickAtBeat(float InBeat) const;`
- L132 _public prototype_ `EMusicalBeatType GetBeatTypeAtTick(int32 Tick) const;`
- L134 _public prototype_ `float GetBeatInPulseBarAtTick(float Tick) const;`
- L136 _public prototype_ `int32 GetNumBeatsInPulseBarAt(int32 Tick) const;`
- L139 _public prototype_ `bool IsDownbeat(float Beat) const;` — Is the specified "from count in" beat the first beat in its bar?
- L142 _public prototype_ `int32 FindDownbeatIndexAfterBeat(float Beat) const;` — Retrieve the first downbeat AFTER the specified "from count in" beat
- L145 _public prototype_ `int32 FindDownbeatIndexAtOrAfterBeat(float Beat) const;` — Retrieve the first downbeat ON OR AFTER the specified "from count in"  beat
- L147 _public prototype_ `const FBeatMapPoint& GetBeatPointInfo(int32 index) const;`
- L149 _public prototype_ `void Finalize(int32 LastTick);`
- L153 _protected member_ `int32 TicksPerQuarterNote;` — `UPROPERTY()`
- L155 _protected member_ `TArray<FBeatMapPoint> Points;` — `UPROPERTY()`
- L158 _protected member_ `TArray<FPulseBar> Bars;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMIDI_API`
- L19 _prototype_ `FString MusicalBeatTypeToString(EMusicalBeatType BeatType);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/Blueprint/MidiNote.h` (Public)


#### struct `FMidiNote`  
`struct FMidiNote`  
_L18-64_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "MIDI Note"))`
- desc: Helper struct for getting and assigning MidiNote values Uses custom detail customization and custom pins for convenience in Editor has a one property uint8 NoteNumber ranging from Midi::kMinNote to Midi::kMaxNote [0 - 127]
- L22 _public function_ `FMidiNote() : NoteNumber(60)`
- L24 _public function_ `FMidiNote(uint8 inValue) : NoteNumber(inValue)`
- L25 _public function_ `FMidiNote(int inValue) : NoteNumber(inValue < 0 ? 0 : inValue)`
- L26 _public function_ `FMidiNote(int8 inValue) : NoteNumber(inValue < 0 ? 0 : inValue)`
- L28 _public function_ `operator uint8()`
- L29 _public function_ `operator int8()`
- L30 _public function_ `operator int()`
- L32 _public function_ `bool operator==(const FMidiNote& rhs) const`
- L33 _public function_ `bool operator!=(const FMidiNote& rhs) const`
- L34 _public function_ `bool operator< (const FMidiNote& rhs) const`
- L35 _public function_ `bool operator> (const FMidiNote& rhs) const`
- L36 _public function_ `bool operator<=(const FMidiNote& rhs) const`
- L37 _public function_ `bool operator>=(const FMidiNote& rhs) const`
- L42 _public member_ `uint8 NoteNumber = 60;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi", meta=(ClampMin="0", ClampMax="127"))`
- L44 _public prototype_ `FText GetDisplayText() const;`
- L46 _public prototype_ `FName GetDisplayName() const;`
- L49 _public prototype_ `FString ToString() const;` — note names formated enharmonic stile sharp with octave number (eg. C#4)
- L52 _public prototype_ `static FMidiNote FromString(const FString& NoteName);` — takes a note name (eg C#4) and makes a FMidiNote struct from it
- L54 _public prototype_ `static uint8 NoteNumberFromString(const FString& NoteName);`
- L58 _public prototype_ `FString ToEditorString() const;`
- L60 _public prototype_ `static FMidiNote FromEditorString(const FString& EditorName);`
- L62 _public prototype_ `static uint8 NoteNumberFromEditorString(const FString& EditorName);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/ChordMap.h` (Public)


#### struct `FChordMapPoint`  
`struct FChordMapPoint : public FMusicMapTimespanBase`  
_L15-37_
- reflection: `USTRUCT()`
- inherits: `FMusicMapTimespanBase`
- desc: Specifies the tonality of a given section of music.
- L20 _public member_ `static constexpr bool DefinedAsRegions = false;`
- L22 _public function_ `FChordMapPoint()`
- L25 _public function_ `FChordMapPoint(FName ChordName, int32 InStartTick, int32 InLengthTicks = 1) : FMusicMapTimespanBase(InStartTick, InLengthTicks) , Name(ChordName)`
- L30 _public function_ `bool operator==(const FChordMapPoint& Other) const`
- L36 _public member_ `FName Name;` — `UPROPERTY()`

#### struct `FChordProgressionMap`  
`struct FChordProgressionMap`  
_L47-111_
- reflection: `USTRUCT()`
- desc: A collection of chords. Constructed when a standard midi file is imported and is seen to contain a 'chord track' that conforms to the Harmonix chord markup convention.
- L52 _public function_ `FChordProgressionMap() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L55 _public prototype_ `bool operator==(const FChordProgressionMap& Other) const;`
- L57 _public prototype_ `void Finalize(int32 LastTick);`
- L59 _public prototype_ `void Copy(const FChordProgressionMap& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L60 _public prototype_ `bool IsEmpty() const;`
- L63 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)` — Called by the midi file importer before map points are added to this map
- L73 _public prototype_ `void AddChord(FName Name, int32 StartTick, bool SortNow = false);` — Adds a chord at the specified position. Note: It DOES NOT take a duration or end tick! It is assumed to endure until the next existing chord or for the remainder of the song.
- L75 _public prototype_ `const FChordMapPoint* GetPointInfoForTick(int32 Tick) const;`
- L80 _public prototype_ `FName GetChordNameAtTick(int32 Tick) const;` — Returns the chord that applies to the specified Tick
- L82 _public function_ `int32 GetNumChords() const`
- L83 _public function_ `const TArray<FChordMapPoint>& GetChordList() const`
- L84 _public prototype_ `const void GetChordListCopy(TArray<FChordMapPoint>& ChordList) const;`
- L92 _public function_ `int32 GetTrack() const` — When the midi file importer finds a chord track, and constructs this map, it will set this map's ChordTrackIndex. This could be useful if you would like to parse the chord track yourself using the FMidiFile & FMidiTrack APIs, etc.
- L99 _public function_ `void SetTrack(int32 t)` — Called by the standard midi file importer when it finds a chord track in the data. If you construct the chord track yourself you may choose to set this index, but it isn't required.
- L101 _public prototype_ `void Empty();`
- L105 _protected member_ `int32 TicksPerQuarterNote;` — `UPROPERTY()`
- L107 _protected member_ `TArray<FChordMapPoint> Points;` — `UPROPERTY()`
- L110 _private member_ `int32 ChordTrackIndex = -1;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiConstants.h` (Public)


#### enum `Harmonix::Midi::Constants::EMidiTextEventEncoding`  
`enum class EMidiTextEventEncoding`  
_L14-18_
- L16 _public enumerator_ `Latin1`
- L17 _public enumerator_ `UTF8`

#### enum `Harmonix::Midi::Constants::EControllerID`  
`enum class EControllerID : uint8`  
_L123-196_
- desc: Controllers In a Control Change message, data byte 1 is the controller ID, and data byte 2 is the controller value.
- L126 _public enumerator_ `BankSelection = 0` — NOTE: If you add any here also add them to the GetControllerName function!
- L127 _public enumerator_ `ModWheel = 1`
- L128 _public enumerator_ `Breath = 2`
- L130 _public enumerator_ `PortamentoTime = 5`
- L131 _public enumerator_ `DataCoarse = 6`
- L132 _public enumerator_ `Volume = 7`
- L133 _public enumerator_ `Balance = 8`
- L134 _public enumerator_ `PanRight = 10`
- L135 _public enumerator_ `Expression = 11`
- L137 _public enumerator_ `BitCrushWetMix = 14`
- L138 _public enumerator_ `BitCrushLevel = 15`
- L139 _public enumerator_ `BitCrushSampleHold = 16`
- L141 _public enumerator_ `LFO0Frequency = 22`
- L142 _public enumerator_ `LFO1Frequency = 23`
- L143 _public enumerator_ `LFO0Depth = 24`
- L144 _public enumerator_ `LFO1Depth = 25`
- L146 _public enumerator_ `DelayTime = 26`
- L147 _public enumerator_ `DelayDryGain = 27`
- L148 _public enumerator_ `DelayWetGain = 28`
- L149 _public enumerator_ `DelayFeedback = 29`
- L151 _public enumerator_ `CoarsePitchBend = 30`
- L152 _public enumerator_ `SampleStartTime = 31`
- L153 _public enumerator_ `DataFine = 38`
- L155 _public enumerator_ `SubStreamVol1 = 52`
- L156 _public enumerator_ `SubStreamVol2 = 53`
- L157 _public enumerator_ `SubStreamVol3 = 54`
- L158 _public enumerator_ `SubStreamVol4 = 55`
- L159 _public enumerator_ `SubStreamVol5 = 56`
- L160 _public enumerator_ `SubStreamVol6 = 57`
- L161 _public enumerator_ `SubStreamVol7 = 58`
- L162 _public enumerator_ `SubStreamVol8 = 59`
- L164 _public enumerator_ `DelayEQEnabled = 60`
- L165 _public enumerator_ `DelayEQType = 61`
- L166 _public enumerator_ `DelayEQFreq = 62`
- L167 _public enumerator_ `DelayEQQ = 63`
- L169 _public enumerator_ `Hold = 64`
- L170 _public enumerator_ `PortamentoSwitch = 65`
- L171 _public enumerator_ `Sustenuto = 66`
- L172 _public enumerator_ `SoftPedal = 67`
- L173 _public enumerator_ `Legato = 68`
- L174 _public enumerator_ `Hold2 = 69`
- L175 _public enumerator_ `FilterQ = 71`
- L176 _public enumerator_ `Release = 72`
- L177 _public enumerator_ `Attack = 73`
- L178 _public enumerator_ `FilterFrequency = 74`
- L180 _public enumerator_ `TimeStretchEnvelopeOrder = 79`
- L182 _public enumerator_ `DelayLFOBeatSync = 80`
- L183 _public enumerator_ `DelayLFOEnabled = 81`
- L184 _public enumerator_ `DelayLFORate = 82`
- L185 _public enumerator_ `DelayLFODepth = 83`
- L187 _public enumerator_ `DelayStereoType = 84`
- L188 _public enumerator_ `DelayPanLeft = 85`
- L189 _public enumerator_ `DelayPanRight = 86`
- L191 _public enumerator_ `RPNFine = 100`
- L192 _public enumerator_ `RPNCourse = 101`
- L193 _public enumerator_ `AllSoundOff = 120`
- L194 _public enumerator_ `Reset = 121`
- L195 _public enumerator_ `AllNotesOff = 123`

#### enum `Harmonix::Midi::Constants::ENoteNameEnharmonicStyle`  
`enum class ENoteNameEnharmonicStyle : uint8`  
_L204-209_
- desc: allows choice between various naming conventions for enharmonic notes
- L206 _public enumerator_ `Sharp`
- L207 _public enumerator_ `Flat`
- L208 _public enumerator_ `SharpAndFlat`

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMIDI, Log, All);`
- L12 _namespace_ `namespace Harmonix`
- L12 _namespace_ `namespace Midi` (scope `Harmonix`)
- L12 _namespace_ `namespace Constants` (scope `Harmonix::Midi`)
- L27 _variable_ `inline constexpr uint8 GNumChannels = 16;` (scope `Harmonix::Midi::Constants`)
- L28 _variable_ `inline constexpr uint8 GNotesPerOctave = 12;` (scope `Harmonix::Midi::Constants`)
- L29 _variable_ `inline constexpr uint8 GMinNote = 0;` (scope `Harmonix::Midi::Constants`)
- L30 _variable_ `inline constexpr uint8 GMaxNote = 127;` (scope `Harmonix::Midi::Constants`)
- L31 _variable_ `inline constexpr uint8 GMaxNumNotes = 128;` (scope `Harmonix::Midi::Constants`)
- L32 _variable_ `inline constexpr uint8 GMinVelocity = 0;` (scope `Harmonix::Midi::Constants`)
- L33 _variable_ `inline constexpr uint8 GMaxVelocity = 127;` (scope `Harmonix::Midi::Constants`)
- L35 _variable_ `inline constexpr int32 GTicksPerQuarterNoteInt = 960;` (scope `Harmonix::Midi::Constants`)
- L36 _variable_ `inline constexpr float GTicksPerQuarterNote = 960.0f;` (scope `Harmonix::Midi::Constants`)
- L37 _variable_ `inline constexpr float GQuarterNotesPerTick = 1.0f / GTicksPerQuarterNote;` (scope `Harmonix::Midi::Constants`)
- L39 _variable_ `inline constexpr float GMinMidiFileTempo = 10.0f;` (scope `Harmonix::Midi::Constants`)
- L40 _variable_ `inline constexpr float GMaxMidiFileTempo = 960.0;` (scope `Harmonix::Midi::Constants`)
- L46 _variable_ `inline constexpr uint8 GFile_Escape = 0xf7;` (scope `Harmonix::Midi::Constants`) — Codes for special handling of System Exclusive messages:
- L47 _variable_ `inline constexpr uint8 GFile_SysEx = 0xf0;` (scope `Harmonix::Midi::Constants`)
- L50 _variable_ `inline constexpr uint8 GFile_Meta = 0xff;` (scope `Harmonix::Midi::Constants`) — Status code for SMF meta-events:
- L53 _variable_ `inline constexpr uint8 GMeta_Text = 0x01;` (scope `Harmonix::Midi::Constants`) — Meta-event IDs:
- L54 _variable_ `inline constexpr uint8 GMeta_Copyright = 0x02;` (scope `Harmonix::Midi::Constants`)
- L55 _variable_ `inline constexpr uint8 GMeta_TrackName = 0x03;` (scope `Harmonix::Midi::Constants`)
- L56 _variable_ `inline constexpr uint8 GMeta_InstrumentName = 0x04;` (scope `Harmonix::Midi::Constants`)
- L57 _variable_ `inline constexpr uint8 GMeta_Lyric = 0x05;` (scope `Harmonix::Midi::Constants`)
- L58 _variable_ `inline constexpr uint8 GMeta_Marker = 0x06;` (scope `Harmonix::Midi::Constants`)
- L59 _variable_ `inline constexpr uint8 GMeta_CuePoint = 0x07;` (scope `Harmonix::Midi::Constants`)
- L60 _variable_ `inline constexpr uint8 GMeta_ChannelPrefix = 0x20;` (scope `Harmonix::Midi::Constants`)
- L61 _variable_ `inline constexpr uint8 GMeta_Port = 0x21;` (scope `Harmonix::Midi::Constants`) — obsolete
- L62 _variable_ `inline constexpr uint8 GMeta_EndOfTrack = 0x2f;` (scope `Harmonix::Midi::Constants`)
- L63 _variable_ `inline constexpr uint8 GMeta_Tempo = 0x51;` (scope `Harmonix::Midi::Constants`)
- L64 _variable_ `inline constexpr uint8 GMeta_SMPTE = 0x54;` (scope `Harmonix::Midi::Constants`)
- L65 _variable_ `inline constexpr uint8 GMeta_TimeSig = 0x58;` (scope `Harmonix::Midi::Constants`)
- L66 _variable_ `inline constexpr uint8 GMeta_KeySig = 0x59;` (scope `Harmonix::Midi::Constants`)
- L67 _variable_ `inline constexpr uint8 GMeta_Special = 0x7f;` (scope `Harmonix::Midi::Constants`)
- L69 _prototype_ `FString GetMetaEventTypeName(uint8 Type);` (scope `Harmonix::Midi::Constants`)
- L73 _variable_ `inline constexpr uint8 GRuntimeAllNotesOffStatus = 0x01;` (scope `Harmonix::Midi::Constants`) — if FMidiMsg type is "Runtime" these are the possible status byte. note: runtime messages are not serialized!
- L74 _variable_ `inline constexpr uint8 GRuntimeAllNotesKillStatus = 0x02;` (scope `Harmonix::Midi::Constants`) — Receiver is expected to immediately free resources associated with any sounding notes and stop playing ASAP!
- L76 _prototype_ `FString GetTextTypeName(uint8 TextType);` (scope `Harmonix::Midi::Constants`)
- L82 _variable_ `inline constexpr uint8 GStatusBitMask = 0x80;` (scope `Harmonix::Midi::Constants`) — Masks for disassembling MIDI Status bytes
- L83 _variable_ `inline constexpr uint8 GMessageTypeMask = 0xf0;` (scope `Harmonix::Midi::Constants`) — mask for message type
- L84 _variable_ `inline constexpr uint8 GChannelMask = 0x0f;` (scope `Harmonix::Midi::Constants`) — mask for channel
- L85 _variable_ `inline constexpr uint8 GRealTimeMask = 0xf8;` (scope `Harmonix::Midi::Constants`) — indicates real-time Status message
- L87 _variable_ `inline constexpr uint8 GNoteOff = 0x80;` (scope `Harmonix::Midi::Constants`) — Note Off
- L88 _variable_ `inline constexpr uint8 GNoteOn = 0x90;` (scope `Harmonix::Midi::Constants`) — Note On
- L89 _variable_ `inline constexpr uint8 GPolyPres = 0xa0;` (scope `Harmonix::Midi::Constants`) — Polyphonic Key Pressure
- L90 _variable_ `inline constexpr uint8 GControl = 0xb0;` (scope `Harmonix::Midi::Constants`) — Control Change
- L91 _variable_ `inline constexpr uint8 GProgram = 0xc0;` (scope `Harmonix::Midi::Constants`) — Program Change (2 bytes)
- L92 _variable_ `inline constexpr uint8 GChanPres = 0xd0;` (scope `Harmonix::Midi::Constants`) — Channel Pressure (2 bytes)
- L93 _variable_ `inline constexpr uint8 GPitch = 0xe0;` (scope `Harmonix::Midi::Constants`) — Pitch Wheel Change
- L94 _variable_ `inline constexpr uint8 GSystem = 0xf0;` (scope `Harmonix::Midi::Constants`) — System
- L96 _function_ `inline bool IsStatus(uint8 Byte)` (scope `Harmonix::Midi::Constants`)
- L97 _function_ `inline uint8 GetType(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L99 _function_ `inline bool IsNoteOff(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L100 _function_ `inline bool IsNoteOn(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L101 _function_ `inline bool IsPolyPres(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L102 _function_ `inline bool IsControl(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L103 _function_ `inline bool IsProgram(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L104 _function_ `inline bool IsChanPres(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L105 _function_ `inline bool IsPitch(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L106 _function_ `inline bool IsSystem(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L108 _function_ `inline uint8 GetChannel(uint8 Status)` (scope `Harmonix::Midi::Constants`)
- L111 _function_ `inline float MidiTempoToBPM(int32 UsPerQuarterNote)` (scope `Harmonix::Midi::Constants`) — turns MIDI style tempo (microseconds per quarter note) into BPM...
- L112 _function_ `inline int32 BPMToMidiTempo(float Bpm)` (scope `Harmonix::Midi::Constants`)
- L113 _prototype_ `int32 SubdivisionToMidiTicks(const EMidiClockSubdivisionQuantization Division, const FTimeSignature& TimeSignature, const int32 TicksPerQuarterNote);` (scope `Harmonix::Midi::Constants`)
- L114 _prototype_ `float SubdivisionToBeats(EMidiClockSubdivisionQuantization Subdivision, const FTimeSignature& TimeSignature);` (scope `Harmonix::Midi::Constants`)
- L116 _prototype_ `float RoundToStandardBeatPrecision(float InBeat, int TimeSignatureDenominator);` (scope `Harmonix::Midi::Constants`)
- L198 _prototype_ `FString GetControllerName(EControllerID ControllerId);` (scope `Harmonix::Midi::Constants`)
- L199 _prototype_ `void GetControllerNames(TArray<FString>& Names);` (scope `Harmonix::Midi::Constants`)
- L201 _prototype_ `FString MakeStdMsgString(uint8 Status, uint8 Data1, uint8 Data2);` (scope `Harmonix::Midi::Constants`)
- L211 _prototype_ `int8 GetNoteNumberFromNoteName(const char* InName);` (scope `Harmonix::Midi::Constants`)
- L212 _prototype_ `const char* GetNoteNameFromNoteNumber(uint8 MidiNoteNumber, ENoteNameEnharmonicStyle Style = ENoteNameEnharmonicStyle::SharpAndFlat);` (scope `Harmonix::Midi::Constants`)
- L213 _prototype_ `int8 GetNoteOctaveFromNoteNumber(uint8 MidiNoteNumber);` (scope `Harmonix::Midi::Constants`)
- L219 _variable_ `inline constexpr uint8 GSys_Mtc = 0xf1;` (scope `Harmonix::Midi::Constants`) — System Common:
- L220 _variable_ `inline constexpr uint8 GSys_SongPos = 0xf2;` (scope `Harmonix::Midi::Constants`) — 3 byte message
- L221 _variable_ `inline constexpr uint8 GSys_SongSelect = 0xf3;` (scope `Harmonix::Midi::Constants`) — 2 byte message
- L222 _variable_ `inline constexpr uint8 GSys_TuneRequest = 0xf6;` (scope `Harmonix::Midi::Constants`) — 1 byte message
- L223 _variable_ `inline constexpr uint8 GSys_Eox = 0xf7;` (scope `Harmonix::Midi::Constants`) — 1 byte message
- L226 _variable_ `inline constexpr uint8 GSys_TimingClock = 0xf8;` (scope `Harmonix::Midi::Constants`) — System RealTime messages (all 1 byte)
- L227 _variable_ `inline constexpr uint8 GSys_Start = 0xfa;` (scope `Harmonix::Midi::Constants`)
- L228 _variable_ `inline constexpr uint8 GSys_Continue = 0xfb;` (scope `Harmonix::Midi::Constants`)
- L229 _variable_ `inline constexpr uint8 GSys_Stop = 0xfc;` (scope `Harmonix::Midi::Constants`)
- L230 _variable_ `inline constexpr uint8 GSys_ActiveSense = 0xfe;` (scope `Harmonix::Midi::Constants`)
- L231 _variable_ `inline constexpr uint8 GSys_Reset = 0xff;` (scope `Harmonix::Midi::Constants`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiCursor.h` (Public)


#### class `FMidiCursor`  
`class FMidiCursor`  
_L9-55_
- L12 _public member_ `static const int32 kAllTracks = -1;`
- L14 _public prototype_ `void Prepare(UMidiFile* InMidiFile, int32 TrackIndex = kAllTracks, bool bResetState = true);`
- L15 _public prototype_ `void Prepare(TSharedPtr<FMidiFileData> InMidiFile, int32 TrackIndex = kAllTracks, bool bResetState = true);`
- L17 _public function_ `int32 GetNextTick() const`
- L31 _public prototype_ `void SeekToNextTick(int32 NewNextTick, int32 PrerollBars = 0, FReceiver* PrerollReceiver = nullptr);`
- L32 _public prototype_ `int32 SeekToMs(float NewPositionMs, int32 PrerollBars = 0, FReceiver* PrerollReceiver = nullptr);`
- L34 _public prototype_ `void Process(int32 FirstTickToProcess, int32 LastTickToProcess, FReceiver& Receiver);`
- L42 _public prototype_ `void Preroll(int32 FirstTickToProcess, int32 LastTickToProcess, FReceiver& Receiver);` — Preroll is like process except it filters meaningless messages that happen in the provided span of ticks. For example: - If the span includes both a note-on AND a note-off for the same note on the same track those events are 'eaten' and not provided to the receiver. - Only the last time signature and tempo in the span will be sent. - etc.
- L44 _public prototype_ `bool PassedEnd() const;`
- L47 _private prototype_ `void UpdateNextTick(int32 NewNextTick);`
- L49 _private member_ `TSharedPtr<FMidiFileData> MidiFile;`
- L50 _private member_ `TArray<int32> TrackNextEventIndexs;`
- L51 _private member_ `float CurrentFileMs = 0.0f;`
- L52 _private member_ `int32 NextTick = 0;`
- L53 _private member_ `int32 LastTick = -1;`
- L54 _private member_ `int32 WatchTrack = -1;`

#### class `FMidiCursor::FReceiver`  
`class FReceiver`  
_L19-29_
- L23 _public function_ `virtual void OnMidiMessage(int32 TrackIndex, int32 Tick, uint8 Status, uint8 Data1, uint8 Data2, bool bIsPreroll)`
- L24 _public function_ `virtual void OnPreRollNoteOn(int32 TrackIndex, int32 EventTick, int32 Tick, float PreRollMs, uint8 Status, uint8 Data1, uint8 Data2)`
- L25 _public function_ `virtual void OnText(int32 TrackIndex, int32 Tick, int32 TextIndex, const FString& Str, uint8 Type, bool bIsPreroll)`
- L26 _public function_ `virtual void OnTempo(int32 TrackIndex, int32 Tick, int32 Tempo, bool bIsPreroll)`
- L27 _public function_ `virtual void OnTimeSig(int32 TrackIndex, int32 Tick, int32 Numerator, int32 Denominator, bool bIsPreroll)`
- L28 _public prototype_ `virtual bool HandleMessage(int32 TrackIndex, const FMidiTrack& Track, const FMidiEvent& Event, bool bIsPreroll);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiEvent.h` (Public)


#### struct `FMidiEvent`  
`struct FMidiEvent`  
_L17-69_
- reflection: `USTRUCT()`
- desc: An FMidiEvent is a container for a tick and a midi message.
- L23 _public function_ `FMidiEvent() : Tick(0)` — default construct for USTRUCT
- L27 _public prototype_ `FMidiEvent(int32 Tick, const FMidiMsg& InMessage);`
- L29 _public function_ `bool operator==(const FMidiEvent& Other) const`
- L35 _public prototype_ `void WriteStdMidi(FMidiWriter& Writer, const FMidiTrack& Track) const;` — Save the event out in standard midi file format
- L37 _public prototype_ `bool Serialize(FArchive& Archive);`
- L39 _public function_ `int32 GetTick() const`
- L40 _public function_ `bool IsText() const`
- L41 _public function_ `const FMidiMsg& GetMsg() const`
- L42 _public function_ `FMidiMsg& GetMsg()`
- L43 _public function_ `void SetMsg(const FMidiMsg& InMessage)`
- L45 _public function_ `bool operator < (const FMidiEvent& rhs) const`
- L54 _public function_ `explicit FORCEINLINE FMidiEvent(EForceInit FI) : Tick(0) , Message(FI)`
- L66 _private member_ `int32 Tick;` — `UPROPERTY()`
- L68 _private member_ `FMidiMsg Message;` — `UPROPERTY()`

#### struct `FMidiEvent::LessThan`  
`struct LessThan`  
_L47-52_
- L49 _public function_ `bool operator()(const FMidiEvent& Event, float InTick) const`
- L50 _public function_ `bool operator()(float InTick, const FMidiEvent& Event) const`
- L51 _public function_ `bool operator()(const FMidiEvent& EventA, const FMidiEvent& EventB) const`

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FMidiEvent> : public TStructOpsTypeTraitsBase2<FMidiEvent>`  
_L73-80_
- inherits: `TStructOpsTypeTraitsBase2<FMidiEvent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L76-79_

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMIDI_API`
- L77 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon9bb48e080103`)
- L78 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon9bb48e080103`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiFile.h` (Public)


#### struct `FMidiFileData`  
`struct FMidiFileData #if CPP : public ISongMapEvaluator #endif`  
_L22-101_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "MIDI File Data"))`
- inherits: `ISongMapEvaluator`
- L29 _public function_ `FMidiFileData() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L33 _public prototype_ `virtual ~FMidiFileData() = default;`
- L35 _public prototype_ `bool operator==(const FMidiFileData& Other) const;`
- L37 _public function_ `void Empty()`
- L46 _public function_ `bool IsEmpty() const`
- L55 _public member_ `FString MidiFileName;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiFile")`
- L57 _public member_ `int32 TicksPerQuarterNote;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiFile")`
- L59 _public member_ `FSongMaps SongMaps;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiFile")`
- L61 _public member_ `TArray<FMidiTrack> Tracks;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiFile")`
- L63 _public prototype_ `int32 GetLastEventTick() const;`
- L65 _public prototype_ `int32 FindTrackIndexByName(const FString& TrackName);`
- L67 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L69 _public prototype_ `bool ConformToLength(int32 NewLengthTicks);`
- L70 _public prototype_ `bool ConformToLengthGivenLastEventTick(int32 NewLastEventTick);`
- L77 _public prototype_ `void AddTempoChange(int32 TrackIdx, int32 Tick, float TempoBPM);` — Adds a tempo change to the midi data at the given tick for the given track idx asserts valid TrackIdx
- L87 _public prototype_ `void AddTimeSigChange(int32 TrackIdx, int32 Tick, int32 TimeSigNum, int32 TimeSigDenom);` — Adds a Time Signature change to the next bar boundary from the input tick for the given track Time signature changes can only happen at the beginning of a bar So input Tick will be rounded UP to the next bar boundary. asserts valid TrackIdx
- L89 _public prototype_ `void ScanTracksForSongLengthChange();`
- L91 _public prototype_ `bool LengthIsAPerfectSubdivision() const;`
- L94 _public function_ `virtual const FSongLengthData& GetSongLengthData() const override` — /  BEGIN ISongMapEvaluator Overrides ***********
- L95 _public function_ `virtual const FTempoMap& GetTempoMap() const override`
- L96 _public function_ `virtual const FBeatMap& GetBeatMap() const override`
- L97 _public function_ `virtual const FBarMap& GetBarMap() const override`
- L98 _public function_ `virtual const FSectionMap& GetSectionMap() const override`
- L99 _public function_ `virtual const FChordProgressionMap& GetChordMap() const override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMidiFileData> : public TStructOpsTypeTraitsBase2<FMidiFileData>`  
_L104-110_
- inherits: `TStructOpsTypeTraitsBase2<FMidiFileData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L107-109_

#### class `UMidiFile`  
`class UMidiFile : public UObject, public IAudioProxyDataFactory, public IMusicMapSource`  
_L119-265_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category="Music", Meta = (DisplayName = "Standard MIDI File"))`
- inherits: `UObject,IAudioProxyDataFactory,IMusicMapSource`
- desc: An FMidFile is primarily a container for FMidiTracks. This class can handle loading and saving standard midi files, as well as serializing itself to standard Unreal Engine FArchives.
- L124 _public typedef_ `using FMidiTrackList = TArray<FMidiTrack>;`
- L132 _public prototype_ `UMidiFile();`
- L137 _public prototype_ `bool operator==(const UMidiFile& Other) const;` — A comparison operator. This allows for differences in members related to how a midi file was generated/imported, but compares the underlying "renderable" midi data.
- L139 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L140 _public prototype_ `virtual void PostInitProperties() override;`
- L143 _public prototype_ `ELoadResult LoadStdMidiFile( const FString& FilePath, int32 DesiredTicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8, bool EnsureNotFailed = true);` — A method for importing a standard midi file, with the option of providing a pointer to an FSongMaps instance that will be populated during the load.
- L149 _public prototype_ `ELoadResult LoadStdMidiFile( void* Buffer, int32 BufferSize, const FString& FileName, int32 DesiredTicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8, bool EnsureNotFailed = true);` — A method for importing a standard midi file, with the option of providing a pointer to an FSongMaps instance that will be populated during the load.
- L157 _public prototype_ `ELoadResult LoadStdMidiFile( TSharedPtr<FArchive> Archive, const FString& Filename, int32 DesiredTicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8, bool EnsureNotFailed = true);` — A method for importing a standard midi file, with the option of providing a pointer to an FSongMaps instance that will be populated during the load.
- L165 _public prototype_ `void SaveStdMidiFile(const FString& FilePath) const;` — A method for exporting the midi track data to a standard midi file.
- L167 _public prototype_ `void SaveStdMidiFile(TSharedPtr<FArchive> Archive, const FString& Filename = FString()) const;` — A method for exporting the midi track data to a standard midi file.
- L170 _public prototype_ `virtual void CreateFrameBasedMusicMap(UFrameBasedMusicMap* Map) const override;` — /  BEGIN IMusicMapSource
- L171 _public prototype_ `virtual FMarkerProviderResults GatherMarkers(const UFrameBasedMusicMap* Map) const override;`
- L174 _public prototype_ `FMidiTrack* AddTrack(const FString& Name);`
- L176 _public prototype_ `void Empty();`
- L177 _public prototype_ `bool IsEmpty() const;`
- L179 _public prototype_ `void SortAllTracks();`
- L181 _public function_ `int32 GetNumTracks() const`
- L182 _public function_ `const FMidiTrack* GetTrack(int32 Index) const`
- L183 _public function_ `FMidiTrack* GetTrack(int32 Index)`
- L184 _public prototype_ `const FMidiTrack* FindTrackByName(const FString& TrackName) const;`
- L185 _public prototype_ `int32 FindTrackIndexByName(const FString& TrackName) const;`
- L188 _public prototype_ `int32 FindTextEvent(const FString& EventText, const FString* TrackName = nullptr);` — Find the text event and return the tick or -1 if not found.
- L190 _public prototype_ `int32 FindTextEvent(const FString& EventText, int32 TrackIndex);` — Find the text event and return the tick or -1 if not found.
- L193 _public prototype_ `TArray<int32> FindAllTextEvents(const FString& EventText, const FString* TrackName = nullptr);` — Find all the ticks at which the text event occurs
- L194 _public prototype_ `void FindAllTextEvents(const FString& EventText, int32 TrackIndex, TArray<int32> OutIndexes);`
- L196 _public function_ `FMidiTrackList& GetTracks()`
- L197 _public function_ `const FMidiTrackList& GetTracks() const`
- L199 _public prototype_ `void BuildConductorTrack();`
- L205 _public prototype_ `void ScanTracksForSongLengthChange();` — This function must be called if any changes are made to any of the tracks of this midi file. It will do various internal tasks necessary to assure the midi data is consistent and "playable".
- L207 _public function_ `int32 GetLastEventTick() const`
- L213 _public member_ `TObjectPtr<UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)` — Import data for this MidiFileAsset updated during Import in MidiFile
- L214 _public prototype_ `FString GetImportedSrcFilePath() const;`
- L218 _public member_ `int32 StartBar = 1;` — `UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Midi File Start Bar")` — The Start Bar of a Midi File
- L221 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — StartBar UPROPERTY callback
- L226 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L230 _public function_ `int32 GetStartBar()`
- L239 _public prototype_ `bool LengthIsAPerfectSubdivision() const;` — This does a quick and dirty to check to see if the length of the midi is on a musical subdivision. It is used primarily during asset importing, and if it returns true the importer will do further checking to see how far off it is, and suggest either conforming the length via QuantizeLengthToNearestPerfectSubdivision (for "off-by-one" type small errors) or QuantizeLengthToSubdivision (when the error is large and the user should choose a specific subdivision and direction for conforming the file.
- L241 _public prototype_ `void QuantizeLengthToNearestPerfectSubdivision(const EMidiFileQuantizeDirection Direction);`
- L243 _public prototype_ `void QuantizeLengthToSubdivision(const EMidiFileQuantizeDirection Direction, const EMidiClockSubdivisionQuantization Subdivision);`
- L245 _public prototype_ `bool ConformToLength(int32 NewLengthTicks);`
- L247 _public prototype_ `bool ConformToLengthGivenLastEventTick(int32 NewLastEventTick);`
- L249 _public function_ `const FSongMaps* GetSongMaps() const`
- L250 _public function_ `FSongMaps* GetSongMaps()`
- L252 _public prototype_ `TSharedPtr<FMidiFileData> GetOrCreateRenderableCopy();`
- L255 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;` — IAudioProxyDataFactory
- L258 _public prototype_ `void BeginDestroy() override;` — UObject
- L262 _protected member_ `FMidiFileData TheMidiData;` — `UPROPERTY()`
- L264 _protected member_ `TSharedPtr<FMidiFileData> RenderableCopyOfMidiFileData;`

#### enum `UMidiFile::ELoadResult`  
`enum class ELoadResult`  
_L126-130_
- L128 _public enumerator_ `Failed = 0`
- L129 _public enumerator_ `Success`

#### class `FMidiFileProxy`  
`class FMidiFileProxy : public Audio::TProxyData<FMidiFileProxy>`  
_L267-283_
- inherits: `Audio::TProxyData<FMidiFileProxy>`
- L270 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FMidiFileProxy);`
- L272 _public function_ `explicit FMidiFileProxy(TSharedPtr<FMidiFileData>& Data) : MidiFileDataPtr(Data)`
- L276 _public function_ `TSharedPtr<FMidiFileData> GetMidiFile()`
- L282 _private member_ `TSharedPtr<FMidiFileData> MidiFileDataPtr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARMONIXMIDI_API`
- L19 _typedef_ `using FMidiFileProxyPtr = TSharedPtr<FMidiFileProxy, ESPMode::ThreadSafe>;`
- L108 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon4bf6eb460103`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiMsg.h` (Public)


#### struct `FMidiMsg`  
`struct FMidiMsg`  
_L21-175_
- reflection: `USTRUCT()`
- desc: A class representing a single standard midi message. This class is tiny and tightly packed to keep the midi data footprint small on disk and in memory.
- L35 _public prototype_ `static FMidiMsg CreateNoteOn(int32 Channel, int32 Note, int32 Velocity);`
- L36 _public prototype_ `static FMidiMsg CreateNoteOff(int32 Channel, int32 Note);`
- L37 _public prototype_ `static FMidiMsg CreateControlChange(uint8 Channel, uint8 ControlNumber, uint8 Value);`
- L38 _public prototype_ `static FMidiMsg CreateText(uint16 InTextIndex, uint8 InTextType);`
- L39 _public prototype_ `static float GetPitchBendFromData(int8 Data1, int8 Data2);`
- L41 _public function_ `EType MsgType() const`
- L42 _public function_ `bool IsStd() const`
- L43 _public function_ `bool IsRuntime() const`
- L44 _public function_ `bool IsText() const`
- L45 _public function_ `bool IsNoteMessage() const`
- L46 _public function_ `bool IsNoteOn() const`
- L47 _public function_ `bool IsNoteOff() const`
- L51 _public function_ `bool IsAllNotesOff() const`
- L52 _public function_ `bool IsAllNotesKill() const`
- L53 _public function_ `bool IsControlChange() const`
- L54 _public function_ `bool IsTempo() const`
- L55 _public function_ `bool IsTimeSignature() const`
- L56 _public function_ `bool IsLyric() const`
- L57 _public function_ `bool IsSystemMessage() const`
- L60 _public prototype_ `FMidiMsg(uint8 InStatus, uint8 InData1, uint8 InData2);` — Construct a standard (std) midi message
- L61 _public function_ `uint8 GetStdStatus() const`
- L62 _public function_ `uint8 GetStdData1() const`
- L63 _public function_ `uint8 GetStdData2() const`
- L64 _public function_ `uint8 GetStdChannel() const`
- L65 _public function_ `uint8 GetStdStatusType() const`
- L66 _public prototype_ `float GetPitchBendFromData() const;`
- L69 _public prototype_ `FMidiMsg(int32 MicrosecPerQuarterNote);` — Construct a midi tempo message
- L70 _public function_ `int32 GetMicrosecPerQuarterNote() const`
- L77 _public prototype_ `FMidiMsg(uint8 Numerator, uint8 Denominator);` — Construct a midi time signature message
- L78 _public function_ `uint8 GetTimeSigNumerator() const`
- L79 _public function_ `uint8 GetTimeSigDenominator() const`
- L83 _public function_ `uint16 GetTextIndex() const` — Text Note: messages of this type are constructed using the subclass below.
- L84 _public function_ `uint8 GetTextType() const`
- L86 _public prototype_ `void SetNoteOnVelocity(uint8 Velocity);`
- L88 _public prototype_ `void WriteStdMidi(int32 Tick, FMidiWriter& writer, const FMidiTrack& track) const;`
- L90 _public prototype_ `static FString ToString(const FMidiMsg& Message, const FMidiTrack* Track = nullptr);`
- L92 _public prototype_ `bool Serialize(FArchive& Archive);`
- L94 _public function_ `explicit FORCEINLINE FMidiMsg(EForceInit) : Type(EType::Std) , Status(0) , Data1(0) , Data2(0)`
- L103 _public function_ `static FMidiMsg CreateAllNotesOff()` — Runtime Messages
- L110 _public function_ `static FMidiMsg CreateAllNotesKill()`
- L118 _public function_ `FMidiMsg() : Type(EType::Std) , Status(0) , Data1(0) , Data2(0)`
- L125 _public function_ `bool operator==(const FMidiMsg& Other) const`
- L137 _public member_ `EType Type;`

#### enum `FMidiMsg::EType`  
`enum class EType : uint8`  
_L26-33_
- L28 _public enumerator_ `Std = 1`
- L29 _public enumerator_ `Tempo = 2`
- L30 _public enumerator_ `TimeSig = 4`
- L31 _public enumerator_ `Text = 8`
- L32 _public enumerator_ `Runtime = 16`

#### union `FMidiMsg::(anonymous)`  
``  
_L147-174_

#### struct `FMidiMsg::__anona5ba124d010a::(anonymous)`  
``  
_L150-154_

#### struct `FMidiMsg::__anona5ba124d010a::(anonymous)`  
``  
_L157-160_

#### struct `FMidiMsg::__anona5ba124d010a::(anonymous)`  
``  
_L163-167_

#### struct `FMidiMsg::__anona5ba124d010a::(anonymous)`  
``  
_L170-173_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FMidiMsg> : public TStructOpsTypeTraitsBase2<FMidiMsg>`  
_L180-187_
- inherits: `TStructOpsTypeTraitsBase2<FMidiMsg>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L183-186_

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMIDI_API`
- L12 _typedef_ `using FMidiTextRepository = TArray<FString>;`
- L130 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMidiMsg& InMidiMsg)`
- L151 _member_ `uint8 Status;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0208`)
- L152 _member_ `uint8 Data1;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0208`)
- L153 _member_ `uint8 Data2;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0208`)
- L158 _member_ `uint8 MicsPerQuarterNoteH;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0308`)
- L159 _member_ `uint16 MicsPerQuarterNoteL;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0308`)
- L164 _member_ `uint8 Numerator;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0408`)
- L165 _member_ `uint8 Denominator;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0408`)
- L166 _member_ `uint8 ts_pad;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0408`)
- L171 _member_ `uint8 TextType;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0508`)
- L172 _member_ `uint16 TextIndex;` (scope `FMidiMsg::__anona5ba124d010a::__anona5ba124d0508`)
- L184 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anona5ba124d0603`)
- L185 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anona5ba124d0603`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiReader.h` (Public)


#### class `IMidiReader`  
`class IMidiReader`  
_L20-33_
- desc: A base class for Midi Readers so that IMidiReceivers can have a generic "back pointer" to the reader that is calling them.
- L23 _public prototype_ `virtual ~IMidiReader() = default;`
- L25 _public prototype_ `virtual const TSharedPtr<FBarMap> GetBarMap() const = 0;` — Called by a receiver when it wants to format a tick into an MBT for error messaging
- L26 _public prototype_ `virtual const FString& GetCurrentTrackName() const = 0;`
- L27 _public prototype_ `virtual int32 GetCurrentTrackIndex() const = 0;`
- L28 _public prototype_ `virtual const FString& GetFilename() const = 0;`
- L29 _public prototype_ `virtual int32 GetLastTick() const = 0;`
- L31 _public prototype_ `virtual void SkipCurrentTrack() = 0;` — Called by a receiver when it wants to skip to the next track
- L32 _public prototype_ `virtual bool IsFailed() const = 0;`

#### class `FStdMidiFileReader`  
`class FStdMidiFileReader : public IMidiReader`  
_L43-178_
- inherits: `IMidiReader`
- desc: A concrete IMidiReader implementation that can read standard midi files. You rarely have to interact with this class, as FMidiFile uses it internally when you use its LoadStdMidiFile functions. @see FMidiFile
- L46 _public prototype_ `FStdMidiFileReader( TSharedPtr<FArchive> Archive, const FString& InFilename, IMidiReceiver* InReceiver, int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8);`
- L52 _public prototype_ `FStdMidiFileReader( const FString& FilePath, IMidiReceiver* Receiver, int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8);`
- L57 _public prototype_ `FStdMidiFileReader( void* Buffer, int32 BufferSize, const FString& FileName, IMidiReceiver* Receiver, int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt, Harmonix::Midi::Constants::EMidiTextEventEncoding InTextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::UTF8);`
- L65 _public prototype_ `virtual ~FStdMidiFileReader() = default;`
- L67 _public prototype_ `void ReadAllTracks();` — Read all tracks
- L68 _public prototype_ `bool ReadSomeEvents(int32 NumEvents);`
- L69 _public prototype_ `bool ReadTrack();` — Read the next track, return false if no more
- L70 _public prototype_ `bool ReadEvents(int32 Count);` — Read some events, return false if no more
- L71 _public prototype_ `void SkipCurrentTrack() override;` — call this at any point to skip to the next track
- L74 _public function_ `virtual const FString& GetFilename() const override` — used by error reporting system
- L75 _public function_ `virtual int32 GetCurrentTrackIndex() const override`
- L76 _public function_ `virtual const FString& GetCurrentTrackName() const override`
- L77 _public function_ `virtual const TSharedPtr<FBarMap> GetBarMap() const override`
- L79 _public function_ `virtual int32 GetLastTick() const override`
- L81 _public function_ `virtual bool IsFailed() const override`
- L84 _private prototype_ `void Init();`
- L85 _private prototype_ `void ReadNextEvent();`
- L86 _private prototype_ `void ReadNextEventImpl();`
- L88 _private prototype_ `void ReadFileHeader();`
- L89 _private prototype_ `void ReadTrackHeader();`
- L90 _private prototype_ `void ReadEvent();`
- L91 _private prototype_ `void ReadMidiEvent(int32 Tick, uint8 Status, uint8 Data1);`
- L92 _private prototype_ `void ReadSystemEvent(int32 Tick, uint8 Status);`
- L93 _private prototype_ `void ReadMetaEvent(int32 Tick, uint8 Type);`
- L94 _private prototype_ `FString ReadText(int32 Length);`
- L97 _private prototype_ `void QueueChannelMsg(int32 Tick, uint8 Status, uint8 Data1, uint8 Data2);` — functions for sorting the midi before sending it out to the receivers
- L98 _private prototype_ `void ProcessMidiList();`
- L99 _private prototype_ `bool FailIfReadPositionIsPastTrackEnd();`
- L100 _private prototype_ `bool FailIfBytesNotAvailableInTrackData(int64 NumBytes);`
- L111 _private member_ `FString Filename;`
- L112 _private member_ `TSharedRef<FArchive> Archive;`
- L114 _private member_ `IMidiReceiver* Receiver = nullptr;`
- L115 _private member_ `Harmonix::Midi::Constants::EMidiTextEventEncoding TextEncoding = Harmonix::Midi::Constants::EMidiTextEventEncoding::Latin1;`
- L116 _private member_ `EState State = EState::Start;`
- L118 _private member_ `int32 DestinationTicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt;`
- L119 _private member_ `float TickConversionFactor = 1.0f;` — factor to convert from file's tick-per-quarternote to kTicksPerQuarterNote
- L121 _private member_ `int16 Format = 1;` — Format 0 or Format 1 standard midi file?
- L122 _private member_ `int16 NumTracks = 0;` — Number of tracks.
- L123 _private member_ `int64 LastTracksFilePosition;` — Position in the file of the current track's first byte.
- L124 _private member_ `int32 TrackEndPos = 0;` — end byte position of the current track
- L125 _private member_ `int32 CurrentFileTick = 0;` — Current tick in units of File's ticks-per-quarter.
- L126 _private member_ `int32 CurrentTick = 0;` — Current tick count for current track where one quarter note is TicksPerQuarterNote.
- L127 _private member_ `int32 LastTick = 0;`
- L128 _private member_ `uint8 PrevStatus = 0;` — Previous status byte (for running status).
- L129 _private member_ `int32 CurrentTrackIndex = -1;` — What track are we currently reading?
- L130 _private member_ `FString CurrentTrackName;`
- L132 _private member_ `inline static constexpr int32 kMaxSupportedMidiStringSize = 2048;`
- L140 _private member_ `ETrackFilteringMode TrackFilteringMode = ETrackFilteringMode::None;`
- L149 _private typedef_ `using FRawMidiList = TArray<FRawMidiMsg>;`
- L150 _private member_ `FRawMidiList EventsOnSameTick;` — a list of midi msgs all at the same tick (to be sorted)
- L151 _private member_ `int32 MidiListTick = 0;` — the tick of the messages in mMidiList
- L177 _private member_ `TSharedPtr<FBarMap> BarMap;` — we'll keep track of our own bar map so we can display more meaningful error/warning messages

#### enum `FStdMidiFileReader::EState`  
`enum class EState`  
_L102-109_
- L104 _public enumerator_ `Failed`
- L105 _public enumerator_ `Start` — at the very beginning (before MThd chunk)
- L106 _public enumerator_ `NewTrack` — at the beginning of a track (before MTrk chunk)
- L107 _public enumerator_ `InTrack` — in the middle of reading a track
- L108 _public enumerator_ `End` — done

#### enum `FStdMidiFileReader::ETrackFilteringMode`  
`enum class ETrackFilteringMode`  
_L134-139_
- L136 _public enumerator_ `None`
- L137 _public enumerator_ `ConductorEvents`
- L138 _public enumerator_ `NonConductorEvents`

#### struct `FStdMidiFileReader::FRawMidiMsg`  
`struct FRawMidiMsg`  
_L143-148_
- desc: stuff for sorting Midi messages on the same tick
- L145 _public member_ `uint8 Status;`
- L146 _public member_ `uint8 Data1;`
- L147 _public member_ `uint8 Data2;`

#### struct `FStdMidiFileReader::RawMidiLess`  
`struct RawMidiLess`  
_L152-173_
- L154 _public function_ `inline int32 MidiRank(uint8 Status) const`
- L169 _public function_ `bool operator()(const FStdMidiFileReader::FRawMidiMsg& lhs, const FStdMidiFileReader::FRawMidiMsg& rhs) const`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiReceiver.h` (Public)


#### class `IMidiReceiver`  
`class IMidiReceiver`  
_L23-76_
- L26 _public prototype_ `virtual ~IMidiReceiver() = default;`
- L29 _public prototype_ `virtual bool Reset() = 0;` — The reader is about to read a new MIDI file. Now is your chance to reset your state.
- L32 _public function_ `virtual bool SetNumTracks(int32 Num)` — Called when the reader has determined how many tracks are in the midi data
- L35 _public function_ `virtual bool Finalize(int32 InLastFileTick)` — called when all tracks have been read.
- L37 _public prototype_ `virtual bool OnNewTrack(int32 NewTrackIndex) = 0;`
- L38 _public prototype_ `virtual bool OnEndOfTrack(int32 LastTick) = 0;`
- L39 _public prototype_ `virtual bool OnAllTracksRead() = 0;`
- L42 _public prototype_ `virtual bool OnMidiMessage(int32 Tick, uint8 Status, uint8 Data1, uint8 Data2) = 0;` — For standard 1- or 2-byte MIDI message
- L48 _public prototype_ `virtual bool OnText(int32 Tick, const FString& Str, uint8 Type) = 0;` — Text, Copyright, TrackName, InstName, Lyric, Marker, CuePoint meta-event: "type" is the type of meta-event (constants defined in MidiConstants.h)
- L54 _public function_ `virtual bool OnTempo(int32 Tick, int32 Tempo)` — Tempo Change meta - event: tempo is in microseconds per quarter-note
- L59 _public function_ `virtual bool OnTimeSignature(int32 Tick, int32 Numerator, int32 Denominator, bool FailOnError = true)` — Time Signature meta - event: time signature is numerator/denominator
- L67 _public function_ `virtual void SetMidiReader(IMidiReader* InReader)` — Called by the reader before it starts processing the midi data stream. This saves off a back pointer that is very useful for things like writing good error messages when a receiver encounters unexpected data, or for telling the reader to skip the current track and move on.
- L70 _public prototype_ `void SkipCurrentTrack();` — Tells the reader to Skip the rest of this track and go to the next one
- L72 _public function_ `const IMidiReader* GetReader() const`
- L75 _protected member_ `IMidiReader* Reader = nullptr;`

#### class `FMidiReceiverList`  
`class FMidiReceiverList : public IMidiReceiver`  
_L87-170_
- inherits: `IMidiReceiver`
- desc: An implementation of IMidiReceiver that allows one to parse a midi file and send the found data to many receivers at the same time. Again, this can be very useful if a game has multiple systems that want to build their own runtime data based on data found in a standard midi file. @see IMidiReceiver
- L91 _public function_ `virtual bool Reset()`
- L98 _public function_ `virtual bool Finalize(int32 LastFileTick)`
- L105 _public function_ `virtual bool OnNewTrack(int32 NewTrackIndex)`
- L112 _public function_ `virtual bool OnEndOfTrack(int32 LastTick)`
- L119 _public function_ `virtual bool OnAllTracksRead()`
- L126 _public function_ `virtual bool OnMidiMessage(int32 Tick, uint8 Status, uint8 Data1, uint8 Data2)`
- L133 _public function_ `virtual bool OnText(int32 Tick, const FString& Str, uint8 Type)`
- L140 _public function_ `virtual bool OnTempo(int32 Tick, int32 Tempo)`
- L147 _public function_ `virtual bool OnTimeSignature(int32 Tick, int32 Numerator, int32 Denominator, bool FailOnError = true)`
- L154 _public function_ `virtual void SetMidiReader(IMidiReader* InReader)`
- L161 _public function_ `void Add(IMidiReceiver* recvr)`
- L163 _public function_ `void Empty()`
- L165 _public function_ `int32 Num()`
- L168 _private member_ `TArray<IMidiReceiver*> ReceiverList;`

#### Free symbols / members of external scopes

- L89 _macro_ `#define _FOR_EACH_MIDI_RECEIVER(func_body) Algo::ForEach(ReceiverList, [&](IMidiReceiver* recvr){ if (Result) func_body });`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiSongPos.h` (Public)


#### struct `FMidiSongPos`  
`struct FMidiSongPos`  
_L19-123_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "MIDI Song Position"))`
- desc: Position within a song (midi info)
- L26 _public member_ `float SecondsFromBarOne = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Total seconds from bar 1 beat 1. (negative for count-in and/or pickup bars)
- L30 _public member_ `float SecondsIncludingCountIn = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Total seconds from the beginning of the musical content (ie. includes all count-in and pickup bars)
- L34 _public member_ `int32 TimeSigNumerator = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Time Signature Numerator (Indicates Number of Beats Per Bar)
- L38 _public member_ `int32 TimeSigDenominator = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Time Signature Numerator (Indicates Subdivision of Bar that counts as 1 beat (4 means Quarter Note = One Beat))
- L42 _public member_ `float Tempo = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Tempo in Quarter Notes Per Minute (BPM)
- L45 _public member_ `float BarsIncludingCountIn = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Total bars from the beginning of the song.
- L49 _public member_ `float BeatsIncludingCountIn = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Total beats from the beginning of the song.
- L57 _public member_ `EMusicalBeatType BeatType = EMusicalBeatType::Normal;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — Whether this beat is a Downbeat (beat 1 of the current bar) or otherwise This value is determined by the authored content Defaults to "Normal"
- L61 _public member_ `FMusicTimestamp Timestamp;` — `UPROPERTY(BlueprintReadOnly, Category = "MidiSongPosition")` — The Musical Timestamp: Bar Number and Beat Number within the bar (Bar 1 Beat 1.0f)
- L63 _public member_ `FSongSection CurrentSongSection;`
- L78 _public prototype_ `void SetByTime(float InElapsedMs, float Bpm, int32 TimeSigNum = 4, int32 TimeSigDenom = 4, int32 StartBar = 1);` — This version is for use when song maps are unavailable. StartBar can be used if you know the content has, or will have, etc. a pickup or count-in. So for example... If tempo = 60 bpm, time signature = 4/4, and StartBar = -1 (two bars or count-in, bars -1 and 0), then... InElapsedMs = 0000.0 --> Seconds = -8, ElapsedBars = 0.00, MusicPosition.Bar = -1, MusicPosition.Beat = 1 InElapsedMs = 1000.0 --> Seconds = -7, ElapsedBars = 0.25, MusicPosition.Bar = -1, MusicPosition.Beat = 2 InElapsedMs = 2000.0 --> Seconds = -6, ElapsedBars = 0.50, MusicPosition.Bar = -1, MusicPosition.Beat = 3 InElapsedMs = 3000.0 --> Seconds = -5, ElapsedBars = 0.75, MusicPosition.Bar = -1, MusicPosition.Beat = 4 InElapsedMs = 4000.0 --> Seconds = -4, ElapsedBars = 1.00, MusicPosition.Bar =  0, MusicPosition.Beat = 1 InElapsedMs = 5000.0 --> Seconds = -3, ElapsedBars = 1.25, MusicPosition.Bar =  0, MusicPosition.Beat = 2 InElapsedMs = 6000.0 --> Seconds = -2, ElapsedBars = 1.50, MusicPosition.Bar =  0, MusicPosition.Beat = 3 InElapsedMs = 7000.0 --> Seconds = -1, ElapsedBars = 1.75, MusicPosition.Bar =  0, MusicPosition.Beat = 4 InElapsedMs = 8000.0 --> Seconds =  0, ElapsedBars = 2.00, MusicPosition.Bar =  1, MusicPosition.Beat = 1 etc.
- L80 _public prototype_ `void SetByTime(float InElapsedMs, const ISongMapEvaluator& Map);`
- L84 _public prototype_ `void SetByTick(float Tick, const ISongMapEvaluator& Map);` — Low-level version for midi players / parsers that use the low-level "midi tick system" for advancing song position.
- L86 _public function_ `void Reset()`
- L102 _public prototype_ `float GetBeatsPerMinute() const;` — Tempo converted from Quarter Notes to our Beats, only valid if TimeSigDenominator is set.
- L104 _public function_ `float GetBeatsPerSecond() const`
- L107 _public function_ `bool IsValid() const` — Has this been set by a system yet, or is it in the default state?
- L110 _public prototype_ `bool operator<(const FMidiSongPos& rhs) const;` — operators
- L111 _public prototype_ `bool operator<=(const FMidiSongPos& rhs) const;`
- L112 _public prototype_ `bool operator>(const FMidiSongPos& rhs) const;`
- L113 _public prototype_ `bool operator>=(const FMidiSongPos& rhs) const;`
- L114 _public prototype_ `bool operator==(const FMidiSongPos& rhs) const;`
- L116 _public prototype_ `static FMidiSongPos Lerp(const FMidiSongPos& A, const FMidiSongPos& B, float Alpha);`
- L118 _public prototype_ `void SetByTimeAndTick(float Ms, float Tick, const ISongMapEvaluator& Map);`
- L122 _private member_ `bool IsSet = false;` — Has anyone explicitly set this, or is this just the defaults.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiTrack.h` (Public)


#### struct `FMidiTrack`  
`struct FMidiTrack`  
_L20-106_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "MIDI Track"))`
- desc: An FMidiTrack is a collection of FMidiEvents in chronological order. It can be created dynamically or be the end result of importing a standard midi file.
- L25 _public prototype_ `FMidiTrack();`
- L26 _public prototype_ `FMidiTrack(const FString& name);`
- L28 _public prototype_ `bool operator==(const FMidiTrack& Other) const;`
- L30 _public prototype_ `const FMidiEventList& GetEvents() const;` — this will ASSERT if events aren't sorted!
- L31 _public prototype_ `const FMidiEventList& GetUnsortedEvents() const;` — this won't sort
- L34 _public prototype_ `FMidiEventList& GetRawEvents();` — Do not call unless you know what you're doing!
- L36 _public function_ `int32 GetNumEvents() const`
- L37 _public function_ `const FMidiEvent* GetEvent(int32 index) const`
- L39 _public prototype_ `void SetName(const FString& InName);`
- L40 _public prototype_ `const FString* GetName() const;`
- L42 _public prototype_ `void AddEvent(const FMidiEvent& Event);`
- L51 _public prototype_ `void ChangeTick(FMidiEventList::TIterator Iterator, int32 NewTick);` — This will not move the event's location in the list so that iterators into Events do note get screwed up, BUT it CAN result in the midi events not being sorted. So if you call this function one or more times you should call Sort() after doing so. @see Sort
- L53 _public prototype_ `void WriteStdMidi(FMidiWriter& writer) const;`
- L55 _public prototype_ `void Sort();`
- L57 _public function_ `void Empty()`
- L58 _public prototype_ `void ClearEventsAfter(int32 Tick, bool IncludeTick);`
- L59 _public prototype_ `void ClearEventsBefore(int32 Tick, bool IncludeTick);`
- L61 _public function_ `int32 GetPrimaryMidiChannel() const`
- L63 _public prototype_ `int32 CopyEvents(FMidiTrack& SourceTrack, int32 FromTick, int32 ThruTick, int32 TickOffset = 0, bool Clear = true, int32 MinNote = 0, int32 MaxNote = 127, int32 NoteTranspose = 0, bool FilterTrackName = true);`
- L66 _public function_ `const FString& GetTextAtIndex(int32 Index) const`
- L71 _public function_ `int32 AddText(const FString& Str)`
- L91 _public function_ `FMidiTextRepository* GetTextRepository()`
- L92 _public function_ `const FMidiTextRepository* GetTextRepository() const`
- L93 _public function_ `FString GetTextForMsg(const FMidiMsg& Message) const`
- L95 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L99 _private member_ `TArray<FMidiEvent> Events;` — `UPROPERTY()` — All the midi events
- L101 _private member_ `bool Sorted;` — `UPROPERTY()` — Are the events sorted.
- L103 _private member_ `int32 PrimaryMidiChannel;` — `UPROPERTY()` — The midi channel of the first event on the track!
- L105 _private member_ `TArray<FString> Strings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HARMONIXMIDI_API`
- L10 _typedef_ `using FMidiEventList = TArray<FMidiEvent>;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiVoiceId.h` (Public)


#### class `FMidiVoiceGeneratorBase`  
`class FMidiVoiceGeneratorBase`  
_L8-20_
- L11 _public prototype_ `FMidiVoiceGeneratorBase();`
- L12 _public function_ `uint32 GetIdBits() const`
- L14 _public member_ `static constexpr uint32 IdWidth = 20;`
- L17 _private member_ `uint32 IdBits;`
- L18 _private member_ `static FCriticalSection GeneratorIdLock;`
- L19 _private member_ `static uint32 NextGeneratorId;`

#### class `FMidiVoiceId`  
`class FMidiVoiceId`  
_L22-117_
- L25 _public function_ `FMidiVoiceId() : Id(0)`
- L29 _public function_ `FMidiVoiceId(const uint32 GeneratorId, const FMidiMsg& FromMessage)`
- L37 _public function_ `FMidiVoiceId(const FMidiVoiceId& Other) : Id (Other.Id)`
- L41 _public function_ `FMidiVoiceId(FMidiVoiceId&& Other) noexcept : Id(Other.Id)`
- L47 _public function_ `void ReassignGenerator(uint32 GeneratorId)`
- L55 _public function_ `void GetGeneratorChannelAndNote(uint32& GeneratorOut, uint8& ChOut, uint8& NoteOut) const`
- L61 _public function_ `void GetChannelAndNote(uint8& ChOut, uint8& NoteOut) const`
- L67 _public function_ `uint32 GetGeneratorId() const`
- L72 _public function_ `FMidiVoiceId& operator=(const FMidiVoiceId& Other)`
- L78 _public function_ `FMidiVoiceId& operator=(uint32 RawId)`
- L84 _public function_ `operator bool() const`
- L89 _public function_ `bool operator==(const FMidiVoiceId& Other) const`
- L94 _public function_ `bool operator==(uint32 RawId) const`
- L99 _public function_ `static FMidiVoiceId Any()`
- L104 _public function_ `static FMidiVoiceId None()`
- L112 _private function_ `FMidiVoiceId(uint32 RawId) : Id(RawId)`
- L116 _private member_ `uint32 Id;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXMIDI_API`
- L119 _function_ `FORCEINLINE uint32 GetTypeHash(const FMidiVoiceId& VoiceId)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MidiWriter.h` (Public)


#### class `FMidiWriter`  
`class FMidiWriter`  
_L21-69_
- desc: Writes MIDI data to an SMF (Standard MIDI Format) file. Does not support all meta-events (no SysEx events, for example). Only writes Format 1 files. Does not take advantage of running status. You rarely have to interact with this class, as FMidiFile uses it internally when you use its SaveStdMidiFile functions. @see FMidiFile
- L24 _public prototype_ `FMidiWriter(FArchive& OutputArhive, int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt);`
- L25 _public prototype_ `~FMidiWriter();`
- L28 _public prototype_ `void Close();` — Flushes data to file; also called by dtor
- L30 _public prototype_ `void EndOfTrack();`
- L33 _public prototype_ `void MidiMessage(int32 Tick, uint8 Status, uint8 Data1, uint8 Data2);` — Writes a standard 1- or 2-byte MIDI message
- L38 _public prototype_ `void Tempo(int32 Tick, int32 Tempo);` — Writes a Tempo Change meta-event: Tempo is in microseconds per quarter-note
- L45 _public prototype_ `void Text(int32 Tick, const TCHAR* Str, uint8 Type);` — Writes Text, Copyright, TrackName, InstName, Lyric, Marker, CuePoint meta-event: "type" is the type of meta-event (constants defined in MidiConstants.h)
- L51 _public prototype_ `void TimeSignature(int32 Tick, int32 Numerator, int32 Denominator);` — Writes a Time Signature meta-event: time signature is numer/denom
- L54 _private member_ `FArchive& Archive;`
- L56 _private member_ `TArray<TSharedPtr<FBufferWriter>> TrackWriters;` — one per track
- L57 _private member_ `TSharedPtr<FBufferWriter> CurrentWriter;`
- L58 _private member_ `int32 TicksPerQuarterNote;`
- L59 _private member_ `int32 CurTick;`
- L60 _private member_ `bool Closed;`
- L62 _private prototype_ `void ProcessTick(int32 Tick);`
- L63 _private prototype_ `void WriteFileHeader();`
- L64 _private prototype_ `void WriteTrack(FBufferWriter& OFile);`
- L65 _private prototype_ `void Write();`
- L67 _private prototype_ `FMidiWriter(const FMidiWriter&);`
- L68 _private prototype_ `FMidiWriter& operator=(const FMidiWriter&);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MusicMapBase.h` (Public)


#### struct `FMusicMapTimespanBase`  
`struct FMusicMapTimespanBase`  
_L12-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: FMusicMapPointBase represents a span in a midi file defined by a start tick and a length. This is a base class for many types of map points we recognize in midi files (e.g. chord, section, tempo, pulse, etc.)
- L16 _public function_ `FMusicMapTimespanBase() : StartTick(0) , LengthTicks(1)`
- L20 _public function_ `FMusicMapTimespanBase(int32 InStartTick, int32 InLengthTicks = 1) : StartTick(InStartTick) , LengthTicks(InLengthTicks)`
- L26 _public member_ `int32 StartTick;` — `UPROPERTY(BlueprintReadOnly, Category = "Timespan")`
- L28 _public member_ `int32 LengthTicks;` — `UPROPERTY(BlueprintReadOnly, Category = "Timespan")`
- L30 _public function_ `FORCEINLINE int32 EndTick() const`
- L31 _public function_ `FORCEINLINE bool ContainsTick(float Tick) const`
- L32 _public function_ `FORCEINLINE float TickInPoint(float Tick) const`
- L33 _public function_ `FORCEINLINE float Progress(float Tick) const`

#### struct `FMusicMapTimespanBase::LessThan`  
`struct LessThan`  
_L35-40_
- desc: friend FArchive& operator<<(FArchive& Archive, FMusicMapTimespanBase& Info);
- L37 _public function_ `bool operator()(const FMusicMapTimespanBase& Point, float Tick) const`
- L38 _public function_ `bool operator()(float Tick, const FMusicMapTimespanBase& Point) const`
- L39 _public function_ `bool operator()(const FMusicMapTimespanBase& Point1, const FMusicMapTimespanBase& Point2) const`

#### struct `FMusicMapUtl`  
`struct FMusicMapUtl`  
_L74-196_
- desc: template<typename T, bool DEFINED_REGIONS>
- L78 _public function_ `template<typename T> static int32 GetPointIndexForTick(const TArray<T>& Points, int32 Tick)`
- L96 _public function_ `template<typename T> static float GetFractionalPointForTick(const TArray<T>& Points, float Tick)`
- L107 _public function_ `template<typename T> static const T* GetPointInfoForTick(const TArray<T>& Points, int32 Tick)`
- L114 _public function_ `template<typename T> static float GetFractionalTickForFractionalPoint(const TArray<T>& Points, float Point)`
- L125 _public function_ `template<typename T> static void Finalize(TArray<T>& Points, int32 LastTick = 0)`
- L145 _public function_ `template<typename T, typename... T0toN> static void AddPoint(T0toN... constructor_args, TArray<T>& Points, int32 StartTick, bool SortNow = true, int32 LengthTicks = 1)`
- L162 _public function_ `template<typename T> static void RemovePointsOnAndAfterTick(TArray<T>& Points, int32 Tick)`
- L175 _public function_ `template<typename T> static void Copy(const TArray<T>& FromPoints, TArray<T>& ToPoints, int32 StartTick, int32 EndTick)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MusicTimeSpan.h` (Public)


#### enum `EMusicTimeSpanOffsetUnits`  
`enum class EMusicTimeSpanOffsetUnits : uint8`  
_L12-32_
- reflection: `UENUM()`
- L14 _public enumerator_ `Ms UMETA(DisplayName = "Milliseconds", EnumDefault)`
- L15 _public enumerator_ `Bars UMETA(DisplayName = "Bars", ToolTip = "(dependent on time signature)")`
- L16 _public enumerator_ `Beats UMETA(DisplayName = "Beats", ToolTip = "(dependent on time signature and Pulse Override)")`
- L17 _public enumerator_ `ThirtySecondNotes UMETA(DisplayName = "1/32s")`
- L18 _public enumerator_ `SixteenthNotes UMETA(DisplayName = "1/16s")`
- L19 _public enumerator_ `EighthNotes UMETA(DisplayName = "1/8s")`
- L20 _public enumerator_ `QuarterNotes UMETA(DisplayName = "1/4s")`
- L21 _public enumerator_ `HalfNotes UMETA(DisplayName = "Halfs")`
- L22 _public enumerator_ `WholeNotes UMETA(DisplayName = "Wholes")`
- L23 _public enumerator_ `DottedSixteenthNotes UMETA(DisplayName = "(dotted) 1/16s")`
- L24 _public enumerator_ `DottedEighthNotes UMETA(DisplayName = "(dotted) 1/8s")`
- L25 _public enumerator_ `DottedQuarterNotes UMETA(DisplayName = "(dotted) 1/4s")`
- L26 _public enumerator_ `DottedHalfNotes UMETA(DisplayName = "(dotted) Halfs")`
- L27 _public enumerator_ `DottedWholeNotes UMETA(DisplayName = "(dotted) Wholes")`
- L28 _public enumerator_ `SixteenthNoteTriplets UMETA(DisplayName = "1/16 (triplets)")`
- L29 _public enumerator_ `EighthNoteTriplets UMETA(DisplayName = "1/8 (triplets)")`
- L30 _public enumerator_ `QuarterNoteTriplets UMETA(DisplayName = "1/4 (triplets)")`
- L31 _public enumerator_ `HalfNoteTriplets UMETA(DisplayName = "1/2 (triplets)")`

#### enum `EMusicTimeSpanLengthUnits`  
`enum class EMusicTimeSpanLengthUnits : uint8`  
_L35-54_
- reflection: `UENUM()`
- L37 _public enumerator_ `Bars UMETA(DisplayName = "Bars", ToolTip = "(dependent on time signature)")`
- L38 _public enumerator_ `Beats UMETA(DisplayName = "Beats", ToolTip = "(dependent on time signature and Pulse Override)")`
- L39 _public enumerator_ `ThirtySecondNotes UMETA(DisplayName = "1/32s")`
- L40 _public enumerator_ `SixteenthNotes UMETA(DisplayName = "1/16s")`
- L41 _public enumerator_ `EighthNotes UMETA(DisplayName = "1/8s")`
- L42 _public enumerator_ `QuarterNotes UMETA(DisplayName = "1/4s")`
- L43 _public enumerator_ `HalfNotes UMETA(DisplayName = "Halfs")`
- L44 _public enumerator_ `WholeNotes UMETA(DisplayName = "Wholes")`
- L45 _public enumerator_ `DottedSixteenthNotes UMETA(DisplayName = "(dotted) 1/16s")`
- L46 _public enumerator_ `DottedEighthNotes UMETA(DisplayName = "(dotted) 1/8s")`
- L47 _public enumerator_ `DottedQuarterNotes UMETA(DisplayName = "(dotted) 1/4s")`
- L48 _public enumerator_ `DottedHalfNotes UMETA(DisplayName = "(dotted) Halfs")`
- L49 _public enumerator_ `DottedWholeNotes UMETA(DisplayName = "(dotted) Wholes")`
- L50 _public enumerator_ `SixteenthNoteTriplets UMETA(DisplayName = "1/16 (triplets)")`
- L51 _public enumerator_ `EighthNoteTriplets UMETA(DisplayName = "1/8 (triplets)")`
- L52 _public enumerator_ `QuarterNoteTriplets UMETA(DisplayName = "1/4 (triplets)")`
- L53 _public enumerator_ `HalfNoteTriplets UMETA(DisplayName = "1/2 (triplets)")`

#### struct `FMusicalTimeSpan`  
`struct FMusicalTimeSpan`  
_L62-95_
- reflection: `USTRUCT(BlueprintType, Category = "HarmonixMidi", meta = (ScriptName = MusicalTimeSpan))`
- L68 _public member_ `EMusicTimeSpanLengthUnits LengthUnits = EMusicTimeSpanLengthUnits::Bars;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HarmonixMidi")`
- L70 _public member_ `int Length = 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HarmonixMidi")`
- L72 _public member_ `EMusicTimeSpanOffsetUnits OffsetUnits = EMusicTimeSpanOffsetUnits::Ms;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HarmonixMidi")`
- L74 _public member_ `int Offset = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HarmonixMidi")`
- L76 _public function_ `FMusicalTimeSpan()`
- L79 _public function_ `FMusicalTimeSpan(EMusicTimeSpanLengthUnits InLengthUnits, float InLength, EMusicTimeSpanOffsetUnits InOffsetUnits, float InOffset) : LengthUnits(InLengthUnits) , Length(InLength) , OffsetUnits(InOffsetUnits) , Offset(InOffset)`
- L86 _public prototype_ `float CalcPositionInSpan(const FMidiSongPos& Position, const ISongMapEvaluator& Maps) const;`
- L87 _public prototype_ `float CalcPositionInSpan(float Ms, const ISongMapEvaluator& Maps) const;`
- L90 _private prototype_ `float CalculateEnclosingVariableSizeSpanExtents(const FMidiSongPos& Position, const ISongMapEvaluator& Maps) const;`
- L91 _private prototype_ `float CalculateEnclosingFixedSizeSpanExtents(const FMidiSongPos& Position, const ISongMapEvaluator& Maps) const;`
- L93 _private prototype_ `float CalcPositionInSpanWithOffset(const FMidiSongPos& Position, const ISongMapEvaluator& Maps) const;`
- L94 _private prototype_ `float CalcPositionInSpanNoOffset(const FMidiSongPos& Position, const ISongMapEvaluator& Maps) const;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXMIDI_API`
- L56 _namespace_ `namespace MusicalTimeSpan`
- L58 _prototype_ `int32 CalculateMusicalSpanLengthTicks(EMusicTimeSpanLengthUnits Unit, const ISongMapEvaluator& Maps, int32 AtTick);` (scope `MusicalTimeSpan`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/MusicTimeSpecifier.h` (Public)


#### enum `Midi::EMusicTimeStringFormat`  
`enum class EMusicTimeStringFormat`  
_L25-29_
- desc: Composers, Musicians, Sound Designers, etc. (and their software tools) speak about musical time in terms of positions and durations. Positions are specified as 1 based numbers for bars and beats. Bar 1, beat 1.0 is the first moment in a song. Durations are 0 based. A musical note might be 0 Bars and 0.33 beats long (a eighth note triplet if beats are quarter notes). When we are parsing a string that specifies a musical time, or converting a midi tick to musical time string we want to maintain this convention. So the parse and format functions below need to know whether they are working on a position or a duration.
- L27 _public enumerator_ `Position`
- L28 _public enumerator_ `Duration`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Midi`
- L47 _prototype_ `FMusicTimestamp ParseMusicTimestamp(const FString& Str, EMusicTimeStringFormat Format);` (scope `Midi`) — Converts a music time string to a bar and a beat. @param Str A string like "3.2.25" or "3:2.25" If 3 numbers are present: (1) is assumed to be the bar, (2&3) is assumed to be the fractional beat. If only 1 or 2 are present it is assumed to specify a beat. @param Format Is the string a music position or a music duration? If position 1 will be subtracted from the values found in the string. @param OutBar The found bar number. NOTE: 0-based! @param OutBeat The found beat number. NOTE: 0-based! @see ParseBarBeatDuration
- L56 _prototype_ `FString FormatBarBeat(const FMusicTimestamp& Timestamp, EMusicTimeStringFormat Format);` (scope `Midi`) — converts a bar and beat position to a string... "Bar.Beat.BeatFraction" @param Bar @param Beat @param Format If 'Position', 1 will be added to both the bar and beat values.
- L77 _prototype_ `int32 BarBeatStringtoMidiTick(const FString& Str, const FBarMap* BarMap, EMusicTimeStringFormat Format);` (scope `Midi`) — Converts a "midi position" string to a low-level midi tick. given the supplied time signature and the current value of the kTicksPerQuarterNote constant in MidiConstants.h @param Str A string like "3.2.25" or "3:2.25" If 3 numbers are present (1) is assumed to be the bar, (2-3) is assumed to be the fractional beat. If only 1 or 2 are present it is assumed to specify a beat. THE NUMBERS SPECIFYING A POSITION ARE ASSUMED TO BE 1-BASED! @param Format Is the string a music position or a music duration? If position 1 will be subtracted from the values found in the string. @param TimeSignatureNumerator @param TimeSignatureDenominator @see BarBeatDurationStringtoMidiTick
- L88 _prototype_ `FString MidiTickFormat(int32 InTick, const FBarMap* Map, EMusicTimeStringFormat Format);` (scope `Midi`) — Given a Tick and a FBarMap it will return a formated string like "3.2.25". In this string the first number is the bar, the second and third are the fractional beat (Reaper style). @param InTick "raw" midi tick @param Map Bar map to use for translation. @param Format If 'Position', 1 will be added to both the bar and beat values.

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/SectionMap.h` (Public)


#### struct `FSongSection`  
`struct FSongSection : public FMusicMapTimespanBase`  
_L15-36_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMusicMapTimespanBase`
- desc: A section in a piece of music has a name, a starting point, and a length
- L20 _public member_ `static constexpr bool DefinedAsRegions = true;`
- L22 _public function_ `FSongSection()`
- L24 _public function_ `FSongSection(const FString& InName, int32 InStartTick, int32 InLengthTicks = 1) : FMusicMapTimespanBase(InStartTick, InLengthTicks) , Name(InName)`
- L29 _public function_ `bool operator==(const FSongSection& Other) const`
- L35 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "SongSection")`

#### struct `FSectionMap`  
`struct FSectionMap`  
_L42-85_
- reflection: `USTRUCT()`
- desc: A map of sections in a piece of music
- L47 _public function_ `FSectionMap() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L50 _public prototype_ `bool operator==(const FSectionMap& Other) const;`
- L52 _public prototype_ `void Finalize(int32 LastTick);`
- L54 _public prototype_ `void Empty();`
- L55 _public prototype_ `void Copy(const FSectionMap& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L56 _public prototype_ `bool IsEmpty() const;`
- L59 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)` — Called by the midi file importer before map points are added to this map
- L64 _public prototype_ `bool AddSection(const FString& Name, int32 StartTick, int32 LengthTicks, bool SortNow = true);`
- L66 _public prototype_ `int32 TickToSectionIndex(int32 Tick) const;`
- L67 _public prototype_ `const FSongSection* TickToSection(int32 Tick) const;`
- L68 _public prototype_ `int32 GetSectionStartTick(const FString& Name) const;`
- L69 _public prototype_ `int32 GetSectionStartTick(int32 SectionIndex) const;`
- L71 _public function_ `const TArray<FSongSection>& GetSections() const`
- L72 _public function_ `int32 GetNumSections() const`
- L73 _public prototype_ `const FSongSection* GetSection(int32 SectionIndex) const;`
- L74 _public prototype_ `FString GetSectionName(int32 SectionIndex) const;`
- L75 _public prototype_ `FString GetSectionNameAtTick(int32 Tick) const;`
- L76 _public prototype_ `void GetSectionNames(TArray<FString>& Names) const;`
- L77 _public prototype_ `int32 FindSectionIndex(const FString& Name) const;`
- L78 _public prototype_ `const FSongSection* FindSectionInfo(const FString& Name) const;`
- L82 _protected member_ `int32 TicksPerQuarterNote;` — `UPROPERTY()`
- L84 _protected member_ `TArray<FSongSection> Points;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/SongMaps.h` (Public)


#### enum `EMidiFileQuantizeDirection`  
`enum class EMidiFileQuantizeDirection : uint8`  
_L29-34_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Nearest = 0`
- L32 _public enumerator_ `Up = 1`
- L33 _public enumerator_ `Down = 2`

#### enum `EMidiClockSubdivisionQuantization`  
`enum class EMidiClockSubdivisionQuantization : uint8`  
_L37-57_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `Bar = static_cast<uint8>(EQuartzCommandQuantization::Bar)`
- L40 _public enumerator_ `Beat = static_cast<uint8>(EQuartzCommandQuantization::Beat)`
- L41 _public enumerator_ `ThirtySecondNote = static_cast<uint8>(EQuartzCommandQuantization::ThirtySecondNote)`
- L42 _public enumerator_ `SixteenthNote = static_cast<uint8>(EQuartzCommandQuantization::SixteenthNote)`
- L43 _public enumerator_ `EighthNote = static_cast<uint8>(EQuartzCommandQuantization::EighthNote)`
- L44 _public enumerator_ `QuarterNote = static_cast<uint8>(EQuartzCommandQuantization::QuarterNote)`
- L45 _public enumerator_ `HalfNote = static_cast<uint8>(EQuartzCommandQuantization::HalfNote)`
- L46 _public enumerator_ `WholeNote = static_cast<uint8>(EQuartzCommandQuantization::WholeNote)`
- L47 _public enumerator_ `DottedSixteenthNote = static_cast<uint8>(EQuartzCommandQuantization::DottedSixteenthNote)`
- L48 _public enumerator_ `DottedEighthNote = static_cast<uint8>(EQuartzCommandQuantization::DottedEighthNote)`
- L49 _public enumerator_ `DottedQuarterNote = static_cast<uint8>(EQuartzCommandQuantization::DottedQuarterNote)`
- L50 _public enumerator_ `DottedHalfNote = static_cast<uint8>(EQuartzCommandQuantization::DottedHalfNote)`
- L51 _public enumerator_ `DottedWholeNote = static_cast<uint8>(EQuartzCommandQuantization::DottedWholeNote)`
- L52 _public enumerator_ `SixteenthNoteTriplet = static_cast<uint8>(EQuartzCommandQuantization::SixteenthNoteTriplet)`
- L53 _public enumerator_ `EighthNoteTriplet = static_cast<uint8>(EQuartzCommandQuantization::EighthNoteTriplet)`
- L54 _public enumerator_ `QuarterNoteTriplet = static_cast<uint8>(EQuartzCommandQuantization::QuarterNoteTriplet)`
- L55 _public enumerator_ `HalfNoteTriplet = static_cast<uint8>(EQuartzCommandQuantization::HalfNoteTriplet)`
- L56 _public enumerator_ `None = static_cast<uint8>(EQuartzCommandQuantization::None)`

#### struct `FSongLengthData`  
`struct FSongLengthData`  
_L60-78_
- reflection: `USTRUCT()`
- L66 _public member_ `int32 LengthTicks = 0;` — `UPROPERTY()`
- L68 _public member_ `float LengthFractionalBars = 0.0f;` — `UPROPERTY()`
- L70 _public member_ `int32 LastTick = 0;` — `UPROPERTY()`
- L72 _public function_ `bool operator==(const FSongLengthData& Other) const`

#### struct `ISongMapEvaluator`  
`struct ISongMapEvaluator`  
_L80-197_
- L83 _public prototype_ `int32 GetTicksPerQuarterNote() const;`
- L84 _public prototype_ `float TickToMs(float Tick) const;`
- L85 _public prototype_ `float MsToTick(float Ms) const;`
- L86 _public prototype_ `float GetCountInSeconds() const;`
- L89 _public prototype_ `const FTempoInfoPoint* GetTempoInfoForMs(float Ms) const;` — tempo
- L90 _public prototype_ `const FTempoInfoPoint* GetTempoInfoForTick(int32 Tick) const;`
- L91 _public prototype_ `int32 GetTempoPointIndexForTick(int32 Tick) const;`
- L92 _public prototype_ `const FTempoInfoPoint* GetTempoInfoPoint(int32 PointIndex) const;`
- L93 _public prototype_ `int32 GetNumTempoChanges() const;`
- L94 _public prototype_ `int32 GetTempoChangePointTick(int32 PointIndex) const;`
- L95 _public prototype_ `float GetTempoAtMs(float Ms) const;`
- L96 _public prototype_ `float GetTempoAtTick(int32 Tick) const;`
- L97 _public prototype_ `bool TempoMapIsEmpty() const;`
- L100 _public prototype_ `const FBeatMapPoint* GetBeatAtMs(float Ms) const;` — beats
- L101 _public prototype_ `float GetMsAtBeat(float Beat) const;` — Beat is zero indexed.
- L102 _public prototype_ `const FBeatMapPoint* GetBeatAtTick(int32 Tick) const;`
- L103 _public prototype_ `float GetMsPerBeatAtMs(float Ms) const;`
- L104 _public prototype_ `float GetMsPerBeatAtTick(int32 Tick) const;`
- L105 _public prototype_ `float GetFractionalBeatAtMs(float Ms) const;` — Returns ONE indexed beat, beware.
- L106 _public prototype_ `float GetFractionalBeatAtTick(float Tick) const;` — Returns ONE indexed beat, beware.
- L107 _public prototype_ `int32 GetBeatIndexAtMs(float Ms) const;`
- L108 _public prototype_ `int32 GetBeatIndexAtTick(int32 Tick) const;`
- L109 _public prototype_ `EMusicalBeatType GetBeatTypeAtMs(float Ms) const;`
- L110 _public prototype_ `EMusicalBeatType GetBeatTypeAtTick(int32 Tick) const;`
- L111 _public prototype_ `const FBeatMapPoint* GetBeatPointInfoAtTick(int32 Tick, int32* PointIndex = nullptr) const;`
- L113 _public prototype_ `float GetBeatInPulseBarAtMs(float Ms) const;`
- L114 _public prototype_ `float GetBeatInPulseBarAtTick(float Tick) const;`
- L115 _public prototype_ `int32 GetNumBeatsInPulseBarAtMs(float Ms) const;`
- L116 _public prototype_ `int32 GetNumBeatsInPulseBarAtTick(int32 Tick) const;`
- L117 _public prototype_ `bool BeatMapIsEmpty() const;`
- L120 _public prototype_ `int32 GetStartBar() const;` — bars
- L121 _public prototype_ `int32 GetNumTimeSignatureChanges() const;`
- L122 _public prototype_ `const FTimeSignature* GetTimeSignatureAtMs(float Ms) const;`
- L123 _public prototype_ `const FTimeSignature* GetTimeSignatureAtTick(int32 Tick) const;`
- L124 _public prototype_ `int32 GetTimeSignaturePointIndexForTick(int32 Tick) const;`
- L125 _public prototype_ `const FTimeSignature* GetTimeSignatureAtBar(int32 Bar) const;`
- L126 _public prototype_ `const FTimeSignaturePoint* GetTimeSignaturePointAtTick(int32 Tick) const;`
- L127 _public prototype_ `const FTimeSignaturePoint* GetTimeSignaturePoint(int32 PointIndex) const;`
- L128 _public prototype_ `int32 GetTimeSignatureChangePointTick(int32 PointIndex);`
- L129 _public prototype_ `float GetBarIncludingCountInAtMs(float Ms) const;`
- L130 _public prototype_ `float GetBarIncludingCountInAtTick(float Tick) const;`
- L131 _public prototype_ `float GetMsAtFractionalBarIncludingCountIn(float BarIncludingCountIn) const;` — BarIncludingCountIn is zero based
- L132 _public prototype_ `float GetMsPerBarAtMs(float Ms) const;`
- L133 _public prototype_ `float GetMsPerBarAtTick(float Tick) const;`
- L134 _public prototype_ `bool BarMapIsEmpty() const;`
- L135 _public prototype_ `FMusicTimestamp TickToMusicTimestamp(float Tick, int32* OutBeatsPerBar = nullptr) const;`
- L136 _public prototype_ `int32 BarIncludingCountInToTick(int32 BarIndex, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;`
- L137 _public prototype_ `int32 BarBeatTickIncludingCountInToTick(int32 BarIndex, int32 BeatInBar, int32 TickInBeat) const;`
- L138 _public prototype_ `float FractionalBarIncludingCountInToTick(float FractionalBarIndex) const;`
- L139 _public prototype_ `float FractionalBeatIncludingCountInToTick(float FractionalBeatIndex) const;`
- L140 _public prototype_ `int32 TickToBarIncludingCountIn(int32 Tick) const;`
- L141 _public prototype_ `float TickToFractionalBarIncludingCountIn(float Tick) const;`
- L142 _public prototype_ `void TickToBarBeatTickIncludingCountIn(int32 RawTick, int32& OutBarIndex, int32& OutBeatInBar, int32& OutTickIndexInBeat, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;`
- L143 _public prototype_ `int32 CalculateMidiTick(const FMusicTimestamp& Timestamp, const EMidiClockSubdivisionQuantization Quantize) const;`
- L144 _public prototype_ `int32 SubdivisionToMidiTicks(const EMidiClockSubdivisionQuantization Division, const int32 AtTick) const;`
- L145 _public prototype_ `float MusicTimestampToTick(const FMusicTimestamp& Timestamp) const;`
- L146 _public prototype_ `int32 MusicTimestampBarToTick(int32 BarNumber, int32* OutBeatsPerBar = nullptr, int32* OutTicksPerBeat = nullptr) const;`
- L149 _public prototype_ `const TArray<FSongSection>& GetSections() const;` — sections
- L150 _public prototype_ `int32 GetNumSections() const;`
- L151 _public prototype_ `float GetSectionStartMsAtMs(float Ms) const;`
- L152 _public prototype_ `float GetSectionEndMsAtMs(float Ms) const;`
- L153 _public prototype_ `const FSongSection* GetSectionAtMs(float Ms) const;`
- L154 _public prototype_ `const FSongSection* GetSectionAtTick(int32 Tick) const;`
- L155 _public prototype_ `int32 GetSectionIndexAtTick(int32 Tick) const;`
- L156 _public prototype_ `const FSongSection* GetSectionWithName(const FString& Name) const;`
- L157 _public prototype_ `FString GetSectionNameAtMs(float Ms) const;`
- L158 _public prototype_ `FString GetSectionNameAtTick(int32 Tick) const;`
- L159 _public prototype_ `float GetSectionLengthMsAtMs(float Ms) const;`
- L160 _public prototype_ `float GetSectionLengthMsAtTick(int32 Tick) const;`
- L161 _public prototype_ `bool SectionMapIsEmpty() const;`
- L164 _public prototype_ `const FChordMapPoint* GetChordAtMs(float Ms) const;` — chords
- L165 _public prototype_ `const FChordMapPoint* GetChordAtTick(int32 Tick) const;`
- L166 _public prototype_ `FName GetChordNameAtMs(float Ms) const;`
- L167 _public prototype_ `FName GetChordNameAtTick(int32 Tick) const;`
- L168 _public prototype_ `float GetChordLengthMsAtMs(float Ms) const;`
- L169 _public prototype_ `float GetChordLengthMsAtTick(int32 Tick) const;`
- L170 _public prototype_ `bool ChordMapIsEmpty() const;`
- L173 _public prototype_ `float GetSongLengthMs() const;` — length
- L174 _public prototype_ `int32 GetSongLengthBeats() const;`
- L175 _public prototype_ `float GetSongLengthFractionalBars() const;`
- L176 _public prototype_ `bool LengthIsAPerfectSubdivision() const;`
- L177 _public prototype_ `FString GetSongLengthString() const;`
- L179 _public prototype_ `int32 QuantizeTickToAnyNearestSubdivision(int32 InTick, EMidiFileQuantizeDirection Direction, EMidiClockSubdivisionQuantization& Division) const;`
- L180 _public prototype_ `int32 QuantizeTickToNearestSubdivision(int32 InTick, EMidiFileQuantizeDirection Direction, EMidiClockSubdivisionQuantization Division) const;`
- L181 _public prototype_ `void GetTicksForNearestSubdivision(int32 InTick, EMidiClockSubdivisionQuantization Division, int32& LowerTick, int32& UpperTick) const;`
- L183 _public prototype_ `virtual const FSongLengthData& GetSongLengthData() const = 0;`
- L186 _public prototype_ `FMusicalTime GetMusicalTimeAtSeconds(double Seconds) const;` — engine level music types
- L187 _public prototype_ `FMusicalTime GetMusicalTimeAtFractionalBar(float Bars) const;`
- L192 _protected prototype_ `virtual const FTempoMap& GetTempoMap() const = 0;`
- L193 _protected prototype_ `virtual const FBeatMap& GetBeatMap() const = 0;`
- L194 _protected prototype_ `virtual const FBarMap& GetBarMap() const = 0;`
- L195 _protected prototype_ `virtual const FSectionMap& GetSectionMap() const = 0;`
- L196 _protected prototype_ `virtual const FChordProgressionMap& GetChordMap() const = 0;`

#### struct `FSongMaps`  
`struct FSongMaps #if CPP : public ISongMapEvaluator #endif`  
_L209-309_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `ISongMapEvaluator`
- desc: FSongMaps encapsulates a number of other musical/midi map types that are very useful for musical gameplay and interactivity. With this class and the current playback position of a piece of music you can do things like determine the current Bar | Beat | Tick, song section, tempo, chord, etc.
- L217 _public prototype_ `FSongMaps();`
- L218 _public prototype_ `FSongMaps(float Bpm, int32 TimeSigNumerator, int32 TimeSigDenominator);`
- L219 _public prototype_ `FSongMaps(const ISongMapEvaluator& Other);`
- L220 _public prototype_ `virtual ~FSongMaps() = default;`
- L222 _public prototype_ `bool operator==(const FSongMaps& Other) const;`
- L224 _public prototype_ `void Init(int32 InTicksPerQuarterNote);`
- L225 _public prototype_ `void Copy(const ISongMapEvaluator& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L228 _public prototype_ `bool LoadFromStdMidiFile(const FString& FilePath);` — For importing...
- L229 _public prototype_ `bool LoadFromStdMidiFile(void* Buffer, int32 BufferSize, const FString& Filename);`
- L230 _public prototype_ `bool LoadFromStdMidiFile(TSharedPtr<FArchive> Archive, const FString& Filename);`
- L233 _public prototype_ `void FillInFrameBasedMusicMap(UFrameBasedMusicMap* Map) const;` — /  BEGIN Support for IMusicMapSource
- L237 _public function_ `TArray<FString>& GetTrackNames()` — tracks
- L238 _public function_ `const TArray<FString>& GetTrackNames() const`
- L239 _public prototype_ `FString GetTrackName(int32 Index) const;`
- L240 _public function_ `bool TrackNamesIsEmpty() const`
- L241 _public function_ `void EmptyTrackNames()`
- L243 _public function_ `void EmptyTempoMap()`
- L244 _public function_ `void EmptyBeatMap()`
- L245 _public function_ `void EmptyBarMap()`
- L246 _public prototype_ `void SetLengthTotalBars(int32 Bars);`
- L247 _public function_ `void EmptySectionMap()`
- L248 _public function_ `void EmptyChordMap()`
- L250 _public prototype_ `void EmptyAllMaps();`
- L251 _public prototype_ `bool IsEmpty() const;`
- L254 _public function_ `virtual const FTempoMap& GetTempoMap() const override` — BEGIN ISongMapEvaluator overrides (Immutable access to maps)
- L255 _public function_ `virtual const FBeatMap& GetBeatMap() const override`
- L256 _public function_ `virtual const FBarMap& GetBarMap() const override`
- L257 _public function_ `virtual const FSectionMap& GetSectionMap() const override`
- L258 _public function_ `virtual const FChordProgressionMap& GetChordMap() const override`
- L259 _public function_ `virtual const FSongLengthData& GetSongLengthData() const override`
- L262 _public function_ `FTempoMap& GetTempoMap()`
- L263 _public function_ `FBeatMap& GetBeatMap()`
- L264 _public function_ `FBarMap& GetBarMap()`
- L265 _public function_ `FSectionMap& GetSectionMap()`
- L266 _public function_ `FChordProgressionMap& GetChordMap()`
- L267 _public function_ `FSongLengthData& GetSongLengthData()`
- L269 _public function_ `int32 GetTicksPerQuarterNote() const`
- L271 _public prototype_ `void SetStartBar(int32 StartBar);`
- L272 _public prototype_ `void SetSongLengthTicks(int32 NewLengthTicks);`
- L273 _public prototype_ `void FinalizeBarMap(int32 InLastTick);`
- L275 _public prototype_ `void AddTempoChange(int32 Tick, float TempoBPM);`
- L276 _public prototype_ `void AddTimeSigChange(int32 Tick, int32 TimeSigNum, int32 TimeSigDenom);`
- L278 _public prototype_ `bool AddTempoInfoPoint(int32 MicrosecondsPerQuarterNote, int32 Tick, bool SortNow = true);`
- L279 _public prototype_ `bool AddTimeSignatureAtBarIncludingCountIn(int32 BarIndex, int32 InNumerator, int32 InDenominator, bool SortNow = true, bool FailOnError = true);`
- L280 _public prototype_ `FTimeSignaturePoint* GetMutableTimeSignaturePoint(int32 PointIndex);`
- L287 _protected member_ `int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt;` — `UPROPERTY()`
- L289 _protected member_ `FTempoMap TempoMap;` — `UPROPERTY()`
- L291 _protected member_ `FBarMap BarMap;` — `UPROPERTY()`
- L293 _protected member_ `FBeatMap BeatMap;` — `UPROPERTY()`
- L295 _protected member_ `FSectionMap SectionMap;` — `UPROPERTY()`
- L297 _protected member_ `FChordProgressionMap ChordMap;` — `UPROPERTY()`
- L299 _protected member_ `TArray<FString> TrackNames;` — `UPROPERTY()`
- L303 _private member_ `FSongLengthData LengthData;` — `UPROPERTY()`
- L306 _private prototype_ `void StringLengthToMT(const FString& LengthString, int32& OutBars, int32& OutTicks);`
- L307 _private prototype_ `bool ReadWithReader(FStdMidiFileReader& Reader);`
- L308 _private prototype_ `bool FinalizeRead(IMidiReader* Reader);`

#### struct `FSongMapsWithAlternateTempoSource`  
`struct FSongMapsWithAlternateTempoSource : public ISongMapEvaluator`  
_L311-354_
- inherits: `ISongMapEvaluator`
- L314 _public function_ `FSongMapsWithAlternateTempoSource(const TSharedPtr<const ISongMapEvaluator>& SongMapsWithTempo, const TSharedPtr<const ISongMapEvaluator>& SongMapsWithOthers) : SongMapsWithTempoMap(SongMapsWithTempo) , SongMapsWithOtherMaps(SongMapsWithOthers)`
- L319 _public function_ `FSongMapsWithAlternateTempoSource(const TSharedPtr<const ISongMapEvaluator>& SongMaps) : SongMapsWithTempoMap(SongMaps) , SongMapsWithOtherMaps(SongMaps)`
- L325 _public function_ `FSongMapsWithAlternateTempoSource& operator=(const TSharedPtr<const FSongMapsWithAlternateTempoSource>& Other)`
- L332 _public prototype_ `virtual ~FSongMapsWithAlternateTempoSource() = default;`
- L334 _public function_ `operator bool() const`
- L339 _public function_ `const TSharedPtr<const ISongMapEvaluator>& GetSongMapsWithTempoMap() const`
- L340 _public function_ `const TSharedPtr<const ISongMapEvaluator>& GetSongMapsWithOtherMaps() const`
- L342 _public function_ `bool AllMapsHaveOneSource() const`
- L345 _protected prototype_ `virtual const FTempoMap& GetTempoMap() const override;`
- L346 _protected prototype_ `virtual const FBeatMap& GetBeatMap() const override;`
- L347 _protected prototype_ `virtual const FBarMap& GetBarMap() const override;`
- L348 _protected prototype_ `virtual const FSectionMap& GetSectionMap() const override;`
- L349 _protected prototype_ `virtual const FChordProgressionMap& GetChordMap() const override;`
- L350 _protected prototype_ `virtual const FSongLengthData& GetSongLengthData() const override;`
- L352 _protected member_ `TSharedPtr<const ISongMapEvaluator> SongMapsWithTempoMap;`
- L353 _protected member_ `TSharedPtr<const ISongMapEvaluator> SongMapsWithOtherMaps;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HARMONIXMIDI_API`
- L23 _namespace_ `namespace HarmonixMetasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidi/TempoMap.h` (Public)


#### struct `FTempoInfoPoint`  
`struct FTempoInfoPoint : public FMusicMapTimespanBase`  
_L15-52_
- reflection: `USTRUCT()`
- inherits: `FMusicMapTimespanBase`
- desc: A position in a song where the tempo is specified (the rate at which the music plays)
- L20 _public member_ `static constexpr bool DefinedAsRegions = false;`
- L22 _public function_ `FTempoInfoPoint()`
- L25 _public function_ `FTempoInfoPoint(float InMs, int32 InMidiTempo, int32 InStartTick, int32 InLengthTicks = 1) : FMusicMapTimespanBase(InStartTick, InLengthTicks) , Ms(InMs) , MidiTempo(InMidiTempo)`
- L32 _public function_ `bool operator==(const FTempoInfoPoint& Other) const`
- L37 _public function_ `float GetBPM() const`
- L39 _public function_ `float GetMsPerQuarterNote() const`
- L42 _public member_ `float Ms = 0;` — `UPROPERTY()` — The time at which the tempo is changing
- L44 _public member_ `int32 MidiTempo = 0;` — `UPROPERTY()` — microseconds per beat at that point

#### struct `FTempoInfoPoint::TimeLessThan`  
`struct TimeLessThan`  
_L46-51_
- L48 _public function_ `bool operator()(float InMs, const FTempoInfoPoint& Point) const`
- L49 _public function_ `bool operator()(const FTempoInfoPoint& Point, float InMs) const`
- L50 _public function_ `bool operator()(const FTempoInfoPoint& PointA, const FTempoInfoPoint& PointB) const`

#### struct `FTempoMap`  
`struct FTempoMap`  
_L62-170_
- reflection: `USTRUCT()`
- L68 _public function_ `FTempoMap() : TicksPerQuarterNote(Harmonix::Midi::Constants::GTicksPerQuarterNoteInt)`
- L71 _public prototype_ `virtual ~FTempoMap() = default;`
- L73 _public prototype_ `bool operator==(const FTempoMap& Other) const;`
- L75 _public prototype_ `void Empty();`
- L76 _public prototype_ `void Copy(const FTempoMap& Other, int32 StartTick = 0, int32 EndTick = std::numeric_limits<int32>::max());`
- L77 _public prototype_ `bool IsEmpty() const;`
- L80 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)` — Called by the midi file importer before map points are added to this map
- L86 _public prototype_ `float TickToMs(float Tick) const;` — Get the time (in milliseconds) at a given tick:
- L99 _public prototype_ `float TickToMs(float Tick, int32 Index, int32* NextIndex) const;` — Get the time (in milliseconds) at the given tick. This flavor of the function can speed up iteration through midi data when you might be making many calls to TickToMs in a row with sequencial tick numbers. @param Tick Midi tick position @param Index The index of the tempo point to be checked first. @param NextIndex Filles in with the tempo point most likely to contain the next tick you are likely to request.
- L102 _public prototype_ `float MsToTick(float TimeMs) const;` — Get the tick at a given time (in milliseconds)
- L115 _public prototype_ `float MsToTick(float TimeMs, int32 Index, int32* NextIndex) const;` — Get the tick at the given millisecond. This flavor of the function can speed up iteration through midi data when you might be making many calls to MsToTick in a row with sequencial times. @param TimeMs Millisecond @param Index The index of the tempo point to be checked first. @param NextIndex Fills in with the tempo point most likely to contain the next tick you are likely to request.
- L118 _public prototype_ `float GetMsPerQuarterNoteAtTick(int32 Tick) const;` — Get the tempo in ms/quarter-note
- L121 _public prototype_ `int32 GetMicrosecondsPerQuarterNoteAtTick(int32 Tick) const;` — Get the tempo in us/quarter-note
- L124 _public prototype_ `float GetTempoAtTick(int32 Tick) const;` — Get the tempo in beats (quarter-notes)/min
- L127 _public prototype_ `const FTempoInfoPoint* GetTempoPointAtTick(int32 Tick) const;` — Get the tempo info point
- L130 _public prototype_ `int32 GetTempoPointIndexAtTick(int32 Tick) const;` — Get the tempo info point
- L133 _public prototype_ `int32 GetNumTempoChangePoints() const;` — The number of 'tempo events' in the song
- L136 _public prototype_ `int32 GetTempoChangePointTick(int32 Index) const;` — Return the tick of the nth tempo change point.
- L139 _public prototype_ `void Finalize(int32 LastTick);` — Call when you're done changing it
- L141 _public prototype_ `bool AddTempoInfoPoint(int32 MicrosecondsPerQuarterNote, int32 Tick, bool SortNow = true);`
- L144 _public prototype_ `void WipeTempoInfoPoints(int32 Tick);` — Remove every point from the given tick onward
- L147 _public prototype_ `void SupplyDefault();` — if there are no points, supply a default tempo of 120.
- L150 _public function_ `const TArray<FTempoInfoPoint>& GetTempoPoints() const` — Returns the tempo info points for inspection.
- L152 _public function_ `int32 GetTicksPerQuarterNote() const`
- L156 _protected member_ `int32 TicksPerQuarterNote;` — `UPROPERTY()`
- L158 _protected member_ `TArray<FTempoInfoPoint> Points;` — `UPROPERTY()`
- L163 _private prototype_ `int32 PointIndexForTime(float TimeMs) const;` — Given a time, find the TempoInfoPoint at or before it.
- L167 _private prototype_ `float TickToMsInternal(float Tick, const FTempoInfoPoint& prevTempoInfoPoint) const;` — Assuming prevInfoPoint is the last TempoInfoPoint before tick, calculate tick as time in ms
- L168 _private prototype_ `float MsToTickInternal(float TimeMs, const FTempoInfoPoint& prevTempoInfoPoint) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMIDI_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidi/Public/HarmonixMidiModule.h` (Public)


#### class `FHarmonixMidiModule`  
`class FHarmonixMidiModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule();`
- L11 _public prototype_ `virtual void ShutdownModule();`
