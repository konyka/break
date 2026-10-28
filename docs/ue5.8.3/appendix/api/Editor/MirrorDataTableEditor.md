# Editor / MirrorDataTableEditor

- module root: `Source/Editor/MirrorDataTableEditor`
- headers: 3; symbols: 50
- symbol kinds: class=3, enum=1, enumerator=3, function=3, member=15, prototype=22, struct=3
- PrivateDependencyModuleNames: AssetTools, CoreUObject, DataTableEditor, EditorStyle, Engine, SkeletonEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, SlateCore

### `Source/Editor/MirrorDataTableEditor/Private/MirrorDataTableCustomization.h` (Private)


#### class `FMirrorDataTableCustomization`  
`class FMirrorDataTableCustomization : public IDetailCustomization`  
_L15-32_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L27 _protected member_ `TSharedPtr<FSkeletonTreeBuilder> SkeletonTreeBuilder;`
- L28 _protected member_ `TSharedPtr<ISkeletonTree> SkeletonTree;`
- L29 _protected member_ `TWeakObjectPtr<UMirrorDataTable> MirrorTable;`
- L30 _protected member_ `TSharedPtr<IPropertyHandle> BoneScopeHandle;`
- L31 _protected member_ `IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;`

### `Source/Editor/MirrorDataTableEditor/Public/MirrorDataTableEditorModule.h` (Public)


#### class `FMirrorDataTableEditorModule`  
`class FMirrorDataTableEditorModule : public IModuleInterface`  
_L16-90_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — Begin IModuleInterface
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `void RegisterMenus();` — Register tool menus specific when editing a mirror data tables
- L29 _public prototype_ `static void ExecuteMenuAction_ReimportFromSkeleton(const FToolMenuContext& Context, const UMirrorDataTable::FFindReplaceOptions& Options);` — Reimports and syncs the active mirror data table from its skeleton.
- L32 _public prototype_ `static void ExecuteMenuAction_Validate(const FToolMenuContext& Context);` — Validates the active mirror data table.
- L35 _public prototype_ `static void ExecuteMenuAction_AutoPair(const FToolMenuContext& Context);` — Auto-generates mirror pairs for the active mirror data table.
- L38 _public prototype_ `static void ExecuteMenuAction_ClearSheet(const FToolMenuContext& Context);` — Clears all rows from the active mirror data table.
- L41 _public prototype_ `static void ExecuteMenuAction_ToggleRowEnabled(const FToolMenuContext& Context);` — Toggles the enabled state of the selected row in the active mirror data table.
- L44 _public prototype_ `static void ExecuteMenuAction_SwapPair(const FToolMenuContext& Context);` — Swaps the Name and MirroredName of the selected row.
- L47 _public prototype_ `static void ExecuteMenuAction_AutoPairRow(const FToolMenuContext& Context);` — Applies find/replace expressions to the selected row to derive its mirrored name.
- L50 _public prototype_ `static FSlateIcon GetStatusIcon(UMirrorDataTable* InMirrorDataTable);` — Returns the status icon for the given mirror data table.
- L55 _private prototype_ `static void ValidateMirrorDataTable(UMirrorDataTable* MirrorTable, bool bNotifyOnCleanPass);` — Validates the given mirror data table and logs all issues. Skips showing notification on validation passed if requested.
- L71 _private prototype_ `void BindSkeletonCallbacks(UMirrorDataTable* MirrorTable);` — Binds skeleton change callbacks for the given MirrorTable. Unbinds any existing callbacks first if the MirrorTable was previously bound.
- L74 _private prototype_ `void UnbindSkeletonCallbacks(UMirrorDataTable* MirrorTable);` — Unbinds all skeleton change callbacks for the given MirrorTable and removes its entry from ActiveSkeletonCallbacks.
- L77 _private prototype_ `void OnAssetOpenedInEditor(UObject* Asset, IAssetEditorInstance* EditorInstance);` — Called when any asset is opened in the editor. Binds skeleton callbacks if the asset is a mirror data table.
- L80 _private prototype_ `void OnPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Called when a property changes on any UObject. Rebinds skeleton callbacks when the Skeleton property changes on a mirror data table.
- L83 _private member_ `TMap<TWeakObjectPtr<UMirrorDataTable>, FSkeletonCallbackHandles> ActiveSkeletonCallbacks;` — Per-MirrorTable skeleton callback state for all actively-edited mirror data tables.
- L86 _private member_ `FDelegateHandle OnAssetOpenedHandle;` — Handle for the UAssetEditorSubsystem::OnAssetOpenedInEditor delegate.
- L89 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;` — Handle for the FCoreUObjectDelegates::OnObjectPropertyChanged delegate.

