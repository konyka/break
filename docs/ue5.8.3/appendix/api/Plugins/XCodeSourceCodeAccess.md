# Plugins / XCodeSourceCodeAccess

- module root: `Plugins/Developer/XCodeSourceCodeAccess/Source/XCodeSourceCodeAccess`
- headers: 2; symbols: 22
- symbol kinds: class=2, function=1, member=2, prototype=17
- PrivateDependencyModuleNames: Core, DesktopPlatform, SourceCodeAccess

### `Plugins/Developer/XCodeSourceCodeAccess/Source/XCodeSourceCodeAccess/Private/XCodeSourceCodeAccessModule.h` (Private)


#### class `FXCodeSourceCodeAccessModule`  
`class FXCodeSourceCodeAccessModule : public IModuleInterface`  
_L9-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FXCodeSourceCodeAccessor XCodeSourceCodeAccessor;`

### `Plugins/Developer/XCodeSourceCodeAccess/Source/XCodeSourceCodeAccess/Private/XCodeSourceCodeAccessor.h` (Private)


#### class `FXCodeSourceCodeAccessor`  
`class FXCodeSourceCodeAccessor : public ISourceCodeAccessor`  
_L7-36_
- inherits: `ISourceCodeAccessor`
- L12 _public prototype_ `void Startup();` — Initialise internal systems, register delegates etc.
- L15 _public prototype_ `void Shutdown();` — Shut down internal systems, unregister delegates etc.
- L18 _public function_ `virtual void RefreshAvailability() override` — ISourceCodeAccessor implementation
- L19 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L20 _public prototype_ `virtual FName GetFName() const override;`
- L21 _public prototype_ `virtual FText GetNameText() const override;`
- L22 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L23 _public prototype_ `virtual bool OpenSolution() override;`
- L24 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L25 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L26 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L27 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L28 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L29 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L30 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L34 _private prototype_ `FString GetSolutionPath() const;`
- L35 _private member_ `mutable FString CachedSolutionPath;`
