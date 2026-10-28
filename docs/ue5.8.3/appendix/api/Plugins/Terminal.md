# Plugins / Terminal

- module root: `Plugins/Experimental/Terminal/Source/Terminal`
- headers: 12; symbols: 324
- symbol kinds: class=11, delegate=3, enum=3, enumerator=25, function=8, member=122, namespace=4, prototype=144, struct=4
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, EditorSubsystem, Engine, InputCore, Json, JsonUtilities, MainFrame, Projects, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure

### `Plugins/Experimental/Terminal/Source/Terminal/Public/ConPTYSession.h` (Public)


#### class `FConPTYSession`  
`class FConPTYSession : public ITerminalSession`  
_L20-69_
- inherits: `ITerminalSession`
- desc: Manages a ConPTY pseudo-console session on Windows. Creates a pseudo-console via the ConPTY API (dynamically loaded), spawns a shell process attached to it, and runs asynchronous I/O on a background thread with staged dispatch to the game thread.
- L24 _public prototype_ `FConPTYSession();`
- L27 _public prototype_ `FConPTYSession(const FConPTYSession&) = delete;`
- L28 _public prototype_ `FConPTYSession& operator=(const FConPTYSession&) = delete;`
- L31 _public prototype_ `static bool IsConPTYAvailable();` — Check if the ConPTY API is available on this system.
- L33 _public prototype_ `virtual bool Create(const FString& ShellPath, const FString& WorkingDirectory, int32 Columns, int32 Rows) override;`
- L34 _public prototype_ `virtual void Shutdown() override;`
- L35 _public prototype_ `virtual void WriteInput(TArrayView<const uint8> Data) override;`
- L36 _public prototype_ `virtual void Resize(int32 Columns, int32 Rows) override;`
- L37 _public prototype_ `virtual TArray<uint8> ConsumeOutput() override;`
- L38 _public prototype_ `virtual bool IsRunning() const override;`
- L54 _private member_ `void* PseudoConsoleHandle = nullptr;`
- L55 _private member_ `void* InputPipeWrite = nullptr;`
- L56 _private member_ `void* OutputPipeRead = nullptr;`
- L57 _private member_ `void* ProcessHandle = nullptr;`
- L58 _private member_ `void* ThreadHandle = nullptr;`
- L61 _private member_ `TSharedPtr<TAtomic<bool>> bAlive;` — Shared alive flag for safe async callback dispatch after destruction.
- L64 _private member_ `TArray<uint8> StagingBuffer;` — Output staging buffer  - filled by the reader thread, drained by ConsumeOutput() on the game thread.
- L65 _private member_ `FCriticalSection StagingLock;`
- L67 _private member_ `TUniquePtr<FReaderRunnable> ReaderRunnable;`
- L68 _private member_ `TUniquePtr<FRunnableThread> ReaderThread;`

#### class `FConPTYSession::FReaderRunnable`  
`class FReaderRunnable : public FRunnable`  
_L43-52_
- inherits: `FRunnable`
- desc: Background I/O reader thread.
- L46 _public function_ `FReaderRunnable(FConPTYSession* InOwner) : Owner(InOwner)`
- L47 _public prototype_ `virtual uint32 Run() override;`
- L48 _public prototype_ `virtual void Stop() override;`
- L50 _private member_ `FConPTYSession* Owner = nullptr;`
- L51 _private member_ `TAtomic<bool> bStopRequested{false};`

### `Plugins/Experimental/Terminal/Source/Terminal/Public/ITerminalSession.h` (Public)


