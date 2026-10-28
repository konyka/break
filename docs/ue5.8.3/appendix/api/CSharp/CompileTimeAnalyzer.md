# CSharp / CompileTimeAnalyzer

- project root: `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer`
- files: 13; symbols: 204
- symbol kinds: class=19, const=2, ctor=14, enum=1, enumerator=6, event=5, field=31, method=94, property=31, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/App.xaml.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.App`  
`public partial class App : Application`  
_public; L16-18_
- inherits: `Application`
- desc: Interaction logic for App.xaml

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Commands/OpenTimingDataCommand.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.Commands.OpenTimingDataCommand`  
`public class OpenTimingDataCommand : ICommand`  
_public; L11-35_
- inherits: `ICommand`
- L13 _private field_ `private TimingDataViewModel ViewModelToOpen`
- L16 _public event_ `public event EventHandler? CanExecuteChanged`
- L19-22 _public ctor_ `public OpenTimingDataCommand(TimingDataViewModel TimingData)`
- L24 _public property_ `public Action<TimingDataViewModel> OpenAction { get; set; }`
- L26-29 _public method_ `public bool CanExecute(object? parameter)`
- L31-34 _public method_ `public void Execute(object? parameter)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Controls/TimingDataGrid.xaml.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.Controls.TimingDataGrid`  
`public partial class TimingDataGrid : UserControl`  
_public; L20-116_
- inherits: `UserControl`
- desc: Interaction logic for TimingDataGrid.xaml
- L22 _private field_ `private DataGridColumn SortingColumn = null`
- L24-27 _public ctor_ `public TimingDataGrid()`
- L29-55 _private method_ `private void Grid_Sorting(object sender, DataGridSortingEventArgs e)`
- L57-67 _private method_ `private void SortNodes()`
- L69-100 _private method_ `private void Grid_KeyDown(object sender, KeyEventArgs e)`
- L102-115 _private method_ `private void Button_Click(object sender, System.Windows.RoutedEventArgs e)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Controls/TimingDataTab.xaml.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.Controls.TimingDataTab`  
`public partial class TimingDataTab : UserControl`  
_public; L26-429_
- inherits: `UserControl`
- desc: Interaction logic for TimingDataTab.xaml
- L28 _private field_ `private TreeGridModel FilesModel`
- L29 _private field_ `private TreeGridModel IncludesModel`
- L30 _private field_ `private TreeGridModel FlattenedIncludesModel`
- L31 _private field_ `private TreeGridModel ClassesModel`
- L32 _private field_ `private TreeGridModel GroupedClassesModel`
- L33 _private field_ `private TreeGridModel FunctionsModel`
- L34 _private field_ `private TreeGridModel GroupedFunctionsModel`
- L36 _private field_ `private Dictionary<TimingDataViewModel, TabState> TabStates = ...`
- L36 _private field_ `private Dictionary< TabStates = new Dictionary<TimingDataViewModel, TabState>()`
- L55-60 _public ctor_ `public TimingDataTab()`
- L62-137 _private method_ `private void TimingDataTab_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)`
- L139-163 _private method_ `private void UpdateUIForAggregate(TimingDataViewModel TimingData)`
- L165-188 _private method_ `private void UpdateUIForSingleFile(TimingDataViewModel TimingData)`
- L190-198 _private method_ `private void RefreshTabState(TabItem Tab, TabState State)`
- L200-218 _private method_ `private void SortModel(DataGrid Grid)`
- L220-224 _private method_ `private void UpdateTabVisibility(TreeGridFlatModel TabModel, TabItem Tab, TimingDataGrid Grid)`
- L226-236 _private method_ `private TreeGridModel GenerateTreeGridModel(TreeGridElement Parent)`
- L238-261 _private method_ `private void FlattenIncludesInternal(Dictionary<string, TimingDataViewModel> FlattenedIncludes, IEnumerable<TimingDataViewModel> ViewModels, double ParentDurationOverride)`
- L263-270 _private method_ `private TreeGridModel GenerateFlattenedModel(TreeGridModel UnflattenedModel)`
- L272-298 _private method_ `private TreeGridModel GenerateGroupedModel(TreeGridModel UngroupedModel)`
- L300-378 _private method_ `private IEnumerable<TimingDataViewModel> GroupChildren(IEnumerable<TimingDataViewModel> Children)`
- L380-390 _private method_ `private void UpdateGridModel(CheckBox CheckBox, TimingDataGrid Grid, TreeGridModel UncheckedModel, TreeGridModel CheckedModel)`
- L392-396 _private method_ `private void FlattenIncludes_Checked(object sender, RoutedEventArgs e)`
- L398-409 _private method_ `private void GroupTemplates_Checked(object sender, RoutedEventArgs e)`
- L411-415 _private method_ `private void DataGridRow_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)`
- L417-421 _private method_ `private void DataGridRow_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)`
- L423-428 _private method_ `private void DataGridRow_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)`

