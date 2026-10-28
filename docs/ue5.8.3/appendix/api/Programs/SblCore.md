# Programs / SblCore

- module root: `Source/Programs/SwitchboardListener/SblCore`
- headers: 25; symbols: 622
- symbol kinds: class=12, delegate=5, enum=4, enumerator=42, function=68, macro=29, member=236, namespace=19, prototype=151, struct=46, typedef=7, variable=3
- DynamicallyLoadedModuleNames: Sockets
- PrivateDependencyModuleNames: JWT, Json, JsonUtilities, MsQuicRuntime, NVAPI, TraceLog
- PrivateIncludePathModuleNames: Launch
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, MsQuic, Networking, Projects, SwitchboardCommon
- PublicIncludePathModuleNames: OpenSSL

### `Source/Programs/SwitchboardListener/SblCore/Internal/CpuUtilizationMonitor.h` (Internal)


#### class `FGenericCpuUtilizationMonitor`  
`class FGenericCpuUtilizationMonitor`  
_L15-37_
- desc: Default implementation does nothing (functionality optional and only implemented for some platforms). Instead, use the FCpuUtilizationMonitor typedef to get a platform-specific implementation if available.
- L18 _public function_ `virtual ~FGenericCpuUtilizationMonitor()`
- L22 _public function_ `virtual bool IsInitialized() const`
- L33 _public function_ `virtual bool GetPerCoreUtilization(TArray<int8>& OutCoreUtilization)` — Samples the current CPU utilization, provided as per-core values ranging from 0-100. @param OutCoreUtilization The array that will receive the sampled values. @return True if OutCoreUtilization is valid (new or recently cached values were available).

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCpuUtilizationMonitor, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCpuUtilizationMonitor, Log, All);`
- L43 _typedef_ `typedef FGenericCpuUtilizationMonitor FCpuUtilizationMonitor;`

### `Source/Programs/SwitchboardListener/SblCore/Internal/Linux/LinuxSwitchboardCredential.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L10 _function_ `inline ICredentialManager& ICredentialManager::GetPlatformCredentialManager()` (scope `UE::SwitchboardListener::ICredentialManager`)

### `Source/Programs/SwitchboardListener/SblCore/Internal/PosixOS/PosixOSSwitchboardCredential.h` (Internal)


