# Developer / ScreenShotComparison

- module root: `Source/Developer/ScreenShotComparison`
- headers: 7; symbols: 107
- symbol kinds: class=6, delegate=1, function=5, member=37, prototype=57, struct=1
- PrivateDependencyModuleNames: AutomationMessages, CoreUObject, DesktopWidgets, DirectoryWatcher, ImageWrapper, InputCore, Json, JsonUtilities, ScreenShotComparisonTools, Slate, SlateCore, SourceControl, ToolWidgets
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core

### `Source/Developer/ScreenShotComparison/Private/Models/ScreenComparisonModel.h` (Private)


#### class `FScreenComparisonModel`  
`class FScreenComparisonModel`  
_L11-60_
- L14 _public prototype_ `FScreenComparisonModel(const FComparisonReport& InReport);`
- L16 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnComplete);`
- L17 _public member_ `FOnComplete OnComplete;`
- L19 _public member_ `FComparisonReport Report;`
- L21 _public prototype_ `bool IsComplete() const;`
- L23 _public prototype_ `void Complete(bool WasSuccessful);`
- L25 _public prototype_ `bool AddNew();`
- L26 _public prototype_ `bool Replace();`
- L27 _public prototype_ `bool AddAlternative();`
- L29 _public prototype_ `TOptional<FAutomationScreenshotMetadata> GetMetadata();`
- L30 _public prototype_ `FString GetName();`
- L34 _private prototype_ `bool RemoveExistingApproved();`
- L35 _private prototype_ `void TryLoadMetadata();`
- L38 _private member_ `bool bComplete;`
- L40 _private member_ `TOptional<FAutomationScreenshotMetadata> Metadata;`
- L41 _private member_ `FString Name;`
- L59 _private member_ `TArray<FFileMapping> FileImports;`

#### struct `FScreenComparisonModel::FFileMapping`  
`struct FFileMapping`  
_L43-56_
- L45 _public function_ `FFileMapping(const FString& InDestFile, const FString& InSourceFile) : DestinationFile(InDestFile) , SourceFile(InSourceFile)`
- L52 _public member_ `FString DestinationFile;` — local file we'd write to on disk
- L55 _public member_ `FString SourceFile;` — input file from the report

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnComplete);`

### `Source/Developer/ScreenShotComparison/Private/Widgets/SAsyncImage.h` (Private)


#### class `SAsyncImage`  
`class SAsyncImage : public SCompoundWidget`  
_L11-33_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SAsyncImage)`
- L15 _public prototype_ `SLATE_ARGUMENT(FString, ImageFilePath) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L22 _public prototype_ `TSharedPtr<FSlateDynamicImageBrush> GetDynamicBrush();`
- L25 _private member_ `FString ImageFilePath;`
- L26 _private member_ `TSharedPtr<SImage> Image;`
- L27 _private member_ `TSharedPtr<SCircularThrobber> Progress;`
- L28 _private member_ `bool bLoaded;`
- L29 _private member_ `TFuture<FSlateTextureDataPtr> TextureFuture;`
- L30 _private member_ `TSharedPtr<FSlateDynamicImageBrush> DynamicBrush;`
- L32 _private prototype_ `static FSlateTextureDataPtr LoadScreenshot(FString ImagePath);`

### `Source/Developer/ScreenShotComparison/Private/Widgets/SScreenComparisonRow.h` (Private)


