# CSharp / NetworkProfiler

- project root: `Source/Programs/NetworkProfiler/NetworkProfiler`
- files: 13; symbols: 516
- symbol kinds: class=45, const=4, ctor=33, enum=4, enumerator=66, field=238, method=121, property=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/NetworkProfiler/NetworkProfiler/BinaryReaderBigEndian.cs` (NetworkProfiler)


#### class `NetworkProfiler.BinaryReaderBigEndian`  
`public class BinaryReaderBigEndian : BinaryReader`  
_public; L12-91_
- inherits: `BinaryReader`
- L14 _private* field_ `byte[] SwappedBytes = new byte[8]`
- L19-22 _public ctor_ `public BinaryReaderBigEndian(Stream Input) : base(Input, System.Text.Encoding.ASCII)`
- L27-34 _private method_ `private byte[] ReadSwappedBytes(int Count)`
- L39-42 _public method_ `public override ushort ReadUInt16()`
- L47-50 _public method_ `public override short ReadInt16()`
- L55-58 _public method_ `public override int ReadInt32()`
- L63-66 _public method_ `public override uint ReadUInt32()`
- L71-74 _public method_ `public override long ReadInt64()`
- L79-82 _public method_ `public override ulong ReadUInt64()`
- L87-90 _public method_ `public override float ReadSingle()`

### `Source/Programs/NetworkProfiler/NetworkProfiler/Charting.cs` (NetworkProfiler)


#### class `NetworkProfiler.ChartParser`  
`class ChartParser`  
_internal*; L20-145_
- L22-144 _public method_ `public static void ParseStreamIntoChart( MainWindow InMainWindow, NetworkStream NetworkStream, Chart NetworkChart, FilterValues InFilterValues )`

### `Source/Programs/NetworkProfiler/NetworkProfiler/MainWindow.Designer.cs` (NetworkProfiler)


#### class `NetworkProfiler.MainWindow`  
`partial class MainWindow`  
_internal*; L5-893_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-825 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L829 _private field_ `private System.Windows.Forms.Button OpenButton`
- L830 _private field_ `private System.Windows.Forms.TabControl tabControl1`
- L831 _private field_ `private System.Windows.Forms.TabPage tabPage1`
- L832 _private field_ `private System.Windows.Forms.TabPage tabPage3`
- L833 _private field_ `private System.Windows.Forms.TabPage tabPage4`
- L834 _private field_ `private System.Windows.Forms.ListView PropertyListView`
- L835 _private field_ `private System.Windows.Forms.ColumnHeader SizeBits`
- L836 _private field_ `private System.Windows.Forms.ColumnHeader Count`
- L837 _private field_ `private System.Windows.Forms.ColumnHeader AvgSizeBytes`
- L838 _private field_ `private System.Windows.Forms.ColumnHeader Property`
- L839 _private field_ `private System.Windows.Forms.TabPage tabPage5`
- L840 _private field_ `private System.Windows.Forms.ColumnHeader AvgSizeBits`
- L841 _private field_ `private System.Windows.Forms.ListView ActorListView`
- L842 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L843 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader2`
- L844 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader3`
- L845 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader4`
- L846 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader5`
- L847 _private field_ `private System.Windows.Forms.ListView RPCListView`
- L848 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader6`
- L849 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader7`
- L850 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader8`
- L851 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader9`
- L852 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader10`
- L853 _private field_ `private System.Windows.Forms.ProgressBar CurrentProgress`
- L854 _private field_ `private System.Windows.Forms.ContextMenuStrip ContextMenuStrip1`
- L855 _private field_ `private System.Windows.Forms.Label EarlyOutLabel`
- L856 _private field_ `private System.Windows.Forms.TextBox MaxProfileMinutesTextBox`
- L857 _private field_ `private System.Windows.Forms.TabPage AllObjectsTabPage`
- L858 _private field_ `private System.Windows.Forms.ListView ObjectPropertyReplicationListView`
- L859 _private field_ `private System.Windows.Forms.ColumnHeader PropertyColumn`
- L860 _private field_ `private System.Windows.Forms.ColumnHeader PropertyComparedColumn`
- L861 _private field_ `private System.Windows.Forms.ColumnHeader PropertyChangedColumn`
- L862 _private field_ `private System.Windows.Forms.ListView ObjectReplicationListView`
- L863 _private field_ `private System.Windows.Forms.ColumnHeader ObjectClassColumn`
- L864 _private field_ `private System.Windows.Forms.ColumnHeader ComparisonsColumn`
- L865 _private field_ `private System.Windows.Forms.ColumnHeader ReplicationsColumn`
- L866 _private field_ `private System.Windows.Forms.ColumnHeader ComparisonTime`
- L867 _private field_ `private System.Windows.Forms.ColumnHeader PropertyReplicationsColumn`
- L868 _private field_ `private System.Windows.Forms.ColumnHeader ComparisonTimeAvgColumn`
- L869 _private field_ `private System.Windows.Forms.SplitContainer splitContainer2`
- L870 _private field_ `private System.Windows.Forms.RadioButton StackedBunchSizeRadioButton`
- L871 _private field_ `private System.Windows.Forms.RadioButton LineViewRadioButton`
- L872 _private field_ `private System.Windows.Forms.DataVisualization.Charting.Chart NetworkChart`
- L873 _private field_ `private System.Windows.Forms.CheckedListBox ChartListBox`
- L874 _private field_ `private System.Windows.Forms.CheckBox checkAllConnectionsCheckBox`
- L875 _private field_ `private System.Windows.Forms.TabControl Details`
- L876 _private field_ `private System.Windows.Forms.TabPage tabPage2`
- L877 _private field_ `private System.Windows.Forms.TreeView ActorSummaryView`
- L878 _private field_ `private System.Windows.Forms.TabPage tabPage6`
- L879 _private field_ `private System.Windows.Forms.SplitContainer splitContainer1`
- L880 _private field_ `private System.Windows.Forms.ListView ActorPerfPropsListView`
- L881 _private field_ `private System.Windows.Forms.ListView ActorPerfPropsDetailsListView`
- L882 _private field_ `private System.Windows.Forms.TabPage tabPage8`
- L883 _private field_ `private System.Windows.Forms.TreeView TokenDetailsView`
- L884 _private field_ `private System.Windows.Forms.Button ApplyFiltersButton`
- L885 _private field_ `private System.Windows.Forms.CheckedListBox ConnectionListBox`
- L886 _private field_ `private System.Windows.Forms.Panel panel1`
- L887 _private field_ `private System.Windows.Forms.ComboBox RPCFilterBox`
- L888 _private field_ `private System.Windows.Forms.ComboBox PropertyFilterBox`
- L889 _private field_ `private System.Windows.Forms.ComboBox ActorFilterBox`
- L890 _private field_ `private System.Windows.Forms.Label label1`
- L891 _private field_ `private System.Windows.Forms.Label label3`
- L892 _private field_ `private System.Windows.Forms.Label label2`

