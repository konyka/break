# Runtime / EngineMessages

- module root: `Source/Runtime/EngineMessages`
- headers: 2; symbols: 112
- symbol kinds: enum=1, enumerator=3, function=6, member=69, struct=33
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject

### `Source/Runtime/EngineMessages/Public/EngineServiceMessages.h` (Public)


#### struct `FEngineServicePing`  
`struct FEngineServicePing`  
_L18-21_
- reflection: `USTRUCT()`
- desc: Implements a message for discovering engine instances on the network.

#### struct `FEngineServicePong`  
`struct FEngineServicePong`  
_L28-59_
- reflection: `USTRUCT()`
- desc: Implements a message for responding to a request to discover engine instances on the network.
- L34 _public member_ `FString CurrentLevel;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the currently loaded level, if any.
- L38 _public member_ `int32 EngineVersion=0;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the engine version.
- L42 _public member_ `bool HasBegunPlay=false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether game play has begun.
- L46 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the instance identifier.
- L50 _public member_ `FString InstanceType;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the type of the engine instance.
- L54 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the identifier of the session that the application belongs to.
- L58 _public member_ `float WorldTimeSeconds=0.0f;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the time in seconds since the world was loaded.

#### struct `FEngineServiceAuthDeny`  
`struct FEngineServiceAuthDeny`  
_L69-80_
- reflection: `USTRUCT()`
- desc: Implements a message for denying service access to a remote user.
- L75 _public member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that denied access.
- L79 _public member_ `FString UserToDeny;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that access is denied to.

#### struct `FEngineServiceAuthGrant`  
`struct FEngineServiceAuthGrant`  
_L87-99_
- reflection: `USTRUCT()`
- desc: Implements a message for granting service access to a remote user.
- L93 _public member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that granted access.
- L97 _public member_ `FString UserToGrant;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that access is granted to.

#### struct `FEngineServiceExecuteCommand`  
`struct FEngineServiceExecuteCommand`  
_L109-129_
- reflection: `USTRUCT()`
- desc: Implements a message for executing a console command.
- L115 _public member_ `FString Command;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the command to execute.
- L119 _public member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that wants to execute the command.
- L122 _public function_ `FEngineServiceExecuteCommand()` — Default constructor.
- L125 _public function_ `FEngineServiceExecuteCommand(const FString& InCommand, const FString& InUserName) : Command(InCommand) , UserName(InUserName)` — Creates and initializes a new instance.

#### struct `FEngineServiceTerminate`  
`struct FEngineServiceTerminate`  
_L136-151_
- reflection: `USTRUCT()`
- desc: Implements a message for terminating the engine.
- L142 _public member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that wants to terminate the engine.
- L145 _public function_ `FEngineServiceTerminate()` — Default constructor.
- L148 _public function_ `FEngineServiceTerminate(const FString& InUserName) : UserName(InUserName)` — Creates and initializes a new instance.

#### struct `FEngineServiceNotification`  
`struct FEngineServiceNotification`  
_L161-181_
- reflection: `USTRUCT()`
- desc: Implements a message that contains a notification or log output.
- L167 _public member_ `FString Text;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the notification text.
- L171 _public member_ `double TimeSeconds;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the time in seconds since the engine started.
- L174 _public function_ `FEngineServiceNotification() : TimeSeconds(0.0)` — Default constructor.
- L177 _public function_ `FEngineServiceNotification(const FString& InText, double InTimeSeconds) : Text(InText) , TimeSeconds(InTimeSeconds)` — Creates and initializes a new instance.

### `Source/Runtime/EngineMessages/Public/TraceControlMessages.h` (Public)


#### struct `FTraceControlStatusPing`  
`struct FTraceControlStatusPing`  
_L19-22_
- reflection: `USTRUCT()`
- desc: Request a status update

