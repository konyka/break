# Programs / LiveCodingConsole

- module root: `Source/Programs/LiveCodingConsole`
- headers: 4; symbols: 50
- symbol kinds: class=3, function=1, member=18, prototype=26, struct=2
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Json, LiveCodingServer, MessageLog, Projects, Slate, SlateCore, SourceCodeAccess, StandaloneRenderer, VisualStudioDTE, VisualStudioSourceCodeAccess, XCodeSourceCodeAccess
- PublicIncludePathModuleNames: Launch

### `Source/Programs/LiveCodingConsole/Private/LiveCodingConsole.h` (Private)
_(no declarations extracted)_

### `Source/Programs/LiveCodingConsole/Private/LiveCodingConsoleStyle.h` (Private)


#### class `FLiveCodingConsoleStyle`  
`class FLiveCodingConsoleStyle`  
_L8-31_
- L14 _public prototype_ `static void Initialize();` — Set up specific styles for the crash report client app
- L19 _public prototype_ `static void Shutdown();` — Tidy up on shut-down
- L24 _public prototype_ `static const ISlateStyle& Get();` — Access to singleton style object
- L27 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L30 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Singleton style object

### `Source/Programs/LiveCodingConsole/Private/LiveCodingManifest.h` (Private)


#### struct `FLiveCodingManifest`  
`struct FLiveCodingManifest`  
_L9-19_
- L11 _public member_ `FString LinkerPath;`
- L12 _public member_ `TMap<FString, FString> LinkerEnvironment;`
- L13 _public member_ `TMap<FString, TArray<FString>> BinaryToObjectFiles;`
- L14 _public member_ `TMap<FString, TArray<FString>> Libraries;`
- L15 _public member_ `TArray<TPair<FString, FString>> VfsEntries;`
- L17 _public prototype_ `bool Read(const TCHAR* FileName, FString& OutFailReason);`
- L18 _public prototype_ `bool Parse(FJsonObject& Object, FString& OutFailReason);`

### `Source/Programs/LiveCodingConsole/Private/SLogWidget.h` (Private)


#### class `FLogWidgetTextLayoutMarshaller`  
`class FLogWidgetTextLayoutMarshaller : public FBaseTextLayoutMarshaller`  
_L16-34_
- inherits: `FBaseTextLayoutMarshaller`
- L19 _public prototype_ `FLogWidgetTextLayoutMarshaller();`
- L20 _public prototype_ `virtual ~FLogWidgetTextLayoutMarshaller();`
- L23 _public prototype_ `virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;` — ITextLayoutMarshaller
- L24 _public prototype_ `virtual void GetText(FString& TargetString, const FTextLayout& SourceTextLayout) override;`
- L26 _public prototype_ `void Clear();`
- L27 _public prototype_ `void AppendLine(const FSlateColor& Color, const FString& Line);`
- L28 _public prototype_ `int32 GetNumLines() const;`
- L31 _private member_ `FTextBlockStyle DefaultStyle;`
- L32 _private member_ `TArray<TSharedRef<FString>> Lines;`
- L33 _private member_ `FTextLayout* TextLayout;`

#### class `SLogWidget`  
`class SLogWidget : public SCompoundWidget`  
_L36-84_
- inherits: `SCompoundWidget`
- L39 _public function_ `SLATE_BEGIN_ARGS(SLogWidget)`
- L42 _public prototype_ `SLogWidget();`
- L43 _public prototype_ `~SLogWidget();`
- L45 _public prototype_ `void Construct( const FArguments& InArgs );`
- L47 _public prototype_ `void Clear();`
- L48 _public prototype_ `void ScrollToEnd();`
- L49 _public prototype_ `void AppendLine(const FSlateColor& Color, const FString& Text);`
- L50 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L58 _protected member_ `FEditableTextBoxStyle Style;`
- L59 _protected member_ `FCriticalSection CriticalSection;`
- L60 _protected member_ `TArray<FLine> QueuedLines;`
- L61 _protected member_ `TSharedPtr<FLogWidgetTextLayoutMarshaller> MessagesTextMarshaller;`
- L62 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> MessagesTextBox;`
- L63 _protected member_ `bool bIsUserScrolledX;`
- L64 _protected member_ `bool bIsUserScrolledY;`
- L66 _protected prototype_ `void OnScrollX(float ScrollOffset);`
- L67 _protected prototype_ `void OnScrollY(float ScrollOffset);`
- L68 _protected prototype_ `EActiveTimerReturnType OnTimerElapsed(double CurrentTime, float DeltaTime);`
- L73 _protected prototype_ `void ExtendTextBoxMenu(FMenuBuilder& Builder);` — Extends the context menu used by the text box
- L78 _protected prototype_ `void OnClearLog();` — Called when delete all is selected
- L83 _protected prototype_ `bool CanClearLog() const;` — Called to determine whether delete all is currently a valid command

#### struct `SLogWidget::FLine`  
`struct FLine`  
_L52-56_
- L54 _public member_ `FSlateColor Color;`
- L55 _public member_ `FString Text;`
