# CSharp / ImageValidator

- project root: `Source/Programs/ImageValidator`
- files: 11; symbols: 188
- symbol kinds: class=12, ctor=7, field=81, method=77, property=6, struct=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/ImageValidator/Form1.Designer.cs` (ImageValidator)


#### class `ImageValidator.Form1`  
`partial class Form1`  
_internal*; L3-510_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-467 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L471 _private field_ `private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1`
- L472 _private field_ `private System.Windows.Forms.ImageList imageListThumbnails`
- L473 _private field_ `private System.Windows.Forms.ListView listView1`
- L474 _private field_ `private System.Windows.Forms.TextBox textBoxRefDir`
- L475 _private field_ `private System.Windows.Forms.Label label1`
- L476 _private field_ `private System.Windows.Forms.OpenFileDialog openFileDialog1`
- L477 _private field_ `private System.Windows.Forms.PictureBox pictureBoxTest`
- L478 _private field_ `private System.Windows.Forms.PictureBox pictureBoxDiff`
- L479 _private field_ `private System.Windows.Forms.PictureBox pictureBoxRef`
- L480 _private field_ `private System.Windows.Forms.Label label2`
- L481 _private field_ `private System.Windows.Forms.Label label3`
- L482 _private field_ `private NumericTextBox textBoxThreshold`
- L483 _private field_ `private NumericTextBox textBoxCountToFail`
- L484 _private field_ `private System.Windows.Forms.Timer timer1`
- L485 _private field_ `private System.IO.FileSystemWatcher fileSystemWatcher1`
- L486 _private field_ `private System.IO.FileSystemWatcher fileSystemWatcher2`
- L487 _private field_ `private System.Windows.Forms.MenuStrip menuStrip1`
- L488 _private field_ `private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem`
- L489 _private field_ `private System.Windows.Forms.ToolStripMenuItem newToolStripMenuNew`
- L490 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator2`
- L491 _private field_ `private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuSave`
- L492 _private field_ `private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuSaveAs`
- L493 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator1`
- L494 _private field_ `private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuQuit`
- L495 _private field_ `private System.Windows.Forms.TextBox textBoxTestDir`
- L496 _private field_ `private System.Windows.Forms.Button buttonPickTestFolder`
- L497 _private field_ `private System.Windows.Forms.Label label4`
- L498 _private field_ `private System.Windows.Forms.SaveFileDialog saveFileDialog1`
- L499 _private field_ `private System.Windows.Forms.Button buttonPickRefFolder`
- L500 _private field_ `private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem`
- L501 _private field_ `private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem`
- L502 _private field_ `private System.Windows.Forms.ToolStripMenuItem howToUseWithUnrealEngineToolStripMenuItem`
- L503 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator3`
- L504 _private field_ `private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem`
- L505 _private field_ `private System.Windows.Forms.ToolStripMenuItem actionToolStripMenuItem`
- L506 _private field_ `private System.Windows.Forms.ToolStripMenuItem MenuItemGenerateHTMLReport`
- L507 _private field_ `private System.Windows.Forms.SaveFileDialog saveFileDialogExport`
- L508 _private field_ `private System.Windows.Forms.ToolStripMenuItem generateHTMLReportWithThumbnailsToolStripMenuItem`
- L509 _private field_ `private System.Windows.Forms.Button buttonRefresh`

### `Source/Programs/ImageValidator/Form1.cs` (ImageValidator)


