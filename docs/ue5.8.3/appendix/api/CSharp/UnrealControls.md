# CSharp / UnrealControls

- project root: `Source/Programs/UnrealControls`
- files: 26; symbols: 451
- symbol kinds: class=27, const=9, ctor=25, delegate=2, enum=1, enumerator=6, event=7, field=108, indexer=4, method=189, operator=8, property=59, struct=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealControls/ColorPair.cs` (UnrealControls)


#### struct `UnrealControls.ColorPair`  
`public struct ColorPair`  
_public; L13-34_
- desc: A pair of colors.
- L18 _public field_ `public Color? BackColor` — The foreground color.
- L22 _public field_ `public Color? ForeColor` — The background color
- L29-33 _public ctor_ `public ColorPair(Color? BackColor, Color? ForeColor)` — Constructor.

### `Source/Programs/UnrealControls/ColoredDocumentLineSegment.cs` (UnrealControls)


#### struct `UnrealControls.ColoredDocumentLineSegment`  
`public struct ColoredDocumentLineSegment`  
_public; L13-49_
- desc: Represents a segment of colored text within a document.
- L15 _private* field_ `ColorPair mColor`
- L16 _private* field_ `string mText`
- L21-24 _public property_ `public ColorPair Color { get; }` — Gets the color of the text.
- L29-32 _public property_ `public string Text { get; }` — Gets the text associated with the segment.
- L39-48 _public ctor_ `public ColoredDocumentLineSegment(ColorPair Colors, string Text)` — Constructor.

### `Source/Programs/UnrealControls/ColoredTextRange.cs` (UnrealControls)


#### class `UnrealControls.ColoredTextRange`  
`public class ColoredTextRange`  
_public; L13-44_
- desc: Represents a range of colored characters within a line of a document.
- L15 _public field_ `public Color? ForeColor`
- L16 _public field_ `public Color? BackColor`
- L17 _public field_ `public int StartIndex`
- L18 _public field_ `public int Length`
- L27-43 _public ctor_ `public ColoredTextRange(Color? TxtForeColor, Color? TxtBackColor, int StartIndex, int Length)` — Constructor.

### `Source/Programs/UnrealControls/DynamicTabControl.cs` (UnrealControls)


#### class `UnrealControls.DynamicTabControl`  
`public partial class DynamicTabControl : UserControl`  
_public; L22-783_
- inherits: `UserControl`
- desc: VS.NET style tab control.
- L214 _private* const_ `const int SLIDEWIDTH = 24`
- L215 _private* const_ `const int TABHEIGHT = 17`
- L216 _private* const_ `const int CURVEOFFSETY = 15`
- L217 _private* const_ `const int CURVEOFFSETX = 15`
- L218 _private* const_ `const int BOXHEIGHT = 15`
- L219 _private* const_ `const int BOXWIDTH = 16`
- L220 _private* const_ `const int ARROWLEFTOFFSET = 40`
- L222 _private* field_ `DynamicTabPageCollection mTabPages`
- L223 _private* field_ `XButton mXButton = new XButton()`
- L224 _private* field_ `MenuArrow mMnuArrow = new MenuArrow()`
- L225 _private* field_ `ContextMenuStrip mCtxMenu = new ContextMenuStrip()`
- L226 _private* field_ `Font mBoldFont`
- L227 _private* field_ `int mSelectedTab`
- L228 _private* field_ `EventHandler<EventArgs> mSelectedIndexChanged`
- L233-237 _public event_ `public event EventHandler<EventArgs> SelectedIndexChanged { add; remove; }` — Event for when the selected tab has changed.
- L242-245 _public property_ `public DynamicTabPageCollection TabPages { get; }` — Gets the collection of tab pages.
- L250-254 _public property_ `public int SelectedIndex { get; set; }` — Gets/Sets the index of the currently selected tab.
- L259-274 _public property_ `public DynamicTabPage SelectedTab { get; set; }` — Gets/Sets the currently selected tab.
- L279-294 _public ctor_ `public DynamicTabControl()` — Constructor.
- L301-319 _private* method_ `void MnuArrow_Click(object sender, EventArgs e)` — Called when the tab selection arrow has been clicked.
- L326-334 _private* method_ `void CtxMenuHandler(object sender, EventArgs e)` — The context menu for the tab selection arrow.
- L341-344 _private* method_ `void XButton_Click(object sender, EventArgs e)` — Called when the X button has been clicked to close a tab.
- L350-390 _protected method_ `protected override void OnPaint(PaintEventArgs e)` — Called to paint the tab control.
- L402-435 _private method_ `private void DrawTab(int offX, SizeF size, Graphics graphics, string text, StringFormat fmt, bool clip, bool selectedTab, DynamicTabPage tabPage)` — Called to draw a tab.
- L441-466 _private* method_ `void OnTabPageAdded(int index)` — Called when a tab page has been added.
- L473-476 _private* method_ `void DynamicTabControl_TextChanged(object sender, EventArgs e)` — Called when the text of a tab page has changed.
- L482-571 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)` — Called when a mouse button has been pressed.
- L581-614 _private method_ `private bool PointInTriangle(PointF i, PointF p0, PointF p1, PointF p2)` — Returns true if the specified point is within the specified triangle.
- L620-653 _private method_ `private void SelectTab(int i)` — Selects the tab at the specified index.
- L660-685 _public method_ `public bool TabInView(int index)` — Returns true if the tab at the specified index is in view.
- L691-697 _protected method_ `protected override void OnControlAdded(ControlEventArgs e)` — Called when a control has been added to the tab page.
- L703-717 _protected method_ `protected override void OnResize(EventArgs e)` — Called when the tab control has been resized.
- L722-726 _private* method_ `void UpdateMenuItemPositions()` — Updates the arrow button and X button positions.
- L733-769 _internal method_ `internal void OnTabPageRemoved(int index, DynamicTabPage page)` — Called when a tab page has been removed.
- L776-782 _protected method_ `protected virtual void OnSelectedIndexChanged(object sender, EventArgs e)` — Called when the index of the selected tab page has changed.