#### class `ITerminalSession`  
`class ITerminalSession`  
_L18-62_
- desc: Abstract interface for a terminal PTY session. Platform-specific backends (FConPTYSession on Windows, FPosixPTYSession on Linux/macOS) implement this interface so that the terminal widget can drive any backend without platform conditionals in its core logic.
- L22 _public prototype_ `virtual ~ITerminalSession() = default;`
- L32 _public prototype_ `static TSharedPtr<ITerminalSession> CreateForCurrentPlatform(FString& OutError);` — Create a platform-appropriate session backend. Returns nullptr with an error message if no backend is available (e.g. ConPTY missing on older Windows, or unsupported platform). @param OutError Receives a user-visible error string when nullptr is returned.
- L43 _public prototype_ `virtual bool Create(const FString& ShellPath, const FString& WorkingDirectory, int32 Columns, int32 Rows) = 0;` — Create a new session. @param ShellPath Path to the shell executable. Empty uses the system default. @param WorkingDirectory Initial working directory for the shell. @param Columns Initial column count. @param Rows Initial row count. @return true if the session was created successfully.
- L46 _public prototype_ `virtual void Shutdown() = 0;` — Shut down the session, closing the PTY and terminating the shell process.
- L49 _public prototype_ `virtual void WriteInput(TArrayView<const uint8> Data) = 0;` — Write input bytes to the PTY input pipe.
- L52 _public prototype_ `virtual void Resize(int32 Columns, int32 Rows) = 0;` — Resize the PTY.
- L55 _public prototype_ `virtual TArray<uint8> ConsumeOutput() = 0;` — Swap the output staging buffer and return the accumulated bytes for parsing on the game thread.
- L58 _public prototype_ `virtual bool IsRunning() const = 0;` — Check if the shell process is still running.
- L61 _public member_ `FOnTerminalProcessExited OnProcessExited;` — Delegate fired when the shell process exits.

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTerminal, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTerminal, Log, All);`
- L9 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTerminalProcessExited, int32 );`
- L9 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTerminalProcessExited, int32 );`

### `Plugins/Experimental/Terminal/Source/Terminal/Public/PosixPTYSession.h` (Public)


#### class `FPosixPTYSession`  
`class FPosixPTYSession : public ITerminalSession`  
_L20-66_
- inherits: `ITerminalSession`
- desc: Manages a POSIX PTY session on Linux and macOS. Creates a pseudo-terminal via forkpty(), spawns a shell process, and runs asynchronous I/O on a background thread with staged dispatch to the game thread  - mirroring the FConPTYSession pattern on Windows.
- L24 _public prototype_ `FPosixPTYSession();`
- L27 _public prototype_ `FPosixPTYSession(const FPosixPTYSession&) = delete;`
- L28 _public prototype_ `FPosixPTYSession& operator=(const FPosixPTYSession&) = delete;`
- L30 _public prototype_ `virtual bool Create(const FString& ShellPath, const FString& WorkingDirectory, int32 Columns, int32 Rows) override;`
- L31 _public prototype_ `virtual void Shutdown() override;`
- L32 _public prototype_ `virtual void WriteInput(TArrayView<const uint8> Data) override;`
- L33 _public prototype_ `virtual void Resize(int32 Columns, int32 Rows) override;`
- L34 _public prototype_ `virtual TArray<uint8> ConsumeOutput() override;`
- L35 _public prototype_ `virtual bool IsRunning() const override;`
- L52 _private member_ `int MasterFileDescriptor = -1;` — Master file descriptor of the pseudo-terminal.
- L55 _private member_ `pid_t ProcessId = -1;` — PID of the child shell process.
- L58 _private member_ `TSharedPtr<TAtomic<bool>> bAlive;` — Shared alive flag for safe async callback dispatch after destruction.
- L61 _private member_ `TArray<uint8> StagingBuffer;` — Output staging buffer  - filled by the reader thread, drained by ConsumeOutput() on the game thread.
- L62 _private member_ `FCriticalSection StagingLock;`
- L64 _private member_ `TUniquePtr<FReaderRunnable> ReaderRunnable;`
- L65 _private member_ `TUniquePtr<FRunnableThread> ReaderThread;`

#### class `FPosixPTYSession::FReaderRunnable`  
`class FReaderRunnable : public FRunnable`  
_L40-49_
- inherits: `FRunnable`
- desc: Background I/O reader thread.
- L43 _public function_ `FReaderRunnable(FPosixPTYSession* InOwner) : Owner(InOwner)`
- L44 _public prototype_ `virtual uint32 Run() override;`
- L45 _public prototype_ `virtual void Stop() override;`
- L47 _private member_ `FPosixPTYSession* Owner = nullptr;`
- L48 _private member_ `TAtomic<bool> bStopRequested{false};`

### `Plugins/Experimental/Terminal/Source/Terminal/Public/STerminal.h` (Public)


#### class `STerminal`  
`class STerminal : public SLeafWidget`  
_L24-190_
- inherits: `SLeafWidget`
- desc: Native Slate terminal emulator widget. Renders a character cell grid directly via OnPaint using FSlateDrawElement. Backed by FTerminalBuffer + FVTParser + FConPTYSession.
- L30 _public function_ `SLATE_BEGIN_ARGS(STerminal)`
- L32 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void ExecuteCommand(const FString& Command);` — Write a command string to the terminal session followed by a carriage return.
- L43 _public prototype_ `bool IsSessionRunning() const;` — Returns true once the terminal session has been created and is running.
- L46 _public member_ `FOnTerminalOutputReceived OnOutputReceived;` — Broadcast on the game thread after each tick that consumed a non-empty output chunk from the session.
- L49 _public function_ `double GetLastOutputTime() const` — Engine time of the last non-empty output chunk, or 0.0 if none.
- L52 _public prototype_ `static TArray<TSharedRef<STerminal>> GetAllInstances();` — Snapshot of every live STerminal (and subclass). Game thread only. Expired entries are pruned.
- L55 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L56 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L57 _public prototype_ `virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;`
- L58 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L59 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L60 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L61 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L62 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L63 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L64 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L65 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L66 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L67 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L73 _private prototype_ `EActiveTimerReturnType OnTick(double InCurrentTime, float InDeltaTime);` — Tick handler  - consumes session output and parses it.
- L76 _private prototype_ `EActiveTimerReturnType OnCursorBlink(double InCurrentTime, float InDeltaTime);` — Cursor blink timer.
- L79 _private prototype_ `void MeasureCellSize(float LayoutScale = 1.0f);` — Measure the monospace cell dimensions from the current font at the given layout scale.
- L82 _private prototype_ `void InitializeTerminal();` — Deferred initialization  - creates buffer and terminal session at correct dimensions.
- L85 _private prototype_ `void UpdateViewportDimensions(const FGeometry& AllottedGeometry);` — Recompute viewport rows and columns from the widget's allocated geometry.
- L88 _private prototype_ `void UpdateScrollBar();` — Update the external scrollbar thumb position and size to reflect current scroll state.
- L91 _private prototype_ `FIntPoint PixelToCell(const FGeometry& MyGeometry, const FVector2D& LocalPosition) const;` — Convert a local pixel position to a buffer-absolute cell coordinate.
- L94 _private prototype_ `bool IsCellSelected(int32 AbsoluteRow, int32 Column) const;` — Check if a cell is within the current selection range.
- L97 _private prototype_ `FString GetSelectedText() const;` — Get the selected text as a string.
- L100 _private prototype_ `void ClearSelection();` — Clear the current selection.
- L103 _private prototype_ `void PaintBackground(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;` — Paint per-cell backgrounds (inverse-aware).
- L106 _private prototype_ `void PaintText(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;` — Paint text with monospace-safe batching, underline, and strikethrough.
- L109 _private prototype_ `void PaintForeground(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;` — Paint foreground overlays (selection highlight, cursor).
- L112 _private prototype_ `static FColor ComputeForegroundColor(const FTerminalCell& Cell);` — Compute the effective foreground color for a cell, applying inverse, bold, and dim.
- L115 _private prototype_ `void ApplyColorScheme(const FTerminalColorScheme& Scheme);` — Apply a color scheme to default cell colors.
- L118 _private prototype_ `void HandleProcessExited(int32 ExitCode);` — Called when the shell process exits.
- L121 _private prototype_ `void HandleScrollBarScrolled(float InScrollOffsetFraction);` — Called when the user drags the external scrollbar.
- L124 _private prototype_ `void SendMouseEvent(int32 Button, int32 Column, int32 Row, bool bRelease);` — Send a mouse event escape sequence to the session when mouse tracking is active.
- L127 _private prototype_ `TOptional<FReply> HandleShiftArrowSelection(const FKeyEvent& InKeyEvent);` — Shift+Arrow: start or extend the keyboard selection. Returns a handled reply when consumed.
- L132 _private prototype_ `TOptional<FReply> HandleCopyShortcut(const FKeyEvent& InKeyEvent, bool bCopyPasteModifier);` — Copy the current selection to the OS clipboard on the platform's copy shortcut. Returns a handled reply when the selection was copied; empty otherwise so the caller can fall through (e.g. sending ETX on Ctrl+C without a selection).
- L137 _private prototype_ `TOptional<FReply> HandlePasteShortcut(const FKeyEvent& InKeyEvent, bool bCopyPasteModifier);` — Paste the OS clipboard into the session on the platform's paste shortcut, wrapping in bracketed paste sequences when the parser is in bracketed-paste mode. Returns a handled reply when the event matched the paste shortcut; empty otherwise.
- L140 _private member_ `FTerminalBuffer Buffer;` — Core terminal components.
- L141 _private member_ `FVTParser Parser;`
- L142 _private member_ `TSharedPtr<ITerminalSession> Session;`
- L143 _private member_ `TSharedPtr<SScrollBar> ScrollBar;`
- L146 _private member_ `TSharedPtr<FStandaloneCompositeFont> TerminalFont;` — Font and rendering.
- L147 _private member_ `FSlateFontInfo FontInfo;`
- L148 _private member_ `float CellWidth = 8.0f;`
- L149 _private member_ `float CellHeight = 16.0f;`
- L150 _private member_ `FColor SelectionHighlightColor = FColor(38, 79, 120);`
- L151 _private member_ `FColor CursorDisplayColor = FColor(174, 175, 173, 180);`
- L154 _private member_ `int32 ViewportColumns = 80;` — Viewport dimensions.
- L155 _private member_ `int32 ViewportRows = 24;`
- L156 _private member_ `int32 ScrollOffset = 0;`
- L157 _private member_ `mutable FVector2D LastAllocatedSize = FVector2D::ZeroVector;`
- L160 _private member_ `static constexpr int32 ParseBudgetPerTick = 256 * 1024;` — Per-tick parse budget in bytes.
- L163 _private member_ `TArray<uint8> PendingParseData;` — Leftover bytes from a previous tick that exceeded the parse budget.
- L166 _private member_ `FIntPoint SelectionAnchor = FIntPoint(-1, -1);` — Selection state (buffer-absolute coordinates).
- L167 _private member_ `FIntPoint SelectionActive = FIntPoint(-1, -1);`
- L170 _private member_ `int32 SelectionAutoScrollDirection = 0;` — Auto-scroll during drag selection: positive = scroll up (older), negative = scroll down (newer), 0 = none.
- L171 _private member_ `float SelectionAutoScrollAccumulator = 0.0f;`
- L174 _private member_ `int32 ClickCount = 0;` — Click tracking for double/triple click.
- L175 _private member_ `double LastClickTime = 0.0;`
- L176 _private member_ `FIntPoint LastClickCell = FIntPoint(-1, -1);`
- L179 _private member_ `int64 TotalBytesConsumed = 0;` — Diagnostic counters.
- L180 _private member_ `double LastOutputTime = 0.0;`
- L181 _private member_ `double LastHeartbeatLogTime = 0.0;`
- L184 _private member_ `bool bInitialized = false;` — State flags.
- L185 _private member_ `bool bSessionDead = false;`
- L186 _private member_ `bool bReceivedFirstOutput = false;`
- L187 _private member_ `bool bHasFocus = false;`
- L188 _private member_ `bool bSelecting = false;`
- L189 _private member_ `bool bHasSelection = false;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTerminalOutputReceived, int32 );` — Fired on the game thread after the terminal consumes a non-empty chunk of session output.
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTerminalOutputReceived, int32 );` — Fired on the game thread after the terminal consumes a non-empty chunk of session output.

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalBuffer.h` (Public)


