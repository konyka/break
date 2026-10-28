# CSharp / Agent

- project root: `Source/Programs/UnrealSwarm/Agent`
- files: 15; symbols: 793
- symbol kinds: class=47, const=3, ctor=26, delegate=16, enum=6, enumerator=31, field=321, indexer=1, interface=1, method=278, property=62, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealSwarm/Agent/Agent.cs` (Agent)


#### interface `Agent.IAgentInternalInterface`  
`public interface IAgentInternalInterface`  
_public; L30-99_
- L35 _public* method_ `bool Init( Int32 NewAgentProcessID )`
- L40 _public* method_ `void Destroy()`
- L46 _public* method_ `bool ShuttingDown()`
- L51 _public* method_ `bool Restarting()`
- L56 _public* method_ `void RequestShutdown()`
- L61 _public* method_ `void MaintainAgent()`
- L66 _public* method_ `void MaintainConnections()`
- L71 _public* method_ `void MaintainCache()`
- L76 _public* method_ `void MaintainJobs()`
- L81 _public* method_ `bool SendChannel( Int32 ConnectionHandle, string ChannelName, byte[] ChannelData, AgentGuid JobGuid )`
- L86 _public* method_ `bool RequestChannel( Int32 ConnectionHandle, string ChannelName, AgentGuid JobGuid )`
- L93 _public* method_ `bool ValidateChannel( Int32 ConnectionHandle, string ChannelName, byte[] RemoteChannelHashValue )`
- L98 _public* method_ `bool TestConnection( Int32 ConnectionHandle )`

#### struct `Agent.ChannelTransferData`  
`public struct ChannelTransferData`  
_public; L105-109_
- attrs: `[Serializable]`
- L107 _public field_ `public string ChannelName`
- L108 _public field_ `public byte[] ChannelData`

#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L116-451_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L123 _public field_ `public Int32 AgentProcessID = -1`
- L124 _public field_ `public Int32 OwnerProcessID = -1`
- L129 _public field_ `public X509Certificate Certificate = null`
- L135 _public field_ `public bool AgentIsShuttingDown = false`
- L136 _public field_ `public bool AgentHasShutDown = false`
- L141 _private field_ `private Thread ProcessMessageThread`
- L146 _private field_ `private ManualResetEvent Initialized = new ManualResetEvent( false )`
- L147 _private field_ `private DateTime InitializedTime`
- L152 _private field_ `private DateTime NextCleanUpCacheTime`
- L157 _private field_ `private Version CurrentVersion = Assembly.GetExecutingAssembly().GetName().Version`
- L226 _private* field_ `PerformanceStats LocalPerformanceStats = null`
- L227 _private* field_ `float CPUBusyThreshold = 20.0f`
- L231-240 _public method_ `public override Object InitializeLifetimeService()`
- L242-355 _public method_ `public bool Init( Int32 NewAgentProcessID )`
- L357-376 _public method_ `public void Destroy()`
- L378-435 _public method_ `public void MaintainAgent()`
- L439-443 _public method_ `public bool TestConnection( Int32 ConnectionHandle )`
- L448-450 _public ctor_ `public Agent()`

#### class `Agent.Agent.PerformanceStats`  
`private class PerformanceStats`  
_private; L162-225_
- L164-183 _public ctor_ `public PerformanceStats()`
- L185-210 _public method_ `public bool Update()`
- L212 _private field_ `private DateTime NextUpdateTime = DateTime.UtcNow + TimeSpan.FromSeconds(1)`
- L215 _private field_ `private PerformanceCounter CPUBusy = null`
- L216 _public field_ `public float LastCPUBusy = 100.0f`
- L218 _private const_ `private const int AverageCPUBusyValuesCount = 10`
- L219 _private field_ `private float[] AverageCPUBusyValues = new float[AverageCPUBusyValuesCount]`
- L220 _private field_ `private int AverageCPUBusyIndex`
- L221 _public field_ `public float AverageCPUBusyRaw`
- L222 _public field_ `public float AverageCPUBusy`

### `Source/Programs/UnrealSwarm/Agent/AgentApplication.cs` (Agent)


#### class `Agent.AgentApplication`  
`static partial class AgentApplication`  
_internal*; L23-297_
- L26 _private field_ `private static Agent LocalAgent = null`
- L29 _private field_ `private static DateTime NextUpdateCheckTime = DateTime.UtcNow`
- L35-51 _private* method_ `static bool CheckForUpdates()`
- L52-73 _private* method_ `static bool InstallAllUpdates()`
- L78-92 _private* method_ `static void ClearCache()`
- L98-296 _private* method_ `static void Main( string[] args )` — attrs: `[STAThread]`

### `Source/Programs/UnrealSwarm/Agent/Channels.cs` (Agent)


#### class `Agent.Channel`  
`public class Channel`  
_public; L23-81_
- L28 _private field_ `private string Private_Name = ""`
- L29-33 _public property_ `public string Name { get; set; }`
- L38 _private field_ `private EChannelFlags Private_Flags`
- L39-43 _public property_ `public EChannelFlags Flags { get; set; }`
- L48 _private field_ `private Int32 Private_Handle = Constants.INVALID`
- L49-53 _public property_ `public Int32 Handle { get; set; }`
- L58 _private field_ `private string Private_FullName = ""`
- L59-63 _public property_ `public string FullName { get; set; }`
- L70-75 _public ctor_ `public Channel( string ChannelName, string FullChannelName, EChannelFlags ChannelFlags )`
- L77-80 _public method_ `public void SetHandle( Int32 NewHandle )`

#### class `Agent.JobChannel`  
`public class JobChannel : Channel`  
_public; L85-107_
- inherits: `Channel`
- L90 _private field_ `private AgentGuid Private_JobGuid`
- L91-95 _public property_ `public AgentGuid JobGuid { get; set; }`
- L102-106 _public ctor_ `public JobChannel( AgentGuid NewJobGuid, string ChannelName, string FullChannelName, EChannelFlags ChannelFlags ) : base( ChannelName, FullChannelName, ChannelFlags )`

#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L114-1405_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L119 _private field_ `private ReaderWriterDictionary<string, byte[]> ChannelHashValues = ...`
- L119 _private field_ `private ReaderWriterDictionary< ChannelHashValues = new ReaderWriterDictionary<string, byte[]>()`
- L122 _private field_ `private SHA1Managed SHhash = new SHA1Managed()`
- L125 _private* field_ `bool CacheRelocationRequested = false`
- L126 _private* field_ `bool CacheClearRequested = false`
- L127 _private* field_ `bool CacheValidateRequested = false`
- L131-137 _private method_ `private byte[] ComputeHash( byte[] HashInput )`
- L139-201 _public method_ `public bool InitCache()`
- L203-281 _private method_ `private Int32 AddChannel_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L283-329 _private method_ `private Int32 TestChannel_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L333 _private field_ `private Object SetChannelHandleAndAddLock = new Object()`
- L334 _private field_ `private Random SetChannelHandleAndAddGenerator = new Random()`
- L335-353 _private method_ `private Int32 SetChannelHandleAndAdd( Connection ConnectionThatOwnsChannel, Channel NewChannel )`
- L355-684 _private method_ `private Int32 OpenChannel_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L686-781 _private method_ `private Int32 CloseChannel_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L787-878 _public method_ `public bool PushChannel(RemoteConnection Remote, string ChannelName, AgentGuid JobGuid)`
- L883-971 _public method_ `public bool SendChannel( Int32 ConnectionHandle, string ChannelName, byte[] ChannelData, AgentGuid JobGuid )`
- L983-1018 _public method_ `public bool PullChannel(RemoteConnection Remote, string ChannelName, AgentGuid JobGuid, int RetriesOnFailure = int.MaxValue)`
- L1023-1034 _public method_ `public bool RequestChannel( Int32 ConnectionHandle, string ChannelName, AgentGuid JobGuid )`
- L1041-1096 _public method_ `public bool ValidateChannel( Int32 ConnectionHandle, string ChannelName, byte[] RemoteChannelHashValue )`
- L1101-1127 _public method_ `public string GetCacheLocation()`
- L1129-1137 _public method_ `public void RequestCacheRelocation()`
- L1139-1149 _public method_ `public void RequestCacheClear()`
- L1151-1161 _public method_ `public void RequestCacheValidate()`
- L1163-1225 _public method_ `public void CacheAgingThreadProc()`
- L1227-1404 _public method_ `public void MaintainCache()`

### `Source/Programs/UnrealSwarm/Agent/Connections.cs` (Agent)


#### enum `Agent.ConnectionState`  
`public enum ConnectionState`  
_public; L31-37_
- L33 _public* enumerator_ `UNINITIALIZED`
- L34 _public* enumerator_ `CONNECTED`
- L35 _public* enumerator_ `DISCONNECTING`
- L36 _public* enumerator_ `DISCONNECTED`

#### class `Agent.Connection`  
`public class Connection`  
_public; L43-123_
- L48 _public field_ `public Int32 Handle = Constants.INVALID`
- L54 _public field_ `public ConnectionState CurrentState = ConnectionState.UNINITIALIZED`
- L61 _public field_ `public Connection Parent = null`
- L68 _public field_ `public UInt32 ChildrenSeen = 0`
- L69 _public field_ `public ReaderWriterDictionary<Int32, LocalConnection> LocalChildren = ...`
- L69 _public field_ `public ReaderWriterDictionary< LocalChildren = new ReaderWriterDictionary<Int32, LocalConnection>()`
- L70 _public field_ `public UInt32 LocalChildrenSeen = 0`
- L71 _public field_ `public ReaderWriterDictionary<Int32, RemoteConnection> RemoteChildren = ...`
- L71 _public field_ `public ReaderWriterDictionary< RemoteChildren = new ReaderWriterDictionary<Int32, RemoteConnection>()`
- L72 _public field_ `public UInt32 RemoteChildrenSeen = 0`
- L77 _public field_ `public ReaderWriterDictionary<Int32, Channel> OpenChannels = ...`
- L77 _public field_ `public ReaderWriterDictionary< OpenChannels = new ReaderWriterDictionary<Int32, Channel>()`
- L82 _public field_ `public Int32 CacheRequests = 0`
- L83 _public field_ `public Int32 CacheMisses = 0`
- L84 _public field_ `public Int32 CacheHits = 0`
- L89 _public field_ `public Int64 NetworkBytesSent = 0`
- L90 _public field_ `public Int64 NetworkBytesReceived = 0`
- L96 _public field_ `public AgentJob Job = null`
- L101 _public field_ `public ReaderWriterDictionary<AgentGuid, AgentTask> RunningTasks = ...`
- L101 _public field_ `public ReaderWriterDictionary< RunningTasks = new ReaderWriterDictionary<AgentGuid, AgentTask>()`
- L106 _public field_ `public UInt32 ReservationCount = 0`
- L111 _public field_ `public DateTime ConnectedTime = DateTime.UtcNow`
- L112 _public field_ `public DateTime DisconnectedTime`
- L119-122 _public ctor_ `public Connection( Int32 ConnectionHandle )`

#### class `Agent.LocalConnection`  
`public class LocalConnection : Connection`  
_public; L133-256_
- inherits: `Connection`
- L140 _private field_ `private Int32 Private_ProcessID = 0`
- L141-145 _public property_ `public Int32 ProcessID { get; set; }`
- L152 _private field_ `private Queue<AgentInfo> Private_PotentialRemoteAgents = new Queue<AgentInfo>()`
- L153-157 _public property_ `public Queue<AgentInfo> PotentialRemoteAgents { get; set; }`
- L158 _private field_ `private Queue<AgentInfo> Private_UnavailableRemoteAgents = new Queue<AgentInfo>()`
- L159-163 _public property_ `public Queue<AgentInfo> UnavailableRemoteAgents { get; set; }`
- L164 _public field_ `public bool RemoteAgentsAbandoned = false`
- L170 _private field_ `private Queue<AgentMessage> Private_MessageQueue = new Queue<AgentMessage>()`
- L171-175 _public property_ `public Queue<AgentMessage> MessageQueue { get; set; }`
- L180 _private field_ `private Semaphore Private_MessageAvailable = new Semaphore( 0, 10000 )`
- L181-185 _public property_ `public Semaphore MessageAvailable { get; set; }`
- L186 _private field_ `private ReaderWriterLockSlim OverflowCounterLock = new ReaderWriterLockSlim()`
- L187 _private field_ `private Int32 OverflowCounter = 0`
- L194-199 _public ctor_ `public LocalConnection( Int32 ConnectionHandle, Int32 ConnectionProcessID ) : base( ConnectionHandle )`
- L201-219 _public method_ `public void MessageAvailableSignal()`
- L221-255 _public method_ `public bool MessageAvailableWait( Int32 TimeOut )`

#### class `Agent.RemoteConnectionInterfaceWrapper`  
`public class RemoteConnectionInterfaceWrapper`  
_public; L266-731_
- L268-278 _public ctor_ `public RemoteConnectionInterfaceWrapper( Int32 NewRemoteAgentHandle, string NewRemoteAgentName, string NewRemoteAgentIPAddress, Agent NewRemoteInterface )`
- L280 _private* field_ `Object SignalConnectionDroppedLock = new Object()`
- L281-292 _public method_ `public void SignalConnectionDropped()`
- L294 _private* delegate_ `delegate bool TestConnectionDelegate( Int32 ConnectionHandle )`
- L296-303 _public method_ `public void BeginMonitoring()`
- L305-315 _public method_ `public void EndMonitoring()`
- L317-377 _private method_ `private void RemoteInterfaceMonitorThreadProc()`
- L379-383 _public method_ `public bool IsAlive()`
- L388 _private* delegate_ `delegate Int32 OpenRemoteConnectionDelegate( string RequestingAgentName, Int32 ConnectionHandle, ELogFlags LoggingFlags, bool IsAssigned, DateTime AssignedTimestamp )`
- L389-417 _public method_ `public Int32 OpenRemoteConnection( string RequestingAgentName, Int32 ConnectionHandle, ELogFlags LoggingFlags, bool IsAssigned, DateTime AssignedTimestamp )`
- L419 _private* delegate_ `delegate Int32 ConfirmRemoteConnectionDelegate( Int32 ConnectionHandle )`
- L420-447 _public method_ `public Int32 ConfirmRemoteConnection( Int32 ConnectionHandle )`
- L449 _private* delegate_ `delegate Int32 CloseConnectionDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L450-473 _public method_ `public Int32 CloseConnection( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L475 _private* delegate_ `delegate Int32 SendMessageDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L476-497 _public method_ `public Int32 SendMessage( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L499 _private* delegate_ `delegate bool SendChannelDelegate( Int32 ConnectionHandle, string ChannelName, byte[] ChannelData, AgentGuid JobGuid )`
- L500-521 _public method_ `public bool SendChannel( Int32 ConnectionHandle, string ChannelName, byte[] ChannelData, AgentGuid JobGuid )`
- L523 _private* delegate_ `delegate bool RequestChannelDelegate( Int32 ConnectionHandle, string ChannelName, AgentGuid JobGuid )`
- L524-551 _public method_ `public bool RequestChannel( Int32 ConnectionHandle, string ChannelName, AgentGuid JobGuid )`
- L553 _private* delegate_ `delegate bool ValidateChannelDelegate( Int32 ConnectionHandle, string ChannelName, byte[] ChannelHashValue )`
- L554-575 _public method_ `public bool ValidateChannel( Int32 ConnectionHandle, string ChannelName, byte[] ChannelHashValue )`
- L577 _private* delegate_ `delegate Int32 OpenJobDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L578-599 _public method_ `public Int32 OpenJob( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L601 _private* delegate_ `delegate Int32 BeginJobSpecificationDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L602-623 _public method_ `public Int32 BeginJobSpecification( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L625 _private* delegate_ `delegate Int32 AddTaskDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L626-647 _public method_ `public Int32 AddTask( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L649 _private* delegate_ `delegate Int32 EndJobSpecificationDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L650-671 _public method_ `public Int32 EndJobSpecification( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L673 _private* delegate_ `delegate Int32 CloseJobDelegate( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L674-695 _public method_ `public Int32 CloseJob( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L697-722 _private method_ `private void RetryCatch(Action TryClause, Action CatchClause, int RetriesOnFailure = 5)`
- L724 _public field_ `public string RemoteAgentName`
- L725 _public field_ `public string RemoteAgentIPAddress`
- L726 _private field_ `private Int32 RemoteAgentHandle`
- L727 _private field_ `private Agent RemoteInterface`
- L728 _private field_ `private ManualResetEvent RemoteInterfaceDropped`
- L729 _private field_ `private bool RemoteInterfaceAlive`
- L730 _private field_ `private Thread RemoteInterfaceMonitorThread`

#### class `Agent.RemoteConnection`  
`public class RemoteConnection : Connection`  
_public; L740-787_
- inherits: `Connection`
- L745 _private field_ `private AgentInfo Private_Info = null`
- L746-750 _public property_ `public AgentInfo Info { get; set; }`
- L755 _private field_ `private RemoteConnectionInterfaceWrapper Private_Interface = null`
- L756-760 _public property_ `public RemoteConnectionInterfaceWrapper Interface { get; set; }`
- L767 _private field_ `private List<Int32> Private_Aliases = new List<Int32>()`
- L768-772 _public property_ `public List<Int32> Aliases { get; set; }`
- L779-786 _public ctor_ `public RemoteConnection( Int32 ConnectionHandle, AgentInfo NewRemoteAgentInfo, RemoteConnectionInterfaceWrapper NewRemoteInterface ) : base( ConnectionHandle )`

#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L794-2549_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L799 _private field_ `private ISwarmCoordinator Coordinator`
- L800 _private field_ `private bool CoordinatorResponding`
- L801 _private field_ `private AgentState CurrentState = AgentState.Available`
- L802 _private field_ `private string WorkingFor = ""`
- L805 _private field_ `private static DateTime LastCoordinatorPingTime = DateTime.MinValue`
- L806 _private field_ `private static bool AgentIsRestarting = false`
- L809 _private field_ `private ReaderWriterDictionary<Int32, Connection> Connections = ...`
- L809 _private field_ `private ReaderWriterDictionary< Connections = new ReaderWriterDictionary<Int32, Connection>()`
- L810 _private field_ `private ManualResetEvent LocalConnectionRequestWaiting = new ManualResetEvent( false )`
- L812 _private field_ `private ReaderWriterDictionary<Int32, RemoteConnection> PendingConnections = ...`
- L812 _private field_ `private ReaderWriterDictionary< PendingConnections = new ReaderWriterDictionary<Int32, RemoteConnection>()`
- L814 _private* field_ `DateTime LastAssignedTime = DateTime.MinValue`
- L822-838 _public method_ `public void ValidateHostName(string HostName)` — Validates host name. Currently checks if the name contains only numeric characters Throws an exception if the name is invalid
- L843-885 _public method_ `public void InitCoordinator()`
- L892-895 _public method_ `public void SetCurrentDirectoryByProcessID (int ProcessID)`
- L901 _private field_ `private Object GetUniqueHandleLock = new Object()`
- L902 _private field_ `private Random GetUniqueHandleGenerator = new Random()`
- L903-952 _private method_ `private Int32 GetUniqueHandle()`
- L957-1141 _private method_ `private Int32 OpenConnection_1_0( Hashtable InParameters, ref Hashtable OutParameters )`
- L1150-1335 _public method_ `public Int32 OpenRemoteConnection( string RequestingAgentName, Int32 ConnectionHandle, ELogFlags LoggingFlags, bool IsAssigned, DateTime AssignedTimestamp )`
- L1340-1369 _public method_ `public Int32 ConfirmRemoteConnection( Int32 ConnectionHandle )`
- L1371-1400 _public method_ `public bool AgentNamePassesAllowedAgentsFilter( string RemoteAgentName )`
- L1407-1428 _private method_ `private bool PingRemoteHost( string RemoteHostName, string RemoteHostNameOrAddressToPing )`
- L1433-1551 _public method_ `public Int32 TryOpenRemoteConnection( LocalConnection ParentConnection, AgentInfo RemoteAgentInfo, bool IsAssigned, DateTime AssignedTimestamp, out RemoteConnection OpenedRemoteConnection )`
- L1556 _private field_ `private Object CloseConnectionLock = new Object()`
- L1557-1768 _public method_ `public Int32 CloseConnection_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L1773-1782 _public method_ `public bool RetryUnavailableRemoteAgent( LocalConnection ParentConnection )`
- L1787-1863 _public method_ `public bool ResetPotentialRemoteAgents( LocalConnection ParentConnection )`
- L1869-1902 _public method_ `public RemoteConnection GetNextRemoteAgent( LocalConnection ParentConnection )`
- L1904 _public field_ `public Object AbandonPotentialRemoteAgentsLock = new Object()`
- L1905-1927 _public method_ `public void AbandonPotentialRemoteAgents( LocalConnection ParentConnection )`
- L1929-2001 _private method_ `private void PrintSimpleAgentList( List<AgentInfo> AgentInfoList )`
- L2006-2026 _public method_ `public void PingRemoteAgents( string AgentGroupName )`
- L2028-2031 _public method_ `public void RestartAgentGroup( string AgentGroupName )`
- L2033-2096 _public method_ `public void RestartAgentGroupThreadProc( Object MethodData )`
- L2101-2235 _public method_ `public bool PingCoordinator( bool ForcePing )`
- L2237-2242 _public method_ `public void RequestShutdown()`
- L2244-2249 _public method_ `public void RequestRestart()`
- L2251-2263 _public method_ `public bool ShuttingDown()`
- L2265-2269 _public method_ `public bool Restarting()`
- L2271-2523 _public method_ `public void MaintainConnections()`
- L2525-2547 _private method_ `private string GetProcessPathById(int ProcessID)`

### `Source/Programs/UnrealSwarm/Agent/Display.Designer.cs` (Agent)


#### class `Agent.SwarmAgentWindow`  
`partial class SwarmAgentWindow`  
_internal*; L5-712_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-660 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L664 _private field_ `private System.Windows.Forms.TabControl AgentTabs`
- L665 _private field_ `private System.Windows.Forms.TabPage VisualiserTab`
- L666 _private field_ `private System.Windows.Forms.TabPage SettingsTab`
- L667 _private field_ `private System.Windows.Forms.TabPage LoggingTab`
- L668 _private field_ `private System.Windows.Forms.PropertyGrid SettingsPropertyGrid`
- L669 _private field_ `private System.Windows.Forms.MenuStrip AgentMenu`
- L670 _private field_ `private System.Windows.Forms.ToolStripMenuItem FileMenuItem`
- L671 _private field_ `private System.Windows.Forms.ToolStripMenuItem ExitMenuItem`
- L672 _private field_ `private System.Windows.Forms.ToolStripMenuItem HelpMenuItem`
- L673 _public field_ `public System.Windows.Forms.NotifyIcon SwarmAgentNotifyIcon`
- L674 _private field_ `private System.Windows.Forms.ContextMenuStrip TaskTrayContextMenu`
- L675 _private field_ `private System.Windows.Forms.ToolStripMenuItem ExitToolStripMenuItem`
- L676 _private field_ `private System.Windows.Forms.DataGridView VisualiserGridView`
- L677 _private field_ `private System.Windows.Forms.ToolStripMenuItem EditMenuItem`
- L678 _private field_ `private System.Windows.Forms.ToolStripMenuItem ClearMenuItem`
- L679 _public field_ `public UnrealControls.OutputWindowView LogOutputWindowView`
- L680 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Machine`
- L681 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Progress`
- L682 _private field_ `private System.Windows.Forms.GroupBox KeyGroupBox`
- L683 _private field_ `private System.Windows.Forms.Label ExportingBox`
- L684 _private field_ `private System.Windows.Forms.Label ExportingResultsBox`
- L685 _private field_ `private System.Windows.Forms.Label ProcessingBox`
- L686 _private field_ `private System.Windows.Forms.Label IrradianceCacheBox`
- L687 _private field_ `private System.Windows.Forms.Label EmitPhotonBox`
- L688 _private field_ `private System.Windows.Forms.Label ProcessingLabel`
- L689 _private field_ `private System.Windows.Forms.Label IrradianceCacheLabel`
- L690 _private field_ `private System.Windows.Forms.Label EmitPhotonsLabel`
- L691 _private field_ `private System.Windows.Forms.Label ExportingLabel`
- L692 _private field_ `private System.Windows.Forms.Label ExportingResultsLabel`
- L693 _private field_ `private System.Windows.Forms.GroupBox ProgressBarGroupBox`
- L694 _private field_ `private System.Windows.Forms.Label OverallProgressBar`
- L695 _private field_ `private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem`
- L696 _private field_ `private System.Windows.Forms.ToolStripMenuItem CacheMenuItem`
- L697 _private field_ `private System.Windows.Forms.ToolStripMenuItem CacheClearMenuItem`
- L698 _private field_ `private System.Windows.Forms.ToolStripMenuItem CacheValidateMenuItem`
- L699 _private field_ `private System.Windows.Forms.ToolStripMenuItem NetworkMenuItem`
- L700 _private field_ `private System.Windows.Forms.ToolStripMenuItem NetworkPingCoordinatorMenuItem`
- L701 _private field_ `private System.Windows.Forms.ToolStripMenuItem NetworkPingRemoteAgentsMenuItem`
- L702 _private field_ `private System.Windows.Forms.ToolTip BarToolTip`
- L703 _private field_ `private System.Windows.Forms.Label label1`
- L704 _private field_ `private System.Windows.Forms.Label StartingBox`
- L705 _private field_ `private System.Windows.Forms.Label ImportingLabel`
- L706 _private field_ `private System.Windows.Forms.Label ImportingBox`
- L707 _private field_ `private System.Windows.Forms.ToolStripMenuItem DeveloperMenuItem`
- L708 _private field_ `private System.Windows.Forms.ToolStripMenuItem DeveloperRestartQAAgentsMenuItem`
- L709 _private field_ `private System.Windows.Forms.ToolStripMenuItem DeveloperRestartWorkerAgentsMenuItem`
- L710 _private field_ `private System.Windows.Forms.TabPage DeveloperSettingsTab`
- L711 _private field_ `private System.Windows.Forms.PropertyGrid DeveloperSettingsPropertyGrid`

### `Source/Programs/UnrealSwarm/Agent/Display.cs` (Agent)


#### class `Agent.SwarmAgentWindow`  
`public partial class SwarmAgentWindow : Form`  
_public; L26-558_
- inherits: `Form`
- L54 _private field_ `private OutputWindowDocument MainLogDoc = new OutputWindowDocument()`
- L59 _private field_ `private Progressions ProgressionData = null`
- L64-92 _public ctor_ `public SwarmAgentWindow()`
- L94-97 _public method_ `public void SelectVisualizerTab()`
- L99-108 _public method_ `public void SaveOptions()`
- L110-114 _public method_ `public void Destroy()`
- L120 _private* delegate_ `delegate void DelegateLog( LogLine Line )`
- L122-158 _public method_ `public void Log (LogLine Line)`
- L160 _private* delegate_ `delegate void DelegateClearLog()`
- L161-174 _public method_ `public void ClearLog()`
- L179 _private* delegate_ `delegate void DelegateProcessProgressionEvent( ProgressionEvent Event )`
- L181-210 _public method_ `public void ProcessProgressionEvent( ProgressionEvent Event )`
- L212-223 _public method_ `public void Tick()`
- L225-227 _protected method_ `protected void XmlSerializer_UnknownAttribute( object sender, XmlAttributeEventArgs e )`
- L229-231 _protected method_ `protected void XmlSerializer_UnknownNode( object sender, XmlNodeEventArgs e )`
- L233-286 _private method_ `private T ReadOptions<T>( string OptionsFileName ) where T : new()`
- L288-339 _private method_ `private void WriteOptions<T>( T Data, string OptionsFileName )`
- L341-349 _private method_ `private void UpdateFonts()`
- L351-356 _private method_ `private void SaveWindowState()`
- L358-368 _private method_ `private void DeveloperMenuItemVisibilityChanged( Object Sender, EventArgs Args )`
- L370-402 _private method_ `private void UpdateWindowState()`
- L404-408 _private method_ `private void ClickExitMenu( object sender, EventArgs e )`
- L410-413 _private method_ `private void ShowSwarmAgentWindow( object sender, MouseEventArgs e )`
- L415-426 _private method_ `private void SwarmAgentWindowClosing( object sender, FormClosingEventArgs e )`
- L428-431 _private method_ `private void CancelButtonClick( object sender, EventArgs e )`
- L433-436 _private method_ `private void EditClearClick( object sender, EventArgs e )`
- L438-449 _private method_ `private void MenuAboutClick( object sender, EventArgs e )`
- L451-486 _private method_ `private void OptionsValueChanged( object s, PropertyValueChangedEventArgs e )`
- L488-491 _private method_ `private void CacheClearClick( object sender, EventArgs e )`
- L493-496 _private method_ `private void CacheValidateClick( object sender, EventArgs e )`
- L498-517 _private method_ `private void NetworkPingCoordinatorMenuItem_Click( object sender, EventArgs e )`
- L519-531 _private method_ `private void NetworkPingRemoteAgentsMenuItem_Click( object sender, EventArgs e )`
- L533-544 _private method_ `private void DeveloperRestartQAAgentsMenuItem_Click( object sender, EventArgs e )`
- L546-557 _private method_ `private void DeveloperRestartWorkerAgentsMenuItem_Click( object sender, EventArgs e )`

#### enum `Agent.SwarmAgentWindow.DialogFont`  
`public enum DialogFont`  
_public; L28-32_
- L30 _public* enumerator_ `Consolas`
- L31 _public* enumerator_ `Tahoma`

#### class `Agent.SwarmAgentWindow.LogLine`  
`public class LogLine`  
_public; L37-49_
- L39 _public field_ `public EVerbosityLevel Verbosity`
- L40 _public field_ `public ELogColour Colour`
- L41 _public field_ `public string Line`
- L43-48 _public ctor_ `public LogLine( EVerbosityLevel InVerbosity, ELogColour InColour, string InLine )`

#### class `Agent.AgentApplication`  
`static partial class AgentApplication`  
_internal*; L560-856_
- L564 _private method_ `private static extern bool SetForegroundWindow( IntPtr hWnd )` — attrs: `[DllImport( "user32.dll" )]`
- L572 _public field_ `public static SettableOptions Options = null`
- L573 _public field_ `public static SettableDeveloperOptions DeveloperOptions = null`
- L578 _private field_ `private static Thread ProcessGUIThread = null`
- L583 _private field_ `private static ReaderWriterQueue<SwarmAgentWindow.LogLine> LogLines = null`
- L588 _private field_ `private static ReaderWriterQueue<SwarmAgentWindow.ProgressionEvent> ProgressionEvents = null`
- L593 _private field_ `private static ManualResetEvent GUIInit = null`
- L598 _private field_ `private static bool Ticking = false`
- L603 _private field_ `private static bool CacheRelocationRequested = false`
- L608 _private field_ `private static bool CacheClearRequested = false`
- L613 _private field_ `private static bool CacheValidateRequested = false`
- L618 _public field_ `public static bool ShowWindow = false`
- L623 _public field_ `public static string OptionsFolder = ""`
- L628 _private field_ `private static SwarmAgentWindow MainWindow = null`
- L633 _private field_ `private static StreamWriter LogFile = null`
- L638 _private field_ `private static Object LogFileLock = new Object()`
- L640-673 _public method_ `public static void StartNewLogFile()`
- L675-685 _public method_ `public static void ClearLogWindow()`
- L687-708 _private method_ `private static void ProcessThreadQueues( TimeSpan MaximumExecutionTime )`
- L713-751 _private method_ `private static void ProcessGUIThreadProc()`
- L753-781 _public method_ `public static void Log( EVerbosityLevel Verbosity, ELogColour TextColour, string Line )`
- L783-786 _public method_ `public static void UpdateMachineState( string Machine, int ThreadNum, EProgressionState NewState )`
- L788-791 _public method_ `public static void RequestQuit()`
- L793-796 _public method_ `public static void RequestCacheRelocation()`
- L798-801 _public method_ `public static void RequestCacheClear()`
- L803-806 _public method_ `public static void RequestCacheValidation()`
- L808-811 _public method_ `public static bool RequestPingCoordinator()`
- L813-816 _public method_ `public static void RequestInitCoordinator()`
- L818-821 _public method_ `public static void RequestPingRemoteAgents()`
- L823-826 _public method_ `public static void RequestRestartQAAgents()`
- L828-831 _public method_ `public static void RequestRestartWorkerAgents()`
- L833-842 _private method_ `private static void ParseArgs(string[] args)`
- L844-855 _private method_ `private static void InitGUIThread()`

### `Source/Programs/UnrealSwarm/Agent/Interface.cs` (Agent)


#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L19-319_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L21-44 _public method_ `public Int32 OpenConnection( Hashtable InParameters, ref Hashtable OutParameters )`
- L46-63 _public method_ `public Int32 CloseConnection( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L65-86 _public method_ `public Int32 SendMessage( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L88-109 _public method_ `public Int32 GetMessage( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L111-133 _public method_ `public Int32 AddChannel( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L135-156 _public method_ `public Int32 TestChannel( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L158-180 _public method_ `public Int32 OpenChannel( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L182-203 _public method_ `public Int32 CloseChannel( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L205-226 _public method_ `public Int32 OpenJob( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L228-250 _public method_ `public Int32 BeginJobSpecification( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L252-274 _public method_ `public Int32 AddTask( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L276-293 _public method_ `public Int32 EndJobSpecification( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L295-312 _public method_ `public Int32 CloseJob( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L314-318 _public method_ `public Int32 Method( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`

### `Source/Programs/UnrealSwarm/Agent/Jobs.cs` (Agent)


#### class `Agent.AgentTask`  
`public class AgentTask`  
_public; L21-51_
- L23-28 _public ctor_ `public AgentTask( AgentTaskSpecification NewSpecification )`
- L30-38 _public method_ `public static Int32 CompareTasksByCostDescending(AgentTask A, AgentTask B)`
- L40-43 _public method_ `public static Int32 CompareTasksByAssignTime( AgentTask A, AgentTask B )`
- L45 _public field_ `public AgentTaskSpecification Specification`
- L46 _public field_ `public AgentTaskState CurrentState`
- L47 _public field_ `public Connection CurrentOwner`
- L48 _public field_ `public DateTime AssignTime`
- L49 _public field_ `public DateTime StartTime`
- L50 _public field_ `public DateTime StopTime`

#### class `Agent.AgentJob`  
`public class AgentJob`  
_public; L53-1846_
- L70-74 _public ctor_ `public AgentJob( Agent NewManager )`
- L76-102 _public method_ `public Int32 OpenJob( Connection NewOwner, AgentGuid NewJobGuid )`
- L104-146 _private method_ `private bool RequestDependency(Connection RequestingConnection, string Dependency, bool bIsRequired)`
- L148-177 _private method_ `private bool RequestJobFiles( Connection RequestingConnection, AgentJobSpecification JobSpecification )`
- L182 _public method_ `public static extern bool IsWow64Process([In] IntPtr hProcess, [Out] out bool lpSystemInfo)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CallingConvention = CallingConvention.Winapi)] [return: MarshalAs(UnmanagedType.Bool)]`
- L185-209 _public method_ `public bool Allow64bitJobs()`
- L211-264 _public method_ `public Int32 BeginJobSpecification( AgentJobSpecification NewJobSpecification32, Hashtable NewJobDescription32, AgentJobSpecification NewJobSpecification64, Hashtable NewJobDescription64 )`
- L266-280 _private method_ `private bool RequestTaskFiles( Connection RequestingConnection, AgentTaskSpecification TaskSpecification )`
- L282-323 _public method_ `public Int32 AddTask( AgentTaskSpecification NewTaskSpecification )`
- L325-360 _private method_ `private void SendJobCompletedMessage( AgentInfoMessage AdditionalInfoMessage )`
- L362-384 _public method_ `public void OutputReceivedDataEventHandler( Object Sender, DataReceivedEventArgs Line )`
- L386-408 _public method_ `public void ErrorReceivedDataEventHandler( Object Sender, DataReceivedEventArgs Line )`
- L410 _private field_ `private Object PostJobStatsToDBLock = new Object()`
- L411-488 _private method_ `private void PostJobStatsToDB()`
- L490-559 _public method_ `public void ExitedProcessEventHandler( Object Sender, EventArgs Args )`
- L561-752 _private method_ `private Int32 StartJobExecution()`
- L766-835 _private* method_ `static void OpenJobOnRemoteThreadProc( Object ObjectState )`
- L837-896 _private* method_ `static void OpenJobOnRemotesThreadProc( Object ObjectState )`
- L898-1040 _private method_ `private bool ValidateDeterministicDistributionRequirements()`
- L1042-1160 _public method_ `public Int32 EndJobSpecification()`
- L1162-1347 _public method_ `public Int32 CloseJob()`
- L1349-1358 _private method_ `private bool AvoidNextTask( Connection RequestingConection )`
- L1360-1460 _public method_ `public AgentTaskRequestResponse GetNextTask( Connection RequestingConnection )`
- L1462-1470 _public method_ `public void CancelReservations( Connection ReservationHolder )`
- L1472-1632 _public method_ `public void CheckForReservations()`
- L1634-1641 _private method_ `private void UpdateTaskStateAsSuccess( AgentTask RunningTask )`
- L1643-1650 _private method_ `private void UpdateTaskStateAsFailure( AgentTask RunningTask )`
- L1652-1678 _private method_ `private void UpdateTaskStateAsRequeued( AgentTask RunningTask )`
- L1680-1790 _public method_ `public void UpdateTaskState( AgentTaskState UpdatedTaskState )`
- L1793 _public field_ `public Agent Manager = null`
- L1794 _public field_ `public Connection Owner = null`
- L1795 _public field_ `public bool OwnerIsInstigator = false`
- L1796 _public field_ `public bool DeterministicModeEnabled = false`
- L1798 _public field_ `public AgentGuid JobGuid`
- L1799 _public field_ `public AgentJobSpecification Specification32 = null`
- L1800 _public field_ `public AgentJobSpecification Specification64 = null`
- L1801 _public field_ `public AgentJobSpecification Specification = null`
- L1804 _public field_ `public UInt32 TaskCount = 0`
- L1805 _public field_ `public UInt32 TaskCountRemote = 0`
- L1806 _public field_ `public UInt32 TaskCountRequeue = 0`
- L1807 _public field_ `public UInt32 TaskSuccessCount = 0`
- L1808 _public field_ `public UInt32 TaskFailureCount = 0`
- L1809 _public field_ `public UInt32 TaskReservationCount = 0`
- L1810 _public field_ `public ReaderWriterStack<AgentTask> PendingTasks = new ReaderWriterStack<AgentTask>()`
- L1811 _public field_ `public ReaderWriterDictionary<AgentGuid, AgentTask> RunningTasks = ...`
- L1811 _public field_ `public ReaderWriterDictionary< RunningTasks = new ReaderWriterDictionary<AgentGuid, AgentTask>()`
- L1812 _public field_ `public ReaderWriterQueue<AgentTask> RetiredTasks = new ReaderWriterQueue<AgentTask>()`
- L1815 _public field_ `public JobState CurrentState = JobState.AGENT_JOB_UNSPECIFIED`
- L1816 _public field_ `public Object CurrentStateLock = new Object()`
- L1817 _public field_ `public JobSuccessState CurrentSuccessState = JobSuccessState.AGENT_JOB_INCOMPLETE`
- L1818 _public field_ `public Object CurrentSuccessStateLock = new Object()`
- L1820 _public field_ `public Process ProcessObject = null`
- L1821 _public field_ `public Object ProcessObjectLock = new Object()`
- L1822 _public field_ `public Int32 ProcessObjectOutputLines = 0`
- L1824 _public field_ `public Int32 ProcessObjectExitCode = 0`
- L1825 _public field_ `public Int64 ProcessObjectPeakVirtualMemorySize64 = 0`
- L1826 _public field_ `public Int64 ProcessObjectPeakWorkingSet64 = 0`
- L1829 _public field_ `public Int32 CacheRequests = 0`
- L1830 _public field_ `public Int32 CacheMisses = 0`
- L1831 _public field_ `public Int32 CacheHits = 0`
- L1834 _public field_ `public Int64 NetworkBytesSent = 0`
- L1835 _public field_ `public Int64 NetworkBytesReceived = 0`
- L1838 _public field_ `public Hashtable Description32 = null`
- L1839 _public field_ `public Hashtable Description64 = null`
- L1840 _public field_ `public Hashtable Description = null`
- L1842 _public field_ `public bool JobStatsPostedToDB = false`
- L1844 _public field_ `public DateTime StartTime`
- L1845 _public field_ `public DateTime StopTime`

#### enum `Agent.AgentJob.JobState`  
`public enum JobState`  
_public; L55-61_
- L57 _public* enumerator_ `AGENT_JOB_UNSPECIFIED`
- L58 _public* enumerator_ `AGENT_JOB_PENDING`
- L59 _public* enumerator_ `AGENT_JOB_RUNNING`
- L60 _public* enumerator_ `AGENT_JOB_CLOSED`

#### enum `Agent.AgentJob.JobSuccessState`  
`public enum JobSuccessState`  
_public; L63-68_
- L65 _public* enumerator_ `AGENT_JOB_INCOMPLETE`
- L66 _public* enumerator_ `AGENT_JOB_SUCCESS`
- L67 _public* enumerator_ `AGENT_JOB_FAILURE`

#### class `Agent.AgentJob.OpenJobOnRemoteData`  
`public class OpenJobOnRemoteData`  
_public; L754-764_
- L756-760 _public ctor_ `public OpenJobOnRemoteData( AgentJob NewJob, RemoteConnection NewRemote )`
- L762 _public field_ `public AgentJob Job`
- L763 _public field_ `public RemoteConnection Remote`

#### class `Agent.AgentJobRecord`  
`public class AgentJobRecord`  
_public; L1854-1872_
- L1856-1864 _public ctor_ `public AgentJobRecord()`
- L1866 _public field_ `public AgentJobSpecification Specification`
- L1867 _public field_ `public List<string> WorkerAgentNames`
- L1868 _public field_ `public List<string> WorkerAgentIPAddresses`
- L1869 _public field_ `public ReaderWriterDictionary<AgentGuid, AgentTask> AllTasks`
- L1869 _public field_ `public ReaderWriterDictionary< AllTasks`
- L1870 _public field_ `public ReaderWriterDictionary<string, Queue<AgentTask>> AgentToGoldenTaskQueueMapping`
- L1870 _public field_ `public ReaderWriterDictionary< AgentToGoldenTaskQueueMapping`
- L1871 _public field_ `public ReaderWriterDictionary<string, Queue<AgentTask>> AgentToTaskQueueMapping`
- L1871 _public field_ `public ReaderWriterDictionary< AgentToTaskQueueMapping`

#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L1879-2260_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L1884 _public field_ `public ReaderWriterDictionary<AgentGuid, AgentJob> ActiveJobs = ...`
- L1884 _public field_ `public ReaderWriterDictionary< ActiveJobs = new ReaderWriterDictionary<AgentGuid, AgentJob>()`
- L1885 _public field_ `public AgentJobRecord LastSuccessfulJobRecord = null`
- L1888 _public field_ `public AgentGuid DebuggingJobGuid = new AgentGuid( 0x00000123, 0x00004567, 0x000089ab, 0x0000cdef )`
- L1892-1968 _private method_ `private Int32 OpenJob_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L1970-2005 _private method_ `private Int32 BeginJobSpecification_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L2007-2056 _private method_ `private Int32 AddTask_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L2058-2078 _private method_ `private Int32 EndJobSpecification_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L2080-2100 _private method_ `private Int32 CloseJob_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L2102-2126 _public method_ `public Int32 GetActiveJobGuid( Int32 ConnectionHandle, ref AgentGuid ActiveJobGuid )`
- L2128-2259 _public method_ `public void MaintainJobs()`

### `Source/Programs/UnrealSwarm/Agent/Messaging.cs` (Agent)


#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L19-764_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L28 _private field_ `private Queue<AgentMessage> MessageQueueSM = new Queue<AgentMessage>()`
- L29 _private field_ `private Queue<AgentMessage> MessageQueuePM = new Queue<AgentMessage>()`
- L30 _private field_ `private AutoResetEvent MessageQueueReady = new AutoResetEvent( false )`
- L31 _private field_ `private Object MessageQueueLock = new Object()`
- L37 _private* field_ `ReaderWriterLock SendMessageLock = new ReaderWriterLock()`
- L58-92 _private method_ `private Int32 SendMessage_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`
- L97-276 _public method_ `public Int32 SendMessageInternal( Connection Sender, AgentMessage NewMessage )`
- L281-296 _public method_ `public string MachineNameFromConnection( Connection RequestingConnection )`
- L301-316 _public method_ `public string MachineIPAddressFromConnection( Connection RequestingConnection )`
- L323-360 _public method_ `public bool FlushMessageQueue( Connection RequestingConnection, bool WithDisconnect )`
- L366-659 _private method_ `private void ProcessMessagesThreadProc()`
- L664-763 _private method_ `private Int32 GetMessage_1_0( Int32 ConnectionHandle, Hashtable InParameters, ref Hashtable OutParameters )`

#### class `Agent.Agent.DisconnectionSignalMessage`  
`private class DisconnectionSignalMessage : AgentSignalMessage`  
_private; L41-49_
- inherits: `AgentSignalMessage`
- L43-46 _public ctor_ `public DisconnectionSignalMessage( Connection InConnectionToDisconnect )`
- L48 _public field_ `public Connection ConnectionToDisconnect`

### `Source/Programs/UnrealSwarm/Agent/Progression.cs` (Agent)


#### class `Agent.SwarmAgentWindow`  
`public partial class SwarmAgentWindow : Form`  
_public; L17-835_
- inherits: `Form`
- L36 _private field_ `private static Dictionary<string, BarColour> BarColours = ...`
- L36 _private field_ `private static Dictionary< BarColours = null`
- L37 _private field_ `private static Dictionary<string, string> BarNames = ...`
- L37 _private field_ `private static Dictionary< BarNames = null`
- L39-84 _public method_ `public static void CreateBarColours( SwarmAgentWindow Owner )`
- L500 _private field_ `private bool VisualiserGridViewResized = false`
- L505-521 _private method_ `private int CalculateIdealBarHeight( int NumMachines )`
- L523-574 _private method_ `private static int CompareByStateAndTime( KeyValuePair<string, Progression> A, KeyValuePair<string, Progression> B )`
- L579-665 _public method_ `public void PopulateGridView()`
- L670 _private const_ `private const int TickBorder = 4`
- L672-696 _private method_ `private void DrawScale( DateTime StartTime, float ZoomLevel, Graphics Gfx, Rectangle Bounds )`
- L701-744 _private method_ `private void ProgressCellPaint( object sender, DataGridViewCellPaintingEventArgs e )`
- L746-761 _private method_ `private void MouseWheelHandler( object sender, MouseEventArgs e )`
- L763-804 _private method_ `private void MouseMoveHandler(object sender, MouseEventArgs e)`
- L806-809 _private method_ `private void MouseLeaveHandler(object sender, EventArgs e)`
- L811-814 _private method_ `private void GridViewSelectionChanged( object sender, EventArgs e )`
- L816-819 _private method_ `private void GridViewResized( object sender, EventArgs e )`
- L821-834 _private method_ `private void OverallProgressBarPaint( object sender, PaintEventArgs e )`

#### class `Agent.SwarmAgentWindow.BarColour`  
`class BarColour`  
_private*; L19-34_
- L21 _public field_ `public Color Colour`
- L22 _public field_ `public Color BorderColour`
- L23 _public field_ `public Pen Border`
- L24 _public field_ `public SolidBrush FillBrush`
- L26-33 _public ctor_ `public BarColour( Color InColour )`

#### class `Agent.SwarmAgentWindow.ProgressionEvent`  
`public class ProgressionEvent`  
_public; L86-99_
- L88 _public field_ `public string Machine = null`
- L89 _public field_ `public int ThreadNum = 0`
- L90 _public field_ `public EProgressionState State = EProgressionState.Idle`
- L91 _public field_ `public DateTime Time = DateTime.UtcNow`
- L93-98 _public ctor_ `public ProgressionEvent( string InMachine, int InThreadNum, EProgressionState NewState )`

#### class `Agent.SwarmAgentWindow.ProgressionThreadSample`  
`public class ProgressionThreadSample`  
_public; L101-123_
- L103 _public field_ `public EProgressionState State = EProgressionState.Idle`
- L104 _public field_ `public DateTime StartTime = DateTime.UtcNow`
- L105 _public field_ `public DateTime EndTime = DateTime.UtcNow`
- L106 _public field_ `public int NumTimestamps = 0`
- L108-112 _public ctor_ `public ProgressionThreadSample(EProgressionState NewState)`
- L114-122 _public method_ `public void AddTimestamp( DateTime EventTime )`

#### class `Agent.SwarmAgentWindow.ProgressionSample`  
`public class ProgressionSample`  
_public; L125-157_
- L127 _public field_ `public EProgressionState State = EProgressionState.Idle`
- L128 _public field_ `public DateTime StartTime = DateTime.UtcNow`
- L129 _public field_ `public DateTime EndTime = DateTime.UtcNow`
- L130 _public field_ `public List<ProgressionThreadSample> ThreadSamples = null`
- L131 _public field_ `public Rectangle Bounds`
- L132 _public field_ `public double Duration`
- L133 _public field_ `public int NumTimestamps = 0`
- L135-137 _public ctor_ `public ProgressionSample()`
- L139-146 _public ctor_ `public ProgressionSample( EProgressionState NewState, DateTime EventTime )`
- L148-156 _public method_ `public void AddTimestamp( DateTime EventTime )`

#### class `Agent.SwarmAgentWindow.Progression`  
`public class Progression`  
_public; L159-298_
- L164 _public field_ `public List<ProgressionSample> ProgressionSamples = new List<ProgressionSample>()`
- L166 _private const_ `private const int BarBorder = 4`
- L169 _public field_ `public int ProgressTotalWidth = 0`
- L171-175 _public ctor_ `public Progression()`
- L177-187 _public method_ `public void DrawBackground( Graphics Gfx, Rectangle Bounds )`
- L189-197 _private method_ `private void DrawFilledBar( Graphics Gfx, EProgressionState State, int Left, int Top, int Width, int Height )`
- L199-297 _public method_ `public int Draw( DateTime Start, float ZoomLevel, Graphics Gfx, Rectangle Bounds )`

#### class `Agent.SwarmAgentWindow.Progressions`  
`public class Progressions`  
_public; L300-498_
- L305 _public field_ `public int NumTasks = 0`
- L306 _public field_ `public int NumRetiredTasks = 0`
- L307 _public field_ `public int NumRunningTasks = 0`
- L312 _public field_ `public DateTime StartTime = DateTime.UtcNow`
- L319 _public field_ `public ReaderWriterDictionary<string, Progression> MachineProgressions = ...`
- L319 _public field_ `public ReaderWriterDictionary< MachineProgressions = new ReaderWriterDictionary<string, Progression>()`
- L321-350 _public method_ `public void DrawOverallProgressBar( Graphics Gfx, Rectangle Bounds )`
- L355-476 _public method_ `public bool ProcessEvent( ProgressionEvent Event )`
- L481-497 _public method_ `public bool Tick()`

### `Source/Programs/UnrealSwarm/Agent/Properties/AssemblyInfo.cs` (Agent)
_(no declarations)_


### `Source/Programs/UnrealSwarm/Agent/Properties/Resources.Designer.cs` (Agent)


#### class `Agent.Properties.Resources`  
`internal class Resources`  
_internal; L27-64_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L29 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L31 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L34-35 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L41-49 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L56-63 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/UnrealSwarm/Agent/Properties/Settings.Designer.cs` (Agent)


#### class `Agent.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L18-54_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "10.0.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L20 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L22-26 _public property_ `public static Settings Default { get; }`
- L31-35 _public property_ `public int CoordinatorRemotingPort { get; }` — attrs: `[global::System.Configuration.ApplicationScopedSettingAttribute()] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Configuration.DefaultSettingValueAttribute("8009")]`
- L40-44 _public property_ `public int AgentRemotingPort { get; }` — attrs: `[global::System.Configuration.ApplicationScopedSettingAttribute()] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Configuration.DefaultSettingValueAttribute("8008")]`
- L49-53 _public property_ `public string StatsDatabaseName { get; }` — attrs: `[global::System.Configuration.ApplicationScopedSettingAttribute()] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Configuration.DefaultSettingValueAttribute("engine-db")]`

### `Source/Programs/UnrealSwarm/Agent/SettableOptions.cs` (Agent)


#### enum `Agent.EOptionsVersion`  
`public enum EOptionsVersion`  
_public; L22-39_
- L24 _public* enumerator_ `OriginalVersion = 3`
- L25 _public* enumerator_ `NewBarColors = 4`
- L26 _public* enumerator_ `CacheManagement = 5`
- L27 _public* enumerator_ `NewStartupColor = 6`
- L28 _public* enumerator_ `AdjustedProgressionColors = 7`
- L29 _public* enumerator_ `TweaksToTheNumberOfThreads = 8`
- L30 _public* enumerator_ `FixTheOptionsReset = 9`
- L31 _public* enumerator_ `DeployNewFarmMachineNames = 10`
- L32 _public* enumerator_ `BumpTheJobsToKeepCount = 11`
- L33 _public* enumerator_ `MoveTheDefaultCacheFolder = 12`
- L34 _public* enumerator_ `ChangeCoordinatorLocation = 13`
- L35 _public* enumerator_ `AddPerformanceMonitoringDisable = 14`
- L36 _public* enumerator_ `MakeLocalJobsProcessorsCountLimited = 15`
- L38 _public* enumerator_ `Current = MakeLocalJobsProcessorsCountLimited`

#### class `Agent.EnumedCollectionPropertyDescriptor`  
`public class EnumedCollectionPropertyDescriptor<E, T> : PropertyDescriptor`  
_public; L41-111_
- inherits: `PropertyDescriptor`
- L43 _private field_ `private EnumedCollection<E, T> Collection = ...`
- L43 _private field_ `private EnumedCollection< Collection = null`
- L44 _private field_ `private int Index = -1`
- L46-51 _public ctor_ `public EnumedCollectionPropertyDescriptor( EnumedCollection<E, T> InCollection, int InIndex ) : base( "#" + InIndex.ToString(), null )`
- L53-56 _public property_ `public override AttributeCollection Attributes { get; }`
- L58-61 _public method_ `public override bool CanResetValue( object component )`
- L63-66 _public property_ `public override Type ComponentType { get; }`
- L68-71 _public property_ `public override string Description { get; }`
- L73-76 _public property_ `public override string DisplayName { get; }`
- L78-81 _public method_ `public override object GetValue( object component )`
- L83-86 _public property_ `public override bool IsReadOnly { get; }`
- L88-91 _public property_ `public override string Name { get; }`
- L93-96 _public property_ `public override Type PropertyType { get; }`
- L98-100 _public method_ `public override void ResetValue( object component )`
- L102-105 _public method_ `public override bool ShouldSerializeValue( object component )`
- L107-110 _public method_ `public override void SetValue( object component, object value )`

#### class `Agent.EnumedCollection`  
`public class EnumedCollection<E, T> : CollectionBase, ICustomTypeDescriptor`  
_public; L113-199_
- inherits: `CollectionBase, ICustomTypeDescriptor`
- L115-118 _public method_ `public void Add( T BarColour )`
- L120-123 _public method_ `public void Remove( T BarColour )`
- L125-129 _public indexer_ `public T this[int Index] { get; set; }`
- L132-135 _public method_ `public String GetClassName()`
- L137-140 _public method_ `public AttributeCollection GetAttributes()`
- L142-145 _public method_ `public String GetComponentName()`
- L147-150 _public method_ `public TypeConverter GetConverter()`
- L152-155 _public method_ `public EventDescriptor GetDefaultEvent()`
- L157-160 _public method_ `public PropertyDescriptor GetDefaultProperty()`
- L162-165 _public method_ `public object GetEditor( Type editorBaseType )`
- L167-170 _public method_ `public EventDescriptorCollection GetEvents( Attribute[] attributes )`
- L172-175 _public method_ `public EventDescriptorCollection GetEvents()`
- L177-180 _public method_ `public object GetPropertyOwner( PropertyDescriptor pd )`
- L182-185 _public method_ `public PropertyDescriptorCollection GetProperties( Attribute[] attributes )`
- L187-198 _public method_ `public PropertyDescriptorCollection GetProperties()`

#### class `Agent.EnumedCollectionConverter`  
`internal class EnumedCollectionConverter : ExpandableObjectConverter`  
_internal; L201-212_
- inherits: `ExpandableObjectConverter`
- L203-211 _public method_ `public override object ConvertTo( ITypeDescriptorContext Context, System.Globalization.CultureInfo Culture, object Value, Type DestType )`

#### class `Agent.SuppressCollectionEditor`  
`public class SuppressCollectionEditor : UITypeEditor`  
_public; L214-220_
- inherits: `UITypeEditor`
- L216-219 _public method_ `public override UITypeEditorEditStyle GetEditStyle( ITypeDescriptorContext context )`

#### class `Agent.SerialisableColour`  
`public class SerialisableColour`  
_public; L222-243_
- L224-227 _public ctor_ `public SerialisableColour()`
- L229-232 _public ctor_ `public SerialisableColour( Color InColour )`
- L235-239 _public property_ `public Color Colour { get; set; }` — attrs: `[XmlIgnore]`
- L242 _public field_ `public int LocalColour = 0` — attrs: `[XmlAttribute]`

#### class `Agent.SettableOptions`  
`public class SettableOptions`  
_public; L245-591_
- L250-254 _public property_ `public EVerbosityLevel Verbosity { get; set; }` — attrs: `[CategoryAttribute( "Log Settings" )] [DescriptionAttribute( "The amount of text spewed to the window." )] [DefaultValueAttribute( EVerbosityLevel.Informative )]`
- L256 _private field_ `private EVerbosityLevel LocalVerbosity = EVerbosityLevel.Informative` — attrs: `[XmlEnumAttribute]`
- L261-265 _public property_ `public SwarmAgentWindow.DialogFont TextFont { get; set; }` — attrs: `[CategoryAttribute( "Log Settings" )] [DescriptionAttribute( "The font used in all Swarm Agent dialogs." )] [DefaultValueAttribute( SwarmAgentWindow.DialogFont.Tahoma )]`
- L267 _private field_ `private SwarmAgentWindow.DialogFont LocalTextFont = SwarmAgentWindow.DialogFont.Tahoma` — attrs: `[XmlAttribute]`
- L272-276 _public property_ `public bool AvoidLocalExecution { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "Whether to allow only distribution of jobs and tasks from this agent (no local execution)." )] [DefaultValueAttribute( false )]`
- L278 _private field_ `private bool LocalAvoidLocalExecution = false` — attrs: `[XmlAttribute]`
- L283-287 _public property_ `public bool EnableStandaloneMode { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "Enables Standalone mode, which disables the distribution system for both outgoing and incoming tasks." )] [DefaultValueAttribute( false )]`
- L289 _private field_ `private bool LocalEnableStandaloneMode = false` — attrs: `[XmlAttribute]`
- L294-298 _public property_ `public string AllowedRemoteAgentNames { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "[Advanced] The remote machine filter string (' ', ',' or ';' delimited)." )] [DefaultValueAttribute( "RENDER*" )]`
- L300 _private field_ `private string LocalAllowedRemoteAgentNames = "RENDER*"` — attrs: `[XmlTextAttribute]`
- L305-309 _public property_ `public string AllowedRemoteAgentGroup { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "[Advanced] The name of the agent group jobs can be distributed to." )] [DefaultValueAttribute( "DefaultDeployed" )]`
- L311 _private field_ `private string LocalAllowedRemoteAgentGroup = "DefaultDeployed"` — attrs: `[XmlTextAttribute]`
- L316-320 _public property_ `public string AgentGroupName { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "[Advanced] The name of the agent group to which this machine belongs." )] [DefaultValueAttribute( "Default" )]`
- L323 _private field_ `private string LocalAgentGroupName = ( ApplicationDeployment.IsNetworkDeployed ? "DefaultDeployed" : "Default" )` — attrs: `[XmlTextAttribute]`
- L325 _private field_ `private string LocalAgentGroupName = "Default"`
- L331-335 _public property_ `public string CoordinatorRemotingHost { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "[Advanced] The name of the machine hosting the Coordinator." )] [DefaultValueAttribute( "RENDER-01" )]`
- L337 _private field_ `private string LocalCoordinatorRemotingHost = "RENDER-01"` — attrs: `[XmlTextAttribute]`
- L342-346 _public property_ `public string CacheFolder { get; set; }` — attrs: `[CategoryAttribute( "Cache Settings" )] [DescriptionAttribute( "The location of the cache folder. This should be on a fast drive with plenty of free space." )] [DefaultValueAttribute( "C:\\SwarmCache" )]`
- L348 _private field_ `private string LocalCacheFolder = "C:\\SwarmCache"` — attrs: `[XmlTextAttribute]`
- L353-357 _public property_ `public Int32 MaximumJobsToKeep { get; set; }` — attrs: `[CategoryAttribute( "Cache Settings" )] [DescriptionAttribute( "The number of previous jobs to keep the logs and output data for." )] [DefaultValueAttribute( 10 )]`
- L359 _private field_ `private Int32 LocalMaximumJobsToKeep = 10` — attrs: `[XmlTextAttribute]`
- L364-368 _public property_ `public Int32 MaximumCacheSize { get; set; }` — attrs: `[CategoryAttribute( "Cache Settings" )] [DescriptionAttribute( "The approximate maximum size, in gigabytes, of the cache folder." )] [DefaultValueAttribute( 10 )]`
- L370 _private field_ `private Int32 LocalMaximumCacheSize = 10` — attrs: `[XmlTextAttribute]`
- L375-379 _public property_ `public bool BringToFront { get; set; }` — attrs: `[CategoryAttribute( "General Settings" )] [DescriptionAttribute( "If enabled, brings the Agent window to the front when a Job is started." )] [DefaultValueAttribute( true )]`
- L381 _private field_ `private bool LocalBringToFront = false` — attrs: `[XmlEnumAttribute]`
- L388-391 _public property_ `public EnumedCollection<EProgressionState, Color> VisualizerColors { get; }` — attrs: `[CategoryAttribute( "Visualizer Settings" )] [DescriptionAttribute( "The colors used to draw the progress bars." )] [Editor( typeof( SuppressCollectionEditor ), typeof( UITypeEditor ) )] [TypeConverter( typeof( EnumedCollectionConverter ) )`
- L392 _private field_ `private EnumedCollection<EProgressionState, Color> LocalColours = ...`
- L392 _private field_ `private EnumedCollection< LocalColours = new EnumedCollection<EProgressionState, Color>()`
- L395 _public field_ `public List<SerialisableColour> SerialisableColours = new List<SerialisableColour>()` — attrs: `[BrowsableAttribute( false )]`
- L400-404 _public property_ `public bool ShowDeveloperMenu { get; set; }` — attrs: `[CategoryAttribute( "Developer Settings" )] [DescriptionAttribute( "[DEVELOPER AND QA USE ONLY] If enabled, shows the developer menu." )] [DefaultValueAttribute( false )]`
- L406 _private field_ `private bool LocalShowDeveloperMenu = false` — attrs: `[XmlEnumAttribute]`
- L412-416 _public property_ `public int OptionsVersion { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L418 _private field_ `private int LocalOptionsVersion = (int)EOptionsVersion.Current` — attrs: `[XmlAttribute]`
- L421-425 _public property_ `public Point WindowLocation { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L427 _private field_ `private Point LocalWindowLocation = new Point( 0, 0 )` — attrs: `[XmlAttribute]`
- L430-434 _public property_ `public Size WindowSize { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L436 _private field_ `private Size LocalWindowSize = new Size( 768, 768 )` — attrs: `[XmlAttribute]`
- L439-443 _public property_ `public int AgentTabIndex { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L445 _private field_ `private int LocalAgentTabIndex = 0` — attrs: `[XmlAttribute]`
- L448-452 _public property_ `public float VisualiserZoomLevel { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L454 _private field_ `private float LocalVisualiserZoomLevel = 4.0f` — attrs: `[XmlAttribute]`
- L459-540 _private method_ `private void SetDefaults()`
- L545-557 _private method_ `private void Validate()`
- L562-572 _public method_ `public void PreSave()`
- L577-590 _public method_ `public void PostLoad()`

#### enum `Agent.AgentProcessPriorityClass`  
`public enum AgentProcessPriorityClass`  
_public; L594-600_
- L596 _public* enumerator_ `Normal = ProcessPriorityClass.Normal`
- L597 _public* enumerator_ `Idle = ProcessPriorityClass.Idle`
- L598 _public* enumerator_ `BelowNormal = ProcessPriorityClass.BelowNormal`
- L599 _public* enumerator_ `AboveNormal = ProcessPriorityClass.AboveNormal`

#### class `Agent.SettableDeveloperOptions`  
`public class SettableDeveloperOptions`  
_public; L602-817_
- L607-611 _public property_ `public bool ReplayLastDistribution { get; set; }` — attrs: `[CategoryAttribute( "Developer Settings" )] [DescriptionAttribute( "[DEVELOPER AND QA USE ONLY] Enables a distribution mode which attempts to reproduce the distribution behavior of the last Job." )] [DefaultValueAttribute( false )]`
- L613 _private field_ `private bool LocalReplayLastDistribution = false` — attrs: `[XmlAttribute]`
- L617-621 _public property_ `public bool LocalEnableLocalPerformanceMonitoring { get; set; }` — attrs: `[CategoryAttribute("Local Performance Settings")] [DescriptionAttribute("Whether to enable local performance monitoring")]`
- L623 _private field_ `private bool PrivateLocalEnableLocalPerformanceMonitoring = true` — attrs: `[XmlAttribute]`
- L627-631 _public property_ `public int LocalJobsDefaultProcessorCount { get; set; }` — attrs: `[CategoryAttribute("Local Performance Settings")] [DescriptionAttribute( "The number of processors to make available to locally initiated jobs" )]`
- L633 _private field_ `private int PrivateLocalJobsDefaultProcessorCount = GetDefaultLocalJobsDefaultProcessorCount()` — attrs: `[XmlAttribute]`
- L637-641 _public property_ `public AgentProcessPriorityClass LocalJobsDefaultProcessPriority { get; set; }` — attrs: `[CategoryAttribute( "Local Performance Settings" )] [DescriptionAttribute( "The default priority for locally initiated jobs" )]`
- L643 _private field_ `private AgentProcessPriorityClass PrivateLocalJobsDefaultProcessPriority = AgentProcessPriorityClass.BelowNormal` — attrs: `[XmlAttribute]`
- L647-651 _public property_ `public int RemoteJobsDefaultProcessorCount { get; set; }` — attrs: `[CategoryAttribute( "Local Performance Settings" )] [DescriptionAttribute( "The number of processors to make available to remotely initiated jobs" )]`
- L653 _private field_ `private int PrivateRemoteJobsDefaultProcessorCount = GetDefaultRemoteJobsDefaultProcessorCount()` — attrs: `[XmlAttribute]`
- L657-661 _public property_ `public AgentProcessPriorityClass RemoteJobsDefaultProcessPriority { get; set; }` — attrs: `[CategoryAttribute( "Local Performance Settings" )] [DescriptionAttribute( "The default priority for remotely initiated jobs" )]`
- L663 _private field_ `private AgentProcessPriorityClass PrivateRemoteJobsDefaultProcessPriority = AgentProcessPriorityClass.Idle` — attrs: `[XmlAttribute]`
- L668-672 _public property_ `public int JobExecutableTimeout { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "The amount of time to wait before forefully killing a Job executable after the Job is closed (in seconds). Set to anything < 0 for an infinite timeout." )] [DefaultValue`
- L674 _private field_ `private int LocalJobExecutableTimeout = 5` — attrs: `[XmlAttribute]`
- L680-684 _public property_ `public int RemoteAgentTimeout { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "The amount of time to wait before considering a remote Agent dropped (in seconds). Set to anything < 0 for an infinite timeout." )] [DefaultValueAttribute( 30 )]`
- L686 _private field_ `private int LocalRemoteAgentTimeout = 30` — attrs: `[XmlAttribute]`
- L691-695 _public property_ `public bool UpdateAutomatically { get; set; }` — attrs: `[CategoryAttribute( "Distribution Settings" )] [DescriptionAttribute( "[Advanced] Enables auto updating for deployed agents." )] [DefaultValueAttribute( true )]`
- L698 _private field_ `private bool LocalUpdateAutomatically = ( ApplicationDeployment.IsNetworkDeployed ? true : false )` — attrs: `[XmlTextAttribute]`
- L700 _private field_ `private bool LocalUpdateAutomatically = false`
- L706-710 _public property_ `public Int32 MaximumJobApplicationLogLines { get; set; }` — attrs: `[CategoryAttribute( "Log Settings" )] [DescriptionAttribute( "The maximum number of lines of output from a job application before it truncates what goes to the window. All of the output is written to the log on disk." )] [DefaultValueAttrib`
- L712 _private field_ `private Int32 LocalMaximumJobApplicationLogLines = 1000` — attrs: `[XmlAttribute]`
- L718-722 _public property_ `public int OptionsVersion { get; set; }` — attrs: `[BrowsableAttribute( false )]`
- L724 _private field_ `private int LocalOptionsVersion = ( int )EOptionsVersion.Current` — attrs: `[XmlAttribute]`
- L734-748 _private method_ `private static Int32 GetAllowedProcessorCount()`
- L750-758 _private method_ `private static Int32 GetDefaultLocalJobsDefaultProcessorCount()`
- L760-763 _private method_ `private static Int32 GetDefaultRemoteJobsDefaultProcessorCount()`
- L768-789 _private method_ `private void SetDefaults()`
- L794-800 _private method_ `private void Validate()`
- L805-807 _public method_ `public void PreSave()`
- L812-816 _public method_ `public void PostLoad()`

### `Source/Programs/UnrealSwarm/Agent/Utils.cs` (Agent)


#### class `Agent.ReaderWriterDictionary`  
`public class ReaderWriterDictionary<TKey, TValue>`  
_public; L22-192_
- L27 _private field_ `private ReaderWriterLock AccessLock = new ReaderWriterLock()`
- L32 _private field_ `private Dictionary<TKey, TValue> ProtectedDictionary = ...`
- L32 _private field_ `private Dictionary< ProtectedDictionary = new Dictionary<TKey,TValue>()`
- L37-56 _public method_ `public bool Add( TKey K, TValue V )`
- L58-72 _public method_ `public bool Remove( TKey K )`
- L74-86 _public method_ `public void Clear()`
- L88-102 _public method_ `public bool ContainsKey( TKey K )`
- L104-118 _public method_ `public bool TryGetValue( TKey K, out TValue V )`
- L120-137 _public property_ `public List<TValue> Values { get; }`
- L139-156 _public property_ `public List<TKey> Keys { get; }`
- L158-175 _public property_ `public int Count { get; }`
- L177-191 _public method_ `public Dictionary<TKey, TValue> Copy()`

#### class `Agent.ReaderWriterQueue`  
`public class ReaderWriterQueue<TValue>`  
_public; L199-293_
- L204 _private field_ `private ReaderWriterLock AccessLock = new ReaderWriterLock()`
- L209 _private field_ `private Queue<TValue> ProtectedQueue = new Queue<TValue>()`
- L214-226 _public method_ `public void Clear()`
- L228-240 _public method_ `public void Enqueue( TValue V )`
- L242-257 _public method_ `public TValue Dequeue()`
- L259-273 _public method_ `public TValue[] ToArray()`
- L275-292 _public property_ `public int Count { get; }`

#### class `Agent.ReaderWriterStack`  
`public class ReaderWriterStack<TValue>`  
_public; L300-394_
- L305 _private field_ `private ReaderWriterLock AccessLock = new ReaderWriterLock()`
- L310 _private field_ `private Stack<TValue> ProtectedStack = new Stack<TValue>()`
- L315-327 _public method_ `public void Clear()`
- L329-341 _public method_ `public void Push( TValue V )`
- L343-358 _public method_ `public TValue Pop()`
- L360-374 _public method_ `public TValue[] ToArray()`
- L376-393 _public property_ `public int Count { get; }`

#### class `Agent.PerfTimer`  
`public class PerfTimer`  
_public; L398-494_
- L434 _private* field_ `ReaderWriterDictionary<string, PerfTiming> Timings = ...`
- L434 _private* field_ `ReaderWriterDictionary< Timings = new ReaderWriterDictionary<string, PerfTiming>()`
- L435 _private* field_ `Stack<PerfTiming> LastTimers = new Stack<PerfTiming>()`
- L437-453 _public method_ `public void Start( string Name, bool Accum, Int64 Adder )`
- L455-462 _public method_ `public void Stop()`
- L464-493 _public method_ `public string DumpTimings()`

#### class `Agent.PerfTimer.PerfTiming`  
`private class PerfTiming`  
_private; L400-432_
- L402 _public field_ `public string Name`
- L403 _public field_ `public Stopwatch StopWatchTimer`
- L404 _public field_ `public Int32 Count`
- L405 _public field_ `public bool Accumulate`
- L406 _public field_ `public Int64 Counter`
- L408-415 _public ctor_ `public PerfTiming( string InName, bool InAccumulate )`
- L417-420 _public method_ `public void Start()`
- L422-426 _public method_ `public void Stop()`
- L428-431 _public method_ `public void IncrementCounter( Int64 Adder )`

#### class `Agent.Agent`  
`public partial class Agent : MarshalByRefObject, IAgentInternalInterface, IAgentInterface`  
_public; L501-810_
- inherits: `MarshalByRefObject, IAgentInternalInterface, IAgentInterface`
- L508-512 _public method_ `public Int32 Log( EVerbosityLevel Verbosity, ELogColour TextColour, string Line )`
- L516-581 _private method_ `private Int32 DirectoryRecreate( string DirectoryName )`
- L601-625 _private method_ `private Int64 SizeOfDirectory( string DirectoryPath )`
- L634-679 _private method_ `private void CleanupJobDirectory( string DirectoryPath, Int32 NumSubDirectoriesToKeep, out DateTime OldestJobKeptUtc )`
- L687-717 _private method_ `private void CleanupLogDirectory( string DirectoryPath, DateTime OldestToKeepUtc )`
- L719-741 _private method_ `private Int32 EnsureFolderExists( string Folder )`
- L746 _private field_ `private ELogFlags LoggingFlags = ELogFlags.LOG_NONE`
- L747 _private field_ `private PerfTimer PerfTimerInstance = new PerfTimer()`
- L748 _private field_ `private bool bPerfTimerInstanceActive = false`
- L750-757 _private method_ `private void CreateTimings( ELogFlags InLoggingFlags )`
- L762-771 _private method_ `private void StartTiming( string Name, bool Accum, Int64 Adder )`
- L773-776 _private method_ `private void StartTiming( string Name, bool Accum )`
- L781-790 _private method_ `private void StopTiming()`
- L795-809 _private method_ `private void DumpTimings( Connection Parent )`

#### class `Agent.Agent.DirectoryWriteTimestampComparer`  
`public class DirectoryWriteTimestampComparer : IComparer<DirectoryInfo>`  
_public; L586-592_
- inherits: `IComparer<DirectoryInfo>`
- L588-591 _public method_ `public int Compare( DirectoryInfo A, DirectoryInfo B )`

#### class `Agent.Agent.FileAccessTimestampComparer`  
`public class FileAccessTimestampComparer : IComparer<FileInfo>`  
_public; L593-599_
- inherits: `IComparer<FileInfo>`
- L595-598 _public method_ `public int Compare( FileInfo A, FileInfo B )`
