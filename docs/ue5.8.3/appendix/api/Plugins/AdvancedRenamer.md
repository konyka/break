# Plugins / AdvancedRenamer

- module root: `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer`
- headers: 23; symbols: 438
- symbol kinds: class=21, delegate=5, enum=4, enumerator=10, function=13, member=89, namespace=2, prototype=278, struct=2, variable=14
- PrivateDependencyModuleNames: ContentBrowser, CoreUObject, Engine, InputCore, LevelEditor, Projects, Slate, SlateCore, ToolMenus, UMG, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamer.h` (Private)


#### class `FAdvancedRenamer`  
`class FAdvancedRenamer : public IAdvancedRenamer`  
_L11-69_
- inherits: `IAdvancedRenamer`
- L14 _public prototype_ `FAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InProvider);`
- L17 _public prototype_ `virtual const TSharedRef<IAdvancedRenamerProvider>& GetProvider() const override;`
- L18 _public prototype_ `virtual TArray<TSharedPtr<FAdvancedRenamerPreview>>& GetSortablePreviews() override;`
- L19 _public prototype_ `virtual void ResetSortablePreviews() override;`
- L20 _public prototype_ `virtual void AddSection(FAdvancedRenamerExecuteSection InSection) override;`
- L21 _public prototype_ `virtual bool HasRenames() const override;`
- L22 _public prototype_ `virtual bool IsDirty() const override;`
- L23 _public prototype_ `virtual void MarkDirty() override;`
- L24 _public prototype_ `virtual void MarkClean() override;`
- L25 _public prototype_ `virtual FString ApplyRename(const FString& InName) override;`
- L26 _public prototype_ `virtual bool UpdatePreviews() override;`
- L27 _public prototype_ `virtual bool Execute() override;`
- L31 _public prototype_ `virtual int32 Num() const override;`
- L32 _public prototype_ `virtual bool IsValidIndex(int32 InIndex) const override;`
- L33 _public prototype_ `virtual uint32 GetHash(int32 InIndex) const override;`
- L34 _public prototype_ `virtual FString GetOriginalName(int32 InIndex) const override;`
- L35 _public prototype_ `virtual bool RemoveIndex(int32 InIndex) override;`
- L36 _public prototype_ `virtual bool CanRename(int32 InIndex) const override;`
- L38 _public prototype_ `virtual bool BeginRename() override;`
- L39 _public prototype_ `virtual bool PrepareRename(int32 InIndex, const FString& InNewName) override;`
- L40 _public prototype_ `virtual bool ExecuteRename() override;`
- L41 _public prototype_ `virtual bool EndRename() override;`
- L46 _private prototype_ `void BeforeOperationsStartExecute();` — Called before the whole Rename logic start
- L49 _private prototype_ `void AfterOperationsEndExecute();` — Called after the whole Rename logic end
- L53 _private member_ `TSharedRef<IAdvancedRenamerProvider> Provider;` — Provider for this Renamer
- L56 _private member_ `TArray<TSharedPtr<FAdvancedRenamerPreview>> Previews;` — Previews Name list
- L59 _private member_ `TArray<TSharedPtr<FAdvancedRenamerPreview>> SortablePreviews;` — Sorted Previews Name list
- L62 _private member_ `TArray<FAdvancedRenamerExecuteSection> Sections;` — Renamer sections list
- L65 _private member_ `bool bHasRenames;` — Whether or not at least 1 preview has a Rename
- L68 _private member_ `bool bDirty;` — if true the Rename logic will be executed

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerCommands.h` (Private)


#### class `FAdvancedRenamerCommands`  
`class FAdvancedRenamerCommands : public TCommands<FAdvancedRenamerCommands>`  
_L10-19_
- inherits: `TCommands<FAdvancedRenamerCommands>`
- L13 _public prototype_ `FAdvancedRenamerCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> BatchRenameObject;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> BatchRenameSharedClassActors;`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerExecuteSection.h` (Private)


#### struct `FAdvancedRenamerExecuteSection`  
`struct FAdvancedRenamerExecuteSection`  
_L12-36_
- L15 _public function_ `FOnOperationExecuted& OnOperationExecuted()` — Get the callback executed before the whole Rename happens
- L18 _public function_ `FOnBeforeOperationExecutionStart& OnBeforeOperationExecutionStart()` — Get the callback executed during the Rename
- L21 _public function_ `FOnAfterOperationExecutionEnded& OnAfterOperationExecutionEnded()` — Get the callback executed after the whole Rename happens
- L25 _public member_ `FName SectionName;` — Name of this section
- L29 _private member_ `FOnBeforeOperationExecutionStart OnBeforeOperationExecutionStartDelegate;` — Callback called before the whole Rename execution is applied
- L32 _private member_ `FOnOperationExecuted OnOperationExecutedDelegate;` — Callback called during the whole Rename execution
- L35 _private member_ `FOnAfterOperationExecutionEnded OnAfterOperationExecutionEndedDelegate;` — Callback called after the whole Rename execution is applied

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE(FOnBeforeOperationExecutionStart) DECLARE_DELEGATE_OneParam(FOnOperationExecuted, FString& ) DECLARE_DELEGATE(FOnAfterOperationExecutionEnded) struct FAdvancedRenamerExecuteSection { FOnOperationExecuted& OnOperationExecuted() { return OnOperationExecutedDelegate; } FOnBeforeOperationExecutionStart& OnBeforeOperationExecutionStart() { return OnBeforeOperationExecutionStartDelegate; } FOnAfterOperationExecutionEnded& OnAfterOperationExecutionEnded() { return OnAfterOperationExecutionEndedDelegate; } public: FName SectionName; private: FOnBeforeOperationExecutionStart OnBeforeOperationExecutionStartDelegate; FOnOperationExecuted OnOperationExecutedDelegate; FOnAfterOperationExecutionEnded OnAfterOperationExecutionEndedDelegate; };`
- L9 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOperationExecuted, FString& ) DECLARE_DELEGATE(FOnAfterOperationExecutionEnded) struct FAdvancedRenamerExecuteSection { FOnOperationExecuted& OnOperationExecuted() { return OnOperationExecutedDelegate; } FOnBeforeOperationExecutionStart& OnBeforeOperationExecutionStart() { return OnBeforeOperationExecutionStartDelegate; } FOnAfterOperationExecutionEnded& OnAfterOperationExecutionEnded() { return OnAfterOperationExecutionEndedDelegate; } public: FName SectionName; private: FOnBeforeOperationExecutionStart OnBeforeOperationExecutionStartDelegate; FOnOperationExecuted OnOperationExecutedDelegate; FOnAfterOperationExecutionEnded OnAfterOperationExecutionEndedDelegate; };`
- L10 _delegate_ `DECLARE_DELEGATE(FOnAfterOperationExecutionEnded) struct FAdvancedRenamerExecuteSection { FOnOperationExecuted& OnOperationExecuted() { return OnOperationExecutedDelegate; } FOnBeforeOperationExecutionStart& OnBeforeOperationExecutionStart() { return OnBeforeOperationExecutionStartDelegate; } FOnAfterOperationExecutionEnded& OnAfterOperationExecutionEnded() { return OnAfterOperationExecutionEndedDelegate; } public: FName SectionName; private: FOnBeforeOperationExecutionStart OnBeforeOperationExecutionStartDelegate; FOnOperationExecuted OnOperationExecutedDelegate; FOnAfterOperationExecutionEnded OnAfterOperationExecutionEndedDelegate; };`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerModule.h` (Private)


