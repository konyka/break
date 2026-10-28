# Plugins / VisualStudioSourceCodeAccess

- module root: `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess`
- headers: 4; symbols: 89
- symbol kinds: class=4, function=4, member=24, prototype=55, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, HotReload, Json, Projects, SourceCodeAccess, VisualStudioDTE, VisualStudioSetup

### `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess/Private/VisualStudioSourceCodeAccessModule.h` (Private)


#### class `FVisualStudioSourceCodeAccessModule`  
`class FVisualStudioSourceCodeAccessModule : public IModuleInterface`  
_L10-26_
- inherits: `IModuleInterface`
- L13 _public prototype_ `FVisualStudioSourceCodeAccessModule();`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `FVisualStudioSourceCodeAccessor& GetAccessor();`
- L22 _private prototype_ `void RegisterWrapper(FName Name, FText NameText, FText DescriptionText);`
- L24 _private member_ `TSharedRef<FVisualStudioSourceCodeAccessor> VisualStudioSourceCodeAccessor;`
- L25 _private member_ `TArray<TSharedRef<FVisualStudioSourceCodeAccessorWrapper>> Wrappers;`

### `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess/Private/VisualStudioSourceCodeAccessSettings.h` (Private)


#### class `UVisualStudioSourceCodeAccessSettings`  
`class UVisualStudioSourceCodeAccessSettings : public UObject`  
_L11-23_
- reflection: `UCLASS(config=EditorSettings)`
- inherits: `UObject`
- L18 _public member_ `bool bUproject;` — `UPROPERTY(Config, EditAnywhere, Category = "Visual Studio Source Code", meta = (DisplayName = "Direct Unreal Project Support"))` — Open a .uproject directly in Visual Studio instead of the generated .sln solution.
- L22 _public member_ `bool bPreview;` — `UPROPERTY(Config, EditAnywhere, Category = "Visual Studio Source Code", meta = (DisplayName = "Prefer Preview Releases"))` — Prefer preview releases of Visual Studio.

### `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess/Private/VisualStudioSourceCodeAccessor.h` (Private)


#### class `FVisualStudioSourceCodeAccessor`  
`class FVisualStudioSourceCodeAccessor : public ISourceCodeAccessor`  
_L7-191_
- inherits: `ISourceCodeAccessor`
- L21 _public function_ `FVisualStudioSourceCodeAccessor()`
- L26 _public prototype_ `void Startup();` — Initialise internal systems, register delegates etc.
- L29 _public prototype_ `void Shutdown();` — Shut down internal systems, unregister delegates etc.
- L32 _public prototype_ `virtual void RefreshAvailability() override;` — ISourceCodeAccessor implementation
- L33 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L34 _public prototype_ `virtual FName GetFName() const override;`
- L35 _public prototype_ `virtual FText GetNameText() const override;`
- L36 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L37 _public prototype_ `virtual bool OpenSolution() override;`
- L38 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L39 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L40 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L41 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L42 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L43 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L44 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L45 _public prototype_ `virtual FName GetOpenIconName() const override;`
- L46 _public prototype_ `virtual FName GetRefreshIconName() const override;`
- L71 _private prototype_ `bool CanRunVisualStudio(FString& OutPath, const FString& InSolution) const;` — Checks to see if we can run visual studio, also outputs the executable path if it's needed
- L74 _private prototype_ `bool RunVisualStudioAndOpenSolution(const FString& InSolution) const;` — Run an instance of visual studio instance if possible.
- L77 _private prototype_ `bool OpenVisualStudioFileAtLineInternal(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0);` — Opens a file in the correct running instance of Visual Studio at a line and optionally to a column.
- L80 _private prototype_ `bool OpenVisualStudioFilesInternal(const TArray<FileOpenRequest>& Requests);` — Opens multiple files in the correct running instance of Visual Studio.
- L83 _private prototype_ `void VSLaunchStarted();` — An instance of VS it attempting to be opened
- L90 _private prototype_ `void VSLaunchFinished( bool bSuccess );` — An instance of VS has finished processing @param	bSuccess	Whether VS has finished successfully or not
- L97 _private function_ `bool IsVSLaunchInProgress() const` — Are we trying to launch an instance of VS @return	true if we're in the middle of a VS instance being launched
- L105 _private prototype_ `void AddVisualStudioVersion(const int MajorVersion, const bool bAllowExpress = true);` — Add a new version of Visual Studio to the supported locations array @param	MajorVersion	The major version number of Visual Studio (eg, 17 for VS2022) @param	bAllowExpress	true to also add the express version of Visual Studio to the list of locations
- L112 _private prototype_ `void AddVisualStudioVersionUsingVisualStudioSetupAPI(const int MinimumVersionNumber);` — Add a new version of Visual Studio to the supported locations array using the Visual Studio Setup API @param	MinimumVersionNumber	The minimum major version number of Visual Studio (eg, 17 for VS2022) to return
- L123 _private prototype_ `int32 VisualStudioVersionSortWeight(const VisualStudioLocation& InLocation, const int32 ExactVersion, const bool bPreferPreview) const;` — Get the sort weight of a Visual Studio install when ordering by priority. @param	InLocation		The Visual Studio install @param	ExactVersion	The specific major version number of Visual Studio to prioritize @param	bPreferPreview	true if preview releases should be prioritized @return	The sort weight of an install location
- L130 _private prototype_ `TArray<VisualStudioLocation> GetPrioritizedVisualStudioVersions(const FString& InSolution) const;` — Get the prioritized list of VS install locations based upon the version of the given solution @return	The sorted array of install locations
- L139 _private prototype_ `bool RunVisualStudioAndOpenSolutionAndFiles(const FString& ExecutablePath, const FString& SolutionPath, const TArray<FileOpenRequest>* const Requests) const;` — Run a new instance Visual Studio, optionally opening the provided solution and list of files @param	ExecutablePath	Path to the Visual Studio executable to open @param	SolutionPath	Path to the solution to open, or an empty string to open no solution @param	Requests		Array of files to open, or null to open no files
- L148 _private prototype_ `FString RetrieveSolutionForFileOpenRequests(const TArray<FileOpenRequest>& Requests, const TArray<FString>& CurrentlyOpenedSolutions) const;` — Based on the list of file open requests and the list of solutions currently opened, make an educated guess as to which solution might be the most relevant to open them all @param	Requests					Array of files to open @param	CurrentlyOpenedSolutions	List of solutions currently opened by running VS instances @return the absolute file path to the most likely solution or an empty string if no solution was found
- L152 _private prototype_ `bool OpenVisualStudioSolutionViaDTE();` — DTE specific implementations
- L153 _private prototype_ `bool OpenVisualStudioFilesInternalViaDTE(const TArray<FileOpenRequest>& Requests, bool& bWasDeferred);`
- L156 _private prototype_ `bool OpenVisualStudioSolutionViaProcess();` — Fallback (non-DTE) implementations
- L157 _private prototype_ `bool OpenVisualStudioFilesInternalViaProcess(const TArray<FileOpenRequest>& Requests);`
- L162 _private member_ `static constexpr int32 MinimumVisualStudioVersion = 17;` — The minimum major version of Visual Studio we support (eg, 17 for Visual Studio 2022)
- L165 _private member_ `TArray<VisualStudioLocation> Locations;` — The versions of VS we support, in preference order
- L168 _private member_ `mutable FString CachedSolutionPath;` — String storing the solution path obtained from the module manager to avoid having to use it on a thread
- L171 _private member_ `mutable FString CachedSolutionPathOverride;` — Override for the cached solution path
- L174 _private member_ `double VSLaunchTime;` — If !0 it represents the time at which the a VS instance was opened
- L177 _private member_ `FCriticalSection DeferredRequestsCriticalSection;` — Critical section for updating DeferredRequests
- L180 _private member_ `mutable FCriticalSection CachedSolutionPathCriticalSection;` — Critical section for updating SolutionPath
- L183 _private member_ `TArray<FileOpenRequest> DeferredRequests;` — Array of file open requests that have been deferred because Visual Studio was not available when the request was made
- L186 _private prototype_ `FString GetSolutionPath() const;` — Accessor for SolutionPath. Will try to update it when called from the game thread, otherwise will use the cached value
- L189 _private member_ `FDelegateHandle SaveVisualStudioDocumentsDelegateHandle;`