#### struct `FTraceControlStatus`  
`struct FTraceControlStatus`  
_L29-74_
- reflection: `USTRUCT()`
- desc: Response for FTraceControlStatusPing. Meant to be fairly high frequency.
- L34 _public member_ `FString Endpoint;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L37 _public member_ `FGuid SessionGuid;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L40 _public member_ `FGuid TraceGuid;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L43 _public member_ `uint64 BytesSent = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L46 _public member_ `uint64 BytesTraced = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L49 _public member_ `uint64 MemoryUsed = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L52 _public member_ `uint32 CacheAllocated = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L55 _public member_ `uint32 CacheUsed = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L58 _public member_ `uint32 CacheWaste = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L61 _public member_ `bool bAreStatNamedEventsEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L64 _public member_ `bool bIsPaused = false;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L67 _public member_ `bool bIsTracing = false;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L70 _public member_ `FDateTime StatusTimestamp;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L73 _public member_ `uint8 TraceSystemStatus = 0;` — `UPROPERTY(EditAnywhere, Category = "Message")`

#### struct `FTraceControlSettingsPing`  
`struct FTraceControlSettingsPing`  
_L80-83_
- reflection: `USTRUCT()`
- desc: Request update of settings

#### struct `FTraceChannelPreset`  
`struct FTraceChannelPreset`  
_L89-101_
- reflection: `USTRUCT()`
- desc: Contains data about a trace channel preset
- L94 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L97 _public member_ `FString ChannelList;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L100 _public member_ `bool bIsReadOnly = false;` — `UPROPERTY(EditAnywhere, Category = "Message")`

