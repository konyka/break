# Plugins / MetaHumanImageViewer

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanImageViewer`
- headers: 2; symbols: 35
- symbol kinds: class=2, delegate=2, function=1, macro=1, member=9, prototype=20
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, MetaHumanCoreTech, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanImageViewer/Private/MetaHumanImageViewerModule.h` (Private)


#### class `FMetaHumanImageViewerModule`  
`class FMetaHumanImageViewerModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanImageViewer/Public/SMetaHumanImageViewer.h` (Public)


#### class `SMetaHumanImageViewer`  
`class SMetaHumanImageViewer : public SImage`  
_L13-65_
- inherits: `SImage`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanImageViewer)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(TSharedPtr<class FUICommandList>, CommandList) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Image resource
- L28 _public prototype_ `FReply HandleMouseButtonDown(const FGeometry& InGeometry, const FVector2f& InLocalMouse, const FKey& InEffectingButton);`
- L29 _public prototype_ `FReply HandleMouseButtonUp(const FGeometry& InGeometry, const FVector2f& InLocalMouse, const FKey& InEffectingButton);`
- L30 _public prototype_ `FReply HandleMouseMove(const FGeometry& InGeometry, const FVector2f& InLocalMouse);`
- L31 _public prototype_ `FReply HandleMouseWheel(const FGeometry& InGeometry, const FVector2f& InLocalMouse, float InWheelDelta);`
- L33 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L36 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L37 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L38 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L40 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InWidgetClippingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool InParentEnabled) const override;`
- L44 _public member_ `FOnViewChanged OnViewChanged;`
- L46 _public prototype_ `void SetNonConstBrush(FSlateBrush* InBrush);`
- L47 _public prototype_ `virtual void ResetView();`
- L49 _public prototype_ `void SetDrawBlanking(bool bInDrawBlanking);`
- L53 _protected member_ `TSharedPtr<class FUICommandList> CommandList;`
- L55 _protected member_ `FBox2f UVOrig;`
- L56 _protected member_ `FVector2f MouseOrig;`
- L57 _protected member_ `bool bIsPanning = false;`
- L58 _protected member_ `mutable FGeometry Geometry;`
- L60 _protected member_ `FOnGeometryChanged OnGeometryChanged;`
- L61 _protected member_ `FSlateBrush* NonConstBrush = nullptr;`
- L62 _protected prototype_ `virtual void GeometryChanged();`
- L64 _protected member_ `bool bDrawBlanking = true;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANIMAGEVIEWER_API`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewChanged, FBox2f);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewChanged, FBox2f);`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGeometryChanged);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGeometryChanged);`
