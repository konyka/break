# Editor / SequencerCore

- module root: `Source/Editor/SequencerCore`
- headers: 104; symbols: 2335
- symbol kinds: class=112, delegate=12, enum=31, enumerator=132, function=500, macro=68, member=416, namespace=206, prototype=728, struct=93, typedef=37
- PrivateDependencyModuleNames: EditorFramework, EditorStyle, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, CurveEditor, Engine, GraphEditor, InputCore, Slate, SlateCore, TimeManagement

### `Source/Editor/SequencerCore/Private/MVVM/ViewModels/OutlinerColumns/OutlinerColumnTypesPrivate.h` (Private)


#### struct `UE::Sequencer::FOutlinerHeaderRowWidgetMetaData`  
`struct FOutlinerHeaderRowWidgetMetaData : ISlateMetaData`  
_L12-17_
- inherits: `ISlateMetaData`
- L14 _public prototype_ `SLATE_METADATA_TYPE(FOutlinerHeaderRowWidgetMetaData, ISlateMetaData) TArray<FOutlinerColumnLayout> Columns;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Private/MVVM/Views/OutlinerColumns/SDeactivateColumnWidget.h` (Private)


#### class `UE::Sequencer::SDeactivateColumnWidget`  
`class SDeactivateColumnWidget : public SColumnToggleWidget`  
_L16-53_
- inherits: `SColumnToggleWidget`
- desc: A widget that shows and controls the deactivated state of outliner items.
- L20 _public function_ `SLATE_BEGIN_ARGS(SDeactivateColumnWidget)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IOutlinerColumn> InWeakOutlinerColumn, const FCreateOutlinerColumnParams& InParams);`
- L26 _public prototype_ `virtual void OnToggleOperationComplete();` — Refreshes the Sequencer Tree.
- L32 _protected prototype_ `virtual bool IsActive() const override;` — Returns whether or not this item is deactivated.
- L35 _protected prototype_ `virtual void SetIsActive(const bool bInIsActive) override;` — Sets this item as activated or deactivated. If selected, applies to all selected items.
- L38 _protected prototype_ `virtual bool IsChildActive() const override;` — Returns whether or not a child of this item is deactivated.
- L41 _protected prototype_ `virtual bool IsImplicitlyActive() const override;` — Returns true if this item is implicitly deactivated, but not directly deactivated
- L44 _protected prototype_ `virtual const FSlateBrush* GetActiveBrush() const override;` — Returns the brush to display when this item is deactivated.
- L49 _private prototype_ `void SetIsActive_Internal(const FViewModelPtr& ViewModel, const bool bInIsActive);`
- L52 _private member_ `TWeakViewModelPtr<FDeactiveStateCacheExtension> WeakStateCacheExtension;` — Weak cache extension ptr (can be null).

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Private/MVVM/Views/OutlinerColumns/SLockColumnWidget.h` (Private)


#### class `UE::Sequencer::SLockColumnWidget`  
`class SLockColumnWidget : public SColumnToggleWidget`  
_L15-41_
- inherits: `SColumnToggleWidget`
- desc: A widget that shows and controls the locked state of outliner items.
- L19 _public function_ `SLATE_BEGIN_ARGS(SLockColumnWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IOutlinerColumn> InWeakOutlinerColumn, const FCreateOutlinerColumnParams& InParams);`
- L26 _public prototype_ `virtual bool IsActive() const override;` — Returns whether or not this outliner item is locked.
- L29 _public prototype_ `virtual void SetIsActive(const bool bInIsActive) override;` — Sets this item and it's sections as locked or unlocked. If selected, applies to all selected items.
- L32 _public prototype_ `virtual bool IsChildActive() const override;` — Returns whether or not a child of this item is locked.
- L35 _public prototype_ `virtual const FSlateBrush* GetActiveBrush() const override;` — Returns the brush to display when this item is locked.
- L40 _private member_ `TWeakViewModelPtr<FLockStateCacheExtension> WeakLockStateCacheExtension;` — Weak cache extension ptr (can be null).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Private/MVVM/Views/OutlinerColumns/SMuteColumnWidget.h` (Private)


#### class `UE::Sequencer::SMuteColumnWidget`  
`class SMuteColumnWidget : public SColumnToggleWidget`  
_L15-54_
- inherits: `SColumnToggleWidget`
- desc: A widget that shows and controls the muted state of outliner items.
- L19 _public function_ `SLATE_BEGIN_ARGS(SMuteColumnWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IOutlinerColumn> InWeakOutlinerColumn, const FCreateOutlinerColumnParams& InParams);`
- L27 _public prototype_ `virtual void OnToggleOperationComplete();` — Refreshes the Sequencer Tree to handle simultaneous mute and solo modifiers.
- L31 _protected prototype_ `virtual bool IsActive() const override;` — Returns whether or not this item is muted.
- L34 _protected prototype_ `virtual void SetIsActive(const bool bInIsActive) override;` — Sets this item as muted or unmuted. If selected, applies to all selected items.
- L37 _protected prototype_ `virtual bool IsChildActive() const override;` — Returns whether or not a child of this item is muted.
- L40 _protected prototype_ `virtual bool IsImplicitlyActive() const override;` — Returns true if this item is implicitly active, but not directly active
- L43 _protected prototype_ `virtual const FSlateBrush* GetActiveBrush() const override;` — Returns the brush to display when this item is muted.
- L46 _protected prototype_ `virtual const FSlateBrush* GetInactiveBrush() const override;` — Returns the brush to display when this item is not muted.
- L50 _private prototype_ `void SetIsActive_Internal(const FViewModelPtr& ViewModel, const bool bInIsActive);`
- L53 _private member_ `TWeakViewModelPtr<FMuteStateCacheExtension> WeakMuteStateCacheExtension;` — Weak cache extension ptr (can be null).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Private/MVVM/Views/OutlinerColumns/SSoloColumnWidget.h` (Private)


#### class `UE::Sequencer::SSoloColumnWidget`  
`class SSoloColumnWidget : public SColumnToggleWidget`  
_L15-50_
- inherits: `SColumnToggleWidget`
- desc: A widget that shows and controls the soloed state of outliner items.
- L19 _public function_ `SLATE_BEGIN_ARGS(SSoloColumnWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IOutlinerColumn> InWeakOutlinerColumn, const FCreateOutlinerColumnParams& InParams);`
- L27 _public prototype_ `virtual void OnToggleOperationComplete();` — Refreshes the Sequencer Tree to show other outliner items as greyed out if they are not also soloed.
- L32 _protected prototype_ `virtual bool IsActive() const override;` — Returns whether or not this outliner item is soloed.
- L35 _protected prototype_ `virtual void SetIsActive(const bool bInIsActive) override;` — Sets this item as soloed or not soloed. If selected, applies to all selected items.
- L38 _protected prototype_ `virtual bool IsChildActive() const override;` — Returns whether or not a child of this item is soloed.
- L41 _protected prototype_ `virtual bool IsImplicitlyActive() const override;` — Returns true if this item is implicitly active, but not directly active
- L44 _protected prototype_ `virtual const FSlateBrush* GetActiveBrush() const override;` — Returns the brush to display when this item is pinned.
- L49 _private member_ `TWeakViewModelPtr<FSoloStateCacheExtension> WeakSoloStateCacheExtension;` — Weak cache extension ptr (can be null).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Private/MVVM/Views/SOutlinerViewRowPanel.h` (Private)


#### class `UE::Sequencer::SOutlinerViewRowPanel`  
`class SOutlinerViewRowPanel : public SPanel`  
_L14-65_
- inherits: `SPanel`
- L19 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGenerateCellContent, const FName&) SLATE_BEGIN_ARGS(SOutlinerViewRowPanel)`
- L22 _public function_ `SLATE_EVENT(FOnGenerateCellContent, OnGenerateCellContent) SLATE_END_ARGS() SOutlinerViewRowPanel() : Children(this)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SHeaderRow> InHeaderRow);`
- L33 _private prototype_ `void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L35 _private prototype_ `void HandleColumnsUpdated(const TSharedRef<SHeaderRow>&);`
- L37 _private prototype_ `void UpdateCells();`
- L42 _private prototype_ `FVector2D ComputeDesiredSize(float) const override;` — ~ SPanel Interface
- L43 _private prototype_ `FChildren* GetChildren() override;`
- L62 _private member_ `TPanelChildren<FSlot> Children;`
- L63 _private member_ `TWeakPtr<SHeaderRow> WeakHeaderRow;`
- L64 _private member_ `FOnGenerateCellContent GenerateCellContentEvent;`

#### struct `UE::Sequencer::SOutlinerViewRowPanel::FSlot`  
`struct FSlot : public TWidgetSlotWithAttributeSupport<FSlot>`  
_L47-60_
- inherits: `TWidgetSlotWithAttributeSupport<FSlot>`
- L49 _public prototype_ `SLATE_SLOT_BEGIN_ARGS(FSlot, TWidgetSlotWithAttributeSupport<FSlot>) SLATE_ARGUMENT(FName, ColumnId) SLATE_SLOT_END_ARGS() FName ColumnId;`
- L55 _public function_ `void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGenerateCellContent, const FName&) SLATE_BEGIN_ARGS(SOutlinerViewRowPanel){} SLATE_EVENT(FOnGenerateCellContent, OnGenerateCellContent) SLATE_END_ARGS() SOutlinerViewRowPanel() : Children(this) {} void Construct(const FArguments& InArgs, TSharedRef<SHeaderRow> InHeaderRow);`

### `Source/Editor/SequencerCore/Private/SequencerCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSequencerCore, Log, All);`

### `Source/Editor/SequencerCore/Public/ISequencerCoreModule.h` (Public)


#### class `UE::Sequencer::ISequencerCoreModule`  
`class ISequencerCoreModule : public IModuleInterface`  
_L19-80_
- inherits: `IModuleInterface`
- desc: Interface for the Sequencer module.
- L33 _public prototype_ `virtual FDelegateHandle RegisterModelType(const TWeakObjectPtr<UClass>& WeakClass, TFunction<TSharedPtr<FViewModel>(UObject*)> FactoryFunctor) = 0;` — Register a new MVVM view model type factory functor that will be used for any UObjects of the specified class type @note It is a violation to attempt to register multiple functors for the same class type @param WeakClass       A weak pointer to the class type that should invoke this factory @param FactoryFunctor  The functor that defines how to create a view model for the object @return A delegate handle that can be passed to UnRegisterModelType to unregister this factory
- L41 _public prototype_ `virtual void UnRegisterModelType(FDelegateHandle Handle) = 0;` — Unregister a previously registered view model type @param Handle  The handle to the factory functor that was provided from calling RegisterModelType
- L50 _public prototype_ `virtual TSharedPtr<FViewModel> FactoryNewModel(UObject* Object) const = 0;` — Attempt to create a new model type for the specified object @param Object  The object to create a view model for @return A pointer to a new view-model, or nullptr if the object didn't match any registered class.
- L63 _public function_ `template<typename T> FDelegateHandle RegisterModelType(const TWeakObjectPtr<UClass>& WeakClass, TViewModelTypeID<T> Type)` — Register a new MVVM view model type from a view model type ID that will be used for any UObjects of the specified class type @param Object  The object to create a view model for @param Type    The view model type ID to create for UObjects of type WeakClass @return A delegate handle that can be passed to UnRegisterModelType to unregister this factory
- L79 _private prototype_ `void InitializeObjectModel(const FViewModelPtr& ViewModel, UObject* Object);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L66 _function_ `` (scope `UE::Sequencer::ISequencerCoreModule::RegisterModelType`)

### `Source/Editor/SequencerCore/Public/ISequencerEditTool.h` (Public)


#### class `UE::Sequencer::ISequencerEditToolDragOperation`  
`class ISequencerEditToolDragOperation`  
_L24-67_
- desc: Interface for drag and drop operations that are handled by edit tools in Sequencer.
- L35 _public prototype_ `virtual void OnBeginDrag(const FPointerEvent& MouseEvent, FVector2D LocalMousePos, const FVirtualTrackArea& VirtualTrackArea) = 0;` — Called to initiate a drag @param MouseEvent		The associated mouse event for dragging @param LocalMousePos		The current location of the mouse, relative to the top-left corner of the physical track area @param VirtualTrackArea	A virtual track area that can be used for pixel->time conversions and hittesting
- L44 _public prototype_ `virtual void OnDrag(const FPointerEvent& MouseEvent, FVector2D LocalMousePos, const FVirtualTrackArea& VirtualTrackArea) = 0;` — Notification called when the mouse moves while dragging @param MouseEvent		The associated mouse event for dragging @param LocalMousePos		The current location of the mouse, relative to the top-left corner of the physical track area @param VirtualTrackArea	A virtual track area that can be used for pixel->time conversions and hittesting
- L52 _public prototype_ `virtual void OnEndDrag( const FPointerEvent& MouseEvent, FVector2D LocalMousePos, const FVirtualTrackArea& VirtualTrackArea) = 0;` — Called when a drag has ended @param MouseEvent		The associated mouse event for dragging @param LocalMousePos		The current location of the mouse, relative to the top-left corner of the physical track area @param VirtualTrackArea	A virtual track area that can be used for pixel->time conversions and hittesting
- L55 _public prototype_ `virtual FCursorReply GetCursor() const = 0;` — Request the cursor for this drag operation
- L58 _public prototype_ `virtual int32 OnPaint(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const = 0;` — Override to implement drag-specific paint logic
- L61 _public function_ `virtual TSharedPtr<FViewModel> GetDragOwnerTrackModel() const` — Get the track model that owns this drag operation (for hover suppression). Returns nullptr if not applicable.
- L66 _public prototype_ `virtual ~ISequencerEditToolDragOperation() = default;` — Virtual destructor.

#### class `UE::Sequencer::ISequencerEditTool`  
`class ISequencerEditTool : public ISequencerInputHandler`  
_L73-112_
- inherits: `ISequencerInputHandler`
- desc: Interface for edit tools in Sequencer.
- L76 _public prototype_ `virtual ~ISequencerEditTool() override = default;`
- L79 _public function_ `virtual void OnMouseCaptureLost()` — `UE_DEPRECATED(5.8, "OnMouseCaptureLost has been deprecated. Please override OnMouseCaptureLost from ISequencerInputHandler instead.")`
- L81 _public function_ `virtual FCursorReply OnCursorQuery(const SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) const override`
- L90 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) const` — `UE_DEPRECATED(5.8, "OnCursorQuery has been deprecated. Please override OnCursorQuery from ISequencerInputHandler instead.")`
- L93 _public function_ `virtual void OnMouseEnter(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)` — `UE_DEPRECATED(5.8, "OnMouseEnter has been deprecated. Please override OnMouseEnter from ISequencerInputHandler instead.")`
- L96 _public function_ `virtual void OnMouseLeave(SWidget& OwnerWidget, const FPointerEvent& InPointerEvent)` — `UE_DEPRECATED(5.8, "OnMouseLeave has been deprecated. Please override OnMouseLeave from ISequencerInputHandler instead.")`
- L99 _public function_ `virtual FReply OnKeyDown(SWidget& OwnerWidget, const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)` — `UE_DEPRECATED(5.8, "OnKeyDown has been deprecated. Please override OnKeyDown from ISequencerInputHandler instead.")`
- L102 _public function_ `virtual FReply OnKeyUp(SWidget& OwnerWidget, const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)` — `UE_DEPRECATED(5.8, "OnKeyUp has been deprecated. Please override OnKeyUp from ISequencerInputHandler instead.")`
- L104 _public prototype_ `virtual FName GetIdentifier() const = 0;`
- L106 _public function_ `virtual bool CanDeactivate() const`
- L108 _public prototype_ `virtual int32 OnPaint(const FGeometry& InGeometry, const FSlateRect& InCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const = 0;`
- L110 _public function_ `virtual TSharedPtr<ITrackAreaHotspot> GetDragHotspot() const`
- L111 _public function_ `virtual ISequencerEditToolDragOperation* GetCurrentDragOperation() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/ISequencerInputHandler.h` (Public)


#### struct `ISequencerInputHandler`  
`struct ISequencerInputHandler`  
_L13-33_
- desc: Common base-class for objects that handle input in the sequencer.
- L15 _public prototype_ `virtual ~ISequencerInputHandler() = default;`
- L17 _public function_ `virtual FCursorReply OnCursorQuery(const SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) const`
- L19 _public function_ `virtual void OnMouseEnter(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L20 _public function_ `virtual void OnMouseLeave(SWidget& OwnerWidget, const FPointerEvent& InPointerEvent)`
- L21 _public function_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L22 _public function_ `virtual void OnMouseCaptureLost()`
- L24 _public function_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L25 _public function_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L26 _public function_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L27 _public function_ `virtual FReply OnMouseWheel(SWidget& OwnerWidget, const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L29 _public function_ `virtual FReply OnKeyDown(SWidget& OwnerWidget, const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)`
- L30 _public function_ `virtual FReply OnKeyUp(SWidget& OwnerWidget, const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)`
- L32 _public function_ `virtual void OnFocusLost(SWidget& OwnerWidget, const FFocusEvent& InFocusEvent)`

### `Source/Editor/SequencerCore/Public/MVVM/CastableTypeTable.h` (Public)


#### struct `UE::Sequencer::FCastableTypeTable`  
`struct FCastableTypeTable`  
_L25-249_
- L27 _public prototype_ `explicit FCastableTypeTable(uint8* InTypeMaskStorage);`
- L29 _public prototype_ `FCastableTypeTable(const FCastableTypeTable&) = delete;`
- L30 _public prototype_ `void operator=(const FCastableTypeTable&) = delete;`
- L31 _public prototype_ `FCastableTypeTable(FCastableTypeTable&&) = delete;`
- L32 _public prototype_ `void operator=(FCastableTypeTable&&) = delete;`
- L39 _public function_ `template<typename T> static FCastableTypeTable* MakeTypeTable(const void* Unused, uint32 TypeID, FName InName)` — Make a new type table for the templated type, ID and typename. The new table is allocated using malloc and is intentionally leaked
- L44 _public function_ `template<typename T> static FCastableTypeTable* MakeTypeTable(const ICastable* Unused, uint32 TypeID, FName InName)`
- L51 _public function_ `template<typename T> static FCastableTypeTable* MakeTypeTable(const IDynamicExtension* Unused, uint32 TypeID, FName InName)`
- L61 _public prototype_ `static const FCastableTypeTable* FindTypeByName(FName InName);` — Attempt to locate a type table by its C++ name
- L70 _public function_ `const void* Cast(const ICastable* BasePtr, uint32 ToType) const` — Use this type table to cast the specified base ptr to another type @note BasePtr must be an instance of the type specified by this type table, or the result is undefined. @return BasePtr casted to the type ID specified by ToType, or nullptr if the cast failed
- L82 _public function_ `const void* Cast(const IDynamicExtension* BasePtr, uint32 ToType) const` — Use this type table to cast the specified base ptr to another type @note BasePtr must be an instance of the type specified by this type table, or the result is undefined. @return BasePtr casted to the type ID specified by ToType, or nullptr if the cast failed
- L90 _public function_ `FName GetTypeName() const` — Retrieve the C++ type name that this type table relates to
- L100 _public function_ `uint32 GetTypeID() const` — Retrieve the type ID for this type table. Warning: This type ID is not deterministic or stable across different processes and should not be saved persistently
- L110 _private function_ `const void* CastImpl(const void* BasePtr, uint32 ToType) const` — Cast implementation function
- L240 _private member_ `int16* StaticTypeOffsets;` — Ptr to the static type offsets allocated at the end of this struct. Size = NumStaticTypes
- L242 _private member_ `MovieScene::TFixedSparseBitSet<uint32, MovieScene::TFixedSparseBitSetBucketStorage<uint8>> TypeMask;` — Fixed sparse bitset of types that this table contains. Storage is allocated at the end of this struct.
- L244 _private member_ `uint32 NumStaticTypes;` — The number of static types implemented within this type table.
- L246 _private member_ `uint32 ThisTypeID;` — Unique static type ID for this type.
- L248 _private member_ `FName ThisTypeName;` — The name of the C++ type that this table relates to.

#### struct `UE::Sequencer::FCastableTypeTable::FCastableTypeTableGenerator`  
`struct FCastableTypeTableGenerator`  
_L123-235_
- desc: Utility class that generates a type table used for dynamic casting and instance of an ICastable object
- L129 _public function_ `template<typename T> void Generate()` — Generate the type table from a template type
- L139 _public prototype_ `FCastableTypeTable* Commit(uint32 TypeID, FName InName);` — Commit this generator to its final form
- L147 _public function_ `template<typename FromType, typename ToType> static int16 ClassOffsetFrom()` — Compute the ptr offset from one class to another in an inheritance hierarchy. @note: This can be negative for situations where multiple inheritance would put the FromType class after the ToType in memory.
- L165 _public function_ `template<typename T> static int16 ComputeStartOffset(const ICastable*)` — Compute the start offset from an ICastable type to the root of T This offset is added to all other class offsets that are computed from T so that we can always cast from an ICastable* to the concrete types
- L176 _public function_ `template<typename T> static int16 ComputeStartOffset(const IDynamicExtension*)` — Compute the start offset from an IDynamicExtension type to the root of T This offset is added to all other class offsets that are computed from T so that we can always cast from an IDynamicExtension* to the concrete types
- L181 _public function_ `uint32 ByteSize() const`
- L187 _public function_ `template<typename StartClass, typename T, typename U = typename T::Implements> void ConsumeImplements(T*, int16 StartOffset)`
- L193 _public function_ `template<typename StartClass> void ConsumeImplements(...)`
- L198 _public function_ `template<typename StartClass, typename ...Types> void ConsumeImplementsImpl(TImplements<Types...>*, int16 StartOffset)`
- L205 _public function_ `template<typename StartClass, typename T> void ConsumeImplements(void*, int16 StartOffset)`
- L210 _public function_ `template<typename StartClass, typename T, typename U = decltype(T::ID)> void AddStaticType(T*, int16 StartOffset)`
- L225 _public function_ `template<typename StartClass> constexpr void AddStaticType(void*, int16 StartOffset)`
- L232 _private member_ `MovieScene::TFixedSparseBitSet<uint32> TypeMask;` — Accumulator sparse bitset of types that are implemented on the type that Generate was called with
- L234 _private member_ `TArray<int16> StaticTypeOffsets;` — Typeoffsets from T to the ptr for each type within TypeMask

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/DynamicExtensionContainer.h` (Public)


#### class `UE::Sequencer::IDynamicExtension`  
`class IDynamicExtension : public TSharedFromThis<IDynamicExtension>`  
_L35-49_
- inherits: `TSharedFromThis<IDynamicExtension>`
- desc: Base class for dynamic extensions that can be added to sequence data models and participate in dynamic casting.
- L44 _public function_ `virtual void OnCreated(TSharedRef<FViewModel> InWeakOwner)` — Called when the extension is created on a data model
- L46 _public function_ `virtual void OnPostInitialize()` — Called after all extensions have been created on a data model
- L48 _public function_ `virtual void OnReinitialize()` — Called to reinitialize extensions after a major change

#### class `UE::Sequencer::FDynamicExtensionContainer`  
`class FDynamicExtensionContainer`  
_L57-201_
- desc: Base class for supporting dynamic extensions that participate in dynamic casting.
- L61 _public prototype_ `virtual ~FDynamicExtensionContainer() = default;`
- L63 _public prototype_ `FDynamicExtensionContainer() = default;`
- L65 _public prototype_ `FDynamicExtensionContainer(const FDynamicExtensionContainer&) = delete;`
- L66 _public prototype_ `FDynamicExtensionContainer& operator=(const FDynamicExtensionContainer&) = delete;`
- L73 _public function_ `template<typename T> const T* CastDynamic() const`
- L80 _public function_ `template<typename T> const T* CastDynamicChecked() const`
- L87 _public function_ `template<typename T> T* CastDynamic()`
- L93 _public function_ `template<typename T> T* CastDynamicChecked()`
- L99 _public function_ `template<typename T> TDynamicExtensionContainerIteratorProxy<T> FilterDynamic()`
- L104 _public prototype_ `const void* CastDynamic(FViewModelTypeID Type) const;`
- L105 _public prototype_ `void RemoveDynamicExtension(FViewModelTypeID Type);`
- L107 _public function_ `const void* CastDynamicChecked(FViewModelTypeID Type) const`
- L114 _public function_ `void* CastDynamic(FViewModelTypeID Type)`
- L119 _public function_ `void* CastDynamicChecked(FViewModelTypeID Type)`
- L129 _protected function_ `template<typename T, typename... InArgTypes> T& AddDynamicExtension(TSharedRef<FViewModel> InOwner, InArgTypes&&... Args)`
- L144 _protected function_ `template<typename T> void RemoveDynamicExtension()`
- L149 _protected function_ `void PostInitializeExtensions()`
- L169 _protected function_ `void ReinitializeExtensions()`
- L200 _private member_ `TArray<FDynamicExtensionInfo> DynamicExtensions;`

#### struct `UE::Sequencer::FDynamicExtensionContainer::FDynamicExtensionInfo`  
`struct FDynamicExtensionInfo`  
_L194-198_
- L196 _public member_ `FCastableTypeTable* TypeTable;`
- L197 _public member_ `TSharedPtr<IDynamicExtension> Extension;`

#### struct `UE::Sequencer::FDynamicExtensionContainerIterator`  
`struct FDynamicExtensionContainerIterator`  
_L203-224_
- L205 _public function_ `explicit operator bool() const`
- L210 _public prototype_ `FDynamicExtensionContainerIterator& operator++();`
- L215 _protected typedef_ `using IteratorType = TArray<FDynamicExtensionContainer::FDynamicExtensionInfo>::TConstIterator;`
- L219 _protected prototype_ `explicit FDynamicExtensionContainerIterator(IteratorType&& InIterator, FViewModelTypeID InType);`
- L221 _protected member_ `void* CurrentExtension = nullptr;`
- L222 _protected member_ `IteratorType Iterator;`
- L223 _protected member_ `FViewModelTypeID Type;`

#### struct `UE::Sequencer::TDynamicExtensionContainerIteratorProxy`  
`template<typename T> struct TDynamicExtensionContainerIteratorProxy`  
_L227-242_
- L229 _public function_ `FORCEINLINE TDynamicExtensionContainerIterator<T> begin()`
- L230 _public function_ `FORCEINLINE TDynamicExtensionContainerIterator<T> end()`
- L235 _private typedef_ `using IteratorType = TArray<FDynamicExtensionContainer::FDynamicExtensionInfo>::TConstIterator;`
- L237 _private function_ `TDynamicExtensionContainerIteratorProxy(FDynamicExtensionContainer* InContainer) : Container(InContainer)`
- L241 _private member_ `FDynamicExtensionContainer* Container;`

#### struct `UE::Sequencer::TDynamicExtensionContainerIterator`  
`template<typename T> struct TDynamicExtensionContainerIterator : FDynamicExtensionContainerIterator`  
_L245-259_
- inherits: `FDynamicExtensionContainerIterator`
- L247 _public function_ `T& operator*() const`
- L256 _protected function_ `explicit TDynamicExtensionContainerIterator(FDynamicExtensionContainerIterator::IteratorType InIterator) : FDynamicExtensionContainerIterator(MoveTemp(InIterator), T::ID)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERCORE_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FDynamicExtensionCallback, TSharedRef<FViewModel>);`
- L51 _prototype_ `DECLARE_DELEGATE_OneParam(FDynamicExtensionCallback, TSharedRef<FViewModel>);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/HierarchicalCacheExtension.h` (Public)


#### class `UE::Sequencer::IHierarchicalCache`  
`class IHierarchicalCache`  
_L28-40_
- L36 _public prototype_ `virtual void BeginUpdate() = 0;`
- L37 _public prototype_ `virtual void PreVisitChildren(const FViewModelPtr& ViewModel) = 0;`
- L38 _public prototype_ `virtual void PostVisitChildren(const FViewModelPtr& ViewModel) = 0;`
- L39 _public prototype_ `virtual void EndUpdate() = 0;`

#### class `UE::Sequencer::FHierarchicalCacheExtension`  
`class FHierarchicalCacheExtension : public IDynamicExtension`  
_L43-70_
- inherits: `IDynamicExtension`
- L48 _public prototype_ `~FHierarchicalCacheExtension();`
- L50 _public member_ `FPreUpdateCachesEvent PreUpdateCachesEvent;`
- L52 _public prototype_ `void Initialize(const FViewModelPtr& InRootModel);`
- L54 _public prototype_ `void OnCreated(TSharedRef<FViewModel> InWeakOwner) override;`
- L56 _public prototype_ `void OnHierarchyUpdated();`
- L58 _public prototype_ `void UpdateCachedFlags();`
- L59 _public prototype_ `void UpdateAllCachedFlags(const FViewModelPtr& ViewModel, TArrayView<IHierarchicalCache* const> HierarchicalCaches);`
- L63 _private prototype_ `void UpdateCachedFlagsForModel(const FViewModelPtr& ViewModel, TArrayView<IHierarchicalCache* const> HierarchicalCaches);`
- L67 _protected member_ `FWeakViewModelPtr WeakOwnerModel;`
- L68 _protected member_ `FWeakViewModelPtr WeakRootModel;`
- L69 _protected member_ `EViewModelListType ModelListFilter;`

#### class `UE::Sequencer::TFlagStateCacheExtension`  
`template<typename FlagsType> class TFlagStateCacheExtension : public IDynamicExtension , public IHierarchicalCache`  
_L75-147_
- inherits: `IDynamicExtension,IHierarchicalCache`
- L81 _public typedef_ `using Implements = TImplements<IDynamicExtension, IHierarchicalCache>;`
- L83 _public prototype_ `virtual ~TFlagStateCacheExtension() = default;`
- L85 _public function_ `FlagsType GetRootFlags() const`
- L89 _public function_ `FlagsType GetCachedFlags(const FViewModelPtr& ViewModel) const`
- L93 _public function_ `FlagsType GetCachedFlags(uint32 InModelID) const`
- L100 _private prototype_ `virtual FlagsType ComputeFlagsForModel(const FViewModelPtr& ViewModel) = 0;`
- L101 _private function_ `virtual void PostComputeChildrenFlags(const FViewModelPtr& ViewModel, FlagsType& OutThisModelFlags, FlagsType& OutPropagateToParentFlags)`
- L105 _protected function_ `void BeginUpdate() override`
- L111 _protected function_ `void PreVisitChildren(const FViewModelPtr& ViewModel) override`
- L117 _protected function_ `void PostVisitChildren(const FViewModelPtr& ViewModel) override`
- L132 _protected function_ `void EndUpdate() override`
- L143 _protected member_ `TArray<FlagsType> AccumulatedChildFlags;`
- L144 _protected member_ `TArray<FlagsType> IndividualItemFlags;`
- L145 _protected member_ `TMap<uint32, FlagsType> CachedFlagsFromNodeID;`
- L146 _protected member_ `FlagsType RootFlags;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L21 _function_ `template<typename EnumType> EnumType CombinePropagatedChildFlags(EnumType ParentFlags, EnumType CombinedChildFlags)` (scope `UE::Sequencer`)
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPreUpdateCachesEvent, FViewModelPtr);`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPreUpdateCachesEvent, FViewModelPtr);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDeactivatableExtension.h` (Public)


#### enum `UE::Sequencer::EDeactivatableState`  
`enum class EDeactivatableState`  
_L13-18_
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `Deactivated`
- L17 _public enumerator_ `PartiallyDeactivated`

#### class `UE::Sequencer::IDeactivatableExtension`  
`class IDeactivatableExtension`  
_L23-41_
- desc: An extension for outliner nodes that can be deactivated
- L28 _public prototype_ `virtual ~IDeactivatableExtension() = default;`
- L31 _public prototype_ `virtual bool IsDeactivated() const = 0;` — Returns whether this item is deactivated
- L34 _public prototype_ `virtual void SetIsDeactivated(const bool bInIsDeactivated) = 0;` — Set this item's deactivated state
- L37 _public function_ `virtual bool IsInheritable() const` — Returns whether this deactivatable can be deactivated by a parent, and should report its deactivated state to a parent

#### enum `UE::Sequencer::ECachedDeactiveState`  
`enum class ECachedDeactiveState`  
_L43-55_
- L45 _public enumerator_ `None = 0`
- L47 _public enumerator_ `Deactivatable = 1 << 0`
- L48 _public enumerator_ `DeactivatableChildren = 1 << 1`
- L49 _public enumerator_ `Deactivated = 1 << 2`
- L50 _public enumerator_ `PartiallyDeactivatedChildren = 1 << 3`
- L51 _public enumerator_ `ImplicitlyDeactivatedByParent = 1 << 4`
- L52 _public enumerator_ `Inheritable = 1 << 5`
- L54 _public enumerator_ `InheritedFromChildren = DeactivatableChildren | PartiallyDeactivatedChildren`

#### class `UE::Sequencer::FDeactiveStateCacheExtension`  
`class FDeactiveStateCacheExtension : public TFlagStateCacheExtension<ECachedDeactiveState>`  
_L60-69_
- inherits: `TFlagStateCacheExtension<ECachedDeactiveState>`
- L67 _private prototype_ `ECachedDeactiveState ComputeFlagsForModel(const FViewModelPtr& ViewModel) override;`
- L68 _private prototype_ `void PostComputeChildrenFlags(const FViewModelPtr& ViewModel, ECachedDeactiveState& OutThisModelFlags, ECachedDeactiveState& OutPropagateToParentFlags) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)
- L56 _prototype_ `ENUM_CLASS_FLAGS(ECachedDeactiveState) ECachedDeactiveState CombinePropagatedChildFlags(const ECachedDeactiveState ParentFlags, ECachedDeactiveState CombinedChildFlags);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDeletableExtension.h` (Public)


#### class `UE::Sequencer::IDeletableExtension`  
`class IDeletableExtension`  
_L16-26_
- L24 _public prototype_ `virtual bool CanDelete(FText* OutErrorMessage) const = 0;`
- L25 _public prototype_ `virtual void Delete() = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDimmableExtension.h` (Public)


#### class `UE::Sequencer::IDimmableExtension`  
`class IDimmableExtension`  
_L15-24_
- L23 _public prototype_ `virtual bool IsDimmed() const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDraggableOutlinerExtension.h` (Public)


#### class `UE::Sequencer::IDraggableOutlinerExtension`  
`class IDraggableOutlinerExtension`  
_L21-31_
- desc: Extension for models that can be dragged
- L30 _public prototype_ `virtual bool CanDrag() const = 0;` — Returns whether the model can be dragged

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDraggableTrackAreaExtension.h` (Public)


