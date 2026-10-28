# Runtime / NetworkFileSystem

- module root: `Source/Runtime/NetworkFileSystem`
- headers: 5; symbols: 133
- symbol kinds: class=4, delegate=6, enum=1, enumerator=3, function=3, member=53, namespace=4, prototype=57, struct=2
- PrivateDependencyModuleNames: CookOnTheFly, CookOnTheFlyNetServer, CoreUObject, DesktopPlatform, Engine, Projects, SandboxFile, TargetPlatform
- PublicDependencyModuleNames: Core, Sockets

### `Source/Runtime/NetworkFileSystem/Private/NetworkFileServer.h` (Private)


#### class `FNetworkFileServer`  
`class FNetworkFileServer : public INetworkFileServer`  
_L24-61_
- inherits: `INetworkFileServer`
- desc: This class wraps the server thread and network connection
- L34 _public prototype_ `FNetworkFileServer(FNetworkFileServerOptions InFileServerOptions, TSharedRef<UE::Cook::ICookOnTheFlyNetworkServer> InCookOnTheFlyNetworkServer);` — Creates and initializes a new instance. @param InFileServerOptions Network file server options
- L39 _public prototype_ `~FNetworkFileServer( );` — Destructor.
- L43 _public prototype_ `virtual bool IsItReadyToAcceptConnections(void) const override;`
- L44 _public prototype_ `virtual bool GetAddressList(TArray<TSharedPtr<FInternetAddr> >& OutAddresses) const override;`
- L45 _public prototype_ `virtual FString GetSupportedProtocol() const override;`
- L46 _public prototype_ `virtual int32 NumConnections() const override;`
- L47 _public prototype_ `virtual void Shutdown() override;`
- L49 _private prototype_ `void OnClientConnected(UE::Cook::ICookOnTheFlyClientConnection& Connection);`
- L50 _private prototype_ `void OnClientDisconnected(UE::Cook::ICookOnTheFlyClientConnection& Connection);`
- L51 _private prototype_ `bool HandleRequest(UE::Cook::ICookOnTheFlyClientConnection& Connection, const UE::Cook::FCookOnTheFlyRequest& Request);`
- L54 _private member_ `FNetworkFileServerOptions FileServerOptions;` — File server options
- L56 _private member_ `TSharedPtr<UE::Cook::ICookOnTheFlyNetworkServer> CookOnTheFlyServer;`
- L59 _private member_ `FCriticalSection ConnectionsCritical;` — Holds all the client connections.
- L60 _private member_ `TMap<UE::Cook::ICookOnTheFlyClientConnection*, class FCookOnTheFlyNetworkFileServerConnection*> Connections;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cook` (scope `UE`)

### `Source/Runtime/NetworkFileSystem/Private/NetworkFileServerConnection.h` (Private)


