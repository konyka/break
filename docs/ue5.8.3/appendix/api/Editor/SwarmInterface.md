# Editor / SwarmInterface

- module root: `Source/Editor/SwarmInterface`
- headers: 3; symbols: 279
- symbol kinds: class=10, enum=12, enumerator=122, function=37, macro=2, member=63, namespace=2, prototype=18, struct=12, typedef=1
- PrivateIncludePathModuleNames: MessagingCommon
- PublicDependencyModuleNames: Core, CoreUObject, Networking, Sockets

### `Source/Editor/SwarmInterface/Private/SwarmMessages.h` (Private)


#### struct `FSwarmPingMessage`  
`struct FSwarmPingMessage`  
_L13-16_
- reflection: `USTRUCT()`

#### struct `FSwarmPongMessage`  
`struct FSwarmPongMessage`  
_L20-38_
- reflection: `USTRUCT()`
- L25 _public member_ `bool bIsEditor;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L28 _public member_ `FString ComputerName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L30 _public function_ `FSwarmPongMessage() : bIsEditor(false)`
- L34 _public function_ `FSwarmPongMessage(bool bInIsEditor, const TCHAR* InComputerName) : bIsEditor(bInIsEditor) , ComputerName(InComputerName)`

#### struct `FSwarmInfoMessage`  
`struct FSwarmInfoMessage`  
_L42-54_
- reflection: `USTRUCT()`
- L47 _public member_ `FString TextMessage;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L49 _public function_ `FSwarmInfoMessage()`
- L51 _public function_ `FSwarmInfoMessage(const FString& InTextMessage) : TextMessage(InTextMessage)`

#### struct `FSwarmAlertMessage`  
`struct FSwarmAlertMessage`  
_L58-94_
- reflection: `USTRUCT()`
- L64 _public member_ `FGuid JobGuid;` — `UPROPERTY(EditAnywhere, Category="Message")` — The Job Guid
- L68 _public member_ `uint8 AlertLevel;` — `UPROPERTY(EditAnywhere, Category="Message")` — The type of alert
- L72 _public member_ `FGuid ObjectGuid;` — `UPROPERTY(EditAnywhere, Category="Message")` — The identifier for the object that is associated with the issue
- L76 _public member_ `int32 TypeId;` — `UPROPERTY(EditAnywhere, Category="Message")` — App-specific identifier for the type of the object
- L80 _public member_ `FString TextMessage;` — `UPROPERTY(EditAnywhere, Category="Message")` — Generic text message for informational purposes
- L82 _public function_ `FSwarmAlertMessage() : AlertLevel(0) , TypeId(0)`
- L87 _public function_ `FSwarmAlertMessage(const FGuid& InJobGuid, NSwarm::TAlertLevel InAlertLevel, const FGuid& InObjectGuid, int32 InTypeId, const FString& InTextMessage) : JobGuid(InJobGuid) , AlertLevel(InAlertLevel) , ObjectGuid(InObjectGuid) , TypeId(InTypeId) , TextMessage(InTextMessage)`

#### struct `FSwarmTimingMessage`  
`struct FSwarmTimingMessage`  
_L98-119_
- reflection: `USTRUCT()`
- L104 _public member_ `uint8 State;` — `UPROPERTY(EditAnywhere, Category="Message")` — State that the distributed job is transitioning to
- L108 _public member_ `int32 ThreadNum;` — `UPROPERTY(EditAnywhere, Category="Message")` — The thread this state is referring to
- L110 _public function_ `FSwarmTimingMessage() : State(0) , ThreadNum(0)`
- L115 _public function_ `FSwarmTimingMessage(NSwarm::TProgressionState InState, int32 InThreadNum) : State(InState) , ThreadNum(InThreadNum)`

#### struct `FSwarmTaskRequestMessage`  
`struct FSwarmTaskRequestMessage`  
_L123-128_
- reflection: `USTRUCT()`
- L127 _public function_ `FSwarmTaskRequestMessage()`

#### struct `FSwarmTaskRequestReleaseMessage`  
`struct FSwarmTaskRequestReleaseMessage`  
_L132-137_
- reflection: `USTRUCT()`
- L136 _public function_ `FSwarmTaskRequestReleaseMessage()`

#### struct `FSwarmTaskRequestReservationMessage`  
`struct FSwarmTaskRequestReservationMessage`  
_L141-146_
- reflection: `USTRUCT()`
- L145 _public function_ `FSwarmTaskRequestReservationMessage()`

#### struct `FSwarmTaskRequestSpecificationMessage`  
`struct FSwarmTaskRequestSpecificationMessage`  
_L150-185_
- reflection: `USTRUCT()`
- L156 _public member_ `FGuid TaskGuid;` — `UPROPERTY(EditAnywhere, Category="Message")` — The GUID used for identifying the Task being referred to
- L160 _public member_ `FString Parameters;` — `UPROPERTY(EditAnywhere, Category="Message")` — The Task's parameter string specified with AddTask
- L164 _public member_ `uint8 Flags;` — `UPROPERTY(EditAnywhere, Category="Message")` — Flags used to control the behavior of the Task, subject to overrides from the containing Job
- L168 _public member_ `uint32 Cost;` — `UPROPERTY(EditAnywhere, Category="Message")` — The Task's cost, relative to all other Tasks in the same Job, used for even distribution and scheduling
- L172 _public member_ `TArray<FString> Dependencies;` — `UPROPERTY(EditAnywhere, Category="Message")` — Any additional Task dependencies
- L174 _public function_ `FSwarmTaskRequestSpecificationMessage() : Flags(0) , Cost(0)`
- L179 _public function_ `FSwarmTaskRequestSpecificationMessage(FGuid InTaskGuid, const FString& InParameters, NSwarm::TJobTaskFlags InFlags, const TArray<FString>& InDependencies) : TaskGuid(InTaskGuid) , Parameters(InParameters) , Flags(InFlags) , Dependencies(InDependencies)`

#### struct `FSwarmJobStateMessage`  
`struct FSwarmJobStateMessage`  
_L189-224_
- reflection: `USTRUCT()`
- L195 _public member_ `FGuid Guid;` — `UPROPERTY(EditAnywhere, Category="Message")` — The Job GUID used for identifying the Job
- L199 _public member_ `uint8 State;` — `UPROPERTY(EditAnywhere, Category="Message")` — The current state and arbitrary message
- L202 _public member_ `FString Message;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L206 _public member_ `int32 ExitCode;` — `UPROPERTY(EditAnywhere, Category="Message")` — Various stats, including run time, exit codes, etc.
- L209 _public member_ `double RunningTime;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L211 _public function_ `FSwarmJobStateMessage() : State(0) , ExitCode(0) , RunningTime(0.0)`
- L217 _public function_ `FSwarmJobStateMessage(FGuid InGuid, NSwarm::TJobTaskState InState, const FString& InMessage, int32 InExitCode, double InRunningTime) : Guid(InGuid) , State(InState) , Message(InMessage) , ExitCode(InExitCode) , RunningTime(InRunningTime)`

#### struct `FSwarmTaskStateMessage`  
`struct FSwarmTaskStateMessage`  
_L228-263_
- reflection: `USTRUCT()`
- L234 _public member_ `FGuid Guid;` — `UPROPERTY(EditAnywhere, Category="Message")` — The Task GUID used for identifying the Task
- L238 _public member_ `uint8 State;` — `UPROPERTY(EditAnywhere, Category="Message")` — The current state and arbitrary message
- L241 _public member_ `FString Message;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L245 _public member_ `int32 ExitCode;` — `UPROPERTY(EditAnywhere, Category="Message")` — Various stats, including run time, exit codes, etc.
- L248 _public member_ `double RunningTime;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L250 _public function_ `FSwarmTaskStateMessage() : State(0) , ExitCode() , RunningTime(0.0)`
- L256 _public function_ `FSwarmTaskStateMessage(FGuid InGuid, NSwarm::TJobTaskState InState, const FString& InMessage, int32 InExitCode, double InRunningTime) : Guid(InGuid) , State(InState) , Message(InMessage) , ExitCode(InExitCode) , RunningTime(InRunningTime)`

#### struct `FSwarmQuitMessage`  
`struct FSwarmQuitMessage`  
_L267-272_
- reflection: `USTRUCT()`
- L271 _public function_ `FSwarmQuitMessage()`

### `Source/Editor/SwarmInterface/Public/SwarmDefines.h` (Public)


#### enum `NSwarm::(anonymous)`  
``  
_L11-31_

#### enum `NSwarm::TSwarmVersionValue`  
`enum TSwarmVersionValue`  
_L36-40_
- desc: Consistent version enum used by messages, Jobs, Tasks, etc.
- L38 _public enumerator_ `VERSION_INVALID = 0x00000000`
- L39 _public enumerator_ `VERSION_1_0 = 0x00000010`

#### enum `NSwarm::TLogFlags`  
`enum TLogFlags`  
_L45-56_
- desc: Flags to determine the level of logging
- L47 _public enumerator_ `SWARM_LOG_NONE = 0`
- L48 _public enumerator_ `SWARM_LOG_TIMINGS = ( 1 << 0 )`
- L49 _public enumerator_ `SWARM_LOG_CONNECTIONS = ( 1 << 1 )`
- L50 _public enumerator_ `SWARM_LOG_CHANNELS = ( 1 << 2 )`
- L51 _public enumerator_ `SWARM_LOG_MESSAGES = ( 1 << 3 )`
- L52 _public enumerator_ `SWARM_LOG_JOBS = ( 1 << 4 )`
- L53 _public enumerator_ `SWARM_LOG_TASKS = ( 1 << 5 )`
- L55 _public enumerator_ `SWARM_LOG_ALL = SWARM_LOG_TIMINGS | SWARM_LOG_CONNECTIONS | SWARM_LOG_CHANNELS | SWARM_LOG_MESSAGES | SWARM_LOG_JOBS | SWARM_LOG_TASKS`

#### enum `NSwarm::TVerbosityLevel`  
`enum TVerbosityLevel`  
_L61-71_
- desc: The level of debug info spewed to the log files
- L63 _public enumerator_ `VERBOSITY_Silent = 0`
- L64 _public enumerator_ `VERBOSITY_Critical`
- L65 _public enumerator_ `VERBOSITY_Simple`
- L66 _public enumerator_ `VERBOSITY_Informative`
- L67 _public enumerator_ `VERBOSITY_Complex`
- L68 _public enumerator_ `VERBOSITY_Verbose`
- L69 _public enumerator_ `VERBOSITY_ExtraVerbose`
- L70 _public enumerator_ `VERBOSITY_SuperVerbose`

#### enum `NSwarm::TLogColour`  
`enum TLogColour`  
_L74-80_
- desc: Available colours used in log text.
- L76 _public enumerator_ `LOGCOLOUR_Green = 0`
- L77 _public enumerator_ `LOGCOLOUR_Red`
- L78 _public enumerator_ `LOGCOLOUR_Orange`
- L79 _public enumerator_ `LOGCOLOUR_Blue`

#### enum `NSwarm::TProgressionState`  
`enum TProgressionState`  
_L85-115_
- desc: The current state of the lighting build process
- L87 _public enumerator_ `PROGSTATE_TaskTotal = 0`
- L88 _public enumerator_ `PROGSTATE_TasksInProgress`
- L89 _public enumerator_ `PROGSTATE_TasksCompleted`
- L90 _public enumerator_ `PROGSTATE_Idle`
- L91 _public enumerator_ `PROGSTATE_InstigatorConnected`
- L92 _public enumerator_ `PROGSTATE_RemoteConnected`
- L93 _public enumerator_ `PROGSTATE_Exporting`
- L94 _public enumerator_ `PROGSTATE_BeginJob`
- L95 _public enumerator_ `PROGSTATE_Blocked`
- L96 _public enumerator_ `PROGSTATE_Preparing0`
- L97 _public enumerator_ `PROGSTATE_Preparing1`
- L98 _public enumerator_ `PROGSTATE_Preparing2`
- L99 _public enumerator_ `PROGSTATE_Preparing3`
- L100 _public enumerator_ `PROGSTATE_Processing0`
- L101 _public enumerator_ `PROGSTATE_Processing1`
- L102 _public enumerator_ `PROGSTATE_Processing2`
- L103 _public enumerator_ `PROGSTATE_Processing3`
- L104 _public enumerator_ `PROGSTATE_FinishedProcessing0`
- L105 _public enumerator_ `PROGSTATE_FinishedProcessing1`
- L106 _public enumerator_ `PROGSTATE_FinishedProcessing2`
- L107 _public enumerator_ `PROGSTATE_FinishedProcessing3`
- L108 _public enumerator_ `PROGSTATE_ExportingResults`
- L109 _public enumerator_ `PROGSTATE_ImportingResults`
- L110 _public enumerator_ `PROGSTATE_Finished`
- L111 _public enumerator_ `PROGSTATE_RemoteDisconnected`
- L112 _public enumerator_ `PROGSTATE_InstigatorDisconnected`
- L113 _public enumerator_ `PROGSTATE_Preparing4`
- L114 _public enumerator_ `PROGSTATE_Num`

#### enum `NSwarm::TChannelFlags`  
`enum TChannelFlags`  
_L124-144_
- desc: Flags that define the intended behavior of the channel. The most important of which are whether the channel is read or write, and whether it's a general, persistent cache channel, or whether it's a job-specific channel. Additional misc flags are available as well.
- L126 _public enumerator_ `SWARM_CHANNEL_TYPE_PERSISTENT = 0x00000001`
- L127 _public enumerator_ `SWARM_CHANNEL_TYPE_JOB_ONLY = 0x00000002`
- L128 _public enumerator_ `SWARM_CHANNEL_TYPE_MASK = 0x0000000F`
- L130 _public enumerator_ `SWARM_CHANNEL_ACCESS_READ = 0x00000010`
- L131 _public enumerator_ `SWARM_CHANNEL_ACCESS_WRITE = 0x00000020`
- L132 _public enumerator_ `SWARM_CHANNEL_ACCESS_MASK = 0x000000F0`
- L135 _public enumerator_ `SWARM_CHANNEL_READ = SWARM_CHANNEL_TYPE_PERSISTENT | SWARM_CHANNEL_ACCESS_READ` — The combinations we care about are easiest to just special case here
- L136 _public enumerator_ `SWARM_CHANNEL_WRITE = SWARM_CHANNEL_TYPE_PERSISTENT | SWARM_CHANNEL_ACCESS_WRITE`
- L137 _public enumerator_ `SWARM_JOB_CHANNEL_READ = SWARM_CHANNEL_TYPE_JOB_ONLY | SWARM_CHANNEL_ACCESS_READ`
- L138 _public enumerator_ `SWARM_JOB_CHANNEL_WRITE = SWARM_CHANNEL_TYPE_JOB_ONLY | SWARM_CHANNEL_ACCESS_WRITE`
- L141 _public enumerator_ `SWARM_CHANNEL_MISC_ENABLE_PAPER_TRAIL = 0x00010000` — Any additional flags for debugging or extended features
- L142 _public enumerator_ `SWARM_CHANNEL_MISC_ENABLE_COMPRESSION = 0x00020000`
- L143 _public enumerator_ `SWARM_CHANNEL_MISC_MASK = 0x000F0000`

#### enum `NSwarm::TMessageType`  
`enum TMessageType`  
_L146-165_
- L148 _public enumerator_ `MESSAGE_NONE = 0x00000000`
- L149 _public enumerator_ `MESSAGE_INFO = 0x00000001`
- L150 _public enumerator_ `MESSAGE_ALERT = 0x00000002`
- L151 _public enumerator_ `MESSAGE_TIMING = 0x00000003`
- L152 _public enumerator_ `MESSAGE_PING = 0x00000004`
- L153 _public enumerator_ `MESSAGE_SIGNAL = 0x00000005`
- L156 _public enumerator_ `MESSAGE_JOB_SPECIFICATION = 0x00000010` — Job messages
- L157 _public enumerator_ `MESSAGE_JOB_STATE = 0x00000020`
- L160 _public enumerator_ `MESSAGE_TASK_REQUEST = 0x00000100` — Task messages
- L161 _public enumerator_ `MESSAGE_TASK_REQUEST_RESPONSE = 0x00000200`
- L162 _public enumerator_ `MESSAGE_TASK_STATE = 0x00000300`
- L164 _public enumerator_ `MESSAGE_QUIT = 0x00008000`

#### enum `NSwarm::TTaskRequestResponseType`  
`enum TTaskRequestResponseType`  
_L167-172_
- L169 _public enumerator_ `RESPONSE_TYPE_RELEASE = 0x00000001`
- L170 _public enumerator_ `RESPONSE_TYPE_RESERVATION = 0x00000002`
- L171 _public enumerator_ `RESPONSE_TYPE_SPECIFICATION = 0x00000003`

#### enum `NSwarm::TJobTaskFlags`  
`enum TJobTaskFlags`  
_L177-187_
- desc: Flags used when creating a Job or Task
- L179 _public enumerator_ `JOB_FLAG_USE_DEFAULTS = 0x00000000`
- L180 _public enumerator_ `JOB_FLAG_ALLOW_REMOTE = 0x00000001`
- L181 _public enumerator_ `JOB_FLAG_MANUAL_START = 0x00000002`
- L182 _public enumerator_ `JOB_FLAG_64BIT = 0x00000004`
- L183 _public enumerator_ `JOB_FLAG_MINIMIZED = 0x00000008`
- L185 _public enumerator_ `JOB_TASK_FLAG_USE_DEFAULTS = 0x00000000`
- L186 _public enumerator_ `JOB_TASK_FLAG_ALLOW_REMOTE = 0x00000100`

#### enum `NSwarm::TJobTaskState`  
`enum TJobTaskState`  
_L192-210_
- desc: All possible states a Job or Task can be in
- L194 _public enumerator_ `JOB_STATE_INVALID = 0x00000001`
- L195 _public enumerator_ `JOB_STATE_IDLE = 0x00000002`
- L196 _public enumerator_ `JOB_STATE_READY = 0x00000003`
- L197 _public enumerator_ `JOB_STATE_RUNNING = 0x00000004`
- L198 _public enumerator_ `JOB_STATE_COMPLETE_SUCCESS = 0x00000005`
- L199 _public enumerator_ `JOB_STATE_COMPLETE_FAILURE = 0x00000006`
- L200 _public enumerator_ `JOB_STATE_KILLED = 0x00000007`
- L202 _public enumerator_ `JOB_TASK_STATE_INVALID = 0x00000011`
- L203 _public enumerator_ `JOB_TASK_STATE_IDLE = 0x00000012`
- L204 _public enumerator_ `JOB_TASK_STATE_ACCEPTED = 0x00000013`
- L205 _public enumerator_ `JOB_TASK_STATE_REJECTED = 0x00000014`
- L206 _public enumerator_ `JOB_TASK_STATE_RUNNING = 0x00000015`
- L207 _public enumerator_ `JOB_TASK_STATE_COMPLETE_SUCCESS = 0x00000016`
- L208 _public enumerator_ `JOB_TASK_STATE_COMPLETE_FAILURE = 0x00000017`
- L209 _public enumerator_ `JOB_TASK_STATE_KILLED = 0x00000018`

#### enum `NSwarm::TAlertLevel`  
`enum TAlertLevel`  
_L215-221_
- desc: The alert levels
- L217 _public enumerator_ `ALERT_LEVEL_INFO = 0x00000001`
- L218 _public enumerator_ `ALERT_LEVEL_WARNING = 0x00000002`
- L219 _public enumerator_ `ALERT_LEVEL_ERROR = 0x00000003`
- L220 _public enumerator_ `ALERT_LEVEL_CRITICAL_ERROR UE_DEPRECATED(5.1, "CriticalError was removed because it can't trigger an assert at the callsite. Use 'checkf' instead.") = 0x00000004`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace NSwarm`
- L12 _enumerator_ `SWARM_SUCCESS = 0` (scope `NSwarm::__anon12b501e20103`)
- L14 _enumerator_ `SWARM_INVALID = -1` (scope `NSwarm::__anon12b501e20103`)
- L15 _enumerator_ `SWARM_ERROR_FILE_FOUND_NOT = -2` (scope `NSwarm::__anon12b501e20103`)
- L16 _enumerator_ `SWARM_ERROR_NULL_POINTER = -3` (scope `NSwarm::__anon12b501e20103`)
- L17 _enumerator_ `SWARM_ERROR_EXCEPTION = -4` (scope `NSwarm::__anon12b501e20103`)
- L18 _enumerator_ `SWARM_ERROR_INVALID_ARG = -5` (scope `NSwarm::__anon12b501e20103`)
- L19 _enumerator_ `SWARM_ERROR_INVALID_ARG1 = -6` (scope `NSwarm::__anon12b501e20103`)
- L20 _enumerator_ `SWARM_ERROR_INVALID_ARG2 = -7` (scope `NSwarm::__anon12b501e20103`)
- L21 _enumerator_ `SWARM_ERROR_INVALID_ARG3 = -8` (scope `NSwarm::__anon12b501e20103`)
- L22 _enumerator_ `SWARM_ERROR_INVALID_ARG4 = -9` (scope `NSwarm::__anon12b501e20103`)
- L23 _enumerator_ `SWARM_ERROR_CHANNEL_NOT_FOUND = -10` (scope `NSwarm::__anon12b501e20103`)
- L24 _enumerator_ `SWARM_ERROR_CHANNEL_NOT_READY = -11` (scope `NSwarm::__anon12b501e20103`)
- L25 _enumerator_ `SWARM_ERROR_CHANNEL_IO_FAILED = -12` (scope `NSwarm::__anon12b501e20103`)
- L26 _enumerator_ `SWARM_ERROR_CONNECTION_NOT_FOUND = -13` (scope `NSwarm::__anon12b501e20103`)
- L27 _enumerator_ `SWARM_ERROR_JOB_NOT_FOUND = -14` (scope `NSwarm::__anon12b501e20103`)
- L28 _enumerator_ `SWARM_ERROR_JOB = -15` (scope `NSwarm::__anon12b501e20103`)
- L29 _enumerator_ `SWARM_ERROR_CONNECTION_DISCONNECTED = -16` (scope `NSwarm::__anon12b501e20103`)
- L30 _enumerator_ `SWARM_ERROR_AGENT_NOT_FOUND = -17` (scope `NSwarm::__anon12b501e20103`)