#### class `ImageValidator.Form1`  
`public partial class Form1 : Form, IMessageFilter`  
_public; L22-915_
- inherits: `Form, IMessageFilter`
- L25 _private* field_ `ImageValidatorData data`
- L27 _private* field_ `ImageValidatorIntermediate intermediate`
- L30 _private field_ `private ColumnHeader SortingColumn = null`
- L33 _private field_ `private int MouseStartTrackOffsetX`
- L34 _private field_ `private int MouseStartTrackOffsetY`
- L36 _private field_ `private float ImageOffsetX`
- L37 _private field_ `private float ImageOffsetY`
- L39 _private field_ `private int ImageZoom`
- L46-60 _public method_ `public bool PreFilterMessage(ref Message m)`
- L63 _private method_ `private static extern IntPtr WindowFromPoint(Point pt)` — attrs: `[DllImport("user32.dll")]`
- L65 _private method_ `private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp)` — attrs: `[DllImport("user32.dll")]`
- L69-75 _public ctor_ `public Form1()`
- L77-91 _public method_ `public void PopulateList()`
- L93-133 _private method_ `private void Form1_Load(object sender, EventArgs e)`
- L135-147 _private method_ `private int FindListViewIndexFromImageIndex(int ImageIndex)`
- L149-159 _private method_ `private void buttonPickRefFolder_Click(object sender, EventArgs e)`
- L161-171 _private method_ `private void buttonPickTestFolder_Click(object sender, EventArgs e)`
- L173-181 _private method_ `private void textBoxTestDir_KeyDown(object sender, KeyEventArgs e)`
- L183-191 _private method_ `private void textBoxRefDir_KeyDown(object sender, KeyEventArgs e)`
- L193-239 _private method_ `private void UpdateListView()`
- L242-247 _private method_ `private int GetSelectedListViewIndex()`
- L250-255 _private method_ `private int GetSelectedImageEntryIndex()`
- L257-295 _private method_ `private ImageValidatorSettings GetSettings()`
- L297-303 _private method_ `private void SetSettings(ImageValidatorSettings settings)`
- L305-315 _private method_ `private void UpdateImages(int ImageEntryIndex)`
- L317-321 _private method_ `private void listView1_Click(object sender, EventArgs e)`
- L323-335 _private method_ `private float ComputeScale()`
- L337-354 _private method_ `private void DrawOutlinedString(Graphics g, int x, int y, string drawString, Font drawFont)`
- L356-382 _private method_ `private void PaintImage(Bitmap image, object sender, PaintEventArgs e, string drawString)`
- L384-387 _private method_ `private void pictureBoxTest_Paint(object sender, PaintEventArgs e)`
- L389-392 _private method_ `private void pictureBoxDiff_Paint(object sender, PaintEventArgs e)`
- L394-397 _private method_ `private void pictureBoxRef_Paint(object sender, PaintEventArgs e)`
- L399-443 _private method_ `private void Form1_Resize(object sender, EventArgs e)`
- L445-448 _private method_ `private void textBoxCountToFail_TextChanged(object sender, EventArgs e)`
- L450-454 _private method_ `private void textBoxThreshold_TextChanged(object sender, EventArgs e)`
- L456-464 _private method_ `private void ClearListViewSorting()`
- L466-476 _private method_ `private void SetListViewSorting(int ColumnIndex)`
- L478-534 _private method_ `private void listView1_ColumnClick(object sender, ColumnClickEventArgs e)`
- L536-542 _private method_ `private void timer1_Tick(object sender, EventArgs e)`
- L544-569 _private method_ `private void SetupFileSystemWatcher()`
- L572-595 _public method_ `public static bool IsFileReady(String sFilename)`
- L597-611 _private method_ `private void fileSystemWatcher1_Changed(object sender, FileSystemEventArgs e)`
- L613-618 _private method_ `private void fileSystemWatcher1_Renamed(object sender, RenamedEventArgs e)`
- L620-694 _private method_ `private void pictureBoxTest_MouseMove(object sender, MouseEventArgs e)`
- L696-707 _private method_ `private void newToolStripMenuNew_Click(object sender, EventArgs e)`
- L709-729 _private method_ `private bool SaveSettings(string FileName)`
- L732-735 _private method_ `private string GetFileName()`
- L738-743 _private method_ `private void SetFileName(string FileName)`
- L745-775 _private method_ `private bool LoadSettings(string FileName)`
- L777-784 _private method_ `private void saveToolStripMenuSave_Click(object sender, EventArgs e)`
- L786-792 _private method_ `private void saveAsToolStripMenuSaveAs_Click(object sender, EventArgs e)`
- L794-802 _private method_ `private void quitToolStripMenuQuit_Click(object sender, EventArgs e)`
- L804-810 _private method_ `private void openToolStripMenuItem_Click(object sender, EventArgs e)`
- L812-816 _private method_ `private void howToUseWithUnrealEngineToolStripMenuItem_Click(object sender, EventArgs e)`
- L832-839 _private method_ `private void WaitUntilTestIsDone(ref ImageValidatorData data, ref ImageValidatorSettings settings)`
- L841-899 _private method_ `private void GenerateHTMLReport(bool bThumbnails)`
- L901-904 _private method_ `private void MenuItemGenerateHTMLReport_Click(object sender, EventArgs e)`
- L906-909 _private method_ `private void MenuItemGenerateHTMLReportWithT_Click(object sender, EventArgs e)`
- L911-914 _private method_ `private void Refresh_Click(object sender, EventArgs e)`