#### enum `ETerminalAttribute::Type`  
`enum Type : uint8`  
_L10-19_
- L12 _public enumerator_ `None = 0`
- L13 _public enumerator_ `Bold = 1 << 0`
- L14 _public enumerator_ `Dim = 1 << 1`
- L15 _public enumerator_ `Italic = 1 << 2`
- L16 _public enumerator_ `Underline = 1 << 3`
- L17 _public enumerator_ `Inverse = 1 << 4`
- L18 _public enumerator_ `Strikethrough = 1 << 5`

#### struct `FTerminalCell`  
`struct FTerminalCell`  
_L23-29_
- desc: A single character cell in the terminal grid.
- L25 _public member_ `TCHAR Character = TEXT(' ');`
- L26 _public member_ `FColor Foreground = FColor(212, 212, 212);`
- L27 _public member_ `FColor Background = FColor(30, 30, 30);`
- L28 _public member_ `uint8 Attributes = ETerminalAttribute::None;`

#### struct `FTerminalCursor`  
`struct FTerminalCursor`  
_L32-41_
- desc: Cursor state for the terminal.
- L34 _public member_ `int32 Row = 0;`
- L35 _public member_ `int32 Column = 0;`
- L36 _public member_ `bool bBlinkOn = true;`
- L39 _public member_ `int32 SavedRow = 0;` — Saved cursor position for DECSC/DECRC.
- L40 _public member_ `int32 SavedColumn = 0;`

