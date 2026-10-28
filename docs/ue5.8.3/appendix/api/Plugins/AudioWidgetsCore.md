# Plugins / AudioWidgetsCore

- module root: `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore`
- headers: 9; symbols: 291
- symbol kinds: class=9, delegate=7, enum=1, enumerator=2, function=55, macro=4, member=127, namespace=4, prototype=63, struct=9, typedef=9, variable=1
- PrivateDependencyModuleNames: AppFramework, AudioMixerCore, CoreUObject, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Private/Permutations.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioWidgetsCore`
- L7 _namespace_ `namespace Permutations` (scope `AudioWidgetsCore`)
- L9 _variable_ `constexpr uint8 MaxFactorial = 20;` (scope `AudioWidgetsCore::Permutations`)
- L14 _function_ `constexpr uint64 Factorial(uint8 N)` (scope `AudioWidgetsCore::Permutations`) — Compute exact factorial. Only valid for small non-negative integers.
- L35 _prototype_ `uint64 AnalyzePermutation(TArrayView<uint8> PermutationArray);` (scope `AudioWidgetsCore::Permutations`) — Get an integer that uniquely represents the given permutation. @param PermutationArray The elements of the array should be distinct values in the interval [0, N-1] where N == PermutationArray.Num(). On return, the array will have been sorted. @return A value in the interval [0, N!-1] where N == PermutationArray.Num(). If N > MaxFactorial, the result is undefined.
- L44 _prototype_ `TArray<uint8> GeneratePermutation(uint64 PermutationID, uint8 NumValues);` (scope `AudioWidgetsCore::Permutations`) — Create the permutation that is uniquely represented by the given integer. @param PermutationID A value in the interval [0, N!-1] where N == NumValues. @param NumValues The desired number of values in the permutation, must be no greater than MaxFactorial. @return An array of distinct values with length == NumValues. If NumValues > MaxFactorial, the result is undefined.

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Private/SDragReorderableTileView.h` (Private)


#### class `AudioWidgetsCore::TItemDragDropOperation`  
`template<typename ItemT, typename DragDropOperationT> class TItemDragDropOperation : public FDragDropOperation`  
_L23-42_
- inherits: `FDragDropOperation`
- desc: Abstract base class, represents an item that is being dragged from a given source tile view. Uses Curiously Recurring Template Pattern so that FDragDropOperation type checking operations can be used.
- L26 _public typedef_ `using ItemType = ItemT;`
- L27 _public typedef_ `using STileViewType = SDragReorderableTileView<DragDropOperationT>;`
- L29 _public function_ `TItemDragDropOperation(TSharedRef<STileViewType> InSourceTileView) : WeakSourceTileView(InSourceTileView.ToWeakPtr())`
- L34 _public prototype_ `virtual const ItemType& GetItem() const = 0;`
- L36 _public function_ `TSharedPtr<STileViewType> GetSourceTileView() const`
- L38 _public function_ `virtual FCursorReply OnCursorQuery() override`
- L41 _private member_ `const TWeakPtr<STileViewType> WeakSourceTileView;`

