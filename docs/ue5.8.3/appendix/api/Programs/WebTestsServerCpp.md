# Programs / WebTestsServerCpp

- module root: `Source/Programs/WebTestsServerCpp`
- headers: 1; symbols: 8
- symbol kinds: member=2, prototype=5, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, HTTPServer, Json, Projects, Sockets, WebSocketServer
- PublicIncludePathModuleNames: Launch

### `Source/Programs/WebTestsServerCpp/Private/WebTestsServer.h` (Private)


#### struct `FDeferredResponse`  
`struct FDeferredResponse`  
_L12-16_
- L14 _public member_ `FHttpResultCallback OnComplete;`
- L15 _public member_ `TUniquePtr<FHttpServerResponse> Response;`

#### Free symbols / members of external scopes

- L18 _prototype_ `void EnqueueDeferredResponse(FHttpResultCallback&& OnComplete, TUniquePtr<FHttpServerResponse>&& Response);`
- L19 _prototype_ `void FlushDeferredResponses();`
- L21 _prototype_ `void StartHttpServer(uint32 Port);`
- L22 _prototype_ `void StartWebSocketServer(uint32 Port);`
- L23 _prototype_ `int32 RunWebTestsServer(int32 ArgC, TCHAR** ArgV);`
