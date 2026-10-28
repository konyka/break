# NoModule / _nomodule__Developer__Source__Developer__ZenPluggableTransport__transport-sdk

- module root: `.`
- headers: 1; symbols: 36
- symbol kinds: class=5, enum=1, enumerator=6, macro=2, namespace=1, prototype=18, typedef=2, variable=1

### `Source/Developer/ZenPluggableTransport/transport-sdk/include/transportplugin.h` (Other)


#### class `zen::TransportServerConnection`  
`class TransportServerConnection`  
_L46-52_
- desc: Plugin-server interface for connection This is returned by a call to TransportServer::CreateConnectionHandler and there should be one instance created per established connection The plugin uses this interface to feed data into the server side protocol implementation which will parse the incoming messages and dispatch to appropriate request handlers and ultimately call into TransportConnection functions which write data back to the client
- L49 _public prototype_ `virtual uint32_t AddRef() const = 0;`
- L50 _public prototype_ `virtual uint32_t Release() const = 0;`
- L51 _public prototype_ `virtual void OnBytesRead(const void* Buffer, size_t DataSize) = 0;`

#### class `zen::TransportServer`  
`class TransportServer`  
_L61-65_
- desc: Server interface There will be one instance of this provided by the system to the transport plugin The plugin can use this to register new connections
- L64 _public prototype_ `virtual TransportServerConnection* CreateConnectionHandler(TransportConnection* Connection) = 0;`

#### class `zen::TransportLogger`  
`class TransportLogger`  
_L74-88_
- desc: Logger interface There will be one instance of this provided by the system to the transport plugin The plugin can use this to log messages back to zen server
- L87 _public prototype_ `virtual void LogMessage(LogLevel Level, const char* Message) = 0;`

#### enum `zen::TransportLogger::LogLevel`  
`enum class LogLevel : uint32_t`  
_L77-85_
- L79 _public enumerator_ `Trace = 0`
- L80 _public enumerator_ `Debug = 1`
- L81 _public enumerator_ `Info = 2`
- L82 _public enumerator_ `Warn = 3`
- L83 _public enumerator_ `Err = 4`
- L84 _public enumerator_ `Critical = 5`

#### class `zen::TransportPlugin`  
`class TransportPlugin`  
_L104-117_
- desc: Interface which needs to be implemented by a transport plugin This is responsible for setting up and running the communication for a given transport. Once initialized, the plugin should be ready to accept connections using its own execution resources (threads, thread pools etc)
- L107 _public prototype_ `virtual uint32_t AddRef() const = 0;`
- L108 _public prototype_ `virtual uint32_t Release() const = 0;`
- L109 _public prototype_ `virtual void Configure(const char* OptionTag, const char* OptionValue) = 0;`
- L110 _public prototype_ `virtual void Initialize(TransportServer* ServerInterface) = 0;`
- L111 _public prototype_ `virtual void Shutdown() = 0;`
- L112 _public prototype_ `virtual const char* GetDebugName() = 0;`
- L116 _public prototype_ `virtual bool IsAvailable() = 0;` — Check whether this transport is usable.

#### class `zen::TransportConnection`  
`class TransportConnection`  
_L127-134_
- desc: A transport plugin provider needs to implement this interface The plugin should create one instance of this per established connection and register it with the TransportServer instance CreateConnectionHandler() function. The server will subsequently use this interface to write response data back to the client and to manage the connection life cycle in general
- L130 _public prototype_ `virtual int64_t WriteBytes(const void* Buffer, size_t DataSize) = 0;`
- L131 _public prototype_ `virtual void Shutdown(bool Receive, bool Transmit) = 0;`
- L132 _public prototype_ `virtual void CloseConnection() = 0;`
- L133 _public prototype_ `virtual const char* GetDebugName() = 0;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace zen`
- L21 _variable_ `static const uint32_t kTransportApiVersion = 1;` (scope `zen`) — Current API version, value will be incremented to represent breaking changes
- L139 _macro_ `# define DLL_TRANSPORT_API __declspec(dllexport)`
- L141 _macro_ `# define DLL_TRANSPORT_API`
- L152 _prototype_ `void GetTransportPluginVersion(uint32_t* OutApiVersion, uint32_t* OutPluginVersion);` — Provide information about plugin version Fills out API version (kTransportApiVersion) plugin was built against. Fills out plugin own version ever increasing version number, a copy of plugin with higher version will be used.
- L155 _prototype_ `zen::TransportPlugin* CreateTransportPlugin(zen::TransportLogger* Logger);` — Return nullptr if requested api version mismatches api version plugin was built against
- L158 _typedef_ `typedef void (*PfnGetTransportPluginVersion)(uint32_t* OutApiVersion, uint32_t* OutPluginVersion);`
- L160 _typedef_ `typedef zen::TransportPlugin* (*PfnCreateTransportPlugin)(zen::TransportLogger* Logger);`
