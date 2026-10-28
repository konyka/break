# Programs / SblSlate

- module root: `Source/Programs/SwitchboardListener/SblSlate`
- headers: 1; symbols: 24
- symbol kinds: class=1, enum=1, enumerator=2, member=7, prototype=13
- PrivateDependencyModuleNames: OutputLog, Slate, SlateReflector, StandaloneRenderer, ToolMenus
- PublicDependencyModuleNames: SblCore, SlateCore

### `Source/Programs/SwitchboardListener/SblSlate/Internal/SblMainWindow.h` (Internal)


#### class `FSwitchboardListenerMainWindow`  
`class FSwitchboardListenerMainWindow`  
_L19-64_
- L28 _public prototype_ `FSwitchboardListenerMainWindow(FSwitchboardListener& InListener);`
- L31 _private prototype_ `void OnInit();`
- L32 _private prototype_ `void OnShutdown();`
- L33 _private prototype_ `void OnTick();`
- L36 _private prototype_ `void CustomizeToolMenus();`
- L37 _private prototype_ `void CustomizeToolMenus_AddGeneralSection(UToolMenu* InMenu);`
- L38 _private prototype_ `void CustomizeToolMenus_AddPasswordSection(UToolMenu* InMenu);`
- L40 _private prototype_ `void CustomizeToolMenus_AddDevelopmentSection(UToolMenu* InMenu);`
- L43 _private prototype_ `TSharedRef<SWidget> CreateRootSwitcher();`
- L44 _private prototype_ `TSharedRef<SWidget> CreateSetPasswordPanel();`
- L45 _private prototype_ `TSharedRef<SWidget> CreateMainPanel();`
- L46 _private prototype_ `TSharedRef<SWidget> CreateOutputLog();`
- L48 _private prototype_ `FReply OnSetPasswordClicked();`
- L51 _private member_ `FSwitchboardListener& Listener;`
- L53 _private member_ `TSharedPtr<SWindow> RootWindow;`
- L54 _private member_ `TSharedPtr<SWidgetSwitcher> PanelSwitcher;`
- L56 _private member_ `TSharedPtr<SEditableTextBox> PasswordTextBox;`
- L58 _private member_ `bool bPasswordRevealedInEditBox = false;`
- L59 _private member_ `bool bPasswordRevealedInMenu = false;`
- L62 _private member_ `ECheckBoxState CachedAutolaunchEnabled;`

#### enum `FSwitchboardListenerMainWindow::EPanelIndices`  
`enum class EPanelIndices`  
_L21-25_
- L23 _public enumerator_ `MainPanel = 0`
- L24 _public enumerator_ `PasswordPanel`
