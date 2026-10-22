# Developer / ScreenShotComparisonTools

- module root: `Source/Developer/ScreenShotComparisonTools`
- headers: 6; symbols: 157
- symbol kinds: class=7, delegate=1, enum=4, enumerator=12, function=28, macro=2, member=53, prototype=43, struct=5, typedef=2
- PrivateDependencyModuleNames: AutomationMessages, DesktopPlatform, ImageWrapper, Json, JsonUtilities, RenderCore
- PrivateIncludePathModuleNames: LauncherServices, MessagingCommon
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/ScreenShotComparisonTools/Private/ScreenShotManager.h` (Private)


#### class `FScreenShotManager`  
`class FScreenShotManager : public IScreenShotManager`  
_L24-88_
- inherits: `IScreenShotManager`
- desc: Implements the ScreenShotManager that contains screen shot data.
- L38 _public prototype_ `FScreenShotManager();` — Creates and initializes a new instance.
- L40 _public prototype_ `~FScreenShotManager();`
- L46 _public prototype_ `virtual TFuture<FImageComparisonResult> CompareScreenshotAsync(const FString& IncomingPath, const FAutomationScreenshotMetadata& MetaData, const EScreenShotCompareOptions Options) override;`
- L48 _public prototype_ `virtual FScreenshotExportResult ExportScreenshotComparisonResult(FString ScreenshotName, FString ExportPath = TEXT(""), bool bOnlyGeneratedFiles = false) override;`
- L50 _public prototype_ `TFuture<TSharedPtr<TArray<FComparisonReport>>> OpenComparisonReportsAsync(const FString& ImportPath) override;`
- L52 _public prototype_ `virtual FString GetIdealApprovedFolderForImage(const FAutomationScreenshotMetadata& MetaData) const override;`
- L54 _public prototype_ `virtual TArray<FString> FindApprovedFiles(const FAutomationScreenshotMetadata& IncomingMetaData, const FString& FilePattern) const override;`
- L56 _public prototype_ `virtual TSharedPtr<FImageComparisonResult> CompareImageSequence(const TMap<FString, FString>& Sequence, const FAutomationScreenshotMetadata& Metadata) override;`
- L58 _public prototype_ `virtual void NotifyAutomationTestFrameworkOfImageComparison(const FImageComparisonResult& Result) override;`
- L64 _private prototype_ `FString GetPathComponentForRHI(const FAutomationScreenshotMetadata& MetaData) const;`
- L65 _private prototype_ `FString GetPathComponentForPlatformAndRHI(const FAutomationScreenshotMetadata& MetaData) const;`
- L66 _private prototype_ `FString GetPathComponentForTestImages(const FAutomationScreenshotMetadata& MetaData, bool bIncludeVariantName) const;`
- L69 _private prototype_ `FString GetApprovedFolderForImageWithOptions(const FAutomationScreenshotMetadata& MetaData, EApprovedFolderOptions InOptions) const;`
- L71 _private prototype_ `FString GetDefaultExportDirectory() const;`
- L73 _private prototype_ `FImageComparisonResult CompareScreenshot(const FString& IncomingPath, const FAutomationScreenshotMetadata& MetaData, const EScreenShotCompareOptions Options);`
- L75 _private prototype_ `void CopyDirectory(const FString& DestDir, const FString& SrcDir, const TArray<FString> Patterns);`
- L77 _private prototype_ `void BuildFallbackPlatformsListFromConfig();`
- L81 _private member_ `FString ScreenshotTempDeltaFolder;`
- L82 _private member_ `FString ScreenshotResultsFolder;`
- L83 _private member_ `TSharedPtr<TArray<FString>> PendingComparisonReportPaths;`
- L85 _private member_ `TMap<FString, FString> FallbackPlatforms;`
- L87 _private member_ `bool bUseConfidentialPlatformPaths;`

#### enum `FScreenShotManager::EApprovedFolderOptions`  
`enum class EApprovedFolderOptions : int8`  
_L28-32_
- L30 _public enumerator_ `None = 0`
- L31 _public enumerator_ `UsePlatformFolders = 1 << 0`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenShotManager, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenShotManager, Log, All);`
- L90 _function_ `inline FScreenShotManager::EApprovedFolderOptions operator | (FScreenShotManager::EApprovedFolderOptions lhs, FScreenShotManager::EApprovedFolderOptions rhs)`
- L95 _function_ `inline bool operator & (FScreenShotManager::EApprovedFolderOptions& lhs, FScreenShotManager::EApprovedFolderOptions rhs)`

