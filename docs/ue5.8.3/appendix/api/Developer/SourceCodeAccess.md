# Developer / SourceCodeAccess

- module root: `Source/Developer/SourceCodeAccess`
- headers: 5; symbols: 67
- symbol kinds: class=5, delegate=3, function=3, member=6, prototype=50
- PrivateDependencyModuleNames: CoreUObject, Slate, SlateCore
- PublicDependencyModuleNames: Core, Settings

### `Source/Developer/SourceCodeAccess/Private/DefaultSourceCodeAccessor.h` (Private)


#### class `FDefaultSourceCodeAccessor`  
`class FDefaultSourceCodeAccessor : public ISourceCodeAccessor`  
_L8-25_
- inherits: `ISourceCodeAccessor`
- L12 _public function_ `virtual void RefreshAvailability() override` — ISourceCodeAccessor implementation
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

### `Source/Developer/SourceCodeAccess/Private/SourceCodeAccessModule.h` (Private)


#### class `FSourceCodeAccessModule`  
`class FSourceCodeAccessModule : public ISourceCodeAccessModule`  
_L12-66_
- inherits: `ISourceCodeAccessModule`
- desc: Implementation of ISourceCodeAccessModule.
- L18 _public prototype_ `FSourceCodeAccessModule();` — Default constructor.
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L32 _public prototype_ `virtual bool CanCompileSourceCode() const override;`
- L33 _public prototype_ `virtual ISourceCodeAccessor& GetAccessor() const override;`
- L34 _public prototype_ `virtual void SetAccessor(const FName& InName) override;`
- L35 _public prototype_ `virtual FLaunchingCodeAccessor& OnLaunchingCodeAccessor() override;`
- L36 _public prototype_ `virtual FDoneLaunchingCodeAccessor& OnDoneLaunchingCodeAccessor() override;`
- L37 _public prototype_ `virtual FOpenFileFailed& OnOpenFileFailed() override;`
- L42 _private prototype_ `void HandleModularFeatureRegistered(const FName& Type, IModularFeature* ModularFeature);` — Handle when one of the modular features we are interested in is registered
- L45 _private prototype_ `void HandleModularFeatureUnregistered(const FName& Type, IModularFeature* ModularFeature);` — Handle when one of the modular features we are interested in is unregistered
- L48 _private prototype_ `bool IsSourceCodeAccessorAvailable(FName Name) const;` — Checks if a source code accessor with the given name is available
- L53 _private member_ `FLaunchingCodeAccessor LaunchingCodeAccessorDelegate;` — Event delegate fired when launching code accessor.
- L56 _private member_ `FDoneLaunchingCodeAccessor DoneLaunchingCodeAccessorDelegate;` — Event delegate fired when done launching code accessor.
- L59 _private member_ `FOpenFileFailed OpenFileFailedDelegate;` — Event delegate fired when opening a file has failed.
- L62 _private member_ `FDefaultSourceCodeAccessor DefaultSourceCodeAccessor;` — The default accessor we will use if we have no IDE.
- L65 _private member_ `ISourceCodeAccessor* CurrentSourceCodeAccessor;` — The current accessor.

### `Source/Developer/SourceCodeAccess/Private/SourceCodeAccessSettings.h` (Private)


#### class `USourceCodeAccessSettings`  
`class USourceCodeAccessSettings : public UObject`  
_L11-18_
- reflection: `UCLASS(config=EditorSettings)`
- inherits: `UObject`
- L17 _private member_ `FString PreferredAccessor;` — `UPROPERTY(Config, EditAnywhere, Category="Source Code Editor", meta=(DisplayName="Source Code Editor", ConfigRestartRequired = true))` — The source code editor we prefer to use.

### `Source/Developer/SourceCodeAccess/Public/ISourceCodeAccessModule.h` (Public)


