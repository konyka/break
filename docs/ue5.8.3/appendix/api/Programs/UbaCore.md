# Programs / UbaCore

- module root: `Source/Programs/UnrealBuildAccelerator/Core`
- headers: 46; symbols: 2160
- symbol kinds: class=32, enum=20, enumerator=47, externvar=5, function=822, macro=182, member=377, namespace=51, prototype=371, struct=105, typedef=55, union=2, variable=91
- PrivateDependencyModuleNames: BLAKE3, UbaMimalloc
- PublicDependencyModuleNames: UbaVersion
- PublicIncludePathModuleNames: OodleDataCompression, UbaMimalloc

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventDispatchSemaphore.inl` (Private)


#### struct `uba::EventDispatchSemaphore`  
`struct EventDispatchSemaphore : EventHeader`  
_L14-225_
- inherits: `EventHeader`
- L16 _public prototype_ `EventDispatchSemaphore() = default;`
- L18 _public function_ `EventDispatchSemaphore(EventResetType resetType)`
- L23 _public function_ `~EventDispatchSemaphore()`
- L28 _public function_ `void Create(EventResetType resetType)`
- L43 _public function_ `void Destroy()`
- L59 _public function_ `void Set()`
- L82 _public function_ `void Reset()`
- L93 _public function_ `bool IsSet(u64 timeoutMs = ~0u)`
- L141 _public function_ `void Signal()`
- L153 _public function_ `bool Wait(u64 timeoutMs)`
- L186 _public function_ `void Drain()`
- L199 _public function_ `void* GetHandle()`
- L209 _public member_ `Waiter* m_oldestWaiter = nullptr;`
- L210 _public member_ `Waiter* m_newestWaiter = nullptr;`
- L214 _public member_ `TriggerType m_triggered = TriggerType_None;`
- L216 _public member_ `Futex m_lock;`
- L219 _public member_ `HANDLE m_sem = 0;`
- L221 _public member_ `sem_t* m_sem;`
- L223 _public member_ `dispatch_semaphore_t m_sem = 0;`

#### struct `uba::EventDispatchSemaphore::Waiter`  
`struct Waiter`  
_L204-208_
- L206 _public member_ `Waiter* next = nullptr;`
- L207 _public member_ `Waiter* prev = nullptr;`

#### enum `uba::EventDispatchSemaphore::TriggerType`  
`enum TriggerType : u8`  
_L212-212_
- L212 _public enumerator_ `enum TriggerType : u8 { TriggerType_None, TriggerType_One, TriggerType_All }; TriggerType m_triggered = TriggerType_None; Futex m_lock; #if PLATFORM_WINDOWS HANDLE m_sem = 0;`
- L212 _public enumerator_ `enum TriggerType : u8 { TriggerType_None, TriggerType_One, TriggerType_All }; TriggerType m_triggered = TriggerType_None; Futex m_lock; #if PLATFORM_WINDOWS HANDLE m_sem = 0;`
- L212 _public enumerator_ `enum TriggerType : u8 { TriggerType_None, TriggerType_One, TriggerType_All }; TriggerType m_triggered = TriggerType_None; Futex m_lock; #if PLATFORM_WINDOWS HANDLE m_sem = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventFutex.inl` (Private)


#### enum `uba::EventFutexState`  
`enum EventFutexState : u32`  
_L60-65_
- L62 _public enumerator_ `EventFutexState_Reset = 0`
- L63 _public enumerator_ `EventFutexState_Signaled = 2`
- L64 _public enumerator_ `EventFutexState_Destroyed = 3`

