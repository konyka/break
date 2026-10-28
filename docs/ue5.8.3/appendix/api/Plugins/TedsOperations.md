# Plugins / TedsOperations

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations`
- headers: 15; symbols: 251
- symbol kinds: class=8, enum=1, enumerator=3, function=13, macro=8, member=40, namespace=68, prototype=65, struct=21, typedef=24
- PrivateDependencyModuleNames: Engine, SceneOutliner, Slate, TedsQueryStack, TypedElementRuntime
- PublicDependencyModuleNames: Core, CoreUObject, SlateCore, TypedElementFramework, UnrealEd

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Private/TedsOperationsModule.h` (Private)


#### class `UE::Editor::DataStorage::Operations::FTedsOperationsModule`  
`class FTedsOperationsModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/Deletion/DeletionOperationInput.h` (Public)


#### struct `FDeletionOperationForceTag`  
`struct FDeletionOperationForceTag final : public FEditorDataStorageTag`  
_L10-13_
- reflection: `USTRUCT(meta = (DisplayName = "Force Deletion"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L17 _typedef_ `using FDeletionForceTag = FDeletionOperationForceTag;` (scope `UE::Editor::DataStorage::Operations`) — Tag to notify the deletion operation that the input should be force deleted, i.e. regardless of restrictions.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/Deletion/DeletionOperationSystem.h` (Public)


#### struct `FDeletionOperationTag`  
`struct FDeletionOperationTag final : public FEditorDataStorageTag`  
_L14-17_
- reflection: `USTRUCT(meta = (DisplayName = "Deletion Operation"))`
- inherits: `FEditorDataStorageTag`

#### class `UDeletionOperationSystem`  
`class UDeletionOperationSystem : public UOperationSystem`  
_L28-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOperationSystem`
- desc: Operation system to execute operations that delete something. Only considers operations with the FDeletionTag.
- L32 _public prototype_ `UDeletionOperationSystem();`
- L35 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& Storage) override;`
- L47 _public prototype_ `bool CreateInputRows(UE::Editor::DataStorage::FRowHandleArray& OutInputRows, UE::Editor::DataStorage::FRowHandleArrayView SourceRows, bool bForce, bool bAddDescription) const;` — Utility method to create a batch of rows that can be used as input for deletion operations. The method will create as many rows as source rows were passed in and automatically assign the FSourceColumn and FDeletionTag. The source rows will be the ones the operation should consider for deletion. @OutInputRows The array to fill with the input rows that were created. @SourceRows The array holding the source rows that should be deleted. Automatically assigned to the FSourceColumn. @bForce Whether the FForceDeletionTag should be added to the input rows. Informs the operation to execute deletion regardless of restrictions. @bAddDescription Whether the FDescriptionColumn should be added to the input rows. Holds an FText which the operation may write to. @returns True if the requested number of rows were successfully created, otherwise false.
- L51 _protected prototype_ `virtual void GetQueryDescription(UE::Editor::DataStorage::FQueryDescription& OutDescription) const override;`
- L53 _protected member_ `UE::Editor::DataStorage::TableHandle InputTableForce;`
- L54 _protected member_ `UE::Editor::DataStorage::TableHandle InputTableForceDescr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L21 _typedef_ `using FDeletionTag = FDeletionOperationTag;` (scope `UE::Editor::DataStorage::Operations`) — Tag to identify this operation as a drop operation. UDeletionOperationSystem will only consider operation rows with this tag.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/DropOperationInput.h` (Public)


#### struct `FDropOperationTargetColumn`  
`struct FDropOperationTargetColumn final : public FEditorDataStorageColumn`  
_L12-17_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Target"))`
- inherits: `FEditorDataStorageColumn`
- L16 _public member_ `UE::Editor::DataStorage::RowHandle Value;`

#### struct `FDropOperationNameColumn`  
`struct FDropOperationNameColumn final : public FEditorDataStorageColumn`  
_L20-25_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Name"))`
- inherits: `FEditorDataStorageColumn`
- L24 _public member_ `FName Value;`

#### struct `FDropOperationTransformColumn`  
`struct FDropOperationTransformColumn final : public FEditorDataStorageColumn`  
_L28-33_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Transform"))`
- inherits: `FEditorDataStorageColumn`
- L32 _public member_ `FTransform Value;`

