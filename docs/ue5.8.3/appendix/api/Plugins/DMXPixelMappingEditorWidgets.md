# Plugins / DMXPixelMappingEditorWidgets

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets`
- headers: 5; symbols: 92
- symbol kinds: class=7, function=8, member=46, prototype=30, struct=1
- PrivateDependencyModuleNames: Core, DMXPixelMappingCore, DMXProtocol, DMXRuntime, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Slate, SlateCore

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets/Public/DMXPixelMappingComponentWidget.h` (Public)


#### class `FDMXPixelMappingComponentWidget`  
`class FDMXPixelMappingComponentWidget : public TSharedFromThis<FDMXPixelMappingComponentWidget>`  
_L19-83_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `TSharedFromThis<FDMXPixelMappingComponentWidget>`
- desc: Since pixel mapping designer logic relies on computed sizes, two widgets are needed, one as label text, one as the actual box that needs its real size. This widget internally holds both, both are guaranteed to be valid, and adopt sizes and positions reasonably together.
- L24 _public prototype_ `FDMXPixelMappingComponentWidget(TSharedPtr<SDMXPixelMappingComponentBox> InComponentBox = nullptr, TSharedPtr<SDMXPixelMappingComponentLabel> InComponentLabel = nullptr, bool bShowLabelAbove = false);` — Constructs the class, optionally with custom widgets
- L27 _public prototype_ `virtual ~FDMXPixelMappingComponentWidget();` — Destructor
- L30 _public prototype_ `void AddToCanvas(const TSharedRef<SConstraintCanvas>& Canvas, float ZOrder);` — Adds the widgets to a canvas. If it already resides in a canvas it is removed from that.
- L33 _public prototype_ `void RemoveFromCanvas();` — Adds the widgets to a canvas. Needs to be assigned to a canvas already.
- L36 _public prototype_ `void SetZOrder(float ZOrder);` — Sets the position in a canvas. Needs to be assigned to a canvas already.
- L39 _public prototype_ `void SetPosition(const FVector2D& LocalPosition);` — Sets the position in the canvas it was added to.
- L42 _public prototype_ `void SetSize(const FVector2D& LocalSize);` — Sets the size on both widgets
- L45 _public prototype_ `FVector2D GetLocalSize() const;` — Sets the size of both widgets
- L48 _public prototype_ `void SetLabelText(const FText& Text);` — Sets the label text
- L51 _public prototype_ `void SetIDVisibility(bool bVisible);` — Sets if the ID text of is visible
- L54 _public prototype_ `void SetColor(const FLinearColor& Color);` — Sets the color of the widget
- L57 _public prototype_ `FLinearColor GetColor() const;` — Retuns the color of the widget
- L60 _public prototype_ `void SetVisibility(EVisibility Visibility);` — Sets the visibility of the widget
- L62 _public function_ `const TSharedPtr<SDMXPixelMappingComponentBox>& GetComponentBox() const`
- L63 _public function_ `const TSharedPtr<SDMXPixelMappingComponentLabel>& GetComponentLabel() const`
- L67 _protected member_ `TSharedPtr<SConstraintCanvas> OuterCanvas;` — When added to a canvas, the canvas it was added to
- L70 _protected member_ `SConstraintCanvas::FSlot* ComponentSlot = nullptr;` — The canvas slot of the component widget
- L73 _protected member_ `SConstraintCanvas::FSlot* LabelSlot = nullptr;` — The canvas slot of the label widget
- L76 _protected member_ `TSharedPtr<SDMXPixelMappingComponentBox> ComponentBox;` — The component widget
- L79 _protected member_ `TSharedPtr<SDMXPixelMappingComponentLabel> ComponentLabel;` — The label widget
- L82 _protected member_ `bool bLabelAbove = false;` — If true, the label is drawn above the box, else inside

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets/Public/SDMXPixelMappingComponentBox.h` (Public)


#### class `SDMXPixelMappingComponentBox`  
`class SDMXPixelMappingComponentBox : public SCompoundWidget`  
_L17-68_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SCompoundWidget`
- desc: A label component label in pixelmapping designer. Ment to be used with DMXPixelMapingComponentWidgetWrapper
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingComponentBox) :_MaxIDTextSize(FVector2D(18.f, 18.f))`
- L25 _public prototype_ `SLATE_ATTRIBUTE(FText, IDText) SLATE_ARGUMENT(FVector2D, MaxIDTextSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Text shown in the middle of the widget. Always scales to the widget
- L35 _public prototype_ `virtual void SetLocalSize(const FVector2D& NewSize);` — Sets the size of the widget
- L38 _public prototype_ `virtual void SetIDText(const FText& NewIDText);` — Sets the IDText
- L41 _public prototype_ `virtual FVector2f GetLocalSize() const;` — Returns the local size
- L44 _public prototype_ `virtual void SetBorderColor(const FLinearColor& Color);` — Sets the color of the border
- L47 _public prototype_ `virtual FLinearColor GetBorderColor() const;` — Retuns the color of the widget
- L51 _protected member_ `FVector2D LocalSize = FVector2D(1.f, 1.f);` — The currently drawn local size
- L54 _protected member_ `TSharedPtr<SBox> ComponentBox;` — The box that is shown
- L57 _protected member_ `TSharedPtr<SBox> IDTextBox;` — The box that is shown
- L60 _protected member_ `TSharedPtr<STextBlock> IDTextBlock;` — The box that is shown
- L63 _protected member_ `FSlateBrush BorderBrush;` — The brush used for the border
- L66 _protected member_ `TAttribute<FText> IDText;` — Slate arguments
- L67 _protected member_ `FVector2D MaxIDTextSize;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets/Public/SDMXPixelMappingComponentLabel.h` (Public)


#### class `SDMXPixelMappingComponentLabel`  
`class SDMXPixelMappingComponentLabel : public SCompoundWidget`  
_L14-55_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SCompoundWidget`
- desc: A box in pixel mapping designer. Ment to be used with DMXPixelMapingComponentWidgetWrapper
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingComponentLabel) : _bAlignAbove(false) , _bScaleToSize(true)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(FText, LabelText) SLATE_ARGUMENT(bool, bAlignAbove) SLATE_ARGUMENT(bool, bScaleToSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Label shown on top of the widget
- L37 _public prototype_ `virtual void SetWidth(const float& Width);` — Sets the width of the widget
- L40 _public prototype_ `virtual void SetText(const FText& Text);` — Sets the label text
- L43 _public prototype_ `virtual FVector2f GetLocalSize() const;` — Returns the local size
- L47 _protected member_ `TSharedPtr<SBox> Box;` — The box that defines the size
- L50 _protected member_ `TSharedPtr<STextBlock> LabelTextBlock;` — Text box that shows the ID text
- L53 _protected member_ `TAttribute<FText> LabelText;` — Slate arguments
- L54 _protected member_ `bool bAlignAbove;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets/Public/SDMXPixelMappingEditorWidgets.h` (Public)


#### class `SDMXPixelMappingScreenLayout`  
`class SDMXPixelMappingScreenLayout : public SCompoundWidget`  
_L18-83_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingScreenLayout) : _NumXCells(1) , _NumYCells(1) , _Distribution(EDMXPixelMappingDistribution::TopLeftToRight) , _PixelFormat(EDMXCellFormat::PF_RGB) , _bShowAddresses(false) , _bShowUniverse(false) , _LocalUniverse(1) , _StartAddress(1)`
- L33 _public prototype_ `SLATE_ARGUMENT(int32, NumXCells) SLATE_ARGUMENT(int32, NumYCells) SLATE_ARGUMENT(EDMXPixelMappingDistribution, Distribution) SLATE_ARGUMENT(EDMXCellFormat, PixelFormat) SLATE_ARGUMENT(bool, bShowAddresses) SLATE_ARGUMENT(bool, bShowUniverse) SLATE_ARGUMENT(int32, LocalUniverse) SLATE_ARGUMENT(int32, StartAddress) SLATE_ATTRIBUTE(const FSlateBrush*, Brush) SLATE_END_ARGS()`
- L58 _private member_ `int32 NumXCells;`
- L60 _private member_ `int32 NumYCells;`
- L62 _private member_ `EDMXPixelMappingDistribution Distribution;`
- L64 _private member_ `EDMXCellFormat PixelFormat;`
- L66 _private member_ `bool bShowAddresses;`
- L68 _private member_ `bool bShowUniverse;`
- L70 _private member_ `int32 LocalUniverse;`
- L72 _private member_ `int32 StartAddress;`
- L74 _private member_ `TAttribute<const FSlateBrush*> Brush;`
- L76 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;`
- L78 _private member_ `TSharedPtr<SUniformGridPanel> GridPanel;`
- L80 _private member_ `TArray<TPair<int32, int32>> UnorderedList;`
- L82 _private member_ `TArray<TPair<int32, int32>> SortedList;`

#### class `SDMXPixelMappingSimpleScreenLayout`  
`class SDMXPixelMappingSimpleScreenLayout : public SCompoundWidget`  
_L86-123_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SCompoundWidget`
- L90 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingSimpleScreenLayout) : _NumXCells(1) , _NumYCells(1) , _LocalUniverse(1) , _StartAddress(1)`
- L97 _public prototype_ `SLATE_ARGUMENT(int32, NumXCells) SLATE_ARGUMENT(int32, NumYCells) SLATE_ARGUMENT(int32, LocalUniverse) SLATE_ARGUMENT(int32, StartAddress) SLATE_ATTRIBUTE(const FSlateBrush*, Brush) SLATE_END_ARGS()`
- L114 _private member_ `int32 LocalUniverse;`
- L116 _private member_ `int32 StartAddress;`
- L118 _private member_ `int32 NumXCells;`
- L120 _private member_ `int32 NumYCells;`
- L122 _private member_ `TAttribute<const FSlateBrush*> Brush;`

#### class `SDMXPixelMappingCell`  
`class SDMXPixelMappingCell : public SCompoundWidget`  
_L126-149_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SCompoundWidget`
- L130 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingCell) : _CellID(1)`
- L134 _public prototype_ `SLATE_ARGUMENT(int32, CellID) SLATE_ATTRIBUTE(const FSlateBrush*, Brush) SLATE_END_ARGS()`
- L145 _public member_ `TAttribute<const FSlateBrush*> Brush;`
- L148 _private member_ `int32 CellID;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditorWidgets/Public/SDMXPixelMappingScreenComponentBox.h` (Public)


#### struct `FDMXPixelMappingScreenComponentGridParams`  
`struct FDMXPixelMappingScreenComponentGridParams`  
_L17-27_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- desc: Params to update a SDMXPixelMappingScreenComponentBox
- L19 _public member_ `int32 NumXCells = 1;`
- L20 _public member_ `int32 NumYCells = 1;`
- L21 _public member_ `EDMXPixelMappingDistribution Distribution = EDMXPixelMappingDistribution::TopLeftToRight;`
- L22 _public member_ `EDMXCellFormat PixelFormat = EDMXCellFormat::PF_RGB;`
- L23 _public member_ `bool bShowAddresses = false;`
- L24 _public member_ `bool bShowUniverse = false;`
- L25 _public member_ `int32 LocalUniverse = 1;`
- L26 _public member_ `int32 StartAddress = 1;`

#### class `SDMXPixelMappingScreenComponentBox`  
`class SDMXPixelMappingScreenComponentBox : public SDMXPixelMappingComponentBox`  
_L32-88_
- reflection: `UE_DEPRECATED(5.1, "Pixel Mapping Editor Widgets are no longer supported and to be implemented per view. See SDMXPixelMappingOutputComponent for an example.")`
- inherits: `SDMXPixelMappingComponentBox`
- desc: A label component label in pixelmapping designer. Ment to be used with DMXPixelMapingComponentWidgetWrapper
- L36 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingScreenComponentBox) : _NumXCells(1) , _NumYCells(1) , _Distribution(EDMXPixelMappingDistribution::TopLeftToRight) , _PixelFormat(EDMXCellFormat::PF_RGB) , _bShowAddresses(false) , _bShowUniverse(false) , _LocalUniverse(1) , _StartAddress(1)`
- L48 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, Size) SLATE_ATTRIBUTE(FLinearColor, Color) SLATE_ARGUMENT(int32, NumXCells) SLATE_ARGUMENT(int32, NumYCells) SLATE_ARGUMENT(EDMXPixelMappingDistribution, Distribution) SLATE_ARGUMENT(EDMXCellFormat, PixelFormat) SLATE_ARGUMENT(bool, bShowAddresses) SLATE_ARGUMENT(bool, bShowUniverse) SLATE_ARGUMENT(int32, LocalUniverse) SLATE_ARGUMENT(int32, StartAddress) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The size of the widget
- L74 _public prototype_ `virtual void SetLocalSize(const FVector2D& NewSize) override;` — Sets the size of the widget
- L77 _public prototype_ `virtual FVector2f GetLocalSize() const override;` — Returns the local size
- L80 _public prototype_ `void RebuildGrid(const FDMXPixelMappingScreenComponentGridParams& GridParams);` — Rebuilds the grid
- L84 _private member_ `static const uint32 MaxGridUICells;` — The max grid cells shown before the widget shows as single box
