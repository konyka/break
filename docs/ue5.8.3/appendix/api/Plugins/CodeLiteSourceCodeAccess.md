# Plugins / CodeLiteSourceCodeAccess

- module root: `Plugins/Developer/CodeLiteSourceCodeAccess/Source/CodeLiteSourceCodeAccess`
- headers: 2; symbols: 29
- symbol kinds: class=2, function=1, member=5, prototype=20, struct=1
- PrivateDependencyModuleNames: Core, DesktopPlatform, HotReload, Projects, SourceCodeAccess

### `Plugins/Developer/CodeLiteSourceCodeAccess/Source/CodeLiteSourceCodeAccess/Private/CodeLiteSourceCodeAccessModule.h` (Private)


#### class `FCodeLiteSourceCodeAccessModule`  
`class FCodeLiteSourceCodeAccessModule : public IModuleInterface`  
_L8-27_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L20 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L22 _public prototype_ `FCodeLiteSourceCodeAccessor& GetAccessor();`
- L26 _private member_ `FCodeLiteSourceCodeAccessor CodeLiteSourceCodeAccessor;`

### `Plugins/Developer/CodeLiteSourceCodeAccess/Source/CodeLiteSourceCodeAccess/Private/CodeLiteSourceCodeAccessor.h` (Private)


#### class `FCodeLiteSourceCodeAccessor`  
`class FCodeLiteSourceCodeAccessor : public ISourceCodeAccessor`  
_L7-112_
- inherits: `ISourceCodeAccessor`
- L14 _public prototype_ `virtual void RefreshAvailability() override;` — Call if we've likely modified the availability of the source code accessor.
- L19 _public prototype_ `virtual bool CanAccessSourceCode() const override;` — Can we access source code.
- L24 _public prototype_ `virtual FName GetFName() const override;` — Get the name of this accessor. Will be used as a unique identifier.
- L29 _public prototype_ `virtual FText GetNameText() const override;` — Get the name of this accessor.
- L34 _public prototype_ `virtual FText GetDescriptionText() const override;` — Get the descriptor of this accessor.
- L39 _public prototype_ `virtual bool OpenSolution() override;` — Open the CodeLite Workspace for editing.
- L44 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;` — Open the CodeLite Workspace for editing.
- L49 _public prototype_ `virtual bool DoesSolutionExist() const override;` — Open the CodeLite Workspace for editing.
- L54 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;` — Open a file at a specific line and optional column.
- L59 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;` — Open a group of files.
- L64 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;` — Add a group of files.
- L69 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;` — Save all open files.
- L75 _public prototype_ `virtual void Tick(const float DeltaTime) override;` — Tick this source code accessor @param DeltaTime Delta time (in seconds) since the last call to Tick
- L80 _public prototype_ `void Startup();` — Initialize the accessor.
- L85 _public prototype_ `void Shutdown();` — Deinitialize the accessor.
- L100 _private member_ `FLocation Location;` — Location instance
- L103 _private member_ `mutable FString CachedSolutionPath;` — String storing the solution path obtained from the module manager to avoid having to use it on a thread
- L106 _private member_ `mutable FCriticalSection CachedSolutionPathCriticalSection;` — Critical section for updating SolutionPath
- L109 _private prototype_ `FString GetSolutionPath() const;` — Gets solution path
- L111 _private prototype_ `bool Launch(const TArray<FString>& InArgs);`

#### struct `FCodeLiteSourceCodeAccessor::FLocation`  
`struct FLocation`  
_L89-97_
- L91 _public function_ `bool IsValid() const`
- L96 _public member_ `FString URL;`