#### class `UE::Sequencer::IDragOperation`  
`class IDragOperation`  
_L23-33_
- desc: Interface for drag operations
- L26 _public prototype_ `virtual ~IDragOperation() = default;`
- L29 _public prototype_ `virtual void AddSnapTime(FFrameNumber SnapTime) = 0;` — Adds a time that the drag operation will snap to
- L32 _public prototype_ `virtual void AddModel(TSharedPtr<FViewModel> Model) = 0;` — Adds a model to the drag operation to be dragged

#### class `UE::Sequencer::IDraggableTrackAreaExtension`  
`class IDraggableTrackAreaExtension`  
_L38-52_
- desc: Extension for models that can be dragged
- L47 _public prototype_ `virtual bool CanDrag() const = 0;` — Returns whether the model can be dragged
- L49 _public prototype_ `virtual void OnBeginDrag(IDragOperation& DragOperation) = 0;` — Called at the beginning of the drag operation
- L51 _public prototype_ `virtual void OnEndDrag(IDragOperation& DragOperation) = 0;` — Called at the end of a drag operation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IDroppableExtension.h` (Public)


#### class `UE::Sequencer::IDroppableExtension`  
`class IDroppableExtension`  
_L21-34_
- desc: Extension for models that can be dragged
- L30 _public prototype_ `virtual bool CanAcceptDrag(IDragOperation& DragOperation, FText* OutInfo) const = 0;` — Check whether this droppable extension is able to accept the specified drag
- L31 _public prototype_ `virtual void OnHover(IDragOperation& DragOperation) = 0;`
- L32 _public prototype_ `virtual void ProcessDragOperation(IDragOperation& DragOperation) = 0;`
- L33 _public prototype_ `virtual void OnUnhover(IDragOperation& DragOperation) = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IGeometryExtension.h` (Public)


#### struct `UE::Sequencer::FVirtualGeometry`  
`struct FVirtualGeometry`  
_L20-53_
- desc: Virtual bounding box information for track area elements.
- L22 _public function_ `FVirtualGeometry() : Top(0.f), Height(0.f), NestedBottom(0.f)`
- L26 _public function_ `FVirtualGeometry(float InTop, float InHeight, float InNestedBottom) : Top(InTop), Height(InHeight), NestedBottom(InNestedBottom)`
- L30 _public function_ `float GetTop() const`
- L35 _public function_ `float GetHeight() const`
- L40 _public function_ `float GetNestedHeight() const`
- L45 _public function_ `float GetTotalChildHeight() const`
- L50 _public member_ `float Top;`
- L51 _public member_ `float Height;`
- L52 _public member_ `float NestedBottom;`

#### class `UE::Sequencer::IGeometryExtension`  
`class IGeometryExtension`  
_L58-70_
- desc: Interface for data models who can store virtual geometry information
- L66 _public prototype_ `virtual FVirtualGeometry GetVirtualGeometry() const = 0;`
- L67 _public prototype_ `virtual void ReportVirtualGeometry(const FVirtualGeometry& VirtualGeometry) = 0;`
- L69 _public prototype_ `static float UpdateVirtualGeometry(float InitialVirtualPosition, TSharedPtr<FViewModel> InInitialItem);`

#### class `UE::Sequencer::FGeometryExtensionShim`  
`class FGeometryExtensionShim : public IGeometryExtension`  
_L75-92_
- inherits: `IGeometryExtension`
- desc: Basic utility implementation of the IGeometryExtension interface
- L79 _public function_ `FVirtualGeometry GetVirtualGeometry() const override`
- L84 _public function_ `void ReportVirtualGeometry(const FVirtualGeometry& InVirtualGeometry) override`
- L91 _protected member_ `FVirtualGeometry VirtualGeometry;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IGroupableExtension.h` (Public)


#### class `UE::Sequencer::IGroupableExtension`  
`class IGroupableExtension`  
_L18-34_
- L26 _public prototype_ `virtual void GetIdentifierForGrouping(TStringBuilder<128>& OutString) const = 0;`
- L28 _public function_ `FString GetIdentifierForGrouping() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IHotspotExtension.h` (Public)


#### class `UE::Sequencer::IHotspotExtension`  
`class IHotspotExtension`  
_L15-22_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IHoveredExtension.h` (Public)


#### class `UE::Sequencer::IHoveredExtension`  
`class IHoveredExtension`  
_L15-27_
- L23 _public prototype_ `virtual bool IsHovered() const = 0;`
- L25 _public prototype_ `virtual void OnHovered() = 0;`
- L26 _public prototype_ `virtual void OnUnhovered() = 0;`

#### class `UE::Sequencer::FHoveredExtensionShim`  
`class FHoveredExtensionShim : public IHoveredExtension`  
_L29-41_
- inherits: `IHoveredExtension`
- L33 _public function_ `virtual bool IsHovered() const`
- L35 _public function_ `virtual void OnHovered()`
- L36 _public function_ `virtual void OnUnhovered()`
- L40 _protected member_ `bool bIsHovered = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IKeyExtension.h` (Public)


#### struct `UE::Sequencer::FCachedKeys`  
`struct FCachedKeys`  
_L21-39_
- L24 _public member_ `TArray<FKeyHandle> KeyHandles;` — Handles to each of the keys
- L26 _public member_ `TArray<FFrameTime> KeyTimes;` — Frame times for each of the keys in a data-dependent time-space
- L37 _public prototype_ `void GetKeysInRange(const TRange<FFrameTime>& Range, TArrayView<const FFrameTime>* OutKeyTimes, TArrayView<const FKeyHandle>* OutHandles) const;`
- L38 _public prototype_ `void GetKeysInRangeWithBounds(const TRange<FFrameTime>& Range, TArrayView<const FFrameTime>* OutKeyTimes, TArrayView<const FKeyHandle>* OutHandles, FCachedKey* OutLeadingKey, FCachedKey* OutTrailingKey) const;`

#### struct `UE::Sequencer::FCachedKeys::FCachedKey`  
`struct FCachedKey`  
_L28-35_
- L30 _public member_ `FFrameTime Time;`
- L31 _public member_ `FKeyHandle Handle = FKeyHandle::Invalid();`
- L33 _public prototype_ `bool IsValid() const;`
- L34 _public prototype_ `void Reset();`

#### class `UE::Sequencer::IKeyExtension`  
`class IKeyExtension`  
_L41-57_
- L50 _public prototype_ `virtual bool UpdateCachedKeys(TSharedPtr<FCachedKeys>& OutCachedKeys) const = 0;`
- L52 _public prototype_ `virtual bool GetFixedExtents(double& OutFixedMin, double& OutFixedMax) const = 0;`
- L54 _public prototype_ `virtual void DrawKeys(TArrayView<const FKeyHandle> InKeyHandles, TArrayView<FKeyDrawParams> OutKeyDrawParams) = 0;`
- L56 _public prototype_ `virtual TUniquePtr<FCurveModel> CreateCurveModel() = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ILayerBarExtension.h` (Public)


#### class `UE::Sequencer::ILayerBarExtension`  
`class ILayerBarExtension`  
_L16-26_
- L24 _public prototype_ `virtual TRange<FFrameNumber> GetLayerBarRange() const = 0;`
- L25 _public prototype_ `virtual void OffsetLayerBar(FFrameNumber Amount) = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ILockableExtension.h` (Public)


#### enum `UE::Sequencer::ELockableLockState`  
`enum class ELockableLockState`  
_L16-21_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Locked`
- L20 _public enumerator_ `PartiallyLocked`

#### class `UE::Sequencer::ILockableExtension`  
`class ILockableExtension`  
_L26-39_
- desc: An extension for models that can be locked
- L35 _public prototype_ `virtual ELockableLockState GetLockState() const = 0;` — Returns whether this item is locked
- L38 _public prototype_ `virtual void SetIsLocked(bool bIsLocked) = 0;` — Set whether this item is locked

#### enum `UE::Sequencer::ECachedLockState`  
`enum class ECachedLockState`  
_L41-52_
- L43 _public enumerator_ `None = 0`
- L45 _public enumerator_ `Lockable = 1 << 0`
- L46 _public enumerator_ `LockableChildren = 1 << 1`
- L47 _public enumerator_ `Locked = 1 << 2`
- L48 _public enumerator_ `PartiallyLockedChildren = 1 << 3`
- L49 _public enumerator_ `ImplicitlyLockedByParent = 1 << 4`
- L51 _public enumerator_ `InheritedFromChildren = LockableChildren | PartiallyLockedChildren`

#### class `UE::Sequencer::FLockStateCacheExtension`  
`class FLockStateCacheExtension : public TFlagStateCacheExtension<ECachedLockState>`  
_L55-66_
- inherits: `TFlagStateCacheExtension<ECachedLockState>`
- L64 _private prototype_ `ECachedLockState ComputeFlagsForModel(const FViewModelPtr& ViewModel) override;`
- L65 _private prototype_ `void PostComputeChildrenFlags(const FViewModelPtr& ViewModel, ECachedLockState& OutThisModelFlags, ECachedLockState& OutPropagateToParentFlags) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IMutableExtension.h` (Public)


#### class `UE::Sequencer::IMutableExtension`  
`class IMutableExtension`  
_L19-38_
- desc: An extension for outliner nodes that can be muted
- L28 _public prototype_ `virtual bool IsMuted() const = 0;` — Returns whether this item is muted
- L31 _public prototype_ `virtual void SetIsMuted(bool bIsMuted) = 0;` — Set this item's mute state
- L34 _public function_ `virtual bool IsInheritable() const` — Returns whether this mutable can be muted by a parent, and should report its mute state to a parent

#### enum `UE::Sequencer::ECachedMuteState`  
`enum class ECachedMuteState`  
_L40-52_
- L42 _public enumerator_ `None = 0`
- L44 _public enumerator_ `Mutable = 1 << 0`
- L45 _public enumerator_ `MutableChildren = 1 << 1`
- L46 _public enumerator_ `Muted = 1 << 2`
- L47 _public enumerator_ `PartiallyMutedChildren = 1 << 3`
- L48 _public enumerator_ `ImplicitlyMutedByParent = 1 << 4`
- L49 _public enumerator_ `Inheritable = 1 << 5`
- L51 _public enumerator_ `InheritedFromChildren = MutableChildren | PartiallyMutedChildren`

#### class `UE::Sequencer::FMuteStateCacheExtension`  
`class FMuteStateCacheExtension : public TFlagStateCacheExtension<ECachedMuteState>`  
_L56-67_
- inherits: `TFlagStateCacheExtension<ECachedMuteState>`
- L65 _private prototype_ `ECachedMuteState ComputeFlagsForModel(const FViewModelPtr& ViewModel) override;`
- L66 _private prototype_ `void PostComputeChildrenFlags(const FViewModelPtr& ViewModel, ECachedMuteState& OutThisModelFlags, ECachedMuteState& OutPropagateToParentFlags) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)
- L53 _prototype_ `ENUM_CLASS_FLAGS(ECachedMuteState) ECachedMuteState CombinePropagatedChildFlags(ECachedMuteState ParentFlags, ECachedMuteState CombinedChildFlags);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IObjectModelExtension.h` (Public)


#### class `UE::Sequencer::IObjectModelExtension`  
`class IObjectModelExtension`  
_L17-27_
- desc: An extension that is used for view models that represent UObject data
- L25 _public prototype_ `virtual void InitializeObject(TWeakObjectPtr<> InWeakObject) = 0;`
- L26 _public prototype_ `virtual UObject* GetObject() const = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IOutlinerExtension.h` (Public)


#### enum `UE::Sequencer::EOutlinerSelectionState`  
`enum class EOutlinerSelectionState`  
_L40-49_
- L42 _public enumerator_ `None = 0`
- L43 _public enumerator_ `SelectedDirectly = 1 << 0`
- L44 _public enumerator_ `HasSelectedKeys = 1 << 1`
- L45 _public enumerator_ `HasSelectedTrackAreaItems = 1 << 2`
- L47 _public enumerator_ `DescendentHasSelectedKeys = 1 << 3`
- L48 _public enumerator_ `DescendentHasSelectedTrackAreaItems = 1 << 4`

#### enum `UE::Sequencer::EOutlinerSizingFlags`  
`enum class EOutlinerSizingFlags`  
_L52-58_
- L54 _public enumerator_ `None = 0`
- L55 _public enumerator_ `DynamicSizing = 1 << 0`
- L56 _public enumerator_ `IncludeSeparator = 1 << 1`
- L57 _public enumerator_ `CustomHeight = 1 << 2`

#### struct `UE::Sequencer::FOutlinerSizing`  
`struct FOutlinerSizing`  
_L61-117_
- L63 _public prototype_ `FOutlinerSizing() = default;`
- L65 _public function_ `FOutlinerSizing(float InHeight) : Height(InHeight)`
- L69 _public function_ `FOutlinerSizing(float InHeight, float UniformPadding) : Height(InHeight) , PaddingTop(UniformPadding) , PaddingBottom(UniformPadding)`
- L88 _public function_ `float GetSeparatorHeight() const`
- L95 _public function_ `float GetTotalHeight() const`
- L100 _public function_ `void Accumulate(const FOutlinerSizing& Other)`
- L113 _public member_ `float Height = 0.f;`
- L114 _public member_ `float PaddingTop = 0.f;`
- L115 _public member_ `float PaddingBottom = 0.f;`
- L116 _public member_ `EOutlinerSizingFlags Flags = EOutlinerSizingFlags::IncludeSeparator;`

#### class `UE::Sequencer::ISequencerTreeViewRow`  
`class ISequencerTreeViewRow : public STableRow<TWeakViewModelPtr<IOutlinerExtension>>`  
_L120-124_
- inherits: `STableRow<TWeakViewModelPtr<IOutlinerExtension>>`
- desc: Facade class to allow SOutlinerViewRow to be passed around publicly
- L123 _public prototype_ `virtual bool IsColumnVisible(const FName& InColumnName) const = 0;`

#### struct `UE::Sequencer::FCreateOutlinerViewParams`  
`struct FCreateOutlinerViewParams`  
_L127-135_
- desc: Parameters for creating an outliner item widget.
- L129 _public function_ `FCreateOutlinerViewParams(const TSharedRef<ISequencerTreeViewRow>& InTreeViewRow, const TSharedPtr<FEditorViewModel>& InEditor) : TreeViewRow(InTreeViewRow), Editor(InEditor)`
- L133 _public member_ `const TSharedRef<ISequencerTreeViewRow> TreeViewRow;`
- L134 _public member_ `const TSharedPtr<FEditorViewModel> Editor;`

#### struct `UE::Sequencer::FCreateOutlinerContextMenuWidgetParams`  
`struct FCreateOutlinerContextMenuWidgetParams`  
_L138-145_
- desc: Parameters for building a context menu widget
- L140 _public function_ `FCreateOutlinerContextMenuWidgetParams(const TSharedPtr<FEditorViewModel> InEditor) : Editor(InEditor)`
- L144 _public member_ `const TSharedPtr<FEditorViewModel> Editor;`

#### class `UE::Sequencer::IOutlinerExtension`  
`class IOutlinerExtension`  
_L150-237_
- desc: Extension interface for models that can be displayed in the outliner view.
- L159 _public prototype_ `virtual FName GetIdentifier() const = 0;` — Return the identifier of the owning model
- L162 _public prototype_ `virtual FOutlinerSizing GetOutlinerSizing() const = 0;` — Return the desired size for the owning model
- L165 _public prototype_ `virtual bool IsExpanded() const = 0;` — Gets whether this outliner item is expanded
- L168 _public prototype_ `virtual void SetExpansion(bool bIsExpanded) = 0;` — Sets the expansion state of this outliner item
- L171 _public prototype_ `virtual bool IsFilteredOut() const = 0;` — Gets whether this outliner item has been filtered out
- L174 _public prototype_ `virtual void SetFilteredOut(bool bIsFilteredOut) = 0;` — Sets whether this outliner item is being filtered out
- L176 _public prototype_ `virtual bool ShouldAnchorToTop() const = 0;`
- L179 _public prototype_ `virtual EOutlinerSelectionState GetSelectionState() const = 0;` — Gets the outliner item's selection state
- L182 _public prototype_ `virtual void SetSelectionState(EOutlinerSelectionState InState) = 0;` — Sets the outliner item's selection state
- L185 _public prototype_ `virtual void ToggleSelectionState(EOutlinerSelectionState InState, bool bInValue);` — Toggles a bit in the outliner item's selection state
- L188 _public prototype_ `virtual TSharedRef<SWidget> CreateOutlinerView(const FCreateOutlinerViewParams& InParams);` — (deprecated) Create the outliner view for the label column
- L191 _public prototype_ `virtual TSharedPtr<SWidget> CreateOutlinerViewForColumn(const FCreateOutlinerViewParams& InParams, const FName& InColumnName);` — Create the visual outliner widget for the specified column
- L195 _public function_ `virtual bool SupportsOutlinerColumn(const FName& InColumnName) const` — Whether this outliner item supports the given column. Default is true for all columns. Override to suppress specific columns (e.g. mute/solo on transition sections).
- L198 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenuWidget(const FCreateOutlinerContextMenuWidgetParams& InParams) = 0;` — Build the context menu widget for this outliner item
- L201 _public prototype_ `virtual FText GetLabel() const;` — Gets the label for the outliner item
- L204 _public prototype_ `virtual FSlateFontInfo GetLabelFont() const;` — Gets the font for the outliner item
- L207 _public prototype_ `virtual FSlateColor GetLabelColor() const;` — Gets the color for the outliner item label
- L210 _public prototype_ `virtual FText GetLabelToolTipText() const;` — Gets the tooltip text for the outliner item
- L213 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const;` — Gets the icon for the outliner item
- L216 _public prototype_ `virtual FSlateColor GetIconTint() const;` — Gets the icon tint color for the outliner item
- L219 _public prototype_ `virtual const FSlateBrush* GetIconOverlayBrush() const;` — Gets the overlay icon for the outliner item
- L222 _public prototype_ `virtual FText GetIconToolTipText() const;` — Gets the tooltip text for the outliner item icon
- L225 _public prototype_ `virtual bool HasBackground() const;` — Gets whether the outliner item has a background
- L228 _public prototype_ `static FString GetPathName(const FViewModel& Item);` — Utility method to get the full path name of the given model
- L230 _public prototype_ `static FString GetPathName(const TSharedPtr<FViewModel> Item);` — Utility method to get the full path name of the given model
- L232 _public prototype_ `static FString GetPathName(const TSharedPtr<const FViewModel> Item);` — Utility method to get the full path name of the given model
- L234 _public prototype_ `static FString GetPathName(const TWeakPtr<const FViewModel> Item);` — Utility method to get the full path name of the given model
- L236 _public prototype_ `static void GetPathName(const FViewModel& Item, FStringBuilderBase& OutString);` — Utility method to get the full path name of the given model

#### class `UE::Sequencer::FOutlinerExtensionShim`  
`class FOutlinerExtensionShim : public IOutlinerExtension`  
_L242-259_
- inherits: `IOutlinerExtension`
- desc: Default implementation for some of the outliner extension API.
- L246 _public function_ `virtual bool IsExpanded() const override`
- L247 _public function_ `virtual void SetExpansion(bool bInIsExpanded) override`
- L248 _public function_ `virtual bool IsFilteredOut() const override`
- L249 _public function_ `virtual void SetFilteredOut(bool bInIsFilteredOut) override`
- L250 _public function_ `virtual EOutlinerSelectionState GetSelectionState() const override`
- L251 _public function_ `virtual void SetSelectionState(EOutlinerSelectionState InState) override`
- L252 _public function_ `virtual bool ShouldAnchorToTop() const override`
- L256 _protected member_ `bool bIsExpanded = false;`
- L257 _protected member_ `bool bIsFilteredOut = false;`
- L258 _protected member_ `EOutlinerSelectionState SelectionState = EOutlinerSelectionState::None;`

#### class `UE::Sequencer::IOutlinerDropTargetOutlinerExtension`  
`class IOutlinerDropTargetOutlinerExtension`  
_L264-274_
- desc: Extension for outliner items that accept drag and drop.
- L272 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FViewModelPtr& TargetModel, const FDragDropEvent& DragDropEvent, EItemDropZone InItemDropZone) = 0;`
- L273 _public prototype_ `virtual void PerformDrop(const FViewModelPtr& TargetModel, const FDragDropEvent& DragDropEvent, EItemDropZone InItemDropZone) = 0;`

#### class `UE::Sequencer::ICompoundOutlinerExtension`  
`class ICompoundOutlinerExtension`  
_L279-288_
- desc: Extension for outliner models that want to compute their and their children's sizing.
- L287 _public prototype_ `virtual FOutlinerSizing RecomputeSizing() = 0;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API SEQUENCERCORE_API`
- L30 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Sequencer` (scope `UE`)
- L50 _prototype_ `ENUM_CLASS_FLAGS(EOutlinerSelectionState);` (scope `UE::Sequencer`)
- L59 _prototype_ `ENUM_CLASS_FLAGS(EOutlinerSizingFlags);` (scope `UE::Sequencer`)
- L75 _function_ `friend bool operator==(const FOutlinerSizing& A, const FOutlinerSizing& B)` (scope `UE::Sequencer`)
- L83 _function_ `friend bool operator!=(const FOutlinerSizing& A, const FOutlinerSizing& B)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IPinnableExtension.h` (Public)


#### class `UE::Sequencer::IPinnableExtension`  
`class IPinnableExtension`  
_L21-35_
- desc: An extension for outliner nodes that can be pinned at the top
- L30 _public prototype_ `virtual bool IsPinned() const = 0;` — Returns whether this item is pinned, or is in a pinned branch
- L32 _public prototype_ `virtual void SetPinned(bool bInIsPinned) = 0;` — Sets whether this item is pinned
- L34 _public prototype_ `virtual void ReportPinnedParent(bool bInIsInPinnedBranch) = 0;` — Lets parent items report to their children that they are in a pinned branch

#### class `UE::Sequencer::FPinnableExtensionShim`  
`class FPinnableExtensionShim : public IPinnableExtension`  
_L41-61_
- inherits: `IPinnableExtension`
- desc: Default implementation for IPinnableExtension, with helper method to cache pinned states for children of a pinned branch
- L45 _public prototype_ `virtual bool IsPinned() const override;`
- L46 _public prototype_ `virtual void SetPinned(bool bInIsPinned) override;`
- L47 _public prototype_ `virtual void ReportPinnedParent(bool bInIsInPinnedBranch) override;`
- L55 _public prototype_ `static void UpdateCachedPinnedState(TSharedPtr<FViewModel> RootModel);` — Looks for any direct child of RootModel that is pinnable, and reports all their descendants that they are in a pinned branch, to make that lookup faster
- L59 _private member_ `bool bIsPinned = false;`
- L60 _private member_ `bool bIsInPinnedBranch = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IRecyclableExtension.h` (Public)


#### class `UE::Sequencer::IRecyclableExtension`  
`class IRecyclableExtension`  
_L16-27_
- L24 _public prototype_ `virtual ~IRecyclableExtension()= default;`
- L26 _public prototype_ `virtual void OnRecycle() = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IRenameableExtension.h` (Public)


#### class `UE::Sequencer::IRenameableExtension`  
`class IRenameableExtension`  
_L17-39_
- L25 _public function_ `FSimpleMulticastDelegate& OnRenameRequested()`
- L27 _public prototype_ `virtual bool CanRename() const = 0;`
- L28 _public prototype_ `virtual void Rename(const FText& NewName) = 0;`
- L30 _public prototype_ `bool IsRenameValid(const FText& NewName, FText& OutErrorMessage) const;`
- L34 _private function_ `virtual bool IsRenameValidImpl(const FText& NewName, FText& OutErrorMessage) const`
- L38 _private member_ `FSimpleMulticastDelegate RenameRequestedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IResizableExtension.h` (Public)


#### class `UE::Sequencer::IResizableExtension`  
`class IResizableExtension`  
_L15-25_
- L23 _public prototype_ `virtual bool IsResizable() const = 0;`
- L24 _public prototype_ `virtual void Resize(float NewSize) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ISelectableExtension.h` (Public)


#### enum `UE::Sequencer::ESelectionIntent`  
`enum class ESelectionIntent`  
_L26-38_
- desc: Enumeration specifying the type of interaction that instigated the selection This allows models to opt-into selection in some contexts while refusing selection in others
- L29 _public enumerator_ `Never = 0x0` — Symbolic value signifying that a model is never selectable
- L32 _public enumerator_ `PersistentSelection = 0x1` — Used when the selection will be persistent and visible on the UI
- L34 _public enumerator_ `ContextMenu = 0x2` — Used exclisively for a transient context-menu selection
- L37 _public enumerator_ `Any = PersistentSelection | ContextMenu` — Combination that defines any intent is supported