#### class `AudioWidgetsCore::SDragReorderableTileView`  
`template<typename DragDropOperationT> class SDragReorderableTileView : public STileView<typename DragDropOperationT::ItemType>`  
_L54-175_
- inherits: `STileView<typenameDragDropOperationT::ItemType>`
- desc: Abstract base class for TileView widget that allow its tiles to be dragged and dropped for reordering etc. Dropping of a dragged item onto the tile view is supported if the tile view is currently empty.
- L57 _public typedef_ `using Base = STileView<typename DragDropOperationT::ItemType>;`
- L58 _public typedef_ `using ItemType = typename DragDropOperationT::ItemType;`
- L60 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSetShowItem, const ItemType&, bool);`
- L61 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnReorderItems, const ItemType& , bool , const ItemType& );`
- L63 _public function_ `void Construct(const typename Base::FArguments& InArgs, FOnSetShowItem InOnSetShowItem, FOnReorderItems InOnReorderItems)`
- L71 _public prototype_ `virtual TSharedPtr<DragDropOperationT> CreateDragDropOperation() = 0;`
- L73 _public function_ `void SetShowItem(const ItemType& Item, bool bShow)`
- L78 _public function_ `void ReorderItems(const ItemType& ItemDroppedOnto, bool bInsertAfter, const ItemType& DragDropItem)`
- L84 _public function_ `void HandleItemDrop(const ItemType& InItemDroppedOnto, bool bInInsertAfter, const ItemType& InDragDropItem, TSharedPtr<SDragReorderableTileView> InDragSourceTileView)`
- L105 _public function_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L117 _public function_ `virtual void OnDragLeave(FDragDropEvent const& DragDropEvent) override`
- L122 _public function_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L158 _public function_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override`
- L172 _private member_ `FOnSetShowItem OnSetShowItem;`
- L173 _private member_ `FOnReorderItems OnReorderItems;`
- L174 _private member_ `bool bPaintDropIndicator = false;`

#### class `AudioWidgetsCore::SDragReorderableTile`  
`template<ItemDragDropOperation DragDropOperationT> class SDragReorderableTile : public STableRow<typename DragDropOperationT::ItemType>`  
_L181-320_
- inherits: `STableRow<typenameDragDropOperationT::ItemType>`
- desc: Base class for tiles displayed by SDragReorderableTileView.
- L184 _public typedef_ `using Base = STableRow<typename DragDropOperationT::ItemType>;`
- L185 _public typedef_ `using ItemType = typename DragDropOperationT::ItemType;`
- L186 _public typedef_ `using STileViewType = SDragReorderableTileView<DragDropOperationT>;`
- L188 _public function_ `bool IsBeingDragged() const`
- L192 _protected function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent) override`
- L211 _protected function_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L219 _protected function_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L234 _protected function_ `virtual int32 OnPaintDropIndicator(EItemDropZone InItemDropZone, const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override`
- L242 _private function_ `TOptional<EItemDropZone> CanAcceptDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)`
- L258 _private function_ `bool IsValidDrop(const TSharedRef<STileViewType>& OwnerTileView, EItemDropZone ItemHoverZone, TSharedRef<DragDropOperationT> DragDropOp) const`
- L291 _private function_ `FReply AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemHoverZone)`
- L308 _private function_ `TSharedPtr<STileViewType> GetPinnedTileView()`
- L313 _private function_ `EItemDropZone GetItemHoverZone(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)`
- L319 _private member_ `TWeakPtr<FDragDropOperation> WeakDragDropOperation;` — Will be set when a drag is detected.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AudioWidgetsCore`
- L13 _prototype_ `int32 DrawDropIndicator(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, EHorizontalAlignment HorizontalAlignment);` (scope `AudioWidgetsCore`) — Function to draw a dotted line representing where the current drag drop would place the dragged item.
- L46 _member_ `requires { typename T::ItemType; };` (scope `AudioWidgetsCore::T`) — && std::derived_from<T, TItemDragDropOperation<typename T::ItemType, T>>; // Can uncomment when all platform stdlibs have <concepts> header.
- L60 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetShowItem, const ItemType&, bool);`
- L61 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnReorderItems, const ItemType& , bool , const ItemType& );`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/AudioMeterChannelInfo.h` (Public)


#### struct `FAudioMeterChannelInfo`  
`struct FAudioMeterChannelInfo`  
_L8-23_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public member_ `float MeterValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioMeter)`
- L16 _public member_ `float PeakValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioMeter)`
- L19 _public member_ `float ClippingValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioMeter)`
- L22 _public member_ `TOptional<float> MeterValueBarStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioMeter, meta = (ToolTip = "By default the meter value bar will be drawn from the minimum of the ValueRangeDb up to the MeterValue. Set this property to draw the meter value bar starting at a different value."))`

#### Free symbols / members of external scopes