### `Source/Editor/SwarmInterface/Public/SwarmInterface.h` (Public)


#### class `NSwarm::FMessage`  
`class FMessage`  
_L27-66_
- desc: A simple base class for messages. For each version of the messaging interface a newly derived type will inherit from this class. The base class is used to simply carry lightweight loads for messages, i.e. just the message type, which may be enough information in itself. For additional message data, subclass and add any additional data there.
- L33 _public function_ `FMessage( void ) : Version( VERSION_1_0 ) , Type( MESSAGE_NONE )` — Default constructor, initializes to default values
- L44 _public function_ `FMessage( TMessageType NewType ) : Version( VERSION_1_0 ) , Type( NewType )` — Constructor, initializes to specified values @param NewType The type of the message, one of EMessageType
- L56 _public function_ `FMessage( TSwarmVersionValue NewVersion, TMessageType NewType ) : Version( NewVersion ) , Type( NewType )` — Constructor, initializes to specified values @param NewVersion The version of the message format; one of ESwarmVersionValue @param NewType The type of the message, one of EMessageType
- L63 _public member_ `TSwarmVersionValue Version;` — The version of the message format; one of ESwarmVersionValue
- L65 _public member_ `TMessageType Type;` — The type of the message, one of EMessageType

#### class `NSwarm::FInfoMessage`  
`class FInfoMessage : public FMessage`  
_L73-87_
- inherits: `FMessage`
- desc: Implementation of a generic info message, which just includes generic text.
- L79 _public function_ `FInfoMessage( const TCHAR* InTextMessage ) : FMessage( VERSION_1_0, MESSAGE_INFO ) , TextMessage( InTextMessage )` — Constructor, initializes to default and specified values
- L86 _public member_ `const TCHAR* TextMessage;` — Generic text message for informational purposes