#### class `UE::Sequencer::ISelectableExtension`  
`class ISelectableExtension`  
_L41-50_
- L49 _public function_ `virtual ESelectionIntent IsSelectable() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L39 _prototype_ `ENUM_CLASS_FLAGS(ESelectionIntent);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ISoloableExtension.h` (Public)


#### class `UE::Sequencer::ISoloableExtension`  
`class ISoloableExtension`  
_L19-32_
- desc: An extension for outliner nodes that can be made 'solo'
- L28 _public prototype_ `virtual bool IsSolo() const = 0;` — Returns whether this item is solo
- L31 _public prototype_ `virtual void SetIsSoloed(bool bIsSoloed) = 0;` — Enable or disable solo for this object

#### enum `UE::Sequencer::ECachedSoloState`  
`enum class ECachedSoloState`  
_L34-45_
- L36 _public enumerator_ `None = 0`
- L38 _public enumerator_ `Soloable = 1 << 0`
- L39 _public enumerator_ `SoloableChildren = 1 << 1`
- L40 _public enumerator_ `Soloed = 1 << 2`
- L41 _public enumerator_ `PartiallySoloedChildren = 1 << 3`
- L42 _public enumerator_ `ImplicitlySoloedByParent = 1 << 4`
- L44 _public enumerator_ `InheritedFromChildren = SoloableChildren | PartiallySoloedChildren`

#### class `UE::Sequencer::FSoloStateCacheExtension`  
`class FSoloStateCacheExtension : public TFlagStateCacheExtension<ECachedSoloState>`  
_L48-63_
- inherits: `TFlagStateCacheExtension<ECachedSoloState>`
- L55 _public typedef_ `using Implements = TImplements<IDynamicExtension, IHierarchicalCache>;`
- L57 _public prototype_ `virtual ~FSoloStateCacheExtension() = default;`
- L61 _private prototype_ `ECachedSoloState ComputeFlagsForModel(const FViewModelPtr& ViewModel) override;`
- L62 _private prototype_ `void PostComputeChildrenFlags(const FViewModelPtr& ViewModel, ECachedSoloState& OutThisModelFlags, ECachedSoloState& OutPropagateToParentFlags) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ISortableExtension.h` (Public)


#### struct `UE::Sequencer::FSortingKey`  
`struct FSortingKey`  
_L28-63_
- desc: Structure for sorting models of various types together. Lower values have more precedence than higher values, i.e. items associated with lower values are ordered before items with higher values.
- L31 _public member_ `int8 Priority = 0;` — Priority order
- L33 _public member_ `FText DisplayName;` — Identifier
- L35 _public member_ `int32 CustomOrder = -1;` — Custom order, only relevant if >= 0
- L37 _public function_ `FSortingKey()`
- L40 _public function_ `FSortingKey& PrioritizeBy(int8 InOffset)`
- L46 _public function_ `FSortingKey& DeprioritizeBy(int8 InOffset)`
- L53 _public prototype_ `static bool ComparePriorityFirst(const FSortingKey& A, const FSortingKey& B);` — Compare priorities, identifiers, and custom orders
- L55 _public prototype_ `static bool CompareCustomOrderFirst(const FSortingKey& A, const FSortingKey& B);` — Compare custom orders (if both set), priorities, and identifiers

#### enum `UE::Sequencer::ESortingMode`  
`enum class ESortingMode`  
_L65-70_
- L67 _public enumerator_ `PriorityFirst`
- L68 _public enumerator_ `CustomOrderFirst`
- L69 _public enumerator_ `Default = CustomOrderFirst`

#### class `UE::Sequencer::ISortableExtension`  
`class ISortableExtension`  
_L75-94_
- desc: Extension for models that can sort their children, and be sorted themselves among their siblings
- L84 _public prototype_ `virtual void SortChildren() = 0;` — Called when the model should sort its immediate children
- L86 _public prototype_ `virtual FSortingKey GetSortingKey() const = 0;` — Called by the part to sort this model among its siblings
- L88 _public prototype_ `virtual void SetCustomOrder(int32 InCustomOrder) = 0;` — Set a custom sort index for this view model
- L91 _public prototype_ `static void SortChildren(TSharedPtr<FViewModel> ParentModel, ESortingMode SortingMode);` — Utility function for sorting children based on their sorting key
- L93 _public prototype_ `static void SortChildren(FViewModelChildren& Children, ESortingMode SortingMode);` — Utility function for sorting children based on their sorting key

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERCORE_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L57 _function_ `friend bool operator==(const FSortingKey& A, const FSortingKey& B)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IStretchableExtension.h` (Public)


#### enum `UE::Sequencer::EStretchConstraint`  
`enum class EStretchConstraint`  
_L25-28_
- L27 _public enumerator_ `AnchorToStart`
- L27 _public enumerator_ `AnchorToStart`

#### enum `UE::Sequencer::EStretchResult`  
`enum class EStretchResult`  
_L30-33_
- L32 _public enumerator_ `Success`
- L32 _public enumerator_ `Success`

#### struct `UE::Sequencer::FStretchParameters`  
`struct FStretchParameters`  
_L35-44_
- L37 _public member_ `double Anchor = 0.0;`
- L38 _public member_ `double Handle = 0.0;`
- L40 _public function_ `bool IsValid() const`

#### struct `UE::Sequencer::FStretchScreenParameters`  
`struct FStretchScreenParameters`  
_L46-55_
- L48 _public member_ `FFrameTime DragStartPosition;`
- L49 _public member_ `FFrameTime CurrentDragPosition;`
- L51 _public member_ `FVector2D LocalMousePos;`
- L53 _public member_ `const FPointerEvent* MouseEvent = nullptr;`
- L54 _public member_ `const FVirtualTrackArea* VirtualTrackArea = nullptr;`

#### class `UE::Sequencer::IStretchableExtension`  
`class IStretchableExtension`  
_L57-70_
- L65 _public function_ `virtual void OnInitiateStretch(IStretchOperation& StretchOperation, EStretchConstraint Constraint, FStretchParameters* InOutGlobalParameters)`
- L67 _public function_ `virtual EStretchResult OnBeginStretch(const IStretchOperation& StretchOperation, const FStretchScreenParameters& ScreenParameters, FStretchParameters* InOutParameters)`
- L68 _public function_ `virtual void OnStretch(const IStretchOperation& StretchOperation, const FStretchScreenParameters& ScreenParameters, FStretchParameters* InOutParameters)`
- L69 _public function_ `virtual void OnEndStretch(const IStretchOperation& StretchOperation, const FStretchScreenParameters& ScreenParametersm, FStretchParameters* InOutParameters)`

#### class `UE::Sequencer::IStretchOperation`  
`class IStretchOperation`  
_L72-79_
- L75 _public prototype_ `virtual ~IStretchOperation() = default;`
- L77 _public prototype_ `virtual void DoNotSnapTo(TSharedPtr<FViewModel> Model) = 0;`
- L78 _public prototype_ `virtual bool InitiateStretch(TSharedPtr<FViewModel> Controller, TSharedPtr<IStretchableExtension> Target, int32 Priority, const FStretchParameters& InParams) = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERCORE_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ITopTimeSliderOverlayExtension.h` (Public)


#### class `UE::Sequencer::ITopTimeSliderOverlayExtension`  
`class ITopTimeSliderOverlayExtension`  
_L18-31_
- desc: This extension allows you to paint custom geometry in the time slider area.
- L30 _public prototype_ `virtual ~ITopTimeSliderOverlayExtension() = default;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCERCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ITrackAreaExtension.h` (Public)


#### enum `UE::Sequencer::ETrackAreaLaneType`  
`enum class ETrackAreaLaneType : uint8`  
_L18-23_
- L20 _public enumerator_ `Inline`
- L21 _public enumerator_ `Nested`
- L22 _public enumerator_ `None`

#### struct `UE::Sequencer::FTrackAreaParameters`  
`struct FTrackAreaParameters`  
_L25-33_
- L27 _public member_ `ETrackAreaLaneType LaneType = ETrackAreaLaneType::None;`
- L32 _public member_ `} TrackLanePadding;`

#### struct `UE::Sequencer::FTrackAreaParameters::(anonymous)`  
``  
_L29-32_

#### class `UE::Sequencer::ITrackAreaExtension`  
`class ITrackAreaExtension`  
_L38-55_
- desc: This extension can be added to any model in order to provide a list of models that are relevent to the track area
- L46 _public prototype_ `virtual FTrackAreaParameters GetTrackAreaParameters() const = 0;`
- L47 _public prototype_ `virtual FViewModelVariantIterator GetTrackAreaModelList() const = 0;`
- L48 _public function_ `virtual FViewModelVariantIterator GetTopLevelChildTrackAreaModels() const`
- L51 _public function_ `template<typename T> TTypedIterator<T, FViewModelVariantIterator> GetTrackAreaModelListAs() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)
- L30 _member_ `float Top = 0.f;` (scope `UE::Sequencer::FTrackAreaParameters::__anon4bf50c7b0108`)
- L31 _member_ `float Bottom = 0.f;` (scope `UE::Sequencer::FTrackAreaParameters::__anon4bf50c7b0108`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ITrackAreaOverlayExtension.h` (Public)


#### class `UE::Sequencer::ITrackAreaOverlayExtension`  
`class ITrackAreaOverlayExtension`  
_L18-31_
- desc: This extension allows you to paint custom geometry in the track area.
- L30 _public prototype_ `virtual ~ITrackAreaOverlayExtension() = default;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCERCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ITrackAreaViewSpaceProviderExtension.h` (Public)


#### class `UE::Sequencer::ITrackAreaViewSpaceProviderExtension`  
`class ITrackAreaViewSpaceProviderExtension`  
_L19-28_
- desc: An extension that supplies view spaces to a track area. Must exist as an immediate child of the root model to be effective.
- L27 _public prototype_ `virtual void UpdateViewSpaces(FTrackAreaViewModel& TrackAreaViewModel) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ITrackLaneExtension.h` (Public)


#### struct `UE::Sequencer::FTrackLaneVerticalArrangement`  
`struct FTrackLaneVerticalArrangement`  
_L34-38_
- L36 _public member_ `float Offset = 0;`
- L37 _public member_ `float Height = 0;`

#### struct `UE::Sequencer::FTrackLaneVerticalAlignment`  
`struct FTrackLaneVerticalAlignment`  
_L40-53_
- L47 _public member_ `float VSizeParam = 1.f;`
- L48 _public member_ `float VPadding = 0.f;`
- L49 _public member_ `EVerticalAlignment VAlign = VAlign_Center;`
- L50 _public member_ `ESizeMode Mode = ESizeMode::Proportional;`
- L52 _public prototype_ `FTrackLaneVerticalArrangement ArrangeWithin(float LayoutHeight) const;`

#### enum `UE::Sequencer::FTrackLaneVerticalAlignment::ESizeMode`  
`enum class ESizeMode : uint8`  
_L42-45_
- L44 _public enumerator_ `Proportional`
- L44 _public enumerator_ `Proportional`

#### struct `UE::Sequencer::FTrackLaneVirtualAlignment`  
`struct FTrackLaneVirtualAlignment`  
_L55-78_
- L57 _public member_ `TRange<FFrameNumber> Range;`
- L58 _public member_ `FTrackLaneVerticalAlignment VerticalAlignment;`
- L59 _public member_ `FGuid ViewSpaceID;`
- L61 _public function_ `bool IsVisible() const`
- L66 _public function_ `static FTrackLaneVirtualAlignment Fixed(const TRange<FFrameNumber>& InRange, float InFixedHeight, EVerticalAlignment InVAlign = VAlign_Center, const FGuid& InViewSpaceID = FGuid())`
- L70 _public function_ `static FTrackLaneVirtualAlignment Proportional(const TRange<FFrameNumber>& InRange, float InStretchFactor, EVerticalAlignment InVAlign = VAlign_Center, const FGuid& InViewSpaceID = FGuid())`
- L75 _public prototype_ `TOptional<FFrameNumber> GetFiniteLength() const;`
- L77 _public prototype_ `FTrackLaneScreenAlignment ToScreen(const FTimeToPixel& TimeToPixel, const FGeometry& ParentGeometry) const;`

#### struct `UE::Sequencer::FTrackLaneScreenAlignment`  
`struct FTrackLaneScreenAlignment`  
_L80-104_
- L82 _public function_ `FTrackLaneScreenAlignment() : LeftPosPx(0.f) , WidthPx(0.f)`
- L88 _public function_ `FTrackLaneScreenAlignment(float InLeftPosPx, float InWidthPx, FTrackLaneVerticalAlignment InVerticalAlignment) : LeftPosPx(InLeftPosPx), WidthPx(InWidthPx), VerticalAlignment(InVerticalAlignment)`
- L93 _public member_ `TSharedPtr<INonLinearTimeTransform> NonLinearTransform;`
- L94 _public member_ `float LeftPosPx;`
- L95 _public member_ `float WidthPx;`
- L96 _public member_ `FTrackLaneVerticalAlignment VerticalAlignment;`
- L98 _public function_ `bool IsVisible() const`
- L103 _public prototype_ `FArrangedWidget ArrangeWidget(TSharedRef<SWidget> InWidget, const FGeometry& ParentGeometry) const;`

#### struct `UE::Sequencer::FArrangedVirtualEntity`  
`struct FArrangedVirtualEntity`  
_L106-110_
- L108 _public member_ `TRange<FFrameNumber> Range;`
- L109 _public member_ `float VirtualTop, VirtualBottom;`
- L109 _public member_ `float VirtualTop, VirtualBottom;`

#### class `UE::Sequencer::ITrackLaneWidgetSpace`  
`class ITrackLaneWidgetSpace`  
_L113-117_
- desc: Interface used for laying out track lane widgets in screen space
- L116 _public prototype_ `virtual FTimeToPixel GetScreenSpace(const FGuid& ViewSpaceID = FGuid()) const = 0;`

#### class `UE::Sequencer::ITrackLaneWidget`  
`class ITrackLaneWidget`  
_L120-164_
- desc: Base interface for track-area lanes
- L127 _public prototype_ `virtual TSharedRef<const SWidget> AsWidget() const = 0;` — Retrieve this interface as a widget
- L129 _public function_ `TSharedRef<SWidget> AsWidget()`
- L139 _public function_ `virtual FTrackLaneScreenAlignment GetAlignment(const FTimeToPixel& TimeToPixel, const FGeometry& InParentGeometry) const` — `UE_DEPRECATED(5.6, "Please use the ITrackLaneWidgetSpace overload")` — Arrange this widget within its parent slot
- L143 _public prototype_ `virtual FTrackLaneScreenAlignment GetAlignment(const ITrackLaneWidgetSpace& ScreenSpace, const FGeometry& InParentGeometry) const;`
- L148 _public function_ `virtual int32 GetOverlapPriority() const` — Gets this widget's overlap priority
- L153 _public function_ `virtual void ReportParentGeometry(const FGeometry& InDesktopSpaceParentGeometry)` — Receive parent geometry for this lane in Desktop space
- L158 _public function_ `virtual bool AcceptsChildren() const` — Whether this track lane accepts child widgets
- L163 _public function_ `virtual void AddChildView(TSharedPtr<ITrackLaneWidget> ChildWidget, TWeakPtr<STrackLane> InWeakOwningLane)` — Add a new child to this lane

#### struct `UE::Sequencer::FCreateTrackLaneViewParams`  
`struct FCreateTrackLaneViewParams`  
_L167-180_
- desc: Parameters for creating a track lane widget
- L169 _public function_ `FCreateTrackLaneViewParams(const TSharedPtr<FEditorViewModel> InEditor) : Editor(InEditor)`
- L173 _public member_ `const TSharedPtr<FEditorViewModel> Editor;`
- L175 _public member_ `TSharedPtr<FViewModel> ParentModel;`
- L177 _public member_ `TSharedPtr<STrackLane> OwningTrackLane;`
- L179 _public member_ `TSharedPtr<FTimeToPixel> TimeToPixel;`

#### class `UE::Sequencer::ITrackLaneExtension`  
`class ITrackLaneExtension`  
_L183-193_
- desc: Extension for view-models that can create track lanes in the track area
- L191 _public prototype_ `virtual TSharedPtr<ITrackLaneWidget> CreateTrackLaneView(const FCreateTrackLaneViewParams& InParams) = 0;`
- L192 _public prototype_ `virtual FTrackLaneVirtualAlignment ArrangeVirtualTrackLaneView() const = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/IViewSpaceClientExtension.h` (Public)


#### class `UE::Sequencer::IViewSpaceClientExtension`  
`class IViewSpaceClientExtension`  
_L20-30_
- desc: An extension that is used for view models that represent UObject data
- L28 _public prototype_ `virtual FGuid GetViewSpaceID() const = 0;`
- L29 _public prototype_ `virtual void SetViewSpaceID(const FGuid&) = 0;`

#### class `UE::Sequencer::FViewSpaceClientExtensionShim`  
`class FViewSpaceClientExtensionShim : public IDynamicExtension , public IViewSpaceClientExtension`  
_L36-64_
- inherits: `IDynamicExtension,IViewSpaceClientExtension`
- desc: An extension that is used for view models that represent UObject data
- L44 _public typedef_ `using Implements = TImplements<IDynamicExtension, IViewSpaceClientExtension>;`
- L46 _public function_ `FViewSpaceClientExtensionShim(const FGuid& InViewSpaceID) : ViewSpaceID(InViewSpaceID)`
- L51 _public function_ `virtual FGuid GetViewSpaceID() const override`
- L56 _public function_ `virtual void SetViewSpaceID(const FGuid& InViewSpaceID) override`
- L63 _protected member_ `FGuid ViewSpaceID;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/LinkedOutlinerExtension.h` (Public)


#### class `UE::Sequencer::FLinkedOutlinerExtension`  
`class FLinkedOutlinerExtension`  
_L24-39_
- desc: Extension for a model that is linked somehow to an outliner model. This is the case for example in Sequencer where the channels of the sections in the track area are linked to the channel group items in the outliner.
- L30 _public prototype_ `FLinkedOutlinerExtension();`
- L32 _public prototype_ `TViewModelPtr<IOutlinerExtension> GetLinkedOutlinerItem() const;`
- L34 _public prototype_ `void SetLinkedOutlinerItem(const TViewModelPtr<IOutlinerExtension>& InOutlinerItem);`
- L38 _private member_ `TWeakViewModelPtr<IOutlinerExtension> WeakModel;`

#### class `UE::Sequencer::FLinkedOutlinerComputedSizingShim`  
`class FLinkedOutlinerComputedSizingShim`  
_L46-56_
- desc: Simple mixin class for having computed sizing information on a linked outliner item. This is useful for instance when the outliner item is going to compute sizing info for all of its linked items.
- L50 _public function_ `FOutlinerSizing GetComputedSizing() const`
- L51 _public function_ `void SetComputedSizing(const FOutlinerSizing& InSizing)`
- L55 _protected member_ `FOutlinerSizing ComputedSizing;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERCORE_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Extensions/ViewModelExtensionCollection.h` (Public)


#### struct `UE::Sequencer::FViewModelExtensionCollection`  
`struct FViewModelExtensionCollection : FNoncopyable`  
_L30-83_
- inherits: `FNoncopyable`
- desc: Utility class for maintaining a list of view-models that implement a given extension in a given hierarchy. The list is kept up to date when the hierarchy changes.
- L34 _private prototype_ `FViewModelExtensionCollection(FViewModelTypeID InExtensionType);`
- L35 _private prototype_ `explicit FViewModelExtensionCollection(FViewModelTypeID InExtensionType, TWeakPtr<FViewModel> InWeakModel, int32 InDesiredRecursionDepth = -1);`
- L37 _private prototype_ `virtual ~FViewModelExtensionCollection();`
- L41 _protected function_ `virtual void OnExtensionsDirtied()`
- L43 _protected prototype_ `void Initialize();`
- L44 _protected prototype_ `void Reinitialize(TWeakPtr<FViewModel> InWeakModel, int32 InDesiredRecursionDepth = -1);`
- L45 _protected prototype_ `void Destroy();`
- L47 _protected function_ `TSharedPtr<FViewModel> GetObservedModel() const`
- L54 _private prototype_ `void Update() const;`
- L56 _private prototype_ `void OnHierarchyUpdated();`
- L58 _private prototype_ `void ConditionalUpdate() const;`
- L60 _private prototype_ `void DestroyImpl();`
- L63 _private function_ `template<typename T> TArrayView<T* const> GetExtensions() const`
- L77 _private member_ `mutable TArray<void*> ExtensionContainer;`
- L78 _private member_ `TWeakPtr<FViewModel> WeakModel;`
- L79 _private member_ `FDelegateHandle OnHierarchyUpdatedHandle;`
- L80 _private member_ `FViewModelTypeID ExtensionType;`
- L81 _private member_ `int32 DesiredRecursionDepth;`
- L82 _private member_ `mutable bool bNeedsUpdate;`

#### struct `UE::Sequencer::TViewModelExtensionCollection`  
`template<typename T> struct TViewModelExtensionCollection : FViewModelExtensionCollection`  
_L89-119_
- inherits: `FViewModelExtensionCollection`
- desc: Strongly typed version of FViewModelExtensionCollection
- L91 _public function_ `TViewModelExtensionCollection() : FViewModelExtensionCollection(T::ID)`
- L95 _public function_ `explicit TViewModelExtensionCollection(TWeakPtr<FViewModel> InWeakModel) : FViewModelExtensionCollection(T::ID, InWeakModel)`
- L99 _public function_ `explicit TViewModelExtensionCollection(TWeakPtr<FViewModel> InWeakModel, int32 InDesiredRecursionDepth) : FViewModelExtensionCollection(T::ID, InWeakModel, InDesiredRecursionDepth)`
- L103 _public function_ `TArrayView<T* const> GetExtensions() const`
- L109 _public function_ `template<typename Predicate> void FilterExtensions(Predicate&& InPredicate)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERCORE_API`
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ICastable.h` (Public)


#### class `UE::Sequencer::ICastable`  
`class ICastable`  
_L23-128_
- L28 _public function_ `template<typename RetType, typename InterfaceType, typename ...ArgTypes, typename ...ParamTypes> RetType CastedCall(RetType(InterfaceType::*MemberFunc)(ArgTypes...), ParamTypes&&... InArgs)`
- L34 _public function_ `template<typename RetType, typename InterfaceType, typename ...ArgTypes, typename ...ParamTypes> RetType CastedCall(RetType(InterfaceType::*MemberFunc)(ArgTypes...), ParamTypes&&... InArgs) const`
- L40 _public function_ `template<typename T> static T* CastWeakPtr(const TWeakPtr<ICastable>& InWeakPtr)`
- L50 _public function_ `template<typename T> static TSharedPtr<T> CastWeakPtrShared(const TWeakPtr<ICastable>& InWeakPtr)`
- L59 _public function_ `bool IsA(FViewModelTypeID InType) const`
- L65 _public function_ `template<typename T> bool IsA() const`
- L70 _public prototype_ `void* CastRaw(FViewModelTypeID InType);`
- L71 _public prototype_ `const void* CastRaw(FViewModelTypeID InType) const;`
- L74 _public function_ `template<typename T> T* CastThis()`
- L80 _public function_ `template<typename T> const T* CastThis() const`
- L86 _public function_ `template<typename T> T* CastThisChecked()`
- L94 _public function_ `template<typename T> const T* CastThisChecked() const`
- L101 _public function_ `const FCastableTypeTable& GetTypeTable() const`
- L124 _private member_ `const FCastableTypeTable* const TypeTable = nullptr;`
- L127 _protected member_ `FDynamicExtensionContainer* DynamicTypes = nullptr;`

#### struct `UE::Sequencer::ICastable::FAutoRegisterTypeTable`  
`struct FAutoRegisterTypeTable`  
_L111-119_
- desc: Struct that assigns an ICastable instance's TypeTable. See UE_SEQUENCER_DECLARE_CASTABLE for usage.
- L114 _public function_ `template<typename T> FAutoRegisterTypeTable(T* InThis)`

#### struct `UE::Sequencer::TImplements`  
`template<typename ...T> struct TImplements`  
_L131-133_

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SEQUENCERCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)
- L140 _macro_ `#define UE_SEQUENCER_NO_UNIQUE_ADDRESS`
- L142 _macro_ `#define UE_SEQUENCER_NO_UNIQUE_ADDRESS UE_NO_UNIQUE_ADDRESS`
- L145 _macro_ `#define UE_SEQUENCER_DECLARE_CASTABLE(ThisType, ...) \`
- L148 _macro_ `#define UE_SEQUENCER_DECLARE_CASTABLE_API(MODULE_API, ThisType, ...) \`
- L153 _macro_ `#define UE_SEQUENCER_DEFINE_CASTABLE(ThisType) \`

### `Source/Editor/SequencerCore/Public/MVVM/Selection/SequencerCoreSelection.h` (Public)


#### class `UE::Sequencer::FSequencerCoreSelection`  
`class FSequencerCoreSelection : public TSharedFromThis<FSequencerCoreSelection>`  
_L26-126_
- inherits: `TSharedFromThis<FSequencerCoreSelection>`
- desc: Core selection class that manages multiple different selection sets through FSelectionBase. Implementers of this class should create a derived type that defines each of its selection sets by calling AddSelectionSet in its constructor. This enables a central implementation for event suppression and broadcast.
- L34 _public member_ `FSimpleMulticastDelegate OnChanged;` — Event that is broadcast when any selection state inside this class has changed & after all scoped suppressors have been destroyed
- L39 _public function_ `uint32 GetSerialNumber() const` — Retrieve the serial number that identifies this selection's state.
- L47 _public function_ `bool IsTriggeringSelectionChangedEvents() const` — Check whether this selection is currently broadcasting its selection changed events
- L55 _public prototype_ `[[nodiscard]] FSelectionEventSuppressor SuppressEvents();` — Retrieve a scoped object that will suppress selection events for the duration of its lifetime on the stack
- L62 _public prototype_ `[[nodiscard]] TUniquePtr<FSelectionEventSuppressor> SuppressEventsLongRunning();` — Retrieve a scoped object that will suppress selection events for the duration of its lifetime. This function should only be used for longer running suppression such as those as part of a mouse-down operation. The suppressor can be destroyed by resetting the unique pointer
- L67 _public prototype_ `void Empty();` — Empty all the selection states within this selection class
- L71 _public function_ `virtual TSharedPtr< FOutlinerSelection> GetOutlinerSelection()`
- L72 _public function_ `virtual TSharedPtr<const FOutlinerSelection> GetOutlinerSelection() const`
- L79 _protected function_ `FSequencerCoreSelection() : ScopedSuppressionCount(0) , SerialNumber(0) , bTriggeringSelectionEvents(false)` — Protected constructor - to be implemented by a derived class
- L85 _protected prototype_ `virtual ~FSequencerCoreSelection() = default;`
- L91 _protected function_ `void AddSelectionSet(FSelectionBase* InSelection)` — Add a selection set to this class - selection set should be a member of the derived implementation of this class so as to ensure its lifetime matches this owner
- L103 _private function_ `virtual void PreBroadcastChangeEvent()` — Function that is called after increasing the serial number, but before triggering any OnChanged events This allows derived classes to update any cached data they might want to generate from the selection before publicizing the change
- L109 _private function_ `virtual void PreSelectionSetChangeEvent(FSelectionBase* InSelectionSet)` — Function that is called the first time within a FSelectionEventSuppressor scope that a selection set is changed. Care should be taken to not cause infinite loops or non-deterministc modification or other selection sets when overriding this function .
- L111 _private prototype_ `void BroadcastSelectionChanged();`
- L119 _private member_ `TArray<FSelectionBase*> SelectionSets;` — Array of registered selection sets (contained in a derived type), registerd thorugh AddSelectionSet
- L121 _private member_ `int32 ScopedSuppressionCount;` — The number of outstanding scoped event suppression objects.
- L123 _private member_ `uint32 SerialNumber;` — A monotonically increasing integer that changes whenever anything within this selection is changed
- L125 _private member_ `bool bTriggeringSelectionEvents;` — Boolean to guard against re-entrancy when triggering selection events

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Selection/SequencerCoreSelectionIterators.h` (Public)


#### struct `UE::Sequencer::TSelectionSetIteratorImpl`  
`template<typename T> struct TSelectionSetIteratorImpl`  
_L28-52_
- desc: Minimal traits class for iterator implementations. Can be specialized to customize selection set iteration behavior.
- L33 _public function_ `const T& operator*() const` — Access the current value of the iterator. By default this just returns the value directly.
- L40 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<T>::TRangedForConstIterator InIteratorBegin, typename TSet<T>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L47 _protected function_ `constexpr void SkipInvalid()` — Skip invalid iterations - by default all items are valid
- L50 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorBegin;`
- L51 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorEnd;`
- L175 _public function_ `TSharedPtr<T> operator*() const`
- L182 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L186 _protected function_ `void SkipInvalid()`
- L194 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L195 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorEnd;`
- L205 _public function_ `TViewModelPtr<T> operator*() const`
- L212 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L224 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L225 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorEnd;`

#### struct `UE::Sequencer::TSelectionSetIteratorState`  
`template<typename T, typename ImplType = TSelectionSetIteratorImpl<T>> struct TSelectionSetIteratorState : ImplType`  
_L58-76_
- inherits: `ImplType`
- desc: Selection iterator class that iterates a given selection set using specialized behavior for weak pointers
- L60 _public function_ `explicit TSelectionSetIteratorState(typename TSet<T>::TRangedForConstIterator InIteratorBegin, typename TSet<T>::TRangedForConstIterator InIteratorEnd) : ImplType(InIteratorBegin, InIteratorEnd)`
- L66 _public function_ `void operator++()`

#### struct `UE::Sequencer::TFilteredSelectionSetIteratorImpl`  
`template<typename KeyType, typename FilterType> struct TFilteredSelectionSetIteratorImpl`  
_L80-113_
- L85 _public function_ `TViewModelPtr<FilterType> operator*() const` — Access the current value of the iterator. By default this just returns the value directly.
- L92 _protected function_ `explicit TFilteredSelectionSetIteratorImpl(typename TSet<KeyType>::TRangedForConstIterator InIteratorBegin, typename TSet<KeyType>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L96 _protected function_ `void SkipInvalid()`
- L110 _protected member_ `typename TSet<KeyType>::TRangedForConstIterator IteratorBegin;`
- L111 _protected member_ `typename TSet<KeyType>::TRangedForConstIterator IteratorEnd;`
- L112 _protected member_ `TViewModelPtr<FilterType> CurrentValue;`

#### struct `UE::Sequencer::TUniqueFragmentSelectionSetIterator`  
`template<typename KeyType> struct TUniqueFragmentSelectionSetIterator`  
_L125-157_
- desc: Iterator for iterating unique fragment selection sets
- L127 _public function_ `void operator++()`
- L132 _public function_ `operator KeyType() const`
- L137 _public function_ `KeyType operator*() const`
- L152 _private function_ `explicit TUniqueFragmentSelectionSetIterator(typename TSet<KeyType>::TRangedForConstIterator InIterator) : Iterator(InIterator)`
- L156 _private member_ `typename TSet<KeyType>::TRangedForConstIterator Iterator;`

#### struct `UE::Sequencer::TFilteredViewModelSelectionIterator`  
`template<typename StorageKeyType, typename FilterType> struct TFilteredViewModelSelectionIterator`  
_L160-166_
- L162 _public member_ `const TSet<StorageKeyType>* SelectionSet;`
- L164 _public function_ `FORCEINLINE TFilteredViewModelSelectionIteratorState<StorageKeyType, FilterType> begin() const`
- L165 _public function_ `FORCEINLINE TFilteredViewModelSelectionIteratorState<StorageKeyType, FilterType> end() const`

#### struct `UE::Sequencer::TSelectionSetIteratorImpl`  
`template<typename T> struct TSelectionSetIteratorImpl<TWeakPtr<T>>`  
_L173-196_
- desc: Specialization for TWeakPtr types that skips invalid pointers and exposes iterators as TSharedPtr
- L33 _public function_ `const T& operator*() const` — Access the current value of the iterator. By default this just returns the value directly.
- L40 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<T>::TRangedForConstIterator InIteratorBegin, typename TSet<T>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L47 _protected function_ `constexpr void SkipInvalid()` — Skip invalid iterations - by default all items are valid
- L50 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorBegin;`
- L51 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorEnd;`
- L175 _public function_ `TSharedPtr<T> operator*() const`
- L182 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L186 _protected function_ `void SkipInvalid()`
- L194 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L195 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorEnd;`
- L205 _public function_ `TViewModelPtr<T> operator*() const`
- L212 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L224 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L225 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorEnd;`

#### struct `UE::Sequencer::TSelectionSetIteratorImpl`  
`template<typename T> struct TSelectionSetIteratorImpl<TWeakViewModelPtr<T>>`  
_L203-226_
- desc: Specialization for TWeakViewModelPtr types that skips invalid pointers and exposes iterators as TViewModelPtr
- L33 _public function_ `const T& operator*() const` — Access the current value of the iterator. By default this just returns the value directly.
- L40 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<T>::TRangedForConstIterator InIteratorBegin, typename TSet<T>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L47 _protected function_ `constexpr void SkipInvalid()` — Skip invalid iterations - by default all items are valid
- L50 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorBegin;`
- L51 _protected member_ `typename TSet<T>::TRangedForConstIterator IteratorEnd;`
- L175 _public function_ `TSharedPtr<T> operator*() const`
- L182 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L186 _protected function_ `void SkipInvalid()`
- L194 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L195 _protected member_ `typename TSet<TWeakPtr<T>>::TRangedForConstIterator IteratorEnd;`
- L205 _public function_ `TViewModelPtr<T> operator*() const`
- L212 _protected function_ `explicit TSelectionSetIteratorImpl(typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorBegin, typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator InIteratorEnd) : IteratorBegin(InIteratorBegin), IteratorEnd(InIteratorEnd)`
- L224 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorBegin;`
- L225 _protected member_ `typename TSet<TWeakViewModelPtr<T>>::TRangedForConstIterator IteratorEnd;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L72 _function_ `friend bool operator!=(const TSelectionSetIteratorState<T, ImplType>& A, const TSelectionSetIteratorState<T, ImplType>& B)` (scope `UE::Sequencer`)
- L119 _typedef_ `template<typename StorageKeyType, typename FilterType> using TFilteredViewModelSelectionIteratorState = TSelectionSetIteratorState<StorageKeyType, TFilteredSelectionSetIteratorImpl<StorageKeyType, FilterType>>;` (scope `UE::Sequencer`) — Filtered iterator for a TSelectionSet<TWeakViewModelPtr<T>> that iterates only the items of a specific filtered type
- L142 _function_ `friend bool operator!=(const TUniqueFragmentSelectionSetIterator<KeyType>& A, const TUniqueFragmentSelectionSetIterator<KeyType>& B)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Selection/SequencerCoreSelectionTypes.h` (Public)


#### class `UE::Sequencer::FSelectionBase`  
`class FSelectionBase`  
_L21-81_
- desc: Base class for all selection sets that can be added to an FSequencerCoreSelection owner.
- L28 _public member_ `FSimpleMulticastDelegate OnChanged;` — Broadcast if this selection set has changed when all event suppressors have been destroyed
- L33 _public prototype_ `void Empty();` — Empty this selection set
- L38 _public function_ `bool HasPendingChanges() const` — Check whether this selection set has reported changes that are currently pending
- L48 _protected function_ `FSelectionBase() : Owner(nullptr) , bSelectionChanged(false)` — Should only be used by derived types
- L53 _protected prototype_ `virtual ~FSelectionBase() = default;`
- L58 _protected function_ `FSequencerCoreSelection* GetOwner() const` — Retrieve the owner of this instance, assuming it has been added to one
- L66 _protected prototype_ `void ReportChanges(bool bInSelectionChanged = true);` — Called by derived classes when they have changed
- L73 _private prototype_ `virtual void EmptyImpl() = 0;` — Abstract function for emptying this selection
- L78 _private member_ `FSequencerCoreSelection* Owner;` — The owning instance of this class
- L80 _private member_ `bool bSelectionChanged;` — Flag indicating whether this selection has changed within the current scope or not

