# Developer / SourceControlCheckInPrompt

- module root: `Source/Developer/SourceControlCheckInPrompt`
- headers: 3; symbols: 36
- symbol kinds: class=3, function=4, member=9, prototype=20
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, SourceControl, SourceControlWindows, UnrealEd

### `Source/Developer/SourceControlCheckInPrompt/Private/SourceControlCheckInPromptModule.h` (Private)


#### class `FSourceControlCheckInPromptModule`  
`class FSourceControlCheckInPromptModule : public ISourceControlCheckInPromptModule`  
_L13-56_
- inherits: `ISourceControlCheckInPromptModule`
- L16 _public prototype_ `FSourceControlCheckInPromptModule();`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual void ShowModal(const FText& InMessage) override;` — ISourceControlCheckInPromptModule implementation
- L24 _public prototype_ `virtual void ShowToast(const FText& InMessage) override;`
- L31 _public function_ `static FSourceControlCheckInPromptModule& Get()` — Gets a reference to the source control check in prompt module instance. @return A reference to the source control check in prompt module.
- L36 _public function_ `static FSourceControlCheckInPromptModule* TryGet()`
- L42 _protected prototype_ `void OnNotificationCheckInClicked();`
- L43 _protected prototype_ `void OnNotificationDismissClicked();`
- L45 _protected prototype_ `void OnProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);`
- L49 _private member_ `TSharedPtr<FSourceControlCheckInPrompter> SourceControlCheckInPrompter;` — The prompter which triggers a periodic prompt
- L52 _private member_ `TWeakPtr<SNotificationItem> CheckInNotification;` — The notification toast that a check-in is recommended
- L55 _private member_ `FDelegateHandle ProviderChangedHandle;` — The delegate handle for provider changes

### `Source/Developer/SourceControlCheckInPrompt/Private/SourceControlCheckInPrompter.h` (Private)


#### class `FSourceControlCheckInPrompter`  
`class FSourceControlCheckInPrompter : public TSharedFromThis<FSourceControlCheckInPrompter>`  
_L12-85_
- inherits: `TSharedFromThis<FSourceControlCheckInPrompter>`
- L15 _public prototype_ `FSourceControlCheckInPrompter();`
- L16 _public prototype_ `virtual ~FSourceControlCheckInPrompter();`
- L21 _public prototype_ `void Init();` — Initializes the instance.
- L30 _private prototype_ `void OnPackageSaved(const FString& Filename, UPackage* Pkg, FObjectPostSaveContext ObjectSaveContext);` — Called when a package has been saved. @param Filename The filename the package was saved to @param Obj The package that was saved
- L36 _private prototype_ `void OnStartPrompt();` — Called when a prompt flow should start, which might result in one being shown if it's been over a day since the last commit.
- L41 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Called when an executed source control operation completes.
- L47 _private prototype_ `bool OnAttemptPrompt(float);` — Called when a check-in prompt should attempted to be shown. @param DeltaTime argument is the time since the last game frame
- L53 _private prototype_ `bool IsPromptAllowed() const;` — Checks if it's allowed to display the periodic check-in prompt. The prompt is only expected to be shown once every X hours.
- L59 _private prototype_ `bool IsGetSubmittedChangelistsAllowed() const;` — Checks if it's allow to perform an asynchronous get submitted changelist operation. The operation is only expected to be executed once every X minutes.
- L64 _private prototype_ `void CheckPrompt();` — Called when a check should happen whether a prompt should be shown.
- L68 _private member_ `FString PromptFlowMapName;` — When non empty, contains the package name of the map the prompt will be shown for
- L71 _private member_ `TMap<FString, FDateTime> TimeCheckInPromptShown;` — Time the last prompt was shown by map name
- L74 _private member_ `TMap<FString, FDateTime> TimeGetSubmittedChangelistsExecuted;` — Time the last get submitted changelists operation was performed by map name
- L77 _private member_ `FString ProjectDirectory;` — The project directory user is working in
- L80 _private member_ `FDateTime ProjectActivationTime;` — The project activation time (eg: when was it opened)
- L83 _private member_ `bool bPromptDelayed;` — The prompt has been delayed

### `Source/Developer/SourceControlCheckInPrompt/Public/ISourceControlCheckInPromptModule.h` (Public)


#### class `ISourceControlCheckInPromptModule`  
`class ISourceControlCheckInPromptModule : public IModuleInterface`  
_L10-42_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void ShowModal(const FText& InMessage) = 0;` — Shows a check-in prompt reminding the user that it's important to frequently save their work. @param InMessage		The message to display in the message box
- L23 _public prototype_ `virtual void ShowToast(const FText& InMessage) = 0;` — Shows a check-in toast reminder the user that it's important to frequently save their work. @param InMessage		The message to display in the toast
- L31 _public function_ `static inline ISourceControlCheckInPromptModule& Get()` — Gets a reference to the source control check in prompt module instance. @return A reference to the source control check in module.
- L37 _public function_ `static inline ISourceControlCheckInPromptModule* TryGet()`