### `Source/Programs/NetworkProfiler/NetworkProfiler/MainWindow.cs` (NetworkProfiler)


#### enum `NetworkProfiler.SeriesType`  
`public enum SeriesType : int`  
_public; L19-62_
- inherits: `int`
- L21 _public* enumerator_ `OutgoingBandwidthSize = 0`
- L22 _public* enumerator_ `OutgoingBandwidthSizeSec`
- L23 _public* enumerator_ `OutgoingBandwidthSizeAvgSec`
- L24 _public* enumerator_ `ActorCount`
- L25 _public* enumerator_ `PropertySize`
- L26 _public* enumerator_ `PropertySizeSec`
- L27 _public* enumerator_ `RPCSize`
- L28 _public* enumerator_ `RPCSizeSec`
- L29 _public* enumerator_ `Events`
- L30 _public* enumerator_ `ActorCountSec`
- L31 _public* enumerator_ `PropertyCount`
- L32 _public* enumerator_ `PropertyCountSec`
- L33 _public* enumerator_ `RPCCount`
- L34 _public* enumerator_ `RPCCountSec`
- L35 _public* enumerator_ `ExportBunchCount`
- L36 _public* enumerator_ `ExportBunchSize`
- L37 _public* enumerator_ `MustBeMappedGuidsCount`
- L38 _public* enumerator_ `MustBeMappedGuidsSize`
- L39 _public* enumerator_ `SendAckCount`
- L40 _public* enumerator_ `SendAckCountSec`
- L41 _public* enumerator_ `SendAckSize`
- L42 _public* enumerator_ `SendAckSizeSec`
- L43 _public* enumerator_ `ContentBlockHeaderSize`
- L44 _public* enumerator_ `ContentBlockFooterSize`
- L45 _public* enumerator_ `PropertyHandleSize`
- L46 _public* enumerator_ `SendBunchCount`
- L47 _public* enumerator_ `SendBunchCountSec`
- L48 _public* enumerator_ `SendBunchSize`
- L49 _public* enumerator_ `SendBunchSizeSec`
- L50 _public* enumerator_ `SendBunchHeaderSize`
- L51 _public* enumerator_ `GameSocketSendSize`
- L52 _public* enumerator_ `GameSocketSendSizeSec`
- L53 _public* enumerator_ `GameSocketSendCount`
- L54 _public* enumerator_ `GameSocketSendCountSec`
- L55 _public* enumerator_ `ActorReplicateTimeInMS`

