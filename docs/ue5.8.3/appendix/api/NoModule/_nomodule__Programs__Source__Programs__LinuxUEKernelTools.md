# NoModule / _nomodule__Programs__Source__Programs__LinuxUEKernelTools

- module root: `.`
- headers: 1; symbols: 27
- symbol kinds: enum=1, enumerator=2, function=5, macro=2, member=10, struct=3, typedef=3, union=1

### `Source/Programs/LinuxUEKernelTools/LinuxUEKernelToolsShared.h` (Other)


#### struct `LinuxUEKernelToolsIPC`  
`struct LinuxUEKernelToolsIPC`  
_L39-91_
- L41 _public member_ `static constexpr size_t MAX_EVENTS_PER_PACKET = 256;` — maximum number of packets sent over the IPC socket in a single sendto()
- L43 _public member_ `int Fd;`
- L45 _public function_ `LinuxUEKernelToolsIPC() : Fd(INVALID_FD)`
- L55 _public function_ `~LinuxUEKernelToolsIPC()`
- L64 _public member_ `static constexpr size_t SocketBasePathMaxLen = sizeof(sockaddr_un::sun_path) - 10;` — reserve 8 chars for pid, 1 for /, and 1 for null char
- L65 _public function_ `static void FillSockAddrUn(sockaddr_un* Addr, const char* BasePath, pid_t Pid)`

#### struct `BPFEventCOWData`  
`typedef struct BPFEventCOWData`  
_L94-103_
- L96 _public member_ `uint64_t VirtualAddress;`
- L98 _public function_ `int32_t ToString(char* Buffer, size_t Len) const`

#### enum `EBPFEventType`  
`typedef enum EBPFEventType`  
_L105-109_
- L107 _public enumerator_ `BPFEventIgnore = 0`
- L108 _public enumerator_ `BPFEventCOW`

#### struct `BPFEvent`  
`typedef struct BPFEvent`  
_L112-144_
- L114 _public member_ `uint32_t Pid;`
- L115 _public member_ `uint32_t Tid;`
- L116 _public member_ `uint16_t _Reserved1;`
- L117 _public member_ `uint8_t Type;`
- L118 _public member_ `uint8_t _Reserved2;`
- L125 _public function_ `int32_t ToString(char* Buffer, size_t Len) const`

#### union `BPFEvent::(anonymous)`  
``  
_L120-122_

#### Free symbols / members of external scopes

- L33 _macro_ `#define INVALID_FD (-1)`
- L36 _macro_ `#define PRINTF_ANSI_STR "%hs"`
- L103 _typedef_ `} BPFEventCOWData;`
- L109 _typedef_ `BPFEventIgnore = 0, BPFEventCOW, } EBPFEventType;`
- L121 _member_ `BPFEventCOWData COW;` (scope `BPFEvent::__anon54ac9924010a`)
- L144 _typedef_ `} BPFEvent;`
