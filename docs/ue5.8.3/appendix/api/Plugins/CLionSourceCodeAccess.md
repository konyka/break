# Plugins / CLionSourceCodeAccess

- module root: `Plugins/Developer/CLionSourceCodeAccess/Source/CLionSourceCodeAccess`
- headers: 2; symbols: 23
- symbol kinds: class=2, function=1, member=3, prototype=17
- PrivateDependencyModuleNames: Core, DesktopPlatform, HotReload, Json, SourceCodeAccess

### `Plugins/Developer/CLionSourceCodeAccess/Source/CLionSourceCodeAccess/Private/CLionSourceCodeAccessModule.h` (Private)


#### class `FCLionSourceCodeAccessModule`  
`class FCLionSourceCodeAccessModule : public IModuleInterface`  
_L8-23_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L18 _public prototype_ `FCLionSourceCodeAccessor& GetAccessor();`
- L21 _private member_ `FCLionSourceCodeAccessor CLionSourceCodeAccessor;`

### `Plugins/Developer/CLionSourceCodeAccess/Source/CLionSourceCodeAccess/Private/CLionSourceCodeAccessor.h` (Private)


#### class `FCLionSourceCodeAccessor`  
`class FCLionSourceCodeAccessor : public ISourceCodeAccessor`  
_L7-60_
- inherits: `ISourceCodeAccessor`
- L11 _public prototype_ `virtual void RefreshAvailability() override;` — ISourceCodeAccessor implementation
- L13 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L15 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L17 _public prototype_ `virtual FName GetFName() const override;`
- L19 _public prototype_ `virtual FText GetNameText() const override;`
- L21 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L23 _public prototype_ `virtual bool OpenSolution() override;`
- L25 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L27 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L29 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L31 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L33 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L39 _public function_ `virtual void Tick(const float DeltaTime) override` — Frame Tick (Not Used) @param DeltaTime of frame
- L49 _private member_ `bool bHasCLionInstalled = false;` — Is CLion installed on this system?
- L53 _private member_ `FString ExecutablePath;` — The path to the CLion executable.
- L59 _private prototype_ `FString FindExecutablePath();` — Search for CLion installation @return Executable path