#### class `Timing_Data_Investigator.Controls.TimingDataTab.TabState`  
`private class TabState`  
_private; L38-53_
- L40 _public property_ `public Dictionary<TabItem, DataGridColumn> SortColumns { get; }`
- L41 _public property_ `public Dictionary<TabItem, ListSortDirection?> SortDirections { get; }`
- L43 _public property_ `public bool? FlattenIncludes { get; set; }`
- L44 _public property_ `public bool? GroupClasses { get; set; }`
- L45 _public property_ `public bool? GroupFunctions { get; set; }`
- L47-52 _public method_ `public void SetTabState(TabItem Tab, DataGrid TabDataGrid)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Converters.cs` (CompileTimeAnalyzer)


#### enum `Timing_Data_Investigator.VisibilityOptions`  
`public enum VisibilityOptions`  
_public; L12-20_
- L14 _public* enumerator_ `VisibleOnFalse`
- L15 _public* enumerator_ `VisibleOnTrue`
- L16 _public* enumerator_ `HiddenOnFalse`
- L17 _public* enumerator_ `HiddenOnTrue`
- L18 _public* enumerator_ `CollapsedOnFalse`
- L19 _public* enumerator_ `CollapsedOnTrue`

#### class `Timing_Data_Investigator.NullToVisibilityConverter`  
`public class NullToVisibilityConverter : IValueConverter`  
_public; L22-54_
- inherits: `IValueConverter`
- L24-47 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L49-52 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `Timing_Data_Investigator.BoolToVisibilityConverter`  
`public class BoolToVisibilityConverter : IValueConverter`  
_public; L55-86_
- inherits: `IValueConverter`
- L57-80 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L82-85 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `Timing_Data_Investigator.MultiBoolToVisibilityConverter`  
`public class MultiBoolToVisibilityConverter : IMultiValueConverter`  
_public; L88-128_
- inherits: `IMultiValueConverter`
- L90-122 _public method_ `public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)`
- L124-127 _public method_ `public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)`

#### class `Timing_Data_Investigator.IntGreaterThanConverter`  
`public class IntGreaterThanConverter : IValueConverter`  
_public; L130-151_
- inherits: `IValueConverter`
- L132-145 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L147-150 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `Timing_Data_Investigator.IntLessThanConverter`  
`public class IntLessThanConverter : IValueConverter`  
_public; L153-174_
- inherits: `IValueConverter`
- L155-168 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L170-173 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `Timing_Data_Investigator.LevelConverter`  
`public class LevelConverter : IValueConverter`  
_public; L176-190_
- inherits: `IValueConverter`
- L178 _public property_ `public GridLength LevelWidth { get; set; }`
- L180-184 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L186-189 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/MainWindow.xaml.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.MainWindow`  
`public partial class MainWindow : Window`  
_public; L21-162_
- inherits: `Window`
- desc: Interaction logic for MainWindow.xaml
- L23-31 _public ctor_ `public MainWindow()`
- L33-46 _private method_ `private void MainWindow_Loaded(object sender, RoutedEventArgs e)`
- L48-96 _private method_ `private void LoadTimingFile(string FilePath)`
- L98-103 _private method_ `private void AddTimingDataViewModelToTabs(TimingDataViewModel NewViewModel)`
- L105-108 _private method_ `private void OpenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)`
- L110-113 _private method_ `private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)`
- L115-123 _private method_ `private void ShowOpenFileDialog()`
- L125-128 _private method_ `private void Exit_Click(object sender, RoutedEventArgs e)`
- L130-135 _private method_ `private void RemoveTab_Click(object sender, RoutedEventArgs e)`
- L137-145 _private method_ `private void StackPanel_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)`
- L147-161 _private method_ `private void CloseTab(TimingDataViewModel TabToRemove)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Models/TimingDataViewModel.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.Models.TimingDataViewModel`  
`public class TimingDataViewModel : TreeGridElement`  
_public; L21-256_
- inherits: `TreeGridElement`
- L30 _private field_ `private Dictionary<string, BinaryBlob> BinaryBlobLookupTable`
- L30 _private field_ `private Dictionary< BinaryBlobLookupTable`
- L31 _private field_ `private byte[] BinaryBlobBytes`
- L33-35 _public ctor_ `public TimingDataViewModel()`
- L37-40 _public ctor_ `public TimingDataViewModel(IEnumerable<TreeGridElement> InitialChildren)`
- L42 _public property_ `public string Name { get; set; }`
- L43 _public property_ `public TimingDataType Type { get; set; }`
- L44 _public property_ `public int Count { get; set; }`
- L45 _public property_ `public double? ParentDurationOverride { get; set; }`
- L46 _public property_ `public double ExclusiveDuration { get; set; }`
- L47 _public property_ `public double ExclusivePercent => ...`
- L48 _public property_ `public double InclusiveDuration => ...`
- L49 _public property_ `public double InclusivePercent => ...`
- L50 _public property_ `public string ShortName => ...`
- L51 _public property_ `public ICommand OpenCommand { get; set; }`
- L52 _public property_ `public int SortedIndex { get; set; }`
- L54-68 _private method_ `private double GetPercentOfParent(double Duration)`
- L70-74 _public method_ `public void UpdateSortIndex(string SortMember, ListSortDirection SortDirection)`
- L76-139 _private method_ `private static void UpdateSortIndexInternal(string SortMember, ListSortDirection SortDirection, TimingDataViewModel ViewModel, ref int Index)`
- L141-147 _public method_ `public static TimingDataViewModel FromBinaryFile(FileReference BinaryFile)`
- L149-154 _public method_ `public static TimingDataViewModel FromJsonFile(FileReference JsonFile)`
- L156-174 _public method_ `public static TimingDataViewModel FromTimingData(TimingData TimingData)`
- L176-198 _public method_ `public TimingDataViewModel LoadTimingDataFromBinaryBlob(string BinaryBlobName)`
- L200-235 _private method_ `private static TimingDataViewModel FromBinaryReader(BinaryReader Reader)`
- L237-255 _public method_ `public TimingDataViewModel Clone()`

#### struct `Timing_Data_Investigator.Models.TimingDataViewModel.BinaryBlob`  
`private struct BinaryBlob`  
_private; L23-28_
- L25 _public property_ `public int Offset { get; set; }`
- L26 _public property_ `public int CompressedSize { get; set; }`
- L27 _public property_ `public int DecompressedSize { get; set; }`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Properties/Resources.Designer.cs` (CompileTimeAnalyzer)