#### class `UnrealControls.DynamicTabControl.DynamicTabPageCollection`  
`public class DynamicTabPageCollection : IList<DynamicTabPage>, ICollection<DynamicTabPage>, IEnumerable<DynamicTabPage>`  
_public; L27-212_
- inherits: `IList<DynamicTabPage>, ICollection<DynamicTabPage>, IEnumerable<DynamicTabPage>`
- desc: Collection of tab pages.
- L29 _private* field_ `DynamicTabControl m_owner`
- L30 _private* field_ `List<DynamicTabPage> m_pages = new List<DynamicTabPage>()`
- L36-44 _public ctor_ `public DynamicTabPageCollection(DynamicTabControl owner)` — Constructor.
- L53-56 _public method_ `public int IndexOf(DynamicTabPage item)` — Returns the index of the specified item.
- L63-75 _public method_ `public void Insert(int index, DynamicTabPage item)` — Inserts a new item into the collection.
- L81-89 _public method_ `public void RemoveAt(int index)` — Removes the item at the specified index.
- L96-106 _public indexer_ `public DynamicTabPage this[int index] { get; set; }` — Overloaded [] operator.
- L116-120 _public method_ `public void Add(DynamicTabPage item)` — Adds a tab page to the collection.
- L125-128 _public method_ `public void Clear()` — Clears the collection.
- L135-138 _public method_ `public bool Contains(DynamicTabPage item)` — Returns true if the specified item exists in the collection.
- L145-148 _public method_ `public void CopyTo(DynamicTabPage[] array, int arrayIndex)` — Copies the collection into an array.
- L153-156 _public property_ `public int Count { get; }` — The number of items in the collection.
- L161-164 _public property_ `public bool IsReadOnly { get; }` — Returns false.
- L171-183 _public method_ `public bool Remove(DynamicTabPage item)` — Removes the specified item from the collection.
- L193-196 _public method_ `public IEnumerator<DynamicTabPage> GetEnumerator()` — Gets an enumerator.
- L206-209 _private* method_ `System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()` — Gets an enumerator.

### `Source/Programs/UnrealControls/DynamicTabControl.designer.cs` (UnrealControls)


#### class `UnrealControls.DynamicTabControl`  
`partial class DynamicTabControl`  
_internal*; L5-46_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-43 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.

### `Source/Programs/UnrealControls/DynamicTabControlMenuItem.cs` (UnrealControls)


#### class `UnrealControls.DynamicTabControlMenuItem`  
`public class DynamicTabControlMenuItem : ToolStripMenuItem`  
_public; L14-51_
- inherits: `ToolStripMenuItem`
- desc: A tab control menu item.
- L16 _private* field_ `int m_index`
- L21-24 _public property_ `public int TabPageIndex { get; }` — The index of the tab control.
- L31-36 _public ctor_ `public DynamicTabControlMenuItem(string text, int index)` — Constructor.
- L44-50 _public ctor_ `public DynamicTabControlMenuItem(string text, int index, EventHandler handler)` — Constructor.

### `Source/Programs/UnrealControls/DynamicTabPage.cs` (UnrealControls)


#### class `UnrealControls.DynamicTabPage`  
`public class DynamicTabPage : UserControl`  
_public; L15-153_
- inherits: `UserControl`
- desc: A VS.NET style tab page.
- L17 _private* field_ `Brush mTabForeColorBrush = SystemBrushes.ControlText`
- L18 _private* field_ `Brush mTabBackgroundColorBrush = SystemBrushes.Window`
- L19 _private* field_ `EventHandler<EventArgs> mTabSelected`
- L20 _private* field_ `EventHandler<EventArgs> mTabDeselected`
- L25-29 _public event_ `public event EventHandler<EventArgs> TabSelected { add; remove; }` — Event for when the tab has been selected.
- L34-38 _public event_ `public event EventHandler<EventArgs> TabDeselected { add; remove; }` — Event for when the tab has been deselected.
- L43-58 _public property_ `public Brush TabForegroundColor { get; set; }` — Gets/Sets the foreground color for this tab pages tab.
- L63-78 _public property_ `public Brush TabBackgroundColor { get; set; }` — Gets/Sets the background color for this tab pages tab.
- L84-94 _public property_ `public override DockStyle Dock { get; set; }` — attrs: `[Browsable(false)]` — The dock style of the tab.
- L99-102 _public ctor_ `public DynamicTabPage()` — Constructor.
- L108-112 _public ctor_ `public DynamicTabPage(string text)` — Constructor.
- L118-124 _protected method_ `protected virtual void OnTabSelected(EventArgs e)` — Called when the tab has been selected.
- L130-136 _protected method_ `protected virtual void OnTabDeselected(EventArgs e)` — Called when the tab has been deselected.
- L141-144 _internal method_ `internal void SelectTab()` — Called to select a tab.
- L149-152 _internal method_ `internal void DeselectTab()` — Deselects the tab.

### `Source/Programs/UnrealControls/EngineVersioning.cs` (UnrealControls)


#### class `UnrealControls.EngineVersioning`  
`public class EngineVersioning`  
_public; L12-75_
- L14 _public field_ `public DateTime TimeStamp = DateTime.MinValue`
- L15 _public field_ `public int EngineVersion = -1`
- L16 _public field_ `public int Changelist = -1`
- L17 _public field_ `public List<string> SpecialDefines = new List<string>()`
- L19-74 _public ctor_ `public EngineVersioning()`

### `Source/Programs/UnrealControls/FindResult.cs` (UnrealControls)


#### struct `UnrealControls.FindResult`  
`public struct FindResult`  
_public; L9-48_
- L11 _public field_ `public static readonly FindResult Empty = new FindResult(-1, -1, 0)`
- L13 _public field_ `public int Line`
- L14 _public field_ `public int Column`
- L15 _public field_ `public int Length`
- L17-22 _public ctor_ `public FindResult(int Line, int Column, int Length)`
- L24-32 _public method_ `public override bool Equals(object obj)`
- L34-37 _public method_ `public override int GetHashCode()`
- L39-42 _public operator_ `public static bool operator ==(FindResult Left, FindResult Right)`
- L44-47 _public operator_ `public static bool operator !=(FindResult Left, FindResult Right)`

### `Source/Programs/UnrealControls/GameLocator.cs` (UnrealControls)


#### class `UnrealControls.GameLocator`  
`static public class GameLocator`  
_public; L15-70_
- L17-58 _public method_ `static public List<string> LocateGames( string BranchRoot )`
- L60-69 _public method_ `static public List<string> LocateGames()`

#### class `UnrealControls.LanguageLocator`  
`static public class LanguageLocator`  
_public; L72-90_
- L74-89 _public method_ `static public List<string> LocateLanguages( string Game )`

#### class `UnrealControls.DefaultTargetDirectory`  
`static public class DefaultTargetDirectory`  
_public; L92-122_
- L94-121 _public method_ `static public string GetDefaultTargetDirectory()`