#### class `UE::Sequencer::TSelectionSetBase`  
`template<typename MixinType, typename KeyType> class TSelectionSetBase : public FSelectionBase`  
_L118-309_
- inherits: `FSelectionBase`
- desc: Typed selection set for keeping track of an externally provided key type KeyType is what is stored within the selection set (ie, an FObjectKey, TWeakPtr or int32) MixinType is the type of the derived class. This allows for compile-time injection of OnSelect/OnDeselect behavior without needing virtual function calls: bool OnSelectItem(const KeyType&){ return true; } void OnDeselectItem(const KeyType&){} Example implementation: class FMySelection : TSelectionSetBase<FMySelection, uint32> { public: // Both these functions are optional: bool OnSelectItem(uint32 In){ return In != 0; } void OnDeselectItem(uint32){} }; Iteration is supported for all types (weak ptrs are skipped and iterated as shared pointers): class FMySelection : TSelectionSetBase<FMySelection, FWeakViewModelPtr>{}; FMySelection& Selection = ...; for (FViewModelPtr ViewModel : Selection) { //...; } // Filtered iteration is also supported for TWeakViewModelPtr<> types: for (TViewModelPtr<IOutlinerExtension> Outliner : Selection.Filter<IOutlinerExtension>()) { // Only viewmodels that implement the IOutlinerExtension will be iterated }
- L125 _public function_ `int32 Num() const` — Returns the number of selected items (including potentially invalid items)
- L133 _public function_ `const TSet<KeyType>& GetSelected() const` — Returns the underlying selection set  (including potentially invalid items)
- L141 _public function_ `bool IsSelected(KeyType InKey) const` — Check whether a given item is currently selected
- L152 _public function_ `void Select(KeyType InKey, bool* OutNewlySelected = nullptr)` — Select a key, optionally supplying a boolean to receieve a value indicating whether it was already selected or not @param  InKey                The item to select @param  OutNewlySelected     (Optional) When non-null, will be assigned true of false based on whether this item was newly selected as a result of this call
- L174 _public function_ `template<typename RangeType> void SelectRange(RangeType Range, bool* OutAnySelected = nullptr)` — Selects a range of keys, optionally supplying a boolean to receieve a value indicating whether any were newly selected or not @param  Range               An arbitrary range of items to select. Must be implicitly convertible to KeyType. @param  OutNewlySelected    (Optional) When non-null, will be assigned true of false based on whether this item was newly selected as a result of this call
- L210 _public function_ `void ReplaceWith(TSelectionSetBase<MixinType, KeyType>&& OtherSelection)` — Replace this selection set with the contents from another @param  OtherSelection      The selection set to replace this one with
- L235 _public function_ `void Deselect(KeyType InKey)` — Deselect an item
- L250 _public function_ `void Empty()` — Empty this selection
- L270 _public function_ `template<typename Filter> void RemoveByPredicate(Filter&& InFilter)` — * Remove all selected items that pass the specified filter
- L294 _public function_ `FORCEINLINE TSelectionSetIteratorState<KeyType> begin() const` — Ranged-for iteration support. Do not use directly
- L295 _public function_ `FORCEINLINE TSelectionSetIteratorState<KeyType> end() const`
- L298 _public function_ `FORCEINLINE static constexpr bool OnSelectItem(const KeyType&)` — Fallback functions for use when derived classes do not implement them. Should be completely compiled out
- L299 _public function_ `FORCEINLINE static constexpr void OnDeselectItem(const KeyType&)`
- L303 _protected function_ `void EmptyImpl() override`
- L308 _protected member_ `TSet<KeyType> SelectionSet;`

#### class `UE::Sequencer::TUniqueFragmentSelectionSet`  
`template<typename KeyType, typename ModelType> class TUniqueFragmentSelectionSet : public FSelectionBase`  
_L320-497_
- inherits: `FSelectionBase`
- desc: Selection set that defines a fragment selection of a view model where each fragment is globally unique. A good example is FKeyHandle or any other monotomic counter. Selection must be associated with a view model type defined by the template parameter ModelType.
- L327 _public function_ `int32 Num() const` — Returns the number of selected items (including potentially invalid items)
- L335 _public function_ `const TSet<KeyType>& GetSelected() const` — Returns the underlying selection set (including potentially invalid items)
- L343 _public function_ `TViewModelPtr<ModelType> GetModelForKey(KeyType InKey) const` — Retrieve the view model associated with the specified fragment selection
- L351 _public function_ `bool IsSelected(KeyType InKey) const` — Check whether a given item is currently selected
- L362 _public function_ `void Select(TViewModelPtr<ModelType> InOwner, KeyType InKey, bool* OutNewlySelected = nullptr)` — Select a key, optionally supplying a boolean to receieve a value indicating whether it was already selected or not @param  InKey                The item to select @param  OutNewlySelected     (Optional) When non-null, will be assigned true of false based on whether this item was newly selected as a result of this call
- L375 _public function_ `template<typename RangeType> void SelectRange(TViewModelPtr<ModelType> InOwner, RangeType Range, bool* OutAnySelected = nullptr)` — Selects a range of keys, optionally supplying a boolean to receieve a value indicating whether any were newly selected or not @param  Range               An arbitrary range of items to select. Must be implicitly convertible to KeyType. @param  OutNewlySelected    (Optional) When non-null, will be assigned true of false based on whether this item was newly selected as a result of this call
- L411 _public function_ `void ReplaceWith(TUniqueFragmentSelectionSet<KeyType, ModelType>&& OtherSelection)` — Replace this selection set with the contents from another @param  OtherSelection      The selection set to replace this one with
- L429 _public function_ `void Deselect(KeyType InKey)` — Deselect an item
- L444 _public function_ `void Empty()` — Empty this selection
- L459 _public function_ `template<typename Filter> void RemoveByPredicate(Filter&& InFilter)` — Remove all selected items that pass the specified filter
- L483 _public function_ `FORCEINLINE TUniqueFragmentSelectionSetIterator<KeyType> begin() const`
- L484 _public function_ `FORCEINLINE TUniqueFragmentSelectionSetIterator<KeyType> end() const`
- L488 _private function_ `void EmptyImpl() override`
- L494 _private member_ `TSet<KeyType> SelectionSet;` — The unique selection set of fragments
- L496 _private member_ `TMap<KeyType, TWeakViewModelPtr<ModelType>> KeyToViewModel;` — Reverse mapping from item to its owning model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Selection/SequencerOutlinerSelection.h` (Public)


#### class `UE::Sequencer::FOutlinerSelection`  
`class FOutlinerSelection : public TSelectionSetBase<FOutlinerSelection, TWeakViewModelPtr<IOutlinerExtension>>`  
_L18-37_
- inherits: `TSelectionSetBase<FOutlinerSelection,TWeakViewModelPtr<IOutlinerExtension>>`
- L26 _public function_ `template<typename FilterType> TFilteredViewModelSelectionIterator<TWeakViewModelPtr<IOutlinerExtension>, FilterType> Filter() const` — Filter this selection set based on the specified filter type
- L35 _private prototype_ `bool OnSelectItem(const TWeakViewModelPtr<IOutlinerExtension>& WeakViewModel);`
- L36 _private prototype_ `void OnDeselectItem(const TWeakViewModelPtr<IOutlinerExtension>& WeakViewModel);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Selection/SequencerSelectionEventSuppressor.h` (Public)


#### struct `UE::Sequencer::FSelectionEventSuppressor`  
`struct FSelectionEventSuppressor`  
_L16-29_
- desc: Scoped object type that temporarily suppresses broadcast of selection events @see FSequencerCoreSelection::SuppressEvents
- L18 _public prototype_ `FSelectionEventSuppressor(FSequencerCoreSelection* InSelection);`
- L19 _public prototype_ `~FSelectionEventSuppressor();`
- L21 _public prototype_ `FSelectionEventSuppressor(const FSelectionEventSuppressor&) = delete;`
- L22 _public prototype_ `void operator=(const FSelectionEventSuppressor&) = delete;`
- L24 _public prototype_ `FSelectionEventSuppressor(FSelectionEventSuppressor&&) = delete;`
- L25 _public prototype_ `void operator=(FSelectionEventSuppressor&&) = delete;`
- L28 _private member_ `FSequencerCoreSelection* Selection;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/SharedList.h` (Public)


#### class `UE::Sequencer::TSharedListItem`  
`template<typename T> class TSharedListItem : public TSharedFromThis<T>`  
_L13-57_
- inherits: `TSharedFromThis<T>`
- L16 _public function_ `virtual ~TSharedListItem()`
- L21 _public function_ `TSharedPtr<T> Next() const`
- L26 _public function_ `void Link(TSharedPtr<T>& Head)`
- L38 _public function_ `void Unlink()`
- L55 _private member_ `TSharedPtr<T> NextLink;`
- L56 _private member_ `TSharedPtr<T>* PrevLink = nullptr;`

#### class `UE::Sequencer::TWeakListItem`  
`template<typename T> class TWeakListItem`  
_L61-65_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/SharedViewModelData.h` (Public)


#### class `UE::Sequencer::FSharedViewModelData`  
`class FSharedViewModelData : public FViewModel`  
_L25-50_
- inherits: `FViewModel`
- L32 _public prototype_ `void PreHierarchicalChange(const TSharedPtr<FViewModel>& InChangedModel);`
- L33 _public prototype_ `void BroadcastHierarchicalChange(const TSharedPtr<FViewModel>& InChangedModel);`
- L35 _public prototype_ `void ReportLatentHierarchicalOperations();`
- L37 _public prototype_ `FSimpleMulticastDelegate& SubscribeToHierarchyChanged(const TSharedPtr<FViewModel>& InModel);`
- L38 _public prototype_ `void UnsubscribeFromHierarchyChanged(const TSharedPtr<FViewModel>& InModel, FDelegateHandle InHandle);`
- L39 _public prototype_ `void UnsubscribeFromHierarchyChanged(const TSharedPtr<FViewModel>& InModel, FDelegateUserObjectConst InUserObject);`
- L41 _public prototype_ `void PurgeStaleHandlers();`
- L46 _private member_ `TMap<TWeakPtr<FViewModel>, FSimpleMulticastDelegate> HierarchyChangedEventsByModel;`
- L48 _private member_ `FViewModelHierarchyOperation* CurrentHierarchicalOperation = nullptr;`
- L49 _private member_ `TUniquePtr<FViewModelHierarchyOperation> LatentOperation;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCERCORE_API`
- L18 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModelPtr.h` (Public)


#### struct `UE::Sequencer::TViewModelPtrStorage`  
`template<typename T> struct TViewModelPtrStorage`  
_L21-51_
- desc: Storage selector implemented as a type alias to defer instantiation and allow use with fwd declared types
- L24 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;` — ~ Define either 'FViewModel' or 'const FViewModel' based on the constness of T
- L26 _public function_ `FORCEINLINE T* Get() const`
- L30 _public function_ `FORCEINLINE const TSharedPtr<ViewModelType>& GetModel() const`
- L35 _public function_ `void Set(TSharedPtr<ViewModelType> InModel, T* ExtensionPtr)`
- L49 _public member_ `TSharedPtr<ViewModelType> SharedModel;`
- L50 _public member_ `T* Extension = nullptr;`

#### struct `UE::Sequencer::TViewModelConversions`  
`template<typename T> struct TViewModelConversions`  
_L54-80_
- L57 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;` — ~ Define either 'FViewModel' or 'const FViewModel' based on the constness of T
- L59 _public function_ `operator TSharedPtr<ViewModelType>() const`
- L63 _public function_ `operator TSharedPtr<T>() const`
- L68 _public function_ `operator TWeakPtr<ViewModelType>() const`
- L72 _public function_ `operator TWeakPtr<T>() const`
- L76 _public function_ `TWeakViewModelPtr<T> AsWeak() const`
- L84 _public prototype_ `operator TSharedPtr<FViewModel>() const;`
- L85 _public prototype_ `operator TWeakPtr<FViewModel>() const;`
- L87 _public prototype_ `TWeakViewModelPtr<FViewModel> AsWeak() const;`
- L92 _public prototype_ `operator TSharedPtr<const FViewModel>() const;`
- L93 _public prototype_ `operator TWeakPtr<const FViewModel>() const;`
- L95 _public prototype_ `TWeakViewModelPtr<const FViewModel> AsWeak() const;`

#### struct `UE::Sequencer::TViewModelConversions`  
`template<> struct TViewModelConversions<FViewModel>`  
_L82-88_
- L57 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;` — ~ Define either 'FViewModel' or 'const FViewModel' based on the constness of T
- L59 _public function_ `operator TSharedPtr<ViewModelType>() const`
- L63 _public function_ `operator TSharedPtr<T>() const`
- L68 _public function_ `operator TWeakPtr<ViewModelType>() const`
- L72 _public function_ `operator TWeakPtr<T>() const`
- L76 _public function_ `TWeakViewModelPtr<T> AsWeak() const`
- L84 _public prototype_ `operator TSharedPtr<FViewModel>() const;`
- L85 _public prototype_ `operator TWeakPtr<FViewModel>() const;`
- L87 _public prototype_ `TWeakViewModelPtr<FViewModel> AsWeak() const;`
- L92 _public prototype_ `operator TSharedPtr<const FViewModel>() const;`
- L93 _public prototype_ `operator TWeakPtr<const FViewModel>() const;`
- L95 _public prototype_ `TWeakViewModelPtr<const FViewModel> AsWeak() const;`

#### struct `UE::Sequencer::TViewModelConversions`  
`template<> struct TViewModelConversions<const FViewModel>`  
_L90-96_
- L57 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;` — ~ Define either 'FViewModel' or 'const FViewModel' based on the constness of T
- L59 _public function_ `operator TSharedPtr<ViewModelType>() const`
- L63 _public function_ `operator TSharedPtr<T>() const`
- L68 _public function_ `operator TWeakPtr<ViewModelType>() const`
- L72 _public function_ `operator TWeakPtr<T>() const`
- L76 _public function_ `TWeakViewModelPtr<T> AsWeak() const`
- L84 _public prototype_ `operator TSharedPtr<FViewModel>() const;`
- L85 _public prototype_ `operator TWeakPtr<FViewModel>() const;`
- L87 _public prototype_ `TWeakViewModelPtr<FViewModel> AsWeak() const;`
- L92 _public prototype_ `operator TSharedPtr<const FViewModel>() const;`
- L93 _public prototype_ `operator TWeakPtr<const FViewModel>() const;`
- L95 _public prototype_ `TWeakViewModelPtr<const FViewModel> AsWeak() const;`

#### struct `UE::Sequencer::TViewModelPtr`  
`template<typename T> struct TViewModelPtr : TViewModelConversions<T>`  
_L107-336_
- inherits: `TViewModelConversions<T>`
- desc: Pointer type that wraps a shared view model pointer to provide implicit dynamic_cast style casting to any other view-model or extension. Implicit conversion is implemented through a proxy object so as to make the 'implicit' conversion somewhat explicit: FViewModelPtr ModelPtr = GetViewModel(); TSharedPtr<IDraggableOutlinerExtension>   Draggable = ModelPtr.ImplicitCast(); TSharedPtr<IDroppableExtension>           Droppable = ModelPtr.ImplicitCast();
- L109 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;`
- L111 _public prototype_ `TViewModelPtr() = default;`
- L112 _public prototype_ `TViewModelPtr(const TViewModelPtr&) = default;`
- L113 _public prototype_ `TViewModelPtr& operator=(const TViewModelPtr&) = default;`
- L114 _public prototype_ `TViewModelPtr(TViewModelPtr&&) = default;`
- L115 _public prototype_ `TViewModelPtr& operator=(TViewModelPtr&&) = default;`
- L117 _public function_ `explicit TViewModelPtr(T* InViewModelType)`
- L122 _public function_ `TViewModelPtr(TSharedPtr<ViewModelType> InModel, T* InExtension)`
- L131 _public function_ `template<typename OtherType> TViewModelPtr(const TViewModelPtr<OtherType>& In)`
- L144 _public function_ `template<typename OtherType> TViewModelPtr& operator=(const TViewModelPtr<OtherType>& In)`
- L158 _public function_ `TViewModelPtr(TYPE_OF_NULLPTR)` — Construction from a nullptr
- L162 _public function_ `TViewModelPtr& operator=(TYPE_OF_NULLPTR)` — Assignment from a nullptr
- L170 _public function_ `template<typename ModelType> TViewModelPtr(const TSharedPtr<ModelType>& InModel)` — Construction from a shared ptr
- L179 _public function_ `template<typename ModelType> TViewModelPtr& operator=(const TSharedPtr<ModelType>& InModel)` — Assignment from a shared ptr
- L190 _public function_ `template<typename ModelType> TViewModelPtr(const TSharedRef<ModelType>& InModel)` — Construction from a shared ptr
- L200 _public function_ `template<typename ModelType> TViewModelPtr& operator=(const TSharedRef<ModelType>& InModel)` — Assignment from a shared ptr
- L215 _public function_ `explicit operator bool() const` — Check whether this ptr is valid (non-null)
- L223 _public function_ `void Reset()` — Reset this view model pointer back to its default (null) state
- L231 _public function_ `T* operator->() const` — Member access operator giving access to the wrapped view model
- L241 _public function_ `T* Get() const` — Member access operator giving access to the wrapped view model
- L249 _public function_ `T& operator*() const` — Dereference operator giving access to the wrapped view model
- L259 _public function_ `TSharedPtr<ViewModelType> AsModel() const` — Explicitly access the view model as a regular shared pointer
- L263 _public function_ `TSharedRef<T> ToSharedRef() const`
- L267 _public function_ `bool IsValid() const`
- L276 _public prototype_ `TImplicitViewModelCast<ViewModelType> ImplicitCast() const;` — Return a proxy type that is able to implicitly convert this view model to any other TViewModel<IMyExtension> or TSharedPtr<IMyExtension>
- L277 _public prototype_ `TImplicitViewModelCastChecked<ViewModelType> ImplicitCastChecked() const;`
- L335 _protected member_ `TViewModelPtrStorage<T> Storage;`
- L632 _function_ `template<typename T> TImplicitViewModelCast<typename TViewModelPtr<T>::ViewModelType> TViewModelPtr<T>::ImplicitCast() const`
- L637 _function_ `template<typename T> TImplicitViewModelCastChecked<typename TViewModelPtr<T>::ViewModelType> TViewModelPtr<T>::ImplicitCastChecked() const`

#### struct `UE::Sequencer::TWeakViewModelConversions`  
`template<typename T> struct TWeakViewModelConversions`  
_L401-409_
- L403 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;`
- L405 _public function_ `operator TWeakPtr<ViewModelType>() const`

#### struct `UE::Sequencer::TWeakViewModelPtr`  
`template<typename T> struct TWeakViewModelPtr : TWeakViewModelConversions<T>`  
_L416-505_
- inherits: `TWeakViewModelConversions<T>`
- desc: Templated version of FWeakViewModelPtr that provides an additional self-documenting extension that should exist on the view model.
- L418 _public typedef_ `using ViewModelType = typename std::conditional_t<std::is_const_v<T>, const FViewModel, FViewModel>;`
- L420 _public prototype_ `TWeakViewModelPtr() = default;`
- L421 _public prototype_ `TWeakViewModelPtr(const TWeakViewModelPtr&) = default;`
- L422 _public prototype_ `TWeakViewModelPtr& operator=(const TWeakViewModelPtr&) = default;`
- L423 _public prototype_ `TWeakViewModelPtr(TWeakViewModelPtr&&) = default;`
- L424 _public prototype_ `TWeakViewModelPtr& operator=(TWeakViewModelPtr&&) = default;`
- L426 _public function_ `TWeakViewModelPtr(TYPE_OF_NULLPTR)`
- L430 _public function_ `template<typename OtherType> TWeakViewModelPtr(const TWeakPtr<OtherType>& InModel)`
- L438 _public function_ `template<typename OtherType> TWeakViewModelPtr(const TSharedPtr<OtherType>& InModel)`
- L446 _public function_ `template<typename OtherType> TWeakViewModelPtr(const TSharedRef<OtherType>& InModel)`
- L455 _public function_ `template<typename OtherType> TWeakViewModelPtr(const TViewModelPtr<OtherType>& InModel)` — Construction from a TViewModelPtr
- L464 _public function_ `template<typename OtherType> TWeakViewModelPtr& operator=(const TViewModelPtr<OtherType>& InModel)` — Assignment from a TViewModelPtr
- L474 _public function_ `TViewModelPtr<T> Pin() const` — Pin this weak view model ptr
- L484 _public prototype_ `TImplicitWeakViewModelPin<ViewModelType> ImplicitPin() const;` — Returns a proxy object that will simultaneously Pin() and Cast() this view model to a particular view-model or extension type
- L504 _protected member_ `TWeakPtr<ViewModelType> WeakModel;`
- L643 _function_ `template<typename T> TImplicitWeakViewModelPin<typename TWeakViewModelPtr<T>::ViewModelType> TWeakViewModelPtr<T>::ImplicitPin() const`

#### struct `UE::Sequencer::TImplicitViewModelCastImpl`  
`template<typename ViewModelType, bool bChecked> struct TImplicitViewModelCastImpl`  
_L517-571_
- desc: Proxy type that enables implicit dynamic casting of a view-model to any other view-model or extension type. This is implemented as a proxy type rather than the conversion operators existing on FViewModelPtr so that the implicit cast must be user-directed, while still removing additional template boilerplate at the call-site. @see FViewModelPtr::ImplicitCast
- L520 _public function_ `explicit TImplicitViewModelCastImpl(const TSharedPtr<ViewModelType>& In) : ViewModel(In)` — Construction from a regular shared ptr to a view model
- L529 _public function_ `template<typename ExtensionType> operator TSharedPtr<ExtensionType>() const` — Implicitly convert this view model to any other view-model or extension type @return A regular shared pointer to the view-model or extension if it is implemented on the existing model; nullptr otherwise.
- L546 _public function_ `template<typename ExtensionType> operator TViewModelPtr<ExtensionType>() const` — Implicitly convert this view model to any other view-model or extension type @return A TViewModelPtr to the view-model or extension if it is implemented on the existing model; nullptr otherwise.
- L563 _public function_ `template<typename ExtensionType> operator TWeakViewModelPtr<ExtensionType>() const` — Implicitly convert this view model to any other view-model or extension type @return A TWeakViewModelPtr to the view-model or extension if it is implemented on the existing model; nullptr otherwise.
- L570 _private member_ `TSharedPtr<ViewModelType> ViewModel;`

#### struct `UE::Sequencer::TImplicitWeakViewModelPin`  
`template<typename ViewModelType> struct TImplicitWeakViewModelPin`  
_L579-628_
- desc: Proxy type that combines a Pin() and Cast() of a weak view model ptr, gracefully handling null. @see FWeakViewModelPtr::ImplicitPin
- L582 _public function_ `explicit TImplicitWeakViewModelPin(const TWeakPtr<ViewModelType>& In) : WeakModel(In)` — Construction from a regular weak ptr to a view model
- L591 _public function_ `template<typename ExtensionType> operator TSharedPtr<ExtensionType>() const` — Simultaneously Pin() and Cast() this view model to the templated type @return A shared pointer to the view-model or extension type if it is implemented on this model, nullptr otherwise.
- L607 _public function_ `template<typename ExtensionType> operator TViewModelPtr<ExtensionType>() const` — Simultaneously Pin() and Cast() this view model to the templated type @return A TViewModelPtr to the view-model or extension type if it is implemented on this model, nullptr otherwise.
- L620 _public function_ `template<typename ExtensionType> operator TWeakViewModelPtr<ExtensionType>() const`
- L627 _private member_ `TWeakPtr<ViewModelType> WeakModel;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
- L282 _function_ `friend uint32 GetTypeHash(const TViewModelPtr<T>& In)` (scope `UE::Sequencer`) — Type hash function for use with the TSet and TMap family of containers
- L290 _function_ `friend bool operator==(const TViewModelPtr<T>& A, const TViewModelPtr<T>& B)` (scope `UE::Sequencer`) — Equality operator comparing 2 view model pointers
- L294 _function_ `friend bool operator!=(const TViewModelPtr<T>& A, const TViewModelPtr<T>& B)` (scope `UE::Sequencer`)
- L300 _function_ `template<typename SharedType> friend bool operator==(const TViewModelPtr<T>& A, const TSharedPtr<SharedType>& B)` (scope `UE::Sequencer`)
- L305 _function_ `template<typename SharedType> friend bool operator!=(const TViewModelPtr<T>& A, const TSharedPtr<SharedType>& B)` (scope `UE::Sequencer`)
- L311 _function_ `template<typename SharedType> friend bool operator==(const TViewModelPtr<T>& A, const TSharedRef<SharedType>& B)` (scope `UE::Sequencer`)
- L316 _function_ `template<typename SharedType> friend bool operator!=(const TViewModelPtr<T>& A, const TSharedRef<SharedType>& B)` (scope `UE::Sequencer`)
- L321 _function_ `friend bool operator==(const TViewModelPtr<T>& A, TYPE_OF_NULLPTR B)` (scope `UE::Sequencer`)
- L325 _function_ `friend bool operator!=(const TViewModelPtr<T>& A, TYPE_OF_NULLPTR B)` (scope `UE::Sequencer`)
- L340 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModel(const TSharedRef<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L345 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModel(const TSharedPtr<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L354 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModel(const TViewModelPtr<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L360 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModelChecked(const TSharedRef<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L367 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModelChecked(const TSharedPtr<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L374 _function_ `template<typename OutModelType, typename InModelType> TViewModelPtr<OutModelType> CastViewModelChecked(const TViewModelPtr<InModelType>& InViewModel)` (scope `UE::Sequencer`)
- L486 _function_ `friend uint32 GetTypeHash(const TWeakViewModelPtr<T>& In)` (scope `UE::Sequencer`)
- L491 _function_ `friend bool operator==(const TWeakViewModelPtr<T>& A, const TWeakViewModelPtr<T>& B)` (scope `UE::Sequencer`)
- L496 _function_ `friend bool operator!=(const TWeakViewModelPtr<T>& A, const TWeakViewModelPtr<T>& B)` (scope `UE::Sequencer`)
- L531 _typedef_ `using FinalExtensionType = std::conditional_t<std::is_const_v<ViewModelType>, const ExtensionType, ExtensionType>;` (scope `UE::Sequencer::TImplicitViewModelCastImpl::operator TSharedPtr<ExtensionType>`)
- L548 _typedef_ `using FinalExtensionType = std::conditional_t<std::is_const_v<ViewModelType>, const ExtensionType, ExtensionType>;` (scope `UE::Sequencer::TImplicitViewModelCastImpl::operator TViewModelPtr<ExtensionType>`)
- L593 _typedef_ `using FinalExtensionType = std::conditional_t<std::is_const_v<ViewModelType>, const ExtensionType, ExtensionType>;` (scope `UE::Sequencer::TImplicitWeakViewModelPin::operator TSharedPtr<ExtensionType>`)
- L609 _typedef_ `using FinalExtensionType = std::conditional_t<std::is_const_v<ViewModelType>, const ExtensionType, ExtensionType>;` (scope `UE::Sequencer::TImplicitWeakViewModelPin::operator TViewModelPtr<ExtensionType>`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModelTypeID.h` (Public)


#### struct `UE::Sequencer::FViewModelTypeID`  
`struct FViewModelTypeID`  
_L31-64_
- L48 _public function_ `uint32 GetTypeID() const`
- L53 _public prototype_ `static uint32 RegisterNewID();`
- L55 _public function_ `FViewModelTypeID(FCastableTypeTable* InTypeTable, uint32 InID) : TypeTable(InTypeTable) , ID(InID)`
- L62 _private member_ `FCastableTypeTable* TypeTable;`
- L63 _private member_ `uint32 ID;`

#### struct `UE::Sequencer::TViewModelTypeID`  
`template<typename T> struct TViewModelTypeID`  
_L67-105_
- L69 _public function_ `operator FViewModelTypeID() const`
- L75 _public function_ `uint32 GetTypeID() const`
- L81 _public function_ `FCastableTypeTable* GetTypeTable() const`
- L87 _public function_ `void Register() const`
- L98 _protected function_ `bool IsRegistered() const`
- L103 _protected member_ `FCastableTypeTable* TypeTable = nullptr;`
- L104 _protected member_ `uint32 ID = ~0u;`

#### struct `UE::Sequencer::TAutoRegisterViewModelTypeID`  
`template<typename T> struct TAutoRegisterViewModelTypeID : TViewModelTypeID<T>`  
_L108-110_
- inherits: `TViewModelTypeID<T>`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_SEQUENCER_DECLARE_VIEW_MODEL_TYPE_ID(Type) \`
- L12 _macro_ `#define UE_SEQUENCER_DECLARE_VIEW_MODEL_TYPE_ID_API(MODULE_API, Type) \`
- L16 _macro_ `#define UE_SEQUENCER_DEFINE_VIEW_MODEL_TYPE_ID(Type) \`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Sequencer` (scope `UE`)
- L33 _function_ `friend uint32 GetTypeHash(FViewModelTypeID In)` (scope `UE::Sequencer`)
- L38 _function_ `friend bool operator<(FViewModelTypeID A, FViewModelTypeID B)` (scope `UE::Sequencer`)
- L43 _function_ `friend bool operator==(FViewModelTypeID A, FViewModelTypeID B)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/EditorSharedViewModelData.h` (Public)


#### class `UE::Sequencer::FEditorSharedViewModelData`  
`class FEditorSharedViewModelData : public FSharedViewModelData`  
_L14-35_
- inherits: `FSharedViewModelData`
- L21 _public function_ `FEditorSharedViewModelData(TSharedRef<FEditorViewModel> InEditor) : WeakEditor(InEditor)`
- L26 _public function_ `TSharedPtr<FEditorViewModel> GetEditor() const`
- L34 _private member_ `TWeakPtr<FEditorViewModel> WeakEditor;` — The editor view model for this shared data

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/EditorViewModel.h` (Public)


#### class `UE::Sequencer::FEditorViewModel`  
`class FEditorViewModel : public FViewModel`  
_L41-130_
- inherits: `FViewModel`
- desc: This represents to root view-model for a sequencer-like editor. This view-model assumes that the editor includes at least an outliner area and a track area. Other panels in the editor can be added to the list of panels. The data being edited is represented by a root view-model which doesn't change: if the editor needs to edit a different piece of data, this should change *inside* the root view-model, and call the necessary code to refresh the entire view-model hierarchy. Note that this root view-model is *not* parented under the editor view-model.
- L49 _public prototype_ `static EViewModelListType GetEditorPanelType();` — Children type for editor panels
- L52 _public prototype_ `FEditorViewModel();` — Builds a new editor view model.
- L54 _public prototype_ `~FEditorViewModel();` — Destroys this editor view model.
- L57 _public prototype_ `void InitializeEditor();` — Initializes the outliner and track-area for this editor.
- L60 _public prototype_ `FViewModelPtr GetRootModel() const;` — Gets the root view-model of the sequence being edited.
- L63 _public prototype_ `FViewModelChildren GetEditorPanels();` — Gets the editor panels' view models.
- L66 _public prototype_ `TSharedPtr<FOutlinerViewModel> GetOutliner() const;` — Gets the outliner view-model.
- L69 _public prototype_ `TSharedPtr<FTrackAreaViewModel> GetTrackArea() const;` — Gets the track area view-model.
- L72 _public prototype_ `TSharedPtr<FSequencerCoreSelection> GetSelection() const;` — Gets the selection class
- L75 _public prototype_ `USequencerScriptingLayer* GetScriptingLayer() const;` — Gets the scripting layer
- L78 _public prototype_ `FViewDensityInfo GetViewDensity() const;` — Returns the current view density for this editor
- L81 _public prototype_ `void SetViewDensity(const FViewDensityInfo& InViewDensity);` — Returns the current view density for this editor
- L84 _public prototype_ `virtual bool IsReadOnly() const;` — Returns whether this editor is currently read-only
- L87 _public function_ `bool IsEditable() const` — Returns the inverse of read-only - useful for direct bindings to IsEnabled for widgets
- L95 _protected function_ `virtual void PreInitializeEditorImpl()` — Initializes this view model before panels and root models are created
- L97 _protected prototype_ `virtual TSharedPtr<FViewModel> CreateRootModelImpl();` — Creates the root data model for this editor.
- L99 _protected prototype_ `virtual TSharedPtr<FOutlinerViewModel> CreateOutlinerImpl();` — Creates the outliner for this editor.
- L101 _protected prototype_ `virtual TSharedPtr<FTrackAreaViewModel> CreateTrackAreaImpl();` — Creates the track-area for this editor.
- L103 _protected prototype_ `virtual TSharedPtr<FSequencerCoreSelection> CreateSelectionImpl();` — Creates the selection class for this editor.
- L105 _protected prototype_ `virtual USequencerScriptingLayer* CreateScriptingLayerImpl();` — Creates the scripting layer class for this editor.
- L107 _protected function_ `virtual void InitializeEditorImpl()` — Creates any other panels for this editor.
- L114 _private member_ `FViewModelListHead PanelList;` — List of panel view-models for this editor
- L117 _private member_ `TSharedPtr<FOutlinerViewModel> Outliner;` — Cached pointer to the outliner panel view-model
- L119 _private member_ `TSharedPtr<FTrackAreaViewModel> TrackArea;` — Cached pointer to the track area panel view-model
- L121 _private member_ `TSharedPtr<FSequencerCoreSelection> Selection;` — Cached pointer to the selection class
- L123 _private member_ `TStrongObjectPtr<USequencerScriptingLayer> ScriptingLayer;` — Cached pointer to the scripting layer class
- L126 _private member_ `TSharedPtr<FViewModel> RootDataModel;` — The root view-model for the data being edited
- L129 _private member_ `FViewDensityInfo ViewDensity;` — This editor's current view density defining how condensed the elements appear

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API SEQUENCERCORE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/AddOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FAddOutlinerColumn`  
`class FAddOutlinerColumn : public FOutlinerColumnBase`  
_L10-16_
- inherits: `FOutlinerColumnBase`
- L15 _public prototype_ `FAddOutlinerColumn();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/ColorPickerOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FColorPickerOutlinerColumn`  
`class FColorPickerOutlinerColumn : public FOutlinerColumnBase`  
_L10-16_
- inherits: `FOutlinerColumnBase`
- L15 _public prototype_ `FColorPickerOutlinerColumn();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/DeactivateOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FDeactivateOutlinerColumn`  
`class FDeactivateOutlinerColumn : public FOutlinerColumnBase`  
_L13-21_
- inherits: `FOutlinerColumnBase`
- desc: A column for local (not serialized to the asset) muting/unmuting tracks.
- L17 _public prototype_ `FDeactivateOutlinerColumn();`
- L19 _public prototype_ `bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const override;`
- L20 _public prototype_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/EditOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FEditOutlinerColumn`  
`class FEditOutlinerColumn : public FOutlinerColumnBase`  
_L10-16_
- inherits: `FOutlinerColumnBase`
- L15 _public prototype_ `FEditOutlinerColumn();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/IOutlinerColumn.h` (Public)


#### struct `UE::Sequencer::FCreateOutlinerColumnParams`  
`struct FCreateOutlinerColumnParams`  
_L24-33_
- desc: Parameters for creating an outliner column widget.
- L26 _public function_ `FCreateOutlinerColumnParams(const TViewModelPtr<IOutlinerExtension>& InOutlinerExtension, const TSharedPtr<FEditorViewModel> InEditor) : OutlinerExtension(InOutlinerExtension) , Editor(InEditor)`
- L31 _public member_ `const TViewModelPtr<IOutlinerExtension> OutlinerExtension;`
- L32 _public member_ `const TSharedPtr<FEditorViewModel> Editor;`

#### class `UE::Sequencer::IOutlinerColumn`  
`class IOutlinerColumn : public TSharedFromThis<IOutlinerColumn>`  
_L38-72_
- inherits: `TSharedFromThis<IOutlinerColumn>`
- desc: Interface for sequencer outliner columns.
- L44 _public prototype_ `virtual FName GetColumnName() const = 0;` — Returns the name of the column. Used for determining column type when dragging or saving settings.
- L47 _public prototype_ `virtual FText GetColumnLabel() const = 0;` — Returns the label of the column to display in visibility settings.
- L50 _public prototype_ `virtual FOutlinerColumnPosition GetPosition() const = 0;` — Get this columns position data relative to other columns
- L53 _public prototype_ `virtual FOutlinerColumnLayout GetLayout() const = 0;` — Get the layout information for this column's cells
- L56 _public function_ `virtual bool IsColumnVisibleByDefault() const` — The default visibility state of this column when loaded for the first time.
- L59 _public function_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const` — Gets whether or not this column is supported by a given Sequencer.
- L62 _public prototype_ `virtual bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const = 0;` — Gets whether or not a widget should be generated for a given item in the outliner column.
- L65 _public prototype_ `virtual TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) = 0;` — Gets the widget created for each item within the SOutlinerView, column widgets must be fixed width.
- L70 _public prototype_ `virtual ~IOutlinerColumn() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/KeyFrameOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FKeyFrameOutlinerColumn`  
`class FKeyFrameOutlinerColumn : public FOutlinerColumnBase`  
_L10-18_
- inherits: `FOutlinerColumnBase`
- L15 _public prototype_ `FKeyFrameOutlinerColumn();`
- L17 _public prototype_ `bool IsColumnVisibleByDefault() const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/LabelOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FLabelOutlinerColumn`  
`class FLabelOutlinerColumn : public FOutlinerColumnBase`  
_L13-21_
- inherits: `FOutlinerColumnBase`
- desc: Label Column
- L18 _public prototype_ `FLabelOutlinerColumn();`
- L20 _public prototype_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/LockOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FLockOutlinerColumn`  
`class FLockOutlinerColumn : public FOutlinerColumnBase`  
_L13-22_
- inherits: `FOutlinerColumnBase`
- desc: A column for locking/unlocking tracks.
- L18 _public prototype_ `FLockOutlinerColumn();`
- L20 _public prototype_ `bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const override;`
- L21 _public prototype_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/MuteOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FMuteOutlinerColumn`  
`class FMuteOutlinerColumn : public FOutlinerColumnBase`  
_L13-22_
- inherits: `FOutlinerColumnBase`
- desc: A column for muting/unmuting tracks.
- L18 _public prototype_ `FMuteOutlinerColumn();`
- L20 _public prototype_ `bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const override;`
- L21 _public prototype_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/NavOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FNavOutlinerColumn`  
`class FNavOutlinerColumn : public FOutlinerColumnBase`  
_L10-16_
- inherits: `FOutlinerColumnBase`
- L15 _public prototype_ `FNavOutlinerColumn();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/OutlinerColumnBase.h` (Public)


#### class `UE::Sequencer::FOutlinerColumnBase`  
`class FOutlinerColumnBase : public IOutlinerColumn`  
_L11-66_
- inherits: `IOutlinerColumn`
- L16 _public function_ `FOutlinerColumnBase()`
- L20 _public function_ `FOutlinerColumnBase(FName InName, FText InLabel, FOutlinerColumnPosition InPosition, FOutlinerColumnLayout InLayout) : Name(InName), Label(InLabel), Position(InPosition), Layout(InLayout)`
- L25 _public function_ `FName GetColumnName() const override`
- L30 _public function_ `FText GetColumnLabel() const override`
- L35 _public function_ `FOutlinerColumnPosition GetPosition() const override`
- L40 _public function_ `FOutlinerColumnLayout GetLayout() const override`
- L45 _public function_ `bool IsColumnVisibleByDefault() const override`
- L50 _public function_ `bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const override`
- L55 _public function_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override`
- L62 _protected member_ `FName Name;`
- L63 _protected member_ `FText Label;`
- L64 _protected member_ `FOutlinerColumnPosition Position;`
- L65 _protected member_ `FOutlinerColumnLayout Layout;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/OutlinerColumnTypes.h` (Public)


#### enum `UE::Sequencer::EOutlinerColumnFlags`  
`enum class EOutlinerColumnFlags : uint8`  
_L12-21_
- L14 _public enumerator_ `None = 0`
- L16 _public enumerator_ `OverflowSubsequentEmptyCells = 1 << 0`
- L18 _public enumerator_ `OverflowOnHover = 1 << 1`
- L20 _public enumerator_ `Hidden = 1 << 2`

#### enum `UE::Sequencer::EOutlinerColumnGroup`  
`enum class EOutlinerColumnGroup : uint8`  
_L24-40_
- L27 _public enumerator_ `LeftGutter` — Far left gutter area: Indicators
- L30 _public enumerator_ `AssetToggles` — Asset state toggles area: Pin, Lock, Deactivate (states saved to the asset)
- L33 _public enumerator_ `TransientToggles` — Editor transient state toggles area: Mute, Solo (states NOT saved to the asset)
- L36 _public enumerator_ `Center` — Main center area: Add, Edit, Label
- L39 _public enumerator_ `RightGutter` — Far right gutter area: Key Frame, Key Nav, Color Picker, etc.

#### enum `UE::Sequencer::EOutlinerColumnSizeMode`  
`enum class EOutlinerColumnSizeMode : uint8`  
_L42-46_
- L44 _public enumerator_ `Fixed`
- L45 _public enumerator_ `Stretch`

#### struct `UE::Sequencer::FOutlinerColumnPosition`  
`struct FOutlinerColumnPosition`  
_L48-61_
- L50 _public member_ `int16 SortOrder = 0;`
- L51 _public member_ `EOutlinerColumnGroup Group = EOutlinerColumnGroup::Center;`

#### struct `UE::Sequencer::FOutlinerColumnLayout`  
`struct FOutlinerColumnLayout`  
_L63-71_
- L65 _public member_ `float Width;`
- L66 _public member_ `FMargin CellPadding;`
- L67 _public member_ `EHorizontalAlignment HAlign;`
- L68 _public member_ `EVerticalAlignment VAlign;`
- L69 _public member_ `EOutlinerColumnSizeMode SizeMode;`
- L70 _public member_ `EOutlinerColumnFlags Flags;`

#### struct `UE::Sequencer::FCommonOutlinerNames`  
`struct FCommonOutlinerNames`  
_L73-89_
- L75 _public member_ `static FName Indicator;`
- L76 _public member_ `static FName Pin;`
- L77 _public member_ `static FName Lock;`
- L78 _public member_ `static FName Deactivate;`
- L79 _public member_ `static FName Mute;`
- L80 _public member_ `static FName Solo;`
- L81 _public member_ `static FName Label;`
- L82 _public member_ `static FName Edit;`
- L83 _public member_ `static FName Add;`
- L84 _public member_ `static FName Nav;`
- L85 _public member_ `static FName KeyFrame;`
- L86 _public member_ `static FName ColorPicker;`
- L87 _public member_ `static FName TimeWarp;`
- L88 _public member_ `static FName Condition;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Sequencer` (scope `UE`)
- L53 _function_ `friend bool operator<(FOutlinerColumnPosition A, FOutlinerColumnPosition B)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerColumns/SoloOutlinerColumn.h` (Public)


#### class `UE::Sequencer::FSoloOutlinerColumn`  
`class FSoloOutlinerColumn : public FOutlinerColumnBase`  
_L13-22_
- inherits: `FOutlinerColumnBase`
- desc: A column for soloing/unsoloing tracks.
- L18 _public prototype_ `FSoloOutlinerColumn();`
- L20 _public prototype_ `bool IsItemCompatibleWithColumn(const FCreateOutlinerColumnParams& InParams) const override;`
- L21 _public prototype_ `TSharedPtr<SWidget> CreateColumnWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerIndicators/IOutlinerIndicatorBuilder.h` (Public)


#### class `UE::Sequencer::IOutlinerIndicatorBuilder`  
`class IOutlinerIndicatorBuilder : public TSharedFromThis<IOutlinerIndicatorBuilder>`  
_L20-39_
- inherits: `TSharedFromThis<IOutlinerIndicatorBuilder>`
- desc: Interface for building sequencer indicator outliner items.
- L26 _public prototype_ `virtual FName GetIndicatorName() const = 0;` — Returns the name of the indicator outliner item.
- L29 _public function_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const` — Gets whether or not this indicator outliner item is supported by a given Sequencer.
- L31 _public prototype_ `virtual bool IsItemCompatibleWithIndicator(const FCreateOutlinerColumnParams& InParams) const = 0;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateIndicatorWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow, const TSharedRef<IOutlinerColumn>& OutlinerColumn, const int32 NumCompatibleIndicators) = 0;`
- L37 _public prototype_ `virtual ~IOutlinerIndicatorBuilder() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerIndicators/OutlinerIndicatorBuilderBase.h` (Public)


#### class `UE::Sequencer::FOutlinerIndicatorBuilderBase`  
`class FOutlinerIndicatorBuilderBase : public IOutlinerIndicatorBuilder`  
_L10-23_
- inherits: `IOutlinerIndicatorBuilder`
- L15 _public function_ `FOutlinerIndicatorBuilderBase()`
- L21 _public function_ `bool IsItemCompatibleWithIndicator(const FCreateOutlinerColumnParams& InParams) const override`
- L22 _public function_ `TSharedPtr<SWidget> CreateIndicatorWidget(const FCreateOutlinerColumnParams& InParams, const TSharedRef<ISequencerTreeViewRow>& TreeViewRow, const TSharedRef<IOutlinerColumn>& OutlinerColumn, const int32 NumCompatibleIndicators) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerSpacer.h` (Public)


#### class `UE::Sequencer::FOutlinerSpacer`  
`class FOutlinerSpacer : public FViewModel , public FGeometryExtensionShim , public FOutlinerExtensionShim , public ISortableExtension , public IOutlinerDropTargetOutlinerExtension`  
_L28-68_
- inherits: `FViewModel,FGeometryExtensionShim,FOutlinerExtensionShim,ISortableExtension,IOutlinerDropTargetOutlinerExtension`
- L39 _public prototype_ `FOutlinerSpacer(float InDesiredSpacerHeight);`
- L40 _public prototype_ `~FOutlinerSpacer();`
- L42 _public function_ `void SetDesiredHeight(float InDesiredSpacerHeight)`
- L50 _public prototype_ `bool HasBackground() const override;` — ~ IOutlinerExtension
- L51 _public prototype_ `FName GetIdentifier() const override;`
- L52 _public prototype_ `FOutlinerSizing GetOutlinerSizing() const override;`
- L53 _public prototype_ `TSharedPtr<SWidget> CreateContextMenuWidget(const FCreateOutlinerContextMenuWidgetParams& InParams) override;`
- L56 _public prototype_ `virtual void SortChildren() override;` — ~ ISortableExtension
- L57 _public prototype_ `virtual FSortingKey GetSortingKey() const override;`
- L58 _public prototype_ `virtual void SetCustomOrder(int32 InCustomOrder) override;`
- L61 _public prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FViewModelPtr& TargetModel, const FDragDropEvent& DragDropEvent, EItemDropZone InItemDropZone) override;` — ~ IOutlinerDropTargetOutlinerExtension
- L62 _public prototype_ `void PerformDrop(const FViewModelPtr& TargetModel, const FDragDropEvent& DragDropEvent, EItemDropZone InItemDropZone) override;`
- L66 _private member_ `float DesiredSpacerHeight;`
- L67 _private member_ `int32 CustomOrder;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API SEQUENCERCORE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerViewModel.h` (Public)


#### class `UE::Sequencer::FOutlinerViewModel`  
`class FOutlinerViewModel : public FViewModel`  
_L28-120_
- inherits: `FViewModel`
- L35 _public member_ `FSimpleMulticastDelegate OnRefreshed;`
- L40 _public prototype_ `FOutlinerViewModel();` — Constructor
- L45 _public prototype_ `virtual ~FOutlinerViewModel() = default;` — Destructor
- L50 _public prototype_ `void Initialize(const FWeakViewModelPtr& InWeakRootDataModel);` — Initialize the view model with a given root model
- L55 _public prototype_ `TSharedPtr<FEditorViewModel> GetEditor() const;` — Get the editor view-model provided by the creation context
- L60 _public prototype_ `FViewModelPtr GetRootItem() const;` — Get the logical root item of the outliner hierarchy
- L65 _public prototype_ `TArrayView<const TWeakViewModelPtr<IOutlinerExtension>> GetTopLevelItems() const;` — Retrieve a flat list of the root items in this outliner model
- L70 _public prototype_ `void SetHoveredItem(TViewModelPtr<IOutlinerExtension> InHoveredModel);` — Set the single hovered model in the tree
- L75 _public prototype_ `TViewModelPtr<IOutlinerExtension> GetHoveredItem() const;` — Get the single hovered model in the tree, possibly nullptr
- L80 _public prototype_ `void UnpinAllNodes();` — Unpins any pinned nodes in this tree
- L85 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenuWidget();` — Called when the default context menu is opened
- L90 _public prototype_ `virtual TSharedRef<FDragDropOperation> InitiateDrag(TArray<TWeakViewModelPtr<IOutlinerExtension>>&& InDraggedModels);` — Initate a new drag operation from the specified dragged models.
- L95 _public prototype_ `virtual void RequestUpdate();` — Request that this tree be updated
- L102 _public function_ `bool IsHierarchyInvalidated() const` — Returns true if the root item hierarchy has been invalidated since the last call to GetTopLevelItems. Used by SOutlinerView::Refresh to decide between a full list rebuild (hierarchy changed) and an incremental refresh pass (state-only change such as mute/solo/deactivate).
- L106 _private prototype_ `void HandleDataHierarchyChanged();`
- L111 _private member_ `FWeakViewModelPtr WeakRootDataModel;` — The root data
- L113 _private member_ `TArray<TWeakViewModelPtr<IOutlinerExtension>> RootItems;` — A cached list of the root data's children, which are the outliner's root items
- L116 _private member_ `TWeakViewModelPtr<IOutlinerExtension> WeakHoveredItem;` — The currently mouse-hovered item
- L119 _private member_ `bool bRootItemsInvalidated;` — Whether root items should be re-evaluated

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SEQUENCERCORE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/OutlinerViewModelDragDropOp.h` (Public)


#### class `UE::Sequencer::FOutlinerViewModelDragDropOp`  
`class FOutlinerViewModelDragDropOp : public FGraphEditorDragDropAction , public IDragOperation`  
_L32-128_
- inherits: `FGraphEditorDragDropAction,IDragOperation`
- desc: A decorated drag drop operation object for dragging sequencer outliner items.
- L37 _public prototype_ `DRAG_DROP_OPERATOR_TYPE( FOutlinerViewModelDragDropOp, FGraphEditorDragDropAction ) static TSharedRef<FOutlinerViewModelDragDropOp> New(TArray<TWeakViewModelPtr<IOutlinerExtension>>&& InDraggedViewModels, FText InDefaultText, const FSlateBrush* InDefaultIcon);`
- L47 _protected function_ `FOutlinerViewModelDragDropOp()` — Protected construction for derived types. Generally constructed via a New() factory function to ensure that Construct is called
- L53 _public prototype_ `virtual void Construct() override;`
- L60 _public prototype_ `void ResetToDefaultToolTip();` — Reset the tooltip decorator back to its original state
- L65 _public prototype_ `TArrayView<const TWeakViewModelPtr<IOutlinerExtension>> GetDraggedViewModels() const;` — Gets the nodes which are currently being dragged.
- L71 _public prototype_ `bool ValidateParentChildDrop(const FViewModel& ProspectiveItem);` — Check whether dropping onto the specified outliner item would result in a parent being dropped onto its child @note: Sets this operation's CurrentHoverText to an error string on failure
- L80 _public prototype_ `virtual void GetTargetAndDropModel(const FViewModelPtr& CurrentViewModel, EItemDropZone InItemDropZone, FViewModelPtr& DropModel, FViewModelPtr& TargetModel) const;` — Based on the current view model being hovered, return the 'target' model and the 'drop model'. DropModel is the model we will call to execute the drop. TargetModel is only set if we're inserting before or after a child model of DropModel. We default to using the CurrentViewModel for the DropModel unless we've dragged above or below the CurrentViewModel, in which we default to the CurrentViewModel's parent for the DropModel and the TargetModel as the CurrentViewModel.
- L84 _private function_ `void AddSnapTime(FFrameNumber SnapTime) override`
- L87 _private function_ `void AddModel(TSharedPtr<FViewModel> Model) override`
- L93 _private function_ `FText GetDecoratorText() const` — Get the current decorator text
- L101 _private function_ `const FSlateBrush* GetDecoratorIcon() const` — Get the current decorator icon
- L111 _public member_ `FText CurrentHoverText;` — Current string to show as the decorator text
- L116 _public member_ `const FSlateBrush* CurrentIconBrush;` — Current icon to be displayed on the decorator
- L121 _protected member_ `TArray<TWeakViewModelPtr<IOutlinerExtension>> WeakViewModels;` — The nodes currently being dragged.
- L124 _protected member_ `FText DefaultHoverText;` — Default string to show as hover text
- L127 _protected member_ `const FSlateBrush* DefaultHoverIcon;` — Default icon to be displayed

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SEQUENCERCORE_API`
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/TrackAreaViewModel.h` (Public)


#### class `UE::Sequencer::FTrackAreaViewModel`  
`class FTrackAreaViewModel : public FViewModel`  
_L33-121_
- inherits: `FViewModel`
- L40 _public prototype_ `FTrackAreaViewModel();`
- L41 _public prototype_ `virtual ~FTrackAreaViewModel();`
- L45 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FViewSpaceEvent, const FGuid&, TSharedPtr<FTrackAreaViewSpace>) FViewSpaceEvent OnViewSpaceAdded;`
- L48 _public member_ `FViewSpaceEvent OnViewSpaceRemoved;`
- L51 _public prototype_ `TSharedPtr<FEditorViewModel> GetEditor() const;` — Get the editor view-model provided by the creation context
- L54 _public prototype_ `FTimeToPixel GetTimeToPixel(float TrackAreaWidth) const;` — Create a time/pixel converter for the given geometry
- L57 _public prototype_ `virtual FFrameRate GetTickResolution() const;` — Gets the current tick resolution of the editor
- L59 _public prototype_ `virtual TRange<double> GetViewRange() const;` — Gets the current view range of this track area
- L61 _public prototype_ `virtual void OnConstruct() override;`
- L64 _public prototype_ `TSharedPtr<ITrackAreaHotspot> GetHotspot() const;` — Get the current active hotspot
- L67 _public prototype_ `void SetHotspot(TSharedPtr<ITrackAreaHotspot> NewHotspot);` — Set the hotspot to something else
- L68 _public prototype_ `void AddHotspot(TSharedPtr<ITrackAreaHotspot> NewHotspot);`
- L69 _public prototype_ `void RemoveHotspot(FViewModelTypeID Type);`
- L70 _public prototype_ `void ClearHotspots();`
- L73 _public prototype_ `void LockHotspot(bool bIsLocked);` — Set whether the hotspot is locked and cannot be changed (ie when a menu is open)
- L76 _public prototype_ `FOnTrackAreaHotspotChanged& GetOnHotspotChangedDelegate();` — Get the callback that is fired when the current hotspot changes
- L78 _public prototype_ `void AddEditTool(TSharedPtr<ISequencerEditTool> InNewTool);`
- L81 _public function_ `ISequencerEditTool* GetEditTool() const` — Access the currently active track area edit tool
- L84 _public prototype_ `bool CanActivateEditTool(FName Identifier) const;` — Check whether it's possible to activate the specified tool
- L86 _public prototype_ `bool AttemptToActivateTool(FName Identifier);`
- L88 _public prototype_ `void LockEditTool();`
- L89 _public prototype_ `void UnlockEditTool();`
- L91 _public prototype_ `void AddViewSpace(const FGuid& ID, TSharedPtr<FTrackAreaViewSpace> ViewSpace);`
- L92 _public prototype_ `void RemoveViewSpace(const FGuid& ID);`
- L94 _public prototype_ `TSharedPtr<FTrackAreaViewSpace> FindViewSpace(const FGuid& InID) const;`
- L98 _protected prototype_ `void UpdateViewSpaces();`
- L102 _protected member_ `TMap<FGuid, TSharedPtr<FTrackAreaViewSpace>> ViewSpaces;`
- L105 _protected member_ `TArray<TSharedPtr<ITrackAreaHotspot>> HotspotStack;` — The current hotspot that can be set from anywhere to initiate drags
- L108 _protected member_ `FOnTrackAreaHotspotChanged OnHotspotChangedDelegate;` — The delegate that is fired when the current hotspot changes
- L111 _protected member_ `TArray<TSharedPtr<ISequencerEditTool>> EditTools;` — The currently active edit tools on this track area
- L114 _protected member_ `TSharedPtr<ISequencerEditTool> EditTool;` — The currently active edit tool on this track area
- L117 _protected member_ `bool bHotspotLocked;` — When true, prevents any other hotspot being activated
- L120 _protected member_ `bool bEditToolLocked;` — When true, prevents any other edit tool being activated by way of CanActivateEditTool always returning true

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SEQUENCERCORE_API`
- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Sequencer` (scope `UE`)
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackAreaHotspotChanged, TSharedPtr<ITrackAreaHotspot>);`
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackAreaHotspotChanged, TSharedPtr<ITrackAreaHotspot>);` (scope `UE::Sequencer`)
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FViewSpaceEvent, const FGuid&, TSharedPtr<FTrackAreaViewSpace>) FViewSpaceEvent OnViewSpaceAdded;`

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/TrackAreaViewSpace.h` (Public)


#### class `UE::Sequencer::FTrackAreaViewSpace`  
`class FTrackAreaViewSpace : public FViewModel , public INonLinearTimeTransform`  
_L14-27_
- inherits: `FViewModel,INonLinearTimeTransform`
- L22 _public prototype_ `FTrackAreaViewSpace();`
- L23 _public prototype_ `virtual ~FTrackAreaViewSpace();`
- L25 _public prototype_ `virtual double SourceToView(double Seconds) const override;`
- L26 _public prototype_ `virtual double ViewToSource(double Source) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/ViewDensity.h` (Public)


#### enum `UE::Sequencer::EViewDensity`  
`enum class EViewDensity`  
_L11-21_
- L14 _public enumerator_ `Variable` — Variable density where inner items are more condensed than top level or outer items
- L17 _public enumerator_ `Compact` — A compact view type with uniform heights
- L20 _public enumerator_ `Relaxed` — A relaxed view type with larger, uniform heights and additional information

#### struct `UE::Sequencer::FViewDensityInfo`  
`struct FViewDensityInfo`  
_L24-34_
- L26 _public prototype_ `FViewDensityInfo();`
- L27 _public prototype_ `FViewDensityInfo(EViewDensity InViewDensity);`
- L29 _public prototype_ `static TOptional<float> GetUniformHeight(EViewDensity Density);`
- L31 _public member_ `TOptional<float> UniformHeight;`
- L33 _public member_ `EViewDensity Density;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/ViewModel.h` (Public)


#### class `UE::Sequencer::FViewModel`  
`class FViewModel : public ICastable , public TSharedFromThis<FViewModel> , public FDynamicExtensionContainer`  
_L37-323_
- inherits: `ICastable,TSharedFromThis<FViewModel>,FDynamicExtensionContainer`
- desc: Base class for a sequencer data model. This might wrap an underlying UObject, or be a purely logical construct for the sequencer UI. WARNING: most of the casting and hierarchy related methods are not safe to call from a sub-class' constructor because they rely on shared-pointers to be available for `this`.
- L45 _public prototype_ `FViewModel();` — Builds a new data model
- L47 _public prototype_ `FViewModel(const FViewModel&) = delete;`
- L48 _public prototype_ `FViewModel& operator=(const FViewModel&) = delete;`
- L50 _public prototype_ `virtual ~FViewModel();`
- L58 _public function_ `template<typename T, typename... InArgTypes> T& AddDynamicExtension(InArgTypes&&... Args)` — Adds a dynamic extension to this data model
- L73 _public function_ `template<typename T, typename... InArgTypes> T& AddDynamicExtension(const TViewModelTypeID<T>& TypeID, InArgTypes&&... Args)` — Adds a dynamic extension to this data model
- L80 _public function_ `template<typename T> TViewModelPtr<T> CastThisShared()` — Casts this data model to an extension, or to a child class implementation
- L88 _public function_ `template<typename T> TViewModelPtr<const T> CastThisShared() const` — Casts this data model to an extension, or to a child class implementation
- L96 _public function_ `template<typename T> TSharedPtr<T> CastThisSharedChecked()` — Casts this data model to an extension, or to a child class implementation
- L104 _public function_ `template<typename T> TSharedPtr<const T> CastThisSharedChecked() const` — Casts this data model to an extension, or to a child class implementation
- L114 _public function_ `int32 GetHierarchicalDepth() const` — Gets the hierarchical depth of this data model, i.e. the number of levels to the top-most parent.
- L127 _public prototype_ `FViewModelPtr GetParent() const;` — Gets the parent data model
- L131 _public function_ `template<typename T> TViewModelPtr<T> CastParent() const` — Gets the parent data model
- L138 _public prototype_ `FViewModelPtr GetRoot() const;` — Returns the root model of the hierarchy, i.e. the parent model that has no parent
- L142 _public function_ `uint32 GetModelID() const` — Get this model's unique, non-persistent and non-deterministic ID
- L149 _public prototype_ `bool IsConstructed() const;`
- L151 _public prototype_ `TSharedPtr<FSharedViewModelData> GetSharedData() const;`
- L152 _public prototype_ `void SetSharedData(TSharedPtr<FSharedViewModelData> InSharedData);`
- L155 _public prototype_ `TOptional<FViewModelChildren> FindChildList(EViewModelListType InType);` — Retrieve the first child list that matches the specified type (if any)
- L157 _public prototype_ `FViewModelChildren GetChildList(EViewModelListType InType);` — Retrieve the first child list that matches the specified type. Asserts on failure.
- L160 _public prototype_ `bool HasChildren() const;` — Returns whether this model has any children in any of its child lists
- L163 _public prototype_ `TSharedPtr<FViewModel> GetPreviousSibling() const;` — Gets the next sibling of this data model in the children list it belongs to
- L166 _public prototype_ `TSharedPtr<FViewModel> GetNextSibling() const;` — Gets the next sibling of this data model in the children list it belongs to
- L171 _public prototype_ `void RemoveFromParent();` — Remove this model from its parent
- L174 _public prototype_ `void DiscardAllChildren();` — Unlinks the head of the children list
- L179 _public prototype_ `FViewModelListIterator GetChildren(EViewModelListType InFilter = EViewModelListType::Everything) const;` — Gets an iterator for the data model's default children list
- L183 _public function_ `template<typename T> TViewModelListIterator<T> GetChildrenOfType(EViewModelListType InFilter = EViewModelListType::Everything) const` — Gets children of a given type from the view-model's children lists, or the specified list
- L191 _public prototype_ `FParentFirstChildIterator GetDescendants(bool bIncludeThis = false, EViewModelListType InFilter = EViewModelListType::Everything) const;` — Gets all children and their descendants in the hierarchy below this data model.
- L196 _public prototype_ `void GetDescendantsOfType(FViewModelTypeID Type, TArray<TSharedPtr<FViewModel>>& OutChildren, EViewModelListType InFilter = EViewModelListType::Everything) const;` — Gets all children and descendants of a given type in the hierarchy below this data model.
- L202 _public function_ `template<typename T> TParentFirstChildIterator<T> GetDescendantsOfType(bool bIncludeThis = false, EViewModelListType InFilter = EViewModelListType::Everything) const` — Gets all children and descendants of a given type in the hierarchy below this data model.
- L211 _public function_ `template<typename T> TViewModelPtr<T> FindAncestorOfType(bool bIncludeThis = false) const` — Finds the first ancestor view model that implements the given type.
- L223 _public prototype_ `FViewModelPtr FindAncestorOfType(FViewModelTypeID Type, bool bIncludeThis = false) const;` — Finds a parent data model of a given type among the ancestry of this data model.
- L229 _public prototype_ `FViewModelPtr FindAncestorOfTypes(TArrayView<const FViewModelTypeID> Types, bool bIncludeThis = false) const;` — Finds a parent data model that supports all the given interface types among the ancestry of this data model.
- L234 _public prototype_ `FParentModelIterator GetAncestors(bool bIncludeThis = false) const;` — Iterates over the ancestry of this data model.
- L240 _public function_ `template<typename T> TParentModelIterator<T> GetAncestorsOfType(bool bIncludeThis = false) const` — Iterates over all ancestors of a given time along the ancestry of this data model.
- L250 _public function_ `bool IsAncestorOf(const TSharedPtr<FViewModel>& InDescendant, bool bIncludeThis = false) const` — Returns true if this view model is an ancestor of the given view model. @param InDescendant The potential descendant to check @param bIncludeThis If true, returns true when InDescendant.Get() == this
- L267 _protected prototype_ `void RegisterChildList(FViewModelListHead* InChildren);` — Chain a new children list to the existing children lists
- L270 _protected prototype_ `FViewModelChildren GetChildrenForList(FViewModelListHead* ListHead);` — Retrieve the children for the specified child list head
- L272 _protected prototype_ `void SetSharedDataFromConstructor(TSharedPtr<FSharedViewModelData> InSharedData);`
- L282 _private prototype_ `ESetParentResult SetParentOnly(const TSharedPtr<FViewModel>& NewParent, bool bReportChanges = true);`
- L285 _private function_ `virtual void OnConstruct()` — Called once for this model when it is added to a parent that has valid shared data
- L286 _private function_ `virtual void OnDestruct()`
- L298 _private member_ `TWeakPtr<FViewModel> WeakParent;` — Parent of this data model
- L300 _private member_ `TSharedPtr<FSharedViewModelData> SharedData;` — Data that is shared between all view-models in this hierarchy
- L302 _private member_ `FViewModelListLink Link;` — Link to siblings of this data model
- L304 _private member_ `FViewModelListHead* FirstChildListHead;` — List of children data models
- L314 _private member_ `int32 ActiveIterationCount;` — Counter that is non-zero when this model is actively being iterated that enables detection of invalid move operations during iteration Note: this is not set when the model is only a _prospective candidate_ for iteration (ie a sibling of an item that an iterator is currently looking at). Such models are safe to move due to children being linked lists
- L317 _private member_ `uint32 ModelID;` — Non-deterministic, non-persistent, serially increasing model ID unique to this instance
- L322 _private member_ `uint8 bNeedsConstruction : 1;` — Flag to track whether this view model needs to be constructed

#### enum `UE::Sequencer::FViewModel::ESetParentResult`  
`enum class ESetParentResult`  
_L276-281_
- L278 _public enumerator_ `AlreadySameParent`
- L279 _public enumerator_ `ChangedParent`
- L280 _public enumerator_ `ClearedParent`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SEQUENCERCORE_API`
- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/ViewModelHierarchy.h` (Public)


#### enum `UE::Sequencer::EViewModelListType`  
`enum class EViewModelListType : uint32`  
_L35-55_
- desc: Model list for defining logical groupings of children within a view model Custom list types can be registered using RegisterCustomModelListType
- L38 _public enumerator_ `Generic = 1u << 0` — Generic entry for unidentified or miscellaneous view models
- L40 _public enumerator_ `Outliner = 1u << 1` — Entry containing all outliner view models
- L42 _public enumerator_ `TrackArea = 1u << 2` — Entry containing all track area view models
- L44 _public enumerator_ `Custom = 1u << 4` — Custom entry start
- L47 _public enumerator_ `Recycled = 1u << 30` — Recycled models - not included in any iteration by default
- L50 _public enumerator_ `Last = 1u << 31` — Symbolic last and invalid entries - should only be used as an error condition
- L51 _public enumerator_ `Invalid = Last`
- L53 _public enumerator_ `Everything = (~0u) & ~(Recycled|Invalid)`
- L54 _public enumerator_ `Any = Everything`

#### struct `UE::Sequencer::FViewModelListLink`  
`struct FViewModelListLink`  
_L71-100_
- desc: Intrusive linked-list of data models W A R N I N G : DO NOT USE DIRECTLY UNLESS YOU KNOW WHAT YOU'RE DOING! This structure won't correctly update the data models' parent pointers, which can lead to problems. Use the methods on FViewModel. This link structure is mostly private anyway.
- L73 _public prototype_ `~FViewModelListLink();`
- L76 _public prototype_ `void Unlink();` — Detach only this link from its list
- L79 _public prototype_ `TSharedPtr<FViewModel> FindLastLink() const;` — Find ths last valid link in the list
- L88 _private prototype_ `void DetectLinkListCycle();` — Throws an assert if a cycle is detected
- L91 _private prototype_ `static void DetectLinkListCycle(TSharedPtr<FViewModel> StartAt);` — Throws an assert if a cycle is detected
- L94 _private prototype_ `static void LinkModelTo(TSharedPtr<FViewModel> Model, TSharedPtr<FViewModelListLink> ToLink);` — Unlinks the model from its siblings and insert it after the given chain link
- L97 _private member_ `TSharedPtr<FViewModel> Next;` — Next data model in the list
- L99 _private member_ `TWeakPtr<FViewModelListLink> WeakPrev;` — Previous item in the list

#### struct `UE::Sequencer::FViewModelListHead`  
`struct FViewModelListHead`  
_L117-151_
- desc: Defines the head of a linked list of view models. This list can actually be considered a linked list of linked-lists due to each FViewModelListHead object containing a NextList pointer which allows the segregation of logical groupings of view models. One example of this would be separating Outliner view models from track area view models. Keeping these as separate lists allows efficient filtering of these logical groupings during iteration. W A R N I N G : DO NOT USE DIRECTLY UNLESS YOU KNOW WHAT YOU'RE DOING! This structure won't correctly update the data models' parent pointers, which can lead to problems. Use the methods on FViewModel. This link structure is mostly private anyway.
- L119 _public function_ `FViewModelListHead(EViewModelListType InType) : Type(InType)`
- L124 _public prototype_ `FViewModelPtr GetHead() const;` — Returns the head model of this list
- L127 _public prototype_ `FViewModelPtr GetTail() const;` — Finds the last model of this list
- L130 _public prototype_ `FViewModelSubListIterator Iterate() const;` — Iterate the children held within this sub list
- L134 _public function_ `template<typename T> TViewModelSubListIterator<T> Iterate() const` — Iterate the children held within this sub list
- L143 _public prototype_ `TSharedPtr<FViewModel> ReliquishList();` — Move all the children in this list to a new list. @note: does not change parent relationships - NewHead must be within the same parent
- L146 _public member_ `FViewModelListLink HeadLink;` — Head of this list, where Next is the first item
- L148 _public member_ `FViewModelListHead* NextListHead = nullptr;` — Next list, for when data models have multiple lists of children
- L150 _public member_ `EViewModelListType Type;` — Identifier for this list head

#### struct `UE::Sequencer::FScopedViewModelListHead`  
`struct FScopedViewModelListHead`  
_L157-182_
- desc: Scoped object that adds a temporary child list to the specified model of the specified type. Primarily used during regeneration of children to temporarily introduce a 'Recycled' child list
- L160 _public prototype_ `FScopedViewModelListHead(const TSharedPtr<FViewModel>& InModel, EViewModelListType InType);` — Constructor that adds the list to the model
- L162 _public prototype_ `~FScopedViewModelListHead();` — Destructor that removes the list to the model
- L165 _public prototype_ `FScopedViewModelListHead(const FScopedViewModelListHead&) = delete;` — Non-copyable and non-moveable since a pointer to our ListHead member is added to our owner
- L166 _public prototype_ `FScopedViewModelListHead& operator=(const FScopedViewModelListHead&) = delete;`
- L168 _public prototype_ `FScopedViewModelListHead(FScopedViewModelListHead&&) = delete;`
- L169 _public prototype_ `FScopedViewModelListHead& operator=(FScopedViewModelListHead&&) = delete;`
- L174 _public prototype_ `FViewModelChildren GetChildren();` — Retrieve this child list
- L179 _private member_ `TSharedPtr<FViewModel> Model;` — The model that contains our child list
- L181 _private member_ `FViewModelListHead ListHead;` — List head whose pointer is added to Model's ChildLists

#### struct `UE::Sequencer::FViewModelChildren`  
`struct FViewModelChildren`  
_L184-274_
- L189 _public prototype_ `EViewModelListType GetType() const;` — Get the collective type of these children
- L194 _public prototype_ `FViewModelPtr GetParent() const;` — Get this children's parent
- L200 _public prototype_ `void AddChild(const TSharedPtr<FViewModel>& Child);` — Add a child from a different parent to these children @note: If the child is already under this parent, this function is a noop
- L206 _public prototype_ `void InsertChild(const TSharedPtr<FViewModel>& Child, const TSharedPtr<FViewModel>& PreviousSibling);` — Add a child from a different parent to these children to the specified previous sibling, or the head if nullptr @note: If the child is already the specified model's next sibling, this function is a noop
- L211 _public prototype_ `void MoveChildrenTo(const FViewModelChildren& OutDestination);` — Move all these children into the specified destination list, changing parent pointers if necessary
- L217 _public function_ `template<typename T, typename Callback> void MoveChildrenTo(const FViewModelChildren& OutDestination, Callback&& InCallback)` — Invoke a callback on these children, and move them all into the specified destination list, changing parent pointers if necessary
- L229 _public prototype_ `void Empty();` — Empty this specific sub-list, resetting all parent ptrs
- L234 _public prototype_ `FViewModelSubListIterator IterateSubList() const;` — Returns an iterator over this list
- L238 _public function_ `template<typename T> TViewModelSubListIterator<T> IterateSubList() const` — Returns an iterator over this list which will skip any item not of type T
- L244 _public function_ `bool IsEmpty() const` — Returns whether this list is empty
- L250 _public prototype_ `FViewModelPtr GetHead() const;` — Returns the head model of this list
- L253 _public prototype_ `FViewModelPtr GetTail() const;` — Finds the last model of this list
- L256 _public function_ `template<typename T> TViewModelPtr<T> FindFirstChildOfType() const`
- L270 _private prototype_ `FViewModelChildren(const TSharedPtr<FViewModel>& InOwner, FViewModelListHead* InListHead);`
- L272 _private member_ `TSharedPtr<FViewModel> Owner;`
- L273 _private member_ `FViewModelListHead* ListHead;`

#### class `UE::Sequencer::FViewModelHierarchyOperation`  
`class FViewModelHierarchyOperation`  
_L292-332_
- desc: Scoped utility class for batching change notifications on a view model hierarchy This class works by keeping track of models that have been changed in some way, along with their previous sibling and parent pointers before any change was made. With this information, when all FViewModelHierarchyOperation's have gone out of scope we can compare everything with its original pointers, and only dispatch change events in the case where they have actually changed. This enables reliable and accurate event processing in cases where large updates are made to a hierarchy with little or no meaningful change to the hierarchy. Within any given hierarhcy of FViewModelHierarchyOperation scopes, there is guaranteed to be a maximum of one event triggered for each changed node. This is achieved by tracking which models have already been handled during the event processing.
- L298 _public function_ `explicit FViewModelHierarchyOperation(const TSharedPtr<ViewModelType>& InAnyModel) : SharedData(InAnyModel->SharedData)` — `UE_DEPRECATED(5.5, "Please use the FSharedViewModelData overload by passing ->GetSharedData()")`
- L304 _public prototype_ `explicit FViewModelHierarchyOperation(const TSharedPtr<FSharedViewModelData>& InSharedData);`
- L305 _public prototype_ `~FViewModelHierarchyOperation();`
- L310 _public prototype_ `void PreHierarchicalChange(const TSharedPtr<FViewModel>& InChangedNode);` — Called before a change is made to the specified model's parent or previous sibling
- L314 _private prototype_ `void Construct();`
- L327 _private member_ `TSharedPtr<FSharedViewModelData> SharedData;` — Shared data that contains the bound event handlers for any model
- L329 _private member_ `TSharedPtr<FOperationAccumulationBuffer> AccumulationBuffer;` — Accumulation buffer shared between all active FViewModelHierarchyOperations
- L331 _private member_ `FViewModelHierarchyOperation* OldOperation;` — Pointer to the most recently active operation before this one existed

#### struct `UE::Sequencer::FViewModelHierarchyOperation::FCachedHierarchicalPosition`  
`struct FCachedHierarchicalPosition`  
_L316-320_
- L318 _public member_ `TWeakPtr<FViewModel> PreviousParent;`
- L319 _public member_ `TWeakPtr<FViewModel> PreviousSibling;`

#### struct `UE::Sequencer::FViewModelHierarchyOperation::FOperationAccumulationBuffer`  
`struct FOperationAccumulationBuffer`  
_L321-324_
- L323 _public member_ `TMap<TWeakPtr<FViewModel>, FCachedHierarchicalPosition> ChangedModels;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERCORE_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)
- L26 _macro_ `#define UE_SEQUENCER_DETECT_LINK_LIST_CYCLES 1`
- L28 _macro_ `#define UE_SEQUENCER_DETECT_LINK_LIST_CYCLES 0`
- L56 _prototype_ `ENUM_CLASS_FLAGS(EViewModelListType) EViewModelListType RegisterCustomModelListType();` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/ViewModelIterators.h` (Public)


#### struct `UE::Sequencer::FViewModelIterationState`  
`struct FViewModelIterationState`  
_L30-44_
- desc: Iterator state that wraps a view model and handles incrementing/decrementing its ActiveIterationCount while active
- L32 _public member_ `FViewModelPtr ViewModel;`
- L34 _public prototype_ `FViewModelIterationState() = default;`
- L35 _public prototype_ `FViewModelIterationState(FViewModelPtr&& InViewModel);`
- L37 _public prototype_ `FViewModelIterationState(const FViewModelIterationState&);`
- L38 _public prototype_ `FViewModelIterationState& operator=(const FViewModelIterationState&);`
- L40 _public prototype_ `FViewModelIterationState(FViewModelIterationState&&);`
- L41 _public prototype_ `FViewModelIterationState& operator=(FViewModelIterationState&&);`
- L43 _public prototype_ `~FViewModelIterationState();`

#### struct `UE::Sequencer::TPopulatableIteratorMixin`  
`template<typename DerivedType, typename EnumeratedType> struct TPopulatableIteratorMixin`  
_L52-127_
- L66 _public function_ `template<typename ContainerType> void Populate(ContainerType& OutContainer) const` — Populate the specified container with the remaining items in this iterator. ContainerType must have a .Add method that accepts the enumerated type. The state of this iterator remains unchanged. Example usage: TSet<FViewModelPtr> Set; It.Populate(Set);
- L84 _public function_ `template<template<typename T, typename ...Rest> class ContainerType> ContainerType<EnumeratedType> Populate() const` — Create a new container of the templated type and populate it with the remaining items in this iterator. ContainerType must have a .Add method that accepts the enumerated type. The state of this iterator remains unchanged. Example usage: TSet<TViewModelPtr<FTrackModel>> Tracks = ViewModel->GetDescendentsOfType<FTrackModel>().Populate<TSet>();
- L95 _public function_ `void ToArray(TArray<EnumeratedType>& OutArray) const` — Populate the specified array with the remaining items in this iterator The state of this iterator remains unchanged
- L104 _public function_ `TArray<EnumeratedType> ToArray() const` — Return the remaining items in this iterator as an array The state of this iterator remains unchanged
- L116 _public function_ `template<typename ValueType, typename ProjectionType> EnumeratedType FindBy(const ValueType& Value, ProjectionType Proj) const` — Linearly search through this iterator to find a predicate using a projection For example: UMovieSceneTrack* TrackToFind = ...; Model->GetChildrenOfType<FTrackModel>().FindBy(TrackToFind, &FTrackModel::GetTrack)

#### struct `UE::Sequencer::FViewModelSubListIterator`  
`struct FViewModelSubListIterator : TPopulatableIteratorMixin<FViewModelSubListIterator, FViewModelPtr>`  
_L132-168_
- inherits: `TPopulatableIteratorMixin<FViewModelSubListIterator,FViewModelPtr>`
- desc: Iterates all models that exist in a single list from the start model
- L134 _public prototype_ `FViewModelSubListIterator() = default;`
- L136 _public function_ `explicit FViewModelSubListIterator(const FViewModelListHead* List) : State(List ? List->GetHead() : nullptr)`
- L140 _public function_ `explicit FViewModelSubListIterator(TSharedPtr<FViewModel> InStart) : State(InStart)`
- L148 _public function_ `FORCEINLINE explicit operator bool() const` — Returns whether the iterator is pointing to a valid data model
- L151 _public function_ `FORCEINLINE FViewModel* operator->() const` — Dereferences the iterator to the pointed-to data model
- L153 _public function_ `FORCEINLINE const FViewModelPtr& operator*() const` — Dereferences the iterator to the pointed-to data model
- L156 _public function_ `FORCEINLINE void operator++()` — Moves to the next sibling of the pointed-to data model
- L159 _public function_ `FORCEINLINE FViewModelPtr GetCurrentItem() const` — Gets the pointed-to data model
- L161 _public function_ `FORCEINLINE FViewModelSubListIterator begin() const`
- L162 _public function_ `FORCEINLINE FViewModelSubListIterator end() const`
- L167 _private member_ `FViewModelIterationState State;` — The pointed-to data model

#### struct `UE::Sequencer::FViewModelListIterator`  
`struct FViewModelListIterator : TPopulatableIteratorMixin<FViewModelListIterator, FViewModelPtr>`  
_L173-237_
- inherits: `TPopulatableIteratorMixin<FViewModelListIterator,FViewModelPtr>`
- desc: Iterates all models contained in the specified list chain
- L175 _public function_ `FViewModelListIterator(EViewModelListType InFilter = EViewModelListType::Everything) : NextList(nullptr) , Filter(InFilter)`
- L180 _public function_ `explicit FViewModelListIterator(const TSharedPtr<FViewModel>& InModel, EViewModelListType InFilter = EViewModelListType::Everything) : NextList(InModel ? InModel->FirstChildListHead : nullptr) , Filter(InFilter)`
- L187 _public function_ `explicit FViewModelListIterator(const FViewModelListHead* InListHead, EViewModelListType InFilter = EViewModelListType::Everything) : NextList(InListHead) , Filter(InFilter)`
- L198 _public function_ `FORCEINLINE explicit operator bool() const`
- L199 _public function_ `FORCEINLINE FViewModel* operator->() const`
- L200 _public function_ `FORCEINLINE const FViewModelPtr& operator*() const`
- L201 _public function_ `FORCEINLINE FViewModelPtr GetCurrentItem() const`
- L203 _public function_ `void operator++()`
- L209 _public function_ `FORCEINLINE FViewModelListIterator begin() const`
- L210 _public function_ `FORCEINLINE FViewModelListIterator end() const`
- L214 _private function_ `void FindNextValidIterator()`
- L234 _private member_ `const FViewModelListHead* NextList;`
- L235 _private member_ `FViewModelSubListIterator ListIterator;`
- L236 _private member_ `EViewModelListType Filter;`

#### struct `UE::Sequencer::FViewModelVariantIterator`  
`struct FViewModelVariantIterator`  
_L242-345_
- desc: An iterator that can accomodate different types of data model lists, arrays, etc.
- L244 _public function_ `FViewModelVariantIterator() : Value(nullptr) , Data(nullptr) , ArrayProjection(nullptr) , ArrayIndex(0) , ArrayNum(0)`
- L253 _public function_ `FViewModelVariantIterator(const FViewModelListHead* DirectList) : Value(DirectList->GetHead()) , Data(DirectList) , ArrayProjection(nullptr) , ArrayIndex(0) , ArrayNum(0)`
- L263 _public function_ `template<typename T> FViewModelVariantIterator(const TArray<TWeakViewModelPtr<T>>* InWeakArrayView) : Data(InWeakArrayView->GetData()) , ArrayIndex(-1)`
- L273 _public function_ `template<typename T> FViewModelVariantIterator(const TArray<TViewModelPtr<T>>* InStrongArrayView) : Data(InStrongArrayView->GetData()) , ArrayIndex(-1)`
- L282 _public function_ `FORCEINLINE const FViewModelPtr& GetCurrentItem() const`
- L286 _public function_ `FORCEINLINE const FViewModelPtr& operator*() const`
- L290 _public function_ `FORCEINLINE FViewModel* operator->() const`
- L295 _public function_ `FORCEINLINE explicit operator bool() const`
- L299 _public function_ `FORCEINLINE void operator++()`
- L320 _public function_ `FORCEINLINE FViewModelVariantIterator begin() const`
- L321 _public function_ `FORCEINLINE FViewModelVariantIterator end() const`
- L326 _private function_ `template<typename T> static TSharedPtr<FViewModel> ProjectWeak(int32 Index, const void* InData)`
- L332 _private function_ `template<typename T> static TSharedPtr<FViewModel> ProjectStrong(int32 Index, const void* InData)`
- L338 _private typedef_ `using ProjectionType = TSharedPtr<FViewModel> (*)(int32 Index, const void*);`
- L340 _private member_ `FViewModelPtr Value;`
- L341 _private member_ `const void* Data;`
- L342 _private member_ `ProjectionType ArrayProjection;`
- L343 _private member_ `int32 ArrayIndex;`
- L344 _private member_ `int32 ArrayNum;`

#### struct `UE::Sequencer::FParentFirstChildIterator`  
`struct FParentFirstChildIterator`  
_L350-442_
- desc: A depth-first iterator into a hierarchy of data models. It iterates over *all* registered children lists of each model.
- L352 _public function_ `FParentFirstChildIterator(EViewModelListType InFilter = EViewModelListType::Everything) : Filter(InFilter) , DepthLimit(-1) , bIgnoreCurrentChildren(false)`
- L358 _public prototype_ `FParentFirstChildIterator(const TSharedPtr<FViewModel>& StartAt, bool bIncludeThis = false, EViewModelListType InFilter = EViewModelListType::Everything);`
- L360 _public function_ `FORCEINLINE int32 GetCurrentDepth() const`
- L364 _public function_ `FORCEINLINE const FViewModelPtr& GetCurrentItem() const`
- L368 _public function_ `FORCEINLINE const FViewModelPtr& operator*() const`
- L372 _public function_ `FORCEINLINE FViewModel* operator->() const`
- L376 _public function_ `FORCEINLINE explicit operator bool() const`
- L380 _public function_ `FORCEINLINE void operator++()`
- L393 _public function_ `FORCEINLINE void SetMaxDepth()`
- L397 _public function_ `FORCEINLINE void SetMaxDepth(int32 InDepthLimit)`
- L410 _public function_ `FORCEINLINE void IgnoreCurrentChildren()` — Request that this iterator ignore any and all children of the current model @note: Does not change the state of this iterator until it is incremented
- L415 _public function_ `FORCEINLINE FParentFirstChildIterator begin() const`
- L416 _public function_ `FORCEINLINE FParentFirstChildIterator end() const`
- L420 _protected prototype_ `void IterateToNext();`
- L422 _protected prototype_ `bool IterateToNextChild();`
- L424 _protected prototype_ `void IterateToNextSibling();`
- L429 _protected member_ `FViewModelPtr CurrentItem;` — The model currently pointed to by this iterator
- L432 _protected member_ `TArray<FViewModelListIterator, TInlineAllocator<8>> IterStack;` — Stack of parent's that have been visited in the current branch
- L435 _protected member_ `EViewModelListType Filter;` — List type filter to allow skipping of different child lists
- L438 _protected member_ `int32 DepthLimit;` — Maximum depth that this iterator is allowed to recurse to
- L441 _protected member_ `bool bIgnoreCurrentChildren;` — Flag that signals this iterator to skip all children of the current item and iterate directly to its sibling

#### struct `UE::Sequencer::FParentModelIterator`  
`struct FParentModelIterator`  
_L445-492_
- desc: Iterator going up the parent relationships towards the root
- L447 _public prototype_ `FParentModelIterator() = default;`
- L449 _public function_ `FParentModelIterator(TSharedPtr<FViewModel> StartAtChild, bool bIncludeThis = false)`
- L461 _public function_ `FORCEINLINE const FViewModelPtr& GetCurrentItem() const`
- L465 _public function_ `FORCEINLINE const FViewModelPtr& operator*() const`
- L469 _public function_ `FORCEINLINE FViewModel* operator->() const`
- L473 _public function_ `FORCEINLINE explicit operator bool() const`
- L477 _public function_ `FORCEINLINE void operator++()`
- L486 _public function_ `FORCEINLINE FParentModelIterator begin() const`
- L487 _public function_ `FORCEINLINE FParentModelIterator end() const`
- L491 _protected member_ `FViewModelPtr Node;`

#### struct `UE::Sequencer::TTypedIteratorBase`  
`template<typename T, typename IteratorType> struct TTypedIteratorBase : public IteratorType, public TPopulatableIteratorMixin<TTypedIteratorBase<T, IteratorType>, TViewModelPtr<T>>`  
_L499-542_
- inherits: `IteratorType,TPopulatableIteratorMixin<TTypedIteratorBase<T,IteratorType>,TViewModelPtr<T>>`
- desc: Utility class to wrap an untyped iterator (one that only returns FViewModel pointers) so that it can be used as a typed iterator.
- L502 _public function_ `template<typename ...ArgTypes> TTypedIteratorBase(ArgTypes&&... InArgs) : IteratorType(Forward<ArgTypes>(InArgs)...)`
- L508 _public function_ `FORCEINLINE T* operator->() const`
- L509 _public function_ `FORCEINLINE const TViewModelPtr<T>& operator*() const`
- L511 _public function_ `void operator++()`
- L517 _public function_ `FORCEINLINE TTypedIterator<T, IteratorType> begin() const`
- L518 _public function_ `FORCEINLINE TTypedIterator<T, IteratorType> end() const`
- L526 _protected function_ `void GetCastResultOrContinue()`
- L541 _protected member_ `TViewModelPtr<T> TypedValue;`

#### struct `UE::Sequencer::TTypedIterator`  
`template<typename T, typename IteratorType> struct TTypedIterator : TTypedIteratorBase<T, IteratorType>`  
_L545-551_
- inherits: `TTypedIteratorBase<T,IteratorType>`
- L548 _public function_ `template<typename ...ArgTypes> TTypedIterator(ArgTypes&&... InArgs) : TTypedIteratorBase<T, IteratorType>(Forward<ArgTypes>(InArgs)...)`
- L557 _public function_ `template<typename ...ArgTypes> TTypedIterator(ArgTypes&&... InArgs) : TTypedIteratorBase<T, FParentFirstChildIterator>(Forward<ArgTypes>(InArgs)...)`

#### struct `UE::Sequencer::TTypedIterator`  
`template<typename T> struct TTypedIterator<T, FParentFirstChildIterator> : TTypedIteratorBase<T, FParentFirstChildIterator>`  
_L554-560_
- inherits: `TTypedIteratorBase<T,FParentFirstChildIterator>`
- L548 _public function_ `template<typename ...ArgTypes> TTypedIterator(ArgTypes&&... InArgs) : TTypedIteratorBase<T, IteratorType>(Forward<ArgTypes>(InArgs)...)`
- L557 _public function_ `template<typename ...ArgTypes> TTypedIterator(ArgTypes&&... InArgs) : TTypedIteratorBase<T, FParentFirstChildIterator>(Forward<ArgTypes>(InArgs)...)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Sequencer` (scope `UE`)
- L145 _function_ `FORCEINLINE friend bool operator!=(const FViewModelSubListIterator& A, const FViewModelSubListIterator& B)` (scope `UE::Sequencer`) — Returns whether iterators point to the same data models
- L194 _function_ `FORCEINLINE friend bool operator!=(const FViewModelListIterator& A, const FViewModelListIterator& B)` (scope `UE::Sequencer`)
- L315 _function_ `FORCEINLINE friend bool operator!=(const FViewModelVariantIterator& A, const FViewModelVariantIterator& B)` (scope `UE::Sequencer`)
- L401 _function_ `FORCEINLINE friend bool operator!=(const FParentFirstChildIterator& A, const FParentFirstChildIterator& B)` (scope `UE::Sequencer`)
- L481 _function_ `FORCEINLINE friend bool operator!=(const FParentModelIterator& A, const FParentModelIterator& B)` (scope `UE::Sequencer`)
- L563 _typedef_ `template<typename T> using TParentModelIterator = TTypedIterator<T, FParentModelIterator>;` (scope `UE::Sequencer`)
- L565 _typedef_ `template<typename T> using TParentFirstChildIterator = TTypedIterator<T, FParentFirstChildIterator>;` (scope `UE::Sequencer`)
- L567 _typedef_ `template<typename T> using TViewModelListIterator = TTypedIterator<T, FViewModelListIterator>;` (scope `UE::Sequencer`)
- L569 _typedef_ `template<typename T> using TViewModelSubListIterator = TTypedIterator<T, FViewModelSubListIterator>;` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/ViewModels/VirtualTrackArea.h` (Public)


#### class `UE::Sequencer::FVirtualTrackArea`  
`class FVirtualTrackArea : public FTimeToPixel`  
_L25-62_
- inherits: `FTimeToPixel`
- desc: Structure used for handling the virtual space of the track area
- L30 _public prototype_ `FVirtualTrackArea(const FTrackAreaViewModel& InTrackArea, SOutlinerView& InTreeView, const FGeometry& InTrackAreaGeometry);` — Construction responsibility is delegated to SSequencer. See SSequencer::GetVirtualTrackArea
- L33 _public prototype_ `float PixelToVerticalOffset(float InPixel) const;` — Convert the specified pixel position into a virtual vertical offset from the absolute top of the tree
- L37 _public prototype_ `float VerticalOffsetToPixel(float InOffset) const;` — @note: Use with caution - not reliable where the specified offset is not on screen
- L40 _public prototype_ `FVector2D PhysicalToVirtual(FVector2D InPosition) const;` — Convert the specified physical point into a virtual point the absolute top of the tree
- L44 _public prototype_ `FVector2D VirtualToPhysical(FVector2D InPosition) const;` — @note: Use with caution - not reliable where the specified point is not on screen
- L47 _public prototype_ `FVector2D GetPhysicalSize() const;` — Get the physical size of the track area
- L50 _public prototype_ `TSharedPtr<FViewModel> HitTestNode(float InPhysicalPosition) const;` — Hit test at the specified physical position for a sequencer node
- L53 _public function_ `FGeometry CachedTrackAreaGeometry() const` — Cached track area geometry
- L58 _private member_ `SOutlinerView& TreeView;` — Reference to the sequencer tree
- L61 _private member_ `FGeometry TrackAreaGeometry;` — Cached physical geometry of the track area

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SEQUENCERCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/ISequencerTreeView.h` (Public)


#### class `UE::Sequencer::ISequencerTreeView`  
`class ISequencerTreeView : public STreeView<TWeakPtr<FViewModel>>`  
_L13-15_
- inherits: `STreeView<TWeakPtr<FViewModel>>`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/ITrackAreaHotspot.h` (Public)


#### struct `UE::Sequencer::ITrackAreaHotspot`  
`struct ITrackAreaHotspot : public ICastable`  
_L28-44_
- inherits: `ICastable`
- desc: A sequencer hotspot is used to identify specific areas on the sequencer track area
- L33 _public prototype_ `virtual ~ITrackAreaHotspot() = default;`
- L34 _public prototype_ `virtual void UpdateOnHover(FTrackAreaViewModel& InTrackArea) const = 0;`
- L35 _public function_ `virtual TOptional<FFrameNumber> GetTime() const`
- L36 _public function_ `virtual TOptional<FFrameTime> GetOffsetTime() const`
- L37 _public function_ `virtual TSharedPtr<ISequencerEditToolDragOperation> InitiateDrag(const FPointerEvent& MouseEvent)`
- L38 _public function_ `virtual bool PopulateContextMenu(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> MenuExtender, FFrameTime MouseDownTime)`
- L39 _public function_ `virtual FCursorReply GetCursor() const`
- L40 _public function_ `virtual const FSlateBrush* GetCursorDecorator(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const`
- L43 _public function_ `virtual int32 Priority() const` — Priority when multiple hotspots are present - highest wins

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SEQUENCERCORE_API`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)
- L47 _function_ `template<typename T> FORCEINLINE TSharedPtr<T> HotspotCast(const TSharedPtr<ITrackAreaHotspot>& InHotspot)` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/KeyDrawParams.h` (Public)


#### enum `EKeyConnectionStyle`  
`enum class EKeyConnectionStyle`  
_L10-16_
- L12 _public enumerator_ `None = 0`
- L13 _public enumerator_ `Dotted = 1 << 0`
- L14 _public enumerator_ `Dashed = 1 << 1`
- L15 _public enumerator_ `Solid = 1 << 2`

#### struct `FKeyDrawParams`  
`struct FKeyDrawParams`  
_L22-57_
- desc: Structure defining how a key should be drawn
- L24 _public function_ `FKeyDrawParams() : BorderBrush(nullptr), FillBrush(nullptr) , BorderTint(FLinearColor::White), FillTint(FLinearColor::White) , FillOffset(0.f, 0.f) , ConnectionStyle(EKeyConnectionStyle::None)`
- L41 _public member_ `const FSlateBrush* BorderBrush;` — Brush to use for drawing the key's border
- L44 _public member_ `const FSlateBrush* FillBrush;` — Brush to use for drawing the key's filled area
- L47 _public member_ `FLinearColor BorderTint;` — Tint to be used for the key's border
- L50 _public member_ `FLinearColor FillTint;` — Tint to be used for the key's filled area
- L53 _public member_ `FVector2D FillOffset;` — The amount to offset the fill brush from the keys center
- L56 _public member_ `EKeyConnectionStyle ConnectionStyle;` — Flags denoting how to draw connecting lines between this key and the next

#### Free symbols / members of external scopes

- L31 _function_ `friend bool operator==(const FKeyDrawParams& A, const FKeyDrawParams& B)`
- L35 _function_ `friend bool operator!=(const FKeyDrawParams& A, const FKeyDrawParams& B)`

### `Source/Editor/SequencerCore/Public/MVVM/Views/KeyRenderer.h` (Public)


#### enum `UE::Sequencer::EKeySelectionPreviewState`  
`enum class EKeySelectionPreviewState : uint8`  
_L29-34_
- desc: Key selection preview state - mirrored from FSequencer while selection concepts are ported to SequencerCore
- L31 _public enumerator_ `Undefined`
- L32 _public enumerator_ `Selected`
- L33 _public enumerator_ `NotSelected`

#### enum `UE::Sequencer::EKeyRendererStyle`  
`enum class EKeyRendererStyle : uint8`  
_L37-43_
- desc: The style to draw a key
- L39 _public enumerator_ `Circle`
- L40 _public enumerator_ `Diamond`
- L41 _public enumerator_ `Line`
- L42 _public enumerator_ `FrameBlock`

#### struct `UE::Sequencer::FKeyRendererPaintArgs`  
`struct FKeyRendererPaintArgs`  
_L48-97_
- desc: Paint arguments required for painting keys on a sequencer track
- L51 _public member_ `FSlateWindowElementList* DrawElements;` — Draw elements to paint onto
- L54 _public member_ `float KeyThrobValue = 0.f;` — The amount to throb selected keys by
- L57 _public member_ `float SectionThrobValue = 0.f;` — The amount to throb selected sections by
- L60 _public member_ `FVector2D ThrobAmount = FVector2D(12.f, 12.f);` — Fixed amount to throb newly created keys by
- L63 _public member_ `ESlateDrawEffect DrawEffects;` — Default draw effect
- L66 _public member_ `FLinearColor CurveColor = FLinearColor(0.8f, 0.8f, 0.f, 0.7f);` — Curve color to paint underlying curves with
- L69 _public member_ `FLinearColor KeyBarColor = FColor(160, 160, 160);` — Key bar color
- L72 _public member_ `EKeyRendererStyle KeyStyle = EKeyRendererStyle::Circle;` — Style used to draw each key
- L75 _public member_ `FVector2D KeyOffset = FVector2D::ZeroVector;` — Key draw offset
- L78 _public member_ `FLinearColor KeyFillColor = FLinearColor(.83f, .12f, .12f, 1.f);` — The fill color to use to display keys on the timeline
- L81 _public member_ `FLinearColor HoveredKeyFillColor = FLinearColor::White;` — The fill color to use to display hovered keys on the timeline
- L84 _public member_ `bool bBlendHoveredKeyColorWithBaseKeyColor = false;` — If true, hovered keys blend between their base fill color and HoveredKeyFillColor.
- L87 _public member_ `float HoveredKeyBlendFactor = .5f;` — Blend amount used when bBlendHoveredKeyColorWithBaseKeyColor is true.
- L90 _public member_ `FLinearColor KeySelectionFillColor = HoveredKeyFillColor;` — The fill color to use to display selected keys on the timeline
- L93 _public member_ `FLinearColor PartialKeyFillColor = FLinearColor::White;` — The fill color to use to display partial keys on the timeline
- L96 _public member_ `FLinearColor PartialKeySelectionFillColor = KeySelectionFillColor;` — The fill color to use to display selected partial keys on the timeline

#### enum `UE::Sequencer::EViewDependentCacheFlags`  
`enum class EViewDependentCacheFlags : uint8`  
_L100-111_
- desc: Flag enum signifying how the cache has changed since it was last generated
- L102 _public enumerator_ `None = 0` — The cache is still entirely valid, simply redraw the keys
- L103 _public enumerator_ `DataChanged = 1 << 0` — The underlying keyframes have changed - everything needs regenerating
- L104 _public enumerator_ `KeyStateChanged = 1 << 1` — The selection, hover or preview selection state of the keys has changed
- L105 _public enumerator_ `ViewChanged = 1 << 2` — The view range has changed - view dependent data needs regenerating, but some cache data may be preserved
- L106 _public enumerator_ `ViewZoomed = 1 << 3` — The view range has been zoomed - view dependent data needs regenerating, no key grouping can be preserved
- L108 _public enumerator_ `Empty = 1 << 4` — The view range is empty and there is nothing to show
- L110 _public enumerator_ `All = DataChanged | KeyStateChanged | ViewChanged | ViewZoomed`

#### class `UE::Sequencer::IKeyRendererInterface`  
`class IKeyRendererInterface`  
_L114-126_
- desc: Interface for defining selection states for keys
- L117 _public prototype_ `virtual ~IKeyRendererInterface()= default;`
- L119 _public prototype_ `virtual bool HasAnySelectedKeys() const = 0;`
- L120 _public prototype_ `virtual bool HasAnyPreviewSelectedKeys() const = 0;`
- L121 _public prototype_ `virtual bool HasAnyHoveredKeys() const = 0;`
- L123 _public prototype_ `virtual bool IsKeySelected(const TViewModelPtr<IKeyExtension>&, FKeyHandle) const = 0;`
- L124 _public prototype_ `virtual bool IsKeyHovered(const TViewModelPtr<IKeyExtension>&, FKeyHandle) const = 0;`
- L125 _public prototype_ `virtual EKeySelectionPreviewState GetPreviewSelectionState(const TViewModelPtr<IKeyExtension>&, FKeyHandle) const = 0;`

#### struct `UE::Sequencer::FKeyBatchParameters`  
`struct FKeyBatchParameters`  
_L128-173_
- L130 _public function_ `FKeyBatchParameters(const FTimeToPixel& InTimeToPixel) : ClientInterface(nullptr) , TimeToPixel(InTimeToPixel) , KeySizePx(12.f, 12.f) , ValidPlayRangeMin(TNumericLimits<int32>::Min()) , ValidPlayRangeMax(TNumericLimits<int32>::Max()) , CacheState(EViewDependentCacheFlags::None) , bShowCurve(false) , bShowKeyBars(true) , bCollapseChildren(false) , bUpdateViewIndependentData(true)`
- L144 _public member_ `IKeyRendererInterface* ClientInterface;` — Interface ptr for defining selection states for keys. Can be null if selection is not supported.
- L147 _public member_ `FTimeToPixel TimeToPixel;` — Time to pixel convertor
- L150 _public member_ `TRange<FFrameTime> VisibleRange;` — Visible range to clip rendering to
- L153 _public member_ `FVector2D KeySizePx;` — Screen-space size of keys in px
- L156 _public member_ `FFrameNumber ValidPlayRangeMin;` — Valid range for keys - keys outside this range are drawn de-saturated
- L157 _public member_ `FFrameNumber ValidPlayRangeMax;`
- L160 _public member_ `EViewDependentCacheFlags CacheState;` — Cache state that defines whether and how we need to update any cached view (in)dependent data
- L163 _public member_ `uint8 bShowCurve : 1;` — Whether to show a curve underneath the keys
- L166 _public member_ `uint8 bShowKeyBars : 1;` — Whether to show key bars connecting each key
- L169 _public member_ `uint8 bCollapseChildren : 1;` — Whether to collapse all children of the model into this key renderer as well, drawing all nested keys as groups within this renderer
- L172 _public member_ `uint8 bUpdateViewIndependentData : 1;` — Whether to poll key extensions for view-independent key data changes during this update.

#### struct `UE::Sequencer::FKeyRenderer`  
`struct FKeyRenderer`  
_L178-406_
- desc: Utility class for efficiently drawing large numbers of keys on a track lane.
- L223 _public prototype_ `void Initialize(const FViewModelPtr& InViewModel);` — Initialize this renderer with a generic model
- L228 _public prototype_ `void Initialize(const TSet<FWeakViewModelPtr>& InViewModels);` — Initialize this renderer with multiple generic models
- L233 _public prototype_ `void InitializeGrouped(const TSet<FWeakViewModelPtr>& InViewModels, TMap<uint32, uint32> InGroupIDsByModelID);` — Initialize this renderer with multiple generic models, evaluating partial keys independently per logical group
- L238 _public prototype_ `void Update(const FKeyBatchParameters& Params, const FGeometry& AllottedGeometry) const;` — Update any invalidated data required for drawing keys
- L243 _public prototype_ `int32 DrawCurve(const FKeyBatchParameters& Params, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, const FKeyRendererPaintArgs& Args, int32 LayerId) const;` — Draw this batch's curve
- L248 _public prototype_ `int32 Draw(const FKeyBatchParameters& Params, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, const FKeyRendererPaintArgs& Args, int32 LayerId) const;` — Draw this batch
- L253 _public prototype_ `void HitTestKeys(const FFrameTime& Time, TArray<FKeysForModel>& OutAllKeys, const bool bInLeftAlignCollision = false) const;` — Retrieve keys at the specified position
- L258 _public prototype_ `bool HitTestKeyBar(const FFrameTime& Time, FKeyBar& OutKeyBar) const;` — Retrieve keys at the specified position
- L263 _public prototype_ `bool HasCurve() const;` — Returns true if this renderer has a curve, false otherwise
- L367 _private prototype_ `void CacheKeyExtensions(const FKeyBatchParameters& Params) const;` — Cache all the key extensions from our model
- L373 _private prototype_ `EViewDependentCacheFlags UpdateViewIndependentData() const;` — Attempt to update data that is not dependent upon the current view @return EViewDependentCacheFlags::DataChanged if view-indipendent data was updated, EViewDependentCacheFlags::None otherwise
- L379 _private prototype_ `void UpdateViewDependentData(const FKeyBatchParameters& Params, const FGeometry& AllottedGeometry) const;` — Ensure that view-dependent data (such as which keys need drawing and how) is up to date
- L384 _private member_ `TSet<FWeakViewModelPtr> WeakViewModels;` — The models that we are drawing keys for
- L387 _private member_ `bool bEvaluatePartialKeysByGroup = false;` — Whether partial-key state should be evaluated independently per logical model group.
- L390 _private member_ `TMap<uint32, uint32> PartialKeyGroupIDsByModelID;` — Map from model ID to logical partial-key group ID.
- L393 _private member_ `mutable TArray<FCachedKeyDrawInformation, TInlineAllocator<1>> KeyDrawInfo;` — Array of cached draw info for each of the key areas that comprise this batch
- L396 _private member_ `mutable TArray<FKey> PrecomputedKeys;` — Computed final draw info for keys
- L399 _private member_ `mutable TArray<FCachedKeyBar> PrecomputedKeyBars;` — Computed final draw info for key bars
- L402 _private member_ `mutable TArray<TTuple<double, double>> PrecomputedCurve;` — Computed final draw curve info
- L405 _private member_ `mutable FFrameTime KeyWidthInFrames;` — Cached width of a key in frames

#### enum `UE::Sequencer::FKeyRenderer::EKeyRenderingFlags`  
`enum class EKeyRenderingFlags`  
_L181-193_
- desc: Flag enum signifying states for a particular key or group of keys
- L183 _public enumerator_ `None = 0`
- L184 _public enumerator_ `PartialKey = 1 << 0` — Indicates that this key comprises multiple keys of different types, or a partially keyed collapsed channel
- L185 _public enumerator_ `Selected = 1 << 1` — Only if.NumSelected == Key.TotalNumKeys
- L186 _public enumerator_ `PreviewSelected = 1 << 2` — Only if NumPreviewSelected == NumKeys
- L187 _public enumerator_ `PreviewNotSelected = 1 << 3` — Only if NumPreviewNotSelected == NumKeys
- L188 _public enumerator_ `AnySelected = 1 << 4` — If any are selected
- L189 _public enumerator_ `Hovered = 1 << 5` — Only if NumKeys == NumHovered
- L190 _public enumerator_ `Overlaps = 1 << 6` — If NumKeys > 1
- L191 _public enumerator_ `OutOfRange = 1 << 7` — If any of the keys fall outside of the valid range
- L192 _public enumerator_ `SubFrame = 1 << 8` — If the key is on a sub frame or a whole frame

#### enum `UE::Sequencer::FKeyRenderer::EKeyBarRenderingFlags`  
`enum class EKeyBarRenderingFlags`  
_L195-200_
- L197 _public enumerator_ `None = 0`
- L198 _public enumerator_ `Hovered = 1 << 0`
- L199 _public enumerator_ `OutOfRange = 1 << 1`

#### struct `UE::Sequencer::FKeyRenderer::FKeysForModel`  
`struct FKeysForModel`  
_L202-206_
- L204 _public member_ `FViewModelPtr Model;`
- L205 _public member_ `TArray<FKeyHandle> Keys;`

#### struct `UE::Sequencer::FKeyRenderer::FKeyBar`  
`struct FKeyBar`  
_L208-218_
- L210 _public member_ `TRange<FFrameTime> Range = TRange<FFrameTime>::Empty();`
- L211 _public member_ `TArray<FKeysForModel> LeadingKeys;`
- L212 _public member_ `TArray<FKeysForModel> TrailingKeys;`
- L214 _public function_ `bool IsValid() const`

#### struct `UE::Sequencer::FKeyRenderer::FCachedKeyDrawInformation`  
`struct FCachedKeyDrawInformation`  
_L268-331_
- desc: Container that caches the key positions for a given key area, along with those that overlap the current visible range
- L271 _public function_ `FCachedKeyDrawInformation(TViewModelPtr<IKeyExtension> KeyExtension, int32 InGroupIndex) : NextUnhandledIndex(0) , PreserveToIndex(0) , GroupIndex(InGroupIndex) , WeakKeyExtension(KeyExtension)` — Construction from the key area this represents
- L285 _public prototype_ `EViewDependentCacheFlags UpdateViewIndependentData();` — Attempt to update data that is not dependent upon the current view @return EViewDependentCacheFlags::DataChanged if view-indipendent data was updated, EViewDependentCacheFlags::None otherwise
- L293 _public prototype_ `void CacheViewDependentData(const FKeyBatchParameters& Params);` — Ensure that view-dependent data (such as which keys need drawing and how) is up to date @param Params    The batch parameters
- L298 _public function_ `int32 Num() const` — Return the size of this key draw information
- L306 _public member_ `int32 NextUnhandledIndex;` — Index into the array views for the next unhandled key
- L309 _public member_ `int32 PreserveToIndex;` — Index into the array views for the first index proceeding a preserved range (TimesInRange.Num() if not)
- L312 _public member_ `int32 GroupIndex;` — Logical group used to evaluate partial keys independently when multiple channel groups share one renderer.
- L315 _public member_ `TArrayView<const FFrameTime> FramesInRange;` — Cached array view retrieved from CachedKeys for the key frames that overlap the current time
- L317 _public member_ `TArrayView<const FKeyHandle> HandlesInRange;` — Cached array view retrieved from CachedKeys for the key handles that overlap the current time
- L319 _public member_ `TArray<FKeyDrawParams> DrawParams;` — Draw params for each of the keys visible on screen
- L321 _public member_ `FKeyDrawParams LeadingKeyParams;`
- L322 _public member_ `FKeyDrawParams TrailingKeyParams;`
- L324 _public member_ `FCachedKeys::FCachedKey LeadingKey;`
- L325 _public member_ `FCachedKeys::FCachedKey TrailingKey;`
- L328 _public member_ `TSharedPtr<FCachedKeys> CachedKeys;` — Construction from the key area this represents
- L330 _public member_ `TWeakViewModelPtr<IKeyExtension> WeakKeyExtension;`

#### struct `UE::Sequencer::FKeyRenderer::FKey`  
`struct FKey`  
_L335-348_
- desc: Cached parameters for drawing a single key
- L338 _public member_ `FKeyDrawParams Params;` — Paint parameters for this key
- L341 _public member_ `FFrameTime KeyTickStart, KeyTickEnd;` — The tick range that this key occupies (significant when this FKey represents multiple overlapping keys)
- L341 _public member_ `FFrameTime KeyTickStart, KeyTickEnd;` — The tick range that this key occupies (significant when this FKey represents multiple overlapping keys)
- L344 _public member_ `FFrameTime FinalKeyPosition;` — The time that this key should be drawn - represents the average time for overlapping keys
- L347 _public member_ `EKeyRenderingFlags Flags = EKeyRenderingFlags::None;` — Flags that specify how to draw this key

#### struct `UE::Sequencer::FKeyRenderer::FCachedKeyBar`  
`struct FCachedKeyBar`  
_L352-362_
- desc: Cached parameters for drawing a single key
- L355 _public member_ `FFrameTime StartTime, EndTime;` — The tick range that this key occupies (significant when this FKey represents multiple overlapping keys)
- L355 _public member_ `FFrameTime StartTime, EndTime;` — The tick range that this key occupies (significant when this FKey represents multiple overlapping keys)
- L358 _public member_ `EKeyBarRenderingFlags Flags = EKeyBarRenderingFlags::None;` — Flags that specify how to draw this key bar
- L361 _public member_ `EKeyConnectionStyle ConnectionStyle = EKeyConnectionStyle::None;` — Key bar connection style

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SEQUENCERCORE_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Sequencer` (scope `UE`)
- L408 _prototype_ `ENUM_CLASS_FLAGS(EViewDependentCacheFlags);` (scope `UE::Sequencer`)
- L409 _prototype_ `ENUM_CLASS_FLAGS(FKeyRenderer::EKeyRenderingFlags);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/OutlinerColumns/SColumnToggleWidget.h` (Public)


#### class `UE::Sequencer::SColumnToggleWidget`  
`class SColumnToggleWidget : public SImage`  
_L27-154_
- inherits: `SImage`
- desc: Outliner Column Widget for toggling active state with click and drag functionality. Adjusts image color and transparency based on active state and item hover. Displays an alternate icon when a child is active and the item is not. Column Toggle widgets have 4 States: Active, Inactive, Active Child, and Implicitly Active. Column Toggle widgets will change its brush based on its state.
- L32 _public function_ `SLATE_BEGIN_ARGS(SColumnToggleWidget)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TWeakPtr<IOutlinerColumn> InOutlinerColumn, const FCreateOutlinerColumnParams& InParams);`
- L43 _public function_ `virtual void OnToggleOperationComplete()` — Called when a drag or click ends and can be used to refresh the SequencerTree if necessary.
- L46 _public prototype_ `virtual FSlateColor GetImageColorAndOpacity() const;` — Get the color and opacity of the column toggle widget.
- L51 _protected function_ `virtual bool IsEnabled() const` — Returns whether the widget is enabled or not.
- L56 _protected prototype_ `virtual bool IsActive() const = 0;` — Returns whether or not the item is directly active or not.
- L59 _protected prototype_ `virtual void SetIsActive(const bool bInIsActive) = 0;` — Sets the active state of this item to the input value.
- L62 _protected prototype_ `virtual bool IsChildActive() const = 0;` — Returns true if a child of this item is active.
- L65 _protected function_ `virtual bool IsImplicitlyActive() const` — Returns true if this item is implicitly active, but not directly active
- L68 _protected prototype_ `virtual const FSlateBrush* GetActiveBrush() const = 0;` — Returns the brush to be used to represent a widget is active.
- L71 _protected function_ `virtual const FSlateBrush* GetInactiveBrush() const` — Returns the brush to be used to represent a widget is inactive. If Null, will use the active brush.
- L77 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;` — Get the image this widget displays.
- L82 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Start a new drag/drop operation for this widget.
- L85 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — If a matching column drag drop operation has entered this widget, set its item to the specified active state.
- L88 _protected prototype_ `FReply HandleClick();` — Handles left click-type inputs and potentially begins drag and drop operation.
- L91 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;` — Called when the mouse button is double clicked on this widget.
- L94 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when the mouse button is pressed down on this widget.
- L97 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;` — Called when this widget had captured the mouse, but that capture has been revoked for some reason.
- L100 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Process a mouse up message.
- L103 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Tick this widget to update its cached state
- L106 _protected prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when mouse enters the column widget.
- L109 _protected prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;` — Called when mouse leaves the column widget.
- L114 _protected prototype_ `void RefreshSequencerTree();` — Refreshes the Sequencer Tree. Can be used after toggle operation is complete if operation affects other items.
- L118 _protected member_ `TWeakPtr<FEditorViewModel> WeakEditor;` — Editor view-model for this view.
- L121 _protected member_ `TWeakViewModelPtr<IOutlinerExtension> WeakOutlinerExtension;` — Outliner item this widget accesses.
- L124 _protected member_ `TWeakPtr<IOutlinerColumn> WeakOutlinerColumn;` — Reference to column this widget is a member of.
- L129 _private member_ `const FSlateBrush* ActiveBrush = nullptr;` — Brushes for the various states of active widgets.
- L130 _private member_ `const FSlateBrush* InactiveBrush = nullptr;`
- L131 _private member_ `const FSlateBrush* ChildActiveBrush = nullptr;`
- L134 _private member_ `TUniquePtr<FScopedTransaction> UndoTransaction;` — Scoped undo transaction.
- L139 _protected member_ `uint32 ModelID;` — Cached model ID of the outliner widget this widget relates to
- L144 _private member_ `uint8 bIsMouseOverWidget : 1;` — Whether or not the mouse is directly over the widget.
- L147 _private member_ `uint8 bIsActive : 1;` — Whether this item is active.
- L150 _private member_ `uint8 bIsChildActive : 1;` — Whether or not a child of this item is active.
- L153 _private member_ `uint8 bIsImplicitlyActive : 1;` — Whether this item is active implicitly (as a result of some item's state, not this item explicitly).

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/OutlinerColumns/SOutlinerColumnButton.h` (Public)


#### class `UE::Sequencer::SOutlinerColumnButton`  
`class SOutlinerColumnButton : public SCompoundWidget`  
_L17-60_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SOutlinerColumnButton) : _Image(nullptr) , _UncheckedImage(nullptr) , _IsFocusable(false)`
- L27 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(const FSlateBrush*, UncheckedImage) SLATE_ATTRIBUTE(bool, IsRowHovered) SLATE_ATTRIBUTE(bool, IsChecked) SLATE_ARGUMENT(bool, IsFocusable) SLATE_EVENT(FOnClicked, OnClicked) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _private prototype_ `FSlateColor GetColorAndOpacity() const;`
- L49 _private prototype_ `const FSlateBrush* GetImage() const;`
- L51 _private prototype_ `FReply ToggleMenu();`
- L55 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L56 _private member_ `TAttribute<bool> IsRowHovered;`
- L57 _private member_ `TAttribute<bool> IsChecked;`
- L58 _private member_ `TAttribute<const FSlateBrush*> Image;`
- L59 _private member_ `TAttribute<const FSlateBrush*> UncheckedImage;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/SCompoundTrackLaneView.h` (Public)


#### class `UE::Sequencer::SCompoundTrackLaneView`  
`class SCompoundTrackLaneView : public SPanel`  
_L29-80_
- inherits: `SPanel`
- L34 _public function_ `SLATE_BEGIN_ARGS(SCompoundTrackLaneView)`
- L37 _public prototype_ `SCompoundTrackLaneView();`
- L38 _public prototype_ `~SCompoundTrackLaneView();`
- L41 _public function_ `void Construct(const FArguments& InArgs)` — `UE_DEPRECATED(5.6, "Please use the TSharedPtr<ITrackLaneWidgetSpace> overload")`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<ITrackLaneWidgetSpace> InTrackLaneWidgetSpace);`
- L48 _public prototype_ `void AddWeakWidget(TSharedPtr<ITrackLaneWidget> InWidget, TWeakPtr<STrackLane> InOwningLane);`
- L49 _public prototype_ `void AddStrongWidget(TSharedPtr<ITrackLaneWidget> InWidget, TWeakPtr<STrackLane> InOwningLane);`
- L52 _public prototype_ `void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;` — ~ SPanel Interface
- L53 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L54 _public prototype_ `FChildren* GetChildren() override;`
- L56 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L77 _private member_ `TPanelChildren<FSlot> Children;` — All the widgets in the panel
- L79 _private member_ `TWeakPtr<ITrackLaneWidgetSpace> WeakTrackLaneWidgetSpace;`

#### struct `UE::Sequencer::SCompoundTrackLaneView::FSlot`  
`struct FSlot : TSlotBase<FSlot>`  
_L60-74_
- inherits: `TSlotBase<FSlot>`
- L62 _public prototype_ `FSlot(TSharedPtr<ITrackLaneWidget> InInterface, TWeakPtr<STrackLane> InOwningLane);`
- L63 _public prototype_ `FSlot(TWeakPtr<ITrackLaneWidget> InWeakInterface, TWeakPtr<STrackLane> InOwningLane);`
- L65 _public function_ `TSharedPtr<ITrackLaneWidget> GetInterface() const`
- L70 _public member_ `TSharedPtr<ITrackLaneWidget> Interface;`
- L71 _public member_ `TWeakPtr<ITrackLaneWidget> WeakInterface;`
- L73 _public member_ `TWeakPtr<STrackLane> WeakOwningLane;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/SKeyNavigationButtons.h` (Public)


#### enum `UE::Sequencer::EKeyNavigationButtons`  
`enum class EKeyNavigationButtons : uint8`  
_L30-38_
- L32 _public enumerator_ `PreviousKey = 1 << 0`
- L33 _public enumerator_ `AddKey = 1 << 1`
- L34 _public enumerator_ `NextKey = 1 << 2`
- L36 _public enumerator_ `NavOnly = PreviousKey | NextKey`
- L37 _public enumerator_ `All = NavOnly | AddKey`

#### class `UE::Sequencer::SKeyNavigationButtons`  
`class SKeyNavigationButtons : public SCompoundWidget`  
_L44-83_
- inherits: `SCompoundWidget`
- desc: A widget for navigating between keys on a sequencer track
- L49 _public function_ `DECLARE_DELEGATE_OneParam(FOnSetTime, FFrameTime) DECLARE_DELEGATE_OneParam(FOnGetNavigatableTimes, TArray<FFrameNumber>&) DECLARE_DELEGATE_TwoParams(FOnAddKey, FFrameTime, TSharedPtr<FViewModel>) SLATE_BEGIN_ARGS(SKeyNavigationButtons) : _Buttons(EKeyNavigationButtons::All)`
- L55 _public prototype_ `SLATE_ARGUMENT(EKeyNavigationButtons, Buttons) SLATE_ARGUMENT(FText, PreviousKeyToolTip) SLATE_ARGUMENT(FText, NextKeyToolTip) SLATE_ATTRIBUTE(FFrameTime, Time) SLATE_EVENT(FOnSetTime, OnSetTime) SLATE_EVENT(FOnAddKey, OnAddKey) SLATE_ARGUMENT(FText, AddKeyToolTip) SLATE_EVENT(FOnGetNavigatableTimes, GetNavigatableTimes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FViewModel>& InModel);`
- L71 _public prototype_ `FReply OnPreviousKeyClicked();`
- L72 _public prototype_ `FReply OnNextKeyClicked();`
- L73 _public prototype_ `FReply OnAddKeyClicked();`
- L77 _protected member_ `TAttribute<FFrameTime> TimeAttribute;`
- L78 _protected member_ `FOnSetTime SetTimeEvent;`
- L79 _protected member_ `FOnAddKey AddKeyEvent;`
- L80 _protected member_ `FOnGetNavigatableTimes GetNavigatableTimesEvent;`
- L82 _protected member_ `TWeakPtr<FViewModel> WeakModel;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SEQUENCERCORE_API`
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Sequencer` (scope `UE`)
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetTime, FFrameTime) DECLARE_DELEGATE_OneParam(FOnGetNavigatableTimes, TArray<FFrameNumber>&) DECLARE_DELEGATE_TwoParams(FOnAddKey, FFrameTime, TSharedPtr<FViewModel>) SLATE_BEGIN_ARGS(SKeyNavigationButtons) : _Buttons(EKeyNavigationButtons::All) {} SLATE_ARGUMENT(EKeyNavigationButtons, Buttons) SLATE_ARGUMENT(FText, PreviousKeyToolTip) SLATE_ARGUMENT(FText, NextKeyToolTip) SLATE_ATTRIBUTE(FFrameTime, Time) SLATE_EVENT(FOnSetTime, OnSetTime) SLATE_EVENT(FOnAddKey, OnAddKey) SLATE_ARGUMENT(FText, AddKeyToolTip) SLATE_EVENT(FOnGetNavigatableTimes, GetNavigatableTimes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FViewModel>& InModel);`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetNavigatableTimes, TArray<FFrameNumber>&) DECLARE_DELEGATE_TwoParams(FOnAddKey, FFrameTime, TSharedPtr<FViewModel>) SLATE_BEGIN_ARGS(SKeyNavigationButtons) : _Buttons(EKeyNavigationButtons::All) {} SLATE_ARGUMENT(EKeyNavigationButtons, Buttons) SLATE_ARGUMENT(FText, PreviousKeyToolTip) SLATE_ARGUMENT(FText, NextKeyToolTip) SLATE_ATTRIBUTE(FFrameTime, Time) SLATE_EVENT(FOnSetTime, OnSetTime) SLATE_EVENT(FOnAddKey, OnAddKey) SLATE_ARGUMENT(FText, AddKeyToolTip) SLATE_EVENT(FOnGetNavigatableTimes, GetNavigatableTimes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FViewModel>& InModel);`
- L51 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAddKey, FFrameTime, TSharedPtr<FViewModel>) SLATE_BEGIN_ARGS(SKeyNavigationButtons) : _Buttons(EKeyNavigationButtons::All) {} SLATE_ARGUMENT(EKeyNavigationButtons, Buttons) SLATE_ARGUMENT(FText, PreviousKeyToolTip) SLATE_ARGUMENT(FText, NextKeyToolTip) SLATE_ATTRIBUTE(FFrameTime, Time) SLATE_EVENT(FOnSetTime, OnSetTime) SLATE_EVENT(FOnAddKey, OnAddKey) SLATE_ARGUMENT(FText, AddKeyToolTip) SLATE_EVENT(FOnGetNavigatableTimes, GetNavigatableTimes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FViewModel>& InModel);`

