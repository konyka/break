# Plugins / StormSyncCore

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncCore`
- headers: 9; symbols: 158
- symbol kinds: class=4, delegate=22, enum=3, enumerator=12, function=9, member=53, prototype=45, struct=7, typedef=3
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, DeveloperSettings, Engine, Projects, Serialization
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Internal/StormSyncMemoryReader.h` (Internal)


#### class `FStormSyncMemoryReader`  
`class FStormSyncMemoryReader : public FMemoryArchive`  
_L12-54_
- inherits: `FMemoryArchive`
- desc: Archive for reading arbitrary data from a shared storm sync buffer.
- L16 _public function_ `virtual FString GetArchiveName() const override`
- L21 _public function_ `virtual int64 TotalSize() override`
- L26 _public function_ `virtual void Serialize(void* OutData, int64 InNum) override`
- L44 _public function_ `explicit FStormSyncMemoryReader(const FStormSyncBufferPtr& InBuffer) : Buffer(InBuffer)`
- L53 _private member_ `FStormSyncBufferPtr Buffer;` — Keep a shared reference on the buffer.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Private/StormSyncCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncCore, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncCore, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCommandLineUtils.h` (Public)


#### class `FStormSyncCommandLineUtils`  
`class FStormSyncCommandLineUtils`  
_L11-23_
- desc: Provides command line helpers to help in dealing with command parameters
- L22 _public prototype_ `static void Parse(const TCHAR* CmdLine, TArray<FName>& Arguments);` — Parses a string into tokens, separating switches (beginning with - or /) from other parameters @param	CmdLine		the string to parse @param	Arguments	[out] filled with all the non-option arguments found in the string

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCommonTypes.h` (Public)


