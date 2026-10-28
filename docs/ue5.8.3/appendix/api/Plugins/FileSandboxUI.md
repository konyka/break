# Plugins / FileSandboxUI

- module root: `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI`
- headers: 13; symbols: 128
- symbol kinds: class=11, delegate=1, function=29, macro=2, member=14, namespace=30, prototype=40, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, SlateCore, ToolWidgets
- PublicDependencyModuleNames: Core, FileSandboxCore, Slate

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Private/EntryPoint/ExternalSandboxActiveViewModel.h` (Private)


#### class `UE::FileSandboxUI::FExternalSandboxActiveViewModel`  
`class FExternalSandboxActiveViewModel : public IExternalSandboxActiveViewModel`  
_L13-39_
- inherits: `IExternalSandboxActiveViewModel`
- desc: This view-model is associated with an ISandboxEntryPoint. The UI is shown when the sandbox is not owned by its entry point.
- L17 _public prototype_ `explicit FExternalSandboxActiveViewModel(const TSharedRef<ISandboxEntryPoint>& InOwningEntryPoint);`
- L21 _public prototype_ `virtual bool IsExternalSandboxActive() const override;`
- L22 _public prototype_ `virtual void SummonSandboxOwnerUI() const override;`
- L23 _public prototype_ `virtual bool IsSummoningSupported() const override;`
- L24 _public prototype_ `virtual FText GetSummonActionLabel() const override;`
- L25 _public prototype_ `virtual FText GetExternalSandboxActiveText() const override;`
- L26 _public function_ `virtual FSimpleMulticastDelegate& OnVisibilityChanged() override`
- L32 _private member_ `const TSharedRef<ISandboxEntryPoint> OwningEntryPoint;` — The entry point for which the UI is being displayed. Used to determine whether an external sandbox is active.
- L35 _private member_ `FSimpleMulticastDelegate OnVisibilityChangedDelegate;` — Event invoked when the visibility of the widget should change.
- L37 _private function_ `void OnSandboxStartup(FileSandboxCore::ISandboxInstance& SandboxInstance)`
- L38 _private function_ `void OnSandboxShutdown()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Private/EntryPoint/SandboxEntryPointManager.h` (Private)


#### class `UE::FileSandboxUI::FSandboxEntryPointManager`  
`class FSandboxEntryPointManager : public ISandboxEntryPointRegistry`  
_L10-28_
- inherits: `ISandboxEntryPointRegistry`
- L15 _public prototype_ `virtual void RegisterEntryPoint(const TSharedRef<ISandboxEntryPoint>& InEntryPoint) override;`
- L16 _public prototype_ `virtual void UnregisterEntryPoint(const TSharedRef<ISandboxEntryPoint>& InEntryPoint) override;`
- L17 _public prototype_ `virtual TSharedPtr<ISandboxEntryPoint> FindOwnerOfActiveSandbox() const override;`
- L18 _public function_ `virtual FSimpleMulticastDelegate& OnEntryPointsChanged() override`
- L24 _private member_ `TArray<TWeakPtr<ISandboxEntryPoint>> EntryPoints;` — The entry points this manager knows about.
- L27 _private member_ `FSimpleMulticastDelegate OnEntryPointsChangedDelegate;` — Event invoked when the registered entry points have changed.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Private/EntryPoint/Widgets/SExternalSandboxActiveOverlay.h` (Private)


#### class `UE::FileSandboxUI::SExternalSandboxActiveOverlay`  
`class SExternalSandboxActiveOverlay : public SCompoundWidget`  
_L16-33_
- inherits: `SCompoundWidget`
- desc: Use this overlay in your editor system to tell the user that the engine is sandboxed by another editor system. This widget shows a button to summon the other system's UI.
- L20 _public function_ `SLATE_BEGIN_ARGS(SExternalSandboxActiveOverlay)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IExternalSandboxActiveViewModel>& InViewModel);`
- L28 _private member_ `TSharedPtr<IExternalSandboxActiveViewModel> ViewModel;` — View model that we're displaying.
- L30 _private prototype_ `FText GetTitleText() const;`
- L31 _private prototype_ `FText GetSummonButtonLabel() const;`
- L32 _private prototype_ `FReply OnSummonClicked();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Private/FileSandboxStyle.h` (Private)


#### class `UE::FileSandboxUI::FFileSandboxStyle`  
`class FFileSandboxStyle final : public FSlateStyleSet`  
_L13-21_
- inherits: `FSlateStyleSet`
- L17 _public prototype_ `static FFileSandboxStyle& Get();`
- L19 _public prototype_ `FFileSandboxStyle();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Private/FileSandboxUIModule.h` (Private)