### `Source/Editor/SequencerCore/Public/MVVM/Views/SOutlinerItemViewBase.h` (Public)


#### enum `UE::Sequencer::EOutlinerItemViewBaseStyle`  
`enum class EOutlinerItemViewBaseStyle`  
_L37-42_
- L39 _public enumerator_ `Default`
- L40 _public enumerator_ `ContainerHeader`
- L41 _public enumerator_ `InsideContainer`

#### class `UE::Sequencer::SOutlinerItemViewBase`  
`class SOutlinerItemViewBase : public SCompoundWidget`  
_L47-178_
- inherits: `SCompoundWidget`
- desc: A widget for displaying a sequencer tree node in the animation outliner.
- L52 _public function_ `SLATE_BEGIN_ARGS(SOutlinerItemViewBase) : _ItemStyle(EOutlinerItemViewBaseStyle::Default), _IsReadOnly(false)`
- L53 _public prototype_ `SLATE_ARGUMENT(EOutlinerItemViewBaseStyle, ItemStyle) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_NAMED_SLOT(FArguments, CustomContent) SLATE_NAMED_SLOT(FArguments, AdditionalLabelContent) SLATE_NAMED_SLOT(FArguments, RightGutterContent) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TWeakViewModelPtr<IOutlinerExtension> InWeakExtension, TWeakPtr<FEditorViewModel> InWeakEditor, const TSharedRef<ISequencerTreeViewRow>& InTableRow );`
- L71 _protected prototype_ `virtual FText GetLabel() const;` — @return The color used to draw the display name.
- L76 _protected prototype_ `virtual FSlateColor GetLabelColor() const;` — @return The color used to draw the display name.
- L81 _protected prototype_ `virtual FSlateFontInfo GetLabelFont() const;` — @return The font used to draw the display name.
- L86 _protected prototype_ `virtual FText GetLabelToolTipText() const;` — @return The text displayed for the tool tip for the diplay name label.
- L91 _protected prototype_ `bool IsRenameValid(const FText& NewName, FText& OutErrorMessage) const;` — Returns whether a requested rename is valid.
- L96 _protected prototype_ `void OnNodeLabelTextCommitted(const FText& NewLabel, ETextCommit::Type CommitType);` — Called when a new name has been committed in the text box.
- L101 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const;` — @return The icon to use on the view
- L106 _protected prototype_ `virtual FSlateColor GetIconTint() const;` — @return A color tint to apply to the icon
- L111 _protected prototype_ `virtual const FSlateBrush* GetIconOverlayBrush() const;` — @return The icon overlay (eg a spawnable badge) to use on the view
- L116 _protected prototype_ `virtual FText GetIconToolTipText() const;` — @return Tooltip text to apply to the icon
- L121 _protected prototype_ `virtual bool IsNodeLabelReadOnly() const;` — Callback for checking whether the node label can be edited.
- L126 _protected prototype_ `virtual bool IsDimmed() const;` — Whether this node should be drawn dimmed or not
- L128 _protected prototype_ `FOptionalSize GetHeight() const;`
- L134 _private prototype_ `FSlateColor GetForegroundBasedOnSelection() const;`
- L139 _private prototype_ `const FSlateBrush* GetNodeBorderImage() const;` — @return The border image to show in the tree node.
- L144 _private prototype_ `FSlateColor GetNodeInnerBackgroundTint() const;` — @return The tint to apply to the border image for the inner portion of the node.
- L149 _private prototype_ `EVisibility GetExpanderVisibility() const;` — @return The expander visibility of this node.
- L154 _protected member_ `TWeakViewModelPtr<IOutlinerExtension> WeakOutlinerExtension;` — Weak extension pointer for the outliner (mandatory, non-owning reference)
- L156 _protected member_ `TWeakViewModelPtr<IRenameableExtension> WeakRenameExtension;` — Weak extension pointer for a rename extension (optional, non-owning reference)
- L159 _protected member_ `TWeakPtr<FEditorViewModel> WeakEditor;` — Editor view-model for this view.
- L161 _protected member_ `TAttribute<bool> IsReadOnlyAttribute;`
- L162 _protected member_ `TAttribute<bool> IsRowSelectedAttribute;`
- L165 _protected member_ `const FSlateBrush* ExpandedBackgroundBrush;` — Default background brush for this node when expanded
- L168 _protected member_ `const FSlateBrush* CollapsedBackgroundBrush;` — Default background brush for this node when collapsed
- L171 _protected member_ `const FSlateBrush* InnerBackgroundBrush;` — The brush to use when drawing the background for the inner portion of the node.
- L174 _protected member_ `const FTableRowStyle* TableRowStyle;` — The table row style used for nodes in the tree. This is required as we don't actually use the tree for selection.
- L177 _protected member_ `EOutlinerItemViewBaseStyle ItemStyle;` — Style enumeration

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SEQUENCERCORE_API`
- L27 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/SOutlinerView.h` (Public)


#### enum `UE::Sequencer::ETreeRecursion`  
`enum class ETreeRecursion`  
_L63-66_
- L65 _public enumerator_ `Recursive`
- L65 _public enumerator_ `Recursive`

#### class `UE::Sequencer::SOutlinerView`  
`class SOutlinerView : public STreeView<TWeakViewModelPtr<IOutlinerExtension>>`  
_L70-288_
- inherits: `STreeView<TWeakViewModelPtr<IOutlinerExtension>>`
- desc: The tree view used in the sequencer
- L75 _public function_ `SLATE_BEGIN_ARGS(SOutlinerView)`
- L77 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FSequencerCoreSelection>, Selection ) SLATE_ARGUMENT( TSharedPtr<SScrollBar>, ExternalScrollbar ) SLATE_END_ARGS() static const FName TrackNameColumn;`
- L85 _public prototype_ `SOutlinerView();`
- L86 _public prototype_ `~SOutlinerView();`
- L89 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FOutlinerViewModel> InWeakOutliner, const TSharedRef<STrackAreaView>& InTrackArea);` — Construct this widget
- L90 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime );`
- L91 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L93 _public prototype_ `TSharedPtr<FOutlinerViewModel> GetOutlinerModel() const;`
- L96 _public function_ `int32 GetNumRootNodes() const` — @return the number of root nodes this tree contains
- L98 _public prototype_ `float GetVirtualTop() const;`
- L100 _public prototype_ `void GetVisibleItems(TArray<TViewModelPtr<IOutlinerExtension>>& OutItems) const;`
- L102 _public prototype_ `void ForceSetSelectedItems(const TSet<TWeakViewModelPtr<IOutlinerExtension>>& InItems);`
- L107 _public prototype_ `TViewModelPtr<IOutlinerExtension> HitTestNode(float InPhysical) const;` — Get the tree item model at the specified physical vertical position
- L110 _public prototype_ `float PhysicalToVirtual(float InPhysical) const;` — Convert the specified physical vertical position into an absolute virtual position, ignoring expanded states
- L115 _public prototype_ `float VirtualToPhysical(float InVirtual) const;` — Convert the specified absolute virtual position into a physical position in the tree. @note: Will not work reliably for virtual positions that are outside of the physical space
- L117 _public prototype_ `void ReportChildRowGeometry(const TViewModelPtr<IOutlinerExtension>& InNode, const FGeometry& InGeometry);`
- L122 _public prototype_ `void Refresh();` — Refresh this tree as a result of the underlying tree data changing
- L125 _public prototype_ `void ToggleExpandCollapseNodes(ETreeRecursion Recursion = ETreeRecursion::Recursive, bool bExpandAll = false, bool bCollapseAll = false);` — Expand or collapse nodes
- L128 _public prototype_ `void ScrollByDelta(float DeltaInSlateUnits);` — Scroll this tree view by the specified number of slate units
- L130 _public prototype_ `bool IsColumnVisible(const FName& InName) const;`
- L133 _public prototype_ `void ExpandCollapseNode(TViewModelPtr<IOutlinerExtension> InDataModel, bool bExpansionState, ETreeRecursion Recursion);` — Set the item's expansion state, including all of its children
- L138 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TWeakViewModelPtr<IOutlinerExtension> InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for a particular node
- L140 _protected prototype_ `void CreateTrackLanesForRow(TSharedRef<SOutlinerViewRow> InRow, TViewModelPtr<IOutlinerExtension> InDataModel);`
- L141 _protected prototype_ `TSharedPtr<STrackLane> FindOrCreateParentLane(TViewModelPtr<IOutlinerExtension> InDataModel);`
- L144 _protected prototype_ `void OnGetChildren(TWeakViewModelPtr<IOutlinerExtension> InParent, TArray<TWeakViewModelPtr<IOutlinerExtension>>& OutChildren) const;` — Gather the children from the specified node
- L147 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(TViewModelPtr<IOutlinerExtension> InDataModel, const FName& ColumnId, const TSharedRef<SOutlinerViewRow>& Row) const;` — Generate a widget for the specified Node and Column
- L150 _protected prototype_ `void OnExpansionChanged(TWeakViewModelPtr<IOutlinerExtension> InItem, bool bIsExpanded);` — Called when a node has been expanded or collapsed
- L153 _protected prototype_ `virtual void Private_UpdateParentHighlights() override;` — Tree selection methods which must be overriden to maintain selection consistency with the rest of sequencer.
- L154 _protected prototype_ `virtual void Private_SetItemSelection( TWeakViewModelPtr<IOutlinerExtension> TheItem, bool bShouldBeSelected, bool bWasUserDirected = false ) override;`
- L155 _protected prototype_ `virtual void Private_ClearSelection() override;`
- L156 _protected prototype_ `virtual void Private_SelectRangeFromCurrentTo( TWeakViewModelPtr<IOutlinerExtension> InRangeSelectionEnd ) override;`
- L157 _protected prototype_ `virtual void Private_SignalSelectionChanged( ESelectInfo::Type SelectInfo ) override;`
- L159 _protected prototype_ `virtual void OnRightMouseButtonDown(const FPointerEvent& MouseEvent) override;`
- L160 _protected prototype_ `virtual void OnRightMouseButtonUp(const FPointerEvent& MouseEvent) override;`
- L162 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L163 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L167 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L172 _protected prototype_ `void SetItemSelection();` — Private, unimplemented overloaded name for SetItemSelection to prevent external calls - use ForceSetItemSelection instead
- L174 _protected prototype_ `void ClearSelection();` — Private, unimplemented overloaded name for SetItemSelection to prevent external calls - use ForceSetItemSelection instead
- L176 _protected prototype_ `void UpdateViewSelectionFromModel();`
- L177 _protected prototype_ `void UpdateModelSelectionFromView();`
- L179 _protected prototype_ `void HandleTableViewScrolled(double InScrollOffset);`
- L180 _protected prototype_ `void UpdatePhysicalGeometry(bool bIsRefresh);`
- L183 _protected prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Handles the context menu opening when right clicking on the tree view.
- L185 _protected prototype_ `void SetItemExpansionRecursive(TWeakViewModelPtr<IOutlinerExtension> InItem, bool bIsExpanded);`
- L207 _public function_ `const TArray<FCachedGeometry>& GetAllVisibleNodes() const` — Access all the physical nodes currently visible on the sequencer
- L210 _public prototype_ `void AddPinnedTreeView(TSharedPtr<SOutlinerView> PinnedTreeView);` — Add a SOutlinerView object that should be modified or updated when this Treeview is updated
- L213 _public function_ `void SetPrimaryTreeView(TSharedPtr<SOutlinerView> InPrimaryTreeView)` — Set a SOutlinerView object this Treeview is pinned to, for operations that should happen on the primary
- L216 _public function_ `void SetShowPinned(bool bShowPinned)` — Set whether this TreeView should show only pinned nodes or only non-pinned nodes
- L219 _public prototype_ `void SetOutlinerColumns(const TArray<TSharedPtr<IOutlinerColumn>>& InOutlinerColumns);` — Updates the list of visible outliner columns and regenerates columns in the outliner view
- L224 _protected member_ `TArray<FCachedGeometry> PhysicalNodes;` — Linear, sorted array of nodes that we currently have generated widgets for
- L226 _protected prototype_ `int32 CreateOutlinerColumnsForGroup(int32 ColumnIndex, EOutlinerColumnGroup Group);`
- L229 _protected prototype_ `void UpdateOutlinerColumns();` — Populate the map of column definitions, and add relevant columns to the header row. Must be called when outliner columns change
- L232 _protected prototype_ `void InsertSeparatorColumn(int32 InsertIndex, int32 SeparatorID);` — Insert a separator column at the specified column index, with a unique identifier
- L234 _protected prototype_ `FReply OnDragRow(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, TSharedRef<SOutlinerViewRow> InRow);`
- L236 _protected prototype_ `FString OnItemToString_Debug(TWeakViewModelPtr<IOutlinerExtension> InWeakModel);`
- L240 _protected typedef_ `using FColumnGenerator = TFunction<TSharedPtr<SWidget>(const FCreateOutlinerColumnParams& Params, const TSharedRef<SOutlinerViewRow>&)>;`
- L243 _protected member_ `TSharedPtr<SHeaderRow> HeaderRow;` — The tree view's header row (hidden)
- L246 _protected member_ `TSharedPtr<FOutlinerHeaderRowWidgetMetaData> ColumnMetaData;` — MetaData pertaining to each column within HeaderRow
- L249 _protected member_ `TWeakPtr<FOutlinerViewModel> WeakOutliner;` — The outliner view model
- L252 _protected member_ `TArray<TWeakViewModelPtr<IOutlinerExtension>> RootNodes;` — Cached copy of the root nodes from the tree data
- L255 _protected member_ `TMap<FName, FColumnGenerator> ColumnGenerators;` — Column definitions for each of the columns in the tree view
- L257 _protected member_ `TSharedPtr<FSequencerCoreSelection> Selection;`
- L258 _protected member_ `TUniquePtr<FSelectionEventSuppressor> DelayedEventSuppressor;`
- L261 _protected member_ `TSharedPtr<STrackAreaView> TrackArea;` — Strong pointer to the track area so we can generate track lanes as we need them
- L264 _protected member_ `TArray<TSharedPtr<SOutlinerView>> PinnedTreeViews;` — SOutlinerView objects that should be modified or updated when this Treeview is updated
- L267 _protected member_ `TWeakPtr<SOutlinerView> PrimaryTreeView;` — The SOutlinerView object this SOutlinerView is pinned to, or nullptr if not pinned
- L270 _protected member_ `TArray<TSharedPtr<IOutlinerColumn>> OutlinerColumns;` — Visible Outliner columns to display in the outliner view
- L272 _protected member_ `float VirtualTop;`
- L275 _protected member_ `bool bUpdatingTreeSelection;` — When true, the tree selection is being updated from a change in the sequencer selection.
- L278 _protected member_ `bool bRightMouseButtonDown;` — Right mouse button is down, don't update sequencer selection.
- L281 _protected member_ `bool bShowPinnedNodes;` — Whether this tree is for pinned nodes or non-pinned nodes
- L284 _protected member_ `bool bSelectionChangesPending;` — Whether we have pending selection changes to broadcast
- L287 _protected member_ `bool bRefreshPhysicalGeometry;` — Whether physical geometry information should be recomputed

#### struct `UE::Sequencer::SOutlinerView::FCachedGeometry`  
`struct FCachedGeometry`  
_L190-204_
- desc: Structure used to cache physical geometry for a particular node
- L192 _public function_ `FCachedGeometry(TWeakViewModelPtr<IOutlinerExtension> InWeakItem, float InPhysicalTop, float InPhysicalHeight, float InVirtualTop, float InVirtualHeight, float InVirtualNestedHeight) : WeakItem(MoveTemp(InWeakItem)) , PhysicalTop(InPhysicalTop), PhysicalHeight(InPhysicalHeight) , VirtualTop(InVirtualTop), VirtualHeight(InVirtualHeight), VirtualNestedHeight(InVirtualNestedHeight)`
- L201 _public member_ `TWeakViewModelPtr<IOutlinerExtension> WeakItem;`
- L202 _public member_ `float PhysicalTop, PhysicalHeight;`
- L202 _public member_ `float PhysicalTop, PhysicalHeight;`
- L203 _public member_ `float VirtualTop, VirtualHeight, VirtualNestedHeight;`
- L203 _public member_ `float VirtualTop, VirtualHeight, VirtualNestedHeight;`
- L203 _public member_ `float VirtualTop, VirtualHeight, VirtualNestedHeight;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API SEQUENCERCORE_API`
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace Sequencer` (scope `UE`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/SOutlinerViewRow.h` (Public)


#### class `UE::Sequencer::SOutlinerViewRow`  
`class SOutlinerViewRow : public ISequencerTreeViewRow`  
_L19-123_
- inherits: `ISequencerTreeViewRow`
- desc: Widget that represents a row in the sequencer's tree control.
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<SWidget>, FOnGenerateWidgetForColumn, TViewModelPtr<IOutlinerExtension>, const FName&, const TSharedRef<SOutlinerViewRow>&);`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FDetectDrag, const FGeometry&, const FPointerEvent&, TSharedRef<SOutlinerViewRow>);`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsColumnVisible, const FName&);`
- L27 _public function_ `SLATE_BEGIN_ARGS(SOutlinerViewRow)`
- L30 _public prototype_ `SLATE_EVENT(FIsColumnVisible, OnGetColumnVisibility) SLATE_EVENT(FOnGenerateWidgetForColumn, OnGenerateWidgetForColumn) SLATE_EVENT(FDetectDrag, OnDetectDrag) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TWeakViewModelPtr<IOutlinerExtension> InDataModel);` — Delegate to invoke to retrieve a specific column's visibility
- L44 _public prototype_ `~SOutlinerViewRow();` — Destroy this widget
- L47 _public prototype_ `TViewModelPtr<IOutlinerExtension> GetDataModel() const;` — Get the model to which this row relates
- L55 _public prototype_ `TSharedPtr<STrackLane> GetTrackLane(bool bOnlyOwnTrackLane = false) const;` — Gets the track lane we relate to @param bOnlyOwnTrackLane  Whether to return nullptr if our referenced track lane wasn't created by our own outliner item view-model @return The track lane for this row
- L62 _public prototype_ `void SetTrackLane(const TSharedPtr<STrackLane>& InTrackLane);` — Adds a reference to track lane, either because: - It is a parent row's track lane that we want to be kept alive when the parent row disappears out of view, or - It is a track lane that was created by our outliner view-model
- L65 _public prototype_ `bool IsSelectable() const;` — Whether the underlying data model is selectable
- L67 _public prototype_ `virtual const FSlateBrush* GetBorder() const override;`
- L69 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L71 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L73 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L75 _public prototype_ `virtual int32 OnPaintDropIndicator(EItemDropZone InItemDropZone, const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L77 _public prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L79 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L81 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L83 _public prototype_ `virtual bool IsColumnVisible(const FName& InColumnName) const override;`
- L86 _public prototype_ `FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;` — Called whenever a drag is detected by the tree view.
- L89 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TWeakViewModelPtr<IOutlinerExtension> InDataModel);` — Called to determine whether a current drag operation is valid for this row.
- L92 _public prototype_ `FReply OnAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TWeakViewModelPtr<IOutlinerExtension> InDataModel);` — Called to complete a drag and drop onto this drop.
- L96 _protected prototype_ `TSharedPtr<SWidget> GenerateWidgetForColumn(const FName& ColumnId);`
- L98 _protected prototype_ `FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L108 _protected member_ `TSharedPtr<STrackLane> TrackLane;` — Cached reference to a track lane that we relate to. Depending on the situation, this is either the actual track lane originally created by the our outliner model, or it's just a reference we use to keep the track lane alive (it's a weak widget) as long as we are in view.
- L111 _protected member_ `TWeakViewModelPtr<IOutlinerExtension> WeakModel;` — The item associated with this row of data
- L114 _protected member_ `FOnGenerateWidgetForColumn OnGenerateWidgetForColumn;` — Delegate to call to create a new widget for a particular column.
- L117 _protected member_ `FDetectDrag OnDetectDrag;` — Delegate to call when dragging a tree item is detected
- L120 _protected member_ `FIsColumnVisible OnGetColumnVisibility;` — Delegate to call to retrieve column visibility.
- L122 _protected member_ `float SeparatorHeight;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<SWidget>, FOnGenerateWidgetForColumn, TViewModelPtr<IOutlinerExtension>, const FName&, const TSharedRef<SOutlinerViewRow>&);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FDetectDrag, const FGeometry&, const FPointerEvent&, TSharedRef<SOutlinerViewRow>);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsColumnVisible, const FName&);`

### `Source/Editor/SequencerCore/Public/MVVM/Views/STrackAreaLaneView.h` (Public)


#### class `UE::Sequencer::STrackAreaLaneView`  
`class STrackAreaLaneView : public SCompoundWidget , public ITrackLaneWidget`  
_L18-40_
- inherits: `SCompoundWidget,ITrackLaneWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(STrackAreaLaneView)`
- L24 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FViewModelPtr& InViewModel, TSharedPtr<STrackAreaView> InTrackAreaView);`
- L30 _public prototype_ `virtual TSharedRef<const SWidget> AsWidget() const;` — ~ ITrackLaneWidget
- L31 _public prototype_ `virtual FTrackLaneScreenAlignment GetAlignment(const ITrackLaneWidgetSpace& InScreenSpace, const FGeometry& InParentGeometry) const;`
- L33 _public prototype_ `FTimeToPixel GetRelativeTimeToPixel() const;`
- L37 _protected member_ `FWeakViewModelPtr WeakModel;`
- L38 _protected member_ `TWeakPtr<STrackAreaView> WeakTrackAreaView;`
- L39 _protected member_ `TSharedPtr<FTimeToPixel> TrackAreaTimeToPixel;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/STrackAreaView.h` (Public)


