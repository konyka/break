# Editor / StatusBar

- module root: `Source/Editor/StatusBar`
- headers: 6; symbols: 233
- symbol kinds: class=6, delegate=2, enum=3, enumerator=11, function=15, macro=1, member=57, namespace=4, prototype=126, struct=5, typedef=1, variable=2
- DynamicallyLoadedModuleNames: ContentBrowser, MainFrame, OutputLog
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine, InputCore, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, ToolWidgets, UnrealEd, UnsavedAssetsTracker
- PrivateIncludePathModuleNames: ContentBrowser, MainFrame, OutputLog

### `Source/Editor/StatusBar/Private/SOneTimeIndustryQuery.h` (Private)


#### class `SOneTimeIndustryQuery`  
`class SOneTimeIndustryQuery : public SCompoundWidget`  
_L11-55_
- inherits: `SCompoundWidget`
- L13 _private function_ `SLATE_BEGIN_ARGS(SOneTimeIndustryQuery)`
- L17 _private function_ `SOneTimeIndustryQuery() : NewBadgeBrush(FStyleColors::Success) , KeybindBackgroundBrush(FLinearColor::Transparent, 6.0f, FStyleColors::ForegroundHover, 1.5f)`
- L22 _private prototype_ `static void Show(TSharedPtr<SWindow> InParentWindow);`
- L24 _private prototype_ `static void Dismiss();`
- L26 _private prototype_ `static const bool ShouldShowIndustryQuery();`
- L28 _private prototype_ `void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `bool CanSubmitIndustryInfo() const;`
- L32 _private prototype_ `void HandleIndustryComboChanged(TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo);`
- L33 _private prototype_ `TSharedRef<SWidget> GenerateIndustryComboItem(TSharedPtr<FName> InItem) const;`
- L34 _private prototype_ `FText GetUserSetIndustryNameText() const;`
- L35 _private prototype_ `FText GetIndustryNameText(FName IndustryName) const;`
- L36 _private prototype_ `FReply OnSubmit();`
- L39 _private member_ `FSlateRoundedBoxBrush NewBadgeBrush;`
- L40 _private member_ `FSlateRoundedBoxBrush KeybindBackgroundBrush;`
- L41 _private member_ `static TWeakPtr<SOneTimeIndustryQuery> ActiveNotification;`
- L42 _private member_ `static TWeakPtr<SWindow> ParentWindow;`
- L43 _private member_ `TArray<TSharedPtr<FName>> IndustryComboList;`
- L44 _private member_ `TOptional<FName> UserSetIndustry;`
- L46 _private member_ `static const FName GamesIndustryName;`
- L47 _private member_ `static const FName FilmIndustryName;`
- L48 _private member_ `static const FName ArchitectureIndustryName;`
- L49 _private member_ `static const FName AutoIndustryName;`
- L50 _private member_ `static const FName BroadcastIndustryName;`
- L51 _private member_ `static const FName AdIndustryName;`
- L52 _private member_ `static const FName SimulationIndustryName;`
- L53 _private member_ `static const FName FashionIndustryName;`
- L54 _private member_ `static const FName OtherIndustryName;`

### `Source/Editor/StatusBar/Private/SStatusBar.h` (Private)


#### struct `FStatusBarMessage`  
`struct FStatusBarMessage`  
_L34-46_
- desc: Data payload for messages in the status bar
- L36 _public prototype_ `FStatusBarMessage(const TAttribute<FText>& InMessageText, const TAttribute<FText>& InHintText, FStatusBarMessageHandle InHandle);`
- L38 _public prototype_ `FStatusBarMessage(const TAttribute<FText>& InMessageText, const TAttribute<FText>& InHintText, FStatusBarMessageHandle InHandle, const TAttribute<const FSlateBrush*>& InIconBrush, const TAttribute<FSlateColor>& InIconColor);`
- L41 _public member_ `TAttribute<FText> MessageText;`
- L42 _public member_ `TAttribute<FText> HintText;`
- L43 _public member_ `TAttribute<const FSlateBrush*> IconBrush;`
- L44 _public member_ `TAttribute<FSlateColor> IconColor;`
- L45 _public member_ `FStatusBarMessageHandle Handle;`

#### struct `FStatusBarProgress`  
`struct FStatusBarProgress`  
_L49-64_
- desc: Data payload for progress bars in the status bar
- L51 _public function_ `FStatusBarProgress(FText InDisplayText, double InStartTime, FProgressNotificationHandle InHandle, int32 InTotalWorkToDo) : DisplayText(InDisplayText) , StartTime(InStartTime) , TotalWorkToDo(InTotalWorkToDo) , TotalWorkDone(0) , Handle(InHandle)`
- L59 _public member_ `FText DisplayText;`
- L60 _public member_ `double StartTime;`
- L61 _public member_ `int32 TotalWorkToDo;`
- L62 _public member_ `int32 TotalWorkDone;`
- L63 _public member_ `FProgressNotificationHandle Handle;`

#### class `SStatusBar`  
`class SStatusBar : public SCompoundWidget`  
_L66-231_
- inherits: `SCompoundWidget`
- L68 _private function_ `SLATE_BEGIN_ARGS(SStatusBar)`
- L70 _private prototype_ `SLATE_ARGUMENT_DEFAULT(bool, CreateSourceControlSection) = true;`
- L74 _public prototype_ `~SStatusBar();`
- L77 _public function_ `virtual bool SupportsKeyboardFocus() const` — SWidget interface
- L78 _public prototype_ `void Construct(const FArguments& InArgs, FName InStatusBarName, const TSharedRef<SDockTab> InParentTab, TArray<UStatusBarSubsystem::FTabIdAndButtonLabel>&& PanelDrawerSummons);`
- L87 _public prototype_ `void PushMessage(FStatusBarMessageHandle InHandle, const TAttribute<FText>& InMessage, const TAttribute<FText>& InHintText);` — Pushes a new status bar message @param InHandle	A handle to the message for clearing it later @param InMessage	The message to display @param InHintText	Optional hint text message.  This message will be highlighted to make it stand out
- L98 _public prototype_ `void PushMessage(FStatusBarMessageHandle InHandle, const TAttribute<FText>& InMessage, const TAttribute<FText>& InHintText, const TAttribute<const FSlateBrush*>& InIconBrush, const TAttribute<FSlateColor>& InIconColor);` — Pushes a new status bar message with a custom icon and color @param InHandle A handle to the message for clearing it later @param InMessage The message to display @param InHintText Optional hint text. Highlighted to stand out @param InIconBrush Custom icon brush. Pass nullptr to use the default help icon @param InIconColor Color/opacity for the icon, supports dynamic attributes for pulsing effects
- L106 _public prototype_ `void PopMessage(FStatusBarMessageHandle InHandle);` — Removes a message from the status bar.  When messages are removed the previous message on the stack (if any) is displayed @param InHandle	Handle to the status bar message to remove
- L111 _public prototype_ `void ClearAllMessages();` — Removes all messages from the status bar
- L119 _public prototype_ `void StartProgressNotification(FProgressNotificationHandle InHandle, FText DisplayText, int32 TotalWorkToDo);` — Called when a progress notification begins @param Handle			Handle to the notification @param DisplayText		Display text used to describe the type of work to the user @param TotalWorkToDo		Arbitrary number of work units to perform.
- L128 _public prototype_ `bool UpdateProgressNotification(FProgressNotificationHandle InHandle, int32 TotalWorkDone, int32 UpdatedTotalWorkToDo, FText UpdatedDisplayText);` — Called when a notification should be updated. @param InHandle				Handle to the notification that was previously created with StartProgressNotification @param TotalWorkDone			The total number of work units done for the notification. @param UpdatedTotalWorkToDo	UpdatedTotalWorkToDo. This value will be 0 if the total work did not change @param UpdatedDisplayText	Updated display text of the notification. This value will be empty if the text did not change
- L133 _public prototype_ `bool CancelProgressNotification(FProgressNotificationHandle InHandle);` — Called when a notification should be canceled
- L138 _public prototype_ `TSharedPtr<SDockTab> GetParentTab() const;` — Gets the owning major tab that this status bar is in
- L143 _public prototype_ `void RegisterDrawer(FWidgetDrawerConfig&& Drawer, int32 SlotIndex = INDEX_NONE);` — Registers a new drawer with this status bar. Registering will add a button to open and close the drawer
- L151 _public prototype_ `void UnregisterDrawer(FName DrawerId);` — Unregisters drawer with the given DrawerId. This will dismiss the drawer immediately if its opened, and destroy the status bar widget that opens/closes the drawer @param DrawerId name of the registered drawer to unregister
- L158 _public prototype_ `void OpenDrawer(const FName DrawerId);` — Opens a drawer @param DrawerId Name of the registered drawer to open
- L166 _public prototype_ `bool DismissDrawer(const TSharedPtr<SWidget>& NewlyFocusedWidget);` — Dismisses an open drawer with an animation.  The drawer contents are removed once the animation is complete @param NewlyFocusedWidget Optional widget to focus @return true if any open drawer was dismissed
- L172 _public prototype_ `void CloseDrawerImmediately(FName DrawerId = NAME_None);` — Closes a drawer immediately with no closing animation. Needed for when UI is shutting down or to prevent conflicts where a drawer is open in two places at once. @param DrawerId The name of the drawer to close. If no name is specified all drawers are closed immediately
- L175 _public prototype_ `bool IsDrawerOpened(const FName DrawerId) const;` — Is a specific registered drawer currently open
- L178 _public prototype_ `bool IsAnyOtherDrawerOpened(const FName DrawerId) const;` — Is any drawer other than the one specified by DrawerId opened
- L181 _public prototype_ `FName GetStatusBarName() const;` — Get unique name of this status bar
- L185 _private prototype_ `FSlateColor GetIconColorAndOpacity() const;`
- L186 _private prototype_ `const FSlateBrush* GetIconBrush() const;`
- L187 _private prototype_ `EVisibility GetIconVisibility() const;`
- L188 _private prototype_ `FText GetStatusBarMessage() const;`
- L190 _private prototype_ `TSharedRef<SWidget> MakeStatusBarToolBarWidget();`
- L191 _private prototype_ `TSharedRef<SWidget> MakeStatusMessageWidget();`
- L192 _private prototype_ `TSharedRef<SWidget> MakeProgressBar();`
- L193 _private prototype_ `TSharedPtr<SWidget> MakeSummonPanelDrawer(TArray<UStatusBarSubsystem::FTabIdAndButtonLabel>&& InTabIdAndLabels);`
- L195 _private prototype_ `FReply OnDrawerButtonClicked(const FName DrawerId);`
- L197 _private prototype_ `void RegisterStatusBarMenu();`
- L198 _private prototype_ `void RegisterSourceControlStatus();`
- L200 _private prototype_ `FStatusBarProgress* FindProgressNotification(FProgressNotificationHandle InHandle);`
- L202 _private prototype_ `void UpdateProgressStatus();`
- L203 _private prototype_ `void OpenProgressBar();`
- L204 _private prototype_ `void DismissProgressBar();`
- L206 _private prototype_ `void UpdateSummonPanelDrawerArrowRotation(const FTabManager& TabManager);`
- L207 _private prototype_ `FReply ToggleTabInPanelDrawer(FName TabId);`
- L208 _private prototype_ `FReply ClosePanelDrawer();`
- L210 _private prototype_ `TSharedRef<SWidget> OnGetProgressBarMenuContent();`
- L212 _private prototype_ `FName GetToolbarName() const;`
- L216 _private member_ `TArray<FStatusBarMessage> MessageStack;`
- L217 _private member_ `TArray<FStatusBarProgress> ProgressNotifications;`
- L219 _private member_ `TWeakPtr<SDockTab> ParentTab;`
- L220 _private member_ `TSharedPtr<SWidgetDrawer> WidgetDrawer;`
- L221 _private member_ `TSharedPtr<SStatusBarProgressArea> ProgressBar;`
- L223 _private member_ `TSharedPtr<SImage> PanelDrawerArrow;`
- L224 _private member_ `static TUniquePtr<FSlateRoundedBoxBrush> SummonPanelDrawerRoundedBox;`
- L226 _private member_ `const FSlateBrush* UpArrow = nullptr;`
- L227 _private member_ `const FSlateBrush* DownArrow = nullptr;`
- L230 _private member_ `bool bCreateSourceControlSection = true;` — Whether or not to create the source control section.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerTargetHeightChanged, float);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerTargetHeightChanged, float);`
- L27 _namespace_ `namespace StatusBarDrawerIds`
- L29 _variable_ `const FName ContentBrowser("Con` (scope `StatusBarDrawerIds`)
- L30 _variable_ `const FName OutputLog("Out` (scope `StatusBarDrawerIds`)