#### class `CompileTimeAnalyzer.Properties.Resources`  
`internal class Resources`  
_internal; L25-62_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "17.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/Properties/Settings.Designer.cs` (CompileTimeAnalyzer)


#### class `CompileTimeAnalyzer.Properties.Settings`  
`internal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase`  
_internal; L16-25_
- attrs: `[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()] [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "17.3.0.0")]`
- inherits: `global::System.Configuration.ApplicationSettingsBase`
- L18 _private field_ `private static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())))`
- L20-24 _public property_ `public static Settings Default { get; }`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/TreeGridElement.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.TreeGridElement`  
`public class TreeGridElement : ContentElement`  
_public; L18-316_
- inherits: `ContentElement`
- L20 _private const_ `private const string NullItemError = "The item added to the collection cannot be null."`
- L22 _public field_ `public static readonly RoutedEvent ExpandingEvent`
- L23 _public field_ `public static readonly RoutedEvent ExpandedEvent`
- L24 _public field_ `public static readonly RoutedEvent CollapsingEvent`
- L25 _public field_ `public static readonly RoutedEvent CollapsedEvent`
- L26 _public field_ `public static readonly DependencyProperty HasChildrenProperty`
- L27 _public field_ `public static readonly DependencyProperty IsExpandedProperty`
- L28 _public field_ `public static readonly DependencyProperty LevelProperty`
- L30 _public property_ `public TreeGridElement Parent { get; set; }`
- L31 _public property_ `public TreeGridModel Model { get; set; }`
- L32 _public property_ `public ObservableCollection<TreeGridElement> Children { get; set; }`
- L34-46 _private* ctor_ `static TreeGridElement()`
- L48-55 _public ctor_ `public TreeGridElement()`
- L57-70 _internal method_ `internal void SetModel(TreeGridModel NewModel, TreeGridElement NewParent = null)`
- L72 _protected method_ `protected virtual void OnExpanding()`
- L73 _protected method_ `protected virtual void OnExpanded()`
- L74 _protected method_ `protected virtual void OnCollapsing()`
- L75 _protected method_ `protected virtual void OnCollapsed()`
- L77-106 _private method_ `private void OnChildrenChanged(object sender, NotifyCollectionChangedEventArgs args)`
- L108-118 _private method_ `private void OnChildAdded(object item)`
- L120-130 _private method_ `private void OnChildReplaced(TreeGridElement oldChild, object item, int index)`
- L132-139 _private method_ `private void OnChildRemoved(TreeGridElement child)`
- L141-157 _private method_ `private void OnChildrenCleared(IList children)`
- L159-170 _internal method_ `internal static TreeGridElement VerifyItem(object Item)`
- L172-212 _private method_ `private static void OnIsExpandedChanged(DependencyObject element, DependencyPropertyChangedEventArgs args)`
- L214-224 _private method_ `private static DependencyProperty RegisterHasChildrenProperty()`
- L226-237 _private method_ `private static DependencyProperty RegisterIsExpandedProperty()`
- L239-249 _private method_ `private static DependencyProperty RegisterLevelProperty()`
- L251-255 _private method_ `private static RoutedEvent RegisterExpandingEvent()`
- L257-261 _private method_ `private static RoutedEvent RegisterExpandedEvent()`
- L263-267 _private method_ `private static RoutedEvent RegisterCollapsingEvent()`
- L269-273 _private method_ `private static RoutedEvent RegisterCollapsedEvent()`
- L275-279 _public property_ `public bool HasChildren { get; set; }`
- L281-285 _public property_ `public bool IsExpanded { get; set; }`
- L287-291 _public property_ `public int Level { get; set; }`
- L293-297 _public event_ `public event RoutedEventHandler Expanding { add; remove; }`
- L299-303 _public event_ `public event RoutedEventHandler Expanded { add; remove; }`
- L305-309 _public event_ `public event RoutedEventHandler Collapsing { add; remove; }`
- L311-315 _public event_ `public event RoutedEventHandler Collapsed { add; remove; }`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/TreeGridElementComparer.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.PropertyComparer`  
`public class PropertyComparer<TClassType> : IComparer<TClassType>`  
_public; L13-46_
- inherits: `IComparer<TClassType>`
- L15 _private field_ `private string sCompareProperty`
- L16 _private field_ `private bool bSortDescending`
- L18-22 _public ctor_ `public PropertyComparer(string CompareProperty, bool SortDescending)`
- L24-45 _public method_ `public int Compare(TClassType? x, TClassType? y)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/TreeGridFlatModel.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.TreeGridFlatModel`  
`public class TreeGridFlatModel : ObservableCollection<TreeGridElement>`  
_public; L16-199_
- inherits: `ObservableCollection<TreeGridElement>`
- L18 _private const_ `private const string ModificationError = "The collection cannot be modified by the user."`
- L20 _private field_ `private bool Modification`
- L21 _private field_ `private HashSet<TreeGridElement> Keys`
- L22 _private field_ `private PropertyInfo CurrentSortProperty`
- L23 _private field_ `private ListSortDirection? CurrentSortDirection`
- L25-27 _public ctor_ `public TreeGridFlatModel() : this(null)`
- L29-38 _public ctor_ `public TreeGridFlatModel(IEnumerable<TreeGridElement> Elements)`
- L40-69 _public method_ `public void Sort(PropertyInfo SortProperty, ListSortDirection? SortDirection)`
- L71-91 _private method_ `private void SortNodes(TreeGridElement Node)`
- L93-97 _internal method_ `internal bool ContainsKey(TreeGridElement item)`
- L99-112 _internal method_ `internal void PrivateInsert(int index, TreeGridElement item)`
- L114-153 _internal method_ `internal void PrivateInsertRange(int Index, IList<TreeGridElement> Items)`
- L155-172 _internal method_ `internal void PrivateRemoveRange(int index, int count)`
- L174-185 _internal method_ `internal void PrivateClear()`
- L187-198 _protected method_ `protected override void OnCollectionChanged(NotifyCollectionChangedEventArgs args)`