#### struct `FDropOperationFolderColumn`  
`struct FDropOperationFolderColumn final : public FEditorDataStorageColumn`  
_L36-41_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Folder"))`
- inherits: `FEditorDataStorageColumn`
- L40 _public member_ `FName Path;`

#### struct `FDropOperationPreviewTag`  
`struct FDropOperationPreviewTag final : public FEditorDataStorageTag`  
_L44-47_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Preview"))`
- inherits: `FEditorDataStorageTag`

#### struct `FDropOperationTypedElementResultColumn`  
`struct FDropOperationTypedElementResultColumn final : public FEditorDataStorageColumn`  
_L50-55_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation Typed Element Result"))`
- inherits: `FEditorDataStorageColumn`
- L54 _public member_ `TArray<FTypedElementHandle> Elements;`

#### Free symbols / members of external scopes

- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace Editor` (scope `UE`)
- L57 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L57 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L60 _typedef_ `using FDropTargetColumn = FDropOperationTargetColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds the target row of the drop operation (e.g. a level).
- L62 _typedef_ `using FDropPreviewTag = FDropOperationPreviewTag;` (scope `UE::Editor::DataStorage::Operations`) — Informs the operation to create a preview.
- L64 _typedef_ `using FDropNameColumn = FDropOperationNameColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds the name that should be used by the operation.
- L66 _typedef_ `using FDropTransformColumn = FDropOperationTransformColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds the transform that should be used by the operation.
- L68 _typedef_ `using FDropFolderColumn = FDropOperationFolderColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds the folder path that should be used by the operation.
- L70 _typedef_ `using FDropTypedElementResultColumn = FDropOperationTypedElementResultColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds the TEv1 handles created by the operation.
- L72 _namespace_ `namespace Utilities` (scope `UE::Editor::DataStorage::Operations`)
- L74 _function_ `inline RowHandle GetDropTargetRow(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`)
- L80 _function_ `inline FName GetDropName(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`)
- L86 _function_ `inline FTransform GetDropTransform(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`)
- L92 _function_ `inline FName GetDropFolderPath(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`)
- L98 _function_ `inline bool HasDropPreviewTag(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/DropOperationSystem.h` (Public)


#### struct `FDropOperationTag`  
`struct FDropOperationTag final : public FEditorDataStorageTag`  
_L14-17_
- reflection: `USTRUCT(meta = (DisplayName = "Drop Operation"))`
- inherits: `FEditorDataStorageTag`

#### class `UDropOperationSystem`  
`class UDropOperationSystem : public UOperationSystem`  
_L28-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOperationSystem`
- desc: Operation system to execute operations that drag&drop something on a target. Only considers operations with the FDropTag.
- L32 _public prototype_ `UDropOperationSystem();`
- L35 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& Storage) override;`
- L46 _public prototype_ `bool CreateInputRows(UE::Editor::DataStorage::FRowHandleArray& OutInputRows, UE::Editor::DataStorage::FRowHandleArrayView SourceRows, UE::Editor::DataStorage::RowHandle TargetRow, bool bAddDescription) const;` — Utility method to create a batch of rows that can be used as input for drop operations. The method will create as many rows as source rows were passed in and automatically assign the FSourceColumn and FDropTag. The source rows will be the ones the drop operation should consider. @OutInputRows The array to fill with the input rows that were created. @SourceRows The array holding the source rows that should be considered by the drop operation. Automatically assigned to the FSourceColumn. @bAddDescription Whether the FDescriptionColumn should be added to the input rows. Holds an FText which the operation may write to. @returns True if the requested number of rows were successfully created, otherwise false.
- L50 _protected prototype_ `virtual void GetQueryDescription(UE::Editor::DataStorage::FQueryDescription& OutDescription) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L21 _typedef_ `using FDropTag = FDropOperationTag;` (scope `UE::Editor::DataStorage::Operations`) — Tag to identify this operation as a drop operation. UDropOperationSystem will only consider rows with this tag.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/TedsDragDropOp.h` (Public)