#### class `NSwarm::FAlertMessage`  
`class FAlertMessage : public FMessage`  
_L103-141_
- inherits: `FMessage`
- desc: Implementation of a alert message, which includes: - The alert type: a) warning b) error c) critical error - The Job GUID - The GUID of the item causing the issue - A 32-bit field intended to identify the type of the item - A string giving the issue message (which will be localized on the Unreal side of things).
- L109 _public function_ `FAlertMessage( const FGuid& InJobGuid, TAlertLevel InAlertLevel, const FGuid& InObjectGuid, int InTypeId ) : FMessage( VERSION_1_0, MESSAGE_ALERT ) , JobGuid(InJobGuid) , AlertLevel(InAlertLevel) , ObjectGuid(InObjectGuid) , TypeId(InTypeId) , TextMessage(NULL)` — Constructor, initializes to default and specified values
- L121 _public function_ `FAlertMessage( const FGuid& InJobGuid, TAlertLevel InAlertLevel, const FGuid& InObjectGuid, int InTypeId, const TCHAR* InTextMessage ) : FMessage( VERSION_1_0, MESSAGE_ALERT ) , JobGuid(InJobGuid) , AlertLevel(InAlertLevel) , ObjectGuid(InObjectGuid) , TypeId(InTypeId) , TextMessage( InTextMessage )` — Constructor, initializes to default and specified values
- L132 _public member_ `FGuid JobGuid;` — The Job Guid
- L134 _public member_ `TAlertLevel AlertLevel;` — The type of alert
- L136 _public member_ `FGuid ObjectGuid;` — The identifier for the object that is associated with the issue
- L138 _public member_ `int TypeId;` — App-specific identifier for the type of the object
- L140 _public member_ `const TCHAR* TextMessage;` — Generic text message for informational purposes

