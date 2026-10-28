# Programs / ZenOplogDiffTool

- module root: `Source/Programs/ZenOplogDiffTool`
- headers: 7; symbols: 64
- symbol kinds: class=6, delegate=1, enum=3, enumerator=7, member=25, prototype=22
- PrivateDependencyModuleNames: ApplicationCore, Core, DesktopPlatform, Projects, ZenOplogUtils
- PublicIncludePathModuleNames: Launch

### `Source/Programs/ZenOplogDiffTool/Private/DownloadSnapshotOperation.h` (Private)


#### class `FDownloadSnapshot`  
`class FDownloadSnapshot : public IOplogDiffOperation`  
_L9-21_
- inherits: `IOplogDiffOperation`
- desc: Downloads a snapshot from zen, using a snapshot descriptor
- L12 _public prototype_ `FDownloadSnapshot(const UE::FZenSnapshotDescriptor& Descriptor, bool DownloadAsJson, FStringView OutputRoot);`
- L13 _public prototype_ `virtual ~FDownloadSnapshot() = default;`
- L14 _public prototype_ `virtual ERunningState Run() override;`
- L16 _public member_ `UE::FZenSnapshotDescriptor SnapshotDescriptor;` — Used to identify the oplog to download
- L17 _public member_ `FString OutputDirectory;` — Directory to write the manifests to (optional)
- L18 _public member_ `bool DownloadManifestAsJson = false;`
- L20 _public member_ `FString DownloadedManifest;` — Local path to the manifest that was successfully downloaded

### `Source/Programs/ZenOplogDiffTool/Private/FindSnapshotOperation.h` (Private)


#### class `FFindSnapshot`  
`class FFindSnapshot : public IOplogDiffOperation`  
_L9-24_
- inherits: `IOplogDiffOperation`
- desc: Uses the zen build service to lookup a snapshot descriptor for a particular build
- L12 _public prototype_ `virtual ~FFindSnapshot() = default;`
- L13 _public prototype_ `virtual ERunningState Run() override;`
- L16 _public member_ `FString FindProjectName;` — Find a snapshot based on these parameters
- L17 _public member_ `FString FindStream;`
- L18 _public member_ `FString FindPlatform;`
- L19 _public member_ `FString FindCommitID;`
- L20 _public member_ `bool bDisplayAllBuildsFound = false;`
- L22 _public member_ `TSharedFuture<TOptional<UE::FZenSnapshotDescriptor>> PendingResult;`
- L23 _public member_ `TOptional<UE::FZenSnapshotDescriptor> FoundSnapshot;`

### `Source/Programs/ZenOplogDiffTool/Private/IZenOplogDiffOperation.h` (Private)


#### class `IOplogDiffOperation`  
`class IOplogDiffOperation`  
_L9-23_
- desc: Represents an operation that can run continuously.
- L12 _public prototype_ `virtual ~IOplogDiffOperation() = default;`
- L21 _public prototype_ `virtual ERunningState Run() = 0;` — Continuously called until it returns Success or Error
- L22 _public member_ `TFunction<void(IOplogDiffOperation&)> OnComplete;` — Parameter = reference to operation that just completed. Should be called when Run returns Success

#### enum `IOplogDiffOperation::ERunningState`  
`enum class ERunningState`  
_L14-19_
- L16 _public enumerator_ `Running`
- L17 _public enumerator_ `Success`
- L18 _public enumerator_ `Error`

### `Source/Programs/ZenOplogDiffTool/Private/LoadSnapshotDescriptorOperation.h` (Private)


#### class `FLoadSnapshotDescriptor`  
`class FLoadSnapshotDescriptor : public IOplogDiffOperation`  
_L9-18_
- inherits: `IOplogDiffOperation`
- desc: Load a snapshot descriptor from horde build artifact json
- L12 _public prototype_ `FLoadSnapshotDescriptor(FStringView SnapshotJson);`
- L13 _public prototype_ `virtual ~FLoadSnapshotDescriptor() = default;`
- L14 _public prototype_ `virtual ERunningState Run() override;`
- L16 _public member_ `FString SnapshotJsonPath;` — Path to the file to load
- L17 _public member_ `TArray<UE::FZenSnapshotDescriptor> LoadedSnapshots;` — Snapshot json may contain more than one build

### `Source/Programs/ZenOplogDiffTool/Private/OplogManifestDiffOperation.h` (Private)


#### class `FOplogManifestDiff`  
`class FOplogManifestDiff : public IOplogDiffOperation`  
_L9-28_
- inherits: `IOplogDiffOperation`
- L12 _public prototype_ `FOplogManifestDiff(FString Manifest1, FString Manifest2);`
- L13 _public prototype_ `virtual ~FOplogManifestDiff() = default;`
- L14 _public prototype_ `virtual ERunningState Run() override;`
- L17 _public member_ `FString ManifestToDiff1;` — Paths to local manifest files
- L18 _public member_ `FString ManifestToDiff2;`
- L20 _public member_ `UE::FOplogManifest Manifest1;`
- L21 _public member_ `UE::FOplogManifest Manifest2;`
- L24 _public member_ `UE::FOplogDiffResults DiffResults;` — Results of the diff
- L27 _private prototype_ `bool LoadManifests();`

### `Source/Programs/ZenOplogDiffTool/Private/OutputDiffResultsOperation.h` (Private)


#### class `FOutputDiffResults`  
`class FOutputDiffResults : public IOplogDiffOperation`  
_L10-44_
- inherits: `IOplogDiffOperation`
- desc: Takes ownership of diff results + outputs them to a file and/or the log
- L25 _public prototype_ `FOutputDiffResults(UE::FOplogManifest&& Oplog1, UE::FOplogManifest&& Oplog2, UE::FOplogDiffResults&& DiffResults);`
- L26 _public prototype_ `virtual ~FOutputDiffResults() = default;`
- L27 _public prototype_ `virtual ERunningState Run() override;`
- L29 _public member_ `FString OutputPath;`
- L30 _public member_ `ELogOptions LoggerOptions = ELogOptions::None;`
- L31 _public member_ `EOutputOptions OutputOptions = EOutputOptions::None;`
- L33 _public member_ `UE::FOplogManifest Manifest1;`
- L34 _public member_ `UE::FOplogManifest Manifest2;`
- L35 _public member_ `UE::FOplogDiffResults DiffResults;`
- L40 _private prototype_ `void LogOutput();`
- L41 _private prototype_ `bool OutputCompactBinary(const FDiffSummary& Summary, UE::EOutputManifestDiffOptions Flags);`
- L42 _private prototype_ `bool OutputJson(const FDiffSummary& Summary, UE::EOutputManifestDiffOptions Flags);`
- L43 _private prototype_ `FDiffSummary SummarizeDiffResults();`

#### enum `FOutputDiffResults::ELogOptions`  
`enum class ELogOptions`  
_L13-17_
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `Summary`

#### enum `FOutputDiffResults::EOutputOptions`  
`enum class EOutputOptions`  
_L19-23_
- L21 _public enumerator_ `None`
- L22 _public enumerator_ `OutputChangedValues`

### `Source/Programs/ZenOplogDiffTool/Private/ZenOplogDiffLogging.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogZenOplogDiffTool, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogZenOplogDiffTool, Log, All);`