#### class `FAdvancedRenamerModule`  
`class FAdvancedRenamerModule : public IAdvancedRenamerModule`  
_L13-40_
- inherits: `IAdvancedRenamerModule`
- desc: Advanced Rename Panel Plugin - Easily bulk rename stuff!
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `virtual TSharedRef<IAdvancedRenamer> CreateAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider) override;`
- L22 _private prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider, const TSharedPtr<SWidget>& InParentWidget) override;`
- L23 _private prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider, const TSharedPtr<IToolkitHost>& InToolkitHost) override;`
- L24 _private prototype_ `virtual void OpenAdvancedRenamerForActors(const TArray<AActor*>& InActors, const TSharedPtr<SWidget>& InParentWidget) override;`
- L25 _private prototype_ `virtual void OpenAdvancedRenamerForActors(const TArray<AActor*>& InActors, const TSharedPtr<IToolkitHost>& InToolkitHost) override;`
- L26 _private prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamer>& InRenamer, const TSharedPtr<IToolkitHost>& InToolkitHost) override;`
- L27 _private prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamer>& InRenamer, const TSharedPtr<SWidget>& InParentWidget) override;`
- L28 _private prototype_ `virtual TArray<AActor*> GetActorsSharingClassesInWorld(const TArray<AActor*>& InActors) override;`
- L29 _private function_ `virtual TArray<TSharedPtr<IAdvancedRenamerSection>> GetRegisteredSections() const override`
- L30 _private function_ `virtual FOnFilterAdvancedRenamerActors& OnFilterAdvancedRenamerActors() override`
- L34 _private prototype_ `void RegisterDefaultSections();`
- L37 _private member_ `TArray<TSharedPtr<IAdvancedRenamerSection>> Sections;`
- L38 _private member_ `FDelegateHandle EnableRenamerHandle;`
- L39 _private member_ `FOnFilterAdvancedRenamerActors FilterAdvancedRenamerActors;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogARP, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogARP, Log, All);`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerAddPrefixSuffixSection.h` (Private)


#### class `FAdvancedRenamerAddPrefixSuffixSection`  
`class FAdvancedRenamerAddPrefixSuffixSection : public FAdvancedRenamerSectionBase`  
_L15-77_
- inherits: `FAdvancedRenamerSectionBase`
- L18 _public prototype_ `FAdvancedRenamerAddPrefixSuffixSection();`
- L20 _public prototype_ `virtual ~FAdvancedRenamerAddPrefixSuffixSection() = default;`
- L23 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L26 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L29 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L33 _private prototype_ `TSharedRef<SWidget> CreateAddPrefix();` — Create the AddPrefix widget
- L36 _private prototype_ `TSharedRef<SWidget> CreateAddSuffix();` — Create the AddSuffix widget
- L39 _private prototype_ `FText GetPrefixText() const;` — Get the Prefix text
- L42 _private prototype_ `FText GetSuffixText() const;` — Get the Suffix text
- L45 _private prototype_ `void OnPrefixChanged(const FText& InNewText);` — Called when the Prefix text change
- L48 _private prototype_ `void OnSuffixChanged(const FText& InNewText);` — Called when the Suffix text change
- L51 _private prototype_ `bool CanApplyAddPrefixOperation();` — Whether the AddPrefix operation can be executed
- L54 _private prototype_ `bool CanApplyAddSuffixOperation();` — Whether the AddSuffix operation can be executed
- L57 _private prototype_ `void ApplyAddPrefixOperation(FString& OutOriginalName);` — Execute logic for the AddPrefix
- L60 _private prototype_ `void ApplyAddSuffixOperation(FString& OutOriginalName);` — Execute logic for the AddSuffix
- L63 _private prototype_ `void ApplyAddPrefixSuffixNumberOperation(FString& OutOriginalName);` — Execute logic for this section
- L67 _private member_ `TSharedPtr<SEditableTextBox> PrefixTextBox;` — AddPrefix TextBox
- L70 _private member_ `TSharedPtr<SEditableTextBox> SuffixTextBox;` — AddSuffix TextBox
- L73 _private member_ `FText PrefixText;` — AddPrefix Text
- L76 _private member_ `FText SuffixText;` — AddSuffix text

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerChangeCaseSection.h` (Private)


#### enum `EAdvancedRenamerChangeCaseType`  
`enum class EAdvancedRenamerChangeCaseType : uint8`  
_L14-20_
- desc: Change case types
- L16 _public enumerator_ `SwapFirst`
- L17 _public enumerator_ `SwapAll`
- L18 _public enumerator_ `AllLower`
- L19 _public enumerator_ `AllUpper`

