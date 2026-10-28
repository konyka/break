# Plugins / KDevelopSourceCodeAccess

- module root: `Plugins/Developer/KDevelopSourceCodeAccess/Source/KDevelopSourceCodeAccess`
- headers: 2; symbols: 25
- symbol kinds: class=2, function=1, member=2, prototype=20
- PrivateDependencyModuleNames: Core, DesktopPlatform, HotReload, SourceCodeAccess

### `Plugins/Developer/KDevelopSourceCodeAccess/Source/KDevelopSourceCodeAccess/Private/KDevelopSourceCodeAccessModule.h` (Private)


#### class `FKDevelopSourceCodeAccessModule`  
`class FKDevelopSourceCodeAccessModule : public IModuleInterface`  
_L8-19_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public prototype_ `FKDevelopSourceCodeAccessor& GetAccessor();`
- L18 _private member_ `FKDevelopSourceCodeAccessor KDevelopSourceCodeAccessor;`

### `Plugins/Developer/KDevelopSourceCodeAccess/Source/KDevelopSourceCodeAccess/Private/KDevelopSourceCodeAccessor.h` (Private)


#### class `FKDevelopSourceCodeAccessor`  
`class FKDevelopSourceCodeAccessor : public ISourceCodeAccessor`  
_L6-43_
- inherits: `ISourceCodeAccessor`
- L10 _public prototype_ `void Startup();` — Initialise internal systems, register delegates etc.
- L13 _public prototype_ `void Shutdown();` — Shut down internal systems, unregister delegates etc.
- L16 _public function_ `virtual void RefreshAvailability() override` — ISourceCodeAccessor implementation
- L17 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L18 _public prototype_ `virtual FName GetFName() const override;`
- L19 _public prototype_ `virtual FText GetNameText() const override;`
- L20 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L21 _public prototype_ `virtual bool OpenSolution() override;`
- L22 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L23 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L24 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L25 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L26 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L27 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L28 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L33 _private member_ `mutable FString CachedSolutionPath;` — String storing the solution path obtained from the module manager to avoid having to use it on a thread
- L36 _private prototype_ `bool CanRunKDevelop(FString& OutPath) const;` — Tests if KDevelop is present and returns path to it
- L39 _private prototype_ `bool IsIDERunning();` — Check if KDevelop is already running
- L42 _private prototype_ `FString GetSolutionPath() const;` — Gets solution path