#### class `UE::SwitchboardListener::Private::FPosixCredentialManager`  
`class FPosixCredentialManager : public ICredentialManager`  
_L10-15_
- inherits: `ICredentialManager`
- L13 _public prototype_ `virtual TSharedPtr<ICredential> LoadCredential(FStringView InCredentialName) override;`
- L14 _public prototype_ `virtual bool SaveCredential(FStringView InCredentialName, FStringView InUser, FStringView InBlob) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::SwitchboardListener`)

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardAuth.h` (Internal)


#### class `FSwitchboardAuthHelper`  
`class FSwitchboardAuthHelper`  
_L72-147_
- desc: - Uses either the specified key pair, or an automatically generated self-signed key pair. On systems where credentials can be stored encrypted at rest, the resulting private key is protected with a randomly generated password. - Can sign and verify JSON Web Tokens using the loaded key pair. - Can generate, persist, and constant-time compare password hashes using scrypt key derivation. - Has helper methods for MsQuic interop.
- L91 _public prototype_ `bool Initialize(const FSettings& InSettings = FSettings());`
- L92 _public prototype_ `void Shutdown();`
- L96 _public prototype_ `const FUtf8String& GetCertificateFilePath() const;` — May be empty if the certificate was not loaded from file.
- L99 _public prototype_ `const FUtf8String& GetPrivateKeyFilePath() const;` — May be empty if the private key was not loaded from file.
- L102 _public prototype_ `const UTF8CHAR* GetPrivateKeyPassword() const;` — May be null if the private key was not password-protected.
- L106 _public prototype_ `bool SetAuthPassword(FStringView InNewPassword, bool bExpireExistingTokens = true);` — Change the required password.
- L109 _public prototype_ `bool ValidatePassword(FStringView InAttempt);` — Validate whether the provided password attempt matches the expected password.
- L112 _public prototype_ `const UTF8CHAR* GetAuthPassword() const;` — Retrieves the plain text; only supported on platforms where the credential can be encrypted at rest.
- L115 _public prototype_ `bool IsAuthPasswordSet() const;` — True if a password hash is set, even if `GetAuthPassword` would return unset.
- L119 _public prototype_ `FString IssueJWT(const TMap<FStringView, FStringView>& InPayloadFields);` — Returns a JWT, signed with our private key, containing the provided payload.
- L122 _public prototype_ `TOptional<FJsonWebToken> GetValidatedJWT(FStringView InEncodedJwt) const;` — Returns the decoded and validated JWT; result is unset if validation fails.
- L125 _public prototype_ `bool IsValidJWT(FStringView InEncodedJwt) const;` — Returns just whether the JWT passes validation.
- L129 _private prototype_ `bool CheckOrCreateSelfSignedKeyPair(FSettings& InOutSettings);`
- L130 _private prototype_ `FUtf8String GenerateHashSalt();`
- L131 _private prototype_ `bool UpdateLastPasswordChangeTimeUtc(FDateTime InChangeTimeUtc = FDateTime::UtcNow());`
- L134 _private member_ `UE::SwitchboardListener::ICredentialManager* CredentialManager;`
- L135 _private member_ `bool bSecureHeapNeedsShutdown = false;`
- L137 _private member_ `FUtf8String CertificateFilePath;`
- L138 _private member_ `FUtf8String PrivateKeyFilePath;`
- L139 _private member_ `UTF8CHAR* PrivateKeyPassword = nullptr;`
- L140 _private member_ `EVP_PKEY* PrivateKey = nullptr;`
- L141 _private member_ `X509* Certificate = nullptr;`
- L143 _private member_ `UTF8CHAR* PlainAuthPassword = nullptr;`
- L144 _private member_ `FUtf8String HashSalt;`
- L145 _private member_ `TArray<uint8> HashedAuthPassword;`
- L146 _private member_ `int64 LastPasswordChangeTimeUtc = -1;`

#### struct `FSwitchboardAuthHelper::FSettings`  
`struct FSettings`  
_L75-89_
- L77 _public member_ `TOptional<TVariant<FString, X509*>> Certificate;`
- L78 _public member_ `TOptional<TVariant<FString, EVP_PKEY*>> PrivateKey;`
- L79 _public member_ `TOptional<FUtf8StringView> PrivateKeyPassword;`
- L81 _public member_ `UE::SwitchboardListener::ICredentialManager* CredentialManager = nullptr;`
- L83 _public function_ `FSettings()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UI UI_ST` — Workaround for "ossl_typ.h(144): error C2365: 'UI': redefinition; previous definition was 'namespace'" "ObjectMacros.h(872): note: see declaration of 'UI'"
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L38 _prototype_ `FString GetSwitchboardDataDirectory();` (scope `UE::SwitchboardListener`) — Get the default paths for self-signed key pairs, or (on some platforms) persisted credentials. - Windows: %LocalAppData%\SwitchboardListener - PosixOS family: ~/.switchboard/listener
- L47 _prototype_ `FString ReadPasswordFromStdin(bool bAllowEmpty = false);` (scope `UE::SwitchboardListener`) — Disable console echo and prompt the user to enter a password (twice). @param bAllowEmpty Whether to allow the user to leave the input empty. @return The password the user entered.
- L55 _prototype_ `void FillSecureRandom(TArrayView<uint8> InOutArray);` (scope `UE::SwitchboardListener`) — Completely overwrites the contents of the provided array with cryptographically secure pseudo-random bytes. @param InOutArray Set to the desired length before calling.
- L150 _namespace_ `namespace UE`
- L150 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L150 _namespace_ `namespace Private` (scope `UE::SwitchboardListener`)
- L153 _variable_ `static constexpr mode_t CredentialFilePermissionFlags = S_IRUSR | S_IWUSR;` (scope `UE::SwitchboardListener::Private`)
- L154 _variable_ `static constexpr mode_t CredentialDirPermissionFlags = S_IRUSR | S_IWUSR | S_IXUSR;` (scope `UE::SwitchboardListener::Private`)
- L155 _variable_ `static constexpr mode_t CredentialPermissionMask = S_IRWXU | S_IRWXG | S_IRWXO;` (scope `UE::SwitchboardListener::Private`)
- L158 _prototype_ `bool CheckCredentialPermissions(FStringView InFilePath);` (scope `UE::SwitchboardListener::Private`)
- L159 _prototype_ `TPair<EVP_PKEY*, X509*> CreateSelfSignedPair();` (scope `UE::SwitchboardListener::Private`)

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardCredential.h` (Internal)
_(no declarations extracted)_

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardCredentialInterface.h` (Internal)


#### class `UE::SwitchboardListener::ICredential`  
`class ICredential : public TSharedFromThis<ICredential>`  
_L12-22_
- inherits: `TSharedFromThis<ICredential>`
- L15 _public prototype_ `virtual ~ICredential() = default;`
- L18 _public prototype_ `virtual FStringView GetUser() = 0;` — Returns the user field value for this credential.
- L21 _public prototype_ `virtual FStringView GetBlob() = 0;` — Returns the blob field value (password, token, etc) for this credential.

#### class `UE::SwitchboardListener::ICredentialManager`  
`class ICredentialManager : public TSharedFromThis<ICredentialManager>`  
_L24-41_
- inherits: `TSharedFromThis<ICredentialManager>`
- L28 _public prototype_ `static ICredentialManager& GetPlatformCredentialManager();` — Returns the default credential manager for this platform.
- L31 _public prototype_ `virtual ~ICredentialManager() = default;`
- L34 _public function_ `virtual bool IsEncryptedAtRest() const` — Returns whether credentials are encrypted at rest on the current platform.
- L37 _public prototype_ `virtual TSharedPtr<ICredential> LoadCredential(FStringView InCredentialName) = 0;` — Returns the stored credential if it exists.
- L40 _public prototype_ `virtual bool SaveCredential(FStringView InCredentialName, FStringView InUser, FStringView InBlob) = 0;` — Stores the provided credential.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SwitchboardListener` (scope `UE`)

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardListener.h` (Internal)


#### struct `FSwitchboardCommandLineOptions`  
`struct FSwitchboardCommandLineOptions`  
_L48-60_
- L50 _public member_ `bool OutputVersion = false;`
- L51 _public member_ `bool MinimizeOnLaunch = true;`
- L53 _public member_ `TOptional<FIPv4Address> Address;`
- L54 _public member_ `TOptional<uint16> Port;`
- L56 _public member_ `TOptional<uint32> RedeployFromPid;`
- L58 _public prototype_ `static FSwitchboardCommandLineOptions FromString(const TCHAR* CommandLine);`
- L59 _public prototype_ `FString ToString(bool bIncludeRedeploy = false) const;`

#### struct `FRedeployStatus`  
`struct FRedeployStatus`  
_L63-109_
- L90 _public function_ `bool InProgress() const`
- L95 _public member_ `EState State = EState::None;`
- L98 _public member_ `FIPv4Endpoint RequestingClient;` — Valid when State >= RequestReceived
- L101 _public member_ `FString OriginalThisExePath;` — Valid when State >= NewListenerWrittenTemp
- L102 _public member_ `FString TempNewListenerPath;`
- L105 _public member_ `FProcHandle ListenerProc;` — Valid when State >= NewListenerStarted
- L108 _public member_ `FString TempThisListenerPath;` — Valid when State >= ThisListenerRenamed

#### enum `FRedeployStatus::EState`  
`enum class EState : uint8`  
_L65-88_
- L68 _public enumerator_ `None` — No redeploy initiated.
- L71 _public enumerator_ `RequestReceived` — Redeploy initiated by client, decline subsequent redeploy requests.
- L75 _public enumerator_ `NewListenerWrittenTemp` — New listener executable hash verified and written to randomly-named temporary file. This also means we've stopped listening for new connections in this (old) listener.
- L78 _public enumerator_ `NewListenerStarted` — New listener successfully launched and running.
- L81 _public enumerator_ `ThisListenerRenamed` — Current process executable moved to randomly-named temporary file.
- L84 _public enumerator_ `NewListenerRenamed` — New listener executable moved to original location of this executable.
- L87 _public enumerator_ `Complete` — Child process has signaled via IPC that it's initialized; shutting down.

#### class `FSwitchboardListener`  
`class FSwitchboardListener`  
_L112-342_
- L115 _private typedef_ `using FConnectionRef = TSharedRef<FConnection>;`
- L116 _private typedef_ `using FByteArrayRef = TSharedRef<TArray<uint8>>;`
- L118 _private member_ `static const FIPv4Endpoint InvalidEndpoint;`
- L121 _public prototype_ `explicit FSwitchboardListener(const FSwitchboardCommandLineOptions& InOptions);`
- L122 _public prototype_ `~FSwitchboardListener();`
- L124 _public prototype_ `bool Init();`
- L125 _public prototype_ `void Shutdown();`
- L127 _public prototype_ `void Tick();`
- L129 _public prototype_ `bool StartListening();`
- L130 _public prototype_ `bool StopListening();`
- L131 _public function_ `bool IsListening() const`
- L134 _public prototype_ `const UTF8CHAR* GetAuthPassword() const;` — May be null if the plain text password cannot be stored encrypted at rest on this platform.
- L135 _public prototype_ `bool IsAuthPasswordSet() const;`
- L136 _public prototype_ `bool SetAuthPassword(const FString& NewPassword);`
- L138 _public prototype_ `TSet<FIPv4Endpoint> GetConnectedClientEndpoints() const;`
- L139 _public prototype_ `TSet<FIPv4Address> GetConnectedClientAddresses() const;`
- L142 _public prototype_ `static FString GetIpcSemaphoreName(uint32 ParentPid);` — Used for redeploy synchronization.
- L144 _public function_ `FSimpleMulticastDelegate& OnInit()`
- L145 _public function_ `FSimpleMulticastDelegate& OnShutdown()`
- L146 _public function_ `FSimpleMulticastDelegate& OnTick()`
- L149 _private prototype_ `bool ParseIncomingMessage(const FString& InMessage, const FIPv4Endpoint& InEndpoint, const FConnectionRef& Connection);`
- L151 _private prototype_ `bool RunScheduledTask(const FSwitchboardTask& InTask);`
- L152 _private prototype_ `bool Task_Authenticate(const FSwitchboardAuthenticateTask& InAuthTask);`
- L153 _private prototype_ `bool Task_StartProcess(const FSwitchboardStartTask& InRunTask);`
- L154 _private prototype_ `bool Task_KillProcess(const FSwitchboardKillTask& KillTask);`
- L155 _private prototype_ `bool Task_ReceiveFileFromClient(const FSwitchboardReceiveFileFromClientTask& InReceiveFileFromClientTask);`
- L156 _private prototype_ `bool Task_RedeployListener(const FSwitchboardRedeployListenerTask& InRedeployListenerTask);`
- L157 _private prototype_ `bool Task_SendFileToClient(const FSwitchboardSendFileToClientTask& InSendFileToClientTask);`
- L158 _private prototype_ `bool Task_GetSyncStatus(const FSwitchboardGetSyncStatusTask& InGetSyncStatusTask);`
- L159 _private prototype_ `bool Task_RefreshMosaics(const FSwitchboardRefreshMosaicsTask& InRefreshMosaicsTask);`
- L160 _private prototype_ `bool Task_FixExeFlags(const FSwitchboardFixExeFlagsTask& InFixExeFlagsTask);`
- L161 _private prototype_ `bool Task_MinimizeWindows(const FSwitchboardMinimizeWindowsTask& InRefreshMosaicsTask);`
- L162 _private prototype_ `bool Task_SetInactiveTimeout(const FSwitchboardSetInactiveTimeoutTask& InTimeoutTask);`
- L163 _private prototype_ `bool Task_FreeListenerBinary(const FSwitchboardFreeListenerBinaryTask& InRenameProcessTask);`
- L166 _private prototype_ `bool Task_StartLiveLogStream(const FSwitchboardStartLiveLogStreamTask& InStartLiveLogStreamTask);` — Starts streaming a log file to Switchboard
- L169 _private prototype_ `bool Task_StopLiveLogStream(const FSwitchboardStopLiveLogStreamTask& InStopLiveLogStreamTask);` — Stops streaming a log file to Switchboard
- L171 _private prototype_ `bool KillProcessNow(FRunningProcess* InProcess, float SoftKillTimeout = 0.0f);`
- L174 _private typedef_ `using FFlipModeMonitorSessionId = uint8;`
- L175 _private member_ `static constexpr FFlipModeMonitorSessionId InvalidFlipModeSessionId = FFlipModeMonitorSessionId(-1);`
- L176 _private member_ `static constexpr FFlipModeMonitorSessionId MaxFlipModeMonitorSessions = 16;`
- L177 _private prototype_ `void HarvestExistingFlipModeSessions();`
- L178 _private prototype_ `bool EnsureFlipModeSessionAvailable(FFlipModeMonitorSessionId SessionId, bool* bOutStoppedSession = nullptr);`
- L179 _private prototype_ `FFlipModeMonitorSessionId AllocFlipModeMonitorSessionId();`
- L180 _private prototype_ `void FreeFlipModeMonitorSessionId(FFlipModeMonitorSessionId SessionId);`
- L181 _private prototype_ `FString MakeFlipModeMonitorSessionName(FFlipModeMonitorSessionId SessionId);`
- L182 _private prototype_ `FRunningProcess* FindOrStartFlipModeMonitorForUUID(const FGuid& UUID);`
- L185 _private prototype_ `void CleanUpDisconnectedSockets();`
- L186 _private prototype_ `void HandleStdout(const TSharedPtr<FRunningProcess>& Process);`
- L187 _private prototype_ `void HandleRunningProcesses(TArray<TSharedPtr<FRunningProcess>>& Processes, bool bNotifyThatProgramEnded);`
- L190 _private prototype_ `void HandleLiveLogStreams();` — Processes all active live log streams, reading new content and sending to Switchboard clients
- L192 _private prototype_ `bool SendMessage(const FString& InMessage, const FIPv4Endpoint& InEndpoint);`
- L193 _private prototype_ `void SendMessageFutures();`
- L195 _private prototype_ `bool EquivalentTaskFutureExists(uint32 TaskEquivalenceHash) const;`
- L197 _private prototype_ `void RollbackRedeploy();`
- L199 _private prototype_ `void FillStatePacket(struct FSwitchboardStatePacket& OutStatePacket);`
- L201 _private prototype_ `_Function_class_(QUIC_LISTENER_CALLBACK) static QUIC_STATUS QuicListenerThunk(HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event);`
- L203 _private prototype_ `static QUIC_STATUS QuicConnectionThunk(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);`
- L204 _private prototype_ `static QUIC_STATUS QuicStreamThunk(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);`
- L205 _private prototype_ `QUIC_STATUS QuicListenerCallback(HQUIC Listener, QUIC_LISTENER_EVENT* Event);`
- L206 _private prototype_ `QUIC_STATUS QuicConnectionCallback(HQUIC Connection, QUIC_CONNECTION_EVENT* Event);`
- L207 _private prototype_ `QUIC_STATUS QuicStreamCallback(HQUIC Stream, QUIC_STREAM_EVENT* Event);`
- L258 _private member_ `FSwitchboardCommandLineOptions Options;`
- L259 _private member_ `TUniquePtr<FIPv4Endpoint> ListenerEndpoint;`
- L261 _private member_ `FSwitchboardAuthHelper AuthHelper;`
- L264 _private member_ `const QUIC_API_TABLE* QuicApi = nullptr;` — MsQuic top level function table for all other API calls.
- L267 _private member_ `HQUIC QuicRegistration = nullptr;` — MsQuic registration manages the execution context for all child objects.
- L270 _private member_ `HQUIC QuicConfiguration = nullptr;` — MsQuic configuration manages security-related and other common QUIC settings.
- L273 _private member_ `HQUIC QuicListener = nullptr;` — MsQuic incoming connection handler.
- L275 _private member_ `UE::FRecursiveMutex ConnectionsLock;`
- L276 _private member_ `TMap<FIPv4Endpoint, FConnectionRef> ConnectionsByEndpoint;`
- L277 _private member_ `TMap<HQUIC, FConnectionRef> ConnectionsByQuicConn;`
- L278 _private member_ `TMap<HQUIC, FConnectionRef> ConnectionsByQuicStream;`
- L280 _private member_ `static constexpr int8 MaxAuthFailures = 5;`
- L281 _private member_ `TMap<FIPv4Address, int8> AuthFailuresByAddress;`
- L283 _private member_ `TQueue<TUniquePtr<FSwitchboardTask>, EQueueMode::Spsc> ScheduledTasks;`
- L284 _private member_ `TQueue<TUniquePtr<FSwitchboardTask>, EQueueMode::Spsc> DisconnectTasks;`
- L285 _private member_ `TArray<TSharedPtr<FRunningProcess>> RunningProcesses;`
- L286 _private member_ `TArray<TSharedPtr<FRunningProcess>> FlipModeMonitors;`
- L289 _private member_ `TBitArray<> RunningFlipModeSessions;`
- L292 _private member_ `TArray<FSwitchboardMessageFuture> MessagesFutures;`
- L293 _private member_ `TSharedPtr<FCpuUtilizationMonitor> CpuMonitor;`
- L296 _private member_ `TSharedPtr<FGpuClockerManager> GpuClockerManager;` — Gpu clock manager. Used to lock/unlock gpu clocks.
- L298 _private member_ `bool bProcessorSMT;`
- L300 _private member_ `TSharedPtr<FRWLock> CachedMosaicToposLock;`
- L301 _private member_ `TSharedPtr<TArray<struct FMosaicTopo>> CachedMosaicTopos;`
- L303 _private member_ `FRedeployStatus RedeployStatus;`
- L305 _private member_ `FSimpleMulticastDelegate OnInitDelegate;`
- L306 _private member_ `FSimpleMulticastDelegate OnShutdownDelegate;`
- L307 _private member_ `FSimpleMulticastDelegate OnTickDelegate;`
- L340 _private member_ `TArray<FLiveLogStream> ActiveLogStreams;`
- L341 _private member_ `UE::FMutex LiveLogStreamsMutex;`

#### struct `FSwitchboardListener::FQuicBuffer`  
`struct FQuicBuffer`  
_L211-230_
- desc: Combines a QUIC_BUFFER span (ptr + len) and its backing array.
- L213 _public member_ `QUIC_BUFFER QuicBuffer;`
- L214 _public member_ `FByteArrayRef Storage;`
- L216 _public function_ `FQuicBuffer() : QuicBuffer`
- L222 _public function_ `explicit FQuicBuffer(FByteArrayRef&& InStorage) : Storage(MoveTemp(InStorage))`

#### struct `FSwitchboardListener::FConnection`  
`struct FConnection`  
_L233-255_
- desc: Tracks all the state for an established connection.
- L235 _public member_ `FIPv4Endpoint Endpoint;`
- L236 _public member_ `HQUIC QuicConn = nullptr;`
- L238 _public member_ `HQUIC QuicStream = nullptr;` — We currently assume a single bidirectional stream initiated by the peer.
- L240 _public member_ `UE::FMutex SendLock;`
- L241 _public member_ `TQueue<TSharedPtr<FQuicBuffer>> SendBuffers;`
- L243 _public member_ `UE::FMutex ReceiveLock;`
- L244 _public member_ `bool bMessageComplete = false;`
- L245 _public member_ `FByteArrayRef ReceiveBuffer = MakeShared<TArray<uint8>>();`
- L247 _public member_ `bool bAuthenticated = false;`
- L253 _public member_ `float InactiveTimeout;` — TODO?: MsQuic handles idle timeout, but configuration is app-wide. If we want to support the existing per-client override, need to figure out how best to pass one override when calling QuicApi->ConnectionSetConfiguration() (clone config obj N times?).
- L254 _public member_ `double LastActivityTime;`

#### struct `FSwitchboardListener::FLiveLogStream`  
`struct FLiveLogStream`  
_L310-338_
- desc: Live log streaming state
- L313 _public member_ `FString LogFilePath;` — Local path to the log file being streamed
- L316 _public member_ `FIPv4Endpoint ClientEndpoint;` — Network endpoint of the client receiving the stream
- L319 _public member_ `int64 LastFilePosition;` — Current read position in the log file
- L322 _public member_ `bool bTailOnly;` — If true, only stream new content added after the stream is started
- L325 _public member_ `double LastUpdateTime;` — Timestamp of the last stream update check
- L328 _public member_ `FGuid AssociatedProcessUUID;` — UUID of the process whose log is being streamed
- L330 _public function_ `FLiveLogStream(const FString& InLogFilePath, const FIPv4Endpoint& InClientEndpoint, bool bInTailOnly, const FGuid& InProcessUUID = FGuid(), int64 InStartOffset = -1) : LogFilePath(InLogFilePath) , ClientEndpoint(InClientEndpoint) , LastFilePosition(InStartOffset >= 0 ? InStartOffset : 0) , bTailOnly(bInTailOnly) , LastUpdateTime(0.0) , AssociatedProcessUUID(InProcessUUID)`

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardListenerApp.h` (Internal)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboard, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboard, Verbose, All);`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardProtocol, Verbose, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardProtocol, Verbose, All);`
- L13 _macro_ `# define SBL_SLATE 0`
- L19 _macro_ `# define SWITCHBOARD_CPUPROFILERTRACE_ENABLED 1`
- L21 _macro_ `# define SWITCHBOARD_CPUPROFILERTRACE_ENABLED 0`
- L29 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE(Name) \`
- L32 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE_STR(Name) \`
- L35 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name) \`
- L40 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE(Name)`
- L41 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE_STR(Name)`
- L42 _macro_ `# define SWITCHBOARD_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name)`

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardListenerMainCommon.h` (Internal)


#### Free symbols / members of external scopes

- L10 _prototype_ `bool SwitchboardListenerMainInit(const FSwitchboardCommandLineOptions& InOptions);`
- L11 _prototype_ `bool SwitchboardListenerMainShutdown();`
- L13 _prototype_ `int32 SwitchboardListenerMainWrapper();`

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardListenerVersion.h` (Internal)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SBLISTENER_VERSION_MAJOR 3`
- L6 _macro_ `#define SBLISTENER_VERSION_MINOR 5`
- L7 _macro_ `#define SBLISTENER_VERSION_PATCH 0`