#### enum `EStormSyncEngineType`  
`enum class EStormSyncEngineType : uint8`  
_L17-25_
- reflection: `UENUM()`
- desc: Engine type values for a storm sync connected device
- L19 _public enumerator_ `Server`
- L20 _public enumerator_ `Commandlet`
- L21 _public enumerator_ `Editor`
- L22 _public enumerator_ `Game`
- L23 _public enumerator_ `Other`
- L24 _public enumerator_ `Unknown`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FStormSyncBuffer = TArray64<uint8>;` — Common alias to a ThreadSafe SharedPtr to hold a Buffer (array of uint8)
- L12 _typedef_ `using FStormSyncBufferPtr = TSharedPtr<FStormSyncBuffer, ESPMode::ThreadSafe>;`
- L13 _typedef_ `using FStormSyncArchivePtr = TSharedPtr<FArchive, ESPMode::ThreadSafe>;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCoreDelegates.h` (Public)


#### enum `EStormSyncConnectedDeviceState`  
`enum class EStormSyncConnectedDeviceState : uint8`  
_L11-21_
- reflection: `UENUM()`
- desc: Connection states for storm sync discovered devices over the network
- L14 _public enumerator_ `State_Active` — Connected and known from this editor instance
- L17 _public enumerator_ `State_Unresponsive` — Became unresponsive, haven't received any heartbeats for a certain amount of time (as configured in project settings)
- L20 _public enumerator_ `State_Disconnected` — Initial state before service discovery has a chance to update state

#### struct `FStormSyncConnectedDevice`  
`struct FStormSyncConnectedDevice`  
_L24-62_
- desc: UI related data holder for storm sync connected devices
- L27 _public member_ `EStormSyncConnectedDeviceState State = EStormSyncConnectedDeviceState::State_Disconnected;` — Holds the state of the connection
- L34 _public member_ `bool bIsServerRunning = false;` — Holds the state of the remote server for the connection. Whether remote server endpoint is currently running and able to receive incoming connections
- L37 _public member_ `FString MessageAddressId;` — Holds the message bus address identifier for Service Discovery endpoint
- L40 _public member_ `FString StormSyncServerAddressId;` — Holds the message bus address identifier for Storm Sync Server endpoint
- L43 _public member_ `FString StormSyncClientAddressId;` — Holds the message bus address identifier for Storm Sync Client endpoint
- L46 _public member_ `FString HostName;` — The hostname this message was generated from
- L49 _public member_ `FString ProjectName;` — The unreal project name this message was generated from
- L52 _public member_ `FString ProjectDir;` — The unreal project directory this message was generated from (last portion of the path)
- L55 _public member_ `FString InstanceId;` — Holds instance identifier
- L58 _public member_ `EStormSyncEngineType InstanceType = EStormSyncEngineType::Unknown;` — Holds the type of the engine instance.
- L61 _public prototype_ `FStormSyncConnectedDevice() = default;` — Default constructor

#### struct `FStormSyncCoreDelegates`  
`struct FStormSyncCoreDelegates`  
_L69-242_
- desc: FStormSyncCoreDelegates Delegates used by the editor.
- L77 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestImportBuffer, const FStormSyncPackageDescriptor&, const FStormSyncArchivePtr&);` — Delegate type for when an incoming pak extraction process starts @param PackageDescriptor Metadata information about incoming buffer (name, description, etc.) @param Archive The archive for the incoming pak buffer
- L84 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestImportFile, const FString&);` — Delegate type for when one an incoming pak extraction process starts @param Filename The absolute filename path for the imported file
- L91 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFileImported, const FString& );` — Delegate type for when imported spak has completed extraction. @param InFilename The absolute filename path for the imported file
- L99 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPakAssetExtracted, const FName& , const FString& );` — Delegate type for when one asset is extracted from an incoming pak @param PackageName Original Package Name @param DestFilepath The fully qualified destination filepath where the file should be extracted to
- L108 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreStartSendingBuffer, const FString&, const FString&, int32);` — Delegate type for a client socket about to open a stream for sending a buffer @param RemoteAddress FString remote address of the server we are about to send to @param RemoteHostName FString remote hostname (or friendly name) of the server we are sending to @param PackageNums The total number of files (or package names) to include in the buffer
- L116 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartSendingBuffer, const FString&, int32);` — Delegate type for a client socket opening a tcp stream and sending a buffer to a remote server @param RemoteAddress FString remote address of the server we are sending to @param BufferSize The total number of bytes the server should expect, representing the buffer size
- L124 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReceivingBytes, const FString&, int32);` — Delegate type for a client socket receiving response from server, indicating how many bytes it received so far @param RemoteAddress FString remote address of the server we get a response from @param BytesCount The number of bytes received so far by the remote server
- L131 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTransferComplete, const FString&);` — Delegate type for a client socket receiving "transfer complete" response from server, indicating the tcp transfer is done. @param RemoteAddress FString remote address of the server we get a response from
- L141 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryConnection, const FString&, const FStormSyncConnectedDevice&);` — Delegate type for a new connection over the network on storm sync message bus. Service Discovery related. @param FString Message Bus Address UID. @param FStormSyncConnectedDevice Data Holding struct with info about connected device.
- L151 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryStateChange, const FString&, EStormSyncConnectedDeviceState);` — Delegate type for when a connection on storm sync network state is changing (might become unresponsive). Service Discovery related. @param FString Message Bus Address UID. @param EStormSyncConnectedDeviceState Enum state indicating if connection is active or unresponsive
- L157 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnServiceDiscoveryReceivedWakeup);` — Wakeup event sent through the discovery service to re-active the other services.
- L167 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryServerStatusChange, const FString&, bool);` — Delegate type for when server status for a connection on storm sync network has changed (either running or stopped). Service Discovery related. @param FString Message Bus Address UID. @param boolean Whether the state for remote server endpoint is running or stopped (false)
- L173 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStormSyncServerStopped) DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceDiscoveryDisconnection, const FString&);` — Broadcasted when server module stops the endpoint
- L189 _public member_ `static FOnRequestImportBuffer OnRequestImportBuffer;` — Called when receiving a buffer over network and used to queue up an import task
- L192 _public member_ `static FOnRequestImportFile OnRequestImportFile;` — Called when importing an .spak file via the Archive factory (import via content browser) and used to queue up an import task
- L194 _public member_ `static FOnFileImported OnFileImported;`
- L197 _public member_ `static FOnPakAssetExtracted OnPakAssetExtracted;` — Called when a file is extracted from an incoming storm sync pak
- L203 _public member_ `static FOnPreStartSendingBuffer OnPreStartSendingBuffer;` — Called when a tcp socket client is about to open a tcp stream and starts sending buffer to a remote server, before the buffer is created and the connection is established.
- L206 _public member_ `static FOnStartSendingBuffer OnStartSendingBuffer;` — Called when a tcp socket client opens a tcp stream and starts sending a buffer to a remote server
- L209 _public member_ `static FOnReceivingBytes OnReceivingBytes;` — Called when a tcp socket client is receiving a response from a server we are sending to (including the size it receives so far)
- L212 _public member_ `static FOnTransferComplete OnTransferComplete;` — Called when a tcp socket client is receiving a response from a server we are sending to (including the size it receives so far)
- L215 _public member_ `static FOnServiceDiscoveryConnection OnServiceDiscoveryConnection;` — Called when service discovery manager detects a new connection on Storm Sync network
- L221 _public member_ `static FOnServiceDiscoveryStateChange OnServiceDiscoveryStateChange;` — Called when service discovery manager detects a state change for a connected device on Storm Sync network (might become unresponsive)
- L226 _public member_ `static FOnServiceDiscoveryReceivedWakeup OnServiceDiscoveryReceivedWakeup;` — Called when the discovery service receives a wakeup request.
- L229 _public member_ `static FOnServiceDiscoveryServerStatusChange OnServiceDiscoveryServerStatusChange;` — Called when service discovery manager detects a state change for remote server endpoint on a connected device
- L235 _public member_ `static FOnServiceDiscoveryDisconnection OnServiceDiscoveryDisconnection;` — Called when service discovery manager detects a connection dropped on Storm Sync network (happens after a certain amount of inactivity configured via StormSyncTransportSettings)
- L238 _public member_ `static FOnStormSyncServerStarted OnStormSyncServerStarted;` — Server started delegate
- L241 _public member_ `static FOnStormSyncServerStopped OnStormSyncServerStopped;` — Server stopped delegate