#### class `NSwarm::FTimingMessage`  
`class FTimingMessage : public FMessage`  
_L148-165_
- inherits: `FMessage`
- desc: Implementation of a generic info message, which just includes generic text.
- L154 _public function_ `FTimingMessage( TProgressionState NewState, int InThreadNum ) : FMessage( VERSION_1_0, MESSAGE_TIMING ) , State( NewState ) , ThreadNum( InThreadNum )` — Constructor, initializes to default and specified values
- L162 _public member_ `TProgressionState State;` — State that the distributed job is transitioning to
- L164 _public member_ `int ThreadNum;` — The thread this state is referring to

#### class `NSwarm::FTaskRequestResponse`  
`class FTaskRequestResponse : public FMessage`  
_L181-195_
- inherits: `FMessage`
- desc: Implementation of a task request response message. All uses include the GUID of the Job the request referred to. Currently used for these message types: TASK_RELEASE: Signifies that the requester is no longer required to process any more Tasks. The requester is free to consider this Job completed. TASK_RESERVATION: Sent back only if the Job specified is still active but no additional Tasks are available at this time. TASK_SPECIFICATION: Details a Task that can be worked on
- L187 _public function_ `FTaskRequestResponse( TTaskRequestResponseType NewResponseType ) : FMessage( VERSION_1_0, MESSAGE_TASK_REQUEST_RESPONSE ) , ResponseType( NewResponseType )` — Constructor, initializes to default and specified values
- L194 _public member_ `TTaskRequestResponseType ResponseType;` — The type of response this message is. Subclasses add any additional data