### `Source/Programs/SwitchboardListener/SblCore/Internal/SwitchboardProcess.h` (Internal)


#### struct `FGenericSwitchboardProcess`  
`struct FGenericSwitchboardProcess`  
_L15-102_
- desc: Alternative implementation of FPlatformProcess::CreateProc with some additional features. Currently, the primary difference is that handles must be explicitly marked for inheritance.
- L72 _public prototype_ `static FCreateProcResult CreateProc(const FCreateProcParams& InParams);`
- L75 _public prototype_ `static FProcHandle CreateProc( const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void* PipeReadChild = nullptr );` — FPlatformProcess-compatible signature that calls into our implementation with more restrictive handle inheritance.

#### struct `FGenericSwitchboardProcess::FCreateProcParams`  
`struct FCreateProcParams`  
_L18-63_
- L21 _public member_ `FStringView Executable;` — Path to the executable to launch.
- L24 _public member_ `TArrayView<const FStringView> Args;` — Command line arguments.
- L27 _public member_ `bool bLaunchDetached = false;` — If true, the new process will have its own window.
- L30 _public member_ `bool bLaunchMinimized = false;` — If true, the new process will be minimized in the task bar.
- L33 _public member_ `bool bLaunchReallyHidden = false;` — If true, the new process will not have a window or be in the task bar.
- L36 _public member_ `int32 PriorityModifier = 0;` — -2 idle, -1 low, 0 normal, 1 high, 2 higher
- L39 _public member_ `TOptional<FStringView> WorkingDirectory;` — Working directory in which to start the program. If unset, uses the current working directory.
- L42 _public member_ `void* StdinPipe = nullptr;` — The read end of a pipe which will serve as stdin for the child process.
- L45 _public member_ `void* StdoutPipe = nullptr;` — The write end of a pipe which will serve as stdout for the child process.
- L48 _public member_ `void* StderrPipe = nullptr;` — The write end of a pipe which will serve as stderr for the child process.
- L55 _public member_ `TArrayView<void*> AdditionalInheritedHandles;` — Additional handles which the descendant process is permitted to inherit. StdinPipe, StdoutPipe, and StderrPipe are always inheritable, and should not be added to this list. Ignored if `bInheritAllHandles == true` (legacy behavior; not recommended).
- L62 _public member_ `bool bInheritAllHandles = false;` — Permit child process to inherit any handles from the parent process not explicitly excluded otherwise. This was the legacy behavior if any standard I/O redirection pipes were specified. This can lead to arcane resource leaks, and is not recommended.