### `Source/Programs/ImageValidator/HTMLFragment.cs` (ImageValidator)


#### class `ImageValidator.HtmlFragment`  
`class HtmlFragment`  
_internal*; L43-135_
- L50-53 _private* method_ `static string To8DigitString(int x)`
- L63-66 _public method_ `public static void CopyToClipboard(string htmlFragment)` — Clears clipboard and copy a HTML fragment to the clipboard. This generates the header.
- L75-131 _public method_ `public static void CopyToClipboard(string htmlFragment, string title, Uri sourceUrl)` — Clears clipboard and copy a HTML fragment to the clipboard, providing additional meta-information.

### `Source/Programs/ImageValidator/ImageValidatorData.cs` (ImageValidator)


#### class `ImageValidator.ImageValidatorSettings`  
`public class ImageValidatorSettings`  
_public; L16-33_
- L18 _public field_ `public string TestDir`
- L19 _public field_ `public string RefDir`
- L20 _public field_ `public uint Threshold`
- L21 _public field_ `public uint PixelCountToFail`
- L23-27 _public ctor_ `public ImageValidatorSettings()`
- L29-32 _public method_ `public static string GetVersionString()`

#### struct `ImageValidator.ImageValidatorIntermediate`  
`public struct ImageValidatorIntermediate`  
_public; L35-272_
- L91 _public field_ `public Bitmap imageTest`
- L92 _public field_ `public Bitmap imageDiff`
- L93 _public field_ `public Bitmap imageRef`
- L95-122 _private method_ `private Bitmap LoadBitmap(string filename)`
- L124-133 _public method_ `public void Process(ImageValidatorSettings settings, ImageValidatorData.ImageEntry imageEntry)`
- L135-150 _public method_ `public static System.Drawing.Size GetImageSize(Bitmap bitmap)`
- L152-161 _public method_ `public System.Drawing.Size GetImagesSize()`
- L163-182 _public method_ `public static Bitmap resizeImage(Image image)`
- L185-271 _public method_ `public TestResult ComputeDiff(uint Threshold)`

#### struct `ImageValidator.ImageValidatorIntermediate.PixelElement`  
`public struct PixelElement`  
_public; L37-89_
- L40 _public field_ `public byte b, g, r, a`
- L40 _public field_ `public byte g`
- L40 _public field_ `public byte r`
- L40 _public field_ `public byte a`
- L42-53 _public method_ `public void SetErrorColor(float squaredError)`
- L73-80 _public method_ `public static float ComputeSquaredError(PixelElement Test, PixelElement Ref)`
- L81-88 _public method_ `public static uint ComputeAbsDiff(PixelElement Test, PixelElement Ref)`

#### class `ImageValidator.TestResult`  
`public class TestResult`  
_public; L274-315_
- L276-279 _public method_ `public static Color GetColor(bool bPassed)`
- L281-284 _public method_ `public Color GetColor(ref ImageValidatorSettings settings)`
- L286-289 _public method_ `public bool IsPassed(ref ImageValidatorSettings settings)`
- L291-305 _public method_ `public string GetString(ref ImageValidatorSettings settings)`
- L308 _public field_ `public string ErrorText`
- L310 _public field_ `public uint ErrorPixels`
- L312 _public field_ `public Bitmap ThumbnailTest`
- L313 _public field_ `public Bitmap ThumbnailDiff`
- L314 _public field_ `public Bitmap ThumbnailRef`