#### class `NSwarm::FTaskSpecification`  
`class FTaskSpecification : public FTaskRequestResponse`  
_L203-248_
- inherits: `FTaskRequestResponse`
- desc: Encapsulates information about a Task specification passed into AddTask and later sent in response to a TASK_REQUEST message
- L209 _public function_ `FTaskSpecification( FGuid TaskTaskGuid, const TCHAR* TaskParameters, TJobTaskFlags TaskFlags ) : FTaskRequestResponse( RESPONSE_TYPE_SPECIFICATION ) , TaskGuid( TaskTaskGuid ) , Parameters( TaskParameters ) , Flags( TaskFlags ) , Dependencies( NULL ) , DependencyCount( 0 )` — Constructor, initializes to default and specified values
- L227 _public function_ `void AddDependencies( const TCHAR** NewDependencies, uint32 NewDependencyCount )` — Used to add channel dependencies to a Task. When an Agent runs this Task, it will ensure that all dependencies are satisfied prior to giving the Task to the requester. @param NewDependencies The list of additional dependent channel names @param NewDependencyCount The number of elements in the NewDependencies list
- L234 _public member_ `FGuid TaskGuid;` — The GUID used for identifying the Task being referred to
- L237 _public member_ `const TCHAR* Parameters;` — The Task's parameter string specified with AddTask
- L240 _public member_ `TJobTaskFlags Flags;` — Flags used to control the behavior of the Task, subject to overrides from the containing Job
- L243 _public member_ `uint32 Cost;` — The Task's cost, relative to all other Tasks in the same Job, used for even distribution and scheduling
- L246 _public member_ `const TCHAR** Dependencies;` — Any additional Task dependencies
- L247 _public member_ `uint32 DependencyCount;`

