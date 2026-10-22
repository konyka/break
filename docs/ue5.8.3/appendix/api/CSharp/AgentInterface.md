# CSharp / AgentInterface

- project root: `Source/Programs/UnrealSwarm/AgentInterface`
- files: 2; symbols: 224
- symbol kinds: class=13, const=18, ctor=17, enum=11, enumerator=104, field=42, interface=1, method=18
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealSwarm/AgentInterface/AgentInterface.cs` (AgentInterface)


#### class `AgentInterface.Constants`  
`public class Constants`  
_public; L14-34_
- attrs: `[Serializable]`
- L16 _public const_ `public const Int32 SUCCESS = 0`
- L17 _public const_ `public const Int32 INVALID = -1`
- L18 _public const_ `public const Int32 ERROR_FILE_FOUND_NOT = -2`
- L19 _public const_ `public const Int32 ERROR_NULL_POINTER = -3`
- L20 _public const_ `public const Int32 ERROR_EXCEPTION = -4`
- L21 _public const_ `public const Int32 ERROR_INVALID_ARG = -5`
- L22 _public const_ `public const Int32 ERROR_INVALID_ARG1 = -6`
- L23 _public const_ `public const Int32 ERROR_INVALID_ARG2 = -7`
- L24 _public const_ `public const Int32 ERROR_INVALID_ARG3 = -8`
- L25 _public const_ `public const Int32 ERROR_INVALID_ARG4 = -9`
- L26 _public const_ `public const Int32 ERROR_CHANNEL_NOT_FOUND = -10`
- L27 _public const_ `public const Int32 ERROR_CHANNEL_NOT_READY = -11`
- L28 _public const_ `public const Int32 ERROR_CHANNEL_IO_FAILED = -12`
- L29 _public const_ `public const Int32 ERROR_CONNECTION_NOT_FOUND = -13`
- L30 _public const_ `public const Int32 ERROR_JOB_NOT_FOUND = -14`
- L31 _public const_ `public const Int32 ERROR_JOB = -15`
- L32 _public const_ `public const Int32 ERROR_CONNECTION_DISCONNECTED = -16`
- L33 _public const_ `public const Int32 ERROR_AGENT_NOT_FOUND = -17`

#### enum `AgentInterface.ESwarmVersionValue`  
`public enum ESwarmVersionValue`  
_public; L40-44_
- attrs: `[Serializable]`
- L42 _public* enumerator_ `INVALID = 0x00000000`
- L43 _public* enumerator_ `VER_1_0 = 0x00000010`

#### enum `AgentInterface.ELogFlags`  
`public enum ELogFlags`  
_public; L50-60_
- attrs: `[Serializable]`
- L52 _public* enumerator_ `LOG_NONE = 0`
- L53 _public* enumerator_ `LOG_TIMINGS = ( 1 << 0 )`
- L54 _public* enumerator_ `LOG_CONNECTIONS = ( 1 << 1 )`
- L55 _public* enumerator_ `LOG_CHANNELS = ( 1 << 2 )`
- L56 _public* enumerator_ `LOG_MESSAGES = ( 1 << 3 )`
- L57 _public* enumerator_ `LOG_JOBS = ( 1 << 4 )`
- L58 _public* enumerator_ `LOG_TASKS = ( 1 << 5 )`
- L59 _public* enumerator_ `LOG_ALL = LOG_TIMINGS | LOG_CONNECTIONS | LOG_CHANNELS | LOG_MESSAGES | LOG_JOBS | LOG_TASKS`

#### enum `AgentInterface.EVerbosityLevel`  
`public enum EVerbosityLevel`  
_public; L66-76_
- attrs: `[Serializable]`
- L68 _public* enumerator_ `Silent = 0`
- L69 _public* enumerator_ `Critical`
- L70 _public* enumerator_ `Simple`
- L71 _public* enumerator_ `Informative`
- L72 _public* enumerator_ `Complex`
- L73 _public* enumerator_ `Verbose`
- L74 _public* enumerator_ `ExtraVerbose`
- L75 _public* enumerator_ `SuperVerbose`

#### enum `AgentInterface.ELogColour`  
`public enum ELogColour`  
_public; L82-88_
- attrs: `[Serializable]`
- desc: Defines the colour of any log text written into the Agent text log.
- L84 _public* enumerator_ `Green = 0`
- L85 _public* enumerator_ `Red`
- L86 _public* enumerator_ `Blue`
- L87 _public* enumerator_ `Orange`

#### enum `AgentInterface.EProgressionState`  
`public enum EProgressionState`  
_public; L95-125_
- attrs: `[Serializable]`
- L97 _public* enumerator_ `TaskTotal = 0`
- L98 _public* enumerator_ `TasksInProgress`
- L99 _public* enumerator_ `TasksCompleted`
- L100 _public* enumerator_ `Idle`
- L101 _public* enumerator_ `InstigatorConnected`
- L102 _public* enumerator_ `RemoteConnected`
- L103 _public* enumerator_ `Exporting`
- L104 _public* enumerator_ `BeginJob`
- L105 _public* enumerator_ `Blocked`
- L106 _public* enumerator_ `Preparing0`
- L107 _public* enumerator_ `Preparing1`
- L108 _public* enumerator_ `Preparing2`
- L109 _public* enumerator_ `Preparing3`
- L110 _public* enumerator_ `Processing0`
- L111 _public* enumerator_ `FinishedProcessing0`
- L112 _public* enumerator_ `Processing1`
- L113 _public* enumerator_ `FinishedProcessing1`
- L114 _public* enumerator_ `Processing2`
- L115 _public* enumerator_ `FinishedProcessing2`
- L116 _public* enumerator_ `Processing3`
- L117 _public* enumerator_ `FinishedProcessing3`
- L118 _public* enumerator_ `ExportingResults`
- L119 _public* enumerator_ `ImportingResults`
- L120 _public* enumerator_ `Finished`
- L121 _public* enumerator_ `RemoteDisconnected`
- L122 _public* enumerator_ `InstigatorDisconnected`
- L123 _public* enumerator_ `Preparing4`
- L124 _public* enumerator_ `Num`

#### enum `AgentInterface.EChannelFlags`  
`public enum EChannelFlags`  
_public; L135-155_
- attrs: `[Serializable]`
- L137 _public* enumerator_ `TYPE_PERSISTENT = 0x00000001`
- L138 _public* enumerator_ `TYPE_JOB_ONLY = 0x00000002`
- L139 _public* enumerator_ `TYPE_MASK = 0x0000000F`
- L141 _public* enumerator_ `ACCESS_READ = 0x00000010`
- L142 _public* enumerator_ `ACCESS_WRITE = 0x00000020`
- L143 _public* enumerator_ `ACCESS_MASK = 0x000000F0`
- L146 _public* enumerator_ `CHANNEL_READ = TYPE_PERSISTENT | ACCESS_READ`
- L147 _public* enumerator_ `CHANNEL_WRITE = TYPE_PERSISTENT | ACCESS_WRITE`
- L148 _public* enumerator_ `JOB_CHANNEL_READ = TYPE_JOB_ONLY | ACCESS_READ`
- L149 _public* enumerator_ `JOB_CHANNEL_WRITE = TYPE_JOB_ONLY | ACCESS_WRITE`
- L152 _public* enumerator_ `MISC_ENABLE_PAPER_TRAIL = 0x00010000`
- L153 _public* enumerator_ `MISC_ENABLE_COMPRESSION = 0x00020000`
- L154 _public* enumerator_ `MISC_MASK = 0x000F0000`

#### enum `AgentInterface.EMessageType`  
`public enum EMessageType`  
_public; L161-180_
- attrs: `[Serializable]`
- L163 _public* enumerator_ `NONE = 0x00000000`
- L164 _public* enumerator_ `INFO = 0x00000001`
- L165 _public* enumerator_ `ALERT = 0x00000002`
- L166 _public* enumerator_ `TIMING = 0x00000003`
- L167 _public* enumerator_ `PING = 0x00000004`
- L168 _public* enumerator_ `SIGNAL = 0x00000005`
- L171 _public* enumerator_ `JOB_SPECIFICATION = 0x00000010`
- L172 _public* enumerator_ `JOB_STATE = 0x00000020`
- L175 _public* enumerator_ `TASK_REQUEST = 0x00000100`
- L176 _public* enumerator_ `TASK_REQUEST_RESPONSE = 0x00000200`
- L177 _public* enumerator_ `TASK_STATE = 0x00000300`
- L179 _public* enumerator_ `QUIT = 0x00008000`

#### enum `AgentInterface.ETaskRequestResponseType`  
`public enum ETaskRequestResponseType`  
_public; L183-188_
- attrs: `[Serializable]`
- L185 _public* enumerator_ `RELEASE = 0x00000001`
- L186 _public* enumerator_ `RESERVATION = 0x00000002`
- L187 _public* enumerator_ `SPECIFICATION = 0x00000003`

#### enum `AgentInterface.EJobTaskFlags`  
`public enum EJobTaskFlags`  
_public; L194-204_
- attrs: `[Serializable]`
- L196 _public* enumerator_ `FLAG_USE_DEFAULTS = 0x00000000`
- L197 _public* enumerator_ `FLAG_ALLOW_REMOTE = 0x00000001`
- L198 _public* enumerator_ `FLAG_MANUAL_START = 0x00000002`
- L199 _public* enumerator_ `FLAG_64BIT = 0x00000004`
- L200 _public* enumerator_ `FLAG_MINIMIZED = 0x00000008`
- L202 _public* enumerator_ `TASK_FLAG_USE_DEFAULTS = 0x00000000`
- L203 _public* enumerator_ `TASK_FLAG_ALLOW_REMOTE = 0x00000100`

#### enum `AgentInterface.EJobTaskState`  
`public enum EJobTaskState`  
_public; L210-228_
- attrs: `[Serializable]`
- L212 _public* enumerator_ `STATE_INVALID = 0x00000001`
- L213 _public* enumerator_ `STATE_IDLE = 0x00000002`
- L214 _public* enumerator_ `STATE_READY = 0x00000003`
- L215 _public* enumerator_ `STATE_RUNNING = 0x00000004`
- L216 _public* enumerator_ `STATE_COMPLETE_SUCCESS = 0x00000005`
- L217 _public* enumerator_ `STATE_COMPLETE_FAILURE = 0x00000006`
- L218 _public* enumerator_ `STATE_KILLED = 0x00000007`
- L220 _public* enumerator_ `TASK_STATE_INVALID = 0x00000011`
- L221 _public* enumerator_ `TASK_STATE_IDLE = 0x00000012`
- L222 _public* enumerator_ `TASK_STATE_ACCEPTED = 0x00000013`
- L223 _public* enumerator_ `TASK_STATE_REJECTED = 0x00000014`
- L224 _public* enumerator_ `TASK_STATE_RUNNING = 0x00000015`
- L225 _public* enumerator_ `TASK_STATE_COMPLETE_SUCCESS = 0x00000016`
- L226 _public* enumerator_ `TASK_STATE_COMPLETE_FAILURE = 0x00000017`
- L227 _public* enumerator_ `TASK_STATE_KILLED = 0x00000018`

#### enum `AgentInterface.EAlertLevel`  
`public enum EAlertLevel`  
_public; L234-240_
- attrs: `[Serializable]`
- L236 _public* enumerator_ `ALERT_INFO = 0x00000001`
- L237 _public* enumerator_ `ALERT_WARNING = 0x00000002`
- L238 _public* enumerator_ `ALERT_ERROR = 0x00000003`
- L239 _public* enumerator_ `ALERT_CRITICAL_ERROR = 0x00000004`

#### class `AgentInterface.AgentGuid`  
`public class AgentGuid : IEquatable<AgentGuid>`  
_public; L248-289_
- attrs: `[Serializable]`
- inherits: `IEquatable<AgentGuid>`
- L250-256 _public ctor_ `public AgentGuid()`
- L258-264 _public ctor_ `public AgentGuid(UInt32 InA, UInt32 InB, UInt32 InC, UInt32 InD)`
- L266-273 _public method_ `public virtual bool Equals(AgentGuid Other)`
- L275-278 _public method_ `public override int GetHashCode()`
- L280-283 _public method_ `public override String ToString()`
- L285 _public field_ `public UInt32 A`
- L286 _public field_ `public UInt32 B`
- L287 _public field_ `public UInt32 C`
- L288 _public field_ `public UInt32 D`

#### class `AgentInterface.AgentMessage`  
`public class AgentMessage`  
_public; L294-325_
- attrs: `[Serializable]`
- L296-302 _public ctor_ `public AgentMessage()`
- L304-310 _public ctor_ `public AgentMessage(EMessageType NewType)`
- L312-318 _public ctor_ `public AgentMessage(ESwarmVersionValue NewVersion, EMessageType NewType)`
- L321 _public field_ `public Int32 To`
- L322 _public field_ `public Int32 From`
- L323 _public field_ `public ESwarmVersionValue Version`
- L324 _public field_ `public EMessageType Type`

#### class `AgentInterface.AgentInfoMessage`  
`public class AgentInfoMessage : AgentMessage`  
_public; L330-345_
- attrs: `[Serializable]`
- inherits: `AgentMessage`
- L332-335 _public ctor_ `public AgentInfoMessage() : base(EMessageType.INFO)`
- L337-341 _public ctor_ `public AgentInfoMessage(String NewTextMessage) : base(EMessageType.INFO)`
- L344 _public field_ `public String TextMessage`

#### class `AgentInterface.AgentTimingMessage`  
`public class AgentTimingMessage : AgentMessage`  
_public; L350-363_
- attrs: `[Serializable]`
- inherits: `AgentMessage`
- L352-357 _public ctor_ `public AgentTimingMessage(EProgressionState NewState, int InThreadNum) : base(EMessageType.TIMING)`
- L360 _public field_ `public EProgressionState State`
- L362 _public field_ `public int ThreadNum`

#### class `AgentInterface.AgentJobMessageBase`  
`public class AgentJobMessageBase : AgentMessage`  
_public; L368-378_
- attrs: `[Serializable]`
- inherits: `AgentMessage`
- L370-374 _public ctor_ `public AgentJobMessageBase(AgentGuid NewJobGuid, EMessageType NewType) : base(NewType)`
- L377 _public field_ `public AgentGuid JobGuid`

#### class `AgentInterface.AgentAlertMessage`  
`public class AgentAlertMessage : AgentJobMessageBase`  
_public; L390-414_
- attrs: `[Serializable]`
- inherits: `AgentJobMessageBase`
- L392-395 _public ctor_ `public AgentAlertMessage(AgentGuid NewJobGuid) : base(NewJobGuid, EMessageType.ALERT)`
- L397-404 _public ctor_ `public AgentAlertMessage(AgentGuid NewJobGuid, EAlertLevel NewAlertLevel, AgentGuid NewObjectGuid, Int32 NewTypeId, String NewTextMessage) : base(NewJobGuid, EMessageType.ALERT)`
- L407 _public field_ `public EAlertLevel AlertLevel`
- L409 _public field_ `public AgentGuid ObjectGuid`
- L411 _public field_ `public Int32 TypeId`
- L413 _public field_ `public String TextMessage`

#### class `AgentInterface.AgentJobSpecification`  
`public class AgentJobSpecification`  
_public; L419-445_
- attrs: `[Serializable]`
- L421-430 _public ctor_ `public AgentJobSpecification(AgentGuid NewJobGuid, EJobTaskFlags NewJobFlags, String JobExecutableName, String JobParameters, List<String> JobRequiredDependencies, List<String> JobOptionalDependencies)`
- L433 _public field_ `public AgentGuid JobGuid`
- L434 _public field_ `public EJobTaskFlags JobFlags`
- L437 _public field_ `public String ExecutableName`
- L438 _public field_ `public String Parameters`
- L442 _public field_ `public List<String> RequiredDependencies`
- L443 _public field_ `public List<String> OptionalDependencies`
- L444 _public field_ `public Dictionary<String, String> DependenciesOriginalNames`
- L444 _public field_ `public Dictionary< DependenciesOriginalNames`

#### class `AgentInterface.AgentSignalMessage`  
`public class AgentSignalMessage : AgentMessage`  
_public; L450-459_
- attrs: `[Serializable]`
- inherits: `AgentMessage`
- L452-456 _public ctor_ `public AgentSignalMessage() : base(EMessageType.SIGNAL)`
- L458 _public field_ `public ManualResetEvent ResetEvent`

#### class `AgentInterface.AgentTaskRequestResponse`  
`public class AgentTaskRequestResponse : AgentJobMessageBase`  
_public; L464-474_
- attrs: `[Serializable]`
- inherits: `AgentJobMessageBase`
- L466-470 _public ctor_ `public AgentTaskRequestResponse(AgentGuid TaskJobGuid, ETaskRequestResponseType TaskResponseType) : base(TaskJobGuid, EMessageType.TASK_REQUEST_RESPONSE)`
- L473 _public field_ `public ETaskRequestResponseType ResponseType`

#### class `AgentInterface.AgentTaskSpecification`  
`public class AgentTaskSpecification : AgentTaskRequestResponse`  
_public; L479-507_
- attrs: `[Serializable]`
- inherits: `AgentTaskRequestResponse`
- L481-490 _public ctor_ `public AgentTaskSpecification(AgentGuid TaskJobGuid, AgentGuid TaskTaskGuid, Int32 TaskTaskFlags, String TaskParameters, Int32 TaskCost, List<String> TaskDependencies) : base(TaskJobGuid, ETaskRequestResponseType.SPECIFICATION)`
- L493 _public field_ `public AgentGuid TaskGuid`
- L494 _public field_ `public Int32 TaskFlags`
- L497 _public field_ `public String Parameters`
- L501 _public field_ `public Int32 Cost`
- L505 _public field_ `public List<String> Dependencies`
- L506 _public field_ `public Dictionary<String, String> DependenciesOriginalNames`
- L506 _public field_ `public Dictionary< DependenciesOriginalNames`

#### class `AgentInterface.AgentJobState`  
`public class AgentJobState : AgentJobMessageBase`  
_public; L512-527_
- attrs: `[Serializable]`
- inherits: `AgentJobMessageBase`
- L514-518 _public ctor_ `public AgentJobState(AgentGuid NewJobGuid, EJobTaskState NewJobState) : base(NewJobGuid, EMessageType.JOB_STATE)`
- L521 _public field_ `public EJobTaskState JobState`
- L522 _public field_ `public String JobMessage`
- L525 _public field_ `public double JobRunningTime`
- L526 _public field_ `public Int32 JobExitCode`

#### class `AgentInterface.AgentTaskState`  
`public class AgentTaskState : AgentJobMessageBase`  
_public; L532-549_
- attrs: `[Serializable]`
- inherits: `AgentJobMessageBase`
- L534-539 _public ctor_ `public AgentTaskState(AgentGuid NewJobGuid, AgentGuid NewTaskGuid, EJobTaskState NewTaskState) : base(NewJobGuid, EMessageType.TASK_STATE)`
- L542 _public field_ `public AgentGuid TaskGuid`
- L543 _public field_ `public EJobTaskState TaskState`
- L544 _public field_ `public String TaskMessage`
- L547 _public field_ `public double TaskRunningTime`
- L548 _public field_ `public Int32 TaskExitCode`

#### interface `AgentInterface.IAgentInterface`  
`public interface IAgentInterface`  
_public; L556-647_
- L561 _public* method_ `Int32 OpenConnection(Hashtable InParameters, ref Hashtable OutParameters)`
- L566 _public* method_ `Int32 CloseConnection(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L571 _public* method_ `Int32 SendMessage(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L578 _public* method_ `Int32 GetMessage(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L584 _public* method_ `Int32 AddChannel(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L589 _public* method_ `Int32 TestChannel(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L594 _public* method_ `Int32 OpenChannel(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L599 _public* method_ `Int32 CloseChannel(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L606 _public* method_ `Int32 OpenJob(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L618 _public* method_ `Int32 BeginJobSpecification(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L623 _public* method_ `Int32 AddTask(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L630 _public* method_ `Int32 EndJobSpecification(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L635 _public* method_ `Int32 CloseJob(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L641 _public* method_ `Int32 Method(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L646 _public* method_ `Int32 Log(EVerbosityLevel Verbosity, ELogColour TextColour, String Line)`

### `Source/Programs/UnrealSwarm/AgentInterface/Properties/AssemblyInfo.cs` (AgentInterface)
_(no declarations)_