#### class `FAdvancedRenamerChangeCaseSection`  
`class FAdvancedRenamerChangeCaseSection : public FAdvancedRenamerSectionBase`  
_L25-72_
- inherits: `FAdvancedRenamerSectionBase`
- desc: ChangeCase section
- L28 _public prototype_ `FAdvancedRenamerChangeCaseSection();`
- L30 _public prototype_ `virtual ~FAdvancedRenamerChangeCaseSection() = default;`
- L33 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L36 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L39 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L43 _private prototype_ `FReply OnChangeCaseButtonClicked(EAdvancedRenamerChangeCaseType InNewValue);` — Called when one of the CaseChange buttons is clicked
- L46 _private prototype_ `bool CanApplyChangeCaseSection();` — Whether or not the ChangeCase operation can be executed
- L49 _private prototype_ `void ApplySwapFirst(FString& OutOriginalName);` — Execute logic for the SwapFirst
- L52 _private prototype_ `void ApplySwapAll(FString& OutOriginalName);` — Execute logic for the SwapAll
- L55 _private prototype_ `void ApplyAllLower(FString& OutOriginalName);` — Execute logic for the AllLower
- L58 _private prototype_ `void ApplyAllUpper(FString& OutOriginalName);` — Execute logic for the AllUpper
- L61 _private prototype_ `void ResetButtonClicked();` — Reset the current button clicked and disable the ChangeCase until the next time a button is clicked
- L64 _private prototype_ `void ApplyChangeCaseSection(FString& OutOriginalName);` — Execute logic for this section
- L68 _private member_ `EAdvancedRenamerChangeCaseType ChangeCaseType;` — ChangeCase type to execute
- L71 _private member_ `bool bButtonWasClicked;` — Whether a button was clicked and the Renamer needs to apply the ChangeCase

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerNumberingSection.h` (Private)


#### enum `EAdvancedRenamerNumberingType`  
`enum class EAdvancedRenamerNumberingType`  
_L17-21_
- L19 _public enumerator_ `Number`
- L20 _public enumerator_ `Letter`

#### class `FAdvancedRenamerNumberingSection`  
`class FAdvancedRenamerNumberingSection : public FAdvancedRenamerSectionBase`  
_L23-166_
- inherits: `FAdvancedRenamerSectionBase`
- L26 _public prototype_ `FAdvancedRenamerNumberingSection();`
- L28 _public prototype_ `virtual ~FAdvancedRenamerNumberingSection() = default;`
- L31 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L34 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L37 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L41 _private prototype_ `ECheckBoxState IsAddNumberingChecked() const;` — If checked the section will be enabled
- L44 _private prototype_ `bool IsAddNumberingEnabled() const;` — Whether the section is enabled
- L47 _private prototype_ `EVisibility IsAddNumberingTypeNumber() const;` — Visible if the type is Number, Collapsed otherwise
- L50 _private prototype_ `EAdvancedRenamerNumberingType GetAddNumberingType() const;` — Get the type of the AddNumbering, either by Number or by Letter
- L53 _private prototype_ `FText GetCurrentFormatText() const;` — Get the current Text Format
- L56 _private prototype_ `int32 GetNumberingIndex() const;` — Get the Index of the WidgetSwitcher to either show the Number or the Letter
- L59 _private prototype_ `int32 GetAddNumberValue() const;` — Get the starting Number of the AddNumber SpinBox
- L62 _private prototype_ `FText GetAddLetterText() const;` — Get the starting Letter of the AddLetter TextBox
- L65 _private prototype_ `int32 GetAddNumberingStepValue() const;` — Get the starting Number of the AddNumbering Step SpinBox
- L68 _private prototype_ `FText GetFormatTextForIndex(TSharedPtr<int32> InFormatIndex) const;` — Get the Text Format for the given InFormatIndex
- L71 _private prototype_ `FString GetFormattedNumber() const;` — Get the formatted Number Text
- L74 _private prototype_ `TSharedRef<SWidget> OnGenerateFormatWidget(TSharedPtr<int32> InOption) const;` — Generate the Format option widget for the ComboBox
- L77 _private prototype_ `void OnFormatSelectionChanged(TSharedPtr<int32> InNewFormat, ESelectInfo::Type InSelectInfo);` — Called when the Format selected change
- L80 _private prototype_ `void OnAddNumberingCheckBoxChanged(ECheckBoxState InNewState);` — Called when the AddNumbering CheckBox state change
- L83 _private prototype_ `void OnAddNumberingTypeChanged(EAdvancedRenamerNumberingType InNewValue);` — Called when the AddNumbering type changed, it will be either by Number or Letter
- L86 _private prototype_ `void OnAddNumberChanged(int32 InNewValue);` — Called when the AddNumber number change
- L89 _private prototype_ `void OnAddLetterChanged(const FText& InNewText);` — Called when the AddLetter letter change
- L92 _private prototype_ `bool OnLetteringVerifyText(const FText& InNewText, FText& OutErrorText);` — Called to verify that the Letter input is correct and allowed
- L95 _private prototype_ `void OnAddNumberingStepChanged(int32 InNewValue);` — Called when the AddNumbering Step number change
- L98 _private prototype_ `bool CanApplyAddNumberOperation() const;` — Whether the AddNumber operation can be executed
- L101 _private prototype_ `bool CanApplyAddLetterOperation() const;` — Whether the AddLetter operation can be executed
- L104 _private prototype_ `void ApplyAddNumberOperation(FString& OutOriginalName);` — Execute logic for the AddNumber
- L107 _private prototype_ `void ApplyAddLetterOperation(FString& OutOriginalName);` — Execute logic for the AddLetter
- L110 _private prototype_ `void ResetCurrentNumbering();` — Reset current numbering
- L113 _private prototype_ `void ApplyNumbering(FString& OutOriginalName);` — Execute logic for this section
- L117 _private member_ `TSharedPtr<SCheckBox> AddNumberingCheckBox;` — Section enabler CheckBox
- L120 _private member_ `TSharedPtr<SSpinBox<int32>> AddNumberStartSpinBox;` — Starting Number SpinBox for the AddNumber
- L123 _private member_ `TSharedPtr<SEditableTextBox> AddLetterStartTextBox;` — Starting Letter TextBox for the AddLetter
- L126 _private member_ `TSharedPtr<SSpinBox<int32>> AddNumberStepSpinBox;` — Step Number SpinBox for the AddNumbering section
- L129 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> FormattingComboBox;` — Step Number SpinBox for the AddNumbering section
- L132 _private member_ `bool bIsAddNumberingSectionEnabled;` — AddNumbering section enabler, section is enabled if true
- L135 _private member_ `bool bIsAddLetteringInputCorrect;` — AddNumbering section enabler, section is enabled if true
- L138 _private member_ `EAdvancedRenamerNumberingType AddNumberingType;` — AddNumbering type, either Number or Letter
- L141 _private member_ `int32 AddNumberingWidgetSwitcherIndex;` — Index of the WidgetSwitcher between Number and Letter
- L144 _private member_ `int32 AddNumberValue;` — AddNumber start/stop value
- L147 _private member_ `FText AddLetterText;` — AddLetter start/stop value
- L150 _private member_ `int32 AddNumberingStepValue;` — AddNumber step value
- L153 _private member_ `int32 CurrentAddNumberValue;` — Current AddNumber value
- L156 _private member_ `FString CurrentAddLetterString;` — Current AddLetter value
- L159 _private member_ `int32 CurrentFormatChosen;` — Current format chosen
- L162 _private member_ `TArray<TSharedPtr<int32>> ComboBoxSourceOptions;` — Source option for the DropDown Menu of the ComboBox
- L165 _private member_ `static TArray<FText> ComboBoxTextOptions;` — Text option based on the SourceOption

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerRemovePrefixSection.h` (Private)


#### class `FAdvancedRenamerRemovePrefixSection`  
`class FAdvancedRenamerRemovePrefixSection : public FAdvancedRenamerSectionBase`  
_L16-102_
- inherits: `FAdvancedRenamerSectionBase`
- L19 _public prototype_ `FAdvancedRenamerRemovePrefixSection();`
- L21 _public prototype_ `virtual ~FAdvancedRenamerRemovePrefixSection() = default;`
- L24 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L27 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L30 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L34 _private prototype_ `ECheckBoxState IsRemoveOldPrefixChecked() const;` — If checked the section will be enabled
- L37 _private prototype_ `bool IsRemoveOldPrefixEnabled() const;` — If checked it will remove all the current suffix numbers
- L40 _private prototype_ `FText GetPrefixSeparatorText() const;` — Get the separator text
- L43 _private prototype_ `uint8 GetPrefixCharsValue() const;` — Get the numbers of chars to remove
- L46 _private prototype_ `EAdvancedRenamerRemoveOldType GetRemoveOldPrefixType() const;` — Get the type of the remove, either by Separator or by number of Chars
- L49 _private prototype_ `void OnRemoveOldPrefixCheckBoxChanged(ECheckBoxState InNewState);` — Called when the RemoveOldPrefix checkbox state change
- L52 _private prototype_ `bool OnPrefixSeparatorVerifyTextChanged(const FText& InText, FText& OutErrorText) const;` — Verify that the separator text is valid
- L55 _private prototype_ `void OnPrefixSeparatorChanged(const FText& InNewText);` — Called when the separator text change
- L58 _private prototype_ `void OnPrefixRemoveCharactersChanged(uint8 InNewValue);` — Called when the remove chars number change
- L61 _private prototype_ `void OnRemoveOldPrefixTypeChanged(EAdvancedRenamerRemoveOldType InNewValue);` — Called when the remove type changed, it will be either by Separator or by number of Chars
- L64 _private prototype_ `bool CanApplyRemovePrefixSeparatorOperation();` — Whether or not the Remove by Separator operation can be executed
- L67 _private prototype_ `bool CanApplyRemovePrefixCharOperation();` — Whether or not the Remove by number of Chars operation can be executed
- L70 _private prototype_ `void ApplyRemovePrefixSeparatorOperation(FString& OutOriginalName);` — Execute logic for the Remove by Separator
- L73 _private prototype_ `void ApplyRemovePrefixCharOperation(FString& OutOriginalName);` — Execute logic for the Remove by number of Chars
- L76 _private prototype_ `void ApplyRemovePrefixOperation(FString& OutOriginalName);` — Execute logic for this section
- L80 _private member_ `TSharedPtr<SCheckBox> RemoveOldPrefixCheckBox;` — Section enabler CheckBox
- L83 _private member_ `TSharedPtr<SEditableTextBox> PrefixSeparatorTextBox;` — Separator EditableTextBox
- L86 _private member_ `TSharedPtr<SSpinBox<uint8>> PrefixRemoveCharactersSpinBox;` — Number of Chars SSpinBox
- L89 _private member_ `uint8 RemovePrefixCharsValue;` — Number of Chars value
- L92 _private member_ `FText RemovePrefixSeparatorText;` — Separator Text
- L95 _private member_ `int32 PrefixWidgetSwitcherIndex;` — Index of the WidgetSwitcher
- L98 _private member_ `EAdvancedRenamerRemoveOldType RemovePrefixType;` — RemoveSuffix Remove type, either Separator or by number of Chars
- L101 _private member_ `bool bRemoveOldPrefixSection;` — RemoveOldSuffix section enabler, section is enabled if true

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerRemoveSuffixSection.h` (Private)


