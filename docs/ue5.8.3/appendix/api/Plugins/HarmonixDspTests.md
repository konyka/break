# Plugins / HarmonixDspTests

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixDspTests`
- headers: 1; symbols: 11
- symbol kinds: function=4, namespace=3, prototype=4
- PrivateDependencyModuleNames: Core, Engine, HarmonixDsp, HarmonixDspEditor, HarmonixMidi, Json, Projects, SignalProcessing, UnrealEd

### `Plugins/Runtime/Harmonix/Source/HarmonixDspTests/Private/TestUtility.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Harmonix`
- L8 _namespace_ `namespace Testing` (scope `Harmonix`)
- L8 _namespace_ `namespace Utility` (scope `Harmonix::Testing`)
- L11 _function_ `template<typename TType> FString ArrayToString(const TArray<TType>& Array,` (scope `Harmonix::Testing::Utility`)
- L13 _function_ `TFunction<FString(const TType&)> ValueToString = [](const TType& Value)` (scope `Harmonix::Testing::Utility`) — default string formatter
- L27 _function_ `template<typename T0, typename T1> bool CheckAll(const TArray<T0>& Array0, const TArray<T1>& Array1,` (scope `Harmonix::Testing::Utility`)
- L29 _function_ `TFunction<bool(const T0&, const T1&)> Comparator = [](const T0& First, const T1& Second)` (scope `Harmonix::Testing::Utility`) — default comparator. Assumes types have == operator overload
- L43 _prototype_ `FString ArrayToString(const TArray<float>& Array, int MinFractionalDigits);` (scope `Harmonix::Testing::Utility`)
- L44 _prototype_ `FString ArrayToString(const TArray<double>& Array, int MinFractionalDigits);` (scope `Harmonix::Testing::Utility`)
- L45 _prototype_ `bool CheckAll(const TArray<float>& Array0, const TArray<float>& Array1, float Tolerance = UE_SMALL_NUMBER);` (scope `Harmonix::Testing::Utility`)
- L46 _prototype_ `bool CheckAll(const TArray<double>& Array0, const TArray<double>& Array1, double Tolerance = UE_DOUBLE_SMALL_NUMBER);` (scope `Harmonix::Testing::Utility`)
