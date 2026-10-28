# Plugins / HarmonixMidiTests

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMidiTests`
- headers: 1; symbols: 10
- symbol kinds: namespace=4, prototype=6
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HarmonixMidi, UnrealEd

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiTests/Private/MidiTestUtility.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Harmonix`
- L8 _namespace_ `namespace Testing` (scope `Harmonix`)
- L8 _namespace_ `namespace Utility` (scope `Harmonix::Testing`)
- L8 _namespace_ `namespace MidiTestUtility` (scope `Harmonix::Testing::Utility`)
- L15 _prototype_ `UMidiFile* CreateAndInitializaMidiFile(float FileLengthBars, int32 NumTracksIncludingConductor, int32 InTimeSigNum, int32 InTimeSigDenom, int32 InTempo, bool PutTextEventOnLastTick = false);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Construct an empty UMidiFile according to: input file length in bars (fractional), input number of midi channels, input number of midi tracks, input time signature, and input tempo (bpm) 1 text event is added at the end of the file according to input file length to mark the last event tick
- L22 _prototype_ `void AddNoteOnNoteOffPairToFile(UMidiFile* InFile, int32 InNoteNumber, int32 InNoteVelocity,int32 InTrackIndex, int32 InChannel, int32 AtTick, int32 DurationTicks);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Add 1 Note On/Note Off pair to the input midi file given the input Midi note number, note velocity, track index, channel, and fractional bar position
- L28 _prototype_ `void AddCCEventToFile(UMidiFile* InFile, uint8 InControllerID, uint8 InControlValue,int32 InTrackIndex, int32 InChannel, int32 AtTick);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Add 1 CC Event to the input midi file given the input Midi Controller ID, control value, track index, channel, and fractional bar position
- L34 _prototype_ `void AddTextEventToFile(UMidiFile* InFile, FString InText, int32 InTrackIndex, int32 AtTick);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Add 1 CC Event to the input midi file given the input text, track index, and fractional bar position
- L40 _prototype_ `void AddPitchEventToFile(UMidiFile* InFile, uint8 InPitchValueLSB, uint8 InPitchValueMSB, int32 InTrackIndex, int32 InChannel, int32 AtTick);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Add 1 Pitch Bend Event to the input midi file given the input Pitch Bend value (LSB), Pitch Bend value (MSB), track index, channel, and fractional bar position
- L46 _prototype_ `void AddPolyPresEventToFile(UMidiFile* InFile, uint8 InNoteNumber, uint8 InPolyPresValue, int32 InTrackIndex, int32 InChannel, int32 AtTick);` (scope `Harmonix::Testing::Utility::MidiTestUtility`) — Add 1 Pitch Bend Event to the input midi file given the input Midi note number, polyphonic pressure value, track index, channel, and fractional bar position
