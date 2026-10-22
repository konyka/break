# CSharp / SwarmCoordinator

- project root: `Source/Programs/UnrealSwarm/SwarmCoordinator`
- files: 7; symbols: 69
- symbol kinds: class=7, ctor=2, field=25, method=31, property=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealSwarm/SwarmCoordinator/Coordinator.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.Coordinator`  
`class Coordinator`  
_internal*; L15-540_
- L17 _public field_ `static public bool AgentsDirty = true`
- L19 _private field_ `static private Dictionary<string, AgentInfo> Agents = ...`
- L19 _private field_ `static private Dictionary< Agents = null`
- L20 _private field_ `static private Int32 UniqueHandle = 0`
- L21 _private field_ `static private DateTime LastMaintainTime = DateTime.MinValue`
- L24-34 _public method_ `public static bool Init()`
- L36-43 _public method_ `public static bool Destroy()`
- L45-64 _public method_ `public static Int32 RestartAgentGroup( string GroupNameToRestart )`
- L66-78 _public method_ `public static void RestartAllAgents()`
- L85-248 _public method_ `public static PingResponse Ping( AgentInfo UpdatedInfo )`
- L253 _private field_ `private static Object GetUniqueHandleLock = new Object()`
- L254-260 _public method_ `public static Int32 GetUniqueHandle()`
- L263-310 _private method_ `private static int AliveAgentSorter( AgentInfo A, AgentInfo B )`
- L317-485 _public method_ `public static List<AgentInfo> GetAvailableAgents( Hashtable RequestedConfiguration )`
- L488-522 _public method_ `public static void MaintainAgents()`
- L524-528 _public method_ `public static Int32 Method( Hashtable InParameters, ref Hashtable OutParameters )`
- L531-539 _public method_ `public static Dictionary<string, AgentInfo> GetAgents()`

### `Source/Programs/UnrealSwarm/SwarmCoordinator/Program.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.Program`  
`static class Program`  
_internal*; L12-68_
- L18-36 _private* method_ `static void CheckForUpdate()`
- L42-67 _private* method_ `static void Main()` — attrs: `[STAThread]` — The main entry point for the application.

### `Source/Programs/UnrealSwarm/SwarmCoordinator/Properties/AssemblyInfo.cs` (SwarmCoordinator)
_(no declarations)_


### `Source/Programs/UnrealSwarm/SwarmCoordinator/Properties/Resources.Designer.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.Properties.Resources`  
`internal class Resources`  
_internal; L27-64_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L29 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L31 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L34-35 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L41-49 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L56-63 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/UnrealSwarm/SwarmCoordinator/Properties/Settings.Designer.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L18-36_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "10.0.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L20 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L22-26 _public property_ `public static Settings Default { get; }`
- L31-35 _public property_ `public int CoordinatorRemotingPort { get; }` — attrs: `[global::System.Configuration.ApplicationScopedSettingAttribute()] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Configuration.DefaultSettingValueAttribute("8009")]`

### `Source/Programs/UnrealSwarm/SwarmCoordinator/SwarmCoordinator.Designer.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.SwarmCoordinator`  
`partial class SwarmCoordinator`  
_internal*; L5-200_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose( bool disposing )` — Clean up any resources being used.
- L31-184 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L188 _private field_ `private System.Windows.Forms.DataGridView AgentGridView`
- L189 _private field_ `private System.Windows.Forms.Button RestartAllAgentsButton`
- L190 _private field_ `private System.Windows.Forms.Button RestartCoordinatorButton`
- L191 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn AgentName`
- L192 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn GroupName`
- L193 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Version`
- L194 _private field_ `private System.Windows.Forms.DataGridViewComboBoxColumn State`
- L195 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn IPAddress`
- L196 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn LastPingTime`
- L197 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn NumLocalCores`
- L198 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn NumRemoteCores`
- L199 _private field_ `private System.Windows.Forms.Button RestartQAAgentsButton`

### `Source/Programs/UnrealSwarm/SwarmCoordinator/SwarmCoordinator.cs` (SwarmCoordinator)


#### class `SwarmCoordinator.SwarmCoordinator`  
`public partial class SwarmCoordinator : Form`  
_public; L19-240_
- inherits: `Form`
- L21 _public field_ `public bool Ticking = false`
- L22 _public field_ `public bool RestartRequested = false`
- L24 _private field_ `private TcpServerChannel ServerChannel = null`
- L26-29 _public ctor_ `public SwarmCoordinator()`
- L31-34 _private method_ `private void Log( string Message )`
- L36-40 _private method_ `private void AppExceptionHandler( object sender, UnhandledExceptionEventArgs args )`
- L42-64 _public method_ `public void Init()`
- L66-69 _public method_ `public bool Restarting()`
- L71-82 _public method_ `public void Destroy()`
- L84-91 _public method_ `public void Run()`
- L93-218 _private method_ `private void UpdateGridRows()`
- L220-223 _private method_ `private void SwarmCoordinator_Closing( object sender, FormClosingEventArgs e )`
- L225-229 _private method_ `private void RestartCoordinatorButton_Click( object sender, EventArgs e )`
- L231-234 _private method_ `private void RestartQAAgentsButton_Click( object sender, EventArgs e )`
- L236-239 _private method_ `private void RestartAllAgentsButton_Click( object sender, EventArgs e )`

#### class `SwarmCoordinator.SwarmCoordinatorImplementation`  
`public class SwarmCoordinatorImplementation : MarshalByRefObject, ISwarmCoordinator`  
_public; L242-268_
- inherits: `MarshalByRefObject, ISwarmCoordinator`
- L244-247 _public method_ `public PingResponse Ping( AgentInfo Agent )`
- L249-252 _public method_ `public Int32 GetUniqueHandle()`
- L254-257 _public method_ `public List<AgentInfo> GetAvailableAgents( Hashtable RequestedConfiguration )`
- L259-262 _public method_ `public Int32 RestartAgentGroup( string GroupNameToRestart )`
- L264-267 _public method_ `public Int32 Method( Hashtable InParameters, ref Hashtable OutParameters )`