#### struct `ImageValidator.ImageValidatorData`  
`public struct ImageValidatorData`  
_public; L317-496_
- L421 _public field_ `public List<ImageEntry> imageEntries`
- L423-471 _private method_ `private void PopulatePartList(bool bRef, string path)`
- L474-487 _public method_ `public bool ProcessOneElement(ImageValidatorSettings settings)`
- L489-495 _public method_ `public void PopulateList(string TestDir, string RefDir)`

#### struct `ImageValidator.ImageValidatorData.ImageEntryColumnData`  
`public struct ImageEntryColumnData`  
_public; L319-370_
- L321 _public field_ `public string Platform`
- L322 _public field_ `public string Map`
- L323 _public field_ `public string Time`
- L324 _public field_ `public string Actor`
- L326-369 _public ctor_ `public ImageEntryColumnData(string Name)`

#### class `ImageValidator.ImageValidatorData.ImageEntry`  
`public class ImageEntry : IComparable`  
_public; L372-416_
- inherits: `IComparable`
- L374-378 _public ctor_ `public ImageEntry()`
- L381 _public field_ `public string Name`
- L383 _public field_ `public bool bRefExists`
- L385 _public field_ `public bool bTestExists`
- L387 _public field_ `public TestResult testResult`
- L389-415 _public method_ `public int CompareTo(object _rhs)`

### `Source/Programs/ImageValidator/ListViewComparer.cs` (ImageValidator)


#### class `ImageValidator.ListViewComparer`  
`public class ListViewComparer : System.Collections.IComparer`  
_public; L14-90_
- inherits: `System.Collections.IComparer`
- L16 _private field_ `private int ColumnNumber`
- L17 _private field_ `private SortOrder SortOrder`
- L19-24 _public ctor_ `public ListViewComparer(int column_number, SortOrder sort_order)`
- L27-89 _public method_ `public int Compare(object object_x, object object_y)`

### `Source/Programs/ImageValidator/NumericTextBox.cs` (ImageValidator)


#### class `ImageValidator.NumericTextBox`  
`class NumericTextBox : TextBox`  
_internal*; L15-95_
- inherits: `TextBox`
- L17 _private* field_ `bool allowSpace = false`
- L21-65 _protected method_ `protected override void OnKeyPress(KeyPressEventArgs e)`
- L67-73 _public property_ `public int IntValue { get; }`
- L75-81 _public property_ `public decimal DecimalValue { get; }`
- L83-94 _public property_ `public bool AllowSpace { set; get; }`

### `Source/Programs/ImageValidator/Program.cs` (ImageValidator)


#### class `ImageValidator.Program`  
`static class Program`  
_internal*; L11-23_
- L17-22 _private* method_ `static void Main()` — attrs: `[STAThread]` — The main entry point for the application.

### `Source/Programs/ImageValidator/Properties/AssemblyInfo.cs` (ImageValidator)
_(no declarations)_


### `Source/Programs/ImageValidator/Properties/Resources.Designer.cs` (ImageValidator)


#### class `ImageValidator.Properties.Resources`  
`internal class Resources`  
_internal; L25-62_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/ImageValidator/Properties/Settings.Designer.cs` (ImageValidator)


#### class `ImageValidator.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L17-29_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "11.0.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L20 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L22-28 _public property_ `public static Settings Default { get; }`

### `Source/Programs/ImageValidator/ReportGenerator.cs` (ImageValidator)


#### class `ImageValidator.ReportGenerator`  
`class ReportGenerator`  
_internal*; L16-307_
- L44-306 _public method_ `public void ExportHTML(string SettingsFileName, ref ImageValidatorData data, ref ImageValidatorSettings settings, string FileName, bool bSilent, bool bThumbnails)`

#### struct `ImageValidator.ReportGenerator.ValidationSummary`  
`private struct ValidationSummary`  
_private; L18-42_
- L20 _public field_ `public uint Failed`
- L21 _public field_ `public uint Succeeded`
- L23-41 _public ctor_ `public ValidationSummary(ref ImageValidatorData data, ref ImageValidatorSettings settings)`
