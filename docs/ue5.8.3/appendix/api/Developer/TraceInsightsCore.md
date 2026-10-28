# Developer / TraceInsightsCore

- module root: `Source/Developer/TraceInsightsCore`
- headers: 45; symbols: 1692
- symbol kinds: class=107, delegate=7, enum=13, enumerator=64, function=467, macro=41, member=287, namespace=81, prototype=577, struct=12, typedef=34, union=2
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, InputCore, Slate, SlateCore, ToolWidgets, TraceServices

### `Source/Developer/TraceInsightsCore/Private/InsightsCore/TraceInsightsCoreModule.h` (Private)


#### class `FTraceInsightsCoreModule`  
`class FTraceInsightsCoreModule : public ITraceInsightsCoreModule`  
_L7-14_
- inherits: `ITraceInsightsCoreModule`
- L10 _public prototype_ `virtual ~FTraceInsightsCoreModule() = default;`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/AsyncOperationProgress.h` (Public)


#### class `UE::Insights::IAsyncOperationProgress`  
`class IAsyncOperationProgress`  
_L12-18_
- L15 _public prototype_ `virtual void CancelCurrentAsyncOp() = 0;`
- L16 _public prototype_ `virtual void Reset() = 0;`
- L17 _public prototype_ `virtual bool ShouldCancelAsyncOp() const = 0;`

#### class `UE::Insights::FAsyncOperationProgress`  
`class FAsyncOperationProgress : public IAsyncOperationProgress`  
_L20-29_
- inherits: `IAsyncOperationProgress`
- L23 _public function_ `virtual void CancelCurrentAsyncOp() override`
- L24 _public function_ `virtual void Reset() override`
- L25 _public function_ `virtual bool ShouldCancelAsyncOp() const override`
- L28 _private member_ `std::atomic<bool> bCancelCurrentAsyncOp{ false };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/AvailabilityCheck.h` (Public)


#### class `UE::Insights::FAvailabilityCheck`  
`class FAvailabilityCheck`  
_L15-30_
- desc: Utility class used by profiler managers to limit how often they check for availability conditions.
- L19 _public prototype_ `bool Tick();` — Returns true if managers are allowed to do (slow) availability check during this tick.
- L22 _public prototype_ `void Disable();` — Disables the "availability check" (i.e. Tick() calls will return false when disabled).
- L25 _public prototype_ `void Enable(double InWaitTime);` — Enables the "availability check" with a specified initial delay.
- L28 _private member_ `double WaitTime = 0.0;`
- L29 _private member_ `uint64 NextTimestamp = (uint64)-1;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/FixedCircularBuffer.h` (Public)


#### struct `UE::Insights::TFixedCircularBuffer`  
`template <typename T, int32 Size = 64> struct TFixedCircularBuffer`  
_L11-55_
- L13 _public member_ `T Buffer[Size];`
- L14 _public member_ `int32 BufferStartOffset = 0;`
- L15 _public member_ `int32 BufferLength = 0;`
- L17 _public function_ `void Reset()`
- L23 _public function_ `void AddValue(const T Value)`
- L37 _public function_ `const T GetValue(const int32 RecentIndex) const`
- L42 _public function_ `const T ComputeAverage() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/IAsyncOperationStatusProvider.h` (Public)


#### class `UE::Insights::IAsyncOperationStatusProvider`  
`class IAsyncOperationStatusProvider`  
_L12-22_
- L15 _public prototype_ `virtual bool IsRunning() const = 0;`
- L17 _public prototype_ `virtual double GetAllOperationsDuration() = 0;`
- L18 _public prototype_ `virtual double GetCurrentOperationDuration() = 0;`
- L19 _public prototype_ `virtual uint32 GetOperationCount() const = 0;`
- L21 _public prototype_ `virtual FText GetCurrentOperationName() const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/InsightsCoreStyle.h` (Public)


#### class `UE::Insights::FInsightsCoreStyle`  
`class FInsightsCoreStyle`  
_L21-79_
- L24 _public prototype_ `static void Initialize();`
- L25 _public prototype_ `static void Shutdown();`
- L27 _public prototype_ `static FName GetStyleSetName();`
- L28 _public prototype_ `static const ISlateStyle& Get();`
- L30 _public function_ `static const FLinearColor& GetColor(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L35 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L40 _public function_ `static const FSlateBrush* GetOutlineBrush(EHorizontalAlignment HAlign)`
- L76 _private prototype_ `static TSharedRef<FInsightsCoreStyle::FStyle> Create();`
- L78 _private member_ `static TSharedPtr<FInsightsCoreStyle::FStyle> StyleInstance;`

#### class `UE::Insights::FInsightsCoreStyle::FStyle`  
`class FStyle : public FSlateStyleSet`  
_L56-73_
- inherits: `FSlateStyleSet`
- L59 _public prototype_ `FStyle(const FName& InStyleSetName);`
- L61 _public prototype_ `void Initialize();`
- L63 _public prototype_ `void SyncParentStyles();`
- L67 _public member_ `FTextBlockStyle NormalText;` — Styles inherited from the parent style
- L68 _public member_ `FButtonStyle Button;`
- L69 _public member_ `FSlateColor SelectorColor;`
- L70 _public member_ `FSlateColor SelectionColor;`
- L71 _public member_ `FSlateColor SelectionColor_Inactive;`
- L72 _public member_ `FSlateColor SelectionColor_Pressed;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/Log.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInsights, Verbose, All);`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/MessageDialogUtils.h` (Public)


#### enum `UE::Insights::EDialogResponse`  
`enum class EDialogResponse`  
_L14-18_
- L16 _public enumerator_ `OK = 0`
- L17 _public enumerator_ `Cancel = 1`

#### class `UE::Insights::FMessageDialogUtils`  
`class FMessageDialogUtils`  
_L22-26_
- L25 _public prototype_ `static EDialogResponse ShowChoiceDialog(const FText& Title, const FText& Content);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/MiscUtils.h` (Public)


#### class `UE::Insights::FMiscUtils`  
`class FMiscUtils`  
_L20-29_
- L28 _public prototype_ `static bool OpenUnrealInsights(const TCHAR* InCmdLine = nullptr);` — Starts a new Unreal Insights instance. @param InCmdLine - The command line passed to the new UnrealInsights.exe process @returns true if UnrealInsights process is created successfully.

#### class `UE::Insights::FVersionWidget`  
`class FVersionWidget : public TSharedFromThis<FVersionWidget>`  
_L31-67_
- inherits: `TSharedFromThis<FVersionWidget>`
- L44 _public function_ `FVersionWidget()`
- L45 _public prototype_ `virtual ~FVersionWidget() = default;`
- L47 _public prototype_ `virtual FText GetWidgetText() const;`
- L48 _public prototype_ `virtual FSlateColor GetColor() const;`
- L49 _public prototype_ `virtual FReply OnDoubleClicked(const FGeometry&, const FPointerEvent&);`
- L50 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget();`
- L52 _public function_ `EDisplayMode GetDisplayMode() const`
- L56 _public function_ `void SetDisplayMode(EDisplayMode InDisplayMode)`
- L60 _public function_ `void NextDisplayMode()`
- L66 _private member_ `EDisplayMode DisplayMode = EDisplayMode::Version;`

#### enum `UE::Insights::FVersionWidget::EDisplayMode`  
`enum class EDisplayMode`  
_L34-41_
- L36 _public enumerator_ `Version`
- L37 _public enumerator_ `VersionAndMem`
- L38 _public enumerator_ `VersionAndDetailedMem`
- L40 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/PaintUtils.h` (Public)


#### class `UE::Insights::FDrawContext`  
`class FDrawContext`  
_L32-140_
- desc: Holds current state provided by OnPaint function, used to simplify drawing.
- L35 _public function_ `FDrawContext( const FGeometry& InGeometry, const FSlateRect& InCullingRect, const FWidgetStyle& InWidgetStyle, const ESlateDrawEffect InDrawEffects, FSlateWindowElementList& InOutElementList, int32& InOutLayerId) : Geometry(InGeometry) , CullingRect(InCullingRect) , WidgetStyle(InWidgetStyle) , DrawEffects(InDrawEffects) , ElementList(InOutElementList) , LayerId(InOutLayerId)`
- L54 _public prototype_ `FDrawContext(const FDrawContext&) = delete;` — Non-copyable
- L55 _public prototype_ `FDrawContext& operator=(const FDrawContext&) = delete;`
- L59 _public typedef_ `using FDrawContextOld = ::FDrawContext;`
- L60 _public prototype_ `inline explicit FDrawContext(FDrawContextOld&);`
- L61 _public prototype_ `inline FDrawContext& operator=(FDrawContextOld&);`
- L62 _public prototype_ `inline operator FDrawContextOld& ();`
- L66 _public function_ `inline void DrawBox(const float X, const float Y, const float W, const float H, const FSlateBrush* Brush, const FLinearColor& Color) const`
- L71 _public function_ `inline void DrawBox(const int32 InLayer, const float X, const float Y, const float W, const float H, const FSlateBrush* Brush, const FLinearColor& Color) const`
- L76 _public function_ `inline void DrawRotatedBox(const float X, const float Y, const float W, const float H, const FSlateBrush* Brush, const FLinearColor& Color, float Angle, TOptional<FVector2D> RotationPoint) const`
- L81 _public function_ `inline void DrawText(const float X, const float Y, const FString& Text, const FSlateFontInfo& Font, const FLinearColor& Color) const`
- L86 _public function_ `inline void DrawText(const int32 InLayer, const float X, const float Y, const FString& Text, const FSlateFontInfo& Font, const FLinearColor& Color) const`
- L91 _public function_ `inline void DrawText(const float X, const float Y, const FString& Text, const int32 StartIndex, const int32 EndIndex, const FSlateFontInfo& Font, const FLinearColor& Color) const`
- L96 _public function_ `inline void DrawText(const int32 InLayer, const float X, const float Y, const FString& Text, const int32 StartIndex, const int32 EndIndex, const FSlateFontInfo& Font, const FLinearColor& Color) const`
- L101 _public function_ `inline void DrawTextAligned(EHorizontalAlignment HAlign, const float X, const float Y, const FString& Text, const FSlateFontInfo& Font, const FLinearColor& Color) const`
- L121 _public function_ `inline void DrawSpline(uint32 InLayer, const float X, const float Y, const FVector2D& InStart, const FVector2D& InStartDir, const FVector2D& InEnd, const FVector2D& InEndDir, float InThickness = 0.0f, const FLinearColor& InTint=FLinearColor::White) const`
- L126 _public function_ `inline void DrawLines(uint32 InLayer, const float X, const float Y, const TArray<FVector2D>& Points, const FLinearColor& InTint = FLinearColor::White, bool bAntialias = true, float Thickness = 1.0f) const`
- L133 _public member_ `const FGeometry& Geometry;` — Accessors
- L134 _public member_ `const FSlateRect& CullingRect;`
- L135 _public member_ `const FWidgetStyle& WidgetStyle;`
- L136 _public member_ `const ESlateDrawEffect DrawEffects;`
- L138 _public member_ `FSlateWindowElementList& ElementList;`
- L139 _public member_ `int32& LayerId;`
- L192 _function_ `FDrawContext::FDrawContext(FDrawContextOld& Other) : FDrawContext(Other.Geometry, Other.CullingRect, Other.WidgetStyle, Other.DrawEffects, Other.ElementList, Other.LayerId)`
- L197 _function_ `FDrawContext& FDrawContext::operator=(FDrawContextOld& Other)`
- L203 _function_ `FDrawContext::operator FDrawContextOld& ()`

#### struct `FDrawContext`  
`struct FDrawContext final : public UE::Insights::FDrawContext`  
_L147-186_
- reflection: `UE_DEPRECATED(5.5, "FDrawContext struct was moved inside UE::Insights namespace")`
- inherits: `UE::Insights::FDrawContext`
- L149 _public function_ `FDrawContext( const FGeometry& InGeometry, const FSlateRect& InCullingRect, const FWidgetStyle& InWidgetStyle, const ESlateDrawEffect InDrawEffects, FSlateWindowElementList& InOutElementList, int32& InOutLayerId) : UE::Insights::FDrawContext(InGeometry, InCullingRect, InWidgetStyle, InDrawEffects, InOutElementList, InOutLayerId)`
- L163 _public prototype_ `FDrawContext(const FDrawContext&) = delete;` — Non-copyable
- L164 _public prototype_ `FDrawContext& operator=(const FDrawContext&) = delete;`
- L166 _public function_ `explicit FDrawContext(UE::Insights::FDrawContext& Other) : UE::Insights::FDrawContext(Other.Geometry, Other.CullingRect, Other.WidgetStyle, Other.DrawEffects, Other.ElementList, Other.LayerId)`
- L171 _public function_ `FDrawContext& operator=(UE::Insights::FDrawContext& Other)`
- L177 _public function_ `FDrawContext& operator()(UE::Insights::FDrawContext& Other)`
- L182 _public function_ `inline void DrawLines(uint32 InLayer, const float X, const float Y, const TArray<FVector2D>& Points, ESlateDrawEffect InDrawEffects = ESlateDrawEffect::None, const FLinearColor& InTint = FLinearColor::White, bool bAntialias = true, float Thickness = 1.0f) const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define MAKE_PAINT_GEOMETRY_PT(Geometry, X, Y) Geometry.ToPaintGeometry(FSlateLayoutTransform(1.0f, FVector2D(X, Y)))`
- L14 _macro_ `#define MAKE_PAINT_GEOMETRY_RC(Geometry, X, Y, W, H) Geometry.ToPaintGeometry(FVector2D(W, H), FSlateLayoutTransform(1.0f, FVector2D(X, Y)))`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Insights` (scope `UE`)
- L188 _namespace_ `namespace UE`
- L188 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/SimpleRtti.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define INSIGHTS_DECLARE_RTTI_BASE(BaseClassName, ...) \` — Macro to be used in declaration of the base class of the SimpleRTTI class hierarchy.
- L23 _macro_ `#define INSIGHTS_DECLARE_RTTI(ClassName, BaseClassName, ...) \` — Macro to be used in declaration of a derived class in a SimpleRTTI hierarchy.
- L32 _macro_ `#define INSIGHTS_IMPLEMENT_RTTI(ClassName) \` — Macro to be used in implementation of a class in a SimpleRTTI hierarchy.

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/Stopwatch.h` (Public)


#### struct `UE::Insights::FStopwatch`  
`struct FStopwatch`  
_L13-81_
- desc: Simple stopwatch.
- L15 _public member_ `uint64 AccumulatedTime = 0;`
- L16 _public member_ `uint64 StartTime = 0;`
- L17 _public member_ `bool bIsStarted = false;`
- L19 _public function_ `void Start()`
- L28 _public function_ `void Stop()`
- L37 _public function_ `void Update()`
- L47 _public function_ `void Restart()`
- L54 _public function_ `void Reset()`
- L61 _public function_ `double GetAccumulatedTime() const`
- L66 _public function_ `uint64 GetAccumulatedTimeMs() const`
- L71 _public function_ `static double Cycles64ToSeconds(const uint64 Cycles64)`
- L76 _public function_ `static uint64 Cycles64ToMilliseconds(const uint64 Cycles64)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Common/TimeUtils.h` (Public)


#### struct `UE::Insights::FTimeValue`  
`struct FTimeValue`  
_L30-43_
- L32 _public member_ `static constexpr double Picosecond = 0.000000000001;`
- L33 _public member_ `static constexpr double Nanosecond = 0.000000001;`
- L34 _public member_ `static constexpr double Microsecond = 0.000001;`
- L35 _public member_ `static constexpr double Millisecond = 0.001;`
- L36 _public member_ `static constexpr double Second = 1.0;`
- L37 _public member_ `static constexpr double Minute = 60.0;`
- L38 _public member_ `static constexpr double Hour = 3600.0;`
- L39 _public member_ `static constexpr double Day = 86400.0;`
- L40 _public member_ `static constexpr double Week = 604800.0;`
- L42 _public member_ `double Value;`

#### struct `UE::Insights::FTimeSplit`  
`struct FTimeSplit`  
_L45-66_
- L62 _public member_ `bool bIsZero;`
- L63 _public member_ `bool bIsNegative;`
- L64 _public member_ `bool bIsInfinite;`
- L65 _public member_ `bool bIsNaN;`

#### union `UE::Insights::FTimeSplit::(anonymous)`  
``  
_L48-61_

#### struct `UE::Insights::FTimeSplit::__anon94050b38010a::(anonymous)`  
``  
_L51-60_

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Insights` (scope `UE`)
- L49 _member_ `int32 Units[8];` (scope `UE::Insights::FTimeSplit::__anon94050b38010a`) — Units[0] = Days, Units[1] = Hours, ..., Units[7] = Picoseconds
- L52 _member_ `int32 Days;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L53 _member_ `int32 Hours;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L54 _member_ `int32 Minutes;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L55 _member_ `int32 Seconds;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L56 _member_ `int32 Milliseconds;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L57 _member_ `int32 Microseconds;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L58 _member_ `int32 Nanoseconds;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L59 _member_ `int32 Picoseconds;` (scope `UE::Insights::FTimeSplit::__anon94050b38010a::__anon94050b380208`)
- L68 _prototype_ `FString FormatTimeValue(const double Duration, const int32 NumDigits = 2);` (scope `UE::Insights`)
- L69 _prototype_ `FString FormatTimeAuto(const double Duration, const int32 NumDigits = 2);` (scope `UE::Insights`)
- L70 _prototype_ `FString FormatTimeMs(const double Duration, const int32 NumDigits = 3, bool bAddTimeUnit = false);` (scope `UE::Insights`)
- L71 _prototype_ `FString FormatTime(const double Time, const double Precision = 0.0);` (scope `UE::Insights`)
- L72 _prototype_ `FString FormatTimeHMS(const double Time, const double Precision = 0.0);` (scope `UE::Insights`)
- L73 _prototype_ `void SplitTime(const double Time, FTimeSplit& OutTimeSplit);` (scope `UE::Insights`)
- L74 _prototype_ `FString FormatTimeSplit(const FTimeSplit& TimeSplit, const double Precision = 0.0);` (scope `UE::Insights`)
- L75 _prototype_ `FString FormatTimeSplit(const double Time, const double Precision = 0.0);` (scope `UE::Insights`)
- L77 _prototype_ `void TestTimeFormatting();` (scope `UE::Insights`)
- L78 _prototype_ `void TestTimeAutoFormatting();` (scope `UE::Insights`)
- L79 _prototype_ `void TestOptimizationIssue();` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Config.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_INSIGHTS_CORE_BACKWARD_COMPATIBILITY_UE54 1`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/ViewModels/FilterConfigurator.h` (Public)


#### class `UE::Insights::FFilterConfigurator`  
`class FFilterConfigurator : public IFilterExecutor`  
_L18-78_
- inherits: `IFilterExecutor`
- L21 _public prototype_ `FFilterConfigurator();`
- L23 _public prototype_ `FFilterConfigurator(const FFilterConfigurator& Other);`
- L24 _public prototype_ `FFilterConfigurator& operator=(const FFilterConfigurator& Other);`
- L26 _public prototype_ `bool operator==(const FFilterConfigurator& Other) const;`
- L27 _public function_ `bool operator!=(const FFilterConfigurator& Other) const`
- L29 _public prototype_ `virtual ~FFilterConfigurator();`
- L31 _public function_ `bool IsEmpty() const`
- L34 _public function_ `void Update()` — Called to update the internal state of some filters
- L36 _public prototype_ `virtual bool ApplyFilters(const FBaseFilterContext& Context) const override;`
- L38 _public prototype_ `bool IsKeyUsed(int32 Key) const;`
- L40 _public function_ `FFilterConfiguratorNodePtr GetRootNode()`
- L41 _public function_ `TSharedPtr<TArray<TSharedPtr<FFilter>>>& GetAvailableFilters()`
- L43 _public function_ `void Add(TSharedPtr<FFilter> InFilter)`
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDestroyedEvent);` — The event to execute when an instance is destroyed.
- L51 _public function_ `FOnDestroyedEvent& GetOnDestroyedEvent()`
- L54 _private member_ `FOnDestroyedEvent OnDestroyedEvent;`
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnChangesCommittedEvent);` — The event to execute when the changes to the Filter Widget are saved by clicking on the OK Button.
- L62 _public function_ `FOnChangesCommittedEvent& GetOnChangesCommittedEvent()`
- L65 _private member_ `FOnChangesCommittedEvent OnChangesCommittedEvent;`
- L70 _private prototype_ `void ComputeUsedKeys();`
- L73 _private member_ `FFilterConfiguratorNodePtr RootNode;`
- L75 _private member_ `TSharedPtr<TArray<TSharedPtr<FFilter>>> AvailableFilters;`
- L77 _private member_ `TSet<int32> KeysUsed;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Insights` (scope `UE`)
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDestroyedEvent);` — The event to execute when an instance is destroyed.
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnChangesCommittedEvent);` — The event to execute when the changes to the Filter Widget are saved by clicking on the OK Button.

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/ViewModels/FilterConfiguratorNode.h` (Public)


#### class `UE::Insights::FFilterConfiguratorNode`  
`class FFilterConfiguratorNode : public FBaseTreeNode`  
_L33-92_
- inherits: `FBaseTreeNode`
- desc: Class used to store information about a filter node
- L39 _public prototype_ `FFilterConfiguratorNode(bool bInIsGroup);` — Initialization constructor for the filter configurator node.
- L42 _public function_ `FFilterConfiguratorNode(FName InName, bool bInIsGroup) : FFilterConfiguratorNode(bInIsGroup)` — `UE_DEPRECATED(5.8, "Use constructor without Name")`
- L44 _public prototype_ `static TSharedRef<FFilterConfiguratorNode> DeepCopy(const FFilterConfiguratorNode& Node);`
- L46 _public prototype_ `bool operator==(const FFilterConfiguratorNode& Other) const;`
- L48 _public prototype_ `virtual ~FFilterConfiguratorNode() = default;`
- L50 _public prototype_ `void SetAvailableFilters(TSharedPtr<TArray<TSharedPtr<FFilter>>> InAvailableFilters);`
- L51 _public function_ `TSharedPtr<TArray<TSharedPtr<FFilter>>> GetAvailableFilters()`
- L53 _public prototype_ `void SetSelectedFilter(TSharedPtr<FFilter> InSelectedFilter);`
- L54 _public function_ `TSharedPtr<FFilter> GetSelectedFilter() const`
- L56 _public prototype_ `void SetSelectedFilterOperator(TSharedPtr<IFilterOperator> InSelectedFilterOperator);`
- L57 _public prototype_ `TSharedPtr<const IFilterOperator> GetSelectedFilterOperator() const;`
- L59 _public prototype_ `const TArray<TSharedPtr<FFilterGroupOperator>>& GetFilterGroupOperators() const;`
- L60 _public function_ `void SetSelectedFilterGroupOperator(TSharedPtr<FFilterGroupOperator> InSelectedFilterGroupOperator)`
- L61 _public function_ `TSharedPtr<FFilterGroupOperator> GetSelectedFilterGroupOperator() const`
- L63 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetAvailableFilterOperators() const`
- L65 _public function_ `const FString& GetTextBoxValue()`
- L66 _public prototype_ `void SetTextBoxValue(const FString& InValue);`
- L68 _public prototype_ `bool ApplyFilters(const FBaseFilterContext& Context) const;`
- L70 _public prototype_ `void GetUsedKeys(TSet<int32>& GetUsedKeys) const;`
- L72 _public prototype_ `void ProcessFilter();`
- L74 _public prototype_ `void Update();`
- L76 _public function_ `TSharedPtr<FFilterState> GetSelectedFilterState()`
- L79 _private prototype_ `FFilterConfiguratorNode& operator=(const FFilterConfiguratorNode& Other);`
- L81 _private member_ `TSharedPtr<TArray<TSharedPtr<FFilter>>> AvailableFilters;`
- L83 _private member_ `TSharedPtr<FFilter> SelectedFilter;`
- L85 _private member_ `TSharedPtr<FFilterGroupOperator> SelectedFilterGroupOperator;`
- L87 _private member_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> AvailableFilterOperators;`
- L89 _private member_ `FString TextBoxValue;`
- L91 _private member_ `TSharedPtr<FFilterState> FilterState;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)
- L18 _typedef_ `typedef TSharedPtr<class FFilterConfiguratorNode> FFilterConfiguratorNodePtr;` (scope `UE::Insights`) — Type definition for shared pointers to instances of FFilterConfiguratorNode.
- L21 _typedef_ `typedef TSharedRef<class FFilterConfiguratorNode> FFilterConfiguratorRef;` (scope `UE::Insights`) — Type definition for shared references to instances of FFilterConfiguratorNode.
- L24 _typedef_ `typedef TSharedRef<const class FFilterConfiguratorNode> FFilterConfiguratorRefConst;` (scope `UE::Insights`) — Type definition for shared references to const instances of FFilterConfiguratorNode.
- L27 _typedef_ `typedef TWeakPtr<class FFilterConfiguratorNode> FFilterConfiguratorNodeWeak;` (scope `UE::Insights`) — Type definition for weak references to instances of FFilterConfiguratorNode.

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/ViewModels/Filters.h` (Public)


#### enum `UE::Insights::EFilterDataType`  
`enum class EFilterDataType : uint8`  
_L28-53_
- L30 _public enumerator_ `Void = 0` — not set
- L36 _public enumerator_ `Int64` — Bool, Uint32, Uint64, Int32,
- L38 _public enumerator_ `Double` — Float,
- L45 _public enumerator_ `String` — StringView, AnsiStringView, Utf8StringView, CString, AnsiCString, Utf8CString,
- L49 _public enumerator_ `Custom` — AnsiString, Utf8String, ByteArray,
- L50 _public enumerator_ `StringInt64Pair` — Displayed as a string but translates to a Int64 key.
- L52 _public enumerator_ `Count`

#### enum `UE::Insights::EFilterOperator`  
`enum class EFilterOperator : uint8`  
_L57-67_
- L59 _public enumerator_ `Eq = 0` — Equals
- L60 _public enumerator_ `NotEq = 1` — Not Equals
- L61 _public enumerator_ `Lt = 2` — Less Than
- L62 _public enumerator_ `Lte = 3` — Less than or equal to
- L63 _public enumerator_ `Gt = 4` — Greater than
- L64 _public enumerator_ `Gte = 5` — Greater than or equal to
- L65 _public enumerator_ `Contains = 6`
- L66 _public enumerator_ `NotContains = 7`

#### enum `UE::Insights::EFilterField`  
`enum class EFilterField : int32`  
_L71-83_
- L73 _public enumerator_ `StartTime = 0`
- L74 _public enumerator_ `EndTime = 1`
- L75 _public enumerator_ `Duration = 2`
- L76 _public enumerator_ `TrackName = 3`
- L77 _public enumerator_ `TimerId = 4`
- L78 _public enumerator_ `TimerName = 5`
- L79 _public enumerator_ `CoreEventName = 6`
- L80 _public enumerator_ `RegionName = 7`
- L81 _public enumerator_ `RegionCategory = 8`
- L82 _public enumerator_ `Metadata = 9`

#### class `UE::Insights::IFilterOperator`  
`class IFilterOperator`  
_L87-92_
- L90 _public prototype_ `virtual EFilterOperator GetKey() const = 0;`
- L91 _public prototype_ `virtual FString GetName() const = 0;`

#### class `UE::Insights::FFilterOperator`  
`template<typename T> class FFilterOperator : public IFilterOperator`  
_L97-121_
- inherits: `IFilterOperator`
- L100 _public typedef_ `typedef TFunction<bool(T, T)> FOperatorFunc;`
- L103 _public function_ `FFilterOperator(EFilterOperator InKey, FString InName, FOperatorFunc InFunc) : Key(InKey) , Name(InName) , Func(InFunc)`
- L110 _public prototype_ `virtual ~FFilterOperator() = default;`
- L112 _public function_ `virtual EFilterOperator GetKey() const override`
- L113 _public function_ `virtual FString GetName() const override`
- L115 _public function_ `bool Apply(T InValueA, T InValueB) const`
- L118 _private member_ `EFilterOperator Key;`
- L119 _private member_ `FString Name;`
- L120 _private member_ `FOperatorFunc Func;`

#### enum `UE::Insights::EFilterGroupOperator`  
`enum class EFilterGroupOperator`  
_L125-129_
- L127 _public enumerator_ `And = 0`
- L128 _public enumerator_ `Or = 1`

#### class `UE::Insights::FFilterGroupOperator`  
`class FFilterGroupOperator`  
_L133-151_
- L136 _public function_ `FFilterGroupOperator(EFilterGroupOperator InType, FText InName, FText InDesc) : Type(InType) , Name(InName) , Desc(InDesc)`
- L143 _public function_ `EFilterGroupOperator GetType() const`
- L144 _public function_ `const FText& GetName() const`
- L145 _public function_ `const FText& GetDesc() const`
- L148 _private member_ `EFilterGroupOperator Type;`
- L149 _private member_ `FText Name;`
- L150 _private member_ `FText Desc;`

#### class `UE::Insights::IFilterValueConverter`  
`class IFilterValueConverter`  
_L155-162_
- L158 _public function_ `virtual bool Convert(const FString& Input, int64& Output, FText& OutError) const`
- L159 _public function_ `virtual bool Convert(const FString& Input, double& Output, FText& OutError) const`
- L160 _public function_ `virtual FText GetTooltipText() const`
- L161 _public function_ `virtual FText GetHintText() const`

#### class `UE::Insights::FBaseFilterContext`  
`class FBaseFilterContext`  
_L166-203_
- L169 _public prototype_ `FBaseFilterContext() = default;`
- L170 _public prototype_ `virtual ~FBaseFilterContext() = default;`
- L172 _public function_ `virtual bool GetDefaultReturnValue() const`
- L177 _public prototype_ `virtual bool HasData(int32 Key) const = 0;`
- L178 _public prototype_ `virtual EFilterDataType GetDataType(int32 Key) const = 0;`
- L184 _public function_ `virtual int64 GetDataAsInt64(int32 Key) const` — virtual bool GetDataAsBool(int32 Key) const                                 { return false; } virtual uint32 GetDataAsUint32(int32 Key) const                             { return 0; } virtual uint64 GetDataAsUint64(int32 Key) const                             { return 0; } virtual int32 GetDataAsInt32(int32 Key) const                               { return 0; }
- L186 _public function_ `virtual double GetDataAsDouble(int32 Key) const` — virtual float GetDataAsFloat(int32 Key) const                               { return 0.0f; }
- L187 _public function_ `virtual FStringView GetDataAsStringView(int32 Key) const`
- L190 _public function_ `virtual const TCHAR* GetDataAsCString(int32 Key) const` — virtual FAnsiStringView GetDataAsAnsiStringView(int32 Key) const            { return FAnsiStringView(); } virtual FUtf8StringView GetDataAsUtf8StringView(int32 Key) const            { return FUtf8StringView();}
- L193 _public function_ `virtual const FString& GetDataAsString(int32 Key) const` — virtual const ANSICHAR* GetDataAsAnsiCString(int32 Key) const               { return nullptr; } virtual const UTF8CHAR* GetDataAsUtf8CString(int32 Key) const               { return nullptr; }
- L200 _protected member_ `static FString EmptyString;`

#### class `UE::Insights::FFilterContext`  
`class FFilterContext : public FBaseFilterContext`  
_L207-316_
- inherits: `FBaseFilterContext`
- L210 _public typedef_ `typedef TVariant<int64, double, FString> ContextData;`
- L213 _public prototype_ `FFilterContext() = default;`
- L214 _public prototype_ `virtual ~FFilterContext() = default;`
- L219 _public function_ `bool GetReturnValueForUnsetFilters() const` — `UE_DEPRECATED(5.8, "Use GetDefaultReturnValue() instead")`
- L222 _public function_ `void SetReturnValueForUnsetFilters(bool InValue)` — `UE_DEPRECATED(5.8, "Use custom class instead")`
- L224 _public function_ `virtual bool GetDefaultReturnValue() const override`
- L227 _public function_ `bool HasFilterData(int32 Key) const` — `UE_DEPRECATED(5.8, "Use HasData() instead")`
- L232 _public function_ `virtual bool HasData(int32 Key) const override`
- L237 _public function_ `virtual EFilterDataType GetDataType(int32 Key) const override`
- L261 _public function_ `template<typename T> void AddFilterData(int32 Key, const T& InData)`
- L269 _public function_ `template<typename T> void SetFilterData(int32 Key, const T& InData)`
- L275 _public function_ `template<typename T> void GetFilterData(int32 Key, T& OutData) const`
- L283 _public function_ `const FString& GetFilterDataAsString(int32 Key) const` — `UE_DEPRECATED(5.8, "Use GetDataAsString instead")`
- L292 _public function_ `virtual int64 GetDataAsInt64(int32 Key) const override`
- L298 _public function_ `virtual double GetDataAsDouble(int32 Key) const override`
- L304 _public function_ `virtual const FString& GetDataAsString(int32 Key) const override`
- L314 _private member_ `TMap<int32, ContextData> DataMap;`
- L315 _private member_ `bool bDefaultReturnValue = true;`

#### class `UE::Insights::FFilterState`  
`class FFilterState`  
_L327-358_
- L332 _public function_ `FFilterState(TSharedRef<FFilter> InFilter) : Filter(InFilter)`
- L337 _public prototype_ `virtual ~FFilterState() = default;`
- L339 _public function_ `void SetSelectedOperator(TSharedPtr<IFilterOperator> InOperator)`
- L340 _public function_ `TSharedPtr<const IFilterOperator> GetSelectedOperator() const`
- L342 _public function_ `virtual void Update()`
- L344 _public prototype_ `virtual bool ApplyFilter(const FBaseFilterContext& Context) const;`
- L346 _public prototype_ `virtual void SetFilterValue(FString InTextValue);`
- L348 _public function_ `virtual bool HasCustomUI() const`
- L349 _public function_ `virtual void AddCustomUI(TSharedRef<SHorizontalBox> LeftBox)`
- L351 _public prototype_ `virtual bool Equals(const FFilterState& Other) const;`
- L352 _public prototype_ `virtual TSharedRef<FFilterState> DeepCopy() const;`
- L355 _protected member_ `TSharedRef<FFilter> Filter;`
- L356 _protected member_ `TSharedPtr<IFilterOperator> SelectedOperator;`
- L357 _protected member_ `FFilterContext::ContextData FilterValue;`

#### class `UE::Insights::FFilter`  
`class FFilter : public TSharedFromThis<FFilter>`  
_L362-396_
- inherits: `TSharedFromThis<FFilter>`
- L367 _public function_ `FFilter(int32 InKey, FText InName, FText InDesc, EFilterDataType InDataType, TSharedPtr<IFilterValueConverter> InConverter, SupportedOperatorsArrayPtr InSupportedOperators) : Key(InKey) , Name(InName) , Desc(InDesc) , DataType(InDataType) , Converter(InConverter) , SupportedOperators(InSupportedOperators)`
- L377 _public prototype_ `virtual ~FFilter() = default;`
- L379 _public function_ `int32 GetKey() const`
- L380 _public function_ `const FText& GetName() const`
- L381 _public function_ `const FText& GetDesc() const`
- L382 _public function_ `EFilterDataType GetDataType() const`
- L383 _public function_ `const TSharedPtr<IFilterValueConverter>& GetConverter() const`
- L384 _public function_ `SupportedOperatorsArrayConstPtr GetSupportedOperators() const`
- L386 _public function_ `virtual TSharedRef<FFilterState> BuildFilterState()`
- L387 _public function_ `virtual TSharedRef<FFilterState> BuildFilterState(const FFilterState& Other)`
- L390 _protected member_ `int32 Key;`
- L391 _protected member_ `FText Name;`
- L392 _protected member_ `FText Desc;`
- L393 _protected member_ `EFilterDataType DataType;`
- L394 _protected member_ `TSharedPtr<IFilterValueConverter> Converter;`
- L395 _protected member_ `SupportedOperatorsArrayPtr SupportedOperators;`

#### class `UE::Insights::FFilterWithSuggestionsValueConverter`  
`class FFilterWithSuggestionsValueConverter : public IFilterValueConverter`  
_L400-406_
- inherits: `IFilterValueConverter`
- L403 _public function_ `virtual bool Convert(const FString& Input, double& Output, FText& OutError) const override`
- L404 _public prototype_ `virtual FText GetTooltipText() const override;`
- L405 _public prototype_ `virtual FText GetHintText() const override;`

#### class `UE::Insights::FFilterWithSuggestions`  
`class FFilterWithSuggestions : public FFilter`  
_L410-436_
- inherits: `FFilter`
- L415 _public typedef_ `typedef TFunction<void(const FString& , TArray<FString>& OutSuggestions)> FGetSuggestionsCallback;`
- L418 _public function_ `FFilterWithSuggestions(int32 InKey, FText InName, FText InDesc, EFilterDataType InDataType, TSharedPtr<IFilterValueConverter> InConverter, SupportedOperatorsArrayPtr InSupportedOperators) : FFilter(InKey, InName, InDesc, InDataType, InConverter, InSupportedOperators)`
- L428 _public prototype_ `virtual ~FFilterWithSuggestions() = default;`
- L430 _public function_ `const FGetSuggestionsCallback& GetCallback() const`
- L431 _public function_ `void SetCallback(FGetSuggestionsCallback InCallback)`
- L432 _public function_ `void GetSuggestions(const FString& Text, TArray<FString>& OutSuggestions)`
- L435 _private member_ `FGetSuggestionsCallback Callback;`

#### class `UE::Insights::FFilterStorage`  
`class FFilterStorage`  
_L440-458_
- L443 _public prototype_ `FFilterStorage();`
- L444 _public prototype_ `~FFilterStorage();`
- L446 _public function_ `const TArray<TSharedPtr<FFilterGroupOperator>>& GetFilterGroupOperators() const`
- L448 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetDoubleOperators() const`
- L449 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetIntegerOperators() const`
- L450 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetStringOperators() const`
- L453 _private member_ `TArray<TSharedPtr<FFilterGroupOperator>> FilterGroupOperators;`
- L455 _private member_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> DoubleOperators;`
- L456 _private member_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> IntegerOperators;`
- L457 _private member_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> StringOperators;`

#### class `UE::Insights::FFilterService`  
`class FFilterService`  
_L462-490_
- L465 _public prototype_ `FFilterService();`
- L466 _public prototype_ `~FFilterService();`
- L468 _public prototype_ `static void Initialize();`
- L469 _public prototype_ `static void Shutdown();`
- L470 _public function_ `static TSharedPtr<FFilterService> Get()`
- L472 _public prototype_ `void RegisterTabSpawner();`
- L473 _public prototype_ `void UnregisterTabSpawner();`
- L474 _public prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L476 _public function_ `const TArray<TSharedPtr<FFilterGroupOperator>>& GetFilterGroupOperators() const`
- L478 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetDoubleOperators() const`
- L479 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetIntegerOperators() const`
- L480 _public function_ `TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> GetStringOperators() const`
- L482 _public prototype_ `TSharedPtr<SWidget> CreateFilterConfiguratorWidget(TSharedPtr<class FFilterConfigurator> FilterConfiguratorViewModel, TWeakPtr<SWidget> ParentWidget = nullptr);`
- L485 _private member_ `static const FName FilterConfiguratorTabId;`
- L486 _private member_ `static TSharedPtr<FFilterService> Instance;`
- L487 _private member_ `FFilterStorage FilterStorage;`
- L488 _private member_ `TSharedPtr<class SAdvancedFilter> PendingWidget;`
- L489 _private member_ `TWeakPtr<SWidget> PendingParentWidget;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Insights` (scope `UE`)
- L320 _typedef_ `typedef TSharedPtr<const TArray<TSharedPtr<IFilterOperator>>> SupportedOperatorsArrayConstPtr;` (scope `UE::Insights`)
- L321 _typedef_ `typedef TSharedPtr<TArray<TSharedPtr<IFilterOperator>>> SupportedOperatorsArrayPtr;` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/ViewModels/IFilterExecutor.h` (Public)


