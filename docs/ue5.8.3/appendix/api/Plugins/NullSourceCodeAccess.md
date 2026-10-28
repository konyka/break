# Plugins / NullSourceCodeAccess

- module root: `Plugins/Developer/NullSourceCodeAccess/Source/NullSourceCodeAccess`
- headers: 2; symbols: 19
- symbol kinds: class=2, function=1, member=1, prototype=15
- PrivateDependencyModuleNames: Core, DesktopPlatform, SourceCodeAccess

### `Plugins/Developer/NullSourceCodeAccess/Source/NullSourceCodeAccess/Private/NullSourceCodeAccessModule.h` (Private)


#### class `FNullSourceCodeAccessModule`  
`class FNullSourceCodeAccessModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L14 _public prototype_ `FNullSourceCodeAccessor& GetAccessor();`
- L17 _private member_ `FNullSourceCodeAccessor NullSourceCodeAccessor;`

### `Plugins/Developer/NullSourceCodeAccess/Source/NullSourceCodeAccess/Private/NullSourceCodeAccessor.h` (Private)


#### class `FNullSourceCodeAccessor`  
`class FNullSourceCodeAccessor : public ISourceCodeAccessor`  
_L7-24_
- inherits: `ISourceCodeAccessor`
- L11 _public function_ `virtual void RefreshAvailability() override` — ISourceCodeAccessor implementation
- L12 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L13 _public prototype_ `virtual FName GetFName() const override;`
- L14 _public prototype_ `virtual FText GetNameText() const override;`
- L15 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L16 _public prototype_ `virtual bool OpenSolution() override;`
- L17 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L18 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L19 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L20 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L21 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L22 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L23 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
