# Programs / UbaCli

- module root: `Source/Programs/UnrealBuildAccelerator/Cli`
- headers: 1; symbols: 33
- symbol kinds: class=1, function=7, member=23, namespace=1, struct=1
- PrivateDependencyModuleNames: UbaCommon

### `Source/Programs/UnrealBuildAccelerator/Cli/Private/UbaClient.h` (Private)


#### struct `uba::ClientInitInfo`  
`struct ClientInitInfo`  
_L11-24_
- L13 _public member_ `LogWriter& logWriter;`
- L14 _public member_ `NetworkBackend& networkBackend;`
- L15 _public member_ `const tchar* rootDir = nullptr;`
- L16 _public member_ `const tchar* host = TC("loc`
- L17 _public member_ `u16 port = DefaultPort;`
- L18 _public member_ `const tchar* zone = TC("");`
- L19 _public member_ `u32 maxProcessorCount = ~0u;`
- L20 _public member_ `u32 index = 0;`
- L21 _public member_ `bool createSession = true;`
- L22 _public member_ `bool addDirSuffix = true;`
- L23 _public member_ `bool useDependencyCrawler = false;`

#### class `uba::Client`  
`class Client`  
_L26-163_
- L29 _public function_ `bool Init(const ClientInitInfo& info)`
- L97 _public function_ `bool StartProxy(u16 proxyPort, const Guid& storageServerUid)`
- L120 _public function_ `NetworkBackend& GetProxyBackend(const tchar* host)`
- L125 _public function_ `~Client()`
- L148 _public member_ `TString m_host;`
- L149 _public member_ `u16 m_port;`
- L151 _public member_ `NetworkBackendMemory* networkBackendMem = nullptr;`
- L152 _public member_ `NetworkClient* networkClient = nullptr;`
- L153 _public member_ `StorageClient* storageClient = nullptr;`
- L154 _public member_ `SessionClient* sessionClient = nullptr;`
- L156 _public member_ `NetworkBackend* networkBackend = nullptr;`
- L157 _public member_ `NetworkServer* proxyNetworkServer = nullptr;`
- L158 _public member_ `StorageProxy* proxyStorage = nullptr;`
- L159 _public member_ `TString serverPrefix;`
- L161 _public member_ `Event m_loopDone;`
- L162 _public member_ `Thread m_loop;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L47 _function_ `storageClientInfo.getProxyBackendCallback = [](void* ud, const tchar* h) -> NetworkBackend&` (scope `uba::Client::Init`)
- L49 _function_ `storageClientInfo.startProxyCallback = [](void* ud, u16 p, const Guid& ssu)` (scope `uba::Client::Init`)
- L80 _function_ `` (scope `uba::Client::Init`)
