# Runtime / IPC

- module root: `Source/Runtime/IPC`
- headers: 2; symbols: 13
- symbol kinds: class=2, function=8, member=2, namespace=1
- PrivateDependencyModuleNames: Core

### `Source/Runtime/IPC/Public/IPC.h` (Public)


#### class `IPC::FSynchronizedInterprocessMemory`  
`class FSynchronizedInterprocessMemory`  
_L17-177_
- desc: Example class for synchronized interprocess memory
- L20 _private member_ `FPlatformProcess::FSemaphore * Mutex;` — Lock that guards access to the memory region
- L23 _private member_ `FPlatformMemory::FSharedMemoryRegion * Memory;` — Low-level memory region
- L28 _private function_ `FSynchronizedInterprocessMemory(FPlatformProcess::FSemaphore * InMutex, FPlatformMemory::FSharedMemoryRegion * InMemory) : Mutex(InMutex) , Memory(InMemory)` — Constructor
- L41 _public function_ `~FSynchronizedInterprocessMemory()` — Destructor
- L59 _public function_ `static FSynchronizedInterprocessMemory * Create(const TCHAR* Name, SIZE_T Size)` — Creates a new synchronized interprocess memory object
- L86 _public function_ `static FSynchronizedInterprocessMemory * OpenExisting(const TCHAR* Name, SIZE_T Size)` — Opens existing synchronized interprocess memory object
- L114 _public function_ `bool Write(const FString& String, uint32 MaxMillisecondsToWait = 0)` — Writes string to shared memory @param String string to write @param MaxMillisecondsToWait max milliseconds to wait (if 0, wait forever) @return true if was able to write
- L150 _public function_ `bool Read(FString& OutString, uint32 MaxMillisecondsToWait = 0)` — Reads a string from shared memory @param String string to read into @param MaxMillisecondsToWait max milliseconds to wait (if 0, wait forever) @return true if read withing given time

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace IPC`

### `Source/Runtime/IPC/Public/IPCModule.h` (Public)


#### class `IIPCModule`  
`class IIPCModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IIPCModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