#### class `UE::FileSandboxUI::FFileSandboxUIModule`  
`class FFileSandboxUIModule : public IFileSandboxUIModule`  
_L11-28_
- inherits: `IFileSandboxUIModule`
- desc: Knows about editor systems that start sandboxes.
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public function_ `virtual ISandboxEntryPointRegistry& GetEntryPointRegistry() override`
- L27 _private member_ `TUniquePtr<FSandboxEntryPointManager> EntryPoints;` — Knows about editor systems that start sandboxes.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/EntryPoint/EntryPointWidgetFactory.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FILESANDBOXUI_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L18 _prototype_ `TSharedRef<SWidget> MakeExternalSandboxActiveOverlay(const TSharedRef<IExternalSandboxActiveViewModel>& InViewModel);` (scope `UE::FileSandboxUI`) — @return Widget to overlay your UI with when you want to tell the user that a sandbox owned by another editor system is blocking your feature.
- L21 _prototype_ `TSharedRef<IExternalSandboxActiveViewModel> MakeExternalSandboxActiveViewModel( const TSharedRef<ISandboxEntryPoint>& InOwningEntryPoint );` (scope `UE::FileSandboxUI`) — @return A view model for the entry point.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/EntryPoint/IExternalSandboxActiveViewModel.h` (Public)


#### class `UE::FileSandboxUI::IExternalSandboxActiveViewModel`  
`class IExternalSandboxActiveViewModel`  
_L14-35_
- desc: This view-model is used for UI telling the user that a sandbox cannot currently be started. Usually, the widget displays a message that another editor system has started a sandbox and provides a way to summon the UI of the other system.
- L19 _public prototype_ `virtual bool IsExternalSandboxActive() const = 0;` — @return Whether the mutex widget should be displayed, i.e. a sandbox is active and not owned by the current ISandboxEntryPoint.
- L22 _public prototype_ `virtual void SummonSandboxOwnerUI() const = 0;` — Summons the UI of the system owning the active sandbox.
- L24 _public prototype_ `virtual bool IsSummoningSupported() const = 0;` — @return Whether the UI (e.g. button) for summoning the sandbox owner should be shown.
- L26 _public prototype_ `virtual FText GetSummonActionLabel() const = 0;` — @return The label to display for the summon action, e.g. could be displayed in button.
- L29 _public prototype_ `virtual FText GetExternalSandboxActiveText() const = 0;` — @return A text explaining the current system is not available while the external system is active. Empty of no external sandbox is active.
- L32 _public prototype_ `virtual FSimpleMulticastDelegate& OnVisibilityChanged() = 0;` — Event invoked when the visibility of the widget should change.
- L34 _public prototype_ `virtual ~IExternalSandboxActiveViewModel() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/EntryPoint/ISandboxEntryPoint.h` (Public)


#### class `UE::FileSandboxUI::ISandboxEntryPoint`  
`class ISandboxEntryPoint`  
_L12-29_
- desc: Implemented by editor systems that makes use of the sandbox feature.
- L17 _public prototype_ `virtual void SummonProviderUI() = 0;` — Summons the UI in which the sandboxes
- L23 _public prototype_ `virtual FText GetEntryPointLabel() const = 0;` — @return The name of the UI that will be summoned. This is displayed e.g. in a summon button. This should be an app name, like "Multi-User" or "Sandboxed Editing".
- L26 _public prototype_ `virtual bool OwnsSandbox(const FileSandboxCore::ISandboxInstance& InSandbox) const = 0;` — @return Whether this provider owns the active sandbox instance.
- L28 _public prototype_ `virtual ~ISandboxEntryPoint() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/EntryPoint/ISandboxEntryPointRegistry.h` (Public)


#### class `UE::FileSandboxUI::ISandboxEntryPointRegistry`  
`class ISandboxEntryPointRegistry`  
_L15-31_
- desc: Knows about editor systems that start sandboxes.
- L20 _public prototype_ `virtual void RegisterEntryPoint(const TSharedRef<ISandboxEntryPoint>& InEntryPoint) = 0;` — Registers the entry point.
- L22 _public prototype_ `virtual void UnregisterEntryPoint(const TSharedRef<ISandboxEntryPoint>& InEntryPoint) = 0;` — Unregisters the entry point.
- L25 _public prototype_ `virtual TSharedPtr<ISandboxEntryPoint> FindOwnerOfActiveSandbox() const = 0;` — Finds the entry point that owns the active sandbox.
- L28 _public prototype_ `virtual FSimpleMulticastDelegate& OnEntryPointsChanged() = 0;` — Event invoked when the registered entry points have changed.
- L30 _public prototype_ `virtual ~ISandboxEntryPointRegistry() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/IFileSandboxUIModule.h` (Public)


#### class `UE::FileSandboxUI::IFileSandboxUIModule`  
`class IFileSandboxUIModule : public IModuleInterface`  
_L12-33_
- inherits: `IModuleInterface`
- L22 _public function_ `static IFileSandboxUIModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L32 _public prototype_ `virtual ISandboxEntryPointRegistry& GetEntryPointRegistry() = 0;` — @return Manager with which you can register editor entry points into the sandbox system.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/Persist/Feedback/PersistSummary.h` (Public)


#### struct `UE::FileSandboxUI::FPersistSummary`  
`struct FPersistSummary`  
_L11-22_
- desc: Summary of a persist operation.
- L14 _public member_ `int32 Edited = 0;` — Number of edited files.
- L16 _public member_ `int32 Added = 0;` — Number of added files.
- L18 _public member_ `int32 Deleted = 0;` — Number of deletes files.
- L21 _public member_ `TArray<FString> FailedFiles;` — Non-sandbox paths of files that were not persisted.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/Persist/Feedback/SlowTaskPersistFeedback.h` (Public)