#### class `NetworkProfiler.MainWindow`  
`public partial class MainWindow : Form`  
_public; L64-877_
- inherits: `Form`
- L67 _private* field_ `int CurrentFrame = 0`
- L70 _private* field_ `int RangeSelectStart = -1`
- L71 _private* field_ `int RangeSelectEnd = -1`
- L74 _private* field_ `NetworkStream CurrentNetworkStream = null`
- L77 _private* field_ `FilterValues CurrentFilterValues = new FilterValues()`
- L80 _private* field_ `Thread LoadThread = null`
- L81 _private* field_ `Thread SelectRangeThread = null`
- L83 _private* field_ `PartialNetworkStream CurrentStreamSelection = null`
- L86 _private* field_ `int MaxProfileMinutes = 0`
- L88-120 _public ctor_ `public MainWindow( string[] Args )`
- L121-127 _private method_ `private void OnDragEnter( object sender, DragEventArgs e )`
- L129-136 _private method_ `private void OnDragDrop( object sender, DragEventArgs e )`
- L138-142 _private method_ `private void OnFormClosing( object sender, CancelEventArgs e )`
- L144-180 _private* method_ `void NetworkChart_PostPaint( object sender, ChartPaintEventArgs e )`
- L182-237 _private method_ `private void SetDefaultLineView()`
- L239-255 _protected method_ `protected void RegisterChartSeries( SeriesType Type, string FriendlyName, bool bEnabled )`
- L257-262 _protected method_ `protected void UpdateChartSeries( SeriesType Type, SeriesChartType ChartType, bool bEnabled )`
- L264-267 _public method_ `public void AddChartPoint( SeriesType Type, double X, double Y )`
- L269-278 _public method_ `public void UpdateProgress( Int32 Value )`
- L280-290 _public method_ `public void ShowProgress( bool bShow )`
- L292-313 _private method_ `private void SetDefaultStackedBunchSizeView()`
- L315-336 _private method_ `private void SetDefaultFastLineView()`
- L338-348 _private method_ `private void SetupColumns(ListView ListView, String[] Headers)`
- L350-355 _private method_ `private void AddColumn( ListView ListView, String HeaderText )`
- L357-379 _private method_ `private void ChangeNetworkStreamWorker( string Filename )`
- L381-388 _private method_ `private void CancelLoadThread()`
- L390-396 _private method_ `private void ChangeNetworkStream( string Filename )`
- L398-412 _public method_ `public void ClearStreamAndChart()`
- L414-466 _public method_ `public void ParseStreamForListViews()`
- L468-482 _private method_ `private void OpenButton_Click(object sender, EventArgs e)`
- L484-497 _private method_ `private void NetworkChart_MouseClick(object sender, MouseEventArgs e)`
- L499-514 _private method_ `private void ChartListBox_SelectedValueChanged( object sender, EventArgs e )`
- L519-536 _private method_ `private void NetworkChart_CursorPositionChanged(object sender, System.Windows.Forms.DataVisualization.Charting.CursorEventArgs e)`
- L538-558 _public method_ `public void SetCurrentStreamSelection( NetworkStream NetworkStream, PartialNetworkStream Selection, bool bSingleSelect )`
- L560-576 _private method_ `private void SelectRangeWorker( int SelectionStart, int SelectionEnd )`
- L578-585 _private method_ `private void CancelSelectRangeThread()`
- L590-614 _private method_ `private void NetworkChart_SelectionRangeChanged(object sender, CursorEventArgs e)`
- L616-634 _private method_ `private void ReloadChartWorker()`
- L636-648 _private method_ `private void ApplyFiltersButton_Click(object sender, EventArgs e)`
- L711-734 _private method_ `private void HandleListViewSorting( int RequestedSortColumn, ListView ListView )`
- L737-740 _private method_ `private void PropertyListView_ColumnClick(object sender, ColumnClickEventArgs e)`
- L742-745 _private method_ `private void RPCListView_ColumnClick(object sender, ColumnClickEventArgs e)`
- L747-750 _private method_ `private void ActorListView_ColumnClick(object sender, ColumnClickEventArgs e)`
- L752-755 _private method_ `private void ActorPerfPropsListView_ColumnClick( object sender, ColumnClickEventArgs e )`
- L757-760 _private method_ `private void ActorPerfPropsDetailsListView_ColumnClick( object sender, ColumnClickEventArgs e )`
- L762-772 _private method_ `private void ActorPerfPropsListView_SelectedIndexChanged( object sender, EventArgs e )`
- L774-780 _private method_ `private void LineViewRadioButton_CheckChanged( object sender, EventArgs e )`
- L782-788 _private method_ `private void StackedBunchSizeRadioButton_CheckChanged(object sender, EventArgs e)`
- L790-801 _private method_ `private void UpdateConnectionFilter()`
- L803-806 _private method_ `private void ConnectionListBox_SelectedValueChanged( object sender, EventArgs e )`
- L808-811 _public method_ `public int GetMaxProfileMinutes()`
- L813-828 _private method_ `private void MaxProfileMinutesTextBox_TextChanged( object sender, EventArgs e )`
- L830-848 _private method_ `private void CheckAllConnectionsCheckBox_Click(object sender, System.EventArgs e)`
- L850-866 _private method_ `private void ObjectReplicationListView_SelectedIndexChanged(object sender, EventArgs e)`
- L868-871 _private method_ `private void ObjectReplicationListView_ColumnClick(object sender, ColumnClickEventArgs e)`
- L873-876 _private method_ `private void ObjectPropertyReplicationListView_ColumnClick(object sender, ColumnClickEventArgs e)`

#### class `NetworkProfiler.MainWindow.ListViewItemComparer`  
`private class ListViewItemComparer : System.Collections.IComparer`  
_private; L654-703_
- inherits: `System.Collections.IComparer`
- L657 _public field_ `public int SortColumn`
- L659 _public field_ `public SortOrder SortOrder`
- L667-671 _public ctor_ `public ListViewItemComparer(int InSortColumn, SortOrder InSortOrder)`
- L676-702 _public method_ `public int Compare( object A, object B )`

#### class `NetworkProfiler.FilterValues`  
`public class FilterValues`  
_public; L879-886_
- L881 _public field_ `public string ActorFilter = ""`
- L882 _public field_ `public string PropertyFilter = ""`
- L883 _public field_ `public string RPCFilter = ""`
- L885 _public field_ `public HashSet<int> ConnectionMask = null`

### `Source/Programs/NetworkProfiler/NetworkProfiler/NetworkStream.cs` (NetworkProfiler)


#### class `NetworkProfiler.NetworkStream`  
`public class NetworkStream`  
_public; L17-196_
- L21 _public field_ `public static int PacketOverhead = 28`
- L24 _public field_ `public List<string> NameArray = new List<string>()`
- L27 _public field_ `public List<UInt64> AddressArray = new List<UInt64>()`
- L29 _public field_ `public List<string> StringAddressArray = new List<string>()`
- L32 _public field_ `public int CurrentConnectionIndex = 0`
- L35 _private field_ `private Dictionary<string,int> ClassNameToNameIndex = ...`
- L35 _private field_ `private Dictionary< ClassNameToNameIndex = new Dictionary<string,int>()`
- L38 _public field_ `public int NameIndexUnreal = -1`
- L41 _public field_ `public List<PartialNetworkStream> Frames = new List<PartialNetworkStream>()`
- L44 _public field_ `public Dictionary<int,TypeSummary> PropertyNameToSummary = ...`
- L44 _public field_ `public Dictionary< PropertyNameToSummary = new Dictionary<int,TypeSummary>()`
- L46 _public field_ `public Dictionary<int,TypeSummary> ActorNameToSummary = ...`
- L46 _public field_ `public Dictionary< ActorNameToSummary = new Dictionary<int,TypeSummary>()`
- L48 _public field_ `public Dictionary<int,TypeSummary> RPCNameToSummary = ...`
- L48 _public field_ `public Dictionary< RPCNameToSummary = new Dictionary<int,TypeSummary>()`
- L50 _public field_ `public Dictionary<int, ObjectReplicationSummary> ObjectNameToReplicationSummary = ...`
- L50 _public field_ `public Dictionary< ObjectNameToReplicationSummary = new Dictionary<int, ObjectReplicationSummary>()`
- L52 _public field_ `public StreamHeader Header`
- L60-63 _public method_ `public string GetName(int Index)`
- L72-90 _public method_ `public string GetIpString( int ConnectionIndex, uint NetworkVersion )`
- L98-138 _public method_ `public int GetClassNameIndex(int ActorNameIndex)`
- L146-154 _public method_ `public int GetIndexFromClassName( string ClassName )`
- L163-176 _public method_ `public void UpdateSummary( ref Dictionary<int,TypeSummary> Summaries, int NameIndex, int SizeBits, float TimeInMS )`
- L178-181 _public method_ `public UInt32 GetVersion()`
- L183-195 _public method_ `public string GetChannelTypeName(int ChannelTypeIndex)`

