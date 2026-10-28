# Developer / CSVUtils

- module root: `Source/Developer/CSVUtils`
- headers: 1; symbols: 15
- symbol kinds: member=9, namespace=1, prototype=2, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject

### `Source/Developer/CSVUtils/Public/CSVProfilerUtils.h` (Public)


#### struct `CsvUtils::FCsvProfilerSample`  
`struct FCsvProfilerSample`  
_L11-17_
- L13 _public member_ `FString Name;`
- L14 _public member_ `TArray<float> Values;`
- L15 _public member_ `float Average = 0.0f;`
- L16 _public member_ `double Total = 0.0;`

#### struct `CsvUtils::FCsvProfilerEvent`  
`struct FCsvProfilerEvent`  
_L19-23_
- L21 _public member_ `FString Name;`
- L22 _public member_ `int32 Frame = INDEX_NONE;`

#### struct `CsvUtils::FCsvProfilerCapture`  
`struct FCsvProfilerCapture`  
_L25-30_
- L27 _public member_ `TMap<FString, FCsvProfilerSample> Samples;`
- L28 _public member_ `TArray<FCsvProfilerEvent> Events;`
- L29 _public member_ `TMap<FString, FString> Metadata;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace CsvUtils`
- L39 _prototype_ `bool ReadFromCsv(FCsvProfilerCapture& OutCapture, const TCHAR* FilePath, TArray<FText>* OutErrors = nullptr);` (scope `CsvUtils`) — Reads a csv profiler capture from the parameter file path into the parameter container. @param OutCapture The destination capture container. @param FilePath The source file path. @param OutErrors Optional output array to hold any reported errors. @return True if the capture was successfully read.
- L48 _prototype_ `bool ReadFromCsvBin(FCsvProfilerCapture& OutCapture, const TCHAR* FilePath, TArray<FText>* OutErrors = nullptr);` (scope `CsvUtils`) — Reads a binary csv profiler capture from the parameter file path into the parameter container. @param OutCapture The destination capture container. @param FilePath The source file path. @param OutErrors Optional output array to hold any reported errors. @return True if the capture was successfully read.