#### class `NSwarm::FJobState`  
`class FJobState : public FMessage`  
_L256-282_
- inherits: `FMessage`
- desc: Encapsulates information about a Job's state, used to communicate back to the Instigator
- L262 _public function_ `FJobState( FGuid NewJobGuid, TJobTaskState NewJobState ) : FMessage( VERSION_1_0, MESSAGE_JOB_STATE ) , JobGuid( NewJobGuid ) , JobState( NewJobState ) , JobMessage( NULL ) , JobExitCode( 0 ) , JobRunningTime( 0.0 )` — Constructor, initializes to specified values
- L273 _public member_ `FGuid JobGuid;` — The Job GUID used for identifying the Job
- L276 _public member_ `TJobTaskState JobState;` — The current state and arbitrary message
- L277 _public member_ `const TCHAR* JobMessage;`
- L280 _public member_ `int32 JobExitCode;` — Various stats, including run time, exit codes, etc.
- L281 _public member_ `double JobRunningTime;`

#### class `NSwarm::FTaskState`  
`class FTaskState : public FMessage`  
_L290-316_
- inherits: `FMessage`
- desc: Encapsulates information about a Task's state, used to communicate back to the Instigator
- L296 _public function_ `FTaskState( FGuid NewTaskGuid, TJobTaskState NewTaskState ) : FMessage( VERSION_1_0, MESSAGE_TASK_STATE ) , TaskGuid( NewTaskGuid ) , TaskState( NewTaskState ) , TaskMessage( NULL ) , TaskExitCode( 0 ) , TaskRunningTime( 0.0 )` — Constructor, initializes to specified values
- L307 _public member_ `FGuid TaskGuid;` — The Task GUID used for identifying the Task
- L310 _public member_ `TJobTaskState TaskState;` — The current Task state and arbitrary message
- L311 _public member_ `const TCHAR* TaskMessage;`
- L314 _public member_ `int32 TaskExitCode;` — Various stats, including run time, exit codes, etc.
- L315 _public member_ `double TaskRunningTime;`