#### class `UE::Insights::IFilterExecutor`  
`class IFilterExecutor`  
_L12-16_
- L15 _public prototype_ `virtual bool ApplyFilters(const FBaseFilterContext& Context) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/ViewModels/TimeFilterValueConverter.h` (Public)


#### class `UE::Insights::FTimeFilterValueConverter`  
`class FTimeFilterValueConverter : public IFilterValueConverter`  
_L17-23_
- inherits: `IFilterValueConverter`
- L20 _public prototype_ `virtual bool Convert(const FString& Input, double& Output, FText& OutError) const override;`
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L22 _public prototype_ `virtual FText GetHintText() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/Widgets/SAdvancedFilter.h` (Public)


#### class `UE::Insights::SAdvancedFilter`  
`class SAdvancedFilter: public SCompoundWidget`  
_L28-70_
- inherits: `SCompoundWidget`
- desc: A custom widget used to configure custom filters.
- L32 _public prototype_ `SAdvancedFilter();` — Default constructor.
- L35 _public prototype_ `virtual ~SAdvancedFilter();` — Virtual destructor.
- L37 _public function_ `SLATE_BEGIN_ARGS(SAdvancedFilter)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FFilterConfigurator> InFilterConfiguratorViewModel);`
- L46 _public prototype_ `void Reset();`
- L48 _public function_ `void SetParentTab(const TSharedPtr<SDockTab> InTab)`
- L49 _public function_ `const TWeakPtr<SDockTab> GetParentTab()`
- L51 _public prototype_ `void RequestClose();`
- L54 _private prototype_ `void InitCommandList();`
- L56 _private prototype_ `FReply OK_OnClicked();`
- L58 _private prototype_ `FReply Cancel_OnClicked();`
- L61 _private member_ `TSharedPtr<SFilterConfigurator> FilterConfigurator;`
- L63 _private member_ `TWeakPtr<FFilterConfigurator> OriginalFilterConfiguratorViewModel;`
- L65 _private member_ `TSharedPtr<FFilterConfigurator> FilterConfiguratorViewModel;`
- L67 _private member_ `TWeakPtr<SDockTab> ParentTab;`
- L69 _private member_ `FDelegateHandle OnViewModelDestroyedHandle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/Widgets/SFilterConfigurator.h` (Public)


