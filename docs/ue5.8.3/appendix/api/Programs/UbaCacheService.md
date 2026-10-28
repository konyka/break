# Programs / UbaCacheService

- module root: `Source/Programs/UnrealBuildAccelerator/CacheService`
- headers: 1; symbols: 11
- symbol kinds: class=1, member=3, namespace=1, prototype=5, typedef=1
- PrivateDependencyModuleNames: UbaCommon

### `Source/Programs/UnrealBuildAccelerator/CacheService/Private/UbaHttpServer.h` (Private)


#### class `uba::HttpServer`  
`class HttpServer`  
_L10-28_
- L13 _public prototype_ `HttpServer(LogWriter& logWriter, NetworkBackend& backend, const tchar* name = TC("UbaH`
- L15 _public typedef_ `using CommandHandler = Function<const char*(StringView command, StringBufferBase& arguments)>;`
- L16 _public prototype_ `void AddCommandHandler(const CommandHandler& handler);`
- L18 _public prototype_ `bool StartListen(u16 port);`
- L21 _private prototype_ `static bool ReceiveHeader(void* context, const Guid& connectionUid, u8* headerData, void*& outBodyContext, u8*& outBodyData, u32& outBodySize);`
- L22 _private prototype_ `static bool ReceiveBody(void* context, bool recvError, u8* headerData, void* bodyContext, u8* bodyData, u32 bodySize);`
- L25 _private member_ `MutableLogger m_logger;`
- L26 _private member_ `NetworkBackend& m_backend;`
- L27 _private member_ `CommandHandler m_handler;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
