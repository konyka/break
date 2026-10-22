# Plugins / CaptureManagerIngestBlueprint

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint`
- headers: 7; symbols: 91
- symbol kinds: class=3, delegate=3, enum=3, enumerator=8, member=34, namespace=10, prototype=26, struct=4
- PrivateDependencyModuleNames: CaptureDataConverter, CaptureManagerEditorSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CaptureUtils, DataIngestCore, DataIngestCoreEditor, NamingTokens
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerFindTakes.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L10 _prototype_ `TArray<FCaptureManagerTakeDirectoryInfo> FindTakesInDirectory(const FString& InSearchDirectory, bool bRecursive);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerIngestBlueprintLibrary.h` (Private)


#### enum `ECaptureManagerIngestType`  
`enum class ECaptureManagerIngestType : uint8`  
_L13-20_
- reflection: `UENUM(BlueprintType)`
- desc: Describes which ingest path produced a result. Returned in async ingest callbacks as context.
- L15 _public enumerator_ `MonoVideo UMETA(DisplayName = "Mono Video")`
- L16 _public enumerator_ `StereoVideo UMETA(DisplayName = "Stereo Video")`
- L17 _public enumerator_ `LiveLinkFace UMETA(DisplayName = "LiveLink Face")`
- L18 _public enumerator_ `TakeArchive UMETA(DisplayName = "Take Archive")`
- L19 _public enumerator_ `Calibration UMETA(DisplayName = "Calibration")`

#### enum `ECaptureManagerImageFormat`  
`enum class ECaptureManagerImageFormat : uint8`  
_L23-27_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Png = 0 UMETA(DisplayName = "PNG")`
- L26 _public enumerator_ `Jpg = 1 UMETA(DisplayName = "JPG")`

#### enum `ECaptureManagerAudioFormat`  
`enum class ECaptureManagerAudioFormat : uint8`  
_L30-33_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `Wav = 0 UMETA(DisplayName = "WAV")`