#### class `NetworkProfiler.TypeSummary`  
`public class TypeSummary`  
_public; L199-214_
- L202 _public field_ `public long Count = 1`
- L204 _public field_ `public long SizeBits`
- L206 _public field_ `public float TimeInMS`
- L209-213 _public ctor_ `public TypeSummary( long InSizeBits, float InTimeInMS )`

#### class `NetworkProfiler.ObjectReplicationSummary`  
`public class ObjectReplicationSummary`  
_public; L216-247_
- L218-226 _public ctor_ `public ObjectReplicationSummary(int InObjectNameIndex, List<int> PropertyNameIndices)`
- L228 _public field_ `public readonly int ObjectNameIndex`
- L229 _public field_ `public int LastReplicatedFrame = -1`
- L230 _public field_ `public int LastReplicateFrameWithData = -1`
- L232 _public field_ `public int NumberOfComparisons = 0`
- L233 _public field_ `public int NumberOfReplications = 0`
- L234 _public field_ `public int NumberOfReplicationsWithData = 0`
- L236 _public field_ `public int NumberOfFramesReplicated = 0`
- L237 _public field_ `public int NumberOfFramesReplicatedWithData = 0`
- L239 _public field_ `public float TimeSpentComparingProperties = 0`
- L241 _private field_ `private List<PropertyReplicationSummary> PropertiesPrivate`
- L242-245 _public property_ `public ReadOnlyCollection<PropertyReplicationSummary> Properties { get; }`

#### class `NetworkProfiler.PropertyReplicationSummary`  
`public class PropertyReplicationSummary`  
_public; L249-268_
- L251-254 _public ctor_ `public PropertyReplicationSummary(int InPropertyNameIndex)`
- L256 _public field_ `public readonly int PropertyNameIndex`
- L257 _public field_ `public int LastReplicatedFrame = -1`
- L258 _public field_ `public int LastComparedFrame = -1`
- L259 _public field_ `public int LastChangedFrame = -1`
- L261 _public field_ `public int NumberOfComparisons = 0`
- L262 _public field_ `public int NumberOfChanges = 0`
- L263 _public field_ `public int NumberOfReplications = 0`
- L265 _public field_ `public int NumberOfFramesReplicated = 0`
- L266 _public field_ `public int NumberOfFramesCompared = 0`
- L267 _public field_ `public int NumberOfFramesChanged = 0`

### `Source/Programs/NetworkProfiler/NetworkProfiler/PartialNetworkStream.cs` (NetworkProfiler)