#### class `FNetworkFileServerClientConnection`  
`class FNetworkFileServerClientConnection : public FSelfRegisteringExec`  
_L16-295_
- inherits: `FSelfRegisteringExec`
- desc: This class processes all incoming messages from the client.
- L26 _public prototype_ `FNetworkFileServerClientConnection(const FNetworkFileServerOptions& InFileServerOptions);` — Creates and initializes a new instance. @param InSocket - The client socket to use. @param NetworkFileDelegates- delegates the client calls when events from the client happen
- L31 _public prototype_ `virtual ~FNetworkFileServerClientConnection( );` — Destructor.
- L41 _public prototype_ `bool ProcessPayload(FArchive& Ar);` — Processes the given payload. @param Ar An archive containing the payload data. @param Out An archive that will contain the processed data.
- L48 _public prototype_ `FString GetDescription() const;` — Gets the client connection's description. @return Description string.
- L58 _protected prototype_ `void ConvertClientFilenameToServerFilename(FString& FilenameToConvert);` — Convert the given filename from the client to the server version of it NOTE: Potentially modifies the input FString!!!! @param	FilenameToConvert		Upon input, the client version of the filename. After the call, the server version
- L66 _protected prototype_ `void ConvertLocalFilenameToServerFilename(FString& FilenameToConvert);` — Convert the given filename from the an arbitrary local representation to the normalized server version of it NOTE: Potentially modifies the input FString!!!! @param	FilenameToConvert		Upon input, the filename. After the call, the server version
- L77 _protected prototype_ `void ProcessOpenFile(FArchive& In, FArchive& Out, bool bIsWriting);` — Opens a file for reading or writing.
- L80 _protected prototype_ `void ProcessReadFile(FArchive& In, FArchive& Out);` — Reads from file.
- L83 _protected prototype_ `void ProcessWriteFile(FArchive& In, FArchive& Out);` — Writes to file.
- L86 _protected prototype_ `void ProcessSeekFile(FArchive& In, FArchive& Out);` — Seeks in file.
- L89 _protected prototype_ `void ProcessCloseFile(FArchive& In, FArchive& Out);` — Closes file handle and removes it from the open handles list.
- L92 _protected prototype_ `void ProcessGetFileInfo(FArchive& In, FArchive& Out);` — Gets info on the specified file.
- L95 _protected prototype_ `void ProcessMoveFile(FArchive& In, FArchive& Out);` — Moves file.
- L98 _protected prototype_ `void ProcessDeleteFile(FArchive& In, FArchive& Out);` — Deletes file.
- L101 _protected prototype_ `void ProcessCopyFile(FArchive& In, FArchive& Out);` — Copies file.
- L104 _protected prototype_ `void ProcessSetTimeStamp(FArchive& In, FArchive& Out);` — Sets file timestamp.
- L107 _protected prototype_ `void ProcessSetReadOnly(FArchive& In, FArchive& Out);` — Sets read only flag.
- L110 _protected prototype_ `void ProcessCreateDirectory(FArchive& In, FArchive& Out);` — Creates directory.
- L113 _protected prototype_ `void ProcessDeleteDirectory(FArchive& In, FArchive& Out);` — Deletes directory.
- L116 _protected prototype_ `void ProcessDeleteDirectoryRecursively(FArchive& In, FArchive& Out);` — Deletes directory recursively.
- L119 _protected prototype_ `void ProcessToAbsolutePathForRead(FArchive& In, FArchive& Out);` — ConvertToAbsolutePathForExternalAppForRead.
- L122 _protected prototype_ `void ProcessToAbsolutePathForWrite(FArchive& In, FArchive& Out);` — ConvertToAbsolutePathForExternalAppForWrite.
- L125 _protected prototype_ `void ProcessReportLocalFiles(FArchive& In, FArchive& Out);` — Reposts local files.
- L128 _protected prototype_ `bool ProcessGetFileList(FArchive& In, FArchive& Out);` — Walk over a set of directories, and get all files (recursively) in them, along with their timestamps.
- L131 _protected prototype_ `void ProcessHeartbeat(FArchive& In, FArchive& Out);` — Heartbeat.
- L139 _protected function_ `FORCEINLINE IFileHandle* FindOpenFile( uint64 HandleId )` — Finds open file handle by its ID. @param HandleId @return Pointer to the file handle, NULL if the specified handle id doesn't exist.
- L146 _protected prototype_ `bool PackageFile( FString& Filename, FString& TargetFilename, FArchive& Out);`
- L154 _protected prototype_ `bool ProcessSyncFile( FArchive& In, FArchive& Out );` — Processes a heartbeat message. @param In - @param Out -
- L157 _protected prototype_ `virtual bool SendPayload( TArray<uint8> &Out ) = 0;`
- L165 _protected prototype_ `void FileModifiedCallback( const FString& Filename );` — When a file is modified this callback is triggered cleans up any cached information about the file and notifies client @param Filename of the file which has been modified
- L168 _protected prototype_ `virtual bool Exec_Runtime(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L178 _protected prototype_ `FString FixupSandboxPathForClient(const FString& Filename);` — Convert a path to a sandbox path and translate so the client can understand it @param Filename to convert @param bLowerCaseFiles conver the file name to all lower case @return Resulting fixed up path
- L187 _protected prototype_ `TMap<FString,FDateTime> FixupSandboxPathsForClient(const TMap<FString, FDateTime>& SandboxPaths);` — Convert a path to a sandbox path and translate so the client can understand it @param Filename to convert @param bLowerCaseFiles conver the file name to all lower case @return Resulting fixed up path
- L192 _private member_ `FString ConnectedPlatformName;` — Hold the name of the currently connected platform.
- L195 _private member_ `FString ConnectedIPAddress;` — Hold the ip address of the currently connected platform.
- L198 _private member_ `FString ConnectedEngineDir;` — Hold the engine directory from the connected platform.
- L201 _private member_ `FString ConnectedProjectDir;` — Hold the game directory from the connected platform.
- L204 _private member_ `FString ConnectedEnginePlatformExtensionsDir;` — Hold the engine platform extensions directory from the connected platform.
- L207 _private member_ `FString ConnectedProjectPlatformExtensionsDir;` — Hold the project platform extensions directory from the connected platform.
- L210 _private member_ `FString SandboxEngine;` — Hold the sandbox engine directory for the connected platform
- L213 _private member_ `FString SandboxProject;` — hold the sandbox game directory for the connected platform
- L216 _private member_ `FString SandboxEnginePlatformExtensions;` — hold the engine sandbox platform extensions directory for the connected platform
- L219 _private member_ `FString SandboxProjectPlatformExtensions;` — hold the project sandbox platform extensions directory for the connected platform
- L222 _private member_ `bool bSendLowerCase;` — Should we send the filenames in lowercase
- L225 _private member_ `uint64 LastHandleId;` — Holds the last assigned handle id (0 = invalid).
- L228 _private member_ `TArray<FString> ModifiedFiles;` — Holds the list of files found by the directory watcher.
- L231 _private member_ `FCriticalSection ModifiedFilesSection;` — Holds a critical section to protect the ModifiedFiles array.
- L234 _private member_ `TMap<uint64, IFileHandle*> OpenFiles;` — Holds all currently open file handles.
- L237 _private member_ `TUniquePtr<FSandboxPlatformFile> Sandbox;` — Holds the file interface for local (to the server) files - all file ops MUST go through here, NOT IFileManager.
- L240 _private member_ `TArray<FString> UnsolictedFiles;` — Holds the list of unsolicited files to send in separate packets.
- L243 _private member_ `TArray<FString> WatchedDirectories;` — Holds the list of directories being watched.
- L246 _private member_ `FString LocalEngineDir;` — Local path to the engine directory
- L249 _private member_ `FString LocalEngineDirAbs;` — Absolute local path to the engine directory
- L252 _private member_ `FString LocalProjectDir;` — Local path to the project directory
- L255 _private member_ `FString LocalProjectDirAbs;` — Absolute local path to the project directory
- L258 _private member_ `FString LocalEnginePlatformExtensionsDir;` — Local path to the engine platform extensions directory
- L261 _private member_ `FString LocalEnginePlatformExtensionsDirAbs;` — Absolute local path to the engine platform extensions directory
- L264 _private member_ `FString LocalProjectPlatformExtensionsDir;` — Local path to the project platform extensions directory
- L267 _private member_ `FString LocalProjectPlatformExtensionsDirAbs;` — Absolute local path to the project platform extensions directory
- L269 _private member_ `const FNetworkFileDelegateContainer* NetworkFileDelegates;`
- L272 _private member_ `const TArray<ITargetPlatform*>& ActiveTargetPlatforms;` — cached copy of the active target platforms (if any)
- L275 _private member_ `ITargetPlatform* ConnectedTargetPlatform;` — connected TargetPlatform object, if ActiveTargetPlatforms existed
- L278 _private member_ `TMap<FString,FString> ConnectedTargetCustomData;` — custom key-value pair data for the curently connected target platform
- L281 _private member_ `bool bRestrictPackageAssetsToSandbox;` — whether to restrict sending package assets from outside the sandbox
- L285 _private member_ `double FileRequestDelegateTime;` — stats
- L286 _private member_ `double PackageFileTime;`
- L287 _private member_ `double UnsolicitedFilesTime;`
- L289 _private member_ `int32 FileRequestCount;`
- L290 _private member_ `int32 UnsolicitedFilesCount;`
- L291 _private member_ `int32 PackageRequestsSucceeded;`
- L292 _private member_ `int32 PackageRequestsFailed;`
- L293 _private member_ `int32 FileBytesSent;`

### `Source/Runtime/NetworkFileSystem/Private/NetworkFileSystemLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFileServer, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFileServer, Log, All);`

### `Source/Runtime/NetworkFileSystem/Public/INetworkFileServer.h` (Public)


#### class `INetworkFileServer`  
`class INetworkFileServer`  
_L12-60_
- desc: Interface for network file servers.
- L21 _public prototype_ `virtual bool IsItReadyToAcceptConnections(void) const = 0;` — Returns Whether the network server was able to successfully start or not. @return true on success, false otherwise.
- L30 _public prototype_ `virtual bool GetAddressList( TArray<TSharedPtr<FInternetAddr> >& OutAddresses ) const = 0;` — Gets the list of local network addresses that the file server listens on. @param OutAddresses - Will hold the address list. @return true on success, false otherwise.
- L40 _public prototype_ `virtual FString GetSupportedProtocol() const = 0;` — Gets the list of local network addresses that the file server listens on. @param OutAddresses - Will hold the address list. @return true on success, false otherwise.
- L47 _public prototype_ `virtual int32 NumConnections(void) const = 0;` — Gets the number of active connections. @return The number of connections.
- L52 _public prototype_ `virtual void Shutdown(void) = 0;` — Shuts down the file server.
- L59 _public prototype_ `virtual ~INetworkFileServer(void) = default;` — Virtual destructor.

### `Source/Runtime/NetworkFileSystem/Public/INetworkFileSystemModule.h` (Public)


#### struct `FNetworkFileDelegateContainer`  
`struct FNetworkFileDelegateContainer`  
_L50-66_
- desc: container struct for delegates which the network file system uses
- L53 _public function_ `FNetworkFileDelegateContainer() : NewConnectionDelegate(nullptr), SandboxPathOverrideDelegate(nullptr), FileRequestDelegate(nullptr), RecompileShadersDelegate(nullptr), OnFileModifiedCallback(nullptr)`
- L60 _public member_ `FNewConnectionDelegate NewConnectionDelegate;`
- L61 _public member_ `FSandboxPathDelegate SandboxPathOverrideDelegate;`
- L62 _public member_ `FFileRequestDelegate FileRequestDelegate;`
- L63 _public member_ `FRecompileShadersDelegate RecompileShadersDelegate;`
- L65 _public member_ `FOnFileModifiedDelegate* OnFileModifiedCallback;` — this is called from other systems to notify the network file system that a file has been modified hence the terminology callback

#### enum `ENetworkFileServerProtocol`  
`enum ENetworkFileServerProtocol`  
_L68-80_
- L70 _public enumerator_ `NFSP_Tcp`
- L71 _public enumerator_ `NFSP_Http`
- L79 _public enumerator_ `NFSP_Platform` — Platform-specific type of connection between a target device and a host pc. It potentially offers performance benefits compared to generic networking protocols but is supported by only some of the platforms.

#### struct `FNetworkFileServerOptions`  
`struct FNetworkFileServerOptions`  
_L83-99_
- desc: Network file server options
- L86 _public member_ `ENetworkFileServerProtocol Protocol = NFSP_Tcp;` — File server protocol
- L89 _public member_ `int32 Port = INDEX_NONE;` — The port number to bind to (-1 = default port, 0 = any available port)
- L92 _public member_ `FNetworkFileDelegateContainer Delegates;` — Optional delegates to be invoked when a file is requested by a client
- L95 _public member_ `TArray<ITargetPlatform*> TargetPlatforms;` — Active target platform(s)
- L98 _public member_ `bool bRestrictPackageAssetsToSandbox = false;` — When running cook on the fly this options restricts package assets being sent from the project content folder

#### class `INetworkFileSystemModule`  
`class INetworkFileSystemModule : public IModuleInterface`  
_L104-150_
- inherits: `IModuleInterface`
- desc: Interface for network file system modules.
- L119 _public prototype_ `virtual INetworkFileServer* CreateNetworkFileServer( bool bLoadTargetPlatforms, int32 Port = -1, FNetworkFileDelegateContainer InNetworkFileDelegateContainer = FNetworkFileDelegateContainer(), const ENetworkFileServerProtocol Protocol = NFSP_Tcp ) const = 0;` — Creates a new network file server. @param InPort The port number to bind to (-1 = default port, 0 = any available port). @param Streaming Whether it should be a streaming server. @param InFileRequestDelegate An optional delegate to be invoked when a file is requested by a client. @param InRecompileShadersDelegate An optional delegate to be invoked when shaders need to be recompiled. @return The new file server, or nullptr if creation failed.
- L129 _public prototype_ `virtual INetworkFileServer* CreateNetworkFileServer(FNetworkFileServerOptions FileServerOptions, bool bLoadTargetPlatforms) const = 0;` — Creates a new network file server. @param FileServerOptions File server options @param bLoadTargetPlatforms If true, gets the target platform from the command line or all available target platforms @return The new file server, or nullptr if creation failed.
- L139 _public function_ `virtual INetworkFileServer* CreateNetworkFileServer(TSharedRef<UE::Cook::ICookOnTheFlyNetworkServer> CookOnTheFlyNetworkServer, FNetworkFileDelegateContainer Delegates) const` — Creates a new network file server for COTF. @param CookOnTheFlyNetworkServer CookOnTheFly network server @param Delegates Delegates to be invoked when a file is requested by a client. @return The new file server, or nullptr if creation failed.
- L149 _public prototype_ `virtual ~INetworkFileSystemModule( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cook` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_ThreeParams(FFileRequestDelegate, FString&, const FString&, TArray<FString>&);` — Delegate type for handling file requests from a network client. The first parameter is the name of the requested file. The second parameter will hold the list of unsolicited files to send back.
- L21 _prototype_ `DECLARE_DELEGATE_ThreeParams(FFileRequestDelegate, FString&, const FString&, TArray<FString>&);` — Delegate type for handling file requests from a network client. The first parameter is the name of the requested file. The second parameter will hold the list of unsolicited files to send back.
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FRecompileShadersDelegate, const FShaderRecompileData&);` — Delegate type for handling shader recompilation requests from a network client.
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FRecompileShadersDelegate, const FShaderRecompileData&);` — Delegate type for handling shader recompilation requests from a network client.
- L31 _delegate_ `DECLARE_DELEGATE_RetVal( FString, FSandboxPathDelegate);` — Delegate which returns an override for the sandbox path
- L31 _prototype_ `DECLARE_DELEGATE_RetVal( FString, FSandboxPathDelegate);` — Delegate which returns an override for the sandbox path
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnFileModifiedDelegate, const FString& );` — Delegate which is called when an outside system modifies a file
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnFileModifiedDelegate, const FString& );` — Delegate which is called when an outside system modifies a file
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FNewConnectionDelegate, const FString&, const FString& );` — Delegate which is called when a new connection is made to a file server client @param 1 Version string @param 2 Platform name @return return false if the connection should be destroyed
- L46 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FNewConnectionDelegate, const FString&, const FString& );` — Delegate which is called when a new connection is made to a file server client @param 1 Version string @param 2 Platform name @return return false if the connection should be destroyed
