# Plugins / TweeningUtilsEditor

- module root: `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor`
- headers: 30; symbols: 516
- symbol kinds: class=20, delegate=7, enum=4, enumerator=16, function=89, macro=13, member=124, namespace=68, prototype=159, struct=15, typedef=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, CurveEditor, Engine, InputCore, Slate, SlateCore, TweeningUtils, UnrealEd

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Private/Misc/CommandUtils.h` (Private)


#### class `UE::TweeningUtilsEditor::FCommandChordUpListener`  
`class FCommandChordUpListener`  
_L13-13_
- L13 _public prototype_ `class FCommandChordUpListener`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L19 _prototype_ `TUniquePtr<FCommandChordUpListener> ListenForCommandChordUp(const TSharedRef<FUICommandInfo>& InCommand, FExecuteAction InAction);` (scope `UE::TweeningUtilsEditor`) — Listens for the command chord going up as there is no built-in system for this. @return Listener object. When it goes out of scope, the subscription is cleaned up.
- L20 _prototype_ `TUniquePtr<FCommandChordUpListener> ListenForCommandChordUp(const TSharedPtr<FUICommandInfo>& InCommand, FExecuteAction InAction);` (scope `UE::TweeningUtilsEditor`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Private/TweeningUtilsEditorModule.h` (Private)


#### class `UE::TweeningUtilsEditor::FTweeningUtilsEditorModule`  
`class FTweeningUtilsEditorModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Private/TweeningUtilsStyle.h` (Private)


#### class `UE::TweeningUtilsEditor::FTweeningUtilsStyle`  
`class FTweeningUtilsStyle final : public FSlateStyleSet`  
_L10-19_
- inherits: `FSlateStyleSet`
- desc: Style for the widgets and commands in this module.
- L15 _public prototype_ `static FTweeningUtilsStyle& Get();`
- L17 _public prototype_ `FTweeningUtilsStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Private/Widgets/TweenSliderDrawUtils.h` (Private)


#### struct `UE::TweeningUtilsEditor::FTweenSliderHoverState`  
`struct FTweenSliderHoverState`  
_L20-27_
- L23 _public member_ `bool bIsSliderHovered = false;` — Whether the slider button is pressed.
- L26 _public member_ `TOptional<int32> HoveredPointIndex;` — Index of FTweenSliderDrawArgs::Points that is hovered.

#### enum `UE::TweeningUtilsEditor::EPointType`  
`enum class EPointType : uint8`  
_L29-38_
- L31 _public enumerator_ `Small`
- L33 _public enumerator_ `Medium` — When overshoot mode is enabled, a bar at 100% and -100%
- L35 _public enumerator_ `End` — Left or right end
- L37 _public enumerator_ `Num`

#### struct `UE::TweeningUtilsEditor::FTweenSliderDrawArgs`  
`struct FTweenSliderDrawArgs`  
_L44-74_
- desc: Contains the basic primitives that are supposed to be drawn. This is designed to keep the drawing algorithm as straight forward as possible. This way, theoretically, we could unit test the geometry generation.
- L47 _public member_ `FGeometry BarArea;` — The black bar
- L50 _public member_ `TArray<FGeometry> Points;` — The points on the bar
- L52 _public member_ `TArray<EPointType> PointTypes;` — Equal length as Points. Used to get the right brush.
- L57 _public member_ `TBitArray<> PassedPoints;` — Indicates which of the points should be rendered as passed (i.e. the slider has moved over them): true if passed, false if not passed. Equal length as Points when dragging. 0 length if not dragging.
- L60 _public member_ `FGeometry SliderArea;` — The slider button.
- L62 _public member_ `FGeometry IconArea;` — The area of icon in the button
- L65 _public member_ `FGeometry DragValueIndication;` — This widget is shown while dragging: it draws from the center to the slider. It helps the user see how much they dragged so far.
- L68 _public member_ `bool bDrawButtonPressed = false;` — Whether to draw the button as pressed down. Can be true when bIsDragging is false (e.g. while detecting a drag).
- L70 _public member_ `bool bIsDragging = false;` — Whether the slider is being dragged. Affects whether to draw DragValueIndication and how to draw points.
- L73 _public member_ `FTweenSliderHoverState HoverState;` — Indicates the hovered element

#### struct `UE::TweeningUtilsEditor::FTweenWidgetArgs`  
`struct FTweenWidgetArgs`  
_L77-94_
- desc: The drawing relevant construction args of the widget.
- L80 _public member_ `const FTweenSliderStyle* Style;` — The style that was used to construct the widget.
- L83 _public member_ `TAttribute<FSlateColor> ColorAndOpacity;` — The root opacity of the widget.
- L86 _public member_ `TAttribute<const FSlateBrush*> SliderIconAttr;` — The icon to place in the button
- L88 _public member_ `TAttribute<FLinearColor> SliderColor;` — The main color. It tints the slider button and the points.
- L90 _public member_ `TAttribute<ETweenScaleMode> ScaleRenderModeAttr;` — Affects how the normalized values are supposed to be interpreted
- L93 _public member_ `TAttribute<TOptional<float>> OverrideSliderPositionAttr;` — If set, an indication where to position the slider. Range [-1,1]. If unset, defaults to 0. Ignored if the user is dragging the slider.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L97 _prototype_ `void GetBarGeometry(const FGeometry& AllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, FGeometry& OutBarArea);` (scope `UE::TweeningUtilsEditor`) — Gets geometry of the background bar.
- L99 _prototype_ `void GetDragValueIndicationGeometry( const FGeometry& InAllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, float InSliderPosition, FGeometry& OutDragValueIndication );` (scope `UE::TweeningUtilsEditor`) — This widget is shown while dragging: it draws from the center to the slider.
- L103 _prototype_ `void GetSliderButtonGeometry( float InNormalizedPosition, const FGeometry& InAllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, FGeometry& OutSliderArea, FGeometry& OutIconArea );` (scope `UE::TweeningUtilsEditor`) — Computes the geometry for the slider button
- L108 _prototype_ `void GetDrawnPointGeometry( const FGeometry& InAllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, const FTweenSliderHoverState& InHoverState, bool bIsMouseButtonDown, TArray<FGeometry>& OutPoints, TArray<EPointType>& OutPointTypes, TArray<float>& OutNormalizedPositions );` (scope `UE::TweeningUtilsEditor`) — Gets the drawn geometry of the points on the bar.
- L114 _prototype_ `void GetPointHitTestGeometry( const FGeometry& InAllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, TArray<FGeometry>& OutPoints, TArray<float>& OutPointSliderValues );` (scope `UE::TweeningUtilsEditor`) — Gets the point geometry for doing hit tests with.
- L119 _prototype_ `void GetPointHitTestGeometry( const FGeometry& InAllottedGeometry, const FTweenWidgetArgs& InWidgetArgs, TArray<FGeometry>& OutPoints );` (scope `UE::TweeningUtilsEditor`) — Util overload for when the caller does not care about the point values.
- L124 _prototype_ `void GetPassedPointStates(const TArray<float>& InNormalizedPositions, float InSliderPosition, TBitArray<>& OutPassedPoints);` (scope `UE::TweeningUtilsEditor`) — Computes the points that have been passed by the slider while dragging.
- L126 _prototype_ `FTweenSliderHoverState GetHoverState(const FVector2D& InMouseScreenSpace, const FGeometry& InButtonArea, const TArray<FGeometry>& InPoints);` (scope `UE::TweeningUtilsEditor`) — Computes the hover state.
- L132 _prototype_ `int32 DrawTweenSlider( const FTweenSliderDrawArgs& InDrawArgs, const FTweenWidgetArgs& InWidgetArgs, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle );` (scope `UE::TweeningUtilsEditor`) — Draws a tween slider. @return The max LayerId that was drawn onto.

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Abstraction/ITweenModelContainer.h` (Public)


#### class `UE::TweeningUtilsEditor::ITweenModelContainer`  
`class ITweenModelContainer`  
_L23-60_
- desc: This acts as the source of FTweenModels displayed in UI, e.g. by FTweenToolbarController. The implementation is expected to be a static list of tween functions, i.e. each invocation of ForEachFunction is supposed to return the same functions.
- L28 _public prototype_ `virtual void ForEachModel(const TFunctionRef<void(FTweenModel&)> InConsumer) const = 0;` — Iterates through all the functions
- L31 _public prototype_ `virtual FTweenModel* GetModel(int32 InIndex) const = 0;` — @return The function at InIndex.
- L33 _public prototype_ `virtual int32 NumModels() const = 0;` — @return The number of functions contained.
- L35 _public prototype_ `int32 IndexOf(const FTweenModel& InTweenModel) const;` — @return The index of InTweenModel if found and INDEX_NONE if not.
- L37 _public function_ `bool IsValidIndex(int32 InIndex) const` — @return Whether InIndex is a valid argument for GetFunction.
- L39 _public function_ `bool Contains(const FTweenModel& InTweenModel) const` — @return Whether InTweenModel is contained by this model.
- L42 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetCommandForModel(const FTweenModel& InTweenModel) const = 0;` — @return The command that is used to select the function
- L45 _public prototype_ `virtual const FSlateBrush* GetIconForModel(const FTweenModel& InTweenModel) const = 0;` — @return The un-tinted icon to display the function in the UI with
- L47 _public prototype_ `virtual FLinearColor GetColorForModel(const FTweenModel& InTweenModel) const = 0;` — @return The color that represents the function in the UI
- L50 _public prototype_ `virtual FText GetLabelForModel(const FTweenModel& InTweenModel) const = 0;` — @return The label to display in the combo button
- L52 _public prototype_ `virtual FText GetToolTipForModel(const FTweenModel& InTweenModel) const = 0;` — @return The description to displayed, e.g. in tool tips.
- L55 _public prototype_ `virtual FString GetModelIdentifier(const FTweenModel& InTweenModel) const = 0;` — @return Identifier that uniquely identifies this function. Used e.g. to encode the function type in a config file.
- L57 _public prototype_ `FTweenModel* FindModelByIdentifier(const FString& InIdentifier);` — @return The function identified by the InIdentifier (as returned by a call to GetFunctionIdentifier).
- L59 _public prototype_ `virtual ~ITweenModelContainer() = default;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Abstraction/KeyBlendingAbstraction.h` (Public)