#### class `UnrealControls.XmlHandler`  
`static public class XmlHandler`  
_public; L124-208_
- L126-128 _private method_ `static private void XmlSerializer_UnknownAttribute( object sender, XmlAttributeEventArgs e )`
- L130-132 _private method_ `static private void XmlSerializer_UnknownNode( object sender, XmlNodeEventArgs e )`
- L134-166 _public method_ `static public T ReadXml<T>( string FileName ) where T : new()`
- L168-207 _public method_ `static public bool WriteXml<T>( T Data, string FileName, string DefaultNameSpace )`

#### class `UnrealControls.ProcessHandler`  
`static public class ProcessHandler`  
_public; L210-277_
- L213 _public delegate_ `public delegate void CaptureMessageDelegate( string Message )`
- L214 _private* field_ `static CaptureMessageDelegate CaptureOutput = null`
- L216-219 _public method_ `static public void CaptureOutputCallback( object Sender, DataReceivedEventArgs e )`
- L221-276 _public method_ `static public int SpawnProcessAndWait( string Executable, string CWD, CaptureMessageDelegate CaptureOutputInstance, params string[] Parameters )`

### `Source/Programs/UnrealControls/MenuArrow.cs` (UnrealControls)


#### class `UnrealControls.MenuArrow`  
`public partial class MenuArrow : UserControl`  
_public; L20-129_
- inherits: `UserControl`
- desc: The arrow button on a VS.NET style tab control.
- L22 _private* field_ `ProfessionalColorTable mColorTable = new ProfessionalColorTable()`
- L23 _private* field_ `bool mDrawLine = false`
- L24 _private* field_ `bool mMouseOver = false`
- L29-40 _public property_ `public bool DrawLine { get; set; }` — Gets/Sets whether or not to draw a line above the arrow.
- L45-48 _public property_ `public bool MouseOver { get; }` — Gets whether or not the mouse is currently over the control.
- L53-56 _public ctor_ `public MenuArrow()` — Constructor.
- L62-94 _protected method_ `protected override void OnPaint(PaintEventArgs e)` — Called to draw the control.
- L100-106 _protected method_ `protected override void OnMouseEnter(EventArgs e)` — Called when the mouse enters the control.
- L112-118 _protected method_ `protected override void OnMouseLeave(EventArgs e)` — Called when the mouse leaves the control.

### `Source/Programs/UnrealControls/MenuArrow.designer.cs` (UnrealControls)


#### class `UnrealControls.MenuArrow`  
`partial class MenuArrow`  
_internal*; L5-38_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-35 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.

### `Source/Programs/UnrealControls/OutputWindowDocument.cs` (UnrealControls)


#### class `UnrealControls.OutputWindowDocument`  
`public class OutputWindowDocument`  
_public; L23-1170_
- desc: A document that can be viewed by multiple OutputWindowView's.
- L480 _private* field_ `List<DocumentLine> mLines = new List<DocumentLine>()`
- L481 _private* field_ `int mLongestLineLength`
- L483 _private* field_ `EventHandler<OutputWindowDocumentLineAddedEventArgs> mOnLineAdded`
- L484 _private* field_ `EventHandler<EventArgs> mOnModified`
- L489-493 _public event_ `public event EventHandler<OutputWindowDocumentLineAddedEventArgs> LineAdded { add; remove; }` — Triggered when a full line of text has been added to the document.
- L498-502 _public event_ `public event EventHandler<EventArgs> Modified { add; remove; }` — Triggered when the document has been modified.
- L507-531 _public property_ `public string Text { set; get; }` — Gets/Sets the text in the document.
- L536-549 _public property_ `public string[] Lines { get; }` — Gets the lines associated with the document.
- L554-557 _public property_ `public int LineCount { get; }` — Gets the number of lines in the document.
- L562-565 _public property_ `public int LongestLineLength { get; }` — Gets the length in characters of the longest line in the document.
- L570-573 _public property_ `public TextLocation BeginningOfDocument { get; }` — Gets the TextLocation of the beginning of the document.
- L578-585 _public property_ `public TextLocation EndOfDocument { get; }` — Gets the TextLocation of the end of the document.
- L590-594 _public ctor_ `public OutputWindowDocument()` — Constructor.
- L601-695 _public method_ `public void AppendText(Color? TxtColor, string Txt)` — Appends text of the specified color to the document.
- L702-705 _public method_ `public void AppendLine(Color? TxtColor, string Txt)` — Appends a line of colored text to the document.
- L713-723 _public method_ `public string GetLine(int Index, bool bIncludeEOL)` — Retrieves a line of text from the document.
- L732-735 _public method_ `public string GetLine(int LineIndex, int CharOffset, int Length)` — Retrieves a line of text from the document.
- L742-750 _public method_ `public int GetLineLength(int Index)` — Gets the length of the line in characters at the specified index.
- L757-767 _private method_ `private static int GetLineLength(DocumentLine Line)` — Gets the length of the line in characters.
- L772-778 _public method_ `public void Clear()` — Clears the document.
- L789-799 _public method_ `public bool Find(string Txt, TextLocation StartLoc, TextLocation EndLoc, RichTextBoxFinds Flags, out FindResult Result)` — Finds the first occurence of the specified string within the document if it exists.
- L810-854 _private method_ `private bool FindForward(string Txt, ref TextLocation StartLoc, ref TextLocation EndLoc, RichTextBoxFinds Flags, out FindResult Result)` — Looks forward in the document from the specified location for the supplied text.
- L868-891 _private method_ `private static void CheckForWholeWord(string Txt, ref FindResult Result, bool bMatchWord, ref bool bFound, bool bIsWord, int CurLineIndex, DocumentLine CurLine, int ColumnIndex, int Index)` — Checks to see if a text location is a matching word.
- L898-901 _private method_ `private static bool IsWordCharacter(char CharToCheck)` — Checks to see if a character is valid within a word.
- L914-951 _private method_ `private void SetupFindState(string Txt, ref TextLocation StartLoc, ref TextLocation EndLoc, RichTextBoxFinds Flags, out FindResult Result, out bool bIsWord, out StringComparison ComparisonFlags, out bool bMatchWord)` — Performs general housekeeping for setting up a search.
- L959-972 _private method_ `private static bool IsWord(int Index, string Txt)` — Checks a string to see if it contains a valid word.
- L983-1027 _private method_ `private bool FindReverse(string Txt, ref TextLocation StartLoc, ref TextLocation EndLoc, RichTextBoxFinds Flags, out FindResult Result)` — Searches for a string in the reverse direction of FindForward.
- L1033-1042 _public method_ `public void SaveToFile(string Name)` — Saves the document to disk.
- L1049-1059 _public method_ `public bool IsValidTextLocation(TextLocation Loc)` — Determines whether a location within the document is valid.
- L1066-1069 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments(int LineIndex)` — Gets an array of line segments for the line at the specified index.
- L1078-1081 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments(int LineIndex, int StartIndex, int Length)` — Gets an array of line segments for the line at the specified index.
- L1097-1100 _public method_ `public ColoredDocumentLineSegment[] GetLineSegmentsWithFindString(int LineIndex, int StartIndex, int Length, string FindText, ColorPair InsertionColors, StringComparison ComparisonType, out bool bHasFindText)` — Gets an array of colored line segments that can be used for drawing.
- L1106-1112 _protected method_ `protected virtual void OnLineAdded(OutputWindowDocumentLineAddedEventArgs e)` — Event handler for when a full line of text has been added to the document.
- L1118-1124 _protected method_ `protected virtual void OnModified(EventArgs e)` — Event handler for when the document has been modified.
- L1132-1169 _public method_ `public OutputWindowDocument CreateFilteredDocument(OutputWindowDocumentFilterDelegate Filter, object Data)` — Creates a new document by filtering out the lines of the current document using the supplied filter function.