#### class `FAdvancedRenamerRemoveSuffixSection`  
`class FAdvancedRenamerRemoveSuffixSection : public FAdvancedRenamerSectionBase`  
_L19-124_
- inherits: `FAdvancedRenamerSectionBase`
- desc: RemoveSuffix section
- L22 _public prototype_ `FAdvancedRenamerRemoveSuffixSection();`
- L24 _public prototype_ `virtual ~FAdvancedRenamerRemoveSuffixSection() = default;`
- L27 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L30 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L33 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L38 _private prototype_ `ECheckBoxState IsRemoveOldSuffixChecked() const;` — If checked the section will be enabled
- L41 _private prototype_ `ECheckBoxState IsSuffixRemoveNumberChecked() const;` — If checked it will remove all the current suffix numbers
- L44 _private prototype_ `bool IsRemoveOldSuffixEnabled() const;` — Whether or not the section is enabled
- L47 _private prototype_ `FText GetSuffixSeparatorText() const;` — Get the separator text
- L50 _private prototype_ `uint8 GetSuffixCharsValue() const;` — Get the numbers of chars to remove
- L53 _private prototype_ `EAdvancedRenamerRemoveOldType GetRemoveOldSuffixType() const;` — Get the type of the remove, either by Separator or by number of Chars
- L56 _private prototype_ `void OnRemoveOldSuffixCheckBoxChanged(ECheckBoxState InNewState);` — Called when the RemoveOldSuffix checkbox state change
- L59 _private prototype_ `void OnSuffixRemoveNumberCheckBoxChanged(ECheckBoxState InNewState);` — Called when the RemoveNumber checkbox state change
- L62 _private prototype_ `bool OnSuffixSeparatorVerifyTextChanged(const FText& InText, FText& OutErrorText) const;` — Verify that the separator text is valid
- L65 _private prototype_ `void OnSuffixSeparatorChanged(const FText& InNewText);` — Called when the separator text change
- L68 _private prototype_ `void OnSuffixRemoveCharactersChanged(uint8 InNewValue);` — Called when the remove chars number change
- L71 _private prototype_ `void OnRemoveOldSuffixTypeChanged(EAdvancedRenamerRemoveOldType InNewValue);` — Called when the remove type changed, it will be either by Separator or by number of Chars
- L74 _private prototype_ `bool CanApplyRemoveSuffixSeparatorOperation();` — Whether or not the Remove by Separator operation can be executed
- L77 _private prototype_ `bool CanApplyRemoveSuffixCharOperation();` — Whether or not the Remove by number of Chars operation can be executed
- L80 _private prototype_ `bool CanApplyRemoveSuffixNumbers();` — Whether or not the RemoveNumbers operation can be executed
- L83 _private prototype_ `void ApplyRemoveSuffixSeparatorOperation(FString& OutOriginalName);` — Execute logic for the Remove by Separator
- L86 _private prototype_ `void ApplyRemoveSuffixCharOperation(FString& OutOriginalName);` — Execute logic for the Remove by number of Chars
- L89 _private prototype_ `void ApplyRemoveSuffixNumbers(FString& OutOriginalName);` — Execute logic for the RemoveNumbers
- L92 _private prototype_ `void ApplyRemoveSuffixOperation(FString& OutOriginalName);` — Execute logic for this section
- L96 _private member_ `TSharedPtr<SCheckBox> RemoveOldSuffixCheckBox;` — Section enabler CheckBox
- L99 _private member_ `TSharedPtr<SEditableTextBox> SuffixSeparatorTextBox;` — Separator EditableTextBox
- L102 _private member_ `TSharedPtr<SSpinBox<uint8>> SuffixRemoveCharactersSpinBox;` — Number of Chars SSpinBox
- L105 _private member_ `TSharedPtr<SCheckBox> SuffixRemoveNumberCheckBox;` — RemoveNumber CheckBox
- L108 _private member_ `uint8 RemoveSuffixCharsValue;` — Number of Chars value
- L111 _private member_ `FText RemoveSuffixSeparatorText;` — Separator Text
- L114 _private member_ `int32 SuffixWidgetSwitcherIndex;` — Index of the WidgetSwitcher
- L117 _private member_ `EAdvancedRenamerRemoveOldType RemoveSuffixType;` — RemoveSuffix Remove type, either Separator or by number of Chars
- L120 _private member_ `bool bRemoveOldSuffixSection;` — RemoveOldSuffix section enabler, section is enabled if true
- L123 _private member_ `bool bRemoveSuffixNumbers;` — RemoveNumber enabler, RemoveNumber operation will be executed if true

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerSearchAndReplaceSection.h` (Private)


#### enum `EAdvancedRenamerSearchAndReplaceType`  
`enum class EAdvancedRenamerSearchAndReplaceType`  
_L18-22_
- desc: Search And Replace options
- L20 _public enumerator_ `PlainText`
- L21 _public enumerator_ `RegularExpression`

#### class `FAdvancedRenamerSearchAndReplaceSection`  
`class FAdvancedRenamerSearchAndReplaceSection : public FAdvancedRenamerSectionBase`  
_L27-107_
- inherits: `FAdvancedRenamerSectionBase`
- desc: Search and Replace/Rename section
- L30 _public prototype_ `FAdvancedRenamerSearchAndReplaceSection();`
- L32 _public prototype_ `virtual ~FAdvancedRenamerSearchAndReplaceSection() = default;`
- L35 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L38 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — Return the widget for this section
- L41 _public prototype_ `virtual void ResetToDefault() override;` — Reset all values of the section to the default ones
- L45 _private function_ `static FString GetRegexDocumentationURL()` — Regex documentation URL
- L48 _private prototype_ `FReply OnRegexHelp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Called when the Regex help icon is clicked
- L51 _private prototype_ `ECheckBoxState IsSearchReplaceIgnoreCaseChecked() const;` — If checked it will use the IgnoreCase, otherwise it is CaseSensitive
- L54 _private prototype_ `void OnSearchReplaceIgnoreCaseCheckBoxChanged(ECheckBoxState InNewState);` — Called when the ignore case checkbox state change
- L57 _private prototype_ `void OnSearchTextChanged(const FText& InNewText);` — Called when the search text change
- L60 _private prototype_ `FText GetSearchText() const;` — Get the search text
- L63 _private prototype_ `void OnReplaceTextChanged(const FText& InNewText);` — Called when the replace text change
- L66 _private prototype_ `FText GetReplaceText() const;` — Get the replace text
- L69 _private prototype_ `FString RegexReplace(const FString& InOriginalString, const FRegexPattern& InPattern, const FString& InReplaceString) const;` — Regex Replace logic
- L72 _private prototype_ `bool CanApplySearchAndReplaceOperation();` — Whether or not the SearchAndReplace operation can be executed
- L75 _private prototype_ `bool CanApplyRenameOperation();` — Whether or not the Rename operation can be executed
- L78 _private prototype_ `void ApplySearchAndReplaceOperation(FString& OutOriginalName);` — Execute logic for the SearchAndReplace
- L81 _private prototype_ `void ApplyRenameOperation(FString& OutOriginalName);` — Execute logic for the Rename
- L84 _private prototype_ `void ApplySearchAndReplaceOrRenameOperation(FString& OutOriginalName);` — Execute logic for this section
- L88 _private member_ `TSharedPtr<SEditableTextBox> SearchReplaceSearchTextBox;` — Search EditableTextBox
- L91 _private member_ `TSharedPtr<SEditableTextBox> SearchReplaceReplaceTextBox;` — Replace/Rename EditableTextBox
- L94 _private member_ `TSharedPtr<SCheckBox> SearchReplaceIgnoreCaseCheckBox;` — Ignore case CheckBox
- L97 _private member_ `EAdvancedRenamerSearchAndReplaceType SearchAndReplaceType;` — SearchAndReplace search type, either PlainText or RegularExpression
- L100 _private member_ `ESearchCase::Type SearchCaseType;` — SearchAndReplace case type, either IgnoreCase or CaseSensitive
- L103 _private member_ `FText SearchText;` — Search Text
- L106 _private member_ `FText ReplaceText;` — Replace/Rename Text

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/AdvancedRenamerSectionBase.h` (Private)


#### class `FAdvancedRenamerSectionBase`  
`class FAdvancedRenamerSectionBase : public IAdvancedRenamerSection`  
_L10-29_
- inherits: `IAdvancedRenamerSection`
- desc: Base class for all the default sections, implementing common behavior for them
- L14 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) override;` — Init the given section
- L17 _public prototype_ `virtual FAdvancedRenamerExecuteSection GetSection() const override;` — Return the section information
- L21 _protected prototype_ `virtual void MarkRenamerDirty() const override;` — Mark the Renamer dirty, this will make the Renamer re-execute the Rename logic
- L25 _protected member_ `FAdvancedRenamerExecuteSection Section;` — Section information of this extension
- L28 _protected member_ `TWeakPtr<IAdvancedRenamer> RenamerWeakPtr;` — Weak pointer to the Renamer

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerSections/IAdvancedRenamerSection.h` (Private)


#### class `IAdvancedRenamerSection`  
`class IAdvancedRenamerSection : public TSharedFromThis<IAdvancedRenamerSection>`  
_L14-52_
- inherits: `TSharedFromThis<IAdvancedRenamerSection>`
- desc: Interface for all the sections for the AdvancedRenamer
- L29 _public function_ `static TSharedRef<InAdvancedRenamerSectionFactory> MakeInstance(InArgsType&&... InArgs)`
- L35 _public prototype_ `virtual ~IAdvancedRenamerSection() = default;` — virtual destructor
- L38 _public prototype_ `virtual void Init(TSharedRef<IAdvancedRenamer> InRenamer) = 0;` — Init the given section
- L41 _public prototype_ `virtual void ResetToDefault() = 0;` — Reset all values of the section to the default ones
- L44 _public prototype_ `virtual FAdvancedRenamerExecuteSection GetSection() const = 0;` — Return the section information
- L47 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — Return the widget for this section
- L51 _protected prototype_ `virtual void MarkRenamerDirty() const = 0;` — Mark the Renamer dirty, this will make the Renamer re-execute the Rename logic

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/AdvancedRenamerStyle.h` (Private)