#### class `NetworkProfiler.PartialNetworkStream`  
`public class PartialNetworkStream`  
_public; L14-625_
- L19 _public field_ `public float StartTime = -1`
- L21 _public field_ `public float EndTime = 0`
- L23 _public field_ `public int NumFrames = 0`
- L25 _public field_ `public int NumEvents = 0`
- L31 _public field_ `public int ActorCount = 0`
- L35 _public field_ `public int ReplicatedActorCount = 0`
- L38 _public field_ `public float ActorReplicateTimeInMS = 0.0f`
- L41 _public field_ `public int PropertyCount = 0`
- L43 _public field_ `public int ReplicatedSizeBits = 0`
- L48 _public field_ `public int RPCCount = 0`
- L50 _public field_ `public int RPCSizeBits = 0`
- L55 _public field_ `public int SendBunchCount = 0`
- L57 _public field_ `public int SendBunchSizeBits = 0`
- L59 _public field_ `public int SendBunchHeaderSizeBits = 0`
- L62 _public field_ `public Dictionary<int, int> SendBunchCountPerChannel = ...`
- L62 _public field_ `public Dictionary< SendBunchCountPerChannel = new Dictionary<int,int>()`
- L64 _public field_ `public Dictionary<int, int> SendBunchSizeBitsPerChannel = ...`
- L64 _public field_ `public Dictionary< SendBunchSizeBitsPerChannel = new Dictionary<int,int>()`
- L66 _public field_ `public Dictionary<int, int> SendBunchHeaderSizeBitsPerChannel = ...`
- L66 _public field_ `public Dictionary< SendBunchHeaderSizeBitsPerChannel = new Dictionary<int,int>()`
- L68 _public field_ `public Dictionary<int, int> SendBunchPayloadSizeBitsPerChannel = ...`
- L68 _public field_ `public Dictionary< SendBunchPayloadSizeBitsPerChannel = new Dictionary<int,int>()`
- L73 _public field_ `public int UnrealSocketCount = 0`
- L75 _public field_ `public int UnrealSocketSize = 0`
- L77 _public field_ `public int OtherSocketCount = 0`
- L79 _public field_ `public int OtherSocketSize = 0`
- L84 _public field_ `public int SendAckCount = 0`
- L86 _public field_ `public int SendAckSizeBits = 0`
- L91 _public field_ `public int ExportBunchCount = 0`
- L93 _public field_ `public int ExportBunchSizeBits = 0`
- L98 _public field_ `public int MustBeMappedGuidCount = 0`
- L100 _public field_ `public int MustBeMappedGuidSizeBits = 0`
- L105 _public field_ `public int ContentBlockHeaderCount = 0`
- L107 _public field_ `public int ContentBlockHeaderSizeBits = 0`
- L109 _public field_ `public int ContentBlockFooterCount = 0`
- L111 _public field_ `public int ContentBlockFooterSizeBits = 0`
- L116 _public field_ `public int PropertyHandleCount = 0`
- L118 _public field_ `public int PropertyHandleSizeBits = 0`
- L123 _private* field_ `List<TokenBase> Tokens = new List<TokenBase>()`
- L126 _private* field_ `UniqueItemTracker<UniqueActor, TokenReplicateActor> UniqueActors = ...`
- L126 _private* field_ `UniqueItemTracker< UniqueActors = new UniqueItemTracker<UniqueActor, TokenReplicateActor>()`
- L131 _private* field_ `float FirstFrameDeltaTime = 0`
- L133 _private* field_ `int NameIndexUnreal = -1`
- L142-162 _public ctor_ `public PartialNetworkStream( List<TokenBase> InTokens, int InNameIndexUnreal, float InDeltaTime )`
- L172-186 _public ctor_ `public PartialNetworkStream( PartialNetworkStream InStream, FilterValues InFilterValues )`
- L188-221 _public ctor_ `public PartialNetworkStream( MainWindow InMainWindow, List<PartialNetworkStream> InStreams, int InStartFrame, int InEndFrame, int InNameIndexUnreal, FilterValues InFilterValues, float InDeltaTime )`
- L223-227 _public ctor_ `public PartialNetworkStream( int InNameIndexUnreal, float InDeltaTime )`
- L229-237 _public method_ `public void AddStream( PartialNetworkStream InStream )`
- L248-251 _public method_ `public PartialNetworkStream Filter( FilterValues InFilterValues )`
- L253-382 _protected method_ `protected void UpdateSummary( TokenBase Token, FilterValues InFilterValues )`
- L387-395 _protected method_ `protected void CreateSummary( int NameIndexUnreal, float DeltaTime, FilterValues InFilterValues )`
- L397-405 _public method_ `public void ToDetailedTreeView( TreeNodeCollection Nodes, FilterValues InFilterValues )`
- L407-417 _private method_ `private TreeNode AddNode( TreeNodeCollection Nodes, int Index, String Value )`
- L419-488 _public method_ `public void ToActorSummaryView( NetworkStream NetworkStream, TreeView TreeView )`
- L493-541 _public method_ `public void ToActorPerformanceView( NetworkStream NetworkStream, ListView ListView, ListView PropertyListView, FilterValues InFilterValues )`
- L546-567 _public method_ `public void ToPropertyPerformanceView( NetworkStream NetworkStream, string ActorClassName, ListView ListView, FilterValues InFilterValues )`
- L577-597 _public method_ `public string ConvertToSizeString( float SizeInBytes, bool bPerSecond )`
- L605-609 _public method_ `public string ConvertToCountString( float Count, bool bPerSecond )`
- L616-624 _public method_ `public int GetTotalBunchOverheadSizeBits()`

#### class `NetworkProfiler.UniqueItem`  
`class UniqueItem<T> where T : class`  
_internal*; L632-645_
- constraints: `where T : class`
- L634 _public field_ `public int Count = 0`
- L635 _public field_ `public T FirstItem = null`
- L637-644 _public method_ `public virtual void OnItemAdded( T Item )`

#### class `NetworkProfiler.UniqueItemTracker`  
`class UniqueItemTracker<UniqueT, ItemT> where ItemT : class where UniqueT : UniqueItem<ItemT>, new()`  
_internal*; L652-667_
- constraints: `where ItemT : class where UniqueT : UniqueItem<ItemT>, new()`
- L656 _public field_ `public Dictionary<int, UniqueT> UniqueItems = ...`
- L656 _public field_ `public Dictionary< UniqueItems = new Dictionary<int, UniqueT>()`
- L658-666 _public method_ `public void AddItem(ItemT Item, int Key)`

#### class `NetworkProfiler.UniqueProperty`  
`class UniqueProperty : UniqueItem<TokenReplicateProperty>`  
_internal*; L673-682_
- inherits: `UniqueItem<TokenReplicateProperty>`
- L675 _public field_ `public long SizeBits = 0`
- L677-681 _public method_ `override public void OnItemAdded(TokenReplicateProperty Item)`

#### class `NetworkProfiler.UniquePropertyHeader`  
`class UniquePropertyHeader : UniqueItem<TokenWritePropertyHeader>`  
_internal*; L688-697_
- inherits: `UniqueItem<TokenWritePropertyHeader>`
- L690 _public field_ `public long SizeBits = 0`
- L692-696 _public method_ `override public void OnItemAdded(TokenWritePropertyHeader Item)`

#### class `NetworkProfiler.UniqueActor`  
`class UniqueActor : UniqueItem<TokenReplicateActor>`  
_internal*; L703-733_
- inherits: `UniqueItem<TokenReplicateActor>`
- L705 _public field_ `public long SizeBits = 0`
- L706 _public field_ `public float TimeInMS = 0`
- L707 _public field_ `public int ReplicatedCount = 0`
- L709 _public field_ `public UniqueItemTracker<UniqueProperty, TokenReplicateProperty> Properties = ...`
- L709 _public field_ `public UniqueItemTracker< Properties = new UniqueItemTracker<UniqueProperty, TokenReplicateProperty>()`
- L711-732 _public method_ `override public void OnItemAdded(TokenReplicateActor Item)`