#### class `UE::Insights::SFilterConfigurator`  
`class SFilterConfigurator: public SCompoundWidget`  
_L28-84_
- inherits: `SCompoundWidget`
- desc: A custom widget used to configure custom filters.
- L32 _public prototype_ `SFilterConfigurator();` — Default constructor.
- L35 _public prototype_ `virtual ~SFilterConfigurator();` — Virtual destructor.
- L37 _public function_ `SLATE_BEGIN_ARGS(SFilterConfigurator)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FFilterConfigurator> InFilterConfiguratorViewModel);`
- L46 _public prototype_ `void Reset();`
- L53 _public prototype_ `void TreeView_OnGetChildren(FFilterConfiguratorNodePtr InParent, TArray<FFilterConfiguratorNodePtr>& OutChildren);` — Called by STreeView to retrieves the children for the specified parent item. @param InParent    - The parent node to retrieve the children from. @param OutChildren - List of children for the parent node.
- L56 _public prototype_ `TSharedRef<class ITableRow> TreeView_OnGenerateRow(FFilterConfiguratorNodePtr TreeNode, const TSharedRef<class STableViewBase>& OwnerTable);` — Called by STreeView to generate a table row for the specified item.
- L58 _public function_ `void SetParentTab(const TSharedPtr<SDockTab> InTab)`
- L59 _public function_ `const TWeakPtr<SDockTab> GetParentTab()`
- L61 _public prototype_ `void RequestClose();`
- L64 _private prototype_ `void InitCommandList();`
- L66 _private prototype_ `void SetInitialExpansionRec(const FFilterConfiguratorNodePtr& Node, bool Value);`
- L69 _private member_ `TSharedPtr<FFilterConfigurator> FilterConfiguratorViewModel;`
- L72 _private member_ `TSharedPtr<STreeView<FFilterConfiguratorNodePtr>> TreeView;` — The tree widget which holds the filters.
- L75 _private member_ `TSharedPtr<class SHeaderRow> TreeViewHeaderRow;` — Holds the tree view header row widget which display all columns in the tree view.
- L78 _private member_ `TSharedPtr<class SScrollBar> ExternalScrollbar;` — External scrollbar used to synchronize tree view position.
- L81 _private member_ `TArray<FFilterConfiguratorNodePtr> GroupNodes;` — A filtered array of group and filter nodes to be displayed in the tree widget.
- L83 _private member_ `TWeakPtr<SDockTab> ParentTab;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Filter/Widgets/SFilterConfiguratorRow.h` (Public)


#### class `UE::Insights::SFilterConfiguratorRow`  
`class SFilterConfiguratorRow : public SMultiColumnTableRow<FFilterConfiguratorNodePtr>`  
_L22-92_
- inherits: `SMultiColumnTableRow<FFilterConfiguratorNodePtr>`
- desc: Widget that represents a table row in the Filter's tree control. Generates widgets for each column on demand.
- L25 _public function_ `SFilterConfiguratorRow()`
- L26 _public prototype_ `~SFilterConfiguratorRow() = default;`
- L28 _public function_ `SLATE_BEGIN_ARGS(SFilterConfiguratorRow)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L35 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L38 _private prototype_ `const TArray<TSharedPtr<FFilter>>* GetAvailableFilters();`
- L40 _private prototype_ `TSharedRef<SWidget> AvailableFilters_OnGenerateWidget(TSharedPtr<FFilter> InFilter);`
- L42 _private prototype_ `void AvailableFilters_OnSelectionChanged(TSharedPtr<FFilter> InFilter, ESelectInfo::Type SelectInfo);`
- L44 _private prototype_ `FText AvailableFilters_GetSelectionText() const;`
- L46 _private prototype_ `const TArray<TSharedPtr<IFilterOperator>>* GetAvailableFilterOperators();`
- L48 _private prototype_ `TSharedRef<SWidget> AvailableFilterOperators_OnGenerateWidget(TSharedPtr<IFilterOperator> InFilter);`
- L50 _private prototype_ `void AvailableFilterOperators_OnSelectionChanged(TSharedPtr<IFilterOperator> InFilter, ESelectInfo::Type SelectInfo);`
- L52 _private prototype_ `FText AvailableFilterOperators_GetSelectionText() const;`
- L54 _private prototype_ `const TArray<TSharedPtr<FFilterGroupOperator>>* GetFilterGroupOperators();`
- L56 _private prototype_ `TSharedRef<SWidget> FilterGroupOperators_OnGenerateWidget(TSharedPtr<FFilterGroupOperator> InFilter);`
- L58 _private prototype_ `void FilterGroupOperators_OnSelectionChanged(TSharedPtr<FFilterGroupOperator> InFilter, ESelectInfo::Type SelectInfo);`
- L60 _private prototype_ `FText FilterGroupOperators_GetSelectionText() const;`
- L62 _private prototype_ `FReply AddFilter_OnClicked();`
- L63 _private prototype_ `FReply DeleteFilter_OnClicked();`
- L65 _private prototype_ `FReply AddGroup_OnClicked();`
- L66 _private prototype_ `FReply DeleteGroup_OnClicked();`
- L68 _private prototype_ `FText GetTextBoxValue() const;`
- L69 _private prototype_ `void OnTextBoxValueCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L71 _private prototype_ `FText GetTextBoxTooltipText() const;`
- L72 _private prototype_ `FText GetTextBoxHintText() const;`
- L73 _private prototype_ `bool TextBox_OnVerifyTextChanged(const FText& InText, FText& OutErrorMessage);`
- L75 _private prototype_ `void SuggestionTextBox_GetSuggestions(const FString& Text, TArray<FString>& Suggestions);`
- L76 _private prototype_ `void SuggestionTextBox_GetHistory(TArray<FString>& Suggestions);`
- L78 _private prototype_ `void SuggestionTextBox_OnValueChanged(const FText& InNewText);`
- L79 _private prototype_ `FText SuggestionTextBox_GetValue() const;`
- L80 _private prototype_ `void SuggestionTextBox_OnValueCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L83 _private member_ `FFilterConfiguratorNodePtr FilterConfiguratorNodePtr;`
- L85 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FFilter>>> FilterTypeComboBox;`
- L87 _private member_ `TSharedPtr<SComboBox<TSharedPtr<IFilterOperator>>> FilterOperatorComboBox;`
- L89 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FFilterGroupOperator>>> FilterGroupOperatorComboBox;`
- L91 _private member_ `FString SuggestionTextBoxValue;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/ITraceInsightsCoreModule.h` (Public)


#### class `ITraceInsightsCoreModule`  
`class ITraceInsightsCoreModule : public IModuleInterface`  
_L10-14_
- inherits: `IModuleInterface`
- desc: Interface for TraceInsightsCore module.
- L13 _public prototype_ `virtual ~ITraceInsightsCoreModule() = default;`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/BaseTreeNode.h` (Public)


#### class `UE::Insights::FBaseTreeNode`  
`class FBaseTreeNode : public TSharedFromThis<FBaseTreeNode>`  
_L43-542_
- inherits: `TSharedFromThis<FBaseTreeNode>`
- L73 _public function_ `explicit FBaseTreeNode(bool bInIsGroup) : GroupData(bInIsGroup ? new FGroupNodeData() : &DefaultGroupData)` — Initialization constructor for the node.
- L80 _public function_ `explicit FBaseTreeNode(const FName InName, bool bInIsGroup) : Name(InName) , GroupData(bInIsGroup ? new FGroupNodeData() : &DefaultGroupData)` — `UE_DEPRECATED(5.8, "Use the constructor without FName")` — Initialization constructor for the node.
- L86 _public function_ `virtual ~FBaseTreeNode()`
- L95 _public function_ `const FName& GetName() const` — `UE_DEPRECATED(5.8, "Override the GetDisplayName() instead")` — @returns a name of this node.
- L103 _public prototype_ `virtual const FText GetDisplayName() const;` — @returns a name of this node to display in tree view.
- L108 _public prototype_ `virtual const FText GetExtraDisplayName() const;` — @returns a name suffix for this node to display in tree view. Ex.: group nodes may include additional info, like the number of visible / total children.
- L113 _public prototype_ `virtual bool HasExtraDisplayName() const;` — @returns true if the node has an extra display name (a name suffix to display in tree view).
- L118 _public function_ `virtual const FText GetTooltipText() const` — @returns a descriptive text for this node to display in a tooltip.
- L126 _public prototype_ `static const FSlateBrush* GetDefaultIcon(bool bIsGroupNode);` — @returns the default icon for a group/leaf node.
- L131 _public function_ `virtual const FSlateBrush* GetIcon() const` — @returns the brush icon for this node.
- L139 _public prototype_ `static FLinearColor GetDefaultIconColor(bool bIsGroupNode);` — @returns the default color tint for a group or leaf node.
- L144 _public function_ `virtual FLinearColor GetIconColor() const` — @returns the color tint to be used for the icon of this node.
- L152 _public prototype_ `static FLinearColor GetDefaultColor(bool bIsGroupNode);` — @returns the default color tint for a group or leaf node.
- L157 _public function_ `virtual FLinearColor GetColor() const` — @returns the color tint to be used for the name text of this node.
- L168 _public function_ `FBaseTreeNodeWeak GetParentWeak() const` — @returns a weak reference to the parent group of this node; may be invalid.
- L176 _public function_ `FBaseTreeNodePtr GetParent() const` — @returns a reference to the parent group of this node; may be invalid.
- L187 _public function_ `bool IsGroup() const` — @returns true if this node is a group node.
- L195 _public function_ `void InitGroupData()` — Initializes the group data, allowing this node to accept children.
- L203 _public function_ `void RemoveGroupData()`
- L223 _public function_ `int32 GetChildrenCount() const` — @returns the number of children nodes.
- L231 _public function_ `void EnumerateChildren(TFunction<bool(const FBaseTreeNodePtr&)> Callback) const` — Enumerates the children nodes.
- L245 _public function_ `const TArray<FBaseTreeNodePtr>& GetChildren() const` — @returns a const reference to the children nodes of this group.
- L250 _public prototype_ `void SortChildren(const ITableCellValueSorter& Sorter, ESortMode SortMode);`
- L253 _public function_ `template <typename PredicateType> void SortChildren(PredicateType Predicate)`
- L259 _public function_ `void AddChild(const FBaseTreeNodePtr& ChildPtr)` — Adds specified node to the children nodes.
- L265 _public function_ `void AddChildAndSetParent(const FBaseTreeNodePtr& ChildPtr)` — Adds specified node to the children nodes. Also sets the current node as the parent group of the specified node.
- L272 _public function_ `void RemoveFromParent()` — Removes this node from the parent's children nodes (preserving the order). Also resets the parent group.
- L283 _public function_ `void RemoveFromParentSwap()` — Removes this node from the parent's children nodes (not preserving the order). Also resets the parent group.
- L294 _public function_ `int32 RemoveChild(const FBaseTreeNodePtr& ChildPtr)` — Removes the specified node from the children nodes (preserving the order). If successful, resets the parent group of the specified node.
- L305 _public function_ `int32 RemoveChildSwap(const FBaseTreeNodePtr& ChildPtr)` — Removes the specified node from the children nodes (not preserving the order). If successful, resets the parent group of the specified node.
- L315 _public function_ `void SetParent(const FBaseTreeNodeWeak& InParentWeak)`
- L320 _public function_ `void SetParentForChildren()`
- L329 _public function_ `void SetParentForChildrenRec()`
- L339 _public function_ `void ResetParentForChildren()`
- L347 _public function_ `void ResetParentForChildrenRec()`
- L357 _public function_ `void ClearChildren(int32 NewSize = 0)` — Clears children.
- L363 _public function_ `void SwapChildren(TArray<FBaseTreeNodePtr>& NewChildren)`
- L370 _public function_ `void SwapChildrenFast(TArray<FBaseTreeNodePtr>& NewChildren)`
- L378 _public function_ `virtual bool IsFiltered() const`
- L386 _public function_ `int32 GetFilteredChildrenCount() const` — @returns the number of filtered children nodes.
- L394 _public function_ `const FBaseTreeNodePtr& GetFilteredChildNode(int32 Index) const` — @returns a const reference to the filtered child node at specified index.
- L402 _public function_ `FBaseTreeNodePtr& GetFilteredChildNode(int32 Index)` — @returns a reference to the filtered child node at specified index.
- L410 _public function_ `void EnumerateFilteredChildren(TFunction<bool(const FBaseTreeNodePtr&)> Callback) const` — Enumerates the filtered children nodes.
- L424 _public function_ `const TArray<FBaseTreeNodePtr>& GetFilteredChildren() const` — @returns a const reference to the children nodes that should be visible to the UI based on filtering.
- L429 _public prototype_ `void SortFilteredChildren(const ITableCellValueSorter& Sorter, ESortMode SortMode);`
- L432 _public function_ `template <typename PredicateType> void SortFilteredChildren(PredicateType Predicate)`
- L438 _public function_ `void ClearFilteredChildren(int32 NewSize = 0)` — Clears (removes all) the filtered children nodes.
- L448 _public function_ `void AddFilteredChild(const FBaseTreeNodePtr& ChildPtr)` — Adds specified child to the filtered children nodes.
- L461 _public function_ `void ResetFilteredChildren()` — Resets the filtered children nodes. The filtered array of children nodes will be initialized with the unfiltered array of children.
- L474 _public function_ `void ResetFilteredChildrenRec()` — Resets the filtered children for this node and also recursively for all children nodes. The filtered array of children nodes will be initialized with the unfiltered array of children.
- L485 _public function_ `bool IsExpanded() const`
- L490 _public function_ `void SetExpansion(bool bOnOff)`
- L507 _public function_ `virtual uint32 GetDefaultSortOrder() const`
- L513 _public function_ `void SetDefaultSortOrder(uint32 Order)` — `UE_DEPRECATED(5.8, "Override GetDefaultSortOrder() in a custom node instead")`
- L522 _protected function_ `TArray<FBaseTreeNodePtr>& GetChildrenMutable()` — @returns a reference to the children nodes of this group.
- L529 _private member_ `uint32 DefaultSortOrder = 0;` — The default sort order. Index used to optimize sorting.
- L532 _private member_ `const FName Name;` — The name of this node.
- L535 _private member_ `FBaseTreeNodeWeak Parent;` — A weak pointer to the parent group of this node.
- L538 _private member_ `FGroupNodeData* GroupData;` — The struct containing properties of a group node. It is allocated only for group nodes.
- L541 _private member_ `static FGroupNodeData DefaultGroupData;` — The only group data for "not a group" nodes.

#### enum `UE::Insights::FBaseTreeNode::EGroupNodeFlags`  
`enum class EGroupNodeFlags : uint32`  
_L48-52_
- L50 _public enumerator_ `None = 0`
- L51 _public enumerator_ `IsExpanded = 1 << 0`

#### struct `UE::Insights::FBaseTreeNode::FGroupNodeData`  
`struct FGroupNodeData`  
_L54-67_
- L57 _public member_ `TArray<FBaseTreeNodePtr> Children;` — Children of the group node.
- L63 _public member_ `TArray<FBaseTreeNodePtr>* FilteredChildrenPtr = &Children;` — A pointer to the filtered children of the group node. If filter is empty (no filtering), this points directly to Children array.
- L66 _public member_ `EGroupNodeFlags Flags = EGroupNodeFlags::None;` — Various flags specific to a group node.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Insights` (scope `UE`)
- L30 _typedef_ `typedef TSharedPtr<class FBaseTreeNode> FBaseTreeNodePtr;` (scope `UE::Insights`) — Type definition for shared pointers to instances of FBaseTreeNode.
- L33 _typedef_ `typedef TSharedRef<class FBaseTreeNode> FBaseTreeNodeRef;` (scope `UE::Insights`) — Type definition for shared references to instances of FBaseTreeNode.
- L36 _typedef_ `typedef TSharedRef<const class FBaseTreeNode> FBaseTreeNodeRefConst;` (scope `UE::Insights`) — Type definition for shared references to const instances of FBaseTreeNode.
- L39 _typedef_ `typedef TWeakPtr<class FBaseTreeNode> FBaseTreeNodeWeak;` (scope `UE::Insights`) — Type definition for weak references to instances of FBaseTreeNode.

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/Table.h` (Public)


#### class `UE::Insights::FTable`  
`class FTable : public TSharedFromThis<FTable>`  
_L27-84_
- inherits: `TSharedFromThis<FTable>`
- desc: Table View Model. View model class for the STableListView and STableTreeView widgets.
- L30 _public prototype_ `FTable();`
- L31 _public prototype_ `virtual ~FTable();`
- L33 _public function_ `const FText& GetDisplayName() const`
- L34 _public function_ `void SetDisplayName(const FText& InDisplayName)`
- L36 _public function_ `const FText& GetDescription() const`
- L37 _public function_ `void SetDescription(const FText& InDescription)`
- L39 _public prototype_ `virtual void Reset();`
- L41 _public function_ `int32 GetColumnCount() const`
- L42 _public function_ `bool IsValid() const`
- L44 _public function_ `const TArray<TSharedRef<FTableColumn>>& GetColumns() const`
- L45 _public prototype_ `void SetColumns(const TArray<TSharedRef<FTableColumn>>& InColumns);`
- L47 _public prototype_ `void GetVisibleColumns(TArray<TSharedRef<FTableColumn>>& InArray) const;`
- L49 _public function_ `TSharedRef<FTableColumn> FindColumnChecked(const FName& ColumnId) const`
- L54 _public function_ `TSharedPtr<FTableColumn> FindColumn(const FName& ColumnId) const`
- L64 _public prototype_ `int32 GetColumnPositionIndex(const FName& ColumnId) const;`
- L66 _public prototype_ `void GetVisibleColumnsData(const TArray<TSharedPtr<FBaseTreeNode>>& InNodes, const FName& LogListingName, TCHAR Separator, bool bIncludeHeaders, FString& OutData) const;`
- L68 _public prototype_ `static const FName GetHierarchyColumnId();`
- L71 _protected function_ `void ResetColumns()`
- L72 _protected prototype_ `void AddColumn(TSharedRef<FTableColumn> Column);`
- L73 _protected prototype_ `void AddHierarchyColumn(int32 ColumnIndex, const TCHAR* ColumnName);`
- L76 _private member_ `FText DisplayName;`
- L77 _private member_ `FText Description;`
- L80 _private member_ `TArray<TSharedRef<FTableColumn>> Columns;` — All available columns.
- L83 _private member_ `TMap<FName, TSharedRef<FTableColumn>> ColumnIdToPtrMapping;` — Mapping between column Ids and FTableColumn shared refs.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableCellValue.h` (Public)


#### enum `UE::Insights::ETableCellDataType`  
`enum class ETableCellDataType : uint32`  
_L17-35_
- L19 _public enumerator_ `Unknown`
- L22 _public enumerator_ `Bool` — Basic types.
- L24 _public enumerator_ `Int64` — Int32,
- L25 _public enumerator_ `Float`
- L26 _public enumerator_ `Double`
- L27 _public enumerator_ `CString`
- L30 _public enumerator_ `Custom` — Custom types.
- L31 _public enumerator_ `Text` — FTextCustomTableCellValue
- L34 _public enumerator_ `InvalidOrMax` — Invalid enum type, may be used as a number of enumerations.

#### class `UE::Insights::ICustomTableCellValue`  
`class ICustomTableCellValue`  
_L39-46_
- L42 _public prototype_ `virtual bool AsBool() const = 0;`
- L43 _public prototype_ `virtual int64 AsInt64() const = 0;`
- L44 _public prototype_ `virtual double AsDouble() const = 0;`
- L45 _public prototype_ `virtual FText AsText() const = 0;`

#### class `UE::Insights::FTextCustomTableCellValue`  
`class FTextCustomTableCellValue : public ICustomTableCellValue`  
_L50-65_
- inherits: `ICustomTableCellValue`
- L53 _public function_ `FTextCustomTableCellValue(const FText& InText) : Text(InText)`
- L54 _public prototype_ `virtual ~FTextCustomTableCellValue() = default;`
- L56 _public function_ `virtual bool AsBool() const override`
- L57 _public function_ `virtual int64 AsInt64() const override`
- L58 _public function_ `virtual double AsDouble() const override`
- L59 _public function_ `virtual FText AsText() const override`
- L61 _public function_ `const FText& GetText() const`
- L64 _private member_ `const FText Text;`

#### struct `UE::Insights::FTableCellValue`  
`struct FTableCellValue`  
_L69-194_
- L72 _public function_ `FTableCellValue() : DataType(ETableCellDataType::Unknown)`
- L74 _public function_ `explicit FTableCellValue(bool Value) : DataType(ETableCellDataType::Bool), Bool(Value)`
- L75 _public function_ `explicit FTableCellValue(int64 Value) : DataType(ETableCellDataType::Int64), Int64(Value)`
- L76 _public function_ `explicit FTableCellValue(float Value) : DataType(ETableCellDataType::Float), Float(Value)`
- L77 _public function_ `explicit FTableCellValue(double Value) : DataType(ETableCellDataType::Double), Double(Value)`
- L78 _public function_ `explicit FTableCellValue(const TCHAR* Value) : DataType(ETableCellDataType::CString), CString(Value)`
- L79 _public function_ `explicit FTableCellValue(TSharedPtr<ICustomTableCellValue> Value, uint64 Id = 0) : DataType(ETableCellDataType::Custom), ValueId(Id), Custom(Value)`
- L80 _public function_ `explicit FTableCellValue(const FText& Value, uint64 Id = 0) : DataType(ETableCellDataType::Text), ValueId(Id), Custom(MakeShared<FTextCustomTableCellValue>(Value))`
- L82 _public function_ `bool AsBool() const`
- L96 _public function_ `int64 AsInt64() const`
- L110 _public function_ `float AsFloat() const`
- L124 _public function_ `double AsDouble() const`
- L138 _public function_ `FString AsString() const`
- L152 _public function_ `FText AsText() const`
- L166 _public function_ `const FText& GetText() const`
- L175 _public function_ `uint64 GetValueId() const`
- L181 _public member_ `ETableCellDataType DataType;`
- L193 _public member_ `TSharedPtr<ICustomTableCellValue> Custom;`

#### union `UE::Insights::FTableCellValue::(anonymous)`  
``  
_L184-191_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)
- L185 _member_ `bool Bool;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`)
- L186 _member_ `int64 Int64;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`)
- L187 _member_ `float Float;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`)
- L188 _member_ `double Double;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`)
- L189 _member_ `const TCHAR* CString;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`) — should be valid for the lifetime of the owner table
- L190 _member_ `uint64 ValueId;` (scope `UE::Insights::FTableCellValue::__anon5e19350a010a`) — only used by Custom types

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableCellValueFormatter.h` (Public)