#### struct `FVisualStudioSourceCodeAccessor::VisualStudioLocation`  
`struct VisualStudioLocation`  
_L11-19_
- desc: Struct representing identifying information about Visual Studio versions
- L13 _public member_ `int32 VersionNumber;`
- L14 _public member_ `bool bPreviewRelease;`
- L15 _public member_ `FString ExecutablePath;`
- L17 _public member_ `FString ROTMoniker;`

#### struct `FVisualStudioSourceCodeAccessor::FileOpenRequest`  
`struct FileOpenRequest`  
_L50-68_
- L52 _public member_ `FString FullPath;`
- L53 _public member_ `int32 LineNumber;`
- L54 _public member_ `int32 ColumnNumber;`
- L56 _public function_ `FileOpenRequest() : LineNumber(0) , ColumnNumber(0)`
- L62 _public function_ `FileOpenRequest(const FString& InitFullPath, int32 InitLineNumber, int32 InitColumnNumber) : FullPath(InitFullPath) , LineNumber(InitLineNumber) , ColumnNumber(InitColumnNumber)`

### `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess/Private/VisualStudioSourceCodeAccessorWrapper.h` (Private)


#### class `FVisualStudioSourceCodeAccessorWrapper`  
`class FVisualStudioSourceCodeAccessorWrapper : public ISourceCodeAccessor`  
_L6-33_
- inherits: `ISourceCodeAccessor`
- L9 _public prototype_ `FVisualStudioSourceCodeAccessorWrapper(const FName& InName, const FText& InNameText, const FText& InDescriptionText, const TSharedRef<FVisualStudioSourceCodeAccessor>& InInner);`
- L12 _public prototype_ `virtual void RefreshAvailability() override;` — ISourceCodeAccessor implementation
- L13 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L14 _public prototype_ `virtual FName GetFName() const override;`
- L15 _public prototype_ `virtual FText GetNameText() const override;`
- L16 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L17 _public prototype_ `virtual bool OpenSolution() override;`
- L18 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L19 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L20 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L21 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L22 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L23 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L24 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L25 _public prototype_ `virtual FName GetOpenIconName() const override;`
- L26 _public prototype_ `virtual FName GetRefreshIconName() const override;`
- L29 _private member_ `FName Name;`
- L30 _private member_ `FText NameText;`
- L31 _private member_ `FText DescriptionText;`
- L32 _private member_ `TSharedRef<FVisualStudioSourceCodeAccessor> Inner;`