#### class `UE::Editor::DataStorage::Widgets::FTedsDragDropOp`  
`class FTedsDragDropOp : public FDecoratedDragDropOp`  
_L14-30_
- inherits: `FDecoratedDragDropOp`
- desc: TEDS UI TODO: Instead of using a decorated operation use a default one and allow decorator customization using TEDS UI
- L17 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FTedsDragDropOp, FDecoratedDragDropOp) static TSharedRef<FTedsDragDropOp> New(FRowHandleArray InDraggedRows);`
- L21 _public function_ `FRowHandleArrayView GetRows() const`
- L22 _public function_ `FRowHandleArray& GetRowArray()`
- L23 _public function_ `const FRowHandleArray& GetRowArray() const`
- L26 _protected prototype_ `void Init(FRowHandleArray InDraggedRows);`
- L29 _protected member_ `FRowHandleArray DraggedRows;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/TedsDragDropOpUtility.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace DragAndDrop` (scope `UE::Editor::DataStorage`)
- L19 _prototype_ `bool GetRowsFromData(FRowHandleArray& OutRows, const FDragDropOperation& InData);` (scope `UE::Editor::DataStorage::DragAndDrop`) — Tries to convert the dropped data into rows. Returns true if all data was successfully converted.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/Widgets/PreviewWidgetDropHandler.h` (Public)


#### class `UE::Editor::FPreviewWidgetDropHandler`  
`class FPreviewWidgetDropHandler : public FWidgetDropHandler`  
_L17-46_
- inherits: `FWidgetDropHandler`
- desc: Utility type for widgets that accepts drag&drop-events and preview creation on drag-over using teds operations.
- L20 _public prototype_ `FPreviewWidgetDropHandler(TWeakObjectPtr<UTypedElementSelectionSet> SelectionSet);`
- L23 _public function_ `bool HasPreviews() const`
- L26 _protected prototype_ `virtual FDropResult ResetOperations(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L27 _protected prototype_ `virtual TOptional<FDropResult> Update(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FGeometry& Geometry, const FDragDropEvent& InputEvent) override;`
- L29 _protected prototype_ `virtual void Stop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L30 _protected prototype_ `virtual void Drop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FGeometry& Geometry, const FDragDropEvent& InputEvent) override;`
- L33 _protected prototype_ `virtual void CreatePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem);`
- L34 _protected prototype_ `virtual void UpdatePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem);`
- L35 _protected prototype_ `virtual void RemovePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem);`
- L37 _protected prototype_ `void GetPreviewRows(DataStorage::FRowHandleArray& OutRows, DataStorage::ICoreProvider& Storage) const;`
- L39 _protected prototype_ `virtual int32 ExecutePreviewDrop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, DataStorage::FRowHandleArrayView InputRows);`
- L40 _protected prototype_ `virtual bool ExecutePreviewDropSingle(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, DataStorage::RowHandle InputRow);`
- L43 _protected member_ `DataStorage::FRowHandleArray PreviewInputRows;`
- L45 _protected member_ `TArray<FTypedElementHandle> PreviewElements;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/Widgets/ViewportDropHandler.h` (Public)