#### class `UE::FileSandboxUI::FSlowTaskPersistFeedback`  
`class FSlowTaskPersistFeedback : public FileSandboxCore::IPersistFeedback`  
_L18-54_
- inherits: `FileSandboxCore::IPersistFeedback`
- desc: Starts a slow task for the duration of the persist operation. Remember that nested of FScopedSlowTask works.
- L23 _public member_ `FScopedSlowTask SlowTask;` — Spawns the progress bar.
- L26 _public member_ `FFormatPathDelegate FormatPathDelegate;` — Optional delegate that produces the progress bar text.
- L28 _public function_ `explicit FSlowTaskPersistFeedback(int32 InNumFilesToPersist, FFormatPathDelegate InFormatPath = FFormatPathDelegate()) : SlowTask(InNumFilesToPersist) , FormatPathDelegate(InFormatPath)`
- L34 _public function_ `virtual void StartFile(const TCHAR* InFilename) override`
- L44 _public function_ `virtual void HandleSuccess(const TCHAR* InFilename) override`
- L45 _public function_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) override`
- L46 _public function_ `virtual void HandleError_Checkout(const TCHAR* InFilename) override`
- L47 _public function_ `virtual void HandleError_Revert(const TCHAR* InFilename) override`
- L48 _public function_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) override`
- L49 _public function_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) override`
- L50 _public function_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) override`
- L51 _public function_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) override`
- L52 _public function_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FFormatPathDelegate, const TCHAR* InFileName);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FFormatPathDelegate, const TCHAR* InFileName);` (scope `UE::FileSandboxUI`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxUI/Public/Persist/Feedback/SummaryPersistFeedback.h` (Public)


#### class `UE::FileSandboxUI::FSummaryPersistFeedback`  
`class FSummaryPersistFeedback : public FileSandboxCore::IPersistFeedback`  
_L19-53_
- inherits: `FileSandboxCore::IPersistFeedback`
- desc: Fills in a FPersistSummary so you
- L21 _private member_ `TMap<FString, FileSandboxCore::ESandboxFileChange> FileActions;`
- L26 _public member_ `FPersistSummary Summary;` — The summary of the operation.
- L28 _public prototype_ `explicit FSummaryPersistFeedback( TConstArrayView<FString> InPersistedFiles, TConstArrayView<FileSandboxCore::ESandboxFileChange> InFileActions );`
- L33 _public function_ `explicit FSummaryPersistFeedback(const FileSandboxCore::FGatheredFileChanges& InChanges) : FSummaryPersistFeedback(InChanges.NonSandboxPaths, InChanges.FileActions)`
- L38 _public function_ `virtual void StartFile(const TCHAR* InFilename) override`
- L39 _public prototype_ `virtual void HandleSuccess(const TCHAR* InFilename) override;`
- L40 _public function_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) override`
- L41 _public function_ `virtual void HandleError_Checkout(const TCHAR* InFilename) override`
- L42 _public function_ `virtual void HandleError_Revert(const TCHAR* InFilename) override`
- L43 _public function_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) override`
- L44 _public function_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) override`
- L45 _public function_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) override`
- L46 _public function_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) override`
- L47 _public function_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) override`
- L52 _private prototype_ `void HandleError(const TCHAR* InToFilename);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API FILESANDBOXUI_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FileSandboxUI` (scope `UE`)
