# Runtime / StreamingFile

- module root: `Source/Runtime/StreamingFile`
- headers: 1; symbols: 40
- symbol kinds: class=1, delegate=1, function=6, member=1, prototype=31
- PublicDependencyModuleNames: Core, NetworkFile, Sockets

### `Source/Runtime/StreamingFile/Public/StreamingNetworkPlatformFile.h` (Public)


#### class `FStreamingNetworkPlatformFile`  
`class FStreamingNetworkPlatformFile : public FNetworkPlatformFile`  
_L129-227_
- inherits: `FNetworkPlatformFile`
- desc: Wrapper to redirect the low level file system to a server
- L135 _private prototype_ `virtual bool InitializeInternal(IPlatformFile* Inner, const TCHAR* HostIP) override;` — FNetworkPlatformFile interface
- L140 _public function_ `FStreamingNetworkPlatformFile()` — Default Constructor
- L147 _public prototype_ `virtual ~FStreamingNetworkPlatformFile();` — Virtual destructor
- L151 _public function_ `static const TCHAR* GetTypeName()`
- L157 _public prototype_ `class FStreamingNetworkFileHandle* SendOpenMessage(const FString& Filename, bool bIsWriting, bool bAppend, bool bAllowRead);` — Sends Open message to the server and creates a new file handle if successful.
- L160 _public prototype_ `bool SendReadMessage(uint64 HandleId, uint8* Destination, int64 BytesToRead);` — Sends Read message to the server.
- L162 _public prototype_ `bool SendReadMessage(uint64 HandleId, uint8* Destination, int64 BytesToRead, int64 Offset);`
- L165 _public prototype_ `bool SendWriteMessage(uint64 HandleId, const uint8* Source, int64 BytesToWrite);` — Sends Write message to the server.
- L168 _public prototype_ `bool SendSeekMessage(uint64 HandleId, int64 NewPosition);` — Sends Seek message to the server.
- L171 _public prototype_ `bool SendCloseMessage(uint64 HandleId);` — Sends Close message to the server.
- L176 _public function_ `void InitializeAfterSetActive() override` — need to override what FNetworkPlatformFile does here
- L180 _public prototype_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override;`
- L182 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L186 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L191 _public function_ `virtual const TCHAR* GetName() const override`
- L196 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L197 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L198 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L199 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L200 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L201 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L202 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L203 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L204 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend, bool bAllowRead) override;`
- L205 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L206 _public prototype_ `virtual bool CreateDirectoryTree(const TCHAR* Directory) override;`
- L207 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L208 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L209 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L210 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L211 _public prototype_ `virtual bool DeleteDirectoryRecursively(const TCHAR* Directory) override;`
- L212 _public prototype_ `virtual bool CopyFile(const TCHAR* To, const TCHAR* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) override;`
- L213 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForRead( const TCHAR* Filename ) override;`
- L214 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForWrite( const TCHAR* Filename ) override;`
- L220 _private prototype_ `virtual void PerformHeartbeat() override;`
- L221 _private prototype_ `virtual void GetFileInfo(const TCHAR* Filename, FFileInfo& Info) override;`
- L226 _private member_ `TArray<FString> FilesToSyncAsync;` — Set files that the server said we should sync asynchronously

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStreamingPlatformFile, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStreamingPlatformFile, Log, All);`