#### class `UE::Editor::FViewportDropHandler`  
`class FViewportDropHandler : public FPreviewWidgetDropHandler`  
_L14-47_
- inherits: `FPreviewWidgetDropHandler`
- L17 _public typedef_ `using FTargetRowGetter = TFunction<DataStorage::RowHandle(const FEditorViewportClient&)>;`
- L24 _public prototype_ `FViewportDropHandler(TSharedPtr<FEditorViewportClient> InViewportClient, FTargetRowGetter InGetDefaultTargetRow);` — Construct a viewport drop handler. @param InViewportClient The client of the viewport the handler is representing. @param InGetDefaultTargetRow A function to return a "default" target during drag&drop that is used when not tracing.
- L27 _public prototype_ `virtual FReply OnDrop(const FGeometry& Geometry, const FDragDropEvent& InputEvent) override;`
- L30 _protected prototype_ `virtual EUpdateParameters UpdateParameters(DataStorage::ICoreProvider& Storage, const FGeometry& Geometry, const FDragDropEvent& InputEvent) override;`
- L31 _protected prototype_ `virtual void SetRowsFromParameters(DataStorage::ICoreProvider& Storage, DataStorage::FRowHandleArrayView Rows) const override;`
- L32 _protected prototype_ `virtual void Stop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L34 _protected prototype_ `virtual void CreatePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L35 _protected prototype_ `virtual void UpdatePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L36 _protected prototype_ `virtual void RemovePreviews(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L38 _protected prototype_ `void InvalidateViewport();`
- L41 _protected member_ `TSharedPtr<FEditorViewportClient> ViewportClient;`
- L42 _protected member_ `FTargetRowGetter GetDefaultTargetRow;` — A function to return a "default" target during drag&drop that is used when not tracing.
- L44 _protected member_ `FIntPoint LastCursorPos;`
- L45 _protected member_ `DataStorage::RowHandle LastTargetRow;`
- L46 _protected member_ `FTransform LastTransform;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/DragAndDrop/Widgets/WidgetDropHandler.h` (Public)


#### class `UE::Editor::FWidgetDropHandler`  
`class FWidgetDropHandler`  
_L28-93_
- desc: Utility type for widgets that accepts drag&drop-events using teds operations.
- L46 _public prototype_ `static void ShowErrorNotifications(const DataStorage::ICoreProvider& Storage, DataStorage::FRowHandleArrayView InputRows);`
- L48 _public prototype_ `FWidgetDropHandler(TWeakObjectPtr<UTypedElementSelectionSet> SelectionSet);`
- L49 _public prototype_ `virtual ~FWidgetDropHandler();`
- L51 _public prototype_ `virtual bool OnDragEnter(const FGeometry& Geometry, const FDragDropEvent& InputEvent);`
- L52 _public prototype_ `virtual FReply OnDragOver(const FGeometry& Geometry, const FDragDropEvent& InputEvent);`
- L53 _public prototype_ `virtual bool OnDragLeave(const FDragDropEvent& InputEvent);`
- L54 _public prototype_ `virtual FReply OnDrop(const FGeometry& Geometry, const FDragDropEvent& InputEvent);`
- L55 _public prototype_ `virtual FDragDropOperation* GetCurrentOperation() const;`
- L59 _protected prototype_ `virtual bool PrepareInput(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FDragDropOperation& Operation);` — Creates input rows for the given drag&drop input event.
- L61 _protected prototype_ `virtual bool PrepareInput(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, DataStorage::FRowHandleArrayView SourceRows);` — Creates input rows for the given drag&drop input event.
- L63 _protected prototype_ `virtual FDropResult ResetOperations(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem);` — Finds suitable operations for the given input rows and sets 'bIsValidDrop'.
- L66 _protected prototype_ `virtual EUpdateParameters UpdateParameters(DataStorage::ICoreProvider& Storage, const FGeometry& Geometry, const FDragDropEvent& InputEvent);` — Method to update cached parameters for the given input data.
- L68 _protected prototype_ `virtual void SetRowsFromParameters(DataStorage::ICoreProvider& Storage, DataStorage::FRowHandleArrayView Rows) const;` — Method to assign cached parameters to the given rows.
- L71 _protected prototype_ `virtual TOptional<FDropResult> Start(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FGeometry& Geometry, const FDragDropEvent& InputEvent, FDragDropOperation& Operation);` — Starts a drag-operation internally. Returns an unset value if the operation is ignored, a result with True if the drop operation would be valid or False if invalid.
- L74 _protected prototype_ `virtual TOptional<FDropResult> Update(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FGeometry& Geometry, const FDragDropEvent& InputEvent);` — Updates the current drag-operation internally. Returns an updated result or unset optional if nothing has changed.
- L77 _protected prototype_ `virtual void Stop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem);` — Stops the current drag-operation.
- L79 _protected prototype_ `virtual void Drop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, const FGeometry& Geometry, const FDragDropEvent& InputEvent);` — Stops and executes the drop for the current drag-operation.
- L82 _protected prototype_ `virtual void UpdateOperationDecorator(FDragDropOperation& Operation, TOptional<FDropResult> Result) const;`
- L84 _protected prototype_ `virtual int32 ExecuteDrop(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, DataStorage::FRowHandleArrayView InputRows);`
- L85 _protected prototype_ `virtual bool ExecuteDropSingle(DataStorage::ICoreProvider& Storage, UDropOperationSystem& DropSystem, DataStorage::RowHandle InputRow);`
- L88 _protected member_ `TWeakObjectPtr<UTypedElementSelectionSet> SelectionSet;`
- L90 _protected member_ `FDragDropOperation* CurrentOperation;`
- L91 _protected member_ `DataStorage::FRowHandleArray InputRows;`
- L92 _protected member_ `bool bIsValidDrop;`

#### struct `UE::Editor::FWidgetDropHandler::FDropResult`  
`struct FDropResult`  
_L31-35_
- L33 _public member_ `bool bCanDrop = false;`
- L34 _public member_ `FText Tooltip = FText();`

#### enum `UE::Editor::FWidgetDropHandler::EUpdateParameters`  
`enum class EUpdateParameters`  
_L38-43_
- L40 _public enumerator_ `NoChanges` — Nothing has changed.
- L41 _public enumerator_ `MinorChanges` — Some changes to input, but no need to reset operations.
- L42 _public enumerator_ `ResetOperations` — Input has major changes, reset operations.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Editor` (scope `UE`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/TedsOperationCallbacks.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L18 _typedef_ `using FProbeCallback = TFunction<bool(const ICoreProvider&, RowHandle)>;` (scope `UE::Editor::DataStorage::Operations`) — Probe call to test superficially if the given input is potentially acceptable for the operation.
- L20 _typedef_ `using FTestCallback = TFunction<bool(ICoreProvider&, RowHandle)>;` (scope `UE::Editor::DataStorage::Operations`) — Test call to query if the operation for the given input can be executed.
- L22 _typedef_ `using FApplyCallback = TFunction<TOptional<FResult>(ICoreProvider&, RowHandle)>;` (scope `UE::Editor::DataStorage::Operations`) — Apply call to execute the operation for the given input.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/TedsOperationColumns.h` (Public)


#### struct `FOperationNameColumn`  
`struct FOperationNameColumn final : public FEditorDataStorageColumn`  
_L11-16_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Name"))`
- inherits: `FEditorDataStorageColumn`
- L15 _public member_ `FName Value;`

#### struct `FOperationProbeColumn`  
`struct FOperationProbeColumn final : public FEditorDataStorageColumn`  
_L19-24_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Probe"))`
- inherits: `FEditorDataStorageColumn`
- L23 _public member_ `UE::Editor::DataStorage::Operations::FProbeCallback Callback;`

#### struct `FOperationTestColumn`  
`struct FOperationTestColumn final : public FEditorDataStorageColumn`  
_L27-32_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Test"))`
- inherits: `FEditorDataStorageColumn`
- L31 _public member_ `UE::Editor::DataStorage::Operations::FTestCallback Callback;`

#### struct `FOperationApplyColumn`  
`struct FOperationApplyColumn final : public FEditorDataStorageColumn`  
_L35-40_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Apply"))`
- inherits: `FEditorDataStorageColumn`
- L39 _public member_ `UE::Editor::DataStorage::Operations::FApplyCallback Callback;`

#### struct `FOperationPriorityColumn`  
`struct FOperationPriorityColumn final : public FEditorDataStorageColumn`  
_L43-48_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Priority"))`
- inherits: `FEditorDataStorageColumn`
- L47 _public member_ `int64 Value;`

#### Free symbols / members of external scopes

- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace Editor` (scope `UE`)
- L50 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L50 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L53 _typedef_ `using FNameColumn = FOperationNameColumn;` (scope `UE::Editor::DataStorage::Operations`) — Column for the name of the operation.
- L55 _typedef_ `using FProbeColumn = FOperationProbeColumn;` (scope `UE::Editor::DataStorage::Operations`) — Probe call column, to test superficially if a given input is potentially acceptable for the operation.
- L57 _typedef_ `using FTestColumn = FOperationTestColumn;` (scope `UE::Editor::DataStorage::Operations`) — Test call column, to query if the operation for a given input can be executed.
- L59 _typedef_ `using FApplyColumn = FOperationApplyColumn;` (scope `UE::Editor::DataStorage::Operations`) — Apply call column, to execute the operation for a given input.
- L61 _typedef_ `using FPriorityColumn = FOperationPriorityColumn;` (scope `UE::Editor::DataStorage::Operations`) — Priority value of this operation. Used for the default sorting when calling the operation system.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/TedsOperationInput.h` (Public)


#### struct `FOperationSourceColumn`  
`struct FOperationSourceColumn final : public FEditorDataStorageColumn`  
_L12-17_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Input Source"))`
- inherits: `FEditorDataStorageColumn`
- L16 _public member_ `UE::Editor::DataStorage::RowHandle Value;`

#### struct `FOperationDescriptionColumn`  
`struct FOperationDescriptionColumn final : public FEditorDataStorageColumn`  
_L20-25_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Input Description"))`
- inherits: `FEditorDataStorageColumn`
- L24 _public member_ `FText Value;`

#### struct `FOperationTestResultTag`  
`struct FOperationTestResultTag final : public FEditorDataStorageTag`  
_L28-31_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Test Result"))`
- inherits: `FEditorDataStorageTag`

#### struct `FOperationResultColumn`  
`struct FOperationResultColumn final : public FEditorDataStorageColumn`  
_L34-39_
- reflection: `USTRUCT(meta = (DisplayName = "Operation Result"))`
- inherits: `FEditorDataStorageColumn`
- L38 _public member_ `UE::Editor::DataStorage::Operations::FResult Value;`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Editor` (scope `UE`)
- L41 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L41 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L44 _typedef_ `using FSourceColumn = FOperationSourceColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds a general purpose source row for the operation.
- L46 _typedef_ `using FDescriptionColumn = FOperationDescriptionColumn;` (scope `UE::Editor::DataStorage::Operations`) — Holds a description which the operation may write to.
- L48 _typedef_ `using FTestResultTag = FOperationTestResultTag;` (scope `UE::Editor::DataStorage::Operations`) — Denotes that the test operation has been successful.
- L50 _typedef_ `using FResultColumn = FOperationResultColumn;` (scope `UE::Editor::DataStorage::Operations`) — Denotes that the operation has been sucessful.
- L52 _namespace_ `namespace Utilities` (scope `UE::Editor::DataStorage::Operations`)
- L55 _function_ `inline RowHandle GetSourceRow(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the value of the source column, if set.
- L62 _function_ `inline FText* GetDescriptionPtr(ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns a pointer to the description text, if set.
- L69 _function_ `inline const FText* GetDescriptionPtr(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns a pointer to the description text, if set.
- L76 _function_ `inline FText GetDescription(const ICoreProvider& Storage, RowHandle InputRow)` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the description text as a value.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/TedsOperationResult.h` (Public)


#### struct `UE::Editor::DataStorage::Operations::FResult`  
`struct FResult`  
_L10-15_
- L12 _public member_ `FRowHandleArray Created;`
- L13 _public member_ `FRowHandleArray Changed;`
- L14 _public member_ `FRowHandleArray Removed;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L7 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOperations/Public/TedsOperationSystem.h` (Public)


#### class `UOperationSystem`  
`class UOperationSystem : public UEditorDataStorageFactory`  
_L33-114_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UEditorDataStorageFactory`
- desc: System to execute externally customizable logic for a given purpose and input. By deriving this type, an "OperationSystem" for a specific purpose may be created, to which customizable "Operations" can be registered. The system may then be invoked to "test" or "apply" a registered operation that fits the given input.
- L37 _public member_ `static constexpr int64 DefaultPriority = 0;`
- L39 _public typedef_ `using FFilter = TFunction<bool(const UE::Editor::DataStorage::ICoreProvider&, UE::Editor::DataStorage::RowHandle)>;`
- L40 _public typedef_ `using FLess = TFunction<bool(const UE::Editor::DataStorage::ICoreProvider&, UE::Editor::DataStorage::RowHandle, UE::Editor::DataStorage::RowHandle)>;`
- L49 _public prototype_ `UOperationSystem();`
- L52 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& Storage) override;`
- L53 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& Storage) override;`
- L54 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& Storage) override;`
- L57 _public prototype_ `UE::Editor::DataStorage::RowHandle AddOperation(FName Name, TNotNull<UE::Editor::DataStorage::Operations::FApplyCallback> Operation, UE::Editor::DataStorage::Operations::FTestCallback Test, UE::Editor::DataStorage::Operations::FProbeCallback Probe, int64 Priority = DefaultPriority);` — Utility method to create a row with columns for the given input operation.
- L67 _public prototype_ `void GetOperations(TArray<UE::Editor::DataStorage::RowHandle>& OutRows, UE::Editor::DataStorage::RowHandle InputRow, const FFilter& Filter = {}, const FLess& Less = FDefaultLess()) const;` — Retrieves all operation rows that accept (probe call) the given input row. @param OutRows The array to fill with the operation rows. @param InputRow The row that contains input data that will be passed to the operations. @param Filter [optional] Predicate that can be used to customarily filter the operation rows. False = Skip, True = Keep. @param Less [optional] Sorter that can be used to customarily sort the operation rows.
- L76 _public prototype_ `int32 Test(UE::Editor::DataStorage::FRowHandleArrayView InputRows, const FFilter& Filter = {}, const FLess& Less = FDefaultLess()) const;` — Invokes the Test callback for each input row for all operations that accept (probe call) it and writes the result of the first success to the input row. @param InputRows The rows that contain input data that will be passed to the operations. @param Filter [optional] Predicate that can be used to customarily filter the operation rows. False = Skip, True = Keep. @param Less [optional] Sorter that can be used to customarily sort the operation rows. @returns The number of successfully tested input rows.
- L84 _public prototype_ `int32 Apply(UE::Editor::DataStorage::FRowHandleArrayView InputRows, const FFilter& Filter = {}, const FLess& Less = FDefaultLess()) const;` — Invokes the Apply callback for each input row for all operations that accept (probe call) it and writes the result of the first success to the input row. @param InputRows The rows that contain input data that will be passed to the operations. @param Filter [optional] Predicate that can be used to customarily filter the operation rows. False = Skip, True = Keep. @param Less [optional] Sorter that can be used to customarily sort the operation rows. @returns The number of successfully applied input rows.
- L95 _public prototype_ `bool CreateInputRows(UE::Editor::DataStorage::FRowHandleArray& OutRows, UE::Editor::DataStorage::FRowHandleArrayView SourceRows, bool bAddDescription = false) const;` — Utility method to create a batch of rows that can be used as input for operations. The method will create as many rows as source rows were passed in and automatically assign the FSourceColumn. The source rows will be the ones the operation should consider. @OutInputRows The array to fill with the input rows that were created. @SourceRows The array holding the source rows that should be considered by the operation. Automatically assigned to the FSourceColumn. @bAddDescription Whether the FDescriptionColumn should be added to the input rows. Holds an FText which the operation may write to. @returns True if the requested number of rows were successfully created, otherwise false.
- L99 _public prototype_ `void RemoveInputRows(UE::Editor::DataStorage::FRowHandleArrayView RowsToRemove) const;` — Utility method to remove a batch of rows.
- L102 _protected prototype_ `virtual void GetQueryDescription(UE::Editor::DataStorage::FQueryDescription& OutDescription) const;`
- L105 _protected member_ `UE::Editor::DataStorage::ICoreProvider* StoragePtr;`
- L106 _protected member_ `UE::Editor::DataStorage::TableHandle OperationTable;`
- L107 _protected member_ `TSharedPtr<UE::Editor::DataStorage::QueryStack::IQueryNode> QueryNode;`
- L108 _protected member_ `TSharedPtr<UE::Editor::DataStorage::QueryStack::IRowNode> ResultsNode;`
- L109 _protected member_ `TSharedPtr<UE::Editor::DataStorage::QueryStack::FExplicitUpdateExecutor> Executor;`
- L112 _protected member_ `UE::Editor::DataStorage::TableHandle InputTable;`
- L113 _protected member_ `UE::Editor::DataStorage::TableHandle InputTableDescr;`

#### struct `UOperationSystem::FDefaultLess`  
`struct FDefaultLess`  
_L43-46_
- desc: Default sorter for invoking an OperationSystem. Sorts by priority column first and name column second.
- L45 _public prototype_ `bool operator()(const UE::Editor::DataStorage::ICoreProvider& Storage, UE::Editor::DataStorage::RowHandle A, UE::Editor::DataStorage::RowHandle B) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOPERATIONS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
