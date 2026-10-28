# Plugins / ModelingUI

- module root: `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI`
- headers: 2; symbols: 32
- symbol kinds: class=4, delegate=1, function=3, member=12, prototype=12
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, Engine, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingUIModule.h` (Public)


#### class `FModelingUIModule`  
`class FModelingUIModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TArray<FName> CustomizedClasses;`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h` (Public)


#### class `SDraggableBoxOverlay`  
`class UE_DEPRECATED(5.6, "Use UE::ToolWidgets::SDraggableBoxOverlay instead.") SDraggableBoxOverlay : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- desc: Class that can be used to place a draggable box into a viewport or some other large widget as an overlay. Just place the widget that you want to be draggable as the contents of SDraggableBoxOverlay.
- L18 _public function_ `SLATE_BEGIN_ARGS(SDraggableBoxOverlay)`
- L25 _public prototype_ `SLATE_ARGUMENT(bool, bPositionRelativeToBottom) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — When true, the positioning of the box is relative to the bottom of the widget rather than the top, so the VerticalPosition in SetBoxPosition is interpreted as distance from the bottom of the containing widget. The choice here depends on how your widget is generally positioned, for instance if it is near the bottom, you want this to be true so that making the window smaller does not immediately clip your box.
- L36 _public prototype_ `void SetBoxPosition(float HorizontalPosition, float VerticalPosition);` — Sets the box position in the overlay. Horizontal position is distance from left, and vertical position is distance from bottom or from top depending on whether bPositionRelativeToBottom == true.
- L40 _protected member_ `TSharedPtr<SWidget> DraggableBox;`
- L41 _protected member_ `TSharedPtr<SWidget> ContainingBox;`
- L43 _protected member_ `float DraggableBoxPaddingHorizontal = 0;`
- L44 _protected member_ `float DraggableBoxPaddingVertical = 0;`

#### class `SDraggableBox`  
`class UE_DEPRECATED(5.6, "SDraggableBox is now private. Use UE::ToolWidgets::SDraggableBoxOverlay instead.") SDraggableBox : public SCompoundWidget`  
_L55-79_
- inherits: `SCompoundWidget`
- desc: A widget for the draggable box itself, which requires its parent to handle its positioning in response to the drag. Users probably shouldn't use this class directly; rather, they should use SDraggableBoxOverlay, which will put its contents into a draggable box and properly handle the dragging without the user having to set it up.
- L59 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDragComplete, const FVector2D& );`
- L61 _public function_ `SLATE_BEGIN_ARGS(SDraggableBox)`
- L62 _public prototype_ `SLATE_EVENT(FOnDragComplete, OnDragComplete) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L69 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget overrides necessary for box to be draggable
- L70 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L73 _protected member_ `TSharedPtr<SWidget> InnerWidget;`
- L74 _protected member_ `FOnDragComplete OnDragComplete;`
- L78 _protected member_ `FVector2D ScreenSpaceOffsetOfGrab;` — Remembers the point in the box that we grabbed (on click, rather than when the drag was confirmed)

#### class `FDraggableBoxUIDragOperation`  
`class UE_DEPRECATED(5.6, "FDraggableBoxUIDragOperation is now private. Use UE::ToolWidgets::SDraggableBoxOverlay instead.") FDraggableBoxUIDragOperation : public FDragDropOperation`  
_L88-139_
- inherits: `FDragDropOperation`
- desc: A drag/drop operation used by SDraggableBox, largely modeled on FInViewportUIDragOperation, except instead of requiring the drop location to be able to handle that particular class to trigger the OnDragComplete delegate, it just triggers on any drop. This makes it possible to use it in any viewports, not just the level editor.
- L92 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDraggableBoxUIDragOperation, FDragDropOperation)`
- L96 _public prototype_ `virtual void OnDragged(const FDragDropEvent& DragDropEvent) override;`
- L109 _public prototype_ `static TSharedRef<FDraggableBoxUIDragOperation> New(const TSharedRef<class SWidget>& InUIToBeDragged, const FVector2D InDecoratorOffset, const FVector2D& OwnerAreaSize, SDraggableBox::FOnDragComplete& OnDragComplete);` — Create this Drag and Drop Content @param InUIToBeDragged	  The UI being dragged @param InDecoratorOffset   Where within the UI we grabbed, so we're not dragging by the upper left of the UI. @param OwnerAreaSize       Size of the DockArea at the time when we start dragging. @param OnDragComplete      Delegate to call when dropped. Gets passed in the screen space location of the top left corner. @return a new FDockingDragOperation
- L114 _public function_ `virtual ~FDraggableBoxUIDragOperation()`
- L121 _protected prototype_ `FDraggableBoxUIDragOperation(const TSharedRef<class SWidget>& InUIToBeDragged, const FVector2D InDecoratorOffsetFromCursor, const FVector2D& OwnerAreaSize, SDraggableBox::FOnDragComplete& OnDragCompletee);` — The constructor is protected, so that this class can only be instantiated as a shared pointer.
- L128 _protected member_ `TSharedPtr<class SWidget> UIBeingDragged;` — Shared pointer to our contents, which are a weak pointer.
- L131 _protected member_ `FVector2D DecoratorOffsetFromCursor;` — Screen space offset of grab location from the top left corner of the rectangle being dragged.
- L134 _protected member_ `FVector2D LastContentSize;` — Size of rectangle being dragged
- L137 _protected member_ `SDraggableBox::FOnDragComplete OnDragComplete;`

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDragComplete, const FVector2D& );`