#### class `FAdvancedRenamerStyle`  
`class FAdvancedRenamerStyle`  
_L11-28_
- L15 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static const ISlateStyle& Get();`
- L21 _public prototype_ `static FName GetStyleSetName();`
- L25 _private prototype_ `static void InitStyle();`
- L26 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/IAdvancedRenamer.h` (Private)


#### struct `FAdvancedRenamerPreview`  
`struct FAdvancedRenamerPreview`  
_L10-30_
- L12 _public function_ `FAdvancedRenamerPreview(int32 InHash, const FString InOriginalName) : Hash(InHash) , OriginalName(InOriginalName) , NewName(TEXT("")) , OriginalNameForSort(InOriginalName)`
- L21 _public function_ `FName GetNameForSort() const` — Get the OriginalName FName for sort purposes
- L24 _public member_ `int32 Hash;`
- L25 _public member_ `const FString OriginalName;`
- L26 _public member_ `FString NewName;`
- L29 _private member_ `const FName OriginalNameForSort;`

#### class `IAdvancedRenamer`  
`class IAdvancedRenamer : public IAdvancedRenamerProvider`  
_L36-68_
- inherits: `IAdvancedRenamerProvider`
- desc: Implements its own provider interface so it can avoid long Execute_ lines and handle the 2 different types of provider (SharedPtr and UObject.)
- L39 _public prototype_ `virtual ~IAdvancedRenamer() = default;`
- L41 _public prototype_ `virtual const TSharedRef<IAdvancedRenamerProvider>& GetProvider() const = 0;`
- L44 _public prototype_ `virtual TArray<TSharedPtr<FAdvancedRenamerPreview>>& GetSortablePreviews() = 0;` — Get the sortable previews
- L47 _public prototype_ `virtual void ResetSortablePreviews() = 0;` — Reset the order of the Previews to the original one
- L50 _public prototype_ `virtual void AddSection(FAdvancedRenamerExecuteSection InSection) = 0;` — Add a section to this Renamer
- L53 _public prototype_ `virtual bool HasRenames() const = 0;` — True if there are any items actually renamed by the preview generator.
- L56 _public prototype_ `virtual bool IsDirty() const = 0;` — Whether the options have been updated.
- L57 _public prototype_ `virtual void MarkDirty() = 0;`
- L58 _public prototype_ `virtual void MarkClean() = 0;`
- L61 _public prototype_ `virtual FString ApplyRename(const FString& InName) = 0;` — Executes the rename on the given name.
- L64 _public prototype_ `virtual bool UpdatePreviews() = 0;` — Returns true if any names actually changed.
- L67 _public prototype_ `virtual bool Execute() = 0;` — Returns true if all items were updated without error.

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Integrations/AdvancedRenamerContentBrowserIntegration.h` (Private)


#### class `FAdvancedRenamerContentBrowserIntegration`  
`class FAdvancedRenamerContentBrowserIntegration`  
_L5-10_
- L8 _public prototype_ `static void Initialize();`
- L9 _public prototype_ `static void Shutdown();`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Integrations/AdvancedRenamerLevelEditorIntegration.h` (Private)


