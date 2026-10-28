# Plugins / VisualStudioCodeSourceCodeAccess

- module root: `Plugins/Developer/VisualStudioCodeSourceCodeAccess/Source/VisualStudioCodeSourceCodeAccess`
- headers: 2; symbols: 31
- symbol kinds: class=2, function=2, member=5, prototype=21, struct=1
- PrivateDependencyModuleNames: Core, DesktopPlatform, HotReload, Projects, SourceCodeAccess

### `Plugins/Developer/VisualStudioCodeSourceCodeAccess/Source/VisualStudioCodeSourceCodeAccess/Private/VisualStudioCodeSourceCodeAccessModule.h` (Private)


#### class `FVisualStudioCodeSourceCodeAccessModule`  
`class FVisualStudioCodeSourceCodeAccessModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L13 _public prototype_ `FVisualStudioCodeSourceCodeAccessModule();`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `FVisualStudioCodeSourceCodeAccessor& GetAccessor();`
- L23 _private member_ `TSharedRef<FVisualStudioCodeSourceCodeAccessor> VisualStudioCodeSourceCodeAccessor;`

### `Plugins/Developer/VisualStudioCodeSourceCodeAccess/Source/VisualStudioCodeSourceCodeAccess/Private/VisualStudioCodeSourceCodeAccessor.h` (Private)


#### class `FVisualStudioCodeSourceCodeAccessor`  
`class FVisualStudioCodeSourceCodeAccessor : public ISourceCodeAccessor`  
_L6-61_
- inherits: `ISourceCodeAccessor`
- L9 _public function_ `FVisualStudioCodeSourceCodeAccessor()`
- L14 _public prototype_ `void Startup();` — Initialise internal systems, register delegates etc.
- L17 _public prototype_ `void Shutdown();` — Shut down internal systems, unregister delegates etc.
- L20 _public prototype_ `virtual void RefreshAvailability() override;` — ISourceCodeAccessor implementation
- L21 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L22 _public prototype_ `virtual FName GetFName() const override;`
- L23 _public prototype_ `virtual FText GetNameText() const override;`
- L24 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L25 _public prototype_ `virtual bool OpenSolution() override;`
- L26 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L27 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L28 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L29 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L30 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L31 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L32 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L48 _private member_ `FLocation Location;` — Location instance
- L51 _private member_ `mutable FString CachedSolutionPath;` — String storing the solution path obtained from the module manager to avoid having to use it on a thread
- L54 _private member_ `mutable FCriticalSection CachedSolutionPathCriticalSection;` — Critical section for updating SolutionPath
- L57 _private prototype_ `FString GetSolutionPath() const;` — Accessor for SolutionPath. Will try to update it when called from the game thread, otherwise will use the cached value
- L60 _private prototype_ `bool Launch(const TArray<FString>& InArgs);` — Helper function for launching the VSCode instance with the given list of arguments

#### struct `FVisualStudioCodeSourceCodeAccessor::FLocation`  
`struct FLocation`  
_L37-45_
- desc: Wrapper for vscode executable launch information
- L39 _public function_ `bool IsValid() const`
- L44 _public member_ `FString URL;`