#### struct `FGenericSwitchboardProcess::FCreateProcResult`  
`struct FCreateProcResult`  
_L65-69_
- L67 _public member_ `FProcHandle Handle;`
- L68 _public member_ `uint32 ProcessId = 0;`

#### Free symbols / members of external scopes

- L110 _typedef_ `using FSwitchboardProcess = FGenericSwitchboardProcess;`

### `Source/Programs/SwitchboardListener/SblCore/Internal/Windows/WindowsCpuUtilizationMonitor.h` (Internal)


#### class `FWindowsCpuUtilizationMonitor`  
`class FWindowsCpuUtilizationMonitor : public FGenericCpuUtilizationMonitor`  
_L18-40_
- inherits: `FGenericCpuUtilizationMonitor`
- L21 _public prototype_ `FWindowsCpuUtilizationMonitor();`
- L22 _public prototype_ `~FWindowsCpuUtilizationMonitor();`
- L24 _public function_ `bool IsInitialized() const override`
- L29 _public prototype_ `bool GetPerCoreUtilization(TArray<int8>& OutCoreUtilization) override;`
- L32 _private prototype_ `bool QueryUpdatedUtilization();`
- L34 _private member_ `bool bIsInitialized = false;`
- L36 _private member_ `HQUERY QueryHandle = INVALID_HANDLE_VALUE;`
- L37 _private member_ `TArray<PDH_HCOUNTER> CounterHandles;`
- L38 _private member_ `double LastQueryTime = DBL_MIN;`
- L39 _private member_ `TArray<int8> CachedCoreUtilization;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define _WIN32_WINDOWS 0x0410`
- L42 _typedef_ `typedef FWindowsCpuUtilizationMonitor FCpuUtilizationMonitor;`

### `Source/Programs/SwitchboardListener/SblCore/Internal/Windows/WindowsSwitchboardCredential.h` (Internal)


#### class `UE::SwitchboardListener::Private::FWindowsCredentialManager`  
`class FWindowsCredentialManager : public ICredentialManager`  
_L10-16_
- inherits: `ICredentialManager`
- L13 _public function_ `virtual bool IsEncryptedAtRest() const override`
- L14 _public prototype_ `virtual TSharedPtr<ICredential> LoadCredential(FStringView InCredentialName) override;`
- L15 _public prototype_ `virtual bool SaveCredential(FStringView InCredentialName, FStringView InUser, FStringView InBlob) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::SwitchboardListener`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L22 _function_ `inline ICredentialManager& ICredentialManager::GetPlatformCredentialManager()` (scope `UE::SwitchboardListener::ICredentialManager`)

### `Source/Programs/SwitchboardListener/SblCore/Internal/Windows/WindowsSwitchboardProcess.h` (Internal)


#### struct `FWindowsSwitchboardProcess`  
`struct FWindowsSwitchboardProcess : public FGenericSwitchboardProcess`  
_L9-15_
- inherits: `FGenericSwitchboardProcess`
- desc: Windows implementation of FSwitchboardProcess. See FGenericSwitchboardProcess for details.
- L14 _public prototype_ `static FCreateProcResult CreateProc(const FCreateProcParams& InParams);`

#### Free symbols / members of external scopes

- L18 _typedef_ `using FSwitchboardProcess = FWindowsSwitchboardProcess;`

### `Source/Programs/SwitchboardListener/SblCore/NvmlWrapper/Public/GpuClocker.h` (Public)


#### class `FGpuClocker`  
`class EXPORTLIB FGpuClocker`  
_L10-37_
- desc: Encapsulates the logic to lock/unlock gpu clocks
- L15 _public prototype_ `bool LockGpuClocks() const;` — Locks the gpu clocks to the maximum allowed
- L18 _public prototype_ `bool UnlockGpuClocks() const;` — Unlocks the gpu and memory clocks
- L21 _public prototype_ `bool GpuUnlockDevice(const uint32_t GpuIdx) const;` — Locks the given gpu and memory clocks to the maximum allowed
- L24 _public prototype_ `bool GpuLockDevice(const uint32_t GpuIdx) const;` — Unlocks the given gpu and memory clocks
- L27 _public prototype_ `bool GetGpuCount(uint32_t& OutNumGpus) const;` — Returns number of GPUs
- L30 _public prototype_ `bool GetGpuCelsius(const uint32_t GpuIdx, uint32_t& OutCelsius) const;` — Returns the temperature in Celsius of the indexed GPU
- L33 _public prototype_ `bool GetGpuUsage(const uint32_t GpuIdx, uint32_t& OutUsageKernel, uint32_t& OutUsageMemory) const;` — Returns the GPU usage in percentage of running kernels and memory operations
- L36 _public prototype_ `bool GetGpuMHz(const uint32_t GpuIdx, uint32_t& GraphicsMHz, uint32_t& MemoryMHz) const;` — Return GPU clock frequency in MHz

