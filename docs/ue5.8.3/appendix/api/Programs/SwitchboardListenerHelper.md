# Programs / SwitchboardListenerHelper

- module root: `Source/Programs/SwitchboardListenerHelper`
- headers: 4; symbols: 43
- symbol kinds: class=2, delegate=1, macro=8, member=11, prototype=21
- DynamicallyLoadedModuleNames: Sockets
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Json, JsonUtilities, Networking, Projects, TraceLog
- PrivateIncludePathModuleNames: Launch

### `Source/Programs/SwitchboardListenerHelper/NvmlWrapper/Public/GpuClocker.h` (Public)


#### class `FGpuClocker`  
`class EXPORTLIB FGpuClocker`  
_L10-25_
- desc: Encapsulates the logic to lock/unlock gpu clocks
- L15 _public prototype_ `bool LockGpuClocks();` — Locks the gpu clocks to the maximum allowed
- L18 _public prototype_ `bool UnlockGpuClocks();` — Unlocks the gpu and memory clocks
- L21 _public prototype_ `bool GpuUnlockDevice(const uint32_t GpuIdx);` — Locks the given gpu and memory clocks to the maximum allowed
- L24 _public prototype_ `bool GpuLockDevice(const uint32_t GpuIdx);` — Unlocks the given gpu and memory clocks

### `Source/Programs/SwitchboardListenerHelper/NvmlWrapper/Public/NvmlWrapperPublic.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define EXPORTLIB __declspec(dllexport)`
- L7 _macro_ `#define IMPORTLIB __declspec(dllimport)`
- L9 _macro_ `#define EXPORTLIB __attribute__((visibility("default")))`
- L10 _macro_ `#define IMPORTLIB`
- L12 _macro_ `#define EXPORTLIB`

### `Source/Programs/SwitchboardListenerHelper/Private/SBLHelperService.h` (Private)


#### class `FSBLHelperService`  
`class FSBLHelperService`  
_L18-120_
- desc: Provides services that Switchboard listener cannot perform on its own due to required user privileges
- L22 _public prototype_ `~FSBLHelperService();`
- L25 _public prototype_ `void Start(uint16 Port = 8010);` — Starts the service and tcp server
- L28 _public prototype_ `void Stop();` — Stops the service and tcp server
- L31 _public prototype_ `bool IsRunning();` — Returns true if the service is currently running or not.
- L34 _public prototype_ `void Tick();` — Call periodically to perform service maintenance tasks
- L39 _private prototype_ `bool OnIncomingConnection(FSocket* InSocket, const FIPv4Endpoint& InEndpoint);` — Called when there is a new tcp client connection
- L49 _private prototype_ `bool ParseIncomingMessage(const FString& Message, const FIPv4Endpoint& InEndpoint);` — Parses and handles the specified incoming message @param Message The message to parse and handle. @param InEndpoint The endpoint that sent the given message. @return True if the message was parsed and handled
- L59 _private prototype_ `FString CreateMessage(const FString& Cmd, const TMap<FString, FString>& AdditionalFields);` — Creates a new message for the given command and additional fields @param Cmd The command to create this message for. @param AdditionalFields Any additional fields or parameters to include in the message. @return The created message, ready to be sent over the socket.
- L62 _private prototype_ `uint32 GetNextPacketId();` — Gets the next packet id to use when creating a new message. Monotonically increments. Skips zero.
- L65 _private prototype_ `bool SendMessage(const FString& InMessage, const FIPv4Endpoint& InEndpoint);` — Send the given message to the given endpoint
- L68 _private prototype_ `bool HandleCmdLock(const TSharedPtr<FJsonObject>& Json);` — Handles the lock gpu clock command
- L71 _private prototype_ `void HandlePendingConnections();` — Dequeues the pending new tcp client connections and sends a hello message
- L74 _private prototype_ `void ParseIncomingData();` — Parses all incoming data from all connected clients
- L77 _private prototype_ `void ManageGpuClocks();` — Locks/unlocks the gpu clocks depending on the Pids that are holding said request
- L80 _private prototype_ `void HandlePendingDisconnections();` — Removes stale client connections and clients who sent a bye cmd
- L83 _private prototype_ `void DisconnectClient(const FIPv4Endpoint& InClientEndpoint);` — Removes the given client endpoint from the list of active connections and frees related resources
- L88 _private member_ `TQueue<TPair<FIPv4Endpoint, TSharedPtr<FSocket>>, EQueueMode::Spsc> PendingConnections;` — List of incoming client connections that have not been handled yet
- L91 _private member_ `TMap<FIPv4Endpoint, TSharedPtr<FSocket>> Connections;` — List of active client connections
- L94 _private member_ `TQueue<FIPv4Endpoint, EQueueMode::Spsc> PendingDisconnections;` — List of client connections to be disconnected (due to inactivity or bye command)
- L97 _private member_ `TMap<FIPv4Endpoint, TArray<uint8>> ReceiveBuffer;` — Receive buffers dedicated to each client
- L100 _private member_ `bool bIsRunning = false;` — Flag indicating whether the service is currently running or not
- L103 _private member_ `uint32 NextPacketId = 1;` — Next packet id when creating a new message to be sent
- L106 _private member_ `TUniquePtr<FTcpListener> SocketListener;` — The listening tcp socket
- L109 _private member_ `std::atomic<int32> NumProcessesHoldingGpuClocks = 0;` — Count of processes that are holding gpu clock lock active
- L112 _private member_ `bool bGpuClocksLocked = false;` — Whether the gpu clocks have been locked by this service or not
- L115 _private member_ `TMap<FIPv4Endpoint, double> LastActivityTime;` — Last activity time for each client. Used to detect stale connections.
- L118 _private member_ `FGpuClocker GpuClocker;` — Used to lock/unlock the gpu clocks on demand

### `Source/Programs/SwitchboardListenerHelper/Private/SwitchboardListenerHelper.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define SBLHELPER_VERSION_MAJOR 1`
- L8 _macro_ `#define SBLHELPER_VERSION_MINOR 0`
- L9 _macro_ `#define SBLHELPER_VERSION_PATCH 0`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardListenerHelper, Verbose, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardListenerHelper, Verbose, All);`