#### struct `FCaptureManagerConversionParams`  
`struct FCaptureManagerConversionParams`  
_L36-64_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `ECaptureManagerImageFormat ImageFormat = ECaptureManagerImageFormat::Png;` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L44 _public member_ `ECaptureManagerAudioFormat AudioFormat = ECaptureManagerAudioFormat::Wav;` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L47 _public member_ `FString ImageFilePrefix = TEXT("fra` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L50 _public member_ `FString AudioFilePrefix = TEXT("aud` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L53 _public member_ `FString DepthFilePrefix = TEXT("dep` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L56 _public member_ `FString CalibrationFilePrefix = TEXT("cal` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L59 _public member_ `ECaptureManagerPixelFormat PixelFormat = ECaptureManagerPixelFormat::U8_BGRA;` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`
- L62 _public member_ `ECaptureManagerRotation Rotation = ECaptureManagerRotation::Auto;` — `UPROPERTY(BlueprintReadWrite, Category = Ingest)`

#### struct `FCaptureManagerTakeDirectoryInfo`  
`struct FCaptureManagerTakeDirectoryInfo`  
_L68-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: Inventory of capture-related files found in a single directory.
- L74 _public member_ `FString Path;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — Absolute path to the directory.
- L78 _public member_ `bool bIsTakeArchive = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — True if the directory contains a .cptake file.
- L82 _public member_ `bool bIsLiveLinkFace = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — True if the directory contains frame_log.csv and video_metadata.json (LiveLink Face capture).
- L86 _public member_ `TArray<FString> VideoFiles;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — Full paths of video files (.mp4, .mov, .avi, .mkv, .webm) found in the directory.
- L90 _public member_ `TArray<FString> ImageSeqDirs;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — Full paths of subdirectories containing image sequences (.jpg, .jpeg, .png).
- L94 _public member_ `TArray<FString> AudioFiles;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — Full paths of audio files (.wav, .mp3, .flac, .m4a, .aac) found in the directory.
- L98 _public member_ `TArray<FString> CalibrationFiles;` — `UPROPERTY(BlueprintReadOnly, Category = "Ingest")` — Full paths of calibration files found in the directory. Currently only files named "calib.json" are detected.

#### class `UCaptureManagerIngestBlueprintLibrary`  
`class UCaptureManagerIngestBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L105-329_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L119 _public prototype_ `static UFootageCaptureData* IngestTakeArchiveSync( const FString& TakeArchivePath, const FCaptureManagerConversionParams& Params, FText& OutErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest|Blocking", meta = (DisplayName = "Ingest Take Archive", ReturnDisplayName = "FootageCaptureData", Keywords = "import"))` — Import a take archive (.cptake). Accepts a directory path or a direct path to the .cptake file. Slate, take number, and device info are read from the archive metadata. @param TakeArchivePath		Path to the take directory or .cptake file. If a directory is given, searches for a .cptake file automatically. @param Params				Conversion settings (pixel format, rotation, output formats). @param OutErrorMessage		Set on failure; describes what went wrong.
- L135 _public prototype_ `static int32 IngestTakeArchive( FString TakeArchivePath, FCaptureManagerConversionParams Params, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (DisplayName = "Ingest Take Archive", ReturnDisplayName = "IngestId", Keywords = "import"))` — Import a take archive (.cptake) asynchronously. Accepts a directory path or a direct path to the .cptake file. Slate, take number, and device info are read from the archive metadata. @param TakeArchivePath		Path to the take directory or .cptake file. If a directory is given, searches for a .cptake file automatically. @param Params				Conversion settings (pixel format, rotation, output formats). @param OnSuccess				Called on the game thread when the import completes successfully. @param OnFailure				Called on the game thread if the import fails.
- L153 _public prototype_ `static UFootageCaptureData* IngestMonoVideoSync( const FString& VideoFilePath, const FString& AudioFilePath, const FString& Slate, int32 TakeNumber, const FCaptureManagerConversionParams& Params, FText& OutErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest|Blocking", meta = (DisplayName = "Ingest Mono Video", ReturnDisplayName = "FootageCaptureData", InTakeNumber = "1", Keywords = "import"))` — Import a single-camera video file (.mp4 or .mov). @param VideoFilePath			Path to the video file. @param AudioFilePath			Optional. Path to a separate audio file. Leave empty to use embedded audio if present. @param Slate					Optional. Slate name for the imported take. Derived from the video filename if empty. @param TakeNumber			Optional. Take number. Defaults to 1 if less than 1. @param Params				Conversion settings (pixel format, rotation, output formats). @param OutErrorMessage		Set on failure; describes what went wrong.
- L174 _public prototype_ `static int32 IngestMonoVideo( FString VideoFilePath, FString AudioFilePath, FString Slate, int32 TakeNumber, FCaptureManagerConversionParams Params, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (DisplayName = "Ingest Mono Video", ReturnDisplayName = "IngestId", InTakeNumber = "1", Keywords = "import"))` — Import a single-camera video file (.mp4 or .mov) asynchronously. @param VideoFilePath			Path to the video file. @param AudioFilePath			Optional. Path to a separate audio file. Leave empty to use embedded audio if present. @param Slate					Optional. Slate name for the imported take. Derived from the video filename if empty. @param TakeNumber			Optional. Take number. Defaults to 1 if less than 1. @param Params				Conversion settings (pixel format, rotation, output formats). @param OnSuccess				Called on the game thread when the import completes successfully. @param OnFailure				Called on the game thread if the import fails.
- L197 _public prototype_ `static UFootageCaptureData* IngestStereoVideoSync( const FString& VideoPathA, const FString& VideoPathB, const FString& AudioFilePath, const FString& CalibrationFilePath, const FString& Slate, int32 TakeNumber, const FCaptureManagerConversionParams& Params, FText& OutErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest|Blocking", meta = (DisplayName = "Ingest Stereo Video", ReturnDisplayName = "FootageCaptureData", InTakeNumber = "1", Keywords = "import"))` — Import a dual-camera stereo video. Pass two video files (.mp4/.mov) or two image-sequence folders. @param VideoPathA				Path to the first video file or image-sequence folder. Becomes the default primary camera for MHA processing. @param VideoPathB				Path to the second video file or image-sequence folder. Must be the same type as the first video (both files, or both folders). Becomes the secondary view, resolved automatically. @param AudioFilePath				Optional. Path to a dedicated audio file. Leave empty if there is no separate audio. @param CalibrationFilePath		Optional. Path to a calibration file (.json). Format (OpenCV or Unreal) is auto-detected from JSON structure. Leave empty if not available. @param Slate						Optional. Slate name for the imported take. Derived from the first video's filename if empty. @param TakeNumber				Optional. Take number. Defaults to 1 if less than 1. @param Params					Conversion settings (pixel format, rotation, output formats). @param OutErrorMessage			Set on failure; describes what went wrong.
- L222 _public prototype_ `static int32 IngestStereoVideo( FString VideoPathA, FString VideoPathB, FString AudioFilePath, FString CalibrationFilePath, FString Slate, int32 TakeNumber, FCaptureManagerConversionParams Params, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (DisplayName = "Ingest Stereo Video", ReturnDisplayName = "IngestId", InTakeNumber = "1", Keywords = "import"))` — Import a dual-camera stereo video asynchronously. Pass two video files (.mp4/.mov) or two image-sequence folders. @param VideoPathA				Path to the first video file or image-sequence folder. Becomes the default primary camera for MHA processing. @param VideoPathB				Path to the second video file or image-sequence folder. Must be the same type as the first video (both files, or both folders). Becomes the secondary view, resolved automatically. @param AudioFilePath				Optional. Path to a dedicated audio file. Leave empty if there is no separate audio. @param CalibrationFilePath		Optional. Path to a calibration file (.json). Format (OpenCV or Unreal) is auto-detected from JSON structure. Leave empty if not available. @param Slate						Optional. Slate name for the imported take. Derived from the first video's filename if empty. @param TakeNumber				Optional. Take number. Defaults to 1 if less than 1. @param Params					Conversion settings (pixel format, rotation, output formats). @param OnSuccess					Called on the game thread when the import completes successfully. @param OnFailure					Called on the game thread if the import fails.
- L242 _public prototype_ `static UFootageCaptureData* IngestLiveLinkFaceSync( const FString& TakeDirectoryPath, const FCaptureManagerConversionParams& Params, FText& OutErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest|Blocking", meta = (DisplayName = "Ingest Live Link Face", ReturnDisplayName = "FootageCaptureData", Keywords = "import livelink iphone"))` — Import a LiveLink Face capture. Supports both the current .cptake format and the pre-5.6 LiveLink Face format. @param TakeDirectoryPath		Path to the take directory containing the LiveLink Face capture data. @param Params				Conversion settings (pixel format, rotation, output formats). @param OutErrorMessage		Set on failure; describes what went wrong.
- L257 _public prototype_ `static int32 IngestLiveLinkFace( FString TakeDirectoryPath, FCaptureManagerConversionParams Params, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (DisplayName = "Ingest Live Link Face", ReturnDisplayName = "IngestId", Keywords = "import livelink iphone"))` — Import a LiveLink Face capture asynchronously. Supports both the current .cptake format and the pre-5.6 LiveLink Face format. @param TakeDirectoryPath		Path to the take directory containing the LiveLink Face capture data. @param Params				Conversion settings (pixel format, rotation, output formats). @param OnSuccess				Called on the game thread when the import completes successfully. @param OnFailure				Called on the game thread if the import fails.
- L274 _public prototype_ `static UFootageCaptureData* IngestCalibrationSync( const FString& CalibrationFilePath, const FString& CalibrationName, FText& OutErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest|Blocking", meta = (DisplayName = "Ingest Calibration", ReturnDisplayName = "FootageCaptureData", Keywords = "import"))` — Import a standalone calibration file (.json). Format (OpenCV or Unreal) is auto-detected. Creates a FootageCaptureData asset with no footage and one CameraCalibration entry. Access the calibration via FootageCaptureData->CameraCalibrations[0]. @param CalibrationFilePath		Path to a calibration JSON file. @param CalibrationName			Name for the calibration asset. Must be unique per import - determines the output asset path. If multiple calibration files share the same filename (e.g. calib.json), consider using the parent folder name to distinguish them. @param OutErrorMessage			Set on failure; describes what went wrong.
- L289 _public prototype_ `static int32 IngestCalibration( FString CalibrationFilePath, FString CalibrationName, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (DisplayName = "Ingest Calibration", ReturnDisplayName = "IngestId", Keywords = "import"))` — Import a standalone calibration file (.json) asynchronously. Format (OpenCV or Unreal) is auto-detected. @param CalibrationFilePath		Path to a calibration JSON file. @param CalibrationName			Name for the calibration asset. Must be unique per import - determines the output asset path. If multiple calibration files share the same filename (e.g. calib.json), consider using the parent folder name to distinguish them. @param OnSuccess					Called on the game thread when the import completes successfully. @param OnFailure					Called on the game thread if the import fails.
- L308 _public prototype_ `static bool CancelIngest(int32 IngestId);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (Keywords = "abort stop cancel"))` — Cancel a queued or running ingest by its ID. Queued ingests are removed immediately and their OnFailure delegate fires with a cancellation message. Running ingests are signaled to stop - conversion nodes bail at their next cancellation check and the partial working directory is cleaned up. @param IngestId	The ID returned by an async ingest function. @return				True if the IngestId was found and cancellation was initiated. False if it was already completed, already canceled, or invalid.
- L325 _public prototype_ `static TArray<FCaptureManagerTakeDirectoryInfo> FindTakeDirectories( const FString& SearchDirectory, bool bRecursive = true );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Ingest", meta = (ReturnDisplayName = "TakeDirectories", Keywords = "scan"))` — Scans a directory for capture-related content and returns an inventory of what was found. Returns one entry per directory that contains at least one recognized capture artifact (video, image sequence, audio, calibration, or .cptake archive). File arrays are populated by filesystem scan only, not by parsing .cptake metadata. When bIsTakeArchive is true, the file arrays are empty - the .cptake manifest is the authoritative inventory. Pass the directory path to IngestTakeArchive directly. @param SearchDirectory		Root directory to search. @param bRecursive			If true, recurse into subdirectories. Recursion stops at directories that contain capture artifacts.