### `Source/Programs/SwitchboardListener/SblCore/NvmlWrapper/Public/NvmlWrapperPublic.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define EXPORTLIB __declspec(dllexport)`
- L7 _macro_ `#define IMPORTLIB __declspec(dllimport)`
- L9 _macro_ `#define EXPORTLIB __attribute__((visibility("default")))`
- L10 _macro_ `#define IMPORTLIB`
- L12 _macro_ `#define EXPORTLIB`

### `Source/Programs/SwitchboardListener/SblCore/Private/GpuClockerManager.h` (Private)


#### class `FGpuClockerManager`  
`class FGpuClockerManager`  
_L15-55_
- desc: Manages the GpuClocker, whether using local functionality when SBL is launched with elevanted privileges (which is an NVML requirement to lock Gpu clocks), or the SwitchboardListenerHelper process
- L19 _public prototype_ `FGpuClockerManager();`
- L20 _public prototype_ `~FGpuClockerManager();`
- L23 _public prototype_ `void Tick();` — Call periodically to perform service maintenance tasks.
- L26 _public prototype_ `bool LockGpuClocksForPid(uint32 Pid);` — Locks the Gpu clocks for at least the lifetime of the given process id.
- L32 _public prototype_ `void PidEnded(uint32 Pid);` — Must be called when a Pid that this gpu clock manager may have in its internal list has ended. When all pids that conditio the gpu clocks end, then the clocks are put back to their normal state.
- L37 _private prototype_ `bool LockGpuClocksUsingSBLHelper(uint32 Pid);` — Requests the SBL Helper executable to lock the Gpu clocks during the lifetime of at least the given process id.
- L42 _private member_ `TSharedPtr<FSBLHelperClient> SBLHelper;` — Client interface to the Switchboard Listener Helper external process
- L48 _private member_ `TSet<uint32> LockingPids;` — Set of Pids that are keeping the gpus clocks locked. Only applicable when locally managed and not when using the external SBLHelper.
- L54 _private member_ `bool bLockManagedLocally = false;` — True when we are locally managing the locking of the Gpu clocks. It doesn't imply that the local locking succeeded, only that we are not using SBL Helper to do it for the current pids in the set.

### `Source/Programs/SwitchboardListener/SblCore/Private/SBLHelperClient.h` (Private)


#### class `FSBLHelperClient`  
`class FSBLHelperClient`  
_L17-123_
- desc: Class in charge of communicating with the SwitchboardListenerHelper server
- L29 _public prototype_ `~FSBLHelperClient();` — Destructor
- L32 _public prototype_ `bool IsConnected();` — Returns true if currently connected to the SBLHelper server
- L40 _public prototype_ `bool Connect(const FConnectionParams& InConnectionParams);` — Connects to the SBLHelper server specified in the given connection parameters. If already connected, it will disconnect before attempting the new connection. @return True if it was able to establish the connection to a valid server.
- L43 _public prototype_ `void Disconnect();` — Disconnects from the SBLHelper server. Can be called even if already disconnected.
- L52 _public prototype_ `bool LockGpuClock(const uint32 Pid);` — Requests the server to lock the gpu and memory clocks to the maximum allowed. @param Pid Proces ID to which the lock gpu clock request is tied to. @return True if the message was sent over the socket.
- L55 _public prototype_ `FString GetStatus();` — Returns a string describing the status of the server
- L58 _public prototype_ `void Tick();` — Call this periodically for tasks such as parsing the incoming messages from the server
- L69 _private prototype_ `TArray<FString> ReceiveMessages(const float TimeoutSeconds = 0);` — Receives messages from the socket into an array. @param TimeoutSeconds Maximum time to wait for at least one message to be completely received. @return Array of received messages.
- L76 _private prototype_ `void ParseMessage(const FString& InMessage);` — Parses the given message and calls the respective handlers @param InMessage The message to parse.
- L83 _private prototype_ `void ParseIncomingMessages(const float TimeoutSeconds = 0);` — Checks the socket for new messages and calls ParseMessage on each. @param TimeoutSeconds The maximum time to wait for at least one message to be completely received.
- L86 _private prototype_ `void HandleCmdHello(TSharedPtr<FJsonObject>& Json);` — Handles the 'Hello' command from the server
- L96 _private prototype_ `FString CreateMessage(const FString& Cmd, const TMap<FString, FString>& AdditionalFields);` — Creates a new message for the given command and additional fields @param Cmd The command to create this message for. @param AdditionalFields Any additional fields or parameters to include in the message. @return The created message, ready to be sent over the socket.
- L99 _private prototype_ `bool SendMessage(const FString& Message);` — Sends the given message over the socket, if connected.
- L102 _private prototype_ `uint32 GetNextPacketId();` — Gets the next packet id to use when creating a new message. Monotonically increments. Skips zero.
- L107 _private member_ `static const int32 CompatibleVersion[3];` — The minimum compatible SBLHelper server version.
- L110 _private member_ `FSocket* Socket = nullptr;` — Socket for this client to communicate with the server
- L113 _private member_ `uint32 NextPacketId = 1;` — Next packet id when creating a new message to be sent
- L116 _private member_ `TArray<uint8> ReceiveBuffer;` — Buffer to hold partial messages received over the socket from the server
- L119 _private member_ `FConnectionParams ConnectionParams;` — Cached connection parameters. Mostly used for logging purposes.
- L122 _private member_ `FString ServerVersion;` — The current server version that this client is connected to.

#### struct `FSBLHelperClient::FConnectionParams`  
`struct FConnectionParams`  
_L22-26_
- desc: Structure holding the desired connection parameters, such as IP and Port
- L25 _public member_ `FIPv4Endpoint Endpoint;` — Server end point to connect to

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSBLHelperClient, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSBLHelperClient, Log, All);`

### `Source/Programs/SwitchboardListener/SblCore/Private/ScopedNvApi.h` (Private)


#### class `FScopedNvApi`  
`class FScopedNvApi`  
_L12-59_
- desc: Used to allow multi-threaded usage of NvApi and to control when it gets loaded or unloaded
- L16 _public prototype_ `FScopedNvApi();`
- L17 _public prototype_ `~FScopedNvApi();`
- L20 _public prototype_ `bool IsNvApiInitialized() const;` — Returns true if the NvAPI was initialized successfully
- L23 _public prototype_ `void FillOutSyncTopologies(TArray<FSyncTopo>& SyncTopos) const;` — Fills out the Sync topologies
- L26 _public prototype_ `void FillOutDriverVersion(FSyncStatus& SyncStatus) const;` — Fills out the sync status
- L29 _public prototype_ `void FillOutPhysicalGpuStats(FSyncStatus& SyncStatus, bool bGetUtilizations, bool bGetClocks, bool bGetTemperatures);` — Fills out physical the requested gpu stats
- L32 _public prototype_ `uint32 GetGpuCount();` — Returns the gpu count
- L35 _public prototype_ `void FillOutMosaicTopologies(TArray<FMosaicTopo>& MosaicTopos);` — Fill out the mosaic topologies
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNvApiInstantiated);` — Multicast delegate that gets called when a new instance of FScopedNvApi is instantiated
- L41 _public prototype_ `static FOnNvApiInstantiated& GetOnNvApiInstantiated();` — Delegate for when the index of the single tile being edited changes
- L46 _private prototype_ `bool CacheGpuHandles();` — Caches the gpu handles to avoid re-querying them every time gpu stats are requested
- L58 _private member_ `bool bIsNvApiInitialized = false;` — True if the NvAPI was initialized for use by the current FScopedNvApi instance

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNvApiInstantiated);` — Multicast delegate that gets called when a new instance of FScopedNvApi is instantiated

### `Source/Programs/SwitchboardListener/SblCore/Private/SwitchboardMessageFuture.h` (Private)


#### struct `FSwitchboardMessageFuture`  
`struct FSwitchboardMessageFuture`  
_L10-20_
- L13 _public member_ `FIPv4Endpoint InEndpoint;` — Endpoint where this message should be sent to
- L16 _public member_ `uint32 EquivalenceHash;` — Equivalence hash of the original task
- L19 _public member_ `TFuture<FString> Future;` — Future containing message contents

### `Source/Programs/SwitchboardListener/SblCore/Private/SwitchboardPacket.h` (Private)


#### struct `FSwitchboardPacket`  
`struct FSwitchboardPacket`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Command;` — `UPROPERTY()`
- L21 _public member_ `bool bAck;` — `UPROPERTY()`
- L24 _public member_ `FString Error;` — `UPROPERTY()`