#### class `UnrealControls.OutputWindowDocument.DocumentLine`  
`internal class DocumentLine : ICloneable`  
_internal; L28-395_
- inherits: `ICloneable`
- desc: Represents a line of colored text within a document.
- L31 _private* field_ `StringBuilder mBldrText = new StringBuilder()`
- L32 _private* field_ `string mFinalText`
- L33 _private* field_ `List<ColoredTextRange> mColorRanges = new List<ColoredTextRange>()`
- L34 _private* field_ `ICloneable mUserData`
- L39-42 _public property_ `public int Length { get; }` — Gets the length of the line in characters.
- L49-52 _public indexer_ `public char this[int Index] { get; }` — Gets the character at the specified index.
- L57-61 _public property_ `public ICloneable UserData { get; set; }` — Gets/Sets the user data associated with the line.
- L68-93 _public method_ `public void Append(Color? TxtColor, char CharToAppend)` — Appends a character to the line of text.
- L99-114 _private* method_ `int CountEOL()` — This is a debug function that counts the number of EOL's in a line. There should only ever be 1.
- L121-146 _public method_ `public void Append(Color? TxtColor, string TxtToAppend)` — Appends text to the end of the line.
- L152-163 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments()` — Gets an array of colored line segments that can be used for drawing.
- L171-212 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments(int StartIndex, int Length)` — Gets an array of colored line segments that can be used for drawing.
- L227-329 _public method_ `public ColoredDocumentLineSegment[] GetLineSegmentsWithFindString(int StartIndex, int Length, string FindText, ColorPair InsertionColors, StringComparison ComparisonType, out bool bHasFindText)` — Gets an array of colored line segments that can be used for drawing.
- L334-341 _public method_ `public void FinishBuilding()` — Finishes construction of the line so that reads and searches may be optimized.
- L347-350 _public method_ `public override string ToString()` — Returns the text associated with the line.
- L358-366 _public method_ `public string ToString(int StartIndex, int Length)` — Returns the text associated with the line.
- L370-392 _public method_ `public object Clone()`

#### struct `UnrealControls.OutputWindowDocument.ReadOnlyDocumentLine`  
`public struct ReadOnlyDocumentLine`  
_public; L403-478_
- desc: This structure represents a read only document line.
- L405 _private* field_ `DocumentLine mDocLine`
- L407-410 _internal ctor_ `internal ReadOnlyDocumentLine(DocumentLine DocLine)`
- L415-418 _public property_ `public int Length { get; }` — Gets the length of the line in characters.
- L423-427 _public property_ `public ICloneable UserData { get; set; }` — Gets/Sets the user data associated with the line.
- L434-437 _public indexer_ `public char this[int Index] { get; }` — Gets the character at the specified index.
- L443-446 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments()` — Gets an array of colored line segments that can be used for drawing.
- L454-457 _public method_ `public ColoredDocumentLineSegment[] GetLineSegments(int StartIndex, int Length)` — Gets an array of colored line segments that can be used for drawing.
- L463-466 _public method_ `public override string ToString()` — Returns the text associated with the line.
- L474-477 _public method_ `public string ToString(int StartIndex, int Length)` — Returns the text associated with the line.

#### Namespace-level symbols

- L18 _public delegate_ `public delegate bool OutputWindowDocumentFilterDelegate(OutputWindowDocument.ReadOnlyDocumentLine Line, object Data)` — This delegate is for creating filtered documents.

### `Source/Programs/UnrealControls/OutputWindowDocumentLineAddedEventArgs.cs` (UnrealControls)


#### class `UnrealControls.OutputWindowDocumentLineAddedEventArgs`  
`public class OutputWindowDocumentLineAddedEventArgs : EventArgs`  
_public; L12-43_
- inherits: `EventArgs`
- desc: This class represents event arguments for when a full line of text has been added to a document.
- L14 _private* field_ `OutputWindowDocument.ReadOnlyDocumentLine mLine`
- L15 _private* field_ `int mLineIndex`
- L20-23 _public property_ `public OutputWindowDocument.ReadOnlyDocumentLine Line { get; }` — Gets the text for the line.
- L28-31 _public property_ `public int Index { get; }` — Gets the line index within the document.
- L38-42 _public ctor_ `public OutputWindowDocumentLineAddedEventArgs(int LineIndex, OutputWindowDocument.ReadOnlyDocumentLine Txt)` — Constructor.

### `Source/Programs/UnrealControls/OutputWindowView.Designer.cs` (UnrealControls)


#### class `UnrealControls.OutputWindowView`  
`partial class OutputWindowView`  
_internal*; L5-214_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-196 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L200 _private field_ `private System.Windows.Forms.HScrollBar mHScrollBar`
- L201 _private field_ `private System.Windows.Forms.VScrollBar mVScrollBar`
- L202 _private field_ `private System.Windows.Forms.ContextMenuStrip mDefaultCtxMenu`
- L203 _private field_ `private System.Windows.Forms.ToolStripMenuItem mCtxDefault_Copy`
- L204 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripSeparator1`
- L205 _private field_ `private System.Windows.Forms.ToolStripMenuItem mCtxDefault_ScrollToEnd`
- L206 _private field_ `private System.Windows.Forms.ToolStripMenuItem mCtxDefault_ScrollToHome`
- L207 _private field_ `private System.Windows.Forms.Timer mScrollSelectedTextTimer`
- L208 _private field_ `private System.Windows.Forms.ToolStrip mToolStrip_Find`
- L209 _private field_ `private System.Windows.Forms.ToolStripLabel toolStripLabel_Find`
- L210 _private field_ `private System.Windows.Forms.ToolStripButton mToolStripButton_FindNext`
- L211 _private field_ `private System.Windows.Forms.ToolStripButton mToolStripButton_FindPrevious`
- L212 _private field_ `private System.Windows.Forms.ToolStripTextBox mToolStripTextBox_Find`
- L213 _private field_ `private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemClear`