#### struct `FMirrorDataTableEditorModule::FSkeletonCallbackHandles`  
`struct FSkeletonCallbackHandles`  
_L58-68_
- desc: Stores per-mirror-table skeleton callback handles for an actively-edited mirror data table.
- L61 _public member_ `TSharedPtr<IEditableSkeleton> EditableSkeleton;` — Editable skeleton interface used to register/unregister notifies callbacks.
- L64 _public member_ `FDelegateHandle CurveMetaDataChangedHandle;` — Handle for the curve metadata changed callback.
- L67 _public member_ `TWeakObjectPtr<USkeleton> BoundSkeleton;` — The skeleton that was bound. Stored separately so unbinding is safe even if the MirrorTable's Skeleton property has already changed.

### `Source/Editor/MirrorDataTableEditor/Public/MirrorDataTableValidator.h` (Public)


#### class `FMirrorDataTableValidator`  
`class FMirrorDataTableValidator`  
_L10-91_
- L79 _public prototype_ `static FResult Validate(const UMirrorDataTable& MirrorDataTable);` — Looks for any issues with the provided data table and record them.
- L84 _private prototype_ `static void ValidateSkeletonBackedEntries(const UMirrorDataTable& MirrorDataTable, FResult& OutResult, FScopedSlowTask& InOutProgress);` — Checks for missing or stale skeleton entries.
- L87 _private prototype_ `static void ValidateDuplicateMappings(const UMirrorDataTable& MirrorDataTable, FResult& OutResult, FScopedSlowTask& InOutProgress);` — Catches duplicate logical source entries of the same row type.
- L90 _private prototype_ `static void ValidateReverseMappings(const UMirrorDataTable& MirrorDataTable, FResult& OutResult, FScopedSlowTask& InOutProgress);` — Checks for two entries mapping to the same mirror entry causing the operation to no be invertible. Ex. A -> B and C -> B.

#### struct `FMirrorDataTableValidator::FIssue`  
`struct FIssue`  
_L15-32_
- desc: Used to record an issue when validating a Mirror Data Table.
- L25 _public member_ `ESeverity Severity = ESeverity::Info;` — Determines the scale of the issue
- L28 _public member_ `FText Message;` — Summary of what went wrong.
- L31 _public member_ `FName RowName = NAME_None;` — Row where the issue is present.

#### enum `FMirrorDataTableValidator::FIssue::ESeverity`  
`enum class ESeverity : uint8`  
_L17-22_
- L19 _public enumerator_ `Info`
- L20 _public enumerator_ `Warning`
- L21 _public enumerator_ `Error`

#### struct `FMirrorDataTableValidator::FResult`  
`struct FResult`  
_L35-76_
- desc: Used to record the results from validating a Mirror Data Table.
- L38 _public member_ `TArray<FIssue> Issues;` — Record of everything that is not properly setup.
- L41 _public function_ `bool HasErrors() const` — Do we have any issues at all?
- L55 _public function_ `bool HasWarnings() const` — Do we have any warnings at all?
- L69 _public function_ `void AddIssue(FIssue::ESeverity Severity, const FText& Message, FName RowName = NAME_None)` — Records an issue that occurred during validation.