#### struct `FSwitchboardStateRunningProcess`  
`struct FSwitchboardStateRunningProcess`  
_L29-47_
- reflection: `USTRUCT()`
- L34 _public member_ `FString Uuid;` — `UPROPERTY()`
- L37 _public member_ `FString Path;` — `UPROPERTY()`
- L40 _public member_ `FString Name;` — `UPROPERTY()`
- L43 _public member_ `FString Caller;` — `UPROPERTY()`
- L46 _public member_ `uint32 Pid;` — `UPROPERTY()`

#### struct `FSwitchboardStatePacket`  
`struct FSwitchboardStatePacket : public FSwitchboardPacket`  
_L51-98_
- reflection: `USTRUCT()`
- inherits: `FSwitchboardPacket`
- desc: This is an initial snapshot, sent upon connecting.
- L55 _public function_ `FSwitchboardStatePacket() : FSwitchboardPacket()`
- L69 _public member_ `TArray<FSwitchboardStateRunningProcess> RunningProcesses;` — `UPROPERTY()` — All active child processes launched via this Listener.
- L73 _public member_ `uint32 Version;` — `UPROPERTY()` — Reports the SwitchboardListener version back to the client.
- L77 _public member_ `bool bProcessorSMT;` — `UPROPERTY()` — Whether simultaneous multi-threading (aka Hyper-Threading) is enabled.
- L81 _public member_ `FString OsVersionLabel;` — `UPROPERTY()` — Operating system version "label". See FPlatformMisc::GetOSVersions.
- L85 _public member_ `FString OsVersionLabelSub;` — `UPROPERTY()` — Operating system version "sub-label". See FPlatformMisc::GetOSVersions.
- L89 _public member_ `FString OsVersionNumber;` — `UPROPERTY()` — Operating system version, returned by FPlatformMisc::GetOSVersion.
- L93 _public member_ `uint64 TotalPhysicalMemory;` — `UPROPERTY()` — Total physical memory (used + available) in bytes.
- L97 _public member_ `FString PlatformBinaryDirectory;` — `UPROPERTY()` — The name of the platform as it appears in Engine/Binaries

#### struct `FSwitchboardProgramStdout`  
`struct FSwitchboardProgramStdout : public FSwitchboardPacket`  
_L101-119_
- reflection: `USTRUCT()`
- inherits: `FSwitchboardPacket`
- L105 _public function_ `FSwitchboardProgramStdout() : FSwitchboardPacket()`
- L112 _public member_ `FSwitchboardStateRunningProcess Process;` — `UPROPERTY()`
- L115 _public member_ `FString PartialStdoutB64;` — `UPROPERTY()`
- L118 _public member_ `FString PartialStderrB64;` — `UPROPERTY()`

#### struct `FSwitchboardProgramEnded`  
`struct FSwitchboardProgramEnded : public FSwitchboardPacket`  
_L122-143_
- reflection: `USTRUCT()`
- inherits: `FSwitchboardPacket`
- L126 _public function_ `FSwitchboardProgramEnded() : FSwitchboardPacket()`
- L133 _public member_ `FSwitchboardStateRunningProcess Process;` — `UPROPERTY()`
- L136 _public member_ `int32 Returncode;` — `UPROPERTY()`
- L139 _public member_ `FString StdoutB64;` — `UPROPERTY()`
- L142 _public member_ `FString StderrB64;` — `UPROPERTY()`

#### struct `FSwitchboardProgramStarted`  
`struct FSwitchboardProgramStarted : public FSwitchboardPacket`  
_L146-158_
- reflection: `USTRUCT()`
- inherits: `FSwitchboardPacket`
- L150 _public function_ `FSwitchboardProgramStarted() : FSwitchboardPacket()`
- L157 _public member_ `FSwitchboardStateRunningProcess Process;` — `UPROPERTY()`

#### struct `FSwitchboardProgramKilled`  
`struct FSwitchboardProgramKilled : public FSwitchboardPacket`  
_L161-173_
- reflection: `USTRUCT()`
- inherits: `FSwitchboardPacket`
- L165 _public function_ `FSwitchboardProgramKilled() : FSwitchboardPacket()`
- L172 _public member_ `FSwitchboardStateRunningProcess Process;` — `UPROPERTY()`

### `Source/Programs/SwitchboardListener/SblCore/Private/SwitchboardProtocol.h` (Private)


#### enum `ECreateTaskStatus`  
`enum class ECreateTaskStatus`  
_L48-55_
- L50 _public enumerator_ `Success`
- L52 _public enumerator_ `Error_Unauthenticated`
- L53 _public enumerator_ `Error_ParsingFailed`
- L54 _public enumerator_ `Error_Unhandled`

#### struct `FCreateTaskResult`  
`struct FCreateTaskResult`  
_L57-65_
- L59 _public member_ `ECreateTaskStatus Status;`
- L60 _public member_ `TUniquePtr<FSwitchboardTask> Task;`
- L61 _public member_ `bool bEcho;`
- L63 _public member_ `TOptional<FString> CommandName;`
- L64 _public member_ `TOptional<FGuid> MessageID;`

#### Free symbols / members of external scopes

- L21 _function_ `template<typename InStructType> FString CreateMessage(const InStructType& InStruct)`
- L28 _prototype_ `FString CreateMessage(const TMap<FString, FString>& InFields);`
- L30 _prototype_ `FString CreateTaskDeclinedMessage(const FSwitchboardTask& InTask, const FString& InErrorMessage, const TMap<FString, FString>& InAdditionalFields);`
- L31 _prototype_ `FString CreateCommandAcceptedMessage(const FGuid& InMessageID);`
- L32 _prototype_ `FString CreateCommandDeclinedMessage(const FGuid& InMessageID, const FString& InErrorMessage);`
- L34 _prototype_ `FString CreateReceiveFileFromClientCompletedMessage(const FString& InDestinationPath);`
- L35 _prototype_ `FString CreateReceiveFileFromClientFailedMessage(const FString& InDestinationPath, const FString& InError);`
- L37 _prototype_ `FString CreateSendFileToClientCompletedMessage(const FString& InSourcePath, const FString& InFileContent);`
- L38 _prototype_ `FString CreateSendFileToClientFailedMessage(const FString& InSourcePath, const FString& InError);`
- L40 _prototype_ `FString CreateSyncStatusMessage(const FSyncStatus& SyncStatus, ESyncStatusRequestFlags RequestFlags);`
- L42 _prototype_ `FString CreateRedeployStatusMessage(const FGuid& InMessageID, bool bAck, const FString& Status);`
- L44 _prototype_ `FString CreateLiveLogStreamTerminatedMessage(const FString& InLogFilePath, const FString& InReason);`
- L67 _prototype_ `FCreateTaskResult CreateTaskFromCommand(const FString& InCommand, const FIPv4Endpoint& InEndpoint, bool bAuthenticated);`

### `Source/Programs/SwitchboardListener/SblCore/Private/SwitchboardTasks.h` (Private)


#### enum `ESwitchboardTaskType`  
`enum class ESwitchboardTaskType : uint8`  
_L9-29_
- L11 _public enumerator_ `Authenticate`
- L12 _public enumerator_ `Start`
- L13 _public enumerator_ `Kill`
- L14 _public enumerator_ `Restart`
- L15 _public enumerator_ `ReceiveFileFromClient`
- L16 _public enumerator_ `SendFileToClient`
- L17 _public enumerator_ `Disconnect`
- L18 _public enumerator_ `KeepAlive`
- L19 _public enumerator_ `GetSyncStatus`
- L20 _public enumerator_ `GetFlipMode`
- L21 _public enumerator_ `FixExeFlags`
- L22 _public enumerator_ `RedeployListener`
- L23 _public enumerator_ `RefreshMosaics`
- L24 _public enumerator_ `MinimizeWindows`
- L25 _public enumerator_ `SetInactiveTimeout`
- L26 _public enumerator_ `FreeListenerBinary`
- L27 _public enumerator_ `StartLiveLogStream`
- L28 _public enumerator_ `StopLiveLogStream`

#### struct `FSwitchboardTask`  
`struct FSwitchboardTask`  
_L32-53_
- L34 _public member_ `ESwitchboardTaskType Type;`
- L35 _public member_ `FGuid TaskID;`
- L36 _public member_ `FIPv4Endpoint Recipient;`
- L38 _public function_ `FSwitchboardTask(ESwitchboardTaskType InType, FGuid InTaskID, FIPv4Endpoint InRecipient) : Type(InType) , TaskID(InTaskID) , Recipient(InRecipient)`
- L44 _public prototype_ `virtual ~FSwitchboardTask() = default;`
- L46 _public prototype_ `virtual const TCHAR* GetCommandName() const = 0;`
- L49 _public function_ `virtual uint32 GetEquivalenceHash() const` — Calculates a hash that should be the same for equivalent Tasks, even if their TaskID is different