### `Source/Programs/UnrealControls/OutputWindowView.cs` (UnrealControls)


#### class `UnrealControls.OutputWindowView`  
`public partial class OutputWindowView : UserControl`  
_public; L19-2055_
- inherits: `UserControl`
- desc: This class represents a view into an output document.
- L21 _private* const_ `const TextFormatFlags TXT_FLAGS = TextFormatFlags.NoPadding | TextFormatFlags.NoPrefix | TextFormatFlags.PreserveGraphicsClipping`
- L22 _private* field_ `static readonly Color INVALID_SEARCH_BACKCOLOR = Color.FromArgb(255, 102, 102)`
- L23 _private* field_ `static readonly Color INVALID_SEARCH_FORECOLOR = Color.White`
- L24 _private* field_ `static readonly Color HAS_FINDTEXT_BACKCOLOR = Color.FromArgb(239, 248, 255)`
- L27 _private* field_ `EventHandler<EventArgs> mOnDocChanged`
- L28 _private* field_ `EventHandler<EventArgs> mOnSelectionChanged`
- L31 _private* field_ `XButton mXButtonFind`
- L32 _private* field_ `CheckBox mCheckBox_MatchCase`
- L35 _private* field_ `OutputWindowDocument mDocument`
- L36 _private* field_ `Size mFontDimensions`
- L37 _private* field_ `TextLocation mCaretPosition`
- L38 _private* field_ `TextLocation mSelectionStart`
- L39 _private* field_ `TextLocation mCurrentDocumentSize`
- L40 _private* field_ `Point mLastMousePos`
- L41 _private* field_ `Color mFindTextLineHighlight = HAS_FINDTEXT_BACKCOLOR`
- L42 _private* field_ `Color mFindTextBackColor = Color.Yellow`
- L43 _private* field_ `Color mFindTextForeColor = Color.Black`
- L44 _private* field_ `Size mLastSize`
- L45 _private* field_ `bool mIsSelecting`
- L46 _private* field_ `bool mAutoScroll`
- L48 _private* const_ `const int VK_SHIFT = 0x10`
- L52 _private* method_ `extern static ushort GetAsyncKeyState(int vKey)` — attrs: `[DllImport("user32.dll")]`
- L58-71 _private property_ `private int DisplayableVerticalLines { get; }` — Gets the maximum number of lines that can be drawn in the control.
- L76-79 _private property_ `private int WidthInDisplayablePixels { get; }` — Gets the width of the actual client area in pixels.
- L84-87 _private property_ `private int DisplayableCharacters { get; }` — Gets the maximum number of columns/characters that can be drawn in the control.
- L92-119 _public property_ `public OutputWindowDocument Document { get; set; }` — Gets/Sets the document associated with the view.
- L124-142 _public property_ `public override Font Font { get; set; }` — Gets/Sets the font used to draw text.
- L148-158 _public property_ `public override bool AutoScroll { get; set; }` — attrs: `[Description("Controls whether or not the control autoscrolls when text is appended.")]` — Gets/Sets whether or not the control supports autoscrolling output.
- L164-177 _public property_ `public TextLocation SelectionStart { get; set; }` — attrs: `[Browsable(false)]` — Gets/Sets the start location of the currently selected text.
- L183-197 _public property_ `public TextLocation SelectionEnd { get; set; }` — attrs: `[Browsable(false)]` — Gets/Sets the end location of the currently selected text.
- L203-240 _public property_ `public string SelectedText { get; }` — attrs: `[Browsable(false)]` — Gets the currently selected text.
- L246-249 _public property_ `public bool HasSelectedText { get; }` — attrs: `[Browsable(false)]` — Gets whether or not there's currently selected text.
- L255-274 _public property_ `public TextLocation CaretLocation { get; set; }` — attrs: `[Browsable(false)]` — Gets/Sets the location of the caret within the source document.
- L279-297 _public property_ `public override string Text { get; set; }` — Gets/Sets the text for the window.
- L302-305 _public property_ `public bool IsInFindMode { get; }` — Gets whether or not the view is in "find" mode.
- L310-321 _public property_ `public Color FindTextLineHighlight { get; set; }` — Gets/Sets the highlight color used on lines that contain "find" text.
- L326-337 _public property_ `public Color FindTextBackColor { get; set; }` — Gets/Sets the background color used to draw "find" text.
- L342-353 _public property_ `public Color FindTextForeColor { get; set; }` — Gets/Sets the foreground color used to draw "find" text.
- L358-362 _public event_ `public event EventHandler<EventArgs> DocumentChanged { add; remove; }` — Triggered when the document associated with the view has changed.
- L367-371 _public event_ `public event EventHandler<EventArgs> SelectionChanged { add; remove; }` — Triggered when the selected text has changed.
- L377 _private* method_ `static extern bool CreateCaret(IntPtr hWnd, IntPtr hBitmap, int nWidth, int nHeight)` — attrs: `[DllImport("user32.dll")]`
- L380 _private* method_ `static extern bool DestroyCaret()` — attrs: `[DllImport("user32.dll")]`
- L383 _private* method_ `static extern bool ShowCaret(IntPtr hWnd)` — attrs: `[DllImport("user32.dll")]`
- L386 _private* method_ `static extern bool SetCaretPos(int X, int Y)` — attrs: `[DllImport("user32.dll")]`
- L389 _private* method_ `static extern bool HideCaret(IntPtr hWnd)` — attrs: `[DllImport("user32.dll")]`
- L397-433 _public ctor_ `public OutputWindowView()` — Constructor.
- L440-443 _private* method_ `void mXButtonFind_Click(object sender, EventArgs e)` — Event handler for when the X button on the "Find" toolstrip is clicked.
- L449-568 _protected method_ `protected override void OnPaint(PaintEventArgs e)` — Draws the control.
- L577-594 _private method_ `private ColoredDocumentLineSegment[] GetSegmentsForLine(int LineIndex, int ColIndex, int Length)` — Gets the segments for a line so that it can be drawn.
- L604-619 _private method_ `private void DrawLineSegment(Graphics Gfx, int YLineOffset, ref System.Drawing.Size MaxLineSize, ref int XOffset, ColoredDocumentLineSegment CurSegment)` — Draws the text for a line segment.
- L625-646 _protected method_ `virtual protected void OnDocumentChanged(EventArgs e)` — Event handler for when the document associated with the view has been changed.
- L652-658 _protected method_ `virtual protected void OnSelectionChanged(EventArgs e)` — Event handler for when the selected text has changed.
- L663-717 _private method_ `private void UpdateScrollbars()` — Updates the vertical and horizontal scrollbar values.
- L723-738 _protected method_ `protected override void OnResize(EventArgs e)` — Event handler for when the control is resizing.
- L740-758 _private method_ `private void UpdateScrollbarPositions()`
- L765-769 _private method_ `private void mVScrollBar_ValueChanged(object sender, EventArgs e)` — Event handler for when the vertical scrollbar has been modified.
- L776-780 _private method_ `private void mHScrollBar_ValueChanged(object sender, EventArgs e)` — Event handler for when the horizontal scrollbar has been modified.
- L786-790 _protected method_ `protected override void OnGotFocus(EventArgs e)` — Event handler for when the control has received focus.
- L796-802 _protected method_ `protected override void OnLostFocus(EventArgs e)` — Event handler for when the control has lost focus.
- L807-810 _private method_ `private void InternalCreateCaret()` — Creates the caret.
- L815-820 _private method_ `private void InternalDestroyCaret()` — Destroys the caret.
- L825-863 _private method_ `private void UpdateCaret()` — Updates the position and view state of the caret.
- L869-928 _protected method_ `protected override void OnMouseDown(MouseEventArgs e)` — Event handler for when a mouse button has been pressed.
- L934-940 _protected method_ `protected override void OnMouseUp(MouseEventArgs e)` — Event handler for when a mouse button has been released.
- L946-973 _protected method_ `protected override void OnMouseMove(MouseEventArgs e)` — Event handler for when the mouse cursor has been moved.
- L979-991 _private method_ `private Rectangle GetTextAreaRect()` — Generates a rectangle for the area within the client rectangle that's used for drawing text.
- L997-1014 _protected method_ `protected override void OnMouseWheel(MouseEventArgs e)` — Event handler for when the mouse wheel has been moved.
- L1020-1024 _private method_ `private int GetMaximumVScrollValue()` — Retrieves the maximum value that the vertical scrollbar can be set to.
- L1032-1060 _private* method_ `TextLocation GetCharacterPosFromCoord(int X, int Y)` — Converts a screen coordinate into a character position.
- L1069-1128 _private* method_ `bool GetSelectionForLine(int LineIndex, out int SelectionStart, out int SelectionLength)` — Determines whether or not a line contains selected text.
- L1134-1309 _protected method_ `protected override void OnKeyDown(KeyEventArgs e)` — Event handler for when a key has been pressed.
- L1316-1339 _private method_ `private void MoveCaretDownLines(int NumLines, bool bMoveSelectionStart)` — Moves the caret down in the document.
- L1346-1369 _private method_ `private void MoveCaretUpLines(int NumLines, bool bMoveSelectionStart)` — Moves the caret up in the document.
- L1375-1385 _public method_ `public string CopySelectedText()` — Copies the currently selected text to the clipboard.
- L1390-1402 _public method_ `public void SelectAll()` — Selects all text and scrolls to the caret.
- L1408-1446 _public method_ `public bool ScrollToCaret()` — Scrolls the control so that the caret is visible.
- L1453-1462 _protected method_ `protected override bool IsInputKey(Keys keyData)` — Allows us to handle the arrow keys.
- L1469-1479 _private* method_ `bool IsValidTextLocation(TextLocation Loc)` — Determines whether a location within the current document is valid.
- L1486-1507 _public method_ `public void Select(TextLocation StartLoc, TextLocation EndLoc)` — Selects a range of text and brings the selection into view.
- L1513-1528 _public method_ `public void Select(FindResult Range)` — Selects a range of text and brings the selection into view.
- L1539-1558 _public method_ `public bool Find(string Txt, TextLocation StartLoc, TextLocation EndLoc, RichTextBoxFinds Flags, out FindResult Result)` — Finds the first occurence of the specified string within the document if it exists.
- L1563-1569 _public method_ `public void Clear()` — Clears the text in the source document.
- L1575-1581 _public method_ `public void SaveToFile(string Name)` — Saves the source document to a file.
- L1586-1601 _public method_ `public void ScrollToEnd()` — Scrolls the caret to the end of the document.
- L1606-1621 _public method_ `public void ScrollToHome()` — Scrolls the caret to the beginning of the document.
- L1626-1633 _private method_ `private void ScrollToCaretOrInvalidate()` — Scrolls to the location of the caret. If the caret is already in view then it forces a redraw.
- L1640-1643 _private method_ `private void mCtxDefault_Copy_Click(object sender, EventArgs e)` — Event handler for copying text.
- L1650-1656 _private method_ `private void ToolStripMenuItem_Clear_Click( object sender, EventArgs e )` — Event handler for clearing the document.
- L1663-1666 _private method_ `private void mCtxDefault_ScrollToEnd_Click(object sender, EventArgs e)` — Event handler for scrolling to the end of the document.
- L1673-1676 _private method_ `private void mCtxDefault_ScrollToHome_Click(object sender, EventArgs e)` — Event handler for scrolling to the beginning of the document.
- L1683-1742 _private method_ `private void mScrollSelectedTextTimer_Tick(object sender, EventArgs e)` — Event handler for auto-scrolling selected text.
- L1749-1813 _private* method_ `void mDocument_Modified(object sender, EventArgs e)` — Event handler for when the document has been modified.
- L1820-1826 _private method_ `private void mToolStrip_Find_VisibleChanged(object sender, EventArgs e)` — Event handler for when the visibility of the "Find" toolstrip changes.
- L1833-1853 _private method_ `private void OutputWindowView_MouseMove(object sender, MouseEventArgs e)` — Event handler for when the mouse movers over the control.
- L1860-1866 _private method_ `private void ChildControl_MouseEnter(object sender, EventArgs e)` — Event handler for when the mouse movers over a child control.
- L1871-1880 _public method_ `public void EnterFindMode()` — Tells the view to display the "find" tool strip.
- L1885-1888 _public method_ `public void ExitFindMode()` — Tells the view to close the "find" tool strip.
- L1893-1904 _public method_ `public void FindNext()` — Searches down within the text box for the specified search string.
- L1910-1936 _private* method_ `void FindNext(TextLocation? DownSearchStart)` — Searches down within the text box for the specified search string.
- L1941-1952 _public method_ `public void FindPrevious()` — Searches up within the text box for the specified search string.
- L1958-1983 _private* method_ `void FindPrevious(TextLocation? UpSearchStart)` — Searches up within the text box for the specified search string.
- L1989-2013 _private method_ `private void UpdateFindBoxColor(bool bFound)` — Updates the color of the "Find" text box.
- L2020-2023 _private method_ `private void mToolStripButton_FindNext_Click(object sender, EventArgs e)` — Event handler for when the "Find Next" button has been clicked.
- L2030-2033 _private method_ `private void mToolStripButton_FindPrevious_Click(object sender, EventArgs e)` — Event handler for when the "Find Previous" button has been clicked.
- L2040-2054 _private method_ `private void mToolStripTextBox_Find_TextChanged(object sender, EventArgs e)` — Event handler or when the text in the "find" text box has changed or the state of the "match case" checkbox has changed.