#### class `UE::Insights::ITableCellValueFormatter`  
`class ITableCellValueFormatter`  
_L25-40_
- L28 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const = 0;`
- L29 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const = 0;`
- L31 _public prototype_ `virtual FText FormatValue(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L32 _public prototype_ `virtual FText FormatValueForTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L33 _public prototype_ `virtual FText FormatValueForGrouping(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L35 _public prototype_ `virtual FText CopyValue(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L36 _public prototype_ `virtual FText CopyTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GenerateCustomWidget(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L39 _public prototype_ `virtual TSharedPtr<IToolTip> GetCustomTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`

#### class `UE::Insights::FTableCellValueFormatter`  
`class FTableCellValueFormatter : public ITableCellValueFormatter`  
_L44-64_
- inherits: `ITableCellValueFormatter`
- L47 _public function_ `FTableCellValueFormatter()`
- L48 _public prototype_ `virtual ~FTableCellValueFormatter() = default;`
- L50 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`
- L51 _public function_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override`
- L53 _public prototype_ `virtual FText FormatValue(const FTableColumn& Column, const FBaseTreeNode& Node) const override;` — { return FormatValue(Column.GetValue(Node)); }
- L54 _public prototype_ `virtual FText FormatValueForTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const override;` — { return FormatValueForTooltip(Column.GetValue(Node)); }
- L55 _public prototype_ `virtual FText FormatValueForGrouping(const FTableColumn& Column, const FBaseTreeNode& Node) const override;` — { return FormatValueForTooltip(Column.GetValue(Node)); }
- L57 _public prototype_ `virtual FText CopyValue(const FTableColumn& Column, const FBaseTreeNode& Node) const override;` — { return FormatValue(Column, Node); }
- L58 _public prototype_ `virtual FText CopyTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const override;` — { return FormatValueForTooltip(Column, Node); }
- L60 _public function_ `virtual TSharedPtr<SWidget> GenerateCustomWidget(const FTableColumn& Column, const FBaseTreeNode& Node) const override`
- L61 _public prototype_ `virtual TSharedPtr<IToolTip> GetCustomTooltip(const FTableColumn& Column, const FBaseTreeNode& Node) const override;`
- L63 _public prototype_ `static EVisibility GetTooltipVisibility();`

#### class `UE::Insights::FTextValueFormatter`  
`class FTextValueFormatter : public FTableCellValueFormatter`  
_L68-79_
- inherits: `FTableCellValueFormatter`
- L71 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`

#### class `UE::Insights::FAsTextValueFormatter`  
`class FAsTextValueFormatter : public FTableCellValueFormatter`  
_L83-94_
- inherits: `FTableCellValueFormatter`
- L86 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`

#### class `UE::Insights::FBoolValueFormatterAsTrueFalse`  
`class FBoolValueFormatterAsTrueFalse : public FTableCellValueFormatter`  
_L98-102_
- inherits: `FTableCellValueFormatter`
- L101 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FBoolValueFormatterAsOnOff`  
`class FBoolValueFormatterAsOnOff : public FTableCellValueFormatter`  
_L106-110_
- inherits: `FTableCellValueFormatter`
- L109 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FInt64ValueFormatterAsNumber`  
`class FInt64ValueFormatterAsNumber : public FTableCellValueFormatter`  
_L114-121_
- inherits: `FTableCellValueFormatter`
- L117 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`

#### class `UE::Insights::FInt64ValueFormatterAsUInt32InfiniteNumber`  
`class FInt64ValueFormatterAsUInt32InfiniteNumber : public FTableCellValueFormatter`  
_L125-130_
- inherits: `FTableCellValueFormatter`
- L128 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L129 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FInt64ValueFormatterAsHex32`  
`class FInt64ValueFormatterAsHex32 : public FTableCellValueFormatter`  
_L137-144_
- inherits: `FTableCellValueFormatter`
- L140 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`

#### class `UE::Insights::FInt64ValueFormatterAsHex64`  
`class FInt64ValueFormatterAsHex64 : public FTableCellValueFormatter`  
_L148-155_
- inherits: `FTableCellValueFormatter`
- L151 _public function_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override`

#### class `UE::Insights::FInt64ValueFormatterAsMemory`  
`class FInt64ValueFormatterAsMemory : public FTableCellValueFormatter`  
_L159-178_
- inherits: `FTableCellValueFormatter`
- L162 _public function_ `FInt64ValueFormatterAsMemory()`
- L166 _public prototype_ `virtual ~FInt64ValueFormatterAsMemory() = default;`
- L168 _public function_ `const FNumberFormattingOptions& GetFormattingOptions() const`
- L169 _public function_ `FNumberFormattingOptions& GetFormattingOptions()`
- L171 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L172 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override;`
- L174 _public prototype_ `static FText FormatForTooltip(int64 InValue);`
- L177 _private member_ `FNumberFormattingOptions FormattingOptions;`

#### class `UE::Insights::FFloatValueFormatterAsNumber`  
`class FFloatValueFormatterAsNumber : public FTableCellValueFormatter`  
_L182-186_
- inherits: `FTableCellValueFormatter`
- L185 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FFloatValueFormatterAsTimeAuto`  
`class FFloatValueFormatterAsTimeAuto : public FTableCellValueFormatter`  
_L190-195_
- inherits: `FTableCellValueFormatter`
- L193 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L194 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FDoubleValueFormatterAsNumber`  
`class FDoubleValueFormatterAsNumber : public FTableCellValueFormatter`  
_L199-203_
- inherits: `FTableCellValueFormatter`
- L202 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FDoubleValueFormatterAsCustomNumber`  
`class FDoubleValueFormatterAsCustomNumber : public FTableCellValueFormatter`  
_L207-223_
- inherits: `FTableCellValueFormatter`
- L210 _public function_ `FDoubleValueFormatterAsCustomNumber()`
- L214 _public prototype_ `virtual ~FDoubleValueFormatterAsCustomNumber() = default;`
- L216 _public function_ `const FNumberFormattingOptions& GetFormattingOptions() const`
- L217 _public function_ `FNumberFormattingOptions& GetFormattingOptions()`
- L219 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L222 _private member_ `FNumberFormattingOptions FormattingOptions;`

#### class `UE::Insights::FDoubleValueFormatterAsPercent`  
`class FDoubleValueFormatterAsPercent : public FTableCellValueFormatter`  
_L227-244_
- inherits: `FTableCellValueFormatter`
- L230 _public function_ `FDoubleValueFormatterAsPercent()`
- L235 _public prototype_ `virtual ~FDoubleValueFormatterAsPercent() = default;`
- L237 _public function_ `const FNumberFormattingOptions& GetFormattingOptions() const`
- L238 _public function_ `FNumberFormattingOptions& GetFormattingOptions()`
- L240 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L243 _private member_ `FNumberFormattingOptions FormattingOptions;`

#### class `UE::Insights::FDoubleValueFormatterAsTimeAuto`  
`class FDoubleValueFormatterAsTimeAuto : public FTableCellValueFormatter`  
_L248-253_
- inherits: `FTableCellValueFormatter`
- L251 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L252 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FDoubleValueFormatterAsTimeMs`  
`class FDoubleValueFormatterAsTimeMs : public FTableCellValueFormatter`  
_L257-262_
- inherits: `FTableCellValueFormatter`
- L260 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`
- L261 _public prototype_ `virtual FText FormatValueForTooltip(const TOptional<FTableCellValue>& InValue) const override;`

#### class `UE::Insights::FCStringValueFormatterAsText`  
`class FCStringValueFormatterAsText : public FTableCellValueFormatter`  
_L266-270_
- inherits: `FTableCellValueFormatter`
- L269 _public prototype_ `virtual FText FormatValue(const TOptional<FTableCellValue>& InValue) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Insights` (scope `UE`)
- L133 _typedef_ `typedef FInt64ValueFormatterAsUInt32InfiniteNumber FInt64ValueFormatterAsUInt32InfinteNumber;` (scope `UE::Insights`) — `UE_DEPRECATED(5.8, "Please fix the spelling for 'Infinte'")`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableCellValueGetter.h` (Public)


#### class `UE::Insights::ITableCellValueGetter`  
`class ITableCellValueGetter`  
_L21-26_
- L24 _public prototype_ `virtual const TOptional<FTableCellValue> GetValue(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`
- L25 _public prototype_ `virtual uint64 GetValueId(const FTableColumn& Column, const FBaseTreeNode& Node) const = 0;`

#### class `UE::Insights::FTableCellValueGetter`  
`class FTableCellValueGetter : public ITableCellValueGetter`  
_L30-38_
- inherits: `ITableCellValueGetter`
- L33 _public function_ `FTableCellValueGetter()`
- L34 _public prototype_ `virtual ~FTableCellValueGetter() = default;`
- L36 _public function_ `virtual const TOptional<FTableCellValue> GetValue(const FTableColumn& Column, const FBaseTreeNode& Node) const override`
- L37 _public function_ `virtual uint64 GetValueId(const FTableColumn& Column, const FBaseTreeNode& Node) const override`

#### class `UE::Insights::FNameValueGetter`  
`class FNameValueGetter : public FTableCellValueGetter`  
_L42-46_
- inherits: `FTableCellValueGetter`
- L45 _public prototype_ `virtual const TOptional<FTableCellValue> GetValue(const FTableColumn& Column, const FBaseTreeNode& Node) const override;`

#### class `UE::Insights::FDisplayNameValueGetter`  
`class FDisplayNameValueGetter : public FTableCellValueGetter`  
_L50-54_
- inherits: `FTableCellValueGetter`
- L53 _public prototype_ `virtual const TOptional<FTableCellValue> GetValue(const FTableColumn& Column, const FBaseTreeNode& Node) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableCellValueSorter.h` (Public)


#### enum `UE::Insights::ESortMode`  
`enum class ESortMode`  
_L23-27_
- L25 _public enumerator_ `Ascending`
- L26 _public enumerator_ `Descending`

#### class `UE::Insights::ITableCellValueSorter`  
`class ITableCellValueSorter`  
_L33-49_
- L36 _public prototype_ `virtual FName GetName() const = 0;`
- L37 _public prototype_ `virtual FText GetShortName() const = 0;`
- L38 _public prototype_ `virtual FText GetTitleName() const = 0;`
- L39 _public prototype_ `virtual FText GetDescription() const = 0;`
- L40 _public prototype_ `virtual FName GetColumnId() const = 0;`
- L42 _public prototype_ `virtual FSlateBrush* GetIcon(ESortMode SortMode) const = 0;`
- L44 _public prototype_ `virtual FTreeNodeCompareFunc GetTreeNodeCompareDelegate(ESortMode SortMode) const = 0;`
- L46 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const = 0;`
- L48 _public prototype_ `virtual void SetAsyncOperationProgress(IAsyncOperationProgress* AsyncOperationProgress) = 0;`

#### class `UE::Insights::FTableCellValueSorter`  
`class FTableCellValueSorter : public ITableCellValueSorter`  
_L53-97_
- inherits: `ITableCellValueSorter`
- L56 _public prototype_ `FTableCellValueSorter(const FName InName, const FText& InShortName, const FText& InTitleName, const FText& InDescription, TSharedRef<FTableColumn> InColumnRef);`
- L57 _public prototype_ `virtual ~FTableCellValueSorter() = default;`
- L59 _public function_ `virtual FName GetName() const override`
- L60 _public function_ `virtual FText GetShortName() const override`
- L61 _public function_ `virtual FText GetTitleName() const override`
- L62 _public function_ `virtual FText GetDescription() const override`
- L63 _public function_ `virtual FName GetColumnId() const override`
- L65 _public function_ `virtual FSlateBrush* GetIcon(ESortMode SortMode) const override`
- L66 _public function_ `virtual FTreeNodeCompareFunc GetTreeNodeCompareDelegate(ESortMode SortMode) const override`
- L68 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`
- L70 _public function_ `virtual void SetAsyncOperationProgress(IAsyncOperationProgress* InAsyncOperationProgress) override`
- L72 _public function_ `bool ShouldSortGroupsFirst() const`
- L73 _public function_ `void SetShouldSortGroupsFirst(bool bOnOff)`
- L77 _protected prototype_ `bool CancelSort() const;` — Attempts to cancel the sort by throwing an exception. If exceptions are not available the return value is meant to be returned from sort predicates to speed up the sort.
- L78 _protected prototype_ `bool ShouldCancelSort() const;`
- L81 _protected member_ `FName Name;`
- L82 _protected member_ `FText ShortName;`
- L83 _protected member_ `FText TitleName;`
- L84 _protected member_ `FText Description;`
- L86 _protected member_ `TSharedRef<FTableColumn> ColumnRef;`
- L88 _protected member_ `FSlateBrush* AscendingIcon;`
- L89 _protected member_ `FSlateBrush* DescendingIcon;`
- L91 _protected member_ `FTreeNodeCompareFunc AscendingCompareDelegate;`
- L92 _protected member_ `FTreeNodeCompareFunc DescendingCompareDelegate;`
- L94 _protected member_ `IAsyncOperationProgress* AsyncOperationProgress = nullptr;`
- L96 _protected member_ `bool bShouldSortGroupsFirst = true;`

#### class `UE::Insights::FBaseTableColumnSorter`  
`class FBaseTableColumnSorter : public FTableCellValueSorter`  
_L101-105_
- inherits: `FTableCellValueSorter`
- L104 _public prototype_ `FBaseTableColumnSorter(TSharedRef<FTableColumn> InColumnRef);`

#### class `UE::Insights::FSorterByName`  
`class FSorterByName : public FTableCellValueSorter`  
_L109-113_
- inherits: `FTableCellValueSorter`
- L112 _public prototype_ `FSorterByName(TSharedRef<FTableColumn> InColumnRef);`

#### class `UE::Insights::FSorterByTypeName`  
`class FSorterByTypeName : public FTableCellValueSorter`  
_L117-121_
- inherits: `FTableCellValueSorter`
- L120 _public prototype_ `FSorterByTypeName(TSharedRef<FTableColumn> InColumnRef);`

#### class `UE::Insights::FSorterByBoolValue`  
`class FSorterByBoolValue : public FBaseTableColumnSorter`  
_L125-129_
- inherits: `FBaseTableColumnSorter`
- L128 _public prototype_ `FSorterByBoolValue(TSharedRef<FTableColumn> InColumnRef);`

#### class `UE::Insights::FSorterByInt64Value`  
`class FSorterByInt64Value : public FBaseTableColumnSorter`  
_L133-139_
- inherits: `FBaseTableColumnSorter`
- L136 _public prototype_ `FSorterByInt64Value(TSharedRef<FTableColumn> InColumnRef);`
- L138 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`

#### class `UE::Insights::FSorterByFloatValue`  
`class FSorterByFloatValue : public FBaseTableColumnSorter`  
_L143-149_
- inherits: `FBaseTableColumnSorter`
- L146 _public prototype_ `FSorterByFloatValue(TSharedRef<FTableColumn> InColumnRef);`
- L148 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`

#### class `UE::Insights::FSorterByDoubleValue`  
`class FSorterByDoubleValue : public FBaseTableColumnSorter`  
_L153-159_
- inherits: `FBaseTableColumnSorter`
- L156 _public prototype_ `FSorterByDoubleValue(TSharedRef<FTableColumn> InColumnRef);`
- L158 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`

#### class `UE::Insights::FSorterByCStringValue`  
`class FSorterByCStringValue : public FBaseTableColumnSorter`  
_L163-167_
- inherits: `FBaseTableColumnSorter`
- L166 _public prototype_ `FSorterByCStringValue(TSharedRef<FTableColumn> InColumnRef);`

#### class `UE::Insights::FSorterByTextValue`  
`class FSorterByTextValue : public FBaseTableColumnSorter`  
_L171-177_
- inherits: `FBaseTableColumnSorter`
- L174 _public prototype_ `FSorterByTextValue(TSharedRef<FTableColumn> InColumnRef);`
- L176 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`

#### class `UE::Insights::FSorterByTextValueWithId`  
`class FSorterByTextValueWithId : public FBaseTableColumnSorter`  
_L181-187_
- inherits: `FBaseTableColumnSorter`
- L184 _public prototype_ `FSorterByTextValueWithId(TSharedRef<FTableColumn> InColumnRef);`
- L186 _public prototype_ `virtual void Sort(TArray<FBaseTreeNodePtr>& NodesToSort, ESortMode SortMode) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)
- L19 _typedef_ `typedef TSharedPtr<class FBaseTreeNode> FBaseTreeNodePtr;` (scope `UE::Insights`)
- L31 _typedef_ `typedef TFunction<bool(const FBaseTreeNodePtr& A, const FBaseTreeNodePtr& B)> FTreeNodeCompareFunc;` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableColumn.h` (Public)


#### enum `UE::Insights::ETableColumnFlags`  
`enum class ETableColumnFlags : uint32`  
_L27-35_
- L29 _public enumerator_ `None = 0`
- L30 _public enumerator_ `ShouldBeVisible = (1 << 0)` — Column should be initially visible.
- L31 _public enumerator_ `CanBeHidden = (1 << 1)` — Column can be hidden.
- L32 _public enumerator_ `CanBeFiltered = (1 << 2)` — Column can be used for filtering.
- L33 _public enumerator_ `IsHierarchy = (1 << 3)` — Column is the hierarchy (name) column, in a tree view.
- L34 _public enumerator_ `IsDynamic = (1 << 4)` — Column is dynamic. The column's value can not be cached.

#### enum `UE::Insights::ETableColumnAggregation`  
`enum class ETableColumnAggregation : uint32`  
_L40-47_
- L42 _public enumerator_ `None = 0`
- L43 _public enumerator_ `Sum`
- L44 _public enumerator_ `Min`
- L45 _public enumerator_ `Max`
- L46 _public enumerator_ `SameValue`

#### class `UE::Insights::FTableColumn`  
`class FTableColumn`  
_L54-271_
- desc: Table Column View Model. Holds information about a column in STableListView or STableTreeView widgets.
- L58 _public prototype_ `FTableColumn() = delete;` — No default constructor.
- L61 _public function_ `FTableColumn(const FName InId) : Id(InId) , Index(-1) , ShortName() , TitleName() , Description() , bIsVisible(false) , Flags(ETableColumnFlags::None) , HorizontalAlignment(HAlign_Left) , InitialWidth(60.0f) , MinWidth(0.0f) , MaxWidth(FLT_MAX) , DataType(ETableCellDataType::Unknown) , Aggregation(ETableColumnAggregation::None) , ValueGetter(GetDefaultValueGetter()) , ValueFormatter(GetDefaultValueFormatter()) , ValueSorter(nullptr) , InitialSortMode(EColumnSortMode::Ascending) , ParentTable(nullptr)` — Initialization constructor.
- L85 _public function_ `const FName& GetId() const`
- L87 _public function_ `int32 GetIndex() const`
- L88 _public function_ `void SetIndex(int32 InIndex)`
- L93 _public function_ `const FText& GetShortName() const`
- L94 _public function_ `void SetShortName(const FText& InShortName)`
- L96 _public function_ `const FText& GetTitleName() const`
- L97 _public function_ `void SetTitleName(const FText& InTitleName)`
- L99 _public function_ `const FText& GetDescription() const`
- L100 _public function_ `void SetDescription(const FText& InDescription)`
- L105 _public function_ `bool IsVisible() const`
- L106 _public function_ `void Show()`
- L107 _public function_ `void Hide()`
- L108 _public function_ `void ToggleVisibility()`
- L109 _public function_ `void SetVisibilityFlag(bool bOnOff)`
- L110 _public function_ `void OnVisibilityChanged()`
- L113 _public function_ `bool ShouldBeVisible() const` — Whether this column should be initially visible.
- L116 _public function_ `bool CanBeHidden() const` — Whether this column can be hidden.
- L119 _public function_ `bool CanBeFiltered() const` — Whether this column can be used for filtering.
- L122 _public function_ `bool IsHierarchy() const` — Whether this column is the hierarchy (name) column, in a tree view.
- L125 _public function_ `bool IsDynamic() const` — Whether this column is dynamic or not. If a column is dynamic, the column's value can not be cached.
- L127 _public function_ `void SetFlags(ETableColumnFlags InFlags)`
- L132 _public function_ `EHorizontalAlignment GetHorizontalAlignment() const`
- L133 _public function_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)`
- L135 _public function_ `float GetInitialWidth() const`
- L136 _public function_ `void SetInitialWidth(float InWidth)`
- L138 _public function_ `float GetMinWidth() const`
- L139 _public function_ `void SetMinWidth(float InWidth)`
- L141 _public function_ `float GetMaxWidth() const`
- L142 _public function_ `void SetMaxWidth(float InWidth)`
- L148 _public function_ `bool IsFixedWidth() const` — If MinWidth == MaxWidth, this column has fixed width and cannot be resized.
- L153 _public function_ `ETableCellDataType GetDataType() const`
- L154 _public function_ `void SetDataType(ETableCellDataType InDataType)`
- L159 _public function_ `ETableColumnAggregation GetAggregation() const`
- L160 _public function_ `void SetAggregation(ETableColumnAggregation InAggregation)`
- L165 _public prototype_ `static TSharedRef<ITableCellValueGetter> GetDefaultValueGetter();`
- L167 _public function_ `TSharedRef<ITableCellValueGetter> GetValueGetter() const`
- L168 _public function_ `void SetValueGetter(TSharedRef<ITableCellValueGetter> InValueGetter)`
- L170 _public prototype_ `const TOptional<FTableCellValue> GetValue(const FBaseTreeNode& InNode) const;`
- L171 _public prototype_ `uint64 GetValueId(const FBaseTreeNode& InNode) const;`
- L176 _public prototype_ `static TSharedRef<ITableCellValueFormatter> GetDefaultValueFormatter();`
- L178 _public function_ `TSharedRef<ITableCellValueFormatter> GetValueFormatter() const`
- L179 _public function_ `void SetValueFormatter(TSharedRef<ITableCellValueFormatter> InValueFormatter)`
- L181 _public prototype_ `FText GetValueAsText(const FBaseTreeNode& InNode) const;`
- L182 _public prototype_ `FText GetValueAsTooltipText(const FBaseTreeNode& InNode) const;`
- L183 _public prototype_ `FText GetValueAsGroupingText(const FBaseTreeNode& InNode) const;`
- L185 _public prototype_ `FText CopyValue(const FBaseTreeNode& InNode) const;`
- L186 _public prototype_ `FText CopyTooltip(const FBaseTreeNode& InNode) const;`
- L188 _public prototype_ `FString GetValueAsSerializableString(const FBaseTreeNode& InNode) const;`
- L193 _public function_ `TSharedPtr<ITableCellValueSorter> GetValueSorter() const`
- L194 _public function_ `void SetValueSorter(TSharedPtr<ITableCellValueSorter> InValueSorter)`
- L197 _public function_ `bool CanBeSorted() const` — Whether this column can be used for sorting.
- L200 _public function_ `EColumnSortMode::Type GetInitialSortMode() const` — Gets the initial sorting mode.
- L203 _public function_ `void SetInitialSortMode(EColumnSortMode::Type InMode)` — Sets the initial sorting mode.
- L208 _public function_ `TSharedPtr<IFilterValueConverter> GetValueConverter() const`
- L209 _public function_ `void SetValueConverter(TSharedPtr<IFilterValueConverter> InValueConverter)`
- L213 _public function_ `TWeakPtr<FTable> GetParentTable() const`
- L214 _public function_ `void SetParentTable(TWeakPtr<FTable> InParentTable)`
- L220 _private member_ `FName Id;` — Id of the column.
- L223 _private member_ `int32 Index;` — Column index in source table.
- L226 _private member_ `FText ShortName;` — Short name of the column, displayed in the column header.
- L229 _private member_ `FText TitleName;` — Title name of the column, displayed as title in the column tooltip.
- L232 _private member_ `FText Description;` — Long name of the column, displayed in the column tooltip.
- L235 _private member_ `bool bIsVisible;` — Is this column visible?
- L238 _private member_ `ETableColumnFlags Flags;` — Other on/off switches.
- L241 _private member_ `EHorizontalAlignment HorizontalAlignment;` — Horizontal alignment of the content in this column.
- L243 _private member_ `float InitialWidth;`
- L244 _private member_ `float MinWidth;` — float InitialWidth;  < Initial column width.
- L245 _private member_ `float MaxWidth;` — float MinWidth;  < Minimum column width.
- L249 _private member_ `ETableCellDataType DataType;` — Data type for this column.
- L252 _private member_ `ETableColumnAggregation Aggregation;` — Aggregation for values in this column, when grouped.
- L255 _private member_ `TSharedRef<ITableCellValueGetter> ValueGetter;` — Custom getter for values identified by this column.
- L258 _private member_ `TSharedRef<ITableCellValueFormatter> ValueFormatter;` — Custom formatter for values displayed by this column.
- L261 _private member_ `TSharedPtr<ITableCellValueSorter> ValueSorter;` — Custom sorter for values displayed by this column.
- L264 _private member_ `EColumnSortMode::Type InitialSortMode;` — Initial sorting mode.
- L267 _private member_ `TSharedPtr<IFilterValueConverter> ValueConverter;` — Used in FilterConfigurator to convert from string to column's data type.
- L270 _private member_ `TWeakPtr<FTable> ParentTable;` — Parent table. Only one table instance can own this column.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)
- L36 _prototype_ `ENUM_CLASS_FLAGS(ETableColumnFlags);` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableImporter.h` (Public)