#### struct `FSwitchboardAuthenticateTask`  
`struct FSwitchboardAuthenticateTask : public FSwitchboardTask`  
_L55-82_
- inherits: `FSwitchboardTask`
- L57 _public function_ `FSwitchboardAuthenticateTask( const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, TOptional<FString> InJwt, TOptional<FString> InPassword ) : FSwitchboardTask`
- L70 _public member_ `TOptional<FString> Jwt;`
- L71 _public member_ `TOptional<FString> Password;`
- L74 _public member_ `static constexpr const TCHAR* CommandName = TEXT("aut`
- L75 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L77 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### enum `ESyncStatusRequestFlags`  
`enum class ESyncStatusRequestFlags`  
_L85-100_
- desc: Bit flags for the request. It should match its counterpart's definition in message_protocol.py
- L87 _public enumerator_ `None = 0`
- L88 _public enumerator_ `SyncTopos = 1 << 0`
- L89 _public enumerator_ `MosaicTopos = 1 << 1`
- L90 _public enumerator_ `FlipModeHistory = 1 << 2`
- L91 _public enumerator_ `ProgramLayers = 1 << 3`
- L92 _public enumerator_ `DriverInfo = 1 << 4`
- L93 _public enumerator_ `Taskbar = 1 << 5`
- L94 _public enumerator_ `PidInFocus = 1 << 6`
- L95 _public enumerator_ `CpuUtilization = 1 << 7`
- L96 _public enumerator_ `AvailablePhysicalMemory = 1 << 8`
- L97 _public enumerator_ `GpuUtilization = 1 << 9`
- L98 _public enumerator_ `GpuCoreClockKhz = 1 << 10`
- L99 _public enumerator_ `GpuTemperature = 1 << 11`