### `Source/Programs/NetworkProfiler/NetworkProfiler/Program.cs` (NetworkProfiler)


#### class `NetworkProfiler.Program`  
`static class Program`  
_internal*; L12-25_
- L18-24 _private* method_ `static void Main( string[] Args )` — attrs: `[STAThread]` — The main entry point for the application.

### `Source/Programs/NetworkProfiler/NetworkProfiler/Properties/AssemblyInfo.cs` (NetworkProfiler)
_(no declarations)_


### `Source/Programs/NetworkProfiler/NetworkProfiler/Properties/Resources.Designer.cs` (NetworkProfiler)


#### class `NetworkProfiler.Properties.Resources`  
`internal class Resources`  
_internal; L27-64_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L29 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L31 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L34-35 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L41-49 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L56-63 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/NetworkProfiler/NetworkProfiler/Properties/Settings.Designer.cs` (NetworkProfiler)


#### class `NetworkProfiler.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L18-37_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "10.0.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L20 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L22-26 _public property_ `public static Settings Default { get; }`
- L32-36 _public property_ `public string NetworkPerfConnectionString { get; }` — attrs: `[global::System.Configuration.ApplicationScopedSettingAttribute()] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Configuration.SpecialSettingAttribute(global::System.Configuration.SpecialSetting.ConnectionStrin`

### `Source/Programs/NetworkProfiler/NetworkProfiler/StreamHeader.cs` (NetworkProfiler)


#### class `NetworkProfiler.StreamHeader`  
`public class StreamHeader`  
_public; L14-152_
- L17 _public const_ `public const UInt32 ExpectedMagic = 0x1DBF348C`
- L20 _public const_ `public const UInt32 MinSupportedVersion = 10`
- L23 _public field_ `public UInt32 Magic`
- L25 _public field_ `public UInt32 Version`
- L28 _public field_ `public string Tag`
- L30 _public field_ `public string GameName`
- L32 _public field_ `public string URL`
- L34-63 _public method_ `public static void ShowDialog( string Header, string Message )`
- L73-108 _public method_ `public static StreamHeader ReadHeader( Stream ParserStream, out BinaryReader BinaryStream )`
- L115-139 _public ctor_ `public StreamHeader(BinaryReader BinaryStream)`
- L147-151 _private method_ `private string SerializeAnsiString( BinaryReader BinaryStream )`

### `Source/Programs/NetworkProfiler/NetworkProfiler/StreamParser.cs` (NetworkProfiler)


#### class `NetworkProfiler.StreamParser`  
`class StreamParser`  
_internal*; L16-492_
- L18 _public field_ `public static NetworkStream NetworkStream = new NetworkStream()`
- L26-33 _private method_ `private static void HandleActorSummary(NetworkStream NetworkStream, TokenReplicateActor TokenReplicateActor )`
- L43-56 _private method_ `private static void FinishActorProperties(TokenReplicateActor TokenReplicateActor, List<TokenReplicateProperty> LastProperties, List<TokenWritePropertyHeader> LastPropertyHeaders)`
- L64-313 _public method_ `public static NetworkStream Parse( MainWindow InMainWindow, Stream ParserStream )`
- L322-343 _public method_ `public static void ParseStreamIntoListView( NetworkStream NetworkStream, Dictionary<int,TypeSummary> Summaries, ListView ListView )`
- L345-396 _private method_ `private static void HandleObjectComparison(NetworkStream NetworkStream, TokenPropertyComparison ObjectComparison)`
- L398-447 _private method_ `private static void HandleObjectReplication(NetworkStream NetworkStream, TokenPropertyComparison ObjectComparison, TokenReplicatePropertiesMetaData ObjectReplication)`
- L449-468 _public method_ `public static void ParseStreamIntoReplicationListView( NetworkStream NetworkStream, Dictionary<int, ObjectReplicationSummary> Summaries, ListView ListView )`
- L470-491 _public method_ `public static void ParseStreamIntoPropertyReplicationListView(NetworkStream NetworkStream, ReadOnlyCollection<PropertyReplicationSummary> Summaries, ListView ListView )`

### `Source/Programs/NetworkProfiler/NetworkProfiler/Tokens.cs` (NetworkProfiler)


#### enum `NetworkProfiler.ETokenTypes`  
`public enum ETokenTypes`  
_public; L15-39_
- L17 _public* enumerator_ `FrameMarker = 0`
- L18 _public* enumerator_ `SocketSendTo`
- L19 _public* enumerator_ `SendBunch`
- L20 _public* enumerator_ `SendRPC`
- L21 _public* enumerator_ `ReplicateActor`
- L22 _public* enumerator_ `ReplicateProperty`
- L23 _public* enumerator_ `EndOfStreamMarker`
- L24 _public* enumerator_ `Event`
- L25 _public* enumerator_ `RawSocketData`
- L26 _public* enumerator_ `SendAck`
- L27 _public* enumerator_ `WritePropertyHeader`
- L28 _public* enumerator_ `ExportBunch`
- L29 _public* enumerator_ `MustBeMappedGuids`
- L30 _public* enumerator_ `BeginContentBlock`
- L31 _public* enumerator_ `EndContentBlock`
- L32 _public* enumerator_ `WritePropertyHandle`
- L33 _public* enumerator_ `ConnectionChange`
- L34 _public* enumerator_ `NameReference`
- L35 _public* enumerator_ `ConnectionReference`
- L36 _public* enumerator_ `PropertyComparison`
- L37 _public* enumerator_ `ReplicatePropertiesMetaData`
- L38 _public* enumerator_ `MaxAndInvalid`

