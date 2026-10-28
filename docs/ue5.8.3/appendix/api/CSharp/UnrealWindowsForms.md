# CSharp / UnrealWindowsForms

- project root: `Source/Programs/Windows/UnrealWindowsForms`
- files: 5; symbols: 64
- symbol kinds: class=6, ctor=3, field=29, method=25, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Windows/UnrealWindowsForms/Gauntlet/BuildLauncher.Designer.cs` (UnrealWindowsForms)


#### class `UnrealWindowsForms.BuildLauncher`  
`partial class BuildLauncher`  
_internal*; L3-384_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-356 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L360 _private field_ `private System.Windows.Forms.ComboBox buildList`
- L361 _private field_ `private System.Windows.Forms.Label label1`
- L362 _private field_ `private System.Windows.Forms.Label label2`
- L363 _private field_ `private System.Windows.Forms.ComboBox platformList`
- L364 _private field_ `private System.Windows.Forms.Label label3`
- L365 _private field_ `private System.Windows.Forms.ComboBox configurationList`
- L366 _private field_ `private System.Windows.Forms.Button goButton`
- L367 _private field_ `private System.Windows.Forms.TabControl optionTab`
- L368 _private field_ `private System.Windows.Forms.TabPage tabPage1`
- L369 _private field_ `private System.Windows.Forms.TabPage tabPage2`
- L370 _private field_ `private System.Windows.Forms.CheckBox optionCook`
- L371 _private field_ `private System.Windows.Forms.CheckBox optionBuildClient`
- L372 _private field_ `private System.Windows.Forms.Label label4`
- L373 _private field_ `private System.Windows.Forms.ComboBox modeList`
- L374 _private field_ `private System.Windows.Forms.Button refreshButton`
- L375 _private field_ `private System.Windows.Forms.CheckBox optionSharedCookedBuild`
- L376 _private field_ `private System.Windows.Forms.CheckBox optionBuildEditor`
- L377 _private field_ `private System.Windows.Forms.CheckBox optionUsePrecompiledBuild`
- L378 _private field_ `private System.Windows.Forms.Label etaLabel`
- L379 _private field_ `private System.Windows.Forms.CheckBox optionRealTimeUpdates`
- L380 _private field_ `private System.Windows.Forms.TextBox testTextBox`
- L381 _private field_ `private System.Windows.Forms.Label label5`
- L382 _private field_ `private System.Windows.Forms.CheckBox optionEditorServer`
- L383 _private field_ `private System.Windows.Forms.CheckBox optionForceStage`

### `Source/Programs/Windows/UnrealWindowsForms/Gauntlet/BuildLauncher.cs` (UnrealWindowsForms)


#### class `UnrealWindowsForms.BuildLauncher`  
`public partial class BuildLauncher : Form`  
_public; L18-392_
- inherits: `Form`
- L20 _public field_ `public List<String> RunParams`
- L22 _public property_ `public string BuildLocation { get; set; }`
- L25-65 _public ctor_ `public BuildLauncher(String InBuildLocation)`
- L67-70 _private method_ `private void refreshButton_Click(object sender, EventArgs e)`
- L72-104 _private method_ `private bool IsBuildValid(DirectoryInfo Dir)`
- L106-150 _private method_ `private void UpdateBuildList()`
- L152-229 _private method_ `private void goButton_Click(object sender, EventArgs e)`
- L231 _private field_ `private int EnabledStateRecurseProtection = 0`
- L232-283 _private method_ `private void UpdateEnabledState()`
- L285-330 _private method_ `private void UpdateEstimatedTime()`
- L332-336 _private method_ `private void optionSharedCookedBuild_CheckedChanged(object sender, EventArgs e)`
- L338-342 _private method_ `private void optionUsePrecompiledBuild_CheckedChanged(object sender, EventArgs e)`
- L344-348 _private method_ `private void optionTab_TabIndexChanged(object sender, EventArgs e)`
- L350-354 _private method_ `private void optionTab_SelectedIndexChanged(object sender, EventArgs e)`
- L356-359 _private method_ `private void optionBuildEditor_CheckedChanged(object sender, EventArgs e)`
- L361-365 _private method_ `private void optionBuildClient_CheckedChanged(object sender, EventArgs e)`
- L367-371 _private method_ `private void optionRealTimeUpdates_CheckedChanged(object sender, EventArgs e)`
- L373-376 _private method_ `private void label5_Click(object sender, EventArgs e)`
- L378-381 _private method_ `private void platformList_SelectedIndexChanged(object sender, EventArgs e)`
- L383-386 _private method_ `private void EditorServer_CheckedChanged(object sender, EventArgs e)`
- L388-391 _private method_ `private void optionCook_CheckedChanged(object sender, EventArgs e)`

#### class `UnrealWindowsForms.ListItem`  
`class ListItem`  
_internal*; L394-410_
- L396-400 _public ctor_ `public ListItem(string InText, params string[] InArgs)`
- L401-405 _public ctor_ `public ListItem(string InText)`
- L407 _public field_ `public string Text`
- L408 _public field_ `public List<string> Args`
- L409 _public method_ `public override string ToString()`

### `Source/Programs/Windows/UnrealWindowsForms/Gauntlet/GauntletBuildLauncherDialog.cs` (UnrealWindowsForms)


#### class `UnrealWindowsForms.GauntletBuildLauncherDialog`  
`public static class GauntletBuildLauncherDialog`  
_public; L9-22_
- L11-21 _public method_ `public static List<string> ShowDialogAndReturnRunParams(string RootPath)`

### `Source/Programs/Windows/UnrealWindowsForms/Turnkey/TurnkeyDialog.cs` (UnrealWindowsForms)


#### class `UnrealWindowsForms.TurnkeyDialog`  
`public class TurnkeyDialog`  
_public; L8-109_
- L10-108 _public method_ `public static string ShowDialogAndReturnResult(string Prompt, string Default)`

### `Source/Programs/Windows/UnrealWindowsForms/Utils/Utils.cs` (UnrealWindowsForms)


#### class `UnrealWindowsForms.Utils`  
`public static class Utils`  
_public; L10-39_
- L13 _private method_ `private static extern bool SetProcessDPIAware()` — attrs: `[System.Runtime.InteropServices.DllImport("user32.dll")]`
- L15-22 _public method_ `public static void SetupVisuals()`
- L24-38 _public method_ `public static string ShowOpenFileDialogAndReturnFilename(string Filter, string InitialDirectory="")`