#### class `UE::Insights::FTableImporter`  
`class FTableImporter : public TSharedFromThis<FTableImporter>`  
_L28-68_
- inherits: `TSharedFromThis<FTableImporter>`
- L43 _public prototype_ `FTableImporter(FName InLogListingName);`
- L44 _public prototype_ `virtual ~FTableImporter();`
- L46 _public prototype_ `void StartImportProcess();`
- L47 _public prototype_ `void ImportFile(const FString& Filename);`
- L49 _public prototype_ `void StartDiffProcess();`
- L50 _public prototype_ `void DiffFiles(const FString& FilenameA, const FString& FilenameB);`
- L52 _public prototype_ `void CloseAllOpenTabs();`
- L55 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TableImportTreeView(const FSpawnTabArgs& Args, FName TableViewID, FText InDisplayName);`
- L56 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TableDiffTreeView(const FSpawnTabArgs& Args, FName TableViewID, FText InDisplayName);`
- L57 _private prototype_ `void OnTableImportTreeViewTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L59 _private prototype_ `void DisplayImportTable(FName TableViewID);`
- L60 _private prototype_ `void DisplayDiffTable(FName TableViewID);`
- L61 _private prototype_ `void TableImportServiceCallback(TSharedPtr<TraceServices::FTableImportCallbackParams> Params);`
- L63 _private prototype_ `FName GetTableID(const FString& Path);`
- L66 _private member_ `FName LogListingName;`
- L67 _private member_ `TMap<FName, FOpenTableTabData> OpenTablesMap;`

#### struct `UE::Insights::FTableImporter::FOpenTableTabData`  
`struct FOpenTableTabData`  
_L31-40_
- L33 _public member_ `TSharedPtr<SDockTab> Tab;`
- L34 _public member_ `TSharedPtr<SUntypedTableTreeView> TableTreeView;`
- L36 _public function_ `bool operator ==(const FOpenTableTabData& Other) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L16 _namespace_ `namespace TraceServices`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TableTreeNode.h` (Public)


#### struct `UE::Insights::FTableRowId`  
`struct FTableRowId`  
_L19-28_
- L21 _public member_ `static constexpr int32 InvalidRowIndex = -1;`
- L23 _public function_ `FTableRowId(int32 InRowIndex) : RowIndex(InRowIndex)`
- L25 _public function_ `bool HasValidIndex() const`
- L27 _public member_ `int32 RowIndex;`

#### class `UE::Insights::FTableTreeNode`  
`class FTableTreeNode : public FBaseTreeNode`  
_L51-181_
- inherits: `FBaseTreeNode`
- desc: Table Tree Node View Model. Class used to store information about a generic table tree node (used in STableTreeView).
- L59 _public function_ `explicit FTableTreeNode(TWeakPtr<FTable> InParentTable, int32 InRowIndex, bool IsGroup = false) : FBaseTreeNode(IsGroup) , ParentTable(InParentTable) , RowId(InRowIndex)` — Initialization constructor for a table record node.
- L67 _public function_ `explicit FTableTreeNode(TWeakPtr<FTable> InParentTable) : FBaseTreeNode(true) , ParentTable(InParentTable) , RowId(FTableRowId::InvalidRowIndex)` — Initialization constructor for a group node.
- L79 _public prototype_ `explicit FTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, int32 InRowIndex);` — `UE_DEPRECATED(5.8, "Use the constructor without FName.")` — Initialization constructor for a table record node.
- L83 _public prototype_ `explicit FTableTreeNode(const FName InGroupName, TWeakPtr<FTable> InParentTable);` — `UE_DEPRECATED(5.8, "Use the constructor without FName.")` — Initialization constructor for a group node.
- L87 _public prototype_ `explicit FTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, int32 InRowIndex, bool IsGroup);` — `UE_DEPRECATED(5.8, "Use the constructor without FName.")` — Initialization constructor for a table record node.
- L91 _public function_ `virtual ~FTableTreeNode()`
- L96 _public function_ `const TWeakPtr<FTable>& GetParentTable() const`
- L97 _public function_ `FTableRowId GetRowId() const`
- L98 _public function_ `int32 GetRowIndex() const`
- L100 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L105 _public function_ `void InitAggregatedValues()`
- L113 _public function_ `void CleanupAggregatedValues()`
- L122 _public function_ `void ResetAggregatedValues()`
- L127 _public function_ `void ResetAggregatedValue(const FName& ColumnId)`
- L135 _public function_ `bool HasAggregatedValue(const FName& ColumnId) const`
- L140 _public function_ `const FTableCellValue* FindAggregatedValue(const FName& ColumnId) const`
- L145 _public function_ `const FTableCellValue& GetAggregatedValue(const FName& ColumnId) const`
- L151 _public function_ `void SetAggregatedValue(const FName& ColumnId, const FTableCellValue& Value)`
- L159 _public function_ `virtual uint32 GetDefaultSortOrder() const override`
- L164 _public function_ `virtual bool IsFiltered() const`
- L165 _public function_ `virtual void SetIsFiltered(bool InValue)`
- L167 _public function_ `virtual bool OnLazyCreateChildren(TSharedPtr<STableTreeView> InTableTreeView)`
- L174 _public function_ `virtual const FTreeNodeGrouping* GetAuthorGrouping() const` — The grouping that has generated this node. This is used to correctly apply further groupings for the lazy created children. If this returns nullptr, grouping is not applied for lazy created children.
- L177 _protected member_ `TWeakPtr<FTable> ParentTable;`
- L178 _protected member_ `FTableRowId RowId = FTableRowId::InvalidRowIndex;`
- L179 _protected member_ `bool bIsFiltered = false;`
- L180 _protected member_ `TMap<FName, FTableCellValue>* AggregatedValues = nullptr;`

#### class `UE::Insights::FCustomTableTreeNode`  
`class FCustomTableTreeNode : public FTableTreeNode`  
_L185-363_
- inherits: `FTableTreeNode`
- L191 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, int32 InRowIndex, const FText& InDisplayName, bool IsGroup) : FTableTreeNode(InParentTable, InRowIndex, IsGroup) , DisplayName(InDisplayName) , IconBrush(FBaseTreeNode::GetDefaultIcon(true)) , IconColor(FBaseTreeNode::GetDefaultIconColor(true)) , Color(FBaseTreeNode::GetDefaultColor(true))` — Initialization constructor for a table record node.
- L201 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, int32 InRowIndex, const FText& InDisplayName, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor, bool IsGroup) : FTableTreeNode(InParentTable, InRowIndex, IsGroup) , DisplayName(InDisplayName) , IconBrush(InIconBrush) , IconColor(InIconColor) , Color(InColor)` — Initialization constructor for a table record node.
- L211 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, int32 InRowIndex, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor, bool IsGroup) : FTableTreeNode(InParentTable, InRowIndex, IsGroup) , DisplayName() , IconBrush(InIconBrush) , IconColor(InIconColor) , Color(InColor)` — Initialization constructor for a table record node.
- L221 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, const FText& InDisplayName) : FTableTreeNode(InParentTable) , DisplayName(InDisplayName) , IconBrush(FBaseTreeNode::GetDefaultIcon(true)) , IconColor(FBaseTreeNode::GetDefaultIconColor(true)) , Color(FBaseTreeNode::GetDefaultColor(true))` — Initialization constructor for the group node.
- L231 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, const FText& InDisplayName, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor) : FTableTreeNode(InParentTable) , DisplayName(InDisplayName) , IconBrush(InIconBrush) , IconColor(InIconColor) , Color(InColor)` — Initialization constructor for the group node.
- L241 _public function_ `explicit FCustomTableTreeNode(TWeakPtr<FTable> InParentTable, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor) : FTableTreeNode(InParentTable) , DisplayName() , IconBrush(InIconBrush) , IconColor(InIconColor) , Color(InColor)` — Initialization constructor for the group node.
- L255 _public prototype_ `explicit FCustomTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, int32 InRowIndex, const FSlateBrush* InIconBrush, FLinearColor InColor, bool IsGroup);` — `UE_DEPRECATED(5.8, "Use the constructor without FName. Set name using SetDisplayName().")` — Initialization constructor for a table record node.
- L259 _public prototype_ `explicit FCustomTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, int32 InRowIndex, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor, bool IsGroup);` — `UE_DEPRECATED(5.8, "Use the constructor without FName. Set name using SetDisplayName().")` — Initialization constructor for a table record node.
- L263 _public prototype_ `explicit FCustomTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, FLinearColor InColor);` — `UE_DEPRECATED(5.8, "Use the constructor without FName. Set name using SetDisplayName().")` — Initialization constructor for the group node.
- L267 _public prototype_ `explicit FCustomTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, const FSlateBrush* InIconBrush, FLinearColor InColor);` — `UE_DEPRECATED(5.8, "Use the constructor without FName. Set name using SetDisplayName().")` — Initialization constructor for the group node.
- L271 _public prototype_ `explicit FCustomTableTreeNode(const FName InName, TWeakPtr<FTable> InParentTable, const FSlateBrush* InIconBrush, FLinearColor InIconColor, FLinearColor InColor);` — `UE_DEPRECATED(5.8, "Use the constructor without FName. Set name using SetDisplayName().")` — Initialization constructor for the group node.
- L275 _public prototype_ `virtual ~FCustomTableTreeNode() = default;`
- L280 _public function_ `virtual const FText GetDisplayName() const override`
- L288 _public function_ `void SetDisplayName(const FText& InDisplayName)` — Sets the display name for this node.
- L296 _public function_ `void SetDisplayName(FText&& InDisplayName)` — Sets the display name for this node.
- L304 _public function_ `virtual const FSlateBrush* GetIcon() const override`
- L312 _public function_ `void SetIcon(const FSlateBrush* InIconBrush)` — Sets an icon brush for this node.
- L320 _public function_ `virtual FLinearColor GetIconColor() const override`
- L328 _public function_ `void SetIconColor(const FLinearColor& InIconColor)` — Sets the color tint for the icon of this node.
- L336 _public function_ `virtual FLinearColor GetColor() const override`
- L344 _public function_ `void SetColor(const FLinearColor& InColor)` — Sets the color tint for the display name of this node.
- L353 _private member_ `FText DisplayName;` — The display name of this node.
- L356 _private member_ `const FSlateBrush* IconBrush;` — The icon of this node.
- L359 _private member_ `FLinearColor IconColor;` — The color tint for the icon of this node.
- L362 _private member_ `FLinearColor Color;` — The color tint for the display name of this node.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)
- L35 _typedef_ `typedef TSharedPtr<class FTableTreeNode> FTableTreeNodePtr;` (scope `UE::Insights`) — Type definition for shared pointers to instances of FTableTreeNode.
- L38 _typedef_ `typedef TSharedRef<class FTableTreeNode> FTableTreeNodeRef;` (scope `UE::Insights`) — Type definition for shared references to instances of FTableTreeNode.
- L41 _typedef_ `typedef TSharedRef<const class FTableTreeNode> FTableTreeNodeRefConst;` (scope `UE::Insights`) — Type definition for shared references to const instances of FTableTreeNode.
- L44 _typedef_ `typedef TWeakPtr<class FTableTreeNode> FTableTreeNodeWeak;` (scope `UE::Insights`) — Type definition for weak references to instances of FTableTreeNode.

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/TreeNodeGrouping.h` (Public)


#### class `UE::Insights::ITreeNodeGrouping`  
`class ITreeNodeGrouping`  
_L34-47_
- L39 _public prototype_ `virtual FText GetShortName() const = 0;`
- L40 _public prototype_ `virtual FText GetTitleName() const = 0;`
- L41 _public prototype_ `virtual FText GetDescription() const = 0;`
- L43 _public prototype_ `virtual const FSlateBrush* GetIcon() const = 0;`
- L44 _public prototype_ `virtual const FLinearColor& GetColor() const = 0;`
- L46 _public prototype_ `virtual FName GetColumnId() const = 0;`

#### class `UE::Insights::FTreeNodeGroupInfo`  
`class FTreeNodeGroupInfo`  
_L51-99_
- L54 _public prototype_ `FTreeNodeGroupInfo() = default;`
- L56 _public function_ `FTreeNodeGroupInfo(const FName& InName, bool bInIsExpanded = false) : Name(InName) , bIsExpanded(bInIsExpanded)`
- L62 _public function_ `FTreeNodeGroupInfo(const FName& InName, bool bInIsExpanded, const FLinearColor& InColor) : Name(InName) , bIsExpanded(bInIsExpanded) , bIsCustom(true) , Icon(nullptr) , IconColor(InColor) , Color(InColor)`
- L72 _public function_ `FTreeNodeGroupInfo(const FName& InName, bool bInIsExpanded, const FSlateBrush* InIcon, const FLinearColor& InIconColor, const FLinearColor& InColor) : Name(InName) , bIsExpanded(bInIsExpanded) , bIsCustom(true) , Icon(InIcon) , IconColor(InIconColor) , Color(InColor)`
- L82 _public function_ `const FName& GetName() const`
- L83 _public function_ `FText GetDisplayName() const`
- L85 _public function_ `bool IsExpanded() const`
- L86 _public function_ `bool IsCustom() const`
- L88 _public function_ `const FSlateBrush* GetIcon() const`
- L89 _public function_ `const FLinearColor& GetIconColor() const`
- L90 _public function_ `const FLinearColor& GetColor() const`
- L93 _private member_ `FName Name;`
- L94 _private member_ `bool bIsExpanded = false;`
- L95 _private member_ `bool bIsCustom = false;`
- L96 _private member_ `const FSlateBrush* Icon = nullptr;`
- L97 _private member_ `FLinearColor IconColor;`
- L98 _private member_ `FLinearColor Color;`

#### class `UE::Insights::FTreeNodeGrouping`  
`class FTreeNodeGrouping : public ITreeNodeGrouping`  
_L103-138_
- inherits: `ITreeNodeGrouping`
- L108 _public prototype_ `FTreeNodeGrouping();`
- L109 _public prototype_ `FTreeNodeGrouping(const FText& InShortName, const FText& InTitleName, const FText& InDescription, const FSlateBrush* InIcon);`
- L111 _public prototype_ `FTreeNodeGrouping(const FTreeNodeGrouping&) = delete;`
- L112 _public prototype_ `FTreeNodeGrouping& operator=(FTreeNodeGrouping&) = delete;`
- L114 _public prototype_ `virtual ~FTreeNodeGrouping() = default;`
- L117 _public function_ `virtual FText GetShortName() const override` — ITreeNodeGrouping
- L118 _public function_ `virtual FText GetTitleName() const override`
- L119 _public function_ `virtual FText GetDescription() const override`
- L120 _public function_ `virtual const FSlateBrush* GetIcon() const override`
- L121 _public function_ `virtual const FLinearColor& GetColor() const override`
- L122 _public function_ `virtual FName GetColumnId() const override`
- L124 _public function_ `virtual void SetIcon(const FSlateBrush* InIcon)`
- L125 _public function_ `virtual void SetColor(const FLinearColor& InColor)`
- L127 _public function_ `virtual FTreeNodeGroupInfo GetGroupForNode(const FBaseTreeNodePtr InNode) const`
- L128 _public prototype_ `virtual void GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const;`
- L130 _public prototype_ `static FLinearColor MakeDistinctColor(const FName& InName);`
- L133 _protected member_ `FText ShortName;`
- L134 _protected member_ `FText TitleName;`
- L135 _protected member_ `FText Description;`
- L136 _protected member_ `const FSlateBrush* Icon = nullptr;`
- L137 _protected member_ `FLinearColor Color;`

#### class `UE::Insights::FTreeNodeGroupingFlat`  
`class FTreeNodeGroupingFlat : public FTreeNodeGrouping`  
_L143-152_
- inherits: `FTreeNodeGrouping`
- desc: Creates a single group for all nodes.
- L148 _public prototype_ `FTreeNodeGroupingFlat();`
- L149 _public prototype_ `virtual ~FTreeNodeGroupingFlat() = default;`
- L151 _public prototype_ `virtual void GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const override;`

#### class `UE::Insights::FTreeNodeGroupingByUniqueValue`  
`class FTreeNodeGroupingByUniqueValue : public FTreeNodeGrouping`  
_L157-176_
- inherits: `FTreeNodeGrouping`
- desc: Creates a group for each unique value.
- L162 _public prototype_ `FTreeNodeGroupingByUniqueValue(TSharedRef<FTableColumn> InColumnRef);`
- L163 _public prototype_ `virtual ~FTreeNodeGroupingByUniqueValue() = default;`
- L165 _public prototype_ `virtual FTreeNodeGroupInfo GetGroupForNode(const FBaseTreeNodePtr InNode) const override;`
- L167 _public function_ `virtual FName GetColumnId() const override`
- L168 _public function_ `TSharedRef<FTableColumn> GetColumn() const`
- L171 _protected prototype_ `TSharedRef<FCustomTableTreeNode> CreateGroupNode(TWeakPtr<FTable> InParentTable, const FText& InGroupName) const;`
- L172 _protected prototype_ `TSharedRef<FCustomTableTreeNode> CreateUnsetGroupNode(TWeakPtr<FTable> InParentTable) const;`
- L175 _private member_ `TSharedRef<FTableColumn> ColumnRef;`

#### class `UE::Insights::TTreeNodeGroupingByUniqueValue`  
`template<typename Type> class TTreeNodeGroupingByUniqueValue : public FTreeNodeGroupingByUniqueValue`  
_L182-192_
- inherits: `FTreeNodeGroupingByUniqueValue`
- desc: Creates a group for each unique value (assumes data type of cell values is a simple type).
- L185 _public function_ `TTreeNodeGroupingByUniqueValue(TSharedRef<FTableColumn> InColumnRef) : FTreeNodeGroupingByUniqueValue(InColumnRef)`
- L186 _public prototype_ `virtual ~TTreeNodeGroupingByUniqueValue() = default;`
- L188 _public prototype_ `virtual void GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const override;`
- L191 _private prototype_ `static Type GetValue(const FTableCellValue& CellValue);`
- L195 _function_ `template<typename Type> void TTreeNodeGroupingByUniqueValue<Type>::GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const`

#### class `UE::Insights::FTreeNodeGroupingByUniqueValueCString`  
`class FTreeNodeGroupingByUniqueValueCString : public FTreeNodeGroupingByUniqueValue`  
_L258-268_
- inherits: `FTreeNodeGroupingByUniqueValue`
- desc: Creates a group for each unique value (assumes data type of cell values is const TCHAR*).
- L261 _public function_ `FTreeNodeGroupingByUniqueValueCString(TSharedRef<FTableColumn> InColumnRef) : FTreeNodeGroupingByUniqueValue(InColumnRef)`
- L262 _public prototype_ `virtual ~FTreeNodeGroupingByUniqueValueCString() = default;`
- L264 _public prototype_ `virtual void GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const override;`
- L267 _private prototype_ `static FName GetGroupName(const TCHAR* Value);`

#### class `UE::Insights::FTreeNodeGroupingByNameFirstLetter`  
`class FTreeNodeGroupingByNameFirstLetter : public FTreeNodeGrouping`  
_L273-282_
- inherits: `FTreeNodeGrouping`
- desc: Creates a group for each first letter of node names.
- L278 _public prototype_ `FTreeNodeGroupingByNameFirstLetter();`
- L279 _public prototype_ `virtual ~FTreeNodeGroupingByNameFirstLetter() = default;`
- L281 _public prototype_ `virtual FTreeNodeGroupInfo GetGroupForNode(const FBaseTreeNodePtr InNode) const override;`

#### class `UE::Insights::FTreeNodeGroupingByType`  
`class FTreeNodeGroupingByType : public FTreeNodeGrouping`  
_L287-296_
- inherits: `FTreeNodeGrouping`
- desc: Creates a group for each type.
- L292 _public prototype_ `FTreeNodeGroupingByType();`
- L293 _public prototype_ `virtual ~FTreeNodeGroupingByType() = default;`
- L295 _public prototype_ `virtual FTreeNodeGroupInfo GetGroupForNode(const FBaseTreeNodePtr InNode) const override;`

#### class `UE::Insights::FTreeNodeGroupingByPathBreakdown`  
`class FTreeNodeGroupingByPathBreakdown : public FTreeNodeGrouping`  
_L301-316_
- inherits: `FTreeNodeGrouping`
- desc: Creates a tree hierarchy out of the path structure of string values.
- L306 _public prototype_ `FTreeNodeGroupingByPathBreakdown(TSharedRef<FTableColumn> InColumnRef);`
- L307 _public prototype_ `virtual ~FTreeNodeGroupingByPathBreakdown() = default;`
- L309 _public prototype_ `virtual void GroupNodes(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, TWeakPtr<FTable> InParentTable, IAsyncOperationProgress& InAsyncOperationProgress) const override;`
- L311 _public function_ `virtual FName GetColumnId() const override`
- L312 _public function_ `TSharedRef<FTableColumn> GetColumn() const`
- L315 _private member_ `TSharedRef<FTableColumn> ColumnRef;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Insights` (scope `UE`)
- L250 _typedef_ `typedef TTreeNodeGroupingByUniqueValue<bool> FTreeNodeGroupingByUniqueValueBool;` (scope `UE::Insights`)
- L251 _typedef_ `typedef TTreeNodeGroupingByUniqueValue<int64> FTreeNodeGroupingByUniqueValueInt64;` (scope `UE::Insights`)
- L252 _typedef_ `typedef TTreeNodeGroupingByUniqueValue<float> FTreeNodeGroupingByUniqueValueFloat;` (scope `UE::Insights`)
- L253 _typedef_ `typedef TTreeNodeGroupingByUniqueValue<double> FTreeNodeGroupingByUniqueValueDouble;` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/ViewModels/UntypedTable.h` (Public)


