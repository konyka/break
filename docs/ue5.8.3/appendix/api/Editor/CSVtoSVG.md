# Editor / CSVtoSVG

- module root: `Source/Editor/CSVtoSVG`
- headers: 4; symbols: 62
- symbol kinds: class=4, delegate=2, enum=1, enumerator=2, function=3, member=32, prototype=18
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, EditorWidgets
- PrivateDependencyModuleNames: ContentBrowserData, Core, CoreUObject, EditorFramework, Engine, InputCore, Settings, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: WorkspaceMenuStructure
- PublicDependencyModuleNames: EditorConfig

### `Source/Editor/CSVtoSVG/Private/SCSVtoSVG.h` (Private)


#### class `SCSVtoSVG`  
`class SCSVtoSVG : public SCompoundWidget, public FNotifyHook`  
_L21-54_
- inherits: `SCompoundWidget,FNotifyHook`
- L23 _private function_ `SLATE_BEGIN_ARGS(SCSVtoSVG)`
- L27 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L32 _private prototype_ `~SCSVtoSVG();` — SCSVtoSVG destructor
- L36 _private prototype_ `FReply OnGenerateGraphClicked();`
- L38 _private prototype_ `void StatListSelectionChanged(const TArray<FString>& Stats);`
- L41 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L44 _private prototype_ `void LoadCSVFile(const FString& Filepath);`
- L47 _private member_ `TSharedPtr<IDetailsView> CSVtoSVGArgumentsDetailsView = nullptr;` — This is the Detail View for the currently selected UActorRecording or an item from an Extender
- L50 _private member_ `TSharedPtr<SStatList> StatListView = nullptr;` — The list of stats parsed from the CSV file.
- L53 _private member_ `TStrongObjectPtr<UCSVtoSVGArugments> Arguments = nullptr;` — The current arguments.

### `Source/Editor/CSVtoSVG/Private/SStatList.h` (Private)