#### class `FAdvancedRenamerLevelEditorIntegration`  
`class FAdvancedRenamerLevelEditorIntegration`  
_L5-14_
- L8 _public prototype_ `static void Initialize();`
- L9 _public prototype_ `static void Shutdown();`
- L12 _private prototype_ `static void InitializeMenu();`
- L13 _private prototype_ `static void ShutdownMenu();`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Providers/AdvancedRenamerActorProvider.h` (Private)


#### class `FAdvancedRenamerActorProvider`  
`class FAdvancedRenamerActorProvider : public IAdvancedRenamerProvider`  
_L13-41_
- inherits: `IAdvancedRenamerProvider`
- L16 _public prototype_ `FAdvancedRenamerActorProvider();`
- L19 _public prototype_ `void SetActorList(const TArray<TWeakObjectPtr<AActor>>& InActorList);`
- L20 _public prototype_ `void AddActorList(const TArray<TWeakObjectPtr<AActor>>& InActorList);`
- L21 _public prototype_ `void AddActorData(AActor* InActor);`
- L22 _public prototype_ `AActor* GetActor(int32 InIndex) const;`
- L26 _protected prototype_ `virtual int32 Num() const override;`
- L27 _protected prototype_ `virtual bool IsValidIndex(int32 InIndex) const override;`
- L28 _protected prototype_ `virtual uint32 GetHash(int32 InIndex) const override;`
- L29 _protected prototype_ `virtual FString GetOriginalName(int32 InIndex) const override;`
- L30 _protected prototype_ `virtual bool RemoveIndex(int32 InIndex) override;`
- L31 _protected prototype_ `virtual bool CanRename(int32 InIndex) const override;`
- L33 _protected prototype_ `virtual bool BeginRename() override;`
- L34 _protected prototype_ `virtual bool PrepareRename(int32 InIndex, const FString& InNewName) override;`
- L35 _protected prototype_ `virtual bool ExecuteRename() override;`
- L36 _protected prototype_ `virtual bool EndRename() override;`
- L39 _protected member_ `TArray<TWeakObjectPtr<AActor>> ActorList;`
- L40 _protected member_ `TArray<TTuple<AActor*, FString>> ActorToNewNameList;`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Providers/AdvancedRenamerAssetProvider.h` (Private)