#### struct `uba::EventFutex`  
`struct EventFutex : EventHeader`  
_L67-299_
- inherits: `EventHeader`
- L73 _public function_ `EventFutex()` — Stamp tag 3 at offset 0 so cross-process consumers (notably the static-detour stub's SharedEvent::Set/IsSet sanity check) can identify EventFutex slots in shm without any higher-level handshake. SharedEvent::Destroy zeroes this byte again when the slot is torn down.
- L74 _public function_ `~EventFutex()`
- L76 _public function_ `bool Create(EventResetType rt, bool = true)`
- L89 _public function_ `void Destroy()`
- L105 _public function_ `void Set()`
- L127 _public function_ `bool IsSet(u32 timeoutMs = ~0u)`
- L142 _public function_ `void Reset()` — Reset() is required by the local-event dispatcher (Event::Reset, Event::Create's pool-reuse path). Manual-reset: clear any latched signal. Auto-reset: drain outstanding tokens. No-op if Destroyed; never wakes anyone (waiters only care about Signaled/Destroyed).
- L164 _public function_ `void* GetHandle()`
- L170 _private function_ `bool WaitManual(u32 timeoutMs)`
- L215 _private function_ `bool WaitAuto(u32 timeoutMs)`
- L266 _private function_ `static void FutexWakeOne(Atomic<u32>* addr)`
- L271 _private function_ `static void FutexWakeAll(Atomic<u32>* addr)`
- L276 _private function_ `static u64 MonotonicNs()`
- L283 _private function_ `static struct timespec NsToTimespec(u64 ns)`
- L295 _private member_ `Atomic<bool> m_initialized { false };` — EventHeader occupies the first 8 bytes (tag byte + m_resetType). The atomics below are plain u32s, naturally aligned, safe for cross-process FUTEX use on Linux x86_64 and aarch64.
- L297 _private member_ `Atomic<u32> m_state { EventFutexState_Reset };` — 3 bytes of padding to align the u32s (the compiler inserts these).
- L298 _private member_ `Atomic<u32> m_autoCount { 0 };`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventMachSemaphore.inl` (Private)


#### struct `uba::EventMachSemaphore`  
`struct EventMachSemaphore : EventHeader`  
_L11-69_
- inherits: `EventHeader`
- L13 _public function_ `~EventMachSemaphore()`
- L18 _public function_ `bool Create(StringView name, bool isOwner)`
- L40 _public function_ `void Destroy()`
- L48 _public function_ `void Set()`
- L53 _public function_ `bool IsSet(u32 timeoutMs = ~0u)`
- L62 _public function_ `void ToString(StringBufferBase& out)`
- L67 _public member_ `bool m_isOwner = false;`
- L68 _public member_ `semaphore_t m_sem = MACH_PORT_NULL;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventPosixSemaphore.inl` (Private)


#### struct `uba::EventPosixSemaphore`  
`struct EventPosixSemaphore : EventHeader`  
_L11-153_
- inherits: `EventHeader`
- L14 _public function_ `~EventPosixSemaphore()`
- L19 _public function_ `bool Create(StringView name, bool isOwner)`
- L49 _public function_ `void Destroy()`
- L72 _public function_ `void Set()`
- L79 _public function_ `bool IsSet(u32 timeoutMs = ~0u)`
- L143 _public function_ `void ToString(StringBufferBase& out)`
- L149 _private member_ `bool m_isOwner = false;`
- L150 _private member_ `sem_t* m_snd = nullptr;`
- L151 _private member_ `sem_t* m_rcv = nullptr;`
- L152 _private member_ `tchar* m_name = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventUlock.inl` (Private)


#### enum `uba::EventUlockState`  
`enum EventUlockState : u32`  
_L68-73_
- L70 _public enumerator_ `EventUlockState_Reset = 0`
- L71 _public enumerator_ `EventUlockState_Signaled = 2`
- L72 _public enumerator_ `EventUlockState_Destroyed = 3`

#### struct `uba::EventUlock`  
`struct EventUlock : EventHeader`  
_L75-333_
- inherits: `EventHeader`
- L77 _public prototype_ `EventUlock() = default;`
- L78 _public function_ `~EventUlock()`
- L80 _public function_ `bool Create(EventResetType rt, bool = true)`
- L97 _public function_ `void Destroy()`
- L116 _public function_ `void Set()`
- L135 _public function_ `void Reset()`
- L152 _public function_ `bool IsSet(u32 timeoutMs = ~0u)`
- L212 _public function_ `void* GetHandle()`
- L218 _private function_ `bool WaitManual(u32 timeoutMs)`
- L258 _private function_ `bool WaitAuto(u32 timeoutMs)`
- L308 _private function_ `static void WakeOne(Atomic<u32>* addr)`
- L313 _private function_ `static void WakeAll(Atomic<u32>* addr)`
- L318 _private function_ `static u64 MonotonicNs()`
- L330 _private member_ `Atomic<u32> m_initialized { 0 };` — EventHeader occupies the first 8 bytes (tag byte + m_resetType). All three atomics are u32 so __ulock_wait2 can wait on each. Bool- padding would have left the dword at &m_initialized with undefined upper bytes, which UL_COMPARE_AND_WAIT can't compare against zero.
- L331 _private member_ `Atomic<u32> m_state { EventUlockState_Reset };`
- L332 _private member_ `Atomic<u32> m_autoCount { 0 };`

#### Free symbols / members of external scopes

- L15 _prototype_ `int __ulock_wait2(uint32_t operation, void* addr, uint64_t value, uint64_t timeout_ns, uint64_t value2);`
- L16 _prototype_ `int __ulock_wake (uint32_t operation, void* addr, uint64_t wake_value);`
- L24 _macro_ `#define UL_COMPARE_AND_WAIT_SHARED 3`
- L27 _macro_ `#define ULF_WAKE_ALL 0x00000100`
- L30 _macro_ `#define ULF_NO_ERRNO 0x01000000`
- L33 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Private/UbaEventWin32.inl` (Private)


#### struct `uba::EventWin32`  
`struct EventWin32 : EventHeader`  
_L7-54_
- inherits: `EventHeader`
- L9 _public member_ `HANDLE m_handle;`
- L11 _public function_ `bool Create(EventResetType rt, bool = true)`
- L18 _public function_ `void Destroy()`
- L24 _public function_ `void Set()`
- L29 _public function_ `void Reset()`
- L34 _public function_ `bool IsSet(u32 timeOutMs)`
- L39 _public function_ `bool Create(StringView name, bool isOwner)`
- L45 _public function_ `void ToString(StringBufferBase& out)`
- L50 _public function_ `void* GetHandle()`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaAlgorithm.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L13 _function_ `template<typename It, typename T, typename Cmp> inline It LowerBound(It first, It last, const T& value, Cmp cmp)` (scope `uba`) — Minimal std::lower_bound replacement. Returns the first `it` in [first, last) for which `cmp(*it, value)` is false. Requires random-access iterators.
- L27 _function_ `template<typename It, typename T> inline It LowerBound(It first, It last, const T& value)` (scope `uba`)
- L29 _function_ `return LowerBound(first, last, value, [](const auto& a, const auto& b) { return a < b; });` (scope `uba::LowerBound`)
- L34 _function_ `template<typename It, typename T, typename Cmp> inline bool BinarySearch(It first, It last, const T& value, Cmp cmp)` (scope `uba`) — Minimal std::binary_search replacement. Returns true if `value` is present.
- L41 _function_ `template<typename It, typename T> inline bool BinarySearch(It first, It last, const T& value)` (scope `uba`)
- L43 _function_ `return BinarySearch(first, last, value, [](const auto& a, const auto& b) { return a < b; });` (scope `uba::BinarySearch`)
- L48 _namespace_ `namespace detail` (scope `uba`)
- L51 _function_ `template<typename It, typename Cmp> inline void InsertionSort(It first, It last, Cmp cmp)` (scope `uba::detail`)
- L67 _function_ `template<typename It, typename Cmp> inline void QuickSort(It first, It last, Cmp cmp)` (scope `uba::detail`)
- L106 _function_ `template<typename It, typename Cmp> inline void Sort(It first, It last, Cmp cmp)` (scope `uba`)
- L112 _function_ `template<typename It> inline void Sort(It first, It last)` (scope `uba`)
- L114 _function_ `Sort(first, last, [](const auto& a, const auto& b) { return a < b; });` (scope `uba::Sort`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaApplicationRules.h` (Public)


#### class `uba::GlobalRules`  
`class GlobalRules`  
_L9-14_
- L12 _public prototype_ `bool FileCanBeCompressed(const StringView& fileName);`
- L13 _public prototype_ `u8 GetUsedCountBeforeFree(const StringView& fileName);`

#### enum `uba::DependencyCrawlerType`  
`enum DependencyCrawlerType`  
_L19-26_
- L21 _public enumerator_ `DependencyCrawlerType_None`
- L22 _public enumerator_ `DependencyCrawlerType_ClangCompiler`
- L23 _public enumerator_ `DependencyCrawlerType_MsvcCompiler`
- L24 _public enumerator_ `DependencyCrawlerType_ClangLinker`
- L25 _public enumerator_ `DependencyCrawlerType_MsvcLinker`

#### class `uba::ApplicationRules`  
`class ApplicationRules`  
_L29-226_
- L34 _public function_ `virtual bool AllowDetach() const` — This means that process can run entirely without console. (win32 flag DETACHED_PROCESS) Uba stub out console interaction. This is an optimization that is entirely optional
- L40 _public function_ `virtual bool CanDetour(StringView file, bool isRunningRemote) const` — Control if certain files should not be detoured
- L46 _public function_ `virtual bool IsThrowAway(StringView fileName, bool isRunningRemote) const` — Throw-away means that the file is temporary and will not be used after process exists. (By default these are kept in memory and never touch disk)
- L53 _public function_ `virtual bool KeepInMemory(StringView fileName, StringView systemTemp, bool isRunningRemote, bool isWrite) const` — Keep file in memory If this returns true it means that file will be kept in memory and never touch disk.
- L61 _public function_ `virtual u64 FileTypeMaxSize(const StringView& file, bool isSystemOrTempFile) const` — Max file size if using memory files. Setting this value to a proper size is important because of Wine on linux use this .. on windows this size can be very big since it is just virtual address space and nothing is committed... On wine (as of version 9.10) a ftruncate is done on the wine server causing large max sizes to take up actual disk space on the tmp partition
- L67 _public function_ `virtual u32 FileTypeCommitSize(StringView file) const` — When writing this type of file, how big commits should shared memory system take. We want as few as possible without wasting memory
- L73 _public function_ `virtual bool IsOutputFile(StringView fileName, StringView systemTemp) const` — Outputfile means that it is kept in memory and then sent back to session process which can decide to write it to disk or send it over network
- L79 _public function_ `virtual bool KeepTempOutputFile(const StringView& fileName) const` — In general, output files in temp are dropped and never gets written to disk or networked to host.
- L85 _public function_ `virtual bool IsInvisible(const StringView& fileName) const` — Useful when sending files back that is never read by any processes spawned by uba (keep internal tables smaller)
- L91 _public function_ `virtual bool CanExist(StringView file) const` — If returns false this means that all GetFileAttribute etc will return file-not-found on this file
- L98 _public function_ `virtual bool IsRarelyRead(const StringView& file) const` — Return true if the file is only read by this process or very rarely read more than once This is an optimization to not store the file in the mapping table since it will not be read again and would just take up space
- L105 _public function_ `virtual bool IsMaybeReadAfterWritten(const StringView& fileName) const` — Return true if the file is never/rarely read after it was written. This is an optimization where the written file is not kept in file mappings after written
- L110 _public function_ `virtual bool AllowStorageProxy(const StringView& file) const`
- L116 _public function_ `virtual bool AllowMiMalloc() const` — Process is allowed to detour crt allocator and use mimalloc
- L122 _public function_ `virtual bool AllowLoadLibrary(const tchar* libraryName) const` — Can be used to disallow libraries we don't want loaded
- L131 _public function_ `virtual bool SuppressLogLine(const tchar* logLine, u32 logLineLen) const` — Silently suppress log lines. Use this to prevent log lines from be marshalled over from detoured process to session and
- L137 _public function_ `virtual bool IsExitCodeSuccess(u32 exitCode) const` — Return true if exit code is a success for this application
- L143 _public function_ `virtual void RepairMalformedLibPath(const tchar* path) const` — Attempt to work around bugs in pvs studio producing malformed lib paths
- L149 _public function_ `virtual bool IsCacheable() const` — Is used by uba scheduler to decide if application can be cached.
- L154 _public function_ `virtual bool CanDependOnCompressedFiles()`
- L160 _public function_ `virtual bool SendFileCompressedFromClient(const StringView& fileName) const` — Return false if we for example know file sent from client is already compressed (no need to compress again)
- L167 _public function_ `virtual bool ShouldExtractSymbols(const StringView& fileName) const` — Return true if uba should attempt to extract symbols from produced file (Used when compiling and extracing symbols from obj files)
- L173 _public function_ `virtual const tchar* const* LibrariesToPreload() const` — Preload if libraries. This is used to prevent deadlocks in combination with mimalloc also loading modules
- L179 _public function_ `virtual bool ShouldDevirtualizeFile(const StringView& fileName, bool& outEscapeSpaces) const` — Returns true if produced file should be devirtualized (paths are turned into local paths)
- L184 _public function_ `virtual DependencyCrawlerType GetDependencyCrawlerType() const`
- L189 _public function_ `virtual bool ReportAllExceptions() const`
- L197 _public function_ `virtual bool CloseFileMappingAfterUse(StringView fileName) const` — Return true if process should be allowed to close file mappings of files after used. For example, when linker is done with obj files they are likely never used again so we can unmap them. .. but if we have both .lib and .dll creation we might end up unmap just to remap obj files (and if they are compressed that means decompressing twice)
- L203 _public function_ `virtual bool SupportsPlaceholder(StringView fileName) const` — Files that can be written as placeholders if WritePlaceholders is enabled
- L208 _public function_ `virtual bool SupportsRacing() const`
- L215 _public function_ `virtual bool ShouldWriteFilesBeforeWaitOnExit() const` — Return true if we allow file writes to happen before process has been exited by the kernel This is useful for processes that has tons of file mappings open and take a long time to exit
- L220 _public function_ `virtual bool Time64AlwaysReturnZero() const`
- L225 _public member_ `u32 index = ~0u;`

#### struct `uba::RulesRec`  
`struct RulesRec`  
_L229-229_
- L229 _public member_ `struct RulesRec { u32 hash; ApplicationRules* rules; };`
- L229 _public member_ `struct RulesRec { u32 hash; ApplicationRules* rules; };`

#### enum `uba::SpecialRulesIndex`  
`enum SpecialRulesIndex`  
_L234-239_
- L236 _public enumerator_ `SpecialRulesIndex_ClExe = 2`
- L237 _public enumerator_ `SpecialRulesIndex_LinkExe = 3`
- L238 _public enumerator_ `SpecialRulesIndex_LdExePlatform1 = 15`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L16 _externvar_ `extern GlobalRules g_globalRules;` (scope `uba`)
- L231 _prototype_ `const RulesRec* GetApplicationRules();` (scope `uba`)
- L232 _prototype_ `u32 GetApplicationHash(const StringView& str);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaBase.h` (Public)


#### struct `uba::Guid`  
`struct Guid`  
_L27-31_
- L29 _public member_ `u32 data1 = 0;`
- L29 _public member_ `u32 data1 = 0;`
- L29 _public member_ `u32 data1 = 0;`
- L29 _public member_ `u32 data1 = 0;`
- L30 _public function_ `bool operator==(const Guid& o) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UBA_STUB_BUILD 0`
- L19 _namespace_ `namespace uba`
- L21 _typedef_ `using u8 = unsigned char;` (scope `uba`)
- L22 _typedef_ `using u16 = unsigned short;` (scope `uba`)
- L23 _typedef_ `using u32 = unsigned int;` (scope `uba`)
- L24 _typedef_ `using u64 = unsigned long long;` (scope `uba`)
- L25 _typedef_ `using s64 = long long;` (scope `uba`)
- L33 _function_ `template<class T> const T& Min(const T& a, const T& b)` (scope `uba`)
- L34 _function_ `template<class T> const T& Min(const T& a, const T& b)` (scope `uba`)
- L37 _variable_ `inline constexpr bool IsWindows = true;` (scope `uba`)
- L38 _variable_ `inline constexpr bool IsLinux = false;` (scope `uba`)
- L39 _variable_ `inline constexpr bool IsMac = false;` (scope `uba`)
- L40 _typedef_ `using tchar = wchar_t;` (scope `uba`)
- L41 _macro_ `#define TC(x) L##x`
- L42 _macro_ `#define PERCENT_HS L"%hs"`
- L44 _variable_ `inline constexpr bool IsWindows = false;` (scope `uba`)
- L45 _variable_ `inline constexpr bool IsLinux = PLATFORM_LINUX != 0;` (scope `uba`)
- L46 _variable_ `inline constexpr bool IsMac = !IsLinux;` (scope `uba`)
- L47 _typedef_ `using tchar = char;` (scope `uba`)
- L48 _macro_ `#define TC(x) x`
- L49 _macro_ `#define PERCENT_HS "%s"`
- L53 _macro_ `#define PLATFORM_CPU_X86_FAMILY 1`
- L55 _macro_ `#define PLATFORM_CPU_X86_FAMILY 0`
- L59 _macro_ `#define PLATFORM_CPU_ARM_FAMILY 1`
- L61 _macro_ `#define PLATFORM_CPU_ARM_FAMILY 0`
- L65 _variable_ `inline constexpr bool IsArmBinary = true;` (scope `uba`)
- L67 _variable_ `inline constexpr bool IsArmBinary = false;` (scope `uba`)
- L74 _variable_ `inline constexpr u32 CacheLineSize = 64;` (scope `uba`)
- L79 _macro_ `#define UBA_API __declspec(dllimport)`
- L81 _macro_ `#define UBA_API __attribute__((weak))`
- L83 _macro_ `#define UBA_API`
- L88 _macro_ `#define UBA_LIFETIMEBOUND [[clang::lifetimebound]]`
- L90 _macro_ `#define UBA_LIFETIMEBOUND [[msvc::lifetimebound]]`
- L92 _macro_ `#define UBA_LIFETIMEBOUND`
- L96 _macro_ `#define UBA_ASSUME(expr) __builtin_assume(expr)`
- L98 _macro_ `#define UBA_ASSUME(expr) __assume(expr)`
- L100 _macro_ `#define UBA_ASSUME(expr) ((void)0)`
- L104 _macro_ `#define UBA_ANALYZER_SUPPRESS [[clang::suppress]]`
- L106 _macro_ `#define UBA_ANALYZER_SUPPRESS`
- L109 _macro_ `#define UBA_USE_PARKINGLOT !PLATFORM_MAC`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaBinaryParser.h` (Public)
_(no declarations extracted)_

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaBinaryReaderWriter.h` (Public)


#### enum `uba::ProcessCommunication`  
`enum ProcessCommunication`  
_L13-13_
- L13 _public enumerator_ `enum ProcessCommunication { ProcessCommunication_Write }; template<typename CharType> inline u64 GetUtf8WrittenBytes(const CharType* str, u64 strlen); inline u8 Get7BitEncodedCount(u64 value); inline u64 GetStringWriteSize(const tchar* str, u64 len);`

#### struct `uba::BinaryWriter`  
`struct BinaryWriter`  
_L22-82_
- L24 _public prototype_ `inline void WriteByte(u8 value);`
- L25 _public prototype_ `inline void WriteBytes(const void* data, u64 size);`
- L27 _public prototype_ `inline void WriteU16(u16 value);`
- L28 _public prototype_ `inline void WriteU32(u32 value);`
- L29 _public prototype_ `inline void WriteU64(u64 value);`
- L30 _public prototype_ `inline void WriteString(const tchar* str);`
- L31 _public prototype_ `inline void WriteString(const tchar* str, u64 len);`
- L32 _public prototype_ `inline void WriteString(const StringView& str);`
- L33 _public prototype_ `inline void WriteStringf(const tchar* format, ...);`
- L34 _public prototype_ `inline void WriteString(const TString& str);`
- L35 _public prototype_ `inline void WriteStringKey(const StringKey& g);`
- L36 _public prototype_ `inline void WriteGuid(const Guid& g);`
- L37 _public prototype_ `inline void WriteCasKey(const CasKey& casKey);`
- L38 _public prototype_ `inline void Write7BitEncoded(u64 value);`
- L39 _public function_ `inline void WriteBool(bool value)`
- L42 _public prototype_ `template<typename CharType> inline void WriteUtf8String(const CharType* str, u64 len);`
- L44 _public prototype_ `void WriteLongString(const StringView& str, u32 threshold = 10000);`
- L57 _public prototype_ `void WriteLongString(const PreparedLongString& prepared);`
- L59 _public prototype_ `bool WriteBytesCompressed(const void* data, u64 size, bool assertOnFail = true);`
- L61 _public function_ `inline void WriteFileTime(u64 fileTime)`
- L62 _public function_ `inline void WriteFileAttributes(u32 attributes)`
- L63 _public function_ `inline void WriteVolumeSerial(u32 volumeSerial)`
- L64 _public function_ `inline void WriteFileIndex(u64 fileIndex)`
- L65 _public function_ `inline void WriteFileSize(u64 fileSize)`
- L67 _public prototype_ `inline u8* AllocWrite(u64 bytes);`
- L68 _public function_ `inline u64 GetPosition() const`
- L69 _public function_ `inline u64 GetCapacityLeft() const`
- L70 _public function_ `inline u8* GetData() const`
- L71 _public function_ `inline void ChangeData(u8* newData, u64 newCapacity = InvalidValue)`
- L72 _public function_ `inline void Reset(u8* data, u64 offset = 0, u64 capacity = InvalidValue)`
- L73 _public function_ `inline BinaryWriter(u8* data, u64 offset = 0, u64 capacity = InvalidValue)`
- L75 _public prototype_ `BinaryReader Flush(bool waitOnResponse = true);`
- L76 _public prototype_ `BinaryWriter(ProcessCommunication);`
- L79 _protected member_ `u8* m_begin;`
- L80 _protected member_ `u8* m_pos;`
- L81 _protected member_ `u8* m_end;`
- L197 _function_ `void BinaryWriter::WriteByte(u8 value)`
- L204 _function_ `void BinaryWriter::WriteBytes(const void* data, u64 size)`
- L211 _function_ `void BinaryWriter::WriteString(const tchar* str)`
- L218 _function_ `template<typename CharType> void BinaryWriter::WriteUtf8String(const CharType* str, u64 len)`
- L243 _function_ `void BinaryWriter::WriteString(const tchar* str, u64 len)`
- L257 _function_ `void BinaryWriter::WriteString(const StringView& str)`
- L262 _function_ `void BinaryWriter::WriteStringf(const tchar* format, ...)`
- L273 _function_ `void BinaryWriter::WriteString(const TString& str)`
- L278 _function_ `void BinaryWriter::WriteGuid(const Guid& g)`
- L287 _function_ `void BinaryWriter::WriteStringKey(const StringKey& key)`
- L295 _function_ `void BinaryWriter::WriteCasKey(const CasKey& key)`
- L304 _function_ `void BinaryWriter::WriteU32(u32 value)`
- L311 _function_ `void BinaryWriter::WriteU16(u16 value)`
- L318 _function_ `void BinaryWriter::WriteU64(u64 value)`
- L325 _function_ `void BinaryWriter::Write7BitEncoded(u64 value)`
- L336 _function_ `u8* BinaryWriter::AllocWrite(u64 bytes)`

#### struct `uba::BinaryWriter::PreparedLongString`  
`struct PreparedLongString`  
_L49-56_
- desc: Pre-encoded form for callers that need to know the on-wire size before writing (e.g. slot reservation in lock-free ring buffers). The constructor compresses when needed; GetWriteSize then returns the exact byte count.
- L51 _public prototype_ `PreparedLongString(const StringView& s, u32 threshold = 10000);`
- L52 _public prototype_ `u64 GetWriteSize() const;`
- L54 _public member_ `StringView str;`
- L55 _public member_ `Vector<u8> compressedBuffer;` — Empty -> short-string path (length below threshold).

#### struct `uba::StackBinaryWriter`  
`template<u32 Capacity> struct StackBinaryWriter : BinaryWriter`  
_L85-90_
- inherits: `BinaryWriter`
- L87 _public function_ `StackBinaryWriter() : BinaryWriter(buffer, 0, Capacity)`
- L88 _public function_ `StackBinaryWriter& Reset()`
- L89 _public member_ `u8 buffer[Capacity];`

#### struct `uba::BinaryReader`  
`struct BinaryReader`  
_L94-142_
- L96 _public prototype_ `inline void ReadBytes(void* data, u64 size);`
- L97 _public prototype_ `inline u8 ReadByte();`
- L98 _public prototype_ `inline u16 ReadU16();`
- L99 _public prototype_ `inline u32 ReadU32();`
- L100 _public prototype_ `inline u64 ReadU64();`
- L101 _public prototype_ `inline u64 ReadString(tchar* str, u64 strCapacity);`
- L102 _public prototype_ `inline void ReadString(StringBufferBase& out);`
- L103 _public prototype_ `inline TString ReadString();`
- L104 _public prototype_ `inline void SkipString();`
- L105 _public prototype_ `inline StringKey ReadStringKey();`
- L106 _public prototype_ `inline Guid ReadGuid();`
- L107 _public prototype_ `inline CasKey ReadCasKey();`
- L108 _public function_ `inline bool ReadBool()`
- L109 _public prototype_ `inline u64 Read7BitEncoded();`
- L110 _public prototype_ `template<typename CharType> inline CharType ReadUtf8Char();`
- L111 _public prototype_ `template<typename CharType> inline CharType ReadUtf8Char();`
- L112 _public prototype_ `void ReadBytesCompressed(void* outData, u64 outCapacity);`
- L114 _public function_ `inline u64 ReadFileTime()`
- L115 _public function_ `inline u32 ReadFileAttributes()`
- L116 _public function_ `inline u32 ReadVolumeSerial()`
- L117 _public function_ `inline u64 ReadFileIndex()`
- L118 _public function_ `inline u64 ReadFileSize()`
- L120 _public prototype_ `inline bool TryRead7BitEncoded(u64& outValue);`
- L121 _public prototype_ `inline bool TryReadString(StringBufferBase& out);`
- L122 _public prototype_ `inline u32 PeekU32();`
- L123 _public prototype_ `inline u64 PeekU64();`
- L124 _public function_ `inline void Skip(u64 size)`
- L125 _public function_ `inline u64 GetPosition() const`
- L126 _public function_ `inline u64 GetLeft() const`
- L127 _public function_ `inline void SetPosition(u64 pos)`
- L128 _public function_ `inline void SetSize(u64 size)`
- L129 _public function_ `inline const u8* GetPositionData()`
- L130 _public function_ `inline BinaryReader(const u8* data, u64 offset = 0, u64 size = InvalidValue)`
- L131 _public function_ `inline BinaryReader(const Vector<u8>& data, u64 offset = 0)`
- L134 _protected prototype_ `inline u64 InternalReadString(tchar* str, u64 charLen);`
- L135 _protected prototype_ `inline void InternalSkipString(u64 charLen);`
- L136 _protected member_ `const u8* m_begin;`
- L137 _protected member_ `const u8* m_pos;`
- L138 _protected member_ `const u8* m_end;`
- L141 _private prototype_ `BinaryReader() = delete;`
- L346 _function_ `void BinaryReader::ReadBytes(void* data, u64 size)`
- L354 _function_ `u8 BinaryReader::ReadByte()`
- L360 _function_ `u16 BinaryReader::ReadU16()`
- L368 _function_ `u32 BinaryReader::ReadU32()`
- L376 _function_ `u64 BinaryReader::ReadU64()`
- L384 _function_ `u64 BinaryReader::ReadString(tchar* str, u64 strCapacity)`
- L397 _function_ `u64 BinaryReader::InternalReadString(tchar* str, u64 charLen)`
- L446 _function_ `void BinaryReader::InternalSkipString(u64 charLen)`
- L478 _function_ `void BinaryReader::ReadString(StringBufferBase& out)`
- L483 _function_ `TString BinaryReader::ReadString()`
- L492 _function_ `void BinaryReader::SkipString()`
- L498 _function_ `Guid BinaryReader::ReadGuid()`
- L508 _function_ `StringKey BinaryReader::ReadStringKey()`
- L518 _function_ `CasKey BinaryReader::ReadCasKey()`
- L529 _function_ `u64 BinaryReader::Read7BitEncoded()`
- L547 _function_ `bool BinaryReader::TryRead7BitEncoded(u64& outValue)`
- L567 _function_ `bool BinaryReader::TryReadString(StringBufferBase& out)`
- L620 _function_ `template<typename CharType> CharType BinaryReader::ReadUtf8Char()`
- L647 _function_ `u32 BinaryReader::PeekU32()`
- L652 _function_ `u64 BinaryReader::PeekU64()`

#### struct `uba::StackBinaryReader`  
`template<u32 Capacity> struct StackBinaryReader : BinaryReader`  
_L145-150_
- inherits: `BinaryReader`
- L147 _public function_ `StackBinaryReader() : BinaryReader(buffer, 0, Capacity)`
- L148 _public function_ `StackBinaryReader& Reset()`
- L149 _public member_ `u8 buffer[Capacity];`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L16 _prototype_ `template<typename CharType> inline u64 GetUtf8WrittenBytes(const CharType* str, u64 strlen);` (scope `uba`)
- L17 _prototype_ `inline u8 Get7BitEncodedCount(u64 value);` (scope `uba`)
- L18 _prototype_ `inline u64 GetStringWriteSize(const tchar* str, u64 len);` (scope `uba`)
- L154 _macro_ `#define UBA_ASSERT_WRITE(size) UBA_ASSERTF(m_pos + size <= m_end, TC("BinaryWriter overflow. Written: %llu, Capacity: %llu, Trying to write: %zu"), u64(m_pos - m_begin), u64(m_end - m_begin), size_t(size))`
- L155 _macro_ `#define UBA_ASSERT_READ(size) UBA_ASSERTF(m_pos + size <= m_end, TC("BinaryReader overflow. Addr: 0x%llx Offset: %llu, Size: %llu, Trying to read: %zu"), u64(m_begin), u64(m_pos - m_begin), u64(m_end - m_begin), size_t(size))`
- L158 _function_ `template<typename CharType> inline u64 GetUtf8WrittenBytes(const CharType* str, u64 strlen)` (scope `uba`)
- L174 _function_ `inline u8 Get7BitEncodedCount(u64 value)` (scope `uba`)
- L185 _function_ `inline u64 GetStringWriteSize(const tchar* str, u64 len)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaCompressedFileHeader.h` (Public)


#### struct `uba::CompressedFileHeader`  
`struct CompressedFileHeader`  
_L9-22_
- L11 _public member_ `inline static constexpr u8 Magic[] = { 'U', 'B', 'A', 0x01 };`
- L13 _public function_ `CompressedFileHeader(const CasKey& key) : casKey(key)`
- L18 _public function_ `bool IsValid() const`
- L20 _public member_ `u8 magic[sizeof(Magic)];`
- L21 _public member_ `CasKey casKey;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaCorePch.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `namespace std` (scope `std`)
- L9 _namespace_ `namespace std`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define UBA_USE_NATIVE_MAC_SEMAPHORES 0//PLATFORM_MAC` — Use native mach semaphores for IPC.
- L10 _macro_ `#define UBA_DISABLE_PTHREAD_CANCELLATIONS 1` — Disable pthread cancellation to reduce work when waking up from event. No uba code should rely on cancelling threads and shutdown is gracefully so this can be disabled
- L13 _macro_ `#define UBA_TEST_WINDOWS_SEMAPHORES 0` — Enable this to test semaphore implementation for local events
- L16 _macro_ `#define UBA_DEBUG_FILE_MAPPING 0` — Enable to add logging of file mappings
- L18 _macro_ `#define UBA_PROTOCOL_GUARD 0`
- L21 _macro_ `#define UBA_SUPPORTS_GO PLATFORM_LINUX && !PLATFORM_CPU_ARM_FAMILY` — Need special binary patching to be able to hook Go applications on Linux. Only works for non-static applications.
- L23 _macro_ `#define UBA_SUPPORT_SYMLINKS !PLATFORM_WINDOWS`
- L25 _macro_ `#define UBA_CATCH_NTREAD_EXCEPTIONS 0`
- L27 _namespace_ `namespace uba`
- L29 _variable_ `inline constexpr bool EventIsNative = bool(PLATFORM_WINDOWS && !UBA_TEST_WINDOWS_SEMAPHORES);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaDetoursPayload.h` (Public)


#### struct `uba::DetoursPayload`  
`struct __declspec(uuid("{a1041c70-bf7c-4e94-8f8b-bacf0f31ba9a}")) DetoursPayload`  
_L12-35_
- L14 _public member_ `HANDLE hostProcess = 0;`
- L15 _public member_ `HANDLE cancelEvent = 0;`
- L16 _public member_ `HANDLE writeEvent = 0;`
- L17 _public member_ `HANDLE readEvent = 0;`
- L18 _public member_ `u64 communicationHandle = 0;`
- L19 _public member_ `u64 communicationOffset = 0;`
- L20 _public member_ `u32 version = 0;`
- L21 _public member_ `u32 rulesIndex = 0;`
- L22 _public member_ `bool runningRemote = false;`
- L23 _public member_ `bool useCustomAllocator = true;`
- L24 _public member_ `bool isRunningWine = false;`
- L25 _public member_ `bool isChild = false;`
- L26 _public member_ `bool allowLazyCopyOnWrite = false;`
- L27 _public member_ `bool allowKeepFilesInMemory = IsWindows;`
- L28 _public member_ `bool allowOutputFiles = IsWindows;`
- L29 _public member_ `bool allowDiscardVirtualMemory = false;`
- L30 _public member_ `bool suppressLogging = false;`
- L31 _public member_ `bool readIntermediateFilesCompressed = false;`
- L32 _public member_ `bool reportAllExceptions = false;`
- L33 _public member_ `int uiLanguage = 0;`
- L34 _public member_ `StringBuffer<512> logFile;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L37 _variable_ `static const _GUID DetoursPayloadGuid = __uuidof(DetoursPayload);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaDirectoryTable.h` (Public)


#### enum `uba::(anonymous)`  
`enum : u64`  
_L50-50_
- desc: Important that it is zero to compress enc7 as good as possible

#### enum `uba::(anonymous)`  
`enum : u32`  
_L51-51_

#### enum `uba::(anonymous)`  
`enum : u32`  
_L52-52_

#### struct `uba::DirTableSize`  
`struct DirTableSize`  
_L54-54_
- L54 _public member_ `struct DirTableSize { u32 main = 0; u32 overlay = 0; };`
- L54 _public member_ `struct DirTableSize { u32 main = 0; u32 overlay = 0; };`

#### struct `uba::DirTableOffset`  
`struct DirTableOffset`  
_L58-58_
- L58 _public member_ `struct DirTableOffset { u32 internal = InvalidTableOffset; };`

#### class `uba::DirectoryTable`  
`class DirectoryTable`  
_L65-174_
- L92 _public typedef_ `using EntryLookup = UnorderedMap<StringKey, DirTableOffset, std::hash<StringKey>, std::equal_to<StringKey>, GrowingAllocator, BucketAllocator, u32>;`
- L105 _public typedef_ `using DirLookup = UnorderedMap<StringKey, Directory, std::hash<StringKey>, std::equal_to<StringKey>, GrowingAllocator, BucketAllocator, u32>;`
- L107 _public prototype_ `inline void Init(const u8* mem, u32 tableCount, u32 tableSize);`
- L108 _public prototype_ `inline void InitOverlay(const u8* mem, u32 tableSize);`
- L109 _public prototype_ `inline void DeinitOverlay();`
- L110 _public prototype_ `inline void ParseDirectoryTable(DirTableSize size);`
- L111 _public prototype_ `inline void ParseDirectoryTableNoLock(DirTableSize size);`
- L112 _public prototype_ `inline void ParseDirectoryTableNoLock(const u8* memory, u32 from, u32 to, u32 isOverlayFlag);`
- L113 _public prototype_ `inline void PopulateDirectory(const StringKeyHasher& hasher, Directory& dir);`
- L114 _public prototype_ `inline bool IsDirectoryUpToDate(Directory& dir);`
- L115 _public prototype_ `inline void PopulateDirectoryNoLock(const StringKeyHasher& hasher, Directory& dir);`
- L116 _public prototype_ `inline BinaryReader GetReader(u32 tableOffset);`
- L117 _public prototype_ `inline void PopulateDirectoryRecursive(const StringKeyHasher& hasher, u32 latestOffset, u32 populatedOffset, EntryLookup& files, u32 isOverlayFlag);`
- L118 _public prototype_ `inline void PopulateDirectoryWithFiles(BinaryReader& reader, const StringKeyHasher& hasher, EntryLookup& files, u32 isOverlayFlag);`
- L130 _public prototype_ `inline Exists EntryExists(StringKey entryKey, StringView entryName, bool checkIfDir = false, DirTableOffset* outTableOffset = nullptr);` — When checkIfDir is true these functions will search for the offset where a directory stores its files. It is only useful when the intention is to traverse files inside the dir. NOTE, even if checkIfDir is true you can still get back a normal "file entry" representing the dir. "IsDirectoryEntry(tableOffset)" can be used to check which one it is
- L131 _public prototype_ `inline Exists EntryExistsNoLock(StringKey entryKey, StringView entryName, bool checkIfDir = false, DirTableOffset* outTableOffset = nullptr);`
- L132 _public prototype_ `inline Exists EntryExists(StringView str, bool checkIfDir = false, DirTableOffset* outTableOffset = nullptr);`
- L143 _public prototype_ `inline u32 GetAttributes(DirTableOffset tableOffset);`
- L144 _public prototype_ `inline u32 GetEntryInformation(EntryInformation& outInfo, DirTableOffset tableOffset, tchar* outFileName = nullptr, u32 fileNameCapacity = 0);`
- L145 _public prototype_ `inline bool GetEntrySymlink(StringBufferBase& out, DirTableOffset tableOffset);`
- L146 _public prototype_ `inline void GetFinalPath(StringBufferBase& out, const tchar* path);`
- L147 _public prototype_ `inline bool GetRealPath(StringBufferBase& out, const tchar* path, u32 maxLinkDepth = 40);`
- L148 _public prototype_ `inline bool GetLatestOffset(DirTableOffset& out, const Directory& dir);`
- L149 _public prototype_ `inline bool ContainsFile(const StringKeyHasher& hasher, Directory& dir, StringKey fileNameKey);`
- L153 _public prototype_ `template<typename Func> inline void TraverseOriginalFilesNoPopulate(DirTableOffset tableOffset, const Func& func);` — This function only traverses the entries that was in the original populate and does not populate the lookup table. Can be used for scenarios where we know we only want the files that existed before the session started and not files that were added while active
- L156 _public prototype_ `template<typename Func> inline void TraverseFilesRecursiveNoLock(StringView path, const Func& func);` — Func is (const DirectoryTable::EntryInformation& info, StringView fileName, DirTableOffset fileOffset)
- L157 _public prototype_ `template<typename Func> inline void TraverseFilesRecursiveNoLock(StringView path, const Func& func);` — Func is (const DirectoryTable::EntryInformation& info, StringView fileName, DirTableOffset fileOffset)
- L159 _public prototype_ `inline DirectoryTable(MemoryBlock& block);`
- L160 _public prototype_ `DirectoryTable(const DirectoryTable&) = delete;`
- L161 _public prototype_ `void operator=(const DirectoryTable&) = delete;`
- L162 _public function_ `inline bool IsOverlayOffset(u32 offset)`
- L164 _public member_ `MemoryBlock& m_memoryBlock;`
- L165 _public member_ `ReaderWriterLock m_lookupLock;`
- L166 _public member_ `DirLookup m_lookup;`
- L168 _public member_ `ReaderWriterLock m_memoryLock;`
- L169 _public member_ `const u8* m_memory = nullptr;`
- L170 _public member_ `u32 m_memorySize = 0;`
- L172 _public member_ `const u8* m_overlayMemory = nullptr;`
- L173 _public member_ `u32 m_overlaySize = 0;`
- L178 _function_ `void DirectoryTable::Init(const u8* mem, u32 tableCount, u32 tableSize)`
- L186 _function_ `void DirectoryTable::InitOverlay(const u8* mem, u32 tableSize)`
- L193 _function_ `void DirectoryTable::DeinitOverlay()`
- L230 _function_ `void DirectoryTable::ParseDirectoryTable(DirTableSize size)`
- L236 _function_ `void DirectoryTable::ParseDirectoryTableNoLock(DirTableSize size)`
- L250 _function_ `void DirectoryTable::ParseDirectoryTableNoLock(const u8* memory, u32 from, u32 to, u32 isOverlayFlag)`
- L269 _function_ `void DirectoryTable::PopulateDirectory(const StringKeyHasher& hasher, Directory& dir)`
- L275 _function_ `bool DirectoryTable::IsDirectoryUpToDate(Directory& dir)`
- L280 _function_ `void DirectoryTable::PopulateDirectoryNoLock(const StringKeyHasher& hasher, Directory& dir)`
- L294 _function_ `BinaryReader DirectoryTable::GetReader(u32 tableOffset)`
- L302 _function_ `void DirectoryTable::PopulateDirectoryRecursive(const StringKeyHasher& hasher, u32 latestOffset, u32 populatedOffset, EntryLookup& files, u32 isOverlayFlag)`
- L358 _function_ `void DirectoryTable::PopulateDirectoryWithFiles(BinaryReader& reader, const StringKeyHasher& hasher, EntryLookup& files, u32 isOverlayFlag)`
- L401 _function_ `DirectoryTable::Exists DirectoryTable::EntryExists(StringKey entryKey, StringView entryName, bool checkIfDir, DirTableOffset* outTableOffset)`
- L407 _function_ `DirectoryTable::Exists DirectoryTable::EntryExistsNoLock(StringKey entryKey, StringView entryName, bool checkIfDir, DirTableOffset* outTableOffset)`
- L492 _function_ `DirectoryTable::Exists DirectoryTable::EntryExists(StringView str, bool checkIfDir, DirTableOffset* outTableOffset)`
- L502 _function_ `u32 DirectoryTable::GetAttributes(DirTableOffset tableOffset)`
- L520 _function_ `u32 DirectoryTable::GetEntryInformation(EntryInformation& outInfo, DirTableOffset tableOffset, tchar* outFileName, u32 fileNameCapacity)`
- L574 _function_ `bool DirectoryTable::GetEntrySymlink(StringBufferBase& out, DirTableOffset tableOffset)`
- L593 _function_ `void DirectoryTable::GetFinalPath(StringBufferBase& out, const tchar* path)`
- L663 _function_ `bool DirectoryTable::GetRealPath(StringBufferBase& out, const tchar* path, u32 maxLinkDepth)`
- L827 _function_ `bool DirectoryTable::GetLatestOffset(DirTableOffset& out, const Directory& dir)`
- L842 _function_ `bool DirectoryTable::ContainsFile(const StringKeyHasher& hasher, Directory& dir, StringKey fileNameKey)`
- L855 _function_ `template<typename Func> void DirectoryTable::TraverseOriginalFilesNoPopulate(DirTableOffset tableOffset, const Func& func)`
- L901 _function_ `template<typename Func> void DirectoryTable::TraverseFilesRecursiveNoLock(StringView path, const Func& func)`
- L925 _function_ `template<typename Func> void DirectoryTable::TraverseAllFilesNoLock(const Func& func)`
- L939 _function_ `DirectoryTable::DirectoryTable(MemoryBlock& block) : m_memoryBlock(block) , m_lookup(block, block)`

#### struct `uba::DirectoryTable::BucketAllocator`  
`struct BucketAllocator : Allocator`  
_L71-90_
- inherits: `Allocator`
- desc: m_block==nullptr -> system heap (used by snapshot builder so per-build rehashes free their old bucket arrays); m_block set -> bump-allocate from the mapping arena.
- L73 _public function_ `void* Allocate(u64 size, u64 align)`
- L82 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L87 _public function_ `BucketAllocator() : m_block(nullptr)`
- L88 _public function_ `BucketAllocator(MemoryBlock& b) : m_block(&b)`
- L89 _public member_ `MemoryBlock* m_block;`

#### struct `uba::DirectoryTable::Directory`  
`struct Directory`  
_L94-103_
- L96 _public function_ `Directory(MemoryBlock& block) : files(block, block)`
- L97 _public member_ `u32 latestOffset = InvalidTableOffset;`
- L98 _public member_ `u32 populatedOffset = InvalidTableOffset;`
- L99 _public member_ `u32 latestOverlayOffset = InvalidTableOffset;`
- L100 _public member_ `u32 populatedOverlayOffset = InvalidTableOffset;`
- L101 _public member_ `EntryLookup files;`
- L102 _public member_ `ReaderWriterLock lock;`

#### enum `uba::DirectoryTable::Exists`  
`enum Exists`  
_L120-125_
- L122 _public enumerator_ `Exists_Yes`
- L123 _public enumerator_ `Exists_No`
- L124 _public enumerator_ `Exists_Maybe`

#### struct `uba::DirectoryTable::EntryInformation`  
`struct EntryInformation`  
_L134-141_
- L136 _public member_ `u32 attributes = 0;`
- L137 _public member_ `u32 volumeSerial = 0;`
- L138 _public member_ `u64 fileIndex = 0;`
- L139 _public member_ `u64 size = 0;`
- L140 _public member_ `u64 lastWrite = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define WRITE_DEBUG(format, ...) \`
- L21 _namespace_ `namespace uba`
- L50 _enumerator_ `enum : u64 { InvalidTableOffset = 0 }; enum : u32 { OverlayTableFlag = 0x10000000 }; enum : u32 { DirectoryEntryFlag = 0x80000000 }; struct DirTableSize { u32 main = 0; u32 overlay = 0; }; inline DirTableSize FromU64(u64 v) { return {u32(v), u32(v >> 32u)}; } inline u64 ToU64(DirTableSize size) { return size.main + (u64(size.overlay) << 32llu); }` (scope `uba::__anonb47e9a8c0103`) — Important that it is zero to compress enc7 as good as possible
- L51 _enumerator_ `enum : u32 { OverlayTableFlag = 0x10000000 }; enum : u32 { DirectoryEntryFlag = 0x80000000 }; struct DirTableSize { u32 main = 0; u32 overlay = 0; }; inline DirTableSize FromU64(u64 v) { return {u32(v), u32(v >> 32u)}; } inline u64 ToU64(DirTableSize size) { return size.main + (u64(size.overlay) << 32llu); } struct DirTableOffset { u32 internal = InvalidTableOffset; };` (scope `uba::__anonb47e9a8c0203`)
- L52 _enumerator_ `enum : u32 { DirectoryEntryFlag = 0x80000000 }; struct DirTableSize { u32 main = 0; u32 overlay = 0; }; inline DirTableSize FromU64(u64 v) { return {u32(v), u32(v >> 32u)}; } inline u64 ToU64(DirTableSize size) { return size.main + (u64(size.overlay) << 32llu); } struct DirTableOffset { u32 internal = InvalidTableOffset; }; inline bool IsDirectoryEntry(DirTableOffset d) { return (d.internal & DirectoryEntryFlag) != 0; }` (scope `uba::__anonb47e9a8c0303`)
- L55 _function_ `inline DirTableSize FromU64(u64 v)` (scope `uba`)
- L56 _function_ `inline u64 ToU64(DirTableSize size)` (scope `uba`)
- L59 _function_ `inline bool IsDirectoryEntry(DirTableOffset d)` (scope `uba`)
- L60 _function_ `inline bool IsValidEntry(DirTableOffset d)` (scope `uba`)
- L61 _function_ `inline bool IsOverlayOffset(DirTableOffset d)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaElf.h` (Public)


#### struct `uba::Elf64FileHeader`  
`struct Elf64FileHeader`  
_L9-25_
- L11 _public member_ `unsigned char e_ident[16];` — Magic number and other info
- L12 _public member_ `u16 e_type;` — Object file type
- L13 _public member_ `u16 e_machine;` — Architecture
- L14 _public member_ `u32 e_version;` — Object file version
- L15 _public member_ `u64 e_entry;` — Entry point virtual address
- L16 _public member_ `u64 e_phoff;` — Program header table file offset
- L17 _public member_ `u64 e_shoff;` — Section header table file offset
- L18 _public member_ `u32 e_flags;` — Processor-specific flags
- L19 _public member_ `u16 e_ehsize;` — ELF header size in bytes
- L20 _public member_ `u16 e_phentsize;` — Program header table entry size
- L21 _public member_ `u16 e_phnum;` — Program header table entry count
- L22 _public member_ `u16 e_shentsize;` — Section header table entry size
- L23 _public member_ `u16 e_shnum;` — Section header table entry count
- L24 _public member_ `u16 e_shstrndx;` — Section header string table index

#### struct `uba::Elf64ProgramHeader`  
`struct Elf64ProgramHeader`  
_L33-43_
- L35 _public member_ `u32 p_type;` — Segment type
- L36 _public member_ `u32 p_flags;` — Segment flags
- L37 _public member_ `u64 p_offset;` — Offset in file
- L38 _public member_ `u64 p_vaddr;` — Virtual address in memory
- L39 _public member_ `u64 p_paddr;` — Physical address (ignored)
- L40 _public member_ `u64 p_filesz;` — Size of segment in file
- L41 _public member_ `u64 p_memsz;` — Size of segment in memory
- L42 _public member_ `u64 p_align;` — Alignment

#### struct `uba::Elf64SectionHeader`  
`struct Elf64SectionHeader`  
_L45-57_
- L47 _public member_ `u32 sh_name;` — Section name (string tbl index)
- L48 _public member_ `u32 sh_type;` — Section type
- L49 _public member_ `u64 sh_flags;` — Section flags
- L50 _public member_ `u64 sh_addr;` — Section virtual addr at execution
- L51 _public member_ `u64 sh_offset;` — Section file offset
- L52 _public member_ `u64 sh_size;` — Section size in bytes
- L53 _public member_ `u32 sh_link;` — Link to another section
- L54 _public member_ `u32 sh_info;` — Additional section information
- L55 _public member_ `u64 sh_addralign;` — Section alignment
- L56 _public member_ `u64 sh_entsize;` — Entry size if section holds table

#### struct `uba::Elf64Dyn`  
`struct Elf64Dyn`  
_L68-76_
- L70 _public member_ `s64 d_tag;` — Dynamic entry type
- L75 _public member_ `} d_un;` — u64  d_ptr;    Address value

#### union `uba::Elf64Dyn::(anonymous)`  
``  
_L72-75_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L27 _variable_ `inline const constexpr char* ELFMAG = "\1` (scope `uba`)
- L28 _variable_ `inline constexpr int SELFMAG = 4;` (scope `uba`)
- L29 _variable_ `inline constexpr int EI_CLASS = 4;` (scope `uba`)
- L30 _variable_ `inline constexpr int ELFCLASS32 = 1;` (scope `uba`)
- L31 _variable_ `inline constexpr int ELFCLASS64 = 2;` (scope `uba`)
- L59 _variable_ `inline constexpr int SHT_PROGBITS = 1;` (scope `uba`) — Program data
- L60 _variable_ `inline constexpr int SHT_SYMTAB = 2;` (scope `uba`) — Symbol table
- L61 _variable_ `inline constexpr int SHT_STRTAB = 3;` (scope `uba`)
- L62 _variable_ `inline constexpr int SHT_RELA = 4;` (scope `uba`) — Relocation entries with addends
- L63 _variable_ `inline constexpr int SHT_DYNAMIC = 6;` (scope `uba`) — Dynamic linking information
- L64 _variable_ `inline constexpr int SHT_REL = 9;` (scope `uba`) — Relocation entries, no addends
- L65 _variable_ `inline constexpr int SHT_DYNSYM = 11;` (scope `uba`) — Dynamic linker symbol table
- L66 _variable_ `inline constexpr int SHT_SYMTAB_SHNDX = 18;` (scope `uba`) — Extended section indeces
- L73 _member_ `u64 d_val;` (scope `uba::Elf64Dyn::__anona395f7e6010a`)
- L74 _member_ `u64 d_ptr;` (scope `uba::Elf64Dyn::__anona395f7e6010a`) — u64 d_val;    Integer value
- L78 _typedef_ `using Elf64Addr = u64;` (scope `uba`)
- L79 _typedef_ `using Elf64Off = u64;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaEvent.h` (Public)


#### enum `uba::EventResetType`  
`enum EventResetType : u8`  
_L16-20_
- L18 _public enumerator_ `EventResetType_Auto`
- L19 _public enumerator_ `EventResetType_Manual`

#### class `uba::Event`  
`class Event`  
_L24-43_
- L27 _public prototype_ `Event() = default;`
- L28 _public prototype_ `Event(EventResetType resetType);`
- L29 _public prototype_ `~Event();`
- L30 _public prototype_ `bool Create(EventResetType resetType);`
- L31 _public prototype_ `void Destroy();`
- L32 _public prototype_ `void Set();`
- L33 _public prototype_ `void Reset();`
- L34 _public prototype_ `bool IsCreated();`
- L35 _public prototype_ `bool IsSet(u32 timeOutMs = ~0u);`
- L36 _public prototype_ `void* GetHandle();`
- L37 _public prototype_ `static bool IsNative();`
- L38 _public prototype_ `static void ClearCache();`
- L40 _private member_ `void* m_impl = nullptr;`
- L41 _private prototype_ `Event(const Event&) = delete;`
- L42 _private prototype_ `void operator=(const Event&) = delete;`

#### class `uba::SharedEvent`  
`class SharedEvent`  
_L47-70_
- L50 _public prototype_ `SharedEvent();`
- L51 _public prototype_ `~SharedEvent();`
- L52 _public prototype_ `bool Create(EventResetType resetType);`
- L53 _public prototype_ `bool Create(StringView name, bool isOwner);`
- L54 _public prototype_ `void Destroy();`
- L55 _public prototype_ `void Set();`
- L56 _public prototype_ `bool IsSet(u32 timeOutMs = ~0u);`
- L57 _public prototype_ `void ToString(StringBufferBase& out);`
- L58 _public prototype_ `void* GetHandle();`
- L60 _private prototype_ `bool IsSemaphore();`
- L62 _private member_ `u64 m_data[16];`
- L64 _private member_ `u64 m_data[13];`
- L66 _private member_ `u64 m_data[2];`
- L68 _private prototype_ `SharedEvent(const SharedEvent&) = delete;`
- L69 _private prototype_ `void operator=(const SharedEvent&) = delete;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L78 _namespace_ `namespace uba`
- L81 _typedef_ `using EventSlim = EventWaitOnAddress;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaEventWaitOnAddress.inl` (Public)


#### struct `uba::EventWaitOnAddress`  
`struct alignas(4) EventWaitOnAddress`  
_L11-98_
- L13 _public member_ `Atomic<u32> m_state;`
- L14 _public member_ `EventResetType m_resetType;`
- L16 _public prototype_ `EventWaitOnAddress() = default;`
- L17 _public function_ `EventWaitOnAddress(EventResetType rt)`
- L19 _public function_ `bool Create(EventResetType rt)`
- L27 _public function_ `void Set()`
- L36 _public function_ `void Reset()`
- L41 _public function_ `bool IsSet(u32 timeoutMs = ~0u)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFileHandle.h` (Public)


#### enum `uba::FileHandle`  
`enum FileHandle : u64`  
_L11-11_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L12 _variable_ `inline constexpr FileHandle InvalidFileHandle = (FileHandle)-1;` (scope `uba`)
- L14 _variable_ `inline constexpr u64 FileHandleFlagMask = 0x0000'0000'ffff'ffff;` (scope `uba`)
- L19 _typedef_ `typedef void *HANDLE;` (scope `uba`)
- L20 _function_ `inline HANDLE AsHANDLE(FileHandle fh)` (scope `uba`)
- L22 _function_ `inline int AsFileDescriptor(FileHandle fh)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFileMapping.h` (Public)


#### enum `uba::MemoryMapType`  
`enum MemoryMapType`  
_L40-40_
- desc: LazyCopyOnWrite: like CopyOnWrite but on Windows the view is mapped read-only so it does not eagerly charge commit for the whole view. Pages are flipped to copy-on-write on the first write fault by a vectored exception handler (see RegisterLazyCowRange in the detour), so commit tracks only the pages the tool actually dirties. On POSIX it is identical to CopyOnWrite (MAP_PRIVATE already commits lazily on write fault).
- L40 _public enumerator_ `enum MemoryMapType { MemoryMapType_ReadOnly, MemoryMapType_ReadWrite, MemoryMapType_CopyOnWrite, MemoryMapType_LazyCopyOnWrite }; FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint); FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 flProtect, u64 maxSize, const fmchar* hint); u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 dwDesiredAccess, u64 offset, u64 dwNumberOfBytesToMap, bool allowDiscard = false); bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard = false); bool FileMapping_Unmap(Logger& logger, const void* lpBaseAddress, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard = false); bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint);` — LazyCopyOnWrite: like CopyOnWrite but on Windows the view is mapped read-only so it does not eagerly charge commit for the whole view. Pages are flipped to copy-on-write on the first write fault by a vectored exception handler (see RegisterLazyCowRange in the detour), so commit tracks only the pages the tool actually dirties. On POSIX it is identical to CopyOnWrite (MAP_PRIVATE already commits lazily on write fault).
- L40 _public enumerator_ `enum MemoryMapType { MemoryMapType_ReadOnly, MemoryMapType_ReadWrite, MemoryMapType_CopyOnWrite, MemoryMapType_LazyCopyOnWrite }; FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint); FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 flProtect, u64 maxSize, const fmchar* hint); u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 dwDesiredAccess, u64 offset, u64 dwNumberOfBytesToMap, bool allowDiscard = false); bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard = false); bool FileMapping_Unmap(Logger& logger, const void* lpBaseAddress, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard = false); bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint);` — LazyCopyOnWrite: like CopyOnWrite but on Windows the view is mapped read-only so it does not eagerly charge commit for the whole view. Pages are flipped to copy-on-write on the first write fault by a vectored exception handler (see RegisterLazyCowRange in the detour), so commit tracks only the pages the tool actually dirties. On POSIX it is identical to CopyOnWrite (MAP_PRIVATE already commits lazily on write fault).
- L40 _public enumerator_ `enum MemoryMapType { MemoryMapType_ReadOnly, MemoryMapType_ReadWrite, MemoryMapType_CopyOnWrite, MemoryMapType_LazyCopyOnWrite }; FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint); FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 flProtect, u64 maxSize, const fmchar* hint); u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 dwDesiredAccess, u64 offset, u64 dwNumberOfBytesToMap, bool allowDiscard = false); bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard = false); bool FileMapping_Unmap(Logger& logger, const void* lpBaseAddress, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard = false); bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint);` — LazyCopyOnWrite: like CopyOnWrite but on Windows the view is mapped read-only so it does not eagerly charge commit for the whole view. Pages are flipped to copy-on-write on the first write fault by a vectored exception handler (see RegisterLazyCowRange in the detour), so commit tracks only the pages the tool actually dirties. On POSIX it is identical to CopyOnWrite (MAP_PRIVATE already commits lazily on write fault).
- L40 _public enumerator_ `enum MemoryMapType { MemoryMapType_ReadOnly, MemoryMapType_ReadWrite, MemoryMapType_CopyOnWrite, MemoryMapType_LazyCopyOnWrite }; FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint); FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 flProtect, u64 maxSize, const fmchar* hint); u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 dwDesiredAccess, u64 offset, u64 dwNumberOfBytesToMap, bool allowDiscard = false); bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard = false); bool FileMapping_Unmap(Logger& logger, const void* lpBaseAddress, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard = false); bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint);` — LazyCopyOnWrite: like CopyOnWrite but on Windows the view is mapped read-only so it does not eagerly charge commit for the whole view. Pages are flipped to copy-on-write on the first write fault by a vectored exception handler (see RegisterLazyCowRange in the detour), so commit tracks only the pages the tool actually dirties. On POSIX it is identical to CopyOnWrite (MAP_PRIVATE already commits lazily on write fault).

#### struct `uba::FileMappingBackend`  
`struct FileMappingBackend`  
_L80-89_
- L87 _public member_ `bool linuxBackend = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L13 _typedef_ `using fmchar = UBA_FM_STRING_TYPE;` (scope `uba`)
- L15 _typedef_ `using fmchar = tchar;` (scope `uba`)
- L21 _variable_ `inline constexpr u32 FILE_MAP_WRITE = 0x0002;` (scope `uba`)
- L22 _variable_ `inline constexpr u32 FILE_MAP_READ = 0x0004;` (scope `uba`)
- L23 _variable_ `inline constexpr u32 FILE_MAP_ALL_ACCESS = FILE_MAP_WRITE | FILE_MAP_READ;` (scope `uba`)
- L24 _variable_ `inline constexpr u32 SEC_RESERVE = 0x04000000;` (scope `uba`)
- L25 _variable_ `inline constexpr u32 PAGE_READONLY = PROT_READ;` (scope `uba`)
- L26 _variable_ `inline constexpr u32 PAGE_READWRITE = PROT_READ | PROT_WRITE;` (scope `uba`)
- L29 _variable_ `inline constexpr u32 SHM_MAX_FILENAME = PSHMNAMLEN;` (scope `uba`)
- L31 _variable_ `inline constexpr u32 SHM_MAX_FILENAME = 38;` (scope `uba`)
- L42 _prototype_ `FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint);` (scope `uba`)
- L43 _prototype_ `FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 flProtect, u64 maxSize, const fmchar* hint);` (scope `uba`)
- L44 _prototype_ `u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 dwDesiredAccess, u64 offset, u64 dwNumberOfBytesToMap, bool allowDiscard = false);` (scope `uba`)
- L45 _prototype_ `bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard = false);` (scope `uba`)
- L46 _prototype_ `bool FileMapping_Unmap(Logger& logger, const void* lpBaseAddress, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard = false);` (scope `uba`)
- L47 _prototype_ `bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint);` (scope `uba`)
- L48 _prototype_ `void* FileMapping_ReservePlaceholder(void* baseAddress, u64 capacity);` (scope `uba`)
- L49 _prototype_ `void* FileMapping_MapPlaceholder(FileMappingHandle handle, MemoryMapType mapType, void* targetAddress, u64 targetOffset, u64 targetCapacity, u64 handleOffset, u64 size);` (scope `uba`)
- L50 _prototype_ `bool FileMapping_UnmapPlaceholder(void* memory, u64 capacity, u64 mappedSize, u64* subMappings, u64 subMappingsCount);` (scope `uba`)
- L51 _prototype_ `void FileMapping_CopyMem(void* dest, const void* source, u64 size);` (scope `uba`)
- L53 _prototype_ `FileMappingHandle FileMapping_DuplicateFromHost(FileMappingHandle handle, const char* hint);` (scope `uba`)
- L54 _prototype_ `u8* FileMapping_MapFromHost(FileMappingHandle handle, u64 size, u64 offset, bool writable, const char* hint);` (scope `uba`)
- L55 _prototype_ `u8* FileMapping_MapFromHost2(FileMappingHandle handle, u64 size, u64 offset, MemoryMapType mapType, void* targetAddress, const char* hint);` (scope `uba`)
- L58 _prototype_ `bool FileMapping_ResolveBacking(Logger& logger, const fmchar* preferredDir, u64 shmFloorBytes, char* outEnv = nullptr, int outEnvCap = 0);` (scope `uba`) — Pick memfd/shm/disk backing once before any mapping is created (Linux). outEnv gets the env var to inject into children.
- L59 _externvar_ `extern char g_fileMappingBackingEnv[512];` (scope `uba`) — ResolveBacking's choice; the session injects it into children
- L64 _macro_ `#define UBA_FM_FUNCTIONS \`
- L82 _macro_ `#define UBA_FM_FUNC(func) decltype(FileMapping_##func)* func = FileMapping_##func;`
- L92 _prototype_ `bool FileMapping_GetWineBackend(FileMappingBackend& out, Logger& logger, HMODULE wineDll);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFileMapping.inl` (Public)