#### class `NSwarm::FJobSpecification`  
`class FJobSpecification`  
_L323-402_
- desc: Encapsulates information about a Job specification passed into BeginJobSpecification
- L329 _public function_ `FJobSpecification() : ExecutableName( NULL ) , Parameters( NULL ) , Flags( JOB_FLAG_USE_DEFAULTS ) , RequiredDependencies( NULL ) , RequiredDependencyCount( 0 ) , OptionalDependencies( NULL ) , OptionalDependencyCount( 0 ) , DescriptionKeys( NULL ) , DescriptionValues( NULL ) , DescriptionCount( 0 )` — Default constructor, initializes to an empty (invalid) job.
- L346 _public function_ `FJobSpecification( const TCHAR* JobExecutableName, const TCHAR* JobParameters, TJobTaskFlags JobFlags ) : ExecutableName( JobExecutableName ) , Parameters( JobParameters ) , Flags( JobFlags ) , RequiredDependencies( NULL ) , RequiredDependencyCount( 0 ) , OptionalDependencies( NULL ) , OptionalDependencyCount( 0 ) , DescriptionKeys( NULL ) , DescriptionValues( NULL ) , DescriptionCount( 0 )` — Constructor, initializes to default and specified values
- L370 _public function_ `void AddDependencies( const TCHAR** NewRequiredDependencies, uint32 NewRequiredDependencyCount, const TCHAR** NewOptionalDependencies, uint32 NewOptionalDependencyCount )` — Used to add channel dependencies to a Job. When an Agent runs this Job, it will ensure that all dependencies are satisfied prior to launching the executable. Note that the Job executable is an implied dependency. @param NewRequiredDependencies The list of additional required dependent channel names @param NewRequiredDependencyCount The number of elements in the NewRequiredDependencies list @param NewOptionalDependencies The list of additional optional dependent channel names @param NewOptionalDependencyCount The number of elements in the NewOptionalDependencies list
- L378 _public function_ `void AddDescription( const TCHAR** NewDescriptionKeys, const TCHAR** NewDescriptionValues, uint32 NewDescriptionCount )`
- L386 _public member_ `const TCHAR* ExecutableName;` — The Job's executable name and parameter string
- L387 _public member_ `const TCHAR* Parameters;`
- L390 _public member_ `TJobTaskFlags Flags;` — Flags used to control the behavior of the executing Job
- L393 _public member_ `const TCHAR** RequiredDependencies;` — Any additional Job dependencies
- L394 _public member_ `uint32 RequiredDependencyCount;`
- L395 _public member_ `const TCHAR** OptionalDependencies;`
- L396 _public member_ `uint32 OptionalDependencyCount;`
- L399 _public member_ `const TCHAR** DescriptionKeys;` — Optional Job description values in key/value form
- L400 _public member_ `const TCHAR** DescriptionValues;`
- L401 _public member_ `uint32 DescriptionCount;`

