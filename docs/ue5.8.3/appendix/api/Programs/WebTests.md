# Programs / WebTests

- module root: `Source/Programs/WebTests`
- headers: 1; symbols: 17
- symbol kinds: class=1, externvar=1, function=7, member=7, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, EventLoop, HTTP, HTTPServer, Json, SSL, Sockets, WebSockets

### `Source/Programs/WebTests/Private/WebTestFixtures.h` (Private)


#### struct `FWebTestSettings`  
`struct FWebTestSettings`  
_L37-67_
- desc: Parses web test runtime settings from the command line. Http and WebSocket tests may use different ports on the same server host. Command-line parameters: -web_server_ip=<ip>                    (default: 127.0.0.1) -web_server_http_port=<port>            (default: 8000) -web_server_websockets_port=<port>      (default: 8001) -very_verbose=true                      (default: false) — enables VeryVerbose log level
- L39 _public function_ `FWebTestSettings() : WebServerIp(TEXT("127.0.0.1")) , WebServerHttpPort(8000) , WebServerWsPort(8001) , bVeryVerbose(false)`
- L52 _public function_ `FString HttpUrlBase() const` — Base HTTP URL: "http://<ip>:<port>"
- L55 _public function_ `FString UrlHttpTests() const` — URL prefix for the http test routes: "http://<ip>:<port>/webtests/httptests"
- L58 _public function_ `FString WsUrlBase() const` — Base WebSocket URL: "ws://<ip>:<wsport>"
- L61 _public function_ `FString UrlWebSocketsTests() const` — URL prefix for the websocket test routes: "ws://<ip>:<wsport>/webtests/websocketstests"
- L63 _public member_ `FString WebServerIp;`
- L64 _public member_ `uint32 WebServerHttpPort;`
- L65 _public member_ `uint32 WebServerWsPort;`
- L66 _public member_ `bool bVeryVerbose;`

#### class `FWebTestTickRunner`  
`class FWebTestTickRunner`  
_L76-97_
- desc: Helper that provides engine-tick simulation for integration tests that drive async operations (Http requests, WebSocket connections, etc.) from the game thread. Drives FTSBackgroundableTicker and FTSTicker at 60 FPS until RequestQuit() is called. Intended to be used as a member variable in test fixtures, not as a base class.
- L79 _public function_ `void SimulateEngineTick()`
- L86 _public function_ `void RunUntilQuitRequested()`
- L94 _public member_ `float TickFrequency = 1.0f / 60;`
- L95 _public member_ `bool bQuitRequested = false;` — float TickFrequency  = 1.0f / 60;  60 FPS
- L96 _public member_ `bool bSucceeded = false;`

#### Free symbols / members of external scopes

- L25 _externvar_ `extern TAutoConsoleVariable<bool> CVarHttpInsecureProtocolEnabled;` — Defined in HttpModule.cpp — allows tests to connect over plain http:// / ws://