#### class `UE::Insights::FUntypedTable`  
`class FUntypedTable : public FTable`  
_L26-46_
- inherits: `FTable`
- L29 _public prototype_ `FUntypedTable();`
- L30 _public prototype_ `virtual ~FUntypedTable();`
- L32 _public prototype_ `virtual void Reset();`
- L34 _public function_ `TSharedPtr<TraceServices::IUntypedTable> GetSourceTable() const`
- L35 _public function_ `TSharedPtr<TraceServices::IUntypedTableReader> GetTableReader() const`
- L38 _public prototype_ `bool UpdateSourceTable(TSharedPtr<TraceServices::IUntypedTable> InSourceTable);` — Update table content. Returns true if the table layout has changed.
- L41 _private prototype_ `void CreateColumns(const TraceServices::ITableLayout& TableLayout);`
- L44 _private member_ `TSharedPtr<TraceServices::IUntypedTable> SourceTable;`
- L45 _private member_ `TSharedPtr<TraceServices::IUntypedTableReader> TableReader;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L14 _namespace_ `namespace TraceServices`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/SAsyncOperationStatus.h` (Public)


#### class `UE::Insights::SAsyncOperationStatus`  
`class SAsyncOperationStatus : public SCompoundWidget`  
_L18-40_
- inherits: `SCompoundWidget`
- desc: A widget representing the status message used in table / tree views for background operations.
- L21 _public function_ `SLATE_BEGIN_ARGS(SAsyncOperationStatus)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IAsyncOperationStatusProvider> InStatusProvider);`
- L28 _private prototype_ `EVisibility GetContentVisibility() const;`
- L30 _private prototype_ `FSlateColor GetBackgroundColorAndOpacity() const;`
- L31 _private prototype_ `FSlateColor GetTextColorAndOpacity() const;`
- L32 _private prototype_ `float ComputeOpacity() const;`
- L34 _private prototype_ `FText GetText() const;`
- L35 _private prototype_ `FText GetAnimatedText() const;`
- L36 _private prototype_ `FText GetTooltipText() const;`
- L39 _private member_ `TWeakPtr<IAsyncOperationStatusProvider> StatusProvider;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/STableTreeView.h` (Public)


#### enum `UE::Insights::EAsyncOperationType`  
`enum class EAsyncOperationType : uint32`  
_L53-60_
- L55 _public enumerator_ `NodeFiltering = 1 << 0`
- L56 _public enumerator_ `Grouping = 1 << 1`
- L57 _public enumerator_ `Aggregation = 1 << 2`
- L58 _public enumerator_ `Sorting = 1 << 3`
- L59 _public enumerator_ `HierarchyFiltering = 1 << 4`

#### struct `UE::Insights::FTableColumnConfig`  
`struct FTableColumnConfig`  
_L64-69_
- L66 _public member_ `FName ColumnId;`
- L67 _public member_ `bool bIsVisible;`
- L68 _public member_ `float Width;`

#### class `UE::Insights::ITableTreeViewPreset`  
`class ITableTreeViewPreset`  
_L73-83_
- L76 _public prototype_ `virtual FText GetName() const = 0;`
- L77 _public prototype_ `virtual FText GetToolTip() const = 0;`
- L78 _public prototype_ `virtual FName GetSortColumn() const = 0;`
- L79 _public prototype_ `virtual EColumnSortMode::Type GetSortMode() const = 0;`
- L80 _public prototype_ `virtual void SetCurrentGroupings(const TArray<TSharedPtr<FTreeNodeGrouping>>& InAvailableGroupings, TArray<TSharedPtr<FTreeNodeGrouping>>& InOutCurrentGroupings) const = 0;`
- L81 _public prototype_ `virtual void GetColumnConfigSet(TArray<FTableColumnConfig>& InOutConfigSet) const = 0;`
- L82 _public function_ `virtual void OnAppliedToView(STableTreeView& TableTreeView) const`

#### class `UE::Insights::FTableTaskCancellationToken`  
`class FTableTaskCancellationToken`  
_L85-97_
- L88 _public function_ `FTableTaskCancellationToken() : bCancel(false)`
- L92 _public function_ `bool ShouldCancel()`
- L93 _public function_ `void Cancel()`
- L96 _private member_ `std::atomic<bool> bCancel;`

#### struct `UE::Insights::FTableTaskInfo`  
`struct FTableTaskInfo`  
_L99-103_
- L101 _public member_ `FGraphEventRef Event;`
- L102 _public member_ `TSharedPtr<FTableTaskCancellationToken> CancellationToken;`