### `Source/Editor/StatusBar/Private/SourceControlMenuHelpers.h` (Private)


#### class `FSourceControlCommands`  
`class FSourceControlCommands : public TCommands<FSourceControlCommands>`  
_L14-59_
- inherits: `TCommands<FSourceControlCommands>`
- L17 _public prototype_ `FSourceControlCommands();`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L26 _private prototype_ `static void ConnectToSourceControl_Clicked();`
- L27 _private prototype_ `static bool ViewChangelists_CanExecute();`
- L28 _private prototype_ `static bool ViewChangelists_IsVisible();`
- L29 _private prototype_ `static void ViewChangelists_Clicked();`
- L30 _private prototype_ `static bool SubmitContent_CanExecute();`
- L31 _private prototype_ `static bool SubmitContent_IsVisible();`
- L32 _private prototype_ `static void SubmitContent_Clicked();`
- L33 _private prototype_ `static bool ViewSnapshotHistory_CanExecute();`
- L34 _private prototype_ `static bool ViewSnapshotHistory_IsVisible();`
- L35 _private prototype_ `static void ViewSnapshotHistory_Clicked();`
- L36 _private prototype_ `static bool ViewBranchExplorer_CanExecute();`
- L37 _private prototype_ `static bool ViewBranchExplorer_IsVisible();`
- L38 _private prototype_ `static void ViewBranchExplorer_Clicked();`
- L39 _private prototype_ `static bool CheckOutModifiedFiles_CanExecute();`
- L40 _private prototype_ `static bool CheckOutModifiedFiles_IsVisible();`
- L41 _private prototype_ `static void CheckOutModifiedFiles_Clicked();`
- L42 _private prototype_ `static bool RevertAllModifiedFiles_CanExecute();`
- L43 _private prototype_ `static void RevertAllModifiedFiles_Clicked();`
- L49 _public member_ `TSharedPtr< FUICommandInfo > ConnectToSourceControl;` — Source Control Commands
- L50 _public member_ `TSharedPtr< FUICommandInfo > ChangeSourceControlSettings;`
- L51 _public member_ `TSharedPtr< FUICommandInfo > ViewChangelists;`
- L52 _public member_ `TSharedPtr< FUICommandInfo > SubmitContent;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > ViewSnapshotHistory;`
- L54 _public member_ `TSharedPtr< FUICommandInfo > ViewBranchExplorer;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > CheckOutModifiedFiles;`
- L56 _public member_ `TSharedPtr< FUICommandInfo > RevertAll;`
- L58 _public member_ `static TSharedRef<FUICommandList> ActionList;`