### `Source/Programs/UnrealControls/Properties/AssemblyInfo.cs` (UnrealControls)
_(no declarations)_


### `Source/Programs/UnrealControls/Properties/Resources.Designer.cs` (UnrealControls)


#### class `UnrealControls.Properties.Resources`  
`internal class Resources`  
_internal; L27-71_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L29 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L31 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L34-35 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L41-49 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L56-63 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L65-70 _internal property_ `internal static System.Drawing.Bitmap XButton { get; }`

### `Source/Programs/UnrealControls/SerializableDictionary.cs` (UnrealControls)


#### struct `UnrealControls.SerializableKeyValuePair`  
`public struct SerializableKeyValuePair<TKey, TValue>`  
_public; L14-36_
- attrs: `[Serializable]`
- L16 _private* field_ `TKey mKey`
- L17 _private* field_ `TValue mValue`
- L19-23 _public property_ `public TKey Key { get; set; }`
- L25-29 _public property_ `public TValue Value { get; set; }`
- L31-35 _public ctor_ `public SerializableKeyValuePair(KeyValuePair<TKey, TValue> Pair)`

#### class `UnrealControls.SerializableDictionary`  
`public class SerializableDictionary<TKey, TValue> : ICollection<SerializableKeyValuePair<TKey, TValue>>, IEnumerable<SerializableKeyValuePair<TKey, TValue>>, IEnumerable`  
_public; L39-178_
- attrs: `[Serializable]`
- inherits: `ICollection<SerializableKeyValuePair<TKey, TValue>>, IEnumerable<SerializableKeyValuePair<TKey, TValue>>, IEnumerable`
- L41 _private* field_ `Dictionary<TKey, TValue> mInternalDictionary = ...`
- L41 _private* field_ `Dictionary< mInternalDictionary = new Dictionary<TKey, TValue>()`
- L43-45 _public ctor_ `public SerializableDictionary()`
- L47-56 _protected ctor_ `protected SerializableDictionary(SerializationInfo si, StreamingContext context)`
- L60-63 _public method_ `public void Add(TKey key, TValue value)`
- L65-68 _public method_ `public bool ContainsKey(TKey key)`
- L71-74 _public property_ `public ICollection<TKey> Keys { get; }` — attrs: `[XmlIgnore]`
- L76-79 _public method_ `public bool Remove(TKey key)`
- L81-84 _public method_ `public bool TryGetValue(TKey key, out TValue value)`
- L87-90 _public property_ `public ICollection<TValue> Values { get; }` — attrs: `[XmlIgnore]`
- L93-103 _public indexer_ `public TValue this[TKey key] { get; set; }` — attrs: `[XmlIgnore]`
- L109-113 _public method_ `public void Add(SerializableKeyValuePair<TKey, TValue> item)`
- L115-118 _public method_ `public void Clear()`
- L120-124 _public method_ `public bool Contains(SerializableKeyValuePair<TKey, TValue> item)`
- L126-133 _public method_ `public void CopyTo(SerializableKeyValuePair<TKey, TValue>[] array, int arrayIndex)`
- L136-139 _public property_ `public int Count { get; }` — attrs: `[XmlIgnore]`
- L142-145 _public property_ `public bool IsReadOnly { get; }` — attrs: `[XmlIgnore]`
- L147-151 _public method_ `public bool Remove(SerializableKeyValuePair<TKey, TValue> item)`
- L157-163 _public method_ `public IEnumerator<SerializableKeyValuePair<TKey, TValue>> GetEnumerator()`
- L169-175 _private* method_ `System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()`

