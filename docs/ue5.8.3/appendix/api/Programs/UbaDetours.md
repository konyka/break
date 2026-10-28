# Programs / UbaDetours

- module root: `Source/Programs/UnrealBuildAccelerator/Detours`
- headers: 19; symbols: 1093
- symbol kinds: class=2, enum=7, enumerator=23, externvar=42, function=488, macro=100, member=134, namespace=9, prototype=222, struct=23, typedef=14, variable=29
- PrivateDependencyModuleNames: Detours, OodleDataCompression, UbaCore

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/PosixOS/UbaDetoursGoPosix.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L13 _prototype_ `bool IsGoBinary(const char* path);` (scope `uba`)
- L14 _prototype_ `void PatchGoSyscalls();` (scope `uba`)
- L15 _prototype_ `void PatchGoExit();` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/PosixOS/UbaDetoursRealPosix.h` (Private)


#### struct `uba::Real_clone3_pidfd::uba_clone_args`  
`struct uba_clone_args`  
_L546-546_
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`
- L546 _public member_ `struct uba_clone_args { unsigned long flags, pidfd, child_tid, parent_tid, exit_signal, stack, stack_size, tls; };`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace uba`
- L28 _function_ `inline long Real_readlink(int& outError, const char* path, char* buf, unsigned long bufSize)` (scope `uba`)
- L41 _function_ `inline long Real_readlinkat(int& outError, int dirfd, const char* path, char* buf, unsigned long bufSize)` (scope `uba`)
- L56 _function_ `inline int Real_faccessat(int& outError, int dirfd, const char* path, int mode, int flags)` (scope `uba`)
- L69 _function_ `inline int Real_access(int& outError, const char* path, int mode)` (scope `uba`)
- L80 _function_ `inline long Real_lseek(int& outError, int fd, long offset, int whence)` (scope `uba`)
- L93 _function_ `inline int Real_dup(int& outError, int oldfd)` (scope `uba`)
- L106 _function_ `inline int Real_dup3(int& outError, int oldfd, int newfd, int flags)` (scope `uba`)
- L124 _function_ `inline int Real_dup2(int& outError, int oldfd, int newfd)` (scope `uba`)
- L137 _function_ `inline int Real_openat(int& outError, int dirfd, const char* path, int flags, int mode)` (scope `uba`)
- L150 _function_ `inline int Real_open(int& outError, const char* path, int flags, int mode)` (scope `uba`)
- L161 _function_ `inline int Real_close(int& outError, int fd)` (scope `uba`)
- L174 _function_ `inline long Real_read(int& outError, int fd, void* buf, unsigned long count)` (scope `uba`)
- L187 _function_ `inline long Real_pread(int& outError, int fd, void* buf, unsigned long count, long offset)` (scope `uba`)
- L200 _function_ `inline long Real_write(int& outError, int fd, const void* buf, unsigned long count)` (scope `uba`)
- L217 _function_ `inline int Real_fstatat(int& outError, int dirfd, const char* path, struct stat* buf, int flags)` (scope `uba`)
- L230 _function_ `inline int Real_fstat(int& outError, int fd, struct stat* buf)` (scope `uba`)
- L247 _function_ `inline int Real_stat(int& outError, const char* path, struct stat* buf)` (scope `uba`)
- L258 _function_ `inline int Real_lstat(int& outError, const char* path, struct stat* buf)` (scope `uba`)
- L270 _function_ `inline int Real_statx(int& outError, int dirfd, const char* path, int flags, unsigned int mask, struct ::statx* buf)` (scope `uba`)
- L280 _function_ `inline int Real_mkdirat(int& outError, int dirfd, const char* path, unsigned int mode)` (scope `uba`)
- L293 _function_ `inline int Real_mkdir(int& outError, const char* path, unsigned int mode)` (scope `uba`)
- L304 _function_ `inline int Real_unlinkat(int& outError, int dirfd, const char* path, int flags)` (scope `uba`)
- L317 _function_ `inline int Real_unlink(int& outError, const char* path)` (scope `uba`)
- L328 _function_ `inline int Real_rmdir(int& outError, const char* path)` (scope `uba`)
- L339 _function_ `inline int Real_renameat(int& outError, int olddirfd, const char* oldpath, int newdirfd, const char* newpath)` (scope `uba`)
- L352 _function_ `inline int Real_rename(int& outError, const char* oldpath, const char* newpath)` (scope `uba`)
- L364 _function_ `inline int Real_renameat2(int& outError, int olddirfd, const char* oldpath, int newdirfd, const char* newpath, unsigned int flags)` (scope `uba`)
- L372 _function_ `inline int Real_linkat(int& outError, int olddirfd, const char* oldpath, int newdirfd, const char* newpath, int flags)` (scope `uba`)
- L385 _function_ `inline int Real_link(int& outError, const char* oldpath, const char* newpath)` (scope `uba`)
- L396 _function_ `inline int Real_symlinkat(int& outError, const char* target, int newdirfd, const char* linkpath)` (scope `uba`)
- L409 _function_ `inline int Real_symlink(int& outError, const char* target, const char* linkpath)` (scope `uba`)
- L420 _function_ `inline int Real_fchmodat(int& outError, int dirfd, const char* path, unsigned int mode, int flags)` (scope `uba`)
- L433 _function_ `inline int Real_chmod(int& outError, const char* path, unsigned int mode)` (scope `uba`)
- L444 _function_ `inline int Real_fchmod(int& outError, int fd, unsigned int mode)` (scope `uba`)
- L457 _function_ `inline int Real_truncate(int& outError, const char* path, long length)` (scope `uba`)
- L471 _function_ `inline int Real_fcntl(int& outError, int fd, int cmd, long arg)` (scope `uba`) — fcntl's third arg is variadic and command-dependent. Caller passes the resolved arg as `long`.
- L484 _function_ `inline int Real_kill(int& outError, int pid, int sig)` (scope `uba`)
- L498 _function_ `[[noreturn]] inline void Real_exit_group(int code)` (scope `uba`) — SYS_exit_group on Linux (terminates the whole process); _exit on macOS (no atexit handlers either way).
- L510 _function_ `inline int Real_fork()` (scope `uba`)
- L524 _function_ `inline int Real_getpid()` (scope `uba`)
- L533 _function_ `inline int Real_prctl_pdeathsig()` (scope `uba`)
- L543 _function_ `inline long Real_clone3_pidfd(int* outPidfd)` (scope `uba`) — CLONE_PIDFD clone3 for host-pid tracking (see UbaDetoursSharedPosix.h). Linux 5.5+; -1 on Mac.

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/PosixOS/UbaDetoursSharedPosix.h` (Private)


#### struct `uba::DirInfo`  
`struct DirInfo`  
_L35-41_
- L37 _public member_ `Vector<DirTableOffset> fileTableOffsets;`
- L38 _public member_ `int it = -1;`
- L39 _public member_ `int realFd = -1;` — /dev/null fd registered in g_fileHandles so dirfd(DIR*) + openat(fd, "sub") works (depmod)
- L40 _public member_ `dirent ent;`

#### struct `uba::FileObject`  
`struct FileObject`  
_L46-57_
- L48 _public member_ `FileInfo* fileInfo = nullptr;`
- L49 _public member_ `DirInfo* dirInfo = nullptr;`
- L50 _public member_ `u32 refCount = 1;`
- L51 _public member_ `u32 closeId = 0;`
- L52 _public member_ `u32 desiredAccess = 0;`
- L53 _public member_ `bool deleteOnClose = false;`
- L54 _public member_ `bool ownsFileInfo = false;`
- L55 _public member_ `bool isDirectory = false;`
- L56 _public member_ `TString newName;`

#### struct `uba::DetouredHandle`  
`struct DetouredHandle`  
_L59-63_
- L61 _public member_ `FileObject* fileObject = nullptr;`
- L62 _public member_ `bool hasCloexec = false;` — Per-fd (kernel auto-closes at execve); skipped by Shared_BuildInheritedHandlesEnv so reused fd doesn't trip 'already added' assert.

#### enum `uba::SharedDeleteAction`  
`enum class SharedDeleteAction`  
_L100-105_
- L102 _public enumerator_ `Passthrough`
- L103 _public enumerator_ `Error`
- L104 _public enumerator_ `Success`

#### enum `uba::SharedReadlinkAction`  
`enum class SharedReadlinkAction`  
_L145-150_
- L147 _public enumerator_ `Passthrough`
- L148 _public enumerator_ `Synthesized`
- L149 _public enumerator_ `Error`

#### enum `uba::SharedOpenAction`  
`enum class SharedOpenAction`  
_L154-162_
- L156 _public enumerator_ `Error`
- L157 _public enumerator_ `NoDetourFallback`
- L158 _public enumerator_ `ProcFallback`
- L159 _public enumerator_ `DirectoryFd`
- L160 _public enumerator_ `UnsupportedFail`
- L161 _public enumerator_ `NormalOpen`

#### struct `uba::SharedOpenPrep`  
`struct SharedOpenPrep`  
_L164-181_
- L166 _public member_ `SharedOpenAction action = SharedOpenAction::Error;`
- L167 _public member_ `StringBuffer<> fileName;`
- L168 _public member_ `StringKey fileNameKey;`
- L169 _public member_ `u32 desiredAccess = 0;`
- L170 _public member_ `bool isWrite = false;`
- L171 _public member_ `DirectoryTableEntryInformation entryInfo;`
- L172 _public member_ `bool fileExists = false;`
- L173 _public member_ `int err = 0;`
- L174 _public member_ `const char* tempFileName = nullptr;`
- L175 _public member_ `int trueFlags = 0;`
- L176 _public member_ `int trueMode = 0;`
- L177 _public member_ `Vector<u8> dataToWrite;`
- L178 _public member_ `bool isDirectoryEntry = false;`
- L179 _public member_ `FileInfo* fileInfo = nullptr;`
- L180 _public member_ `u32 closeId = 0;`