#### class `FTerminalBuffer`  
`class FTerminalBuffer`  
_L50-132_
- desc: Ring-buffer-backed character cell grid with configurable scrollback. Rows are stored in a flat ring buffer. The viewport (the visible portion) is always the last ViewportRows rows of the active buffer. Scrollback rows accumulate above the viewport up to ScrollbackLimit.
- L54 _public prototype_ `FTerminalBuffer();`
- L56 _public prototype_ `void Initialize(int32 InColumns, int32 InViewportRows, int32 InScrollbackLimit);`
- L58 _public prototype_ `void Resize(int32 InColumns, int32 InViewportRows);`
- L61 _public prototype_ `const FTerminalCell& GetCell(int32 AbsoluteRow, int32 Column) const;` — Get a cell by absolute row index (0 = oldest scrollback row) and column.
- L64 _public prototype_ `void SetCell(int32 AbsoluteRow, int32 Column, const FTerminalCell& Cell);` — Set a cell by absolute row index and column.
- L67 _public prototype_ `void PushNewLine();` — Push a new blank line at the bottom, advancing the ring buffer.
- L70 _public prototype_ `int32 GetAbsoluteRow(int32 ViewportRow, int32 ScrollOffset) const;` — Get the absolute row index for a given viewport row (0 = top of viewport) and scroll offset.
- L73 _public prototype_ `void Clear();` — Clear the entire buffer.
- L76 _public prototype_ `int32 GetScrollbackLength() const;` — Get the number of rows available for scrollback (above the viewport).
- L79 _public prototype_ `int32 GetTotalRows() const;` — Get the total number of rows written (viewport + scrollback).
- L81 _public function_ `int32 GetColumns() const`
- L82 _public function_ `int32 GetViewportRows() const`
- L85 _public prototype_ `void ScrollRegionUp(int32 TopRow, int32 BottomRow, int32 Count);` — Scroll a region of viewport rows up by Count lines, filling new lines with blank cells.
- L88 _public prototype_ `void ScrollRegionDown(int32 TopRow, int32 BottomRow, int32 Count);` — Scroll a region of viewport rows down by Count lines, filling new lines with blank cells.
- L91 _public prototype_ `void FillRegion(int32 AbsoluteRowStart, int32 ColumnStart, int32 AbsoluteRowEnd, int32 ColumnEnd, const FTerminalCell& Cell);` — Fill a region of cells with a given cell value.
- L94 _public prototype_ `FString GetTextInRange(int32 StartRow, int32 StartColumn, int32 EndRow, int32 EndColumn) const;` — Get text content from a range of buffer-absolute rows.
- L97 _public prototype_ `void ClearScrollback();` — Clear all scrollback rows, keeping only the current viewport content.
- L99 _public member_ `FTerminalCursor Cursor;`
- L102 _public member_ `FTerminalCell DefaultCell;` — Default cell used for clearing and new lines.
- L105 _public prototype_ `void ActivateAlternateBuffer();` — Alternate screen buffer support.
- L106 _public prototype_ `void DeactivateAlternateBuffer();`
- L107 _public function_ `bool IsAlternateBufferActive() const`
- L112 _private prototype_ `int32 GetRingIndex(int32 AbsoluteRow) const;` — Get the ring buffer index for an absolute row.
- L115 _private prototype_ `void EnsureRow(int32 RingIndex);` — Ensure a row exists at the given ring index with correct column count.
- L117 _private member_ `int32 Columns = 80;`
- L118 _private member_ `int32 ViewportRows = 24;`
- L119 _private member_ `int32 ScrollbackLimit = 131072;`
- L122 _private member_ `TArray<TArray<FTerminalCell>> Rows;` — Ring buffer of rows. Each row is a TArray<FTerminalCell> of Columns length.
- L123 _private member_ `int32 RingStart = 0;`
- L124 _private member_ `int32 TotalRowsWritten = 0;`
- L127 _private member_ `bool bAlternateBufferActive = false;` — Alternate buffer state.
- L128 _private member_ `TArray<TArray<FTerminalCell>> SavedMainRows;`
- L129 _private member_ `int32 SavedRingStart = 0;`
- L130 _private member_ `int32 SavedTotalRowsWritten = 0;`
- L131 _private member_ `FTerminalCursor SavedCursor;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ETerminalAttribute`

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalColorScheme.h` (Public)


#### struct `FTerminalColorScheme`  
`struct FTerminalColorScheme`  
_L13-27_
- desc: Terminal color scheme loaded from a JSON file. Each scheme defines: default foreground/background, cursor color, selection highlight color, and a 16-color ANSI palette.
- L15 _public member_ `FString Name;`
- L16 _public member_ `FLinearColor DefaultForeground = FLinearColor(0.831f, 0.831f, 0.831f);`
- L17 _public member_ `FLinearColor DefaultBackground = FLinearColor(0.118f, 0.118f, 0.118f);`
- L18 _public member_ `FLinearColor CursorColor = FLinearColor(0.682f, 0.686f, 0.678f);`
- L19 _public member_ `FLinearColor SelectionColor = FLinearColor(0.149f, 0.310f, 0.471f);`
- L20 _public member_ `TArray<FLinearColor> Palette;` — 16 ANSI colors (0-15)
- L23 _public prototype_ `static FTerminalColorScheme MakeDefault();` — Create a default scheme.
- L26 _public prototype_ `static bool FromJSON(const FString& JSONString, FTerminalColorScheme& OutScheme);` — Parse a scheme from a JSON string. Returns true on success.

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalKeyTranslator.h` (Public)


