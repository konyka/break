# Plugins / N10XSourceCodeAccess

- module root: `Plugins/Developer/N10XSourceCodeAccess/Source/N10XSourceCodeAccess`
- headers: 2; symbols: 28
- symbol kinds: class=2, function=1, member=4, prototype=21
- PrivateDependencyModuleNames: Core, DesktopPlatform, HotReload, Projects, SourceCodeAccess

### `Plugins/Developer/N10XSourceCodeAccess/Source/N10XSourceCodeAccess/Private/N10XSourceCodeAccessModule.h` (Private)


#### class `F10XSourceCodeAccessModule`  
`class F10XSourceCodeAccessModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L13 _public prototype_ `F10XSourceCodeAccessModule();`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `F10XSourceCodeAccessor& GetAccessor();`
- L23 _private member_ `TSharedRef<F10XSourceCodeAccessor> SourceCodeAccessor;`

### `Plugins/Developer/N10XSourceCodeAccess/Source/N10XSourceCodeAccess/Private/N10XSourceCodeAccessor.h` (Private)


#### class `F10XSourceCodeAccessor`  
`class F10XSourceCodeAccessor : public ISourceCodeAccessor`  
_L6-40_
- inherits: `ISourceCodeAccessor`
- L9 _public function_ `F10XSourceCodeAccessor()`
- L13 _public prototype_ `void Startup();`
- L14 _public prototype_ `void Shutdown();`
- L17 _public prototype_ `virtual void RefreshAvailability() final;` — ISourceCodeAccessor implementation
- L18 _public prototype_ `virtual bool CanAccessSourceCode() const final;`
- L19 _public prototype_ `virtual FName GetFName() const final;`
- L20 _public prototype_ `virtual FText GetNameText() const final;`
- L21 _public prototype_ `virtual FText GetDescriptionText() const final;`
- L22 _public prototype_ `virtual bool OpenSolution() final;`
- L23 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) final;`
- L24 _public prototype_ `virtual bool DoesSolutionExist() const final;`
- L25 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) final;`
- L26 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) final;`
- L27 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) final;`
- L28 _public prototype_ `virtual bool SaveAllOpenDocuments() const final;`
- L29 _public prototype_ `virtual void Tick(const float DeltaTime) final;`
- L32 _private member_ `FString ApplicationFilePath;`
- L34 _private member_ `mutable FString CachedSolutionPath;`
- L35 _private member_ `mutable FCriticalSection CachedSolutionPathCriticalSection;`
- L37 _private prototype_ `const FString& GetSolutionPath() const;`
- L39 _private prototype_ `bool Launch(const TArray<FString>& InArgs);`