### `Source/Programs/Windows/CompileTimeAnalyzer/CompileTimeAnalyzer/TreeGridModel.cs` (CompileTimeAnalyzer)


#### class `Timing_Data_Investigator.TreeGridModel`  
`public class TreeGridModel : ObservableCollection<TreeGridElement>`  
_public; L14-213_
- inherits: `ObservableCollection<TreeGridElement>`
- L16 _private field_ `private List<TreeGridElement> ItemCache`
- L18-20 _public ctor_ `public TreeGridModel() : this(null)`
- L22-35 _public ctor_ `public TreeGridModel(IEnumerable<TreeGridElement> Elements)`
- L37 _public property_ `public TreeGridFlatModel FlatModel { get; set; }`
- L39-50 _protected method_ `protected override void OnCollectionChanged(NotifyCollectionChangedEventArgs args)`
- L52-72 _internal method_ `internal void Expand(TreeGridElement item)`
- L74-89 _internal method_ `internal void Collapse(TreeGridElement item)`
- L91-111 _internal method_ `internal void OnChildAdded(TreeGridElement child)`
- L113-115 _internal method_ `internal void OnChildReplaced(TreeGridElement oldChild, TreeGridElement child, int index)`
- L117-119 _internal method_ `internal void OnChildRemoved(TreeGridElement child)`
- L121-123 _internal method_ `internal void OnChildrenRemoved(TreeGridElement parent, IList children)`
- L125-144 _private method_ `private void OnRootAdded(object Item, bool InsertIntoFlatModel)`
- L146-161 _private method_ `private void CacheFlatChildren(TreeGridElement item)`
- L163-181 _private method_ `private int CountFlatChildren(TreeGridElement item)`
- L183-212 _private method_ `private int FindFlatInsertionIndex(TreeGridElement item)`