### `Source/Programs/UnrealControls/TextLocation.cs` (UnrealControls)


#### struct `UnrealControls.TextLocation`  
`public struct TextLocation`  
_public; L12-167_
- desc: Represents a location within the text of a document.
- L14 _private field_ `private int mLine`
- L15 _private field_ `private int mColumn`
- L20-24 _public property_ `public int Line { get; set; }` — Gets/Sets the line number.
- L29-33 _public property_ `public int Column { get; set; }` — Gets/Sets the character column.
- L40-44 _public ctor_ `public TextLocation(int Line, int Column)` — Constructor.
- L52-55 _public operator_ `public static bool operator !=(TextLocation Left, TextLocation Right)` — Operator overload for !=.
- L63-66 _public operator_ `public static bool operator ==(TextLocation Left, TextLocation Right)` — Operator overload for ==.
- L74-82 _public operator_ `public static bool operator <(TextLocation Left, TextLocation Right)` — Operator overload for <.
- L90-98 _public operator_ `public static bool operator >(TextLocation Left, TextLocation Right)` — Operator overload for >.
- L106-119 _public operator_ `public static bool operator <=(TextLocation Left, TextLocation Right)` — Operator overload for <=.
- L127-140 _public operator_ `public static bool operator >=(TextLocation Left, TextLocation Right)` — Operator overload for >=.
- L147-157 _public method_ `public override bool Equals(object obj)` — Checks an object for equality.
- L163-166 _public method_ `public override int GetHashCode()` — Generates a hash code.

### `Source/Programs/UnrealControls/UnrealAboutBox.Designer.cs` (UnrealControls)