#### class `FSourceControlMenuHelpers`  
`class FSourceControlMenuHelpers`  
_L61-95_
- L66 _private function_ `FSourceControlMenuHelpers()`
- L76 _private member_ `static EQueryState QueryState;`
- L79 _public prototype_ `static void CheckSourceControlStatus();`
- L80 _public prototype_ `static TSharedRef<SWidget> MakeSourceControlStatusWidget();`
- L83 _private prototype_ `static void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L84 _private prototype_ `static TSharedRef<SWidget> GenerateSourceControlMenuContent();`
- L85 _private prototype_ `static TSharedRef<SWidget> GenerateCheckInComboButtonContent();`
- L86 _private prototype_ `static FText GetSourceControlStatusText();`
- L87 _private prototype_ `static FText GetSourceControlTooltip();`
- L88 _private prototype_ `static const FSlateBrush* GetSourceControlIconBadge();`
- L92 _private member_ `FDelegateHandle SourceControlProviderChangedHandle;` — Delegate handles
- L93 _private member_ `FDelegateHandle SourceControlStateChangedHandle;`

#### enum `FSourceControlMenuHelpers::EQueryState`  
`enum EQueryState`  
_L69-74_
- L71 _public enumerator_ `NotQueried`
- L72 _public enumerator_ `Querying`
- L73 _public enumerator_ `Queried`

### `Source/Editor/StatusBar/Public/GlobalStatusBarExtension.h` (Public)


#### struct `IGlobalStatusBarExtension`  
`struct IGlobalStatusBarExtension`  
_L11-20_
- desc: Extension point for extending the functionality of status bars across the entire editor.
- L13 _public prototype_ `virtual ~IGlobalStatusBarExtension() = default;`
- L16 _public function_ `virtual void ExtendContentBrowserDrawer(FWidgetDrawerConfig& WidgetDrawerConfig)` — Called before the content browser drawer is registered in the status bar.
- L19 _public function_ `virtual void ExtendOutputLogDrawer(FWidgetDrawerConfig& WidgetDrawerConfig)` — Called before the output log drawer is registered in the status bar.

### `Source/Editor/StatusBar/Public/StatusBarModule.h` (Public)


#### class `IStatusBarModule`  
`class IStatusBarModule : public IModuleInterface`  
_L13-26_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L17 _public function_ `static inline IStatusBarModule& Get()`
- L22 _public function_ `static inline bool IsAvailable()`

### `Source/Editor/StatusBar/Public/StatusBarSubsystem.h` (Public)


#### struct `FStatusBarMessageHandle`  
`struct FStatusBarMessageHandle`  
_L30-58_
- L34 _public function_ `FStatusBarMessageHandle() : Id(INDEX_NONE)`
- L38 _public function_ `bool IsValid()`
- L43 _public function_ `void Reset()`
- L48 _public function_ `bool operator==(const FStatusBarMessageHandle& OtherHandle) const`
- L53 _private function_ `FStatusBarMessageHandle(int32 InId) : Id(InId)`
- L57 _private member_ `int32 Id;`

#### enum `UE::Editor::Toolbars::ECreateStatusBarOptions`  
`enum class ECreateStatusBarOptions : uint8`  
_L63-69_
- desc: Options used to specify what parts (if any) of the status bar should be hidden.
- L65 _public enumerator_ `Default = 0`
- L66 _public enumerator_ `HideContentBrowser = 1`
- L67 _public enumerator_ `HideOutputLog = 1 << 1`
- L68 _public enumerator_ `HideSourceControl = 1 << 2`

#### struct `FStatusBarData`  
`struct FStatusBarData`  
_L73-77_
- L75 _public member_ `TWeakPtr<SStatusBar> StatusBarWidget;`
- L76 _public member_ `TSharedPtr<SWidget> ConsoleEditBox;`

#### class `UStatusBarSubsystem`  
`class UStatusBarSubsystem : public UEditorSubsystem, public IProgressNotificationHandler`  
_L80-299_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,IProgressNotificationHandler`
- L89 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override final;` — Prepares for use
- L94 _public prototype_ `virtual void Deinitialize() override final;` — Internal cleanup
- L103 _public prototype_ `bool ToggleDebugConsole(TSharedRef<SWindow> ParentWindow, bool bAlwaysToggleDrawer=false);` — Focuses the debug console or opens the output log drawer on the status bar for status bar residing in the passed in parent window @param ParentWindow			The parent window of the status bar @param bAlwaysToggleDrawer	If true, the output log drawer will be toggled without focusing the debug console first @return true if a status bar debug console was found and focused
- L110 _public prototype_ `bool OpenOutputLogDrawer();` — Opens the output log drawer for a status bar residing in the active window @return true if the output log was opened
- L117 _public prototype_ `bool OpenContentBrowserDrawer();` — Opens the content browser drawer for a status bar residing in the active window @return true if the content browser was opened
- L124 _public prototype_ `bool ToggleContentBrowserDrawer();` — Opens or closes the content browser drawer for a status bar residing in the active window @return true if the content browser was toggled or false if no status bar in the active window was found
- L131 _public prototype_ `bool DismissContentBrowserDrawer();` — Closes the content browser drawer for a status bar residing in the active window @return true if the content browser was dismissed
- L136 _public prototype_ `bool TryToggleDrawer(const FName DrawerId);` — Tries to toggle the given drawer
- L141 _public prototype_ `bool ForceDismissDrawer();` — Forces all drawers to dismiss. Usually it dismisses with focus. Only call this if there is some reason an open drawer would be invalid for the current state of the editor.
- L149 _public prototype_ `TSharedRef<SWidget> MakeStatusBarWidget(FName UniqueStatusBarName, const TSharedRef<SDockTab>& InParentTab, UE::Editor::Toolbars::ECreateStatusBarOptions CreateStatusBarOptions = UE::Editor::Toolbars::ECreateStatusBarOptions::Default);` — Creates a new instance of a status bar widget @param StatusBarName	The name of the status bar for updating it later. This name must be unique. You can use the instance number of an fname to generate a unique fname for comparison but a non-unique one for serialization of status bar data. I.E all asset editors of a specific type will be saved the same but at runtime will be indentified uniquely. This is usally what you want. @param ParentTab	Parent tab of the status bar.
- L154 _public prototype_ `bool ActiveWindowHasStatusBar() const;` — @return true if a status bar was found for the active window
- L159 _public prototype_ `bool ActiveWindowBehindNotificationHasStatusBar();` — @return true if a status bar was found for the active window immediately behind a Notification Window
- L168 _public prototype_ `void RegisterDrawer(FName StatusBarName, FWidgetDrawerConfig&& Drawer, int32 SlotIndex = INDEX_NONE);` — Creates a new instance of a status bar widget @param StatusBarName	The name of the status bar to add the drawer to @param Drawer		The drawer to add to the status bar @param SlotIndex		The position at which to add the new drawer
- L176 _public prototype_ `void UnregisterDrawer(FName StatusBarName, FName DrawerId);` — Unregisters and destroys the drawer with the given DrawerId @param StatusBarName	The name of the status bar to unregister the drawer from @param DrawerId		the unique name id of the drawer to unregister
- L186 _public prototype_ `FStatusBarMessageHandle PushStatusBarMessage(FName StatusBarName, const TAttribute<FText>& InMessage, const TAttribute<FText>& InHintText);` — Pushes a new status bar message @param StatusBarName	The name of the status bar to push messages to @param InMessage		The message to display @param InHintText	Optional hint text message.  This message will be highlighted to make it stand out @return	A handle to the message for clearing it later
- L187 _public prototype_ `FStatusBarMessageHandle PushStatusBarMessage(FName StatusBarName, const TAttribute<FText>& InMessage);`
- L200 _public prototype_ `FStatusBarMessageHandle PushStatusBarMessage(FName StatusBarName, const TAttribute<FText>& InMessage, const TAttribute<FText>& InHintText, const TAttribute<const FSlateBrush*>& InIconBrush, const TAttribute<FSlateColor>& InIconColor);` — Pushes a new status bar message with a custom icon brush and color. Useful for contextual indicators (e.g. a red record icon during recording). @param StatusBarName The name of the status bar to push messages to @param InMessage The message to display @param InHintText Optional hint text. Highlighted to stand out @param InIconBrush Custom icon brush. Pass nullptr to use the default help icon @param InIconColor Color/opacity for the icon, supports dynamic attributes for pulsing effects @return A handle to the message for clearing it later
- L209 _public prototype_ `void PopStatusBarMessage(FName StatusBarName, FStatusBarMessageHandle InHandle);` — Removes a message from the status bar.  When messages are removed the previous message on the stack (if any) is displayed @param StatusBarName	The name of the status bar to remove from @param InHandle		Handle to the status bar message to remove
- L216 _public prototype_ `void ClearStatusBarMessages(FName StatusBarName);` — Removes all messages from the status bar @param StatusBarName	The name of the status bar to remove from
- L224 _public prototype_ `IGlobalStatusBarExtension& RegisterGlobalStatusBarExtension(TUniquePtr<IGlobalStatusBarExtension>&& Extension);` — Registers a new global status bar extension. @param Extension The extension to register @return A reference to the extension interface, which can be later used to unregister the extension
- L232 _public prototype_ `TUniquePtr<IGlobalStatusBarExtension> UnregisterGlobalStatusBarExtension(IGlobalStatusBarExtension* Extension);` — Unregisters an existing status bar extension. @param Extension Reference returned by RegisterGlobalStatusBarExtension containing the extension to unregister @return An owned instance of the extension that was registered, or null if the extension was not found
- L236 _public typedef_ `typedef TPair<FName, FText> FTabIdAndButtonLabel;`
- L240 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRegisterPanelDrawerSummonDelegate, TArray<FTabIdAndButtonLabel>& , const TSharedRef<SDockTab>& );`
- L247 _public prototype_ `void UnregisterPanelDrawerSummon(FDelegateHandle ResgistrationHandle);`
- L251 _private prototype_ `virtual void StartProgressNotification(FProgressNotificationHandle Handle, FText DisplayText, int32 TotalWorkToDo) override;` — IProgressNotificationHandler interface
- L252 _private prototype_ `virtual void UpdateProgressNotification(FProgressNotificationHandle Handle, int32 TotalWorkDone, int32 UpdatedTotalWorkToDo, FText UpdatedDisplayText) override;`
- L253 _private prototype_ `virtual void CancelProgressNotification(FProgressNotificationHandle Handle) override;`
- L264 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EDrawerTriggerMode);`
- L266 _private prototype_ `bool TriggerContentBrowser(EDrawerTriggerMode DrawerTriggerMode);`
- L268 _private prototype_ `void OnDebugConsoleClosed(TWeakPtr<SStatusBar> OwningStatusBar);`
- L269 _private prototype_ `void CreateContentBrowserIfNeeded();`
- L270 _private prototype_ `void CreateAndShowNewUserTipIfNeeded(TSharedPtr<SWindow> ParentWindow, bool bIsRunningStartupDialog);`
- L271 _private prototype_ `const FString GetNewUserTipState() const;`
- L272 _private prototype_ `void CreateAndShowOneTimeIndustryQueryIfNeeded(TSharedPtr<SWindow> ParentWindow, bool bIsRunningStartupDialog);`
- L273 _private prototype_ `static const FString GetOneTimeStateWithFallback(const FString StoreId, const FString SectionName, const FString KeyName, const FString FallbackIniLocation, const FString FallbackIniKey);`
- L274 _private prototype_ `static void SetOneTimeStateWithFallback(const FString StoreId, const FString SectionName, const FString KeyName, const FString FallbackIniLocation, const FString FallbackIniKey);`
- L276 _private prototype_ `TSharedPtr<SStatusBar> GetStatusBar(FName StatusBarName) const;`
- L277 _private prototype_ `TSharedRef<SWidget> OnGetContentBrowser();`
- L278 _private prototype_ `void OnContentBrowserOpened(FName StatusBarWithDrawerName);`
- L279 _private prototype_ `void OnContentBrowserDismissed(const TSharedPtr<SWidget>& NewlyFocusedWidget);`
- L280 _private prototype_ `void HandleDeferredOpenContentBrowser(TSharedPtr<SWindow> ParentWindow);`
- L282 _private prototype_ `TSharedRef<SWidget> OnGetOutputLog();`
- L283 _private prototype_ `void OnOutputLogOpened(FName StatusBarWithDrawerName);`
- L284 _private prototype_ `void OnOutputLogDismised(const TSharedPtr<SWidget>& NewlyFocusedWidget);`
- L286 _private prototype_ `void OnDebugConsoleDrawerClosed();`
- L288 _private member_ `TMap<FName, FStatusBarData> StatusBars;`
- L289 _private member_ `TWeakPtr<SWidget> PreviousKeyboardFocusedWidget;`
- L291 _private member_ `TSharedPtr<SWidget> StatusBarContentBrowser;` — The floating content browser that is opened via the content browser button in the status bar
- L292 _private member_ `TSharedPtr<SWidget> StatusBarOutputLog;`
- L293 _private member_ `static int32 MessageHandleCounter;`
- L294 _private member_ `TArray<TUniquePtr<IGlobalStatusBarExtension>> GlobalStatusBarExtensions;`
- L297 _private member_ `FRegisterPanelDrawerSummonDelegate RegisteredPanelDrawerSummons;`

#### enum `UStatusBarSubsystem::EDrawerTriggerMode`  
`enum class EDrawerTriggerMode : uint8`  
_L255-263_
- L257 _public enumerator_ `None = 0`
- L259 _public enumerator_ `Open = 1 << 0`
- L260 _public enumerator_ `Dismiss = 1 << 1`
- L262 _public enumerator_ `Toggle = Open | Dismiss`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API STATUSBAR_API`
- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace Editor` (scope `UE`)
- L60 _namespace_ `namespace Toolbars` (scope `UE::Editor`)
- L70 _prototype_ `ENUM_CLASS_FLAGS(ECreateStatusBarOptions);` (scope `UE::Editor::Toolbars`)
- L240 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRegisterPanelDrawerSummonDelegate, TArray<FTabIdAndButtonLabel>& , const TSharedRef<SDockTab>& );`