#### class `UE::Sequencer::FTrackAreaSlot`  
`class FTrackAreaSlot : public TSlotBase<FTrackAreaSlot>, public TAlignmentWidgetSlotMixin<FTrackAreaSlot>`  
_L57-67_
- inherits: `TSlotBase<FTrackAreaSlot>,TAlignmentWidgetSlotMixin<FTrackAreaSlot>`
- desc: Structure representing a slot in the track area.
- L63 _public prototype_ `FTrackAreaSlot(const TSharedPtr<STrackLane>& InSlotContent);` — Construction from a track lane
- L66 _public member_ `TWeakPtr<STrackLane> TrackLane;` — The track lane that we represent.

#### struct `UE::Sequencer::FTrackAreaViewLayers`  
`struct FTrackAreaViewLayers`  
_L70-73_
- L72 _public member_ `int32 LaneBackgrounds = 0;`

#### class `UE::Sequencer::STrackAreaView`  
`class STrackAreaView : public SPanel , public ITrackLaneWidgetSpace`  
_L79-217_
- inherits: `SPanel,ITrackLaneWidgetSpace`
- desc: The area where tracks( rows of sections ) are displayed.
- L85 _public function_ `SLATE_BEGIN_ARGS( STrackAreaView )`
- L91 _public prototype_ `STrackAreaView();`
- L92 _public prototype_ `~STrackAreaView();`
- L95 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FTrackAreaViewModel> InWeakViewModel);` — Construct this widget
- L97 _public prototype_ `TSharedPtr<FTrackAreaViewModel> GetViewModel() const;`
- L99 _public prototype_ `void SetVirtualPosition(float InVirtualTop);`
- L101 _public prototype_ `TSharedPtr<FTimeToPixel> GetFallbackTimeToPixel() const;`
- L102 _public prototype_ `TSharedPtr<FTimeToPixel> GetTimeToPixel(const FGuid& InViewSpaceID = FGuid()) const;`
- L107 _public prototype_ `void Empty();` — Empty the track area
- L110 _public prototype_ `void PurgeDeadTrackSlots();` — Drop slots whose track lane has been destroyed because no row holds it any more.
- L113 _public prototype_ `void AddTrackSlot(const TViewModelPtr<IOutlinerExtension>& InDataModel, const TSharedPtr<STrackLane>& InSlot);` — Add a new track slot to this area for the given node. The slot will be automatically cleaned up when all external references to the supplied slot are removed.
- L116 _public prototype_ `TSharedPtr<STrackLane> FindTrackSlot(const TViewModelPtr<IOutlinerExtension>& InDataModel);` — Attempt to find an existing slot relating to the given node
- L119 _public prototype_ `void SetOutliner(const TSharedPtr<SOutlinerView>& InOutliner);` — Assign a tree view to this track area.
- L120 _public function_ `TWeakPtr<SOutlinerView> GetOutliner() const`
- L123 _public function_ `void SetShowPinned(bool bShowPinned)` — Set whether this TrackArea should show only pinned nodes or only non-pinned nodes
- L124 _public function_ `bool ShowPinned() const`
- L127 _public function_ `void SetIsPinned(bool bInIsPinned)` — Set whether this TrackArea is pinned to another TrackArea and should skip updating external controls
- L128 _public function_ `bool IsPinned() const`
- L130 _public prototype_ `const FTrackAreaViewLayers& GetPaintLayers() const;`
- L131 _public prototype_ `static FLinearColor BlendDefaultTrackColor(FLinearColor InColor);`
- L136 _public prototype_ `FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — ~ SWidget interface
- L137 _public prototype_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L138 _public prototype_ `FReply OnMouseButtonDoubleClick( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L139 _public prototype_ `FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L140 _public prototype_ `FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L141 _public prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L142 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L143 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L144 _public prototype_ `void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L145 _public prototype_ `FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L146 _public prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L147 _public prototype_ `void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`
- L148 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L149 _public prototype_ `FChildren* GetChildren() override;`
- L150 _public prototype_ `void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L151 _public prototype_ `void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L152 _public prototype_ `FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L153 _public prototype_ `FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L154 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L155 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L156 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L159 _public prototype_ `virtual FTimeToPixel GetScreenSpace(const FGuid& InViewSpaceID = FGuid()) const override;` — ~ Begin ITrackLaneWidgetSpace Interface
- L164 _protected function_ `virtual void OnResized(const FVector2D& OldSize, const FVector2D& NewSize)`
- L167 _protected prototype_ `virtual void UpdateHoverStates( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );` — Update any hover state required for the track area
- L171 _private prototype_ `void HandleViewSpaceAdded(const FGuid& InID, TSharedPtr<FTrackAreaViewSpace> ViewSpace);`
- L172 _private prototype_ `void HandleViewSpaceRemoved(const FGuid& InID, TSharedPtr<FTrackAreaViewSpace> ViewSpace);`
- L177 _private member_ `TPanelChildren<FTrackAreaSlot> Children;` — The track area's children.
- L182 _protected member_ `FInputHandlerStack InputStack;` — Input handler stack responsible for routing input to the different handlers
- L185 _protected member_ `TMap<TWeakViewModelPtr<IOutlinerExtension>, TWeakPtr<STrackLane>> TrackSlots;` — A map of child slot content that exist in our view.
- L188 _protected member_ `TWeakPtr<FTrackAreaViewModel> WeakViewModel;` — Weak pointer to the track area view model.
- L191 _protected member_ `TWeakPtr<SOutlinerView> WeakOutliner;` — Weak pointer to the outliner view (used for scrolling interactions).
- L194 _protected member_ `TOptional<FVector2D> SizeLastFrame;` — Keep a hold of the size of the area so we can maintain zoom levels.
- L197 _protected member_ `TWeakViewModelPtr<IOutlinerExtension> WeakDroppedItem;` — Weak pointer to the dropped node
- L199 _protected member_ `mutable TSharedPtr<FTimeToPixel> TimeToPixel;`
- L200 _protected member_ `mutable TMap<FGuid, TSharedPtr<FTimeToPixel>> ViewSpaceTimeToPixel;`
- L202 _protected member_ `float VirtualTop;`
- L204 _protected member_ `mutable FTrackAreaViewLayers LayerIds;`
- L207 _protected member_ `TOptional<TRange<FFrameNumber>> DropFrameRange;` — The frame range of the section about to be dropped
- L210 _protected member_ `bool bAllowDrop;` — Whether the dropped node is allowed to be dropped onto
- L213 _protected member_ `bool bShowPinnedNodes;` — Whether this TrackArea is for pinned nodes or non-pinned nodes
- L216 _protected member_ `bool bIsPinned;` — Whether this TrackArea is pinned to another TrackArea and should skip updating external controls

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API SEQUENCERCORE_API`
- L42 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/STrackLane.h` (Public)


#### class `UE::Sequencer::STrackLane`  
`class STrackLane : public SPanel`  
_L31-139_
- inherits: `SPanel`
- desc: A wrapper widget responsible for positioning a track lane within the section area
- L35 _public function_ `SLATE_BEGIN_ARGS(STrackLane)`
- L38 _public prototype_ `STrackLane();`
- L39 _public prototype_ `~STrackLane();`
- L42 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<STrackAreaView> InTrackAreaView, TWeakViewModelPtr<IOutlinerExtension> InWeakOutlinerItem, TSharedPtr<STrackLane> InParentLane, const FTrackAreaParameters& InTrackParams, const TSharedRef<SOutlinerView>& InTreeView);` — Construct this widget
- L45 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — ~ SWidget Interface
- L46 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L47 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L48 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L49 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public prototype_ `FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L53 _public prototype_ `void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;` — ~ SPanel Interface
- L54 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L55 _public function_ `FChildren* GetChildren() override`
- L58 _public prototype_ `TViewModelPtr<IOutlinerExtension> GetOutlinerItem() const;` — Gets the outliner view-model that created this track lane
- L60 _public prototype_ `TSharedPtr<STrackAreaView> GetTrackAreaView() const;`
- L61 _public prototype_ `TSharedPtr<STrackLane> GetParentLane() const;`
- L62 _public prototype_ `TSharedPtr<FTimeToPixel> GetTimeToPixel() const;`
- L64 _public prototype_ `TArrayView<const TWeakPtr<STrackLane>> GetChildLanes() const;`
- L66 _public function_ `const TMap<FWeakViewModelPtr, TSharedPtr<ITrackLaneWidget>>& GetAllWidgets() const`
- L69 _public prototype_ `float GetVerticalPosition() const;` — Gets the vertical offset of this track lane
- L71 _public prototype_ `void SetVerticalPosition(float InPosition);` — Sets the vertical offset of this track lane
- L79 _public prototype_ `void PositionParentTrackLanes(TViewModelPtr<IOutlinerExtension> InItem, float InItemTop);` — Sets the vertical offset of this track lane and all parent track lanes given the vertical offset of a particular outliner item inside the current track lane (i.e. an outliner item that's a child of the item that created this track lane) Note that the given item *could* actually be the one that created this track lane.
- L82 _public prototype_ `bool IsPinned() const;` — Returns whether the outliner item that created this track lane is pinned or not
- L84 _public prototype_ `TSharedPtr<ITrackLaneWidget> FindWidgetForModel(const FWeakViewModelPtr& InModel) const;`
- L88 _protected prototype_ `int32 PaintLaneForeground(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) const;`
- L90 _protected prototype_ `void OnHierarchyUpdated();`
- L91 _protected prototype_ `void RecreateWidgets();`
- L94 _private member_ `TWeakPtr<STrackAreaView> WeakTrackAreaView;`
- L97 _private member_ `TWeakViewModelPtr<IOutlinerExtension> WeakOutlinerItem;` — The outliner item that created this lane
- L100 _private member_ `TWeakPtr<SOutlinerView> TreeView;` — Pointer back to the tree view for virtual <-> physical space conversions. Important: weak ptr to avoid circular references
- L102 _private member_ `TMap<FWeakViewModelPtr, TSharedPtr<ITrackLaneWidget>> WidgetsByModel;`
- L104 _private member_ `TArray<TWeakPtr<STrackLane>> WeakChildLanes;`
- L107 _private member_ `TSharedPtr<STrackLane> ParentLane;` — Parent track lane - intentionally a _strong_ ptr to the parent in order to keep it alive even if it is scrolled out of view
- L109 _private member_ `TSharedPtr<FTimeToPixel> TimeToPixel;`
- L120 _private member_ `TPanelChildren<FSlot> Children;` — All the widgets in the panel
- L123 _private member_ `TOptional<FVector2D> LastDesiredSize;` — Our desired size last frame
- L132 _private member_ `TOptional<FDragParameters> DragParameters;`
- L134 _private member_ `FTrackAreaParameters TrackParams;`
- L136 _private member_ `float Position;`
- L138 _private member_ `bool bWidgetsDirty;`

#### struct `UE::Sequencer::STrackLane::FSlot`  
`struct FSlot : TSlotBase<FSlot>`  
_L111-117_
- inherits: `TSlotBase<FSlot>`
- L113 _public prototype_ `FSlot(TSharedPtr<ITrackLaneWidget> InInterface);`
- L114 _public prototype_ `~FSlot();`
- L116 _public member_ `TSharedRef<ITrackLaneWidget> Interface;`

#### struct `UE::Sequencer::STrackLane::FDragParameters`  
`struct FDragParameters`  
_L125-131_
- L127 _public function_ `FDragParameters(float InOriginalHeight, float InDragStartY) : OriginalHeight(InOriginalHeight), DragStartY(InDragStartY)`
- L129 _public member_ `float OriginalHeight;`
- L130 _public member_ `float DragStartY;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SEQUENCERCORE_API`
- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/SequencerInputHandlerStack.h` (Public)