#### class `SScreenComparisonRow`  
`class SScreenComparisonRow : public SMultiColumnTableRow< TSharedPtr<FScreenComparisonModel> >`  
_L23-98_
- inherits: `SMultiColumnTableRow<TSharedPtr<FScreenComparisonModel>>`
- desc: Widget to display a particular view.
- L27 _public function_ `SLATE_BEGIN_ARGS( SScreenComparisonRow )`
- L30 _public prototype_ `SLATE_ARGUMENT( IScreenShotManagerPtr, ScreenshotManager ) SLATE_ARGUMENT( FString, ComparisonDirectory ) SLATE_ARGUMENT( TSharedPtr<FScreenComparisonModel>, ComparisonResult ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView );`
- L44 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L52 _public prototype_ `FText GetName() const;` — Get content of the Name column. @return FText object corresponding to the current object's content of the Name column.
- L55 _private prototype_ `bool CanUseSourceControl() const;`
- L56 _private prototype_ `bool IsComparingAgainstPlatformFallback() const;`
- L58 _private prototype_ `TSharedRef<SWidget> BuildAddedView();`
- L59 _private prototype_ `TSharedRef<SWidget> BuildComparisonPreview();`
- L61 _private prototype_ `FText GetAddNewButtonTooltip() const;`
- L62 _private prototype_ `bool CanAddNew() const;`
- L63 _private prototype_ `FReply AddNew();`
- L65 _private prototype_ `bool CanAddPlatformSpecificNew() const;`
- L66 _private prototype_ `FReply AddPlatformSpecificNew();`
- L68 _private prototype_ `bool CanReplace() const;`
- L69 _private prototype_ `FReply Replace();`
- L71 _private prototype_ `bool CanAddAsAlternative() const;`
- L72 _private prototype_ `FReply AddAlternative();`
- L74 _private prototype_ `FReply Remove();`
- L76 _private prototype_ `FReply OnCompareImages(const FGeometry& InGeometry, const FPointerEvent& InEvent);`
- L77 _private prototype_ `FReply OnCompareNewImage(const FGeometry& InGeometry, const FPointerEvent& InEvent);`
- L78 _private prototype_ `FReply OnImageClicked(const FGeometry& InGeometry, const FPointerEvent& InEvent, TSharedPtr<FSlateDynamicImageBrush> Image);`
- L83 _private member_ `TSharedPtr<FScreenComparisonModel> Model;` — Holds the screen shot info.
- L85 _private member_ `mutable TOptional<FText> Name;`
- L88 _private member_ `IScreenShotManagerPtr ScreenshotManager;` — The manager containing the screen shots
- L90 _private member_ `FString ComparisonDirectory;`
- L93 _private member_ `FIntPoint CachedActualImageSize;` — The cached actual size of the screenshot
- L95 _private member_ `TSharedPtr<SAsyncImage> ApprovedImageWidget;`
- L96 _private member_ `TSharedPtr<SAsyncImage> DeltaImageWidget;`
- L97 _private member_ `TSharedPtr<SAsyncImage> UnapprovedImageWidget;`

### `Source/Developer/ScreenShotComparison/Private/Widgets/SScreenShotBrowser.h` (Private)