#### Free symbols / members of external scopes

- L101 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerIngestSuccess, int32, IngestId, ECaptureManagerIngestType, IngestType, UFootageCaptureData*, FootageCaptureData);`
- L101 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerIngestSuccess, int32, IngestId, ECaptureManagerIngestType, IngestType, UFootageCaptureData*, FootageCaptureData);`
- L102 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerIngestFailed, int32, IngestId, ECaptureManagerIngestType, IngestType, FText, ErrorMessage);`
- L102 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerIngestFailed, int32, IngestId, ECaptureManagerIngestType, IngestType, FText, ErrorMessage);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerIngestBlueprintModule.h` (Private)


#### class `FCaptureManagerIngestBlueprintModule`  
`class FCaptureManagerIngestBlueprintModule : public IModuleInterface`  
_L13-23_
- inherits: `IModuleInterface`
- L16 _public prototype_ `void StartupModule() override;`
- L17 _public prototype_ `void ShutdownModule() override;`
- L19 _public prototype_ `UE::CaptureManager::FCaptureManagerIngestDispatcher& GetDispatcher();`
- L22 _private member_ `TUniquePtr<UE::CaptureManager::FCaptureManagerIngestDispatcher> Dispatcher;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerIngestDispatcher.h` (Private)


#### class `UE::CaptureManager::FCaptureManagerIngestDispatcher`  
`class FCaptureManagerIngestDispatcher`  
_L24-86_
- desc: Deferred-launch dispatcher for Blueprint ingest async calls. Maintains a FIFO queue of pending ingest requests and launches at most MaxConcurrentIngests tasks at once (read from UCaptureManagerEditorSettings at each launch). Tasks are only created when a slot is free - no worker threads are ever blocked waiting for a slot.
- L33 _public prototype_ `void Shutdown();` — Drain active tasks and reject future work. Signals all running ingests to stop via their FStopToken, discards queued items, then blocks until every in-flight task has completed. Called from ShutdownModule on the game thread.
- L35 _public prototype_ `int32 Enqueue( ECaptureManagerIngestType IngestType, TFunction<UFootageCaptureData*(FText&, int32, const FStopToken&)> SyncIngestFn, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );`
- L52 _public prototype_ `bool CancelIngest(int32 InIngestId);` — Cancel a queued or running ingest. Queued ingests are removed from the queue and their OnFailure delegate is fired on the game thread with a "canceled" message. Running ingests are signaled via FStopToken - conversion nodes will bail at their next check. @return true if the IngestId was found (queued or running), false if it was already completed, already canceled, or never existed.
- L66 _private prototype_ `void TryLaunchNext();` — Must be called under Lock.
- L68 _private member_ `FCriticalSection Lock;`
- L69 _private member_ `TArray<FPendingIngest> Queue;`
- L70 _private member_ `int32 ActiveCount = 0;`
- L71 _private member_ `int32 NextIngestId = 1;`
- L78 _private member_ `TMap<int32, TSharedPtr<FStopRequester>> ActiveRequesters;` — Maps IngestId to the stop requester for currently running ingests. Entries are added in TryLaunchNext before the task launches and removed inside the task lambda under Lock before ActiveCount is decremented. The TSharedPtr is also held by the task lambda, so the requester remains valid for the entire task lifetime.
- L83 _private member_ `TMap<int32, UE::Tasks::FTask> ActiveTasks;` — Task handles for currently running ingests, keyed by IngestId. Mirrors ActiveRequesters lifecycle. Used by Shutdown() to wait for in-flight tasks before the dispatcher is destroyed.
- L85 _private member_ `bool bShuttingDown = false;`