#### class `UE::Sequencer::FInputHandlerStack`  
`class FInputHandlerStack`  
_L31-191_
- desc: Class responsible for handling input to multiple objects that reside at the same level in the widget hierarchy. The sequencer track area is one such example of a single widget that delegates its input handling to multiple sources (edit tool, or time slider controller). To alleviate the complexity of handling input for such sources, where each may fight for mouse capture, this class keeps track of which handler captured the mouse and routs input accordingly. When no mouse capture is active, handlers are called sequentially in the order they were added, until the event is handled.
- L35 _public member_ `FSimpleMulticastDelegate OnBeginCapture;`
- L36 _public member_ `FSimpleMulticastDelegate OnEndCapture;`
- L38 _public function_ `FInputHandlerStack() : CapturedIndex(INDEX_NONE)`
- L41 _public function_ `void AddHandler(ISequencerInputHandler* Handler)` — Add a handler to the stack
- L44 _public function_ `void SetHandlerAt(int32 Index, ISequencerInputHandler* Handler)` — Reset an existing entry in the stack to a new handler
- L62 _public function_ `int32 GetCapturedIndex() const` — Get the index of the currently captured handler, or INDEX_NONE
- L65 _public function_ `FReply HandleMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Handle a mouse down
- L71 _public function_ `FReply HandleMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Handle a mouse up
- L77 _public function_ `FReply HandleMouseDoubleClick(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Handle a mouse double click
- L83 _public function_ `FReply HandleMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Handle a mouse move
- L89 _public function_ `FReply HandleMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Handle a mouse wheel
- L94 _public function_ `FReply HandleKeyDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)`
- L99 _public function_ `FReply HandleKeyUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)`
- L105 _private typedef_ `typedef FReply(ISequencerInputHandler::*InputHandlerFunction)(SWidget&, const FGeometry&, const FPointerEvent&);`
- L106 _private typedef_ `typedef FReply(ISequencerInputHandler::* KeyInputHandlerFunction)(SWidget&, const FGeometry&, const FKeyEvent&);`
- L108 _private function_ `FReply ProcessEvent(InputHandlerFunction Function, SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L139 _private function_ `const FReply& ProcessReply(const FReply& Reply, int32 ThisIndex)`
- L155 _private function_ `FReply ProcessKeyEvent(KeyInputHandlerFunction Function, SWidget& OwnerWidget, const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)` — use mouse capture for the key event
- L187 _private member_ `int32 CapturedIndex;` — Index of the handler that currently has the mouse captured
- L190 _private member_ `TArray<ISequencerInputHandler*> Handlers;` — Array o9f input handlers

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/TreeViewTraits.h` (Public)


#### struct `TListTypeTraits`  
`template<typename ExtensionType> struct TListTypeTraits<UE::Sequencer::TWeakViewModelPtr<ExtensionType>>`  
_L10-54_
- L13 _public typedef_ `using PtrType = UE::Sequencer::TWeakViewModelPtr<ExtensionType>;`
- L14 _public typedef_ `using NullableType = PtrType;`
- L16 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<PtrType, TSharedRef<ITableRow>, false>;`
- L17 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<PtrType, FSparseItemInfo, false>;`
- L18 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<PtrType>;`
- L21 _public function_ `template<typename U> static void AddReferencedObjects( FReferenceCollector&, TArray< PtrType >&, TSet< PtrType >&, TMap< const U*, PtrType >& )`
- L27 _public function_ `static bool IsPtrValid( const PtrType& InPtr )`
- L32 _public function_ `static void ResetPtr( PtrType& InPtr )`
- L37 _public function_ `static PtrType MakeNullPtr()`
- L42 _public function_ `static PtrType NullableItemTypeConvertToItemType( const PtrType& InPtr )`
- L47 _public function_ `static FString DebugDump( PtrType InPtr )`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L53-53_

#### struct `TIsValidListItem`  
`template <typename ExtensionType> struct TIsValidListItem<UE::Sequencer::TWeakViewModelPtr<ExtensionType>>`  
_L57-63_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L60-62_

#### Free symbols / members of external scopes

- L61 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon48b3c9470103`)

### `Source/Editor/SequencerCore/Public/MVVM/Views/ViewUtilities.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Sequencer` (scope `UE`)
- L19 _prototype_ `TSharedRef<SWidget> MakeButton(FText HoverText, const FSlateBrush* Image, const FOnClicked& HandleClicked, const FViewModelPtr& ViewModel);` (scope `UE::Sequencer`)
- L21 _prototype_ `TSharedRef<SWidget> MakeButton(FText HoverText, const FSlateBrush* Image, const FOnGetContent& HandleGetMenuContent, const FViewModelPtr& ViewModel);` (scope `UE::Sequencer`)
- L23 _prototype_ `TSharedRef<SWidget> MakeAddButton(FText HoverText, const FOnClicked& HandleClicked, const FViewModelPtr& ViewModel);` (scope `UE::Sequencer`)
- L25 _prototype_ `TSharedRef<SWidget> MakeAddButton(FText HoverText, const FOnGetContent& HandleGetMenuContent, const FViewModelPtr& ViewModel);` (scope `UE::Sequencer`)
- L27 _prototype_ `TSharedRef<SWidget> MakeAddButton(FText HoverText, const FOnClicked& OnClicked, const TAttribute<bool>& HoverState, const TAttribute<bool>& IsEnabled);` (scope `UE::Sequencer`)
- L29 _prototype_ `TSharedRef<SWidget> MakeAddButton(FText HoverText, const FOnGetContent& HandleGetMenuContent, const TAttribute<bool>& HoverState, const TAttribute<bool>& IsEnabled);` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/Scripting/OutlinerScriptingObject.h` (Public)


#### class `USequencerOutlinerScriptingObject`  
`class USequencerOutlinerScriptingObject : public UObject`  
_L19-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L26 _public member_ `FSequencerOutlinerSelectionChanged OnSelectionChanged;` — `UPROPERTY(BlueprintAssignable, Category="Sequencer Editor")`
- L28 _public prototype_ `void Initialize(UE::Sequencer::TViewModelPtr<UE::Sequencer::FOutlinerViewModel> InOutliner);`
- L31 _public prototype_ `FSequencerViewModelScriptingStruct GetRootNode() const;` — `UFUNCTION(BlueprintCallable, Category="Sequencer Editor")`
- L34 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetChildren(FSequencerViewModelScriptingStruct Node, FName TypeName = NAME_None) const;` — `UFUNCTION(BlueprintCallable, Category="Sequencer Editor")`
- L37 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetSelection() const;` — `UFUNCTION(BlueprintCallable, Category="Sequencer Editor")`
- L40 _public prototype_ `void SetSelection(const TArray<FSequencerViewModelScriptingStruct>& InSelection);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L44 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetMuteNodes();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Mute
- L47 _public prototype_ `void SetMuteNodes(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bInMuted);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L51 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetSoloNodes();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Solo
- L54 _public prototype_ `void SetSoloNodes(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bInSoloed);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L58 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetDeactivatedNodes();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Deactivated
- L61 _public prototype_ `void SetDeactivatedNodes(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bInDeactivated);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L65 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetLockedNodes();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Locked
- L68 _public prototype_ `void SetLockedNodes(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bInLocked);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L72 _public prototype_ `TArray<FSequencerViewModelScriptingStruct> GetPinnedNodes();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Pinned
- L75 _public prototype_ `void SetPinnedNodes(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bInPinned);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")`
- L79 _public prototype_ `void SetExpansion(const TArray<FSequencerViewModelScriptingStruct>& InNodes, bool bExpanded);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Editor")` — Expansion
- L82 _public prototype_ `bool IsExpanded(FSequencerViewModelScriptingStruct InNode) const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer Editor")`
- L86 _protected member_ `UE::Sequencer::TWeakViewModelPtr<UE::Sequencer::FOutlinerViewModel> WeakOutliner;`
- L90 _private prototype_ `void BroadcastSelectionChanged();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSequencerOutlinerSelectionChanged);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSequencerOutlinerSelectionChanged);`

### `Source/Editor/SequencerCore/Public/Scripting/SequencerScriptingLayer.h` (Public)


#### class `USequencerScriptingLayer`  
`class USequencerScriptingLayer : public UObject`  
_L18-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L24 _public prototype_ `virtual void Initialize(TSharedPtr<UE::Sequencer::FEditorViewModel> InViewModel);`
- L27 _public member_ `TObjectPtr<USequencerOutlinerScriptingObject> Outliner;` — `UPROPERTY(BlueprintReadOnly, Category="Sequencer Editor")`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/SequencerCore/Public/Scripting/ViewModelScriptingStruct.h` (Public)


#### struct `FSequencerViewModelScriptingStruct`  
`struct FSequencerViewModelScriptingStruct`  
_L13-29_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public prototype_ `FSequencerViewModelScriptingStruct();`
- L19 _public prototype_ `FSequencerViewModelScriptingStruct(UE::Sequencer::FViewModelPtr InViewModel);`
- L26 _public member_ `FName Type;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sequencer Editor")`
- L28 _public member_ `UE::Sequencer::FWeakViewModelPtr WeakViewModel;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSequencerViewModelScriptingStruct> : public TStructOpsTypeTraitsBase2<FSequencerViewModelScriptingStruct>`  
_L32-39_
- inherits: `TStructOpsTypeTraitsBase2<FSequencerViewModelScriptingStruct>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L35-38_

#### class `USequencerViewModelStructExtensions`  
`class USequencerViewModelStructExtensions : public UBlueprintFunctionLibrary`  
_L46-57_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto FSequencerScriptingRanges
- L53 _public prototype_ `static FString GetLabel(const FSequencerViewModelScriptingStruct& ViewModel);` — `UFUNCTION(BlueprintPure, Category = "Sequencer Editor", meta=(ScriptMethod))`
- L56 _public prototype_ `static FString GetPath(const FSequencerViewModelScriptingStruct& ViewModel);` — `UFUNCTION(BlueprintPure, Category = "Sequencer Editor", meta = (ScriptMethod))`

#### Free symbols / members of external scopes

- L21 _function_ `friend bool operator==(const FSequencerViewModelScriptingStruct& A, const FSequencerViewModelScriptingStruct& B)`
- L36 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonfbfec8590103`)
- L37 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonfbfec8590103`)

### `Source/Editor/SequencerCore/Public/SequencerCoreFwd.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)
- L34 _typedef_ `template<typename T> using TParentModelIterator = TTypedIterator<T, FParentModelIterator>;` (scope `UE::Sequencer`)
- L36 _typedef_ `template<typename T> using TParentFirstChildIterator = TTypedIterator<T, FParentFirstChildIterator>;` (scope `UE::Sequencer`)
- L38 _typedef_ `template<typename T> using TViewModelListIterator = TTypedIterator<T, FViewModelListIterator>;` (scope `UE::Sequencer`)
- L40 _typedef_ `template<typename T> using TViewModelSubListIterator = TTypedIterator<T, FViewModelSubListIterator>;` (scope `UE::Sequencer`)
- L52 _typedef_ `template<typename ViewModelType> using TImplicitViewModelCast = TImplicitViewModelCastImpl<ViewModelType, false>;` (scope `UE::Sequencer`)
- L55 _typedef_ `template<typename ViewModelType> using TImplicitViewModelCastChecked = TImplicitViewModelCastImpl<ViewModelType, true>;` (scope `UE::Sequencer`)
- L63 _typedef_ `using FViewModelPtr = TViewModelPtr<FViewModel>;` (scope `UE::Sequencer`)
- L64 _typedef_ `using FConstViewModelPtr = TViewModelPtr<const FViewModel>;` (scope `UE::Sequencer`)
- L65 _typedef_ `using FWeakViewModelPtr = TWeakViewModelPtr<FViewModel>;` (scope `UE::Sequencer`)