#### class `UE::Insights::STableTreeView`  
`class STableTreeView : public SCompoundWidget, public IAsyncOperationStatusProvider`  
_L109-661_
- inherits: `SCompoundWidget,IAsyncOperationStatusProvider`
- desc: A custom widget used to display the list of tree nodes.
- L128 _public prototype_ `STableTreeView();` — Default constructor.
- L131 _public prototype_ `virtual ~STableTreeView();` — Virtual destructor.
- L133 _public function_ `SLATE_BEGIN_ARGS(STableTreeView)`
- L134 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTable> InTablePtr);`
- L142 _public function_ `TSharedPtr<STreeView<FTableTreeNodePtr>> GetInnerTreeView() const`
- L144 _public function_ `TSharedPtr<FTable>& GetTable()`
- L145 _public function_ `const TSharedPtr<FTable>& GetTable() const`
- L147 _public prototype_ `virtual void Reset();`
- L149 _public prototype_ `void RebuildColumns();`
- L158 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  AllottedGeometry The space allotted for this widget @param  InCurrentTime  Current absolute real time @param  InDeltaTime  Real time passed since last tick
- L164 _public prototype_ `virtual void RebuildTree(bool bResync);` — Rebuilds the tree (if necessary). @param bResync - If true, it forces a resync even if the list did not changed since last sync.
- L166 _public prototype_ `FTableTreeNodePtr GetNodeByTableRowIndex(int32 RowIndex) const;`
- L167 _public prototype_ `void SelectNodeByTableRowIndex(int32 RowIndex);`
- L168 _public function_ `bool IsRunningAsyncUpdate()`
- L170 _public prototype_ `void OnClose();`
- L172 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L177 _public function_ `virtual bool IsRunning() const override`
- L179 _public prototype_ `virtual double GetAllOperationsDuration() override;`
- L180 _public function_ `virtual double GetCurrentOperationDuration() override`
- L181 _public function_ `virtual uint32 GetOperationCount() const override`
- L182 _public prototype_ `virtual FText GetCurrentOperationName() const override;`
- L187 _public function_ `void SetLogListingName(const FName& InLogListingName)` — Sets a log listing name to be used for any errors or warnings. Must be preregistered by the caller with the MessageLog module.
- L188 _public function_ `const FName& GetLogListingName()`
- L191 _public function_ `const TArray<FTableTreeNodePtr>& GetTableRowNodes() const` — Gets the table row nodes. Each node corresponds to a table row. Index in this array corresponds to RowIndex in source table.
- L194 _public function_ `const TArray<TSharedPtr<FTreeNodeGrouping>>& GetAvailableGroupings() const` — Gets the available groupings.
- L197 _public prototype_ `void SetCurrentGroupings(TArray<TSharedPtr<FTreeNodeGrouping>>& InCurrentGroupings);` — Sets the current groupings.
- L200 _protected prototype_ `void InitCommandList();`
- L202 _protected prototype_ `virtual void ConstructWidget(TSharedPtr<FTable> InTablePtr);`
- L203 _protected prototype_ `virtual TSharedPtr<SWidget> ConstructFilterToolbar();`
- L204 _protected prototype_ `virtual TSharedRef<SWidget> ConstructHierarchyBreadcrumbTrail();`
- L205 _protected function_ `virtual TSharedPtr<SWidget> ConstructToolbar()`
- L206 _protected function_ `virtual TSharedPtr<SWidget> ConstructExtraToolbar()`
- L207 _protected function_ `virtual TSharedPtr<SWidget> ConstructFooter()`
- L208 _protected prototype_ `virtual void ConstructHeaderArea(TSharedRef<SVerticalBox> InHostBox);`
- L209 _protected prototype_ `virtual void ConstructFooterArea(TSharedRef<SVerticalBox> InHostBox);`
- L211 _protected prototype_ `void UpdateTree();`
- L216 _protected prototype_ `TSharedPtr<SWidget> TreeView_GetMenuContent();`
- L217 _protected prototype_ `void TreeView_BuildSortByMenu(FMenuBuilder& MenuBuilder);`
- L218 _protected prototype_ `void TreeView_BuildViewColumnMenu(FMenuBuilder& MenuBuilder);`
- L219 _protected prototype_ `void TreeView_BuildExportMenu(FMenuBuilder& MenuBuilder);`
- L221 _protected prototype_ `bool ContextMenu_CopySelectedToClipboard_CanExecute() const;`
- L222 _protected prototype_ `void ContextMenu_CopySelectedToClipboard_Execute();`
- L223 _protected prototype_ `bool ContextMenu_CopyColumnToClipboard_CanExecute() const;`
- L224 _protected prototype_ `void ContextMenu_CopyColumnToClipboard_Execute();`
- L225 _protected prototype_ `bool ContextMenu_CopyColumnTooltipToClipboard_CanExecute() const;`
- L226 _protected prototype_ `void ContextMenu_CopyColumnTooltipToClipboard_Execute();`
- L227 _protected prototype_ `bool ContextMenu_ExpandSubtree_CanExecute() const;`
- L228 _protected prototype_ `void ContextMenu_ExpandSubtree_Execute();`
- L229 _protected prototype_ `bool ContextMenu_ExpandCriticalPath_CanExecute() const;`
- L230 _protected prototype_ `void ContextMenu_ExpandCriticalPath_Execute();`
- L231 _protected prototype_ `bool ContextMenu_CollapseSubtree_CanExecute() const;`
- L232 _protected prototype_ `void ContextMenu_CollapseSubtree_Execute();`
- L233 _protected prototype_ `bool ContextMenu_ExportToFile_CanExecute() const;`
- L234 _protected prototype_ `void ContextMenu_ExportToFile_Execute(bool bInExportCollapsed, bool InExportLeafs);`
- L239 _protected prototype_ `void InitializeAndShowHeaderColumns();`
- L241 _protected prototype_ `FText GetColumnHeaderText(const FName ColumnId) const;`
- L243 _protected prototype_ `TSharedRef<SWidget> TreeViewHeaderRow_GenerateColumnMenu(const FTableColumn& Column);`
- L248 _protected prototype_ `void TreeView_Refresh();`
- L255 _protected prototype_ `void TreeView_OnGetChildren(FTableTreeNodePtr InParent, TArray<FTableTreeNodePtr>& OutChildren);` — Called by STreeView to retrieves the children for the specified parent item. @param InParent    - The parent node to retrieve the children from. @param OutChildren - List of children for the parent node.
- L258 _protected prototype_ `virtual void TreeView_OnSelectionChanged(FTableTreeNodePtr SelectedItem, ESelectInfo::Type SelectInfo);` — Called by STreeView when selection has changed.
- L261 _protected prototype_ `virtual void TreeView_OnExpansionChanged(FTableTreeNodePtr TreeNode, bool bShouldBeExpanded);` — Called by STreeView when a tree node is expanded or collapsed.
- L264 _protected prototype_ `virtual void TreeView_OnMouseButtonDoubleClick(FTableTreeNodePtr TreeNode);` — Called by STreeView when a tree item is double clicked.
- L270 _protected prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(FTableTreeNodePtr TreeNode, const TSharedRef<STableViewBase>& OwnerTable);` — Called by STreeView to generate a table row for the specified item.
- L272 _protected prototype_ `bool TableRow_ShouldBeEnabled(FTableTreeNodePtr NodePtr) const;`
- L274 _protected prototype_ `void TableRow_SetHoveredCell(TSharedPtr<FTable> TablePtr, TSharedPtr<FTableColumn> ColumnPtr, FTableTreeNodePtr NodePtr);`
- L275 _protected prototype_ `EHorizontalAlignment TableRow_GetColumnOutlineHAlignment(const FName ColumnId) const;`
- L277 _protected prototype_ `FText TableRow_GetHighlightText() const;`
- L282 _protected prototype_ `void InitNodeFiltering();`
- L284 _protected prototype_ `void OnNodeFilteringChanged();`
- L285 _protected prototype_ `bool ScheduleNodeFilteringAsyncOperationIfNeeded();`
- L286 _protected prototype_ `void ScheduleNodeFilteringAsyncOperation();`
- L287 _protected prototype_ `FGraphEventRef StartNodeFilteringTask(FGraphEventRef Prerequisite = nullptr);`
- L289 _protected prototype_ `void ApplyNodeFiltering();`
- L291 _protected function_ `virtual bool HasCustomNodeFilter() const`
- L292 _protected function_ `virtual bool FilterNodeCustom(const FTableTreeNode& InNode) const`
- L294 _protected prototype_ `virtual bool FilterNode(const FFilterConfigurator& InFilterConfigurator, const FTableTreeNode& InNode) const;`
- L296 _protected prototype_ `virtual void InitFilterConfigurator(FFilterConfigurator& InOutFilterConfigurator);`
- L297 _protected prototype_ `virtual void UpdateFilterContext(const FFilterConfigurator& InFilterConfigurator, const FTableTreeNode& InNode) const;`
- L299 _protected prototype_ `virtual TSharedRef<SWidget> ConstructFilterConfiguratorButton();`
- L300 _protected prototype_ `FReply FilterConfigurator_OnClicked();`
- L305 _protected prototype_ `void InitHierarchyFiltering();`
- L313 _protected prototype_ `static void HandleItemToStringArray(const FTableTreeNodePtr& GroupOrStatNodePtr, TArray<FString>& OutSearchStrings);` — Populates OutSearchStrings with the strings that should be used in searching. @param GroupOrStatNodePtr - the group and stat node to get a text description from. @param OutSearchStrings   - an array of strings to use in searching.
- L315 _protected prototype_ `void OnHierarchyFilteringChanged();`
- L316 _protected prototype_ `bool ScheduleHierarchyFilteringAsyncOperationIfNeeded();`
- L317 _protected prototype_ `void ScheduleHierarchyFilteringAsyncOperation();`
- L318 _protected prototype_ `FGraphEventRef StartHierarchyFilteringTask(FGraphEventRef Prerequisite = nullptr);`
- L320 _protected prototype_ `void ApplyHierarchyFiltering();`
- L321 _protected prototype_ `void ApplyEmptyHierarchyFilteringRec(FTableTreeNodePtr NodePtr);`
- L322 _protected prototype_ `bool ApplyHierarchyFilteringRec(FTableTreeNodePtr NodePtr);`
- L325 _protected prototype_ `bool MakeSubtreeVisible(FTableTreeNodePtr NodePtr, bool bFilterIsEmpty);` — Set all the nodes belonging to a subtree as visible. Returns true if the caller node should be expanded.
- L327 _protected prototype_ `virtual TSharedRef<SWidget> ConstructSearchBox();`
- L328 _protected prototype_ `void SearchBox_OnTextChanged(const FText& InFilterText);`
- L333 _protected prototype_ `void CreateGroupings();`
- L334 _protected prototype_ `virtual void InternalCreateGroupings();`
- L336 _protected prototype_ `void OnGroupingChanged();`
- L337 _protected prototype_ `bool ScheduleGroupingAsyncOperationIfNeeded();`
- L338 _protected prototype_ `void ScheduleGroupingAsyncOperation();`
- L339 _protected prototype_ `FGraphEventRef StartGroupingTask(FGraphEventRef Prerequisite = nullptr);`
- L340 _protected prototype_ `void ApplyGrouping();`
- L341 _protected prototype_ `void CreateGroups(const TArray<TSharedPtr<FTreeNodeGrouping>>& Groupings);`
- L342 _protected prototype_ `void GroupNodesRec(const TArray<FTableTreeNodePtr>& Nodes, FTableTreeNode& ParentGroup, int32 GroupingDepth, const TArray<TSharedPtr<FTreeNodeGrouping>>& Groupings);`
- L344 _protected prototype_ `void RebuildGroupingCrumbs();`
- L345 _protected prototype_ `TSharedRef<SWidget> GetGroupingCrumbButtonContent(const TSharedPtr<FTreeNodeGrouping>& CrumbGrouping, const FTextBlockStyle* InTextStyle);`
- L346 _protected prototype_ `void OnGroupingCrumbClicked(const TSharedPtr<FTreeNodeGrouping>& InEntry);`
- L347 _protected prototype_ `TSharedRef<SWidget> CreateGroupingMenuWidget(const FTreeNodeGrouping& Grouping) const;`
- L348 _protected prototype_ `void AddGroupingMenuEntries(FMenuBuilder& MenuBuilder, EGroupingMenuType MenuType, const TSharedPtr<FTreeNodeGrouping> CrumbGrouping, TFunction<bool(const FTreeNodeGrouping&)> FilterFunc);`
- L349 _protected prototype_ `void BuildGroupingSubMenu(FMenuBuilder& MenuBuilder, EGroupingMenuType MenuType, const TSharedPtr<FTreeNodeGrouping> CrumbGrouping);`
- L350 _protected prototype_ `TSharedRef<SWidget> GetGroupingCrumbMenuContent(const TSharedPtr<FTreeNodeGrouping>& CrumbGrouping);`
- L352 _protected prototype_ `void PreChangeGroupings();`
- L353 _protected prototype_ `void PostChangeGroupings();`
- L354 _protected prototype_ `int32 GetGroupingDepth(const TSharedPtr<FTreeNodeGrouping>& Grouping) const;`
- L356 _protected prototype_ `void GroupingCrumbMenu_Reset_Execute();`
- L357 _protected prototype_ `void GroupingCrumbMenu_Remove_Execute(const TSharedPtr<FTreeNodeGrouping> Grouping);`
- L358 _protected prototype_ `void GroupingCrumbMenu_MoveLeft_Execute(const TSharedPtr<FTreeNodeGrouping> Grouping);`
- L359 _protected prototype_ `void GroupingCrumbMenu_MoveRight_Execute(const TSharedPtr<FTreeNodeGrouping> Grouping);`
- L360 _protected prototype_ `void GroupingCrumbMenu_Change_Execute(const TSharedPtr<FTreeNodeGrouping> OldGrouping, const TSharedPtr<FTreeNodeGrouping> NewGrouping);`
- L361 _protected prototype_ `bool GroupingCrumbMenu_Change_CanExecute(const TSharedPtr<FTreeNodeGrouping> OldGrouping, const TSharedPtr<FTreeNodeGrouping> NewGrouping) const;`
- L362 _protected prototype_ `void GroupingCrumbMenu_Add_Execute(const TSharedPtr<FTreeNodeGrouping> Grouping, const TSharedPtr<FTreeNodeGrouping> AfterGrouping);`
- L363 _protected prototype_ `bool GroupingCrumbMenu_Add_CanExecute(const TSharedPtr<FTreeNodeGrouping> Grouping, const TSharedPtr<FTreeNodeGrouping> AfterGrouping) const;`
- L368 _protected prototype_ `static void UpdateCStringSameValueAggregationSingleNode(const FTableColumn& InColumn, FTableTreeNode& GroupNode);`
- L369 _protected prototype_ `static void UpdateCStringSameValueAggregationRec(const FTableColumn& InColumn, FTableTreeNode& GroupNode);`
- L372 _protected prototype_ `template<typename T, bool bSetInitialValue, bool bIsRercursive> static void UpdateAggregation(const FTableColumn& InColumn, FTableTreeNode& InOutGroupNode, const T InitialAggregatedValue, TFunctionRef<T(T, const FTableCellValue&)> ValueGetterFunc);`
- L375 _protected prototype_ `template<bool bIsRercursive> static void UpdateAggregatedValues(TSharedPtr<FTable> InTable, FTableTreeNode& InOutGroupNode);`
- L377 _protected prototype_ `void UpdateAggregatedValuesSingleNode(FTableTreeNode& GroupNode);`
- L378 _protected prototype_ `void UpdateAggregatedValuesRec(FTableTreeNode& GroupNode);`
- L383 _protected prototype_ `static const EColumnSortMode::Type GetDefaultColumnSortMode();`
- L384 _protected prototype_ `static const FName GetDefaultColumnBeingSorted();`
- L386 _protected prototype_ `void CreateSortings();`
- L387 _protected prototype_ `void UpdateCurrentSortingByColumn();`
- L389 _protected prototype_ `void OnSortingChanged();`
- L390 _protected prototype_ `bool ScheduleSortingAsyncOperationIfNeeded();`
- L391 _protected prototype_ `void ScheduleSortingAsyncOperation();`
- L392 _protected prototype_ `FGraphEventRef StartSortingTask(FGraphEventRef Prerequisite = nullptr);`
- L393 _protected prototype_ `void ApplySorting();`
- L394 _protected prototype_ `void SortTreeNodes(ITableCellValueSorter* InSorter, EColumnSortMode::Type InColumnSortMode);`
- L395 _protected prototype_ `void SortTreeNodesRec(FTableTreeNode& GroupNode, const ITableCellValueSorter& Sorter, EColumnSortMode::Type InColumnSortMode);`
- L397 _protected prototype_ `EColumnSortMode::Type GetSortModeForColumn(const FName ColumnId) const;`
- L398 _protected prototype_ `void SetSortModeForColumn(const FName& ColumnId, EColumnSortMode::Type SortMode);`
- L399 _protected prototype_ `void OnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type SortMode);`
- L405 _protected prototype_ `bool HeaderMenu_SortMode_IsChecked(const FName ColumnId, const EColumnSortMode::Type InSortMode);` — SortMode (HeaderMenu)
- L406 _protected prototype_ `bool HeaderMenu_SortMode_CanExecute(const FName ColumnId, const EColumnSortMode::Type InSortMode) const;`
- L407 _protected prototype_ `void HeaderMenu_SortMode_Execute(const FName ColumnId, const EColumnSortMode::Type InSortMode);`
- L410 _protected prototype_ `bool ContextMenu_SortMode_IsChecked(const EColumnSortMode::Type InSortMode);` — SortMode (ContextMenu)
- L411 _protected prototype_ `bool ContextMenu_SortMode_CanExecute(const EColumnSortMode::Type InSortMode) const;`
- L412 _protected prototype_ `void ContextMenu_SortMode_Execute(const EColumnSortMode::Type InSortMode);`
- L415 _protected prototype_ `bool ContextMenu_SortByColumn_IsChecked(const FName ColumnId);` — SortByColumn (ContextMenu)
- L416 _protected prototype_ `bool ContextMenu_SortByColumn_CanExecute(const FName ColumnId) const;`
- L417 _protected prototype_ `void ContextMenu_SortByColumn_Execute(const FName ColumnId);`
- L423 _protected prototype_ `bool CanShowColumn(const FName ColumnId) const;` — ShowColumn
- L424 _protected prototype_ `void ShowColumn(const FName ColumnId);`
- L425 _protected prototype_ `void ShowColumn(FTableColumn& Column);`
- L428 _protected prototype_ `bool CanHideColumn(const FName ColumnId) const;` — HideColumn
- L429 _protected prototype_ `void HideColumn(const FName ColumnId);`
- L430 _protected prototype_ `void HideColumn(FTableColumn& Column);`
- L433 _protected prototype_ `bool IsColumnVisible(const FName ColumnId);` — ToggleColumnVisibility
- L434 _protected prototype_ `bool CanToggleColumnVisibility(const FName ColumnId) const;`
- L435 _protected prototype_ `void ToggleColumnVisibility(const FName ColumnId);`
- L438 _protected prototype_ `bool ContextMenu_ShowAllColumns_CanExecute() const;` — ShowAllColumns (ContextMenu)
- L439 _protected prototype_ `void ContextMenu_ShowAllColumns_Execute();`
- L442 _protected prototype_ `bool ContextMenu_ResetColumns_CanExecute() const;` — ResetColumns (ContextMenu)
- L443 _protected prototype_ `void ContextMenu_ResetColumns_Execute();`
- L446 _protected prototype_ `bool ContextMenu_HideAllColumns_CanExecute() const;` — HideAllColumns (ContextMenu)
- L447 _protected prototype_ `void ContextMenu_HideAllColumns_Execute();`
- L452 _protected prototype_ `virtual void OnPreAsyncUpdate();`
- L453 _protected prototype_ `virtual void OnPostAsyncUpdate();`
- L455 _protected function_ `void AddPendingAsyncOperation(EAsyncOperationType InType)`
- L456 _protected function_ `bool HasPendingAsyncOperation(EAsyncOperationType InType) const`
- L457 _protected function_ `void ClearPendingAsyncOperation(EAsyncOperationType InType)`
- L458 _protected function_ `void ClearPendingAsyncOperations()`
- L460 _protected function_ `void AddInProgressAsyncOperation(EAsyncOperationType InType)`
- L461 _protected function_ `bool HasInProgressAsyncOperation(EAsyncOperationType InType) const`
- L462 _protected function_ `void ClearInProgressAsyncOperations()`
- L464 _protected prototype_ `void StartPendingAsyncOperations();`
- L466 _protected prototype_ `void CancelCurrentAsyncOp();`
- L470 _protected prototype_ `void CountNumNodesPerDepthRec(FBaseTreeNode* InRoot, TArray<int32>& InOutNumNodesPerDepth, int32 InDepth, int32 InMaxDepth, int32 InMaxNodes) const;`
- L471 _protected prototype_ `void ApplyNodeExpansion(const FTableTreeNodePtr& InNode);`
- L472 _protected prototype_ `void SetExpandValueForChildGroups(FBaseTreeNode* InRoot, int32 InMaxExpandedNodes, int32 MaxDepthToExpand, bool InValue);`
- L473 _protected prototype_ `void SetExpandValueForChildGroupsRec(FBaseTreeNode* InRoot, int32 InDepth, int32 InMaxDepth, bool InValue);`
- L475 _protected function_ `virtual void ExtendMenu(TSharedRef<FExtender> Extender)`
- L476 _protected function_ `virtual void ExtendMenu(FMenuBuilder& Menu)`
- L478 _protected typedef_ `typedef TFunctionRef<void(TArray<FBaseTreeNodePtr>& InNodes)> WriteToFileCallback;`
- L479 _protected prototype_ `void ExportToFileRec(const FBaseTreeNodePtr& InGroupNode, TArray<FBaseTreeNodePtr>& InNodes, bool bInExportCollapsed, bool InExportLeafs, WriteToFileCallback Callback);`
- L481 _protected function_ `FText GetTreeViewBannerText() const`
- L482 _protected prototype_ `virtual void UpdateBannerText();`
- L487 _protected function_ `virtual void InitAvailableViewPresets()`
- L488 _protected function_ `const TArray<TSharedRef<ITableTreeViewPreset>>* GetAvailableViewPresets() const`
- L489 _protected prototype_ `TSharedPtr<ITableTreeViewPreset> GetSelectedViewPreset() const;`
- L490 _protected prototype_ `void SelectViewPreset(TSharedPtr<ITableTreeViewPreset> InPreset);`
- L491 _protected prototype_ `void ApplyViewPreset(const ITableTreeViewPreset& InPreset);`
- L492 _protected prototype_ `void ApplyColumnConfig(const TArrayView<FTableColumnConfig>& InTableConfig);`
- L493 _protected prototype_ `void ViewPreset_OnSelectionChanged(TSharedPtr<ITableTreeViewPreset> InPreset, ESelectInfo::Type SelectInfo);`
- L494 _protected prototype_ `TSharedRef<SWidget> ViewPreset_OnGenerateWidget(TSharedRef<ITableTreeViewPreset> InPreset);`
- L495 _protected prototype_ `FText ViewPreset_GetSelectedText() const;`
- L496 _protected prototype_ `FText ViewPreset_GetSelectedToolTipText() const;`
- L497 _protected prototype_ `void ConstructViewPreset(TSharedPtr<SHorizontalBox> InHorizontalBox, float InMinDesiredWidth = 50.0f);`
- L501 _protected function_ `virtual void SearchForItem(TSharedPtr<FTableTaskCancellationToken> CancellationToken)`
- L506 _protected function_ `template<typename T, typename... TArgs> TSharedPtr<FTableTaskInfo> StartTableDataTask(TArgs&&... Args)` — Table data tasks should be tasks that operate read only operations on the data from the Table They should not operate on the tree nodes because they will run concurrently with the populated table UI.
- L515 _protected prototype_ `void StopAllTableDataTasks(bool bWait = true);`
- L519 _protected member_ `TSharedPtr<FTable> Table;` — Table view model.
- L521 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L527 _protected member_ `TSharedPtr<STreeView<FTableTreeNodePtr>> TreeView;` — The child STreeView widget.
- L530 _protected member_ `TSharedPtr<SHeaderRow> TreeViewHeaderRow;` — Holds the tree view header row widget which display all columns in the tree view.
- L533 _protected member_ `TSharedPtr<SScrollBar> ExternalScrollbar;` — External scrollbar used to synchronize tree view position.
- L539 _protected member_ `FName HoveredColumnId;` — Name of the column currently being hovered by the mouse.
- L542 _protected member_ `FTableTreeNodePtr HoveredNodePtr;` — A shared pointer to the tree node currently being hovered by the mouse.
- L548 _protected member_ `FTableTreeNodePtr Root;` — The root node of the tree. It is invisible; only its children are displayed in the tree view.
- L551 _protected member_ `TArray<FTableTreeNodePtr> TableRowNodes;` — Table row nodes. Each node corresponds to a table row. Index in this array corresponds to RowIndex in source table.
- L554 _protected member_ `TArray<FTableTreeNodePtr> FilteredNodes;` — Filtered table nodes. These are the nodes from the TableRowNodes array, after applying the node filtering.
- L557 _protected member_ `TArray<FTableTreeNodePtr>* FilteredNodesPtr = nullptr;` — A pointer to the filtered table nodes. If node filtering is empty, this points directly to TableRowNodes.
- L560 _protected member_ `TArray<FTableTreeNodePtr> FilteredGroupNodes;` — A filtered array of group nodes to be displayed in the tree widget.
- L562 _protected member_ `int32 MaxNodesToAutoExpand = 1000;`
- L563 _protected member_ `int32 MaxDepthToAutoExpand = 4;`
- L564 _protected member_ `int32 MaxNodesToExpand = 1000000;`
- L565 _protected member_ `int32 MaxDepthToExpand = 100;`
- L571 _protected member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box widget used to filter items displayed in the stats and groups tree.
- L574 _protected member_ `TSharedPtr<FTableTreeNodeFilterCollection> Filters;` — The filter collection.
- L577 _protected member_ `TSharedPtr<FTableTreeNodeTextFilter> TextFilter;` — The text based filter.
- L580 _protected member_ `TSharedPtr<FTableTreeNodeTextFilter> CurrentAsyncOpTextFilter;` — The text based filter actually used in the Hierarchy Filtering async task.
- L585 _protected member_ `TSharedPtr<FFilterConfigurator> FilterConfigurator;`
- L586 _protected member_ `FDelegateHandle OnFilterChangesCommittedHandle;`
- L589 _protected member_ `FFilterConfigurator* CurrentAsyncOpFilterConfigurator = nullptr;` — The filter configurator actually used in the Hierarchy Filtering async task.
- L591 _protected member_ `mutable FFilterContext FilterContext;`
- L596 _protected member_ `TArray<TSharedPtr<FTreeNodeGrouping>> AvailableGroupings;`
- L599 _protected member_ `TArray<TSharedPtr<FTreeNodeGrouping>> CurrentGroupings;` — How we group the tree nodes?
- L601 _protected member_ `TSharedPtr<SBreadcrumbTrail<TSharedPtr<FTreeNodeGrouping>>> GroupingBreadcrumbTrail;`
- L604 _protected member_ `TArray<TSharedPtr<FTreeNodeGrouping>> CurrentAsyncOpGroupings;` — The groupings actually used in the Grouping async task.
- L607 _protected member_ `TSet<FName> GroupingHiddenColumns;` — The columns hidden when grouping is applied.
- L613 _protected member_ `TArray<TSharedPtr<ITableCellValueSorter>> AvailableSorters;` — All available sorters.
- L616 _protected member_ `TSharedPtr<ITableCellValueSorter> CurrentSorter;` — Current sorter. It is nullptr if sorting is disabled.
- L619 _protected member_ `FName ColumnBeingSorted;` — Name of the column currently being sorted. Can be NAME_None if sorting is disabled (CurrentSorting == nullptr) or if a complex sorting is used (CurrentSorting != nullptr).
- L622 _protected member_ `EColumnSortMode::Type ColumnSortMode = EColumnSortMode::None;` — How we sort the nodes? Ascending or Descending.
- L625 _protected member_ `ITableCellValueSorter* CurrentAsyncOpSorter = nullptr;` — The sorter actually used in the Sorting async task.
- L628 _protected member_ `EColumnSortMode::Type CurrentAsyncOpColumnSortMode;` — The sort mode actually used in the Sorting async task.
- L633 _protected member_ `bool bRunInAsyncMode = false;`
- L634 _protected member_ `bool bIsUpdateRunning = false;`
- L635 _protected member_ `bool bIsCloseScheduled = false;`
- L637 _protected member_ `TArray<FTableTreeNodePtr> DummyGroupNodes;`
- L638 _protected member_ `FGraphEventRef InProgressAsyncOperationEvent;`
- L639 _protected member_ `FGraphEventRef AsyncCompleteTaskEvent;`
- L640 _protected member_ `EAsyncOperationType PendingAsyncOperations = static_cast<EAsyncOperationType>(0);`
- L641 _protected member_ `EAsyncOperationType InProgressAsyncOperations = static_cast<EAsyncOperationType>(0);`
- L642 _protected member_ `TSharedPtr<class SAsyncOperationStatus> AsyncOperationStatus;`
- L643 _protected member_ `FStopwatch AsyncUpdateStopwatch;`
- L644 _protected member_ `FAsyncOperationProgress AsyncOperationProgress;`
- L645 _protected member_ `FGraphEventRef DispatchEvent;`
- L646 _protected member_ `TArray<TSharedPtr<FTableTaskInfo>> DataTaskInfos;`
- L650 _protected member_ `FText TreeViewBannerText;`
- L652 _protected member_ `TArray<TSharedRef<ITableTreeViewPreset>> AvailableViewPresets;`
- L653 _protected member_ `TSharedPtr<ITableTreeViewPreset> SelectedViewPreset;`
- L654 _protected member_ `TSharedPtr<SComboBox<TSharedRef<ITableTreeViewPreset>>> PresetComboBox;`
- L660 _protected member_ `FName LogListingName;` — A log listing name to be used for any errors or warnings.

#### enum `UE::Insights::STableTreeView::EGroupingMenuType`  
`enum class EGroupingMenuType`  
_L120-124_
- L122 _public enumerator_ `Change`
- L123 _public enumerator_ `Add`

#### class `UE::Insights::FTableTreeViewNodeFilteringAsyncTask`  
`class FTableTreeViewNodeFilteringAsyncTask`  
_L665-687_
- L668 _public function_ `FTableTreeViewNodeFilteringAsyncTask(STableTreeView* InPtr) : TableTreeViewPtr(InPtr)`
- L673 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L674 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L675 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L677 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L686 _private member_ `STableTreeView* TableTreeViewPtr = nullptr;`

#### class `UE::Insights::FTableTreeViewHierarchyFilteringAsyncTask`  
`class FTableTreeViewHierarchyFilteringAsyncTask`  
_L691-713_
- L694 _public function_ `FTableTreeViewHierarchyFilteringAsyncTask(STableTreeView* InPtr) : TableTreeViewPtr(InPtr)`
- L699 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L700 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L701 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L703 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L712 _private member_ `STableTreeView* TableTreeViewPtr = nullptr;`

#### class `UE::Insights::FTableTreeViewSortingAsyncTask`  
`class FTableTreeViewSortingAsyncTask`  
_L717-743_
- L720 _public function_ `FTableTreeViewSortingAsyncTask(STableTreeView* InPtr, ITableCellValueSorter* InSorter, EColumnSortMode::Type InColumnSortMode) : TableTreeViewPtr(InPtr) , Sorter(InSorter) , ColumnSortMode(InColumnSortMode)`
- L727 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L728 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L729 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L731 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L740 _private member_ `STableTreeView* TableTreeViewPtr = nullptr;`
- L741 _private member_ `ITableCellValueSorter* Sorter = nullptr;`
- L742 _private member_ `EColumnSortMode::Type ColumnSortMode = EColumnSortMode::Type::None;`

#### class `UE::Insights::FTableTreeViewGroupingAsyncTask`  
`class FTableTreeViewGroupingAsyncTask`  
_L747-771_
- L750 _public function_ `FTableTreeViewGroupingAsyncTask(STableTreeView* InPtr, TArray<TSharedPtr<FTreeNodeGrouping>>* InGroupings) : TableTreeViewPtr(InPtr) , Groupings(InGroupings)`
- L756 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L757 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L758 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L760 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L769 _private member_ `STableTreeView* TableTreeViewPtr = nullptr;`
- L770 _private member_ `TArray<TSharedPtr<FTreeNodeGrouping>>* Groupings = nullptr;`

#### class `UE::Insights::FSearchForItemToSelectTask`  
`class FSearchForItemToSelectTask`  
_L775-802_
- L778 _public function_ `FSearchForItemToSelectTask(TSharedPtr<FTableTaskCancellationToken> InToken, TSharedPtr<STableTreeView> InPtr) : CancellationToken(InToken) , TableTreeViewPtr(InPtr)`
- L784 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L785 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L786 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L788 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L800 _private member_ `TSharedPtr<FTableTaskCancellationToken> CancellationToken;`
- L801 _private member_ `TSharedPtr<STableTreeView> TableTreeViewPtr;`