#### struct `UE::CaptureManager::FCaptureManagerIngestDispatcher::FPendingIngest`  
`struct FPendingIngest`  
_L55-63_
- L57 _public member_ `int32 IngestId;`
- L58 _public member_ `ECaptureManagerIngestType IngestType;`
- L59 _public member_ `TFunction<UFootageCaptureData*(FText&, int32, const FStopToken&)> SyncIngestFn;`
- L60 _public member_ `FCaptureManagerIngestSuccess OnSuccess;`
- L61 _public member_ `FCaptureManagerIngestFailed OnFailure;`
- L62 _public member_ `TSharedPtr<FStopRequester> StopRequester;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerIngestFromMetadata.h` (Private)


#### struct `UE::CaptureManager::FIngestPipelineOptions`  
`struct FIngestPipelineOptions`  
_L22-29_
- desc: Configuration for IngestFromMetadata sourced from editor settings by the caller. Settings are read once at the call site (per-device Blueprint function) and passed in rather than accessed internally.
- L24 _public member_ `FString WorkingDirectory;`
- L25 _public member_ `TOptional<FString> EncoderPath;` — set only when third-party encoder is enabled
- L26 _public member_ `FString CustomAudioCommandArguments;` — empty = use built-in default
- L27 _public member_ `FString CustomVideoCommandArguments;` — empty = use built-in default
- L28 _public member_ `bool bAutoSaveAssets = true;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CaptureManager` (scope `UE`)
- L43 _prototype_ `UFootageCaptureData* IngestFromMetadata( const FTakeMetadata& InMetadata, const FString& InTakeOriginDirectory, const FCaptureManagerConversionParams& InParams, const FIngestPipelineOptions& InOptions, FText& OutErrorMessage, TOptional<FStopToken> InStopToken = {} );` (scope `UE::CaptureManager`) — Shared ingest pipeline: working directory creation, conversion, intermediate-file parsing, and game-thread asset creation. Called by every per-device Blueprint ingest function after metadata extraction. @param InMetadata             Extracted take metadata (device-agnostic). @param InTakeOriginDirectory  Absolute path to the directory that contains the source media files. @param InParams               Conversion output format options. @param InOptions              Pipeline configuration sourced from editor settings by the caller. @param OutErrorMessage        Populated on failure. @return                       The created asset, or nullptr on failure.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerIngestLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManagerIngest, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManagerIngest, Log, All);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerIngestBlueprint/Private/CaptureManagerRunIngestAsync.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)
- L19 _prototype_ `int32 RunIngestAsync( ECaptureManagerIngestType IngestType, TFunction<UFootageCaptureData*(FText&, int32, const FStopToken&)> SyncIngestFn, FCaptureManagerIngestSuccess OnSuccess, FCaptureManagerIngestFailed OnFailure );` (scope `UE::CaptureManager`) — Generic async wrapper for all per-device Blueprint ingest functions. Enqueues SyncIngestFn via the ingest dispatcher and marshals the result back to the game thread, firing OnSuccess or OnFailure accordingly.
- L30 _prototype_ `bool CancelIngest(int32 InIngestId);` (scope `UE::CaptureManager`) — Cancel a queued or running ingest by its ID. @return true if the IngestId was found and cancellation was initiated.