### `Source/Developer/ScreenShotComparisonTools/Public/ImageComparer.h` (Public)


#### struct `FImageTolerance`  
`struct FImageTolerance`  
_L28-97_
- reflection: `USTRUCT()`
- L35 _public member_ `uint8 Red;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L38 _public member_ `uint8 Green;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L41 _public member_ `uint8 Blue;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L44 _public member_ `uint8 Alpha;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L47 _public member_ `uint8 MinBrightness;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L50 _public member_ `uint8 MaxBrightness;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L53 _public member_ `bool IgnoreAntiAliasing;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L56 _public member_ `bool IgnoreColors;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L59 _public member_ `float MaximumLocalError;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L62 _public member_ `float MaximumGlobalError;` — `UPROPERTY(EditAnywhere, Category = Automation)`
- L64 _public function_ `FImageTolerance() : Red(0) , Green(0) , Blue(0) , Alpha(0) , MinBrightness(0) , MaxBrightness(255) , IgnoreAntiAliasing(false) , IgnoreColors(false) , MaximumLocalError(0.0f) , MaximumGlobalError(0.0f)`
- L78 _public function_ `FImageTolerance(uint8 R, uint8 G, uint8 B, uint8 A, uint8 InMinBrightness, uint8 InMaxBrightness, bool InIgnoreAntiAliasing, bool InIgnoreColors, float InMaximumLocalError, float InMaximumGlobalError) : Red(R) , Green(G) , Blue(B) , Alpha(A) , MinBrightness(InMinBrightness) , MaxBrightness(InMaxBrightness) , IgnoreAntiAliasing(InIgnoreAntiAliasing) , IgnoreColors(InIgnoreColors) , MaximumLocalError(InMaximumLocalError) , MaximumGlobalError(InMaximumGlobalError)`
- L93 _public member_ `const static FImageTolerance DefaultIgnoreNothing;`
- L94 _public member_ `const static FImageTolerance DefaultIgnoreLess;`
- L95 _public member_ `const static FImageTolerance DefaultIgnoreAntiAliasing;`
- L96 _public member_ `const static FImageTolerance DefaultIgnoreColors;`

#### enum `EImageTolerancePreset`  
`enum class EImageTolerancePreset : uint8`  
_L100-107_
- reflection: `UENUM()`
- L102 _public enumerator_ `IgnoreNothing`
- L103 _public enumerator_ `IgnoreLess`
- L104 _public enumerator_ `IgnoreAntiAliasing`
- L105 _public enumerator_ `IgnoreColors`
- L106 _public enumerator_ `Custom`

#### class `FPixelOperations`  
`class FPixelOperations`  
_L127-175_
- L130 _public function_ `static FORCEINLINE double GetLuminance(const FColor& Color)`
- L136 _public function_ `static bool IsBrightnessSimilar(const FColor& ColorA, const FColor& ColorB, const FImageTolerance& Tolerance)`
- L147 _public function_ `static FORCEINLINE bool IsRGBSame(const FColor& ColorA, const FColor& ColorB)`
- L154 _public function_ `static FORCEINLINE bool IsRGBSimilar(const FColor& ColorA, const FColor& ColorB, const FImageTolerance& Tolerance)`
- L164 _public function_ `static FORCEINLINE bool IsContrasting(const FColor& ColorA, const FColor& ColorB, const FImageTolerance& Tolerance)`
- L172 _public prototype_ `static float GetHue(const FColor& Color);`
- L174 _public prototype_ `static bool IsAntialiased(const FColor& SourcePixel, const FComparableImage* Image, int32 X, int32 Y, const FImageTolerance& Tolerance);`

#### class `FComparableImage`  
`class FComparableImage`  
_L180-229_
- L183 _public member_ `int32 Width = 0;`
- L184 _public member_ `int32 Height = 0;`
- L185 _public member_ `TArray64<uint8> Bytes;`
- L187 _public function_ `FComparableImage()`
- L191 _public function_ `FORCEINLINE bool CanGetPixel(int32 X, int32 Y) const`
- L196 _public function_ `FORCEINLINE FColor GetPixel(int32 X, int32 Y) const`
- L216 _public prototype_ `bool LoadFile(const FString& ImagePath, FText& OutError);` — Populate image by loading an file @param ImagePath Path for the image file to load @param OutError Contains the error message if load fails @return true if success
- L228 _public prototype_ `bool LoadCompressedData(const void* CompressedData, int64 CompressedSize, const FString& ImageExtension, FText& OutError);` — Populate image by loading compressed data @param CompressedData The memory address of the start of the compressed data. @param CompressedSize The size of the compressed data parsed. @param ImageExtension File extension of the image format @param OutError Contains the error message if load fails @return true if success

#### struct `FImageComparisonResult`  
`struct FImageComparisonResult`  
_L240-436_
- reflection: `USTRUCT()`
- desc: This struct holds the results of comparing an incoming image from a platform with an approved image that exists under the project hierarchy. All paths in this structure should be portable. Test results (including this struct) result can be serialized to JSON and stored on the network as during automation runs then opened in the editor to commit / approve changes to the local project.
- L250 _public member_ `FDateTime CreationTime;` — `UPROPERTY()` — Time that the comparison was performed
- L256 _public member_ `FString SourcePlatform;` — `UPROPERTY()` — Platform that the incoming image was generated on
- L262 _public member_ `FString SourceRHI;` — `UPROPERTY()` — RHI that the incoming image was generated with
- L271 _public member_ `FString IdealApprovedFolderPath;` — `UPROPERTY()` — Path to a folder where the idealized ground-truth for this comparison would be. Relative to the project directory. Note: This path may not exist a fallback is being used for approval, or if there is no approved image at all. Comparing this value with the FPaths::GetPath(ApprovedFilePath) can be used to determine that. (the IsIdeal() function performs that check).
- L277 _public member_ `FString ApprovedFilePath;` — `UPROPERTY()` — Path to the file that was considered as the ground-truth. Relative to the project directory
- L283 _public member_ `FString IncomingFilePath;` — `UPROPERTY()` — Path to the file that was generated in the test. Relative to the project directory, only valid when a test is run locally
- L289 _public member_ `FString ComparisonFilePath;` — `UPROPERTY()` — Path to the delta image between the ground-truth and the incoming file. Relative to the project directory, only valid when a test is run locally
- L295 _public member_ `FString ReportApprovedFilePath;` — `UPROPERTY()` — Name of the approved file saved for the report. Path is relative to the location of the metadata for the report
- L301 _public member_ `FString ReportIncomingFilePath;` — `UPROPERTY()` — name of the incoming file saved for the report.  Path is relative to the location of the metadata for the report
- L307 _public member_ `FString ReportComparisonFilePath;` — `UPROPERTY()` — Name of the delta image saved for the report.  Path is relative to the location of the metadata for the report
- L313 _public member_ `double MaxLocalDifference;` — `UPROPERTY()` — Largest local difference found during comparison
- L319 _public member_ `double GlobalDifference;` — `UPROPERTY()` — Global difference found during comparison
- L325 _public member_ `FImageTolerance Tolerance;` — `UPROPERTY()` — Tolerance values for comparison
- L331 _public member_ `FText ErrorMessage;` — `UPROPERTY()` — Error message that can be set during a comparison
- L337 _public member_ `FString ScreenshotPath;` — `UPROPERTY()` — Path of the screenshot (includes variant if applicable)
- L343 _public member_ `FGuid ComparisonId;` — `UPROPERTY()` — Id of the comparison request
- L349 _public member_ `bool bSkipAttachingImages;` — `UPROPERTY()` — Whether to skip saving and attaching images to the report for this test
- L355 _public member_ `int32 Version;` — `UPROPERTY()` — Version of the image comparision result
- L357 _public member_ `static constexpr int32 CurrentVersion = 3;`
- L358 _public member_ `static constexpr int32 OldestSupportedVersion = 2;`
- L360 _public function_ `FImageComparisonResult() : CreationTime(0) , MaxLocalDifference(0.0f) , GlobalDifference(0.0f) , ErrorMessage() , bSkipAttachingImages(false) , Version(CurrentVersion)`
- L370 _public function_ `FImageComparisonResult(const FText& Error) : CreationTime(0) , MaxLocalDifference(0.0f) , GlobalDifference(0.0f) , ErrorMessage(Error) , bSkipAttachingImages(false) , Version(CurrentVersion)`
- L383 _public function_ `bool IsValid() const` — Returns true if this is a new image with no approved file to compare against
- L392 _public function_ `void SetInvalid()` — Marks this struct as invalid. Can be used before serializing in to ensure very old files with no version info aren't recognized.
- L400 _public function_ `bool IsNew() const` — Returns true if this is a new image with no approved file to compare against
- L409 _public function_ `bool IsIdeal() const` — Returns true if this is am ideal comparison (e.g not using a fallback for comparison)
- L417 _public function_ `bool AreSimilar() const` — Returns true if the images were within the provided tolerance values

#### struct `FComparisonReport`  
`struct FComparisonReport`  
_L438-480_
- L447 _public prototype_ `FComparisonReport(const FString& InReportRootDirectory, const FString& InReportFile);`
- L449 _public function_ `void SetComparisonResult(const FImageComparisonResult& InResult)`
- L454 _public function_ `const FImageComparisonResult& GetComparisonResult() const`
- L462 _public function_ `const FString& GetReportFile() const` — Return the path to the file used to generate this report
- L467 _public function_ `const FString& GetReportPath() const` — Return the path to all files in this report
- L472 _public function_ `const FString& GetReportRootDirectory() const` — Return the path to a location where all reports (including this one) are kept in this session
- L476 _private member_ `FString ReportRootDirectory;`
- L477 _private member_ `FString ReportFile;`
- L478 _private member_ `FString ReportPath;`
- L479 _private member_ `FImageComparisonResult Comparison;`

#### class `FImageComparer`  
`class FImageComparer`  
_L485-503_
- L489 _public prototype_ `FImageComparisonResult Compare(const FString& ImagePathA, const FString& ImagePathB, FImageTolerance Tolerance, const FString& OutDeltaPath);`
- L490 _public prototype_ `FImageComparisonResult Compare(const FComparableImage* ImageA, const FComparableImage* ImageB, FImageTolerance Tolerance, const FString& OutDeltaPath);`
- L501 _public prototype_ `double CompareStructuralSimilarity(const FString& ImagePathA, const FString& ImagePathB, EStructuralSimilarityComponent InCompareComponent, const FString& OutDeltaPath);` — https://en.wikipedia.org/wiki/Structural_similarity
- L502 _public prototype_ `double CompareStructuralSimilarity(const FComparableImage* ImageA, const FComparableImage* ImageB, EStructuralSimilarityComponent InCompareComponent, const FString& OutDeltaPath);`

#### enum `FImageComparer::EStructuralSimilarityComponent`  
`enum class EStructuralSimilarityComponent : uint8`  
_L492-496_
- L494 _public enumerator_ `Luminance`
- L495 _public enumerator_ `Color`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SCREENSHOTCOMPARISONTOOLS_API`
- L109 _function_ `static FImageTolerance GetImageToleranceForPreset(EImageTolerancePreset Preset, FImageTolerance CustomTolerance)`