#### class `NSwarm::FSwarmInterface`  
`class FSwarmInterface`  
_L416-603_
- desc: The primary interface to the Swarm system
- L422 _public prototype_ `static FSwarmInterface& Get( void );` — @return The Swarm singleton
- L428 _public prototype_ `static bool Initialize(const TCHAR* SwarmInterfacePath);` — Initializes the Swarm singleton, must be called before FSwarmInterface::Get(). @return A boolean indicating if the initialization was successful
- L437 _public prototype_ `virtual int32 OpenConnection( FConnectionCallback CallbackFunc, void* CallbackData, TLogFlags LoggingFlags, const TCHAR* OptionsFolder ) = 0;` — Opens a new connection to the Swarm @param CallbackFunc The callback function Swarm will use to communicate back to the Instigator @return An int32 containing the error code (if < 0) or the handle (>= 0) which is useful for debugging only
- L444 _public prototype_ `virtual int32 CloseConnection( void ) = 0;` — Closes an existing connection to the Swarm @return int32 Error code (< 0 is an error)
- L453 _public prototype_ `virtual int32 SendMessage( const FMessage& Message ) = 0;` — Sends a message to an Agent (return messages are sent via the FConnectionCallback) @param Message The message being sent @return int32 Error code (< 0 is an error)
- L464 _public prototype_ `virtual int32 AddChannel( const TCHAR* FullPath, const TCHAR* ChannelName ) = 0;` — Adds an existing file to the cache. Note, any existing channel with the same name will be overwritten. @param FullPath The full path name to the file that should be copied into the cache @param ChannelName The name of the channel once it's in the cache @return int32 Error code (< 0 is an error)
- L473 _public prototype_ `virtual int32 TestChannel( const TCHAR* ChannelName ) = 0;` — Determines if the named channel is in the cache @param ChannelName The name of the channel to look for @return int32 Error code (< 0 is an error)
- L483 _public prototype_ `virtual int32 OpenChannel( const TCHAR* ChannelName, TChannelFlags ChannelFlags ) = 0;` — Opens a data channel for streaming data into the cache associated with an Agent @param ChannelName The name of the channel being opened @param ChannelFlags The mode, access, and other attributes of the channel being opened @return A handle to the opened channel (< 0 is an error), be sure to close it with CloseChannel
- L492 _public prototype_ `virtual int32 CloseChannel( int32 Channel ) = 0;` — Closes an open channel @param Channel An open channel handle, returned by OpenChannel @return int32 Error code (< 0 is an error)
- L503 _public prototype_ `virtual int32 WriteChannel( int32 Channel, const void* Data, int32 DataSize ) = 0;` — Writes the provided data to the open channel opened for WRITE @param Channel An open channel handle, returned by OpenChannel @param Data Source buffer for the write @param Data Size of the source buffer @return The number of bytes written (< 0 is an error)
- L514 _public prototype_ `virtual int32 ReadChannel( int32 Channel, void* Data, int32 DataSize ) = 0;` — Reads data from a channel opened for READ into the provided buffer @param Channel An open channel handle, returned by OpenChannel @param Data Destination buffer for the read @param Data Size of the destination buffer @return The number of bytes read (< 0 is an error)
- L525 _public prototype_ `virtual int32 OpenJob( const FGuid& JobGuid ) = 0;` — Opens a Job session, which allows a Job to be specified, Tasks added, Job channels opened and used, etc. When the Job is complete and no more Job related data is needed from the Swarm, call CloseJob. @param JobGuid A GUID that uniquely identifies this Job, generated by the caller @return int32 Error code (< 0 is an error)
- L542 _public prototype_ `virtual int32 BeginJobSpecification( const FJobSpecification& Specification32, const FJobSpecification& Specification64 ) = 0;` — Begins a Job specification, which allows a series of Tasks to be specified via AddTask. When Tasks are done being specified, call EndJobSpecification. The default behavior will be to execute the Job executable with the specified parameters. If Tasks are added for the Job, they are expected to be requested by the executable run for the Job. If no Tasks are added for the Job, it is expected that the Job executable will perform its operations without additional Task input from Swarm. @param Specification32 A structure describing a new 32-bit Job (can be an empty specification) @param Specification64 A structure describing a new 64-bit Job (can be an empty specification) @return int32 Error code (< 0 is an error)
- L551 _public prototype_ `virtual int32 AddTask( const FTaskSpecification& Specification ) = 0;` — Adds a Task to the current Job @param Specification A structure describing the new Task @return int32 Error code (< 0 is an error)
- L560 _public prototype_ `virtual int32 EndJobSpecification( void ) = 0;` — Ends the Job specification, after which no additional Tasks may be defined. Also, this is generally the point when the Agent will validate and launch the Job executable, potentially distributing the Job to other Agents. @return int32 Error code (< 0 is an error)
- L567 _public prototype_ `virtual int32 CloseJob( void ) = 0;` — Ends the Job, after which all Job-related API usage (except OpenJob) will be rejected @return int32 Error code (< 0 is an error)
- L576 _public prototype_ `virtual int32 Log( TVerbosityLevel Verbosity, TLogColour TextColour, const TCHAR* Message ) = 0;` — Adds a line of text to the Agent log window @param Verbosity the importance of this message @param TextColour the colour of the text @param Message the line of text to add
- L578 _public function_ `virtual void SetJobGuid( const FGuid& JobGuid )`
- L589 _public function_ `virtual bool IsJobProcessRunning( int32* OutStatus )` — Checks if the job's process is still running @param OutStatus Exit status if process is no longer running @return bool true if process is still running
- L595 _protected function_ `FSwarmInterface( void )`
- L599 _protected prototype_ `virtual ~FSwarmInterface( void ) = default;`
- L602 _private member_ `static FSwarmInterface* GInstance;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define USE_LOCAL_SWARM_INTERFACE 1`
- L12 _macro_ `#define USE_LOCAL_SWARM_INTERFACE 0`
- L17 _namespace_ `namespace NSwarm`
- L409 _typedef_ `typedef void ( *FConnectionCallback )( FMessage* CallbackMessage, void* CallbackData );` (scope `NSwarm`) — A simple callback used by the Agent to send messages back to the Instigator