#### class `SStatList`  
`class SStatList : public SCompoundWidget`  
_L23-43_
- inherits: `SCompoundWidget`
- L25 _private function_ `SLATE_BEGIN_ARGS(SStatList)`
- L29 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L33 _private prototype_ `void UpdateStatList(const TArray<FString>& StatNames);`
- L35 _private prototype_ `TArray<FString> GetSelectedStats() const;`
- L39 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> StatListView;`
- L42 _private member_ `TArray<TSharedPtr<FString>> StatList;`

### `Source/Editor/CSVtoSVG/Public/CSVtoSVGArguments.h` (Public)


#### enum `ESVGTheme`  
`enum class ESVGTheme`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `Dark`
- L26 _public enumerator_ `Light`

#### class `UCSVtoSVGArugments`  
`class UCSVtoSVGArugments : public UEditorConfigBase`  
_L30-125_
- reflection: `UCLASS(EditorConfig = "CSVtoSVG")`
- inherits: `UEditorConfigBase`
- L36 _private member_ `FFilePath CSV;` — `UPROPERTY(EditAnywhere, Category = RequiredArguments, meta = (EditorConfig, DisplayName = "CSV", Tooltip = "Specifies a list of CSVs separated by spaces"))` — The base directories to be considered Internal Only for the struct picker.
- L39 _private member_ `FDirectoryPath OutputDirectory;` — `UPROPERTY(EditAnywhere, Category = RequiredArguments, meta = (EditorConfig, DisplayName = "Ouput Directory", Tooltip = "Sets the filename for the SVG output."))`
- L42 _private member_ `FString OutputFilename;` — `UPROPERTY(EditAnywhere, Category = RequiredArguments, meta = (EditorConfig, DisplayName = "Ouput Filename", Tooltip = "Sets the filename for the SVG output."))`
- L45 _private member_ `int32 skipRows = 0;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Skip Rows", Tooltip = "Skips a specified number of rows in the CSV. This is useful for CSV file sgenerated from the FPSChartStart command, where there's a 4-row summary at the top."))`
- L48 _private member_ `float minX = -100000.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "minX", Tooltip = "Clamps the X and Y range of the source data."))`
- L51 _private member_ `float maxX = -100000.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "maxX ", Tooltip = "Clamps the X and Y range of the source data."))`
- L54 _private member_ `float minY = -100000.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "minY", Tooltip = "Clamps the X and Y range of the source data."))`
- L57 _private member_ `float maxY = -100000.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "maxY", Tooltip = "Clamps the X and Y range of the source data."))`
- L60 _private member_ `bool smooth = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Smooth", Tooltip = "Smooth the graph."))`
- L63 _private member_ `int32 smoothKernelSize = -1;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Smooth kernel size", Tooltip = "Specifies the smoothing kernel size in column entries to use."))`
- L66 _private member_ `float smoothKernelPercent = -1.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Smooth kernel size", Tooltip = "Specifies the smoothing kernel size as a percentage of the graph length."))`
- L69 _private member_ `int32 width = 1000;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Width", Tooltip = "The width of the graph."))`
- L72 _private member_ `int32 height = 500;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Height", Tooltip = "The height of the graph."))`
- L75 _private member_ `FString title;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Title", Tooltip = "Sets the title for the graph."))`
- L78 _private member_ `bool noMetadata = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "No Metadata", Tooltip = ""))`
- L81 _private member_ `bool graphOnly = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Graph only", Tooltip = "Render just the graph, no borders."))`
- L84 _private member_ `float budget = 33.3f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Budget [ms]", Tooltip = "Sets the budget line. Default is 33.3."))`
- L87 _private member_ `float thickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Thickness", Tooltip = "Sets the line thickness of the graph."))`
- L90 _private member_ `ESVGTheme theme = ESVGTheme::Dark;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Theme", Tooltip = ""))`
- L93 _private member_ `float threshold = -FLT_MAX;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Threshold", Tooltip = "Ignores stats which are entirely under this threshold."))`
- L96 _private member_ `bool stacked = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Stacked", Tooltip = "Makes a stacked graph for cumulative stats."))`
- L99 _private member_ `FString stacktotalstack;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Stacked Total Stat", Tooltip = "Specifies the total stat. Valid for stacked graphs only."))`
- L102 _private member_ `bool interactive = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Interactive", Tooltip = "Adds an interactive frame marker."))`
- L105 _private member_ `bool showaverages = false;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Show Averages", Tooltip = "Shows stat averages next to the legend and sorts the stats in the legend high to low by average value."))`
- L108 _private member_ `int colourOffset = 0;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Colour Offset", Tooltip = "Rotates the colours."))`
- L111 _private member_ `float averageThreshold = -FLT_MAX;` — `UPROPERTY(EditAnywhere, Category = OptionalArguments, meta = (EditorConfig, DisplayName = "Average Threshold", Tooltip = "Ignores stats whose average is under this threshold."))`
- L113 _private prototype_ `FString GetCommandLine() const;`
- L115 _private prototype_ `FString GetOutputFileName() const;`
- L118 _private function_ `FCSVtoSVGArugmentsPropertySetModifiedSignature& GetOnModified()` — @return the multicast delegate that is called when properties are modified
- L124 _private member_ `FCSVtoSVGArugmentsPropertySetModifiedSignature OnModified;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FCSVtoSVGArugmentsPropertySetModifiedSignature, UObject*, FProperty*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FCSVtoSVGArugmentsPropertySetModifiedSignature, UObject*, FProperty*);`

### `Source/Editor/CSVtoSVG/Public/CSVtoSVGModule.h` (Public)


#### class `FCSVtoSVGModule`  
`class FCSVtoSVGModule : public IModuleInterface`  
_L31-46_
- inherits: `IModuleInterface`
- desc: Struct Viewer module
- L37 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L42 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L45 _private prototype_ `TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& Args);`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCSVtoSVG, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCSVtoSVG, Log, All);`
- L26 _prototype_ `FFilePath GenerateSVG(const UCSVtoSVGArugments& Arguments, const TArray<FString>& StatList);` — Generates a SVG graph from the given arguments. @param	Arguments								The arguments to define and configure graph generation. @return	File path to the generated SVG file.
