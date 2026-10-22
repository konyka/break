# Plugins / SequenceValidator

- module root: `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator`
- headers: 14; symbols: 202
- symbol kinds: class=16, delegate=2, function=23, member=43, namespace=29, prototype=84, struct=2, typedef=3
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, ContentBrowser, Core, CoreUObject, Engine, InputCore, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTracks, Projects, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/SequenceValidatorCommands.h` (Private)


#### class `UE::Sequencer::FSequenceValidatorCommands`  
`class FSequenceValidatorCommands : public TCommands<FSequenceValidatorCommands>`  
_L15-26_
- inherits: `TCommands<FSequenceValidatorCommands>`
- L19 _public prototype_ `FSequenceValidatorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> StartValidation;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/SequenceValidatorStyle.h` (Private)


#### class `UE::Sequencer::FSequenceValidatorStyle`  
`class FSequenceValidatorStyle final : public FSlateStyleSet`  
_L13-25_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the sequence validator.
- L17 _public prototype_ `FSequenceValidatorStyle();`
- L18 _public prototype_ `virtual ~FSequenceValidatorStyle();`
- L20 _public prototype_ `static TSharedRef<FSequenceValidatorStyle> Get();`
- L24 _private member_ `static TSharedPtr<FSequenceValidatorStyle> Singleton;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Validation/Rules/SequenceValidationRule_DuplicateKeys.h` (Private)


#### class `UE::Sequencer::FSequenceValidationRule_DuplicateKeys`  
`class FSequenceValidationRule_DuplicateKeys : public FSequenceValidationRule`  
_L13-22_
- inherits: `FSequenceValidationRule`
- desc: A validation rule that warns about duplicate keys on the same channel.
- L17 _public prototype_ `static FSequenceValidationRuleInfo MakeRuleInfo();`
- L21 _protected prototype_ `virtual void OnRun(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Validation/Rules/SequenceValidationRule_SectionAlignments.h` (Private)


#### class `UE::Sequencer::FSequenceValidationRule_SectionAlignments`  
`class FSequenceValidationRule_SectionAlignments : public FSequenceValidationRule`  
_L14-23_
- inherits: `FSequenceValidationRule`
- desc: A validation rule that checks that sections throughout the sequence hierarchy are correctly aligned to "important times" such as camera cuts and start/end times.
- L18 _public prototype_ `static FSequenceValidationRuleInfo MakeRuleInfo();`
- L22 _protected prototype_ `virtual void OnRun(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Validation/Rules/SequenceValidationRule_UnassignedBindingsAndAssets.h` (Private)


#### class `UE::Sequencer::FSequenceValidationRule_UnassignedBindingsAndAssets`  
`class FSequenceValidationRule_UnassignedBindingsAndAssets : public FSequenceValidationRule`  
_L13-22_
- inherits: `FSequenceValidationRule`
- desc: A validation rule that checks that sections reference valid assets.
- L17 _public prototype_ `static FSequenceValidationRuleInfo MakeRuleInfo();`
- L21 _protected prototype_ `virtual void OnRun(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Validation/Rules/SequenceValidationRule_WholeSectionRanges.h` (Private)


#### class `UE::Sequencer::FSequenceValidationRule_WholeSectionRanges`  
`class FSequenceValidationRule_WholeSectionRanges : public FSequenceValidationRule`  
_L13-22_
- inherits: `FSequenceValidationRule`
- desc: A validation rule that checks that most sections have start/end times that are on whole frames.
- L17 _public prototype_ `static FSequenceValidationRuleInfo MakeRuleInfo();`
- L21 _protected prototype_ `virtual void OnRun(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Widgets/SSequenceValidator.h` (Private)


#### class `UE::Sequencer::SSequenceValidator`  
`class SSequenceValidator : public SCompoundWidget`  
_L24-67_
- inherits: `SCompoundWidget`
- L28 _public member_ `static const FName WindowName;`
- L29 _public member_ `static const FName MenubarName;`
- L31 _public prototype_ `static void RegisterTabSpawners();`
- L32 _public prototype_ `static TSharedRef<SDockTab> SpawnSequenceValidator(const FSpawnTabArgs& Args);`
- L33 _public prototype_ `static void UnregisterTabSpawners();`
- L37 _public function_ `SLATE_BEGIN_ARGS(SSequenceValidator)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L50 _private prototype_ `TSharedRef<SWidget> ConstructMenubar();`
- L52 _private prototype_ `void StartValidation();`
- L53 _private prototype_ `bool CanStartValidation() const;`
- L55 _private prototype_ `EVisibility GetValidationStatusVisibility() const;`
- L56 _private prototype_ `FText GetValidationStatusText() const;`
- L60 _private member_ `TSharedPtr<SSequenceValidatorQueue> QueueWidget;`
- L61 _private member_ `TSharedPtr<SSequenceValidatorResults> ResultsWidget;`
- L62 _private member_ `TSharedPtr<SSequenceValidatorRules> RulesWidget;`
- L64 _private member_ `TSharedPtr<FSequenceValidator> Validator;`
- L66 _private member_ `bool bWaitingForValidationToFinish = false;`

#### class `USequenceValidatorMenuContext`  
`class USequenceValidatorMenuContext : public UObject`  
_L72-79_
- reflection: `UCLASS()`
- inherits: `UObject`
- L78 _public member_ `TWeakPtr<UE::Sequencer::SSequenceValidator> ValidatorWidget;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Widgets/SSequenceValidatorQueue.h` (Private)


#### class `UE::Sequencer::SSequenceValidatorQueue`  
`class SSequenceValidatorQueue : public SCompoundWidget`  
_L15-56_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SSequenceValidatorQueue)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSequenceValidator>, Validator) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `void RequestListRefresh();`
- L31 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L32 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L33 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L37 _private prototype_ `TSharedRef<SWidget> GenerateAddSequenceMenu();`
- L38 _private prototype_ `void OnAddSequence(const FAssetData& SelectedAsset);`
- L39 _private prototype_ `void OnAddSequences(const TArray<FAssetData>& ActivatedAssets, EAssetTypeActivationMethod::Type ActivationMethod);`
- L40 _private prototype_ `void DeleteSequences();`
- L41 _private prototype_ `void ClearQueue();`
- L43 _private prototype_ `TSharedRef<ITableRow> OnListGenerateItemRow(UMovieSceneSequence* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L44 _private prototype_ `TSharedPtr<SWidget> GetContextMenuContent();`
- L46 _private prototype_ `void UpdateItemSource();`
- L50 _private member_ `TSharedPtr<FSequenceValidator> Validator;`
- L52 _private member_ `TSharedPtr<SListView<UMovieSceneSequence*>> ListView;`
- L53 _private member_ `TArray<UMovieSceneSequence*> ItemSource;`
- L55 _private member_ `bool bUpdateItemSource = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Widgets/SSequenceValidatorResults.h` (Private)


#### class `UE::Sequencer::SSequenceValidatorResults`  
`class SSequenceValidatorResults : public SCompoundWidget`  
_L14-52_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSequenceValidatorResults)`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSequenceValidator>, Validator) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void RequestListRefresh();`
- L30 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L34 _private typedef_ `using FTreeItemPtr = TSharedPtr<FSequenceValidationResult>;`
- L36 _private prototype_ `TSharedRef<ITableRow> OnTreeViewGenerateRow(FTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L37 _private prototype_ `void OnTreeViewGetChildren(FTreeItemPtr Item, TArray<FTreeItemPtr>& OutChildren);`
- L38 _private prototype_ `void OnTreeViewMouseButtonDoubleClick(FTreeItemPtr Item);`
- L40 _private prototype_ `void UpdateItemSource();`
- L42 _private prototype_ `EVisibility GetEmptyResultsMessageVisibility() const;`
- L46 _private member_ `TSharedPtr<FSequenceValidator> Validator;`
- L48 _private member_ `TSharedPtr<STreeView<FTreeItemPtr>> TreeView;`
- L49 _private member_ `TArray<FTreeItemPtr> ItemSource;`
- L51 _private member_ `bool bUpdateItemSource = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Private/Widgets/SSequenceValidatorRules.h` (Private)


#### class `UE::Sequencer::SSequenceValidatorRules`  
`class SSequenceValidatorRules : public SCompoundWidget`  
_L14-39_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSequenceValidatorRules)`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<const FSequenceValidator>, Validator) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private typedef_ `using FListItemPtr = TSharedPtr<FSequenceValidationRuleInfo>;`
- L29 _private prototype_ `TSharedRef<ITableRow> OnListGenerateItemRow(FListItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L31 _private prototype_ `void UpdateItemSource();`
- L35 _private member_ `TSharedPtr<const FSequenceValidator> Validator;`
- L37 _private member_ `TSharedPtr<SListView<FListItemPtr>> ListView;`
- L38 _private member_ `TArray<FListItemPtr> ItemSource;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Public/ISequenceValidatorModule.h` (Public)


#### class `UE::Sequencer::ISequenceValidatorModule`  
`class ISequenceValidatorModule : public IModuleInterface`  
_L22-32_
- inherits: `IModuleInterface`
- desc: Interface for the Sequence Validator module.
- L27 _public prototype_ `virtual FSequenceValidationRuleID RegisterValidationRule(FSequenceValidationRuleInfo&& InRuleInfo) = 0;` — Registers a new validation rule factory.
- L29 _public prototype_ `virtual TConstArrayView<FSequenceValidationRuleInfo> GetValidationRules() const = 0;` — Gets the registered validation rule factories.
- L31 _public prototype_ `virtual void UnregisterValidationRule(FSequenceValidationRuleID InRuleID) = 0;` — Unregisters an existing validation rule factory.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSequenceValidator, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSequenceValidator, Log, All);`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L17 _typedef_ `using FSequenceValidationRuleID = FDelegateHandle;` (scope `UE::Sequencer`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Public/Validation/SequenceValidationResult.h` (Public)


#### struct `UE::Sequencer::FTargetKeys`  
`struct FTargetKeys`  
_L21-25_
- L23 _public member_ `FMovieSceneChannel* Channel = nullptr;`
- L24 _public member_ `TArray<FKeyHandle> KeyHandles;`

#### class `UE::Sequencer::FSequenceValidationResult`  
`class FSequenceValidationResult : public TSharedFromThis<FSequenceValidationResult>`  
_L30-116_
- inherits: `TSharedFromThis<FSequenceValidationResult>`
- desc: A single validation result, indicating a note, warning, error, etc. inside the sequence.
- L35 _public prototype_ `FSequenceValidationResult() = default;` — Creates a new default validation result.
- L38 _public function_ `FSequenceValidationResult(UObject* InTarget) : WeakTarget(InTarget)` — Creates a new validation result for the given object.
- L43 _public function_ `FSequenceValidationResult(EMessageSeverity::Type InSeverity, UObject* InTarget, const FSequenceValidationRuleInfo& InRuleInfo) : Severity(InSeverity) , WeakTarget(InTarget) , RuleInfo(InRuleInfo)` — Creates a new validation result for the given object, with the given severity.
- L50 _public function_ `FSequenceValidationResult(EMessageSeverity::Type InSeverity, const FText& InUserMessage) : Severity(InSeverity) , UserMessage(InUserMessage)` — Creates a new validation result with the given severity and message.
- L56 _public function_ `FSequenceValidationResult(EMessageSeverity::Type InSeverity, UObject* InTarget, const FText& InUserMessage, const FSequenceValidationRuleInfo& InRuleInfo) : Severity(InSeverity) , WeakTarget(InTarget) , UserMessage(InUserMessage) , RuleInfo(InRuleInfo)` — Creates a new validation result with the given severity and message, for the given object.
- L65 _public function_ `EMessageSeverity::Type GetSeverity() const`
- L66 _public function_ `const FSequenceValidationRuleInfo& GetRuleInfo() const`
- L68 _public prototype_ `bool GetSubSectionTrail(TArray<UMovieSceneSubSection*>& OutTrail) const;`
- L69 _public prototype_ `void SetSubSectionTrail(TArrayView<UMovieSceneSubSection*> InTrail);`
- L71 _public function_ `UObject* GetTarget() const`
- L72 _public function_ `void SetTarget(UObject* InTarget)`
- L74 _public function_ `FTargetKeys GetTargetKeys() const`
- L75 _public function_ `void SetTargetKeys(FTargetKeys InTargetKeys)`
- L77 _public function_ `const FText& GetUserMessage() const`
- L78 _public function_ `void SetUserMessage(const FText& InUserMessage)`
- L80 _public function_ `bool HasLocalTime() const`
- L81 _public function_ `FFrameTime GetLocalTime() const`
- L82 _public function_ `void SetLocalTime(const FFrameTime InLocalTime)`
- L86 _public function_ `TSharedPtr<FSequenceValidationResult> GetParent() const`
- L91 _public prototype_ `TSharedPtr<FSequenceValidationResult> GetRoot();`
- L93 _public function_ `bool HasChildren() const`
- L95 _public function_ `TArrayView<const TSharedPtr<FSequenceValidationResult>> GetChildren() const`
- L100 _public prototype_ `void AddChild(TSharedRef<FSequenceValidationResult> InChild);`
- L102 _public prototype_ `void AppendChildren(TConstArrayView<TSharedPtr<FSequenceValidationResult>> InChildren);`
- L106 _private member_ `TWeakPtr<FSequenceValidationResult> WeakParent;`
- L107 _private member_ `TArray<TSharedPtr<FSequenceValidationResult>> Children;`
- L109 _private member_ `EMessageSeverity::Type Severity = EMessageSeverity::Info;`
- L110 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSubSection>> WeakSubSectionTrail;`
- L111 _private member_ `TWeakObjectPtr<> WeakTarget;`
- L112 _private member_ `FTargetKeys TargetKeys;`
- L113 _private member_ `FText UserMessage;`
- L114 _private member_ `TOptional<FFrameTime> LocalTime;`
- L115 _private member_ `FSequenceValidationRuleInfo RuleInfo;`

#### class `UE::Sequencer::FSequenceValidationResults`  
`class FSequenceValidationResults : public TSharedFromThis<FSequenceValidationResult>`  
_L121-136_
- inherits: `TSharedFromThis<FSequenceValidationResult>`
- desc: A collection of validation results.
- L125 _public prototype_ `void AddResult(TSharedRef<FSequenceValidationResult> InResult);`
- L126 _public prototype_ `void AppendResults(const FSequenceValidationResults& InResults);`
- L127 _public prototype_ `void AppendResults(TConstArrayView<TSharedPtr<FSequenceValidationResult>> InResults);`
- L129 _public prototype_ `TArrayView<const TSharedPtr<FSequenceValidationResult>> GetResults() const;`
- L131 _public prototype_ `void Reset();`
- L135 _private member_ `TArray<TSharedPtr<FSequenceValidationResult>> ValidationResults;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Public/Validation/SequenceValidationRule.h` (Public)


#### struct `UE::Sequencer::FSequenceValidationRuleInfo`  
`struct FSequenceValidationRuleInfo`  
_L20-32_
- desc: Basic information regarding a validation rule, and how to create it.
- L23 _public member_ `FText RuleName;` — The name of the rule.
- L25 _public member_ `FText RuleDescription;` — The description of the rule.
- L27 _public member_ `FOnCreateSequenceValidationRule RuleFactory;` — A factory method for creating an instance of the rule.
- L29 _public member_ `bool bIsEnabled = true;` — Whether this rule is enabled.
- L31 _public member_ `FSlateColor RuleColor = FSlateColor::UseForeground();` — Color to display in the UI

#### class `UE::Sequencer::FSequenceValidationRule`  
`class FSequenceValidationRule : public TSharedFromThis<FSequenceValidationRule>`  
_L38-55_
- inherits: `TSharedFromThis<FSequenceValidationRule>`
- desc: Base class for a validation rule that can be run on a sequence.
- L42 _public prototype_ `FSequenceValidationRule() = default;`
- L43 _public prototype_ `virtual ~FSequenceValidationRule() = default;`
- L47 _public prototype_ `void Run(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const;`
- L50 _public prototype_ `static FSlateColor GetRuleColor(const FText& InRuleName);` — Get the color for the rule from an internal palette
- L54 _protected function_ `virtual void OnRun(const UMovieSceneSequence* InSequence, FSequenceValidationResults& OutResults) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<FSequenceValidationRule>, FOnCreateSequenceValidationRule);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<FSequenceValidationRule>, FOnCreateSequenceValidationRule);` (scope `UE::Sequencer`)

### `Plugins/MovieScene/SequenceValidator/Source/SequenceValidator/Public/Validation/SequenceValidator.h` (Public)


#### class `UE::Sequencer::FSequenceValidator`  
`class FSequenceValidator`  
_L28-88_
- desc: A sequence validator that can run a given set of validation rules on a sequence. Validation rules are created along with the validator instance, using whatever validation rules factories are registered on the ISequenceValidatorModule at the time.
- L32 _public prototype_ `FSequenceValidator();`
- L33 _public prototype_ `~FSequenceValidator();`
- L38 _public prototype_ `TArrayView<UMovieSceneSequence* const> GetQueue() const;` — The current queue of sequences to validate.
- L40 _public prototype_ `TArray<TSharedPtr<FSequenceValidationRuleInfo>> GetRules() const;` — The list of validation rules to run on the queue.
- L42 _public prototype_ `const FSequenceValidationResults& GetResults() const;` — The current list of results generated by the validation rules.
- L45 _public prototype_ `void Queue(UMovieSceneSequence* InSequence);` — Add the given root sequence to the queue.
- L47 _public prototype_ `void Queue(TArrayView<UMovieSceneSequence*> InSequences);` — Add the given root sequences to the queue.
- L49 _public prototype_ `void Delete(UMovieSceneSequence* InSequence);` — Remove a sequence from the queue.
- L51 _public prototype_ `void ClearQueue();` — Clears the current queue.
- L58 _public prototype_ `void StartValidation();` — Start validating the current queue. This runs all validation rules on all queued-up sequences in an asynchronous manner. Call the IsValidating() method to know when the validation has ended.
- L61 _public prototype_ `bool IsValidating() const;` — Whether an asynchronous validation is in progress.
- L64 _public prototype_ `FSimpleMulticastDelegate& GetOnValidationFinished();` — Gets an event that will be triggered when an asynchronous validation ends.
- L69 _public prototype_ `void Validate(UMovieSceneSequence* InSequence);` — Validates the given sequence synchronously.
- L71 _public prototype_ `void Validate(TArrayView<UMovieSceneSequence*> InSequences);` — Validates the given sequences synchronously.
- L75 _private prototype_ `void CreateValidationRuleInfos();`
- L76 _private prototype_ `void StartValidation(bool bAsync);`
- L77 _private prototype_ `void OnValidationFinished();`
- L81 _private member_ `TArray<UMovieSceneSequence*> ValidationQueue;`
- L82 _private member_ `TArray<TSharedRef<FSequenceValidationRuleInfo>> ValidationRuleInfos;`
- L83 _private member_ `FSequenceValidationResults ValidationResults;`
- L85 _private member_ `TUniquePtr<Internal::FSequenceValidatorTaskScheduler> Scheduler;`
- L87 _private member_ `FSimpleMulticastDelegate OnValidationFinishedDelegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L20 _namespace_ `namespace Internal` (scope `UE::Sequencer`)