#### struct `UE::Terminal::FKeyTranslationOptions`  
`struct FKeyTranslationOptions`  
_L12-16_
- desc: Options that influence key-to-byte translation.
- L15 _public member_ `bool bApplicationCursorKeys = false;` — DECCKM: when true, unmodified cursor / Home / End keys use SS3 sequences (ESC O x) instead of CSI (ESC [ x).

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Terminal` (scope `UE`)
- L35 _prototype_ `TArray<uint8> TranslateKeyToBytes(const FKeyEvent& KeyEvent, const FKeyTranslationOptions& Options);` (scope `UE::Terminal`) — Translate a Slate key event to the byte sequence a VT-compatible shell expects. Covers: - Ctrl+A..Z via the `ch & 0x1F` bitmask. - Ctrl+Space / [ / \ / ] / / / ? control-byte mappings. - Enter, Tab (plus Shift+Tab = CSI Z), Escape, BackSpace (plus Ctrl/Alt variants). - Arrows, Home, End, Insert, Delete, PageUp, PageDown, F1..F12 with the xterm modifier parameter `1 + (Shift?1:0) + (Alt?2:0) + (Ctrl?4:0)`. - Alt+<printable> readline meta: `ESC <byte>`. Guarded against AltGr (LeftCtrl + RightAlt on Windows). Returns an empty array when the key has no terminal meaning: pure modifier presses (Shift/Ctrl/Alt alone), unmapped keys, and printable characters that belong to the OnKeyChar path. Non-goals: Kitty keyboard protocol, DECKPAM (application keypad), C1 8-bit control sequences. Add with concrete motivation.

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalModule.h` (Public)


#### class `FTerminalModule`  
`class FTerminalModule : public IModuleInterface`  
_L10-26_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `TSharedRef<SDockTab> SpawnTerminalTab(const FSpawnTabArgs& SpawnTabArgs);`
- L23 _private prototype_ `bool HandleCanCloseEditor();` — Returns false (vetoes close) if any STerminal is producing output and the user declines to close.
- L25 _private member_ `FDelegateHandle CanCloseEditorHandle;`

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalSettings.h` (Public)


#### class `UTerminalSettings`  
`class UTerminalSettings : public UDeveloperSettings`  
_L10-47_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta=(DisplayName="Terminal"))`
- inherits: `UDeveloperSettings`
- L18 _public member_ `FString ShellExecutablePath;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal")` — Path to the shell executable. Leave empty to use the system default (COMSPEC on Windows, SHELL on Unix).
- L22 _public member_ `FString FontFamily = TEXT("Cas` — `UPROPERTY(Config, EditAnywhere, Category="Terminal")` — Font filename stem (without extension) as found in the system Fonts directory, e.g. "consola" for Consolas.
- L26 _public member_ `int32 FontSize = 10;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal", meta=(ClampMin=6, ClampMax=72))` — Font size in points.
- L30 _public member_ `int32 ScrollbackLimit = 131072;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal", meta=(ClampMin=0, ClampMax=1000000))` — Maximum number of scrollback rows retained by the terminal.
- L34 _public member_ `FString ColorSchemeName = TEXT("Def` — `UPROPERTY(Config, EditAnywhere, Category="Terminal")` — Name of the color scheme to use. Must match a JSON file in Config/ColorSchemes/.
- L38 _public member_ `TArray<FString> StartupCommands;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal")` — Commands to execute automatically when a new terminal window is created. Each entry is sent as a separate command.
- L42 _public member_ `bool bPreventCloseDuringActivity = true;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal|Activity")` — When true, prompt for confirmation if the editor is closed while a terminal session is producing output.
- L46 _public member_ `float ActivityTimeoutSeconds = 5.0f;` — `UPROPERTY(Config, EditAnywhere, Category="Terminal|Activity", meta=(ClampMin=1.0, ClampMax=60.0, EditCondition="bPreventCloseDuringActivity"))` — Seconds of silence after which a terminal is no longer considered active. Floor is 1.0s to stay above realistic tick jitter (frame hitches, GC pauses).

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalSubsystem.h` (Public)


#### class `UTerminalSubsystem`  
`class UTerminalSubsystem : public UEditorSubsystem`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Editor subsystem that manages terminal sessions and color schemes.
- L21 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L22 _public prototype_ `virtual void Deinitialize() override;`
- L26 _public prototype_ `FTerminalColorScheme GetActiveColorScheme() const;` — Get the active color scheme based on settings.
- L29 _public prototype_ `FTerminalColorScheme GetColorScheme(const FString& Name) const;` — Get a color scheme by name. Returns the default if not found.
- L32 _public prototype_ `void ReloadColorSchemes();` — Reload color schemes from disk.
- L37 _private member_ `TMap<FString, FTerminalColorScheme> ColorSchemes;` — Loaded color schemes indexed by name.
- L40 _private member_ `FTerminalColorScheme DefaultScheme;` — The hardcoded default scheme used as fallback.

### `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TerminalUtilities`
- L11 _prototype_ `bool IsMonospaceSafe(TCHAR Character);` (scope `TerminalUtilities`) — Returns true for characters that the primary monospace font will render with correct cell-width advance.
- L14 _prototype_ `FString ResolveSystemFontPath(const FString& FontFamily);` (scope `TerminalUtilities`) — Resolve a font family name to an absolute .ttf path in the system Fonts directory. Returns empty if not found.
- L17 _prototype_ `TArrayView<const TCHAR* const> GetFallbackFontNames();` (scope `TerminalUtilities`) — Platform-appropriate monospace font fallback names, tried in order.
- L20 _prototype_ `TArrayView<const TCHAR* const> GetSymbolFontNames();` (scope `TerminalUtilities`) — Platform-appropriate symbol font names (box drawing, arrows, math, etc.), tried in order.
- L23 _prototype_ `TArrayView<const TCHAR* const> GetEmojiFontNames();` (scope `TerminalUtilities`) — Platform-appropriate emoji font names, tried in order.
- L26 _prototype_ `FString GetEngineFallbackFontPath();` (scope `TerminalUtilities`) — Engine-bundled monospace font path, used as final fallback when no system font is found.
- L29 _prototype_ `FLinearColor ParseHexColor(const FString& HexString);` (scope `TerminalUtilities`) — Parse a hex color string (with or without leading '#') into a linear color. Returns white on invalid input.

### `Plugins/Experimental/Terminal/Source/Terminal/Public/VTParser.h` (Public)


#### class `FVTParser`  
`class FVTParser`  
_L18-174_
- desc: VT/ANSI escape sequence parser implemented as a state machine. Follows the Paul Williams / vt100.net canonical parser model with 14 states, "anywhere" transitions (ESC/CAN/SUB), and proper C0 mid-sequence execution. Processes a byte buffer of UTF-8 text containing VT sequences and applies the resulting actions to an FTerminalBuffer.
- L22 _public prototype_ `FVTParser();`
- L25 _public prototype_ `void SetBuffer(FTerminalBuffer* InBuffer);` — Bind the parser to a terminal buffer. Must be called before Parse().
- L28 _public prototype_ `void Parse(const uint8* Data, int32 Length);` — Parse a chunk of UTF-8 bytes.
- L31 _public prototype_ `void Reset();` — Reset the parser and SGR state to defaults.
- L34 _public prototype_ `FString GetDebugStateName() const;` — Get the current parser state as a debug string.
- L37 _public prototype_ `void InitializeTabStops();` — Initialize default tab stops (every 8 columns).
- L40 _public member_ `FColor CurrentForeground;` — Current SGR state applied to newly written cells.
- L41 _public member_ `FColor CurrentBackground;`
- L42 _public member_ `uint8 CurrentAttributes = 0;`
- L45 _public member_ `FColor AnsiPalette[16];` — 16-color ANSI palette (indices 0-15). Initialized with defaults, overridden by color scheme.
- L48 _public member_ `int32 ScrollRegionTop = -1;` — Scroll region (viewport-relative, inclusive). -1 means default (full viewport).
- L49 _public member_ `int32 ScrollRegionBottom = -1;`
- L55 _public member_ `bool bAutoWrap = true;` — Mode flags.
- L56 _public member_ `bool bCursorVisible = true;`
- L57 _public member_ `bool bApplicationCursorKeys = false;`
- L58 _public member_ `bool bBracketedPaste = false;`
- L59 _public member_ `bool bSynchronizedOutput = false;`
- L60 _public member_ `bool bSGRMouseEncoding = false;`
- L61 _public member_ `EMouseTrackingMode MouseTrackingMode = EMouseTrackingMode::None;`
- L64 _public member_ `TArray<bool> TabStops;` — Tab stops.
- L67 _public member_ `FString WindowTitle;` — Window title set via OSC.
- L70 _public member_ `TArray<uint8> ResponseBuffer;` — Response buffer  - bytes to send back to the PTY (DA, DSR replies). Drained by STerminal::OnTick.
- L93 _private member_ `EParserState State = EParserState::Ground;`
- L96 _private member_ `TArray<int32> CSIParams;` — CSI/DCS parameter accumulation.
- L97 _private member_ `FString CSIIntermediateChars;`
- L98 _private member_ `FString CurrentParam;`
- L101 _private member_ `TCHAR CSIPrivatePrefix = 0;` — CSI private parameter prefix character ('<', '=', '>', '?'), or '\0' for none.
- L104 _private member_ `FString EscapeIntermediateChars;` — Escape sequence intermediate characters accumulator.
- L107 _private member_ `FString OSCPayload;` — OSC accumulation.
- L109 _private member_ `FTerminalBuffer* Buffer = nullptr;`
- L112 _private member_ `uint32 UTF8Codepoint = 0;` — UTF-8 decoder state.
- L113 _private member_ `int32 UTF8Remaining = 0;`
- L114 _private member_ `uint32 UTF8MinCodepoint = 0;` — Minimum valid codepoint for current sequence length (overlong detection).
- L117 _private prototype_ `void ProcessCodepoint(uint32 Codepoint);` — Process a single decoded Unicode codepoint.
- L120 _private prototype_ `void ClearSequenceState();` — Reset CSI/DCS parameter accumulation state (the spec's "clear" action).
- L123 _private prototype_ `bool TryExecuteC0(uint32 Codepoint);` — Execute a C0 control character in Ground context. Returns true if handled.
- L126 _private prototype_ `void HandleGround(uint32 Codepoint);` — State handlers.
- L127 _private prototype_ `void HandleEscape(uint32 Codepoint);`
- L128 _private prototype_ `void HandleEscapeIntermediate(uint32 Codepoint);`
- L129 _private prototype_ `void HandleCSIEntry(uint32 Codepoint);`
- L130 _private prototype_ `void HandleCSIParam(uint32 Codepoint);`
- L131 _private prototype_ `void HandleCSIIntermediate(uint32 Codepoint);`
- L132 _private prototype_ `void HandleCSIIgnore(uint32 Codepoint);`
- L133 _private prototype_ `void HandleOSCString(uint32 Codepoint);`
- L134 _private prototype_ `void HandleDCSEntry(uint32 Codepoint);`
- L135 _private prototype_ `void HandleDCSParam(uint32 Codepoint);`
- L136 _private prototype_ `void HandleDCSIntermediate(uint32 Codepoint);`
- L137 _private prototype_ `void HandleDCSPassthrough(uint32 Codepoint);`
- L138 _private prototype_ `void HandleDCSIgnore(uint32 Codepoint);`
- L139 _private prototype_ `void HandleSOSPMAPCString(uint32 Codepoint);`
- L142 _private prototype_ `void ExecuteCSI(uint32 FinalByte);` — Execute a completed CSI sequence.
- L145 _private prototype_ `void ExecuteSGR();` — Execute an SGR (Select Graphic Rendition) sequence.
- L148 _private prototype_ `void ExecutePrivateMode(uint32 FinalByte);` — Execute a DECSET/DECRST private mode sequence.
- L151 _private prototype_ `void ExecuteEscapeSequence(uint32 FinalByte);` — Execute a completed escape sequence with intermediates.
- L154 _private prototype_ `void ExecuteOSC();` — Execute a completed OSC sequence.
- L157 _private prototype_ `void PutCharacter(TCHAR Character);` — Write a printable character at the cursor position.
- L160 _private prototype_ `static bool IsZeroWidthCodepoint(uint32 Codepoint);` — Check if a codepoint is zero-width (combining marks, variation selectors, etc.).
- L163 _private prototype_ `void LineFeed();` — Advance the cursor to the next line, scrolling if necessary.
- L166 _private prototype_ `int32 GetEffectiveScrollTop() const;` — Get the effective scroll region boundaries.
- L167 _private prototype_ `int32 GetEffectiveScrollBottom() const;`
- L170 _private prototype_ `int32 GetCSIParam(int32 Index, int32 Default) const;` — Helper to get a CSI parameter with a default value.
- L173 _private prototype_ `FColor Get256Color(int32 Index) const;` — Get a color from the 256-color palette. Indices 0-15 use AnsiPalette.

#### enum `FVTParser::EMouseTrackingMode`  
`enum class EMouseTrackingMode : uint8`  
_L52-52_
- desc: Mouse tracking mode set via DECSET 1000/1002/1003. Encoding format controlled by mode 1006 (`bSGRMouseEncoding`).
- L52 _public enumerator_ `enum class EMouseTrackingMode : uint8 { None, Normal, ButtonEvent, Any }; bool bAutoWrap = true; bool bCursorVisible = true; bool bApplicationCursorKeys = false; bool bBracketedPaste = false; bool bSynchronizedOutput = false;` — Mouse tracking mode set via DECSET 1000/1002/1003. Encoding format controlled by mode 1006 (`bSGRMouseEncoding`).
- L52 _public enumerator_ `enum class EMouseTrackingMode : uint8 { None, Normal, ButtonEvent, Any }; bool bAutoWrap = true; bool bCursorVisible = true; bool bApplicationCursorKeys = false; bool bBracketedPaste = false; bool bSynchronizedOutput = false;` — Mouse tracking mode set via DECSET 1000/1002/1003. Encoding format controlled by mode 1006 (`bSGRMouseEncoding`).
- L52 _public enumerator_ `enum class EMouseTrackingMode : uint8 { None, Normal, ButtonEvent, Any }; bool bAutoWrap = true; bool bCursorVisible = true; bool bApplicationCursorKeys = false; bool bBracketedPaste = false; bool bSynchronizedOutput = false;` — Mouse tracking mode set via DECSET 1000/1002/1003. Encoding format controlled by mode 1006 (`bSGRMouseEncoding`).
- L52 _public enumerator_ `enum class EMouseTrackingMode : uint8 { None, Normal, ButtonEvent, Any }; bool bAutoWrap = true; bool bCursorVisible = true; bool bApplicationCursorKeys = false; bool bBracketedPaste = false; bool bSynchronizedOutput = false;` — Mouse tracking mode set via DECSET 1000/1002/1003. Encoding format controlled by mode 1006 (`bSGRMouseEncoding`).

#### enum `FVTParser::EParserState`  
`enum class EParserState : uint8`  
_L75-91_
- desc: Parser states per the Williams/vt100.net state machine.
- L77 _public enumerator_ `Ground`
- L78 _public enumerator_ `Escape`
- L79 _public enumerator_ `EscapeIntermediate`
- L80 _public enumerator_ `CSIEntry`
- L81 _public enumerator_ `CSIParam`
- L82 _public enumerator_ `CSIIntermediate`
- L83 _public enumerator_ `CSIIgnore`
- L84 _public enumerator_ `OSCString`
- L85 _public enumerator_ `DCSEntry`
- L86 _public enumerator_ `DCSParam`
- L87 _public enumerator_ `DCSIntermediate`
- L88 _public enumerator_ `DCSPassthrough`
- L89 _public enumerator_ `DCSIgnore`
- L90 _public enumerator_ `SOSPMAPCString`