#### enum `NetworkProfiler.EChannelTypes`  
`public enum EChannelTypes`  
_public; L42-50_
- L44 _public* enumerator_ `Invalid = 0`
- L45 _public* enumerator_ `Control`
- L46 _public* enumerator_ `Actor`
- L47 _public* enumerator_ `File`
- L48 _public* enumerator_ `Voice`
- L49 _public* enumerator_ `Max`

#### class `NetworkProfiler.TokenBase`  
`public class TokenBase`  
_public; L55-188_
- L58 _public field_ `public ETokenTypes TokenType = ETokenTypes.MaxAndInvalid`
- L61 _public field_ `public int ConnectionIndex = 0`
- L64 _public field_ `public static int[] TokenTypeStats = Enumerable.Repeat(0, (int)ETokenTypes.MaxAndInvalid).ToArray()`
- L73-165 _public method_ `public static TokenBase ReadNextToken(BinaryReader BinaryStream, NetworkStream InNetworkStream)`
- L167-170 _public method_ `public virtual void ToDetailedTreeView( TreeNodeCollection List, FilterValues InFilterValues )`
- L179-187 _public method_ `public virtual bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenEndOfStreamMarker`  
`class TokenEndOfStreamMarker : TokenBase`  
_internal*; L193-195_
- inherits: `TokenBase`

#### class `NetworkProfiler.TokenFrameMarker`  
`class TokenFrameMarker : TokenBase`  
_internal*; L200-217_
- inherits: `TokenBase`
- L203 _public field_ `public float RelativeTime`
- L206-209 _public ctor_ `public TokenFrameMarker(BinaryReader BinaryStream)`
- L211-216 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenSocketSendTo`  
`class TokenSocketSendTo : TokenBase`  
_internal*; L222-267_
- inherits: `TokenBase`
- L225 _public field_ `public int SocketNameIndex`
- L227 _public field_ `public UInt16 BytesSent`
- L229 _public field_ `public UInt16 NumPacketIdBits`
- L231 _public field_ `public UInt16 NumBunchBits`
- L233 _public field_ `public UInt16 NumAckBits`
- L235 _public field_ `public UInt16 NumPaddingBits`
- L238-246 _public ctor_ `public TokenSocketSendTo(BinaryReader BinaryStream)`
- L248-261 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`
- L263-266 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenSendBunch`  
`class TokenSendBunch : TokenBase`  
_internal*; L272-335_
- inherits: `TokenBase`
- L275 _public field_ `public UInt16 ChannelIndex`
- L277 _protected field_ `protected byte ChannelType`
- L279 _protected field_ `protected int ChannelTypeNameIndex`
- L281 _public field_ `public UInt16 NumHeaderBits`
- L283 _public field_ `public UInt16 NumPayloadBits`
- L286-302 _public ctor_ `public TokenSendBunch(BinaryReader BinaryStream, UInt32 Version)`
- L304-314 _public method_ `public int GetChannelTypeIndex()`
- L319-322 _public method_ `public int GetNumTotalBits()`
- L324-334 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenSendRPC`  
`class TokenSendRPC : TokenBase`  
_internal*; L340-409_
- inherits: `TokenBase`
- L343 _public field_ `public int ActorNameIndex`
- L345 _public field_ `public int FunctionNameIndex`
- L347 _public field_ `public int NumHeaderBits`
- L349 _public field_ `public int NumParameterBits`
- L351 _public field_ `public int NumFooterBits`
- L354-371 _public ctor_ `public TokenSendRPC(BinaryReader BinaryStream, UInt32 Version)`
- L376-379 _public method_ `public int GetNumTotalBits()`
- L381-393 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`
- L404-408 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenReplicateActor`  
`class TokenReplicateActor : TokenBase`  
_internal*; L416-545_
- inherits: `TokenBase`
- L425 _public field_ `public byte NetFlags`
- L427 _public field_ `public int ActorNameIndex`
- L429 _public field_ `public float TimeInMS`
- L432 _public field_ `public List<TokenReplicateProperty> Properties`
- L435 _public field_ `public List<TokenWritePropertyHeader> PropertyHeaders`
- L438-445 _public ctor_ `public TokenReplicateActor(BinaryReader BinaryStream)`
- L454-474 _public method_ `public int GetNumReplicatedBits( FilterValues InFilterValues )`
- L484-516 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`
- L527-539 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`
- L541-544 _public method_ `public int GetClassNameIndex()`

#### enum `NetworkProfiler.TokenReplicateActor.ENetFlags`  
`public enum ENetFlags`  
_public; L418-423_
- L420 _public* enumerator_ `Dirty = 1`
- L421 _public* enumerator_ `Initial = 2`
- L422 _public* enumerator_ `Owner = 4`