#### class `SScreenShotBrowser`  
`class SScreenShotBrowser : public SCompoundWidget`  
_L22-143_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SScreenShotBrowser)`
- L37 _public prototype_ `void Construct( const FArguments& InArgs, IScreenShotManagerRef InScreenShotManager );` — Construct this widget. @param InArgs - The declaration data for this widget. @param InScreenShotManager - The screen shot manager containing the screen shot data.
- L38 _public prototype_ `virtual ~SScreenShotBrowser();`
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L44 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForScreenResults(TSharedPtr<FScreenComparisonModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L46 _public prototype_ `void DisplaySuccess_OnCheckStateChanged(ECheckBoxState NewRadioState);`
- L47 _public prototype_ `void DisplayError_OnCheckStateChanged(ECheckBoxState NewRadioState);`
- L48 _public prototype_ `void DisplayNew_OnCheckStateChanged(ECheckBoxState NewRadioState);`
- L49 _public prototype_ `void OnReportFilterTextChanged(const FText& InText);`
- L53 _private prototype_ `void OnDirectoryChanged(const FString& Directory);`
- L55 _private prototype_ `void RefreshDirectoryWatcher();`
- L57 _private prototype_ `void OnReportsChanged(const TArray<struct FFileChangeData>& );`
- L62 _private prototype_ `void RequestRebuildTree();` — Requests regeneration of the widgets when it is needed.
- L67 _private prototype_ `void ContinueRebuildTreeIfReady();` — Rebuilds screenshot tree if there are any pending comparison reports that are ready to be displayed.
- L72 _private prototype_ `void FinishRebuildTreeIfReady();` — Finishes rebuilding of screenshot tree if all the report model metadata is loaded.
- L77 _private prototype_ `EVisibility GetReportsVisibility() const;` — Gets reports tree widget visibility.
- L82 _private prototype_ `EVisibility GetReportsUpdatingThrobberVisibility() const;` — Gets throbber visibility (report tree rebuild process is in progress).
- L84 _private prototype_ `bool CanAddNewReportResult(const FImageComparisonResult& Comparison);`
- L93 _private prototype_ `bool MatchesReportFilterCriteria(const FString& ComparisonName, const FImageComparisonResult& ComparisonResult) const;` — Checks whether or not the information is valid against the report filtering criteria. @param ComparisonName - The name of the item to be checked against. @param ComparisonResult - The ImageComparisonResult used to be checked against the display criteria. @return true if the passed in information matches the current filtering criteria
- L98 _private prototype_ `void ApplyReportFilterToWidgets();` — Apply the current report filter to the widgets of comparison view.
- L103 _private member_ `IScreenShotManagerPtr ScreenShotManager;` — The manager containing the screen shots
- L106 _private member_ `FString ComparisonRoot;` — The directory where we're imported comparisons from.
- L109 _private member_ `TSharedPtr<TArray<FComparisonReport>> CurrentReports;` — The imported screenshot results
- L112 _private member_ `TArray<TSharedPtr<FScreenComparisonModel>> ComparisonList;` — The imported screenshot results copied into an array to be filtered
- L115 _private member_ `TArray<TSharedPtr<FScreenComparisonModel>> FilteredComparisonList;` — The filtered screenshot results copied into an array usable by the list view
- L118 _private member_ `TSharedPtr< SListView< TSharedPtr<FScreenComparisonModel> > > ComparisonView;`
- L121 _private member_ `FDelegateHandle DirectoryWatchingHandle;` — Directory watching handle
- L124 _private member_ `bool bReportsChanged;`
- L127 _private member_ `bool bDisplayingSuccess;` — Whether or not we're currently displaying successful tests
- L130 _private member_ `bool bDisplayingError;` — Whether or not we're currently displaying tests with errors
- L133 _private member_ `bool bDisplayingNew;` — Whether or not we're currently displaying warnings
- L136 _private member_ `FString ReportFilterString;` — Filter string for our reports, if any
- L139 _private member_ `TFuture<TSharedPtr<TArray<FComparisonReport>>> PendingOpenComparisonReportsResult;` — Stores comparison reports that are loaded asynchronously if ready
- L142 _private member_ `TFuture<TArray<TSharedPtr<FScreenComparisonModel>>> PendingScreenComparisonModelsLoadResult;` — Stores comparison reports' model objects that are loaded asynchronously if ready

### `Source/Developer/ScreenShotComparison/Private/Widgets/SScreenShotImagePopup.h` (Private)


#### class `SScreenShotImagePopup`  
`class SScreenShotImagePopup : public SCompoundWidget`  
_L17-43_
- inherits: `SCompoundWidget`
- desc: A widget to show a screen shot image as a pop up window
- L21 _public function_ `SLATE_BEGIN_ARGS( SScreenShotImagePopup )`
- L24 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FSlateDynamicImageBrush>, ImageBrush ) SLATE_ARGUMENT( FIntPoint, ImageSize ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The assest name for the screen shot
- L42 _private member_ `TSharedPtr<FSlateDynamicImageBrush> DynamicImageBrush;` — Holds the brush for this screenshot

### `Source/Developer/ScreenShotComparison/Public/Interfaces/IScreenShotComparisonModule.h` (Public)


#### class `IScreenShotComparisonModule`  
`class IScreenShotComparisonModule : public IModuleInterface`  
_L16-35_
- inherits: `IModuleInterface`
- desc: Interface for screen shot comparison UI modules.
- L27 _public prototype_ `virtual TSharedRef<class SWidget> CreateScreenShotComparison( const IScreenShotManagerRef& InScreenShotManager ) = 0;` — Creates a screen shot comparison widget. @param InScreenShotManager - the manager containing the screen shot data @return The new widget
- L34 _public prototype_ `virtual ~IScreenShotComparisonModule( ) = default;` — Virtual destructor.

### `Source/Developer/ScreenShotComparison/Public/ScreenShotComparison.h` (Public)
_(no declarations extracted)_