#### class `UnrealControls.UnrealAboutBox`  
`partial class UnrealAboutBox`  
_internal*; L5-128_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-118 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L122 _private field_ `private System.Windows.Forms.PictureBox mPictureBox_AppIcon`
- L123 _private field_ `private System.Windows.Forms.Label label1`
- L124 _private field_ `private System.Windows.Forms.Label mLabel_EngineVersion`
- L125 _private field_ `private System.Windows.Forms.Label mLabel_Changelist`
- L126 _private field_ `private System.Windows.Forms.Button mButton_OK`
- L127 _private field_ `private System.Windows.Forms.Label mLabel_AppVersion`

### `Source/Programs/UnrealControls/UnrealAboutBox.cs` (UnrealControls)


#### class `UnrealControls.UnrealAboutBox`  
`public partial class UnrealAboutBox : Form`  
_public; L18-49_
- inherits: `Form`
- desc: This class represents an about box for an Unreal application.
- L24-48 _public ctor_ `public UnrealAboutBox(Icon AppIcon, EngineVersioning Versioning)` — Constructor.

### `Source/Programs/UnrealControls/UnrealToolStripItemRenderer.cs` (UnrealControls)


#### class `UnrealControls.UnrealToolStripItemRenderer`  
`public class UnrealToolStripItemRenderer : ToolStripProfessionalRenderer`  
_public; L12-122_
- inherits: `ToolStripProfessionalRenderer`
- desc: Custom renderer for drawing ToolStripItems in Unreal .NET tools. Prevents highlighting of ToolStripItems when the application is not focused.
- L18-30 _protected method_ `protected bool AppHasFocus()` — Determines if any of the running forms has focus.
- L37-43 _protected method_ `protected override void OnRenderMenuItemBackground(ToolStripItemRenderEventArgs Args)` — Disables menu item highlighting while mousing over a menu item when the app doesn't have focus.
- L50-56 _protected method_ `protected override void OnRenderItemBackground(ToolStripItemRenderEventArgs Args)` — Disables tool strip item highlighting while mousing over a tool strip item when the app doesn't have focus.
- L63-69 _protected method_ `protected override void OnRenderButtonBackground(ToolStripItemRenderEventArgs Args)` — Disables button highlighting while mousing over a button when the app doesn't have focus.
- L76-82 _protected method_ `protected override void OnRenderDropDownButtonBackground(ToolStripItemRenderEventArgs Args)` — Disables drop down button highlighting while mousing over a drop down button when the app doesn't have focus.
- L89-95 _protected method_ `protected override void OnRenderOverflowButtonBackground(ToolStripItemRenderEventArgs Args)` — Disables overflow button highlighting while mousing over a overflow button when the app doesn't have focus.
- L102-121 _protected method_ `protected override void OnRenderSplitButtonBackground(ToolStripItemRenderEventArgs Args)` — Disables split button highlighting while mousing over a split button when the app doesn't have focus.

### `Source/Programs/UnrealControls/Utilities.cs` (UnrealControls)


#### enum `EpicCommonUtilities.EStatType`  
`public enum EStatType`  
_public; L11-19_
- desc: The kinds of statistics that the StatisticalFloat class tracks (or can optionally track, in the case of Median)
- L13 _public* enumerator_ `Minimum`
- L14 _public* enumerator_ `Maximum`
- L15 _public* enumerator_ `Average`
- L16 _public* enumerator_ `StDev`
- L17 _public* enumerator_ `Median`
- L18 _public* enumerator_ `Count`

#### class `EpicCommonUtilities.StatisticalFloat`  
`public class StatisticalFloat`  
_public; L24-247_
- desc: Keeps a running set of first-order statistics for a single variable
- L30 _public field_ `public static bool bSupportMedian = true` — Should newly constructed StatisticalFloat instances track the median value? This requires O(N) storage instead of O(1) storage and it is only checked on construction.
- L32-51 _public method_ `public double GetByType(EStatType Type)`
- L53-56 _public property_ `public double Average { get; }`
- L58-61 _public property_ `public double Min { get; }`
- L63-66 _public property_ `public double Max { get; }`
- L68-72 _public property_ `public double Value { get; set; }`
- L77-91 _public property_ `public double Median { get; }` — Returns the median if bSupportMedian was true at construction and NaN otherwise
- L93-102 _public property_ `public double StandardDeviation { get; }`
- L104-107 _public property_ `public double AggregateSum { get; }`
- L109-115 _public ctor_ `public StatisticalFloat()`
- L117-122 _public method_ `public StatisticalFloat Clone()`
- L124-133 _public ctor_ `public StatisticalFloat(double InValue)`
- L135-158 _public method_ `public void AddSample(double InValue)`
- L160-183 _public method_ `public void AddSamples(StatisticalFloat Samples)`
- L185-205 _public method_ `public void AddDistribution(StatisticalFloat Samples)`
- L207-221 _public method_ `public void ScaleBy(double ScaleFactor)`
- L223-226 _public method_ `public string ToStringSizesInKB()`
- L228-231 _public method_ `public string Min_ToStringInt()`
- L233-236 _public method_ `public string Max_ToStringInt()`
- L238 _private* field_ `double MySumOfSquares = 0.0`
- L239 _private* field_ `double MySum = 0.0`
- L240 _private* field_ `double MyMin = 0.0`
- L241 _private* field_ `double MyMax = 0.0`
- L242 _private* field_ `long MyCount = 0`
- L246 _private* field_ `List<double> MySamples = null`

### `Source/Programs/UnrealControls/XButton.cs` (UnrealControls)


#### class `UnrealControls.XButton`  
`public partial class XButton : UserControl`  
_public; L20-115_
- inherits: `UserControl`
- desc: The X button on a VS.NET style tab control.
- L22 _private* field_ `ProfessionalColorTable mColorTable = new ProfessionalColorTable()`
- L23 _private* field_ `Bitmap mXBitmap`
- L24 _private* field_ `Color mBitmapDisplayColor = Color.Black`
- L25 _private* field_ `bool mMouseOver = false`
- L30-37 _public ctor_ `public XButton()` — Constructor.
- L42-63 _private* method_ `unsafe void UpdateBitmapDisplayColor()` — Updates the colors in the bitmap to show the correct text color.
- L69-90 _protected method_ `protected override void OnPaint(PaintEventArgs e)` — Called to draw the control.
- L96-102 _protected method_ `protected override void OnMouseEnter(EventArgs e)` — Called when the mouse enters the control.
- L108-114 _protected method_ `protected override void OnMouseLeave(EventArgs e)` — Called when the mouse leaves the control.

### `Source/Programs/UnrealControls/XButton.designer.cs` (UnrealControls)


#### class `UnrealControls.XButton`  
`partial class XButton`  
_internal*; L5-38_
- L10 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L16-23 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L31-35 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