#### class `NetworkProfiler.TokenReplicateProperty`  
`class TokenReplicateProperty : TokenBase`  
_internal*; L550-577_
- inherits: `TokenBase`
- L553 _public field_ `public int PropertyNameIndex`
- L555 _public field_ `public UInt16 NumBits`
- L558-562 _public ctor_ `public TokenReplicateProperty(BinaryReader BinaryStream)`
- L573-576 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenWritePropertyHeader`  
`class TokenWritePropertyHeader : TokenBase`  
_internal*; L582-609_
- inherits: `TokenBase`
- L585 _public field_ `public int PropertyNameIndex`
- L587 _public field_ `public UInt16 NumBits`
- L590-594 _public ctor_ `public TokenWritePropertyHeader(BinaryReader BinaryStream)`
- L605-608 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenExportBunch`  
`class TokenExportBunch : TokenBase`  
_internal*; L614-631_
- inherits: `TokenBase`
- L617 _public field_ `public UInt16 NumBits`
- L620-623 _public ctor_ `public TokenExportBunch(BinaryReader BinaryStream)`
- L625-630 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenMustBeMappedGuids`  
`class TokenMustBeMappedGuids : TokenBase`  
_internal*; L636-658_
- inherits: `TokenBase`
- L639 _public field_ `public UInt16 NumGuids`
- L642 _public field_ `public UInt16 NumBits`
- L645-649 _public ctor_ `public TokenMustBeMappedGuids(BinaryReader BinaryStream)`
- L651-657 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenBeginContentBlock`  
`class TokenBeginContentBlock : TokenBase`  
_internal*; L663-690_
- inherits: `TokenBase`
- L666 _public field_ `public int ObjectNameIndex`
- L668 _public field_ `public UInt16 NumBits`
- L671-675 _public ctor_ `public TokenBeginContentBlock(BinaryReader BinaryStream)`
- L686-689 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenEndContentBlock`  
`class TokenEndContentBlock : TokenBase`  
_internal*; L695-722_
- inherits: `TokenBase`
- L698 _public field_ `public int ObjectNameIndex`
- L700 _public field_ `public UInt16 NumBits`
- L703-707 _public ctor_ `public TokenEndContentBlock(BinaryReader BinaryStream)`
- L718-721 _public method_ `public override bool MatchesFilters( FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenWritePropertyHandle`  
`class TokenWritePropertyHandle : TokenBase`  
_internal*; L727-737_
- inherits: `TokenBase`
- L730 _public field_ `public UInt16 NumBits`
- L733-736 _public ctor_ `public TokenWritePropertyHandle(BinaryReader BinaryStream)`

#### class `NetworkProfiler.TokenConnectionChanged`  
`class TokenConnectionChanged : TokenBase`  
_internal*; L742-752_
- inherits: `TokenBase`
- L745 _public field_ `public Int32 AddressIndex`
- L748-751 _public ctor_ `public TokenConnectionChanged( BinaryReader BinaryStream )`

#### class `NetworkProfiler.TokenNameReference`  
`class TokenNameReference : TokenBase`  
_internal*; L757-768_
- inherits: `TokenBase`
- L760 _public field_ `public string Name = null`
- L763-767 _public ctor_ `public TokenNameReference( BinaryReader BinaryStream )`

#### class `NetworkProfiler.TokenConnectionReference`  
`class TokenConnectionReference : TokenBase`  
_internal*; L773-783_
- inherits: `TokenBase`
- L776 _public field_ `public UInt64 Address`
- L779-782 _public ctor_ `public TokenConnectionReference( BinaryReader BinaryStream )`

#### class `NetworkProfiler.TokenConnectionStringReference`  
`class TokenConnectionStringReference : TokenBase`  
_internal*; L790-801_
- inherits: `TokenBase`
- L793 _public field_ `public string Address = null`
- L796-800 _public ctor_ `public TokenConnectionStringReference(BinaryReader BinaryStream)`

#### class `NetworkProfiler.TokenEvent`  
`class TokenEvent : TokenBase`  
_internal*; L806-835_
- inherits: `TokenBase`
- L809 _public field_ `public int EventNameNameIndex`
- L811 _public field_ `public int EventDescriptionNameIndex`
- L814-818 _public ctor_ `public TokenEvent(BinaryReader BinaryStream)`
- L828-834 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenRawSocketData`  
`class TokenRawSocketData : TokenBase`  
_internal*; L840-851_
- inherits: `TokenBase`
- L843 _public field_ `public byte[] RawData`
- L846-850 _public ctor_ `public TokenRawSocketData(BinaryReader BinaryStream)`

#### class `NetworkProfiler.TokenSendAck`  
`class TokenSendAck : TokenBase`  
_internal*; L856-873_
- inherits: `TokenBase`
- L859 _public field_ `public UInt16 NumBits`
- L862-865 _public ctor_ `public TokenSendAck(BinaryReader BinaryStream)`
- L867-872 _public method_ `public override void ToDetailedTreeView( TreeNodeCollection Tree, FilterValues InFilterValues )`

#### class `NetworkProfiler.TokenPropertyComparison`  
`class TokenPropertyComparison : TokenBase`  
_internal*; L878-918_
- inherits: `TokenBase`
- L881 _public field_ `public int ObjectNameIndex`
- L884 _public field_ `public float TimeSpentComparing`
- L890 _public field_ `public BitArray ComparedProperties`
- L897 _public field_ `public BitArray ChangedProperties`
- L899 _public field_ `public List<int> ExportedPropertyNames`
- L901-917 _public ctor_ `public TokenPropertyComparison(BinaryReader BinaryStream)`

#### class `NetworkProfiler.TokenReplicatePropertiesMetaData`  
`class TokenReplicatePropertiesMetaData : TokenBase`  
_internal*; L923-952_
- inherits: `TokenBase`
- L926 _public field_ `public int ObjectNameIndex`
- L934 _public field_ `public bool bSentAllChangedProperties`
- L942 _public field_ `public BitArray FilteredProperties`
- L944-951 _public ctor_ `public TokenReplicatePropertiesMetaData(BinaryReader BinaryStream)`

#### class `NetworkProfiler.TokenHelper`  
`public class TokenHelper`  
_public; L955-1011_
- L957 _public const_ `public const int NumBitsPerDWord = 32`
- L958 _public const_ `public const int NumBitsPerDWordLog2 = 5`
- L960-977 _public method_ `static public TreeNode AddNode( TreeNodeCollection Tree, string Text )`
- L979-994 _public method_ `public static int LoadPackedInt( BinaryReader BinaryStream )`
- L996-1010 _public method_ `public static void ReadBitArray(BinaryReader BinaryStream, ref BitArray OutBitArray)`