- L25 _function_ `inline bool operator==(const FAudioMeterChannelInfo& Lhs, const FAudioMeterChannelInfo& Rhs)`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/AudioMeterWidgetStyle.h` (Public)


#### struct `FAudioMeterWidgetStyle`  
`struct FAudioMeterWidgetStyle : public FSlateWidgetStyle`  
_L20-149_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an AudioMeter widget
- L24 _public prototype_ `static const FAudioMeterWidgetStyle& GetDefault();`
- L26 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L27 _public function_ `virtual const FName GetTypeName() const override`
- L29 _public prototype_ `void UnlinkColors();`
- L31 _public member_ `inline static const FName TypeName = "FA`
- L35 _public member_ `FSlateBrush MeterValueImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Image to use to represent the meter value.
- L36 _public function_ `FAudioMeterWidgetStyle& SetMeterValueImage(const FSlateBrush& InMeterValueImage)`
- L40 _public member_ `FSlateBrush BackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use to represent the background.
- L41 _public function_ `FAudioMeterWidgetStyle& SetBackgroundImage(const FSlateBrush& InBackgroundImage)`
- L45 _public member_ `FSlateBrush MeterBackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use to represent the meter background.
- L46 _public function_ `FAudioMeterWidgetStyle& SetMeterBackgroundImage(const FSlateBrush& InMeterBackgroundImage)`
- L50 _public member_ `FSlateBrush MeterValueBackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use to draw behind the meter value.
- L51 _public function_ `FAudioMeterWidgetStyle& SetMeterValueBackgroundImage(const FSlateBrush& InMeterValueBackgroundImage)`
- L55 _public member_ `FSlateBrush MeterPeakImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use to represent the meter peak.
- L56 _public function_ `FAudioMeterWidgetStyle& SetMeterPeakImage(const FSlateBrush& InMeterPeakImage)`
- L60 _public member_ `FSlateBrush MeterClippingImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use to represent the meter clipping indicator.
- L61 _public function_ `FAudioMeterWidgetStyle& SetMeterClippingImage(const FSlateBrush& InMeterClippingImage)`
- L65 _public member_ `FVector2D MeterSize = FVector2D(250.0f, 25.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — How thick to draw the meter
- L66 _public function_ `FAudioMeterWidgetStyle& SetMeterSize(const FVector2D& InMeterSize)`
- L70 _public member_ `FVector2D MeterPadding = FVector2D(10.0f, 5.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — How much padding to add around the meter
- L71 _public function_ `FAudioMeterWidgetStyle& SetMeterPadding(const FVector2D& InMeterPadding)`
- L75 _public member_ `float MeterValuePadding = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — How much padding to add around the meter value
- L76 _public function_ `FAudioMeterWidgetStyle& SetMeterValuePadding(float InMeterValuePadding)`
- L80 _public member_ `float PeakValueWidth = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — How wide to draw the peak value indicator
- L81 _public function_ `FAudioMeterWidgetStyle& SetPeakValueWidth(float InPeakValueWidth)`
- L85 _public member_ `float ClippingValueWidth = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — How wide to draw the clipping value indicator
- L86 _public function_ `FAudioMeterWidgetStyle& SetClippingValueWidth(float InClippingValueWidth)`
- L90 _public member_ `FVector2D ValueRangeDb = FVector2D(-160, 10);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The minimum and maximum value to display in dB (values are clamped in this range)
- L91 _public function_ `FAudioMeterWidgetStyle& SetValueRangeDb(const FVector2D& InValueRangeDb)`
- L95 _public member_ `bool bShowScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Whether or not to show the decibel scale alongside the meter
- L96 _public function_ `FAudioMeterWidgetStyle& SetShowScale(bool bInShowScale)`
- L100 _public member_ `bool bScaleSide = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Which side to show the scale. If vertical, true means left side, false means right side. If horizontal, true means above, false means below.
- L101 _public function_ `FAudioMeterWidgetStyle& SetScaleSide(bool bInScaleSide)`
- L105 _public member_ `float ScaleHashOffset = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Offset for the hashes
- L106 _public function_ `FAudioMeterWidgetStyle& SetScaleHashOffset(float InScaleHashOffset)`
- L110 _public member_ `float ScaleHashWidth = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The width of each hash mark
- L111 _public function_ `FAudioMeterWidgetStyle& SetScaleHashWidth(float InScaleHashWidth)`
- L115 _public member_ `float ScaleHashHeight = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The height of each hash mark
- L116 _public function_ `FAudioMeterWidgetStyle& SetScaleHashHeight(float InScaleHashHeight)`
- L120 _public member_ `int32 DecibelsPerHash = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance, meta = (UIMin = "3", ClampMin="3", UIMax = "10"))` — How wide to draw the decibel scale, if it's enabled
- L121 _public function_ `FAudioMeterWidgetStyle& SetDecibelsPerHash(float InDecibelsPerHash)`
- L125 _public member_ `FSlateFontInfo Font = FStyleDefaults::GetFontInfo(5);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Font family and size to be used when displaying the meter scale.
- L126 _public function_ `FAudioMeterWidgetStyle& SetFont(const FSlateFontInfo& InFont)`
- L127 _public function_ `FAudioMeterWidgetStyle& SetFont(TSharedPtr<const FCompositeFont> InCompositeFont, const int32 InSize, const FName& InTypefaceFontName = NAME_None)`
- L128 _public function_ `FAudioMeterWidgetStyle& SetFont(const UObject* InFontObject, const int32 InSize, const FName& InTypefaceFontName = NAME_None)`
- L131 _public prototype_ `FAudioMeterWidgetStyle& SetFont(const FName& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L133 _public prototype_ `FAudioMeterWidgetStyle& SetFont(const FString& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L135 _public prototype_ `FAudioMeterWidgetStyle& SetFont(const WIDECHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L137 _public prototype_ `FAudioMeterWidgetStyle& SetFont(const ANSICHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L139 _public prototype_ `FAudioMeterWidgetStyle& SetFontName(const FName& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L141 _public prototype_ `FAudioMeterWidgetStyle& SetFontName(const FString& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L143 _public prototype_ `FAudioMeterWidgetStyle& SetFontName(const WIDECHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L145 _public prototype_ `FAudioMeterWidgetStyle& SetFontName(const ANSICHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L147 _public function_ `FAudioMeterWidgetStyle& SetFontSize(uint16 InSize)`
- L148 _public function_ `FAudioMeterWidgetStyle& SetTypefaceFontName(const FName& InTypefaceFontName)`

#### struct `FAudioMeterDefaultColorWidgetStyle`  
`struct FAudioMeterDefaultColorWidgetStyle : public FSlateWidgetStyle`  
_L153-180_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- L157 _public prototype_ `static const FAudioMeterDefaultColorWidgetStyle& GetDefault();`
- L159 _public function_ `virtual const FName GetTypeName() const override`
- L161 _public member_ `inline static const FName TypeName = "FA`
- L164 _public member_ `FLinearColor MeterBackgroundColor = FLinearColor(0.031f, 0.031f, 0.031f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L167 _public member_ `FLinearColor MeterValueColor = FLinearColor(0.025719f, 0.208333f, 0.069907f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L170 _public member_ `FLinearColor MeterPeakColor = FLinearColor(0.24349f, 0.708333f, 0.357002f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L173 _public member_ `FLinearColor MeterClippingColor = FLinearColor::Transparent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L176 _public member_ `FLinearColor MeterScaleColor = FLinearColor(0.017642f, 0.017642f, 0.017642f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L179 _public member_ `FLinearColor MeterScaleLabelColor = FLinearColor(0.442708f, 0.442708f, 0.442708f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETSCORE_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/AudioWidgetsCoreModule.h` (Public)


#### class `FAudioWidgetsCoreModule`  
`class FAudioWidgetsCoreModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/AudioWidgetsCoreStyle.h` (Public)


#### class `FAudioWidgetsCoreStyle`  
`class FAudioWidgetsCoreStyle : public FSlateStyleSet`  
_L12-23_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for audio widgets core
- L16 _public prototype_ `static const FAudioWidgetsCoreStyle& Get();` — Access the singleton instance for this style set
- L18 _public member_ `inline static const FName StyleName = "Au`
- L21 _private prototype_ `FAudioWidgetsCoreStyle();`
- L22 _private prototype_ `~FAudioWidgetsCoreStyle();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOWIDGETSCORE_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/LoudnessMeterSettings.h` (Public)


#### struct `FLoudnessMeterDisplayOptions`  
`struct FLoudnessMeterDisplayOptions`  
_L10-28_
- reflection: `USTRUCT()`
- L15 _public member_ `bool bShowValue = false;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L18 _public member_ `bool bShowMeter = false;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L21 _public member_ `bool bHoldMaxForValue = false;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L24 _public member_ `bool bHoldMaxForMeter = false;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L27 _public member_ `FLinearColor Color = FStyleColors::AccentGreen.GetSpecifiedColor().CopyWithNewOpacity(0.5f);` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`

#### struct `FLoudnessMeterSettings`  
`struct FLoudnessMeterSettings`  
_L31-84_
- reflection: `USTRUCT()`
- L35 _public member_ `static constexpr FLinearColor DefaultLoudnessRangeColor = FLinearColor(0.631f, 0.024f, 1.0f, 0.502f);`
- L36 _public member_ `static constexpr FLinearColor DefaultTruePeakColor = FLinearColor(0.019f, 0.497f, 1.0f, 0.502f);`
- L38 _public member_ `static constexpr int32 LatestConfigVersion = 1;`
- L41 _public member_ `int32 ConfigVersion = 0;` — `UPROPERTY(config)`
- L44 _public member_ `int LoudnessScaleRange = 60;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "10", ClampMax = "70", UIMin = "10", UIMax = "70"))`
- L47 _public member_ `int LoudnessScaleOffset = 0;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "-10", ClampMax = "30", UIMin = "-10", UIMax = "30"))`
- L50 _public member_ `int LoudnessScaleTarget = -23;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "-60", ClampMax = "30", UIMin = "-60", UIMax = "30"))`
- L53 _public member_ `float TruePeakLimit = -1.0f;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "-60.0", ClampMax = "30.0", UIMin = "-60.0", UIMax = "30.0"))`
- L56 _public member_ `FLinearColor TargetColor = FStyleColors::AccentOrange.GetSpecifiedColor();` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L59 _public member_ `bool bUseRelativeLoudnessScale = false;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L62 _public member_ `bool bDisplayAnalysisTimer = true;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L65 _public member_ `FLoudnessMeterDisplayOptions LongTermLoudness = { .bShowValue = true, .bShowMeter = false };` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L68 _public member_ `FLoudnessMeterDisplayOptions ShortTermLoudness = { .bShowValue = false, .bShowMeter = true };` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L71 _public member_ `FLoudnessMeterDisplayOptions MomentaryLoudness = { .bShowValue = false, .bShowMeter = true };` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L74 _public member_ `FLoudnessMeterDisplayOptions LoudnessRange = { .bShowValue = true, .bShowMeter = false, .Color = DefaultLoudnessRangeColor };` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L77 _public member_ `FLoudnessMeterDisplayOptions TruePeak = { .bShowValue = true, .bShowMeter = false, .bHoldMaxForValue = true, .bHoldMaxForMeter = true, .Color = DefaultTruePeakColor };` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter)`
- L80 _public member_ `uint64 ValuesOrderingPermutation = 0;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "0", ClampMax = "119", UIMin = "0", UIMax = "119"))` — Max == 5! - 1
- L83 _public member_ `uint64 MetersOrderingPermutation = 0;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ClampMin = "0", ClampMax = "119", UIMin = "0", UIMax = "119"))` — Max == 5! - 1

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/LoudnessMeterWidgetView.h` (Public)


#### enum `AudioWidgetsCore::EAudioMeterMetric`  
`enum class EAudioMeterMetric : uint8`  
_L14-18_
- L16 _public enumerator_ `Loudness`
- L17 _public enumerator_ `Decibels`

#### class `AudioWidgetsCore::FLoudnessMeterWidgetView`  
`class FLoudnessMeterWidgetView`  
_L23-153_
- desc: A widget that displays various loudness metrics as numeric values and/or meters.
- L26 _public prototype_ `static FLinearColor GetDefaultMeterColor();`
- L27 _public prototype_ `static FLinearColor GetDefaultMeterColor(const FName& InLoudnessMeterName);`
- L28 _public prototype_ `static FLinearColor GetDefaultTargetColor();`
- L66 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnIntValueChanged, int32 );`
- L67 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnIntValueCommitted, int32 , ETextCommit::Type );`
- L69 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFloatValueChanged, float );`
- L70 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnFloatValueCommitted, float , ETextCommit::Type );`
- L100 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPermutationChanged, uint64 );`
- L108 _public prototype_ `FLoudnessMeterWidgetView();`
- L109 _public prototype_ `~FLoudnessMeterWidgetView();`
- L111 _public prototype_ `void InitTimerPanel(const FTimerPanelParams& InTimerPanelParams);`
- L112 _public prototype_ `void InitLoudnessScale(const FLoudnessScaleParams& InLoudnessScaleParams);`
- L113 _public prototype_ `void InitValuesDisplayOrder(const FDisplayOrderParams& InDisplayOrderParams);`
- L114 _public prototype_ `void InitMetersDisplayOrder(const FDisplayOrderParams& InDisplayOrderParams);`
- L116 _public prototype_ `TSharedRef<SWidget> MakeWidget() const;`
- L118 _public prototype_ `void AddLoudnessMetric(const FLoudnessMetric& LoudnessMetric);`
- L119 _public prototype_ `void RefreshVisibleLoudnessMetrics();`
- L122 _private typedef_ `using FLoudnessMetricRef = TSharedRef<const FLoudnessMetric>;`
- L123 _private typedef_ `using FLoudnessMetricRefArray = UE::Slate::Containers::TObservableArray<FLoudnessMetricRef>;`
- L148 _private member_ `TSharedRef<FLoudnessMetricRefArray> LoudnessMetrics;`
- L149 _private member_ `TSharedRef<FLoudnessMetricCollectionView> ValuesCollectionView;`
- L150 _private member_ `TSharedRef<FLoudnessMetricCollectionView> MetersCollectionView;`
- L151 _private member_ `FTimerPanelParams TimerPanelParams;`
- L152 _private member_ `FLoudnessScaleParams LoudnessScaleParams;`