#### struct `FSwitchboardGetSyncStatusTask`  
`struct FSwitchboardGetSyncStatusTask : public FSwitchboardTask`  
_L102-131_
- inherits: `FSwitchboardTask`
- L104 _public function_ `FSwitchboardGetSyncStatusTask( const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, const FGuid& InProgramID, const ESyncStatusRequestFlags InRequestFlags ) : FSwitchboardTask`
- L116 _public member_ `FGuid ProgramID;` — ID of the program that we wish to get the FlipMode of
- L119 _public member_ `ESyncStatusRequestFlags RequestFlags = static_cast<ESyncStatusRequestFlags>(~0);` — Mask for the information requested
- L122 _public member_ `static constexpr const TCHAR* CommandName = TEXT("get`
- L123 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L125 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardRefreshMosaicsTask`  
`struct FSwitchboardRefreshMosaicsTask : public FSwitchboardTask`  
_L133-143_
- inherits: `FSwitchboardTask`
- L135 _public function_ `FSwitchboardRefreshMosaicsTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint) : FSwitchboardTask`
- L140 _public member_ `static constexpr const TCHAR* CommandName = TEXT("ref`
- L141 _public function_ `virtual const TCHAR* GetCommandName() const override`

#### struct `FSwitchboardStartTask`  
`struct FSwitchboardStartTask : public FSwitchboardTask`  
_L145-187_
- inherits: `FSwitchboardTask`
- L147 _public function_ `FSwitchboardStartTask( const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, const FString& InCommand, const FString& InArgs, const FString& InName, const FString& InCaller, const FString& InWorkingDir ) : FSwitchboardTask`
- L165 _public member_ `FString Command;`
- L166 _public member_ `FString Arguments;`
- L167 _public member_ `FString Name;`
- L168 _public member_ `FString Caller;`
- L169 _public member_ `FString WorkingDir;`
- L170 _public member_ `bool bUpdateClientsWithStdout = false;`
- L171 _public member_ `bool bCombinedStdoutStderr = true;`
- L172 _public member_ `bool bLockGpuClock = false;`
- L173 _public member_ `int32 PriorityModifier = 0;`
- L174 _public member_ `bool bHide = false;`
- L177 _public member_ `static constexpr const TCHAR* CommandName = TEXT("sta`
- L178 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L180 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardKillTask`  
`struct FSwitchboardKillTask : public FSwitchboardTask`  
_L189-214_
- inherits: `FSwitchboardTask`
- L191 _public function_ `FSwitchboardKillTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, const FGuid& InProgramID, float InSoftKillTimeout = -1.0f) : FSwitchboardTask`
- L198 _public member_ `FGuid ProgramID;` — unique ID of process to kill
- L201 _public member_ `float SoftKillTimeout = 2.0f;` — Time after a soft termination signal before issuing a hard termination signal.
- L204 _public member_ `static constexpr const TCHAR* CommandName = TEXT("kil`
- L205 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L207 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardReceiveFileFromClientTask`  
`struct FSwitchboardReceiveFileFromClientTask : public FSwitchboardTask`  
_L216-238_
- inherits: `FSwitchboardTask`
- L218 _public function_ `FSwitchboardReceiveFileFromClientTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint, const FString& InDestination, const FString& InContent) : FSwitchboardTask`
- L224 _public member_ `FString Destination;`
- L225 _public member_ `FString FileContent;`
- L226 _public member_ `bool bForceOverwrite = false;`
- L229 _public member_ `static constexpr const TCHAR* CommandName = TEXT("sen`
- L230 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L232 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardRedeployListenerTask`  
`struct FSwitchboardRedeployListenerTask : public FSwitchboardTask`  
_L240-262_
- inherits: `FSwitchboardTask`
- L242 _public function_ `FSwitchboardRedeployListenerTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint, const FString& InExpectedHashHexDigest, const FString& InContent) : FSwitchboardTask`
- L249 _public member_ `FSHAHash ExpectedHash;`
- L250 _public member_ `FString FileContent;`
- L253 _public member_ `static constexpr const TCHAR* CommandName = TEXT("red`
- L254 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L256 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardSendFileToClientTask`  
`struct FSwitchboardSendFileToClientTask : public FSwitchboardTask`  
_L264-282_
- inherits: `FSwitchboardTask`
- L266 _public function_ `FSwitchboardSendFileToClientTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint, const FString& InSource) : FSwitchboardTask`
- L271 _public member_ `FString Source;`
- L274 _public member_ `static constexpr const TCHAR* CommandName = TEXT("rec`
- L275 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L277 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardFixExeFlagsTask`  
`struct FSwitchboardFixExeFlagsTask : public FSwitchboardTask`  
_L284-302_
- inherits: `FSwitchboardTask`
- L286 _public function_ `FSwitchboardFixExeFlagsTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, const FGuid& InProgramID) : FSwitchboardTask`
- L291 _public member_ `FGuid ProgramID;`
- L294 _public member_ `static constexpr const TCHAR* CommandName = TEXT("fix`
- L295 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L297 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardDisconnectTask`  
`struct FSwitchboardDisconnectTask : public FSwitchboardTask`  
_L304-314_
- inherits: `FSwitchboardTask`
- L306 _public function_ `FSwitchboardDisconnectTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint) : FSwitchboardTask`
- L311 _public member_ `static constexpr const TCHAR* CommandName = TEXT("dis`
- L312 _public function_ `virtual const TCHAR* GetCommandName() const override`

#### struct `FSwitchboardKeepAliveTask`  
`struct FSwitchboardKeepAliveTask : public FSwitchboardTask`  
_L316-326_
- inherits: `FSwitchboardTask`
- L318 _public function_ `FSwitchboardKeepAliveTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint) : FSwitchboardTask`
- L323 _public member_ `static constexpr const TCHAR* CommandName = TEXT("kee`
- L324 _public function_ `virtual const TCHAR* GetCommandName() const override`

#### struct `FSwitchboardMinimizeWindowsTask`  
`struct FSwitchboardMinimizeWindowsTask : public FSwitchboardTask`  
_L328-338_
- inherits: `FSwitchboardTask`
- L330 _public function_ `FSwitchboardMinimizeWindowsTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint) : FSwitchboardTask`
- L335 _public member_ `static constexpr const TCHAR* CommandName = TEXT("min`
- L336 _public function_ `virtual const TCHAR* GetCommandName() const override`

#### struct `FSwitchboardSetInactiveTimeoutTask`  
`struct FSwitchboardSetInactiveTimeoutTask : public FSwitchboardTask`  
_L340-358_
- inherits: `FSwitchboardTask`
- L342 _public function_ `FSwitchboardSetInactiveTimeoutTask(const FGuid& InTaskId, const FIPv4Endpoint& InEndpoint, double InTimeoutSeconds) : FSwitchboardTask`
- L347 _public member_ `double TimeoutSeconds;`
- L350 _public member_ `static constexpr const TCHAR* CommandName = TEXT("set`
- L351 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L353 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardFreeListenerBinaryTask`  
`struct FSwitchboardFreeListenerBinaryTask : public FSwitchboardTask`  
_L360-370_
- inherits: `FSwitchboardTask`
- L362 _public function_ `FSwitchboardFreeListenerBinaryTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint) : FSwitchboardTask`
- L367 _public member_ `static constexpr const TCHAR* CommandName = TEXT("fre`
- L368 _public function_ `virtual const TCHAR* GetCommandName() const override`

#### struct `FSwitchboardStartLiveLogStreamTask`  
`struct FSwitchboardStartLiveLogStreamTask : public FSwitchboardTask`  
_L372-398_
- inherits: `FSwitchboardTask`
- L374 _public function_ `FSwitchboardStartLiveLogStreamTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint, const FString& InLogFilePath, bool bInTailOnly = false, const FGuid& InProcessUUID = FGuid(), int64 InStartOffset = -1) : FSwitchboardTask`
- L383 _public member_ `FString LogFilePath;`
- L384 _public member_ `bool bTailOnly;`
- L385 _public member_ `FGuid ProcessUUID;`
- L386 _public member_ `int64 StartOffset;` — -1 means use default behavior (0 or file size based on bTailOnly)
- L389 _public member_ `static constexpr const TCHAR* CommandName = TEXT("sta`
- L390 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L392 _public function_ `virtual uint32 GetEquivalenceHash() const override`

#### struct `FSwitchboardStopLiveLogStreamTask`  
`struct FSwitchboardStopLiveLogStreamTask : public FSwitchboardTask`  
_L400-418_
- inherits: `FSwitchboardTask`
- L402 _public function_ `FSwitchboardStopLiveLogStreamTask(const FGuid& InTaskID, const FIPv4Endpoint& InEndpoint, const FString& InLogFilePath) : FSwitchboardTask`
- L407 _public member_ `FString LogFilePath;`
- L410 _public member_ `static constexpr const TCHAR* CommandName = TEXT("sto`
- L411 _public function_ `virtual const TCHAR* GetCommandName() const override`
- L413 _public function_ `virtual uint32 GetEquivalenceHash() const override`

### `Source/Programs/SwitchboardListener/SblCore/Private/SyncStatus.h` (Private)


#### struct `FSyncGpu`  
`struct FSyncGpu`  
_L11-20_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bIsSynced;` — `UPROPERTY()`
- L19 _public member_ `int32 Connector;` — `UPROPERTY()`

#### struct `FSyncDisplay`  
`struct FSyncDisplay`  
_L23-39_
- reflection: `USTRUCT()`
- L28 _public member_ `FName SyncState;` — `UPROPERTY()`
- L31 _public member_ `uint32 Bpc;` — `UPROPERTY()`
- L34 _public member_ `uint8 ColorFormat;` — `UPROPERTY()`
- L37 _public member_ `int32 Depth;` — `UPROPERTY()`

#### struct `FSyncStatusParams`  
`struct FSyncStatusParams`  
_L43-59_
- reflection: `USTRUCT()`
- L48 _public member_ `uint32 RefreshRate;` — `UPROPERTY()`
- L51 _public member_ `uint32 HouseSyncIncoming;` — `UPROPERTY()`
- L54 _public member_ `bool bHouseSync;` — `UPROPERTY()`
- L58 _public member_ `bool bInternalSecondary;` — `UPROPERTY()` — Per nvapi.h comment: "means that this P2061 board receives input from another P2061 board"

#### struct `FSyncDelay`  
`struct FSyncDelay`  
_L62-77_
- reflection: `USTRUCT()`
- L67 _public member_ `uint32 NumLines;` — `UPROPERTY()`
- L70 _public member_ `uint32 NumPixels;` — `UPROPERTY()`
- L73 _public member_ `uint32 MaxLines;` — `UPROPERTY()`
- L76 _public member_ `uint32 MinPixels;` — `UPROPERTY()`

#### struct `FSyncControlParams`  
`struct FSyncControlParams`  
_L80-107_
- reflection: `USTRUCT()`
- L85 _public member_ `int32 Polarity;` — `UPROPERTY()`
- L88 _public member_ `int32 VMode;` — `UPROPERTY()`
- L91 _public member_ `uint32 Interval;` — `UPROPERTY()`
- L94 _public member_ `int32 Source;` — `UPROPERTY()`
- L97 _public member_ `bool bInterlaced;` — `UPROPERTY()`
- L100 _public member_ `bool bSyncSourceIsOutput;` — `UPROPERTY()`
- L103 _public member_ `FSyncDelay SyncSkew;` — `UPROPERTY()`
- L106 _public member_ `FSyncDelay StartupDelay;` — `UPROPERTY()`

#### struct `FSyncTopo`  
`struct FSyncTopo`  
_L110-125_
- reflection: `USTRUCT()`
- L115 _public member_ `TArray<FSyncGpu> SyncGpus;` — `UPROPERTY()`
- L118 _public member_ `TArray<FSyncDisplay> SyncDisplays;` — `UPROPERTY()`
- L121 _public member_ `FSyncStatusParams SyncStatusParams;` — `UPROPERTY()`
- L124 _public member_ `FSyncControlParams SyncControlParams;` — `UPROPERTY()`

#### struct `FMosaicDisplaySettings`  
`struct FMosaicDisplaySettings`  
_L128-143_
- reflection: `USTRUCT()`
- L133 _public member_ `uint32 Width;` — `UPROPERTY()`
- L136 _public member_ `uint32 Height;` — `UPROPERTY()`
- L139 _public member_ `uint32 Bpp;` — `UPROPERTY()`
- L142 _public member_ `uint32 Freq;` — `UPROPERTY()`

#### struct `FMosaicTopo`  
`struct FMosaicTopo`  
_L146-161_
- reflection: `USTRUCT()`
- L151 _public member_ `uint32 Rows;` — `UPROPERTY()`
- L154 _public member_ `uint32 Columns;` — `UPROPERTY()`
- L157 _public member_ `uint32 DisplayCount;` — `UPROPERTY()`
- L160 _public member_ `FMosaicDisplaySettings DisplaySettings;` — `UPROPERTY()`

#### struct `FSyncStatus`  
`struct FSyncStatus`  
_L164-206_
- reflection: `USTRUCT()`
- L169 _public member_ `TArray<FSyncTopo> SyncTopos;` — `UPROPERTY()`
- L172 _public member_ `TArray<FMosaicTopo> MosaicTopos;` — `UPROPERTY()`
- L175 _public member_ `TArray<FString> FlipModeHistory;` — `UPROPERTY()`
- L178 _public member_ `TArray<FString> ProgramLayers;` — `UPROPERTY()`
- L181 _public member_ `uint32 DriverVersion;` — `UPROPERTY()`
- L184 _public member_ `FString DriverBranch;` — `UPROPERTY()`
- L187 _public member_ `FString Taskbar;` — `UPROPERTY()`
- L190 _public member_ `uint32 PidInFocus;` — `UPROPERTY()`
- L193 _public member_ `TArray<int8> CpuUtilization;` — `UPROPERTY()`
- L196 _public member_ `uint64 AvailablePhysicalMemory;` — `UPROPERTY()`
- L199 _public member_ `TArray<int8> GpuUtilization;` — `UPROPERTY()`
- L202 _public member_ `TArray<int32> GpuCoreClocksKhz;` — `UPROPERTY()`
- L205 _public member_ `TArray<int32> GpuTemperature;` — `UPROPERTY()`

### `Source/Programs/SwitchboardListener/SblCore/Private/Windows/Resources/Resource.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define IDD_SELECTBUILD 101` — {{NO_DEPENDENCIES}} Microsoft Visual C++ generated include file. Used by Resource.rc
- L8 _macro_ `#define IDD_ERRORDIALOG 105`
- L9 _macro_ `#define IDC_BROWSE 1001`
- L10 _macro_ `#define IDC_BUILDLIST 1002`
- L11 _macro_ `#define IDC_ERRORLOGTEXT 1005`
- L12 _macro_ `#define IDC_ERRORMESSAGE 1006`
- L18 _macro_ `#define _APS_NEXT_RESOURCE_VALUE 106`
- L19 _macro_ `#define _APS_NEXT_COMMAND_VALUE 40001`
- L20 _macro_ `#define _APS_NEXT_CONTROL_VALUE 1007`
- L21 _macro_ `#define _APS_NEXT_SYMED_VALUE 101`