#### struct `FTraceCapability`  
`struct FTraceCapability`  
_L104-110_
- reflection: `USTRUCT()`
- L109 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlSettings`  
`struct FTraceControlSettings`  
_L117-135_
- reflection: `USTRUCT()`
- desc: Response for FTraceControlSettingsPing containing TraceLog and system settings.
- L122 _public member_ `bool bUseWorkerThread = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L125 _public member_ `bool bUseImportantCache = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L128 _public member_ `uint32 TailSizeBytes = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L131 _public member_ `TArray<FTraceChannelPreset> ChannelPresets;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L134 _public member_ `TArray<FTraceCapability> Capabilities;` — `UPROPERTY(EditAnywhere, Category = "Message")`

#### struct `FTraceControlChannelsPing`  
`struct FTraceControlChannelsPing`  
_L141-147_
- reflection: `USTRUCT()`
- desc: Request update of channels and status
- L146 _public member_ `uint32 KnownChannelCount = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlChannelsDesc`  
`struct FTraceControlChannelsDesc`  
_L154-169_
- reflection: `USTRUCT()`
- desc: Response for FTraceControlChannelsPing with information about available channels.
- L159 _public member_ `TArray<FString> Channels;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L162 _public member_ `TArray<uint32> Ids;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L165 _public member_ `TArray<FString> Descriptions;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L168 _public member_ `TArray<uint32> ReadOnlyIds;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlChannelsStatus`  
`struct FTraceControlChannelsStatus`  
_L176-182_
- reflection: `USTRUCT()`
- desc: Response for FTraceControlChannelsPing with information about enabled channels.
- L181 _public member_ `TArray<uint32> EnabledIds;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlChannelsSet`  
`struct FTraceControlChannelsSet`  
_L189-198_
- reflection: `USTRUCT()`
- desc: Command to set the state of channels
- L194 _public member_ `TArray<uint32> ChannelIdsToEnable;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L197 _public member_ `TArray<uint32> ChannelIdsToDisable;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlChannelsSetError`  
`struct FTraceControlChannelsSetError`  
_L204-210_
- reflection: `USTRUCT()`
- desc: Error messages related to channel enable/disable commands
- L209 _public member_ `TMap<uint32, FString> Errors;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlDiscoveryPing`  
`struct FTraceControlDiscoveryPing`  
_L217-226_
- reflection: `USTRUCT()`
- desc: Message sent when first connecting to a session. Expected to return FTraceControlPong message.
- L222 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L225 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlDiscovery`  
`struct FTraceControlDiscovery : public FTraceControlStatus`  
_L234-243_
- reflection: `USTRUCT()`
- inherits: `FTraceControlStatus`
- desc: Response for FTraceControlPing. A status message with additional information about session instance and properties that doesn't change over the course of the session lifetime.
- L239 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L242 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlStop`  
`struct FTraceControlStop`  
_L249-252_
- reflection: `USTRUCT()`
- desc: Stop current trace.

#### struct `FTraceControlStartCommon`  
`struct FTraceControlStartCommon`  
_L258-267_
- reflection: `USTRUCT()`
- desc: Shared properties for starting a trace. Never use this message directly.
- L263 _public member_ `FString Channels;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L266 _public member_ `bool bExcludeTail = false;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlSend`  
`struct FTraceControlSend : public FTraceControlStartCommon`  
_L273-279_
- reflection: `USTRUCT()`
- inherits: `FTraceControlStartCommon`
- desc: Start tracing to a host
- L278 _public member_ `FString Host;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlFile`  
`struct FTraceControlFile : public FTraceControlStartCommon`  
_L285-294_
- reflection: `USTRUCT()`
- inherits: `FTraceControlStartCommon`
- desc: Start tracing to a file (on the receiver)
- L290 _public member_ `FString File;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L293 _public member_ `bool bTruncateFile = false;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlSecure`  
`struct FTraceControlSecure : public FTraceControlStartCommon`  
_L300-303_
- reflection: `USTRUCT()`
- inherits: `FTraceControlStartCommon`
- desc: Start tracing to a host using a secure connection (if supported on the target)

#### enum `ETraceSecureMode`  
`enum class ETraceSecureMode : uint8`  
_L311-316_
- reflection: `UENUM()`
- desc: Secure connection mode. See TraceAuxiliary for details.
- L313 _public enumerator_ `SelfSignedCertAndAuthToken`
- L314 _public enumerator_ `CertFileAndAuthToken`
- L315 _public enumerator_ `AuthToken`

#### struct `FTraceControlSecureResponse`  
`struct FTraceControlSecureResponse`  
_L324-345_
- reflection: `USTRUCT()`
- desc: Response to a secure start request. Specifies port to connect to, optional authorization token, and optional certificate if using self-signed certificates.
- L329 _public member_ `FString Host;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L332 _public member_ `uint16 Port = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L335 _public member_ `ETraceSecureMode Mode = ETraceSecureMode::SelfSignedCertAndAuthToken;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L338 _public member_ `TArray<uint8> AuthorizationToken;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L341 _public member_ `TArray<uint8> CertificateAuthority;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L344 _public member_ `FString Identity;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlPause`  
`struct FTraceControlPause`  
_L353-356_
- reflection: `USTRUCT()`
- desc: Pause all tracing (i.e. mute all channels)

#### struct `FTraceControlResume`  
`struct FTraceControlResume`  
_L362-365_
- reflection: `USTRUCT()`
- desc: Resume all tracing (from pause)

#### struct `FTraceControlSnapshotSend`  
`struct FTraceControlSnapshotSend`  
_L371-377_
- reflection: `USTRUCT()`
- desc: Trace a snapshot to the trace server.
- L376 _public member_ `FString Host;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlSnapshotFile`  
`struct FTraceControlSnapshotFile`  
_L383-389_
- reflection: `USTRUCT()`
- desc: Trace a snapshot to a file.
- L388 _public member_ `FString File;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlBookmark`  
`struct FTraceControlBookmark`  
_L395-401_
- reflection: `USTRUCT()`
- desc: Trace a bookmark with the given label.
- L400 _public member_ `FString Label;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlScreenshot`  
`struct FTraceControlScreenshot`  
_L407-416_
- reflection: `USTRUCT()`
- desc: Trace a screenshot with the given label.
- L412 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L415 _public member_ `bool bShowUI = true;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FTraceControlSetStatNamedEvents`  
`struct FTraceControlSetStatNamedEvents`  
_L422-428_
- reflection: `USTRUCT()`
- desc: Set the StatNamedEvents flag.
- L427 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Message")`