#### Free symbols / members of external scopes

- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestImportBuffer, const FStormSyncPackageDescriptor&, const FStormSyncArchivePtr&);` — Delegate type for when an incoming pak extraction process starts @param PackageDescriptor Metadata information about incoming buffer (name, description, etc.) @param Archive The archive for the incoming pak buffer
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestImportFile, const FString&);` — Delegate type for when one an incoming pak extraction process starts @param Filename The absolute filename path for the imported file
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFileImported, const FString& );` — Delegate type for when imported spak has completed extraction. @param InFilename The absolute filename path for the imported file
- L99 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPakAssetExtracted, const FName& , const FString& );` — Delegate type for when one asset is extracted from an incoming pak @param PackageName Original Package Name @param DestFilepath The fully qualified destination filepath where the file should be extracted to
- L108 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreStartSendingBuffer, const FString&, const FString&, int32);` — Delegate type for a client socket about to open a stream for sending a buffer @param RemoteAddress FString remote address of the server we are about to send to @param RemoteHostName FString remote hostname (or friendly name) of the server we are sending to @param PackageNums The total number of files (or package names) to include in the buffer
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartSendingBuffer, const FString&, int32);` — Delegate type for a client socket opening a tcp stream and sending a buffer to a remote server @param RemoteAddress FString remote address of the server we are sending to @param BufferSize The total number of bytes the server should expect, representing the buffer size
- L124 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReceivingBytes, const FString&, int32);` — Delegate type for a client socket receiving response from server, indicating how many bytes it received so far @param RemoteAddress FString remote address of the server we get a response from @param BytesCount The number of bytes received so far by the remote server
- L131 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTransferComplete, const FString&);` — Delegate type for a client socket receiving "transfer complete" response from server, indicating the tcp transfer is done. @param RemoteAddress FString remote address of the server we get a response from
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryConnection, const FString&, const FStormSyncConnectedDevice&);` — Delegate type for a new connection over the network on storm sync message bus. Service Discovery related. @param FString Message Bus Address UID. @param FStormSyncConnectedDevice Data Holding struct with info about connected device.
- L151 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryStateChange, const FString&, EStormSyncConnectedDeviceState);` — Delegate type for when a connection on storm sync network state is changing (might become unresponsive). Service Discovery related. @param FString Message Bus Address UID. @param EStormSyncConnectedDeviceState Enum state indicating if connection is active or unresponsive
- L157 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnServiceDiscoveryReceivedWakeup);` — Wakeup event sent through the discovery service to re-active the other services.
- L167 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnServiceDiscoveryServerStatusChange, const FString&, bool);` — Delegate type for when server status for a connection on storm sync network has changed (either running or stopped). Service Discovery related. @param FString Message Bus Address UID. @param boolean Whether the state for remote server endpoint is running or stopped (false)
- L170 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStormSyncServerStarted) DECLARE_MULTICAST_DELEGATE(FOnStormSyncServerStopped) DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceDiscoveryDisconnection, const FString&);` — Broadcasted when server module starts the endpoint
- L173 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStormSyncServerStopped) DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceDiscoveryDisconnection, const FString&);` — Broadcasted when server module stops the endpoint
- L186 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceDiscoveryDisconnection, const FString&);` — Delegate type for a disconnection on storm sync message bus. Happens after a certain amount of inactivity configured via StormSyncTransportSettings. Service Discovery related. @param FString Message Bus Address UID. @param FStormSyncConnectedDevice Data Holding struct with info about connected device.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCoreSettings.h` (Public)


