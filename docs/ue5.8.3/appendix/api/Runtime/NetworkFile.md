# Runtime / NetworkFile

- module root: `Source/Runtime/NetworkFile`
- headers: 1; symbols: 110
- symbol kinds: class=2, delegate=1, function=20, member=37, namespace=2, prototype=48
- PrivateDependencyModuleNames: CookOnTheFly, Core, CoreUObject, Sockets
- PrivateIncludePathModuleNames: DerivedDataCache

### `Source/Runtime/NetworkFile/Public/NetworkPlatformFile.h` (Public)


#### class `FNetworkPlatformFile`  
`class FNetworkPlatformFile : public IPlatformFile, public FSelfRegisteringExec`  
_L38-309_
- inherits: `IPlatformFile,FSelfRegisteringExec`
- desc: Wrapper to redirect the low level file system to a server
- L51 _protected prototype_ `virtual bool InitializeInternal(IPlatformFile* Inner, const TCHAR* HostIP);` — Initialize network platform file give the specified host IP @param Inner Inner platform file @param HostIP host IP address @return true if the initialization succeeded, false otherwise
- L53 _protected prototype_ `virtual void OnFileUpdated(const FString& LocalFilename);`
- L58 _public function_ `static const TCHAR* GetTypeName()`
- L64 _public prototype_ `FNetworkPlatformFile();` — Constructor
- L67 _public prototype_ `virtual ~FNetworkPlatformFile();` — Destructor
- L69 _public prototype_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override;`
- L70 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;`
- L71 _public prototype_ `virtual void InitializeAfterSetActive() override;`
- L73 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L77 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L81 _public function_ `virtual void GetTimeStampPair(const TCHAR* PathA, const TCHAR* PathB, FDateTime& OutTimeStampA, FDateTime& OutTimeStampB)`
- L92 _public function_ `virtual const TCHAR* GetName() const override`
- L97 _public function_ `virtual bool IsUsable()`
- L102 _public function_ `virtual bool FileExists(const TCHAR* Filename) override`
- L108 _public function_ `virtual int64 FileSize(const TCHAR* Filename) override`
- L114 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L115 _public function_ `virtual bool IsReadOnly(const TCHAR* Filename) override`
- L121 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L122 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L123 _public function_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override`
- L129 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L130 _public function_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override`
- L136 _public function_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override`
- L140 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L141 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L142 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L143 _public prototype_ `virtual bool CreateDirectoryTree(const TCHAR* Directory) override;`
- L144 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L145 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L147 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L149 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L150 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L152 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L153 _public prototype_ `virtual bool IterateDirectoryStatRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L155 _public prototype_ `virtual bool DeleteDirectoryRecursively(const TCHAR* Directory) override;`
- L156 _public prototype_ `virtual bool CopyFile(const TCHAR* To, const TCHAR* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) override;`
- L158 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForRead( const TCHAR* Filename ) override;`
- L159 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForWrite( const TCHAR* Filename ) override;`
- L161 _public prototype_ `virtual bool SendMessageToServer(const TCHAR* Message, IPlatformFile::IFileServerMessageHandler* Handler) override;`
- L164 _public prototype_ `virtual void Tick() override;`
- L168 _public prototype_ `virtual bool SendPayloadAndReceiveResponse(TArray<uint8>& In, TArray<uint8>& Out);`
- L169 _public prototype_ `virtual bool ReceiveResponse(TArray<uint8>& Out);`
- L171 _public prototype_ `bool SendReadMessage(uint8* Destination, int64 BytesToRead);`
- L172 _public prototype_ `bool SendWriteMessage(const uint8* Source, int64 BytesToWrite);`
- L174 _public prototype_ `static void ConvertServerFilenameToClientFilename(FString& FilenameToConvert, const FString& InServerEngineDir, const FString& InServerProjectDir, const FString& InServerEnginePlatformExtensionsDir, const FString& InServerProjectPlatformExtensionsDir);`
- L177 _public prototype_ `virtual FString GetVersionInfo() const;`
- L183 _protected prototype_ `virtual bool Exec_Runtime(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar ) override;` — FSelfRegisteringExec interface
- L190 _protected prototype_ `virtual void PerformHeartbeat();` — Send a heartbeat message to the file server. This will tell it we are alive, as well as get back a list of files that have been updated on the server (so we can toss our copy)
- L192 _protected prototype_ `virtual void GetFileInfo(const TCHAR* Filename, FFileInfo& Info);`
- L200 _protected prototype_ `virtual void ConvertServerFilenameToClientFilename(FString& FilenameToConvert);` — Convert the given filename from the server to the client version of it NOTE: Potentially modifies the input FString!!!! @param	FilenameToConvert		Upon input, the server version of the filename. After the call, the client version
- L202 _protected prototype_ `virtual void FillGetFileList(FNetworkFileArchive& Payload);`
- L204 _protected prototype_ `virtual void ProcessServerInitialResponse(FArrayReader& InResponse, FPackageFileVersion& OutServerPackageVersion, int32& OutServerPackageLicenseeVersion);`
- L205 _protected prototype_ `virtual void ProcessServerCachedFilesResponse(FArrayReader& InReponse, const FPackageFileVersion& ServerPackageVersion, const int32 ServerPackageLicenseeVersion );`
- L216 _private prototype_ `static bool IsMediaExtension(const TCHAR* Ext);` — Returns whether the passed in extension is a video extension. Extensions with and without trailing dots are supported. @param	Extension to test. @return	True if Ext is a video extension.  e.g. .mp4
- L224 _private prototype_ `static bool IsAdditionalCookedFileExtension(const TCHAR* Ext);` — Returns whether the passed in extension is a an additional (but non asset) cooked file. @param	Extension to test. @return	True if Ext is a additional cooked file.  e.g. .ubulk, .ufont
- L229 _private prototype_ `bool IsInLocalDirectory(const FString& Filename);` — @return true if the path exists in a directory that should always use the local filesystem
- L234 _private prototype_ `void EnsureFileIsLocal(const FString& Filename);` — Given a filename, make sure the file exists on the local filesystem
- L236 _private prototype_ `void OnCookOnTheFlyMessage(const UE::Cook::FCookOnTheFlyMessage& Message);`
- L243 _protected prototype_ `void MakeStandardNetworkFilename(FString& Filename);` — Does normal path standardization, and also any extra modifications to make string comparisons against the internal directory list work properly.
- L248 _protected member_ `IPlatformFile* InnerPlatformFile;` — The file interface to read/write local files with
- L251 _protected member_ `TSet<FString> CachedLocalFiles;` — This keeps track of what files have been "EnsureFileIsLocal'd"
- L254 _protected member_ `FString ServerEngineDir;` — The server engine dir
- L257 _protected member_ `FString ServerProjectDir;` — The server game dir
- L260 _protected member_ `FString ServerEnginePlatformExtensionsDir;` — The server engine platform extensions dir
- L263 _protected member_ `FString ServerProjectPlatformExtensionsDir;` — The server project platform extensions dir
- L266 _protected member_ `FServerTOC ServerFiles;` — This is the "TOC" of the server
- L269 _protected member_ `TArray<FString> LocalDirectories;` — Set of directories that should use the local filesystem
- L271 _protected member_ `FCriticalSection SynchronizationObject;`
- L272 _protected member_ `bool bIsUsable;`
- L273 _protected member_ `int32 FileServerPort;`
- L277 _protected member_ `EConnectionFlags ConnectionFlags;` — the connection flags are passed to the server during GetFileList the server may cache them
- L279 _protected member_ `float HeartbeatFrequency;` — Frequency to send heartbeats to server in seconds set to negative number to disable
- L283 _protected member_ `double TotalWriteTime;` — some stats for messuring network platform file performance
- L284 _protected member_ `double TotalNetworkSyncTime;` — total non async time spent syncing to network
- L285 _protected member_ `int32 TotalFilesSynced;` — total number files synced from network
- L286 _protected member_ `int32 TotalUnsolicitedPackages;` — total number unsolicited files synced
- L287 _protected member_ `int32 TotalFilesFoundLocally;`
- L288 _protected member_ `int32 UnsolicitedPackagesHits;` — total number of hits from waiting on unsolicited packages
- L289 _protected member_ `int32 UnsolicitedPackageWaits;` — total number of waits on unsolicited packages
- L290 _protected member_ `double TotalTimeSpentInUnsolicitedPackages;` — total time async processing unsolicited packages
- L291 _protected member_ `double TotalWaitForAsyncUnsolicitedPackages;` — total time spent waiting for unsolicited packages
- L298 _private member_ `FScopedEvent *FinishedAsyncNetworkReadUnsolicitedFiles;` — Unsolicitied files events
- L299 _private member_ `FScopedEvent *FinishedAsyncWriteUnsolicitedFiles;`
- L301 _private member_ `TSharedPtr<UE::Cook::ICookOnTheFlyServerConnection> Connection;`
- L302 _private member_ `TSpscQueue<TArray<uint8>> PendingPayloads;`
- L303 _private member_ `FEventRef NewPayloadEvent;`
- L305 _private member_ `static FString MP4Extension;`
- L306 _private member_ `static FString BulkFileExtension;`
- L307 _private member_ `static FString ExpFileExtension;`
- L308 _private member_ `static FString FontFileExtension;`