#### class `FAdvancedRenamerAssetProvider`  
`class FAdvancedRenamerAssetProvider : public IAdvancedRenamerProvider`  
_L12-40_
- inherits: `IAdvancedRenamerProvider`
- L15 _public prototype_ `FAdvancedRenamerAssetProvider();`
- L18 _public prototype_ `void SetAssetList(const TArray<FAssetData>& InAssetList);`
- L19 _public prototype_ `void AddAssetList(const TArray<FAssetData>& InAssetList);`
- L20 _public prototype_ `void AddAssetData(const FAssetData& InAsset);`
- L21 _public prototype_ `UObject* GetAsset(int32 InIndex) const;`
- L25 _protected prototype_ `virtual int32 Num() const override;`
- L26 _protected prototype_ `virtual bool IsValidIndex(int32 InIndex) const override;`
- L27 _protected prototype_ `virtual uint32 GetHash(int32 InIndex) const override;`
- L28 _protected prototype_ `virtual FString GetOriginalName(int32 InIndex) const override;`
- L29 _protected prototype_ `virtual bool RemoveIndex(int32 InIndex) override;`
- L30 _protected prototype_ `virtual bool CanRename(int32 InIndex) const override;`
- L32 _protected prototype_ `virtual bool BeginRename() override;`
- L33 _protected prototype_ `virtual bool PrepareRename(int32 InIndex, const FString& InNewName) override;`
- L34 _protected prototype_ `virtual bool ExecuteRename() override;`
- L35 _protected prototype_ `virtual bool EndRename() override;`
- L38 _protected member_ `TArray<FAssetData> AssetList;`
- L39 _protected member_ `TArray<FAssetRenameData> AssetRenameDataList;`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Providers/AdvancedRenamerObjectProvider.h` (Private)


#### class `FAdvancedRenamerObjectProvider`  
`class FAdvancedRenamerObjectProvider : public IAdvancedRenamerProvider`  
_L13-41_
- inherits: `IAdvancedRenamerProvider`
- L16 _public prototype_ `FAdvancedRenamerObjectProvider();`
- L19 _public prototype_ `void SetObjectList(const TArray<TWeakObjectPtr<UObject>>& InObjectList);`
- L20 _public prototype_ `void AddObjectList(const TArray<TWeakObjectPtr<UObject>>& InObjectList);`
- L21 _public prototype_ `void AddObjectData(UObject* InObject);`
- L22 _public prototype_ `UObject* GetObject(int32 InIndex) const;`
- L26 _protected prototype_ `virtual int32 Num() const override;`
- L27 _protected prototype_ `virtual bool IsValidIndex(int32 InIndex) const override;`
- L28 _protected prototype_ `virtual uint32 GetHash(int32 InIndex) const override;`
- L29 _protected prototype_ `virtual FString GetOriginalName(int32 InIndex) const override;`
- L30 _protected prototype_ `virtual bool RemoveIndex(int32 InIndex) override;`
- L31 _protected prototype_ `virtual bool CanRename(int32 InIndex) const override;`
- L33 _protected prototype_ `virtual bool BeginRename() override;`
- L34 _protected prototype_ `virtual bool PrepareRename(int32 InIndex, const FString& InNewName) override;`
- L35 _protected prototype_ `virtual bool ExecuteRename() override;`
- L36 _protected prototype_ `virtual bool EndRename() override;`
- L39 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectList;`
- L40 _protected member_ `TArray<TTuple<UObject*, FString>> ObjectToNewNameList;`

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Slate/SAdvancedRenamerPanel.h` (Private)


#### class `SAdvancedRenamerPanel`  
`class SAdvancedRenamerPanel : public SCompoundWidget`  
_L23-128_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SAdvancedRenamerPanel)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IAdvancedRenamer>& InRenamer);`
- L35 _private prototype_ `void CreateApplyResetCancelPanel();` — Create Apply Reset and Cancel bottom panel
- L38 _private prototype_ `TSharedRef<SWidget> CreateApplyButton();` — Create Apply button
- L41 _private prototype_ `TSharedRef<SWidget> CreateResetButton();` — Create Reset button
- L44 _private prototype_ `TSharedRef<SWidget> CreateCancelButton();` — Create Cancel button
- L47 _private prototype_ `void CreateRightPanel();` — Create the right side panel
- L50 _private prototype_ `TSharedRef<SWidget> CreateRenamePreview();` — Create the rename preview
- L53 _private prototype_ `bool CloseWindow();` — Close the Renamer window
- L56 _private prototype_ `void RefreshListViewAndUpdate(const double InCurrentTime);` — Refresh and Update the Preview
- L59 _private prototype_ `void RemoveSelectedObjects();` — Remove selected entries from the Renamer
- L62 _private prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L66 _private prototype_ `EColumnSortMode::Type GetColumnSortMode() const;` — Get the current Column SortMode
- L69 _private prototype_ `void OnColumnSortModeChanged(EColumnSortPriority::Type InSortPriority, const FName& InName, EColumnSortMode::Type InSortMode);` — Called when the SortMode change
- L72 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAdvancedRenamerPreview> InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — Callback to generate ListBoxRows
- L75 _private prototype_ `FReply OnListViewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);` — Handle the click on the ListView
- L78 _private prototype_ `TSharedPtr<SWidget> GenerateListViewContextMenu();` — Generate the ListView menu
- L81 _private prototype_ `bool IsApplyButtonEnabled() const;` — Whether or not the ApplyButton is enabled
- L84 _private prototype_ `FReply OnApplyButtonClicked();` — Called when clicking on the Apply button
- L87 _private prototype_ `FReply OnResetButtonClicked();` — Called when clicking on the Reset button
- L90 _private prototype_ `FReply OnCancelButtonClicked();` — Called when clicking on the Cancel button
- L94 _private member_ `static constexpr double MinUpdateFrequency = 0.1f;` — Min update frequency, used in the tick to avoid updating the renamer too often
- L97 _private member_ `EColumnSortMode::Type SortMode;` — Current SortMode for the List
- L100 _private member_ `TArray<TSharedPtr<FAdvancedRenamerPreview>> PreviewList;` — Preview list used for the ListView
- L103 _private member_ `TSharedPtr<IAdvancedRenamer> Renamer;` — Renamer instance
- L106 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list of the Renamer Panel
- L109 _private member_ `double ListLastUpdateTime = 0;` — Last update time of the list
- L112 _private member_ `TSharedPtr<SVerticalBox> LeftSideVerticalBox;` — Sections VerticalBox
- L115 _private member_ `TSharedPtr<SBox> RightSideBox;` — RightSide container Box
- L118 _private member_ `TSharedPtr<SBox> ApplyResetCancelBox;` — Bottom panel button container Box
- L121 _private member_ `TSharedPtr<SBox> RenamePreviewListBox;` — ListView container Box
- L124 _private member_ `TSharedPtr<SHeaderRow> RenamePreviewListHeaderRow;` — ListView Header row
- L127 _private member_ `TSharedPtr<SListView<TSharedPtr<FAdvancedRenamerPreview>>> RenamePreviewList;` — ListView of the Previews

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Private/Utils/AdvancedRenamerSlateUtils.h` (Private)


#### enum `EAdvancedRenamerRemoveOldType`  
`enum class EAdvancedRenamerRemoveOldType : uint8`  
_L8-12_
- L10 _public enumerator_ `Separator`
- L11 _public enumerator_ `Chars`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AdvancedRenamerSlateUtils`
- L14 _namespace_ `namespace Default` (scope `AdvancedRenamerSlateUtils`)
- L16 _variable_ `static FName OriginalNameColumnName = TEXT("Ori` (scope `AdvancedRenamerSlateUtils::Default`)
- L17 _variable_ `static FName NewNameColumnName = TEXT("New` (scope `AdvancedRenamerSlateUtils::Default`)
- L18 _variable_ `static FMargin FirstWidgetPadding = FMargin(0.f, 0.f, 4.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L19 _variable_ `static FMargin LastWidgetPadding = FMargin(4.f, 0.f, 0.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L20 _variable_ `static FMargin MiddleWidgetPadding = FMargin(4.f, 0.f, 4.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L21 _variable_ `static FMargin SectionContentFirstEntryPadding = FMargin(8.f, 8.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L22 _variable_ `static FMargin SectionContentMiddleEntriesPadding = FMargin(8.f, 0.f, 8.f, 8.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L23 _variable_ `static FMargin VerticalPadding = FMargin(0.f, 4.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L24 _variable_ `static FMargin ChangeCaseFirstButtonPadding = FMargin(0.f, 0.f, 4.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L25 _variable_ `static FMargin ChangeCaseMiddleButtonsPadding = FMargin(4.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L26 _variable_ `static FMargin ChangeCaseLastButtonPadding = FMargin(4.f, 0.f, 0.f, 0.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L27 _variable_ `static FMargin ApplyButtonPadding = FMargin(8.f, 8.f, 4.f, 8.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L28 _variable_ `static FMargin ResetButtonPadding = FMargin(4.f, 8.f, 4.f, 8.f);` (scope `AdvancedRenamerSlateUtils::Default`)
- L29 _variable_ `static FMargin CancelButtonPadding = FMargin(4.f, 8.f, 8.f, 8.f);` (scope `AdvancedRenamerSlateUtils::Default`)

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Public/IAdvancedRenamerModule.h` (Public)


#### class `IAdvancedRenamerModule`  
`class IAdvancedRenamerModule : public IModuleInterface`  
_L17-55_
- inherits: `IModuleInterface`
- desc: Advanced Rename Panel Plugin - Easily bulk rename stuff!
- L20 _protected member_ `static constexpr const TCHAR* ModuleName = TEXT("Adv`
- L23 _public function_ `static bool IsLoaded()`
- L28 _public function_ `static IAdvancedRenamerModule& Get()`
- L33 _public prototype_ `virtual TSharedRef<IAdvancedRenamer> CreateAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider) = 0;`
- L35 _public prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider, const TSharedPtr<IToolkitHost>& InToolkitHost) = 0;`
- L37 _public prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamerProvider>& InRenameProvider, const TSharedPtr<SWidget>& InParentWidget) = 0;`
- L39 _public prototype_ `virtual void OpenAdvancedRenamerForActors(const TArray<AActor*>& InActors, const TSharedPtr<IToolkitHost>& InToolkitHost) = 0;`
- L41 _public prototype_ `virtual void OpenAdvancedRenamerForActors(const TArray<AActor*>& InActors, const TSharedPtr<SWidget>& InParentWidget) = 0;`
- L43 _public prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamer>& InRenamer, const TSharedPtr<IToolkitHost>& InToolkitHost) = 0;`
- L45 _public prototype_ `virtual void OpenAdvancedRenamer(const TSharedRef<IAdvancedRenamer>& InRenamer, const TSharedPtr<SWidget>& InParentWidget) = 0;`
- L47 _public prototype_ `virtual TArray<TSharedPtr<IAdvancedRenamerSection>> GetRegisteredSections() const = 0;`
- L49 _public prototype_ `virtual TArray<AActor*> GetActorsSharingClassesInWorld(const TArray<AActor*>& InActors) = 0;`
- L52 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilterAdvancedRenamerActors, TArray<TWeakObjectPtr<AActor>>&);` — Delegate to filter out actors before they are opened in the advanced renamer. The renamer will not be opened if the array is empty
- L53 _public prototype_ `virtual FOnFilterAdvancedRenamerActors& OnFilterAdvancedRenamerActors() = 0;`

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilterAdvancedRenamerActors, TArray<TWeakObjectPtr<AActor>>&);` — Delegate to filter out actors before they are opened in the advanced renamer. The renamer will not be opened if the array is empty

### `Plugins/Experimental/AdvancedRenamer/Source/AdvancedRenamer/Public/Providers/IAdvancedRenamerProvider.h` (Public)


#### class `IAdvancedRenamerProvider`  
`class IAdvancedRenamerProvider`  
_L10-40_
- L13 _public prototype_ `virtual ~IAdvancedRenamerProvider() = default;`
- L14 _public prototype_ `virtual int32 Num() const = 0;`
- L15 _public prototype_ `virtual bool IsValidIndex(int32 InIndex) const = 0;`
- L16 _public prototype_ `virtual uint32 GetHash(int32 InIndex) const = 0;`
- L17 _public prototype_ `virtual FString GetOriginalName(int32 InIndex) const = 0;`
- L18 _public prototype_ `virtual bool RemoveIndex(int32 InIndex) = 0;`
- L19 _public prototype_ `virtual bool CanRename(int32 InIndex) const = 0;`
- L21 _public prototype_ `virtual bool BeginRename() = 0;`
- L22 _public prototype_ `virtual bool PrepareRename(int32 InIndex, const FString& InNewName) = 0;`
- L23 _public prototype_ `virtual bool ExecuteRename() = 0;`
- L24 _public prototype_ `virtual bool EndRename() = 0;`
- L26 _public function_ `virtual int32 FindHash(int32 InInHash) const`