#### class `UStormSyncCoreSettings`  
`class UStormSyncCoreSettings : public UDeveloperSettings`  
_L16-92_
- reflection: `UCLASS(MinimalAPI, Config=Game, DefaultConfig, DisplayName="Core Settings")`
- inherits: `UDeveloperSettings`
- desc: Settings for the StormSyncCore plugin modules. Handle configuration for buffer creation / extraction.
- L21 _public prototype_ `UStormSyncCoreSettings();`
- L30 _public member_ `bool bExportOnlyGameContent = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings | Export")` — Whether StormSync should consider packages only within the `/Game` project content when performing an export or sending over the network. Can be used together with IgnoredPackages list below.
- L39 _public member_ `bool bFilterInvalidReferences = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings | Export", DisplayName = "Filter Out Invalid References")` — Whether to always ignore invalid references (eg. not existing on disk) during pak creation (when exporting or sending over network) If set to false, the export process will be stricter and prevent the operation, but you'll get a notification error about each invalid references.
- L52 _public member_ `TSet<FName> IgnoredPackages;` — `UPROPERTY(config, EditAnywhere, Category = "Settings | Export")` — Set of package names to ignore in pak file creation. Any package dependencies is filtered out using this list. This is a StartsWith search pattern, meaning any value here should be the beginning of dependency package names we'd like to ignore (eg, /SomePlugin, /AnotherPlugin, /Game/Folder, ...) Can be used together with bExportOnlyGameContent set to true, in which case you can filter out specific /Game/... folders and paths (other root paths such as /SomePlugin would have no effect)
- L74 _public member_ `FString ExportDefaultNameFormatString;` — `UPROPERTY(config, EditAnywhere, Category = "Settings | Export")` — A DateTime format string to customize the default name generated during a package export to local file (.spak). If the format string is set empty, no date time information will be appended to the default export name. Uses a non-standard format syntax (see below) %a - am or pm %A - AM or PM %d - Day, 01-31 %D - Day of the Year, 001-366 %m - Month, 01-12 %y - Year, YY %Y - Year, YYYY %h - 12h Hour, 01-12 %H - 24h Hour, 00-23 %M - Minute, 00-59 %S - Second, 00-60 %s - Millisecond, 000-999
- L80 _public member_ `TSet<FName> IgnoredPackagesInternal;` — Not exposed to end user via Project Settings UI, acts as a fail-safe additional ignore list for Packages like `/Engine` and `/Script`, or any other Packages we want to make sure to ignore regardless of user settings.
- L91 _public member_ `bool bEnableHotReloadPackages = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings | Import")` — Enables Hot Reloading of packages when modified by a sync operation. Hot reloading attempts to quickly reload the modified packages to avoid temporary invalid states to propagate in the system. If this is disabled, the assets will be deleted from memory and packages will be reloaded eventually by the Asset Registry's directory watcher.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCoreUtils.h` (Public)


