# CSharp / SwarmInterface

- project root: `Source/Editor/SwarmInterface/DotNET`
- files: 3; symbols: 311
- symbol kinds: class=21, const=2, ctor=28, delegate=47, field=123, method=87, property=2, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Editor/SwarmInterface/DotNET/Properties/AssemblyInfo.cs` (SwarmInterface)
_(no declarations)_


### `Source/Editor/SwarmInterface/DotNET/SwarmInterface.cs` (SwarmInterface)


#### class `NSwarm.DebugLog`  
`internal static class DebugLog`  
_internal; L21-28_
- L24-27 _internal method_ `internal static void Write (string msg)` — attrs: `[Conditional("DEBUG")]`

#### class `NSwarm.PerfTiming`  
`public class PerfTiming`  
_public; L35-67_
- L37 _public field_ `public String Name`
- L38 _public field_ `public Stopwatch StopWatchTimer`
- L39 _public field_ `public Int32 Count`
- L40 _public field_ `public bool Accumulate`
- L41 _public field_ `public Int64 Counter`
- L43-50 _public ctor_ `public PerfTiming(String InName, bool InAccumulate)`
- L52-55 _public method_ `public void Start()`
- L57-61 _public method_ `public void Stop()`
- L63-66 _public method_ `public void IncrementCounter(Int64 Adder)`

#### class `NSwarm.PerfTimer`  
`public class PerfTimer`  
_public; L74-144_
- L76 _public field_ `public Stack<PerfTiming> LastTimers`
- L77 _private* field_ `ReaderWriterDictionary<String, PerfTiming> Timings`
- L77 _private* field_ `ReaderWriterDictionary< Timings`
- L79-83 _public ctor_ `public PerfTimer()`
- L85-102 _public method_ `public void Start(String Name, bool Accum, Int64 Adder)`
- L104-112 _public method_ `public void Stop()`
- L114-143 _public method_ `public String DumpTimings()`

#### class `NSwarm.AgentConfiguration`  
`public class AgentConfiguration`  
_public; L151-174_
- L153-159 _public ctor_ `public AgentConfiguration()`
- L163 _public field_ `public Int32 AgentProcessID`
- L166 _public field_ `public String AgentCachePath`
- L169 _public field_ `public AgentGuid AgentJobGuid`
- L173 _public field_ `public bool IsPureLocalConnection`

#### class `NSwarm.IAgentInterfaceWrapper`  
`public class IAgentInterfaceWrapper`  
_public; L182-631_
- L184-189 _public ctor_ `public IAgentInterfaceWrapper()`
- L191-194 _public method_ `public void SignalConnectionDropped()`
- L199-251 _public method_ `public Int32 OpenConnection(Process AgentProcess, bool AgentProcessOwner, Int32 LocalProcessID, ELogFlags LoggingFlags, out AgentConfiguration NewConfiguration)`
- L255-273 _public method_ `public Int32 CloseConnection(Int32 ConnectionHandle)`
- L277-299 _public method_ `public Int32 SendMessage(Int32 ConnectionHandle, AgentMessage NewMessage)`
- L303-336 _public method_ `public Int32 GetMessage(Int32 ConnectionHandle, out AgentMessage NextMessage, Int32 Timeout)`
- L340-363 _public method_ `public Int32 AddChannel(Int32 ConnectionHandle, String FullPath, String ChannelName)`
- L367-389 _public method_ `public Int32 TestChannel(Int32 ConnectionHandle, String ChannelName)`
- L393-416 _public method_ `public Int32 OpenChannel(Int32 ConnectionHandle, String ChannelName, EChannelFlags ChannelFlags)`
- L420-442 _public method_ `public Int32 CloseChannel(Int32 ConnectionHandle, Int32 ChannelHandle)`
- L446-468 _public method_ `public Int32 OpenJob(Int32 ConnectionHandle, AgentGuid JobGuid )`
- L472-497 _public method_ `public Int32 BeginJobSpecification(Int32 ConnectionHandle, AgentJobSpecification Specification32, Hashtable Description32, AgentJobSpecification Specification64, Hashtable Description64)`
- L501-523 _public method_ `public Int32 AddTask(Int32 ConnectionHandle, List<AgentTaskSpecification> Specifications)`
- L527-545 _public method_ `public Int32 EndJobSpecification(Int32 ConnectionHandle)`
- L549-567 _public method_ `public Int32 CloseJob(Int32 ConnectionHandle)`
- L571-587 _public method_ `public Int32 Method(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L591-607 _public method_ `public Int32 Log(EVerbosityLevel Verbosity, ELogColour TextColour, String Line)`
- L612 _private* field_ `IAgentInterface Connection`
- L613 _private* field_ `ManualResetEvent ConnectionDroppedEvent`
- L616 _private* delegate_ `delegate Int32 OpenConnectionDelegate(Hashtable InParameters, ref Hashtable OutParameters)`
- L617 _private* delegate_ `delegate Int32 CloseConnectionDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L618 _private* delegate_ `delegate Int32 SendMessageDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L619 _private* delegate_ `delegate Int32 GetMessageDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L620 _private* delegate_ `delegate Int32 AddChannelDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L621 _private* delegate_ `delegate Int32 TestChannelDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L622 _private* delegate_ `delegate Int32 OpenChannelDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L623 _private* delegate_ `delegate Int32 CloseChannelDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L624 _private* delegate_ `delegate Int32 OpenJobDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L625 _private* delegate_ `delegate Int32 BeginJobSpecificationDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L626 _private* delegate_ `delegate Int32 AddTaskDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L627 _private* delegate_ `delegate Int32 EndJobSpecificationDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L628 _private* delegate_ `delegate Int32 CloseJobDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L629 _private* delegate_ `delegate Int32 MethodDelegate(Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters)`
- L630 _private* delegate_ `delegate Int32 LogDelegate(EVerbosityLevel Verbosity, ELogColour TextColour, String Line)`

#### struct `NSwarm.MessageThreadData`  
`public struct MessageThreadData`  
_public; L640-648_
- L642 _public field_ `public FSwarmInterface Owner`
- L643 _public field_ `public IAgentInterfaceWrapper Connection`
- L644 _public field_ `public Int32 ConnectionHandle`
- L645 _public field_ `public FConnectionCallback ConnectionCallback`
- L646 _public field_ `public IntPtr ConnectionCallbackData`
- L647 _public field_ `public AgentConfiguration ConnectionConfiguration`

#### class `NSwarm.FSwarmInterface`  
`public class FSwarmInterface`  
_public; L653-3253_
- L655-675 _private* ctor_ `FSwarmInterface()`
- L677 _private* delegate_ `delegate int SwarmOpenConnectionProc(FConnectionCallback CallbackFunc, IntPtr CallbackData, ELogFlags LoggingFlags, IntPtr OptionsFolder)`
- L678 _private* delegate_ `delegate int SwarmCloseConnectionProc()`
- L679 _private* delegate_ `delegate int SwarmSendMessageProc(IntPtr Message)`
- L680 _private* delegate_ `delegate int SwarmAddChannelProc(IntPtr FullPath, IntPtr ChannelName)`
- L681 _private* delegate_ `delegate int SwarmTestChannelProc(IntPtr ChannelName)`
- L682 _private* delegate_ `delegate int SwarmOpenChannelProc(IntPtr ChannelName, EChannelFlags ChannelFlags)`
- L683 _private* delegate_ `delegate int SwarmCloseChannelProc(int Channel)`
- L684 _private* delegate_ `delegate int SwarmWriteChannelProc(int Channel, IntPtr Data, int DataSize)`
- L685 _private* delegate_ `delegate int SwarmReadChannelProc(int Channel, IntPtr Data, int DataSize)`
- L686 _private* delegate_ `delegate int SwarmOpenJobProc(IntPtr JobGuid)`
- L687 _private* delegate_ `delegate int SwarmBeginJobSpecificationProc(IntPtr Specification32, IntPtr Specification64)`
- L688 _private* delegate_ `delegate int SwarmAddTaskProc(IntPtr Specification)`
- L689 _private* delegate_ `delegate int SwarmEndJobSpecificationProc()`
- L690 _private* delegate_ `delegate int SwarmCloseJobProc()`
- L691 _private* delegate_ `delegate int SwarmLogProc(EVerbosityLevel Verbosity, ELogColour TextColour, IntPtr Message)`
- L692 _private* delegate_ `delegate int SwarmInterfaceLogDelegate(EVerbosityLevel Verbosity, IntPtr Message)`
- L694 _private* field_ `static SwarmInterfaceLogDelegate SwarmInterfaceLogCppProc`
- L696 _private delegate_ `private delegate void RegisterSwarmOpenConnectionProc(SwarmOpenConnectionProc Proc)`
- L697 _private delegate_ `private delegate void RegisterSwarmCloseConnectionProc(SwarmCloseConnectionProc Proc)`
- L698 _private delegate_ `private delegate void RegisterSwarmSendMessageProc(SwarmSendMessageProc Proc)`
- L699 _private delegate_ `private delegate void RegisterSwarmAddChannelProc(SwarmAddChannelProc Proc)`
- L700 _private delegate_ `private delegate void RegisterSwarmTestChannelProc(SwarmTestChannelProc Proc)`
- L701 _private delegate_ `private delegate void RegisterSwarmOpenChannelProc(SwarmOpenChannelProc Proc)`
- L702 _private delegate_ `private delegate void RegisterSwarmCloseChannelProc(SwarmCloseChannelProc Proc)`
- L703 _private delegate_ `private delegate void RegisterSwarmWriteChannelProc(SwarmWriteChannelProc Proc)`
- L704 _private delegate_ `private delegate void RegisterSwarmReadChannelProc(SwarmReadChannelProc Proc)`
- L705 _private delegate_ `private delegate void RegisterSwarmOpenJobProc(SwarmOpenJobProc Proc)`
- L706 _private delegate_ `private delegate void RegisterSwarmBeginJobSpecificationProc(SwarmBeginJobSpecificationProc Proc)`
- L707 _private delegate_ `private delegate void RegisterSwarmAddTaskProc(SwarmAddTaskProc Proc)`
- L708 _private delegate_ `private delegate void RegisterSwarmEndJobSpecificationProc(SwarmEndJobSpecificationProc Proc)`
- L709 _private delegate_ `private delegate void RegisterSwarmCloseJobProc(SwarmCloseJobProc Proc)`
- L710 _private delegate_ `private delegate void RegisterSwarmLogProc(SwarmLogProc Proc)`
- L712-723 _private* method_ `static int SwarmOpenConnection(FConnectionCallback CallbackFunc, IntPtr CallbackData, ELogFlags LoggingFlags, IntPtr OptionsFolder)`
- L725-736 _private* method_ `static int SwarmCloseConnection()`
- L738-749 _private* method_ `static int SwarmSendMessage(IntPtr Message)`
- L751-762 _private* method_ `static int SwarmAddChannel(IntPtr FullPath, IntPtr ChannelName)`
- L764-775 _private* method_ `static int SwarmTestChannel(IntPtr ChannelName)`
- L777-788 _private* method_ `static int SwarmOpenChannel(IntPtr ChannelName, EChannelFlags ChannelFlags)`
- L790-801 _private* method_ `static int SwarmCloseChannel(int Channel)`
- L803-814 _private* method_ `static int SwarmWriteChannel(int Channel, IntPtr Data, int DataSize)`
- L816-827 _private* method_ `static int SwarmReadChannel(int Channel, IntPtr Data, int DataSize)`
- L829-840 _private* method_ `static int SwarmOpenJob(IntPtr JobGuid)`
- L842-875 _private* method_ `static FJobSpecification MarshalJobSpecification(IntPtr SpecificationPtr)`
- L877-888 _private* method_ `static int SwarmBeginJobSpecification(IntPtr Specification32, IntPtr Specification64)`
- L890-902 _private* method_ `static FTaskSpecification MarshalTaskSpecification(IntPtr SpecificationPtr)`
- L904-915 _private* method_ `static int SwarmAddTask(IntPtr Specification)`
- L917-928 _private* method_ `static int SwarmEndJobSpecification()`
- L930-941 _private* method_ `static int SwarmCloseJob()`
- L943-954 _private* method_ `static int SwarmLog(EVerbosityLevel Verbosity, ELogColour TextColour, IntPtr Message)`
- L956 _private* field_ `static FSwarmInterface GInstance = new FSwarmInterface()`
- L957 _private* field_ `static SwarmOpenConnectionProc OpenConnectionProc = new SwarmOpenConnectionProc(SwarmOpenConnection)`
- L958 _private* field_ `static SwarmCloseConnectionProc CloseConnectionProc = new SwarmCloseConnectionProc(SwarmCloseConnection)`
- L959 _private* field_ `static SwarmSendMessageProc SendMessageProc = new SwarmSendMessageProc(SwarmSendMessage)`
- L960 _private* field_ `static SwarmAddChannelProc AddChannelProc = new SwarmAddChannelProc(SwarmAddChannel)`
- L961 _private* field_ `static SwarmTestChannelProc TestChannelProc = new SwarmTestChannelProc(SwarmTestChannel)`
- L962 _private* field_ `static SwarmOpenChannelProc OpenChannelProc = new SwarmOpenChannelProc(SwarmOpenChannel)`
- L963 _private* field_ `static SwarmCloseChannelProc CloseChannelProc = new SwarmCloseChannelProc(SwarmCloseChannel)`
- L964 _private* field_ `static SwarmWriteChannelProc WriteChannelProc = new SwarmWriteChannelProc(SwarmWriteChannel)`
- L965 _private* field_ `static SwarmReadChannelProc ReadChannelProc = new SwarmReadChannelProc(SwarmReadChannel)`
- L966 _private* field_ `static SwarmOpenJobProc OpenJobProc = new SwarmOpenJobProc(SwarmOpenJob)`
- L967 _private* field_ `static SwarmBeginJobSpecificationProc BeginJobSpecificationProc = new SwarmBeginJobSpecificationProc(SwarmBeginJobSpecification)`
- L968 _private* field_ `static SwarmAddTaskProc AddTaskProc = new SwarmAddTaskProc(SwarmAddTask)`
- L969 _private* field_ `static SwarmEndJobSpecificationProc EndJobSpecificationProc = new SwarmEndJobSpecificationProc(SwarmEndJobSpecification)`
- L970 _private* field_ `static SwarmCloseJobProc CloseJobProc = new SwarmCloseJobProc(SwarmCloseJob)`
- L971 _private* field_ `static SwarmLogProc LogProc = new SwarmLogProc(SwarmLog)`
- L972 _private* field_ `static bool KillMonitorThread = false`
- L976 _private method_ `private static extern IntPtr LoadLibrary(string name)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]`
- L978 _private method_ `private static extern IntPtr GetProcAddress(IntPtr hModule, string name)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]`
- L981 _private method_ `private static extern IntPtr dlopen(string name, int flag)` — attrs: `[DllImport("dl", CharSet = CharSet.Auto, SetLastError = true)]`
- L983 _private method_ `private static extern IntPtr dlsym(int handle, string name)` — attrs: `[DllImport("dl", CharSet = CharSet.Ansi, SetLastError = true)]`
- L988-1195 _public method_ `public static int InitCppBridgeCallbacks(String SwarmInterfaceDllName)`
- L1204-1267 _public method_ `public virtual Int32 OpenConnection(FConnectionCallback CallbackFunc, IntPtr CallbackData, ELogFlags LoggingFlags, string OptionsFolder)`
- L1274-1325 _public method_ `public virtual Int32 CloseConnection()`
- L1334-1459 _public method_ `public virtual Int32 SendMessage(IntPtr NativeMessagePtr)`
- L1470-1497 _public method_ `public virtual Int32 AddChannel(String FullPath, String ChannelName)`
- L1506-1551 _public method_ `public virtual Int32 TestChannel(String ChannelName)`
- L1561-1712 _public method_ `public virtual Int32 OpenChannel(String ChannelName, EChannelFlags ChannelFlags)`
- L1721-1826 _public method_ `public virtual Int32 CloseChannel(Int32 Channel)`
- L1837-1931 _public method_ `public virtual Int32 WriteChannel(Int32 Channel, IntPtr Data, Int32 DataSize)`
- L1942-1998 _public method_ `public virtual Int32 ReadChannel(Int32 Channel, IntPtr Data, Int32 DataSize)`
- L2009-2045 _public method_ `public virtual Int32 OpenJob(FGuid JobGuid)`
- L2062-2160 _public method_ `public virtual Int32 BeginJobSpecification(FJobSpecification Specification32, FJobSpecification Specification64)`
- L2169-2219 _public method_ `public virtual Int32 AddTask(FTaskSpecification Specification)`
- L2228-2269 _public method_ `public virtual Int32 EndJobSpecification()`
- L2276-2321 _public method_ `public virtual Int32 CloseJob()`
- L2330-2341 _public method_ `public virtual Int32 Log(EVerbosityLevel Verbosity, ELogColour TextColour, String Message)`
- L2347-2580 _private* method_ `static void MessageThreadProc(Object ThreadParameters)`
- L2586-2642 _private* method_ `static void MonitorThreadProc(Object ThreadParameters)`
- L2647-2653 _private* method_ `void StartTiming(String Name, bool Accum, Int64 Adder)`
- L2655-2658 _private* method_ `void StartTiming(String Name, bool Accum)`
- L2663-2669 _private* method_ `void StopTiming()`
- L2674-2684 _private* method_ `void DumpTimings()`
- L2689-2746 _private* method_ `Int32 CleanupClosedConnection()`
- L2749 _private* field_ `Process AgentProcess`
- L2750 _private* field_ `bool AgentProcessOwner`
- L2753 _private* field_ `IAgentInterfaceWrapper Connection`
- L2754 _private* field_ `Int32 ConnectionHandle`
- L2755 _private* field_ `Thread ConnectionMessageThread`
- L2756 _private* field_ `Thread ConnectionMonitorThread`
- L2757 _private* field_ `FConnectionCallback ConnectionCallback`
- L2758 _private* field_ `IntPtr ConnectionCallbackData`
- L2759 _private* field_ `ELogFlags ConnectionLoggingFlags`
- L2760 _private* field_ `AgentConfiguration ConnectionConfiguration`
- L2761 _private* field_ `Object CleanupClosedConnectionLock`
- L2776 _private* field_ `ReaderWriterDictionary<Int32, ChannelInfo> OpenChannels`
- L2776 _private* field_ `ReaderWriterDictionary< OpenChannels`
- L2777 _private* field_ `Stack<byte[]> FreeChannelWriteBuffers`
- L2778 _private* field_ `Int32 BaseChannelHandle`
- L2781 _private* field_ `List<AgentTaskSpecification> PendingTasks`
- L2784 _private* field_ `String AgentCacheFolder`
- L2787 _private* field_ `TcpClientChannel NetworkChannel`
- L2790 _private* field_ `PerfTimer PerfTimerInstance`
- L2792-2868 _private* method_ `Int32 TryOpenConnection(FConnectionCallback CallbackFunc, IntPtr CallbackData, ELogFlags LoggingFlags)`
- L2870-2943 _private* method_ `void EnsureAgentIsRunning(string OptionsFolder)`
- L2952-2986 _private* method_ `AgentJobSpecification ConvertJobSpecification(ref FJobSpecification Specification, bool bIs64bit)`
- L2991-3024 _private* method_ `String GenerateFullChannelName(String ManagedChannelName, EChannelFlags ChannelFlags)`
- L3032-3077 _private* method_ `Int32 CacheFileAndConvertName(String FullPathName, out String CachedFileName, bool bUse64bitNamingConvention)`
- L3084-3168 _private* method_ `Int32 CacheAllFiles(AgentJobSpecification JobSpecification)`
- L3170-3213 _private* method_ `Int32 CacheAllFiles(AgentTaskSpecification TaskSpecification)`
- L3218-3239 _private* method_ `Int32 FlushChannel(ChannelInfo ChannelToFlush)`
- L3241-3251 _private method_ `private void EditorLog(EVerbosityLevel Verbosity, string Message)`

#### class `NSwarm.FSwarmInterface.ChannelInfo`  
`class ChannelInfo`  
_private*; L2764-2774_
- L2766 _public field_ `public String ChannelName`
- L2767 _public field_ `public EChannelFlags ChannelFlags`
- L2768 _public field_ `public Int32 ChannelHandle`
- L2769 _public field_ `public Stream ChannelFileStream`
- L2772 _public field_ `public byte[] ChannelData`
- L2773 _public field_ `public Int32 ChannelOffset`

#### Namespace-level symbols

- L635 _public delegate_ `public delegate void FConnectionCallback(IntPtr CallbackMessage, IntPtr CallbackData)`

### `Source/Editor/SwarmInterface/DotNET/Util.cs` (SwarmInterface)


#### class `NSwarm.FStringMarshaler`  
`public class FStringMarshaler`  
_public; L19-70_
- L21-37 _public method_ `public static IntPtr MarshalManagedToNative(String Str)`
- L39-63 _public method_ `public static String MarshalNativeToManaged(IntPtr NativeString)`
- L66 _private* const_ `const Int32 CHAR_SIZE = 4`
- L68 _private* const_ `const Int32 CHAR_SIZE = 2`

#### class `NSwarm.FGuid`  
`public class FGuid`  
_public; L76-127_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L81-87 _public ctor_ `public FGuid()`
- L92-98 _public ctor_ `public FGuid(UInt32 InA, UInt32 InB, UInt32 InC, UInt32 InD)`
- L103-109 _private* method_ `void Set(UInt32 InA, UInt32 InB, UInt32 InC, UInt32 InD)`
- L114-121 _public method_ `public bool Equals(FGuid Other)`
- L123 _public field_ `public UInt32 A`
- L124 _public field_ `public UInt32 B`
- L125 _public field_ `public UInt32 C`
- L126 _public field_ `public UInt32 D`

#### class `NSwarm.FMessage`  
`public class FMessage`  
_public; L139-177_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L144-148 _public ctor_ `public FMessage()`
- L155-159 _public ctor_ `public FMessage(EMessageType NewType)`
- L167-171 _public ctor_ `public FMessage(ESwarmVersionValue NewVersion, EMessageType NewType)`
- L174 _public field_ `public ESwarmVersionValue Version`
- L176 _public field_ `public EMessageType Type`

#### class `NSwarm.FInfoMessage`  
`public class FInfoMessage : FMessage`  
_public; L185-203_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- inherits: `FMessage`
- L187-190 _public ctor_ `public FInfoMessage() : base(ESwarmVersionValue.VER_1_0, EMessageType.INFO)`
- L195-199 _public ctor_ `public FInfoMessage(String InTextMessage) : base(ESwarmVersionValue.VER_1_0, EMessageType.INFO)`
- L202 _public field_ `public IntPtr TextMessage`

#### class `NSwarm.FAlertMessage`  
`public class FAlertMessage : FMessage`  
_public; L220-262_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- inherits: `FMessage`
- L222-225 _public ctor_ `public FAlertMessage() : base(ESwarmVersionValue.VER_1_0, EMessageType.ALERT)`
- L230-238 _public ctor_ `public FAlertMessage(FGuid InJobGuid, EAlertLevel InAlertLevel, FGuid InObjectGuid, int InTypeId) : base(ESwarmVersionValue.VER_1_0, EMessageType.ALERT)`
- L242-250 _public ctor_ `public FAlertMessage( FGuid InJobGuid, EAlertLevel InAlertLevel, FGuid InObjectGuid, int InTypeId, String InTextMessage ) : base(ESwarmVersionValue.VER_1_0, EMessageType.ALERT)`
- L253 _public field_ `public FGuid JobGuid`
- L255 _public field_ `public EAlertLevel AlertLevel`
- L257 _public field_ `public FGuid ObjectGuid`
- L259 _public field_ `public int TypeId`
- L261 _public field_ `public IntPtr TextMessage`

#### class `NSwarm.FTimingMessage`  
`public class FTimingMessage : FMessage`  
_public; L270-291_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- inherits: `FMessage`
- L272-275 _public ctor_ `public FTimingMessage() : base(ESwarmVersionValue.VER_1_0, EMessageType.TIMING)`
- L280-285 _public ctor_ `public FTimingMessage( EProgressionState NewState, int InThreadNum ) : base(ESwarmVersionValue.VER_1_0, EMessageType.TIMING)`
- L288 _public field_ `public EProgressionState State`
- L290 _public field_ `public int ThreadNum`

#### class `NSwarm.FTaskRequestResponse`  
`public class FTaskRequestResponse : FMessage`  
_public; L308-326_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- inherits: `FMessage`
- L310-313 _public ctor_ `public FTaskRequestResponse() : base(ESwarmVersionValue.VER_1_0, EMessageType.TASK_REQUEST_RESPONSE)`
- L318-322 _public ctor_ `public FTaskRequestResponse( ETaskRequestResponseType NewResponseType ) : base(ESwarmVersionValue.VER_1_0, EMessageType.TASK_REQUEST_RESPONSE)`
- L325 _private* field_ `ETaskRequestResponseType ResponseType`

#### class `NSwarm.FJobSpecification`  
`public class FJobSpecification`  
_public; L333-410_
- L338-350 _public ctor_ `public FJobSpecification()`
- L355-367 _public ctor_ `public FJobSpecification(String JobExecutableName, String JobParameters, EJobTaskFlags JobFlags)`
- L379-385 _private* method_ `void AddDependencies(String[] NewRequiredDependencies, UInt32 NewRequiredDependencyCount, String[] NewOptionalDependencies, UInt32 NewOptionalDependencyCount)`
- L387-392 _private* method_ `void AddDescription(String[] NewDescriptionKeys, String[] NewDescriptionValues, UInt32 NewDescriptionCount )`
- L395 _public field_ `public String ExecutableName`
- L396 _public field_ `public String Parameters`
- L399 _public field_ `public EJobTaskFlags Flags`
- L401 _public field_ `public String[] RequiredDependencies`
- L402 _public field_ `public UInt32 RequiredDependencyCount`
- L403 _public field_ `public String[] OptionalDependencies`
- L404 _public field_ `public UInt32 OptionalDependencyCount`
- L407 _public field_ `public String[] DescriptionKeys`
- L408 _public field_ `public String[] DescriptionValues`
- L409 _public field_ `public UInt32 DescriptionCount`

#### class `NSwarm.FJobSpecificationMarshalHelper`  
`class FJobSpecificationMarshalHelper`  
_internal*; L413-425_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- L415 _public field_ `public IntPtr ExecutableName`
- L416 _public field_ `public IntPtr Parameters`
- L417 _public field_ `public EJobTaskFlags Flags`
- L418 _public field_ `public IntPtr RequiredDependencies`
- L419 _public field_ `public UInt32 RequiredDependencyCount`
- L420 _public field_ `public IntPtr OptionalDependencies`
- L421 _public field_ `public UInt32 OptionalDependencyCount`
- L422 _public field_ `public IntPtr DescriptionKeys`
- L423 _public field_ `public IntPtr DescriptionValues`
- L424 _public field_ `public UInt32 DescriptionCount`

#### class `NSwarm.FTaskSpecification`  
`public class FTaskSpecification : FTaskRequestResponse`  
_public; L433-477_
- inherits: `FTaskRequestResponse`
- L438-446 _public ctor_ `public FTaskSpecification(FGuid TaskTaskGuid, String TaskParameters, EJobTaskFlags TaskFlags) : base(ETaskRequestResponseType.SPECIFICATION)`
- L456-460 _private* method_ `void AddDependencies(String[] NewDependencies, UInt32 NewDependencyCount )`
- L463 _public field_ `public FGuid TaskGuid`
- L466 _public field_ `public String Parameters`
- L469 _public field_ `public EJobTaskFlags Flags`
- L472 _public field_ `public UInt32 Cost`
- L475 _public field_ `public String[] Dependencies`
- L476 _public field_ `public UInt32 DependencyCount`

#### class `NSwarm.FTaskSpecificationMarshalHelper`  
`public class FTaskSpecificationMarshalHelper : FTaskRequestResponse`  
_public; L480-492_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- inherits: `FTaskRequestResponse`
- L482-485 _public ctor_ `public FTaskSpecificationMarshalHelper() : base(ETaskRequestResponseType.SPECIFICATION)`
- L486 _public field_ `public FGuid TaskGuid`
- L487 _public field_ `public IntPtr Parameters`
- L488 _public field_ `public EJobTaskFlags Flags`
- L489 _public field_ `public UInt32 Cost`
- L490 _public field_ `public IntPtr Dependencies`
- L491 _public field_ `public UInt32 DependencyCount`

#### class `NSwarm.FJobState`  
`public class FJobState : FMessage`  
_public; L501-531_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- inherits: `FMessage`
- L503-506 _public ctor_ `public FJobState() : base(ESwarmVersionValue.VER_1_0, EMessageType.JOB_STATE)`
- L511-519 _public ctor_ `public FJobState(FGuid NewJobGuid, EJobTaskState NewJobState) : base(ESwarmVersionValue.VER_1_0, EMessageType.JOB_STATE)`
- L522 _public field_ `public FGuid JobGuid`
- L525 _public field_ `public EJobTaskState JobState`
- L526 _public field_ `public IntPtr JobMessage`
- L529 _public field_ `public Int32 JobExitCode`
- L530 _public field_ `public double JobRunningTime`

#### class `NSwarm.FTaskState`  
`public class FTaskState : FMessage`  
_public; L540-570_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- inherits: `FMessage`
- L542-545 _public ctor_ `public FTaskState() : base(ESwarmVersionValue.VER_1_0, EMessageType.TASK_STATE)`
- L550-558 _public ctor_ `public FTaskState(FGuid NewTaskGuid, EJobTaskState NewTaskState) : base(ESwarmVersionValue.VER_1_0, EMessageType.TASK_STATE)`
- L561 _public field_ `public FGuid TaskGuid`
- L564 _public field_ `public EJobTaskState TaskState`
- L565 _public field_ `public IntPtr TaskMessage`
- L568 _public field_ `public Int32 TaskExitCode`
- L569 _public field_ `public double TaskRunningTime`

#### class `NSwarm.ReaderWriterDictionary`  
`public class ReaderWriterDictionary<TKey, TValue>`  
_public; L577-698_
- L582 _private* field_ `ReaderWriterLock AccessLock`
- L587 _private* field_ `Dictionary<TKey, TValue> ProtectedDictionary`
- L587 _private* field_ `Dictionary< ProtectedDictionary`
- L589-593 _public ctor_ `public ReaderWriterDictionary()`
- L598-610 _public method_ `public void Add(TKey Key, TValue Value)`
- L612-626 _public method_ `public bool Remove(TKey Key)`
- L628-640 _public method_ `public void Clear()`
- L642-656 _public method_ `public bool TryGetValue(TKey Key, out TValue Value)`
- L658-678 _public property_ `public Dictionary<TKey, TValue>.ValueCollection Values { get; set; }`
- L680-697 _public property_ `public Int32 Count { get; }`