#### enum `UE::TweeningUtilsEditor::EBlendFunction`  
`enum class EBlendFunction : uint8`  
_L21-47_
- desc: Util enum which is useful for UI code to abstract functions.
- L24 _public enumerator_ `BlendNeighbor` — Simple blends, i.e. signature: double(const FKeyBlendInfo&).
- L25 _public enumerator_ `PushPull`
- L26 _public enumerator_ `BlendEase`
- L27 _public enumerator_ `ControlsToTween`
- L28 _public enumerator_ `BlendRelative`
- L29 _public enumerator_ `SmoothRough`
- L32 _public enumerator_ `TimeOffset` — Complex blends
- L46 _public enumerator_ `Num` — Add new entries above.

#### enum `UE::TweeningUtilsEditor::EBreakBehavior`  
`enum class EBreakBehavior : uint8`  
_L72-72_
- L72 _public enumerator_ `enum class EBreakBehavior : uint8 { Continue, Break }; template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior`
- L72 _public enumerator_ `enum class EBreakBehavior : uint8 { Continue, Break }; template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L50 _prototype_ `FString BlendFunctionToString(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return Converts InFunction to a string
- L52 _prototype_ `TOptional<EBlendFunction> LexBlendFunction(const FString& InString);` (scope `UE::TweeningUtilsEditor`) — @return The EBlendFunction encoded by InString.
- L55 _prototype_ `TSharedPtr<FUICommandInfo> GetCommandForBlendFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The command that is used to select the function in most UI.
- L57 _prototype_ `const FSlateBrush* GetUntintedIconForTweenFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The un-tinted icon to display the function in the UI with
- L59 _prototype_ `FLinearColor GetTintColorForTweenFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The color that represents the function in the UI
- L62 _prototype_ `FText GetLabelForBlendFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The full label to display in the function with, e.g. "Push / Pull"
- L64 _prototype_ `FText GetAbbreviationForBlendFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The short label to display in the function with, e.g. "PP" (for Push / Pull)
- L66 _prototype_ `FText GetDescriptionForBlendFunction(EBlendFunction InFunction);` (scope `UE::TweeningUtilsEditor`) — @return The description of the function
- L70 _prototype_ `template<typename TCallback> requires std::is_invocable_v<TCallback, EBlendFunction> void ForEachBlendFunction(TCallback&& InCallback);` (scope `UE::TweeningUtilsEditor`) — Iterates through all blend function types.
- L75 _prototype_ `template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, EBlendFunction> void ForEachBlendFunctionBreakable(TCallback&& InCallback);` (scope `UE::TweeningUtilsEditor`) — Iterates through all blend function types with the ability to break.
- L78 _namespace_ `namespace UE`
- L78 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L81 _function_ `template<typename TCallback> requires std::is_invocable_v<TCallback, EBlendFunction> void ForEachBlendFunction(TCallback&& InCallback)` (scope `UE::TweeningUtilsEditor`)
- L84 _function_ `` (scope `UE::TweeningUtilsEditor::ForEachBlendFunction`)
- L89 _function_ `template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, EBlendFunction> void ForEachBlendFunctionBreakable(TCallback&& InCallback)` (scope `UE::TweeningUtilsEditor`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Abstraction/TweenModelArray.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweenModelArray`  
`class FTweenModelArray : public ITweenModelContainer, public FNoncopyable`  
_L15-37_
- inherits: `ITweenModelContainer,FNoncopyable`
- desc: Backed by an array of tween models and their UI info.
- L19 _public function_ `explicit FTweenModelArray(TArray<FTweenModelUIEntry> InTweenModels) : TweenModels(MoveTemp(InTweenModels))`
- L22 _public prototype_ `virtual void ForEachModel(const TFunctionRef<void(FTweenModel&)> InConsumer) const override;`
- L23 _public prototype_ `virtual FTweenModel* GetModel(int32 InIndex) const override;`
- L24 _public function_ `virtual int32 NumModels() const override`
- L25 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetCommandForModel(const FTweenModel& InTweenModel) const override;`
- L26 _public prototype_ `virtual const FSlateBrush* GetIconForModel(const FTweenModel& InTweenModel) const override;`
- L27 _public prototype_ `virtual FLinearColor GetColorForModel(const FTweenModel& InTweenModel) const override;`
- L28 _public prototype_ `virtual FText GetLabelForModel(const FTweenModel& InTweenModel) const override;`
- L29 _public prototype_ `virtual FText GetToolTipForModel(const FTweenModel& InTweenModel) const override;`
- L30 _public prototype_ `virtual FString GetModelIdentifier(const FTweenModel& InTweenModel) const override;`
- L36 _private member_ `const TArray<FTweenModelUIEntry> TweenModels;` — Info about the contained tween models.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Abstraction/TweenModelDisplayInfo.h` (Public)


#### struct `UE::TweeningUtilsEditor::FTweenModelDisplayInfo`  
`struct FTweenModelDisplayInfo`  
_L21-52_
- desc: Information about how a FTweenModel can be displayed in the UI.
- L23 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L24 _public member_ `const FSlateBrush* Brush;`
- L25 _public member_ `FLinearColor Color;`
- L26 _public member_ `FText Label;`
- L27 _public member_ `FText ToolTip;`
- L28 _public member_ `FString Identifier;`
- L30 _public function_ `explicit FTweenModelDisplayInfo( TSharedPtr<FUICommandInfo> Command, const FSlateBrush* Brush, const FLinearColor& Color, const FText& Label, const FText& ToolTip, const FString& Identifier ) : Command(MoveTemp(Command)) , Brush(Brush) , Color(Color) , Label(Label) , ToolTip(ToolTip) , Identifier(Identifier)`
- L42 _public function_ `explicit FTweenModelDisplayInfo(EBlendFunction InBlendFunction) : FTweenModelDisplayInfo( GetCommandForBlendFunction(InBlendFunction), GetUntintedIconForTweenFunction(InBlendFunction), GetTintColorForTweenFunction(InBlendFunction), GetLabelForBlendFunction(InBlendFunction), GetDescriptionForBlendFunction(InBlendFunction), BlendFunctionToString(InBlendFunction) )`

#### struct `UE::TweeningUtilsEditor::FTweenModelUIEntry`  
`struct FTweenModelUIEntry : FNoncopyable`  
_L55-64_
- inherits: `FNoncopyable`
- desc: An association between a tween model and its UI display info. Useful for backing some UI, e.g. like combo button selection list.
- L57 _public member_ `TUniquePtr<FTweenModel> TweenModel;`
- L58 _public member_ `FTweenModelDisplayInfo DisplayInfo;`
- L60 _public function_ `explicit FTweenModelUIEntry(TUniquePtr<FTweenModel> TweenModel, FTweenModelDisplayInfo DisplayInfo) : TweenModel(MoveTemp(TweenModel)) , DisplayInfo(MoveTemp(DisplayInfo))`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Abstraction/TweenRangeTemplates.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L24 _prototype_ `template<EBlendFunction> double TweenRange( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex );` (scope `UE::TweeningUtilsEditor`) — Interface for applying "simple" blend function to range of keys. Template specializations extract the required parameters and passes them to the underlying blend function. This pattern is only possible with "simple" blend functions, i.e. those that only have the generic parameters described in KeyBlendingFunctions.h. For these simple functions, all you need to do is specialize TweenRange and your function should then show up automatically, provided tools are using ForEachCurveTweenable to go discover tween simple functions. Some blend functions may require more arguments. For example, time offsetting / shifting would require caching underlying FCurveModel to be able to evaluate arbitrary function values between the keys, etc.
- L34 _prototype_ `constexpr bool SupportsTweenRange(EBlendFunction BlendFunction);` (scope `UE::TweeningUtilsEditor`) — @return Whether this EBlendFunction supports simple tweening by using TweenRange. Some blend functions require more arguments, like a cached curve, etc.
- L36 _prototype_ `constexpr int32 NumBlendFunctionsSupportingTweenRange();` (scope `UE::TweeningUtilsEditor`) — @return Number of functions for which SupportsTweenRange returns true.
- L43 _prototype_ `template <typename TCallback> constexpr void ForEachCurveTweenable(TCallback&& InCallback);` (scope `UE::TweeningUtilsEditor`) — Invokes InCallback for each EBlendFunction that TCurveTweener can be instantiated with. InCallback must be a templated lambda, e.g. []<EBlendFunction Function>(){}.
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L48 _function_ `constexpr bool SupportsTweenRange(EBlendFunction BlendFunction)` (scope `UE::TweeningUtilsEditor`)
- L69 _function_ `constexpr int32 NumBlendFunctionsSupportingTweenRange()` (scope `UE::TweeningUtilsEditor`)
- L83 _function_ `template<> inline double TweenRange<EBlendFunction::ControlsToTween>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex` (scope `UE::TweeningUtilsEditor`)
- L95 _function_ `template<> inline double TweenRange<EBlendFunction::PushPull>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex )` (scope `UE::TweeningUtilsEditor`)
- L110 _function_ `template<> inline double TweenRange<EBlendFunction::BlendNeighbor>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex )` (scope `UE::TweeningUtilsEditor`)
- L125 _function_ `template<> inline double TweenRange<EBlendFunction::BlendRelative>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex )` (scope `UE::TweeningUtilsEditor`)
- L142 _function_ `template<> inline double TweenRange<EBlendFunction::BlendEase>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex )` (scope `UE::TweeningUtilsEditor`)
- L157 _function_ `template<> inline double TweenRange<EBlendFunction::SmoothRough>( double InBlendValue, const FBlendRangesData& AllBlendedKeys, const FContiguousKeys& CurrentBlendRange, int32 InCurrentKeyIndex )` (scope `UE::TweeningUtilsEditor`)
- L172 _function_ `template <typename TCallback> constexpr void ForEachCurveTweenable(TCallback&& InCallback)` (scope `UE::TweeningUtilsEditor`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/ContiguousKeyMapping.h` (Public)


#### struct `UE::TweeningUtilsEditor::FContiguousKeys`  
`struct FContiguousKeys`  
_L19-33_
- desc: Unbroken chain of keys.
- L22 _public member_ `const TArray<int32> Indices;` — Indices of keys to blend
- L24 _public member_ `const int32 PreviousIndex = INDEX_NONE;` — The index of the key before Indices[0]. INDEX_NONE if there is no previous key.
- L26 _public member_ `const int32 NextIndex = INDEX_NONE;` — The index of the key after Indidces' last element. INDEX_NONE if there is no next key.
- L28 _public function_ `explicit FContiguousKeys(const TArray<FVector2d>& InAllKeyPositions, const TArray<int32>& InContiguousKeyIndices) : Indices(InContiguousKeyIndices) , PreviousIndex(InAllKeyPositions.IsValidIndex(Indices[0] - 1) ? Indices[0] - 1 : INDEX_NONE) , NextIndex(InAllKeyPositions.IsValidIndex(Indices[Indices.Num() -1] + 1) ? Indices[Indices.Num() -1] + 1 : INDEX_NONE)`

#### struct `UE::TweeningUtilsEditor::FBlendRangesData`  
`struct FBlendRangesData`  
_L39-80_
- desc: Stores all key positions as they were before the blend, and all the chains of keys that are supposed to be blended. You can use this type independently from FContiguousKeyMapping. For example, you can use this to call TweeningUtilsEditor::TweenRange directly.
- L41 _public member_ `const TArray<FVector2d> AllKeyPositions;`
- L50 _public member_ `TArray<FContiguousKeys> KeysArray;` — The user selected keys split up into consecutive ranges. Let 'x' denote keys selected by the user and '.' keys not selected. Suppose the user selection was '.xx...xxx.', i.e. the user selected keys and then shift+selected additional keys somewhere else on the curve. Then this array would contain indices of the two ranges 'xx' and 'xxx' is not a blendable range.
- L52 _public function_ `explicit FBlendRangesData(const TArray<FVector2d>& InAllKeyPositions) : AllKeyPositions(InAllKeyPositions)`
- L55 _public prototype_ `const FVector2d& GetBeforeBlendRange(const FContiguousKeys& InKeys) const;` — @return The key before the blend range defined by InKeys
- L57 _public prototype_ `const FVector2D& GetFirstInBlendRange(const FContiguousKeys& InKeys) const;` — @retuirn The first key that is blended in the specified range.
- L63 _public prototype_ `const FVector2D& GetBeforeCurrent(const FContiguousKeys& InKeys, int32 InIndex) const;` — @param InIndex Index to InKeys.Indices. @return Gets the key before the currently blended key. If the current key is the first in the blend range, this returns GetBeforeBlendRange.
- L67 _public prototype_ `const FVector2D& GetCurrent(const FContiguousKeys& InKeys, int32 InIndex) const;` — @param InIndex Index to InKeys.Indices. @return AllKeyPositions[Indices[Index]]
- L72 _public prototype_ `const FVector2D& GetAfterCurrent(const FContiguousKeys& InKeys, int32 InIndex) const;` — @param InIndex Index to InKeys.Indices. @return Gets the key after the currently blended key. If the current key is the last in the blend range, this returns GetAfterBlendRange.
- L75 _public prototype_ `const FVector2D& GetLastInBlendRange(const FContiguousKeys& InKeys) const;` — @retuirn The last key that is blended in the specified range.
- L77 _public prototype_ `const FVector2d& GetAfterBlendRange(const FContiguousKeys& InKeys) const;` — @return The key after the blend range defined by InKeys
- L79 _public prototype_ `void AddBlendRange(const TArray<int32>& InContiguousKeyIndices);`
- L108 _function_ `inline const FVector2d& FBlendRangesData::GetBeforeBlendRange(const FContiguousKeys& InKeys) const`
- L114 _function_ `inline const FVector2D& FBlendRangesData::GetFirstInBlendRange(const FContiguousKeys& InKeys) const`
- L119 _function_ `inline const FVector2D& FBlendRangesData::GetBeforeCurrent(const FContiguousKeys& InKeys, int32 InIndex) const`
- L124 _function_ `inline const FVector2D& FBlendRangesData::GetCurrent(const FContiguousKeys& InKeys, int32 InIndex) const`
- L129 _function_ `inline const FVector2D& FBlendRangesData::GetAfterCurrent(const FContiguousKeys& InKeys, int32 InIndex) const`
- L134 _function_ `inline const FVector2D& FBlendRangesData::GetLastInBlendRange(const FContiguousKeys& InKeys) const`
- L139 _function_ `inline const FVector2d& FBlendRangesData::GetAfterBlendRange(const FContiguousKeys& InKeys) const`

#### struct `UE::TweeningUtilsEditor::FContiguousKeyMapping`  
`struct FContiguousKeyMapping`  
_L83-103_
- desc: Information for blending a map of curves and the keys in it to blend. Saves the old key values for the duration of the blend.
- L96 _public prototype_ `FContiguousKeyMapping() = default;`
- L97 _public prototype_ `explicit FContiguousKeyMapping(const FCurveEditor& InCurveEditor);`
- L100 _public prototype_ `void Append(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeysToBlend);` — Appends keys from the given curve.
- L102 _public member_ `TMap<FCurveModelID, FContiguousKeysArray> KeyMap;`

#### struct `UE::TweeningUtilsEditor::FContiguousKeyMapping::FContiguousKeysArray`  
`struct FContiguousKeysArray : FBlendRangesData`  
_L86-94_
- inherits: `FBlendRangesData`
- desc: Holds the corresponding key handles for all the keys.
- L88 _public member_ `const TArray<FKeyHandle> AllKeyHandles;`
- L90 _public function_ `explicit FContiguousKeysArray(const TArray<FKeyHandle>& InAllKeyHandles, const TArray<FVector2d>& InAllKeyPositions) : FBlendRangesData(InAllKeyPositions) , AllKeyHandles(InAllKeyHandles)`
- L93 _public prototype_ `void AddBlendRange(const TArray<int32>& ContiguousKeyIndices);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L106 _namespace_ `namespace UE`
- L106 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/CurveBlending.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L27 _prototype_ `template<CBlendKeyCallable TCallback> bool BlendCurves_BySingleKey(const FCurveEditor& InCurveEditor, const FContiguousKeyMapping& InKeySelection, TCallback&& InBlendKeyCallback);` (scope `UE::TweeningUtilsEditor`) — Blends the specified keys by using a InBlendKeyCallback, which returns the new key value each key should have.
- L48 _prototype_ `template<CBlendRangeCallback TCallback> bool BlendCurve_ByKeyRange(const FCurveEditor& InCurveEditor, const FContiguousKeyMapping& InKeySelection, TCallback&& InBlendRangeCallback);` (scope `UE::TweeningUtilsEditor`) — Generic helper function that invokes InBlendRangeCallback for each unbroken sub-range of keys in each curve. @return Whether any key value was changed.
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L54 _function_ `template <CBlendKeyCallable TCallback> bool BlendCurves_BySingleKey(const FCurveEditor& InCurveEditor, const FContiguousKeyMapping& InKeySelection, TCallback&& InBlendKeyCallback)` (scope `UE::TweeningUtilsEditor`)
- L62 _function_ `` (scope `UE::TweeningUtilsEditor::BlendCurves_BySingleKey`)
- L77 _function_ `template<CBlendRangeCallback TCallback> bool BlendCurve_ByKeyRange(const FCurveEditor& InCurveEditor, const FContiguousKeyMapping& InKeySelection, TCallback&& InBlendRangeCallback)` (scope `UE::TweeningUtilsEditor`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/CurveTimeOffsetTweenModel.h` (Public)


#### class `UE::TweeningUtilsEditor::FCurveTimeOffsetTweenModel`  
`class FCurveTimeOffsetTweenModel : public FTweenModel, public FNoncopyable`  
_L19-41_
- inherits: `FTweenModel,FNoncopyable`
- desc: Recomputes all keys output values such that the curve is effectively shifted to left and right without modifying the keys' input values.
- L23 _public prototype_ `explicit FCurveTimeOffsetTweenModel(TAttribute<TWeakPtr<FCurveEditor>> InWeakCurveEditor);`
- L26 _public prototype_ `virtual void StartBlendOperation() override;`
- L27 _public prototype_ `virtual void StopBlendOperation() override;`
- L28 _public prototype_ `virtual void BlendValues(float InNormalizedValue) override;`
- L34 _protected member_ `const TAttribute<TWeakPtr<FCurveEditor>> WeakCurveEditor;` — The curve editor on which to tween the curves.
- L37 _protected member_ `FContiguousKeyMapping ContiguousKeySelection;` — Created in StartBlendOperation and used for the entirety of the blend operation.
- L40 _protected member_ `TMap<FCurveModelID, TUniquePtr<IBufferedCurveModel>> OriginalBlendedCurves;` — The state of the curves before they were blended. Created in StartBlendOperation. Used to evaluate original curve value during time shift.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/CurveTweenModel.h` (Public)


#### class `UE::TweeningUtilsEditor::TCurveTweenModel`  
`template<EBlendFunction Func> class TCurveTweenModel : public FTweenModel`  
_L18-41_
- inherits: `FTweenModel`
- desc: Tweens the curves of the curve editor's selection.
- L20 _private prototype_ `static_assert(SupportsTweenRange(Func), "Thi`
- L23 _public prototype_ `explicit TCurveTweenModel(TWeakPtr<FCurveEditor> InWeakCurveEditor);`
- L26 _public prototype_ `bool HasAnythingToBlend() const;` — @return Whether it makes sense to call StartBlendOperation, etc.
- L29 _public prototype_ `virtual void StartBlendOperation() override;`
- L30 _public prototype_ `virtual void StopBlendOperation() override;`
- L31 _public prototype_ `virtual void BlendValues(float InNormalizedValue) override;`
- L37 _protected member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — The curve editor on which to tween the curves.
- L40 _protected member_ `FContiguousKeyMapping ContiguousKeySelection;` — Created in StartBlendOperation and used for the entirety of the blend operation.
- L47 _function_ `template <EBlendFunction BlendFunction> TCurveTweenModel<BlendFunction>::TCurveTweenModel(TWeakPtr<FCurveEditor> InWeakCurveEditor) : WeakCurveEditor(MoveTemp(InWeakCurveEditor))`
- L52 _function_ `template <EBlendFunction BlendFunction> bool TCurveTweenModel<BlendFunction>::HasAnythingToBlend() const`
- L59 _function_ `template <EBlendFunction BlendFunction> void TCurveTweenModel<BlendFunction>::StartBlendOperation()`
- L66 _function_ `template <EBlendFunction BlendFunction> void TCurveTweenModel<BlendFunction>::StopBlendOperation()`
- L74 _function_ `template <EBlendFunction BlendFunction> void TCurveTweenModel<BlendFunction>::BlendValues(float InNormalizedValue)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L89 _function_ `` (scope `UE::TweeningUtilsEditor::TCurveTweenModel::BlendValues`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/EditorTweenModel.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L27 _typedef_ `template<typename TUnderlyingModel> requires std::is_base_of_v<FTweenModel, TUnderlyingModel> using TEditorTweenModel = TTransactionalTweenModelProxy<TTangentFlatteningTweenProxy<TUnderlyingModel>>;` (scope `UE::TweeningUtilsEditor`) — Extends TUnderlyingModel with commonly expected shared functionality: - Undo / redo - As the tween function squishes the keys vertically, user-specified tangents are flattened. - In the future this can be extended to remove vertically stacked keys (same keys per frame). For now, no implemented tween function stack keys. Construct like this: using FModel = TEditorTweenModel<FFooTweenModel> // FFooTweenModel should inherit from FTweenModel. const TSharedRef<FModel> TweenModel = MakeShared<FModel>( WeakCurveEditor,							// TTangentFlatteningTweenProxy arg Bar											// Any arguments that FFooTweenModel requires for construction );

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/TangentFlatteningTweenProxy.h` (Public)


#### class `UE::TweeningUtilsEditor::TTangentFlatteningTweenProxy`  
`template<typename TBase> requires std::is_base_of_v<FTweenModel, TBase> class TTangentFlatteningTweenProxy : public TBase`  
_L20-72_
- inherits: `TBase`
- desc: This class squishes the curves based on how much the tween function squishes the keys vertically. The squishing is achieved by interpolating the tangents to 0.
- L25 _public function_ `template<typename... TArg> explicit TTangentFlatteningTweenProxy(TAttribute<TWeakPtr<FCurveEditor>> WeakCurveEditorAttr, TArg&&... Arg) : TBase(Forward<TArg>(Arg)...) , WeakCurveEditor(MoveTemp(WeakCurveEditorAttr))`
- L33 _public function_ `virtual void StartBlendOperation() override`
- L43 _public function_ `virtual void BlendValues(float InNormalizedValue) override`
- L67 _private member_ `const TAttribute<TWeakPtr<FCurveEditor>> WeakCurveEditor;` — Needed as arg for TangentTweener.
- L69 _private member_ `CurveEditor::FTangentSelectionFlattener TangentTweener;` — Implements the logic for flattening tangents of consecutive keys.
- L71 _private member_ `CurveEditor::FTangentSingleKeyFlattener SingleKeyTangentTweener;` — Implements logic for flattening tangents of single keys

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/TransactionalTweenModelProxy.h` (Public)


#### class `UE::TweeningUtilsEditor::TTransactionalTweenModelProxy`  
`template<typename TBase> requires std::is_base_of_v<FTweenModel, TBase> class TTransactionalTweenModelProxy : public TBase`  
_L23-59_
- inherits: `TBase`
- desc: Starts a transaction in StartBlendOperation, stops it in StopBlendOperation.
- L28 _public function_ `template<typename... TArg> explicit TTransactionalTweenModelProxy(TAttribute<TWeakPtr<FCurveEditor>> InCurveEditorAttr, TArg&&... Arg) : TBase(Forward<TArg>(Arg)...) , CurveEditorAttr(MoveTemp(InCurveEditorAttr))`
- L34 _public function_ `virtual void StartBlendOperation() override`
- L45 _public function_ `virtual void StopBlendOperation() override`
- L55 _private member_ `const TAttribute<TWeakPtr<FCurveEditor>> CurveEditorAttr;` — Used to detect key changes.
- L58 _private member_ `TOptional<CurveEditor::FScopedCurveChange> InProgressTransaction;` — Active during a blend operation.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Math/Models/TweenModel.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweenModel`  
`class FTweenModel`  
_L13-62_
- desc: Implements the logic of tweening some values: it could be curves, it could be control rig models. Acts as model in a Model-View-Controller architecture.
- L18 _public function_ `virtual void StartBlendOperation()` — Called when a blend operation is started.
- L20 _public function_ `virtual void StopBlendOperation()` — Called when a blend operation is stopped.
- L25 _public prototype_ `virtual void BlendValues(float InNormalizedValue) = 0;` — Does the blending based on the InNormalizedValue. @param InNormalizedValue Value in [-1, 1]
- L31 _public function_ `void BlendOneOff(float InNormalizedValue)` — Blends to a single value once. @param InNormalizedValue Value in [-1, 1]
- L38 _public function_ `virtual void SetScaleMode(ETweenScaleMode InMode)`
- L39 _public function_ `ETweenScaleMode GetScaleMode() const`
- L45 _public function_ `float ScaleBlendValue(float InNormalizedValue) const` — @param InNormalizedValue Value from -1 to 1. @return Value scaled according to the ScaleMode setting.
- L52 _public prototype_ `virtual ~FTweenModel() = default;`
- L61 _private member_ `ETweenScaleMode ScaleMode = ETweenScaleMode::Normalized;` — Affects how normalized values sent to BlendValueNormalizedAndRecomputeKeys are interpreted: - False: -1.0 to 1.0 maps to -100% to +100% - True: -1.0 to 1.0 maps to -200% to +200%

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/TweeningToolsUserSettings.h` (Public)


#### class `UTweeningToolsUserSettings`  
`class UTweeningToolsUserSettings : public UObject`  
_L14-39_
- reflection: `UCLASS(MinimalAPI, Config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L19 _public prototype_ `static UTweeningToolsUserSettings* Get();`
- L22 _public function_ `void SetPreferredTweenFunction(FName InFeatureKey, FString InNewPreferredFunction)` — Sets the preferred tween function for the given feature.
- L28 _public function_ `const FString* GetPreferredTweenFunction(FName InFeatureKey) const` — Gets the preferred tween function for the given feature, if there is any.
- L38 _private member_ `TMap<FName, FString> PreferredTweenFunction;` — `UPROPERTY(Config)` — Associates features with the preferred function in that feature. If you want multiple locations in the editor to share the same setting, use the same key. This tween function should be selected by default when a curve editor is created. It is the function that was used last time in the editor.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/TweeningUtilsCommands.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweeningUtilsCommands`  
`class FTweeningUtilsCommands : public TCommands<FTweeningUtilsCommands>`  
_L9-45_
- inherits: `TCommands<FTweeningUtilsCommands>`
- L13 _public member_ `TSharedPtr<FUICommandInfo> SetControlsToTween;`
- L14 _public member_ `TSharedPtr<FUICommandInfo> SetTweenPushPull;`
- L15 _public member_ `TSharedPtr<FUICommandInfo> SetTweenBlendNeighbor;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> SetTweenBlendRelative;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> SetTweenBlendEase;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> SetTweenSmoothRough;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> SetTweenTimeOffset;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ToggleOvershootMode;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> DragAnimSliderTool;` — Triggers detection of mouse movement to drive the slider indirectly.
- L25 _public member_ `TSharedPtr<FUICommandInfo> ChangeAnimSliderTool;` — Cycles to the next tween functions
- L28 _public member_ `TSharedPtr<FUICommandInfo> SetSliderLeft;` — Positions the slider 100% to the left as if you had dragged it there.
- L30 _public member_ `TSharedPtr<FUICommandInfo> SetSliderRight;` — Positions the slider 100% to the right as if you had dragged it there.
- L32 _public member_ `TSharedPtr<FUICommandInfo> SetSliderHalfLeft;` — Positions the slider 50% to the left as if you had dragged it there.
- L34 _public member_ `TSharedPtr<FUICommandInfo> SetSliderHalfRight;` — Positions the slider 50% to the right as if you had dragged it there.
- L36 _public member_ `TSharedPtr<FUICommandInfo> SetSliderQuarterLeft;` — Positions the slider 25% to the left as if you had dragged it there.
- L38 _public member_ `TSharedPtr<FUICommandInfo> SetSliderQuarterRight;` — Positions the slider 25% to the right as if you had dragged it there.
- L40 _public prototype_ `FTweeningUtilsCommands();`
- L43 _public prototype_ `virtual void RegisterCommands() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/TweeningUtilsStyle.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweeningUtilsStyle`  
`class FTweeningUtilsStyle final : public FSlateStyleSet`  
_L10-19_
- inherits: `FSlateStyleSet`
- desc: Style for the widgets and commands in this module.
- L15 _public prototype_ `static FTweeningUtilsStyle& Get();`
- L17 _public prototype_ `FTweeningUtilsStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/ETweenScaleMode.h` (Public)


#### enum `UE::TweeningUtilsEditor::ETweenScaleMode`  
`enum class ETweenScaleMode : uint8`  
_L10-16_
- desc: Affects how blend values, which are normalized to the range -1.0 to 1.0, are interpreted.
- L13 _public enumerator_ `Normalized` — -1.0 to 1.0 maps to -100% to +100%
- L15 _public enumerator_ `Overshoot` — -1.0 to 1.0 maps to -200% to +200%

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/CycleFunctionController.h` (Public)


#### class `UE::TweeningUtilsEditor::FCycleFunctionController`  
`class FCycleFunctionController : public FNoncopyable`  
_L21-73_
- inherits: `FNoncopyable`
- desc: Cycles through functions on a tween model.
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FHandleTweenChange, FTweenModel&);`
- L34 _public prototype_ `explicit FCycleFunctionController( TAttribute<const FTweenModel*> InCurrentTweenModelAttr, const TSharedRef<ITweenModelContainer>& InTweenModelContainer, FHandleTweenChange InHandleTweenChange, const TSharedRef<FUICommandList>& InCommandList, TSharedPtr<FUICommandInfo> InCycleCommand );` — @param InCurrentTweenModelAttr The tween model that is currently selected. @param InTweenModelContainer Determines the functions through which you can cycle @param InHandleTweenChange Invoked to change the current tween function @param InCommandList The command list to add / remove the command to / from. @param InCycleCommand The command that cycles the function
- L48 _public prototype_ `virtual ~FCycleFunctionController();`
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFunctionCycled);`
- L52 _public function_ `FOnFunctionCycled& OnFunctionCycleCommandInvoked()` — Invoked when CycleCommand is invoked.
- L57 _private member_ `const TAttribute<const FTweenModel*> CurrentTweenModelAttr;` — The tween model that is currently selected
- L59 _private member_ `const TSharedRef<ITweenModelContainer> TweenModelContainer;` — Holds the functions that can be cycled through.
- L61 _private member_ `const FHandleTweenChange HandleTweenChangeDelegate;` — Invoked to change the current tween function
- L64 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Used to bind and unbind the CycleCommand command.
- L66 _private member_ `const TSharedPtr<FUICommandInfo> CycleCommand;` — Invokes CycleToNextFunction.
- L69 _private member_ `FOnFunctionCycled OnFunctionCycleCommandInvokedDelegate;` — Invoked when CycleCommand is invoked.
- L72 _private prototype_ `void CycleToNextFunction() const;` — Sets the next tween function.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FHandleTweenChange, FTweenModel&);`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFunctionCycled);`

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/MouseSlidingController.h` (Public)


#### class `UE::TweeningUtilsEditor::FMouseSlidingController`  
`class FMouseSlidingController : public FNoncopyable`  
_L40-121_
- inherits: `FNoncopyable`
- desc: Generic controller that allows you to move the mouse while a command is pressed. The sliding value is normalized to [-1,1] depending on whether the mouse was moved left or right. The user must first press down the key chord for DragSliderCommand, and then the LMB. The user can press and release LMB multiple times while DragSliderCommand's key chord is pressed down. During sliding, the mouse is locked to the rect of the virtual slider: the area around where the user started dragging. This is intended to give the user feedback when they've moved the mouse far enough to reach -1 or 1. Example: - Suppose MaxSlideWidthAttr returns 200, and that InDragSliderCommand is bound to U. - The user presses U and moves the mouse - to right by 50 Slate units > OnSliderMovedDelegate is invoked with is 0.5. - to the right by 125 Slate units (exceeds the max sliding by 25 units) > OnSliderMovedDelegate is invoked with 1.0 (clamped). - to the left by 25 Slate units > OnSliderMovedDelegate is invoked with -0.25.
- L50 _public prototype_ `FMouseSlidingController( TAttribute<float> InMaxSlideWidthAttr, const TSharedRef<FUICommandList>& InCommandList, TSharedPtr<FUICommandInfo> InDragSliderCommand );` — @param InMaxSlideWidthAttr The total size of the "invisible" slider. The mouse can be moved left and right InMaxSlideWidthAttr.Get / 2.0 before being clamped. @param InCommandList The command list to add / remove the command to / from. @param InDragSliderCommand The command that triggers detection of mouse movement.
- L55 _public prototype_ `virtual ~FMouseSlidingController();`
- L58 _public prototype_ `void BindCommand();` — Starts listening for the mouse sliding command.
- L60 _public prototype_ `void UnbindCommand() const;` — Stops listening for the mouse sliding command.
- L63 _public function_ `bool IsSliding() const` — @return Whether the slider operation is currently in progress.
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMoveSliderDelegate, float );`
- L67 _public function_ `FMoveSliderDelegate& OnUpdateSliding()` — Invoked every tick the slider is moved. The event is throttled, so there's at most one invocation per tick.
- L69 _public function_ `FSimpleMulticastDelegate& OnStartSliding()` — Invoked when sliding starts.
- L71 _public function_ `FSimpleMulticastDelegate& OnStopSliding()` — Invoked when sliding stops.
- L75 _protected function_ `const TSharedRef<FUICommandList>& GetCommandList() const`
- L80 _private member_ `const TAttribute<float> MaxSlideWidthAttr;` — The total size of the "invisible" slider. The mouse can be moved left and right by MaxSlideWidthAttr.Get() / 2.0 before being clamped.
- L83 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Used to bind and unbind the DragSliderCommand command.
- L85 _private member_ `const TSharedPtr<FUICommandInfo> DragSliderCommand;` — The command must be pressed down to start sliding. You also need to press LMB to start sliding.
- L101 _private member_ `TOptional<FSlidingState> SlidingState;` — Set while listening for mouse events, unset while not sliding.
- L104 _private member_ `FMoveSliderDelegate OnUpdateSlidingDelegate;` — Invoked every tick the slider is moved. The event is throttled, so there's at most one invocation per tick.
- L106 _private member_ `FSimpleMulticastDelegate OnStartSlidingDelegate;` — Invoked when sliding starts.
- L108 _private member_ `FSimpleMulticastDelegate OnStopSlidingDelegate;` — Invoked when sliding stops.
- L111 _private prototype_ `void StartListeningForMouseEvents();` — Once DragSliderCommand has triggered, start listening for mouse down events.
- L113 _private prototype_ `void StopListeningForMouseEvents(ICursor& InCursor);` — Once DragSliderCommand is released, stop listening for mouse down events.
- L116 _private prototype_ `void StartSliding(const FVector2D& InInitialScreenLocation, ICursor& InCursor);` — Starts sliding from mouse position and locks the mouse; emits OnUpdateSliding calls. Called once DragSliderCommand and LMB are both down.
- L118 _private prototype_ `void StopSliding(ICursor& InCursor);` — Stops emiting emitting OnUpdateSliding calls. Unlocks the cursor. Called once either DragSliderCommand or LMB are released.
- L120 _private prototype_ `void UpdateSliding(const FVector2D& InScreenLocation);` — Emits a OnUpdateSliding call. Called once per frame while sliding is active.

#### struct `UE::TweeningUtilsEditor::FMouseSlidingController::FSlidingState`  
`struct FSlidingState`  
_L87-99_
- L90 _public member_ `const TSharedRef<FMouseSlidingInputProcessor> InputProcessor;` — Listens for DragSliderCommand and LMB going up. Orchestrates calls to StartSliding, StopSliding, and UpdateSliding.
- L92 _public member_ `TOptional<FVector2D> InitialMouse;` — Set while sliding is active. Unset while inactive.
- L94 _public prototype_ `explicit FSlidingState(FMouseSlidingController& InOwner);`
- L95 _public prototype_ `~FSlidingState();`
- L98 _public function_ `bool IsSliding() const` — @return Whether sliding is currently active.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMoveSliderDelegate, float );`

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/MoveSliderByHotkeyController.h` (Public)


#### class `UE::TweeningUtilsEditor::FMoveSliderByHotkeyController`  
`class FMoveSliderByHotkeyController : public FNoncopyable`  
_L26-53_
- inherits: `FNoncopyable`
- desc: Allows the user to move the slider - 100% to the left (FTweeningUtilsCommands::SetSliderLeft) - 100% to the right (FTweeningUtilsCommands::SetSliderRight) while indirectly moving the slider (@see FTweeningUtilsCommands::DragAnimSliderTool).
- L30 _public prototype_ `explicit FMoveSliderByHotkeyController(TAttribute<FTweenModel*> InTweenModelAttr, const TSharedRef<FUICommandList>& InCommandList);`
- L31 _public prototype_ `~FMoveSliderByHotkeyController();`
- L34 _public prototype_ `TOptional<float> GetCurrentSliderPosition() const;` — @return The current slider position that is being driven by the active command. Range [-1,1].
- L39 _private member_ `const TAttribute<FTweenModel*> TweenModelAttr;` — Does the actual blending.
- L42 _private member_ `const TWeakPtr<FUICommandList> WeakCommandList;` — The command list that the commands are bound to.
- L46 _private member_ `TPimplPtr<FActiveCommandOverride> ActiveCommand;` — Set while one of the commands is pressed down. Becomes unset when the command chord goes up.
- L49 _private prototype_ `void HandleMoveSlider(float InBlendValue, TWeakPtr<FUICommandInfo> InCommandForChordUp);` — Handles the command to move the slider to InBlendValue and keeps the slider position there until the key is released.
- L52 _private prototype_ `void HandleCommandChordUp();` — Handles on of the command chord being released.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/STweenView.h` (Public)


#### class `UE::TweeningUtilsEditor::STweenView`  
`class STweenView : public SCompoundWidget`  
_L22-57_
- inherits: `SCompoundWidget`
- desc: It bridges the STweenSlider, which acts as the view, and the model, FTweenModel, by interchanging data between them. Acts as view in a Model-View-Controller architecture.
- L26 _public function_ `SLATE_BEGIN_ARGS(STweenView)`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FTweenModel*, TweenModel) SLATE_ATTRIBUTE(const FSlateBrush*, SliderIcon) SLATE_ATTRIBUTE(FLinearColor, SliderColor) SLATE_ATTRIBUTE(TOptional<float>, OverrideSliderPosition) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Gets the tween model this view is driving.
- L40 _public function_ `const TSharedPtr<STweenSlider>& GetTweenSlider() const`
- L45 _private member_ `TSharedPtr<STweenSlider> TweenSlider;` — The embedded tween slider this widget is wrapping.
- L48 _private member_ `TAttribute<FTweenModel*> TweenModelAttr;` — The model that these controls are driving
- L50 _private prototype_ `ETweenScaleMode GetBarRenderMode() const;`
- L52 _private prototype_ `void OnDragStarted() const;`
- L53 _private prototype_ `void OnDragEnded() const;`
- L54 _private prototype_ `void OnDragValueUpdated(float Value) const;`
- L55 _private prototype_ `void OnPointPicked(float Value) const;`
- L56 _private prototype_ `float MapSliderValueToBlendValue(float Value) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/TweenControllers.h` (Public)


#### struct `UE::TweeningUtilsEditor::FTweenControllers`  
`struct FTweenControllers`  
_L18-45_
- desc: Holds functionality that may be reused across modules to add tweening widgets to a toolbar.
- L21 _public member_ `FTweenToolbarController ToolbarController;` — Manages the toolbar widget
- L24 _public member_ `FCycleFunctionController CycleFunctionController;` — Cycles functions (Shift + U).
- L27 _public member_ `FTweenMouseSlidingController MouseSlidingController;` — Allows indirect movement of the slider by using u + Move Mouse
- L30 _public member_ `FMoveSliderByHotkeyController MoveSliderByHotkeyController;` — Allows moving the slider via hotkeys.
- L37 _public prototype_ `explicit FTweenControllers( const TSharedRef<FUICommandList>& InCommandList, const TSharedRef<ITweenModelContainer>& InTweenModels, FName UserPreferredFunctionContext = NAME_None );` — @param InCommandList The command list to bind commands to @param InTweenModels Contains all tween models that can be selected by the tweening widgets @param UserPreferredFunctionContext Optional. The config key under which the selected tween function is saved. The function currently saved under this key will be the first one to be selected.
- L44 _public prototype_ `TOptional<float> GetCurrentSliderPosition() const;` — @return The current slider override position that may be driven by one of the subsytems, like MouseSlidingController. Range [-1,1].

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/TweenMouseSlidingController.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweenMouseSlidingController`  
`class FTweenMouseSlidingController : public FMouseSlidingController`  
_L19-59_
- inherits: `FMouseSlidingController`
- desc: Specialization that sends blend values to a tween model based on how far the mouse is moved.
- L30 _public prototype_ `explicit FTweenMouseSlidingController( TAttribute<float> InMaxSlideWidthAttr, TAttribute<FTweenModel*> InTweenModelAttr, const TSharedRef<FUICommandList>& InCommandList, TSharedPtr<FUICommandInfo> InDragSliderCommand );` — Version that allows you to specify every detail @param InMaxSlideWidthAttr The total size of the "invisible" slider. The mouse can be moved left and right InMaxSlideWidthAttr.Get / 2.0 before being clamped. @param InTweenModelAttr The tween model that the sliding will update. @param InCommandList The command list to bind / unbind the command with. @param InDragSliderCommand The command that triggers detection of mouse movement.
- L40 _public prototype_ `explicit FTweenMouseSlidingController( TAttribute<FTweenModel*> InTweenModelAttr, const TSharedRef<FUICommandList>& InCommandList );` — Version that defaults to using the commands from FTweeningUtilsCommands. The slider width is based on the size of the slider in the toolbar(= value from FTweeningUtilsStyle).
- L46 _public function_ `const TOptional<float>& GetCurrentSliderPosition() const` — @return The current slider position that is being driven by the mouse. Range [-1,1].
- L51 _private member_ `const TAttribute<FTweenModel*> TweenModelAttr;` — Does the actual blending.
- L54 _private member_ `TOptional<float> CurrentSliderPosition;` — The current slider position that is being driven by the mouse. Range [-1,1].
- L56 _private prototype_ `void OnSliderStartMove();`
- L57 _private prototype_ `void OnSliderEndMove();`
- L58 _private prototype_ `void OnSliderMove(float InValue);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/MVC/TweenToolbarController.h` (Public)


#### class `UE::TweeningUtilsEditor::FTweenToolbarController`  
`class FTweenToolbarController : public FNoncopyable`  
_L38-129_
- inherits: `FNoncopyable`
- desc: Binds together a STweenView and FTweenModel in the context of adding the controls to a toolbar widget. Acts as controller in a Model-View-Controller architecture. Makes a toolbar as follows |Combo|Slider|Overshot| - Combo: Selects the blend function - Slider: Adjusts the blend value and updates the FTweenModel - Overshoot: Toggle button for changing the overshoot property on FTweenModel
- L47 _public prototype_ `explicit FTweenToolbarController( const TSharedRef<FUICommandList>& InCommandList, const TSharedRef<ITweenModelContainer>& InTweenFunctions, int32 InInitialTweenModelIndex = 0 );` — @param InCommandList Used to bind the commands added to the toolbar. @param InTweenFunctions The functions that can be selected @param InInitialTweenModelIndex Index of the tween model to initially be selected.
- L52 _public prototype_ `~FTweenToolbarController();`
- L80 _public prototype_ `FAddToToolbarResult AddToToolbar(FToolBarBuilder& ToolbarBuilder, FMakeWidgetArgs InArgs = {}) const;` — Extends the toolbar. Safe to call multiple times (although typically you'll call this exactly once). @param ToolbarBuilder The toolbar to add the widgets to @param InArgs Optional additional args to control how the widget should be constructed.
- L83 _public prototype_ `void SetSelectedTweenModel(FTweenModel& InTweenModel);` — Sets the currently selected tween model. Asserts that the tween model is contained in TweenModels.
- L86 _public function_ `FTweenModel& GetSelectedTweenModel() const` — @return Gets the currently selected tween model
- L87 _public function_ `TAttribute<FTweenModel*> MakeSelectedTweenModelAttr() const`
- L88 _public function_ `TAttribute<const FTweenModel*> MakeSelectedConstTweenModelAttr() const`
- L90 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTweenFunctionChanged, const FTweenModel&);`
- L92 _public function_ `FOnTweenFunctionChanged& OnTweenFunctionChanged()` — Invoked when the tween function is changed by this controller.
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOvershootModeToggled);` — Invoked when the overshoot mode is changed by this controller.
- L95 _public function_ `FOnOvershootModeToggled& OnOvershootModeCommandInvoked()`
- L100 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Used when the combo button is opened.
- L102 _private member_ `const TSharedRef<ITweenModelContainer> TweenModels;` — Holds the functions that can be selected and gives us information about how to display them.
- L104 _private member_ `TNotNull<FTweenModel*> SelectedTweenModel;` — The selected tween model. Points into TweenModels.
- L107 _private member_ `const TPimplPtr<class FOvershootButtonStyleHack> OverrideStyle;` — Used to override the color of the overshoot button to match the color of the tween model.
- L110 _private member_ `FOnTweenFunctionChanged OnTweenFunctionChangedDelegate;` — Invoked when the tween function is changed by this controller.
- L112 _private member_ `FOnOvershootModeToggled OnOvershootModeCommandInvokedDelegate;` — Invoked when the overshoot mode is changed by this controller.
- L115 _private prototype_ `TSharedRef<SWidget> MakeTweenModeMenu() const;` — Creates the drop-down list for selecting the tween mode.
- L116 _private prototype_ `FText GetLabelForComboBox() const;`
- L117 _private prototype_ `FText GetToolTipForComboBox() const;`
- L118 _private prototype_ `FSlateIcon GetIconForComboBox() const;`
- L120 _private prototype_ `void SetTweenModel(FTweenModel* InTweenModel);`
- L121 _private prototype_ `bool IsTweenModelSelected(FTweenModel* InTweenModel) const;`
- L123 _private prototype_ `void ToggleOvershootMode() const;`
- L124 _private prototype_ `bool IsOvershootModeEnabled() const;`
- L125 _private prototype_ `FSlateIcon GetOvershootModeIcon() const;`
- L127 _private prototype_ `const FSlateBrush* GetIconForSlider() const;`
- L128 _private prototype_ `FLinearColor GetColorForSlider() const;`

#### struct `UE::TweeningUtilsEditor::FTweenToolbarController::FMakeWidgetArgs`  
`struct FMakeWidgetArgs`  
_L54-68_
- L60 _public member_ `TAttribute<TOptional<float>> OverrideSliderPositionAttr;` — Optional override for the where the slider is visually placed (does not affect functionality). Range [-1,1]. Useful e.g. in conjunction with FTweenMouseSlidingController (while pressing U+LMB, give the user a visual association).
- L63 _public member_ `FMenuEntryResizeParams FunctionSelectResizeParams;` — Affects how the tween function selection combo box is resized.
- L65 _public member_ `FMenuEntryResizeParams SliderResizeParams;` — Affects how the slider widget is resized.
- L67 _public member_ `FMenuEntryResizeParams OvershootResizeParams;` — Affects how the overshoot button is resized.

#### struct `UE::TweeningUtilsEditor::FTweenToolbarController::FAddToToolbarResult`  
`struct FAddToToolbarResult`  
_L69-73_
- L72 _public member_ `TSharedPtr<STweenSlider> TweenSlider;` — The tween slider widget that was added to the toolbar.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L87 _function_ `TAttribute<FTweenModel*> MakeSelectedTweenModelAttr() const` (scope `UE::TweeningUtilsEditor::FTweenToolbarController::MakeSelectedTweenModelAttr`)
- L88 _function_ `TAttribute<const FTweenModel*> MakeSelectedConstTweenModelAttr() const` (scope `UE::TweeningUtilsEditor::FTweenToolbarController::MakeSelectedConstTweenModelAttr`)
- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTweenFunctionChanged, const FTweenModel&);`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOvershootModeToggled);` — Invoked when the overshoot mode is changed by this controller.

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/STweenSlider.h` (Public)


#### class `UE::TweeningUtilsEditor::STweenSlider`  
`class STweenSlider : public SLeafWidget`  
_L30-125_
- inherits: `SLeafWidget`
- desc: The slider ranges from -1 to 1. It drives the blend while pressed down. When released, it jumps to 0: letting the user reapply the blend again. The slider looks like this: - ETweenScaleMode::Normalized: [   +   +   +   [I]   +   +   +   ] - ETweenScaleMode::Overshoot:  [ + + + | + + + [I] + + + | + + + ] Here: - I is the Icon and the bit behind it is the SliderIconBackground. Together, they form a button. - + is a point on the scale.
- L34 _public prototype_ `DECLARE_DELEGATE_OneParam(FSliderChangedDelegate, float );` — Value's range is [-1,1].
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(float, FMapSliderValueToBlendValue, float );` — Value's range is [-1,1].
- L37 _public function_ `SLATE_BEGIN_ARGS(STweenSlider) : _Style(&FTweeningUtilsStyle::Get().GetWidgetStyle<FTweenSliderStyle>("TweenSlider")) , _ColorAndOpacity(FLinearColor::White) , _SliderIcon(nullptr) , _SliderColor(FLinearColor(254.f/255.f, 155.f/255.f, 7.f/255.f)) , _ScaleRenderMode(ETweenScaleMode::Normalized)`
- L46 _public prototype_ `SLATE_STYLE_ARGUMENT( FTweenSliderStyle, Style ) SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity) SLATE_ATTRIBUTE(const FSlateBrush*, SliderIcon) SLATE_ATTRIBUTE(FLinearColor, SliderColor) SLATE_ATTRIBUTE(ETweenScaleMode, ScaleRenderMode) SLATE_ATTRIBUTE(TOptional<float>, OverrideSliderPosition) SLATE_EVENT(FSimpleDelegate, OnSliderDragStarted) SLATE_EVENT(FSimpleDelegate, OnSliderDragEnded) SLATE_EVENT(FSliderChangedDelegate, OnSliderValueDragged) SLATE_EVENT(FSliderChangedDelegate, OnPointValuePicked) SLATE_EVENT(FMapSliderValueToBlendValue, MapSliderValueToBlendValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The visual style of the button
- L85 _private member_ `TPimplPtr<FSliderWidgetData> Pimpl;` — Abstracts the implementation. Specifically, it hides FTweenSliderHoverState, FTweenSliderDrawArgs, and FTweenWidgetArgs so TweenSliderDrawUtils.h does not become part of the public API.
- L88 _private member_ `FSimpleDelegate OnSliderDragStartedDelegate;` — Invoked when the slider begins being dragged.
- L90 _private member_ `FSimpleDelegate OnSliderDragStoppedDelegate;` — Invoked when the slider stops being dragged
- L92 _private member_ `FSliderChangedDelegate OnSliderChangedDelegate;` — Invoked during drag when the slider value changes.
- L94 _private member_ `FSliderChangedDelegate OnPointValuePickedDelegate;` — Invoked when the user presses a point to select a blend value.
- L97 _private member_ `FMapSliderValueToBlendValue MapSliderValueToBlendValueDelegate;` — Invoked to display the correct blend value tooltips.
- L100 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L101 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L102 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L103 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& InMouseEvent) override;`
- L104 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent) override;`
- L105 _private prototype_ `virtual void OnFinishedPointerInput() override;`
- L106 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L107 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L108 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L109 _private prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;`
- L113 _private prototype_ `void UpdateLastMousePositionOnSlider(const FGeometry& InGeometry, const FVector2D& InMousePos);` — Updates LastMousePositionOnSliderBar.
- L115 _private prototype_ `bool IsMouseDown() const;`
- L116 _private prototype_ `bool IsDragging() const;`
- L118 _private prototype_ `void OnStartDragOp() const;`
- L121 _private prototype_ `void HandlePickValueOfCurrentlyHoveredPoint(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) const;` — If the user is currently hovering a point, set the blend value to that point's value.
- L124 _private prototype_ `FText GetToolTipText() const;` — Gets the tooltip text for what is currently being hovered.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L34 _delegate_ `DECLARE_DELEGATE_OneParam(FSliderChangedDelegate, float );`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FMapSliderValueToBlendValue, float );`

### `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/Widgets/TweenSliderStyle.h` (Public)


#### struct `FTweenPointStyle`  
`struct FTweenPointStyle`  
_L14-49_
- reflection: `USTRUCT()`
- L18 _public prototype_ `FTweenPointStyle();`
- L19 _public prototype_ `explicit FTweenPointStyle( const FVector2D& InNormalSize, const FVector2D& InHoveredSize, const FVector2D& InPressedSize, const FVector2D& InHitSize );`
- L25 _public member_ `FSlateBrush Normal;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when a point on the bar is not hovered or pressed
- L26 _public function_ `FTweenPointStyle& SetNormal( const FSlateBrush& InNormal )`
- L30 _public member_ `FSlateBrush Hovered;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when a point on the bar is hovered
- L31 _public function_ `FTweenPointStyle& SetHovered( const FSlateBrush& InHovered)`
- L35 _public member_ `FSlateBrush Pressed;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when a point on the bar is pressed
- L36 _public function_ `FTweenPointStyle& Set( const FSlateBrush& InPressed )`
- L40 _public member_ `FSlateBrush PassedPoint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when the slider has passed a point
- L41 _public function_ `FTweenPointStyle& SetPassed( const FSlateBrush& InPassed )`
- L45 _public member_ `FVector2D HitTestSize = { 10.0, 12.0 };` — `UPROPERTY(EditAnywhere, Category=Appearance)` — The size of the hit box against which hit tests are made for this point (so the user does not need to click them pixel perfectly).
- L46 _public function_ `FTweenPointStyle& SetHitTestSize( const FVector2D& InSize )`
- L48 _public prototype_ `void GetResources(TArray<const FSlateBrush*>& OutBrushes) const;`

#### struct `FTweenSliderStyle`  
`struct FTweenSliderStyle : public FSlateWidgetStyle`  
_L53-142_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Style for STweenSlider
- L57 _public prototype_ `FTweenSliderStyle();`
- L60 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L63 _public member_ `static const FName TypeName;`
- L64 _public function_ `virtual const FName GetTypeName() const override`
- L66 _public prototype_ `static const FTweenSliderStyle& GetDefault();`
- L70 _public member_ `FVector2D BarDimensions;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — The dimensions of the slider.
- L71 _public function_ `FTweenSliderStyle& SetBarDimensions( const FVector2D& InDimensions )`
- L75 _public member_ `FSlateBrush BarBrush;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush of the bar on which the points are drawn. The slider brush is drawn over it. Usually the bar's brush is smaller than the button.
- L76 _public function_ `FTweenSliderStyle& SetBarBrush( const FSlateBrush& InBarBrush )`
- L82 _public member_ `FSlateBrush NormalSliderButton;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when the button is not hovered or pressed
- L83 _public function_ `FTweenSliderStyle& SetNormalSliderButton( const FSlateBrush& InNormalBrush )`
- L87 _public member_ `FSlateBrush HoveredSliderButton;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when hovered
- L88 _public function_ `FTweenSliderStyle& SetHoveredSliderButton( const FSlateBrush& InHoveredBrush)`
- L92 _public member_ `FSlateBrush PressedSliderButton;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush when pressed
- L93 _public function_ `FTweenSliderStyle& SetPressedSliderButton( const FSlateBrush& InPressedBrush )`
- L99 _public member_ `FSlateColor NormalIconTint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Tint for the icon when the button is not hovered or pressed
- L100 _public function_ `FTweenSliderStyle& SetNormalIconTint( const FSlateColor& InNormalIconTint )`
- L104 _public member_ `FSlateColor HoveredIconTint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Tint for the icon when hovered
- L105 _public function_ `FTweenSliderStyle& SetHoveredIconTint( const FSlateColor& InHoveredIconTint)`
- L109 _public member_ `FSlateColor PressedIconTint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Tint for the icon when pressed
- L110 _public function_ `FTweenSliderStyle& SetPressedIconTint( const FSlateColor& InPressedIconTint )`
- L116 _public member_ `FTweenPointStyle SmallPoint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brushes for the small points on the bar.
- L117 _public function_ `FTweenSliderStyle& SetSmallPoint( const FTweenPointStyle& InNormal )`
- L121 _public member_ `FTweenPointStyle MediumPoint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — When overshoot mode is enabled, the bars at 100% and -100%.
- L122 _public function_ `FTweenSliderStyle& SetMediumPoint( const FTweenPointStyle& InHovered)`
- L126 _public member_ `FTweenPointStyle EndPoint;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brushes for points on the left or right end.
- L127 _public function_ `FTweenSliderStyle& SetEndPoint( const FTweenPointStyle& InPressed )`
- L133 _public member_ `FSlateBrush PassedValueBackground;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Brush drawn from center to slider when moving the slider (should be a little transparent, drawn over points but under the slider).
- L134 _public function_ `FTweenSliderStyle& SetPassedValueBackground( const FSlateBrush& InBrush )`
- L140 _public member_ `FMargin IconPadding;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Padding of the icon placed in the slider button
- L141 _public function_ `FTweenSliderStyle& SetIconPadding( const FMargin& InIconPadding )`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TWEENINGUTILSEDITOR_API`