#### struct `AudioWidgetsCore::FLoudnessMeterWidgetView::FLoudnessMetric`  
`struct FLoudnessMetric`  
_L30-55_
- L32 _public member_ `FName Name;`
- L33 _public member_ `FText DisplayName;`
- L34 _public member_ `TAttribute<EAudioMeterMetric> MeterMetric;`
- L35 _public member_ `TAttribute<TOptional<float>> Value;`
- L36 _public member_ `TAttribute<TOptional<float>> MaxValue;`
- L37 _public member_ `TAttribute<TOptional<FFloatInterval>> Range;`
- L38 _public member_ `TAttribute<bool> bShowValue = false;`
- L39 _public member_ `TAttribute<bool> bShowMeter = false;`
- L40 _public member_ `TAttribute<bool> bHoldMaxForValue = false;`
- L41 _public member_ `TAttribute<bool> bHoldMaxForMeter = false;`
- L42 _public member_ `FSimpleDelegate OnShowValueToggleRequested;`
- L43 _public member_ `FSimpleDelegate OnShowMeterToggleRequested;`
- L44 _public member_ `FSimpleDelegate OnShowValueToggleFromDragDropRequested;`
- L45 _public member_ `FSimpleDelegate OnShowMeterToggleFromDragDropRequested;`
- L46 _public member_ `FSimpleDelegate OnHoldMaxForValueToggleRequested;`
- L47 _public member_ `FSimpleDelegate OnHoldMaxForMeterToggleRequested;`
- L48 _public member_ `TAttribute<FLinearColor> Color = GetDefaultMeterColor();`
- L49 _public member_ `FOnLinearColorValueChanged OnColorChanged;`
- L50 _public member_ `FOnWindowClosed OnColorPickerWindowClosed;`
- L51 _public member_ `FSimpleDelegate OnResetColorRequested;`
- L52 _public member_ `FSimpleDelegate OnClicked;`
- L54 _public function_ `bool IsRanged() const`