#### class `FNetworkFileHandle`  
`class FNetworkFileHandle : public IFileHandle`  
_L311-397_
- inherits: `IFileHandle`
- L313 _private member_ `FNetworkPlatformFile& Network;`
- L314 _private member_ `FString Filename;`
- L315 _private member_ `int64 FilePos;`
- L316 _private member_ `int64 Size;`
- L317 _private member_ `bool bWritable;`
- L318 _private member_ `bool bReadable;`
- L321 _public function_ `FNetworkFileHandle(FNetworkPlatformFile& InNetwork, const TCHAR* InFilename, int64 InFilePos, int64 InFileSize, bool bWriting) : Network(InNetwork) , Filename(InFilename) , FilePos(InFilePos) , Size(InFileSize) , bWritable(bWriting) , bReadable(!bWriting)`
- L331 _public function_ `virtual int64 Tell() override`
- L335 _public function_ `virtual bool Seek(int64 NewPosition) override`
- L344 _public function_ `virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override`
- L348 _public function_ `virtual bool Read(uint8* Destination, int64 BytesToRead) override`
- L368 _public function_ `virtual bool Write(const uint8* Source, int64 BytesToWrite) override`
- L389 _public function_ `virtual bool Flush(const bool bFullFlush = false) override`
- L393 _public function_ `virtual bool Truncate(int64 NewSize) override`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Cook` (scope `UE`)
- L32 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPlatformFile, Log, All);`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPlatformFile, Log, All);`