#### struct `FStormSyncCoreExtractArgs`  
`struct FStormSyncCoreExtractArgs`  
_L16-72_
- desc: FStormSyncCoreExtractArgs Delegates used by the main extract method. Use it to register delegates when you want to be notified from external code.
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPakPreExtract, int32 );` — Delegate type for when one an incoming pak extraction process starts @param FileCount The int32 file count extracted from incoming buffer
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPakPostExtract, int32 );` — Delegate type for when one an incoming pak extraction is ended @param FileCount The int32 file count extracted from incoming buffer
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FStormSyncArchivePtr, FOnGetArchiveForExtract, const FStormSyncFileDependency& , const FString& );` — Delegate type called to obtain an archive to extract an asset. This is called before extraction starts. @param InFileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @return Archive (writer) into which the incoming file will be written.
- L44 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnArchiveExtracted, const FStormSyncFileDependency& , const FString& , const FStormSyncArchivePtr& );` — Delegate type called after a file buffer is extracted from an incoming pak into the provided archive. @param InFileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @param InArchive The archive that was returned by FOnGetArchiveForExtract is returned back.
- L53 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnFileExtract, const FStormSyncFileDependency& , FString , const FStormSyncBufferPtr& );` — Delegate type for when one asset is being extracted from an incoming pak @param FileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @param InBuffer The raw buffer (as an array of bytes shared ptr) for the individual files extracted from incoming pak buffer @remark if an archive was provided by OnGetArchiveForExtract delegate, this delegate will not be called.
- L56 _public member_ `FOnPakPreExtract OnPakPreExtract;` — Delegate type for when one an incoming pak extraction process starts
- L59 _public member_ `FOnPakPostExtract OnPakPostExtract;` — Delegate type for when one an incoming pak extraction is ended
- L62 _public member_ `FOnGetArchiveForExtract OnGetArchiveForExtract;` — Delegate type called to obtain an archive to extract an asset. This is called before extraction starts.
- L65 _public member_ `FOnArchiveExtracted OnArchiveExtracted;` — Delegate type called after a file buffer is extracted from the archive.
- L68 _public member_ `FOnFileExtract OnFileExtract;` — Delegate type triggered when a file asset is extracted from an incoming pak
- L71 _public prototype_ `FStormSyncCoreExtractArgs() = default;` — Default constructor

#### class `FStormSyncCoreUtils`  
`class FStormSyncCoreUtils`  
_L75-254_
- desc: This class exposes a set of static methods to manipulate Ava Pak files, creation and extraction.
- L79 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFileAdded, const FStormSyncFileDependency&) static bool GetAssetData(const FString& InPackageName, TArray<FAssetData>& OutAssets, TArray<FName>& OutDependencies);` — Delegate type triggered on pak buffer creation for each added file
- L108 _public prototype_ `static bool GetDependenciesForPackages(const TArray<FName>& InPackageNames, TArray<FName>& OutDependencies, FText& OutErrorText, const bool bInShouldValidatePackages = true);` — Gathers a list of PackageNames dependencies referenced by the supplied packages. Internally uses the AssetRegistry to recursively determine dependencies and returns a flatten list of all referenced assets (On disk references ONLY). @param InPackageNames List of packages to look for dependencies @param OutDependencies Sorted (alphabetically) list of all package dependencies @param OutErrorText Localized Text if the operation failed @param bInShouldValidatePackages Whether to disable strict verification on validity of package (eg. must exist locally) @return Returns true if we were able to generate a list of dependencies and false if the operation failed. Note that in case of failure, ErrorText is filled with further information.
- L124 _public prototype_ `static bool GetAvaFileDependenciesForPackages(const TArray<FName>& InPackageNames, TArray<FStormSyncFileDependency>& OutFileDependencies, FText& OutErrorText, const bool bInShouldValidatePackages = true);` — Similar to GetDependenciesForPackages internally searching for any recursive dependencies. Gathers a list of PackageNames dependencies referenced by the supplied packages, creating a list of FStormSyncFileDependency with info such as asset path, file size, timestamp and file hash. @param InPackageNames List of packages to look for dependencies @param OutFileDependencies Sorted (alphabetically) list of all package dependencies @param OutErrorText Localized Text if the operation failed @param bInShouldValidatePackages Whether to disable strict verification on validity of package (eg. must exist locally) @return Returns true if we were able to generate a list of dependencies and false if the operation failed. Note that in case of failure, ErrorText is filled with further information.
- L134 _public prototype_ `static TArray<FStormSyncFileDependency> GetAvaFileDependenciesFromPackageNames(const TArray<FName>& InPackageNames, bool bInShouldIncludeInvalid = false);` — Creates a list of FStormSyncFileDependency (with info such as asset path, file size, timestamp and file hash) from the supplied list of package names. @param InPackageNames List of packages to look for dependencies @return Returns a list of FStormSyncFileDependency
- L146 _public prototype_ `static TFuture<TArray<FStormSyncFileDependency>> GetAvaFileDependenciesAsync(const TArray<FName>& InPackageNames, const bool bInShouldValidatePackages = true, EAsyncExecution InThreadType = EAsyncExecution::Thread);` — Async version of FStormSyncCoreUtils::GetAvaFileDependenciesFromPackageNames to return a list of File Dependencies (with info about file size, asset path, timestamp file hash, etc.) from the provided list of package names. @param InPackageNames The list of package names to convert into FStormSyncFileDependency @param bInShouldValidatePackages Whether to disable strict verification on validity of package (eg. must exist locally) @param InThreadType Optional Thread Type to use for the async execution (Default EAsyncExecution::Thread) @return A future containing the list of file dependencies.
- L153 _public prototype_ `static FStormSyncFileDependency CreateStormSyncFile(const FName& InPackageName);` — Creates a new FStormSyncFileDependency and initialize filesystem related information Note: Considering renaming FStormSyncFileDependency to FStormSyncFileInfo (to distinguish with file references / dependencies idea)
- L172 _public prototype_ `static bool CreatePakBufferWithDependencies(const TArray<FName>& InPackageNames, FArchive& OutPakArchive, FText& OutErrorText, const FOnFileAdded& InOnFileAdded = FOnFileAdded());` — Recursively get dependencies for provided list of Package Names and attempts to create an ava pak buffer using a memory archive. A list of FStormSyncFileDependency is also returned with `OutSuccessfullyPackedFiles` including info such as asset path, file size, timestamp and file hash. @param InPackageNames List of package name to include in the pak @param OutPakBuffer Raw buffer of the created in memory archive @param OutErrorText Localized Text if the operation failed @param InOnFileAdded Delegate triggered with FStormSyncFileDependency for each added file @see FStormSyncFileDependency @return Returns true if we were able to generate the pak buffer false if the operation failed. Note that in case of failure, ErrorText is filled with further information.
- L193 _public prototype_ `static bool CreatePakBuffer(const TArray<FName>& InPackageNames, FArchive& OutPakArchive, FText& OutErrorText, const FOnFileAdded& InOnFileAdded = FOnFileAdded());` — Attempts to create an ava pak buffer using a memory archive from the provided list of Package Names. A list of FStormSyncFileDependency is also returned with `OutSuccessfullyPackedFiles` including info such as asset path, file size, timestamp and file hash. It differs from CreatePakBufferWithDependencies by not looking for inner dependencies. If you need to recursively search for dependencies, use CreatePakBufferWithDependencies instead. @param InPackageNames List of package name to include in the pak @param OutPakArchive Destination archive @param OutErrorText Localized Text if the operation failed @param InOnFileAdded Delegate triggered with FStormSyncFileDependency for each added file @see FStormSyncFileDependency @return Returns true if we were able to generate the pak buffer false if the operation failed. Note that in case of failure, ErrorText is filled with further information.
- L207 _public prototype_ `static bool ExtractPakBuffer(FArchive& InPakArchive, const FStormSyncCoreExtractArgs& InExtractArgs, TArray<FText>& OutErrors);` — Main entry point for unpacking. Extracts an ava pak into the current Unreal project (Game content or Plugins content folder) Will extract package names from pak buffer, and create any .uasset files that does not exist yet on local project. @param InPakArchive Raw ava pak archive to extract into project @param InExtractArgs The arguments used to trigger delegates during extraction process @param OutErrors List of localized Text if the operation failed @return Returns true if we were able to fully import the package and false if the operation failed (even for partial imports). Note that in case of failure, Errors array of localized text is filled with further information.
- L216 _public prototype_ `static FString GetHumanReadableByteSize(uint64 InSize);` — Converts the provided bytes size into a human readable string. @param InSize Number of bytes to convert @return A string representing the provided size with B, KB, MB of GB suffix.
- L237 _public prototype_ `static TArray<FStormSyncFileModifierInfo> GetSyncFileModifiers(const TArray<FName>& InPackageNames, const TArray<FStormSyncFileDependency>& InRemoteDependencies);` — Figures out the files that needs to be synced based on local and remote list of dependencies. Returns a list of FStormSyncFileModifierInfo based on the provided list of file dependencies (most likely coming from remote and part of sync request / response message transaction) from which we extract package names and gather the local state via GetAvaFileDependenciesFromPackageNames(). A list of FStormSyncFileModifierInfo is then based on those two list of file dependencies: - If missing locally, a FStormSyncFileModifierInfo is added with Addition operation - If present but with mismatched FileSize, a FStormSyncFileModifierInfo is added with Overwrite operation - If present but with mismatched FileHash, a FStormSyncFileModifierInfo is added with Overwrite operation - If present but with exact same FileSize and FileHash, no FStormSyncFileModifierInfo is added @param InPackageNames List of top level package names (from which we gather references) to base the diffing on @param InRemoteDependencies List of FStormSyncFileDependency to base our diffing against @return List of FStormSyncFileModifierInfo indicating files that are either missing or dirty
- L247 _private prototype_ `static void RecursiveGetDependencies(const FName& InPackageName, TArray<FName>& OutAllDependencies);` — Gets the dependencies of the specified package recursively. Note: Closely follow RecursiveGetDependencies implementation of AssetTools, except we don't deal with External Actors here. Uses AssetRegistry to gather up all dependency for a given package name.
- L250 _private prototype_ `static bool IsValidDependency(const FString& InDependencyName);` — Filters out any dependency we don't want to consider for a pak
- L253 _private prototype_ `static bool ValidateAssets(const TArray<FName>& InAssetsFilename, FText& OutErrorText);` — Validates all assets for existence on disk

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPakPreExtract, int32 );` — Delegate type for when one an incoming pak extraction process starts @param FileCount The int32 file count extracted from incoming buffer
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPakPostExtract, int32 );` — Delegate type for when one an incoming pak extraction is ended @param FileCount The int32 file count extracted from incoming buffer
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FStormSyncArchivePtr, FOnGetArchiveForExtract, const FStormSyncFileDependency& , const FString& );` — Delegate type called to obtain an archive to extract an asset. This is called before extraction starts. @param InFileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @return Archive (writer) into which the incoming file will be written.
- L44 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnArchiveExtracted, const FStormSyncFileDependency& , const FString& , const FStormSyncArchivePtr& );` — Delegate type called after a file buffer is extracted from an incoming pak into the provided archive. @param InFileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @param InArchive The archive that was returned by FOnGetArchiveForExtract is returned back.
- L53 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnFileExtract, const FStormSyncFileDependency& , FString , const FStormSyncBufferPtr& );` — Delegate type for when one asset is being extracted from an incoming pak @param FileDependency struct holding info such as Package Name, File size, timestamp and hash @param InDestFilename The fully qualified destination filepath where the file should be extracted to @param InBuffer The raw buffer (as an array of bytes shared ptr) for the individual files extracted from incoming pak buffer @remark if an archive was provided by OnGetArchiveForExtract delegate, this delegate will not be called.
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFileAdded, const FStormSyncFileDependency&) static bool GetAssetData(const FString& InPackageName, TArray<FAssetData>& OutAssets, TArray<FName>& OutDependencies);` — Delegate type triggered on pak buffer creation for each added file

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncImportTypes.h` (Public)


#### struct `FStormSyncImportFileInfo`  
`struct FStormSyncImportFileInfo`  
_L16-42_
- reflection: `USTRUCT()`
- desc: Data holder during an extraction process. Used to compute a list of files that needs extraction.
- L21 _public member_ `FStormSyncFileDependency FileDependency;` — Holds info such as PackageName, FileSize, Timestamp and hash
- L24 _public member_ `FString DestFilepath;` — The associated fully qualified path of the .uasset
- L27 _public member_ `FText ImportReason;` — UI-exposed reason of the import
- L30 _public member_ `FText ImportReasonTooltip;` — UI-exposed extended info for reason of the import
- L33 _public member_ `bool bNewAsset = false;` — True if the file was a new asset
- L35 _public prototype_ `FStormSyncImportFileInfo() = default;`
- L37 _public function_ `FStormSyncImportFileInfo(const FStormSyncFileDependency& InFileDependency, const FString& InDestFilepath) : FileDependency(InFileDependency) , DestFilepath(InDestFilepath)`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncPackageDescriptor.h` (Public)