#### struct `AudioWidgetsCore::FLoudnessMeterWidgetView::FTimerPanelParams`  
`struct FTimerPanelParams`  
_L57-64_
- L59 _public member_ `TAttribute<FTimespan> AnalysisTime = FTimespan::Zero();`
- L60 _public member_ `FOnClicked OnResetButtonClicked;`
- L61 _public member_ `TAttribute<bool> bIsResetButtonEnabled = true;`
- L62 _public member_ `TAttribute<bool> bIsVisible = false;`
- L63 _public member_ `FSimpleDelegate OnVisibilityToggleRequested;`

#### struct `AudioWidgetsCore::FLoudnessMeterWidgetView::FLoudnessScaleParams`  
`struct FLoudnessScaleParams`  
_L72-98_
- L74 _public member_ `TAttribute<int32> Range = 60;`
- L75 _public member_ `FOnIntValueChanged OnRangeValueChanged;`
- L76 _public member_ `FOnIntValueCommitted OnRangeValueCommitted;`
- L78 _public member_ `TAttribute<int32> Offset = 0;`
- L79 _public member_ `FOnIntValueChanged OnOffsetValueChanged;`
- L80 _public member_ `FOnIntValueCommitted OnOffsetValueCommitted;`
- L82 _public member_ `TAttribute<int32> Target = -23;`
- L83 _public member_ `FOnIntValueChanged OnTargetValueChanged;`
- L84 _public member_ `FOnIntValueCommitted OnTargetValueCommitted;`
- L87 _public member_ `TAttribute<float> TruePeakLimit = -1.0f;` — Using float here to have a more fine grained representation of true peak in dB where fractional precision matters (unlike LUFS values).
- L88 _public member_ `FOnFloatValueChanged OnTruePeakLimitValueChanged;`
- L89 _public member_ `FOnFloatValueCommitted OnTruePeakLimitValueCommitted;`
- L91 _public member_ `TAttribute<FLinearColor> TargetColor = GetDefaultTargetColor();`
- L92 _public member_ `FOnLinearColorValueChanged OnTargetColorChanged;`
- L93 _public member_ `FOnWindowClosed OnTargetColorPickerWindowClosed;`
- L94 _public member_ `FSimpleDelegate OnResetTargetColorRequested;`
- L96 _public member_ `TAttribute<bool> bRelativeScale = false;`
- L97 _public member_ `FSimpleDelegate OnRelativeScaleToggleRequested;`

