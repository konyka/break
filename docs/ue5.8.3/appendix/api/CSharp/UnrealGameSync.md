# CSharp / UnrealGameSync

- project root: `Source/Programs/UnrealGameSync/UnrealGameSync`
- files: 138; symbols: 3794
- symbol kinds: class=244, const=43, ctor=133, delegate=15, enum=24, enumerator=98, event=20, field=1436, interface=5, method=1443, property=330, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/UnrealGameSync/ActivationListener.cs` (UnrealGameSync)


#### class `UnrealGameSync.ActivationListener`  
`class ActivationListener : IDisposable`  
_internal*; L8-66_
- inherits: `IDisposable`
- L10 _private* field_ `Thread? _backgroundThread`
- L11 _private* field_ `readonly EventWaitHandle _activateEventHandle`
- L12 _private* field_ `readonly EventWaitHandle _quitEventHandle`
- L14 _public event_ `public event Action? OnActivate`
- L16-20 _public ctor_ `public ActivationListener(EventWaitHandle inActivateEventHandle)`
- L22-30 _public method_ `public void Start()`
- L32-41 _public method_ `public void Stop()`
- L43-49 _public method_ `public void Dispose()`
- L51-65 _private* method_ `void ThreadProc()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/ApplicationThemeManager.cs` (UnrealGameSync)


#### class `UnrealGameSync.InvertibleImage`  
`public sealed class InvertibleImage : IDisposable`  
_public; L14-63_
- inherits: `IDisposable`
- L16 _private* field_ `readonly bool _disposeImage`
- L17 _private* field_ `Image? _standardImage`
- L18 _private* field_ `Image? _invertedImage`
- L20-26 _public ctor_ `public InvertibleImage(Image image, bool disposeImage)`
- L28-32 _public method_ `public Image? ResolveImage()`
- L34-44 _public method_ `public void Dispose()`
- L46-62 _private method_ `private void InitInvertedImage()`

#### class `UnrealGameSync.InvertibleColor`  
`public class InvertibleColor`  
_public; L65-81_
- L67 _public property_ `public Color StandardColor { get; init; }`
- L68 _public property_ `public Color InvertedColor { get; init; }`
- L70-74 _public ctor_ `public InvertibleColor(Color color)`
- L76-80 _public method_ `public Color ResolveColor()`

#### interface `UnrealGameSync.ICustomThemeHandler`  
`interface ICustomThemeHandler`  
_internal*; L83-86_
- L85 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

#### class `UnrealGameSync.ApplicationThemeManager`  
`public sealed class ApplicationThemeManager : IDisposable`  
_public; L88-420_
- inherits: `IDisposable`
- L91 _public property_ `public ApplicationTheme Theme => ...`
- L94 _private* field_ `readonly InvertibleImage _dropListIcon = new InvertibleImage(global::UnrealGameSync.Properties.Resources.DropList, false)`
- L96-99 _public ctor_ `public ApplicationThemeManager()`
- L101-104 _public method_ `public void Dispose()`
- L107 _private method_ `private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref int attrValue, int attrSize)` — attrs: `[DllImport("dwmapi.dll")]`
- L110 _private method_ `private static extern int SetWindowTheme(IntPtr hWnd, string? pszSubAppName, string? pszSubIdList)` — attrs: `[DllImport("uxtheme.dll", CharSet = CharSet.Unicode)]`
- L113-120 _private method_ `private static void UpdateDefaultTheme()` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Not currently used")]`
- L122-163 _private method_ `private void ApplyDarkMode(Control control)`
- L165-171 _public method_ `public void ApplyThemeRecursively()`
- L173-179 _private method_ `private void ControlHandleCreated(object? sender, EventArgs args)`
- L181-187 _private method_ `private void ControlEnabledChanged(object? sender, EventArgs args)`
- L189-195 _private method_ `private void ControlAdded(object? sender, ControlEventArgs args)`
- L197-203 _private method_ `private void ControlHandleDestroyed(object? sender, EventArgs args)`
- L205-211 _private method_ `private void ToolStripDropDownClosed(object? sender, EventArgs args)`
- L213-222 _private method_ `private void UninitialiseToolStripDropDown(ToolStripDropDown dropDown)`
- L224-238 _private method_ `private void UnitialiseControl(Control control)`
- L240 _private field_ `private readonly HashSet<Control> _registeredControls = new HashSet<Control>()`
- L242-269 _public method_ `public void ApplyThemeRecursively(Control control)`
- L271-277 _public method_ `public void ApplyThemeRecursively(Control.ControlCollection controls)`
- L279-285 _public method_ `public void ApplyThemeRecursively(ToolStripItemCollection items)`
- L287-296 _public method_ `public void ApplyThemeRecursively(ToolStripItem item)`
- L298-302 _public method_ `public void ApplyThemeRecursively(ToolTip item)`
- L304-386 _public method_ `public void DefaultApplyThemeToControl(Control control)`

#### class `UnrealGameSync.ApplicationThemeManager.ThemedToolStripRenderer`  
`private class ThemedToolStripRenderer(ApplicationThemeManager themeManager) : ToolStripProfessionalRenderer(new ThemedColorTable(themeManager))`  
_private; L388-419_
- L390-397 _protected method_ `protected override void OnRenderImageMargin(ToolStripRenderEventArgs e)`
- L399-407 _protected method_ `protected override void OnRenderArrow(ToolStripArrowRenderEventArgs e)`

#### class `UnrealGameSync.ApplicationThemeManager.ThemedToolStripRenderer.ThemedColorTable`  
`private class ThemedColorTable(ApplicationThemeManager themeManager) : ProfessionalColorTable`  
_private; L409-418_
- L411 _public property_ `public override Color MenuItemSelectedGradientBegin => ...`
- L412 _public property_ `public override Color MenuItemSelectedGradientEnd => ...`
- L413 _public property_ `public override Color MenuItemBorder => ...`
- L414 _public property_ `public override Color CheckBackground => ...`
- L415 _public property_ `public override Color CheckPressedBackground => ...`
- L416 _public property_ `public override Color CheckSelectedBackground => ...`
- L417 _public property_ `public override Color ButtonSelectedBorder => ...`

### `Source/Programs/UnrealGameSync/UnrealGameSync/ArtifactDownload.cs` (UnrealGameSync)


#### class `UnrealGameSync.ArtifactDownload`  
`class ArtifactDownload`  
_internal*; L21-216_
- L38-79 _private* method_ `static async Task DoSyncAsync(Uri baseUri, RefName refName, DirectoryReference outputDir, IProgress<string> progress, CancellationToken cancellationToken)`
- L81-112 _private* method_ `static async Task DoSyncZenAsync(Uri baseUri, DirectoryReference outputDir, IProgress<string> progress, CancellationToken cancellationToken)`
- L114-144 _public method_ `public static void RegisterFileAssociations(string application)`
- L146-166 _public method_ `public static bool ProcessCommandLine(string[] args)`
- L168-215 _private* method_ `static void Download(string artifactFile)`

#### class `UnrealGameSync.ArtifactDownload.CopyProgressAdapter`  
`class CopyProgressAdapter : IProgress<IExtractStats>`  
_private*; L23-36_
- inherits: `IProgress<IExtractStats>`
- L25 _private* field_ `readonly IProgress<string> _inner`
- L27-30 _public ctor_ `public CopyProgressAdapter(IProgress<string> inner)`
- L32-35 _public method_ `public void Report(IExtractStats value)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Automation/P4Automation.cs` (UnrealGameSync)


#### class `UnrealGameSync.P4Automation`  
`static class P4Automation`  
_internal*; L12-67_
- L14-21 _public method_ `public static IPerforceSettings GetConnectionSettings()`
- L23-26 _public method_ `public static Task<string> PrintToTempFile(IPerforceConnection? connection, string depotPath, ILogger logger)`
- L28-66 _public method_ `public static async Task<string> PrintToTempFileAsync(IPerforceConnection? connection, string depotPath, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Automation/VisualStudioAutomation.cs` (UnrealGameSync)


#### class `UnrealGameSync.VisualStudioAutomation`  
`static class VisualStudioAutomation`  
_internal*; L17-53_
- L19-52 _public method_ `public static bool OpenFile(string fileName, out string? errorMessage, int line = -1)`

#### class `UnrealGameSync.VisualStudioAccessor`  
`static class VisualStudioAccessor`  
_internal*; L58-169_
- desc: Visual Studio automation accessor
- L60-84 _public method_ `public static bool LaunchVisualStudio(string arguments, out string errorMessage)`
- L87-141 _public method_ `public static DTE? GetDte()` — attrs: `[STAThread]`
- L143-157 _private* method_ `static bool IsVisualStudioDteMoniker(string inName)`
- L159-162 _private* method_ `static bool Succeeded(int result)`
- L165 _public method_ `public static extern int CreateBindCtx(int reserved, out IBindCtx bindCtx)` — attrs: `[DllImport("ole32.dll")]`
- L168 _public method_ `public static extern int GetRunningObjectTable(int reserved, out IRunningObjectTable rot)` — attrs: `[DllImport("ole32.dll")]`

#### class `UnrealGameSync.VisualStudioInstallation`  
`class VisualStudioInstallation`  
_internal*; L171-192_
- L176 _public property_ `public string? BaseDir { get; set; }` — Base directory for the installation
- L181 _public property_ `public string? DevEnvPath { get; set; }` — Path of the devenv executable
- L186 _public property_ `public int MajorVersion { get; set; }` — Visual Studio major version number
- L191 _public property_ `public string? RotMoniker { get; set; }` — Running Object Table moniker for this installation

#### class `UnrealGameSync.VisualStudioInstallations`  
`static class VisualStudioInstallations`  
_internal*; L197-294_
- L200-217 _public method_ `public static VisualStudioInstallation? GetPreferredInstallation(int majorVersion = 0)`
- L219 _public property_ `public static IReadOnlyList<VisualStudioInstallation> Installs => ...`
- L221-224 _public method_ `public static void Refresh()`
- L226-286 _private* method_ `static List<VisualStudioInstallation> GetVisualStudioInstallations()`
- L288-291 _private* ctor_ `static VisualStudioInstallations()`
- L293 _private* field_ `static readonly List<VisualStudioInstallation> s_cachedInstalls = new List<VisualStudioInstallation>()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/AutomationServer.cs` (UnrealGameSync)


#### enum `UnrealGameSync.AutomationRequestType`  
`enum AutomationRequestType`  
_internal*; L17-25_
- L19 _public* enumerator_ `SyncProject = 0`
- L20 _public* enumerator_ `FindProject = 1`
- L21 _public* enumerator_ `OpenProject = 2`
- L22 _public* enumerator_ `ExecCommand = 3`
- L23 _public* enumerator_ `OpenIssue = 4`
- L24 _public* enumerator_ `RunCustomTool = 5`

#### class `UnrealGameSync.AutomationRequestInput`  
`class AutomationRequestInput`  
_internal*; L27-57_
- L29 _public field_ `public AutomationRequestType Type`
- L30 _public field_ `public byte[] Data`
- L32-36 _public ctor_ `public AutomationRequestInput(AutomationRequestType type, byte[] data)`
- L38-47 _public method_ `public static AutomationRequestInput Read(Stream inputStream)`
- L49-56 _public method_ `public void Write(Stream outputStream)`

#### enum `UnrealGameSync.AutomationRequestResult`  
`enum AutomationRequestResult`  
_internal*; L59-67_
- L61 _public* enumerator_ `Ok`
- L62 _public* enumerator_ `Invalid`
- L63 _public* enumerator_ `Busy`
- L64 _public* enumerator_ `Canceled`
- L65 _public* enumerator_ `Error`
- L66 _public* enumerator_ `NotFound`

#### class `UnrealGameSync.AutomationRequestOutput`  
`class AutomationRequestOutput`  
_internal*; L69-106_
- L71 _public field_ `public AutomationRequestResult Result`
- L72 _public field_ `public byte[] Data`
- L74-78 _public ctor_ `public AutomationRequestOutput(AutomationRequestResult result)`
- L80-84 _public ctor_ `public AutomationRequestOutput(AutomationRequestResult result, byte[] data)`
- L86-95 _public method_ `public static AutomationRequestOutput Read(Stream inputStream)`
- L97-105 _public method_ `public void Write(Stream outputStream)`

#### class `UnrealGameSync.AutomationRequest`  
`class AutomationRequest : IDisposable`  
_internal*; L108-130_
- inherits: `IDisposable`
- L110 _public field_ `public AutomationRequestInput Input`
- L111 _public field_ `public AutomationRequestOutput? Output`
- L112 _public field_ `public ManualResetEventSlim Complete`
- L114-118 _public ctor_ `public AutomationRequest(AutomationRequestInput input)`
- L120-124 _public method_ `public void SetOutput(AutomationRequestOutput output)`
- L126-129 _public method_ `public void Dispose()`

#### class `UnrealGameSync.AutomationServer`  
`class AutomationServer : IAsyncDisposable, IDisposable`  
_internal*; L132-402_
- inherits: `IAsyncDisposable, IDisposable`
- L134 _private* field_ `static readonly UnicodeEncoding _streamEncoding = new UnicodeEncoding()`
- L136 _private* field_ `readonly CancellationTokenSource _cancellationSource = new CancellationTokenSource()`
- L138 _private* const_ `const string IpcChannel = @"\.\pipe\UGSChannel"`
- L139 _private* field_ `readonly Task? _ipcTask`
- L141 _public const_ `public const int DefaultPortNumber = 30422`
- L142 _private* field_ `readonly Task? _tcpTask`
- L144 _private* field_ `readonly Action<AutomationRequest> _postRequest`
- L146 _private* field_ `readonly ILogger _logger`
- L148-176 _public ctor_ `public AutomationServer(Action<AutomationRequest> postRequest, string? uri, ILogger<AutomationServer> logger)`
- L178-188 _public method_ `public static void SetPortNumber(int portNumber)`
- L190-201 _public method_ `public static int GetPortNumber()`
- L203-242 _private* method_ `async Task RunIpcAsync(string? commandLineUri, CancellationToken cancellationToken)`
- L244-294 _private* method_ `async Task RunTcpAsync(int portNumber, CancellationToken cancellationToken)`
- L296-319 _private* method_ `void HandleUri(string uri)`
- L324-338 _public method_ `public static void SendUri(string uri)` — Sends UGS scope URI from secondary process to main for handling
- L340-348 _private* method_ `static string ReadString(Stream stream)`
- L350-365 _private* method_ `static void WriteString(Stream stream, string output)`
- L367-370 _public method_ `public void Dispose()`
- L372-401 _public method_ `public async ValueTask DisposeAsync()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/AlertButtonControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.AlertButtonControl`  
`partial class AlertButtonControl : Button`  
_internal*; L11-214_
- inherits: `Button`
- L66 _private* field_ `AlertButtonTheme _themeValue`
- L67 _private* field_ `AlertButtonColors _colors`
- L68 _private* field_ `AlertButtonColors _customColorsValue`
- L69 _private* field_ `bool _mouseOver`
- L70 _private* field_ `bool _mouseDown`
- L73-81 _public property_ `public AlertButtonTheme Theme { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L84-92 _public property_ `public AlertButtonColors CustomColors { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L94-98 _public ctor_ `public AlertButtonControl()`
- L100-151 _private method_ `private void UpdateThemeColors()`
- L153-159 _protected method_ `protected override void OnMouseDown(MouseEventArgs mevent)`
- L161-167 _protected method_ `protected override void OnMouseUp(MouseEventArgs mevent)`
- L169-175 _protected method_ `protected override void OnMouseEnter(EventArgs e)`
- L177-183 _protected method_ `protected override void OnMouseLeave(EventArgs e)`
- L185-213 _protected method_ `protected override void OnPaint(PaintEventArgs e)`

#### enum `UnrealGameSync.AlertButtonControl.AlertButtonTheme`  
`public enum AlertButtonTheme`  
_public; L13-20_
- L15 _public* enumerator_ `Normal`
- L16 _public* enumerator_ `Green`
- L17 _public* enumerator_ `Red`
- L18 _public* enumerator_ `Strong`
- L19 _public* enumerator_ `Custom`

#### struct `UnrealGameSync.AlertButtonControl.AlertButtonColors`  
`public struct AlertButtonColors`  
_public; L23-64_
- attrs: `[TypeConverter(typeof(ExpandableObjectConverter))]`
- L25-28 _public property_ `public Color ForeColor { get; set; }`
- L30-33 _public property_ `public Color BorderColor { get; set; }`
- L35-38 _public property_ `public Color BackgroundColor1 { get; set; }`
- L40-43 _public property_ `public Color BackgroundColor2 { get; set; }`
- L45-48 _public property_ `public Color BackgroundColorHover1 { get; set; }`
- L50-53 _public property_ `public Color BackgroundColorHover2 { get; set; }`
- L55-58 _public property_ `public Color BackgroundColorDown1 { get; set; }`
- L60-63 _public property_ `public Color BackgroundColorDown2 { get; set; }`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/AlertImageControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.AlertImageControl`  
`partial class AlertImageControl : UserControl`  
_internal*; L11-47_
- inherits: `UserControl`
- L13 _private* field_ `Image? _imageValue`
- L16-24 _public property_ `public Image? Image { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L26-28 _public ctor_ `public AlertImageControl()`
- L30-46 _protected method_ `protected override void OnPaint(PaintEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/BuildListControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.BuildListControl`  
`class BuildListControl : CustomListViewControl`  
_internal*; L12-160_
- inherits: `CustomListViewControl`
- L26 _private* const_ `const int WmVscroll = 0x115`
- L27 _private* const_ `const int WmMousewheel = 0x020A`
- L30 _private* const_ `const int SbVert = 1`
- L32 _private* const_ `const int SifRange = 0x0001`
- L33 _private* const_ `const int SifPage = 0x0002`
- L34 _private* const_ `const int SifPos = 0x0004`
- L36 _private* const_ `const int SifTrackpos = 0x0010`
- L37 _private* const_ `const int SifAll = (SifRange | SifPage | SifPos | SifTrackpos)`
- L39 _private* const_ `const int LvmGettopindex = 0x1000 + 39`
- L40 _private* const_ `const int LvmGetcountperpage = 0x1000 + 40`
- L43 _private method_ `private static extern int GetScrollInfo(IntPtr hwnd, int fnBar, Scrollinfo lpsi)` — attrs: `[DllImport("user32.dll")]`
- L46 _private method_ `private static extern int SetScrollInfo(IntPtr hwnd, int fnBar, Scrollinfo lpsi, int redraw)` — attrs: `[DllImport("user32.dll")]`
- L49 _private method_ `private static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)` — attrs: `[DllImport("user32.dll", CharSet = CharSet.Auto)]`
- L51 _public delegate_ `public delegate void OnScrollDelegate()`
- L53 _public event_ `public event OnScrollDelegate? OnScroll`
- L55-58 _public ctor_ `public BuildListControl()`
- L60-67 _public method_ `public int GetFirstVisibleIndex()`
- L69-76 _public method_ `public int GetVisibleItemsPerPage()`
- L78-99 _public method_ `public bool GetScrollPosition(out int scrollY)`
- L101-111 _public method_ `public void SetScrollPosition(int scrollY)`
- L113-126 _public method_ `public bool IsScrolledToLastPage()`
- L128-142 _protected method_ `protected override void WndProc(ref Message message)`
- L147-151 _public property_ `public override Font Font { get; set; }` — attrs: `[Browsable(false)] [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)] [AllowNull]`
- L153-159 _protected method_ `protected override void Dispose(bool disposing)`

#### class `UnrealGameSync.BuildListControl.Scrollinfo`  
`public class Scrollinfo`  
_public; L15-24_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L17 _public field_ `public int cbSize`
- L18 _public field_ `public int fMask`
- L19 _public field_ `public int nMin`
- L20 _public field_ `public int nMax`
- L21 _public field_ `public int nPage`
- L22 _public field_ `public int nPos`
- L23 _public field_ `public int nTrackPos`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/CustomListViewControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.CustomListViewWidget`  
`abstract class CustomListViewWidget`  
_internal*; L10-72_
- L12-16 _public property_ `public ListViewItem Item { get; set; }`
- L18 _private* field_ `Rectangle? _previousBounds`
- L20-24 _public property_ `public Cursor Cursor { get; set; }`
- L26-30 _public ctor_ `public CustomListViewWidget(ListViewItem item)`
- L32-35 _public method_ `public void Invalidate()`
- L37-40 _public method_ `public virtual bool RequiresLayout()`
- L42-52 _public method_ `public void ConditionalLayout(Control owner, Rectangle bounds)`
- L54-56 _public method_ `public virtual void OnMouseMove(Point location)`
- L58-60 _public method_ `public virtual void OnMouseLeave()`
- L62-64 _public method_ `public virtual void OnMouseDown(Point location)`
- L66-68 _public method_ `public virtual void OnMouseUp(Point location)`
- L70 _public method_ `public abstract void Layout(Graphics graphics, Rectangle bounds)`
- L71 _public method_ `public abstract void Render(Graphics graphics)`

#### class `UnrealGameSync.StatusLineListViewWidget`  
`class StatusLineListViewWidget : CustomListViewWidget`  
_internal*; L74-191_
- inherits: `CustomListViewWidget`
- L76 _public property_ `public StatusElementResources Resources { get; }`
- L77 _public property_ `public StatusLine Line { get; }`
- L79-82 _public property_ `public HorizontalAlignment HorizontalAlignment { get; set; }`
- L84 _private* field_ `Rectangle _bounds`
- L85 _private* field_ `StatusElement? _mouseDownElement`
- L86 _private* field_ `StatusElement? _mouseOverElement`
- L88-93 _public ctor_ `public StatusLineListViewWidget(ListViewItem item, StatusElementResources resources) : base(item)`
- L95-98 _public method_ `public override bool RequiresLayout()`
- L100-110 _public method_ `public override void OnMouseDown(Point location)`
- L112-128 _public method_ `public override void OnMouseUp(Point location)`
- L130-153 _public method_ `public override void OnMouseMove(Point location)`
- L155-164 _public method_ `public override void OnMouseLeave()`
- L166-183 _public method_ `public override void Layout(Graphics graphics, Rectangle bounds)`
- L185-190 _public method_ `public override void Render(Graphics graphics)`

#### class `UnrealGameSync.CustomListViewControl`  
`partial class CustomListViewControl : ListView, ICustomThemeHandler`  
_internal*; L193-522_
- inherits: `ListView, ICustomThemeHandler`
- L195 _private* field_ `readonly VisualStyleRenderer? _selectedItemRenderer`
- L196 _private* field_ `readonly VisualStyleRenderer? _trackedItemRenderer`
- L198 _public field_ `public int HoverItem = -1`
- L200 _private* field_ `CustomListViewWidget? _mouseOverWidget`
- L201 _private* field_ `CustomListViewWidget? _mouseDownWidget`
- L203 _private* field_ `Color _textColor = SystemColors.WindowText`
- L205-212 _public ctor_ `public CustomListViewControl()`
- L214-238 _protected method_ `protected void ConditionalLayoutWidget(CustomListViewWidget widget)`
- L240-247 _protected method_ `protected void ConditionalRedrawWidget(CustomListViewWidget widget)`
- L249-252 _protected method_ `protected CustomListViewWidget? FindWidget(Point location)`
- L254-273 _protected method_ `protected static CustomListViewWidget? FindWidget(ListViewHitTestInfo hitTest)`
- L275-292 _protected method_ `protected override void OnMouseLeave(EventArgs e)`
- L294-318 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L320-332 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L334-368 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L369-385 _public method_ `public void DrawText(Graphics graphics, Rectangle bounds, HorizontalAlignment textAlign, Color textColor, string text)`
- L387-398 _public method_ `public void DrawIcon(Graphics graphics, Rectangle bounds, Rectangle icon)`
- L400-406 _public method_ `public void DrawNormalSubItem(DrawListViewSubItemEventArgs e)`
- L408-426 _public method_ `public void DrawCustomSubItem(Graphics graphics, ListViewItem.ListViewSubItem subItem)`
- L428-442 _public method_ `public void DrawBackground(Graphics graphics, ListViewItem item)`
- L444-450 _public method_ `public void DrawDefaultBackground(Graphics graphics, Rectangle bounds)`
- L452-464 _public method_ `public void DrawSelectedBackground(Graphics graphics, Rectangle bounds)`
- L466-478 _public method_ `public void DrawTrackedBackground(Graphics graphics, Rectangle bounds)`
- L480-511 _protected method_ `protected override void OnDrawColumnHeader(DrawListViewColumnHeaderEventArgs e)`
- L513-521 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/ErrorPanel.cs` (UnrealGameSync)


#### class `UnrealGameSync.ErrorPanel`  
`class ErrorPanel : StatusPanel, IMainWindowTabPanel`  
_internal*; L8-66_
- inherits: `StatusPanel, IMainWindowTabPanel`
- L10-14 _public ctor_ `public ErrorPanel(UserSelectedProjectSettings inSelectedProject)`
- L16-19 _public method_ `public void Activate()`
- L21-23 _public method_ `public void Deactivate()`
- L25-28 _public method_ `public bool IsBusy()`
- L30-33 _public method_ `public bool CanClose()`
- L35-38 _public method_ `public bool CanSyncNow()`
- L40-42 _public method_ `public void SyncLatestChange()`
- L44-47 _public method_ `public bool CanLaunchEditor()`
- L49-51 _public method_ `public void LaunchEditor()`
- L53-55 _public method_ `public void UpdateSettings()`
- L57 _public property_ `public Color? TintColor => ...`
- L59 _public property_ `public Tuple<TaskbarState, float> DesiredTaskbarState => ...`
- L61-65 _public property_ `public UserSelectedProjectSettings SelectedProject { get; set; }`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/LogControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.LogControl`  
`public class LogControl : UserControl, ICustomThemeHandler`  
_public; L19-948_
- inherits: `UserControl, ICustomThemeHandler`
- L58 _private* method_ `static extern bool EnableScrollBar(IntPtr hWnd, ScrollBarType wSBflags, ScrollBarArrows wArrows)` — attrs: `[DllImport("user32.dll")]`
- L61 _private* method_ `static extern int SetScrollInfo(IntPtr hwnd, ScrollBarType fnBar, Scrollinfo lpsi, bool fRedraw)` — attrs: `[DllImport("user32.dll")]`
- L64 _private* method_ `static extern int GetScrollInfo(IntPtr hwnd, ScrollBarType fnBar, Scrollinfo lpsi)` — attrs: `[DllImport("user32.dll")]`
- L67 _private* method_ `static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)` — attrs: `[DllImport("user32.dll", CharSet = CharSet.Auto)]`
- L108 _private* field_ `readonly List<string> _lines = new List<string>()`
- L109 _private* field_ `int _maxLineLength`
- L111 _private* field_ `int _scrollLine`
- L112 _private* field_ `int _scrollLinesPerPage`
- L113 _private* field_ `bool _trackingScroll`
- L115 _private* field_ `int _scrollColumn`
- L116 _private* field_ `int _scrollColumnsPerPage`
- L118 _private* field_ `bool _isSelecting`
- L119 _private* field_ `TextSelection? _selection`
- L121 _private* field_ `Size _fontSize`
- L122 _private* field_ `Color _textColor = Color.Black`
- L123 _private* field_ `Color _warningColor = Color.FromArgb(128, 128, 0)`
- L124 _private* field_ `Color _errorColor = Color.FromArgb(189, 54, 47)`
- L126 _private* field_ `Timer? _selectionScrollTimer`
- L127 _private* field_ `int _autoScrollRate = 0`
- L129 _private* field_ `Timer? _updateTimer`
- L130 _private* field_ `ConcurrentQueue<string> _queuedLines = new ConcurrentQueue<string>()`
- L131 _private* field_ `FileStream? _logFileStream`
- L133-148 _public ctor_ `public LogControl()`
- L150-171 _protected method_ `protected override void OnCreateControl()`
- L173-190 _protected method_ `protected override void Dispose(bool disposing)`
- L192-229 _public method_ `public bool OpenFile(FileReference newLogFileName)`
- L231-238 _public method_ `public void CloseFile()`
- L240-269 _public method_ `public void Clear()`
- L271-275 _public method_ `public void ScrollToEnd()`
- L277-280 _public method_ `public void AppendLine(string line)`
- L282-322 _private method_ `private void Tick()`
- L324-373 _private method_ `private void AddLinesInternal(List<string> newLines)`
- L375-383 _private method_ `private bool IsTrackingLastLine()`
- L385-408 _private method_ `private void CopySelection()`
- L410-413 _private method_ `private void ContextMenu_CopySelection(object? sender, EventArgs e)`
- L415-418 _private method_ `private void ContextMenu_SelectAll(object? sender, EventArgs e)`
- L420-423 _private method_ `private void ContextMenu_Clear(object? sender, EventArgs e)`
- L425-432 _public method_ `public void SelectAll()`
- L434-456 _private* method_ `TextLocation PointToTextLocation(Point clientPoint)`
- L458-473 _protected method_ `protected override void OnResize(EventArgs e)`
- L475-486 _private* method_ `void UpdateVerticalScrollBarPageSize()`
- L488-505 _private* method_ `void UpdateScrollBarPageSize()`
- L507-512 _protected method_ `protected override void OnFontChanged(EventArgs e)`
- L514-520 _private method_ `private void UpdateFontMetrics()`
- L522-539 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L541-546 _protected method_ `protected override void OnMouseCaptureChanged(EventArgs e)`
- L548-563 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L565-577 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L579-586 _protected method_ `protected override void OnMouseWheel(MouseEventArgs e)`
- L588-598 _protected method_ `protected override bool IsInputKey(Keys key)`
- L600-641 _protected method_ `protected override void OnKeyDown(KeyEventArgs e)`
- L643-654 _private* method_ `void EndSelection()`
- L656-758 _protected method_ `protected override void OnScroll(ScrollEventArgs se)`
- L760-767 _private* method_ `void UpdateVerticalScrollPosition(int targetScrollPos, ref Scrollinfo scrollInfo)`
- L769-809 _protected method_ `protected override void OnPaint(PaintEventArgs e)`
- L811-823 _private* method_ `void ScrollWindow(int scrollDelta)`
- L825-858 _private method_ `private void SelectionScrollTimer_TimerElapsed(object? sender, EventArgs args)`
- L860-936 _protected method_ `protected void ClipSelectionToLine(int lineIdx, out int selectMinIdx, out int selectMaxIdx)`
- L938-947 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

#### enum `UnrealGameSync.LogControl.ScrollInfoMask`  
`public enum ScrollInfoMask : int`  
_public; L22-30_
- attrs: `[Flags]`
- inherits: `int`
- L24 _public* enumerator_ `SifRange = 0x1`
- L25 _public* enumerator_ `SifPage = 0x2`
- L26 _public* enumerator_ `SifPos = 0x4`
- L27 _public* enumerator_ `SifDisablenoscroll = 0x8`
- L28 _public* enumerator_ `SifTrackpos = 0x10`
- L29 _public* enumerator_ `SifAll = SifRange | SifPage | SifPos | SifTrackpos`

#### class `UnrealGameSync.LogControl.Scrollinfo`  
`class Scrollinfo`  
_private*; L33-42_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L35 _public field_ `public int cbSize`
- L36 _public field_ `public ScrollInfoMask fMask`
- L37 _public field_ `public int nMin`
- L38 _public field_ `public int nMax`
- L39 _public field_ `public int nPage`
- L40 _public field_ `public int nPos`
- L41 _public field_ `public int nTrackPos`

#### enum `UnrealGameSync.LogControl.ScrollBarType`  
`enum ScrollBarType : int`  
_private*; L44-50_
- inherits: `int`
- L46 _public* enumerator_ `SbHorz = 0`
- L47 _public* enumerator_ `SbVert = 1`
- L48 _public* enumerator_ `SbControl = 2`
- L49 _public* enumerator_ `SbBoth = 3`

#### enum `UnrealGameSync.LogControl.ScrollBarArrows`  
`enum ScrollBarArrows : uint`  
_private*; L52-55_
- inherits: `uint`
- L54 _public* enumerator_ `EsbEnableBoth = 0`

#### struct `UnrealGameSync.LogControl.TextLocation`  
`struct TextLocation`  
_private*; L69-84_
- L71 _public field_ `public readonly int LineIdx`
- L72 _public field_ `public readonly int ColumnIdx`
- L74-78 _public ctor_ `public TextLocation(int inLineIdx, int inColumnIdx)`
- L80-83 _public method_ `public override string ToString()`

#### class `UnrealGameSync.LogControl.TextSelection`  
`class TextSelection`  
_private*; L86-106_
- L88 _public field_ `public TextLocation Start`
- L89 _public field_ `public TextLocation End`
- L91-95 _public ctor_ `public TextSelection(TextLocation inStart, TextLocation inEnd)`
- L97-100 _public method_ `public bool IsEmpty()`
- L102-105 _public method_ `public override string ToString()`

#### class `UnrealGameSync.LogControlTextWriter`  
`public class LogControlTextWriter : ILogger`  
_public; L950-988_
- inherits: `ILogger`
- L952 _private* const_ `const LogLevel MinLogLevel = LogLevel.Information`
- L959 _private* field_ `readonly LogControl _logControl`
- L961-964 _public ctor_ `public LogControlTextWriter(LogControl inLogControl)`
- L966-983 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)`
- L985 _public method_ `public bool IsEnabled(LogLevel logLevel)`
- L987 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull`

#### class `UnrealGameSync.LogControlTextWriter.NullDisposable`  
`class NullDisposable : IDisposable`  
_private*; L954-957_
- inherits: `IDisposable`
- L956 _public method_ `public void Dispose()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/LogSplitContainer.cs` (UnrealGameSync)


#### class `UnrealGameSync.LogSplitContainer`  
`public class LogSplitContainer : SplitContainer, ICustomThemeHandler`  
_public; L10-331_
- inherits: `SplitContainer, ICustomThemeHandler`
- L12 _private* const_ `const int WmSetcursor = 0x0020`
- L14 _private* field_ `bool _hoverOverClose`
- L15 _private* field_ `bool _mouseDownOverClose`
- L16 _private* field_ `bool _logVisible = true`
- L17 _private* field_ `bool _splitterMoved = false`
- L18 _private* field_ `bool _changingLogVisibility = false`
- L20 _private* const_ `const int CaptionPadding = 4`
- L22 _private* field_ `int _logHeight = 200`
- L24 _private* field_ `Color _textColor = SystemColors.ControlText`
- L25 _private* field_ `Color _borderColor = SystemColors.ControlDark`
- L26 _private* field_ `Color _activeCaption = SystemColors.ActiveCaption`
- L27 _private* field_ `Color _inactiveCaption = SystemColors.InactiveCaption`
- L28 _private* field_ `Color _inactiveCaptionText = SystemColors.InactiveCaptionText`
- L29 _private* field_ `readonly InvertibleImage _logIcon = new InvertibleImage(Properties.Resources.Log, false)`
- L31 _public event_ `public event Action<bool>? OnVisibilityChanged`
- L35-39 _public property_ `public string Caption { get; set; }` — attrs: `[Browsable(true)] [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L41-49 _public ctor_ `public LogSplitContainer()`
- L51 _protected property_ `protected static Font CaptionFont => ...`
- L53-61 _protected method_ `protected override void Dispose(bool disposing)`
- L63-68 _protected method_ `protected override void OnCreateControl()`
- L70-77 _protected method_ `protected override void OnKeyUp(KeyEventArgs e)`
- L79-89 _private method_ `private void OnSplitterMoved(object? obj, EventArgs args)`
- L91-118 _public method_ `public void SetLogVisibility(bool visible)`
- L120-136 _private method_ `private void UpdateMetrics()`
- L138-152 _protected method_ `protected override void OnSizeChanged(EventArgs e)`
- L154-162 _protected method_ `protected override void OnLayout(LayoutEventArgs e)`
- L164-167 _public method_ `public bool IsLogVisible()`
- L169-174 _protected method_ `protected override void OnFontChanged(EventArgs e)`
- L176-186 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L188-198 _protected method_ `protected override void OnMouseLeave(EventArgs e)`
- L200-212 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L214-224 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L226 _protected property_ `protected override bool ShowFocusCues => ...`
- L228-233 _protected method_ `protected override void OnResize(EventArgs e)`
- L235-237 _protected method_ `protected override void OnPaintBackground(PaintEventArgs e)`
- L239-298 _protected method_ `protected override void OnPaint(PaintEventArgs e)`
- L300-314 _protected method_ `protected override void WndProc(ref Message message)`
- L316-328 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`
- L330 _private* property_ `Rectangle CloseButtonRectangle => ...`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/ReadOnlyCheckbox.cs` (UnrealGameSync)


#### class `UnrealGameSync.Controls.ReadOnlyCheckbox`  
`public class ReadOnlyCheckbox : CheckBox`  
_public; L8-48_
- inherits: `CheckBox`
- L10 _private field_ `private bool _readOnly = false`
- L13-22 _public property_ `public bool ReadOnly { get; set; }` — attrs: `[System.ComponentModel.Category("Behavior")] [System.ComponentModel.DefaultValue(false)]`
- L24-31 _protected method_ `protected override void OnMouseEnter(EventArgs e)`
- L32-39 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L40-47 _protected method_ `protected override void OnKeyDown(KeyEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/RichTextBox41.cs` (UnrealGameSync)


#### class `UnrealGameSync.RichTextBox41`  
`class RichTextBox41 : RichTextBox`  
_internal*; L9-26_
- inherits: `RichTextBox`
- L12 _private* method_ `static extern IntPtr LoadLibrary(string lpFileName)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Auto)]`
- L14-25 _protected property_ `protected override CreateParams CreateParams { get; }`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/StatusPanel.cs` (UnrealGameSync)


#### class `UnrealGameSync.NativeCursors`  
`static class NativeCursors`  
_internal*; L15-23_
- L18 _public method_ `public static extern IntPtr LoadCursor(IntPtr hInstance, IntPtr lpCursorName)` — attrs: `[DllImport("user32.dll")]`
- L20 _private* const_ `const int IdcHand = 32649`
- L22 _public field_ `public static readonly Cursor Hand = new Cursor(LoadCursor(IntPtr.Zero, new IntPtr(IdcHand)))`

#### class `UnrealGameSync.StatusElementResources`  
`class StatusElementResources : IDisposable`  
_internal*; L25-63_
- inherits: `IDisposable`
- L27 _private* field_ `readonly Dictionary<FontStyle, Font> _fontCache = ...`
- L27 _private* field_ `readonly Dictionary< _fontCache = new Dictionary<FontStyle, Font>()`
- L28 _public field_ `public readonly Font BadgeFont`
- L30-38 _public ctor_ `public StatusElementResources(Font baseFont)`
- L40-51 _public method_ `public void Dispose()`
- L53-62 _public method_ `public Font FindOrAddFont(FontStyle style)`

#### class `UnrealGameSync.StatusElement`  
`abstract class StatusElement`  
_internal*; L65-91_
- L67 _public property_ `public Cursor Cursor { get; set; }`
- L68 _public property_ `public bool MouseOver { get; set; }`
- L69 _public property_ `public bool MouseDown { get; set; }`
- L70 _public property_ `public Rectangle Bounds { get; set; }`
- L72-76 _public property_ `public string? ToolTip { get; set; }`
- L78-83 _public method_ `public Point Layout(Graphics graphics, Point location, StatusElementResources resources)`
- L85 _public method_ `public abstract Size Measure(Graphics graphics, StatusElementResources resources)`
- L86 _public method_ `public abstract void Draw(Graphics grahpics, StatusElementResources resources)`
- L88-90 _public method_ `public virtual void OnClick(Point location)`

#### class `UnrealGameSync.IconStatusElement`  
`class IconStatusElement : StatusElement`  
_internal*; L93-111_
- inherits: `StatusElement`
- L95 _private* field_ `readonly Image _icon`
- L97-100 _public ctor_ `public IconStatusElement(Image inIcon)`
- L102-105 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L107-110 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.IconStripStatusElement`  
`class IconStripStatusElement : StatusElement`  
_internal*; L113-139_
- inherits: `StatusElement`
- L115 _private* field_ `readonly Image _strip`
- L116 _private* field_ `readonly Size _iconSize`
- L117 _private* field_ `readonly int _index`
- L118 _private* field_ `readonly bool _applyDpiScaling`
- L120-126 _public ctor_ `public IconStripStatusElement(Image strip, Size iconSize, int index, bool applyDpiScaling = true)`
- L128-133 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L135-138 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.TextStatusElement`  
`class TextStatusElement : StatusElement`  
_internal*; L141-163_
- inherits: `StatusElement`
- L143 _private* field_ `readonly string _text`
- L144 _private* field_ `readonly Color _color`
- L145 _private* field_ `readonly FontStyle _style`
- L147-152 _public ctor_ `public TextStatusElement(string inText, Color inColor, FontStyle inStyle)`
- L154-157 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L159-162 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.LinkStatusElement`  
`class LinkStatusElement : StatusElement`  
_internal*; L165-202_
- inherits: `StatusElement`
- L167 _private* field_ `readonly string _text`
- L168 _private* field_ `readonly FontStyle _style`
- L169 _private* field_ `readonly Action<Point, Rectangle> _linkAction`
- L169 _private* field_ `readonly Action< _linkAction`
- L171-177 _public ctor_ `public LinkStatusElement(string text, FontStyle style, Action<Point, Rectangle> linkAction)`
- L179-182 _public method_ `public override void OnClick(Point location)`
- L184-187 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L189-201 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.BadgeStatusElement`  
`class BadgeStatusElement : StatusElement`  
_internal*; L204-281_
- inherits: `StatusElement`
- L206 _private* field_ `readonly string _name`
- L207 _private* field_ `readonly Color _backgroundColor`
- L208 _private* field_ `readonly Color _hoverBackgroundColor`
- L209 _private* field_ `readonly Action<Point, Rectangle>? _clickAction`
- L209 _private* field_ `readonly Action< _clickAction`
- L211-214 _public property_ `public bool MergeLeft { get; set; }`
- L216-219 _public property_ `public bool MergeRight { get; set; }`
- L221-239 _public ctor_ `public BadgeStatusElement(string inName, Color inBackgroundColor, Action<Point, Rectangle>? inClickAction)`
- L241-247 _public method_ `public override void OnClick(Point location)`
- L249-254 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L256-280 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.ProgressBarStatusElement`  
`class ProgressBarStatusElement : StatusElement`  
_internal*; L283-311_
- inherits: `StatusElement`
- L285 _private* field_ `readonly float _progress`
- L287-290 _public ctor_ `public ProgressBarStatusElement(float inProgress)`
- L292-296 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L298-310 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.StatusLine`  
`class StatusLine`  
_internal*; L313-452_
- L315 _private* field_ `bool _modified`
- L316 _private* field_ `readonly List<StatusElement> _elements = new List<StatusElement>()`
- L318-321 _public ctor_ `public StatusLine()`
- L323-327 _public property_ `public float LineHeight { get; set; }`
- L329-333 _public property_ `public Rectangle Bounds { get; set; }`
- L335-338 _public method_ `public bool RequiresLayout()`
- L340-344 _public method_ `public void Clear()`
- L346-350 _public property_ `public string? ToolTip { get; set; }`
- L352-357 _public method_ `public void Add(StatusElement element, string? toolTip = null)`
- L359-362 _public method_ `public void AddIcon(Image inIcon, string? toolTip = null)`
- L364-367 _public method_ `public void AddIcon(Image inStrip, Size inIconSize, int inIndex, bool applyDpiScaling = true, string? toolTip = null)`
- L369-373 _public method_ `public void AddText(string inText, FontStyle inStyle = FontStyle.Regular, string? toolTip = null)`
- L375-378 _public method_ `public void AddText(string inText, Color inColor, FontStyle inStyle = FontStyle.Regular, string? toolTip = null)`
- L380-383 _public method_ `public void AddLink(string inText, FontStyle inStyle, Action inLinkAction, string? toolTip = null)`
- L385-388 _public method_ `public void AddLink(string inText, FontStyle inStyle, Action<Point, Rectangle> inLinkAction, string? toolTip = null)`
- L390-407 _public method_ `public void AddBadge(string inText, Color inBackgroundColor, Action<Point, Rectangle>? inClickAction, string? toolTip = null)`
- L409-412 _public method_ `public void AddProgressBar(float progress, string? toolTip = null)`
- L414-429 _public method_ `public bool HitTest(Point location, [NotNullWhen(true)] out StatusElement? outElement)`
- L431-443 _public method_ `public void Layout(Graphics graphics, Point location, StatusElementResources resources)`
- L445-451 _public method_ `public void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.StatusPanel`  
`class StatusPanel : Panel, ICustomThemeHandler`  
_internal*; L454-963_
- inherits: `Panel, ICustomThemeHandler`
- L456 _private* const_ `const float LineSpacing = 1.35f`
- L457 _private* const_ `const int InfoMargin = 15`
- L458 _private* const_ `const int TopMargin = 10`
- L460 _private* field_ `InvertibleImage _projectLogo = new InvertibleImage(Properties.Resources.DefaultProjectLogo, false)`
- L461 _private* field_ `Rectangle _projectLogoBounds`
- L462 _private* field_ `StatusElementResources? _resources`
- L463 _private* field_ `readonly List<StatusLine> _lines = new List<StatusLine>()`
- L464 _private* field_ `readonly List<StatusLine> _infoLines = new List<StatusLine>()`
- L465 _private* field_ `StatusLine? _caption`
- L466 _private* field_ `Pen? _alertDividerPen`
- L467 _private* field_ `int _alertDividerY`
- L468 _private* field_ `StatusLine? _alert`
- L469 _private* field_ `InvertibleColor? _tintColor`
- L470 _private* field_ `Point? _mouseOverLocation`
- L471 _private* field_ `StatusElement? _mouseOverElement`
- L472 _private* field_ `Point? _mouseDownLocation`
- L473 _private* field_ `StatusElement? _mouseDownElement`
- L474 _private* field_ `int _contentWidth = 400`
- L475 _private* field_ `int _suspendDisplayCount`
- L476 _private* field_ `readonly System.Windows.Forms.ToolTip _toolTip = new System.Windows.Forms.ToolTip()`
- L477 _private* field_ `string? _currentToolTip = null`
- L479 _private field_ `private bool _showInfoLines = true`
- L481-491 _public ctor_ `public StatusPanel()`
- L493-496 _public method_ `public void SuspendDisplay()`
- L498-501 _public method_ `public void ResumeDisplay()`
- L503-511 _public method_ `public void SetContentWidth(int newContentWidth)`
- L513-531 _protected method_ `protected override void Dispose(bool disposing)`
- L533-541 _private method_ `private void ResetFontCache()`
- L543-549 _public method_ `public void SetProjectLogo(Image newProjectLogo, bool dispose)`
- L551-557 _public method_ `public void Clear()`
- L559-583 _public method_ `public void Set(IEnumerable<StatusLine> newLines, IEnumerable<StatusLine> newInfoLines, StatusLine? newCaption, StatusLine? newAlert, Color? newTintColor)`
- L585-605 _protected method_ `protected void InvalidateElements()`
- L607-650 _protected method_ `protected bool HitTest(Point location, [NotNullWhen(true)] out StatusElement? outElement, out StatusLine? outLine)`
- L652-658 _protected method_ `protected override void OnFontChanged(EventArgs e)`
- L660-666 _protected method_ `protected void LayoutElements()`
- L668-754 _protected method_ `protected void LayoutElements(Graphics graphics)`
- L756-761 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L763-771 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L773-783 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L785-791 _protected method_ `protected override void OnMouseLeave(EventArgs e)`
- L793-799 _protected method_ `protected override void OnResize(EventArgs eventargs)`
- L801-822 _protected method_ `protected override void OnPaintBackground(PaintEventArgs e)`
- L824-855 _protected method_ `protected override void OnPaint(PaintEventArgs e)`
- L857-925 _protected method_ `protected void SetMouseOverLocation(Point? newMouseOverLocation)`
- L927-954 _protected method_ `protected void SetMouseDownLocation(Point? newMouseDownLocation)`
- L956-962 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/SyncFilterControl.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Controls.SyncFilterControl`  
`partial class SyncFilterControl`  
_internal*; L5-385_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-361 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L365 _private field_ `private System.Windows.Forms.GroupBox ViewGroupBox`
- L366 _private field_ `private System.Windows.Forms.GroupBox CategoriesGroupBox`
- L367 _public field_ `public System.Windows.Forms.CheckedListBox CategoriesCheckList`
- L368 _private field_ `private System.Windows.Forms.SplitContainer SplitContainer`
- L369 _private field_ `private System.Windows.Forms.LinkLabel SyntaxButton`
- L370 _private field_ `private System.Windows.Forms.DataGridView ViewDataGrid`
- L371 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L372 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L373 _public field_ `public System.Windows.Forms.CheckBox SyncAllProjects`
- L374 _public field_ `public System.Windows.Forms.CheckBox IncludeAllProjectsInSolution`
- L375 _public field_ `public System.Windows.Forms.CheckBox GenerateUprojectSpecificSolution`
- L376 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L377 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4`
- L378 _public field_ `public CheckBox SyncLocalProjects`
- L379 _private field_ `private ToolTip CategoriesToolTip`
- L380 _private field_ `private TableLayoutPanel CustomViewTableLayoutPanel`
- L381 _private field_ `private FlowLayoutPanel flowLayoutPanel1`
- L382 _private field_ `private Button CopyCustomViewsToClipboard`
- L383 _private field_ `private Button PasteCustomViewsToClipboard`
- L384 _private field_ `private Button ClearCustomViewsToClipboard`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/SyncFilterControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.Controls.SyncFilterControl`  
`public partial class SyncFilterControl : UserControl`  
_public; L13-284_
- inherits: `UserControl`
- L27 _private field_ `private readonly BindingList<ViewItem> _views = new BindingList<ViewItem>()`
- L29 _private field_ `private int _categoriesCheckListHoverIndex = -1`
- L30 _private property_ `private Timer _categoriesCheckListooltipTimer { get; }`
- L43-66 _public ctor_ `public SyncFilterControl()`
- L68-88 _private method_ `private void CheckedListBox_MouseMove(object? sender, MouseEventArgs e)`
- L90-108 _private method_ `private void TooltipTimer_Tick(object? sender, EventArgs e)`
- L110-113 _private* method_ `void Views_AddingNew(object? sender, AddingNewEventArgs e)`
- L115-125 _private method_ `private void ViewDataGrid_CellBeginEdit(object? sender, DataGridViewCellCancelEventArgs e)`
- L127-133 _private method_ `private void ViewDataGrid_UserDeletingRow(object? sender, DataGridViewRowCancelEventArgs e)`
- L135-139 _private method_ `private void ViewDataGrid_DefaultValuesNeeded(object? sender, System.Windows.Forms.DataGridViewRowEventArgs e)`
- L141-145 _private method_ `private void SyntaxButton_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L147-188 _public method_ `public void SetView(string[] views)`
- L190-207 _public method_ `public string[] GetView()`
- L208-239 _private method_ `private void CopyCustomViewsToClipboard_Click(object sender, EventArgs e)`
- L241-278 _private method_ `private async void PasteCustomViewsToClipboard_Click(object sender, EventArgs e)`
- L280-283 _private method_ `private void ClearCustomViewsToClipboard_Click(object sender, EventArgs e)`

#### class `UnrealGameSync.Controls.SyncFilterControl.ViewItem`  
`private class ViewItem`  
_private; L15-25_
- L17 _public property_ `public bool Locked { get; set; }`
- L18 _public property_ `public string Value { get; set; }`
- L20-24 _public ctor_ `public ViewItem(bool locked, string value)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/TabControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.TabControl`  
`class TabControl : Control, ICustomThemeHandler`  
_internal*; L12-654_
- inherits: `Control, ICustomThemeHandler`
- L14 _private* const_ `const int TabPadding = 13`
- L15 _private* const_ `const int TabCloseButtonWidth = 8 + 13`
- L51 _private* field_ `readonly List<TabData> _tabs = new List<TabData>()`
- L52 _private* field_ `int _selectedTabIdx`
- L53 _private* field_ `int _hoverTabIdx`
- L54 _private* field_ `int _highlightTabIdx`
- L55 _private* field_ `bool _isHoveringCloseBtn = false`
- L56 _private* field_ `TabDragData? _dragState`
- L57 _private* field_ `Color _textColor = SystemColors.WindowText`
- L58 _private* field_ `Color _selectedColor = SystemColors.HotTrack`
- L59 _private* field_ `Color _borderColor = SystemColors.Window`
- L60 _private* field_ `Color _hoverColor = SystemColors.Window`
- L61 _private* field_ `Color _hoverStripeColor = Color.FromArgb(192, 192, 192)`
- L62 _private* field_ `Color _closeColor = SystemColors.HotTrack`
- L63 _private* field_ `Color _closeColorHovered = Color.FromArgb(SystemColors.HotTrack.B, SystemColors.HotTrack.G, SystemColors.HotTrack.R)`
- L65 _public delegate_ `public delegate void OnTabChangedDelegate(object? newTabData)`
- L66 _public event_ `public event OnTabChangedDelegate? OnTabChanged`
- L68 _public delegate_ `public delegate void OnNewTabClickDelegate(Point location, MouseButtons buttons)`
- L69 _public event_ `public event OnNewTabClickDelegate? OnNewTabClick`
- L71 _public delegate_ `public delegate void OnTabClickedDelegate(object? tabData, Point location, MouseButtons buttons)`
- L72 _public event_ `public event OnTabClickedDelegate? OnTabClicked`
- L74 _public delegate_ `public delegate bool OnTabClosingDelegate(object tabData)`
- L75 _public event_ `public event OnTabClosingDelegate? OnTabClosing`
- L77 _public delegate_ `public delegate void OnTabClosedDelegate(object tabData)`
- L78 _public event_ `public event OnTabClosedDelegate? OnTabClosed`
- L80 _public delegate_ `public delegate void OnTabReorderDelegate()`
- L81 _public event_ `public event OnTabReorderDelegate? OnTabReorder`
- L83 _public delegate_ `public delegate void OnButtonClickDelegate(int buttonIdx, Point location, MouseButtons buttons)`
- L84 _public event_ `public event OnButtonClickDelegate? OnButtonClick`
- L86-93 _public ctor_ `public TabControl()`
- L95-98 _public method_ `public void LockHover()`
- L100-104 _public method_ `public void UnlockHover()`
- L106-118 _public method_ `public int FindTabIndex(object data)`
- L120-139 _public method_ `public void SetHighlight(int tabIdx, Tuple<Color, float>? highlight)`
- L141-148 _public method_ `public void SetTint(int tabIdx, Color? tintColor)`
- L150-166 _public method_ `public int InsertTab(int insertIdx, string name, object data, Color? tintColor)`
- L168-171 _public method_ `public int GetTabCount()`
- L173-178 _public method_ `public void SetTabName(int tabIdx, string name)`
- L180-183 _public method_ `public object GetTabData(int tabIdx)`
- L185-188 _public method_ `public void SetTabData(int tabIdx, object data)`
- L190-193 _public method_ `public int GetSelectedTabIndex()`
- L195-198 _public method_ `public object GetSelectedTabData()`
- L200-206 _public method_ `public void SelectTab(int tabIdx)`
- L208-225 _private method_ `private void ForceSelectTab(int tabIdx)`
- L227-268 _public method_ `public void RemoveTab(int tabIdx)`
- L270-334 _private* method_ `void LayoutTabs()`
- L336-342 _protected method_ `protected override void OnResize(EventArgs e)`
- L344-395 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L397-413 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L415-482 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L484-493 _protected method_ `protected override void OnMouseCaptureChanged(EventArgs e)`
- L495-601 _protected method_ `protected override void OnPaint(PaintEventArgs e)`
- L603-628 _private* method_ `void DrawBackground(Graphics graphics, TabData tab, Brush backgroundBrush, Brush stripeBrush, Tuple<Color, float>? highlight)`
- L630-635 _private* method_ `void DrawText(Graphics graphics, TabData tab)`
- L637-653 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

#### class `UnrealGameSync.TabControl.TabData`  
`class TabData`  
_private*; L17-33_
- L19 _public field_ `public string _name`
- L20 _public field_ `public object _data`
- L21 _public field_ `public int _minX`
- L22 _public field_ `public int _width`
- L23 _public field_ `public int _closeButtonWidth`
- L24 _public field_ `public Size _textSize`
- L25 _public field_ `public Tuple<Color, float>? _highlight`
- L25 _public field_ `public Tuple< _highlight`
- L26 _public field_ `public Color? _tintColor`
- L28-32 _public ctor_ `public TabData(string name, object data)`

#### class `UnrealGameSync.TabControl.TabDragData`  
`class TabDragData`  
_private*; L35-49_
- L37 _public field_ `public TabData _tab`
- L38 _public field_ `public int _initialIdx`
- L39 _public field_ `public int _mouseX`
- L40 _public field_ `public int _relativeMouseX`
- L42-48 _public ctor_ `public TabDragData(TabData tab, int initialIdx, int mouseX, int relativeMouseX)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/TextBoxWithCueBanner.cs` (UnrealGameSync)


#### class `UnrealGameSync.TextBoxWithCueBanner`  
`class TextBoxWithCueBanner : TextBox`  
_internal*; L10-43_
- inherits: `TextBox`
- L12 _private const_ `private const int EmSetcuebanner = 0x1501`
- L15 _private method_ `private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wparam, string lparam)` — attrs: `[DllImport("user32.dll", CharSet = CharSet.Unicode)]`
- L17 _private field_ `private string _cueBannerValue = String.Empty`
- L20-28 _public property_ `public string CueBanner { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L30-36 _private method_ `private void UpdateCueBanner()`
- L38-42 _protected method_ `protected override void OnHandleCreated(EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/WorkspaceControl.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.WorkspaceControl`  
`partial class WorkspaceControl`  
_internal*; L6-1479_
- L11 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L19-1327 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L1331 _private field_ `private BuildListControl BuildList`
- L1332 _private field_ `private LogControl SyncLog`
- L1333 _private field_ `private System.Windows.Forms.ColumnHeader IconColumn`
- L1334 _private field_ `private System.Windows.Forms.ColumnHeader TimeColumn`
- L1335 _private field_ `private System.Windows.Forms.ColumnHeader DescriptionColumn`
- L1336 _private field_ `private System.Windows.Forms.ColumnHeader StatusColumn`
- L1337 _private field_ `private System.Windows.Forms.ColumnHeader ChangeColumn`
- L1338 _private field_ `private System.Windows.Forms.ColumnHeader AuthorColumn`
- L1339 _private field_ `private System.Windows.Forms.Button OptionsButton`
- L1340 _private field_ `private System.Windows.Forms.ContextMenuStrip OptionsContextMenu`
- L1341 _private field_ `private UnrealGameSync.Controls.ReadOnlyCheckbox RunAfterSyncCheckBox`
- L1342 _private field_ `private UnrealGameSync.Controls.ReadOnlyCheckbox BuildAfterSyncCheckBox`
- L1343 _private field_ `private System.Windows.Forms.Label AfterSyncingLabel`
- L1344 _private field_ `private System.Windows.Forms.ContextMenuStrip BuildListContextMenu`
- L1345 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Cancel`
- L1346 _private field_ `private LogSplitContainer Splitter`
- L1347 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_MoreInfo`
- L1348 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_AddStar`
- L1349 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildListContextMenu_CustomTool_End`
- L1350 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_MarkGood`
- L1351 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_MarkBad`
- L1352 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_StartInvestigating`
- L1353 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Sync`
- L1354 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator4`
- L1355 _private field_ `private System.Windows.Forms.NotifyIcon NotifyIcon`
- L1356 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_RemoveStar`
- L1357 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_FinishInvestigating`
- L1358 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator1`
- L1359 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_LaunchEditor`
- L1360 _private field_ `private System.Windows.Forms.ToolTip BuildListToolTip`
- L1361 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_AutoResolveConflicts`
- L1362 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_AlwaysClobberFiles`
- L1363 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_AlwaysDeleteFiles`
- L1364 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_EditorArguments`
- L1365 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_OpenVisualStudio`
- L1366 _private field_ `private System.Windows.Forms.Panel panel1`
- L1367 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Build`
- L1368 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_GenerateProjectFiles`
- L1369 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_EditorBuildConfiguration`
- L1370 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_BuildConfig_Debug`
- L1371 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_BuildConfig_DebugGame`
- L1372 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_BuildConfig_Development`
- L1373 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Rebuild`
- L1374 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_WithdrawReview`
- L1375 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_ScheduledSync`
- L1376 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_LeaveComment`
- L1377 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator7`
- L1378 _private field_ `private System.Windows.Forms.ColumnHeader CISColumn`
- L1379 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_EditComment`
- L1380 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L1381 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L1382 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L1383 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildListContextMenu_TimeZoneSeparator`
- L1384 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_ShowServerTimes`
- L1385 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_ShowLocalTimes`
- L1386 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_CustomizeBuildSteps`
- L1387 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TimeZone`
- L1388 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TimeZone_Local`
- L1389 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TimeZone_PerforceServer`
- L1390 _private field_ `private UnrealGameSync.Controls.ReadOnlyCheckbox OpenSolutionAfterSyncCheckBox`
- L1391 _private field_ `private System.Windows.Forms.TableLayoutPanel StatusLayoutPanel`
- L1392 _private field_ `private StatusPanel StatusPanel`
- L1393 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_SyncContentOnly`
- L1394 _private field_ `private System.Windows.Forms.ContextMenuStrip MoreToolsContextMenu`
- L1395 _private field_ `private System.Windows.Forms.ToolStripMenuItem MoreToolsContextMenu_CleanWorkspace`
- L1396 _private field_ `private System.Windows.Forms.ToolStripMenuItem MoreToolsContextMenu_UpdateTools`
- L1397 _private field_ `private System.Windows.Forms.ToolStripSeparator MoreActionsContextMenu_CustomToolSeparator`
- L1398 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator3`
- L1399 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator5`
- L1400 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator6`
- L1401 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_Diagnostics`
- L1402 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_SyncFilter`
- L1403 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_Presets`
- L1404 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_SyncOnlyThisChange`
- L1405 _private field_ `private System.Windows.Forms.ContextMenuStrip SyncContextMenu`
- L1406 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator8`
- L1407 _private field_ `private System.Windows.Forms.ToolStripMenuItem SyncContexMenu_EnterChangelist`
- L1408 _private field_ `private System.Windows.Forms.ContextMenuStrip StreamContextMenu`
- L1409 _private field_ `private System.Windows.Forms.ToolStripMenuItem tabLabelsToolStripMenuItem`
- L1410 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TabNames_Stream`
- L1411 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TabNames_WorkspaceName`
- L1412 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TabNames_WorkspaceRoot`
- L1413 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_TabNames_ProjectFile`
- L1414 _private field_ `private System.Windows.Forms.ContextMenuStrip RecentMenu`
- L1415 _private field_ `private System.Windows.Forms.ToolStripSeparator RecentMenu_Separator`
- L1416 _private field_ `private System.Windows.Forms.ToolStripMenuItem RecentMenu_ClearList`
- L1417 _private field_ `private System.Windows.Forms.ToolStripMenuItem RecentMenu_Browse`
- L1418 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator9`
- L1419 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildListContextMenu_CustomTool_Start`
- L1420 _private field_ `private System.Windows.Forms.ToolStripMenuItem showChangesToolStripMenuItem`
- L1421 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_ShowChanges_ShowUnreviewed`
- L1422 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_ShowChanges_ShowAutomated`
- L1423 _private field_ `private System.Windows.Forms.ColumnHeader TypeColumn`
- L1424 _private field_ `private System.Windows.Forms.ContextMenuStrip BuildListMultiContextMenu`
- L1425 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListMultiContextMenu_Bisect`
- L1426 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildListMultiContextMenu_TimeZoneSeparator`
- L1427 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListMultiContextMenu_ShowServerTimes`
- L1428 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListMultiContextMenu_ShowLocalTimes`
- L1429 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Bisect_Pass`
- L1430 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Bisect_Fail`
- L1431 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Bisect_Exclude`
- L1432 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Bisect_Include`
- L1433 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildListContextMenu_Bisect_Separator`
- L1434 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_ApplicationSettings`
- L1435 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator2`
- L1436 _private field_ `private System.Windows.Forms.Button FilterButton`
- L1437 _private field_ `private System.Windows.Forms.ContextMenuStrip FilterContextMenu`
- L1438 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Default`
- L1439 _private field_ `private System.Windows.Forms.ToolStripSeparator FilterContextMenu_BeforeBadgeSeparator`
- L1440 _private field_ `private System.Windows.Forms.ToolStripSeparator FilterContextMenu_AfterBadgeSeparator`
- L1441 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_ShowBuildMachineChanges`
- L1442 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Badges`
- L1443 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Type`
- L1444 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Type_Code`
- L1445 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Type_Content`
- L1446 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Type_UEFN`
- L1447 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Type_ShowAll`
- L1448 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Robomerge`
- L1449 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Robomerge_ShowAll`
- L1450 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Robomerge_ShowBadged`
- L1451 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Robomerge_ShowNone`
- L1452 _private field_ `private System.Windows.Forms.ToolStripSeparator FilterContextMenu_AfterRobomergeShowSeparator`
- L1453 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Robomerge_Annotate`
- L1454 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterContextMenu_Author`
- L1455 _private field_ `private System.Windows.Forms.ToolStripTextBox FilterContextMenu_Author_Name`
- L1456 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator10`
- L1457 _private field_ `private System.Windows.Forms.ContextMenuStrip BuildHealthContextMenu`
- L1458 _private field_ `private System.Windows.Forms.ContextMenuStrip BadgeContextMenu`
- L1459 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildHealthContextMenu_MaxSeparator`
- L1460 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildHealthContextMenu_Settings`
- L1461 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildHealthContextMenu_Browse`
- L1462 _private field_ `private System.Windows.Forms.ToolStripSeparator BuildHealthContextMenu_MinSeparator`
- L1463 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_SyncPrecompiledBinaries`
- L1464 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_SyncPrecompiledBinariesProjectOverride`
- L1465 _private field_ `private System.Windows.Forms.ToolStripMenuItem disabledToolStripMenuItem`
- L1466 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator11`
- L1467 _private field_ `private System.Windows.Forms.ToolStripMenuItem editorToolStripMenuItem`
- L1468 _private field_ `private System.Windows.Forms.ToolStripMenuItem editorPhysXToolStripMenuItem`
- L1469 _private field_ `private System.IO.FileSystemWatcher EditorConfigWatcher`
- L1470 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_ViewInSwarm`
- L1471 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_CopyChangelistNumber`
- L1472 _private field_ `private System.Windows.Forms.ColumnHeader ReviewerColumn`
- L1473 _private field_ `private System.Windows.Forms.ColumnHeader PreflightColumn`
- L1474 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_OpenPreflight`
- L1475 _private field_ `private UnrealGameSync.Controls.ReadOnlyCheckbox GenerateAfterSyncCheckBox`
- L1476 _private field_ `private System.Windows.Forms.ToolStripMenuItem OptionsContextMenu_ImportSnapshots`
- L1477 _private field_ `private Label PCBLabel`
- L1478 _private field_ `private System.Windows.Forms.FlowLayoutPanel BuildListFooterLayoutPanel`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/WorkspaceControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.WorkspaceControl`  
`partial class WorkspaceControl : UserControl, IMainWindowTabPanel, ICustomThemeHandler`  
_internal*; L32-7999_
- inherits: `UserControl, IMainWindowTabPanel, ICustomThemeHandler`
- L151 _public property_ `public static Rectangle GoodBuildIcon { get; }`
- L152 _public property_ `public static Rectangle MixedBuildIcon { get; }`
- L153 _public property_ `public static Rectangle BadBuildIcon { get; }`
- L154 _public property_ `public static Rectangle DefaultBuildIcon { get; }`
- L155 _private* property_ `static Rectangle PromotedBuildIcon { get; }`
- L156 _private* property_ `static Rectangle InfoIcon { get; }`
- L157 _private* property_ `static Rectangle CancelIcon { get; }`
- L158 _private* property_ `static Rectangle HappyIcon { get; }`
- L159 _private* property_ `static Rectangle DisabledHappyIcon { get; }`
- L160 _private* property_ `static Rectangle FrownIcon { get; }`
- L161 _private* property_ `static Rectangle DisabledFrownIcon { get; }`
- L162 _private* property_ `static Rectangle PreviousSyncIcon { get; }`
- L163 _private* property_ `static Rectangle AdditionalSyncIcon { get; }`
- L164 _private* property_ `static Rectangle BisectPassIcon { get; }`
- L165 _private* property_ `static Rectangle BisectFailIcon { get; }`
- L166 _private* property_ `static Rectangle BisectImplicitPassIcon { get; }`
- L167 _private* property_ `static Rectangle BisectImplicitFailIcon { get; }`
- L170 _private* method_ `static extern int SetWindowTheme(IntPtr hWnd, string pszSubAppName, string pszSubIdList)` — attrs: `[DllImport("uxtheme.dll", CharSet = CharSet.Unicode)]`
- L173 _private* method_ `static extern bool FlashWindow(IntPtr hwnd, bool bInvert)` — attrs: `[DllImport("user32.dll")]`
- L175 _private* const_ `const int BuildListExpandCount = 250`
- L177 _private* field_ `readonly IWorkspaceControlOwner _owner`
- L178 _private* field_ `readonly DirectoryReference _appDataFolder`
- L179 _private* field_ `readonly string? _apiUrl`
- L180 _private* field_ `readonly DirectoryReference _workspaceDataFolder`
- L181 _private* field_ `readonly IServiceProvider _serviceProvider`
- L182 _private* field_ `readonly ILogger _logger`
- L183 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L185 _private* field_ `readonly IHordeClient? _hordeClient`
- L187 _private* property_ `ProjectInfo ProjectInfo { get; }`
- L189 _private* field_ `readonly UserSettings _settings`
- L190 _private* field_ `readonly UserWorkspaceSettings _workspaceSettings`
- L191 _private* field_ `readonly UserProjectSettings _projectSettings`
- L193 _private* field_ `bool _userHasOpenIssues = false`
- L195 _public property_ `public UserSelectedProjectSettings SelectedProject { get; }`
- L197 _public property_ `public FileReference SelectedFileName => ...`
- L198 _private* property_ `string SelectedProjectIdentifier => ...`
- L199 _public property_ `public DirectoryReference BranchDirectoryName => ...`
- L200 _public property_ `public string? StreamName => ...`
- L201 _public property_ `public string ClientName => ...`
- L203 _private* field_ `readonly SynchronizationContext _mainThreadSynchronizationContext`
- L204 _private* field_ `bool _isDisposing`
- L206 _private* field_ `PerforceMonitor _perforceMonitor`
- L207 _private* field_ `Workspace _workspace`
- L209 _private* field_ `IssueMonitor _issueMonitor`
- L211 _private* field_ `EventMonitor _eventMonitor`
- L213 _private* field_ `readonly System.Windows.Forms.Timer _updateTimer`
- L215 _private* field_ `HashSet<int> _promotedChangeNumbers = new HashSet<int>()`
- L216 _private* field_ `List<int> _listIndexToChangeIndex = new List<int>()`
- L217 _private* field_ `List<int> _sortedChangeNumbers = new List<int>()`
- L218 _private* field_ `readonly Dictionary<string, Dictionary<int, IArchive?>> _archiveToChangeNumberToArchiveKey = ...`
- L218 _private* field_ `readonly Dictionary< int`
- L218 _private* field_ `readonly Dictionary< _archiveToChangeNumberToArchiveKey = new Dictionary<string, Dictionary<int, IArchive?>>()`
- L219 _private* field_ `readonly Dictionary<int, ChangeLayoutInfo> _changeNumberToLayoutInfo = ...`
- L219 _private* field_ `readonly Dictionary< _changeNumberToLayoutInfo = new Dictionary<int, ChangeLayoutInfo>()`
- L220 _private* field_ `readonly List<ContextMenuStrip> _customStatusPanelMenus = new List<ContextMenuStrip>()`
- L221 _private* field_ `readonly List<(string, Action<Point, Rectangle>)> _customStatusPanelLinks = new List<(string, Action<Point, Rectangle>)>()`
- L222 _private* field_ `int _numChanges`
- L223 _private* field_ `int _pendingSelectedChangeNumber = -1`
- L224 _private* field_ `bool _hasBuildSteps = false`
- L226 _private* field_ `readonly Dictionary<string, int> _notifiedBuildTypeToChangeNumber = ...`
- L226 _private* field_ `readonly Dictionary< _notifiedBuildTypeToChangeNumber = new Dictionary<string, int>()`
- L228 _private* field_ `bool _mouseOverExpandLink`
- L230 _private* field_ `string? _hoverBadgeUniqueId = null`
- L231 _private* field_ `bool _hoverSync`
- L232 _private* field_ `ChangesRecord? _contextMenuChange`
- L233 _private* field_ `Font? _buildFont`
- L234 _private* field_ `Font? _selectedBuildFont`
- L235 _private* field_ `Font? _badgeFont`
- L236 _private* field_ `List<KeyValuePair<string, string>> _badgeNameAndGroupPairs = ...`
- L236 _private* field_ `List<KeyValuePair< _badgeNameAndGroupPairs = new List<KeyValuePair<string, string>>()`
- L237 _private* field_ `readonly Dictionary<string, Size> _badgeLabelToSize = ...`
- L237 _private* field_ `readonly Dictionary< _badgeLabelToSize = new Dictionary<string, Size>()`
- L238 _private* field_ `List<ServiceBadgeInfo> _serviceBadges = new List<ServiceBadgeInfo>()`
- L240 _private* field_ `NotificationWindow _notificationWindow`
- L242-246 _public property_ `public Tuple<TaskbarState, float> DesiredTaskbarState { get; set; }`
- L248 _private* field_ `int _buildListWidth`
- L249 _private* field_ `float[] _columnWidths = Array.Empty<float>()`
- L250 _private* field_ `float[] _columnWeights = Array.Empty<float>()`
- L251 _private* field_ `int[] _minColumnWidths = Array.Empty<int>()`
- L252 _private* field_ `int[] _desiredColumnWidths = Array.Empty<int>()`
- L253 _private* field_ `string? _lastColumnSettings`
- L254 _private* field_ `List<ColumnHeader> _customColumns = new List<ColumnHeader>()`
- L255 _private* field_ `int _maxBuildBadgeChars`
- L256 _private* field_ `ListViewItem? _expandItem`
- L258 _private* field_ `bool _updateBuildListPosted`
- L259 _private* field_ `bool _updateBuildMetadataPosted`
- L260 _private* field_ `bool _updateReviewsPosted`
- L262 _private field_ `private bool _showReviewerColumn = true`
- L263 _private field_ `private bool _showPreflightColumn = true`
- L265 _private field_ `private readonly ISet<string> _reviewTags = new HashSet<string>(StringComparer.OrdinalIgnoreCase)`
- L266 _private field_ `private readonly ISet<string> _preflightTags = new HashSet<string>(StringComparer.OrdinalIgnoreCase)`
- L268 _private* field_ `WorkspaceUpdateCallback? _updateCallback`
- L270 _private* field_ `System.Threading.Timer? _startupTimer`
- L271 _private* field_ `List<WorkspaceStartupCallback>? _startupCallbacks`
- L274 _private* field_ `string _authorFilterText = ""`
- L275 _private* field_ `readonly List<string> _authorsFilter = new List<string>()`
- L278 _private* const_ `const string AuthorFilterPlaceholderText = "<username>"`
- L280 _private* field_ `static readonly Bitmap s_hackToolStripMenuGutter = new Bitmap(1, 1)`
- L282-584 _public ctor_ `public WorkspaceControl(IWorkspaceControlOwner owner, DirectoryReference appDataFolder, string? apiUrl, OpenProjectInfo openProjectInfo, IServiceProvider serviceProvider, UserSettings settings)`
- L586-595 _public method_ `public void IssueMonitor_OnIssuesChangedAsync()`
- L597-600 _public method_ `public List<IssueData> GetOpenIssuesForUser()`
- L602-611 _public method_ `public void IssueMonitor_OnIssuesChanged()`
- L613-616 _public method_ `public IssueMonitor GetIssueMonitor()`
- L618-627 _private method_ `private void CheckForStartupComplete()`
- L629-645 _private method_ `private void StartupTimerElapsed(bool cancel)`
- L647-657 _public method_ `public void AddStartupCallback(WorkspaceStartupCallback startupCallback)`
- L659-820 _private method_ `private void UpdateColumnSettings(bool forceUpdate)`
- L822-847 _private method_ `private bool UpdateServiceBadges()`
- L849-869 _protected method_ `protected override void OnLoad(EventArgs e)`
- L875-946 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L948-951 _public method_ `public bool IsBusy()`
- L953-956 _public method_ `public bool CanSyncNow()`
- L958-961 _public method_ `public bool CanLaunchEditor()`
- L963-966 _private method_ `private void MainWindow_Load(object sender, EventArgs e)`
- L968-973 _private method_ `private void ShowErrorDialog(string format, params object[] args)`
- L975-979 _public method_ `public bool CanClose()`
- L981-991 _private method_ `private void StreamChanged()`
- L993-996 _private method_ `private void StreamViewChanged()`
- L998-1009 _private method_ `private void RefreshAfterStreamChange()`
- L1011-1018 _private method_ `private void LoginExpired()`
- L1020-1023 _private method_ `private void BuildList_OnScroll()`
- L1025-1065 _private* method_ `void ShrinkNumRequestedBuilds()`
- L1067-1070 _private* method_ `void StartSync(int changeNumber, bool skipKnownChangeLists)`
- L1072-1123 _private* method_ `void StartSync(int changeNumber, bool syncOnly, WorkspaceUpdateCallback? callback, bool skipKnownChangeLists)`
- L1125-1128 _private* method_ `void StartWorkspaceUpdate(int changeNumber, WorkspaceUpdateOptions options, bool skipKnownChangeLists)`
- L1130-1264 _private* method_ `async void StartWorkspaceUpdate(int changeNumber, WorkspaceUpdateOptions options, WorkspaceUpdateCallback? callback, bool skipKnownChangeLists)`
- L1266-1315 _private* method_ `void StartWorkspaceUpdate(WorkspaceUpdateContext context, WorkspaceUpdateCallback? callback)`
- L1317-1337 _private* method_ `void CancelWorkspaceUpdate()`
- L1339-1348 _private* method_ `void StateChangedCallback(ReadOnlyWorkspaceState state)`
- L1350-1359 _private* method_ `void UpdateCompleteCallback(WorkspaceUpdateContext context, WorkspaceUpdateResult result, string resultMessage)`
- L1361-1486 _private* method_ `void UpdateComplete(WorkspaceUpdateContext context, WorkspaceUpdateResult result)`
- L1488-1502 _private* method_ `void UpdateBuildListCallback()`
- L1504-1573 _private* method_ `void UpdateBuildList()`
- L1575-1653 _private* method_ `void UpdateBuildListInternal(List<ChangesRecord> changes, bool showExpandItem)`
- L1655-1682 _private* method_ `ListViewGroup BuildList_FindOrAddGroup(ChangesRecord change, string groupName)`
- L1684-1798 _private* method_ `void BuildList_AddItem(ChangesRecord change)`
- L1805-1810 _private* method_ `static bool IsRobomergeChange(ChangesRecord change)` — Returns true if this change was submitted on behalf of someone by robomerge
- L1812-1891 _private* method_ `bool ShouldShowChange(ChangesRecord change, string[] excludeChanges)`
- L1893-1907 _private* method_ `void UpdateBuildMetadataCallback()`
- L1909-1917 _private* method_ `string? GetIssuesApiUrl()`
- L1919-2012 _private* method_ `void UpdateBuildMetadata()`
- L2014-2040 _private* method_ `void UpdateMaxBuildBadgeChars()`
- L2042-2066 _private* method_ `int GetBuildBadgeStripWidth(int maxNumChars)`
- L2068-2088 _private* method_ `bool ShouldIncludeInReviewedList(int changeNumber)`
- L2090-2093 _private* method_ `Dictionary<Guid, WorkspaceSyncCategory> GetSyncCategories()`
- L2095-2098 _private* method_ `IDictionary<string, Preset> GetPresets()`
- L2100-2108 _private* method_ `string GetDefaultPreset()`
- L2110-2118 _private* method_ `bool GetForceDefaultPreset()`
- L2120-2123 _private* method_ `ISet<string> GetAdditionalPathsToSync()`
- L2125-2128 _private* method_ `ISet<string> GetBaseContentPaths()`
- L2130-2172 _private* method_ `static List<string> GetProjectRoots(string inUProjectDirsPath)`
- L2174-2200 _private* method_ `void ParseUncontrolledChangelistsPersistencyFile(string inProjectRoot, HashSet<string> outUncontrolledFiles)`
- L2202-2216 _private* method_ `void UpdateReviewsCallback()`
- L2218-2232 _private* method_ `void UpdateReviews()`
- L2234-2358 _private* method_ `void UpdateBuildFailureNotification()`
- L2368-2401 _private* method_ `ExpandRowLayout LayoutExpandRow(Graphics graphics, Rectangle bounds)`
- L2403-2415 _private method_ `private void DrawExpandRow(Graphics graphics, ExpandRowLayout layout)`
- L2417-2428 _private method_ `private bool HitTestExpandLink(Point location)`
- L2430-2455 _private method_ `private void BuildList_DrawItem(object sender, DrawListViewItemEventArgs e)`
- L2457-2466 _private method_ `private IArchive? GetArchiveForChangeNumber(IArchiveChannel archiveChannel, int changeNumber, bool skipKnownChangeLists)`
- L2468-2480 _private method_ `private IArchive? GetArchiveForChangeNumber(IArchiveChannel archiveChannel, int changeNumber, int maxChangeNumber, Dictionary<int, IArchive?> changeNumberToArchive, bool skipKnownChangeLists)`
- L2482-2512 _private method_ `private IArchive? GetArchiveForChangeNumberUncached(IArchiveChannel archiveChannel, int changeNumber, int maxChangeNumber)`
- L2514-2517 _private method_ `private static Color Blend(Color first, Color second, float t)`
- L2519-2560 _private method_ `private bool CanSyncChange(int changeNumber, bool skipKnownChangeLists)`
- L2567-2572 _private method_ `private static bool DoRequiredBadgesExist(List<string> requiredBadgeList, List<BadgeData> inBadges)` — Should read as Do Required Badges Exist and Are They Good. Determines if the ini specified INI filter is a subset of the InBadges passed BadgeGroupSyncFilter - is used as the ini
- L2574-2602 _private method_ `private static bool DoRequiredBadgesExist(List<string> requiredBadgeList, List<BadgeData> inBadges, out bool badgesSuccessful)`
- L2604-2632 _private method_ `private void GetRequiredBadgesStatusOnlyAtChangeCumulative(int changeNumber, List<string> requiredBadgeList, Dictionary<string, bool?> badgeResults)`
- L2634-2687 _private method_ `private Dictionary<string, bool?> GetRequiredBadgesStatusAtChange(int changeNumber, List<string> requiredBadgeList, bool includeFutureChanges = false)`
- L2689-2716 _private method_ `private bool CanSyncChangeType(LatestChangeType changeType, int changeNumber, EventSummary? summary)`
- L2718-2735 _private method_ `private ChangeLayoutInfo GetChangeLayoutInfo(ChangesRecord change)`
- L2737-2759 _private method_ `private void GetRemainingBisectRange(out int outPassChangeNumber, out int outFailChangeNumber)`
- L2761-3040 _private method_ `private void BuildList_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)`
- L3042-3061 _private method_ `private void LayoutBadges(List<BadgeInfo> badges)`
- L3063-3095 _private method_ `private static Point GetBadgeListLocation(List<BadgeInfo> badges, Rectangle bounds, HorizontalAlign horzAlign, VerticalAlignment vertAlign)`
- L3097-3115 _private method_ `private void DrawBadges(Graphics graphics, Point listLocation, List<BadgeInfo> badges, int alpha)`
- L3117-3226 _private method_ `private List<BadgeInfo> CreateDescriptionBadges(ChangesRecord change)`
- L3228-3234 _private method_ `private void PrintLatestChangeTypeUsage(string erroringDefinition)`
- L3240-3271 _public method_ `public List<LatestChangeType> GetCustomLatestChangeTypes()` — Array of config specified options for what the Latest Change to Sync should be. See PrintLatestChangeTypeUsage for usage information
- L3273-3283 _private method_ `private static void SafeProcessStart(ProcessStartInfo startInfo)`
- L3285-3298 _private method_ `private static void SafeProcessStart(string url)`
- L3300-3314 _private method_ `private static void SafeProcessStart(string url, string arguments)`
- L3316-3331 _private method_ `private static void SafeProcessStart(string url, string arguments, string workingDir)`
- L3333-3338 _public method_ `public void UpdateSettings()`
- L3341-3344 _private method_ `private void UpdatePerforceSettings()`
- L3347-3358 _private method_ `private static string? ReplaceRegexMatches(string? text, Match matchResult)` — attrs: `[return: NotNullIfNotNull("text")]`
- L3360-3390 _private method_ `private List<BadgeInfo> CreateTypeBadges(int changeNumber)`
- L3392-3395 _private method_ `private bool TryGetProjectSetting(ConfigFile projectConfigFile, string name, [NotNullWhen(true)] out string? value)`
- L3397-3410 _private method_ `private bool TryGetProjectSetting(ConfigFile projectConfigFile, string name, [NotNullWhen(true)] out string[]? values)`
- L3412-3439 _private method_ `private List<BadgeInfo> CreateBuildBadges(int changeNumber, EventSummary? summary)`
- L3441-3511 _private method_ `private BadgeInfo CreateBadge(int changeNumber, string badgeName, string badgeGroup, BadgeData? badgeData, int maxBadgeChars = -1)`
- L3513-3539 _private method_ `private Dictionary<string, List<BadgeInfo>> CreateCustomBadges(int changeNumber, EventSummary? summary)`
- L3541-3563 _private method_ `private static Color GetBuildBadgeColor(BadgeResult result)`
- L3565-3569 _private method_ `private Rectangle GetSyncBadgeRectangle(Rectangle bounds)`
- L3571-3600 _private method_ `private void DrawBadge(Graphics graphics, Rectangle badgeRect, string badgeText, Color badgeColor, bool mergeLeft, bool mergeRight)`
- L3602-3614 _private method_ `private Size GetBadgeSize(string badgeText)`
- L3616-3624 _private method_ `private static bool GetLastUpdateMessage(WorkspaceUpdateResult result, string? resultMessage, [NotNullWhen(true)] out string? message)`
- L3626-3656 _private method_ `private static bool GetGenericLastUpdateMessage(WorkspaceUpdateResult result, [NotNullWhen(true)] out string? message)`
- L3658-3668 _public method_ `public static string FormatUserName(string userName)`
- L3670-3673 _private method_ `private static void AppendUserList(StringBuilder builder, string separator, string format, IEnumerable<EventData> reviews)`
- L3675-3686 _private method_ `private static void AppendItemList(StringBuilder builder, string separator, string format, IEnumerable<string> items)`
- L3688-3708 _private method_ `private static string? FormatItemList(string format, IEnumerable<string> items)`
- L3710-3731 _private method_ `private void BuildList_MouseDoubleClick(object sender, MouseEventArgs args)`
- L3733-3790 _public method_ `public void LaunchEditor()`
- L3792-3802 _private method_ `private void ShowEditorLaunchError(string message)`
- L3804-3816 _private method_ `private bool WaitForProgramsToFinish()`
- L3818-3883 _private method_ `private FileReference[] GetProcessesRunningInWorkspace()`
- L3885-3901 _private method_ `private void TimerCallback(object? sender, EventArgs args)`
- L3903-3918 _private method_ `private string? GetDefaultIssueFilter()`
- L3920-3963 _private method_ `private Dictionary<string, Func<IssueData, bool>> GetCustomIssueFilters()`
- L3965-3973 _private method_ `private void OpenPerforce()`
- L3975-3989 _private* method_ `void RunTool(ToolInfo tool, ToolLink link)`
- L3991-4001 _private method_ `private void UpdateStatusPanel_CrossThread()`
- L4003-4018 _private method_ `private void AddHordeStatus(StatusLine statusLine)`
- L4020-4462 _private method_ `private void UpdateStatusPanel()`
- L4464-4478 _private method_ `private void ConnectToHorde(IHordeClient hordeClient)`
- L4480-4568 _private method_ `private void ShowBuildHealthMenu(Rectangle bounds)`
- L4570-4573 _private method_ `private void BuildHealthContextMenu_Issue_Click(IssueData issue)`
- L4575-4583 _private method_ `private TimeSpan? GetServerTimeOffset()`
- L4585-4588 _public method_ `public void ShowIssueDetails(IssueData issue)`
- L4590-4595 _private method_ `private void BuildHealthContextMenu_Browse_Click(object sender, EventArgs e)`
- L4597-4607 _private method_ `private void BuildHealthContextMenu_Settings_Click(object sender, EventArgs e)`
- L4609-4618 _private method_ `private void ShowRequiredSdkInfo()`
- L4620-4713 _private method_ `private static StatusLine CreateStatusLineFromMarkdown(string text, bool applyDpiScalingToIcons = true)`
- L4715-4722 _private method_ `private static void FlushMarkdownText(StatusLine line, StringBuilder elementText, FontStyle style)`
- L4724-4768 _private method_ `private void SelectOtherStream(Rectangle bounds)`
- L4770-4777 _private method_ `private void SelectOtherStreamDialog()`
- L4779-4841 _private method_ `private void SelectStream(string newStreamName)`
- L4843-4855 _private method_ `private void ViewLastSyncStatus()`
- L4857-4864 _private method_ `private void ShowErrorInLog()`
- L4866-4870 _private method_ `private void ShowToolContextMenu(Rectangle bounds, ContextMenuStrip menuStrip)`
- L4872-4877 _private method_ `private void ShowActionsMenu(Rectangle bounds)`
- L4879-4907 _private method_ `private void SelectChange(int changeNumber)`
- L4909-5086 _private method_ `private void BuildList_MouseClick(object sender, MouseEventArgs args)`
- L5088-5193 _private method_ `private void ShowChangelistContextMenu(Control parentControl, bool showTimeRelatedItems, Point location, ToolStripDropDownDirection direction = ToolStripDropDownDirection.BelowRight)`
- L5195-5275 _private method_ `private void BuildList_MouseMove(object sender, MouseEventArgs e)`
- L5277-5288 _private method_ `private static BadgeInfo? HitTestBadge(Point location, List<BadgeInfo> badgeList, Point listLocation)`
- L5290-5312 _private method_ `private static List<IArchiveChannel> GetSelectedArchiveChannels(IReadOnlyList<IArchiveChannel> archives, IReadOnlyList<ArchiveSettings> archiveSettingsList)`
- L5314-5317 _private method_ `private List<IArchiveChannel> GetSelectedArchiveChannels(IReadOnlyList<IArchiveChannel> archives)`
- L5319-5322 _private method_ `private List<IArchiveChannel> GetSelectedProjectOverrideArchiveChannels(IReadOnlyList<IArchiveChannel> archives)`
- L5324-5333 _private method_ `private void ClearSelectedArchives()`
- L5335-5346 _private method_ `private void ClearSelectedProjectOverrideArchives()`
- L5348-5359 _private method_ `private void DeactivateSelectedProjectOverrideArchives()`
- L5360-5381 _private method_ `private void SetSelectedArchive(IArchiveChannel archive, bool selected)`
- L5383-5406 _private method_ `private void SetSelectedArchiveProjectOverride(IArchiveChannel archive, bool selected)`
- L5408-5414 _private method_ `private void UpdateSelectedArchives()`
- L5416-5446 _private method_ `private void UpdateSelectedArchivesLabel()`
- L5448-5562 _private method_ `private void OptionsButton_Click(object sender, EventArgs e)`
- L5564-5572 _private method_ `private IReadOnlyList<IArchiveChannel> GetArchiveChannels()`
- L5574-5583 _private method_ `private void GenerateAfterSyncCheckBox_CheckedChanged(object sender, EventArgs e)`
- L5585-5594 _private method_ `private void BuildAfterSyncCheckBox_CheckedChanged(object sender, EventArgs e)`
- L5596-5605 _private method_ `private void RunAfterSyncCheckBox_CheckedChanged(object sender, EventArgs e)`
- L5607-5612 _private method_ `private void BuildListToolTip_Draw(object sender, DrawToolTipEventArgs e)`
- L5614-5623 _private method_ `private void OpenSolutionAfterSyncCheckBox_CheckedChanged(object sender, EventArgs e)`
- L5625 _private field_ `private static readonly ToolTip s_syncActionsInactiveToolTip = new ToolTip()`
- L5626 _private const_ `private const string _syncActionsInactiveToolTipText = "After sync actions disabled for UEFN projects"`
- L5628-5674 _private method_ `private void UpdateSyncActionCheckboxes()`
- L5676-5740 _private method_ `private void UpdateImportSnapshotDropdown(string host, string ns, string branch, string project, bool allowInteractiveLogin = false)`
- L5742-5752 _private method_ `private void BuildList_FontChanged(object? sender, EventArgs e)`
- L5754-5757 _private method_ `private void WorkspaceControl_DpiChangedAfterParent(object sender, System.EventArgs e)`
- L5759-5773 _public method_ `public void ExecCommand(string description, string statusText, string fileName, string arguments, string workingDir, bool useLogWindow)`
- L5775-5783 _public method_ `public void SyncChange(int changeNumber, bool syncOnly, WorkspaceUpdateCallback? callback, bool skipKnownChangeLists)`
- L5785-5788 _public method_ `public void SyncLatestChange()`
- L5790-5817 _public method_ `public void SyncLatestChange(WorkspaceUpdateCallback? callback)`
- L5819-5825 _private method_ `private void BuildListContextMenu_MarkGood_Click(object sender, EventArgs e)`
- L5827-5833 _private method_ `private void BuildListContextMenu_MarkBad_Click(object sender, EventArgs e)`
- L5835-5841 _private method_ `private void BuildListContextMenu_WithdrawReview_Click(object sender, EventArgs e)`
- L5843-5849 _private method_ `private void BuildListContextMenu_Sync_Click(object sender, EventArgs e)`
- L5851-5857 _private method_ `private void BuildListContextMenu_SyncContentOnly_Click(object sender, EventArgs e)`
- L5859-5865 _private method_ `private void BuildListContextMenu_SyncOnlyThisChange_Click(object sender, EventArgs e)`
- L5867-5870 _private method_ `private void BuildListContextMenu_Build_Click(object sender, EventArgs e)`
- L5872-5875 _private method_ `private void BuildListContextMenu_Rebuild_Click(object sender, EventArgs e)`
- L5877-5880 _private method_ `private void BuildListContextMenu_GenerateProjectFiles_Click(object sender, EventArgs e)`
- L5882-5885 _private method_ `private void BuildListContextMenu_CancelSync_Click(object sender, EventArgs e)`
- L5887-5893 _private method_ `private void BuildListContextMenu_MoreInfo_Click(object sender, EventArgs e)`
- L5895-5909 _private method_ `private void BuildListContextMenu_ViewInSwarm_Click(object sender, EventArgs e)`
- L5911-5924 _private method_ `private void BuildListContextMenu_CopyChangelistNumber_Click(object sender, EventArgs e)`
- L5926-5975 _private method_ `private void BuildListContextMenu_OpenPreflight_Click(object sender, EventArgs e)`
- L5977-5986 _private method_ `private void BuildListContextMenu_AddStar_Click(object sender, EventArgs e)`
- L5988-6002 _private method_ `private void BuildListContextMenu_RemoveStar_Click(object sender, EventArgs e)`
- L6004-6007 _private method_ `private void BuildListContextMenu_LaunchEditor_Click(object sender, EventArgs e)`
- L6009-6019 _private method_ `private void BuildListContextMenu_StartInvestigating_Click(object sender, EventArgs e)`
- L6021-6045 _private method_ `private void BuildListContextMenu_FinishInvestigating_Click(object sender, EventArgs e)`
- L6047-6051 _private method_ `private void OnlyShowReviewedCheckBox_CheckedChanged(object sender, EventArgs e)`
- L6053-6064 _public method_ `public void Activate()`
- L6066-6069 _public method_ `public void Deactivate()`
- L6071-6146 _private method_ `private void BuildList_ItemMouseHover(object sender, ListViewItemMouseHoverEventArgs args)`
- L6148-6164 _private method_ `private void BuildList_MouseLeave(object sender, EventArgs e)`
- L6166-6169 _private method_ `private void OptionsContextMenu_ShowLog_Click(object sender, EventArgs e)`
- L6171-6174 _private method_ `private void ToggleLogVisibility()`
- L6176-6182 _private method_ `private void Splitter_OnVisibilityChanged(bool visible)`
- L6184-6189 _private method_ `private void OptionsContextMenu_AutoResolveConflicts_Click(object sender, EventArgs e)`
- L6191-6196 _private method_ `private void OptionsContextMenu_AlwaysClobberFiles_Click(object sender, EventArgs e)`
- L6198-6203 _private method_ `private void OptionsContextMenu_AlwaysDeleteFiles_Click(object sender, EventArgs e)`
- L6205-6208 _private method_ `private void OptionsContextMenu_EditorArguments_Click(object sender, EventArgs e)`
- L6210-6226 _private method_ `private List<LockableEditorArgument> GetDefaultEditorArguments()`
- L6228-6258 _private method_ `private List<LockableEditorArgument> GetEditorArgumentsWithDefaults()`
- L6260-6294 _private method_ `private bool ModifyEditorArguments()`
- L6296-6299 _private method_ `private void BuildListContextMenu_OpenVisualStudio_Click(object sender, EventArgs e)`
- L6301-6374 _private method_ `private void OpenSolution()`
- L6376-6379 _private method_ `private void OptionsContextMenu_BuildConfig_Debug_Click(object sender, EventArgs e)`
- L6381-6384 _private method_ `private void OptionsContextMenu_BuildConfig_DebugGame_Click(object sender, EventArgs e)`
- L6386-6389 _private method_ `private void OptionsContextMenu_BuildConfig_Development_Click(object sender, EventArgs e)`
- L6391-6396 _private* method_ `void UpdateBuildConfig(BuildConfig newConfig)`
- L6398-6410 _private* method_ `void UpdateCheckedBuildConfig()`
- L6412-6415 _private method_ `private void OptionsContextMenu_ScheduleSync_Click(object sender, EventArgs e)`
- L6417-6457 _public method_ `public void ScheduleTimerElapsed()`
- L6459-6482 _private* method_ `bool FindChangeToSync(string? changeTypeId, out int changeNumber)`
- L6484-6535 _private* method_ `bool FindChangeToSync(LatestChangeType changeType, out int changeNumber)`
- L6537-6570 _private* method_ `int FindNewestGoodContentChange(int changeNumber)`
- L6572-6589 _private method_ `private void BuildListContextMenu_LeaveOrEditComment_Click(object sender, EventArgs e)`
- L6591-6597 _private method_ `private void BuildListContextMenu_ShowServerTimes_Click(object sender, EventArgs e)`
- L6599-6605 _private method_ `private void BuildListContextMenu_ShowLocalTimes_Click(object sender, EventArgs e)`
- L6607-6610 _private method_ `private void MoreToolsContextMenu_CleanWorkspace_Click(object sender, EventArgs e)`
- L6612-6647 _private method_ `private void CleanWorkspace()`
- L6649-6653 _private method_ `private void MoreToolsContextMenu_UpdateTools_Click(object sender, EventArgs e)`
- L6655-6776 _private method_ `private void UpdateBuildSteps()`
- L6778-6793 _private method_ `private bool CanRunStep(BuildStep step)`
- L6795-6864 _private method_ `private void RunCustomTool(BuildStep step, List<BuildStep> allSteps)`
- L6866-6919 _private method_ `private void OptionsContextMenu_EditBuildSteps_Click(object sender, EventArgs e)`
- L6921-6937 _private method_ `private static void AddOrUpdateBuildStep(Dictionary<Guid, ConfigObject> steps, ConfigObject obj)`
- L6939 _private property_ `private bool ShouldSyncPrecompiledEditor => ...`
- L6941-6970 _private method_ `private bool ShouldSyncPrecompiledEditor_Impl()`
- L6972-6975 _public method_ `public BuildConfig GetEditorBuildConfig()`
- L6977-6989 _private method_ `private Dictionary<Guid, ConfigObject> GetProjectBuildStepObjects(ConfigFile projectConfigFile)`
- L6991-7002 _private method_ `private List<BuildStep> GetUserBuildSteps(Dictionary<Guid, ConfigObject> projectBuildStepObjects)`
- L7004-7014 _private method_ `private void OptionsContextMenu_SyncPrecompiledBinaries_Click(object sender, EventArgs e)`
- L7016-7026 _private method_ `private void OptionsContextMenu_SyncPrecompiledBinariesProjectOverride_Click(object sender, EventArgs e)`
- L7028-7031 _private method_ `private void BuildList_SelectedIndexChanged(object sender, EventArgs e)`
- L7033-7052 _private method_ `private void OptionsContextMenu_Diagnostics_Click(object sender, EventArgs e)`
- L7054-7079 _private method_ `private void OptionsContextMenu_SyncFilter_Click(object sender, EventArgs e)`
- L7081-7141 _private method_ `private void OptionsContextMenu_Presets_Click(object sender, EventArgs e)`
- L7146-7166 _private method_ `private void RefreshSyncMenuItems()` — Used to load CustomLatestChangeTypes config data into the windows form.
- L7168-7203 _private method_ `private void ShowSyncMenu(Rectangle bounds)`
- L7205-7209 _private method_ `private void SyncContextMenu_LatestChangeType_Click(string syncTypeId)`
- L7211-7223 _private method_ `private void SyncContextMenu_EnterChangelist_Click(object sender, EventArgs e)`
- L7225-7237 _private method_ `private void BuildList_KeyDown(object sender, KeyEventArgs args)`
- L7239-7242 _private method_ `private void OptionsContextMenu_ApplicationSettings_Click(object sender, EventArgs e)`
- L7244-7247 _private method_ `private void OptionsContextMenu_TabNames_Stream_Click(object sender, EventArgs e)`
- L7249-7252 _private method_ `private void OptionsContextMenu_TabNames_WorkspaceName_Click(object sender, EventArgs e)`
- L7254-7257 _private method_ `private void OptionsContextMenu_TabNames_WorkspaceRoot_Click(object sender, EventArgs e)`
- L7259-7262 _private method_ `private void OptionsContextMenu_TabNames_ProjectFile_Click(object sender, EventArgs e)`
- L7264-7282 _private method_ `private void SelectRecentProject(Rectangle bounds)`
- L7284-7287 _private method_ `private void RecentMenu_Browse_Click(object sender, EventArgs e)`
- L7289-7293 _private method_ `private void RecentMenu_ClearList_Click(object sender, EventArgs e)`
- L7295-7302 _private method_ `private void OptionsContextMenu_ShowChanges_ShowUnreviewed_Click(object sender, EventArgs e)`
- L7304-7310 _private method_ `private void OptionsContextMenu_ShowChanges_ShowAutomated_Click(object sender, EventArgs e)`
- L7312-7315 _private method_ `private void BuildList_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)`
- L7317-7330 _private method_ `private void BuildList_ColumnWidthChanged(object sender, ColumnWidthChangedEventArgs e)`
- L7332-7356 _private method_ `private void BuildList_Resize(object sender, EventArgs e)`
- L7358-7390 _private* method_ `void ResizeColumns(float nextTotalWidth)`
- L7392-7485 _private* method_ `float[] GetTargetColumnWidths(float nextTotalWidth)`
- L7487-7490 _private method_ `private void BuidlListMultiContextMenu_Bisect_Click(object sender, EventArgs e)`
- L7492-7495 _private method_ `private bool IsBisectModeEnabled()`
- L7497-7520 _private method_ `private void EnableBisectMode()`
- L7522-7525 _private method_ `private void CancelBisectMode()`
- L7527-7540 _private method_ `private void SetBisectStateForSelection(BisectState state)`
- L7542-7560 _private method_ `private int GetBisectChangeNumber()`
- L7562-7571 _private method_ `private void SyncBisectChange()`
- L7573-7576 _private method_ `private void BuildListContextMenu_Bisect_Pass_Click(object sender, EventArgs e)`
- L7578-7581 _private method_ `private void BuildListContextMenu_Bisect_Fail_Click(object sender, EventArgs e)`
- L7583-7586 _private method_ `private void BuildListContextMenu_Bisect_Exclude_Click(object sender, EventArgs e)`
- L7588-7591 _private method_ `private void BuildListContextMenu_Bisect_Include_Click(object sender, EventArgs e)`
- L7593-7599 _private method_ `private void WorkspaceControl_VisibleChanged(object sender, EventArgs e)`
- L7601-7669 _private method_ `private void FilterButton_Click(object sender, EventArgs e)`
- L7671-7684 _private method_ `private void FilterContextMenu_Badge_Click(string badgeName)`
- L7686-7696 _private method_ `private void FilterContextMenu_Default_Click(object sender, EventArgs e)`
- L7698-7704 _private method_ `private void FilterContextMenu_ShowBuildMachineChanges_Click(object sender, EventArgs e)`
- L7706-7711 _private method_ `private void FilterContextMenu_Robomerge_ShowAll_Click(object sender, EventArgs e)`
- L7713-7718 _private method_ `private void FilterContextMenu_Robomerge_ShowBadged_Click(object sender, EventArgs e)`
- L7720-7725 _private method_ `private void FilterContextMenu_Robomerge_ShowNone_Click(object sender, EventArgs e)`
- L7727-7734 _private method_ `private void FilterContextMenu_Robomerge_Annotate_Click(object sender, EventArgs e)`
- L7742-7750 _private method_ `private void FilterContextMenu_Author_Name_GotFocus(object? sender, EventArgs e)` — Handler for the edit box of the author filtering taking focus. This clears any placeholder text and sets the foreground color to black so it shows as active
- L7758-7766 _private method_ `private void FilterContextMenu_Author_Name_LostFocus(object? sender, EventArgs e)` — Handler for the edit box of the author filter losing focus. If the filter box is empty we restore the placeholder text and state
- L7774-7788 _private method_ `private void FilterContextMenu_Author_Name_Changed(object? sender, EventArgs e)` — Handler for the author name changing. We save off the text and update the filter string
- L7790-7796 _private method_ `private void FilterContextMenu_Type_ShowAll_Click(object sender, EventArgs e)`
- L7798-7804 _private method_ `private void FilterContextMenu_Type_Code_Click(object sender, EventArgs e)`
- L7806-7812 _private method_ `private void FilterContextMenu_Type_Content_Click(object sender, EventArgs e)`
- L7814-7820 _private method_ `private void FilterContextMenu_Type_UEFN_Click(object sender, EventArgs e)`
- L7822-7826 _private method_ `private void UpdateBuildListFilter()`
- L7828-7832 _public property_ `public Color? TintColor { get; set; }`
- L7834-7837 _private method_ `private void EditorConfigWatcher_Changed(object sender, FileSystemEventArgs e)`
- L7839-7842 _private method_ `private void EditorConfigWatcher_Renamed(object sender, RenamedEventArgs e)`
- L7844-7854 _private method_ `private Color? GetTintColor()`
- L7856-7909 _private method_ `private Color? GetNewTintColor()`
- L7911-7978 _private method_ `private Color? GetLegacyTintColor()`
- L7980-7988 _private method_ `private void UpdateTintColor()`
- L7990-7998 _public method_ `public void ApplyTheme(ApplicationThemeManager themeManager)`

#### enum `UnrealGameSync.WorkspaceControl.HorizontalAlignment`  
`enum HorizontalAlignment`  
_private*; L34-39_
- L36 _public* enumerator_ `Left`
- L37 _public* enumerator_ `Center`
- L38 _public* enumerator_ `Right`

#### enum `UnrealGameSync.WorkspaceControl.VerticalAlignment`  
`enum VerticalAlignment`  
_private*; L41-46_
- L43 _public* enumerator_ `Top`
- L44 _public* enumerator_ `Middle`
- L45 _public* enumerator_ `Bottom`

#### class `UnrealGameSync.WorkspaceControl.BadgeInfo`  
`class BadgeInfo`  
_private*; L48-91_
- L50 _public field_ `public string _label`
- L51 _public field_ `public string? _group`
- L52 _public field_ `public string? _uniqueId`
- L53 _public field_ `public int _offset`
- L54 _public field_ `public int _width`
- L55 _public field_ `public int _height`
- L56 _public field_ `public Color _backgroundColor`
- L57 _public field_ `public Color _hoverBackgroundColor`
- L58 _public field_ `public Action? _leftClickHandler`
- L59 _public field_ `public Action<Control, Point>? _rightClickHandler`
- L59 _public field_ `public Action< _rightClickHandler`
- L60 _public field_ `public string? _toolTip`
- L62-65 _public ctor_ `public BadgeInfo(string label, string group, Color badgeColor) : this(label, group, null, badgeColor, badgeColor, null, null)`
- L67-77 _public ctor_ `public BadgeInfo(string label, string? group, string? uniqueId, Color backgroundColor, Color hoverBackgroundColor, Action? leftClickHandler, Action<Control, Point>? rightClickHandler)`
- L79-85 _public ctor_ `public BadgeInfo(BadgeInfo other) : this(other._label, other._group, other._uniqueId, other._backgroundColor, other._hoverBackgroundColor, other._leftClickHandler, other._rightClickHandler)`
- L87-90 _public method_ `public Rectangle GetBounds(Point listLocation)`

#### class `UnrealGameSync.WorkspaceControl.ServiceBadgeInfo`  
`class ServiceBadgeInfo : IEquatable<ServiceBadgeInfo>`  
_private*; L93-120_
- inherits: `IEquatable<ServiceBadgeInfo>`
- L95 _public property_ `public string Name { get; }`
- L96 _public property_ `public string? Url { get; }`
- L97 _public property_ `public BadgeResult Result { get; }`
- L99-104 _public ctor_ `public ServiceBadgeInfo(string name, string? url, BadgeResult result)`
- L106-109 _public method_ `public bool Equals(ServiceBadgeInfo? otherBadge)`
- L111-114 _public method_ `public override bool Equals(object? other)`
- L116-119 _public method_ `public override int GetHashCode()`

#### class `UnrealGameSync.WorkspaceControl.ChangeLayoutInfo`  
`class ChangeLayoutInfo`  
_private*; L122-128_
- L124 _public field_ `public List<BadgeInfo> _descriptionBadges = new List<BadgeInfo>()`
- L125 _public field_ `public List<BadgeInfo> _typeBadges = new List<BadgeInfo>()`
- L126 _public field_ `public List<BadgeInfo> _buildBadges = new List<BadgeInfo>()`
- L127 _public field_ `public Dictionary<string, List<BadgeInfo>> _customBadges = ...`
- L127 _public field_ `public Dictionary< _customBadges = new Dictionary<string, List<BadgeInfo>>()`

#### class `UnrealGameSync.WorkspaceControl.BuildListItemComparer`  
`class BuildListItemComparer : System.Collections.IComparer`  
_private*; L130-149_
- inherits: `System.Collections.IComparer`
- L132-148 _public method_ `public int Compare(object? a, object? b)`

#### class `UnrealGameSync.WorkspaceControl.ExpandRowLayout`  
`class ExpandRowLayout`  
_private*; L2360-2366_
- L2362 _public field_ `public string? _mainText`
- L2363 _public field_ `public Rectangle _mainRect`
- L2364 _public field_ `public string? _linkText`
- L2365 _public field_ `public Rectangle _linkRect`

#### class `UnrealGameSync.UncontrolledChangelist`  
`public class UncontrolledChangelist`  
_public; L8001-8006_
- L8003 _public property_ `public string Guid { get; set; }`
- L8004 _public property_ `public string Name { get; set; }`
- L8005 _public property_ `public List<string> Files { get; }`

#### class `UnrealGameSync.UncontrolledChangelistPersistency`  
`public class UncontrolledChangelistPersistency`  
_public; L8008-8012_
- L8010 _public property_ `public int Version { get; set; }`
- L8011 _public property_ `public List<UncontrolledChangelist> Changelists { get; }`

#### interface `UnrealGameSync.IWorkspaceControlOwner`  
`interface IWorkspaceControlOwner`  
_internal*; L8014-8031_
- L8016 _public* property_ `ToolUpdateMonitor ToolUpdateMonitor { get; }`
- L8018 _public* method_ `void EditSelectedProject(WorkspaceControl workspace)`
- L8019 _public* method_ `void RequestProjectChange(WorkspaceControl workspace, UserSelectedProjectSettings project, bool modal)`
- L8020 _public* method_ `void ShowAndActivate()`
- L8021 _public* method_ `void StreamChanged(WorkspaceControl workspace)`
- L8022 _public* method_ `void SetTabNames(TabLabels tabNames)`
- L8023 _public* method_ `void SetupScheduledSync()`
- L8024 _public* method_ `void UpdateProgress()`
- L8025 _public* method_ `void ModifyApplicationSettings()`
- L8026 _public* method_ `void UpdateAlertWindows()`
- L8027 _public* method_ `void UpdateTintColors()`
- L8029 _public* method_ `IssueMonitor CreateIssueMonitor(string? apiUrl, string userName)`
- L8030 _public* method_ `void ReleaseIssueMonitor(IssueMonitor issueMonitor)`

#### Namespace-level symbols

- L8033 _private* delegate_ `delegate void WorkspaceStartupCallback(WorkspaceControl workspace, bool cancel)`
- L8034 _private* delegate_ `delegate void WorkspaceUpdateCallback(WorkspaceUpdateResult result)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/WorkspaceSyncFilterControl.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Controls.WorkspaceSyncFilterControl`  
`partial class WorkspaceSyncFilterControl`  
_internal*; L5-481_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-38 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L46-451 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L455 _private field_ `private System.Windows.Forms.GroupBox ViewGroupBox`
- L456 _private field_ `private System.Windows.Forms.GroupBox CategoriesGroupBox`
- L457 _private field_ `private System.Windows.Forms.SplitContainer SplitContainer`
- L458 _private field_ `private System.Windows.Forms.LinkLabel SyntaxButton`
- L459 _public field_ `public System.Windows.Forms.DataGridView ViewDataGrid`
- L460 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L461 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L462 _public field_ `public System.Windows.Forms.CheckBox SyncAllProjects`
- L463 _public field_ `public System.Windows.Forms.CheckBox IncludeAllProjectsInSolution`
- L464 _public field_ `public System.Windows.Forms.CheckBox GenerateUprojectSpecificSolution`
- L465 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L466 _private field_ `private System.Windows.Forms.TableLayoutPanel CustomViewTableLayoutPanel`
- L467 _public field_ `public CheckBox SyncLocalProjects`
- L468 _private field_ `private Label PresetNameLabel`
- L469 _public field_ `public ComboBox PresetComboBox`
- L470 _public field_ `public CheckBox SyncBaseContentCheckBox`
- L471 _private field_ `private FlowLayoutPanel CustomViewsHeaderPanel`
- L472 _private field_ `private Button CopyCustomViewsToClipboard`
- L473 _private field_ `private ToolTip CategoriesToolTip`
- L474 _private field_ `private FlowLayoutPanel flowLayoutPanel3`
- L475 _public field_ `public CheckedListBox CategoriesCheckList`
- L476 _private field_ `private ToolTip SyncBaseContentToolTip`
- L477 _private field_ `private Button PasteCustomViewsToClipboard`
- L478 _private field_ `private Button ClearCustomViewsToClipboard`
- L479 _private field_ `private TableLayoutPanel CategoriesTableLayoutPanel`
- L480 _private field_ `private FlowLayoutPanel SyncBaseContentFlowLayout`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Controls/WorkspaceSyncFilterControl.cs` (UnrealGameSync)


#### class `UnrealGameSync.Controls.WorkspaceSyncFilterControl`  
`public partial class WorkspaceSyncFilterControl : UserControl`  
_public; L14-364_
- inherits: `UserControl`
- L16 _private field_ `private int _categoriesCheckListHoverIndex = -1`
- L18 _private property_ `private Timer _categoriesCheckListTooltipTimer { get; }`
- L20 _private property_ `private Timer _syncBaseContentTooltipTimer { get; }`
- L34 _private field_ `private readonly BindingList<ViewItem> _views = new BindingList<ViewItem>()`
- L35 _private field_ `private readonly List<ViewItem> _presetViews = new List<ViewItem>()`
- L38 _public property_ `public string SyncBaseContentToolTipTitle { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L40 _public property_ `public string SyncBaseContentToolTipContent { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L42-70 _public ctor_ `public WorkspaceSyncFilterControl()`
- L72-98 _private method_ `private void SyncBaseContentFlowLayout_MouseMove(object? sender, MouseEventArgs e)`
- L100-104 _private method_ `private void SyncBaseContentCheckBox_MouseHover(object? sender, EventArgs e)`
- L106-126 _private method_ `private void CheckedListBox_MouseMove(object? sender, MouseEventArgs e)`
- L128-152 _private method_ `private void CategoriesCheckListTooltipTimer_Tick(object? sender, EventArgs e)`
- L154-164 _private method_ `private void BaseSyncContentTooltipTimer_Tick(object? sender, EventArgs e)`
- L166-169 _private* method_ `void Views_AddingNew(object? sender, AddingNewEventArgs e)`
- L171-181 _private method_ `private void ViewDataGrid_CellBeginEdit(object? sender, DataGridViewCellCancelEventArgs e)`
- L183-189 _private method_ `private void ViewDataGrid_UserDeletingRow(object? sender, DataGridViewRowCancelEventArgs e)`
- L191-195 _private method_ `private void ViewDataGrid_DefaultValuesNeeded(object? sender, System.Windows.Forms.DataGridViewRowEventArgs e)`
- L197-201 _private method_ `private void SyntaxButton_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L203-253 _public method_ `public void SetView(string preset, string[] presetViews, string[] views)`
- L255-272 _public method_ `public string[] GetView()`
- L274-305 _private method_ `private void CopyViewsToClipBoard_Click(object sender, EventArgs e)`
- L307-353 _private method_ `private async void PasteCustomViewsToClipboard_Click(object sender, EventArgs e)`
- L355-363 _private method_ `private void ClearCustomViewsToClipboard_Click(object sender, EventArgs e)`

#### class `UnrealGameSync.Controls.WorkspaceSyncFilterControl.ViewItem`  
`private class ViewItem`  
_private; L22-32_
- L24 _public property_ `public bool Locked { get; set; }`
- L25 _public property_ `public string Value { get; set; }`
- L27-31 _public ctor_ `public ViewItem(bool locked, string value)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/DeleteFilesTask.cs` (UnrealGameSync)


#### class `UnrealGameSync.DeleteFilesTask`  
`static class DeleteFilesTask`  
_internal*; L15-77_
- L17-76 _public method_ `public static async Task RunAsync(IPerforceSettings perforceSettings, List<FileInfo> filesToSync, List<FileInfo> filesToDelete, List<DirectoryInfo> directoriesToDelete, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/EventMonitor.cs` (UnrealGameSync)


#### enum `UnrealGameSync.EventType`  
`enum EventType`  
_internal*; L19-37_
- L21 _public* enumerator_ `Syncing`
- L24 _public* enumerator_ `Compiles`
- L25 _public* enumerator_ `DoesNotCompile`
- L26 _public* enumerator_ `Good`
- L27 _public* enumerator_ `Bad`
- L28 _public* enumerator_ `Unknown`
- L31 _public* enumerator_ `Starred`
- L32 _public* enumerator_ `Unstarred`
- L35 _public* enumerator_ `Investigating`
- L36 _public* enumerator_ `Resolved`

#### class `UnrealGameSync.LatestData`  
`class LatestData`  
_internal*; L39-45_
- L41 _public property_ `public int Version { get; set; }`
- L42 _public property_ `public long LastEventId { get; set; }`
- L43 _public property_ `public long LastCommentId { get; set; }`
- L44 _public property_ `public long LastBuildId { get; set; }`

#### class `UnrealGameSync.EventData`  
`class EventData`  
_internal*; L47-54_
- L49 _public property_ `public long Id { get; set; }`
- L50 _public property_ `public int Change { get; set; }`
- L51 _public property_ `public string UserName { get; set; }`
- L52 _public property_ `public EventType Type { get; set; }`
- L53 _public property_ `public string Project { get; set; }`

#### class `UnrealGameSync.CommentData`  
`class CommentData`  
_internal*; L56-63_
- L58 _public property_ `public long Id { get; set; }`
- L59 _public property_ `public int ChangeNumber { get; set; }`
- L60 _public property_ `public string UserName { get; set; }`
- L61 _public property_ `public string Text { get; set; }`
- L62 _public property_ `public string Project { get; set; }`

#### enum `UnrealGameSync.BadgeResult`  
`enum BadgeResult`  
_internal*; L65-72_
- L67 _public* enumerator_ `Starting`
- L68 _public* enumerator_ `Failure`
- L69 _public* enumerator_ `Warning`
- L70 _public* enumerator_ `Success`
- L71 _public* enumerator_ `Skipped`

#### class `UnrealGameSync.Link`  
`class Link`  
_internal*; L74-78_
- L76 _public property_ `public string Text { get; set; }`
- L77 _public property_ `public string Url { get; set; }`

#### class `UnrealGameSync.BadgeMetadata`  
`class BadgeMetadata`  
_internal*; L80-83_
- L82 _public property_ `public List<Link>? Links { get; set; }`

#### class `UnrealGameSync.BadgeData`  
`class BadgeData`  
_internal*; L85-140_
- L87 _public property_ `public long Id { get; set; }`
- L88 _public property_ `public int ChangeNumber { get; set; }`
- L89 _public property_ `public string BuildType { get; set; }`
- L90 _public property_ `public BadgeResult Result { get; set; }`
- L91 _public property_ `public string Url { get; set; }`
- L92 _public property_ `public string Project { get; set; }`
- L93 _public property_ `public BadgeMetadata? Metadata { get; set; }`
- L95 _public property_ `public bool IsSuccess => ...`
- L97 _public property_ `public bool IsFailure => ...`
- L99-118 _public property_ `public string BadgeName { get; }`
- L120-139 _public property_ `public string BadgeLabel { get; }`

#### enum `UnrealGameSync.ReviewVerdict`  
`enum ReviewVerdict`  
_internal*; L142-148_
- L144 _public* enumerator_ `Unknown`
- L145 _public* enumerator_ `Good`
- L146 _public* enumerator_ `Bad`
- L147 _public* enumerator_ `Mixed`

#### enum `UnrealGameSync.UgsUserVote`  
`public enum UgsUserVote`  
_public; L150-157_
- L152 _public* enumerator_ `None`
- L153 _public* enumerator_ `CompileSuccess`
- L154 _public* enumerator_ `CompileFailure`
- L155 _public* enumerator_ `Good`
- L156 _public* enumerator_ `Bad`

#### class `UnrealGameSync.GetUserDataResponseV2`  
`class GetUserDataResponseV2`  
_internal*; L159-167_
- L161 _public property_ `public string User { get; set; }`
- L162 _public property_ `public long? SyncTime { get; set; }`
- L163 _public property_ `public UgsUserVote? Vote { get; set; }`
- L164 _public property_ `public string Comment { get; set; }`
- L165 _public property_ `public bool? Investigating { get; set; }`
- L166 _public property_ `public bool? Starred { get; set; }`

#### class `UnrealGameSync.GetBadgeDataResponseV2`  
`class GetBadgeDataResponseV2`  
_internal*; L169-174_
- L171 _public property_ `public string Name { get; set; }`
- L172 _public property_ `public string Url { get; set; }`
- L173 _public property_ `public BadgeResult State { get; set; }`

#### class `UnrealGameSync.GetMetadataResponseV2`  
`class GetMetadataResponseV2`  
_internal*; L176-182_
- L178 _public property_ `public int Change { get; set; }`
- L179 _public property_ `public string Project { get; set; }`
- L180 _public property_ `public List<GetUserDataResponseV2> Users { get; set; }`
- L181 _public property_ `public List<GetBadgeDataResponseV2> Badges { get; set; }`

#### class `UnrealGameSync.GetMetadataListResponseV2`  
`class GetMetadataListResponseV2`  
_internal*; L184-188_
- L186 _public property_ `public long SequenceNumber { get; set; }`
- L187 _public property_ `public List<GetMetadataResponseV2> Items { get; set; }`

#### class `UnrealGameSync.UpdateMetadataRequestV2`  
`class UpdateMetadataRequestV2`  
_internal*; L190-201_
- L192 _public property_ `public string? Stream { get; set; }`
- L193 _public property_ `public int Change { get; set; }`
- L194 _public property_ `public string? Project { get; set; }`
- L195 _public property_ `public string? UserName { get; set; }`
- L196 _public property_ `public bool? Synced { get; set; }`
- L197 _public property_ `public string? Vote { get; set; }`
- L198 _public property_ `public bool? Investigating { get; set; }`
- L199 _public property_ `public bool? Starred { get; set; }`
- L200 _public property_ `public string? Comment { get; set; }`

#### class `UnrealGameSync.EventSummary`  
`class EventSummary`  
_internal*; L203-216_
- L205 _public field_ `public int ChangeNumber`
- L206 _public field_ `public ReviewVerdict Verdict`
- L207 _public field_ `public List<EventData> SyncEvents = new List<EventData>()`
- L208 _public field_ `public List<EventData> Reviews = new List<EventData>()`
- L209 _public field_ `public List<string> CurrentUsers = new List<string>()`
- L210 _public field_ `public EventData? LastStarReview`
- L211 _public field_ `public List<BadgeData> Badges = new List<BadgeData>()`
- L212 _public field_ `public List<CommentData> Comments = new List<CommentData>()`
- L214 _public field_ `public GetMetadataResponseV2? SharedMetadata`
- L215 _public field_ `public GetMetadataResponseV2? ProjectMetadata`

#### class `UnrealGameSync.EventMonitor`  
`class EventMonitor : IDisposable`  
_internal*; L218-1158_
- inherits: `IDisposable`
- L220 _private* field_ `readonly string? _apiUrl`
- L221 _private* field_ `int _apiVersion`
- L222 _private* field_ `readonly string _project`
- L223 _private* field_ `readonly string _currentUserName`
- L224 _private* field_ `readonly SynchronizationContext _synchronizationContext`
- L226 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L228 _private* field_ `Task? _workerTask`
- L229 _private* field_ `readonly AsyncEvent _refreshEvent = new AsyncEvent()`
- L230 _private* field_ `readonly ConcurrentQueue<EventData> _outgoingEvents = new ConcurrentQueue<EventData>()`
- L231 _private* field_ `readonly ConcurrentQueue<EventData> _incomingEvents = new ConcurrentQueue<EventData>()`
- L232 _private* field_ `readonly ConcurrentQueue<CommentData> _outgoingComments = new ConcurrentQueue<CommentData>()`
- L233 _private* field_ `readonly ConcurrentQueue<CommentData> _incomingComments = new ConcurrentQueue<CommentData>()`
- L234 _private* field_ `readonly ConcurrentQueue<BadgeData> _incomingBadges = new ConcurrentQueue<BadgeData>()`
- L235 _private* field_ `readonly SortedDictionary<int, EventSummary> _changeNumberToSummary = ...`
- L235 _private* field_ `readonly SortedDictionary< _changeNumberToSummary = new SortedDictionary<int, EventSummary>()`
- L236 _private* field_ `readonly Dictionary<string, EventData> _userNameToLastSyncEvent = ...`
- L236 _private* field_ `readonly Dictionary< _userNameToLastSyncEvent = new Dictionary<string, EventData>(StringComparer.InvariantCultureIgnoreCase)`
- L237 _private* field_ `readonly Dictionary<string, BadgeData> _badgeNameToLatestData = ...`
- L237 _private* field_ `readonly Dictionary< _badgeNameToLatestData = new Dictionary<string, BadgeData>()`
- L238 _private* field_ `readonly ILogger _logger`
- L239 _private* field_ `readonly IAsyncDisposer _asyncDisposer`
- L240 _private* field_ `readonly LatestData _latestIds`
- L241 _private* field_ `HashSet<int> _filterChangeNumbers = new HashSet<int>()`
- L244 _private* field_ `readonly SortedSet<EventData> _investigationEvents = new SortedSet<EventData>( Comparer<EventData>.Create((first, second) => { int clOrder = second.Change.CompareTo(first.Change); return clOrder != 0 ? clOrder : first.Id.CompareTo(second.Id); }))`
- L250 _private* field_ `SortedSet<EventData>? _activeInvestigations = null`
- L253 _private* field_ `readonly string _metadataStream`
- L254 _private* field_ `readonly string _metadataProject`
- L255 _private* field_ `readonly ConcurrentQueue<GetMetadataResponseV2> _incomingMetadata = new ConcurrentQueue<GetMetadataResponseV2>()`
- L256 _private* field_ `int _minChange`
- L257 _private* field_ `int _newMinChange`
- L258 _private* field_ `long _metadataSequenceNumber`
- L260 _public field_ `public Action? OnUpdatesReady`
- L262-298 _public ctor_ `public EventMonitor(string? inApiUrl, string inProject, string inCurrentUserName, IServiceProvider serviceProvider)`
- L300-303 _public method_ `public void Start()`
- L305-315 _public method_ `public void Dispose()`
- L317-371 _public method_ `public void FilterChanges(IEnumerable<int> changeNumbers)`
- L373-383 _protected method_ `protected EventSummary FindOrAddSummary(int changeNumber)`
- L385-389 _public property_ `public string LastStatusMessage { get; set; }`
- L391-416 _public method_ `public void ApplyUpdates()`
- L418-465 _private* method_ `void ApplyEventUpdate(EventData evt)`
- L467-492 _private* method_ `void ApplyBadgeUpdate(BadgeData badge)`
- L494-503 _private* method_ `void ApplyCommentUpdate(CommentData comment)`
- L505-528 _private* method_ `static bool AddPerUserItem<T>(List<T> items, T newItem, Func<T, long> idSelector, Func<T, string> userSelector)`
- L530-547 _private* method_ `static EventType? GetEventTypeFromVote(UgsUserVote? state)`
- L549-586 _private* method_ `void ConvertMetadataToEvents(GetMetadataResponseV2 metadata)`
- L588-643 _private* method_ `void PostEvents(GetMetadataResponseV2 metadata)`
- L645-669 _private* method_ `static ReviewVerdict GetVerdict(IEnumerable<EventData> events, IEnumerable<BadgeData> badges)`
- L671-685 _private* method_ `static ReviewVerdict GetVerdict(int numPositive, int numNegative)`
- L687-708 _private* method_ `void ApplyFilteredUpdate(EventData evt)`
- L710-761 _private* method_ `async Task PollForUpdatesAsync(CancellationToken cancellationToken)`
- L763-777 _public method_ `public static bool HasNetCore3()`
- L779-800 _private* method_ `async Task<bool> SendEventToBackendAsync(EventData evt, CancellationToken cancellationToken)`
- L802-824 _private* method_ `async Task<bool> SendCommentToBackendAsync(CommentData comment, CancellationToken cancellationToken)`
- L826-873 _private* method_ `async Task SendMetadataUpdateUpdateV2Async(int change, string userName, EventType? evt, string? comment, CancellationToken cancellationToken)`
- L875-981 _private* method_ `async Task<bool> ReadEventsFromBackendAsync(bool fireThrottledRequests, CancellationToken cancellationToken)`
- L983-999 _public method_ `public void PostEvent(int changeNumber, EventType type)`
- L1001-1017 _public method_ `public void PostComment(int changeNumber, string text)`
- L1019-1037 _public method_ `public bool GetCommentByCurrentUser(int changeNumber, [NotNullWhen(true)] out string? commentText)`
- L1039-1054 _public method_ `public EventData? GetReviewByCurrentUser(int changeNumber)`
- L1056-1061 _public method_ `public EventSummary? GetSummaryForChange(int changeNumber)`
- L1063-1066 _public method_ `public bool TryGetLatestBadge(string buildType, [NotNullWhen(true)] out BadgeData? badgeData)`
- L1068-1071 _public method_ `public static bool IsReview(EventType type)`
- L1073-1076 _public method_ `public static bool IsPositiveReview(EventType type)`
- L1078-1081 _public method_ `public static bool IsNegativeReview(EventType type)`
- L1083-1087 _public method_ `public bool WasSyncedByCurrentUser(int changeNumber)`
- L1089-1092 _public method_ `public void StartInvestigating(int changeNumber)`
- L1094-1097 _public method_ `public void FinishInvestigating(int changeNumber)`
- L1099-1118 _protected method_ `protected void UpdateActiveInvestigations()`
- L1120-1124 _public method_ `public bool IsUnderInvestigation(int changeNumber)`
- L1126-1130 _public method_ `public bool IsUnderInvestigationByCurrentUser(int changeNumber)`
- L1132-1136 _public method_ `public IEnumerable<string> GetInvestigatingUsers(int changeNumber)`
- L1138-1157 _public method_ `public int GetInvestigationStartChangeNumber(int lastChangeNumber)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/FindFoldersToCleanTask.cs` (UnrealGameSync)


#### class `UnrealGameSync.FolderToClean`  
`class FolderToClean`  
_internal*; L15-33_
- L17 _public field_ `public DirectoryInfo _directory`
- L18 _public field_ `public Dictionary<string, FolderToClean> _nameToSubFolder = ...`
- L18 _public field_ `public Dictionary< _nameToSubFolder = new Dictionary<string, FolderToClean>(StringComparer.InvariantCultureIgnoreCase)`
- L19 _public field_ `public Dictionary<string, FileInfo> _nameToFile = ...`
- L19 _public field_ `public Dictionary< _nameToFile = new Dictionary<string, FileInfo>(StringComparer.InvariantCultureIgnoreCase)`
- L20 _public field_ `public List<FileInfo> _filesToDelete = new List<FileInfo>()`
- L21 _public field_ `public List<FileInfo> _filesToSync = new List<FileInfo>()`
- L22 _public field_ `public bool _emptyLeaf = false`
- L23 _public field_ `public bool _emptyAfterClean = true`
- L25-28 _public ctor_ `public FolderToClean(DirectoryInfo inDirectory)`
- L30 _public property_ `public string Name => ...`
- L32 _public method_ `public override string ToString()`

#### class `UnrealGameSync.FindFoldersToCleanTask`  
`class FindFoldersToCleanTask : IDisposable`  
_internal*; L35-333_
- inherits: `IDisposable`
- L43 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L44 _private* field_ `readonly string _clientRootPath`
- L45 _private* field_ `readonly IReadOnlyList<string> _syncPaths`
- L46 _private* field_ `readonly ILogger _logger`
- L47 _private* field_ `readonly FolderToClean _rootFolderToClean`
- L49 _private* field_ `int _remainingFoldersToScan`
- L50 _private* field_ `ManualResetEvent _finishedScan = new ManualResetEvent(false)`
- L51 _private* field_ `bool _abortScan`
- L52 _private* field_ `string? _scanError`
- L54 _public field_ `public List<string> FileNames = new List<string>()`
- L56-64 _public ctor_ `public FindFoldersToCleanTask(IPerforceSettings inPerforceSettings, FolderToClean inRootFolderToClean, string inClientRootPath, IReadOnlyList<string> inSyncPaths, ILogger logger)`
- L66-73 _private* method_ `void QueueFolderToPopulate(FolderToClean folder)`
- L75-108 _private* method_ `void PopulateFolder(FolderToClean folder)`
- L110-180 _private* method_ `static void MergeTrees(FolderToClean localFolder, PerforceHaveFolder? perforceFolder, HashSet<string> openClientPaths, string? perforceConfigFile)`
- L182-193 _private* method_ `static bool IsFileTypeWritable(string? type)`
- L195-203 _private* method_ `static void RemoveEmptyFolders(FolderToClean folder)`
- L205-215 _public method_ `public void Dispose()`
- L217-332 _public method_ `public async Task RunAsync(CancellationToken cancellationToken)`

#### class `UnrealGameSync.FindFoldersToCleanTask.PerforceHaveFolder`  
`class PerforceHaveFolder`  
_private*; L37-41_
- L39 _public field_ `public Dictionary<string, PerforceHaveFolder> _nameToSubFolder = ...`
- L39 _public field_ `public Dictionary< _nameToSubFolder = new Dictionary<string, PerforceHaveFolder>(StringComparer.OrdinalIgnoreCase)`
- L40 _public field_ `public Dictionary<string, FStatRecord> _nameToFile = ...`
- L40 _public field_ `public Dictionary< _nameToFile = new Dictionary<string, FStatRecord>(StringComparer.OrdinalIgnoreCase)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ApplicationSettingsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ApplicationSettingsWindow`  
`partial class ApplicationSettingsWindow`  
_internal*; L5-559_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-522 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L525 _private field_ `private System.Windows.Forms.Label label1`
- L526 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L527 _private field_ `private System.Windows.Forms.Button OkBtn`
- L528 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L529 _private field_ `private System.Windows.Forms.Button ViewLogBtn`
- L530 _private field_ `private System.Windows.Forms.Label label3`
- L531 _private field_ `private TextBoxWithCueBanner ServerTextBox`
- L532 _private field_ `private TextBoxWithCueBanner UserNameTextBox`
- L533 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L534 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L535 _private field_ `private System.Windows.Forms.CheckBox AutomaticallyRunAtStartupCheckBox`
- L536 _private field_ `private System.Windows.Forms.CheckBox KeepInTrayCheckBox`
- L537 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L538 _private field_ `private System.Windows.Forms.GroupBox groupBox4`
- L539 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L540 _private field_ `private System.Windows.Forms.CheckBox EnableAutomationCheckBox`
- L541 _private field_ `private System.Windows.Forms.TextBox AutomationPortTextBox`
- L542 _private field_ `private System.Windows.Forms.Label label2`
- L543 _private field_ `private System.Windows.Forms.NumericUpDown ParallelSyncThreadsSpinner`
- L544 _private field_ `private System.Windows.Forms.Button AdvancedBtn`
- L545 _private field_ `private System.Windows.Forms.CheckBox EnableProtocolHandlerCheckBox`
- L546 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L547 _private field_ `private System.Windows.Forms.GroupBox groupBox5`
- L548 _private field_ `private System.Windows.Forms.CheckedListBox CustomToolsListBox`
- L549 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel6`
- L550 _private field_ `private System.Windows.Forms.GroupBox groupBox3`
- L551 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4`
- L552 _private field_ `private TextBoxWithCueBanner HordeServerTextBox`
- L553 _private field_ `private System.Windows.Forms.Label label4`
- L554 _private field_ `private System.Windows.Forms.Button UpdateSettingsBtn`
- L555 _private field_ `private System.Windows.Forms.GroupBox groupBox6`
- L556 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel7`
- L557 _private field_ `private System.Windows.Forms.Label label5`
- L558 _private field_ `private System.Windows.Forms.ComboBox ThemeComboBox`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ApplicationSettingsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ApplicationSettingsWindow`  
`partial class ApplicationSettingsWindow : ThemedForm`  
_internal*; L17-427_
- inherits: `ThemedForm`
- L42 _private* field_ `readonly string _originalExecutableFileName`
- L43 _private* field_ `readonly UserSettings _settings`
- L44 _private* field_ `readonly ILogger _logger`
- L46 _private* field_ `readonly int _initialAutomationPortNumber`
- L47 _private* field_ `readonly ProtocolHandlerState _initialProtocolHandlerState`
- L49 _private* field_ `readonly ToolUpdateMonitor _toolUpdateMonitor`
- L50 _private* field_ `readonly Tuple<bool, string> _toolUpdateStatus`
- L50 _private* field_ `readonly Tuple< _toolUpdateStatus`
- L52 _private* field_ `Result _result = Result.Ok`
- L94-204 _private ctor_ `private ApplicationSettingsWindow(IPerforceSettings defaultPerforceSettings, string originalExecutableFileName, UserSettings settings, ToolUpdateMonitor toolUpdateMonitor, ILogger<ApplicationSettingsWindow> logger)`
- L206-216 _private* method_ `static void FindDependencies(ToolItem toolItem, HashSet<ToolItem> dependsOnToolItems, Dictionary<Guid, ToolItem> idToToolItem)`
- L218-223 _public method_ `public static Result ShowModal(IWin32Window owner, IPerforceSettings defaultPerforceSettings, string originalExecutableFileName, UserSettings settings, ToolUpdateMonitor toolUpdateMonitor, ILogger<ApplicationSettingsWindow> logger)`
- L225-229 _private method_ `private static bool IsAutomaticallyRunAtStartup()`
- L231-247 _private method_ `private void UpdateSettingsBtn_Click(object sender, EventArgs e)`
- L249-252 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L254-371 _private method_ `private void ApplySettings(Result result)`
- L373-377 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L379-382 _private method_ `private void EnableAutomationCheckBox_CheckedChanged(object sender, EventArgs e)`
- L384-388 _private method_ `private void AdvancedBtn_Click(object sender, EventArgs e)`
- L390 _private* field_ `bool _recursiveItemCheck = false`
- L392-426 _private method_ `private void CustomToolsListBox_ItemCheck(object sender, ItemCheckEventArgs e)`

#### enum `UnrealGameSync.ApplicationSettingsWindow.Result`  
`public enum Result`  
_public; L19-26_
- L21 _public* enumerator_ `Cancel`
- L22 _public* enumerator_ `Ok`
- L23 _public* enumerator_ `Quit`
- L24 _public* enumerator_ `Restart`
- L25 _public* enumerator_ `RestartAndConfigureUpdate`

#### class `UnrealGameSync.ApplicationSettingsWindow.PerforceTestConnectionTask`  
`static class PerforceTestConnectionTask`  
_private*; L28-40_
- L30-39 _public method_ `public static async Task RunAsync(IPerforceConnection perforce, string depotPath, CancellationToken cancellationToken)`

#### class `UnrealGameSync.ApplicationSettingsWindow.ToolItem`  
`class ToolItem`  
_private*; L54-92_
- L56 _public property_ `public Guid Id => ...`
- L58 _public property_ `public int Index { get; }`
- L59 _public property_ `public ToolInfo Definition { get; }`
- L60 _public property_ `public List<ToolItem> RequiresTools { get; }`
- L62 _public property_ `public bool Enabled { get; set; }`
- L63 _public property_ `public int DependencyRefCount { get; set; }`
- L65-70 _public ctor_ `public ToolItem(int index, ToolInfo definition, bool enabled)`
- L72-86 _public method_ `public CheckState GetCheckState()`
- L88-91 _public method_ `public override string ToString()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ArgumentsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ArgumentsWindow`  
`partial class ArgumentsWindow`  
_internal*; L5-186_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-174 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L178 _private field_ `private System.Windows.Forms.Button OkButton`
- L179 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L180 _private field_ `private System.Windows.Forms.ListView ArgumentsList`
- L181 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L182 _private field_ `private System.Windows.Forms.Button MoveUpButton`
- L183 _private field_ `private System.Windows.Forms.Button MoveDownButton`
- L184 _private field_ `private System.Windows.Forms.Button ResetToDefaultsButton`
- L185 _private field_ `private System.Windows.Forms.CheckBox PromptBeforeLaunchCheckBox`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ArgumentsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ArgumentsWindow`  
`public partial class ArgumentsWindow : ThemedForm`  
_public; L12-369_
- inherits: `ThemedForm`
- L14 _private* const_ `const int LvmFirst = 0x1000`
- L15 _private* const_ `const int LvmEditlabelw = (LvmFirst + 118)`
- L17 _private* const_ `const int EmSetsel = 0xb1`
- L20 _private* method_ `static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)` — attrs: `[DllImport("user32.dll", CharSet = CharSet.Auto)]`
- L23 _private* method_ `static extern bool SetWindowText(IntPtr hWnd, string text)` — attrs: `[DllImport("user32.dll")]`
- L25 _private field_ `private readonly List<LockableEditorArgument> _defaultEditorArguments = new List<LockableEditorArgument>()`
- L27-74 _public ctor_ `public ArgumentsWindow(List<LockableEditorArgument> arguments, List<LockableEditorArgument> defaultArguments, bool promptBeforeLaunch)`
- L76 _public property_ `public bool PromptBeforeLaunch => ...`
- L78-87 _public method_ `public List<LockableEditorArgument> GetItems()`
- L89-94 _private method_ `private void ClearButton_Click(object sender, EventArgs e)`
- L96-111 _private method_ `private void ArgumentsList_AfterLabelEdit(object sender, LabelEditEventArgs e)`
- L113-127 _private method_ `private void ArgumentsList_BeforeLabelEdit(object sender, LabelEditEventArgs e)`
- L129-161 _private method_ `private void ArgumentsList_MouseClick(object sender, MouseEventArgs e)`
- L163 _private* const_ `const int CheckBoxPadding = 5`
- L165-179 _private method_ `private void ArgumentsList_DrawItem(object sender, DrawListViewItemEventArgs e)`
- L181-195 _private method_ `private void DrawItemLabel(Graphics graphics, Color normalColor, ListViewItem item)`
- L197-207 _private method_ `private Rectangle GetLabelRectangle(Graphics graphics, ListViewItem item)`
- L209-228 _private method_ `private void ArgumentsList_KeyUp(object sender, KeyEventArgs e)`
- L230-256 _private method_ `private void ArgumentsList_KeyPress(object sender, KeyPressEventArgs e)`
- L258-270 _private method_ `private void MoveUpButton_Click(object sender, EventArgs e)`
- L272-284 _private method_ `private void MoveDownButton_Click(object sender, EventArgs e)`
- L286-301 _private method_ `private void ResetToDefaultsButton_Click(object sender, EventArgs e)`
- L303-306 _private method_ `private void ArgumentsList_SelectedIndexChanged(object sender, EventArgs e)`
- L308-313 _private method_ `private void UpdateMoveButtons()`
- L315-325 _private method_ `private LockableEditorArgument? GetDefaultArgumentForItem(ListViewItem item)`
- L327-335 _private method_ `private LockableEditorArgument? GetDefaultArgumentForItem(int index)`
- L337-358 _private method_ `private string GetDefaultArgumentDebugText(ListViewItem item)`
- L360-368 _private method_ `private void ArgumentsList_ItemCheck(object? sender, ItemCheckEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/AutomatedBuildWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.AutomatedBuildWindow`  
`partial class AutomatedBuildWindow`  
_internal*; L3-355_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-331 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L335 _private field_ `private System.Windows.Forms.LinkLabel ChangeLink`
- L336 _private field_ `private System.Windows.Forms.Label ServerLabel`
- L337 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L338 _private field_ `private System.Windows.Forms.Button OkBtn`
- L339 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L340 _private field_ `private System.Windows.Forms.GroupBox groupBox3`
- L341 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L342 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L343 _private field_ `private System.Windows.Forms.CheckBox ExecCommandCheckBox`
- L344 _private field_ `private System.Windows.Forms.TextBox ExecCommandTextBox`
- L345 _private field_ `private System.Windows.Forms.CheckBox SyncToChangeCheckBox`
- L346 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L347 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L348 _private field_ `private System.Windows.Forms.Label WorkspaceNameLabel`
- L349 _private field_ `private System.Windows.Forms.TextBox WorkspaceNameTextBox`
- L350 _private field_ `private System.Windows.Forms.Button WorkspaceNameNewBtn`
- L351 _private field_ `private System.Windows.Forms.Button WorkspaceNameBrowseBtn`
- L352 _private field_ `private System.Windows.Forms.Label WorkspacePathLabel`
- L353 _private field_ `private System.Windows.Forms.TextBox WorkspacePathTextBox`
- L354 _private field_ `private System.Windows.Forms.Button WorkspacePathBrowseBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/AutomatedBuildWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.AutomatedBuildWindow`  
`partial class AutomatedBuildWindow : ThemedForm`  
_internal*; L11-201_
- inherits: `ThemedForm`
- L29 _private* field_ `readonly string _streamName`
- L30 _private* field_ `readonly IServiceProvider _serviceProvider`
- L32 _private* field_ `string? _serverAndPortOverride`
- L33 _private* field_ `string? _userNameOverride`
- L34 _private* field_ `readonly IPerforceSettings _defaultPerforceSettings`
- L35 _private* field_ `readonly UserSettings _settings`
- L37 _private* field_ `BuildInfo? _result`
- L39-72 _private ctor_ `private AutomatedBuildWindow(string streamName, int changelist, string command, IPerforceSettings defaultPerforceSettings, string? defaultWorkspaceName, string? defaultProjectPath, UserSettings settings, IServiceProvider serviceProvider)`
- L74 _private property_ `private IPerforceSettings Perforce => ...`
- L76-109 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings defaultPerforceSettings, string streamName, string projectPath, int changelist, string command, UserSettings settings, IServiceProvider loggerFactory, [NotNullWhen(true)] out BuildInfo? buildInfo)`
- L111-117 _private method_ `private void ChangeLink_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L119-122 _private method_ `private void UpdateServerLabel()`
- L124-132 _private method_ `private void WorkspaceNameNewBtn_Click(object sender, EventArgs e)`
- L134-142 _private method_ `private void WorkspaceNameBrowseBtn_Click(object sender, EventArgs e)`
- L144-147 _private method_ `private void UpdateOkButton()`
- L149-158 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L160-163 _private method_ `private void ExecCommandCheckBox_CheckedChanged(object sender, EventArgs e)`
- L165-168 _private method_ `private void UpdateWorkspacePathBrowseButton()`
- L170-182 _private method_ `private void WorkspacePathBrowseBtn_Click(object sender, EventArgs e)`
- L184-195 _private method_ `private bool TryGetWorkspaceName([NotNullWhen(true)] out string? workspaceName)`
- L197-200 _private method_ `private void WorkspaceNameTextBox_TextChanged(object sender, EventArgs e)`

#### class `UnrealGameSync.Forms.AutomatedBuildWindow.BuildInfo`  
`public class BuildInfo`  
_public; L13-27_
- L15 _public property_ `public AutomatedSyncWindow.WorkspaceInfo SelectedWorkspaceInfo { get; }`
- L16 _public property_ `public string ProjectPath { get; }`
- L17 _public property_ `public bool Sync { get; }`
- L18 _public property_ `public string ExecCommand { get; }`
- L20-26 _public ctor_ `public BuildInfo(AutomatedSyncWindow.WorkspaceInfo selectedWorkspaceInfo, string projectPath, bool sync, string execCommand)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/AutomatedSyncWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.AutomatedSyncWindow`  
`partial class AutomatedSyncWindow`  
_internal*; L3-214_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-199 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L203 _private field_ `private System.Windows.Forms.TextBox ProjectTextBox`
- L204 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L205 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L206 _private field_ `private System.Windows.Forms.Button OkBtn`
- L207 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L208 _private field_ `private System.Windows.Forms.LinkLabel ChangeLink`
- L209 _private field_ `private System.Windows.Forms.Label ServerLabel`
- L210 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L211 _private field_ `private System.Windows.Forms.TextBox WorkspaceNameTextBox`
- L212 _private field_ `private System.Windows.Forms.Button WorkspaceNameNewBtn`
- L213 _private field_ `private System.Windows.Forms.Button WorkspaceNameBrowseBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/AutomatedSyncWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.AutomatedSyncWindow`  
`partial class AutomatedSyncWindow : ThemedForm`  
_internal*; L20-237_
- inherits: `ThemedForm`
- L95 _private* field_ `readonly string _streamName`
- L96 _private* field_ `readonly IServiceProvider _serviceProvider`
- L98 _private* field_ `string? _serverAndPortOverride`
- L99 _private* field_ `string? _userNameOverride`
- L100 _private* field_ `readonly IPerforceSettings _defaultPerforceSettings`
- L101 _private* field_ `readonly UserSettings _settings`
- L102 _private* field_ `WorkspaceInfo? _selectedWorkspaceInfo`
- L104-129 _private ctor_ `private AutomatedSyncWindow(string streamName, string projectPath, string? workspaceName, IPerforceSettings defaultPerforceSettings, UserSettings settings, IServiceProvider serviceProvider)`
- L131 _private property_ `private IPerforceSettings Perforce => ...`
- L133-138 _public method_ `public static string? FindDefaultWorkspace(IWin32Window owner, IPerforceSettings defaultPerforceSettings, string streamName, IServiceProvider serviceProvider)`
- L140-155 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings defaultPerforceSettings, string streamName, string projectPath, UserSettings settings, [NotNullWhen(true)] out WorkspaceInfo? workspaceInfo, IServiceProvider serviceProvider)`
- L157-163 _private method_ `private void ChangeLink_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L165-169 _private method_ `private void UpdateServerLabel()`
- L171-179 _private method_ `private void WorkspaceNameNewBtn_Click(object sender, EventArgs e)`
- L181-189 _private method_ `private void WorkspaceNameBrowseBtn_Click(object sender, EventArgs e)`
- L191-194 _private method_ `private void UpdateOkButton()`
- L196-227 _public method_ `public static bool ValidateWorkspace(IWin32Window owner, IPerforceSettings perforce, string workspaceName, string streamName, IServiceProvider serviceProvider, [NotNullWhen(true)] out WorkspaceInfo? selectedWorkspaceInfo)`
- L229-236 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`

#### class `UnrealGameSync.AutomatedSyncWindow.FindDefaultWorkspaceTask`  
`static class FindDefaultWorkspaceTask`  
_private*; L22-49_
- L24-48 _public method_ `public static async Task<string?> RunAsync(IPerforceConnection perforce, string streamName, CancellationToken cancellationToken)`

#### class `UnrealGameSync.AutomatedSyncWindow.ValidateWorkspaceTask`  
`class ValidateWorkspaceTask`  
_private*; L51-77_
- L53 _public property_ `public string WorkspaceName { get; }`
- L54 _public property_ `public string StreamName { get; }`
- L55 _public property_ `public bool RequiresStreamSwitch { get; set; }`
- L56 _public property_ `public bool HasOpenFiles { get; set; }`
- L58-62 _public ctor_ `public ValidateWorkspaceTask(string workspaceName, string streamName)`
- L64-76 _public method_ `public async Task RunAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`

#### class `UnrealGameSync.AutomatedSyncWindow.WorkspaceInfo`  
`public class WorkspaceInfo`  
_public; L79-93_
- L81 _public property_ `public string ServerAndPort { get; }`
- L82 _public property_ `public string UserName { get; }`
- L83 _public property_ `public string WorkspaceName { get; }`
- L84 _public property_ `public bool RequiresStreamSwitch { get; }`
- L86-92 _public ctor_ `public WorkspaceInfo(string serverAndPort, string userName, string workspaceName, bool requiresStreamSwitch)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/BuildStepWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.BuildStepWindow`  
`partial class BuildStepWindow`  
_internal*; L5-528_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-489 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L493 _private field_ `private System.Windows.Forms.Label label1`
- L494 _private field_ `private System.Windows.Forms.TextBox DescriptionTextBox`
- L495 _private field_ `private System.Windows.Forms.Label label2`
- L496 _private field_ `private System.Windows.Forms.TextBox DurationTextBox`
- L497 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L498 _private field_ `private System.Windows.Forms.Button OtherFileNameButton`
- L499 _private field_ `private System.Windows.Forms.TextBox OtherFileNameTextBox`
- L500 _private field_ `private System.Windows.Forms.TextBox CookFileNameTextBox`
- L501 _private field_ `private System.Windows.Forms.RadioButton OtherRadioButton`
- L502 _private field_ `private System.Windows.Forms.RadioButton CookRadioButton`
- L503 _private field_ `private System.Windows.Forms.TextBox CompileArgumentsTextBox`
- L504 _private field_ `private System.Windows.Forms.ComboBox CompileConfigComboBox`
- L505 _private field_ `private System.Windows.Forms.ComboBox CompilePlatformComboBox`
- L506 _private field_ `private System.Windows.Forms.RadioButton CompileRadioButton`
- L507 _private field_ `private System.Windows.Forms.Button OkButton`
- L508 _private field_ `private System.Windows.Forms.Button NewCancelButton`
- L509 _private field_ `private System.Windows.Forms.ComboBox CompileTargetComboBox`
- L510 _private field_ `private System.Windows.Forms.Button CookFileNameButton`
- L511 _private field_ `private System.Windows.Forms.Label label6`
- L512 _private field_ `private System.Windows.Forms.Label label5`
- L513 _private field_ `private UnrealGameSync.Controls.ReadOnlyCheckbox OtherUseLogWindowCheckBox`
- L514 _private field_ `private System.Windows.Forms.TextBox StatusTextTextBox`
- L515 _private field_ `private System.Windows.Forms.Label label4`
- L516 _private field_ `private System.Windows.Forms.Label label9`
- L517 _private field_ `private System.Windows.Forms.Label label8`
- L518 _private field_ `private System.Windows.Forms.Label label7`
- L519 _private field_ `private System.Windows.Forms.GroupBox groupBox3`
- L520 _private field_ `private System.Windows.Forms.GroupBox groupBox4`
- L521 _private field_ `private System.Windows.Forms.Button VariablesButton`
- L522 _private field_ `private System.Windows.Forms.Button OtherWorkingDirButton`
- L523 _private field_ `private System.Windows.Forms.Label label3`
- L524 _private field_ `private System.Windows.Forms.TextBox OtherWorkingDirTextBox`
- L525 _private field_ `private System.Windows.Forms.TextBox OtherArgumentsTextBox`
- L526 _private field_ `private System.Windows.Forms.Label label10`
- L527 _private field_ `private System.Windows.Forms.TextBox StatusPanelLinkTextBox`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/BuildStepWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.BuildStepWindow`  
`partial class BuildStepWindow : ThemedForm`  
_internal*; L13-279_
- inherits: `ThemedForm`
- L15 _private* field_ `readonly BuildStep _step`
- L16 _private* field_ `readonly List<string> _targetNames`
- L17 _private* field_ `readonly DirectoryReference _baseDirectory`
- L18 _private* field_ `readonly IReadOnlyDictionary<string, string> _variables`
- L18 _private* field_ `readonly IReadOnlyDictionary< _variables`
- L20 _private* field_ `VariablesWindow? _variablesWindow`
- L23-35 _public ctor_ `public BuildStepWindow(BuildStep inTask, List<string> inTargetNames, DirectoryReference inBaseDirectory, IReadOnlyDictionary<string, string> inVariables)`
- L37-80 _private method_ `private void BuildTaskWindow_Load(object sender, EventArgs e)`
- L82-101 _public method_ `public void UpdateType()`
- L103-106 _private method_ `private void CompileRadioButton_CheckedChanged(object sender, EventArgs e)`
- L108-111 _private method_ `private void CookRadioButton_CheckedChanged(object sender, EventArgs e)`
- L113-116 _private method_ `private void OtherRadioButton_CheckedChanged(object sender, EventArgs e)`
- L118-165 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L167-171 _private method_ `private void NewCancelButton_Click(object sender, EventArgs e)`
- L173-182 _private method_ `private void CookFileNameButton_Click(object sender, EventArgs e)`
- L184-193 _private method_ `private void OtherFileNameButton_Click(object sender, EventArgs e)`
- L195-203 _private method_ `private void OtherWorkingDirButton_Click(object sender, EventArgs e)`
- L205-219 _private method_ `private string AddBaseDirectory(string fileName)`
- L221-232 _private method_ `private string RemoveBaseDirectory(string fileName)`
- L234-237 _private method_ `private void OnClosedVariablesWindow(object? sender, EventArgs e)`
- L239-257 _private method_ `private void InsertVariable(string name)`
- L259-278 _private method_ `private void VariablesButton_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ChangelistWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ChangelistWindow`  
`partial class ChangelistWindow`  
_internal*; L5-109_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-101 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L105 _private field_ `private System.Windows.Forms.TextBox ChangeNumberTextBox`
- L106 _private field_ `private System.Windows.Forms.Button OkBtn`
- L107 _private field_ `private System.Windows.Forms.Label label1`
- L108 _private field_ `private System.Windows.Forms.Button CancelBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ChangelistWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ChangelistWindow`  
`public partial class ChangelistWindow : ThemedForm`  
_public; L8-44_
- inherits: `ThemedForm`
- L10 _public property_ `public int ChangeNumber { get; set; }`
- L12-22 _public ctor_ `public ChangelistWindow(int changeNumber)`
- L24-37 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L39-43 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/CleanWorkspaceWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.CleanWorkspaceWindow`  
`partial class CleanWorkspaceWindow`  
_internal*; L5-216_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-199 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L203 _private field_ `private System.Windows.Forms.TreeView TreeView`
- L204 _private field_ `private System.Windows.Forms.Button CleanBtn`
- L205 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L206 _private field_ `private System.Windows.Forms.Label label1`
- L207 _private field_ `private System.Windows.Forms.Button SelectAllBtn`
- L208 _private field_ `private System.Windows.Forms.ContextMenuStrip FolderContextMenu`
- L209 _private field_ `private System.Windows.Forms.ToolStripMenuItem FolderContextMenu_SelectAll`
- L210 _private field_ `private System.Windows.Forms.ToolStripMenuItem FolderContextMenu_SelectSafeToDelete`
- L211 _private field_ `private System.Windows.Forms.ToolStripMenuItem FolderContextMenu_SelectEmptyFolder`
- L212 _private field_ `private System.Windows.Forms.ToolStripMenuItem FolderContextMenu_SelectNone`
- L213 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator1`
- L214 _private field_ `private System.Windows.Forms.ToolStripMenuItem FolderContextMenu_OpenWithExplorer`
- L215 _private field_ `private System.Windows.Forms.Button SelectMissingBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/CleanWorkspaceWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.CleanWorkspaceWindow`  
`partial class CleanWorkspaceWindow : ThemedForm`  
_internal*; L19-520_
- inherits: `ThemedForm`
- L48 _private* field_ `static readonly CheckBoxState[] s_checkBoxStates = { CheckBoxState.UncheckedNormal, CheckBoxState.MixedNormal, CheckBoxState.CheckedNormal }`
- L55 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L56 _private* field_ `readonly FolderToClean _rootFolderToClean`
- L58 _private* field_ `static readonly string[] s_safeToDeleteFolders = { "/binaries/", "/intermediate/", "/build/receipts/", "/.vs/", "/automationtool/saved/rules/", "/saved/logs/", "/bin/debug/", "/bin/development/", "/bin/release/", "/obj/debug/", "/obj/development/",  ...`
- L89 _private* field_ `static readonly string[] s_safeToDeleteExtensions = { ".pdb", ".obj", ".sdf", ".suo", ".sln", ".csproj.user", ".csproj.references", }`
- L100 _private* field_ `readonly IReadOnlyList<string> _extraSafeToDeleteFolders`
- L101 _private* field_ `readonly IReadOnlyList<string> _extraSafeToDeleteExtensions`
- L102 _private* field_ `readonly ILogger _logger`
- L105 _private method_ `private static extern int ExtractIconEx(string sFile, int iIndex, IntPtr piLargeVersion, out IntPtr piSmallVersion, int amountIcons)` — attrs: `[DllImport("Shell32.dll", EntryPoint = "ExtractIconExW", CharSet = CharSet.Unicode, ExactSpelling = true, CallingConvention = CallingConvention.StdCall)]`
- L107-117 _private ctor_ `private CleanWorkspaceWindow(IPerforceSettings perforceSettings, FolderToClean rootFolderToClean, string[] extraSafeToDeleteFolders, string[] extraSafeToDeleteExtensions, ILogger<CleanWorkspaceWindow> logger)`
- L119-144 _public method_ `public static bool DoClean(IWin32Window owner, IPerforceSettings perforceSettings, DirectoryReference localRootPath, string clientRootPath, IReadOnlyList<string> syncPaths, string[] extraSafeToDeleteFolders, string[] extraSafeToDeleteExtensions, ILogger<CleanWorkspaceWindow> logger)`
- L146-202 _private method_ `private void CleanWorkspaceWindow_Load(object sender, EventArgs e)`
- L204-301 _private method_ `private TreeNode BuildTreeViewStructure(FolderToClean folder, string folderPath, bool parentFolderSelected, int depth)`
- L303-306 _private method_ `private bool IsSafeToDeleteFolder(string folderPath)`
- L308-311 _private method_ `private bool IsSafeToDeleteFile(string name)`
- L313-316 _private method_ `private void TreeView_DrawNode(object sender, DrawTreeNodeEventArgs e)`
- L318-335 _private method_ `private void TreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)`
- L337-354 _private method_ `private static void SetSelected(TreeNode parentNode, SelectionType type)`
- L356-392 _private method_ `private static void SetSelectedOnChildren(TreeNode parentNode, SelectionType type)`
- L394-401 _private method_ `private static void UpdateImage(TreeNode node)`
- L403-425 _private method_ `private void CleanBtn_Click(object sender, EventArgs e)`
- L427-458 _private method_ `private static void FindSelection(TreeNode node, List<FileInfo> filesToSync, List<FileInfo> filesToDelete, List<DirectoryInfo> directoriesToDelete)`
- L460-469 _private method_ `private void SelectAllBtn_Click(object sender, EventArgs e)`
- L471-480 _private method_ `private void SelectMissingBtn_Click(object sender, EventArgs e)`
- L482-486 _private method_ `private void FolderContextMenu_SelectAll_Click(object sender, EventArgs e)`
- L488-492 _private method_ `private void FolderContextMenu_SelectSafeToDelete_Click(object sender, EventArgs e)`
- L494-498 _private method_ `private void FolderContextMenu_SelectEmptyFolder_Click(object sender, EventArgs e)`
- L500-504 _private method_ `private void FolderContextMenu_SelectNone_Click(object sender, EventArgs e)`
- L506-519 _private method_ `private void FolderContextMenu_OpenWithExplorer_Click(object sender, EventArgs e)`

#### enum `UnrealGameSync.CleanWorkspaceWindow.TreeNodeAction`  
`enum TreeNodeAction`  
_private*; L21-25_
- L23 _public* enumerator_ `Sync`
- L24 _public* enumerator_ `Delete`

#### class `UnrealGameSync.CleanWorkspaceWindow.TreeNodeData`  
`class TreeNodeData`  
_private*; L27-37_
- L29 _public field_ `public TreeNodeAction _action`
- L30 _public field_ `public FileInfo? _file`
- L31 _public field_ `public FolderToClean? _folder`
- L32 _public field_ `public int _numFiles`
- L33 _public field_ `public int _numSelectedFiles`
- L34 _public field_ `public int _numEmptySelectedFiles`
- L35 _public field_ `public int _numMissingSelectedFiles`
- L36 _public field_ `public int _numDefaultSelectedFiles`

#### enum `UnrealGameSync.CleanWorkspaceWindow.SelectionType`  
`enum SelectionType`  
_private*; L39-46_
- L41 _public* enumerator_ `All`
- L42 _public* enumerator_ `SafeToDelete`
- L43 _public* enumerator_ `Missing`
- L44 _public* enumerator_ `Empty`
- L45 _public* enumerator_ `None`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ClobberWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ClobberWindow`  
`partial class ClobberWindow`  
_internal*; L5-167_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-155 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L159 _private field_ `private System.Windows.Forms.ListView FileList`
- L160 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L161 _private field_ `private System.Windows.Forms.Button UncheckAll`
- L162 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L163 _private field_ `private System.Windows.Forms.Button ContinueButton`
- L164 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader2`
- L165 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L166 _private field_ `private System.Windows.Forms.Label label1`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ClobberWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ClobberWindow`  
`public partial class ClobberWindow : ThemedForm`  
_public; L11-69_
- inherits: `ThemedForm`
- L13 _private* field_ `readonly Dictionary<string, bool> _filesToClobber`
- L13 _private* field_ `readonly Dictionary< _filesToClobber`
- L15-46 _public ctor_ `public ClobberWindow(Dictionary<string, bool> inFilesToClobber, HashSet<string> inUncontrolledFiles)`
- L48-57 _private method_ `private void UncheckAll_Click(object sender, EventArgs e)`
- L59-68 _private method_ `private void ContinueButton_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/CombinedViewsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.CombinedViewsWindow`  
`partial class CombinedViewsWindow`  
_internal*; L5-162_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-150 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L154 _private field_ `private System.Windows.Forms.Panel TopPanel`
- L155 _private field_ `private System.Windows.Forms.FlowLayoutPanel ControlPanel`
- L156 _private field_ `private System.Windows.Forms.FlowLayoutPanel ViewsPanel`
- L157 _private field_ `private System.Windows.Forms.Button CopyToClipBoard`
- L158 _private field_ `private System.Windows.Forms.Label label1`
- L159 _private field_ `private System.Windows.Forms.TextBox SearchBox`
- L160 _private field_ `private System.Windows.Forms.ListBox Views`
- L161 _private field_ `private System.Windows.Forms.Button ClearSearch`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/CombinedViewsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.CombinedViewsWindow`  
`public partial class CombinedViewsWindow : ThemedForm`  
_public; L11-83_
- inherits: `ThemedForm`
- L13 _private field_ `private readonly IList<string> _views`
- L14-20 _public ctor_ `public CombinedViewsWindow(IList<string> views)`
- L22-35 _private method_ `private void CopyToClipBoard_Click(object sender, EventArgs e)`
- L37-40 _private method_ `private void SearchBox_TextChanged(object sender, EventArgs e)`
- L42-77 _private method_ `private void FilterViews(string search)`
- L79-82 _private method_ `private void ClearSearch_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ConnectWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ConnectWindow`  
`partial class ConnectWindow`  
_internal*; L3-203_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-190 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L193 _private field_ `private System.Windows.Forms.Label UserNameLabel`
- L194 _private field_ `private TextBoxWithCueBanner UserNameTextBox`
- L195 _private field_ `private TextBoxWithCueBanner ServerAndPortTextBox`
- L196 _private field_ `private System.Windows.Forms.Label ServerAndPortLabel`
- L197 _private field_ `private System.Windows.Forms.Button OkBtn`
- L198 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L199 _private field_ `private System.Windows.Forms.CheckBox UseDefaultConnectionSettings`
- L200 _private field_ `private System.Windows.Forms.Button BrowseUserBtn`
- L201 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L202 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ConnectWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ConnectWindow`  
`partial class ConnectWindow : ThemedForm`  
_internal*; L10-118_
- inherits: `ThemedForm`
- L12 _private* field_ `readonly IPerforceSettings _defaultPerforceSettings`
- L13 _private* field_ `string? _serverAndPortOverride`
- L14 _private* field_ `string? _userNameOverride`
- L15 _private* field_ `readonly IServiceProvider _serviceProvider`
- L17-41 _private ctor_ `private ConnectWindow(IPerforceSettings defaultPerforceSettings, string? serverAndPortOverride, string? userNameOverride, IServiceProvider serviceProvider)`
- L43-53 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings defaultSettings, ref string? serverAndPortOverride, ref string? userNameOverride, IServiceProvider serviceProvider)`
- L55-59 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L61-85 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L87-90 _private method_ `private void UseCustomSettings_CheckedChanged(object sender, EventArgs e)`
- L92-108 _private method_ `private void UpdateEnabledControls()`
- L110-117 _private method_ `private void BrowseUserBtn_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DeleteWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.DeleteWindow`  
`partial class DeleteWindow`  
_internal*; L5-152_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-141 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L145 _private field_ `private System.Windows.Forms.ListView FileList`
- L146 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L147 _private field_ `private System.Windows.Forms.Label label1`
- L148 _private field_ `private System.Windows.Forms.Button UncheckAll`
- L149 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L150 _private field_ `private System.Windows.Forms.Button ContinueButton`
- L151 _private field_ `private System.Windows.Forms.Button CheckAll`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DeleteWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.DeleteWindow`  
`public partial class DeleteWindow : ThemedForm`  
_public; L9-52_
- inherits: `ThemedForm`
- L11 _private* field_ `readonly Dictionary<string, bool> _filesToDelete`
- L11 _private* field_ `readonly Dictionary< _filesToDelete`
- L13-27 _public ctor_ `public DeleteWindow(Dictionary<string, bool> inFilesToDelete)`
- L29-35 _private method_ `private void UncheckAll_Click(object sender, EventArgs e)`
- L37-43 _private method_ `private void CheckAll_Click(object sender, EventArgs e)`
- L45-51 _private method_ `private void ContinueButton_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DiagnosticsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.DiagnosticsWindow`  
`partial class DiagnosticsWindow`  
_internal*; L5-128_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-119 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L123 _private field_ `private System.Windows.Forms.Button ApplicationDataButton`
- L124 _private field_ `private System.Windows.Forms.Button button2`
- L125 _private field_ `private System.Windows.Forms.TextBox DiagnosticsTextBox`
- L126 _private field_ `private System.Windows.Forms.Button SaveButton`
- L127 _private field_ `private System.Windows.Forms.Button WorkspaceDataButton`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DiagnosticsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.DiagnosticsWindow`  
`public partial class DiagnosticsWindow : ThemedForm`  
_public; L14-110_
- inherits: `ThemedForm`
- L16 _private* field_ `readonly DirectoryReference _appDataFolder`
- L17 _private* field_ `readonly DirectoryReference _workspaceDataFolder`
- L18 _private* field_ `readonly List<FileReference> _extraFiles`
- L20-30 _public ctor_ `public DiagnosticsWindow(DirectoryReference inAppDataFolder, DirectoryReference inWorkspaceDataFolder, string inDiagnosticsText, IEnumerable<FileReference> inExtraFiles)`
- L32-35 _private method_ `private void ViewApplicationDataButton_Click(object sender, EventArgs e)`
- L37-40 _private method_ `private void ViewWorkspaceDataButton_Click(object sender, EventArgs e)`
- L42-91 _private method_ `private void SaveButton_Click(object sender, EventArgs e)`
- L93-109 _private method_ `private static void AddFilesToZip(ZipArchive zip, DirectoryReference dataFolder, string relativeDir)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DownloadProgressWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.DownloadProgressWindow`  
`partial class DownloadProgressWindow`  
_internal*; L5-54_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-49 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L53 _private field_ `private System.Windows.Forms.Label StatusMessage`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DownloadProgressWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.DownloadProgressWindow`  
`public partial class DownloadProgressWindow : ThemedForm`  
_public; L11-101_
- inherits: `ThemedForm`
- L30 _private* field_ `readonly Func<IProgress<string>, CancellationToken, Task> _taskFunc`
- L30 _private* field_ `readonly Func< CancellationToken`
- L30 _private* field_ `readonly Func< _taskFunc`
- L31 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L32 _private* field_ `ExceptionDispatchInfo? _taskExceptionDispatchInfo`
- L33 _private* field_ `Task _task = Task.CompletedTask`
- L35 _public property_ `public Task Task => ...`
- L37-44 _private ctor_ `private DownloadProgressWindow(Func<IProgress<string>, CancellationToken, Task> taskFunc, CancellationToken cancellationToken)`
- L46-54 _protected method_ `protected override void Dispose(bool disposing)`
- L56-64 _public method_ `public static void Execute(Func<IProgress<string>, CancellationToken, Task> taskFunc, CancellationToken cancellationToken)`
- L66-72 _private method_ `private void UpdateStatus(string text)`
- L74-84 _private method_ `private async Task RunTaskAsync(SynchronizationContext syncContext)`
- L86-91 _private method_ `private void DownloadProcessWindow_Load(object sender, EventArgs e)`
- L93-100 _private method_ `private void DownloadProgressWindow_FormClosing(object sender, FormClosingEventArgs e)`

#### class `UnrealGameSync.Forms.DownloadProgressWindow.ProgressReporter`  
`class ProgressReporter : IProgress<string>`  
_private*; L13-28_
- inherits: `IProgress<string>`
- L15 _private* field_ `readonly DownloadProgressWindow _owner`
- L16 _private* field_ `readonly SynchronizationContext _syncContext`
- L18-22 _public ctor_ `public ProgressReporter(DownloadProgressWindow owner, SynchronizationContext syncContext)`
- L24-27 _public method_ `public void Report(string value)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DownloadSettingsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.DownloadSettingsWindow`  
`partial class DownloadSettingsWindow`  
_internal*; L5-235_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-220 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L224 _private field_ `private System.Windows.Forms.Button DownloadBtn`
- L225 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L226 _private field_ `private System.Windows.Forms.Button OutputFolderBrowseBtn`
- L227 _private field_ `private System.Windows.Forms.Label label1`
- L228 _private field_ `private System.Windows.Forms.TextBox OutputFolderText`
- L229 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L230 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L231 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L232 _private field_ `private System.Windows.Forms.Label label2`
- L233 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4`
- L234 _private field_ `private System.Windows.Forms.TextBox SourceText`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/DownloadSettingsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.DownloadSettingsWindow`  
`public partial class DownloadSettingsWindow : ThemedForm`  
_public; L10-49_
- inherits: `ThemedForm`
- L12-16 _public ctor_ `public DownloadSettingsWindow()`
- L18-32 _public method_ `public static bool Show(string source, string defaultOutputDir, [NotNullWhen(true)] out DirectoryReference? outputDir)`
- L34-43 _private method_ `private void OutputFolderBrowseBtn_Click(object sender, EventArgs e)`
- L45-48 _private method_ `private void DownloadSettingsWindow_Load(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/FailedToDeleteWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.FailedToDeleteWindow`  
`partial class FailedToDeleteWindow`  
_internal*; L5-95_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-88 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L92 _private field_ `private System.Windows.Forms.Button OkBtn`
- L93 _private field_ `private System.Windows.Forms.Label label1`
- L94 _public field_ `public System.Windows.Forms.TextBox FileList`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/FailedToDeleteWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.FailedToDeleteWindow`  
`public partial class FailedToDeleteWindow : ThemedForm`  
_public; L5-12_
- inherits: `ThemedForm`
- L7-11 _public ctor_ `public FailedToDeleteWindow()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueAlertWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueAlertWindow`  
`partial class IssueAlertWindow`  
_internal*; L5-240_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-227 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L231 _private field_ `private System.Windows.Forms.LinkLabel SummaryLabel`
- L232 _public field_ `public AlertButtonControl AcceptBtn`
- L233 _public field_ `public AlertButtonControl DeclineBtn`
- L234 _public field_ `public AlertButtonControl DetailsBtn`
- L235 _private field_ `private System.Windows.Forms.Label OwnerLabel`
- L236 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L237 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L238 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L239 _private field_ `private System.Windows.Forms.LinkLabel LatestBuildLinkLabel`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueAlertWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueAlertWindow`  
`partial class IssueAlertWindow : ThemedForm`  
_internal*; L13-262_
- inherits: `ThemedForm`
- L15 _private* field_ `static readonly IntPtr HwndTopmost = new IntPtr(-1)`
- L17 _private* const_ `const uint SwpNomove = 0x0002`
- L18 _private* const_ `const uint SwpNosize = 0x0001`
- L19 _private* const_ `const uint SwpNoactivate = 0x0010`
- L22 _private* method_ `static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int x, int y, int width, int height, uint flags)` — attrs: `[DllImport("user32.dll", SetLastError = true)]`
- L24 _public property_ `public IssueMonitor IssueMonitor { get; }`
- L27 _public property_ `public bool IsWarning { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L30 _public property_ `public bool? StrongAlert { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L32-41 _public ctor_ `public IssueAlertWindow(IssueMonitor issueMonitor, IssueData issue, IssueAlertReason reason)`
- L43-47 _public property_ `public IssueData Issue { get; set; }`
- L49-53 _public property_ `public IssueAlertReason Reason { get; set; }`
- L55-91 _protected method_ `protected override void OnPaintBackground(PaintEventArgs e)`
- L93-221 _public method_ `public void SetIssue(IssueData newIssue, IssueAlertReason newReason)`
- L223-229 _protected method_ `protected override void OnHandleCreated(EventArgs e)`
- L231 _protected property_ `protected override bool ShowWithoutActivation => ...`
- L233-236 _private method_ `private void SummaryLabel_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)`
- L238-241 _private method_ `private void IssueAlertWindow_Click(object sender, EventArgs e)`
- L243-261 _public method_ `public void LaunchUrl()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueBrowserWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueBrowserWindow`  
`partial class IssueBrowserWindow`  
_internal*; L5-288_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-265 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L269 _private field_ `private CustomListViewControl IssueListView`
- L270 _private field_ `private System.Windows.Forms.ColumnHeader IdHeader`
- L271 _private field_ `private System.Windows.Forms.ColumnHeader CreatedHeader`
- L272 _private field_ `private System.Windows.Forms.ColumnHeader ResolvedHeader`
- L273 _private field_ `private System.Windows.Forms.ColumnHeader DescriptionHeader`
- L274 _private field_ `private System.Windows.Forms.Button OkBtn`
- L275 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L276 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L277 _private field_ `private System.Windows.Forms.Label StatusLabel`
- L278 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L279 _private field_ `private System.Windows.Forms.LinkLabel FetchMoreResultsLinkLabel`
- L280 _private field_ `private System.Windows.Forms.ColumnHeader IconHeader`
- L281 _private field_ `private System.Windows.Forms.ColumnHeader OwnerHeader`
- L282 _private field_ `private System.Windows.Forms.Button FilterBtn`
- L283 _private field_ `private System.Windows.Forms.ContextMenuStrip FilterMenu`
- L284 _private field_ `private System.Windows.Forms.ToolStripMenuItem FilterMenu_ShowAll`
- L285 _private field_ `private System.Windows.Forms.ToolStripSeparator FilterMenu_Separator`
- L286 _private field_ `private System.Windows.Forms.Timer RefreshIssuesTimer`
- L287 _private field_ `private System.Windows.Forms.ColumnHeader TimeToFixHeader`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueBrowserWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueBrowserWindow`  
`partial class IssueBrowserWindow : ThemedForm`  
_internal*; L15-436_
- inherits: `ThemedForm`
- L17 _private* field_ `readonly IssueMonitor _issueMonitor`
- L18 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L19 _private* field_ `readonly TimeSpan? _serverTimeOffset`
- L20 _private* field_ `readonly IServiceProvider _serviceProvider`
- L21 _private* field_ `readonly string? _currentStream`
- L22 _private* field_ `int _maxResults = 0`
- L23 _private* field_ `int _pendingMaxResults = 0`
- L24 _private* field_ `string? _filterName`
- L25 _private* field_ `readonly Dictionary<string, Func<IssueData, bool>> _customFilters = ...`
- L25 _private* field_ `readonly Dictionary< IssueData`
- L25 _private* field_ `readonly Dictionary< _customFilters = new Dictionary<string, Func<IssueData, bool>>()`
- L26 _private* field_ `List<IssueData> _issues = new List<IssueData>()`
- L27 _private* field_ `readonly SynchronizationContext _mainThreadSynchronizationContext`
- L28 _private* field_ `Task? _backgroundTask`
- L29 _private* field_ `bool _disposed`
- L31-58 _public ctor_ `public IssueBrowserWindow(IssueMonitor issueMonitor, IPerforceSettings perforceSettings, TimeSpan? serverTimeOffset, IServiceProvider serviceProvider, string? currentStream, Dictionary<string, Func<IssueData, bool>> customFilters, string? filterName)`
- L60-72 _protected method_ `protected override void Dispose(bool disposing)`
- L74-77 _private method_ `private void IssueBrowserWindow_Load(object sender, EventArgs e)`
- L79-83 _private method_ `private void FetchMoreResults()`
- L85-122 _private* method_ `async Task FetchIssues(int newMaxResults, CancellationToken cancellationToken)`
- L124-134 _private* method_ `void FetchIssuesSuccess(int newMaxResults, List<IssueData> newIssues)`
- L136-141 _private* method_ `void FetchIssuesFailure(Exception ex)`
- L143-149 _private* method_ `void CheckToStartBackgroundThread()`
- L151-158 _private* method_ `void StartBackgroundThread()`
- L160-226 _private* method_ `void UpdateIssueList()`
- L228-238 _private* method_ `void IssueList_InsertItem(int itemIdx, IssueData issue, DateTime midnight)`
- L240-248 _private* method_ `void IssueList_UpdateItem(ListViewItem item, IssueData issue, DateTime midnight)`
- L250-260 _private* method_ `static string FormatIssueDateTime(DateTime dateTime, DateTime midnight)`
- L262 _private* field_ `static readonly List<IssueBrowserWindow> s_existingWindows = new List<IssueBrowserWindow>()`
- L264-282 _public method_ `public static void Show(Form owner, IssueMonitor issueMonitor, IPerforceSettings perforceSettings, TimeSpan? serverTimeOffset, IServiceProvider serviceProvider, string? currentStream, Dictionary<string, Func<IssueData, bool>> customFilters, string? defaultFilter)`
- L284-287 _private method_ `private void FetchMoreResultsLinkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L289-293 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L295-303 _private method_ `private void IssueListView_MouseDoubleClick(object sender, MouseEventArgs e)`
- L305-357 _private method_ `private void FilterBtn_Click(object sender, EventArgs e)`
- L359-363 _private method_ `private void FilterMenu_ShowAll_Click(object sender, EventArgs e)`
- L365-368 _private method_ `private void ShowIssue(IssueData issue)`
- L370-405 _private method_ `private void IssueListView_DrawItem(object sender, DrawListViewItemEventArgs e)`
- L407-430 _private method_ `private void IssueListView_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)`
- L432-435 _private method_ `private void RefreshIssuesTimer_Tick(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueDetailsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueDetailsWindow`  
`partial class IssueDetailsWindow`  
_internal*; L5-650_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-604 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L607 _private field_ `private System.Windows.Forms.Button OkBtn`
- L608 _private field_ `private System.Windows.Forms.Button AssignToOtherBtn`
- L609 _private field_ `private System.Windows.Forms.ContextMenuStrip BuildListContextMenu`
- L610 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_MoreInfo`
- L611 _private field_ `private System.Windows.Forms.ToolStripMenuItem BuildListContextMenu_Assign`
- L612 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator1`
- L613 _private field_ `private System.Windows.Forms.Label OpenSinceTextBox`
- L614 _private field_ `private System.Windows.Forms.Label label1`
- L615 _private field_ `private System.Windows.Forms.Label label3`
- L616 _private field_ `private System.Windows.Forms.Label label5`
- L617 _private field_ `private System.Windows.Forms.Label StatusTextBox`
- L618 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L619 _private field_ `private System.Windows.Forms.Button AssignToMeBtn`
- L620 _private field_ `private System.Windows.Forms.Button MarkFixedBtn`
- L621 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4`
- L622 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5`
- L623 _private field_ `private System.Windows.Forms.Label StepNamesTextBox`
- L624 _private field_ `private System.Windows.Forms.Label label2`
- L625 _private field_ `private System.Windows.Forms.Label label4`
- L626 _private field_ `private System.Windows.Forms.Label StreamNamesTextBox`
- L627 _private field_ `private System.Windows.Forms.ContextMenuStrip JobContextMenu`
- L628 _private field_ `private System.Windows.Forms.ToolStripSeparator JobContextMenu_StepSeparatorMin`
- L629 _private field_ `private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1`
- L630 _private field_ `private System.Windows.Forms.ToolStripMenuItem JobContextMenu_ViewJob`
- L631 _private field_ `private System.Windows.Forms.TabControl tabControl1`
- L632 _private field_ `private System.Windows.Forms.TabPage OutputTabPage`
- L633 _private field_ `private RichTextBox41 DetailsTextBox`
- L634 _private field_ `private System.Windows.Forms.TabPage ChangesTabPage`
- L635 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L636 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L637 _private field_ `private TextBoxWithCueBanner FilterTextBox`
- L638 _private field_ `private System.Windows.Forms.ComboBox FilterTypeComboBox`
- L639 _private field_ `private System.Windows.Forms.ComboBox StreamComboBox`
- L640 _private field_ `private CustomListViewControl BuildListView`
- L641 _private field_ `private System.Windows.Forms.ColumnHeader IconHeader`
- L642 _private field_ `private System.Windows.Forms.ColumnHeader ChangeHeader`
- L643 _private field_ `private System.Windows.Forms.ColumnHeader TypeHeader`
- L644 _private field_ `private System.Windows.Forms.ColumnHeader AuthorHeader`
- L645 _private field_ `private System.Windows.Forms.ColumnHeader DescriptionHeader`
- L646 _private field_ `private System.Windows.Forms.Label SummaryTextBox`
- L647 _private field_ `private System.Windows.Forms.Label label6`
- L648 _private field_ `private System.Windows.Forms.LinkLabel BuildLinkLabel`
- L649 _private field_ `private System.Windows.Forms.ColumnHeader TimeHeader`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueDetailsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueDetailsWindow`  
`partial class IssueDetailsWindow : ThemedForm`  
_internal*; L22-1431_
- inherits: `ThemedForm`
- L264 _private* field_ `IssueMonitor _issueMonitor`
- L265 _private* field_ `IssueData _issue`
- L266 _private* field_ `readonly List<IssueBuildData> _issueBuilds`
- L267 _private* field_ `readonly List<IssueDiagnosticData> _diagnostics`
- L268 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L269 _private* field_ `readonly TimeSpan? _serverTimeOffset`
- L270 _private* field_ `PerforceWorkerTask? _perforceWorker`
- L271 _private* field_ `readonly IServiceProvider _serviceProvider`
- L272 _private* field_ `readonly SynchronizationContext _mainThreadSynchronizationContext`
- L273 _private* field_ `string? _selectedStream`
- L274 _private* field_ `List<PerforceChangeRange> _selectedStreamRanges = new List<PerforceChangeRange>()`
- L275 _private* field_ `bool _isDisposing`
- L276 _private* field_ `Font? _boldFont`
- L277 _private* field_ `ChangesRecord? _contextMenuChange`
- L278 _private* field_ `string? _lastOwner`
- L279 _private* field_ `string? _lastDetailsText`
- L281 _private* field_ `System.Windows.Forms.Timer? _updateTimer`
- L283 _private* field_ `StatusElementResources _statusElementResources`
- L285-345 _private* ctor_ `IssueDetailsWindow(IssueMonitor issueMonitor, IssueData issue, List<IssueBuildData> issueBuilds, List<IssueDiagnosticData> diagnostics, IPerforceSettings perforceSettings, TimeSpan? serverTimeOffset, IServiceProvider serviceProvider, string? currentStream)`
- L347-369 _protected method_ `protected override void Dispose(bool disposing)`
- L371-382 _private method_ `private void StartUpdateTimer()`
- L384-393 _private method_ `private void StopUpdateTimer()`
- L395-399 _private method_ `private void UpdateTimer_Tick(object? sender, EventArgs e)`
- L401-407 _private* method_ `static void UpdateSummaryTextIfChanged(Label label, string newText)`
- L409-431 _private* method_ `static void AppendEscapedRtf(StringBuilder result, string text)`
- L433-443 _private* method_ `static void AppendHyperlink(StringBuilder richText, string label, string url)`
- L445-523 _private* method_ `static string CreateRichTextErrors(List<IssueBuildData> issueBuilds, List<IssueDiagnosticData> diagnostics)`
- L525-625 _private* method_ `void UpdateCurrentIssue()`
- L627-631 _private method_ `private void IssueDetailsWindow_Disposed(object? sender, EventArgs e)`
- L633-641 _private* method_ `void FetchBuildChanges(PerforceChangeRange range)`
- L643-654 _private* method_ `static bool FilterMatch(Regex filterRegex, ChangesRecord summary)`
- L656-671 _private* method_ `static bool FilterMatch(Regex filterRegex, DescribeRecord describeRecord)`
- L673-856 _private* method_ `void UpdateBuildList()`
- L858 _private* field_ `BuildGroup? _selectedBuildGroup`
- L860-882 _private* method_ `void ShowJobContextMenu(Point point, BuildGroup buildGroup)`
- L884-902 _private* method_ `static void UpdateChangeTypeWidget(StatusLineListViewWidget typeWidget, PerforceChangeDetails? details)`
- L904-949 _private* method_ `void CreateWorker()`
- L951-963 _private* method_ `void OnUpdateIssues()`
- L965-974 _private method_ `private void OnUpdateIssuesAsync()`
- L976-983 _private* method_ `void DestroyWorker()`
- L985-988 _private* method_ `void OnRequestComplete(PerforceChangeRange range)`
- L990-1013 _private* method_ `void UpdateChangeMetadata(ChangesRecord change)`
- L1015 _private* field_ `static readonly List<IssueDetailsWindow> s_existingWindows = new List<IssueDetailsWindow>()`
- L1036-1045 _public method_ `public static void Show(Form owner, IssueMonitor issueMonitor, IPerforceSettings perforceSettings, TimeSpan? serverTimeOffset, IssueData issue, IServiceProvider serviceProvider, string? currentStream)`
- L1047-1082 _public method_ `public static void Show(Form owner, IssueMonitor issueMonitor, IPerforceSettings perforceSettings, TimeSpan? serverTimeOffset, IssueData issue, List<IssueBuildData> issueBuilds, IServiceProvider serviceProvider, string? currentStream)`
- L1084-1088 _private method_ `private void CloseBtn_Click(object sender, EventArgs e)`
- L1090-1094 _private method_ `private void StreamComboBox_SelectedIndexChanged(object sender, EventArgs e)`
- L1096-1099 _private method_ `private void BuildListView_DrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)`
- L1101-1140 _private method_ `private void BuildListView_DrawItem(object sender, DrawListViewItemEventArgs e)`
- L1142-1254 _private method_ `private void BuildListView_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)`
- L1256-1263 _private method_ `private void BuildListView_FontChanged(object sender, EventArgs e)`
- L1265-1281 _private method_ `private void BuildListView_MouseClick(object sender, MouseEventArgs args)`
- L1283-1289 _private method_ `private void BuildListContextMenu_MoreInfo_Click(object sender, EventArgs e)`
- L1291-1297 _private method_ `private void BuildListContextMenu_Blame_Click(object sender, EventArgs e)`
- L1299-1318 _private method_ `private void AssignToUser(string user)`
- L1320-1323 _private method_ `private void AssignToMeBtn_Click(object sender, EventArgs e)`
- L1325-1332 _private method_ `private void AssignToOtherBtn_Click(object sender, EventArgs e)`
- L1334-1338 _private method_ `private void FilterTextBox_TextChanged(object sender, EventArgs e)`
- L1340-1343 _private method_ `private void FilterTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)`
- L1345-1365 _private method_ `private void MarkFixedBtn_Click(object sender, EventArgs e)`
- L1367-1374 _private method_ `private void DescriptionLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L1376-1389 _private method_ `private void JobContextMenu_ShowError_Click(object sender, EventArgs e)`
- L1391-1397 _private method_ `private void JobContextMenu_ViewJob_Click(object sender, EventArgs e)`
- L1399-1413 _private method_ `private void BuildListView_MouseUp(object sender, MouseEventArgs e)`
- L1415-1422 _private method_ `private void BuildLinkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L1424-1430 _private method_ `private void DetailsTextBox_LinkClicked(object sender, LinkClickedEventArgs e)`

#### class `UnrealGameSync.IssueDetailsWindow.BuildGroup`  
`class BuildGroup`  
_private*; L24-40_
- L26 _public property_ `public string JobName { get; }`
- L27 _public property_ `public string JobUrl { get; }`
- L28 _public property_ `public int Change { get; }`
- L29 _public property_ `public IssueBuildOutcome Outcome { get; }`
- L30 _public property_ `public IReadOnlyList<IssueBuildData> Builds { get; }`
- L32-39 _public ctor_ `public BuildGroup(string jobName, string jobUrl, int change, IssueBuildOutcome outcome, IReadOnlyList<IssueBuildData> builds)`

#### class `UnrealGameSync.IssueDetailsWindow.PerforceChangeRange`  
`class PerforceChangeRange`  
_private*; L42-57_
- L44 _public property_ `public bool Expanded { get; set; }`
- L45 _public property_ `public int MinChange { get; }`
- L46 _public property_ `public int MaxChange { get; }`
- L47 _public property_ `public List<ChangesRecord>? Changes { get; set; }`
- L48 _public property_ `public string? ErrorMessage { get; set; }`
- L49 _public property_ `public BuildGroup BuildGroup { get; }`
- L51-56 _public ctor_ `public PerforceChangeRange(int minChange, int maxChange, BuildGroup buildGroup)`

#### class `UnrealGameSync.IssueDetailsWindow.PerforceChangeDetailsWithDescribeRecord`  
`class PerforceChangeDetailsWithDescribeRecord : PerforceChangeDetails`  
_private*; L59-68_
- inherits: `PerforceChangeDetails`
- L61 _public field_ `public DescribeRecord DescribeRecord`
- L63-67 _public ctor_ `public PerforceChangeDetailsWithDescribeRecord(DescribeRecord describeRecord) : base(describeRecord)`

#### class `UnrealGameSync.IssueDetailsWindow.PerforceWorkerTask`  
`class PerforceWorkerTask : IDisposable`  
_private*; L70-210_
- inherits: `IDisposable`
- L72 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L73 _private* field_ `readonly string _filter`
- L74 _private* field_ `Action<PerforceChangeRange>? _onUpdateChanges`
- L75 _private* field_ `Action<ChangesRecord>? _onUpdateChangeMetadata`
- L76 _private* field_ `readonly ILogger _logger`
- L77 _private* field_ `readonly object _lockObject = new object()`
- L78 _private* field_ `readonly SynchronizationContext _synchronizationContext`
- L79 _private* field_ `Task? _workerTask`
- L81 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L83 _private* field_ `readonly AsyncEvent _refreshEvent`
- L84 _private* field_ `readonly List<PerforceChangeRange> _requests = new List<PerforceChangeRange>()`
- L85 _private* field_ `readonly Dictionary<int, PerforceChangeDetailsWithDescribeRecord> _changeNumberToDetails = ...`
- L85 _private* field_ `readonly Dictionary< _changeNumberToDetails = new Dictionary<int, PerforceChangeDetailsWithDescribeRecord>()`
- L87-99 _public ctor_ `public PerforceWorkerTask(IPerforceSettings perforceSettings, string filter, Action<PerforceChangeRange>? onUpdateChanges, Action<ChangesRecord>? onUpdateChangeMetadata, ILogger logger)`
- L101-108 _public method_ `public void AddRequest(PerforceChangeRange range)`
- L110-122 _public method_ `public void Dispose()`
- L124-201 _private* method_ `async Task RunAsync(CancellationToken cancellationToken)`
- L203-209 _public method_ `public bool TryGetChangeDetails(int changeNumber, [NotNullWhen(true)] out PerforceChangeDetailsWithDescribeRecord? details)`

#### class `UnrealGameSync.IssueDetailsWindow.BadgeInfo`  
`class BadgeInfo`  
_private*; L212-222_
- L214 _public field_ `public string _label`
- L215 _public field_ `public Color _color`
- L217-221 _public ctor_ `public BadgeInfo(string label, Color color)`

#### class `UnrealGameSync.IssueDetailsWindow.ExpandRangeStatusElement`  
`class ExpandRangeStatusElement : StatusElement`  
_private*; L224-262_
- inherits: `StatusElement`
- L226 _private* field_ `readonly string _text`
- L227 _private* field_ `readonly Action _linkAction`
- L229-234 _public ctor_ `public ExpandRangeStatusElement(string text, Action inLinkAction)`
- L236-239 _public method_ `public override void OnClick(Point location)`
- L241-244 _public method_ `public override Size Measure(Graphics graphics, StatusElementResources resources)`
- L246-261 _public method_ `public override void Draw(Graphics graphics, StatusElementResources resources)`

#### class `UnrealGameSync.IssueDetailsWindow.UpdateIssueDetailsTask`  
`class UpdateIssueDetailsTask`  
_private*; L1017-1034_
- L1019 _private* field_ `readonly string _apiUrl`
- L1020 _private* field_ `readonly long _issueId`
- L1021 _private* field_ `readonly List<IssueDiagnosticData> _diagnostics`
- L1023-1028 _public ctor_ `public UpdateIssueDetailsTask(string apiUrl, long issueId, List<IssueDiagnosticData> diagnostics)`
- L1030-1033 _public method_ `public async Task RunAsync(CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueFixedWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueFixedWindow`  
`partial class IssueFixedWindow`  
_internal*; L5-381_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-354 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L358 _private field_ `private System.Windows.Forms.Button OkBtn`
- L359 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L360 _private field_ `private TextBoxWithCueBanner ChangeNumberTextBox`
- L361 _private field_ `private System.Windows.Forms.ListView ChangesListView`
- L362 _private field_ `private System.Windows.Forms.ColumnHeader ChangeHeader`
- L363 _private field_ `private System.Windows.Forms.ColumnHeader StreamHeader`
- L364 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L365 _private field_ `private System.Windows.Forms.RadioButton SpecifyChangeRadioButton`
- L366 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L367 _private field_ `private System.Windows.Forms.RadioButton RecentChangeRadioButton`
- L368 _private field_ `private System.Windows.Forms.ColumnHeader DescriptionHeader`
- L369 _private field_ `private System.Windows.Forms.ColumnHeader Spacer`
- L370 _private field_ `private System.Windows.Forms.ContextMenuStrip ChangesListContextMenu`
- L371 _private field_ `private System.Windows.Forms.ToolStripMenuItem ChangesContextMenu_MoreInfo`
- L372 _private field_ `private System.Windows.Forms.Button UserBrowseBtn`
- L373 _private field_ `private System.Windows.Forms.TextBox UserNameTextBox`
- L374 _private field_ `private System.Windows.Forms.GroupBox groupBox3`
- L375 _private field_ `private System.Windows.Forms.Label label1`
- L376 _private field_ `private System.Windows.Forms.RadioButton SystemicFixRadioButton`
- L377 _private field_ `private System.Windows.Forms.Label label2`
- L378 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L379 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L380 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueFixedWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueFixedWindow`  
`partial class IssueFixedWindow : ThemedForm`  
_internal*; L20-377_
- inherits: `ThemedForm`
- L109 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L110 _private* field_ `int _changeNumber`
- L112 _private* field_ `readonly FindChangesWorker _worker`
- L114 _private* field_ `readonly IServiceProvider _serviceProvider`
- L116-144 _public ctor_ `public IssueFixedWindow(IPerforceSettings perforceSettings, int initialChangeNumber, IServiceProvider serviceProvider)`
- L146-164 _protected method_ `protected override void OnLoad(EventArgs e)`
- L166-181 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforce, IServiceProvider serviceProvider, ref int fixChangeNumber)`
- L183-190 _private method_ `private void UpdateSelectedChangeAndClose()`
- L192-195 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L197-237 _private method_ `private void PopulateChanges(string userName, List<DescribeRecord> changes)`
- L239-255 _private method_ `private void ChangesListView_MouseClick(object sender, MouseEventArgs args)`
- L257-260 _private method_ `private void ChangesListView_MouseDoubleClick(object sender, MouseEventArgs e)`
- L262-266 _private method_ `private void ChangesContextMenu_MoreInfo_Click(object sender, EventArgs e)`
- L268-272 _private method_ `private void ChangeNumberTextBox_Enter(object sender, EventArgs e)`
- L274-278 _private method_ `private void ChangesListView_Enter(object sender, EventArgs e)`
- L280-284 _private method_ `private void UserNameTextBox_Enter(object sender, EventArgs e)`
- L286-290 _private method_ `private void UserBrowseBtn_Enter(object sender, EventArgs e)`
- L292-295 _private method_ `private void ChangeNumberTextBox_TextChanged(object sender, EventArgs e)`
- L297-300 _private method_ `private void ChangesListView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)`
- L302-327 _private method_ `private bool TryGetSelectedChange(out int changeNumber)`
- L329-332 _private method_ `private void UpdateOkButton()`
- L334-342 _private method_ `private void SpecifyChangeRadioButton_CheckedChanged(object sender, EventArgs e)`
- L344-352 _private method_ `private void RecentChangeRadioButton_CheckedChanged(object sender, EventArgs e)`
- L354-362 _private method_ `private void SystemicFixRadioButton_CheckedChanged(object sender, EventArgs e)`
- L364-371 _private method_ `private void UserBrowseBtn_Click(object sender, EventArgs e)`
- L373-376 _private method_ `private void UserNameTextBox_TextChanged(object sender, EventArgs e)`

#### class `UnrealGameSync.IssueFixedWindow.FindChangesWorker`  
`class FindChangesWorker : Component`  
_private*; L22-107_
- inherits: `Component`
- L24 _public delegate_ `public delegate void OnCompleteDelegate(string userName, List<DescribeRecord> changes)`
- L26 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L27 _private* field_ `readonly SynchronizationContext _mainThreadSyncContext`
- L28 _private* field_ `readonly AsyncEvent _wakeEvent`
- L29 _private* field_ `string? _requestedUserName`
- L30 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L31 _private* field_ `Task _backgroundTask`
- L32 _private* field_ `OnCompleteDelegate? _onComplete`
- L33 _private* field_ `readonly ILogger _logger`
- L35-45 _public ctor_ `public FindChangesWorker(IPerforceSettings perforceSettings, OnCompleteDelegate? onComplete, ILogger logger)`
- L47-50 _public method_ `public void Stop()`
- L52-63 _private* method_ `async Task StopAsync()`
- L65-69 _public method_ `public void FetchChanges(string userName)`
- L71-78 _protected method_ `protected override void Dispose(bool disposing)`
- L80-106 _public method_ `public async Task DoWork(CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueSettingsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueSettingsWindow`  
`partial class IssueSettingsWindow`  
_internal*; L5-341_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-318 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L322 _private field_ `private System.Windows.Forms.Button OkBtn`
- L323 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L324 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L325 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L326 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L327 _private field_ `private System.Windows.Forms.CheckBox NotifyUnassignedCheckBox`
- L328 _private field_ `private System.Windows.Forms.TextBox NotifyUnassignedTextBox`
- L329 _private field_ `private System.Windows.Forms.Label label2`
- L330 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2`
- L331 _private field_ `private System.Windows.Forms.CheckBox NotifyUnresolvedCheckBox`
- L332 _private field_ `private System.Windows.Forms.TextBox NotifyUnresolvedTextBox`
- L333 _private field_ `private System.Windows.Forms.Label label3`
- L334 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel3`
- L335 _private field_ `private System.Windows.Forms.CheckBox NotifyUnacknowledgedCheckBox`
- L336 _private field_ `private System.Windows.Forms.TextBox NotifyUnacknowledgedTextBox`
- L337 _private field_ `private System.Windows.Forms.Label label1`
- L338 _private field_ `private System.Windows.Forms.CheckBox NotifyProjectsCheckBox`
- L339 _private field_ `private TextBoxWithCueBanner NotifyProjectsTextBox`
- L340 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/IssueSettingsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.IssueSettingsWindow`  
`partial class IssueSettingsWindow : ThemedForm`  
_internal*; L10-158_
- inherits: `ThemedForm`
- L12 _private* field_ `readonly UserSettings _settings`
- L13 _private* field_ `readonly ILogger _logger`
- L15-68 _public ctor_ `public IssueSettingsWindow(UserSettings settings, string currentProject, ILogger logger)`
- L70-76 _private method_ `private void UpdateEnabledTextBoxes()`
- L78-81 _private method_ `private void NotifyProjectsCheckBox_CheckedChanged(object sender, EventArgs e)`
- L83-86 _private method_ `private void NotifyUnassignedCheckBox_CheckedChanged(object sender, EventArgs e)`
- L88-91 _private method_ `private void NotifyUnacknowledgedCheckBox_CheckedChanged(object sender, EventArgs e)`
- L93-96 _private method_ `private void NotifyUnresolvedCheckBox_CheckedChanged(object sender, EventArgs e)`
- L98-151 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L153-157 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LauncherUpdateWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.LauncherUpdateWindow`  
`partial class LauncherUpdateWindow`  
_internal*; L3-97_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-90 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L94 _private field_ `private System.Windows.Forms.Label label1`
- L95 _private field_ `private System.Windows.Forms.Button UpdateNowBtn`
- L96 _private field_ `private System.Windows.Forms.Button LaterBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LauncherUpdateWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.LauncherUpdateWindow`  
`public partial class LauncherUpdateWindow : ThemedForm`  
_public; L5-12_
- inherits: `ThemedForm`
- L7-11 _public ctor_ `public LauncherUpdateWindow()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LeaveCommentWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.LeaveCommentWindow`  
`partial class LeaveCommentWindow`  
_internal*; L5-90_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-83 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L87 _private field_ `private System.Windows.Forms.Button OkBtn`
- L88 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L89 _public field_ `public System.Windows.Forms.TextBox CommentTextBox`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LeaveCommentWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.LeaveCommentWindow`  
`public partial class LeaveCommentWindow : ThemedForm`  
_public; L5-12_
- inherits: `ThemedForm`
- L7-11 _public ctor_ `public LeaveCommentWindow()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LogWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.LogWindow`  
`partial class LogWindow`  
_internal*; L3-83_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-77 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L81 _private field_ `private System.Windows.Forms.Button OkBtn`
- L82 _private field_ `private System.Windows.Forms.TextBox LogTextBox`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/LogWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.LogWindow`  
`public partial class LogWindow : ThemedForm`  
_public; L5-14_
- inherits: `ThemedForm`
- L7-13 _public ctor_ `public LogWindow(string text)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/MainWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.MainWindow`  
`partial class MainWindow`  
_internal*; L5-234_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-213 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L217 _private field_ `private TabControl TabControl`
- L218 _private field_ `private System.Windows.Forms.Panel TabPanel`
- L219 _private field_ `private StatusPanel DefaultControl`
- L220 _private field_ `private System.Windows.Forms.ContextMenuStrip TabMenu`
- L221 _private field_ `private System.Windows.Forms.ToolStripMenuItem labelsToolStripMenuItem`
- L222 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_TabNames_Stream`
- L223 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_TabNames_WorkspaceName`
- L224 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_TabNames_WorkspaceRoot`
- L225 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_TabNames_ProjectFile`
- L226 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_OpenProject`
- L227 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_RecentProjects`
- L228 _private field_ `private System.Windows.Forms.ToolStripSeparator TabMenu_Recent_Separator`
- L229 _private field_ `private System.Windows.Forms.ToolStripMenuItem TabMenu_RecentProjects_ClearList`
- L230 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator2`
- L231 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L232 _private field_ `private System.Windows.Forms.Timer UpdateAlertPositionsTimer`
- L233 _private field_ `private System.Windows.Forms.Timer CheckLauncherVersionTimer`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/MainWindow.cs` (UnrealGameSync)


#### interface `UnrealGameSync.IMainWindowTabPanel`  
`interface IMainWindowTabPanel : IDisposable`  
_internal*; L26-54_
- inherits: `IDisposable`
- L28 _public* method_ `void Activate()`
- L29 _public* method_ `void Deactivate()`
- L30 _public* method_ `void Hide()`
- L31 _public* method_ `void Show()`
- L32 _public* method_ `bool IsBusy()`
- L33 _public* method_ `bool CanClose()`
- L34 _public* method_ `bool CanSyncNow()`
- L35 _public* method_ `void SyncLatestChange()`
- L36 _public* method_ `bool CanLaunchEditor()`
- L37 _public* method_ `void LaunchEditor()`
- L38 _public* method_ `void UpdateSettings()`
- L40-43 _public* property_ `Color? TintColor { get; }`
- L45-48 _public* property_ `Tuple<TaskbarState, float> DesiredTaskbarState { get; }`
- L50-53 _public* property_ `UserSelectedProjectSettings SelectedProject { get; }`

#### class `UnrealGameSync.MainWindow`  
`partial class MainWindow : ThemedForm, IWorkspaceControlOwner`  
_internal*; L56-1879_
- inherits: `ThemedForm, IWorkspaceControlOwner`
- L79 _private* field_ `static readonly int s_minLauncherVersion = MakeLauncherVersion(1, 19)` — Minimum version of the launcher that should be installed. Users will be prompted to upgrade it if the installed version is older than this.
- L82 _private* method_ `static extern int SetWindowTheme(IntPtr hWnd, string pszSubAppName, string pszSubIdList)` — attrs: `[DllImport("uxtheme.dll", CharSet = CharSet.Unicode)]`
- L85 _public method_ `public static extern int SendMessage(IntPtr hWnd, int wMsg, int wParam, int lParam)` — attrs: `[DllImport("user32.dll")]`
- L87 _private const_ `private const int WmSetredraw = 11`
- L89 _private* field_ `readonly UpdateMonitor _updateMonitor`
- L90 _private* field_ `readonly SynchronizationContext _mainThreadSynchronizationContext`
- L91 _private* field_ `readonly List<IssueMonitor> _defaultIssueMonitors = new List<IssueMonitor>()`
- L92 _private* field_ `readonly List<WorkspaceIssueMonitor> _workspaceIssueMonitors = new List<WorkspaceIssueMonitor>()`
- L94 _private* field_ `readonly string? _apiUrl`
- L95 _private* field_ `readonly DirectoryReference _dataFolder`
- L96 _private* field_ `readonly IPerforceSettings _defaultPerforceSettings`
- L97 _private* field_ `readonly IServiceProvider _serviceProvider`
- L98 _private* field_ `readonly ILogger _logger`
- L99 _private* field_ `readonly UserSettings _settings`
- L100 _private* field_ `int _tabMenuTabIdx = -1`
- L101 _private* field_ `int _changingWorkspacesRefCount`
- L103 _private* field_ `bool _allowClose = false`
- L105 _private* field_ `System.Threading.Timer? _scheduleTimer`
- L106 _private* field_ `System.Threading.Timer? _scheduleSettledTimer`
- L108 _private* field_ `readonly string _originalExecutableFileName`
- L109 _private* field_ `readonly bool _preview`
- L111 _private* field_ `IMainWindowTabPanel? _currentTabPanel`
- L113 _private* field_ `AutomationServer _automationServer`
- L115 _private* field_ `readonly bool _allowCreatingHandle`
- L117 _private* field_ `Rectangle _primaryWorkArea`
- L118 _private* field_ `readonly List<IssueAlertWindow> _alertWindows = new List<IssueAlertWindow>()`
- L120 _public property_ `public ToolUpdateMonitor ToolUpdateMonitor { get; set; }`
- L122-213 _public ctor_ `public MainWindow(UpdateMonitor inUpdateMonitor, string? apiUrl, DirectoryReference dataFolder, string originalExecutableFileName, bool preview, List<(UserSelectedProjectSettings, ModalTask<OpenProjectInfo>)> startupTasks, IPerforceSettings defaultPerforceSettings, IServiceProvider serviceProvider, UserSettings settings, string? uri)`
- L215-269 _private* method_ `void PostAutomationRequest(AutomationRequest request)`
- L271-293 _private* method_ `AutomationRequestOutput StartExecCommand(AutomationRequest request)`
- L295-309 _private method_ `private static void StartExecCommandAfterStartup(WorkspaceControl workspace, bool cancel, int changelist, string command)`
- L311-318 _private method_ `private static void StartExecCommandAfterSync(WorkspaceControl workspace, WorkspaceUpdateResult result, string command)`
- L320-347 _private* method_ `AutomationRequestOutput? StartAutomatedSync(AutomationRequest request, bool forceSync)`
- L349-403 _private method_ `private bool OpenWorkspaceForAutomation(AutomatedSyncWindow.WorkspaceInfo workspaceInfo, string streamName, string projectPath, [NotNullWhen(true)] out WorkspaceControl? outWorkspace)`
- L405-415 _private method_ `private static void StartAutomatedSyncAfterStartup(WorkspaceControl workspace, bool cancel, AutomationRequest request)`
- L417-431 _private* method_ `static void CompleteAutomatedSync(WorkspaceUpdateResult result, FileReference selectedFileName, AutomationRequest request)`
- L433-461 _private* method_ `AutomationRequestOutput FindProject(AutomationRequest request)`
- L463-507 _private* method_ `AutomationRequestOutput OpenIssue(AutomationRequest request)`
- L509-544 _private* method_ `AutomationRequestOutput RunCustomTool(AutomationRequest request)`
- L546-551 _protected method_ `protected override void OnHandleCreated(EventArgs e)`
- L553-559 _private* method_ `void TabControl_OnButtonClick(int buttonIdx, Point location, MouseButtons buttons)`
- L561-606 _private* method_ `void TabControl_OnTabClicked(object? tabData, Point location, MouseButtons buttons)`
- L608-611 _private* method_ `void TabControl_OnTabReorder()`
- L613-623 _private* method_ `void TabControl_OnTabClosed(object data)`
- L625-629 _private* method_ `bool TabControl_OnTabClosing(object tabData)`
- L635-669 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L671-682 _public method_ `public bool ConfirmClose()`
- L684-721 _private method_ `private void MainWindow_FormClosing(object sender, FormClosingEventArgs eventArgs)`
- L723-738 _private method_ `private void SetupDefaultControl()`
- L740-826 _private method_ `private void CreateErrorPanel(int replaceTabIdx, UserSelectedProjectSettings project, string message)`
- L829 _private method_ `private static extern int ShowWindow(IntPtr hWnd, uint msg)` — attrs: `[DllImport("user32.dll")]`
- L831 _private const_ `private const uint SwRestore = 0x09`
- L833-847 _public method_ `public void ShowAndActivate()`
- L849-866 _public method_ `public bool CanPerformUpdate()`
- L868-871 _public method_ `public bool CanSyncNow()`
- L873-876 _public method_ `public bool CanLaunchEditor()`
- L878-881 _public method_ `public void SyncLatestChange()`
- L883-886 _public method_ `public void LaunchEditor()`
- L888-892 _public method_ `public void ForceClose()`
- L894-897 _private method_ `private void MainWindow_Activated(object sender, EventArgs e)`
- L899-902 _private method_ `private void MainWindow_Deactivate(object sender, EventArgs e)`
- L904-933 _public method_ `public void SetupScheduledSync()`
- L935-967 _private method_ `private void StartScheduleTimer()`
- L969-1017 _private method_ `private void CheckLauncherVersionTimer_Tick(object sender, EventArgs e)`
- L1019-1043 _private* method_ `static int GetLauncherVersion()`
- L1045 _private* method_ `static int MakeLauncherVersion(int major, int minor)`
- L1047-1056 _private method_ `private void StopScheduleTimer()`
- L1058-1079 _private method_ `private void ScheduleTimerElapsed()`
- L1081-1092 _private method_ `private void StartScheduleSettledTimer()`
- L1094-1103 _private method_ `private void StopScheduleSettledTimer()`
- L1105-1121 _private method_ `private void ScheduleSettledTimerElapsed()`
- L1123-1167 _private* method_ `void TabControl_OnTabChanged(object? newTabData)`
- L1169-1183 _public method_ `public void RequestProjectChange(WorkspaceControl workspace, UserSelectedProjectSettings project, bool modal)`
- L1185-1199 _public method_ `public void OpenNewProject()`
- L1201-1213 _private* method_ `void UpdateRecentProjectsList(UserSelectedProjectSettings detectedProjectSettings)`
- L1215-1226 _public method_ `public void EditSelectedProject(int tabIdx)`
- L1228-1235 _public method_ `public void EditSelectedProject(WorkspaceControl workspace)`
- L1237-1244 _public method_ `public void EditSelectedProject(ErrorPanel panel)`
- L1246-1259 _public method_ `public void EditSelectedProject(int tabIdx, UserSelectedProjectSettings selectedProject)`
- L1261-1284 _private* method_ `int TryOpenProject(UserSelectedProjectSettings project, int replaceTabIdx, OpenProjectOptions options = OpenProjectOptions.None)`
- L1286-1363 _private* method_ `int TryOpenProject(OpenProjectInfo openProjectInfo, int replaceTabIdx, OpenProjectOptions options)`
- L1365-1374 _public method_ `public void StreamChanged(WorkspaceControl workspace)`
- L1376-1397 _public method_ `public void StreamChangedCallback(WorkspaceControl workspace)`
- L1399-1408 _private* method_ `void SaveTabSettings()`
- L1410-1416 _private* method_ `void TabControl_OnNewTabClick(Point location, MouseButtons buttons)`
- L1418-1447 _private* method_ `string GetTabName(WorkspaceControl workspace)`
- L1449-1465 _public method_ `public void SetTabNames(TabLabels newTabNames)`
- L1467-1470 _private method_ `private void TabMenu_OpenProject_Click(object sender, EventArgs e)`
- L1472-1476 _private method_ `private void TabMenu_OpenRecentProject_Click(UserSelectedProjectSettings recentProject, int tabIdx)`
- L1478-1481 _private method_ `private void TabMenu_TabNames_Stream_Click(object sender, EventArgs e)`
- L1483-1486 _private method_ `private void TabMenu_TabNames_WorkspaceName_Click(object sender, EventArgs e)`
- L1488-1491 _private method_ `private void TabMenu_TabNames_WorkspaceRoot_Click(object sender, EventArgs e)`
- L1493-1496 _private method_ `private void TabMenu_TabNames_ProjectFile_Click(object sender, EventArgs e)`
- L1498-1502 _private method_ `private void TabMenu_RecentProjects_ClearList_Click(object sender, EventArgs e)`
- L1504-1507 _private method_ `private void TabMenu_Closed(object sender, ToolStripDropDownClosedEventArgs e)`
- L1509-1513 _private method_ `private void RecentMenu_ClearList_Click(object sender, EventArgs e)`
- L1515-1559 _public method_ `public void UpdateProgress()`
- L1561-1568 _public method_ `public void UpdateTintColors()`
- L1570-1591 _public method_ `public void ModifyApplicationSettings()`
- L1593-1617 _private method_ `private void MainWindow_Load(object sender, EventArgs e)`
- L1619-1622 _private* method_ `bool ShowNotificationForIssue(IssueData issue)`
- L1624-1627 _private* method_ `bool ShowNotificationsForProject(string project)`
- L1629-1713 _public method_ `public void UpdateAlertWindows()`
- L1715-1718 _private* method_ `void IssueMonitor_OnUpdateAsync()`
- L1720-1723 _private* method_ `void IssueMonitor_OnUpdate()`
- L1725-1739 _private* method_ `void ShowAlertWindow(IssueMonitor issueMonitor, IssueData issue, IssueAlertReason reason)`
- L1741-1757 _private* method_ `void AcceptIssue(IssueAlertWindow alert)`
- L1759-1768 _private* method_ `void DeclineIssue(IssueAlertWindow alert)`
- L1770-1781 _private* method_ `void ShowIssueDetails(IssueAlertWindow alert)`
- L1783-1799 _private* method_ `void CloseAlertWindow(IssueAlertWindow alert)`
- L1801-1804 _private method_ `private void SetAlertWindowPosition(int idx)`
- L1806-1820 _private method_ `private void SetAlertWindowPositions()`
- L1822-1825 _private method_ `private void UpdateAlertPositionsTimer_Tick(object sender, EventArgs e)`
- L1827-1852 _public method_ `public IssueMonitor CreateIssueMonitor(string? apiUrl, string userName)`
- L1854-1878 _public method_ `public void ReleaseIssueMonitor(IssueMonitor issueMonitor)`

#### class `UnrealGameSync.MainWindow.WorkspaceIssueMonitor`  
`class WorkspaceIssueMonitor`  
_private*; L58-67_
- L60 _public field_ `public IssueMonitor _issueMonitor`
- L61 _public field_ `public int _refCount`
- L63-66 _public ctor_ `public WorkspaceIssueMonitor(IssueMonitor issueMonitor)`

#### enum `UnrealGameSync.MainWindow.OpenProjectOptions`  
`enum OpenProjectOptions`  
_private*; L70-74_
- attrs: `[Flags]`
- L72 _public* enumerator_ `None`
- L73 _public* enumerator_ `Quiet`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ModalTaskWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ModalTaskWindow`  
`partial class ModalTaskWindow`  
_internal*; L5-68_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-63 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L67 _private field_ `private System.Windows.Forms.Label MessageLabel`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ModalTaskWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ModalTaskWindow`  
`partial class ModalTaskWindow : ThemedForm`  
_internal*; L10-47_
- inherits: `ThemedForm`
- L12 _private* field_ `readonly Task _task`
- L13 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L15-25 _public ctor_ `public ModalTaskWindow(string inTitle, string inMessage, FormStartPosition inStartPosition, Task inTask, CancellationTokenSource inCancellationSource)`
- L27-31 _public method_ `public void ShowAndActivate()`
- L33-37 _private method_ `private void ModalTaskWindow_Load(object sender, EventArgs e)`
- L39-46 _private method_ `private void ModalTaskWindow_FormClosing(object sender, FormClosingEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ModifyBuildStepsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ModifyBuildStepsWindow`  
`partial class ModifyBuildStepsWindow`  
_internal*; L5-201_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-187 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L191 _private field_ `private System.Windows.Forms.ListView BuildStepList`
- L192 _private field_ `private System.Windows.Forms.ColumnHeader DescriptionColumn`
- L193 _private field_ `private System.Windows.Forms.ColumnHeader NormalSyncColumn`
- L194 _private field_ `private System.Windows.Forms.ColumnHeader ScheduledSyncColumn`
- L195 _private field_ `private System.Windows.Forms.Button NewStepButton`
- L196 _private field_ `private System.Windows.Forms.Button EditStepButton`
- L197 _private field_ `private System.Windows.Forms.Button RemoveStepButton`
- L198 _private field_ `private System.Windows.Forms.Button CloseButton`
- L199 _private field_ `private System.Windows.Forms.Button MoveUp`
- L200 _private field_ `private System.Windows.Forms.Button MoveDown`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ModifyBuildStepsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ModifyBuildStepsWindow`  
`partial class ModifyBuildStepsWindow : ThemedForm`  
_internal*; L12-272_
- inherits: `ThemedForm`
- L14 _private* field_ `readonly List<string> _targetNames`
- L15 _private* field_ `readonly List<BuildStep> _steps`
- L16 _private* field_ `readonly HashSet<Guid> _projectSteps`
- L17 _private* field_ `readonly DirectoryReference _baseDirectory`
- L18 _private* field_ `ListViewItem.ListViewSubItem? _mouseDownSubItem = null`
- L19 _private* field_ `readonly IReadOnlyDictionary<string, string> _variables`
- L19 _private* field_ `readonly IReadOnlyDictionary< _variables`
- L21-38 _public ctor_ `public ModifyBuildStepsWindow(List<string> inTargetNames, List<BuildStep> inSteps, HashSet<Guid> inProjectSteps, DirectoryReference inBaseDirectory, IReadOnlyDictionary<string, string> inVariables)`
- L40-47 _private method_ `private void ModifyBuildStepsWindow_Load(object sender, EventArgs e)`
- L49-56 _private* method_ `void AddTask(BuildStep task)`
- L58-69 _private method_ `private void NewStepButton_Click(object sender, EventArgs e)`
- L71-83 _private method_ `private void EditStepButton_Click(object sender, EventArgs e)`
- L85-98 _private method_ `private void RemoveStepButton_Click(object sender, EventArgs e)`
- L100-111 _private method_ `private void CloseButton_Click(object sender, EventArgs e)`
- L113-123 _private method_ `private void UpdateEnabledButtons()`
- L125-128 _private method_ `private void BuildStepList_SelectedIndexChanged(object sender, EventArgs e)`
- L130-140 _private method_ `private void BuildStepList_DrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)`
- L142-180 _private method_ `private void BuildStepList_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)`
- L182-190 _private method_ `private void BuildStepList_MouseDown(object sender, MouseEventArgs e)`
- L192-217 _private method_ `private void BuildStepList_MouseUp(object sender, MouseEventArgs e)`
- L219-237 _private method_ `private void MoveUp_Click(object sender, EventArgs e)`
- L239-257 _private method_ `private void MoveDown_Click(object sender, EventArgs e)`
- L259-271 _private method_ `private void ModifyBuildStepsWindow_FormClosed(object sender, FormClosedEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/NewWorkspaceWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.NewWorkspaceWindow`  
`partial class NewWorkspaceWindow`  
_internal*; L3-207_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-192 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L196 _private field_ `private TextBoxWithCueBanner NameTextBox`
- L197 _private field_ `private System.Windows.Forms.TextBox StreamTextBox`
- L198 _private field_ `private TextBoxWithCueBanner RootDirTextBox`
- L199 _private field_ `private System.Windows.Forms.Label label1`
- L200 _private field_ `private System.Windows.Forms.Label label2`
- L201 _private field_ `private System.Windows.Forms.Label label3`
- L202 _private field_ `private System.Windows.Forms.Button RootDirBrowseBtn`
- L203 _private field_ `private System.Windows.Forms.Button OkBtn`
- L204 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L205 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L206 _private field_ `private System.Windows.Forms.Button StreamBrowseBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/NewWorkspaceWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.NewWorkspaceWindow`  
`partial class NewWorkspaceWindow : ThemedForm`  
_internal*; L20-387_
- inherits: `ThemedForm`
- L87 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L88 _private* field_ `readonly InfoRecord _info`
- L89 _private* field_ `readonly List<ClientsRecord> _clients`
- L90 _private* field_ `readonly IServiceProvider _serviceProvider`
- L91 _private* field_ `NewWorkspaceSettings? _settings`
- L92 _private* field_ `readonly DirectoryReference? _defaultRootPath`
- L93 _private* field_ `readonly UserSettings _userSettings`
- L95-162 _private ctor_ `private NewWorkspaceWindow(IPerforceSettings perforceSettings, string? forceStream, string? defaultStream, InfoRecord info, List<ClientsRecord> clients, IServiceProvider serviceProvider, UserSettings settings)`
- L164-184 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforceSettings, string? forceStreamName, string currentWorkspaceName, UserSettings settings, IServiceProvider serviceProvider, [NotNullWhen(true)] out string? workspaceName)`
- L186-196 _private method_ `private void RootDirBrowseBtn_Click(object sender, EventArgs e)`
- L198-208 _private method_ `private string GetDefaultWorkspaceName()`
- L210-222 _private method_ `private string GetDefaultWorkspaceRootDir()`
- L224-235 _private method_ `private static string Sanitize(string text)`
- L237-240 _private method_ `private void UpdateNameCueBanner()`
- L242-245 _private method_ `private void UpdateRootDirCueBanner()`
- L247-250 _private method_ `private void UpdateOkButton()`
- L252-296 _private method_ `private bool TryGetWorkspaceSettings([NotNullWhen(true)] out NewWorkspaceSettings? settings)`
- L298-301 _private method_ `private void NameTextBox_TextChanged(object sender, EventArgs e)`
- L303-308 _private method_ `private void StreamTextBox_TextChanged(object sender, EventArgs e)`
- L310-313 _private method_ `private void RootDirTextBox_TextChanged(object sender, EventArgs e)`
- L315-339 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L341-345 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L347-354 _private method_ `private void StreamBrowseBtn_Click(object sender, EventArgs e)`
- L356-362 _private method_ `private void RootDirTextBox_Enter(object sender, EventArgs e)`
- L364-370 _private method_ `private void RootDirTextBox_Leave(object sender, EventArgs e)`
- L372-378 _private method_ `private void NameTextBox_Enter(object sender, EventArgs e)`
- L380-386 _private method_ `private void NameTextBox_Leave(object sender, EventArgs e)`

#### class `UnrealGameSync.NewWorkspaceWindow.NewWorkspaceSettings`  
`class NewWorkspaceSettings`  
_private*; L22-34_
- L24 _public property_ `public string Name { get; }`
- L25 _public property_ `public string Stream { get; }`
- L26 _public property_ `public DirectoryReference RootDir { get; }`
- L28-33 _public ctor_ `public NewWorkspaceSettings(string name, string stream, DirectoryReference rootDir)`

#### class `UnrealGameSync.NewWorkspaceWindow.FindWorkspaceSettingsTask`  
`class FindWorkspaceSettingsTask`  
_private*; L36-62_
- L38 _public property_ `public InfoRecord Info { get; }`
- L39 _public property_ `public List<ClientsRecord> Clients { get; }`
- L40 _public property_ `public string? CurrentStream { get; }`
- L42-47 _public ctor_ `public FindWorkspaceSettingsTask(InfoRecord info, List<ClientsRecord> clients, string? currentStream)`
- L49-61 _public method_ `public static async Task<FindWorkspaceSettingsTask> RunAsync(IPerforceConnection perforce, string currentWorkspaceName, CancellationToken cancellationToken)`

#### class `UnrealGameSync.NewWorkspaceWindow.NewWorkspaceTask`  
`static class NewWorkspaceTask`  
_private*; L64-85_
- L66-84 _public method_ `public static async Task RunAsync(IPerforceConnection perforce, NewWorkspaceSettings settings, string owner, string hostName, ClientSubmitOptions clientSubmitOptions, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/NotificationWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.NotificationWindow`  
`partial class NotificationWindow`  
_internal*; L5-42_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-37 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/NotificationWindow.cs` (UnrealGameSync)


#### enum `UnrealGameSync.NotificationType`  
`public enum NotificationType`  
_public; L11-16_
- L13 _public* enumerator_ `Info`
- L14 _public* enumerator_ `Warning`
- L15 _public* enumerator_ `Error`

#### class `UnrealGameSync.NotificationWindow`  
`public partial class NotificationWindow : ThemedForm`  
_public; L18-278_
- inherits: `ThemedForm`
- L20 _private* field_ `NotificationType _type`
- L23 _private* field_ `Rectangle _logoBounds`
- L24 _private* field_ `readonly InvertibleImage _logoImage`
- L27 _private* field_ `Rectangle _captionBounds`
- L28 _private* field_ `string _captionText = "Caption Text"`
- L29 _private* field_ `Font? _captionFont`
- L32 _private* field_ `Rectangle _messageBounds`
- L33 _private* field_ `string _messageText = "Mesage Text"`
- L36 _private* field_ `Rectangle _closeButtonBounds`
- L37 _private* field_ `bool _hoverOverClose`
- L38 _private* field_ `bool _mouseDownOverClose`
- L42 _public property_ `public Action? OnMoreInformation { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L44 _public property_ `public Action? OnDismiss { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L46-51 _public ctor_ `public NotificationWindow(Image inLogo)`
- L53-68 _public method_ `public void Show(NotificationType inType, string inCaption, string inMessage)`
- L70-87 _protected method_ `protected override void Dispose(bool disposing)`
- L89-124 _public method_ `public void CalculateBounds()`
- L126-135 _protected method_ `protected override void OnFontChanged(EventArgs e)`
- L137-140 _protected method_ `protected override void OnFormClosed(FormClosedEventArgs e)`
- L142-148 _protected method_ `protected override void OnResize(EventArgs e)`
- L150-160 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)`
- L162-171 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)`
- L173-198 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)`
- L200-235 _protected method_ `protected override void OnPaintBackground(PaintEventArgs e)`
- L237-277 _protected method_ `protected override void OnPaint(PaintEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/OpenProjectWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.OpenProjectWindow`  
`partial class OpenProjectWindow`  
_internal*; L3-370_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-344 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L347 _private field_ `private System.Windows.Forms.Label WorkspaceNameLabel`
- L348 _private field_ `private System.Windows.Forms.Label WorkspacePathLabel`
- L349 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L350 _private field_ `private System.Windows.Forms.Button WorkspacePathBrowseBtn`
- L351 _private field_ `private System.Windows.Forms.TextBox WorkspacePathTextBox`
- L352 _private field_ `private System.Windows.Forms.TextBox WorkspaceNameTextBox`
- L353 _private field_ `private System.Windows.Forms.Label ServerLabel`
- L354 _private field_ `private System.Windows.Forms.LinkLabel ChangeLink`
- L355 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L356 _private field_ `private System.Windows.Forms.Button OkBtn`
- L357 _private field_ `private System.Windows.Forms.RadioButton WorkspaceRadioBtn`
- L358 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L359 _private field_ `private System.Windows.Forms.RadioButton LocalFileRadioBtn`
- L360 _private field_ `private System.Windows.Forms.Button LocalFileBrowseBtn`
- L361 _private field_ `private System.Windows.Forms.TextBox LocalFileTextBox`
- L362 _private field_ `private System.Windows.Forms.Label LocalFileLabel`
- L363 _private field_ `private System.Windows.Forms.Button WorkspaceNameBrowseBtn`
- L364 _private field_ `private System.Windows.Forms.Button WorkspaceNameNewBtn`
- L365 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L366 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L367 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L368 _private field_ `private System.Windows.Forms.CheckBox GenerateP4ConfigCheckbox`
- L369 _private field_ `private System.Windows.Forms.ToolTip GenerateP4ConfigToolTip`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/OpenProjectWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.OpenProjectWindow`  
`partial class OpenProjectWindow : ThemedForm`  
_internal*; L19-444_
- inherits: `ThemedForm`
- L21 _private* field_ `string? _serverAndPortOverride`
- L22 _private* field_ `string? _userNameOverride`
- L23 _private* field_ `OpenProjectInfo? _openProjectInfo`
- L24 _private* field_ `readonly IPerforceSettings _defaultSettings`
- L25 _private* field_ `readonly IServiceProvider _serviceProvider`
- L26 _private* field_ `readonly UserSettings _settings`
- L27 _private* field_ `readonly ILogger _logger`
- L29 _private* delegate_ `delegate bool DetectProjectSettingsEvent(OpenProjectInfo openProjectInfo, ILogger logger, [NotNullWhen(false)] out string? error)`
- L33 _private* field_ `static readonly DetectProjectSettingsEvent? s_onDetectProjectSettings`
- L36-93 _private ctor_ `private OpenProjectWindow(UserSelectedProjectSettings? project, UserSettings settings, IPerforceSettings defaultSettings, IServiceProvider serviceProvider, ILogger logger)`
- L95 _private property_ `private IPerforceSettings Perforce => ...`
- L97-108 _public method_ `public static OpenProjectInfo? ShowModal(IWin32Window owner, UserSelectedProjectSettings? project, UserSettings settings, IPerforceSettings defaultPerforceSettings, IServiceProvider serviceProvider, ILogger logger)`
- L110-130 _private method_ `private void UpdateEnabledControls()`
- L132-160 _public method_ `public static string GetServerLabelText(IPerforceSettings defaultSettings, string? serverAndPort, string? userName)`
- L162-168 _protected method_ `protected override void OnHandleCreated(EventArgs e)`
- L170-173 _private method_ `private void UpdateServerLabel()`
- L175-178 _private method_ `private void UpdateWorkspacePathBrowseButton()`
- L180-183 _private method_ `private void UpdateOkButton()`
- L185-195 _private method_ `private void WorkspaceNewBtn_Click(object sender, EventArgs e)`
- L197-206 _private method_ `private void WorkspaceBrowseBtn_Click(object sender, EventArgs e)`
- L208-222 _private method_ `private void WorkspacePathBrowseBtn_Click(object sender, EventArgs e)`
- L224-235 _private method_ `private bool TryGetWorkspaceName([NotNullWhen(true)] out string? workspaceName)`
- L237-255 _private method_ `private bool TryGetClientPath([NotNullWhen(true)] out string? clientPath)`
- L257-268 _private method_ `private bool TryGetLocalPath(out string? localPath)`
- L270-293 _private method_ `private bool TryGetSelectedProject([NotNullWhen(true)] out UserSelectedProjectSettings? project)`
- L295-317 _private method_ `private void GenerateP4ConfigCheckbox_Click(object sender, EventArgs e)`
- L319-336 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L338-350 _public method_ `public static async Task<OpenProjectInfo> DetectSettingsAsync(IPerforceConnection perforce, UserSelectedProjectSettings selectedProject, UserSettings userSettings, bool GenerateP4Config, ILogger<OpenProjectInfo> logger, CancellationToken cancellationToken)`
- L352-358 _private method_ `private void ChangeLink_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L360-397 _private method_ `private void LocalFileBrowseBtn_Click(object sender, EventArgs e)`
- L399-403 _private method_ `private void WorkspaceNameTextBox_TextChanged(object sender, EventArgs e)`
- L405-408 _private method_ `private void WorkspacePathTextBox_TextChanged(object sender, EventArgs e)`
- L410-413 _private method_ `private void LocalFileTextBox_TextChanged(object sender, EventArgs e)`
- L415-418 _private method_ `private void WorkspaceRadioBtn_CheckedChanged(object sender, EventArgs e)`
- L420-423 _private method_ `private void LocalFileRadioBtn_CheckedChanged(object sender, EventArgs e)`
- L425-428 _private method_ `private void LocalFileTextBox_Enter(object sender, EventArgs e)`
- L430-433 _private method_ `private void WorkspaceNameTextBox_Enter(object sender, EventArgs e)`
- L435-438 _private method_ `private void WorkspacePathTextBox_Enter(object sender, EventArgs e)`
- L440-443 _private method_ `private static bool IsP4ConfigSet()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PasswordWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.PasswordWindow`  
`partial class PasswordWindow`  
_internal*; L3-111_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-103 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L107 _private field_ `private System.Windows.Forms.Label PromptLabel`
- L108 _private field_ `private System.Windows.Forms.TextBox PasswordTextBox`
- L109 _private field_ `private System.Windows.Forms.Button OkBtn`
- L110 _private field_ `private System.Windows.Forms.Button CancelBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PasswordWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.PasswordWindow`  
`public partial class PasswordWindow : ThemedForm`  
_public; L7-31_
- inherits: `ThemedForm`
- L9 _public property_ `public string Password { get; set; }`
- L11-20 _public ctor_ `public PasswordWindow(string prompt, string password)`
- L22-25 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L27-30 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PerforceSyncSettingsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.PerforceSyncSettingsWindow`  
`partial class PerforceSyncSettingsWindow`  
_internal*; L3-281_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-262 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L265 _private field_ `private System.Windows.Forms.Button OkButton`
- L266 _private field_ `private System.Windows.Forms.Button CancButton`
- L267 _private field_ `private System.Windows.Forms.Button ResetButton`
- L268 _private field_ `private System.Windows.Forms.Label labelMaxCommandsPerBatch`
- L269 _private field_ `private System.Windows.Forms.Label labelMaxSizePerBatch`
- L270 _private field_ `private System.Windows.Forms.NumericUpDown numericUpDownMaxSizePerBatch`
- L271 _private field_ `private System.Windows.Forms.NumericUpDown numericUpDownMaxCommandsPerBatch`
- L272 _private field_ `private System.Windows.Forms.GroupBox groupBoxSyncing`
- L273 _private field_ `private System.Windows.Forms.NumericUpDown numericUpDownRetriesOnSyncError`
- L274 _private field_ `private System.Windows.Forms.Label labelRetriesOnSyncError`
- L275 _private field_ `private System.Windows.Forms.NumericUpDown numericUpDownSyncErrorRetryDelay`
- L276 _private field_ `private System.Windows.Forms.Label labelSyncErrorRetryDelay`
- L277 _private field_ `private System.Windows.Forms.CheckBox FastSyncCheckBox`
- L278 _private field_ `private System.Windows.Forms.Label label1`
- L279 _private field_ `private System.Windows.Forms.CheckBox UseNativeLibraryCheckBox`
- L280 _private field_ `private System.Windows.Forms.Label labelUseNativeLibrary`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PerforceSyncSettingsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.PerforceSyncSettingsWindow`  
`partial class PerforceSyncSettingsWindow : ThemedForm`  
_internal*; L8-68_
- inherits: `ThemedForm`
- L10 _private* field_ `readonly UserSettings _settings`
- L11 _private* field_ `readonly ILogger _logger`
- L13-20 _public ctor_ `public PerforceSyncSettingsWindow(UserSettings settings, ILogger logger)`
- L22-32 _private method_ `private void PerforceSettingsWindow_Load(object sender, EventArgs e)`
- L34-46 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L48-51 _private method_ `private static int? GetValueIfNotDefault(int value, int defaultValue)`
- L53-57 _private method_ `private void CancButton_Click(object sender, EventArgs e)`
- L59-67 _private method_ `private void ResetButton_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PresetsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.PresetsWindow`  
`partial class PresetsWindow`  
_internal*; L7-380_
- L12 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-25 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L33-354 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L358 _private field_ `private System.Windows.Forms.ComboBox RoleSelector`
- L359 _private field_ `private System.Windows.Forms.DataGridView SyncFilters`
- L360 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Category`
- L361 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Include`
- L362 _private field_ `private System.Windows.Forms.DataGridViewTextBoxColumn Paths`
- L363 _private field_ `private System.Windows.Forms.ListView Views`
- L364 _private field_ `private System.Windows.Forms.Label label3`
- L365 _private field_ `private System.Windows.Forms.Label label4`
- L366 _private field_ `private System.Windows.Forms.Label CurrentPreset`
- L367 _private field_ `private System.Windows.Forms.Button SelectPreset`
- L368 _private field_ `private System.Windows.Forms.Button CancButton`
- L369 _private field_ `private System.Windows.Forms.Button OkButton`
- L370 _private field_ `private System.Windows.Forms.Button CopyToGlobal`
- L371 _private field_ `private System.Windows.Forms.Button CopyToWorkspace`
- L372 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L373 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L374 _private field_ `private System.Windows.Forms.ToolTip PresetComboBoxToolTip`
- L375 _private field_ `private System.Windows.Forms.TableLayoutPanel HeaderTableLayout`
- L376 _private field_ `private System.Windows.Forms.FlowLayoutPanel TopLevelFlowLayout`
- L377 _private field_ `private System.Windows.Forms.FlowLayoutPanel FooterFlowLayout`
- L378 _private field_ `private System.Windows.Forms.ToolTip CopyToToolTip`
- L379 _private field_ `private System.Windows.Forms.FlowLayoutPanel DialogControlsFlowLayout`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/PresetsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.PresetsWindow`  
`public partial class PresetsWindow : ThemedForm`  
_public; L10-266_
- inherits: `ThemedForm`
- L12 _private const_ `private const string ForcedDefaultPresetToolTip = "Presets are disabled as a locked default preset is used."`
- L13 _private field_ `private readonly IDictionary<Guid, WorkspaceSyncCategory> _uniqueIdToCategory`
- L13 _private field_ `private readonly IDictionary< _uniqueIdToCategory`
- L14 _private field_ `private readonly IDictionary<string, Preset> _roles`
- L14 _private field_ `private readonly IDictionary< _roles`
- L16 _private field_ `private readonly Action<Preset>? _copyToGlobal`
- L17 _private field_ `private readonly Action<Preset>? _copyToWorkspace`
- L19 _private property_ `private Timer _presetComboboxTooltipTimer { get; }`
- L20 _private property_ `private Timer _copyToTooltipTimer { get; }`
- L40 _public property_ `public string PresetName { get; set; }` — attrs: `[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]`
- L42-141 _public ctor_ `public PresetsWindow( IDictionary<Guid, WorkspaceSyncCategory> uniqueIdToCategory, string presetName, string defaultPreset, bool forceDefaultPreset, IDictionary<string, Preset> roles, Action<Preset>? copyToGlobal = null, Action<Preset>? copyToWorkspace = null )`
- L143-156 _private method_ `private void RoleSelector_SelectedIndexChanged(object? sender, System.EventArgs e)`
- L158-189 _private method_ `private void PopulateGrid(string name)`
- L191-210 _private method_ `private void PopulateViews(string name)`
- L212-217 _private method_ `private void SelectRole_Click(object sender, EventArgs e)`
- L219-226 _private method_ `private void SetCurrentPreset(string? newPreset)`
- L228-231 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L233-236 _private method_ `private void CancButton_Click(object sender, EventArgs e)`
- L238-241 _private method_ `private void CopyToGlobal_Click(object sender, EventArgs e)`
- L243-246 _private method_ `private void CopyToWorkspace_Click(object sender, EventArgs e)`
- L248-265 _private method_ `private void CopyTo(Action<Preset>? action)`

#### class `UnrealGameSync.Forms.PresetsWindow.PresetItem`  
`private class PresetItem`  
_private; L22-37_
- L24 _public property_ `public string Name { get; set; }`
- L26 _public property_ `public string Suffix { get; set; }`
- L28-36 _public method_ `public override string ToString()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ProgramsRunningWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ProgramsRunningWindow`  
`partial class ProgramsRunningWindow`  
_internal*; L3-136_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-126 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L130 _private field_ `private System.Windows.Forms.Button IgnoreBtn`
- L131 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L132 _private field_ `private System.Windows.Forms.ListBox ProgramListBox`
- L133 _private field_ `private System.Windows.Forms.Label label1`
- L134 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L135 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ProgramsRunningWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ProgramsRunningWindow`  
`public partial class ProgramsRunningWindow : ThemedForm`  
_public; L12-95_
- inherits: `ThemedForm`
- L14 _private* field_ `readonly object _syncObject = new object()`
- L15 _private* field_ `FileReference[] _programs`
- L16 _private* field_ `readonly Func<FileReference[]> _enumeratePrograms`
- L17 _private* field_ `ManualResetEvent? _terminateEvent`
- L18 _private* field_ `Thread? _backgroundThread`
- L20-28 _public ctor_ `public ProgramsRunningWindow(Func<FileReference[]> enumeratePrograms, FileReference[] programs)`
- L30-38 _protected method_ `protected override void Dispose(bool disposing)`
- L40-47 _private method_ `private void ProgramsRunningWindow_Load(object sender, EventArgs e)`
- L49-68 _private method_ `private void ExecuteBackgroundWork()`
- L70-80 _private method_ `private void UpdatePrograms()`
- L82-94 _private method_ `private void ProgramsRunningWindow_FormClosed(object sender, FormClosedEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ScheduleWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.ScheduleWindow`  
`partial class ScheduleWindow`  
_internal*; L5-191_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-178 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L182 _private field_ `private System.Windows.Forms.DateTimePicker TimePicker`
- L183 _private field_ `private System.Windows.Forms.CheckBox EnableCheckBox`
- L184 _private field_ `private System.Windows.Forms.Button OkBtn`
- L185 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L186 _private field_ `private System.Windows.Forms.CheckedListBox ProjectListBox`
- L187 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L188 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L189 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2`
- L190 _private field_ `private System.Windows.Forms.ContextMenuStrip SyncTypeDropDown`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ScheduleWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.ScheduleWindow`  
`partial class ScheduleWindow : ThemedForm`  
_internal*; L12-148_
- inherits: `ThemedForm`
- L14 _private* field_ `readonly Dictionary<UserSelectedProjectSettings, List<LatestChangeType>> _projectToLatestChangeTypes`
- L14 _private* field_ `readonly Dictionary< _projectToLatestChangeTypes`
- L16-52 _public ctor_ `public ScheduleWindow( bool inEnabled, TimeSpan inTime, bool anyOpenProject, IEnumerable<UserSelectedProjectSettings> scheduledProjects, IEnumerable<UserSelectedProjectSettings> openProjects, Dictionary<UserSelectedProjectSettings, List<LatestChangeType>> inProjectToLatestChangeTypes)`
- L54-72 _private method_ `private void UpdateSyncTypeDropDownWithProject(UserSelectedProjectSettings? selectedProject)`
- L74-86 _private method_ `private void ProjectListBox_ItemCheck(object? sender, ItemCheckEventArgs e)`
- L88-94 _private method_ `private void SyncTypeDropDown_Closed(object? sender, ToolStripDropDownClosedEventArgs e)`
- L96-104 _private method_ `private void SyncTypeDropDown_Click(string syncTypeId)`
- L106-115 _private method_ `private static void AddProjects(IEnumerable<UserSelectedProjectSettings> projects, Dictionary<string, UserSelectedProjectSettings> localFileToProject)`
- L117-136 _public method_ `public void CopySettings(UserSettings settings)`
- L138-141 _private method_ `private void EnableCheckBox_CheckedChanged(object sender, EventArgs e)`
- L143-147 _private method_ `private void UpdateEnabledControls()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SdkInfoWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SdkInfoWindow`  
`partial class SdkInfoWindow`  
_internal*; L3-121_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-114 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L117 _private field_ `private System.Windows.Forms.Button OkBtn`
- L118 _private field_ `private CustomListViewControl SdkListView`
- L119 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader2`
- L120 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader3`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SdkInfoWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.SdkInfoWindow`  
`public partial class SdkInfoWindow : ThemedForm`  
_public; L17-363_
- inherits: `ThemedForm`
- L89 _private* field_ `readonly Font _badgeFont`
- L90 _private* field_ `string? _hoverBadgeUniqueId`
- L92-226 _public ctor_ `public SdkInfoWindow(string[] sdkInfoEntries, Dictionary<string, string> variables, Font badgeFont)`
- L228-232 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L234-237 _private method_ `private void SdkListView_DrawItem(object sender, DrawListViewItemEventArgs e)`
- L239-263 _private method_ `private void SdkListView_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)`
- L265-287 _private method_ `private void SdkListView_MouseMove(object sender, MouseEventArgs e)`
- L289-292 _private method_ `private void SdkListView_MouseLeave(object sender, EventArgs e)`
- L294-308 _private method_ `private void SdkListView_MouseDown(object sender, MouseEventArgs e)`
- L310-334 _private method_ `private List<BadgeInfo> GetBadges(ListViewItem item, ListViewItem.ListViewSubItem subItem)`
- L336-342 _private method_ `private Size GetBadgeSize(string badgeText)`
- L344-362 _private method_ `private void DrawBadge(Graphics graphics, string badgeText, Rectangle badgeRect, bool mergeLeft, bool mergeRight, Color badgeColor)`

#### class `UnrealGameSync.SdkInfoWindow.SdkAction`  
`abstract class SdkAction`  
_private*; L19-29_
- L21 _public property_ `public string Name { get; init; }`
- L23-26 _public ctor_ `public SdkAction(string name)`
- L28 _public method_ `public abstract void Execute()`

#### class `UnrealGameSync.SdkInfoWindow.SdkActionRun`  
`class SdkActionRun : SdkAction`  
_private*; L31-59_
- inherits: `SdkAction`
- L33 _public property_ `public string Program { get; set; }`
- L34 _public property_ `public string Args { get; set; }`
- L36-41 _public ctor_ `public SdkActionRun(string name, string program = "", string args = "") : base(name)`
- L43-58 _public method_ `public override void Execute()`

#### class `UnrealGameSync.SdkInfoWindow.SdkItem`  
`class SdkItem`  
_private*; L61-73_
- L63 _public property_ `public string Category { get; }`
- L64 _public property_ `public string Description { get; }`
- L66 _public field_ `public List<SdkAction> Actions = new List<SdkAction>()`
- L68-72 _public ctor_ `public SdkItem(string category, string description)`

#### class `UnrealGameSync.SdkInfoWindow.BadgeInfo`  
`class BadgeInfo`  
_private*; L75-87_
- L77 _public property_ `public string UniqueId { get; }`
- L78 _public property_ `public string Label { get; }`
- L79 _public property_ `public Rectangle Rectangle { get; set; }`
- L80 _public property_ `public Action? OnClick { get; set; }`
- L82-86 _public ctor_ `public BadgeInfo(string uniqueId, string label)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectProjectFromWorkspaceWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectProjectFromWorkspaceWindow`  
`partial class SelectProjectFromWorkspaceWindow`  
_internal*; L3-110_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-102 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L106 _private field_ `private System.Windows.Forms.TreeView ProjectTreeView`
- L107 _private field_ `private System.Windows.Forms.Button OkBtn`
- L108 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L109 _private field_ `private System.Windows.Forms.CheckBox ShowProjectDirsFiles`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectProjectFromWorkspaceWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectProjectFromWorkspaceWindow`  
`partial class SelectProjectFromWorkspaceWindow : ThemedForm`  
_internal*; L22-259_
- inherits: `ThemedForm`
- L82 _private method_ `private static extern int ExtractIconEx(string sFile, int iIndex, IntPtr piLargeVersion, out IntPtr piSmallVersion, int amountIcons)` — attrs: `[DllImport("Shell32.dll", EntryPoint = "ExtractIconExW", CharSet = CharSet.Unicode, ExactSpelling = true, CallingConvention = CallingConvention.StdCall)]`
- L84 _private* field_ `readonly List<string> _projectFiles`
- L85 _private* field_ `string _selectedProjectFile`
- L103-140 _public ctor_ `public SelectProjectFromWorkspaceWindow(string workspaceName, List<string> projectFiles, string selectedProjectFile)`
- L142-189 _private method_ `private void Populate()`
- L191-206 _private* method_ `static TreeNode FindOrAddChildNode(TreeNode parentNode, string text, int imageIndex)`
- L208-232 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforce, string workspaceName, string workspacePath, IServiceProvider serviceProvider, bool allowUEFNProjects, [NotNullWhen(true)] out string? newWorkspacePath)`
- L234-237 _private method_ `private void ProjectTreeView_AfterSelect(object sender, TreeViewEventArgs e)`
- L239-247 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L249-253 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L255-258 _private method_ `private void ShowProjectDirsFiles_CheckedChanged(object sender, EventArgs e)`

#### class `UnrealGameSync.SelectProjectFromWorkspaceWindow.EnumerateWorkspaceProjectsTask`  
`static class EnumerateWorkspaceProjectsTask`  
_private*; L24-79_
- L26 _private* field_ `static readonly string[] Patterns = { "....uproject", "....uprojectdirs" }`
- L32 _private* field_ `static readonly string[] UEFNPatterns = { "....uproject", "....uprojectdirs", "....uefnproject" }`
- L39-78 _public method_ `public static async Task<List<string>> RunAsync(IPerforceConnection perforce, string clientName, bool allowUEFNProjects, CancellationToken cancellationToken)`

#### class `UnrealGameSync.SelectProjectFromWorkspaceWindow.ProjectNode`  
`class ProjectNode`  
_private*; L87-101_
- L89 _public field_ `public string FullName`
- L90 _public field_ `public string Folder`
- L91 _public field_ `public string Name`
- L93-100 _public ctor_ `public ProjectNode(string fullName)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectStreamWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectStreamWindow`  
`partial class SelectStreamWindow`  
_internal*; L3-110_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-102 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L106 _private field_ `private TextBoxWithCueBanner FilterTextBox`
- L107 _private field_ `private System.Windows.Forms.TreeView StreamsTreeView`
- L108 _private field_ `private System.Windows.Forms.Button OkBtn`
- L109 _private field_ `private System.Windows.Forms.Button CancelBtn`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectStreamWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectStreamWindow`  
`partial class SelectStreamWindow : ThemedForm`  
_internal*; L20-400_
- inherits: `ThemedForm`
- L70 _private field_ `private string? _selectedStream`
- L71 _private field_ `private readonly List<StreamDepot> _depots = new List<StreamDepot>()`
- L73-135 _private ctor_ `private SelectStreamWindow(List<StreamsRecord> streams, string? streamName)`
- L137-150 _private method_ `private static void GetExpandedNodes(TreeNodeCollection nodes, List<TreeNode> expandedNodes)`
- L152-174 _private method_ `private void MoveSelection(int delta)`
- L176-189 _protected method_ `protected override bool ProcessCmdKey(ref Message msg, Keys keyData)`
- L191-194 _private method_ `private static bool IncludeNodeInFilter(StreamNode node, string[] filter)`
- L196-218 _private method_ `private static bool TryFilterTree(StreamNode node, string[] filter, [NotNullWhen(true)] out StreamNode? newNode)`
- L220-296 _private method_ `private void PopulateTree()`
- L298-321 _private method_ `private bool AddStreamNodeToTree(StreamNode stream, string[] filter, TreeNode parentTreeNode, bool expandAll)`
- L323-345 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforce, string? streamName, IServiceProvider serviceProvider, [NotNullWhen(true)] out string? newStreamName)`
- L347-350 _private method_ `private void FilterTextBox_TextChanged(object sender, EventArgs e)`
- L352-355 _private method_ `private void UpdateOkButton()`
- L357-368 _private method_ `private string? GetSelectedStream()`
- L370-373 _private method_ `private void UpdateSelectedStream()`
- L375-382 _private method_ `private void StreamsTreeView_AfterSelect(object sender, TreeViewEventArgs e)`
- L384-393 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L395-399 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`

#### class `UnrealGameSync.SelectStreamWindow.EnumerateStreamsTask`  
`static class EnumerateStreamsTask`  
_private*; L22-28_
- L24-27 _public method_ `public static async Task<List<StreamsRecord>> RunAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`

#### class `UnrealGameSync.SelectStreamWindow.StreamNode`  
`class StreamNode`  
_private*; L30-48_
- L32 _public field_ `public StreamsRecord Record`
- L33 _public field_ `public List<StreamNode> ChildNodes = new List<StreamNode>()`
- L35-38 _public ctor_ `public StreamNode(StreamsRecord record)`
- L40-47 _public method_ `public void Sort()`

#### class `UnrealGameSync.SelectStreamWindow.StreamDepot`  
`class StreamDepot`  
_private*; L50-68_
- L52 _public field_ `public string Name`
- L53 _public field_ `public List<StreamNode> RootNodes = new List<StreamNode>()`
- L55-58 _public ctor_ `public StreamDepot(string name)`
- L60-67 _public method_ `public void Sort()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectUserWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectUserWindow`  
`partial class SelectUserWindow`  
_internal*; L5-137_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-126 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L130 _private field_ `private TextBoxWithCueBanner FilterTextBox`
- L131 _private field_ `private System.Windows.Forms.Button OkBtn`
- L132 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L133 _private field_ `private System.Windows.Forms.ListView UserListView`
- L134 _private field_ `private System.Windows.Forms.ColumnHeader NameHeader`
- L135 _private field_ `private System.Windows.Forms.ColumnHeader FullNameHeader`
- L136 _private field_ `private System.Windows.Forms.ColumnHeader EmailHeader`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectUserWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectUserWindow`  
`partial class SelectUserWindow : ThemedForm`  
_internal*; L17-201_
- inherits: `ThemedForm`
- L27 _private field_ `private int _selectedUserIndex`
- L28 _private field_ `private readonly List<UsersRecord> _users`
- L30-40 _private ctor_ `private SelectUserWindow(List<UsersRecord> users, int selectedUserIndex)`
- L42-73 _private method_ `private void MoveSelection(int delta)`
- L75-88 _protected method_ `protected override bool ProcessCmdKey(ref Message msg, Keys keyData)`
- L90-102 _private method_ `private static bool IncludeInFilter(UsersRecord user, string[] filterWords)`
- L104-145 _private method_ `private void PopulateList()`
- L147-169 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforceSettings, IServiceProvider serviceProvider, [NotNullWhen(true)] out string? selectedUserName)`
- L171-174 _private method_ `private void FilterTextBox_TextChanged(object sender, EventArgs e)`
- L176-179 _private method_ `private void UpdateOkButton()`
- L181-189 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L191-195 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L197-200 _private method_ `private void UserListView_SelectedIndexChanged(object sender, EventArgs e)`

#### class `UnrealGameSync.SelectUserWindow.EnumerateUsersTask`  
`static class EnumerateUsersTask`  
_private*; L19-25_
- L21-24 _public method_ `public static async Task<List<UsersRecord>> RunAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectWorkspaceWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectWorkspaceWindow`  
`partial class SelectWorkspaceWindow`  
_internal*; L3-149_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-137 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L141 _private field_ `private System.Windows.Forms.ListView WorkspaceListView`
- L142 _private field_ `private System.Windows.Forms.Button OkBtn`
- L143 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L144 _private field_ `private System.Windows.Forms.ColumnHeader NameColumnHeader`
- L145 _private field_ `private System.Windows.Forms.ColumnHeader StreamColumnHeader`
- L146 _private field_ `private System.Windows.Forms.ColumnHeader RootDirColumnHeader`
- L147 _private field_ `private System.Windows.Forms.CheckBox OnlyForThisComputer`
- L148 _private field_ `private System.Windows.Forms.ColumnHeader HostColumnHeader`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SelectWorkspaceWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.SelectWorkspaceWindow`  
`partial class SelectWorkspaceWindow : ThemedForm`  
_internal*; L18-145_
- inherits: `ThemedForm`
- L39 _private* field_ `readonly InfoRecord _info`
- L40 _private* field_ `readonly List<ClientsRecord> _clients`
- L41 _private* field_ `string? _workspaceName`
- L43-54 _private ctor_ `private SelectWorkspaceWindow(InfoRecord info, List<ClientsRecord> clients, string? workspaceName)`
- L56-81 _private method_ `private void UpdateListView()`
- L83-86 _private method_ `private void UpdateOkButton()`
- L88-108 _public method_ `public static bool ShowModal(IWin32Window owner, IPerforceSettings perforce, string workspaceName, IServiceProvider serviceProvider, out string? newWorkspaceName)`
- L110-113 _private method_ `private void OnlyForThisComputer_CheckedChanged(object sender, EventArgs e)`
- L115-118 _private method_ `private void WorkspaceListView_SelectedIndexChanged(object sender, EventArgs e)`
- L120-128 _private method_ `private void OkBtn_Click(object sender, EventArgs e)`
- L130-134 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L136-144 _private method_ `private void WorkspaceListView_MouseDoubleClick(object sender, MouseEventArgs e)`

#### class `UnrealGameSync.SelectWorkspaceWindow.EnumerateWorkspaces`  
`class EnumerateWorkspaces`  
_private*; L20-37_
- L22 _public property_ `public InfoRecord Info { get; }`
- L23 _public property_ `public List<ClientsRecord> Clients { get; }`
- L25-29 _public ctor_ `public EnumerateWorkspaces(InfoRecord info, List<ClientsRecord> clients)`
- L31-36 _public method_ `public static async Task<EnumerateWorkspaces> RunAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SwitchStreamWarningWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.SwitchStreamWarningWindow`  
`partial class SwitchStreamWarningWindow`  
_internal*; L5-149_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-138 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L142 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L143 _private field_ `private System.Windows.Forms.Label Title`
- L144 _private field_ `private System.Windows.Forms.ListBox OpenedFiles`
- L145 _private field_ `private System.Windows.Forms.Label Question`
- L146 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2`
- L147 _private field_ `private System.Windows.Forms.Button CancButton`
- L148 _private field_ `private System.Windows.Forms.Button OkButton`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SwitchStreamWarningWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.SwitchStreamWarningWindow`  
`public partial class SwitchStreamWarningWindow : ThemedForm`  
_public; L9-30_
- inherits: `ThemedForm`
- L11-19 _public ctor_ `public SwitchStreamWarningWindow(List<string> openedFiles)`
- L21-24 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L26-29 _private method_ `private void CancButton_Click(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncBaseContentConfirmationWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.SyncBaseContentConfirmationWindow`  
`partial class SyncBaseContentConfirmationWindow`  
_internal*; L5-185_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-173 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L176 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1`
- L177 _private field_ `private System.Windows.Forms.Label label1`
- L178 _private field_ `private System.Windows.Forms.Label label2`
- L179 _private field_ `private System.Windows.Forms.Label label3`
- L180 _private field_ `private System.Windows.Forms.Button SyncBaseContentButton`
- L181 _private field_ `private System.Windows.Forms.Button DoNotSyncBaseContentButton`
- L182 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L183 _private field_ `private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2`
- L184 _private field_ `private System.Windows.Forms.Label BaseContentPaths`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncBaseContentConfirmationWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.Forms.SyncBaseContentConfirmationWindow`  
`public partial class SyncBaseContentConfirmationWindow : ThemedForm`  
_public; L8-26_
- inherits: `ThemedForm`
- L10-25 _public ctor_ `public SyncBaseContentConfirmationWindow(string baseContentPaths)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncFilter.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SyncFilter`  
`partial class SyncFilter`  
_internal*; L5-261_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-245 _private method_ `private void InitializeComponent(bool defaultToWorkspaceView=false)` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L249 _private field_ `private System.Windows.Forms.Button OkButton`
- L250 _private field_ `private System.Windows.Forms.Button CancButton`
- L251 _private field_ `private System.Windows.Forms.TextBox FilterTextGlobal`
- L252 _private field_ `private System.Windows.Forms.Label label1`
- L253 _private field_ `private System.Windows.Forms.TabControl TabControl`
- L254 _private field_ `private System.Windows.Forms.TabPage GlobalTab`
- L255 _private field_ `private System.Windows.Forms.Button ShowCombinedView`
- L256 _private field_ `private System.Windows.Forms.TabPage WorkspaceTab`
- L257 _private field_ `private Controls.SyncFilterControl GlobalControl`
- L258 _private field_ `private Controls.WorkspaceSyncFilterControl WorkspaceControl`
- L259 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L260 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncFilter.cs` (UnrealGameSync)


#### class `UnrealGameSync.SyncFilter`  
`partial class SyncFilter : ThemedForm`  
_internal*; L11-545_
- inherits: `ThemedForm`
- L64 _private field_ `private readonly UserWorkspaceSettings _userWorkspaceSettings`
- L65 _private field_ `private readonly UserProjectSettings _userProjectSettings`
- L66 _private field_ `private readonly Dictionary<Guid, WorkspaceSyncCategory> _uniqueIdToCategory`
- L66 _private field_ `private readonly Dictionary< _uniqueIdToCategory`
- L67 _private field_ `private readonly string _currentPreset`
- L68 _private field_ `private readonly string _defaultPreset`
- L69 _private field_ `private readonly bool _forceDefaultPreset`
- L70 _private field_ `private readonly IDictionary<string, Preset> _availablePresets`
- L70 _private field_ `private readonly IDictionary< _availablePresets`
- L71 _private field_ `private readonly ConfigSection? _perforceSection`
- L72 _private field_ `private readonly ISet<string> _baseContentPaths`
- L74 _public field_ `public FilterSettings GlobalFilter`
- L75 _public field_ `public FilterSettings WorkspaceFilter`
- L77-206 _public ctor_ `public SyncFilter( UserWorkspaceSettings userWorkspaceSettings, UserProjectSettings userProjectSettings, Dictionary<Guid, WorkspaceSyncCategory> uniqueIdToCategory, string roleName, string defaultPreset, bool forceDefaultPreset, IDictionary<string, Preset> roles, ISet<string> baseContentPaths, FilterSettings globalFilter, FilterSettings workspaceFilter, ConfigSection? perforceSection, bool defaultToWorkspaceView)`
- L208-246 _private method_ `private void SyncBaseContentCheckBox_CheckStateChanged(object? sender, EventArgs e)`
- L248-272 _private method_ `private void PresetComboBox_SelectedValueChanged(object? sender, EventArgs e)`
- L274-303 _private method_ `private void GlobalControl_CategoriesCheckList_ItemCheck(object? sender, ItemCheckEventArgs e)`
- L305-316 _private method_ `private void WorkspaceControl_CategoriesCheckList_ItemCheck(object? sender, ItemCheckEventArgs e)`
- L318-321 _private method_ `private void GlobalControl_SyncAllProjects_CheckStateChanged(object? sender, EventArgs e)`
- L323-326 _private method_ `private void GlobalControl_SyncLocalProjects_CheckStateChanged(object? sender, EventArgs e)`
- L328-331 _private method_ `private void GlobalControl_IncludeAllProjectsInSolution_CheckStateChanged(object? sender, EventArgs e)`
- L333-336 _private method_ `private void GlobalControl_GenerateUprojectSpecificSolution_CheckStateChanged(object? sender, EventArgs e)`
- L338-365 _private method_ `private void SetPresetData(ComboBox presetComboBox, string currentPreset, IEnumerable<string> availablePresets)`
- L367-412 _private method_ `private static void SetExcludedCategories( CheckedListBox listBox, Dictionary<Guid, WorkspaceSyncCategory> uniqueIdToFilter, Preset? role, Dictionary<Guid, bool> categoryIdToSetting)`
- L414-425 _private method_ `private void SetReadonlyFlag(CheckedListBox list, bool isReadOnly)`
- L427-450 _private method_ `private void GetSettings(out FilterSettings newGlobalFilter, out FilterSettings newWorkspaceFilter)`
- L452-481 _private method_ `private Dictionary<Guid, bool> GetCategorySettings(CheckedListBox listBox, IEnumerable<KeyValuePair<Guid, bool>> originalSettings, bool includeLockedItems = true)`
- L483-514 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L516-519 _private method_ `private void CancButton_Click(object sender, EventArgs e)`
- L521-544 _private method_ `private void ShowCombinedView_Click(object sender, EventArgs e)`

#### class `UnrealGameSync.SyncFilter.PresetItem`  
`private class PresetItem`  
_private; L13-28_
- L15 _public property_ `public string Name { get; set; }`
- L17 _public property_ `public string Suffix { get; set; }`
- L19-27 _public method_ `public override string ToString()`

#### class `UnrealGameSync.SyncFilter.CheckListItem`  
`private class CheckListItem`  
_private; L30-62_
- L32 _public property_ `public string Name => ...`
- L33 _public property_ `public Guid UniqueId { get; set; }`
- L34 _public property_ `public string CategoryName { get; set; }`
- L35 _public property_ `public bool Locked { get; set; }`
- L36 _public property_ `public string Preset { get; set; }`
- L37 _public property_ `public bool Enabled { get; set; }`
- L38 _public property_ `public bool IsReadOnly { get; set; }`
- L39 _public property_ `public List<string> Paths { get; set; }`
- L40 _public property_ `public string ToolTip { get; set; }`
- L42-45 _public method_ `public override string ToString()`
- L47-61 _private method_ `private string GetName()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncFilterSyntax.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.SyncFilterSyntax`  
`partial class SyncFilterSyntax`  
_internal*; L3-103_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-96 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L100 _private field_ `private System.Windows.Forms.Button button1`
- L101 _private field_ `private System.Windows.Forms.Panel panel1`
- L102 _private field_ `private System.Windows.Forms.TextBox textBox1`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/SyncFilterSyntax.cs` (UnrealGameSync)


#### class `UnrealGameSync.SyncFilterSyntax`  
`public partial class SyncFilterSyntax : ThemedForm`  
_public; L5-12_
- inherits: `ThemedForm`
- L7-11 _public ctor_ `public SyncFilterSyntax()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/ThemedForm.cs` (UnrealGameSync)


#### class `UnrealGameSync.ThemedForm`  
`public class ThemedForm : Form`  
_public; L8-19_
- inherits: `Form`
- L10-15 _protected method_ `protected override void OnHandleCreated(EventArgs e)`
- L17 _protected property_ `protected static ApplicationThemeManager? ThemeManager => ...`
- L18 _protected property_ `protected static ApplicationTheme Theme => ...`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/UpdateSettingsWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.UpdateSettingsWindow`  
`partial class UpdateSettingsWindow`  
_internal*; L5-420_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-392 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L396 _private field_ `private System.Windows.Forms.TextBox ServerTextBox`
- L397 _private field_ `private System.Windows.Forms.TextBox DepotPathTextBox`
- L398 _private field_ `private System.Windows.Forms.Label DepotPathLabel`
- L399 _private field_ `private System.Windows.Forms.Label PromptLabel`
- L400 _private field_ `private System.Windows.Forms.Button RetryBtn`
- L401 _private field_ `private System.Windows.Forms.Button CancelBtn`
- L402 _private field_ `private System.Windows.Forms.Button ViewLogBtn`
- L403 _private field_ `private System.Windows.Forms.TextBox UserNameTextBox`
- L404 _private field_ `private System.Windows.Forms.Label label3`
- L405 _private field_ `private System.Windows.Forms.CheckBox UsePreviewBuildCheckBox`
- L406 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1`
- L407 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2`
- L408 _private field_ `private System.Windows.Forms.RadioButton PerforceRadioBtn`
- L409 _private field_ `private System.Windows.Forms.RadioButton HordeRadioBtn`
- L410 _private field_ `private System.Windows.Forms.Label label1`
- L411 _private field_ `private System.Windows.Forms.GroupBox PerforceGroupBox`
- L412 _private field_ `private System.Windows.Forms.GroupBox HordeGroupBox`
- L413 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3`
- L414 _private field_ `private System.Windows.Forms.TextBox HordeServerTextBox`
- L415 _private field_ `private System.Windows.Forms.Label label5`
- L416 _private field_ `private System.Windows.Forms.RadioButton DisableRadioBtn`
- L417 _private field_ `private System.Windows.Forms.GroupBox DisableGroupBox`
- L418 _private field_ `private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4`
- L419 _private field_ `private System.Windows.Forms.Label DisableUpdateLabel`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/UpdateSettingsWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.UpdateSettingsWindow`  
`partial class UpdateSettingsWindow : ThemedForm`  
_internal*; L14-175_
- inherits: `ThemedForm`
- L17 _private method_ `private static extern IntPtr SendMessage(IntPtr hWnd, int msg, int wParam, [MarshalAs(UnmanagedType.LPWStr)] string lParam)` — attrs: `[DllImport("user32.dll")]`
- L19 _public delegate_ `public delegate Task SyncAndRunDelegate(IPerforceConnection? perforce, LauncherSettings settings, ILogger logWriter, CancellationToken cancellationToken)`
- L21 _private* const_ `const int EmSetcuebanner = 0x1501`
- L23 _private* field_ `readonly LauncherSettings _settings`
- L24 _private* field_ `string? _logText`
- L25 _private* field_ `readonly SyncAndRunDelegate _syncAndRun`
- L27-64 _public ctor_ `public UpdateSettingsWindow(string? prompt, string? logText, LauncherSettings settings, SyncAndRunDelegate syncAndRun)`
- L66-80 _public method_ `public LauncherResult ShowModal()`
- L82-88 _protected method_ `protected override void OnLoad(EventArgs e)`
- L90-94 _private method_ `private void ViewLogBtn_Click(object sender, EventArgs e)`
- L96-147 _private method_ `private void ConnectBtn_Click(object sender, EventArgs e)`
- L149-153 _private method_ `private void CancelBtn_Click(object sender, EventArgs e)`
- L155-160 _private method_ `private void HordeRadioBtn_CheckedChanged(object sender, EventArgs e)`
- L162-167 _private method_ `private void PerforceRadioBtn_CheckedChanged(object sender, EventArgs e)`
- L169-174 _private method_ `private void DisableRadioBtn_CheckedChanged(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/VariablesWindow.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.VariablesWindow`  
`partial class VariablesWindow`  
_internal*; L5-120_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-111 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L115 _private field_ `private System.Windows.Forms.Button OkButton`
- L116 _private field_ `private System.Windows.Forms.ListView MacrosList`
- L117 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L118 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader2`
- L119 _private field_ `private System.Windows.Forms.Button InsertButton`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Forms/VariablesWindow.cs` (UnrealGameSync)


#### class `UnrealGameSync.VariablesWindow`  
`public partial class VariablesWindow : ThemedForm`  
_public; L13-95_
- inherits: `ThemedForm`
- L15 _private* field_ `static readonly HashSet<string> s_legacyVariables = new HashSet<string>() { "UE4EditorConfig", "UE4EditorDebugArg", "UE4EditorExe", "UE4EditorCmdExe", "UseIncrementalBuilds", }`
- L24 _public delegate_ `public delegate void InsertVariableDelegate(string name)`
- L26 _public event_ `public event InsertVariableDelegate? OnInsertVariable`
- L28-61 _public ctor_ `public VariablesWindow(IReadOnlyDictionary<string, string> variables)`
- L63 _protected property_ `protected override bool ShowWithoutActivation => ...`
- L65-69 _private method_ `private void OkButton_Click(object sender, EventArgs e)`
- L71-81 _private method_ `private void MacrosList_MouseDoubleClick(object sender, MouseEventArgs args)`
- L83-89 _private method_ `private void InsertButton_Click(object sender, EventArgs e)`
- L91-94 _private method_ `private void MacrosList_SelectedIndexChanged(object sender, EventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/IssueMonitor.cs` (UnrealGameSync)


#### enum `UnrealGameSync.IssueBuildOutcome`  
`public enum IssueBuildOutcome`  
_public; L19-25_
- L21 _public* enumerator_ `Unknown`
- L22 _public* enumerator_ `Success`
- L23 _public* enumerator_ `Error`
- L24 _public* enumerator_ `Warning`

#### class `UnrealGameSync.IssueBuildData`  
`public class IssueBuildData`  
_public; L27-38_
- L29 _public property_ `public long Id { get; set; }`
- L30 _public property_ `public string Stream { get; set; }`
- L31 _public property_ `public int Change { get; set; }`
- L32 _public property_ `public string JobName { get; set; }`
- L33 _public property_ `public string JobUrl { get; set; }`
- L34 _public property_ `public string JobStepName { get; set; }`
- L35 _public property_ `public string JobStepUrl { get; set; }`
- L36 _public property_ `public string ErrorUrl { get; set; }`
- L37 _public property_ `public IssueBuildOutcome Outcome { get; set; }`

#### class `UnrealGameSync.IssueDiagnosticData`  
`public class IssueDiagnosticData`  
_public; L40-45_
- L42 _public property_ `public long? BuildId { get; set; }`
- L43 _public property_ `public string Message { get; set; }`
- L44 _public property_ `public string Url { get; set; }`

#### class `UnrealGameSync.IssueData`  
`public class IssueData`  
_public; L47-109_
- L49 _public property_ `public int Version { get; set; }`
- L50 _public property_ `public long Id { get; set; }`
- L51 _public property_ `public DateTime CreatedAt { get; set; }`
- L52 _public property_ `public DateTime RetrievedAt { get; set; }`
- L53 _public property_ `public string Project { get; set; }`
- L54 _public property_ `public string Summary { get; set; }`
- L55 _public property_ `public string Details { get; set; }`
- L56 _public property_ `public string Owner { get; set; }`
- L57 _public property_ `public string NominatedBy { get; set; }`
- L58 _public property_ `public DateTime? AcknowledgedAt { get; set; }`
- L59 _public property_ `public int FixChange { get; set; }`
- L60 _public property_ `public DateTime? ResolvedAt { get; set; }`
- L61 _public property_ `public bool Notify { get; set; }`
- L62 _public property_ `public bool IsWarning { get; set; }`
- L63 _public property_ `public string BuildUrl { get; set; }`
- L64 _public property_ `public List<string> Streams { get; }`
- L66 _private* field_ `HashSet<string>? _cachedProjects`
- L68-108 _public property_ `public HashSet<string> Projects { get; }`

#### class `UnrealGameSync.IssueUpdateData`  
`public class IssueUpdateData`  
_public; L111-119_
- L113 _public property_ `public long Id { get; set; }`
- L114 _public property_ `public string Owner { get; set; }`
- L115 _public property_ `public string? NominatedBy { get; set; }`
- L116 _public property_ `public bool? Acknowledged { get; set; }`
- L117 _public property_ `public int? FixChange { get; set; }`
- L118 _public property_ `public bool? Resolved { get; set; }`

#### enum `UnrealGameSync.IssueAlertReason`  
`public enum IssueAlertReason`  
_public; L122-129_
- attrs: `[Flags]`
- L124 _public* enumerator_ `Normal = 1`
- L125 _public* enumerator_ `Owner = 2`
- L126 _public* enumerator_ `UnassignedTimer = 4`
- L127 _public* enumerator_ `UnacknowledgedTimer = 8`
- L128 _public* enumerator_ `UnresolvedTimer = 16`

#### class `UnrealGameSync.IssueMonitor`  
`class IssueMonitor : IDisposable`  
_internal*; L131-466_
- inherits: `IDisposable`
- L133 _public property_ `public string? ApiUrl { get; }`
- L134 _public property_ `public string UserName { get; }`
- L135 _private* field_ `int _refCount = 1`
- L136 _private* field_ `Task? _workerTask`
- L137 _private* field_ `readonly ILogger _logger`
- L139 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L141 _private* field_ `readonly AsyncEvent _refreshEvent`
- L142 _private* field_ `int _updateIntervalMs`
- L143 _private* field_ `readonly List<long> _trackingIssueIds = new List<long>()`
- L144 _private* field_ `List<IssueData> _issues = new List<IssueData>()`
- L145 _private* field_ `readonly object _lockObject = new object()`
- L146 _private* field_ `readonly List<IssueUpdateData> _pendingUpdates = new List<IssueUpdateData>()`
- L147 _private* field_ `readonly IAsyncDisposer _asyncDisposer`
- L149 _public property_ `public Action? OnIssuesChanged { get; set; }`
- L152 _public property_ `public Dictionary<long, IssueAlertReason> IssueIdToAlertReason { get; }`
- L154-173 _public ctor_ `public IssueMonitor(string? apiUrl, string userName, TimeSpan updateInterval, IServiceProvider serviceProvider)`
- L175-179 _public property_ `public string LastStatusMessage { get; set; }`
- L181-184 _public method_ `public List<IssueData> GetIssues()`
- L186-189 _public method_ `public TimeSpan GetUpdateInterval()`
- L191-195 _public method_ `public void SetUpdateInterval(TimeSpan updateInterval)`
- L197-204 _public method_ `public void StartTracking(long issueId)`
- L206-212 _public method_ `public void StopTracking(long issueId)`
- L214-217 _public method_ `public bool HasPendingUpdate()`
- L219-234 _public method_ `public void PostUpdate(IssueUpdateData update)`
- L236-272 _private* method_ `static bool ApplyPendingUpdate(List<IssueData> issues, IssueUpdateData update)`
- L274-280 _public method_ `public void Start()`
- L282-289 _public method_ `public void AddRef()`
- L291-302 _public method_ `public void Release()`
- L304-307 _private* method_ `void IDisposable.Dispose()`
- L309-319 _private* method_ `void DisposeInternal()`
- L321-364 _private* method_ `async Task PollForUpdatesAsync(CancellationToken cancellationToken)`
- L366-379 _private* method_ `async Task<bool> SendUpdateAsync(IssueUpdateData update, CancellationToken cancellationToken)`
- L381-465 _private* method_ `async Task<bool> ReadCurrentIssuesAsync(CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Launcher.cs` (UnrealGameSync)


#### enum `UnrealGameSync.LauncherResult`  
`enum LauncherResult`  
_internal*; L28-32_
- L30 _public* enumerator_ `Continue`
- L31 _public* enumerator_ `Exit`

#### class `UnrealGameSync.Launcher`  
`static class Launcher`  
_internal*; L34-470_
- L37-124 _public method_ `public static LauncherResult SyncAndRunLatest(Mutex instanceMutex, string[] args)`
- L127 _public field_ `public static readonly string[] s_deleteActions = { "delete", "move/delete", "purge", "archive" }`
- L138-141 _private* method_ `static string GetSyncFolder()`
- L143-381 _public method_ `public static async Task SyncAndRun(IPerforceConnection? perforce, LauncherSettings launcherSettings, string[] args, Mutex instanceMutex, ILogger logger, CancellationToken cancellationToken)`
- L383-395 _private* method_ `static bool TryReadAllText(string fileName, [NotNullWhen(true)] out string? text)`
- L397-408 _private* method_ `static bool TryWriteAllText(string fileName, string text)`
- L410-421 _private* method_ `static bool SafeCreateDirectory(string directoryName)`
- L423-434 _private* method_ `static bool SafeDeleteDirectory(string directoryName)`
- L436-456 _private* method_ `static bool SafeDeleteDirectoryContents(string directoryName)`
- L458-469 _private* method_ `static async Task SafeDeleteDirectoryContentsWithRetryAsync(string directoryName, CancellationToken cancellationToken)`

#### class `UnrealGameSync.Launcher.LoggerProviderAdapter`  
`class LoggerProviderAdapter : ILoggerProvider`  
_private*; L129-136_
- inherits: `ILoggerProvider`
- L131 _private* field_ `readonly ILogger _logger`
- L133 _public ctor_ `public LoggerProviderAdapter(ILogger logger)`
- L134 _public method_ `public ILogger CreateLogger(string categoryName)`
- L135 _public method_ `public void Dispose()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Logging.cs` (UnrealGameSync)


#### class `UnrealGameSync.Logging`  
`static class Logging`  
_internal*; L10-22_
- L12-21 _public method_ `public static ILoggerProvider CreateLoggerProvider(FileReference file)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/ModalTask.cs` (UnrealGameSync)


#### enum `UnrealGameSync.ModalTaskFlags`  
`enum ModalTaskFlags`  
_internal*; L11-15_
- attrs: `[Flags]`
- L13 _public* enumerator_ `None = 0`
- L14 _public* enumerator_ `Quiet = 1`

#### class `UnrealGameSync.ModalTask`  
`class ModalTask`  
_internal*; L17-92_
- L19 _public property_ `public Task Task { get; }`
- L21 _public property_ `public bool Failed => ...`
- L22 _public property_ `public bool Succeeded => ...`
- L24 _public property_ `public Exception? Exception => ...`
- L26-29 _public ctor_ `public ModalTask(Task task)`
- L31-54 _public property_ `public string Error { get; }`
- L56-64 _public method_ `public static ModalTask? Execute(IWin32Window? owner, string title, string message, Func<CancellationToken, Task> taskFunc, ModalTaskFlags flags = ModalTaskFlags.None)`
- L66-91 _public method_ `public static ModalTask<T>? Execute<T>(IWin32Window? owner, string title, string message, Func<CancellationToken, Task<T>> taskFunc, ModalTaskFlags flags = ModalTaskFlags.None)`

#### class `UnrealGameSync.ModalTask`  
`class ModalTask<T> : ModalTask`  
_internal*; L94-103_
- inherits: `ModalTask`
- L96 _public property_ `public new Task<T> Task => ...`
- L98 _public property_ `public T Result => ...`
- L100-102 _public ctor_ `public ModalTask(Task<T> task) : base(task)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/PerforceModalTask.cs` (UnrealGameSync)


#### class `UnrealGameSync.PerforceLoginException`  
`public class PerforceLoginException : Exception`  
_public; L12-20_
- inherits: `Exception`
- L14 _public property_ `public PerforceResponse<LoginRecord> Response { get; }`
- L16-19 _public ctor_ `public PerforceLoginException(PerforceResponse<LoginRecord> response) : base($"Login failed: {response}")`

#### class `UnrealGameSync.PerforceModalTask`  
`static class PerforceModalTask`  
_internal*; L22-136_
- L24-33 _public method_ `public static ModalTask? Execute(IWin32Window? owner, string title, string message, IPerforceSettings perforceSettings, Func<IPerforceConnection, CancellationToken, Task> executeAsync, ILogger logger, ModalTaskFlags flags = ModalTaskFlags.None)`
- L35-53 _public method_ `public static ModalTask<T>? Execute<T>(IWin32Window? owner, string title, string message, IPerforceSettings perforceSettings, Func<IPerforceConnection, CancellationToken, Task<T>> executeAsync, ILogger logger, ModalTaskFlags flags = ModalTaskFlags.None)`
- L55-63 _public method_ `public static ModalTask? Execute(IWin32Window? owner, string title, string message, IPerforceConnection perforceConnection, Func<IPerforceConnection, CancellationToken, Task> executeAsync, ILogger logger, ModalTaskFlags flags = ModalTaskFlags.None)`
- L65-68 _public method_ `public static ModalTask<T>? Execute<T>(IWin32Window? owner, string title, string message, IPerforceConnection perforceConnection, Func<IPerforceConnection, CancellationToken, Task<T>> executeAsync, ModalTaskFlags flags = ModalTaskFlags.None)`
- L70-111 _private method_ `private static ModalTask<T>? ExecuteInternal<T>(IWin32Window? owner, string title, string message, IPerforceSettings perforceSettings, Func<Task<IPerforceConnection>> connectAsync, Func<IPerforceConnection, CancellationToken, Task<T>> executeAsync, ModalTaskFlags flags = ModalTaskFlags.None)`
- L113-135 _private method_ `private static async Task<T> LoginAndExecuteAsync<T>(string? password, Func<Task<IPerforceConnection>> connectAsync, Func<IPerforceConnection, CancellationToken, Task<T>> executeAsync, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/PerforceMonitor.cs` (UnrealGameSync)


#### interface `UnrealGameSync.IArchiveInfoSource`  
`interface IArchiveInfoSource`  
_internal*; L20-23_
- L22 _public* property_ `IReadOnlyList<IArchiveChannel> AvailableArchiveChannels { get; }`

#### class `UnrealGameSync.PerforceMonitorCache`  
`internal class PerforceMonitorCache`  
_internal; L25-50_
- L27 _public property_ `public Dictionary<string, DateTime> Streams { get; set; }`
- L29-40 _public method_ `public static bool Get(FileReference path, out PerforceMonitorCache? cache)`
- L42-49 _public method_ `public static void Set(FileReference path, PerforceMonitorCache? cache)`

#### class `UnrealGameSync.PerforceMonitor`  
`class PerforceMonitor : IDisposable, IArchiveInfoSource`  
_internal*; L52-694_
- inherits: `IDisposable, IArchiveInfoSource`
- L62 _public const_ `public const int InitialMaxChangesValue = 100`
- L63 _public property_ `public bool ShowChangesForAllProjects { get; set; }`
- L65 _private* field_ `readonly IPerforceSettings _perforceSettings`
- L66 _private* field_ `readonly string _branchClientPath`
- L67 _private* field_ `readonly string _selectedClientFileName`
- L68 _private* field_ `readonly string _selectedProjectIdentifier`
- L69 _private* field_ `Task? _workerTask`
- L71 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L73 _private* field_ `int _pendingMaxChangesValue`
- L74 _private* field_ `SortedSet<ChangesRecord> _changes = new SortedSet<ChangesRecord>(new PerforceChangeSorter())`
- L75 _private* field_ `readonly SortedDictionary<int, PerforceChangeDetails> _changeDetails = ...`
- L75 _private* field_ `readonly SortedDictionary< _changeDetails = new SortedDictionary<int, PerforceChangeDetails>()`
- L76 _private* field_ `readonly SortedSet<int> _promotedChangeNumbers = new SortedSet<int>()`
- L77 _private* field_ `List<BaseArchiveChannel> _archives = new List<BaseArchiveChannel>()`
- L78 _private* field_ `readonly AsyncEvent _refreshEvent = new AsyncEvent()`
- L79 _private* field_ `readonly ILogger _logger`
- L80 _private* field_ `readonly bool _isEnterpriseProject`
- L81 _private* field_ `readonly DirectoryReference _cacheFolder`
- L82 _private* field_ `readonly List<KeyValuePair<FileReference, DateTime>> _localConfigFiles`
- L82 _private* field_ `readonly List<KeyValuePair< _localConfigFiles`
- L83 _private* field_ `readonly IAsyncDisposer _asyncDisposeTasks`
- L85 _private* field_ `readonly IHordeClient? _hordeClient`
- L87 _private field_ `private readonly ICloudStorage? _cloudStorage`
- L88 _private* field_ `string[] prevCodeRules = Array.Empty<string>()`
- L89 _private* field_ `string[] prevUefnRules = Array.Empty<string>()`
- L91 _private* field_ `readonly FileReference CacheFile`
- L93 _private* field_ `readonly SynchronizationContext _synchronizationContext`
- L94 _public event_ `public event Action? OnUpdate`
- L95 _public event_ `public event Action? OnUpdateMetadata`
- L96 _public event_ `public event Action? OnStreamChange`
- L97 _public event_ `public event Action? OnStreamViewChange`
- L98 _public event_ `public event Action? OnLoginExpired`
- L100 _private* field_ `readonly object _lockObject = new object()`
- L102-106 _public property_ `public TimeSpan ServerTimeZone { get; set; }`
- L108-132 _public ctor_ `public PerforceMonitor(IPerforceSettings perforceSettings, ProjectInfo projectInfo, Workspace workspace, ConfigFile projectConfigFile, DirectoryReference cacheFolder, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, IServiceProvider serviceProvider)`
- L134-137 _public method_ `public void Start()`
- L139-153 _public method_ `public void Dispose()`
- L155-159 _public property_ `public bool IsActive { get; set; }`
- L161-165 _public property_ `public string LastStatusMessage { get; set; }`
- L167-171 _public property_ `public int CurrentMaxChanges { get; set; }`
- L173-187 _public property_ `public int PendingMaxChanges { get; set; }`
- L189-211 _private* method_ `async Task PollForUpdates(CancellationToken cancellationToken)`
- L213-357 _private* method_ `async Task PollForUpdatesInner(CancellationToken cancellationToken)`
- L359-512 _private* method_ `async Task<bool> UpdateChangesAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L514-610 _public method_ `public async Task<bool> UpdateChangeTypesAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L612-629 _private* method_ `async Task<bool> UpdateArchivesAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L631-635 _private* method_ `async Task UpdateProjectConfigFileAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L637-643 _public method_ `public List<ChangesRecord> GetChanges()`
- L645-651 _public method_ `public bool TryGetChangeDetails(int number, [NotNullWhen(true)] out PerforceChangeDetails? details)`
- L653-659 _public method_ `public HashSet<int> GetPromotedChangeNumbers()`
- L661-664 _public method_ `public ConfigSection? LatestPerforceConfigSection()`
- L666-670 _public property_ `public int LastChangeByCurrentUser { get; set; }`
- L672-676 _public property_ `public int LastCodeChangeByCurrentUser { get; set; }`
- L678-682 _public property_ `public ConfigFile LatestProjectConfigFile { get; set; }`
- L684-688 _public property_ `public IReadOnlyList<IArchiveChannel> AvailableArchiveChannels { get; set; }`
- L690-693 _public method_ `public void Refresh()`

#### class `UnrealGameSync.PerforceMonitor.PerforceChangeSorter`  
`class PerforceChangeSorter : IComparer<ChangesRecord>`  
_private*; L54-60_
- inherits: `IComparer<ChangesRecord>`
- L56-59 _public method_ `public int Compare(ChangesRecord? summaryA, ChangesRecord? summaryB)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Program.cs` (UnrealGameSync)


#### class `UnrealGameSync.Program`  
`static partial class Program`  
_internal*; L32-511_
- L37 _private* property_ `static CreateTelemetrySinkDelegate CreateTelemetrySink { get; }` — Delegate used to create a new telemetry sink
- L40 _private property_ `private static SessionLockTracker SessionLockTracker { get; }`
- L42-46 _public method_ `public static string GetVersionString()`
- L48 _public field_ `public static string? SyncVersion = null`
- L50-56 _public method_ `public static void CaptureException(Exception exception)`
- L59-89 _private* method_ `static void Main(string[] args)` — attrs: `[STAThread]`
- L91-140 _private* method_ `static void RealMain(string[] args)`
- L142-296 _private* method_ `static void InnerMain(Mutex instanceMutex, EventWaitHandle activateEvent, string[] args, bool runUpdateCheck)`
- L298-303 _private* method_ `static void AsyncDispose(IAsyncDisposable disposable)`
- L305-317 _public method_ `public static string GetCurrentExecutable()`
- L319-326 _private* method_ `static bool ShouldRunAutoUpdate(string[] args)`
- L328-342 _private method_ `private static UpdateMonitor CreateUpdateMonitor(LauncherSettings launcherSettings, IPerforceSettings defaultSettings, string? updatePath, bool runUpdateCheck, IServiceProvider serviceProvider)`
- L344-351 _private method_ `private static void TraceException(Exception ex, ILogger logger)`
- L353-360 _private method_ `private static void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs args)`
- L362-369 _private method_ `private static void CurrentDomain_UnhandledException_Sentry(object sender, UnhandledExceptionEventArgs args)`
- L371-385 _private method_ `private static void Application_ThreadException_Sentry(object sender, ThreadExceptionEventArgs e)`
- L387-394 _private method_ `private static void Application_UnobservedException_Sentry(object? sender, UnobservedTaskExceptionEventArgs args)`
- L396-429 _private* method_ `static void MergeUpdateSettings(FileReference updateConfigFile, ref string? updatePath, ref string? updateSpawn)`
- L431-445 _private* method_ `static bool ParseOption(List<string> remainingArgs, string option, out bool value)`
- L447-461 _private* method_ `static bool ParseArgument(List<string> remainingArgs, string prefix, [NotNullWhen(true)] out string? value)`
- L463-489 _public method_ `public static IEnumerable<string> GetPerforcePaths()`
- L491-510 _public method_ `public static void SpawnP4Vc(string arguments)`

#### Namespace-level symbols

- L30 _public delegate_ `public delegate ITelemetrySink CreateTelemetrySinkDelegate(string userName, string sessionId, ILogger logger)` — Delegate used to create a telemetry sink

### `Source/Programs/UnrealGameSync/UnrealGameSync/ProgramApplicationContext.cs` (UnrealGameSync)


#### class `UnrealGameSync.ProgramApplicationContext`  
`class ProgramApplicationContext : ApplicationContext`  
_internal*; L23-488_
- inherits: `ApplicationContext`
- L25 _private* property_ `static ProgramApplicationContext? s_instance { get; set; }`
- L26 _private* field_ `readonly SynchronizationContext _mainThreadSynchronizationContext`
- L28 _private* field_ `readonly IPerforceSettings _defaultPerforceSettings`
- L29 _private* field_ `readonly UpdateMonitor _updateMonitor`
- L30 _private* field_ `readonly string? _apiUrl`
- L31 _private* field_ `readonly DirectoryReference _dataFolder`
- L32 _private* field_ `readonly DirectoryReference _cacheFolder`
- L33 _private* field_ `readonly bool _restoreState`
- L34 _private* field_ `readonly string? _updateSpawn`
- L35 _private* field_ `readonly bool _preview`
- L36 _private* field_ `bool _isClosing`
- L37 _private* field_ `readonly string? _uri`
- L39 _private* field_ `readonly IServiceProvider _serviceProvider`
- L40 _private* field_ `readonly ILogger _logger`
- L41 _private* field_ `readonly UserSettings _settings`
- L42 _private* field_ `readonly ApplicationThemeManager _themeManager`
- L43 _private* field_ `ActivationListener _activationListener`
- L45 _private* field_ `Container _components = new Container()`
- L46 _private* field_ `NotifyIcon _notifyIcon`
- L49 _private* field_ `readonly ContextMenuStrip _notifyMenu`
- L50 _private* field_ `readonly ToolStripMenuItem _notifyMenuOpenUnrealGameSync`
- L51 _private* field_ `readonly ToolStripSeparator _notifyMenuOpenUnrealGameSyncSeparator`
- L52 _private* field_ `readonly ToolStripMenuItem _notifyMenuSyncNow`
- L53 _private* field_ `readonly ToolStripMenuItem _notifyMenuLaunchEditor`
- L54 _private* field_ `readonly ToolStripSeparator _notifyMenuExitSeparator`
- L55 _private* field_ `readonly ToolStripMenuItem _notifyMenuExit`
- L58 _private* field_ `CancellationTokenSource _startupCancellationSource = new CancellationTokenSource()`
- L59 _private* field_ `readonly Task _startupTask`
- L60 _private* field_ `ModalTaskWindow? _startupWindow`
- L62 _private* field_ `MainWindow? _mainWindowInstance`
- L65 _private* field_ `WindowsFormsSynchronizationContext? _synchronizationContext`
- L67-230 _public ctor_ `public ProgramApplicationContext(IPerforceSettings defaultPerforceSettings, UpdateMonitor updateMonitor, string? apiUrl, DirectoryReference dataFolder, EventWaitHandle activateEvent, bool restoreState, string? updateSpawn, string? projectFileName, bool preview, IServiceProvider serviceProvider, string? uri)`
- L232-235 _public method_ `public static ApplicationThemeManager? GetThemeManager()`
- L237-240 _public method_ `public static ApplicationTheme GetTheme()`
- L242-254 _private* method_ `static bool IsValidProject(UserSelectedProjectSettings projectSettings, ILogger logger)`
- L256-283 _private* method_ `static async Task WaitForStartupTasks(List<(UserSelectedProjectSettings, ModalTask<OpenProjectInfo>)> startupTasks, IHordeClient? hordeClient)`
- L285-295 _private method_ `private UserSelectedProjectSettings UpgradeSelectedProjectSettings(UserSelectedProjectSettings project)`
- L297-334 _private method_ `private void OnStartupComplete(List<(UserSelectedProjectSettings, ModalTask<OpenProjectInfo>)> startupTasks)`
- L336-339 _private method_ `private void MainWindowInstance_FormClosed(object? sender, FormClosedEventArgs e)`
- L341-347 _private method_ `private void OnActivationListenerCallback()`
- L349-352 _private method_ `private void OnActivationListenerAsyncCallback()`
- L354-365 _private method_ `private void OnUpdateAvailable(UpdateType type)`
- L367-370 _private method_ `private void OnUpdateAvailableCallback(UpdateType type)`
- L372-421 _protected method_ `protected override void Dispose(bool disposing)`
- L423-434 _private method_ `private void NotifyIcon_MouseDown(object? sender, MouseEventArgs e)`
- L436-439 _private method_ `private void NotifyIcon_DoubleClick(object? sender, EventArgs e)`
- L441-445 _private method_ `private void NotifyMenu_OpenUnrealGameSync_Click(object? sender, EventArgs e)`
- L447-450 _private method_ `private void NotifyMenu_SyncNow_Click(object? sender, EventArgs e)`
- L452-455 _private method_ `private void NotifyMenu_LaunchEditor_Click(object? sender, EventArgs e)`
- L457-477 _private method_ `private void NotifyMenu_Exit_Click(object? sender, EventArgs e)`
- L479-487 _protected method_ `protected override void ExitThreadCore()`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Properties/Resources.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Properties.Resources`  
`internal class Resources`  
_internal; L25-172_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L66-71 _internal property_ `internal static System.Drawing.Bitmap AlertErrorIcon { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L76-81 _internal property_ `internal static System.Drawing.Bitmap AlertWarningIcon { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L86-91 _internal property_ `internal static System.Drawing.Bitmap DefaultErrorLogo { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L96-101 _internal property_ `internal static System.Drawing.Bitmap DefaultNotificationLogo { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L106-111 _internal property_ `internal static System.Drawing.Bitmap DefaultProjectLogo { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L116-121 _internal property_ `internal static System.Drawing.Bitmap DropList { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L126-131 _internal property_ `internal static System.Drawing.Icon Icon { get; }` — Looks up a localized resource of type System.Drawing.Icon similar to (Icon).
- L136-141 _internal property_ `internal static System.Drawing.Bitmap Icons { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L146-151 _internal property_ `internal static System.Drawing.Bitmap Log { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L156-161 _internal property_ `internal static System.Drawing.Bitmap Perforce { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.
- L166-171 _internal property_ `internal static System.Drawing.Bitmap StatusIcons { get; }` — Looks up a localized resource of type System.Drawing.Bitmap.

### `Source/Programs/UnrealGameSync/UnrealGameSync/Properties/Settings.Designer.cs` (UnrealGameSync)


#### class `UnrealGameSync.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L16-25_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "16.7.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L18 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L20-24 _public property_ `public static Settings Default { get; }`

### `Source/Programs/UnrealGameSync/UnrealGameSync/RESTApi.cs` (UnrealGameSync)


#### class `UnrealGameSync.RestException`  
`public class RestException : Exception`  
_public; L13-24_
- inherits: `Exception`
- L15-18 _public ctor_ `public RestException(HttpMethod method, string? uri, Exception innerException) : base(String.Format("Error executing {0} {1}", method, uri), innerException)`
- L20-23 _public method_ `public override string ToString()`

#### class `UnrealGameSync.RestApi`  
`public static class RestApi`  
_public; L26-77_
- L28 _private* field_ `static readonly HttpClient s_httpClient = new HttpClient()`
- L30-56 _private method_ `private static async Task<string> SendRequestInternalAsync(string url, HttpMethod method, string? requestBody, CancellationToken cancellationToken)`
- L58-61 _public method_ `public static Task<string> PostAsync(string url, string requestBody, CancellationToken cancellationToken)`
- L63-66 _public method_ `public static Task<string> GetAsync(string url, CancellationToken cancellationToken)`
- L68-71 _public method_ `public static async Task<T> GetAsync<T>(string url, CancellationToken cancellationToken)`
- L73-76 _public method_ `public static Task<string> PutAsync<T>(string url, T obj, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/SessionLockTracker.cs` (UnrealGameSync)


#### class `UnrealGameSync.SessionLockTracker`  
`public class SessionLockTracker`  
_public; L7-29_
- L9 _private field_ `private volatile bool _sessionLocked = false`
- L11 _public property_ `public bool IsSessionLocked => ...`
- L13-16 _public ctor_ `public SessionLockTracker()`
- L18-28 _private method_ `private void OnSessionSwitch(object sender, SessionSwitchEventArgs e)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Taskbar.cs` (UnrealGameSync)


#### enum `UnrealGameSync.TaskbarState`  
`enum TaskbarState`  
_internal*; L8-15_
- L10 _public* enumerator_ `NoProgress = 0`
- L11 _public* enumerator_ `Indeterminate = 0x1`
- L12 _public* enumerator_ `Normal = 0x2`
- L13 _public* enumerator_ `Error = 0x4`
- L14 _public* enumerator_ `Paused = 0x8`

#### class `UnrealGameSync.Taskbar`  
`static class Taskbar`  
_internal*; L17-78_
- L37 _private* field_ `static readonly ITaskbarList3? _interface = CreateTaskbarListInterface()`
- L39-49 _private* method_ `static ITaskbarList3? CreateTaskbarListInterface()`
- L51-63 _public method_ `public static void SetState(IntPtr windowHandle, TaskbarState state)`
- L65-77 _public method_ `public static void SetProgress(IntPtr windowHandle, ulong completed, ulong total)`

#### interface `UnrealGameSync.Taskbar.ITaskbarList3`  
`interface ITaskbarList3`  
_private*; L20-30_
- attrs: `[ComImport, Guid("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]`
- L22 _public* method_ `void HrInit()`
- L23 _public* method_ `void AddTab(IntPtr hWnd)`
- L24 _public* method_ `void DeleteTab(IntPtr hWnd)`
- L25 _public* method_ `void ActivateTab(IntPtr hWnd)`
- L26 _public* method_ `void SetActiveAlt(IntPtr hWnd)`
- L27 _public* method_ `void MarkFullscreenWindow(IntPtr hWnd, int fFullscreen)`
- L28 _public* method_ `void SetProgressValue(IntPtr hWnd, ulong ullCompleted, ulong ullTotal)`
- L29 _public* method_ `void SetProgressState(IntPtr hWnd, TaskbarState state)`

#### class `UnrealGameSync.Taskbar.TaskbarList3`  
`class TaskbarList3`  
_private*; L33-35_
- attrs: `[ComImport, Guid("56FDF344-FD6D-11d0-958A-006097C9A090"), ClassInterfaceAttribute(ClassInterfaceType.None)]`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UpdateMonitor.cs` (UnrealGameSync)


#### enum `UnrealGameSync.UpdateType`  
`enum UpdateType`  
_internal*; L15-19_
- L17 _public* enumerator_ `Background`
- L18 _public* enumerator_ `UserInitiated`

#### class `UnrealGameSync.UpdateMonitor`  
`abstract class UpdateMonitor : IAsyncDisposable`  
_internal*; L21-48_
- inherits: `IAsyncDisposable`
- L23-27 _public property_ `public bool IsUpdateAvailable { get; set; }`
- L29 _public field_ `public Action<UpdateType>? OnUpdateAvailable`
- L31-35 _public property_ `public bool OpenSettings { get; set; }`
- L37 _public method_ `public abstract ValueTask DisposeAsync()`
- L39-47 _public method_ `public void TriggerUpdate(UpdateType updateType, bool openSettings)`

#### class `UnrealGameSync.NullUpdateMonitor`  
`class NullUpdateMonitor : UpdateMonitor`  
_internal*; L50-53_
- inherits: `UpdateMonitor`
- L52 _public method_ `public override ValueTask DisposeAsync()`

#### class `UnrealGameSync.HordeUpdateMonitor`  
`class HordeUpdateMonitor : UpdateMonitor`  
_internal*; L55-118_
- inherits: `UpdateMonitor`
- L57 _private* field_ `readonly ToolId _toolId`
- L58 _private* field_ `readonly string _currentVersion`
- L59 _private* field_ `readonly IServiceProvider _serviceProvider`
- L60 _private* field_ `readonly BackgroundTask _backgroundTask`
- L61 _private* field_ `readonly ILogger _logger`
- L63-66 _public ctor_ `public HordeUpdateMonitor(string currentVersion, IServiceProvider serviceProvider) : this(DeploymentSettings.Instance.HordeToolId, currentVersion, serviceProvider)`
- L68-75 _public ctor_ `public HordeUpdateMonitor(ToolId toolId, string currentVersion, IServiceProvider serviceProvider)`
- L77-80 _public method_ `public override async ValueTask DisposeAsync()`
- L82-117 _public method_ `public async Task CheckForUpdatesLoopAsync(CancellationToken cancellationToken)`

#### class `UnrealGameSync.PerforceUpdateMonitor`  
`class PerforceUpdateMonitor : UpdateMonitor`  
_internal*; L120-197_
- inherits: `UpdateMonitor`
- L122 _private* field_ `Task? _workerTask`
- L124 _private* field_ `readonly CancellationTokenSource _cancellationSource = new CancellationTokenSource()`
- L126 _private* field_ `readonly ILogger _logger`
- L128-137 _public ctor_ `public PerforceUpdateMonitor(IPerforceSettings perforceSettings, string? watchPath, IServiceProvider serviceProvider)`
- L139-152 _public method_ `public override async ValueTask DisposeAsync()`
- L154-196 _private* method_ `async Task PollForUpdatesAsync(IPerforceSettings perforceSettings, string watchPath, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UriHandlers/P4Handler.cs` (UnrealGameSync)


#### class `UnrealGameSync.P4Handler`  
`static class P4Handler`  
_internal*; L11-42_
- desc: P4 URI handler
- L14-24 _public method_ `public static UriResult P4V(string depotPath)` — attrs: `[UriHandler(true)]`
- L27-34 _public method_ `public static UriResult Timelapse(string depotPath, int line = -1)` — attrs: `[UriHandler(true)]`
- L37-41 _public method_ `public static UriResult Change(int number)` — attrs: `[UriHandler(true)]`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UriHandlers/RdpHandler.cs` (UnrealGameSync)


#### class `UnrealGameSync.RdpHandler`  
`static class RdpHandler`  
_internal*; L12-134_
- L14 _private* const_ `const uint CredTypeGeneric = 1`
- L15 _private* const_ `const uint CredTypeDomainPassword = 2`
- L16 _private* const_ `const uint CredPersistLocalMachine = 2`
- L49 _private* method_ `static extern bool CredRead(string target, uint type, int reservedFlag, out IntPtr buffer)` — attrs: `[DllImport("Advapi32.dll", EntryPoint = "CredReadW", CharSet = CharSet.Unicode, SetLastError = true)]`
- L52 _private* method_ `static extern bool CredWrite(Credential userCredential, uint flags)` — attrs: `[DllImport("Advapi32.dll", EntryPoint = "CredWriteW", CharSet = CharSet.Unicode, SetLastError = true)]`
- L55 _private* method_ `static extern bool CredFree(IntPtr buffer)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)]`
- L57-88 _public method_ `public static bool ReadCredential(string name, uint type, [NotNullWhen(true)] out string? userName, [NotNullWhen(true)] out string? password)`
- L90-110 _public method_ `public static void WriteCredential(string name, uint type, string userName, string password)`
- L113-133 _public method_ `public static UriResult Rdp(string host)` — attrs: `[UriHandler(terminate: true)]`

#### struct `UnrealGameSync.RdpHandler.CredentialAttribute`  
`struct CredentialAttribute`  
_private*; L21-27_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]`
- L23 _private* field_ `string Keyword`
- L24 _private* field_ `uint Flags`
- L25 _private* field_ `uint ValueSize`
- L26 _private* field_ `IntPtr Value`

#### class `UnrealGameSync.RdpHandler.Credential`  
`class Credential`  
_private*; L30-44_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L32 _public field_ `public uint Flags`
- L33 _public field_ `public uint Type`
- L34 _public field_ `public string? TargetName`
- L35 _public field_ `public string? Comment`
- L36 _public field_ `public FILETIME LastWritten`
- L37 _public field_ `public int CredentialBlobSize`
- L38 _public field_ `public IntPtr CredentialBlob`
- L39 _public field_ `public uint Persist`
- L40 _public field_ `public uint AttributeCount`
- L41 _public field_ `public IntPtr Attributes`
- L42 _public field_ `public string? TargetAlias`
- L43 _public field_ `public string? UserName`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UriHandlers/UGSHandler.cs` (UnrealGameSync)


#### class `UnrealGameSync.UgsHandler`  
`static class UgsHandler`  
_internal*; L12-87_
- desc: UGS handler
- L15-29 _public method_ `public static UriResult OpenProject(string stream, string project, bool sync = false)` — attrs: `[UriHandler]`
- L32-37 _public method_ `public static UriResult BuildStep(string project, string stream, string step, string changelist, string arguments)` — attrs: `[UriHandler]`
- L40-55 _public method_ `public static UriResult Execute(string stream, int changelist, string command, string project = "")` — attrs: `[UriHandler]`
- L58-70 _public method_ `public static UriResult OpenIssue(int id)` — attrs: `[UriHandler]`
- L73-86 _public method_ `public static UriResult RunCustomTool(string toolName, string args)` — attrs: `[UriHandler]`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UriHandlers/UriHandler.cs` (UnrealGameSync)


#### class `UnrealGameSync.UriResult`  
`class UriResult`  
_internal*; L22-27_
- desc: Uri handler result
- L24 _public field_ `public bool Success = false`
- L25 _public field_ `public string? Error`
- L26 _public field_ `public AutomationRequest? Request = null`

#### class `UnrealGameSync.UriHandler`  
`static class UriHandler`  
_internal*; L32-251_
- desc: Main handler for Uri requests
- L34-110 _public method_ `public static UriResult HandleUri(string uriIn)`
- L112 _public const_ `public const string InstallHandlerArg = "-InstallHandler"`
- L113 _public const_ `public const string UninstallHandlerArg = "-UninstallHandler"`
- L114 _public const_ `public const string ElevatedArg = "-Elevated"`
- L119-208 _public method_ `public static bool ProcessCommandLine(string[] args, bool firstInstance, EventWaitHandle? activateEvent = null)` — Handle URI passed in via command lines
- L210-244 _private* ctor_ `static UriHandler()`
- L249 _private* field_ `static readonly Dictionary<string, MethodInfo> Handlers = ...` — All available handler infos
- L249 _private* field_ `static readonly Dictionary< Handlers = new Dictionary<string, MethodInfo>(StringComparer.OrdinalIgnoreCase)` — All available handler infos

#### class `UnrealGameSync.UriHandlerAttribute`  
`sealed class UriHandlerAttribute : Attribute`  
_internal*; L257-265_
- attrs: `[AttributeUsage(AttributeTargets.Method)]`
- inherits: `Attribute`
- desc: Method attribute for Uri handlers
- L259 _public property_ `public bool Terminate { get; }`
- L261-264 _public ctor_ `public UriHandlerAttribute(bool terminate = false)`

#### enum `UnrealGameSync.ProtocolHandlerState`  
`enum ProtocolHandlerState`  
_internal*; L267-272_
- L269 _public* enumerator_ `Unknown`
- L270 _public* enumerator_ `Installed`
- L271 _public* enumerator_ `NotInstalled`

#### class `UnrealGameSync.ProtocolHandlerUtils`  
`static class ProtocolHandlerUtils`  
_internal*; L278-437_
- desc: Development utilities to register protocol binary, this or a variation should go in installer/updater Needs administrator to edit registry
- L296 _public property_ `public static string CurrentProcessFilePath => ...`
- L298-308 _private* method_ `static List<RegistrySetting> GetGlobalRegistrySettings()`
- L310-320 _private* method_ `static List<RegistrySetting> GetUserRegistrySettings()`
- L322-325 _public method_ `public static ProtocolHandlerState GetState()`
- L327-359 _private method_ `private static ProtocolHandlerState GetState(IEnumerable<RegistrySetting> keys)`
- L361-364 _public method_ `public static void Install()`
- L366-376 _public method_ `public static void InstallElevated()`
- L378-389 _public method_ `public static void InstallQuiet(ILogger logger)`
- L391-394 _public method_ `public static void Uninstall()`
- L396-406 _public method_ `public static void UninstallElevated()`
- L408-419 _private method_ `private static void RunElevated(string arguments)`
- L421-436 _private method_ `private static void ApplyRegistrySettings(IEnumerable<RegistrySetting> settings)`

#### class `UnrealGameSync.ProtocolHandlerUtils.RegistrySetting`  
`class RegistrySetting`  
_private*; L280-294_
- L282 _public field_ `public RegistryKey RootKey`
- L283 _public field_ `public string KeyName`
- L284 _public field_ `public string? ValueName`
- L285 _public field_ `public string Value`
- L287-293 _public ctor_ `public RegistrySetting(RegistryKey rootKey, string keyName, string? valueName, string value)`

### `Source/Programs/UnrealGameSync/UnrealGameSync/UriHandlers/VisualStudioHandler.cs` (UnrealGameSync)


#### class `UnrealGameSync.VisualStudioHandler`  
`static class VisualStudioHandler`  
_internal*; L10-25_
- desc: VisualStudio Uri Handler
- L13-24 _public method_ `public static UriResult VsOpen(string depotPath, int line = -1)` — attrs: `[UriHandler(true)]`

### `Source/Programs/UnrealGameSync/UnrealGameSync/Workspace.cs` (UnrealGameSync)


#### class `UnrealGameSync.Workspace`  
`public sealed class Workspace : IDisposable`  
_public; L14-256_
- inherits: `IDisposable`
- L16 _public property_ `public IPerforceSettings PerforceSettings { get; }`
- L17 _private* field_ `readonly WorkspaceStateWrapper _stateWrapper`
- L18 _public property_ `public ReadOnlyWorkspaceState State { get; set; }`
- L19 _public property_ `public ProjectInfo Project { get; }`
- L20 _public property_ `public DirectoryReference RootDir => ...`
- L22 _public property_ `public SynchronizationContext SynchronizationContext { get; }`
- L23 _public property_ `public WorkspaceLock Lock { get; }`
- L24 _private* field_ `readonly ILogger _logger`
- L26 _private* property_ `bool Syncing => ...`
- L28 _private* field_ `WorkspaceUpdate? _currentUpdate`
- L30 _public event_ `public event Action<WorkspaceUpdateContext, WorkspaceUpdateResult, string>? OnUpdateComplete`
- L30 _public event_ `public event Action<WorkspaceUpdateResult`
- L30 _public event_ `public event Action<string>? OnUpdateComplete`
- L32 _public event_ `public event Action<ReadOnlyWorkspaceState>? OnStateChanged`
- L34 _private* field_ `readonly IAsyncDisposer _asyncDisposer`
- L36-53 _public ctor_ `public Workspace(IPerforceSettings perforceSettings, ProjectInfo project, WorkspaceStateWrapper stateWrapper, ConfigFile projectConfigFile, IReadOnlyList<string>? projectStreamFilter, ILogger logger, IServiceProvider serviceProvider)`
- L55 _public method_ `public bool IsExternalSyncActive()`
- L57-64 _public method_ `public void ModifyState(Action<WorkspaceState> action)`
- L66-69 _private method_ `private void OnLockChangedInternal(bool locked)`
- L71-74 _private method_ `private void OnLockChangedInternalMainThread(object? obj)`
- L76-79 _private method_ `private void OnStateChangedInternal(ReadOnlyWorkspaceState state)`
- L81-85 _private method_ `private void OnStateChangedInternalMainThread(ReadOnlyWorkspaceState state)`
- L87-99 _public method_ `public void Dispose()`
- L101-105 _private* method_ `void FinishDispose()`
- L107-110 _public property_ `public ConfigFile ProjectConfigFile { get; set; }`
- L112-115 _public property_ `public IReadOnlyList<string>? ProjectStreamFilter { get; set; }`
- L118 _private* field_ `CancellationTokenSource? _prevCancellationSource`
- L120 _private* field_ `Task _prevUpdateTask = Task.CompletedTask`
- L122-134 _public method_ `public void Update(WorkspaceUpdateContext context)`
- L136-151 _public method_ `public void CancelUpdate()`
- L153-202 _private* method_ `async Task UpdateWorkspaceMini(WorkspaceUpdate update, Task prevUpdateTask, CancellationToken cancellationToken)`
- L204-228 _private* method_ `void CompleteUpdate(WorkspaceUpdate update, WorkspaceUpdateResult result, string statusMessage)`
- L230-242 _public method_ `public Dictionary<string, string> GetVariables(BuildConfig editorConfig, int? overrideChange = null, int? overrideCodeChange = null)`
- L244-247 _public method_ `public bool IsBusy()`
- L249 _public property_ `public int CurrentChangeNumber => ...`
- L251 _public property_ `public int PendingChangeNumber => ...`
- L253 _public property_ `public string ClientName => ...`
- L255 _public property_ `public Tuple<string, float> CurrentProgress => ...`