### `Source/Developer/ScreenShotComparisonTools/Public/Interfaces/IScreenShotManager.h` (Public)


#### struct `FScreenshotExportResult`  
`struct FScreenshotExportResult`  
_L26-35_
- L28 _public member_ `bool Success;`
- L29 _public member_ `FString ExportPath;`
- L31 _public function_ `FScreenshotExportResult() : Success(false)`

#### enum `EScreenShotCompareOptions`  
`enum class EScreenShotCompareOptions`  
_L40-45_
- desc: Describes options available when comparing screenshots
- L42 _public enumerator_ `None`
- L43 _public enumerator_ `DiscardImage`
- L44 _public enumerator_ `KeepImage`

#### class `IScreenShotManager`  
`class IScreenShotManager`  
_L51-98_
- desc: Interface that defines a class which is capable of comparing screenshots at a provided path with checked in ground truth versions and generate results and reports.
- L55 _public prototype_ `virtual ~IScreenShotManager()= default;`
- L66 _public prototype_ `virtual TFuture<FImageComparisonResult> CompareScreenshotAsync(const FString& IncomingPath, const FAutomationScreenshotMetadata& MetaData, const EScreenShotCompareOptions Options) = 0;` — Takes the file at the provided path and uses the metadata to find and compare it with a ground truth version. @param IncomingPath		Path to the file. The file can reside anywhere but for best practices it should be under FPaths::AutomationTransientDir() @param MetaData			Meta data for the image. This should have been created when the image was captured and is usually at the same path but with a json extension @param Options			Comparison options. Use EScreenShotCompareOptions::DiscardImage if the incoming image does not need to be preserved (implicit if the path is under a transient dir) @return TFuture<FImageComparisonResult>
- L71 _public prototype_ `virtual FScreenshotExportResult ExportScreenshotComparisonResult(FString ScreenshotName, FString ExportPath = FString{}, bool bOnlyGeneratedFiles = false) = 0;` — Exports target screenshot report to the export location specified
- L76 _public prototype_ `virtual TFuture<TSharedPtr<TArray<FComparisonReport>>> OpenComparisonReportsAsync(const FString& ImportPath) = 0;` — Imports screenshot comparison data from a given path asynchronously.
- L82 _public prototype_ `virtual FString GetIdealApprovedFolderForImage(const FAutomationScreenshotMetadata& MetaData) const = 0;` — Calculate the ideal path for already already approved (ground truth) images. This handles abstracting away where Ground Truth images should be saved based on the platform/rhi/etc.
- L87 _public prototype_ `virtual TArray<FString> FindApprovedFiles(const FAutomationScreenshotMetadata& IncomingMetaData, const FString& FilePattern) const = 0;` — Find the all the files that are approved for the given metadata and file pattern
- L92 _public prototype_ `virtual TSharedPtr<FImageComparisonResult> CompareImageSequence(const TMap<FString, FString>& Sequence, const FAutomationScreenshotMetadata& Metadata) = 0;` — Compare a sequence of images. If the returned value is null no comparison failed. Otherwise return the first failing frame.
- L97 _public prototype_ `virtual void NotifyAutomationTestFrameworkOfImageComparison(const FImageComparisonResult& Result) = 0;` — Notify the automation test framework of an image comparison result

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TSharedPtr<class IScreenShotManager> IScreenShotManagerPtr;` — Type definition for shared pointers to instances of IScreenShotManager.
- L24 _typedef_ `typedef TSharedRef<class IScreenShotManager> IScreenShotManagerRef;` — Type definition for shared references to instances of IScreenShotManager.

### `Source/Developer/ScreenShotComparisonTools/Public/Interfaces/IScreenShotToolsModule.h` (Public)


#### class `IScreenShotToolsModule`  
`class IScreenShotToolsModule : public IModuleInterface`  
_L16-34_
- inherits: `IModuleInterface`
- desc: Interface for session core modules.
- L26 _public prototype_ `virtual IScreenShotManagerPtr GetScreenShotManager( ) = 0;` — Get the session manager. @return The session manager.
- L33 _public prototype_ `virtual ~IScreenShotToolsModule( ) = default;` — Virtual destructor.

### `Source/Developer/ScreenShotComparisonTools/Public/ScreenShotComparisonSettings.h` (Public)


#### struct `FScreenshotFallbackEntry`  
`struct FScreenshotFallbackEntry`  
_L17-31_
- reflection: `USTRUCT()`
- desc: Holds settings for screenshot fallbacks
- L22 _public member_ `FString Parent;` — `UPROPERTY(Config)`
- L25 _public member_ `FString Child;` — `UPROPERTY(Config)`
- L27 _public function_ `bool operator==(const FScreenshotFallbackEntry& Other) const`

#### class `UScreenShotComparisonSettings`  
`class UScreenShotComparisonSettings : public UObject`  
_L39-93_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- L49 _public member_ `bool bUseConfidentialPlatformPathsForSavedResults;` — `UPROPERTY(Config)` — If true, any checked-in test results for confidential platforms will be put under <ProjectDir>/Platforms/<Platform>/Test instead of <ProjectDir>/Test
- L55 _public member_ `TArray<FScreenshotFallbackEntry> ScreenshotFallbackPlatforms;` — `UPROPERTY(Config)` — An array of entries that describe other platforms we can use for fallbacks when comparing screenshots
- L61 _public prototype_ `static UScreenShotComparisonSettings* Create(const FString& PlatformName = FString{});` — Creates class instance @param PlatformName Reference to a string containing platform name (if it is empty the current platform name is used).
- L66 _public prototype_ `virtual void LoadSettings() final;` — Loads settings of corresponding config.
- L71 _public prototype_ `virtual const TCHAR* GetConfigOverridePlatform() const override;` — Overrides config hierarchy platform to be used in UObject internals
- L75 _public prototype_ `static const TSet<FScreenshotFallbackEntry>& GetAllPlatformSettings();`
- L83 _protected prototype_ `virtual const FString& GetPlatformName() const;` — Returns platform name reference. As the class can store platform-independent config, it returns an empty string if the platform was not specified.
- L89 _protected prototype_ `virtual void SetPlatform(const FString& PlatformName);` — Sets platform and reloads settings. @param PlatformName Reference to a string containing platform name (if it is empty the default config is used).
- L92 _private member_ `FString Platform;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCREENSHOTCOMPARISONTOOLS_API`
- L33 _function_ `FORCEINLINE uint32 GetTypeHash(const FScreenshotFallbackEntry& Object)`

### `Source/Developer/ScreenShotComparisonTools/Public/ScreenShotComparisonTools.h` (Public)
_(no declarations extracted)_