#### struct `FStormSyncFileDependency`  
`struct FStormSyncFileDependency`  
_L15-73_
- reflection: `USTRUCT()`
- desc: FStormSyncFileDependency. Represents a file included in an ava package (and buffer). Has information about package name, and file system data such as file timestamp, size and hash used in the diffing process to figure out which files need to be synchronized for a given ava package.
- L20 _public prototype_ `FStormSyncFileDependency() = default;` — Default constructor.
- L23 _public function_ `explicit FStormSyncFileDependency(const FName& InPackageName) : PackageName(InPackageName)` — Default constructor initializing just the PackageName
- L29 _public function_ `FStormSyncFileDependency(const FName& InPackageName, const int32 InFileSize, const int64 InTimestamp, const FString& InFileHash) : PackageName(InPackageName) , FileSize(InFileSize) , Timestamp(InTimestamp) , FileHash(InFileHash)` — Default constructor with all members initialization
- L39 _public member_ `FName PackageName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — Original package name (eg. /Game/Path/File)
- L43 _public member_ `uint64 FileSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — File size on disk
- L47 _public member_ `int64 Timestamp = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — Unix timestamp the file had when the buffer was created
- L51 _public member_ `FString FileHash;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — The MD5 hash of the file on disk
- L67 _public prototype_ `static FString GetDestFilepath(const FName& InPackageName, FText& OutFailureReason);` — Return the fully qualified path for destination filename based on provided Package Name. The path on disk where this asset should be extracted to. If a package is coming from a plugin, it'll return the correct content destination folder for the plugin if it is installed in current project. It also handles arbitrary mount points and returns the absolute filename based on registered mount points. @param InPackageName Package name to base @param OutFailureReason Localized text filled with more information if operation failed. @return Destination filepath or empty string if we were not able to determine destination output (eg, Plugin package while plugin not installed or enabled in current project)
- L70 _public prototype_ `bool IsValid() const;` — Returns whether file info was properly initialized
- L72 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncPackageDescriptor`  
`struct FStormSyncPackageDescriptor`  
_L83-119_
- reflection: `USTRUCT()`
- desc: FStormSyncPackageDescriptor. A package descriptor is holding the metadata information for a given ava package. Has information about its name, description, version, author and most importantly a list of file dependencies (full list of files with data about their state, timestamp, size, hash, etc.)
- L88 _public function_ `FStormSyncPackageDescriptor() : Author(FPlatformProcess::UserName())` — Default constructor.
- L95 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — Friendly name of the package
- L104 _public member_ `FString Version = TEXT("1.0` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — Name of the version for this plugin. This is the front-facing part of the version number. It doesn't need to match the version number numerically, but should be updated when the version number is increased accordingly.
- L108 _public member_ `FString Description;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — Description of the package
- L112 _public member_ `FString Author;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — The company or individual who created this package
- L116 _public member_ `TArray<FStormSyncFileDependency> Dependencies;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync")` — The inner list of file assets dependencies for this ava package
- L118 _public prototype_ `FString ToString() const;`

#### enum `EStormSyncModifierOperation`  
`enum class EStormSyncModifierOperation : uint8`  
_L129-139_
- reflection: `UENUM()`
- desc: EStormSyncModifierOperation. Defines the ways that mods will modify packages @see FStormSyncFileModifierInfo
- L132 _public enumerator_ `Addition UMETA(DisplayName="Add")` — This is an addition, meaning receiver is missing the file
- L135 _public enumerator_ `Missing UMETA(DisplayName="Missing")` — This is a missing situation, meaning receiver has the file but sender has not
- L138 _public enumerator_ `Overwrite UMETA(DisplayName="Overwrite")` — This is an overwrite, meaning both sender and receiver have the file, but in a different state (mismatch filesize, hash, etc.)

#### struct `FStormSyncFileModifierInfo`  
`struct FStormSyncFileModifierInfo`  
_L148-170_
- reflection: `USTRUCT()`
- desc: FStormSyncFileModifierInfo. Effectively a sync request with an additional list of sync modifiers, representing the diffing results and files we want to synchronize.
- L154 _public member_ `EStormSyncModifierOperation ModifierOperation = EStormSyncModifierOperation::Addition;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The operation of this modifier: Addition, Missing, Overwrite, etc
- L158 _public member_ `FStormSyncFileDependency FileDependency;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The file dependency this modifier relates to
- L161 _public prototype_ `FStormSyncFileModifierInfo() = default;` — Default constructor.
- L163 _public function_ `FStormSyncFileModifierInfo(const EStormSyncModifierOperation InModifierOperation, const FStormSyncFileDependency& InFileDependency) : ModifierOperation(InModifierOperation) , FileDependency(InFileDependency)`
- L169 _public prototype_ `FString ToString() const;`
