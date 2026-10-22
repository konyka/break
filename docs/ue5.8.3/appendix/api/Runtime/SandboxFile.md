# Runtime / SandboxFile

- module root: `Source/Runtime/SandboxFile`
- headers: 1; symbols: 73
- symbol kinds: class=1, delegate=1, function=1, member=16, prototype=54
- PrivateDependencyModuleNames: Core

### `Source/Runtime/SandboxFile/Public/IPlatformFileSandboxWrapper.h` (Public)


#### class `FSandboxPlatformFile`  
`class FSandboxPlatformFile : public IPlatformFile`  
_L24-232_
- inherits: `IPlatformFile`
- L27 _private member_ `IPlatformFile* LowerLevel;` — Wrapped file
- L29 _private member_ `FString SandboxDirectory;` — Absolute path to the sandbox directory
- L31 _private member_ `FString GameSandboxDirectoryName;` — Name of the game's sandbox directory
- L33 _private member_ `FString RelativeRootDirectory;` — Relative path to root directory. Cached for faster access
- L35 _private member_ `FString AbsoluteRootDirectory;` — Absolute path to root directory. Cached for faster access
- L37 _private member_ `FString AbsoluteGameDirectory;` — Absolute game directory. Cached for faster access
- L39 _private member_ `FString AbsolutePathToGameDirectory;` — Absolute path to game directory. Cached for faster access
- L41 _private member_ `TArray<FString> FileExclusionWildcards;` — Access to any file (in unreal standard form) matching this is not allowed
- L43 _private member_ `TArray<FString> DirectoryExclusionWildcards;` — Access to any directory (in unreal standard form) matching this is not allowed
- L44 _private member_ `bool bEntireEngineWillUseThisSandbox;`
- L51 _private member_ `bool bSandboxEnabled;` — Whether the sandbox is enabled or not. Defaults to true. Set to false when operations require writing to the actual physical location given.
- L58 _private member_ `FString InjectedSourceDirectory;` — For an injection sandbox, we insert the contents of one directory into the contents of another directory (InjectedSource) in the eyes of the engine (InjectedTarget). So you could inject C:\MyPlugins\Foo into ../../../MyProject/Plugins/Foo and as far as the engine knows, Foo is underneath your MyProject directory
- L59 _private member_ `FString InjectedSourceDirectoryParent;`
- L60 _private member_ `FString InjectedTargetDirectory;`
- L61 _private member_ `FString InjectedTargetDirectoryParent;`
- L67 _private member_ `bool bSandboxOnly;` — Whether access is restricted to the sandbox or not. Defaults to false.
- L75 _private prototype_ `bool WipeSandboxFolder( const TCHAR* AbsolutePath );` — Clears the contents of the specified folder @param AbsolutePath Absolute path to the folder to wipe @return true if the folder's contents could be deleted, false otherwise
- L87 _private prototype_ `void FindFiles( TArray<FString>& Result, const TCHAR* InFilename, bool Files, bool Directories );` — Finds all files or folders in the given directory. This is partially copied from file manager but since IPlatformFile is lower level it's better to have local version which doesn't use the wrapped IPlatformFile. @param Result List of found files or folders. @param InFilename Path to the folder to look in. @param Files true to include files in the Result @param Files true to include directories in the Result
- L101 _private prototype_ `bool DeleteDirectory( const TCHAR* Path, bool Tree );` — Deletes a directory This is partially copied from file manager but since IPlatformFile is lower level it's better to have local version which doesn't use the wrapped IPlatformFile. @param Path Path to the directory to delete. @param Tree true to recursively delete the directory and its contents @return true if the operaton was successful.
- L110 _private prototype_ `bool OkForInnerAccess(const TCHAR* InFilenameOrDirectoryName, bool bIsDirectory = false) const;` — Check if a file or directory has been filtered, and hence is unavailable to the outside world @param FilenameOrDirectoryName @param bIsDirectory if true, this is a directory @return true if it is ok to access the non-sandboxed files here
- L112 _private function_ `static const TCHAR* GetTypeName()`
- L121 _private prototype_ `FSandboxPlatformFile(bool bInEntireEngineWillUseThisSandbox);` — Converts passed in filename to use a sandbox path. @param	bEntireEngineWillUseThisSandbox		If true, the we set up the engine so that subprocesses also use this subdirectory
- L124 _public prototype_ `static TUniquePtr<FSandboxPlatformFile> Create(bool bInEntireEngineWillUseThisSandbox);`
- L126 _public prototype_ `virtual ~FSandboxPlatformFile();`
- L139 _public prototype_ `virtual void SetSandboxEnabled(bool bInEnabled) override;` — Set whether the sandbox is enabled or not @param	bInEnabled		true to enable the sandbox, false to disable it
- L146 _public prototype_ `virtual bool IsSandboxEnabled() const override;` — Returns whether the sandbox is enabled or not @return	bool			true if enabled, false if not
- L148 _public prototype_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override;`
- L149 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;`
- L151 _public prototype_ `virtual IPlatformFile* GetLowerLevel() override;`
- L152 _public prototype_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override;`
- L153 _public prototype_ `virtual const TCHAR* GetName() const override;`
- L162 _public prototype_ `FString ConvertToSandboxPath(const TCHAR* Filename) const;` — Converts passed in filename to use a sandbox path. @param	Filename	filename (under game directory) to convert to use a sandbox path. Can be relative or absolute. @return	filename using sandbox path
- L163 _public prototype_ `FString ConvertFromSandboxPath(const TCHAR* Filename) const;`
- L166 _public prototype_ `const FString& GetSandboxDirectory() const;` — Returns sandbox directory
- L169 _public prototype_ `const FString& GetGameSandboxDirectoryName();` — Returns the name of the sandbox directory for the game's content
- L172 _public prototype_ `const FString& GetAbsoluteRootDirectory() const;` — Returns absolute root directory
- L175 _public prototype_ `const FString& GetAbsoluteGameDirectory();` — Returns absolute game directory
- L178 _public prototype_ `const FString& GetAbsolutePathToGameDirectory();` — Returns absolute path to game directory (without the game directory itself)
- L186 _public prototype_ `void AddExclusion(const TCHAR* Wildcard, bool bIsDirectory = false);` — Add exclusion. These files and / or directories pretend not to exist so that they cannot be accessed at all (except in the sandbox) @param Wildcard FString::MatchesWildcard-type wild card to test for exclusion @param bIsDirectory if true, this is a directory @Caution, these have a performance cost
- L187 _public prototype_ `void RemoveExclusion(const TCHAR* Wildcard, bool bIsDirectory = false);`
- L190 _public prototype_ `void SetSandboxOnly(bool bInSandboxOnly);` — Whether access is restricted the the sandbox or not.
- L194 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) override;`
- L195 _public prototype_ `virtual int64 FileSize(const TCHAR* Filename) override;`
- L196 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L197 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L198 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L199 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L200 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L201 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L202 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L203 _public prototype_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;`
- L204 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L205 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L206 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L207 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L208 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L209 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L211 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L212 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L214 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L215 _public prototype_ `virtual bool IterateDirectoryStatRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L217 _public prototype_ `virtual bool DeleteDirectoryRecursively(const TCHAR* Directory) override;`
- L218 _public prototype_ `virtual bool CreateDirectoryTree(const TCHAR* Directory) override;`
- L220 _public prototype_ `virtual bool CopyFile(const TCHAR* To, const TCHAR* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) override;`
- L221 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForRead( const TCHAR* Filename ) override;`
- L222 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForWrite( const TCHAR* Filename ) override;`
- L224 _public prototype_ `virtual IAsyncReadFileHandle* OpenAsyncRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L225 _public prototype_ `virtual void SetAsyncMinimumPriority(EAsyncIOPriorityAndFlags Priority) override;`
- L227 _public prototype_ `virtual FOpenMappedResult OpenMappedEx(const TCHAR* Filename, EOpenReadFlags OpenOptions = EOpenReadFlags::None, int64 MaximumSize = 0) override;`
- L228 _public prototype_ `virtual FOpenMappedResult OpenMappedEx2(const TCHAR* Filename, EOpenMappedFlags OpenOptions = EOpenMappedFlags::None, int64 MaximumSize = 0) override;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(SandboxFile, Log, All);` — Wrapper to log the low level file system
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SandboxFile, Log, All);` — Wrapper to log the low level file system