#### struct `AudioWidgetsCore::FLoudnessMeterWidgetView::FDisplayOrderParams`  
`struct FDisplayOrderParams`  
_L102-106_
- L104 _public member_ `TAttribute<uint64> PermutationIndex = 0;`
- L105 _public member_ `FOnPermutationChanged OnPermutationChanged;`

#### class `AudioWidgetsCore::FLoudnessMeterWidgetView::FLoudnessMetricCollectionView`  
`class FLoudnessMetricCollectionView : public TSharedFromThis<FLoudnessMetricCollectionView>`  
_L125-146_
- inherits: `TSharedFromThis<FLoudnessMetricCollectionView>`
- L128 _public prototype_ `FLoudnessMetricCollectionView(TSharedRef<FLoudnessMetricRefArray> InLoudnessMetrics, TFunction<bool(const FLoudnessMetricRef&)> InVisibilityPredicate);`
- L130 _public function_ `void SetDisplayOrderParams(const FDisplayOrderParams& InDisplayOrderParams)`
- L131 _public prototype_ `void RefreshVisibleItems();`
- L132 _public function_ `void ResetVisibleItems()`
- L133 _public function_ `TSharedRef<FLoudnessMetricRefArray> GetVisibleItems()`
- L134 _public function_ `bool HasVisibleItems() const`
- L136 _public prototype_ `void DraggedItemReorder(const FLoudnessMetricRef& ItemDroppedOnto, bool bInsertAfter, const FLoudnessMetricRef& DragDropItem);`
- L139 _private prototype_ `static uint64 GetPermutationIndex(TArrayView<uint8> PermutationArray);`
- L140 _private prototype_ `static TArray<uint8> GetPermutationArray(uint64 PermutationIndex, uint8 NumValues);`
- L142 _private member_ `const TSharedRef<FLoudnessMetricRefArray> LoudnessMetrics;`
- L143 _private member_ `const TFunction<bool(const FLoudnessMetricRef&)> VisibilityPredicate;`
- L144 _private member_ `const TSharedRef<FLoudnessMetricRefArray> VisibleItems;`
- L145 _private member_ `FDisplayOrderParams DisplayOrderParams;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETSCORE_API`
- L12 _namespace_ `namespace AudioWidgetsCore`
- L66 _delegate_ `DECLARE_DELEGATE_OneParam(FOnIntValueChanged, int32 );`
- L67 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnIntValueCommitted, int32 , ETextCommit::Type );`
- L69 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFloatValueChanged, float );`
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnFloatValueCommitted, float , ETextCommit::Type );`
- L100 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPermutationChanged, uint64 );`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsCore/Public/SAudioMeterWidget.h` (Public)


#### class `SAudioMeterWidgetBase`  
`class SAudioMeterWidgetBase : public SLeafWidget`  
_L18-29_
- inherits: `SLeafWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SAudioMeterWidgetBase)`
- L22 _public prototype_ `SLATE_END_ARGS() virtual TArray<FAudioMeterChannelInfo> GetMeterChannelInfo() const = 0;`
- L25 _public prototype_ `virtual void SetMeterChannelInfo(const TAttribute<TArray<FAudioMeterChannelInfo>>& InMeterChannelInfo) = 0;`
- L28 _public member_ `bool bIsActiveTimerRegistered = false;` — The active timer registered to refresh the meter channel info

#### class `SAudioMeterWidget`  
`class SAudioMeterWidget : public SAudioMeterWidgetBase`  
_L34-118_
- inherits: `SAudioMeterWidgetBase`
- desc: A widget that displays audio channel's levels.
- L37 _public function_ `SLATE_BEGIN_ARGS(SAudioMeterWidget) : _Orientation(EOrientation::Orient_Horizontal) , _BackgroundColor(FLinearColor::Black) , _MeterBackgroundColor(FLinearColor::Gray) , _MeterValueColor(FLinearColor::Green) , _MeterPeakColor(FLinearColor::Blue) , _MeterClippingColor(FLinearColor::Transparent) , _MeterScaleColor(FLinearColor::White) , _MeterScaleLabelColor(FLinearColor::Gray) , _Style(&FAudioMeterWidgetStyle::GetDefault())`
- L51 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation)` — The audio meter's orientation
- L84 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L85 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L86 _public prototype_ `virtual bool ComputeVolatility() const override;`
- L88 _public prototype_ `virtual TArray<FAudioMeterChannelInfo> GetMeterChannelInfo() const override;`
- L89 _public prototype_ `virtual void SetMeterChannelInfo(const TAttribute<TArray<FAudioMeterChannelInfo>>& InMeterChannelInfo) override;`
- L91 _public prototype_ `void SetOrientation(EOrientation InOrientation);`
- L92 _public prototype_ `void SetBackgroundColor(FSlateColor InBackgroundColor);`
- L93 _public prototype_ `void SetMeterBackgroundColor(FSlateColor InMeterBackgroundColor);`
- L94 _public prototype_ `void SetMeterValueColor(FSlateColor InMeterValueColor);`
- L95 _public prototype_ `void SetMeterPeakColor(FSlateColor InMeterPeakColor);`
- L96 _public prototype_ `void SetMeterClippingColor(FSlateColor InMeterPeakColor);`
- L97 _public prototype_ `void SetMeterScaleColor(FSlateColor InMeterScaleColor);`
- L98 _public prototype_ `void SetMeterScaleLabelColor(FSlateColor InMeterScaleLabelColor);`
- L100 _public prototype_ `float GetScaleHeight() const;`
- L103 _protected member_ `const FAudioMeterWidgetStyle* Style = nullptr;`
- L106 _protected member_ `EOrientation Orientation = EOrientation::Orient_Vertical;` — Audio meter's orientation
- L109 _protected member_ `TAttribute<FSlateColor> BackgroundColor;` — Colors
- L110 _protected member_ `TAttribute<FSlateColor> MeterBackgroundColor;`
- L111 _protected member_ `TAttribute<FSlateColor> MeterValueColor;`
- L112 _protected member_ `TAttribute<FSlateColor> MeterPeakColor;`
- L113 _protected member_ `TAttribute<FSlateColor> MeterClippingColor;`
- L114 _protected member_ `TAttribute<FSlateColor> MeterScaleColor;`
- L115 _protected member_ `TAttribute<FSlateColor> MeterScaleLabelColor;`
- L117 _protected member_ `TAttribute<TArray<FAudioMeterChannelInfo>> MeterChannelInfoAttribute;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETSCORE_API`