#### class `UE::Insights::FSelectNodeByTableRowIndexTask`  
`class FSelectNodeByTableRowIndexTask`  
_L806-835_
- L809 _public function_ `FSelectNodeByTableRowIndexTask(TSharedPtr<FTableTaskCancellationToken> InToken, TSharedPtr<STableTreeView> InPtr, uint32 InRowIndex) : CancellationToken(InToken) , TableTreeViewPtr(InPtr) , RowIndex(InRowIndex)`
- L816 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L817 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L818 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L820 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L832 _private member_ `TSharedPtr< FTableTaskCancellationToken> CancellationToken;`
- L833 _private member_ `TSharedPtr<STableTreeView> TableTreeViewPtr;`
- L834 _private member_ `uint32 RowIndex = 0;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Insights` (scope `UE`)
- L46 _typedef_ `typedef TFilterCollection<const FTableTreeNodePtr&> FTableTreeNodeFilterCollection;` (scope `UE::Insights`) — The filter collection - used for updating the list of tree nodes.
- L49 _typedef_ `typedef TTextFilter<const FTableTreeNodePtr&> FTableTreeNodeTextFilter;` (scope `UE::Insights`) — The text based filter - used for updating the list of tree nodes.
- L62 _prototype_ `ENUM_CLASS_FLAGS(EAsyncOperationType);` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/STableTreeViewCell.h` (Public)


#### class `UE::Insights::STableTreeViewCell`  
`class STableTreeViewCell : public SCompoundWidget`  
_L26-150_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(STableTreeViewCell)`
- L30 _public prototype_ `SLATE_EVENT(FSetHoveredTableTreeViewCell, OnSetHoveredCell) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(TSharedPtr<FTable>, TablePtr) SLATE_ARGUMENT(TSharedPtr<FTableColumn>, ColumnPtr) SLATE_ARGUMENT(FTableTreeNodePtr, TableTreeNodePtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<ITableRow>& InTableRow);`
- L40 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FArguments& InArgs);`
- L41 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForNameColumn(const FArguments& InArgs);`
- L42 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForTableColumn(const FArguments& InArgs);`
- L50 _protected function_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override` — The system will use this event to notify a widget that the cursor has entered it. This event is NOT bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event
- L61 _protected function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override` — The system will use this event to notify a widget that the cursor has left it. This event is NOT bubbled. @param MouseEvent Information about the input event
- L84 _protected function_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override` — Called during drag and drop when the drag enters a widget. Enter/Leave events in slate are meant as lightweight notifications. So we do not want to capture mouse or set focus in response to these. However, OnDragEnter must also support external APIs (e.g. OLE Drag/Drop) Those require that we let them know whether we can handle the content being dragged OnDragEnter. The concession is to return a can_handled/cannot_handle boolean rather than a full FReply. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether the contents of the DragDropEvent can potentially be processed by this widget.
- L95 _protected function_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override` — Called during drag and drop when the drag leaves a widget. @param DragDropEvent   The drag and drop event.
- L101 _protected function_ `EVisibility GetHintIconVisibility() const`
- L106 _protected prototype_ `bool IsSelected() const;`
- L108 _protected function_ `const FSlateBrush* GetIcon() const`
- L113 _protected function_ `FText GetDisplayName() const`
- L118 _protected function_ `FText GetExtraDisplayName() const`
- L123 _protected function_ `EVisibility HasExtraDisplayName() const`
- L128 _protected prototype_ `FText GetValueAsText() const;`
- L130 _protected prototype_ `FSlateColor GetIconColorAndOpacity() const;`
- L131 _protected prototype_ `FSlateColor GetDisplayNameColorAndOpacity() const;`
- L132 _protected prototype_ `FSlateColor GetExtraDisplayNameColorAndOpacity() const;`
- L133 _protected prototype_ `FSlateColor GetNormalTextColorAndOpacity() const;`
- L134 _protected prototype_ `FLinearColor GetShadowColorAndOpacity() const;`
- L138 _protected member_ `TWeakPtr<ITableRow> WeakTableRow;` — A weak pointer to the parent table row widget.
- L141 _protected member_ `TSharedPtr<FTable> TablePtr;` — A shared pointer to the table view model.
- L144 _protected member_ `TSharedPtr<FTableColumn> ColumnPtr;` — A shared pointer to the table column view model.
- L147 _protected member_ `FTableTreeNodePtr TableTreeNodePtr;` — A shared pointer to the tree node.
- L149 _protected member_ `FSetHoveredTableTreeViewCell SetHoveredCellDelegate;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_ThreeParams(FSetHoveredTableTreeViewCell, TSharedPtr<FTable> , TSharedPtr<FTableColumn> , FTableTreeNodePtr );`
- L24 _prototype_ `DECLARE_DELEGATE_ThreeParams(FSetHoveredTableTreeViewCell, TSharedPtr<FTable> , TSharedPtr<FTableColumn> , FTableTreeNodePtr );` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/STableTreeViewRow.h` (Public)


#### class `UE::Insights::STableTreeViewRow`  
`class STableTreeViewRow : public SMultiColumnTableRow<FTableTreeNodePtr>`  
_L32-95_
- inherits: `SMultiColumnTableRow<FTableTreeNodePtr>`
- desc: Widget that represents a table row in the tree control. Generates widgets for each column on demand.
- L35 _public function_ `SLATE_BEGIN_ARGS(STableTreeViewRow)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L48 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;`
- L64 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when Slate detects that a widget started to be dragged. Usage: A widget can ask Slate to detect a drag. OnMouseDown() reply with FReply::Handled().DetectDrag(SharedThis(this)). Slate will either send an OnDragDetected() event or do nothing. If the user releases a mouse button or leaves the widget before a drag is triggered (maybe user started at the very edge) then no event will be sent. @param  InMyGeometry  Widget geometry @param  InMouseEvent  MouseMove that triggered the drag
- L66 _public prototype_ `TSharedRef<IToolTip> GetRowToolTip() const;`
- L67 _public prototype_ `void InvalidateContent();`
- L70 _protected prototype_ `TSharedRef<SWidget> CreateCellWidget(FName ColumnId);`
- L71 _protected prototype_ `FSlateColor GetBackgroundColorAndOpacity() const;`
- L72 _protected prototype_ `FSlateColor GetBackgroundColorAndOpacity(double Time) const;`
- L73 _protected prototype_ `FSlateColor GetOutlineColorAndOpacity() const;`
- L74 _protected prototype_ `const FSlateBrush* GetOutlineBrush(const FName ColumnId) const;`
- L75 _protected prototype_ `bool HandleShouldBeEnabled() const;`
- L76 _protected prototype_ `EVisibility IsColumnVisible(const FName ColumnId) const;`
- L77 _protected prototype_ `void OnSetHoveredCell(TSharedPtr<FTable> InTablePtr, TSharedPtr<FTableColumn> InColumnPtr, FTableTreeNodePtr InTreeNodePtr);`
- L81 _protected member_ `TSharedPtr<FTable> TablePtr;` — A shared pointer to the table view model.
- L84 _protected member_ `FTableTreeNodePtr TableTreeNodePtr;` — Data context for this table row.
- L86 _protected member_ `FTableTreeNodeShouldBeEnabledDelegate OnShouldBeEnabled;`
- L87 _protected member_ `FIsColumnVisibleDelegate IsColumnVisibleDelegate;`
- L88 _protected member_ `FSetHoveredTableTreeViewCell SetHoveredCellDelegate;`
- L89 _protected member_ `FGetColumnOutlineHAlignmentDelegate GetColumnOutlineHAlignmentDelegate;`
- L92 _protected member_ `TAttribute<FText> HighlightText;` — Text to be highlighted on tree node's name.
- L94 _protected member_ `TSharedPtr<STableTreeRowToolTip> RowToolTip;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Insights` (scope `UE`)
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FTableTreeNodeShouldBeEnabledDelegate, FTableTreeNodePtr );`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FTableTreeNodeShouldBeEnabledDelegate, FTableTreeNodePtr );` (scope `UE::Insights`)
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsColumnVisibleDelegate, const FName );`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsColumnVisibleDelegate, const FName );` (scope `UE::Insights`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EHorizontalAlignment, FGetColumnOutlineHAlignmentDelegate, const FName );`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EHorizontalAlignment, FGetColumnOutlineHAlignmentDelegate, const FName );` (scope `UE::Insights`)
- L29 _delegate_ `DECLARE_DELEGATE_ThreeParams(FSetHoveredTableTreeViewCell, TSharedPtr<FTable> , TSharedPtr<FTableColumn> , FTableTreeNodePtr );`
- L29 _prototype_ `DECLARE_DELEGATE_ThreeParams(FSetHoveredTableTreeViewCell, TSharedPtr<FTable> , TSharedPtr<FTableColumn> , FTableTreeNodePtr );` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/STableTreeViewTooltip.h` (Public)


#### class `UE::Insights::STableTreeViewTooltip`  
`class STableTreeViewTooltip`  
_L23-34_
- desc: Tooltip for STableTreeView widget.
- L26 _public prototype_ `STableTreeViewTooltip() = delete;`
- L28 _public prototype_ `static TSharedPtr<SToolTip> GetTableTooltip(const FTable& Table);`
- L29 _public prototype_ `static TSharedPtr<SToolTip> GetColumnTooltip(const FTableColumn& Column);`
- L30 _public prototype_ `static TSharedPtr<SToolTip> GetRowTooltip(const TSharedPtr<FTableTreeNode> TreeNodePtr);`
- L33 _private prototype_ `static void AddGridRow(TSharedPtr<SGridPanel> Grid, int32& Row, const FText& Name, const FText& Value);`

#### class `UE::Insights::STableTreeRowToolTip`  
`class STableTreeRowToolTip : public IToolTip`  
_L38-85_
- inherits: `IToolTip`
- L41 _public function_ `STableTreeRowToolTip(const TSharedPtr<FTableTreeNode> InTreeNodePtr) : TreeNodePtr(InTreeNodePtr)`
- L42 _public prototype_ `virtual ~STableTreeRowToolTip() = default;`
- L44 _public function_ `virtual TSharedRef<SWidget> AsWidget()`
- L50 _public function_ `virtual TSharedRef<SWidget> GetContentWidget()`
- L56 _public function_ `virtual void SetContentWidget(const TSharedRef<SWidget>& InContentWidget)`
- L62 _public function_ `void InvalidateWidget()`
- L67 _public function_ `virtual bool IsEmpty() const`
- L68 _public function_ `virtual bool IsInteractive() const`
- L69 _public function_ `virtual void OnOpening()`
- L70 _public function_ `virtual void OnClosed()`
- L73 _private function_ `void CreateToolTipWidget()`
- L83 _private member_ `TSharedPtr<SToolTip> ToolTipWidget;`
- L84 _private member_ `const TSharedPtr<FTableTreeNode> TreeNodePtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/SUntypedDiffTableTreeView.h` (Public)


#### class `UE::Insights::SUntypedDiffTableTreeView`  
`class SUntypedDiffTableTreeView : public SUntypedTableTreeView`  
_L22-41_
- inherits: `SUntypedTableTreeView`
- L25 _public prototype_ `void UpdateSourceTableA(const FString& Name, TSharedPtr<TraceServices::IUntypedTable> SourceTable);`
- L26 _public prototype_ `void UpdateSourceTableB(const FString& Name, TSharedPtr<TraceServices::IUntypedTable> SourceTable);`
- L29 _protected prototype_ `FReply SwapTables_OnClicked();`
- L30 _protected prototype_ `FText GetSwapButtonText() const;`
- L32 _protected prototype_ `virtual TSharedPtr<SWidget> ConstructToolbar() override;`
- L34 _protected prototype_ `void RequestMergeTables();`
- L37 _private member_ `TSharedPtr<TraceServices::IUntypedTable> SourceTableA;`
- L38 _private member_ `TSharedPtr<TraceServices::IUntypedTable> SourceTableB;`
- L39 _private member_ `FString TableNameA;`
- L40 _private member_ `FString TableNameB;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Table/Widgets/SUntypedTableTreeView.h` (Public)


#### class `UE::Insights::SUntypedTableTreeView`  
`class SUntypedTableTreeView : public STableTreeView`  
_L28-75_
- inherits: `STableTreeView`
- L31 _public prototype_ `SUntypedTableTreeView();`
- L32 _public prototype_ `virtual ~SUntypedTableTreeView();`
- L34 _public function_ `SLATE_BEGIN_ARGS(SUntypedTableTreeView) : _RunInAsyncMode(false)`
- L37 _public prototype_ `SLATE_ARGUMENT(bool, RunInAsyncMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FUntypedTable> InTablePtr);`
- L46 _public function_ `TSharedPtr<FUntypedTable> GetUntypedTable() const`
- L48 _public prototype_ `void UpdateSourceTable(TSharedPtr<TraceServices::IUntypedTable> SourceTable);`
- L50 _public prototype_ `virtual void Reset();`
- L55 _public prototype_ `virtual bool IsRunning() const override;`
- L56 _public prototype_ `virtual double GetAllOperationsDuration() override;`
- L57 _public function_ `virtual double GetCurrentOperationDuration() override`
- L58 _public function_ `virtual uint32 GetOperationCount() const override`
- L59 _public prototype_ `virtual FText GetCurrentOperationName() const override;`
- L63 _public prototype_ `void SetCurrentOperationNameOverride(const FText& InOperationName);`
- L64 _public prototype_ `void ClearCurrentOperationNameOverride();`
- L70 _public prototype_ `virtual void RebuildTree(bool bResync);` — Rebuilds the tree (if necessary). @param bResync - If true, it forces a resync even if the list did not changed since last sync.
- L73 _private member_ `FStopwatch CurrentOperationStopwatch;`
- L74 _private member_ `FText CurrentOperationNameOverride;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace TraceServices`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Version.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UNREAL_INSIGHTS_VERSION_MAJOR 1`
- L8 _macro_ `#define UNREAL_INSIGHTS_VERSION_MINOR 9`
- L9 _macro_ `#define UNREAL_INSIGHTS_VERSION_PATCH 0`
- L11 _macro_ `#define UNREAL_INSIGHTS_VERSION_STRING "1.09"`
- L22 _macro_ `#define UNREAL_INSIGHTS_VERSION_STRING_EX "v" UNREAL_INSIGHTS_VERSION_STRING "-" UNREAL_INSIGHTS_VERSION_ID_STRING`
- L24 _macro_ `#define UNREAL_INSIGHTS_VERSION_STRING_EX "v" UNREAL_INSIGHTS_VERSION_STRING`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/ViewModels/IBarGraphSegment.h` (Public)


#### class `UE::Insights::IBarGraphSegment`  
`class IBarGraphSegment`  
_L14-43_
- L17 _public prototype_ `virtual ~IBarGraphSegment() = default;`
- L22 _public prototype_ `virtual double GetSize() const = 0;` — Returns the relative segment size, in interval [0 .. 1].
- L27 _public prototype_ `virtual FText GetText() const = 0;` — Returns the text displayed on the segment.
- L32 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Returns the tool tip text of the segment.
- L37 _public prototype_ `virtual FLinearColor GetColor() const = 0;` — Returns the color of the segment.
- L42 _public prototype_ `virtual FLinearColor GetTextColor() const = 0;` — Returns the color of the text displayed on the segment.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Widgets/SLazyToolTip.h` (Public)


#### class `ILazyToolTipCreator`  
`class ILazyToolTipCreator`  
_L11-15_
- L14 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTooltip() const = 0;`

#### class `SLazyToolTip`  
`class SLazyToolTip : public SCompoundWidget, public IToolTip`  
_L17-77_
- inherits: `SCompoundWidget,IToolTip`
- L19 _private function_ `SLATE_BEGIN_ARGS(SLazyToolTip)`
- L23 _public function_ `void Construct(const FArguments& InArgs, TSharedPtr<const ILazyToolTipCreator> InCreator)`
- L28 _public function_ `virtual TSharedRef<SWidget> AsWidget()`
- L34 _public function_ `virtual TSharedRef<SWidget> GetContentWidget()`
- L40 _public function_ `virtual void SetContentWidget(const TSharedRef<SWidget>& InContentWidget)`
- L46 _public function_ `void InvalidateWidget()`
- L51 _public function_ `virtual bool IsEmpty() const`
- L52 _public function_ `virtual bool IsInteractive() const`
- L53 _public function_ `virtual void OnOpening()`
- L54 _public function_ `virtual void OnClosed()`
- L57 _private function_ `void CreateToolTipWidget()`
- L75 _private member_ `TSharedPtr<SToolTip> ToolTipWidget;`
- L76 _private member_ `TWeakPtr<const ILazyToolTipCreator> WeakCreator;`

### `Source/Developer/TraceInsightsCore/Public/InsightsCore/Widgets/SSegmentedBarGraph.h` (Public)


#### class `UE::Insights::FObservableSegmentArrayPointer`  
`class FObservableSegmentArrayPointer : public UE::Slate::ItemsSource::IItemsSource<TSharedPtr<IBarGraphSegment>>`  
_L25-62_
- inherits: `UE::Slate::ItemsSource::IItemsSource<TSharedPtr<IBarGraphSegment>>`
- L28 _public typedef_ `using WidgetType = SSegmentedBarGraph;`
- L29 _public typedef_ `using SegmentType = TSharedPtr<IBarGraphSegment>;`
- L31 _public function_ `explicit FObservableSegmentArrayPointer(TSharedRef<WidgetType> InGraphWidget, UE::Slate::Containers::TObservableArray<SegmentType>* InSegmentsSource) : SegmentsSource(InSegmentsSource) , GraphWidgetOwner(InGraphWidget.ToWeakPtr())`
- L38 _public function_ `virtual ~FObservableSegmentArrayPointer()`
- L45 _public function_ `virtual const TArrayView<const SegmentType> GetItems() const override`
- L50 _public function_ `virtual bool IsSame(const void* RawPointer) const override`
- L56 _private prototype_ `void HandleArrayChanged(typename UE::Slate::Containers::TObservableArray<SegmentType>::ObservableArrayChangedArgsType Args);`
- L59 _private member_ `UE::Slate::Containers::TObservableArray<SegmentType>* SegmentsSource;`
- L60 _private member_ `TWeakPtr<WidgetType> GraphWidgetOwner;`
- L61 _private member_ `FDelegateHandle ArrayChangedHandle;`

#### class `UE::Insights::FSharedObservableSegmentArray`  
`class FSharedObservableSegmentArray : public UE::Slate::ItemsSource::IItemsSource<TSharedPtr<IBarGraphSegment>>`  
_L66-102_
- inherits: `UE::Slate::ItemsSource::IItemsSource<TSharedPtr<IBarGraphSegment>>`
- L69 _public typedef_ `using WidgetType = SSegmentedBarGraph;`
- L70 _public typedef_ `using SegmentType = TSharedPtr<IBarGraphSegment>;`
- L72 _public function_ `explicit FSharedObservableSegmentArray(TSharedRef<WidgetType> InGraphWidget, TSharedRef<UE::Slate::Containers::TObservableArray<SegmentType>> InSegmentsSource) : SegmentsSource(InSegmentsSource) , GraphWidgetOwner(InGraphWidget.ToWeakPtr())`
- L79 _public function_ `virtual ~FSharedObservableSegmentArray()`
- L84 _public function_ `virtual const TArrayView<const SegmentType> GetItems() const override`
- L89 _public function_ `virtual bool IsSame(const void* RawPointer) const override`
- L96 _private prototype_ `void HandleArrayChanged(typename UE::Slate::Containers::TObservableArray<SegmentType>::ObservableArrayChangedArgsType Args);`
- L99 _private member_ `TSharedRef<UE::Slate::Containers::TObservableArray<SegmentType>> SegmentsSource;`
- L100 _private member_ `TWeakPtr<WidgetType> GraphWidgetOwner;`
- L101 _private member_ `FDelegateHandle ArrayChangedHandle;`

#### class `UE::Insights::SSegmentedBarGraph`  
`class SSegmentedBarGraph : public SCompoundWidget`  
_L109-211_
- inherits: `SCompoundWidget`
- desc: A widget that displays a segmented bar graph.
- L112 _public typedef_ `using SegmentType = TSharedPtr<IBarGraphSegment>;`
- L113 _public typedef_ `using SegmentSourceType = UE::Slate::ItemsSource::IItemsSource<SegmentType>;`
- L116 _public prototype_ `SSegmentedBarGraph();` — Default constructor.
- L119 _public prototype_ `virtual ~SSegmentedBarGraph();` — Virtual destructor.
- L121 _public function_ `SLATE_BEGIN_ARGS(SSegmentedBarGraph)`
- L122 _public function_ `SLATE_ITEMS_SOURCE_ARGUMENT(SegmentType, SegmentsSource) TUniquePtr<SegmentSourceType> MakeSegmentsSource(TSharedRef<SSegmentedBarGraph> InWidget) const`
- L139 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L147 _public prototype_ `void RequestGraphRefresh();`
- L153 _public function_ `void SetSegmentsSource(const TArray<SegmentType>* InSegmentsSource)` — Set the SegmentsSource. The graph bar will generate widgets to represent these segments. @param InSegmentsSource A pointer to the array of segments that should be observed by this widget.
- L169 _public function_ `void SetSegmentsSource(TSharedRef<UE::Slate::Containers::TObservableArray<SegmentType>> InSegmentsSource)`
- L177 _public function_ `void SetSegmentsSource(TUniquePtr<SegmentSourceType> Provider)`
- L183 _public function_ `void ClearSegmentsSource()`
- L188 _public function_ `bool HasValidSegmentsSource() const`
- L193 _public function_ `TArrayView<const SegmentType> GetSegments() const`
- L199 _private prototype_ `void AddHorizontalSegment(TSharedRef<SHorizontalBox> Box, int32 SegmentIndex);`
- L200 _private prototype_ `float GetSegmentSize(int32 SegmentIndex) const;`
- L201 _private prototype_ `FText GetSegmentText(int32 SegmentIndex) const;`
- L202 _private prototype_ `FText GetSegmentToolTipText(int32 SegmentIndex) const;`
- L203 _private prototype_ `FSlateColor GetSegmentColor(int32 SegmentIndex) const;`
- L204 _private prototype_ `FSlateColor GetSegmentTextColor(int32 SegmentIndex) const;`
- L208 _private member_ `TUniquePtr<SegmentSourceType> SegmentsSource;` — Pointer to the source data that we are observing
- L210 _private member_ `TSharedPtr<SHorizontalBox> HorizontalBox;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TRACEINSIGHTSCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)