#### struct `FileMapping_ResolveBackingUnix::(anonymous)`  
`struct`  
_L494-494_
- desc: raw statfs avoids needing <sys/vfs.h> across the many .inl includers

#### Free symbols / members of external scopes

- L7 _macro_ `#define UBA_USE_MEMFD 0 // PLATFORM_LINUX — This does not work cross linux namespaces`
- L22 _variable_ `Bottleneck& g_createFileHandleBottleneck = *new Bottleneck(8);` — Allocated and leaked just to prevent shutdown asserts in debug
- L24 _function_ `HANDLE InternalCreateFileMappingW(Logger& logger, HANDLE hFile, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName, const tchar* hint)`
- L49 _function_ `static void InternalDiscard(Logger& logger, u8* mem, u64 size, const tchar* from, const tchar* hint)`
- L73 _macro_ `#define UBA_NR_OPEN 2`
- L74 _macro_ `#define UBA_NR_CLOSE 3`
- L75 _macro_ `#define UBA_NR_MMAP 9`
- L76 _macro_ `#define UBA_NR_MUNMAP 11`
- L77 _macro_ `#define UBA_NR_GETPID 39`
- L78 _macro_ `#define UBA_NR_FCNTL 72`
- L79 _macro_ `#define UBA_NR_FTRUNCATE 77`
- L80 _macro_ `#define UBA_NR_OPENAT 257`
- L81 _macro_ `#define UBA_NR_UNLINKAT 263`
- L82 _macro_ `#define UBA_NR_MKDIRAT 258`
- L83 _macro_ `#define UBA_NR_STATFS 137`
- L84 _macro_ `#define UBA_NR_FORK 57`
- L85 _macro_ `#define UBA_NR_WAIT4 61`
- L86 _macro_ `#define UBA_NR_EXIT_GROUP 231`
- L87 _macro_ `#define UBA_NR_PRCTL 157`
- L88 _macro_ `#define UBA_NR_MEMFD_CREATE 319`
- L89 _macro_ `#define UBA_NR_PIDFD_OPEN 434`
- L90 _macro_ `#define UBA_NR_PIDFD_GETFD 438`
- L92 _macro_ `#define UBA_NR_UNLINKAT 35`
- L93 _macro_ `#define UBA_NR_FCNTL 25`
- L94 _macro_ `#define UBA_NR_FTRUNCATE 46`
- L95 _macro_ `#define UBA_NR_OPENAT 56`
- L96 _macro_ `#define UBA_NR_CLOSE 57`
- L97 _macro_ `#define UBA_NR_MKDIRAT 34`
- L98 _macro_ `#define UBA_NR_STATFS 43`
- L99 _macro_ `#define UBA_NR_CLONE 220`
- L100 _macro_ `#define UBA_NR_WAIT4 260`
- L101 _macro_ `#define UBA_NR_EXIT_GROUP 94`
- L102 _macro_ `#define UBA_NR_PRCTL 167`
- L103 _macro_ `#define UBA_NR_GETPID 172`
- L104 _macro_ `#define UBA_NR_MUNMAP 215`
- L105 _macro_ `#define UBA_NR_MMAP 222`
- L106 _macro_ `#define UBA_NR_MEMFD_CREATE 279`
- L112 _macro_ `#define UBA_MFD_CLOEXEC 0x0001U`
- L113 _macro_ `#define UBA_PROT_NONE 0x0`
- L114 _macro_ `#define UBA_PROT_READ 0x1`
- L115 _macro_ `#define UBA_PROT_WRITE 0x2`
- L116 _macro_ `#define UBA_MAP_SHARED 0x01`
- L117 _macro_ `#define UBA_MAP_PRIVATE 0x02`
- L118 _macro_ `#define UBA_MAP_FIXED 0x10`
- L119 _macro_ `#define UBA_MAP_ANONYMOUS 0x20`
- L120 _macro_ `#define UBA_MAP_FIXED_NOREPLACE 0x100000`
- L121 _macro_ `#define UBA_AT_FDCWD (-100)`
- L122 _macro_ `#define UBA_O_RDONLY 0x0`
- L123 _macro_ `#define UBA_O_RDWR 0x2`
- L124 _macro_ `#define UBA_O_CLOEXEC 0x80000`
- L125 _macro_ `#define UBA_F_SETFD 2`
- L126 _macro_ `#define UBA_FD_CLOEXEC 1`
- L128 _function_ `inline bool UbaSyscallIsErr(long r)` — mmap-style return: r1 in [-4095, -1] is -errno, anything else is the mapped address.
- L131 _function_ `inline const char* FmBackingDir()` — UBA_FILE_MAPPING_DIR => disk files under it; else /dev/shm. Uncached: ResolveBacking's setenv may run after an early mapping.
- L134 _externvar_ `extern const char* g_ubaFileMappingDir;` (scope `FmBackingDir`) — stub getenv() is a nullptr stub; set by its envp scan
- L143 _function_ `inline bool FmUseMemfd()` — memfd mode for CREATION only. Attach side dispatches on FileMappingHandle::MemfdFlag — the creator's mode travels with the handle, so mixed-mode trees still attach correctly.
- L146 _externvar_ `extern bool g_ubaUseMemfd;` (scope `FmUseMemfd`) — set by the stub's envp scan
- L154 _function_ `inline long FmRawFork()` — arm64 has no fork; clone(SIGCHLD) is the equivalent
- L164 _function_ `inline bool FmMemfdProbe(char* outWhy, int whyCap)` — memfd works only if a child can pidfd_getfd back to us — fork a child that tries it. PR_SET_PTRACER_ANY lifts yama scope=1 (some LSMs still reject). outWhy gets the failing step+errno on false.
- L195 _function_ `inline bool FmBuildShmPath(const char* name, char* out, int outSize)` — "<dir>/uba_NNNN" (disk) or "/dev/shm/uba_NNNN" (shm). Returns true if disk-backed.
- L206 _function_ `inline int FmShmOpen(const char* name, int flags, int mode)`
- L214 _function_ `inline int FmShmUnlink(const char* name)`
- L222 _function_ `inline int FmFcntl(int fd, int cmd, int arg)`
- L228 _function_ `inline int FmClose(int fd)`
- L234 _function_ `inline void* FmMmap(void* addr, u64 size, int prot, int flags, int fd, u64 offset)`
- L240 _function_ `inline int FmMunmap(void* addr, u64 size)`
- L257 _function_ `void AppendPrefixAndValue(char* out, const char* prefix, u64 value, bool addSeparatorAfterPrefix = false)`
- L275 _function_ `void GetMappingHandleName(char* out, u64 uid)`
- L286 _function_ `u64 ParseMappingUid(const char* str)`
- L292 _function_ `auto hexVal = [](char c) -> u8` (scope `ParseMappingUid`)
- L302 _function_ `inline int FmHostShmOpen(const char* leafName, int flags, int mode)` — glibc create/unlink (errno-setting, unlike the raw FmShm* above) that honor UBA_FILE_MAPPING_DIR.
- L313 _function_ `inline int FmHostShmUnlink(const char* leafName)`
- L327 _variable_ `Atomic<u64> g_mappingUidCounter = 0;` — Host-only: shm uid counter + lock-dir GC. The stub never creates shms or runs GC — it just maps existing shm names produced by the host.
- L328 _variable_ `static pthread_mutex_t g_mappingUidCounterLock = PTHREAD_MUTEX_INITIALIZER;`
- L333 _variable_ `char g_lockDirBuf[256];` — /tmp preferred — shared so user B's GC reclaims user A's leaked shms after a crash. XDG_RUNTIME_DIR per-user fallback when /tmp isn't usable (PrivateTmp=yes, sandbox, ro fs). pthread_once over function-local static so this links without libstdc++ (winegcc).
- L334 _variable_ `bool g_lockDirShared = false;`
- L335 _variable_ `pthread_once_t g_lockDirOnce = PTHREAD_ONCE_INIT;`
- L336 _function_ `void InitLockDir()`
- L339 _function_ `` (scope `InitLockDir`)
- L361 _function_ `const char* GetLockDir()`
- L367 _function_ `bool GarbageCollectFileMappings(Logger& logger)`
- L453 _function_ `bool FileMapping_ResolveBackingUnix(Logger& logger, const char* preferredDirUnix, u64 shmFloorBytes, char* outEnv, int outEnvCap)` — outEnv gets the env var the caller injects into children ("UBA_FILE_MAPPING_MEMFD=1"/"..._DIR=<dir>"/"").
- L494 _member_ `struct { u64 w[16]; } sf;` (scope `FileMapping_ResolveBackingUnix::__anondd214e960308`) — raw statfs avoids needing <sys/vfs.h> across the many .inl includers
- L527 _function_ `bool FileMapping_ResolveBacking(Logger& logger, const fmchar* preferredDir, u64 shmFloorBytes, char* outEnv, int outEnvCap)`
- L543 _function_ `FileMappingHandle FileMapping_Create(Logger& logger, u32 flProtect, u64 maxSize, const fmchar* name, const fmchar* hint)`
- L687 _function_ `FileMappingHandle FileMapping_CreateFromFile(Logger& logger, FileHandle file, u32 protect, u64 maxSize, const fmchar* hint)`
- L726 _function_ `u8* FileMapping_Map(Logger& logger, FileMappingHandle fileMappingObject, u32 desiredAccess, u64 offset, u64 bytesToMap, bool allowDiscard)`
- L782 _function_ `bool FileMapping_Commit(Logger& logger, void* address, u64 size, bool allowDiscard)`
- L796 _function_ `bool FileMapping_Unmap(Logger& logger, const void* address, u64 bytesToUnmap, const fmchar* hint, bool allowDiscard)`
- L834 _function_ `bool FileMapping_Close(Logger& logger, FileMappingHandle h, const fmchar* hint)`
- L892 _function_ `void* FileMapping_ReservePlaceholder(void* baseAddress, u64 capacity)`
- L915 _function_ `void* FileMapping_MapPlaceholder(FileMappingHandle handle, MemoryMapType mapType, void* targetAddress, u64 targetOffset, u64 targetCapacity, u64 handleOffset, u64 size)`
- L977 _function_ `bool FileMapping_UnmapPlaceholder(void* memory, u64 capacity, u64 mappedSize, u64* subMappings, u64 subMappingsCount)`
- L1012 _function_ `FileMappingHandle FileMapping_DuplicateFromHost(FileMappingHandle handle, const char* hint)`
- L1071 _function_ `u8* FileMapping_MapFromHost(FileMappingHandle handle, u64 size, u64 offset, bool writable, const char* hint)`
- L1077 _function_ `u8* FileMapping_MapFromHost2(FileMappingHandle handle, u64 size, u64 offset, MemoryMapType mapType, void* targetAddress, const char* hint)`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFileMappingHandle.h` (Public)


#### struct `uba::FileMappingHandle`  
`struct FileMappingHandle`  
_L14-27_
- L16 _public prototype_ `FileMappingHandle() = default;`
- L17 _public function_ `bool operator==(const FileMappingHandle& o) const`
- L18 _public function_ `bool IsValid() const`
- L19 _public function_ `u64 ToU64() const`
- L20 _public function_ `static FileMappingHandle FromU64(u64 v)`
- L22 _public function_ `FileMappingHandle(u64 v)`
- L23 _public member_ `u64 internal = 0;` — HANDLE on windows, uid or tagged (pid,fd) on posix
- L25 _public member_ `int shmFd = -1;` — Unused on windows
- L26 _public member_ `int lockFd = -1;` — Unused on windows

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L32 _function_ `inline HANDLE AsHANDLE(FileMappingHandle h)` (scope `uba`)
- L38 _variable_ `inline constexpr u64 FileMappingMemfdFlag = 1ull << 62;` (scope `uba`) — Linux memfd handles are (creatorPid<<32)|creatorFd plus this tag, so attach-side code can pick the pidfd path per handle instead of trusting process-wide env (which can disagree with the creator's mode, e.g. stale UBA_FILE_MAPPING_MEMFD in a container image). Bit 63 is taken: SharedMemoryAllocator's external-mapping flag is added on top of ToU64().
- L39 _function_ `inline bool IsMemfdHandle(FileMappingHandle h)` (scope `uba`) — ~0ull = caller-owned-fd sentinel

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFileMappingWin.inl` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uba`
- L9 _variable_ `HANDLE g_hostProcess;` (scope `uba`)
- L14 _function_ `bool FileMapping_GetWineBackend(FileMappingBackend& out, Logger& logger, HMODULE wineDll)` (scope `uba`)
- L16 _macro_ `#define UBA_FM_FUNC(func) \`
- L22 _macro_ `#define UBA_FM_FUNC(func) out.func = func##Func;`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaFunctional.h` (Public)


#### class `uba::Function`  
`template<typename R, typename... Args> class Function<R (Args...)>`  
_L15-107_
- L41 _public prototype_ `Function() = default;`
- L42 _public function_ `Function(decltype(nullptr))`
- L51 _public function_ `Function(F&& f) : m_impl(new Callable<std::decay_t<F>>(std::forward<F>(f)))`
- L53 _public function_ `Function(const Function& o) : m_impl(o.m_impl ? o.m_impl->Clone() : nullptr)`
- L55 _public function_ `Function(Function&& o) noexcept : m_impl(o.m_impl)`
- L57 _public function_ `~Function()`
- L59 _public function_ `Function& operator=(const Function& o)`
- L69 _public function_ `Function& operator=(Function&& o) noexcept`
- L80 _public function_ `Function& operator=(decltype(nullptr))`
- L91 _public function_ `Function& operator=(F&& f)`
- L98 _public function_ `explicit operator bool() const`
- L100 _public function_ `R operator()(Args... args) const`
- L106 _private member_ `CallableBase* m_impl = nullptr;`

#### struct `uba::Function::CallableBase`  
`struct CallableBase`  
_L17-22_
- L19 _public prototype_ `virtual ~CallableBase() = default;`
- L20 _public prototype_ `virtual R Invoke(Args... args) = 0;`
- L21 _public prototype_ `virtual CallableBase* Clone() const = 0;`

#### struct `uba::Function::Callable`  
`template<typename F> struct Callable : CallableBase`  
_L25-38_
- inherits: `CallableBase`
- L27 _public member_ `F fn;`
- L29 _public function_ `template<typename G> explicit Callable(G&& g) : fn(std::forward<G>(g))`
- L30 _public function_ `R Invoke(Args... args) override`
- L37 _public function_ `CallableBase* Clone() const override`

#### class `uba::FunctionWithContext`  
`template <typename ReturnType, typename... ArgTypes> class FunctionWithContext<ReturnType (ArgTypes...)>`  
_L116-182_
- L119 _public typedef_ `using FunctionType = ReturnType (void*, ArgTypes...);`
- L122 _public function_ `template <typename CallableType> inline FunctionWithContext(CallableType&& callable UBA_LIFETIMEBOUND) requires (!std::is_same_v<std::decay_t<CallableType>, FunctionWithContext>) && std::is_invocable_r_v<ReturnType, std::decay_t<CallableType>, ArgTypes...> : function(&Call<std::decay_t<CallableType>>) , context(&callable)`
- L131 _public function_ `template <typename CallableType> inline FunctionWithContext& operator=(CallableType&& callable UBA_LIFETIMEBOUND) requires (!std::is_same_v<std::decay_t<CallableType>, FunctionWithContext>) && std::is_invocable_r_v<ReturnType, std::decay_t<CallableType>, ArgTypes...>`
- L140 _public function_ `inline explicit FunctionWithContext(FunctionType* inFunction, void* inContext) : function(inFunction) , context(inContext)`
- L146 _public function_ `inline constexpr FunctionWithContext(decltype(nullptr))`
- L150 _public function_ `inline explicit operator bool() const`
- L155 _public function_ `inline ReturnType operator()(ArgTypes... args) const`
- L160 _public function_ `inline FunctionType* GetFunction() const`
- L165 _public function_ `inline void* GetContext() const`
- L172 _private function_ `template <typename CallableType> static ReturnType Call(void* callable, ArgTypes... args)`
- L180 _private member_ `FunctionType* function = nullptr;`
- L181 _private member_ `void* context = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaHash.h` (Public)


#### struct `uba::StringKey`  
`struct StringKey`  
_L14-22_
- L16 _public function_ `constexpr StringKey(u64 a_ = 0, u64 b_ = 0) : a(a_), b(b_)`
- L17 _public member_ `u64 a;`
- L18 _public member_ `u64 b;`
- L19 _public function_ `bool operator==(const StringKey& o) const`
- L20 _public function_ `bool operator!=(const StringKey& o) const`
- L21 _public function_ `bool operator<(const StringKey& o) const`

#### struct `uba::CasKey`  
`struct CasKey`  
_L27-37_
- L29 _public function_ `constexpr CasKey() : a(0), b(0), c(0)`
- L30 _public function_ `constexpr CasKey(u64 a_, u64 b_, u32 c_) : a(a_), b(b_), c(c_)`
- L31 _public member_ `u64 a;`
- L32 _public member_ `u64 b;`
- L33 _public member_ `u32 c;`
- L34 _public function_ `bool operator==(const CasKey& o) const`
- L35 _public function_ `bool operator!=(const CasKey& o) const`
- L36 _public function_ `bool operator<(const CasKey& o) const`

#### struct `uba::GuidToString`  
`struct GuidToString : StringView`  
_L49-53_
- inherits: `StringView`
- L51 _public function_ `GuidToString(const Guid& g) : StringView(str, 36)`
- L52 _public member_ `tchar str[37];`

#### struct `uba::KeyToString`  
`struct KeyToString : StringBuffer<33>`  
_L55-58_
- inherits: `StringBuffer<33>`
- L57 _public function_ `KeyToString(const StringKey& key)`

#### struct `uba::HashString`  
`struct HashString`  
_L61-70_
- desc: REMOVE!!
- L63 _public function_ `size_t operator()(const tchar* s) const`

#### struct `uba::EqualString`  
`struct EqualString`  
_L72-78_
- L74 _public function_ `bool operator()(const tchar* a, const tchar* b) const`

#### struct `uba::HashStringNoCase`  
`struct HashStringNoCase`  
_L80-89_
- L82 _public function_ `size_t operator()(const tchar* s) const`

#### struct `uba::EqualStringNoCase`  
`struct EqualStringNoCase`  
_L91-97_
- L93 _public function_ `bool operator()(const tchar* a, const tchar* b) const`

#### struct `uba::StringKeyHasher`  
`struct StringKeyHasher`  
_L99-106_
- L101 _public prototype_ `StringKeyHasher();`
- L102 _public prototype_ `void Update(const StringView& str);`
- L103 _public prototype_ `void Update(const tchar* str, u64 strLen);`
- L104 _public prototype_ `void UpdateNoCheck(const StringView& str);`
- L105 _public member_ `u64 hasher[1912 / sizeof(u64)];`

#### struct `uba::CasKeyHasher`  
`struct CasKeyHasher`  
_L176-181_
- L178 _public prototype_ `CasKeyHasher();`
- L179 _public prototype_ `CasKeyHasher& Update(const void* data, u64 bytes);`
- L180 _public member_ `u64 hasher[1912/sizeof(u64)];`

#### struct `uba::CasKeyString`  
`struct CasKeyString : StringView`  
_L217-221_
- inherits: `StringView`
- L219 _public function_ `CasKeyString(const CasKey& g) : StringView(str, 40)`
- L220 _public member_ `tchar str[41];`

#### struct `uba::BloomFilter`  
`struct BloomFilter`  
_L248-255_
- L250 _public member_ `u8 bytes[128] = { 0 };`
- L252 _public prototype_ `void Add(const StringKey& key);`
- L253 _public prototype_ `bool IsGuaranteedMiss(const StringKey& key) const;`
- L254 _public prototype_ `bool IsEmpty() const;`

#### struct `std::hash`  
`template<> struct std::hash<uba::StringKey>`  
_L259-259_
- desc: template<> struct std::hash<uba::Guid> { size_t operator()(const uba::Guid& g) const { std::hash<uba::u64> hash; return hash(((uba::u64*)&g)[0]) ^ hash(((uba::u64*)&g)[1]); } };
- L259 _public function_ `template<> struct std::hash<uba::StringKey>` — template<> struct std::hash<uba::Guid> { size_t operator()(const uba::Guid& g) const { std::hash<uba::u64> hash; return hash(((uba::u64*)&g)[0]) ^ hash(((uba::u64*)&g)[1]); } };

#### struct `std::hash`  
`template<> struct std::hash<uba::StringKey>`  
_L260-260_
- desc: template<> struct std::hash<uba::Guid> { size_t operator()(const uba::Guid& g) const { std::hash<uba::u64> hash; return hash(((uba::u64*)&g)[0]) ^ hash(((uba::u64*)&g)[1]); } };
- L259 _public function_ `template<> struct std::hash<uba::StringKey>` — template<> struct std::hash<uba::Guid> { size_t operator()(const uba::Guid& g) const { std::hash<uba::u64> hash; return hash(((uba::u64*)&g)[0]) ^ hash(((uba::u64*)&g)[1]); } };

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`
- L23 _variable_ `constexpr StringKey StringKeyZero;` (scope `uba`)
- L40 _variable_ `constexpr CasKey CasKeyZero;` (scope `uba`)
- L41 _variable_ `constexpr CasKey CasKeyInvalid(~0ull, ~0ull, ~0u);` (scope `uba`)
- L44 _function_ `inline void GuidToStr(tchar* out, u32 capacity, const Guid& g)` (scope `uba`) — Use 36+1 characters
- L108 _prototype_ `StringKey ToStringKey(const tchar* str, u64 strLen);` (scope `uba`)
- L109 _prototype_ `StringKey ToStringKeyLower(const tchar* str, u64 strLen);` (scope `uba`)
- L110 _prototype_ `StringKey ToStringKey(const StringView& b);` (scope `uba`)
- L111 _prototype_ `StringKey ToStringKeyLower(const StringView& b);` (scope `uba`)
- L112 _prototype_ `StringKey ToStringKey(const StringKeyHasher& hasher, const tchar* str, u64 strLen);` (scope `uba`)
- L113 _prototype_ `StringKey ToStringKey(const StringKeyHasher& hasher);` (scope `uba`)
- L114 _prototype_ `StringKey ToStringKeyNoCheck(const tchar* str, u64 strLen);` (scope `uba`)
- L115 _prototype_ `StringKey ToStringKeyRaw(const void* data, u64 dataLen);` (scope `uba`)
- L117 _function_ `constexpr inline u64 AlignUp(u64 v, u64 a)` (scope `uba`)
- L118 _variable_ `constexpr u64 InvalidValue = 0x7ffffffff;` (scope `uba`) — ~34gb - the largest number that can 7bit encode to 5 bytes
- L120 _variable_ `constexpr u8 EmptyMask = 0;` (scope `uba`)
- L121 _variable_ `constexpr u8 IsCompressedMask = 1;` (scope `uba`)
- L122 _variable_ `constexpr u8 IsNormalizedMask = 2;` (scope `uba`)
- L123 _variable_ `constexpr u8 IsProxyMask = 4;` (scope `uba`)
- L124 _variable_ `constexpr u8 IsExecutableMask = 8;` (scope `uba`)
- L126 _function_ `inline bool IsCompressed(const CasKey& key)` (scope `uba`)
- L132 _function_ `inline CasKey AsCompressed(const CasKey& key, bool compressed)` (scope `uba`)
- L144 _function_ `inline bool IsExecutable(const CasKey& key)` (scope `uba`) — For posix we need to set +x on file so we track this on the cas key because it is easier in terms of downloading from cache server etc
- L150 _function_ `inline CasKey AsExecutable(const CasKey& key, bool executable)` (scope `uba`)
- L161 _function_ `inline bool IsNormalized(const CasKey& key)` (scope `uba`)
- L167 _function_ `inline CasKey AsNormalized(const CasKey& key, bool normalized)` (scope `uba`)
- L183 _prototype_ `CasKey ToCasKey(const CasKeyHasher& hasher, bool compressed);` (scope `uba`)
- L185 _function_ `inline CasKey CasKeyFromString(const tchar* str)` (scope `uba`)
- L200 _function_ `inline void ToString(tchar* out, int capacity, const CasKey& key)` (scope `uba`)
- L224 _function_ `inline void CheckPath(const StringView& fileName)` (scope `uba`)
- L243 _macro_ `#define CHECK_PATH(path) CheckPath(path);`
- L245 _macro_ `#define CHECK_PATH(path) while (false) {}`
- L263 _function_ `template <class Map> void PrintMapInfo(const char* name, const Map& map)`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaLinuxBinDependencyParser.h` (Public)


#### Free symbols / members of external scopes

- L16 _macro_ `#define TRUE_WRAPPER(func) func`
- L19 _macro_ `#define UBA_FINDIMPORTS_DEBUG 0`
- L21 _namespace_ `namespace uba`
- L23 _variable_ `inline constexpr int PT_LOAD = 1;` (scope `uba`) — Elf64_Phdr	Load segment into memory
- L24 _variable_ `inline constexpr int PT_DYNAMIC = 2;` (scope `uba`) — Elf64_Phdr	Dynamic linker info
- L25 _variable_ `inline constexpr int DT_NULL = 0;` (scope `uba`) — Elf64_Dyn	End marker
- L26 _variable_ `inline constexpr int DT_NEEDED = 1;` (scope `uba`) — Elf64_Dyn	Dependency
- L27 _variable_ `inline constexpr int DT_STRTAB = 5;` (scope `uba`) — Elf64_Dyn	String table address
- L28 _variable_ `inline constexpr int DT_STRSZ = 10;` (scope `uba`) — Elf64_Dyn	String table size
- L29 _variable_ `inline constexpr int DT_RPATH = 15;` (scope `uba`) — Elf64_Dyn	Legacy library path
- L30 _variable_ `inline constexpr int DT_RUNPATH = 29;` (scope `uba`) — Elf64_Dyn	Modern library path
- L33 _namespace_ `namespace linux` (scope `uba`)
- L44 _variable_ `constexpr StringView g_kernelBoundFiles[] = {` (scope `uba::linux`) — Libraries with hard kernel / glibc / host-daemon ABI coupling. These MUST NOT be transferred from coordinator to helper — shipping them across hosts will break when the two sides have different kernel, glibc, or host-service versions (e.g. libutil from glibc 2.39 on a 2.34 helper).
- L76 _variable_ `constexpr StringView g_commonSystemFiles[] = { TCV("libstdc++.so"), TCV("libgcc_s.so"), TCV("libz.so"), TCV("libzstd.so"), TCV("libexpat.so"), TCV("libtinfo.so"), TCV("libdxil.so"),` (scope `uba::linux`) — Libraries that are expected to exist on the helper and are skipped for efficiency, but would not be inherently broken by transfer. If you hit an ABI mismatch on one of these, consider either shipping it bundled with your binary or moving it to g_kernelBoundFiles.
- L111 _function_ `inline bool IsKnownSystemFile(const tchar* fileName)` (scope `uba::linux`)
- L123 _function_ `inline bool ParseBinary(StringView filePath, StringView originalPath, BinaryInfo& outInfo, const Function<void(const tchar* import, bool isKnown, const tchar* const* loaderPaths)>& func, StringBufferBase& outError)` (scope `uba::linux`)
- L136 _function_ `auto closeFileHandle = MakeGuard([&]() { TRUE_WRAPPER(close)(fd); });` (scope `uba::linux::ParseBinary`)
- L146 _function_ `auto unmap = MakeGuard([&]() { munmap(mem, fileSize); });` (scope `uba::linux::ParseBinary`)
- L151 _function_ `auto closeFileHandle = MakeGuard([&]() { ::CloseHandle(fileHandle); });` (scope `uba::linux::ParseBinary`)
- L155 _function_ `auto closeMappingHandle = MakeGuard([&]() { ::CloseHandle(fileMapping); });` (scope `uba::linux::ParseBinary`)
- L159 _function_ `auto unmap = MakeGuard([&]() { ::UnmapViewOfFile(mem); });` (scope `uba::linux::ParseBinary`)
- L175 _function_ `auto vaddr_to_offset = [](Elf64Addr vaddr, Elf64ProgramHeader* phdrs, int phnum) -> Elf64Off` (scope `uba::linux::ParseBinary`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaLinuxRawSyscall.h` (Public)


#### struct `uba::RawSyscallResult`  
`struct RawSyscallResult`  
_L14-14_
- desc: Raw Linux syscall with no glibc involvement (no errno TLS, no wrappers). Safe to call from any thread, including goroutine OS threads that lack a proper glibc TCB (the original motivation for this helper). On error: r1 is -errno (negative), r2 is 0. On success: r1 is the return value, r2 is rdx after syscall (usually 0).
- L14 _public member_ `struct RawSyscallResult { long r1; long r2; };` — Raw Linux syscall with no glibc involvement (no errno TLS, no wrappers). Safe to call from any thread, including goroutine OS threads that lack a proper glibc TCB (the original motivation for this helper). On error: r1 is -errno (negative), r2 is 0. On success: r1 is the return value, r2 is rdx after syscall (usually 0).
- L14 _public member_ `struct RawSyscallResult { long r1; long r2; };` — Raw Linux syscall with no glibc involvement (no errno TLS, no wrappers). Safe to call from any thread, including goroutine OS threads that lack a proper glibc TCB (the original motivation for this helper). On error: r1 is -errno (negative), r2 is 0. On success: r1 is the return value, r2 is rdx after syscall (usually 0).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L15 _function_ `inline RawSyscallResult RawSyscallDirect(long nr, long a1, long a2, long a3, long a4 = 0, long a5 = 0, long a6 = 0)` (scope `uba`)
- L50 _function_ `inline long RawReadlinkat(const char* path, char* buf, unsigned long bufSize)` (scope `uba`) — Stub-safe readlinkat. Both x86_64 and aarch64 have SYS_readlinkat; aarch64 dropped the legacy SYS_readlink, so always use the *at variant with AT_FDCWD.
- L63 _function_ `inline long RawSyscall0(long num)` (scope `uba`) — Arity-keyed wrappers around RawSyscallDirect — discard the rdx component (only mattering for pipe/fork/etc. which write through pointers anyway). Compilers inline RawSyscallDirect into these so the generated code matches a hand-rolled syscall instruction.
- L64 _function_ `inline long RawSyscall1(long num, long a)` (scope `uba`)
- L65 _function_ `inline long RawSyscall3(long num, long a, long b, long c)` (scope `uba`)
- L66 _function_ `inline long RawSyscall6(long num, long a, long b, long c, long d, long e, long f)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaList.h` (Public)


#### class `uba::List`  
`template<typename T, typename NodeAlloc = Allocator> class List`  
_L14-287_
- desc: Minimal std::list replacement: doubly-linked, heap-allocated nodes. Elements never move in memory — pointers/refs/iterators stay valid across insert/erase of other elements.
- L29 _public typedef_ `using value_type = T;`
- L30 _public typedef_ `using size_type = u64;`
- L31 _public typedef_ `using reference = T&;`
- L32 _public typedef_ `using const_reference = const T&;`
- L68 _public function_ `List()`
- L70 _public function_ `List(const List& o)`
- L76 _public function_ `List(List&& o) noexcept`
- L82 _public function_ `~List()`
- L84 _public function_ `List& operator=(const List& o)`
- L94 _public function_ `List& operator=(List&& o) noexcept`
- L100 _public function_ `bool empty() const`
- L101 _public function_ `size_type size() const`
- L103 _public function_ `T& front()`
- L104 _public function_ `const T& front() const`
- L105 _public function_ `T& back()`
- L106 _public function_ `const T& back() const`
- L108 _public function_ `iterator begin()`
- L109 _public function_ `iterator end()`
- L110 _public function_ `const_iterator begin() const`
- L111 _public function_ `const_iterator end() const`
- L112 _public function_ `const_iterator cbegin() const`
- L113 _public function_ `const_iterator cend() const`
- L129 _public function_ `reverse_iterator rbegin()`
- L130 _public function_ `reverse_iterator rend()`
- L132 _public function_ `void clear()`
- L146 _public function_ `template<typename... Args> T& emplace_back(Args&&... args)`
- L155 _public function_ `template<typename... Args> T& emplace_front(Args&&... args)`
- L163 _public function_ `void push_back(const T& v)`
- L164 _public function_ `void push_back(T&& v)`
- L165 _public function_ `void push_front(const T& v)`
- L166 _public function_ `void push_front(T&& v)`
- L168 _public function_ `void pop_back()`
- L177 _public function_ `void pop_front()`
- L186 _public function_ `iterator insert(const_iterator pos, const T& v)`
- L196 _public function_ `template<typename... Args> iterator emplace(const_iterator pos, Args&&... args)` — emplace(pos, args...) — construct in place before `pos`, return iter to new element.
- L204 _public function_ `iterator insert(const_iterator pos, T&& v)`
- L212 _public function_ `iterator erase(const_iterator pos)`
- L222 _public function_ `void swap(List& o) noexcept`
- L254 _private function_ `void init_sentinel()`
- L257 _private function_ `template<typename... Args> Node* create_node(Args&&... args)`
- L264 _private function_ `void destroy_node(Node* n)`
- L270 _private function_ `void link_before(NodeBase* pos, NodeBase* n)`
- L278 _private function_ `void unlink(NodeBase* n)`
- L284 _private member_ `NodeBase m_sentinel{};`
- L285 _private member_ `size_type m_size = 0;`
- L286 _private member_ `NodeAlloc m_alloc;`

#### struct `uba::List::NodeBase`  
`struct NodeBase`  
_L16-20_
- L18 _public member_ `NodeBase* prev;`
- L19 _public member_ `NodeBase* next;`

#### struct `uba::List::Node`  
`struct Node : NodeBase`  
_L21-26_
- inherits: `NodeBase`
- L23 _public member_ `T value;`
- L25 _public function_ `template<typename... Args> Node(Args&&... args) : value(std::forward<Args>(args)...)`

#### class `uba::List::iterator`  
`class iterator`  
_L35-49_
- L38 _public prototype_ `iterator() = default;`
- L39 _public function_ `iterator(NodeBase* n) : m_node(n)`
- L40 _public function_ `T& operator*() const`
- L41 _public function_ `T* operator->() const`
- L42 _public function_ `iterator& operator++()`
- L43 _public function_ `iterator operator++(int)`
- L44 _public function_ `iterator& operator--()`
- L45 _public function_ `iterator operator--(int)`
- L46 _public function_ `bool operator==(const iterator& o) const`
- L47 _public function_ `bool operator!=(const iterator& o) const`
- L48 _public member_ `NodeBase* m_node = nullptr;`

#### class `uba::List::const_iterator`  
`class const_iterator`  
_L51-66_
- L54 _public prototype_ `const_iterator() = default;`
- L55 _public function_ `const_iterator(const NodeBase* n) : m_node(n)`
- L56 _public function_ `const_iterator(iterator it) : m_node(it.m_node)`
- L57 _public function_ `const T& operator*() const`
- L58 _public function_ `const T* operator->() const`
- L59 _public function_ `const_iterator& operator++()`
- L60 _public function_ `const_iterator operator++(int)`
- L61 _public function_ `const_iterator& operator--()`
- L62 _public function_ `const_iterator operator--(int)`
- L63 _public function_ `bool operator==(const const_iterator& o) const`
- L64 _public function_ `bool operator!=(const const_iterator& o) const`
- L65 _public member_ `const NodeBase* m_node = nullptr;`

#### class `uba::List::reverse_iterator`  
`class reverse_iterator`  
_L116-128_
- desc: Minimal reverse iterators (forward-decrementing).
- L119 _public prototype_ `reverse_iterator() = default;`
- L120 _public function_ `reverse_iterator(NodeBase* n) : m_node(n)`
- L121 _public function_ `T& operator*() const`
- L122 _public function_ `T* operator->() const`
- L123 _public function_ `reverse_iterator& operator++()`
- L124 _public function_ `reverse_iterator operator++(int)`
- L125 _public function_ `bool operator==(const reverse_iterator& o) const`
- L126 _public function_ `bool operator!=(const reverse_iterator& o) const`
- L127 _public member_ `NodeBase* m_node = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaMacBinDependencyParser.h` (Public)


#### struct `uba::BinaryInfo`  
`struct BinaryInfo`  
_L18-21_
- L20 _public member_ `u32 minVersion = 0;`

#### struct `uba::ParseBinary::__anon53cdc0c50302::version_min_command`  
`struct version_min_command`  
_L77-77_
- L77 _public member_ `struct version_min_command { u32 cmd; u32 cmdsize; u32 version; u32 sdk; };`
- L77 _public member_ `struct version_min_command { u32 cmd; u32 cmdsize; u32 version; u32 sdk; };`
- L77 _public member_ `struct version_min_command { u32 cmd; u32 cmdsize; u32 version; u32 sdk; };`
- L77 _public member_ `struct version_min_command { u32 cmd; u32 cmdsize; u32 version; u32 sdk; };`

#### Free symbols / members of external scopes

- L13 _macro_ `#define TRUE_WRAPPER(func) func`
- L16 _namespace_ `namespace uba`
- L23 _function_ `inline bool IsKnownSystemFile(const tchar* fileName)` (scope `uba`)
- L28 _function_ `inline bool ParseBinary(const StringView& filePath, const StringView& originalPath, BinaryInfo& outInfo, const Function<void(const tchar* import, bool isKnown, const char* const* loaderPaths)>& func, StringBufferBase& outError)` (scope `uba`)
- L36 _function_ `auto closeFileHandle = MakeGuard([&]() { TRUE_WRAPPER(close)(fd); });` (scope `uba::ParseBinary`)
- L51 _function_ `auto unmap = MakeGuard([&]() { TRUE_WRAPPER(munmap)(mem, fileSize); });` (scope `uba::ParseBinary`)
- L62 _function_ `` (scope `uba::ParseBinary`)
- L73 _function_ `auto g = MakeGuard([&]() { memIt += lc.cmdsize; });` (scope `uba::ParseBinary::__anon53cdc0c50302`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaMemory.h` (Public)


#### struct `uba::Allocator`  
`struct Allocator`  
_L29-39_
- L31 _public prototype_ `Allocator() = default;`
- L32 _public prototype_ `Allocator(const Allocator& o) = default;`
- L33 _public prototype_ `Allocator(Allocator&& o) noexcept = default;`
- L34 _public prototype_ `Allocator& operator=(const Allocator& o) = default;`
- L35 _public prototype_ `Allocator& operator=(Allocator&& o) noexcept = default;`
- L36 _public function_ `void* Allocate(u64 size, u64 align)`
- L37 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L38 _public function_ `bool TryGrowInPlace(void* p, u64 , u64 newSize)`

#### struct `uba::Allocator`  
`struct Allocator`  
_L43-48_
- L31 _public prototype_ `Allocator() = default;`
- L32 _public prototype_ `Allocator(const Allocator& o) = default;`
- L33 _public prototype_ `Allocator(Allocator&& o) noexcept = default;`
- L34 _public prototype_ `Allocator& operator=(const Allocator& o) = default;`
- L35 _public prototype_ `Allocator& operator=(Allocator&& o) noexcept = default;`
- L36 _public function_ `void* Allocate(u64 size, u64 align)`
- L37 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L38 _public function_ `bool TryGrowInPlace(void* p, u64 , u64 newSize)`

#### struct `uba::Allocator`  
`struct Allocator`  
_L50-68_
- L31 _public prototype_ `Allocator() = default;`
- L32 _public prototype_ `Allocator(const Allocator& o) = default;`
- L33 _public prototype_ `Allocator(Allocator&& o) noexcept = default;`
- L34 _public prototype_ `Allocator& operator=(const Allocator& o) = default;`
- L35 _public prototype_ `Allocator& operator=(Allocator&& o) noexcept = default;`
- L36 _public function_ `void* Allocate(u64 size, u64 align)`
- L37 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L38 _public function_ `bool TryGrowInPlace(void* p, u64 , u64 newSize)`

#### struct `uba::MemoryBlock`  
`struct MemoryBlock`  
_L71-97_
- L73 _public prototype_ `MemoryBlock(const tchar* name_, u64 reserveSize_, void* baseAddress_ = nullptr);`
- L74 _public prototype_ `MemoryBlock(const tchar* name_, u8* baseAddress_ = nullptr);`
- L75 _public prototype_ `~MemoryBlock();`
- L76 _public prototype_ `bool Init(u64 reserveSize_, void* baseAddress_ = nullptr, bool useHugePages = false);`
- L77 _public prototype_ `void Deinit();`
- L78 _public prototype_ `void* Allocate(u64 bytes, u64 alignment, const tchar* hint);`
- L79 _public prototype_ `void* AllocateNoLock(u64 bytes, u64 alignment, const tchar* hint, bool lockMemory = false);`
- L80 _public prototype_ `void* CommitNoLock(u64 bytes, const tchar* hint);`
- L84 _public prototype_ `bool TryGrowTail(void* p, u64 oldBytes, u64 newBytes);` — Grow the allocation ending at (p + oldBytes) to newBytes in place. Only succeeds if that allocation sits at the current bump tail; otherwise returns false and the caller must allocate + copy. Used by Vector::reserve to avoid the copy when growing alone.
- L85 _public prototype_ `bool TryGrowTailNoLock(void* p, u64 oldBytes, u64 newBytes);`
- L86 _public prototype_ `void Free(void* p);`
- L87 _public prototype_ `StringView Strdup(const StringView& str);`
- L88 _public prototype_ `tchar* Strdup(const tchar* str);`
- L89 _public prototype_ `void Swap(MemoryBlock& other);`
- L91 _public member_ `Futex lock;`
- L92 _public member_ `u8* memory;`
- L93 _public member_ `u64 reserveSize = 0;`
- L94 _public member_ `u64 writtenSize = 0;`
- L95 _public member_ `u64 committedSize = 0;`
- L96 _public member_ `const tchar* name;`

#### struct `uba::GrowingAllocator`  
`struct GrowingAllocator`  
_L100-109_
- L102 _public function_ `GrowingAllocator(MemoryBlock& block) : m_block(&block)`
- L103 _public function_ `GrowingAllocator(const GrowingAllocator& o) : m_block(o.m_block)`
- L104 _public function_ `GrowingAllocator(GrowingAllocator&& o) noexcept : m_block(o.m_block)`
- L105 _public function_ `void* Allocate(u64 size, u64 align)`
- L106 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L107 _public function_ `bool TryGrowInPlace(void* p, u64 oldSize, u64 newSize)`
- L108 _public member_ `MemoryBlock* m_block;`

#### struct `uba::GrowingAllocatorNoLock`  
`struct GrowingAllocatorNoLock`  
_L111-120_
- L113 _public function_ `GrowingAllocatorNoLock(MemoryBlock* block) : m_block(block)`
- L114 _public function_ `GrowingAllocatorNoLock(const GrowingAllocatorNoLock& o) : m_block(o.m_block)`
- L115 _public function_ `GrowingAllocatorNoLock(GrowingAllocatorNoLock&& o) noexcept : m_block(o.m_block)`
- L116 _public function_ `void* Allocate(u64 size, u64 align)`
- L117 _public function_ `void Deallocate(void* p, u64 size, u64 align)`
- L118 _public function_ `bool TryGrowInPlace(void* p, u64 oldSize, u64 newSize)`
- L119 _public member_ `MemoryBlock* m_block;`

#### struct `uba::BlockAllocator`  
`template<typename Type> struct BlockAllocator`  
_L123-156_
- L126 _public function_ `BlockAllocator(MemoryBlock& memory) : m_memory(memory)`
- L130 _public function_ `void* Allocate()`
- L143 _public function_ `void Free(void* mem)`
- L153 _public member_ `Futex m_lock;`
- L154 _public member_ `MemoryBlock& m_memory;`
- L155 _public member_ `u64 m_nextFree = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define aligned_alloc(a, s) _aligned_malloc(s, a)`
- L15 _macro_ `#define aligned_free(p) _aligned_free(p)`
- L17 _macro_ `#define aligned_free(p) free(p)`
- L20 _namespace_ `namespace uba`
- L25 _function_ `template<typename T> constexpr inline T AlignUp(T arg, uintptr_t alignment)` (scope `uba`)
- L41 _prototype_ `void* StubAllocatorAllocate(u64 bytes, u64 alignment);` (scope `uba`)
- L42 _prototype_ `void StubAllocatorFree(void* p, u64 bytes, u64 alignment);` (scope `uba`)
- L158 _function_ `inline u8 HexToByte(tchar c)` (scope `uba`)
- L165 _variable_ `constexpr tchar g_hexChars[] = TC("012` (scope `uba`)
- L168 _function_ `inline u32 ValueToString(tchar* out, int capacity, u64 value)` (scope `uba`) — TODO: These are backwards but changing would break cas storage
- L185 _function_ `inline u64 StringToValue(const tchar* str, u64 len)` (scope `uba`) — TODO: These are backwards but changing would break cas storage
- L199 _function_ `inline u64 StringToValue2(const tchar* str, u64 len)` (scope `uba`)
- L213 _variable_ `constexpr tchar g_base64Chars[] = TC("012` (scope `uba`)
- L215 _function_ `inline u64 StringToValueBase62(const tchar* str, u64 len)` (scope `uba`)
- L234 _function_ `inline u32 RoundUpPow2(u64 value)` (scope `uba`)
- L247 _prototype_ `bool SupportsHugePages();` (scope `uba`)
- L248 _prototype_ `u64 GetHugePageCount();` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaParkingLot.h` (Public)


#### struct `uba::ParkingLot::WaitState`  
`struct WaitState final`  
_L15-23_
- L18 _public member_ `bool didWait = false;` — Did this thread wait? True only if canWait returned true.
- L20 _public member_ `bool didWake = false;` — Did this wake from a wait? True only if a Wake call woke the thread, false for timeouts.
- L22 _public member_ `u64 wakeToken = 0;` — Optional value that was provided by the callback in WakeOne.

#### struct `uba::ParkingLot::WakeState`  
`struct WakeState final`  
_L25-31_
- L28 _public member_ `bool didWake = false;` — Did a thread wake up?
- L30 _public member_ `bool hasWaitingThreads = false;` — Does the queue MAYBE have another thread waiting on this address?

#### class `uba::ParkingLot::WordMutex`  
`class WordMutex final`  
_L73-94_
- desc: A mutex that is the size of a pointer and does not depend on ParkingLot. Prefer CriticalSection or ReaderWriterLock to WordMutex whenever possible. This mutex is not fair and does not support recursive locking.
- L76 _public prototype_ `constexpr WordMutex() = default;`
- L78 _public prototype_ `WordMutex(const WordMutex&) = delete;`
- L79 _public prototype_ `WordMutex& operator=(const WordMutex&) = delete;`
- L81 _public prototype_ `bool TryEnter();`
- L82 _public prototype_ `void Enter();`
- L83 _public prototype_ `void Leave();`
- L86 _private prototype_ `void EnterSlow();`
- L87 _private prototype_ `void LeaveSlow(u64 currentState);`
- L89 _private member_ `static constexpr u64 isLockedFlag = 1 << 0;`
- L90 _private member_ `static constexpr u64 isQueueLockedFlag = 1 << 1;`
- L91 _private member_ `static constexpr u64 queueMask = ~(isLockedFlag | isQueueLockedFlag);`
- L93 _private member_ `std::atomic<u64> state = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace uba`
- L13 _namespace_ `namespace ParkingLot` (scope `uba`)
- L33 _namespace_ `namespace Private` (scope `uba::ParkingLot`)
- L35 _prototype_ `WaitState Wait(const void* address, bool (*canWait)(void*), void* canWaitContext, void (*beforeWait)(void*), void* beforeWaitContext);` (scope `uba::ParkingLot::Private`)
- L36 _prototype_ `WaitState WaitFor(const void* address, bool (*canWait)(void*), void* canWaitContext, void (*beforeWait)(void*), void* beforeWaitContext, u32 waitTimeMs);` (scope `uba::ParkingLot::Private`)
- L37 _prototype_ `void WakeOne(const void* address, u64 (*onWakeState)(void*, WakeState), void* onWakeStateContext);` (scope `uba::ParkingLot::Private`)
- L41 _function_ `inline WaitState Wait(const void* address, FunctionWithContext<bool ()> canWait, FunctionWithContext<void ()> beforeWait)` (scope `uba::ParkingLot`) — Queue the calling thread to wait if canWait returns true. beforeWait is only called if canWait returns true.
- L47 _function_ `inline WaitState WaitFor(const void* address, FunctionWithContext<bool ()> canWait, FunctionWithContext<void ()> beforeWait, u32 waitTimeMs)` (scope `uba::ParkingLot`) — Queue the calling thread to wait if canWait returns true. beforeWait is only called if canWait returns true.
- L53 _function_ `inline void WakeOne(const void* address, FunctionWithContext<u64 (WakeState)> onWakeState)` (scope `uba::ParkingLot`) — Wake one thread from the queue of threads waiting on the address.
- L59 _prototype_ `WakeState WakeOne(const void* address);` (scope `uba::ParkingLot`) — Wake one thread from the queue of threads waiting on the address.
- L62 _prototype_ `u32 WakeMultiple(const void* address, u32 wakeCount);` (scope `uba::ParkingLot`) — Wake up to wakeCount threads from the queue of threads waiting on the address.
- L65 _prototype_ `u32 WakeAll(const void* address);` (scope `uba::ParkingLot`) — Wake all threads from the queue of threads waiting on the address.

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaPathUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L11 _prototype_ `u32 GetLongPathNameW(const tchar* lpszShortPath, tchar* lpszLongPath, u32 cchBuffer);` (scope `uba`)
- L12 _macro_ `#define Local_GetLongPathNameW GetLongPathNameW`
- L15 _function_ `inline bool IsUncPath(const tchar* path)` (scope `uba`)
- L16 _function_ `inline bool IsUncPath(StringView path)` (scope `uba`)
- L18 _function_ `inline bool FixPath2(const tchar* fileName, u32 fileNameLen, const tchar* workingDir, u64 workingDirCharLen, tchar* buffer, u64 bufferCharCapacity, u32* outBufferCharLen)` (scope `uba`)
- L382 _function_ `inline bool FixPath(const tchar* fileName, const tchar* workingDir, u64 workingDirCharLen, StringBufferBase& buffer)` (scope `uba`)
- L390 _function_ `inline bool FixPath(StringBufferBase& out, StringView fileName, StringView workingDir)` (scope `uba`)
- L398 _function_ `inline bool IsAbsolutePath(const tchar* path)` (scope `uba`)
- L408 _function_ `inline bool IsAbsolutePath(StringView path)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaPlatform.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define WINDOWS_LEAN_AND_MEAN`
- L9 _macro_ `#define NOMINMAX`
- L11 _macro_ `#define WIN32_NO_STATUS`
- L12 _macro_ `#define _WINSOCK_DEPRECATED_NO_WARNINGS`
- L17 _macro_ `#define ANALYSIS_NORETURN __attribute__((analyzer_noreturn))`
- L19 _macro_ `#define ANALYSIS_NORETURN __analysis_noreturn`
- L40 _macro_ `#define ANALYSIS_NORETURN`
- L42 _prototype_ `extern "C" char* getenv(const char* name)` — -ffreestanding strips these from stdlib; shared core references them on dead paths or via stub-local bodies — declare so .cpp compiles.
- L43 _prototype_ `extern "C" void* aligned_alloc(size_t alignment, size_t size)`
- L44 _prototype_ `extern "C" void free(void* ptr)`
- L74 _macro_ `#define ANALYSIS_NORETURN // __attribute__((analyzer_noreturn))`
- L81 _macro_ `#define UBA_EXPERIMENTAL 0`
- L84 _macro_ `#define UBA_FMT_CHECK(Format, ...) do { if (false) { wprintf(Format, ##__VA_ARGS__); } } while(false)`
- L86 _macro_ `#define UBA_FMT_CHECK(Format, ...)`
- L89 _namespace_ `namespace uba`
- L96 _macro_ `#define sizeof_array(array) int(sizeof(array)/sizeof(array[0]))`
- L99 _macro_ `#define UBA_SHIPPING_ASSERT(x) do { if (x) break; uba::UbaAssert(TC(""), __FILE__, __LINE__, #x, true, 543221, nullptr, 0); } while(false)`
- L100 _macro_ `#define UBA_SHIPPING_ASSERTF(x, fmt, ...) do { UBA_FMT_CHECK(fmt, ##__VA_ARGS__); if (x) break; uba::StringBuffer<> _buf; _buf.Appendf(fmt, ##__VA_ARGS__); uba::UbaAssert(_buf.data, __FILE__, __LINE__, #x, true, 543221, nullptr, 0); } while`
- L103 _macro_ `#define UBA_ASSERT(x) UBA_SHIPPING_ASSERT(x)`
- L104 _macro_ `#define UBA_ASSERTF(x, fmt, ...) UBA_SHIPPING_ASSERTF(x, fmt, ##__VA_ARGS__)`
- L105 _macro_ `#define UBA_ASSERT_MESSAGEBOX 0`
- L106 _macro_ `#define UBA_FOR_ASSERT(...) __VA_ARGS__`
- L107 _variable_ `inline constexpr bool IsDebug = true;` (scope `uba`)
- L109 _macro_ `#define UBA_ASSERT(x) do { } while(false)`
- L110 _macro_ `#define UBA_ASSERTF(x, ...) do { } while(false)`
- L112 _macro_ `#define UBA_FOR_ASSERT(...)`
- L113 _variable_ `inline constexpr bool IsDebug = false;` (scope `uba`)
- L116 _macro_ `#define UBA_NOT_IMPLEMENTED(x) UBA_ASSERTF(false, TC("%s not implemented!"), #x);`
- L118 _prototype_ `u32 GetCallstack(void** outCallstack, u32 callstackCapacity, u32 skipCallstack, void* contextPtr);` (scope `uba`)
- L119 _prototype_ `bool WriteCallstackInfo(BinaryWriter& out, u32 skipCallstack, void* context);` (scope `uba`)
- L120 _prototype_ `bool WriteCallstackInfo(BinaryWriter& out, void** callstack, u32 callstackCount);` (scope `uba`)
- L121 _prototype_ `void WriteAssertInfo(StringBufferBase& out, const tchar* text, const char* file, u32 line, const char* expr, void* context = nullptr);` (scope `uba`)
- L122 _prototype_ `ANALYSIS_NORETURN void UbaAssert(const tchar* text, const char* file, u32 line, const char* expr, bool allowTerminate, u32 terminateCode, void* context, u32 skipCallstackCount);` (scope `uba`)
- L123 _prototype_ `ANALYSIS_NORETURN void FatalError(u32 code, const tchar* format, ...);` (scope `uba`)
- L124 _typedef_ `using CustomAssertHandler = void(const tchar* text, u32 textLen, void* userData);` (scope `uba`)
- L125 _prototype_ `void SetCustomAssertHandler(CustomAssertHandler* handler, void* userData);` (scope `uba`)
- L126 _prototype_ `bool CreateGuid(Guid& out);` (scope `uba`)
- L127 _prototype_ `const char* GetWineVersion();` (scope `uba`)
- L128 _prototype_ `bool IsRunningWine();` (scope `uba`)
- L129 _prototype_ `bool IsRunningDarling();` (scope `uba`)
- L130 _prototype_ `bool IsRunningArm();` (scope `uba`)
- L131 _prototype_ `bool IsEscapePressed();` (scope `uba`)
- L133 _prototype_ `void Sleep(u32 milliseconds);` (scope `uba`)
- L135 _function_ `inline void YieldInSpinWait()` (scope `uba`)
- L150 _prototype_ `u32 GetUserDefaultUILanguage();` (scope `uba`)
- L151 _prototype_ `u32 GetLastError();` (scope `uba`)
- L152 _prototype_ `void SetLastError(u32 error);` (scope `uba`)
- L153 _prototype_ `bool GetComputerNameW(StringBufferBase& out);` (scope `uba`)
- L154 _prototype_ `bool GetOsVersion(StringBufferBase& outPretty, u32& outValue);` (scope `uba`)
- L155 _prototype_ `u32 GetCurrentProcessId();` (scope `uba`)
- L157 _prototype_ `void AddExceptionHandler();` (scope `uba`)
- L158 _prototype_ `void InitMemory();` (scope `uba`)
- L159 _prototype_ `bool SetMemoryWorkingSet(u64 minWorkingSet);` (scope `uba`)
- L160 _prototype_ `bool UseSemaphoreForLocalEvents();` (scope `uba`)
- L161 _prototype_ `bool UseSemaphoreForSharedEvents();` (scope `uba`)
- L163 _variable_ `inline constexpr u64 PageSize = 64 * 1024;` (scope `uba`)
- L166 _variable_ `inline constexpr bool CaseInsensitiveFs = true;` (scope `uba`)
- L167 _variable_ `inline constexpr tchar PathSeparator = '\\';` (scope `uba`)
- L168 _variable_ `inline constexpr tchar NonPathSeparator = '/';` (scope `uba`)
- L169 _variable_ `inline constexpr u32 MaxPath = 1024;` (scope `uba`)
- L170 _function_ `inline DWORD ToLow(u64 v)` (scope `uba`)
- L171 _function_ `inline LONG ToHigh(u64 v)` (scope `uba`)
- L172 _function_ `inline LARGE_INTEGER ToLargeInteger(u64 v)` (scope `uba`)
- L173 _function_ `inline LARGE_INTEGER ToLargeInteger(u32 high, u32 low)` (scope `uba`)
- L174 _function_ `inline bool IsDirectory(u32 attributes)` (scope `uba`)
- L175 _function_ `inline bool IsSymlink(u32 attributes)` (scope `uba`)
- L176 _function_ `inline bool IsExecutable(u32 attributes)` (scope `uba`)
- L177 _function_ `inline tchar* TStrdup(const tchar* s)` (scope `uba`)
- L178 _macro_ `#define TStrlen(s) u32(wcslen(s))`
- L179 _macro_ `#define TStrchr(a, b) wcschr(a, b)`
- L180 _macro_ `#define TStrrchr(a, b) wcsrchr(a, b)`
- L181 _macro_ `#define TStrstr(a, b) wcsstr(a, b)`
- L182 _macro_ `#define TStrcmp(a, b) wcscmp(a, b)`
- L183 _macro_ `#define TSprintf_s swprintf_s`
- L184 _macro_ `#define Tvsprintf_s(...) vswprintf_s(__VA_ARGS__)`
- L185 _macro_ `#define TStrcpy_s wcscpy_s`
- L186 _macro_ `#define TStrcat_s wcscat_s`
- L187 _macro_ `#define TFputs fputws`
- L188 _macro_ `#define UBA_NOINLINE __declspec(noinline)`
- L190 _externvar_ `extern thread_local bool g_expectingAccessViolation;` (scope `uba`)
- L193 _variable_ `inline constexpr tchar PathSeparator = '/';` (scope `uba`)
- L194 _variable_ `inline constexpr tchar NonPathSeparator = '\\';` (scope `uba`)
- L195 _variable_ `inline constexpr u32 MaxPath = IsLinux ? 2048 : 1024;` (scope `uba`) — AOSP and similar deep-symlink builds need more headroom; we assert at this limit.
- L196 _macro_ `#define TStrlen(s) u32(strlen(s))`
- L197 _macro_ `#define TStrchr(a, b) strchr(a, b)`
- L198 _macro_ `#define TStrrchr(a, b) strrchr(a, b)`
- L199 _macro_ `#define TStrstr(a, b) strstr(a, b)`
- L200 _macro_ `#define TStrcmp(a, b) strcmp(a, b)`
- L201 _macro_ `#define TSprintf_s(...) snprintf(__VA_ARGS__)`
- L202 _macro_ `#define Tvsprintf_s(a, b, c, d) vsnprintf(a, b, c, d)`
- L203 _macro_ `#define TStrcpy_s(a, b, c) strcpy_s(a, b, c)`
- L204 _macro_ `#define TStrcat_s(a, b, c) strcat_s(a, b, c)`
- L205 _macro_ `#define TFputs fputs`
- L206 _macro_ `#define localtime_s(a,b) localtime_r(b,a)`
- L207 _prototype_ `void strcpy_s(tchar* dest, u64 destCapacity, const tchar* source);` (scope `uba`)
- L208 _prototype_ `void strcat_s(tchar* dest, u64 destCapacity, const tchar* source);` (scope `uba`)
- L209 _prototype_ `void GetMappingHandleName(StringBufferBase& out, u64 uid);` (scope `uba`)
- L210 _prototype_ `bool GetPhysicallyInstalledSystemMemory(u64& outKb);` (scope `uba`)
- L211 _function_ `inline u64 FromTimeSpec(const timespec& ts)` (scope `uba`)
- L212 _function_ `inline timespec ToTimeSpec(u64 time)` (scope `uba`)
- L218 _variable_ `inline constexpr bool CaseInsensitiveFs = false;` (scope `uba`)
- L219 _macro_ `#define st_atimespec st_atim`
- L220 _macro_ `#define st_mtimespec st_mtim`
- L221 _macro_ `#define st_ctimespec st_ctim`
- L225 _macro_ `#define UBA_NOINLINE __attribute__((noinline))`
- L226 _macro_ `#define ERROR_SUCCESS 0`
- L227 _macro_ `#define DUPLICATE_SAME_ACCESS 0`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaProcessStats.h` (Public)


#### struct `uba::ProcessStats`  
`struct ProcessStats`  
_L17-126_
- L19 _public member_ `Timer waitOnResponse;`
- L71 _public member_ `AtomicU64 startupTime;`
- L72 _public member_ `AtomicU64 exitTime;`
- L75 _public member_ `AtomicU64 wallTime;` — Don't add in GetTotalTime()
- L78 _public member_ `AtomicU64 cpuTime;` — From job object (windows only)
- L79 _public member_ `AtomicU64 peakProcessMemory;`
- L80 _public member_ `AtomicU64 peakJobMemory;`
- L82 _public member_ `AtomicU64 detoursMemory;`
- L83 _public member_ `AtomicU64 peakMemory;`
- L85 _public member_ `AtomicU64 iopsRead;`
- L86 _public member_ `AtomicU64 iopsWrite;`
- L87 _public member_ `AtomicU64 iopsOther;`
- L89 _public member_ `AtomicU64 hostTotalTime;`
- L91 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`
- L93 _public prototype_ `u64 GetTotalTime();`
- L94 _public prototype_ `u32 GetTotalCount();`
- L95 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L96 _public prototype_ `void Add(const ProcessStats& other);`
- L98 _public function_ `void Write(BinaryWriter& writer) const`

#### enum `uba::ProcessStats::(anonymous)`  
``  
_L65-69_

#### struct `uba::TimeAndBytes`  
`struct TimeAndBytes : ExtendedTimer`  
_L128-132_
- inherits: `ExtendedTimer`
- L130 _public function_ `void operator+=(const TimeAndBytes& o)`
- L131 _public member_ `AtomicU64 bytes;`

#### struct `uba::KernelStats`  
`struct KernelStats`  
_L136-195_
- L168 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L169 _public prototype_ `void Print(Logger& logger, bool writeHeader, u64 frequency = GetFrequency());`
- L170 _public prototype_ `bool IsEmpty();`
- L171 _public prototype_ `void Add(const KernelStats& other);`
- L172 _public prototype_ `static KernelStats& GetCurrent();`
- L173 _public prototype_ `static KernelStats& GetGlobal();`
- L182 _public function_ `void Write(BinaryWriter& writer)`

#### enum `uba::KernelStats::(anonymous)`  
``  
_L176-180_

#### struct `uba::KernelStatsScope`  
`struct KernelStatsScope`  
_L197-203_
- L199 _public prototype_ `KernelStatsScope(KernelStats& stats);`
- L200 _public prototype_ `~KernelStatsScope();`
- L202 _public member_ `KernelStats& stats;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L12 _function_ `inline void Write(BinaryWriter& writer, const Timer& timer)` (scope `uba`)
- L13 _function_ `inline void Write(BinaryWriter& writer, const AtomicU64& v)` (scope `uba`)
- L14 _function_ `inline bool IsEmpty(const Timer& timer)` (scope `uba`)
- L15 _function_ `inline bool IsEmpty(const AtomicU64& v)` (scope `uba`)
- L21 _macro_ `#define UBA_PROCESS_STATS \`
- L60 _macro_ `#define UBA_PROCESS_STAT(T, ver) Timer T;`
- L66 _macro_ `#define UBA_PROCESS_STAT(var, ver) Bit_##var,`
- L67 _enumerator_ `UBA_PROCESS_STATS #undef UBA_PROCESS_STAT` (scope `uba::ProcessStats::__anon7fa55d7d0103`)
- L103 _macro_ `#define UBA_PROCESS_STAT(var, ver) if (!uba::IsEmpty(var)) bits |= (1llu << Bit_##var);`
- L109 _macro_ `#define UBA_PROCESS_STAT(var, ver) if (!uba::IsEmpty(var)) uba::Write(writer, var);`
- L134 _function_ `inline void Write(BinaryWriter& writer, const TimeAndBytes& timer)` (scope `uba`)
- L138 _macro_ `#define UBA_KERNEL_STATS \`
- L164 _macro_ `#define UBA_KERNEL_STAT(type, var, ver) type var;`
- L177 _macro_ `#define UBA_KERNEL_STAT(type, var, ver) Bit_##var,`
- L178 _enumerator_ `UBA_KERNEL_STATS #undef UBA_KERNEL_STAT` (scope `uba::KernelStats::__anon7fa55d7d0203`)
- L185 _macro_ `#define UBA_KERNEL_STAT(type, var, ver) if (var.count) bits |= (1 << Bit_##var);`
- L191 _macro_ `#define UBA_KERNEL_STAT(type, var, ver) if (var.count) uba::Write(writer, var);`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaProcessUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L11 _function_ `template<typename CharType, typename Func> bool ParseArguments(const CharType* arguments, u64 argumentsLen, const Func& argumentFunc)` (scope `uba`) — func is void(const CharType* arg, u32 strArg)
- L31 _function_ `auto g = MakeGuard([&]() { if (argWriteBuffer != temp) delete[] argWriteBuffer; });` (scope `uba::ParseArguments`)
- L190 _function_ `template<typename Func> bool ParseArguments(const tchar* arguments, const Func& argumentFunc)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaProtocol.h` (Public)


#### enum `uba::MessageType`  
`enum MessageType : u8`  
_L52-58_
- L54 _public enumerator_ `MessageType_None = 0`
- L56 _public enumerator_ `UBA_PROCESS_MESSAGES #undef UBA_PROCESS_MESSAGE`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L9 _macro_ `#define UBA_PROCESS_MESSAGES \`
- L55 _macro_ `#define UBA_PROCESS_MESSAGE(type) MessageType_##type,`
- L60 _variable_ `inline constexpr u32 ProcessMessageVersion = 1352;` (scope `uba`)
- L62 _variable_ `inline constexpr u32 CommunicationMemSize = IsWindows ? 64*1024 : 64*1024*2;` (scope `uba`) — Macos expands some commandlines to be crazy long
- L64 _variable_ `inline constexpr u32 FileMappingTableMaxSize = 16 * 1024 * 1024;` (scope `uba`)
- L65 _variable_ `inline constexpr u32 DirTableMaxSize = 256 * 1024 * 1024;` (scope `uba`)
- L66 _variable_ `inline constexpr u32 OverlayTableMaxSize = 16 * 1024 * 1024;` (scope `uba`) — Seen ~600kb max size for ltcg/thinlto linking of our biggest binaries (one temp file per .o file)
- L67 _variable_ `inline constexpr u32 DirTableSnapshotMaxSize = 96 * 1024 * 1024;` (scope `uba`)
- L68 _variable_ `inline constexpr u32 EmergencyShutdownExitCode = 9886;` (scope `uba`)
- L74 _macro_ `#define UBA_DEBUG_LOG_ENABLED 1`
- L76 _macro_ `#define UBA_DEBUG_LOG_ENABLED 0`
- L80 _macro_ `#define UBA_DEBUG_VALIDATE 0`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaSharedMemoryView.h` (Public)


#### struct `uba::SharedMemoryHandle`  
`struct SharedMemoryHandle`  
_L18-25_
- L20 _public function_ `inline bool IsValid() const`
- L21 _public function_ `inline u64 ToU64() const`
- L22 _public function_ `inline bool operator==(const SharedMemoryHandle& o) const`
- L23 _public function_ `static SharedMemoryHandle FromU64(u64 v)`
- L24 _public member_ `u64 internalHandle = 0;`

#### enum `uba::SharedMemoryMapType`  
`enum SharedMemoryMapType`  
_L28-28_
- desc: Must stay parallel to MemoryMapType (UbaFileMapping.h) - SharedMemoryView casts between them.
- L28 _public enumerator_ `enum SharedMemoryMapType { SharedMemoryMapType_ReadOnly, SharedMemoryMapType_ReadWrite, SharedMemoryMapType_CopyOnWrite, SharedMemoryMapType_LazyCopyOnWrite }; class SharedMemoryView { public: SharedMemoryView(FileMappingBackend& backend);` — Must stay parallel to MemoryMapType (UbaFileMapping.h) - SharedMemoryView casts between them.
- L28 _public enumerator_ `enum SharedMemoryMapType { SharedMemoryMapType_ReadOnly, SharedMemoryMapType_ReadWrite, SharedMemoryMapType_CopyOnWrite, SharedMemoryMapType_LazyCopyOnWrite }; class SharedMemoryView { public: SharedMemoryView(FileMappingBackend& backend);` — Must stay parallel to MemoryMapType (UbaFileMapping.h) - SharedMemoryView casts between them.
- L28 _public enumerator_ `enum SharedMemoryMapType { SharedMemoryMapType_ReadOnly, SharedMemoryMapType_ReadWrite, SharedMemoryMapType_CopyOnWrite, SharedMemoryMapType_LazyCopyOnWrite }; class SharedMemoryView { public: SharedMemoryView(FileMappingBackend& backend);` — Must stay parallel to MemoryMapType (UbaFileMapping.h) - SharedMemoryView casts between them.
- L28 _public enumerator_ `enum SharedMemoryMapType { SharedMemoryMapType_ReadOnly, SharedMemoryMapType_ReadWrite, SharedMemoryMapType_CopyOnWrite, SharedMemoryMapType_LazyCopyOnWrite }; class SharedMemoryView { public: SharedMemoryView(FileMappingBackend& backend);` — Must stay parallel to MemoryMapType (UbaFileMapping.h) - SharedMemoryView casts between them.

#### class `uba::SharedMemoryView`  
`class SharedMemoryView`  
_L32-68_
- L35 _public prototype_ `SharedMemoryView(FileMappingBackend& backend);`
- L36 _public prototype_ `SharedMemoryView(SharedMemoryView&&) = default;`
- L38 _public prototype_ `bool Init(SharedMemoryAllocatorHandle handle, u64 capacity, void* baseAddress = nullptr, const tchar* hint = TC(""));`
- L39 _public prototype_ `bool Init(SharedMemoryAllocatorHandle handle, u8* sharedMemory, BinaryReader& reader, u64 capacity, const tchar* hint = TC(""), SharedMemoryMapType type = SharedMemoryMapType_ReadOnly);`
- L41 _public prototype_ `bool AddRequestedMemory(SharedMemoryAllocatorHandle handle, BinaryReader& reader, SharedMemoryMapType mapType = SharedMemoryMapType_ReadWrite, u64 offset = 0, const tchar* hint = TC(""), u8 init = 0);`
- L42 _public prototype_ `void Reset();`
- L44 _public function_ `u8* GetMemory()`
- L45 _public function_ `u64 GetMappedSize()`
- L46 _public function_ `u64 GetCapacity()`
- L48 _public prototype_ `void SetMemory(u8* memory, u64 capacity);`
- L49 _public prototype_ `u8* DetachMemory();`
- L50 _public prototype_ `~SharedMemoryView();`
- L53 _private prototype_ `bool InternalInit(SharedMemoryAllocatorHandle handle, u64 capacity, void* baseAddress, const tchar* hint);`
- L54 _private prototype_ `bool AddRequestedMemory(SharedMemoryAllocatorHandle handle, BinaryReader& reader, u32 sliceCount, SharedMemoryMapType mapType, u64 offset, const tchar* hint, u8 init);`
- L55 _private prototype_ `void ReferenceExternalMemory(u8* memory, u64 mappedSize);`
- L56 _private prototype_ `bool ExtendMemory(SharedMemoryAllocatorHandle handle, u64 offset, u64 size, SharedMemoryMapType mapType, const tchar* hint, u8 init = 0);`
- L58 _private member_ `FileMappingBackend& m_fileMappingBackend;`
- L59 _private member_ `u8* m_memory = nullptr;`
- L60 _private member_ `u64 m_mappedSize = 0;`
- L61 _private member_ `u64 m_capacity = 0;`
- L63 _private member_ `Vector<u64> m_additionalMappings;`
- L65 _private prototype_ `SharedMemoryView(const SharedMemoryView&) = delete;`
- L66 _private prototype_ `SharedMemoryView& operator=(const SharedMemoryView&) = delete;`

#### struct `std::hash`  
`template<> struct std::hash<uba::SharedMemoryHandle>`  
_L82-82_
- L82 _public function_ `template<> struct std::hash<uba::SharedMemoryHandle>`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L16 _typedef_ `using SharedMemoryAllocatorHandle = FileMappingHandle;` (scope `uba`)
- L72 _prototype_ `bool IsMemoryHandle(const tchar* name);` (scope `uba`)
- L73 _prototype_ `bool IsFreeableMemoryHandle(const tchar* name);` (scope `uba`)
- L74 _prototype_ `void GetMappingHandleAndOffset(const tchar* str, u64& outHandle, u64& outOffset);` (scope `uba`)
- L75 _variable_ `inline constexpr tchar MemoryHandleChar = '^';` (scope `uba`)
- L76 _variable_ `inline constexpr tchar FreeableMemoryHandleChar = '>';` (scope `uba`)
- L77 _variable_ `inline constexpr tchar WrittenMemoryHandleChar = ':';` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaString.h` (Public)


#### class `uba::TString`  
`class TString`  
_L14-371_
- desc: Minimal basic_string-like TString for tchar. Heap-only (no SSO yet — easy to add later if profiling calls for it).
- L17 _public typedef_ `using value_type = tchar;`
- L18 _public typedef_ `using size_type = u64;`
- L20 _public prototype_ `TString() = default;`
- L22 _public function_ `TString(const tchar* s)`
- L29 _public function_ `TString(const tchar* s, size_type n)`
- L32 _public function_ `TString(const tchar* first, const tchar* last)` — Iterator-range ctor: [first, last). Fast path for raw tchar pointers.
- L40 _public function_ `TString(InputIt first, InputIt last)`
- L45 _public function_ `TString(size_type n, tchar c)`
- L53 _public function_ `TString(const TString& o)`
- L55 _public function_ `TString(TString&& o) noexcept`
- L57 _public function_ `~TString()`
- L62 _public function_ `TString& operator=(const TString& o)`
- L72 _public function_ `TString& operator=(TString&& o) noexcept`
- L83 _public function_ `TString& operator=(const tchar* s)`
- L90 _public function_ `size_type size() const`
- L91 _public function_ `size_type length() const`
- L92 _public function_ `bool empty() const`
- L93 _public function_ `size_type capacity() const`
- L95 _public function_ `const tchar* c_str() const`
- L96 _public function_ `const tchar* data() const`
- L97 _public function_ `tchar* data()`
- L99 _public function_ `tchar& operator[](size_type i)`
- L100 _public function_ `const tchar& operator[](size_type i) const`
- L103 _public typedef_ `using iterator = tchar*;` — Raw-pointer iterators (tchar*).
- L104 _public typedef_ `using const_iterator = const tchar*;`
- L105 _public function_ `iterator begin()`
- L106 _public function_ `iterator end()`
- L107 _public function_ `const_iterator begin() const`
- L108 _public function_ `const_iterator end() const`
- L109 _public function_ `const_iterator cbegin() const`
- L110 _public function_ `const_iterator cend() const`
- L112 _public function_ `tchar& front()`
- L113 _public function_ `const tchar& front() const`
- L114 _public function_ `tchar& back()`
- L115 _public function_ `const tchar& back() const`
- L117 _public member_ `static constexpr size_type npos = size_type(-1);`
- L120 _public function_ `size_type find(const tchar* s, size_type from = 0) const` — Find first occurrence of `s` starting at `from`. Returns npos on miss.
- L135 _public function_ `size_type find(tchar c, size_type from = 0) const`
- L141 _public function_ `size_type find(const TString& o, size_type from = 0) const`
- L144 _public function_ `TString& replace(size_type pos, size_type count, const tchar* s, size_type slen)` — Replace [pos, pos+count) with [s, s+slen). Returns *this.
- L170 _public function_ `TString& replace(size_type pos, size_type count, const tchar* s)`
- L175 _public function_ `TString& replace(size_type pos, size_type count, const TString& o)`
- L180 _public function_ `TString& assign(const tchar* s)`
- L181 _public function_ `TString& assign(const tchar* s, size_type n)`
- L182 _public function_ `TString& assign(const TString& o)`
- L183 _public function_ `TString& assign(size_type n, tchar c)`
- L196 _public function_ `TString& assign(InputIt first, InputIt last)`
- L204 _public function_ `TString substr(size_type pos = 0, size_type count = npos) const` — Substring from [pos, pos+count).
- L212 _public function_ `TString& erase(size_type pos, size_type count = npos)` — Erase `count` chars starting at `pos`.
- L224 _public function_ `void clear()`
- L230 _public function_ `void reserve(size_type n)`
- L249 _public function_ `void resize(size_type n)`
- L257 _public function_ `TString& append(const tchar* s, size_type n)`
- L267 _public function_ `TString& append(const tchar* s)`
- L272 _public function_ `TString& append(const TString& o)`
- L274 _public function_ `TString& operator+=(const tchar* s)`
- L275 _public function_ `TString& operator+=(const TString& o)`
- L276 _public function_ `TString& operator+=(tchar c)`
- L284 _public function_ `void push_back(tchar c)`
- L286 _public function_ `void swap(TString& o) noexcept`
- L294 _public function_ `int compare(const TString& o) const` — Lexicographic compare.
- L295 _public function_ `int compare(const tchar* s) const`
- L302 _public function_ `int compare(size_type pos, size_type count, const tchar* s, size_type slen) const` — Compare substring [pos, pos+count) with (s, slen) / s / other.
- L308 _public function_ `int compare(size_type pos, size_type count, const tchar* s) const`
- L312 _public function_ `int compare(size_type pos, size_type count, const TString& o) const`
- L317 _public function_ `bool operator==(const TString& o) const`
- L323 _public function_ `bool operator!=(const TString& o) const`
- L324 _public function_ `bool operator<(const TString& o) const`
- L326 _public function_ `bool operator==(const tchar* s) const`
- L333 _public function_ `bool operator!=(const tchar* s) const`
- L336 _private function_ `static const tchar* empty_str()`
- L338 _private function_ `static size_type strlen_tchar(const tchar* s)`
- L345 _private function_ `static int compare_raw(const tchar* a, size_type an, const tchar* b, size_type bn)`
- L358 _private function_ `void assign_raw(const tchar* s, size_type n)`
- L367 _private member_ `tchar* m_data = nullptr;`
- L368 _private member_ `size_type m_size = 0;`
- L369 _private member_ `size_type m_capacity = 0;` — includes space for null terminator
- L370 _private member_ `Allocator m_alloc;`

#### struct `std::hash`  
`template<> struct hash<uba::TString>`  
_L410-425_
- L412 _public function_ `size_t operator()(const uba::TString& s) const noexcept`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L374 _function_ `inline bool operator==(const tchar* s, const TString& t)` (scope `uba`) — Free comparison for (const tchar*, TString)
- L375 _function_ `inline bool operator!=(const tchar* s, const TString& t)` (scope `uba`)
- L379 _function_ `inline bool operator<(const TString& a, const tchar* b)` (scope `uba`) — Heterogeneous `<` against tchar* so std::less<> transparent compare works (e.g. Map<TString, V> with `find(const tchar*)`).
- L380 _function_ `inline bool operator<(const tchar* a, const TString& b)` (scope `uba`)
- L383 _function_ `inline TString operator+(const TString& a, const TString& b)` (scope `uba`) — Concatenation operators.
- L387 _function_ `inline TString operator+(const TString& a, const tchar* b)` (scope `uba`)
- L391 _function_ `inline TString operator+(const tchar* a, const TString& b)` (scope `uba`)
- L395 _function_ `inline TString operator+(const TString& a, tchar b)` (scope `uba`)
- L399 _function_ `inline TString operator+(tchar a, const TString& b)` (scope `uba`)
- L407 _namespace_ `namespace std`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaStringBuffer.h` (Public)


#### class `uba::StringBufferBase`  
`class StringBufferBase`  
_L30-101_
- L33 _public function_ `StringBufferBase& Append(const StringBufferBase& str)`
- L34 _public function_ `StringBufferBase& Append(const TString& str)`
- L35 _public prototype_ `StringBufferBase& Append(const tchar* str);`
- L36 _public function_ `StringBufferBase& Append(const tchar c)`
- L37 _public prototype_ `StringBufferBase& Append(const tchar* str, u64 charCount);`
- L38 _public prototype_ `StringBufferBase& Append(StringView view);`
- L39 _public prototype_ `StringBufferBase& Appendf(const tchar* format, ...);`
- L40 _public prototype_ `StringBufferBase& AppendDir(const StringBufferBase& str);`
- L41 _public prototype_ `StringBufferBase& AppendDir(const tchar* dir);`
- L42 _public prototype_ `StringBufferBase& AppendFileName(const tchar* str);`
- L43 _public prototype_ `StringBufferBase& AppendHex(u64 v);`
- L44 _public prototype_ `StringBufferBase& AppendBase62(u64 v);`
- L45 _public prototype_ `StringBufferBase& AppendValue(u64 v);`
- L46 _public prototype_ `StringBufferBase& Append(const tchar* format, va_list& args);`
- L47 _public prototype_ `StringBufferBase& Prepend(StringView view, u32 overwriteCount = 0);`
- L48 _public prototype_ `StringBufferBase& Resize(u64 newSize);`
- L49 _public prototype_ `StringBufferBase& Clear();`
- L51 _public prototype_ `StringBufferBase& ReadString(BinaryReader& reader);`
- L54 _public prototype_ `StringBufferBase& Append(const char* str);`
- L55 _public prototype_ `StringBufferBase& Append(const char* str, u32 charCount);`
- L59 _public prototype_ `template<typename Container, typename Func> StringBufferBase& Join(const Container& c, const Func& f, const tchar* separator = TC(","))`
- L61 _public function_ `tchar operator[](u64 i) const`
- L62 _public function_ `tchar& operator[](u64 i)`
- L64 _public function_ `bool IsEmpty() const`
- L65 _public function_ `bool StartsWith(const tchar* str, bool ignoreCase = true) const`
- L66 _public prototype_ `bool StartsWith(StringView str, bool ignoreCase = true) const;`
- L67 _public prototype_ `bool EndsWith(const tchar* value, bool ignoreCase = true) const;`
- L68 _public prototype_ `bool EndsWith(StringView value, bool ignoreCase = true) const;`
- L69 _public prototype_ `bool Contains(tchar c) const;`
- L70 _public function_ `bool Contains(const tchar* str, bool ignoreCase = true, const tchar** pos = nullptr) const`
- L71 _public function_ `bool Equals(const tchar* str, bool ignoreCase = true) const`
- L72 _public prototype_ `bool Equals(StringView str, bool ignoreCase = true) const;`
- L73 _public prototype_ `const tchar* First(tchar c, u64 offset = 0) const;`
- L74 _public prototype_ `const tchar* Last(tchar c, u64 offset = 0) const;`
- L75 _public function_ `const tchar* GetFileName() const`
- L76 _public function_ `inline StringBufferBase& Replace(tchar from, tchar to)`
- L78 _public prototype_ `StringBufferBase& EnsureEndsWithSlash();`
- L79 _public prototype_ `StringBufferBase& FixPathSeparators();`
- L80 _public prototype_ `StringBufferBase& MakeLower();`
- L82 _public prototype_ `bool Parse(u64& out) const;`
- L83 _public prototype_ `bool Parse(u32& out, u64 offset = 0) const;`
- L84 _public prototype_ `bool Parse(u16& out, u64 offset = 0) const;`
- L85 _public prototype_ `bool Parse(bool& out) const;`
- L86 _public prototype_ `bool Parse(float& out) const;`
- L87 _public prototype_ `bool Parse(TString& out, u64 offset = 0) const;`
- L88 _public prototype_ `bool Parse(StringBufferBase& out, u64 offset = 0) const;`
- L89 _public prototype_ `u32 Parse(char* out, u64 outCapacity) const;` — Note, return value contains length + null termination.. zero if failed
- L91 _public function_ `TString ToString() const`
- L92 _public function_ `TString ToStringAndClear()`
- L93 _public function_ `bool ToFalse() const`
- L95 _public member_ `u32 count;`
- L96 _public member_ `u32 capacity;`
- L97 _public member_ `tchar data[1];`
- L100 _protected function_ `StringBufferBase(u32 c) : capacity(c)`
- L189 _function_ `template<typename Container, typename Func> StringBufferBase& StringBufferBase::Join(const Container& c, const Func& f, const tchar* separator)`

#### enum `uba::NoInitEnum`  
`enum NoInitEnum`  
_L105-105_
- L105 _public enumerator_ `enum NoInitEnum { NoInit }; struct StringView { constexpr StringView() : data(TC("")), count(0) {} constexpr StringView(NoInitEnum) {} constexpr StringView(const StringView&) = default; constexpr StringView(const tchar* d, u32 c) : data(d), count(c) {}`

#### struct `uba::StringView`  
`struct StringView`  
_L107-153_
- L109 _public function_ `constexpr StringView() : data(TC("")), count(0)`
- L110 _public function_ `constexpr StringView(NoInitEnum)`
- L111 _public prototype_ `constexpr StringView(const StringView&) = default;`
- L112 _public function_ `constexpr StringView(const tchar* d, u32 c) : data(d), count(c)`
- L113 _public function_ `constexpr StringView(const StringBufferBase& sb) : data(sb.data), count(sb.count)`
- L114 _public prototype_ `constexpr StringView(const tchar* d) = delete;`
- L115 _public function_ `StringView(const TString& str) : data(str.data()), count(u32(str.size()))`
- L117 _public function_ `tchar operator[](u64 i) const`
- L118 _public function_ `tchar Last()`
- L120 _public function_ `bool IsEmpty() const`
- L121 _public function_ `bool IsTerminated() const`
- L122 _public prototype_ `bool StartsWith(StringView str, bool ignoreCase = true) const;` — Requires terminated StringViews
- L123 _public function_ `bool StartsWith(const tchar* str, bool ignoreCase = true) const` — Requires terminated StringView
- L124 _public function_ `bool EndsWith(StringView value, bool ignoreCase = true) const`
- L125 _public prototype_ `bool EndsWith(const tchar* value, bool ignoreCase = true) const;`
- L126 _public prototype_ `bool Contains(tchar c, u32* outPos = nullptr) const;`
- L127 _public function_ `bool Contains(const tchar* str, bool ignoreCase = true) const` — Requires terminated StringViews
- L128 _public function_ `bool Contains(StringView str, bool ignoreCase = true) const` — Requires terminated StringViews
- L129 _public function_ `bool Equals(const tchar* str, bool ignoreCase = true) const` — Requires terminated StringViews
- L130 _public function_ `bool Equals(StringView str, bool ignoreCase = true) const`
- L131 _public prototype_ `StringView GetFileName() const;`
- L132 _public prototype_ `StringView GetPath(bool keepLastSlash = false) const;`
- L133 _public function_ `StringView Skip(u32 skipCount) const`
- L134 _public function_ `StringView RemoveSuffix(u32 removeCount)`
- L135 _public function_ `StringView SubStr(u32 startOffset, u32 length) const`
- L136 _public prototype_ `StringView Trim();`
- L138 _public prototype_ `const tchar* CheckTerminated() const;`
- L140 _public function_ `TString ToString() const`
- L142 _public prototype_ `bool Parse(u64& out) const;`
- L143 _public prototype_ `bool Parse(u32& out, u64 offset = 0) const;`
- L144 _public prototype_ `bool Parse(u16& out, u64 offset = 0) const;`
- L145 _public prototype_ `bool Parse(bool& out) const;`
- L146 _public prototype_ `bool Parse(float& out) const;`
- L147 _public prototype_ `bool Parse(TString& out, u64 offset = 0) const;`
- L148 _public prototype_ `bool Parse(StringBufferBase& out, u64 offset = 0) const;`
- L149 _public prototype_ `u32 Parse(char* out, u64 outCapacity) const;` — Note, return value contains length + null termination.. zero if failed
- L151 _public member_ `const tchar* data;`
- L152 _public member_ `u32 count;`

#### class `uba::StringBuffer`  
`template<u32 Capacity = 512> class StringBuffer : public StringBufferBase`  
_L167-177_
- inherits: `StringBufferBase`
- L170 _public function_ `StringBuffer() : StringBufferBase(Capacity)`
- L171 _public function_ `explicit StringBuffer(const TString& str) : StringBufferBase(Capacity)`
- L172 _public function_ `explicit StringBuffer(const tchar* str) : StringBufferBase(Capacity)`
- L173 _public function_ `StringBuffer(const StringBufferBase& str) : StringBufferBase(Capacity)`
- L174 _public function_ `StringBuffer(StringView str) : StringBufferBase(Capacity)`
- L176 _private member_ `tchar buf[Capacity];`

#### struct `uba::LastErrorToText`  
`struct LastErrorToText : StringBuffer<256>`  
_L181-186_
- inherits: `StringBuffer<256>`
- L183 _public prototype_ `LastErrorToText();`
- L184 _public prototype_ `LastErrorToText(u32 lastError);`
- L185 _public function_ `operator const tchar* () const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L15 _prototype_ `bool StartsWith(const tchar* data, const tchar* str, bool ignoreCase = true);` (scope `uba`)
- L16 _prototype_ `bool EndsWith(const tchar* str, u64 strLen, const tchar* value, u64 valueLen, bool ignoreCase);` (scope `uba`)
- L17 _prototype_ `bool Contains(const tchar* str, const tchar* sub, bool ignoreCase = true, const tchar** pos = nullptr);` (scope `uba`)
- L18 _prototype_ `bool Equals(const tchar* str1, const tchar* str2, bool ignoreCase = true);` (scope `uba`)
- L19 _prototype_ `bool Equals(const tchar* str1, const tchar* str2, u64 count, bool ignoreCase = true);` (scope `uba`)
- L20 _prototype_ `void Replace(tchar* str, tchar from, tchar to);` (scope `uba`)
- L21 _prototype_ `void FixPathSeparators(tchar* str);` (scope `uba`)
- L22 _prototype_ `bool Parse(u64& out, const tchar* str, u64 strLen);` (scope `uba`)
- L23 _function_ `inline void ToLower(tchar* str)` (scope `uba`)
- L24 _function_ `inline tchar ToLower(tchar c)` (scope `uba`)
- L25 _function_ `inline tchar ToUpper(tchar c)` (scope `uba`)
- L26 _prototype_ `const tchar* GetFileName(const tchar* path);` (scope `uba`)
- L155 _prototype_ `StringView ToView(const tchar* s);` (scope `uba`)
- L156 _prototype_ `StringView ToView(StringView sv);` (scope `uba`)
- L157 _prototype_ `StringView ToView(StringBufferBase& sb);` (scope `uba`)
- L160 _function_ `template<typename T, size_t size> constexpr StringView AsView(T (&buffer)[size])` (scope `uba`)
- L162 _macro_ `#define TCV(x) AsView(TC(x))`

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaSynchronization.h` (Public)


#### struct `uba::AtomicU64`  
`struct AtomicU64 : Atomic<u64>`  
_L21-27_
- inherits: `Atomic<u64>`
- L23 _public function_ `AtomicU64(u64 initialValue = 0) : Atomic<u64>(initialValue)`
- L24 _public function_ `AtomicU64(AtomicU64&& o) noexcept : Atomic<u64>(o.load())`
- L25 _public function_ `void operator=(u64 o)`
- L26 _public function_ `void operator=(const AtomicU64& o)`

#### class `uba::CriticalSection`  
`class CriticalSection`  
_L35-57_
- L38 _public prototype_ `CriticalSection() = default;`
- L40 _public prototype_ `[[nodiscard]] bool TryEnter();`
- L41 _public prototype_ `void Enter();`
- L42 _public prototype_ `void Leave();`
- L45 _private prototype_ `void EnterSlow(u32 currentState, u32 currentThreadId);`
- L46 _private prototype_ `void WakeWaitingThread();`
- L48 _private member_ `static constexpr u32 mayHaveWaitingLockFlag = 1 << 0;`
- L49 _private member_ `static constexpr u32 lockCountShift = 1;`
- L50 _private member_ `static constexpr u32 lockCountMask = 0xffff'fffe;`
- L52 _private member_ `Atomic<u32> state = 0;`
- L53 _private member_ `Atomic<u32> threadId = 0;`
- L55 _private prototype_ `CriticalSection(const CriticalSection&) = delete;`
- L56 _private prototype_ `CriticalSection& operator=(const CriticalSection&) = delete;`
- L62 _public prototype_ `CriticalSection(bool recursive = true);`
- L63 _public prototype_ `~CriticalSection();`
- L68 _public prototype_ `bool TryEnter() const;`
- L72 _private member_ `u64 data[5];`

#### class `uba::CriticalSection`  
`class CriticalSection`  
_L59-79_
- L38 _public prototype_ `CriticalSection() = default;`
- L40 _public prototype_ `[[nodiscard]] bool TryEnter();`
- L41 _public prototype_ `void Enter();`
- L42 _public prototype_ `void Leave();`
- L45 _private prototype_ `void EnterSlow(u32 currentState, u32 currentThreadId);`
- L46 _private prototype_ `void WakeWaitingThread();`
- L48 _private member_ `static constexpr u32 mayHaveWaitingLockFlag = 1 << 0;`
- L49 _private member_ `static constexpr u32 lockCountShift = 1;`
- L50 _private member_ `static constexpr u32 lockCountMask = 0xffff'fffe;`
- L52 _private member_ `Atomic<u32> state = 0;`
- L53 _private member_ `Atomic<u32> threadId = 0;`
- L55 _private prototype_ `CriticalSection(const CriticalSection&) = delete;`
- L56 _private prototype_ `CriticalSection& operator=(const CriticalSection&) = delete;`
- L62 _public prototype_ `CriticalSection(bool recursive = true);`
- L63 _public prototype_ `~CriticalSection();`
- L68 _public prototype_ `bool TryEnter() const;`
- L72 _private member_ `u64 data[5];`

#### class `uba::ReaderWriterLock`  
`class ReaderWriterLock`  
_L85-162_
- L88 _public prototype_ `ReaderWriterLock() = default;`
- L90 _public function_ `inline bool TryEnter()`
- L98 _public function_ `inline void Enter()`
- L108 _public function_ `inline void Leave()`
- L119 _public function_ `inline void EnterRead() const`
- L131 _public function_ `inline void LeaveRead() const`
- L144 _private prototype_ `void EnterSlow();`
- L145 _private prototype_ `void EnterReadSlow() const;`
- L146 _private prototype_ `void WakeWaitingThread() const;`
- L147 _private prototype_ `void WakeWaitingThreads(u32 lastState);`
- L149 _private prototype_ `const void* GetLockAddress() const;`
- L150 _private prototype_ `const void* GetReadLockAddress() const;`
- L152 _private member_ `static constexpr u32 isLockedFlag = 1 << 0;`
- L153 _private member_ `static constexpr u32 mayHaveWaitingLockFlag = 1 << 1;`
- L154 _private member_ `static constexpr u32 mayHaveWaitingReadLockFlag = 1 << 2;`
- L155 _private member_ `static constexpr u32 readLockCountShift = 3;`
- L156 _private member_ `static constexpr u32 readLockCountMask = 0xffff'fff8;`
- L158 _private member_ `mutable Atomic<u32> state = 0;`
- L160 _private prototype_ `ReaderWriterLock(const ReaderWriterLock&) = delete;`
- L161 _private prototype_ `ReaderWriterLock& operator=(const ReaderWriterLock&) = delete;`
- L167 _public prototype_ `ReaderWriterLock();`
- L168 _public prototype_ `~ReaderWriterLock();`
- L170 _public prototype_ `void EnterRead() const;`
- L171 _public prototype_ `void LeaveRead() const;`
- L173 _public prototype_ `void Enter();`
- L174 _public prototype_ `void Leave();`
- L176 _public prototype_ `bool TryEnter();`
- L181 _private member_ `u64 data[1];`

#### class `uba::ReaderWriterLock`  
`class ReaderWriterLock`  
_L164-190_
- L88 _public prototype_ `ReaderWriterLock() = default;`
- L90 _public function_ `inline bool TryEnter()`
- L98 _public function_ `inline void Enter()`
- L108 _public function_ `inline void Leave()`
- L119 _public function_ `inline void EnterRead() const`
- L131 _public function_ `inline void LeaveRead() const`
- L144 _private prototype_ `void EnterSlow();`
- L145 _private prototype_ `void EnterReadSlow() const;`
- L146 _private prototype_ `void WakeWaitingThread() const;`
- L147 _private prototype_ `void WakeWaitingThreads(u32 lastState);`
- L149 _private prototype_ `const void* GetLockAddress() const;`
- L150 _private prototype_ `const void* GetReadLockAddress() const;`
- L152 _private member_ `static constexpr u32 isLockedFlag = 1 << 0;`
- L153 _private member_ `static constexpr u32 mayHaveWaitingLockFlag = 1 << 1;`
- L154 _private member_ `static constexpr u32 mayHaveWaitingReadLockFlag = 1 << 2;`
- L155 _private member_ `static constexpr u32 readLockCountShift = 3;`
- L156 _private member_ `static constexpr u32 readLockCountMask = 0xffff'fff8;`
- L158 _private member_ `mutable Atomic<u32> state = 0;`
- L160 _private prototype_ `ReaderWriterLock(const ReaderWriterLock&) = delete;`
- L161 _private prototype_ `ReaderWriterLock& operator=(const ReaderWriterLock&) = delete;`
- L167 _public prototype_ `ReaderWriterLock();`
- L168 _public prototype_ `~ReaderWriterLock();`
- L170 _public prototype_ `void EnterRead() const;`
- L171 _public prototype_ `void LeaveRead() const;`
- L173 _public prototype_ `void Enter();`
- L174 _public prototype_ `void Leave();`
- L176 _public prototype_ `bool TryEnter();`
- L181 _private member_ `u64 data[1];`

#### struct `uba::ContentionTracker`  
`struct ContentionTracker`  
_L203-203_
- L203 _public function_ `struct ContentionTracker`
- L203 _public member_ `struct ContentionTracker { void Add(u64 t) { time += t; ++count; }; Atomic<u64> time; Atomic<u64> count; const char* file; u64 line; };`
- L203 _public member_ `struct ContentionTracker { void Add(u64 t) { time += t; ++count; }; Atomic<u64> time; Atomic<u64> count; const char* file; u64 line; };`
- L203 _public member_ `struct ContentionTracker { void Add(u64 t) { time += t; ++count; }; Atomic<u64> time; Atomic<u64> count; const char* file; u64 line; };`
- L203 _public member_ `struct ContentionTracker { void Add(u64 t) { time += t; ++count; }; Atomic<u64> time; Atomic<u64> count; const char* file; u64 line; };`

#### class `uba::ScopedCriticalSection`  
`template <typename MutexType> class ScopedCriticalSection`  
_L222-232_
- L225 _public function_ `ScopedCriticalSection(MutexType& mutex) : m_mutex(mutex), m_active(true)`
- L226 _public function_ `~ScopedCriticalSection()`
- L227 _public function_ `void Enter()`
- L228 _public function_ `void Leave()`
- L230 _private member_ `MutexType& m_mutex;`
- L231 _private member_ `bool m_active;`

#### class `uba::ScopedReadLock`  
`class ScopedReadLock`  
_L236-246_
- L239 _public function_ `ScopedReadLock(const ReaderWriterLock& lock) : m_lock(lock)`
- L240 _public function_ `~ScopedReadLock()`
- L241 _public function_ `inline void Enter()`
- L242 _public function_ `inline void Leave()`
- L244 _public member_ `const ReaderWriterLock& m_lock;`
- L245 _public member_ `bool m_active = true;`

#### class `uba::ScopedWriteLock`  
`class ScopedWriteLock`  
_L250-260_
- L253 _public function_ `ScopedWriteLock(ReaderWriterLock& lock) : m_lock(lock)`
- L254 _public function_ `~ScopedWriteLock()`
- L255 _public function_ `inline void Enter()`
- L256 _public function_ `inline void Leave()`
- L258 _public member_ `ReaderWriterLock& m_lock;`
- L259 _public member_ `bool m_active = true;`

#### class `uba::Futex`  
`class Futex : public CriticalSection`  
_L269-269_
- inherits: `CriticalSection`
- L269 _public function_ `class Futex : public CriticalSection`

#### struct `uba::ScopeGuard`  
`template<typename Lambda> struct ScopeGuard`  
_L278-293_
- L280 _public function_ `void Cancel()`
- L281 _public function_ `auto Execute()`
- L283 _public function_ `ScopeGuard(Lambda lambda) : m_lambda(lambda)`
- L284 _public function_ `ScopeGuard(ScopeGuard&& o)`
- L285 _public prototype_ `ScopeGuard() = delete;`
- L286 _public prototype_ `ScopeGuard(const ScopeGuard& o) = delete;`
- L287 _public prototype_ `void operator=(const ScopeGuard&) = delete;`
- L288 _public prototype_ `void operator=(ScopeGuard&&) = delete;`
- L289 _public function_ `~ScopeGuard()`
- L291 _private member_ `Lambda m_lambda;`
- L292 _private member_ `bool m_called = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UBA_TRACK_CONTENTION 0`
- L11 _macro_ `#define STRING_JOIN(arg1, arg2) STRING_JOIN_INNER(arg1, arg2)`
- L12 _macro_ `#define STRING_JOIN_INNER(arg1, arg2) arg1 ## arg2`
- L14 _namespace_ `namespace uba`
- L17 _typedef_ `template<typename Type> using Atomic = std::atomic<Type>;` (scope `uba`)
- L30 _prototype_ `template<typename T> void AtomicMax(Atomic<T>& target, T value);` (scope `uba`)
- L196 _macro_ `#define SCOPED_READ_LOCK(readerWriterLock, name) ScopedReadLock name(readerWriterLock);`
- L197 _macro_ `#define SCOPED_WRITE_LOCK(readerWriterLock, name) ScopedWriteLock name(readerWriterLock);`
- L198 _macro_ `#define SCOPED_CRITICAL_SECTION(cs, name) ScopedCriticalSection name(cs);`
- L199 _macro_ `#define SCOPED_FUTEX(cs, name) ScopedFutex name(cs);`
- L200 _macro_ `#define SCOPED_FUTEX_READ(cs, name) ScopedFutexRead name(cs);`
- L202 _prototype_ `u64 GetTime();` (scope `uba`)
- L204 _prototype_ `ContentionTracker& GetContentionTracker(const char* file, u64 line);` (scope `uba`)
- L206 _macro_ `#define SCOPED_LOCK_INTERNAL(lock, lockType, name) \`
- L212 _macro_ `#define SCOPED_READ_LOCK(readerWriterLock, name) SCOPED_LOCK_INTERNAL(readerWriterLock, ScopedReadLock, name)`
- L213 _macro_ `#define SCOPED_WRITE_LOCK(readerWriterLock, name) SCOPED_LOCK_INTERNAL(readerWriterLock, ScopedWriteLock, name)`
- L214 _macro_ `#define SCOPED_CRITICAL_SECTION(cs, name) SCOPED_LOCK_INTERNAL(cs, ScopedCriticalSection, name)`
- L215 _macro_ `#define SCOPED_FUTEX(futex, name) SCOPED_LOCK_INTERNAL(futex, ScopedFutex, name)`
- L216 _macro_ `#define SCOPED_FUTEX_READ(futex, name) SCOPED_LOCK_INTERNAL(futex, ScopedFutex, name)`
- L265 _typedef_ `using Futex = ReaderWriterLock;` (scope `uba`)
- L266 _typedef_ `using ScopedFutex = ScopedWriteLock;` (scope `uba`)
- L267 _typedef_ `using ScopedFutexRead = ScopedReadLock;` (scope `uba`)
- L270 _typedef_ `using ScopedFutex = ScopedCriticalSection<Futex>;` (scope `uba`)
- L271 _typedef_ `using ScopedFutexRead = ScopedCriticalSection<Futex>;` (scope `uba`)
- L295 _function_ `template<typename Lambda> ScopeGuard<Lambda> MakeGuard(Lambda&& lambda)` (scope `uba`)
- L300 _function_ `template<typename T> void AtomicMax(Atomic<T>& target, T value)` (scope `uba`)
- L307 _function_ `template<typename T> void AtomicMin(Atomic<T>& target, T value)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaTimer.h` (Public)


#### struct `uba::Timer`  
`struct Timer`  
_L28-39_
- L30 _public function_ `Timer(Timer &o)`
- L31 _public prototype_ `Timer() = default;`
- L32 _public function_ `Timer(u64 t, u32 c) : time(t), count(c)`
- L33 _public function_ `Timer(Timer&& o) noexcept : time(o.time.load()), count(o.count.load())`
- L34 _public function_ `void operator=(const Timer& o)`
- L35 _public member_ `Atomic<u64> time;`
- L36 _public member_ `Atomic<u32> count;`
- L37 _public function_ `void operator+=(const Timer& o)`
- L38 _public function_ `bool operator==(const Timer& o) const`

#### struct `uba::ExtendedTimer`  
`struct ExtendedTimer : Timer`  
_L43-46_
- inherits: `Timer`
- L45 _public member_ `AtomicU64 longest;`

#### struct `uba::TimerScope`  
`struct TimerScope`  
_L50-60_
- L52 _public function_ `TimerScope(Timer& t) : timer(t), start(GetTime())`
- L53 _public function_ `~TimerScope()`
- L54 _public function_ `void Leave()`
- L55 _public function_ `void Cancel()`
- L56 _public member_ `Timer& timer;`
- L57 _public member_ `u64 start;`
- L58 _public prototype_ `TimerScope(const TimerScope&) = delete;`
- L59 _public prototype_ `void operator=(const TimerScope&) = delete;`

#### struct `uba::ExtendedTimerScope`  
`struct ExtendedTimerScope`  
_L64-76_
- L66 _public function_ `ExtendedTimerScope(ExtendedTimer& t) : timer(t), start(GetTime())`
- L67 _public function_ `~ExtendedTimerScope()`
- L74 _public member_ `ExtendedTimer& timer;`
- L75 _public member_ `u64 start;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L11 _prototype_ `u64 GetTime();` (scope `uba`) — Counter for time. Note this has no specific start time for 0
- L12 _prototype_ `u64 GetFrequency();` (scope `uba`) — Number of counts per second. GetTime() / GetFrequency() = seconds
- L13 _prototype_ `u64 GetSystemTimeUs();` (scope `uba`) — Get time in microseconds since 1 Jan 1970 00:00 UTC
- L15 _function_ `inline u64 TimeToUs(u64 time, u64 frequency)` (scope `uba`)
- L16 _function_ `inline u64 TimeToMs(u64 time, u64 frequency)` (scope `uba`)
- L17 _function_ `inline float TimeToS(u64 time, u64 frequency)` (scope `uba`)
- L19 _function_ `inline u64 TimeToUs(u64 time)` (scope `uba`)
- L20 _function_ `inline u64 TimeToMs(u64 time)` (scope `uba`)
- L21 _function_ `inline float TimeToS(u64 time)` (scope `uba`)
- L23 _function_ `inline u64 UsToTime(u64 us)` (scope `uba`)
- L24 _function_ `inline u64 MsToTime(u64 ms)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaUnorderedMap.h` (Public)


#### class `uba::UnorderedMap`  
`template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<>, typename NodeAlloc = Allocator, typename BucketAlloc = Allocator, typename SizeType = u64> class UnorderedMap`  
_L31-514_
- L34 _public typedef_ `using key_type = Key;`
- L35 _public typedef_ `using mapped_type = Value;`
- L36 _public typedef_ `using value_type = std::pair<const Key, Value>;`
- L37 _public typedef_ `using size_type = SizeType;`
- L38 _public typedef_ `using hasher = Hash;`
- L39 _public typedef_ `using key_equal = KeyEqual;`
- L128 _public prototype_ `UnorderedMap() = default;`
- L129 _public function_ `explicit UnorderedMap(const NodeAlloc& na, const BucketAlloc& ba = {}) : m_nodeAlloc(na), m_bucketAlloc(ba)`
- L130 _public function_ `explicit UnorderedMap(size_type reserveCount)`
- L131 _public function_ `UnorderedMap(const UnorderedMap& o)`
- L132 _public function_ `UnorderedMap(UnorderedMap&& o) noexcept`
- L134 _public function_ `~UnorderedMap()`
- L140 _public function_ `UnorderedMap& operator=(const UnorderedMap& o)`
- L150 _public function_ `UnorderedMap& operator=(UnorderedMap&& o) noexcept`
- L164 _public function_ `size_type size() const`
- L165 _public function_ `bool empty() const`
- L167 _public function_ `iterator begin()`
- L168 _public function_ `iterator end()`
- L169 _public function_ `const_iterator begin() const`
- L170 _public function_ `const_iterator end() const`
- L171 _public function_ `const_iterator cbegin() const`
- L172 _public function_ `const_iterator cend() const`
- L176 _public function_ `iterator find(const Key& k)`
- L185 _public function_ `const_iterator find(const Key& k) const`
- L194 _public function_ `bool contains(const Key& k) const`
- L196 _public function_ `size_type count(const Key& k) const`
- L200 _public function_ `Value& operator[](const Key& k)`
- L212 _public function_ `std::pair<iterator, bool> insert(const value_type& p)`
- L217 _public function_ `std::pair<iterator, bool> insert(value_type&& p)`
- L229 _public function_ `std::pair<iterator, bool> insert(P&& p)`
- L239 _public function_ `void insert(InputIt first, InputIt last)`
- L244 _public function_ `std::pair<iterator, bool> try_emplace(const Key& k)`
- L257 _public function_ `template<typename... Args> std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args)`
- L270 _public function_ `template<typename... Args> std::pair<iterator, bool> emplace(Args&&... args)`
- L279 _public function_ `size_type erase(const Key& k)`
- L299 _public function_ `iterator erase(const_iterator it)`
- L318 _public function_ `iterator erase(iterator it)`
- L320 _public function_ `void clear()`
- L332 _public function_ `void reserve(size_type n)`
- L339 _public function_ `void set_bucket_alloc(const BucketAlloc& alloc)` — UB if m_buckets is non-null.
- L344 _public function_ `void compact_buckets(const BucketAlloc& newAlloc, size_type minBucketCount = 0)`
- L374 _public function_ `void swap(UnorderedMap& o) noexcept`
- L381 _public function_ `void merge_move(UnorderedMap& o)`
- L422 _private function_ `template<typename It> It first_iter() const`
- L429 _private function_ `size_type bucket_of(const Key& k) const`
- L435 _private function_ `template<typename... Args> std::pair<iterator, bool> emplace_impl(const Key& k, Args&&... args)`
- L447 _private function_ `Node* create_node_piecewise(Node* next, const Key& k)`
- L455 _private function_ `template<typename... Args> Node* create_node_piecewise_args(Node* next, const Key& k, Args&&... args)`
- L465 _private function_ `template<typename P> Node* create_node_from_pair(Node* next, P&& p)`
- L472 _private function_ `void destroy_node(Node* n)`
- L478 _private function_ `void ensure_capacity()`
- L485 _private function_ `void rehash(size_type newCount)`
- L509 _private member_ `Node** m_buckets = nullptr;`
- L510 _private member_ `size_type m_bucketCount = 0;`
- L511 _private member_ `size_type m_size = 0;`
- L512 _private member_ `NodeAlloc m_nodeAlloc;`
- L513 _private member_ `BucketAlloc m_bucketAlloc;`

#### struct `uba::UnorderedMap::Node`  
`struct Node`  
_L42-56_
- L44 _public member_ `value_type kv;`
- L45 _public member_ `Node* next;`
- L48 _public function_ `template<typename K_, typename... VArgs> Node(Node* n, std::piecewise_construct_t, std::tuple<K_> kt, std::tuple<VArgs...> vt) : kv(std::piecewise_construct, std::move(kt), std::move(vt)) , next(n)`
- L53 _public function_ `template<typename P> Node(Node* n, P&& p) : kv(std::forward<P>(p)) , next(n)`

#### class `uba::UnorderedMap::iterator`  
`class iterator`  
_L61-92_
- L64 _public typedef_ `using value_type = UnorderedMap::value_type;`
- L65 _public typedef_ `using reference = value_type&;`
- L66 _public typedef_ `using pointer = value_type*;`
- L68 _public prototype_ `iterator() = default;`
- L69 _public function_ `iterator(const UnorderedMap* m, size_type b, Node* n) : m_map(m), m_bucket(b), m_node(n)`
- L71 _public function_ `reference operator*() const`
- L72 _public function_ `pointer operator->() const`
- L74 _public function_ `iterator& operator++()`
- L84 _public function_ `iterator operator++(int)`
- L86 _public function_ `bool operator==(const iterator& o) const`
- L87 _public function_ `bool operator!=(const iterator& o) const`
- L89 _public member_ `const UnorderedMap* m_map = nullptr;`
- L90 _public member_ `size_type m_bucket = 0;`
- L91 _public member_ `Node* m_node = nullptr;`

#### class `uba::UnorderedMap::const_iterator`  
`class const_iterator`  
_L94-126_
- L97 _public typedef_ `using value_type = UnorderedMap::value_type;`
- L98 _public typedef_ `using reference = const value_type&;`
- L99 _public typedef_ `using pointer = const value_type*;`
- L101 _public prototype_ `const_iterator() = default;`
- L102 _public function_ `const_iterator(const UnorderedMap* m, size_type b, const Node* n) : m_map(m), m_bucket(b), m_node(n)`
- L103 _public function_ `const_iterator(iterator it) : m_map(it.m_map), m_bucket(it.m_bucket), m_node(it.m_node)`
- L105 _public function_ `reference operator*() const`
- L106 _public function_ `pointer operator->() const`
- L108 _public function_ `const_iterator& operator++()`
- L118 _public function_ `const_iterator operator++(int)`
- L120 _public function_ `bool operator==(const const_iterator& o) const`
- L121 _public function_ `bool operator!=(const const_iterator& o) const`
- L123 _public member_ `const UnorderedMap* m_map = nullptr;`
- L124 _public member_ `size_type m_bucket = 0;`
- L125 _public member_ `const Node* m_node = nullptr;`

#### class `uba::UnorderedSet`  
`template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<>, typename NodeAlloc = Allocator, typename BucketAlloc = Allocator> class UnorderedSet`  
_L519-828_
- L522 _public typedef_ `using key_type = Key;`
- L523 _public typedef_ `using value_type = Key;`
- L524 _public typedef_ `using size_type = u64;`
- L564 _public typedef_ `using iterator = const_iterator;` — set iterators expose const keys only
- L566 _public prototype_ `UnorderedSet() = default;`
- L567 _public function_ `explicit UnorderedSet(const NodeAlloc& na, const BucketAlloc& ba = {}) : m_nodeAlloc(na), m_bucketAlloc(ba)`
- L568 _public function_ `explicit UnorderedSet(size_type reserveCount)`
- L569 _public function_ `UnorderedSet(const UnorderedSet& o)`
- L570 _public function_ `UnorderedSet(UnorderedSet&& o) noexcept`
- L572 _public function_ `~UnorderedSet()`
- L578 _public function_ `UnorderedSet& operator=(const UnorderedSet& o)`
- L584 _public function_ `UnorderedSet& operator=(UnorderedSet&& o) noexcept`
- L596 _public function_ `size_type size() const`
- L597 _public function_ `bool empty() const`
- L599 _public function_ `iterator begin()`
- L600 _public function_ `iterator end()`
- L601 _public function_ `const_iterator begin() const`
- L602 _public function_ `const_iterator end() const`
- L603 _public function_ `const_iterator cbegin() const`
- L604 _public function_ `const_iterator cend() const`
- L606 _public function_ `const_iterator find(const Key& k) const`
- L615 _public function_ `iterator find(const Key& k)`
- L620 _public function_ `bool contains(const Key& k) const`
- L622 _public function_ `size_type count(const Key& k) const`
- L624 _public function_ `std::pair<const_iterator, bool> insert(const Key& k)`
- L636 _public function_ `std::pair<const_iterator, bool> insert(Key&& k)`
- L651 _public function_ `void insert(InputIt first, InputIt last)`
- L657 _public function_ `template<typename... Args> std::pair<const_iterator, bool> emplace(Args&&... args)`
- L663 _public function_ `size_type erase(const Key& k)`
- L683 _public function_ `const_iterator erase(const_iterator it)`
- L702 _public function_ `void clear()`
- L714 _public function_ `void reserve(size_type n)`
- L720 _public function_ `void swap(UnorderedSet& o) noexcept`
- L727 _public function_ `void merge_move(UnorderedSet& o)`
- L767 _private function_ `const_iterator first_iter() const`
- L774 _private function_ `size_type bucket_of(const Key& k) const`
- L780 _private function_ `template<typename K_> Node* create_node(Node* next, K_&& k)`
- L787 _private function_ `void destroy_node(Node* n)`
- L793 _private function_ `void ensure_capacity()`
- L799 _private function_ `void rehash(size_type newCount)`
- L823 _private member_ `Node** m_buckets = nullptr;`
- L824 _private member_ `size_type m_bucketCount = 0;`
- L825 _private member_ `size_type m_size = 0;`
- L826 _private member_ `NodeAlloc m_nodeAlloc;`
- L827 _private member_ `BucketAlloc m_bucketAlloc;`

#### struct `uba::UnorderedSet::Node`  
`struct Node`  
_L527-533_
- L529 _public member_ `Key key;`
- L530 _public member_ `Node* next;`
- L532 _public function_ `template<typename K_> Node(Node* n, K_&& k) : key(std::forward<K_>(k)), next(n)`

#### class `uba::UnorderedSet::const_iterator`  
`class const_iterator`  
_L536-563_
- L539 _public prototype_ `const_iterator() = default;`
- L540 _public function_ `const_iterator(const UnorderedSet* m, size_type b, const Node* n) : m_set(m), m_bucket(b), m_node(n)`
- L542 _public function_ `const Key& operator*() const`
- L543 _public function_ `const Key* operator->() const`
- L545 _public function_ `const_iterator& operator++()`
- L555 _public function_ `const_iterator operator++(int)`
- L557 _public function_ `bool operator==(const const_iterator& o) const`
- L558 _public function_ `bool operator!=(const const_iterator& o) const`
- L560 _public member_ `const UnorderedSet* m_set = nullptr;`
- L561 _public member_ `size_type m_bucket = 0;`
- L562 _public member_ `const Node* m_node = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L13 _namespace_ `namespace detail` (scope `uba`)
- L16 _function_ `template<typename T> inline T next_pow2(T v)` (scope `uba::detail`)
- L833 _typedef_ `template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename NodeAlloc = GrowingAllocator> using GrowingUnorderedMap = UnorderedMap<Key, Value, Hash, KeyEqual, NodeAlloc>;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaVector.h` (Public)


#### struct `uba::detail::HasTryGrowInPlace`  
`template<typename A, typename = void> struct HasTryGrowInPlace : std::false_type`  
_L19-19_
- inherits: `std::false_type`
- desc: Detect whether an allocator exposes `try_grow_in_place(p, oldN, newN)`. Enables Vector to extend in-place on bump allocators (GrowingAllocator[NoLock]) without reallocating + copying the old buffer.

#### struct `uba::detail::HasTryGrowInPlace`  
`template<typename A> struct HasTryGrowInPlace<A, std::void_t< decltype(std::declval<A&>().TryGrowInPlace( std::declval<typename A::value_type*>(), std::declval<u64>(), std::declval<u64>()))>> : std::true_type`  
_L22-26_
- inherits: `std::true_type`

#### class `uba::Vector`  
`template<typename T, typename Alloc = Allocator> class Vector`  
_L31-382_
- desc: Minimal std::vector replacement. Contiguous storage; doubles capacity on grow.
- L34 _public typedef_ `using value_type = T;`
- L35 _public typedef_ `using size_type = u64;`
- L36 _public typedef_ `using iterator = T*;`
- L37 _public typedef_ `using const_iterator = const T*;`
- L38 _public typedef_ `using reference = T&;`
- L39 _public typedef_ `using const_reference = const T&;`
- L41 _public prototype_ `Vector() = default;`
- L43 _public function_ `explicit Vector(const Alloc& a) : m_alloc(a)`
- L45 _public function_ `explicit Vector(size_type n)`
- L47 _public function_ `Vector(size_type n, const T& v)`
- L49 _public function_ `Vector(std::initializer_list<T> il)`
- L56 _public function_ `template<typename It> Vector(It first, It last)`
- L61 _public function_ `Vector(const Vector& o)`
- L67 _public function_ `Vector(Vector&& o) noexcept`
- L69 _public function_ `~Vector()`
- L75 _public function_ `Vector& operator=(const Vector& o)`
- L86 _public function_ `Vector& operator=(Vector&& o) noexcept`
- L98 _public function_ `Vector& operator=(std::initializer_list<T> il)`
- L106 _public function_ `T* data()`
- L107 _public function_ `const T* data() const`
- L108 _public function_ `size_type size() const`
- L109 _public function_ `size_type capacity() const`
- L110 _public function_ `bool empty() const`
- L112 _public function_ `T& operator[](size_type i)`
- L113 _public function_ `const T& operator[](size_type i) const`
- L114 _public function_ `T& at(size_type i)`
- L115 _public function_ `const T& at(size_type i) const`
- L117 _public function_ `T& front()`
- L118 _public function_ `const T& front() const`
- L119 _public function_ `T& back()`
- L120 _public function_ `const T& back() const`
- L122 _public function_ `iterator begin()`
- L123 _public function_ `iterator end()`
- L124 _public function_ `const_iterator begin() const`
- L125 _public function_ `const_iterator end() const`
- L126 _public function_ `const_iterator cbegin() const`
- L127 _public function_ `const_iterator cend() const`
- L156 _public function_ `reverse_iterator rbegin()`
- L157 _public function_ `reverse_iterator rend()`
- L158 _public function_ `const_reverse_iterator rbegin() const`
- L159 _public function_ `const_reverse_iterator rend() const`
- L161 _public function_ `void clear()`
- L168 _public function_ `void reserve(size_type n)`
- L207 _public function_ `void resize(size_type n)`
- L223 _public function_ `void resize(size_type n, const T& v)`
- L239 _public function_ `void shrink_to_fit()`
- L241 _public function_ `void push_back(const T& v)`
- L248 _public function_ `void push_back(T&& v)`
- L256 _public function_ `template<typename... Args> T& emplace_back(Args&&... args)`
- L265 _public function_ `void pop_back()`
- L272 _public function_ `iterator insert(const_iterator pos, const T& v)`
- L291 _public function_ `iterator insert(const_iterator pos, T&& v)`
- L312 _public function_ `template<typename InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)` — Range insert: insert [first, last) at `pos`.
- L332 _public function_ `iterator erase(const_iterator pos)`
- L343 _public function_ `iterator erase(const_iterator first, const_iterator last)`
- L358 _public function_ `void swap(Vector& o) noexcept`
- L369 _private function_ `void grow_to(size_type n)` — Geometric growth helper used by resize/insert/push_back. Matches std::vector's policy: capacity at least doubles on every grow, so N successive resize(1..N) calls cost O(N) amortized instead of O(N^2) that a plain reserve(n) would give.
- L376 _private function_ `void grow_one()`
- L378 _private member_ `T* m_data = nullptr;`
- L379 _private member_ `size_type m_size = 0;`
- L380 _private member_ `size_type m_capacity = 0;`
- L381 _private member_ `Alloc m_alloc;`

#### class `uba::Vector::reverse_iterator`  
`class reverse_iterator`  
_L130-142_
- desc: Minimal reverse iterators — forward-incrementing, stepping backward.
- L133 _public prototype_ `reverse_iterator() = default;`
- L134 _public function_ `reverse_iterator(T* p) : m_p(p)`
- L135 _public function_ `T& operator*() const`
- L136 _public function_ `T* operator->() const`
- L137 _public function_ `reverse_iterator& operator++()`
- L138 _public function_ `reverse_iterator operator++(int)`
- L139 _public function_ `bool operator==(const reverse_iterator& o) const`
- L140 _public function_ `bool operator!=(const reverse_iterator& o) const`
- L141 _public member_ `T* m_p = nullptr;`

#### class `uba::Vector::const_reverse_iterator`  
`class const_reverse_iterator`  
_L143-155_
- L146 _public prototype_ `const_reverse_iterator() = default;`
- L147 _public function_ `const_reverse_iterator(const T* p) : m_p(p)`
- L148 _public function_ `const T& operator*() const`
- L149 _public function_ `const T* operator->() const`
- L150 _public function_ `const_reverse_iterator& operator++()`
- L151 _public function_ `const_reverse_iterator operator++(int)`
- L152 _public function_ `bool operator==(const const_reverse_iterator& o) const`
- L153 _public function_ `bool operator!=(const const_reverse_iterator& o) const`
- L154 _public member_ `const T* m_p = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`
- L13 _namespace_ `namespace detail` (scope `uba`)
- L385 _function_ `template<typename T, typename A> bool operator==(const Vector<T, A>& a, const Vector<T, A>& b)` (scope `uba`)
- L392 _function_ `template<typename T, typename A> bool operator!=(const Vector<T, A>& a, const Vector<T, A>& b)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaWinBinDependencyParser.h` (Public)


#### struct `uba::BinaryInfo`  
`struct BinaryInfo`  
_L18-20_

#### Free symbols / members of external scopes

- L11 _macro_ `#define True_CreateFileMappingW ::CreateFileMappingW`
- L12 _macro_ `#define True_MapViewOfFile ::MapViewOfFile`
- L13 _macro_ `#define True_UnmapViewOfFile ::UnmapViewOfFile`
- L16 _namespace_ `namespace uba`
- L25 _variable_ `static const wchar_t* g_knownSystemFiles[] =` (scope `uba`) — These dlls should _always_ exist on all machines so we can filter them out from the list of imports to copy It should somewhat match what is found in Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\KnownDLLs but also take info from wine source code which dlls that are custom implemented for wine.
- L90 _function_ `inline bool IsKnownSystemFile(const tchar* fileName)` (scope `uba`)
- L98 _function_ `return uba::BinarySearch(g_knownSystemFiles, g_knownSystemFiles + sizeof_array(g_knownSystemFiles), nameLower.data, [](const wchar_t* a, const wchar_t* b) { return TStrcmp(a, b) < 0; });` (scope `uba::IsKnownSystemFile`)
- L101 _function_ `inline DWORD GetOffset(DWORD rva, PIMAGE_SECTION_HEADER psh, PIMAGE_NT_HEADERS pnt)` (scope `uba`)
- L112 _prototype_ `DWORD UbaExceptionHandlerAllowAccessViolation(DWORD code, _EXCEPTION_POINTERS* info, const tchar* fileName);` (scope `uba`)
- L114 _function_ `inline bool FindImportsInMem(StringView fileName, void* mem, u64 memSize, const Function<void(const tchar* import, bool isKnown, const tchar* const* importLoaderPaths)>& func, StringBufferBase& outError)` (scope `uba`)
- L150 _function_ `inline bool ParseBinary(const StringView& filePath, const StringView& originalPath, BinaryInfo& outInfo, const Function<void(const tchar* import, bool isKnown, const tchar* const* importLoaderPaths)>& func, StringBufferBase& outError)` (scope `uba`)
- L164 _function_ `auto closeFileHandle = MakeGuard([&]() { CloseHandle(fileHandle); });` (scope `uba::ParseBinary`)
- L168 _function_ `auto closeMappingHandle = MakeGuard([&]() { CloseHandle(fileMapping); });` (scope `uba::ParseBinary`)
- L172 _function_ `auto unmap = MakeGuard([&]() { True_UnmapViewOfFile(mem); });` (scope `uba::ParseBinary`)

### `Source/Programs/UnrealBuildAccelerator/Core/Public/UbaWinTypes.h` (Public)


#### struct `FILE_DIRECTORY_INFORMATION`  
`struct FILE_DIRECTORY_INFORMATION`  
_L8-20_
- L9 _public member_ `ULONG NextEntryOffset;`
- L10 _public member_ `ULONG FileIndex;`
- L11 _public member_ `LARGE_INTEGER CreationTime;`
- L12 _public member_ `LARGE_INTEGER LastAccessTime;`
- L13 _public member_ `LARGE_INTEGER LastWriteTime;`
- L14 _public member_ `LARGE_INTEGER ChangeTime;`
- L15 _public member_ `LARGE_INTEGER EndOfFile;`
- L16 _public member_ `LARGE_INTEGER AllocationSize;`
- L17 _public member_ `ULONG FileAttributes;`
- L18 _public member_ `ULONG FileNameLength;`
- L19 _public member_ `WCHAR FileName[1];`

#### struct `FILE_FULL_DIR_INFORMATION`  
`struct FILE_FULL_DIR_INFORMATION`  
_L22-35_
- L23 _public member_ `ULONG NextEntryOffset;`
- L24 _public member_ `ULONG FileIndex;`
- L25 _public member_ `LARGE_INTEGER CreationTime;`
- L26 _public member_ `LARGE_INTEGER LastAccessTime;`
- L27 _public member_ `LARGE_INTEGER LastWriteTime;`
- L28 _public member_ `LARGE_INTEGER ChangeTime;`
- L29 _public member_ `LARGE_INTEGER EndOfFile;`
- L30 _public member_ `LARGE_INTEGER AllocationSize;`
- L31 _public member_ `ULONG FileAttributes;`
- L32 _public member_ `ULONG FileNameLength;`
- L33 _public member_ `ULONG EaSize;`
- L34 _public member_ `WCHAR FileName[1];`

#### struct `FILE_ID_BOTH_DIR_INFORMATION`  
`struct FILE_ID_BOTH_DIR_INFORMATION`  
_L37-53_
- L38 _public member_ `ULONG NextEntryOffset;`
- L39 _public member_ `ULONG FileIndex;`
- L40 _public member_ `LARGE_INTEGER CreationTime;`
- L41 _public member_ `LARGE_INTEGER LastAccessTime;`
- L42 _public member_ `LARGE_INTEGER LastWriteTime;`
- L43 _public member_ `LARGE_INTEGER ChangeTime;`
- L44 _public member_ `LARGE_INTEGER EndOfFile;`
- L45 _public member_ `LARGE_INTEGER AllocationSize;`
- L46 _public member_ `ULONG FileAttributes;`
- L47 _public member_ `ULONG FileNameLength;`
- L48 _public member_ `ULONG EaSize;`
- L49 _public member_ `CCHAR ShortNameLength;`
- L50 _public member_ `WCHAR ShortName[12];`
- L51 _public member_ `LARGE_INTEGER FileId;`
- L52 _public member_ `WCHAR FileName[1];`

#### struct `FILE_BASIC_INFORMATION`  
`struct FILE_BASIC_INFORMATION`  
_L55-61_
- L56 _public member_ `LARGE_INTEGER CreationTime;`
- L57 _public member_ `LARGE_INTEGER LastAccessTime;`
- L58 _public member_ `LARGE_INTEGER LastWriteTime;`
- L59 _public member_ `LARGE_INTEGER ChangeTime;`
- L60 _public member_ `ULONG FileAttributes;`

#### struct `FILE_FS_DEVICE_INFORMATION`  
`struct FILE_FS_DEVICE_INFORMATION`  
_L63-67_
- L65 _public member_ `DEVICE_TYPE DeviceType;`
- L66 _public member_ `ULONG Characteristics;`

#### struct `FILE_FS_ATTRIBUTE_INFORMATION`  
`struct FILE_FS_ATTRIBUTE_INFORMATION`  
_L72-78_
- L74 _public member_ `ULONG FileSystemAttributes;`
- L75 _public member_ `LONG MaximumComponentNameLength;`
- L76 _public member_ `ULONG FileSystemNameLength;`
- L77 _public member_ `WCHAR FileSystemName[1];`

#### struct `FILE_NETWORK_OPEN_INFORMATION`  
`struct FILE_NETWORK_OPEN_INFORMATION`  
_L80-89_
- L82 _public member_ `LARGE_INTEGER CreationTime;`
- L83 _public member_ `LARGE_INTEGER LastAccessTime;`
- L84 _public member_ `LARGE_INTEGER LastWriteTime;`
- L85 _public member_ `LARGE_INTEGER ChangeTime;`
- L86 _public member_ `LARGE_INTEGER AllocationSize;`
- L87 _public member_ `LARGE_INTEGER EndOfFile;`
- L88 _public member_ `ULONG FileAttributes;`

#### struct `FILE_POSITION_INFORMATION`  
`struct FILE_POSITION_INFORMATION`  
_L91-94_
- L93 _public member_ `LARGE_INTEGER CurrentByteOffset;`

#### struct `FILE_END_OF_FILE_INFORMATION`  
`struct FILE_END_OF_FILE_INFORMATION`  
_L96-99_
- L98 _public member_ `LARGE_INTEGER EndOfFile;`

#### struct `FILE_STANDARD_INFORMATION`  
`struct FILE_STANDARD_INFORMATION`  
_L101-107_
- L102 _public member_ `LARGE_INTEGER AllocationSize;`
- L103 _public member_ `LARGE_INTEGER EndOfFile;`
- L104 _public member_ `ULONG NumberOfLinks;`
- L105 _public member_ `BOOLEAN DeletePending;`
- L106 _public member_ `BOOLEAN Directory;`

#### struct `FILE_RENAME_INFORMATION`  
`struct FILE_RENAME_INFORMATION`  
_L109-117_
- L113 _public member_ `} DUMMYUNIONNAME;`
- L114 _public member_ `HANDLE RootDirectory;`
- L115 _public member_ `ULONG FileNameLength;`
- L116 _public member_ `WCHAR FileName[1];`

#### union `FILE_RENAME_INFORMATION::(anonymous)`  
`union`  
_L110-113_

#### struct `FILE_IS_REMOTE_DEVICE_INFORMATION`  
`struct FILE_IS_REMOTE_DEVICE_INFORMATION`  
_L119-122_
- L121 _public member_ `BOOLEAN IsRemote;`

#### struct `FILE_ID_INFORMATION`  
`struct FILE_ID_INFORMATION`  
_L124-128_
- L126 _public member_ `ULONGLONG VolumeSerialNumber;`
- L127 _public member_ `FILE_ID_128 FileId;`

#### struct `FILE_NAME_INFORMATION`  
`struct FILE_NAME_INFORMATION`  
_L130-134_
- L132 _public member_ `ULONG FileNameLength;`
- L133 _public member_ `WCHAR FileName[1];`

#### struct `FILE_INTERNAL_INFORMATION`  
`struct FILE_INTERNAL_INFORMATION`  
_L136-139_
- L138 _public member_ `LARGE_INTEGER IndexNumber;`

#### struct `FILE_EA_INFORMATION`  
`struct FILE_EA_INFORMATION`  
_L141-144_
- L143 _public member_ `ULONG EaSize;`

#### struct `FILE_ACCESS_INFORMATION`  
`struct FILE_ACCESS_INFORMATION`  
_L146-149_
- L148 _public member_ `ACCESS_MASK AccessFlags;`

#### struct `FILE_MODE_INFORMATION`  
`struct FILE_MODE_INFORMATION`  
_L151-154_
- L153 _public member_ `ULONG Mode;`

#### struct `FILE_ALIGNMENT_INFORMATION`  
`struct FILE_ALIGNMENT_INFORMATION`  
_L156-159_
- L158 _public member_ `ULONG AlignmentRequirement;`

#### struct `FILE_DISPOSITION_INFORMATION`  
`struct FILE_DISPOSITION_INFORMATION`  
_L161-164_
- L163 _public member_ `BOOLEAN DeleteFile;`

#### struct `FILE_ALLOCATION_INFORMATION`  
`struct FILE_ALLOCATION_INFORMATION`  
_L166-169_
- L168 _public member_ `LARGE_INTEGER AllocationSize;`

#### struct `FILE_ALL_INFORMATION`  
`struct FILE_ALL_INFORMATION`  
_L171-182_
- L173 _public member_ `FILE_BASIC_INFORMATION BasicInformation;`
- L174 _public member_ `FILE_STANDARD_INFORMATION StandardInformation;`
- L175 _public member_ `FILE_INTERNAL_INFORMATION InternalInformation;`
- L176 _public member_ `FILE_EA_INFORMATION EaInformation;`
- L177 _public member_ `FILE_ACCESS_INFORMATION AccessInformation;`
- L178 _public member_ `FILE_POSITION_INFORMATION PositionInformation;`
- L179 _public member_ `FILE_MODE_INFORMATION ModeInformation;`
- L180 _public member_ `FILE_ALIGNMENT_INFORMATION AlignmentInformation;`
- L181 _public member_ `FILE_NAME_INFORMATION NameInformation;`

#### struct `FILE_FS_VOLUME_INFORMATION`  
`struct FILE_FS_VOLUME_INFORMATION`  
_L184-190_
- L185 _public member_ `LARGE_INTEGER VolumeCreationTime;`
- L186 _public member_ `ULONG VolumeSerialNumber;`
- L187 _public member_ `ULONG VolumeLabelLength;`
- L188 _public member_ `BOOLEAN SupportsObjects;`
- L189 _public member_ `WCHAR VolumeLabel[1];`

#### enum `FS_INFORMATION_CLASS`  
`enum FS_INFORMATION_CLASS : int`  
_L217-217_

#### enum `RTL_PATH_TYPE`  
`enum RTL_PATH_TYPE`  
_L223-233_
- L225 _public enumerator_ `RtlPathTypeUnknown = 0`
- L226 _public enumerator_ `RtlPathTypeUncAbsolute` — "//foo"
- L227 _public enumerator_ `RtlPathTypeDriveAbsolute` — "c:/foo"
- L228 _public enumerator_ `RtlPathTypeDriveRelative` — "c:foo"
- L229 _public enumerator_ `RtlPathTypeRooted` — "/foo"
- L230 _public enumerator_ `RtlPathTypeRelative` — "foo"
- L231 _public enumerator_ `RtlPathTypeLocalDevice` — "//./foo"
- L232 _public enumerator_ `RtlPathTypeRootLocalDevice` — "//."

#### struct `RTL_RELATIVE_NAME_U`  
`struct RTL_RELATIVE_NAME_U`  
_L235-240_
- L237 _public member_ `UNICODE_STRING RelativeName;`
- L238 _public member_ `HANDLE ContainingDirectory;`
- L239 _public member_ `PVOID CurDirRef;`

#### struct `FILE_IO_COMPLETION_INFORMATION`  
`struct FILE_IO_COMPLETION_INFORMATION`  
_L242-247_
- L244 _public member_ `PVOID KeyContext;`
- L245 _public member_ `PVOID ApcContext;`
- L246 _public member_ `IO_STATUS_BLOCK IoStatusBlock;`

#### Free symbols / members of external scopes

- L68 _variable_ `constexpr ULONG FILE_REMOTE_DEVICE = 0x00000010;`
- L69 _variable_ `constexpr ULONG FILE_DEVICE_IS_MOUNTED = 0x00000020;`
- L111 _member_ `BOOLEAN ReplaceIfExists;` (scope `FILE_RENAME_INFORMATION::__anon55b32192010a`) — FileRenameInformation
- L112 _member_ `ULONG Flags;` (scope `FILE_RENAME_INFORMATION::__anon55b32192010a`) — FileRenameInformationEx
- L192 _macro_ `#define FILE_INFO_CLASSES \`
- L211 _macro_ `#define FILE_INFO_CLASS(name, value) [[maybe_unused]] const FILE_INFORMATION_CLASS name = (FILE_INFORMATION_CLASS)value;` — const (not constexpr): clang rejects the out-of-range cast to this fixed-type-less winternl enum in a constant expression.
- L215 _variable_ `constexpr OBJECT_INFORMATION_CLASS ObjectNameInformation = (OBJECT_INFORMATION_CLASS)1;`
- L219 _variable_ `constexpr FS_INFORMATION_CLASS FileFsVolumeInformation = (FS_INFORMATION_CLASS)1;`
- L220 _variable_ `constexpr FS_INFORMATION_CLASS FileFsDeviceInformation = (FS_INFORMATION_CLASS)4;`
- L221 _variable_ `constexpr FS_INFORMATION_CLASS FileFsAttributeInformation = (FS_INFORMATION_CLASS)5;`