#### struct `uba::ProcessCreator`  
`struct ProcessCreator`  
_L200-222_
- L202 _public prototype_ `int SendMessage(MessageType messageType, const char* messageName, Timer& messageTimer, const char* path, char* const argv[], char* const envp[], bool fixupPath, bool isExec);`
- L204 _public member_ `TString virtualApplication;`
- L205 _public member_ `TString realApplication;`
- L206 _public member_ `TString cmdLineWithoutApplication;`
- L207 _public member_ `u32 processId = 0;`
- L208 _public member_ `TString currentDir;`
- L209 _public member_ `TString comIdVar;`
- L210 _public member_ `TString rulesStr;`
- L211 _public member_ `TString logFile;`
- L212 _public member_ `TString ldLibraryPath;`
- L213 _public member_ `TString sessionProcess;`
- L214 _public member_ `TString tmpDir;`
- L216 _public member_ `TString pidVar;`
- L218 _public member_ `StringBuffer<> result;`
- L219 _public member_ `Vector<const char*> tempArgv;`
- L220 _public member_ `char* const* fixedArgv;`
- L221 _public member_ `Vector<const char*> envvars;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define UBA_IS_DETOURED_INCLUDE 1`
- L20 _namespace_ `namespace uba`
- L23 _prototype_ `u8 GetFileAccessFlags(int flags);` (scope `uba`) — Defined in UbaDetoursFunctionsPosix.cpp (LD_PRELOAD) / UbaStaticStubCore.cpp (stub).
- L24 _prototype_ `StringKey ToFilenameKey(const StringBufferBase& b);` (scope `uba`)
- L25 _prototype_ `StringKey ToFilenameKey(StringView b);` (scope `uba`)
- L27 _externvar_ `extern bool g_isDetouring;` (scope `uba`)
- L28 _externvar_ `extern bool g_isUsingLocalBinary;` (scope `uba`)
- L32 _externvar_ `extern u32 g_virtualUid;` (scope `uba`) — Virtual UID/GID reported to detoured processes — constant across local + remote so dirtable paths like /run/user/<UID> resolve consistently (kernel UID differs: WSL=1000, AL2025=990). Kernel-truth is fetched inline via raw syscall where actually needed (gid_map for userns setup).
- L33 _externvar_ `extern u32 g_virtualGid;` (scope `uba`)
- L43 _function_ `inline bool IsDirInfo(DIR* dir)` (scope `uba`)
- L44 _function_ `inline DirInfo* AsDirInfo(DIR* dir)` (scope `uba`)
- L65 _typedef_ `using FileHandles = UnorderedMap<int, DetouredHandle>;` (scope `uba`)
- L68 _prototype_ `void* g_fileHandlesStorage();` (scope `uba`)
- L69 _prototype_ `void* g_fileHandlesLockStorage();` (scope `uba`)
- L70 _macro_ `#define g_fileHandles (*static_cast<::uba::FileHandles*>(::uba::g_fileHandlesStorage()))`
- L71 _macro_ `#define g_fileHandlesLock (*static_cast<::uba::ReaderWriterLock*>(::uba::g_fileHandlesLockStorage()))`
- L73 _externvar_ `extern FileHandles& g_fileHandles;` (scope `uba`)
- L74 _externvar_ `extern ReaderWriterLock& g_fileHandlesLock;` (scope `uba`)
- L77 _prototype_ `void InitFileHandles();` (scope `uba`)
- L80 _prototype_ `const char* ResolvePath(int dirfd, const char* pathname, StringBufferBase& temp);` (scope `uba`) — Returns absolute path; nullptr if dirfd has no g_fileHandles entry (caller passthroughs).
- L83 _prototype_ `const char* ResolveProcSelfFd(const char* pathname);` (scope `uba`) — "/proc/self/fd/<N>" → tracked originalName, else returns pathname unchanged.
- L85 _prototype_ `int Shared_chdir(const char* func, const char* path, int& error);` (scope `uba`)
- L86 _prototype_ `int Shared_fchdir(int fd, int& error);` (scope `uba`)
- L87 _prototype_ `const char* StrError(int res, int error);` (scope `uba`)
- L91 _prototype_ `DetouredHandle& CreateFileTableEntry(int fd, const SharedOpenPrep& prep, bool isDirectory, const char* funcName, const char* hint);` (scope `uba`)
- L95 _prototype_ `template<typename TrueOpen> int CreateDirFd(const SharedOpenPrep& prep, int flags, const char* funcName, const TrueOpen& trueOpen);` (scope `uba`) — Synthesizes a UBA-tracked directory fd via trueOpen("/dev/null"); getdents64 → Shared_getdents64; close → Shared_close.
- L98 _prototype_ `long Shared_getdents64(const char* funcName, int fd, void* buf, unsigned int count, int* outErrno);` (scope `uba`) — Returns: >0 bytes written, 0 EOS, -1 untracked-passthrough. EINVAL when buffer too small for one entry.
- L108 _prototype_ `SharedDeleteAction Shared_prepareDelete(const char* funcName, const char* pathname, int& error, StringBufferBase& fixedNameOut);` (scope `uba`) — Passthrough callers MUST use fixedNameOut (FixPath'd absolute) — process cwd may not match g_virtualWorkingDir.
- L111 _prototype_ `template<typename TrueUnlink> int Shared_deleteFile(const char* funcName, const char* pathname, int& error, const TrueUnlink& trueUnlink);` (scope `uba`)
- L114 _prototype_ `template<typename TrueRmdir> int Shared_rmdir(const char* funcName, const char* path, int& error, const TrueRmdir& trueRmdir);` (scope `uba`)
- L117 _prototype_ `template<typename TrueMkdir> int Shared_mkdir(const char* funcName, const char* path, mode_t mode, int& error, const TrueMkdir& trueMkdir);` (scope `uba`)
- L121 _prototype_ `template<typename TrueRename> int Shared_rename(const char* func, const char* oldpath, const char* newpath, int& error, const TrueRename& trueRename);` (scope `uba`) — Shared code MUST NOT touch glibc errno directly (Go M-thread FS-register issue) — use the int& error out-param.
- L125 _prototype_ `template<typename TrueChmod> int Shared_chmod(const char* funcName, const char* pathname, mode_t mode, int& error, const TrueChmod& trueChmod);` (scope `uba`) — chmod / fchmodat(AT_FDCWD). Tracked writes go through SessionClient::Chmod (overlay-only); trueChmod only fires when !CanDetour2.
- L128 _prototype_ `void Shared_BuildInheritedHandlesEnv(StringBufferBase& out);` (scope `uba`) — Encode g_fileHandles entries with closeId != 0 into "UBA_INHERIT_HANDLES=<fd>:<closeId>:<pathLen>:<path>;…"; out.count = 0 if none.
- L132 _prototype_ `template<typename TrueGetenv> u32 Shared_AdoptInheritedHandles(const TrueGetenv& trueGetenv);` (scope `uba`) — Adopts UBA_INHERIT_HANDLES via getenv lambda; allocates FileObject{closeId, fileInfo, refCount=1} per entry. Returns count adopted.
- L135 _prototype_ `void DuplicateFd(int oldFd, int newFd, bool newCloexec);` (scope `uba`) — Increments FileObject::refCount so Shared_close waits for ALL fds to close before sending Rpc_UpdateCloseHandle.
- L139 _prototype_ `template<typename TrueClose, typename TrueSnapshot> int Shared_close(const char* funcName, int fd, const TrueClose& trueClose, const TrueSnapshot& trueSnapshot);` (scope `uba`) — Refcounted close. trueSnapshot must do dup→fstat→close so we measure the file AFTER stdio buffers flush.
- L143 _prototype_ `template<typename TrueSnapshot> void Shared_PreFinalizeForOverwrite(const char* funcName, int fd, const TrueSnapshot& trueSnapshot);` (scope `uba`) — Pre-finalize a tracked write fd before a syscall that implicitly closes it (dup2/dup3 with newfd open). See .inl for rationale.
- L152 _prototype_ `SharedReadlinkAction Shared_prepareReadlink(const char* funcName, const char* pathname, char* buf, u64 bufsiz, u64& outLen, int& error);` (scope `uba`)
- L184 _prototype_ `template<typename TrueOpen> void Shared_prepareOpen(const char* funcName, const char* file, int flags, int mode, const TrueOpen& trueOpen, SharedOpenPrep& prep);` (scope `uba`)
- L187 _prototype_ `template<typename TrueOpen> int Shared_open(const char* funcName, const char* file, int flags, int mode, const TrueOpen& trueOpen);` (scope `uba`)
- L190 _function_ `inline const char* EnvLookup(const char* const* envp, const char* keyEquals)` (scope `uba`) — keyEquals MUST include the trailing '=' (e.g. "TMPDIR=").
- L226 _prototype_ `template<typename TrueExecve, typename TrueNanosleepUs, typename TrueSnapshot> int Shared_Internal_exec(const char* func, const char* pathname, char* const argv[], char* const envp[], bool fixupPath, const TrueExecve& trueExecve, const TrueNanosleepUs& trueNanosleepUs, const TrueSnapshot& trueSnapshot);` (scope `uba`) — Returns 0 on success (unreachable in practice) or -errno on failure.
- L233 _prototype_ `u32 GetHostPidFromPidfd(int pidfd);` (scope `uba`) — PID-NS-aware fork helpers. Inside a non-init NS, getpid() returns NS-local pid the host can't waitpid() — gated by g_parentInNonInitNs. Real_fork / Real_getpid / Real_clone3_pidfd / Real_prctl_pdeathsig live inline in UbaDetoursRealPosix.h.
- L234 _prototype_ `bool CheckParentInNonInitPidNs();` (scope `uba`) — true iff /proc/self/status NSpid: line has >1 value
- L235 _externvar_ `extern bool g_parentInNonInitNs;` (scope `uba`)
- L237 _externvar_ `extern int g_comFd;` (scope `uba`)
- L238 _externvar_ `extern u8* g_messageMappingMem;` (scope `uba`)
- L240 _externvar_ `extern SharedEvent* g_cancelEvent;` (scope `uba`)
- L241 _externvar_ `extern SharedEvent* g_readEvent;` (scope `uba`)
- L242 _externvar_ `extern SharedEvent* g_writeEvent;` (scope `uba`)
- L243 _externvar_ `extern int g_sessionPid;` (scope `uba`)
- L244 _externvar_ `extern bool g_isCancelled;` (scope `uba`)
- L246 _prototype_ `void SendStartProcess(u32 processId, u32 pid, bool success, u32 res);` (scope `uba`)
- L247 _prototype_ `void Shared_SendExit(u32 exitCode);` (scope `uba`)
- L251 _prototype_ `void Shared_Init(char** envp);` (scope `uba`) — MessageType_Init send + parse + post-init (table mappings, DirectoryTable adopt, env adoption). Driver for both LD_PRELOAD and the static stub. envp is used only on stub (no libc getenv); LD_PRELOAD passes ::environ but the implementation prefers libc getenv directly.
- L257 _prototype_ `DirectoryTable* StubAllocDirectoryTable(MemoryBlock& mb);` (scope `uba`) — Stub-side placement-new into VariableMem (we have no operator new). Defined in UbaStaticStubCore.cpp.
- L260 _prototype_ `pid_t Shared_fork();` (scope `uba`)
- L264 _prototype_ `bool CanDetour2(uba::StringView file);` — Global scope: callers in UbaDetoursFunctionsPosix.cpp use unqualified name.

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/PosixOS/UbaDetoursSharedPosix.inl` (Private)


#### Free symbols / members of external scopes

- L33 _namespace_ `namespace uba`
- L40 _function_ `inline StringBuffer<256> OpenFlagsToString(int flags)` (scope `uba`)
- L43 _function_ `auto append = [&](const char* s)` (scope `uba::OpenFlagsToString`)
- L73 _function_ `template<typename TrueOpen> void Shared_prepareOpen(const char* funcName, const char* file, int flags, int mode, const TrueOpen& trueOpen, SharedOpenPrep& prep)` (scope `uba`) — See UbaDetoursSharedPosix.h for the contract. The body lives here so both LD_PRELOAD and the static stub instantiate identical code (same FixPath / CanDetour2 / Rpc_GetEntryOffset / Rpc_CreateFileW / dirtable lookups / DEBUG_LOG_DETOURED entries).
- L358 _function_ `` (scope `uba::Shared_prepareOpen`)
- L418 _function_ `template<typename TrueUnlink> int Shared_deleteFile(const char* funcName, const char* pathname, int& error, const TrueUnlink& trueUnlink)` (scope `uba`)
- L456 _function_ `template<typename RegisterFd> inline void Shared_postOpenSuccess(int fd, const SharedOpenPrep& prep, const RegisterFd& registerFd)` (scope `uba`) — Both the LD_PRELOAD path (Shared_open below) and the static stub's SYS_nr_openat handler (DetoursStatic/UbaStaticStubCore.cpp) MUST run the same sequence after a successful open through UBA. Centralising these helpers stops the two paths from drifting (read-fd tracking, missing Rpc_RegisterFileForWrite, missing TrackInput on NoDetourFallback — each of those was a separate session of debugging because the stub had re-implemented Shared_open's switch and quietly missed an invariant). `registerFd` is the ONE thing that legitimately differs: LD_PRELOAD inserts into g_fileHandles via CreateFileTableEntry (FileObject layout), the stub uses its own freestanding fd_table_insert. Everything else (TrackInput, dataToWrite preload gated by UBA_STUB_BUILD, Rpc_RegisterFileForWrite) is identical and lives here. See ClaudeNotes/03-detour-invariants.md rule 1 for why every fd from a path-based open MUST be tracked, even read fds.
- L498 _function_ `inline void Shared_postNoDetourFallback(int res, const SharedOpenPrep& prep)` (scope `uba`) — Shared post-NoDetourFallback helper — when a path falls outside UBA's detour scope (CanDetour2 returned false), we still need to record that this process touched it as input. The stub previously skipped this and it was a latent divergence waiting to surface.
- L505 _function_ `template<typename TrueOpen> int CreateDirFd(const SharedOpenPrep& prep, int flags, const char* funcName, const TrueOpen& trueOpen)` (scope `uba`)
- L550 _function_ `template<typename TrueOpen, typename RegisterFd> int Shared_open(const char* funcName, const char* file, int flags, int mode, int& error, const TrueOpen& trueOpen, const RegisterFd& registerFd)` (scope `uba`) — Out-param `error` is set to the kernel-style errno value when the return is -1 (Error / failed trueOpen). Caller surfaces it: LD_PRELOAD passes glibc's `errno` directly so the assignment lands in the right TLS slot; the stub passes a local int and translates the result back into the kernel-style negative return that raw_syscall6 callers expect. Shared code MUST NOT touch glibc errno directly — in patched Go binaries the FS register points at Go's M-struct, not a glibc TCB, and __errno_location() returns a wrong address that would corrupt the runtime.
- L644 _function_ `template<typename TrueOpen> inline int Shared_open(const char* funcName, const char* file, int flags, int mode, const TrueOpen& trueOpen)` (scope `uba`) — Convenience overload: defaults to CreateFileTableEntry (g_fileHandles + FileObject layout) and uses glibc-style `errno` as the error out-param. Same on LD_PRELOAD and stub — both have __errno_location (stub provides it via UbaStaticStubCore.cpp's import-slot wrapper).
- L648 _function_ `` (scope `uba::Shared_open`)
- L654 _function_ `template<typename True_stat> int Shared_stat(const char* funcName, const char* file, struct stat* attr, const True_stat& trueStat, bool followSymlink = true)` (scope `uba`)
- L810 _function_ `template<typename TrueRmdir> int Shared_rmdir(const char* funcName, const char* path, int& error, const TrueRmdir& trueRmdir)` (scope `uba`) — Shared_rmdir — see header for the contract. Out-param `error` is set to the kernel-style errno value on -1 returns. Caller is responsible for surfacing it (via glibc errno on the LD_PRELOAD side, or by writing it into saved[]/argregs on the static-stub side where glibc errno TLS may not be available in patched Go binaries).
- L927 _function_ `template<typename TrueMkdir> int Shared_mkdir(const char* funcName, const char* path, mode_t mode, int& error, const TrueMkdir& trueMkdir)` (scope `uba`) — Shared_mkdir — see header for the contract. Out-param `error` is set to the kernel-style errno value on -1 returns. Same rationale as Shared_rmdir: the static stub's caller can't rely on the glibc errno TLS in patched Go binaries, so we surface the error explicitly via the out-param. Caller writes it into glibc's errno (LD_PRELOAD path) or saved[]/argregs (stub path).
- L1052 _function_ `template<typename TrueRename> int Shared_rename(const char* func, const char* oldpath, const char* newpath, int& error, const TrueRename& trueRename)` (scope `uba`) — Shared_rename — see header for the contract. Body lifted verbatim from the LD_PRELOAD original (UbaDetoursFunctionsPosix.cpp's Shared_rename). Only difference: TRUE_WRAPPER(rename)(o, n) becomes trueRename(o, n) so the static stub can plug in raw_syscall6(SYS_nr_renameat, AT_FDCWD, o, AT_FDCWD, n, …). The original body had an inner `UBA_INIT_DETOUR(rename, oldpath, newpath)` guard at the top. That guard was redundant: every caller of Shared_rename (UBA_WRAPPER(rename), renameat, renameat2) already does UBA_INIT_DETOUR for ITS OWN syscall name at entry, so by the time control reaches here we already know g_isDetouring && !DisallowDetourDepth(). Removed because the .inl is also instantiated from UbaDetoursSharedPosix.cpp (a separate TU that doesn't include the LD_PRELOAD-only UBA_INIT_DETOUR macro). Behavior is preserved — the guard never fired in practice.
- L1240 _function_ `template<typename TrueChmod> int Shared_chmod(const char* funcName, const char* pathname, mode_t mode, int& error, const TrueChmod& trueChmod)` (scope `uba`)
- L1308 _function_ `template<typename TrueSnapshot> void FlushWriteHandlesBeforeExec(const char* funcName, const TrueSnapshot& trueSnapshot)` (scope `uba`) — FlushWriteHandlesBeforeExec — called from Shared_Internal_exec. Without this pass, an fd opened for write in this process (typical bash redirect: child opens /sandbox/out/foo.java O_WRONLY|O_CREAT before execve'ing the producer) leaves m_activeFiles[closeId] live on the host with contentSize=InvalidValue (= 0x7ffffffff = 34359738367). The execve replaces our memory and the new program's fresh stub has no record of these fds, so Rpc_UpdateCloseHandle is never sent and the InvalidValue placeholder leaks into DIRTABLE forever. Walk g_fileHandles, snapshot each write-tracked fd's current size via the caller's trueSnapshot lambda, and fire Rpc_UpdateCloseHandle so the host clears the placeholder. The kernel fd remains open across execve (we don't close it here); whatever the new program writes goes to disk, but UBA's tracking is "the file was closed at this size". That's still wrong for redirects (snapshot is taken before the producer runs, so size will typically be 0), but it eliminates the 34GB ghosts that confuse downstream directory walks. Stage 2 will transfer ownership across execve so post-exec writes are accounted.
- L1362 _function_ `template<typename TrueSnapshot> inline void Shared_PreFinalizeForOverwrite(const char* funcName, int fd, const TrueSnapshot& trueSnapshot)` (scope `uba`) — Finalize tracked write fd before a syscall that implicitly closes it (dup2/dup3 with newfd open). Snapshots while fd still points at the tracked file, then Shared_close drops the entry. Repro: bash redirect-with-restore (`dup2(file,1); fork; wait; dup2(saved,1)`).
- L1378 _function_ `Shared_close(funcName, fd, []() { return 0; }, trueSnapshot);` (scope `uba::Shared_PreFinalizeForOverwrite`)
- L1413 _function_ `inline void Shared_BuildInheritedHandlesEnv(StringBufferBase& out)` (scope `uba`)
- L1447 _function_ `template<typename TrueGetenv> u32 Shared_AdoptInheritedHandles(const TrueGetenv& trueGetenv)` (scope `uba`) — Adopt UBA_INHERIT_HANDLES from env on detour init. Caller passes a libc-style getenv lambda; LD_PRELOAD uses ::getenv, the stub uses an envp-scan helper. Returns the number of entries adopted.
- L1475 _function_ `` (scope `uba::Shared_AdoptInheritedHandles`)
- L1559 _prototype_ `void Shared_BuildVfsEnv(StringBufferBase& out);` (scope `uba`) — UBA_VFS_OVERLAYS: propagate g_vfsEntries across execve (bind mounts + chroot/pivot_root). Format: <vfsLen>:<vfs>:<localLen>:<local>;... (length-prefixed).
- L1562 _function_ `template<typename TrueGetenv> u32 Shared_AdoptVfsEntries(const TrueGetenv& trueGetenv)` (scope `uba`)
- L1588 _function_ `` (scope `uba::Shared_AdoptVfsEntries`)
- L1628 _function_ `template<typename TrueGetenv> u32 Shared_AdoptPassThroughRoots(const TrueGetenv& trueGetenv)` (scope `uba`) — Adopt UBA_PASSTHROUGH_ROOTS — paths registered by parent's Shared_mount fstype branch.
- L1653 _function_ `` (scope `uba::Shared_AdoptPassThroughRoots`)
- L1687 _function_ `template<typename TrueExecve, typename TrueNanosleepUs, typename TrueSnapshot> int Shared_Internal_exec(const char* func, const char* pathname, char* const argv[], char* const envp[], bool fixupPath, const TrueExecve& trueExecve, const TrueNanosleepUs& trueNanosleepUs, const TrueSnapshot& trueSnapshot)` (scope `uba`) — Shared_Internal_exec — see header for the contract. Both LD_PRELOAD's Internal_exec and the stub's SYS_execve handler instantiate this with their own execve / nanosleep / snapshot lambdas. Builds the UBA_INHERIT_HANDLES env var (see Shared_BuildInheritedHandlesEnv above) just before trueExecve so the post-execve program can adopt our open- for-write fds.
- L1766 _function_ `inline void DuplicateFd(int oldFd, int newFd, bool newCloexec)` (scope `uba`) — DuplicateFd — see header for the contract. newCloexec reflects the FD_CLOEXEC bit on the *new* fd: dup / dup2 / F_DUPFD  -> false (kernel clears CLOEXEC); dup3(O_CLOEXEC) / F_DUPFD_CLOEXEC -> true.
- L1785 _function_ `template<typename TrueClose, typename TrueSnapshot> int Shared_close(const char* funcName, int fd, const TrueClose& trueClose, const TrueSnapshot& trueSnapshot)` (scope `uba`) — Shared_close — see header for the contract. The body lives here so LD_PRELOAD and the static stub instantiate the same refcounting + Rpc_UpdateCloseHandle logic; only the syscall mechanics (close + the dup/fstat/close-of-dup snapshot) come from the caller's lambdas.
- L1788 _function_ `` (scope `uba::Shared_close`)
- L1814 _function_ `auto dg = MakeGuard([fo]() { delete fo->dirInfo; delete fo; });` (scope `uba::Shared_close`)
- L1860 _function_ `inline void SynthStatFromEntry(struct stat* sbOut, const DirectoryTable::EntryInformation& info)` (scope `uba`) — SynthStatFromEntry / SharedStatPath — fill caller's `struct stat` from the dirtable. Shared by GlibcStat/Lstat/Fstatat (UbaGlibc.cpp) and the SYS_newfstatat/statx dispatcher arms (UbaStaticStubCore.cpp). Real_fstatat is used for kernel passthrough on the pre-init / NODETOUR branches; the dirtable hit synthesizes locally without a syscall.
- L1884 _function_ `inline int Shared_unlinkat(const char* funcName, int dirfd, const char* path, int flags)` (scope `uba`)
- L1894 _function_ `? Shared_rmdir (funcName, resolved, err, [](const char* p) { return Real_rmdir (errno, p); }) : Shared_deleteFile(funcName, resolved, err, [](const char* p) { return Real_unlink(errno, p); });` (scope `uba::Shared_unlinkat`)
- L1895 _function_ `: Shared_deleteFile(funcName, resolved, err, [](const char* p) { return Real_unlink(errno, p); });` (scope `uba::Shared_unlinkat`)
- L1900 _function_ `inline int Shared_renameat(const char* funcName, int olddirfd, const char* oldpath, int newdirfd, const char* newpath)` (scope `uba`)
- L1909 _function_ `int rc = Shared_rename(funcName, resolvedOld, resolvedNew, err, [](const char* o, const char* n) { return Real_rename(errno, o, n); });` (scope `uba::Shared_renameat`)
- L1914 _function_ `inline int Shared_mkdirat(const char* funcName, int dirfd, const char* path, mode_t mode)` (scope `uba`)
- L1924 _function_ `int rc = Shared_mkdir(funcName, resolved, mode, err, [](const char* p, unsigned int m) { return Real_mkdir(errno, p, m); });` (scope `uba::Shared_mkdirat`)
- L1931 _function_ `inline int Shared_faccessat(const char* funcName, int dirfd, const char* path, int mode, int flags)` (scope `uba`) — Shared_faccessat — DIRTABLE-driven existence check. Returns 0 if dirtable says exists, -1+ENOENT if dirtable says no, or kernel passthrough for unresolvable/non-detourable paths.
- L1959 _function_ `inline void SharedStatxFromEntry(struct ::statx* sxOut, const DirectoryTable::EntryInformation& info)` (scope `uba`) — Mirror of SynthStatFromEntry for struct statx. Used by SYS_nr_statx dispatcher arm. Same DIRTABLE→struct conversion path keeps stat() and statx() consistent for the same entry.
- L1978 _function_ `inline int Shared_statx(const char* funcName, int dirfd, const char* path, int flags, unsigned int mask, struct ::statx* sxOut)` (scope `uba`)
- L2008 _function_ `inline int SharedStatPath(const char* funcName, const char* path, struct stat* sbOut, bool followSymlink)` (scope `uba`) — followSymlink unused — Rpc_GetEntryInformation resolves chains. Kept for symmetry with libc API.

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/PosixOS/UbaDetoursTrueWrappersPosix.h` (Private)


#### Free symbols / members of external scopes

- L32 _macro_ `#define UBA_WRAPPER(func) uba_##func`
- L33 _macro_ `#define TRUE_WRAPPER(func) func`
- L36 _macro_ `#define DYLD_INTERPOSE(_replacement,_replacee) \`
- L41 _macro_ `#define UBA_WRAPPER(func) func`
- L42 _macro_ `#define TRUE_WRAPPER(func) True_##func`
- L45 _prototype_ `extern "C" int __open_2(const char* pathname, int flags)` — _FORTIFY_SOURCE-rewrite targets: no public header declares __open_2 et al., but DETOURED_FUNCTION's decltype needs them.
- L46 _prototype_ `extern "C" int __openat_2(int dirfd, const char* pathname, int flags)`
- L47 _prototype_ `extern "C" int __open64_2(const char* pathname, int flags)`
- L48 _prototype_ `extern "C" int __openat64_2(int dirfd, const char* pathname, int flags)`
- L49 _prototype_ `extern "C" int pivot_root(const char* new_root, const char* put_old)` — no glibc header declares it
- L53 _macro_ `#define UBA_DETOUR_DEBUG 0`
- L57 _macro_ `#define DETOURED_FUNCTION_DEBUG \`
- L62 _macro_ `#define DETOURED_FUNCTION_DEBUG`
- L66 _macro_ `#define DETOURED_FUNCTION_MACOS`
- L67 _macro_ `#define DETOURED_FUNCTION_LINUX \`
- L118 _macro_ `#define DETOURED_FUNCTION_LINUX`
- L119 _macro_ `#define DETOURED_FUNCTION_MACOS \`
- L125 _macro_ `#define DETOURED_FUNCTIONS \`
- L219 _macro_ `#define DETOURED_FUNCTION(func) \` — Type aliases + extern storage decls. Storage itself is defined once in UbaDetoursFunctionsPosix.cpp.
- L225 _namespace_ `namespace uba`
- L228 _function_ `template<typename TrueFunc> inline void InitDetour(TrueFunc*& trueFunc, const char* func)` (scope `uba`)
- L238 _macro_ `#define UBA_INIT_DETOUR(func, ...) \`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/UbaDetoursFileMappingTable.h` (Private)


#### struct `uba::FileInfo`  
`struct FileInfo`  
_L17-72_
- L20 _public member_ `u64 size = InvalidValue;` — Size of file. Can be different than what Directory table says (For example for decompressed obj files)
- L23 _public member_ `StringKey fileNameKey;` — Key of fixed up file name
- L26 _public member_ `const tchar* name = nullptr;` — "Real" name of file. Can also be ids/handles to memory buffers etc
- L29 _public member_ `const tchar* originalName = nullptr;` — Original name of file as the detoured process sees it
- L32 _public member_ `MemoryFile* memoryFile = nullptr;` — Set if file is a memory file (writable, sharable across process hierarchies). isFileMap is false when set.
- L35 _public member_ `u32 lastDesiredAccess = 0;` — Holds previous file open access flags. Is used to figure out if file open is the first write
- L38 _public member_ `DirTableOffset lastSeenTableOffset;` — Last-seen offset in dirtable; if overlay has a newer one, Rpc_CheckRemapping is needed.
- L42 _public member_ `bool isFileMap = false;` — This is the Filemap handle and mapped view that represents the File HANDLE. It can be used for other mappings too but doesnt' have to.
- L45 _public member_ `bool freeFileMapOnClose = false;` — If this is true, fileMapMem will be deleted when
- L48 _public member_ `bool tracked = false;` — Is set to true once file has been tracked to prevent tracking same file multiple times
- L51 _public member_ `bool created = false;` — If set to true, this means file was created during process group lifetime (which means it has its own file id etc)
- L53 _public member_ `bool recursiveCall = false;`
- L56 _public member_ `SharedMemoryHandle trueFileMapHandle;` — File mapping handle coming from session process (Set in NtCreateFile)
- L59 _public member_ `u64 trueFileMapOffset = 0;` — Offset into trueFileMapHandle
- L62 _public member_ `u8* fileMapMem = nullptr;` — If file mapping is resolved, then this points to the memory. Is also used for compressed obj files
- L65 _public member_ `u64 fileMapMemSize = 0;` — Size of fileMapMem
- L68 _public member_ `u32 refCount = 0;`
- L69 _public member_ `u32 fileMapDesiredAccess = PAGE_READONLY;`
- L70 _public member_ `u32 fileMapViewDesiredAccess = FILE_MAP_READ;` — This is the parameter to MapViewOfFile

#### class `uba::MappedFileTable`  
`class MappedFileTable`  
_L74-93_
- L77 _public prototype_ `MappedFileTable(MemoryBlock& memoryBlock);`
- L79 _public prototype_ `void Init(const u8* mem, u32 tableCount, u32 tableSize);`
- L81 _public prototype_ `void ParseNoLock(u32 tableSize);`
- L82 _public prototype_ `void Parse(u32 tableSize);`
- L83 _public prototype_ `void SetDeleted(const StringKey& key, const tchar* name, bool deleted);`
- L85 _public member_ `MemoryBlock& m_memoryBlock;`
- L86 _public member_ `const u8* m_mem = 0;`
- L87 _public member_ `u32 m_memPosition = 0;`
- L88 _public member_ `ReaderWriterLock m_lookupLock;`
- L89 _public member_ `GrowingUnorderedMap<StringKey, FileInfo> m_lookup;`
- L90 _public member_ `Futex m_memLookupLock;`
- L92 _public member_ `UnorderedMap<const void*, Entry> m_memLookup;`

#### struct `uba::MappedFileTable::Entry`  
`struct Entry`  
_L91-91_
- L91 _public member_ `struct Entry { int refCount = 0; DetouredHandle* handle = nullptr; };`
- L91 _public member_ `struct Entry { int refCount = 0; DetouredHandle* handle = nullptr; };`

#### struct `uba::DirectoryTableEntryInformation`  
`struct DirectoryTableEntryInformation : DirectoryTable::EntryInformation`  
_L95-95_
- inherits: `DirectoryTable::EntryInformation`
- L95 _public member_ `struct DirectoryTableEntryInformation : DirectoryTable::EntryInformation { DirTableOffset dirTableOffset; };`

#### enum `uba::(anonymous)`  
`enum : u8`  
_L97-97_

#### struct `uba::DirHash`  
`struct DirHash`  
_L117-122_
- L119 _public prototype_ `DirHash(const StringView& str);`
- L120 _public member_ `StringKey key;`
- L121 _public member_ `StringKeyHasher open;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L97 _enumerator_ `enum : u8 { AccessFlag_Read = 1, AccessFlag_Write = 2 }; void Rpc_CreateFileW(const StringView& fileName, const StringKey& fileNameKey, u8 accessFlags, tchar* outNewName, u64 newNameCapacity, u64& outSize, u32& outCloseId, bool lock); void Rpc_RegisterFileForWrite(StringView fileName, const StringKey& fileNameKey); void Rpc_CheckRemapping(const StringView& fileName, const StringKey& fileNameKey); void Rpc_CheckRemapping2(StringBufferBase& out, StringKey fileNameKey); bool Rpc_UpdateDirectory(const StringKey& dirKey, const tchar* dirName, u64 dirNameLen, bool lockDirTable = true); void Rpc_UpdateCloseHandle(const tchar* handleName, u32 closeId, bool deleteOnClose, const tchar* newName, SharedMemoryHandle memoryHandle, u64 fileSize, u64 lastWriteTime, u32 attributes, bool success);` (scope `uba::__anond63469620103`)
- L97 _enumerator_ `enum : u8 { AccessFlag_Read = 1, AccessFlag_Write = 2 }; void Rpc_CreateFileW(const StringView& fileName, const StringKey& fileNameKey, u8 accessFlags, tchar* outNewName, u64 newNameCapacity, u64& outSize, u32& outCloseId, bool lock); void Rpc_RegisterFileForWrite(StringView fileName, const StringKey& fileNameKey); void Rpc_CheckRemapping(const StringView& fileName, const StringKey& fileNameKey); void Rpc_CheckRemapping2(StringBufferBase& out, StringKey fileNameKey); bool Rpc_UpdateDirectory(const StringKey& dirKey, const tchar* dirName, u64 dirNameLen, bool lockDirTable = true); void Rpc_UpdateCloseHandle(const tchar* handleName, u32 closeId, bool deleteOnClose, const tchar* newName, SharedMemoryHandle memoryHandle, u64 fileSize, u64 lastWriteTime, u32 attributes, bool success);` (scope `uba::__anond63469620103`)
- L99 _prototype_ `void Rpc_CreateFileW(const StringView& fileName, const StringKey& fileNameKey, u8 accessFlags, tchar* outNewName, u64 newNameCapacity, u64& outSize, u32& outCloseId, bool lock);` (scope `uba`)
- L100 _prototype_ `void Rpc_RegisterFileForWrite(StringView fileName, const StringKey& fileNameKey);` (scope `uba`)
- L101 _prototype_ `void Rpc_CheckRemapping(const StringView& fileName, const StringKey& fileNameKey);` (scope `uba`)
- L102 _prototype_ `void Rpc_CheckRemapping2(StringBufferBase& out, StringKey fileNameKey);` (scope `uba`)
- L103 _prototype_ `bool Rpc_UpdateDirectory(const StringKey& dirKey, const tchar* dirName, u64 dirNameLen, bool lockDirTable = true);` (scope `uba`)
- L104 _prototype_ `void Rpc_UpdateCloseHandle(const tchar* handleName, u32 closeId, bool deleteOnClose, const tchar* newName, SharedMemoryHandle memoryHandle, u64 fileSize, u64 lastWriteTime, u32 attributes, bool success);` (scope `uba`)
- L105 _prototype_ `void Rpc_UpdateTables();` (scope `uba`)
- L106 _prototype_ `bool Rpc_GetEntryOffset(DirTableOffset& out, const StringKey& entryNameKey, StringView entryName, bool checkIfDir = false);` (scope `uba`)
- L107 _prototype_ `bool Rpc_GetEntryInformation(DirectoryTableEntryInformation& out, StringKey entryNameKey, StringView entryName, bool checkIfDir = false, bool followSymlink = true, StringBufferBase* outResolvedPath = nullptr, StringKey* outResolvedKey = nullptr);` (scope `uba`)
- L108 _prototype_ `void Rpc_GetFullFileName(const tchar*& path, u64& pathLen, StringBufferBase& tempBuf, bool useVirtualName, const tchar* const* loaderPaths = nullptr);` (scope `uba`)
- L109 _prototype_ `void Rpc_GetFullFileName2(const tchar* path, StringBufferBase& outReal, StringBufferBase& outVirtual, const tchar* const* loaderPaths = nullptr);` (scope `uba`)
- L110 _prototype_ `void Rpc_GetWrittenFiles();` (scope `uba`)
- L112 _prototype_ `SharedMemoryHandle Rpc_CreateSharedMemory(SharedMemoryView& out, SharedMemoryAllocatorHandle allocatorHandle, u64 capacity, u64 initialSize, const tchar* hint);` (scope `uba`)
- L113 _prototype_ `void Rpc_CommitSharedMemory(SharedMemoryView& view, SharedMemoryAllocatorHandle allocatorHandle, SharedMemoryHandle handle, u64 size);` (scope `uba`)
- L114 _prototype_ `void Rpc_GetSharedMemory(SharedMemoryView& view, SharedMemoryAllocatorHandle allocatorHandle, u8* allocatorMem, SharedMemoryHandle handle, u64 offset, u64 size, const tchar* hint, SharedMemoryMapType type = SharedMemoryMapType_ReadOnly);` (scope `uba`)
- L115 _prototype_ `void Rpc_UpdateSharedMemory(SharedMemoryView& view, SharedMemoryAllocatorHandle allocatorHandle, SharedMemoryHandle handle, u64 capacity);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/UbaDetoursShared.h` (Private)


#### struct `uba::SuppressDetourScope`  
`struct SuppressDetourScope`  
_L98-102_
- L100 _public prototype_ `SuppressDetourScope();`
- L101 _public prototype_ `~SuppressDetourScope();`

#### struct `uba::LogScope`  
`struct LogScope`  
_L112-112_
- L112 _public prototype_ `struct LogScope`
- L112 _public prototype_ `struct LogScope`
- L112 _public prototype_ `struct LogScope`

#### struct `uba::FileAttributes`  
`struct FileAttributes`  
_L150-157_
- L152 _public member_ `FileAttributesData data;`
- L153 _public member_ `u64 fileIndex;`
- L154 _public member_ `u32 volumeSerial;`
- L155 _public member_ `u8 exists;`
- L156 _public member_ `u32 lastError;`

#### struct `uba::VariableMem`  
`template<typename T> struct VariableMem`  
_L173-173_
- L173 _public function_ `template<typename T> struct VariableMem`
- L173 _public member_ `template<typename T> struct VariableMem { template<typename... Args> void Create(Args&&... args) { new (data) T(args...); }; u64 data[AlignUp(sizeof(T), sizeof(u64)) / sizeof(u64)]; };`

#### enum `uba::LogEntryType`  
`enum LogEntryType : u8`  
_L244-244_
- desc: Dummy code
- L244 _public enumerator_ `enum LogEntryType : u8 { LogEntryType_Error = 0, LogEntryType_Warning = 1, }; class Logger { public: void Logf(...) {} void Info(...) {} bool Warning(...) { return false; } bool Error(...) { return false; } };` — Dummy code
- L244 _public enumerator_ `enum LogEntryType : u8 { LogEntryType_Error = 0, LogEntryType_Warning = 1, }; class Logger { public: void Logf(...) {} void Info(...) {} bool Warning(...) { return false; } bool Error(...) { return false; } };` — Dummy code

#### class `uba::Logger`  
`class Logger`  
_L245-245_
- L245 _public function_ `class Logger`
- L245 _public function_ `class Logger`
- L245 _public function_ `class Logger`
- L245 _public function_ `class Logger`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace uba`
- L26 _prototype_ `DWORD Local_GetLongPathNameW(LPCWSTR lpszShortPath, LPWSTR lpszLongPath, DWORD cchBuffer);` (scope `uba`)
- L29 _prototype_ `void Rpc_WriteLog(const tchar* text, u64 textCharLength, bool printInSession, bool isError);` (scope `uba`)
- L30 _prototype_ `void Rpc_WriteLogf(const tchar* format, ...);` (scope `uba`)
- L31 _prototype_ `void Rpc_ResolveCallstack(StringBufferBase& out, u32 skipCallstackCount, void* context);` (scope `uba`)
- L33 _prototype_ `const tchar* GetApplicationShortName();` (scope `uba`)
- L34 _prototype_ `bool FixPath(StringBufferBase& out, const tchar* path, u32 pathLen = ~0u);` (scope `uba`)
- L35 _prototype_ `bool FixPath(StringBufferBase& out, const StringView path);` (scope `uba`)
- L37 _prototype_ `void PopulateVfs(BinaryReader& vfsReader);` (scope `uba`)
- L38 _prototype_ `bool IsVfsEnabled();` (scope `uba`)
- L39 _prototype_ `bool AddVfsEntry(StringView vfs, StringView local);` (scope `uba`) — vfs/local must be absolute FixPath'd paths
- L40 _prototype_ `bool AddVfsEntryBulkNoDedup(StringView vfs, StringView local);` (scope `uba`) — bulk fast path; caller MUST call FinalizeVfsEntriesAfterBulk()
- L41 _prototype_ `void FinalizeVfsEntriesAfterBulk();` (scope `uba`)
- L42 _prototype_ `bool RemoveVfsEntry(StringView vfs);` (scope `uba`)
- L43 _prototype_ `bool DevirtualizePath(StringBufferBase& path);` (scope `uba`)
- L44 _prototype_ `tchar DevirtualizeDrive(tchar drive);` (scope `uba`)
- L45 _prototype_ `bool VirtualizePath(StringBufferBase& path);` (scope `uba`)
- L46 _prototype_ `bool IsVfsParentDir(StringView path);` (scope `uba`) — True if path is an ancestor of any vfs entry; synthesizes "is a directory" for unbound bind-mount parents
- L47 _prototype_ `bool AddPassThroughRoot(StringView root);` (scope `uba`) — Roots + descendants bypass detour; used by tmpfs mounts the host DIRTABLE can't model
- L48 _prototype_ `bool IsUnderPassThroughRoot(StringView path);` (scope `uba`)
- L49 _prototype_ `u32 BuildPassThroughRootsEnvValue(tchar* outBuf, u32 outCap);` (scope `uba`) — Encode as "<len>:<path>;..."; returns bytes written
- L50 _prototype_ `void Shared_BuildPassThroughEnv(StringBufferBase& out);` (scope `uba`)
- L51 _prototype_ `void LogHeader(StringView cmdLine);` (scope `uba`)
- L52 _prototype_ `void LogVfsInfo();` (scope `uba`)
- L55 _macro_ `#define DEBUG_LOG_PREFIX(Prefix, Command, fmt, ...) \`
- L59 _macro_ `#define DEBUG_LOG_TRUE(Command, ...) DEBUG_LOG_PREFIX(T, Command, __VA_ARGS__)`
- L60 _macro_ `#define DEBUG_LOG_DETOURED(Command, ...) DEBUG_LOG_PREFIX(D, Command, __VA_ARGS__)`
- L61 _macro_ `#define DEBUG_LOG_PROXY(Command, ...) DEBUG_LOG_PREFIX(P, Command, __VA_ARGS__)`
- L62 _macro_ `#define DEBUG_LOG_PIPE(Command, ...) ts.Leave();`
- L63 _macro_ `#define DEBUG_LOG(fmt, ...) do { UBA_FMT_CHECK(fmt, ##__VA_ARGS__); if (::uba::isLogging()) ::uba::WriteDebugLog(fmt, ##__VA_ARGS__); } while(0)`
- L65 _macro_ `#define DEBUG_LOG(...) {}`
- L66 _macro_ `#define DEBUG_LOG_DETOURED(Command, ...) {}`
- L67 _macro_ `#define DEBUG_LOG_TRUE(Command, ...) {}`
- L68 _macro_ `#define DEBUG_LOG_PROXY(Command, ...) {}`
- L69 _macro_ `#define DEBUG_LOG_PIPE(...) ts.Leave();`
- L74 _externvar_ `extern StringBuffer<512>& g_virtualApplication;` (scope `uba`) — Normal build: each global is a reference backed by a pointer slot the dynamic linker fills in.
- L75 _externvar_ `extern StringBuffer<512>& g_virtualApplicationDir;` (scope `uba`)
- L76 _externvar_ `extern StringBuffer<256>& g_exeDir;` (scope `uba`)
- L77 _externvar_ `extern StringBuffer<512>& g_logName;` (scope `uba`)
- L79 _externvar_ `extern StringBuffer<512>& g_virtualWorkingDir;` (scope `uba`)
- L80 _externvar_ `extern StringBuffer<256>& g_systemTemp;` (scope `uba`)
- L81 _externvar_ `extern StringBuffer<128>& g_systemRoot;` (scope `uba`)
- L83 _externvar_ `extern ProcessStats& g_stats;` (scope `uba`)
- L84 _externvar_ `extern KernelStats& g_kernelStats;` (scope `uba`)
- L85 _externvar_ `extern Futex& g_communicationLock;` (scope `uba`)
- L86 _externvar_ `extern MemoryBlock& g_memoryBlock;` (scope `uba`)
- L87 _externvar_ `extern MappedFileTable& g_mappedFileTable;` (scope `uba`)
- L90 _externvar_ `extern bool g_conEnabled[2];` (scope `uba`) — Stub-build declarations follow further down (after VariableMem is defined).
- L94 _prototype_ `u32 DisallowDetourDepth();` (scope `uba`) — TLS-free per-thread suppression state. Goroutine OS threads created via clone() lack a glibc TCB, so thread_local access crashes them. Tracked via tiny open-addressed array keyed by OS tid.
- L95 _prototype_ `void DisallowDetourIncrement();` (scope `uba`)
- L96 _prototype_ `void DisallowDetourDecrement();` (scope `uba`)
- L105 _macro_ `#define t_disallowDetour uba::DisallowDetourDepth()` — Back-compat shim for existing `if (t_disallowDetour)` callsites.
- L108 _externvar_ `extern FileHandle g_debugFile;` (scope `uba`)
- L109 _externvar_ `extern Futex& g_debugLogMutex;` (scope `uba`)
- L110 _externvar_ `extern StringBuffer<MaxPath>& g_debugLogPath;` (scope `uba`)
- L111 _function_ `inline bool isLogging()` (scope `uba`)
- L113 _prototype_ `void WriteDebugLogWithPrefix(const char* prefix, LogScope& scope, const tchar* command, const tchar* format, ...);` (scope `uba`)
- L114 _prototype_ `void WriteDebugLog(const tchar* format, ...);` (scope `uba`)
- L115 _prototype_ `void WriteDebugInner(const void* data, u32 dataLen);` (scope `uba`) — Raw writer (platform-defined). Caller MUST hold g_debugLogMutex.
- L116 _prototype_ `void WriteDebug(const void* data, u32 dataLen);` (scope `uba`) — Locked public wrapper around WriteDebugInner.
- L117 _prototype_ `void FlushDebugLog();` (scope `uba`)
- L120 _externvar_ `extern bool g_validateFileAccess;` (scope `uba`)
- L123 _variable_ `inline constexpr bool g_allowDirectoryCache = true;` (scope `uba`)
- L124 _variable_ `inline constexpr bool g_allowFileMappingDetour = true;` (scope `uba`)
- L125 _variable_ `inline constexpr bool g_allowFindFileDetour = true;` (scope `uba`)
- L126 _variable_ `inline constexpr bool g_allowListDirectoryHandle = true;` (scope `uba`)
- L128 _externvar_ `extern DirectoryTable* g_directoryTable;` (scope `uba`)
- L129 _externvar_ `extern u32 g_processId;` (scope `uba`)
- L130 _externvar_ `extern u32 g_rulesIndex;` (scope `uba`)
- L131 _externvar_ `extern ApplicationRules* g_rules;` (scope `uba`)
- L132 _externvar_ `extern bool g_runningRemote;` (scope `uba`)
- L133 _externvar_ `extern bool g_isChild;` (scope `uba`)
- L134 _externvar_ `extern bool g_allowKeepFilesInMemory;` (scope `uba`)
- L135 _externvar_ `extern bool g_allowOutputFiles;` (scope `uba`)
- L136 _externvar_ `extern bool g_allowDiscardVirtualMemory;` (scope `uba`)
- L137 _externvar_ `extern bool g_suppressLogging;` (scope `uba`)
- L140 _variable_ `constexpr u32 ErrorSuccess = 0;` (scope `uba`)
- L141 _variable_ `constexpr u32 ErrorFileNotFound = ERROR_FILE_NOT_FOUND;` (scope `uba`)
- L142 _typedef_ `using FileAttributesData = WIN32_FILE_ATTRIBUTE_DATA;` (scope `uba`)
- L144 _typedef_ `using FileAttributesData = struct stat;` (scope `uba`)
- L146 _variable_ `constexpr u32 ErrorFileNotFound = ENOENT;` (scope `uba`)
- L159 _prototype_ `bool CouldBeCompressedFile(const StringView& fileName);` (scope `uba`)
- L161 _prototype_ `void Shared_WriteConsole(const char* chars, u32 charCount, bool isError);` (scope `uba`)
- L162 _prototype_ `void Shared_WriteConsole(const wchar_t* chars, u32 charCount, bool isError);` (scope `uba`)
- L164 _prototype_ `const tchar* Shared_GetFileAttributes(FileAttributes& outAttr, StringView fileName, bool followSymlink = true, bool checkIfDir = false);` (scope `uba`)
- L166 _prototype_ `void InitSharedVariables();` (scope `uba`)
- L167 _prototype_ `void InitTrackInput();` (scope `uba`)
- L168 _prototype_ `void TrackInput(StringView file);` (scope `uba`)
- L169 _prototype_ `void SkipTrackInput(StringView file);` (scope `uba`)
- L170 _prototype_ `bool IsTrackingInput();` (scope `uba`)
- L171 _prototype_ `void SendInput();` (scope `uba`)
- L177 _macro_ `#define VARIABLE_MEM(type, name) VariableMem<type> name##Mem;` — Stub build: emit storage only. The g_name macros below resolve through RIP-relative accessors — no pointer slots, so no R_X86_64_RELATIVE relocations the objcopied blob couldn't apply.
- L180 _prototype_ `void* g_virtualApplicationStorage();` (scope `uba`) — Untyped accessors so headers don't need the shared-globals' complete types in scope.
- L181 _prototype_ `void* g_virtualApplicationDirStorage();` (scope `uba`)
- L182 _prototype_ `void* g_exeDirStorage();` (scope `uba`)
- L183 _prototype_ `void* g_logNameStorage();` (scope `uba`)
- L184 _prototype_ `void* g_virtualWorkingDirStorage();` (scope `uba`)
- L185 _prototype_ `void* g_systemTempStorage();` (scope `uba`)
- L186 _prototype_ `void* g_systemRootStorage();` (scope `uba`)
- L187 _prototype_ `void* g_statsStorage();` (scope `uba`)
- L188 _prototype_ `void* g_kernelStatsStorage();` (scope `uba`)
- L189 _prototype_ `void* g_communicationLockStorage();` (scope `uba`)
- L190 _prototype_ `void* g_memoryBlockStorage();` (scope `uba`)
- L191 _prototype_ `void* g_mappedFileTableStorage();` (scope `uba`)
- L192 _prototype_ `void* g_trackInputsLockStorage();` (scope `uba`)
- L193 _prototype_ `void* g_vfsLockStorage();` (scope `uba`)
- L195 _prototype_ `void* g_debugLogPathStorage();` (scope `uba`)
- L196 _prototype_ `void* g_debugLogMutexStorage();` (scope `uba`)
- L201 _macro_ `#define g_virtualApplication (*static_cast<::uba::StringBuffer<512>*>(::uba::g_virtualApplicationStorage()))` — Redirect bare `g_xxx` references through storage-accessor casts. Preprocessor expansion runs before name lookup so callsites lower to RIP-relative lea + deref — no relocation.
- L202 _macro_ `#define g_virtualApplicationDir (*static_cast<::uba::StringBuffer<512>*>(::uba::g_virtualApplicationDirStorage()))`
- L203 _macro_ `#define g_exeDir (*static_cast<::uba::StringBuffer<256>*>(::uba::g_exeDirStorage()))`
- L204 _macro_ `#define g_logName (*static_cast<::uba::StringBuffer<512>*>(::uba::g_logNameStorage()))`
- L205 _macro_ `#define g_virtualWorkingDir (*static_cast<::uba::StringBuffer<512>*>(::uba::g_virtualWorkingDirStorage()))`
- L206 _macro_ `#define g_systemTemp (*static_cast<::uba::StringBuffer<256>*>(::uba::g_systemTempStorage()))`
- L207 _macro_ `#define g_systemRoot (*static_cast<::uba::StringBuffer<128>*>(::uba::g_systemRootStorage()))`
- L208 _macro_ `#define g_stats (*static_cast<::uba::ProcessStats*>(::uba::g_statsStorage()))`
- L209 _macro_ `#define g_kernelStats (*static_cast<::uba::KernelStats*>(::uba::g_kernelStatsStorage()))`
- L210 _macro_ `#define g_communicationLock (*static_cast<::uba::Futex*>(::uba::g_communicationLockStorage()))`
- L211 _macro_ `#define g_memoryBlock (*static_cast<::uba::MemoryBlock*>(::uba::g_memoryBlockStorage()))`
- L212 _macro_ `#define g_mappedFileTable (*static_cast<::uba::MappedFileTable*>(::uba::g_mappedFileTableStorage()))`
- L213 _macro_ `#define g_trackInputsLock (*static_cast<::uba::Futex*>(::uba::g_trackInputsLockStorage()))`
- L214 _macro_ `#define g_vfsLock (*static_cast<::uba::ReaderWriterLock*>(::uba::g_vfsLockStorage()))`
- L216 _macro_ `#define g_debugLogPath (*static_cast<::uba::StringBuffer<::uba::MaxPath>*>(::uba::g_debugLogPathStorage()))`
- L217 _macro_ `#define g_debugLogMutex (*static_cast<::uba::Futex*>(::uba::g_debugLogMutexStorage()))`
- L220 _macro_ `#define VARIABLE_MEM(type, name) VariableMem<type> name##Mem; type& name = (type&)name##Mem.data;`
- L223 _macro_ `#define RPC_MESSAGE(messageName, timerName) \`
- L226 _macro_ `#define RPC_MESSAGE2(messageType, messageName, timer) \`
- L233 _macro_ `#define RPC_MESSAGE_NO_LOCK(messageName, timerName) \`
- L239 _macro_ `#define RPC_MESSAGE_END \`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsCombase.inl` (Private)


#### Free symbols / members of external scopes

- L3 _function_ `HRESULT Detoured_CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv)`
- L19 _typedef_ `typedef HRESULT (WINAPI* FnDllGetClassObject)(REFCLSID, REFIID, LPVOID*);` (scope `Detoured_CoCreateInstance`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsDbgHelp.inl` (Private)


#### struct `_MODLOAD_DATA`  
`typedef struct _MODLOAD_DATA`  
_L3-3_

#### Free symbols / members of external scopes

- L3 _typedef_ `typedef struct _MODLOAD_DATA {} *PMODLOAD_DATA;`
- L4 _typedef_ `using SymLoadModuleExWFunc = BOOL(HANDLE hProcess, HANDLE hFile, PCWSTR ImageName, DWORD64 BaseOfDll, DWORD DllSize, PMODLOAD_DATA Data, DWORD Flags);`
- L5 _variable_ `SymLoadModuleExWFunc* True_SymLoadModuleExW;`
- L7 _function_ `BOOL Detoured_SymLoadModuleExW(HANDLE hProcess, HANDLE hFile, PCWSTR ImageName, DWORD64 BaseOfDll, DWORD DllSize, PMODLOAD_DATA Data, DWORD Flags)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsImagehlp.inl` (Private)


#### Free symbols / members of external scopes

- L3 _typedef_ `typedef PVOID DIGEST_HANDLE;`
- L4 _typedef_ `typedef BOOL(WINAPI* DIGEST_FUNCTION) (DIGEST_HANDLE refdata, PBYTE pData, DWORD dwLength);`
- L6 _typedef_ `using ImageGetDigestStreamFunc = BOOL(HANDLE FileHandle, DWORD DigestLevel, DIGEST_FUNCTION DigestFunction, DIGEST_HANDLE DigestHandle);`
- L7 _variable_ `ImageGetDigestStreamFunc* True_ImageGetDigestStream;`
- L9 _function_ `BOOL Detoured_ImageGetDigestStream(HANDLE FileHandle, DWORD DigestLevel, DIGEST_FUNCTION DigestFunction, DIGEST_HANDLE DigestHandle)`
- L17 _function_ `auto ErrorInvalidParameter = []()` (scope `Detoured_ImageGetDigestStream`)
- L28 _function_ `auto hg = MakeGuard([&]() { ::CloseHandle(mappingHandle); });` (scope `Detoured_ImageGetDigestStream`)
- L33 _function_ `auto mg = MakeGuard([&]() { ::UnmapViewOfFile(mem); });` (scope `Detoured_ImageGetDigestStream`)
- L77 _function_ `` (scope `Detoured_ImageGetDigestStream`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsKernelBase.inl` (Private)


#### struct `Recursive_LoadLibraryExW::Import`  
`struct Import`  
_L2673-2673_
- desc: Important that this code is not doing allocations.. it could cause a recursive stack overflow
- L2673 _public function_ `struct Import` — Important that this code is not doing allocations.. it could cause a recursive stack overflow
- L2673 _public member_ `struct Import { wchar_t name[128]; bool isKnown; Import(const wchar_t* s, bool ik) : isKnown(ik) { wcscpy_s(name, sizeof_array(name), s); } };` — Important that this code is not doing allocations.. it could cause a recursive stack overflow
- L2673 _public member_ `struct Import { wchar_t name[128]; bool isKnown; Import(const wchar_t* s, bool ik) : isKnown(ik) { wcscpy_s(name, sizeof_array(name), s); } };` — Important that this code is not doing allocations.. it could cause a recursive stack overflow

#### struct `Detoured_CreateProcessW::PROC_THREAD_ATTRIBUTE`  
`struct PROC_THREAD_ATTRIBUTE`  
_L3325-3325_
- L3325 _public member_ `struct PROC_THREAD_ATTRIBUTE { DWORD_PTR Attribute; SIZE_T Size; ULONG_PTR Value; };`
- L3325 _public member_ `struct PROC_THREAD_ATTRIBUTE { DWORD_PTR Attribute; SIZE_T Size; ULONG_PTR Value; };`
- L3325 _public member_ `struct PROC_THREAD_ATTRIBUTE { DWORD_PTR Attribute; SIZE_T Size; ULONG_PTR Value; };`

#### struct `Detoured_CreateProcessW::PROC_THREAD_ATTRIBUTE_LIST_INTERNAL`  
`struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL`  
_L3326-3326_
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`
- L3326 _public member_ `struct PROC_THREAD_ATTRIBUTE_LIST_INTERNAL { DWORD Unknown1; DWORD AttributeCount; DWORD Unknown2; DWORD Unknown3; DWORD Unknown4; DWORD Unknown5; PROC_THREAD_ATTRIBUTE Attributes[1]; };`

#### Free symbols / members of external scopes

- L3 _macro_ `#define UBA_ASSERT_ON_DETOURED_STD_PIPE 0 // Errors on clang on llvm-symbolizer.exe.. needs investigation`
- L5 _function_ `static inline BOOL SetLastErrorFromNtStatus(NTSTATUS status)`
- L14 _function_ `DWORD Local_GetLongPathNameW(LPCWSTR lpszShortPath, LPWSTR lpszLongPath, DWORD cchBuffer)`
- L91 _function_ `LPWSTR Detoured_GetCommandLineW()`
- L99 _function_ `VOID Detoured_GetSystemInfo(LPSYSTEM_INFO lpSystemInfo)`
- L110 _function_ `DWORD Detoured_GetCurrentDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer)`
- L130 _function_ `DWORD Detoured_GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer)`
- L148 _function_ `void Shared_SetCurrentDirectory(const wchar_t* workingDirBuffer)`
- L157 _function_ `BOOL Detoured_SetCurrentDirectoryW(LPCWSTR lpPathName)`
- L173 _function_ `BOOL Detoured_DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions)`
- L220 _function_ `BOOL Detoured_CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L249 _function_ `` (scope `Detoured_CreateDirectoryW`)
- L286 _variable_ `thread_local bool t_calledRemoveDirectoryW;`
- L289 _function_ `BOOL Detoured_RemoveDirectoryW(LPCWSTR lpPathName)`
- L360 _function_ `BOOL Detoured_LockFile(HANDLE hFile, DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh, DWORD nNumberOfBytesToLockLow, DWORD nNumberOfBytesToLockHigh)`
- L375 _function_ `BOOL Detoured_LockFileEx(HANDLE hFile, DWORD dwFlags, DWORD dwReserved, DWORD nNumberOfBytesToLockLow, DWORD nNumberOfBytesToLockHigh, LPOVERLAPPED lpOverlapped)`
- L390 _function_ `BOOL Detoured_UnlockFile(HANDLE hFile, DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh, DWORD nNumberOfBytesToUnlockLow, DWORD nNumberOfBytesToUnlockHigh)`
- L405 _function_ `BOOL Detoured_UnlockFileEx(HANDLE hFile, DWORD dwReserved, DWORD nNumberOfBytesToUnlockLow, DWORD nNumberOfBytesToUnlockHigh, LPOVERLAPPED lpOverlapped)`
- L420 _function_ `BOOL Detoured_WriteConsoleA(HANDLE hConsoleOutput, const VOID* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)`
- L430 _function_ `BOOL Detoured_WriteConsoleW(HANDLE hConsoleOutput, const VOID* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)`
- L440 _function_ `BOOL Detoured_ReadConsoleW(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, PCONSOLE_READCONSOLE_CONTROL pInputControl)`
- L456 _function_ `UINT Detoured_GetDriveTypeW(LPCWSTR lpRootPathName)`
- L469 _function_ `BOOL Detoured_GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes)`
- L501 _function_ `BOOL Detoured_GetVolumeInformationByHandleW(HANDLE hFile, LPWSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPWSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)`
- L565 _function_ `BOOL Detoured_GetVolumeInformationW(LPCWSTR lpRootPathName, LPWSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPWSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)`
- L603 _function_ `LPVOID Detoured_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)`
- L636 _function_ `PVOID Detoured_AddVectoredExceptionHandler(ULONG First, PVECTORED_EXCEPTION_HANDLER Handler)`
- L642 _function_ `BOOL Detoured_PathSearchAndQualifyW(LPCWSTR pszPath, LPWSTR pszBuf, UINT cchBuf)`
- L652 _function_ `BOOL Detoured_InitializeSynchronizationBarrier(LPSYNCHRONIZATION_BARRIER lpBarrier, LONG lTotalThreads, LONG lSpinCount)`
- L658 _function_ `BOOL Detoured_DeleteSynchronizationBarrier(LPSYNCHRONIZATION_BARRIER lpBarrier)`
- L663 _function_ `HANDLE Detoured_CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID)`
- L672 _function_ `BOOL Detoured_FlushFileBuffers(HANDLE hFile)`
- L696 _function_ `BOOL Detoured_SetFileTime(HANDLE hFile, const FILETIME* lpCreationTime, const FILETIME* lpLastAccessTime, const FILETIME* lpLastWriteTime)`
- L721 _function_ `DWORD Detoured_GetFileType(HANDLE hFile)`
- L754 _function_ `BOOL Shared_GetFileAttributesExW(const tchar* caller, StringView fileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation, LPCWSTR originalName)`
- L764 _function_ `BOOL Detoured_GetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)`
- L790 _function_ `DWORD Detoured_GetFileAttributesW(LPCWSTR lpFileName)`
- L818 _function_ `BOOL Detoured_SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes)`
- L861 _function_ `DWORD Detoured_GetLongPathNameW(LPCWSTR lpszShortPath, LPWSTR lpszLongPath, DWORD cchBuffer)`
- L920 _function_ `DWORD Detoured_GetFullPathNameW(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR* lpFilePart)`
- L942 _function_ `DWORD Detoured_GetFullPathNameA(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer, LPSTR* lpFilePart)`
- L975 _function_ `BOOL Detoured_GetVolumePathNameW(LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength)`
- L1005 _function_ `DWORD Shared_GetModuleFileNameInner(const tchar* func, HMODULE hModule, const StringView& moduleName, LPWSTR lpFilename, DWORD nSize)`
- L1025 _function_ `DWORD Shared_GetModuleFileNameW(const tchar* func, HMODULE hModule, LPWSTR lpFilename, DWORD nSize)`
- L1084 _function_ `DWORD Detoured_GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize)`
- L1090 _function_ `DWORD Detoured_GetModuleFileNameExW(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize)`
- L1109 _function_ `DWORD Shared_GetModuleFileNameA(const tchar* func, HMODULE hModule, LPSTR lpFilename, DWORD nSize)`
- L1127 _function_ `DWORD Detoured_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize)`
- L1134 _function_ `DWORD Detoured_GetModuleFileNameExA(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize)`
- L1155 _function_ `BOOL Detoured_GetModuleHandleExW(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE *phModule)`
- L1181 _function_ `BOOL Shared_CopyFileExW(const tchar* func, bool isHardlink, LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L1282 _function_ `BOOL Detoured_CopyFileExW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags)`
- L1288 _function_ `BOOL Detoured_CopyFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists)`
- L1295 _function_ `BOOL Detoured_CreateHardLinkW(LPCWSTR lpFileName, LPCWSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L1302 _variable_ `thread_local bool t_calledDeleteFileW;`
- L1305 _function_ `BOOL Detoured_DeleteFileW(LPCWSTR lpFileName)`
- L1360 _function_ `bool Shared_MoveFile(const tchar* func, LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFlags)`
- L1489 _function_ `BOOL Detoured_MoveFileExW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFlags)`
- L1495 _function_ `BOOL Detoured_MoveFileWithProgressW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, DWORD dwFlags)` — MoveFileW ends up here
- L1508 _function_ `bool Shared_GetNextFile(WIN32_FIND_DATA& outData, ListDirectoryHandle& listHandle)`
- L1555 _function_ `HANDLE Local_FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags, const wchar_t* funcName)`
- L1565 _function_ `HANDLE Shared_FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags, const wchar_t* funcName)`
- L1703 _function_ `HANDLE Detoured_FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)`
- L1709 _function_ `HANDLE Detoured_FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)`
- L1715 _function_ `BOOL Detoured_FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)`
- L1748 _function_ `HANDLE Detoured_FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)`
- L1768 _function_ `BOOL Detoured_FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)`
- L1782 _function_ `BOOL Detoured_FindClose(HANDLE handle)`
- L1798 _function_ `BOOL Detoured_GetFileInformationByHandleEx(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS fileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize)`
- L1987 _function_ `BOOL Detoured_GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation)`
- L2162 _function_ `BOOL Detoured_GetFileInformationByName(PCWSTR FileName, FILE_INFO_BY_NAME_CLASS FileInformationClass, PVOID FileInfoBuffer, ULONG FileInfoBufferSize)`
- L2224 _function_ `BOOL Detoured_SetFileInformationByHandle(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize)`
- L2253 _function_ `HANDLE Detoured_CreateFileMappingW(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName)`
- L2320 _function_ `HANDLE Detoured_CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName)`
- L2332 _function_ `HANDLE Detoured_OpenFileMappingW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName)`
- L2351 _variable_ `auto& g_specialViewsLock = *new ReaderWriterLock();`
- L2352 _variable_ `auto& g_specialViews = *new List<SharedMemoryView>();`
- L2355 _function_ `LPVOID Detoured_MapViewOfFileEx(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress)`
- L2461 _function_ `LPVOID Detoured_MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap)`
- L2467 _function_ `PVOID Detoured_MapViewOfFile3(HANDLE FileMapping, HANDLE Process, PVOID BaseAddress, ULONG64 Offset, SIZE_T ViewSize, ULONG AllocationType, ULONG PageProtection, MEM_EXTENDED_PARAMETER *ExtendedParameters, ULONG ParameterCount)`
- L2514 _function_ `BOOL Detoured_FlushViewOfFile(LPCVOID lpBaseAddress, SIZE_T dwNumberOfBytesToFlush)`
- L2521 _function_ `BOOL Detoured_UnmapViewOfFileEx(PVOID lpBaseAddress, ULONG UnmapFlags)`
- L2565 _function_ `BOOL Detoured_UnmapViewOfFile(LPCVOID lpBaseAddress)`
- L2571 _function_ `DWORD Detoured_GetFinalPathNameByHandleW(HANDLE hFile, LPTSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags)`
- L2628 _function_ `DWORD Detoured_SearchPathW(LPCWSTR lpPath, LPCWSTR lpFileName, LPCWSTR lpExtension, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR* lpFilePart)`
- L2664 _typedef_ `using AdditionalLoads = Vector<HMODULE, GrowingAllocator>;`
- L2665 _typedef_ `using VisitedModules = UnorderedSet<StringKey, std::hash<StringKey>, std::equal_to<StringKey>, GrowingAllocator>;`
- L2667 _function_ `HMODULE Recursive_LoadLibraryExW(const StringView& filePath, LPCWSTR originalName, DWORD dwFlags, AdditionalLoads& additionalLoads, VisitedModules& visitedModules)`
- L2680 _function_ `` (scope `Recursive_LoadLibraryExW`)
- L2750 _macro_ `#define ReadTebOffset(offset) (((BYTE*)NtCurrentTeb()) + offset)`
- L2752 _macro_ `#define ReadTebOffset(offset) __readgsqword(offset)`
- L2755 _function_ `HMODULE LoadModuleNoSyscall(StringView moduleName)`
- L2760 _function_ `auto lockGuard = MakeGuard([&](){ LdrUnlockLoaderLock(0, cookie); });` (scope `LoadModuleNoSyscall`)
- L2791 _function_ `HMODULE Shared_LoadLibrary(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags, bool& mightExist)`
- L2844 _function_ `HMODULE Detoured_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)`
- L2889 _function_ `HANDLE Detoured_GetStdHandle(DWORD nStdHandle)`
- L2905 _variable_ `bool g_setStdHandleCalled;`
- L2907 _function_ `BOOL Detoured_SetStdHandle(DWORD nStdHandle, HANDLE hHandle)`
- L2941 _function_ `BOOL Detoured_GetConsoleMode(HANDLE hConsoleHandle, LPDWORD lpMode)`
- L2967 _function_ `BOOL Detoured_SetConsoleMode(HANDLE hConsoleHandle, DWORD mode)`
- L3007 _function_ `BOOL Detoured_GetConsoleTitleW(LPTSTR lpConsoleTitle, DWORD nSize)`
- L3016 _function_ `BOOL Detoured_CreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)`
- L3085 _function_ `auto g = MakeGuard([&]() { if (tempAllocated) delete[] tempAllocated; if (nulStdIn != INVALID_HANDLE_VALUE) CloseHandle(nulStdIn); });` (scope `Detoured_CreateProcessW`)
- L3237 _function_ `` (scope `Detoured_CreateProcessW`)
- L3252 _function_ `auto assertGuard = MakeGuard([&]() { UBA_ASSERTF(false, L"%s is detoured and there is no p` (scope `Detoured_CreateProcessW::__anondee7a8180502`)
- L3530 _function_ `BOOL Detoured_CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)`
- L3563 _function_ `BOOL Detoured_RegisterWaitForSingleObject(PHANDLE phNewWaitObject, HANDLE hObject, WAITORTIMERCALLBACK Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)`
- L3572 _function_ `BOOL Detoured_GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode)`
- L3588 _function_ `BOOL Detoured_CreateTimerQueueTimer(PHANDLE phNewTimer, HANDLE TimerQueue, WAITORTIMERCALLBACK Callback, PVOID Parameter, DWORD DueTime, DWORD Period, ULONG Flags)`
- L3596 _function_ `BOOL Detoured_DeleteTimerQueueTimer(HANDLE TimerQueue, HANDLE Timer, HANDLE CompletionEvent)`
- L3609 _function_ `DWORD Detoured_WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)`
- L3615 _function_ `DWORD Detoured_WaitForSingleObjectEx(HANDLE hHandle, DWORD dwMilliseconds, BOOL bAlertable)` — Both WaitForSingleObject and WaitForSingleObjectEx is needed to support Wine
- L3647 _function_ `DWORD Detoured_WaitForMultipleObjects(DWORD nCount, const HANDLE* lpHandles, BOOL bWaitAll, DWORD dwMilliseconds)`
- L3660 _function_ `auto g = MakeGuard([&]() { _freea(tempHandles); _freea(isProcess); });` (scope `Detoured_WaitForMultipleObjects`)
- L3699 _function_ `DWORD Detoured_WaitForMultipleObjectsEx(DWORD nCount, const HANDLE* lpHandles, BOOL bWaitAll, DWORD dwMilliseconds, BOOL bAlertable)`
- L3735 _function_ `LANGID Detoured_GetUserDefaultUILanguage()`
- L3743 _function_ `BOOL Detoured_GetThreadPreferredUILanguages(DWORD dwFlags, PULONG pulNumLanguages, PZZWSTR pwszLanguagesBuffer, PULONG pcchLanguagesBuffer)`
- L3777 _function_ `BOOL Detoured_DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)`
- L3783 _function_ `BOOL Detoured_GetDiskFreeSpaceExA(LPCSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes)`
- L3790 _function_ `DWORD Detoured_GetLongPathNameA(LPCSTR lpszShortPath, LPSTR lpszLongPath, DWORD cchBuffer)`
- L3798 _function_ `BOOL Detoured_GetVolumePathNameA(LPCSTR lpszFileName, LPSTR lpszVolumePathName, DWORD cchBufferLength)`
- L3805 _function_ `HANDLE Detoured_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)`
- L3812 _function_ `HANDLE Detoured_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)`
- L3819 _function_ `DWORD Detoured_GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)`
- L3826 _function_ `DWORD Detoured_GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize)`
- L3833 _function_ `BOOL Detoured_GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)`
- L3840 _function_ `DWORD Detoured_SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)`
- L3847 _function_ `DWORD Detoured_SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod)`
- L3854 _function_ `BOOL Detoured_SetEndOfFile(HANDLE hFile)`
- L3861 _function_ `DWORD Detoured_GetFileAttributesA(LPCSTR lpFileName)`
- L3868 _function_ `BOOL Detoured_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)`
- L3876 _function_ `HMODULE Detoured_LoadLibraryW(LPCWSTR lpLibFileName)`
- L3884 _function_ `BOOL Detoured_SetDllDirectoryW(LPCWSTR lpPathName)`
- L3892 _function_ `BOOL Detoured_GetDllDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer)`
- L3900 _function_ `DWORD Detoured_GetModuleBaseNameA(HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize)`
- L3918 _function_ `DWORD Detoured_GetModuleBaseNameW(HANDLE hProcess, HMODULE hModule, LPWSTR lpBaseName, DWORD nSize)`
- L3935 _function_ `LPTOP_LEVEL_EXCEPTION_FILTER Detoured_SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)`
- L3942 _function_ `BOOL Detoured_FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize)`
- L3951 _function_ `HANDLE Detoured_CreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams)`
- L3958 _function_ `HANDLE Detoured_CreateFileTransactedW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile, HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID lpExtendedParameter)`
- L3966 _function_ `HFILE Detoured_OpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle)`
- L3973 _function_ `HANDLE Detoured_ReOpenFile(HANDLE hOriginalFile, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwFlagsAndAttributes)`
- L3985 _function_ `BOOL Detoured_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)`
- L3994 _function_ `BOOL Detoured_ReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)`
- L4004 _function_ `BOOL Detoured_ReadFileScatter(HANDLE hFile, FILE_SEGMENT_ELEMENT* aSegmentArray, DWORD nNumberOfBytesToRead, LPDWORD lpReserved, LPOVERLAPPED lpOverlapped)`
- L4013 _function_ `BOOL Detoured_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)`
- L4021 _function_ `BOOL Detoured_WriteFileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)`
- L4030 _function_ `void Detoured_SetLastError(DWORD dwErrCode)`
- L4040 _function_ `DWORD Detoured_GetLastError()`
- L4050 _function_ `BOOL Detoured_SetFileValidData(HANDLE hFile, LONGLONG ValidDataLength)`
- L4058 _function_ `BOOL Detoured_ReplaceFileW(LPCWSTR lpReplacedFileName, LPCWSTR lpReplacementFileName, LPCWSTR lpBackupFileName, DWORD dwReplaceFlags, LPVOID lpExclude, LPVOID lpReserved)`
- L4066 _function_ `BOOL Detoured_CreateHardLinkA(LPCSTR lpFileName, LPCSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L4074 _function_ `BOOL Detoured_DeleteFileA(LPCSTR lpFileName)`
- L4084 _function_ `DWORD Detoured_GetShortPathNameW(LPCWSTR lpszLongPath, LPWSTR lpszShortPath, DWORD cchBuffer)`
- L4092 _function_ `BOOL Detoured_NeedCurrentDirectoryForExePathW(LPCWSTR ExeName)`
- L4099 _function_ `BOOL Detoured_ReadDirectoryChangesW(HANDLE hDirectory, LPVOID lpBuffer, DWORD nBufferLength, BOOL bWatchSubtree, DWORD dwNotifyFilter, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)`
- L4106 _function_ `BOOL Detoured_SetCurrentDirectoryA(LPCSTR lpPathName)`
- L4112 _function_ `BOOLEAN Detoured_CreateSymbolicLinkW(LPCWSTR lpSymlinkFileName, LPCWSTR lpTargetFileName, DWORD dwFlags)`
- L4120 _function_ `BOOLEAN Detoured_CreateSymbolicLinkA(LPCSTR lpSymlinkFileName, LPCSTR lpTargetFileName, DWORD dwFlags)`
- L4128 _function_ `DWORD Detoured_SetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpValue)`
- L4136 _function_ `DWORD Detoured_GetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize)`
- L4144 _function_ `DWORD Detoured_GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize)`
- L4152 _function_ `LPWCH Detoured_GetEnvironmentStringsW()`
- L4170 _function_ `DWORD Detoured_GetTempPathW(DWORD nBufferLength, LPWSTR lpBuffer)`
- L4178 _function_ `DWORD Detoured_GetTempPath2W(DWORD nBufferLength, LPWSTR lpBuffer)`
- L4186 _function_ `DWORD Detoured_ExpandEnvironmentStringsW(LPCWSTR lpSrc, LPWSTR lpDst, DWORD nSize)`
- L4193 _function_ `HANDLE Detoured_FindFirstFileNameW(LPCWSTR lpFileName, DWORD dwFlags, LPDWORD StringLength, PWSTR LinkName)`
- L4200 _function_ `UINT Detoured_GetTempFileNameW(LPCWSTR lpPathName, LPCWSTR lpPrefixString, UINT uUnique, LPTSTR lpTempFileName)`
- L4207 _function_ `DWORD Detoured_GetShortPathNameA(LPCSTR lpszLongPath, LPSTR lpszShortPath, DWORD cchBuffer)`
- L4216 _function_ `DWORD Detoured_GetTempPathA(DWORD nBufferLength, LPSTR lpBuffer)`
- L4223 _function_ `UINT Detoured_GetTempFileNameA(LPCSTR lpPathName, LPCSTR lpPrefixString, UINT uUnique, LPSTR lpTempFileName)`
- L4230 _function_ `BOOL Detoured_CreateDirectoryExW(LPCWSTR lpTemplateDirectory, LPCWSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L4237 _function_ `BOOL Detoured_RemoveDirectoryA(LPCSTR lpPathName)`
- L4300 _function_ `HANDLE Detoured_OpenFileById(HANDLE hFile, LPFILE_ID_DESCRIPTOR lpFileID, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwFlags)` — DWORD Detoured_GetSecurityInfo(HANDLE handle, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID* ppsidOwner, PSID* ppsidGroup, PACL* ppDacl, PACL* ppSacl, PSECURITY_DESCRIPTOR* ppSecurityDescriptor) { DETOURED_CALL(GetSecurityInfo); if (isDetouredHandle(handle)) { handle = asDetouredHandle(handle).trueHandle; UBA_ASSERTF(handle != INVALID_HANDLE_VALUE, L"GetSecurityInfo"); } DEBUG_LOG_TRUE(L"GetSecurityInfo", L""); return True_GetSecurityInfo(handle, ObjectType, SecurityInfo, ppsidOwner, ppsidGroup, ppDacl, ppSacl, ppSecurityDescriptor); } BOOL Detoured_DecryptFileW(LPCWSTR lpFileName, DWORD dwReserved) { DETOURED_CALL(DecryptFileW); DEBUG_LOG_TRUE(L"DecryptFileW", L""); return True_DecryptFileW(lpFileName, dwReserved); } BOOL Detoured_DecryptFileA(LPCSTR lpFileName, DWORD dwReserved) { DETOURED_CALL(DecryptFileA); DEBUG_LOG_TRUE(L"DecryptFileA", L""); return True_DecryptFileA(lpFileName, dwReserved); } BOOL Detoured_EncryptFileW(LPCWSTR lpFileName) { DETOURED_CALL(EncryptFileW); DEBUG_LOG_TRUE(L"EncryptFileW", L""); return True_EncryptFileW(lpFileName); } BOOL Detoured_EncryptFileA(LPCSTR lpFileName) { DETOURED_CALL(EncryptFileA); DEBUG_LOG_TRUE(L"EncryptFileA", L""); return True_EncryptFileA(lpFileName); } DWORD Detoured_OpenEncryptedFileRawW(LPCWSTR lpFileName, ULONG ulFlags, PVOID* pvContext) { DETOURED_CALL(OpenEncryptedFileRawW); DEBUG_LOG_TRUE(L"OpenEncryptedFileRawW", L""); return True_OpenEncryptedFileRawW(lpFileName, ulFlags, pvContext); } DWORD Det
- L4308 _function_ `HANDLE Detoured_CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName)`
- L4318 _function_ `HANDLE Detoured_CreateEventExW(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)`
- L4328 _function_ `HANDLE Detoured_CreateMutexExW(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)`
- L4338 _function_ `HANDLE Detoured_CreateWaitableTimerExW(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCWSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess)`
- L4348 _function_ `HANDLE Detoured_CreateIoCompletionPort(HANDLE FileHandle, HANDLE ExistingCompletionPort, ULONG_PTR CompletionKey, DWORD NumberOfConcurrentThreads)`
- L4360 _function_ `HANDLE Detoured_CreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)`
- L4366 _function_ `BOOL Detoured_PostQueuedCompletionStatus(HANDLE CompletionPort, DWORD dwNumberOfBytesTransferred, ULONG_PTR dwCompletionKey, LPOVERLAPPED lpOverlapped)`
- L4373 _function_ `BOOL Detoured_GetQueuedCompletionStatusEx(HANDLE CompletionPort, LPOVERLAPPED_ENTRY lpCompletionPortEntries, ULONG ulCount, PULONG ulNumEntriesRemoved, DWORD dwMilliseconds, BOOL fAlertable)`
- L4380 _function_ `BOOL Detoured_CancelIo(HANDLE hFile)`
- L4387 _function_ `BOOL Detoured_CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped)`
- L4394 _function_ `BOOL Detoured_SetFileCompletionNotificationModes(HANDLE FileHandle, UCHAR Flags)`
- L4401 _function_ `BOOL Detoured_CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize)`
- L4411 _function_ `BOOL Detoured_SetHandleInformation(HANDLE hObject, DWORD dwMask, DWORD dwFlags)`
- L4418 _function_ `HANDLE Detoured_CreateNamedPipeW(LPCWSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes)`
- L4426 _function_ `BOOL Detoured_CallNamedPipeW(LPCWSTR lpNamedPipeName, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, DWORD nTimeOut)`
- L4433 _function_ `BOOL Detoured_PeekNamedPipe(HANDLE hNamedPipe, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage)`
- L4440 _function_ `BOOL Detoured_GetKernelObjectSecurity(HANDLE Handle, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)`
- L4449 _function_ `BOOL Detoured_ImpersonateNamedPipeClient(HANDLE hNamedPipe)`
- L4455 _function_ `BOOL Detoured_TransactNamedPipe(HANDLE hNamedPipe, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, LPOVERLAPPED lpOverlapped)`
- L4461 _function_ `BOOL Detoured_SetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpMode, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout)`
- L4467 _function_ `BOOL Detoured_GetNamedPipeInfo(HANDLE hNamedPipe, LPDWORD lpFlags, LPDWORD lpOutBufferSize, LPDWORD lpInBufferSize, LPDWORD lpMaxInstances)`
- L4473 _function_ `BOOL Detoured_GetNamedPipeHandleStateW(HANDLE hNamedPipe, LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout, LPWSTR lpUserName, DWORD nMaxUserNameSize)`
- L4479 _function_ `BOOL Detoured_GetNamedPipeServerProcessId(HANDLE Pipe, PULONG ServerProcessId)`
- L4485 _function_ `BOOL Detoured_GetNamedPipeServerSessionId(HANDLE Pipe, PULONG ServerSessionId)`
- L4492 _function_ `HANDLE Detoured_OpenFileMappingA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName)`
- L4499 _function_ `DWORD Detoured_GetMappedFileNameW(HANDLE hProcess, LPVOID lpv, LPWSTR lpFilename, DWORD nSize)`
- L4506 _function_ `BOOL Detoured_IsProcessorFeaturePresent(DWORD ProcessorFeature)`
- L4514 _function_ `PVOID Detoured_VirtualAlloc2(HANDLE Process, PVOID BaseAddress, SIZE_T Size, ULONG AllocationType, ULONG PageProtection, MEM_EXTENDED_PARAMETER *ExtendedParameters, ULONG ParameterCount)`
- L4522 _function_ `PVOID Detoured_VirtualAlloc2FromApp(HANDLE Process, PVOID BaseAddress, SIZE_T Size, ULONG AllocationType, ULONG PageProtection, MEM_EXTENDED_PARAMETER *ExtendedParameters, ULONG ParameterCount)`
- L4530 _function_ `BOOL Detoured_UnmapViewOfFile2(HANDLE Process, PVOID BaseAddress, ULONG UnmapFlags)`
- L4538 _function_ `BOOL Detoured_GetComputerNameA(LPSTR lpBuffer, LPDWORD nSize)`
- L4546 _function_ `HMODULE Detoured_GetModuleHandleW(LPCWSTR lpModuleName)`
- L4554 _function_ `VOID Detoured_GetStartupInfoW(LPSTARTUPINFOW lpStartupInfo)`
- L4579 _function_ `VOID Detoured_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime)`
- L4586 _function_ `SIZE_T Detoured_GetLargePageMinimum()`
- L4609 _function_ `void Detoured_ExitProcess(UINT uExitCode)`
- L4614 _function_ `LPSTR Detoured_GetCommandLineA()`
- L4622 _function_ `LPWSTR* Detoured_CommandLineToArgvW(LPCWSTR lpCmdLine, int *pNumArgs)`
- L4630 _function_ `void* Detoured_GetProcAddress(HMODULE hModule, LPCSTR lpProcName)`
- L4643 _function_ `BOOL Detoured_FreeLibrary(HMODULE hModule)`
- L4651 _function_ `LSTATUS Detoured_RegOpenKeyW(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)`
- L4661 _function_ `LSTATUS Detoured_RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)`
- L4671 _function_ `LSTATUS Detoured_RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition)`
- L4681 _function_ `LSTATUS Detoured_RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)`
- L4690 _function_ `LSTATUS Detoured_RegCloseKey(HKEY hKey)`
- L4696 _function_ `HANDLE Detoured_CreateConsoleScreenBuffer(DWORD dwDesiredAccess, DWORD dwShareMode, const SECURITY_ATTRIBUTES* lpSecurityAttributes, DWORD dwFlags, LPVOID lpScreenBufferData)`
- L4703 _function_ `HANDLE Detoured_OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)`
- L4711 _function_ `ULONG Detoured_RemoveVectoredExceptionHandler(PVOID Handle)`
- L4717 _function_ `VOID Detoured_RaiseFailFastException(PEXCEPTION_RECORD pExceptionRecord, PCONTEXT pContextRecord, DWORD dwFlags)`
- L4723 _function_ `BOOL Detoured_TerminateJobObject(HANDLE hJob, UINT uExitCode)`
- L4729 _function_ `UINT Detoured_SetErrorMode(UINT uMode)`
- L4734 _function_ `BOOL Detoured_CreateProcessAsUserW(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)`
- L4741 _function_ `BOOL WINAPI Detoured_SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, BOOL Add)`
- L4748 _function_ `UINT Detoured_GetConsoleOutputCP()`
- L4757 _function_ `BOOL Detoured_ReadConsoleInputA(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead)`
- L4764 _function_ `HWND Detoured_GetConsoleWindow()`
- L4772 _function_ `BOOL Detoured_SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD dwCursorPosition)`
- L4781 _function_ `BOOL Detoured_GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo)`
- L4798 _function_ `BOOL Detoured_ScrollConsoleScreenBufferW(HANDLE hConsoleOutput, const SMALL_RECT* lpScrollRectangle, const SMALL_RECT* lpClipRectangle, COORD dwDestinationOrigin, const CHAR_INFO* lpFill)`
- L4805 _function_ `BOOL Detoured_FillConsoleOutputAttribute(HANDLE hConsoleOutput, WORD wAttribute, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfAttrsWritten)`
- L4812 _function_ `BOOL Detoured_FillConsoleOutputCharacterW(HANDLE hConsoleOutput, TCHAR cCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)`
- L4819 _function_ `BOOL Detoured_FlushConsoleInputBuffer(HANDLE hConsoleInput)`
- L4832 _function_ `BOOL Detoured_SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes)`
- L4839 _function_ `BOOL Detoured_SetConsoleTitleW(LPCTSTR lpConsoleTitle)`
- L4846 _function_ `int Detoured_GetLocaleInfoEx(LPCWSTR lpLocaleName, LCTYPE LCType, LPWSTR lpLCData, int cchData)`
- L4855 _function_ `int Detoured_GetUserDefaultLocaleName(LPWSTR lpLocaleName, int cchLocaleName)`
- L4865 _function_ `BOOL Detoured_IsValidCodePage(UINT CodePage)`
- L4873 _function_ `UINT Detoured_GetACP()`
- L4881 _function_ `LPCWSTR Detoured_PathFindFileNameW(LPCWSTR pszPath)` — This is called by Ps4SymbolTool.exe and vctip.exe
- L4888 _function_ `BOOL Detoured_PathIsRelativeW(LPCWSTR pszPath)`
- L4895 _function_ `BOOL Detoured_PathIsDirectoryEmptyW(LPCWSTR pszPath)`
- L4903 _function_ `void Detoured_UrlCreateFromPathW(PCWSTR pszPath, PWSTR pszUrl, DWORD* pcchUrl, DWORD dwFlags)`
- L4909 _function_ `void Detoured_PathCreateFromUrlW(PCWSTR pszUrl, PWSTR pszPath, DWORD* pcchPath, DWORD dwFlags)`
- L4915 _function_ `HRESULT Detoured_SHCreateStreamOnFileW(LPCWSTR pszFile, DWORD grfMode, IStream** ppstm)`
- L4921 _function_ `BOOL Detoured_PathFileExistsW(LPCWSTR pszPath)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsMiMalloc.inl` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DETOURED_CALL_MEM(x) DETOURED_CALL(x)`
- L7 _macro_ `#define TRACK_UCRT_ALLOC_ENABLED 0`
- L10 _variable_ `Atomic<u64> g_reallocCount;`
- L11 _variable_ `Atomic<u64> g_allocCount;`
- L12 _variable_ `Atomic<u64> g_freeCount;`
- L13 _macro_ `#define TRACK_UCRT_ALLOC(x) ++g_##x##Count;`
- L15 _macro_ `#define TRACK_UCRT_ALLOC(x)`
- L18 _function_ `inline bool IsInMiMalloc(void* ptr)`
- L24 _macro_ `#define VALIDATE_IN_MIMALLOC(ptr) UBA_ASSERT(!ptr || IsInMiMalloc(ptr));`
- L26 _macro_ `#define VALIDATE_IN_MIMALLOC(ptr)`
- L29 _function_ `void* Detoured_malloc(size_t size)`
- L36 _function_ `void* Detoured_calloc(size_t number, size_t size)`
- L43 _function_ `void* Detoured__recalloc(void* memblock, size_t num, size_t size)`
- L51 _function_ `void* Detoured_realloc(void* memblock, size_t size)`
- L59 _function_ `void* Detoured__expand(void* memblock, size_t size)`
- L67 _function_ `size_t Detoured__msize(void* memblock)`
- L74 _function_ `void Detoured_free(void* memblock)`
- L84 _function_ `char* Detoured__strdup(const char* s)`
- L91 _function_ `wchar_t* Detoured__wcsdup(const wchar_t* s)`
- L102 _function_ `wchar_t* Detoured__mbsdup(const wchar_t* s)`
- L109 _function_ `void* Detoured__aligned_malloc(size_t size, size_t alignment)`
- L116 _function_ `void* Detoured__aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment)`
- L124 _function_ `void* Detoured__aligned_realloc(void* memblock, size_t size, size_t alignment)`
- L132 _function_ `void Detoured__aligned_free(void* memblock)`
- L140 _function_ `void* Detoured__aligned_offset_malloc(size_t size, size_t alignment, size_t offset)`
- L147 _function_ `void* Detoured__aligned_offset_recalloc(void* memblock, size_t num, size_t size, size_t alignment, size_t offset)`
- L155 _function_ `void* Detoured__aligned_offset_realloc(void* memblock, size_t size, size_t alignment, size_t offset)`
- L163 _function_ `errno_t Detoured__wdupenv_s(wchar_t** buffer, size_t* numberOfElements, const wchar_t* varname)`
- L176 _function_ `errno_t Detoured__dupenv_s(char** buffer, size_t* numberOfElements, const char* varname)`
- L185 _function_ `void* Detoured__malloc_base(size_t _Size)`
- L191 _function_ `void* Detoured__calloc_base(size_t _Count, size_t _Size)`
- L197 _function_ `void* Detoured__realloc_base(void* memblock, size_t size)`
- L205 _function_ `void Detoured__free_base(void* memblock)`
- L216 _function_ `void* Detoured__expand_base(void* memblock, size_t size)`
- L224 _function_ `size_t Detoured__msize_base(void* memblock)`
- L232 _function_ `void* Detoured__recalloc_base(void* memblock, size_t num, size_t size)`
- L242 _function_ `size_t Detoured__aligned_msize(void* p, size_t alignment, size_t offset)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsNtDll.inl` (Private)


#### struct `JobInfo`  
`struct JobInfo`  
_L962-962_
- L962 _public member_ `struct JobInfo { Vector<HANDLE> processes; bool shouldKill = false; };`
- L962 _public member_ `struct JobInfo { Vector<HANDLE> processes; bool shouldKill = false; };`

#### struct `Detoured_NtQueryInformationProcess::PROCESS_CONSOLE_HOST_PROCESS_INFORMATION`  
`struct PROCESS_CONSOLE_HOST_PROCESS_INFORMATION`  
_L2762-2765_
- L2764 _public member_ `ULONG_PTR ConsoleHostProcess;`

#### Free symbols / members of external scopes

- L3 _function_ `StringBuffer<64> ToString(FILE_INFORMATION_CLASS c)`
- L7 _macro_ `#define FILE_INFO_CLASS(name, value) case value: return StringBuffer<64>(TCV(#name));`
- L16 _function_ `StringBuffer<64> ToString(FS_INFORMATION_CLASS c)`
- L29 _function_ `bool IsContentWrite(u32 desiredAccess, u32 createDisposition)`
- L38 _function_ `bool IsContentRead(u32 desiredAccess, u32 createDisposition)`
- L43 _function_ `bool IsContentUse(u32 desiredAccess, u32 createDisposition)`
- L48 _function_ `bool IsWrite(u32 desiredAccess, u32 createDisposition)`
- L53 _function_ `u8 GetFileAccessFlags(DWORD desiredAccess, u32 createDisposition)`
- L63 _function_ `const tchar* StdToString(DWORD stdHandle)`
- L75 _function_ `StringBuffer<32> ToString(NTSTATUS s)`
- L96 _prototype_ `extern "C" RTL_PATH_TYPE NTAPI RtlDetermineDosPathNameType_U(PCWSTR DosFileName)`
- L97 _prototype_ `extern "C" ULONG NTAPI RtlIsDosDeviceName_U(PCWSTR DosFileName)`
- L99 _function_ `static void FixupDosPath(PCWSTR& dosPath, StringBufferBase& temp)`
- L130 _function_ `NTSTATUS Detoured_RtlDosPathNameToNtPathName_U_WithStatus(PCWSTR dosPath, PUNICODE_STRING ntPath, PWSTR* filePart, VOID* reserved)`
- L140 _function_ `NTSTATUS Detoured_RtlDosPathNameToRelativeNtPathName_U_WithStatus(PCWSTR dosPath, PUNICODE_STRING ntPath, PWSTR* filePart, RTL_RELATIVE_NAME_U* relativeName)`
- L150 _function_ `DWORD WINAPI Detoured_RtlGetFullPathName_U(const WCHAR* name, ULONG size, WCHAR* buffer, WCHAR** file_part)`
- L160 _function_ `ULONG WINAPI Detoured_RtlGetFullPathName_UEx(const WCHAR* name, ULONG size, WCHAR* buffer, WCHAR** file_part, RTL_PATH_TYPE* type)`
- L170 _function_ `BOOLEAN NTAPI Detoured_RtlDosPathNameToRelativeNtPathName_U(PCWSTR dosPath, PUNICODE_STRING ntPath, PWSTR* filePart, RTL_RELATIVE_NAME_U* relativeName)`
- L180 _function_ `NTSTATUS Detoured_NtQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FS_INFORMATION_CLASS FsInformationClass)`
- L186 _function_ `` (scope `Detoured_NtQueryVolumeInformationFile`)
- L260 _function_ `NTSTATUS Detoured_NtQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass)`
- L324 _function_ `` (scope `Detoured_NtQueryInformationFile`)
- L541 _function_ `NTSTATUS NTAPI Detoured_NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan)`
- L549 _function_ `` (scope `Detoured_NtQueryDirectoryFile`)
- L734 _function_ `NTSTATUS Detoured_NtQueryFullAttributesFile(POBJECT_ATTRIBUTES ObjectAttributes, PVOID Attributes)`
- L776 _function_ `NTSTATUS Detoured_NtSetInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass)`
- L786 _function_ `` (scope `Detoured_NtSetInformationFile`)
- L940 _function_ `NTSTATUS Detoured_NtSetInformationObject(HANDLE ObjectHandle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG Length)`
- L953 _function_ `NTSTATUS Detoured_NtRemoveIoCompletionEx(HANDLE IoCompletionHandle, FILE_IO_COMPLETION_INFORMATION *info, ULONG count, ULONG *written, LARGE_INTEGER* timeout, BOOLEAN alertable)`
- L963 _variable_ `auto& g_jobsLock = *new ReaderWriterLock();`
- L964 _variable_ `auto& g_jobs = *new UnorderedMap<FileObject*, JobInfo>();`
- L966 _function_ `void TerminateProcessesInJob(JobInfo&& info, u32 exitCode)`
- L979 _function_ `void CloseProcess(u32 exitStatus)`
- L995 _function_ `NTSTATUS NTAPI Detoured_NtTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus)`
- L1030 _function_ `NTSTATUS Detoured_NtCreateJobObject(HANDLE* handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES* attr)`
- L1033 _function_ `auto g = MakeGuard([&]() { DEBUG_LOG_TRUE(L"NtCreateJobObject", L"%llu -> %s", u64(*handle` (scope `Detoured_NtCreateJobObject`)
- L1044 _function_ `NTSTATUS Detoured_NtSetInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS infoClass, void* info, ULONG len)`
- L1053 _function_ `auto g = MakeGuard([&]() { DEBUG_LOG_TRUE(L"NtSetInformationJobObject", L"%s(%u) -> %s", prefix` (scope `Detoured_NtSetInformationJobObject`)
- L1079 _function_ `NTSTATUS Detoured_NtAssignProcessToJobObject(HANDLE job, HANDLE process)`
- L1100 _function_ `NTSTATUS Detoured_NtTerminateJobObject(HANDLE handle, NTSTATUS status)`
- L1109 _function_ `NTSTATUS NTAPI Detoured_NtCreateSection(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize, ULONG SectionPageProtection, ULONG AllocationAttributes, HANDLE FileHandle)`
- L1121 _function_ `VOID NTAPI Detoured_RtlExitUserProcess(NTSTATUS ExitStatus)`
- L1131 _variable_ `bool g_checkRtlHeap = true;`
- L1133 _function_ `SIZE_T Detoured_RtlSizeHeap(HANDLE HeapPtr, ULONG Flags, PVOID Ptr)`
- L1142 _function_ `BOOLEAN Detoured_RtlFreeHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress)`
- L1154 _function_ `NTSTATUS Detoured_RtlAnsiStringToUnicodeString(PUNICODE_STRING DestinationString, PCANSI_STRING SourceString, BOOLEAN AllocateDestinationString)`
- L1168 _function_ `NTSTATUS Detoured_RtlUnicodeStringToAnsiString(PANSI_STRING DestinationString, PCUNICODE_STRING SourceString, BOOLEAN AllocateDestinationString)`
- L1184 _function_ `VOID Detoured_RtlFreeAnsiString(PANSI_STRING AnsiString)`
- L1196 _function_ `BOOLEAN Detoured_RtlIsPackageSid(PSID Sid)`
- L1203 _function_ `BOOLEAN Detoured_RtlIsCapabilitySid(PSID sid)`
- L1210 _function_ `NTSTATUS NTAPI Local_NtCreateFile(bool IsCreateFunc, PHANDLE hFileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength)`
- L1269 _function_ `NTSTATUS NTAPI Shared_NtCreateFile(bool IsCreateFunc, PHANDLE hFileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength)`
- L1282 _function_ `` (scope `Shared_NtCreateFile`)
- L1864 _function_ `auto mfg = MakeGuard([mf](){ delete mf; });` (scope `Shared_NtCreateFile`)
- L2017 _function_ `NTSTATUS NTAPI Detoured_NtCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength)`
- L2024 _variable_ `thread_local bool t_ntOpenFileDisallowed;`
- L2026 _function_ `NTSTATUS NTAPI Detoured_NtOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions)`
- L2038 _variable_ `thread_local bool t_ntReadFileCalled;`
- L2042 _function_ `int ReadFileAccessViolation(PEXCEPTION_POINTERS ep, HANDLE fileHandle, const FileInfo& fi, const void* mem, u64 size, u64 readPos, u64 bytesRead, u64 length, bool hasByteOffset)`
- L2077 _function_ `NTSTATUS NTAPI Detoured_NtReadFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key)`
- L2086 _function_ `` (scope `Detoured_NtReadFile`)
- L2174 _variable_ `thread_local bool t_ntWriteFileCalled;`
- L2177 _variable_ `StringBuffer<32 * 1024> g_stdFile;`
- L2178 _variable_ `ReaderWriterLock& g_stdFileLock = *new ReaderWriterLock();`
- L2180 _function_ `void WriteStdFile(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, bool isError)`
- L2208 _function_ `int WriteFileAccessViolation(PEXCEPTION_POINTERS ep)`
- L2217 _function_ `NTSTATUS NTAPI Detoured_NtWriteFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key)`
- L2226 _function_ `` (scope `Detoured_NtWriteFile`)
- L2312 _function_ `NTSTATUS NTAPI Detoured_NtFsControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG FsControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength)`
- L2345 _function_ `NTSTATUS Detoured_NtDeviceIoControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength)`
- L2417 _function_ `NTSTATUS NTAPI Detoured_NtCopyFileChunk(HANDLE Source, HANDLE Dest, HANDLE Event, PIO_STATUS_BLOCK IoStatusBlock, ULONG Length, PULONG SourceOffset, PULONG DestOffset, PULONG SourceKey, PULONG DestKey, ULONG Flags)`
- L2437 _function_ `NTSTATUS NTAPI Detoured_NtClose(HANDLE handle)`
- L2479 _function_ `` (scope `Detoured_NtClose`)
- L2682 _function_ `NTSTATUS Detoured_NtQueryObject(HANDLE Handle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength)`
- L2750 _function_ `NTSTATUS Detoured_NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength)`
- L2786 _variable_ `thread_local bool t_ntQuerySecurityObjectCalled;`
- L2789 _function_ `NTSTATUS Detoured_NtQuerySecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG Length, PULONG LengthNeeded)`
- L2798 _function_ `` (scope `Detoured_NtQuerySecurityObject`)
- L2895 _function_ `NTSTATUS Detoured_RtlCreateUserThread(HANDLE process, SECURITY_DESCRIPTOR* descr, BOOLEAN suspended, ULONG zero_bits, SIZE_T stack_reserve, SIZE_T stack_commit, void* start, void *param, HANDLE *handle_ptr, CLIENT_ID* id)`
- L2902 _function_ `NTSTATUS Detoured_NtCreateThreadEx(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, HANDLE ProcessHandle, USER_THREAD_START_ROUTINE* StartRoutine, PVOID Argument, ULONG CreateFlags, SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaximumStackSize, PS_ATTRIBUTE_LIST* AttributeList)`
- L2909 _function_ `NTSTATUS Detoured_NtOpenJobObject(HANDLE* handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)`
- L2916 _function_ `NTSTATUS Detoured_NtAllocateVirtualMemoryEx(HANDLE ProcessHandle, PVOID *BaseAddress, SIZE_T *RegionSize, ULONG AllocationType, ULONG Protect, PMEM_EXTENDED_PARAMETER ExtendedParameters, ULONG ExtendedParameterCount)`
- L2923 _function_ `NTSTATUS Detoured_NtQueryInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS infoClass, void* info, ULONG len, ULONG* retLen)`
- L2930 _function_ `NTSTATUS Detoured_NtCreateIoCompletion(PHANDLE IoCompletionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, ULONG Count)`
- L2938 _function_ `NTSTATUS Detoured_NtRemoveIoCompletion(HANDLE IoCompletionHandle, PULONG_PTR CompletionKey, PULONG_PTR CompletionValue, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER Timeout)`
- L2945 _function_ `NTSTATUS NTAPI Detoured_NtFlushBuffersFileEx(HANDLE FileHandle, ULONG Flags, PVOID Parameters, ULONG ParametersSize, PIO_STATUS_BLOCK IoStatusBlock)`
- L2953 _function_ `NTSTATUS NTAPI Detoured_NtAlpcCreatePort(PHANDLE PortHandle, POBJECT_ATTRIBUTES ObjectAttributes, PALPC_PORT_ATTRIBUTES PortAttributes)`
- L2959 _function_ `NTSTATUS NTAPI Detoured_NtAlpcConnectPort(PHANDLE PortHandle, PUNICODE_STRING PortName, POBJECT_ATTRIBUTES ObjectAttributes, PALPC_PORT_ATTRIBUTES PortAttributes, DWORD ConnectionFlags, PSID RequiredServerSid, PPORT_MESSAGE ConnectionMessage, PSIZE_T ConnectMessageSize, PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes, PALPC_MESSAGE_ATTRIBUTES InMessageAttributes, PLARGE_INTEGER Timeout)`
- L2965 _function_ `NTSTATUS NTAPI Detoured_NtAlpcCreatePortSection(HANDLE PortHandle, ULONG Flags, HANDLE SectionHandle, SIZE_T SectionSize, PHANDLE AlpcSectionHandle, PSIZE_T ActualSectionSize)`
- L2971 _function_ `NTSTATUS NTAPI Detoured_NtAlpcSendWaitReceivePort(HANDLE PortHandle, DWORD Flags, PPORT_MESSAGE SendMessage_, PALPC_MESSAGE_ATTRIBUTES SendMessageAttributes, PPORT_MESSAGE ReceiveMessage, PSIZE_T BufferLength, PALPC_MESSAGE_ATTRIBUTES ReceiveMessageAttributes, PLARGE_INTEGER Timeout)`
- L2980 _function_ `NTSTATUS NTAPI Detoured_NtAlpcDisconnectPort(HANDLE PortHandle, ULONG Flags)`
- L2986 _function_ `NTSTATUS NTAPI Detoured_ZwQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan)`
- L3012 _function_ `NTSTATUS NTAPI Detoured_ZwSetInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass)`
- L3020 _function_ `NTSTATUS Detoured_RtlGetVersion(PRTL_OSVERSIONINFOW lpVersionInformation)`
- L3028 _function_ `PVOID Detoured_RtlAllocateHeap(PVOID HeapHandle, ULONG Flags, SIZE_T Size)`
- L3037 _function_ `PVOID Detoured_RtlReAllocateHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress, SIZE_T Size)`
- L3054 _function_ `BOOLEAN Detoured_RtlValidateHeap(HANDLE HeapPtr, ULONG Flags, PVOID Block)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsRpcrt4.inl` (Private)


#### Free symbols / members of external scopes

- L5 _function_ `RPC_STATUS Detoured_RpcStringBindingComposeW(RPC_WSTR ObjUuid, RPC_WSTR Protseq, RPC_WSTR NetworkAddr, RPC_WSTR Endpoint, RPC_WSTR Options, RPC_WSTR* StringBinding)`
- L13 _variable_ `UnorderedSet<void*> g_rpcBindings;`
- L15 _function_ `RPC_STATUS Detoured_RpcBindingFromStringBindingW(RPC_WSTR StringBinding, RPC_BINDING_HANDLE *Binding)`
- L40 _function_ `RPC_STATUS Detoured_RpcBindingSetAuthInfoExW(RPC_BINDING_HANDLE Binding, RPC_WSTR ServerPrincName, unsigned long AuthnLevel, unsigned long AuthnSvc, RPC_AUTH_IDENTITY_HANDLE AuthIdentity, unsigned long AuthzSvc, RPC_SECURITY_QOS *SecurityQOS)`
- L54 _variable_ `void* True2_NdrClientCall2 = nullptr;`
- L56 _prototype_ `ULONG_PTR __cdecl Detoured_NdrClientCall2(PMIDL_STUB_DESC pStubDescriptor, PFORMAT_STRING pFormat, ...);`
- L58 _function_ `ULONG_PTR Local_NdrClientCall2(PMIDL_STUB_DESC pStubDescriptor, PFORMAT_STRING pFormat, void** pStack)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsShell32.inl` (Private)


#### Free symbols / members of external scopes

- L3 _function_ `HRESULT Detoured_SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR* ppszPath)`
- L37 _function_ `HRESULT Detoured_SHGetFolderPathAndSubDirW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPCWSTR pszSubDir, LPWSTR pszPath)`
- L68 _function_ `HRESULT Detoured_SHGetFolderPathW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath)`
- L76 _function_ `HRESULT Detoured_SHGetKnownFolderIDList(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, PIDLIST_ABSOLUTE *pidl)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsUcrtBase.inl` (Private)


#### Free symbols / members of external scopes

- L3 _function_ `wchar_t* Detoured__wgetcwd(wchar_t* buffer, int maxlen)`
- L23 _function_ `wchar_t* Detoured__wfullpath(wchar_t* absPath, const wchar_t* relPath, size_t maxLength)`
- L63 _function_ `char* Detoured__fullpath(char* absPath, const char* relPath, size_t maxLength)` — Needed for ltcg builds on wine
- L113 _function_ `errno_t Detoured__get_wpgmptr(wchar_t** pValue)`
- L121 _variable_ `static WCHAR* g_fake_wpgmptr = g_virtualApplication.data;`
- L123 _function_ `WCHAR** Detoured___p__wpgmptr()`
- L130 _function_ `__time64_t Detoured__time64(__time64_t* destTime)`
- L143 _function_ `const wchar_t* WaccessResultToString(errno_t res)`
- L161 _function_ `errno_t Detoured__waccess_s(const wchar_t* path, int mode)`
- L216 _function_ `intptr_t Detoured__get_osfhandle(int fd)`
- L238 _function_ `int Detoured__isatty(int fd)`
- L249 _function_ `int Detoured__write(int fd, const void* buffer, unsigned int count)`
- L277 _function_ `int Detoured__wspawnl(int mode, const wchar_t* cmdname, const wchar_t* arg0, const wchar_t* arg1, ...)`
- L329 _function_ `auto g = MakeGuard([&]() { CloseHandle(pi.hProcess); CloseHandle(pi.hThread); });` (scope `Detoured__wspawnl`)
- L348 _function_ `errno_t Detoured__wsplitpath_s(const wchar_t* path, wchar_t* drive, size_t driveNumberOfElements, wchar_t* dir, size_t dirNumberOfElements, wchar_t* fname, size_t nameNumberOfElements, wchar_t* ext, size_t extNumberOfElements)`
- L360 _function_ `int Detoured__wcsnicoll_l(const wchar_t* string1, const wchar_t* string2, size_t count, _locale_t locale)`
- L383 _function_ `wchar_t* Detoured__wgetenv(const wchar_t* varname)`
- L391 _function_ `errno_t Detoured__wgetenv_s(size_t* pReturnValue, wchar_t* buffer, size_t numberOfElements, const wchar_t* varname)`
- L399 _function_ `char* Detoured_getenv(const char* varname)`
- L407 _function_ `errno_t Detoured_getenv_s(size_t* pReturnValue, char* buffer, size_t numberOfElements, const char* varname)`
- L415 _function_ `errno_t Detoured__wmakepath_s(wchar_t* path, size_t sizeInWords, const wchar_t* drive, const wchar_t* dir, const wchar_t* fname, const wchar_t* ext)`
- L422 _function_ `char* Detoured__getcwd(char* buffer, int maxlen)`
- L430 _function_ `int Detoured_fputs(const char* str, FILE* stream)`

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursFunctionsWin.h` (Private)


#### enum `FILE_INFO_BY_NAME_CLASS`  
`enum FILE_INFO_BY_NAME_CLASS`  
_L534-534_

#### Free symbols / members of external scopes

- L17 _macro_ `#define DETOURED_INCLUDE_DEBUG 1`
- L19 _macro_ `#define DETOURED_INCLUDE_DEBUG 0`
- L27 _macro_ `#define DETOURED_FUNCTIONS \`
- L38 _macro_ `#define DETOURED_FUNCTION_X64(x)`
- L40 _macro_ `#define DETOURED_FUNCTION_X64(x) DETOURED_FUNCTION(x)`
- L43 _macro_ `#define DETOURED_FUNCTIONS_KERNELBASE \`
- L123 _macro_ `#define DETOURED_FUNCTIONS_KERNEL32 \`
- L132 _macro_ `#define DETOURED_FUNCTIONS_NTDLL \`
- L170 _macro_ `#define DETOURED_FUNCTIONS_SHLWAPI \`
- L173 _macro_ `#define DETOURED_FUNCTIONS_SHELL32 \`
- L179 _macro_ `#define DETOURED_WSPLITPATH DETOURED_FUNCTION(_wsplitpath_s)`
- L181 _macro_ `#define DETOURED_WSPLITPATH`
- L184 _macro_ `#define DETOURED_FUNCTIONS_UCRTBASE \`
- L200 _macro_ `#define DETOURED_FUNCTIONS_RPCRT4 \`
- L207 _macro_ `#define DETOURED_FUNCTIONS_RPCRT4`
- L211 _macro_ `#define DETOURED_FUNCTIONS_MEMORY \`
- L235 _macro_ `#define DETOURED_FUNCTIONS_MEMORY_NON_WINE \` — All these are calling above functions on wine
- L244 _macro_ `#define DETOURED_FUNCTIONS_MEMORY`
- L245 _macro_ `#define DETOURED_FUNCTIONS_MEMORY_NON_WINE`
- L248 _macro_ `#define DETOURED_FUNCTIONS_COMBASE \`
- L253 _macro_ `#define DETOURED_FUNCTIONS_KERNELBASE_DEBUG \`
- L384 _macro_ `#define DETOURED_FUNCTIONS_KERNEL32_DEBUG \`
- L391 _macro_ `#define DETOURED_FUNCTIONS_NTDLL_DEBUG \`
- L415 _macro_ `#define DETOURED_FUNCTIONS_SHLWAPI_DEBUG \`
- L422 _macro_ `#define DETOURED_FUNCTIONS_SHELL32_DEBUG \`
- L426 _macro_ `#define DETOURED_FUNCTIONS_UCRTBASE_DEBUG \`
- L450 _macro_ `#define DETOURED_FUNCTIONS_MEMORY_DEBUG \`
- L457 _macro_ `#define DETOURED_FUNCTIONS_KERNELBASE_DEBUG`
- L458 _macro_ `#define DETOURED_FUNCTIONS_KERNEL32_DEBUG`
- L459 _macro_ `#define DETOURED_FUNCTIONS_NTDLL_DEBUG`
- L460 _macro_ `#define DETOURED_FUNCTIONS_SHLWAPI_DEBUG`
- L461 _macro_ `#define DETOURED_FUNCTIONS_SHELL32_DEBUG`
- L462 _macro_ `#define DETOURED_FUNCTIONS_UCRTBASE_DEBUG`
- L463 _macro_ `#define DETOURED_FUNCTIONS_MEMORY_DEBUG`
- L467 _typedef_ `using PALPC_PORT_ATTRIBUTES = void*;`
- L468 _typedef_ `using PALPC_MESSAGE_ATTRIBUTES = void*;`
- L469 _typedef_ `using PPORT_MESSAGE = void*;`
- L470 _prototype_ `NTSTATUS NTAPI NtQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FS_INFORMATION_CLASS FsInformationClass);`
- L471 _prototype_ `NTSTATUS NTAPI NtQueryFullAttributesFile(POBJECT_ATTRIBUTES ObjectAttributes, PVOID Attributes);`
- L472 _prototype_ `NTSTATUS NTAPI NtQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);`
- L473 _prototype_ `NTSTATUS NTAPI NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);`
- L474 _prototype_ `NTSTATUS NTAPI NtDeviceIoControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);`
- L475 _prototype_ `NTSTATUS NTAPI NtFsControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG FsControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);`
- L476 _prototype_ `NTSTATUS NTAPI NtCopyFileChunk(HANDLE Source, HANDLE Dest, HANDLE Event, PIO_STATUS_BLOCK IoStatusBlock, ULONG Length, PULONG SourceOffset, PULONG DestOffset, PULONG SourceKey, PULONG DestKey, ULONG Flags);`
- L477 _prototype_ `NTSTATUS NTAPI NtFlushBuffersFileEx(HANDLE FileHandle, ULONG Flags, PVOID Parameters, ULONG ParametersSize, PIO_STATUS_BLOCK IoStatusBlock);`
- L478 _prototype_ `NTSTATUS NTAPI NtReadFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);`
- L479 _prototype_ `NTSTATUS NTAPI NtWriteFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);`
- L480 _prototype_ `NTSTATUS NTAPI NtTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus);`
- L481 _prototype_ `NTSTATUS NTAPI NtSetInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);`
- L482 _prototype_ `NTSTATUS NTAPI NtSetInformationObject(HANDLE ObjectHandle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG Length);`
- L483 _prototype_ `NTSTATUS NTAPI RtlCreateUserThread(HANDLE process, SECURITY_DESCRIPTOR* descr, BOOLEAN suspended, ULONG zero_bits, SIZE_T stack_reserve, SIZE_T stack_commit, void* start, void *param, HANDLE *handle_ptr, CLIENT_ID* id);`
- L484 _prototype_ `NTSTATUS NTAPI NtCreateThreadEx(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, HANDLE ProcessHandle, USER_THREAD_START_ROUTINE* StartRoutine, PVOID Argument, ULONG CreateFlags, SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaximumStackSize, PS_ATTRIBUTE_LIST* AttributeList);`
- L485 _prototype_ `NTSTATUS NTAPI NtCreateJobObject(HANDLE* handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES* attr);`
- L486 _prototype_ `NTSTATUS NTAPI NtOpenJobObject(HANDLE* handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr);`
- L487 _prototype_ `NTSTATUS NTAPI NtQueryInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS infoClass, void* info, ULONG len, ULONG* retLen);`
- L488 _prototype_ `NTSTATUS NTAPI NtSetInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS infoClass, void* info, ULONG len);`
- L489 _prototype_ `NTSTATUS NTAPI NtAssignProcessToJobObject(HANDLE job, HANDLE process);`
- L490 _prototype_ `NTSTATUS NTAPI NtTerminateJobObject(HANDLE handle, NTSTATUS status);`
- L491 _prototype_ `NTSTATUS NTAPI NtCreateSection(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize, ULONG SectionPageProtection, ULONG AllocationAttributes, HANDLE FileHandle);`
- L492 _prototype_ `NTSTATUS NTAPI NtCreateIoCompletion(PHANDLE IoCompletionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, ULONG Count);`
- L493 _prototype_ `NTSTATUS NTAPI NtRemoveIoCompletion(HANDLE IoCompletionHandle, PULONG_PTR CompletionKey, PULONG_PTR CompletionValue, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER Timeout);`
- L494 _prototype_ `NTSTATUS NTAPI NtRemoveIoCompletionEx(HANDLE IoCompletionHandle, FILE_IO_COMPLETION_INFORMATION* info, ULONG count, ULONG *written, LARGE_INTEGER *timeout, BOOLEAN alertable);`
- L495 _prototype_ `NTSTATUS NTAPI NtAllocateVirtualMemoryEx(HANDLE ProcessHandle, PVOID *BaseAddress, SIZE_T *RegionSize, ULONG AllocationType, ULONG Protect, PMEM_EXTENDED_PARAMETER ExtendedParameters, ULONG ExtendedParameterCount);`
- L496 _prototype_ `NTSTATUS NTAPI NtQuerySecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG Length, PULONG LengthNeeded);`
- L497 _prototype_ `NTSTATUS NTAPI NtAlpcCreatePort(PHANDLE PortHandle, POBJECT_ATTRIBUTES ObjectAttributes, PALPC_PORT_ATTRIBUTES PortAttributes);`
- L498 _prototype_ `NTSTATUS NTAPI NtAlpcConnectPort(PHANDLE PortHandle, PUNICODE_STRING PortName, POBJECT_ATTRIBUTES ObjectAttributes, PALPC_PORT_ATTRIBUTES PortAttributes, DWORD ConnectionFlags, PSID RequiredServerSid, PPORT_MESSAGE ConnectionMessage, PSIZE_T ConnectMessageSize, PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes, PALPC_MESSAGE_ATTRIBUTES InMessageAttributes, PLARGE_INTEGER Timeout);`
- L499 _prototype_ `NTSTATUS NTAPI NtAlpcCreatePortSection(HANDLE PortHandle, ULONG Flags, HANDLE SectionHandle, SIZE_T SectionSize, PHANDLE AlpcSectionHandle, PSIZE_T ActualSectionSize);`
- L500 _prototype_ `NTSTATUS NTAPI NtAlpcSendWaitReceivePort(HANDLE PortHandle, DWORD Flags, PPORT_MESSAGE SendMessage_, PALPC_MESSAGE_ATTRIBUTES SendMessageAttributes, PPORT_MESSAGE ReceiveMessage, PSIZE_T BufferLength, PALPC_MESSAGE_ATTRIBUTES ReceiveMessageAttributes, PLARGE_INTEGER Timeout);`
- L501 _prototype_ `NTSTATUS NTAPI NtAlpcDisconnectPort(HANDLE PortHandle, ULONG Flags);`
- L502 _prototype_ `NTSTATUS NTAPI NtExtendSection(HANDLE, PLARGE_INTEGER);`
- L503 _prototype_ `NTSTATUS NTAPI ZwCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);`
- L504 _prototype_ `NTSTATUS NTAPI ZwOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions);`
- L505 _prototype_ `NTSTATUS NTAPI ZwClose(HANDLE Handle);`
- L506 _prototype_ `NTSTATUS NTAPI ZwMapViewOfSection(HANDLE SectionHandle, HANDLE ProcessHandle, PVOID* BaseAddress, ULONG_PTR ZeroBits, SIZE_T CommitSize, PLARGE_INTEGER SectionOffset, PSIZE_T ViewSize, DWORD InheritDisposition, ULONG AllocationType, ULONG Win32Protect);`
- L507 _prototype_ `NTSTATUS NTAPI ZwCreateSection(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize, ULONG SectionPageProtection, ULONG AllocationAttributes, HANDLE FileHandle);`
- L508 _prototype_ `NTSTATUS NTAPI ZwQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);`
- L509 _prototype_ `NTSTATUS NTAPI ZwSetInformationFile(HANDLE FileHandle,PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);`
- L510 _prototype_ `NTSTATUS NTAPI LdrLockLoaderLock(ULONG Flags, ULONG* Disposition, PVOID* Cookie);`
- L511 _prototype_ `NTSTATUS NTAPI LdrUnlockLoaderLock(ULONG Flags, PVOID Cookie);`
- L512 _prototype_ `NTSTATUS NTAPI LdrAddRefDll(ULONG Flags, PVOID BaseAddress);`
- L513 _prototype_ `PVOID WINAPI ResolveDelayLoadedAPI(PVOID ParentModuleBase, PCIMAGE_DELAYLOAD_DESCRIPTOR DelayloadDescriptor, void* FailureDllHook, void* FailureSystemHook, PIMAGE_THUNK_DATA ThunkAddress, ULONG Flags);`
- L514 _prototype_ `void WINAPI RtlExitUserThread(ULONG);`
- L515 _prototype_ `NTSTATUS NTAPI RtlGetVersion(PRTL_OSVERSIONINFOW lpVersionInformation);`
- L516 _prototype_ `BOOLEAN NTAPI RtlFreeHeap(PVOID HeapHandle, ULONG Flags, PVOID HeapBase);`
- L517 _prototype_ `BOOLEAN NTAPI RtlValidateHeap(HANDLE HeapPtr, ULONG Flags, PVOID Block);`
- L518 _prototype_ `NTSTATUS NTAPI RtlDosPathNameToNtPathName_U_WithStatus(PCWSTR dos_path, PUNICODE_STRING ntpath, PWSTR* file_part, VOID* reserved);`
- L519 _prototype_ `NTSTATUS NTAPI RtlDosPathNameToRelativeNtPathName_U_WithStatus(PCWSTR DosFileName, PUNICODE_STRING NtFileName, PWSTR *FilePart, RTL_RELATIVE_NAME_U* RelativeName);`
- L520 _prototype_ `DWORD WINAPI RtlGetFullPathName_U(const WCHAR* name, ULONG size, WCHAR* buffer, WCHAR** file_part);`
- L521 _prototype_ `BOOLEAN NTAPI RtlDosPathNameToRelativeNtPathName_U(PCWSTR DosName, PUNICODE_STRING NtName, PWSTR *FilePart, RTL_RELATIVE_NAME_U* RelativeName);`
- L522 _prototype_ `ULONG NTAPI WINAPI RtlGetFullPathName_UEx(const WCHAR* name, ULONG size, WCHAR* buffer, WCHAR** file_part, RTL_PATH_TYPE* type);`
- L523 _prototype_ `VOID NTAPI RtlExitUserProcess(NTSTATUS ExitStatus);`
- L524 _prototype_ `VOID NTSYSAPI RtlMapGenericMask(PACCESS_MASK AccessMask, const GENERIC_MAPPING *GenericMapping);`
- L525 _prototype_ `PVOID NTAPI RtlAllocateHeap( PVOID HeapHandle, ULONG Flags, SIZE_T Size);`
- L526 _prototype_ `PVOID NTAPI RtlReAllocateHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress, SIZE_T Size);`
- L527 _prototype_ `SIZE_T NTAPI RtlSizeHeap(HANDLE HeapPtr, ULONG Flags, PVOID Ptr);`
- L528 _prototype_ `void NTAPI BaseThreadInitThunk(ULONG Unknown,LPTHREAD_START_ROUTINE StartAddress,PVOID ThreadParameter);`
- L529 _prototype_ `void* _expand_base(void* memblock, size_t size);`
- L530 _prototype_ `HRESULT SHGetFolderPathAndSubDirW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPCWSTR pszSubDir, LPWSTR pszPath);`
- L531 _prototype_ `HRESULT SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR* ppszPath);`
- L532 _prototype_ `HRESULT SHGetKnownFolderIDList(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, PIDLIST_ABSOLUTE *pidl);`
- L533 _prototype_ `HRESULT SHGetFolderPathW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);`
- L535 _prototype_ `BOOL WINAPI GetFileInformationByName(PCWSTR FileName, FILE_INFO_BY_NAME_CLASS FileInformationClass, PVOID FileInfoBuffer, ULONG FileInfoBufferSize);`
- L536 _prototype_ `DWORD WINAPI GetTempPath2W(DWORD BufferLength, LPWSTR Buffer);`
- L537 _prototype_ `__time64_t WINAPI _time64(__time64_t* destTime);`
- L541 _macro_ `#define DETOURED_FUNCTION_UNKNOWN(Func) DETOURED_FUNCTION(Func)`
- L543 _macro_ `#define DETOURED_FUNCTION(Func) extern decltype(Func)* True_##Func;`
- L547 _namespace_ `namespace uba`
- L551 _prototype_ `void PreInit(const DetoursPayload& payload);` (scope `uba`)
- L552 _prototype_ `void Init(const DetoursPayload& payload, u64 startTime);` (scope `uba`)
- L553 _prototype_ `void Deinit(u64 startTime);` (scope `uba`)
- L554 _prototype_ `void PostDeinit();` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Private/Windows/UbaDetoursUtilsWin.h` (Private)


#### struct `uba::FileObject`  
`struct FileObject`  
_L12-28_
- L14 _public prototype_ `void* operator new(size_t size);`
- L15 _public prototype_ `void operator delete(void* p);`
- L16 _public member_ `FileInfo* fileInfo = nullptr;`
- L17 _public member_ `u32 refCount = 1;`
- L18 _public member_ `u32 closeId = 0;`
- L19 _public member_ `u32 desiredAccess = 0;`
- L20 _public member_ `bool deleteOnClose = false;`
- L21 _public member_ `bool ownsFileInfo = false;`
- L24 _public member_ `bool wasUsed = false;` — Is set to true once content of file has been accessed (ReadFile or MapViewOfFile)
- L27 _public member_ `TString newName;`
- L30 _function_ `inline void* FileObject::operator new(size_t size)`
- L31 _function_ `inline void FileObject::operator delete(void* p)`

#### enum `uba::HandleType`  
`enum HandleType`  
_L34-44_
- L36 _public enumerator_ `HandleType_File`
- L37 _public enumerator_ `HandleType_FileMapping`
- L38 _public enumerator_ `HandleType_Process`
- L39 _public enumerator_ `HandleType_Job`
- L40 _public enumerator_ `HandleType_StdErr`
- L41 _public enumerator_ `HandleType_StdOut`
- L42 _public enumerator_ `HandleType_StdIn`

#### struct `uba::DetouredHandle`  
`struct DetouredHandle`  
_L47-61_
- L49 _public prototype_ `void* operator new(size_t size);`
- L50 _public prototype_ `void operator delete(void* p);`
- L52 _public function_ `DetouredHandle(HandleType t, HANDLE th = INVALID_HANDLE_VALUE) : trueHandle(th), type(t)`
- L54 _public member_ `HANDLE trueHandle;`
- L55 _public member_ `DirTableOffset dirTableOffset;`
- L56 _public member_ `HandleType type;`
- L59 _public member_ `FileObject* fileObject = nullptr;` — Only for files
- L60 _public member_ `u64 pos = 0;`

#### struct `uba::MemoryFile`  
`struct MemoryFile`  
_L64-92_
- L66 _public prototype_ `MemoryFile(u8* data = nullptr, bool localOnly = true);`
- L67 _public prototype_ `MemoryFile(bool localOnly, u64 reserveSize, bool isThrowAway, u32 commitStepSize, const tchar* fileName = nullptr);`
- L69 _public prototype_ `void Reserve(u64 reserveSize_, const tchar* fileName = nullptr);`
- L70 _public prototype_ `void Unreserve();`
- L71 _public prototype_ `void Write(struct DetouredHandle& handle, LPCVOID lpBuffer, u64 nNumberOfBytesToWrite, const tchar* hint);`
- L72 _public prototype_ `void EnsureCommitted(const struct DetouredHandle& handle, u64 size);`
- L73 _public prototype_ `void Remap(const struct DetouredHandle& handle, u64 size);`
- L75 _public member_ `u64 fileIndex = ~u64(0);`
- L76 _public member_ `u64 fileTime = ~u64(0);`
- L77 _public member_ `u32 volumeSerial = 0;`
- L78 _public member_ `u32 commitStepSize = 1024*1024;`
- L80 _public member_ `SharedMemoryHandle memoryHandle;`
- L81 _public member_ `SharedMemoryView memoryView;`
- L83 _public member_ `u8* baseAddress = nullptr;`
- L84 _public member_ `u64 reserveSize = 0;`
- L85 _public member_ `u64 mappedSize = 0;`
- L86 _public member_ `u64 committedSize = 0;`
- L87 _public member_ `u64 writtenSize = 0;`
- L88 _public member_ `ReaderWriterLock lock;`
- L89 _public member_ `bool isLocalOnly;`
- L90 _public member_ `bool isReported = false;`
- L91 _public member_ `bool isThrowAway = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L29 _externvar_ `extern BlockAllocator<FileObject>& g_fileObjectAllocator;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Detours/Public/UbaDetoursApi.h` (Public)


#### Free symbols / members of external scopes

- L4 _macro_ `#define UBA_DETOURED_API __declspec(dllexport)`
- L6 _macro_ `#define UBA_DETOURED_API __declspec(dllimport)`
- L13 _prototype_ `unsigned int UbaSendCustomMessage(const void* send, unsigned int sendSize, void* recv, unsigned int recvCapacity);` — Send custom message from detoured process all the way out to callback registered with RegisterCustomService Handles remote processes as well and network the message
- L16 _prototype_ `bool UbaFlushWrittenFiles();` — Make sure all written files are flushed to destination (lots of files are kept in memory until process ends otherwise)
- L20 _prototype_ `bool UbaUpdateEnvironment(const wchar_t* reason, bool resetStats);` — Update environment. Making sure caches are up-to-date in detoured process. reason ends up in the visualizer for the next block of process if resetStats is true (if resetStats is not true, this will just update the environment within same process)
- L23 _prototype_ `bool UbaRunningRemote();` — Returns true if process is running on a remote machine
- L28 _prototype_ `bool UbaRequestNextProcess(unsigned int prevExitCode, wchar_t* outArguments, unsigned int outArgumentsCapacity);` — This function will automatically flush written files before requesting next process and will also update environment if new process is retrieved prevExitCode should contain exit code of "finished" process. Will write arguments into outArguments. outArgumentsCapacity should be in characters (not bytes)
- L31 _prototype_ `bool UbaRequestNextProcess2(unsigned int prevExitCode, wchar_t* outArguments, unsigned int outArgumentsCapacity, unsigned int timeOutMs, bool* outShouldExit);` — Same as above but with a timeout how long it can wait before giving up to get next process and a "should exit" variable telling the calling process to exit