#### class `ISourceCodeAccessModule`  
`class ISourceCodeAccessModule : public IModuleInterface`  
_L28-63_
- inherits: `IModuleInterface`
- desc: Module used to access source code
- L35 _public prototype_ `virtual bool CanAccessSourceCode() const = 0;` — Check to see if source code can be accessed. @return true if source code can be accessed.
- L41 _public prototype_ `virtual bool CanCompileSourceCode() const = 0;` — Checks if a compiler is available @return true if source code can be compiled.
- L47 _public prototype_ `virtual ISourceCodeAccessor& GetAccessor() const = 0;` — Get the accessor to allow us to view source code @return the accessor.
- L53 _public prototype_ `virtual void SetAccessor(const FName& InName) = 0;` — Set the accessor we want to use to view source code @param	InName	The name of the accessor we want to use
- L56 _public prototype_ `virtual FLaunchingCodeAccessor& OnLaunchingCodeAccessor() = 0;` — Gets the Event that is broad casted when attempting to launch visual studio
- L59 _public prototype_ `virtual FDoneLaunchingCodeAccessor& OnDoneLaunchingCodeAccessor() = 0;` — Gets the Event that is broadcasted when an attempted launch of this code accessor was successful or failed
- L62 _public prototype_ `virtual FOpenFileFailed& OnOpenFileFailed() = 0;` — Gets the Event that is broadcast when an attempt to load a file through Visual Studio failed

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE( FLaunchingCodeAccessor );` — Event fired when launching code accessor
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE( FLaunchingCodeAccessor );` — Event fired when launching code accessor
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FDoneLaunchingCodeAccessor, const bool );` — Event fired when done launching code accessor @param	bSuccess	Whether the launch was successful or not
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FDoneLaunchingCodeAccessor, const bool );` — Event fired when done launching code accessor @param	bSuccess	Whether the launch was successful or not
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOpenFileFailed, const FString& );` — Event fired when opening a file has failed @param	InFilename	The filename that failed to open
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOpenFileFailed, const FString& );` — Event fired when opening a file has failed @param	InFilename	The filename that failed to open

### `Source/Developer/SourceCodeAccess/Public/ISourceCodeAccessor.h` (Public)


#### class `ISourceCodeAccessor`  
`class ISourceCodeAccessor : public IModularFeature`  
_L11-126_
- inherits: `IModularFeature`
- desc: Interface for viewing/editing source code
- L14 _public prototype_ `virtual ~ISourceCodeAccessor() = default;`
- L21 _public prototype_ `virtual void RefreshAvailability() = 0;` — Not necessary to call unless you know you're changing the state of any installed compilers. If that's the case, you should call this before checking the state the installed state of the compilers.
- L27 _public prototype_ `virtual bool CanAccessSourceCode() const = 0;` — Check if we can currently access source code @return true if source code can be accessed
- L33 _public prototype_ `virtual FName GetFName() const = 0;` — Get the name of this source code accessor - used as a unique identifier @return the name of this accessor
- L39 _public prototype_ `virtual FText GetNameText() const = 0;` — Get the name text for this source code accessor @return the name text of this accessor
- L45 _public prototype_ `virtual FText GetDescriptionText() const = 0;` — Get the description text for this source code accessor @return the description text of this accessor
- L51 _public prototype_ `virtual bool OpenSolution() = 0;` — Open the current code solution for editing @return true if successful
- L58 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) = 0;` — Open the code solution at a specific path for editing @param InSolutionPath	Path to project directory @return true if successful
- L64 _public prototype_ `virtual bool DoesSolutionExist() const = 0;` — Determine if the source code solution for the given accessor already exists @return true if solution files exist
- L73 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) = 0;` — Opens a file in the correct running instance of this code accessor at a line and optionally to a column. @param	FullPath		Full path to the file to open @param	LineNumber		Line number to open the file at @param	ColumnNumber	Column number to open the file at @return true if successful
- L79 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) = 0;` — Opens a group of source files. @param	AbsoluteSourcePaths		Array of paths to files to open
- L87 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) = 0;` — Add a group of source files to the current solution/project/workspace @param	AbsoluteSourcePaths		Array of paths to files to open @param	AvailableModules		Array of known module locations (.Build.cs files) - you can get this from calling FSourceCodeNavigation::GetSourceFileDatabase().GetModuleNames() if in the editor @return true if the files could be added, false otherwise
- L94 _public prototype_ `virtual bool SaveAllOpenDocuments() const = 0;` — Saves all open code documents if they need to be saved. Will block if there is any read-only files open that need to be saved. @return true if successful
- L100 _public prototype_ `virtual void Tick(const float DeltaTime) = 0;` — Tick this source code accessor @param DeltaTime Delta time (in seconds) since the last call to Tick
- L106 _public function_ `virtual FName GetOpenIconName() const` — Get the icon that represents opening this source code editor @return the default source code editor icon
- L115 _public function_ `virtual FName GetRefreshIconName() const` — Get the icon that represents refreshing this source code editor @return the default source code editor icon
- L125 _public prototype_ `virtual FName GetStyleSet() const;` — Get the style set where custom icons for the editors are defined. By default uses FAppStyle::GetAppStyleSetName() == "CoreStyle" @return the default style set for icons