### `Source/Editor/SequencerCore/Public/TimeToPixel.h` (Public)


#### struct `UE::Sequencer::INonLinearTimeTransform`  
`struct INonLinearTimeTransform`  
_L12-18_
- L14 _public prototype_ `virtual ~INonLinearTimeTransform() = default;`
- L16 _public prototype_ `virtual double SourceToView(double Seconds) const = 0;`
- L17 _public prototype_ `virtual double ViewToSource(double Source) const = 0;`

#### struct `UE::Sequencer::FTimeToPixelSpace`  
`struct FTimeToPixelSpace`  
_L25-119_
- desc: Utility for converting time units to slate pixel units and vice versa
- L29 _public prototype_ `FTimeToPixelSpace( const FGeometry& AllottedGeometry, const TRange<double>& InLocalViewRange, const FFrameRate& InTickResolution );`
- L31 _public prototype_ `FTimeToPixelSpace( float WidthPx, const TRange<double>& InLocalViewRange, const FFrameRate& InTickResolution );`
- L33 _public prototype_ `FTimeToPixelSpace CreateNonLinear(TSharedPtr<INonLinearTimeTransform> InNonLinearTransform) const;`
- L41 _public prototype_ `float SecondsToPixel( double Time ) const;` — Converts a time to a pixel point relative to the geometry of a widget (passed into the constructor) @param Time	The time to convert @return The pixel equivalent of the time
- L49 _public prototype_ `float SecondsDeltaToPixel( double TimeDelta ) const;` — Converts a time delta to a pixel delta @param TimeDelta  The time delta to convert @return           The pixel equivalent of the delta time
- L57 _public prototype_ `double PixelToSeconds( float PixelX ) const;` — Converts a pixel value to time @param PixelX The x value of a pixel coordinate relative to the geometry that was passed into the constructor. @return The time where the pixel is located
- L65 _public prototype_ `float FrameToPixel( const FFrameTime& Time ) const;` — Converts a frame time to a pixel point relative to the geometry of a widget (passed into the constructor) @param Time The time to convert @return The pixel equivalent of the frame time
- L73 _public prototype_ `float FrameDeltaToPixel( const FFrameTime& TimeDelta) const;` — Converts a frame delta value to pixel delta @param TimeDelta   The time delta to convert @return            The pixel equivalent of the delta time
- L81 _public prototype_ `FFrameTime PixelToFrame( float PixelX ) const;` — Converts a pixel value to frame time @param PixelX The x value of a pixel coordinate relative to the geometry that was passed into the constructor. @return The frame time where the pixel is located
- L89 _public prototype_ `FFrameTime PixelDeltaToFrame( float PixelDelta ) const;` — Converts a pixel delta value to delta frame time @param PixelDelta The delta value in pixel space @return The equivalent delta frame time
- L97 _public prototype_ `double PixelDeltaToSeconds( float PixelDelta ) const;` — Converts a pixel delta value to delta seconds time @param PixelDelta The delta value in pixel space @return The equivalent delta time in seconds
- L102 _public prototype_ `FFrameRate GetTickResolution() const;` — Retrieve the tick resolution of the current sequence
- L107 _public prototype_ `FTimeToPixelSpace RelativeTo(const FFrameTime& FrameZero) const;` — Make this converter relative to the specified time (ie, such that pixel 0 == FrameAmount)
- L109 _public member_ `TSharedPtr<INonLinearTimeTransform> NonLinearTransform;`
- L112 _protected function_ `FTimeToPixelSpace()`
- L115 _protected member_ `FFrameRate TickResolution;` — The tick resolution of the current timeline
- L117 _protected member_ `float PixelsPerSecond;` — The number of pixels in the view range
- L118 _protected member_ `float PixelOffset;`

#### struct `FTimeToPixel`  
`struct FTimeToPixel : UE::Sequencer::FTimeToPixelSpace`  
_L130-168_
- inherits: `UE::Sequencer::FTimeToPixelSpace`
- desc: Utility for converting time units to slate pixel units and vice versa This class will eventually be deprecated in favor of UE::Sequencer::FTimeToPixelSpace
- L134 _public prototype_ `FTimeToPixel() = delete;`
- L136 _public function_ `FTimeToPixel( const FGeometry& AllottedGeometry, const TRange<double>& InLocalViewRange, const FFrameRate& InTickResolution ) : UE::Sequencer::FTimeToPixelSpace(AllottedGeometry.GetLocalSize().X, InLocalViewRange, InTickResolution)`
- L141 _public function_ `FTimeToPixel( float WidthPx, const TRange<double>& InLocalViewRange, const FFrameRate& InTickResolution ) : UE::Sequencer::FTimeToPixelSpace(WidthPx, InLocalViewRange, InTickResolution)`
- L146 _public function_ `FTimeToPixel(const UE::Sequencer::FTimeToPixelSpace& InOther) : UE::Sequencer::FTimeToPixelSpace(InOther)`
- L151 _public function_ `FTimeToPixel CreateNonLinear(TSharedPtr<UE::Sequencer::INonLinearTimeTransform> InNonLinearTransform) const`
- L158 _public function_ `FTimeToPixel& operator=(const UE::Sequencer::FTimeToPixelSpace& InOther)`
- L167 _public prototype_ `FTimeToPixel RelativeTo(const FFrameTime& FrameZero) const;` — Make this converter relative to the specified time (ie, such that pixel 0 == FrameAmount)

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Sequencer` (scope `UE`)
